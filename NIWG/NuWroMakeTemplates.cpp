// Include necessary ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TChain.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

const int NFiles   = 2;
const int NSpecies = 4;
const int NModes  = 7;

const std::string GeneratorName[NFiles] = {"NEUT", "NuWro"};

const std::string NuetrinoName[NSpecies] = {"numu", "nue", "numu_bar", "nue_bar"};
const int NuetrinoPDG[NSpecies] = {14, 12, -14, -12};

const std::unordered_map<int, int> ModeMap = {
  {11, 0},
  {12, 1},
  {13, 2},
  {31, 3},
  {32, 4},
  {33, 5},
  {34, 6}
};

const std::unordered_map<int, int> ReversedModeMap = {
  {0, 11},
  {1, 12},
  {2, 13},
  {3, 31},
  {4, 32},
  {5, 33},
  {6, 34}
};

// Define the filenames for the two ROOT files
std::vector<std::string> neutFileName = {"NEUT_T2K_numu_NUISFLAT.root", "NEUT_T2K_nue_NUISFLAT.root", "NEUT_T2K_numubar_NUISFLAT.root", "NEUT_T2K_nuebar_NUISFLAT.root"};
std::vector<std::string> nuwroFileName = {"NUWRO_T2K_numu_NUISFLAT.root", "NUWRO_T2K_nue_NUISFLAT.root", "NUWRO_T2K_numubar_NUISFLAT.root", "NUWRO_T2K_nuebar_NUISFLAT.root"};

// Loop over the two files
std::vector<std::vector<std::string>> fileNames = {neutFileName, nuwroFileName};

