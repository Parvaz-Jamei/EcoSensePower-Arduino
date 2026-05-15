/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_NMEA_UART_GPS_GENERIC_H
#define ECOSENSE_PROFILES_GPS_NMEA_UART_GPS_GENERIC_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile NMEAUARTGPSGeneric() {
  return EcoSensorProfile("NMEA UART GPS generic placeholder", 30000UL, 28000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "NMEA UART GPS placeholder. UART baud/output rate, update rate, cold/warm/hot start, and host parsing duty cycle affect system energy.");
}

inline const char* NMEAUARTGPSGenericName() {
  return "NMEA UART GPS generic placeholder";
}

inline bool NMEAUARTGPSGenericMeasured() {
  return false;
}

inline const char* NMEAUARTGPSGenericNotes() {
  return "NMEA UART GPS placeholder. UART baud/output rate, update rate, cold/warm/hot start, and host parsing duty cycle affect system energy.";
}
}

#endif
