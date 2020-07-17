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
    //TODO dodaj te zabawy z ECAL aby rozroznic od mionu
    //TODO ped pionu dla SI aby zobaczyc z czego to wynika
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    //TODO hardocoded value
    DrawingTools draw("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6TPlayground.root",false);
    
    Experiment exp("nd280");

    DataSample* R4mP6T = new DataSample("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6TPlayground.root");
    
    SampleGroup run4("run4");
    run4.AddMCSample("R4mP6T", R4mP6T);

    exp.AddSampleGroup("run4",run4);
    
    TString Type[3] = {"reaction" , "topology", "mectopology"};
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
        /*
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
        */
        /// \VA_SHELL
        /*
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
        
        /// \VA_DLA_CC0Pi_0PROTONS
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
        */
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
        draw.Draw(exp,"protTPC_pos[0][2]", 40,-50., 1000,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsFGD>0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-50., 1000,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && nProtonsFGD>0 && nProtonsTPC==0) FGD proton starting positon");
        draw.SetTitleX("FGD proton starting positon");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"protFGD_pos[0][2]", 40,-50., 1000,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0 && nProtonsTPC==0");
        
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
        /*
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
        
        */
        /// \VA_SHELL
        /*
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
        */
        /// \Muon_Kinematics_0pi
        const int BIN0PI = 30;
        const double MomentumEdges[BIN0PI] = {0, 200, 300, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 2000, 2500, 3000, 5000, 30000.};
        const double CosEdges[BIN0PI] = {-1, 0.5, 0.6, 0.7, 0.76, 0.78, 0.8, 0.83, 0.85, 0.88, 0.89, 0.9, 0.91, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1.};
        gPad->SetGrid();
        gStyle->SetPalette(51);
        
        draw.SetTitle("(accum[0][0]>7) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN0PI-1 ,MomentumEdges, BIN0PI-1, CosEdges, "all","accum_level[0][0]>7","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN0PI-1 ,MomentumEdges, BIN0PI-1, CosEdges, "all","accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN0PI-1 ,MomentumEdges, BIN0PI-1, CosEdges, "all","accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        gPad->SetGrid(0,0);
        
        draw.SetTitle("(accum[0][0]>7) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][1]>7) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>6");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons) costheta");
        draw.SetLegendPos("tl");
        draw.SetTitleX("#mu^{-} candidate costheta");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0");   
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \Muon_Kinematics_1pi
        const int BIN1PI = 19;
        const double MomentumEdges1Pi[BIN1PI] = {0, 300, 350, 400, 500, 600, 650, 700, 750, 800, 900, 1000, 1100, 1200, 1500, 2000, 3000, 5000, 30000.};
        const double CosEdges1Pi[BIN1PI] = {-1, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 0.995, 1.};
        gPad->SetGrid();
        gStyle->SetPalette(51);
        
        draw.SetTitle("(accum[0][1]>7) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN1PI-1 ,MomentumEdges1Pi, BIN1PI-3, CosEdges1Pi, "all","accum_level[0][1]>7","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN1PI-1, MomentumEdges1Pi, BIN1PI-3, CosEdges1Pi, "all","accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) momentum vs cos#theta");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetTitleY("#mu^{-} candidate cos#theta");
        draw.Draw(exp,"selmu_costheta:selmu_mom", BIN1PI-1 ,MomentumEdges1Pi, BIN1PI-3, CosEdges1Pi, "all","accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        gPad->SetGrid(0,0);
        
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
        /// \ZERO_PI_COMPARISON
        
        draw.SetTitle("CC0Pi+pFGD");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pFGD");
        draw.SetTitleX("proton cos#theta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"sel_prot_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pFGD");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pFGD");
        draw.SetTitleX("#mu^{-} cos#theta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        
        draw.SetTitle("CC0Pi+pTPC");
        draw.SetTitleX("proton candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pTPC");
        draw.SetTitleX("proton cos#theta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"sel_prot_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pTPC");
        draw.SetTitleX("#mu^{-} candidate momentum [MeV/c]");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("CC0Pi+pTPC");
        draw.SetTitleX("#mu^{-} cos#theta");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"selmu_costheta",40,-1., 1.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \Physical_Study_CC0Pi
        draw.SetTitle("(accum[0][0]>7) TPCProtonTId");
        draw.SetTitleX("True PDG of reco TPC proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"TPCProtonTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) FGDProtonTId");
        draw.SetTitleX("True PDG of rec FGD proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"FGDProtonTId", 100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /*
        draw.SetTitle("(accum[0][0]>7 && TruePDG==2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC>0 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && TruePDG!=2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC>0 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && TruePDG==2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0 && FGDProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && TruePDG!=2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsFGD>0 && FGDProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
        
        
        draw.SetTitle("(accum[0][0]>7) FGDProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtMom",40., 0., 2500. ,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /*
        draw.SetTitle("(accum[0][0]>7 && no FSI) FGDProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && FGDProtonParentTId==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && only FSI) FGDProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && FGDProtonParentTId!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
        draw.SetTitle("(accum[0][0]>7) TPCProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /*
        draw.SetTitle("(accum[0][0]>7 && no FSI) TPCProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && TPCProtonParentTId==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && only FSI) TPCProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && TPCProtonParentTId!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
        /// \Physical_Study_CC1Pi
        draw.SetTitle("(accum[0][1]>7) TPCProtonTId");
        draw.SetTitleX("True PDG of reco TPC proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"TPCProtonTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) FGDProtonTId");
        draw.SetTitleX("True PDG of rec FGD proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"FGDProtonTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /*
        draw.SetTitle("(accum[0][1]>7 && TruePDG==2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && TruePDG!=2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC>0 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && TruePDG==2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0 && FGDProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && TruePDG!=2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsFGD>0 && FGDProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
        
        draw.SetTitle("(accum[0][1]>7) FGDProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtMom",40., 0., 2500. ,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][1]>7) TPCProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \Physical_Study_CCOther
        draw.SetTitle("(accum[0][2]>6) TPCProtonTId");
        draw.SetTitleX("True PDG of reco TPC proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"TPCProtonTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) FGDProtonTId");
        draw.SetTitleX("True PDG of rec FGD proton");
        draw.SetLegendPos("tl");
        draw.Draw(exp,"FGDProtonTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /*
        draw.SetTitle("(accum[0][2]>6 && TruePDG==2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC>0 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && TruePDG!=2212) TPCProtonParentTId");
        draw.SetTitleX("True parent PDG of reco TPC proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC>0 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && TruePDG==2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0 && FGDProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && TruePDG!=2212) FGDProtonParentTId");
        draw.SetTitleX("True parent PDG of reco FGD proton");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtonParentTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsFGD>0 && FGDProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
               
        draw.SetTitle("(accum[0][2]>6) FGDProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"FGDProtMom",40., 0., 2500. ,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][2]>6) TPCProtMom");
        draw.SetTitleX("Momentum of proton candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProtMom",40., 0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");        
        
        /// \Physical_Study_CC0Pi_SecondTake
        draw.SetTitle("(accum[0][0]>7 && only false topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && only false topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology!=0 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][0]>7 && only false topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology!=0 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][0]>7 && only true topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && only true topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology==0 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][0]>7 && only true topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][0]>7 && topology==0 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \Physical_Study_CC1Pi_SecondTake
        draw.SetTitle("(accum[0][1]>7 && only false topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && only false topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][1]>7 && only false topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][1]>7 && only true topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && only true topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][1]>7 && only true topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
    
        /// \Physical_Study_CCOther_SecondTake
        draw.SetTitle("(accum[0][2]>6 && only false topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && only false topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][2]>6 && only false topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][2]>6 && only true topologies) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && only true topologies && 0 protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    
        draw.SetTitle("(accum[0][2]>6 && only true topologies && N protons) selmu_mom");
        draw.SetTitleX("Momentum of muon candidate");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        /// \Study_ofPionSI_CC0PI
        draw.SetTitle("(accum[0][0]>7 ) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 ) IntType");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^+ && only ABS) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1 && IntType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^+ && only QE) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1 && IntType==2");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+ && only ABS) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+ && only QE) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType==2");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+");
        draw.SetTitleX("Pion momentum[MeV/c]");
        draw.SetTitleY("Pion interaction type");
        draw.Draw(exp,"IntType:PionMom",40,0., 2500., 5., 0, 5., "all","accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^+");
        draw.SetTitleX("Pion momentum[MeV/c]");
        draw.SetTitleY("Pion interaction type");
        draw.Draw(exp,"IntType:PionMom",40,0., 2500., 5., 0, 5., "all","accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1","colz");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][0]>7 && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \Study_ofPionSI_CC1PI
        draw.SetTitle("(accum[0][1]>7 ) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 ) IntType");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \Study_ofPionSI_CCOther
        draw.SetTitle("(accum[0][2]>6 ) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 ) IntType");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons) NPions");
        draw.SetTitleX("Number of pions");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NPions",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0 && NPions!=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && #pi^+) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && #pi^+) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0 && PionType==1 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && #pi^-) IntType");
        draw.SetTitleX("Pion interaction type");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"IntType",5,0., 5.,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && #pi^-) PionMom");
        draw.SetTitleX("Pion momentum");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PionMom",40,0., 2500,Type[ik].Data(),"accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0 && PionType==0 && IntType>=0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \ECAL_VARAIBLES_CC0PI
///////////////////////////////////////////////////////////////////////////////////////        
        draw.SetTitle("(accum[0][0]>7) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 properly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 wrongly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 PDG==13) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && TPCProtonTId==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) TPCProton_ecaldetector");
        draw.SetTitleX("TPC proton ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) TPCProton_ecalnhits");
        draw.SetTitleX("TPC proton ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /// /\selmu
        draw.SetTitle("(accum[0][0]>7) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 properly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && particle==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 wrongly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && particle!=13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 PDG==2212) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][0]>7 && particle==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_ecaldetector");
        draw.SetTitleX("muon candidate ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7) selmu_ecalnhits");
        draw.SetTitleX("muon candidate ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][0]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        
        
        /// \ECAL_VARAIBLES_CC1PI
///////////////////////////////////////////////////////////////
        draw.SetTitle("(accum[0][1]>7) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 properly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 wrongly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 PDG==13) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && TPCProtonTId==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) TPCProton_ecaldetector");
        draw.SetTitleX("TPC proton ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) TPCProton_ecalnhits");
        draw.SetTitleX("TPC proton ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /// \selmu
            
        draw.SetTitle("(accum[0][1]>7) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 properly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && particle==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 wrongly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && particle!=13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 PDG==2212) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && particle==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_ecaldetector");
        draw.SetTitleX("muon candidate ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu_ecalnhits");
        draw.SetTitleX("muon candidate ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        

        /// \ECAL_VARAIBLES_CCOther
///////////////////////////////////////////////////////////////
        draw.SetTitle("(accum[0][2]>6) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 properly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && TPCProtonTId==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 wrongly reconstructed) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && TPCProtonTId!=2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 PDG==13) TPCProton_ecalemene");
        draw.SetTitleX("TPC proton energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && TPCProtonTId==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) TPCProton_ecaldetector");
        draw.SetTitleX("TPC proton ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) TPCProton_ecalnhits");
        draw.SetTitleX("TPC proton ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"TPCProton_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        /// \selmu
        
        draw.SetTitle("(accum[0][2]>6) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 properly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && particle==13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 wrongly reconstructed) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && particle!=13");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 PDG==2212) selmu_ecalemene");
        draw.SetTitleX("muon candidate energy deposit in ECAL");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalemene",40,0., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && particle==2212");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) selmu_ecaldetector");
        draw.SetTitleX("muon candidate ecal detecotr");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecaldetector",20,0., 20.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) selmu_ecalnhits");
        draw.SetTitleX("muon candidate ecal hits");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"selmu_ecalnhits",40,0., 200.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        /// \Pion_reconstruction_CC1Pi
//////////////////////////////////////////////////////////////
        draw.SetTitle("(accum[0][1]>7) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && True topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && True topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][1]>7 && 0 protons && false topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && false topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons && True topology) Michell Electrons");
        draw.SetTitleX("NME");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NME",5.,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && True topology) Michell Electrons");
        draw.SetTitleX("NME");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NME",5.,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && topology==1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][1]>7 && 0 protons && false topology) Michell Electrons");
        draw.SetTitleX("NME");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NME",5.,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons && false topology) Michell Electrons");
        draw.SetTitleX("NME");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NME",5.,0., 5.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) Michell Electrons");
        draw.SetLegendPos("tr");
        draw.SetTitleX("NME");
        draw.Draw(exp,"NME",5.,0., 5.,Type[ik].Data(),"accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && True topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && True topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][2]>6 && 0 protons && false topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && false topology) PosPionTId");
        draw.SetTitleX("True PDG of reco #pi^+");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"PosPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6) NegPionTId");
        draw.SetTitleX("True PDG of reco #pi^-");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NegPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && 0 protons && True topology) NegPionTId");
        draw.SetTitleX("True PDG of reco #pi^-");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NegPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && True topology) NegPionTId");
        draw.SetTitleX("True PDG of reco #pi^-");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NegPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology==2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

        draw.SetTitle("(accum[0][2]>6 && 0 protons && false topology) NegPionTId");
        draw.SetTitleX("True PDG of reco #pi^-");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NegPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && nProtonsTPC==0 && nProtonsFGD==0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons && false topology) NegPionTId");
        draw.SetTitleX("True PDG of reco #pi^-");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"NegPionTId",100, -1000., 2500.,Type[ik].Data(),"accum_level[0][2]>6 && topology!=2 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
///////////////////////////////////////////////////////////////
        /// \protons_constains
//////////////////////////////////////////////////////////////
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && true toplogy) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && topology==0 && nProtonsTPC==0 && nProtonsFGD==0 ");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && true toplogy) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && topology==0 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons && false toplogy) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && topology!=0 && nProtonsTPC==0 && nProtonsFGD==0 ");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons && false toplogy) true_nprotons");
        draw.SetTitleX("true_nprotons");
        draw.SetLegendPos("tr");
        draw.Draw(exp,"true_nprotons",5,0., 5.,Type[ik].Data(),"accum_level[0][0]>7 && topology!=0 && (nProtonsTPC + nProtonsFGD)>0");

        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
    //////////////
        /*
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
    
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        */
    }
    /// \PARTICLE_OF_HMPT
        draw.SetTitle("(accum[0][0]>7) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][0]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][0]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0]>7 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][0]>7 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][1]>7");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][1]>7 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][1]>7 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][1]>7 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0][2]>6) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][2]>6");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][0][2]>6 && 0 protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][2]>6 && nProtonsTPC==0 && nProtonsFGD==0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");
        
        draw.SetTitle("(accum[0][2]>6 && N protons) selmu mom");
        draw.SetLegendPos("tr");
        draw.SetTitleX("muon candidate momentum [MeV/c]");
        draw.Draw(exp,"selmu_mom",40,0., 5000.,"particle","accum_level[0][2]>6 && (nProtonsTPC + nProtonsFGD)>0");
        
        c1->Print(Form("%sProtonSelecPlots.pdf",PathName.Data()), "pdf");

    c1->Print(Form("%sProtonSelecPlots.pdf)",PathName.Data()), "pdf");
    delete c1;
}

