# Desain Power & Wiring — ARCA v2 (Dua Pack, Rail 12 V & 5 V)

> **TL;DR:** **Pack‑Utama 3S Li‑ion (9–12.6 V)** → BMS → sekring → saklar → **bus 12 V**. Motor & conveyor ambil langsung dari bus lewat driver rendah‑drop; **logika 5 V dari buck switching ≥ 3 A** (bukan L7805). **Pack‑CAM 1S** terpisah → proteksi → **boost 5 V ≥ 2 A** → ESP32‑CAM, **GND kedua pack tidak disambung**. Tegangan "dibagi" tanpa membuang arus karena tiap rail punya konverter sendiri yang dipasang **paralel** dari bus dan di‑rating ≥ 1.5× beban. Semua angka beban = **estimasi, ukur sebelum finalisasi**.

Pendamping: [requirements-analysis](requirements-analysis.md) · Menggantikan desain 2S di [power-system](../../2_Areas/power/power-system.md) (arsip bila disetujui).

---

## 1. Anggaran daya

### 1.1 Pack‑Utama (asumsi motor 12 V — lihat A1/A2 di analisis kebutuhan)

| Beban | Rail | Normal | Puncak | Catatan |
|---|---|---|---|---|
| 2× motor baling | 12 V (bus) | 4–6 A total | 14 A (stall) | **ukur** arus kerja & stall |
| Conveyor | 12 V (bus) *atau* 3.5 V (buck) | 0.5–1 A | 2 A macet | tergantung rating motor conveyor |
| ESP32 DevKit (WiFi) | 5 V | 0.15 A | 0.5 A | |
| 4× HC‑SR04 | 5 V | 0.06 A | 0.08 A | |
| GPS + kompas + INA226 + HX711 | 5 V/3.3 V | 0.06 A | 0.1 A | |
| Buzzer + logika driver | 5 V | 0.03 A | 0.1 A | |
| **Total sisi 5 V** | | **≈ 0.3 A** | **≈ 0.8 A** | → buck 3 A punya margin ≥ 3× |
| **Total bus 12 V** | | **≈ 5–7 A** | **≈ 15 A sesaat** | |

Arus masukan buck 5 V: `Iin = (5 V × 0.8 A) / (0.9 × 11.1 V) ≈ 0.4 A` — **lebih kecil** dari arus keluarannya (hukum kekekalan daya).

### 1.2 Pack‑CAM

| Beban | Normal | Puncak |
|---|---|---|
| ESP32‑CAM streaming WiFi (tanpa flash) | 0.18–0.26 A @5 V | 0.4–0.5 A (TX burst) |
| Anggaran desain | **0.6 A @5 V** | |

Dari baterai 1S (3.0–4.2 V), boost 88 %: `Ibat ≈ (5 × 0.5) / (0.88 × 3.0) ≈ 0.95 A` pada kondisi terburuk → modul boost harus mampu ≥ 2 A masuk/≥ 1 A keluar tanpa drop.

### 1.3 Kapasitas & durasi (estimasi)

| Pack | Konfigurasi | Energi | Durasi perkiraan |
|---|---|---|---|
| Utama | 3S3P × 3000 mAh ≈ 9 Ah | ≈ 100 Wh | **≈ 1.2–1.8 jam** (rata‑rata ≈ 5 A @ 11 V, 80 % usable) |
| CAM | 1S2P × 3000 mAh ≈ 6 Ah | ≈ 22 Wh | **≈ 6–9 jam** streaming; 1S1P ≈ 3–4 jam (cukup untuk lomba) |

Rumus: `t ≈ (Wh × 0.8) / P_rata‑rata`. Catatan transportasi: pack 3S3P 3000 mAh ≈ 99.9 Wh — tepat di batas 100 Wh maskapai; periksa aturan bila perlu terbang.

---

## 2. Pilihan baterai

