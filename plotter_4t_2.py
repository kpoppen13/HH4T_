import ROOT
from pprint import pprint
from collections import namedtuple
ROOT.gROOT.SetBatch(ROOT.kTRUE)
ROOT.gStyle.SetOptStat(0)


# short-hand
GetColor = ROOT.TColor.GetColor
black = ROOT.kBlack
no_color = 0


style_map_tuple = namedtuple('style_map_tuple', [
    'fill_color', 'line_color', 'line_style', 'line_width', 'marker_style'
])
style_map = {
    "out_data_eval": style_map_tuple(no_color, black, 1, 1, 8),
    
    "backgrounds": {
        "out_TTT_eval": style_map_tuple(GetColor(255, 165, 0), black, 1, 1, 1),
        "other_bkg_eval": style_map_tuple(GetColor(208, 376, 124), black, 1, 1, 1),
        "out_ZZ_eval": style_map_tuple(GetColor(408, 106, 154), black, 1, 1, 1),
        "out_DY_eval": style_map_tuple(GetColor(208, 126, 254), black, 1, 1, 1)
        },
    "EWK": {
        "out_VV_eval": style_map_tuple(GetColor(200, 282, 232), black, 1, 1, 1),
    },
    "signals": {
        "out_1000_eval": style_map_tuple(no_color, GetColor("#FF0000"), 1, 3, 1), 
        "out_2000_eval": style_map_tuple(no_color, GetColor("#00FF00"), 1, 3, 1),
        "out_3000_eval": style_map_tuple(no_color, GetColor("#0000FF"), 1, 3, 1)

    }
}

style_map_emu = {
 
    "out_data_eval": style_map_tuple(no_color, black, 1, 1, 8),

    "backgrounds": {
        "out_TTT_eval": style_map_tuple(GetColor(0, 0, 0), black, 1, 1, 1),
        "out_ZZ_eval": style_map_tuple(GetColor(408, 106, 154), black, 1, 1, 1),
        "other_bkg_eval": style_map_tuple(GetColor(208, 376, 124), black, 1, 1, 1),
        "out_DY_eval": style_map_tuple(GetColor(208, 126, 254), black, 1, 1, 1)

        },
    "EWK": {
        "out_VV_eval": style_map_tuple(GetColor(200, 282, 232), black, 1, 1, 1),
    },
    "signals": {
        "out_1000_eval": style_map_tuple(no_color, GetColor("#FF0000"), 1, 3, 1), 
        "out_2000_eval": style_map_tuple(no_color, GetColor("#00FF00"), 1, 3, 1),
        "out_3000_eval": style_map_tuple(no_color, GetColor("#0000FF"), 1, 3, 1)
    }
}



def ApplyStyle(ihist, styles):
    ihist.SetFillColor(styles.fill_color)
    ihist.SetLineColor(styles.line_color)
    ihist.SetLineStyle(styles.line_style)
    ihist.SetLineWidth(styles.line_width)
    ihist.SetMarkerStyle(styles.marker_style)
    return ihist


def createCanvas():
    can = ROOT.TCanvas('can', 'can', 432, 451)
    can.Divide(2, 1)

    pad1 = can.cd(1)
    pad1.SetLeftMargin(.12)
    pad1.cd()
    pad1.SetPad(0, .3, 1, 1)
    pad1.SetTopMargin(.1)
    pad1.SetBottomMargin(0.02)
#    pad1.SetLogy()
    pad1.SetTickx(1)
    pad1.SetTicky(1)

    pad2 = can.cd(2)
    pad2.SetLeftMargin(.12)
    pad2.SetPad(0, 0, 1, .3)
    pad2.SetTopMargin(0.06)
    pad2.SetBottomMargin(0.35)
    pad2.SetTickx(1)
    pad2.SetTicky(1)

    can.cd(1)
    return can

def formatStat(stat):
    stat.SetMarkerStyle(0)
    stat.SetLineWidth(2)
    stat.SetLineColor(0)
    stat.SetFillStyle(3004)
    stat.SetFillColor(ROOT.kBlack)
    return stat

