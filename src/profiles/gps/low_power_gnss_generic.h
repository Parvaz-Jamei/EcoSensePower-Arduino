/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_LOW_POWER_GNSS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_LOW_POWER_GNSS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile LowPowerGNSSGeneric() {
  return EcoSensorProfile("Low-power GNSS placeholder", 12000UL, 10000UL, 20UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Low-power GNSS placeholder. Backup supply, duty-cycled acquisition, hot-start retention, and power gating drive real savings.");
}

inline const char* LowPowerGNSSGenericName() {
  return "Low-power GNSS placeholder";
}

inline bool LowPowerGNSSGenericMeasured() {
  return false;
}

inline const char* LowPowerGNSSGenericNotes() {
  return "Low-power GNSS placeholder. Backup supply, duty-cycled acquisition, hot-start retention, and power gating drive real savings.";
}
}

#endif
