/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BL652_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BL652_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BL652BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(14000UL)
    .rxCurrent_uA(9000UL)
    .sleepCurrent_uA(5UL)
    .fixedTxDurationMs(20UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BL652BLEName() {
  return "BL652 BLE placeholder";
}

inline bool BL652BLEMeasured() {
  return false;
}

inline const char* BL652BLENotes() {
  return "BL652 BLE module placeholder. Treat firmware, role, radio interval, TX power, and board regulator as application-specific.";
}
}

#endif
