#ifndef ECOSENSE_PROFILES_BOARDS_ESP32_WROOM_H
#define ECOSENSE_PROFILES_BOARDS_ESP32_WROOM_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ESP32WroomModule() {
  return BoardProfile("ESP32-WROOM module placeholder", 70000UL, 200UL, 5000UL, 70000UL, false,
                      "Placeholder profile. Module-level profile, not a full development board. Deep sleep depends on firmware, wake sources, and attached circuitry.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