//draw.Draw(exp,"selmu_mom",40., 0., 5000.,Type[ik].Data(),"accum_level[0][1]>7 && topology!=1 && (nProtonsTPC + nProtonsFGD)>0 && (FGDProtonTId[0]==2212 || nProtonsFGD==0) && (TPCProtonTId==2212 || nProtonsTPC==0)");




//WARNING PRINT PURITIES

    //draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsTPC==0")
    //draw.PrintPurities(exp,"reaction","accum_level[0][0]>7 && sel_prot_mom_vertex>0 && ((sel_prot_dir_vertex[0][0]*(-selmu_dir[0]))+(sel_prot_dir_vertex[0][1]*(-selmu_dir[1])))>0.3");
    //draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsTPC<2 && (CUTprotTPC_pos>400 || CUTprotTPC_pos<-1000) ")






//draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0 && (selmu_pos[0]-protFGD_pos[0][0])<100 && (selmu_pos[0]-protFGD_pos[0][0])>-100 && (selmu_pos[1]-protFGD_pos[0][1])<100 && (selmu_pos[1]-protFGD_pos[0][1])>-100 && (selmu_pos[2]-protFGD_pos[0][2])>-50 && (selmu_pos[2]-protFGD_pos[0][2])<50")


 //draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,"reaction","accum_level[0][0]>7 && nProtonsFGD==1 && nProtonsTPC==0 && NTPCSec==0 && NFGDSec==1 && (selmu_pos[0]-protFGD_pos[0][0])<100 && (selmu_pos[0]-protFGD_pos[0][0])>-100 && (selmu_pos[1]-protFGD_pos[0][1])<100 && (selmu_pos[1]-protFGD_pos[0][1])>-100 && (selmu_pos[2]-protFGD_pos[0][2])>-50 && (selmu_pos[2]-protFGD_pos[0][2])<50 ");


//draw.Draw(exp,"sel_prot_mom_vertex",40,0., 2500.,"reaction","accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1 && NTPCSec==1 && NFGDSec==0 && (selmu_pos[0]-protTPC_pos[0][0])<50 && (selmu_pos[0]-protTPC_pos[0][0])>-50 && (selmu_pos[1]-protTPC_pos[0][1])<50 && (selmu_pos[1]-protTPC_pos[0][1])>-50 && (selmu_pos[2]-protTPC_pos[0][2])>-30 && (selmu_pos[2]-protTPC_pos[0][2])<30 ");





//draw.PrintPurities(exp, "reaction","accum_level[0][0]>7 && nProtonsFGD==0 && nProtonsTPC==1 && NTPCSec==1 && NFGDSec==0 && (selmu_pos[0]-protTPC_pos[0][0])<50 && (selmu_pos[0]-protTPC_pos[0][0])>-50 && (selmu_pos[1]-protTPC_pos[0][1])<50 && (selmu_pos[1]-protTPC_pos[0][1])>-50 && (selmu_pos[2]-protTPC_pos[0][2])>-30 && (selmu_pos[2]-protTPC_pos[0][2])<30")

        
        
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
