#ifndef ECOSENSE_PROFILES_SENSORS_PIR_GENERIC_H
#define ECOSENSE_PROFILES_SENSORS_PIR_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile PIRGeneric() {
  return EcoSensorProfile("Generic PIR motion module", 30000UL, 150UL, 150UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. Quiescent current varies widely by module, regulator, retrigger mode, and warmup time.");
}
}

#endif
