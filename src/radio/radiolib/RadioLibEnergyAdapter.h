#ifndef ECOSENSE_RADIO_RADIOLIBENERGYADAPTER_H
#define ECOSENSE_RADIO_RADIOLIBENERGYADAPTER_H

#include "radio/GenericRadioProfile.h"

#if defined(ECOSENSE_ENABLE_RADIOLIB_ADAPTER)
#include <RadioLib.h>
#endif

class RadioLibEnergyAdapter : public GenericRadioProfile {
public:
  RadioLibEnergyAdapter() : GenericRadioProfile() {}
  // Optional shim only. Concrete RadioLib objects remain application-owned.
};

#endif
