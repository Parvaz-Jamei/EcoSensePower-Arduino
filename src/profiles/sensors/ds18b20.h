#ifndef ECOSENSE_PROFILES_SENSORS_DS18B20_H
#define ECOSENSE_PROFILES_SENSORS_DS18B20_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile DS18B20() {
  return EcoSensorProfile("DS18B20 1-Wire temperature", 750UL, 1500UL, 1UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Conversion time depends on resolution; parasite power and pullup design affect current and reliability.");
}
}

#endif
