/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC02_BLUETOOTH_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC02_BLUETOOTH_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HC02Bluetooth() {
  GenericRadioProfile p;
  p.txCurrent_uA(30000UL)
    .rxCurrent_uA(22000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HC02BluetoothName() {
  return "HC-02 Bluetooth placeholder";
}

inline bool HC02BluetoothMeasured() {
  return false;
}

inline const char* HC02BluetoothNotes() {
  return "HC-02-style UART Bluetooth placeholder. Treat module idle/connected state and UART traffic as first-order energy drivers.";
}
}

#endif
