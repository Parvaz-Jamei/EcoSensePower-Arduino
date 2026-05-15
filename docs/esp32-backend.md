# ESP32 Backend v1

ESP32 backend v1 adds guarded light/deep sleep methods while keeping Wi-Fi/Bluetooth dependencies out of the EcoSensePower core.

## Backend API

`Esp32SleepBackend` provides:

- `lightSleepFor(ms)`
- `deepSleepFor(ms)`
- `wakeCauseName()`
- `isRealSleep()`

## Wireless guard

ESP32 Wi-Fi/Bluetooth must be stopped by the application before entering light/deep sleep when used. EcoSensePower provides diagnostics and guard hooks, but does not force Wi-Fi/BLE dependencies into the core.

```cpp
node.guard("esp32-wireless")
  .esp32Wireless(true)
  .onSleep([]() {
    // Stop application-owned Wi-Fi/Bluetooth here if used.
  });
```

## Device variants

ESP32-C3/S3 and other variants are not overclaimed. They are experimental until compile and owner-side hardware validation evidence exists.
