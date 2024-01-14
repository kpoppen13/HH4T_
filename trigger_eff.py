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
denominator = Rad_1000.Get("Denominator39")
numerator = Rad_1000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator.Clone()
result_histogram.Divide(denominator)

c = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV MHT and pfMET efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("MHT")
result_histogram.GetYaxis().SetTitle("pfMET")

c.Draw()
c.SaveAs("trigger39_1TeV_eff.pdf")


# TRIGGER 39, 2 TeV
## need to divide the two histograms
denominator = Rad_2000.Get("Denominator39")
numerator = Rad_2000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator.Clone()
result_histogram.Divide(denominator)

c2 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("2 TeV MHT and pfMET efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("MHT")
result_histogram.GetYaxis().SetTitle("pfMET")


c2.Draw()
c2.SaveAs("trigger39_2TeV_eff.pdf")



# TRIGGER 39, 3 TeV
## need to divide the two histograms
denominator = Rad_3000.Get("Denominator39")
numerator = Rad_3000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator.Clone()
result_histogram.Divide(denominator)

c3 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("3 TeV MHT and pfMET efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("MHT")
result_histogram.GetYaxis().SetTitle("pfMET")

c3.Draw()
c3.SaveAs("trigger39_3TeV_eff.pdf")



# TRIGGER 40, 1 TeV

# TRIGGER 40, 2 TeV

# TRIGGER 40, 3 TeV
