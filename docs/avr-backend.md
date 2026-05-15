# AVR Backend v2

The AVR backend is conservative by default. It keeps AVR code behind `ARDUINO_ARCH_AVR` guards and keeps `<avr/sleep.h>`, `<avr/power.h>`, and `<avr/wdt.h>` inside `src/arch/avr`.

## Timed sleep path

`AvrSleepBackend::sleepFor(ms)` is intentionally timed-IDLE based. EcoSensePower does **not** use power-down as a timed scheduler because Arduino `millis()` may not advance in power-down depending on the wake source and timer configuration.

This keeps timed runtime sleeps predictable for Arduino sketches while still allowing applications to opt into deeper sleep explicitly.

## Explicit power-down path

`powerDownOnce()` is an explicit one-shot API. It is application-owned:

- the wake source must be configured by the sketch,
- watchdog chaining is not provided by EcoSensePower in this release,
- fuse manipulation is not performed,
- BOD manipulation remains disabled by default,
- the sketch owner must validate timing and current on real hardware.

Defining `ECOSENSE_AVR_ENABLE_POWERDOWN` enables the one-shot power-down implementation, but `sleepFor(ms)` still remains IDLE-based.

## Peripheral guard

`AvrPeripheralGuard` can disable and restore ADC state. SPI, I2C, and UART remain application-owned unless the sketch uses explicit reversible callbacks through `node.guard()`.

## Limitations

AVR behavior depends on wake source, watchdog configuration, board wiring, regulator, and active peripherals. EcoSensePower does not guarantee measured current without hardware validation.
