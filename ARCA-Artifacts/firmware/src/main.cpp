// ============================================================
// ARCA — firmware FINAL (hardware asli), versi lomba 2026-09-24
//
// Diturunkan dari main.cpp "BREADBOARD TEST MODE" (LED):
//   - Protokol WebSocket, port, dan webpage.h TIDAK diubah.
//   - applyMotorLED()  → driveMotor() ke L298N (IN1-4 + ENA/ENB)
//   - simulateSensors() → readSensors() dari 4× HC-SR04
//   - LED buzzer        → GPIO27 ke BC337
//   - Tambahan: kunci motor saat boot, failsafe, ramp akselerasi.
// ============================================================
#include <Arduino.h>
#include <esp_system.h>
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
float targetL = 0.0f, targetR = 0.0f;  // -1..1 dari joystick
float motorL  = 0.0f, motorR  = 0.0f;  // -1..1 yang benar-benar dipakai (setelah ramp)
bool buzzerOn = false;
unsigned long lastCmdMs = 0;
bool failsafeTripped = false;

// ---------- State sensor ----------
// index: 0 = US1 bak-kiri (SAMPAH), 1 = US2 bak-kanan (SAMPAH),
//        2 = US3 depan-kiri (HALANGAN), 3 = US4 depan-kanan (HALANGAN)
const uint8_t TRIG[4] = {PIN_TRIG_BIN_L, PIN_TRIG_BIN_R, PIN_TRIG_FRONT_L, PIN_TRIG_FRONT_R};
const uint8_t ECHO[4] = {PIN_ECHO_BIN_L, PIN_ECHO_BIN_R, PIN_ECHO_FRONT_L, PIN_ECHO_FRONT_R};
float distCm[4] = {NO_ECHO_CM, NO_ECHO_CM, NO_ECHO_CM, NO_ECHO_CM};
float hist[4][3];
uint8_t histIdx[4] = {0, 0, 0, 0};
uint8_t sensorIdx = 0;

bool obsL = false;
bool obsR = false;
bool binFull = false;
const bool conveyorActive = true;  // always-on dari buck converter, gak dikontrol ESP32

// ---------- Buzzer (level aktif bisa dibalik di config.h) ----------
inline void buzzerWrite(bool on) {
#if BUZZER_ACTIVE_LOW
  digitalWrite(PIN_BUZZER, on ? LOW : HIGH);
#else
  digitalWrite(PIN_BUZZER, on ? HIGH : LOW);
#endif
}

// ---------- Timer non-blocking ----------
unsigned long tTelemetry = 0, tSensor = 0, tRamp = 0;
unsigned long beepUntil = 0;

// =======================================================
// Motor — L298N
// =======================================================
void stopMotorsNow() {
  targetL = targetR = motorL = motorR = 0.0f;
  digitalWrite(PIN_IN1, LOW); digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW); digitalWrite(PIN_IN4, LOW);
  ledcWrite(CH_ENA, 0);
  ledcWrite(CH_ENB, 0);
}

void setupMotors() {
  // Kunci motor MATI sebelum apa pun (ENA/ENB mengambang saat boot).
  pinMode(PIN_IN1, OUTPUT); pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT); pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENA, OUTPUT); pinMode(PIN_ENB, OUTPUT);
  digitalWrite(PIN_ENA, LOW); digitalWrite(PIN_ENB, LOW);
  ledcSetup(CH_ENA, PWM_FREQ, PWM_RESOLUTION);
  ledcSetup(CH_ENB, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PIN_ENA, CH_ENA);
  ledcAttachPin(PIN_ENB, CH_ENB);
  stopMotorsNow();
}

// value -1..1 → arah lewat IN, kecepatan lewat PWM EN
void driveMotor(uint8_t inA, uint8_t inB, uint8_t ch, float value, bool invert) {
  value = constrain(value, -1.0f, 1.0f);
  if (invert) value = -value;
  float mag = fabs(value);
  int duty = 0;
  if (mag > MOTOR_DEADZONE) {
    duty = MOTOR_MIN_DUTY + (int)((255 - MOTOR_MIN_DUTY) * mag);
    if (duty > 255) duty = 255;
  }
  if (duty == 0)       { digitalWrite(inA, LOW);  digitalWrite(inB, LOW);  }
  else if (value > 0)  { digitalWrite(inA, HIGH); digitalWrite(inB, LOW);  }
  else                 { digitalWrite(inA, LOW);  digitalWrite(inB, HIGH); }
  ledcWrite(ch, duty);
}

