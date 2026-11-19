#pragma once

// ============================================================
// ARCA — Pinout BREADBOARD TEST MODE
// Board: esp32doit-devkit-v1
//
// Part asli (L298N, HC-SR04, buzzer+transistor) masih dipesan.
// Semua output/sensor digantikan LED dulu, dengan protokol
// WebSocket yang SAMA seperti versi final — jadi pas part asli
// datang, cukup ganti bagian driver-nya (pinout final beda,
// lihat catatan project), logic inti gak perlu diubah.
// ============================================================

// ---- Motor kiri (gantiin L298N — 2 LED arah, PWM = kecepatan) ----
#define PIN_MOTOR_L_FWD   18   // LED nyala saat maju, brightness = speed
#define PIN_MOTOR_L_REV   19   // LED nyala saat mundur, brightness = speed

// ---- Motor kanan ----
#define PIN_MOTOR_R_FWD   21
#define PIN_MOTOR_R_REV   22

// ---- Indikator sensor (disimulasikan firmware, ganti ke HC-SR04 asli nanti) ----
#define PIN_LED_OBS_L     25   // gantiin: HALANGAN KIRI
#define PIN_LED_OBS_R     26   // gantiin: HALANGAN KANAN
#define PIN_LED_BIN_FULL  27   // gantiin: TAMPUNGAN penuh

// ---- Status ----
#define PIN_LED_CONVEYOR  14   // simulasi "conveyor aktif" (nanti gak butuh pin asli)
#define PIN_LED_BUZZER    23   // gantiin buzzer + transistor BC337
#define PIN_LED_WIFI      13   // nyala kalau ada HP yang connect ke ESP32

// ---- LEDC PWM channel assignment (untuk motor LED) ----
#define CH_MOTOR_L_FWD   0
#define CH_MOTOR_L_REV   1
#define CH_MOTOR_R_FWD   2
#define CH_MOTOR_R_REV   3
#define PWM_FREQ         5000
#define PWM_RESOLUTION   8   // 0-255
