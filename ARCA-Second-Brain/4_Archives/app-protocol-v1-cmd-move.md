# [Arsip] ARCA Control v1/v2 & Protokol `cmd:move`

> **TL;DR:** Dirancang 21 Sep tanpa melihat kode lokal: WebSocket `/ws` (port 80), `{"cmd":"move","left":±255,"right":±255}`, `stop`, `buzzer{on}`, `ping/pong`, telemetry `sensors{frontL,…}` dalam cm. **Tidak kompatibel** dengan firmware asli (port 81, `type:joystick`). Digantikan 23 Sep oleh UI `webpage.h`.

Temuan saat diarsipkan (23 Sep):
- v1 ping tiap 2 s dan `move` hanya dikirim saat joystick bergerak → tidak cocok dengan failsafe.
- v1 jejak navigasi **terbalik** (motor kanan lebih kencang digambar belok kanan). Diperbaiki di v2 sebelum diganti.
- Artifact di claude.ai (https) tidak bisa membuka `ws://` ke ESP32 → hanya berguna sebagai demo.

Ide yang layak dibawa ke masa depan: tampilan jarak sensor dalam cm, indikator latensi, pengaturan kecepatan maks & sensitivitas belok, kalibrasi dead‑reckoning.
