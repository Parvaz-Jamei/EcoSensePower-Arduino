#ifndef ECOSENSE_PROFILES_SENSORS_SCD30_H
#define ECOSENSE_PROFILES_SENSORS_SCD30_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile SCD30() {
  return EcoSensorProfile("SCD30 CO2 sensor", 2000UL, 19000UL, 1000UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. CO2 sensing is not ultra-low-power; duty-cycle carefully and validate warmup/measurement interval.");
}
}

#endif
