# EcoSensePower API

## API freeze candidate

The following public surface is the release-candidate API freeze candidate. Future changes should be additive or clearly documented:

- `EcoSensePower`
- `begin()`
- `loop()`
- `sensor()`
- `guard()`
- `battery()`
- `board()`
- `onReport()`
- `ledger()`
- `printDiagnostics()`
- `runtime()` advanced/internal escape hatch
- `EnergyContract` interval, threshold, priority, warmup, and budget methods
- `EnergyLedger` cycle/lifetime reporting methods
- `EcoTime::seconds()`, `EcoTime::minutes()`, `EcoTime::hours()`


## Advanced runtime escape hatch

`EcoSensePower::runtime()` returns the lower-level `EcoRuntime` object. It is intentionally public for diagnostics, host tests, and expert integrations, but normal sketches should prefer the high-level `EcoSensePower` methods. Treat it as an advanced/internal escape hatch; pre-v1.0.0-final stability is narrower than the primary API surface.

## Runtime

```cpp
EcoSensePower node;
node.begin();
node.loop();
```

`node.loop()` drives the EcoSensePower runtime and may block while the selected backend sleeps. EcoSensePower is not a non-blocking task scheduler and is not an RTOS.

## Time helpers

```cpp
EcoTime::seconds(10);
EcoTime::minutes(5);
EcoTime::hours(6);
```

These helpers return millisecond values and are intended to make Arduino sketches more readable than raw multiplication expressions.

## Sensor contract

```cpp
node.sensor("soil")
  .read([]() -> float { return (float)analogRead(A0); })
  .warmupTimeMs(20)
  .minIntervalMs(EcoTime::minutes(5))
  .maxIntervalMs(EcoTime::hours(6))
  .initialIntervalMs(EcoTime::minutes(5))
  .changeThreshold(20.0f)
  .priority(ECO_NORMAL)
  .maxDailyEnergy_mJ(25000UL)
  .onWake([]() {})
  .onSleep([]() {})
  .calibratedCurrent(false);
```

`currentIntervalMs` is clamped to `minIntervalMs` and `maxIntervalMs`. `initialIntervalMs()` can be used for deterministic first scheduling. After a sensor is processed, the next deadline is scheduled from post-processing time.

Sensor names are stored as `const char*` pointers. Use string literals or other static-lifetime names. Do not pass temporary stack buffers or dynamically owned names that can disappear while the runtime is active.

## Peripheral guard

```cpp
node.guard("soil-power")
  .powerPin(7)
  .activeLevel(HIGH)
  .warmupTimeMs(20)
  .onWake([]() {})
  .onSleep([]() {});
```

Guard names are also stored as `const char*` pointers and should have static lifetime. Guard wake callbacks are executed when the runtime is about to process a due sensor; the idle sleep path intentionally does not run guard wake immediately after backend sleep to avoid duplicate wake behavior.

ESP32 wireless guard marker:

```cpp
node.guard("esp32-wireless")
  .esp32Wireless(true)
  .onSleep([]() {
    // Stop Wi-Fi/Bluetooth here if the application uses them.
  });
```

## Ledger

```cpp
node.ledger().beginCycle();
node.ledger().endCycle();
node.ledger().clearCycle();
node.ledger().printCycleTo(Serial);
node.ledger().printTotalTo(Serial);
```

The runtime records full-duty-cycle energy where backend sleep recorded before wake/sense/report remains in the same cycle until sensor processing finishes. A first immediate sensor read may have no preceding sleep segment.

## Diagnostics

```cpp
node.printDiagnostics(Serial);
```

Power Doctor reports severity-tagged diagnostics and does not stop runtime execution. The missing sleep-hook warning refers to the sensor-specific `onSleep()` callback; separate guards may still be configured. Use `printDiagnostics(out, minSeverity)` to hide INFO-level educational diagnostics in normal field logs.

## Optional harvesting interface

```cpp
#include <harvester/HarvesterBase.h>
```

`HarvesterBase` is runtime-connected through `node.harvester()` and `EnergyBudgetManager`. `SolarHarvester`, `PiezoHarvester`, `ThermoelectricHarvester`, and `WindHarvester` are energy-model helpers only. Board-specific MPPT, charger, fuel-gauge, and harvester hardware drivers remain outside the core until real hardware validation exists.

## Industrial scientific API additions

### Time helpers

`EcoTime::seconds(value)`, `EcoTime::minutes(value)`, and `EcoTime::hours(value)` are the preferred way to express intervals in public examples. `EcoTime::milliseconds(value)` is available for short guard/sensor warmup windows.

### Machine-readable diagnostics

Power Doctor still prints human-readable output, but diagnostics are also exposed as structured records:

```cpp
uint8_t count = node.diagnosticCount();
EcoDiagnostic diagnostic = node.diagnosticAt(0);
bool hasCritical = node.hasCriticalDiagnostics();
```

Each record contains:

```cpp
EcoDiagnosticCode code;
EcoDiagnosticSeverity severity;
const char* subject;
```

This makes diagnostics assertable in host tests and usable by dashboards/loggers without parsing text.

### Profile confidence

`BoardProfile` and `BatteryProfile` carry `EcoProfileConfidence`. Power Doctor separates generic-board fallback (`GENERIC_BOARD_PROFILE`) from placeholder board confidence (`BOARD_PROFILE_PLACEHOLDER`):

- `PLACEHOLDER`
- `DATASHEET` (only with a named vendor source and cited values)
- `MEASURED`

