/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_PORTENTA_H7_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_PORTENTA_H7_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoPortentaH7BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(60000UL)
    .rxCurrent_uA(35000UL)
    .sleepCurrent_uA(1500UL)
    .fixedTxDurationMs(40UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoPortentaH7BLEName() {
  return "Arduino Portenta H7 BLE placeholder";
}

inline bool ArduinoPortentaH7BLEMeasured() {
  return false;
}

inline const char* ArduinoPortentaH7BLENotes() {
  return "Arduino Portenta H7 BLE placeholder. Board mode, radio firmware, role, interval, scan mode, payload frequency, and PMIC/regulator state dominate.";
}
}

#endif
