#ifndef ECOSENSE_PROFILES_SENSORS_GENERIC_ANALOG_H
#define ECOSENSE_PROFILES_SENSORS_GENERIC_ANALOG_H

#include "core/SensorProfile.h"
#include <stdint.h>

struct EcoGenericAnalogSensorProfile {
  const char* name;
  uint32_t warmupTimeMs;
  uint32_t readCurrent_uA;
  bool measured;
  const char* notes;
};

namespace EcoProfiles {
inline EcoGenericAnalogSensorProfile GenericAnalogSensorLegacy() {
  EcoGenericAnalogSensorProfile p = {"Generic analog sensor", 20UL, 3000UL, false, "Placeholder. Replace current and warmup with measured sensor data."};
  return p;
}

inline EcoSensorProfile GenericAnalogSensor() {
  return EcoSensorProfile("Generic analog sensor", 20UL, 3000UL, 1UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder. Replace current, divider leakage, warmup, and sleep current with measured sensor data.");
}
}

#endif
