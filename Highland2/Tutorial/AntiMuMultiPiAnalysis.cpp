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
    TString FileNames8[7]={"Accum8MuonMom.pdf","Accum8MuonCosT.pdf","Accum8PiMinMom.pdf","Accum8PiMinCosT.pdf", "Accum8PiMinMom0ME.pdf", "Accum8PiMinMom1ME.pdf", "Accum5ZdistanceCut.pdf"};
    TString PrintName8[7];
    
    for(int i=0; i<7; i++)
    {
        PrintName8[i]=PathName+FileNames8[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
    /*
    draw.SetTitle("accum[0][1]>8 #mu^{+} moementum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[0]);
    
    draw.SetTitle("accum[0][1]>8 #mu^{+} cos#theta");
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[1]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} momentum");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[2]);
    
    draw.SetTitle("accum[0][1]>8 #pi^{-} cos#theta");
    draw.SetTitleX("TPC #pi^{-} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"cos(NegPionTheta[0][0])",40,0.0,1.0,"particle","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[3]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==0");
    c1->Print(PrintName8[4]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==1");
    c1->Print(PrintName8[5]);
*/
    draw.SetTitle("accum[0][1]>7 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3000., 3000.,"topology","accum_level[0][1]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[6]);
    draw.PrintPurities(exp,"topology", "accum_level[0][1]>7 && selmu_endpos[2]-NegPionPosEnd[0][2]>-500");

    
    //Dla >5   61.10383 % (764.94737 events) 
    //Dla >-5  59.583405 % (799.59239 events)
    //Dla >-10 59.56251 % (800.61084 events)
    //Dla >-15 59.437125 % (800.61084 events)
    //Dla >-20 59.385815 % (800.61084 events)
    //Dla >-30 59.10334 % (800.61084 events)
    //Dla >-100 58.336437 % (806.90315 events)
    //Dla >-200 57.237717 % (817.05121 events)
    //Dla >-500 54.617006 % (828.18823 events)
}
