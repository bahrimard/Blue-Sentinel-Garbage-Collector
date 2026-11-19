import pcbnew, os, sys
os.makedirs('out/kicad', exist_ok=True)
name = sys.argv[1]
plug = pcbnew.IO_MGR.PluginFind(pcbnew.IO_MGR.EAGLE)
brd = plug.Load(f'out/eagle/{name}.brd', None)
print(f'import {name}: footprints={len(brd.GetFootprints())} tracks={len(brd.GetTracks())} nets={brd.GetNetCount()-1}')
pcbnew.SaveBoard(f'out/kicad/{name}.kicad_pcb', brd)
