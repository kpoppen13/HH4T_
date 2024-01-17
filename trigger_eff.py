import os, sys
#rootFile=sys.argv[1]
#histNum=sys.argv[2]
#histDeNum=sys.argv[3]

import ROOT
from ROOT import *
#ROOT.gStyle.SetOptStat(0)

Rad_1000 = TFile('out_1000.root', 'READ')
Rad_2000 = TFile('out_2000.root', 'READ')
Rad_3000 = TFile('out_3000.root', 'READ')

ZZ_bkg = TFile('output_ZZ.root', 'READ')
DY_bkg = TFile('output_DY.root', 'READ')


# TRIGGER 39, 1 TeV
## need to divide the two histograms
denominator = Rad_1000.Get("Denominator39")
numerator = Rad_1000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator.Clone()
result_histogram.Divide(denominator)

c = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV PFHT and PFMET_PFMHT efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("PFHT")
result_histogram.GetYaxis().SetTitle("PFMET_PFMHT")

c.Draw()
c.SaveAs("trigger39_1TeV_eff.pdf")


# TRIGGER 39, 2 TeV
## need to divide the two histograms
denominator1 = Rad_2000.Get("Denominator39")
numerator1 = Rad_2000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator1.Clone()
result_histogram.Divide(denominator1)

c2 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("2 TeV PFHT and PFMET_PFMHT efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("PFHT")
result_histogram.GetYaxis().SetTitle("PFMET_PFMHT")


c2.Draw()
c2.SaveAs("trigger39_2TeV_eff.pdf")



# TRIGGER 39, 3 TeV
## need to divide the two histograms
denominator2 = Rad_3000.Get("Denominator39")
numerator2 = Rad_3000.Get("Numerator39")

# Divide numerator by denominator
result_histogram = numerator2.Clone()
result_histogram.Divide(denominator2)

c3 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("3 TeV PFHT and PFMET_PFMHT efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("PFHT")
result_histogram.GetYaxis().SetTitle("PFMET_PFMHT")

c3.Draw()
c3.SaveAs("trigger39_3TeV_eff.pdf")




# TRIGGER 40, 1 TeV
## need to divide the two histograms
denominator3 = Rad_1000.Get("Denominator40")
numerator3 = Rad_1000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator3.Clone()
result_histogram.Divide(denominator3)

c4 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c4.Draw()
c4.SaveAs("trigger40_1TeV_eff.pdf")




# TRIGGER 40, 2 TeV
denominator4 = Rad_2000.Get("Denominator40")
numerator4 = Rad_2000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator4.Clone()
result_histogram.Divide(denominator4)

c5 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("2 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c5.Draw()
c5.SaveAs("trigger40_2TeV_eff.pdf")





# TRIGGER 40, 3 TeV
denominator5 = Rad_3000.Get("Denominator40")
numerator5 = Rad_3000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator5.Clone()
result_histogram.Divide(denominator5)

c6 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("3 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c6.Draw()
c6.SaveAs("trigger40_3TeV_eff.pdf")

########################################################

# TRIGGER 39, ZZ
denominator6 = ZZ_bkg.Get("Denominator40")
numerator6 = ZZ_bkg.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator6.Clone()
result_histogram.Divide(denominator6)

c7 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("ZZ bkg PFHT and PFMET_PFMHT efficiency trigger 39: HLT_PFHT500_PFMET100_PFMHT100_IDTight_v")
result_histogram.GetXaxis().SetTitle("PFHT")
result_histogram.GetYaxis().SetTitle("PFMET_PFMHT")

c7.Draw()
c7.SaveAs("trigger39_ZZ_eff.pdf")




# TRIGGER 40, ZZ
denominator7 = ZZ_bkg.Get("Denominator40")
numerator7 = ZZ_bkg.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator7.Clone()
result_histogram.Divide(denominator7)

c8 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("ZZ bkg AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c8.Draw()
c8.SaveAs("trigger40_ZZ_eff.pdf")


'''


# TRIGGER 40, 3 TeV
denominator5 = Rad_3000.Get("Denominator40")
numerator5 = Rad_3000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator5.Clone()
result_histogram.Divide(denominator5)

c6 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c6.Draw()
c6.SaveAs("trigger40_3TeV_eff.pdf")






# TRIGGER 40, 3 TeV
denominator5 = Rad_3000.Get("Denominator40")
numerator5 = Rad_3000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator5.Clone()
result_histogram.Divide(denominator5)

c6 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c6.Draw()
c6.SaveAs("trigger40_3TeV_eff.pdf")





# TRIGGER 40, 3 TeV
denominator5 = Rad_3000.Get("Denominator40")
numerator5 = Rad_3000.Get("Numerator40")

# Divide numerator by denominator
result_histogram = numerator5.Clone()
result_histogram.Divide(denominator5)

c6 = TCanvas("canvas", "Divided Histogram", 800, 600)
result_histogram.Draw("colz")

result_histogram.SetTitle("1 TeV AK8Mass and AK8Pt efficiency trigger 40: HLT_AK8PFJet400_TrimMass30_v")
result_histogram.GetXaxis().SetTitle("AK8Mass")
result_histogram.GetYaxis().SetTitle("AK8Pt")

c6.Draw()
c6.SaveAs("trigger40_3TeV_eff.pdf")
'''
