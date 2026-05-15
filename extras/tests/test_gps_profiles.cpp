#include "test_support.h"
#include "core/EcoSensePowerConfig.h"
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
static bool validText(const char* value) { return value != 0 && value[0] != '\0'; }
static bool validGPS(const EcoSensorProfile& p) { return validText(p.name) && validText(p.notes) && !p.measured && p.confidence == EcoProfileConfidence::PLACEHOLDER && p.readCurrent_uA > 0UL; }
int main() {
  ASSERT_TRUE(validText(EcoProfiles::GPSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GPSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GPSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GPSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GNSSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GNSSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::NMEAUARTGPSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::NMEAUARTGPSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::NMEAUARTGPSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::NMEAUARTGPSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::I2CGNSSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::I2CGNSSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::I2CGNSSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::I2CGNSSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::HighUpdateRateGPSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::HighUpdateRateGPSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::HighUpdateRateGPSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::HighUpdateRateGPSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::LowPowerGNSSGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::LowPowerGNSSGenericNotes()));
  ASSERT_TRUE(EcoProfiles::LowPowerGNSSGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::LowPowerGNSSGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::GPSWithBackupBatteryGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GPSWithBackupBatteryGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GPSWithBackupBatteryGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GPSWithBackupBatteryGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO6MName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO6MNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEO6MMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEO6M()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO6Name()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO6Notes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEO6Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEO6()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO7MName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO7MNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEO7MMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEO7M()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO8MName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEO8MNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEO8MMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEO8M()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM8NName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM8NNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEOM8NMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEOM8N()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM8QName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM8QNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEOM8QMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEOM8Q()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM10Name()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxNEOM10Notes()));
  ASSERT_TRUE(EcoProfiles::UBloxNEOM10Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxNEOM10()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxMAXM8QName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxMAXM8QNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxMAXM8QMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxMAXM8Q()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxSAMM8QName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxSAMM8QNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxSAMM8QMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxSAMM8Q()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxZOEM8QName()));
  ASSERT_TRUE(validText(EcoProfiles::UBloxZOEM8QNotes()));
  ASSERT_TRUE(EcoProfiles::UBloxZOEM8QMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::UBloxZOEM8Q()));
  ASSERT_TRUE(validText(EcoProfiles::GYNEO6MV2Name()));
  ASSERT_TRUE(validText(EcoProfiles::GYNEO6MV2Notes()));
  ASSERT_TRUE(EcoProfiles::GYNEO6MV2Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GYNEO6MV2()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76Name()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76Notes()));
  ASSERT_TRUE(EcoProfiles::QuectelL76Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelL76()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76KName()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76KNotes()));
  ASSERT_TRUE(EcoProfiles::QuectelL76KMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelL76K()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76LName()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL76LNotes()));
  ASSERT_TRUE(EcoProfiles::QuectelL76LMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelL76L()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL80Name()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL80Notes()));
  ASSERT_TRUE(EcoProfiles::QuectelL80Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelL80()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL86Name()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelL86Notes()));
  ASSERT_TRUE(EcoProfiles::QuectelL86Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelL86()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelLC76GName()));
  ASSERT_TRUE(validText(EcoProfiles::QuectelLC76GNotes()));
  ASSERT_TRUE(EcoProfiles::QuectelLC76GMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::QuectelLC76G()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM28Name()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM28Notes()));
  ASSERT_TRUE(EcoProfiles::SIMComSIM28Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::SIMComSIM28()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM33ELAName()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM33ELANotes()));
  ASSERT_TRUE(EcoProfiles::SIMComSIM33ELAMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::SIMComSIM33ELA()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM33EAName()));
  ASSERT_TRUE(validText(EcoProfiles::SIMComSIM33EANotes()));
  ASSERT_TRUE(EcoProfiles::SIMComSIM33EAMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::SIMComSIM33EA()));
  ASSERT_TRUE(validText(EcoProfiles::MTK3339GPSName()));
  ASSERT_TRUE(validText(EcoProfiles::MTK3339GPSNotes()));
  ASSERT_TRUE(EcoProfiles::MTK3339GPSMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::MTK3339GPS()));
  ASSERT_TRUE(validText(EcoProfiles::MTK3333GPSName()));
  ASSERT_TRUE(validText(EcoProfiles::MTK3333GPSNotes()));
  ASSERT_TRUE(EcoProfiles::MTK3333GPSMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::MTK3333GPS()));
  ASSERT_TRUE(validText(EcoProfiles::AdafruitUltimateGPSMTK3339Name()));
  ASSERT_TRUE(validText(EcoProfiles::AdafruitUltimateGPSMTK3339Notes()));
  ASSERT_TRUE(EcoProfiles::AdafruitUltimateGPSMTK3339Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::AdafruitUltimateGPSMTK3339()));
  ASSERT_TRUE(validText(EcoProfiles::AdafruitPA1010DGPSName()));
  ASSERT_TRUE(validText(EcoProfiles::AdafruitPA1010DGPSNotes()));
  ASSERT_TRUE(EcoProfiles::AdafruitPA1010DGPSMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::AdafruitPA1010DGPS()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM336HName()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM336HNotes()));
  ASSERT_TRUE(EcoProfiles::ATGM336HMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::ATGM336H()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM332DName()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM332DNotes()));
  ASSERT_TRUE(EcoProfiles::ATGM332DMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::ATGM332D()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM336H5NName()));
  ASSERT_TRUE(validText(EcoProfiles::ATGM336H5NNotes()));
  ASSERT_TRUE(EcoProfiles::ATGM336H5NMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::ATGM336H5N()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN180Name()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN180Notes()));
  ASSERT_TRUE(EcoProfiles::BeitianBN180Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::BeitianBN180()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN220Name()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN220Notes()));
  ASSERT_TRUE(EcoProfiles::BeitianBN220Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::BeitianBN220()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN280Name()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN280Notes()));
  ASSERT_TRUE(EcoProfiles::BeitianBN280Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::BeitianBN280()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN880Name()));
  ASSERT_TRUE(validText(EcoProfiles::BeitianBN880Notes()));
  ASSERT_TRUE(EcoProfiles::BeitianBN880Measured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::BeitianBN880()));
  ASSERT_TRUE(validText(EcoProfiles::GPSUART9600GenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GPSUART9600GenericNotes()));
  ASSERT_TRUE(EcoProfiles::GPSUART9600GenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GPSUART9600Generic()));
  ASSERT_TRUE(validText(EcoProfiles::GPSI2CGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GPSI2CGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GPSI2CGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GPSI2CGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSMultiConstellationGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSMultiConstellationGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GNSSMultiConstellationGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GNSSMultiConstellationGeneric()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSActiveAntennaGenericName()));
  ASSERT_TRUE(validText(EcoProfiles::GNSSActiveAntennaGenericNotes()));
  ASSERT_TRUE(EcoProfiles::GNSSActiveAntennaGenericMeasured() == false);
  ASSERT_TRUE(validGPS(EcoProfiles::GNSSActiveAntennaGeneric()));
  ASSERT_TRUE(EcoProfiles::HighUpdateRateGPSGeneric().readCurrent_uA >= EcoProfiles::LowPowerGNSSGeneric().readCurrent_uA);
  return 0;
}
