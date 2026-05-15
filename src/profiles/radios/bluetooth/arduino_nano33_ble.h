/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoNano33BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(30000UL)
    .rxCurrent_uA(18000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoNano33BLEName() {
  return "Arduino Nano 33 BLE board BLE placeholder";
}

inline bool ArduinoNano33BLEMeasured() {
  return false;
}

inline const char* ArduinoNano33BLENotes() {
  return "Arduino Nano 33 BLE board-level placeholder. Board sensors/regulators and BLE role/intervals dominate over bare SoC current.";
}
}

#endif
