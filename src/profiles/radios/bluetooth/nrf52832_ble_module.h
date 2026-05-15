/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52832_BLE_MODULE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52832_BLE_MODULE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile NRF52832BLEModule() {
  GenericRadioProfile p;
  p.txCurrent_uA(12000UL)
    .rxCurrent_uA(8000UL)
    .sleepCurrent_uA(5UL)
    .fixedTxDurationMs(20UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* NRF52832BLEModuleName() {
  return "nRF52832 BLE module placeholder";
}

inline bool NRF52832BLEModuleMeasured() {
  return false;
}

inline const char* NRF52832BLEModuleNotes() {
  return "nRF52832 BLE module placeholder. Current depends on module board, DC/DC setup, connection/advertising interval, TX power, and sleep configuration.";
}
}

#endif
