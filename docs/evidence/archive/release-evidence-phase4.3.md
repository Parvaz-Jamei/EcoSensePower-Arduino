Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 4.3 Final Industrial Polish Evidence

Phase 4.3 is a final industrial polish package over Phase 4.2. It keeps all Phase 4.2 modules and closes release-gate issues around AVR timed sleep safety, regulator IQ modeling, radio RX-window modeling, aggregate batching semantics, harvesting efficiency, inference energy gating, diagnostics usability, and expanded power-report metadata.

This package is a strong release-candidate artifact, not a public Arduino Library Manager release. Public release remains blocked until real Arduino Lint and Arduino compile evidence are available from GitHub Actions or a local Arduino toolchain.

| Gate | Status | Evidence |
|---|---|---|
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` passed, including `test_phase43_final_polish.cpp`. |
| PowerReport no underflow | PASS | `EcoTime::remainingUntil()` is used and `test_phase43_final_polish.cpp` verifies due deadlines do not create large harvested-energy estimates. |
| Diagnostics truncation snapshot | PASS | `EcoDiagnosticSnapshot` exposes copied/total/truncated; small-buffer test passes. |
| Diagnostics severity filtering | PASS | `printDiagnostics(out, minSeverity)` added and documented. |
| AVR timed sleep safety | PASS | `sleepFor(ms)` remains IDLE-based; `powerDownOnce()` is explicit one-shot and application-owned. |
| Regulator IQ integration | PASS | `BatteryProfile::regulatorIq_uA` is added when board profiles do not include regulator IQ; double-count prevention is tested. |
| Radio payload-aware energy | PASS | `reportPayloadEstimator()` remains supported and tests verify payload size affects radio TX energy. |
| Radio RX window model | PASS | `estimateRxWindowDurationMs()`, `expectsRxWindow()`, `confirmedUplink()`, and `RADIO_RX` ledger recording added. |
| Radio profile confidence | PASS | `RadioEnergyAdapter::confidence()` added; placeholder radio profiles produce diagnostics. |
| Radio batching semantics | PASS | `RadioBatcher` stores fixed-size aggregate summary fields instead of silently dropping non-critical samples. |
| Harvesting usable-energy model | PASS | Input energy and usable/stored energy are distinguished through storage-efficiency assumptions. |
| Inference energy-deficit gating | PASS | `skipWhenEnergyDeficit()` and `INFERENCE_SKIPPED_ENERGY_DEFICIT` diagnostic added. |
| EcoPowerReport expansion | PASS | Energy balance, usable harvested energy, radio/inference/sleep energy, and confidence fields added. |
| Example mock compile | PASS | All `examples/*/*.ino` compile as C++ objects with mock Arduino API. |
| No mandatory heavy dependency | PASS | No mandatory RadioLib, WiFi, BLE, TFLM, Edge Impulse, STL vector, or dynamic-allocation dependency added. |
| No battery-life guarantee | PASS | Battery-life and energy-neutral claims remain estimate/confidence based and require owner-side hardware validation. |
| Arduino Lint strict | NOT RUN LOCALLY / CI CONFIGURED | `arduino-lint` is unavailable in this sandbox. Run `arduino-lint --library-manager submit --compliance strict .` before public release. |
| Arduino CLI AVR UNO/Nano compile | NOT RUN LOCALLY / CI CONFIGURED | `arduino-cli` is unavailable in this sandbox. Run AVR UNO/Nano compile before public release. |
| ESP32/SAMD compile | NOT RUN LOCALLY / CI CONFIGURED | Matrix workflow remains configured; real output is required before public release. |
| Public Library Manager release | BLOCKED | Requires real Arduino Lint and compile evidence. |

## Commands run in this environment

```bash
extras/tests/run_host_tests.sh

mkdir -p /tmp/ecosense_examples
for ino in examples/*/*.ino; do
  name=$(basename $(dirname "$ino"))
  g++ -std=c++17 -Wall -Wextra -Werror \
    -Iextras/tests/mock_arduino -Iextras/tests -Isrc \
    -x c++ -c "$ino" -o "/tmp/ecosense_examples/${name}.o"
done

command -v arduino-cli || true
command -v arduino-lint || true
```

## Professional release note

The host-side logic tests and mock compile checks passed in this environment and are useful release-candidate evidence. They do not replace real Arduino CLI compile or Arduino Lint Library Manager compliance checks. This is intentional and release-safe: the project is presented as a strong industrial RC candidate until real Arduino evidence is attached.
