#include <iostream>
#include <vector>

#include <TH1D.h>
#include <TLine.h>
#include <TStyle.h>

#include "samplePDF/samplePDFND2019.h"
#include "samplePDF/samplePDFND2019GPU.h"
#include "mcmc/mcmc.h"
#include "manager/manager.h"

#include "omp.h"


int main(int argc, char **argv) {

  manager *fitMan = new manager(argv[1]);
  if (fitMan->getGoodConfig() == false) {
    std::cerr << "************* BAD CONFIG ***************" << std::endl;
    throw;
  }

  /// Now we need to see what kind of fit we are doing
  /// Asimov fit    = fit fake data with same parameters than MC
  /// Toy fit       = fit fake data changing the value of nuisance parameters (?)
  /// Fake data fit = fit fake data which are even more different (?)
  /// Real data fit = fit the true ND and SK data (the true fit !)

  bool fakeDataFit = fitMan -> getFakeDataFitFlag();
  bool realDataFit = fitMan -> getRealDataFitFlag();
  bool toyFit      = fitMan -> getToyFitFlag();
  bool asimovFit   = fitMan -> getAsimovFitFlag();

  // The different fits are not compatible between each other so that check that only one type of fit is set
  if (((int)fakeDataFit + (int)realDataFit + (int)toyFit + (int)asimovFit ) != 1) {
    std::cout << "Error: have not chosen one valid type of fit!" << std::endl
      << "Asimov fit = "    << asimovFit    << std::endl
      << "Toy fit = "       << toyFit       << std::endl
      << "Fake data fit = "  << fakeDataFit  << std::endl
      << "Real data fit = " << realDataFit  << std::endl
      << "You have to chose ONLY ONE of them ! " << std::endl  << std::endl;
    throw;
  }

  TString production = fitMan->getNDRuns();

#ifdef CUDA
  samplePDFND2019GPU* sample = new samplePDFND2019GPU(fitMan);
#else
  samplePDFND2019* sample = new samplePDFND2019(fitMan);
#endif

  // Get inputted systematic parameters covariance matrices
  TString xsecCovMatrixFile = fitMan->getXsecCovMatrix();
  TString fluxCovMatrixFile = fitMan->getFluxCovMatrix();
  TString ndDetCovMatrixFile = fitMan->getNDdetCovMatrix();

  covarianceFlux* flux = new covarianceFlux("total_flux_cov", fluxCovMatrixFile);
  covarianceNDDet_2019Poly* det = new covarianceNDDet_2019Poly("nddet_cov", ndDetCovMatrixFile);
  covarianceXsec2015 *xsec = new covarianceXsec2015("xsec_cov", xsecCovMatrixFile);

  // Fill the parameter values
  xsec->setParameters();
  flux->setParameters();
  det->setParameters();

  // Set priors and fix options from file
  // read priors as string from config file
  std::vector<int> NDDetFlatParams = fitMan->getNdDetFlat();
  std::vector<int> NDDetFixParams  = fitMan->getNdDetFix();
  std::vector<int> FluxFlatParams  = fitMan->getFluxFlat();
  std::vector<int> FluxFixParams   = fitMan->getFluxFix();
  std::vector<int> XsecFlatParams  = fitMan->getXsecFlat();
  std::vector<int> XsecFixParams   = fitMan->getXsecFix();

  // Flat flux parameters loop
  if (FluxFlatParams.size() == 1 && FluxFlatParams.at(0) == -1) {
    for (int j = 0; j < flux->getSize(); j++) {
      flux->setEvalLikelihood(j, false);
    }
  } else {
    for (int j = 0; j < FluxFlatParams.size(); j++) {
      flux->setEvalLikelihood(FluxFlatParams.at(j), false);
    }
  }

  // Fixed flux parameters loop
  if (FluxFixParams.size() == 1 && FluxFixParams.at(0) == -1) {
    for (int j = 0; j < flux->getSize(); j++) {
      flux->setParCurrProp(j, flux->getNominal(j));
      flux->toggleFixParameter(j);
    }
  } else {
    for (int j = 0; j < FluxFixParams.size(); j++) {
      flux->setParCurrProp(j, flux->getNominal(j));
      flux->toggleFixParameter(FluxFixParams.at(j));
    }
  }

  std::cout << "------------------------------" << std::endl;

  // Flat ND parameters loop
  if (NDDetFlatParams.size() == 1 && NDDetFlatParams.at(0) == -1) {
    for (int j = 0; j < det->getSize(); j++) {
      det->setEvalLikelihood(j, false);
    }
  } else {
    for (int j = 0; j < NDDetFlatParams.size(); j++) {
      det->setEvalLikelihood(NDDetFlatParams.at(j), false);
    }
  }

  // Fixed ND parameters loop
  if (NDDetFixParams.size() == 1 && NDDetFixParams.at(0) == -1) {
    for (int j = 0; j < det->getSize(); j++) {
      det->setParCurrProp(j, det->getNominal(j));
      det->toggleFixParameter(j);
    }
  } else {
    for (int j = 0; j < NDDetFixParams.size(); j++) {
      det->setParCurrProp(j, det->getNominal(j));
      det->toggleFixParameter(NDDetFixParams.at(j));
    }
  }

  std::cout << "------------------------------" << std::endl;

  // Flat xsec parameters loop
  if (XsecFlatParams.size() == 1 && XsecFlatParams.at(0) == -1) {
    for (int j = 0; j < xsec->getSize(); j++) {
      xsec->setEvalLikelihood(j, false);
    }
  } else {
    for (int j = 0; j < XsecFlatParams.size(); j++) {
      xsec->setEvalLikelihood(XsecFlatParams.at(j), false);
    }
  }

  // Fixed xsec parameters loop
  if (XsecFixParams.size() == 1 && XsecFixParams.at(0) == -1) {
    for (int j = 0; j < xsec->getSize(); j++) {
      xsec->setParCurrProp(j, xsec->getNominal(j));
      xsec->toggleFixParameter(j);
    }
  } else {
    for (int j = 0; j < XsecFixParams.size(); j++) {
      xsec->setParCurrProp(j, xsec->getNominal(j));
      xsec->toggleFixParameter(XsecFixParams.at(j));
    }
  }

  std::cout << "------------------------------" << std::endl;

  // ==========================================================
  //  Set covariance matrices for ND sample
  sample->setXsecCov(xsec);
  sample->setFluxCov(flux);
  sample->setSimpleDetCov(det);

  std::cout << "------------------------------" << std::endl;

  std::cout << "Filling data" << std::endl;
  sample->fillDataFromSamples();
  std::cout << "Filling MC" << std::endl;
  sample->fillReweigtingBins();
#ifdef CUDA
  std::cout << "filling GPU splines" << std::endl;
  sample->fillGPUSplines();
#endif

  std::cout << "ND280 setup complete! " << std::endl;

  // Time reweighting, e.g. GPU vs CPU, splines, event by event...
  TStopwatch reweightClock;
  reweightClock.Start();

  double *fake = 0;
  sample->reweight(fake);

  reweightClock.Stop();
  std::cout << "Single reweight took " << reweightClock.RealTime() << "s to complete" << std::endl;

  std::cout << "Rates after first reweight: " << std::endl;
  sample->printRates();

  // If we're running fake-data fits, we should load up this as data
  if (fakeDataFit) {
    sample->setAsimovFakeData();
  }

  // Now finally get onto the LLH scan stuff
  // Very similar code to MCMC but never start MCMC; just scan over the parameter space

  // only have one sample for ND280 = sample
  std::string outputName = fitMan->getOutputFilename();
  outputName = outputName.substr(0, outputName.find(".root"));
  outputName += "_ND280logL_scan.root";

  TFile *output = new TFile(outputName.c_str(), "RECREATE");
  TDirectory *Flux_LLH = output->mkdir("Flux_LLH");
  TDirectory *XSec_LLH = output->mkdir("XSec_LLH");
  TDirectory *ND280_LLH = output->mkdir("ND280_LLH");
  TDirectory *Sample_LLH = output->mkdir("Sample_LLH");
  TDirectory *Total_LLH = output->mkdir("Total_LLH");
  
  //WARNING
  TDirectory *CC0PI_0p_LLH = output->mkdir("CC0PI_0p_LLH"); 
  TDirectory *CC0PI_Np_LLH = output->mkdir("CC0PI_Np_LLH");
  TDirectory *CC1PI_LLH = output->mkdir("CC1PI_LLH");
  TDirectory *CCOther_LLH = output->mkdir("CCOther_LLH");
  
  TDirectory *CC0Pi_RHC_LLH = output->mkdir("CC0Pi_RHC_LLH");
  TDirectory *CC1Pi_RHC_LLH = output->mkdir("CC1Pi_RHC_LLH");
  TDirectory *CCOtgher_RHC_LLH = output->mkdir("CCOther_RHC_LLH");
  
  TDirectory *CC0Pi_BKG_LLH = output->mkdir("CC0Pi_BKG_LLH");
  TDirectory *CC1Pi_BKG_LLH = output->mkdir("CC1Pi_BKG_LLH");
  TDirectory *CCOtgher_BKG_LLH = output->mkdir("CCOther_BKG_LLH");
  

  TDirectory *CC0PI_LLH2 = output->mkdir("CC0PI_LLH2"); 
  TDirectory *CC1PI_LLH2 = output->mkdir("CC1PI_LLH2");
  TDirectory *CCOther_LLH2 = output->mkdir("CCOther_LLH2");
  
  TDirectory *CC0Pi_RHC_LLH2 = output->mkdir("CC0Pi_RHC_LLH2");
  TDirectory *CC1Pi_RHC_LLH2 = output->mkdir("CC1Pi_RHC_LLH2");
  TDirectory *CCOtgher_RHC_LLH2 = output->mkdir("CCOther_RHC_LLH2");
  
  TDirectory *CC0Pi_BKG_LLH2 = output->mkdir("CC0Pi_BKG_LLH2");
  TDirectory *CC1Pi_BKG_LLH2 = output->mkdir("CC1Pi_BKG_LLH2");
  TDirectory *CCOtgher_BKG_LLH2 = output->mkdir("CCOther_BKG_LLH2");
  
  TDirectory *Sample_SUM_LLH = output->mkdir("Sample_SUM_LLH");
  // Number of points we do for each LLH scan
  int n_points = 150;
  // We print 5 reweights
  int countwidth = double(n_points)/double(5);

  // Make a vector of covarianceBases to loop over and calculate LLH variations for
  std::vector<covarianceBase*> BaseVector;
  // You should be able to add in any arbitrary covariance base class here
  BaseVector.push_back(flux);
  //BaseVector.push_back(det);
  BaseVector.push_back(xsec);
  bool isxsec = false;
  // Loop over the covariance classes
  for (std::vector<covarianceBase*>::iterator it = BaseVector.begin(); it != BaseVector.end(); ++it) {
    // Get the covariance matrix for the current base vector
    TMatrixDSym *cov = (*it)->getCovMatrix();
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

    // Scan over all the parameters
    for (int i = 0; i < (*it)->getSize(); i++) {
      // Get the parameter name
      std::string name = (*it)->getParName(i);
      // For xsec we can get the actual name, hurray for being informative
      if (isxsec) {
        name = TempClass->getParameterName(i);
      }

      // Get the parameter priors and bounds
      double nom = (*it)->getParInit(i);

      // Get the covariance matrix and do the +/- 2 sigma
      int nSigma = 1;
      double lower = (*it)->getNominal(i) - nSigma*sqrt((*cov)(i,i));
      double upper = (*it)->getNominal(i) + nSigma*sqrt((*cov)(i,i));

      if (isxsec) {
        if (lower < TempClass->getParamLowerBound(i)) {
          lower = TempClass->getParamLowerBound(i);
        }
        if (upper > TempClass->getParamUpperBound(i)) {
          upper = TempClass->getParamUpperBound(i);
        }
      }

      std::cout << "Scanning " << name << " with " << n_points << " steps, \nfrom " << lower << " - " << upper << ", nominal = " << nom << std::endl;

      // Make the TH1D
      TH1D *hScan = new TH1D((name+"_full").c_str(), (name+"_full").c_str(), n_points, lower, upper);
      hScan->SetTitle(std::string(std::string("2LLH_full, ") + name + ";" + name + "; -2(ln L_{sample} + ln L_{xsec} + ln L_{flux} + ln L_{det})").c_str());

      TH1D *hScanSam = new TH1D((name+"_sam").c_str(), (name+"_sam").c_str(), n_points, lower, upper);
      hScanSam->SetTitle(std::string(std::string("2LLH_sam, ") + name + ";" + name + "; -2(ln L_{sample})").c_str());

      TH1D *hScanXSec = new TH1D((name+"_xs").c_str(), (name+"_xs").c_str(), n_points, lower, upper);
      hScanXSec->SetTitle(std::string(std::string("2LLH_xs, ") + name + ";" + name + "; -2(ln L_{xsec})").c_str());

      TH1D *hScanFlux = new TH1D((name+"_flux").c_str(), (name+"_flux").c_str(), n_points, lower, upper);
      hScanFlux->SetTitle(std::string(std::string("2LLH_flux, ") + name + ";" + name + "; -2(ln L_{flux})").c_str());

      TH1D *hScanND = new TH1D((name+"_nd").c_str(), (name+"_nd").c_str(), n_points, lower, upper);
      hScanND->SetTitle(std::string(std::string("2LLH_nd, ") + name + ";" + name + "; -2(ln L_{ND280})").c_str());

      //WARNING
      TH1D *hScanSam0p = new TH1D((name+"_sam0p").c_str(), (name+"_sam0p").c_str(), n_points, lower, upper);
      hScanSam0p->SetTitle(std::string(std::string("2LLH_sam0p, ") + name + ";" + name + "; -2(ln L_{sample_0p})").c_str());
      
      TH1D *hScanSamNp = new TH1D((name+"_samNp").c_str(), (name+"_samNp").c_str(), n_points, lower, upper);
      hScanSamNp->SetTitle(std::string(std::string("2LLH_samNp, ") + name + ";" + name + "; -2(ln L_{sample_Np})").c_str());
      
      TH1D *hScanSam1pi = new TH1D((name+"_sam1pi").c_str(), (name+"_sam1pi").c_str(), n_points, lower, upper);
      hScanSam1pi->SetTitle(std::string(std::string("sample_1pi, ") + name + ";" + name + "; -2(ln L_{sample_1pi})").c_str());
      
      TH1D *hScanSamOther = new TH1D((name+"_samOther").c_str(), (name+"_samOther").c_str(), n_points, lower, upper);
      hScanSamOther->SetTitle(std::string(std::string("sample_Other, ") + name + ";" + name + "; -2(ln L_{sample_Other})").c_str());
      
      TH1D *hScanSam0piRHC = new TH1D((name+"_sam0piRHC").c_str(), (name+"_sam0piRHC").c_str(), n_points, lower, upper);
      hScanSam0piRHC->SetTitle(std::string(std::string("sample_0piRHC, ") + name + ";" + name + "; -2(ln L_{sample_0piRHC)").c_str());
      
      TH1D *hScanSam1piRHC = new TH1D((name+"_sam1piRHC").c_str(), (name+"_sam1piRHC").c_str(), n_points, lower, upper);
      hScanSam1piRHC->SetTitle(std::string(std::string("sample_1piRHC, ") + name + ";" + name + "; -2(ln L_{sample_1piRHC)").c_str());

      TH1D *hScanSamOtherRHC = new TH1D((name+"_samOtherRHC").c_str(), (name+"_samOtherRHC").c_str(), n_points, lower, upper);
      hScanSamOtherRHC->SetTitle(std::string(std::string("sample_OtherRHC, ") + name + ";" + name + "; -2(ln L_{sample_OtherRHC)").c_str());
      
      TH1D *hScanSam0piBKG = new TH1D((name+"_sam0piBKG").c_str(), (name+"_sam0piBKG").c_str(), n_points, lower, upper);
      hScanSam0piBKG->SetTitle(std::string(std::string("sample_0piBKG, ") + name + ";" + name + "; -2(ln L_{sample_0piBKG)").c_str());
      
      TH1D *hScanSam1piBKG = new TH1D((name+"_sam1piBKG").c_str(), (name+"_sam1piBKG").c_str(), n_points, lower, upper);
      hScanSam1piBKG->SetTitle(std::string(std::string("sample_1piBKG, ") + name + ";" + name + "; -2(ln L_{sample_1piBKG)").c_str());

      TH1D *hScanSamOtherBKG = new TH1D((name+"_samOtherBKG").c_str(), (name+"_samOtherBKG").c_str(), n_points, lower, upper);
      hScanSamOtherBKG->SetTitle(std::string(std::string("sample_OtherBKG, ") + name + ";" + name + "; -2(ln L_{sample_OtherBKG)").c_str());

           
      
      TH1D *hScanSam0pi2 = new TH1D((name+"_sam0pi2").c_str(), (name+"_sam0pi2").c_str(), n_points, lower, upper);
      hScanSam0pi2->SetTitle(std::string(std::string("2LLH_sam0pi2, ") + name + ";" + name + "; -2(ln L_{sample_0pi2})").c_str());
      
      TH1D *hScanSam1pi2 = new TH1D((name+"_sam1pi2").c_str(), (name+"_sam1pi2").c_str(), n_points, lower, upper);
      hScanSam1pi2->SetTitle(std::string(std::string("sample_1pi2, ") + name + ";" + name + "; -2(ln L_{sample_1pi2})").c_str());
      
      TH1D *hScanSamOther2 = new TH1D((name+"_samOther2").c_str(), (name+"_samOther2").c_str(), n_points, lower, upper);
      hScanSamOther2->SetTitle(std::string(std::string("sample_Other2, ") + name + ";" + name + "; -2(ln L_{sample_Other2})").c_str());
      
      TH1D *hScanSam0piRHC2 = new TH1D((name+"_sam0piRHC2").c_str(), (name+"_sam0piRHC2").c_str(), n_points, lower, upper);
      hScanSam0piRHC2->SetTitle(std::string(std::string("sample_0piRHC2, ") + name + ";" + name + "; -2(ln L_{sample_0piRHC2)").c_str());
      
      TH1D *hScanSam1piRHC2 = new TH1D((name+"_sam1piRHC2").c_str(), (name+"_sam1piRHC2").c_str(), n_points, lower, upper);
      hScanSam1piRHC2->SetTitle(std::string(std::string("sample_1piRHC2, ") + name + ";" + name + "; -2(ln L_{sample_1piRHC2)").c_str());

      TH1D *hScanSamOtherRHC2 = new TH1D((name+"_samOtherRHC2").c_str(), (name+"_samOtherRHC2").c_str(), n_points, lower, upper);
      hScanSamOtherRHC2->SetTitle(std::string(std::string("sample_OtherRHC2, ") + name + ";" + name + "; -2(ln L_{sample_OtherRHC2)").c_str());
      
      TH1D *hScanSam0piBKG2 = new TH1D((name+"_sam0piBKG2").c_str(), (name+"_sam0piBKG2").c_str(), n_points, lower, upper);
      hScanSam0piBKG2->SetTitle(std::string(std::string("sample_0piBKG2, ") + name + ";" + name + "; -2(ln L_{sample_0piBKG2)").c_str());
      
      TH1D *hScanSam1piBKG2 = new TH1D((name+"_sam1piBKG2").c_str(), (name+"_sam1piBKG2").c_str(), n_points, lower, upper);
      hScanSam1piBKG2->SetTitle(std::string(std::string("sample_1piBKG2, ") + name + ";" + name + "; -2(ln L_{sample_1piBKG2)").c_str());

      TH1D *hScanSamOtherBKG2 = new TH1D((name+"_samOtherBKG2").c_str(), (name+"_samOtherBKG2").c_str(), n_points, lower, upper);
      hScanSamOtherBKG2->SetTitle(std::string(std::string("sample_OtherBKG2, ") + name + ";" + name + "; -2(ln L_{sample_OtherBKG2)").c_str());

      TH1D *hScanSamSum = new TH1D((name+"_samSum").c_str(), (name+"_samSum").c_str(), n_points, lower, upper);
      hScanSamSum->SetTitle(std::string(std::string("sample_sum, ") + name + ";" + name + "; -2(ln L_{sample_sum)").c_str());
      // Scan over the parameter space
      for (int j = 0; j < n_points; j++) {

        if (j % countwidth == 0) {
          std::cout << j << "/" << n_points << " (" << double(j)/double(n_points) * 100 << "%)" << std::endl;
        }

        // Set the parameter
        (*it)->setParProp(i, hScan->GetBinCenter(j+1));

        // Reweight the MC
        sample->reweight(fake);

        // Get the -log L likelihoods
        double samplellh = sample->getLikelihood();
        double xsecllh = sample->GetXsecCov()->getLikelihood();
        double fluxllh = sample->GetFluxCov()->getLikelihood();
        double nd280llh = sample->GetSimpleDetCov()->getLikelihood();
        double totalllh = samplellh + xsecllh + fluxllh + nd280llh;
        //WARNING
        double sample0pllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuCC0Pi);
        double sampleNpllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuCC0PiNp);
        double sample1pillh = sample->getSampleLikelihood(SampleId::kFGD1NuMuCC1Pi);
        double sampleOtherllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuCCOther);
            
        double sample0piRHCllh = sample->getSampleLikelihood(SampleId::kFGD1AntiNuMuCC0Pi);
        double sample1piRHCllh = sample->getSampleLikelihood(SampleId::kFGD1AntiNuMuCC1Pi);
        double sampleOtherRHCllh = sample->getSampleLikelihood(SampleId::kFGD1AntiNuMuCCOther);
        
        double sample0piBKGllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuBkgInAntiNuModeCC0Pi);
        double sample1piBKGllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuBkgInAntiNuModeCC1Pi);
        double sampleOtherBKGllh = sample->getSampleLikelihood(SampleId::kFGD1NuMuBkgInAntiNuModeCCOther);
        
            
        double sample0pillh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuCC0Pi);
        double sample1pillh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuCC1Pi);
        double sampleOtherllh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuCCOther);
            
        double sample0piRHCllh2 = sample->getSampleLikelihood(SampleId::kFGD2AntiNuMuCC0Pi);
        double sample1piRHCllh2 = sample->getSampleLikelihood(SampleId::kFGD2AntiNuMuCC1Pi);
        double sampleOtherRHCllh2 = sample->getSampleLikelihood(SampleId::kFGD2AntiNuMuCCOther);
        
        double sample0piBKGllh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuBkgInAntiNuModeCC0Pi);
        double sample1piBKGllh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuBkgInAntiNuModeCC1Pi);
        double sampleOtherBKGllh2 = sample->getSampleLikelihood(SampleId::kFGD2NuMuBkgInAntiNuModeCCOther);
        
    
        double sampleSum = sample0pllh + sampleNpllh + sample1pillh + sampleOtherllh + sample0piRHCllh + sample1piRHCllh + sampleOtherRHCllh + sample0piBKGllh + sample1piBKGllh + sampleOtherBKGllh + sample0pillh2 + sample1pillh2 + sampleOtherllh2 + sample0piRHCllh2 + sample1piRHCllh2 + sampleOtherRHCllh2 +sample0piBKGllh2 + sample1piBKGllh2 + sampleOtherBKGllh2;
        
        
        hScanFlux->SetBinContent(j+1, 2*fluxllh);
        hScanXSec->SetBinContent(j+1, 2*xsecllh);
        hScanND->SetBinContent(j+1, 2*nd280llh);
        hScanSam->SetBinContent(j+1, 2*samplellh);
        hScan->SetBinContent(j+1, 2*totalllh);
        //WARNING
        hScanSam0p->SetBinContent(j+1, 2*sample0pllh);
        hScanSamNp->SetBinContent(j+1, 2*sampleNpllh);
        hScanSam1pi->SetBinContent(j+1, 2*sample1pillh);
        hScanSamOther->SetBinContent(j+1, 2*sampleOtherllh);
        hScanSam0piRHC->SetBinContent(j+1, 2*sample0piRHCllh);
        hScanSam1piRHC->SetBinContent(j+1, 2*sample1piRHCllh);
        hScanSamOtherRHC->SetBinContent(j+1, 2*sampleOtherRHCllh);
        hScanSam0piBKG->SetBinContent(j+1, 2*sample0piBKGllh);
        hScanSam1piBKG->SetBinContent(j+1, 2*sample1piBKGllh);
        hScanSamOtherBKG->SetBinContent(j+1, 2*sampleOtherBKGllh);
        
        hScanSam0pi2->SetBinContent(j+1, 2*sample0pillh2);
        hScanSam1pi2->SetBinContent(j+1, 2*sample1pillh2);
        hScanSamOther2->SetBinContent(j+1, 2*sampleOtherllh2);
        hScanSam0piRHC2->SetBinContent(j+1, 2*sample0piRHCllh2);
        hScanSam1piRHC2->SetBinContent(j+1, 2*sample1piRHCllh2);
        hScanSamOtherRHC2->SetBinContent(j+1, 2*sampleOtherRHCllh2);
        hScanSam0piBKG2->SetBinContent(j+1, 2*sample0piBKGllh2);
        hScanSam1piBKG2->SetBinContent(j+1, 2*sample1piBKGllh2);
        hScanSamOtherBKG2->SetBinContent(j+1, 2*sampleOtherBKGllh2);
        
        
        hScanSamSum->SetBinContent(j+1, 2*sampleSum);
      }

      Flux_LLH->cd();
      hScanFlux->Write();
      XSec_LLH->cd();
      hScanXSec->Write();
      ND280_LLH->cd();
      hScanND->Write();
      Sample_LLH->cd();
      hScanSam->Write();
      Total_LLH->cd();
      hScan->Write();
      
      //WARNING
      CC0PI_0p_LLH->cd(); 
      hScanSam0p->Write();
      CC0PI_Np_LLH->cd(); 
      hScanSamNp->Write();
      CC1PI_LLH->cd();
      hScanSam1pi->Write();
      CCOther_LLH->cd();
      hScanSamOther->Write();
      
      CC0Pi_RHC_LLH->cd();
      hScanSam0piRHC->Write();
      CC1Pi_RHC_LLH->cd();
      hScanSam1piRHC->Write();
      CCOtgher_RHC_LLH->cd();
      hScanSamOtherRHC->Write();
      
      CC0Pi_BKG_LLH->cd();
      hScanSam0piBKG->Write();
      CC1Pi_BKG_LLH->cd();
      hScanSam1piBKG->Write();
      CCOtgher_BKG_LLH->cd();
      hScanSamOtherBKG->Write();
      

      CC0PI_LLH2->cd(); 
      hScanSam0pi2->Write();
      CC1PI_LLH2->cd();
      hScanSam1pi2->Write();
      CCOther_LLH2->cd();
      hScanSamOther2->Write();
      
      CC0Pi_RHC_LLH2->cd();
      hScanSam0piRHC2->Write();
      CC1Pi_RHC_LLH2->cd();
      hScanSam1piRHC2->Write();
      CCOtgher_RHC_LLH2->cd();
      hScanSamOtherRHC2->Write();
      
      CC0Pi_BKG_LLH2->cd();
      hScanSam0piBKG2->Write();
      CC1Pi_BKG_LLH2->cd();
      hScanSam1piBKG2->Write();
      CCOtgher_BKG_LLH2->cd();
      hScanSamOtherBKG2->Write();
      
      Sample_SUM_LLH->cd();
      hScanSamSum->Write();
      
      delete hScanFlux;
      delete hScanXSec;
      delete hScanND;
      delete hScanSam;
      delete hScan;
      //WARNING
      delete hScanSam0p;
      delete hScanSamNp;
      delete hScanSam1pi;
      delete hScanSamOther;
      delete hScanSam0piRHC;
      delete hScanSam1piRHC;
      delete hScanSamOtherRHC;
      delete hScanSam0piBKG;
      delete hScanSam1piBKG;
      delete hScanSamOtherBKG;

      delete hScanSam0pi2;
      delete hScanSam1pi2;
      delete hScanSamOther2;
      delete hScanSam0piRHC2;
      delete hScanSam1piRHC2;
      delete hScanSamOtherRHC2;
      delete hScanSam0piBKG2;
      delete hScanSam1piBKG2;
      delete hScanSamOtherBKG2;
      
      delete hScanSamSum;
      
      hScanFlux = NULL;
      hScanXSec = NULL;
      hScanND = NULL;
      hScanSam = NULL;
      hScan = NULL;
      //WARNING
      hScanSam0p = NULL;
      hScanSamNp = NULL;
      hScanSam1pi = NULL;
      hScanSamOther = NULL;
      hScanSam0piRHC = NULL;
      hScanSam1piRHC = NULL;
      hScanSamOtherRHC = NULL; 
      hScanSam0piBKG = NULL; 
      hScanSam1piBKG = NULL;
      hScanSamOtherBKG = NULL;
      
      hScanSam0pi2 = NULL;
      hScanSam1pi2 = NULL;
      hScanSamOther2 = NULL;
      hScanSam0piRHC2 = NULL;
      hScanSam1piRHC2 = NULL;
      hScanSamOtherRHC2 = NULL; 
      hScanSam0piBKG2 = NULL; 
      hScanSam1piBKG2 = NULL;
      hScanSamOtherBKG2 = NULL;
      
      hScanSamSum = NULL;
      
      // Reset the current parameter to its prior for the next parameter scan
      (*it)->setParProp(i, nom);
    }
  }

  output->Close();
  std::cout << "Wrote scan to " << output->GetName() << std::endl;

  delete output;


  return 0;

}
