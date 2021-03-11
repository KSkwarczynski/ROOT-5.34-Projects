#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "TObjArray.h"
#include "TChain.h"
#include "TFile.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TGraphErrors.h"
#include "TVectorD.h"
#include "TColor.h"
#include "TMath.h"

void DataMCproton()
{
    //gStyle->SetOptStat(0);
    //gStyle->SetPadColor(0);
    //gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Resolution/DataResolution.root");


    DataSample data("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Resolution/DataResolution.root");
    DataSample mc("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Resolution/ResolutionMC.root");
    
        
    double POTData = 115.31e+19;
    double POTMC = 1.93389e+22;
    double POT_Weight = POTData/POTMC;
    
    
    const int    FHCNumuCC0Pi_Mom_NBin        = 28;
    const double FHCNumuCC0Pi_Mom_Bin[29]     = {0.   , 200. , 300. , 400. , 450. , 500. , 550. , 600. ,650. , 700. , 750. , 800. , 850. , 900. , 950. , 1000., 1050., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800., 2000., 2500., 3000., 5000.};
                                         
    const int    FHCNumuCC0Pi_0p_Mom_NBin        = 20;
    const double FHCNumuCC0Pi_0p_Mom_Bin[21]     = {0., 200., 300., 350., 400., 450., 500., 550., 600., 650., 700., 800., 900., 1000., 1250., 1500., 2000., 2500., 3000., 3500., 5000.};                                    
                                     
    const int    FHCNumuCC0Pi_Np_Mom_NBin        = 17;
    const double FHCNumuCC0Pi_Np_Mom_Bin[18]     = {0., 300., 400., 500., 550., 600., 650., 700., 800., 900., 1000., 1250., 1500., 1750., 2000., 2750., 3500., 5000.};
    
    
    const int    FHCNumuCC0Pi_Cos_NBin = 28;
    const double FHCNumuCC0Pi_Cos_Bin[29] = { 0.5, 0.6, 0.7, 0.76, 0.78, 0.8, 0.83, 0.85, 0.88, 0.89, 0.9, 0.91, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1.};
  
  
    const int    FHCNumuCC0Pi_0p_Cos_NBin = 13;
    const double FHCNumuCC0Pi_0p_Cos_Bin[14] = {0.5, 0.6, 0.7, 0.80, 0.85, 0.88, 0.9, 0.92, 0.95, 0.96, 0.98, 0.99, 0.995, 1.0};
    
    const   int    FHCNumuCC0Pi_Np_Cos_NBin = 11;
    const  double FHCNumuCC0Pi_Np_Cos_Bin[12] = {0.55, 0.65, 0.75, 0.8, 0.88, 0.9, 0.92, 0.95, 0.96, 0.975, 0.985, 1.0};

    
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->Print("ProtonSelecPlots.pdf[", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0Pi FGD1");
    draw.SetTitleX("Muon candidate momentum [MeV/c]");
    draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_Mom_NBin, FHCNumuCC0Pi_Mom_Bin, "reaction", "accum_level[0][0][0]>7");    
    //draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_Mom_NBin, FHCNumuCC0Pi_Mom_Bin, "reaction", "accum_level[0][0][0]>7", "", "", false, POT_Weight, false);    
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0Pi-0p FGD1");
    draw.SetTitleX("Muon candidate momentum [MeV/c]");
    draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_0p_Mom_NBin, FHCNumuCC0Pi_0p_Mom_Bin, "reaction", "accum_level[0][0][0]>8"); 
    //draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_0p_Mom_NBin, FHCNumuCC0Pi_0p_Mom_Bin, "reaction", "accum_level[0][0][0]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0Pi-Np FGD1");
    draw.SetTitleX("Muon candidate momentum [MeV/c]");
    draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_Np_Mom_NBin, FHCNumuCC0Pi_Np_Mom_Bin, "reaction", "accum_level[0][0][1]>8"); 
    //draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_Np_Mom_NBin, FHCNumuCC0Pi_Np_Mom_Bin, "reaction", "accum_level[0][0][1]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0Pi-0p FGD2");
    draw.SetTitleX("Muon candidate momentum [MeV/c]");
    draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_0p_Mom_NBin, FHCNumuCC0Pi_0p_Mom_Bin, "fgd2reaction", "accum_level[0][1][0]>8");
    //draw.Draw(data, mc, "selmu_mom", FHCNumuCC0Pi_0p_Mom_NBin, FHCNumuCC0Pi_0p_Mom_Bin, "fgd2reaction", "accum_level[0][1][0]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0Pi-Np FGD2");
    draw.SetTitleX("Muon candidate momentum [MeV/c]");
    draw.Draw(data, mc, "selmu_mom",FHCNumuCC0Pi_Np_Mom_NBin, FHCNumuCC0Pi_Np_Mom_Bin, "fgd2reaction", "accum_level[0][1][1]>8"); 
    //draw.Draw(data, mc, "selmu_mom",FHCNumuCC0Pi_Np_Mom_NBin, FHCNumuCC0Pi_Np_Mom_Bin, "fgd2reaction", "accum_level[0][1][1]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");

    

    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi FGD1");
    draw.SetTitleX("#mu^{-} candidate cos#theta");
    draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Cos_NBin, FHCNumuCC0Pi_Cos_Bin, "reaction", "accum_level[0][0][0]>7");
    //draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Cos_NBin, FHCNumuCC0Pi_Cos_Bin, "reaction", "accum_level[0][0][0]>7", "", "", false, POT_Weight, false);    
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi-0p FGD1");
    draw.SetTitleX("#mu^{-} candidate cos#theta");
    draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_0p_Cos_NBin, FHCNumuCC0Pi_0p_Cos_Bin, "reaction", "accum_level[0][0][0]>8"); 
    //draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_0p_Cos_NBin, FHCNumuCC0Pi_0p_Cos_Bin, "reaction", "accum_level[0][0][0]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi-Np FGD1");
    draw.SetTitleX("#mu^{-} candidate cos#theta");
    draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Np_Cos_NBin, FHCNumuCC0Pi_Np_Cos_Bin, "reaction", "accum_level[0][0][1]>8"); 
    //draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Np_Cos_NBin, FHCNumuCC0Pi_Np_Cos_Bin, "reaction", "accum_level[0][0][1]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi-0p FGD2");
    draw.SetTitleX("#mu^{-} candidate cos#theta");
    draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_0p_Cos_NBin, FHCNumuCC0Pi_0p_Cos_Bin, "fgd2reaction", "accum_level[0][1][0]>8");
    //draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_0p_Cos_NBin, FHCNumuCC0Pi_0p_Cos_Bin, "fgd2reaction", "accum_level[0][1][0]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi-Np FGD2");
    draw.SetTitleX("#mu^{-} candidate cos#theta");
    draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Np_Cos_NBin, FHCNumuCC0Pi_Np_Cos_Bin, "fgd2reaction", "accum_level[0][1][1]>8"); 
    //draw.Draw(data, mc, "selmu_costheta",FHCNumuCC0Pi_Np_Cos_NBin, FHCNumuCC0Pi_Np_Cos_Bin, "fgd2reaction", "accum_level[0][1][1]>8", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    
    
    draw.SetTitle("FGD1");
    draw.SetTitleX("Momentum of FGD proton candidate");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "FGDProtMom",40., 0., 2500. ,"reaction", "accum_level[0][0][0]>7"); 
    //draw.Draw(data, mc, "FGDProtMom",40., 0., 2500. ,"reaction", "accum_level[0][0][0]>7", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
        
    draw.SetTitle("FGD1");
    draw.SetTitleX("Momentum of TPC proton candidate");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "TPCProtMom",40., 0., 2500. ,"reaction", "accum_level[0][0][0]>7"); 
    //draw.Draw(data, mc, "TPCProtMom",40., 0., 2500. ,"reaction", "accum_level[0][0][0]>7", "", "", false, POT_Weight, false); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    
    draw.SetTitle("FGD2");
    draw.SetTitleX("Momentum of FGD proton candidate");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "FGDProtMom",40., 0., 2500. ,"reaction", "accum_level[0][1][0]>7"); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
        
    draw.SetTitle("FGD2");
    draw.SetTitleX("Momentum of TPC proton candidate");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "TPCProtMom",40., 0., 2500. ,"reaction", "accum_level[0][1][0]>7"); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    
    
    draw.SetTitle("FGD1");
    draw.SetTitleX("Number of recosntucted FGD protons");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "nProtonsFGD",5., 0., 5. ,"reaction", "accum_level[0][0][0]>7"); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
        
    draw.SetTitle("FGD1");
    draw.SetTitleX("Number of recosntucted TPC protons");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "nProtonsTPC",5., 0., 5. ,"reaction", "accum_level[0][0][0]>7"); ; 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    
    draw.SetTitle("FGD2");
    draw.SetTitleX("Number of recosntucted FGD protons");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "nProtonsFGD",5., 0., 5. ,"reaction", "accum_level[0][1][0]>7"); 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
        
    draw.SetTitle("FGD2");
    draw.SetTitleX("Number of recosntucted TPC protons");
    draw.SetLegendPos("tr");
    draw.Draw(data, mc, "nProtonsTPC",5., 0., 5. ,"reaction", "accum_level[0][1][0]>7"); ; 
    c1->Print("ProtonSelecPlots.pdf", "pdf");
    
    c1->Print("ProtonSelecPlots.pdf]", "pdf");
    delete c1;
}
