# Cara Kerja Vault Ini (Building a Second Brain)

> **TL;DR:** Metode Tiago Forte. **CODE** = alur kerja pengetahuan (Capture → Organize → Distill → Express). **PARA** = struktur folder menurut *seberapa bisa ditindaklanjuti*. Tiap dokumen punya TL;DR di atas (progressive summarization). Output jadi ada di `ARCA-Artifacts/`.

## CODE di proyek ini

| Tahap | Artinya | Di vault ini |
|---|---|---|
| **C — Capture** | Simpan apa saja yang “beresonansi” tanpa disaring | `0_Capture/` — kronologi sesi, pertanyaan terbuka |
| **O — Organize** | Kelompokkan menurut tindakan, bukan topik | `1_Projects` · `2_Areas` · `3_Resources` · `4_Archives` |
| **D — Distill** | Saring ke inti (progressive summarization) | TL;DR di tiap dokumen; README = ringkasan seluruh proyek; decision‑log = inti keputusan |
| **E — Express** | Ubah jadi hasil nyata yang bisa dipakai/dibagikan | `ARCA-Artifacts/` — web UI, wiring diagram, firmware |

## PARA

- **Projects** — punya tujuan & deadline: *Lomba 24 Sep*, *Upgrade pasca lomba*. Selesai → pindah ke Archives.
- **Areas** — tanggung jawab berkelanjutan tanpa deadline: power, propulsi, sensor, app, firmware, hardware. Inilah “kebenaran terkini” tiap subsistem.
- **Resources** — referensi yang berguna lintas area: BOM, decision log, catatan ESP32, glosarium.
- **Archives** — versi/ide yang sudah tidak berlaku, **tidak dihapus** supaya alasan perubahan tetap terlacak.

## Progressive summarization

1. Lapisan 1 — catatan mentah (Capture).
2. Lapisan 2 — **bold** bagian penting.
3. Lapisan 3 — TL;DR per dokumen.
4. Lapisan 4 — README (ringkasan eksekutif seluruh proyek).

## Aturan merawat

- Info baru → tulis dulu di `0_Capture/`, lalu pindahkan ke Area yang tepat.
- Keputusan baru → satu baris di `decision-log.md` (tanggal, keputusan, alasan, status).
- Area berubah → perbarui TL;DR-nya; versi lama → `4_Archives/` dengan catatan “digantikan oleh …”.
- Kode & UI punya **satu sumber**: `ARCA-Artifacts/web-ui/arca-control.html` → `webpage.h` lewat script.
