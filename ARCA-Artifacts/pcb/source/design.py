"""ARCA PCB v1 — satu sumber kebenaran: footprint, penempatan, netlist, dan jalur tembaga.
Semua satuan mm, origin kiri-bawah, dilihat dari atas (sisi komponen). Tembaga hanya di BOTTOM (1 layer).
"""
import math

# ------------------------------------------------------------------ footprints
# pad: (name, dx, dy, diameter, drill, shape)  shape: round|square|octagon
def row(names, pitch=2.54, horizontal=True, d=1.7, drill=1.0, first_square=True):
    n = len(names); off = (n - 1) * pitch / 2
    pads = []
    for i, nm in enumerate(names):
        p = -off + i * pitch
        x, y = (p, 0) if horizontal else (0, off - i * pitch)
        pads.append((nm, round(x, 3), round(y, 3), d, drill, 'square' if (first_square and i == 0) else 'round'))
    return pads

PKG = {}
def pkg(name, pads, silk=(), desc='', circles=(), holes=()):
    PKG[name] = dict(pads=pads, silk=list(silk), desc=desc, circles=list(circles), holes=list(holes))

# ESP32 DOIT DevKit V1 30-pin (2x15 female header), baris 25.4 mm, antena ke +y
ESP_L = ['EN','VP','VN','D34','D35','D32','D33','D25','D26','D27','D14','D12','D13','GND@1','VIN']
ESP_R = ['D23','D22','TX0','RX0','D21','D19','D18','D5','TX2','RX2','D4','D2','D15','GND@2','3V3']
esp_pads = []
for i in range(15):
    y = 17.78 - i * 2.54
    esp_pads.append((f'L{i+1}', -12.7, round(y, 3), 1.8, 1.0, 'square' if i == 0 else 'round'))
    esp_pads.append((f'R{i+1}', 12.7, round(y, 3), 1.8, 1.0, 'round'))
pkg('ESP32_DEVKIT_V1_30', esp_pads,
    silk=[(-14.1, -21.3, 14.1, -21.3), (14.1, -21.3, 14.1, 30.2), (14.1, 30.2, -14.1, 30.2), (-14.1, 30.2, -14.1, -21.3),
          (-14.1, 22.0, 14.1, 22.0),  # batas antena
          (-4, -21.3, -4, -24.3), (-4, -24.3, 4, -24.3), (4, -24.3, 4, -21.3)],  # USB
    desc='ESP32 DOIT DevKit V1 30 pin, socket 2x15, jarak baris 25.4 mm')
pkg('HDR1X6_V', row(['1','2','3','4','5','6'], horizontal=False),
    silk=[(-1.27, 7.62, 1.27, 7.62), (1.27, 7.62, 1.27, -7.62), (1.27, -7.62, -1.27, -7.62), (-1.27, -7.62, -1.27, 7.62)])
pkg('HDR1X4_H', row(['1','2','3','4']),
    silk=[(-5.08, 1.27, 5.08, 1.27), (5.08, 1.27, 5.08, -1.27), (5.08, -1.27, -5.08, -1.27), (-5.08, -1.27, -5.08, 1.27)])
def term(n):
    pads = row([str(i+1) for i in range(n)], pitch=5.08, d=2.6, drill=1.3)
    w = n * 5.08 / 2
    return pads, [(-w, -4.2, w, -4.2), (w, -4.2, w, 3.4), (w, 3.4, -w, 3.4), (-w, 3.4, -w, -4.2), (-w, -2.8, w, -2.8)]
