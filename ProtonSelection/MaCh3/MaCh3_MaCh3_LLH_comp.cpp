#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "TFile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TH1D.h"

#include "TVectorD.h"
#include "TVectorT.h"
#include "TVector.h"

#include "TMatrixD.h"
#include "TMatrixT.h"
#include "TMatrix.h"

#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"

#include "TLegend.h"

//// HOW TO RUN
//  .x MaCh3_MaCh3_LLH_comp.cpp("LLH_ND_Asimov_ND280logL_scan_OLD.root", "LLH_ND_Asimov_ND280logL_scan_PROTON.root")



// Declare these ahead
//std::vector<std::string> MakeBANFFNames();
//std::vector<std::string> MakeMaCh3Names();
//std::vector<double> GetXSecNominal();

//void BANFFMaCh3(std::string &, std::string &);

int MaCh3_MaCh3_LLH_comp(std::string BANFFFile, std::string MaCh3File) {

  //std::string BANFFFile = std::string(argv[1]);
  //std::string MaCh3File = std::string(argv[2]);

  // *******************
  std::cout << "DEFAULT file: " << BANFFFile << std::endl;
  std::cout << "PROTON file: " << MaCh3File << std::endl;

  TFile *BANFF = new TFile(BANFFFile.c_str());
  TFile *MaCh3 = new TFile(MaCh3File.c_str());

  TCanvas *Canvas = new TCanvas("canv", "canv", 1024, 1024);
  gStyle->SetOptStat(0);
  Canvas->SetBottomMargin(0.08);
  Canvas->SetTopMargin(0.06);
  Canvas->SetLeftMargin(0.10);
  Canvas->SetRightMargin(0.03);
  Canvas->SetGridx();
  Canvas->SetGridy();
  std::string pdfname = BANFFFile+"_"+MaCh3File;
  Canvas->Print((pdfname+".pdf[").c_str());

  // Get all the BANFF names, woop
  std::vector<std::string> BANFFNames = MakeMaCh3Names();
  std::vector<std::string> MaCh3Names = MakeMaCh3Names();


  // Now need to map these onto MaCh3 names somehow...
  unsigned int Params = BANFFNames.size();
  int nXsec = 0;
  int nXsecBANFF = 0;
  for (unsigned int i = 0; i < Params; ++i) {
  //for (unsigned int i = 0; i < 2; ++i) {
    //BANFFNames[i] += "_scan_total";
    //std::cout << "Getting " << BANFFNames[i] << std::endl;
    //TGraph *BANFFGraph = (TGraph*)(BANFF->Get(BANFFNames[i].c_str())->Clone());

    BANFFNames[i] += "_sam";
    std::string TempPath = "Sample_LLH/"+BANFFNames[i];
    std::cout << "Getting " << BANFFNames[i] << std::endl;
    TH1D *BANFFGraph = (TH1D*)( BANFF->Get(TempPath.c_str()) );
    
    MaCh3Names[i] += "_sam";
    std::string TempPath = "Sample_LLH/"+MaCh3Names[i];
    std::cout << "Getting " << MaCh3Names[i] << std::endl;
    TH1D *MaCh3Graph = (TH1D*)( MaCh3->Get(TempPath.c_str()) );

    /*
    // Need to make a new MaCh3 plot which is shifted for xsec parameters
    if (MaCh3Names[i].find("b_") == std::string::npos && MaCh3Names[i].find("ndd_")) {
      int nbins = MaCh3Graph->GetNbinsX();
      double shift = XSecNominals[nXsec];
      double scale =1;
      std::cout << "Shift " << MaCh3Names[i] << " by " << shift << std::endl;
      //Yikes this is really hard codey but... BANFF Eb is in units of sigma, MaCh3s is in MeV so let's scale the histogram axis by 1/prior, which is 6MeV for 2020 OA
      //      if(nXsec > XsecParams-5){
      //shift = -1;
      //scale = scale/6;
      // }
      double LowEdge = scale*(MaCh3Graph->GetBinLowEdge(1))-shift;
      double HighEdge = scale*(MaCh3Graph->GetBinLowEdge(nbins+1))-shift;
      TH1D *TempMaCh3 = new TH1D("tempmach3", "tempmach3", nbins, LowEdge, HighEdge);

      // Need to loop through the MaCh3 plot and shift every x value by the nominal
      for (int j = 0; j < MaCh3Graph->GetNbinsX(); ++j) {
        double content = MaCh3Graph->GetBinContent(j+1);
        TempMaCh3->SetBinContent(j+1, content);
      }

      delete MaCh3Graph;
      MaCh3Graph = TempMaCh3;

      nXsec++;
    }

    
      if (BANFFNames[i].find("b_") == std::string::npos && BANFFNames[i].find("ndd_")) {
      int nbins = BANFFGraph->GetNbinsX();
      double shift = XSecNominals[nXsecBANFF];
      double scale =1;
      std::cout << "Shift " << BANFFNames[i] << " by " << shift << std::endl;
      //Yikes this is really hard codey but... BANFF Eb is in units of sigma, MaCh3s is in MeV so let's scale the histogram axis by 1/prior, which is 6MeV for 2020 OA
      //      if(nXsec > XsecParams-5){
      //shift = -1;
      //scale = scale/6;
      // }
      double LowEdge = scale*(BANFFGraph->GetBinLowEdge(1))-shift;
      double HighEdge = scale*(BANFFGraph->GetBinLowEdge(nbins+1))-shift;
      TH1D *TempBANFF = new TH1D("TempBANFF", "TempBANFF", nbins, LowEdge, HighEdge);

      // Need to loop through the MaCh3 plot and shift every x value by the nominal
      for (int j = 0; j < BANFFGraph->GetNbinsX(); ++j) {
        double content = BANFFGraph->GetBinContent(j+1);
        TempBANFF->SetBinContent(j+1, content);
      }

      delete BANFFGraph;
      BANFFGraph = TempBANFF;

      nXsecBANFF++;
    }
    */
    
    
    
     if(!MaCh3Names[i].find("ndd_"))
      continue;

    
   if(!BANFFNames[i].find("ndd_"))
      continue;
    
    //    if(!MaCh3Names[i].find("EB")){
    //MaCh3Graph->Draw("AL");
    //BANFFGraph->Draw("same");
    // }
    //else {

      // }
    BANFFGraph->SetTitle(BANFFNames[i].c_str());
    BANFFGraph->SetLineStyle(kSolid);
    BANFFGraph->SetLineWidth(3);
    BANFFGraph->SetLineColor(kRed);
    BANFFGraph->GetXaxis()->SetTitle("Variation");
    BANFFGraph->GetYaxis()->SetTitle("-2LLH_{sample}");
    //BANFFGraph->GetYaxis()->SetTitle("-2LLH_{FULL}");

    MaCh3Graph->SetTitle(MaCh3Names[i].c_str());
    MaCh3Graph->SetLineStyle(kDashed);
    MaCh3Graph->SetLineWidth(3);
    MaCh3Graph->SetLineColor(kBlue);
    
    BANFFGraph->Draw("");
    MaCh3Graph->Draw("SAME");
      
    // Add a legend
    TLegend *leg = new TLegend(0.35, 0.5, 0.8, 0.75);
    leg->AddEntry(BANFFGraph, "Updated Uniform", "l");
    leg->AddEntry(MaCh3Graph, "Old Uniform", "l");
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    leg->SetLineWidth(0);
    leg->SetLineColor(0);
    leg->Draw("same");

    Canvas->Print((pdfname+".pdf").c_str());

    delete BANFFGraph;
    delete MaCh3Graph;
    delete leg;
  }
  Canvas->Print((pdfname+".pdf]").c_str());
}

