# Energy Harvesting Interface

EcoSensePower includes optional harvesting model classes: `SolarHarvester`, `PiezoHarvester`, `ThermoelectricHarvester`, and `WindHarvester`, plus `EnergyBudgetManager` policies for energy-neutral scheduling.

These are energy-model helpers, not board-specific MPPT, charger, fuel-gauge, or harvester hardware drivers. Real solar, piezo, thermoelectric, or wind hardware behavior requires owner-side validation and measured evidence.

```cpp
SolarHarvester solar;
solar.fixedMilliWatt(12.0f)
     .storageEfficiencyPercent(70)
     .confidence(EcoProfileConfidence::PLACEHOLDER);

node.harvester(&solar);
node.energyPolicy()
  .targetNeutralOperation(true)
  .minReservePercent(25)
  .allowIntervalStretching(true);
```

## Input energy vs usable energy

`EnergyBudgetManager` distinguishes input energy from usable/stored energy:

- `inputEnergyDuringInterval_mJ()` uses raw harvester input power.
- `usableEnergyDuringInterval_mJ()` applies storage/charging efficiency.
- `harvestedEnergyDuringInterval_mJ()` is kept as a compatibility alias for usable/stored energy.

Power Doctor warns when harvesting profiles or efficiency are placeholder-level.

## Policy states

The policy reports `EcoEnergyBalance`:

- `DEFICIT`: usable energy over the interval is below estimated cycle cost or reserve is too low.
- `NEUTRAL`: usable energy is close to estimated cost.
- `SURPLUS`: usable energy is materially above estimated cost; the runtime may relax interval stretching.
- `UNKNOWN`: not enough policy/evidence data.

Energy-neutral operation is a policy target, not a guarantee. Real validation is owner-side hardware work.

## Harvester coverage

In addition to `SolarHarvester`, EcoSensePower includes `PiezoHarvester`, `ThermoelectricHarvester`, and `WindHarvester`. These model input power and storage efficiency only. Piezo and wind sources are intermittent; thermoelectric sources depend on sustained temperature gradient and converter efficiency.

Use `confidence(EcoProfileConfidence::PLACEHOLDER)` unless you attach project-specific measurement evidence.
