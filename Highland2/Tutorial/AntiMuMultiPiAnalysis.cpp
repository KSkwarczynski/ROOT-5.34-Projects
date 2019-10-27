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
    
    Experiment exp("nd280");
    
    DataSample* mc500 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum5_00.root");
    DataSample* mc501 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum5_01.root");
    DataSample* mc502 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum5_02.root");
    DataSample* mc503 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum5_03.root");
    DataSample* mc504 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/AntiNumuMultiPiAccum5_04.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("mc500", mc500);
    run5.AddMCSample("mc501", mc501);
    run5.AddMCSample("mc502", mc502);
    run5.AddMCSample("mc503", mc503);
    run5.AddMCSample("mc504", mc504);
    
    exp.AddSampleGroup("run5",run5);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/";
    TString FileNames8[6]={"Accum8MuonMom.pdf","Accum8MuonCosT.pdf","Accum8PiMinMom.pdf","Accum8PiMinCosT.pdf", "Accum8PiMinMom0ME.pdf", "Accum8PiMinMom1ME.pdf"};
    TString PrintName8[6];
    
    for(int i=0; i<6; i++)
    {
        PrintName8[i]=PathName+FileNames8[i];
        PrintName0[i]=PathName+FileNames0[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[0]);
    
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[1]);

    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[2]);
    
    draw.SetTitleX("TPC #pi^{-} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"cos(NegPionTheta[0][0])",40,0.0,1.0,"particle","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[3]);

    draw.SetTitle("#pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==0");
    c1->Print(PrintName8[4]);

    draw.SetTitle("#pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==1");
    c1->Print(PrintName8[5]);

    draw.SetTitle("Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_endpos-NegPionPosEnd",100,-2000., 2000.,"particle","accum_level[0][1]>5 && NNegPion==1 && NME==0");
    c1->Print("/mnt/home/kskwarczynski/T2K/PlotOutputs/Accum5ZdistanceCut.pdf");
    
}
