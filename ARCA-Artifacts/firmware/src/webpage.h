#pragma once

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
<!DOCTYPE html>
<html lang="id">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=no">
<title>ARCA — Kontrol Navigasi</title>
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Space+Grotesk:wght@400;500;600;700&family=JetBrains+Mono:wght@400;500;600&display=swap" rel="stylesheet">
<style>
  :root {
    --bg: #0A1620;
    --panel: #101E2B;
    --panel-raised: #16283A;
    --line: #1E3346;
    --teal: #35C9C1;
    --teal-dim: #1E5E5A;
    --amber: #F2A35A;
    --red: #E8604C;
    --text: #E7F1F1;
    --text-dim: #6E8B99;
    --text-faint: #3E5768;
    --font-ui: 'Space Grotesk', system-ui, -apple-system, sans-serif;
    --font-mono: 'JetBrains Mono', 'SF Mono', ui-monospace, monospace;
  }

  * { box-sizing: border-box; margin: 0; padding: 0; -webkit-tap-highlight-color: transparent; }

  html, body {
    background: var(--bg);
    color: var(--text);
    font-family: var(--font-ui);
    height: 100%;
    overflow: hidden;
    overscroll-behavior: none;
    user-select: none;
  }

  body {
    display: flex;
    justify-content: center;
    align-items: stretch;
  }

  .app {
    width: 100%;
    max-width: 480px;
    height: 100vh;
    height: 100dvh;
    display: flex;
    flex-direction: column;
    background:
      radial-gradient(ellipse 120% 60% at 50% 0%, rgba(53,201,193,0.06), transparent 60%),
      var(--bg);
  }

  /* ---------- Status bar ---------- */
  .statusbar {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 14px 18px 10px;
    flex-shrink: 0;
  }

  .brand {
    display: flex;
    flex-direction: column;
    gap: 2px;
  }

  .brand .name {
    font-weight: 700;
    font-size: 15px;
    letter-spacing: 0.02em;
  }

  .brand .sub {
    font-size: 11px;
    color: var(--text-dim);
    font-family: var(--font-mono);
  }

  .status-items {
    display: flex;
    align-items: center;
    gap: 14px;
    font-family: var(--font-mono);
    font-size: 12px;
    color: var(--text-dim);
  }

  .status-item {
    display: flex;
    align-items: center;
    gap: 5px;
  }

  .dot {
    width: 7px;
    height: 7px;
    border-radius: 50%;
    background: var(--teal);
    box-shadow: 0 0 8px var(--teal);
  }
  .dot.off { background: var(--text-faint); box-shadow: none; }
  .dot.sim { background: var(--amber); box-shadow: 0 0 8px var(--amber); }

  .battery-icon {
    width: 20px;
    height: 10px;
    border: 1.5px solid var(--text-dim);
    border-radius: 2px;
    position: relative;
    padding: 1.5px;
  }
  .battery-icon::after {
    content: '';
    position: absolute;
    right: -3px;
    top: 3px;
    width: 2px;
    height: 4px;
    background: var(--text-dim);
    border-radius: 0 1px 1px 0;
  }
  .battery-fill {
    height: 100%;
    width: 78%;
    background: var(--teal);
    border-radius: 0.5px;
  }

  /* ---------- Nav display ---------- */
  .nav-wrap {
    flex: 1;
    position: relative;
    margin: 6px 14px;
    border-radius: 20px;
    background: var(--panel);
    border: 1px solid var(--line);
    overflow: hidden;
    min-height: 0;
  }

  .nav-header {
    position: absolute;
    top: 14px;
    left: 16px;
    right: 16px;
    display: flex;
    justify-content: space-between;
    z-index: 3;
    pointer-events: none;
  }

  .nav-label {
    font-size: 11px;
    letter-spacing: 0.04em;
    color: var(--text-dim);
  }

  .nav-readout {
    text-align: right;
    font-family: var(--font-mono);
    font-size: 11px;
    color: var(--text-dim);
    line-height: 1.5;
  }
  .nav-readout b { color: var(--teal); font-weight: 600; }

  canvas#radar {
    display: block;
    width: 100%;
    height: 100%;
  }

  .reset-track {
    position: absolute;
    bottom: 14px;
    right: 14px;
    z-index: 3;
    background: var(--panel-raised);
    border: 1px solid var(--line);
    color: var(--text-dim);
    font-family: var(--font-ui);
    font-size: 11px;
    padding: 7px 12px;
    border-radius: 20px;
    display: flex;
    align-items: center;
    gap: 6px;
    cursor: pointer;
  }
  .reset-track:active { background: var(--line); }

  /* ---------- Alert row ---------- */
  .alert-row {
    margin: 10px 14px 0;
    display: grid;
    grid-template-columns: minmax(0, 1fr) minmax(0, 1fr);
    gap: 8px;
    flex-shrink: 0;
  }

  .alert-chip {
    background: var(--panel);
    border: 1px solid var(--line);
    border-radius: 14px;
    padding: 10px 14px;
    display: flex;
    align-items: center;
    gap: 10px;
    transition: border-color 0.2s, background 0.2s;
    min-width: 0;
  }

  .alert-chip .icon {
    width: 30px;
    height: 30px;
    border-radius: 9px;
    background: var(--teal-dim);
    display: flex;
    align-items: center;
    justify-content: center;
    flex-shrink: 0;
    transition: background 0.2s;
  }

  .alert-chip .icon svg { width: 16px; height: 16px; }

  .alert-chip .txt { display: flex; flex-direction: column; gap: 1px; min-width: 0; }
  .alert-chip .txt .k { font-size: 10px; color: var(--text-dim); letter-spacing: 0.03em; }
  .alert-chip .txt .v { font-size: 13px; font-weight: 600; font-family: var(--font-mono); }
  .alert-chip .txt .s { font-size: 9.5px; color: var(--text-faint); font-family: var(--font-mono); white-space: nowrap; overflow: hidden; text-overflow: ellipsis; }
  .alert-chip.warn .txt .s { color: var(--text-dim); }

  .alert-chip.warn {
    border-color: rgba(242,163,90,0.4);
    background: rgba(242,163,90,0.06);
  }
  .alert-chip.warn .icon { background: rgba(242,163,90,0.2); }
  .alert-chip.warn .v { color: var(--amber); }

  /* ---------- Control pad ---------- */
  .controls {
    flex-shrink: 0;
    padding: 18px 20px calc(18px + env(safe-area-inset-bottom));
    display: flex;
    align-items: center;
    justify-content: space-between;
    gap: 16px;
  }

  .throttle-info {
    display: flex;
    flex-direction: column;
    gap: 10px;
    width: 72px;
  }

  .motor-readout {
    display: flex;
    flex-direction: column;
    gap: 3px;
  }
  .motor-readout .lbl {
    font-size: 9px;
    color: var(--text-faint);
    letter-spacing: 0.05em;
  }
  .motor-bar {
    height: 4px;
    background: var(--line);
    border-radius: 2px;
    overflow: hidden;
    position: relative;
  }
  .motor-bar-fill {
    position: absolute;
    height: 100%;
    background: var(--teal);
    border-radius: 2px;
    left: 50%;
    transition: none;
  }

  .stick-zone {
    width: 168px;
    height: 168px;
    border-radius: 50%;
    background: var(--panel);
    border: 1px solid var(--line);
    position: relative;
    flex-shrink: 0;
    touch-action: none;
  }

  .stick-zone::before {
    content: '';
    position: absolute;
    inset: 14px;
    border-radius: 50%;
    border: 1px dashed var(--line);
  }

  .stick-arrows {
    position: absolute;
    inset: 0;
    color: var(--text-faint);
  }
  .stick-arrows svg { position: absolute; width: 14px; height: 14px; }
  .arrow-up { top: 10px; left: 50%; transform: translateX(-50%); }
  .arrow-down { bottom: 10px; left: 50%; transform: translateX(-50%) rotate(180deg); }
  .arrow-left { left: 10px; top: 50%; transform: translateY(-50%) rotate(-90deg); }
  .arrow-right { right: 10px; top: 50%; transform: translateY(-50%) rotate(90deg); }

  .stick-knob {
    position: absolute;
    width: 60px;
    height: 60px;
    border-radius: 50%;
    background: linear-gradient(155deg, #3FDDD3, #1E9691);
    left: 50%;
    top: 50%;
    transform: translate(-50%, -50%);
    box-shadow: 0 4px 16px rgba(53,201,193,0.35), inset 0 1px 1px rgba(255,255,255,0.3);
    display: flex;
    align-items: center;
    justify-content: center;
  }
  .stick-knob svg { width: 20px; height: 20px; opacity: 0.85; }

  .buzzer-btn {
    width: 72px;
    display: flex;
    flex-direction: column;
    align-items: center;
    gap: 8px;
  }

  .buzzer-circle {
    width: 52px;
    height: 52px;
    border-radius: 50%;
    background: var(--panel);
    border: 1px solid var(--line);
    display: flex;
    align-items: center;
    justify-content: center;
    cursor: pointer;
    transition: background 0.15s, border-color 0.15s;
  }
  .buzzer-circle:active { background: var(--panel-raised); }
  .buzzer-circle svg { width: 22px; height: 22px; color: var(--text-dim); }
  .buzzer-lbl { font-size: 9px; color: var(--text-faint); letter-spacing: 0.05em; text-align: center; }

  @media (max-height: 640px) {
    .nav-wrap { margin: 4px 12px; border-radius: 16px; }
    .controls { padding: 12px 16px calc(12px + env(safe-area-inset-bottom)); }
    .stick-zone { width: 140px; height: 140px; }
    .stick-knob { width: 50px; height: 50px; }
  }
</style>
</head>
<body>

<div class="app">

  <div class="statusbar">
    <div class="brand">
      <div class="name">ARCA</div>
      <div class="sub" id="runTimer">00:00 BERJALAN</div>
    </div>
    <div class="status-items">
      <div class="status-item">
        <span class="dot off" id="wifiDot"></span>
        <span id="wifiLabel">Menghubungkan…</span>
      </div>
      <div class="status-item">
        <span class="battery-icon"><span class="battery-fill"></span></span>
        <span>78%</span>
      </div>
    </div>
  </div>

  <div class="nav-wrap">
    <div class="nav-header">
      <span class="nav-label">JEJAK NAVIGASI</span>
      <div class="nav-readout">
        HDG <b id="hdgVal">000°</b><br>
        JARAK <b id="distVal">0.0 m</b>
      </div>
    </div>
    <canvas id="radar"></canvas>
    <button class="reset-track" id="resetBtn">
      <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" width="12" height="12"><path d="M3 12a9 9 0 1 0 3-6.7M3 4v5h5"/></svg>
      Reset jejak
    </button>
  </div>

  <div class="alert-row">
    <div class="alert-chip" id="obsLChip">
      <div class="icon">
        <svg viewBox="0 0 24 24" fill="none" stroke="var(--teal)" stroke-width="2"><path d="M12 3v6m0 0l7 7-3 3-4-4-4 4-3-3 7-7z"/></svg>
      </div>
      <div class="txt">
        <span class="k">HALANGAN KIRI</span>
        <span class="v" id="obsLVal">Aman</span>
        <span class="s" id="obsLSub">Depan-kiri · — cm</span>
      </div>
    </div>
    <div class="alert-chip" id="obsRChip">
      <div class="icon">
        <svg viewBox="0 0 24 24" fill="none" stroke="var(--teal)" stroke-width="2"><path d="M12 3v6m0 0l7 7-3 3-4-4-4 4-3-3 7-7z"/></svg>
      </div>
      <div class="txt">
        <span class="k">HALANGAN KANAN</span>
        <span class="v" id="obsRVal">Aman</span>
        <span class="s" id="obsRSub">Depan-kanan · — cm</span>
      </div>
    </div>
    <div class="alert-chip" id="binChip">
      <div class="icon">
        <svg viewBox="0 0 24 24" fill="none" stroke="var(--teal)" stroke-width="2"><path d="M4 7h16M9 7V4h6v3M6 7l1 13h10l1-13"/></svg>
      </div>
      <div class="txt">
        <span class="k">SAMPAH (BAK)</span>
        <span class="v" id="binVal">Kosong</span>
        <span class="s" id="binSub">Bak L — · R — cm</span>
      </div>
    </div>
    <div class="alert-chip" id="convChip">
      <div class="icon">
        <svg viewBox="0 0 24 24" fill="none" stroke="var(--teal)" stroke-width="2"><path d="M4 8h12a3 3 0 010 6H8M4 8l3-3M4 8l3 3M20 16H8a3 3 0 01-3-3"/></svg>
      </div>
      <div class="txt">
        <span class="k">CONVEYOR</span>
        <span class="v" id="convVal">Aktif</span>
        <span class="s">Selalu ON</span>
      </div>
    </div>
  </div>

  <div class="controls">
    <div class="throttle-info">
      <div class="motor-readout">
        <span class="lbl">MOTOR KIRI</span>
        <div class="motor-bar"><div class="motor-bar-fill" id="motorL"></div></div>
      </div>
      <div class="motor-readout">
        <span class="lbl">MOTOR KANAN</span>
        <div class="motor-bar"><div class="motor-bar-fill" id="motorR"></div></div>
      </div>
    </div>

    <div class="stick-zone" id="stickZone">
      <div class="stick-arrows">
        <svg class="arrow-up" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M12 4l-6 8h12z"/></svg>
        <svg class="arrow-down" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M12 4l-6 8h12z"/></svg>
        <svg class="arrow-left" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M12 4l-6 8h12z"/></svg>
        <svg class="arrow-right" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M12 4l-6 8h12z"/></svg>
      </div>
      <div class="stick-knob" id="stickKnob">
        <svg viewBox="0 0 24 24" fill="none" stroke="#04231F" stroke-width="2.5"><path d="M12 2v20M2 12h20"/></svg>
      </div>
    </div>

    <div class="buzzer-btn">
      <div class="buzzer-circle" id="buzzerBtn">
        <svg viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><path d="M10 8a2 2 0 114 0c0 3 2 4 2 6H8c0-2 2-3 2-6z"/><path d="M9 18a3 3 0 006 0"/></svg>
      </div>
      <span class="buzzer-lbl">BUZZER</span>
    </div>
  </div>

</div>

<script>
(function(){
  // ---------- Canvas / radar trail ----------
  const canvas = document.getElementById('radar');
  const ctx = canvas.getContext('2d');
  let W, H, DPR;

  function resize() {
    DPR = Math.min(window.devicePixelRatio || 1, 2);
    W = canvas.clientWidth;
    H = canvas.clientHeight;
    canvas.width = W * DPR;
    canvas.height = H * DPR;
    ctx.setTransform(DPR, 0, 0, DPR, 0, 0);
  }
  window.addEventListener('resize', resize);

  // Boat state (dead-reckoning simulation)
  let boat = { x: 0, y: 0, heading: 0 }; // heading in degrees, 0 = up
  let trail = [{x:0, y:0}];
  let totalDist = 0;
  const MAX_TRAIL = 400;
  let obsLActive = false, obsRActive = false;

  // camera offset (boat stays centered, world scrolls)
  let scale = 6; // px per simulated meter, adjusts as trail grows

  function worldToScreen(px, py) {
    const cx = W/2, cy = H/2;
    return {
      x: cx + (px - boat.x) * scale,
      y: cy + (py - boat.y) * scale
    };
  }

  function drawGrid() {
    ctx.save();
    ctx.strokeStyle = 'rgba(53,201,193,0.06)';
    ctx.lineWidth = 1;
    const spacing = scale * 5;
    const offX = ((W/2 - boat.x*scale) % spacing + spacing) % spacing;
    const offY = ((H/2 - boat.y*scale) % spacing + spacing) % spacing;
    for (let x = offX; x < W; x += spacing) {
      ctx.beginPath(); ctx.moveTo(x, 0); ctx.lineTo(x, H); ctx.stroke();
    }
    for (let y = offY; y < H; y += spacing) {
      ctx.beginPath(); ctx.moveTo(0, y); ctx.lineTo(W, y); ctx.stroke();
    }
    ctx.restore();
  }

  function drawRings() {
    ctx.save();
    ctx.strokeStyle = 'rgba(110,139,153,0.15)';
    ctx.lineWidth = 1;
    const cx = W/2, cy = H/2;
    for (let r = 1; r <= 3; r++) {
      ctx.beginPath();
      ctx.arc(cx, cy, r * Math.min(W,H) * 0.14, 0, Math.PI*2);
      ctx.stroke();
    }
    ctx.restore();
  }

  function drawTrail() {
    if (trail.length < 2) return;
    ctx.save();
    ctx.lineJoin = 'round';
    ctx.lineCap = 'round';
    for (let i = 1; i < trail.length; i++) {
      const p0 = worldToScreen(trail[i-1].x, trail[i-1].y);
      const p1 = worldToScreen(trail[i].x, trail[i].y);
      const age = i / trail.length; // 0 old -> 1 new
      ctx.strokeStyle = `rgba(53,201,193,${0.08 + age*0.55})`;
      ctx.lineWidth = 2.5;
      ctx.beginPath();
      ctx.moveTo(p0.x, p0.y);
      ctx.lineTo(p1.x, p1.y);
      ctx.stroke();
    }
    ctx.restore();
  }

  function drawBoat() {
    const cx = W/2, cy = H/2;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(boat.heading * Math.PI / 180);

    // glow
    const grad = ctx.createRadialGradient(0,0,0, 0,0,26);
    grad.addColorStop(0, 'rgba(53,201,193,0.35)');
    grad.addColorStop(1, 'rgba(53,201,193,0)');
    ctx.fillStyle = grad;
    ctx.beginPath();
    ctx.arc(0,0,26,0,Math.PI*2);
    ctx.fill();

    // boat triangle marker
    ctx.fillStyle = '#35C9C1';
    ctx.beginPath();
    ctx.moveTo(0, -10);
    ctx.lineTo(7, 8);
    ctx.lineTo(0, 4);
    ctx.lineTo(-7, 8);
    ctx.closePath();
    ctx.fill();

    ctx.restore();
  }

  function drawObstacleMarkers() {
    if (!obsLActive && !obsRActive) return;
    const cx = W/2, cy = H/2;
    ctx.save();
    ctx.translate(cx, cy);
    ctx.rotate(boat.heading * Math.PI / 180);
    const spots = [];
    if (obsLActive) spots.push(-11);
    if (obsRActive) spots.push(11);
    spots.forEach(dx => {
      const grad = ctx.createRadialGradient(dx, -22, 0, dx, -22, 11);
      grad.addColorStop(0, 'rgba(232,96,76,0.55)');
      grad.addColorStop(1, 'rgba(232,96,76,0)');
      ctx.fillStyle = grad;
      ctx.beginPath();
      ctx.arc(dx, -22, 11, 0, Math.PI*2);
      ctx.fill();

      ctx.fillStyle = '#E8604C';
      ctx.beginPath();
      ctx.arc(dx, -22, 3.5, 0, Math.PI*2);
      ctx.fill();
    });
    ctx.restore();
  }

  function render() {
    ctx.clearRect(0,0,W,H);
    drawGrid();
    drawRings();
    drawTrail();
    drawBoat();
    drawObstacleMarkers();
  }

  // ---------- Joystick control ----------
  const stickZone = document.getElementById('stickZone');
  const stickKnob = document.getElementById('stickKnob');
  let dragging = false;
  let vec = { x: 0, y: 0 }; // -1..1, y negative = forward

  function setKnob(dx, dy) {
    const maxR = stickZone.clientWidth/2 - 30;
    let dist = Math.hypot(dx, dy);
    if (dist > maxR) { dx = dx/dist*maxR; dy = dy/dist*maxR; dist = maxR; }
    stickKnob.style.transform = `translate(calc(-50% + ${dx}px), calc(-50% + ${dy}px))`;
    vec.x = dx / maxR;
    vec.y = dy / maxR;
  }

  function resetKnob() {
    stickKnob.style.transform = 'translate(-50%, -50%)';
    vec.x = 0; vec.y = 0;
  }

  function pointFromEvent(e) {
    const rect = stickZone.getBoundingClientRect();
    const p = e.touches ? e.touches[0] : e;
    return { x: p.clientX - (rect.left + rect.width/2), y: p.clientY - (rect.top + rect.height/2) };
  }

  stickZone.addEventListener('pointerdown', (e) => {
    dragging = true;
    stickZone.setPointerCapture(e.pointerId);
    const p = pointFromEvent(e);
    setKnob(p.x, p.y);
  });
  stickZone.addEventListener('pointermove', (e) => {
    if (!dragging) return;
    const p = pointFromEvent(e);
    setKnob(p.x, p.y);
  });
  ['pointerup','pointercancel','pointerleave'].forEach(evt => {
    stickZone.addEventListener(evt, () => { dragging = false; resetKnob(); });
  });

  // Kirim posisi joystick ke ESP32 terus-menerus (10Hz) — kalau lagi
  // gak disentuh, vec.x/vec.y otomatis 0 (netral/berhenti).
  setInterval(() => {
    sendCmd({ type: 'joystick', x: vec.x, y: vec.y });
  }, 100);

  // ---------- Buzzer button ----------
  const buzzerBtn = document.getElementById('buzzerBtn');
  function setBuzzerVisual(on) {
    buzzerBtn.style.background = on ? 'rgba(242,163,90,0.18)' : '';
    buzzerBtn.style.borderColor = on ? 'rgba(242,163,90,0.5)' : '';
    buzzerBtn.querySelector('svg').style.color = on ? '#F2A35A' : '';
  }
  buzzerBtn.addEventListener('pointerdown', () => {
    setBuzzerVisual(true);
    sendCmd({ type: 'buzzer', state: true });
  });
  ['pointerup','pointercancel','pointerleave'].forEach(evt => {
    buzzerBtn.addEventListener(evt, () => {
      setBuzzerVisual(false);
      sendCmd({ type: 'buzzer', state: false });
    });
  });

  // ---------- Elemen DOM & koneksi WebSocket ke ESP32 ----------
  const hdgVal = document.getElementById('hdgVal');
  const distVal = document.getElementById('distVal');
  const motorLBar = document.getElementById('motorL');
  const motorRBar = document.getElementById('motorR');
  const runTimer = document.getElementById('runTimer');
  const wifiDot = document.getElementById('wifiDot');
  const wifiLabel = document.getElementById('wifiLabel');
  const obsLChip = document.getElementById('obsLChip');
  const obsLVal = document.getElementById('obsLVal');
  const obsRChip = document.getElementById('obsRChip');
  const obsRVal = document.getElementById('obsRVal');
  const binChip = document.getElementById('binChip');
  const binVal = document.getElementById('binVal');
  const convVal = document.getElementById('convVal');
  const obsLSub = document.getElementById('obsLSub');
  const obsRSub = document.getElementById('obsRSub');
  const binSub = document.getElementById('binSub');

  // Default IP ESP32 waktu mode Access Point (WiFi.softAP di firmware).
  // Kalau nanti ESP32 dipindah ke mode Station (connect ke WiFi rumah),
  // ganti IP ini sesuai yang muncul di Serial Monitor.
  const WS_URL = 'ws://' + location.hostname + ':81';

  // Dibuka dari ESP32 (http://192.168.4.1/) → konek WebSocket beneran.
  // Dibuka dari tempat lain (mis. artifact claude.ai via https) → Mode Simulasi:
  // browser memblokir ws:// dari halaman https, jadi telemetry dibuat lokal
  // dengan logika yang sama seperti firmware (mixing joystick + simulateSensors).
  const ON_DEVICE = location.protocol === 'http:' && location.hostname !== '';

  let ws = null;
  let wsConnected = false;
  let reconnectTimer = null;
  const telemetry = { motorL: 0, motorR: 0, obsL: false, obsR: false, binFull: false, conveyor: true,
                      distFL: null, distFR: null, distBL: null, distBR: null };   // cm (firmware final)

  function connectWS() {
    try {
      ws = new WebSocket(WS_URL);
    } catch (e) {
      scheduleReconnect();
      return;
    }
    ws.onopen = () => {
      wsConnected = true;
      wifiDot.classList.remove('off');
      wifiLabel.textContent = 'ARCA-Boat';
    };
    ws.onclose = () => {
      wsConnected = false;
      wifiDot.classList.add('off');
      wifiLabel.textContent = 'Terputus';
      scheduleReconnect();
    };
    ws.onerror = () => { ws.close(); };
    ws.onmessage = (evt) => {
      let data;
      try { data = JSON.parse(evt.data); } catch (e) { return; }
      if (data.type === 'telemetry') {
        telemetry.motorL = data.motorL ?? 0;
        telemetry.motorR = data.motorR ?? 0;
        telemetry.obsL = !!data.obsL;
        telemetry.obsR = !!data.obsR;
        telemetry.binFull = !!data.binFull;
        telemetry.conveyor = !!data.conveyor;
        ['distFL','distFR','distBL','distBR'].forEach(k => { telemetry[k] = (typeof data[k] === 'number') ? data[k] : null; });
        applyTelemetryToUI();
      }
    };
  }

  function scheduleReconnect() {
    if (reconnectTimer) return;
    reconnectTimer = setTimeout(() => { reconnectTimer = null; connectWS(); }, 2000);
  }

  function sendCmd(obj) {
    if (!ON_DEVICE) { simHandleCommand(obj); return; }
    if (ws && wsConnected && ws.readyState === WebSocket.OPEN) {
      ws.send(JSON.stringify(obj));
    }
  }

  // ---------- Mode Simulasi (meniru firmware main.cpp) ----------
  function clamp1(v) { return Math.max(-1, Math.min(1, v)); }
  function simHandleCommand(obj) {
    if (obj.type === 'joystick') {
      const throttle = -(obj.y || 0);   // maju = atas = y negatif
      const turn = obj.x || 0;
      telemetry.motorL = clamp1(throttle + turn);
      telemetry.motorR = clamp1(throttle - turn);
    }
  }
  // Ambang sama dengan firmware config.h (keputusan final ada di firmware, UI cuma menampilkan)
  const SIM_OBSTACLE_CM = 40, SIM_BIN_FULL_CM = 6;
  function startSimulation() {
    wifiDot.classList.remove('off');
    wifiDot.classList.add('sim');
    wifiLabel.textContent = 'Simulasi';
    let t = 0, fill = 0;
    setInterval(() => {
      t += 0.15;
      // sensor HALANGAN depan: kiri & kanan bergerak sendiri-sendiri
      telemetry.distFL = Math.max(8, 110 + 85 * Math.sin(t / 2.1) + (Math.random() * 6 - 3));
      telemetry.distFR = Math.max(8, 120 + 90 * Math.sin(t / 2.9 + 2) + (Math.random() * 6 - 3));
      // sensor SAMPAH di bak: pelan-pelan terisi, lalu dikosongkan lagi
      fill = (fill + 0.12) % 40;
      telemetry.distBL = Math.max(3, 28 - fill * 0.62 + (Math.random() * 1.6 - 0.8));
      telemetry.distBR = Math.max(3, 27 - fill * 0.60 + (Math.random() * 1.6 - 0.8));
      telemetry.obsL = telemetry.distFL <= SIM_OBSTACLE_CM;
      telemetry.obsR = telemetry.distFR <= SIM_OBSTACLE_CM;
      telemetry.binFull = telemetry.distBL <= SIM_BIN_FULL_CM && telemetry.distBR <= SIM_BIN_FULL_CM;
      applyTelemetryToUI();
    }, 150);
  }

  function applyTelemetryToUI() {
    obsLActive = telemetry.obsL;
    obsRActive = telemetry.obsR;
    obsLChip.classList.toggle('warn', telemetry.obsL);
    obsLVal.textContent = telemetry.obsL ? 'Terdeteksi' : 'Aman';
    obsRChip.classList.toggle('warn', telemetry.obsR);
    obsRVal.textContent = telemetry.obsR ? 'Terdeteksi' : 'Aman';
    binChip.classList.toggle('warn', telemetry.binFull);
    binVal.textContent = telemetry.binFull ? 'Penuh' : 'Kosong';
    convVal.textContent = telemetry.conveyor ? 'Aktif' : 'Nonaktif';
    const cm = v => (v === null ? '—' : (v >= 400 ? '>400' : String(Math.round(v))));
    obsLSub.textContent = 'Depan-kiri · ' + cm(telemetry.distFL) + ' cm';
    obsRSub.textContent = 'Depan-kanan · ' + cm(telemetry.distFR) + ' cm';
    binSub.textContent = 'Bak L ' + cm(telemetry.distBL) + ' · R ' + cm(telemetry.distBR) + ' cm';
  }

  let startTime = Date.now();
  let lastT = performance.now();

  function updateMotorBars() {
    // Nilai motor diambil dari telemetry ASLI yang dikirim ESP32 —
    // supaya bar ini nunjukin apa yang beneran terjadi di board,
    // bukan cuma niat/posisi joystick doang.
    const left = telemetry.motorL;
    const right = telemetry.motorR;
    motorLBar.style.width = (Math.abs(left)*50) + '%';
    motorLBar.style.left = left >= 0 ? '50%' : (50 - Math.abs(left)*50) + '%';
    motorRBar.style.width = (Math.abs(right)*50) + '%';
    motorRBar.style.left = right >= 0 ? '50%' : (50 - Math.abs(right)*50) + '%';
    return { left, right };
  }

  function tick(now) {
    const dt = Math.min((now - lastT) / 1000, 0.1);
    lastT = now;

    const { left, right } = updateMotorBars();
    const throttle = (left + right) / 2;
    const turnRate = (left - right) * 55; // deg/sec

    if (Math.abs(throttle) > 0.02 || Math.abs(turnRate) > 0.5) {
      boat.heading += turnRate * dt;
      boat.heading = ((boat.heading % 360) + 360) % 360;
      const speed = throttle * 14; // sim units/sec
      const rad = boat.heading * Math.PI / 180;
      const dx = Math.sin(rad) * speed * dt;
      const dy = -Math.cos(rad) * speed * dt;
      boat.x += dx;
      boat.y += dy;
      totalDist += Math.hypot(dx, dy);

      const last = trail[trail.length - 1];
      if (Math.hypot(boat.x - last.x, boat.y - last.y) > 0.15) {
        trail.push({ x: boat.x, y: boat.y });
        if (trail.length > MAX_TRAIL) trail.shift();
      }
    }

    hdgVal.textContent = String(Math.round(boat.heading)).padStart(3,'0') + '°';
    distVal.textContent = totalDist.toFixed(1) + ' m';

    const elapsed = Math.floor((Date.now() - startTime)/1000);
    const mm = String(Math.floor(elapsed/60)).padStart(2,'0');
    const ss = String(elapsed%60).padStart(2,'0');
    runTimer.textContent = `${mm}:${ss} BERJALAN`;

    render();
    requestAnimationFrame(tick);
  }

  // ---------- Reset track ----------
  document.getElementById('resetBtn').addEventListener('click', () => {
    boat = { x: 0, y: 0, heading: 0 };
    trail = [{x:0,y:0}];
    totalDist = 0;
    startTime = Date.now();
  });

  // Init
  resize();
  if (ON_DEVICE) connectWS(); else startSimulation();
  requestAnimationFrame(tick);
})();
</script>
</body>
</html>
)ARCAPAGE";
