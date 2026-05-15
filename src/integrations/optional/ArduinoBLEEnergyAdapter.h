/*
  EcoSensePower optional integration adapter.

  This adapter is off by default and must be explicitly enabled by a user macro.
  EcoSensePower does not make the matching external library a mandatory dependency.
  If enabled without the optional library installed, this file intentionally fails with
  a clear compile-time message.
*/

#ifndef ECOSENSE_INTEGRATIONS_OPTIONAL_ARDUINOBLEENERGYADAPTER_H
#define ECOSENSE_INTEGRATIONS_OPTIONAL_ARDUINOBLEENERGYADAPTER_H

#include "core/EcoSensePowerConfig.h"
#include "profiles/radios/bluetooth/bluetooth_ble_generic.h"

#if ECOSENSE_ENABLE_ARDUINO_BLE_ADAPTER
  #if defined(__has_include)
    #if __has_include(<ArduinoBLE.h>)
      #include <ArduinoBLE.h>
    #else
      #error "ECOSENSE_ENABLE_ARDUINO_BLE_ADAPTER requires the optional ArduinoBLE library. Install it or disable the adapter macro."
    #endif
  #else
    #include <ArduinoBLE.h>
  #endif
#endif

class ArduinoBLEEnergyAdapter : public GenericRadioProfile {
public:
  ArduinoBLEEnergyAdapter() : GenericRadioProfile(EcoProfiles::BluetoothBLEGeneric()) {}
};

#endif
