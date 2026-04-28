#include <TFile.h>
#include <TH1D.h>
#include <iostream>



void DrawJarlskogPlot(TCanvas* c1,
                      TH1* h_post_flatDelta,
                      TH1* h_post_flatSinDelta,
                      TH1* h_prior_flatDelta,
                      TH1* h_prior_flatSinDelta,
                      double theta23_min,
                      double theta23_max,
                      const char* outname = "Jarl.pdf")
{
  // ---- Style ----
  h_post_flatDelta->SetLineColor(kAzure+2);
  h_post_flatDelta->SetLineWidth(2);

  h_post_flatSinDelta->SetLineColor(kRed+1);
  h_post_flatSinDelta->SetLineWidth(2);

  h_prior_flatDelta->SetLineColor(kAzure+2);
  h_prior_flatDelta->SetLineStyle(2);
  h_prior_flatDelta->SetLineWidth(2);

  h_prior_flatSinDelta->SetLineColor(kRed+1);
  h_prior_flatSinDelta->SetLineStyle(2);
  h_prior_flatSinDelta->SetLineWidth(2);

  // ---- Axis ----
  h_post_flatDelta->SetTitle("");
  h_post_flatDelta->GetXaxis()->SetTitle("J #equiv s_{13}c_{13}^{2}s_{12}c_{12}s_{23}c_{23}sin#delta");
  h_post_flatDelta->GetYaxis()->SetTitle("Probability Density");

  // ---- Draw ----
  h_post_flatDelta->Draw("hist");
  h_post_flatSinDelta->Draw("hist same");
  h_prior_flatDelta->Draw("hist same");
  h_prior_flatSinDelta->Draw("hist same");

  Double_t value_post = h_post_flatDelta->GetBinContent(h_post_flatDelta->FindBin(0));
  Double_t value_prior = h_prior_flatDelta->GetBinContent(h_prior_flatDelta->FindBin(0));
  Double_t value_post_sin = h_post_flatSinDelta->GetBinContent(h_post_flatSinDelta->FindBin(0));
  Double_t value_prior_sin = h_prior_flatSinDelta->GetBinContent(h_prior_flatSinDelta->FindBin(0));

  // ---- S-D values ----
  TString sd1 = Form("S-D: %.2f", value_prior / value_post);
  TString sd2 = Form("S-D: %.2f", value_prior_sin / value_post_sin);

  // Dummy for legend formatting
  TObject* dummy = (TObject*)0;

  // Header with dynamic range
  TString header = Form("sin^{2}#theta_{23} = [%.g, %.g]",
                        theta23_min, theta23_max);

  // ---- Legend ----
  TLegend* leg = new TLegend(0.35, 0.60, 0.85, 0.88);
  leg->SetNColumns(2);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.035);

  // Header row
  leg->AddEntry(dummy, header, "");
  leg->AddEntry(dummy, "", "");

  // Main entries
  leg->AddEntry(h_post_flatDelta, "Post, flat #delta_{CP}", "l");
  leg->AddEntry(h_post_flatSinDelta, "Post, flat sin#delta_{CP}", "l");
  leg->AddEntry(h_prior_flatDelta, "Prior, flat #delta_{CP}", "l");
  leg->AddEntry(h_prior_flatSinDelta, "Prior, flat sin#delta_{CP}", "l");

  // S-D row
  leg->AddEntry(dummy, sd1, "");
  leg->AddEntry(dummy, sd2, "");

  leg->Draw();

  // ---- Save ----
  c1->Print(outname);
}

void TidyHist(TH1* blarb, std::string name) {
  blarb->Scale(1.0 / blarb->Integral());
  Double_t value = blarb->GetBinContent(blarb->FindBin(0));
  std::cout << "Value at bin 0 for "<< name <<": " << value << std::endl;
}

