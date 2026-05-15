#ifndef ECOSENSE_PROFILES_BATTERIES_LIFEPO4_1S_H
#define ECOSENSE_PROFILES_BATTERIES_LIFEPO4_1S_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile LiFePO4_1S(uint32_t capacity_mAh = 1500UL) {
  return BatteryProfile::LiFePO4_1S(capacity_mAh);
}
}

#endif
