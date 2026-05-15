# EcoSensePower Architecture

EcoSensePower is an energy-aware runtime above low-level sleep backends.

## Layers

```text
Application Layer:
  EcoSensePower.h
  Public Arduino-style API

Runtime Layer:
  EcoRuntime
  EcoScheduler
  FSM state machine

Energy Layer:
  EnergyContract
  AdaptiveSampler
  EnergyModel
  EnergyLedger
  PowerDoctor

Guard Layer:
  PeripheralGuard callback and power-pin guard
  AVR ADC guard
  ESP32 wireless guard marker

Backend Layer:
  arch/generic
  arch/avr
  arch/esp32
  arch/samd
  arch/nrf52
  arch/rp2040

Profile Layer:
  BoardProfile
  BatteryProfile
  SensorProfile

Optional Layer:
  radio/
  harvester/
  ml/
```

## Dependency rule

The core has no mandatory dependency on RadioLib, TensorFlow Lite Micro, Wi-Fi, BLE, or sensor-specific libraries.

## Copy rule

No code, API shape, tests, examples, tables, or text should be copied from other low-power libraries. External projects are used only for conceptual research and compatibility sanity checks.


## Current release-candidate boundary

It adds modular scientific/industrial capabilities while keeping the core Arduino-friendly and dependency-light. Public release remains blocked until real Arduino Lint and Arduino compile evidence are attached.
