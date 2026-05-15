#ifndef ECOSENSE_CORE_PROFILECONFIDENCE_H
#define ECOSENSE_CORE_PROFILECONFIDENCE_H

#include "core/EcoTypes.h"

struct EcoConfidenceSummary {
  EcoProfileConfidence board;
  EcoProfileConfidence battery;
  EcoProfileConfidence sensor;
  EcoProfileConfidence radio;
  EcoProfileConfidence harvester;

  EcoConfidenceSummary()
    : board(EcoProfileConfidence::PLACEHOLDER), battery(EcoProfileConfidence::PLACEHOLDER),
      sensor(EcoProfileConfidence::PLACEHOLDER), radio(EcoProfileConfidence::PLACEHOLDER),
      harvester(EcoProfileConfidence::PLACEHOLDER) {}

  bool hasMeasuredCore() const {
    return board == EcoProfileConfidence::MEASURED && battery == EcoProfileConfidence::MEASURED;
  }
};

#endif
