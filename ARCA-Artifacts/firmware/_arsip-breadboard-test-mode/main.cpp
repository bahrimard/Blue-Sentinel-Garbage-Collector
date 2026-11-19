#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include "pins.h"
#include "config.h"
#include "webpage.h"

WebServer httpServer(80);
WebSocketsServer webSocket(WEBSOCKET_PORT);

// ---------- State kendali (dari HP) ----------
float motorL = 0.0f;   // -1..1
float motorR = 0.0f;   // -1..1
bool buzzerOn = false;

// ---------- State sensor (disimulasikan sementara) ----------
bool obsL = false;
bool obsR = false;
bool binFull = false;
const bool conveyorActive = true; // always-on, gak dikontrol ESP32

// ---------- Timer non-blocking ----------
unsigned long tTelemetry = 0;
unsigned long tObsL = 0;
unsigned long tObsR = 0;
unsigned long tBin = 0;

// =======================================================
// Setup PWM & LED
// =======================================================
void setupMotorPWM() {
  ledcSetup(CH_MOTOR_L_FWD, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(CH_MOTOR_L_REV, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(CH_MOTOR_R_FWD, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(CH_MOTOR_R_REV, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_MOTOR_L_FWD, CH_MOTOR_L_FWD);
  ledcAttachPin(PIN_MOTOR_L_REV, CH_MOTOR_L_REV);
  ledcAttachPin(PIN_MOTOR_R_FWD, CH_MOTOR_R_FWD);
  ledcAttachPin(PIN_MOTOR_R_REV, CH_MOTOR_R_REV);
}

// Terapkan nilai motor (-1..1) ke sepasang LED arah (fwd/rev),
// brightness proporsional ke magnitude — ini yang nanti diganti
// jadi kontrol L298N (IN1-4 + ENA/ENB) pas part asli datang.
void applyMotorLED(int chFwd, int chRev, float value) {
  value = constrain(value, -1.0f, 1.0f);
  int duty = (int)(fabs(value) * 255.0f);
  if (value >= 0) {
    ledcWrite(chFwd, duty);
    ledcWrite(chRev, 0);
  } else {
    ledcWrite(chFwd, 0);
    ledcWrite(chRev, duty);
  }
}

// =======================================================
// Simulasi sensor (NON-BLOCKING, pakai millis())
// Ganti isi fungsi ini ke pembacaan HC-SR04 asli nanti —
// signature & efek ke variabel state TETAP SAMA.
// =======================================================
void simulateSensors(unsigned long now) {
  if (now - tObsL >= SIM_OBSTACLE_L_INTERVAL_MS) {
    tObsL = now;
    obsL = (random(100) < 12); // ~12% kemungkinan "kedeteksi"
    digitalWrite(PIN_LED_OBS_L, obsL ? HIGH : LOW);
  }
  if (now - tObsR >= SIM_OBSTACLE_R_INTERVAL_MS) {
    tObsR = now;
    obsR = (random(100) < 12);
    digitalWrite(PIN_LED_OBS_R, obsR ? HIGH : LOW);
  }
  if (now - tBin >= SIM_BIN_INTERVAL_MS) {
    tBin = now;
    binFull = (random(100) < 10);
    digitalWrite(PIN_LED_BIN_FULL, binFull ? HIGH : LOW);
  }
}

// =======================================================
// Kirim telemetry ke semua HP yang connect
// =======================================================
void sendTelemetry() {
  JsonDocument doc;
  doc["type"] = "telemetry";
  doc["motorL"] = motorL;
  doc["motorR"] = motorR;
  doc["obsL"] = obsL;
  doc["obsR"] = obsR;
  doc["binFull"] = binFull;
  doc["conveyor"] = conveyorActive;

  String out;
  serializeJson(doc, out);
  webSocket.broadcastTXT(out);
}

// =======================================================
// Handler perintah dari HP
// =======================================================
void handleCommand(const JsonDocument &doc) {
  const char* type = doc["type"];
  if (type == nullptr) return;

  if (strcmp(type, "joystick") == 0) {
    float x = doc["x"] | 0.0f;
    float y = doc["y"] | 0.0f;
    float throttle = -y;   // maju = atas = y negatif
    float turn = x;
    motorL = constrain(throttle + turn, -1.0f, 1.0f);
    motorR = constrain(throttle - turn, -1.0f, 1.0f);
    applyMotorLED(CH_MOTOR_L_FWD, CH_MOTOR_L_REV, motorL);
    applyMotorLED(CH_MOTOR_R_FWD, CH_MOTOR_R_REV, motorR);
  }
  else if (strcmp(type, "buzzer") == 0) {
    buzzerOn = doc["state"] | false;
    digitalWrite(PIN_LED_BUZZER, buzzerOn ? HIGH : LOW);
  }
}

// =======================================================
// HTTP handler — serve halaman kontrol web UI
// =======================================================
void handleRoot() {
  httpServer.send_P(200, "text/html", INDEX_HTML);
}

// =======================================================
// WebSocket event
// =======================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      if (webSocket.connectedClients() == 0) {
        digitalWrite(PIN_LED_WIFI, LOW);
      }
      break;

    case WStype_CONNECTED:
      digitalWrite(PIN_LED_WIFI, HIGH);
      break;

    case WStype_TEXT: {
      JsonDocument doc;
      DeserializationError err = deserializeJson(doc, payload, length);
      if (!err) {
        handleCommand(doc);
      }
      break;
    }

    default:
      break;
  }
}

// =======================================================
// Setup
// =======================================================
void setup() {
  Serial.begin(115200);

  pinMode(PIN_LED_OBS_L, OUTPUT);
  pinMode(PIN_LED_OBS_R, OUTPUT);
  pinMode(PIN_LED_BIN_FULL, OUTPUT);
  pinMode(PIN_LED_CONVEYOR, OUTPUT);
  pinMode(PIN_LED_BUZZER, OUTPUT);
  pinMode(PIN_LED_WIFI, OUTPUT);

  digitalWrite(PIN_LED_CONVEYOR, HIGH); // always-on, sesuai desain final

  setupMotorPWM();

  WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP()); // default: 192.168.4.1
  Serial.println("Buka browser HP ke alamat di atas buat akses UI kontrol.");

  httpServer.on("/", HTTP_GET, handleRoot);
  httpServer.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  randomSeed(esp_random());
}

// =======================================================
// Loop — NON-BLOCKING, tanpa delay()
// =======================================================
void loop() {
  httpServer.handleClient();
  webSocket.loop();

  unsigned long now = millis();

  simulateSensors(now);

  if (now - tTelemetry >= TELEMETRY_INTERVAL_MS) {
    tTelemetry = now;
    sendTelemetry();
  }
}
