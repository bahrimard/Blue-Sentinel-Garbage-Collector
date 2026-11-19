# Inbox — Pertanyaan Terbuka

> **TL;DR:** Hal yang belum pasti. Pindahkan ke dokumen Area/Decision begitu terjawab.

- [ ] **Rating tegangan motor baling** (6 V atau 12 V?) — menentukan seberapa besar efek drop ~2 V L298N. Kalau 12 V, dorongan akan lemah.
- [ ] **Arus nyata motor** — ukur di terminal 12V L298N; estimasi sekarang 2–4 A total.
- [x] Ambang sensor diputuskan user: halangan 40 cm, sampah ≈5 cm (6 cm). Tinggal cek posisi sensor bak ≥3 cm dari tumpukan maksimum.
- [ ] **Duty minimum motor mulai muter** → `MOTOR_MIN_DUTY` (default 90/255).
- [ ] **Indikator baterai 78% di UI** masih statis (hardcoded di `webpage.h`) — tidak membaca baterai asli. Perlu divider + ADC (lihat upgrade).
- [ ] **HDG/JARAK di UI** adalah estimasi skala simulasi (`speed = throttle × 14`), belum dikalibrasi ke meter nyata.
- [ ] **Jarak baris ESP32 DevKit** (25.4 vs 22.86 mm) — wajib dicek dengan print 1:1 sebelum PCB dicetak.
- [ ] Varian board: cocokkan penomoran GPIO dengan silkscreen DevKit yang dipakai.
- [ ] Pitch terminal block sensor (5.08 vs 2.54 mm).
- [ ] **Tanggal lomba November 2026** & kriteria penilaian juri (teknis / dampak / demo)?
- [ ] **Rating tegangan & arus conveyor** (12 V atau 3.5 V?) — menentukan MOSFET langsung vs buck 3.5 V.
- [ ] **Anggaran:** ESP32‑S3‑CAM, GPS, BTS7960, antena eksternal, sel 18650 high‑drain asli ×9.
- [ ] **Edge Hub:** laptop siapa, spesifikasi, ada GPU?
- [ ] **Area uji** (kolam/danau/sungai arus) & ada internet atau tidak di lokasi?
- [ ] **Audit GPIO v2** (≈22/25 pin terpakai) — apakah perlu I/O expander?
- [ ] Jenis **BMS 3S** yang tersedia (satu port vs port charge terpisah).
