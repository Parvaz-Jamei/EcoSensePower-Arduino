/*
  EcoSensePower LoRaAdaptiveReporter.

  LoRa-style reporting energy-model example. It demonstrates adaptive reporting and
  radio budget planning only; EcoSensePower is not a LoRaWAN stack, RadioLib wrapper,
  SX127x driver, or network server integration.

  Default build is dependency-free. Real LoRa communication remains user-side and must
  be validated with the selected hardware and radio library.
*/

#include <EcoSensePower.h>
#include <string.h>
#include <radio/generic/RadioEnergyAdapter.h>

EcoSensePower node;
NullRadioEnergyAdapter radioEnergy;

size_t estimateLoRaPayload(const EcoReport& report) {
  // Placeholder for an application-owned payload encoder.
  return 8 + (report.sensorName ? strlen(report.sensorName) : 0);
}

void setup() {
  Serial.begin(115200);

  node.radio(&radioEnergy);
  node.reportPayloadEstimator(estimateLoRaPayload);
  node.reporting().batchMaxSamples(3).maxReportIntervalMs(EcoTime::minutes(10));

  node.guard("radio-energy")
    .onWake([]() {
      radioEnergy.wake();
    })
    .onSleep([]() {
      radioEnergy.sleep();
    });

  node.sensor("lora-payload")
    .read([]() -> float { return (float)analogRead(A0); })
    .minIntervalMs(EcoTime::seconds(10))
    .maxIntervalMs(EcoTime::minutes(5))
    .changeThreshold(20.0f)
    .onSleep([]() {});

  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
    Serial.print(F("LoRaAdaptiveReporter payload estimate bytes: "));
    Serial.println((unsigned long)estimateLoRaPayload(report));
    Serial.print(F("Estimated TX duration placeholder ms: "));
    Serial.println((unsigned long)radioEnergy.estimateTxDurationMs(estimateLoRaPayload(report)));
  });

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
}
