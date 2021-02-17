// Convert ND280 binning
// Compiled because that means we can link to psyche and avoid some hard-coding!
// g++ `root-config --cflags` -g -o ConvertND280Bin ConvertND280Bin.cpp -I`root-config --incdir` -I../psycheinc `root-config --glibs --libs` -L../lib
// ********************************
// ______WARNING______
// THE ORDER OF SAMPLES IN THE FOR LOOP MATTERS AND ____IS HARD CODED____
// FOR 2017 ANALYSES THE SAMPLE ORDERING WAS FGD1 SAMPLES, FGD2 SAMPLES, GOING __AGAINST__ THE PSYCHE NUMBERING
// FOR 2018 ANALYSES THE SAMPLE ORDERING FOLLOWED PSYCHE NUMBERING
// CHECK GIT LOG TO SEE WHAT WAS DONE
// ______END WARNING______

#include <iostream>
#include <iomanip>
#include <string>

#include <TH2Poly.h>
#include <TH2D.h>
#include "TFile.h"
#include "TAxis.h"
#include "TObjArray.h"
#include "TH1I.h"
#include "TVectorD.h"
#include "TMatrixDSym.h"

//TODO terribly hardcoded
#include "/mnt/home/kskwarczynski/T2K/work/protonPlayground/psyche/psycheEventModel/v3r33/src/SampleId.cxx"

