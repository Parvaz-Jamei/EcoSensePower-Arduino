/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLE_UART_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLE_UART_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BLEUARTGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(16000UL)
    .rxCurrent_uA(12000UL)
    .sleepCurrent_uA(10UL)
    .fixedTxDurationMs(25UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BLEUARTGenericName() {
  return "BLE UART generic placeholder";
}

inline bool BLEUARTGenericMeasured() {
  return false;
}

inline const char* BLEUARTGenericNotes() {
  return "Generic BLE UART profile placeholder. Energy depends on notification cadence, connection interval, MTU/payload rate, role, and TX power.";
}
}

#endif
