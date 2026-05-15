/*
  EcoSensePower example.

  This sketch demonstrates energy budgeting, adaptive duty-cycle behavior, sleep planning,
  diagnostics, or confidence-bounded profiles. It is not a replacement for sensor drivers,
  radio protocol stacks, WiFi/BLE managers, GPS parsers, or a navigation framework.

  Default examples are dependency-free unless this file explicitly says otherwise. Real
  BLE communication needs an optional user-side library such as ArduinoBLE on supported
  boards. Real GPS/NMEA parsing needs an optional user-side parser such as TinyGPSPlus
  or Adafruit GPS.

  AVR UNO/Nano use compact Tiny/Core mode. Full ecosystem profile demos are intended for
  capable boards such as ESP32, SAMD, Mega, Nano 33 BLE, Nano ESP32, Portenta, GIGA,
  and similar boards with more SRAM/flash.
*/

#include <EcoSensePower.h>

EcoSensePower node;
SolarHarvester solar;
GenericRadioProfile radio;

static float readSoil() {
  return (float)analogRead(A0);
}

static float readSolarMilliWatt() {
  return 8.0f; // Application-owned harvester measurement.
}

static uint32_t estimateRadioTxMs(size_t bytes) {
  return 100UL + (uint32_t)bytes * 8UL;
}

static void stopSensorPower() {
  // Put sensor-specific shutdown code here if required.
}

void setup() {
  Serial.begin(115200);

  solar.readMilliWatt(readSolarMilliWatt).confidence(EcoProfileConfidence::PLACEHOLDER);
  radio.txCurrent_uA(92000).rxCurrent_uA(12000).sleepCurrent_uA(1).estimatedTxDurationMs(estimateRadioTxMs);

  node.battery(BatteryProfile::AA_Alkaline(2400));
  node.board(BoardProfile::ArduinoUnoPlaceholder());
  node.socTracker().initialSocPercent(90.0f).observedVoltage(1.45f);
  node.harvester(&solar);
  node.radio(&radio);
  node.energyPolicy().targetNeutralOperation(true).minReservePercent(25).allowIntervalStretching(true);

  node.guard("soil-power")
    .powerPin(7)
    .activeLevel(HIGH)
    .warmupTimeMs(EcoTime::milliseconds(20))
    .onSleep(stopSensorPower);

  node.sensor("soil")
    .read(readSoil)
    .minIntervalMs(EcoTime::minutes(5))
    .maxIntervalMs(EcoTime::hours(6))
    .initialIntervalMs(EcoTime::minutes(5))
    .changeThreshold(20.0f)
    .priority(ECO_NORMAL)
    .calibratedCurrent(false);

  node.onReport([](const EcoReport& report) {
    Serial.println(report.toText());
    EcoPowerReport power = node.powerReport();
    Serial.print(F("SoC: "));
    Serial.println(power.socPercent);
  });

  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {
  node.loop();
}
