#ifndef ECOSENSE_RADIO_GENERICRADIOPROFILE_H
#define ECOSENSE_RADIO_GENERICRADIOPROFILE_H

#include "radio/RadioEnergyAdapter.h"
#include "core/EcoTypes.h"

typedef uint32_t (*EcoRadioDurationCallback)(size_t payloadBytes);

class GenericRadioProfile : public RadioEnergyAdapter {
public:
  GenericRadioProfile();
  GenericRadioProfile& txCurrent_uA(uint32_t value);
  GenericRadioProfile& rxCurrent_uA(uint32_t value);
  GenericRadioProfile& sleepCurrent_uA(uint32_t value);
  GenericRadioProfile& rxWindowDurationMs(uint32_t value);
  GenericRadioProfile& confirmedUplink(bool enabled = true);
  GenericRadioProfile& estimatedTxDurationMs(EcoRadioDurationCallback callback);
  GenericRadioProfile& fixedTxDurationMs(uint32_t value);
  GenericRadioProfile& confidence(EcoProfileConfidence confidence);

  bool sleep() override;
  bool wake() override;
  uint32_t estimateTxDurationMs(size_t payloadBytes) const override;
  uint32_t txCurrent_uA() const override;
  uint32_t rxCurrent_uA() const override;
  uint32_t sleepCurrent_uA() const override;
  uint32_t estimateRxWindowDurationMs() const override;
  bool expectsRxWindow() const override;
  bool confirmedUplink() const override;
  EcoProfileConfidence confidence() const override;
  float estimateTxEnergy_mJ(float voltage, size_t payloadBytes) const;
  float estimateRxWindowEnergy_mJ(float voltage) const;

private:
  uint32_t txCurrent_;
  uint32_t rxCurrent_;
  uint32_t sleepCurrent_;
  uint32_t fixedDurationMs_;
  uint32_t rxWindowDurationMs_;
  bool confirmedUplink_;
  EcoRadioDurationCallback durationCallback_;
  EcoProfileConfidence confidence_;
};

#endif
