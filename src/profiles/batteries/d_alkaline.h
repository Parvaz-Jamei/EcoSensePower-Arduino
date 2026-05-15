#ifndef ECOSENSE_PROFILES_BATTERIES_D_ALKALINE_H
#define ECOSENSE_PROFILES_BATTERIES_D_ALKALINE_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile DAlkaline(uint32_t capacity_mAh = 12000UL) {
  return BatteryProfile::D_Alkaline(capacity_mAh);
}
}

#endif
