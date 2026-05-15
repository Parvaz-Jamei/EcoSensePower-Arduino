#include "test_support.h"

// Umbrella marker for Phase 4.4 profile coverage.
// Detailed battery/board/sensor/radio profile checks are split into smaller
// translation units so host tests remain fast and predictable on CI runners.
int main() {
  ASSERT_TRUE(true);
  return 0;
}
