Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 4.3.2 Public RC Positioning + Evidence Gate

This package focuses on public-facing release-candidate polish. It does not remove industrial modules and does not weaken the runtime architecture. It improves the first impression of the repository while keeping release evidence honest and promotion-gated.

## Validation summary

| Gate | Status | Evidence |
|---|---|---|
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` completed successfully in the package validation environment. |
| Example mock compile | PASS | All examples compile against the repository mock Arduino layer. |
| Architecture guard compile | PASS | Generic/AVR/ESP32/SAMD/nRF52/RP2040 guarded paths remain covered by host validation. |
| README public positioning | PASS | README now starts with product value and a short release-candidate status line. Detailed gate language moved to `docs/release-status.md`. |
| `keywords.txt` format | PASS | Malformed `EcoBatteryChemistry` / `socTracker` line fixed and Phase 4.x API symbols added. |
| Standard headers in examples | PASS | Examples using `strlen()` include `<string.h>` explicitly. |
| Public docs polish | PASS | Phase-heavy headings were replaced with stable, public-facing headings. |
| Arduino Lint strict | PENDING PROMOTION GATE | Workflow/configuration is present. Real Arduino Lint output is required before Arduino Library Manager submission. |
| Arduino board compile | PENDING PROMOTION GATE | AVR UNO/Nano compile evidence is required before public tagging; ESP32/SAMD should pass or be documented pending. |
| Battery-life guarantee | NOT CLAIMED | README keeps measurement and estimate boundaries clear. |
| Library Manager-ready claim | NOT CLAIMED | The project is Library Manager-prepared; final readiness waits for real Arduino promotion evidence. |

## Recommended public wording

Host-side validation is complete. Arduino ecosystem promotion is gated on real Arduino Lint and board compile output before Arduino Library Manager submission.

## Promotion commands

```bash
arduino-lint --library-manager submit --compliance strict .
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli compile --fqbn arduino:avr:uno examples/BasicAdaptiveSensor
arduino-cli compile --fqbn arduino:avr:nano examples/BasicAdaptiveSensor
```
