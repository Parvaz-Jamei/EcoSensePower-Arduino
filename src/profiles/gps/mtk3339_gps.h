/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_MTK3339_GPS_H
#define ECOSENSE_PROFILES_GPS_MTK3339_GPS_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile MTK3339GPS() {
  return EcoSensorProfile("MTK3339 GPS placeholder", 30000UL, 25000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "MTK3339 GPS placeholder. Update rate, NMEA sentence output, active antenna, fix state, and backup battery determine real energy.");
}

inline const char* MTK3339GPSName() {
  return "MTK3339 GPS placeholder";
}

inline bool MTK3339GPSMeasured() {
  return false;
}

inline const char* MTK3339GPSNotes() {
  return "MTK3339 GPS placeholder. Update rate, NMEA sentence output, active antenna, fix state, and backup battery determine real energy.";
}
}

#endif
