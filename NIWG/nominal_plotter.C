double get_true_max(TH1* hist){
  double maxVal = 0;
  for (int x = 0; x < hist->GetNbinsX(); ++x){
    double thisVal = hist->GetBinContent(x+1)+hist->GetBinError(x+1);
    if (thisVal > maxVal) maxVal = thisVal;
  }
  return maxVal;
}

void make_basic_plot(std::string input_file_name, std::string input_file_name2, std::string measurement_name, std::string output_plot_name){

  gROOT->SetBatch(1);
  
  // Options to make the histogram prettier
  gStyle->SetLineWidth(3);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetOptFit(0);
  TGaxis::SetMaxDigits(3);
  
  gStyle->SetTextSize(0.06);
  gStyle->SetLabelSize(0.05,"xyzt");
  gStyle->SetTitleSize(0.06,"xyzt");
  
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetNdivisions(505, "XY");
  
  // ROOT sometimes tries to ignore what you tell it...
  gROOT ->ForceStyle();
  
  // Make a canvas (where we will draw the histogram)
  TCanvas *can = new TCanvas("can", "can", 800, 800);
  
  // Open the file
  TFile *in_file = new TFile(input_file_name.c_str());

  TFile *in_file2 = new TFile(input_file_name2.c_str());


  // Get the generator prediction histogram
  TH1D *mc_hist = (TH1D*)in_file->Get((measurement_name+"_MC").c_str());
  
  TH1D *mc_his2 = (TH1D*)in_file2->Get((measurement_name+"_MC").c_str());

  // Get the data histogram
  TH1D *data_hist = (TH1D*)in_file->Get((measurement_name+"_data").c_str());

  // This is a bit of a NUISANCE hack, the chisq between data and MC is stored as the MC histogram title
  std::string chisq = mc_hist->GetTitle();
  std::string chis2 = mc_his2->GetTitle();

  // Presentation is important
  mc_hist  ->SetLineWidth(3);
  mc_hist  ->SetLineColor(kRed);

  mc_his2->SetLineWidth(3);
  mc_his2->SetLineColor(kBlue);

  data_hist->SetLineWidth(3);
  data_hist->SetLineColor(kBlack);

  // Make a legend
  TLegend *leg = new TLegend(0.35, 0.82, 1.00, 0.99, "", "NDC");

  // By default ROOT legends can be ugly... make it nicer
  leg ->SetShadowColor(0);
  leg ->SetFillColor(0);
  leg ->SetLineWidth(0);
  leg ->SetTextSize(0.03);
  leg ->SetLineColor(kWhite);
  //leg ->SetNColumns(3);

  // The information to be conveyed
  leg ->AddEntry(data_hist, measurement_name.c_str(), "l");
  leg ->AddEntry(mc_hist, ("Genie (#chi^{2} = "+chisq+")").c_str(), "l");
  leg ->AddEntry(mc_his2, ("NuWro (#chi^{2} = "+chis2+")").c_str(), "l");

  // Sort out the maximum value
  double maxVal = get_true_max(data_hist);
  if (mc_hist->GetMaximum() > maxVal){
    maxVal = mc_hist->GetMaximum();
  }
	    
  // Note that all style options should be applied to the first histogram we draw
  // Add a small buffer to make it look better
  data_hist ->SetMaximum(maxVal*1.1);
  
  // Now draw everything on the canvas
  can ->cd();
  data_hist ->Draw();
  data_hist ->GetYaxis()->SetTitleOffset(0.9);
  mc_hist ->Draw("HIST SAME");
  mc_his2 ->Draw("HIST SAME");
  leg ->Draw("SAME");

  // Make the borders sensible
  gPad ->SetRightMargin(0.03);
  gPad ->SetTopMargin(0.2);
  gPad ->SetBottomMargin(0.15);
  gPad ->SetLeftMargin(0.15);
  can ->Update();

  // This actually makes the plot
  can ->SaveAs(output_plot_name.c_str());
  return;
};
    

// ROOT CINT expects a function with the same name as the script
// A feature is that subsequent command line arguments are passed to this function
void nominal_plotter(){

  std::string input_file_name  = "nominal_GENIEv3_example.root";
  std::string input_file_name2  = "nominal_NUWro_example.root";
  std::string samples[] = {"MicroBooNE_CC1Mu1p_XSec_1DProtonCosTheta_nu"};
  
  for (const auto& sample : samples) {
    std::string output_plot_name = "plots/nominal_"+sample+"_GENIEv3.png";
    make_basic_plot(input_file_name, input_file_name2, sample, output_plot_name);
  }
  
  return;
}
    
