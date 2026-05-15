/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_GPS_UART_9600_GENERIC_H
#define ECOSENSE_PROFILES_GPS_GPS_UART_9600_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile GPSUART9600Generic() {
  return EcoSensorProfile("GPS UART 9600 generic placeholder", 30000UL, 28000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Generic 9600 baud UART GPS placeholder. UART output sentence rate, update rate, acquisition state, and host parsing cadence affect energy.");
}

inline const char* GPSUART9600GenericName() {
  return "GPS UART 9600 generic placeholder";
}

inline bool GPSUART9600GenericMeasured() {
  return false;
}

inline const char* GPSUART9600GenericNotes() {
  return "Generic 9600 baud UART GPS placeholder. UART output sentence rate, update rate, acquisition state, and host parsing cadence affect energy.";
}
}

#endif
