# Library Manager Checklist

- [x] Repository name: EcoSensePower-Arduino
- [x] Library name: EcoSensePower
- [x] Public header: `src/EcoSensePower.h`
- [x] Main class: `EcoSensePower`
- [x] `library.properties` in root
- [x] `version=0.9.10`
- [x] SemVer-compatible version format
- [x] `includes=EcoSensePower.h`
- [x] `architectures=*` with support matrix clarifying backend status
- [x] No `.development` file
- [x] No `.exe` files
- [x] No symlinks
- [x] No mandatory external dependency
- [x] Independent examples
- [x] License present
- [x] CONTRIBUTING.md present
- [x] Issue templates present
- [x] Optional harvesting interface present without mandatory dependency
- [x] Arduino Lint strict workflow configured
- [x] Arduino compile matrix workflow configured
- [x] Host logic test workflow configured
- [x] Example mock compile script configured
- [ ] Real Arduino Lint strict output attached
- [ ] Real Arduino CLI / compile-sketches output attached

GitHub About:

Energy-aware adaptive runtime for battery-powered Arduino and IoT sensor nodes: adaptive sampling, sleep orchestration, energy budgets, diagnostics, confidence-bounded sensor/radio/Bluetooth/GPS profiles, and AVR/ESP32/SAMD compile-readiness paths.

Topics:

`arduino`, `arduino-library`, `low-power`, `ultra-low-power`, `battery-powered`, `sensor-node`, `iot`, `embedded`, `power-management`, `energy-aware`, `adaptive-sampling`, `sleep-mode`, `energy-harvesting`, `avr`, `esp32`, `samd`, `bluetooth`, `ble`, `gps`, `gnss`, `lora`, `tinyml`


## Current release-candidate boundary

It contains the current modular scientific/industrial capability set while keeping the core Arduino-friendly and dependency-light. Phase 4.4.11 is a tiny final public polish package before RC evidence. Public release remains blocked until real Arduino Lint and Arduino board compile evidence are attached.


## Current release-candidate status

- `library.properties` version: `0.9.10` (Phase 4.4.11 Tiny Final Public Polish / pre-v1.0.0-rc1 package until real Arduino ecosystem evidence passes).
- Public `v1.0.0` or Library Manager submission remains blocked until real Arduino Lint strict and Arduino compile evidence are attached.
- Host logic tests are useful but do not replace Arduino CLI compile or Arduino Lint compliance.
