# EcoSensePower pre-v1.0.0-rc1 Evidence

> Pre-RC note: this file is evidence for a pre-v1.0.0-rc1 package only. It is not a final RC tag or Arduino Library Manager-ready claim. Real Arduino Lint strict and board compile evidence remain pending until GitHub Actions or owner-side CLI output proves them.

## Status

EcoSensePower is a pre-v1.0.0-rc1 candidate pending real Arduino ecosystem evidence.

Phase 4.4.11 is a tiny final public polish patch over Phase 4.4.10. It preserves the AVR Tiny/Core mode defaults and feature gates so UNO/Nano prove the compact core runtime instead of the full ecosystem catalog. It preserves the practical Arduino/IoT profile coverage, including Bluetooth/BLE and GPS/GNSS energy profiles and usability helpers, while keeping all new values confidence-bounded: `measured=false`, `EcoProfileConfidence::PLACEHOLDER`, no battery-life guarantee, and no mandatory RadioLib/WiFi/BLE/TinyML dependency.

Current package: Phase 4.4.11 Tiny Final Public Polish / `library.properties` version `0.9.10`.

## Evidence Table

| Gate | Status | Evidence |
|---|---|---|
| AVR Tiny/Core architecture | PASS | Added central `EcoSensePowerConfig.h`, AVR Tiny defaults, compact `EcoReport::toText(buffer, size)`, zero-default diagnostics storage, compact ledger aggregate mode, optional `EcoSensePowerProfiles.h`, and UNO/Nano-scoped compile gates. |
| Host tests | PASS | `extras/tests/run_host_tests.sh` completed successfully in the packaging sandbox with 31 host test sources, including MeasuredProfileBuilder and direct public profile constructor consistency. |
| Example mock compile | PASS | `extras/tests/run_example_mock_compile.sh` compiled all `src/**/*.cpp` sources with `-Werror`, then syntax-checked all 27 shipped examples in both combined smoke mode and individual wrapper mode. |
| Header self-containment | PASS | `extras/tests/run_header_self_containment.sh` syntax-checks public `src/**/*.h` headers together in one host translation unit and through individual header wrapper checks against the Arduino mock layer. |
| Bluetooth/BLE + GPS/GNSS profile coverage | PASS | Added profile-only Bluetooth Classic, BLE, board-integrated BLE, UART bridge, GPS/GNSS, u-blox, Quectel, SIMCom, MTK/Adafruit, ATGM/CASIC, Beitian, active antenna, and generic profile headers. No protocol-stack dependency was added. |
| Profile catalog coverage | PASS | `test_profile_catalog.cpp` includes every battery, board, sensor, and radio profile header and validates non-null names/notes, placeholder confidence, `measured=false`, canonical Li-ion 18650 chemistry, backward-compatible 18650 aliasing, known battery chemistry, and sane radio currents. |
| MeasuredProfileBuilder confidence consistency | PASS | `test_measured_profile_builder.cpp` verifies conservative aggregation across active/sleep/sensor-read/process current fields so `BoardProfile.confidence` and `BoardProfile.measured` do not contradict each other. |
| Direct profile constructor consistency | PASS | `test_direct_profile_consistency.cpp` verifies that direct `BoardProfile`, `BatteryProfile`, and `EcoSensorProfile` constructors cannot produce `measured=false` with `confidence=MEASURED`, and that `measured=true` normalizes to `confidence=MEASURED`. |
| New profile confidence policy | PASS | Ecosystem profiles default to `measured=false` and `EcoProfileConfidence::PLACEHOLDER` unless evidence is explicitly attached. |
| Arduino Lint strict | PENDING | Run or attach workflow output for `arduino-lint --library-manager submit --compliance strict .`. |
| AVR UNO compile | PENDING | Run or attach workflow output for the verified examples on `arduino:avr:uno`. |
| AVR Nano compile | PENDING | Run or attach workflow output for the verified examples on `arduino:avr:nano`. |
| ESP32 compile | PENDING | Run or attach workflow output for `esp32:esp32:esp32`, or document pending status. |
| SAMD compile | PENDING | Run or attach workflow output for `arduino:samd:arduino_zero_edbg`, or document pending status. |
| No mandatory heavy dependencies | PASS | `library.properties` has no `depends=` field; core remains dependency-light. |
| Package hygiene | PASS | Generated host-test and example-mock build outputs are kept out of the release ZIP by `.gitignore`, script cleanup, and clean packaging. |
| Documentation / evidence alignment | PASS | `README.md`, `docs/release-status.md`, `CHANGELOG.md`, docs profile catalog/confidence policy, and this evidence file align on Phase 4.4.11 / version `0.9.10`. |
| Documentation usability polish | PASS | Added top-of-file comments to all examples, Bluetooth/GPS profile headers, optional subcatalogs, and optional adapter headers; README now includes an Energy Profiles vs Optional Drivers/Parsers table and matches AVR smoke workflow scope. |
| Library Manager structure prepared / promotion gates pending | PENDING | Structure, metadata, examples, and workflows are prepared. Final Library Manager readiness remains blocked until Arduino Lint strict and real board compile evidence pass. |
| Library Manager-ready claim | NOT CLAIMED UNTIL PASS | Public wording remains gated on real Arduino Lint strict and board compile evidence. |
| Battery life guarantee | NOT CLAIMED | README/docs keep battery-life behavior estimate/confidence based. |
| Hardware measurement claim | NOT CLAIMED | Real current/battery-life claims remain owner-side measurement requirements. |

