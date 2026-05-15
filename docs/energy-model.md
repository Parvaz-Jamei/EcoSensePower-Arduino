# Energy Model

EcoSensePower uses state-based estimated energy accounting:

```text
E_cycle = sum(V * I * t)
I_avg = E_cycle / (V_battery * T_cycle)
```

The estimate is based on configured board, battery, current-profile values, and runtime state durations. It is not a current measurement. Current profiles are estimates unless explicitly marked `measured` and backed by owner-side hardware measurement.

## States

```cpp
enum class EcoEnergyState : uint8_t {
  SLEEP,
  WAKEUP,
  SENSOR_WARMUP,
  SENSOR_READ,
  PROCESS,
  REPORT,
  RADIO_TX,
  RADIO_RX,
  RADIO_SLEEP,
  INFERENCE,
  IDLE,
  GUARD
};
```

`RADIO_TX`, `RADIO_RX`, and `RADIO_SLEEP` are recorded when a radio adapter is configured. `INFERENCE` is recorded when anomaly/ML hooks run. EcoSensePower keeps all radio/ML frameworks optional; the ledger records modeled energy states, not vendor stack internals.

## Cycle and lifetime accounting

The ledger keeps current-cycle records and lifetime totals. Record storage is fixed-size. If the record buffer is full, aggregate mode is activated and Power Doctor warns.

## Runtime cycle semantics

EcoSensePower uses **Full Duty Cycle Ledger** semantics for runtime-owned cycles:

```text
sleep segment(s) -> guard wake -> sensor wake -> warmup -> read -> process -> optional report -> guard sleep
```

This is closer to how a battery-powered sensor node is measured in practice: a duty cycle includes the sleep time leading into a wake/read/report event. The idle sleep path does not execute guard wake after backend sleep; guard wake runs at the start of due sensor processing to avoid duplicate callbacks and duplicate guard energy records. If the first sensor read happens immediately after `begin()`, there may be no preceding sleep segment in that first cycle.

`printCycleTo()` reports the latest runtime cycle. `printTotalTo()` reports lifetime totals across all recorded states. Manual calls to `beginCycle()` and `endCycle()` remain available for advanced sketches, but normal users should let the runtime manage cycles.

## Scientific direction

LoRa/LoRaWAN energy modeling literature commonly separates node energy into sensing, processing, transmission, reception, and sleep/idle phases. EcoSensePower follows the same state-based accounting pattern while keeping claims conservative.


## Voltage and current measurement boundary

EcoSensePower computes estimated energy as:

```text
E = V x I x t
```

By default, `V` is `BatteryProfile::nominalVoltageV`. For estimates to be meaningful, current values in `BoardProfile`, `SensorProfile`, `RadioProfile`, and `InferenceBudget` should be expressed at the same electrical boundary as the configured voltage.

If current profiles were measured at a regulated board rail such as 3.3V or 5V, document that boundary in the profile notes. A future release may add an explicit `measurementVoltageV` / `supplyVoltageV` field; this RC keeps the API stable and documents the assumption.

## Limitation

Battery-life claims require owner-side hardware validation with measured current across sleep, wake, sensing, processing, reporting, regulator leakage, sensor leakage, radio behavior, temperature-relevant conditions, and the actual battery chemistry used.

## Profile confidence and estimate quality

EcoSensePower makes estimate quality explicit through `EcoProfileConfidence`:

- `PLACEHOLDER`: default or approximate values, not suitable for battery-life claims.
- `DATASHEET`: values directly sourced from a named vendor datasheet or official hardware document and cited in project evidence/docs; still dependent on operating conditions.
- `MEASURED`: owner-side measured values with documented setup and assumptions.

`EcoReport` includes profile confidence, `includesRegulatorIq`, and `includesSensorLeakage`. Power Doctor warns when regulator quiescent current or sensor leakage is not included.

Energy estimates are model outputs from configured profiles and runtime state durations. They do not replace real current measurement.


## Final-polish model notes

- `BatteryProfile::regulatorIq_uA` is added to modeled currents when the board profile does not already include regulator IQ. This avoids silently ignoring regulator metadata while preventing double-counting for measured board profiles.
- Harvesting reports distinguish input energy from usable/stored energy through storage-efficiency assumptions.
- Radio reports can include TX, RX-window, and sleep energy. Payload-size estimation remains application-provided when the default compact estimate is not representative.
- Inference energy is recorded as `INFERENCE` and can be skipped under energy deficit when the sketch enables that policy.

## Voltage/current boundary reminder

Battery, board, sensor, radio, inference, and harvester profiles must share a consistent electrical boundary. If current was measured at a regulated 3.3V or 5V rail, document that in the profile notes and do not mix it with battery-side voltage without regulator efficiency/current modeling.

The `VoltageDivider` helper can scale ADC readings for battery voltage, but divider leakage and ADC reference tolerance must be included before making runtime claims.
