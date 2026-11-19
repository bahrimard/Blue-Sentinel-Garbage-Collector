"""Ekspor design.py -> Eagle 9 XML (.brd, .sch, .lbr). Satu library 'arca' tertanam."""
from xml.sax.saxutils import quoteattr as qa, escape
import design
from design import PKG

LAYERS = [(1,'Top',4),(16,'Bottom',1),(17,'Pads',2),(18,'Vias',2),(19,'Unrouted',6),(20,'Dimension',15),(21,'tPlace',7),
 (22,'bPlace',7),(23,'tOrigins',15),(24,'bOrigins',15),(25,'tNames',7),(26,'bNames',7),(27,'tValues',7),(28,'bValues',7),
 (29,'tStop',7),(30,'bStop',7),(31,'tCream',7),(32,'bCream',7),(35,'tGlue',7),(36,'bGlue',7),(39,'tKeepout',4),(40,'bKeepout',1),
 (41,'tRestrict',4),(42,'bRestrict',1),(43,'vRestrict',2),(44,'Drills',7),(45,'Holes',7),(46,'Milling',3),(47,'Measures',7),
 (48,'Document',7),(49,'Reference',7),(51,'tDocu',7),(52,'bDocu',7),(91,'Nets',2),(92,'Busses',1),(93,'Pins',2),(94,'Symbols',4),
 (95,'Names',7),(96,'Values',7),(97,'Info',7),(98,'Guide',6)]

def f(v): return f'{v:.4f}'.rstrip('0').rstrip('.') if isinstance(v, float) else str(v)

def header():
    s = ['<?xml version="1.0" encoding="utf-8"?>', '<!DOCTYPE eagle SYSTEM "eagle.dtd">', '<eagle version="9.6.2">', '<drawing>',
         '<settings>', '<setting alwaysvectorfont="no"/>', '<setting verticaltext="up"/>', '</settings>',
         '<grid distance="0.635" unitdist="mm" unit="mm" style="lines" multiple="1" display="no" altdistance="0.127" altunitdist="mm" altunit="mm"/>',
         '<layers>']
    for n, name, c in LAYERS:
        s.append(f'<layer number="{n}" name="{name}" color="{c}" fill="1" visible="yes" active="yes"/>')
    s.append('</layers>')
    return s

def package_xml(name):
    p = PKG[name]; o = [f'<package name={qa(name)}>', f'<description>{escape(p["desc"])}</description>']
    for (n, dx, dy, d, dr, sh) in p['pads']:
        o.append(f'<pad name={qa(n)} x="{f(dx)}" y="{f(dy)}" drill="{f(dr)}" diameter="{f(d)}" shape="{sh}"/>')
    for (x1, y1, x2, y2) in p['silk']:
        o.append(f'<wire x1="{f(x1)}" y1="{f(y1)}" x2="{f(x2)}" y2="{f(y2)}" width="0.2" layer="21"/>')
    for (cx, cy, r) in p['circles']:
        o.append(f'<circle x="{f(cx)}" y="{f(cy)}" radius="{f(r)}" width="0.2" layer="21"/>')
    if p.get('arc'):
        o.append('<wire x1="-2.4" y1="-1.6" x2="2.4" y2="-1.6" width="0.2" layer="21" curve="-253.7"/>')
    ys = [pp[2] for pp in p['pads']] or [0]
    below = name in ('RES_AX_10.16', 'JUMPER_WIRE', 'HDR1X2_BZ')
    ny = (min(ys) - 2.2) if below else (max(ys) + 2.2)
    if name == 'HDR1X4_H':
        o.append('<text x="-5.8" y="0" size="1.016" layer="25" align="center-right">&gt;NAME</text>')
    elif name in ('RES_V_2.54', 'JUMPER_WIRE'):
        o.append('<text x="1.6" y="0" size="1.016" layer="51" align="center-left">&gt;NAME</text>')
    else:
        o.append(f'<text x="{f(5.95 if name == "JUMPER_WIRE" else 0)}" y="{f(ny)}" size="1.016" layer="25" align="{"top-center" if below else "bottom-center"}">&gt;NAME</text>')
    o.append(f'<text x="0" y="{f(min(ys) - 2.2)}" size="1.016" layer="27" align="top-center">&gt;VALUE</text>')
    o.append('</package>')
    return o

# ---------------------------------------------------------------- devices (schematic)
# deviceset: prefix, package, [(pin_name, pads, side)]
def pads_of(pkgname): return [p[0] for p in PKG[pkgname]['pads']]
DEV = {}
def dev(name, prefix, pkgname, pins, desc=''):
    DEV[name] = dict(prefix=prefix, pkg=pkgname, pins=pins, desc=desc)
