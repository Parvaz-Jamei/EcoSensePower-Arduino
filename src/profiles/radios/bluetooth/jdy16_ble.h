/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_JDY16_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_JDY16_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile JDY16BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(16000UL)
    .rxCurrent_uA(13000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* JDY16BLEName() {
  return "JDY-16 BLE placeholder";
}

inline bool JDY16BLEMeasured() {
  return false;
}

inline const char* JDY16BLENotes() {
  return "JDY-16 BLE module placeholder. BLE role, connection interval, advertising interval, and UART traffic dominate energy.";
}
}

#endif
