/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GPS_WITH_BACKUP_BATTERY_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GPS_WITH_BACKUP_BATTERY_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GPSWithBackupBatteryGeneric() {
  return EcoSensorProfile("GPS with backup battery placeholder", 25000UL, 22000UL, 10UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "GPS with backup/RTC retention placeholder. Backup supply can reduce repeated cold-start energy but must be measured with the exact module.");
}

inline const char* GPSWithBackupBatteryGenericName() {
  return "GPS with backup battery placeholder";
}

inline bool GPSWithBackupBatteryGenericMeasured() {
  return false;
}

inline const char* GPSWithBackupBatteryGenericNotes() {
  return "GPS with backup/RTC retention placeholder. Backup supply can reduce repeated cold-start energy but must be measured with the exact module.";
}
}

#endif
