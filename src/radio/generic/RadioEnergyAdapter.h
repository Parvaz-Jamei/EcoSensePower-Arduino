#ifndef ECOSENSE_RADIO_GENERIC_RADIOENERGYADAPTER_H
#define ECOSENSE_RADIO_GENERIC_RADIOENERGYADAPTER_H

#include <Arduino.h>
#include <stddef.h>
#include <stdint.h>
#include "core/EcoTypes.h"

class RadioEnergyAdapter {
public:
  virtual ~RadioEnergyAdapter() {}
  virtual bool sleep() = 0;
  virtual bool wake() = 0;
  virtual uint32_t estimateTxDurationMs(size_t payloadBytes) const = 0;
  virtual uint32_t txCurrent_uA() const = 0;
  virtual uint32_t rxCurrent_uA() const = 0;
  virtual uint32_t sleepCurrent_uA() const = 0;
  virtual uint32_t estimateRxWindowDurationMs() const { return 0UL; }
  virtual bool expectsRxWindow() const { return false; }
  virtual bool confirmedUplink() const { return false; }
  virtual EcoProfileConfidence confidence() const { return EcoProfileConfidence::PLACEHOLDER; }
};

class NullRadioEnergyAdapter : public RadioEnergyAdapter {
public:
  bool sleep() override { return true; }
  bool wake() override { return true; }
  uint32_t estimateTxDurationMs(size_t payloadBytes) const override { return (uint32_t)payloadBytes; }
  uint32_t txCurrent_uA() const override { return 0; }
  uint32_t rxCurrent_uA() const override { return 0; }
  uint32_t sleepCurrent_uA() const override { return 0; }
};

#endif
