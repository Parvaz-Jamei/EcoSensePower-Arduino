/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEOM10_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEOM10_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEOM10() {
  return EcoSensorProfile("u-blox NEO-M10 placeholder", 35000UL, 25000UL, 50UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-M10-class placeholder. Energy depends on constellation configuration, power-save mode, acquisition/tracking state, output rate, and backup supply.");
}

inline const char* UBloxNEOM10Name() {
  return "u-blox NEO-M10 placeholder";
}

inline bool UBloxNEOM10Measured() {
  return false;
}

inline const char* UBloxNEOM10Notes() {
  return "u-blox NEO-M10-class placeholder. Energy depends on constellation configuration, power-save mode, acquisition/tracking state, output rate, and backup supply.";
}
}

#endif