p, s = term(3); pkg('TERM3_508', p, s, desc='Terminal screw 3 pin 5.08 mm, kabel masuk dari sisi -y')
p, s = term(2); pkg('TERM2_508', p, s, desc='Terminal screw 2 pin 5.08 mm, kabel masuk dari sisi -y')
pkg('TO220V', [('1', -2.54, 0, 1.9, 1.1, 'square'), ('2', 0, 0, 1.9, 1.1, 'round'), ('3', 2.54, 0, 1.9, 1.1, 'round')],
    silk=[(-5.1, -1.4, 5.1, -1.4), (5.1, -1.4, 5.1, 3.4), (5.1, 3.4, -5.1, 3.4), (-5.1, 3.4, -5.1, -1.4), (-5.1, 2.2, 5.1, 2.2)],
    desc='TO-220 berdiri, tab/heatsink ke +y. 1=IN 2=GND 3=OUT (L7805)')
pkg('CAP_RAD_2.54', [('1', -1.27, 0, 1.7, 0.9, 'square'), ('2', 1.27, 0, 1.7, 0.9, 'round')],
    circles=[(0, 0, 2.5)], silk=[(-2.4, 1.6, -1.6, 1.6), (-2.0, 2.0, -2.0, 1.2)], desc='Kapasitor radial pitch 2.54, pad 1 = +')
pkg('RES_AX_10.16', [('1', -5.08, 0, 1.8, 0.9, 'round'), ('2', 5.08, 0, 1.8, 0.9, 'round')],
    silk=[(-3.2, -1.1, 3.2, -1.1), (3.2, -1.1, 3.2, 1.1), (3.2, 1.1, -3.2, 1.1), (-3.2, 1.1, -3.2, -1.1),
          (-4.1, 0, -3.2, 0), (3.2, 0, 4.1, 0)], desc='Resistor 1/4 W tidur, pitch 10.16')
pkg('RES_V_2.54', [('1', 0, 1.27, 1.7, 0.9, 'round'), ('2', 0, -1.27, 1.7, 0.9, 'round')],
    circles=[(0, 1.27, 1.25)], silk=[(0, 0.02, 0, -0.4)], desc='Resistor 1/4 W berdiri, pitch 2.54 (badan di atas pad 1)')
pkg('TO92_INLINE', [('1', -2.54, 0, 1.5, 0.8, 'round'), ('2', 0, 0, 1.5, 0.8, 'round'), ('3', 2.54, 0, 1.5, 0.8, 'round')],
    silk=[(-2.4, -1.6, 2.4, -1.6)], circles=[], desc='TO-92 kaki sejajar. BC337: 1=C 2=B 3=E, sisi datar ke -y')
PKG['TO92_INLINE']['arc'] = True
pkg('BUZZER12_7.62', [('1', 3.81, 0, 1.8, 0.9, 'square'), ('2', -3.81, 0, 1.8, 0.9, 'round')],
    circles=[(0, 0, 6.0)], silk=[(3.81, 2.2, 3.81, 3.6), (3.11, 2.9, 4.51, 2.9)],
    desc='Buzzer aktif 12 mm pitch 7.62 (pad 1 = +) — atau kabel 2 pin')
pkg('HDR1X2_BZ', [('1', 1.27, 0, 1.7, 1.0, 'square'), ('2', -1.27, 0, 1.7, 1.0, 'round')],
    silk=[(-2.54, 1.27, 2.54, 1.27), (2.54, 1.27, 2.54, -1.27), (2.54, -1.27, -2.54, -1.27), (-2.54, -1.27, -2.54, 1.27)],
    desc='Header 1x2 ke buzzer aktif 5V (pad 1 = +)')
pkg('JUMPER_WIRE', [('1', 0, 0, 1.8, 0.9, 'round'), ('2', 11.9, 0, 1.8, 0.9, 'round')],
    silk=[(1.2, 0, 10.7, 0)], desc='Jumper kabel di sisi komponen (pad 1 & 2 satu net)')

# ------------------------------------------------------------------ board helpers
def rot(dx, dy, r):
    a = math.radians(r); return (dx * math.cos(a) - dy * math.sin(a), dx * math.sin(a) + dy * math.cos(a))

