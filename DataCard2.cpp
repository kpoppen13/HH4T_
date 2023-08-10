#include <string>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>
#include "boost/algorithm/string/predicate.hpp"
#include "boost/program_options.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/regex.hpp"
#include "boost/filesystem.hpp"
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/CombineTools/interface/HttSystematics.h"
#include "CombineHarvester/CombineTools/interface/CardWriter.h"
#include "CombineHarvester/CombineTools/interface/CopyTools.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"

namespace po = boost::program_options;
using boost::starts_with;
using namespace std;

int main(int argc, char** argv) {
    
    string postfix="";
    string prefix="";
    // changed the year
    string year = "2018";
    string inputFile="";
    string WP="WP";
    po::variables_map vm;
    po::options_description config("configuration");
    config.add_options()
    //    ("mass,m", po::value<string>(&mass)->default_value(mass))
    ("prefix", po::value<string>(&prefix)->default_value(""))
    ("postfix", po::value<string>(&postfix)->default_value(""))
    //      ("control_region", po::value<int>(&control_region)->default_value(0))

    //changed the year

    ("year", po::value<string>(&year)->default_value("2018"))
    ("WP", po::value<string>(&WP)->default_value(""))
    ("inputFile", po::value<string>(&inputFile)->default_value(""));
    po::store(po::command_line_parser(argc, argv).options(config).run(), vm);
    po::notify(vm);
    
    //! [part1]
    // First define the location of the "auxiliaries" directory where we can
    // source the input files containing the datacard shapes
    //    string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/auxiliaries/shapes/";
    string aux_shapes = string(getenv("CMSSW_BASE")) + "/src/CombineHarvester/CombineTools/bin/aux/";
    
    // Create an empty CombineHarvester instance that will hold all of the
    // datacard configuration and histograms etc.
    ch::CombineHarvester cb;
    
    typedef vector<pair<int, string>> Categories;
    typedef vector<string> VString;
    // Uncomment this next line to see a *lot* of debug information
    // cb.SetVerbosity(3);
    
    // Here we will just define two categories for an 8TeV analysis. Each entry in
    // the vector below specifies a bin name and corresponding bin_id.
    
    //    VString chns = { "mt_qcd","et","em","me","tt"};
    VString chns = { "4t_highPurity", "4t_lowPurity"};
        //"mt_qcd","mt_signal","mt_ztt","et_qcd","et_signal","et_ztt","em_qcd","em_signal","em_ztt","tt_qcd","tt_signal","tt_ztt"};
    map<string, string> input_folders = {
        {"4t_highPurity", "."},
        {"4t_lowPurity", "."},
        //{"mt_ztt", "."},
        //{"et_qcd", "."},
        //{"et_signal", "."},
        //{"et_ztt", "."},
        //{"em_qcd", "."},
        //{"em_signal", "."},
        //{"em_ztt", "."},
        //{"tt_qcd", "."},
        //{"tt_signal", "."},
        //{"tt_ztt", "."},
    };
    
    map<string, VString> bkg_procs;

    bkg_procs["4t_lowPurity"] = {"output_bkg_DY", "output_bkg_T-tchan", "output_bkg_TT", "output_bkg_Tbar-tW", "output_bkg_VV2l2nu", "output_bkg_WJets", "output_bkg_WZ", "output_bkg_ZZ"};
    bkg_procs["4t_highPurity"] = {"output_bkg_DY", "output_bkg_T-tchan", "output_bkg_TT", "output_bkg_Tbar-tW", "output_bkg_VV2l2nu", "output_bkg_WJets", "output_bkg_WZ", "output_bkg_ZZ"};

    //bkg_procs["mt_qcd"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["mt_signal"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["mt_ztt"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["et_qcd"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["et_signal"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["et_ztt"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["tt_qcd"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["tt_signal"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["tt_ztt"] = {"QCD", "TT","VV","ZTT"};
    //bkg_procs["em_qcd"] = {"QCD", "TT","VV","ZTT","W"};
    //bkg_procs["em_signal"] = {"QCD", "TT","VV","ZTT","W"};
    //bkg_procs["em_ztt"] = {"QCD", "TT","VV","ZTT","W"};
    
    // check this
    VString sig_procs = {"output_signal_"};
    
    //VString mt_cat = {"mt_qcd","mt_signal","mt_ztt"};
    //VString et_cat = {"et_qcd","et_signal","et_ztt"};
    //VString tt_cat = {"tt_qcd","tt_signal","tt_ztt"};
    //VString em_cat = {"em_qcd","em_signal","em_ztt"};
    
    
    //VString qcd_cat = {"mt_qcd","et_qcd","tt_qcd","em_qcd"};
    //VString sig_cat = {"mt_signal","et_signal","tt_signal","em_signal"};
    //VString ztt_cat = {"mt_ztt","et_ztt","tt_ztt","em_ztt"};
    
    
    //VString qcd_cat_tau = {"mt_qcd","et_qcd","tt_qcd"};
    //VString sig_cat_tau = {"mt_signal","et_signal","tt_signal"};
    //VString ztt_cat_tau = {"mt_ztt","et_ztt","tt_ztt"};


    //VString qcd_cat_lt = {"mt_qcd","et_qcd","tt_qcd"};
    //VString sig_cat_lt = {"mt_signal","et_signal","tt_signal"};
    //VString ztt_cat_lt = {"mt_ztt","et_ztt","tt_ztt"};

    
    
    

    map<string, Categories> cats;
    cats["4t_lowPurity_13TeV"] = {
        {1, "4t_lowPurity"}
    };
    cats["4t_highPurity_13TeV"] = {
        {1, "4t_highPurity"}
    };


    //cats["mt_qcd_13TeV"] = {
        //{1, "mt_qcd"},
    //};
    //cats["mt_signal_13TeV"] = {
        //{1, "mt_signal"},
    //};
    //cats["mt_ztt_13TeV"] = {
        //{1, "mt_ztt"},
    //};
    //cats["et_qcd_13TeV"] = {
        //{1, "et_qcd"},
    //};
    //cats["et_signal_13TeV"] = {
        //{1, "et_signal"},
    //};
    //cats["et_ztt_13TeV"] = {
        //{1, "et_ztt"},
    //};
    //cats["tt_qcd_13TeV"] = {
        //{1, "tt_qcd"},
    //};
    //cats["tt_signal_13TeV"] = {
        //{1, "tt_signal"},
    //};
    //cats["tt_ztt_13TeV"] = {
        //{1, "tt_ztt"},
    //};
    //cats["em_qcd_13TeV"] = {
        //{1, "em_qcd"},
    //};
    //cats["em_signal_13TeV"] = {
        //{1, "em_signal"},
    //};
    //cats["em_ztt_13TeV"] = {
        //{1, "em_ztt"},
    //};
    
    
    
    
    
    
    
    
    // ch::Categories is just a typedef of vector<pair<int, string>>
    //! [part1]
    
    
    //! [part2]
    //    vector<string> masses = ch::MassesFromRange("800-1500:100");
    //    vector<string> masses = ch::MassesFromRange("14-15:1");
    //vector<string> masses = ch::MassesFromRange("14-15:1");
    vector<string> masses = {"1000", "2000", "3000"};
    // Or equivalently, specify the mass points explicitly:
    //! [part2]
    
    
    //! [part4]
    for (auto chn : chns) {
        cb.AddObservations(
                           {"*"}, {"H"}, {"13TeV"}, {chn}, cats[chn+"_13TeV"]);
        cb.AddProcesses(
                        {"*"}, {"H"}, {"13TeV"}, {chn}, bkg_procs[chn], cats[chn+"_13TeV"], false);
//        if ( chn.find("signal") != string::npos)
        cb.AddProcesses(
                        masses, {"H"}, {"13TeV"}, {chn}, sig_procs, cats[chn+"_13TeV"], true);
    }
    
    
    
    
    cout << ">> Extracting histograms from input root files...\n";
    for (string era : {"13TeV"}) {
        for (string chn : chns) {
            
            string file = aux_shapes + input_folders[chn] + "/"+prefix+"_"+year+".root";
            cb.cp().channel({chn}).era({era}).backgrounds().ExtractShapes(
                                                                          file, "$BIN/$PROCESS", "$BIN/$PROCESS_$SYSTEMATIC");
            cb.cp().channel({chn}).era({era}).signals().ExtractShapes(
                                                                      file, "$BIN/$PROCESS$MASS", "$BIN/$PROCESS$MASS_$SYSTEMATIC");
        }
    }
    
    
    //Some of the code for this is in a nested namespace, so
    // we'll make some using declarations first to simplify things a bit.
    using ch::syst::SystMap;
    using ch::syst::era;
    using ch::syst::bin_id;
    using ch::syst::process;
    using ch::JoinStr;
    
    
    //####################################################################################
    // Norm systematics
    //####################################################################################
    
    // Lumi https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM#LumiComb
    //if (year.find("2016") != string::npos){
        //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.01));
        //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.006));
    //}
    
    //if (year.find("2017") != string::npos){
        //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
        //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.009));
        //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).AddSyst(cb, "lumi_13TeV_1718", "lnN", SystMap<era>::init({"13TeV"}, 1.006));
    //}
    
    if (year.find("2018") != string::npos){
        cb.cp().process(ch::JoinStr({sig_procs, {"output_bkg_DY", "output_bkg_T-tchan", "output_bkg_TT", "output_bkg_Tbar-tW",
        "output_bkg_VV2l2nu", "output_bkg_WJets", "output_bkg_WZ", "output_bkg_ZZ"}})).AddSyst(cb, "lumi_13TeV_"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.015));
        cb.cp().process(ch::JoinStr({sig_procs, {"output_bkg_DY", "output_bkg_T-tchan", "output_bkg_TT", "output_bkg_Tbar-tW",
        "output_bkg_VV2l2nu", "output_bkg_WJets", "output_bkg_WZ", "output_bkg_ZZ"}})).AddSyst(cb, "lumi_13TeV_correlated", "lnN", SystMap<era>::init({"13TeV"}, 1.02));
        cb.cp().process(ch::JoinStr({sig_procs, {"output_bkg_DY", "output_bkg_T-tchan", "output_bkg_TT", "output_bkg_Tbar-tW",
        "output_bkg_VV2l2nu", "output_bkg_WJets", "output_bkg_WZ", "output_bkg_ZZ"}})).AddSyst(cb, "lumi_13TeV_1718", "lnN", SystMap<era>::init({"13TeV"}, 1.002));
    }
    
    
    //         electron
    //cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat}))
        //.AddSyst(cb, "CMS_eff_e_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    //cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT"}})).channel(ch::JoinStr({et_cat}))
        //.AddSyst(cb, "CMS_eff_e_et"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat,et_cat}))
        //.AddSyst(cb, "CMS_scale_e"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat}))
        //.AddSyst(cb, "CMS_trg_e_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    //cb.cp().process(ch::JoinStr({sig_procs, {"W","TT","VV","ZTT"}})).channel(ch::JoinStr({et_cat}))
        //.AddSyst(cb, "CMS_trg_e_et"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    
    //      muon
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat}))
        //.AddSyst(cb, "CMS_eff_m_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({mt_cat}))
        //.AddSyst(cb, "CMS_eff_m_mt"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat,mt_cat}))
        //.AddSyst(cb, "CMS_scale_m"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat}))
        //.AddSyst(cb, "CMS_trg_m_em"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({mt_cat}))
        //.AddSyst(cb, "CMS_trg_m_mt"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}})).channel(ch::JoinStr({em_cat,mt_cat,et_cat}))
        //.AddSyst(cb, "CMS_scale_b"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.02));
    
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        //.AddSyst(cb, "CMS_res_j"+year, "lnN", SystMap<era>::init({"13TeV"}, 1.01));
    
    //cb.cp().process({"ZTT"})
        //.AddSyst(cb, "CMS_htt_ZTTNorm"+year, "lnN", SystMap<>::init(1.03));
    
    //cb.cp().process({"TT"})
        //.AddSyst(cb, "CMS_htt_TTNorm"+year, "lnN", SystMap<>::init(1.05));
    
    //cb.cp().process({"VV"})
        //.AddSyst(cb, "CMS_htt_VVNorm"+year, "lnN", SystMap<>::init(1.05));
    
    //cb.cp().process({"W"})
        //.AddSyst(cb, "CMS_htt_WNorm"+year, "lnN", SystMap<>::init(1.10));




        
   // QCD norm uncertainties decorrelated across years channel and categories
    // cb.cp().process({"QCD"}) .AddSyst(cb, "CMS_htt_QCDNorm_"+year, "lnN", SystMap<>::init(1.20));
    
    
    //####################################################################################
    // Shape systematics
    //####################################################################################
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //  Jet ES
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        //.AddSyst(cb, "CMS_scale_j"+year, "shape", SystMap<>::init(1.00));
    
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //  MET ES
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
    //cb.cp().process(ch::JoinStr({sig_procs, {"W", "TT","VV","ZTT"}}))
        //.AddSyst(cb, "CMS_scale_met_unclustered"+year, "shape", SystMap<>::init(1.00));
    
    
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    //  Tau ES
    //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    
  
        //cb.cp().process(ch::JoinStr({sig_procs, { "TT","VV","ZTT"}})).channel(ch::JoinStr({tt_cat,mt_cat,et_cat}))
            //.AddSyst(cb, "CMS_scale_t_1prong1pizero"+year, "shape", SystMap<>::init(1.00));
    
        //cb.cp().process(ch::JoinStr({sig_procs, { "TT","VV","ZTT"}})).channel(ch::JoinStr({tt_cat,mt_cat,et_cat}))
            //.AddSyst(cb, "CMS_scale_t_1prong"+year, "shape", SystMap<>::init(1.00));
    
        //cb.cp().process(ch::JoinStr({sig_procs, { "TT","VV","ZTT"}})).channel(ch::JoinStr({tt_cat,mt_cat,et_cat}))
            //.AddSyst(cb, "CMS_scale_t_3prong"+year, "shape", SystMap<>::init(1.00));

    
    
   
    
    cb.cp().backgrounds().ExtractShapes(
                                        aux_shapes + "/"+prefix+"_"+year+".root",
                                        "$BIN/$PROCESS",
                                        "$BIN/$PROCESS_$SYSTEMATIC");
    cb.cp().signals().ExtractShapes(
                                    aux_shapes + "/"+prefix+"_"+year+".root",
                                    "$BIN/$PROCESS$MASS",
                                    "$BIN/$PROCESS$MASS_$SYSTEMATIC");
    
    
    
    
    //! [part7]
    
    //! [part8]
    //    auto bbb = ch::BinByBinFactory()
    //    .SetAddThreshold(0.1)
    //    .SetFixNorm(true);
    
    //    bbb.AddBinByBin(cb.cp().backgrounds(), cb);
    
    // This function modifies every entry to have a standardised bin name of
    // the form: {analysis}_{channel}_{bin_id}_{era}
    // which is commonly used in the htt analyses
    ch::SetStandardBinNames(cb);
    
    
    
    //! [part8]
    
    //! [part9]
    // First we generate a set of bin names:
    set<string> bins = cb.bin_set();
    // This method will produce a set of unique bin names by considering all
    // Observation, Process and Systematic entries in the CombineHarvester
    // instance.
    
    // We create the output root file that will contain all the shapes.
    //TFile output("RHW_mt.inputs.root", "RECREATE");
    
    // Finally we iterate through each bin,mass combination and write a
    
    
    auto pre_drop = cb.syst_name_set();
    //cb.syst_name(droplist, false);
    auto post_drop = cb.syst_name_set();
    cout << ">> Systematics dropped: " << pre_drop.size() - post_drop.size()
    << "\n";
    
    
    string folder = postfix+"/"+year;
    boost::filesystem::create_directories(folder);
    boost::filesystem::create_directories(folder + "/common");
    for (auto m : masses) {
        boost::filesystem::create_directories(folder + "/" + m);
    }
    
    for (string chn : chns) {
        TFile output((folder + "/common/"+chn+"_"+year+".root").c_str(),
                     "RECREATE");
        auto bins = cb.cp().channel({chn}).bin_set();
        for (auto b : bins) {
            for (auto m : masses) {
                cout << ">> Writing datacard for bin: " << b << " and mass: " << m
                << "\r" << flush;
                cb.cp().channel({chn}).bin({b}).mass({m, "*"}).WriteDatacard(
                                                                             folder + "/" + m + "/" + b + ".txt", output);
            }
        }
        output.Close();
    }
    
    
    //! [part9]
    
}