# Proyek: Lomba 24 Sep 2026

> **TL;DR:** Tujuan = kapal jalan stabil dikendalikan HP, sensor halangan & bak penuh tampil di UI, tidak ada insiden listrik. Malam ini: rakit sesuai diagram → flash firmware final → jalankan urutan uji. Besok: bawa sel cadangan, HP data seluler OFF, buka `http://192.168.4.1/`.

**Deadline:** 24 Sep 2026 pagi · **Outcome:** demo kendali manual + telemetry yang andal.

## Malam ini (urut)

- [ ] **Rakit** sesuai [wiring diagram](../../../ARCA-Artifacts/wiring/arca-wiring-diagram.html) (tabel koneksi pin‑ke‑pin di halaman itu).
- [ ] **Jumper L298N**: ENA/ENB **dicabut**, 12V‑EN **pasang**, pin 5V **kosong**.
- [ ] **GND**: satu kabel per modul ke STAR GND, tanpa kabel GND tambahan antar modul.
- [ ] **Isolasi** semua sambungan VBAT/GND (tidak ada sekring → short = risiko terbesar).
- [ ] **Firmware final**: backup `src/` lama → salin `ARCA-Artifacts/firmware/src/*` ke proyek lokal → `pio run -t upload` → cek Serial Monitor `AP IP address: 192.168.4.1`. Detail: [firmware.md](../../2_Areas/firmware/firmware.md).
- [ ] Jalankan [test-plan](test-plan.md) sampai uji apung.
- [ ] Kalibrasi `OBSTACLE_CM`, `BIN_FULL_CM`, `MOTOR_MIN_DUTY` di `config.h` kalau perlu, flash ulang.
- [ ] **Charge** 2 sel utama + 2 sel cadangan sampai penuh (4.2 V/sel).

## Hari H — bawa & lakukan

- [ ] Sel cadangan penuh, multimeter, obeng kecil (terminal block), isolasi, kabel USB + laptop (untuk flash ulang).
- [ ] HP: sambung WiFi `ARCA-Boat` (pw `arca12345`), **matikan data seluler**, buka `http://192.168.4.1/`.
- [ ] Colok baterai dengan kapal **dipegang/di darat**, tunggu UI “ARCA-Boat” (dot hijau), baru turunkan.
- [ ] Ukur tegangan **tiap sel** tiap selesai sesi (sel 1 habis lebih dulu karena ikut menanggung conveyor); charge keduanya kalau total < 7.0 V atau salah satu sel < 3.5 V.
- [ ] Cabut baterai saat tidak dipakai (conveyor selalu jalan selama baterai tercolok).

## Risiko & mitigasi

| Risiko | Mitigasi |
|---|---|
| Short kabel (tanpa sekring) | Isolasi rapi, kabel diikat jauh dari air |
| HP putus di tengah air | Failsafe 600 ms di firmware → motor stop + buzzer |
| ESP32 reset saat gas mendadak | Ramp akselerasi di firmware; kalau masih, kurangi `MOTOR_MIN_DUTY`/gas pelan |
| Sensor ngaco saat baterai lemah | L7805 dropout < ~7 V → ganti sel |
| Motor kedut saat boot | Nyalakan dengan kapal dipegang |
| Firmware final gagal compile | Kembali ke firmware breadboard tidak bisa menggerakkan L298N — perbaiki error (biasanya nama pin/lib), atau hubungi Claude dengan log error |