dev('ESP32', 'U', 'ESP32_DEVKIT_V1_30',
    [(n, f'L{i+1}', 'L') for i, n in enumerate(design.ESP_L)] + [(n, f'R{i+1}', 'R') for i, n in enumerate(design.ESP_R)],
    'ESP32 DOIT DevKit V1 30 pin')
dev('HDR6', 'J', 'HDR1X6_V', [(str(i), str(i), 'L') for i in range(1, 7)], 'Header 1x6 2.54')
dev('HDR4', 'J', 'HDR1X4_H', [(str(i), str(i), 'L') for i in range(1, 5)], 'Header 1x4 2.54 (male / JST-XH / KF2510)')
dev('HDR4F', 'J', 'HDR1X4_H', [(str(i), str(i), 'L') for i in range(1, 5)], 'Socket 1x4 female untuk HC-SR04')
dev('TERM3', 'J', 'TERM3_508', [(str(i), str(i), 'L') for i in range(1, 4)], 'Terminal screw 3P 5.08')
dev('TERM2', 'J', 'TERM2_508', [(str(i), str(i), 'L') for i in range(1, 3)], 'Terminal screw 2P 5.08')
dev('L7805', 'U', 'TO220V', [('IN', '1', 'L'), ('GND', '2', 'L'), ('OUT', '3', 'R')], 'Regulator 5V TO-220')
dev('CAP', 'C', 'CAP_RAD_2.54', [('+', '1', 'L'), ('-', '2', 'R')], 'Kapasitor 1uF radial')
dev('RES', 'R', 'RES_AX_10.16', [('1', '1', 'L'), ('2', '2', 'R')], 'Resistor 1/4W')
dev('RESV', 'R', 'RES_V_2.54', [('1', '1', 'L'), ('2', '2', 'R')], 'Resistor 1/4W berdiri')
dev('BC337', 'Q', 'TO92_INLINE', [('B', '2', 'L'), ('C', '1', 'R'), ('E', '3', 'R')], 'NPN BC337')
dev('BUZZER', 'BZ', 'BUZZER12_7.62', [('+', '1', 'L'), ('-', '2', 'R')], 'Buzzer aktif 5V')
dev('BUZZERHDR', 'J', 'HDR1X2_BZ', [('+', '1', 'L'), ('-', '2', 'R')], 'Header 2 pin ke buzzer')
dev('JUMPER', 'JP', 'JUMPER_WIRE', [('1', '1 2', 'L')], 'Jumper kabel (2 pad satu net)')

def sym_geom(d):
    L = [p for p in d['pins'] if p[2] == 'L']; R = [p for p in d['pins'] if p[2] == 'R']
    n = max(len(L), len(R), 1); h = n * 2.54; top = (n - 1) * 2.54 / 2
    w = 20.32 if max([len(p[0]) for p in d['pins']] + [0]) > 3 or len(d['pins']) > 6 else 10.16
    pos = {}
    for i, p in enumerate(L): pos[p[0]] = (-w/2 - 2.54, round(top - i * 2.54, 3), 'R0')
    for i, p in enumerate(R): pos[p[0]] = (w/2 + 2.54, round(top - i * 2.54, 3), 'R180')
    return w, top, pos

def symbol_xml(name, d):
    w, top, pos = sym_geom(d)
    y1, y2 = top + 2.54, top - (max(len([p for p in d['pins'] if p[2]==s]) for s in 'LR') - 1) * 2.54 - 2.54
    o = [f'<symbol name={qa(name)}>',
         f'<wire x1="{f(-w/2)}" y1="{f(y1)}" x2="{f(w/2)}" y2="{f(y1)}" width="0.254" layer="94"/>',
         f'<wire x1="{f(w/2)}" y1="{f(y1)}" x2="{f(w/2)}" y2="{f(y2)}" width="0.254" layer="94"/>',
         f'<wire x1="{f(w/2)}" y1="{f(y2)}" x2="{f(-w/2)}" y2="{f(y2)}" width="0.254" layer="94"/>',
         f'<wire x1="{f(-w/2)}" y1="{f(y2)}" x2="{f(-w/2)}" y2="{f(y1)}" width="0.254" layer="94"/>',
         f'<text x="{f(-w/2)}" y="{f(y1 + 0.8)}" size="1.778" layer="95">&gt;NAME</text>',
         f'<text x="{f(-w/2)}" y="{f(y2 - 2.6)}" size="1.778" layer="96">&gt;VALUE</text>']
    for (pn, pads, side) in d['pins']:
        x, y, r = pos[pn]
        o.append(f'<pin name={qa(pn)} x="{f(x)}" y="{f(y)}" length="short" direction="pas" rot="{r}"/>')
    o.append('</symbol>')
    return o

