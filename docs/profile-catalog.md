# EcoSensePower Profile Catalog

EcoSensePower includes broad Arduino/IoT ecosystem coverage while keeping the core dependency-light. These profiles are convenience starting points for modeling and diagnostics, not measured battery-life evidence.

## Batteries

- AA alkaline
- NiMH AA / NiMH AAA
- LiPo 1S / LiPo 1S 400mAh / LiPo 2S / LiPo 2S 2000mAh
- Li-ion 18650
- Li-SOCl2 AA
- LiFePO4 1S
- CR2032
- CR123A
- D alkaline

All new ecosystem battery profiles are placeholders. CR2032/CR123A profiles warn about pulse/load limits. LiPo/Li-ion 18650/LiFePO4 profiles warn about charger/protection/regulator behavior. LiFePO4 and Li-SOCl2 are treated as flat-discharge chemistries for voltage-only SoC caution.

## Boards

- Arduino Nano, Mega, Pro Mini 3.3V/5V, Nano Every, MKR WAN
- ESP32 DevKit, ESP32-WROOM module, ESP8266 NodeMCU
- ATtiny85
- Raspberry Pi Pico / RP2040 placeholder

Board profiles are intentionally conservative because regulator, USB bridge, LEDs, clone variants, onboard peripherals, and firmware configuration often dominate real current.

## Sensors

- DHT22, DS18B20, BME280, HC-SR04
- Resistive soil probe, generic PIR, MPU6050, INA219, SCD30, analog LDR divider

`EcoSensorProfile` is the preferred generic profile model for new sensor profiles. The legacy generic analog shape remains available through `GenericAnalogSensorLegacy()` for compatibility.

## Radios

- SX1276 LoRa, RFM95W, nRF24L01, HC-12, SIM800L, ESP8266 WiFi

Radio profiles use `GenericRadioProfile` and add no mandatory external radio library dependency. SIM800L-style profiles intentionally trigger high burst-current diagnostics.

## Harvesters

- SolarHarvester
- PiezoHarvester
- ThermoelectricHarvester
- WindHarvester

Harvester profiles model input power and storage/conversion efficiency. They do not guarantee energy-neutral operation; storage and duty-cycle validation remain project-specific.

## Utilities

- `VoltageDivider` for battery/rail voltage scaling with leakage-current estimation.
- `EcoTime::days()`, `EcoTime::fromHz()`, and `EcoTime::toHz()` for readable interval configuration.
- Optional AVR `WatchdogSleepHelper::sleepForApprox()` for explicit approximate watchdog sleep experiments.

## Bluetooth/BLE

EcoSensePower now includes placeholder energy profiles for Bluetooth Classic SPP/UART bridge modules, BLE UART modules, nRF52/BLE modules, ESP32 BLE variants, NINA-class Arduino boards, Nano 33 BLE family boards, UNO R4 WiFi, Portenta H7, Giga R1, and generic board-integrated/external Bluetooth modules. See `docs/bluetooth-energy.md`.

## GPS/GNSS

EcoSensePower now includes placeholder high-energy peripheral profiles for generic GPS/GNSS receivers, NMEA UART GPS, I2C GNSS, high-update-rate GPS, low-power GNSS, u-blox/NEO families, Quectel, SIMCom, MTK/Adafruit, ATGM/CASIC, Beitian, active antenna, and multi-constellation variants. See `docs/gps-gnss-energy.md`.
