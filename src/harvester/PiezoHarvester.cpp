#include "harvester/PiezoHarvester.h"

PiezoHarvester::PiezoHarvester()
  : callback_(0), fixed_mW_(0.0f), hasFixed_(false), storageEfficiencyPercent_(60.0f), confidence_(EcoProfileConfidence::PLACEHOLDER) {}
PiezoHarvester& PiezoHarvester::readMilliWatt(PiezoHarvesterPowerCallback callback) { callback_ = callback; return *this; }
PiezoHarvester& PiezoHarvester::fixedMilliWatt(float value) { fixed_mW_ = value < 0.0f ? 0.0f : value; hasFixed_ = true; return *this; }
PiezoHarvester& PiezoHarvester::storageEfficiencyPercent(float value) { if (value < 0.0f) value = 0.0f; if (value > 100.0f) value = 100.0f; storageEfficiencyPercent_ = value; return *this; }
PiezoHarvester& PiezoHarvester::confidence(EcoProfileConfidence confidence) { confidence_ = confidence; return *this; }
const char* PiezoHarvester::notes() const { return "Intermittent vibration source; requires rectifier, storage, and mechanical coupling model."; }
float PiezoHarvester::inputPowerMilliWatt() const { return callback_ ? callback_() : (hasFixed_ ? fixed_mW_ : 0.0f); }
bool PiezoHarvester::available() const { return callback_ || hasFixed_; }
EcoProfileConfidence PiezoHarvester::confidence() const { return confidence_; }
float PiezoHarvester::storageEfficiencyPercent() const { return storageEfficiencyPercent_; }
