# Proyek: Lomba Robotik November 2026 — ARCA v2 (Deteksi Sampah AI + Dashboard IoT)

> **TL;DR:** Evolusi ARCA: 2 MCU (ESP32‑CAM mata + ESP32 DevKit badan), 2 baterai terpisah (CAM 1S, utama 3S), Edge Hub (Mosquitto + YOLO + DB), dashboard web HP/laptop. Status: **analisis kebutuhan DRAFT v0.1 selesai (19 Nov 2026)**, belum ada kode/hardware v2. Tanggal lomba: _belum diketahui_. Branch git: `lomba-robotik-november-2026`.

## Baca urutan ini (hemat token)

| Perlu apa | Buka | Ukuran |
|---|---|---|
| Gambaran & 8 keputusan inti | bagian TL;DR + §1 di [requirements-analysis](requirements-analysis.md) | kecil |
| Kebutuhan (FR/NFR, MoSCoW, kriteria) | §8–§9 di requirements-analysis | sedang |
| Desain AI/deteksi | §10 | sedang |
| Baterai, 5 V/12 V, sekring, wiring, komponen | [power-and-wiring-design](power-and-wiring-design.md) | sedang |
| Topik MQTT, payload, ACL, failsafe | [mqtt-contract](mqtt-contract.md) | kecil |
| Roadmap & MVP cut | §15 requirements-analysis | kecil |
| Pertanyaan tim yang belum terjawab | §17 requirements-analysis · [inbox](../../0_Capture/inbox-open-questions.md) | kecil |

## Keputusan yang diusulkan (belum disetujui tim)

D1 tiga bidang komunikasi (MQTT / MJPEG / AP darurat) · D2 Edge Hub lokal · D3 deteksi bertingkat warna→TinyML→YOLO · D4 dua pack, GND terpisah · D5 pack 3S langsung ke motor, 5 V dari buck · D6 driver BTS7960 gantikan L298N · D7 lease kendali · D8 GPS → peta panas. Alasan: requirements-analysis §1 & §5. Dicatat di [decision-log](../../3_Resources/decision-log.md) sebagai "diusulkan".

## Status & langkah berikutnya

- [x] Analisis kebutuhan, desain power, kontrak MQTT (draft)
- [ ] Review tim + jawab pertanyaan §17 (terutama tanggal lomba & rating motor)
- [ ] Ukur arus motor/conveyor nyata (menentukan sekring & driver)
- [ ] Fase 0: pack baru + driver + MQTT di firmware DevKit + `AP_STA` + dashboard minimal
- [ ] Fase 1: firmware CAM (MJPEG + deteksi warna) + overlay dashboard
- [ ] Audit GPIO DevKit (anggaran ≈ 22/25 pin)

Proyek sebelumnya yang dilanjutkan: [lomba-berikutnya](../lomba-berikutnya/README.md) (ide kamera FPV) · [lomba-2026-09-24](../lomba-2026-09-24/README.md).
