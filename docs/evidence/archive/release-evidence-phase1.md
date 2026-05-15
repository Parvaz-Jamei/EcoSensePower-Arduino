Superseded by ../../../release-evidence-v1.0.0-rc1.md

# Phase 1 Evidence

Generated: 2026-05-15

## Tool Availability in Build Sandbox

The package includes CI workflows for Arduino Lint and AVR compile smoke tests. The local artifact-generation sandbox did not have `arduino-cli` or `arduino-lint` installed, and outbound network installation was unavailable. Therefore official Arduino compile/lint evidence is prepared in CI form and marked as not run locally in this evidence file.

| Gate | Status | Evidence |
|---|---|---|
| Arduino Lint strict | NOT RUN LOCALLY | `.github/workflows/lint.yml` uses `arduino/arduino-lint-action@v2` with `library-manager: submit` and `compliance: strict`. |
| AVR UNO compile | NOT RUN LOCALLY | `.github/workflows/compile-avr.yml` runs `arduino-cli compile --fqbn arduino:avr:uno` for all examples. |
| AVR Nano compile | NOT RUN LOCALLY | `.github/workflows/compile-avr.yml` runs `arduino-cli compile --fqbn arduino:avr:nano` for all examples. |
| BasicAdaptiveSensor compile | NOT RUN LOCALLY | Covered by AVR workflow. |
| BatteryBudgetReport compile | NOT RUN LOCALLY | Covered by AVR workflow. |
| PowerDoctorDiagnostics compile | NOT RUN LOCALLY | Covered by AVR workflow. |
| UltraLowPowerAVRNode compile | NOT RUN LOCALLY | Covered by AVR workflow. |
| No mandatory external dependency | PASS | Core uses Arduino API only; no RadioLib/TFLM/Wi-Fi/BLE dependency. |
| No hardware test performed | NOT TESTED | Owner-side only. |

## Local Syntax Smoke Test

A host-side C++ syntax smoke test with a small mock `Arduino.h` was run to catch obvious C++ errors. This is not a replacement for Arduino CLI or hardware validation.

| Check | Status | Evidence |
|---|---|---|
| Host C++ syntax smoke | PASS | `g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc -c ...` passed for library sources and all examples with a mock Arduino API. |

## Local Validation Commands Actually Run

```sh
g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc -c /tmp/ecosense_mock/Arduino.cpp src/EcoSensePower.cpp src/core/*.cpp src/arch/generic/*.cpp src/arch/avr/*.cpp
for ino in examples/*/*.ino; do g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc -include Arduino.h -x c++ -c "$ino"; done
g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc /tmp/ecosense_patchA_test.cpp /tmp/ecosense_mock/Arduino.cpp src/EcoSensePower.cpp src/core/*.cpp src/arch/generic/*.cpp -o /tmp/ecosense_patchA_test
/tmp/ecosense_patchA_test
```

Result: PASS.

This host syntax smoke test does not replace `arduino-cli compile`, Arduino Lint, or real hardware current validation.


# Phase 1 Patch A Evidence

Generated: 2026-05-15

## Patch A Changes

| Required Fix | Status | Evidence |
|---|---|---|
| currentIntervalMs initialization/clamping | PASS | `minIntervalMs()` resets default/below-min current interval; `maxIntervalMs()` clamps; `initialIntervalMs()` added. |
| Invalid sensor config on registry full | PASS | `sensor()` returns invalid no-op config and sets `sensorRegistryFull_`; it no longer returns `configs_[0]`. |
| Priority scheduling | PASS | `findDueSensor()` selects highest priority among due sensors; equal priority uses earliest deadline. |
| Blocking loop behavior documented | PASS | README and `docs/api.md` state that `node.loop()` may block while sleeping and is not an RTOS/non-blocking scheduler. |
| Explicit includes | PASS | `EcoRuntime.cpp` includes `<string.h>` and `<math.h>`; `EcoTypes.h` includes `<stdio.h>`. |
| EnergyLedger header guard typo | PASS | Guard corrected to `ECOSENSE_CORE_ENERGYLEDGER_H`. |
| Min/max/current interval note | PASS | README, `docs/api.md`, and `BasicAdaptiveSensor` note deterministic interval behavior. |
| Soft daily budget enforcement | PASS | Approximate `maxDailyEnergy_mJ` soft enforcement pushes interval toward max and PowerDoctor reports the warning. |

## Patch A Gate Table

| Gate | Status | Evidence |
|---|---|---|
| Host C++ smoke compile | PASS | `g++ -std=c++11 -Wall -Wextra -pedantic` smoke passed for library sources and all examples with a mock Arduino API. |
| Patch A behavior smoke | PASS | Host executable asserted deterministic current interval, invalid registry config, priority scheduling, and budget soft-limit behavior. |
| arduino:avr:uno compile | NOT RUN LOCALLY | `arduino-cli` not installed in sandbox; `.github/workflows/compile-avr.yml` covers UNO. |
| arduino:avr:nano compile | NOT RUN LOCALLY | `arduino-cli` not installed in sandbox; `.github/workflows/compile-avr.yml` covers Nano. |
| Arduino Lint strict | NOT RUN LOCALLY | `arduino-lint` not installed in sandbox; `.github/workflows/lint.yml` uses Library Manager submit + strict compliance. |
| BasicAdaptiveSensor compile | PASS HOST / CI PENDING | Host mock compile passed; Arduino CLI pending. |
| BatteryBudgetReport compile | PASS HOST / CI PENDING | Host mock compile passed; Arduino CLI pending. |
| PowerDoctorDiagnostics compile | PASS HOST / CI PENDING | Host mock compile passed; Arduino CLI pending. |
| UltraLowPowerAVRNode compile | PASS HOST / CI PENDING | Host mock compile passed; Arduino CLI pending. |
| No mandatory external dependency | PASS | No RadioLib, TFLM, Wi-Fi, BLE, or sensor-driver dependency in core. |
| No .development, .exe, symlink, build junk | PASS | Checked during package creation. |
| No hardware test performed | NOT TESTED | Owner-side only. |

## Patch A Local Validation Commands Actually Run

```sh
g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc -c /tmp/ecosense_mock/Arduino.cpp src/EcoSensePower.cpp src/core/*.cpp src/arch/generic/*.cpp src/arch/avr/*.cpp
for ino in examples/*/*.ino; do g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc -include Arduino.h -x c++ -c "$ino"; done
g++ -std=c++11 -Wall -Wextra -pedantic -I/tmp/ecosense_mock -Isrc /tmp/ecosense_patchA_test.cpp /tmp/ecosense_mock/Arduino.cpp src/EcoSensePower.cpp src/core/*.cpp src/arch/generic/*.cpp -o /tmp/ecosense_patchA_test
/tmp/ecosense_patchA_test
```

Result: PASS.

Official Arduino CLI/Lint must still be run in GitHub Actions or a local machine with those tools installed.

## Post-Patch Review Polish

Generated: 2026-05-15

| Check | Status | Evidence |
|---|---|---|
| Version metadata consistency | PASS | Documentation references updated to match `library.properties` version `0.1.1`. |
| Workflow checkout action freshness | PASS | CI workflows use `actions/checkout@v6` with read-only repository permission. |
| Re-review host smoke | PASS | Generic sources, AVR backend syntax, examples, and Patch A behavior smoke passed again under mock Arduino API. |

