/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEO6M_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEO6M_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEO6M() {
  return EcoSensorProfile("u-blox NEO-6M placeholder", 45000UL, 35000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-6M-class placeholder. Cold start, tracking state, update rate, active antenna current, UART output rate, backup supply, and module regulator dominate energy.");
}

inline const char* UBloxNEO6MName() {
  return "u-blox NEO-6M placeholder";
}

inline bool UBloxNEO6MMeasured() {
  return false;
}

inline const char* UBloxNEO6MNotes() {
  return "u-blox NEO-6M-class placeholder. Cold start, tracking state, update rate, active antenna current, UART output rate, backup supply, and module regulator dominate energy.";
}
}

#endif
