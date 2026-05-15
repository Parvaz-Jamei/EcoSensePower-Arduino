/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HM11_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HM11_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HM11BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(18000UL)
    .rxCurrent_uA(15000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HM11BLEName() {
  return "HM-11 BLE placeholder";
}

inline bool HM11BLEMeasured() {
  return false;
}

inline const char* HM11BLENotes() {
  return "HM-11 BLE placeholder. BLE advertising/connection interval, role, TX power, and module sleep mode dominate energy.";
}
}

#endif
