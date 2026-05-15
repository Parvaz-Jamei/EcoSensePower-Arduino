#ifndef ECOSENSE_PROFILES_BOARDS_ARDUINO_NANO_H
#define ECOSENSE_PROFILES_BOARDS_ARDUINO_NANO_H

#include "core/BoardProfile.h"

namespace EcoProfiles {
inline BoardProfile ArduinoNano() {
  return BoardProfile("Arduino Nano / ATmega328P placeholder", 15000UL, 900UL, 3000UL, 9000UL, false,
                      "Placeholder profile. Classic Nano boards are often dominated by USB bridge, regulator, power LED, and onboard peripherals; measure the exact clone/variant.",
                      EcoProfileConfidence::PLACEHOLDER, false, false);
}
}

#endif
