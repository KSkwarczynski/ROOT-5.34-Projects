#include <fstream>
#include <iostream>
#include "TMath.h"

void RecNuEnMultiPi()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    TString Directory ="/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/";
    
    DrawingTools draw(Form("%sProd6tRun5AntiNuMultiPiAccum5.root",Directory.Data()), false);
    Experiment exp("nd280");
    
    DataSample* R5mc5 = new DataSample(Form("%sProd6tRun5AntiNuMultiPiAccum5.root",Directory.Data()));
    
    SampleGroup run5("run5");
    run5.AddMCSample("R5mc5", R5mc5);

    exp.AddSampleGroup("run5",run5);
    
    DataSample* R6mc5 = new DataSample(Form("%sProd6tRun6AntiNuMultiPiAccum5.root",Directory.Data()));
    
    SampleGroup run6("run6");
    run6.AddMCSample("R6mc5", R6mc5);
    
    exp.AddSampleGroup("run6",run6);
    
    DataSample* R7mc5 = new DataSample(Form("%sProd6tRun7AntiNuMultiPiAccum5.root",Directory.Data()));
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc5", R7mc5);
    
    exp.AddSampleGroup("run7",run7);
    
    const int PlotNumber=5;
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/MyVariableNuEnergy/";
    TString FileNames[PlotNumber]={"MultiPiRecEnTopology.pdf", "MultiPiRecEnParticle.pdf", "MultiPiRecEnReaction.pdf", "MultiPiRecVsTrue.pdf", "MultiPiRecVsTrueTopTrue.pdf" };
    TString PrintName[PlotNumber];
    
    for(int i=0; i<PlotNumber; i++)
    {
        PrintName[i]=PathName+FileNames[i];
    }
    c1 = new TCanvas("c1"," ",10,10,800,600);
   
    draw.SetTitle("accum[0][1]>8 #bar{#nu} rec energy");
    draw.SetTitleX("#bar{#nu} reconstructed energy [MeV]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"nuEnergy",50,0., 6000.,"topology","accum_level[0][1]>8");
    c1->Print(PrintName[0]);
    
    draw.SetTitle("accum[0][1]>8 #bar{#nu} rec energy");
    draw.SetTitleX("#bar{#nu} reconstructed energy [MeV]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"nuEnergy",50,0., 6000.,"particle","accum_level[0][1]>8");
    c1->Print(PrintName[1]);
    
    draw.SetTitle("accum[0][1]>8 #bar{#nu} rec energy");
    draw.SetTitleX("#bar{#nu} reconstructed energy [MeV]");
    draw.SetLegendPos("tr");
    draw.Draw(exp,"nuEnergy",50,0., 6000.,"reaction","accum_level[0][1]>8");
    c1->Print(PrintName[2]);
    
    draw.SetTitle("#bar{#nu} rec energy vs true energy accum[0][1]>8");
    draw.SetTitleX("#bar{#nu} reconstructed energy");
    draw.SetTitleY("#bar{#nu} true energy");
    draw.Draw(exp,"nu_trueE:nuEnergy", 50,0., 6000., 50,0., 6000., "all","accum_level[0][1]>8 " ,"colz");
    c1->Print(PrintName[3]);
    
    draw.SetTitle("#bar{#nu} rec energy vs true energy accum[0][1]>8 true topology");
    draw.SetTitleX("#bar{#nu} reconstructed energy");
    draw.SetTitleY("#bar{#nu} true energy");
    draw.Draw(exp,"nu_trueE:nuEnergy", 50,0., 6000., 50,0., 6000., "all","accum_level[0][1]>8 && topology==1" ,"colz");
    c1->Print(PrintName[4]);
    
    
}