## Ecosystem Coverage QA Note

Phase 4.4.11 keeps the AVR Tiny/Core architecture fix, preserves direct-constructor confidence consistency, keeps AVR-hostile float printf formatting out of EcoReport::toText(), preserves dependency-free Bluetooth/BLE and GPS/GNSS profile coverage, and applies only final public-facing polish before real CI. The direct AVR workflow now compiles a minimum smoke set as separate matrix jobs with `arduino-cli compile --warnings all --verbose`, environment diagnostics, and `--show-properties` output for the first smoke example. Heavy/demo examples remain in the project but are not treated as mandatory UNO/Nano smoke gates until the core compile gate is green. It does not add a new feature phase, redesign the runtime, shrink ecosystem coverage, or add mandatory dependencies.

After this phase is pushed, rerun GitHub Actions. Arduino Lint strict has previously passed in the public repo, but AVR UNO/Nano and matrix compile results must be attached as real CI evidence before RC tagging or Library Manager submission.


## AVR UNO/Nano Core Gate Policy

| AVR Gate | Status | Notes |
|---|---|---|
| BasicAdaptiveSensor on UNO/Nano | PENDING REAL CI | Required compact core gate. |
| UltraLowPowerAVRNode on UNO/Nano | PENDING REAL CI | Required compact core gate. |
| PowerDoctorDiagnostics on UNO/Nano | NON-GATING / OPTIONAL | Diagnostics storage is disabled by default in AVR Tiny mode; this example is not a blocker for UNO/Nano. |
| Profile-heavy examples on UNO/Nano | NON-GATING | Intended for Mega/ESP32/SAMD or mock/extended compile validation. |
| Bluetooth/GPS examples on UNO/Nano | NON-GATING | Dependency-free by default, but excluded from the minimum AVR smoke gate to protect compact core support. |

AVR SRAM policy: PASS <= 1700 bytes global SRAM, WARNING 1701-1900 bytes, FAIL > 1900 bytes. Do not claim full-feature UNO/Nano support; claim compact core support only after real CI passes.

## Host Test Output Summary

