/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GNSS_ACTIVE_ANTENNA_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GNSS_ACTIVE_ANTENNA_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GNSSActiveAntennaGeneric() {
  return EcoSensorProfile("GNSS active antenna placeholder", 40000UL, 30000UL, 500UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "GNSS active antenna placeholder. Receiver current plus active antenna current must both be included before battery-life claims.");
}

inline const char* GNSSActiveAntennaGenericName() {
  return "GNSS active antenna placeholder";
}

inline bool GNSSActiveAntennaGenericMeasured() {
  return false;
}

inline const char* GNSSActiveAntennaGenericNotes() {
  return "GNSS active antenna placeholder. Receiver current plus active antenna current must both be included before battery-life claims.";
}
}

#endif