// Melambat/berhenti langsung, mempercepat bertahap.
float rampToward(float cur, float target) {
  bool sameDir = (cur >= 0 && target >= 0) || (cur <= 0 && target <= 0);
  if (sameDir && fabs(target) <= fabs(cur)) return target;
  if (!sameDir) cur = 0.0f;
  if (target > cur) return min(cur + RAMP_STEP_PER_TICK, target);
  return max(cur - RAMP_STEP_PER_TICK, target);
}

void updateMotors() {
  motorL = rampToward(motorL, targetL);
  motorR = rampToward(motorR, targetR);
  driveMotor(PIN_IN1, PIN_IN2, CH_ENA, motorL, INVERT_MOTOR_L);
  driveMotor(PIN_IN3, PIN_IN4, CH_ENB, motorR, INVERT_MOTOR_R);
}

// =======================================================
// Sensor — HC-SR04 bergiliran (pengganti simulateSensors)
// =======================================================
float readUltrasonic(uint8_t i) {
  digitalWrite(TRIG[i], LOW);  delayMicroseconds(2);
  digitalWrite(TRIG[i], HIGH); delayMicroseconds(10);
  digitalWrite(TRIG[i], LOW);
  unsigned long us = pulseIn(ECHO[i], HIGH, ECHO_TIMEOUT_US);
  return us == 0 ? NO_ECHO_CM : us / 58.0f;
}

float median3(float a, float b, float c) {
  return max(min(a, b), min(max(a, b), c));
}

void readSensors(unsigned long now) {
  if (now - tSensor < SENSOR_GAP_MS) return;
  tSensor = now;

  uint8_t i = sensorIdx;
  hist[i][histIdx[i]] = readUltrasonic(i);         // blocking maks ~25 ms
  histIdx[i] = (histIdx[i] + 1) % 3;
  distCm[i] = median3(hist[i][0], hist[i][1], hist[i][2]);  // buang glitch sesaat
  sensorIdx = (sensorIdx + 1) % 4;

  // SENSOR HALANGAN (depan): kiri & kanan dievaluasi sendiri-sendiri
  bool newObsL = distCm[2] <= OBSTACLE_CM;   // US3 depan-kiri  → hanya Halangan Kiri
  bool newObsR = distCm[3] <= OBSTACLE_CM;   // US4 depan-kanan → hanya Halangan Kanan
#if AUTO_BEEP_ON_OBSTACLE
  if ((newObsL && !obsL) || (newObsR && !obsR)) beepUntil = now + 200;
#endif
  obsL = newObsL;
  obsR = newObsR;
  // SENSOR SAMPAH (bak): penuh hanya kalau KEDUA sensor bak membaca dekat
  binFull = (distCm[0] <= BIN_FULL_CM) && (distCm[1] <= BIN_FULL_CM);
}

// =======================================================
// Kirim telemetry ke semua HP yang connect
// (field sama dengan versi breadboard; dist* tambahan, diabaikan UI)
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
  doc["distBL"] = (int)distCm[0];
  doc["distBR"] = (int)distCm[1];
  doc["distFL"] = (int)distCm[2];
  doc["distFR"] = (int)distCm[3];

  String out;
  serializeJson(doc, out);
  webSocket.broadcastTXT(out);
}

