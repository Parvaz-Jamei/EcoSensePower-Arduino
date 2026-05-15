# Bluetooth/BLE energy profiles

EcoSensePower Bluetooth/BLE coverage is an energy-model layer, not a Bluetooth protocol stack. The core library does not include `ArduinoBLE`, ESP32 BLE/NimBLE headers, `SoftwareSerial`, WiFi headers, or any mandatory Bluetooth dependency.

## What the profiles model

Bluetooth/BLE energy depends on advertising interval, connection interval, TX power, scan mode, central/peripheral role, payload frequency, pairing/bonding state, module idle current, UART bridge idle/connected state, board regulator current, USB bridge current, and host sleep coordination.

## Classic Bluetooth versus BLE

HC-05, HC-06, HC-02, HC-04, RN42, and SPP-style modules are modeled as Bluetooth Classic/UART bridge energy profiles. HM-10/HM-11, AT-09, JDY modules, RN487x, nRF52 modules, NINA-class boards, ESP32 BLE targets, and Arduino BLE-capable boards are modeled separately as BLE-style profiles. They must not be treated as the same energy behavior.

## Dependency policy

Use `#include <profiles/radios/bluetooth/...>` or `#include <EcoSensePowerBluetoothProfiles.h>` for profile-only modeling. Optional protocol integrations remain application-owned and are not included by the core runtime.

All shipped Bluetooth/BLE profiles are placeholders by default: `measured=false`, `EcoProfileConfidence::PLACEHOLDER`, and no battery-life guarantee.
