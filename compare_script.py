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

'''
c=TCanvas()
H1_vismass_1000=Rad_1000.Get("higgs1_vis_mass")
H1_vismass_1000.SetLineColor(1)
H1_vismass_1000.Draw()        

H1_vismass_2000=Rad_2000.Get("higgs1_vis_mass")
H1_vismass_2000.SetLineColor(2)
H1_vismass_2000.Draw('same')

H1_vismass_3000=Rad_3000.Get("higgs1_vis_mass")
H1_vismass_3000.SetLineColor(4)
H1_vismass_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(H1_vismass_1000, "H1_vismass_1000", "l")
leg.AddEntry(H1_vismass_2000, "H1_vismass_2000", "l")
leg.AddEntry(H1_vismass_3000, "H1_vismass_3000", "l")
leg.Draw()

H1_vismass_1000.SetMinimum(0)  # Set the minimum value for the y-axis
H1_vismass_1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c.SaveAs('out.pdf')

c2=TCanvas()
H2_vismass_1000=Rad_1000.Get("higgs2_vis_mass")
H2_vismass_1000.SetLineColor(1)
H2_vismass_1000.Draw()        

H2_vismass_2000=Rad_2000.Get("higgs2_vis_mass")
H2_vismass_2000.SetLineColor(2)
H2_vismass_2000.Draw('same')

H2_vismass_3000=Rad_3000.Get("higgs2_vis_mass")
H2_vismass_3000.SetLineColor(4)
H2_vismass_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(H2_vismass_1000, "H2_vismass_1000", "l")
leg.AddEntry(H2_vismass_2000, "H2_vismass_2000", "l")
leg.AddEntry(H2_vismass_3000, "H2_vismass_3000", "l")
leg.Draw()

H2_vismass_1000.SetMinimum(0)  # Set the minimum value for the y-axis
H2_vismass_1000.SetMaximum(900)  # Set the maximum value for the y-axis

c2.SaveAs('out2.pdf')



c3=TCanvas()
radion_inv_mass1000=Rad_1000.Get("radion_inv_mass")
radion_inv_mass1000.SetLineColor(1)
radion_inv_mass1000.Draw()        

radion_inv_mass2000=Rad_2000.Get("radion_inv_mass")
radion_inv_mass2000.SetLineColor(2)
radion_inv_mass2000.Draw('same')

radion_inv_mass3000=Rad_3000.Get("radion_inv_mass")
radion_inv_mass3000.SetLineColor(4)
radion_inv_mass3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(radion_inv_mass1000, "radion_inv_mass1000", "l")
leg.AddEntry(radion_inv_mass2000, "radion_inv_mass2000", "l")
leg.AddEntry(radion_inv_mass3000, "radion_inv_mass3000", "l")
leg.Draw()

radion_inv_mass1000.SetMinimum(0)  # Set the minimum value for the y-axis
radion_inv_mass1000.SetMaximum(1000)  # Set the maximum value for the y-axis
c3.SaveAs('out3.pdf')


c4=TCanvas()
higgs1_dR1000=Rad_1000.Get("higgs1_dr")
higgs1_dR1000.SetLineColor(1)
higgs1_dR1000.Draw()        

higgs1_dR2000=Rad_2000.Get("higgs1_dr")
higgs1_dR2000.SetLineColor(2)
higgs1_dR2000.Draw('same')

higgs1_dR3000=Rad_3000.Get("higgs1_dr")
higgs1_dR3000.SetLineColor(4)
higgs1_dR3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(higgs1_dR1000, "higgs1_dR1000", "l")
leg.AddEntry(higgs1_dR2000, "higgs1_dR2000", "l")
leg.AddEntry(higgs1_dR3000, "higgs1_dR3000", "l")
leg.Draw()

higgs1_dR1000.SetMinimum(0)  # Set the minimum value for the y-axis
higgs1_dR1000.SetMaximum(2000)  # Set the maximum value for the y-axis

c4.SaveAs('out4.pdf')


c5=TCanvas()
higgs2_dR1000=Rad_1000.Get("higgs2_dr")
higgs2_dR1000.SetLineColor(1)
higgs2_dR1000.Draw()        

higgs2_dR2000=Rad_2000.Get("higgs2_dr")
higgs2_dR2000.SetLineColor(2)
higgs2_dR2000.Draw('same')

higgs2_dR3000=Rad_3000.Get("higgs2_dr")
higgs2_dR3000.SetLineColor(4)
higgs2_dR3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(higgs2_dR1000, "higgs2_dR1000", "l")
leg.AddEntry(higgs2_dR2000, "higgs2_dR2000", "l")
leg.AddEntry(higgs2_dR3000, "higgs2_dR3000", "l")
leg.Draw()

higgs2_dR1000.SetMinimum(0)  # Set the minimum value for the y-axis
higgs2_dR1000.SetMaximum(1450)  # Set the maximum value for the y-axis
c5.SaveAs('out5.pdf')


c6=TCanvas()
dr_HH1000=Rad_1000.Get("dr_HH")
dr_HH1000.SetLineColor(1)
dr_HH1000.Draw()        

dr_HH2000=Rad_2000.Get("dr_HH")
dr_HH2000.SetLineColor(2)
dr_HH2000.Draw('same')

dr_HH3000=Rad_3000.Get("dr_HH")
dr_HH3000.SetLineColor(4)
dr_HH3000.Draw('same')

leg = ROOT.TLegend(0.2, 0.75, 0.45, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dr_HH1000, "dr_HH1000", "l")
leg.AddEntry(dr_HH2000, "dr_HH2000", "l")
leg.AddEntry(dr_HH3000, "dr_HH3000", "l")
leg.Draw()

dr_HH1000.SetMinimum(0)  # Set the minimum value for the y-axis
dr_HH1000.SetMaximum(2000)  # Set the maximum value for the y-axis
c6.SaveAs('out6.pdf')


c7=TCanvas()
HT_rad_1000=Rad_1000.Get("HT")
HT_rad_1000.SetLineColor(1)
HT_rad_1000.Draw()        

HT_rad_2000=Rad_2000.Get("HT")
HT_rad_2000.SetLineColor(2)
HT_rad_2000.Draw('same')

HT_rad_3000=Rad_3000.Get("HT")
HT_rad_3000.SetLineColor(4)
HT_rad_3000.Draw('same')

leg = ROOT.TLegend(0.1, 0.75, 0.35, 0.9)
leg.SetLineColor(1)
leg.AddEntry(HT_rad_1000, "HT1000", "l")
leg.AddEntry(HT_rad_2000, "HT2000", "l")
leg.AddEntry(HT_rad_3000, "HT3000", "l")
leg.Draw()

HT_rad_1000.SetMinimum(0)  # Set the minimum value for the y-axis
HT_rad_1000.SetMaximum(1200)  # Set the maximum value for the y-axis
c7.SaveAs('out7.pdf')


c8=TCanvas()
min_dR_muon1000=Rad_1000.Get("min_dR_muon")
min_dR_muon1000.SetLineColor(1)
min_dR_muon1000.Draw()        

min_dR_muon2000=Rad_2000.Get("min_dR_muon")
min_dR_muon2000.SetLineColor(2)
min_dR_muon2000.Draw('same')

min_dR_muon3000=Rad_3000.Get("min_dR_muon")
min_dR_muon3000.SetLineColor(4)
min_dR_muon3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_muon1000, "min_dR_muon1000", "l")
leg.AddEntry(min_dR_muon2000, "min_dR_muon2000", "l")
leg.AddEntry(min_dR_muon3000, "min_dR_muon3000", "l")
leg.Draw()

c8.SetLogy()
c8.Update()
y_max = min_dR_muon3000.GetMaximum()
min_dR_muon1000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10


c8.SaveAs('out8.pdf')


c9=TCanvas()
min_dR_index_tau_muon1000=Rad_1000.Get("min_dR_index_tau_muon")
min_dR_index_tau_muon1000.SetLineColor(1)
min_dR_index_tau_muon1000.Draw()        

min_dR_index_tau_muon2000=Rad_2000.Get("min_dR_index_tau_muon")
min_dR_index_tau_muon2000.SetLineColor(2)
min_dR_index_tau_muon2000.Draw('same')

min_dR_index_tau_muon3000=Rad_3000.Get("min_dR_index_tau_muon")
min_dR_index_tau_muon3000.SetLineColor(4)
min_dR_index_tau_muon3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_index_tau_muon1000, "min_dR_index_tau_muon1000", "l")
leg.AddEntry(min_dR_index_tau_muon2000, "min_dR_index_tau_muon2000", "l")
leg.AddEntry(min_dR_index_tau_muon3000, "min_dR_index_tau_muon3000", "l")
leg.Draw()

min_dR_index_tau_muon1000.SetMinimum(0)  # Set the minimum value for the y-axis
min_dR_index_tau_muon1000.SetMaximum(6000)  # Set the maximum value for the y-axis
c9.SaveAs('out9.pdf')



c10=TCanvas()
min_dR_electron1000=Rad_1000.Get("min_dR_electron")
min_dR_electron1000.SetLineColor(1)
min_dR_electron1000.Draw()        

min_dR_electron2000=Rad_2000.Get("min_dR_electron")
min_dR_electron2000.SetLineColor(2)
min_dR_electron2000.Draw('same')

min_dR_electron3000=Rad_3000.Get("min_dR_electron")
min_dR_electron3000.SetLineColor(4)
min_dR_electron3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_electron1000, "min_dR_electron1000", "l")
leg.AddEntry(min_dR_electron2000, "min_dR_electron2000", "l")
leg.AddEntry(min_dR_electron3000, "min_dR_electron3000", "l")
leg.Draw()



c10.SetLogy()
c10.Update()
y_max = min_dR_electron3000.GetMaximum()
min_dR_electron1000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10

c10.SaveAs('out10.pdf')


c11=TCanvas()
min_dR_index_tau_ele1000=Rad_1000.Get("min_dR_index_tau_ele")
min_dR_index_tau_ele1000.SetLineColor(1)
min_dR_index_tau_ele1000.Draw()        

min_dR_index_tau_ele2000=Rad_2000.Get("min_dR_index_tau_ele")
min_dR_index_tau_ele2000.SetLineColor(2)
min_dR_index_tau_ele2000.Draw('same')

min_dR_index_tau_ele3000=Rad_3000.Get("min_dR_index_tau_ele")
min_dR_index_tau_ele3000.SetLineColor(4)
min_dR_index_tau_ele3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(min_dR_index_tau_ele1000, "min_dR_index_tau_ele1000", "l")
leg.AddEntry(min_dR_index_tau_ele2000, "min_dR_index_tau_ele2000", "l")
leg.AddEntry(min_dR_index_tau_ele3000, "min_dR_index_tau_ele3000", "l")
leg.Draw()

min_dR_index_tau_ele1000.SetMinimum(0)  # Set the minimum value for the y-axis
min_dR_index_tau_ele1000.SetMaximum(6000)  # Set the maximum value for the y-axis
c11.SaveAs('out11.pdf')



c12=TCanvas()
ratio1000=Rad_1000.Get("ratio")
ratio1000.SetLineColor(1)
ratio1000.Draw()        

ratio2000=Rad_2000.Get("ratio")
ratio2000.SetLineColor(2)
ratio2000.Draw('same')

ratio3000=Rad_3000.Get("ratio")
ratio3000.SetLineColor(4)
ratio3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(ratio1000, "ratio1000", "l")
leg.AddEntry(ratio2000, "ratio2000", "l")
leg.AddEntry(ratio3000, "ratio3000", "l")
leg.Draw()

ratio1000.SetMinimum(0)  # Set the minimum value for the y-axis
ratio1000.SetMaximum(11000)  # Set the maximum value for the y-axis
c12.SaveAs('out12.pdf')
'''

