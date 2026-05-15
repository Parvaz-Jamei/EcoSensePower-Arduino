# EcoSensePower Profile Confidence Policy

EcoSensePower separates convenience profiles from measurement claims. A profile can be useful for modeling and diagnostics without being measured on this project hardware.

## Confidence levels

| Level | Meaning | Public claim boundary |
|---|---|---|
| `PLACEHOLDER` | Estimated, datasheet-typical, module-typical, or conservative value used to make sketches and diagnostics practical. | Not validated on this project hardware. Do not use for battery-life guarantees. |
| `DATASHEET` | Directly sourced from a named vendor datasheet or official hardware document and cited in project evidence/docs. | Still not a measured board-level profile; breakout regulators, pullups, LEDs, firmware, and temperature can change current. |
| `MEASURED` | Owner/user measured and documented with board, battery, firmware, tool, wiring, current range, date, and conditions. | Suitable for project-specific estimates, not universal guarantees. |

## New ecosystem profile rule

New ecosystem profiles default to `measured=false` and `EcoProfileConfidence::PLACEHOLDER`. This is intentional. Many Arduino boards and modules have clone/variant differences, regulator leakage, power LED current, pullup leakage, firmware duty-cycle differences, and environmental dependencies.

## Required notes for profiles

Every profile should mention its measurement boundary and the dominant uncertainty: battery load/cutoff/temperature, board regulator/USB/LED overhead, sensor power mode/warmup, radio burst current, harvester intermittency, or voltage-divider leakage.

## Wireless/GNSS placeholder policy

Bluetooth/BLE and GPS/GNSS profiles must remain `measured=false` and `EcoProfileConfidence::PLACEHOLDER` unless exact project-owned measurement evidence or a documented datasheet-derived profile is attached. A profile must not imply protocol-stack support, GPS parser support, fix-time guarantees, accuracy guarantees, or battery-life guarantees.
