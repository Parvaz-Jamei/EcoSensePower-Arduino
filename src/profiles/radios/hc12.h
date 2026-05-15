#ifndef ECOSENSE_PROFILES_RADIOS_HC12_H
#define ECOSENSE_PROFILES_RADIOS_HC12_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HC12() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(16000UL)
    .sleepCurrent_uA(80UL)
    .fixedTxDurationMs(40UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HC12Notes() {
  return "HC-12 UART radio module placeholder. Sleep, transparent mode, FU mode, baud rate, and output power depend on module configuration.";
}
}

#endif