| Opsi | Pro | Kontra | Putusan |
|---|---|---|---|
| **3S Li‑ion 18650 (sel high‑drain asli)** | Sel sudah dimiliki tim, energi tinggi, 9–12.6 V pas untuk motor 12 V | Perlu BMS & disiplin charge | ✅ **dipilih** |
| 4S LiFePO4 (12.8 V nominal) | Lebih aman termal, 12 V native | Lebih berat/mahal, perlu charger khusus | Alternatif bila prioritas keamanan |
| 3S LiPo | Arus besar | Paling sensitif/berbahaya, tak ada casing keras | ❌ |
| Aki SLA 12 V | Murah | Berat, boros ruang | ❌ |

Syarat sel: **merek asli** (Samsung 25R/30Q, Sony VTC, Molicel, dsb.), **seragam** merek‑kapasitas‑umur satu pack; sel palsu berlabel "9900 mAh" adalah penyebab umum kegagalan.

---

## 3. Cara membagi tegangan tanpa membuang arus

Tiga prinsip:

1. **Switching, bukan linear, untuk penurunan tegangan.** Regulator linear (L7805) membuang `(Vin − Vout) × I` jadi panas: dari 11.1 V ke 5 V pada 0.5 A = **3 W terbuang (efisiensi ≈ 45 %)**. Buck sinkron mencapai 90–95 %.
2. **Paralel dari bus, bukan berantai.** Setiap rail punya konverter sendiri langsung dari bus 12 V. Beban motor yang melonjak tidak menarik rail 5 V ke bawah, dan tiap rail punya sekringnya sendiri.
3. **Rating ≥ 1.5× beban puncak.** Konverter yang dibebani mendekati batas akan *current‑limit* — di sinilah "arus turun" yang dirasakan sebagai brownout. Beban 0.8 A → pakai buck 3 A.

```
          BUS 12 V (9–12.6 V)
             │
   ┌─────────┼─────────────┬──────────────┐
   │         │             │              │
 Driver    Driver       Buck 5 V       (Buck 3.5 V
 motor L   motor R      ≥3 A, ≥90 %     opsional → conveyor
 (12 V     (12 V        → rail 5 V       bila motor 3.5 V)
  penuh)    penuh)      ≈ 0.4 A masuk
```

**Kalau motor ternyata 6 V:** (a) buck sinkron 6 V ≥ 10 A khusus motor (paralel, rail ke‑3), atau (b) batasi duty PWM maks ≈ 50 % di firmware (murah, tapi puncak tegangan 12 V ke motor; periksa panas). Jangan memakai drop L298N sebagai "penurun tegangan".

**Ganti L298N:** pada 12 V, L298N membuang ≈ 2 V per kanal (≈ 4–6 W/kanal pada 2–3 A) dan motor hanya menerima ≈ 9–10 V. BTS7960 (MOSFET, drop < 0.2 V pada 3 A) memberikan hampir seluruh tegangan ke motor dan jauh lebih dingin.

---

## 4. Diagram distribusi daya

```
PACK-UTAMA 3S3P (BMS 3S ≥25 A)
   │ XT60 (anti-spark)
   ▼
[SEKRING UTAMA 20 A, blade 32 V] ──► [SAKLAR UTAMA / kill, ≥20 A DC] ──► BUSBAR + ─────────────┐
                                                                       BUSBAR − = STAR GND       │
                                                                                                 │
  ┌──────────────────────────────────────────────────────────────────────────────────────────────┘
  │
  ├─[F 10 A]──► BTS7960 #1 (motor kiri)   ┐ tiap driver: elco 1000 µF/25 V low-ESR + 100 nF
  ├─[F 10 A]──► BTS7960 #2 (motor kanan)  ┘ TVS SMBJ15A di bus dekat driver
  │             (motor: 100 nF di terminal + 2×100 nF ke casing, kabel twisted)
  ├─[F  3 A]──► Conveyor: MOSFET low-side logic-level (mis. IRLZ44N) + dioda flyback (SS54)
  │             — atau buck 3.5 V bila motor conveyor 3.5 V
  ├─[F  2 A]──► BUCK 5 V (≥3 A, sinkron) ──► rail 5 V ──► DevKit (pin VIN/5V), HC-SR04 ×4,
  │                                           GPS, BTS7960 VCC logika, buzzer (via BC337)
  │                                           elco 470 µF + 100 nF dekat DevKit
  └─ INA226 (shunt 5–10 mΩ di jalur + utama, sebelum cabang) → I2C ke DevKit
     Divider tegangan pack 100 kΩ/33 kΩ → ADC1 (12.6 V → ≈3.13 V) sebagai cadangan INA226
```

