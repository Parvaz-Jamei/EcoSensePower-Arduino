/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GY_NEO6MV2_H
#define ECOSENSE_PROFILES_GPS_GY_NEO6MV2_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GYNEO6MV2() {
  return EcoSensorProfile("GY-NEO6MV2 module placeholder", 50000UL, 40000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "GY-NEO6MV2 maker module placeholder. Regulator, LED, antenna, backup cell presence, UART output rate, and cold-start behavior dominate board current.");
}

inline const char* GYNEO6MV2Name() {
  return "GY-NEO6MV2 module placeholder";
}

inline bool GYNEO6MV2Measured() {
  return false;
}

inline const char* GYNEO6MV2Notes() {
  return "GY-NEO6MV2 maker module placeholder. Regulator, LED, antenna, backup cell presence, UART output rate, and cold-start behavior dominate board current.";
}
}

#endif
