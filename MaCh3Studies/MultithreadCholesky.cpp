// C++ includes
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

// ROOT includes
#include "TFile.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include "TMatrixT.h"
#include "TMatrixDSym.h"
#include "TVectorD.h"
#include "TObject.h"
#include "TChain.h"
#include "TH1.h"


#include "TStopwatch.h"

#include "omp.h"




//KS: Simple script to get Flux penalty term, since flux and xsec are on systeamtic we cannot just directly take it from the chain
//g++ `root-config --cflags` -std=c++11 -fopenmp -g -o MultithreadCholesky MultithreadCholesky.cpp -I`root-config --incdir` `root-config --glibs --libs`

void MultithreadCholesky(std::string inputFile);

std::vector <bool> isFlux;
std::vector <int> nominal;
std::vector<TString> BranchNames;

double** invCovMatrix;

int main(int argc, char *argv[]) 
{
    if (argc != 2 ) 
    {
        std::cerr << "./MultithreadCholesky root_file_to_analyse.root " << std::endl;
        exit(-1);
    }
    std::string filename = argv[1];
    if (argc == 2) MultithreadCholesky(filename);

    return 0;
}

void  MultithreadCholesky(std::string inputFile)
{
    
    TCanvas* canvas = new TCanvas("canvas", "canvas", 0, 0, 1024, 1024);
    canvas->SetGrid();
    canvas->SetTickx();
    canvas->SetTicky();
    canvas->SetBottomMargin(0.1);
    canvas->SetTopMargin(0.02);
    canvas->SetRightMargin(0.03);
    canvas->SetLeftMargin(0.10);
  
    gStyle->SetOptTitle(0); 
    gStyle->SetOptStat(0); 
    gStyle->SetPalette(51);
  
  

    // Do the same for the cross-section
    TFile *XSecFile = new TFile(inputFile.c_str(), "open");

    // Get the matrix
    TMatrixDSym *covMatrix = (TMatrixDSym*)(XSecFile->Get("nddet_cov"));
    TMatrixDSym *Matrix = (TMatrixDSym*)covMatrix->Clone();
    //TMatrixDSym *MatrixClone = (TMatrixDSym*)covMatrix->Clone();
      
     const int npars = covMatrix->GetNrows();

  double* L = new double[npars*npars]();
  double* A = new double[npars*npars]();
  // Set the defaults to true
  for(int i = 0; i < npars; i++)
  {
    for (int j = 0; j < npars; j++)
    {
        L[i* npars + j] = (*covMatrix)(i,j);
        A[i* npars + j] = (*covMatrix)(i,j);
        //std::cout<<(*covMatrix)(i,j)<<std::endl;
    }
  }

  TStopwatch clock;
  clock.Start();
  // Loop over the entries columns
  for (int i = 0; i < npars; i++) {

    // Loop over the entries rows
    for (int j = 0; j < npars; j++) {

      // If diagonal element
      if (i == j) {
        (*Matrix)(i,i) = (*covMatrix)(i,i);
        // For a given entry, loop over the entries up to i
        for (int k = 0; k <= i-1; k++) {
          (*Matrix)(i,i) = (*Matrix)(i,i) - pow((*Matrix)(i,k),2);
        }
        (*Matrix)(i,i) = sqrt((*Matrix)(i,i));

      // If lower half
      } else if (j < i) {

        (*Matrix)(i,j) = (*covMatrix)(i,j);
        for (int k = 0; k <= j - 1; k++) {
          (*Matrix)(i,j) = (*Matrix)(i,j)-(*Matrix)(i,k)*(*Matrix)(j,k);
        }
        (*Matrix)(i,j) = (*Matrix)(i,j)/(*Matrix)(j,j);
      } else {
        (*Matrix)(i,j) = 0.;
      }
    }
  }
  
   clock.Stop();
  std::cout << "Non MP " << clock.RealTime() << "s" << std::endl;


  
  TStopwatch clockMP;
  clockMP.Start();
//https://lume.ufrgs.br/bitstream/handle/10183/151001/001009773.pdf#page=72
  for (int j = 0; j < npars; j++)
  {
    double sum = 0;
    for (int k = 0; k < j; k++)
    {
      sum += L[j * npars + k] * L[j * npars + k];
    }
    L[j * npars + j] = sqrt(A[j * npars+ j] - sum);
    #pragma omp parallel for private(sum)
    for (int i = j + 1; i < npars; i++) {
    sum = 0;
    for (int k = 0; k < j; k++)
    {
      sum += L[i * npars + k] * L[j * npars + k];
    }
    L[i* npars + j] = (1.0 / L[j * npars + j] * (A[i *npars + j] - sum));
    }
  }
    clockMP.Stop();
  std::cout << "MP " << clockMP.RealTime() << "s" << std::endl;
  
  
    for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        std::cout<<"i "<<i<<" j "<<j<<" Non MP "<<(*Matrix)(i,j) <<" MP "<<  L[i* npars + j]<<" difference "<<(*Matrix)(i,j) - L[i* npars + j]<<std::endl;
    }
    }
  
}

