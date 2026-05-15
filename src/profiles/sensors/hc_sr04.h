#ifndef ECOSENSE_PROFILES_SENSORS_HC_SR04_H
#define ECOSENSE_PROFILES_SENSORS_HC_SR04_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile HCSR04() {
  return EcoSensorProfile("HC-SR04 ultrasonic module", 60UL, 15000UL, 5UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Relatively high active current and module leakage; power-gating is recommended for low-power operation.");
}
}

#endif
