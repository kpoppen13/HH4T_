// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "../interface/process_trees_4t.h"
#include <iomanip>      // std::setprecision




using std::string;
using std::vector;
int main(int argc, char *argv[]) {
    auto watch = TStopwatch();
    // get CLI arguments
    CLParser parser(argc, argv);
    bool doSyst = parser.Flag("-s");
    string dir = parser.Option("-d");
    string suffix = parser.Option("--suf");
    std::string var_name = parser.Option("-v");
    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    
    string year;
    if (dir.find("2016") != string::npos) year ="2016";
    else if (dir.find("2017") != string::npos ) year ="2017";
    else if (dir.find("2018") != string::npos) year ="2018";
    else (std::cout << "Year is not specificed in the outFile name !\n");
    
    
    string channel = "4t";
    string tree_name = "tree_4tau";
//    if (dir.find("_tt") != string::npos or dir.find("tt_") != string::npos ) {channel ="tt";tree_name="tautau_tree";}
//    else (std::cout << "channel is not specificed in the outFile name !\n");
    string newChannelName= channel;
    
    // get the provided histogram binning
    std::vector<float> bins;
    for (auto sbin : sbins) {
        bins.push_back(std::stoi(sbin));
    }
    
    
    // get input file directory
    if (dir.empty()) {
        std::cerr << "You must give an input directory" << std::endl;
        return -1;
    }
    
    
    // read all files from input directory
    vector<string> files;
    read_directory(dir, &files);
    
    // initialize histogram holder
    auto hists = new HistTool(newChannelName, channel,var_name,  year, suffix, bins);
    
    std::vector<float>  OSSS= hists->Get_OS_SS_ratio();
    
    
    
    hists->histoLoop(year, files, dir, tree_name,var_name,OSSS,0,"");    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
}

