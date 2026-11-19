# Decision Log

> **TL;DR:** Semua keputusan desain beserta alasannya, terbaru di atas. Status: ✅ berlaku · 🗄️ digantikan (lihat arsip).

| Tanggal | Keputusan | Alasan | Status |
|---|---|---|---|
| 19 Nov | **ARCA v2 (diusulkan):** 3 bidang komunikasi — MQTT (data/perintah), MJPEG HTTP (video), AP `ARCA-Boat` (darurat) | MQTT tak cocok untuk video; satu jalur gagal ≠ semua gagal. [requirements-analysis](../1_Projects/lomba-november-2026/requirements-analysis.md) | 🟡 diusulkan |
| 19 Nov | **Edge Hub lokal** (Mosquitto + YOLO + DB + web) menggantikan "AI di browser HP" | Venue tanpa internet; akurasi & fps lebih baik; ESP32‑CAM tak sanggup YOLO | 🟡 diusulkan |
| 19 Nov | **Deteksi bertingkat:** warna (ESP32‑CAM) → TinyML → YOLO (Hub) | Warna murah & bootstrap data; tetap jalan bila Hub mati | 🟡 diusulkan |
| 19 Nov | **Dua pack terpisah, GND tidak disatukan:** Pack‑CAM 1S → boost 5 V; Pack‑Utama 3S → motor langsung + buck 5 V | Isolasi noise motor; efisiensi; [power-and-wiring-design](../1_Projects/lomba-november-2026/power-and-wiring-design.md) | 🟡 diusulkan (menggantikan 2S+L7805+titik tengah) |
| 19 Nov | **Driver BTS7960 menggantikan L298N** | L298N membuang ≈2 V/kanal di 12 V | 🟡 diusulkan |
| 19 Nov | **Lease kendali** (satu penyetir aktif) + geofence + RTH + pre‑flight gate | Keselamatan & operasional | 🟡 diusulkan |
| 3 Okt | **Sensor bak US1/US2 diganti load cell + HX711** (DOUT→GPIO34, SCK→GPIO4, 3.3 V). US3/US4 halangan tetap | Data berat sampah terkumpul (kg) & batas beban kapal. Catatan: berat ≠ penuh volume — opsi 1 ultrasonik tengah bak belum diputuskan | ✅ (ide) |
| 3 Okt | **Lomba berikutnya: ESP32-CAM terpisah untuk video ke HP**, MJPEG HTTP, ESP32-CAM jadi STA di AP `ARCA-Boat` (IP 192.168.4.10). Tahap 2 (kalau sempat): deteksi sampah di browser HP (TF.js) | Kompatibel semua browser HP, JPEG hardware = efisien, kendali utama tidak terganggu kalau kamera bermasalah. Detail: [lomba-berikutnya](../1_Projects/lomba-berikutnya/README.md) | ✅ (ide) |
| 23 Sep | **PCB v1**: 1 layer, main + 4 board sensor, divider di board sensor, pin ESP32 diatur ulang (env `arca-pcb`) | Bisa dicetak toko lokal; sensor bisa ditaruh bebas | ✅ (belum dicetak) |
| 23 Sep | ECHO sensor depan dipindah: US3 → **D32**, US4 → **D33** | Pin 36/39 tercetak VP/VN (user tidak menemukan “36”); 32/33 kosong & bebas glitch | ✅ |
| 23 Sep | Conveyor dari **titik tengah pack** (1 sel 3.0–4.2 V), tanpa buck | Buck tidak ada; 3V3 ESP32 & 5V L298N terlalu lemah/berisiko | ✅ |
| 23 Sep | Ambang sensor: HALANGAN = depan ≤ 40 cm, kiri & kanan independen; SAMPAH = kedua sensor bak ≤ 6 cm (≈5 cm) | Permintaan user; +1 cm toleransi baca HC‑SR04 | ✅ (SAMPAH 🗄️ diganti load cell, 3 Okt) |
| 23 Sep | UI menampilkan jarak cm + nama sensor di tiap chip | Operator tahu sensor mana yang memicu | ✅ |
| 23 Sep | Firmware final = turunan `main.cpp` asli (WebSockets port 81, protokol `joystick`/`telemetry`) | Kode asli + `webpage.h` sudah jalan; minim risiko sehari sebelum lomba | ✅ |
| 23 Sep | Artifact ARCA Control = UI `webpage.h` + Mode Simulasi | Satu UI yang sama di HP & online; artifact https tidak bisa konek `ws://` | ✅ |
| 23 Sep | Failsafe 600 ms, motor dikunci di awal `setup()`, ramp akselerasi | Pengaman gratis pengganti komponen | ✅ |
| 23 Sep | **Versi lomba tanpa komponen tambahan** (tanpa sekring, saklar, kapasitor, pull‑down, divider baterai) | Waktu tinggal semalam | ✅ (sementara) |
| 23 Sep | GPIO tidak diubah (ECHO tetap 34/35/36/39) | Yang sudah disolder tidak dibongkar; glitch 36/39 dimitigasi software | 🗄️ diganti ECHO 32/33 |
| 23 Sep | Tanpa BMS | Sel di‑charge dicopot satu‑satu (overcharge & balance tertangani) | ✅ |
| 23 Sep | Konfigurasi sensor 4× statis, tanpa servo | Plan final 21 Sep; deskripsi proyek lama menyebut servo | ✅ |
| 23 Sep | Part lama dipertahankan (L298N, L7805) | Permintaan user | ✅ |
| 23 Sep | Review v1: BMS/sekring/saklar/pull‑down/kapasitor wajib | Keamanan ideal | 🗄️ → upgrade pasca lomba |
| 21 Sep | Protokol `cmd:move` di `/ws` (ARCA Control v1) | Dirancang tanpa melihat kode | 🗄️ tidak cocok kode asli |
| 21 Sep | Terminal block screw per sensor | Tahan getar, gampang servis | ✅ |
| 21 Sep | 4 perfboard per subsistem, star ground | Isolasi noise motor, mudah lacak/servis | ✅ |
| 21 Sep | Dead‑reckoning dihitung di HP | Tidak ada encoder/IMU | ✅ |
| ±21 Sep | ESP32 mode Access Point “ARCA-Boat”, UI di-serve ESP32 | Tidak butuh router/internet di lokasi | ✅ |
| ±21 Sep | Conveyor selalu ON via buck 3.5 V, tidak dikontrol ESP32 | Sederhana | 🗄️ buck tidak tersedia |
