# Proyek: Lomba Berikutnya — Kamera FPV (+ Deteksi Sampah)

> **TL;DR:** Tambah ESP32-CAM sebagai board **terpisah** yang stream video ke HP. ESP32 utama tetap memegang motor, sensor, failsafe, dan AP `ARCA-Boat`, jadi kalau kamera bermasalah kendali tidak ikut terganggu. Format stream **MJPEG lewat HTTP** (paling kompatibel di semua browser HP). Kalau waktu cukup, tahap 2 adalah deteksi sampah yang dijalankan **di browser HP** (TensorFlow.js) dari stream yang sama.

Status: ide disepakati 3 Okt 2026 · tanggal lomba: _belum diketahui_

## Arsitektur

```
HP (browser) ──WiFi──► ESP32 utama (AP "ARCA-Boat", 192.168.4.1)
   │                     ├─ UI webpage.h + WebSocket :81 (joystick/telemetry) — TIDAK BERUBAH
   │                     └─ motor, HC-SR04, buzzer, failsafe
   └──<img> /stream────► ESP32-CAM (STA ke ARCA-Boat, IP statis 192.168.4.10)
                           └─ MJPEG http://192.168.4.10/stream (+ header CORS)
```

- ESP32-CAM tidak memakai pin ESP32 utama sama sekali (komunikasi lewat WiFi).
- UI di HP menampilkan panel video (dari `192.168.4.10`) di samping/ di belakang radar & joystick.

## Kenapa MJPEG lewat HTTP

| Opsi | Kesimpulan |
|---|---|
| **MJPEG HTTP (`multipart/x-mixed-replace`)** | ✅ Dipilih. Tampil di `<img>` di Chrome Android & Safari iOS tanpa plugin. JPEG dibuat hardware OV2640 → CPU ESP32 hampir nganggur. |
| JPEG per frame lewat WebSocket → canvas | Cadangan. Kontrol frame-drop lebih baik, tapi butuh JS tambahan. Dipakai kalau latensi MJPEG menumpuk. |
| H.264 / WebRTC / RTSP | ❌ ESP32 tidak punya encoder H.264; browser HP tidak bisa buka RTSP. |

## Setelan efisien (titik awal)

- Resolusi **QVGA 320×240** (naik ke VGA kalau sinyal bagus), `jpeg_quality` 12–15 → ±8–15 KB/frame, ±10–15 fps, ±1–1.5 Mbps.
- `fb_count = 2`, `grab_mode = CAMERA_GRAB_LATEST` → selalu kirim frame terbaru, latensi tidak menumpuk.
- Batasi fps (mis. 12) supaya airtime WiFi tersisa untuk paket kendali (failsafe 600 ms).
- Header `Access-Control-Allow-Origin: *` di `/stream` + `crossorigin="anonymous"` di `<img>` → canvas tidak "tainted", siap untuk AI di tahap 2.
- Endpoint `/capture` (1 foto JPEG) untuk dokumentasi titik sampah.
- Auto-reconnect WiFi; LED flash GPIO4 dimatikan.
- ESP32 utama: tetapkan channel AP (1/6/11 yang paling sepi), `WiFi.setSleep(false)`.

## Hardware

| Item | Catatan |
|---|---|
| ESP32-CAM AI-Thinker (OV2640, PSRAM 4 MB) + board programmer USB (ESP32-CAM-MB) | Cukup untuk streaming. Kalau belum beli dan ingin deteksi on-device: ESP32-S3 + kamera (XIAO ESP32S3 Sense / Freenove ESP32-S3 CAM). |
| **Antena eksternal U.FL** | Antena PCB bawaan lemah, apalagi di dalam lambung. Pindah resistor 0 Ω ke posisi antena eksternal. |
| **Buck LM2596 → 5 V** + elco 470–1000 µF di 5V ESP32-CAM | Penyebab gagal no.1 ESP32-CAM = brownout (puncak ±300+ mA). Jangan dari L7805. Buck yang sama bisa sekaligus dipakai untuk conveyor (kanal terpisah). |
| Kotak tahan air + jendela bening, kamera agak menunduk | Opsional: filter polarisasi untuk kurangi silau air. |

## Tahap 2 — Deteksi sampah (kalau waktu cukup)

1. **Cepat (disarankan):** AI di browser HP. Frame dari `<img>` digambar ke canvas → TensorFlow.js COCO-SSD (kelas `bottle`, `cup`) → kotak deteksi + penghitung sampah di layar. HP jauh lebih cepat dari ESP32. File model di-serve dari microSD ESP32-CAM (HP tidak punya internet saat tersambung ke AP).
2. **Lebih akurat:** model custom (botol, kantong plastik, gelas, kaleng, organik) dilatih dari foto sungai sendiri (200–500 gambar), export ke TF.js.
3. **Opsional:** mode Assist — selama tombol ditahan, kapal belok ke sampah terdekat.

Batasan: COCO-SSD tidak kenal kantong plastik; pantulan air menurunkan akurasi.

## Urutan kerja

- [ ] Beli: ESP32-CAM + MB, antena U.FL, LM2596, kotak + jendela.
- [ ] Firmware ESP32-CAM: STA → `ARCA-Boat`, IP statis `192.168.4.10`, `/stream` MJPEG + CORS, `/capture`, auto-reconnect.
- [ ] ESP32 utama: channel AP tetap, sleep off; tambah panel video di `webpage.h`.
- [ ] Uji: latensi (stopwatch di layar difoto), jangkauan di air, failsafe tidak trip saat streaming, arus 5 V.
- [ ] Tahap 2 AI.

## Risiko

| Risiko | Mitigasi |
|---|---|
| Stream memakan airtime → failsafe trip | Batasi fps/resolusi; uji khusus |
| ESP32-CAM reset (brownout) | Buck 5 V + elco besar |
| Jangkauan pendek | Antena eksternal, posisi antena di atas lambung |
| Panas di kotak tertutup | Ventilasi/heatsink kecil, fps dibatasi |
