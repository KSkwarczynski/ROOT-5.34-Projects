#include <iostream>
#include <vector>
#include <sys/time.h>

#include <TH1D.h>
#include <THStack.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>

#include "samplePDF/samplePDFND2019.h"
#include "samplePDF/samplePDFND2019GPU.h"
#include "covariance/covariancePsyche.h"
#include "mcmc/mcmc.h"
#include "manager/manager.h"

//Basically copy SetupBinning from samplePDF. Used for the 1d axis in projections (have to define your axis if you want to project a poly). We have functions to do it (assuming uniform distribution of events in a bin when they overlap), but need to hard code the axis
void SetBinning(SampleId::SampleEnum Selection, std::vector<double> & BinningX,std::vector<double> & BinningY) {

  switch (Selection) {
    
  case (SampleId::kFGD1NuMuCC0Pi):
  case (SampleId::kFGD1NuMuCC0PiNp): //WARNING
  case (SampleId::kFGD2NuMuCC0Pi):
    {
      const double BinArray_x[] = {0., 200., 300., 400., 450., 500., 550., 600., 650., 700., 750., 800., 850., 900., 950., 1000., 1050., 1100., 1200., 1300., 1400., 1500., 1600., 1700., 1800., 2000., 2500., 3000., 5000., 30000.};
      const double BinArray_y[] = {-1., 0.5, 0.6, 0.7, 0.76, 0.78, 0.8, 0.83, 0.85, 0.88, 0.89, 0.9, 0.91, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1NuMuCC1Pi):
  case (SampleId::kFGD2NuMuCC1Pi):
    {
      const double BinArray_x[] = {0., 300., 350., 400., 500., 600., 650., 700., 750., 800., 900., 1000., 1100., 1200., 1500., 2000., 3000., 5000., 30000.};
      const double BinArray_y[] = {-1., 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 0.995, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1NuMuCCOther):
  case (SampleId::kFGD2NuMuCCOther):
    {
      const double BinArray_x[] = {0., 300., 400., 500., 600., 650., 700., 750., 800., 900., 1000., 1100., 1250., 1500., 1750., 2000., 3000., 5000., 30000.};
      const double BinArray_y[] = {-1., 0.6, 0.7, 0.76, 0.8, 0.85, 0.88, 0.89, 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 0.995, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1AntiNuMuCC0Pi):
  case (SampleId::kFGD2AntiNuMuCC0Pi):
    {
      const double BinArray_x[] = {0., 300., 400., 500., 550., 600., 650., 700., 750., 800., 900., 1000., 1100., 1200., 1500., 2000., 4000., 30000.};
      const double BinArray_y[] = {-1., 0.6, 0.7, 0.8, 0.85, 0.9, 0.92, 0.93, 0.94, 0.95, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1AntiNuMuCC1Pi):
  case (SampleId::kFGD2AntiNuMuCC1Pi):
    {
     const double BinArray_x[] = {0., 500., 700., 900., 1300., 2500., 30000.};
     const double BinArray_y[] = {-1, 0.7, 0.8, 0.9, 0.94, 0.96, 0.98, 0.99, 1};
     BinningX = MakeVector(BinArray_x);
     BinningY = MakeVector(BinArray_y);
     break;
    }
  
  case (SampleId::kFGD1AntiNuMuCCOther):
  case (SampleId::kFGD2AntiNuMuCCOther):
    {
      const double BinArray_x[] = {0., 600., 800., 1000., 1250., 1500., 2000., 4000., 30000.};
      const double BinArray_y[] = {-1., 0.7, 0.8, 0.85, 0.9, 0.93, 0.95, 0.97, 0.98, 0.99, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1NuMuBkgInAntiNuModeCC0Pi):
  case (SampleId::kFGD2NuMuBkgInAntiNuModeCC0Pi):
    {
      const double BinArray_x[] = {0., 300., 500., 700., 800., 900., 1250., 1500., 2000., 4000., 30000.};
      const double BinArray_y[] = {-1., 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.94, 0.96, 0.97, 0.98, 0.99, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }

  case (SampleId::kFGD1NuMuBkgInAntiNuModeCC1Pi):
  case (SampleId::kFGD2NuMuBkgInAntiNuModeCC1Pi):
    {
      const double BinArray_x[] = {0., 600., 800., 1500., 30000.};
      const double BinArray_y[] = {-1, 0.7, 0.8, 0.86, 0.9, 0.94, 0.96, 0.97, 0.98, 0.99, 1};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  case (SampleId::kFGD1NuMuBkgInAntiNuModeCCOther):
  case (SampleId::kFGD2NuMuBkgInAntiNuModeCCOther):
    {
      const double BinArray_x[] = {0., 600., 1000., 1250., 2000., 4000., 30000.};
      const double BinArray_y[] = {-1., 0.7, 0.8, 0.86, 0.9, 0.93, 0.95, 0.97, 0.99, 1.};
      BinningX = MakeVector(BinArray_x);
      BinningY = MakeVector(BinArray_y);
      break;
    }
  
  default:
    std::cerr << "You gave me a selection I don't have a binning for, whaaa?" << std::endl;
    std::cerr << "Selection: " << Selection << " = " << SampleId::ConvertSample(Selection) << std::endl;
    throw;
    break;
  }
}
  
int main(int argc, char **argv) {

  if (argc != 2) {
    std::cout << "sigmavar2014ND runs FGD1 and FGD2 1 sigma variations at ND280" << std::endl;
    std::cout << "syntax is $: sigmavar2014ND config.cfg" << std::endl;
    std::cout << "where config.cfg is a valid config file, compatible with the manager class (manager/manager.cpp/h); an example is provided in example_config.cfg" << std::endl;
    exit(-1);
  }

  manager *fitMan = new manager(argv[1]);

  std::cout << "------------------------------" << std::endl;
#ifdef MULTITHREAD
  std::cout << "OPENMP ON" << std::endl;
#else
  std::cout << "OPENMP OFF" << std::endl;
#endif

#ifdef CUDA
  std::cout << "CUDA ON" << std::endl;
#else
  std::cout << "CUDA OFF" << std::endl;
#endif

#ifdef CUDA
  samplePDFND2019GPU* sample = new samplePDFND2019GPU(fitMan);
#else
  samplePDFND2019* sample = new samplePDFND2019(fitMan);
#endif

  // Get inputted systematic parameters covariance matrices
  TString xsecCovMatrixFile = fitMan->getXsecCovMatrix();
  TString fluxCovMatrixFile = fitMan->getFluxCovMatrix();
  TString ndDetCovMatrixFile = fitMan->getNDdetCovMatrix();

  covarianceXsec2015 *xsec = new covarianceXsec2015("xsec_cov", xsecCovMatrixFile);
  std::cout << "------------------------------" << std::endl;
  covarianceFlux* flux = new covarianceFlux("total_flux_cov", fluxCovMatrixFile);
  std::cout << "------------------------------" << std::endl;
  covarianceNDDet_2019Poly* det = new covarianceNDDet_2019Poly("nddet_cov", ndDetCovMatrixFile);
  std::cout << "------------------------------" << std::endl;

  xsec->setParameters();
  flux->setParameters();
  det->setParameters();

  //  Set covariance matrices for ND sample
  sample->setXsecCov(xsec);
  sample->setFluxCov(flux);
  sample->setSimpleDetCov(det);

  // ==========================================================

  sample->fillDataFromSamples();
  sample->fillReweigtingBins();
#ifdef CUDA
  sample->fillGPUSplines();
#endif


  double* fake=0;
  TStopwatch clock;
  clock.Start();
  sample->reweight(fake);
  clock.Stop();
  std::cout << "Single reweight of MC took " << clock.RealTime() << "s to complete" << std::endl;
  sample->printRates();

  // If we're doing a fake-data fit
  bool fakeDataFit = fitMan -> getFakeDataFitFlag();
  if (fakeDataFit) {
    sample->setAsimovFakeData();
  }

  // only have one sample for ND280 = sample
  std::string outputName = fitMan->getOutputFilename();
  while (outputName.find(".root") != std::string::npos) {
    outputName = outputName.substr(0, outputName.find(".root"));
  }
    
  outputName += "_ND280_sigmavar.root";
  if (fitMan->getPlotByMode()) 
   {
       outputName += "_byMode.root";
   }
  // Number of variations we want
  const int numVar = 5;
  // -1 0 +1 sigma variation
  const int sigmaArray[numVar] = {-3, -1, 0, 1, 3};

  TFile *output = new TFile(outputName.c_str(), "RECREATE");

  // Make a vector of covarianceBases to loop over and calculate LLH variations for
  std::vector<covarianceBase*> BaseVector;
  // You should be able to add in any arbitrary covariance base class here
  BaseVector.push_back(flux);
  //BaseVector.push_back(det);
  BaseVector.push_back(xsec);
  bool isxsec = false;

  for (std::vector<covarianceBase*>::iterator it = BaseVector.begin(); it != BaseVector.end(); ++it) {
    
    TMatrixDSym *Cov = (*it)->getCovMatrix();
    //  Get the xsec2015 class when we're dealing with xsec so we can set names properly
    //  Also we need to identify when we have lower and upper bounds so we don't scan in invalid regions
    //  in 2016 this was only applied to xsec params
    covarianceXsec2015 *TempClass = NULL;
    if (std::string((*it)->getName()) == "xsec_cov") {
      isxsec = true;
      TempClass = dynamic_cast<covarianceXsec2015*>(*it);
    } else {
      TempClass = NULL;
    }


    // Make a 2D array of pointers for directories
    TDirectory *dirArry[SampleId::kNSamples][(*it)->getSize()];

    // Get each sample and how it's responded to our reweighted parameter
    for (int k = 0; k < SampleId::kNSamples; ++k) {

      // Skip insignificant samples
      if (sample->getPDF(k) == NULL || NoOverflowIntegral((TH2Poly*)sample->getPDF(k)) < 1) continue;

      
      // Loop over xsec parameters
      for (int i = 0; i < (*it)->getSize(); ++i) {

        // Make a directory for each sample and selection
        std::string TempName = (*it)->getParName(i);
        if (isxsec) TempName = TempClass->getParameterName(i);

        
        std::string title = std::string(sample->getPDF(k)->GetName()) + "_" + TempName;
        
        if(k==4) //WARNING
        {
            title="FGD1_numuCC_0pi_Np_" + TempName;
        }
        
        dirArry[k][i] = output->mkdir(title.c_str());

        // Get the initial value of ith parameter
        double init = (*it)->getParInit(i);

        TH1D *sigmaArray_x[numVar];
        TH1D *sigmaArray_y[numVar];
        TH1D *sigmaArray_x_norm[numVar];
        TH1D *sigmaArray_y_norm[numVar];

        // Set up for single mode
        TH1D *sigmaArray_mode_x[numVar];
        TH1D *sigmaArray_mode_y[numVar];

        std::cout << std::setw(20) << SampleId::ConvertSample(SampleId::SampleEnum(k)) << std::setw(15) << " integral" << std::setw(20) << (*it)->getParName(i) << std::endl;

        double oldIntegral = NoOverflowIntegral((TH2Poly*)sample->getPDF(k));
        // Skip this parameter (saves on output in file)
        bool skip = false;
        // Make asymmetric errors just in case
        //WARNING
        double integralCCQE=0;
        double integral2p2h=0;
        double integralRES=0;
        double integralDIS=0;
        for (int j = 0; j < numVar; ++j) {

          sigmaArray_x[j] = NULL;
          sigmaArray_y[j] = NULL;

          // New value = nominal + variation*1sigma uncertainity
          double paramVal = (*it)->getNominal(i)+sigmaArray[j]*sqrt((*Cov)(i,i));

          // Check the bounds on the parameter
          if (isxsec) {
            if (paramVal > TempClass->getParamUpperBound(i)) {
              paramVal = TempClass->getParamUpperBound(i);
            } else if (paramVal < TempClass->getParamLowerBound(i)) {
              paramVal = TempClass->getParamLowerBound(i);
            }
          }

          // Set the parameter
          (*it)->setParProp(i, paramVal);
          // And reweight the sample
          sample->reweight(fake);

          double integral = NoOverflowIntegral((TH2Poly*)sample->getPDF(k));
          std::cout << std::setw(20) << " ALL " << std::setw(15) << integral << std::setw(20) << paramVal << std::endl;

          // Skip if this is a particularly dull variable which doesn't affect the event rate much
          if (fabs(integral - oldIntegral) < 1) skip = true;
          oldIntegral = integral;

          // Make a string of the double
          std::ostringstream ss;
          ss << paramVal;
          std::string parVarTitle = std::string((*it)->getParName(i)) + "_" + ss.str();

          // This is a TH2D
          TH2Poly* currSamp = (TH2Poly*)(sample->getPDF(k))->Clone();
          // Set a descriptiv-ish title
          std::string title_long = std::string(currSamp->GetName())+"_"+parVarTitle;

          // Now get the TH2D mode variations
          TH2Poly* currSampMode;
          std::string mode_title_long;
          // Enable the mode histograms AFTER addSelection is called
          //Get the 1d binning we want. Let's just use SetupBinning to get this as it already exists
          std::vector<double> xbins;
          std::vector<double> ybins;
          SetBinning(SampleId::SampleEnum(k), xbins, ybins);
     
      //WARNING
        if (fitMan->getPlotByMode()) {
            currSampMode = (TH2Poly*)(sample->getPDFMode(k, kMaCh3_CCQE))->Clone();
            mode_title_long = title_long+"_"+MaCh3mode_ToString(MaCh3_Mode(kMaCh3_CCQE));
            currSampMode->SetNameTitle(mode_title_long.c_str(), mode_title_long.c_str());
            dirArry[k][i]->cd();
            currSampMode->Write();

            //sigmaArray_mode_x[j] =  ((TH2Poly*)currSampMode)->ProjectionX((mode_title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
            sigmaArray_mode_x[j] = PolyProjectionX(currSampMode, (mode_title_long+"_xProj").c_str(), xbins);
            //sigmaArray_mode_y[j] = ((TH2Poly*)currSampMode)->ProjectionY((mode_title_long+"_yProj").c_str(), 1, currSamp->GetXaxis()->GetNbins(), "e");
            sigmaArray_mode_y[j] = PolyProjectionY(currSampMode, (mode_title_long+"_yProj").c_str(), ybins);
            //delete currSampMode;
        
            integralCCQE = NoOverflowIntegral( (TH2Poly*)sample->getPDFMode(k, kMaCh3_CCQE) );
            std::cout << std::setw(20) << " CCQE " << std::setw(15) << integralCCQE << std::setw(20) << paramVal << std::endl;
          }
          if (fitMan->getPlotByMode()) {

            // Currently just doing 2p2h here but could do a lot more!
            // Just need to add a for loop really
            currSampMode = (TH2Poly*)(sample->getPDFMode(k, kMaCh3_2p2h))->Clone();
            mode_title_long = title_long+"_"+MaCh3mode_ToString(MaCh3_Mode(kMaCh3_2p2h));
            currSampMode->SetNameTitle(mode_title_long.c_str(), mode_title_long.c_str());
            dirArry[k][i]->cd();
            currSampMode->Write();

            //sigmaArray_mode_x[j] =  ((TH2Poly*)currSampMode)->ProjectionX((mode_title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
            sigmaArray_mode_x[j] = PolyProjectionX(currSampMode, (mode_title_long+"_xProj").c_str(), xbins);
            //sigmaArray_mode_y[j] = ((TH2Poly*)currSampMode)->ProjectionY((mode_title_long+"_yProj").c_str(), 1, currSamp->GetXaxis()->GetNbins(), "e");
            sigmaArray_mode_y[j] = PolyProjectionY(currSampMode, (mode_title_long+"_yProj").c_str(), ybins);
            //delete currSampMode;
        
            integral2p2h = NoOverflowIntegral( (TH2Poly*)sample->getPDFMode(k, kMaCh3_2p2h) );
            std::cout << std::setw(20) << " 2p2h " << std::setw(15) << integral2p2h << std::setw(20) << paramVal << std::endl;
          }

            if (fitMan->getPlotByMode()) {
            currSampMode = (TH2Poly*)(sample->getPDFMode(k, kMaCh3_CC1pi))->Clone();
            mode_title_long = title_long+"_"+MaCh3mode_ToString(MaCh3_Mode(kMaCh3_CC1pi));
            currSampMode->SetNameTitle(mode_title_long.c_str(), mode_title_long.c_str());
            dirArry[k][i]->cd();
            currSampMode->Write();

            //sigmaArray_mode_x[j] =  ((TH2Poly*)currSampMode)->ProjectionX((mode_title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
            sigmaArray_mode_x[j] = PolyProjectionX(currSampMode, (mode_title_long+"_xProj").c_str(), xbins);
            //sigmaArray_mode_y[j] = ((TH2Poly*)currSampMode)->ProjectionY((mode_title_long+"_yProj").c_str(), 1, currSamp->GetXaxis()->GetNbins(), "e");
            sigmaArray_mode_y[j] = PolyProjectionY(currSampMode, (mode_title_long+"_yProj").c_str(), ybins);
            //delete currSampMode;
        
            integralRES = NoOverflowIntegral( (TH2Poly*)sample->getPDFMode(k, kMaCh3_CC1pi) );
            std::cout << std::setw(20) << " RES " << std::setw(15) << integralRES << std::setw(20) << paramVal << std::endl;
          }
          
            if (fitMan->getPlotByMode()) {
            currSampMode = (TH2Poly*)(sample->getPDFMode(k, kMaCh3_CCDIS))->Clone();
            mode_title_long = title_long+"_"+MaCh3mode_ToString(MaCh3_Mode(kMaCh3_CCDIS));
            currSampMode->SetNameTitle(mode_title_long.c_str(), mode_title_long.c_str());
            dirArry[k][i]->cd();
            currSampMode->Write();

            //sigmaArray_mode_x[j] =  ((TH2Poly*)currSampMode)->ProjectionX((mode_title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
            sigmaArray_mode_x[j] = PolyProjectionX(currSampMode, (mode_title_long+"_xProj").c_str(), xbins);
            //sigmaArray_mode_y[j] = ((TH2Poly*)currSampMode)->ProjectionY((mode_title_long+"_yProj").c_str(), 1, currSamp->GetXaxis()->GetNbins(), "e");
            sigmaArray_mode_y[j] = PolyProjectionY(currSampMode, (mode_title_long+"_yProj").c_str(), ybins);
            //delete currSampMode;
        
            integralDIS = NoOverflowIntegral( (TH2Poly*)sample->getPDFMode(k, kMaCh3_CCDIS) );
            std::cout << std::setw(20) << " DIS " << std::setw(15) << integralDIS << std::setw(20) << paramVal << std::endl;
          }

          // Project down onto x axis
          //sigmaArray_x[j] = ((TH2Poly*)currSamp)->ProjectionX((title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
          sigmaArray_x[j] = PolyProjectionX(currSamp, (mode_title_long+"_xProj").c_str(), xbins);
	  //sigmaArray_x[j] = ((TH2Poly*)currSamp)->ProjectionX((title_long+"_xProj").c_str(), 1, currSamp->GetYaxis()->GetNbins(), "e");
          sigmaArray_y[j] = PolyProjectionY(currSamp, (mode_title_long+"_yProj").c_str(), ybins);

          sigmaArray_x_norm[j] = (TH1D*)sigmaArray_x[j]->Clone();
          sigmaArray_x_norm[j]->Scale(1., "width");
          sigmaArray_y_norm[j] = (TH1D*)sigmaArray_y[j]->Clone();
          sigmaArray_y_norm[j]->Scale(1., "width");

          currSamp->SetNameTitle(title_long.c_str(), title_long.c_str());
          dirArry[k][i]->cd();
          currSamp->Write();
          
          //WARNING
          sigmaArray_x[j]->SetName( Form("momentum_%s", parVarTitle.c_str()) );
          sigmaArray_x[j]->SetTitle( Form("momentum_%s", parVarTitle.c_str()) );
          sigmaArray_y[j]->SetName( Form("cosT_%s", parVarTitle.c_str()) );
          sigmaArray_y[j]->SetTitle( Form("cosT_%s", parVarTitle.c_str()) );
          sigmaArray_x[j]->Write();
          sigmaArray_y[j]->Write();
	  //          delete currSamp;
        } // End looping over variation

        // Restore the parameter to nominal value
        (*it)->setParProp(i, init);

        TGraphAsymmErrors *var_x = new TGraphAsymmErrors(sigmaArray_x[1]);
        var_x->SetNameTitle((title+"_X").c_str(), (title+"_X").c_str());
        TGraphAsymmErrors *var_y = new TGraphAsymmErrors(sigmaArray_y[1]);
        var_y->SetNameTitle((title+"_Y").c_str(), (title+"_Y").c_str());
        TGraphAsymmErrors *var_x_norm = new TGraphAsymmErrors(sigmaArray_x_norm[1]);
        var_x_norm->SetNameTitle((title+"_X_norm").c_str(), (title+"_X_norm").c_str());
        TGraphAsymmErrors *var_y_norm = new TGraphAsymmErrors(sigmaArray_y_norm[1]);
        var_y_norm->SetNameTitle((title+"_Y_norm").c_str(), (title+"_Y_norm").c_str());

        // Make the ones for the mode variations
        TGraphAsymmErrors *var_mode_x;
        TGraphAsymmErrors *var_mode_y;
        if (fitMan->getPlotByMode()) {
          var_mode_x = new TGraphAsymmErrors(sigmaArray_mode_x[1]);
          var_mode_x->SetNameTitle((title+"_2p2h_X").c_str(), (title+"_2p2h_X").c_str());

          // Loop over the x
          for (int m = 0; m < var_mode_x->GetN(); m++) {
            double xlow = sigmaArray_mode_x[0]->GetBinContent(m+1);
            double xhigh = sigmaArray_mode_x[2]->GetBinContent(m+1);
            double xtemp;

            // Make sure we've got upper and lower event rates correct way around
            if (xlow > xhigh) {
              xtemp = xlow;
              xlow = xhigh;
              xhigh = xtemp;
            }

            // Set the points in the TGraph
            var_mode_x->SetPointEYhigh(m, xhigh - var_mode_x->GetY()[m]);
            var_mode_x->SetPointEYlow(m, var_mode_x->GetY()[m] - xlow);
          }

          // Make the y variations
          var_mode_y = new TGraphAsymmErrors(sigmaArray_mode_y[1]);
          var_mode_y->SetNameTitle((title+"_2p2h_Y").c_str(), (title+"_2p2h_Y").c_str());
          // Loop over the y
          for (int m = 0; m < var_mode_y->GetN(); m++) {
            double ylow = sigmaArray_mode_y[0]->GetBinContent(m+1);
            double yhigh = sigmaArray_mode_y[2]->GetBinContent(m+1);
            double ytemp;

            // Make sure we've got upper and lower event rates correct way around
            if (ylow > yhigh) {
              ytemp = ylow;
              ylow = yhigh;
              yhigh = ytemp;
            }

            // Set the points in the TGraph
            var_mode_y->SetPointEYhigh(m, yhigh - var_mode_y->GetY()[m]);
            var_mode_y->SetPointEYlow(m, var_mode_y->GetY()[m] - ylow);
          }

          var_mode_x->Draw("AP");
          var_mode_x->GetXaxis()->SetTitle(sigmaArray_mode_x[1]->GetXaxis()->GetTitle());
          var_mode_x->GetYaxis()->SetTitle("Number of events/bin");

          var_mode_y->Draw("AP");
          var_mode_y->GetXaxis()->SetTitle(sigmaArray_mode_y[1]->GetXaxis()->GetTitle());
          var_mode_y->GetYaxis()->SetTitle("Number of events/bin");

          dirArry[k][i]->cd();
          var_mode_x->Write();
          var_mode_y->Write();

          delete var_mode_x;
          delete var_mode_y;

        }


        for (int m = 0; m < var_x->GetN(); ++m) {
          double xlow = sigmaArray_x[0]->GetBinContent(m+1);
          double xhigh = sigmaArray_x[2]->GetBinContent(m+1);
          double xtemp;

          double xlow_norm = sigmaArray_x_norm[0]->GetBinContent(m+1);
          double xhigh_norm = sigmaArray_x_norm[2]->GetBinContent(m+1);
          double xtemp_norm;

          // Figure out which variation is larger so we set the error correctly
          if (xlow > xhigh) {
            xtemp = xlow;
            xlow = xhigh;
            xhigh = xtemp;
          }
          if (xlow_norm > xhigh_norm) {
            xtemp_norm = xlow_norm;
            xlow_norm = xhigh_norm;
            xhigh_norm = xtemp_norm;
          }

          var_x->SetPointEYhigh(m, xhigh - var_x->GetY()[m]);
          var_x->SetPointEYlow(m, var_x->GetY()[m] - xlow);
          var_x_norm->SetPointEYhigh(m, xhigh_norm - var_x_norm->GetY()[m]);
          var_x_norm->SetPointEYlow(m, var_x_norm->GetY()[m] - xlow_norm);
        }

        for (int m = 0; m < var_y->GetN(); ++m) {
          double ylow = sigmaArray_y[0]->GetBinContent(m+1);
          double yhigh = sigmaArray_y[2]->GetBinContent(m+1);
          double ytemp;

          double ylow_norm = sigmaArray_y_norm[0]->GetBinContent(m+1);
          double yhigh_norm = sigmaArray_y_norm[2]->GetBinContent(m+1);
          double ytemp_norm;

          // Figure out which variation is larger so we set the error correctly
          if (ylow > yhigh) {
            ytemp = ylow;
            ylow = yhigh;
            yhigh = ytemp;
          }
          if (ylow_norm > yhigh_norm) {
            ytemp_norm = ylow_norm;
            ylow_norm = yhigh_norm;
            yhigh_norm = ytemp_norm;
          }

          var_y->SetPointEYhigh(m, yhigh - var_y->GetY()[m]);
          var_y->SetPointEYlow(m, var_y->GetY()[m] - ylow);

          var_y_norm->SetPointEYhigh(m, yhigh_norm - var_y_norm->GetY()[m]);
          var_y_norm->SetPointEYlow(m, var_y_norm->GetY()[m] - ylow_norm);
        }

        if (skip == true) continue;

        // Need to draw TGraphs to set axes labels
        var_x->Draw("AP");
        var_x->GetXaxis()->SetTitle(sigmaArray_x[1]->GetXaxis()->GetTitle());
        var_x->GetYaxis()->SetTitle("Number of events/bin");
        var_x_norm->Draw("AP");
        var_x_norm->GetXaxis()->SetTitle(sigmaArray_x[1]->GetXaxis()->GetTitle());
        var_x_norm->GetYaxis()->SetTitle("Number of events/MeV");

        var_y->Draw("AP");
        var_y->GetXaxis()->SetTitle(sigmaArray_y[1]->GetYaxis()->GetTitle());
        var_y->GetYaxis()->SetTitle("Number of events/bin");
        var_y_norm->Draw("AP");
        var_y_norm->GetXaxis()->SetTitle(sigmaArray_y[1]->GetYaxis()->GetTitle());
        var_y_norm->GetYaxis()->SetTitle("Number of events/1");

        dirArry[k][i]->cd();
        var_x->Write();
        var_y->Write();
        var_x_norm->Write();
        var_y_norm->Write();

        delete var_x;
        delete var_y;
        delete var_x_norm;
        delete var_y_norm;

      } // end looping over xsec parameters (i)
    } // end looping over psyche samples (k)
  } // end looping over covarianceBase objects

  output->Close();

  std::cout << "Succesfully wrote " << output->GetName() << std::endl;

  return 0;
}
