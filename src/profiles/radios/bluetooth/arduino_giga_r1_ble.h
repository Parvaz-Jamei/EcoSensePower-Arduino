/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_GIGA_R1_BLE_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_ARDUINO_GIGA_R1_BLE_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ArduinoGigaR1BLE() {
  GenericRadioProfile p;
  p.txCurrent_uA(60000UL)
    .rxCurrent_uA(35000UL)
    .sleepCurrent_uA(1500UL)
    .fixedTxDurationMs(40UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ArduinoGigaR1BLEName() {
  return "Arduino Giga R1 BLE placeholder";
}

inline bool ArduinoGigaR1BLEMeasured() {
  return false;
}

inline const char* ArduinoGigaR1BLENotes() {
  return "Arduino Giga R1 BLE placeholder. Board overhead, radio firmware, role, interval, TX power, and scan mode dominate.";
}
}

#endif
