#ifndef ECOSENSE_PROFILES_RADIOS_RFM95W_H
#define ECOSENSE_PROFILES_RADIOS_RFM95W_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile RFM95W() {
  GenericRadioProfile p;
  p.txCurrent_uA(120000UL)
    .rxCurrent_uA(12000UL)
    .sleepCurrent_uA(1UL)
    .fixedTxDurationMs(120UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* RFM95WNotes() {
  return "RFM95W module placeholder around SX127x silicon. Module board sleep current and regulator leakage may differ from transceiver-only values.";
}
}

#endif
