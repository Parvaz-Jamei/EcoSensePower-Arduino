/*
  EcoSensePower SolarPoweredWeatherStation.

  Energy-harvesting and weather-node budget example. It demonstrates adaptive sampling
  and energy-aware behavior, not weather-sensor drivers, BLE/WiFi stacks, GPS parsers,
  or guaranteed battery-life calculations.

  Use real current measurements and site-specific solar/harvesting data before making
  deployment claims. Full demos target boards with enough SRAM/flash.
*/

#include <EcoSensePower.h>
#include <profiles/batteries/lifepo4_1s.h>
#include <profiles/boards/arduino_pro_mini_3v3.h>
#include <profiles/sensors/bme280.h>
#include <profiles/radios/sx1276_lora.h>

EcoSensePower node;
SolarHarvester solar;
GenericRadioProfile radio;

static float readTemperatureLikeValue() { return 23.5f; }
static void report(const EcoReport& r) { Serial.println(r.toText()); }

void setup() {
  Serial.begin(115200);
  EcoSensorProfile bme = EcoProfiles::BME280();
  radio = EcoProfiles::SX1276LoRa();
  solar.fixedMilliWatt(12.0f).storageEfficiencyPercent(65.0f);
  node.battery(EcoProfiles::LiFePO4_1S(1500))
      .board(EcoProfiles::ArduinoProMini3V3())
      .harvester(&solar)
      .radio(&radio)
      .onReport(report);
  node.energyPolicy().targetNeutralOperation(true).allowIntervalStretching(true);
  node.sensor(bme.name).read(readTemperatureLikeValue).warmupTimeMs(bme.warmupTimeMs).minIntervalMs(EcoTime::minutes(5)).maxIntervalMs(EcoTime::hours(1));
  node.begin();
}

void loop() { node.loop(); }
