#ifndef ECOSENSE_PROFILES_SENSORS_SOIL_RESISTIVE_H
#define ECOSENSE_PROFILES_SENSORS_SOIL_RESISTIVE_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile SoilResistive() {
  return EcoSensorProfile("Resistive soil moisture probe", 20UL, 5000UL, 1UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Corrosion risk; energize only during measurement and calibrate for soil/probe geometry.");
}
}

#endif