// =======================================================
// Handler perintah dari HP (protokol sama dengan webpage.h)
// =======================================================
void handleCommand(const JsonDocument &doc) {
  const char* type = doc["type"];
  if (type == nullptr) return;
  lastCmdMs = millis();

  if (strcmp(type, "joystick") == 0) {
    float x = doc["x"] | 0.0f;
    float y = doc["y"] | 0.0f;
    float throttle = -y;   // maju = atas = y negatif
    float turn = x;
    targetL = constrain(throttle + turn, -1.0f, 1.0f);
    targetR = constrain(throttle - turn, -1.0f, 1.0f);
#if DEBUG_SENSORS
    static unsigned long tJs = 0;
    if (millis() - tJs > 500 && (x != 0 || y != 0)) { tJs = millis(); Serial.printf("JOYSTICK x=%+.2f y=%+.2f -> target L=%+.2f R=%+.2f\n", x, y, targetL, targetR); }
#endif
    failsafeTripped = false;
  }
  else if (strcmp(type, "buzzer") == 0) {
    buzzerOn = doc["state"] | false;
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
        stopMotorsNow();                 // HP terakhir putus → berhenti
        buzzerOn = false;
      }
      break;

    case WStype_CONNECTED:
      lastCmdMs = millis();
      break;

    case WStype_TEXT: {
      JsonDocument doc;
      DeserializationError err = deserializeJson(doc, payload, length);
      if (!err) handleCommand(doc);
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
  setupMotors();                         // PALING AWAL: motor terkunci mati

  buzzerWrite(false);                   // set level OFF dulu, baru jadi output
  pinMode(PIN_BUZZER, OUTPUT);
  buzzerWrite(false);
  for (uint8_t i = 0; i < 4; i++) {
    pinMode(TRIG[i], OUTPUT); digitalWrite(TRIG[i], LOW);
    pinMode(ECHO[i], INPUT);
    for (uint8_t k = 0; k < 3; k++) hist[i][k] = NO_ECHO_CM;
  }

  Serial.begin(115200);
  {
    esp_reset_reason_t r = esp_reset_reason();
    const char* why = r == ESP_RST_BROWNOUT ? "BROWNOUT (tegangan drop, cek baterai/kabel power!)" :
                      r == ESP_RST_POWERON  ? "power on" : r == ESP_RST_SW ? "software" :
                      r == ESP_RST_PANIC    ? "crash/panic" : r == ESP_RST_INT_WDT || r == ESP_RST_TASK_WDT ? "watchdog" : "lain";
    Serial.printf("\nARCA boot, alasan reset: %s (%d)\n", why, (int)r);
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_AP_SSID, WIFI_AP_PASSWORD);
  WiFi.setSleep(false);                  // latensi WebSocket lebih stabil
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());       // default: 192.168.4.1
  Serial.println("Buka browser HP ke alamat di atas buat akses UI kontrol.");

  httpServer.on("/", HTTP_GET, handleRoot);
  httpServer.onNotFound(handleRoot);
  httpServer.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // bunyi pendek tanda siap
  buzzerWrite(true); delay(120); buzzerWrite(false);
}

// =======================================================
// Loop — non-blocking (kecuali 1 pembacaan sensor ≤25 ms)
// =======================================================
void loop() {
  httpServer.handleClient();
  webSocket.loop();

  unsigned long now = millis();

  // FAILSAFE: tidak ada pesan dari HP → motor stop + bunyi
  if (!failsafeTripped && (targetL != 0 || targetR != 0 || motorL != 0 || motorR != 0)
      && now - lastCmdMs > FAILSAFE_MS) {
    stopMotorsNow();
    failsafeTripped = true;
    beepUntil = now + 1000;
    Serial.println("FAILSAFE: koneksi HP hilang, motor dimatikan");
  }

  if (now - tRamp >= RAMP_TICK_MS) {
    tRamp = now;
    updateMotors();
  }

  readSensors(now);

  bool beep = buzzerOn || (now < beepUntil && ((now / 120) % 2 == 0));
  buzzerWrite(beep);

  if (now - tTelemetry >= TELEMETRY_INTERVAL_MS) {
    tTelemetry = now;
    sendTelemetry();
  }

#if DEBUG_SENSORS
  static unsigned long tDebug = 0;
  if (now - tDebug >= 500) {
    tDebug = now;
    Serial.printf("SAMPAH bakL=%3dcm bakR=%3dcm %s | HALANGAN depL=%3dcm %s depR=%3dcm %s | motor L=%+.2f R=%+.2f\n",
                  (int)distCm[0], (int)distCm[1], binFull ? "PENUH " : "kosong",
                  (int)distCm[2], obsL ? "ADA " : "aman", (int)distCm[3], obsR ? "ADA " : "aman",
                  motorL, motorR);
  }
#endif
}
