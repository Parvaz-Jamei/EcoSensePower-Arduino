Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 3.1 Industrial RC Evidence

Package: `EcoSensePower-Arduino-phase3.1-industrial-rc.zip`  
Library version: `0.3.2`  
Status: Industrial RC package with host logic evidence; public release still requires real Arduino Lint/CLI or GitHub Actions evidence.

| Gate | Status | Evidence |
|---|---|---|
| Arduino Lint strict | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/lint.yml` uses `arduino/arduino-lint-action@v2`, `library-manager: submit`, `compliance: strict`; local sandbox has no `arduino-lint`. |
| AVR UNO compile | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/compile-avr.yml` and compile matrix configured; local sandbox has no `arduino-cli`. |
| AVR Nano compile | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/compile-avr.yml` configured; local sandbox has no `arduino-cli`. |
| ESP32 compile | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/compile.yml` includes ESP32 FQBN and platform URL; local sandbox has no `arduino-cli`. |
| SAMD compile | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/compile.yml` includes SAMD Zero compile target; local sandbox has no `arduino-cli`. |
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` PASS: energy contract, adaptive sampler, energy ledger, PowerDoctor diagnostics, guard lifecycle. |
| Guard lifecycle tests | PASS | `test_guard_lifecycle.cpp`: wake/sleep callbacks run once per cycle and do not repeat during idle backend sleep. |
| Energy Ledger tests | PASS | `test_energy_ledger.cpp`: cycle open/close, cycle/lifetime duration and energy totals. |
| PowerDoctor diagnostic-code tests | PASS | `test_power_doctor.cpp`: machine-readable diagnostic codes detected for backend/profile/measurement risk. |
| Generic host compile | PASS | g++ mock compile of source and all examples. |
| AVR mock compile | PASS | g++ mock compile with `ARDUINO_ARCH_AVR` and AVR sleep/power headers. |
| AVR optional power-down compile | PASS | g++ mock compile with `ECOSENSE_AVR_ENABLE_POWERDOWN`. |
| ESP32 mock compile | PASS | g++ mock compile with `ARDUINO_ARCH_ESP32` and `esp_sleep.h` mock. |
| SAMD/nRF52/RP2040 placeholder compile | PASS | g++ mock compile of guarded placeholder backend headers. |
| No mandatory dependency | PASS | Core has no mandatory WiFi/BLE/RadioLib/TinyML/harvesting dependency. |
| No hardware measurement claim | PASS | README/docs state measurement is owner-side and estimates are profile-based. |
| No battery-life guarantee | PASS | README/docs explicitly reject battery-life guarantees. |
| Library Manager hard rules | STRUCTURE PASS / REAL LINT PENDING | `library.properties` in root, SemVer, `includes=EcoSensePower.h`, examples independent, no forbidden files detected. |

## Local commands executed in sandbox

```bash
extras/tests/run_host_tests.sh
```

Additional host smoke checks were executed with g++ mocks for generic, AVR, AVR optional power-down, ESP32, SAMD, nRF52, RP2040, and all examples. These are useful logic/syntax checks, not a substitute for real Arduino CLI compile.

## Public release decision

Public release is **not approved** until at least:

- Arduino Lint strict PASS
- AVR UNO compile PASS
- AVR Nano compile PASS
- ESP32 compile PASS or clearly marked pending
- SAMD compile PASS or clearly marked pending
