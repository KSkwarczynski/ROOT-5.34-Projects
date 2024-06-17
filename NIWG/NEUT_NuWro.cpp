// Include necessary ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TChain.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>


// Function to calculate the momentum
float calculateMomentum(float px, float py, float pz) {
  return 1000*std::sqrt(px*px + py*py + pz*pz);
}

float GetLeptonMomentum(int nfsp, float* px, float* py, float* pz, int* pdg) {
  for (int i = 0; i < nfsp; ++i) {
    if (std::abs(pdg[i]) == 13 || abs(pdg[i]) == 11) {
      float momentum = calculateMomentum(px[i], py[i], pz[i]);
      return momentum;
    }
  }
  return -999;
}


void ScaleHistogram(TH1D* Hist)
{
  Hist->Scale(1.0 / Hist->GetEntries());
}

void NiceHistogram(TH1D* Hist, int style, int colour)
{
  Hist->SetLineStyle(style);
  Hist->SetLineWidth(2);
  Hist->SetLineColor(colour);
}

void NIWGStudy() {
  // Define the filenames for the two ROOT files
  std::vector<std::string> neutFileName = {"NEUT570_T2K_numu_NUISFLAT.root", "NEUT570_T2K_nue_NUISFLAT.root", "NEUT570_T2K_numubar_NUISFLAT.root", "NEUT570_T2K_nuebar_NUISFLAT.root"};
  std::vector<std::string> nuwroFileName = {"NUWRO_T2K_LE_FHC_numu_NUISFLAT.root", "NUWRO_T2K_LE_FHC_nue_NUISFLAT.root", "NUWRO_T2K_LE_FHC_numubar_NUISFLAT.root", "NUWRO_T2K_LE_FHC_nuebar_NUISFLAT.root"};

  // Loop over the two files
  std::vector<std::vector<std::string>> fileNames = {neutFileName, nuwroFileName};
  const char* legendEntries[] = {"NEUT", "NUWRO"};
  std::vector<int> Style = {kSolid, kDashed}; // Colors for NEUT and NUWRO histograms

  bool PlotShape = true;
  const int NBins = 20;
  // Create histograms
  // Create histograms
  TH1D* hNuMuPi[2];
  TH1D* hNuEPi[2];
  TH1D* hNuMuPi_W[2];
  TH1D* hNuEPi_W[2];
  TH1D* hNuMuPi_Plep[2];
  TH1D* hNuEPi_Plep[2];

  TH1D* hNuMuPipm[2];
  TH1D* hNuMuPi0[2];
  TH1D* hNuEPipm[2];
  TH1D* hNuEPi0[2];
  TH1D* hNuMuPipm_W[2];
  TH1D* hNuMuPi0_W[2];
  TH1D* hNuEPipm_W[2];
  TH1D* hNuEPi0_W[2];

  TH1D* hNuMuPipm_Plep[2];
  TH1D* hNuMuPi0_Plep[2];
  TH1D* hNuEPipm_Plep[2];
  TH1D* hNuEPi0_Plep[2];

  // Create histograms for anti-neutrino interactions
  TH1D* hNuMuBarPi[2];
  TH1D* hNuEBarPi[2];
  TH1D* hNuMuBarPi_W[2];
  TH1D* hNuEBarPi_W[2];
  TH1D* hNuMuBarPi_Plep[2];
  TH1D* hNuEBarPi_Plep[2];

  TH1D* hNuMuBarPipm[2];
  TH1D* hNuMuBarPi0[2];
  TH1D* hNuEBarPipm[2];
  TH1D* hNuEBarPi0[2];
  TH1D* hNuMuBarPipm_W[2];
  TH1D* hNuMuBarPi0_W[2];
  TH1D* hNuEBarPipm_W[2];
  TH1D* hNuEBarPi0_W[2];

  TH1D* hNuMuBarPipm_Plep[2];
  TH1D* hNuMuBarPi0_Plep[2];
  TH1D* hNuEBarPipm_Plep[2];
  TH1D* hNuEBarPi0_Plep[2];

  for (int fileIndex = 0; fileIndex < 2; ++fileIndex) {
    TChain* Chain = new TChain("FlatTree_VARS", "FlatTree_VARS");
    for (int MCindex = 0; MCindex < fileNames[fileIndex].size(); ++MCindex) {
      Chain->Add(fileNames[fileIndex][MCindex].c_str());
    }
    // Initialize histograms for neutrino interactions
    hNuMuPi[fileIndex] = new TH1D(Form("hNuMuPi_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEPi[fileIndex] = new TH1D(Form("hNuEPi_%s", legendEntries[fileIndex]), "hNuEPi", NBins, 0, 2500);
    hNuMuPi_W[fileIndex] = new TH1D(Form("hNuMuPi_W_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEPi_W[fileIndex] = new TH1D(Form("hNuEPi_W_%s", legendEntries[fileIndex]), "hNuMuPi0_W", NBins, 0, 2500);
    hNuMuPi_Plep[fileIndex] = new TH1D(Form("hNuMuPi_Plep_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEPi_Plep[fileIndex] = new TH1D(Form("hNuEPi_Plep_%s", legendEntries[fileIndex]), "hNuMuPi0_Plep", NBins, 0, 2500);
    hNuMuPipm[fileIndex] = new TH1D(Form("hNuMuPipm_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuPi0[fileIndex] = new TH1D(Form("hNuMuPi0_%s", legendEntries[fileIndex]), "hNuMuPi0", NBins, 0, 2500);
    hNuEPipm[fileIndex] = new TH1D(Form("hNuEPipm_%s", legendEntries[fileIndex]), "hNuEPipm", NBins, 0, 2500);
    hNuEPi0[fileIndex] = new TH1D(Form("hNuEPi0_%s", legendEntries[fileIndex]), "hNuEPi0", NBins, 0, 2500);
    hNuMuPipm_W[fileIndex] = new TH1D(Form("hNuMuPipm_W_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuPi0_W[fileIndex] = new TH1D(Form("hNuMuPi0_W_%s", legendEntries[fileIndex]), "hNuMuPi0_W", NBins, 0, 2500);
    hNuEPipm_W[fileIndex] = new TH1D(Form("hNuEPipm_W_%s", legendEntries[fileIndex]), "hNuEPipm_W", NBins, 0, 2500);
    hNuEPi0_W[fileIndex] = new TH1D(Form("hNuEPi0_W_%s", legendEntries[fileIndex]), "hNuEPi0_W", NBins, 0, 2500);
    hNuMuPipm_Plep[fileIndex] = new TH1D(Form("hNuMuPipm_Plep_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuPi0_Plep[fileIndex] = new TH1D(Form("hNuMuPi0_Plep_%s", legendEntries[fileIndex]), "hNuMuPi0_Plep", NBins, 0, 2500);
    hNuEPipm_Plep[fileIndex] = new TH1D(Form("hNuEPipm_Plep_%s", legendEntries[fileIndex]), "hNuEPipm_Plep", NBins, 0, 2500);
    hNuEPi0_Plep[fileIndex] = new TH1D(Form("hNuEPi0_Plep_%s", legendEntries[fileIndex]), "hNuEPi0_Plep", NBins, 0, 2500);

    // Initialize histograms for anti-neutrino interactions
    hNuMuBarPi[fileIndex] = new TH1D(Form("hNuMuBarPi_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEBarPi[fileIndex] = new TH1D(Form("hNuEBarPi_%s", legendEntries[fileIndex]), "hNuEBarPi", NBins, 0, 2500);
    hNuMuBarPi_W[fileIndex] = new TH1D(Form("hNuMuBarPi_W_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEBarPi_W[fileIndex] = new TH1D(Form("hNuEBarPi_W_%s", legendEntries[fileIndex]), "hNuMuBarPi0_W", NBins, 0, 2500);
    hNuMuBarPi_Plep[fileIndex] = new TH1D(Form("hNuMuBarPi_Plep_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuEBarPi_Plep[fileIndex] = new TH1D(Form("hNuEBarPi_Plep_%s", legendEntries[fileIndex]), "hNuMuBarPi0_Plep", NBins, 0, 2500);
    hNuMuBarPipm[fileIndex] = new TH1D(Form("hNuMuBarPipm_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuBarPi0[fileIndex] = new TH1D(Form("hNuMuBarPi0_%s", legendEntries[fileIndex]), "hNuMuBarPi0", NBins, 0, 2500);
    hNuEBarPipm[fileIndex] = new TH1D(Form("hNuEBarPipm_%s", legendEntries[fileIndex]), "hNuEBarPipm", NBins, 0, 2500);
    hNuEBarPi0[fileIndex] = new TH1D(Form("hNuEBarPi0_%s", legendEntries[fileIndex]), "hNuEBarPi0", NBins, 0, 2500);
    hNuMuBarPipm_W[fileIndex] = new TH1D(Form("hNuMuBarPipm_W_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuBarPi0_W[fileIndex] = new TH1D(Form("hNuMuBarPi0_W_%s", legendEntries[fileIndex]), "hNuMuBarPi0_W", NBins, 0, 2500);
    hNuEBarPipm_W[fileIndex] = new TH1D(Form("hNuEBarPipm_W_%s", legendEntries[fileIndex]), "hNuEBarPipm_W", NBins, 0, 2500);
    hNuEBarPi0_W[fileIndex] = new TH1D(Form("hNuEBarPi0_W_%s", legendEntries[fileIndex]), "hNuEBarPi0_W", NBins, 0, 2500);
    hNuMuBarPipm_Plep[fileIndex] = new TH1D(Form("hNuMuBarPipm_Plep_%s", legendEntries[fileIndex]), "", NBins, 0, 2500);
    hNuMuBarPi0_Plep[fileIndex] = new TH1D(Form("hNuMuBarPi0_Plep_%s", legendEntries[fileIndex]), "hNuMuBarPi0_Plep", NBins, 0, 2500);
    hNuEBarPipm_Plep[fileIndex] = new TH1D(Form("hNuEBarPipm_Plep_%s", legendEntries[fileIndex]), "hNuEBarPipm_Plep", NBins, 0, 2500);
    hNuEBarPi0_Plep[fileIndex] = new TH1D(Form("hNuEBarPi0_Plep_%s", legendEntries[fileIndex]), "hNuEBarPi0_Plep", NBins, 0, 2500);

    // Set titles for axes
    hNuMuPi[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuPi[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPi_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuPi_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPi_Plep[fileIndex]->GetXaxis()->SetTitle("P_{lep} [MeV]");
    hNuMuPi_Plep[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPipm[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuPipm[fileIndex]->GetYaxis()->SetTitle("A.U.");
    hNuMuPipm_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuPipm_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPipm_Plep[fileIndex]->GetXaxis()->SetTitle("P_{lep} [MeV]");
    hNuMuPipm_Plep[fileIndex]->GetYaxis()->SetTitle("A.U.");


    // Set titles for axes
    hNuMuBarPi[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuBarPi[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuBarPi_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuBarPi_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuBarPi_Plep[fileIndex]->GetXaxis()->SetTitle("P_{lep} [MeV]");
    hNuMuBarPi_Plep[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuBarPipm[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuBarPipm[fileIndex]->GetYaxis()->SetTitle("A.U.");
    hNuMuBarPipm_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuBarPipm_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuBarPipm_Plep[fileIndex]->GetXaxis()->SetTitle("P_{lep} [MeV]");
    hNuMuBarPipm_Plep[fileIndex]->GetYaxis()->SetTitle("A.U.");

    // Create branches variables
    int mode = 0;
    int PDG = 0;
    float W = 0;
    float Enu = 0;
    float fScaleFactor;

    static const int kMAX = 200;
    int nfsp;
    float px[kMAX];
    float py[kMAX];
    float pz[kMAX];
    int pdg[kMAX];


    // Set branch addresses
    Chain->SetBranchStatus("*", false);
    Chain->SetBranchStatus("Mode", true);
    Chain->SetBranchAddress("Mode", &mode);
    Chain->SetBranchStatus("W", true);
    Chain->SetBranchAddress("W", &W);
    Chain->SetBranchStatus("PDGnu", true);
    Chain->SetBranchAddress("PDGnu", &PDG);
    //Chain->SetBranchStatus("fScaleFactor", true);
    //Chain->SetBranchAddress("fScaleFactor", &fScaleFactor);
    Chain->SetBranchStatus("Enu_true", true);
    Chain->SetBranchAddress("Enu_true", &Enu);

    Chain->SetBranchStatus("nfsp", true);
    Chain->SetBranchAddress("nfsp", &nfsp);
    Chain->SetBranchStatus("pdg", true);
    Chain->SetBranchAddress("pdg", &pdg);

    Chain->SetBranchStatus("nfsp", true);
    Chain->SetBranchAddress("nfsp", &nfsp);
    Chain->SetBranchStatus("px", true);
    Chain->SetBranchAddress("px", px);
    Chain->SetBranchStatus("py", true);
    Chain->SetBranchAddress("py", py);
    Chain->SetBranchStatus("pz", true);
    Chain->SetBranchAddress("pz", pz);

    // Fill histograms
    Long64_t nentries = Chain->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) {
      if (i % 100000 == 0) std::cout << i << std::endl;

      Chain->GetEntry(i);
      //if(Enu * 1000 > 1000) continue;

      if(PlotShape) fScaleFactor = 1;

      float LepMom = GetLeptonMomentum(nfsp, px, py, pz, pdg);
      if (PDG == 14) {
        if (mode == 11 || mode == 12 || mode == 13) {
          hNuMuPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuPi_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }

        if (mode == 11 || mode == 13) {
          hNuMuPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuPipm_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
        if (mode == 12) {
          hNuMuPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuPi0_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
      }
      if (PDG == 12) {
        if (mode == 11 || mode == 12 || mode == 13) {
          hNuEPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEPi_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }

        if (mode == 11 || mode == 13) {
          hNuEPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEPipm_Plep[fileIndex]->Fill(LepMom, fScaleFactor);

        }
        if (mode == 12) {
          hNuEPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEPi0_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
      }
      //AnitNu
      if (PDG == -14) {
        if (mode == -11 || mode == -12 || mode == -13) {
          hNuMuBarPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuBarPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuBarPi_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }

        if (mode == -11 || mode == -13) {
          hNuMuBarPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuBarPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuBarPipm_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
        if (mode == -12) {
          hNuMuBarPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuBarPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuMuBarPi0_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
      }
      if (PDG == -12) {
        if (mode == -11 || mode == -12 || mode == -13) {
          hNuEBarPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEBarPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEBarPi_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }

        if (mode == -11 || mode == -13) {
          hNuEBarPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEBarPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEBarPipm_Plep[fileIndex]->Fill(LepMom, fScaleFactor);

        }
        if (mode == -12) {
          hNuEBarPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEBarPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
          hNuEBarPi0_Plep[fileIndex]->Fill(LepMom, fScaleFactor);
        }
      }

    }

    if(PlotShape)
    {
      // Normalize histograms for neutrino interactions
      hNuMuPi[fileIndex]->Scale(1.0 / hNuMuPi[fileIndex]->GetEntries());
      hNuEPi[fileIndex]->Scale(1.0 / hNuEPi[fileIndex]->GetEntries());
      hNuMuPi_W[fileIndex]->Scale(1.0 / hNuMuPi_W[fileIndex]->GetEntries());
      hNuEPi_W[fileIndex]->Scale(1.0 / hNuEPi_W[fileIndex]->GetEntries());
      ScaleHistogram(hNuMuPi_Plep[fileIndex]);
      ScaleHistogram(hNuEPi_Plep[fileIndex]);

      hNuMuPipm[fileIndex]->Scale(1.0 / hNuMuPipm[fileIndex]->GetEntries());
      hNuMuPi0[fileIndex]->Scale(1.0 / hNuMuPi0[fileIndex]->GetEntries());
      hNuEPipm[fileIndex]->Scale(1.0 / hNuEPipm[fileIndex]->GetEntries());
      hNuEPi0[fileIndex]->Scale(1.0 / hNuEPi0[fileIndex]->GetEntries());

      hNuMuPipm_W[fileIndex]->Scale(1.0 / hNuMuPipm_W[fileIndex]->GetEntries());
      hNuMuPi0_W[fileIndex]->Scale(1.0 / hNuMuPi0_W[fileIndex]->GetEntries());
      hNuEPipm_W[fileIndex]->Scale(1.0 / hNuEPipm_W[fileIndex]->GetEntries());
      hNuEPi0_W[fileIndex]->Scale(1.0 / hNuEPi0_W[fileIndex]->GetEntries());

      ScaleHistogram(hNuMuPipm_Plep[fileIndex]);
      ScaleHistogram(hNuMuPi0_Plep[fileIndex]);
      ScaleHistogram(hNuEPipm_Plep[fileIndex]);
      ScaleHistogram(hNuEPi0_Plep[fileIndex]);

      // Normalize histograms for anti-neutrino interactions
      hNuMuBarPi[fileIndex]->Scale(1.0 / hNuMuBarPi[fileIndex]->GetEntries());
      hNuEBarPi[fileIndex]->Scale(1.0 / hNuEBarPi[fileIndex]->GetEntries());
      hNuMuBarPi_W[fileIndex]->Scale(1.0 / hNuMuBarPi_W[fileIndex]->GetEntries());
      hNuEBarPi_W[fileIndex]->Scale(1.0 / hNuEBarPi_W[fileIndex]->GetEntries());
      ScaleHistogram(hNuMuBarPi_Plep[fileIndex]);
      ScaleHistogram(hNuEBarPi_Plep[fileIndex]);

      hNuMuBarPipm[fileIndex]->Scale(1.0 / hNuMuBarPipm[fileIndex]->GetEntries());
      hNuMuBarPi0[fileIndex]->Scale(1.0 / hNuMuBarPi0[fileIndex]->GetEntries());
      hNuEBarPipm[fileIndex]->Scale(1.0 / hNuEBarPipm[fileIndex]->GetEntries());
      hNuEBarPi0[fileIndex]->Scale(1.0 / hNuEBarPi0[fileIndex]->GetEntries());

      hNuMuBarPipm_W[fileIndex]->Scale(1.0 / hNuMuBarPipm_W[fileIndex]->GetEntries());
      hNuMuBarPi0_W[fileIndex]->Scale(1.0 / hNuMuBarPi0_W[fileIndex]->GetEntries());
      hNuEBarPipm_W[fileIndex]->Scale(1.0 / hNuEBarPipm_W[fileIndex]->GetEntries());
      hNuEBarPi0_W[fileIndex]->Scale(1.0 / hNuEBarPi0_W[fileIndex]->GetEntries());

      ScaleHistogram(hNuMuBarPipm_Plep[fileIndex]);
      ScaleHistogram(hNuMuBarPi0_Plep[fileIndex]);
      ScaleHistogram(hNuEBarPipm_Plep[fileIndex]);
      ScaleHistogram(hNuEBarPi0_Plep[fileIndex]);
    }

    // Customize and style histograms for neutrino interactions
    NiceHistogram(hNuMuPi[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEPi[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuMuPi_W[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEPi_W[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuMuPi_Plep[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEPi_Plep[fileIndex], Style[fileIndex], kRed);

    NiceHistogram(hNuMuPipm[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuPi0[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEPipm[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEPi0[fileIndex], Style[fileIndex], kMagenta);

    NiceHistogram(hNuMuPipm_W[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuPi0_W[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEPipm_W[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEPi0_W[fileIndex], Style[fileIndex], kMagenta);

    NiceHistogram(hNuMuPipm_Plep[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuPi0_Plep[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEPipm_Plep[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEPi0_Plep[fileIndex], Style[fileIndex], kMagenta);

    // Customize and style histograms for anti-neutrino interactions
    NiceHistogram(hNuMuBarPi[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEBarPi[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuMuBarPi_W[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEBarPi_W[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuMuBarPi_Plep[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuEBarPi_Plep[fileIndex], Style[fileIndex], kRed);

    NiceHistogram(hNuMuBarPipm[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuBarPi0[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEBarPipm[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEBarPi0[fileIndex], Style[fileIndex], kMagenta);

    NiceHistogram(hNuMuBarPipm_W[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuBarPi0_W[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEBarPipm_W[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEBarPi0_W[fileIndex], Style[fileIndex], kMagenta);

    NiceHistogram(hNuMuBarPipm_Plep[fileIndex], Style[fileIndex], kBlue);
    NiceHistogram(hNuMuBarPi0_Plep[fileIndex], Style[fileIndex], kRed);
    NiceHistogram(hNuEBarPipm_Plep[fileIndex], Style[fileIndex], kGreen);
    NiceHistogram(hNuEBarPi0_Plep[fileIndex], Style[fileIndex], kMagenta);
    delete Chain;
  }

  // Draw histograms and legends for Enu
  TCanvas *c1 = new TCanvas("c1_Enu", "Enu", 800, 600);
  gStyle->SetOptStat(0);
  c1->SetGrid();
  c1->SetTopMargin(0.10);
  c1->SetBottomMargin(0.08);
  c1->SetRightMargin(0.12);
  c1->SetLeftMargin(0.12);
  c1->Print("NIWG_Plot.pdf[");

  if(hNuEPi[0]->GetMaximum() > hNuMuPi[1]->GetMaximum()) hNuMuPi[0]->SetMaximum(hNuEPi[0]->GetMaximum());

  hNuMuPi[0]->Draw("hist");
  hNuEPi[0]->Draw("hist SAME");
  hNuMuPi[1]->Draw("hist SAME");
  hNuEPi[1]->Draw("hist SAME");

  TLegend *Legend_Tot = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot->SetFillColor(0);
  Legend_Tot->SetFillStyle(0);
  Legend_Tot->SetLineWidth(0);
  Legend_Tot->SetLineColor(0);
  Legend_Tot->AddEntry(hNuMuPi[0], "NEUT #nu_{#mu} CCSPP", "l");
  Legend_Tot->AddEntry(hNuEPi[0], "NEUT #nu_{e} CCSPP", "l");
  Legend_Tot->AddEntry(hNuMuPi[1], "NUWRO #nu_{#mu} CCSPP", "l");
  Legend_Tot->AddEntry(hNuEPi[1], "NUWRO #nu_{e} CCSPP", "l");
  Legend_Tot->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  delete Legend_Tot;
  TH1D* hNuMuPi_Ratio[2];
  hNuMuPi_Ratio[0] = (TH1D*)hNuMuPi[0]->Clone();
  hNuMuPi_Ratio[0]->GetYaxis()->SetTitle("#nu_{#mu} / #nu_{e}");
  hNuMuPi_Ratio[0]->Divide(hNuEPi[0]);
  hNuMuPi_Ratio[1] = (TH1D*)hNuMuPi[1]->Clone();
  hNuMuPi_Ratio[1]->Divide(hNuEPi[1]);

  double maxz = -999;
  double minz = +999;

  for (int i = 1; i < hNuMuPi_Ratio[0]->GetXaxis()->GetNbins(); i++)
  {
    maxz = std::max(maxz, hNuMuPi_Ratio[0]->GetBinContent(i));
    minz = std::min(minz, hNuMuPi_Ratio[0]->GetBinContent(i));
  }
  maxz = maxz*1.005;
  minz = minz*1.005;

  if (std::fabs(1 - maxz) > std::fabs(1-minz))
    hNuMuPi_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-maxz),1+std::fabs(1-maxz));
  else
    hNuMuPi_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-minz),1+std::fabs(1-minz));

  hNuMuPi_Ratio[0]->SetLineColor(kBlue);
  hNuMuPi_Ratio[1]->SetLineColor(kRed);

  hNuMuPi_Ratio[0]->Draw("hist");
  hNuMuPi_Ratio[1]->Draw("hist SAME");

  Legend_Tot = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot->SetFillColor(0);
  Legend_Tot->SetFillStyle(0);
  Legend_Tot->SetLineWidth(0);
  Legend_Tot->SetLineColor(0);
  Legend_Tot->AddEntry(hNuMuPi_Ratio[0], "NEUT CCSPP", "l");
  Legend_Tot->AddEntry(hNuMuPi_Ratio[1], "NuWro CCSPP", "l");
  Legend_Tot->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  hNuMuPi_W[0]->Draw("hist");
  hNuEPi_W[0]->Draw("hist SAME");
  hNuMuPi_W[1]->Draw("hist SAME");
  hNuEPi_W[1]->Draw("hist SAME");

  TLegend *Legend_Tot_W = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_W->SetFillColor(0);
  Legend_Tot_W->SetFillStyle(0);
  Legend_Tot_W->SetLineWidth(0);
  Legend_Tot_W->SetLineColor(0);
  Legend_Tot_W->AddEntry(hNuMuPi_W[0], "NEUT #nu_{#mu} CCSPP", "l");
  Legend_Tot_W->AddEntry(hNuEPi_W[0], "NEUT #nu_{e} CCSPP", "l");
  Legend_Tot_W->AddEntry(hNuMuPi_W[1], "NUWRO #nu_{#mu} CCSPP", "l");
  Legend_Tot_W->AddEntry(hNuEPi_W[1], "NUWRO #nu_{e} CCSPP", "l");
  Legend_Tot_W->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");
  delete Legend_Tot_W;

  TH1D* hNuMuPi_W_Ratio[2];
  hNuMuPi_W_Ratio[0] = (TH1D*)hNuMuPi_W[0]->Clone();
  hNuMuPi_W_Ratio[1] = (TH1D*)hNuMuPi_W[1]->Clone();
  hNuMuPi_W_Ratio[0]->GetYaxis()->SetTitle("#nu_{#mu} / #nu_{e}");
  hNuMuPi_W_Ratio[0]->Divide(hNuEPi[0]);
  hNuMuPi_W_Ratio[1]->Divide(hNuEPi[1]);

  hNuMuPi_W_Ratio[0]->SetLineColor(kBlue);
  hNuMuPi_W_Ratio[1]->SetLineColor(kRed);

  hNuMuPi_W_Ratio[0]->Draw("hist");
  hNuMuPi_W_Ratio[1]->Draw("hist SAME");

  Legend_Tot_W = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_W->SetFillColor(0);
  Legend_Tot_W->SetFillStyle(0);
  Legend_Tot_W->SetLineWidth(0);
  Legend_Tot_W->SetLineColor(0);
  Legend_Tot_W->AddEntry(hNuMuPi_W_Ratio[0], "NEUT CCSPP", "l");
  Legend_Tot_W->AddEntry(hNuMuPi_W_Ratio[1], "NuWro CCSPP", "l");
  Legend_Tot_W->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  if(hNuEPi_Plep[1]->GetMaximum() > hNuMuPi_Plep[0]->GetMaximum()) hNuMuPi_Plep[0]->SetMaximum(hNuEPi_Plep[1]->GetMaximum());
  hNuMuPi_Plep[0]->Draw("hist");
  hNuEPi_Plep[0]->Draw("hist SAME");
  hNuMuPi_Plep[1]->Draw("hist SAME");
  hNuEPi_Plep[1]->Draw("hist SAME");

  TLegend *Legend_Tot_Lep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_Lep->SetFillColor(0);
  Legend_Tot_Lep->SetFillStyle(0);
  Legend_Tot_Lep->SetLineWidth(0);
  Legend_Tot_Lep->SetLineColor(0);
  Legend_Tot_Lep->AddEntry(hNuMuPi_Plep[0], "NEUT #nu_{#mu} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuEPi_Plep[0], "NEUT #nu_{e} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuMuPi_Plep[1], "NUWRO #nu_{#mu} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuEPi_Plep[1], "NUWRO #nu_{e} CCSPP", "l");
  Legend_Tot_Lep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");
  delete Legend_Tot_Lep;

  TH1D* hNuMuPi_Plep_Ratio[2];
  hNuMuPi_Plep_Ratio[0] = (TH1D*)hNuMuPi_Plep[0]->Clone();
  hNuMuPi_Plep_Ratio[1] = (TH1D*)hNuMuPi_Plep[1]->Clone();
  hNuMuPi_Plep_Ratio[0]->GetYaxis()->SetTitle("#nu_{#mu} / #nu_{e}");
  hNuMuPi_Plep_Ratio[0]->Divide(hNuEPi_Plep[0]);
  hNuMuPi_Plep_Ratio[1]->Divide(hNuEPi_Plep[1]);

  hNuMuPi_Plep_Ratio[0]->SetLineColor(kBlue);
  hNuMuPi_Plep_Ratio[1]->SetLineColor(kRed);

  maxz = -999;
  minz = +999;
  for (int i = 1; i < hNuMuPi_Plep_Ratio[0]->GetXaxis()->GetNbins(); i++)
  {
    maxz = std::max(maxz, hNuMuPi_Plep_Ratio[0]->GetBinContent(i));
    minz = std::min(minz, hNuMuPi_Plep_Ratio[0]->GetBinContent(i));
  }
  maxz = maxz*1.2;
  minz = minz*1.2;

  if (std::fabs(1 - maxz) > std::fabs(1-minz))
    hNuMuPi_Plep_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-maxz),1+std::fabs(1-maxz));
  else
    hNuMuPi_Plep_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-minz),1+std::fabs(1-minz));

  hNuMuPi_Plep_Ratio[0]->Draw("hist");
  hNuMuPi_Plep_Ratio[1]->Draw("hist SAME");

  Legend_Tot_Lep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_Lep->SetFillColor(0);
  Legend_Tot_Lep->SetFillStyle(0);
  Legend_Tot_Lep->SetLineWidth(0);
  Legend_Tot_Lep->SetLineColor(0);
  Legend_Tot_Lep->AddEntry(hNuMuPi_Plep_Ratio[0], "NEUT CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuMuPi_Plep_Ratio[1], "NuWro CCSPP", "l");
  Legend_Tot_Lep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  hNuMuPipm[0]->Draw("hist");
  hNuMuPi0[0]->Draw("hist SAME");
  hNuEPipm[0]->Draw("hist SAME");
  hNuEPi0[0]->Draw("hist SAME");
  hNuMuPipm[1]->Draw("hist SAME");
  hNuMuPi0[1]->Draw("hist SAME");
  hNuEPipm[1]->Draw("hist SAME");
  hNuEPi0[1]->Draw("hist SAME");

  TLegend *Legend_Enu = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Enu->SetFillColor(0);
  Legend_Enu->SetFillStyle(0);
  Legend_Enu->SetLineWidth(0);
  Legend_Enu->SetLineColor(0);
  Legend_Enu->AddEntry(hNuMuPipm[0], "NEUT #nu_{#mu} #pi^{+-}", "l");
  Legend_Enu->AddEntry(hNuMuPi0[0], "NEUT #nu_{#mu} #pi^{0}", "l");
  Legend_Enu->AddEntry(hNuEPipm[0], "NEUT #nu_{e} #pi^{+-}", "l");
  Legend_Enu->AddEntry(hNuEPi0[0], "NEUT #nu_{e} #pi^{0}", "l");
  Legend_Enu->AddEntry(hNuMuPipm[1], "NUWRO #nu_{#mu} #pi^{+-}", "l");
  Legend_Enu->AddEntry(hNuMuPi0[1], "NUWRO #nu_{#mu} #pi^{0}", "l");
  Legend_Enu->AddEntry(hNuEPipm[1], "NUWRO #nu_{e} #pi^{+-}", "l");
  Legend_Enu->AddEntry(hNuEPi0[1], "NUWRO #nu_{e} #pi^{0}", "l");
  Legend_Enu->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  TH1D* hNuMuPipm_Ratio[2];
  hNuMuPipm_Ratio[0] = (TH1D*)hNuMuPipm[0]->Clone();
  hNuMuPipm_Ratio[1] = (TH1D*)hNuMuPipm[1]->Clone();
  TH1D* hNuMuPi0_Ratio[2];
  hNuMuPi0_Ratio[0] = (TH1D*)hNuMuPi0[0]->Clone();
  hNuMuPi0_Ratio[1] = (TH1D*)hNuMuPi0[1]->Clone();

  hNuMuPipm_Ratio[0]->GetYaxis()->SetTitle("#nu_{#mu} / #nu_{e}");
  hNuMuPipm_Ratio[0]->Divide(hNuEPipm[0]);
  hNuMuPipm_Ratio[1]->Divide(hNuEPipm[1]);
  hNuMuPi0_Ratio[0]->Divide(hNuEPipm[0]);
  hNuMuPi0_Ratio[1]->Divide(hNuEPipm[1]);

  maxz = -999;
  minz = +999;
  for (int i = 1; i < hNuMuPipm_Ratio[0]->GetXaxis()->GetNbins(); i++)
  {
    maxz = std::max(maxz, hNuMuPipm_Ratio[0]->GetBinContent(i));
    minz = std::min(minz, hNuMuPipm_Ratio[0]->GetBinContent(i));
  }
  maxz = maxz*1.005;
  minz = minz*1.005;

  if (std::fabs(1 - maxz) > std::fabs(1-minz))
    hNuMuPipm_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-maxz),1+std::fabs(1-maxz));
  else
    hNuMuPipm_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-minz),1+std::fabs(1-minz));

  hNuMuPipm_Ratio[0]->SetLineColor(kBlue);
  hNuMuPipm_Ratio[1]->SetLineColor(kRed);
  hNuMuPi0_Ratio[0]->SetLineColor(kGreen);
  hNuMuPi0_Ratio[1]->SetLineColor(kMagenta);

  hNuMuPipm_Ratio[0]->Draw("hist");
  hNuMuPipm_Ratio[1]->Draw("hist SAME");
  hNuMuPi0_Ratio[0]->Draw("hist SAME");
  hNuMuPi0_Ratio[1]->Draw("hist SAME");

  Legend_Tot = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot->SetFillColor(0);
  Legend_Tot->SetFillStyle(0);
  Legend_Tot->SetLineWidth(0);
  Legend_Tot->SetLineColor(0);
  Legend_Tot->AddEntry(hNuMuPipm_Ratio[0], "NEUT #pi^{+-}", "l");
  Legend_Tot->AddEntry(hNuMuPi0_Ratio[0], "NEUT #pi^{0}", "l");
  Legend_Tot->AddEntry(hNuMuPipm_Ratio[1], "NuWro #pi^{+-}", "l");
  Legend_Tot->AddEntry(hNuMuPi0_Ratio[1], "NuWro #pi^{0}", "l");
  Legend_Tot->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");


  hNuMuPipm_W[0]->Draw("hist");
  hNuMuPi0_W[0]->Draw("hist SAME");
  hNuEPipm_W[0]->Draw("hist SAME");
  hNuEPi0_W[0]->Draw("hist SAME");
  hNuMuPipm_W[1]->Draw("hist SAME");
  hNuMuPi0_W[1]->Draw("hist SAME");
  hNuEPipm_W[1]->Draw("hist SAME");
  hNuEPi0_W[1]->Draw("hist SAME");

  TLegend *Legend_W = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_W->SetFillColor(0);
  Legend_W->SetFillStyle(0);
  Legend_W->SetLineWidth(0);
  Legend_W->SetLineColor(0);
  Legend_W->AddEntry(hNuMuPipm_W[0], "NEUT #nu_{#mu} #pi^{+-}", "l");
  Legend_W->AddEntry(hNuMuPi0_W[0], "NEUT #nu_{#mu} #pi^{0}", "l");
  Legend_W->AddEntry(hNuEPipm_W[0], "NEUT #nu_{e} #pi^{+-}", "l");
  Legend_W->AddEntry(hNuEPi0_W[0], "NEUT #nu_{e} #pi^{0}", "l");
  Legend_W->AddEntry(hNuMuPipm_W[1], "NUWRO #nu_{#mu} #pi^{+-}", "l");
  Legend_W->AddEntry(hNuMuPi0_W[1], "NUWRO #nu_{#mu} #pi^{0}", "l");
  Legend_W->AddEntry(hNuEPipm_W[1], "NUWRO #nu_{e} #pi^{+-}", "l");
  Legend_W->AddEntry(hNuEPi0_W[1], "NUWRO #nu_{e} #pi^{0}", "l");
  Legend_W->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  if(hNuEPipm_Plep[1]->GetMaximum() > hNuMuPipm_Plep[0]->GetMaximum()) hNuMuPipm_Plep[0]->SetMaximum(hNuEPipm_Plep[1]->GetMaximum());

  hNuMuPipm_Plep[0]->Draw("hist");
  hNuMuPi0_Plep[0]->Draw("hist SAME");
  hNuEPipm_Plep[0]->Draw("hist SAME");
  hNuEPi0_Plep[0]->Draw("hist SAME");
  hNuMuPipm_Plep[1]->Draw("hist SAME");
  hNuMuPi0_Plep[1]->Draw("hist SAME");
  hNuEPipm_Plep[1]->Draw("hist SAME");
  hNuEPi0_Plep[1]->Draw("hist SAME");

  TLegend *Legend_Plep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Plep->SetFillColor(0);
  Legend_Plep->SetFillStyle(0);
  Legend_Plep->SetLineWidth(0);
  Legend_Plep->SetLineColor(0);
  Legend_Plep->AddEntry(hNuMuPipm_Plep[0], "NEUT #nu_{#mu} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuMuPi0_Plep[0], "NEUT #nu_{#mu} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuEPipm_Plep[0], "NEUT #nu_{e} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuEPi0_Plep[0], "NEUT #nu_{e} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuMuPipm_Plep[1], "NUWRO #nu_{#mu} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuMuPi0_Plep[1], "NUWRO #nu_{#mu} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuEPipm_Plep[1], "NUWRO #nu_{e} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuEPi0_Plep[1], "NUWRO #nu_{e} #pi^{0}", "l");
  Legend_Plep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");
/////////Antineutrinos//////////

  if(hNuEBarPi_Plep[0]->GetMaximum() > hNuEBarPi_Plep[0]->GetMaximum()) hNuMuBarPi_Plep[0]->SetMaximum(hNuEBarPi_Plep[0]->GetMaximum());
  hNuMuBarPi_Plep[0]->Draw("hist");
  hNuEBarPi_Plep[0]->Draw("hist SAME");
  hNuMuBarPi_Plep[1]->Draw("hist SAME");
  hNuEBarPi_Plep[1]->Draw("hist SAME");

  Legend_Tot_Lep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_Lep->SetFillColor(0);
  Legend_Tot_Lep->SetFillStyle(0);
  Legend_Tot_Lep->SetLineWidth(0);
  Legend_Tot_Lep->SetLineColor(0);
  Legend_Tot_Lep->AddEntry(hNuMuBarPi_Plep[0], "NEUT #bar{#nu}_{#mu} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuEBarPi_Plep[0], "NEUT #bar{#nu}_{e} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuMuBarPi_Plep[1], "NUWRO #bar{#nu}_{#mu} CCSPP", "l");
  Legend_Tot_Lep->AddEntry(hNuEBarPi_Plep[1], "NUWRO #bar{#nu}_{e} CCSPP", "l");
  Legend_Tot_Lep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");


  TH1D* hNuMuBarPi_Plep_Ratio[2];
  hNuMuBarPi_Plep_Ratio[0] = (TH1D*)hNuMuBarPi_Plep[0]->Clone();
  hNuMuBarPi_Plep_Ratio[1] = (TH1D*)hNuMuBarPi_Plep[1]->Clone();
  hNuMuBarPi_Plep_Ratio[0]->GetYaxis()->SetTitle("#bar{#nu}_{#mu} / #bar{#nu}_{e}");
  hNuMuBarPi_Plep_Ratio[0]->Divide(hNuEBarPi_Plep[0]);
  hNuMuBarPi_Plep_Ratio[1]->Divide(hNuEBarPi_Plep[1]);

  hNuMuBarPi_Plep_Ratio[0]->SetLineColor(kBlue);
  hNuMuBarPi_Plep_Ratio[1]->SetLineColor(kRed);

  maxz = -999;
  minz = +999;
  for (int i = 1; i < hNuMuBarPi_Plep_Ratio[0]->GetXaxis()->GetNbins(); i++)
  {
    maxz = std::max(maxz, hNuMuBarPi_Plep_Ratio[0]->GetBinContent(i));
    minz = std::min(minz, hNuMuBarPi_Plep_Ratio[0]->GetBinContent(i));
  }
  maxz = maxz*1.2;
  minz = minz*1.2;

  if (std::fabs(1 - maxz) > std::fabs(1-minz))
    hNuMuBarPi_Plep_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-maxz),1+std::fabs(1-maxz));
  else
    hNuMuBarPi_Plep_Ratio[0]->GetYaxis()->SetRangeUser(1-std::fabs(1-minz),1+std::fabs(1-minz));

  hNuMuBarPi_Plep_Ratio[0]->Draw("hist");
  hNuMuBarPi_Plep_Ratio[1]->Draw("hist same");

  Legend_Tot_Lep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot_Lep->SetFillColor(0);
  Legend_Tot_Lep->SetFillStyle(0);
  Legend_Tot_Lep->SetLineWidth(0);
  Legend_Tot_Lep->SetLineColor(0);
  Legend_Tot_Lep->AddEntry(hNuMuBarPi_Plep_Ratio[0], "NEUT CCSPP #bar{#nu}", "l");
  Legend_Tot_Lep->AddEntry(hNuMuBarPi_Plep_Ratio[1], "NuWro CCSPP #bar{#nu}", "l");
  Legend_Tot_Lep->Draw("SAME");
  c1->Print("NIWG_Plot.pdf");

  if(hNuEPipm_Plep[1]->GetMaximum() > hNuMuPipm_Plep[0]->GetMaximum()) hNuMuPipm_Plep[0]->SetMaximum(hNuEPipm_Plep[1]->GetMaximum());

  hNuMuBarPipm_Plep[0]->Draw("hist");
  hNuMuBarPi0_Plep[0]->Draw("hist SAME");
  hNuEBarPipm_Plep[0]->Draw("hist SAME");
  hNuEBarPi0_Plep[0]->Draw("hist SAME");
  hNuMuBarPipm_Plep[1]->Draw("hist SAME");
  hNuMuBarPi0_Plep[1]->Draw("hist SAME");
  hNuEBarPipm_Plep[1]->Draw("hist SAME");
  hNuEBarPi0_Plep[1]->Draw("hist SAME");

  Legend_Plep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Plep->SetFillColor(0);
  Legend_Plep->SetFillStyle(0);
  Legend_Plep->SetLineWidth(0);
  Legend_Plep->SetLineColor(0);
  Legend_Plep->AddEntry(hNuMuBarPipm_Plep[0], "NEUT #bar{#nu}_{#mu} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuMuBarPi0_Plep[0], "NEUT #bar{#nu}_{#mu} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuEBarPipm_Plep[0], "NEUT #bar{#nu}_{e} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuEBarPi0_Plep[0], "NEUT #bar{#nu}_{e} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuMuBarPipm_Plep[1], "NUWRO #bar{#nu}_{#mu} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuMuBarPi0_Plep[1], "NUWRO #bar{#nu}_{#mu} #pi^{0}", "l");
  Legend_Plep->AddEntry(hNuEBarPipm_Plep[1], "NUWRO #bar{#nu}_{e} #pi^{+-}", "l");
  Legend_Plep->AddEntry(hNuEBarPi0_Plep[1], "NUWRO #bar{#nu}_{e} #pi^{0}", "l");
  Legend_Plep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  hNuMuPi_Plep_Ratio[0]->SetLineColor(kBlue);
  hNuMuPi_Plep_Ratio[1]->SetLineColor(kRed);
  hNuMuBarPi_Plep_Ratio[0]->SetLineColor(kGreen);
  hNuMuBarPi_Plep_Ratio[1]->SetLineColor(kMagenta);

  hNuMuPi_Plep_Ratio[0]->Draw("hist");
  hNuMuPi_Plep_Ratio[1]->Draw("hist same");

  hNuMuBarPi_Plep_Ratio[0]->Draw("hist same");
  hNuMuBarPi_Plep_Ratio[1]->Draw("hist same");

  Legend_Plep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Plep->SetFillColor(0);
  Legend_Plep->SetFillStyle(0);
  Legend_Plep->SetLineWidth(0);
  Legend_Plep->SetLineColor(0);
  Legend_Plep->AddEntry(hNuMuPi_Plep_Ratio[0], "NEUT #nu CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuPi_Plep_Ratio[1], "NUWRO #nu CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuBarPi_Plep_Ratio[0], "NEUT #bar{#nu} CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuBarPi_Plep_Ratio[1], "NUWRO #bar{#nu} CCSPP", "l");
  Legend_Plep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  TH1D* hNuMuPi_Plep_Ratio_Model[2];
  TH1D* hNuMuBarPi_Plep_Ratio_Model[2];

  hNuMuPi_Plep_Ratio_Model[0] = (TH1D*)hNuMuPi_Plep[0]->Clone();
  hNuMuPi_Plep_Ratio_Model[1] = (TH1D*)hNuEPi_Plep[0]->Clone();
  hNuMuBarPi_Plep_Ratio_Model[0] = (TH1D*)hNuMuBarPi_Plep[0]->Clone();
  hNuMuBarPi_Plep_Ratio_Model[1] = (TH1D*)hNuEBarPi_Plep[0]->Clone();
  hNuMuPi_Plep_Ratio_Model[0]->GetYaxis()->SetTitle("NEUT / NuWro");

  hNuMuPi_Plep_Ratio_Model[0]->Divide(hNuMuPi_Plep[1]);
  hNuMuPi_Plep_Ratio_Model[1]->Divide(hNuEPi_Plep[1]);

  hNuMuBarPi_Plep_Ratio_Model[0]->Divide(hNuMuBarPi_Plep[1]);
  hNuMuBarPi_Plep_Ratio_Model[1]->Divide(hNuEBarPi_Plep[1]);

  hNuMuPi_Plep_Ratio_Model[0]->SetLineColor(kBlue);
  hNuMuPi_Plep_Ratio_Model[1]->SetLineColor(kRed);
  hNuMuBarPi_Plep_Ratio_Model[0]->SetLineColor(kGreen);
  hNuMuBarPi_Plep_Ratio_Model[1]->SetLineColor(kMagenta);

  hNuMuPi_Plep_Ratio_Model[0]->GetYaxis()->SetRangeUser(0.7, 1.3);

  hNuMuPi_Plep_Ratio_Model[0]->Draw("hist");
  hNuMuPi_Plep_Ratio_Model[1]->Draw("hist same");
  hNuMuBarPi_Plep_Ratio_Model[0]->Draw("hist same");
  hNuMuBarPi_Plep_Ratio_Model[1]->Draw("hist same");

  Legend_Plep = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Plep->SetFillColor(0);
  Legend_Plep->SetFillStyle(0);
  Legend_Plep->SetLineWidth(0);
  Legend_Plep->SetLineColor(0);
  Legend_Plep->AddEntry(hNuMuPi_Plep_Ratio_Model[0], "#nu_{#mu} CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuPi_Plep_Ratio_Model[1], "#nu_{e} CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuBarPi_Plep_Ratio_Model[0], "#bar{#nu}_{#mu} CCSPP", "l");
  Legend_Plep->AddEntry(hNuMuBarPi_Plep_Ratio_Model[1], "#bar{#nu}_{e} CCSPP", "l");
  Legend_Plep->Draw("SAME");

  c1->Print("NIWG_Plot.pdf");

  c1->Print("NIWG_Plot.pdf]");

  // Cleanup
  delete c1;
  delete Legend_Enu;
  delete Legend_W;
  delete Legend_Plep;
  for (int fileIndex = 0; fileIndex < 2; ++fileIndex) {
    delete hNuMuPipm[fileIndex];
    delete hNuMuPi0[fileIndex];
    delete hNuEPipm[fileIndex];
    delete hNuEPi0[fileIndex];
    delete hNuMuPipm_W[fileIndex];
    delete hNuMuPi0_W[fileIndex];
    delete hNuEPipm_W[fileIndex];
    delete hNuEPi0_W[fileIndex];
  }
}
