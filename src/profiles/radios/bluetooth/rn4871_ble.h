/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN4871_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN4871_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile RN4871BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(18000UL)
    .rxCurrent_uA(14000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* RN4871BLEName() {
  return "RN4871 BLE placeholder";
}

inline bool RN4871BLEMeasured() {
  return false;
}

inline const char* RN4871BLENotes() {
  return "RN4871 BLE module placeholder. Advertising interval, connection interval, role, and application payload cadence dominate energy.";
}
}

#endif
