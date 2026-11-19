# [Arsip] Breadboard Test Mode (LED)

> **TL;DR:** Versi firmware saat part asli belum datang: motor/sensor/buzzer digantikan LED, sensor disimulasikan acak, protokol sama dengan versi final. File asli: `ARCA-Artifacts/firmware/_arsip-breadboard-test-mode/`.

| Fungsi | Pin LED |
|---|---|
| Motor kiri maju/mundur | 18 / 19 (PWM ch 0/1) |
| Motor kanan maju/mundur | 21 / 22 (PWM ch 2/3) |
| Halangan kiri / kanan / tampungan penuh | 25 / 26 / 27 |
| Conveyor aktif | 14 |
| Buzzer | 23 |
| Ada HP terhubung | 13 |

Simulasi sensor: halangan kiri tiap 1.9 s (12%), kanan tiap 2.3 s (12%), bak penuh tiap 6 s (10%). Telemetry tiap 150 ms.
