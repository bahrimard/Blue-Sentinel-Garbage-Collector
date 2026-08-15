#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
// #include <ESPmDNS.h>
#include <joystick_js.h>
#include <index_html.h>

// Ganti dengan SSID & password WiFi kamu
// ssid = Network name
// const char* ssid = "iyalah";
// const char* password = "12345678";
const char* ssid = "Robot01";
const char* password = "12345678";

IPAddress local_IP(192,168,1,1);   // IP tetap robot
IPAddress gateway(192,168,1,1);     // Gateway router
IPAddress subnet(255,255,255,0);    // Subnet mask
// IPAddress primaryDNS(8,8,8,8);      // DNS optional
// IPAddress secondaryDNS(8,8,4,4);    // DNS optional


// Pin motor (sesuaikan dengan driver H-Bridge / motor driver kamu)
#define MOTOR_LEFT_FORWARD  2
#define MOTOR_LEFT_BACKWARD 3
#define MOTOR_RIGHT_FORWARD 4
#define MOTOR_RIGHT_BACKWARD 5

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

// Fungsi kontrol motor
void driveMotors(float x, float y) {
  // Mapping joystick ke motor kiri/kanan
  // y = maju/mundur, x = belok kiri/kanan
  int leftSpeed  = (int)(y*255 - x*255);
  int rightSpeed = (int)(y*255 + x*255);

  // Forward/backward logic
  if (leftSpeed > 0) {
    analogWrite(MOTOR_LEFT_FORWARD, leftSpeed);
    analogWrite(MOTOR_LEFT_BACKWARD, 0);
  } else {
    analogWrite(MOTOR_LEFT_FORWARD, 0);
    analogWrite(MOTOR_LEFT_BACKWARD, -leftSpeed);
  }

  if (rightSpeed > 0) {
    analogWrite(MOTOR_RIGHT_FORWARD, rightSpeed);
    analogWrite(MOTOR_RIGHT_BACKWARD, 0);
  } else {
    analogWrite(MOTOR_RIGHT_FORWARD, 0);
    analogWrite(MOTOR_RIGHT_BACKWARD, -rightSpeed);
  }
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleJS() {
  server.send(200, "application/javascript", joystickJS);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT) {
    String msg = String((char*)payload);
    Serial.println("Joystick: " + msg);

    // Parsing JSON manual (x,y)
    int xIndex = msg.indexOf("\"x\":");
    int yIndex = msg.indexOf("\"y\":");
    if (xIndex >= 0 && yIndex >= 0) {
      float x = msg.substring(xIndex+4, msg.indexOf(",", xIndex)).toFloat();
      float y = msg.substring(yIndex+4, msg.indexOf("}", yIndex)).toFloat();
      driveMotors(x, y);
    }
  }
}

void setup() {
  Serial.begin(9600);

  // Setup pin motor
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);

  // WiFi.mode(WIFI_STA);

  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }

  // WiFi.mode(WIFI_STA);       // pastikan station mode
  WiFi.setSleep(false);      // biar koneksi lebih stabil

  // Set static IP
  // if (!WiFi.config(local_IP, gateway, subnet)) {
  //   Serial.println("⚠️ Gagal set static IP, pakai DHCP");
  // }

  // WiFi.begin(ssid, password);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);  // hasilnya 192.168.10.1
  // unsigned long startAttemptTime = millis();

  // while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
  //   delay(500);
  //   Serial.print(".");
  // }
  // Serial.println("\nWiFi connected!");
  // Serial.println("IP: " + WiFi.localIP().toString());

  // Start mDNS responder
  // if (MDNS.begin("robot")) {  
  //   Serial.println("✅ mDNS responder started");
  //   Serial.println("Akses via: http://robot.local");
  // } else {
  //   Serial.println("⚠️ mDNS gagal start, pakai IP static saja");
  //   Serial.println("IP: " + WiFi.localIP().toString());
  // }

  server.on("/", handleRoot);
  server.on("/joystick.js", handleJS);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  server.handleClient();
  webSocket.loop();
}
