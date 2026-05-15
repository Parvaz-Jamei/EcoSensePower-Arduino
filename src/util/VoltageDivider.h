#ifndef ECOSENSE_UTIL_VOLTAGEDIVIDER_H
#define ECOSENSE_UTIL_VOLTAGEDIVIDER_H

#include <Arduino.h>
#include <stdint.h>

class VoltageDivider {
public:
  VoltageDivider(uint8_t pin, float r1_kohm, float r2_kohm, float vref = 5.0f, uint16_t adcMax = 1023U);
  float readVoltage() const;
  float scaleRaw(uint16_t raw) const;
  float dividerCurrent_uA(float measuredVoltageV) const;
private:
  uint8_t pin_;
  float r1_kohm_;
  float r2_kohm_;
  float vref_;
  uint16_t adcMax_;
};

#endif