c13=TCanvas()
pfMET1000=Rad_1000.Get("MET")
pfMET1000.SetLineColor(1)
pfMET1000.Draw()        

pfMET2000=Rad_2000.Get("MET")
pfMET2000.SetLineColor(2)
pfMET2000.Draw('same')

pfMET3000=Rad_3000.Get("MET")
pfMET3000.SetLineColor(4)
pfMET3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(pfMET1000, "MET1000", "l")
leg.AddEntry(pfMET2000, "MET2000", "l")
leg.AddEntry(pfMET3000, "MET3000", "l")
leg.Draw()

pfMET1000.SetMinimum(0)  # Set the minimum value for the y-axis
pfMET1000.SetMaximum(1000)  # Set the maximum value for the y-axis
c13.SaveAs('out13.pdf')
'''


c14=TCanvas()
ratio2_1000=Rad_1000.Get("ratio2")
ratio2_1000.SetLineColor(1)
ratio2_1000.Draw()        

ratio2_2000=Rad_2000.Get("ratio2")
ratio2_2000.SetLineColor(2)
ratio2_2000.Draw('same')

ratio2_3000=Rad_3000.Get("ratio2")
ratio2_3000.SetLineColor(4)
ratio2_3000.Draw('same')

leg = ROOT.TLegend(0.65, 0.75, 0.9, 0.9)
leg.SetLineColor(1)
leg.AddEntry(ratio2_1000, "ratio2_1000", "l")
leg.AddEntry(ratio2_2000, "ratio2_2000", "l")
leg.AddEntry(ratio2_3000, "ratio2_3000", "l")
leg.Draw()

ratio2_1000.SetMinimum(0)  # Set the minimum value for the y-axis
ratio2_1000.SetMaximum(11000)  # Set the maximum value for the y-axis
c14.SaveAs('out14.pdf')
'''

