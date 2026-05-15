# Energy-Neutral Scheduling

`EnergyBudgetManager` connects battery state, harvested energy, and adaptive interval stretching.

EcoSensePower never guarantees perpetual operation. Energy-neutral mode is a policy target: if incoming energy is unknown or insufficient, the manager recommends stretching intervals toward the configured maximum.

The application owns solar/harvester measurement hardware. EcoSensePower only models the energy budget.

## Runtime integration

When `node.harvester()` and `node.energyPolicy().targetNeutralOperation(true)` are configured, runtime soft-budgeting compares harvested energy during the current interval against the estimated cycle cost. If the income is insufficient and interval stretching is allowed, the sensor interval is stretched toward the configured max interval. This is still an estimate, not a perpetual-operation claim.


## Energy balance states

`EnergyBudgetManager` exposes an explicit balance model:

```cpp
EcoEnergyBalance b = node.energyPolicy().energyBalance(intervalMs, cycleCost_mJ, socPercent);
```

- `DEFICIT`: harvested energy over the interval is below cycle cost, or reserve is below the configured minimum.
- `NEUTRAL`: harvested energy is sufficient but not clearly surplus.
- `SURPLUS`: harvested energy is materially above cycle cost, allowing interval relaxation toward the configured minimum.
- `UNKNOWN`: policy or inputs are insufficient for a meaningful balance decision.

`recommendedIntervalMs(current, min, max, soc, cycleCost)` can stretch under deficit and relax under surplus. This remains an estimate and does not guarantee perpetual operation.


## Usable-energy SoC credit

Harvested input power is not credited directly to the SoC ledger. EcoSensePower credits only usable/stored energy after storage or charging efficiency has been applied. This avoids optimistic SoC behavior when solar/harvester input is available but conversion/storage losses are significant.
