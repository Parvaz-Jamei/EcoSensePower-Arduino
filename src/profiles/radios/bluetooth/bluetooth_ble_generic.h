/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_BLE_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_BLE_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothBLEGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(15000UL)
    .rxCurrent_uA(12000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothBLEGenericName() {
  return "Bluetooth BLE generic placeholder";
}

inline bool BluetoothBLEGenericMeasured() {
  return false;
}

inline const char* BluetoothBLEGenericNotes() {
  return "Generic BLE energy model. Energy depends on advertising interval, connection interval, TX power, scan mode, central/peripheral role, payload frequency, bonding state, and regulator overhead.";
}
}

#endif
