#include "test_support.h"
#include <EcoSensePower.h>
#include "profiles/radios/sx1276_lora.h"
#include "profiles/radios/nrf24l01.h"
#include "profiles/radios/sim800l.h"
int main() {
  GenericRadioProfile lora = EcoProfiles::SX1276LoRa();
  ASSERT_TRUE(lora.txCurrent_uA() > 0UL);
  ASSERT_TRUE(lora.rxCurrent_uA() > 0UL);
  ASSERT_TRUE(lora.confidence() == EcoProfileConfidence::PLACEHOLDER);
  GenericRadioProfile nrf = EcoProfiles::NRF24L01();
  ASSERT_TRUE(nrf.sleepCurrent_uA() > 0UL);
  GenericRadioProfile sim = EcoProfiles::SIM800L();
  ASSERT_TRUE(sim.txCurrent_uA() >= 1000000UL);
  return 0;
}
