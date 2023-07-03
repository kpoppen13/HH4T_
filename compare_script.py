import os, sys
#rootFile=sys.argv[1]
#histNum=sys.argv[2]
#histDeNum=sys.argv[3]

import ROOT
from ROOT import *
#ROOT.gStyle.SetOptStat(0)

Rad_1000 =TFile('GluGluToRadionToHHTo4T_M-1000.root', 'READ')
Rad_2000 = TFile('GluGluToRadionToHHTo4T_M-2000.root', 'READ')
Rad_3000 = TFile('GluGluToRadionToHHTo4T_M-3000.root', 'READ')

c=TCanvas()
Rad_1000.Draw()        
Rad_1000.SetLineColor(1)
Rad_2000.Draw('same')
Rad_2000.SetLineColor(2)
Rad_3000.Draw('same')
Rad_3000.SetLineColor(4)

leg = ROOT.TLegend(0.12, 0.7, 0.85, 0.85)
leg.SetLineColor(0)
leg.SetTextSize(0.035)

