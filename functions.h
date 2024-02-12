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
#include "../interface/boostHTT_4t.h"



// function to chek if tau is good 
// true = good tau, false = bad tau
bool isTauGood(int tau_index) {
    bool good_or_bad = true; // Initialize to true by default
    if (boostedTauByIsolationMVArun2v1DBoldDMwLTrawNew->at(tau_index) < 0.5 || 
        boostedTaupfTausDiscriminationByDecayModeFinding->at(tau_index) < 0.5 || 
        (boostedTauPt->at(tau_index) <= 20 || fabs(boostedTauEta->at(tau_index)) >= 2.3)) {
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
            //don't apply charge here
            //if ((boostedTauCharge->at(ibtau) * charge) > 0) continue;
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
            //don't apply charge here
            //if ((boostedTauCharge->at(ibtau) * charge) > 0) continue;
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
float calculate_efficiency_39(float PFHT, float PFMET_MHT){
    float efficiency_39;
    float passing;
    if (PFHT > 500 && PFMET_MHT > 200){
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