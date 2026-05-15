#ifndef ECOSENSE_CORE_BOARDPROFILE_H
#define ECOSENSE_CORE_BOARDPROFILE_H

#include "core/EcoTypes.h"
#include <stdint.h>

struct BoardProfile {
  const char* name;
  uint32_t activeCurrent_uA;
  uint32_t sleepCurrent_uA;
  uint32_t sensorReadCurrent_uA;
  uint32_t processCurrent_uA;
  bool measured;
  const char* notes;
  EcoProfileConfidence confidence;
  bool includesRegulatorIq;
  bool includesSensorLeakage;

  BoardProfile(const char* profileName = "Generic Arduino",
               uint32_t active_uA = 9000UL,
               uint32_t sleep_uA = 8000UL,
               uint32_t sensorRead_uA = 3000UL,
               uint32_t process_uA = 9000UL,
               bool isMeasured = false,
               const char* profileNotes = "Placeholder current profile.",
               EcoProfileConfidence profileConfidence = EcoProfileConfidence::PLACEHOLDER,
               bool regulatorIqIncluded = false,
               bool sensorLeakageIncluded = false)
    : name(profileName), activeCurrent_uA(active_uA), sleepCurrent_uA(sleep_uA),
      sensorReadCurrent_uA(sensorRead_uA), processCurrent_uA(process_uA), measured(isMeasured),
      notes(profileNotes), confidence(ecoNormalizeProfileConfidence(isMeasured, profileConfidence)),
      includesRegulatorIq(regulatorIqIncluded), includesSensorLeakage(sensorLeakageIncluded) {}

  static BoardProfile Generic() {
    return BoardProfile("Generic Arduino", 9000UL, 8000UL, 3000UL, 9000UL, false,
                        "Placeholder current profile. Replace with measured board-specific current.",
                        EcoProfileConfidence::PLACEHOLDER, false, false);
  }

  static BoardProfile ArduinoUnoPlaceholder() {
    return BoardProfile("Arduino Uno / ATmega328P placeholder", 15000UL, 1000UL, 3000UL, 9000UL, false,
                        "Placeholder only. Board regulator, USB bridge, LEDs, and peripherals dominate real current.",
                        EcoProfileConfidence::PLACEHOLDER, false, false);
  }
};

#endif
