#ifndef ECOSENSE_CORE_PERIPHERALGUARD_H
#define ECOSENSE_CORE_PERIPHERALGUARD_H

#include "core/EcoTypes.h"

struct EcoGuardSlot {
  bool active;
  const char* name;
  int8_t powerPin;
  uint8_t activeLevel;
  uint32_t warmupTimeMs;
  EcoVoidCallback wakeCallback;
  EcoVoidCallback sleepCallback;
  bool esp32Wireless;
  bool failed;

  EcoGuardSlot()
    : active(false), name("guard"), powerPin(-1), activeLevel(HIGH), warmupTimeMs(0),
      wakeCallback(0), sleepCallback(0), esp32Wireless(false), failed(false) {}
};

class EcoGuardConfig {
public:
  EcoGuardConfig();
  explicit EcoGuardConfig(EcoGuardSlot* slot);

  EcoGuardConfig& powerPin(uint8_t pin);
  EcoGuardConfig& activeLevel(uint8_t level);
  EcoGuardConfig& warmupTimeMs(uint32_t value);
  EcoGuardConfig& onWake(EcoVoidCallback callback);
  EcoGuardConfig& onSleep(EcoVoidCallback callback);
  EcoGuardConfig& esp32Wireless(bool enabled = true);
  bool valid() const;

private:
  EcoGuardSlot* slot_;
};

#endif
