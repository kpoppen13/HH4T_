# To plots the distributions
#
import plotter_4t


plots = [
    #('vis_mass', 'vis_mass', 1), 
    #('vis_mass2', 'vis_mass2', 1),
    #("pfMET", pfMET, 5),
    #("higgs_pT", higgs_pT, 5),
    #('higgs_pT2', 'higgs_pT2', 5),
    #('rad_eta', 'rad_eta', 1),
    #('radion_pt', 'radion_pt', 1),
    ('radion_inv_mass', 'radion_inv_mass', 1)
    #('HT', 'HT', 5),
    #('higgs1_dr', 'higgs1_dr', 1),
    #('higgs2_dr', 'higgs2_dr', 1),
    #('dphi_H1', 'dphi_H1', 5),
    #('dphi_H2', 'dphi_H2', 5),
    #('dr_HH', 'dr_HH', 5)
    #('dphi_HH', 'dphi_HH', 5),
    #('TMass_H1', 'TMass_H1', 5),
    #('TMass_H2', 'TMass_H2', 5),
    #('TMass_Radion', 'TMass_Radion', 5),
    #('dphi_H1_MET', 'dphi_H1_MET', 5),
    #('dphi_H2_MET', 'dphi_H2_MET', 5),
    #('dphi_rad_MET', 'dphi_rad_MET', 5),
    #('dphi_H2_Rad', 'dphi_H2_Rad', 5),
    #('dph_H1_Rad', 'dph_H1_Rad', 5), 
    #('dr_H2_Rad', 'dr_H2_Rad', 5),
    #('dr_H1_Rad', 'dr_H1_Rad', 5),
    #('tau1_h1_pt', 'tau1_h1_pt', 5),
    #('tau2_h1_pt', 'tau2_h1_pt', 5),
    #('tau1_h2_pt', 'tau1_h2_pt'),
    #('tau2_h2_pt', 'tau2_h2_pt', 5),
    #('AK8Mass', 'AK8Mass', 5),
    #('AK8Pt', 'AK8Pt', 5)
#    ('NN_disc_ZTT', 'D_{NN} (ZTT)', 3),
#    ('NN_disc_QCD', 'D_{NN} (QCD)', 3),
#    ('m_sv', 'm_{#tau#tau}', 3.0),
#    ('Met', 'Missing E_{T}', 3.0),
#    ('ht', 'ht', 3.0),
#    ('higgs_pT', 'Higgs p_{T}', 3.0),
#    ('higgs_m', 'Higgs mass', 3.0),
#    ('tmass', 'm_{T}', 3.0),
#    ('vis_mass', 'm_{Visible}', 3.0),
#    ('lep1Pt', '1st lepton pT', 3.0),
#    ('lep2Pt', '2nd lepton pT', 3.0),
#    ('dR_lep_lep', 'dR_{#tau #tau}', 3.0),
#    ('LeadJetPt', 'LeadJetPt', 3.0),
#    ('st', 'st', 3.0),
#    ('MuMatchedIsolation', 'BoostedTauRawIso matched to muon', 3.0),
#    ('EleMatchedIsolation', 'BoostedTauRawIso matched to ele', 3.0),
####    ('ZMass', 'ZMass', 3.0),
]

categories = ['_0jet']
#categories = ['_ztt']
#categories = ['_qcd','_signal','_ztt']

class PlotArgs():
    def __init__(self, input, year, category,channelName, variable, label, prefix, scale):
        self.input = input
        self.year = year
        self.category = category
        self.channelName = channelName
        self.variable = variable
        self.label = label
        self.prefix = prefix
        self.scale = scale

def main(args):
    for plot in plots:
        for category in categories:

            InputFile=args.input
            channel=''
            channelName=''
            year=0
            
            if '2016' in InputFile:
                year = 2016
            elif '2017' in InputFile:
                year = 2017
            elif '2018' in InputFile:
                year = 2018
            elif '2020' in InputFile:
                year = 2020
            else:
                print 'which year ???'



            
            channel = '4t'
            channelName='4t'
            '''
            if 'em2' in InputFile or '_em_' in InputFile:
                channel = 'em'
                channelName='em'
    #            treeName = 'emu_tree'
            elif 'me2' in InputFile or    '_me_' in InputFile:
#                channel = 'me'
                channel = 'em'
                channelName='me'
                treeName = 'mue_tree'
            elif 'mt2' in InputFile or '_mt_' in InputFile:
                channel = 'mt'
                channelName='mt'
                treeName = 'mutau_tree'
            elif 'et2' in InputFile  or  '_et_' in InputFile:
                channel = 'et'
                channelName='et'
    #            treeName = 'etau_tree'
            elif 'tt2' in InputFile  or  '_tt_' in InputFile:
                channel = 'tt'
                channelName='tt'
    #            treeName = 'tautau_tree'
            elif 'mm2' in InputFile:
                channel = 'mm'
                channelName='mm'
    #            treeName = 'mumu_tree'
            else:
                print 'which channel ???'
            '''


            inputs = PlotArgs(
                args.input,
                year,
                channel + category,
                channelName,
                plot[0],
                plot[1],
                args.prefix,
                plot[2]
            )
            plotter_4t.BuildPlot(inputs)

if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', required=True, help='path to input files')
    parser.add_argument('--prefix', '-p', required=True, help='prefix for files')
    main(parser.parse_args())