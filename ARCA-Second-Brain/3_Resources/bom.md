# Bill of Materials

> **TL;DR:** Semua yang dipakai versi lomba. Kolom “Upgrade” = tambahan pasca lomba (belum dibeli/dipasang).

| # | Komponen | Qty | Dipakai di | Catatan |
|---|---|---|---|---|
| 1 | ESP32 DevKit V1 (DOIT, WROOM‑32) | 1 | Board B | cocokkan silkscreen GPIO |
| 2 | Modul L298N | 1 | Propulsi | heatsink terpasang |
| 3 | Motor DC + baling | 2 | Propulsi | rating tegangan belum dikonfirmasi |
| 4 | HC‑SR04 | 4 | Board C | tidak tahan air |
| 5 | Resistor 470 Ω | 4 | divider ECHO (sisi sensor) | |
| 6 | Resistor 1 kΩ | 5 | 4 divider ECHO (sisi GND) + 1 basis BC337 | |
| 7 | Terminal block screw 4‑pin (KF301‑4P / KF128‑4P) | 4 | TB1–TB4 | pitch belum final |
| 8 | Transistor BC337 | 1 | Board D | |
| 9 | Buzzer 5 V | 1 | Board D | aktif (piezo) atau magnetik |
| 10 | L7805 + kapasitor 1 µF | 1 + 2 | Board A | |
| 11 | ~~Buck converter~~ | 0 | — | tidak dipakai versi lomba; conveyor dari titik tengah pack. (“BAOTER 3296” = merek trimpot di modul LM2596, bukan nama modul) |
| 12 | Motor conveyor 3.5 V | 1 | conveyor | dari titik tengah pack (3.0–4.2 V), selalu ON |
| 13 | Sel 18650 + holder 2S | 2 (+2 cadangan) | Power | ≥10 A continuous disarankan |
| 14 | Perfboard | 4 | Board A–D | |
| 15 | Pin header 2.54 mm, kabel dupont, kabel power tebal, heatshrink/isolasi | — | semua | |
| **Upgrade** | Sekring 5 A + holder, saklar ≥6 A, elco 1000 µF/16 V, keramik 100 nF (×3), elco 100 µF, resistor 10k (×3), 100k/33k/100k (divider), TB6612FNG/DRV8833, modul step-down LM2596 (conveyor 3.5 V stabil) | — | pasca lomba | lihat upgrade |
