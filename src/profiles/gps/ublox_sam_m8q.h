/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_SAM_M8Q_H
#define ECOSENSE_PROFILES_GPS_UBLOX_SAM_M8Q_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxSAMM8Q() {
  return EcoSensorProfile("u-blox SAM-M8Q placeholder", 40000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox SAM-M8Q placeholder. Embedded antenna behavior, sky visibility, update rate, acquisition state, and backup retention dominate energy.");
}

inline const char* UBloxSAMM8QName() {
  return "u-blox SAM-M8Q placeholder";
}

inline bool UBloxSAMM8QMeasured() {
  return false;
}

inline const char* UBloxSAMM8QNotes() {
  return "u-blox SAM-M8Q placeholder. Embedded antenna behavior, sky visibility, update rate, acquisition state, and backup retention dominate energy.";
}
}

#endif
