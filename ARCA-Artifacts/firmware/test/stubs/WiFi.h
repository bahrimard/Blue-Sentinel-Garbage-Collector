#pragma once
#include <Arduino.h>
#define WIFI_AP 2
struct IPStub{};
struct WiFiStub{ void mode(int){} bool softAP(const char*,const char*){return true;} void setSleep(bool){} IPStub softAPIP(){return {};} };
extern WiFiStub WiFi;
