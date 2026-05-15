/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_BLE_SENSE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NANO33_BLE_SENSE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoNano33BLESense() {
  GenericRadioProfile p;
  p.txCurrent_uA(35000UL)
    .rxCurrent_uA(20000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoNano33BLESenseName() {
  return "Arduino Nano 33 BLE Sense board BLE placeholder";
}

inline bool ArduinoNano33BLESenseMeasured() {
  return false;
}

inline const char* ArduinoNano33BLESenseNotes() {
  return "Arduino Nano 33 BLE Sense board-level placeholder. Onboard sensors, BLE role, intervals, TX power, and regulator overhead dominate.";
}
}

#endif
