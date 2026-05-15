#ifndef ECOSENSE_CORE_MEASUREDPROFILE_H
#define ECOSENSE_CORE_MEASUREDPROFILE_H

#include "core/BoardProfile.h"

class MeasuredProfileBuilder {
public:
  MeasuredProfileBuilder()
    : profile_(BoardProfile::Generic()),
      activeConfidence_(EcoProfileConfidence::PLACEHOLDER),
      sleepConfidence_(EcoProfileConfidence::PLACEHOLDER),
      sensorReadConfidence_(EcoProfileConfidence::PLACEHOLDER),
      processConfidence_(EcoProfileConfidence::PLACEHOLDER) {
    applyAggregateConfidence();
  }

  MeasuredProfileBuilder& name(const char* value) { profile_.name = value; return *this; }
  MeasuredProfileBuilder& activeCurrent_uA(uint32_t value, EcoProfileConfidence confidence = EcoProfileConfidence::MEASURED) { profile_.activeCurrent_uA = value; activeConfidence_ = confidence; applyAggregateConfidence(); return *this; }
  MeasuredProfileBuilder& sleepCurrent_uA(uint32_t value, EcoProfileConfidence confidence = EcoProfileConfidence::MEASURED) { profile_.sleepCurrent_uA = value; sleepConfidence_ = confidence; applyAggregateConfidence(); return *this; }
  MeasuredProfileBuilder& sensorReadCurrent_uA(uint32_t value, EcoProfileConfidence confidence = EcoProfileConfidence::MEASURED) { profile_.sensorReadCurrent_uA = value; sensorReadConfidence_ = confidence; applyAggregateConfidence(); return *this; }
  MeasuredProfileBuilder& processCurrent_uA(uint32_t value, EcoProfileConfidence confidence = EcoProfileConfidence::MEASURED) { profile_.processCurrent_uA = value; processConfidence_ = confidence; applyAggregateConfidence(); return *this; }
  MeasuredProfileBuilder& includesRegulatorIq(bool value = true) { profile_.includesRegulatorIq = value; return *this; }
  MeasuredProfileBuilder& includesSensorLeakage(bool value = true) { profile_.includesSensorLeakage = value; return *this; }
  MeasuredProfileBuilder& notes(const char* value) { profile_.notes = value; return *this; }
  BoardProfile build() const { return profile_; }

private:
  static EcoProfileConfidence conservativeAggregate(EcoProfileConfidence a,
                                                    EcoProfileConfidence b,
                                                    EcoProfileConfidence c,
                                                    EcoProfileConfidence d) {
    if (a == EcoProfileConfidence::PLACEHOLDER ||
        b == EcoProfileConfidence::PLACEHOLDER ||
        c == EcoProfileConfidence::PLACEHOLDER ||
        d == EcoProfileConfidence::PLACEHOLDER) {
      return EcoProfileConfidence::PLACEHOLDER;
    }
    if (a == EcoProfileConfidence::DATASHEET ||
        b == EcoProfileConfidence::DATASHEET ||
        c == EcoProfileConfidence::DATASHEET ||
        d == EcoProfileConfidence::DATASHEET) {
      return EcoProfileConfidence::DATASHEET;
    }
    return EcoProfileConfidence::MEASURED;
  }

  void applyAggregateConfidence() {
    profile_.confidence = conservativeAggregate(activeConfidence_, sleepConfidence_, sensorReadConfidence_, processConfidence_);
    profile_.measured = profile_.confidence == EcoProfileConfidence::MEASURED;
  }

  BoardProfile profile_;
  EcoProfileConfidence activeConfidence_;
  EcoProfileConfidence sleepConfidence_;
  EcoProfileConfidence sensorReadConfidence_;
  EcoProfileConfidence processConfidence_;
};

#endif
