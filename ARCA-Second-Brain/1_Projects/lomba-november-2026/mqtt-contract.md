# Kontrak MQTT ARCA v2 (`v1` — DRAFT)

> **TL;DR:** Semua topik di bawah `arca/<robot_id>/` (default `r01`). **Kendali & data = MQTT, video = HTTP MJPEG.** `drive` QoS 0 @10–20 Hz + failsafe 600 ms; aksi QoS 1 dengan ack; status retained + LWT; hanya pemegang **lease** yang boleh menyetir. Payload JSON ringkas. Kontrak ini sengaja versi‑an: ubah → naikkan `v`.

Rujukan: [requirements-analysis §11](requirements-analysis.md) · format v1 WebSocket: [app-and-protocol](../../2_Areas/control-app/app-and-protocol.md)

## Konvensi

- Waktu: perangkat mengirim `up` (uptime ms); **Hub memberi cap waktu** saat terima (tidak ada NTP di lapangan).
- Satuan: jarak cm, tegangan V, arus A, berat kg, sudut derajat, koordinat WGS84 desimal.
- `x,y ∈ [−1,1]`; **y negatif = maju**; kanan lebih kencang = belok kiri (sama dengan v1).
- Ukuran payload `drive`/`telemetry` ≤ 256 B.

## Topik

| Topik | Arah | QoS | Retain | Laju | Payload |
|---|---|---|---|---|---|
| `arca/r01/ctrl/status` | ctrl→ | 1 | ✔ | saat berubah | `{"online":true,"fw":"2.0.0","up":123456,"rssi":-61,"mode":"manual","rst":"POWERON"}` · **LWT:** `{"online":false}` |
| `arca/r01/ctrl/telemetry` | ctrl→ | 0 | ✘ | 5 Hz | `{"up":..,"seq":..,"mL":0.4,"mR":0.5,"obsL":false,"obsR":false,"dFL":120,"dFR":95,"bin":{"kg":1.2,"full":false},"vb":11.6,"ib":4.1,"soc":72,"gps":{"la":-6.2,"lo":106.8,"sat":9,"hd":1.2,"sp":0.6},"hdg":87,"leak":false}` |
| `arca/r01/ctrl/cmd/drive` | →ctrl | 0 | ✘ | 10–20 Hz | `{"seq":881,"x":0.1,"y":-0.7,"lease":"web-lap1"}` |
| `arca/r01/ctrl/cmd/action` | →ctrl | 1 | ✘ | event | `{"id":"a1","act":"buzzer","val":true}` · `act` ∈ `buzzer, conveyor, mode, estop, rth, reboot` |
| `arca/r01/ctrl/ack` | ctrl→ | 1 | ✘ | event | `{"id":"a1","ok":true,"err":""}` |
| `arca/r01/lease` | hub↔web | 1 | ✔ | event/1 Hz | `{"holder":"web-lap1","exp":3}` (detik tersisa; Hub memperbarui, kosong = bebas) |
| `arca/r01/cam/status` | cam→ | 1 | ✔ | saat berubah | `{"online":true,"fw":"2.0.0","ip":"192.168.4.10","res":"QVGA","fps":11,"mode":"color","rssi":-64}` · **LWT** offline |
| `arca/r01/cam/detections` | cam→ / hub→ | 0 | ✘ | 5 Hz | `{"fid":4021,"src":"color","w":320,"h":240,"objs":[{"c":"botol_plastik","p":0.82,"b":[120,88,40,56]}]}` · `src` ∈ `color, tinyml, yolo` |
| `arca/r01/cam/event` | cam/hub→ | 1 | ✘ | event | `{"id":"e77","c":"kantong_plastik","p":0.91,"b":[..],"snap":"/snap/e77.jpg","gps":{"la":..,"lo":..}}` (GPS & snap diisi Hub) |
| `arca/r01/cam/cmd` | →cam | 1 | ✘ | event | `{"res":"QVGA","fps":10,"q":12,"mode":"color\|tinyml\|stream","reboot":false}` |
| `arca/r01/label` | web→hub | 1 | ✘ | event | `{"event":"e77","ok":false,"c":"vegetasi"}` (koreksi untuk retrain) |
| `arca/r01/log` | any→ | 0 | ✘ | jarang | teks pendek |

**Video (bukan MQTT):** `http://<cam-ip>/stream` (MJPEG, header CORS `*`), snapshot `/capture`. Hub memproses salinan frame untuk YOLO dan mem‑publish `src:"yolo"` ke `cam/detections`.

## Aturan perilaku

1. **Failsafe:** ctrl tidak menerima `drive` valid dari pemegang lease ≥ 600 ms → motor 0 (tetap dengar `estop`). Putus MQTT/WiFi > 3 s → mode **Safe** (motor 0, buzzer berkala, tetap kirim telemetri bila bisa).
2. **Lease:** Hub menerbitkan `lease`; ctrl **hanya** menjalankan `drive` yang `lease`‑nya sama dengan `holder`. Web meminta lease lewat Hub (REST/WS); kedaluwarsa 3 s tanpa heartbeat `drive`.
3. **E‑stop:** `act:"estop"` diproses tanpa lease dan tanpa antre; menahan sampai `act:"mode","val":"manual"` oleh pemegang lease.
4. **Urutan:** `seq` monoton; ctrl mengabaikan `seq` ≤ terakhir (anti pesan lama).
5. **Keamanan:** broker `allow_anonymous false`; ACL per klien:

| Klien | Publish | Subscribe |
|---|---|---|
| `robot-ctrl` | `arca/+/ctrl/status`, `.../telemetry`, `.../ack`, `.../log` | `arca/+/ctrl/cmd/#`, `arca/+/lease`, `arca/+/cam/detections` |
| `robot-cam` | `arca/+/cam/status`, `.../detections`, `.../event`, `.../log` | `arca/+/cam/cmd` |
| `hub` | `arca/+/lease`, `arca/+/cam/detections` (yolo), `arca/+/cam/event` | `arca/#` |
| `web-operator` | `arca/+/ctrl/cmd/#`, `arca/+/cam/cmd`, `arca/+/label` | `arca/#` |
| `web-viewer` | — | `arca/#` |

6. **Multi‑robot:** ganti `r01`; tidak ada perubahan skema.
7. **Kompatibilitas v1:** jalur darurat AP `ws://192.168.4.1:81` tetap memakai pesan `joystick`/`buzzer`/`telemetry` v1 apa adanya.
