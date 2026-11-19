# [Arsip] Review Keamanan v1 (23 Sep, sebelum keputusan “versi lomba”)

> **TL;DR:** Review ideal dengan komponen tambahan. Wajib: BMS 2S, sekring 5 A, saklar, cabut jumper ENA/ENB + pull‑down 10k, failsafe. Disarankan: elco 1000 µF, 100 nF motor, pindah ECHO3/4 ke 32/33, monitor VBAT (GPIO36), hapus GND ref ganda, pull‑down/diode buzzer, kabel AWG18–20. Ditunda karena waktu → [upgrade pasca lomba](../1_Projects/upgrade-pasca-lomba/README.md).

Evolusi:
1. v1: BMS wajib.
2. Setelah tahu charge dicopot: BMS tidak wajib; pengganti = sekring + cutoff firmware + monitor sel 1 via divider 100k/100k di GPIO39.
3. User minta tanpa komponen tambahan → hanya pengaman gratis yang dipakai (jumper, grounding, isolasi, firmware, kebiasaan).

Sudah OK sejak review v1: divider ECHO 3.40 V, TRIG 3.3 V, ESP32 VIN dari VBAT, beban L7805 ~0.3 W, alokasi GPIO & star ground.
