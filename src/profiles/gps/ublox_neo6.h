/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEO6_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEO6_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEO6() {
  return EcoSensorProfile("u-blox NEO-6 placeholder", 45000UL, 35000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-6 family placeholder. Treat acquisition/tracking state, update rate, antenna, and backup supply as project-specific.");
}

inline const char* UBloxNEO6Name() {
  return "u-blox NEO-6 placeholder";
}

inline bool UBloxNEO6Measured() {
  return false;
}

inline const char* UBloxNEO6Notes() {
  return "u-blox NEO-6 family placeholder. Treat acquisition/tracking state, update rate, antenna, and backup supply as project-specific.";
}
}

#endif
