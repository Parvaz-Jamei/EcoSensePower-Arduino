/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC06_BLUETOOTH_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC06_BLUETOOTH_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HC06Bluetooth() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HC06BluetoothName() {
  return "HC-06 Bluetooth SPP placeholder";
}

inline bool HC06BluetoothMeasured() {
  return false;
}

inline const char* HC06BluetoothNotes() {
  return "HC-06 is a Bluetooth Classic SPP/UART bridge placeholder, not BLE. Idle and connected current can dominate small battery designs.";
}
}

#endif
