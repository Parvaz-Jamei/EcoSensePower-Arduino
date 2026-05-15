# Power Doctor v2

Power Doctor is a diagnostic layer. It reports risk; it does not fail or stop the runtime.

## Severity

```cpp
enum class EcoDiagnosticSeverity : uint8_t {
  INFO,
  WARNING,
  RISK,
  CRITICAL
};
```

## Diagnostic checks

- Generic delay fallback active
- Real sleep backend missing
- AVR idle-only backend active
- ESP32 wireless guard missing
- Sensor has no onSleep callback
- Sensor name static-lifetime warning
- No report callback configured
- Placeholder board profile
- Placeholder battery profile
- Regulator quiescent current missing
- `maxDailyEnergy_mJ` active without calibrated current profile
- Estimated daily energy exceeds `maxDailyEnergy_mJ`
- Ledger aggregate mode active
- Sensor registry full
- Current interval clamped
- No hardware current measurement evidence

## Output style

```text
[EcoSensePower Doctor]
- RISK: ESP32 backend active but no wireless guard is configured.
- RISK: Battery estimate excludes regulator quiescent current.
- RISK: Estimated daily energy exceeds maxDailyEnergy_mJ; adaptive interval was increased.
- WARNING: Ledger aggregate mode active; per-state details were truncated.
```

## Name lifetime diagnostic

Power Doctor reminds users that sensor and guard names should have static lifetime. This is a documentation/runtime-risk warning only; the library does not allocate or copy names in order to stay small and AVR-safe.

## Machine-readable diagnostics

Power Doctor exposes `EcoDiagnosticCode`, `EcoDiagnosticSeverity`, and `EcoDiagnostic` so diagnostics can be tested and exported without parsing text.

The public wrapper exposes:

```cpp
node.diagnosticCount();
node.diagnosticAt(index);
node.hasCriticalDiagnostics();
```

`printDiagnostics()` uses the same diagnostic records, so human-readable output and machine-readable diagnostics stay aligned.

Important diagnostic codes include:

- `GENERIC_BOARD_PROFILE`
- `BOARD_PROFILE_PLACEHOLDER`
- `REAL_SLEEP_BACKEND_MISSING`
- `ESP32_WIRELESS_GUARD_MISSING`
- `SENSOR_NO_SLEEP_CALLBACK`
- `SENSOR_NO_CALIBRATED_CURRENT`
- `REGULATOR_IQ_MISSING`
- `SENSOR_LEAKAGE_MISSING`
- `LEDGER_AGGREGATE_MODE`
- `SENSOR_REGISTRY_FULL`
- `GUARD_REGISTRY_FULL`
- `BUDGET_EXCEEDED`
- `CURRENT_INTERVAL_CLAMPED`
- `NO_HARDWARE_MEASUREMENT`

Power Doctor does not stop the runtime; it provides structured risk signals for the application owner.


## Diagnostic snapshot API

Industrial users should prefer `collectDiagnosticsSnapshot()` over repeated `diagnosticAt()` calls when exporting logs. It returns copied count, total count, and truncation status, so small caller buffers cannot silently hide diagnostics.

```cpp
EcoDiagnostic diagnostics[4];
EcoDiagnosticSnapshot snapshot = node.collectDiagnosticsSnapshot(diagnostics, 4);
if (snapshot.truncated) {
  // Increase buffer or export in pages.
}
```

Informational `SENSOR_STATIC_NAME_CAUTION` diagnostics are debug-only in normal operation to reduce output noise. The static-lifetime rule remains documented in README/API docs.

New diagnostics include payload-estimator placeholder status, board-profile placeholder status, and caller-visible truncation handling.


## Diagnostics filtering and module codes

Use severity filtering for field logs:

```cpp
node.printDiagnostics(Serial, EcoDiagnosticSeverity::WARNING);
```

Use `collectDiagnosticsSnapshot()` for structured export because it returns `copied`, `total`, and `truncated`. `collectDiagnostics()` remains a simple copied-count helper for sketches.

Additional module diagnostics include:

- `RADIO_RX_WINDOW_COST_HIGH`
- `RADIO_CONFIRMED_UPLINK_WARNING`
- `HARVESTING_EFFICIENCY_PLACEHOLDER`
- `INFERENCE_SKIPPED_ENERGY_DEFICIT`

These diagnostics are advisory risk signals. They do not block the runtime.


## Truncation freshness

`EcoSensePower::diagnosticsTruncated()` collects a current PowerDoctor snapshot before returning, so it is not based on a stale previous diagnostic state. Prefer `collectDiagnosticsSnapshot()` when exporting diagnostics because it returns copied count, total count, and truncation status in one call.

## Ecosystem diagnostics

Power Doctor can now report additional diagnostics for ecosystem profiles:

- `RADIO_BURST_CURRENT_HIGH` for cellular-style burst-current risk.
- `SOC_LOW_CONFIDENCE_FLAT_CURVE` for voltage-only SoC on flat-discharge chemistries.
- `BATTERY_PULSE_LIMITATION` for coin/primary cells with pulse-load caveats.
- `BATTERY_PROTECTION_CIRCUIT_UNKNOWN` for rechargeable lithium profiles without documented charger/protection/regulator behavior.
- `ENERGY_WINDOW_BUDGET_ACTIVE` and `ENERGY_WINDOW_BUDGET_EXCEEDED` for optional per-window energy contracts.
- `MULTIPLE_CRITICAL_SENSORS`, `SENSOR_PRIORITY_CONFLICT`, and `SENSOR_REGISTRY_NEAR_CAPACITY` for scheduling clarity.

## Wireless/GNSS diagnostics direction

Bluetooth/BLE and GPS/GNSS diagnostics should remain lightweight and confidence-bounded. Candidate warnings include placeholder profile use, unknown advertising/connection intervals, high scan current, unknown TX power, UART bridge idle current, board support requirements, GPS cold-start energy, active antenna current, high update rate, and multi-constellation current. Do not allocate new diagnostic storage in AVR Tiny/Core mode by default.