void NuWroMakeTemplates() {
  TH2D* hTemplate[NFiles][NModes][NSpecies];  // Corrected 'Charge' to 'NCharge'

  for (int fileIndex = 0; fileIndex < NFiles; ++fileIndex) {
    TChain* Chain = new TChain("FlatTree_VARS", "FlatTree_VARS");
    for (int MCindex = 0; MCindex < fileNames[fileIndex].size(); ++MCindex) {
      Chain->Add(fileNames[fileIndex][MCindex].c_str());
    }

    for (int chargeIndex = 0; chargeIndex < NModes; ++chargeIndex) {
      for (int nuindex = 0; nuindex < NSpecies; ++nuindex) {
        // Initialize histograms for neutrino interactions
        hTemplate[fileIndex][chargeIndex][nuindex] = new TH2D(Form("h%s_%s_%s", NuetrinoName[nuindex].c_str(), std::to_string(ReversedModeMap.at(chargeIndex)).c_str(),
                                                              GeneratorName[fileIndex].c_str()),
                                                              "Enu vs Q2", 50, 0, 2, 50, 0, 2);
        // Set titles for axes
        hTemplate[fileIndex][chargeIndex][nuindex]->GetXaxis()->SetTitle("Enu [GeV]");
        hTemplate[fileIndex][chargeIndex][nuindex]->GetYaxis()->SetTitle("Q^2 [GeV^2]");

        hTemplate[fileIndex][chargeIndex][nuindex]->SetDirectory(nullptr);
      }
    }
    // Create branch variables
    int mode = 0;
    int PDG = 0;
    float Enu = 0;
    float Q2 = 0;
    double fScaleFactor;

    // Set branch addresses
    Chain->SetBranchStatus("*", false);
    Chain->SetBranchStatus("Mode", true);
    Chain->SetBranchAddress("Mode", &mode);

    Chain->SetBranchStatus("Q2", true);
    Chain->SetBranchAddress("Q2", &Q2);

    Chain->SetBranchStatus("PDGnu", true);
    Chain->SetBranchAddress("PDGnu", &PDG);
    Chain->SetBranchStatus("Enu_true", true);
    Chain->SetBranchAddress("Enu_true", &Enu);

    Chain->SetBranchStatus("fScaleFactor", true);
    Chain->SetBranchAddress("fScaleFactor", &fScaleFactor);

    // Fill histograms
    Long64_t nentries = Chain->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) {
      if (i % 100000 == 0) std::cout << i << std::endl;

      Chain->GetEntry(i);
      fScaleFactor * 1E38;

      for (int nuindex = 0; nuindex < NSpecies; ++nuindex) {
        if (PDG == NuetrinoPDG[nuindex]) {
          auto it = ModeMap.find(std::abs(mode));
          if (it != ModeMap.end()) {
            hTemplate[fileIndex][it->second][nuindex]->Fill(Enu, Q2, fScaleFactor);
          } else {
            //std::cerr << "Warning: Mode " << mode << " not found in ModeMap. Skipping entry.\n";
          }
        }
      }
    }
  }

  // Save histograms to a TFile
  TFile* outFile = new TFile("Templates.root", "RECREATE");
  for (int fileIndex = 0; fileIndex < NFiles; ++fileIndex) {
    for (int chargeIndex = 0; chargeIndex < NModes; ++chargeIndex) {
      for (int nuindex = 0; nuindex < NSpecies; ++nuindex) {
        hTemplate[fileIndex][chargeIndex][nuindex]->Write();
      }
    }
  }
  // Close the file
  outFile->Close();
  delete outFile;


  // Create a canvas for plotting
  TCanvas* c1 = new TCanvas("c1", "Ratio Plots", 800, 600);

  c1->SaveAs("RatioPlots.pdf[");

  // Loop over the file indices (neut and nuwro)
  for (int chargeIndex = 0; chargeIndex < NModes; ++chargeIndex) {
    // Project TH2D histograms to TH1D on the X-axis (Enu)
    auto* hNueProjNeut = hTemplate[0][chargeIndex][1]->ProjectionX(); // nue for neut
    auto* hNumuProjNeut = hTemplate[0][chargeIndex][0]->ProjectionX(); // numu for neut

    auto* hNueProjNuwro = hTemplate[1][chargeIndex][1]->ProjectionX(); // nue for nuwro
    auto* hNumuProjNuwro = hTemplate[1][chargeIndex][0]->ProjectionX(); // numu for nuwro

    // Create ratio histograms (optional, you can skip this if not needed)
    auto* hRatioNeut = (TH1D*)hNueProjNeut->Clone(Form("hRatioNeut_%d", chargeIndex));
    hRatioNeut->Divide(hNumuProjNeut);
    auto* hRatioNuwro = (TH1D*)hNueProjNuwro->Clone(Form("hRatioNuwro_%d", chargeIndex));
    hRatioNuwro->Divide(hNumuProjNuwro);

    // Set titles and labels for the ratio histograms
    hRatioNeut->SetTitle(Form("Ratio: nue/numu (Generator: %s, Mode: %d)", GeneratorName[0].c_str(), ReversedModeMap.at(chargeIndex)));
    hRatioNeut->GetYaxis()->SetTitle("Ratio nue/numu");
    hRatioNeut->GetXaxis()->SetTitle("Enu [GeV]");

    hRatioNuwro->SetTitle(Form("Ratio: nue/numu (Generator: %s, Mode: %d)", GeneratorName[1].c_str(), ReversedModeMap.at(chargeIndex)));
    hRatioNuwro->GetYaxis()->SetTitle("Ratio nue/numu");
    hRatioNuwro->GetXaxis()->SetTitle("Enu [GeV]");

    // Draw the histograms
    hRatioNeut->SetLineColor(kBlue);   // Color for neut
    hRatioNuwro->SetLineColor(kRed);   // Color for nuwro

    hRatioNeut->GetXaxis()->SetRangeUser(0.45, 2);
    hRatioNeut->SetMaximum(hRatioNeut->GetMaximum() * 1.2);

    hRatioNeut->Draw("HIST");
    hRatioNuwro->Draw("HIST SAME");

    // Create a legend
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9);  // Position of the legend
    legend->AddEntry(hRatioNeut, "NEUT", "l");
    legend->AddEntry(hRatioNuwro, "NuWro", "l");
    legend->Draw();

    // Save the canvas to the PDF file
    c1->SaveAs("RatioPlots.pdf");
  }

  // Close the output file and canvas
  c1->SaveAs("RatioPlots.pdf]");
  delete c1;
}
