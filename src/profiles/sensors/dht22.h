#ifndef ECOSENSE_PROFILES_SENSORS_DHT22_H
#define ECOSENSE_PROFILES_SENSORS_DHT22_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile DHT22() {
  return EcoSensorProfile("DHT22 / AM2302", 2000UL, 1500UL, 50UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Slow sampling and timing-sensitive protocol; power-gating is recommended for battery nodes and module boards may add leakage.");
}
}

#endif
