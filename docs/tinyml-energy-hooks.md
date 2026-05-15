# TinyML / Anomaly Energy Hooks

EcoSensePower does not include TensorFlow Lite Micro, Edge Impulse, or any model runtime as a mandatory dependency. The library provides dependency-free hooks for accounting and gating inference-like work.

## Inference budget

```cpp
node.sensor("vibration")
  .read(readScore)
  .onAnomaly([](float score) {
    return score > 0.75f;
  })
  .inferenceCost()
    .current_uA(8500)
    .durationMs(40)
    .maxRunsPerDay(200)
    .skipWhenEnergyDeficit(true)
    .allowCriticalBypass(true);
```

`maxRunsPerDay()` uses a rolling 24-hour `millis()` window, not a calendar day. EcoSensePower uses wrap-safe unsigned elapsed arithmetic for the window.

The configured cost assumes one inference-equivalent operation per anomaly callback invocation. If a sketch runs several model passes inside one callback, include the combined current and duration in the configured budget.

## Energy deficit behavior

If `skipWhenEnergyDeficit(true)` is enabled and `EnergyBudgetManager` reports `DEFICIT`, non-critical anomaly/inference work can be skipped and Power Doctor reports `INFERENCE_SKIPPED_ENERGY_DEFICIT`.

Critical application logic remains application-owned. EcoSensePower does not know whether a sensor event is safety-critical until the user callback runs, so designers must choose conservative gating settings for safety-sensitive deployments.

## Architecture boundary

- AVR: use lightweight rule-based anomaly hooks and accounting only.
- ESP32 / nRF52 / RP2040 / ARM: optional inference hooks can represent TFLM/Edge Impulse work without making those frameworks mandatory.
- All architectures: no mandatory ML dependency is added to the core.
