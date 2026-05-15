/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_SIMCOM_SIM33ELA_H
#define ECOSENSE_PROFILES_GPS_SIMCOM_SIM33ELA_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile SIMComSIM33ELA() {
  return EcoSensorProfile("SIMCom SIM33ELA placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "SIMCom SIM33ELA GNSS placeholder. Low-power state, backup supply, update rate, active antenna, and sky visibility must be measured.");
}

inline const char* SIMComSIM33ELAName() {
  return "SIMCom SIM33ELA placeholder";
}

inline bool SIMComSIM33ELAMeasured() {
  return false;
}

inline const char* SIMComSIM33ELANotes() {
  return "SIMCom SIM33ELA GNSS placeholder. Low-power state, backup supply, update rate, active antenna, and sky visibility must be measured.";
}
}

#endif
