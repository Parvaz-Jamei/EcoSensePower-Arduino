/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_BLUETOOTH_CLASSIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_BLUETOOTH_CLASSIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ESP32BluetoothClassic() {
  GenericRadioProfile p;
  p.txCurrent_uA(130000UL)
    .rxCurrent_uA(80000UL)
    .sleepCurrent_uA(5000UL)
    .fixedTxDurationMs(80UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ESP32BluetoothClassicName() {
  return "ESP32 Bluetooth Classic placeholder";
}

inline bool ESP32BluetoothClassicMeasured() {
  return false;
}

inline const char* ESP32BluetoothClassicNotes() {
  return "ESP32 Bluetooth Classic placeholder. Controller state, coexistence with Wi-Fi, TX power, scanning, connection state, and board overhead dominate energy.";
}
}

#endif
