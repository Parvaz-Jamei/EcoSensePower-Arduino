#ifndef ECOSENSE_TEST_MOCK_ARDUINO_H
#define ECOSENSE_TEST_MOCK_ARDUINO_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define HIGH 0x1
#define LOW 0x0
#define OUTPUT 0x1
#define INPUT 0x0
#define A0 14
#define A1 15
#define F(x) x

typedef char __FlashStringHelper;

class Print {
public:
  virtual ~Print() {}
  virtual size_t write(uint8_t ch) { (void)ch; return 1; }
  size_t print(const char* value) { if (!value) value = ""; return fwrite(value, 1, strlen(value), stdout); }
  size_t print(char value) { return fwrite(&value, 1, 1, stdout); }
  size_t print(int value) { return printf("%d", value); }
  size_t print(unsigned int value) { return printf("%u", value); }
  size_t print(long value) { return printf("%ld", value); }
  size_t print(unsigned long value) { return printf("%lu", value); }
  size_t print(float value, int digits = 2) { return printf("%.*f", digits, (double)value); }
  size_t print(double value, int digits = 2) { return printf("%.*f", digits, value); }
  size_t println() { return printf("\n"); }
  template <typename T>
  size_t println(const T& value) { size_t n = print(value); n += println(); return n; }
};

class HardwareSerial : public Print {
public:
  void begin(unsigned long baud) { (void)baud; }
};

extern HardwareSerial Serial;
extern uint32_t g_mockMillis;
extern int g_pinWrites[256];

inline uint32_t millis() { return g_mockMillis; }
inline void delay(uint32_t ms) { g_mockMillis += ms; }
inline void pinMode(uint8_t pin, uint8_t mode) { (void)pin; (void)mode; }
inline void digitalWrite(uint8_t pin, uint8_t value) { g_pinWrites[pin] = value; }
inline int analogRead(uint8_t pin) { return 512 + (int)pin; }
inline void mockSetMillis(uint32_t value) { g_mockMillis = value; }

#endif
