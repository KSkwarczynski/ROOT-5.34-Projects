#include <iostream>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include "TGraph.h"
#include <TF1.h>
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include <TAxis.h>

void CompareSplines() 
{
  TFile *file[2];
  TTree *tree[2];
  
    file[0] = new TFile("/mnt/home/share/t2k/kskwarczynski/BANFF/splines/2020/run2aMCsplines.root");
    file[1] = new TFile("/mnt/home/kskwarczynski/OA_T2K/OAGenWeightsApps/OA2021/build/app/ND280/run2aMCsplines.root");

  
    TObjArray *MAQE_1;
    TObjArray *PDD_C_1;
    TObjArray *CA5_1;
    TObjArray *CC_BY_DIS_1;
    TObjArray *FEFQEH_1;
    TObjArray *FEFINEL_1;
    TObjArray *ISO_BKG_1;
    TObjArray *FEFABS_1;
    TObjArray *FEFCX_1;  
    TObjArray *FEFQE_1;
        
    TObjArray *MAQE_2;
    TObjArray *PDD_C_2;
    TObjArray *CA5_2;
    TObjArray *CC_BY_DIS_2;
    TObjArray *FEFQEH_2;
    TObjArray *FEFINEL_2;
    TObjArray *ISO_BKG_2;
    TObjArray *FEFABS_2;
    TObjArray *FEFCX_2;
    TObjArray *FEFQE_2;

    tree[0] = (TTree*)file[0]->Get("sample_sum");
    tree[0]->SetBranchAddress("MAQEGraph", &MAQE_1);
    tree[0]->SetBranchAddress("PDD_CGraph", &PDD_C_1);
    tree[0]->SetBranchAddress("CA5Graph", &CA5_1);
    tree[0]->SetBranchAddress("DIS_BY_corrGraph", &CC_BY_DIS_1);
    tree[0]->SetBranchAddress("FSI_INEL_HIGraph", &FEFQEH_1);
    tree[0]->SetBranchAddress("FSI_PI_PRODGraph", &FEFINEL_1);        
    tree[0]->SetBranchAddress("BgSclResGraph", &ISO_BKG_1); 
    tree[0]->SetBranchAddress("FSI_PI_ABSGraph", &FEFABS_1); 
    tree[0]->SetBranchAddress("FSI_CEX_LOGraph", &FEFCX_1); 
    tree[0]->SetBranchAddress("FSI_INEL_LOGraph", &FEFQE_1); 
    
   
    tree[1] = (TTree*)file[1]->Get("sample_sum");
    tree[1]->SetBranchAddress("MAQEGraph", &MAQE_2);
    tree[1]->SetBranchAddress("PDD_CGraph", &PDD_C_2);
    tree[1]->SetBranchAddress("CA5Graph", &CA5_2);
    tree[1]->SetBranchAddress("DIS_BY_corrGraph", &CC_BY_DIS_2);
    tree[1]->SetBranchAddress("FSI_INEL_HIGraph", &FEFQEH_2);
    tree[1]->SetBranchAddress("FSI_PI_PRODGraph", &FEFINEL_2);        
    tree[1]->SetBranchAddress("BgSclResGraph", &ISO_BKG_2);    
    tree[1]->SetBranchAddress("FSI_PI_ABSGraph", &FEFABS_2); 
    tree[1]->SetBranchAddress("FSI_CEX_LOGraph", &FEFCX_2); 
    tree[1]->SetBranchAddress("FSI_INEL_LOGraph", &FEFQE_2);
        
    TCanvas *canv = new TCanvas("canv", "canv", 2024, 1024);
    canv->Print("asdf.pdf[");
    int nentries = tree[0]->GetEntries();
    int count = 0;
  //for (int i = 0; i < nentries; ++i) {
  for (int i = 0; i < 1000; ++i) {

    TGraph *graphMAQE[2];
    TGraph *graphPDD_CGraph[2];
    TGraph *graphCA5[2];
    TGraph *graphDIS_BY[2];
    TGraph *graphISO_BKG[2];
    TGraph *graphFEFQEH[2];
    TGraph *graphFEFINEL[2];
    TGraph *graphFEFABS[2];
    TGraph *graphFEFCX[2];
    TGraph *graphFEFQE[2];
        
    for(int ik = 0; ik<2; ik++)
    {
        tree[ik]->GetEntry(i);
        if(ik ==0)
        {
            graphMAQE[ik] = (TGraph*)((MAQE_1)->At(0));
            graphPDD_CGraph[ik] = (TGraph*)((PDD_C_1)->At(0));
            graphCA5[ik] = (TGraph*)((CA5_1)->At(0));
            graphDIS_BY[ik] = (TGraph*)((CC_BY_DIS_1)->At(0));
            graphFEFQEH[ik] = (TGraph*)((FEFQEH_1)->At(0));
            graphFEFINEL[ik] = (TGraph*)((FEFINEL_1)->At(0));
            graphISO_BKG[ik] = (TGraph*)((ISO_BKG_1)->At(0));
            graphFEFABS[ik] = (TGraph*)((FEFABS_1)->At(0));
            graphFEFCX[ik] = (TGraph*)((FEFCX_1)->At(0));
            graphFEFQE[ik] = (TGraph*)((FEFQE_1)->At(0));
                        
            graphMAQE[ik]->SetLineStyle(kSolid);
            graphMAQE[ik]->SetLineColor(kRed);
            graphMAQE[ik]->SetMarkerStyle(2);
            graphMAQE[ik]->SetMarkerColor(kRed);
            
            graphPDD_CGraph[ik]->SetLineStyle(kSolid);
            graphPDD_CGraph[ik]->SetLineColor(kRed);
            graphPDD_CGraph[ik]->SetMarkerStyle(2);
            graphPDD_CGraph[ik]->SetMarkerColor(kRed);
            
            graphCA5[ik]->SetLineStyle(kSolid);
            graphCA5[ik]->SetLineColor(kRed);
            graphCA5[ik]->SetMarkerStyle(2);
            graphCA5[ik]->SetMarkerColor(kRed);
            
            graphDIS_BY[ik]->SetLineStyle(kSolid);
            graphDIS_BY[ik]->SetLineColor(kRed);
            graphDIS_BY[ik]->SetMarkerStyle(2);
            graphDIS_BY[ik]->SetMarkerColor(kRed);
            
            graphFEFQEH[ik]->SetLineStyle(kSolid);
            graphFEFQEH[ik]->SetLineColor(kRed);
            graphFEFQEH[ik]->SetMarkerStyle(2);
            graphFEFQEH[ik]->SetMarkerColor(kRed);
            
            graphFEFINEL[ik]->SetLineStyle(kSolid);
            graphFEFINEL[ik]->SetLineColor(kRed);
            graphFEFINEL[ik]->SetMarkerStyle(2);
            graphFEFINEL[ik]->SetMarkerColor(kRed);
            
            graphISO_BKG[ik]->SetLineStyle(kSolid);
            graphISO_BKG[ik]->SetLineColor(kRed);
            graphISO_BKG[ik]->SetMarkerStyle(2);
            graphISO_BKG[ik]->SetMarkerColor(kRed);
            
            graphFEFABS[ik]->SetLineStyle(kSolid);
            graphFEFABS[ik]->SetLineColor(kRed);
            graphFEFABS[ik]->SetMarkerStyle(2);
            graphFEFABS[ik]->SetMarkerColor(kRed);
            
            graphFEFCX[ik]->SetLineStyle(kSolid);
            graphFEFCX[ik]->SetLineColor(kRed);
            graphFEFCX[ik]->SetMarkerStyle(2);
            graphFEFCX[ik]->SetMarkerColor(kRed);
            
            graphFEFQE[ik]->SetLineStyle(kSolid);
            graphFEFQE[ik]->SetLineColor(kRed);
            graphFEFQE[ik]->SetMarkerStyle(2);
            graphFEFQE[ik]->SetMarkerColor(kRed);
        }
        if(ik ==1)
        {
            graphMAQE[ik] = (TGraph*)((MAQE_2)->At(0));
            graphPDD_CGraph[ik] = (TGraph*)((PDD_C_2)->At(0));
            graphCA5[ik] = (TGraph*)((CA5_2)->At(0));
            graphDIS_BY[ik] = (TGraph*)((CC_BY_DIS_2)->At(0));
            graphFEFQEH[ik] = (TGraph*)((FEFQEH_2)->At(0));
            graphFEFINEL[ik] = (TGraph*)((FEFINEL_2)->At(0));
            graphISO_BKG[ik] = (TGraph*)((ISO_BKG_2)->At(0));
            graphFEFABS[ik] = (TGraph*)((FEFABS_2)->At(0));
            graphFEFCX[ik] = (TGraph*)((FEFCX_2)->At(0));
            graphFEFQE[ik] = (TGraph*)((FEFQE_2)->At(0));

                        
            graphMAQE[ik]->SetLineStyle(kDashed);
            graphMAQE[ik]->SetLineColor(kBlue);
            graphMAQE[ik]->SetMarkerStyle(5);
            graphMAQE[ik]->SetMarkerColor(kBlue);
    
            graphPDD_CGraph[ik]->SetLineStyle(kDashed);
            graphPDD_CGraph[ik]->SetLineColor(kBlue);
            graphPDD_CGraph[ik]->SetMarkerStyle(5);
            graphPDD_CGraph[ik]->SetMarkerColor(kBlue);
            
            graphCA5[ik]->SetLineStyle(kDashed);
            graphCA5[ik]->SetLineColor(kBlue);
            graphCA5[ik]->SetMarkerStyle(5);
            graphCA5[ik]->SetMarkerColor(kBlue);
            
            graphDIS_BY[ik]->SetLineStyle(kDashed);
            graphDIS_BY[ik]->SetLineColor(kBlue);
            graphDIS_BY[ik]->SetMarkerStyle(5);
            graphDIS_BY[ik]->SetMarkerColor(kBlue);
            
            graphFEFQEH[ik]->SetLineStyle(kDashed);
            graphFEFQEH[ik]->SetLineColor(kBlue);
            graphFEFQEH[ik]->SetMarkerStyle(5);
            graphFEFQEH[ik]->SetMarkerColor(kBlue);
            
            graphFEFINEL[ik]->SetLineStyle(kDashed);
            graphFEFINEL[ik]->SetLineColor(kBlue);
            graphFEFINEL[ik]->SetMarkerStyle(5);
            graphFEFINEL[ik]->SetMarkerColor(kBlue);
            
            graphISO_BKG[ik]->SetLineStyle(kDashed);
            graphISO_BKG[ik]->SetLineColor(kBlue);
            graphISO_BKG[ik]->SetMarkerStyle(5);
            graphISO_BKG[ik]->SetMarkerColor(kBlue);
            
            graphFEFABS[ik]->SetLineStyle(kDashed);
            graphFEFABS[ik]->SetLineColor(kBlue);
            graphFEFABS[ik]->SetMarkerStyle(5);
            graphFEFABS[ik]->SetMarkerColor(kBlue);
            
            graphFEFCX[ik]->SetLineStyle(kDashed);
            graphFEFCX[ik]->SetLineColor(kBlue);
            graphFEFCX[ik]->SetMarkerStyle(5);
            graphFEFCX[ik]->SetMarkerColor(kBlue);
            
            graphFEFQE[ik]->SetLineStyle(kDashed);
            graphFEFQE[ik]->SetLineColor(kBlue);
            graphFEFQE[ik]->SetMarkerStyle(5);
            graphFEFQE[ik]->SetMarkerColor(kBlue);
        }
        
    }
    
    count++;
    canv->Clear();
    canv->Divide(5,2);
    canv->cd(1);
    graphMAQE[0]->SetTitle(Form("MAQE - Event %i", i));
    graphMAQE[0]->GetYaxis()->SetTitle("weight");
    graphMAQE[0]->GetXaxis()->SetTitle("parameter variation");
    graphMAQE[0]->Draw();
    graphMAQE[1]->Draw("SAME");
        
    canv->cd(2);
    graphPDD_CGraph[0]->SetTitle(Form("PDD_C - Event %i", i));
    graphPDD_CGraph[0]->GetYaxis()->SetTitle("weight");
    graphPDD_CGraph[0]->GetXaxis()->SetTitle("parameter variation");
    graphPDD_CGraph[0]->Draw();
    graphPDD_CGraph[1]->Draw("SAME");
        
    canv->cd(3);
    graphCA5[0]->SetTitle(Form("CA5 - Event %i", i));
    graphCA5[0]->GetYaxis()->SetTitle("weight");
    graphCA5[0]->GetXaxis()->SetTitle("parameter variation");
    graphCA5[0]->Draw();
    graphCA5[1]->Draw("SAME");
        
    canv->cd(4);
    graphISO_BKG[0]->SetTitle(Form("ISO_BKG - Event %i", i));
    graphISO_BKG[0]->GetYaxis()->SetTitle("weight");
    graphISO_BKG[0]->GetXaxis()->SetTitle("parameter variation");
    graphISO_BKG[0]->Draw();
    graphISO_BKG[1]->Draw("SAME");
    
    canv->cd(5);
    graphDIS_BY[0]->SetTitle(Form("DIS_BY[ - Event %i", i));
    graphDIS_BY[0]->GetYaxis()->SetTitle("weight");
    graphDIS_BY[0]->GetXaxis()->SetTitle("parameter variation");
    graphDIS_BY[0]->Draw();
    graphDIS_BY[1]->Draw("SAME");
    
    
    canv->cd(6);
    graphFEFQEH[0]->SetTitle(Form("FEFQEH - Event %i", i));
    graphFEFQEH[0]->GetYaxis()->SetTitle("weight");
    graphFEFQEH[0]->GetXaxis()->SetTitle("parameter variation");
    graphFEFQEH[0]->Draw();
    graphFEFQEH[1]->Draw("SAME");
    
    canv->cd(7);
    graphFEFINEL[0]->SetTitle(Form("FEFINEL - Event %i", i));
    graphFEFINEL[0]->GetYaxis()->SetTitle("weight");
    graphFEFINEL[0]->GetXaxis()->SetTitle("parameter variation");
    graphFEFINEL[0]->Draw();
    graphFEFINEL[1]->Draw("SAME");
        
    canv->cd(8);
    graphFEFABS[0]->SetTitle(Form("FEFABS - Event %i", i));
    graphFEFABS[0]->GetYaxis()->SetTitle("weight");
    graphFEFABS[0]->GetXaxis()->SetTitle("parameter variation");
    graphFEFABS[0]->Draw();
    graphFEFABS[1]->Draw("SAME");
    
    canv->cd(9);
    graphFEFCX[0]->SetTitle(Form("FEFCX - Event %i", i));
    graphFEFCX[0]->GetYaxis()->SetTitle("weight");
    graphFEFCX[0]->GetXaxis()->SetTitle("parameter variation");
    graphFEFCX[0]->Draw();
    graphFEFCX[1]->Draw("SAME");
    
    canv->cd(10);
    graphFEFQE[0]->SetTitle(Form("FEFQE - Event %i", i));
    graphFEFQE[0]->GetYaxis()->SetTitle("weight");
    graphFEFQE[0]->GetXaxis()->SetTitle("parameter variation");
    graphFEFQE[0]->Draw();
    graphFEFQE[1]->Draw("SAME");
    
    canv->Print("asdf.pdf");
  }
  std::cout << "Found " << count << " graphs" << std::endl;
  canv->Print("asdf.pdf]");
}
