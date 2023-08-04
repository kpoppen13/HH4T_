// system includes
#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// ROOT includes
#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TTree.h"
#include "TF1.h"
using namespace std;

using std::cout;
using std::string;
using std::vector;
enum Categories { lowPurity,highPurity
};

// read all *.root files in the given directory and put them in the provided vector
void read_directory(const string &name, std::vector<string> *v) {
    DIR *dirp = opendir(name.c_str());
    struct dirent *dp;
    while ((dp = readdir(dirp)) != 0) {
        if (static_cast<string>(dp->d_name).find("root") != string::npos) {
            v->push_back(dp->d_name);
        }
    }
    closedir(dirp);
}

// class to hold the histograms until I'm ready to write them
class HistTool {
public:
    HistTool(string,string, string, string);
    //  ~HistTool() { delete ff_weight; }
    ~HistTool() {  }
    void writeHistos();
    void writeTemplates(string,string,string);
    void initVectors2d(string);
    void initSystematics(string);
    
    void fillQCD_Norm(int, string, double, double,float);
    void fillQCD_Shape(int, string, double, double,float);
    void fillQCD_Norm_emu(int, string, double, double,float);
    void fillQCD_Shape_emu(int, string, double, double,float);
    // 2D test
    void fillQCD_Norm(int, string, double,double, double,float);
    void fillQCD_Shape(int, string, double,double, double,float);
    void fillQCD_Norm_emu(int, string, double,double, double,float);
    void fillQCD_Shape_emu(int, string, double,double, double,float);
    
    void fillQCD_OS_CR(int, string, double, double);
    void fillQCD_SS_CR(int, string, double, double);
    std::vector<float>  Get_OS_SS_ratio();
    
    //  void convertDataToFake(Categories, string, double, double, double, double, double, double);  // 2d
    void histoLoop(string year  ,std::vector<string>, string, TH1F *, string, string,std::vector<float>,  string);
    
//    hists->histoLoop(year, files, dir,tree_name,var_name);    // fill histograms
    
    void histoLoop(string  ,std::vector<string>, string,string, string);
//    void histoLoop(string year  ,std::vector<string>, string, string);

//hists->histoLoop(year, files, dir,tree_name,var_name);

    
    //    void histoLoop(string year  ,std::vector<string>, string, TH1F *, string, string, string);
    void histoLoop(string channel, string year  ,std::vector<string>, string, string, string,std::vector<float>, string); //for emu
    void histoLoop(string, string   ,std::vector<string>, string, string, string,std::vector<float>,string, float, float, string); //for emu
    
    void histoQCD(std::vector<string>, string, string, string);
    
    bool doNN, old_selection;
    TFile *fout;
    //  FakeFactor *ff_weight;
    string channel_prefix, tree_name;
    std::vector<string> categories, systematics;
    //    std::vector<float> mvis_bins, njets_bins;
    std::map<string, std::vector<TH1F *>> hists_1d;
    std::map<string, std::vector<TH2F *>> hists_2d, Histo_2DMatrix_Higgs, Histo_2DMatrix_Jet;
    std::vector<TH1F *> fakes_1d_norm,  fakes_1d_norm_Up,  fakes_1d_norm_Down , data;
    std::vector<TH2F *> fakes_2d_norm,  fakes_2d_norm_Up,  fakes_2d_norm_Down;
    std::vector<TH1F *> fakes_1d_SS_CR, fakes_1d_SS_CR_Up, fakes_1d_SS_CR_Down;
    std::vector<TH1F *> fakes_1d_OS_CR, fakes_1d_OS_CR_Up, fakes_1d_OS_CR_Down, fakes_1d_OS_CR_data,fakes_1d_OS_CR_mc;
    std::vector<TH1F *> fakes_1d_shape, fakes_1d_shape_Up, fakes_1d_shape_Down, fakes_1d_SS_CR_data,fakes_1d_SS_CR_mc;
    std::vector<TH2F *> fakes_2d_shape, fakes_2d_shape_Up, fakes_2d_shape_Down;
    // binning
//    std::vector<int> bins_NN, bins_FAKE;
    std::vector<Float_t> bins_NN, bins_FAKE;
    std::vector<Float_t> bins_genHPt;
};

