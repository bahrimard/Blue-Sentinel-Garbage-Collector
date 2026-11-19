# Propulsi — 2 Motor Baling via L298N

> **TL;DR:** Differential thrust: kiri/kanan dikendalikan terpisah. **Jumper ENA/ENB dicabut** (PWM dari GPIO25/26), **12V‑EN tetap**, **pin 5V kosong**. L298N buang ~2–3 V → motor dapat ~4.5–5.5 V dari 2S. Kanan lebih kencang = belok kiri.

## Wiring

| ESP32 | L298N | Fungsi |
|---|---|---|
| GPIO13 / 14 | IN1 / IN2 | arah motor kiri (OUT1/OUT2) |
| GPIO16 / 17 | IN3 / IN4 | arah motor kanan (OUT3/OUT4) |
| GPIO25 | ENA (pin sinyal, setelah jumper dicabut) | PWM kiri |
| GPIO26 | ENB | PWM kanan |
| — | 12V ← VBAT, GND ← STAR | daya motor |

## Logika kendali (firmware)

- UI kirim `x,y` (−1..1). `throttle = −y`, `turn = x`, `L = clamp(throttle + turn)`, `R = clamp(throttle − turn)`.
- Nilai > deadzone 0.05 dipetakan ke duty `MOTOR_MIN_DUTY (90) … 255` karena motor kecil + drop L298N sering baru muter di ~35% duty.
- Ramp: naik maks 0.10 per 20 ms, turun/berhenti langsung.
- IN1=IN2=LOW saat nilai 0.

## Catatan & batasan

- Saat ESP32 boot (~0.5 s), ENA/ENB mengambang → motor bisa kedut. Nyalakan kapal sambil dipegang. Fix permanen: 10k pull‑down (upgrade).
- Heatsink L298N wajib terpasang, beri ventilasi.
- Motor rating 12 V akan lemah di sistem 2S — lihat [inbox](../../0_Capture/inbox-open-questions.md).
- Upgrade paling berdampak: TB6612FNG / DRV8833 (drop jauh lebih kecil).
