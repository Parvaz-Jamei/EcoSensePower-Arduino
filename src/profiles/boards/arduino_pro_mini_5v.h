#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_PRO_MINI_5V_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_PRO_MINI_5V_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoProMini5V() {
  return BoardProfile("Arduino Pro Mini 5V placeholder", 9000UL, 250UL, 3000UL, 9000UL, false,
                      "Placeholder profile. Low-power claims require regulator/LED modifications and measured sleep current; 5V rail changes sensor and divider assumptions.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
