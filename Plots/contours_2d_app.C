#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TPad.h"
#include "TGraph.h"
#include "TGaxis.h"
#include "TH2D.h"
#include "TLegend.h"
#include "TMath.h"
#include "TF1.h"
#include "TColor.h"

#include <iostream>
#include <sstream>

/// A function to return a string of a file name without its extension
std::string getNameNoExt(std::string name, std::string ext)
{
  std::size_t pos ;
  pos = name.find(ext);
  name = name.substr(0,pos);
  return name ;
}

/// A function to save canvas as .root / .png / .pdf / .eps 
void saveCanvas(TCanvas* canvas, std::string name, std::string legend_)
{
   name = getNameNoExt(name, ".root") ;
  name = name + legend_ + ".root" ;
  canvas -> SaveAs(name.c_str()) ;
  
  name = getNameNoExt(name, ".root") ;
  name = name + ".png" ;
  canvas -> SaveAs(name.c_str()) ;
  
  name = getNameNoExt(name, ".png") ;
  name = name + ".pdf" ;
  canvas -> SaveAs(name.c_str()) ;
    
  name = getNameNoExt(name, ".pdf") ;
  name = name + ".eps" ;
  canvas -> SaveAs(name.c_str()) ;

}

/// A function to make pretty canvas
void makePrettyCanvas(TCanvas* canv_)
{
  canv_ -> SetLeftMargin(0.15);
  canv_ -> SetRightMargin(0.15);
  canv_ -> SetBottomMargin(0.15);
  canv_ -> SetTopMargin(0.15);

  /// Set better deep-sea-style palette
  const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Int_t DeepSeaMod[NCont];

  //Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 }; // for normal palette 51
  Double_t stops[NRGBs] = { 0.00, 0.02, 0.20, 0.70, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.09, 0.18, 0.09, 0.00 };
  Double_t green[NRGBs] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
  Double_t blue[NRGBs]  = { 0.17, 0.39, 0.62, 0.79, 0.97 };
  Int_t FI = TColor::CreateGradientColorTable(NRGBs,stops,red,green,blue,NCont);
  for (int i=0;i<NCont;i++) DeepSeaMod[i] = FI+i;
 
  /// Some cosmetics
  gPad->SetTickx() ;
  gPad->SetTicky() ;
  //gPad->SetLogz();
  
  gStyle->SetPalette(51,0);
  gStyle->SetOptStat(0);
  TGaxis::SetMaxDigits(4);
  
  gStyle->SetOptStat(0);
  gStyle->SetTextFont(132) ; 
  gStyle->SetTitleOffset(1.3, "xy") ; 
  gStyle->SetTitleSize(0.035, "xy") ;
  gStyle->SetLabelFont(132, "xy") ; 
  gStyle->SetLabelSize(0.035, "xy") ; 
  gStyle->SetLabelSize(0.0, "z") ;
  gStyle->SetLegendFont(132) ;
  gPad->SetLeftMargin(0.13);
}

/// A function to make pretty TH2D
void makePrettyTh2d(TH2D* hist_, std::string varX_, std::string varY_)
{
  if(varX_.find("dcp") != std::string::npos)
    hist_ -> GetXaxis() -> SetTitle("#delta_{CP}") ;
  else if(varX_.find("theta13") != std::string::npos)
    hist_ -> GetXaxis() -> SetTitle("sin^{2}(#theta_{13})") ;
  else if(varX_.find("theta23") != std::string::npos)
    hist_ -> GetXaxis() -> SetTitle("sin^{2}(#theta_{23})") ;
  else if(varX_.find("dm23") != std::string::npos)
    hist_ -> GetXaxis() -> SetTitle("#Delta m_{32}^{2}") ;     
  else
    hist_ -> GetXaxis() -> SetTitle(varX_.c_str()) ;
  
  hist_ -> GetXaxis() -> SetTitleOffset(1.0) ;
  hist_ -> GetXaxis() -> SetTitleFont(132) ;
  hist_ -> GetXaxis() -> SetTitleSize(0.035) ;
  hist_ -> GetXaxis() -> SetLabelFont(132) ;
  hist_ -> GetXaxis() -> SetLabelSize(0.035) ;
  //hist_ -> GetXaxis() -> SetNdivisions(3,false) ;
  //hist_ -> GetXaxis() -> SetNdivisions(3,false) ;

  if(varY_.find("dcp") != std::string::npos)
    hist_ -> GetYaxis() -> SetTitle("#delta_{CP}") ;
  else if(varY_.find("theta13") != std::string::npos)
    hist_ -> GetYaxis() -> SetTitle("sin^{2}(#theta_{13})") ;
  else if(varY_.find("theta23") != std::string::npos)
    hist_ -> GetYaxis() -> SetTitle("sin^{2}(#theta_{23})") ;
  else if(varY_.find("dm23") != std::string::npos)
    hist_ -> GetYaxis() -> SetTitle("#Delta m_{32}^{2}") ;     
  else
    hist_ -> GetYaxis() -> SetTitle(varY_.c_str()) ;
  
  hist_ -> GetYaxis() -> SetTitleOffset(1.3) ;
  hist_ -> GetYaxis() -> SetTitleFont(132) ;
  hist_ -> GetYaxis() -> SetTitleSize(0.035) ;
  hist_ -> GetYaxis() -> SetLabelFont(132) ;
  hist_ -> GetYaxis() -> SetLabelSize(0.035) ;
  hist_ -> GetZaxis() -> SetLabelFont(132) ;
  hist_ -> GetZaxis() -> SetLabelSize(0) ;
}

