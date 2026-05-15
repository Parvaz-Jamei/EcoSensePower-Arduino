# Profile Calibration

EcoSensePower separates placeholder, datasheet, and measured profiles.

A measured profile should document:

- board name and revision,
- power source and regulator,
- sleep current,
- active current,
- sensor read current,
- radio TX/RX current when relevant,
- measurement instrument,
- date and test sketch.

Developer-side hardware testing is not required. Owner-side measurements should be recorded before public battery-life claims.

## Ecosystem profile calibration

The expanded battery, board, sensor, radio, and harvester profiles are intentionally `PLACEHOLDER` until a project owner attaches measurement evidence. Treat them as modeling defaults and diagnostics scaffolding.

Calibration should record: board/module variant, battery cell or pack, regulator path, measurement voltage boundary, current range, measurement tool, firmware duty cycle, radio payload/TX power, sensor power mode, ambient temperature, and date.
