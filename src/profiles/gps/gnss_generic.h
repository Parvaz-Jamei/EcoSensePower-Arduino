/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GNSS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GNSS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GNSSGeneric() {
  return EcoSensorProfile("GNSS generic placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Generic multi-constellation GNSS placeholder. Energy depends on constellation mode, acquisition/tracking state, update rate, antenna current, UART/I2C output rate, and power gating.");
}

inline const char* GNSSGenericName() {
  return "GNSS generic placeholder";
}

inline bool GNSSGenericMeasured() {
  return false;
}

inline const char* GNSSGenericNotes() {
  return "Generic multi-constellation GNSS placeholder. Energy depends on constellation mode, acquisition/tracking state, update rate, antenna current, UART/I2C output rate, and power gating.";
}
}

#endif
