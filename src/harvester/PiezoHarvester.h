#ifndef ECOSENSE_HARVESTER_PIEZOHARVESTER_H
#define ECOSENSE_HARVESTER_PIEZOHARVESTER_H

#include "harvester/HarvesterBase.h"

typedef float (*PiezoHarvesterPowerCallback)();

class PiezoHarvester : public HarvesterBase {
public:
  PiezoHarvester();
  PiezoHarvester& readMilliWatt(PiezoHarvesterPowerCallback callback);
  PiezoHarvester& fixedMilliWatt(float value);
  PiezoHarvester& storageEfficiencyPercent(float value);
  PiezoHarvester& confidence(EcoProfileConfidence confidence);
  const char* notes() const;
  float inputPowerMilliWatt() const override;
  bool available() const override;
  EcoProfileConfidence confidence() const override;
  float storageEfficiencyPercent() const override;
private:
  PiezoHarvesterPowerCallback callback_;
  float fixed_mW_;
  bool hasFixed_;
  float storageEfficiencyPercent_;
  EcoProfileConfidence confidence_;
};

#endif
