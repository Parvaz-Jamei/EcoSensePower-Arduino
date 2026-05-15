#ifndef ECOSENSE_PROFILES_BATTERIES_CR123A_H
#define ECOSENSE_PROFILES_BATTERIES_CR123A_H

#include "core/BatteryProfile.h"

namespace EcoProfiles {
inline BatteryProfile CR123A(uint32_t capacity_mAh = 1500UL) {
  return BatteryProfile::CR123A(capacity_mAh);
}
}

#endif
