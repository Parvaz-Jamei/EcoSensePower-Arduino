/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_IOT_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_IOT_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoNano33IoTBLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoNano33IoTBLEName() {
  return "Arduino Nano 33 IoT BLE placeholder";
}

inline bool ArduinoNano33IoTBLEMeasured() {
  return false;
}

inline const char* ArduinoNano33IoTBLENotes() {
  return "Arduino Nano 33 IoT BLE/NINA-class placeholder. Board regulator, NINA firmware, role, interval, scan mode, and Wi-Fi coexistence affect current.";
}
}

#endif
