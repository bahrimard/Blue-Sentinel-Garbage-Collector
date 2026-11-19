# Proyek: Upgrade Pasca Lomba

> **TL;DR:** Hasil review 23 Sep yang sengaja ditunda karena waktu. Urutan dampak terbesar: sekring+saklar → pull‑down ENA/ENB → kapasitor → cutoff baterai otomatis → driver motor efisien.

| Prioritas | Upgrade | Kenapa | Detail |
|---|---|---|---|
| 1 | Sekring 5 A + saklar di kabel baterai | Satu‑satunya pemutus short; mematikan kapal tanpa cabut kabel | [power](../../2_Areas/power/power-system.md) |
| 2 | Resistor 10k ENA→GND, ENB→GND; 10k basis BC337→GND | Hilangkan kedutan motor & bunyi saat boot | [motor](../../2_Areas/propulsion/motor-l298n.md) |
| 3 | Elco 1000 µF di VS L298N; 100 nF di tiap motor; 100 nF+100 µF di VIN ESP32 | Cegah brownout & noise WiFi/sensor | [power](../../2_Areas/power/power-system.md) |
| 4 | GPIO36/VP = VBAT (100k/33k), GPIO39/VN = sel 1 (100k/100k) — ECHO sudah di 32/33 sejak 23 Sep | Cutoff otomatis per sel; baterai asli di UI (ganti 78% statis) | [sensor](../../2_Areas/sensing/ultrasonic-hc-sr04.md) |
| 5 | Ganti L298N → TB6612FNG / DRV8833 | Drop tegangan jauh lebih kecil → dorongan lebih kuat, tidak panas | [motor](../../2_Areas/propulsion/motor-l298n.md) |
| 6 | Opsional: BMS 2S ≥10 A | Kalau nanti charge tanpa dicopot | [arsip review v1](../../4_Archives/review-v1-bms-and-protection.md) |
| 7 | Encoder/IMU | Jejak navigasi & heading nyata, bukan estimasi | [app](../../2_Areas/control-app/app-and-protocol.md) |
