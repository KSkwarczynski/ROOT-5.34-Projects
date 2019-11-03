#include <fstream>
#include <iostream>
#include "TMath.h"

void AntiMuMultiPiAnalysis()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/";
    TString FileNames0[6]={"Accum0MuonMom.pdf","Accum0MuonCosT.pdf","Accum0PiMinMom.pdf","Accum0PiMinCosT.pdf", "Accum0PiMinMom0ME.pdf", "Accum0PiMinMom1ME.pdf"};
    TString PrintName0[6];
    
    for(int i=0; i<6; i++)
    {
        PrintName0[i]=PathName+FileNames0[i];
    }
    
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
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>=0");
    c1->Print(PrintName0[0]);
    
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>=0");
    c1->Print(PrintName0[1]);
    
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>=0 && NNegPion==1");
    c1->Print(PrintName0[2]);
    
    draw.SetTitleX("TPC #pi^{-} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"NegPionTheta[0][0]",40,0.0,1.0,"particle","accum_level[0][1]>=0 && NNegPion==1");
    c1->Print(PrintName0[3]);

    draw.SetTitle("#pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>0 && NNegPion==1 && NME==0");
    c1->Print(PrintName0[4]);

    draw.SetTitle("#pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>0 && NNegPion==1 && NME==1");
    c1->Print(PrintName0[5]);
}
