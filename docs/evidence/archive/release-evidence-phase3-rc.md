Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 3.1 RC Evidence

Package: `EcoSensePower-Arduino-phase3-rc.zip`  
Library version: `0.3.1`  
Status: Phase 3.1 release-candidate polish package built in sandbox.

| Gate | Status | Evidence |
|---|---|---|
| No guard double-wake behavior | PASS | Idle backend-sleep path no longer calls `runGuardsWake()`; guard wake runs in `processSensor()` when a sensor is due. Host behavior smoke passed. |
| Post-processing nextDueMs | PASS | `slot.nextDueMs = EcoTime::nowMs() + slot.contract.currentIntervalMs;` in `processSensor()`. |
| Time helpers | PASS | `EcoTime::seconds()`, `EcoTime::minutes()`, and `EcoTime::hours()` added. |
| Beginner Quick Start | PASS | README starts with a short single-sensor example; guard/battery/diagnostics moved to Advanced Example. |
| Examples updated | PASS | Examples use `EcoTime` helpers where appropriate; BasicAdaptiveSensor no longer duplicates guard and sensor warmup. |
| PowerDoctor warning polish | PASS | Missing sleep hook warning now says: `has no sensor-specific onSleep callback; separate guards may still be configured.` |
| API docs cleanup | PASS | `docs/api-draft.md` renamed to `docs/api-freeze-candidate.md`; `docs/api.md` remains the primary API reference. |
| CONTRIBUTING.md present | PASS | Includes BoardProfile, BatteryProfile, Guard, measurement evidence, and no-copy/license policy. |
| Issue templates present | PASS | Bug report, board profile request, and feature request templates added. |
| Harvester interface | PASS | `src/harvester/HarvesterBase.h`, `docs/harvesting-interface.md`, and `EnergyHarvestingInterfaceDemo` added as interface-only; no mandatory dependency. |
| Arduino Lint strict | CI CONFIGURED / NOT RUN LOCALLY | `.github/workflows/lint.yml` uses `arduino/arduino-lint-action@v2` with `library-manager: submit` and `compliance: strict`; sandbox has no `arduino-lint`. |
| AVR UNO compile | CI CONFIGURED / HOST MOCK PASS | AVR workflow targets `arduino:avr:uno`; host AVR mock compile passed. |
| AVR Nano compile | CI CONFIGURED / HOST MOCK PASS | AVR workflow targets `arduino:avr:nano`; host AVR mock compile passed. |
| ESP32 compile | CI CONFIGURED / HOST MOCK PASS | Compile matrix targets `esp32:esp32:esp32`; host ESP32 mock compile passed. |
| SAMD compile | CI CONFIGURED / HOST MOCK PASS | Compile matrix targets `arduino:samd:arduino_zero_edbg`; host SAMD mock compile passed. |
| nRF52/RP2040 placeholder compile | HOST MOCK PASS | Host mock compile passed with `ARDUINO_ARCH_NRF52` and `ARDUINO_ARCH_RP2040`. |
| All examples host compile | PASS | All examples, including `EnergyHarvestingInterfaceDemo`, compiled with mock Arduino API. |
| Library Manager hard rules | PASS / CI PENDING | `library.properties`, SemVer version, `includes`, no forbidden files, no mandatory dependencies; real Arduino Lint output pending. |
| No mandatory dependencies | PASS | `depends=` is empty; no RadioLib/WiFi/BLE/TFLM/harvesting dependency in core. |
| No hidden files/build junk | PASS | No `.development`, `.exe`, symlink, `.pio`, `__MACOSX`, or `.DS_Store` in package tree. |
| No hardware measurement claims | PASS | No real current measurement claimed. |
| Battery lifetime guarantee | NOT CLAIMED | Battery-life claims require owner-side validation. |

## Local host compile summary

The sandbox has no `arduino-cli` or `arduino-lint`, so real Arduino evidence remains pending. The following host checks passed with a local Arduino mock:

```bash
# Generic host compile
find src -name '*.cpp'
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -c <all sources>
g++ -std=c++11 -Wall -Wextra -Werror -I mock -I src -x c++ -c examples/*/*.ino

# Architecture smoke modes
g++ ... -DARDUINO_ARCH_AVR
g++ ... -DARDUINO_ARCH_AVR -DECOSENSE_AVR_ENABLE_POWERDOWN
g++ ... -DARDUINO_ARCH_ESP32
g++ ... -DARDUINO_ARCH_SAMD
g++ ... -DARDUINO_ARCH_NRF52
g++ ... -DARDUINO_ARCH_RP2040
```

## Real CI requirement before public release

Public release remains `NOT APPROVED` until real GitHub Actions or local tool output confirms:

- Arduino Lint strict PASS.
- AVR UNO compile PASS.
- AVR Nano compile PASS.
- ESP32 compile PASS or documented pending.
- SAMD compile PASS or documented pending.
- All examples compile or unsupported-target examples are guarded/documented.

## Superseded by Phase 3.1 Industrial RC

This RC polish package has been superseded by `release-evidence-phase3.1-rc.md` and version `0.3.2`, which adds machine-readable diagnostics, profile confidence, and host logic tests.
