Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 4.2 Final Industrial Release Candidate Evidence

Phase 4.2 closes final-RC issues found in the Phase 4.1 review: safe `powerReport()` intervals, diagnostics truncation metadata, lower-noise diagnostics, custom SoC curves, deficit/neutral/surplus energy-harvesting policy, payload-aware radio energy, runtime radio batching, clearer TinyML semantics, and expanded host tests.

| Gate | Status | Evidence |
|---|---|---|
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` passed. |
| PowerReport no underflow | PASS | `EcoTime::remainingUntil()` used in `EcoRuntime::powerReport()`; `test_phase42_final_rc.cpp` verifies due/past deadlines do not create huge harvested-energy estimates. |
| Diagnostic truncation snapshot | PASS | `EcoDiagnosticSnapshot` and `collectDiagnosticsSnapshot()` expose copied/total/truncated; small-buffer test passes. |
| Reduced INFO diagnostic noise | PASS | `SENSOR_STATIC_NAME_CAUTION` is emitted only when debug is enabled. |
| SoC custom curve | PASS | `SoCTracker::voltageCurve()` and `hasCustomVoltageCurve()` added; test validates interpolation. |
| Li-SOCl2 voltage-only low confidence | PASS | Li-SOCl2 voltage-only report keeps placeholder confidence and suppresses strong days-left estimates. |
| Load voltage vs OCV limitation documented | PASS | README/docs clarify `observedVoltage()` is load-dependent and not automatically OCV. |
| Energy deficit/neutral/surplus | PASS | `EcoEnergyBalance` and `EnergyBudgetManager::energyBalance()` added; tests verify DEFICIT and SURPLUS. |
| Interval relaxation under surplus | PASS | `recommendedIntervalMs(current, min, max, soc, cycleCost)` can relax under surplus; test passes. |
| Radio payload-size estimate | PASS | `reportPayloadEstimator()` added; runtime radio TX duration uses configured payload estimate. |
| Radio default payload warning | PASS | PowerDoctor emits `RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER` when radio is configured without payload estimator. |
| Runtime RadioBatcher integration | PASS | `node.reporting()` added; non-critical reports are batched and critical/anomaly reports bypass batching. |
| TinyML rolling 24h window docs | PASS | Docs clarify `maxRunsPerDay()` is a rolling `millis()` window and one inference-equivalent operation per anomaly callback. |
| Inference wrap-safe test | PASS | `test_phase42_final_rc.cpp` checks unsigned elapsed behavior near `millis()` wrap. |
| Example host compile | PASS | All `examples/*/*.ino` compile as C++ objects with mock Arduino API. |
| Generic mock compile | PASS | Host generic compile passed. |
| AVR mock compile | PASS | AVR guarded compile passed in mock environment. |
| ESP32 mock compile | PASS | ESP32 guarded compile passed in mock environment. |
| SAMD/nRF52/RP2040 mock compile | PASS | Placeholder guarded compile passed in mock environment. |
| No mandatory heavy dependency | PASS | No mandatory RadioLib, WiFi, BLE, TFLM, Edge Impulse dependency. |
| No hardware measurement claim | PASS | Battery/SoC/energy reports remain estimate/confidence based. |
| Battery-life guarantee | NOT CLAIMED | Real battery-life claims require owner-side hardware validation. |
| Arduino Lint strict | NOT RUN LOCALLY / CI CONFIGURED | `arduino-lint` unavailable in this sandbox. Workflow remains configured. |
| Arduino CLI AVR UNO/Nano compile | NOT RUN LOCALLY / CI CONFIGURED | `arduino-cli` unavailable in this sandbox. Workflow remains configured. |
| Public Library Manager release | NOT APPROVED | Requires real Arduino Lint and Arduino compile evidence. |

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

## Remaining owner/GitHub gates

- Arduino Lint strict with Library Manager mode: PASS required before public release.
- Arduino CLI or `compile-sketches` matrix: AVR UNO/Nano PASS required before public release.
- ESP32/SAMD compile should pass or remain explicitly documented pending.
