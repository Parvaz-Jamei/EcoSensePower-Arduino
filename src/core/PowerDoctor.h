#ifndef ECOSENSE_CORE_POWERDOCTOR_H
#define ECOSENSE_CORE_POWERDOCTOR_H

#include <Arduino.h>
#include "core/EcoTypes.h"

class EcoRuntime;

class PowerDoctor {
public:
  PowerDoctor();

  uint8_t collect(const EcoRuntime& runtime) const;
  uint8_t collect(const EcoRuntime& runtime, EcoDiagnostic* buffer, uint8_t maxCount) const;
  EcoDiagnosticSnapshot collectSnapshot(const EcoRuntime& runtime, EcoDiagnostic* buffer, uint8_t maxCount) const;
  bool diagnosticsTruncated() const;
  uint8_t diagnosticCount() const;
  EcoDiagnostic diagnosticAt(uint8_t index) const;
  bool hasCriticalDiagnostics() const;
  void print(const EcoRuntime& runtime, Print& out) const;
  void print(const EcoRuntime& runtime, Print& out, EcoDiagnosticSeverity minSeverity) const;

private:
#if ECOSENSE_ENABLE_POWER_DOCTOR_STORAGE && ECOSENSE_MAX_DIAGNOSTICS > 0
  mutable EcoDiagnostic diagnostics_[ECOSENSE_MAX_DIAGNOSTICS];
#endif
  mutable uint8_t diagnosticCount_;
  mutable bool truncated_;

  void clear() const;
  void add(EcoDiagnosticCode code, EcoDiagnosticSeverity severity, const char* subject) const;
};

#endif
