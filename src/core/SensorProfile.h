#ifndef ECOSENSE_CORE_SENSORPROFILE_H
#define ECOSENSE_CORE_SENSORPROFILE_H

#include "core/EcoTypes.h"
#include <stdint.h>

struct EcoSensorProfile {
  const char* name;
  uint32_t warmupTimeMs;
  uint32_t readCurrent_uA;
  uint32_t sleepCurrent_uA;
  bool measured;
  EcoProfileConfidence confidence;
  const char* notes;

  EcoSensorProfile(const char* profileName = "Generic sensor",
                   uint32_t warmupMs = 0UL,
                   uint32_t read_uA = 0UL,
                   uint32_t sleep_uA = 0UL,
                   bool isMeasured = false,
                   EcoProfileConfidence profileConfidence = EcoProfileConfidence::PLACEHOLDER,
                   const char* profileNotes = "Placeholder sensor profile.")
    : name(profileName), warmupTimeMs(warmupMs), readCurrent_uA(read_uA), sleepCurrent_uA(sleep_uA),
      measured(isMeasured), confidence(ecoNormalizeProfileConfidence(isMeasured, profileConfidence)), notes(profileNotes) {}
};

#endif