`EcoReport` also includes board/battery confidence and flags for regulator quiescent current and sensor leakage inclusion. Placeholder values are estimates. Datasheet values are only credible when the named vendor source and copied operating conditions are documented; neither is battery-life evidence.


## Current release-candidate boundary

It adds modular scientific/industrial capabilities while keeping the core Arduino-friendly and dependency-light. Public release remains blocked until real Arduino Lint and Arduino compile evidence are attached.

## Runtime-integrated APIs

EcoSensePower keeps optional runtime integration for the scientific modules and adds safe diagnostics snapshots plus payload-aware radio energy:

```cpp
SoCTracker& socTracker();
EnergyBudgetManager& energyPolicy();
EcoSensePower& harvester(HarvesterBase* harvester);
EcoSensePower& radio(RadioEnergyAdapter* radio);
EcoPowerReport powerReport() const;
uint8_t collectDiagnostics(EcoDiagnostic* buffer, uint8_t maxCount) const;
```

`powerReport()` returns SoC evidence flags, estimate confidence, energy-neutral configuration state, harvested input energy, usable/stored harvested energy, energy balance, radio/inference/sleep energy summaries, and estimated cycle cost. `collectDiagnosticsSnapshot()` is preferred for structured logging because it snapshots diagnostics into a caller-owned fixed buffer with truncation metadata.


## Release-candidate API notes

### Safe power reports
`node.powerReport()` uses safe remaining-time arithmetic. If the next sensor deadline is due or already in the past, the remaining interval is treated as `0` instead of underflowing an unsigned subtraction.

### Structured diagnostics snapshots
Use the snapshot API when exporting diagnostics to a dashboard, file, or test harness:

```cpp
EcoDiagnostic buffer[8];
EcoDiagnosticSnapshot snapshot = node.collectDiagnosticsSnapshot(buffer, 8);
// snapshot.copied: entries copied into buffer
// snapshot.total: total diagnostics collected
// snapshot.truncated: true if the caller buffer or internal buffer truncated output
```

`collectDiagnostics(buffer, maxCount)` returns only the copied count for simple sketches. Use `collectDiagnosticsSnapshot(buffer, maxCount)` when total diagnostic count and truncation status matter.

### Radio payload sizing and batching
Radio energy is payload-size dependent. Use `reportPayloadEstimator()` when the default 24-byte conservative estimate is not suitable:

```cpp
node.reportPayloadEstimator([](const EcoReport& report) -> size_t {
  return report.sensorName ? 16 + strlen(report.sensorName) : 16;
});
node.reporting().batchMaxSamples(8).maxReportIntervalMs(EcoTime::hours(2));
```

The runtime can aggregate non-critical report samples using `RadioBatcher`. The batch summary carries count, latest, min/max, and first/last timestamps so non-critical samples are not silently dropped. First reads, read failures, and anomaly/important-change reports bypass batching.

### TinyML / anomaly semantics
`maxRunsPerDay()` uses a rolling 24-hour `millis()` window, not calendar dates. The energy budget assumes one inference-equivalent operation per anomaly callback invocation. If an application runs multiple model passes inside one callback, its configured duration/current should include the full combined cost.


## Final-polish API notes

### Diagnostics filtering

```cpp
node.printDiagnostics(Serial, EcoDiagnosticSeverity::WARNING);
```

The unfiltered overload is still useful during bring-up. Field logs should normally use `WARNING` or `RISK` as the minimum severity.

### Energy harvesting efficiency

`EnergyBudgetManager` distinguishes harvester input energy from usable/stored energy:

```cpp
node.energyPolicy()
  .targetNeutralOperation(true)
  .storageEfficiencyPercent(70);
```

`powerReport().harvestedEnergy_mJ` reports raw input energy over the remaining interval. `powerReport().usableHarvestedEnergy_mJ` reports the efficiency-adjusted usable estimate.

### Radio RX window model

Radio adapters can model TX, optional RX windows, radio sleep current, confidence, and confirmed-uplink warnings without adding a mandatory radio-stack dependency.

### AVR power-down safety

`AvrSleepBackend::sleepFor(ms)` is timed-IDLE based. `powerDownOnce()` is an explicit one-shot path owned by the application wake-source configuration; it is not used as a timed scheduler.


## Diagnostic snapshot and power report notes

`collectDiagnostics(buffer, maxCount)` returns the number of diagnostics copied into the caller buffer. Use `collectDiagnosticsSnapshot(buffer, maxCount)` when total diagnostic count and truncation metadata are needed.

`EcoSensePower::powerReport()` populates `diagnosticsTruncated` from a PowerDoctor snapshot. `EcoSensePower::diagnosticsTruncated()` also collects a current snapshot before returning, so it is not based on stale previous PowerDoctor state. `EcoRuntime::powerReport()` remains a lower-level runtime report and does not own PowerDoctor collection.

## Ecosystem API additions

- `EcoSensorProfile` provides a generic name/warmup/read-current/sleep-current/confidence/notes model for sensor profiles.
- Battery chemistry coverage now includes LiPo 2S, Li-ion 18650, CR2032, CR123A, LiFePO4 1S, D alkaline, LiPo 1S 400mAh, and NiMH AAA.
- `VoltageDivider` helps scale raw ADC readings and estimate divider leakage current.
- `EcoTime::days()`, `EcoTime::fromHz()`, and `EcoTime::toHz()` improve readable scheduling.
- `EnergyContract::maxEnergyPerWindow_mJ()` and `EcoSensorConfig::maxEnergyPerWindow_mJ()` add optional time-window budget metadata.
- `WatchdogSleepHelper::sleepForApprox()` is an explicit AVR-only helper; it does not replace normal runtime sleep behavior.
