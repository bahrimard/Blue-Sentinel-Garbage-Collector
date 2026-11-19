"""DRC + konektivitas mandiri (shapely) — sebelum diekspor ke Eagle."""
import sys, itertools
from shapely.geometry import Point, LineString, box, Polygon
from shapely.ops import unary_union
import design
from design import PKG

MIN_CLR = 0.40      # jarak tembaga beda net (mm) — aman untuk etching / toko lokal
EDGE_CLR = 0.8
INTERNAL = {'JUMPER_WIRE': [('1', '2')]}   # pad yang tersambung di dalam part

def pad_shape(b, ref, pn):
    e = b.el[ref]
    for (n, dx, dy, d, dr, sh) in PKG[e['pkg']]['pads']:
        if n == pn:
            x, y = b.pad_xy(ref, n)
            return box(x - d/2, y - d/2, x + d/2, y + d/2) if sh == 'square' else Point(x, y).buffer(d/2, 32)

def run(b, verbose=True):
    errs = []
    pad_net = {}
    for net, lst in b.nets.items():
        for rp in lst:
            if rp in pad_net: errs.append(f'pad {rp} di 2 net'); pad_net[rp] = net
            pad_net[rp] = net
    # semua pad (termasuk yang NC)
    items = []   # (net, geom, label)
    for ref, e in b.el.items():
        for (n, *_r) in PKG[e['pkg']]['pads']:
            items.append((pad_net.get((ref, n), f'NC:{ref}.{n}'), pad_shape(b, ref, n), f'{ref}.{n}'))
    for i, (net, pts, w) in enumerate(b.traces):
        items.append((net, LineString(pts).buffer(w/2, 16), f'trace#{i}:{net}'))
    # --- trace ujung harus kena pad/trace net yang sama; trace tidak boleh nabrak net lain (short)
    # clearance
    worst = 99
    for (n1, g1, l1), (n2, g2, l2) in itertools.combinations(items, 2):
        if n1 == n2: continue
        dd = g1.distance(g2)
        if dd < worst: worst = dd
        if dd < MIN_CLR:
            errs.append(f'CLEARANCE {dd:.2f} mm: {l1} ({n1}) <-> {l2} ({n2})')
    # tepi board & lubang mounting
    outline = box(0, 0, b.w, b.h)
    for (n, g, l) in items:
        if not outline.buffer(-EDGE_CLR).contains(g):
            errs.append(f'EDGE: {l} terlalu dekat/keluar tepi board')
        for (hx, hy, hd) in b.holes:
            if g.distance(Point(hx, hy).buffer(hd/2)) < 0.8:
                errs.append(f'HOLE: {l} terlalu dekat lubang ({hx},{hy})')
    # konektivitas per net
    for net, lst in b.nets.items():
        geoms = [pad_shape(b, r, p) for (r, p) in lst] + [LineString(pts).buffer(w/2, 16) for (nn, pts, w) in b.traces if nn == net]
        # internal link (jumper)
        for ref, e in b.el.items():
            for (a, c) in INTERNAL.get(e['pkg'], []):
                if (ref, a) in lst and (ref, c) in lst:
                    geoms.append(LineString([b.pad_xy(ref, a), b.pad_xy(ref, c)]).buffer(0.05))
        geoms += [LineString(pts).buffer(w/2, 16) for (nn, pts, w) in getattr(b, 'top', []) if nn == net]
        u = unary_union(geoms)
        parts = [u] if u.geom_type == 'Polygon' else list(u.geoms)
        if len(parts) != 1:
            # tampilkan pad yang tidak tersambung
            groups = []
            for pg in parts:
                groups.append([f'{r}.{p}' for (r, p) in lst if pad_shape(b, r, p).intersects(pg)])
            errs.append(f'OPEN net {net}: {len(parts)} pulau -> {groups}')
    if verbose:
        print(f'== {b.name}: {len(b.el)} part, {len(b.nets)} net, {len(b.traces)} jalur, clearance terkecil {worst:.2f} mm')
        for e in errs: print('   ', e)
        print('   OK' if not errs else f'   {len(errs)} masalah')
    return errs

if __name__ == '__main__':
    bad = sum(len(run(b)) for b in design.BOARDS)
    sys.exit(1 if bad else 0)
