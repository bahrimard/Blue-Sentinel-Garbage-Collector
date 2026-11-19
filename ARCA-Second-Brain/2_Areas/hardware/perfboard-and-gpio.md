# Hardware — Perfboard, GPIO, Grounding, Konektor

> **TL;DR:** 4 perfboard per subsistem (A PWR, B MCU, C SNS, D BUZ). GPIO final: TRIG 4/5/18/19 · ECHO 34/35/32/33 · IN 13/14/16/17 · EN 25/26 · buzzer 27. **Semua GND ke satu STAR GND di Board A**, satu kabel per modul. Diagram & tabel pin‑ke‑pin: `ARCA-Artifacts/wiring/`.

## Pembagian board

| Board | Isi | Masuk | Keluar |
|---|---|---|---|
| **A · PWR** | VBAT bus (star), L7805 + 1 µF in/out, STAR GND | Baterai 2S | J3 → L298N 12V · J2 → ESP32 VIN · 5V rail → C, D (conveyor langsung dari titik tengah pack, bukan dari Board A) |
| **B · MCU** | ESP32 DevKit V1, header berlabel | VIN/GND dari A | IN1‑4, ENA/ENB → L298N · TRIG/ECHO → C · GPIO27 → D |
| **C · SNS** | 4 terminal block screw 4‑pin (TB1–TB4: VCC·TRIG·ECHO·GND), divider ECHO 470Ω/1kΩ ×4 | 5V dari A, sinyal dari B | ECHO (3.40 V) → B |
| **D · BUZ** | BC337, 1kΩ basis, buzzer | 5V, GPIO27 | — |

Modul jadi (L298N) tidak dibangun ulang, cukup disambung. Board D boleh digabung fisik dengan C.

## GPIO map (final, versi lomba — tidak diubah)

| GPIO | Fungsi | Catatan |
|---|---|---|
| 4, 5, 18, 19 | TRIG US1 Bak‑Kiri, US2 Bak‑Kanan, US3 Depan‑Kiri, US4 Depan‑Kanan | GPIO5 pull‑up saat boot → 1 trigger palsu, aman |
| 34, 35 | ECHO US1, US2 (bak / SAMPAH) | input‑only |
| 32, 33 | ECHO US3, US4 (depan / HALANGAN) | dipindah 23 Sep dari 36/39 (tercetak VP/VN di board, rawan glitch) |
| 13, 14 | IN1, IN2 motor kiri | GPIO14 keluar PWM saat boot → motor bisa kedut |
| 16, 17 | IN3, IN4 motor kanan | aman di WROOM‑32 (bukan WROVER) |
| 25, 26 | ENA, ENB (PWM) | ADC2 tapi dipakai sebagai output → tidak konflik WiFi |
| 27 | Buzzer (basis BC337 via 1kΩ) | |
| 21, 22, 23, 36 (VP), 39 (VN) | Cadangan (21 SDA, 22 SCL; 36/39 input‑only, cocok untuk ukur baterai via ADC) | |
| 0, 1, 2, 3, 6–12, 15 | **Jangan dipakai** | strapping / flash / UART0 |

## Grounding

Satu titik **STAR GND** di Board A (terminal negatif baterai). Tiap modul (L298N, ESP32, Board C, Board D, L7805, motor conveyor −) **satu kabel GND langsung ke star**. **Jangan** tambah kabel “GND ref” antar modul — membuat ground loop sehingga arus motor numpang lewat ground ESP32/sensor.

## Konektor

- Sinyal: pin header 2.54 mm + dupont.
- Sensor: terminal block screw per sensor (tahan getar, gampang servis).
- Power (baterai, L298N, kabel titik tengah ke conveyor): kabel paling tebal yang ada + terminal screw (dupont hanya ~1 A/pin).

## Konvensi arah

Motor kanan lebih kencang = belok **kiri**. Arah motor salah → tukar 2 kabel di OUT L298N (bukan ubah kode; kalau terpaksa: `INVERT_MOTOR_L/R` di `config.h`).
