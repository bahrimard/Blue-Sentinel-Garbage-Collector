#pragma once
#include <cstdint>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
#include <functional>
using std::min; using std::max;
typedef std::string String;
#define HIGH 1
#define LOW 0
#define OUTPUT 1
#define INPUT 0
#define PROGMEM
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
extern unsigned long g_millis;
extern int g_pin[64];
extern int g_duty[16];
extern float g_simCm[64];          // jarak simulasi per pin ECHO
inline unsigned long millis(){ return g_millis; }
inline void delay(unsigned long ms){ g_millis += ms; }
inline void delayMicroseconds(unsigned){}
inline void pinMode(int, int){}
inline void digitalWrite(int p, int v){ g_pin[p]=v; }
inline int digitalRead(int p){ return g_pin[p]; }
inline unsigned long pulseIn(int pin, int, unsigned long timeout){
  float cm=g_simCm[pin]; if(cm<=0) return 0; unsigned long us=(unsigned long)(cm*58.0f); return us>timeout?0:us; }
inline void ledcSetup(int,int,int){}
inline void ledcAttachPin(int,int){}
inline void ledcWrite(int ch,int d){ g_duty[ch]=d; }
inline long random(long m){ return 0; }
inline void randomSeed(unsigned long){}
inline uint32_t esp_random(){ return 1; }
struct SerialStub {
  bool quiet=true;
  void begin(int){}
  template<class T> void print(const T&){}
  template<class T> void println(const T&){}
  void println(){}
  void printf(const char* f, ...){ if(quiet) return; va_list a; va_start(a,f); vprintf(f,a); va_end(a); }
};
extern SerialStub Serial;

typedef enum { ESP_RST_UNKNOWN, ESP_RST_POWERON, ESP_RST_EXT, ESP_RST_SW, ESP_RST_PANIC, ESP_RST_INT_WDT, ESP_RST_TASK_WDT, ESP_RST_WDT, ESP_RST_DEEPSLEEP, ESP_RST_BROWNOUT, ESP_RST_SDIO } esp_reset_reason_t;
inline esp_reset_reason_t esp_reset_reason(){ return ESP_RST_POWERON; }
