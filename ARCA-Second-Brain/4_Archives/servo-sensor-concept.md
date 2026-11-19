# [Arsip] Konsep 1 HC‑SR04 di Atas Servo

> **TL;DR:** Deskripsi proyek awal: satu sensor ultrasonik diputar servo untuk memindai sekitar kapal. Diganti 4 sensor statis (2 depan, 2 bak) di plan 21 Sep; dikonfirmasi user 23 Sep.

Alasan diganti (tersirat dari plan): 4 sensor statis memberi deteksi depan kiri/kanan **dan** status bak penuh tanpa bagian bergerak, dan tidak menambah beban servo (~0.5 A puncak) ke rail 5V L7805.
