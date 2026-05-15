#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_MKR_WAN_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_MKR_WAN_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoMkrWan() {
  return BoardProfile("Arduino MKR WAN placeholder", 30000UL, 1200UL, 4000UL, 25000UL, false,
                      "Placeholder profile. MKR WAN includes a LoRa radio module; board baseline and radio energy must be modeled separately.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
