# Urutan Uji Sebelum Lomba

> **TL;DR:** Uji dari yang paling tidak berisiko (tegangan tanpa beban) ke yang paling berisiko (air). Jangan lompat langkah.

| # | Uji | Lulus kalau | Kalau gagal |
|---|---|---|---|
| 1 | Colok baterai **tanpa** ESP32, sensor & conveyor | VBAT 8.2–8.4 V, 5V rail 4.9–5.1 V, titik tengah→GND 3.0–4.2 V | Cek L7805 (kaki 1 IN, 2 GND, 3 OUT); cek kabel titik tengah |
| 2 | Cek jumper L298N | ENA/ENB lepas, 12V‑EN terpasang, pin 5V kosong | — |
| 3 | Pasang ESP32, baling di udara, cabut‑colok baterai 5× | Motor tidak jalan (paling kedut sesaat), buzzer bunyi pendek tanda siap | Cek `setupMotors()` terpanggil paling awal |
| 4 | HP → `ARCA-Boat` → `http://192.168.4.1/` | UI muncul, dot hijau “ARCA-Boat” | Data seluler OFF; cek Serial Monitor |
| 5 | Joystick maju | Kedua motor mendorong kapal ke depan | Tukar 2 kabel motor di OUT L298N |
| 6 | Joystick kanan | Motor kiri lebih kencang (kapal belok kanan); jejak di UI belok kanan | Cek urutan IN1/IN2 vs IN3/IN4 |
| 7 | Tahan joystick, matikan WiFi HP | Motor berhenti < 1 s, buzzer bunyi | Cek `FAILSAFE_MS` |
| 8 | Gas penuh mendadak 10× | ESP32 tidak reset, UI tetap terhubung | Naikkan ramp (kecilkan `RAMP_STEP_PER_TICK`) |
| 9a | Tangan ≤ 40 cm di depan sensor **depan‑kiri** saja | Hanya chip “Halangan Kiri” = Terdeteksi (jarak cm ikut turun), kanan tetap Aman, bunyi pendek | Cek divider ECHO (470Ω sisi sensor) & kabel TB3; lihat Serial `depL=` |
| 9b | Sama untuk sensor **depan‑kanan** saja | Hanya chip “Halangan Kanan” = Terdeteksi | Cek TB4; lihat Serial `depR=` |
| 10a | Tutup **satu** sensor bak (≈5 cm) | Chip “Sampah (Bak)” tetap Kosong | — |
| 10b | Tutup **kedua** sensor bak (≈5 cm) | Chip “Sampah (Bak)” = Penuh | Lihat Serial `bakL/bakR`, kalibrasi `BIN_FULL_CM` |
| 11 | Uji apung ember/bak 5 menit | Tidak ada air masuk ke elektronik | Tambal/lapisi |
