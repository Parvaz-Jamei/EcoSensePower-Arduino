/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN42_BLUETOOTH_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_RN42_BLUETOOTH_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile RN42Bluetooth() {
  GenericRadioProfile p;
  p.txCurrent_uA(45000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(500UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* RN42BluetoothName() {
  return "RN42 Bluetooth SPP placeholder";
}

inline bool RN42BluetoothMeasured() {
  return false;
}

inline const char* RN42BluetoothNotes() {
  return "RN42 Bluetooth Classic module placeholder. SPP connection state, discoverability, UART traffic, and sleep mode configuration dominate current.";
}
}

#endif
