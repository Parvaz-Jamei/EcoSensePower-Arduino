/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_ATGM336H_H
#define ECOSENSE_PROFILES_GPS_ATGM336H_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile ATGM336H() {
  return EcoSensorProfile("ATGM336H GNSS placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "ATGM336H GNSS placeholder. BeiDou/GPS constellation settings, update rate, active antenna, and backup supply dominate current.");
}

inline const char* ATGM336HName() {
  return "ATGM336H GNSS placeholder";
}

inline bool ATGM336HMeasured() {
  return false;
}

inline const char* ATGM336HNotes() {
  return "ATGM336H GNSS placeholder. BeiDou/GPS constellation settings, update rate, active antenna, and backup supply dominate current.";
}
}

#endif