'''
c15=TCanvas()
lead_tau_iso1000=Rad_1000.Get("lead_tau_iso")
lead_tau_iso1000.SetLineColor(1)
lead_tau_iso1000.Draw()        

lead_tau_iso2000=Rad_2000.Get("lead_tau_iso")
lead_tau_iso2000.SetLineColor(2)
lead_tau_iso2000.Draw('same')

lead_tau_iso3000=Rad_3000.Get("lead_tau_iso")
lead_tau_iso3000.SetLineColor(4)
lead_tau_iso3000.Draw('same')

leg = ROOT.TLegend(0.25, 0.75, 0.5, 0.9)
leg.SetLineColor(1)
leg.AddEntry(lead_tau_iso1000, "lead_tau_iso1000", "l")
leg.AddEntry(lead_tau_iso2000, "lead_tau_iso2000", "l")
leg.AddEntry(lead_tau_iso3000, "lead_tau_iso3000", "l")
leg.Draw()

c15.SetLogy()
c15.Update()
y_max = lead_tau_iso3000.GetMaximum()
lead_tau_iso1000.GetYaxis().SetRangeUser(0.1, 20 * y_max)  # Increase the y-axis range by a factor of 10

c15.SaveAs('out15.pdf')





c16=TCanvas()
subtau_iso1000=Rad_1000.Get("subtau_iso")
subtau_iso1000.SetLineColor(1)
subtau_iso1000.Draw()        

subtau_iso2000=Rad_2000.Get("subtau_iso")
subtau_iso2000.SetLineColor(2)
subtau_iso2000.Draw('same')

subtau_iso3000=Rad_3000.Get("subtau_iso")
subtau_iso3000.SetLineColor(4)
subtau_iso3000.Draw('same')

leg = ROOT.TLegend(0.25, 0.75, 0.5, 0.9)
leg.SetLineColor(1)
leg.AddEntry(subtau_iso1000, "subtau_iso1000", "l")
leg.AddEntry(subtau_iso2000, "subtau_iso2000", "l")
leg.AddEntry(subtau_iso3000, "subtau_iso3000", "l")
leg.Draw()

c16.SetLogy()
c16.Update()
y_max = subtau_iso3000.GetMaximum()
subtau_iso1000.GetYaxis().SetRangeUser(0.1, 20 * y_max)  # Increase the y-axis range by a factor of 10

c16.SaveAs('out16.pdf')





c17=TCanvas()
third_tau_iso1000=Rad_1000.Get("third_tau_iso")
third_tau_iso1000.SetLineColor(1)
third_tau_iso1000.Draw()        

third_tau_iso2000=Rad_2000.Get("third_tau_iso")
third_tau_iso2000.SetLineColor(2)
third_tau_iso2000.Draw('same')

third_tau_iso3000=Rad_3000.Get("third_tau_iso")
third_tau_iso3000.SetLineColor(4)
third_tau_iso3000.Draw('same')

leg = ROOT.TLegend(0.25, 0.75, 0.5, 0.9)
leg.SetLineColor(1)
leg.AddEntry(third_tau_iso1000, "third_tau_iso1000", "l")
leg.AddEntry(third_tau_iso2000, "third_tau_iso2000", "l")
leg.AddEntry(third_tau_iso3000, "third_tau_iso3000", "l")
leg.Draw()

c17.SetLogy()
c17.Update()
y_max = third_tau_iso3000.GetMaximum()
third_tau_iso1000.GetYaxis().SetRangeUser(0.1, 20 * y_max)  # Increase the y-axis range by a factor of 10

c17.SaveAs('out17.pdf')




c18=TCanvas()
fourth_tau_iso1000=Rad_1000.Get("fourth_tau_iso")
fourth_tau_iso1000.SetLineColor(1)
fourth_tau_iso1000.Draw()        

fourth_tau_iso2000=Rad_2000.Get("fourth_tau_iso")
fourth_tau_iso2000.SetLineColor(2)
fourth_tau_iso2000.Draw('same')

fourth_tau_iso3000=Rad_3000.Get("fourth_tau_iso")
fourth_tau_iso3000.SetLineColor(4)
fourth_tau_iso3000.Draw('same')

leg = ROOT.TLegend(0.25, 0.75, 0.5, 0.9)
leg.SetLineColor(1)
leg.AddEntry(fourth_tau_iso1000, "fourth_tau_iso1000", "l")
leg.AddEntry(fourth_tau_iso2000, "fourth_tau_iso2000", "l")
leg.AddEntry(fourth_tau_iso3000, "fourth_tau_iso3000", "l")
leg.Draw()

c18.SetLogy()
c18.Update()
y_max = fourth_tau_iso3000.GetMaximum()
fourth_tau_iso1000.GetYaxis().SetRangeUser(0.1, 20 * y_max)  # Increase the y-axis range by a factor of 10

c18.SaveAs('out18.pdf')



c19=TCanvas()
LeadingBoostedTauPt_1000=Rad_1000.Get("LeadingBoostedTauPt_")
LeadingBoostedTauPt_1000.SetLineColor(1)
LeadingBoostedTauPt_1000.Draw()        

LeadingBoostedTauPt_2000=Rad_2000.Get("LeadingBoostedTauPt_")
LeadingBoostedTauPt_2000.SetLineColor(2)
LeadingBoostedTauPt_2000.Draw('same')

LeadingBoostedTauPt_3000=Rad_3000.Get("LeadingBoostedTauPt_")
LeadingBoostedTauPt_3000.SetLineColor(4)
LeadingBoostedTauPt_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(LeadingBoostedTauPt_1000, "LeadingBoostedTauPt_1000", "l")
leg.AddEntry(LeadingBoostedTauPt_2000, "LeadingBoostedTauPt_2000", "l")
leg.AddEntry(LeadingBoostedTauPt_3000, "LeadingBoostedTauPt_3000", "l")
leg.Draw()

LeadingBoostedTauPt_1000.SetMinimum(0)  # Set the minimum value for the y-axis
LeadingBoostedTauPt_1000.SetMaximum(700)  # Set the maximum value for the y-axis

c19.SaveAs('out19.pdf')


c20=TCanvas()
SubLeadingBoostedTauPt_1000=Rad_1000.Get("SubLeadingBoostedTauPt_")
SubLeadingBoostedTauPt_1000.SetLineColor(1)
SubLeadingBoostedTauPt_1000.Draw()        

SubLeadingBoostedTauPt_2000=Rad_2000.Get("SubLeadingBoostedTauPt_")
SubLeadingBoostedTauPt_2000.SetLineColor(2)
SubLeadingBoostedTauPt_2000.Draw('same')

SubLeadingBoostedTauPt_3000=Rad_3000.Get("SubLeadingBoostedTauPt_")
SubLeadingBoostedTauPt_3000.SetLineColor(4)
SubLeadingBoostedTauPt_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(SubLeadingBoostedTauPt_1000, "SubLeadingBoostedTauPt_1000", "l")
leg.AddEntry(SubLeadingBoostedTauPt_2000, "SubLeadingBoostedTauPt_2000", "l")
leg.AddEntry(SubLeadingBoostedTauPt_3000, "SubLeadingBoostedTauPt_3000", "l")
leg.Draw()

SubLeadingBoostedTauPt_1000.SetMinimum(0)  # Set the minimum value for the y-axis
SubLeadingBoostedTauPt_1000.SetMaximum(900)  # Set the maximum value for the y-axis

c20.SaveAs('out20.pdf')



c21=TCanvas()
ThirdBoostedTauPt_1000=Rad_1000.Get("ThirdBoostedTauPt_")
ThirdBoostedTauPt_1000.SetLineColor(1)
ThirdBoostedTauPt_1000.Draw()        

ThirdBoostedTauPt_2000=Rad_2000.Get("ThirdBoostedTauPt_")
ThirdBoostedTauPt_2000.SetLineColor(2)
ThirdBoostedTauPt_2000.Draw('same')

ThirdBoostedTauPt_3000=Rad_3000.Get("ThirdBoostedTauPt_")
ThirdBoostedTauPt_3000.SetLineColor(4)
ThirdBoostedTauPt_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(ThirdBoostedTauPt_1000, "ThirdBoostedTauPt_1000", "l")
leg.AddEntry(ThirdBoostedTauPt_2000, "ThirdBoostedTauPt_2000", "l")
leg.AddEntry(ThirdBoostedTauPt_3000, "ThirdBoostedTauPt_3000", "l")
leg.Draw()

ThirdBoostedTauPt_1000.SetMinimum(0)  # Set the minimum value for the y-axis
ThirdBoostedTauPt_1000.SetMaximum(1000)  # Set the maximum value for the y-axis

c21.SaveAs('out21.pdf')



c22=TCanvas()
FourthBoostedTauPt_1000=Rad_1000.Get("FourthBoostedTauPt_")
FourthBoostedTauPt_1000.SetLineColor(1)
FourthBoostedTauPt_1000.Draw()        

FourthBoostedTauPt_2000=Rad_2000.Get("FourthBoostedTauPt_")
FourthBoostedTauPt_2000.SetLineColor(2)
FourthBoostedTauPt_2000.Draw('same')

FourthBoostedTauPt_3000=Rad_3000.Get("FourthBoostedTauPt_")
FourthBoostedTauPt_3000.SetLineColor(4)
FourthBoostedTauPt_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(FourthBoostedTauPt_1000, "FourthBoostedTauPt_1000", "l")
leg.AddEntry(FourthBoostedTauPt_2000, "FourthBoostedTauPt_2000", "l")
leg.AddEntry(FourthBoostedTauPt_3000, "FourthBoostedTauPt_3000", "l")
leg.Draw()

FourthBoostedTauPt_1000.SetMinimum(0)  # Set the minimum value for the y-axis
FourthBoostedTauPt_1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c22.SaveAs('out22.pdf')



c23=TCanvas()
fourth_tau_mass1000=Rad_1000.Get("fourth_tau_mass")
fourth_tau_mass1000.SetLineColor(1)
fourth_tau_mass1000.Draw()        

fourth_tau_mass2000=Rad_2000.Get("fourth_tau_mass")
fourth_tau_mass2000.SetLineColor(2)
fourth_tau_mass2000.Draw('same')

fourth_tau_mass3000=Rad_3000.Get("fourth_tau_mass")
fourth_tau_mass3000.SetLineColor(4)
fourth_tau_mass3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(fourth_tau_mass1000, "fourth_tau_mass_1000", "l")
leg.AddEntry(fourth_tau_mass2000, "fourth_tau_mass_2000", "l")
leg.AddEntry(fourth_tau_mass3000, "fourth_tau_mass_3000", "l")
leg.Draw()

fourth_tau_mass1000.SetMinimum(0)  # Set the minimum value for the y-axis
fourth_tau_mass1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c23.SaveAs('out23.pdf')


c24=TCanvas()
lead_tau_mass1000=Rad_1000.Get("lead_tau_mass")
lead_tau_mass1000.SetLineColor(1)
lead_tau_mass1000.Draw()        

lead_tau_mass2000=Rad_2000.Get("lead_tau_mass")
lead_tau_mass2000.SetLineColor(2)
lead_tau_mass2000.Draw('same')

lead_tau_mass3000=Rad_3000.Get("lead_tau_mass")
lead_tau_mass3000.SetLineColor(4)
lead_tau_mass3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(lead_tau_mass1000, "lead_tau_mass1000", "l")
leg.AddEntry(lead_tau_mass2000, "lead_tau_mass2000", "l")
leg.AddEntry(lead_tau_mass3000, "lead_tau_mass3000", "l")
leg.Draw()

lead_tau_mass1000.SetMinimum(0)  # Set the minimum value for the y-axis
lead_tau_mass1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c24.SaveAs('out24.pdf')


c25=TCanvas()
sub_tau_mass1000=Rad_1000.Get("sub_tau_mass")
sub_tau_mass1000.SetLineColor(1)
sub_tau_mass1000.Draw()        

sub_tau_mass2000=Rad_2000.Get("sub_tau_mass")
sub_tau_mass2000.SetLineColor(2)
sub_tau_mass2000.Draw('same')

sub_tau_mass3000=Rad_3000.Get("sub_tau_mass")
sub_tau_mass3000.SetLineColor(4)
sub_tau_mass3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(sub_tau_mass1000, "sub_tau_mass1000", "l")
leg.AddEntry(sub_tau_mass2000, "sub_tau_mass2000", "l")
leg.AddEntry(sub_tau_mass3000, "sub_tau_mass3000", "l")
leg.Draw()

sub_tau_mass1000.SetMinimum(0)  # Set the minimum value for the y-axis
sub_tau_mass1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c25.SaveAs('out25.pdf')



c26=TCanvas()
third_tau_mass1000=Rad_1000.Get("third_tau_mass")
third_tau_mass1000.SetLineColor(1)
third_tau_mass1000.Draw()        

third_tau_mass2000=Rad_2000.Get("third_tau_mass")
third_tau_mass2000.SetLineColor(2)
third_tau_mass2000.Draw('same')

third_tau_mass3000=Rad_3000.Get("third_tau_mass")
third_tau_mass3000.SetLineColor(4)
third_tau_mass3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(third_tau_mass1000, "third_tau_mass1000", "l")
leg.AddEntry(third_tau_mass2000, "third_tau_mass2000", "l")
leg.AddEntry(third_tau_mass3000, "third_tau_mass3000", "l")
leg.Draw()

third_tau_mass1000.SetMinimum(0)  # Set the minimum value for the y-axis
third_tau_mass1000.SetMaximum(1200)  # Set the maximum value for the y-axis

c26.SaveAs('out26.pdf')




c27=TCanvas()
dphi1000=Rad_1000.Get("dphi_HH")
dphi1000.SetLineColor(1)
dphi1000.Draw()        

dphi2000=Rad_2000.Get("dphi_HH")
dphi2000.SetLineColor(2)
dphi2000.Draw('same')

dphi3000=Rad_3000.Get("dphi_HH")
dphi3000.SetLineColor(4)
dphi3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi1000, "dphiHH_1000", "l")
leg.AddEntry(dphi2000, "dphiHH_2000", "l")
leg.AddEntry(dphi3000, "dphiHH_3000", "l")
leg.Draw()

dphi1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi1000.SetMaximum(3000)  # Set the maximum value for the y-axis

c27.SaveAs('out27.pdf')




c28=TCanvas()
dphi_H1_1000=Rad_1000.Get("dphi_H1")
dphi_H1_1000.SetLineColor(1)
dphi_H1_1000.Draw()        

dphi_H1_2000=Rad_2000.Get("dphi_H1")
dphi_H1_2000.SetLineColor(2)
dphi_H1_2000.Draw('same')

dphi_H1_3000=Rad_3000.Get("dphi_H1")
dphi_H1_3000.SetLineColor(4)
dphi_H1_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H1_1000, "dphi_H1_1000", "l")
leg.AddEntry(dphi_H1_2000, "dphi_H1_2000", "l")
leg.AddEntry(dphi_H1_3000, "dphi_H1_3000", "l")
leg.Draw()

dphi_H1_1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H1_1000.SetMaximum(3000)  # Set the maximum value for the y-axis

c28.SaveAs('out28.pdf')


c29=TCanvas()
dphi_H2_1000=Rad_1000.Get("dphi_H2")
dphi_H2_1000.SetLineColor(1)
dphi_H2_1000.Draw()        

dphi_H2_2000=Rad_2000.Get("dphi_H2")
dphi_H2_2000.SetLineColor(2)
dphi_H2_2000.Draw('same')

dphi_H2_3000=Rad_3000.Get("dphi_H2")
dphi_H2_3000.SetLineColor(4)
dphi_H2_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H2_1000, "dphi_H21000", "l")
leg.AddEntry(dphi_H2_2000, "dphi_H22000", "l")
leg.AddEntry(dphi_H2_3000, "dphi_H23000", "l")
leg.Draw()

dphi_H2_1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H2_1000.SetMaximum(2000)  # Set the maximum value for the y-axis

c29.SaveAs('out29.pdf')
'''



