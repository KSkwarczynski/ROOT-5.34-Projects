#include <fstream>
#include <iostream>
#include "TMath.h"

void CC1PiXsecEfficiencyAnalysis()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum0.root",false);
    
    Experiment exp("nd280");

    DataSample* R5mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum0.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5mc0", R5mc0);
    
    exp.AddSampleGroup("run5",run5);
    
    DataSample* R6bmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6b("run6b");
    run6b.AddMCSample("R6bmc0", R6bmc0);
    
    exp.AddSampleGroup("run6b",run6b);
    
    DataSample* R6cmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6cAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6c("run6c");
    run6c.AddMCSample("R6cmc0", R6cmc0);
    
    exp.AddSampleGroup("run6c",run6c);

    DataSample* R6dmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6dAntiNumuMultiPiAccum0.root");
     
    SampleGroup run6d("run6d");
    run6d.AddMCSample("R6dmc0", R6dmc0);
    
    exp.AddSampleGroup("run6d",run6d);
    
    DataSample* R6emc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6eAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6e("run6e");
    run6e.AddMCSample("R6emc0", R6emc0);
    
    exp.AddSampleGroup("run6e",run6e);

   
    DataSample* R7mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun7AntiNumuMultiPiAccum0.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc0", R7mc0);
    
    exp.AddSampleGroup("run7",run7);
    
    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/CC1piXsec/EfficiencyPlots/";
    TString FileNames0;
    TString PrintName0;
    
    for(int ik=0; ik<9; ik++)
    {
        FileNames0=Form("EffciencyLeptonThetaAccum%dX.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[0]>%d for #mu^{+} cos#theta",ik));
        draw.SetTitleX("true #mu^{+} cos#theta");
        draw.DrawEff(exp,false,"truelepton_costheta",40,0.,1.,Form("accum_level[0]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyPiThetaAccum%dX.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[0]>%d #pi^{-} cos#theta",ik));
        draw.SetTitleX("true #pi^{-} cos#theta");
        draw.DrawEff(exp,false,"truepi_costheta",40,0.,1.,Form("accum_level[0]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyLeptonMomAccum%dX.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[0]>%d for #mu^{+} mom",ik));
        draw.SetTitleX("true #mu^{+} mom");
        draw.DrawEff(exp,false,"truelepton_mom",40,0.,3000.,Form("accum_level[0]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyPiMomAccum%dX.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[0]>%d #pi^{-} mom",ik));
        draw.SetTitleX("true #pi^{-} mom");
        draw.DrawEff(exp,false,"truepi_mom",40,0.,3000.,Form("accum_level[0]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
    }

}
