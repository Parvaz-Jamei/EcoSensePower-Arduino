/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HM10_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HM10_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HM10BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(18000UL)
    .rxCurrent_uA(15000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HM10BLEName() {
  return "HM-10 BLE placeholder";
}

inline bool HM10BLEMeasured() {
  return false;
}

inline const char* HM10BLENotes() {
  return "HM-10 BLE placeholder commonly associated with CC2540/CC2541-class modules. Model BLE advertising interval, connection interval, role, payload frequency, and sleep pin behavior separately from HC-05/HC-06.";
}
}

#endif
