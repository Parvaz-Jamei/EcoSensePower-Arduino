#ifndef ECOSENSE_PROFILES_BATTERIES_LIPO_1S_H
#define ECOSENSE_PROFILES_BATTERIES_LIPO_1S_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiPo1S(uint32_t capacity_mAh = 1000UL) {
  return BatteryProfile::LiPo_1S(capacity_mAh);
}
}

#endif
