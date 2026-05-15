# Radio Energy Adapter

EcoSensePower provides a radio energy adapter interface. There is no mandatory RadioLib dependency.

```cpp
class RadioEnergyAdapter {
public:
  virtual bool sleep() = 0;
  virtual bool wake() = 0;
  virtual uint32_t estimateTxDurationMs(size_t payloadBytes) const = 0;
  virtual uint32_t txCurrent_uA() const = 0;
  virtual uint32_t rxCurrent_uA() const = 0;
};
```

RadioLib already covers many wireless modules and protocols. EcoSensePower should not rewrite a radio stack. An optional guarded `RadioLibEnergyAdapter` stub exists. It is enabled only when `ECOSENSE_ENABLE_RADIOLIB_ADAPTER` is defined. RadioLib is not a mandatory dependency of the EcoSensePower core.
