/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_C3_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_C3_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ESP32C3BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(80000UL)
    .rxCurrent_uA(45000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ESP32C3BLEName() {
  return "ESP32-C3 BLE placeholder";
}

inline bool ESP32C3BLEMeasured() {
  return false;
}

inline const char* ESP32C3BLENotes() {
  return "ESP32-C3 BLE placeholder. BLE/802.15.4 coexistence, interval, scan mode, TX power, and sleep coordination affect energy.";
}
}

#endif
