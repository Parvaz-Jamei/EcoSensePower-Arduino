#include "test_support.h"
#include "radio/GenericRadioProfile.h"
#include "profiles/radios/esp8266_wifi.h"
#include "profiles/radios/hc12.h"
#include "profiles/radios/nrf24l01.h"
#include "profiles/radios/rfm95w.h"
#include "profiles/radios/sim800l.h"
#include "profiles/radios/sx1276_lora.h"
#include "profiles/radios/bluetooth/bluetooth_ble_generic.h"
#include "profiles/radios/bluetooth/hc05_bluetooth.h"
static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validRadio(GenericRadioProfile& p) {
  return p.txCurrent_uA() > 0UL && p.rxCurrent_uA() > 0UL && p.sleepCurrent_uA() > 0UL &&
         p.confidence() == EcoProfileConfidence::PLACEHOLDER;
}
int main() {
  GenericRadioProfile sx1276 = EcoProfiles::SX1276LoRa();
  GenericRadioProfile rfm95w = EcoProfiles::RFM95W();
  GenericRadioProfile nrf24 = EcoProfiles::NRF24L01();
  GenericRadioProfile hc12 = EcoProfiles::HC12();
  GenericRadioProfile sim800l = EcoProfiles::SIM800L();
  GenericRadioProfile esp8266 = EcoProfiles::ESP8266WiFi();
  GenericRadioProfile ble = EcoProfiles::BluetoothBLEGeneric();
  GenericRadioProfile hc05 = EcoProfiles::HC05Bluetooth();
  ASSERT_TRUE(validRadio(sx1276));
  ASSERT_TRUE(validRadio(rfm95w));
  ASSERT_TRUE(validRadio(nrf24));
  ASSERT_TRUE(validRadio(hc12));
  ASSERT_TRUE(validRadio(sim800l));
  ASSERT_TRUE(validRadio(esp8266));
  ASSERT_TRUE(validRadio(ble));
  ASSERT_TRUE(validRadio(hc05));
  ASSERT_TRUE(sim800l.txCurrent_uA() >= 1000000UL);
  ASSERT_TRUE(validText(EcoProfiles::SX1276LoRaNotes()));
  ASSERT_TRUE(validText(EcoProfiles::RFM95WNotes()));
  ASSERT_TRUE(validText(EcoProfiles::NRF24L01Notes()));
  ASSERT_TRUE(validText(EcoProfiles::HC12Notes()));
  ASSERT_TRUE(validText(EcoProfiles::SIM800LNotes()));
  ASSERT_TRUE(validText(EcoProfiles::ESP8266WiFiNotes()));
  return 0;
}