c30=TCanvas()
TMass_H1_1000=Rad_1000.Get("TMass_H1")
TMass_H1_1000.SetLineColor(1)
TMass_H1_1000.Draw()        

TMass_H1_2000=Rad_2000.Get("TMass_H1")
TMass_H1_2000.SetLineColor(2)
TMass_H1_2000.Draw('same')

TMass_H1_3000=Rad_3000.Get("TMass_H1")
TMass_H1_3000.SetLineColor(4)
TMass_H1_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_H1_1000, "TMass_H1_1000", "l")
leg.AddEntry(TMass_H1_2000, "TMass_H1_2000", "l")
leg.AddEntry(TMass_H1_3000, "TMass_H1_3000", "l")
leg.Draw()

c30.SetLogy()
c30.Update()
y_max = TMass_H1_3000.GetMaximum()
TMass_H1_1000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10

c30.SaveAs('out30.pdf')



c31=TCanvas()
TMass_H2_1000=Rad_1000.Get("TMass_H2")
TMass_H2_1000.SetLineColor(1)
TMass_H2_1000.Draw()        

TMass_H2_2000=Rad_2000.Get("TMass_H2")
TMass_H2_2000.SetLineColor(2)
TMass_H2_2000.Draw('same')

TMass_H2_3000=Rad_3000.Get("TMass_H2")
TMass_H2_3000.SetLineColor(4)
TMass_H2_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_H2_1000, "TMass_H2_1000", "l")
leg.AddEntry(TMass_H2_2000, "TMass_H2_2000", "l")
leg.AddEntry(TMass_H2_3000, "TMass_H2_3000", "l")
leg.Draw()

