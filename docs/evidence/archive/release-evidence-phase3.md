Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 3 Evidence

Package: `EcoSensePower-Arduino-phase3.zip`  
Library version: `0.3.0`  
Status: Superseded by Phase 3.1 RC polish (`release-evidence-phase3-rc.md`).

| Gate | Status | Evidence |
|---|---|---|
| Arduino Lint strict | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/lint.yml` uses `arduino/arduino-lint-action@v2` with `library-manager: submit` and `compliance: strict`; sandbox has no `arduino-lint`. |
| AVR UNO compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile-avr.yml` targets `arduino:avr:uno`; host AVR mock compile passed with `-DARDUINO_ARCH_AVR`. |
| AVR Nano compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile-avr.yml` targets `arduino:avr:nano`; host AVR mock compile passed with `-DARDUINO_ARCH_AVR`. |
| ESP32 compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile.yml` targets `esp32:esp32:esp32`; host ESP32 mock compile passed with `-DARDUINO_ARCH_ESP32`. |
| SAMD compile | CI CONFIGURED / HOST MOCK PASS | `.github/workflows/compile.yml` targets `arduino:samd:arduino_zero_edbg`; host SAMD mock compile passed with `-DARDUINO_ARCH_SAMD`. |
| All examples compile | HOST MOCK PASS | All examples compiled as C++ with the local Arduino mock for generic, AVR, AVR power-down, ESP32, SAMD, nRF52, and RP2040 modes during the post-review check. |
| Library Manager hard rules | PASS / CI PENDING | `library.properties`, SemVer version, `includes`, no forbidden files, no mandatory dependencies; real Arduino Lint output pending. |
| No mandatory dependencies | PASS | `depends=` is empty; no RadioLib/WiFi/BLE/TFLM mandatory include in core. |
| Phase 1/2 regression check | PASS | Patch A safety behaviors and Phase 2 backend/docs/features preserved. |
| Full Duty Cycle Ledger semantics | PASS | Runtime begins cycle before sleep when needed and keeps sleep + active processing in the same open cycle until `processSensor()` ends it. |
| Static lifetime docs | PASS | README, `docs/api.md`, and `docs/limitations.md` document static-lifetime requirement for sensor/guard names. |
| ESP32-C3/S3 status | PASS | Marked experimental until separate compile/hardware evidence exists. |
| No hardware measurement claims | PASS | No real current measurement claimed. |
| Battery lifetime guarantee | NOT CLAIMED | Battery-life claims require owner-side validation. |

## Local host compile commands executed

```bash
# Generic host compile
find src -name '*.cpp'
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -c <all sources>
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -x c++ -c examples/*/*.ino

# AVR host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_AVR -I mock -I mock_avr -I src -c <all sources and examples>

# ESP32 host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_ESP32 -I mock -I mock_esp32 -I src -c <all sources and examples>

# SAMD host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_SAMD -I mock -I src -c <all sources and examples>

# nRF52/RP2040 placeholder host compile
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_NRF52 -I mock -I src -c <all sources and examples>
g++ -std=c++11 -Wall -Wextra -Werror -DARDUINO_ARCH_RP2040 -I mock -I src -c <all sources and examples>
```

## Local tool limitation

`arduino-cli` and `arduino-lint` were not installed in the sandbox, so real Arduino CLI/Lint output is marked CI-configured / pending. Public release remains `NOT APPROVED` until real GitHub Actions or local Arduino CLI/Lint output is attached.

## Post-review hardening check

Performed after the phase 3 package review:

| Check | Status | Evidence |
|---|---|---|
| ZIP integrity | PASS | `unzip -t EcoSensePower-Arduino-phase3.zip`: no compressed data errors. |
| Forbidden files | PASS | No `.development`, `.exe`, symlinks, build junk, `.pio`, `__MACOSX`, or `.DS_Store`. |
| Mandatory heavy dependencies | PASS | No mandatory RadioLib/WiFi/BLE/TFLM includes in core; `depends=` remains empty. |
| Dynamic allocation/STL in core | PASS | No `malloc`, `new`, `std::vector`, or mandatory `String` use in `src/`. |
| Mock compile matrix | PASS | Generic, AVR, AVR power-down, ESP32, SAMD, nRF52, and RP2040 host mock compiles passed for sources and examples. |
| Documentation polish | PASS | README example list now includes `LoRaAdaptiveReporter`; evidence updated to reflect expanded review scope. |

Result: no code blocker found in this review. Public release still requires real Arduino CLI/Lint or GitHub Actions evidence.
