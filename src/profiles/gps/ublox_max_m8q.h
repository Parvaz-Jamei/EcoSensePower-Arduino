/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_MAX_M8Q_H
#define ECOSENSE_PROFILES_GPS_UBLOX_MAX_M8Q_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxMAXM8Q() {
  return EcoSensorProfile("u-blox MAX-M8Q placeholder", 40000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox MAX-M8Q placeholder. Module board, active antenna, power-save configuration, update rate, and backup supply affect current.");
}

inline const char* UBloxMAXM8QName() {
  return "u-blox MAX-M8Q placeholder";
}

inline bool UBloxMAXM8QMeasured() {
  return false;
}

inline const char* UBloxMAXM8QNotes() {
  return "u-blox MAX-M8Q placeholder. Module board, active antenna, power-save configuration, update rate, and backup supply affect current.";
}
}

#endif
