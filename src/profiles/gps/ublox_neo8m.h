/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEO8M_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEO8M_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEO8M() {
  return EcoSensorProfile("u-blox NEO-8M placeholder", 42000UL, 32000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-8M-class placeholder. Multi-constellation mode, update rate, antenna current, backup supply, and tracking/acquisition state affect current.");
}

inline const char* UBloxNEO8MName() {
  return "u-blox NEO-8M placeholder";
}

inline bool UBloxNEO8MMeasured() {
  return false;
}

inline const char* UBloxNEO8MNotes() {
  return "u-blox NEO-8M-class placeholder. Multi-constellation mode, update rate, antenna current, backup supply, and tracking/acquisition state affect current.";
}
}

#endif
