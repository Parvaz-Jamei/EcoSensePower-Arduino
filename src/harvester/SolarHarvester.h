#ifndef ECOSENSE_HARVESTER_SOLAR_H
#define ECOSENSE_HARVESTER_SOLAR_H

#include "harvester/HarvesterBase.h"

typedef float (*EcoPowerReadCallback)();

class SolarHarvester : public HarvesterBase {
public:
  SolarHarvester();
  SolarHarvester& readMilliWatt(EcoPowerReadCallback callback);
  SolarHarvester& fixedMilliWatt(float value);
  SolarHarvester& storageEfficiencyPercent(float value);
  SolarHarvester& confidence(EcoProfileConfidence confidence);
  const char* notes() const;
  float inputPowerMilliWatt() const override;
  bool available() const override;
  EcoProfileConfidence confidence() const override;
  float storageEfficiencyPercent() const override;
private:
  EcoPowerReadCallback callback_;
  float fixed_mW_;
  bool hasFixed_;
  float storageEfficiencyPercent_;
  EcoProfileConfidence confidence_;
};

#endif
