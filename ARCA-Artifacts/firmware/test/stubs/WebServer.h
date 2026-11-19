#pragma once
#include <Arduino.h>
#define HTTP_GET 1
struct WebServer{
  std::function<void()> root;
  WebServer(int){}
  void on(const char*, int, std::function<void()> f){ root=f; }
  void onNotFound(std::function<void()>){}
  void begin(){}
  void handleClient(){}
  void send_P(int, const char*, const char* c){ sentBytes=strlen(c); }
  size_t sentBytes=0;
};
