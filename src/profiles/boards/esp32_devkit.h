#ifndef ECOSENSE_PROFILES_BOARDS_ESP32_DEVKIT_H
#define ECOSENSE_PROFILES_BOARDS_ESP32_DEVKIT_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ESP32DevKit() {
  return BoardProfile("ESP32 DevKit placeholder", 80000UL, 5000UL, 8000UL, 80000UL, false,
                      "Placeholder profile. Dev board current can differ drastically from the bare ESP32-WROOM module due to regulator, USB bridge, LEDs, and onboard peripherals.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
