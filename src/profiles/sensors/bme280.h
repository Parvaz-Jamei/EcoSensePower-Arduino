#ifndef ECOSENSE_PROFILES_SENSORS_BME280_H
#define ECOSENSE_PROFILES_SENSORS_BME280_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile BME280() {
  return EcoSensorProfile("BME280 environmental sensor", 10UL, 700UL, 1UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Forced mode/sleep mode are suitable for low-power weather nodes; breakout regulator and pullups may dominate sleep current.");
}
}

#endif
