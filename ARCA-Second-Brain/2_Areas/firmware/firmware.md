# Firmware ESP32

> **TL;DR:** Firmware final = `ARCA-Artifacts/firmware/` (PlatformIO), turunan langsung `main.cpp` breadboard: **protokol, port, UI sama**; driver LED diganti L298N + HC‑SR04 + buzzer asli; tambah **motor terkunci saat boot, failsafe 600 ms, ramp, sensor bergiliran + median**. Logika sudah lulus **30/30 uji di PC**; **belum di-compile untuk ESP32/diuji di board** — lakukan malam ini.

## Struktur

```
firmware/
├── platformio.ini          (sama dengan proyek lokal: esp32doit-devkit-v1, WebSockets 2.4.x, ArduinoJson 7)
├── src/main.cpp            firmware final
├── src/pins.h              pinout final (hardware asli)
├── src/config.h            SSID, failsafe, ramp, threshold sensor
├── src/webpage.h           UI (auto-generate dari web-ui/arca-control.html)
├── tools/make_webpage_h.py
├── test/                   uji logika di PC (test.cpp + stubs/ + run_test.sh)
└── _arsip-breadboard-test-mode/   main.cpp, pins.h, config.h versi LED (referensi)
```

## Dua varian pin

- `esp32doit-devkit-v1` (default) = rakit kabel/perfboard versi lomba.
- `arca-pcb` (`-DARCA_PCB_V1`) = PCB ARCA MAIN v1 — pin berbeda, lihat [pcb-v1](../hardware/pcb-v1.md). `bash test/run_test.sh` menguji keduanya.

## Cara pasang ke proyek lokal (malam ini)

1. Backup: salin folder `Blue Sentinel - ARCA/src` → `src-breadboard-backup`.
2. Salin `firmware/src/*` (4 file) ke `Blue Sentinel - ARCA/src/`. `platformio.ini` tidak perlu diubah.
3. VS Code PlatformIO → **Build**, lalu **Upload**, lalu **Monitor** (115200) → harus muncul `AP IP address: 192.168.4.1`.
4. Jalankan [test-plan](../../1_Projects/lomba-2026-09-24/test-plan.md).

## Perbedaan vs versi breadboard

| Bagian | Breadboard (LED) | Final |
|---|---|---|
| Motor | 4 LED PWM (18/19/21/22) | L298N: IN 13/14/16/17, PWM ENA 25/ENB 26, `MOTOR_MIN_DUTY`, ramp |
| Sensor | `simulateSensors()` acak | 4× HC‑SR04 bergiliran 60 ms, median 3, threshold |
| Buzzer | LED GPIO23 | GPIO27 → BC337; + bunyi otomatis halangan/failsafe; bunyi pendek saat siap |
| Keamanan | — | motor dikunci di awal `setup()`; failsafe 600 ms; stop saat client terakhir putus; `WiFi.setSleep(false)` |
| Telemetry | motor, obs, bin, conveyor | + `distFL/FR/BL/BR` |
| `onNotFound` | — | semua path → UI |

## Parameter yang boleh diubah (`config.h`)

`FAILSAFE_MS` 600 · `RAMP_STEP_PER_TICK` 0.10 · `MOTOR_MIN_DUTY` 90 · `MOTOR_DEADZONE` 0.05 · `INVERT_MOTOR_L/R` · `OBSTACLE_CM` 40 · `BIN_FULL_CM` 6 · `SENSOR_GAP_MS` 60 · `AUTO_BEEP_ON_OBSTACLE` 1 · `DEBUG_SENSORS` 1.

## Alur kendali (joystick → motor)

HP (`webpage.h`) kirim `{"type":"joystick","x","y"}` tiap 100 ms lewat WebSocket port 81 → `webSocketEvent()` → `handleCommand()` hitung `targetL = −y + x`, `targetR = −y − x` → tiap 20 ms `updateMotors()` ramp lalu `driveMotor()` set IN1–IN4 (arah) + `ledcWrite` ENA/ENB (kecepatan) → L298N → motor. ESP32 balas telemetry `motorL/motorR` tiap 150 ms; bar motor & jejak di UI memakai nilai ini (bukan posisi joystick), jadi UI menunjukkan apa yang benar‑benar dijalankan board.

## Uji logika di PC (sudah dijalankan 23 Sep: 30/30 lulus)

`bash test/run_test.sh` (butuh g++; ArduinoJson dari `.pio/libdeps`). Hardware diganti tiruan (`test/stubs`), lalu diuji: motor terkunci saat boot, akselerasi bertahap, maju/mundur/belok kiri/kanan/putar di tempat → pin IN & duty benar, failsafe 600 ms + buzzer, stop saat disconnect, halangan kiri/kanan independen di batas 40/41 cm, sampah penuh hanya bila kedua sensor ≤ 6 cm, filter glitch, tombol buzzer. **Yang tidak bisa diuji di PC:** compile untuk ESP32, timing HC‑SR04 asli, WiFi, dan arah putar motor fisik — itu tetap dicek dengan test‑plan.

## Catatan teknis

- API LEDC `ledcSetup/ledcAttachPin` = Arduino core 2.x (default PlatformIO `espressif32`). Kalau suatu saat pakai core 3.x, ganti ke `ledcAttach(pin, freq, res)` dan `ledcWrite(pin, duty)`.
- `pulseIn` memblok ≤25 ms per siklus 60 ms — WebSocket/HTTP tetap responsif.
- Kalau compile error menyebut pin/lib: cek versi lib di `platformio.ini` sama dengan proyek lokal.
