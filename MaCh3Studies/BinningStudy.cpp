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

void BinningStudy();

int  main()
{
    BinningStudy();

    return 0;  
    
}

void BinningStudy()
{
    std::string inputFile = "blarb";
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 1000,1000);
    gPad->SetGrid();
    gStyle->SetPalette(51);
    gStyle->SetOptStat(0); //Set 0 to disable statystic box

    
    const int nsamples = 22;
    
    double sampleEnum[nsamples] = {7,8,10,12,13,31,32,34,36,37, 59,60,61, 65,66,67, 71,72,73, 77,78,79};
    TString sampleName[nsamples] = {
        "FGD1_numuCC_0pi_0_protons_no_photon",
        "FGD1_numuCC_0pi_N_protons_no_photon",
        "FGD1_numuCC_1pi_no_photon",
        "FGD1_numuCC_other_no_photon",
        "FGD1_numuCC_photon",
        "FGD2_numuCC_0pi_0_protons_no_photon",
        "FGD2_numuCC_0pi_N_protons_no_photon",
        "FGD2_numuCC_1pi_no_photon",
        "FGD2_numuCC_other_no_photon",
        "FGD2_numuCC_photon",
    
         "FGD1_anti-numuCC_0pi",
         "FGD1_anti-numuCC_1pi",
         "FGD1_anti-numuCC_other",
         "FGD2_anti-numuCC_0pi",
         "FGD2_anti-numuCC_1pi",
         "FGD2_anti-numuCC_other",
         "FGD1_NuMuBkg_CC0pi_in_AntiNu_Mode",
         "FGD1_NuMuBkg_CC1pi_in_AntiNu_Mode",
         "FGD1_NuMuBkg_CCother_in_AntiNu_Mode",
         "FGD2_NuMuBkg_CC0pi_in_AntiNu_Mode",
         "FGD2_NuMuBkg_CC1pi_in_AntiNu_Mode",
         "FGD2_NuMuBkg_CCother_in_AntiNu_Mode"
    };

     TH2Poly* Binning[nsamples];  
     TFile * filePoly = new TFile("PolyBinning.root","RECREATE");

     for(int s = 0; s<nsamples; s++)
     {
        std::vector<double> BinArray_x;
        std::vector<double> BinArray_y;

        TString histname = sampleName[s];
        
        Binning[s] = new TH2Poly();
        Binning[s]->SetName(histname);
        Binning[s]->SetTitle(histname);
        double xmax = 50;
        double xmin = 0;
        //double ymax = -0.995;
        double ymax = -0.5;
        double ymin = -1;

        std::cout<<" new sample "<<std::endl;
        for(unsigned i=0; i < 600; i++)
        {            
            ymax = -0.5;
            ymin = -1;
            std::cout<<" new mom bin "<<xmax<<std::endl;
            for(unsigned j=0; j < 103; j++)
            {
                double binofx[] = {xmin, xmax, xmax, xmin};
                double binofy[] = {ymin, ymin, ymax, ymax};
            
                Binning[s]->AddBin(4,binofx,binofy);
                if(ymax == 0.5 )
                {
                    ymax = 0.5 ;
                    ymin = 0.495;
                }
                
                if( ymax >= 0.5 )
                {
                    ymax += 0.005;
                    ymin += 0.005;
                }
                else
                {
                    ymax += 0.5;
                    ymin += 0.5;
                }
                
                
            }
            xmax += 50;
            xmin += 50;
        }
            filePoly->cd();
            Binning[s]->Write();
     }
      filePoly->Close();  

}
