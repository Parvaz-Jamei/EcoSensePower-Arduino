#ifndef ECOSENSE_PROFILES_BOARDS_RASPBERRY_PI_PICO_H
#define ECOSENSE_PROFILES_BOARDS_RASPBERRY_PI_PICO_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile RaspberryPiPico() {
  return BoardProfile("Raspberry Pi Pico / RP2040 placeholder", 30000UL, 1000UL, 5000UL, 30000UL, false,
                      "Placeholder profile. Guarded compile-readiness/generic fallback unless a measured RP2040 backend and board-current evidence are attached.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
