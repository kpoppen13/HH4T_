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

# TRIGGER 39, 1 TeV
## need to divide the two histograms
# Get the histograms from the file
denominator = Rad_1000.Get("Denominator39")
numerator = Rad_1000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator.Clone()
result_histogram.Divide(denominator)

c = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("Numerator/Denominator")
#result_histogram.GetXaxis().SetTitle("X-axis label")
#result_histogram.GetYaxis().SetTitle("Y-axis label")

c.Draw()
c.SaveAs("divided_histogram.pdf")


# TRIGGER 39, 2 TeV

# TRIGGER 39, 3 TeV

# TRIGGER 40, 1 TeV

# TRIGGER 40, 2 TeV

# TRIGGER 40, 3 TeV
