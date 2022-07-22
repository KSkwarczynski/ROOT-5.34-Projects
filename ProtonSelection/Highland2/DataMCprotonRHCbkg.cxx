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

void DataMCprotonRHCbkg()
{
    //gStyle->SetOptStat(0);
    //gStyle->SetPadColor(0);
    //gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/Run5MC.root");

    Experiment exp("nd280");

    DataSample* R5Mc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/Run5MC.root");
    DataSample* R5MC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/SandRHC.root");
    DataSample* R5Data = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/DataRun5.root");
        
    SampleGroup run5("run5");
    run5.AddDataSample(R5Data);
    run5.AddMCSample("R5Mc", R5Mc);
    run5.AddMCSample("R5MC_sand", R5MC_sand);

    exp.AddSampleGroup("run5",run5);

    
    DataSample* R6Mc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/Run6MC.root");
    DataSample* R6MC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/SandRHC.root");
    DataSample* R6Data = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/DataRun6.root");
        
    SampleGroup run6("run6");
    run6.AddDataSample(R6Data);
    run6.AddMCSample("R6Mc", R6Mc);
    run6.AddMCSample("R6MC_sand", R6MC_sand);

    exp.AddSampleGroup("run6",run6);
    
    
    DataSample* R7Mc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/Run7MC.root");
    DataSample* R7MC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/SandRHC.root");
    DataSample* R7Data = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/DataRun7.root");
        
    SampleGroup run7("run7");
    run7.AddDataSample(R7Data);
    run7.AddMCSample("R7Mc", R7Mc);
    run7.AddMCSample("R7MC_sand", R7MC_sand);

    exp.AddSampleGroup("run7",run7);
    
    
    
    DataSample* R9Mc = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/Run9MC.root");
    DataSample* R9MC_sand = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/SandRHC.root");
    DataSample* R9Data = new DataSample("/mnt/home/share/t2k/kskwarczynski/HighlandOutput/OutputRHCbkg/DataRun9.root");
        
    SampleGroup run9("run9");
    run9.AddDataSample(R9Data);
    run9.AddMCSample("R9Mc", R7Mc);
    run9.AddMCSample("R9MC_sand", R9MC_sand);

    exp.AddSampleGroup("run9",run9);
    
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->Print("ProtonSelecPlotsNew.pdf[", "pdf");
    

    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi RHC BKG FGD1");
    draw.SetTitleX("Reconstructed #mu momentum");
    draw.Draw(exp, "selmu_mom", 40., 0., 4000., "reaction", "accum_level[0][0][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0p RHC BKG FGD1");
    draw.SetTitleX("Reconstructed #mu momentum");
    draw.Draw(exp, "selmu_mom", 40., 0., 4000., "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 0 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("Reconstructed #mu momentum");
    draw.Draw(exp, "selmu_mom", 40., 0., 4000., "reaction", "accum_level[0][0][0]>7 && (nProtonsFGD + nProtonsTPC) > 0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0#pi RHC BKG FGD1");
    draw.SetTitleX("Reconstructed Cos#theta_{#mu}");
    draw.Draw(exp, "selmu_costheta", 20., 0.2, 1, "reaction", "accum_level[0][0][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0#pi-0p RHC BKG FGD1");
    draw.SetTitleX("Reconstructed Cos#theta_{#mu}");
    draw.Draw(exp, "selmu_costheta", 20., 0.2, 1, "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 0 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tl");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("Reconstructed Cos#theta_{#mu}");
    draw.Draw(exp, "selmu_costheta", 20., 0.2, 1, "reaction", "accum_level[0][0][0]>7 && (nProtonsFGD + nProtonsTPC) > 0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-0p RHC BKG FGD1");
    draw.SetTitleX("True Q^{2}");
    draw.Draw(exp, "true_Q2/1000", 20., 0., 2000, "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 0 && nProtonsTPC==0", "");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("True Q^{2}");
    draw.Draw(exp, "true_Q2/1000", 20., 0., 2000, "reaction", "accum_level[0][0][0]>7 && (nProtonsFGD + nProtonsTPC) > 0", "");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    

    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi RHC BKG FGD1");
    draw.SetTitleX("Number of reconstructer TPC protons");
    draw.Draw(exp, "nProtonsTPC", 5., -0.5, 4.5, "reaction", "accum_level[0][0][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi RHC BKG FGD1");
    draw.SetTitleX("Number of reconstructer FGD protons");
    draw.Draw(exp, "nProtonsFGD", 5., -0.5, 4.5, "reaction", "accum_level[0][0][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");

    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi RHC BKG FGD2");
    draw.SetTitleX("Number of reconstructer TPC protons");
    draw.Draw(exp, "nProtonsTPC", 5., -0.5, 4.5, "fgd2reaction", "accum_level[0][1][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi RHC BKG FGD2");
    draw.SetTitleX("Number of reconstructer FGD protons");
    draw.Draw(exp, "nProtonsFGD", 5., -0.5, 4.5, "fgd2reaction", "accum_level[0][1][0]>7");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("reconstructed FGD proton momentum");
    draw.Draw(exp, "FGDProtMom", 20., 0., 2000., "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 1 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("reconstructed TPC proton momentum");
    draw.Draw(exp, "TPCProtMom", 20., 0., 2000., "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 0 && nProtonsTPC==1");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("reconstructed FGD proton momentum");
    draw.Draw(exp, "FGDProtMom", 20., 0., 2000., "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 1 && nProtonsTPC==0");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    draw.SetLegendPos("tr");
    draw.SetTitle("CC0#pi-Np RHC BKG FGD1");
    draw.SetTitleX("reconstructed TPC proton momentum");
    draw.Draw(exp, "TPCProtMom", 20., 0., 2000., "reaction", "accum_level[0][0][0]>7 && nProtonsFGD == 0 && nProtonsTPC==1");
    c1->Print("ProtonSelecPlotsNew.pdf", "pdf");
    
    c1->Print("ProtonSelecPlotsNew.pdf]", "pdf");
    delete c1;
    
    
    
    
    
    draw.PrintPurities(exp,"reaction", "accum_level[0][0][0]>7");
    
    draw.PrintPurities(exp,"reaction", "accum_level[0][0][0]>7 && (nProtonsFGD + nProtonsTPC) > 0");
    
    draw.PrintPurities(exp,"reaction", "accum_level[0][0][0]>7 && (nProtonsFGD + nProtonsTPC) == 0");
}