/// A function to make pretty legends
void makePrettyLegend(TLegend* legend_)
{
  legend_ -> SetBorderSize(0);
  legend_ -> SetFillStyle(0);
  legend_ -> SetTextFont(132);
  legend_ -> SetTextSize(0.035);
}

/// A function to make pretty TGraph
void makePrettyGraph(TGraph* graph_, TH2D* hist2d_, std::string option_)
{
  graph_ -> GetXaxis() -> SetTitle(hist2d_ -> GetXaxis() -> GetTitle());
  graph_ -> GetYaxis() -> SetTitle(hist2d_ -> GetYaxis() -> GetTitle());

  graph_ -> SetTitle("") ;
  graph_ -> SetLineWidth(2);
  graph_ -> SetLineColor(kWhite);

  if(option_ == "68")
    graph_ -> SetLineStyle(2);

  else if(option_ == "90")
    graph_ -> SetLineStyle(1);

  else if(option_ == "bestfit")
    {
      graph_ -> SetMarkerColor(kWhite);
      graph_ -> SetMarkerStyle(21);
    }
  else if(option_ == "input")
    {
      graph_ -> SetMarkerColor(kAzure-2);
      graph_ -> SetMarkerStyle(34);
      graph_ -> SetMarkerSize(2);
    }
}

/// A function to compute where the 2D integral stops
void getCredibleInterval2D(TH2D *llh_2dhist_, double &contour68_entries_, double &contour90_entries_)
{
  std::cout << "----- Getting 2D credible interval" << std::endl;

  /// Copy the histogram as we are going to modify the content
  TH2D *llh_scan_hist   = (TH2D*)llh_2dhist_ -> Clone("llh_scan_hist");

  /// Variables to loop over bins of the histogram
  double integral = llh_scan_hist -> Integral();
  double sum_entries = 0;

  /// Variables to save where 68% and 90% contour are reached
  double contour68_entries = 0;
  double contour90_entries = 0;

  /// Loop on the histogram bins with highest number of entries until covered 90%
  while ((sum_entries / float(integral)) < 0.9)
    {
      /// Get bin of highest content and save the number of entries reached so far
      int max_entries_bin = llh_scan_hist -> GetMaximumBin();
      double max_entries = llh_scan_hist -> GetMaximum();
      sum_entries = sum_entries + max_entries ;

      /// If the number of entries did not reach 68% yet
      if (sum_entries / float(integral) < 0.68)
	{
	  /// Save the bin content in which 68% is reached
	  contour68_entries = max_entries ;

	  /// Replace bin value by -1 so it is not looped over as being maximum bin again
	  llh_scan_hist -> SetBinContent(max_entries_bin, -1.);
	}

      /// If the number of entries is between 68% and 90%
      if ((sum_entries / float(integral) < 0.9) && (sum_entries / float(integral) > 0.68))
	{
	  /// Save the bin content in which 90% is reached
	  contour90_entries = max_entries;

	  /// Replace bin value by -3 so it is not looped over as being maximum bin again
	  llh_scan_hist -> SetBinContent(max_entries_bin, -3.);
	}
    }

  /// Return the bin value of max entries to draw contours
  contour90_entries_ = contour90_entries ;
  contour68_entries_ = contour68_entries ;

  std::cout << "  Entries level for 68% contour = " << contour68_entries << std::endl 
	    << "  Entries level for 90% contour = " << contour90_entries << std::endl ;

}

