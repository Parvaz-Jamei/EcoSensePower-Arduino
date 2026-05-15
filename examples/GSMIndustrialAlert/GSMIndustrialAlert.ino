/*
  EcoSensePower GSMIndustrialAlert.

  GSM/cellular energy-model example for high-current alert/reporting scenarios. It is
  not a modem driver, AT command stack, SIM800/SIMCom library, or network framework.

  Default build is dependency-free. Real cellular communication, retries, APN setup,
  and modem sleep control remain application-owned.
*/

#include <EcoSensePower.h>
#include <profiles/batteries/lipo_2s.h>
#include <profiles/boards/arduino_mega.h>
#include <profiles/sensors/pir_generic.h>
#include <profiles/radios/sim800l.h>

EcoSensePower node;
GenericRadioProfile modem;
static float readAlarmInput() { return 0.0f; }
static void report(const EcoReport& r) { Serial.println(r.toText()); }

void setup() {
  Serial.begin(115200);
  modem = EcoProfiles::SIM800L();
  EcoSensorProfile pir = EcoProfiles::PIRGeneric();
  node.battery(EcoProfiles::LiPo2S())
      .board(EcoProfiles::ArduinoMega())
      .radio(&modem)
      .onReport(report);
  node.sensor(pir.name).read(readAlarmInput).priority(ECO_CRITICAL).minIntervalMs(EcoTime::seconds(30)).maxIntervalMs(EcoTime::minutes(10));
  node.begin();
}

void loop() { node.loop(); }
