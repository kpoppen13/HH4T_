//#include "../interface/Functions.h"
#include <string>
#include <ostream>
#include <vector>
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooFunctor.h"
#include "RooMsgService.h"
#include "TLorentzVector.h"
#include "../interface/CLParser.h"
#include "../interface/boostHTT_4t.h"
#include "../interface/makeHisto.h"



//function to find which tau are pairs from same higgs
    int MatchBoostedTau(TLorentzVector Object4Momentum, int charge){
        TLorentzVector BoostTau4Momentum;
        float min_dr=100;
        int min_dr_index = -1;
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            if ((boostedTauCharge->at(ibtau) * charge) > 0) continue;
            if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0.5) continue;
            BoostTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
            if(BoostTau4Momentum.DeltaR(Object4Momentum) < min_dr ){
                min_dr = BoostTau4Momentum.DeltaR(Object4Momentum);
                min_dr_index = ibtau;
            }
        }
        return min_dr_index;
    }

//function to find the Tau with the smallest delta R to muon
    struct tau_dR {
    int min_dR_index;
    float min_dR;
    };
    tau_dR MatchTauToMuon(TLorentzVector Muon4Momentum){
        TLorentzVector boostedTau4Momentum;
        float min_dR = 100;
        int min_dR_index = -1;
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0.5) continue;
            boostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
            if (boostedTau4Momentum.DeltaR(Muon4Momentum) < min_dR){
                min_dR = boostedTau4Momentum.DeltaR(Muon4Momentum);
                min_dR_index = ibtau;
            }
        }
        tau_dR result;
        result.min_dR_index = min_dR_index;
        result.min_dR = min_dR;
        return result;
    }

//function to find the Tau with the smallest delta R to electron
    struct tau_ele_dR {
    int min_dR_index2;
    float min_dR2;
    };
    tau_ele_dR MatchTauToElectron(TLorentzVector Electron4Momentum){
        TLorentzVector boostedTau4Momentum;
        float min_dR2 = 100;
        int min_dR_index2 = -1;
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0.5) continue;
            boostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
            if (boostedTau4Momentum.DeltaR(Electron4Momentum) < min_dR2){
                min_dR2 = boostedTau4Momentum.DeltaR(Electron4Momentum);
                min_dR_index2 = ibtau;
            }
        }
        tau_ele_dR result;
        result.min_dR_index2 = min_dR_index2;
        result.min_dR2 = min_dR2;
        return result;
    }

// TMass Definition
float TMass_F(float pt3lep, float px3lep, float py3lep, float met, float metPhi) {
    return sqrt(pow(pt3lep + met, 2) - pow(px3lep + met * cos(metPhi), 2) - pow(py3lep + met * sin(metPhi), 2));
}




