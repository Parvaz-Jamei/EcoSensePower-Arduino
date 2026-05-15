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

void setup() {
  Serial.begin(115200);

#if defined(ECOSENSE_EXAMPLE_USE_OWNER_MEASURED_VALUES)
  // Only enable this branch after recording owner-side instrument measurement evidence
  // for every current field below. A single measured value does not make the whole
  // board profile measured.
  BoardProfile customBoard = MeasuredProfileBuilder()
    .name("Custom owner-measured node")
    .activeCurrent_uA(42000, EcoProfileConfidence::MEASURED)
    .sleepCurrent_uA(12, EcoProfileConfidence::MEASURED)
    .sensorReadCurrent_uA(3200, EcoProfileConfidence::MEASURED)
    .processCurrent_uA(9000, EcoProfileConfidence::MEASURED)
    .includesRegulatorIq(true)
    .includesSensorLeakage(true)
    .notes("Owner-side measured board profile; replace with your documented instrument evidence.")
    .build();
#else
  // Safe default for examples: illustrative values are PLACEHOLDER until the owner
  // records and documents real instrument measurements or cited datasheet values.
  BoardProfile customBoard = MeasuredProfileBuilder()
    .name("Custom placeholder node")
    .activeCurrent_uA(42000, EcoProfileConfidence::PLACEHOLDER)
    .sleepCurrent_uA(12, EcoProfileConfidence::PLACEHOLDER)
    .sensorReadCurrent_uA(3200, EcoProfileConfidence::PLACEHOLDER)
    .processCurrent_uA(9000, EcoProfileConfidence::PLACEHOLDER)
    .includesRegulatorIq(true)
    .includesSensorLeakage(true)
    .notes("Example placeholder values. Use MEASURED only with owner-side measurement evidence.")
    .build();
#endif

  node.board(customBoard);
  node.battery(BatteryProfile::LiPo_1S(1000));
  node.begin();
  node.printDiagnostics(Serial);
}

void loop() {}
