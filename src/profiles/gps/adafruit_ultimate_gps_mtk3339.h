/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_ADAFRUIT_ULTIMATE_GPS_MTK3339_H
#define ECOSENSE_PROFILES_GPS_ADAFRUIT_ULTIMATE_GPS_MTK3339_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile AdafruitUltimateGPSMTK3339() {
  return EcoSensorProfile("Adafruit Ultimate GPS MTK3339 placeholder", 30000UL, 25000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Adafruit Ultimate GPS/MTK3339-style placeholder. Board regulator/LED, active antenna option, update rate, backup battery, and NMEA output rate dominate energy.");
}

inline const char* AdafruitUltimateGPSMTK3339Name() {
  return "Adafruit Ultimate GPS MTK3339 placeholder";
}

inline bool AdafruitUltimateGPSMTK3339Measured() {
  return false;
}

inline const char* AdafruitUltimateGPSMTK3339Notes() {
  return "Adafruit Ultimate GPS/MTK3339-style placeholder. Board regulator/LED, active antenna option, update rate, backup battery, and NMEA output rate dominate energy.";
}
}

#endif
