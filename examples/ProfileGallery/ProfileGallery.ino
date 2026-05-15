/*
  EcoSensePower ProfileGallery.

  Catalog/usability example showing confidence-bounded battery, board, sensor, radio,
  Bluetooth/BLE, GPS/GNSS, and harvester profiles. Profiles are energy models only;
  they are not drivers, parsers, protocol stacks, or measured-current guarantees.

  This is not part of the AVR UNO/Nano smoke gate. Include only the specific profile
  headers you need on memory-limited boards.
*/

#include <EcoSensePower.h>
#include <profiles/batteries/cr2032.h>
#include <profiles/batteries/liion_18650.h>
#include <profiles/boards/esp32_devkit.h>
#include <profiles/sensors/bme280.h>
#include <profiles/sensors/ina219.h>
#include <profiles/radios/sx1276_lora.h>
#include <profiles/radios/sim800l.h>
#include <profiles/radios/bluetooth/bluetooth_ble_generic.h>
#include <profiles/radios/bluetooth/hc05_bluetooth.h>
#include <profiles/gps/ublox_neo6m.h>
#include <profiles/gps/gnss_generic.h>

void printBattery(const BatteryProfile& p) {
  Serial.print(F("Battery: "));
  Serial.print(p.name);
  Serial.print(F(" capacity_mAh="));
  Serial.print((unsigned long)p.capacity_mAh);
  Serial.print(F(" confidence="));
  Serial.println(ecoProfileConfidenceName(p.confidence));
}

void setup() {
  Serial.begin(115200);
  printBattery(EcoProfiles::CR2032());
  printBattery(EcoProfiles::LiIon18650());
  BoardProfile board = EcoProfiles::ESP32DevKit();
  EcoSensorProfile weather = EcoProfiles::BME280();
  EcoSensorProfile monitor = EcoProfiles::INA219();
  GenericRadioProfile lora = EcoProfiles::SX1276LoRa();
  GenericRadioProfile modem = EcoProfiles::SIM800L();
  GenericRadioProfile ble = EcoProfiles::BluetoothBLEGeneric();
  GenericRadioProfile btClassic = EcoProfiles::HC05Bluetooth();
  EcoSensorProfile gps = EcoProfiles::UBloxNEO6M();
  EcoSensorProfile gnss = EcoProfiles::GNSSGeneric();
  Serial.println(board.name);
  Serial.println(weather.name);
  Serial.println(monitor.name);
  Serial.println((unsigned long)lora.txCurrent_uA());
  Serial.println((unsigned long)modem.txCurrent_uA());
  Serial.println((unsigned long)ble.txCurrent_uA());
  Serial.println((unsigned long)btClassic.txCurrent_uA());
  Serial.println(gps.name);
  Serial.println(gnss.name);
}

void loop() {}
