# Changelog

## 0.9.10 - Phase 4.4.11 Tiny Final Public Polish

- Replaced remaining AVR-facing raw Serial string literals with `F()` in `WatchdogDeepSleep` and `ProfileGallery` where safe.
- Cleaned the public changelog ordering so newest package notes appear under a single `# Changelog` heading.
- Kept the pre-v1.0.0-rc1 evidence filename but added an explicit pre-RC note so it cannot be mistaken for a final RC tag or Library Manager-ready claim.
- Preserved the Phase 4.4.9 Bluetooth/BLE and GPS/GNSS coverage, Phase 4.4.8 AVR Tiny/Core architecture, optional adapters, and dependency-free default build.

## 0.9.9 - Phase 4.4.10 Final Public README/Example Usability Polish

- Added user-facing top-of-file comments to all examples to clarify energy profile/model scope, optional dependencies, and AVR Tiny/Core expectations.
- Added top-of-file comments to Bluetooth/BLE and GPS/GNSS profile headers, optional profile subcatalogs, and optional adapter headers.
- Added README table for Energy Profiles vs Optional Drivers / Parsers with ArduinoBLE, TinyGPSPlus, Adafruit GPS, and ESP32 WiFi guidance.
- Updated Library Manager-facing metadata paragraph without adding mandatory dependencies.
- Synced README compile matrix wording with AVR UNO/Nano smoke workflow scope.
- Kept Bluetooth/GPS coverage, AVR Tiny/Core defaults, and dependency-free examples intact.

## 0.9.8 - Phase 4.4.9 Complete Wireless/GPS AVR-safe Coverage

- Added dependency-free Bluetooth Classic, BLE, UART bridge, board-integrated BLE, and external Bluetooth module energy profile headers.
- Added dependency-free GPS/GNSS high-energy peripheral profiles for generic modules, u-blox, Quectel, SIMCom, MTK/Adafruit, ATGM/CASIC, Beitian, active antenna, UART, I2C, and multi-constellation variants.
- Added optional subcatalog headers `EcoSensePowerBluetoothProfiles.h` and `EcoSensePowerGPSProfiles.h` while keeping `EcoSensePower.h` core-only.
- Added dependency-free Bluetooth/GPS budget examples that are excluded from the AVR UNO/Nano smoke gate.
- Added guarded optional adapter headers for ArduinoBLE, TinyGPSPlus, and Adafruit_GPS without adding mandatory dependencies.
- Kept AVR Tiny/Core mode defaults intact and made `UltraLowPowerAVRNode` explicitly opt into one guard.
- Updated docs, CI matrix, tests, and evidence for Bluetooth/BLE plus GPS/GNSS energy-model coverage.

## 0.9.7 - Phase 4.4.8 AVR SRAM Architecture Hardening

- Added central `EcoSensePowerConfig.h` compile-time configuration.
- Added AVR Tiny/Core defaults for UNO/Nano-class boards.
- Added compact `EcoReport::toText(char*, size_t)` and removed the per-report text buffer from AVR Tiny mode.
- Made full ledger record/state arrays, diagnostics storage, SoC tracker storage, and guard arrays optional by feature gates.
- Added optional `EcoSensePowerProfiles.h` profile-catalog convenience header.
- Split AVR core compile gating away from profile-heavy extended examples.
- Updated README, supported-board docs, and release evidence for compact UNO/Nano support without claiming full-feature AVR support.

## 0.9.6 - pre-v1.0.0-RC evidence polish

### Phase 4.4.7 AVR Report Formatting + README Visual Polish
- Replaced float printf formatting in `EcoReport::toText()` with AVR-safe fixed-decimal string formatting.
- Added host coverage for report text formatting so `%f` / `%g` do not re-enter the public report path.
- Improved README presentation with status badges and a runtime map while keeping all promotion gates honest.
- Kept Arduino Lint and real board compile evidence as pending until GitHub Actions or owner-side CLI output proves them.

## 0.9.6 - Pre-RC Evidence Polish

### Phase 4.4.6 Real Arduino CI Failure Diagnosis + Compile Gate Fix

