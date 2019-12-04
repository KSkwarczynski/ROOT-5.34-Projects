#include <fstream>
#include <iostream>
#include "TMath.h"

void CC1PiXsecAnalysis()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("XsecRun5AntiNumuMultiPiAccum5_00.root",false);
    
    Experiment exp("nd280");

    DataSample* R5mc500 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum5_00.root");
    DataSample* R5mc501 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum5_01.root");
    DataSample* R5mc502 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum5_02.root");
    DataSample* R5mc503 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum5_03.root");
    DataSample* R5mc504 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun5AntiNumuMultiPiAccum5_04.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5mc500", R5mc500);
    run5.AddMCSample("R5mc501", R5mc501);
    run5.AddMCSample("R5mc502", R5mc502);
    run5.AddMCSample("R5mc503", R5mc503);
    run5.AddMCSample("R5mc504", R5mc504);

    exp.AddSampleGroup("run5",run5);
    
    DataSample* R6bmc500 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_00.root");
    DataSample* R6bmc501 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_01.root");
    DataSample* R6bmc502 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_02.root");
    DataSample* R6bmc503 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_03.root");
    DataSample* R6bmc504 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_04.root");
    DataSample* R6bmc505 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_05.root");
    DataSample* R6bmc506 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_06.root");
    DataSample* R6bmc507 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6bAntiNumuMultiPiAccum5_07.root");
    
    SampleGroup run6b("run6b");
    run6b.AddMCSample("R6bmc500", R6bmc500);
    run6b.AddMCSample("R6bmc501", R6bmc501);
    run6b.AddMCSample("R6bmc502", R6bmc502);
    run6b.AddMCSample("R6bmc503", R6bmc503);
    run6b.AddMCSample("R6bmc504", R6bmc504);
    run6b.AddMCSample("R6bmc505", R6bmc505);
    run6b.AddMCSample("R6bmc506", R6bmc506);
    run6b.AddMCSample("R6bmc507", R6bmc507);
    
    exp.AddSampleGroup("run6b",run6b);
    
    DataSample* R6cmc5 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6cAntiNumuMultiPiAccum5.root");
    
    SampleGroup run6c("run6c");
    run6c.AddMCSample("R6cmc5", R6cmc5);
    
    exp.AddSampleGroup("run6c",run6c);
    
    DataSample* R6dmc5 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6dAntiNumuMultiPiAccum5.root");
    
    SampleGroup run6d("run6d");
    run6d.AddMCSample("R6dmc5", R6dmc5);
    
    exp.AddSampleGroup("run6d",run6d);
    
    DataSample* R6emc5 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun6eAntiNumuMultiPiAccum5.root");
    
    SampleGroup run6e("run6e");
    run6e.AddMCSample("R6emc5", R6emc5);
    
    exp.AddSampleGroup("run6e",run6e);
    
    DataSample* R7mc5 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCC1piXsecAnalysis/v0r2/Linux-x86_64/XsecRun7AntiNumuMultiPiAccum5.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc5", R7mc5);
    
    exp.AddSampleGroup("run7",run7);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/CC1piXsec/";
    TString FileNames8[22]={"Accum8XMuonMom.pdf", "Accum8XMuonMomClear.pdf", "Accum8XMuonCosT.pdf","Accum8XPiMinMom.pdf","Accum8XPiMinCosT.pdf", "Accum8XPiMinMom0ME.pdf", "Accum8XPiMinMom1ME.pdf", "Accum8XPiMinMom>1ME.pdf", "Accum6XZdistanceCut.pdf", "Accum7XZdistanceCut.pdf", "TH2FmuX.pdf", "TH2FpiX.pdf", "TH2FmuRangeXmomX.pdf", "TH2FpiMinRangeXmomX.pdf", "TH2FpiPosRangeXmomX.pdf", "TH2FmuTrueTopAccum0X.pdf", "TH2FmuTrueTopAccum8X.pdf", "TH2FpiNegTrueTopAccum0X.pdf", "TH2FpiNegTrueTopAccum8X.pdf" , "Accum7XMuonEndPos.pdf","Accum7XPiEndPos.pdf", "Accum8XNuEnergy.pdf" };
    TString PrintName8[22];
    
    for(int i=0; i<22; i++)
    {
        PrintName8[i]=PathName+FileNames8[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    draw.SetTitle("accum[0][0]>8 #mu^{+} momentum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][0]>8");
    c1->Print(PrintName8[0]);
    
    draw.SetTitle("accum[0][0]>8 true #mu^{+} momentum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][0]>8 && particle == -13");
    c1->Print(PrintName8[1]);
    
    draw.SetTitle("accum[0][0]>8 #mu^{+} cos#theta");
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][0]>8");
    c1->Print(PrintName8[2]);

    draw.SetTitle("accum[0][0]>8 #pi^{-} momentum");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"topology","accum_level[0][0]>8 && NNegPion==1");
    c1->Print(PrintName8[3]);
    
    draw.SetTitle("accum[0][0]>8 #pi^{-} cos#theta");
    draw.SetTitleX("TPC #pi^{-} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"cos(NegPionTheta[0][0])",40,0.0,1.0,"topology","accum_level[0][0]>8 && NNegPion==1");
    c1->Print(PrintName8[4]);

    draw.SetTitle("accum[0][0]>8 #pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][0]>8 && NNegPion==1 && NME==0");
    c1->Print(PrintName8[5]);

    draw.SetTitle("accum[0][0]>8 #pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][0]>8 && NNegPion==1 && NME==1");
    c1->Print(PrintName8[6]);
    
    draw.SetTitle("accum[0][0]>8 #pi^{-} if >1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][0]>8 && NNegPion==1 && NME>1");
    c1->Print(PrintName8[7]);
    
    draw.SetTitle("accum[0][0]>6 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][0]>6");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[8]);
    
    draw.SetTitle("accum[0][0]>7 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    //draw.SetRangeY(0, 1400);
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][0]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[9]);
    
    draw.SetTitle("#mu^{+} accum[0][0]>8 momXcos#theta");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50, 0.0, 1.0, "all","accum_level[0][0]>8","colz");
    c1->Print(PrintName8[10]);
    
    draw.SetTitle("#pi^{-} accum[0][0]>8 momXcos#theta");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>8","colz");
    //draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>0 && topology==1","colz");
    c1->Print(PrintName8[11]);
    
    draw.SetTitle("#mu^{+} accum[0][0]>8 momXrange true particle");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate range");
    draw.Draw(exp,"selmu_endpos[2]:NegPionMom[0][0]", 50,0., 3000., 40,0.0, 3500, "all","accum_level[0][0]>8 && particle == -13","colz");
    c1->Print(PrintName8[12]);
    
    draw.SetTitle("#pi^{-} accum[0][0]>8 momXrange true particle");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate range");
    draw.Draw(exp,"NegPionPosEnd[0][2]:NegPionMom[0][0]", 50, 0., 3000., 40, 0.0, 3500, "all","accum_level[0][0]>8 && NegPionTId == -211","colz");
    c1->Print(PrintName8[13]);
    
    draw.SetTitle("#pi^{+} accum[0][0]>8 momXrange true particle");
    draw.SetTitleX("#pi^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{+} candidate Z range");
    draw.Draw(exp,"PosPionPosEnd[0][2]:PosPionMom[0][0]", 50,0., 3000., 40,0.0, 3500, "all","accum_level[0][0]>8 && PosPionTId == +211","colz");
    c1->Print(PrintName8[14]);
    
    draw.SetTitle("#mu^{+} accum[0][0]>0 momXcos#theta true topology");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>0 && topology==1","colz");
    c1->Print(PrintName8[15]);
    
    draw.SetTitle("#mu^{+} accum[0][0]>8 momXcos#theta true topology");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>8 && topology==1","colz");
    c1->Print(PrintName8[16]);
    
    draw.SetTitle("#pi^{-} accum[0][0]>0 momXcos#theta true topology");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>0 && topology==1","colz");
    c1->Print(PrintName8[17]);
    
    draw.SetTitle("#pi^{-} accum[0][0]>8 momXcos#theta true topology");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][0]>8 && topology==1","colz");
    c1->Print(PrintName8[18]);
    
    draw.SetTitle("#mu^{+} end pos accum[0][0]>7");
    draw.SetTitleX("#mu^{+} ending pos");
    draw.SetLegendPos("tc");
    draw.Draw(exp,"selmu_endpos[2]",40,-0., 3500.,"topology","accum_level[0][0]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[19]);
    
    draw.SetTitle("#pi^{-} end pos accum[0][0]>7");
    draw.SetTitleX("#pi^{-} ending pos");
    draw.SetLegendPos("tc");
    draw.Draw(exp,"NegPionPosEnd[0][2]",40, 0., 3500.,"topology","accum_level[0][0]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[20]);
    
    draw.SetTitle("accum[0][0]>8 #bar{#nu} true energy");
    draw.SetTitleX("#bar{#nu} energy [MeV]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"nu_trueE",20,0., 5000.,"topology","accum_level[0][0]>8");
    c1->Print(PrintName8[21]);
    
    
    /////////////////////DODATKOWE FUNKCJONALNOSCI!!!!!!!!!
    //topology_bkg_split
    //draw.PrintPurities(exp,"topology", "accum_level[0][0]>7 && selmu_endpos[2]-NegPionPosEnd[0][2]>-100");
}
