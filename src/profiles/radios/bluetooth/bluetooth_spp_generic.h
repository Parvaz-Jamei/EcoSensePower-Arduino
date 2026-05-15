/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_SPP_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_SPP_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothSPPGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(42000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothSPPGenericName() {
  return "Bluetooth SPP generic placeholder";
}

inline bool BluetoothSPPGenericMeasured() {
  return false;
}

inline const char* BluetoothSPPGenericNotes() {
  return "Generic Serial Port Profile Bluetooth model. Pairing, discoverability, connection state, UART duty cycle, and TX power drive energy.";
}
}

#endif
