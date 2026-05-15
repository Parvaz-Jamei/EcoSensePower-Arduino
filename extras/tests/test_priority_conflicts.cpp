#include "test_support.h"
#include <EcoSensePower.h>
static float readValue() { return 1.0f; }
int main() {
  EcoSensePower node;
  node.battery(BatteryProfile::CR2032());
  node.sensor("a").read(readValue).priority(ECO_CRITICAL).maxEnergyPerWindow_mJ(1.0f, EcoTime::minutes(1));
  node.sensor("b").read(readValue).priority(ECO_CRITICAL);
  EcoDiagnostic d[ECOSENSE_MAX_DIAGNOSTICS];
  EcoDiagnosticSnapshot snapshot = node.collectDiagnosticsSnapshot(d, ECOSENSE_MAX_DIAGNOSTICS);
  ASSERT_TRUE(snapshot.total > 0);
  bool sawMultiple = false;
  bool sawWindow = false;
  for (uint8_t i = 0; i < snapshot.copied; ++i) {
    if (d[i].code == EcoDiagnosticCode::MULTIPLE_CRITICAL_SENSORS) sawMultiple = true;
    if (d[i].code == EcoDiagnosticCode::ENERGY_WINDOW_BUDGET_ACTIVE) sawWindow = true;
  }
  ASSERT_TRUE(sawMultiple);
  ASSERT_TRUE(sawWindow);
  return 0;
}
