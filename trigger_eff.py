import os, sys
#rootFile=sys.argv[1]
#histNum=sys.argv[2]
#histDeNum=sys.argv[3]

import ROOT
from ROOT import *
#ROOT.gStyle.SetOptStat(0)

Rad_1000 =TFile('out_1000.root', 'READ')
Rad_2000 = TFile('out_2000.root', 'READ')
Rad_3000 = TFile('out_3000.root', 'READ')

### Trigger 39, 1 TeV
# create canvas
c = TCanvas("canvas", "2D Efficiency Plot", 800, 600)

pfMET_MHT_1000=Rad_1000.Get("PFMET_PFMHT")
PFHT_1000=Rad_1000.Get("PFHT")
efficiencies = Rad_1000.Get("total_efficiency_39")

# Histogram ranges
# can change these later on
#min_pfMET_MHT = 0
#max_pfMET_MHT = 1000
#min_PFHT = 0
#max_PFHT = 1000

# Create a 2D histogram for efficiency plot
#TH2F::TH2F(const char* name, const char* title, int nbinsx, const float* xbins, int nbinsy, const float* ybins)
histogram = TH2F("efficiency", "Efficiency Plot", 100, pfMET_MHT_1000, 100, PFHT_1000)
histogram.Fill(pfMET_MHT_1000, PFHT_1000, efficiencies)

# "colz" option displays colors for different efficiencies
histogram.Draw("colz")
c.Draw()
c.SaveAs("efficiencies_39.pdf")

