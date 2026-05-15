#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_PRO_MINI_3V3_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_PRO_MINI_3V3_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoProMini3V3() {
  return BoardProfile("Arduino Pro Mini 3.3V placeholder", 6000UL, 150UL, 2500UL, 6000UL, false,
                      "Placeholder profile. Low-power capable only after regulator and power LED modifications; board clone and bootloader/fuse choices matter.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
