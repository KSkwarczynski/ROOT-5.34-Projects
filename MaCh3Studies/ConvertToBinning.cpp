#include "TH1D.h"
#include "TH2Poly.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TFile.h"
#include "TKey.h"
#include "THStack.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TRandom3.h"
#include "TRandom3.h"
#include "omp.h"
#include <iostream>

// g++ `root-config --cflags`-std=c++11 -fopenmp -g -o  ConvertToBinning ConvertToBinning.cpp -I`root-config --incdir` `root-config --glibs --libs`

void Binning(std::string filename, std::string binPoly);
  double NoOverflowIntegral(TH2Poly* poly);
  
int main(int argc, char *argv[]) 
{
    std::string filename = argv[1];
        std::string binPoly = argv[2];
    Binning(filename, binPoly);
    return 0;
}
void Binning(std::string filename, std::string binPoly) {

   TFile *f1 = TFile::Open(filename.c_str());
   TFile *Binning = TFile::Open(binPoly.c_str());
   
   std::string dupa = filename + binPoly +".root";
   TFile *OutputDupa = TFile::Open(dupa.c_str(), "recreate");
   //Get all entries in input file
   std::string name;
   TIter next(f1->GetListOfKeys());
   TKey *key;
   
   //Main loop to get PriorPredicvitve Disribution
   while ((key = (TKey*)next())) 
   {
      std::string classname = std::string(key->GetClassName());  
      if (classname != "TH2Poly") continue;
      name = std::string(key->GetName()); 
      TH2Poly *poly = (TH2Poly*)key->ReadObj();
      TIter nextsub(gDirectory->GetListOfKeys());
       
      if (name.find("_W2Hist") != std::string::npos) continue;

        std::string pupa = "MC_" + name;
        
        TH2Poly *FluctHist = (TH2Poly*)(Binning->Get(name.c_str() ));
        FluctHist->Fill(0.0, 0.0, 0.0);
        std::cout<<pupa<<std::endl;
        double integral = 0;
        //#pragma omp parallel  for reduction(+:integral)
        for (int i = 1; i < poly->GetNumberOfBins()+1; ++i) 
        {
            //get bin and its edges
            TH2PolyBin* bin = (TH2PolyBin*)((TH2Poly*)poly)->GetBins()->At(i-1)->Clone();
            double ymas = bin->GetYMax() - 0.001;
            double xup = bin->GetXMax() - 10;
            double BinCont = bin->GetContent();
            integral += BinCont;
            int NewBin = FluctHist->FindBin(xup, ymas);
            BinCont += FluctHist->GetBinContent(NewBin);
            FluctHist->SetBinContent(NewBin, BinCont);

            delete bin;
        }
         std::cout<<"old  "<<integral<<std::endl;
         std::cout<<"new "<<NoOverflowIntegral(FluctHist)<<std::endl;
        
        OutputDupa->cd();
        FluctHist->Write(pupa.c_str());
   }

  OutputDupa->Close();    
                    
}



double NoOverflowIntegral(TH2Poly* poly) {
  // **************************************************

  double integral=0;

  for(int i=1; i<poly->GetNumberOfBins()+1; i++)
    {
      integral += poly->GetBinContent(i);
    }

  return integral;

} // end function
