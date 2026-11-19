# ARCA-Artifacts (Express)

> **TL;DR:** Hasil jadi proyek ARCA. Dokumentasi & alasan ada di `../ARCA-Second-Brain/`.

```
ARCA-Artifacts/
├── web-ui/
│   └── arca-control.html          UI kontrol (= webpage.h). Buka di browser biasa → Mode Simulasi
├── wiring/
│   ├── arca-wiring-diagram.html   diagram sistem + tabel pin-ke-pin + aturan wajib + urutan uji (versi lomba)
│   ├── arca-wiring-diagram.svg    diagram saja (untuk print)
│   ├── arca-wiring-diagram.png    diagram saja (untuk HP)
│   └── arca-wiring-map-per-board.html  detail per-board (21 Sep) — lihat catatan
├── pcb/                           PCB v1 1 layer modular: eagle/, gerber/, print/ (PDF etching 1:1), preview/ — baca pcb/README.md
└── firmware/                      proyek PlatformIO final (env kabel + env arca-pcb)
    ├── platformio.ini
    ├── src/{main.cpp,pins.h,config.h,webpage.h}
    ├── tools/make_webpage_h.py    web-ui/arca-control.html → src/webpage.h
    ├── test/                      uji logika firmware di PC (bash test/run_test.sh) — 30/30 lulus
    └── _arsip-breadboard-test-mode/
```

**Catatan wiring map per‑board (21 Sep):** tabel interkoneksinya masih menyebut kabel “GND ref” tambahan antar board — **abaikan**; aturan terbaru: satu kabel GND per modul langsung ke STAR GND (lihat diagram versi lomba).

**Firmware belum di-compile untuk ESP32** di lingkungan Claude (toolchain tidak tersedia); logikanya sudah diuji di PC (`firmware/test`). Build & upload lewat PlatformIO di laptop; instruksi di `ARCA-Second-Brain/2_Areas/firmware/firmware.md`.

Versi online (private di claude.ai): ARCA Control, ARCA Wiring Review, ARCA Wiring Map — link di README utama vault.
