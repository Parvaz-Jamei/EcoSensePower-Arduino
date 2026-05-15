#include "harvester/SolarHarvester.h"

SolarHarvester::SolarHarvester()
  : callback_(0), fixed_mW_(0.0f), hasFixed_(false), storageEfficiencyPercent_(70.0f), confidence_(EcoProfileConfidence::PLACEHOLDER) {}
SolarHarvester& SolarHarvester::readMilliWatt(EcoPowerReadCallback callback) { callback_ = callback; return *this; }
SolarHarvester& SolarHarvester::fixedMilliWatt(float value) { fixed_mW_ = value < 0.0f ? 0.0f : value; hasFixed_ = true; return *this; }
SolarHarvester& SolarHarvester::storageEfficiencyPercent(float value) { if (value < 0.0f) value = 0.0f; if (value > 100.0f) value = 100.0f; storageEfficiencyPercent_ = value; return *this; }
SolarHarvester& SolarHarvester::confidence(EcoProfileConfidence confidence) { confidence_ = confidence; return *this; }
const char* SolarHarvester::notes() const { return "Solar input depends on irradiance, panel angle, charger/storage efficiency, temperature, and duty cycle; validate with measured hardware before runtime claims."; }
float SolarHarvester::inputPowerMilliWatt() const { return callback_ ? callback_() : (hasFixed_ ? fixed_mW_ : 0.0f); }
bool SolarHarvester::available() const { return callback_ || hasFixed_; }
EcoProfileConfidence SolarHarvester::confidence() const { return confidence_; }
float SolarHarvester::storageEfficiencyPercent() const { return storageEfficiencyPercent_; }
