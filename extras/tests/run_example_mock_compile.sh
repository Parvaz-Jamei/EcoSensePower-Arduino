#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="$ROOT/extras/tests/example_build"
OBJ_DIR="$BUILD_DIR/obj"
MOCK_DIR="$ROOT/extras/tests/mock_arduino"
CXX=${CXX:-g++}
COMPILE_TIMEOUT_SECONDS=${ECOSENSE_COMPILE_TIMEOUT_SECONDS:-120}
JOBS=${ECOSENSE_JOBS:-$(command -v nproc >/dev/null 2>&1 && nproc || echo 2)}
CXXFLAGS="-std=c++11 -Wall -Wextra -Werror -DECOSENSE_HOST_TEST -I$MOCK_DIR -I$ROOT/extras/tests -I$ROOT/src -I$ROOT"

rm -rf "$BUILD_DIR"
mkdir -p "$OBJ_DIR"

echo "[EcoSensePower example mock] CXXFLAGS include -Wall -Wextra -Werror"
echo "[EcoSensePower example mock] build common src/**/*.cpp with $JOBS job(s)"

mapfile -t COMMON_SRC < <(find "$ROOT/src" -name '*.cpp' | sort)
COMMON_SRC=("$ROOT/extras/tests/mock_arduino/Arduino.cpp" "${COMMON_SRC[@]}")

export ROOT OBJ_DIR CXX COMPILE_TIMEOUT_SECONDS CXXFLAGS
printf '%s\0' "${COMMON_SRC[@]}" | xargs -0 -n1 -P "$JOBS" bash -c '
  set -euo pipefail
  src="$1"
  rel="${src#$ROOT/}"
  obj="$OBJ_DIR/${rel//\//_}.o"
  echo "[EcoSensePower example mock] build common $rel"
  timeout "$COMPILE_TIMEOUT_SECONDS" "$CXX" $CXXFLAGS -c "$src" -o "$obj"
' _

COMBINED="$BUILD_DIR/combined_examples_wrapper.cpp"
cat > "$COMBINED" <<'CPP'
#include <Arduino.h>
#include <EcoSensePower.h>
CPP

while IFS= read -r header; do
  rel="${header#$ROOT/src/}"
  echo "#include \"$rel\"" >> "$COMBINED"
done < <(find "$ROOT/src" -name '*.h' | sort)

index=0
for sketch in "$ROOT"/examples/*/*.ino; do
  name="$(basename "$(dirname "$sketch")")"
  echo "[EcoSensePower example mock] include $name"
  {
    echo "namespace EcoSenseExampleMock_${index} {"
    echo "#include \"$sketch\""
    echo "}"
  } >> "$COMBINED"
  index=$((index + 1))
done

echo "[EcoSensePower example mock] syntax-check combined examples"
timeout "$COMPILE_TIMEOUT_SECONDS" "$CXX" $CXXFLAGS -fsyntax-only "$COMBINED"

echo "[EcoSensePower example mock] individual wrapper syntax-check with $JOBS job(s)"
WRAPPERS_FILE="$BUILD_DIR/individual_wrappers.tsv"
: > "$WRAPPERS_FILE"
idx=0
for sketch in "$ROOT"/examples/*/*.ino; do
  name="$(basename "$(dirname "$sketch")")"
  wrapper="$BUILD_DIR/individual_${idx}_${name}.cpp"
  {
    echo "#include <Arduino.h>"
    echo "#include <EcoSensePower.h>"
    echo "namespace EcoSenseExampleIndividual_${idx} {"
    echo "#include \"$sketch\""
    echo "}"
  } > "$wrapper"
  printf '%s\t%s\n' "$name" "$wrapper" >> "$WRAPPERS_FILE"
  idx=$((idx + 1))
done

while IFS=$'\t' read -r name wrapper; do
  printf '%s\0%s\0' "$name" "$wrapper"
done < "$WRAPPERS_FILE" | xargs -0 -n2 -P "$JOBS" bash -c '
  set -euo pipefail
  name="$1"
  wrapper="$2"
  echo "[EcoSensePower example mock] syntax-check individual $name"
  timeout "$COMPILE_TIMEOUT_SECONDS" "$CXX" $CXXFLAGS -fsyntax-only "$wrapper"
' _

echo "[EcoSensePower example mock] PASS"
