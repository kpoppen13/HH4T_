//#include "../interface/Functions.h"
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




// function to chek if tau is good 
// true = good tau, false = bad tau
bool isTauGood(int tau_index) {
    bool good_or_bad = true; // Initialize to true by default
    if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(tau_index) < 0.5 || 
        boostedTaupfTausDiscriminationByDecayModeFinding->at(tau_index) < 0.5 || 
        (boostedTauPt->at(tau_index) <= 30 || fabs(boostedTauEta->at(tau_index)) >= 2.3)) {
        good_or_bad = false;
    }
    return good_or_bad;
}


//function to find which tau are pairs from same higgs
    int MatchBoostedTau(TLorentzVector Object4Momentum, int charge){
        TLorentzVector BoostTau4Momentum;
        float min_dr=100;
        int min_dr_index = -1;
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            if ((boostedTauCharge->at(ibtau) * charge) > 0) continue;
            if (isTauGood(ibtau) == false) continue;
            BoostTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(ibtau),boostedTauEta->at(ibtau),boostedTauPhi->at(ibtau),boostedTauMass->at(ibtau));
            if(BoostTau4Momentum.DeltaR(Object4Momentum) < min_dr ){
                min_dr = BoostTau4Momentum.DeltaR(Object4Momentum);
                min_dr_index = ibtau;
            }
        }
        return min_dr_index;
    }

