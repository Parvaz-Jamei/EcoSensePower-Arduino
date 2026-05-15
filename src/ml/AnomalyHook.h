#ifndef ECOSENSE_ML_ANOMALYHOOK_H
#define ECOSENSE_ML_ANOMALYHOOK_H

typedef bool (*EcoAnomalyCallback)(float score);

class RuleBasedAnomalyHook {
public:
  RuleBasedAnomalyHook() : threshold_(0.75f) {}
  RuleBasedAnomalyHook& threshold(float value) { threshold_ = value; return *this; }
  bool anomaly(float score) const { return score > threshold_; }
private:
  float threshold_;
};

#endif
