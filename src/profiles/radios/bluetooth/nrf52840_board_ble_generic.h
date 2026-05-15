/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52840_BOARD_BLE_GENERIC_H
#define ECOSENSE_PROFILES_RADIOS_BLUETOOTH_NRF52840_BOARD_BLE_GENERIC_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile NRF52840BoardBLEGeneric() {
  GenericRadioProfile p;
  p.txCurrent_uA(30000UL)
    .rxCurrent_uA(18000UL)
    .sleepCurrent_uA(500UL)
    .fixedTxDurationMs(30UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* NRF52840BoardBLEGenericName() {
  return "nRF52840 board BLE generic placeholder";
}

inline bool NRF52840BoardBLEGenericMeasured() {
  return false;
}

inline const char* NRF52840BoardBLEGenericNotes() {
  return "nRF52840 board-level BLE placeholder. Board regulator, USB, sensors, DC/DC setup, role, interval, and TX power dominate.";
}
}

#endif
