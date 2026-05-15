/*
  EcoSensePower optional profile subcatalog.

  This header collects energy profiles only. It does not include Bluetooth/BLE stacks,
  GPS parsers, WiFi libraries, SoftwareSerial, or protocol drivers. On AVR Tiny/Core,
  profile catalogs remain disabled unless the user explicitly opts in.
*/

#ifndef ECOSENSEPOWER_BLUETOOTH_PROFILES_H
#define ECOSENSEPOWER_BLUETOOTH_PROFILES_H

#include "core/EcoSensePowerConfig.h"

#if ECOSENSE_ENABLE_BLUETOOTH_PROFILE_CATALOG
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
#endif

#endif