**Aturan ground:** semua GND kembali ke **satu busbar negatif (star)**, satu kabel per modul; tidak ada loop GND antar‑modul (aturan v1 dipertahankan). Pack‑CAM **tidak** disambung ke busbar ini.

```
PACK-CAM 1S (1–2 × 18650 paralel)
   │
   ▼
[Proteksi 1S: DW01+8205 / BMS 1S ≥3 A]──► [saklar kecil] ──► BOOST 5 V ≥2 A (efisien, tanpa riak besar)
        ▲                                                       │ elco 1000 µF/10 V + 100 nF di pin 5V ESP32‑CAM
   Charger USB‑C (TP4056 versi proteksi, ≤1 A)                  ▼
   (saklar OFF saat charge)                                    ESP32‑CAM (pin 5V & GND), antena U.FL eksternal
```

---

## 5. Daftar komponen "aman dan proper"

| # | Komponen | Spesifikasi minimum | Alasan | Catatan |
|---|---|---|---|---|
| 1 | Sel 18650 ×9 (Pack‑Utama) | ≥ 15 A kontinu, ≥ 2500 mAh, asli | arus motor & stall | satu merek/umur per pack |
| 2 | Holder/spot‑weld strip nikel 3S3P | strip ≥ 0.15 mm ×8 mm | sambungan mantap, tahan getar | holder plastik hanya untuk uji |
| 3 | BMS 3S | ≥ 25 A kontinu, balance, proteksi short | cegah over‑discharge/short | cek jenis port (satu port vs terpisah) |
| 4 | Konektor baterai | XT60 (anti‑spark XT60‑S bila ada) | 60 A, polaritas terkunci | jangan dupont untuk jalur daya |
| 5 | Sekring utama | 20 A **blade DC 32 V** + holder | proteksi hubung singkat | sekring AC‑only tidak cocok |
| 6 | Saklar utama | ≥ 20 A pada DC 12 V, tahan air (marine) | pemutus | saklar kecil 3 A akan terbakar |
| 7 | Sekring cabang | 10 A ×2, 3 A, 2 A (blade/mini) | isolasi gangguan per rail | sesuaikan setelah ukur stall |
| 8 | Busbar + / − | ≥ 30 A, terminal screw | satu titik star | beri isolasi |
| 9 | Driver motor | BTS7960 ×2 (≥ 10 A) + heatsink | drop rendah, arus cukup | atau Cytron MDD10A |
| 10 | Buck 5 V | ≥ 3 A, sinkron, input ≥ 15 V | logika | **setel 5.05 V dengan multimeter SEBELUM menyambung MCU** |
| 11 | Boost 5 V (CAM) | ≥ 2 A, input 2.7–4.2 V, efisiensi ≥ 88 % | stabil saat TX burst | hindari boost mini murah (MT3608) untuk beban puncak 0.5 A+ |
| 12 | Proteksi + charger 1S | DW01‑8205 atau BMS 1S ≥ 3 A; TP4056 USB‑C versi proteksi | keamanan sel tunggal | tak ada load‑sharing: saklar OFF saat charge |
| 13 | TVS | SMBJ15A di bus 12 V | menahan lonjakan induktif | dekat driver |
| 14 | Elco | 1000 µF/25 V low‑ESR ×2 (bus), 470 µF/10 V (5 V), 1000 µF/10 V (CAM) | peredam lonjakan | |
| 15 | Keramik 100 nF | ≥ 10 buah | decoupling, noise motor | di motor, IC, headers |
| 16 | MOSFET conveyor | logic‑level (IRLZ44N/AO3400 sesuai arus) + dioda SS54 | kontrol conveyor | gerbang 10 kΩ pull‑down |
| 17 | INA226 + shunt | shunt 5–10 mΩ ≥ 3 W *atau* modul Hall ACS758‑50A | pengukuran arus/SoC | |
| 18 | Kabel | 12 AWG bus utama; 14 AWG motor/driver; 18 AWG conveyor; 22 AWG sinyal/5 V | rugi tegangan & panas | silikon fleksibel |
| 19 | Heatshrink berperekat, ferrit | — | isolasi & noise | |
| 20 | Kotak | IP65–IP67 untuk elektronik; kotak baterai terpisah, kering | air | cable gland PG7/PG9, silica gel |
| 21 | Sensor bocor + (opsional) float switch | 3.3 V logika | alarm | dasar lambung |
| 22 | Charger Pack‑Utama | 3S balance charger atau adaptor 12.6 V CC/CV ≥ 3 A + BMS balance | pengisian | di luar robot, diawasi |
| 23 | Antena U.FL + kabel pigtail | 2.4 GHz ≥ 3 dBi | jangkauan CAM | pindahkan resistor 0 Ω antena PCB→ext |
| 24 | Pemutus fisik e‑stop | tombol jamur NC / kabel cabut | keselamatan | memutus enable driver atau bus |

