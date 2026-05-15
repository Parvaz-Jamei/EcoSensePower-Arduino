/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52840_BLE_MODULE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52840_BLE_MODULE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile NRF52840BLEModule() {
  GenericRadioProfile p;
  p.txCurrent_uA(14000UL)
    .rxCurrent_uA(9000UL)
    .sleepCurrent_uA(5UL)
    .fixedTxDurationMs(20UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* NRF52840BLEModuleName() {
  return "nRF52840 BLE module placeholder";
}

inline bool NRF52840BLEModuleMeasured() {
  return false;
}

inline const char* NRF52840BLEModuleNotes() {
  return "nRF52840 BLE module placeholder. Board overhead, USB/regulator state, role, advertising/connection interval, and TX power dominate.";
}
}

#endif
