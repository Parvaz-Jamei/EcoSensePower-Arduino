#ifndef ECOSENSE_PROFILES_BATTERIES_AA_ALKALINE_H
#define ECOSENSE_PROFILES_BATTERIES_AA_ALKALINE_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile AAAlkaline(uint32_t capacity_mAh = 2400UL) {
  return BatteryProfile::AA_Alkaline(capacity_mAh);
}
}

#endif