> Harga tidak dicantumkan (tidak diverifikasi). Minta tim mengisi kolom biaya saat membeli.

---

## 6. Prosedur bring‑up (urutan wajib)

1. **Tanpa beban:** pack terpasang BMS, ukur tegangan tiap grup sel (selisih ≤ 0.05 V), cek polaritas dengan multimeter.
2. Sambungkan **hanya** sekring + saklar + busbar; ukur 9–12.6 V di bus.
3. Sambungkan **buck 5 V**, **setel 5.05 V** dengan multimeter (belum ada MCU).
4. Sambungkan DevKit + sensor; ukur arus idle (target ≈ 0.1–0.2 A @5 V → ≈ 0.06 A di bus).
5. Sambungkan driver **tanpa motor**, uji logika EN/PWM; lalu motor **tanpa baling** (di meja), ukur arus kerja & stall singkat → catat.
6. Baling terpasang **di air** (ember/kolam), ukur arus nyata; sesuaikan sekring cabang.
7. Pack‑CAM terpisah: uji boost 5 V tanpa kamera → lalu kamera; ukur puncak arus saat streaming (osiloskop/multimeter peak).
8. Uji failsafe/e‑stop/leak; uji pack drop (tegangan < 9.6 V → peringatan, < 9.0 V → Safe).
9. Catat hasil di `0_Capture/` (arus tiap beban, tegangan sag, suhu driver/buck).

## 7. Keselamatan operasional

- **Tidak ada kabel daya tanpa sekring** setelah busbar; tidak ada sambungan terbuka.
- Pack di kompartemen kering terpisah, di atas garis air; tahan getar; sensor suhu (NTC) pada pack bila memungkinkan.
- **Charge di luar robot**, diawasi, di atas permukaan tak mudah terbakar; jangan charge pack panas/menggembung; simpan di ≈ 3.8 V/sel.
- Cabut XT60 saat tidak dipakai; periksa insulasi & korosi tiap sesi.
- Setelah tercebur/bocor: matikan, keringkan, **jangan** dicolok sebelum diperiksa.
- Cutoff tegangan: peringatan < 9.6 V, Safe < 9.0 V (≈ 3.0 V/sel) — firmware membaca INA226/divider.
- ESP32 DevKit saat di‑USB: cabut kabel 5 V buck atau pakai dioda Schottky seri untuk menghindari umpan balik.

## 8. Yang perlu dikonfirmasi (menggeser desain)

- Rating tegangan & arus **motor baling** dan **conveyor** (pertanyaan lama).
- Jenis BMS yang tersedia (satu port vs port charge terpisah).
- Ketersediaan driver BTS7960 / buck sinkron di toko lokal (ganti dengan setara ≥ spesifikasi).
