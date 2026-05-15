/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_UART_MODULE_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_BLUETOOTH_UART_MODULE_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile BluetoothUARTModuleGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(35000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(800UL)
    .fixedTxDurationMs(40UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* BluetoothUARTModuleGenericName() {
  return "Bluetooth UART bridge generic placeholder";
}

inline bool BluetoothUARTModuleGenericMeasured() {
  return false;
}

inline const char* BluetoothUARTModuleGenericNotes() {
  return "Generic Bluetooth UART bridge placeholder. Idle/connected UART bridge current can dominate sleep budgets; configure EN/STATE pins and baud-rate duty cycle explicitly.";
}
}

#endif
