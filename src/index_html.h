#include <Arduino.h>

#ifndef INDEX_HTML_H
#define INDEX_HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32S3 Joystick</title>
  <script src="/joystick.js"></script>
  <style>
    body { background:#121212; color:#eee; font-family:Arial; text-align:center; }
    h2 { color:#00bfff; }
    #joystick { width:220px; height:220px; margin:auto; }
    .status { margin-top:20px; font-size:18px; font-weight:bold; }
    .btn { padding:15px 25px; margin:10px; border:none; border-radius:10px; font-size:16px; cursor:pointer; }
    .btn-stop { background:#ff3b3b; color:#fff; }
    .btn-stop:hover { background:#ff0000; }
    .slider { width:200px; margin-top:20px; }
  </style>
</head>
<body>
  <h2 style="text-align:center;">ESP32S3 Robot Controller</h2>
  <div id="joystick"></div>
  <div class="status" id="status">Status: STOP</div>
  <input type="range" min="0" max="255" value="128" class="slider" id="speedSlider">
  <br>
  <button class="btn btn-stop" onclick="emergencyStop()">🛑 Emergency Stop</button>
  <script>
    var ws = new WebSocket("ws://" + location.hostname + ":81/");
    var joystick = nipplejs.create({
      zone: document.getElementById('joystick'),
      mode: 'static',
      position: {left: '50%', top: '50%'},
      color: 'blue'
    });
    joystick.on('move', function (evt, data) {
      if (data.vector) {
        let x = data.vector.x.toFixed(2);
        let y = data.vector.y.toFixed(2);
        ws.send(JSON.stringify({x:x, y:y}));
      }
    });
    joystick.on('end', function () {
      ws.send(JSON.stringify({x:0, y:0}));
    });
  </script>
</body>
</html>
)rawliteral";

#endif
