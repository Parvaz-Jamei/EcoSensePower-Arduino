#include "harvester/ThermoelectricHarvester.h"

ThermoelectricHarvester::ThermoelectricHarvester()
  : callback_(0), fixed_mW_(0.0f), hasFixed_(false), storageEfficiencyPercent_(60.0f), confidence_(EcoProfileConfidence::PLACEHOLDER) {}
ThermoelectricHarvester& ThermoelectricHarvester::readMilliWatt(ThermoelectricHarvesterPowerCallback callback) { callback_ = callback; return *this; }
ThermoelectricHarvester& ThermoelectricHarvester::fixedMilliWatt(float value) { fixed_mW_ = value < 0.0f ? 0.0f : value; hasFixed_ = true; return *this; }
ThermoelectricHarvester& ThermoelectricHarvester::storageEfficiencyPercent(float value) { if (value < 0.0f) value = 0.0f; if (value > 100.0f) value = 100.0f; storageEfficiencyPercent_ = value; return *this; }
ThermoelectricHarvester& ThermoelectricHarvester::confidence(EcoProfileConfidence confidence) { confidence_ = confidence; return *this; }
const char* ThermoelectricHarvester::notes() const { return "Depends on temperature gradient, thermal path, converter efficiency, and cold-side conditions."; }
float ThermoelectricHarvester::inputPowerMilliWatt() const { return callback_ ? callback_() : (hasFixed_ ? fixed_mW_ : 0.0f); }
bool ThermoelectricHarvester::available() const { return callback_ || hasFixed_; }
EcoProfileConfidence ThermoelectricHarvester::confidence() const { return confidence_; }
float ThermoelectricHarvester::storageEfficiencyPercent() const { return storageEfficiencyPercent_; }
