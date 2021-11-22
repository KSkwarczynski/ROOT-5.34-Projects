#include <TH2Poly.h>
#include <TH2D.h>
#include <vector>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <THStack.h>
#include <iostream>
#include <TF1.h>
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"

//g++ `root-config --cflags` -g -std=c++11 -o BinningStudy BinningStudy.cpp -I`root-config --incdir` `root-config --glibs --libs` 



void SKspectra()
{
     TCanvas *c1 = new TCanvas("canvas","canvas", 0, 0, 1024, 1024);
        c1->Print("dupa.pdf[", "pdf");
    TFile* Spectra_Restricted = TFile::Open("Spectra_Restricted.root");
    TFile* Spectra_Standard = TFile::Open("Spectra_Standard.root");
    
  
        TH1D *FHC1Rmu_Restricted = (TH1D*)(Spectra_Restricted->Get("FHC1Rmu-2021"));
        TH1D *RHC1Rmu_Restricted = (TH1D*)(Spectra_Restricted->Get("RHC1Rmu-2021"));
        TH1D *FHCnumuCC1pi_Restricted = (TH1D*)(Spectra_Restricted->Get("FHCnumuCC1pi-2021"));
        
        TH2D *FHC1Re_Restricted = (TH2D*)(Spectra_Restricted->Get("FHC1Re-2021"));
        TH2D *RHC1Re_Restricted = (TH2D*)(Spectra_Restricted->Get("RHC1Re-2021"));
        TH2D *FHC1Re1de_Restricted = (TH2D*)(Spectra_Restricted->Get("FHC1Re1de-2021"));

        
        TH1D *FHC1Rmu_Standard = (TH1D*)(Spectra_Standard->Get("FHC1Rmu-2021"));
        TH1D *RHC1Rmu_Standard = (TH1D*)(Spectra_Standard->Get("RHC1Rmu-2021"));
        TH1D *FHCnumuCC1pi_Standard = (TH1D*)(Spectra_Standard->Get("FHCnumuCC1pi-2021"));
        
        TH2D *FHC1Re_Standard = (TH2D*)(Spectra_Standard->Get("FHC1Re-2021"));
        TH2D *RHC1Re_Standard = (TH2D*)(Spectra_Standard->Get("RHC1Re-2021"));
        TH2D *FHC1Re1de_Standard = (TH2D*)(Spectra_Standard->Get("FHC1Re1de-2021"));
        
        
        FHC1Rmu_Restricted->SetLineStyle(kSolid);
        FHC1Rmu_Restricted->SetLineWidth(3);
        FHC1Rmu_Restricted->SetLineColor(kRed);

        FHC1Rmu_Standard->SetLineStyle(kDashed);
        FHC1Rmu_Standard->SetLineWidth(3);
        FHC1Rmu_Standard->SetLineColor(kBlue);
    
        
        RHC1Rmu_Restricted->SetLineStyle(kSolid);
        RHC1Rmu_Restricted->SetLineWidth(3);
        RHC1Rmu_Restricted->SetLineColor(kRed);

        RHC1Rmu_Standard->SetLineStyle(kDashed);
        RHC1Rmu_Standard->SetLineWidth(3);
        RHC1Rmu_Standard->SetLineColor(kBlue);
        
        
        FHCnumuCC1pi_Restricted->SetLineStyle(kSolid);
        FHCnumuCC1pi_Restricted->SetLineWidth(3);
        FHCnumuCC1pi_Restricted->SetLineColor(kRed);

        FHCnumuCC1pi_Standard->SetLineStyle(kDashed);
        FHCnumuCC1pi_Standard->SetLineWidth(3);
        FHCnumuCC1pi_Standard->SetLineColor(kBlue);
        
        FHC1Rmu_Restricted->SetTitle("FHC1Rmu");
        FHC1Rmu_Restricted->GetXaxis()->SetRangeUser(0,10);
        FHC1Rmu_Standard->GetXaxis()->SetRangeUser(0,10);
        
        
        FHC1Rmu_Restricted->Draw("");
        FHC1Rmu_Standard->Draw("same");
        
        TLegend *legend= new TLegend(0.25,0.52,0.45,0.88);;
        legend->AddEntry(FHC1Rmu_Restricted, "Restricted","l");
        legend->AddEntry(FHC1Rmu_Standard, "Standard","l");
        legend->SetTextSize(0.04);
        legend->Draw();

        c1->Print("dupa.pdf", "pdf");
                    
        RHC1Rmu_Restricted->SetTitle("RHC1Rmu");
        RHC1Rmu_Restricted->GetXaxis()->SetRangeUser(0,10);
        RHC1Rmu_Standard->GetXaxis()->SetRangeUser(0,10);
        
        RHC1Rmu_Restricted->Draw("");
        RHC1Rmu_Standard->Draw("same");
        
        TLegend *legend= new TLegend(0.25,0.52,0.45,0.88);;
        legend->AddEntry(RHC1Rmu_Restricted, "Restricted","l");
        legend->AddEntry(RHC1Rmu_Standard, "Standard","l");
        legend->SetTextSize(0.04);
        legend->Draw();

        c1->Print("dupa.pdf", "pdf");
        
        FHCnumuCC1pi_Restricted->SetTitle("FHCnumuCC1pi");
        FHCnumuCC1pi_Restricted->GetXaxis()->SetRangeUser(0,10);
        FHCnumuCC1pi_Standard->GetXaxis()->SetRangeUser(0,10);
                        
        FHCnumuCC1pi_Restricted->Draw("");
        FHCnumuCC1pi_Standard->Draw("same");
        
        TLegend *legend= new TLegend(0.50,0.52,0.75,0.88);;
        legend->AddEntry(FHCnumuCC1pi_Restricted, "Restricted","l");
        legend->AddEntry(FHCnumuCC1pi_Standard, "Standard","l");
        legend->SetTextSize(0.04);
        legend->Draw();

        c1->Print("dupa.pdf", "pdf");
        
                    
        c1->Print("dupa.pdf]", "pdf");                
}


