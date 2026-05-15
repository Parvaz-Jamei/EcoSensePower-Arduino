#ifndef ECOSENSE_PROFILES_RADIOS_NRF24L01_H
#define ECOSENSE_PROFILES_RADIOS_NRF24L01_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile NRF24L01() {
  GenericRadioProfile p;
  p.txCurrent_uA(11500UL)
    .rxCurrent_uA(12300UL)
    .sleepCurrent_uA(1UL)
    .fixedTxDurationMs(5UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* NRF24L01Notes() {
  return "nRF24L01/nRF24L01+ placeholder. PA/LNA modules, data rate, retries, and supply quality can change energy dramatically.";
}
}

#endif
