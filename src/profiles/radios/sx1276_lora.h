#ifndef ECOSENSE_PROFILES_RADIOS_SX1276_LORA_H
#define ECOSENSE_PROFILES_RADIOS_SX1276_LORA_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile SX1276LoRa() {
  GenericRadioProfile p;
  p.txCurrent_uA(120000UL)
    .rxCurrent_uA(12000UL)
    .sleepCurrent_uA(1UL)
    .fixedTxDurationMs(120UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* SX1276LoRaNotes() {
  return "SX1276/SX127x LoRa placeholder. TX depends on output power, spreading factor, bandwidth, coding rate, payload length, antenna, and duty cycle.";
}
}

#endif
