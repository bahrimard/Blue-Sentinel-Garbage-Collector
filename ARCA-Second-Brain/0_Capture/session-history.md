# Kronologi Proyek ARCA

> **TL;DR:** Kode breadboard + UI `webpage.h` dibuat duluan (±20–21 Sep). Sesi desain 21 Sep menghasilkan wiring plan & app ARCA Control versi sendiri (protokol berbeda dari kode). Sesi 23 Sep: review keamanan → versi lomba tanpa komponen tambahan → ketahuan protokol app ≠ kode asli → artifact diselaraskan ke `webpage.h` + firmware final ditulis dari kode asli.

Catatan mentah (Capture). Ringkasan keputusan ada di [decision-log](../3_Resources/decision-log.md).

## ±20–21 Sep 2026 — Kode lokal “Blue Sentinel - ARCA”

- Proyek PlatformIO dibuat (`esp32doit-devkit-v1`, lib `links2004/WebSockets`, `ArduinoJson` v7).
- **Breadboard test mode**: part asli (L298N, HC‑SR04, buzzer) belum datang, jadi motor/sensor/buzzer digantikan LED (`pins.h` lama → [arsip](../4_Archives/breadboard-test-mode.md)).
- `webpage.h`: UI kontrol dark (radar jejak navigasi, chip Halangan Kiri/Kanan, Tampungan, Conveyor, joystick, tombol buzzer) di-serve ESP32 di `http://192.168.4.1/`, WebSocket port 81.
- Sensor masih disimulasikan acak (`simulateSensors`).

## 21 Sep 2026 — Sesi desain (Claude)

- **Wiring plan 4 perfboard** + GPIO map final (TRIG 4/5/18/19, ECHO 34/35/36/39, IN 13/14/16/17, EN 25/26, buzzer 27). Revisi: tiap sensor pakai terminal block screw 4‑pin (tahan getar, gampang servis).
- Artifact **ARCA Wiring Map** (detail per‑board).
- Artifact **ARCA Control v1** + dokumen protokol `cmd:move` (WebSocket `/ws`, PWM ±255). ⚠️ Dibuat tanpa melihat `webpage.h`, jadi **tidak cocok** dengan kode asli → [arsip](../4_Archives/app-protocol-v1-cmd-move.md).

## 23 Sep 2026 — Sesi review & persiapan lomba (Claude)

1. User minta wiring diagram lengkap + assessment “aman & optimal?”.
   - Klarifikasi: **4 sensor statis** (bukan servo), **part lama dipertahankan** (L298N, L7805).
2. Review v1: 5 wajib (BMS, sekring, saklar, pull‑down ENA/ENB, failsafe) + 7 disarankan → [arsip review v1](../4_Archives/review-v1-bms-and-protection.md).
3. Tanya jawab BMS → user charge sel **dicopot satu‑satu** → BMS tidak wajib; pengganti: sekring + cutoff firmware (monitor tegangan per sel).
4. User: **lomba besok pagi, jangan tambah komponen**. → Wiring diagram **versi lomba**: hanya part di plan, 6 aturan wajib yang gratis (jumper, grounding, isolasi kabel, firmware, cara menyalakan, cek tegangan). GPIO tidak diubah.
5. Saat menyusun dokumentasi: temuan di ARCA Control v1 — ping 2 s (tidak cocok failsafe), jejak navigasi **terbalik arah belok**, dan artifact https **tidak bisa** konek ke `ws://` ESP32. Dirilis v2 (perbaikan).
6. User menunjuk `webpage.h` di kode lokal → dibaca → **ARCA Control v3 = UI `webpage.h` persis** + Mode Simulasi otomatis saat dibuka di luar ESP32.
7. Firmware starter berbasis AsyncWebServer yang sempat ditulis **dibuang** (protokol salah). Diganti **firmware final** turunan `main.cpp` asli: protokol/port/UI sama, driver L298N + HC‑SR04 + buzzer asli, failsafe 600 ms, ramp, motor dikunci saat boot.
8. Vault dokumentasi ini (BASB/CODE/PARA) + folder `ARCA-Artifacts` dibuat, disalin ke folder proyek lokal.
9. User minta kendali & sensor dipastikan works: ambang final **halangan ≤ 40 cm per sisi (independen)**, **sampah penuh bila kedua sensor bak ≤ ~5 cm (6 cm)**. UI diberi nama sensor + jarak cm. Firmware diuji logikanya di PC (g++ + tiruan hardware): **30/30 lulus**. Debug Serial jarak sensor ditambahkan.
10. Modul buck ternyata tidak ada (“BAOTER 3296” = trimpot di modul LM2596). Opsi 3V3 ESP32 dan 5V L298N ditolak (terlalu lemah/berisiko). **Conveyor dipindah ke titik tengah pack** (1 sel), diagram & tabel koneksi diperbarui.
11. User tidak menemukan pin 36 di board (tercetak VP/VN). ECHO depan dipindah ke **D32 (kiri) / D33 (kanan)**; firmware, test (30/30 lulus ulang), diagram, dan dokumen diperbarui.
12. **Desain PCB v1** (Eagle): 1 layer modular — ARCA MAIN v1 + 4× ARCA SENSOR v1. Diverifikasi: DRC mandiri, import ke KiCad 7 + DRC (0 short/0 unconnected), netlist sch=brd, Gerber dibaca ulang. Firmware diberi varian pin `ARCA_PCB_V1` (env `arca-pcb`), test 30/30 untuk kedua varian.

## Belum terjadi (per 23 Sep malam)

- Firmware final belum di-compile untuk ESP32/upload (toolchain ESP32 tidak bisa diunduh di lingkungan Claude); logika sudah lulus uji PC.
- Belum ada uji di air.
