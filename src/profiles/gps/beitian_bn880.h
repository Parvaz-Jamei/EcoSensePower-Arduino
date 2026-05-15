/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_BEITIAN_BN880_H
#define ECOSENSE_PROFILES_GPS_BEITIAN_BN880_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile BeitianBN880() {
  return EcoSensorProfile("Beitian BN-880 GNSS/compass placeholder", 45000UL, 35000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Beitian BN-880 GNSS/compass placeholder. GNSS plus compass board current, update rate, active antenna, and backup supply must be measured.");
}

inline const char* BeitianBN880Name() {
  return "Beitian BN-880 GNSS/compass placeholder";
}

inline bool BeitianBN880Measured() {
  return false;
}

inline const char* BeitianBN880Notes() {
  return "Beitian BN-880 GNSS/compass placeholder. GNSS plus compass board current, update rate, active antenna, and backup supply must be measured.";
}
}

#endif
