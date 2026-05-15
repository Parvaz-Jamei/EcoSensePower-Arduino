#include "test_support.h"
#include <EcoSensePower.h>
int main() {
  ASSERT_EQ(EcoTime::days(1), 86400000UL);
  ASSERT_EQ(EcoTime::fromHz(1.0f), 1000UL);
  ASSERT_EQ(EcoTime::fromHz(0.0f), 0UL);
  float hz = EcoTime::toHz(1000UL);
  ASSERT_TRUE(hz > 0.99f && hz < 1.01f);
  ASSERT_TRUE(EcoTime::fromHz(1.0f / 300.0f) >= 299000UL);
  return 0;
}
