# Peripheral Guard

Peripheral Guard manages reversible peripheral transitions around wake/sleep phases.

## Baseline API

```cpp
node.guard("soil-power")
  .powerPin(7)
  .activeLevel(HIGH)
  .warmupTimeMs(20)
  .onWake([]() {})
  .onSleep([]() {});
```

## Guard lifecycle model

- Callback guard
- Power pin guard
- AVR ADC guard in `arch/avr`
- ESP32 wireless guard hook via `.esp32Wireless(true)`

## Ledger integration

Guard actions are recorded with `EcoEnergyState::GUARD`.

## Rules

Guards should be reversible. If an application-owned guard fails internally, the callback should handle it without crashing the runtime. EcoSensePower does not throw exceptions and does not allocate dynamically.

## Idempotent guard lifecycle

The runtime keeps an internal guard-awake state. `runGuardsWake()` is a no-op when guards are already awake, and `runGuardsSleep()` is a no-op when guards are already asleep. This prevents duplicate wake callbacks, duplicate sleep callbacks, repeated warmup delays, and duplicate guard-energy ledger entries in the same lifecycle.

The idle backend sleep path records sleep energy but does not run guard wake after backend sleep. Guards are woken immediately before due sensor work.
