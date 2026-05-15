#ifndef ECOSENSE_PROFILES_BOARDS_ESP8266_NODEMCU_H
#define ECOSENSE_PROFILES_BOARDS_ESP8266_NODEMCU_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ESP8266NodeMCU() {
  return BoardProfile("ESP8266 NodeMCU placeholder", 80000UL, 8000UL, 7000UL, 80000UL, false,
                      "Placeholder profile. USB bridge, regulator, power LED, and deep-sleep wiring dominate real board current; WiFi association/TX must be modeled separately.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
