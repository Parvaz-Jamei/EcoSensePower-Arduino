/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_UNO_R4_WIFI_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_UNO_R4_WIFI_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoUNOR4WiFiBLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(50000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(1500UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoUNOR4WiFiBLEName() {
  return "Arduino UNO R4 WiFi BLE placeholder";
}

inline bool ArduinoUNOR4WiFiBLEMeasured() {
  return false;
}

inline const char* ArduinoUNOR4WiFiBLENotes() {
  return "Arduino UNO R4 WiFi BLE placeholder. RA4M1 board overhead, ESP32-S3/NINA-style radio state, role, intervals, and USB/regulator current dominate.";
}
}

#endif
