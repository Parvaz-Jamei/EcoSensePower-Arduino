/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GNSS_MULTICONSTELLATION_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GNSS_MULTICONSTELLATION_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GNSSMultiConstellationGeneric() {
  return EcoSensorProfile("GNSS multi-constellation placeholder", 40000UL, 35000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Multi-constellation GNSS placeholder. More constellations can improve availability but may increase receiver and host-processing energy.");
}

inline const char* GNSSMultiConstellationGenericName() {
  return "GNSS multi-constellation placeholder";
}

inline bool GNSSMultiConstellationGenericMeasured() {
  return false;
}

inline const char* GNSSMultiConstellationGenericNotes() {
  return "Multi-constellation GNSS placeholder. More constellations can improve availability but may increase receiver and host-processing energy.";
}
}

#endif
