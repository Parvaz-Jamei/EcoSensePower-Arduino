# Radio Energy Adapter

EcoSensePower does not implement a radio stack. It models radio energy cost through `RadioEnergyAdapter` and `GenericRadioProfile`.

Radio TX/RX often dominates battery use, so EcoSensePower models:

- TX current,
- RX current,
- radio sleep current,
- payload-aware TX duration,
- optional RX-window duration,
- confirmed-uplink warning metadata,
- radio profile confidence,
- fixed-size aggregate batching for non-critical reports.

No RadioLib dependency is mandatory.

## Runtime connection

When `node.radio(&adapter)` is configured and a report is emitted, EcoSensePower records `RADIO_TX`, optional `RADIO_RX`, and `RADIO_SLEEP` energy entries in the ledger.

```cpp
GenericRadioProfile radio;
radio.txCurrent_uA(92000)
     .rxCurrent_uA(12000)
     .sleepCurrent_uA(1)
     .rxWindowDurationMs(250)
     .confirmedUplink(false)
     .confidence(EcoProfileConfidence::PLACEHOLDER);

node.radio(&radio);
```

## Payload sizing

Radio TX energy uses `node.reportPayloadEstimator()` when configured:

```cpp
node.reportPayloadEstimator([](const EcoReport& report) -> size_t {
  return 12 + (report.sensorName ? strlen(report.sensorName) : 0);
});
```

Without a hook, EcoSensePower uses a conservative 24-byte default and emits `RADIO_PAYLOAD_ESTIMATOR_PLACEHOLDER`. This default is a release-safe estimate, not a LoRaWAN airtime model.

## Batching semantics

`node.reporting()` provides a lightweight aggregate batcher for non-critical reports. It stores count, latest, min/max, and first/last timestamps so non-critical samples are not silently dropped. First reads, read failures, anomaly reports, and important-change reports bypass batching.

## LoRa/LoRaWAN boundary

LoRa/LoRaWAN energy depends on payload size, spreading factor, bandwidth, coding rate, TX power, ACK/RX windows, retries, region, and network behavior. EcoSensePower provides state-energy hooks and diagnostics; it does not implement a full LoRaWAN stack.


## Aggregate batching semantics

`RadioBatcher` is intentionally AVR-safe aggregate batching, not arbitrary payload buffering. It keeps a compact summary: sample count, latest value, minimum, maximum, first timestamp, and last timestamp. This prevents silent loss of non-critical observations while avoiding heap allocation or large dynamic payload buffers. Critical/anomaly reports bypass batching and are reported immediately.

Payload-aware radio energy remains estimate-based. The runtime uses the configured payload-size estimator when available; otherwise it falls back to a conservative compact-report default and the Power Doctor can warn about placeholder payload sizing.

## Named radio profiles

EcoSensePower now includes dependency-free radio energy profiles for SX1276 LoRa, RFM95W, nRF24L01, HC-12, SIM800L, and ESP8266 WiFi. They are built on `GenericRadioProfile` and add no mandatory RadioLib, SIM800, WiFi, or BLE dependency.

All named radio profiles default to `EcoProfileConfidence::PLACEHOLDER`. SIM800L-style cellular profiles can trigger `RADIO_BURST_CURRENT_HIGH` because supply/storage peak-current capability is often more important than average current.

## Bluetooth/BLE profile-only coverage

Bluetooth/BLE profile headers model radio energy budgets only. They do not include `ArduinoBLE`, ESP32 BLE/NimBLE, WiFi, or `SoftwareSerial`. Optional application-owned protocol integrations must be explicitly included and guarded.
