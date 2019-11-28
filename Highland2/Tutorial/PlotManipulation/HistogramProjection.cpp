#include <fstream>
#include <iostream>

void HistogramProjection()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    DrawingTools draw("Run7AntiNumuMultiPiAccum0.root",false);    

    Experiment exp("nd280");
    
    DataSample* R7mc0 = new DataSample("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run7AntiNumuMultiPiAccum0.root");
    
    SampleGroup run7("run7");
    run7.AddMCSample("R7mc0", R7mc0);
    
    exp.AddSampleGroup("run7",run7);

    TTree *tree=(TTree*) R7mc0->GetTree("default");
    
    TH1F *Hselmu = new TH1F("Hselmu", "CC1pi tittle", 20, 0., 5000);
    
    tree->Project(Hselmu->GetName(),"selmu_mom", "accum_level[0][1]>8");
    
    Hselmu->Draw();
    
    
    //float nnomi=Hselmu->GetBinContent(i+1);
    //TString nn[4]={"CC","CC0pi","CC1pi","CCOth"}; 
    //int ih=1;
    //Hselmu->SetName(Form("mom_h1_%s",nn[ih]));
    //Hselmu->SetNameTitle(Hselmu->GetName(),Form("mom_h1_%s",nn[ih]));

}
