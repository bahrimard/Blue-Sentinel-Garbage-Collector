# Glosarium

> **TL;DR:** Istilah yang sering muncul di vault ini.

| Istilah | Arti |
|---|---|
| **Differential thrust** | Belok dengan beda kecepatan motor kiri/kanan (tanpa kemudi). Kanan lebih kencang → belok kiri |
| **Dead‑reckoning** | Estimasi posisi dari kecepatan & arah yang diketahui + waktu, tanpa GPS |
| **Failsafe** | Motor otomatis berhenti kalau perintah dari HP hilang > `FAILSAFE_MS` |
| **Star ground** | Semua GND ketemu di satu titik, tidak disambung berantai |
| **Ground loop** | Dua jalur GND paralel → arus besar numpang lewat jalur sinyal |
| **Divider (pembagi tegangan)** | Dua resistor seri untuk menurunkan tegangan, mis. ECHO 5 V → 3.40 V |
| **Dropout** | Selisih minimum input–output agar regulator (L7805 ≈ 2 V) tetap stabil |
| **Brownout** | Tegangan turun sesaat → ESP32 reset |
| **Ramp** | Kenaikan PWM bertahap untuk mengurangi lonjakan arus |
| **PWM / duty** | Kecepatan motor lewat persentase waktu ON (0–255) |
| **AP (Access Point)** | ESP32 memancarkan WiFi sendiri (“ARCA-Boat”) |
| **BMS** | Modul proteksi pack baterai (over/under‑voltage, short, balancing) |
| **2S** | Dua sel seri (7.4 V nominal, 8.4 V penuh) |
| **CODE / PARA** | Metode Building a Second Brain — lihat [how-this-vault-works](how-this-vault-works.md) |
