#ifndef ECOSENSE_PROFILE_BATTERY_NIMH_AA_H
#define ECOSENSE_PROFILE_BATTERY_NIMH_AA_H
#include "core/BatteryProfile.h"
namespace EcoBatteryProfiles {
inline BatteryProfile NiMH_AA(uint32_t capacity_mAh = 2000UL) { return BatteryProfile::NiMH_AA(capacity_mAh); }
}
namespace EcoProfiles {
inline BatteryProfile NiMH_AA(uint32_t capacity_mAh = 2000UL) { return EcoBatteryProfiles::NiMH_AA(capacity_mAh); }
}
#endif
