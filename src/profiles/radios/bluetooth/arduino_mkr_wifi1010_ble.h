/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_MKR_WIFI1010_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_MKR_WIFI1010_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoMKRWiFi1010BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoMKRWiFi1010BLEName() {
  return "Arduino MKR WiFi 1010 BLE placeholder";
}

inline bool ArduinoMKRWiFi1010BLEMeasured() {
  return false;
}

inline const char* ArduinoMKRWiFi1010BLENotes() {
  return "Arduino MKR WiFi 1010 BLE/NINA-class placeholder. NINA firmware, role, interval, TX power, scan mode, and regulator overhead dominate energy.";
}
}

#endif