class Board:
    def __init__(self, name, w, h):
        self.name, self.w, self.h = name, w, h
        self.el = {}      # ref -> dict(pkg, x, y, rot, value, dev)
        self.nets = {}    # net -> [(ref,pad)]
        self.traces = []  # (net, [(x,y)...], width)
        self.top = []     # jalur layer ATAS = kabel jumper di board 1 layer
        self.holes = []   # (x,y,drill)
        self.texts = []   # (x,y,size,text,layer,align)
    def add(self, ref, p, x, y, r=0, value='', dev=''):
        self.el[ref] = dict(pkg=p, x=x, y=y, rot=r, value=value or ref, dev=dev or p)
    def pad_xy(self, ref, pad):
        e = self.el[ref]
        for (n, dx, dy, d, dr, sh) in PKG[e['pkg']]['pads']:
            if n == pad:
                rx, ry = rot(dx, dy, e['rot']); return (round(e['x'] + rx, 3), round(e['y'] + ry, 3))
        raise KeyError(ref + '.' + pad)
    def connect(self, net, *refpads):
        self.nets.setdefault(net, [])
        for rp in refpads:
            ref, pad = rp.split('.'); self.nets[net].append((ref, pad))
    def trace(self, net, pts, w=0.6):
        self.traces.append((net, [(round(x, 3), round(y, 3)) for x, y in pts], w))
    def T(self, net, start, *pts, w=0.6, end=None):
        """start/end bisa 'REF.PAD' atau (x,y)."""
        seq = []
        for p in (start,) + pts + ((end,) if end else ()):
            seq.append(self.pad_xy(*p.split('.')) if isinstance(p, str) else p)
        self.trace(net, seq, w)

# ================================================================== MAIN BOARD
M = Board('arca-main', 100, 79)
M.add('U1', 'ESP32_DEVKIT_V1_30', 47.7, 46.22, 0, 'ESP32 DevKit V1', 'ESP32')
M.add('J4', 'HDR1X6_V', 12, 44.95, 0, 'L298N IN', 'HDR6')
for i, (ref, y) in enumerate([('J5', 58.5), ('J6', 48.3), ('J7', 38.0), ('J8', 27.5)]):
    M.add(ref, 'HDR1X4_H', 77.81, y, 0, 'US' + str(i + 1), 'HDR4')
M.add('J1', 'TERM3_508', 9.58, 6, 0, 'BATERAI 2S', 'TERM3')
M.add('J2', 'TERM2_508', 4.5, 19.08, 270, 'CONVEYOR', 'TERM2')
M.add('J3', 'TERM2_508', 47.54, 6, 0, 'L298N PWR', 'TERM2')
M.add('U2', 'TO220V', 79.08, 13, 0, 'L7805', 'L7805')
M.add('C1', 'CAP_RAD_2.54', 75.27, 6, 0, '1uF', 'CAP')
M.add('C2', 'CAP_RAD_2.54', 80.35, 20.5, 180, '1uF', 'CAP')
M.add('R1', 'RES_AX_10.16', 50.08, 20, 0, '1k', 'RES')
M.add('Q1', 'TO92_INLINE', 60.54, 17.5, 180, 'BC337', 'BC337')
M.add('J9', 'HDR1X2_BZ', 65.85, 25.5, 0, 'BUZZER', 'BUZZERHDR')
M.add('JP1', 'JUMPER_WIRE', 73.6, 23, 0, 'JUMPER', 'JUMPER')
for (x, y) in [(4, 75), (96, 75), (96, 5), (4, 40)]:
    M.holes.append((x, y, 3.2))

E = lambda side, i: f'U1.{side}{i}'
# --- netlist
M.connect('VBAT', 'J1.3', 'J3.2', 'U2.1', 'C1.1', E('L', 15))
M.connect('GND', 'J1.2', 'J3.1', 'J2.1', 'U2.2', 'C1.2', 'C2.2', E('L', 14), 'Q1.3',
          'J5.3', 'J6.3', 'J7.3', 'J8.3')
