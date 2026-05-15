/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_QUECTEL_L80_H
#define ECOSENSE_PROFILES_GPS_QUECTEL_L80_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile QuectelL80() {
  return EcoSensorProfile("Quectel L80 placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Quectel L80 GNSS placeholder. Embedded antenna, sky visibility, update rate, and acquisition state strongly affect energy.");
}

inline const char* QuectelL80Name() {
  return "Quectel L80 placeholder";
}

inline bool QuectelL80Measured() {
  return false;
}

inline const char* QuectelL80Notes() {
  return "Quectel L80 GNSS placeholder. Embedded antenna, sky visibility, update rate, and acquisition state strongly affect energy.";
}
}

#endif
