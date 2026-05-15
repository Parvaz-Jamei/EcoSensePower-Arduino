/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_SIMCOM_SIM28_H
#define ECOSENSE_PROFILES_GPS_SIMCOM_SIM28_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile SIMComSIM28() {
  return EcoSensorProfile("SIMCom SIM28 placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "SIMCom SIM28 GNSS placeholder. Acquisition/tracking state, update rate, active antenna, backup supply, and UART output rate dominate.");
}

inline const char* SIMComSIM28Name() {
  return "SIMCom SIM28 placeholder";
}

inline bool SIMComSIM28Measured() {
  return false;
}

inline const char* SIMComSIM28Notes() {
  return "SIMCom SIM28 GNSS placeholder. Acquisition/tracking state, update rate, active antenna, backup supply, and UART output rate dominate.";
}
}

#endif
