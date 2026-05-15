/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_BEITIAN_BN220_H
#define ECOSENSE_PROFILES_GPS_BEITIAN_BN220_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile BeitianBN220() {
  return EcoSensorProfile("Beitian BN-220 GNSS placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Beitian BN-220 GNSS placeholder. Acquisition/tracking state, update rate, antenna current, and backup supply drive energy.");
}

inline const char* BeitianBN220Name() {
  return "Beitian BN-220 GNSS placeholder";
}

inline bool BeitianBN220Measured() {
  return false;
}

inline const char* BeitianBN220Notes() {
  return "Beitian BN-220 GNSS placeholder. Acquisition/tracking state, update rate, antenna current, and backup supply drive energy.";
}
}

#endif