//auto hists = new HistTool(channel,var_name,  year, suffix);
//HistTool::HistTool(string treeName, string channel_prefix, string var, string year, string suffix)


// HistTool contructor to create the output file, the qcd histograms with the correct binning
// and the map from categories to vectors of TH1F*'s. Each TH1F* in the vector corresponds to
// one file that is being put into that categories directory in the output tempalte
HistTool::HistTool(string treeName, string channel_prefix, string var, string year)
: fout(new TFile(("Output/templates/" + channel_prefix + year + "_" + var+"_" + ".root").c_str(), "recreate")),

// x-axis
//bins_NN{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0}, // This is for 0jet
//bins_NN(bins), // This is for 0jet
bins_NN({10,0,0.5}),
bins_FAKE({10,0,300}),
//bins_genHPt({0,300,400,550,800,2000}),
bins_genHPt({0,350,450,600,2000}),
//bins_FAKE({10,0,1}),
channel_prefix(channel_prefix),
tree_name(treeName),
categories{
    tree_name + "_lowPurity",
    tree_name + "_highPurity",
    //    channel_prefix + "_boosted",
    //    channel_prefix + "_vbf",
},
systematics{
    ""
} {
    
    // Create empty histograms for each category to fill later.
    for (auto cat : categories) {
        // make a 2d template
        hists_1d[cat.c_str()] = std::vector<TH1F *>();
        hists_2d[cat.c_str()] = std::vector<TH2F *>();
        Histo_2DMatrix_Higgs[cat.c_str()] = std::vector<TH2F *>();
        Histo_2DMatrix_Jet[cat.c_str()] = std::vector<TH2F *>();
        
        if (cat.find("0jet") != string::npos) {
            
            fakes_1d_norm.push_back(new TH1F("fake_0jet", "fake_SS_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
//            fakes_2d_norm.push_back(new TH2F("fake_0jet2", "fake_SS_02", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_2d_norm.push_back(new TH2F("fake_0jet2", "fake_SS_02", 2, 0, 2, 12, 200, 800));
            fakes_1d_norm_Up.push_back(new TH1F("fake_0jet_Up", "fake_SS_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_norm_Down.push_back(new TH1F("fake_0jet_Down", "fake_SS_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            
            fakes_1d_shape.push_back(new TH1F("fake_0jet_shape", "fake_SS_shape_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
//            fakes_2d_shape.push_back(new TH2F("fake_0jet_shape2", "fake_SS_shape_02",  bins_NN.at(0), bins_NN.at(1), bins_NN.at(2), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_2d_shape.push_back(new TH2F("fake_0jet_shape2", "fake_SS_shape_02",  2, 0, 2, 12, 200, 800));
            fakes_1d_shape_Up.push_back(new TH1F("fake_0jet_shape_Up", "fake_SS_shape_0_Up_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            fakes_1d_shape_Down.push_back(new TH1F("fake_0jet_shape_Down", "fake_SS_shape_0_Down_0", bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            
            fakes_1d_OS_CR.push_back(new TH1F("OS_CR_0jet", "OS_CR_0jet", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_data.push_back(new TH1F("OS_CR_0jet_data", "OS_CR_0jet_data", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_mc.push_back(new TH1F("OS_CR_0jet_mc", "OS_CR_0jet_mc", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_Up.push_back(new TH1F("OS_CR_0jet_Up", "OS_CR_0jet_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_OS_CR_Down.push_back(new TH1F("OS_CR_0jet_Down", "OS_CR_0jet_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            
            fakes_1d_SS_CR.push_back(new TH1F("SS_CR_0jet", "SS_CR_0jet", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_data.push_back(new TH1F("SS_CR_0jet_data", "SS_CR_0jet_data", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_mc.push_back(new TH1F("SS_CR_0jet_mc", "SS_CR_0jet_mc", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_Up.push_back(new TH1F("SS_CR_0jet_Up", "SS_CR_0jet_Up", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            fakes_1d_SS_CR_Down.push_back(new TH1F("SS_CR_0jet_Down", "SS_CR_0jet_Down", bins_FAKE.at(0), bins_FAKE.at(1), bins_FAKE.at(2)));
            
            
        }
        std::cout<<" cat.c_str()= "<<cat.c_str()<<"\n";
        }
    
    // make all of the directories for templates
    for (auto it = hists_1d.begin(); it != hists_1d.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 1   first directory is "<<it->first <<"\n";
        fout->cd();
    }
    // make all of 2D the directories for templates
    for (auto it = hists_2d.begin(); it != hists_2d.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 2   first directory is "<<it->first <<"\n";
        fout->cd();
    }
    // make all of the directories for templates
    for (auto it = Histo_2DMatrix_Higgs.begin(); it != Histo_2DMatrix_Higgs.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 1   first directory is "<<it->first <<"\n";
        fout->cd();
    }
    for (auto it = Histo_2DMatrix_Jet.begin(); it != Histo_2DMatrix_Jet.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 1   first directory is "<<it->first <<"\n";
        fout->cd();
    }
}

// change to the correct output directory then create a new TH1F that will be filled for the current input file
void HistTool::initVectors2d(string name) {
    for (auto key : hists_1d) {
        fout->cd(key.first.c_str());
        if (name.find("Data") != string::npos) {
            name = "data_obs";
        }
        if (key.first == tree_name + "_0jet") {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        }
    }
    for (auto key : hists_2d) {
        fout->cd(key.first.c_str());
        if (name.find("Data") != string::npos) {
            name = "data_obs";
        }
        if (key.first == tree_name + "_0jet") {
//            hists_2d.at(key.first.c_str()).push_back(new TH2F((name+"_2D__").c_str(), (name+"_2D__").c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
            hists_2d.at(key.first.c_str()).push_back(new TH2F((name+"_2D__").c_str(), (name+"_2D__").c_str(), 2, 0, 2, 12, 200, 800));

        }
    }
    for (auto key : Histo_2DMatrix_Higgs) {
        fout->cd(key.first.c_str());
        if (key.first == tree_name + "_0jet") {
            Histo_2DMatrix_Higgs.at(key.first.c_str()).push_back(new TH2F((name+"_2D_Higgs").c_str(), (name+"_2D_Higgs").c_str(), bins_genHPt.size() - 1, &bins_genHPt[0], bins_genHPt.size() - 1, &bins_genHPt[0]));
        }
    }
    for (auto key : Histo_2DMatrix_Jet) {
        fout->cd(key.first.c_str());
        if (key.first == tree_name + "_0jet") {
            Histo_2DMatrix_Jet.at(key.first.c_str()).push_back(new TH2F((name+"_2D_Jet").c_str(), (name+"_2D_Jet").c_str(), bins_genHPt.size() - 1, &bins_genHPt[0], bins_genHPt.size() - 1, &bins_genHPt[0]));
        }
    }
}



// This is CR to extract OS/SS ratio
void HistTool::fillQCD_OS_CR(int cat, string name, double var1,  double weight) {
    if (name == "Data") {
        fakes_1d_OS_CR.at(cat)->Fill(var1, 1);
        fakes_1d_OS_CR_Up.at(cat)->Fill(var1, 1);
        fakes_1d_OS_CR_Down.at(cat)->Fill(var1, 1);
        fakes_1d_OS_CR_data.at(cat)->Fill(var1, 1);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_1d_OS_CR.at(cat)->Fill(var1, -1*weight);
        fakes_1d_OS_CR_Up.at(cat)->Fill(var1, -1*weight*0.9);
        fakes_1d_OS_CR_Down.at(cat)->Fill(var1, -1*weight*1.1);
        fakes_1d_OS_CR_mc.at(cat)->Fill(var1, weight);
    }
}
// This is CR to extract OS/SS ratio
void HistTool::fillQCD_SS_CR(int cat, string name, double var1,  double weight) {
    if (name == "Data") {
        fakes_1d_SS_CR.at(cat)->Fill(var1, 1);
        fakes_1d_SS_CR_Up.at(cat)->Fill(var1, 1);
        fakes_1d_SS_CR_Down.at(cat)->Fill(var1, 1);
        fakes_1d_SS_CR_data.at(cat)->Fill(var1, 1);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" ||  name == "EWKZ" ) {
        fakes_1d_SS_CR.at(cat)->Fill(var1, -1*weight);
        fakes_1d_SS_CR_Up.at(cat)->Fill(var1, -1*weight*0.9);
        fakes_1d_SS_CR_Down.at(cat)->Fill(var1, -1*weight*1.1);
        fakes_1d_SS_CR_mc.at(cat)->Fill(var1, weight);
    }
}

// This is SS region [need to apply the OS/SS ratio here]
void HistTool::fillQCD_Norm(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_norm.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Down.at(cat)->Fill(var1, 1*OSSS_val);
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_1d_norm.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_norm_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_norm_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}
void HistTool::fillQCD_Norm(int cat, string name, double var1,double var2,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_2d_norm.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_norm_Up.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_norm_Down.at(cat)->Fill(var1,var2, 1*OSSS_val);
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_2d_norm.at(cat)->Fill(var1,var2, -1*OSSS_val*weight);
//        fakes_2d_norm_Up.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*0.9);
//        fakes_2d_norm_Down.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*1.1);
    }
}

void HistTool::fillQCD_Norm_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_norm.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_norm_Down.at(cat)->Fill(var1, 1*OSSS_val);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        //    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_1d_norm.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_norm_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_norm_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}
void HistTool::fillQCD_Norm_emu(int cat, string name, double var1,double var2,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_2d_norm.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_norm_Up.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_norm_Down.at(cat)->Fill(var1,var2, 1*OSSS_val);
    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        //    } else if ( name == "ZTT" || name == "VV" || name == "TT"  || name == "EWKZ" ) {
        fakes_2d_norm.at(cat)->Fill(var1,var2, -1*OSSS_val*weight);
//        fakes_2d_norm_Up.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*0.9);
//        fakes_2d_norm_Down.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*1.1);
    }
}


// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_shape.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Down.at(cat)->Fill(var1, 1*OSSS_val);
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val*weight);
        fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
        fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}
void HistTool::fillQCD_Shape(int cat, string name, double var1,double var2,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_2d_shape.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_shape_Up.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_shape_Down.at(cat)->Fill(var1,var2, 1*OSSS_val);
//    } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
        fakes_2d_shape.at(cat)->Fill(var1,var2, -1*OSSS_val*weight);
//        fakes_2d_shape_Up.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*0.9);
//        fakes_2d_shape_Down.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*1.1);
    }
}


// This is Loose SS region [To get the shape of QCD from SS and loose region]
void HistTool::fillQCD_Shape_emu(int cat, string name, double var1,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_1d_shape.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Up.at(cat)->Fill(var1, 1*OSSS_val);
        fakes_1d_shape_Down.at(cat)->Fill(var1, 1*OSSS_val);
//            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
            } else if (name == "W" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        //    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        
                fakes_1d_shape.at(cat)->Fill(var1, -1*OSSS_val*weight);
                fakes_1d_shape_Up.at(cat)->Fill(var1, -1*OSSS_val*weight*0.9);
                fakes_1d_shape_Down.at(cat)->Fill(var1, -1*OSSS_val*weight*1.1);
    }
}
void HistTool::fillQCD_Shape_emu(int cat, string name, double var1,double var2,  double weight, float OSSS_val) {
    TH1F *hist;
    if (name == "Data") {
        fakes_2d_shape.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_shape_Up.at(cat)->Fill(var1,var2, 1*OSSS_val);
//        fakes_2d_shape_Down.at(cat)->Fill(var1,var2, 1*OSSS_val);
//            } else if (name == "W" || name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
            } else if (name == "W" || name == "VV" || name == "TT" || name == "EWKZ" ) {
        //    } else if ( name == "ZTT" || name == "VV" || name == "TT" || name == "EWKZ" ) {
                fakes_2d_shape.at(cat)->Fill(var1,var2, -1*OSSS_val*weight);
//                fakes_2d_shape_Up.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*0.9);
//                fakes_2d_shape_Down.at(cat)->Fill(var1,var2, -1*OSSS_val*weight*1.1);
    }
}

// Derive OS/SS ratio
std::vector<float>  HistTool::Get_OS_SS_ratio(){
    
    std::vector<float>  os_ss_values;
    os_ss_values.clear();
    
    float OS_SS_0jet = fakes_1d_OS_CR.at(0)->Integral() /  fakes_1d_SS_CR.at(0)->Integral();
    cout<<"OS num = "<<fakes_1d_OS_CR.at(0)->Integral() << "  SS denum = "<<fakes_1d_SS_CR.at(0)->Integral() << "\n";
    cout<<"OS num (data) = "<<fakes_1d_OS_CR_data.at(0)->Integral() << "  SS denum (data)= "<<fakes_1d_SS_CR_data.at(0)->Integral() << "\n";
    cout<<" num purity = "<<fakes_1d_OS_CR.at(0)->Integral()/fakes_1d_OS_CR_data.at(0)->Integral() << "  denum purity= "<<fakes_1d_SS_CR.at(0)->Integral()/fakes_1d_SS_CR_data.at(0)->Integral() << "\n";
    os_ss_values.push_back(OS_SS_0jet);
    return os_ss_values;
}

// write output histograms including the QCD histograms after scaling by OS/SS ratio
void HistTool::writeTemplates(string dir, string channel, string year) {
    auto order(0);
    auto order2(0);
    for (auto cat : hists_1d) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        float CorrFactor=1;
        // Updated fake rate
//        if (channel.find("tt") != string::npos && year.find("2016") != string::npos ) CorrFactor =1.14;
//        if (channel.find("tt") != string::npos && year.find("2017") != string::npos ) CorrFactor =0.92;
//        if (channel.find("tt") != string::npos && year.find("2018") != string::npos ) CorrFactor =0.87;

        // fake rate
//        if (channel.find("tt") != string::npos && year.find("2016") != string::npos ) CorrFactor =0.70;
//        if (channel.find("tt") != string::npos && year.find("2017") != string::npos ) CorrFactor =0.95;
//        if (channel.find("tt") != string::npos && year.find("2018") != string::npos ) CorrFactor =0.80;

    // os to ss
//        if (channel.find("tt") != string::npos && year.find("2016") != string::npos ) CorrFactor =1.30;
//        if (channel.find("tt") != string::npos && year.find("2017") != string::npos ) CorrFactor =0.98;
//        if (channel.find("tt") != string::npos && year.find("2018") != string::npos ) CorrFactor =0.90;

        auto fake_hist_norm = fakes_1d_norm.at(order);
        auto fake_hist2_norm = fakes_2d_norm.at(order2);
        auto fake_hist_norm_Up = fakes_1d_norm_Up.at(order);
        auto fake_hist_norm_Down = fakes_1d_norm_Down.at(order);
        
        fake_hist_norm->Scale(CorrFactor);
        fake_hist2_norm->Scale(CorrFactor);
        fake_hist_norm_Up->Scale(CorrFactor);
        fake_hist_norm_Down->Scale(CorrFactor);
        
        auto fake_hist_shape = fakes_1d_shape.at(order);
        auto fake_hist2_shape = fakes_2d_shape.at(order2);
        auto fake_hist_shape_Up = fakes_1d_shape_Up.at(order);
        auto fake_hist_shape_Down = fakes_1d_shape_Down.at(order);
        
        //========================================================================================================
        //                // ADD protection
        for (int i = 0 ; i < fake_hist_shape->GetNbinsX(); i++){
            if (fake_hist_shape->GetBinContent(i+1) <0 ){
                float negBin=fake_hist_shape->GetBinContent(i+1);
                float totIntegral =fake_hist_shape->Integral();
                fake_hist_shape->SetBinContent(i+1, 0.0001);
                fake_hist_shape->SetBinError(i+1, 0.1);
                std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
            }
            if (fake_hist_shape_Up->GetBinContent(i+1) <0 ){
                fake_hist_shape_Up->SetBinContent(i+1, 0.0001);
                fake_hist_shape_Up->SetBinError(i+1, 0.1);
            }
            if (fake_hist_shape_Down->GetBinContent(i+1) <0 ){
                fake_hist_shape_Down->SetBinContent(i+1, 0.0001);
                fake_hist_shape_Down->SetBinError(i+1, 0.1);
            }
        }
        //                // ADD protection
        for (int i = 0 ; i < fake_hist2_shape->GetNbinsX(); i++){
            for (int j = 0 ; j < fake_hist2_shape->GetNbinsY(); j++){
                if (fake_hist2_shape->GetBinContent(i+1,j+1) <0 ){
                    float negBin=fake_hist2_shape->GetBinContent(i+1,j+1);
                    float totIntegral =fake_hist2_shape->Integral();
                    fake_hist2_shape->SetBinContent(i+1, j+1,0.0001);
                    
                    fake_hist2_shape->SetBinError(i+1,j+1, 0.1);
                    std::cout<< cat.first.c_str() << "   QCD bin of "<<i <<"  "<< j<<"  ratio bin/TotIntegral"<< negBin/totIntegral <<"\n";
                }
            }
        }

        //========================================================================================================
        
        std::cout<<"\n\n Norm QCD is = "<<fake_hist_norm->Integral() <<   "  shape integral is "<< fake_hist_shape->Integral()  <<"\n";
        fake_hist_shape->Scale(fake_hist_norm->Integral()/fake_hist_shape->Integral());
        fake_hist_shape_Up->Scale(fake_hist_norm_Up->Integral()/fake_hist_shape_Up->Integral());
        fake_hist_shape_Down->Scale(fake_hist_norm_Down->Integral()/fake_hist_shape_Down->Integral());
        fake_hist2_shape->Scale(fake_hist2_norm->Integral()/fake_hist2_shape->Integral());
        
        // Only make QCD for nominal process and not sys Up/Down
        if (dir.find("Up")==string::npos && dir.find("Down")==string::npos){
            fake_hist_shape->SetName("QCD");
            fake_hist_shape_Up->SetName("QCD_shape_Up");
            fake_hist_shape_Down->SetName("QCD_shape_Down");
            fake_hist_shape->Write();
            fake_hist_shape_Up->Write();
            fake_hist_shape_Down->Write();

            fake_hist2_shape->SetName("QCD_2D__");
//            fake_hist_shape_Up->SetName("QCD_shape_Up");
//            fake_hist_shape_Down->SetName("QCD_shape_Down");
            fake_hist2_shape->Write();
//            fake_hist_shape_Up->Write();
//            fake_hist_shape_Down->Write();


            // shape for qcd OS/SS
            fakes_1d_OS_CR.at(0)->Write();
            fakes_1d_SS_CR.at(0)->Write();
            fakes_1d_OS_CR_data.at(0)->Write();
            fakes_1d_SS_CR_data.at(0)->Write();
            fakes_1d_OS_CR_mc.at(0)->Write();
            fakes_1d_SS_CR_mc.at(0)->Write();
        }
        
        order++;
        order2++;
    for (auto cat : Histo_2DMatrix_Higgs) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        }
    for (auto cat : Histo_2DMatrix_Jet) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
        }
    for (auto cat : hists_2d) {
        fout->cd(cat.first.c_str());
        for (auto hist : cat.second) {
            hist->Write();
        }
    }
    }
}