/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_ZOE_M8Q_H
#define ECOSENSE_PROFILES_GPS_UBLOX_ZOE_M8Q_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxZOEM8Q() {
  return EcoSensorProfile("u-blox ZOE-M8Q placeholder", 35000UL, 25000UL, 50UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox ZOE-M8Q placeholder. Low-power mode, update rate, antenna matching, acquisition/tracking state, and backup supply are critical.");
}

inline const char* UBloxZOEM8QName() {
  return "u-blox ZOE-M8Q placeholder";
}

inline bool UBloxZOEM8QMeasured() {
  return false;
}

inline const char* UBloxZOEM8QNotes() {
  return "u-blox ZOE-M8Q placeholder. Low-power mode, update rate, antenna matching, acquisition/tracking state, and backup supply are critical.";
}
}

#endif
