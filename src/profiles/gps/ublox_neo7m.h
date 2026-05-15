/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEO7M_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEO7M_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEO7M() {
  return EcoSensorProfile("u-blox NEO-7M placeholder", 42000UL, 32000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-7M-class placeholder. Cold/warm/hot start, active antenna, output rate, backup supply, and sky visibility dominate energy.");
}

inline const char* UBloxNEO7MName() {
  return "u-blox NEO-7M placeholder";
}

inline bool UBloxNEO7MMeasured() {
  return false;
}

inline const char* UBloxNEO7MNotes() {
  return "u-blox NEO-7M-class placeholder. Cold/warm/hot start, active antenna, output rate, backup supply, and sky visibility dominate energy.";
}
}

#endif
