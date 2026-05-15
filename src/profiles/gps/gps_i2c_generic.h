/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GPS_I2C_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GPS_I2C_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GPSI2CGeneric() {
  return EcoSensorProfile("GPS I2C generic placeholder", 30000UL, 28000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Generic I2C GPS/GNSS placeholder. I2C polling cadence, update rate, fix state, and power gating dominate system energy.");
}

inline const char* GPSI2CGenericName() {
  return "GPS I2C generic placeholder";
}

inline bool GPSI2CGenericMeasured() {
  return false;
}

inline const char* GPSI2CGenericNotes() {
  return "Generic I2C GPS/GNSS placeholder. I2C polling cadence, update rate, fix state, and power gating dominate system energy.";
}
}

#endif
