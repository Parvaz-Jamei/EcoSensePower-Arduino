#ifndef ECOSENSE_PROFILES_BOARDS_ATTINY85_H
#define ECOSENSE_PROFILES_BOARDS_ATTINY85_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ATtiny85() {
  return BoardProfile("ATtiny85 placeholder", 3000UL, 20UL, 1500UL, 3000UL, false,
                      "Placeholder profile. Very board/package/clock/fuse dependent. Bare MCU and breakout boards have very different current profiles.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
