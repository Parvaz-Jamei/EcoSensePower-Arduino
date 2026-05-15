# Wireless profile catalog

EcoSensePower provides confidence-bounded energy profiles for common wireless and high-energy peripherals without adding protocol-stack dependencies.

## Radio families

- LoRa/SX127x/RFM95W placeholders
- nRF24L01 placeholders
- HC-12 placeholders
- SIM800L/cellular burst-current placeholders
- ESP8266 WiFi energy placeholder
- Bluetooth Classic/SPP/UART bridge placeholders
- BLE module and board-level placeholders
- GPS/GNSS high-energy receiver placeholders

## Include policy

`EcoSensePower.h` remains the lightweight beginner/core API. Use individual profile headers, `EcoSensePowerProfiles.h`, `EcoSensePowerBluetoothProfiles.h`, or `EcoSensePowerGPSProfiles.h` only when the sketch needs profile coverage. AVR UNO/Nano Tiny/Core mode keeps the full profile catalog disabled by default.

## Claim policy

Profiles are scaffolding for estimates, diagnostics, and project-specific measurement. They do not prove battery life, protocol compatibility, GPS accuracy, GNSS fix time, BLE behavior, or measured current.
