#pragma once
#include <Arduino.h>
typedef enum { WStype_ERROR, WStype_DISCONNECTED, WStype_CONNECTED, WStype_TEXT, WStype_BIN } WStype_t;
struct WebSocketsServer{
  typedef std::function<void(uint8_t, WStype_t, uint8_t*, size_t)> Ev;
  Ev cb; int clients=0; String last;
  WebSocketsServer(int){}
  void begin(){}
  void onEvent(Ev f){ cb=f; }
  void loop(){}
  bool broadcastTXT(String& p){ last=p; return true; }
  int connectedClients(bool=false){ return clients; }
};
