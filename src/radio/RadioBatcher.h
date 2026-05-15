#ifndef ECOSENSE_RADIO_RADIOBATCHER_H
#define ECOSENSE_RADIO_RADIOBATCHER_H

#include <stdint.h>

struct EcoRadioBatchSummary {
  uint8_t count;
  float latest;
  float minValue;
  float maxValue;
  uint32_t firstTimestampMs;
  uint32_t lastTimestampMs;
  bool limited;
  EcoRadioBatchSummary()
    : count(0), latest(0.0f), minValue(0.0f), maxValue(0.0f), firstTimestampMs(0), lastTimestampMs(0), limited(false) {}
};

class RadioBatcher {
public:
  RadioBatcher()
    : batchMaxSamples_(1), maxReportIntervalMs_(3600000UL), pendingSamples_(0), lastReportMs_(0),
      latest_(0.0f), minValue_(0.0f), maxValue_(0.0f), firstTimestampMs_(0), lastTimestampMs_(0), limited_(false) {}
  RadioBatcher& batchMaxSamples(uint8_t value) { batchMaxSamples_ = value == 0 ? 1 : value; return *this; }
  RadioBatcher& maxReportIntervalMs(uint32_t value) { maxReportIntervalMs_ = value; return *this; }
  void markSample(uint32_t nowMs) { markSample(nowMs, 0.0f); }
  void markSample(uint32_t nowMs, float value) {
    if (pendingSamples_ == 0) {
      firstTimestampMs_ = nowMs;
      minValue_ = value;
      maxValue_ = value;
      if (lastReportMs_ == 0) lastReportMs_ = nowMs;
    } else {
      if (value < minValue_) minValue_ = value;
      if (value > maxValue_) maxValue_ = value;
    }
    latest_ = value;
    lastTimestampMs_ = nowMs;
    if (pendingSamples_ < 255) ++pendingSamples_; else limited_ = true;
  }
  bool shouldReport(uint32_t nowMs) const { return pendingSamples_ >= batchMaxSamples_ || (pendingSamples_ > 0 && (uint32_t)(nowMs - lastReportMs_) >= maxReportIntervalMs_); }
  void clear(uint32_t nowMs) { pendingSamples_ = 0; lastReportMs_ = nowMs; latest_ = 0.0f; minValue_ = 0.0f; maxValue_ = 0.0f; firstTimestampMs_ = 0; lastTimestampMs_ = 0; limited_ = false; }
  uint8_t pendingSamples() const { return pendingSamples_; }
  bool limited() const { return limited_; }
  EcoRadioBatchSummary summary() const {
    EcoRadioBatchSummary s;
    s.count = pendingSamples_;
    s.latest = latest_;
    s.minValue = minValue_;
    s.maxValue = maxValue_;
    s.firstTimestampMs = firstTimestampMs_;
    s.lastTimestampMs = lastTimestampMs_;
    s.limited = limited_;
    return s;
  }
private:
  uint8_t batchMaxSamples_;
  uint32_t maxReportIntervalMs_;
  uint8_t pendingSamples_;
  uint32_t lastReportMs_;
  float latest_;
  float minValue_;
  float maxValue_;
  uint32_t firstTimestampMs_;
  uint32_t lastTimestampMs_;
  bool limited_;
};

#endif
