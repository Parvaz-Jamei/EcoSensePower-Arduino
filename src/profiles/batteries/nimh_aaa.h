#ifndef ECOSENSE_PROFILES_BATTERIES_NIMH_AAA_H
#define ECOSENSE_PROFILES_BATTERIES_NIMH_AAA_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile NiMHAAA(uint32_t capacity_mAh = 800UL) {
  return BatteryProfile::NiMH_AAA(capacity_mAh);
}
}

#endif