//function to find which tau are pairs from same higgs
    int MatchBoostedTauAgain(TLorentzVector Object4Momentum, int charge, int lead_index, int lead_index_match){
        TLorentzVector BoostTau4Momentum;
        float min_dr=100;
        int min_dr_index = -1;
        for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
            if (ibtau == lead_index) continue;
            if (ibtau == lead_index_match) continue;
            if ((boostedTauCharge->at(ibtau) * charge) > 0) continue;
            if (isTauGood(ibtau) == false) continue;
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
            if (isTauGood(ibtau) == false) continue;
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
            if (isTauGood(ibtau) == false) continue;
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

// function to find Z to ee multiplicity
int Zto_ee_multiplicity(){
    TLorentzVector lead_electron4Momentum, sublead_electron4Momentum;
    int Z_multiplicity_ele = 0;
    bool eleMVAId= false;
    bool eleMVAId2 = false;
    std::vector<int> indices_used;
    for (int iEle = 0; iEle < nEle; ++iEle){
        std::vector<int>::iterator it = std::find(indices_used.begin(), indices_used.end(), iEle);
        if (it != indices_used.end()) continue;
        // check ID
        if (fabs (eleSCEta->at(iEle)) <= 0.8 && eleIDMVANoIso->at(iEle) >    0.837   ) eleMVAId= true;
        else if (fabs (eleSCEta->at(iEle)) >  0.8 &&fabs (eleSCEta->at(iEle)) <=  1.5 && eleIDMVANoIso->at(iEle) >    0.715   ) eleMVAId= true;
        else if ( fabs (eleSCEta->at(iEle)) >=  1.5 && eleIDMVANoIso->at(iEle) >   0.357   ) eleMVAId= true;
        else eleMVAId= false;
        if (!eleMVAId) continue;
        
        lead_electron4Momentum.SetPtEtaPhiM(elePt->at(iEle), eleEta->at(iEle), elePhi->at(iEle), 0.000511);
        
        for (int jEle = iEle +1; jEle < nEle; ++jEle){
            std::vector<int>::iterator it = std::find(indices_used.begin(), indices_used.end(), jEle);
            if (it != indices_used.end()) continue;
            if (fabs (eleSCEta->at(jEle)) <= 0.8 && eleIDMVANoIso->at(jEle) >    0.837   ) eleMVAId2= true;
            else if (fabs (eleSCEta->at(jEle)) >  0.8 &&fabs (eleSCEta->at(jEle)) <=  1.5 && eleIDMVANoIso->at(jEle) >    0.715   ) eleMVAId2= true;
            else if ( fabs (eleSCEta->at(jEle)) >=  1.5 && eleIDMVANoIso->at(jEle) >   0.357   ) eleMVAId2= true;
            else eleMVAId2= false;
            if (!eleMVAId2) continue;
            if (eleCharge->at(iEle) * eleCharge->at(jEle) > 0) continue;
            sublead_electron4Momentum.SetPtEtaPhiM(elePt->at(jEle), eleEta->at(jEle), elePhi->at(jEle), 0.000511);
        //find mass of the electron pair, add to Z multiplicity
        float ee_mass = (lead_electron4Momentum + sublead_electron4Momentum).M();
        if (ee_mass >= 80 && ee_mass <= 100){
            Z_multiplicity_ele++;
            indices_used.push_back(iEle);
            indices_used.push_back(jEle);
        }
        
            }
    }
            return Z_multiplicity_ele;
    }
    




// function to find Z to muon muon multiplicity
int Zto_mumu_multiplicity(){
    TLorentzVector lead_muon4Momentum, sublead_muon4Momentum;
    int min_index = 100;
    int min_sublead_index = 100;
    int Z_multiplicity_muon = 0;
    float min_dr=100;
    int min_dr_index = -1;
    std::vector<int> indices_used;
    for (int iMu = 0; iMu < nMu; ++iMu){
        std::vector<int>::iterator it = std::find(indices_used.begin(), indices_used.end(), iMu);
        if (it != indices_used.end()) continue;
        //check ID of lead
        bool MuId=((muIDbit->at(iMu) >> 1 & 1)  && fabs(muD0->at(iMu)) < 0.045 && fabs(muDz->at(iMu)) < 0.2);
        if (MuId == false) continue;
        lead_muon4Momentum.SetPtEtaPhiM(muPt->at(iMu), muEta->at(iMu), muPhi->at(iMu), 0.10565837);

        for (int jMu = iMu +1; jMu < nMu; ++jMu){
            std::vector<int>::iterator it = std::find(indices_used.begin(), indices_used.end(), jMu);
            if (it != indices_used.end()) continue;
            bool MuId2=((muIDbit->at(jMu) >> 1 & 1)  && fabs(muD0->at(jMu)) < 0.045 && fabs(muDz->at(jMu)) < 0.2);
            if (! MuId2) continue;
            if (muCharge->at(iMu) * muCharge->at(jMu) > 0) continue;
            sublead_muon4Momentum.SetPtEtaPhiM(muPt->at(jMu), muEta->at(jMu), muPhi->at(jMu), 0.10565837);
            

        // find mass of muon pair, add to Z multiplicity
        float mumu_mass = (lead_muon4Momentum + sublead_muon4Momentum).M();
        if (mumu_mass >= 80 && mumu_mass <= 100){
            Z_multiplicity_muon++;
            indices_used.push_back(iMu);
            indices_used.push_back(jMu);
            }
        }
    }
    return Z_multiplicity_muon;
}


// function to find ST (from his code)
float getST( float SimpleJetPtCut, string JetSys){
    float ST=0;
    
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPt->at(ijet);
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPtTotUncUp->at(ijet);
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 3.0 )
                ST += jetPtTotUncDown->at(ijet);
        }
    }
    
    return ST;
}


