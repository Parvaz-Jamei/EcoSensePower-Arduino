# Supported Boards and Compile-Readiness

EcoSensePower is designed for Arduino-style sensor nodes with dependency-light C++ code. Current support tiers are intentionally conservative:

| Tier | Meaning |
|---|---|
| Runtime backend | The library has target-specific runtime/sleep/peripheral behavior. |
| Guarded compile-readiness | The library exposes guarded headers/placeholders and should compile when the platform provides compatible Arduino APIs, but runtime low-power behavior is not fully claimed. |
| Profile-only | The library includes a board current profile as a modeling starting point only. |

## SRAM-aware support tiers

| Tier | Boards | Default support |
|---|---|---|
| Tier 1A — AVR UNO/Nano Tiny Core | ATmega328P UNO/Nano-class boards | Basic adaptive sensor runtime, one sensor by default, compact reports, diagnostics/ledger records/SoC storage disabled by default |
| Tier 1B — larger AVR | Arduino Mega / larger AVR-compatible boards | More SRAM; users may enable diagnostics, ledger records, larger registries, and profile-heavy examples with macros |
| Tier 2 — larger Arduino-compatible boards | ESP32, SAMD, ARM-class targets | Full runtime features, profile catalog, radio/harvester examples, diagnostics, and advanced examples |

UNO/Nano support is intentionally scoped to a compact core gate. Full ecosystem examples remain in the package but target boards with more SRAM.

## Current support positioning

- AVR and ESP32 have runtime backends.
- Selected ARM-style Arduino targets have guarded compile-readiness/fallback paths.
- Board profiles are placeholders unless measured on the exact board/module variant.

## Board profile catalog

Profiles include Arduino Nano, Pro Mini 3.3V/5V, Mega, Nano Every, MKR WAN, ESP32 DevKit, ESP32-WROOM module, ESP8266 NodeMCU, ATtiny85, and Raspberry Pi Pico/RP2040 placeholder.

Board-level current may be dominated by regulator, USB bridge, power LED, onboard peripherals, wake-source wiring, and attached modules. Do not use profile-only values for battery-life guarantees.

## Bluetooth/GPS examples and AVR scope

Bluetooth/BLE and GPS/GNSS profile examples are dependency-free modeling examples by default, but they are not part of the AVR UNO/Nano smoke gate. AVR UNO/Nano remains Tier 1A compact core support. Full wireless/GNSS ecosystem examples target boards with more SRAM/flash such as ESP32, SAMD, Mega, Nano 33 BLE-class boards, Portenta, Giga, and similar boards.
