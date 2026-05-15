#include "test_support.h"
#include "core/SensorProfile.h"
#include "profiles/sensors/bme280.h"
#include "profiles/sensors/dht22.h"
#include "profiles/sensors/ds18b20.h"
#include "profiles/sensors/generic_analog.h"
#include "profiles/sensors/hc_sr04.h"
#include "profiles/sensors/ina219.h"
#include "profiles/sensors/ldr_analog.h"
#include "profiles/sensors/mpu6050.h"
#include "profiles/sensors/pir_generic.h"
#include "profiles/sensors/scd30.h"
#include "profiles/sensors/soil_resistive.h"
static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validSensor(const EcoSensorProfile& p) {
  return validText(p.name) && validText(p.notes) && !p.measured &&
         p.confidence == EcoProfileConfidence::PLACEHOLDER;
}
int main() {
  ASSERT_TRUE(validSensor(EcoProfiles::GenericAnalogSensor()));
  ASSERT_TRUE(validSensor(EcoProfiles::DHT22()));
  ASSERT_TRUE(validSensor(EcoProfiles::DS18B20()));
  ASSERT_TRUE(validSensor(EcoProfiles::BME280()));
  ASSERT_TRUE(validSensor(EcoProfiles::HCSR04()));
  ASSERT_TRUE(validSensor(EcoProfiles::SoilResistive()));
  ASSERT_TRUE(validSensor(EcoProfiles::PIRGeneric()));
  ASSERT_TRUE(validSensor(EcoProfiles::MPU6050()));
  ASSERT_TRUE(validSensor(EcoProfiles::INA219()));
  ASSERT_TRUE(validSensor(EcoProfiles::SCD30()));
  ASSERT_TRUE(validSensor(EcoProfiles::LDRAnalog()));
  return 0;
}
