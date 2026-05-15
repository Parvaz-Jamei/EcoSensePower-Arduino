/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC05_BLUETOOTH_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_HC05_BLUETOOTH_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile HC05Bluetooth() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* HC05BluetoothName() {
  return "HC-05 Bluetooth SPP placeholder";
}

inline bool HC05BluetoothMeasured() {
  return false;
}

inline const char* HC05BluetoothNotes() {
  return "HC-05 is a Bluetooth Classic SPP/UART bridge placeholder, not BLE. Idle, pairing, connected state, UART traffic, and EN/KEY pin handling dominate energy.";
}
}

#endif
