#pragma once

// ESP32 jadi Access Point sendiri — HP connect langsung ke sini,
// gak butuh router/WiFi rumah.
#define WIFI_AP_SSID       "ARCA-Boat"
#define WIFI_AP_PASSWORD   "arca12345"   // WPA2 min. 8 karakter

#define WEBSOCKET_PORT     81

#define TELEMETRY_INTERVAL_MS   150   // kirim status ke HP tiap 150ms

// ---------- Keselamatan ----------
// UI (webpage.h) kirim "joystick" tiap 100 ms walau stik netral.
// Kalau tidak ada pesan selama ini → motor dimatikan (HP putus / layar mati).
#define FAILSAFE_MS             600

// ---------- Motor ----------
// Akselerasi bertahap supaya arus start tidak bikin ESP32 brownout.
#define RAMP_STEP_PER_TICK      0.10f   // perubahan maks nilai motor (-1..1) per tick
#define RAMP_TICK_MS            20
// L298N buang ~2 V, jadi motor kecil sering baru muter di duty ~35%.
// Nilai joystick kecil (di atas deadzone) dipetakan mulai dari MIN_DUTY.
// Set MOTOR_MIN_DUTY 0 kalau motor sudah mau muter di duty kecil.
#define MOTOR_DEADZONE          0.05f
#define MOTOR_MIN_DUTY          90      // 0-255
// Kalau satu motor muter terbalik, paling gampang tukar kabel di OUT L298N.
// Kalau tidak sempat, set 1 di sini.
#define INVERT_MOTOR_L          0
#define INVERT_MOTOR_R          0

// ---------- Sensor HC-SR04 ----------
#define SENSOR_GAP_MS           60      // 1 sensor per 60 ms, bergiliran (hindari crosstalk)
#define ECHO_TIMEOUT_US         25000   // ~4.3 m; lewat ini dianggap "tidak ada halangan"
#define NO_ECHO_CM              400
// SENSOR HALANGAN = 2 sensor DEPAN (US3 kiri, US4 kanan), kiri & kanan berdiri sendiri:
//   depan-kiri  <= OBSTACLE_CM → hanya "Halangan Kiri"  terdeteksi
//   depan-kanan <= OBSTACLE_CM → hanya "Halangan Kanan" terdeteksi
#define OBSTACLE_CM             40
// SENSOR SAMPAH = 2 sensor di BAK (US1 kiri, US2 kanan):
//   KEDUANYA <= BIN_FULL_CM → "Tampungan Penuh" (≈5 cm, +1 cm toleransi baca HC-SR04)
//   Catatan: HC-SR04 baru akurat mulai ~3 cm — pasang sensor bak minimal 3 cm dari tumpukan maksimum.
#define BIN_FULL_CM             6

// 1 = cetak jarak 4 sensor ke Serial Monitor tiap 500 ms (untuk uji & kalibrasi)
#define DEBUG_SENSORS           1

// ---------- Buzzer ----------
// 1 = buzzer/modul aktif LOW (bunyi saat pin LOW, mis. modul buzzer 3 pin atau transistor PNP)
// 0 = bunyi saat pin HIGH (BC337 NPN sesuai wiring diagram)
#define BUZZER_ACTIVE_LOW       1
#define AUTO_BEEP_ON_OBSTACLE   1       // 1 = bunyi pendek otomatis saat halangan depan baru terdeteksi
