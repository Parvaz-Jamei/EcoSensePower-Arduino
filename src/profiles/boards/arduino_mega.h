#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_MEGA_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_MEGA_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoMega() {
  return BoardProfile("Arduino Mega 2560 placeholder", 70000UL, 15000UL, 6000UL, 50000UL, false,
                      "Placeholder profile. Large board with regulator, USB bridge, LEDs, and many peripherals; not representative of a bare ATmega2560.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
