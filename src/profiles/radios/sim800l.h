#ifndef ECOSENSE_PROFILES_RADIOS_SIM800L_H
#define ECOSENSE_PROFILES_RADIOS_SIM800L_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile SIM800L() {
  GenericRadioProfile p;
  p.txCurrent_uA(2000000UL)
    .rxCurrent_uA(20000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(500UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* SIM800LNotes() {
  return "SIM800L cellular placeholder. Transmit bursts can be very high; supply must handle peaks and GSM registration/TX dominates energy.";
}
}

#endif
