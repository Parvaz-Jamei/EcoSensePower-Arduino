/*
  EcoSensePower BluetoothBeaconBudget.

  BLE advertising energy-model example only. EcoSensePower estimates profile and
  duty-cycle cost; it is not a Bluetooth stack, BLE manager, or ArduinoBLE replacement.

  Default build is dependency-free. For real BLE communication, install and use an
  optional user-side library such as ArduinoBLE on supported boards and enable the
  optional adapter explicitly. This example is not part of the AVR UNO/Nano smoke gate.
*/

#include <EcoSensePower.h>
#include <profiles/radios/bluetooth/bluetooth_ble_generic.h>

EcoSensePower node;
GenericRadioProfile bleRadio = EcoProfiles::BluetoothBLEGeneric();

float readBeaconMetric() {
  return (float)analogRead(A0);
}

size_t estimateBeaconPayload(const EcoReport& report) {
  (void)report;
  return 16;
}

void setup() {
  Serial.begin(115200);
  node.radio(&bleRadio);
  node.reportPayloadEstimator(estimateBeaconPayload);
  node.reporting().batchMaxSamples(1).maxReportIntervalMs(EcoTime::seconds(30));
  node.sensor("ble-beacon-model")
      .read(readBeaconMetric)
      .minIntervalMs(EcoTime::seconds(30))
      .maxIntervalMs(EcoTime::minutes(5))
      .changeThreshold(5.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("BLE example is an energy model only; ArduinoBLE is not required by default."));
    Serial.print(F("BLE TX current uA placeholder: "));
    Serial.println((unsigned long)bleRadio.txCurrent_uA());
  });
  node.begin();
}

void loop() {
  node.loop();
}
