/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_I2C_GNSS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_I2C_GNSS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile I2CGNSSGeneric() {
  return EcoSensorProfile("I2C GNSS generic placeholder", 30000UL, 28000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "I2C GNSS placeholder. I2C output cadence, update rate, acquisition/tracking state, antenna current, and backup supply affect current.");
}

inline const char* I2CGNSSGenericName() {
  return "I2C GNSS generic placeholder";
}

inline bool I2CGNSSGenericMeasured() {
  return false;
}

inline const char* I2CGNSSGenericNotes() {
  return "I2C GNSS placeholder. I2C output cadence, update rate, acquisition/tracking state, antenna current, and backup supply affect current.";
}
}

#endif
