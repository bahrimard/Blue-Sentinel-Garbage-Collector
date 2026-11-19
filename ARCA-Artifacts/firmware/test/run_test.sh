#!/usr/bin/env bash
# Uji logika firmware di PC (tanpa ESP32): hardware diganti tiruan (stubs/).
# Jalankan dari folder ARCA-Artifacts/firmware:  bash test/run_test.sh
# Butuh g++ dan ArduinoJson (otomatis diambil dari .pio/libdeps proyek setelah sekali Build PlatformIO).
set -e
cd "$(dirname "$0")"
AJ="${AJ:-../../../.pio/libdeps/esp32doit-devkit-v1/ArduinoJson/src}"
g++ -std=gnu++17 -I stubs -I ../src -I "$AJ" test.cpp -o /tmp/arca_fw_test && /tmp/arca_fw_test
g++ -std=gnu++17 -DARCA_PCB_V1 -I stubs -I ../src -I "$AJ" test.cpp -o /tmp/arca_fw_test_pcb && /tmp/arca_fw_test_pcb
