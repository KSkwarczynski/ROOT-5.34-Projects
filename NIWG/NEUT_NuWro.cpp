// Include necessary ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TChain.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

void NIWGStudy() {
  // Define the filenames for the two ROOT files
  std::vector<std::string> neutFileName = {"NEUT570_T2K_numu_NUISFLAT.root", "NEUT570_T2K_nue_NUISFLAT.root"};
  std::vector<std::string> nuwroFileName = {"NUWRO_T2K_LE_FHC_numu_NUISFLAT.root", "NUWRO_T2K_LE_FHC_nue_NUISFLAT.root"};

  // Loop over the two files
  std::vector<std::vector<std::string>> fileNames = {neutFileName, nuwroFileName};
  const char* legendEntries[] = {"NEUT", "NUWRO"};
  std::vector<int> Style = {kSolid, kDashed}; // Colors for NEUT and NUWRO histograms

  bool PlotShape = true;
  // Create histograms
  TH1D* hNuMuPi[2];
  TH1D* hNuEPi[2];
  TH1D* hNuMuPi_W[2];
  TH1D* hNuEPi_W[2];
  TH1D* hNuMuPipm[2];
  TH1D* hNuMuPi0[2];
  TH1D* hNuEPipm[2];
  TH1D* hNuEPi0[2];
  TH1D* hNuMuPipm_W[2];
  TH1D* hNuMuPi0_W[2];
  TH1D* hNuEPipm_W[2];
  TH1D* hNuEPi0_W[2];

  for (int fileIndex = 0; fileIndex < 2; ++fileIndex) {
    TChain* Chain = new TChain("FlatTree_VARS", "FlatTree_VARS");
    for (int MCindex = 0; MCindex < fileNames[fileIndex].size(); ++MCindex) {
      Chain->Add(fileNames[fileIndex][MCindex].c_str());
    }
    hNuMuPi[fileIndex] = new TH1D(Form("hNuMuPi_%s", legendEntries[fileIndex]), "", 20, 0, 2500);
    hNuEPi[fileIndex] = new TH1D(Form("hNuEPi_%s", legendEntries[fileIndex]), "hNuEPi", 20, 0, 2500);

    hNuMuPi_W[fileIndex] = new TH1D(Form("hNuMuPi_W_%s", legendEntries[fileIndex]), "", 20, 0, 2500);
    hNuEPi_W[fileIndex] = new TH1D(Form("hNuEPi_W_%s", legendEntries[fileIndex]), "hNuMuPi0_W", 20, 0, 2500);

    // Define histograms for this file
    hNuMuPipm[fileIndex] = new TH1D(Form("hNuMuPipm_%s", legendEntries[fileIndex]), "", 20, 0, 2500);
    hNuMuPi0[fileIndex] = new TH1D(Form("hNuMuPi0_%s", legendEntries[fileIndex]), "hNuMuPi0", 20, 0, 2500);
    hNuEPipm[fileIndex] = new TH1D(Form("hNuEPipm_%s", legendEntries[fileIndex]), "hNuEPipm", 20, 0, 2500);
    hNuEPi0[fileIndex] = new TH1D(Form("hNuEPi0_%s", legendEntries[fileIndex]), "hNuEPi0", 20, 0, 2500);

    hNuMuPipm_W[fileIndex] = new TH1D(Form("hNuMuPipm_W_%s", legendEntries[fileIndex]), "", 20, 0, 2500);
    hNuMuPi0_W[fileIndex] = new TH1D(Form("hNuMuPi0_W_%s", legendEntries[fileIndex]), "hNuMuPi0_W", 20, 0, 2500);
    hNuEPipm_W[fileIndex] = new TH1D(Form("hNuEPipm_W_%s", legendEntries[fileIndex]), "hNuEPipm_W", 20, 0, 2500);
    hNuEPi0_W[fileIndex] = new TH1D(Form("hNuEPi0_W_%s", legendEntries[fileIndex]), "hNuEPi0_W", 20, 0, 2500);

    // Set titles for axes
    hNuMuPi[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuPi[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPi_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuPi_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    hNuMuPipm[fileIndex]->GetXaxis()->SetTitle("Enu [MeV]");
    hNuMuPipm[fileIndex]->GetYaxis()->SetTitle("A.U.");
    hNuMuPipm_W[fileIndex]->GetXaxis()->SetTitle("W [MeV]");
    hNuMuPipm_W[fileIndex]->GetYaxis()->SetTitle("A.U.");

    // Create branches variables
    int mode = 0;
    int PDG = 0;
    float W = 0;
    float Enu = 0;
    float fScaleFactor;

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

    // Fill histograms
    Long64_t nentries = Chain->GetEntries();
    for (Long64_t i = 0; i < nentries; ++i) {
      if (i % 100000 == 0) std::cout << i << std::endl;

      Chain->GetEntry(i);
      if(Enu * 1000 > 1000) continue;

      if(PlotShape) fScaleFactor = 1;
      if (PDG == 14) {
        if (mode == 11 || mode == 12 || mode == 13) {
          hNuMuPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }

        if (mode == 11 || mode == 13) {
          hNuMuPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }
        if (mode == 12) {
          hNuMuPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuMuPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }
      }
      if (PDG == 12) {
        if (mode == 11 || mode == 12 || mode == 13) {
          hNuEPi[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPi_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }

        if (mode == 11 || mode == 13) {
          hNuEPipm[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPipm_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }
        if (mode == 12) {
          hNuEPi0[fileIndex]->Fill(Enu * 1000, fScaleFactor);
          hNuEPi0_W[fileIndex]->Fill(W * 1000, fScaleFactor);
        }
      }
    }

    if(PlotShape)
    {
      hNuMuPi[fileIndex]->Scale(1.0 / hNuMuPi[fileIndex]->GetEntries());
      hNuEPi[fileIndex]->Scale(1.0 / hNuEPi[fileIndex]->GetEntries());
      hNuMuPi_W[fileIndex]->Scale(1.0 / hNuMuPi_W[fileIndex]->GetEntries());
      hNuEPi_W[fileIndex]->Scale(1.0 / hNuEPi_W[fileIndex]->GetEntries());

      // Normalize histograms
      hNuMuPipm[fileIndex]->Scale(1.0 / hNuMuPipm[fileIndex]->GetEntries());
      hNuMuPi0[fileIndex]->Scale(1.0 / hNuMuPi0[fileIndex]->GetEntries());
      hNuEPipm[fileIndex]->Scale(1.0 / hNuEPipm[fileIndex]->GetEntries());
      hNuEPi0[fileIndex]->Scale(1.0 / hNuEPi0[fileIndex]->GetEntries());

      hNuMuPipm_W[fileIndex]->Scale(1.0 / hNuMuPipm_W[fileIndex]->GetEntries());
      hNuMuPi0_W[fileIndex]->Scale(1.0 / hNuMuPi0_W[fileIndex]->GetEntries());
      hNuEPipm_W[fileIndex]->Scale(1.0 / hNuEPipm_W[fileIndex]->GetEntries());
      hNuEPi0_W[fileIndex]->Scale(1.0 / hNuEPi0_W[fileIndex]->GetEntries());
    }

    hNuMuPi[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPi[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuMuPi_W[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPi_W[fileIndex]->SetLineStyle(Style[fileIndex]);

    hNuMuPipm[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuMuPi0[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPipm[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPi0[fileIndex]->SetLineStyle(Style[fileIndex]);

    hNuMuPipm_W[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuMuPi0_W[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPipm_W[fileIndex]->SetLineStyle(Style[fileIndex]);
    hNuEPi0_W[fileIndex]->SetLineStyle(Style[fileIndex]);

    // Set colors for histograms
    hNuMuPi[fileIndex]->SetLineColor(kBlue);
    hNuEPi[fileIndex]->SetLineColor(kRed);
    hNuMuPi_W[fileIndex]->SetLineColor(kBlue);
    hNuEPi_W[fileIndex]->SetLineColor(kRed);

    hNuMuPipm[fileIndex]->SetLineColor(kBlue);
    hNuMuPi0[fileIndex]->SetLineColor(kRed);
    hNuEPipm[fileIndex]->SetLineColor(kGreen);
    hNuEPi0[fileIndex]->SetLineColor(kMagenta);

    hNuMuPipm_W[fileIndex]->SetLineColor(kBlue);
    hNuMuPi0_W[fileIndex]->SetLineColor(kRed);
    hNuEPipm_W[fileIndex]->SetLineColor(kGreen);
    hNuEPi0_W[fileIndex]->SetLineColor(kMagenta);

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

  hNuMuPi[0]->Draw("hist");
  hNuEPi[0]->Draw("hist SAME");
  hNuMuPi[1]->Draw("hist SAME");
  hNuEPi[1]->Draw("hist SAME");

  TLegend *Legend_Tot = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend_Tot->SetFillColor(0);
  Legend_Tot->SetFillStyle(0);
  Legend_Tot->SetLineWidth(0);
  Legend_Tot->SetLineColor(0);
  Legend_Tot->AddEntry(hNuMuPi[0], "NEUT #nu_{#mu} SPP", "l");
  Legend_Tot->AddEntry(hNuEPi[0], "NEUT #nu_{#mu} SPP", "l");
  Legend_Tot->AddEntry(hNuMuPi[1], "NUWRO #nu_{#mu} SPP", "l");
  Legend_Tot->AddEntry(hNuEPi[1], "NUWRO #nu_{#mu} SPP", "l");
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
  Legend_Tot_W->AddEntry(hNuMuPi_W[0], "NEUT #nu_{#mu} SPP", "l");
  Legend_Tot_W->AddEntry(hNuEPi_W[0], "NEUT #nu_{#mu} SPP", "l");
  Legend_Tot_W->AddEntry(hNuMuPi_W[1], "NUWRO #nu_{#mu} SPP", "l");
  Legend_Tot_W->AddEntry(hNuEPi_W[1], "NUWRO #nu_{#mu} SPP", "l");
  Legend_Tot_W->Draw("SAME");

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

  c1->Print("NIWG_Plot.pdf]");

  // Cleanup
  delete c1;
  delete Legend_Enu;
  delete Legend_W;
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
