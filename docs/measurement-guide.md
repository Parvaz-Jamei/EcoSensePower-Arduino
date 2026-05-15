# Measurement Guide

EcoSensePower estimates energy; it does not measure current.

Recommended owner-side validation:

1. Record board, MCU, regulator, battery, sensor, radio, firmware version, Arduino core version, and ambient temperature.
2. Measure sleep current, wake current, sensor warmup, sensor read, processing, reporting, and guard transitions.
3. Include regulator quiescent current and sensor leakage.
4. Compare measured cycle energy against `node.ledger().printCycleTo()` output.
5. Use measured profiles before making battery-life claims.

Do not claim battery lifetime from placeholder profiles.

## Measurement evidence for profile confidence

Use `EcoProfileConfidence::MEASURED` only when current values are measured and documented. A useful report should include board, core version, regulator, sensor/radio state, temperature if known, duty cycle, meter/instrument, and raw measured current values.

Use the `power_measurement_report.yml` issue template when contributing measured board, battery, sensor, or guard profiles.
