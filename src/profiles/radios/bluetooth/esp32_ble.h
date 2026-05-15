/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ESP32_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ESP32BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(90000UL)
    .rxCurrent_uA(50000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(50UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ESP32BLEName() {
  return "ESP32 BLE placeholder";
}

inline bool ESP32BLEMeasured() {
  return false;
}

inline const char* ESP32BLENotes() {
  return "ESP32 BLE placeholder. ESP-IDF/Arduino-ESP32 BLE/NimBLE use remains application-owned; interval, role, TX power, scan mode, and sleep coordination dominate energy.";
}
}

#endif
