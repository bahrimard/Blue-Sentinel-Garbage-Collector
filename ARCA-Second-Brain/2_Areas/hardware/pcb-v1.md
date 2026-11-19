# PCB v1 — 1 layer, modular (Main + 4 Sensor)

> **TL;DR:** **ARCA MAIN v1** (100×79 mm, 1 pcs) + **ARCA SENSOR v1** (26×23.5 mm, 4 pcs), tembaga hanya di bawah, semua THT, 1 kabel jumper (JP1). Sensor disambung kabel 4 pin (**T E G 5V**) → posisi HC-SR04 bebas. Divider ECHO pindah ke board sensor. **Pin ESP32 PCB beda dengan versi kabel** → build env `arca-pcb`. File siap cetak & panduan lengkap: `ARCA-Artifacts/pcb/README.md`.

## Keputusan desain
| Keputusan | Alasan |
|---|---|
| 1 layer, THT, jalur ≥0.6 mm, clearance ≥0.64 mm | Bisa dicetak toko lokal atau etching sendiri |
| Main + 4 board sensor identik | Penempatan sensor fleksibel, gampang ganti kalau rusak |
| Divider 470/1k di board sensor | Kabel membawa ECHO 3.3 V → aman untuk ESP32 |
| Pin ESP32 diatur ulang (motor & buzzer di baris kiri, 4 sensor di baris kanan) | PCB 1 layer tanpa jalur silang; cukup 1 jumper |
| Konektor sensor urutan T-E-G-5V, board sensor menukar ke urutan HC-SR04 | Spine GND & 5V lurus melewati 4 konektor tanpa silang |
| Buzzer lewat header 2 pin (bukan buzzer 12 mm di board) | Buzzer 12 mm menabrak konektor US4 & modul ESP32 |
| Terminal screw: J1 baterai (MID/GND/BAT+), J2 conveyor, J3 power L298N | Semua kabel luar bisa dicabut; conveyor dari titik tengah pack |
| JP1 digambar sebagai jalur layer atas | 1 layer = kabel jumper; 2 layer = otomatis jadi tembaga |

## Pin PCB v1 (`-DARCA_PCB_V1`)
ENA 32 · IN1 33 · IN2 25 · IN3 26 · IN4 27 · ENB 14 · BUZ 13 · US1 T22/E23 · US2 T19/E21 · US3 T17/E18 · US4 T4/E16.

## Verifikasi (23 Sep)
DRC mandiri OK; import Eagle → KiCad 7 DRC: 0 short, 0 clearance, 0 unconnected (sisa: peringatan silkscreen); netlist sch = brd; Gerber dibaca ulang (gerbonara) cocok; firmware test 30/30 kedua varian. **Belum** dibuka di aplikasi Eagle asli, dicetak, atau dirakit.

## Risiko terbuka
- Jarak baris ESP32 diasumsikan **25.4 mm** — cek dengan print 1:1 sebelum cetak.
- Skematik dibuat otomatis berbasis label net (koneksi benar, tata letak sederhana).
