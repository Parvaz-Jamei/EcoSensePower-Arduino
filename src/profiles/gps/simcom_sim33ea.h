/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_SIMCOM_SIM33EA_H
#define ECOSENSE_PROFILES_GPS_SIMCOM_SIM33EA_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile SIMComSIM33EA() {
  return EcoSensorProfile("SIMCom SIM33EA placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "SIMCom SIM33EA GNSS placeholder. Acquisition/tracking state, antenna, update rate, output messages, and backup supply affect current.");
}

inline const char* SIMComSIM33EAName() {
  return "SIMCom SIM33EA placeholder";
}

inline bool SIMComSIM33EAMeasured() {
  return false;
}

inline const char* SIMComSIM33EANotes() {
  return "SIMCom SIM33EA GNSS placeholder. Acquisition/tracking state, antenna, update rate, output messages, and backup supply affect current.";
}
}

#endif
