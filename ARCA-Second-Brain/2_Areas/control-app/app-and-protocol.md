# App Kontrol & Protokol WebSocket

> **TL;DR:** UI resmi = **`webpage.h`** di firmware, di-serve ESP32 di `http://192.168.4.1/`, WebSocket **`ws://192.168.4.1:81`** (lib links2004). HP → ESP32: `{"type":"joystick","x","y"}` tiap 100 ms + `{"type":"buzzer","state"}`. ESP32 → HP: `{"type":"telemetry",…}` tiap 150 ms. Artifact ARCA Control (claude.ai) = UI yang sama + **Mode Simulasi** (tidak bisa konek ke kapal).

## Cara pakai saat lomba

1. HP sambung WiFi **ARCA-Boat** (password `arca12345`). Matikan data seluler.
2. Buka **`http://192.168.4.1/`** (bukan link claude.ai).
3. Status kanan atas: dot hijau “ARCA-Boat” = terhubung; abu “Terputus” = reconnect otomatis tiap 2 s.

## Tampilan (webpage.h)

- **Jejak navigasi** (radar): dead‑reckoning di sisi HP dari nilai motor **telemetry** (bukan posisi joystick). `turnRate = (L − R) × 55°/s`, `speed = (L+R)/2 × 14` unit/s. HDG & JARAK = estimasi, belum dikalibrasi ke meter.
- Chip (tiap chip ada keterangan sensor + jarak cm):
  - **Halangan Kiri** — sensor depan‑kiri (US3), “Depan‑kiri · 110 cm”
  - **Halangan Kanan** — sensor depan‑kanan (US4), berdiri sendiri dari kiri
  - **Sampah (Bak)** — 2 sensor bak (US1, US2), “Bak L 24 · R 24 cm”, Penuh kalau keduanya ≤ 6 cm
  - **Conveyor** — selalu ON
- Keputusan Aman/Terdeteksi/Penuh dihitung **firmware** (flag `obsL/obsR/binFull`); UI hanya menampilkan. Jarak cm dari `distFL/FR/BL/BR` (kalau firmware lama tanpa field ini, tampil “—”).
- Bar Motor Kiri/Kanan, joystick (lepas = netral), tombol **Buzzer** (tekan‑tahan = bunyi), Reset jejak, timer berjalan.
- Indikator baterai **78% statis** (belum membaca baterai).

## Protokol

| Arah | Pesan | Keterangan |
|---|---|---|
| HP → ESP32 | `{"type":"joystick","x":-1..1,"y":-1..1}` | tiap 100 ms, **juga saat netral** (0,0) → jadi heartbeat failsafe. y negatif = maju |
| HP → ESP32 | `{"type":"buzzer","state":true\|false}` | true saat tombol ditekan, false saat dilepas |
| ESP32 → HP | `{"type":"telemetry","motorL":-1..1,"motorR":-1..1,"obsL":bool,"obsR":bool,"binFull":bool,"conveyor":true,"distFL":cm,"distFR":cm,"distBL":cm,"distBR":cm}` | tiap 150 ms; `dist*` ditampilkan di chip UI |

HTTP port 80 (`WebServer`), WebSocket port 81 (`WebSocketsServer`). Tidak ada autentikasi — cukup untuk AP tertutup ber‑password.

## Artifact ARCA Control (claude.ai)

- v3 (23 Sep) = salinan `webpage.h` + deteksi otomatis: dibuka dari ESP32 (`http:`) → konek beneran; dibuka dari tempat lain → **Mode Simulasi** (dot oranye “Simulasi”), meniru mixing joystick & `simulateSensors` firmware breadboard.
- Kenapa tidak bisa konek dari claude.ai: halaman https tidak boleh membuka `ws://` (mixed content) dan sandbox artifact memblokir WebSocket.
- Sumber tunggal: `ARCA-Artifacts/web-ui/arca-control.html` → `python3 firmware/tools/make_webpage_h.py` → `firmware/src/webpage.h`.

Riwayat: v1/v2 memakai protokol `cmd:move` rancangan sendiri → [arsip](../../4_Archives/app-protocol-v1-cmd-move.md).