void ReadJarl() {
  // Open the first file
  TFile *file1 = new TFile("OAR11B_23c_DataFit_MCMC_Reduced_Reweighted_smeared_jarlskog_wRC_withPriors.root", "READ");
  if (!file1 || file1->IsZombie()) {
      std::cerr << "Error opening first file!" << std::endl;
      return;
  }

  // Open the second file
  TFile *file2 = new TFile("priors.root", "READ");
  if (!file2 || file2->IsZombie()) {
      std::cerr << "Error opening second file!" << std::endl;
      file1->Close();
      return;
  }

  // Get the histograms
  TH1D *jarlskog_both = (TH1D*)file1->Get("jarlskog_both");
  TH1D *jarlskog_both_flatsindcp = (TH1D*)file1->Get("jarlskog_both_flatsindcp");

  TH1D *jarlskog_IH = (TH1D*)file1->Get("jarlskog_IH");
  TH1D *jarlskog_NH = (TH1D*)file1->Get("jarlskog_NH");

  TH1D *jarlskog_IH_flatsindcp = (TH1D*)file1->Get("jarlskog_IH_flatsindcp");
  TH1D *jarlskog_NH_flatsindcp = (TH1D*)file1->Get("jarlskog_NH_flatsindcp");

  TH1D *jarl_wRC_prior = (TH1D*)file2->Get("jarl_wRC_prior");
  TH1D *jarl_wRC_prior_flatsindcp = (TH1D*)file2->Get("jarl_wRC_prior_flatsindcp");

  TH1D *jarl_wRC_th23_0109_prior = (TH1D*)file2->Get("jarl_wRC_th23_0109_prior");
  TH1D *jarl_wRC_th23_0109_prior_flatsindcp = (TH1D*)file2->Get("jarl_wRC_th23_0109_prior_flatsindcp");

  TH1D *jarl_wRC_th23_0208_prior = (TH1D*)file2->Get("jarl_wRC_th23_0208_prior");
  TH1D *jarl_wRC_th23_0208_prior_flatsindcp = (TH1D*)file2->Get("jarl_wRC_th23_0208_prior_flatsindcp");

  TH1D *jarl_wRC_th23_0307_prior = (TH1D*)file2->Get("jarl_wRC_th23_0307_prior");
  TH1D *jarl_wRC_th23_0307_prior_flatsindcp = (TH1D*)file2->Get("jarl_wRC_th23_0307_prior_flatsindcp");

  TidyHist(jarlskog_both, "jarlskog_both");
  TidyHist(jarlskog_both_flatsindcp, "value_jarlskog_flatsindcp");
  TidyHist(jarlskog_IH, "jarlskog_both_IH");
  TidyHist(jarlskog_NH, "jarlskog_both_NH");
  TidyHist(jarlskog_IH_flatsindcp, "value_jarlskog_IH_flatsindcp");
  TidyHist(jarlskog_NH_flatsindcp, "value_jarlskog_NH_flatsindcp");
  TidyHist(jarl_wRC_prior, "jarl_wRC_prior");
  TidyHist(jarl_wRC_prior_flatsindcp, "jarl_wRC_prior_flatsindcp");
  TidyHist(jarl_wRC_th23_0109_prior, "jarl_wRC_th23_0109_prior");
  TidyHist(jarl_wRC_th23_0109_prior_flatsindcp, "jarl_wRC_th23_0109_prior_flatsindcp");
  TidyHist(jarl_wRC_th23_0208_prior, "jarl_wRC_th23_0208_prior");
  TidyHist(jarl_wRC_th23_0208_prior_flatsindcp, "jarl_wRC_th23_0208_prior_flatsindcp");
  TidyHist(jarl_wRC_th23_0307_prior, "jarl_wRC_th23_0307_prior");
  TidyHist(jarl_wRC_th23_0307_prior_flatsindcp, "jarl_wRC_th23_0307_prior_flatsindcp");

  // Create canvas
  TCanvas *c1 = new TCanvas("c1", "Jarlskog", 800, 600);
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  c1->SetBottomMargin(0.1f);
  c1->SetTopMargin(0.02f);
  c1->SetRightMargin(0.05f);
  c1->SetLeftMargin(0.15f);
  c1->Print("Jarl.pdf[");

  DrawJarlskogPlot(c1,
                   jarlskog_both,
                   jarlskog_both_flatsindcp,
                   jarl_wRC_prior,
                   jarl_wRC_prior_flatsindcp,
                   0.0, 1.0,
                   "Jarl.pdf");

  DrawJarlskogPlot(c1,
                   jarlskog_both,
                   jarlskog_both_flatsindcp,
                   jarl_wRC_th23_0109_prior,
                   jarl_wRC_th23_0109_prior_flatsindcp,
                   0.1, 0.9,
                   "Jarl.pdf");


  DrawJarlskogPlot(c1,
                   jarlskog_both,
                   jarlskog_both_flatsindcp,
                   jarl_wRC_th23_0208_prior,
                   jarl_wRC_th23_0208_prior_flatsindcp,
                   0.2, 0.8,
                   "Jarl.pdf");

  DrawJarlskogPlot(c1,
                   jarlskog_both,
                   jarlskog_both_flatsindcp,
                   jarl_wRC_th23_0307_prior,
                   jarl_wRC_th23_0307_prior_flatsindcp,
                   0.3, 0.7,
                   "Jarl.pdf");

  c1->Print("Jarl.pdf]");
  // Cleanup
  file1->Close();
  file2->Close();
}