def formatStack(stack):
    stack.GetXaxis().SetLabelSize(0)
    stack.GetYaxis().SetTitle('Events / Bin')
    stack.GetYaxis().SetTitleFont(42)
    stack.GetYaxis().SetTitleSize(.05)
    stack.GetYaxis().SetTitleOffset(1.2)
    stack.SetTitle('')
    stack.GetXaxis().SetNdivisions(505)


def fillLegend(data, backgrounds,backgrounds_EWK, signals, stat):
    leg = ROOT.TLegend(0.5, 0.45, 0.85, 0.85)
    leg.SetLineColor(0)
    leg.SetFillColor(0)
    leg.SetTextFont(61)
    leg.SetTextFont(42)
    leg.SetTextSize(0.045)

    leg.SetNColumns(2)

    # data
    leg.AddEntry(data, 'Data', 'lep')

    # signals
    leg.AddEntry(signals['out_1000_eval'], ' 1 TeV', 'l')
    leg.AddEntry(signals['out_2000_eval'], ' 2 TeV', 'l')
    leg.AddEntry(signals['out_3000_eval'], ' 3 TeV', 'l')

    # backgrounds
    leg.AddEntry(backgrounds['out_ZZ_eval'], 'ZZ4l', 'f')
    leg.AddEntry(backgrounds['out_TTT_eval'], 'TTbar', 'f')
    leg.AddEntry(backgrounds['out_DY_eval'], 'DY', 'f')
    leg.AddEntry(backgrounds_EWK['out_VV_eval'], 'VV', 'f')
    leg.AddEntry(backgrounds['other_bkg_eval'], 'other_bkg', 'f')

    # stat. uncertainty
    #leg.AddEntry(stat, 'Uncertainty', 'f')
    
    return leg
    
def formatPull(pull, title):
    pull.SetTitle('')
    pull.SetMaximum(2)  ## adjust ratio axis here
    pull.SetMinimum(0)  ## adjust ratio axis here
    pull.GetXaxis().SetTitle(title)
    pull.SetMarkerStyle(21)
    pull.GetXaxis().SetTitleSize(0.18)
    pull.GetXaxis().SetTitleOffset(0.8)
    pull.GetXaxis().SetTitleFont(42)
    pull.GetXaxis().SetLabelFont(42)
    pull.GetXaxis().SetLabelSize(.111)
    pull.GetXaxis().SetNdivisions(505)

    # pull.GetXaxis().SetLabelSize(0)
    # pull.GetXaxis().SetTitleSize(0)

    pull.GetYaxis().SetTitle('Obs. / Exp.')
    pull.GetYaxis().SetTitleSize(0.12)
    pull.GetYaxis().SetTitleFont(42)
    pull.GetYaxis().SetTitleOffset(.475)
    pull.GetYaxis().SetLabelSize(.12)
    pull.GetYaxis().SetNdivisions(204)
    return pull

def sigmaLines(data):
    low = data.GetBinLowEdge(1)
    high = data.GetBinLowEdge(data.GetNbinsX()) + \
        data.GetBinWidth(data.GetNbinsX())

    ## high line
    line1 = ROOT.TLine(low, 1.25, high, 1.25)
    line1.SetLineWidth(1)
    line1.SetLineStyle(3)
    line1.SetLineColor(ROOT.kBlack)

    ## low line
    line2 = ROOT.TLine(low, 0.75, high, 0.75)
    line2.SetLineWidth(1)
    line2.SetLineStyle(3)
    line2.SetLineColor(ROOT.kBlack)

    #middle line
    line3 = ROOT.TLine(low, 1, high, 1)
    line3.SetLineWidth(1)
    line3.SetLineStyle(3)
    line3.SetLineColor(ROOT.kBlack)


    return line1, line2, line3

def blindData(data, signal, background,var,cat):
    for ibin in range(data.GetNbinsX()+1):
        sig = signal.GetBinContent(ibin)
        bkg = background.GetBinContent(ibin)
        if bkg > 0 and sig / ROOT.TMath.Sqrt(bkg + pow(0.09*bkg, 2)) >= 0.9:
            err = data.GetBinError(ibin)
            data.SetBinContent(ibin, -1)
            data.SetBinError(ibin, err)

    if var == 'NN_disc' and 'signal' in cat:
         middleBin = data.FindBin(0.7)
         for ibin in range(middleBin, data.GetNbinsX()+1):
             data.SetBinContent(ibin, 0)

    return data

