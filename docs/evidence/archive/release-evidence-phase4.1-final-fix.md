Superseded by ../../../release-evidence-v1.0.0-rc1.md

# EcoSensePower Phase 4.1 Final Fix Evidence

Phase 4.1 fixes the Phase 4 draft gap where scientific modules existed mostly as standalone utilities. This package connects SoC, harvesting, radio, inference, and diagnostics to the runtime-facing API while keeping the core dependency-light.

| Gate | Status | Evidence |
|---|---|---|
| Host logic tests | PASS | `extras/tests/run_host_tests.sh` passed. |
| SoC unknown state no fake 100% | PASS | `test_soc_tracker.cpp` and `test_phase41_integration.cpp` verify unknown SoC returns negative/unknown until evidence is provided. |
| Initial SoC / evidence flags | PASS | `SoCTracker::initialSocPercent()`, `hasInitialSoc()`, `hasVoltageEvidence()`, `hasCoulombEvidence()`. |
| Piecewise SoC lookup | PASS | LiPo, alkaline, NiMH, and Li-SOCl2 use conservative piecewise lookup curves; Li-SOCl2 keeps flat-curve warning. |
| Runtime module integration | PASS | `node.socTracker()`, `node.energyPolicy()`, `node.harvester()`, `node.radio()`, `node.powerReport()`. |
| Energy harvesting interval/cost comparison | PASS | `EnergyBudgetManager::incomeCoversCycle(intervalMs, cycleCost_mJ)` and runtime soft-budget integration. |
| Radio sleep current | PASS | `RadioEnergyAdapter::sleepCurrent_uA()` added and tested. |
| Radio ledger states | PASS | Runtime records `RADIO_TX` and `RADIO_SLEEP` when a radio adapter is configured and a report is emitted. |
| Inference ledger state | PASS | Runtime records `EcoEnergyState::INFERENCE` when anomaly/inference hook runs. |
| Inference 24h window | PASS | Runtime resets inference run count over a 24h `millis()` window. |
| PowerDoctor Phase 4 diagnostics | PASS | Added SoC, harvester, radio, inference, and diagnostic-buffer truncation codes. |
| Structured diagnostics buffer API | PASS | `node.collectDiagnostics(buffer, maxCount)` added. |
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

# Example host compile, compile-only:
for ino in examples/*/*.ino; do
  g++ -std=c++17 -Wall -Wextra -Werror \
    -Iextras/tests/mock_arduino -Iextras/tests -Isrc \
    -x c++ -c "$ino" -o "/tmp/ecosense_examples/<example>.o"
done
```

## Remaining owner/GitHub gates

- Arduino Lint strict with Library Manager mode: PASS required before public release.
- Arduino CLI or `compile-sketches` matrix: AVR UNO/Nano PASS required before public release.
- ESP32/SAMD compile should pass or remain explicitly documented pending.
