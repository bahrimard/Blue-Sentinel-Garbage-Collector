# CLAUDE.md — ARCA (Blue Sentinel Garbage Collector)

Robot pembersih sampah perairan berbasis ESP32 (PlatformIO, Arduino). Repo: `bahrimard/Blue-Sentinel-Garbage-Collector`. Bahasa dokumen: **Indonesia**.

## Aturan git (penting)
- **Satu branch per lomba**, dibuat dari branch lomba sebelumnya (bukan PR ke `Main`; `Main` = "Init commit" saja). Aktif sekarang: `lomba-robotik-november-2026`. Lainnya: `lomba-robotik-september-2026`.
- Nama branch tanpa spasi (kebab-case). Identitas commit sudah diset **lokal repo ini**; jangan ubah global.
- **Commit/push hanya bila user minta.** Jangan commit `*.zip`, `platformio.ini.bak`, `.pio/`, rahasia (WiFi/MQTT password → `secrets.h` yang di-gitignore).
- Remote SSH sudah dipercaya (host key GitHub tercatat).

## Cara membaca konteks hemat token
1. `ARCA-Second-Brain/README.md` = peta seluruh proyek (mulai di sini).
2. Proyek aktif: `ARCA-Second-Brain/1_Projects/lomba-november-2026/README.md` → tabel "baca urutan ini" menunjuk bagian dokumen mana yang perlu dibuka.
3. Tiap dokumen vault diawali **TL;DR** — cukup baca itu dulu; buka isi hanya bila perlu.
4. Keputusan & alasan: `3_Resources/decision-log.md`. Pertanyaan terbuka: `0_Capture/inbox-open-questions.md`.
5. **Jangan baca** kecuali diminta: `*.zip`, `.pio/`, `ARCA-Artifacts/pcb/**` (biner/Gerber), `*.png/*.pdf`, `src/webpage.h` (HTML ter-embed, besar).

## Struktur
- `src/` firmware DevKit (v1: AP `ARCA-Boat`, WebSocket :81, `config.h` `pins.h` `webpage.h` `main.cpp`). `platformio.ini` env `esp32doit-devkit-v1`.
- `ARCA-Artifacts/` hasil jadi (web-ui, wiring, firmware turunan + test PC, PCB). UI sumber tunggal: `web-ui/arca-control.html` → `firmware/tools/make_webpage_h.py` → `webpage.h`.
- `ARCA-Second-Brain/` vault PARA (0_Capture, 1_Projects, 2_Areas, 3_Resources, 4_Archives).

## Konvensi teknis yang tidak boleh dilanggar
- Motor **kanan lebih kencang = belok kiri**. y negatif = maju. Arah salah → tukar kabel motor, bukan kode.
- Jangan pakai GPIO 0/1/2/3/6–12/15 untuk I/O umum; 34–39 input-only; ADC2 tak bisa `analogRead` saat WiFi aktif.
- Failsafe 600 ms tanpa perintah → motor 0; motor dikunci di awal `setup()`. Kegagalan kamera tidak boleh mengganggu kendali.
- Video **bukan** lewat MQTT; MQTT untuk data/perintah (kontrak: `lomba-november-2026/mqtt-contract.md`).
- Angka arus/baterai di dokumen = **estimasi** sampai diukur; tandai jelas bila belum terverifikasi.
- Ambang: halangan ≤ 40 cm (kiri/kanan independen); bak penuh sesuai sensor aktif.

## Saat bekerja
- Info baru → tulis ke `0_Capture/` dulu, lalu pindahkan ke Area; keputusan → 1 baris di decision-log (tanggal, keputusan, alasan, status); dokumen usang → `4_Archives/` dengan alasan.
- Build: `pio run` (lokal PlatformIO). Belum ada firmware v2; kode v1 sudah lulus uji logika PC, belum teruji di board.
