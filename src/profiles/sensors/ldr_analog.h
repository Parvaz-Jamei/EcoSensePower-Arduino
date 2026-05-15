#ifndef ECOSENSE_PROFILES_SENSORS_LDR_ANALOG_H
#define ECOSENSE_PROFILES_SENSORS_LDR_ANALOG_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile LDRAnalog() {
  return EcoSensorProfile("Analog LDR divider", 5UL, 1000UL, 1UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Voltage divider leakage can dominate sleep current; use high-value or switched divider for long battery life.");
}
}

#endif
