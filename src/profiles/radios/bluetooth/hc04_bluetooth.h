/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC04_BLUETOOTH_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC04_BLUETOOTH_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HC04Bluetooth() {
  GenericRadioProfile p;
  p.txCurrent_uA(35000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HC04BluetoothName() {
  return "HC-04 Bluetooth placeholder";
}

inline bool HC04BluetoothMeasured() {
  return false;
}

inline const char* HC04BluetoothNotes() {
  return "HC-04-style Bluetooth UART bridge placeholder. Not a BLE profile; validate module variant before battery-life claims.";
}
}

#endif