int main(int argc, char* argv[]) {
    
    CLParser parser(argc, argv);
    std::string sample = parser.Option("-s");
    std::string name = parser.Option("-n");
//    std::string path = parser.Option("-p");
//    std::string output_dir = parser.Option("-d");
//    std::string syst = parser.Option("-u");
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
    float eleMass= 0.000511;
    float JetPtCut=30;
    float BJetPtCut=30;

    float DeepCSVCut=   1000   ;                  //  loose  https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation94X
    if (year== 2016) DeepCSVCut =     0.8953  ;
    if (year== 2017) DeepCSVCut =     0.8001  ;
    if (year== 2018) DeepCSVCut =    0.7527   ;
//
//    float LeptonIsoCut=0.15;
//    bool debug= false;
//    float LumiWeight = 1;
//    float PUWeight = 1;
//    float LepCorrection=1;
//    float zmasspt_weight=1;
//    float WBosonKFactor=1;
//    float preFireWeight=1;
//    float ttbar_rwt=1;
//    float zmasspt_weight_err=0;
//    float zmasspt_weight_nom=1;
//    float weight_Rivet =1;
//    float weight_g_NNLOPS = 1;
//    float Weight_PS=1;
//
//    float lep1Pt_=-10;
//    float lep2Pt_=-10;
    float vis_mass=-10;
    float vis_mass2=-10;
    float radion_inv_mass=-10;
    float min_dr = 100;
    float lead_tau_iso;
//    float LeadJetPt = -10;
//    float dR_Z_jet=-10;
//    bool lep1IsoPassL,lep2IsoPassL,lep1IsoPassV,lep2IsoPassV,OS,SS;
    float tmass,ht,st,Met,FullWeight, dR_lep_lep, Metphi,BoostedTauRawIso, higgs_pT, higgs_pT2, radion_pt, higgs_m, m_sv_, wtnom_zpt_weight, gen_higgs_pT,gen_leadjet_pT;
    float LeadingBoostedTauPt= -10;
    float SubLeadingBoostedTauPt= -10;
    float ThirdBoostedTauPt= -10;
    float FourthBoostedTauPt= -10;
    float dphi_HH= -10;
    float dr_HH= -10;
    float dphi_H2= -10;
    float dphi_H1= -10;
    float higgs2_dr2= -10;
    float higgs1_dr= -10;
    float fourth_tau_mass= -10;
    float third_tau_mass= -10;
    float sub_tau_mass= -10;
    float lead_tau_mass= -10; 
//    float MuMatchedIsolation= -1; float EleMatchedIsolation =-1;
//    int nbjet, gen_matched1_, gen_matched2_,gen_matched1, gen_matched2, gen_nJet;
//
//    bool isGenTauSub_, isGenTauLead_;
//    bool Chan_emu, Chan_etau, Chan_mutau, Chan_tautau, Chan_emu_fid, Chan_etau_fid, Chan_mutau_fid, Chan_tautau_fid;
//
//    outTr->Branch("evtwt",&FullWeight,"evtwt/F");
//    outTr->Branch("pdfWeight", &pdfWeight);
//    outTr->Branch("pdfSystWeight", &pdfSystWeight);
//    outTr->Branch("pdf", &pdf);
//    outTr->Branch("zmasspt_weight",&zmasspt_weight,"zmasspt_weight/F");
//    outTr->Branch("lep1Pt",&lep1Pt_,"lep1Pt/F");
//    outTr->Branch("lep2Pt",&lep2Pt_,"lep2Pt/F");
//    outTr->Branch("lep1IsoPassL",&lep1IsoPassL,"lep1IsoPassL/O");
//    outTr->Branch("lep2IsoPassL",&lep2IsoPassL,"lep2IsoPassL/O");
//    outTr->Branch("lep1IsoPassV",&lep1IsoPassV,"lep1IsoPassV/O");
//    outTr->Branch("lep2IsoPassV",&lep2IsoPassV,"lep2IsoPassV/O");
//    outTr->Branch("OS",&OS,"OS/O");
//    outTr->Branch("SS",&SS,"SS/O");
   outTr->Branch("vis_mass",&vis_mass,"vis_mass/F");
   outTr->Branch("vis_mass2",&vis_mass2,"vis_mass2/F");
//    outTr->Branch("tmass",&tmass,"tmass/F");
//    outTr->Branch("ht",&ht,"ht/F");
//    outTr->Branch("st",&st,"st/F");
//    outTr->Branch("Met",&Met,"Met/F");
//    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
//    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
//    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
    outTr->Branch("higgs_pT",&higgs_pT,"higgs_pT/F");
    outTr->Branch("higgs_pT2",&higgs_pT2,"higgs_pT/F");
    outTr->Branch("lead_tau_iso",&lead_tau_iso,"lead_tau_iso/F");


    outTr->Branch("lead_tau_mass",&lead_tau_mass,"lead_tau_mass/F");
    outTr->Branch("sub_tau_mass",&sub_tau_mass,"sub_tau_mass/F");
    outTr->Branch("third_tau_mass",&third_tau_mass,"third_tau_mass/F");
    outTr->Branch("fourth_tau_mass",&fourth_tau_mass,"fourth_tau_mass");

    outTr->Branch("higgs1_dr",&higgs1_dr,"higgs1_dr/F");
    outTr->Branch("higgs2_dr",&higgs2_dr2,"higgs2_dr/F");

    outTr->Branch("dphi_H1",&dphi_H1,"dphi_H1/F");
    outTr->Branch("dphi_H2",&dphi_H2,"dphi_H2/F");

    outTr->Branch("dr_HH",&dr_HH,"dr_HH/F");
    outTr->Branch("dphi_HH",&dphi_HH,"dphi_HH/F");

    outTr->Branch("LeadingBoostedTauPt",&LeadingBoostedTauPt,"LeadingBoostedTauPt/F");
    outTr->Branch("SubLeadingBoostedTauPt",&SubLeadingBoostedTauPt,"SubLeadingBoostedTauPt/F");
    outTr->Branch("ThirdBoostedTauPt",&ThirdBoostedTauPt,"ThirdBoostedTauPt/F");
    outTr->Branch("FourthBoostedTauPt",&FourthBoostedTauPt,"FourthBoostedTauPt/F");
//    outTr->Branch("higgs_m",&higgs_m,"higgs_m/F");
//    outTr->Branch("nbjet",&nbjet,"nbjet/I");
//    outTr->Branch("gen_higgs_pT",&gen_higgs_pT,"gen_higgs_pT/F");
//    outTr->Branch("gen_leadjet_pT",&gen_leadjet_pT,"gen_leadjet_pT/F");
//    outTr->Branch("isGenTauLead_",&isGenTauLead_,"isGenTauLead_/O");
//    outTr->Branch("isGenTauSub_",&isGenTauSub_,"isGenTauSub_/O");
//    outTr->Branch("MuMatchedIsolation",&MuMatchedIsolation,"MuMatchedIsolation/F");
//    outTr->Branch("EleMatchedIsolation",&EleMatchedIsolation,"EleMatchedIsolation/F");
//    outTr->Branch("gen_matched1_",&gen_matched1_,"gen_matched1_/I");
//    outTr->Branch("gen_matched2_",&gen_matched2_,"gen_matched2_/I");
//    outTr->Branch("run",&run,"run/I");
//    outTr->Branch("event",&event,"event/I");
//    outTr->Branch("lumis",&lumis,"lumis/I");



  

    


    
    
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
//        //2017 and 2018
//        PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v //HLT_AK8PFJet400_TrimMass30_v
//        PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
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

    //if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(0) < 0.5) continue;
    //if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(1) < 0.5) continue;
    //if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(2) < 0.5) continue;
    //if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(3) < 0.5) continue;
    plotFill("LeadingBoostedTauPt_",LeadingBoostedTauPt ,50,0,2000);
    plotFill("SubLeadingBoostedTauPt_",SubLeadingBoostedTauPt ,50,0,1000);
    plotFill("ThirdBoostedTauPt_",ThirdBoostedTauPt ,50,0,700);
    plotFill("FourthBoostedTauPt_",FourthBoostedTauPt ,50,0,500);

        
        //=========================================================================================================
        // Event Selection
        //=========================================================================================================

    //get the four momentum for each of the first four Tau
    TLorentzVector ThirdTau4Momentum, FourthTau4Momentum, Third_and_Fourth_Momentum;    
    LeadTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(0), boostedTauEta->at(0), boostedTauPhi->at(0), boostedTauMass->at(0));
    SubTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(1), boostedTauEta->at(1), boostedTauPhi->at(1), boostedTauMass->at(1));
    ThirdTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(2), boostedTauEta->at(2), boostedTauPhi->at(2), boostedTauMass->at(2));
    FourthTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(3), boostedTauEta->at(3), boostedTauPhi->at(3), boostedTauMass->at(3));


    // plot mass of each tau
    float lead_tau_mass, sub_tau_mass, third_tau_mass, fourth_tau_mass;
    lead_tau_mass = LeadTau4Momentum.M();
    sub_tau_mass = SubTau4Momentum.M();
    third_tau_mass = ThirdTau4Momentum.M();
    fourth_tau_mass = FourthTau4Momentum.M();
    plotFill("lead_tau_mass", lead_tau_mass, 50, 0, 2);
    plotFill("sub_tau_mass", sub_tau_mass, 50, 0, 2);
    plotFill("third_tau_mass", third_tau_mass, 50, 0, 2);
    plotFill("fourth_tau_mass", fourth_tau_mass, 50, 0, 2);


    // check isolation of each tau
    float subtau_iso, third_tau_iso, fourth_tau_iso;
    lead_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(0);
    //if (lead_tau_iso < .5) continue;
    subtau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(1);
    //if (subtau_iso < .5) continue;
    third_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(2);
    //if (third_tau_iso < .5) continue;
    fourth_tau_iso = boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(3);
    //if (fourth_tau_iso < .5) continue;
    
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
    
    //matching the pairs
    TLorentzVector NewBoostedTau4Momentum, LeadMatch4Momentum, higgs1_momentum, SecondPair4Momentum, higgs2_momentum; 
    //find index of the tau that matches to the lead tau 
    int index_lead_match = MatchBoostedTau(LeadTau4Momentum, boostedTauCharge->at(0));
    if (index_lead_match < 0) continue;
    //plot their visible mass
    LeadMatch4Momentum.SetPtEtaPhiM(boostedTauPt->at(index_lead_match), boostedTauEta->at(index_lead_match), boostedTauPhi->at(index_lead_match), boostedTauMass->at(index_lead_match));
    float higgs1_dr;
    higgs1_dr = LeadTau4Momentum.DeltaR(LeadMatch4Momentum);
    higgs1_momentum = LeadTau4Momentum + LeadMatch4Momentum;
    vis_mass= higgs1_momentum.M();
    plotFill("higgs1_vis_mass", vis_mass, 50, 0, 250);
    plotFill("higgs1_dr", higgs1_dr, 50, 0, 1.5);
    plotFill("lead_match_indices", index_lead_match, 40, .5, 8);

    // delta phi between the two tau in higgs 1
    float dphi_H1;
    dphi_H1 = LeadMatch4Momentum.DeltaPhi(LeadTau4Momentum);
    plotFill("dphi_H1", dphi_H1, 50, 0, 5);
    

    //now eliminate the two indices that are a pair
    float newcharge = 0;
    for (int i=0; i <nBoostedTau; i++){
        if (i ==0) continue;
        if (i==index_lead_match) continue;
        NewBoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(i), boostedTauEta->at(i), boostedTauPhi->at(i), boostedTauMass->at(i));
        newcharge = boostedTauCharge->at(i);
        plotFill("new_boosted_tau_index", i , 40, 0, 7);

    }


    //call match boosted tau function again now that the first pair is eliminated, in order to match the second pair
    int index_match_2 = MatchBoostedTau(NewBoostedTau4Momentum, newcharge);
    if (index_match_2 < 0) continue;
    //plot their visible mass
    SecondPair4Momentum.SetPtEtaPhiM(boostedTauPt->at(index_match_2), boostedTauEta->at(index_match_2), boostedTauPhi->at(index_match_2), boostedTauMass->at(index_match_2));
    higgs2_momentum = SecondPair4Momentum + NewBoostedTau4Momentum;
    float higgs2_dr;
    higgs2_dr = NewBoostedTau4Momentum.DeltaR(SecondPair4Momentum);
    vis_mass2 = higgs2_momentum.M();
    plotFill("higgs2_vis_mass", vis_mass2, 50, 0, 250); 
    plotFill("higgs2_dr", higgs2_dr, 50, 0, 1.5); 
    plotFill("new_boosted_tau_match_index", index_match_2, 40, .5, 8);
    
    // delta phi between the two tau in higgs 2
    float dphi_H2;
    dphi_H2 = SecondPair4Momentum.DeltaPhi(NewBoostedTau4Momentum);
    plotFill("dphi_H2", dphi_H2, 50, 0, 5);


    //delta phi between the two higgs
    float dphi_HH=-10;
    dphi_HH = higgs1_momentum.DeltaPhi(higgs2_momentum);
    plotFill("dphi_HH", dphi_HH, 50, 0, 5);



    //get the pt of each higgs
    higgs_pT = higgs1_momentum.Pt();
    higgs_pT2 = higgs2_momentum.Pt();
    radion_pt = higgs_pT + higgs_pT2;
    plotFill("higgs_pt1", higgs_pT, 50, 0, 1500);
    plotFill("higgs_pt2", higgs_pT2, 50, 0, 1400);
    plotFill("radion_pt", radion_pt, 50, 0, 1000);

    

    //find invariant mass of the two higgs (radion) and plot
    TLorentzVector radion4momentum;
    radion4momentum = higgs1_momentum + higgs2_momentum;
    radion_inv_mass = radion4momentum.M();
    plotFill("radion_inv_mass", radion_inv_mass, 50, 0, 2200); 

    // delta R between the two Higgs
    float dr_HH;
    dr_HH = higgs1_momentum.DeltaR(higgs2_momentum);
    plotFill("dr_HH", dr_HH, 50, 0, 5); 

    // HT
    float HT, TMass;
    TLorentzVector rad4Momentum;
    rad4Momentum = LeadTau4Momentum + LeadMatch4Momentum + NewBoostedTau4Momentum + SecondPair4Momentum;
    HT = rad4Momentum.Pt();
    
    plotFill("HT", HT, 50, 0, 1600);

    //MET
    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
        if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(ibtau) < 0.5) continue;
        plotFill("MET", pfMET, 50, 0, 1000);
    }


    


    // muons
    TLorentzVector Muon4Momentum, MatchedTau4Momentum;
    float muMass = 0.10565837;
    float muon_pt;
    float matched_tau_pt;
    float ratio;
    for (int i = 0; i < nMu; ++i){
        Muon4Momentum.SetPtEtaPhiM(muPt->at(i), muEta->at(i), muPhi->at(i), muMass);
        if (Muon4Momentum.Pt() < 20) continue;
        tau_dR result = MatchTauToMuon(Muon4Momentum);
        int min_dR_index_muon = result.min_dR_index;
        float min_dR = result.min_dR;
        plotFill("min_dR_index_tau_muon", min_dR_index_muon, 50, 0 , 9);
        plotFill("min_dR_muon", min_dR, 50, 0, 2);

        muon_pt = Muon4Momentum.Pt();
        MatchedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(min_dR_index_muon), boostedTauEta->at(min_dR_index_muon), boostedTauPhi->at(min_dR_index_muon), boostedTauMass->at(min_dR_index_muon));
        
        //plotFill("muon_pt", muon_pt, 50, 0, 1000);
        plotFill("muon_Eta", muEta->at(i), 50, 0, 10);
        plotFill("muon_Phi", muPhi->at(i), 50, 0, 10);
        
        matched_tau_pt = MatchedTau4Momentum.Pt();
        ratio = (muon_pt - matched_tau_pt) / matched_tau_pt;
        plotFill("ratio", ratio, 50, -1.1, 1.1);
    }

    // electrons
    TLorentzVector Electron4Momentum, MatchTau4Momentum;
    float eleMass = 0.000511;
    float ele_pt;
    float match_tau_pt;
    float ratio2;
    for (int i = 0; i < nEle; ++i){
        Electron4Momentum.SetPtEtaPhiM(elePt->at(i), eleEta->at(i), elePhi->at(i), eleMass);
        if (Electron4Momentum.Pt() < 20) continue;
        tau_ele_dR result = MatchTauToElectron(Electron4Momentum);
        int min_dR_index2 = result.min_dR_index2;
        float min_dR2 = result.min_dR2;
        plotFill("min_dR_index_tau_ele", min_dR_index2, 50, 0 , 9);
        plotFill("min_dR_electron", min_dR2, 50, 0, 2);

        ele_pt = Electron4Momentum.Pt();
        MatchTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(min_dR_index2), boostedTauEta->at(min_dR_index2), boostedTauPhi->at(min_dR_index2), boostedTauMass->at(min_dR_index2));
        

        match_tau_pt = MatchTau4Momentum.Pt();
        ratio2 = (ele_pt - match_tau_pt) / match_tau_pt;
        plotFill("ratio2", ratio2, 50, -1.1, 1.1);
    }


    // TMass
    float TMass_H1, TMass_H2, TMass_Radion;
    TMass_H1 = TMass_F(higgs1_momentum.Pt(), higgs1_momentum.Px(), higgs1_momentum.Py(), Met, Metphi);
    
    TMass_H2 = TMass_F(higgs2_momentum.Pt(), higgs2_momentum.Px(), higgs2_momentum.Py(), Met, Metphi);
    TMass_Radion = TMass_F(rad4Momentum.Pt(), rad4Momentum.Px(), rad4Momentum.Py(), Met, Metphi);
    plotFill("TMass_H1", TMass_H1, 50, 0, .5);
    plotFill("TMass_H2", TMass_H2, 50, 0, .5);
    plotFill("TMass_Radion", TMass_Radion, 50, 0, .5);




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





