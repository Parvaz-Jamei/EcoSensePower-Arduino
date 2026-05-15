#include "test_support.h"
#include <EcoSensePower.h>
uint32_t txMs(size_t bytes) { return 100 + (uint32_t)bytes; }
int main() {
  GenericRadioProfile radio;
  radio.txCurrent_uA(100000).rxCurrent_uA(12000).sleepCurrent_uA(2).estimatedTxDurationMs(txMs).confidence(EcoProfileConfidence::DATASHEET);
  ASSERT_EQ(132L, (long)radio.estimateTxDurationMs(32));
  ASSERT_EQ(2L, (long)radio.sleepCurrent_uA());
  ASSERT_TRUE(radio.estimateTxEnergy_mJ(3.3f, 32) > 0.0f);
  RadioBatcher batcher;
  batcher.batchMaxSamples(2).maxReportIntervalMs(EcoTime::minutes(10));
  batcher.markSample(0);
  ASSERT_TRUE(!batcher.shouldReport(EcoTime::minutes(1)));
  batcher.markSample(EcoTime::minutes(1));
  ASSERT_TRUE(batcher.shouldReport(EcoTime::minutes(1)));
  batcher.clear(EcoTime::minutes(1));
  batcher.markSample(EcoTime::minutes(1));
  ASSERT_TRUE(batcher.shouldReport(EcoTime::minutes(12)));
  return 0;
}
