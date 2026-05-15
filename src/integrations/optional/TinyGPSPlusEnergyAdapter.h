/*
  EcoSensePower optional integration adapter.

  This adapter is off by default and must be explicitly enabled by a user macro.
  EcoSensePower does not make the matching external library a mandatory dependency.
  If enabled without the optional library installed, this file intentionally fails with
  a clear compile-time message.
*/

#ifndef ECOSENSE_INTEGRATIONS_OPTIONAL_TINYGPSPLUSENERGYADAPTER_H
#define ECOSENSE_INTEGRATIONS_OPTIONAL_TINYGPSPLUSENERGYADAPTER_H

#include "core/EcoSensePowerConfig.h"
#include "profiles/gps/nmea_uart_gps_generic.h"

#if ECOSENSE_ENABLE_TINYGPSPLUS_ADAPTER
  #if defined(__has_include)
    #if __has_include(<TinyGPS++.h>)
      #include <TinyGPS++.h>
    #else
      #error "ECOSENSE_ENABLE_TINYGPSPLUS_ADAPTER requires the optional TinyGPSPlus library. Install it or disable the adapter macro."
    #endif
  #else
    #include <TinyGPS++.h>
  #endif
#endif

struct TinyGPSPlusEnergyAdapter {
  static EcoSensorProfile placeholderProfile() { return EcoProfiles::NMEAUARTGPSGeneric(); }
};

#endif
