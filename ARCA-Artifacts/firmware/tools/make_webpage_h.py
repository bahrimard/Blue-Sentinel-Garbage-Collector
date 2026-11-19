#!/usr/bin/env python3
"""Bungkus web-ui/arca-control.html jadi firmware/src/webpage.h.
Jalankan dari folder ARCA-Artifacts:  python3 firmware/tools/make_webpage_h.py
"""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
html = (root / "web-ui" / "arca-control.html").read_text(encoding="utf-8")
if ')ARCAPAGE"' in html:
    raise SystemExit('HTML mengandung delimiter )ARCAPAGE" — ganti delimiter di script ini.')
header = """#pragma once

// ============================================================
// Halaman web kontrol ARCA — di-embed langsung ke firmware &
// di-serve oleh ESP32 (HTTP server port 80), supaya HP tinggal
// connect ke WiFi "ARCA-Boat" lalu buka browser ke IP ESP32
// (default 192.168.4.1) tanpa perlu hosting eksternal apapun.
//
// AUTO-GENERATED dari ARCA-Artifacts/web-ui/arca-control.html
// (python3 firmware/tools/make_webpage_h.py). Edit HTML-nya, bukan file ini.
// ============================================================

const char INDEX_HTML[] PROGMEM = R"ARCAPAGE(
"""
out = root / "firmware" / "src" / "webpage.h"
out.write_text(header + html + '\n)ARCAPAGE";\n', encoding="utf-8")
print(f"OK: {out} ({len(html)} byte HTML)")