def deviceset_xml(name, d):
    o = [f'<deviceset name={qa(name)} prefix={qa(d["prefix"])}>', f'<description>{escape(d["desc"])}</description>',
         '<gates>', f'<gate name="G$1" symbol={qa(name)} x="0" y="0"/>', '</gates>', '<devices>',
         f'<device name="" package={qa(d["pkg"])}>', '<connects>']
    for (pn, pads, side) in sorted(d['pins'], key=lambda p: p[0]):
        o.append(f'<connect gate="G$1" pin={qa(pn)} pad={qa(pads)}/>')
    o += ['</connects>', '<technologies>', '<technology name=""/>', '</technologies>', '</device>', '</devices>', '</deviceset>']
    return o

def library_xml(pkgs, with_symbols):
    o = ['<library name="arca">', '<description>ARCA IoT River Cleaning Boat — part library</description>', '<packages>']
    for p in pkgs: o += package_xml(p)
    o.append('</packages>')
    if with_symbols:
        used = [n for n, d in DEV.items() if d['pkg'] in pkgs]
        o.append('<symbols>')
        for n in used: o += symbol_xml(n, DEV[n])
        o += ['</symbols>', '<devicesets>']
        for n in used: o += deviceset_xml(n, DEV[n])
        o.append('</devicesets>')
    o.append('</library>')
    return o

DRU = [('layerSetup', '(16)'), ('mdWireWire', '0.4mm'), ('mdWirePad', '0.4mm'), ('mdWireVia', '0.4mm'), ('mdPadPad', '0.4mm'),
       ('mdPadVia', '0.4mm'), ('mdViaVia', '0.4mm'), ('mdCopperDimension', '0.8mm'), ('mdDrill', '0.4mm'), ('msWidth', '0.4mm'),
       ('msDrill', '0.8mm'), ('rvPadTop', '0.25'), ('rvPadInner', '0.25'), ('rvPadBottom', '0.25'), ('rlMinPadTop', '0.3mm'),
       ('rlMinPadBottom', '0.3mm'), ('mvStopFrame', '1'), ('mlMinStopFrame', '0.1mm'), ('mlMaxStopFrame', '0.1mm')]

def board_xml(b):
    s = header() + ['<board>', '<plain>']
    W, H = b.w, b.h
    for (x1, y1, x2, y2) in [(0, 0, W, 0), (W, 0, W, H), (W, H, 0, H), (0, H, 0, 0)]:
        s.append(f'<wire x1="{f(x1)}" y1="{f(y1)}" x2="{f(x2)}" y2="{f(y2)}" width="0" layer="20"/>')
    for t in b.texts:
        x, y, size, txt, layer, align = t[:6]; r = t[6] if len(t) > 6 else 0
        al = {'left': 'bottom-left', 'center': 'bottom-center', 'right': 'bottom-right'}[align]
        s.append(f'<text x="{f(x)}" y="{f(y)}" size="{f(size)}" layer="{layer}" font="vector" ratio="12" rot="R{r}" align="{al}">{escape(txt)}</text>')
    for (x, y, d) in b.holes:
        s.append(f'<hole x="{f(x)}" y="{f(y)}" drill="{f(d)}"/>')
    s.append('</plain>')
    pkgs = sorted({e['pkg'] for e in b.el.values()})
    s += ['<libraries>'] + library_xml(pkgs, False) + ['</libraries>', '<attributes/>', '<variantdefs/>', '<classes>',
          '<class number="0" name="default" width="0.6" drill="0"/>', '<class number="1" name="power" width="1.5" drill="0"/>',
          '</classes>', '<designrules name="arca-1layer">', '<description>1 layer (bottom), jarak min 0.4 mm</description>']
    s += [f'<param name="{k}" value="{v}"/>' for k, v in DRU] + ['</designrules>', '<autorouter/>', '<elements>']
    for ref, e in b.el.items():
        s.append(f'<element name={qa(ref)} library="arca" package={qa(e["pkg"])} value={qa(e["value"])} '
                 f'x="{f(float(e["x"]))}" y="{f(float(e["y"]))}"' + (f' rot="R{e["rot"]}"' if e['rot'] else '') + '/>')
    s += ['</elements>', '<signals>']
    power = {'GND', 'VBAT', '+5V', 'MID'}
    for net, lst in b.nets.items():
        s.append(f'<signal name={qa(net)}' + (' class="1"' if net in power else '') + '>')
        for (ref, pad) in lst:
            s.append(f'<contactref element={qa(ref)} pad={qa(pad)}/>')
        for (nn, pts, w) in b.traces:
            if nn != net: continue
            for (a, c) in zip(pts, pts[1:]):
                s.append(f'<wire x1="{f(a[0])}" y1="{f(a[1])}" x2="{f(c[0])}" y2="{f(c[1])}" width="{f(w)}" layer="16"/>')
        for (nn, pts, w) in getattr(b, 'top', []):
            if nn != net: continue
            for (a, c) in zip(pts, pts[1:]):
                s.append(f'<wire x1="{f(a[0])}" y1="{f(a[1])}" x2="{f(c[0])}" y2="{f(c[1])}" width="{f(w)}" layer="1"/>')
        s.append('</signal>')
    s += ['</signals>', '</board>', '</drawing>', '</eagle>']
    return '\n'.join(s) + '\n'

