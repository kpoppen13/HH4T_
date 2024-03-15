//#include "../interface/Functions.h"
#include "../interface/functions.h"
#include <string>
#include <ostream>
#include <vector>

#include <list>
#include <algorithm>

#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "TLorentzVector.h"
#include "../interface/CLParser.h"
#include "../interface/boostHTT_4t.h"
#include "../interface/makeHisto.h"
#include "../interface/WeightCalculator.h"


int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
//    std::string path = parser.Option("-p");
//    std::string output_dir = parser.Option("-d");
    std::string syst = parser.Option("-u");
//    std::string fname = path + sample + ".root";
    std::string fname = sample ;
    
    std::string year_str;
//    if (path.find("2016") != string::npos) year_str = "2016";
//    else if (path.find("2017") != string::npos) year_str = "2017";
//    else if (path.find("2018") != string::npos) year_str = "2018";
//    else cout<<"Which year are you looking for \n\n";
//    cout<<"%%%% Note: you are running on  "<< year_str <<"%%%%\n";
    
    stringstream yearstream(year_str);
    int year=0;
    yearstream >> year;
    
    
    // create output file
    auto suffix = "_output.root";
    auto prefix =  "";
    std::string filename;
    if (name == sample) {
        filename = prefix + name +  suffix;
    } else {
        filename = name;
    }
    std::cout<<"output name is "<<filename.c_str()<<"\n";
    
    
    // open input file
    std::cout << "Opening file... " << sample << std::endl;
    auto InputFile = TFile::Open(fname.c_str());
    std::cout << "Loading Ntuple..." << std::endl;
    TTree *  Run_Tree;
    Run_Tree= Xttree(InputFile,"4tau_tree");
    
    //    auto HistoTot = reinterpret_cast<TH1D*>(InputFile->Get("ggNtuplizer/hEvents"));
    TH1F * HistoTot = (TH1F*) InputFile->Get("hcount");
    auto fout = new TFile(filename.c_str(), "RECREATE");
    
    myMap1 = new std::unordered_map<std::string, TH1F*>();
    myMap2 = new unordered_map<string, TH2F*>();
    
    TTree * outTr=  new TTree("tree_4tau","tree_4tau");
    

    //###############################################################################################
    // Parameters
    //###############################################################################################
    float MuMass= 0.10565837;
    //float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=30;

    float DeepCSVCut = 0.8001;

    //float DeepCSVCut=   1000   ;                  //  loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    //if (year== 2016) DeepCSVCut =     0.8953  ;
    //if (year== 2017) DeepCSVCut =     0.8001  ;
    //if (year== 2018) DeepCSVCut =    0.7527   ; //come back to this and ask if this is correct?

    float LumiWeight = 1;
    float vis_mass=-10;
    float vis_mass2=-10;
    float radion_inv_mass=-10;
    float min_dr = 100;
    float lead_tau_iso;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_pT2, radion_pt, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
    float LeadingBoostedTauPt;
    float SubLeadingBoostedTauPt;
    float ThirdBoostedTauPt;
    float FourthBoostedTauPt;
    float dphi_HH;
    float dr_HH;
    float dphi_H2;
    float dphi_H1;
    float higgs2_dr;
    float higgs1_dr;
    float TMass_H1, TMass_H2, TMass_Radion;
    float dphi_H1_MET, dphi_H2_MET, dphi_rad_MET, dphi_H1_Rad, dphi_H2_Rad;
    float dr_H1_Rad, dr_H2_Rad;
    float tau1_h1_pt, tau2_h1_pt, tau1_h2_pt, tau2_h2_pt;
    float rad_eta;
    float HT;
    float ratio, ratio2;
    bool PassTrigger_40;
    bool PassTrigger_39;
    float pass_both_triggers;
    float pfMHT;
    float PFMET_MHT;
    float total_efficiency_39;
    float Numerator39;
    float Denominator39;
    float Numerator40;
    float Denominator40;
    float AK8Pt=0;
    float AK8Mass=0;
    float _cut_PFMET_MHT_;
    int H1OS;
    int H2OS;
    int tau4_charge;
    int tau2_charge;
    int Z_multiplicity = 0;
    bool good_or_bad_match = true;
    int tau1_index = 15; 
    int lead_charge;
    int tau3_index = 15; 
    int tau3_charge;  
    float TMass;
    float eleMass = 0.000511;
    float ele_pt;
    float match_tau_pt;
    float muMass = 0.10565837;
    float muon_pt;
    float matched_tau_pt;
    float efficiency39;
    float efficiency40;
    int numBJet;
    bool Mu_trigger;
    bool pfmet_pfmht_trigger;
    bool PassTrigger_50;
    bool PassTrigger_27;

    TLorentzVector Muon4Momentum, MatchedTau4Momentum;


   outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
   outTr->Branch("vis_mass2",&vis_mass2,"vis_mass2/F");
   outTr->Branch("LumiWeight",&LumiWeight,"LumiWeight/F");
   outTr->Branch("pfMET",&pfMET,"pfMET/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_pT2",&higgs_pT2,"higgs_pT/F");
    outTr->Branch("rad_eta", &rad_eta, "rad_eta/F");
    outTr->Branch("radion_pt", &radion_pt, "radion_pt/F");
    outTr->Branch("radion_inv_mass", &radion_inv_mass, "radion_inv_mass/F");
    outTr->Branch("HT",&HT,"HT/F");
    outTr->Branch("higgs1_dr",&higgs1_dr,"higgs1_dr/F");
    outTr->Branch("higgs2_dr",&higgs2_dr,"higgs2_dr/F");
    outTr->Branch("dphi_H1",&dphi_H1,"dphi_H1/F");
    outTr->Branch("dphi_H2",&dphi_H2,"dphi_H2/F");
    outTr->Branch("dr_HH",&dr_HH,"dr_HH/F");
    outTr->Branch("dphi_HH",&dphi_HH,"dphi_HH/F");
    outTr->Branch("TMass_H1",&TMass_H1,"TMass_H1/F");
    outTr->Branch("TMass_H2",&TMass_H2,"TMass_H2/F");
    outTr->Branch("TMass_Radion",&TMass_Radion,"TMass_Radion/F");
    outTr->Branch("dphi_H1_MET",&dphi_H1_MET,"dphi_H1_MET/F");
    outTr->Branch("dphi_H2_MET",&dphi_H2_MET,"dphi_H2_MET/F");
    outTr->Branch("dphi_rad_MET",&dphi_rad_MET,"dphi_rad_MET/F");
    outTr->Branch("dphi_H2_Rad",&dphi_H2_Rad,"dphi_H2_Rad/F");
    outTr->Branch("dph_H1_Rad",&dphi_H1_Rad,"dphi_H1_Rad/F");
    outTr->Branch("dr_H2_Rad",&dr_H2_Rad,"dr_H2_Rad/F");
    outTr->Branch("dr_H1_Rad",&dr_H1_Rad,"dr_H1_Rad/F");
    outTr->Branch("tau1_h1_pt",&tau1_h1_pt,"tau1_h1_pt/F");
    outTr->Branch("tau2_h1_pt",&tau2_h1_pt,"tau2_h1_pt/F");
    outTr->Branch("tau1_h2_pt",&tau1_h2_pt,"tau1_h2_pt/F");
    outTr->Branch("tau2_h2_pt",&tau2_h2_pt,"tau2_h2_pt/F");
    outTr->Branch("ratio",&ratio,"ratio/F");
    outTr->Branch("ratio2",&ratio2,"ratio2/F");
    outTr->Branch("total_efficiency_39",&total_efficiency_39,"total_efficiency_39/F");
    outTr->Branch("Denominator39",&Denominator39,"Denominator39/F");
    outTr->Branch("Numerator39",&Numerator39,"Numerator39/F");
    outTr->Branch("Denominator40",&Denominator40,"Denominator40/F");
    outTr->Branch("Numerator40",&Numerator40,"Numerator40/F");
    outTr->Branch("AK8Mass", &AK8Mass, "AK8Mass/F");
    outTr->Branch("AK8Pt", &AK8Pt, "AK8Pt/F");
    outTr->Branch("H1OS", &H1OS, "H1OS/O");
    outTr->Branch("H2OS", &H2OS, "H2OS/O");
    outTr->Branch("numBJet", &numBJet, "numBJet/I"); 

    outTr->Branch("PassTrigger_50", &PassTrigger_50, "PassTrigger_50/B");
    outTr->Branch("PassTrigger_27", &PassTrigger_27, "PassTrigger_27/B");


