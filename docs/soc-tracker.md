# SoC Tracker Pro

EcoSensePower includes a lightweight `SoCTracker` for battery state-of-charge estimates.

## Model

The tracker combines two estimate families:

- voltage-curve lookup when voltage is available,
- coulomb-style ledger integration from configured current and duration.

This is not a lab-grade fuel gauge. Voltage-only SoC can be misleading for chemistries with a flat discharge curve, especially Li-SOCl2. Coulomb-style accounting drifts unless the current profile and capacity are calibrated.

## Confidence

Every report carries `EcoProfileConfidence`:

- `PLACEHOLDER`: illustrative defaults only,
- `DATASHEET`: directly sourced from a named vendor datasheet or official hardware document and cited,
- `MEASURED`: owner-side measured profile.

Battery-life claims require owner-side hardware validation.

## Runtime correction

SoC is now evidence-bounded. Without initial SoC, voltage evidence, or coulomb evidence, `socPercent()` returns `-1` instead of pretending the battery is full. Coulomb-style estimates require `initialSocPercent()`; voltage estimates use conservative piecewise lookup curves and remain chemistry/load dependent. Li-SOCl2 keeps a flat-discharge warning because voltage-only SoC is low-confidence for that chemistry.


## SoC confidence updates

`SoCTracker` now supports optional custom voltage curves:

```cpp
static const float volts[] = {3.0f, 3.5f, 4.0f};
static const float soc[] = {0.0f, 50.0f, 100.0f};
node.socTracker().voltageCurve(volts, soc, 3);
```

The arrays must have static lifetime. Custom curves are still estimates unless derived from measured owner-side data. `observedVoltage()` is load-dependent and is not automatically equivalent to open-circuit voltage (OCV). For better voltage-based estimates, sample after a rest period, compensate for load, or keep confidence low.

For Li-SOCl2 and other flat-discharge chemistries, voltage-only SoC remains very low confidence. EcoSensePower avoids strong days-left estimates in Li-SOCl2 voltage-only mode. Use initial SoC plus coulomb-style ledger data and measured profiles when possible.
