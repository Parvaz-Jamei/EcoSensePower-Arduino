/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_QUECTEL_LC76G_H
#define ECOSENSE_PROFILES_GPS_QUECTEL_LC76G_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile QuectelLC76G() {
  return EcoSensorProfile("Quectel LC76G placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Quectel LC76G GNSS placeholder. Multi-band/multi-constellation settings, update rate, antenna, and output cadence affect energy.");
}

inline const char* QuectelLC76GName() {
  return "Quectel LC76G placeholder";
}

inline bool QuectelLC76GMeasured() {
  return false;
}

inline const char* QuectelLC76GNotes() {
  return "Quectel LC76G GNSS placeholder. Multi-band/multi-constellation settings, update rate, antenna, and output cadence affect energy.";
}
}

#endif