- Added AVR-specific compact default buffer sizing for UNO/Nano SRAM-limited builds while preserving larger defaults on non-AVR targets and user macro override support.
- Hardened the direct AVR workflow with per-example labels plus `--warnings all --verbose` so real Arduino compiler failures are debuggable in GitHub Actions.
- Kept Arduino Lint and real board compile evidence as promotion gates; no Library Manager-ready claim is made before CI evidence.

### Phase 4.4.5 Direct Profile Consistency + Final Pre-RC Polish

- Normalized direct `BoardProfile`, `BatteryProfile`, and `EcoSensorProfile` constructors so public profile objects cannot end up with `measured=false` and `EcoProfileConfidence::MEASURED`.
- Added direct-constructor host tests covering false+MEASURED degradation and true+PLACEHOLDER/DATASHEET normalization to MEASURED.
- Kept the Phase 4.4.4 `MeasuredProfileBuilder` conservative aggregation behavior intact.
- Kept Arduino Lint and real board compile evidence as PENDING until owner/CI output exists.

- Fixed `MeasuredProfileBuilder` confidence aggregation so board profile `confidence` and `measured` cannot contradict each other when current fields mix PLACEHOLDER, DATASHEET, and MEASURED evidence levels.
- Made `ProfileConfidenceReport` safe by default: illustrative values remain PLACEHOLDER unless `ECOSENSE_EXAMPLE_USE_OWNER_MEASURED_VALUES` is explicitly defined with owner-side measurement evidence.
- Strengthened release hygiene: `extras/tests/clean.sh` removes generated host, example, and header build folders.
- Strengthened header self-containment evidence with combined aggregate and individual header wrapper syntax-checks.
- Aligned README compile-matrix wording with the configured GitHub Actions matrix.
- Kept Arduino Lint and real board compile evidence as PENDING until owner/CI output exists.

### Phase 4.4.3 Pre-RC Documentation Polish

- Final public docs/evidence/usability polish before owner-side Arduino promotion evidence.
- Updated harvesting documentation to describe Solar, Piezo, Thermoelectric, and Wind model helpers without implying hardware drivers.
- Changed public examples/docs to use PLACEHOLDER confidence unless values have named/cited datasheet evidence.
- Removed unnecessary phase wording from README/API/profile docs.
- Added header self-containment check for public `src/**/*.h` headers.
- Kept Arduino Lint and real board compile evidence as PENDING until owner/CI output exists.

### Phase 4.4.2 Naming & Release-Gate Polish

- Canonicalized 18650 battery naming around `ECO_BATTERY_LIION_18650` and `profiles/batteries/liion_18650.h`, while keeping `ECO_BATTERY_LIPO_18650` and `lipo_18650.h` as compatibility aliases before v1.0.
- Tightened Library Manager wording to “structure prepared / promotion gates pending” so the package does not imply Library Manager-ready status before Arduino Lint strict and real board compile evidence.
- Split README compile matrix columns for AVR, ESP32, and SAMD so ESP32-specific examples are not implied to be SAMD-verified.
- Added explicit SolarHarvester coverage to harvester profile tests, including default confidence, availability, fixed input power, storage-efficiency clamping, and notes.
- Hardened example mock compile evidence with individual example wrapper syntax-checks in addition to the combined smoke wrapper and `src/**/*.cpp` compilation.
- Added `extras/tests/clean.sh` for release-package cleanup before ZIP creation.
- Kept `actions/checkout@v6`, version `0.9.6`, and all Arduino promotion gates conservative: no Library Manager-ready claim and no battery-life guarantee.

### Phase 4.4.1 Ecosystem Coverage QA Fix

- Expanded `test_profile_catalog.cpp` so every battery, board, sensor, and radio profile header is included and validated for non-null names/notes, `measured=false`, `EcoProfileConfidence::PLACEHOLDER`, known battery chemistry, and sane radio current values.
- Added `EcoProfiles` namespace aliases for legacy `NiMH_AA` and `LiSOCl2_AA` battery profiles while preserving the older `EcoBatteryProfiles` namespace for backward compatibility.
- Removed phase-heavy wording from public docs while keeping release history in CHANGELOG/evidence.
- Updated release evidence and release-status wording to reflect the QA-fixed ecosystem package without claiming Arduino Library Manager readiness or hardware measurement evidence.
- Kept `library.properties` at `version=0.9.6`; no `v1.0.0-rc1` tag or Library Manager-ready claim is made until real Arduino Lint and board compile evidence pass.

