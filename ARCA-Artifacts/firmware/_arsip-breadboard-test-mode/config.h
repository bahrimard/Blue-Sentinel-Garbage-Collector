#pragma once

// ESP32 jadi Access Point sendiri — HP connect langsung ke sini,
// gak butuh router/WiFi rumah.
#define WIFI_AP_SSID       "ARCA-Boat"
#define WIFI_AP_PASSWORD   "arca12345"   // WPA2 min. 8 karakter

#define WEBSOCKET_PORT     81

#define TELEMETRY_INTERVAL_MS      150   // kirim status ke HP tiap 150ms
#define SIM_OBSTACLE_L_INTERVAL_MS 1900  // simulasi sensor, ganti ke real read nanti
#define SIM_OBSTACLE_R_INTERVAL_MS 2300
#define SIM_BIN_INTERVAL_MS        6000
