#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TROOT.h"

void PrintCRPA() {
    // Open the ROOT file
    TFile *file = TFile::Open("LLHScan_V9Splines_V4Binning_V5CovMat.root");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    // Set global style to remove statistics box
    gStyle->SetOptStat(0);

    // Retrieve the histograms
    TH1 *hist1 = NULL;
    TH1 *hist2 = NULL;

    file->GetObject("Sample_LLH/FSI_strength_C_nu_0_sam", hist1);
    file->GetObject("xsec_LLH/FSI_strength_C_nu_0_xsec", hist2);

    hist1->SetLineColor(kBlue);
    hist2->SetLineColor(kRed);


    hist1->SetTitle("FSI strength C #nu 0");
    hist1->GetXaxis()->SetTitle("Parameter Variation");
    hist1->GetYaxis()->SetTitle("-2LLH");
    // Optionally draw the histogram
    TCanvas *c1 = new TCanvas("c1", "Histogram 1", 800, 600);
    c1->SetGrid();
    hist1->Draw();
    hist2->Draw("SAME");

    TLegend *Legend = new TLegend(0.2, 0.6, 0.6, 0.9);
    Legend->SetFillColor(0);
    Legend->SetFillStyle(0);
    Legend->SetLineWidth(0);
    Legend->SetLineColor(0);
    Legend->AddEntry(hist1, "LLH Stat", "l");
    Legend->AddEntry(hist2, "LLH Prior", "l");

    Legend->Draw("SAME");


    c1->SaveAs("CRPA.pdf");


    // Close the ROOT file
    file->Close();
    delete file;
}