def schematic_xml(b):
    s = header() + ['<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">']
    pkgs = sorted({e['pkg'] for e in b.el.values()})
    s += ['<libraries>'] + library_xml(pkgs, True) + ['</libraries>', '<attributes/>', '<variantdefs/>', '<classes>',
          '<class number="0" name="default" width="0" drill="0"/>', '<class number="1" name="power" width="0" drill="0"/>',
          '</classes>', '<parts>']
    for ref, e in b.el.items():
        s.append(f'<part name={qa(ref)} library="arca" deviceset={qa(e["dev"])} device="" value={qa(e["value"])}/>')
    s += ['</parts>', '<sheets>', '<sheet>', '<plain>',
          f'<text x="5.08" y="5.08" size="2.54" layer="97">{escape(b.name)} — ARCA IoT River Cleaning Boat (dibuat otomatis dari design.py)</text>',
          '</plain>', '<instances>']
    # penempatan grid
    pos = {}; x, y, colw, rowh = 25.4, 180.34, 0, 0
    order = sorted(b.el, key=lambda r: -len(DEV[b.el[r]['dev']]['pins']))
    cx, cy, maxh = 30.48, 200.66, 0
    for ref in order:
        d = DEV[b.el[ref]['dev']]; w, top, pp = sym_geom(d)
        hgt = (top * 2 + 12.7)
        if cx + w + 45 > 380: cx, cy, maxh = 30.48, cy - maxh - 25.4, 0
        gx = round((cx + w/2 + 15.24) / 2.54) * 2.54; gy = round(cy / 2.54) * 2.54
        pos[ref] = (gx, gy); s.append(f'<instance part={qa(ref)} gate="G$1" x="{f(gx)}" y="{f(gy)}"/>')
        cx += w + 50.8; maxh = max(maxh, hgt)
    s += ['</instances>', '<busses/>', '<nets>']
    for net, lst in b.nets.items():
        s.append(f'<net name={qa(net)} class="{1 if net in {"GND","VBAT","+5V","MID"} else 0}">')
        done = set()
        for (ref, pad) in lst:
            d = DEV[b.el[ref]['dev']]
            pin = next(p for p in d['pins'] if pad in p[1].split())
            if (ref, pin[0]) in done: continue
            done.add((ref, pin[0]))
            w, top, pp = sym_geom(d); px, py, r = pp[pin[0]]
            ax, ay = pos[ref][0] + px, pos[ref][1] + py
            ex = ax - 7.62 if r == 'R0' else ax + 7.62
            al = 'bottom-right' if r == 'R0' else 'bottom-left'
            s += ['<segment>', f'<pinref part={qa(ref)} gate="G$1" pin={qa(pin[0])}/>',
                  f'<wire x1="{f(ax)}" y1="{f(ay)}" x2="{f(ex)}" y2="{f(ay)}" width="0.1524" layer="91"/>',
                  f'<label x="{f(ex)}" y="{f(ay)}" size="1.27" layer="95" align="{al}"/>', '</segment>']
        s.append('</net>')
    s += ['</nets>', '</sheet>', '</sheets>', '</schematic>', '</drawing>', '</eagle>']
    return '\n'.join(s) + '\n'

def lbr_xml():
    s = header() + ['<library>'] + library_xml(sorted(PKG), True)[1:-1] + ['</library>', '</drawing>', '</eagle>']
    return '\n'.join(s) + '\n'

if __name__ == '__main__':
    import os; os.makedirs('out/eagle', exist_ok=True)
    for b in design.BOARDS:
        open(f'out/eagle/{b.name}.brd', 'w').write(board_xml(b))
        open(f'out/eagle/{b.name}.sch', 'w').write(schematic_xml(b))
    open('out/eagle/arca.lbr', 'w').write(lbr_xml())
    import xml.dom.minidom, glob
    for p in sorted(glob.glob('out/eagle/*.brd') + glob.glob('out/eagle/*.sch') + glob.glob('out/eagle/*.lbr')):
        xml.dom.minidom.parse(p); print('XML OK', p, os.path.getsize(p))
