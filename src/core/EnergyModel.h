#ifndef ECOSENSE_CORE_ENERGYMODEL_H
#define ECOSENSE_CORE_ENERGYMODEL_H

#include <stdint.h>

class EnergyModel {
public:
  static float energyMilliJoules(float voltageV, uint32_t currentMicroA, uint32_t durationMs);
  static float averageCurrentMicroA(float energyMilliJoules, float voltageV, uint32_t cycleMs);
};

#endif
