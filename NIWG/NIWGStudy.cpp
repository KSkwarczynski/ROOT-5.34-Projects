// Include necessary ROOT headers
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <THStack.h>
#include <TCanvas.h>

void NIWGStudy() {

  TChain* Chain = new TChain("NIWGTree","FlatTree_VARS");
  Chain->Add("NIWGtree.root");


  TH1D *hCCQEMF = new TH1D("hCCQEMF", "CCQE MF", 100, 0, 1000);
  TH1D *hCCQESRC = new TH1D("hCCQESRC", "CCQE SRC", 100, 0, 1000);
  TH1D *h2p2h = new TH1D("h2p2h", "2p2h", 100, 0, 1000);
  TH1D *hSPP = new TH1D("hSPP", "SPP", 100, 0, 1000);

  std::string Variable = "q0";
  hCCQEMF->GetXaxis()->SetTitle("q0 [MeV]");
  hCCQEMF->GetYaxis()->SetTitle("A.U.");

  // Create branches variables
  int mode = 0;
  bool issrc = 0;
  double q0 = 0;
  double Enu = 0;


  // Set branch addresses
  Chain->SetBranchStatus("*", false);
  Chain->SetBranchStatus("neutmode", true);
  Chain->SetBranchAddress("neutmode", &(mode));
  Chain->SetBranchStatus(Variable.c_str(), true);
  Chain->SetBranchAddress(Variable.c_str(), &(q0));
  Chain->SetBranchStatus("isSRC", true);
  Chain->SetBranchAddress("isSRC", &(issrc));

  Chain->SetBranchStatus("q3", true);
  Chain->SetBranchAddress("q3", &(Enu));

  // Fill histograms
  Long64_t nentries = Chain->GetEntries();
  for (Long64_t i = 0; i < nentries; ++i)
  {
    if (i % (100000) == 0) std::cout<<i<<std::endl;

    Chain->GetEntry(i);
    if(Enu*1000 > 600 || Enu*1000 < 500) continue;

    //std::cout<<i<<" "<<q0*1000<<" "<<mode<<" "<<issrc<<std::endl;
    if (mode == 1)
    {
      if(issrc)
      {
        hCCQESRC->Fill(q0*1000);
      }
      else
      {
        hCCQEMF->Fill(q0*1000);
      }
    } else if (mode == 2) {
      h2p2h->Fill(q0*1000);
    }
    else if ((11 <= std::abs(mode) && std::abs(mode) <= 13)) {
      hSPP->Fill(q0*1000);
    }
  }

  // Create a stack and add histograms to it
  THStack *hs = new THStack("hs", "NEUT");
  //hCCQEMF->SetFillColor(kBlue);
  hCCQEMF->SetLineColor(kBlue);
  //hCCQESRC->SetFillColor(kRed);
  hCCQESRC->SetLineColor(kRed);
  //h2p2h->SetFillColor(kMagenta+2);
  h2p2h->SetLineColor(kMagenta+2);
  //hSPP->SetFillColor(kGreen);
  hSPP->SetLineColor(kGreen);

  hs->Add(hCCQEMF);
  hs->Add(hCCQESRC);
  hs->Add(h2p2h);
  hs->Add(hSPP);
  // Draw the stack
  TCanvas *c1 = new TCanvas("c1", "NEUT", 800, 600);
  hs->Draw("hist");
  hs->GetXaxis()->SetTitle("q_0 [MeV]");
  hs->GetYaxis()->SetTitle("A.U.");

  hCCQEMF->Draw("h");
  hCCQESRC->Draw("h SAME");
  h2p2h->Draw("h SAME");
  hSPP->Draw("h SAME");

  TLegend *Legend = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend->SetFillColor(0);
  Legend->SetFillStyle(0);
  Legend->SetLineWidth(0);
  Legend->SetLineColor(0);
  Legend->AddEntry(hCCQEMF, "CCQE MF", "l");
  Legend->AddEntry(hCCQESRC, "CCQE SRC", "l");
  Legend->AddEntry(h2p2h, "2p2h", "l");
  Legend->AddEntry(hSPP, "SPP", "l");

  Legend->Draw("SAME");
  c1->SaveAs("stacked_histogram.pdf");

  // Clean up
  delete c1;
  delete hs;
  delete hCCQEMF;
  delete hCCQESRC;
  delete h2p2h;
  delete Chain;
  delete Legend;
}
