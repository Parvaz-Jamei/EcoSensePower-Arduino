/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEOM8N_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEOM8N_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEOM8N() {
  return EcoSensorProfile("u-blox NEO-M8N placeholder", 42000UL, 32000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-M8N placeholder. Multi-constellation settings, update rate, sky visibility, antenna current, backup battery, and power gating dominate.");
}

inline const char* UBloxNEOM8NName() {
  return "u-blox NEO-M8N placeholder";
}

inline bool UBloxNEOM8NMeasured() {
  return false;
}

inline const char* UBloxNEOM8NNotes() {
  return "u-blox NEO-M8N placeholder. Multi-constellation settings, update rate, sky visibility, antenna current, backup battery, and power gating dominate.";
}
}

#endif
