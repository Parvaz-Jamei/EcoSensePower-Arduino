/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_UBLOX_NEOM8Q_H
#define ECOSENSE_PROFILES_GPS_UBLOX_NEOM8Q_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile UBloxNEOM8Q() {
  return EcoSensorProfile("u-blox NEO-M8Q placeholder", 42000UL, 32000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "u-blox NEO-M8Q placeholder. Treat acquisition/tracking state, update rate, antenna, output messages, and backup supply as application-specific.");
}

inline const char* UBloxNEOM8QName() {
  return "u-blox NEO-M8Q placeholder";
}

inline bool UBloxNEOM8QMeasured() {
  return false;
}

inline const char* UBloxNEOM8QNotes() {
  return "u-blox NEO-M8Q placeholder. Treat acquisition/tracking state, update rate, antenna, output messages, and backup supply as application-specific.";
}
}

#endif
