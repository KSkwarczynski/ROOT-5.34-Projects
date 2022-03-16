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
#include <iostream>

// g++ `root-config --cflags`-std=c++11 -g -o  Fluctuate Fluctuate.cpp -I`root-config --incdir` `root-config --glibs --libs`

void Fluctuate(std::string filename);
    
int main(int argc, char *argv[]) 
{
    std::string filename = argv[1];
    Fluctuate(filename);
    return 0;
}
void Fluctuate(std::string filename) {

   TFile *f1 = TFile::Open(filename.c_str());
     
   std::string KurdeBele = filename + "Fluc";
   TFile *OutputDupa = TFile::Open(KurdeBele.c_str(), "recreate");
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
       
      if (name.find("MC_") != std::string::npos)
      {
          
        TH2Poly *FluctHist = (TH2Poly*)(poly->Clone());
        // Make the Poisson fluctuated hist
        FluctHist->Reset("");
        TRandom3* rnd = new TRandom3();
        for (int i = 1; i < FluctHist->GetNumberOfBins()+1; ++i) 
        {
            // Get the posterior predictive bin content
            double MeanContent = poly->GetBinContent(i);
            // Get a Poisson fluctuation of the content
            double Random = rnd->PoissonD(MeanContent);
            // Set the fluctuated histogram content to the Poisson variation of the posterior predictive histogram
            FluctHist->SetBinContent(i,Random);
        }
        OutputDupa->cd();
        FluctHist->Write();
          
      }
   }
  OutputDupa->Close();    
                    
}