/// The main function
void contours_2d_app(std::string inputFileName_, std::string outputFileName_,
		 std::string varX_branch_, std::string varY_branch_, 
		 int mh_=0, int crop_dm32_=0, bool dataFit_=true, 
		 double trueX_=-999, double trueY_=-999)
{
  ///---------------------------------------------------------------------
  ///  FILL TH2D
  ///---------------------------------------------------------------------
  
  /// Get the tree with posterior oscillation entries
  TFile *inputFile = new TFile(inputFileName_.c_str(), "READ");
  if(!inputFile)
    {
      std::cerr << "Error : input file " << inputFileName_ << " not found. Exiting now. " << std::endl ;
      return ;
    }
  TTree *oscPosteriorTree = (TTree*)inputFile -> Get("osc_posteriors") ;
  if(!oscPosteriorTree)
    {
      std::cerr << "Error : TTree osc_poseriors not found in " << inputFileName_ << ". Exiting now." << std::endl ;
      return ;
    }

  /// Access branches with posterior oscillation entries
  double varX;
  double varY;
  double dm32;
    
  oscPosteriorTree -> SetBranchAddress(varX_branch_.c_str(), &varX) ;
  oscPosteriorTree -> SetBranchAddress(varY_branch_.c_str(), &varY) ;
  /*
  if((varX_branch_.find("dm23") == std::string::npos) && (varY_branch_.find("dm23") == std::string::npos))
    oscPosteriorTree -> SetBranchAddress("dm23",      &dm32) ;
  else if (varX_branch_.find("dm23") != std::string::npos)
    dm32 = varX ;
  else if (varY_branch_.find("dm23") != std::string::npos)
    dm32 = varY ;
*/
  /// Get bining from default histogram
  TCanvas* tmp_canv = new TCanvas("tmp_canv", "tmp_canv", 0, 0, 800,630) ;
    
  oscPosteriorTree -> Draw(varX_branch_.c_str()) ;
  int nBins_varX = oscPosteriorTree -> GetHistogram() -> GetNbinsX() ;
  double binLow_varX = oscPosteriorTree -> GetHistogram() -> GetBinLowEdge(1) ;
  double binHigh_varX = oscPosteriorTree -> GetHistogram() -> GetBinLowEdge(oscPosteriorTree -> GetHistogram() -> GetNbinsX()) ;

  oscPosteriorTree -> Draw(varY_branch_.c_str()) ;
  int nBins_varY = oscPosteriorTree -> GetHistogram() -> GetNbinsX() ;
  double binLow_varY = oscPosteriorTree -> GetHistogram() -> GetBinLowEdge(1) ;
  double binHigh_varY = oscPosteriorTree -> GetHistogram() -> GetBinLowEdge(oscPosteriorTree -> GetHistogram() -> GetNbinsY()) ;

  delete tmp_canv ;

  /// Some variables need specific bin treatment

  /// dcp bounds at -pi, pi
  if(varX_branch_.find("dcp") != std::string::npos)
    {
      binLow_varX  = -1.*TMath::Pi() ;
      binHigh_varX = TMath::Pi() ;
    }
  if(varY_branch_.find("dcp") != std::string::npos)
    {
      binLow_varY  = -1.*TMath::Pi() ;
      binHigh_varY = TMath::Pi() ;
    }

  /// special temporary bounds
  if(varX_branch_.find("theta23") != std::string::npos)
    {
      binLow_varX  = 0.3 ; 
      binHigh_varX = 0.7 ;
    }
   if(varY_branch_.find("theta23") != std::string::npos)
    {
      binLow_varY  = 0.3 ;
      binHigh_varY = 0.7 ;
    }
  if(varX_branch_.find("theta13") != std::string::npos)
    {
      binLow_varX  = 0. ; 
      binHigh_varX = 0.1 ;
    }
   if(varY_branch_.find("theta13") != std::string::npos)
    {
      binLow_varY  = 0. ;
      binHigh_varY = 0.1 ;
    }

   if(varY_branch_.find("dm23") != std::string::npos) 
     binHigh_varY = 0.003 ;
  
  /// dm32 needs finner binning, other need coarser (how coarse depends on MH)
  /*
   if(varX_branch_.find("dm23") != std::string::npos) 
    nBins_varX *= 2 ; 
  else
    {
      if(mh_ == 0)
	  nBins_varX /= 1.5 ; 
      else
	  nBins_varX /= 2 ; 
    }

  if(varY_branch_.find("dm23") != std::string::npos) 
    nBins_varY *= 2 ; 
  else
    {
      if(mh_ == 0)
	  nBins_varY /= 1.5 ; 
      else
	  nBins_varY /= 2 ; 
    }
*/
  
  std::cout << "----- Binning used : " << std::endl
	    << varX_branch_ << " : " << nBins_varX << " bins / min X = " << binLow_varX << " / max Y = " << binHigh_varX  << std::endl
    	    << varY_branch_ << " : " << nBins_varY << " bins / min Y = " << binLow_varY << " / max Y = " << binHigh_varY  << std::endl ;
    
  /// Create the TH2D
  TH2D *posterior_hist2d ;
  posterior_hist2d  = new TH2D("posterior_density", "",
			       nBins_varX, binLow_varX, binHigh_varX,
			       nBins_varY, binLow_varY, binHigh_varY) ;

    //std::cout << " TEST KUUUURWA "<<" bins / min Y = " << binLow_varY << " / max Y = " << binHigh_varY  << std::endl ;  

  /// Parse the tree to fill the TH2D with oscillation entries
  std::cout << "----- Filling TH2D with " << oscPosteriorTree->GetEntries() << " entries "<< std::endl ;
  for (int iEnt = 0; iEnt < oscPosteriorTree->GetEntries() ; iEnt ++)
    {
      oscPosteriorTree -> GetEntry(iEnt);

      if(mh_ > 0 && dm32 < 0.)
	continue ;
      else if(mh_ < 0 && dm32 > 0.)
	continue ;
      
      posterior_hist2d -> Fill(varX, varY);
    } /// end of loop over tree entries

  /// Sometimes the bin edges changes so this set them back 
  posterior_hist2d -> GetXaxis() -> SetLimits(binLow_varX, binHigh_varX) ;
  posterior_hist2d -> GetYaxis() -> SetLimits(binLow_varY, binHigh_varY) ;


  ///Get the name of the file in which we will save the contours (if empty use input file to create name)
  std::string outputFileName_noExt ;

  if(outputFileName_.empty()) {
    std::string nameMH = "" ;
    
    if(mh_ > 0)
      nameMH = "_nh" ;
    else if(mh_ < 0)
      nameMH = "_ih" ;
    else
      nameMH = "_bothMH" ;
    
    outputFileName_noExt = getNameNoExt(inputFileName_, ".root"); 
    outputFileName_noExt = outputFileName_noExt + "_" + varX_branch_ + "_" + varY_branch_ + nameMH  ; 
    outputFileName_ = outputFileName_noExt + ".root" ;
  }
  std::cout << "----- Saving graphs in " << outputFileName_ << std::endl ;
  
  TFile *outFile = new TFile(outputFileName_.c_str(),"RECREATE");

  
  ///---------------------------------------------------------------------
  ///  MAKE CREDIBLE INTERVAL
  ///---------------------------------------------------------------------
  
  /// Get the entries at which we draw the contour for the credible interval
  double contour90_entries, contour68_entries ;
  getCredibleInterval2D(posterior_hist2d, contour90_entries, contour68_entries) ;

    /// An ackward hack where we need to save this in arrays so we can use the function SetContour from ROOT
  /// Ideally to declare as an array from the start, but getInterval2D did not like it as an argument
  double contours_ci_array[2] ;
  contours_ci_array[0] = contour68_entries ;
  contours_ci_array[1] = contour90_entries ;

  TCanvas *credible_interval_canvas = new TCanvas("appearance_credible_interval", "appearance_credible_interval", 0, 0, 800,630);
  makePrettyCanvas(credible_interval_canvas) ;

  /// We use the function SetContour to circle all the events at the level specifield
  /// Then we HAVE TO draw the list of contours and update the Canvas so we can extract them after
  TH2D *posterior_ci_hist2d = (TH2D*)posterior_hist2d -> Clone() ;
  makePrettyTh2d(posterior_hist2d, varX_branch_, varY_branch_) ;

  posterior_ci_hist2d -> Smooth(1) ;
  posterior_ci_hist2d -> SetContour(2, contours_ci_array);
  posterior_ci_hist2d -> Draw("CONT LIST");
  credible_interval_canvas -> Update() ;

  /// Scale the histograms so it shows the posterior probability and draw
  posterior_hist2d -> Scale(1. / posterior_hist2d -> Integral(), "width") ;

  /// Rescale dm32 axis to a specific mh if desired
  /*
  if((varX_branch_.find("dm23") != std::string::npos) && (crop_dm32_ != 0))
    {
      if (crop_dm32_ > 0)
	posterior_hist2d -> GetXaxis() -> SetRangeUser(2E-3, 3E-3) ;
      else
	posterior_hist2d -> GetXaxis() -> SetRangeUser(-3E-3, -2E-3) ;
    }
  if((varY_branch_.find("dm23") != std::string::npos) && (crop_dm32_ != 0))
    {
      if (crop_dm32_ > 0)
	posterior_hist2d -> GetYaxis() -> SetRangeUser(2E-3, 3E-3) ;
      else
	posterior_hist2d -> GetYaxis() -> SetRangeUser(-3E-3, -2E-3) ;
    }
*/
  posterior_hist2d -> Draw("COLZ") ;
  //  std::string obj_name = varX_branch_ + "_" + varY_branch_ + "_posterior"  ;
  std::string obj_name = "2d_posterior"  ;
  posterior_hist2d -> Write(obj_name.c_str()) ;

  /// In order to save the contours as graph, we need to get the list of contours with this very useful function
  TObjArray *contours_ci_objects = (TObjArray*)gROOT -> GetListOfSpecials() -> FindObject("contours");

  /// Check that we indeed extracted some contours
  if (contours_ci_objects == NULL) {
    std::cerr << "Error : no contour extracted. Exiting now. " << std::endl ;
    return ;
  }

  /// Now we are going to iterate over the list of 90% credible intervals and saved them as graphs
  TList *list90 = (TList*)contours_ci_objects -> At(0);
  TIter nextCI90(list90);
  int iterator = 0;

  TGraph *contour_ci_graph ;
  TLegend *legend_ci = new TLegend(0.50, 0.7, 0.75, 1) ;
  makePrettyLegend(legend_ci) ;

  while ((contour_ci_graph = (TGraph*)nextCI90()))
    {
      std::stringstream name_CI90 ;
      name_CI90 << "g90_" << iterator ;

      makePrettyGraph(contour_ci_graph, posterior_hist2d, "90") ;
      contour_ci_graph -> Write(name_CI90.str().c_str());

      if(iterator==0) 
        legend_ci -> AddEntry(contour_ci_graph, "90% Credible interval", "lf") ;
      
      contour_ci_graph -> Draw("SAME.CONT3.LIST") ;

      iterator ++;
    }

  /// Now we are going to iterate over the list of 68% confidence limit and saved them as graphs
  TList *list68 = (TList*)contours_ci_objects -> At(1);
  TIter nextCI68(list68);
  iterator = 0;

  while ((contour_ci_graph = (TGraph*)nextCI68()))
    {
      std::stringstream name_CI68 ;
      name_CI68 << "g68_" << iterator ;

      makePrettyGraph(contour_ci_graph, posterior_hist2d, "68") ;
      contour_ci_graph -> Write(name_CI68.str().c_str());

      if(iterator==0) 
        legend_ci -> AddEntry(contour_ci_graph, "68% Credible interval", "lf") ;
      
      contour_ci_graph -> Draw("SAME.CONT3.LIST") ;

      iterator ++;
    }
  
  /// Find best fit point (aka max posterior proba)
  int max_llh_bin = posterior_hist2d -> GetMaximumBin();
  int max_llh_binX, max_llh_binY, max_llh_binZ ;
  posterior_hist2d -> GetBinXYZ(max_llh_bin,  max_llh_binX, max_llh_binY, max_llh_binZ) ;
  double varX_max_llh, varY_max_llh ; 
  varX_max_llh = posterior_hist2d -> GetXaxis() -> GetBinCenter(max_llh_binX) ;
  varY_max_llh = posterior_hist2d -> GetYaxis() -> GetBinCenter(max_llh_binY) ;
  std::cout << "----- Posterior probabilities at best fit : " << std::endl
	    << "MaCh3 best fit point:" << varX_branch_ << "  = " << varX_max_llh
	    << "  /  " << varY_branch_ << " = " << varY_max_llh 
	    << "  /  posterior in bin = " <<  posterior_hist2d -> GetBinContent(max_llh_bin) 
	    << std::endl;

  /// Create a TGraph to draw and save the best fit point
  TGraph *best_fit_graph = new TGraph(1);
  best_fit_graph -> SetPoint(0, varX_max_llh, varY_max_llh) ;
  makePrettyGraph(best_fit_graph, posterior_hist2d, "bestfit") ;
  best_fit_graph -> Draw("P SAME");
  best_fit_graph -> Write("Bestfit") ;
  legend_ci -> AddEntry(best_fit_graph, "2D posterior mode", "pf") ;

  /// Create a TGraph to draw and save the input point
  TGraph *input_graph = new TGraph(1);
  if (!(trueX_ == -999 && trueY_ == -999)) {
    std::cout << "  MaCh3 input point   : " << varX_branch_ << " = " << trueX_
	      << "  /  " << varY_branch_ << " = " << trueY_ 
	      << "  /  posterior in bin = " <<  posterior_hist2d -> GetBinContent(posterior_hist2d -> FindBin(trueX_, trueY_)) 
	      << std::endl;
    std::cout <<  "Posterior (Best fit MaCh3) / Posterior (true): " 
	      << (posterior_hist2d -> GetBinContent(max_llh_bin) ) / (posterior_hist2d -> GetBinContent(posterior_hist2d -> FindBin(trueX_, trueY_))) 
	      << std::endl ;

    makePrettyGraph(best_fit_graph, posterior_hist2d, "input") ;
    input_graph -> SetPoint(0, trueX_, trueY_) ;

    input_graph -> Draw("P SAME");
    input_graph -> Write("input") ;
    if(dataFit_)
      legend_ci -> AddEntry(input_graph, "4D posterior mode", "p") ;
    else
      legend_ci -> AddEntry(input_graph, "input point", "p") ;
  }

  /// Draw and save legend
  legend_ci -> Draw("SAME") ;
  legend_ci -> Write("legend_ci") ;

  /// Save canvas
  obj_name = varX_branch_ + "_" + varY_branch_ + "_ci"  ;
  //  obj_name = "2d_ci"  ;
  credible_interval_canvas -> Write(obj_name.c_str()) ;
  saveCanvas(credible_interval_canvas, outputFileName_, "_ci") ;

  
  ///---------------------------------------------------------------------
  ///  MAKE CONFIDENCE INTERVAL
  ///---------------------------------------------------------------------
   
  std::cout << "----- Getting 2D confidence interval" << std::endl;

  /// Create a new TH2D that we fill with chi2 distribution instead of likelihood
  TH2D *chi2_hist2d = (TH2D*)posterior_hist2d -> Clone() ;
  makePrettyTh2d(chi2_hist2d, varX_branch_, varY_branch_) ;

  int max_posterior = chi2_hist2d -> GetMaximum();

  for (int iBinX = 1 ; iBinX <= chi2_hist2d -> GetNbinsX() ; iBinX ++) 
    {                                                                
      for (int iBinY = 1 ; iBinY <= chi2_hist2d -> GetNbinsY() ; iBinY ++) 
	{
	  double posterior = chi2_hist2d -> GetBinContent(iBinX, iBinY) ;

	  /// If the posterior = 0 we need to set it to 1 so the logarithm can be computed
	  if(posterior == 0.)
	    posterior = 1. ;

	  /// For each bin replace the likelihood by the chi2
	  chi2_hist2d -> SetBinContent(iBinX, iBinY, (-2. * TMath::Log(posterior/max_posterior) ) ) ;
	} 
    }

  /// Where we are going to draw the confidence limit
  TCanvas *confidence_interval_canvas = new TCanvas("confidence_interval", "confidence_interval", 0, 0, 800,630) ;
  makePrettyCanvas(confidence_interval_canvas) ;

  /// Get the entries at which we draw the contour for the confidence limit
  TH2D *chi2_cl_hist2d = (TH2D*)chi2_hist2d -> Clone() ;
  chi2_cl_hist2d -> Smooth(1) ;   
  double min_chi2 = chi2_cl_hist2d -> GetMinimum();
  double contours_cl_array[2] ;
  contours_cl_array[0] = min_chi2 + 2.30 ; 
  contours_cl_array[1] = min_chi2 + 4.61 ;

  /// We use the function SetContour to circle all the events at the level specifield
  /// Then we have to draw the list of contours and update the Canvas so we can extract them after
  chi2_cl_hist2d -> SetContour(2, contours_cl_array);
  chi2_cl_hist2d -> Draw("CONT LIST");
  confidence_interval_canvas -> Update() ;

  chi2_hist2d -> Draw("COLZ") ;
  obj_name = varX_branch_ + "_" + varY_branch_ + "_chi2"  ;
  //obj_name = "2d_chi2"  ;
  chi2_hist2d -> Write(obj_name.c_str()) ;
  
    /// In order to save the contours as graph, we need to get the list of contours with this very useful function
  TObjArray *contours_cl_objects = (TObjArray*)gROOT -> GetListOfSpecials() -> FindObject("contours");

  /// Check that we indeed extracted some contours
  if (contours_cl_objects == NULL) {
    std::cerr << "Error : no contour extracted. Exiting now. " << std::endl ;
    return ;
  }

  /// Now we are going to iterate over the list of 90% confidence limit and saved them as graphs
  TList *listCL90 = (TList*)contours_cl_objects -> At(1);
  TIter nextCL90(listCL90);
  iterator = 0;

  TGraph *contour_cl_graph ;
  TLegend *legend_cl = new TLegend(0.50, 0.75, 0.75, 1.0) ;
  makePrettyLegend(legend_cl) ;

  while ((contour_cl_graph = (TGraph*)nextCL90()))
    {
      std::stringstream name_CL90 ;
      name_CL90 << "g90_conf_" << iterator ;

      makePrettyGraph(contour_cl_graph, posterior_hist2d, "90") ;
	
      //std::cout << "test while !!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
      
      
      contour_cl_graph -> Write(name_CL90.str().c_str());
      if(iterator==0)
      {
        //std::cout << "TEST KUUUUUUURSEBELE"<<std::endl;
         legend_cl -> AddEntry(contour_cl_graph, "90% Confidence interval", "lf") ;
      }

      contour_cl_graph -> Draw("SAME.CONT3.LIST") ;

      iterator ++;
    }

    /// Now we are going to iterate over the list of 68% confidence limit and saved them as graphs
  TList *listCL68 = (TList*)contours_cl_objects -> At(0);
  TIter nextCL68(listCL68);
  iterator = 0;

  while ((contour_cl_graph = (TGraph*)nextCL68()))
    {
      std::stringstream name_CL68 ;
      name_CL68 << "g68_conf_" << iterator ;

      makePrettyGraph(contour_cl_graph, posterior_hist2d, "68") ;
      
      contour_cl_graph -> Write(name_CL68.str().c_str());
  
      if(iterator==0) 
        legend_cl -> AddEntry(contour_cl_graph, "68% Confidence interval", "lf") ;

      contour_cl_graph -> Draw("SAME.CONT3.LIST") ;

      iterator ++;
    }

    /// Draw best fit and input point
  best_fit_graph -> Draw("P SAME");
  legend_cl -> AddEntry(best_fit_graph, "2D posterior mode", "pf") ;

  if (!(trueX_ == -999 && trueY_ == -999) && !dataFit_) {
    input_graph -> Draw("P SAME");
    legend_cl -> AddEntry(input_graph, "input point", "p") ;
  }
  else if (!(trueX_ == -999 && trueY_ == -999) && dataFit_) {
    input_graph -> Draw("P SAME");
    legend_cl -> AddEntry(input_graph, "4D posterior mode", "p") ;
  }

  /// Draw and save legend
  legend_cl -> Draw("SAME") ;
  legend_cl -> Write("legend_cl") ;
  obj_name = varX_branch_ + "_" + varY_branch_ + "_cl"  ;
  confidence_interval_canvas -> Write(obj_name.c_str()) ;
  saveCanvas(confidence_interval_canvas, outputFileName_, "_cl") ;
  
}
