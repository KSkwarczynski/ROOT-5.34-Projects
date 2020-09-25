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

void ZeroProtonSelection()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6TZero.root",false);
    
    Experiment exp("nd280");

    DataSample* R4mP6T = new DataSample("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6TZero.root");
    
    SampleGroup run4("run4");
    run4.AddMCSample("R4mP6T", R4mP6T);

    exp.AddSampleGroup("run4",run4);
    
    TString Type[4] = {"fgdtargetCCZeroPi", "reaction" , "topology", "mectopology"};
    TString PathName="/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/plots/";
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->Print( Form("%sZeroProtonSelecPlots.pdf(", PathName.Data() ), "pdf");
    
    for(int ik=0; ik<4 ;ik++ )
    {
        /// \muTPC_pTPC
        draw.SetTitle("#muTPC_pTPC");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>8");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("#muTPC_pTPC");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} cos#theta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>8");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("#muTPC_pTPC");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selp_mom",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>8");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("#muTPC_pTPC");
        draw.SetLegendPos("tl");
        draw.SetTitleX("proton cos#theta");
        draw.Draw(exp,"selp_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>8");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \muTPC_pFGD
        draw.SetTitle("#muTPC_pFGD");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][2]>9");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("#muTPC_pFGD");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} cos#theta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>9");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("#muTPC_pFGD");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selp_mom_range_oarecon",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>9");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("#muTPC_pFGD");
        draw.SetLegendPos("tl");
        draw.SetTitleX("proton cos#theta");
        draw.Draw(exp,"selp_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>9");   
        
        c1->Print(Form("%sZeroProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        

    }
    
    c1->Print(Form("%sZeroProtonSelecPlots.pdf)",PathName.Data()), "pdf");
    delete c1;
}

 
