#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_NANO_EVERY_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_NANO_EVERY_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoNanoEvery() {
  return BoardProfile("Arduino Nano Every placeholder", 20000UL, 1200UL, 3500UL, 15000UL, false,
                      "Placeholder profile. ATmega4809 board profile placeholder; USB bridge, regulator, LEDs, and board variant affect real current.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
