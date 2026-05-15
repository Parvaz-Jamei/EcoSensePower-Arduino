/*
  EcoSensePower optional profile subcatalog.

  This header collects energy profiles only. It does not include Bluetooth/BLE stacks,
  GPS parsers, WiFi libraries, SoftwareSerial, or protocol drivers. On AVR Tiny/Core,
  profile catalogs remain disabled unless the user explicitly opts in.
*/

#ifndef ECOSENSEPOWER_GPS_PROFILES_H
#define ECOSENSEPOWER_GPS_PROFILES_H

#include "core/EcoSensePowerConfig.h"

#if ECOSENSE_ENABLE_GPS_PROFILE_CATALOG
#include "profiles/gps/gps_generic.h"
#include "profiles/gps/gnss_generic.h"
#include "profiles/gps/nmea_uart_gps_generic.h"
#include "profiles/gps/i2c_gnss_generic.h"
#include "profiles/gps/high_update_rate_gps_generic.h"
#include "profiles/gps/low_power_gnss_generic.h"
#include "profiles/gps/gps_with_backup_battery_generic.h"
#include "profiles/gps/ublox_neo6m.h"
#include "profiles/gps/ublox_neo6.h"
#include "profiles/gps/ublox_neo7m.h"
#include "profiles/gps/ublox_neo8m.h"
#include "profiles/gps/ublox_neom8n.h"
#include "profiles/gps/ublox_neom8q.h"
#include "profiles/gps/ublox_neom10.h"
#include "profiles/gps/ublox_max_m8q.h"
#include "profiles/gps/ublox_sam_m8q.h"
#include "profiles/gps/ublox_zoe_m8q.h"
#include "profiles/gps/gy_neo6mv2.h"
#include "profiles/gps/quectel_l76.h"
#include "profiles/gps/quectel_l76k.h"
#include "profiles/gps/quectel_l76_l.h"
#include "profiles/gps/quectel_l80.h"
#include "profiles/gps/quectel_l86.h"
#include "profiles/gps/quectel_lc76g.h"
#include "profiles/gps/simcom_sim28.h"
#include "profiles/gps/simcom_sim33ela.h"
#include "profiles/gps/simcom_sim33ea.h"
#include "profiles/gps/mtk3339_gps.h"
#include "profiles/gps/mtk3333_gps.h"
#include "profiles/gps/adafruit_ultimate_gps_mtk3339.h"
#include "profiles/gps/adafruit_pa1010d_gps.h"
#include "profiles/gps/atgm336h.h"
#include "profiles/gps/atgm332d.h"
#include "profiles/gps/atgm336h_5n.h"
#include "profiles/gps/beitian_bn180.h"
#include "profiles/gps/beitian_bn220.h"
#include "profiles/gps/beitian_bn280.h"
#include "profiles/gps/beitian_bn880.h"
#include "profiles/gps/gps_uart_9600_generic.h"
#include "profiles/gps/gps_i2c_generic.h"
#include "profiles/gps/gnss_multiconstellation_generic.h"
#include "profiles/gps/gnss_active_antenna_generic.h"
#endif

#endif
