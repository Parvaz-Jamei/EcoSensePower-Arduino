#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
BUILD_DIR="$ROOT/extras/tests/header_build"
MOCK_DIR="$ROOT/extras/tests/mock_arduino"
CXX=${CXX:-g++}
COMPILE_TIMEOUT_SECONDS=${ECOSENSE_COMPILE_TIMEOUT_SECONDS:-120}
CXXFLAGS="-std=c++11 -Wall -Wextra -Werror -DECOSENSE_HOST_TEST -I$MOCK_DIR -I$ROOT/extras/tests -I$ROOT/src -I$ROOT"

rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR/individual"
WRAPPER="$BUILD_DIR/all_headers_self_containment.cpp"
{
  echo '#include <Arduino.h>'
  while IFS= read -r header; do
    rel="${header#$ROOT/src/}"
    echo "#include \"$rel\""
  done < <(find "$ROOT/src" -name '*.h' | sort)
  echo 'int main() { return 0; }'
} > "$WRAPPER"

count="$(find "$ROOT/src" -name '*.h' | wc -l | tr -d ' ')"
echo "[EcoSensePower header self-containment] aggregate check for all $count src/**/*.h headers"
timeout "$COMPILE_TIMEOUT_SECONDS" "$CXX" $CXXFLAGS -fsyntax-only "$WRAPPER"

echo "[EcoSensePower header self-containment] critical individual header wrapper syntax-check"
critical_headers=(
  "$ROOT/src/EcoSensePower.h"
  "$ROOT/src/EcoSensePowerProfiles.h"
  "$ROOT/src/EcoSensePowerBluetoothProfiles.h"
  "$ROOT/src/EcoSensePowerGPSProfiles.h"
  "$ROOT/src/core/EcoSensePowerConfig.h"
  "$ROOT/src/radio/GenericRadioProfile.h"
  "$ROOT/src/profiles/radios/bluetooth/bluetooth_ble_generic.h"
  "$ROOT/src/profiles/radios/bluetooth/hc05_bluetooth.h"
  "$ROOT/src/profiles/radios/bluetooth/hm10_ble.h"
  "$ROOT/src/profiles/gps/gps_generic.h"
  "$ROOT/src/profiles/gps/ublox_neo6m.h"
  "$ROOT/src/profiles/gps/gnss_multiconstellation_generic.h"
  "$ROOT/src/integrations/optional/ArduinoBLEEnergyAdapter.h"
  "$ROOT/src/integrations/optional/TinyGPSPlusEnergyAdapter.h"
  "$ROOT/src/integrations/optional/AdafruitGPSEnergyAdapter.h"
)
for header in "${critical_headers[@]}"; do
  rel="${header#$ROOT/src/}"
  safe="${rel//\//_}"
  safe="${safe//./_}"
  wrapper="$BUILD_DIR/individual/${safe}.cpp"
  {
    echo '#include <Arduino.h>'
    echo "#include \"$rel\""
    echo 'int main() { return 0; }'
  } > "$wrapper"
  timeout "$COMPILE_TIMEOUT_SECONDS" "$CXX" $CXXFLAGS -fsyntax-only "$wrapper"
done

echo "[EcoSensePower header self-containment] checked $count headers in aggregate and ${#critical_headers[@]} critical headers individually"
echo "[EcoSensePower header self-containment] PASS"
