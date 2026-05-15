Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 2 Evidence

Package: `EcoSensePower-Arduino-phase2.zip`  
Library version: `0.2.0`  
Status: Phase 2 alpha hardening package built in sandbox.

| Gate | Status | Evidence |
|---|---|---|
| Arduino Lint strict | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/lint.yml` uses `arduino/arduino-lint-action@v2` with `library-manager: submit` and `compliance: strict`. Local sandbox does not include `arduino-lint`. |
| AVR UNO compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile-avr.yml` targets `arduino:avr:uno`; host AVR mock compile passed with `-DARDUINO_ARCH_AVR`. |
| AVR Nano compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile-avr.yml` targets `arduino:avr:nano`; host AVR mock compile passed with `-DARDUINO_ARCH_AVR`. |
| ESP32 compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile.yml` targets `esp32:esp32:esp32`; host ESP32 mock compile passed with `-DARDUINO_ARCH_ESP32`. |
| SAMD compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile.yml` targets `arduino:samd:arduino_zero_edbg`; host SAMD mock compile passed with `-DARDUINO_ARCH_SAMD`. |
| Host compile | PASS | Generic, AVR, ESP32, and SAMD host C++ smoke compiles passed with mock Arduino APIs. |
| Phase 2 behavior smoke | PASS | Linked executable exercised guard API, sensor API, cycle ledger printing, total ledger printing, and Power Doctor output. |
| No external mandatory dependency | PASS | `library.properties` has empty `depends=`; no RadioLib/WiFi/BLE/TFLM includes in core. |
| AVR backend guarded | PASS | AVR code remains behind `ARDUINO_ARCH_AVR`; AVR headers are only used under `src/arch/avr`. |
| ESP32 backend guarded | PASS | ESP32 code remains behind `ARDUINO_ARCH_ESP32`; ESP32 sleep APIs are only used under `src/arch/esp32`. |
| Power Doctor v2 warnings documented | PASS | `docs/power-doctor.md` and `src/core/PowerDoctor.*`. |
| Energy Ledger cycle mode | PASS | `beginCycle`, `endCycle`, `clearCycle`, `printCycleTo`, `printTotalTo`, cycle/lifetime totals, dominant state, aggregate mode. |
| Peripheral Guard baseline | PASS | Callback guard, power pin guard, AVR ADC guard, ESP32 wireless guard marker. |
| Radio adapter interface | PASS | `src/radio/generic/RadioEnergyAdapter.h`, no mandatory dependency. |
| ARM/SAMD/nRF52/RP2040 readiness | PASS | Placeholder guarded headers and support docs added. |
| Hardware current measurement | NOT TESTED | Owner-side only. No hardware testing was performed or claimed. |
| Battery life guarantee | NOT CLAIMED | README/docs explicitly reject battery-life guarantees without measurement. |

## Host compile commands executed

```bash
# Generic host compile
find src -name '*.cpp'
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -c <all sources>
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -x c++ -c examples/*/*.ino

# AVR host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_AVR -I mock -I src -c <all sources and examples>

# ESP32 host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_ESP32 -I mock -I src -c <all sources and examples>

# SAMD host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_SAMD -I mock -I src -c <all sources and examples>
```

## Local tool limitation

`arduino-cli` and `arduino-lint` were not installed in the sandbox, so real Arduino CLI/Lint output is marked CI-configured / pending. The workflows are included for real GitHub Actions evidence.
