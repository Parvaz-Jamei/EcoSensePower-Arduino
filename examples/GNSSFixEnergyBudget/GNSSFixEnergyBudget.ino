/*
  EcoSensePower GNSSFixEnergyBudget.

  GNSS fix/acquisition energy-model example only. It demonstrates confidence-bounded
  energy planning for cold/warm/hot-start behavior and update-rate costs; it does not
  parse NMEA, guarantee fix time, or guarantee battery life.

  Default build is dependency-free. Use TinyGPSPlus, Adafruit GPS, or another parser
  only in your application code when real GNSS data is needed.
*/

#include <EcoSensePower.h>
#include <profiles/gps/gnss_multiconstellation_generic.h>

EcoSensePower node;
EcoSensorProfile gnss = EcoProfiles::GNSSMultiConstellationGeneric();

float readFixAttemptModel() {
  return 1.0f;
}

void setup() {
  Serial.begin(115200);
  node.sensor("gnss-fix-energy")
      .warmupTimeMs(gnss.warmupTimeMs)
      .read(readFixAttemptModel)
      .minIntervalMs(EcoTime::minutes(10))
      .maxIntervalMs(EcoTime::hours(2))
      .changeThreshold(1.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("Cold start, sky visibility, active antenna, and backup supply dominate GNSS energy."));
  });
  node.begin();
}

void loop() { node.loop(); }
