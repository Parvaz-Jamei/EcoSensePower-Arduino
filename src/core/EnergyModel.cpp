#include "core/EnergyModel.h"

float EnergyModel::energyMilliJoules(float voltageV, uint32_t currentMicroA, uint32_t durationMs) {
  const float currentA = ((float)currentMicroA) / 1000000.0f;
  const float seconds = ((float)durationMs) / 1000.0f;
  return voltageV * currentA * seconds * 1000.0f;
}

float EnergyModel::averageCurrentMicroA(float energyMilliJoules, float voltageV, uint32_t cycleMs) {
  if (voltageV <= 0.0f || cycleMs == 0) {
    return 0.0f;
  }
  const float joules = energyMilliJoules / 1000.0f;
  const float seconds = ((float)cycleMs) / 1000.0f;
  const float amps = joules / (voltageV * seconds);
  return amps * 1000000.0f;
}
