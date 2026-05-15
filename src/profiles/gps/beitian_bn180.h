/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_BEITIAN_BN180_H
#define ECOSENSE_PROFILES_GPS_BEITIAN_BN180_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile BeitianBN180() {
  return EcoSensorProfile("Beitian BN-180 GNSS placeholder", 35000UL, 30000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Beitian BN-180 UAV-style GNSS module placeholder. Module regulator, antenna, output rate, fix state, and backup supply dominate.");
}

inline const char* BeitianBN180Name() {
  return "Beitian BN-180 GNSS placeholder";
}

inline bool BeitianBN180Measured() {
  return false;
}

inline const char* BeitianBN180Notes() {
  return "Beitian BN-180 UAV-style GNSS module placeholder. Module regulator, antenna, output rate, fix state, and backup supply dominate.";
}
}

#endif
