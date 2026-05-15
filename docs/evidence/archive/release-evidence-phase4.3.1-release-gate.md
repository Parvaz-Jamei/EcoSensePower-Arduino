Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 4.3.1 Release Gate Evidence

Phase 4.3.1 is a pre-v1.0.0-rc1 release-gate patch over Phase 4.3. It keeps the scientific/industrial feature set intact and closes the final state/reporting/documentation gaps identified during RC review.

This package is intended to be reviewed as a strong v1.0.0-RC candidate. Public Arduino Library Manager release remains a promotion decision after real Arduino Lint and Arduino compile output is attached.

## Validation summary

| Gate | Status | Evidence |
|---|---|---|
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` completed successfully. |
| Phase 4.3.1 release-gate tests | PASS | `test_phase431_release_gate.cpp` covers usable-energy SoC credit, diagnostics truncation propagation, and stale inference-deficit clearing. |
| Harvester SoC credit uses usable energy | PASS | 50% vs 100% storage-efficiency behavior is tested. |
| `EcoPowerReport::diagnosticsTruncated` | PASS | Public `EcoSensePower::powerReport()` populates the field via `PowerDoctor::collectSnapshot()`. |
| Stale inference deficit diagnostic | PASS | A deficit cycle emits the diagnostic, and a later recovered-energy cycle clears it. |
| RadioBatcher documentation | PASS | README and `docs/radio-energy-adapter.md` define it as AVR-safe aggregate batching, not arbitrary payload buffering. |
| `keywords.txt` Phase 4.x symbols | PASS | Public API symbols for SoC, energy policy, radio, diagnostics, and reports are included. |
| Stale Phase 3 limitation wording | PASS | `docs/limitations.md` now describes Phase 4.3.x compile-readiness status. |
| Example mock compile | PASS | All `examples/*/*.ino` compile as C++ objects with the mock Arduino API. |
| Guarded architecture mock compile | PASS | Generic, AVR, ESP32, SAMD, nRF52, and RP2040 guarded paths compile in the mock environment. |
| No mandatory heavy dependency | PASS | No mandatory RadioLib, WiFi, BLE, TFLM, Edge Impulse, STL vector, or heap-allocation dependency was added to the core. |
| Battery-life guarantee | NOT CLAIMED | README/docs keep all battery-life, SoC, and energy-neutral behavior estimate/confidence based. |
| Arduino Lint Library Manager mode | PROMOTION GATE READY | Workflow/tooling is configured. Attach `arduino-lint --library-manager submit --compliance strict .` output before public tagging. |
| AVR UNO/Nano Arduino compile | PROMOTION GATE READY | Workflow/tooling is configured. Attach real Arduino CLI or GitHub Actions output before public tagging. |
| ESP32/SAMD Arduino compile | PROMOTION GATE READY | Compile matrix is configured; attach real output or documented pending status for RC promotion. |

## Commands executed for this package

```bash
extras/tests/run_host_tests.sh

mkdir -p /tmp/ecosp_example_objs
for f in examples/*/*.ino; do
  g++ -std=c++17 -Wall -Wextra -Werror     -Iextras/tests/mock_arduino -Isrc     -x c++ -c "$f" -o "/tmp/ecosp_example_objs/$(basename $(dirname "$f")).o"
done

# Architecture-guard mock compile performed for:
# ARDUINO_ARCH_AVR, ARDUINO_ARCH_ESP32, ARDUINO_ARCH_SAMD,
# ARDUINO_ARCH_NRF52, ARDUINO_ARCH_RP2040.
```

## Promotion note

The package has strong in-repository validation for runtime logic, diagnostics, energy modeling, and portable source structure. The remaining promotion step is not a code-quality disclaimer; it is the normal Arduino ecosystem release gate: real Arduino Lint and real board-FQBN compile evidence should be attached before tagging v1.0.0-rc1 or submitting to Arduino Library Manager.
