/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_EXTERNAL_MODULE_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_EXTERNAL_MODULE_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothExternalModuleGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(35000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(200UL)
    .fixedTxDurationMs(40UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothExternalModuleGenericName() {
  return "External Bluetooth module placeholder";
}

inline bool BluetoothExternalModuleGenericMeasured() {
  return false;
}

inline const char* BluetoothExternalModuleGenericNotes() {
  return "External Bluetooth module placeholder. Energy depends on module enable pin, idle/connected state, UART traffic, scan/advertising mode, TX power, and host sleep coordination.";
}
}

#endif
