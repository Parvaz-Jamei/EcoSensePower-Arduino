#include "core/PeripheralGuard.h"

EcoGuardConfig::EcoGuardConfig()
  : slot_(0) {}

EcoGuardConfig::EcoGuardConfig(EcoGuardSlot* slot)
  : slot_(slot) {}

EcoGuardConfig& EcoGuardConfig::powerPin(uint8_t pin) {
  if (slot_) slot_->powerPin = (int8_t)pin;
  return *this;
}

EcoGuardConfig& EcoGuardConfig::activeLevel(uint8_t level) {
  if (slot_) slot_->activeLevel = level;
  return *this;
}

EcoGuardConfig& EcoGuardConfig::warmupTimeMs(uint32_t value) {
  if (slot_) slot_->warmupTimeMs = value;
  return *this;
}

EcoGuardConfig& EcoGuardConfig::onWake(EcoVoidCallback callback) {
  if (slot_) slot_->wakeCallback = callback;
  return *this;
}

EcoGuardConfig& EcoGuardConfig::onSleep(EcoVoidCallback callback) {
  if (slot_) slot_->sleepCallback = callback;
  return *this;
}

EcoGuardConfig& EcoGuardConfig::esp32Wireless(bool enabled) {
  if (slot_) slot_->esp32Wireless = enabled;
  return *this;
}

bool EcoGuardConfig::valid() const {
  return slot_ != 0;
}