void ConvertBANFFcovToMaCh3(TString inputFile)
{

  TFile *file = new TFile(inputFile.Data(), "READ");
  if (file->IsZombie()) 
  {
    std::cerr << "Can't find file " << inputFile.Data() << std::endl;
    std::cerr << "I'll just have to hang up!" << std::endl;
    exit(-1);
  }

  // Check the input file: unfortunately need to change this code for every new input covariance
  // Any of the input files would be fine to check, I've just chosen the GOF for no reason
  TH1D *temp = (TH1D*)(file->Get("Nominal"));
  if (temp->GetNbinsX() != 702) {
    std::cout << "This executable is hard-coded for 2016/2017 analyses" << std::endl;
    std::cout << "Am expecting 702 bins in total, I found " << temp->GetNbinsX() << std::endl;
    //throw;
  }
  TDirectory *DetBinDirectory = (TDirectory*)file->Get("AxisForCov"); 
  TDirectory *FitBinDirectory = (TDirectory*)file->Get("AxisForFit"); 
    
  const int psycheSamples = SampleId::kNSamples;
  TObjArray* sample_poly = new TObjArray();
  std::cout<<"looping over "<<psycheSamples<<" psyche samples"<<endl;

  // All the types that MaCh3 need
  // This holds the offset in going from a bin on x and y axis to a global bin
  TH1I* offset = new TH1I("offset", "offset", psycheSamples, 0, psycheSamples);

  // This holds the actual covariance, just read straight out of the file
  TMatrixDSym *nddet_cov = (TMatrixDSym*)(file->Get("Covariance_Matrix")->Clone());
  // This holds the central values, just read straight out of the file
  TVectorD* det_weight = (TVectorD*)(file->Get("Mean_Value")->Clone());

  // This is the dummy for when we have a psyche sample but it isn't included in the switch below (so isn't included as a sample in ND280 fits!)
  TAxis *dummy = NULL;

  // Have a counter that stores the offset for each sample
  int offsetCounter = 0;

  // Loop over the psyche samples
  // According to Simon the ordering of the bins is FGD1 CC0pi, CC1pi... FGD2 CC0pi, CC1pi...
  //
  // So am hacking this together somewhat: loop over the psyche sample, picking out the FGD1 selections only
  // Then do the same loop again but pick out the FGD2 selections instead
  // This calls two for loops which are identical _EXCEPT_ for the cases in the switch
  
  for (int i = 0; i < psycheSamples; ++i) {
    std::string Samplename = SampleId::ConvertSample(i);
    for(std::string::iterator it = Samplename.begin(); it != Samplename.end(); ++it)
    {
        if(*it == ' ') 
        {
            *it = '_';
        }
    }
    std::string xaxisName = Samplename+"_p_axis";
    std::string yaxisName = Samplename+"_th_axis";
    
    // Make the x axis from the momentum of lepton
    TAxis* xaxis;
    // Make the y axis from the cos theta of lepton
    TAxis* yaxis;

    xaxis = (TAxis*)DetBinDirectory->Get( xaxisName.c_str() );
    yaxis = (TAxis*)DetBinDirectory->Get( yaxisName.c_str() );

    // Need the number of total bins for the selection
    // This is needed because there's an "offset" histogram in MaCh3
    // This histogram stores where each selection's bins start in the global bin numbering
    // The global bin numbering runs from 0~700, where the first n bins are one selection, next bins are another selection, and so on
    std::string name = SampleId::ConvertSample(i);
    if (yaxis != NULL && xaxis != NULL) {
      int size = xaxis->GetNbins()*yaxis->GetNbins();
      std::cout << Samplename << ":" << std::endl;
      std::cout << std::setw(10) << "offset: " << offsetCounter << std::endl;
      std::cout << std::setw(10) << "xaxis: " << xaxis->GetNbins() << std::endl;
      std::cout << std::setw(10) << "yaxis: " << yaxis->GetNbins() << std::endl;
      std::cout << std::setw(10) << "nbins: " << size << std::endl;
      std::cout << std::endl;

        TString histname = Samplename.c_str();
        TH2Poly *poly = new TH2Poly();
        poly->SetName(histname);
        poly->SetTitle(histname);
          
        double xmax, xmin, ymax, ymin;
        
        for(int ix=1; ix<=xaxis->GetNbins(); ix++)
        {
            xmax = xaxis->GetBinUpEdge(ix);
            xmin = xaxis->GetBinLowEdge(ix);
            for(int iy=1; iy<=yaxis->GetNbins(); iy++)
            {
                ymax = yaxis->GetBinUpEdge(iy);
                ymin = yaxis->GetBinLowEdge(iy);
                double binofx[] = {xmin, xmax, xmax, xmin};
                double binofy[] = {ymin, ymin, ymax, ymax};
	  
                poly->AddBin(4,binofx,binofy);
            }
        }
        sample_poly->AddAtAndExpand(poly, i);
      
      offset->SetBinContent(i+1, offsetCounter);
      offsetCounter += size;
    }
    offset->GetXaxis()->SetBinLabel(i+1, name.c_str());
  }

  std::string outputName = inputFile.Data();
  while (outputName.find(".") != std::string::npos) {
    outputName = outputName.substr(0, outputName.find("."));
  }
  outputName += "_convertedToMaCh3.root";

  TFile *output = new TFile(outputName.c_str(), "RECREATE");

  sample_poly->Write("det_polys", 1);
  offset->Write("offset");
  nddet_cov->Write("nddet_cov");
  det_weight->Write("det_weights");

  output->Close();
  
  
  
////////////////////////////////////////////////////////////////  
  TFile *outputPoly = new TFile("polybinning_BANFFTH2Ds_template.root", "RECREATE");
   for (int i = 0; i < psycheSamples; ++i) {
    std::string Samplename = SampleId::ConvertSample(i);
    for(std::string::iterator it = Samplename.begin(); it != Samplename.end(); ++it)
    {
        if(*it == ' ') 
        {
            *it = '_';
        }
    }
    std::string xaxisName = Samplename+"_p_axis";
    std::string yaxisName = Samplename+"_th_axis";
    
    // Make the x axis from the momentum of lepton
    TAxis* xaxis;
    // Make the y axis from the cos theta of lepton
    TAxis* yaxis;

    xaxis = (TAxis*)FitBinDirectory->Get( xaxisName.c_str() );
    yaxis = (TAxis*)FitBinDirectory->Get( yaxisName.c_str() );

    // Need the number of total bins for the selection
    // This is needed because there's an "offset" histogram in MaCh3
    // This histogram stores where each selection's bins start in the global bin numbering
    // The global bin numbering runs from 0~700, where the first n bins are one selection, next bins are another selection, and so on
        
    if (yaxis != NULL && xaxis != NULL) {
      int size = xaxis->GetNbins()*yaxis->GetNbins();

        TString histname = Samplename.c_str();
        TH2Poly *poly = new TH2Poly();
        poly->SetName(histname);
        poly->SetTitle(histname);
          
        double xmax, xmin, ymax, ymin;
        
        for(int ix=1; ix<=xaxis->GetNbins(); ix++)
        {
            xmax = xaxis->GetBinUpEdge(ix);
            xmin = xaxis->GetBinLowEdge(ix);
            for(int iy=1; iy<=yaxis->GetNbins(); iy++)
            {
                ymax = yaxis->GetBinUpEdge(iy);
                ymin = yaxis->GetBinLowEdge(iy);
                double binofx[] = {xmin, xmax, xmax, xmin};
                double binofy[] = {ymin, ymin, ymax, ymax};
	  
                poly->AddBin(4,binofx,binofy);
            }
        }
        //sample_poly->AddAtAndExpand(poly, i);
        poly->Write();
    }
  }
  outputPoly->Close();

  
  file->Close();

};