void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , string var_name, vector<float> OSSS, bool runPDF,string Sys = "") {

    
    std::cout<< "starting .... "<<dir<<"\n";
    float vbf_var1(0.);
    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        if (name.find("Up") !=string::npos || name.find("Down") !=string::npos ) continue;
        if (name.find("PTH") !=string::npos || name.find("OutsideAcceptance") !=string::npos) continue;
        
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        std::cout<<"ifile is openning: " <<ifile<<"\n";
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
        
        // do some initialization
        initVectors2d(name);
        fout->cd();
        
        float lep1Pt_=-10;
        float lep2Pt_=-10;
        float LeadJetPt = -10;
        bool lep1IsoPassV, lep2IsoPassV ,OS,SS, lep1IsoPassL, lep2IsoPassL;
        float tmass,ht,st,Met,weight, dR_lep_lep, Metphi;
        float NN_disc,MuMatchedIsolation,EleMatchedIsolation,NN_disc_ZTT,NN_disc_QCD;
        float higgs_m, m_sv, gen_higgs_pT, gen_leadjet_pT,m_vis;
        bool isGenTauSub_, isGenTauLead_;

        float vis_mass, vis_mass2, pfMET, higgs_pT, higgs_pT2, rad_eta, radion_pt, radion_inv_mass, 
        HT, higgs1_dr, higgs2_dr, dphi_H1, dphi_H2, dr_HH, dphi_HH, TMass_H1, TMass_H2, TMass_Radion,
        dphi_H1_MET, dphi_H2_MET, dphi_rad_MET, dphi_H2_Rad, dph_H1_Rad, dr_H2_Rad, dr_H1_Rad, tau1_h1_pt,
        tau2_h1_pt, tau1_h2_pt, tau2_h2_pt, ratio, ratio2, total_efficiency_39, AK8Mass, AK8Pt, dphi_H1_Rad;

        //bool H1OS, H2OS;


        //tree->SetBranchAddress("H1OS",&H1OS);
        //tree->SetBranchAddress("H2OS",&H2OS);

        tree->SetBranchAddress("vis_mass",&vis_mass);
        tree->SetBranchAddress("vis_mass2",&vis_mass2);
        tree->SetBranchAddress("pfMET",&pfMET);
        tree->SetBranchAddress("higgs_pT",&higgs_pT);
        tree->SetBranchAddress("higgs_pT2",&higgs_pT2);
        tree->SetBranchAddress("rad_eta", &rad_eta);
        tree->SetBranchAddress("radion_pt", &radion_pt);
        tree->SetBranchAddress("radion_inv_mass", &radion_inv_mass);
        tree->SetBranchAddress("HT",&HT);
        tree->SetBranchAddress("higgs1_dr",&higgs1_dr);
        tree->SetBranchAddress("higgs2_dr",&higgs2_dr);
        tree->SetBranchAddress("dphi_H1",&dphi_H1);
        tree->SetBranchAddress("dphi_H2",&dphi_H2);
        tree->SetBranchAddress("dr_HH",&dr_HH);
        tree->SetBranchAddress("dphi_HH",&dphi_HH);
        tree->SetBranchAddress("TMass_H1",&TMass_H1);
        tree->SetBranchAddress("TMass_H2",&TMass_H2);
        tree->SetBranchAddress("TMass_Radion",&TMass_Radion);
        tree->SetBranchAddress("dphi_H1_MET",&dphi_H1_MET);
        tree->SetBranchAddress("dphi_H2_MET",&dphi_H2_MET);
        tree->SetBranchAddress("dphi_rad_MET",&dphi_rad_MET);
        tree->SetBranchAddress("dphi_H2_Rad",&dphi_H2_Rad);
        tree->SetBranchAddress("dph_H1_Rad",&dphi_H1_Rad);
        tree->SetBranchAddress("dr_H2_Rad",&dr_H2_Rad);
        tree->SetBranchAddress("dr_H1_Rad",&dr_H1_Rad);
        tree->SetBranchAddress("tau1_h1_pt",&tau1_h1_pt);
        tree->SetBranchAddress("tau2_h1_pt",&tau2_h1_pt);
        tree->SetBranchAddress("tau1_h2_pt",&tau1_h2_pt);
        tree->SetBranchAddress("tau2_h2_pt",&tau2_h2_pt);
        tree->SetBranchAddress("AK8Mass", &AK8Mass);
        tree->SetBranchAddress("AK8Pt", &AK8Pt);
        tree->SetBranchAddress("LumiWeight",&weight);
        
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            std::map<std::string, float>  ObsName {
                {"vis_mass", vis_mass},
                {"vis_mass2", vis_mass2},
                {"pfMET", pfMET},
                {"higgs_pT", higgs_pT},
                {"higgs_pT2", higgs_pT2},
                {"rad_eta", rad_eta},
                {"radion_pt", radion_pt},
                {"radion_inv_mass", radion_inv_mass},
                {"HT", HT},
                {"higgs1_dr", higgs1_dr},
                {"higgs2_dr", higgs2_dr},
                {"dphi_H1", dphi_H1},
                {"dphi_H2", dphi_H2},
                {"dr_HH", dr_HH},
                {"dphi_HH", dphi_HH},
                {"TMass_H1", TMass_H1},
                {"TMass_H2", TMass_H2},
                {"TMass_Radion", TMass_Radion},
                {"dphi_H1_MET", dphi_H1_MET},
                {"dphi_H2_MET", dphi_H2_MET},
                {"dphi_rad_MET", dphi_rad_MET},
                {"dphi_H2_Rad", dphi_H2_Rad},
                {"dph_H1_Rad", dph_H1_Rad}, //fix this one
                {"dr_H2_Rad", dr_H2_Rad},
                {"dr_H1_Rad", dr_H1_Rad},
                {"tau1_h1_pt", tau1_h1_pt},
                {"tau2_h1_pt", tau2_h1_pt},
                {"tau1_h2_pt", tau1_h2_pt},
                {"tau2_h2_pt", tau2_h2_pt},
                {"AK8Mass", AK8Mass},
                {"AK8Pt", AK8Pt},
                //{"H1OS", H1OS},
                //{"H2OS", H2OS}
            };


            vbf_var1 =ObsName[var_name];
            

            
            
            //            ################################################################################
            //            ################    Fill  data, signal & non QCD Bkg
            //            ################################################################################
// apply the cuts here
            //if (1) { // final analysis
            //if (H1OS && H2OS){
//            if (OS != 0  && lep1IsoPassV) { // final analysis
                //cout<<"vbf_var1,  weight "<<vbf_var1 <<" "<< weight<<"\n";
                //OS OS, have to rerun 4 times for each histogram
                // + "OS_OS").c_str()
                //hists_1d.at(categories.at(zeroJet)).back()->Fill((vbf_var1 ),  weight); // making plots!
            //}
            
            //if (! H1OS && H2OS){
                //SS OS
              //  hists_1d.at(categories.at(zeroJet)).back()->Fill((vbf_var1+"SS_OS").c_str(),  weight); // making plots!
            //}
            //if (H1OS && ! H2OS){
//            //if (OS != 0  && lep1IsoPassV) { // final analysis
                //cout<<"vbf_var1,  weight "<<vbf_var1 <<" "<< weight<<"\n";
                // OS SS
                //hists_1d.at(categories.at(zeroJet)).back()->Fill((vbf_var1+"OS_SS").c_str(),  weight); // making plots!
            //}
            //if (! H1OS && ! H2OS){
//            if (OS != 0  && lep1IsoPassV) { // final analysis
                //cout<<"vbf_var1,  weight "<<vbf_var1 <<" "<< weight<<"\n";
                //SS SS
                //hists_1d.at(categories.at(zeroJet)).back()->Fill((vbf_var1+"SS_SS").c_str(),  weight); // making plots!


            //}
            
        
        }
        delete fin;
    }
}
