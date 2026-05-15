/*
  EcoSensePower GPSPowerGatingBudget.

  GPS power-gating energy-model example only. It demonstrates how to budget a high
  energy GPS/GNSS peripheral and a guard-controlled power pin; it is not a GPS parser,
  NMEA decoder, driver, or navigation framework.

  Default build is dependency-free. This example enables one guard slot before
  including EcoSensePower so node.guard("gps-power") is active. It is not part of the
  AVR UNO/Nano smoke gate; validate real GPS power gating on your exact hardware.
*/

#ifndef ECOSENSE_MAX_GUARDS
#define ECOSENSE_MAX_GUARDS 1
#endif
#include <EcoSensePower.h>
#include <profiles/gps/gps_with_backup_battery_generic.h>

EcoSensePower node;
EcoSensorProfile gps = EcoProfiles::GPSWithBackupBatteryGeneric();
const uint8_t GPS_POWER_PIN = 6;

float readGpsStateModel() { return 1.0f; }

void setup() {
  Serial.begin(115200);
  pinMode(GPS_POWER_PIN, OUTPUT);
  digitalWrite(GPS_POWER_PIN, LOW);
  node.guard("gps-power")
      .powerPin(GPS_POWER_PIN)
      .activeLevel(HIGH)
      .warmupTimeMs(200);
  node.sensor("gps-power-gate")
      .warmupTimeMs(gps.warmupTimeMs)
      .read(readGpsStateModel)
      .minIntervalMs(EcoTime::minutes(15))
      .maxIntervalMs(EcoTime::hours(4))
      .changeThreshold(1.0f);
  node.onReport([](const EcoReport& report) {
    char text[96];
    Serial.println(report.toText(text, sizeof(text)));
    Serial.println(F("Power gating and backup supply behavior must be validated on the exact GPS board."));
  });
  node.begin();
}

void loop() { node.loop(); }
