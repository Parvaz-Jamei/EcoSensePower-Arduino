#include "harvester/WindHarvester.h"

WindHarvester::WindHarvester()
  : callback_(0), fixed_mW_(0.0f), hasFixed_(false), storageEfficiencyPercent_(60.0f), confidence_(EcoProfileConfidence::PLACEHOLDER) {}
WindHarvester& WindHarvester::readMilliWatt(WindHarvesterPowerCallback callback) { callback_ = callback; return *this; }
WindHarvester& WindHarvester::fixedMilliWatt(float value) { fixed_mW_ = value < 0.0f ? 0.0f : value; hasFixed_ = true; return *this; }
WindHarvester& WindHarvester::storageEfficiencyPercent(float value) { if (value < 0.0f) value = 0.0f; if (value > 100.0f) value = 100.0f; storageEfficiencyPercent_ = value; return *this; }
WindHarvester& WindHarvester::confidence(EcoProfileConfidence confidence) { confidence_ = confidence; return *this; }
const char* WindHarvester::notes() const { return "Highly variable source; turbine startup speed, rectification, storage, and converter efficiency matter."; }
float WindHarvester::inputPowerMilliWatt() const { return callback_ ? callback_() : (hasFixed_ ? fixed_mW_ : 0.0f); }
bool WindHarvester::available() const { return callback_ || hasFixed_; }
EcoProfileConfidence WindHarvester::confidence() const { return confidence_; }
float WindHarvester::storageEfficiencyPercent() const { return storageEfficiencyPercent_; }
