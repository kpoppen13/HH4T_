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
: fout(new TFile((channel_prefix + year + "_" + var+"_" + ".root").c_str(), "recreate")),

// x-axis
//bins_NN{0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0}, // This is for 0jet
//bins_NN(bins), // This is for 0jet
bins_NN({10,0,3000}),
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
        std::cout<<" cat.c_str()= "<<cat.c_str()<<"\n";
    }
    
    // make all of the directories for templates
    for (auto it = hists_1d.begin(); it != hists_1d.end(); it++) {
        fout->cd();
        fout->mkdir((it->first).c_str());
        std::cout <<"\t test 1   first directory is "<<it->first <<"\n";
        fout->cd();
    }
}
void HistTool::initVectors2d(string name) {
    for (auto key : hists_1d) {
        fout->cd(key.first.c_str());
        if (name.find("Data") != string::npos) {
            name = "data_obs";
        }
        if (key.first == tree_name + "_lowPurity") {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        }
        if (key.first == tree_name + "_highPurity") {
            hists_1d.at(key.first.c_str()).push_back(new TH1F(name.c_str(), name.c_str(), bins_NN.at(0), bins_NN.at(1), bins_NN.at(2)));
        }
    }
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
    }
}