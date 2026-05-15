#include "test_support.h"
#include <EcoSensePower.h>
static int wakeCount = 0;
static int sleepCount = 0;
static float readValue() { return 10.0f; }
static void wakeGuard() { ++wakeCount; }
static void sleepGuard() { ++sleepCount; }
int main() {
  mockSetMillis(0);
  EcoSensePower node;
  node.guard("soil").onWake(wakeGuard).onSleep(sleepGuard);
  node.sensor("soil").read(readValue).minIntervalMs(EcoTime::seconds(5)).maxIntervalMs(EcoTime::seconds(10));
  node.begin();
  node.loop();
  ASSERT_EQ(wakeCount, 1);
  ASSERT_EQ(sleepCount, 1);
  node.loop();
  ASSERT_EQ(wakeCount, 1);
  ASSERT_EQ(sleepCount, 1);
  mockSetMillis(EcoTime::seconds(6));
  node.loop();
  ASSERT_EQ(wakeCount, 2);
  ASSERT_EQ(sleepCount, 2);
  return 0;
}
