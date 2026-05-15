#include "radio/GenericRadioProfile.h"
#include "core/EnergyModel.h"

GenericRadioProfile::GenericRadioProfile()
  : txCurrent_(92000UL), rxCurrent_(12000UL), sleepCurrent_(1UL), fixedDurationMs_(100UL),
    rxWindowDurationMs_(0UL), confirmedUplink_(false), durationCallback_(0), confidence_(EcoProfileConfidence::PLACEHOLDER) {}
GenericRadioProfile& GenericRadioProfile::txCurrent_uA(uint32_t value) { txCurrent_ = value; return *this; }
GenericRadioProfile& GenericRadioProfile::rxCurrent_uA(uint32_t value) { rxCurrent_ = value; return *this; }
GenericRadioProfile& GenericRadioProfile::sleepCurrent_uA(uint32_t value) { sleepCurrent_ = value; return *this; }
GenericRadioProfile& GenericRadioProfile::rxWindowDurationMs(uint32_t value) { rxWindowDurationMs_ = value; return *this; }
GenericRadioProfile& GenericRadioProfile::confirmedUplink(bool enabled) { confirmedUplink_ = enabled; return *this; }
GenericRadioProfile& GenericRadioProfile::estimatedTxDurationMs(EcoRadioDurationCallback callback) { durationCallback_ = callback; return *this; }
GenericRadioProfile& GenericRadioProfile::fixedTxDurationMs(uint32_t value) { fixedDurationMs_ = value; return *this; }
GenericRadioProfile& GenericRadioProfile::confidence(EcoProfileConfidence confidence) { confidence_ = confidence; return *this; }
bool GenericRadioProfile::sleep() { return true; }
bool GenericRadioProfile::wake() { return true; }
uint32_t GenericRadioProfile::estimateTxDurationMs(size_t payloadBytes) const { return durationCallback_ ? durationCallback_(payloadBytes) : (fixedDurationMs_ + (uint32_t)payloadBytes); }
uint32_t GenericRadioProfile::txCurrent_uA() const { return txCurrent_; }
uint32_t GenericRadioProfile::rxCurrent_uA() const { return rxCurrent_; }
uint32_t GenericRadioProfile::sleepCurrent_uA() const { return sleepCurrent_; }
uint32_t GenericRadioProfile::estimateRxWindowDurationMs() const { return rxWindowDurationMs_; }
bool GenericRadioProfile::expectsRxWindow() const { return rxWindowDurationMs_ > 0UL || confirmedUplink_; }
bool GenericRadioProfile::confirmedUplink() const { return confirmedUplink_; }
EcoProfileConfidence GenericRadioProfile::confidence() const { return confidence_; }
float GenericRadioProfile::estimateTxEnergy_mJ(float voltage, size_t payloadBytes) const { return EnergyModel::energyMilliJoules(voltage, txCurrent_, estimateTxDurationMs(payloadBytes)); }
float GenericRadioProfile::estimateRxWindowEnergy_mJ(float voltage) const { return EnergyModel::energyMilliJoules(voltage, rxCurrent_, estimateRxWindowDurationMs()); }
