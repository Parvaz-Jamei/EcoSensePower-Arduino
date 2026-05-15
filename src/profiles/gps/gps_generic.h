/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GPS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GPS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GPSGeneric() {
  return EcoSensorProfile("GPS generic placeholder", 30000UL, 28000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Generic GPS energy profile. Energy depends on cold/warm/hot start, update rate, acquisition versus tracking, sky visibility, antenna type, backup battery/RTC state, and power gating.");
}

inline const char* GPSGenericName() {
  return "GPS generic placeholder";
}

inline bool GPSGenericMeasured() {
  return false;
}

inline const char* GPSGenericNotes() {
  return "Generic GPS energy profile. Energy depends on cold/warm/hot start, update rate, acquisition versus tracking, sky visibility, antenna type, backup battery/RTC state, and power gating.";
}
}

#endif
