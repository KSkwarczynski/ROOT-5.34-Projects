#include <fstream>
#include <iostream>
#include "TMath.h"

void EfficiencyAnalysis()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("AntiNumuMultiPiAccum5_00.root",false);    

    Experiment exp("nd280");
    
    DataSample* mc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum0_00.root");
    DataSample* mc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum0_01.root");
    DataSample* mc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum0_02.root");
    DataSample* mc003 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum0_03.root");
    DataSample* mc004 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum0_04.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("mc000", mc000);
    run5.AddMCSample("mc001", mc001);
    run5.AddMCSample("mc002", mc002);
    run5.AddMCSample("mc003", mc003);
    run5.AddMCSample("mc004", mc004);

    exp.AddSampleGroup("run5",run5);
    
    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/EfficiencyPlots/";
    TString FileNames0;
    TString PrintName0;
    
    for(int ik=0; ik<9; ik++)
    {
        FileNames0=Form("EffciencyLeptonAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[1]>%d for #mu^{+}",ik));
        draw.SetTitleX("true #mu^{+} cos#theta");
        draw.DrawEff(exp,false,"truelepton_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyPiAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[1]>%d #pi^{-}",ik));
        draw.SetTitleX("true #pi^{-} cos#theta");
        draw.DrawEff(exp,false,"truepi_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
    }

}
