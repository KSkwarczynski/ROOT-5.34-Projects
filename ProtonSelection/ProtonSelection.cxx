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

void ProtonSelection()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6T.root",false);
    
    Experiment exp("nd280");

    DataSample* R4mP6T = new DataSample("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6T.root");
    
    SampleGroup run4("run4");
    run4.AddMCSample("R4mP6T", R4mP6T);

    exp.AddSampleGroup("run4",run4);
    
    TString Type[2] = {"reaction" , "topology"};
    TString PathName="/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/plots/";
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->Print( Form("%sProtonSelecPlots.pdf(", PathName.Data() ), "pdf");
    
    //delete c1;
    //TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    for(int ik=0; ik<2 ;ik++ )
    {
        /// \CC0Pi
        draw.SetTitle("accum[0][0]>7 HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 proton momentum");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 protoncandidate True momentum");
        draw.SetTitleX("proton candidate True momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_truemom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][0]>7 && prot) protonMomXprotonTrueMom");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetTitleY("proton candidate True momentum [MeV/c]");
        draw.Draw(exp,"sel_prot_truemom:sel_prot_mom_vertex", 50,0., 3000., 50, 0., 3000, "all","accum_level[0][0]>7 && sel_prot_mom_vertex>0" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && prot) selmumomXprotonMom");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.SetTitleY("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"sel_prot_mom_vertex:selmu_mom", 50,0., 3000., 50, 0., 3000, "all","accum_level[0][0]>7 && sel_prot_mom_vertex>0" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) nProtonsFGD");
        draw.SetTitleX("nProtonsFGD");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsFGD",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) nProtonsTPC");
        draw.SetTitleX("nProtonsTPC");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsTPC",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC>0) TPC proton starting positon");
        draw.SetTitleX("TPC proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protTPC_pos[0][2]", 40,-50., 1000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsFGD>0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-50., 1000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsFGD>0 && nProtonsTPC==0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-50., 1000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==1) protonMomXprotonStartPosTPC");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetTitleY("TPC proton starting positon");
        draw.Draw(exp,"protTPC_pos[0][2]:sel_prot_mom_vertex", 50,0., 3000., 40,-500., 1000, "all","accum_level[0][0]>7 && nProtonsTPC==1" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_nuErecQE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_nuErecQE");
        draw.Draw(exp,"selmu_nuErecQE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) selmu_nuErecQE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_nuErecQE");
        draw.Draw(exp,"selmu_nuErecQE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && prot) muon proton momentum scalar sum");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muXp mom scalar sum");
        draw.Draw(exp,"sel_prot_mom_vertex+selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && prot) muon proton momentum vector sum");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muXp mom vector sum");
        draw.Draw(exp,"TMath::Sqrt( selmu_mom*selmu_mom+sel_prot_mom_vertex*sel_prot_mom_vertex)",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
    //////////////////////////////////////////
        /*
        draw.SetTitle("(accum[0][0]>7) nprotonsTPCvsSelmuMom");
        draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
        draw.SetTitleY("nProtonsTPC");
        draw.Draw(exp,"nProtonsTPC:selmu_mom", 50,0., 3000., 5, 0.0, 5, "all","accum_level[0][0]>7" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) nprotonsTPCvsSelmuMom");
        draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
        draw.SetTitleY("nProtonsTPC");
        draw.Draw(exp,"nProtonsTPC:selmu_mom", 50,0., 3000., 5, 0.0, 5, "all","accum_level[0][0]>7 && nProtonsTPC==0" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==1) nprotonsTPCvsSelmuMom");
        draw.SetTitleX("#mu^{+} candidate momentum [MeV/c]");
        draw.SetTitleY("nProtonsTPC");
        draw.Draw(exp,"nProtonsTPC:selmu_mom", 50,0., 3000., 5, 0.0, 5, "all","accum_level[0][0]>7 && nProtonsTPC==1" ,"colz");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
        /// \VA_DLA_CC0Pi
        draw.SetTitle("(accum[0][0]>7) selmu_fgd_V11[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V11[0]");
        draw.Draw(exp,"selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) selmu_fgd_V11[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V11[0]");
        draw.Draw(exp,"selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_fgd_V33[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V33[0]");
        draw.Draw(exp,"selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) selmu_fgd_V33[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V33[0]");
        draw.Draw(exp,"selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_fgd_V55[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V55[0]");
        draw.Draw(exp,"selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) selmu_fgd_V55[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V55[0]");
        draw.Draw(exp,"selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_fgd_V77[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V77[0]");
        draw.Draw(exp,"selmu_fgd_V77[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && nProtonsTPC==0) selmu_fgd_V77[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V77[0]");
        draw.Draw(exp,"selmu_fgd_V77[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \VA_SHELL
        draw.SetTitle("(accum[0][0]>7) shell VA33");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA33");
        draw.Draw(exp,"selmu_fgd_V33[0]-selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) shell VA55");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA55");
        draw.Draw(exp,"selmu_fgd_V55[0]-selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) shell VA77");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA77");
        draw.Draw(exp,"selmu_fgd_V77[0]-selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \VA_DLA_CC0Pi
        draw.SetTitle("(accum[0][0]>7 && no protons) selmu_fgd_V11[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V11[0]");
        draw.Draw(exp,"selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && no protons) selmu_fgd_V33[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V33[0]");
        draw.Draw(exp,"selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][0]>7 && no protons) selmu_fgd_V55[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V55[0]");
        draw.Draw(exp,"selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && no protons) selmu_fgd_V77[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V77[0]");
        draw.Draw(exp,"selmu_fgd_V77[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \VA_SHELL_0PROTONS
        draw.SetTitle("(accum[0][0]>7 && no protons) shell VA33");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA33");
        draw.Draw(exp,"selmu_fgd_V33[0]-selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && no protons) shell VA55");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA55");
        draw.Draw(exp,"selmu_fgd_V55[0]-selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && no protons) shell VA77");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA77");
        draw.Draw(exp,"selmu_fgd_V77[0]-selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \ATI
        draw.SetTitle("(accum[0][0]>7 && Prot) Angular Transvere Imbalance");
        draw.SetLegendPos("tl");
        draw.SetTitleX("Angular Transvere Imbalance");
        draw.Draw(exp,"(sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.1) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.1)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.2) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.2)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.3) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.3)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.1) selmu_nuErecQE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("Erec");
        draw.Draw(exp,"selmu_nuErecQE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.1)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.2) selmu_nuErecQE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("Erec");
        draw.Draw(exp,"selmu_nuErecQE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.2)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.3) selmu_nuErecQE mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("Erec");
        draw.Draw(exp,"selmu_nuErecQE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.3)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.1) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.1)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.2) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.2)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.3) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.3)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) n true proton");
        draw.SetLegendPos("tr");
        draw.SetTitleX("true_nprotons");
        draw.Draw(exp,"true_nprotons",5, 0., 5.,Type[ik].Data(),"accum_level[0][0]>7");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.1) n true proton");
        draw.SetLegendPos("tr");
        draw.SetTitleX("true_nprotons");
        draw.Draw(exp,"true_nprotons",5, 0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.1)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.2) n true proton");
        draw.SetLegendPos("tr");
        draw.SetTitleX("true_nprotons");
        draw.Draw(exp,"true_nprotons",5, 0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.2)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot && ATI >0.3) n true proton");
        draw.SetLegendPos("tr");
        draw.SetTitleX("true_nprotons");
        draw.Draw(exp,"true_nprotons",5, 0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))>0.3)");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
//////////////////////////////////////////////////////////////////////////////////////////////////////
        /// \CC1Pi
        draw.SetTitle("accum[0][1]>7 HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && TPCproton==0) HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 proton momentum");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && prot) #Delta invariant mass");
        draw.SetLegendPos("tr");
        draw.SetTitleX("#Delta invariant mass");
        draw.Draw(exp,"TMath::Sqrt( (sel_prot_mom_vertex+PosPionMom[0])*(sel_prot_mom_vertex+PosPionMom[0])+(939.565+139.57061)*(939.565+139.57061) )",50,0., 6000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0 && NPosPion>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) nProtonsFGD");
        draw.SetTitleX("nProtonsFGD");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsFGD",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) nProtonsTPC");
        draw.SetTitleX("nProtonsTPC");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsTPC",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsTPC==0) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsTPC>0) TPC proton starting positon");
        draw.SetTitleX("TPC proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protTPC_pos[0][2]", 40,-500., 2000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsFGD>0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-500., 2000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsFGD>0 && nProtonsTPC==0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-500., 2000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsTPC==0) nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && prot) muon proton momentum scalar sum");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muXp mom scalar sum");
        draw.Draw(exp,"sel_prot_mom_vertex+selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && prot) muon proton momentum vector sum");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muXp mom vector sum");
        draw.Draw(exp,"TMath::Sqrt( (selmu_mom*selmu_dir[0])*(selmu_mom*selmu_dir[0])+(selmu_mom*selmu_dir[1])*(selmu_mom*selmu_dir[1])+(selmu_mom*selmu_dir[2])*(selmu_mom*selmu_dir[2])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][2])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][2]) )",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) nuEnergyRES");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nuEnergyRES");
        draw.Draw(exp,"nuEnergyRES",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsTPC==0) nuEnergyRES");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nuEnergyRES");
        draw.Draw(exp,"nuEnergyRES",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && Prot) Angular Transvere Imbalance");
        draw.SetLegendPos("tl");
        draw.SetTitleX("Angular Transvere Imbalance");
        draw.Draw(exp,"(sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");   
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) NNegPion");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NNegPion");
        draw.Draw(exp,"NNegPion",6.,0., 6.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) NPosPion");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NPosPion");
        draw.Draw(exp,"NPosPion",6.,0., 6.,Type[ik].Data(),"accum_level[0][1]>7");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) Michell Electrons");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NME");
        draw.Draw(exp,"NME",6.,0., 6.,Type[ik].Data(),"accum_level[0][1]>7");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][1]>7) mu-pi Z range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("mu - pi Z range");
        draw.Draw(exp,"selmu_endpos[2]-PosPionPosEnd[0][2]",40,-4000., 4000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \VA_DLA_CC1Pi
        draw.SetTitle("(accum[0][1]>7) selmu_fgd_V11[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V11[0]");
        draw.Draw(exp,"selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_fgd_V33[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V33[0]");
        draw.Draw(exp,"selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_fgd_V55[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V55[0]");
        draw.Draw(exp,"selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_fgd_V77[0]");
        draw.SetLegendPos("tr");
        draw.SetTitleX("selmu_fgd_V77[0]");
        draw.Draw(exp,"selmu_fgd_V77[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \VA_SHELL
        draw.SetTitle("(accum[0][1]>7) shell VA33");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA33");
        draw.Draw(exp,"selmu_fgd_V33[0]-selmu_fgd_V11[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) shell VA55");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA55");
        draw.Draw(exp,"selmu_fgd_V55[0]-selmu_fgd_V33[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) shell VA77");
        draw.SetLegendPos("tr");
        draw.SetTitleX("shell VA77");
        draw.Draw(exp,"selmu_fgd_V77[0]-selmu_fgd_V55[0]",30,0., 1600.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \BEFORE_SPLIT_SELECTION
        draw.SetTitle("(accum[0][0]>5) nProtonsFGD");
        draw.SetTitleX("nProtonsFGD");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsFGD",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>5");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>5) nProtonsTPC");
        draw.SetTitleX("nProtonsTPC");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsTPC",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>5");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>5) NNegPion");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NNegPion");
        draw.Draw(exp,"NNegPion",6.,0., 6.,Type[ik].Data(),"accum_level[0][0]>5");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>5) NPosPion");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NPosPion");
        draw.Draw(exp,"NPosPion",6.,0., 6.,Type[ik].Data(),"accum_level[0][0]>5");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>5) Michell Electrons");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NME");
        draw.Draw(exp,"NME",6.,0., 6.,Type[ik].Data(),"accum_level[0][0]>5");
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>5 proton momentum");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 4000.,Type[ik].Data(),"accum_level[0][0]>5");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>5 proton range");
        draw.SetTitleX("proton range [cm]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_range_vtx",40,0., 4000.,Type[ik].Data(),"accum_level[0][0]>5");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>5 proton sel_prot_costheta");
        draw.SetTitleX("sel_prot_costheta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"sel_prot_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>5 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
///////////////////////////////////////////////////////////////
        
        /// \CC-OTHER
        draw.SetTitle("accum[0][2]>6 HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && nProtonsTPC==0) HM proton true momentum");
        draw.SetTitleX("HM proton true momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"trueHMprot_mom",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 proton momentum");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 protoncandidate True momentum");
        draw.SetTitleX("proton candidate True momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_truemom",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 proton sel_prot_costheta");
        draw.SetTitleX("sel_prot_costheta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"sel_prot_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>6 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) nProtonsFGD");
        draw.SetTitleX("nProtonsFGD");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsFGD",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) nProtonsTPC");
        draw.SetTitleX("nProtonsTPC");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"nProtonsTPC",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && nProtonsTPC==0) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && nProtonsTPC>0) TPC proton starting positon");
        draw.SetTitleX("TPC proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protTPC_pos[0][2]", 40, 0., 1000.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && nProtonsFGD>0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,0., 1000.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && nProtonsFGD>0 && nProtonsTPC==0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40, 0., 1000.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 proton topology");
        draw.SetTitleX("proton candidate topology");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_topo",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 proton range");
        draw.SetTitleX("proton range [cm]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_range_vtx",40,0., 4000.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][2]>6 proton sel_prot_costheta");
        draw.SetTitleX("sel_prot_costheta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"sel_prot_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>6 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
    //////////////
        /// \OTHER_STUFF_FOR_CC0PI
        draw.SetTitle("accum[0][0]>7 #mu^{-} momentum");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot) #mu^{-} momentum");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 proton range");
        draw.SetTitleX("proton range [cm]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_range_vtx",40,0., 4000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 proton topology");
        draw.SetTitleX("proton candidate topology");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_topo",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][0]>7 cos between proton and muon");
        draw.SetLegendPos("tl");
        draw.SetTitleX("cosTheta protonXmuon");
        draw.Draw(exp,"selmu_dir.Dot(sel_prot_dir_vertex[0])",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("accum[0][0]>7 nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot) nu_trueE");
        draw.SetLegendPos("tr");
        draw.SetTitleX("nu_trueE");
        draw.Draw(exp,"nu_trueE",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("selmu_range");
        draw.Draw(exp,"TMath::Sqrt( (selmu_endpos[0] - selmu_pos[0])*(selmu_endpos[0] - selmu_pos[0]) + (selmu_endpos[1] - selmu_pos[1])*(selmu_endpos[1] - selmu_pos[1]) + (selmu_endpos[2] - selmu_pos[2])*(selmu_endpos[2] - selmu_pos[2]) )",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot) selmu_range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("selmu_range");
        draw.Draw(exp,"TMath::Sqrt( (selmu_endpos[0] - selmu_pos[0])*(selmu_endpos[0] - selmu_pos[0]) + (selmu_endpos[1] - selmu_pos[1])*(selmu_endpos[1] - selmu_pos[1]) + (selmu_endpos[2] - selmu_pos[2])*(selmu_endpos[2] - selmu_pos[2]) )",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && Prot) proton Z Endpos");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton Z Endpos");
        draw.Draw(exp,"sel_prot_endpos[2]",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        

////////////////////////////////////
        
        /// \OTHER_STUFF_FOR_CC1PI
        draw.SetTitle("accum[0][1]>7 #mu^{-} momentum");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && Prot) #mu^{-} momentum");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 proton momentum");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 4000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 proton True momentum");
        draw.SetTitleX("proton True momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_truemom",40,0., 4000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 proton range");
        draw.SetTitleX("proton range [cm]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_range_vtx",40,0., 4000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 proton topology");
        draw.SetTitleX("proton candidate topology");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_topo",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && Prot)  costheta proton and muon");
        draw.SetLegendPos("tr");
        draw.SetTitleX("cosTheta protonXmuon");
        draw.Draw(exp,"selmu_dir.Dot(sel_prot_dir_vertex[0])",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && Prot)  costheta proton and #pi^+");
        draw.SetLegendPos("tl");
        draw.SetTitleX("cosTheta protonX#{pi^+}");
        draw.Draw(exp,"PosPionDir[0][0].Dot(sel_prot_truedir[0])",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0 && NPosPion==1");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && Prot)  costheta proton and HPpion");
        draw.SetLegendPos("tl");
        draw.SetTitleX("cosTheta protonX#HMpion");
        draw.Draw(exp,"sel_pi_dir_vertex[0].Dot(sel_prot_dir_vertex[0])",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("accum[0][1]>7 prot range minus pi range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("prot range minus pi range");
        draw.Draw(exp,"sel_prot_range_vtx-sel_pi_range_vtx",50,-4000., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0 && sel_pi_range_vtx>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("selmu_range");
        draw.Draw(exp,"TMath::Sqrt( (selmu_endpos[0] - selmu_pos[0])*(selmu_endpos[0] - selmu_pos[0]) + (selmu_endpos[1] - selmu_pos[1])*(selmu_endpos[1] - selmu_pos[1]) + (selmu_endpos[2] - selmu_pos[2])*(selmu_endpos[2] - selmu_pos[2]) )",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
       
        draw.SetTitle("(accum[0][1]>7 && Prot) selmu_range");
        draw.SetLegendPos("tl");
        draw.SetTitleX("selmu_range");
        draw.Draw(exp,"TMath::Sqrt( (selmu_endpos[0] - selmu_pos[0])*(selmu_endpos[0] - selmu_pos[0]) + (selmu_endpos[1] - selmu_pos[1])*(selmu_endpos[1] - selmu_pos[1]) + (selmu_endpos[2] - selmu_pos[2])*(selmu_endpos[2] - selmu_pos[2]) )",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && sel_prot_mom_vertex>0");
        
        cout<<"debug kurwa"<<endl;
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

    }
    
    cout<<"debug kurwa2"<<endl;
    c1->Print(Form("%sProtonSelecPlots.pdf)",PathName.Data()), "pdf");
    delete c1;
    cout<<"debug kurwa3"<<endl;
}



//WARNING PRINT PURITIES

    //draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsTPC==0")
    //draw.PrintPurities(exp,"reaction","accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1])))>0.3");
    //draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsTPC<2 && (CUTprotTPC_pos>400 || CUTprotTPC_pos<-1000) ")

















        
        
        //WARNING PROBNE ZMIENNE
        /// \brief kat poprzeczny miedzy mionem i protonem
        //draw.Draw(exp,"TMath::Sqrt( (sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1])  )",30,0., 3000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        /// \brief 
        //draw.Draw(exp,"TMath::Sqrt( (selmu_mom*selmu_dir[0])*(selmu_mom*selmu_dir[0])+(selmu_mom*selmu_dir[1])*(selmu_mom*selmu_dir[1]) )",30,0., 3000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");

        
        /// \brief  ANGULAR TRANSVEREE IBALANCE
        //draw.Draw(exp,"(sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1]))",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");

        /// \brief  three momentum transvere imbalance
        //(sel_prot_dir_vertex[0][0]+selmu_dir[0])   (sel_prot_dir_vertex[0][1]+selmu_dir[1])
        //TMath::Sqrt((sel_prot_dir_vertex[0][0]+selmu_dir[0])*(sel_prot_dir_vertex[0][0]+selmu_dir[0])+(sel_prot_dir_vertex[0][1]+selmu_dir[1])*(sel_prot_dir_vertex[0][1]+selmu_dir[1]))
        
        //draw.Draw(exp,"TMath::Sqrt((sel_prot_mom_vertex*sel_prot_dir_vertex[0][0]+selmu_mom*selmu_dir[0])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][0]+selmu_mom*selmu_dir[0])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1]+selmu_mom*selmu_dir[1])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1]+selmu_mom*selmu_dir[1]))",40, 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        
        //draw.PrintPurities(exp,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1])))>0");

        
        //TODO spoko ciecie
        //draw.PrintPurities(exp,"topology","accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1])))>0.4");

        
        //draw.PrintPurities(exp,Type[ik].Data(),"accum_level[0][0]>7")
        
        
        //draw.Draw(exp,"TMath::Sqrt( (sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][0])+(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1])*(sel_prot_mom_vertex*sel_prot_dir_vertex[0][1]) )",30,0., 3000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        //draw.Draw(exp,"TMath::Sqrt( (sel_prot_dir_vertex[0][0])*(sel_prot_dir_vertex[0][0])+(sel_prot_dir_vertex[0][1])*(sel_prot_dir_vertex[0][1]) )",30,0., 3000.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0");
        
        
        
        //draw.PrintPurities(exp,Type[ik].Data(),"accum_level[0][0]>7 && TMath::Sqrt( (sel_prot_dir_vertex[0][0])*(sel_prot_dir_vertex[0][0])+(sel_prot_dir_vertex[0][1])*(sel_prot_dir_vertex[0][1]) )>0.4 && sel_prot_mom_vertex>0")
        
        
        
        //draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1])))>0.2");
    //////////////////////////////////CC1Pi/////////////////// 
