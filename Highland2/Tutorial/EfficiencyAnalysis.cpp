#include <fstream>
#include <iostream>
#include "TMath.h"

void EfficiencyAnalysis()
{
    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("Run5AntiNumuMultiPiAccum0_00.root",false);    

    Experiment exp("nd280");
    
    DataSample* R5mc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0_00.root");
    DataSample* R5mc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0_01.root");
    DataSample* R5mc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0_02.root");
    DataSample* R5mc003 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0_03.root");
    DataSample* R5mc004 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0_04.root");
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5mc000", R5mc000);
    run5.AddMCSample("R5mc001", R5mc001);
    run5.AddMCSample("R5mc002", R5mc002);
    run5.AddMCSample("R5mc003", R5mc003);
    run5.AddMCSample("R5mc004", R5mc004);

    exp.AddSampleGroup("run5",run5);
    
    DataSample* R6bmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_00.root");
    DataSample* R6bmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_01.root");
    DataSample* R6bmc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_02.root");
    DataSample* R6bmc003 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_03.root");
    DataSample* R6bmc004 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_04.root");
    DataSample* R6bmc005 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_05.root");
    DataSample* R6bmc006 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_06.root");
    DataSample* R6bmc007 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6bAntiNumuMultiPiAccum0_07.root");
     
    SampleGroup run6b("run6b");
    run6b.AddMCSample("R6bmc000", R6bmc000);
    run6b.AddMCSample("R6bmc001", R6bmc001);
    run6b.AddMCSample("R6bmc002", R6bmc002);
    run6b.AddMCSample("R6bmc003", R6bmc003);
    run6b.AddMCSample("R6bmc004", R6bmc004);
    run6b.AddMCSample("R6bmc005", R6bmc005);
    run6b.AddMCSample("R6bmc006", R6bmc006);
    run6b.AddMCSample("R6bmc007", R6bmc007);
    
    exp.AddSampleGroup("run6b",run6b);
    
    DataSample* R6cmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6cAntiNumuMultiPiAccum0_00.root");
    DataSample* R6cmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6cAntiNumuMultiPiAccum0_01.root");
    DataSample* R6cmc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6cAntiNumuMultiPiAccum0_02.root");
    
    SampleGroup run6c("run6c");
    run6c.AddMCSample("R6cmc000", R6cmc000);
    run6c.AddMCSample("R6cmc001", R6cmc001);
    run6c.AddMCSample("R6cmc002", R6cmc002);
    
    exp.AddSampleGroup("run6c",run6c);
    
    DataSample* R6dmc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6dAntiNumuMultiPiAccum0_00.root");
    DataSample* R6dmc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6dAntiNumuMultiPiAccum0_01.root");
    DataSample* R6dmc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6dAntiNumuMultiPiAccum0_02.root");
    DataSample* R6dmc003 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6dAntiNumuMultiPiAccum0_03.root");
    
    SampleGroup run6d("run6d");
    run6d.AddMCSample("R6dmc000", R6dmc000);
    run6d.AddMCSample("R6dmc001", R6dmc001);
    run6d.AddMCSample("R6dmc002", R6dmc002);
    run6d.AddMCSample("R6dmc003", R6dmc003);
    
    exp.AddSampleGroup("run6d",run6d);
    
    DataSample* R6emc000 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0_00.root");
    DataSample* R6emc001 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0_01.root");
    DataSample* R6emc002 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0_02.root");
    DataSample* R6emc003 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0_03.root");
    DataSample* R6emc004 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run6eAntiNumuMultiPiAccum0_04.root");
    
    SampleGroup run6e("run6e");
    run6e.AddMCSample("R6emc000", R6emc000);
    run6e.AddMCSample("R6emc001", R6emc001);
    run6e.AddMCSample("R6emc002", R6emc002);
    run6e.AddMCSample("R6emc003", R6emc003);
    run6e.AddMCSample("R6emc004", R6emc004);
    
    exp.AddSampleGroup("run6e",run6e);
    
    DataSample* R7mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7AntiNumuMultiPiAccum0.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc0", R7mc0);
    
    exp.AddSampleGroup("run7",run7);

    c1 = new TCanvas("c1"," ",10,10,800,600);
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/WynikiOld/EfficiencyPlots/";
    TString FileNames0;
    TString PrintName0;
    
    for(int ik=0; ik<9; ik++)
    {
        FileNames0=Form("EffciencyLeptonThetaAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;

    
        draw.SetTitle(Form("accum[1]>%d for #mu^{+} cos#theta",ik));
        draw.SetTitleX("true #mu^{+} cos#theta");
        draw.DrawEff(exp,false,"truelepton_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyPiThetaAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[1]>%d #pi^{-} cos#theta",ik));
        draw.SetTitleX("true #pi^{-} cos#theta");
        draw.DrawEff(exp,false,"truepi_costheta",40,0.,1.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyLeptonMomAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[1]>%d for #mu^{+} mom",ik));
        draw.SetTitleX("true #mu^{+} mom");
        draw.DrawEff(exp,false,"truelepton_mom",40,0.,3000.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
        
        FileNames0=Form("EffciencyPiMomAccum%d.pdf",ik);
        PrintName0=PathName+FileNames0;
        
        draw.SetTitle(Form("accum[1]>%d #pi^{-} mom",ik));
        draw.SetTitleX("true #pi^{-} mom");
        draw.DrawEff(exp,false,"truepi_mom",40,0.,3000.,Form("accum_level[1]>%d",ik),"topology==1","","","");
        c1->Print(PrintName0);
    }

}
