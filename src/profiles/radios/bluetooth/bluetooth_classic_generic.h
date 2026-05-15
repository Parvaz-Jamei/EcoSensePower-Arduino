/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_CLASSIC_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_CLASSIC_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothClassicGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(45000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(60UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothClassicGenericName() {
  return "Bluetooth Classic generic placeholder";
}

inline bool BluetoothClassicGenericMeasured() {
  return false;
}

inline const char* BluetoothClassicGenericNotes() {
  return "Generic Bluetooth Classic energy model. Energy depends on scan mode, pairing/bonding state, TX power, payload frequency, connected/idle state, and board regulator overhead.";
}
}

#endif
