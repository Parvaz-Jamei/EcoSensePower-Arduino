#ifndef ECOSENSE_PROFILES_SENSORS_MPU6050_H
#define ECOSENSE_PROFILES_SENSORS_MPU6050_H

#include "core/SensorProfile.h"

namespace EcoProfiles {
inline EcoSensorProfile MPU6050() {
  return EcoSensorProfile("MPU6050 IMU module", 100UL, 4000UL, 100UL, false,
                          EcoProfileConfidence::PLACEHOLDER,
                          "Placeholder profile. IMU power modes vary; breakout regulators and pullups often dominate low-power behavior.");
}
}

#endif
