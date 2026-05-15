#ifndef ECOSENSE_PROFILES_BATTERIES_LIPO_2S_2000_H
#define ECOSENSE_PROFILES_BATTERIES_LIPO_2S_2000_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiPo2S2000(uint32_t capacity_mAh = 2000UL) {
  return BatteryProfile::LiPo_2S_2000(capacity_mAh);
}
}

#endif