// *******************
// Make vector for the MaCh3 TH1D names
std::vector<std::string> MakeMaCh3Names() {
  // *******************

  std::vector<std::string> NameVector;


  // The cross-section parameters
  // First FSI to match BANFF

  
  NameVector.push_back("MAQE");
  
   
  NameVector.push_back("Q2_norm_5");
  NameVector.push_back("Q2_norm_6");
  NameVector.push_back("Q2_norm_7");
  
  NameVector.push_back("PShell_MF_Norm_C");
  NameVector.push_back("SShell_MF_Norm_C");
  NameVector.push_back("SRC_Norm_C");
  NameVector.push_back("PShell_MF_PMissShape_C");
  NameVector.push_back("SShell_MF_PMissShape_C");
  NameVector.push_back("P1_2Shell_MF_Norm_O");
  NameVector.push_back("P3_2Shell_MF_Norm_O");
  NameVector.push_back("SShell_MF_Norm_O");
  NameVector.push_back("SRC_Norm_O");
  NameVector.push_back("P1_2Shell_MF_PMissShape_O");
  NameVector.push_back("P3_2Shell_MF_PMissShape_O");
  NameVector.push_back("SShell_MF_PMissShape_O");
  
  NameVector.push_back("Pauli_Blocking_C_nu");
  NameVector.push_back("Pauli_Blocking_O_nu");
  NameVector.push_back("Pauli_Blocking_C_nubar");
  NameVector.push_back("Pauli_Blocking_O_nubar");
  NameVector.push_back("Optical_Potential_C");
  NameVector.push_back("Optical_Potential_O");
  NameVector.push_back("MAQE");
  
  
  NameVector.push_back("2p2h_norm_nu");
  NameVector.push_back("2p2h_norm_nubar");
  NameVector.push_back("2p2h_normCtoO");
  NameVector.push_back("PNNN_Shape");
  NameVector.push_back("2p2h_shape_C_np");
  NameVector.push_back("2p2h_shape_C_NN");
  NameVector.push_back("2p2h_shape_O_np");
  NameVector.push_back("2p2h_shape_O_NN");

  NameVector.push_back("2p2h_Edep_lowEnu");
  NameVector.push_back("2p2h_Edep_highEnu");
  NameVector.push_back("2p2h_Edep_lowEnubar");
  NameVector.push_back("2p2h_Edep_highEnubar");
        
        
  NameVector.push_back("CA5");
  NameVector.push_back("MARES");
  NameVector.push_back("ISO_BKG_LowPPi");
  NameVector.push_back("ISO_BKG");

    NameVector.push_back("RES_Eb_C_numu");
  NameVector.push_back("RES_Eb_O_numu");
  NameVector.push_back("RES_Eb_C_numubar");
  NameVector.push_back("RES_Eb_O_numubar");
    NameVector.push_back("RS_Delta_Decay");

    
    NameVector.push_back("FEFQE");
  NameVector.push_back("FEFQEH");
  NameVector.push_back("FEFINEL");
  NameVector.push_back("FEFABS");
  NameVector.push_back("FEFCX");
  NameVector.push_back("FEFCXH");
    
      NameVector.push_back("MPi_Multi_TotXSec");
  NameVector.push_back("MPi_BY_Vector");
  NameVector.push_back("MPi_BY_Axial");
  NameVector.push_back("MPi_Multi_Shape");
    NameVector.push_back("CC_BY_DIS");

  NameVector.push_back("CC_DIS_MultPi_Norm_Nu");
  NameVector.push_back("CC_DIS_MultPi_Norm_Nubar");
  
  NameVector.push_back("CC_norm_nu");
  NameVector.push_back("CC_norm_nubar");

  NameVector.push_back("nue_numu");
  NameVector.push_back("nuebar_numubar");


  NameVector.push_back("CC_Coh_C");
  NameVector.push_back("CC_Coh_O");

  NameVector.push_back("NC_Coh");
  NameVector.push_back("NC_1gamma");
  NameVector.push_back("NC_other_near");
  NameVector.push_back("NC_other_far");

  NameVector.push_back("EB_dial_C_nu");
  NameVector.push_back("EB_dial_O_nu");
  NameVector.push_back("EB_dial_C_nubar");
  NameVector.push_back("EB_dial_O_nubar");

  // The ND280 parameters
  /*  for (int i = 0; i <= 573; ++i) {
    std::stringstream ss;
    ss << "ndd_" << i;
    NameVector.push_back(ss.str());
    }*/

  return NameVector;
}

