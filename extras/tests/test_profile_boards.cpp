#include "test_support.h"
#include "core/BoardProfile.h"
#include "profiles/boards/arduino_mega.h"
#include "profiles/boards/arduino_mkr_wan.h"
#include "profiles/boards/arduino_nano.h"
#include "profiles/boards/arduino_nano_every.h"
#include "profiles/boards/arduino_pro_mini_3v3.h"
#include "profiles/boards/arduino_pro_mini_5v.h"
#include "profiles/boards/attiny85.h"
#include "profiles/boards/avr_uno.h"
#include "profiles/boards/esp32_devkit.h"
#include "profiles/boards/esp32_wroom.h"
#include "profiles/boards/esp8266_nodemcu.h"
#include "profiles/boards/generic_board.h"
#include "profiles/boards/raspberry_pi_pico.h"
static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validBoard(const BoardProfile& p) {
  return validText(p.name) && validText(p.notes) && p.activeCurrent_uA > 0UL &&
         !p.measured && p.confidence == EcoProfileConfidence::PLACEHOLDER;
}
int main() {
  ASSERT_TRUE(validBoard(EcoProfiles::GenericBoard()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoUnoPlaceholder()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoNano()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoProMini3V3()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoProMini5V()));
  ASSERT_TRUE(validBoard(EcoProfiles::ESP32DevKit()));
  ASSERT_TRUE(validBoard(EcoProfiles::ESP32WroomModule()));
  ASSERT_TRUE(validBoard(EcoProfiles::ESP8266NodeMCU()));
  ASSERT_TRUE(validBoard(EcoProfiles::ATtiny85()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoMega()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoNanoEvery()));
  ASSERT_TRUE(validBoard(EcoProfiles::ArduinoMkrWan()));
  ASSERT_TRUE(validBoard(EcoProfiles::RaspberryPiPico()));
  return 0;
}
