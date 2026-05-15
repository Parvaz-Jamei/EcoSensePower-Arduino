#include "test_support.h"
#include "core/EcoSensePowerConfig.h"
#include "profiles/radios/bluetooth/bluetooth_classic_generic.h"
#include "profiles/radios/bluetooth/bluetooth_ble_generic.h"
#include "profiles/radios/bluetooth/bluetooth_uart_module_generic.h"
#include "profiles/radios/bluetooth/bluetooth_board_integrated_generic.h"
#include "profiles/radios/bluetooth/bluetooth_external_module_generic.h"
#include "profiles/radios/bluetooth/hc05_bluetooth.h"
#include "profiles/radios/bluetooth/hc06_bluetooth.h"
#include "profiles/radios/bluetooth/hc02_bluetooth.h"
#include "profiles/radios/bluetooth/hc04_bluetooth.h"
#include "profiles/radios/bluetooth/rn42_bluetooth.h"
#include "profiles/radios/bluetooth/bluetooth_spp_generic.h"
#include "profiles/radios/bluetooth/hm10_ble.h"
#include "profiles/radios/bluetooth/hm11_ble.h"
#include "profiles/radios/bluetooth/at09_ble.h"
#include "profiles/radios/bluetooth/jdy08_ble.h"
#include "profiles/radios/bluetooth/jdy10_ble.h"
#include "profiles/radios/bluetooth/jdy16_ble.h"
#include "profiles/radios/bluetooth/jdy23_ble.h"
#include "profiles/radios/bluetooth/rn4870_ble.h"
#include "profiles/radios/bluetooth/rn4871_ble.h"
#include "profiles/radios/bluetooth/nrf52832_ble_module.h"
#include "profiles/radios/bluetooth/nrf52840_ble_module.h"
#include "profiles/radios/bluetooth/bl652_ble.h"
#include "profiles/radios/bluetooth/ble_uart_generic.h"
#include "profiles/radios/bluetooth/esp32_bluetooth_classic.h"
#include "profiles/radios/bluetooth/esp32_ble.h"
#include "profiles/radios/bluetooth/esp32_s3_ble.h"
#include "profiles/radios/bluetooth/esp32_c3_ble.h"
#include "profiles/radios/bluetooth/arduino_nano33_ble.h"
#include "profiles/radios/bluetooth/arduino_nano33_ble_sense.h"
#include "profiles/radios/bluetooth/arduino_nano33_ble_rev2.h"
#include "profiles/radios/bluetooth/arduino_nano33_iot_ble.h"
#include "profiles/radios/bluetooth/arduino_mkr_wifi1010_ble.h"
#include "profiles/radios/bluetooth/arduino_uno_wifi_rev2_ble.h"
#include "profiles/radios/bluetooth/arduino_uno_r4_wifi_ble.h"
#include "profiles/radios/bluetooth/arduino_nano_esp32_ble.h"
#include "profiles/radios/bluetooth/arduino_nicla_sense_me_ble.h"
#include "profiles/radios/bluetooth/arduino_portenta_h7_ble.h"
#include "profiles/radios/bluetooth/arduino_giga_r1_ble.h"
#include "profiles/radios/bluetooth/nina_w102_ble_generic.h"
#include "profiles/radios/bluetooth/nrf52840_board_ble_generic.h"
static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validRadio(const GenericRadioProfile& p) { return p.txCurrent_uA() > 0UL && p.rxCurrent_uA() > 0UL && p.confidence() == EcoProfileConfidence::PLACEHOLDER; }
int main() {
  ASSERT_TRUE(validText(EcoProfiles::BluetoothClassicGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothClassicGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothClassicGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothClassicGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothBLEGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothBLEGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothBLEGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothBLEGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothUARTModuleGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothUARTModuleGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothUARTModuleGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothUARTModuleGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothBoardIntegratedGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothBoardIntegratedGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothBoardIntegratedGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothBoardIntegratedGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothExternalModuleGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothExternalModuleGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothExternalModuleGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothExternalModuleGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::HC05BluetoothName()));
  ASSERT_TRUE(validText(EcoProfiles::HC05BluetoothNotes()));
  ASSERT_TRUE(EcoProfiles::HC05BluetoothMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HC05Bluetooth()));
  ASSERT_TRUE(validText(EcoProfiles::HC06BluetoothName()));
  ASSERT_TRUE(validText(EcoProfiles::HC06BluetoothNotes()));
  ASSERT_TRUE(EcoProfiles::HC06BluetoothMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HC06Bluetooth()));
  ASSERT_TRUE(validText(EcoProfiles::HC02BluetoothName()));
  ASSERT_TRUE(validText(EcoProfiles::HC02BluetoothNotes()));
  ASSERT_TRUE(EcoProfiles::HC02BluetoothMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HC02Bluetooth()));
  ASSERT_TRUE(validText(EcoProfiles::HC04BluetoothName()));
  ASSERT_TRUE(validText(EcoProfiles::HC04BluetoothNotes()));
  ASSERT_TRUE(EcoProfiles::HC04BluetoothMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HC04Bluetooth()));
  ASSERT_TRUE(validText(EcoProfiles::RN42BluetoothName()));
  ASSERT_TRUE(validText(EcoProfiles::RN42BluetoothNotes()));
  ASSERT_TRUE(EcoProfiles::RN42BluetoothMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::RN42Bluetooth()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothSPPGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BluetoothSPPGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BluetoothSPPGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BluetoothSPPGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::HM10BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::HM10BLENotes()));
  ASSERT_TRUE(EcoProfiles::HM10BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HM10BLE()));
  ASSERT_TRUE(validText(EcoProfiles::HM11BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::HM11BLENotes()));
  ASSERT_TRUE(EcoProfiles::HM11BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::HM11BLE()));
  ASSERT_TRUE(validText(EcoProfiles::AT09BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::AT09BLENotes()));
  ASSERT_TRUE(EcoProfiles::AT09BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::AT09BLE()));
  ASSERT_TRUE(validText(EcoProfiles::JDY08BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::JDY08BLENotes()));
  ASSERT_TRUE(EcoProfiles::JDY08BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::JDY08BLE()));
  ASSERT_TRUE(validText(EcoProfiles::JDY10BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::JDY10BLENotes()));
  ASSERT_TRUE(EcoProfiles::JDY10BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::JDY10BLE()));
  ASSERT_TRUE(validText(EcoProfiles::JDY16BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::JDY16BLENotes()));
  ASSERT_TRUE(EcoProfiles::JDY16BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::JDY16BLE()));
  ASSERT_TRUE(validText(EcoProfiles::JDY23BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::JDY23BLENotes()));
  ASSERT_TRUE(EcoProfiles::JDY23BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::JDY23BLE()));
  ASSERT_TRUE(validText(EcoProfiles::RN4870BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::RN4870BLENotes()));
  ASSERT_TRUE(EcoProfiles::RN4870BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::RN4870BLE()));
  ASSERT_TRUE(validText(EcoProfiles::RN4871BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::RN4871BLENotes()));
  ASSERT_TRUE(EcoProfiles::RN4871BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::RN4871BLE()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52832BLEModuleName()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52832BLEModuleNotes()));
  ASSERT_TRUE(EcoProfiles::NRF52832BLEModuleMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::NRF52832BLEModule()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52840BLEModuleName()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52840BLEModuleNotes()));
  ASSERT_TRUE(EcoProfiles::NRF52840BLEModuleMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::NRF52840BLEModule()));
  ASSERT_TRUE(validText(EcoProfiles::BL652BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::BL652BLENotes()));
  ASSERT_TRUE(EcoProfiles::BL652BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BL652BLE()));
  ASSERT_TRUE(validText(EcoProfiles::BLEUARTGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::BLEUARTGenericNotes()));
  ASSERT_TRUE(EcoProfiles::BLEUARTGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::BLEUARTGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32BluetoothClassicName()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32BluetoothClassicNotes()));
  ASSERT_TRUE(EcoProfiles::ESP32BluetoothClassicMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ESP32BluetoothClassic()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32BLENotes()));
  ASSERT_TRUE(EcoProfiles::ESP32BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ESP32BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32S3BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32S3BLENotes()));
  ASSERT_TRUE(EcoProfiles::ESP32S3BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ESP32S3BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32C3BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ESP32C3BLENotes()));
  ASSERT_TRUE(EcoProfiles::ESP32C3BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ESP32C3BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNano33BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNano33BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLESenseName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLESenseNotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNano33BLESenseMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNano33BLESense()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLERev2Name()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33BLERev2Notes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNano33BLERev2Measured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNano33BLERev2()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33IoTBLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNano33IoTBLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNano33IoTBLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNano33IoTBLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoMKRWiFi1010BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoMKRWiFi1010BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoMKRWiFi1010BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoMKRWiFi1010BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoUNOWiFiRev2BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoUNOWiFiRev2BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoUNOWiFiRev2BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoUNOWiFiRev2BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoUNOR4WiFiBLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoUNOR4WiFiBLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoUNOR4WiFiBLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoUNOR4WiFiBLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNanoESP32BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNanoESP32BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNanoESP32BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNanoESP32BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNiclaSenseMEBLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoNiclaSenseMEBLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoNiclaSenseMEBLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoNiclaSenseMEBLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoPortentaH7BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoPortentaH7BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoPortentaH7BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoPortentaH7BLE()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoGigaR1BLEName()));
  ASSERT_TRUE(validText(EcoProfiles::ArduinoGigaR1BLENotes()));
  ASSERT_TRUE(EcoProfiles::ArduinoGigaR1BLEMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::ArduinoGigaR1BLE()));
  ASSERT_TRUE(validText(EcoProfiles::NINAW102BLEGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::NINAW102BLEGenericNotes()));
  ASSERT_TRUE(EcoProfiles::NINAW102BLEGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::NINAW102BLEGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52840BoardBLEGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::NRF52840BoardBLEGenericNotes()));
  ASSERT_TRUE(EcoProfiles::NRF52840BoardBLEGenericMeasured() == false);
  ASSERT_TRUE(validRadio(EcoProfiles::NRF52840BoardBLEGeneric()));
  ASSERT_TRUE(EcoProfiles::HC05Bluetooth().txCurrent_uA() != EcoProfiles::HM10BLE().txCurrent_uA() || EcoProfiles::HC05Bluetooth().sleepCurrent_uA() != EcoProfiles::HM10BLE().sleepCurrent_uA());
  return 0;
}
