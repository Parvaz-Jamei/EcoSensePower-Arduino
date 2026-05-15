/*
  EcoSensePower GPSDutyCycleBudget.

  GPS/GNSS energy-model example only. It models acquisition/tracking duty-cycle cost;
  it is not a GPS parser, NMEA decoder, positioning library, or navigation framework.

  Default build is dependency-free. Real GPS parsing remains optional through
  user-side libraries such as TinyGPSPlus or Adafruit GPS. This example targets
  capable boards and is not part of the AVR UNO/Nano smoke gate.
*/

#include <EcoSensePower.h>
#include <profiles/gps/ublox_neo6m.h>

EcoSensePower node;
EcoSensorProfile gps = EcoProfiles::UBloxNEO6M();

float readGpsFixQualityModel() {
  return 1.0f; // Placeholder: application-owned GPS parser would update this.
}

void setup() {
  Serial.begin(115200);
  node.sensor("gps-duty-cycle")
      .warmupTimeMs(gps.warmupTimeMs)
      .read(readGpsFixQualityModel)
      .minIntervalMs(EcoTime::minutes(5))
      .maxIntervalMs(EcoTime::hours(1))
      .changeThreshold(1.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("GPS profile is an energy model only; TinyGPSPlus is not required by default."));
  });
  node.begin();
}

void loop() { node.loop(); }
