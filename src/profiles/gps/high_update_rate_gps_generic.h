/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_HIGH_UPDATE_RATE_GPS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_HIGH_UPDATE_RATE_GPS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile HighUpdateRateGPSGeneric() {
  return EcoSensorProfile("High update-rate GPS placeholder", 50000UL, 45000UL, 200UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "High update-rate GPS placeholder. Update rates above 1 Hz can dominate energy through receiver current and host processing/reporting cadence.");
}

inline const char* HighUpdateRateGPSGenericName() {
  return "High update-rate GPS placeholder";
}

inline bool HighUpdateRateGPSGenericMeasured() {
  return false;
}

inline const char* HighUpdateRateGPSGenericNotes() {
  return "High update-rate GPS placeholder. Update rates above 1 Hz can dominate energy through receiver current and host processing/reporting cadence.";
}
}

#endif
