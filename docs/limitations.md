# Limitations

EcoSensePower estimates energy from configured profiles and runtime state durations. It does not replace real current measurement. Battery-life claims require owner-side hardware validation.

## Current limitations

- Generic backend uses delay fallback and is not ultra-low-power.
- AVR power-down is optional and disabled by default.
- ESP32 wireless shutdown is application-owned through guard callbacks.
- ESP32-C3 and ESP32-S3 remain experimental until separately compiled/validated.
- SAMD/nRF52/RP2040 remain compile-readiness / placeholder backends in the current release-candidate line unless real board-specific compile evidence is attached.
- Board and battery profile values may be placeholders unless marked measured.
- Current profiles are estimates unless explicitly measured on the target hardware.
- Regulator quiescent current and sensor leakage must be measured by the owner.
- Sensor and guard names must have static lifetime because the runtime stores `const char*` pointers.
- TinyML, mesh coordination, and concrete RadioLib adapters are post-v1 or optional directions. Energy harvesting has model helpers for solar, piezo, thermoelectric, and wind sources plus EnergyBudgetManager policies; concrete solar/piezo/thermal/wind hardware validation remains owner-side.


## Current release-candidate boundary

It adds modular scientific/industrial capabilities while keeping the core Arduino-friendly and dependency-light. Public release remains blocked until real Arduino Lint and Arduino compile evidence are attached.


## Release-candidate limitations

- Real Arduino Lint and Arduino CLI compile evidence is still required before public release or Library Manager submission.
- SoC estimates are not fuel-gauge measurements. Voltage curves are estimates and are load/temperature/chemistry dependent.
- `observedVoltage()` is load-dependent and not necessarily open-circuit voltage.
- Li-SOCl2 voltage-only SoC is low confidence due to flat discharge behavior.
- Energy-neutral scheduling is a policy estimate; it does not guarantee perpetual operation.
- Radio energy depends on payload size and radio parameters. Configure payload estimators and measured/datasheet radio profiles for credible estimates.
- TinyML hooks estimate one inference-equivalent operation per anomaly callback invocation.
