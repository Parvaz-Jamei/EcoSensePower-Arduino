/*
  EcoSensePower RadioEnergyBudget.

  Radio energy-model example for estimating TX/RX/sleep budget and reporting cadence.
  EcoSensePower is not a LoRaWAN stack, RF driver, WiFi replacement, or Bluetooth
  manager.

  Default build is dependency-free and uses profiles/placeholders. Real communication
  remains application-owned through the user's selected radio library.
*/

#include <EcoSensePower.h>
#include <string.h>

EcoSensePower node;
GenericRadioProfile radio;

uint32_t estimateAirtime(size_t bytes) {
  return 80UL + (uint32_t)bytes * 8UL; // Replace with application-specific LoRa/FSK airtime estimate.
}

float readSensor() {
  return (float)analogRead(A0);
}

size_t estimatePayloadBytes(const EcoReport& report) {
  // Application-owned estimate: header + name + float value + status.
  return 12 + (report.sensorName ? strlen(report.sensorName) : 0) + 8;
}

void setup() {
  Serial.begin(115200);
  radio.txCurrent_uA(92000)
       .rxCurrent_uA(12000)
       .sleepCurrent_uA(1)
       .estimatedTxDurationMs(estimateAirtime)
       .confidence(EcoProfileConfidence::PLACEHOLDER);

  node.radio(&radio);
  node.reportPayloadEstimator(estimatePayloadBytes);
  node.reporting().batchMaxSamples(4).maxReportIntervalMs(EcoTime::hours(1));
  node.sensor("payload")
      .read(readSensor)
      .minIntervalMs(EcoTime::minutes(10))
      .maxIntervalMs(EcoTime::hours(2))
      .changeThreshold(10.0f);
  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
    Serial.print(F("Payload estimate bytes: "));
    Serial.println((unsigned long)estimatePayloadBytes(report));
    Serial.print(F("TX duration for 8/32/64 bytes ms: "));
    Serial.print((unsigned long)radio.estimateTxDurationMs(8));
    Serial.print(F(" / "));
    Serial.print((unsigned long)radio.estimateTxDurationMs(32));
    Serial.print(F(" / "));
    Serial.println((unsigned long)radio.estimateTxDurationMs(64));
    node.ledger().printCycleTo(Serial);
  });
  node.begin();
}

void loop() {
  node.loop();
}
