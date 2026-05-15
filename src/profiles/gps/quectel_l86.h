/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_QUECTEL_L86_H
#define ECOSENSE_PROFILES_GPS_QUECTEL_L86_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile QuectelL86() {
  return EcoSensorProfile("Quectel L86 placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Quectel L86 GNSS placeholder. Antenna, sky visibility, update rate, constellation mode, and backup supply dominate current.");
}

inline const char* QuectelL86Name() {
  return "Quectel L86 placeholder";
}

inline bool QuectelL86Measured() {
  return false;
}

inline const char* QuectelL86Notes() {
  return "Quectel L86 GNSS placeholder. Antenna, sky visibility, update rate, constellation mode, and backup supply dominate current.";
}
}

#endif
