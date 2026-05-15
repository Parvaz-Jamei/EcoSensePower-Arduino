#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"
rm -rf extras/tests/bin extras/tests/obj
mkdir -p extras/tests/bin extras/tests/obj
CXX=${CXX:-g++}
COMPILE_TIMEOUT_SECONDS=${ECOSENSE_COMPILE_TIMEOUT_SECONDS:-120}
RUN_TIMEOUT_SECONDS=${ECOSENSE_RUN_TIMEOUT_SECONDS:-60}
HOST_JOBS=${ECOSENSE_HOST_JOBS:-4}
CXXFLAGS="-std=c++17 -Wall -Wextra -Werror -DECOSENSE_HOST_TEST -Iextras/tests/mock_arduino -Iextras/tests -Isrc"
COMMON_SRC=(
  extras/tests/mock_arduino/Arduino.cpp
  src/EcoSensePower.cpp
  src/core/EcoRuntime.cpp
  src/core/EcoScheduler.cpp
  src/core/EnergyContract.cpp
  src/core/AdaptiveSampler.cpp
  src/core/EnergyModel.cpp
  src/core/EnergyLedger.cpp
  src/core/PowerDoctor.cpp
  src/core/PeripheralGuard.cpp
  src/core/SoCTracker.cpp
  src/core/EnergyBudgetManager.cpp
  src/harvester/SolarHarvester.cpp
  src/harvester/PiezoHarvester.cpp
  src/harvester/ThermoelectricHarvester.cpp
  src/harvester/WindHarvester.cpp
  src/radio/GenericRadioProfile.cpp
  src/ml/InferenceBudget.cpp
  src/arch/generic/SleepBackend.cpp
  src/arch/generic/PeripheralGuard.cpp
  src/util/VoltageDivider.cpp
)

pids=()
wait_for_slot() {
  while [ "${#pids[@]}" -ge "$HOST_JOBS" ]; do
    wait -n
    live=()
    for pid in "${pids[@]}"; do
      if kill -0 "$pid" 2>/dev/null; then live+=("$pid"); fi
    done
    pids=("${live[@]}")
  done
}

compile_common() {
  local src="$1"
  local obj="extras/tests/obj/${src//\//_}.o"
  echo "[EcoSensePower host test] build common $src"
  timeout "$COMPILE_TIMEOUT_SECONDS" $CXX $CXXFLAGS -c "$src" -o "$obj"
}

compile_test() {
  local test_src="$1"
  local test_name="$2"
  local func="${test_name}_main"
  local obj="extras/tests/obj/${test_name}.o"
  echo "[EcoSensePower host test] build $test_name"
  timeout "$COMPILE_TIMEOUT_SECONDS" $CXX $CXXFLAGS -Dmain="$func" -c "$test_src" -o "$obj"
}

for src in "${COMMON_SRC[@]}"; do
  wait_for_slot
  compile_common "$src" &
  pids+=("$!")
done
wait
pids=()

COMMON_OBJ=()
for src in "${COMMON_SRC[@]}"; do
  COMMON_OBJ+=("extras/tests/obj/${src//\//_}.o")
done

TEST_NAMES=()
TEST_OBJS=()
for test_src in extras/tests/test_*.cpp; do
  test_name="$(basename "$test_src" .cpp)"
  TEST_NAMES+=("$test_name")
  TEST_OBJS+=("extras/tests/obj/${test_name}.o")
  wait_for_slot
  compile_test "$test_src" "$test_name" &
  pids+=("$!")
done
wait

RUNNER="extras/tests/obj/combined_host_tests.cpp"
echo '#include <stdio.h>' > "$RUNNER"
for test_name in "${TEST_NAMES[@]}"; do
  echo "int ${test_name}_main();" >> "$RUNNER"
done
{
  echo 'int main() {'
  for test_name in "${TEST_NAMES[@]}"; do
    echo "  printf(\"[EcoSensePower host test] run ${test_name}\\n\");"
    echo "  if (${test_name}_main() != 0) return 1;"
  done
  echo '  return 0;'
  echo '}'
} >> "$RUNNER"
exe="extras/tests/bin/combined_host_tests"
echo "[EcoSensePower host test] link combined host test runner"
timeout "$COMPILE_TIMEOUT_SECONDS" $CXX $CXXFLAGS "$RUNNER" "${COMMON_OBJ[@]}" "${TEST_OBJS[@]}" -o "$exe"
timeout "$RUN_TIMEOUT_SECONDS" "$exe"
echo "[EcoSensePower host test] PASS"
