#pragma once

// ============================================================
// ARCA — Pinout FINAL (hardware asli, versi lomba 2026-09-24)
// Board: esp32doit-devkit-v1
//
// Menggantikan pins.h "BREADBOARD TEST MODE" (LED). Sesuai
// wiring plan final: ARCA-Second-Brain/2_Areas/hardware/perfboard-and-gpio.md
// ============================================================
//
// DUA VARIAN PIN:
//   (default)      = rakit kabel / perfboard (versi lomba 24 Sep) — sesuai wiring diagram
//   ARCA_PCB_V1    = PCB ARCA MAIN v1 (1 layer). Build dengan env "arca-pcb" di platformio.ini.
//                    Pin diatur ulang supaya PCB 1 layer bisa dirute tanpa silang.
// ============================================================


// ================= Rakit kabel (versi lomba) =================
// ---- L298N — motor kiri (OUT1/OUT2) ----
#define PIN_IN1           13
#define PIN_IN2           14
#define PIN_ENA           25   // PWM kecepatan kiri (jumper ENA di L298N DICABUT)

// ---- L298N — motor kanan (OUT3/OUT4) ----
#define PIN_IN3           16
#define PIN_IN4           17
#define PIN_ENB           26   // PWM kecepatan kanan (jumper ENB di L298N DICABUT)

// ---- HC-SR04 ×4 (ECHO lewat divider 470Ω/1kΩ → 3.40 V) ----
// index 0 = US1 Bak-Kiri, 1 = US2 Bak-Kanan, 2 = US3 Depan-Kiri, 3 = US4 Depan-Kanan
#define PIN_TRIG_BIN_L    4
#define PIN_TRIG_BIN_R    5
#define PIN_TRIG_FRONT_L  18
#define PIN_TRIG_FRONT_R  19
#define PIN_ECHO_BIN_L    34
#define PIN_ECHO_BIN_R    35
#define PIN_ECHO_FRONT_L  32   // D32 (dulu GPIO36/VP)
#define PIN_ECHO_FRONT_R  33   // D33 (dulu GPIO39/VN)

// ---- Buzzer (GPIO27 → 1kΩ → basis BC337) ----
#define PIN_BUZZER        27


// ---- LEDC PWM ----
#define CH_ENA            0
#define CH_ENB            1
#define PWM_FREQ          2000   // 1–5 kHz cocok untuk L298N
#define PWM_RESOLUTION    8      // 0-255
