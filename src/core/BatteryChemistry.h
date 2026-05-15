#ifndef ECOSENSE_CORE_BATTERYCHEMISTRY_H
#define ECOSENSE_CORE_BATTERYCHEMISTRY_H

#include <stdint.h>

enum EcoBatteryChemistry : uint8_t {
  ECO_BATTERY_UNKNOWN = 0,
  ECO_BATTERY_ALKALINE_AA,
  ECO_BATTERY_NIMH_AA,
  ECO_BATTERY_LIPO_1S,
  ECO_BATTERY_LISOCL2_AA,
  ECO_BATTERY_LIPO_2S,
  ECO_BATTERY_LIION_18650,
  // Compatibility alias kept before v1.0.0: 18650 is a Li-ion cylindrical cell, not LiPo.
  ECO_BATTERY_LIPO_18650 = ECO_BATTERY_LIION_18650,
  ECO_BATTERY_CR2032,
  ECO_BATTERY_CR123A,
  ECO_BATTERY_LIFEPO4_1S,
  ECO_BATTERY_D_ALKALINE,
  ECO_BATTERY_LIPO_1S_400,
  ECO_BATTERY_NIMH_AAA
};

inline const char* ecoBatteryChemistryName(EcoBatteryChemistry chemistry) {
  switch (chemistry) {
    case ECO_BATTERY_ALKALINE_AA: return "AA alkaline";
    case ECO_BATTERY_NIMH_AA: return "NiMH AA";
    case ECO_BATTERY_LIPO_1S: return "LiPo 1S";
    case ECO_BATTERY_LISOCL2_AA: return "Li-SOCl2 AA";
    case ECO_BATTERY_LIPO_2S: return "LiPo 2S";
    case ECO_BATTERY_LIION_18650: return "Li-ion 18650";
    case ECO_BATTERY_CR2032: return "CR2032 lithium coin cell";
    case ECO_BATTERY_CR123A: return "CR123A lithium primary";
    case ECO_BATTERY_LIFEPO4_1S: return "LiFePO4 1S";
    case ECO_BATTERY_D_ALKALINE: return "D alkaline";
    case ECO_BATTERY_LIPO_1S_400: return "LiPo 1S 400mAh";
    case ECO_BATTERY_NIMH_AAA: return "NiMH AAA";
    case ECO_BATTERY_UNKNOWN:
    default: return "unknown";
  }
}

inline bool ecoBatteryHasFlatDischargeCurve(EcoBatteryChemistry chemistry) {
  return chemistry == ECO_BATTERY_LISOCL2_AA || chemistry == ECO_BATTERY_LIFEPO4_1S;
}

inline bool ecoBatteryHasPulseLimitations(EcoBatteryChemistry chemistry) {
  return chemistry == ECO_BATTERY_CR2032 || chemistry == ECO_BATTERY_CR123A;
}

inline bool ecoBatteryProtectionCircuitRecommended(EcoBatteryChemistry chemistry) {
  return chemistry == ECO_BATTERY_LIPO_1S || chemistry == ECO_BATTERY_LIPO_1S_400 ||
         chemistry == ECO_BATTERY_LIPO_2S || chemistry == ECO_BATTERY_LIION_18650 ||
         chemistry == ECO_BATTERY_LIFEPO4_1S;
}

#endif
