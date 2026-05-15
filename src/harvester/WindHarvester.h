#ifndef ECOSENSE_HARVESTER_WINDHARVESTER_H
#define ECOSENSE_HARVESTER_WINDHARVESTER_H

#include "harvester/HarvesterBase.h"

typedef float (*WindHarvesterPowerCallback)();

class WindHarvester : public HarvesterBase {
public:
  WindHarvester();
  WindHarvester& readMilliWatt(WindHarvesterPowerCallback callback);
  WindHarvester& fixedMilliWatt(float value);
  WindHarvester& storageEfficiencyPercent(float value);
  WindHarvester& confidence(EcoProfileConfidence confidence);
  const char* notes() const;
  float inputPowerMilliWatt() const override;
  bool available() const override;
  EcoProfileConfidence confidence() const override;
  float storageEfficiencyPercent() const override;
private:
  WindHarvesterPowerCallback callback_;
  float fixed_mW_;
  bool hasFixed_;
  float storageEfficiencyPercent_;
  EcoProfileConfidence confidence_;
};

#endif
