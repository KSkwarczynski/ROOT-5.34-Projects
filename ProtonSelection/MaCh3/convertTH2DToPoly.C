#include <TH2Poly.h>
#include <TH2D.h>
#include <vector>
#include <TMath.h>
#include <TFile.h>
#include <TTree.h>
#include <THStack.h>
#include <iostream> 

void convertTH2DToPoly (){
   
  TFile * filePoly = new TFile("TH2PolyProton.root","RECREATE");
  
  const double nsamples = 1;
  TString sampleName[nsamples] = {"FGD1_numuCC_0pi_N_protons_no_photon"};

  const int BinX = 17;
  const int BinY = 13;
  double BinArray_x[BinX+1] = {0., 450., 500., 550, 600., 650, 700., 750, 800., 850, 900., 1000., 1200, 1500, 2000, 3000, 5000, 30000};
  double BinArray_y[BinY+1] = {-1., 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.90, 0.92, 0.94, 0.96, 0.98, 0.99, 1.};

  //const int BinX = 3;
  //const int BinY = 3;
  //double BinArray_x[BinX+1] = {0., 450., 500., 1000};
  //double BinArray_y[BinY+1] = {-1., 0.6, 0.99, 1.};
  
  for(int s = 0; s<nsamples; s++){

    TString histname = sampleName[s];

    TH2Poly *poly = new TH2Poly();
    poly->SetName(histname);
    poly->SetTitle(histname);
    double xmax, xmin, ymax, ymin;
    
    for(int i=0; i<BinX; i++)
    {
    xmax = BinArray_x[i+1];
    xmin =  BinArray_x[i];
    //std::cout<<" xmin "<<xmin<<" xmax "<<xmax<<std::endl;
	for(int j=0; j<BinY; j++)
	  {
	    ymax = BinArray_y[j+1];
	    ymin = BinArray_y[j];
        //std::cout<<" ymin "<<ymin<<" ymax "<<ymax<<std::endl;
	    double binofx[] = {xmin, xmax, xmax, xmin};
	    double binofy[] = {ymin, ymin, ymax, ymax};
	  
        
	    poly->AddBin(4,binofx,binofy);
	  }
    }

    filePoly->cd();
    poly->Write();
  }
    filePoly->Close();

}//end converToPoly

