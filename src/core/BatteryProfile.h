#ifndef ECOSENSE_CORE_BATTERYPROFILE_H
#define ECOSENSE_CORE_BATTERYPROFILE_H

#include "core/EcoTypes.h"
#include "core/BatteryChemistry.h"
#include <stdint.h>

struct BatteryProfile {
  const char* name;
  uint32_t capacity_mAh;
  float nominalVoltageV;
  bool measured;
  const char* notes;
  EcoProfileConfidence confidence;
  EcoBatteryChemistry chemistry;
  float regulatorIq_uA;

  BatteryProfile(const char* profileName = "AA alkaline",
                 uint32_t capacity = 2400UL,
                 float voltage = 1.5f,
                 bool isMeasured = false,
                 const char* profileNotes = "Nominal placeholder.",
                 EcoProfileConfidence profileConfidence = EcoProfileConfidence::PLACEHOLDER,
                 EcoBatteryChemistry batteryChemistry = ECO_BATTERY_UNKNOWN,
                 float regulatorIq = -1.0f)
    : name(profileName), capacity_mAh(capacity), nominalVoltageV(voltage), measured(isMeasured),
      notes(profileNotes), confidence(ecoNormalizeProfileConfidence(isMeasured, profileConfidence)),
      chemistry(batteryChemistry), regulatorIq_uA(regulatorIq) {}

  static BatteryProfile AA_Alkaline(uint32_t capacity_mAh = 2400UL) {
    return BatteryProfile("AA alkaline", capacity_mAh, 1.5f, false,
                          "Nominal placeholder. Capacity depends on load, temperature, cutoff voltage, and cell brand.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_ALKALINE_AA);
  }

  static BatteryProfile LiPo_1S(uint32_t capacity_mAh = 1000UL) {
    return BatteryProfile("LiPo 1S", capacity_mAh, 3.7f, false,
                          "Placeholder profile. Add charger, regulator, protection-circuit current, cutoff voltage, and load evidence before runtime claims.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIPO_1S);
  }

  static BatteryProfile NiMH_AA(uint32_t capacity_mAh = 2000UL) {
    return BatteryProfile("NiMH AA", capacity_mAh, 1.2f, false,
                          "Nominal placeholder. Voltage curve and usable capacity depend on discharge rate, self-discharge, age, temperature, and cutoff voltage.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_NIMH_AA);
  }

  static BatteryProfile LiSOCl2_AA(uint32_t capacity_mAh = 2400UL) {
    return BatteryProfile("Li-SOCl2 AA", capacity_mAh, 3.6f, false,
                          "Nominal placeholder. Flat discharge curve makes voltage-only SoC low-confidence without calibration or coulomb evidence.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LISOCL2_AA);
  }

  static BatteryProfile LiPo_2S(uint32_t capacity_mAh = 2200UL) {
    return BatteryProfile("LiPo 2S", capacity_mAh, 7.4f, false,
                          "Placeholder profile. Pack protection, regulator efficiency/current, cutoff voltage, discharge rating, balance state, and load profile dominate usable runtime.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIPO_2S);
  }

  static BatteryProfile LiPo_1S_400(uint32_t capacity_mAh = 400UL) {
    return BatteryProfile("LiPo 1S 400mAh", capacity_mAh, 3.7f, false,
                          "Placeholder profile for small wearable/sensor packs. High pulse or radio load can reduce usable runtime; include protection/charger/regulator current.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIPO_1S_400);
  }

  static BatteryProfile CR2032(uint32_t capacity_mAh = 235UL) {
    return BatteryProfile("CR2032", capacity_mAh, 3.0f, false,
                          "Placeholder profile. Coin cells are suitable for low current only; pulse current, cutoff voltage, temperature, holder resistance, and load profile strongly affect usable capacity.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_CR2032);
  }

  static BatteryProfile CR123A(uint32_t capacity_mAh = 1500UL) {
    return BatteryProfile("CR123A lithium primary", capacity_mAh, 3.0f, false,
                          "Placeholder profile. Common in camera/security sensors; usable capacity depends on pulse load, temperature, cutoff voltage, and cell vendor.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_CR123A);
  }

  static BatteryProfile D_Alkaline(uint32_t capacity_mAh = 12000UL) {
    return BatteryProfile("D alkaline", capacity_mAh, 1.5f, false,
                          "Placeholder high-capacity alkaline profile. Capacity is highly brand-, load-, temperature-, and cutoff-voltage-dependent.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_D_ALKALINE);
  }

  static BatteryProfile LiIon_18650(uint32_t capacity_mAh = 3000UL) {
    return BatteryProfile("Li-ion 18650", capacity_mAh, 3.7f, false,
                          "Placeholder profile. Distinguish protected versus unprotected cells and include charger/protection/regulator behavior before runtime claims.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIION_18650);
  }

  static BatteryProfile LiPo_2S_2000(uint32_t capacity_mAh = 2000UL) {
    return BatteryProfile("LiPo 2S 2000mAh", capacity_mAh, 7.4f, false,
                          "Placeholder profile. Pack protection, regulator boundary, cutoff voltage, discharge rate, and balance state must be documented for measured claims.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIPO_2S);
  }

  static BatteryProfile NiMH_AAA(uint32_t capacity_mAh = 800UL) {
    return BatteryProfile("NiMH AAA", capacity_mAh, 1.2f, false,
                          "Placeholder profile. Self-discharge, age, discharge rate, temperature, and cutoff voltage strongly affect small-cell runtime.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_NIMH_AAA);
  }

  static BatteryProfile LiFePO4_1S(uint32_t capacity_mAh = 1500UL) {
    return BatteryProfile("LiFePO4 1S", capacity_mAh, 3.2f, false,
                          "Placeholder profile. Safer chemistry and solar-friendly use, but flat discharge curve makes voltage-only SoC low-confidence without calibration or coulomb evidence.",
                          EcoProfileConfidence::PLACEHOLDER, ECO_BATTERY_LIFEPO4_1S);
  }
};

#endif
