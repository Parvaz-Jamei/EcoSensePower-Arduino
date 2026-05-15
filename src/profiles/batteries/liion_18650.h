#ifndef ECOSENSE_PROFILES_BATTERIES_LIION_18650_H
#define ECOSENSE_PROFILES_BATTERIES_LIION_18650_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiIon18650(uint32_t capacity_mAh = 3000UL) {
  return BatteryProfile::LiIon_18650(capacity_mAh);
}
}

#endif
