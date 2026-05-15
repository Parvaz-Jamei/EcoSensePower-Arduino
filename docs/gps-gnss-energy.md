# GPS/GNSS energy profiles

EcoSensePower GPS/GNSS coverage is an energy-model layer, not a location parser, navigation framework, or fix-time guarantee. The core library does not include `TinyGPSPlus`, `Adafruit_GPS`, `SoftwareSerial`, or any mandatory parser dependency.

## What the profiles model

GPS/GNSS energy depends on cold start, warm start, hot start, acquisition versus tracking, update rate, sky visibility, antenna type, active antenna current, backup battery/RTC state, constellation mode, UART/I2C output rate, host processing cadence, and power gating strategy.

## Supported profile families

The catalog includes generic GPS/GNSS profiles plus u-blox/NEO-style modules, Quectel L76/L80/L86/LC76G-style modules, SIMCom GNSS modules, MTK3339/MTK3333/Adafruit maker modules, ATGM/CASIC-style modules, Beitian UAV-style modules, active antenna variants, UART and I2C generic aliases.

All shipped GPS/GNSS profiles are placeholders by default: `measured=false`, `EcoProfileConfidence::PLACEHOLDER`, and no accuracy, fix-time, or battery-life guarantee.
