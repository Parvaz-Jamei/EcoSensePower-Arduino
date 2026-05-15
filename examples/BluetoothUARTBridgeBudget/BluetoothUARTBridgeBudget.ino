/*
  EcoSensePower BluetoothUARTBridgeBudget.

  Bluetooth Classic/SPP UART bridge energy-model example only. HC-05/HC-06-style
  modules are modeled as external radios/peripherals; EcoSensePower is not a serial
  driver, Bluetooth stack, or SoftwareSerial dependency.

  Default build is dependency-free. Real UART/Bluetooth handling remains in the user's
  sketch and selected hardware library. This example is not part of the AVR UNO/Nano
  smoke gate.
*/

#include <EcoSensePower.h>
#include <profiles/radios/bluetooth/hc05_bluetooth.h>

EcoSensePower node;
GenericRadioProfile bridge = EcoProfiles::HC05Bluetooth();

float readBridgeMetric() { return (float)analogRead(A0); }

size_t estimateBridgePayload(const EcoReport& report) {
  (void)report;
  return 32;
}

void setup() {
  Serial.begin(115200);
  node.radio(&bridge);
  node.reportPayloadEstimator(estimateBridgePayload);
  node.sensor("bluetooth-uart-bridge")
      .read(readBridgeMetric)
      .minIntervalMs(EcoTime::seconds(20))
      .maxIntervalMs(EcoTime::minutes(3))
      .changeThreshold(4.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("HC-05/HC-06 are Bluetooth Classic SPP/UART bridge models, not BLE stacks."));
  });
  node.begin();
}

void loop() { node.loop(); }