### Internal package note - Phase 4.4 Ecosystem Coverage & Usability Expansion

- Added broad placeholder profile coverage for common Arduino/IoT batteries, boards, sensors, radios, and harvesters while keeping the core dependency-light and Arduino Library Manager-prepared, not Library Manager-ready.
- Added battery profiles for LiPo 2S, LiPo 1S 400mAh, CR2032, CR123A, D alkaline, Li-ion 18650, LiPo 2S 2000mAh, NiMH AAA, and LiFePO4 1S.
- Expanded battery chemistry metadata and SoC warnings for flat-discharge chemistries, pulse-load limitations, and lithium protection/charger/regulator caveats.
- Added board profiles for Arduino Nano, Pro Mini 3.3V/5V, ESP32 DevKit, ESP32-WROOM, ESP8266 NodeMCU, ATtiny85, Arduino Mega, Nano Every, MKR WAN, and Raspberry Pi Pico/RP2040 placeholder.
- Added `EcoSensorProfile` and named sensor profiles for DHT22, DS18B20, BME280, HC-SR04, resistive soil probe, generic PIR, MPU6050, INA219, SCD30, and analog LDR divider.
- Added dependency-free radio energy profiles for SX1276 LoRa, RFM95W, nRF24L01, HC-12, SIM800L, and ESP8266 WiFi using `GenericRadioProfile`.
- Added `PiezoHarvester`, `ThermoelectricHarvester`, and `WindHarvester` alongside `SolarHarvester` with placeholder confidence and storage-efficiency modeling.
- Added `VoltageDivider`, `EcoTime::days()`, `EcoTime::fromHz()`, `EcoTime::toHz()`, and optional AVR `WatchdogSleepHelper::sleepForApprox()`.
- Added optional energy-window budget metadata through `EnergyContract` / `EcoSensorConfig` and new PowerDoctor diagnostics for radio burst current, flat-curve SoC confidence, battery pulse/protection caveats, energy-window budgets, and sensor priority conflicts.
- Added dependency-free examples: `ProfileGallery`, `SolarPoweredWeatherStation`, `GSMIndustrialAlert`, `MultiSensorLowPower`, and `WatchdogDeepSleep`.
- Added profile catalog/confidence docs and host tests for profile catalog, battery chemistry, radio profiles, harvesters, voltage divider, EcoTime utilities, and priority-conflict diagnostics.
- Kept all new ecosystem values honest: `measured=false`, `EcoProfileConfidence::PLACEHOLDER` unless documented measurement evidence exists, no battery-life guarantee, and no mandatory RadioLib/WiFi/BLE/TinyML dependency.

## 0.9.5 - Phase 4.3.7 Final Public Text Polish (pre-v1.0.0-rc1)

- Accepted Phase 4.3.6 as the final pre-RC evidence-aligned package and kept this phase limited to final public text polish plus real Arduino evidence gating.
- Renamed the root evidence title to `pre-v1.0.0-rc1 Evidence` while keeping `library.properties` at `version=0.9.5` until Arduino Lint strict and board compile evidence pass.
- Kept `actions/checkout@v6` in workflows; fallback to v4 remains a repository-specific response only if real CI execution fails.
- Aligned RadioLib documentation with the optional guarded `RadioLibEnergyAdapter` stub and clarified that RadioLib is not a mandatory core dependency.
- Tightened README architecture wording around AVR/ESP32 sleep backends and guarded compile-readiness paths for selected Arduino ARM boards.
- Removed phase-heavy wording from Power Doctor docs and merged duplicate Issue Templates guidance in CONTRIBUTING.
- Made host tests clean previous `bin/` and `obj/` outputs before building and made the example mock compile script echo the evidence-summary lines it reports.
- Preserved the Library Manager gate: no `v1.0.0-rc1` tag, no Library Manager-ready claim, and no battery-life guarantee until real Arduino evidence is attached.
- Completed final `keywords.txt` Arduino IDE polish for generic and guarded ARM sleep backend symbols.

