/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_QUECTEL_L76_H
#define ECOSENSE_PROFILES_GPS_QUECTEL_L76_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile QuectelL76() {
  return EcoSensorProfile("Quectel L76 placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Quectel L76 GNSS placeholder. Cold/warm/hot start, constellation mode, output rate, antenna current, and backup supply dominate.");
}

inline const char* QuectelL76Name() {
  return "Quectel L76 placeholder";
}

inline bool QuectelL76Measured() {
  return false;
}

inline const char* QuectelL76Notes() {
  return "Quectel L76 GNSS placeholder. Cold/warm/hot start, constellation mode, output rate, antenna current, and backup supply dominate.";
}
}

#endif
