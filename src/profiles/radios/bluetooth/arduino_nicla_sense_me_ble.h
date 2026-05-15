/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NICLA_SENSE_ME_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_NICLA_SENSE_ME_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoNiclaSenseMEBLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(35000UL)
    .rxCurrent_uA(20000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoNiclaSenseMEBLEName() {
  return "Arduino Nicla Sense ME BLE placeholder";
}

inline bool ArduinoNiclaSenseMEBLEMeasured() {
  return false;
}

inline const char* ArduinoNiclaSenseMEBLENotes() {
  return "Arduino Nicla Sense ME BLE placeholder. Onboard sensors, BLE role, interval, TX power, and board power tree dominate current.";
}
}

#endif
