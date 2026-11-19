# Power — Baterai, Regulasi, Proteksi

> **TL;DR:** 2S 18650 (6.6–8.4 V) → VBAT bus → L298N, ESP32 VIN, L7805 5 V (sensor & buzzer). **Conveyor** diambil dari **titik tengah pack** (1 sel, 3.0–4.2 V) — tanpa buck converter. Versi lomba **tanpa BMS/sekring/saklar**; pengamannya: sel di-charge dicopot, kabel terisolasi, konektor baterai = saklar, cek tegangan tiap sesi. Rentang kerja efektif **7.0–8.4 V** (dropout L7805).

## Topologi

Star dari terminal baterai (bukan daisy‑chain lewat regulator onboard L298N) supaya noise/brownout motor tidak ikut ke ESP32.

| Jalur | Dari → Ke | Catatan |
|---|---|---|
| J3 | VBAT → L298N terminal 12V | arus terbesar; kabel tebal |
| J2 | VBAT → ESP32 VIN | AMS1117 onboard terima ≤~15 V, akan hangat (~0.7–1 W) |
| Tap | Titik tengah pack (+ sel 1) → motor conveyor (+); motor (−) → STAR GND | 3.0–4.2 V, conveyor **selalu ON** selama baterai tercolok |
| U1 | VBAT → L7805 → 5V rail (Board C, D) | beban ~90 mA → ~0.3 W, aman tanpa heatsink |

## Baterai & charging (keputusan 23 Sep)

- Sel **dicopot dan di‑charge satu per satu** di charger 18650 CC/CV (4.2 V) → overcharge & ketidakseimbangan sel tertangani → **BMS tidak wajib**.
- Pakai sepasang sel sama merek/kapasitas/umur, charge penuh bersamaan.
- Cek polaritas holder dengan multimeter sebelum colok (tidak ada proteksi terbalik).
- Ganti/charge kalau total < 7.0 V atau sel < 3.5 V.

## Conveyor dari titik tengah (keputusan 23 Sep malam)

Modul buck tidak tersedia. Opsi yang ditolak: pin 3V3 ESP32 (regulator AMS1117 terlalu kecil, ESP32 akan reset/rusak), pin 5V L298N (78M05 ±0.5 A, mengganggu logic L298N, 5 V kelebihan untuk motor 3.5 V), langsung 7–8.4 V (motor rusak), rail 5V L7805 (mengganggu sensor).
Dipilih: **satu sel 18650 via titik tengah** — tegangan pas (3.0–4.2 V), arus kuat, terpisah dari ESP32/L298N.
Konsekuensi: sel 1 terkuras lebih cepat (±0.3–0.6 A ekstra) → ukur **tiap sel** per sesi; kabel titik tengah tanpa pengaman → isolasi rapat; kecepatan conveyor turun perlahan seiring baterai. Upgrade: modul LM2596 set 3.5 V.

## Kenapa versi lomba aman tanpa sekring?

Tidak seaman dengan sekring — risikonya diterima karena waktu. Mitigasi: semua sambungan VBAT/GND terisolasi, kabel diikat jauh dari air, baterai dicabut saat tidak dipakai. **Sekring 5 A + saklar = upgrade #1** setelah lomba.

## Anggaran arus (estimasi, belum diukur)

| Beban | Normal | Puncak |
|---|---|---|
| 2× motor baling | 1.5–3 A | ~4 A saat start |
| Conveyor (dari sel 1) | 0.3–0.6 A | ~1 A macet |
| ESP32 + WiFi | 0.12 A | 0.5 A |
| 4× HC‑SR04 + buzzer | 0.09 A | 0.1 A |
| **Total** | **~2–4 A** | **~5 A sesaat** |

Sel 18650 sebaiknya rating ≥10 A continuous.

## Batasan

- L7805 butuh input ≥~7 V; di bawahnya 5V rail turun → HC‑SR04 tidak stabil.
- Tidak ada pembacaan baterai; indikator 78% di UI statis.

Upgrade: [upgrade-pasca-lomba](../../1_Projects/upgrade-pasca-lomba/README.md).
