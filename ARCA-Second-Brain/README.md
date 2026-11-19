# ARCA — Kapal IoT Pembersih Sampah Sungai

> **Status (23 Sep 2026, malam sebelum lomba):** hardware final siap dirakit sesuai wiring diagram; firmware final sudah ditulis & lulus 30/30 uji logika di PC (belum di-compile untuk ESP32/diuji di board); UI kontrol = `webpage.h` yang di-serve ESP32. **Lomba: 24 Sep 2026 pagi.**
> Mulai dari sini → [Checklist lomba](1_Projects/lomba-2026-09-24/README.md) · [Wiring](2_Areas/hardware/perfboard-and-gpio.md) · [Firmware](2_Areas/firmware/firmware.md)

Nama folder kode lokal: `Documents/robotik/Blue Sentinel - ARCA` (PlatformIO, board `esp32doit-devkit-v1`).

---

## 1. Ide (kenapa proyek ini ada)

Sampah plastik mengambang di sungai. **ARCA** adalah kapal kecil yang **dikemudikan manual dari HP lewat WiFi**, mendorong sampah masuk ke bak lewat **conveyor**, sambil memberi tahu operator kalau ada **halangan di depan** dan kalau **bak sudah penuh**. Layar HP menampilkan **jejak navigasi** kapal (dead‑reckoning dari perintah motor — tanpa GPS/peta).

## 2. Cara kerja dalam satu gambar

```
 HP (browser)  ──WiFi "ARCA-Boat"──►  ESP32 DevKit V1
   http://192.168.4.1/  (UI webpage.h)      │
   ws://192.168.4.1:81  (joystick 10 Hz)    ├─ L298N ─► 2 motor baling (differential thrust)
   ◄── telemetry 150 ms (motor, halangan,   ├─ 4× HC‑SR04 (2 depan = halangan, 2 bak = penuh)
       bak penuh, conveyor)                  └─ BC337 ─► buzzer
 Baterai 2S 18650 ─► Board A (VBAT bus + L7805 5V) ─► semua modul;  titik tengah pack (1 sel) ─► motor conveyor (selalu ON)
```

Konvensi paling penting: **motor kanan lebih kencang = kapal belok KIRI.**

## 3. Komponen utama

ESP32 DevKit V1 · L298N · 2 motor DC + baling · 4× HC‑SR04 · buzzer + BC337 · L7805 · motor conveyor (dari titik tengah pack) · 2× 18650 (2S) · 4 perfboard. Rincian: [BOM](3_Resources/bom.md).

## 4. Plan & status per area

| Area | Keputusan inti | Status | Dokumen |
|---|---|---|---|
| Hardware / perfboard | 4 board (PWR, MCU, SNS, BUZ), star ground, GPIO final | ✅ desain final, 🔧 dirakit malam ini | [perfboard-and-gpio](2_Areas/hardware/perfboard-and-gpio.md) |
| Power | 2S tanpa BMS/sekring (versi lomba), L7805 untuk 5V, conveyor dari titik tengah pack | ✅ final | [power-system](2_Areas/power/power-system.md) |
| Propulsi | L298N, ENA/ENB PWM, jumper ENA/ENB dicabut | ✅ final | [motor-l298n](2_Areas/propulsion/motor-l298n.md) |
| Sensor | 2 depan = HALANGAN (≤40 cm, kiri/kanan independen) · 2 bak = SAMPAH (keduanya ≤~5 cm = penuh) | ✅ final | [ultrasonic-hc-sr04](2_Areas/sensing/ultrasonic-hc-sr04.md) |
| Firmware | Turunan kode breadboard: protokol sama, driver asli, failsafe 600 ms | 🟡 logika lulus 30/30 uji PC; belum compile ESP32/upload | [firmware](2_Areas/firmware/firmware.md) |
| PCB v1 | 1 layer modular: main + 4 board sensor, siap cetak (Eagle + Gerber) | 🟡 terverifikasi DRC, belum dicetak | [pcb-v1](2_Areas/hardware/pcb-v1.md) |
| App kontrol | `webpage.h` di-serve ESP32; artifact ARCA Control = salinan + simulasi | ✅ | [app-and-protocol](2_Areas/control-app/app-and-protocol.md) |

## 5. Yang sudah dilakukan (ringkas)

- Firmware **breadboard test mode** (LED menggantikan part) + UI `webpage.h` — dibuat ±20–21 Sep.
- Rencana 4 perfboard + GPIO map final + wiring per-board (21 Sep).
- Review keamanan & wiring diagram sistem, keputusan “versi lomba tanpa komponen tambahan” (23 Sep).
- Firmware **final** untuk hardware asli + artifact ARCA Control diselaraskan dengan `webpage.h` (23 Sep).

Kronologi lengkap: [session-history](0_Capture/session-history.md) · Semua keputusan + alasannya: [decision-log](3_Resources/decision-log.md).

## 6. Yang harus dilakukan

**Malam ini / sebelum lomba** → [1_Projects/lomba-2026-09-24](1_Projects/lomba-2026-09-24/README.md) (rakit, flash firmware final, urutan uji).
**Setelah lomba** → [1_Projects/upgrade-pasca-lomba](1_Projects/upgrade-pasca-lomba/README.md) (sekring, kapasitor, pull‑down, cutoff baterai, driver motor lebih efisien).
**Pertanyaan terbuka** → [0_Capture/inbox-open-questions.md](0_Capture/inbox-open-questions.md).

## 7. Output (Express) — folder `ARCA-Artifacts/` terpisah

| Output | File | Versi online (claude.ai, private) |
|---|---|---|
| Web UI kontrol | `web-ui/arca-control.html` | [ARCA Control](https://claude.ai/artifact/K1HtBQqEibAvnRwaPDPUgb) — Mode Simulasi |
| Wiring diagram + tabel koneksi + urutan uji | `wiring/arca-wiring-diagram.{html,svg,png}` | [ARCA Wiring Review](https://claude.ai/artifact/JZqtfhD5nCmcUjtJBQrLJ1) |
| Detail per‑board (21 Sep) | `wiring/arca-wiring-map-per-board.html` | [ARCA Wiring Map](https://claude.ai/artifact/MFAHK32cgztGqBZBmvmtF3) |
| Firmware final (PlatformIO) | `firmware/` (env `esp32doit-devkit-v1` = kabel, `arca-pcb` = PCB v1) | — |
| PCB v1 (Eagle, Gerber, PDF etching) | `pcb/` | — |

## 8. Cara membaca vault ini

Disusun dengan metode **Building a Second Brain (Tiago Forte)** — **CODE** (Capture → Organize → Distill → Express) dan **PARA** (Projects, Areas, Resources, Archives). Tiap dokumen dibuka dengan **TL;DR** (lapisan ringkasan tertinggi), lalu detail. Penjelasan lengkap: [how-this-vault-works](3_Resources/how-this-vault-works.md).

```
ARCA-Second-Brain/
├── README.md                 ← kamu di sini (peta proyek)
├── 0_Capture/                ← C: catatan mentah, kronologi, pertanyaan terbuka
├── 1_Projects/               ← O: pekerjaan dengan deadline (lomba, upgrade)
├── 2_Areas/                  ← O: subsistem yang terus dirawat (power, motor, sensor, app, firmware, hardware)
├── 3_Resources/              ← O: referensi (BOM, keputusan, catatan ESP32, glosarium, metode)
└── 4_Archives/               ← O: ide/versi yang sudah tidak berlaku (tetap disimpan + alasannya)
ARCA-Artifacts/               ← E: hasil jadi (web UI, wiring, firmware)
```
