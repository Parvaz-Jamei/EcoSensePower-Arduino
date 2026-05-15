#ifndef ECOSENSE_PROFILE_BATTERY_LISO_CL2_AA_H
#define ECOSENSE_PROFILE_BATTERY_LISO_CL2_AA_H
#include "core/BatteryProfile.h"
namespace EcoBatteryProfiles {
inline BatteryProfile LiSOCl2_AA(uint32_t capacity_mAh = 2400UL) { return BatteryProfile::LiSOCl2_AA(capacity_mAh); }
}
namespace EcoProfiles {
inline BatteryProfile LiSOCl2_AA(uint32_t capacity_mAh = 2400UL) { return EcoBatteryProfiles::LiSOCl2_AA(capacity_mAh); }
}
#endif
