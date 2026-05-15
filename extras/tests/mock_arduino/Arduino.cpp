#include "Arduino.h"
HardwareSerial Serial;
uint32_t g_mockMillis = 0;
int g_pinWrites[256] = {0};
