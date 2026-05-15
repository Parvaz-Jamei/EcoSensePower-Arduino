# Contributing to EcoSensePower

EcoSensePower is an industrial energy-aware runtime for battery-powered Arduino sensor nodes. Contributions should keep the core lightweight, dependency-free, and honest about measurement limits.

## Contribution rules

- Do not copy code, tests, examples, API shapes, tables, or documentation from other projects unless the license, attribution, and reuse decision are explicitly documented.
- Keep the core free of mandatory Wi-Fi, BLE, RadioLib, TinyML, sensor-driver, or harvesting dependencies.
- Do not claim battery life without measured current evidence.
- Prefer small additive changes over public API redesign.
- Keep AVR compile safety in mind: no mandatory STL containers, no dynamic allocation in core runtime paths, and no hidden heavy dependencies.

## Adding a BoardProfile

A board profile should include:

- Board name and MCU family.
- Active current, sleep current, sensor-read current, and process current.
- Whether values are `measured`, `datasheet`, or `placeholder`.
- Measurement setup if measured: board revision, power source, regulator path, meter/tool, sketch, current range, and date.
- Limitations such as USB bridge, LEDs, regulator quiescent current, attached sensors, radio modules, and temperature.

## Adding a BatteryProfile

A battery profile should include:

- Chemistry and nominal voltage.
- Capacity source and discharge assumptions.
- Whether capacity is measured or nominal.
- Any warning about temperature, load, regulator dropout, and pulse current.

## Adding a Guard example

A guard example should be reversible and safe:

- Show what is disabled before sleep and restored after wake.
- Avoid board-specific destructive operations.
- Do not modify fuses or permanent configuration.
- Explain whether the guard controls a power pin, ADC, radio, sensor, or custom peripheral.

## Measurement evidence guide

For measured-current evidence, include:

- Board, MCU, clock, Arduino core version, library version, and sketch.
- Power path and regulator details.
- Instruments used and sampling method.
- Active, sleep, report/radio, and full duty-cycle current results.
- Environmental assumptions and uncertainty.

## Profile confidence policy

Use these confidence levels consistently:

- `EcoProfileConfidence::PLACEHOLDER`: safe default or approximate value; not evidence.
- `EcoProfileConfidence::DATASHEET`: value derived from a datasheet under stated assumptions.
- `EcoProfileConfidence::MEASURED`: owner-side measurement with reproducible setup notes.

Do not mark a profile as measured unless the measurement method and conditions are documented.

## Diagnostics contributions

When adding a new Power Doctor warning, add or reuse a stable `EcoDiagnosticCode`. The printed text must be generated from the same diagnostic record so tests, dashboards, and human output stay consistent.

## Issue templates

Use the provided templates for bug reports, board profile requests, power measurement reports, and feature requests. For new hardware support, attach measurement notes when possible.
