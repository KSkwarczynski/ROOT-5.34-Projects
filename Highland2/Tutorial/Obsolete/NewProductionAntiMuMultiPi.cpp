#include <fstream>
#include <iostream>
#include "TMath.h"

void NewProductionAntiMuMultiPi()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("Run5tAntiNumuMultiPiAccum0_00.root",false);    

    Experiment exp("nd280");
 
    DataSample* R5tmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5tAntiNumuMultiPiAccum0_00.root");
    DataSample* R5tmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5tAntiNumuMultiPiAccum0_01.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5tmc000", R5tmc000);
    run5.AddMCSample("R5tmc001", R5tmc001);
    
    exp.AddSampleGroup("run5",run5);

    DataSample* R6tmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6tAntiNumuMultiPiAccum0_00.root");
    DataSample* R6tmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6tAntiNumuMultiPiAccum0_01.root");
    
    SampleGroup run6("run6");
    run6.AddMCSample("R6tmc000", R6tmc000);
    run6.AddMCSample("R6tmc001", R6tmc001);
    
    exp.AddSampleGroup("run6",run6);
    
    DataSample* R7tmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7tAntiNumuMultiPiAccum0_00.root");
    DataSample* R7tmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7tAntiNumuMultiPiAccum0_01.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R6tmc000", R6tmc000);
    run7.AddMCSample("R6tmc001", R6tmc001);
    
    exp.AddSampleGroup("run7",run7);
    
    
    
    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    TString PathName0="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/NewProduction/EfficiencyPlots/";
    TString FileNames;
    TString PrintName;
    
    for(int ik=0; ik<9; ik++)
    {
        FileNames=Form("EffciencyLeptonThetaAccum%dNew.pdf",ik);
        PrintName=PathName0+FileNames;
        
        draw.SetTitle(Form("accum[1]>%d for #mu^{+} cos#theta",ik));
        draw.SetTitleX("true #mu^{+} cos#theta");
        draw.DrawEff(exp,false,"truelepton_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName);
        
        FileNames=Form("EffciencyPiThetaAccum%dNew.pdf",ik);
        PrintName=PathName0+FileNames;
        
        draw.SetTitle(Form("accum[1]>%d #pi^{-} cos#theta",ik));
        draw.SetTitleX("true #pi^{-} cos#theta");
        draw.DrawEff(exp,false,"truepi_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName);
        
        FileNames=Form("EffciencyLeptonMomAccum%dNew.pdf",ik);
        PrintName=PathName0+FileNames;
        
        draw.SetTitle(Form("accum[1]>%d for #mu^{+} mom",ik));
        draw.SetTitleX("true #mu^{+} mom");
        draw.DrawEff(exp,false,"truelepton_mom",40,0.,3000.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName);
        
        FileNames=Form("EffciencyPiMomAccum%dNew.pdf",ik);
        PrintName=PathName0+FileNames;
        
        draw.SetTitle(Form("accum[1]>%d #pi^{-} mom",ik));
        draw.SetTitleX("true #pi^{-} mom");
        draw.DrawEff(exp,false,"truepi_mom",40,0.,3000.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName);
    }

    ///////////
        
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/NewProduction/";
    TString FileNames0[7]={"Accum0MuonMomNew.pdf","Accum0MuonCosTNew.pdf","Accum0PiMinMomNew.pdf","Accum0PiMinCosTNew.pdf", "Accum0PiMinMom0MENew.pdf", "Accum0PiMinMom1MENew.pdf", "Accum0PiMinMom1MENew.pdf"};
    TString PrintName0[7];
    
    for(int i=0; i<7; i++)
    {
        PrintName0[i]=PathName+FileNames0[i];
    }
    
    DrawingTools draw("Run5AntiNumuMultiPiAccum0_00.root",false);
    
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
    
    ///////////
    TString FileNames8[11]={"Accum8MuonMomNew.pdf","Accum8MuonCosTNew.pdf","Accum8PiMinMomNew.pdf","Accum8PiMinCosTNew.pdf", "Accum8PiMinMom0MENew.pdf", "Accum8PiMinMom1MENew.pdf", "Accum8PiMinMom>1MENew.pdf", "Accum6ZdistanceCutNew.pdf", "Accum7ZdistanceCutNew.pdf", "TH2FmuNew.pdf", "TH2FpiNew.pdf" };
    TString PrintName8[11];
    
    for(int i=0; i<11; i++)
    {
        PrintName8[i]=PathName+FileNames8[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
   
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

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 0 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==0");
    c1->Print(PrintName8[4]);

    draw.SetTitle("accum[0][1]>8 #pi^{-} if 1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME==1");
    c1->Print(PrintName8[5]);
    
    draw.SetTitle("accum[0][1]>8 #pi^{-} if >1 Michel Electrons");
    draw.SetTitleX("TPC #pi^{-} candidate momentum [MeV/c]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"NegPionMom[0][0]",20,0., 5000.,"particle","accum_level[0][1]>8 && NNegPion==1 && NME>1");
    c1->Print(PrintName8[6]);
    
    draw.SetTitle("accum[0][1]>6 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][1]>6");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[7]);
    
    draw.SetTitle("accum[0][1]>7 Z distance difference");
    draw.SetTitleX("Distance");
    draw.SetLegendPos("tl");
    draw.Draw(exp,"selmu_endpos[2]-NegPionPosEnd[0][2]",50,-3500., 3500.,"topology","accum_level[0][1]>7");  //[2] means Z rest is for X and Y
    c1->Print(PrintName8[8]);
    
    draw.SetTitle("#mu^{+} accum[0][1]>0 momXcos_theta");
    draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
    draw.SetTitleY("#mu^{+} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    c1->Print(PrintName8[9]);
    
    draw.SetTitle("#pi^{-} accum[0][1]>0 momXcos_theta");
    draw.SetTitleX("#pi^{-} candidate momentum [MeV/c]");
    draw.SetTitleY("#pi^{-} candidate cos#theta");
    draw.Draw(exp,"selmu_costheta:NegPionMom[0][0]", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    c1->Print(PrintName8[10]);
}