## 0.9.5 - Phase 4.3.6 Final RC Evidence Alignment (pre-v1.0.0-rc1)

- Kept the package at `version=0.9.5` and aligned public docs around Phase 4.3.6 Final RC Evidence Alignment while leaving v1.0.0-RC promotion blocked on real Arduino Lint and board compile evidence.
- Clarified version/tag rules: do not tag `v1.0.0-rc1` while `library.properties` still says `0.9.5`; prepare a separate candidate package after real evidence passes.
- Hardened example mock compile evidence with `-Werror` and automatic compilation of all `src/**/*.cpp` sources.
- Tightened `library.properties` and GitHub About wording to distinguish AVR/ESP32 runtime backends from guarded ARM compile-readiness paths.
- Documented `EcoSensePower::runtime()` as an advanced/internal escape hatch rather than a normal beginner API.
- Fixed archived evidence supersession paths and replaced informal stale-package wording with professional historical evidence wording.
- Added repeatable `extras/tests/run_example_mock_compile.sh` coverage for every shipped example against the mock Arduino layer.
- Hardened GitHub Actions by adding the example mock compile to host tests and making raw Arduino CLI compile commands use `--library .`.
- Expanded AVR compile workflow coverage to all dependency-free public examples and clarified compile evidence versus target compatibility in README.
- Fixed `diagnosticsTruncated()` to collect a current diagnostic snapshot instead of returning stale previous PowerDoctor state.
- Split generic-board fallback from placeholder board-profile confidence with `BOARD_PROFILE_PLACEHOLDER` to avoid duplicate `GENERIC_BOARD_PROFILE` diagnostics.
- Documented the energy-model voltage/current measurement boundary without changing the public API.
- Moved README License to the final section, synchronized the examples list with the actual `examples/` folder, updated issue-template version placeholders, and removed empty `depends=` metadata.

## 0.9.5 internal package note - Phase 4.3.4 Clean Evidence Package (superseded by current 0.9.6)

- Locked the package as a strong v1.0.0-RC candidate while keeping `library.properties` at `version=0.9.5` until real Arduino ecosystem evidence passes.
- Updated GitHub Actions workflows for Arduino Lint strict, AVR UNO/Nano compile, optional cross-board compile matrix, and host logic tests with read-only workflow permissions.
- Replaced scattered root evidence files with `release-evidence-v1.0.0-rc1.md` as the single current root evidence file and archived superseded phase evidence under `docs/evidence/archive/`.
- Updated `docs/library-manager-checklist.md` and release status wording to match the current `0.9.5` pre-v1.0.0-rc1 package boundary.
- Preserved the confident public README positioning while keeping Arduino Library Manager readiness, battery-life, hardware-measurement, and energy-neutral claims gated on real evidence.
- Replaced low-confidence SoC phrasing with confidence-bounded scientific language.

## 0.9.4 - Phase 4.3.1 Release Gate Patch (pre-v1.0.0-rc1)

- Credits harvested energy to SoC using usable/stored energy after efficiency, not raw input power.
- Populates `EcoPowerReport::diagnosticsTruncated` in the public wrapper from a PowerDoctor snapshot.
- Clears stale `INFERENCE_SKIPPED_ENERGY_DEFICIT` per processing cycle.
- Clarifies RadioBatcher as AVR-safe aggregate batching and updates keywords/docs for Phase 4.3 public APIs.
- Adds release-gate tests for SoC credit efficiency, diagnostic truncation propagation, and recovered inference diagnostics.


## 0.9.3 - Phase 4.3 Final Industrial Polish (unreleased until real Arduino CI)

