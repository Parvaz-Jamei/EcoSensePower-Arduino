/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_BOARD_INTEGRATED_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_BOARD_INTEGRATED_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothBoardIntegratedGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(20000UL)
    .rxCurrent_uA(15000UL)
    .sleepCurrent_uA(500UL)
    .fixedTxDurationMs(30UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothBoardIntegratedGenericName() {
  return "Integrated board BLE placeholder";
}

inline bool BluetoothBoardIntegratedGenericMeasured() {
  return false;
}

inline const char* BluetoothBoardIntegratedGenericNotes() {
  return "Integrated board BLE placeholder. Board regulator, USB bridge, sensors, radio firmware, role, advertising/connection interval, and TX power dominate energy.";
}
}

#endif
