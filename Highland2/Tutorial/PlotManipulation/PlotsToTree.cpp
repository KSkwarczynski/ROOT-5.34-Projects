#include <fstream>
#include <iostream>
#include "TMath.h"
#include "TDirectory.h"

void PlotsToTree()
{

    DrawingTools draw("Run7AntiNumuMultiPiAccum0.root",false);    

    Experiment exp("nd280");
    
    DataSample* R7mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7AntiNumuMultiPiAccum0.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc0", R7mc0);
    
    exp.AddSampleGroup("run7",run7);
    
    TFile *fileout = new TFile("/mnt/home/kskwarczynski/T2K/PlotOutputs/FirstCrosscheck/WynikiOld/histograms.root","RECREATE");
    //TDirectory *Directory = fileout->mkdir("Directory"); // save to directorys
    //Directory -> cd();
    
    Canvas1 = new TCanvas("Canvas1"," ",10,10,800,600);
     
    draw.Draw(exp,"selmu_mom",20,0., 5000.,"particle","accum_level[0][1]>8");
    
    Canvas1->Write();
    
    delete Canvas1;
    
    Canvas2 = new TCanvas("Canvas2"," ",10,10,800,600);
    
    draw.DrawEff(exp,false,"truelepton_costheta",40,0.,1.,"accum_level[1]>8","topology==1","","","");
    
    Canvas2->Write();
    delete Canvas2;
    
    Canvas3 = new TCanvas("Canvas3"," ",10,10,800,600);
    
    draw.DrawEff(exp,false,"truepi_costheta",40,0.,1.,"accum_level[1]>8","topology==1","","","");
    
    Canvas3->Write();
    delete Canvas3;
    
    Canvas4 = new TCanvas("Canvas4"," ",10,10,800,600);
    
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>8 && topology==1","colz");
    Canvas4->Write();
    delete Canvas4;
    
    Canvas5 = new TCanvas("Canvas5"," ",10,10,800,600);
    
    draw.Draw(exp,"selmu_costheta:selmu_mom", 50,0., 3000., 50,0.0, 1.0, "all","accum_level[0][1]>0 && topology==1","colz");
    Canvas5->Write();
    delete Canvas5;
    
    fileout->Close();

}