c31.SetLogy()
c31.Update()
y_max = TMass_H2_3000.GetMaximum()
TMass_H2_1000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10

c31.SaveAs('out31.pdf')



c32=TCanvas()
TMass_Radion_1000=Rad_1000.Get("TMass_Radion")
TMass_Radion_1000.SetLineColor(1)
TMass_Radion_1000.Draw()        

TMass_Radion_2000=Rad_2000.Get("TMass_Radion")
TMass_Radion_2000.SetLineColor(2)
TMass_Radion_2000.Draw('same')

TMass_Radion_3000=Rad_3000.Get("TMass_Radion")
TMass_Radion_3000.SetLineColor(4)
TMass_Radion_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(TMass_Radion_1000, "TMass_Radion_1000", "l")
leg.AddEntry(TMass_Radion_2000, "TMass_Radion_2000", "l")
leg.AddEntry(TMass_Radion_3000, "TMass_Radion_3000", "l")
leg.Draw()

c32.SetLogy()
c32.Update()
y_max = TMass_Radion_3000.GetMaximum()
TMass_Radion_1000.GetYaxis().SetRangeUser(0.1, 10 * y_max)  # Increase the y-axis range by a factor of 10

c32.SaveAs('out32.pdf')



'''
c33=TCanvas()
dphi_H1_MET_1000=Rad_1000.Get("dphi_H1_MET")
dphi_H1_MET_1000.SetLineColor(1)
dphi_H1_MET_1000.Draw()        

dphi_H1_MET_2000=Rad_2000.Get("dphi_H1_MET")
dphi_H1_MET_2000.SetLineColor(2)
dphi_H1_MET_2000.Draw('same')

dphi_H1_MET_3000=Rad_3000.Get("dphi_H1_MET")
dphi_H1_MET_3000.SetLineColor(4)
dphi_H1_MET_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H1_MET_1000, "dphi_H1_MET_1000", "l")
leg.AddEntry(dphi_H1_MET_2000, "dphi_H1_MET_2000", "l")
leg.AddEntry(dphi_H1_MET_3000, "dphi_H1_MET_3000", "l")
leg.Draw()

dphi_H1_MET_1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H1_MET_1000.SetMaximum(1500)  # Set the maximum value for the y-axis


c33.SaveAs('out33.pdf')



c34=TCanvas()
dphi_H2_MET_1000=Rad_1000.Get("dphi_H2_MET")
dphi_H2_MET_1000.SetLineColor(1)
dphi_H2_MET_1000.Draw()        

dphi_H2_MET_2000=Rad_2000.Get("dphi_H2_MET")
dphi_H2_MET_2000.SetLineColor(2)
dphi_H2_MET_2000.Draw('same')

dphi_H2_MET_3000=Rad_3000.Get("dphi_H2_MET")
dphi_H2_MET_3000.SetLineColor(4)
dphi_H2_MET_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_H2_MET_1000, "dphi_H2_MET_1000", "l")
leg.AddEntry(dphi_H2_MET_2000, "dphi_H2_MET_2000", "l")
leg.AddEntry(dphi_H2_MET_3000, "dphi_H2_MET_3000", "l")
leg.Draw()

dphi_H2_MET_1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_H2_MET_1000.SetMaximum(1500)  # Set the maximum value for the y-axis



c34.SaveAs('out34.pdf')



c35=TCanvas()
dphi_rad_MET_1000=Rad_1000.Get("dphi_rad_MET")
dphi_rad_MET_1000.SetLineColor(1)
dphi_rad_MET_1000.Draw()        

dphi_rad_MET_2000=Rad_2000.Get("dphi_rad_MET")
dphi_rad_MET_2000.SetLineColor(2)
dphi_rad_MET_2000.Draw('same')

dphi_rad_MET_3000=Rad_3000.Get("dphi_rad_MET")
dphi_rad_MET_3000.SetLineColor(4)
dphi_rad_MET_3000.Draw('same')

leg = ROOT.TLegend(0.50, 0.75, 0.75, 0.9)
leg.SetLineColor(1)
leg.AddEntry(dphi_rad_MET_1000, "dphi_rad_MET_1000", "l")
leg.AddEntry(dphi_rad_MET_2000, "dphi_rad_MET_2000", "l")
leg.AddEntry(dphi_rad_MET_3000, "dphi_rad_MET_3000", "l")
leg.Draw()

dphi_rad_MET_1000.SetMinimum(0)  # Set the minimum value for the y-axis
dphi_rad_MET_1000.SetMaximum(1500)  # Set the maximum value for the y-axis


c35.SaveAs('out35.pdf')
'''










