/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NINA_W102_BLE_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NINA_W102_BLE_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile NINAW102BLEGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(40000UL)
    .rxCurrent_uA(25000UL)
    .sleepCurrent_uA(1000UL)
    .fixedTxDurationMs(35UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* NINAW102BLEGenericName() {
  return "NINA-W102 BLE generic placeholder";
}

inline bool NINAW102BLEGenericMeasured() {
  return false;
}

inline const char* NINAW102BLEGenericNotes() {
  return "NINA-W102/NINA-class BLE placeholder. Firmware, role, interval, scan mode, Wi-Fi coexistence, and host sleep coordination dominate energy.";
}
}

#endif