```text
[EcoSensePower host test] build test_bluetooth_profiles
[EcoSensePower host test] build test_gps_profiles
[EcoSensePower host test] build test_wireless_profile_catalog
[EcoSensePower host test] build test_optional_dependency_guards
[EcoSensePower host test] build test_profile_catalog
[EcoSensePower host test] build test_direct_profile_consistency
[EcoSensePower host test] build test_measured_profile_builder
[EcoSensePower host test] build test_battery_chemistry
[EcoSensePower host test] build test_radio_profiles
[EcoSensePower host test] build test_harvester_profiles
[EcoSensePower host test] build test_voltage_divider
[EcoSensePower host test] build test_ecotime_utilities
[EcoSensePower host test] build test_priority_conflicts
...
[EcoSensePower host test] run test_direct_profile_consistency
[EcoSensePower host test] run test_measured_profile_builder
[EcoSensePower host test] run test_radio_profiles
[EcoSensePower host test] run test_soc_tracker
[EcoSensePower host test] run test_voltage_divider
[EcoSensePower host test] PASS
```

## Example Mock Compile Output Summary

```text
[EcoSensePower example mock] CXXFLAGS include -Wall -Wextra -Werror
[EcoSensePower example mock] build common src/**/*.cpp
[EcoSensePower example mock] build ProfileGallery
[EcoSensePower example mock] build SolarPoweredWeatherStation
[EcoSensePower example mock] build GSMIndustrialAlert
[EcoSensePower example mock] build MultiSensorLowPower
[EcoSensePower example mock] build WatchdogDeepSleep
[EcoSensePower example mock] individual wrapper syntax-check
[EcoSensePower example mock] syntax-check individual ProfileGallery
...
[EcoSensePower example mock] PASS
```

## Header Self-Containment Output Summary

```text
[EcoSensePower header self-containment] checked 178 headers in aggregate plus critical public/optional/profile headers individually
[EcoSensePower header self-containment] PASS
```

## Promotion Rule

Do not tag `v1.0.0-rc1` and do not submit to Arduino Library Manager until:

- Arduino Lint strict PASS
- AVR UNO compile PASS
- AVR Nano compile PASS
- README/docs/package version consistency PASS
- Public docs continue to avoid battery-life guarantees, measured-accuracy claims, and universal-board claims


## Phase 4.4.8 AVR SRAM architecture note

`EcoReport::toText()` still avoids `%f` / `%g` formatted I/O. AVR Tiny mode now also offers `toText(buffer, size)` and a compact default text path, with no per-report text buffer in the `EcoReport` object. Arduino Lint and real board compile evidence remain promotion gates.

## Bluetooth/BLE and GPS/GNSS Claim Policy

Bluetooth/BLE profiles are energy models, not Bluetooth protocol stacks. GPS/GNSS profiles are energy models, not parsers, navigation frameworks, accuracy guarantees, fix-time guarantees, or battery-life guarantees. ArduinoBLE, TinyGPSPlus, Adafruit_GPS, ESP32 BLE/NimBLE, WiFi, and parser/protocol libraries remain optional user-side integrations.

## Phase 4.4.11 Coverage Counts

- Host test sources: 31
- Examples: 27
- Public/source headers: 178
- Profile headers: 127
- Bluetooth/BLE profile headers: 41
- GPS/GNSS profile headers: 42

## Phase 4.4.11 Local Packaging Evidence

- `extras/tests/run_host_tests.sh`: PASS in packaging sandbox after parallelizing compile steps for the expanded test set.
- `extras/tests/run_example_mock_compile.sh`: PASS for all 27 examples, including the new Bluetooth/GPS examples.
- `extras/tests/run_header_self_containment.sh`: PASS using an aggregate check over all 178 source headers plus individual checks for core public headers, subcatalogs, representative Bluetooth/GPS profile headers, and optional adapter headers.
- `extras/tests/clean.sh`: PASS and removes generated build folders.

Arduino Lint and real UNO/Nano/ESP32/SAMD board compile remain PENDING until GitHub Actions or owner-side Arduino CLI evidence is attached.
