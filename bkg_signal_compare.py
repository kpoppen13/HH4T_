import os, sys
#rootFile=sys.argv[1]
#histNum=sys.argv[2]
#histDeNum=sys.argv[3]

import ROOT
from ROOT import *
#ROOT.gStyle.SetOptStat(0)

background =TFile('outputZZ.root', 'READ')
Rad_1000 = TFile('out_2000.root', 'READ')
Rad_2000 = TFile('out_2000.root', 'READ')
Rad_3000 = TFile('out_3000.root', 'READ')


c38=TCanvas()
H1_vismass_2000=Rad_1000.Get("higgs1_vis_mass")
H1_vismass_2000.SetLineColor(1)
H1_vismass_2000.SetMinimum(0)  # Set the minimum value for the y-axis
H1_vismass_2000.SetMaximum(H1_vismass_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
H1_vismass_2000.DrawNormalized()    

H1_vismass_bkg=background.Get("higgs1_vis_mass")
H1_vismass_bkg.SetLineColor(2)
H1_vismass_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(H1_vismass_2000, "H1_vismass_2000", "l")
leg.AddEntry(H1_vismass_bkg, "H1_vismass_bkg", "l")
leg.Draw()


c38.SaveAs('out38.pdf')



c39=TCanvas()
H2_vismass_2000=Rad_2000.Get("higgs2_vis_mass")
H2_vismass_2000.SetLineColor(1)
H2_vismass_2000.SetMinimum(0)  # Set the minimum value for the y-axis
H2_vismass_2000.SetMaximum(H2_vismass_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
H2_vismass_2000.DrawNormalized()        

H2_vismass_bkg=background.Get("higgs2_vis_mass")
H2_vismass_bkg.SetLineColor(2)
H2_vismass_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(H2_vismass_2000, "H2_vismass_2000", "l")
leg.AddEntry(H2_vismass_bkg, "H2_vismass_bkg", "l")
leg.Draw()


c39.SaveAs('out39.pdf')



c40=TCanvas()
radion_inv_mass2000=Rad_1000.Get("radion_inv_mass")
radion_inv_mass2000.SetLineColor(1)
radion_inv_mass2000.SetMinimum(0)  # Set the minimum value for the y-axis
radion_inv_mass2000.SetMaximum(radion_inv_mass2000.GetMaximum()*3)  # Set the maximum value for the y-axis
radion_inv_mass2000.DrawNormalized()     

radion_inv_mass_bkg=background.Get("radion_inv_mass")
radion_inv_mass_bkg.SetLineColor(2)
radion_inv_mass_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(radion_inv_mass2000, "radion_inv_mass2000", "l")
leg.AddEntry(radion_inv_mass_bkg, "radion_inv_mass_bkg", "l")
leg.Draw()


c40.SaveAs('out40.pdf')



c41=TCanvas()
higgs1_dR2000=Rad_2000.Get("higgs1_dr")
higgs1_dR2000.SetLineColor(1)
higgs1_dR2000.SetMinimum(0)  # Set the minimum value for the y-axis
higgs1_dR2000.SetMaximum(higgs1_dR2000.GetMaximum()*3)  # Set the maximum value for the y-axis
higgs1_dR2000.DrawNormalized()        

higgs1_dR_bkg=background.Get("higgs1_dr")
higgs1_dR_bkg.SetLineColor(2)
higgs1_dR_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(higgs1_dR2000, "higgs1_dR2000", "l")
leg.AddEntry(higgs1_dR_bkg, "higgs1_dR_bkg", "l")
leg.Draw()


c41.SaveAs('out41.pdf')



c42=TCanvas()
higgs2_dR2000=Rad_1000.Get("higgs2_dr")
higgs2_dR2000.SetLineColor(1)
higgs2_dR2000.SetMinimum(0)  # Set the minimum value for the y-axis
higgs2_dR2000.SetMaximum(higgs2_dR2000.GetMaximum()*3)  # Set the maximum value for the y-axis
higgs2_dR2000.DrawNormalized()        

higgs2_dR_bkg= background.Get("higgs2_dr")
higgs2_dR_bkg.SetLineColor(2)
higgs2_dR_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(higgs2_dR2000, "higgs2_dR2000", "l")
leg.AddEntry(higgs2_dR_bkg, "higgs2_dR_bkg", "l")
leg.Draw()


c42.SaveAs('out42.pdf')



c43=TCanvas()
dr_HH2000=Rad_2000.Get("dr_HH")
dr_HH2000.SetLineColor(1)
dr_HH2000.SetMinimum(0)  # Set the minimum value for the y-axis
dr_HH2000.SetMaximum(dr_HH2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dr_HH2000.DrawNormalized()        

dr_HH_bkg=background.Get("dr_HH")
dr_HH_bkg.SetLineColor(2)
dr_HH_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.2, 0.75, 0.45, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dr_HH2000, "dr_HH2000", "l")
leg.AddEntry(dr_HH_bkg, "dr_HH_bkg", "l")
leg.Draw()

c43.SaveAs('out43.pdf')



c44=TCanvas()
HT_rad_2000=Rad_2000.Get("HT")
HT_rad_2000.SetLineColor(1)
HT_rad_2000.SetMinimum(0)  # Set the minimum value for the y-axis
HT_rad_2000.SetMaximum(HT_rad_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
HT_rad_2000.DrawNormalized()        

HT_rad_bkg=background.Get("HT")
HT_rad_bkg.SetLineColor(2)
HT_rad_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.1, 0.75, 0.35, 0.9)
leg.SetLineColor(1)
leg.AddEntry(HT_rad_2000, "HT2000", "l")
leg.AddEntry(HT_rad_bkg, "HT_bkg", "l")
leg.Draw()

c44.SaveAs('out44.pdf')


'''
c45=TCanvas()
min_dR_muon2000=Rad_2000.Get("min_dR_muon")
min_dR_muon2000.SetLineColor(1)
min_dR_muon2000.Draw()        

min_dR_muon_bkg=background.Get("min_dR_muon")
min_dR_muon_bkg.SetLineColor(2)
min_dR_muon_bkg.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_muon2000, "min_dR_muon2000", "l")
leg.AddEntry(min_dR_muon_bkg, "min_dR_muon_bkg", "l")
leg.Draw()

c45.SetLogy()
c45.Update()
y_max = min_dR_muon_bkg.GetMaximum()
min_dR_muon2000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10
c45.SaveAs('out45.pdf')




c46=TCanvas()
min_dR_electron2000=Rad_2000.Get("min_dR_electron")
min_dR_electron2000.SetLineColor(1)
min_dR_electron2000.Draw()        

min_dR_electron_bkg=background.Get("min_dR_electron")
min_dR_electron_bkg.SetLineColor(2)
min_dR_electron_bkg.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_electron2000, "min_dR_electron2000", "l")
leg.AddEntry(min_dR_electron_bkg, "min_dR_electron_bkg", "l")
leg.Draw()

c46.SetLogy()
c46.Update()
y_max = min_dR_electron_bkg.GetMaximum()
min_dR_electron2000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10
c46.SaveAs('out46.pdf')
'''


c47=TCanvas()
ratio2000=Rad_2000.Get("ratio")
ratio2000.SetLineColor(1)
ratio2000.SetMinimum(0)  # Set the minimum value for the y-axis
ratio2000.SetMaximum(ratio2000.GetMaximum()*3)  # Set the maximum value for the y-axis
ratio2000.DrawNormalized()        

ratio_bkg=background.Get("ratio")
ratio_bkg.SetLineColor(2)
ratio_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(ratio2000, "ratio2000", "l")
leg.AddEntry(ratio_bkg, "ratio_bkg", "l")
leg.Draw()

c47.SaveAs('out47.pdf')



c48=TCanvas()
pfMET2000=Rad_2000.Get("MET")
pfMET2000.SetLineColor(1)
pfMET2000.SetMinimum(0)  # Set the minimum value for the y-axis
pfMET2000.SetMaximum(pfMET2000.GetMaximum()*3)  # Set the maximum value for the y-axis
pfMET2000.DrawNormalized()        

pfMET_bkg=background.Get("MET")
pfMET_bkg.SetLineColor(2)
pfMET_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(pfMET2000, "MET2000", "l")
leg.AddEntry(pfMET_bkg, "MET_bkg", "l")
leg.Draw()

c48.SaveAs('out48.pdf')



c49=TCanvas()
ratio2_2000=Rad_2000.Get("ratio2")
ratio2_2000.SetLineColor(1)
ratio2_2000.SetMinimum(0)  # Set the minimum value for the y-axis
ratio2_2000.SetMaximum(ratio2_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
ratio2_2000.DrawNormalized()        

ratio2_bkg=background.Get("ratio2")
ratio2_bkg.SetLineColor(2)
ratio2_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(ratio2_2000, "ratio2_2000", "l")
leg.AddEntry(ratio2_bkg, "ratio2_bkg", "l")
leg.Draw()

c49.SaveAs('out49.pdf')



c50=TCanvas()
tau1_h1_pt_2000=Rad_2000.Get("tau1_h1_pt")
tau1_h1_pt_2000.SetLineColor(1)
tau1_h1_pt_2000.SetMinimum(0)  # Set the minimum value for the y-axis
tau1_h1_pt_2000.SetMaximum(tau1_h1_pt_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
tau1_h1_pt_2000.DrawNormalized()        

tau1_h1_pt_bkg=background.Get("tau1_h1_pt")
tau1_h1_pt_bkg.SetLineColor(2)
tau1_h1_pt_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(tau1_h1_pt_2000, "tau1_h1_pt_2000", "l")
leg.AddEntry(tau1_h1_pt_bkg, "tau1_h1_pt_bkg", "l")
leg.Draw()

c50.SaveAs('out50.pdf')



c51=TCanvas()
tau2_h1_pt_2000=Rad_2000.Get("tau2_h1_pt")
tau2_h1_pt_2000.SetLineColor(1)
tau2_h1_pt_2000.SetMinimum(0)  # Set the minimum value for the y-axis
tau2_h1_pt_2000.SetMaximum(tau2_h1_pt_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
tau2_h1_pt_2000.DrawNormalized()        

tau2_h1_pt_bkg=background.Get("tau2_h1_pt")
tau2_h1_pt_bkg.SetLineColor(2)
tau2_h1_pt_bkg.DrawNormalized('same')


leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(tau2_h1_pt_2000, "tau2_h1_pt_2000", "l")
leg.AddEntry(tau2_h1_pt_bkg, "tau2_h1_pt_bkg", "l")
leg.Draw()

c51.SaveAs('out51.pdf')



c52=TCanvas()
tau1_h2_pt_2000=Rad_2000.Get("tau1_h2_pt")
tau1_h2_pt_2000.SetLineColor(1)
tau1_h2_pt_2000.SetMinimum(0)  # Set the minimum value for the y-axis
tau1_h2_pt_2000.SetMaximum(tau1_h2_pt_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
tau1_h2_pt_2000.DrawNormalized()        

tau1_h2_pt_bkg=background.Get("tau1_h2_pt")
tau1_h2_pt_bkg.SetLineColor(2)
tau1_h2_pt_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(tau1_h2_pt_2000, "tau1_h2_pt_2000", "l")
leg.AddEntry(tau1_h2_pt_bkg, "tau1_h2_pt_bkg", "l")
leg.Draw()

c52.SaveAs('out52.pdf')



c53=TCanvas()
tau2_h2_pt_2000=Rad_2000.Get("tau2_h2_pt")
tau2_h2_pt_2000.SetLineColor(1)
tau2_h2_pt_2000.SetMinimum(0)  # Set the minimum value for the y-axis
tau2_h2_pt_2000.SetMaximum(tau2_h2_pt_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
tau2_h2_pt_2000.DrawNormalized()        

tau2_h2_pt_bkg=background.Get("tau2_h2_pt")
tau2_h2_pt_bkg.SetLineColor(2)
tau2_h2_pt_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(tau2_h2_pt_2000, "tau2_h2_pt2000", "l")
leg.AddEntry(tau2_h2_pt_bkg, "tau2_h2_pt_bkg", "l")
leg.Draw()

c53.SaveAs('out53.pdf')



c54=TCanvas()
dphi2000=Rad_2000.Get("dphi_HH")
dphi2000.SetLineColor(1)
dphi2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi2000.SetMaximum(dphi2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi2000.DrawNormalized()        

dphi_bkg=background.Get("dphi_HH")
dphi_bkg.SetLineColor(2)
dphi_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi2000, "dphiHH_2000", "l")
leg.AddEntry(dphi_bkg, "dphiHH_bkg", "l")
leg.Draw()

c54.SaveAs('out54.pdf')



c55=TCanvas()
dphi_H1_2000=Rad_2000.Get("dphi_H1")
dphi_H1_2000.SetLineColor(1)
dphi_H1_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H1_2000.SetMaximum(dphi_H1_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H1_2000.DrawNormalized()        

dphi_H1_bkg=background.Get("dphi_H1")
dphi_H1_bkg.SetLineColor(2)
dphi_H1_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.15, 0.75, 0.40, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H1_2000, "dphi_H1_2000", "l")
leg.AddEntry(dphi_H1_bkg, "dphi_H1_bkg", "l")
leg.Draw()

c55.SaveAs('out55.pdf')



c56=TCanvas()
dphi_H2_2000=Rad_2000.Get("dphi_H2")
dphi_H2_2000.SetLineColor(1)
dphi_H2_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H2_2000.SetMaximum(dphi_H2_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H2_2000.DrawNormalized()        

dphi_H2_bkg=background.Get("dphi_H2")
dphi_H2_bkg.SetLineColor(2)
dphi_H2_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.15, 0.75, 0.40, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H2_2000, "dphi_H22000", "l")
leg.AddEntry(dphi_H2_bkg, "dphi_H2_bkg", "l")
leg.Draw()

c56.SaveAs('out56.pdf')


'''
c57=TCanvas()
TMass_H1_2000=Rad_2000.Get("TMass_H1")
TMass_H1_2000.SetLineColor(1)
TMass_H1_2000.Draw()        

TMass_H1_bkg=background.Get("TMass_H1")
TMass_H1_bkg.SetLineColor(2)
TMass_H1_bkg.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_H1_2000, "TMass_H1_2000", "l")
leg.AddEntry(TMass_H1_bkg, "TMass_H1_bkg", "l")
leg.Draw()

c57.SetLogy()
c57.Update()
y_max = TMass_H1_bkg.GetMaximum()
TMass_H1_2000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10
c57.SaveAs('out57.pdf')



c58=TCanvas()
TMass_H2_2000=Rad_2000.Get("TMass_H2")
TMass_H2_2000.SetLineColor(1)
TMass_H2_2000.Draw()        

TMass_H2_bkg=background.Get("TMass_H2")
TMass_H2_bkg.SetLineColor(2)
TMass_H2_bkg.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_H2_2000, "TMass_H2_2000", "l")
leg.AddEntry(TMass_H2_bkg, "TMass_H2_bkg", "l")
leg.Draw()

c58.SetLogy()
c58.Update()
y_max = TMass_H2_bkg.GetMaximum()
TMass_H2_2000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10
c58.SaveAs('out58.pdf')



c59=TCanvas()
TMass_Radion_2000=Rad_2000.Get("TMass_Radion")
TMass_Radion_2000.SetLineColor(1)
TMass_Radion_2000.Draw()        

TMass_Radion_bkg=background.Get("TMass_Radion")
TMass_Radion_bkg.SetLineColor(2)
TMass_Radion_bkg.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_Radion_2000, "TMass_Radion_2000", "l")
leg.AddEntry(TMass_Radion_bkg, "TMass_Radion_bkg", "l")
leg.Draw()

c59.SetLogy()
c59.Update()
y_max = TMass_Radion_bkg.GetMaximum()
TMass_Radion_2000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10
c59.SaveAs('out59.pdf')
'''


c60=TCanvas()
dphi_H1_MET_2000=Rad_2000.Get("dphi_H1_MET")
dphi_H1_MET_2000.SetLineColor(1)
dphi_H1_MET_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H1_MET_2000.SetMaximum(dphi_H1_MET_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H1_MET_2000.DrawNormalized()        

dphi_H1_MET_bkg=background.Get("dphi_H1_MET")
dphi_H1_MET_bkg.SetLineColor(2)
dphi_H1_MET_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H1_MET_2000, "dphi_H1_MET_2000", "l")
leg.AddEntry(dphi_H1_MET_bkg, "dphi_H1_MET_bkg", "l")
leg.Draw()

c60.SaveAs('out60.pdf')



c61=TCanvas()
dphi_H2_MET_2000=Rad_2000.Get("dphi_H2_MET")
dphi_H2_MET_2000.SetLineColor(1)
dphi_H2_MET_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H2_MET_2000.SetMaximum(dphi_H2_MET_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H2_MET_2000.DrawNormalized()        

dphi_H2_MET_bkg=background.Get("dphi_H2_MET")
dphi_H2_MET_bkg.SetLineColor(2)
dphi_H2_MET_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H2_MET_2000, "dphi_H2_MET_2000", "l")
leg.AddEntry(dphi_H2_MET_bkg, "dphi_H2_MET_bkg", "l")
leg.Draw()

c61.SaveAs('out61.pdf')



c62=TCanvas()
dphi_rad_MET_2000=Rad_2000.Get("dphi_rad_MET")
dphi_rad_MET_2000.SetLineColor(1)
dphi_rad_MET_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_rad_MET_2000.SetMaximum(dphi_rad_MET_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_rad_MET_2000.DrawNormalized()        

dphi_rad_MET_bkg=background.Get("dphi_rad_MET")
dphi_rad_MET_bkg.SetLineColor(2)
dphi_rad_MET_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_rad_MET_2000, "dphi_rad_MET_2000", "l")
leg.AddEntry(dphi_rad_MET_bkg, "dphi_rad_MET_bkg", "l")
leg.Draw()

c62.SaveAs('out62.pdf')



c63=TCanvas()
dphi_H2_Rad_2000=Rad_2000.Get("dphi_H2_Rad")
dphi_H2_Rad_2000.SetLineColor(1)
dphi_H2_Rad_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H2_Rad_2000.SetMaximum(dphi_H2_Rad_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H2_Rad_2000.DrawNormalized()        

dphi_H2_Rad_bkg=background.Get("dphi_H2_Rad")
dphi_H2_Rad_bkg.SetLineColor(2)
dphi_H2_Rad_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H2_Rad_2000, "dphi_H2_Rad_2000", "l")
leg.AddEntry(dphi_H2_Rad_bkg, "dphi_H2_Rad_bkg", "l")
leg.Draw()

c63.SaveAs('out63.pdf')



c64=TCanvas()
dphi_H1_Rad_2000=Rad_2000.Get("dphi_H1_Rad")
dphi_H1_Rad_2000.SetLineColor(1)
dphi_H1_Rad_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H1_Rad_2000.SetMaximum(dphi_H1_Rad_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dphi_H1_Rad_2000.DrawNormalized()        

dphi_H1_Rad_bkg=background.Get("dphi_H1_Rad")
dphi_H1_Rad_bkg.SetLineColor(2)
dphi_H1_Rad_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H1_Rad_2000, "dphi_H1_Rad_2000", "l")
leg.AddEntry(dphi_H1_Rad_bkg, "dphi_H1_Rad_bkg", "l")
leg.Draw()

c64.SaveAs('out64.pdf')



c65=TCanvas()
dr_H1_Rad_2000=Rad_2000.Get("dr_H1_Rad")
dr_H1_Rad_2000.SetLineColor(1)
dr_H1_Rad_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dr_H1_Rad_2000.SetMaximum(dr_H1_Rad_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dr_H1_Rad_2000.DrawNormalized()        

dr_H1_Rad_bkg=background.Get("dr_H1_Rad")
dr_H1_Rad_bkg.SetLineColor(2)
dr_H1_Rad_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dr_H1_Rad_2000, "dr_H1_Rad_2000", "l")
leg.AddEntry(dr_H1_Rad_bkg, "dr_H1_Rad_bkg", "l")
leg.Draw()

c65.SaveAs('out65.pdf')



c66=TCanvas()
dr_H2_Rad_2000=Rad_2000.Get("dr_H2_Rad")
dr_H2_Rad_2000.SetLineColor(1)
dr_H2_Rad_2000.SetMinimum(0)  # Set the minimum value for the y-axis
dr_H2_Rad_2000.SetMaximum(dr_H2_Rad_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
dr_H2_Rad_2000.DrawNormalized()        

dr_H2_Rad_bkg=background.Get("dr_H2_Rad")
dr_H2_Rad_bkg.SetLineColor(2)
dr_H2_Rad_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dr_H2_Rad_2000, "dr_H2_Rad_2000", "l")
leg.AddEntry(dr_H2_Rad_bkg, "dr_H2_Rad_bkg", "l")
leg.Draw()

c66.SaveAs('out66.pdf')



c67=TCanvas()
radion_pt_2000=Rad_2000.Get("radion_pt")
radion_pt_2000.SetLineColor(1)
radion_pt_2000.SetMinimum(0)  # Set the minimum value for the y-axis
radion_pt_2000.SetMaximum(radion_pt_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
radion_pt_2000.DrawNormalized()        

radion_pt_bkg=background.Get("radion_pt")
radion_pt_bkg.SetLineColor(2)
radion_pt_bkg.DrawNormalized('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(radion_pt_2000, "radion_pt_2000", "l")
leg.AddEntry(radion_pt_bkg, "radion_pt_bkg", "l")
leg.Draw()

c67.SaveAs('out67.pdf')




c68=TCanvas()
radion_eta_2000=Rad_2000.Get("radion_eta")
radion_eta_2000.SetLineColor(1)
radion_eta_2000.SetMinimum(0)  # Set the minimum value for the y-axis
radion_eta_2000.SetMaximum(radion_eta_2000.GetMaximum()*3)  # Set the maximum value for the y-axis
radion_eta_2000.DrawNormalized()        

radion_eta_bkg=background.Get("radion_eta")
radion_eta_bkg.SetLineColor(2)
radion_eta_bkg.DrawNormalized('same')


leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(radion_eta_2000, "radion_eta_2000", "l")
leg.AddEntry(radion_eta_bkg, "radion_eta_2000", "l")
leg.Draw()

c68.SaveAs('out68.pdf')
