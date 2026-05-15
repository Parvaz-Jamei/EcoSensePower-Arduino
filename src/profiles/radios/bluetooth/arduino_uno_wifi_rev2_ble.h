/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_UNO_WIFI_REV2_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_UNO_WIFI_REV2_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoUNOWiFiRev2BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(50000UL)
    .rxCurrent_uA(30000UL)
    .sleepCurrent_uA(1500UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoUNOWiFiRev2BLEName() {
  return "Arduino UNO WiFi Rev2 BLE placeholder";
}

inline bool ArduinoUNOWiFiRev2BLEMeasured() {
  return false;
}

inline const char* ArduinoUNOWiFiRev2BLENotes() {
  return "Arduino UNO WiFi Rev2 BLE/NINA-class placeholder. USB bridge, regulator, NINA firmware, role, interval, and scan mode dominate energy.";
}
}

#endif