- Kept Phase 4.2 architecture and modules; no industrial feature was removed or downgraded.
- Made AVR timed `sleepFor(ms)` IDLE-based even when optional power-down is compiled; `powerDownOnce()` remains explicit and application-owned.
- Integrated `BatteryProfile::regulatorIq_uA` into current estimates when board profiles do not already include regulator IQ, with tests preventing double-counting.
- Added radio RX-window modeling, confirmed-uplink diagnostics, radio profile confidence through the base interface, and `RADIO_RX` ledger recording.
- Upgraded `RadioBatcher` from throttle-only behavior to a fixed-size aggregate summary with count/latest/min/max/timestamps for non-critical reports.
- Added harvesting storage-efficiency modeling so reports distinguish input energy from usable/stored energy.
- Added inference energy-deficit gating through `skipWhenEnergyDeficit()` and structured `INFERENCE_SKIPPED_ENERGY_DEFICIT` diagnostics.
- Added `printDiagnostics(out, minSeverity)` and documented `collectDiagnostics()` versus `collectDiagnosticsSnapshot()` semantics.
- Expanded `EcoPowerReport` with energy balance, radio/inference/sleep energy summaries, confidence fields, and usable harvested energy.
- Added Phase 4.3 host tests for power report underflow, diagnostics truncation, regulator IQ, radio RX window, batching aggregate behavior, harvesting efficiency, and inference energy-deficit gating.
- Public release remains blocked until real Arduino Lint strict and Arduino compile evidence are attached.


## 0.9.2 - Phase 4.2 Final Industrial Release Candidate (unreleased until real CI)

- Fixed `powerReport()` remaining-interval underflow when the next sensor deadline is due or already past.
- Added `EcoDiagnosticSnapshot` and `collectDiagnosticsSnapshot()` so caller-buffer truncation exposes copied, total, and truncated status.
- Reduced noisy runtime INFO diagnostics by making the static-name caution debug-only.
- Added optional custom SoC voltage curves and clarified Li-SOCl2 voltage-only estimates as very low confidence.
- Added `EcoEnergyBalance` with DEFICIT / NEUTRAL / SURPLUS / UNKNOWN and interval relaxation under sustained surplus.
- Added runtime payload-size estimator hook for radio energy modeling and removed the hidden hardcoded-only TX payload behavior.
- Integrated `RadioBatcher` with runtime reporting for non-critical reports while critical/anomaly reports bypass batching.
- Clarified TinyML inference-budget semantics as one inference-equivalent operation per callback using a rolling 24h `millis()` window.
- Added Phase 4.2 host tests for underflow, diagnostic truncation, SoC custom curve / flat chemistry confidence, energy deficit/surplus behavior, radio payload energy, batching, and inference window wrap-safety.
- Kept public Library Manager submission blocked until real Arduino Lint and Arduino compile evidence is attached.

## 0.9.1 - Phase 4.1 Final Industrial Fix (unreleased until real CI)

- Integrated Phase 4 modules into the runtime-facing API: `socTracker()`, `energyPolicy()`, `harvester()`, `radio()`, and `powerReport()`.
- Fixed SoCTracker behavior so unknown SoC does not report a fake 100%; added initial SoC and evidence flags.
- Replaced simple linear voltage estimates with conservative piecewise lookup curves and retained flat-discharge warnings.
- Connected energy-neutral policy to runtime interval stretching using harvested energy over the interval versus cycle cost.
- Added radio sleep current to the radio interface and recorded radio TX/sleep energy in the ledger when a radio adapter is configured.
- Recorded inference energy in the ledger with `EcoEnergyState::INFERENCE` and added a 24h inference run window.
- Expanded machine-readable diagnostics for SoC, harvesting, radio, inference, diagnostic truncation, and low-confidence estimates.
- Added `collectDiagnostics(buffer, maxCount)` for Arduino-friendly structured diagnostics without repeated per-index collection.
- Expanded host tests for SoC unknown state, energy income insufficiency, radio sleep current, inference limits, runtime integration, and diagnostic codes.
- Kept public release blocked until real Arduino Lint/CLI evidence is attached.

## 0.9.0 - Phase 4 Industrial Scientific Finalization (draft)

