/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_MTK3333_GPS_H
#define ECOSENSE_PROFILES_GPS_MTK3333_GPS_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile MTK3333GPS() {
  return EcoSensorProfile("MTK3333 GPS placeholder", 30000UL, 25000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "MTK3333 GPS placeholder. Acquisition/tracking state, update rate, antenna current, backup retention, and output cadence dominate.");
}

inline const char* MTK3333GPSName() {
  return "MTK3333 GPS placeholder";
}

inline bool MTK3333GPSMeasured() {
  return false;
}

inline const char* MTK3333GPSNotes() {
  return "MTK3333 GPS placeholder. Acquisition/tracking state, update rate, antenna current, backup retention, and output cadence dominate.";
}
}

#endif
