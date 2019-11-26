#include <fstream>
#include <iostream>
#include "TMath.h"

void OaAnalysisMultiPi()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    DrawingTools draw("OaA6TRun5tAntiNumuMultiPiAccum5_0.root",false);
   
    Experiment exp("nd280");
    SampleGroup run5("run5");
    
    DataSample* Oa6TR5mc0[4];
    for(int ik=0;ik<4;ik++)
    {
        cout<<"licznik "<<ik<<endl;
        Oa6TR5mc0[ik] = new DataSample(Form("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/oaA6TRun5Accum5Com_%d.root",ik));
        run5.AddMCSample(Form("Oa6TR5mc0[%d]",ik), Oa6TR5mc0[ik]);
        
    }
    exp.AddSampleGroup("run5",run5);
    
    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/OaPlots/";
    
    TString FileNames[2]={"Accum8MuonMomOa.pdf", "Accum8MuonThetaOa.pdf"};
    TString PrintName[2];
    
    for(int i=0; i<2; i++)
    {
        PrintName[i]=PathName+FileNames[i];
    }
    
    draw.SetTitle("accum[0][1]>8 #mu^{+} moementum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8");
    c1->Print(PrintName[0]);
    
    draw.SetTitle("accum[0][1]>8 #mu^{+} cos#theta");
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>8");
    c1->Print(PrintName[1]);
}