M.connect('MID', 'J1.1', 'J2.2')
M.connect('+5V', 'U2.3', 'C2.1', 'J5.4', 'J6.4', 'J7.4', 'J8.4', 'JP1.1', 'JP1.2', 'J9.1')
M.connect('BZ-', 'Q1.1', 'J9.2')
M.connect('Q_BASE', 'Q1.2', 'R1.2')
M.connect('BUZ', E('L', 13), 'R1.1')
for i, n in enumerate(['ENA', 'IN1', 'IN2', 'IN3', 'IN4', 'ENB']):
    M.connect(n, E('L', 6 + i), f'J4.{i+1}')
SENS = [('US1', 'J5', 1, 2), ('US2', 'J6', 5, 6), ('US3', 'J7', 7, 9), ('US4', 'J8', 10, 11)]  # (nama, conn, pinE, pinT) baris kanan
for (n, j, pe, pt) in SENS:
    M.connect(n + '_ECHO', E('R', pe), j + '.2')
    M.connect(n + '_TRIG', E('R', pt), j + '.1')

# --- jalur tembaga (bottom)
P = 1.5  # power
M.T('VBAT', 'J1.3', (14.66, 9), (76.54, 9), end='U2.1', w=P)
M.T('VBAT', 'J3.2', (50.08, 9), w=P)
M.T('VBAT', 'C1.1', (74, 9), w=1.0)
M.T('VBAT', E('L', 15), (24, 28.44), (24, 9), w=1.0)
M.T('GND', 'J1.2', (9.58, 2.5), (79.08, 2.5), end='U2.2', w=P)
M.T('GND', 'J3.1', (45, 2.5), w=P)
M.T('GND', 'C1.2', (76.54, 2.5), w=1.0)
M.T('GND', 'J1.2', (9.58, 30.98), end=E('L', 14), w=1.0)
M.T('GND', (9.58, 21.62), end='J2.1', w=1.0)
M.T('GND', 'U2.2', 'C2.2', 'J8.3', 'J7.3', 'J6.3', 'J5.3', w=0.8)       # spine GND
M.T('GND', 'Q1.3', (58, 15.5), (79.08, 15.5), w=0.6)
M.T('MID', 'J1.1', end='J2.2', w=1.0)
M.T('+5V', 'U2.3', 'C2.1', (81.62, 23), 'J8.4', 'J7.4', 'J6.4', 'J5.4', w=0.8)  # spine 5V
M.T('+5V', 'JP1.2', (81.62, 23), w=0.8)
M.top.append(('+5V', [M.pad_xy('JP1', '1'), M.pad_xy('JP1', '2')], 0.8))
M.T('+5V', 'J9.1', (67.12, 23), end='JP1.1', w=0.6)
M.T('BZ-', 'Q1.1', (63.08, 21), (64.58, 22.5), end='J9.2', w=0.6)
M.T('Q_BASE', 'R1.2', (60.54, 20), end='Q1.2')
M.T('BUZ', E('L', 13), (39, 33.52), (39, 20), end='R1.1')
for i, n in enumerate(['ENA', 'IN1', 'IN2', 'IN3', 'IN4', 'ENB']):
    M.T(n, E('L', 6 + i), end=f'J4.{i+1}')
M.T('US1_ECHO', E('R', 1), (76.54, 64), end='J5.2');  M.T('US1_TRIG', E('R', 2), (74, 61.46), end='J5.1')
M.T('US2_ECHO', E('R', 5), (76.54, 53.84), end='J6.2'); M.T('US2_TRIG', E('R', 6), (74, 51.30), end='J6.1')
M.T('US3_ECHO', E('R', 7), (67, 48.76), (67, 45.5), (76.54, 45.5), end='J7.2')
M.T('US3_TRIG', E('R', 9), (74, 43.68), end='J7.1')
M.T('US4_ECHO', E('R', 10), (70, 41.14), (70, 33.5), (76.54, 33.5), end='J8.2')
M.T('US4_TRIG', E('R', 11), (66.5, 38.6), (66.5, 31), (74, 31), end='J8.1')

