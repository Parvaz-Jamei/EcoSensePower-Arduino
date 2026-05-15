#ifndef ECOSENSE_HARVESTER_THERMOELECTRICHARVESTER_H
#define ECOSENSE_HARVESTER_THERMOELECTRICHARVESTER_H

#include "harvester/HarvesterBase.h"

typedef float (*ThermoelectricHarvesterPowerCallback)();

class ThermoelectricHarvester : public HarvesterBase {
public:
  ThermoelectricHarvester();
  ThermoelectricHarvester& readMilliWatt(ThermoelectricHarvesterPowerCallback callback);
  ThermoelectricHarvester& fixedMilliWatt(float value);
  ThermoelectricHarvester& storageEfficiencyPercent(float value);
  ThermoelectricHarvester& confidence(EcoProfileConfidence confidence);
  const char* notes() const;
  float inputPowerMilliWatt() const override;
  bool available() const override;
  EcoProfileConfidence confidence() const override;
  float storageEfficiencyPercent() const override;
private:
  ThermoelectricHarvesterPowerCallback callback_;
  float fixed_mW_;
  bool hasFixed_;
  float storageEfficiencyPercent_;
  EcoProfileConfidence confidence_;
};

#endif
