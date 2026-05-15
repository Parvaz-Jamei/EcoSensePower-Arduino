#include "util/VoltageDivider.h"

VoltageDivider::VoltageDivider(uint8_t pin, float r1_kohm, float r2_kohm, float vref, uint16_t adcMax)
  : pin_(pin), r1_kohm_(r1_kohm), r2_kohm_(r2_kohm), vref_(vref), adcMax_(adcMax == 0U ? 1023U : adcMax) {}

float VoltageDivider::scaleRaw(uint16_t raw) const {
  if (r1_kohm_ < 0.0f || r2_kohm_ <= 0.0f || vref_ <= 0.0f || adcMax_ == 0U) {
    return 0.0f;
  }
  const float adcVoltage = ((float)raw * vref_) / (float)adcMax_;
  return adcVoltage * ((r1_kohm_ + r2_kohm_) / r2_kohm_);
}

float VoltageDivider::readVoltage() const {
  return scaleRaw((uint16_t)analogRead(pin_));
}

float VoltageDivider::dividerCurrent_uA(float measuredVoltageV) const {
  const float total_kohm = r1_kohm_ + r2_kohm_;
  if (measuredVoltageV <= 0.0f || total_kohm <= 0.0f) {
    return 0.0f;
  }
  // V / kOhm == mA; convert mA to uA.
  return (measuredVoltageV / total_kohm) * 1000.0f;
}
