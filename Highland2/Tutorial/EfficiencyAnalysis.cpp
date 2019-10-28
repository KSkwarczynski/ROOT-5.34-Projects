#include <fstream>
#include <iostream>
#include "TMath.h"

void AntiMuMultiPiAnalysis()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("AntiNumuMultiPiAccum5_00.root",false);    

    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/EfficiencyPlots";
    TString FileNames0[8];
    TString PrintName0[8];
    
    for(int i=0; i<8; i++)
    {
        FileNames0[i]=Form("EffciencyAccum%d",i);
        PrintName0[i]=PathName+FileNames0[i];
    }
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
    draw.SetTitleX("tue #mu^{+} cos#theta");
    for(int ik=0; ik<8; ik++)
    {
        draw.SetTitle(Form("accum[0][1]>%d Z distance difference",ik));
        draw.DrawEff(exp,false,"truelepton_costheta",20,0.,5000.,Form("accum_level[0][1]>%d",ik),"1==1","","","");
        c1->Print(PrintName0[ik]);
    }
 

}
