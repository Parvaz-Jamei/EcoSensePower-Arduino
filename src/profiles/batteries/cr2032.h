#ifndef ECOSENSE_PROFILES_BATTERIES_CR2032_H
#define ECOSENSE_PROFILES_BATTERIES_CR2032_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile CR2032(uint32_t capacity_mAh = 235UL) {
  return BatteryProfile::CR2032(capacity_mAh);
}
}

#endif
