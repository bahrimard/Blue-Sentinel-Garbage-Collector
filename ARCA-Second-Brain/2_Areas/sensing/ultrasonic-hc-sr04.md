# Sensor — 4× HC‑SR04 Statis

> **TL;DR:** **Sensor HALANGAN** = 2 sensor depan: depan‑kiri ≤ 40 cm → hanya “Halangan Kiri”, depan‑kanan ≤ 40 cm → hanya “Halangan Kanan” (berdiri sendiri). **Sensor SAMPAH** = 2 sensor di bak: “Penuh” hanya kalau **keduanya** ≤ 6 cm (≈5 cm + toleransi 1 cm). ECHO lewat divider 470Ω/1kΩ (5 V → 3.40 V). Dibaca bergiliran 60 ms, median 3 sampel. **Tanpa servo** (konsep servo diarsipkan).

## Penempatan & pin

| ID | Posisi | TB | TRIG | ECHO | Dipakai untuk |
|---|---|---|---|---|---|
| US1 | Bak kiri | TB1 | 4 | 34 | **SAMPAH** → `binFull` (bersama US2) · UI “Bak L … cm” |
| US2 | Bak kanan | TB2 | 5 | 35 | **SAMPAH** → `binFull` (bersama US1) · UI “Bak R … cm” |
| US3 | Depan kiri | TB3 | 18 | 32 | **HALANGAN** → `obsL` · chip “Halangan Kiri” |
| US4 | Depan kanan | TB4 | 19 | 33 | **HALANGAN** → `obsR` · chip “Halangan Kanan” |

| Aturan | Kondisi | Hasil di UI |
|---|---|---|
| Halangan kiri | US3 ≤ 40 cm | chip Halangan Kiri = Terdeteksi (+ bunyi pendek), kanan tidak terpengaruh |
| Halangan kanan | US4 ≤ 40 cm | chip Halangan Kanan = Terdeteksi (+ bunyi pendek), kiri tidak terpengaruh |
| Sampah penuh | US1 ≤ 6 cm **dan** US2 ≤ 6 cm | chip Sampah (Bak) = Penuh |
| Tidak ada pantulan | timeout 25 ms | dibaca 400 cm (aman) |

## Rangkaian

- VCC → 5V rail (L7805), GND → rail GND Board C → STAR.
- TRIG langsung dari ESP32 (3.3 V cukup).
- ECHO → **470Ω (sisi sensor)** → titik tengah → **1kΩ (sisi GND)**; titik tengah → GPIO. 5 × 1000/1470 = 3.40 V. Kalau resistor terbalik, ESP32 hanya dapat ~1.6 V → sensor tidak terbaca.

## Firmware

- Satu sensor per 60 ms (hindari crosstalk antar sensor), `pulseIn` timeout 25 ms (~4.3 m) → tidak ada pantulan = 400 cm (“aman”).
- Median 3 sampel per sensor → buang pembacaan palsu sesaat.
- Bunyi pendek otomatis saat halangan depan baru terdeteksi (`AUTO_BEEP_ON_OBSTACLE`).
- Telemetry juga mengirim `distFL/FR/BL/BR` (cm) — diabaikan UI, berguna untuk debug/kalibrasi (lihat di Serial/WS client).

## Kalibrasi (lakukan sebelum lomba)

1. Buka Serial Monitor (115200): tiap 500 ms tercetak `SAMPAH bakL=..cm bakR=..cm | HALANGAN depL=..cm depR=..cm`. Isi bak sampai batas “penuh”, pastikan keduanya ≤ 6 cm; kalau tidak, ubah `BIN_FULL_CM`. HC‑SR04 baru akurat mulai ~3 cm — jangan pasang sensor bak terlalu dekat dengan tumpukan maksimum.
2. Uji jarak halangan yang realistis di air → sesuaikan `OBSTACLE_CM`.

## Batasan

- HC‑SR04 **tidak tahan air** → pasang di atas garis air, beri tudung, coating di sisi solderan PCB (bukan transduser).
- Permukaan air bisa memantulkan jika sensor terlalu menunduk.