# --- silkscreen (top, sisi komponen). Reference (U1, R1, ...) dicetak otomatis dari package.
TX = M.texts.append
TX((8, 75.6, 1.6, 'ARCA MAIN v1', 21, 'left')); TX((8, 73.4, 1.0, '1 layer - tembaga bawah', 21, 'left'))
TX((66, 75.6, 1.0, 'ESP32 DevKit V1 30pin', 21, 'left')); TX((66, 73.4, 1.0, 'antena atas, USB bawah', 21, 'left')); TX((47.7, 26.0, 1.0, 'USB', 21, 'center'))
TX((14.2, 53.6, 1.0, 'L298N', 21, 'left'))
for i, n in enumerate(['ENA', 'IN1', 'IN2', 'IN3', 'IN4', 'ENB']):
    TX((14.1, 51.30 - i * 2.54 - 0.5, 1.0, n, 21, 'left'))
for (ref, y), lab in zip([('J5', 58.5), ('J6', 48.3), ('J7', 38.0), ('J8', 27.5)],
                         ['US1 BAK-KIRI', 'US2 BAK-KANAN', 'US3 DEPAN-KIRI', 'US4 DEPAN-KANAN']):
    TX((84.2, y + 0.6, 1.0, lab, 21, 'left')); TX((84.2, y - 1.6, 1.0, 'T E G 5V', 21, 'left'))
TX((9.58, 10.4, 0.9, 'MID GND BAT+', 21, 'center')); TX((1.2, 25.6, 1.0, 'CONVEYOR', 21, 'left'))
TX((47.54, 10.6, 1.0, 'L298N: GND BAT+', 21, 'center'))
TX((71.0, 11.0, 1.0, 'IN G OUT', 21, 'right'))
TX((65.85, 23.0, 1.0, '+  -', 21, 'center'))
TX((88.8, 23.0, 1.0, 'JP1 kabel', 21, 'left'))

# ================================================================== SENSOR BOARD
S = Board('arca-sensor', 26, 23.5)
S.add('J2', 'HDR1X4_H', 13, 19, 0, 'HC-SR04', 'HDR4F')
S.add('J1', 'HDR1X4_H', 13, 4, 0, 'KE MAIN', 'HDR4')
S.add('R1', 'RES_V_2.54', 14.27, 15.23, 0, '470', 'RESV')
S.add('R2', 'RES_V_2.54', 14.27, 10.15, 0, '1k', 'RESV')
for (x, y) in [(3.5, 3.5), (3.5, 19.8)]:
    S.holes.append((x, y, 3.2))
S.connect('+5V', 'J2.1', 'J1.4'); S.connect('TRIG', 'J2.2', 'J1.1')
S.connect('ECHO_5V', 'J2.3', 'R1.1'); S.connect('ECHO', 'R1.2', 'R2.1', 'J1.2')
S.connect('GND', 'J2.4', 'R2.2', 'J1.3')
S.T('TRIG', 'J2.2', (11.73, 16.46), (9.19, 13.92), end='J1.1')
S.T('ECHO_5V', 'J2.3', end='R1.1')
S.T('ECHO', 'R1.2', 'R2.1')
S.T('ECHO', 'R1.2', (11.73, 11.42), end='J1.2')
S.T('GND', 'J2.4', (16.81, 8.88), 'R2.2', end='J1.3', w=0.8)
S.T('+5V', 'J2.1', (9.19, 21.3), (23, 21.3), (23, 4), end='J1.4', w=0.8)
TX = S.texts.append
TX((13, 21.9, 1.0, 'VCC TRIG ECHO GND', 21, 'center')); TX((16.2, 15.6, 1.0, 'R1 470', 21, 'left'))
TX((17.6, 11.0, 1.0, 'R2 1k', 21, 'left')); TX((13, 1.1, 1.0, 'T  E  G  5V', 21, 'center'))
TX((2.2, 7.0, 1.1, 'ARCA SENSOR v1', 21, 'left', 90))

BOARDS = [M, S]