//for the trigger
string JetSys="Nominal";
if (syst=="JEnTotUp") JetSys="JetTotUp";
else if (syst=="JEnTotDown") JetSys="JetTotDown";
else std::cout<<"This is nominal Jet\n";

    Int_t nentries_wtn = (Int_t) Run_Tree->GetEntries();
    cout<<"nentries_wtn===="<<nentries_wtn<<"\n";
    for (Int_t i = 0; i < nentries_wtn; i++) {
        
        Run_Tree->GetEntry(i);
        if (i % 1000 == 0) fprintf(stdout, "\r  Processed events: %8d of %8d ", i, nentries_wtn);
        fflush(stdout);
        
        plotFill("cutFlowTable",1 ,15,0,15);
        //=========================================================================================================
        // Lowest unprescaled trigger           2016                         2017                                     2018
        
        //           HLT_AK8PFJet360_TrimMass30_v                      HLT_AK8PFJet400_TrimMass30(36.75/ 41.54)   HLT_AK8PFJet400_TrimMass30_v
        //           HLT_AK8PFJet500 (not in yet 33.64/36.47 )         HLT_AK8PFJet500 (not in yet)               HLT_AK8PFJet500 (not in yet)
        //           HLT_PFHT300_PFMET110_v                            HLT_PFHT500_PFMET100_PFMHT100_IDT          HLT_PFHT500_PFMET100_PFMHT100_IDT
        //           HLT_PFHT900_v                                     HLT_PFHT1050_v                             HLT_PFHT1050_v
        
        
//
//        //2016
//        PassTrigger_21 = ((HLTJet >> 21 & 1)==1); //HLT_AK8PFJet360_TrimMass30_v // only 2016?
//        PassTrigger_22 = ((HLTJet >> 22 & 1)==1); //HLT_PFHT300_PFMET110_v // only 2016?
//
//
// 2017 and 2018
// Trigger results
PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v 
PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v

/*
//std::cout << "PassTrigger_40: " << PassTrigger_40 << endl;
if (PassTrigger_40 == 1){
    plotFill("passtrigger_40_beforecuts", PassTrigger_40, 100, 0, 1.25);
}
if (PassTrigger_39 == 1){
    plotFill("passtrigger_39_beforecuts", PassTrigger_39, 100, 0, 1.25);
}
plotFill("PassTrigger_40", PassTrigger_40, 100,0,1.25);
plotFill("PassTrigger_39", PassTrigger_39, 100, 0, 1.25);
*/




// use OR between these two triggers 
// Mu50 (bitEleMuX = 21) 
// HLT_PFMET120_PFMHT120_IDTight_v (bitJet = 27)
// No cut on the AKJetpT or AKMAss or PFHT

int bitEleMuX;
int bitJet;

bool HLT_Mu50 = ((HLTEleMuX >> 21 & 1)==1); // else if (name.find(“HLT_Mu50_v”)  != string::npos) bitEleMuX = 21;


// PassTrigger_27 = (HLT_PFMET120_PFMHT120_IDTight_v>>(bitJet = 27)==1);
PassTrigger_27 = ((HLTJet >> 27 & 1)==1); 



if (HLT_Mu50 == 1){
    plotFill("passtrigger_50_beforecuts", HLT_Mu50, 100, 0, 1.25);
}
if (PassTrigger_27==1){
    plotFill("PassTrigger_27_beforecuts", PassTrigger_27, 100, 0, 1.25);
}



//
//        // Trigger
//        //        https://cmsoms.cern.ch/cms/triggers/hlt_trigger_rates?cms_run=325175
//        //https://twiki.cern.ch/twiki/bin/viewauth/CMS/HLTPathsRunIIList
//        PassTrigger_20 = ((HLTJet >> 20 & 1)==1); //HLT_AK8PFHT700_TrimR0p1PT0p3Mass50_v // only 2016?
//        PassTrigger_37 = ((HLTJet >> 37 & 1)==1); //HLT_AK8PFHT800_TrimMass50_v // not effective
//        PassTrigger_38 = ((HLTJet >> 38 & 1)==1); //HLT_PFHT1050_v  NOT Effective at all
//        PassTrigger_41 = ((HLTJet >> 41 & 1)==1);// HLT_AK8PFJet420_TrimMass30_v  // not needed as HLT_AK8PFJet400_TrimMass30_v is available
//        PassTrigger_42 = ((HLTJet >> 42 & 1)==1);//HLT_PFHT500_PFMET110_PFMHT110_IDTight_v
//        PassTrigger_43 = ((HLTJet >> 43 & 1)==1); // HLT_AK8PFHT850_TrimMass50_v  HLT_AK8PFHT800_TrimMass50_v is OK as well
//        PassTrigger_44 = ((HLTJet >> 44 & 1)==1); //HLT_AK8PFHT900_TrimMass50_v

 

        plotFill("cutFlowTable",2 ,15,0,15);
        

        TLorentzVector LeadTau4Momentum,SubTau4Momentum, Sub_and_Lead_Momentum, Met4Momentum, LeadTau4MomentumNominal, SubTau4MomentumNominal;
        //=========================================================================================================
if (nBoostedTau < 3) continue;
    float LeadingBoostedTauPt= boostedTauPt->at(0);
    float SubLeadingBoostedTauPt= boostedTauPt->at(1);
    float ThirdBoostedTauPt= boostedTauPt->at(2);
    float FourthBoostedTauPt= boostedTauPt->at(3);
    plotFill("LeadingBoostedTauPt_",LeadingBoostedTauPt ,50,0,2000);
    plotFill("SubLeadingBoostedTauPt_",SubLeadingBoostedTauPt ,50,0,1000);
    plotFill("ThirdBoostedTauPt_",ThirdBoostedTauPt ,50,0,700);
    plotFill("FourthBoostedTauPt_",FourthBoostedTauPt ,50,0,500);

// 
//=========================================================================================================
        // Cut on AK8 (for trigger purposes)
        //float AK8Pt=0;
        //float AK8Mass=0;
        float AK8Eta=100;
        float AK8Jet;
        float PFHT= getST(JetPtCut,JetSys); 
        float PFMET=Met;
        float MHT=getMHT(JetPtCut,JetSys);
        float TriggerWeight = 1;
        float TriggerWeightError = 1;
        float _cut_AK8Pt_,_cut_AK8Mass_,_cut_PFHT_,_cut_PFMET_,_cut_PFMHT_, _cut_PFMETMHT_, _cut_st_;
        bool _Pass_AK8_Trigger_, _Pass_METHT_Trigger_;

        for (int ijet=0; ijet < nAK8Jet ; ijet ++){
            
            AK8Pt=AK8JetPt->at(ijet);
            if (syst=="JEnTotUp") AK8Pt=AK8JetPtTotUncUp->at(ijet);;
            if (syst=="JEnTotDown") AK8Pt=AK8JetPtTotUncDown->at(ijet);;
            
            AK8Mass=AK8JetSoftDropMass->at(ijet);
            AK8Eta=fabs(AK8JetEta->at(ijet));
            
            if (AK8Pt > 450 && AK8Mass > 30 && AK8Eta < 2.5){
                break;
        }
        }
// Trigger Efficiency==========================================================================
//if (year== 2018  && PFHT > 400 ){
    //plotFill("RunBeforeTrigger",run, 50 ,315000,326000);
    //if (PassTrigger_39) plotFill("RunHLTJet39",run, 50 ,315000,326000);
    //if (PassTrigger_40) plotFill("RunHLTJet40",run, 50 ,315000,326000);
    //}
//=========================================================================================
if (year== 2018){    
    _cut_AK8Pt_ = 450;
    _cut_AK8Mass_ = 30;
    _cut_PFHT_ = 500;         
    _cut_PFMET_ = 100;        
    _cut_PFMHT_= 100;         
    _cut_PFMET_MHT_ = 200;
    _Pass_AK8_Trigger_=PassTrigger_40;
    _Pass_METHT_Trigger_=PassTrigger_39;
    //_cut_st_ = 600;
    }


PFMET_MHT = pfMET + MHT;

    ////apply trigger only on data
    
    /*
    // offline cuts
    bool passing;
    if (year == 2018){
        // trigger 39     HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
        // first check if the events pass trigger 39 offline and online cuts
        if (PassTrigger_39 == 1.0 && PFHT > _cut_PFHT_ && PFMET_MHT > _cut_PFMET_MHT_){
            passing = true;
            // now check trigger 40 if the event did not pass trigger 39 offline and online cuts
            // trigger 40 HLT_AK8PFJet400_TrimMass30_v 
            if (passing == false && PassTrigger_40 == 1.0 && AK8Mass > 30 && AK8Pt > 400){
                passing = true;
            }
        }
        if (passing == false) continue; // get rid of events that did not pass either trigger
    }
    */
    
    
    bool passing;
    if (year == 2018){
        // trigger 50 (Mu50 (bitEleMuX = 21)==1); Mu trigger
        // first check if the events pass this trigger offline and online cuts
        for (int i = 0; i < nMu; ++i){
            // loop over all muons, pt above 52, events pass
            Muon4Momentum.SetPtEtaPhiM(muPt->at(i), muEta->at(i), muPhi->at(i), muMass);
            muon_pt = Muon4Momentum.Pt();
            if (PassTrigger_50 == 1.0 && muon_pt > 52){
                passing = true;
            }
        }
        // now check the other trigger if the event did not pass trigger 50 online and offline cuts
        if (passing == false && PassTrigger_27 == 1.0 && pfMET > 130 && MHT > 130){
            passing = true;
        }
        if (passing == false) continue;  // get rid of events that did not pass either trigger
    }
        
        
        
            
         
    
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================
    //get the four momentum for each of the first four Tau
    TLorentzVector ThirdTau4Momentum, FourthTau4Momentum, Third_and_Fourth_Momentum;    
    LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(0), boostedTauEta->at(0), boostedTauPhi->at(0), boostedTauMass->at(0));
    SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(1), boostedTauEta->at(1), boostedTauPhi->at(1), boostedTauMass->at(1));
    ThirdTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(2), boostedTauEta->at(2), boostedTauPhi->at(2), boostedTauMass->at(2));
    FourthTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(3), boostedTauEta->at(3), boostedTauPhi->at(3), boostedTauMass->at(3));

    // check isolation of each tau
    float subtau_iso, third_tau_iso, fourth_tau_iso;
    lead_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(0);
    subtau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(1);
    third_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(2);
    fourth_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(3);
    
    plotFill("lead_tau_iso", lead_tau_iso, 50, -1.1, 1.1);
    plotFill("subtau_iso", subtau_iso, 50, -1.1, 1);
    plotFill("third_tau_iso", third_tau_iso, 50, -1.1, 1.1);
    plotFill("fourth_tau_iso", fourth_tau_iso, 50, -1.1, 1.1);

    //deltaR between the leading tau and each of the other tau
    float dR_sub_lead= SubTau4Momentum.DeltaR(LeadTau4Momentum);
    float dR_lead_third= LeadTau4Momentum.DeltaR(ThirdTau4Momentum);
    float dR_lead_fourth= LeadTau4Momentum.DeltaR(FourthTau4Momentum);
    plotFill("dR_sub_lead_", dR_sub_lead, 50,0,5);
    plotFill("dR_lead_third_", dR_lead_third, 50,0,5);
    plotFill("dR_lead_fourth_", dR_lead_fourth, 50,0,5);
    //==================================================================

    LumiWeight = getLuminsoity(2018, "tt") * XSection(sample)*1.0 / HistoTot->GetBinContent(2);
    //std::cout<< HistoTot->GetBinContent(2)<<endl;
    // print lumiweight, run on TTbar
    //std::cout<<LumiWeight<<endl;
    // sets LumiWeight to 1 for signal
    if (LumiWeight == 0){
        LumiWeight = 1;
    }

    Z_multiplicity = Zto_mumu_multiplicity() + Zto_ee_multiplicity();
    plotFill("Z_multiplicity", Z_multiplicity, 50, 0, 4.5);
    plotFill("Z_muon_mult", Zto_mumu_multiplicity(), 50, 0, 4.5);
    plotFill("Z_ee_mult", Zto_ee_multiplicity(), 50, 0, 4.5);
    //plotFill("Z_ee_mumu_mult", Zto_mumu_multiplicity(), Zto_ee_multiplicity(), 50, 0, 10);
    if (Z_multiplicity > 0) continue;
    
    //matching the pairs
    TLorentzVector NewBoostedTau4Momentum, LeadMatch4Momentum, higgs1_momentum, SecondPair4Momentum, higgs2_momentum; 
    // get lead tau
    tau1_index = 15;
    TLorentzVector leadtau4mom;
    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
        if (isTauGood(ibtau) == false) continue;
        if (good_or_bad_match == false) continue;
        if (ibtau<tau1_index){ 
            //std::cout<<tau1_index<<endl;
            tau1_index = ibtau; 
            leadtau4mom.SetPtEtaPhiM(boostedTauPt->at(ibtau), boostedTauEta->at(ibtau), boostedTauPhi->at(ibtau), boostedTauMass->at(ibtau));
            lead_charge = boostedTauCharge->at(ibtau);
            plotFill("Lead_Tau_Index", ibtau, 50, 0, 5, LumiWeight);
        }
    }
    
    

    // once I have the lead tau, find the match (the cuts are in the functions, so it should pick good taus)
    int tau2_index = MatchBoostedTau(leadtau4mom, tau1_index);
    //std::cout<<tau2_index<<endl;
    if (tau2_index < 0) continue; 


    tau2_charge = boostedTauCharge->at(tau2_index); 
    //H1 Charge
    if (tau2_charge * lead_charge < 0){ 
        H1OS = 1;
    }
    
    if (tau2_charge * lead_charge > 0){ 
       H1OS = 0;
    }

    plotFill("H1OS", H1OS, 50, -.5, .5);

    LeadMatch4Momentum.SetPtEtaPhiM(boostedTauPt->at(tau2_index), boostedTauEta->at(tau2_index), boostedTauPhi->at(tau2_index), boostedTauMass->at(tau2_index));
    plotFill("Tau_2_Index", tau2_index, 40, 0, 8, LumiWeight); 
    

    tau3_index = 15;
    for (int i = 0; i< nBoostedTau; i++){
        if (i == tau1_index) continue; 
        if (i == tau2_index) continue; 
        if (isTauGood(i) == false) continue;
        if (i<tau3_index){
            tau3_index = i; 
            NewBoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(i), boostedTauEta->at(i), boostedTauPhi->at(i), boostedTauMass->at(i));
            tau3_charge = boostedTauCharge->at(i); 
            plotFill("tau3_index", i , 40, 0, 7, LumiWeight);
        }
    } 
    int tau4_index = MatchBoostedTauAgain(NewBoostedTau4Momentum, tau3_charge, tau1_index, tau2_index, tau3_index); 
    if (tau4_index < 0) continue; 


    tau4_charge = boostedTauCharge->at(tau4_index); 
    //H2 charge
    // if the charge of tau4 *tau3 is negative, then Higgs2 is OS
    if (tau4_charge * tau3_charge < 0){
        H2OS = 1; 
    }
    if (tau4_charge * tau3_charge > 0){
       H2OS = 0;
    }
    plotFill("H2OS", H2OS, 50, -.5, .5);

    SecondPair4Momentum.SetPtEtaPhiM(boostedTauPt->at(tau4_index), boostedTauEta->at(tau4_index), boostedTauPhi->at(tau4_index), boostedTauMass->at(tau4_index));
    plotFill("tau4_index", tau4_index, 40, .5, 8, LumiWeight);
    
    //constructing the higgs, get their dr and vis mass
    higgs1_momentum = leadtau4mom + LeadMatch4Momentum;
    higgs2_momentum = SecondPair4Momentum + NewBoostedTau4Momentum;
    higgs1_dr = leadtau4mom.DeltaR(LeadMatch4Momentum);
    higgs2_dr = NewBoostedTau4Momentum.DeltaR(SecondPair4Momentum);
    vis_mass= higgs1_momentum.M();
    vis_mass2 = higgs2_momentum.M();
    plotFill("higgs1_vis_mass", vis_mass, 50, 0, 250, LumiWeight);
    plotFill("higgs1_dr", higgs1_dr, 50, 0, 1.5, LumiWeight);
    plotFill("higgs2_vis_mass", vis_mass2, 50, 0, 250, LumiWeight); 
    plotFill("higgs2_dr", higgs2_dr, 50, 0, 1.5, LumiWeight); 

    
    if (vis_mass < 10) continue;

   if (vis_mass2 < 10) continue;
    
    
    // pt of each tau
    tau1_h1_pt = leadtau4mom.Pt();
    tau2_h1_pt = NewBoostedTau4Momentum.Pt();
    tau1_h2_pt = SecondPair4Momentum.Pt();
    tau2_h2_pt = LeadMatch4Momentum.Pt();

    plotFill("tau1_h1_pt", tau1_h1_pt, 50, 0, 1500, LumiWeight);
    plotFill("tau2_h1_pt", tau2_h1_pt, 50, 0, 1500, LumiWeight);
    plotFill("tau1_h2_pt", tau1_h2_pt, 50, 0, 1500, LumiWeight);
    plotFill("tau2_h2_pt", tau2_h2_pt, 50, 0, 1500, LumiWeight);

    // delta phi between the two tau in higgs 2
    dphi_H2 = SecondPair4Momentum.DeltaPhi(NewBoostedTau4Momentum);
    plotFill("dphi_H2", dphi_H2, 50, -4, 4, LumiWeight);

    // delta phi between the two tau in higgs 1
    dphi_H1 = LeadMatch4Momentum.DeltaPhi(leadtau4mom);
    plotFill("dphi_H1", dphi_H1, 50, -4, 4, LumiWeight);

    //delta phi between the two higgs
    dphi_HH = higgs1_momentum.DeltaPhi(higgs2_momentum);
    plotFill("dphi_HH", dphi_HH, 50, -4, 4, LumiWeight);

    //get the pt of each higgs
    higgs_pT = higgs1_momentum.Pt();
    higgs_pT2 = higgs2_momentum.Pt();
    radion_pt = higgs_pT + higgs_pT2;
    plotFill("higgs_pt1", higgs_pT, 50, 0, 1500, LumiWeight);
    plotFill("higgs_pt2", higgs_pT2, 50, 0, 1400, LumiWeight);
    plotFill("radion_pt", radion_pt, 50, 0, 2000, LumiWeight);


    //find invariant mass of the two higgs (radion) and plot
    TLorentzVector radion4momentum;
    radion4momentum = higgs1_momentum + higgs2_momentum;
    radion_inv_mass = radion4momentum.M();
    rad_eta = radion4momentum.Eta();
    plotFill("radion_inv_mass", radion_inv_mass, 50, 0, 2600, LumiWeight); 
    plotFill("radion_eta", rad_eta, 50, -5, 5, LumiWeight);

    // delta R between the two Higgs
    dr_HH = higgs1_momentum.DeltaR(higgs2_momentum);
    if (dr_HH < 2) continue;
    plotFill("dr_HH", dr_HH, 50, 0, 5, LumiWeight); 

    // HT
    TLorentzVector rad4Momentum;
    rad4Momentum = leadtau4mom + LeadMatch4Momentum + NewBoostedTau4Momentum + SecondPair4Momentum;
    HT = rad4Momentum.Pt();
    plotFill("HT", HT, 50, 0, 1600, LumiWeight);

    //MET
    plotFill("MET", pfMET, 50, 0, 1000, LumiWeight);

    //MHT
    plotFill("pfMHT", pfMHT, 50, 0, 1000, LumiWeight);



    // BJet veto
    numBJet=numBJets(BJetPtCut,DeepCSVCut,JetSys);
    //std::cout<<BJetPtCut<<endl;
    //if (numBJet > 0) continue;
    plotFill("numBJet", numBJet, 15,0,15);
    


    // muons
    for (int i = 0; i < nMu; ++i){
        Muon4Momentum.SetPtEtaPhiM(muPt->at(i), muEta->at(i), muPhi->at(i), muMass);
        if (Muon4Momentum.Pt() < 20) continue;
        tau_dR result = MatchTauToMuon(Muon4Momentum);
        int min_dR_index_muon = result.min_dR_index;
        float min_dR = result.min_dR;
        plotFill("min_dR_index_tau_muon", min_dR_index_muon, 50, 0 , 9, LumiWeight);
        plotFill("min_dR_muon", min_dR, 50, 0, 1, LumiWeight);

        muon_pt = Muon4Momentum.Pt();
        MatchedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(min_dR_index_muon), boostedTauEta->at(min_dR_index_muon), boostedTauPhi->at(min_dR_index_muon), boostedTauMass->at(min_dR_index_muon));
        
        //plotFill("muon_pt", muon_pt, 50, 0, 1000);
        plotFill("muon_Eta", muEta->at(i), 50, 0, 10, LumiWeight);
        plotFill("muon_Phi", muPhi->at(i), 50, 0, 10, LumiWeight);
        
        matched_tau_pt = MatchedTau4Momentum.Pt();
        ratio = (muon_pt - matched_tau_pt) / matched_tau_pt;
        plotFill("ratio", ratio, 50, -1.1, 1.1, LumiWeight);
    }

    // electrons
    TLorentzVector Electron4Momentum, MatchTau4Momentum;
    for (int i = 0; i < nEle; ++i){
        Electron4Momentum.SetPtEtaPhiM(elePt->at(i), eleEta->at(i), elePhi->at(i), eleMass);
        if (Electron4Momentum.Pt() < 20) continue;
        tau_ele_dR result = MatchTauToElectron(Electron4Momentum);
        int min_dR_index2 = result.min_dR_index2;
        float min_dR2 = result.min_dR2;
        plotFill("min_dR_index_tau_ele", min_dR_index2, 50, 0 , 9, LumiWeight);
        plotFill("min_dR_electron", min_dR2, 50, 0, 1, LumiWeight);

        ele_pt = Electron4Momentum.Pt();
        MatchTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(min_dR_index2), boostedTauEta->at(min_dR_index2), boostedTauPhi->at(min_dR_index2), boostedTauMass->at(min_dR_index2));
        

        match_tau_pt = MatchTau4Momentum.Pt();
        ratio2 = (ele_pt - match_tau_pt) / match_tau_pt;
        plotFill("ratio2", ratio2, 50, -1.1, 1.1, LumiWeight);
    }


    // TMass
    TMass_H1 = TMass_F(higgs1_momentum.Pt(), higgs1_momentum.Px(), higgs1_momentum.Py(), pfMET, pfMETPhi);
    TMass_H2 = TMass_F(higgs2_momentum.Pt(), higgs2_momentum.Px(), higgs2_momentum.Py(), pfMET, pfMETPhi);
    TMass_Radion = TMass_F(rad4Momentum.Pt(), rad4Momentum.Px(), rad4Momentum.Py(), pfMET, pfMETPhi);
    plotFill("TMass_H1", TMass_H1, 50, 0, 5000, LumiWeight);
    plotFill("TMass_H2", TMass_H2, 50, 0, 2500, LumiWeight);
    plotFill("TMass_Radion", TMass_Radion, 50, 0, 4500, LumiWeight);
    plotFill("METPhi", pfMETPhi, 50, 0, 5, LumiWeight);


    //dPhi plots
    Met4Momentum.SetPtEtaPhiM(pfMET, 0, pfMETPhi, 0);
    dphi_H1_MET = higgs1_momentum.DeltaPhi(Met4Momentum);
    dphi_H2_MET = higgs2_momentum.DeltaPhi(Met4Momentum);
    dphi_rad_MET = rad4Momentum.DeltaPhi(Met4Momentum);
    dphi_H1_Rad = higgs1_momentum.DeltaPhi(rad4Momentum);
    dphi_H2_Rad = higgs2_momentum.DeltaPhi(rad4Momentum);
    plotFill("dphi_H2_Rad", dphi_H2_Rad, 50, -4, 4, LumiWeight);
    plotFill("dphi_H1_Rad", dphi_H1_Rad, 50, -4, 4), LumiWeight;
    plotFill("dphi_H1_MET", dphi_H1_MET, 50, -4, 4, LumiWeight);
    plotFill("dphi_H2_MET", dphi_H2_MET, 50, -4, 4, LumiWeight);
    plotFill("dphi_rad_MET", dphi_rad_MET, 50, -4, 4, LumiWeight);

    //dr between higgs and radion
    dr_H1_Rad = higgs1_momentum.DeltaPhi(rad4Momentum);
    dr_H2_Rad = higgs2_momentum.DeltaPhi(rad4Momentum);
    plotFill("dr_H1_Rad", dr_H1_Rad, 50, -4, 4, LumiWeight);
    plotFill("dr_H2_Rad", dr_H2_Rad, 50, -4, 4, LumiWeight);


    plotFill("LumiWeight", LumiWeight, 50, 0, 2);
    


    //Trigger
    PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v //HLT_AK8PFJet400_TrimMass30_v
    PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v

    plotFill("PassTrigger_40", PassTrigger_40, 100,0,1.25);
    plotFill("PassTrigger_39", PassTrigger_39, 100, 0, 1.25);

    /*
    if (PassTrigger_40 == 1){
        plotFill("aftercuts_trigger40", PassTrigger_40, 100, 0, 1.25);
    }

    if (PassTrigger_39==1){
        plotFill("aftercuts_trigger39", PassTrigger_39, 100, 0, 1.25);
    }
    
    if (PassTrigger_40 ==1 && PassTrigger_39==1){
        pass_both_triggers = (PassTrigger_39 + PassTrigger_40)/2;
        plotFill("passed both triggers", pass_both_triggers, 100, .99 , 1.01);
    }
    

    if (PassTrigger_50 == 1){
        plotFill("passtrigger_50_aftercuts", PassTrigger_50, 100, 0, 1.25);
    }
    if (pfmet_pfmht_trigger==1){
        plotFill("Pass_pfmet_pfmht_trigger_aftercuts", pfmet_pfmht_trigger, 100, 0, 1.25);
    }
    if (PassTrigger_50 ==1 && pfmet_pfmht_trigger ==1){
        pass_both_triggers = (PassTrigger_50 + pfmet_pfmht_trigger)/2;
        plotFill("passed both triggers", pass_both_triggers, 100, .99, 1.01);
    }
    */


    //std::cout<<pfMET<<endl;
    //std::cout<<MHT<<endl;
    //std::cout<<TrimMass<<endl;
    //std::cout<<AK8Jet<<endl;
    //std::cout<<PFHT<<endl;
    //PFMET_MHT = pfMET + MHT;
    plotFill("PFMET_MHT", PFMET_MHT, 50, 0, 1000);
    plotFill("PFHT", PFHT, 50, 0, 1500);
    plotFill("MHT", MHT, 50, 0, 1500);
    plotFill("pfMET", pfMET, 50, 0, 1500);


    // trigger 39 outcome (offline cuts)
    efficiency39 = calculate_efficiency_39(PFHT, PFMET_MHT);
    if (efficiency39 == 1.0){
        // denominator (passes offline cuts)
        plotFill("Denominator39", PFHT, PFMET_MHT, 50, 100, 1500, 50, 0, 1100);
    }
    //numerator (passes online cuts and offline cuts)
    if (PassTrigger_39 && efficiency39==1.0){
        plotFill("Numerator39", PFHT, PFMET_MHT, 50, 100, 1500, 50, 0, 1100);
    }

    
    // trigger 40 outcome (offline cuts)
    plotFill("AK8Mass", AK8Mass, 50, 0, 350);
    plotFill("AK8Pt", AK8Pt, 50, 0, 900);

    
    efficiency40 = calculate_efficiency_40(AK8Mass, AK8Pt);
    if (efficiency40 == 1.0){
        // denominator (passes offline cuts)
        plotFill("Denominator40", AK8Mass, AK8Pt, 50, 0, 350, 50, 0, 900);
    }
    // numerator (passes online cuts and offline cuts)
    if (PassTrigger_40 && efficiency40==1.0){
        plotFill("Numerator40", AK8Mass, AK8Pt, 50, 0, 350, 50, 0, 900);
    }
    

    

    // Fill the tree
    outTr->Fill();
        
    } //End of Tree
    

    
    fout->cd();
    unordered_map<string, TH1F*>::const_iterator iMap1 = myMap1->begin();
    unordered_map<string, TH1F*>::const_iterator jMap1 = myMap1->end();
    
    for (; iMap1 != jMap1; ++iMap1)
        nplot1(iMap1->first)->Write();
    outTr->Write();
    
    unordered_map<string, TH2F*>::const_iterator iMap2 = myMap2->begin();
    unordered_map<string, TH2F*>::const_iterator jMap2 = myMap2->end();
    
    for (; iMap2 != jMap2; ++iMap2)
        nplot2(iMap2->first)->Write();
    
    fout->Close();
}