def BuildPlot(args):
    print "ifile,category,variable ", args.input ,args.category , args.channelName, args.variable
    InputFile=args.input.replace('m_sv',args.variable)
    ifile = ROOT.TFile(InputFile)
    category = ifile.Get(args.category)
    channelName = ifile.Get(args.channelName)
#    variable = category.Get(args.variable)
    variableX = ifile.Get(args.category)
    
    style_Xmap=style_map
    if 'em' in args.category or 'me' in args.category:
        style_Xmap=style_map_emu

    # start getting histograms
    data_hist = variableX.Get('out_data_eval').Clone()


    signals = {}
    backgrounds = {}
    backgrounds_EWK = {}

    # loop through histograms to read and store to dict
    for hkey in variableX.GetListOfKeys():
        hname = hkey.GetName()
        ihist = variableX.Get(hname).Clone()
        if hname in style_Xmap['EWK']:
            ihist = ApplyStyle(ihist, style_Xmap['EWK'][hname])
            backgrounds_EWK[hname] = ihist
        
        if hname in style_Xmap['backgrounds']:
            ihist = ApplyStyle(ihist, style_Xmap['backgrounds'][hname])
            backgrounds[hname] = ihist
            
        elif hname in style_Xmap['signals']:
            ihist = ApplyStyle(ihist, style_Xmap['signals'][hname])
            signals[hname] = ihist
            
    
    
            
    # now get stat and stack filled
    stat = data_hist.Clone() # sum of all backgrounds
    stat.Reset()
    stack = ROOT.THStack() # stack of all backgrounds
    
  
   ## checkout sorted function
   ## dont delete this part below 
   
    for bkg in sorted(backgrounds.itervalues(), key = lambda hist: hist.Integral()):
        print "\t\t = ", bkg.GetName(),"  int= ",bkg.Integral()
        stat.Add(bkg)
        stack.Add(bkg)

    '''
    for bkg in sorted(backgrounds_EWK.itervalues(), key = lambda hist: 1./hist.Integral()):
        print "\t\t = ", bkg.GetName()," int= ", bkg.Integral()
        stat.Add(bkg)
        stack.Add(bkg)
    '''
    stack.SetMaximum(data_hist.GetMaximum() * args.scale)
    #stack.GetXaxis().SetRangeUser(0,2500)

    # format the plots
    can = createCanvas()
    #data_hist = ApplyStyle(data_hist, style_Xmap['output_Run2018_data'])
    data_hist = ApplyStyle(data_hist, style_Xmap['out_data_eval'])
   


    stat = formatStat(stat)
    
    data_hist.Rebin(3)  # Rebin the data histogram with a factor of 2
    for bkg in backgrounds.values():
        bkg.Rebin(3)  # Rebin each background histogram with a factor of 2
    for sig_hist in signals.values():
        sig_hist.Rebin(3)  # Rebin each signal histogram with a factor of 2

   
    stack.Draw('hist')
    formatStack(stack)
    stack.SetMaximum(10)


    #combo_signal = signals['out_1000_eval'].Clone() 
    #combo_signal = signals['out_2000_eval'].Clone() 
    #combo_signal = signals['out_3000_eval'].Clone() 
