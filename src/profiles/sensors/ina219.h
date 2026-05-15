#ifndef ECOSENSE_PROFILES_SENSORS_INA219_H
#define ECOSENSE_PROFILES_SENSORS_INA219_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile INA219() {
  return EcoSensorProfile("INA219 current/power monitor", 5UL, 1000UL, 1000UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. The monitor itself consumes energy; useful for calibration nodes and rail measurement, not free instrumentation.");
}
}

#endif
