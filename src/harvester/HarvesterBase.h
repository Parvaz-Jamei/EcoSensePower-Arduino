#ifndef ECOSENSE_HARVESTER_BASE_H
#define ECOSENSE_HARVESTER_BASE_H

#include "core/EcoTypes.h"

class HarvesterBase {
public:
  virtual ~HarvesterBase() {}
  virtual float inputPowerMilliWatt() const = 0;
  virtual bool available() const = 0;
  virtual EcoProfileConfidence confidence() const { return EcoProfileConfidence::PLACEHOLDER; }
  virtual float storageEfficiencyPercent() const { return 100.0f; }
};

class NullHarvester : public HarvesterBase {
public:
  float inputPowerMilliWatt() const { return 0.0f; }
  bool available() const { return false; }
  EcoProfileConfidence confidence() const { return EcoProfileConfidence::PLACEHOLDER; }
  float storageEfficiencyPercent() const { return 0.0f; }
};

#endif
