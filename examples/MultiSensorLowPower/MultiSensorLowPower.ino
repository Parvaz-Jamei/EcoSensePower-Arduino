/*
  EcoSensePower MultiSensorLowPower.

  Multi-sensor energy-budget example. It demonstrates profile-based planning and
  adaptive scheduling; it is not a sensor-driver collection, BLE/WiFi stack, GPS parser,
  or RTOS.

  Default build is dependency-free. On AVR UNO/Nano, use compact core examples first;
  full multi-sensor demos target larger boards.
*/

#include <EcoSensePower.h>
#include <profiles/batteries/cr123a.h>
#include <profiles/boards/attiny85.h>
#include <profiles/sensors/ds18b20.h>
#include <profiles/sensors/ldr_analog.h>
#include <profiles/sensors/soil_resistive.h>

EcoSensePower node;
static float readTemperature() { return 18.0f; }
static float readLight() { return 512.0f; }
static float readSoil() { return 420.0f; }

void setup() {
  Serial.begin(115200);
  node.battery(EcoProfiles::CR123A()).board(EcoProfiles::ATtiny85());
  EcoSensorProfile temp = EcoProfiles::DS18B20();
  EcoSensorProfile light = EcoProfiles::LDRAnalog();
  EcoSensorProfile soil = EcoProfiles::SoilResistive();
  node.sensor(temp.name).read(readTemperature).priority(ECO_HIGH).minIntervalMs(EcoTime::minutes(5)).maxIntervalMs(EcoTime::hours(6));
  node.sensor(light.name).read(readLight).priority(ECO_LOW).minIntervalMs(EcoTime::minutes(10)).maxIntervalMs(EcoTime::hours(12));
  node.sensor(soil.name).read(readSoil).priority(ECO_NORMAL).minIntervalMs(EcoTime::hours(1)).maxIntervalMs(EcoTime::days(1));
  node.begin();
}

void loop() { node.loop(); }
