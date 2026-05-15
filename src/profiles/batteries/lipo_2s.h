#ifndef ECOSENSE_PROFILES_BATTERIES_LIPO_2S_H
#define ECOSENSE_PROFILES_BATTERIES_LIPO_2S_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiPo2S(uint32_t capacity_mAh = 2200UL) {
  return BatteryProfile::LiPo_2S(capacity_mAh);
}
}

#endif
