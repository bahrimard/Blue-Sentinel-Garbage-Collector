import pcbnew, sys
name = sys.argv[1]
path = f'out/kicad/{name}.kicad_pcb'
brd = pcbnew.LoadBoard(path)
ds = brd.GetDesignSettings()
nc = ds.m_NetSettings.m_DefaultNetClass
nc.SetClearance(pcbnew.FromMM(0.4)); nc.SetTrackWidth(pcbnew.FromMM(0.6))
ds.m_MinClearance = pcbnew.FromMM(0.4); ds.m_TrackMinWidth = pcbnew.FromMM(0.4)
ds.m_CopperEdgeClearance = pcbnew.FromMM(0.5); ds.m_HoleClearance = pcbnew.FromMM(0.4)
pcbnew.SaveBoard(path, brd)
brd = pcbnew.LoadBoard(path)
ok = pcbnew.WriteDRCReport(brd, f'out/kicad/{name}-drc.txt', pcbnew.EDA_UNITS_MILLIMETRES, True)
print('drc written', ok)
