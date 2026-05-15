/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN4870_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN4870_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile RN4870BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(18000UL)
    .rxCurrent_uA(14000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* RN4870BLEName() {
  return "RN4870 BLE placeholder";
}

inline bool RN4870BLEMeasured() {
  return false;
}

inline const char* RN4870BLENotes() {
  return "RN4870 BLE module placeholder. Advertising/connection intervals, role, payload rate, TX power, and sleep state drive energy.";
}
}

#endif
