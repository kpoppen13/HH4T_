// ./process_trees_tt -d newBoost_tt_2018_trgData_newcuts  --suf tt_2018_trgData_newcut  -v m_sv -b 30 0 300
// user includes
#include "TStopwatch.h"
#include "TMath.h"
#include "../interface/CLParser.h"
#include "process_trees_4t.h"
#include <iomanip>      // std::setprecision




using std::string;
using std::vector;
int main(int argc, char *argv[]) {
    auto watch = TStopwatch();
    // get CLI arguments
    CLParser parser(argc, argv);
    string dir = parser.Option("-d");
    string suffix = parser.Option("--suf");
    std::string var_name = parser.Option("-v");
//    std::vector<std::string> sbins = parser.MultiOption("-b", 3);
    
    string year="2018";
    string channel, tree_name;
    channel ="4t";tree_name="output_eval_tree";
    
    // get input file directory
    if (dir.empty()) {
        std::cerr << "You must give an input directory" << std::endl;
        return -1;
    }
    
    
    // read all files from input directory
    vector<string> files;
    read_directory(dir, &files);
    
    // initialize histogram holder
    auto hists = new HistTool(channel,var_name,  year, suffix);
    
    
    hists->histoLoop(year, files, dir,tree_name,var_name);    // fill histograms
    hists->writeTemplates(dir,channel,year);  // write histograms to file
    hists->fout->Close();
    
    std::cout << "Template created.\n Timing Info: \n\t CPU Time: " << watch.CpuTime() << "\n\tReal Time: " << watch.RealTime() << std::endl;
    
    //  delete hists->ff_weight;
}


void HistTool::histoLoop(std::string year , vector<string> files, string dir, string tree_name , string var_name) {

    
    std::cout<< "starting .... "<<dir<<"\n";
    float observable(0.);
    for (auto ifile : files) {
        
        
        string name = ifile.substr(0, ifile.find(".")).c_str();
        
        auto fin = new TFile((dir + "/" + ifile).c_str(), "read");
        std::cout<<"ifile is openning: " <<ifile<<"\n";
        auto tree = reinterpret_cast<TTree *>(fin->Get(tree_name.c_str()));
        
        
        // do some initialization
        initVectors2d(name);
        fout->cd();
        


        //float lep1Pt_=-10;
        //float lep2Pt_=-10;
        //float vis_mass=-10;
        //float LeadJetPt = -10;
        //bool lep1IsoPassV, lep2IsoPassV ,OS,SS, lep1IsoPassL, lep2IsoPassL;
        //float tmass,ht,st,Met,weight, dR_lep_lep, Metphi;
        //float NN_disc,MuMatchedIsolation,EleMatchedIsolation,NN_disc_ZTT,NN_disc_QCD;
        //float higgs_pT, higgs_m, m_sv, gen_higgs_pT, gen_leadjet_pT;
        //bool isGenTauSub_, isGenTauLead_;
        double weight, NN_disc, radion_pt, vis_mass, vis_mass2, rad_eta, higgs1_dr, higgs2_dr, dphi_H1, dphi_H1_MET;
        double dphi_H2, dphi_H2_MET, dr_HH, dr_H1_Rad, dphi_HH, dr_H2_Rad, dphi_rad_MET, LumiWeight, radion_inv_mass, HH4tau_NN_output;


        tree->SetBranchAddress("radion_pt",&radion_pt);
        tree->SetBranchAddress("vis_mass",&vis_mass);
        tree->SetBranchAddress("vis_mass2",&vis_mass2);
        tree->SetBranchAddress("rad_eta",&rad_eta);
        tree->SetBranchAddress("higgs1_dr",&higgs1_dr);
        tree->SetBranchAddress("higgs2_dr",&higgs2_dr);
        tree->SetBranchAddress("dphi_H1",&dphi_H1);
        tree->SetBranchAddress("dphi_H1_MET",&dphi_H1_MET);
        tree->SetBranchAddress("dphi_H2",&dphi_H2);
        tree->SetBranchAddress("dphi_H2_MET",&dphi_H2_MET);
        tree->SetBranchAddress("dr_HH",&dr_HH);
        tree->SetBranchAddress("dr_H1_Rad",&dr_H1_Rad);
        tree->SetBranchAddress("dphi_HH",&dphi_HH);
        tree->SetBranchAddress("dr_H2_Rad",&dr_H2_Rad);
        tree->SetBranchAddress("dphi_rad_MET",&dphi_rad_MET);


        tree->SetBranchAddress("LumiWeight",&LumiWeight);
        tree->SetBranchAddress("radion_inv_mass",&radion_inv_mass);
        tree->SetBranchAddress("HH4tau_NN_output",&HH4tau_NN_output);
       
        
        // Here we have to call OS/SS method extracter
        std::cout<<" tree->GetEntries() is "<<tree->GetEntries()<<"\n";
        for (auto i = 0; i < tree->GetEntries(); i++) {
            tree->GetEntry(i);
            
            std::map<std::string, float>  ObsName {
                {"radion_pt",radion_pt},
                {"vis_mass",vis_mass},
                {"vis_mass2",vis_mass2},
                {"rad_eta",rad_eta},
                {"higgs1_dr",higgs1_dr},
                {"higgs2_dr",higgs2_dr},
                {"dphi_H1",dphi_H1},
                {"dphi_H1_MET",dphi_H1_MET},
                {"dphi_H2",dphi_H2},
                {"dphi_H2_MET",dphi_H2_MET},
                {"dr_HH",dr_HH},
                {"dr_H1_Rad",dr_H1_Rad},
                {"dphi_HH",dphi_HH},
                {"dr_H2_Rad",dr_H2_Rad},
                {"dphi_rad_MET",dphi_rad_MET},
                {"LumiWeight",LumiWeight},
                {"radion_inv_mass",radion_inv_mass},
                {"HH4tau_NN_output",HH4tau_NN_output}
            };


        observable  =ObsName[var_name];
            


            //            ################################################################################
            //            ################    Fill  data, signal & non QCD Bkg
            //            ################################################################################
            
            
            // use weight or LumiWeight?? 
            if (NN_disc<0.7) { // final analysis
                hists_1d.at(categories.at(lowPurity)).back()->Fill(observable, weight);
            }
            else{
            hists_1d.at(categories.at(highPurity)).back()->Fill(observable, weight);
      }
        }
        delete fin;
    }
}