#include <TH2Poly.h>
#include <TH2D.h>
#include <vector>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <THStack.h>
#include <iostream>
#include <TF1.h>
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"

//g++ `root-config --cflags` -g -std=c++11 -o BinningStudy BinningStudy.cpp -I`root-config --incdir` `root-config --glibs --libs` 



void MatrixHack()
{

    TFile* XsecMatrix = TFile::Open("xsec_2021a_flux_21bv2_v14.root");
    TFile* PostFitMatrix = TFile::Open("Data_Restricte_Data_Normal.root.root");
    
    TFile *hack = TFile::Open("xsec_2021a_flux_21bv2_v14_hackStandard.root","RECREATE");
    
    TObjArray* xsec_param_names = (TObjArray*)(XsecMatrix->Get("xsec_param_names"));
    TObjArray* sk_spline_names =(TObjArray*)(XsecMatrix->Get("sk_spline_names"));
    TObjArray* sk_spline_modes =(TObjArray*)(XsecMatrix->Get("sk_spline_modes"));
    TObjArray* nd_spline_names =(TObjArray*)(XsecMatrix->Get("nd_spline_names"));
    
    TVectorT<double>  *xsec_param_nom    = (TVectorD*)(XsecMatrix->Get("xsec_param_nom"));
    TVectorT<double>  *xsec_param_nom_unnorm    = (TVectorD*)(XsecMatrix->Get("xsec_param_nom_unnorm"));
    TVectorT<double>  *xsec_param_prior  = (TVectorD*)(XsecMatrix->Get("xsec_param_prior"));
    TVectorT<double>  *xsec_param_prior_unnorm   = (TVectorD*)(XsecMatrix->Get("xsec_param_prior_unnorm"));
    TVectorT<double>  *xsec_param_lb     = (TVectorD*)(XsecMatrix->Get("xsec_param_lb"));
    TVectorT<double>  *xsec_param_ub     = (TVectorD*)(XsecMatrix->Get("xsec_param_ub"));
    TMatrixT<double>  *xsec_param_id     = (TMatrixD*)(XsecMatrix->Get("xsec_param_id"));
    TVectorT<double>  *xsec_stepscale    = (TVectorD*)(XsecMatrix->Get("xsec_stepscale"));


    TObjArray* xsec_norm_modes = (TObjArray*)(XsecMatrix->Get("xsec_norm_modes"));
    TObjArray* xsec_norm_horncurrents = (TObjArray*)(XsecMatrix->Get("xsec_norm_horncurrents"));
    TObjArray* xsec_norm_etru_bnd_low= (TObjArray*)(XsecMatrix->Get("xsec_norm_etru_bnd_low"));
    TObjArray* xsec_norm_etru_bnd_high = (TObjArray*)(XsecMatrix->Get("xsec_norm_etru_bnd_high"));
    TObjArray* xsec_norm_q2_true_bnd_low= (TObjArray*)(XsecMatrix->Get("xsec_norm_q2_true_bnd_low"));
    TObjArray* xsec_norm_q2_true_bnd_high =(TObjArray*)(XsecMatrix->Get("xsec_norm_q2_true_bnd_high"));
    TObjArray* xsec_norm_elements =(TObjArray*)(XsecMatrix->Get("xsec_norm_elements"));
    TObjArray* xsec_norm_nupdg = (TObjArray*)(XsecMatrix->Get("xsec_norm_nupdg"));
    TObjArray* xsec_norm_prod_nupdg= (TObjArray*)(XsecMatrix->Get("xsec_norm_prod_nupdg"));

    TMatrixDSym *xsec_cov = (TMatrixDSym*)(XsecMatrix->Get("xsec_cov"));
    TH2D *hcov = (TH2D*)(XsecMatrix->Get("hcov"));

    
    //TVectorT<double>  *FitParameters_HPD    = (TVectorD*)(PostFitMatrix->Get("FitParameters_HPD"));
    TVectorT<double>  *FitParameters_HPD    = (TVectorD*)(PostFitMatrix->Get("FitParameters_HPD_2"));
        
    hack->cd();
    xsec_param_names->Write("xsec_param_names", 1);
    sk_spline_names->Write("sk_spline_names", 1);
    sk_spline_modes->Write("sk_spline_modes", 1);
    nd_spline_names->Write("nd_spline_names", 1);
    
    xsec_param_nom->Write("xsec_param_nom");
    xsec_param_nom_unnorm->Write("xsec_param_nom_unnorm");
    
    FitParameters_HPD->Write("xsec_param_prior");
    //xsec_param_prior->Write("xsec_param_prior");
    xsec_param_prior_unnorm->Write("xsec_param_prior_unnorm");
    xsec_param_lb->Write("xsec_param_lb");
    xsec_param_ub->Write("xsec_param_ub");
    xsec_param_id->Write("xsec_param_id");
    xsec_stepscale->Write("xsec_stepscale");

    xsec_norm_modes->Write("xsec_norm_modes", 1);
    xsec_norm_horncurrents->Write("xsec_norm_horncurrents", 1);
    xsec_norm_etru_bnd_low->Write("xsec_norm_etru_bnd_low", 1);
    xsec_norm_etru_bnd_high->Write("xsec_norm_etru_bnd_high", 1);
    xsec_norm_q2_true_bnd_low->Write("xsec_norm_q2_true_bnd_low", 1);
    xsec_norm_q2_true_bnd_high->Write("xsec_norm_q2_true_bnd_high", 1);
    xsec_norm_elements->Write("xsec_norm_elements", 1);
    xsec_norm_nupdg->Write("xsec_norm_nupdg", 1);
    xsec_norm_prod_nupdg->Write("xsec_norm_prod_nupdg", 1);

    xsec_cov->Write("xsec_cov");
    hcov->Write("hcov");
        
    hack->Close();
    XsecMatrix->Close();
    PostFitMatrix->Close();
}


