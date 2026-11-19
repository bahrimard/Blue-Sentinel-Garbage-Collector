# Catatan ESP32 (WROOM‑32) yang Relevan

> **TL;DR:** Hindari 0/2/12/15 (strapping), 6–11 (flash), 1/3 (UART). 34–39 input‑only tanpa pull‑up. 36/39 bisa glitch ~80 ns saat RF/ADC aktif. ADC2 tidak bisa `analogRead` saat WiFi aktif (output PWM tetap aman).

- **Strapping:** GPIO0, 2, 12, 15 (dan 5) memengaruhi mode boot. GPIO5 & 14 mengeluarkan sinyal saat boot → motor/sensor bisa terpicu sesaat.
- **Input‑only:** 34, 35, 36 (tercetak **VP**), 39 (tercetak **VN**) — tidak ada pull‑up/down internal. Di DevKit V1 pin 36/39 **tidak** berlabel D36/D39; urutan sisi kiri: EN, VP, VN, D34, D35, D32, D33, D25…
- **Errata 36/39:** input bisa tertarik LOW ~80 ns saat SAR ADC / RF menyala → potongan pulsa ECHO → jarak terbaca terlalu dekat. Mitigasi: `WiFi.setSleep(false)`, median filter, atau pindah ke GPIO32/33.
- **ADC2** (GPIO 0, 2, 4, 12–15, 25–27): `analogRead` tidak bisa dipakai saat WiFi aktif. Untuk ukur baterai pakai ADC1 (32–39).
- **VIN DevKit:** masuk ke AMS1117‑3.3 (dropout ~1.1 V, maks ~15 V). 2S langsung ke VIN = OK, regulator hangat.
- **Access Point default IP:** 192.168.4.1.
- **LEDC:** core 2.x `ledcSetup(ch,f,res)`+`ledcAttachPin(pin,ch)`+`ledcWrite(ch,d)`; core 3.x `ledcAttach(pin,f,res)`+`ledcWrite(pin,d)`.
