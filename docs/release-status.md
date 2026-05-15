# EcoSensePower release-candidate status

EcoSensePower is presented as a pre-v1.0.0-RC candidate package with completed host-side validation and configured Arduino ecosystem promotion gates. The current package version is `0.9.10` / Phase 4.4.11 Tiny Final Public Polish, built on the Phase 4.4.9 complete Bluetooth/BLE and GPS/GNSS energy-profile coverage patch, until real Arduino Lint strict and board compile evidence passes.

## Current status

| Area | Status | Notes |
|---|---|---|
| Host logic validation | PASS | `extras/tests/run_host_tests.sh` is included and expected to pass in a desktop C++ environment. |
| Example mock compilation | PASS | `extras/tests/run_example_mock_compile.sh` compiles all `src/**/*.cpp` sources with `-Werror`, then syntax-checks every shipped example in combined smoke mode and individual wrapper mode. |
| Architecture guard validation | PARTIAL | Guarded paths are covered by host validation, target-scoped compile configuration, and mock compilation; final architecture confidence still requires real board-FQBN compile output. |
| Arduino Lint strict | PENDING PROMOTION GATE | Workflow/configuration is included; real output is required before Arduino Library Manager submission. |
| Arduino board compile | PENDING PROMOTION GATE | AVR UNO/Nano compile output is required before public release tagging; ESP32/SAMD output should pass when possible or be documented pending. |

## Public positioning

EcoSensePower should be described as an industrial energy-aware runtime for battery-powered Arduino sensor nodes. Its Library Manager structure is prepared and promotion gates are pending, but it must not be described as Arduino Library Manager-ready until real Arduino Lint and board compile evidence are attached.

Recommended wording:

> Host-side validation is complete. Arduino ecosystem promotion is gated on real Arduino Lint and board compile output.

Avoid wording that suggests guaranteed battery life, perfect behavior on all Arduino boards, guaranteed energy-neutral operation, fuel-gauge-grade SoC accuracy, a full LoRaWAN stack, or a full TinyML framework.

## Promotion gates before v1.0.0-rc1

- Arduino Lint strict with Library Manager mode: `arduino-lint --library-manager submit --compliance strict .`
- AVR UNO compile evidence.
- AVR Nano compile evidence.
- ESP32 compile evidence or documented pending status.
- SAMD compile evidence or documented pending status.
- Host tests remain PASS.
- Example mock compile remains PASS.
- No mandatory heavy runtime dependencies.
- No battery-life guarantee or hardware measurement claim without owner-side measurement evidence.


## Version and tag clarity

Do not create a `v1.0.0-rc1` tag while `library.properties` still says a pre-RC `0.9.x` version. Use `pre-v1.0.0-rc1 candidate` wording until Arduino Lint strict and board compile evidence pass. After those gates pass, prepare a separate candidate package with matching metadata and tag/release naming.

## AVR UNO/Nano compact defaults

Phase 4.4.11 keeps the public API and ecosystem coverage intact while making the final public-facing polish pass: AVR-facing strings are flash-aware, the changelog is ordered, and pre-RC evidence wording stays explicit. The AVR workflow uses a minimum smoke gate first, with each example compiled in a separate labeled matrix job using verbose Arduino CLI output. Heavy demonstration examples remain available but are not treated as mandatory UNO/Nano smoke gates until core compatibility is green.


## Phase 4.4.8 AVR SRAM architecture note

`EcoReport::toText()` avoids `%f` / `%g` formatted I/O, and AVR Tiny mode can use `toText(buffer, size)` without storing a text buffer inside each report object. Arduino Lint and real board compile evidence remain promotion gates.
