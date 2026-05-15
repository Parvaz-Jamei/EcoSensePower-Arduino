/*
  EcoSensePower BluetoothConnectionBudget.

  BLE connection-interval energy-model example only. It models radio budget tradeoffs;
  it does not create BLE services, connect to peers, or manage protocol state.

  Default build is dependency-free. Real BLE communication remains application-owned
  through optional libraries such as ArduinoBLE or board-specific ESP32 BLE APIs. This
  example targets larger boards and is not an AVR UNO/Nano smoke-gate sketch.
*/

#include <EcoSensePower.h>
#include <profiles/radios/bluetooth/arduino_nano33_ble.h>

EcoSensePower node;
GenericRadioProfile bleConnection = EcoProfiles::ArduinoNano33BLE();

float readConnectedMetric() { return (float)analogRead(A0); }

size_t estimateConnectedPayload(const EcoReport& report) {
  (void)report;
  return 24;
}

void setup() {
  Serial.begin(115200);
  bleConnection.rxWindowDurationMs(15).confirmedUplink(true);
  node.radio(&bleConnection);
  node.reportPayloadEstimator(estimateConnectedPayload);
  node.sensor("ble-connection-model")
      .read(readConnectedMetric)
      .minIntervalMs(EcoTime::seconds(10))
      .maxIntervalMs(EcoTime::minutes(2))
      .changeThreshold(3.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("Connection interval, role, scan mode, and TX power must be measured in the application."));
  });
  node.begin();
}

void loop() { node.loop(); }
