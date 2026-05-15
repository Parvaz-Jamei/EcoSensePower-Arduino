#ifndef ECOSENSE_ARCH_GENERIC_PERIPHERALGUARD_H
#define ECOSENSE_ARCH_GENERIC_PERIPHERALGUARD_H

class GenericPeripheralGuard {
public:
  void prepareForSleep() {}
  void restoreAfterWake() {}
  const char* name() const { return "generic-noop-guard"; }
};

#endif
