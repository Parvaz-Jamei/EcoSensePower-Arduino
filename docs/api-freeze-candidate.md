# API Freeze Candidate

The API freeze candidate keeps the established EcoSensePower style and hardens the public surface without redesign.

Stable public entry points:

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
- `EnergyContract` chainable methods
- `EnergyLedger` cycle/lifetime methods

Constraints:

- Names passed to `sensor()` and `guard()` must have static lifetime.
- `loop()` may block while the backend sleeps.
- Energy values are estimates unless measured profiles are supplied.
- Additive changes are preferred after the release-candidate line; avoid public API redesign unless a compile-breaking defect requires it.

## Industrial scientific API additions under freeze candidate

These additions are included in the RC candidate without changing the basic sketch flow:

- `EcoTime::seconds(value)` / `minutes(value)` / `hours(value)` / `milliseconds(value)`
- `EcoSensePower::diagnosticCount()`
- `EcoSensePower::diagnosticAt(index)`
- `EcoSensePower::hasCriticalDiagnostics()`
- `EcoDiagnosticCode`
- `EcoDiagnostic`
- `EcoProfileConfidence`
- `HarvesterBase` as interface-only optional extension

The beginner API remains:

- `EcoSensePower`
- `sensor()`
- `read()`
- `minIntervalMs()`
- `maxIntervalMs()`
- `changeThreshold()`
- `onReport()`
- `begin()`
- `loop()`


## Advanced runtime escape hatch

`EcoSensePower::runtime()` remains public as an advanced/internal escape hatch for diagnostics, host tests, and expert integrations. It is not required for normal sketches and should not be used as the primary user-facing API before v1.0.0 final.