// function to find MHT (from his code)
float getMHT( float SimpleJetPtCut, string JetSys){
    float MHT_x=0;
    float MHT_y=0;
    
    if (JetSys.find("Nominal")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPt->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPt->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPt->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    else if (JetSys.find("JetTotUp")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncUp->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPtTotUncUp->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPtTotUncUp->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    else if (JetSys.find("JetTotDown")!=string::npos){
        for (int ijet= 0 ; ijet < nJet ; ijet++){
            if (jetPFLooseId->at(ijet) > 0.5 && jetPtTotUncDown->at(ijet) > SimpleJetPtCut && fabs(jetEta->at(ijet)) < 5.0 )
                MHT_x += jetPtTotUncDown->at(ijet)*cos(jetPhi->at(ijet));
            MHT_y += jetPtTotUncDown->at(ijet)*sin(jetPhi->at(ijet));
        }
    }
    return sqrt(MHT_x*MHT_x + MHT_y*MHT_y);
}

// function to find efficiency (trigger 39)
float calculate_efficiency_39(float PFHT, float PFMET_PFMHT){
    float efficiency_39;
    float passing;
    if (PFHT > 500 && PFMET_PFMHT > 200){
        efficiency_39 = 1.0;
    }
    else{
        efficiency_39 = 0.0;
    }
    return efficiency_39;
}


// function to find efficiency (trigger 40)
float calculate_efficiency_40(float TrimMass, float AK8Jet){
    float efficiency_40;
    if (TrimMass > 5 && AK8Jet > 50){
        efficiency_40 = 1.0;
    }
    else{
        efficiency_40 = 0.0;
    }
    return efficiency_40;
}


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
    float LumiWeight = 1;
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
    float PFMET_PFMHT;

    
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
   outTr->Branch("LumiWeight",&LumiWeight,"LumiWeight/F");

   outTr->Branch("pfMET",&pfMET,"pfMET/F");
//    outTr->Branch("tmass",&tmass,"tmass/F");
//    outTr->Branch("ht",&ht,"ht/F");
//    outTr->Branch("st",&st,"st/F");
//    outTr->Branch("Met",&Met,"Met/F");
//    outTr->Branch("LeadJetPt",&LeadJetPt,"LeadJetPt/F");
//    outTr->Branch("dR_lep_lep",&dR_lep_lep,"dR_lep_lep/F");
//    outTr->Branch("BoostedTauRawIso",&BoostedTauRawIso,"BoostedTauRawIso/F");
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
PassTrigger_40 = ((HLTJet >> 40 & 1)==1); //HLT_AK8PFJet400_TrimMass30_v 
PassTrigger_39 = ((HLTJet >> 39 & 1)==1); //HLT_PFHT500_PFMET100_PFMHT100_IDTight_v

//std::cout << "PassTrigger_40: " << PassTrigger_40 << endl;
if (PassTrigger_40 == 1){
    plotFill("passtrigger_40_beforecuts", PassTrigger_40, 100, 0, 1.25);
}
if (PassTrigger_39 == 1){
    plotFill("passtrigger_39_beforecuts", PassTrigger_39, 100, 0, 1.25);
}
plotFill("PassTrigger_40", PassTrigger_40, 100,0,1.25);
plotFill("PassTrigger_39", PassTrigger_39, 100, 0, 1.25);


    
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
        float AK8Pt=0;
        float AK8Mass=0;
        float AK8Eta=100;
        

        //come back to this section

        float PFHT= getST(JetPtCut,JetSys); 
        float PFMET=Met;
        float MHT=getMHT(JetPtCut,JetSys);
        
        float TriggerWeight = 1;
        float TriggerWeightError = 1;
        float _cut_AK8Pt_,_cut_AK8Mass_,_cut_PFHT_,_cut_PFMET_,_cut_PFMHT_, _cut_PFMETMHT_, _cut_st_;
        bool _Pass_AK8_Trigger_, _Pass_METHT_Trigger_;


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
    //_cut_PFMETMHT_ = 280;
    _Pass_AK8_Trigger_=PassTrigger_40;
    _Pass_METHT_Trigger_=PassTrigger_39;
    //_cut_st_ = 600;
    }

    /*
    ////apply trigger only on data
    bool passing;
    if (year == 2018){
        // trigger 39     HLT_PFHT500_PFMET100_PFMHT100_IDTight_v
        //&& PFMHT > _cut_PFMHT_ need to add this into the if statement eventually
        if (PFHT > _cut_PFHT_ && PFMET > _cut_PFMET_  && _Pass_METHT_Trigger_){ 
            //TriggerWeight = getTriggerWeight(year, isData, AK8Pt, AK8Mass, triggerEff_HT_SF);
            //TriggerWeightError = getTriggerWeightError(year, isData,  AK8Pt , AK8Mass ,triggerEff_HT_SF);
            passing = true;
        }
        // trigger 40     HLT_AK8PFJet400_TrimMass30_v
        else if(_Pass_AK8_Trigger_){ 
            //TriggerWeight = getTriggerWeight(year, isData, PFHT, PFMET, MHT, triggerEff_MET_SF);
            //TriggerWeightError = getTriggerWeightError(year, isData, PFHT, PFMET, MHT, triggerEff_MET_SF);
            passing = true;
        }
        else {
            passing = false;
        }
    }
    if (! passing) continue; //FIXME  this is for trigger studies for embedded

    std::cout<<"passing: "<<passing<<endl;
    */

    
//===============================================================================================
// ^^

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
    // sets LumiWeight to 1 for signal
    if (LumiWeight == 0){
        LumiWeight = 1;
    }
    //std::cout<<LumiWeight<<endl;

    int Z_multiplicity = 0;
    Z_multiplicity = Zto_mumu_multiplicity() + Zto_ee_multiplicity();
    plotFill("Z_multiplicity", Z_multiplicity, 50, 0, 4.5);
    plotFill("Z_muon_mult", Zto_mumu_multiplicity(), 50, 0, 4.5);
    plotFill("Z_ee_mult", Zto_ee_multiplicity(), 50, 0, 4.5);
    //plotFill("Z_ee_mumu_mult", Zto_mumu_multiplicity(), Zto_ee_multiplicity(), 50, 0, 10);
    if (Z_multiplicity > 0) continue;
    

    //matching the pairs
    TLorentzVector NewBoostedTau4Momentum, LeadMatch4Momentum, higgs1_momentum, SecondPair4Momentum, higgs2_momentum; 
    // get lead tau
    bool good_or_bad_match = true;
    int min_index = 15;
    float lead_charge;
    TLorentzVector leadtau4mom;
    for (int ibtau = 0; ibtau < nBoostedTau; ++ibtau){
        good_or_bad_match = isTauGood(ibtau);
        if (good_or_bad_match == false) continue;
        if (ibtau<min_index){
            min_index = ibtau;
            leadtau4mom.SetPtEtaPhiM(boostedTauPt->at(ibtau), boostedTauEta->at(ibtau), boostedTauPhi->at(ibtau), boostedTauMass->at(ibtau));
            lead_charge = boostedTauCharge->at(ibtau);
            plotFill("Lead_Tau_Index", ibtau, 50, 0, 5, LumiWeight);
            
        }

    }
    
    // once I have the lead tau, find the match (the cuts are in the functions, so it should pick good taus)
    int index_lead_match = MatchBoostedTau(leadtau4mom, lead_charge);
    if (index_lead_match < 0) continue;
    LeadMatch4Momentum.SetPtEtaPhiM(boostedTauPt->at(index_lead_match), boostedTauEta->at(index_lead_match), boostedTauPhi->at(index_lead_match), boostedTauMass->at(index_lead_match));
    plotFill("Lead_Tau's_Match_Index", index_lead_match, 40, .5, 8, LumiWeight);

    int min2_index = 15;
    float newcharge = 0;
    for (int i = 0; i< nBoostedTau; i++){
        if (i == min_index) continue;
        if (i == index_lead_match) continue;
        if (isTauGood(i) == false) continue;
        if (i<min2_index){
            min2_index = i;
            NewBoostedTau4Momentum.SetPtEtaPhiM(boostedTauPt->at(i), boostedTauEta->at(i), boostedTauPhi->at(i), boostedTauMass->at(i));
            newcharge = boostedTauCharge->at(i);
            plotFill("new_boosted_tau_index", i , 40, 0, 7, LumiWeight);
        }
    } 

    int index_match_2 = MatchBoostedTauAgain(NewBoostedTau4Momentum, newcharge, min_index, index_lead_match);
    if (index_match_2 < 0) continue; 
    SecondPair4Momentum.SetPtEtaPhiM(boostedTauPt->at(index_match_2), boostedTauEta->at(index_match_2), boostedTauPhi->at(index_match_2), boostedTauMass->at(index_match_2));
    plotFill("new_boosted_tau_match_index", index_match_2, 40, .5, 8, LumiWeight);
    


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
    float TMass;
    TLorentzVector rad4Momentum;
    rad4Momentum = leadtau4mom + LeadMatch4Momentum + NewBoostedTau4Momentum + SecondPair4Momentum;
    HT = rad4Momentum.Pt();
    plotFill("HT", HT, 50, 0, 1600, LumiWeight);

    //MET
    plotFill("MET", pfMET, 50, 0, 1000, LumiWeight);

    //MHT
    plotFill("MHT", pfMHT, 50, 0, 1000, LumiWeight);

    //

    // muons
    TLorentzVector Muon4Momentum, MatchedTau4Momentum;
    float muMass = 0.10565837;
    float muon_pt;
    float matched_tau_pt;
    for (int i = 0; i < nMu; ++i){
        Muon4Momentum.SetPtEtaPhiM(muPt->at(i), muEta->at(i), muPhi->at(i), muMass);
        if (Muon4Momentum.Pt() < 20) continue;
        tau_dR result = MatchTauToMuon(Muon4Momentum);
        int min_dR_index_muon = result.min_dR_index;
        float min_dR = result.min_dR;
        plotFill("min_dR_index_tau_muon", min_dR_index_muon, 50, 0 , 9, LumiWeight);
        plotFill("min_dR_muon", min_dR, 50, 0, 2, LumiWeight);

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
    float eleMass = 0.000511;
    float ele_pt;
    float match_tau_pt;
    for (int i = 0; i < nEle; ++i){
        Electron4Momentum.SetPtEtaPhiM(elePt->at(i), eleEta->at(i), elePhi->at(i), eleMass);
        if (Electron4Momentum.Pt() < 20) continue;
        tau_ele_dR result = MatchTauToElectron(Electron4Momentum);
        int min_dR_index2 = result.min_dR_index2;
        float min_dR2 = result.min_dR2;
        plotFill("min_dR_index_tau_ele", min_dR_index2, 50, 0 , 9, LumiWeight);
        plotFill("min_dR_electron", min_dR2, 50, 0, 2, LumiWeight);

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

    //std::cout << "PassTrigger_40: " << PassTrigger_40 << endl;
    plotFill("PassTrigger_40", PassTrigger_40, 100,0,1.25);
    plotFill("PassTrigger_39", PassTrigger_39, 100, 0, 1.25);


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

    //std::cout<<pfMET<<endl;
    //std::cout<<MHT<<endl;
    //std::cout<<TrimMass<<endl;
    //std::cout<<AK8Jet<<endl;
    //std::cout<<PFHT<<endl;
    PFMET_PFMHT = pfMET + MHT;
    


    //find total number of events
    // FIX THIS LATER
    float total_events_aftercuts1TeV = 3706;
    float total_events_aftercuts2TeV = 7363;
    float total_events_aftercuts3TeV = 7325;


    //Trigger 39
    float efficiency39;
    float events_passed39 = 0;
    float total_efficiency_39;
    for (int i=0; i < nBoostedTau; ++i){
        efficiency39 = calculate_efficiency_39(PFHT, PFMET_PFMHT);
        //std::cout<<efficiency_1<<endl;
        if (efficiency39 == 1.0){
            events_passed39 = events_passed39 + 1;
        }
    }
    total_efficiency_39 = events_passed39 / total_events_aftercuts1TeV;
    //std::cout<<total_efficiency_39<<endl;

    /*
    //Trigger 40
    float efficiency40;
    float events_passed40 = 0;
    float total_efficiency_40;
    for (int i=0; i < nBoostedTau; ++i){
        efficiency40 = calculate_efficiency_40(TrimMass, AK8Jet);
        if (efficiency40 == 1.0){
            events_passed40 = events_passed40 + 1;
        }
    }
    total_efficiency_40 = events_passed40 / total_events_aftercuts1TeV;
    */
    

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