/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_ATGM336H_5N_H
#define ECOSENSE_PROFILES_GPS_ATGM336H_5N_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile ATGM336H5N() {
  return EcoSensorProfile("ATGM336H-5N GNSS placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "ATGM336H-5N GNSS placeholder. Cold-start energy, constellation mode, output cadence, and antenna current are key drivers.");
}

inline const char* ATGM336H5NName() {
  return "ATGM336H-5N GNSS placeholder";
}

inline bool ATGM336H5NMeasured() {
  return false;
}

inline const char* ATGM336H5NNotes() {
  return "ATGM336H-5N GNSS placeholder. Cold-start energy, constellation mode, output cadence, and antenna current are key drivers.";
}
}

#endif
