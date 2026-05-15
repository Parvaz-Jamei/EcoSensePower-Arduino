/*
  EcoSensePower energy profile header.

  This file provides a confidence-bounded energy model only. It is not a hardware
  driver, parser, protocol stack, BLE manager, GPS decoder, or navigation framework.
  It adds no mandatory external dependency. Unless a header explicitly documents
  measured evidence, profiles default to measured=false and PLACEHOLDER confidence.
*/

#ifndef ECOSENSE_PROFILES_GPS_ADAFRUIT_PA1010D_GPS_H
#define ECOSENSE_PROFILES_GPS_ADAFRUIT_PA1010D_GPS_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile AdafruitPA1010DGPS() {
  return EcoSensorProfile("Adafruit PA1010D GPS placeholder", 30000UL, 25000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Adafruit PA1010D GPS placeholder. I2C/UART output, update rate, acquisition/tracking state, antenna and backup supply affect energy.");
}

inline const char* AdafruitPA1010DGPSName() {
  return "Adafruit PA1010D GPS placeholder";
}

inline bool AdafruitPA1010DGPSMeasured() {
  return false;
}

inline const char* AdafruitPA1010DGPSNotes() {
  return "Adafruit PA1010D GPS placeholder. I2C/UART output, update rate, acquisition/tracking state, antenna and backup supply affect energy.";
}
}

#endif
