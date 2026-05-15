#ifndef ECOSENSE_PROFILES_RADIOS_ESP8266_WIFI_H
#define ECOSENSE_PROFILES_RADIOS_ESP8266_WIFI_H

#include "radio/GenericRadioProfile.h"

namespace EcoProfiles {
inline GenericRadioProfile ESP8266WiFi() {
  GenericRadioProfile p;
  p.txCurrent_uA(170000UL)
    .rxCurrent_uA(70000UL)
    .sleepCurrent_uA(20UL)
    .fixedTxDurationMs(250UL)
    .confidence(EcoProfileConfidence::PLACEHOLDER);
  return p;
}

inline const char* ESP8266WiFiNotes() {
  return "ESP8266 WiFi placeholder. Association, DHCP, RF calibration, retries, and TX dominate energy; deep-sleep wiring matters.";
}
}

#endif
