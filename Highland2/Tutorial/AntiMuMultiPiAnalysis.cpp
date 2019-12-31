#include <fstream>
#include <iostream>
#include "TMath.h"

void AntiMuMultiPiAnalysis()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

  DrawingTools draw("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0.root",false);    

    Experiment exp("nd280");
    
    DataSample* R5mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5mc0", R5mc0);

    exp.AddSampleGroup("run5",run5);
    
    DataSample* R6bmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0.root");
     
    SampleGroup run6b("run6b");
    run6b.AddMCSample("R6bmc0", R6bmc0);
    
    exp.AddSampleGroup("run6b",run6b);
    
    DataSample* R6cmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6cAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6c("run6c");
    run6c.AddMCSample("R6cmc0", R6cmc0);
    
    exp.AddSampleGroup("run6c",run6c);
    
    DataSample* R6dmc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6dAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6d("run6d");
    run6d.AddMCSample("R6dmc0", R6dmc0);
    
    exp.AddSampleGroup("run6d",run6d);
    
    DataSample* R6emc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0.root");
    
    SampleGroup run6e("run6e");
    run6e.AddMCSample("R6emc0", R6emc0);
    
    exp.AddSampleGroup("run6e",run6e);
    
    DataSample* R7mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7AntiNumuMultiPiAccum0.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc0", R7mc0);
    
    exp.AddSampleGroup("run7",run7);

    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/WynikiOld/";
    TString FileNames8[22]={"Accum8MuonMom.pdf","Accum8MuonMomClear.pdf","Accum8MuonCosT.pdf","Accum8PiMinMom.pdf","Accum8PiMinCosT.pdf", "Accum8PiMinMom0ME.pdf", "Accum8PiMinMom1ME.pdf", "Accum8PiMinMom>1ME.pdf", "Accum6ZdistanceCut.pdf", "Accum7ZdistanceCut.pdf", "TH2Fmu.pdf", "TH2Fpi.pdf", "TH2FmuRangeXmom.pdf", "TH2FpiNegRangeXmom.pdf", "TH2FpiPosRangeXmom.pdf", "TH2FmuTrueTopAccum0.pdf", "TH2FmuTrueTopAccum8.pdf", "TH2FpiNegTrueTopAccum0.pdf", "TH2FpiNegTrueTopAccum8.pdf", "Accum7MuonEndPos.pdf","Accum7PiEndPos.pdf", "Accum8NuEnergy.pdf" };
    TString PrintName8[22];
    
    for(int i=0; i<22; i++)
    {
        PrintName8[i]=PathName+FileNames8[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
   
    draw.SetTitle("accum[0][1]>8 #mu^{+} momentum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[0]);
    
    draw.SetTitle("accum[0][1]>8 true #mu^{+} momentum");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8 && particle == -13");
    c1->Print(PrintName8[1]);
    
    draw.SetTitle("accum[0][1]>8 #mu^{+} cos#theta");
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>8");
    c1->Print(PrintName8[2]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} momentum");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"topology","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[3]);
    
    draw.SetTitle("accum[0][1]>8 #pi^{-} cos#theta");
    draw.SetTitleX("TPC #pi^{-} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"cos(NegPionTheta[0][0])",40,0.0,1.0,"topology","accum_level[0][1]>8 && NNegPion==1");
    c1->Print(PrintName8[4]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==0");
    c1->Print(PrintName8[5]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==1");
    c1->Print(PrintName8[6]);
    
    draw.SetTitle("accum[0][1]>8 #pi^{-} if >1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME>1");
    c1->Print(PrintName8[7]);
    
    draw.SetTitle("accum[0][1]>6 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][1]>6");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[8]);
    
    draw.SetTitle("accum[0][1]>7 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    //draw.SetRangeY(0, 1400);
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][1]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[9]);
    
    draw.SetTitle("#mu^{+} accum[0][1]>8 momXcos#theta");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>8","colz");
    //draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    c1->Print(PrintName8[10]);

    draw.SetTitle("#pi^{-} accum[0][1]>8 momXcos#theta");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>8","colz");
    c1->Print(PrintName8[11]);
    
    draw.SetTitle("#mu^{+} accum[0][1]>8 momXrange true particle");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate Z range");
    draw.Draw(exp,"selmu_endpos[2]:NegPionMom[0][0]", 50,0., 3000., 40,0.0, 3500, "all","accum_level[0][1]>8 && particle == -13","colz");
    c1->Print(PrintName8[12]);
    
    draw.SetTitle("#pi^{-} accum[0][1]>8 momXrange true particle");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate Z range");
    draw.Draw(exp,"NegPionPosEnd[0][2]:NegPionMom[0][0]", 50, 0., 3000., 40, 0.0, 3500, "all","accum_level[0][1]>8 && NegPionTId== -211","colz");
    c1->Print(PrintName8[13]);
    
    draw.SetTitle("#pi^{+} accum[0][1]>8 momXrange true particle");
    draw.SetTitleX("#pi^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{+} candidate Z range");
    draw.Draw(exp,"PosPionPosEnd[0][2]:PosPionMom[0][0]", 50,0., 3000., 40,0.0,3500, "all","accum_level[0][1]>8 && PosPionTId==211","colz");
    c1->Print(PrintName8[14]);
    
    draw.SetTitle("#mu^{+} accum[0][1]>0 momXcos#theta true topology");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    c1->Print(PrintName8[15]);
    
    draw.SetTitle("#mu^{+} accum[0][1]>8 momXcos#theta true topology");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>8 && topology==1","colz");
    c1->Print(PrintName8[16]);
    
    draw.SetTitle("#pi^{-} accum[0][1]>0 momXcos#theta true topology");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    c1->Print(PrintName8[17]);
    
    draw.SetTitle("#pi^{-} accum[0][1]>8 momXcos#theta true topology");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"cos(NegPionTheta[0][0]):NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>8 && topology==1","colz");
    c1->Print(PrintName8[18]);
     
    draw.SetTitle("#mu^{+} end pos accum[0][1]>7");
    draw.SetTitleX("#mu^{+} ending pos");
    draw.SetLegendPos("tc");
    draw.Draw(exp,"selmu_endpos[2]",40,-0., 3500.,"topology","accum_level[0][1]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[19]);
    
    draw.SetTitle("#pi^{-} end pos accum[0][1]>7");
    draw.SetTitleX("#pi^{-} ending pos");
    draw.SetLegendPos("tc");
    draw.Draw(exp,"NegPionPosEnd[0][2]",40, 0., 3500.,"topology","accum_level[0][1]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[20]);
    
    draw.SetTitle("accum[0][1]>8 #bar{#nu} true energy");
    draw.SetTitleX("#bar{#nu} energy [MeV]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"nu_trueE",20,0., 5000.,"topology","accum_level[0][1]>8");
    c1->Print(PrintName8[21]);
    
    TString FileNames0[7]={"Accum0MuonMom.pdf","Accum0MuonCosT.pdf","Accum0PiMinMom.pdf","Accum0PiMinCosT.pdf", "Accum0PiMinMom0ME.pdf", "Accum0PiMinMom1ME.pdf", "Accum0PiMinMom1ME.pdf"};
    TString PrintName0[7];
    
    for(int i=0; i<7; i++)
    {
        PrintName0[i]=PathName+FileNames0[i];
    }
    
    c1 = new TCanvas("c1"," ",10,10,800,600);
    draw.SetTitle("#mu^{+} momentum [MeV/c] accum[0][1]>=0");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>=0");
    c1->Print(PrintName0[0]);
    
    draw.SetTitle("#mu^{+} cos#theta accum[0][1]>=0");
    draw.SetTitleX("#mu^{+} candidate cos#theta");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_costheta",40,0.0,1.0,"particle","accum_level[0][1]>=0");
    c1->Print(PrintName0[1]);
    
    draw.SetTitle("#pi^{-} momentum [MeV/c] accum[0][1]>=0");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>=0 && NNegPion==1");
    c1->Print(PrintName0[2]);
    
    draw.SetTitle("#pi^{-} cos#theta accum[0][1]>=0");
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
    
    draw.SetTitle("#pi^{-} if >1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>0 && NNegPion==1 && NME>1");
    c1->Print(PrintName0[6]);
    
}
