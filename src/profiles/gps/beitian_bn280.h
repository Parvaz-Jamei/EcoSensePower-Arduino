/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_BEITIAN_BN280_H
#define ECOSENSE_PROFILES_GPS_BEITIAN_BN280_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile BeitianBN280() {
  return EcoSensorProfile("Beitian BN-280 GNSS placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Beitian BN-280 GNSS placeholder. Update rate, active antenna, constellation settings, and backup state dominate current.");
}

inline const char* BeitianBN280Name() {
  return "Beitian BN-280 GNSS placeholder";
}

inline bool BeitianBN280Measured() {
  return false;
}

inline const char* BeitianBN280Notes() {
  return "Beitian BN-280 GNSS placeholder. Update rate, active antenna, constellation settings, and backup state dominate current.";
}
}

#endif