#    data_hist = blindData(data_hist, combo_signal, stat,args.variable,args.category)


    #data_hist.GetXaxis().SetRangeUser(1000, 20000)
    data_hist.Draw('same lep')
    

 
    #stat.Draw('same')
    #stat.Draw('same e2')
    stat.SetLineWidth(0)
    stat.SetLineColor(ROOT.kBlack)


    print "CheckData= ",data_hist.Integral()
    print "stat= ",stat.Integral()
   
    for sig_name, sig_hist in signals.iteritems():
        sig_hist.Scale(.002) #SCALING HERE 0.002
        sig_hist.Draw('same hist')
    
    
    legend = fillLegend(data_hist, backgrounds, backgrounds_EWK, signals, stat)
    legend.Draw('same')
    
    # do some printing on the canvas
    ll = ROOT.TLatex()
    ll.SetNDC(ROOT.kTRUE)
    ll.SetTextSize(0.06)
    ll.SetTextFont(42)
    print 'args.category = {} args.year {}'.format(args.category, args.year)
    lepLabel = "e#mu"
    if 'em_' in args.category:
        lepLabel = "e#mu"
    elif 'me_' in args.category:
        lepLabel = "#mu e"
    elif 'mt_' in args.category:
        lepLabel = "#mu#tau_{h}"
    elif 'et_' in args.category:
        lepLabel = "e#tau_{h}"
    elif 'tt_' in args.category:
        lepLabel = "#tau_{h}#tau_{h}"
    else:
        print 'which channel'
        
    lumi='XXX'
    if args.year == 2016:
        lumi = "35.9 fb^{-1}"
    elif args.year == 2017:
        lumi = "41.5 fb^{-1}"
    elif args.year == 2018:
        lumi = "59.7 fb^{-1}"
    elif args.year == 2020:
        lumi = "137 fb^{-1}"

    if args.year == 2020:
        ll.DrawLatex(0.15, 0.94, "{}                                   {} (13 TeV)".format(lepLabel, lumi))
    else:
        ll.DrawLatex(0.42, 0.94, "{} {}, {} (13 TeV)".format(lepLabel, args.year, lumi))

    cms = ROOT.TLatex()
    cms.SetNDC(ROOT.kTRUE)
    cms.SetTextFont(61)
    cms.SetTextSize(0.09)
    cms.DrawLatex(0.16, 0.8, "CMS")

    prel = ROOT.TLatex()
    prel.SetNDC(ROOT.kTRUE)
    prel.SetTextFont(52)
    prel.SetTextSize(0.06)
    prel.DrawLatex(0.16, 0.74, "Preliminary")

    if args.category == 'mt_inclusive':
        catName = 'Inclusive'
    elif args.category == 'mt_0jet':
        catName = '0-Jet'
    elif args.category == 'mt_boosted':
        catName = 'Boosted'
    elif args.category == 'mt_vbf':
        catName = 'VBF Category'
    else:
        catName = ''

    lcat = ROOT.TLatex()
    lcat.SetNDC(ROOT.kTRUE)
    lcat.SetTextFont(42)
    lcat.SetTextSize(0.06)
#    lcat.DrawLatex(0.16, 0.68, catName)

    # now work on ratio plot
    can.cd(2)
    ratio = data_hist.Clone()
    ratio.Divide(stat)
    ratio = formatPull(ratio, args.label)
    
    rat_unc = ratio.Clone()
    for ibin in range(1, rat_unc.GetNbinsX()+1):
        rat_unc.SetBinContent(ibin, 1)
        rat_unc.SetBinError(ibin, ratio.GetBinError(ibin))
    rat_unc = formatStat(rat_unc)
    # rat_unc.SetMarkerSize(0)
    # rat_unc.SetMarkerStyle(8)

    ratio.Scale(.1)

    rat_unc.Draw('same')
    #ratio.Rebin(2) ## TRIED TO REBIN HERE

    ratio.Draw('same')
#    ratio.Fit("pol0","","",200,400)
#    ratio.Fit("pol1","","",20,200)



    line1, line2, line3 = sigmaLines(data_hist)
    line1.Draw()
    line2.Draw()
    line3.Draw()
    
    # save the pdf
    can.SaveAs('Output/plots/{}_{}_{}_{}.pdf'.format(args.prefix, args.variable, args.category,args.year))



if __name__ == "__main__":
    from argparse import ArgumentParser
    parser = ArgumentParser()
    parser.add_argument('--input', '-i', required=True, action='store', help='input file')
    parser.add_argument('--year', '-y', required=True, action='store', help='year to plot')
    parser.add_argument('--category', '-c', required=True, action='store', help='category to plot')
    parser.add_argument('--variable', '-v', required=True, action='store', help='variable to plot')
    parser.add_argument('--label', '-l', required=True, action='store', help='label for plot')
    parser.add_argument('--prefix', '-p', action='store', help='prefix for output name')
    parser.add_argument('--scale', '-s', default=1.2, type=float, action='store', help='scale max by x')
    BuildPlot(parser.parse_args())
