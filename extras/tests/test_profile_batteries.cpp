#include "test_support.h"
#include "core/BatteryProfile.h"
#include "profiles/batteries/aa_alkaline.h"
#include "profiles/batteries/cr123a.h"
#include "profiles/batteries/cr2032.h"
#include "profiles/batteries/d_alkaline.h"
#include "profiles/batteries/lifepo4_1s.h"
#include "profiles/batteries/liion_18650.h"
#include "profiles/batteries/lipo_1s.h"
#include "profiles/batteries/lipo_1s_400.h"
#include "profiles/batteries/lipo_2s.h"
#include "profiles/batteries/lipo_2s_2000.h"
#include "profiles/batteries/liso_cl2_aa.h"
#include "profiles/batteries/nimh_aa.h"
#include "profiles/batteries/nimh_aaa.h"

static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validBattery(const BatteryProfile& p, EcoBatteryChemistry expected) {
  return validText(p.name) && validText(p.notes) && p.capacity_mAh > 0UL &&
         p.nominalVoltageV > 0.0f && !p.measured &&
         p.confidence == EcoProfileConfidence::PLACEHOLDER &&
         p.chemistry == expected && p.chemistry != ECO_BATTERY_UNKNOWN;
}
int main() {
  ASSERT_TRUE(validBattery(EcoProfiles::AAAlkaline(), ECO_BATTERY_ALKALINE_AA));
  ASSERT_TRUE(validBattery(EcoProfiles::LiPo1S(), ECO_BATTERY_LIPO_1S));
  ASSERT_TRUE(validBattery(EcoProfiles::LiPo2S(), ECO_BATTERY_LIPO_2S));
  ASSERT_TRUE(validBattery(EcoProfiles::LiPo1S400(), ECO_BATTERY_LIPO_1S_400));
  ASSERT_TRUE(validBattery(EcoProfiles::CR2032(), ECO_BATTERY_CR2032));
  ASSERT_TRUE(validBattery(EcoProfiles::CR123A(), ECO_BATTERY_CR123A));
  ASSERT_TRUE(validBattery(EcoProfiles::DAlkaline(), ECO_BATTERY_D_ALKALINE));
  ASSERT_TRUE(validBattery(EcoProfiles::LiIon18650(), ECO_BATTERY_LIION_18650));
  ASSERT_TRUE(ECO_BATTERY_LIPO_18650 == ECO_BATTERY_LIION_18650);
  ASSERT_TRUE(validBattery(EcoProfiles::LiPo2S2000(), ECO_BATTERY_LIPO_2S));
  ASSERT_TRUE(validBattery(EcoProfiles::NiMHAAA(), ECO_BATTERY_NIMH_AAA));
  ASSERT_TRUE(validBattery(EcoProfiles::LiFePO4_1S(), ECO_BATTERY_LIFEPO4_1S));
  ASSERT_TRUE(validBattery(EcoProfiles::NiMH_AA(), ECO_BATTERY_NIMH_AA));
  ASSERT_TRUE(validBattery(EcoProfiles::LiSOCl2_AA(), ECO_BATTERY_LISOCL2_AA));
  return 0;
}