- Added SoCTracker Pro with voltage/coulomb hybrid estimates and chemistry warnings.
- Added EnergyBudgetManager and SolarHarvester for energy-neutral scheduling policies.
- Added GenericRadioProfile, RadioBatcher, and optional RadioLib adapter shim.
- Added TinyML/anomaly energy hooks without mandatory TFLM dependency.
- Added measured profile builder, calibration docs, measurement template, and expanded tests.
- Added multi-architecture placeholder backends for Renesas UNO R4 and STM32.
- Kept public release blocked until real Arduino Lint/CLI evidence is available.

## 0.3.2 - Phase 3.1 Industrial RC

- Added machine-readable `EcoDiagnosticCode` / `EcoDiagnostic` diagnostics alongside text output.
- Added `EcoProfileConfidence` and report/profile quality fields for measured/datasheet/placeholder estimates.
- Made guard lifecycle idempotent with internal guard awake state to prevent duplicate wake/sleep callbacks.
- Added host logic test harness under `extras/tests/` for contracts, adaptive sampling, ledger, diagnostics, and guard lifecycle.
- Added `AdvancedIndustrialNode` example while keeping beginner Quick Start simple.
- Updated evidence to separate host logic PASS from pending real Arduino Lint/CLI evidence.

## 0.3.1 - Phase 3.1 release-candidate polish

- Fixed guard double-wake risk by removing guard wake from the idle backend-sleep path; guard wake now runs when a due sensor is processed.
- Scheduled sensor `nextDueMs` from post-processing time.
- Added `EcoTime::seconds()`, `EcoTime::minutes()`, and `EcoTime::hours()` helpers.
- Simplified README Quick Start and moved battery/guard/diagnostics usage into an advanced example.
- Updated examples to use time helpers and avoid duplicate basic warmup.
- Clarified Power Doctor sensor-specific `onSleep()` warning.
- Renamed `docs/api-draft.md` to `docs/api-freeze-candidate.md`.
- Added `CONTRIBUTING.md` and issue templates.
- Added optional interface-only `HarvesterBase` and `EnergyHarvestingInterfaceDemo` without mandatory dependencies.
- Added Phase 3.1 RC evidence file while keeping real Arduino CLI/Lint status pending until actual CI output exists.

## 0.3.0 - Phase 3 release-hardening alpha

- Post-review documentation/evidence polish: README example list includes LoRaAdaptiveReporter and Phase 3 evidence records expanded mock compile coverage.

- Added Full Duty Cycle Ledger runtime semantics so sleep recorded before wake/sense/report remains in the same cycle.
- Added `EnergyLedger::cycleOpen()` for lightweight runtime cycle ownership.
- Documented static-lifetime requirements for sensor and guard names.
- Updated supported-board status and marked ESP32-C3/S3 experimental until separate evidence exists.
- Added Phase 3 API freeze candidate documentation.
- Added Phase 2 real-CI placeholder evidence and Phase 3 evidence table.
- Updated Library Manager checklist to version 0.3.0 and retained no-mandatory-dependency policy.

## 0.2.0 - Phase 2 alpha hardening

- Added AVR backend v2 with conservative idle sleep and optional power-down compile flag.
- Added AVR ADC disable/restore guard implementation.
- Added ESP32 backend v1 with light/deep sleep timer wake and wake-cause reporting.
- Added callback-based ESP32 wireless guard path without Wi-Fi/BLE dependencies.
- Added cycle-aware and lifetime Energy Ledger APIs.
- Added `RADIO_TX`, `RADIO_RX`, and `GUARD` energy states.
- Added Power Doctor v2 with diagnostic severity.
- Added public `node.guard()` API for callback and power-pin guards.
- Added generic RadioEnergyAdapter interface without mandatory RadioLib dependency.
- Added SAMD, nRF52, and RP2040 placeholder backend headers.
- Added Phase 2 examples and multi-architecture compile workflow.
- Updated documentation and evidence for Phase 2.

## 0.1.1 - Phase 1 Patch A reviewed

- Fixed interval initialization/clamping behavior.
- Added invalid sensor config for registry overflow.
- Added priority-aware scheduling and soft budget enforcement.
- Clarified blocking runtime behavior.

## 0.1.0 - Phase 1 alpha foundation

- Initial industrial alpha core with FSM, adaptive sampler, energy contract, ledger, Power Doctor, generic backend, AVR skeleton, docs, and examples.
