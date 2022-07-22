#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "TObjArray.h"
#include "TChain.h"
#include "TFile.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TGraphErrors.h"
#include "TVectorD.h"
#include "TColor.h"
#include "TMath.h"

void DataMCproton()
{
    //gStyle->SetOptStat(0);
    //gStyle->SetPadColor(0);
    //gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run2aMC.root");

    Experiment exp("nd280");


    DataSample* R2aMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run2aMC.root");
    DataSample* R2aMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R2aData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun2a.root");
        
    SampleGroup run2a("run2a");
    run2a.AddDataSample(R2aData);
    run2a.AddMCSample("R2aMc", R2aMc);
    run2a.AddMCSample("R2aMC_sand", R2aMC_sand);

    
    exp.AddSampleGroup("run2a",run2a);

    DataSample* R2wMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run2wMC.root");
    DataSample* R2wMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R2wData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun2w.root");
        
    SampleGroup run2w("run2w");
    run2w.AddDataSample(R2wData);
    run2w.AddMCSample("R2wMc", R2wMc);
    run2w.AddMCSample("R2wMC_sand", R2wMC_sand);

    
    exp.AddSampleGroup("run2w",run2w);
    
    DataSample* R3Mc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run3MC.root");
    DataSample* R3MC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R3Data = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun3.root");
        
    SampleGroup run3("run3");
    run3.AddDataSample(R3Data);
    run3.AddMCSample("R3Mc", R3Mc);
    run3.AddMCSample("R3MC_sand", R3MC_sand);

    
    exp.AddSampleGroup("run3",run3);
 
    DataSample* R4aMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run4aMC.root");
    DataSample* R4aMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R4aData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun4a.root");
        
    SampleGroup run4a("run4a");
    run4a.AddDataSample(R4aData);
    run4a.AddMCSample("R4aMc", R4aMc);
    run4a.AddMCSample("R4aMC_sand", R4aMC_sand);

    
    exp.AddSampleGroup("run4a",run4a);
    
    DataSample* R4wMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run4wMC.root");
    DataSample* R4wMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R4wData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun4w.root");
        
    
    SampleGroup run4w("run4w");
    run4w.AddDataSample(R4wData);
    run4w.AddMCSample("R4aMc", R4aMc);
    run4w.AddMCSample("R4wMC_sand", R4wMC_sand);
    
    exp.AddSampleGroup("run4w",run4w);
    
    DataSample* R8aMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run8aMC.root");
    DataSample* R8aMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R8aData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun8a.root");
        
    SampleGroup run8a("run8a");
    run8a.AddDataSample(R8aData);
    run8a.AddMCSample("R8aMc", R8aMc);
    run8a.AddMCSample("R8aMC_sand", R8aMC_sand);

    
    exp.AddSampleGroup("run8a",run8a);
    
    DataSample* R8wMc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/Run8wMC.root");
    DataSample* R8wMC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/SandFHC.root");
    DataSample* R8wData = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/Output/DataRun8w.root");
        
    SampleGroup run8w("run8w");
    run8w.AddDataSample(R8wData);
    run8w.AddMCSample("R8wMc", R8aMc);
    run8w.AddMCSample("R8wMC_sand", R8wMC_sand);
    
    exp.AddSampleGroup("run8w",run8w);
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->Print("ProtonSelecPlotsNew.pdf[", "pdf");
    

    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0#gamma FGD1");
    draw.SetTitleX("Number of reconstructer TPC protons");
    draw.Draw(exp, "nProtonsTPC", 5., 0., 5., "reaction", "accum_level[0][0][2]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0#gamma FGD1");
    draw.SetTitleX("Number of reconstructer FGD protons");
    draw.Draw(exp, "nProtonsFGD", 5., 0., 5., "reaction", "accum_level[0][0][2]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0#gamma FGD2");
    draw.SetTitleX("Number of reconstructer TPC protons");
    draw.Draw(exp, "nProtonsTPC", 5., 0., 5., "fgd2reaction", "accum_level[0][1][2]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0#gamma FGD2");
    draw.SetTitleX("Number of reconstructer FGD protons");
    draw.Draw(exp, "nProtonsFGD", 5., 0., 5., "fgd2reaction", "accum_level[0][1][2]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD1");
    draw.SetTitleX("reconstructed TPC proton momentum");
    draw.Draw(exp, "sel_prot_mom_vertex",20,0., 2000, "reaction", "accum_level[0][0][2]>8 & nProtonsFGD == 0 && nProtonsTPC==1");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD1");
    draw.SetTitleX("reconstructed FGD proton momentum");
    draw.Draw(exp, "sel_prot_mom_vertex",20,0., 2000, "reaction", "accum_level[0][0][2]>8 & nProtonsFGD == 1 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
        draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD2");
    draw.SetTitleX("reconstructed TPC proton momentum");
    draw.Draw(exp, "sel_prot_mom_vertex",20,0., 2000, "fgd2reaction", "accum_level[0][1][2]>8 & nProtonsFGD == 0 && nProtonsTPC==1");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
        draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD2");
    draw.SetTitleX("reconstructed FGD proton momentum");
    draw.Draw(exp, "sel_prot_mom_vertex",20,0., 2000, "fgd2reaction", "accum_level[0][1][2]>8 & nProtonsFGD == 1 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
    double Blarb[13] = { 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.90, 0.92, 0.94, 0.96, 0.98, 0.99, 1.}
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD1");
    draw.SetTitleX("Proton candidate momentum [MeV/c]");
    draw.Draw(exp, "sel_prot_mom_vertex[0]", 20., 0., 1400., "reaction", "accum_level[0][0][2]>8");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");

    draw.SetLegendPos("tl");
    draw.SetTitle("CC0Pi-Np-0#gamma FGD1");
    draw.SetTitleX("Proton candidate Cos#thete");
    draw.Draw(exp, "sel_prot_dir_vertex[0][2]", 12., Blarb, "reaction", "accum_level[0][0][2]>8");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");

    draw.SetLegendPos("tl");
    draw.SetTitle("CC0#pi-Np-0#gamma FGD1");
    draw.SetTitleX("Proton candidate Cos#{thete}");
    draw.Draw(exp, "sel_prot_dir_vertex[0][2]", 12, Blarb, "all", "accum_level[0][0][2]>8");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    c1->Print("ProtonSelecPlotsNew.pdf]", "pdf");
    delete c1;
}
