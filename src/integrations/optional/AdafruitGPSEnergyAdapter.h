/*
  EcoSensePower optional integration adapter.

  This adapter is off by default and must be explicitly enabled by a user macro.
  EcoSensePower does not make the matching external library a mandatory dependency.
  If enabled without the optional library installed, this file intentionally fails with
  a clear compile-time message.
*/

#ifndef ECOSENSE_INTEGRATIONS_OPTIONAL_ADAFRUITGPSENERGYADAPTER_H
#define ECOSENSE_INTEGRATIONS_OPTIONAL_ADAFRUITGPSENERGYADAPTER_H

#include "core/EcoSensePowerConfig.h"
#include "profiles/gps/adafruit_ultimate_gps_mtk3339.h"

#if ECOSENSE_ENABLE_ADAFRUIT_GPS_ADAPTER
  #if defined(__has_include)
    #if __has_include(<Adafruit_GPS.h>)
      #include <Adafruit_GPS.h>
    #else
      #error "ECOSENSE_ENABLE_ADAFRUIT_GPS_ADAPTER requires the optional Adafruit_GPS library. Install it or disable the adapter macro."
    #endif
  #else
    #include <Adafruit_GPS.h>
  #endif
#endif

struct AdafruitGPSEnergyAdapter {
  static EcoSensorProfile placeholderProfile() { return EcoProfiles::AdafruitUltimateGPSMTK3339(); }
};

#endif
