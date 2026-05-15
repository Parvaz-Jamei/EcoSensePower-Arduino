# Research Notes

Phase 4 research summary. Sources are used for compatibility and design grounding, not for copying code or API design.

## Arduino Library Specification

Arduino Library Specification defines `library.properties`, `src/`, examples, `architectures`, and `includes`. Source files under `src` and its subfolders are compiled recursively, but only `src` is added to the include search path. `EcoSensePower.h` therefore remains the public header in `src/`.

Source: https://docs.arduino.cc/arduino-cli/library-specification/

## Arduino Lint

Arduino Lint checks structure, metadata, configuration, Library Manager submission requirements, and best practices. The CI configuration keeps `library-manager: submit` and `compliance: strict` in CI. Arduino Lint is not a substitute for compile tests or runtime logic tests.

Source: https://arduino.github.io/arduino-lint/dev/

## Arduino Compile CI

`arduino/compile-sketches` checks whether Arduino sketches compile and produces compile reports. Compile pass is not functional proof, but compile failure is a hard signal for package quality. The CI configuration keeps a compile matrix plus a simple AVR CLI workflow as a fallback/evidence path.

Source: https://github.com/arduino/compile-sketches

## GitHub Actions Checkout

`actions/checkout@v6` is used because the official checkout action documents v6 and improved credential storage behavior. Workflows also use `permissions: contents: read`.

Source: https://github.com/actions/checkout

## AVR Sleep

ATmega328P sleep modes are selected by SM2/SM1/SM0 bits in SMCR. Modes include Idle, ADC Noise Reduction, Power-down, Power-save, Standby, and Extended Standby. Enabled interrupts can wake the MCU from sleep.

Source: Microchip ATmega328P documentation, Sleep Modes section.

## ESP32 Sleep

ESP-IDF documentation states Wi-Fi/Bluetooth peripherals are powered down in light/deep sleep and applications must disable Wi-Fi/Bluetooth using appropriate calls before entering sleep. EcoSensePower therefore provides wireless guard hooks and diagnostics without forcing dependencies into core.

Source: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html

## SAMD/nRF52 Direction

The official Arduino Low Power library provides power-save primitives for SAMD and nRF52 32-bit boards. EcoSensePower should remain runtime-level and may integrate optional backend adapters later.

Source: https://docs.arduino.cc/libraries/arduino-low-power/

## Radio/LoRa Direction

RadioLib is a universal wireless communication library for embedded devices and covers SX126x, SX127x, SX128x and other modules/protocols. EcoSensePower should not rewrite a radio stack and must keep radio support optional.

Source: https://jgromes.github.io/RadioLib/

## Energy Model Direction

LoRa/LoRaWAN energy modeling literature commonly separates energy by sensor-node units and states such as sensing, processing, transmission, reception, and sleep. EcoSensePower keeps a state-based model and conservative claims.

Example source: https://pmc.ncbi.nlm.nih.gov/articles/PMC6068831/

## License and no-copy rule

No code, API shape, tests, examples, text, tables, or recognizable implementation from other projects is copied. External projects are used only for research and sanity checks.


## Added research grounding

- SoC tracking is estimate-only. Voltage-only SoC is low-confidence for flat-discharge chemistries such as Li-SOCl2, so EcoSensePower marks flat-curve warnings and confidence levels.
- Energy harvesting support is policy/model based. Energy-neutral mode is a target, not a perpetual-operation guarantee.
- Radio energy is modeled as state/task energy (TX/RX/sleep), not as a radio stack replacement.
- TinyML hooks are optional and dependency-free; application-owned inference frameworks stay outside the core.
