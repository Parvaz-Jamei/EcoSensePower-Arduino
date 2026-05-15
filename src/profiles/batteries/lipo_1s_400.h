#ifndef ECOSENSE_PROFILES_BATTERIES_LIPO_1S_400_H
#define ECOSENSE_PROFILES_BATTERIES_LIPO_1S_400_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiPo1S400(uint32_t capacity_mAh = 400UL) {
  return BatteryProfile::LiPo_1S_400(capacity_mAh);
}
}

#endif
