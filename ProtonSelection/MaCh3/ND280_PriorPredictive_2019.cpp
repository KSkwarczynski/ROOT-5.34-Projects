#include <iostream>
#include <vector>

#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TH2Poly.h>
#include <THStack.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TApplication.h>

#include "samplePDF/samplePDFND2019.h"
#include "samplePDF/samplePDFND2019GPU.h"
#include "covariance/covarianceFlux.h"
#include "covariance/covarianceXsec2015.h"
#include "covariance/covarianceNDDet_2019Poly.h"

#include "mcmc/mcmc.h"
#include "manager/manager.h"

int likelihood;

// *******************
// Class to hold the variations, throws and so on
class SampleSummary {
// *******************
  public:
    SampleSummary(int nSamples, const std::string &Outputfile);
    ~SampleSummary();

    void AddData(std::vector<TH2Poly*> &DataHist);
  void AddNominal(std::vector<TH2Poly*> &NominalHist, std::vector<TH2Poly*> &W2Nom);
    void AddThrow(std::vector<TH2Poly*> &MCHist, std::vector<TH2Poly*> &W2Hist, double LLHPenalty = 0.0);

    void Write();

  private:
    TRandom3* rnd;
    bool first_pass;

    // Finalise the distributions from the thrown samples
    void inline MakePriorPredictive();

    void inline PrepareTree();

    // Helper functions to calculate likelihoods for TH1D and TH2Ds
    void inline CalcLLH(TH2Poly * const & Data, TH2Poly * const & MC, TH2Poly * const & W2);
    void inline CalcLLH(TH1D * const & Data, TH1D * const & MC, TH1D * const & W2);

    double inline GetLLH(TH2Poly * const & Data, TH2Poly * const & MC, TH2Poly * const & W2);
    double inline GetLLH(TH1D * const & Data, TH1D * const & MC, TH1D * const & W2);

    // Helper functions to change titles etc of finished plots, calculate pvalues etc
    void inline MakeCutLLH();
    void inline MakeCutLLH1D(TH1D *Histogram, TH1D *Reference = NULL, TH1D *RefW2 = NULL);
    void inline MakeCutLLH2D(TH2D *Histogram);
    void inline MakeChi2Hists();

    // Check the length of psyche samples agrees
    bool inline CheckPsycheSamples(int Length);

    // Helper to make ratio histograms
    template<class HistType> HistType* RatioHists(HistType* NumHist, HistType* DenomHist);
    // Helper to make ratio of TH2Polys
    TH2Poly* RatioPolys(TH2Poly* NumPoly, TH2Poly* DenomPoly);

    // Helper to project TH2D onto axis
    TH1D* ProjectHist(TH2D* Histogram, bool ProjectX);
    // Helper to project TH2Poly onto axis
    TH1D* ProjectPoly(TH2Poly* Histogram, bool ProjectX, int selection);
  
    // Helper to Normalise histograms
    template<class HistType> HistType* NormaliseHist(HistType* Histogram);
    // Helper to Normalise histograms
    TH2Poly* NormalisePoly(TH2Poly* Histogram);
    // Helper to scale th2poly analogous to th2d scale with option "width"
    TH2Poly* PolyScaleWidth(TH2Poly *Histogram, double scale);
    // Helper to calc integral of th2poly analogous to th2d integra; with option "width"
    double PolyIntegralWidth(TH2Poly *Histogram);
    // Function to set the binning that polys are projected onto
    void SampleSummary::SetBinning(SampleId::SampleEnum Selection, std::vector<double> & BinningX,std::vector<double> & BinningY);

    // Vector of vectors which holds the loaded MC histograms
    std::vector<std::vector<TH2Poly*> > MCVector;
    std::vector<std::vector<TH2Poly*> > W2MCVector;
    // Vector to hold the penalty term
    std::vector<double> LLHPenaltyVector;
    // Vectors to hold exact LLH
    std::vector<double> LLH_DrawFluc_V;
    std::vector<double> LLH_DrawData_V;
    std::vector<double> LLH_DrawFlucDraw_V;

    // A map to keep track of what psyche sample indices we want. Save some read time
    std::vector<int> PsycheSampleMap;
    std::vector<std::string> SampleNames;

    // The prior predictive for the whole selection: this gets built after adding in the toys. Now an array of Th1ds, 1 for each poly bin, for each sample
    TH1D ***PriorHist;
    // The data histogram for the selection
    TH2Poly **DataHist;
    // The nominal histogram for the selection
    TH2Poly **NominalHist;
    // The w2 histograms
    TH2Poly **W2NomHist;
    TH2Poly **W2MeanHist;
    TH2Poly **W2ModeHist;
    TH1D ***w2Hist;
  
    // The histogram containing the lnL for each throw
    TH1D *lnLHist;
    // The lnLhist for the draw vs MC
    TH1D *lnLHist_draw;
    // The lnLhist for the draw vs MC fluctuated
    TH1D *lnLHist_drawfluc;
    // The lnLhist for the draw vs draw fluctuated
    TH1D *lnLHist_drawflucdraw;
    // The lnLhist for the draw vs data
    TH1D *lnLHist_drawdata;
    // The 2D lnLhist, showing (draw vs data) and (draw vs fluct), anything above y=x axis is the p-value
    TH2D *lnLDrawHist;
    // The 2D lnLHist, showing (draw vs data) and (draw vs draw fluct), anything above y=x axis is the p-value
    TH2D *lnLFlucHist;

    // The histogram containing the lnL for each throw for each sample
    TH1D **lnLHist_Sample;

    // The LLH distribution in pmu cosmu for using the mean in each bin
    TH2Poly **lnLHist_Mean;
    // The LLH distribution in pmu cosmu for using the mode in each bin
    TH2Poly **lnLHist_Mode;
    // The prior predictive distribution in pmu cosmu using the mean
    TH2Poly **MeanHist;
    // The prior predictive distribution in pmu cosmu using the mode
    TH2Poly **ModeHist;

    // Holds the event rate for the distribution
    TH1D **SumHist;
    // Holds the total event rate
    TH1D *EventHist;
    // Holds the bin-by-bin LLH for the mean prior predictive vs the data
    TH1D **lnLHist_Mean1D;
    // Holds the bin-by-bin LLH for the mode prior predictive vs the data
    TH1D **lnLHist_Mode1D;

    // Number of samples
    int nSamples;

    // Number of throws
    int nThrows;

    // Max Number of Bins in a sample
    int maxBins;

    // Total LLH for the prior predictive distribution
    double llh_total;

    // Output filename
    std::string OutputName;
    TFile *Outputfile;

    // TTree which we save useful information to
    TTree *OutputTree;
    // Data vs Draw
    double *llh_data_draw;
    // Data vs Fluctuated Draw
    double *llh_data_drawfluc;
    // Data vs Fluctuated Predictive
    double *llh_data_predfluc;

    // Draw vs Predictive
    double *llh_draw_pred;

    // Fluctuated Draw vs Predictive
    double *llh_drawfluc_pred;
    // Fluctuated Draw vs Fluctuated Predictive
    double *llh_drawfluc_predfluc;
    // Fluctuated Draw vs Draw
    double *llh_drawfluc_draw;

    // Fluctuated Predictive vs Predictive
    double *llh_predfluc_pred;
    // Fluctuated Predicitve vs Draw
    double *llh_predfluc_draw;

    // LLH penalty for each throw
    double llh_penalty;

    // Event rate for each throw
    double event_rate;

    // Data vs Draw
    double total_llh_data_draw;
    // Data vs Fluctuated Draw
    double total_llh_data_drawfluc;
    // Data vs Fluctuated Predictive
    double total_llh_data_predfluc;

    // Draw vs Predictive
    double total_llh_draw_pred;

    // Fluctuated Draw vs Predictive
    double total_llh_drawfluc_pred;
    // Fluctuated Draw vs Fluctuated Predictive
    double total_llh_drawfluc_predfluc;
    // Fluctuated Draw vs Draw
    double total_llh_drawfluc_draw;

    // Fluctuated Predictive vs Predictive
    double total_llh_predfluc_pred;
    // Fluctuated Predicitve vs Draw
    double total_llh_predfluc_draw;
};

// *******************
// The constructor
SampleSummary::SampleSummary(const int PsycheSamples, const std::string &Filename) {
// *******************

  std::cout << "Making sample summary class..." << std::endl;

  OutputName = Filename;
  nSamples = PsycheSamples;
  nThrows = 0;
  first_pass = true;
  Outputfile = NULL;
  OutputTree = NULL;

  rnd = new TRandom3();

  DataHist = new TH2Poly*[nSamples];
  NominalHist = new TH2Poly*[nSamples];
  PriorHist = new TH1D**[nSamples];
  W2NomHist = new TH2Poly*[nSamples];
  w2Hist = new TH1D**[nSamples];

  lnLHist_Mean = new TH2Poly*[nSamples];
  lnLHist_Mode = new TH2Poly*[nSamples];
  MeanHist = new TH2Poly*[nSamples];
  ModeHist = new TH2Poly*[nSamples];
  W2MeanHist = new TH2Poly*[nSamples];
  W2ModeHist = new TH2Poly*[nSamples];
  SumHist = new TH1D*[nSamples];
  lnLHist_Mean1D = new TH1D*[nSamples];
  lnLHist_Mode1D = new TH1D*[nSamples];
  lnLHist_Sample = new TH1D*[nSamples];

  lnLHist = new TH1D("lnLHist_predpredfluc", "lnLHist_predpredfluc", 100, 0, 100);
  lnLHist->GetXaxis()->SetTitle("-2LLH (Pred Fluc, Pred)");
  lnLHist->GetYaxis()->SetTitle("Counts");

  lnLHist_draw = new TH1D("lnLHist_preddraw", "lnLHist_preddraw", 100, 0, 100);
  lnLHist_draw->GetXaxis()->SetTitle("-2LLH (Draw, Pred)");
  lnLHist_draw->GetYaxis()->SetTitle("Counts");

  lnLHist_drawdata = new TH1D("lnLHist_drawdata", "lnLHist_drawdata", 100, 0, 100);
  lnLHist_drawdata->GetXaxis()->SetTitle("-2LLH (Data, Draw)");
  lnLHist_drawdata->GetYaxis()->SetTitle("Counts");

  lnLHist_drawfluc = new TH1D("lnLHist_drawpredfluc", "lnLHist_drawpredfluc", 100, 0, 100);
  lnLHist_drawfluc->GetXaxis()->SetTitle("-2LLH (Pred Fluc, Draw)");
  lnLHist_drawfluc->GetYaxis()->SetTitle("Counts");

  lnLHist_drawflucdraw = new TH1D("lnLHist_drawflucdraw", "lnLHist_drawflucdraw", 100, 0, 100);
  lnLHist_drawflucdraw->GetXaxis()->SetTitle("-2LLH (Draw Fluc, Draw)");
  lnLHist_drawflucdraw->GetYaxis()->SetTitle("Counts");

  lnLDrawHist = new TH2D("lnLDrawHist", "lnLDrawHist", 100, 0, 100, 100, 0, 100);
  lnLDrawHist->GetXaxis()->SetTitle("-2LLH_{Draw, Pred Fluc}");
  lnLDrawHist->GetYaxis()->SetTitle("-2LLH_{Draw, Data}");

  lnLFlucHist = new TH2D("lnLFlucHist", "lnLFlucHist", 100, 0, 100, 100, 0, 100);
  lnLFlucHist->GetXaxis()->SetTitle("-2LLH_{Draw, Draw Fluc}");
  lnLFlucHist->GetYaxis()->SetTitle("-2LLH_{Draw, Data}");

  EventHist = new TH1D("EventHist", "EventHist", 100, 0, 100);
  EventHist->GetXaxis()->SetTitle("Total event rate");
  EventHist->GetYaxis()->SetTitle("Counts");
  EventHist->SetLineWidth(2);

  for (int i = 0; i < nSamples; ++i) {
    DataHist[i] = NULL;
    NominalHist[i] = NULL;
    PriorHist[i] = NULL;
    SumHist[i] = NULL;
    MeanHist[i] = NULL;
    W2MeanHist[i] = NULL;
    W2ModeHist[i] = NULL;
    lnLHist_Mean[i] = NULL;
    lnLHist_Mode[i] = NULL;
    lnLHist_Mean1D[i] = NULL;
    lnLHist_Mode1D[i] = NULL;
    lnLHist_Sample[i] = NULL;
  }
}

// *******************
// Empty destructor
// Maybe should delete all the new?
SampleSummary::~SampleSummary() {
// *******************
}

// *******************
// Check size of psyche sample against size of vectors
bool SampleSummary::CheckPsycheSamples(int Length) {
// *******************
  bool ok = (SampleId::kNSamples == Length);
  if (!ok) {
    std::cerr << "Size of SampleVector input != number of psyche samples" << std::endl;
    std::cout << "Size of SampleVector: " << Length << std::endl;
    std::cout << "Size of Psyche samples: " << SampleId::kNSamples << std::endl;
    std::cerr << "Something has gone wrong with making the Samples" << std::endl;
    std::cerr << __FILE__ << ":" << __LINE__ << std::endl;
    throw;
  }
  return ok;
}

// *******************
// Add a data histogram to the list (will have N_psyche_samples of these)
// Since the data doesn't change with varying the MC
void SampleSummary::AddData(std::vector<TH2Poly*> &Data) {
// *******************
  maxBins=0;
  int Length = Data.size();
  // Check length of psyche samples are OK
  if (!CheckPsycheSamples(Length)) throw;
  for (int i = 0; i < Length; ++i) {
    if (Data[i] == NULL) {
      DataHist[i] = NULL;
    } else {
      PsycheSampleMap.push_back(i);
      DataHist[i] = (TH2Poly*)(Data[i]->Clone());
      if(DataHist[i]->GetNumberOfBins() > maxBins)
	maxBins = DataHist[i]->GetNumberOfBins();;
    }
  }
}

// *******************
// Add the nominal histograms to the list (will have N_psyche_samples of these)
void SampleSummary::AddNominal(std::vector<TH2Poly*> &Nominal, std::vector<TH2Poly*> &NomW2) {
// *******************

  /*// Initialise the z-axis bins for the TH3D* PriorPredictive
  const int nZbins = 5000;
  double zBins[nZbins+1];
  // Go from 0 to 2000 in 5000 bins in z
  for (int i = 0; i < nZbins+1; ++i) {
    zBins[i] = 0.0;
    }*/

  int Length = Nominal.size();
  if (!CheckPsycheSamples(Length)) throw;
  // Loop over the lenght of nominal and set the initial distributions up
  for (int i = 0; i < Length; ++i) {

  // If NULL it indicates the selection was turned off, so initialise all the hists to NULL
    if (Nominal[i] == NULL) {
      PriorHist[i] = NULL;
      NominalHist[i] = NULL;
      W2NomHist[i] = NULL;
      lnLHist_Mean[i] = NULL;
      lnLHist_Mode[i] = NULL;
      MeanHist[i] = NULL;
      ModeHist[i] = NULL;
      W2MeanHist[i] = NULL;
      W2ModeHist[i] = NULL;
      SumHist[i] = NULL;
      lnLHist_Sample[i] = NULL;
      // If not NULL it indicates the selection was turned on, so initialise the privates
    } else {
      NominalHist[i] = (TH2Poly*)(Nominal[i]->Clone());
      std::string name = std::string(NominalHist[i]->GetName());
      name = name.substr(0, name.find("_nom"));
      W2NomHist[i] = (TH2Poly*)(NomW2[i]->Clone());
      name = std::string(NominalHist[i]->GetName());
      name = name.substr(0, name.find("_w2"));
      //      double Maximum = NominalHist[i]->GetMaximum()*1.3;
      //double Minimum = NominalHist[i]->GetMinimum()*0.7;
      //for (int z = 0; z < nZbins+1; ++z) {
      //zBins[z] = double(Minimum+(Maximum-Minimum))*(double(z)/double(nZbins));
      //}

      PriorHist[i] = new TH1D*[maxBins];
      w2Hist[i] = new TH1D*[maxBins];
      //      w2Hist[i] = new TH1D*[maxBins];
      //      PriorHist[i] = new TH3D((name+"_PP").c_str(), (name+"_PP").c_str(), 
      //          NominalHist[i]->GetXaxis()->GetNbins(), NominalHist[i]->GetXaxis()->GetXbins()->GetArray(),
      //  NominalHist[i]->GetYaxis()->GetNbins(), NominalHist[i]->GetYaxis()->GetXbins()->GetArray(),
      //  nZbins, zBins);
    //PriorHist[i]->GetXaxis()->SetTitle(NominalHist[i]->GetXaxis()->GetTitle());
    // PriorHist[i]->GetYaxis()->SetTitle(NominalHist[i]->GetYaxis()->GetTitle());
    //PriorHist[i]->GetZaxis()->SetTitle("Events in bin");

      lnLHist_Mean[i] = (TH2Poly*)(NominalHist[i]->Clone());
      lnLHist_Mean[i]->SetNameTitle((name+"_MeanlnL").c_str(), (name+"_MeanlnL").c_str());
      lnLHist_Mean[i]->Reset("");
      lnLHist_Mean[i]->GetZaxis()->SetTitle("-2lnL_{sample} #times sign(MC-data)");

      lnLHist_Mode[i] = (TH2Poly*)(NominalHist[i]->Clone());
      lnLHist_Mode[i]->SetNameTitle((name+"_ModelnL").c_str(), (name+"_ModelnL").c_str());
      lnLHist_Mode[i]->Reset("");
      lnLHist_Mode[i]->GetZaxis()->SetTitle("-2lnL_{sample} #times sign(MC-data)");

      MeanHist[i] = (TH2Poly*)(NominalHist[i]->Clone());
      MeanHist[i]->SetNameTitle((name+"_mean").c_str(), (name+"_mean").c_str());
      MeanHist[i]->Reset("");
      MeanHist[i]->GetZaxis()->SetTitle("Mean");

      ModeHist[i] = (TH2Poly*)(NominalHist[i]->Clone());
      ModeHist[i]->SetNameTitle((name+"_mode").c_str(), (name+"_mode").c_str());
      ModeHist[i]->Reset("");
      ModeHist[i]->GetZaxis()->SetTitle("Mode");

      W2MeanHist[i] = (TH2Poly*)(NominalHist[i]->Clone());
      W2MeanHist[i]->SetNameTitle((name+"_w2mean").c_str(), (name+"_w2mean").c_str());
      W2MeanHist[i]->Reset("");
      W2MeanHist[i]->GetZaxis()->SetTitle("W2Mean");

      W2ModeHist[i] = (TH2Poly*)(NominalHist[i]->Clone());
      W2ModeHist[i]->SetNameTitle((name+"_w2mode").c_str(), (name+"_w2mode").c_str());
      W2ModeHist[i]->Reset("");
      W2ModeHist[i]->GetZaxis()->SetTitle("W2Mode");

      SumHist[i] = new TH1D((name+"_sum").c_str(),(name+"_sum").c_str(), 100, NoOverflowIntegral(NominalHist[i])*0.95, NoOverflowIntegral(NominalHist[i])*1.05);
      SumHist[i]->GetXaxis()->SetTitle("N_{events}");
      SumHist[i]->GetYaxis()->SetTitle("Counts");
      double Integral = NoOverflowIntegral(DataHist[i]);
      std::stringstream ss;
      ss << Integral;
      SumHist[i]->SetTitle((std::string(SumHist[i]->GetTitle())+"_"+ss.str()).c_str());

      // Declare the lnL histograms
      // Get the likelihood for data and nominal hist
      double llh = GetLLH(DataHist[i], NominalHist[i], W2NomHist[i]);

      lnLHist_Mean1D[i] = new TH1D((name+"_MeanlnL1D").c_str(),(name+"_MeanlnL1D").c_str(), 50, 0, 20);
      lnLHist_Mean1D[i]->GetXaxis()->SetTitle("-2LLH");
      lnLHist_Mean1D[i]->GetYaxis()->SetTitle("Counts");

      lnLHist_Mode1D[i] = new TH1D((name+"_ModelnL1D").c_str(),(name+"_ModelnL1D").c_str(), 50, 0, 20);
      lnLHist_Mode1D[i]->GetXaxis()->SetTitle("-2LLH");
      lnLHist_Mode1D[i]->GetYaxis()->SetTitle("Counts");

      lnLHist_Sample[i] = new TH1D((name+"_lnL").c_str(),(name+"_lnL").c_str(), 100, llh*0.9, llh*1.1);
      lnLHist_Sample[i]->GetXaxis()->SetTitle("-2LLH");
      lnLHist_Sample[i]->GetYaxis()->SetTitle("Counts");
    }
  }

}

// *******************
// Add a throw from the MCMC to the prior predictive
// The input here is nSamples long
void SampleSummary::AddThrow(std::vector<TH2Poly*> &SampleVector, std::vector<TH2Poly*> &W2Vec, double LLHPenalty) {
  // *******************

  nThrows++;

  int size = SampleVector.size();
  if (!CheckPsycheSamples(size)) throw;

  // Push back the throw
  MCVector.push_back(SampleVector);
  LLHPenaltyVector.push_back(LLHPenalty);
  W2MCVector.push_back(W2Vec);

  // Loop over the sameples
  for (int z = 0; z < SampleId::kNSamples; ++z) {
    if (SampleVector[z] == NULL) continue;

    // Rebin the prior hist
    if (first_pass) {/*


      // Initialise the z-axis bins for the TH3D* PriorPredictive
      const int nZbins = 5000;
      double zBins[nZbins+1];
      double Maximum = SampleVector[z]->GetMaximum()*1.2;
      double Minimum = SampleVector[z]->GetMinimum()*0.8;
      for (int k = 0; k < nZbins+1; ++k) {
        zBins[k] = double(Minimum+(Maximum-Minimum))*(double(k)/double(nZbins));
      }

      PriorHist[z]->SetBins(NominalHist[z]->GetXaxis()->GetNbins(), NominalHist[z]->GetXaxis()->GetXbins()->GetArray(), NominalHist[z]->GetYaxis()->GetNbins(), NominalHist[z]->GetYaxis()->GetXbins()->GetArray(), nZbins, zBins);
		     */
      //Initialise TH1D which corresponds to each bin in the sample's th2poly
      std::string name = std::string(SampleVector[z]->GetName());
      for (int i =0; i<=SampleVector[z]->GetNumberOfBins(); i++){
	
	const int nXBins = 5000;
	double Maximum = SampleVector[z]->GetMaximum()*1.2;
	double Minimum = SampleVector[z]->GetMinimum()*0.8;
	double MaximumW2 = W2Vec[z]->GetMaximum()*1.2;
        double MinimumW2 = W2Vec[z]->GetMinimum()*0.8;
	std::stringstream ss;
	ss << "_" << i;
	PriorHist[z][i] = new TH1D((std::string(SampleVector[z]->GetName())+ss.str()).c_str(), (std::string(SampleVector[z]->GetTitle())+ss.str()).c_str(),nXBins,Minimum,Maximum);
	w2Hist[z][i] = new TH1D((std::string(SampleVector[z]->GetName())+ss.str()+"_w2").c_str(), (std::string(SampleVector[z]->GetTitle())+ss.str()+"_w2").c_str(),nXBins,MinimumW2,MaximumW2);
      }      
      
      double Minimum2 = NoOverflowIntegral(SampleVector[z])*0.95;
      double Maximum2 = NoOverflowIntegral(SampleVector[z])*1.05;
      if (Minimum2 > NoOverflowIntegral(DataHist[z])*0.95) {
        Minimum2 = NoOverflowIntegral(DataHist[z])*0.95;
      }
      if (Maximum2 < NoOverflowIntegral(DataHist[z])*1.05) {
        Maximum2 = NoOverflowIntegral(DataHist[z])*1.05;//Make these poly integrals remember
      }
      SumHist[z]->SetBins(SumHist[z]->GetNbinsX(), Minimum2, Maximum2);
    }
    // Fill the sum histogram with the integral of the sampled distribution
    SumHist[z]->Fill(NoOverflowIntegral(SampleVector[z]));
    // Loop over the distribution and fill the prior predictive
    for (int i = 1; i <= SampleVector[z]->GetNumberOfBins(); ++i) {
      double Content = SampleVector[z]->GetBinContent(i);
      PriorHist[z][i]->Fill(Content);
      double w2 = W2Vec[z]->GetBinContent(i);
      w2Hist[z][i]->Fill(w2);
    } // end bin loop
  } // end nd280 samples loop
  first_pass = false;
} // end AddThrow

// **********************
void SampleSummary::PrepareTree() {
// **********************

  // Number of good samples
  int nPsycheSamples = PsycheSampleMap.size();

  // The array of doubles we write to the TTree
  // Data vs Draw
  llh_data_draw = new double[nPsycheSamples];
  // Data vs Fluctuated Draw
  llh_data_drawfluc = new double[nPsycheSamples];
  // Data vs Fluctuated Predictive
  llh_data_predfluc = new double[nPsycheSamples];

  // Draw vs Predictive
  llh_draw_pred = new double[nPsycheSamples];

  // Fluctuated Draw vs Predictive
  llh_drawfluc_pred = new double[nPsycheSamples];
  // Fluctuated Draw vs Fluctuated Predictive
  llh_drawfluc_predfluc = new double[nPsycheSamples];
  // Fluctuated Draw vs Draw
  llh_drawfluc_draw = new double[nPsycheSamples];
  // Fluctuated Predictive vs Predictive
  llh_predfluc_pred = new double[nPsycheSamples];
  // Fluctuated Predicitve vs Draw
  llh_predfluc_draw = new double[nPsycheSamples];

  // The output tree we're going to write to
  OutputTree = new TTree("LLH_draws", "LLH_draws");

  // Loop over the samples and set the addresses of the variables to write to file
  for (int i = 0; i < nPsycheSamples; ++i) {
    // Get the psyche sample number
    int PsycheSample = PsycheSampleMap[i];
    // Get the name
    std::string SampleName = SampleId::ConvertSample(SampleId::SampleEnum(PsycheSample));
    
    // Strip out spaces
    while (SampleName.find(" ") != std::string::npos) {
      SampleName.replace(SampleName.find(" "), 1, std::string("_"));
    }
    // Also strip out - signs because it messes up TBranches
    while (SampleName.find("-") != std::string::npos) {
      SampleName.replace(SampleName.find("-"), 1, std::string("_"));
    }

    SampleNames.push_back(SampleName);

    OutputTree->Branch((SampleName+"_data_draw").c_str(),     &llh_data_draw[i]);
    OutputTree->Branch((SampleName+"_data_drawfluc").c_str(), &llh_data_drawfluc[i]);
    OutputTree->Branch((SampleName+"_data_predfluc").c_str(), &llh_data_predfluc[i]);
    OutputTree->Branch((SampleName+"_draw_pred").c_str(),     &llh_draw_pred[i]);
    OutputTree->Branch((SampleName+"_drawfluc_pred").c_str(), &llh_drawfluc_pred[i]);
    OutputTree->Branch((SampleName+"_drawfluc_predfluc").c_str(), &llh_drawfluc_predfluc[i]);
    OutputTree->Branch((SampleName+"_drawfluc_draw").c_str(), &llh_drawfluc_draw[i]);
    OutputTree->Branch((SampleName+"_predfluc_pred").c_str(), &llh_predfluc_pred[i]);
    OutputTree->Branch((SampleName+"_predfluc_draw").c_str(), &llh_predfluc_draw[i]);
  }

  OutputTree->Branch("LLH_Penalty",         &llh_penalty);
  OutputTree->Branch("Total_LLH_Data_Draw", &total_llh_data_draw);
  OutputTree->Branch("Total_LLH_Data_DrawFluc", &total_llh_data_drawfluc);
  OutputTree->Branch("Total_LLH_Data_PredFluc", &total_llh_data_predfluc);
  OutputTree->Branch("Total_LLH_Draw_Pred",     &total_llh_draw_pred);
  OutputTree->Branch("Total_LLH_DrawFluc_Pred", &total_llh_drawfluc_pred);
  OutputTree->Branch("Total_LLH_DrawFluc_PredFluc", &total_llh_drawfluc_predfluc);
  OutputTree->Branch("Total_LLH_DrawFluc_Draw", &total_llh_drawfluc_draw);
  OutputTree->Branch("Total_LLH_PredFluc_Pred", &total_llh_predfluc_pred);
  OutputTree->Branch("Total_LLH_PredFluc_Draw", total_llh_predfluc_draw);
  OutputTree->Branch("Event_Rate", &event_rate);
}

// *******************
// Write the contents to the file
void SampleSummary::Write() {
  // *******************

  // Make the output file (MakePriorPredictive call writes to this)
  std::string TempString = OutputName;
  TempString.replace(TempString.find(".root"), 5, std::string("_procsW2.root"));
  Outputfile = new TFile(TempString.c_str(), "RECREATE");
  // Prepare the output tree
  PrepareTree();

  std::cout << "Summarising " << nThrows << " throws..." << std::endl;
  // After all the throws are added finalise the sample
  std::cout << "DEBUG MakePriorPredictive  "<< std::endl;
  MakePriorPredictive();

  Outputfile->cd();
  TDirectory *Dir[SampleId::kNSamples];

  OutputTree->Write();

  // Make the various distributions
  lnLHist->Write();
  lnLHist_draw->Write();
  lnLHist_drawfluc->Write();
  lnLHist_drawflucdraw->Write();
  lnLHist_drawdata->Write();
  lnLDrawHist->Write();
  lnLFlucHist->Write();
  EventHist->Write();

  // Loop over each sample and write to file
  int nPsycheSamples = PsycheSampleMap.size();
  for (int j = 0; j < nPsycheSamples; ++j) {
    int i = PsycheSampleMap[j];
    
     // Skip the null histograms
    if (DataHist[i] == NULL || NoOverflowIntegral(DataHist[i]) == 0) continue;

    // Make a new direcotry
    Dir[i] = Outputfile->mkdir(ConvertSample(SampleId::SampleEnum(i)).c_str());
    Dir[i]->cd();

    // Make the data/MC ratio histogram
    TH2Poly *RatioHistMean = RatioPolys(DataHist[i], MeanHist[i]);
    RatioHistMean->GetZaxis()->SetTitle("Data/Mean");
    TH2Poly *RatioHistMode = RatioPolys(DataHist[i], ModeHist[i]);
    RatioHistMode->GetZaxis()->SetTitle("Data/Mode");
    TH2Poly *RatioHistNom = RatioPolys(DataHist[i], NominalHist[i]);
    RatioHistNom->GetZaxis()->SetTitle("Data/Nom");

    // And the normalised data histogram
    TH2Poly *DataNormHist = NormalisePoly(DataHist[i]);
    // Last true refers to if project along x or y
    TH1D *DataProjectX = ProjectPoly(DataHist[i], true, i);
    TH1D *DataProjectY = ProjectPoly(DataHist[i], false, i);

    TH2Poly *MeanNormHist = NormalisePoly(MeanHist[i]);
    TH2Poly *ModeNormHist = NormalisePoly(ModeHist[i]);
    TH1D *MeanProjectX = ProjectPoly(MeanHist[i], true, i);
    TH1D *MeanProjectY = ProjectPoly(MeanHist[i], false, i);
    TH1D *ModeProjectX = ProjectPoly(ModeHist[i], true, i);
    TH1D *ModeProjectY = ProjectPoly(ModeHist[i], false, i);

    TH1D *W2MeanProjectX = ProjectPoly(W2MeanHist[i], true, i);
    TH1D *W2MeanProjectY = ProjectPoly(W2MeanHist[i], false, i);
    TH1D *W2ModeProjectX = ProjectPoly(W2ModeHist[i], true, i);
    TH1D *W2ModeProjectY = ProjectPoly(W2ModeHist[i], false, i);

    TH2Poly *NomNormHist = NormalisePoly(NominalHist[i]);
    TH1D *NomProjectX = ProjectPoly(NominalHist[i], true, i);
    TH1D *NomProjectY = ProjectPoly(NominalHist[i], false, i);

    TH1D *W2NomProjectX = ProjectPoly(W2NomHist[i], true, i);
    TH1D *W2NomProjectY = ProjectPoly(W2NomHist[i], false, i);

    // Same for the TH2Ds
    CalcLLH(DataHist[i], NominalHist[i], W2NomHist[i]);
    CalcLLH(DataHist[i], MeanHist[i], W2MeanHist[i]);
    CalcLLH(DataHist[i], ModeHist[i], W2ModeHist[i]);

    // Calculate the log likelihood for the 1D dists
    // Sets the title of the second TH1D to the -2LLH
    CalcLLH(DataProjectX, NomProjectX, W2NomProjectX);
    CalcLLH(DataProjectX, MeanProjectX, W2MeanProjectX);
    CalcLLH(DataProjectX, ModeProjectX, W2ModeProjectX);
    CalcLLH(DataProjectY, NomProjectY, W2NomProjectY);
    CalcLLH(DataProjectY, MeanProjectY, W2MeanProjectY);
    CalcLLH(DataProjectY, ModeProjectY, W2ModeProjectY);

    // For the event rate histogram add a TLine to the data rate
    TLine *TempLine = new TLine(NoOverflowIntegral(DataHist[i]), SumHist[i]->GetMinimum(), NoOverflowIntegral(DataHist[i]), SumHist[i]->GetMaximum());
    TempLine->SetLineColor(kRed);
    TempLine->SetLineWidth(2);
    // Also fit a Gaussian because why not?
    TF1 *Fitter = new TF1("Fit", "gaus", SumHist[i]->GetBinLowEdge(1), SumHist[i]->GetBinLowEdge(SumHist[i]->GetNbinsX()+1));
    SumHist[i]->Fit(Fitter, "RQ");
    Fitter->SetLineColor(kRed-5);
    // Calculate a p-value
    double Above = 0.0;
    for (int z = 0; z < SumHist[i]->GetNbinsX(); ++z) {
      double xvalue = SumHist[i]->GetBinCenter(z+1);
      if (xvalue >= NoOverflowIntegral(DataHist[i])) {
        Above += SumHist[i]->GetBinContent(z+1);
      }
    }
    double pvalue = Above/SumHist[i]->Integral();
    TLegend *Legend = new TLegend(0.4, 0.67, 0.98, 0.93);
    Legend->SetFillColor(0);
    Legend->SetFillStyle(0);
    Legend->SetLineWidth(0);
    Legend->SetLineColor(0);
    Legend->AddEntry(TempLine, Form("Data, %.0f, p-value=%.2f", NoOverflowIntegral(DataHist[i]), pvalue), "l");
    Legend->AddEntry(SumHist[i], Form("MC, #mu=%.1f#pm%.1f", SumHist[i]->GetMean(), SumHist[i]->GetRMS()), "l");
    Legend->AddEntry(Fitter, Form("Gauss, #mu=%.1f#pm%.1f", Fitter->GetParameter(1), Fitter->GetParameter(2)), "l");
    std::string TempTitle = std::string(SumHist[i]->GetName());
    TempTitle += "_canv";
    TCanvas *TempCanvas = new TCanvas(TempTitle.c_str(), TempTitle.c_str(), 1024, 1024);
    TempCanvas->SetGridx();
    TempCanvas->SetGridy();
    TempCanvas->SetRightMargin(0.03);
    TempCanvas->SetBottomMargin(0.08);
    TempCanvas->SetLeftMargin(0.10);
    TempCanvas->SetTopMargin(0.06);
    TempCanvas->cd();
    SumHist[i]->Draw();
    TempLine->Draw("same");
    Fitter->Draw("same");
    Legend->Draw("same");
    TempCanvas->Write();
    delete TempLine;
    delete TempCanvas;
    delete Fitter;
    delete Legend;
    SumHist[i]->Write();


    OutputTree->Draw((SampleNames[j]+"_data_draw:"+SampleNames[j]+"_drawfluc_draw>>htemp").c_str());
    TH2D *TempHistogram = (TH2D*)((gDirectory->Get("htemp"))->Clone());
    TempHistogram->GetXaxis()->SetTitle("-2LLH(Draw Fluc, Draw)");
    TempHistogram->GetYaxis()->SetTitle("-2LLH(Data, Draw)");
    TempHistogram->SetNameTitle((SampleNames[j]+"_drawfluc_draw").c_str(), (SampleNames[j]+"_drawfluc_draw").c_str());
    MakeCutLLH2D(TempHistogram);
    TempHistogram->Write();
    delete TempHistogram;

    // Also write the 2D histograms for the p-value
    OutputTree->Draw((SampleNames[j]+"_data_draw:"+SampleNames[j]+"_predfluc_draw>>htemp2").c_str());
    TH2D *TempHistogram2 = (TH2D*)((gDirectory->Get("htemp2"))->Clone());
    TempHistogram2->GetXaxis()->SetTitle("-2LLH(Pred Fluc, Draw)");
    TempHistogram2->GetYaxis()->SetTitle("-2LLH(Data, Draw)");
    TempHistogram2->SetNameTitle((SampleNames[j]+"_predfluc_draw").c_str(), (SampleNames[j]+"_predfluc_draw").c_str());
    MakeCutLLH2D(TempHistogram2);
    TempHistogram2->Write();
    delete TempHistogram2;
   
    // Write the Histgorams to each folder
    DataHist[i]->Write();
    NominalHist[i]->Write();
    MeanHist[i]->Write();
    ModeHist[i]->Write();
    RatioHistMean->Write();
    RatioHistMode->Write();
    RatioHistNom->Write();

    W2NomHist[i]->Write();
    W2MeanHist[i]->Write();
    W2ModeHist[i]->Write();

    DataNormHist->Write();
    NomNormHist->Write();
    MeanNormHist->Write();
    ModeNormHist->Write();

    DataProjectX->Write();
    NomProjectX->Write();
    MeanProjectX->Write();
    ModeProjectX->Write();

    DataProjectY->Write();
    NomProjectY->Write();
    MeanProjectY->Write();
    ModeProjectY->Write();

    W2NomProjectX->Write();
    W2MeanProjectX->Write();
    W2ModeProjectX->Write();

    W2NomProjectY->Write();
    W2MeanProjectY->Write();
    W2ModeProjectY->Write();

    //PriorHist->Write();

    lnLHist_Mean[i]->Write();
    lnLHist_Mode[i]->Write();
    lnLHist_Mean1D[i]->Write();
    lnLHist_Mode1D[i]->Write();
    lnLHist_Sample[i]->Write();

    // Delete temporary objects
    delete RatioHistMean;
    delete RatioHistMode;
    delete RatioHistNom;

    delete DataNormHist;
    delete MeanNormHist;
    delete ModeNormHist;
    delete NomNormHist;

    delete DataProjectX;
    delete MeanProjectX;
    delete ModeProjectX;
    delete NomProjectX;

    delete DataProjectY;
    delete MeanProjectY;
    delete ModeProjectY;
    delete NomProjectY;

    delete W2NomProjectX;
    delete W2MeanProjectX;
    delete W2ModeProjectX;
  
    delete W2NomProjectY;
    delete W2MeanProjectY;
    delete W2ModeProjectY;

    std::cout << std::endl;
  }

  std::cout << "Wrote to " << Outputfile->GetName() << std::endl;
  Outputfile->Close();
}

// *******************
// Make the prior predictive distributions: fit Poissons etc
void SampleSummary::MakePriorPredictive() {
  // *******************

  // First make the projection on the z axis of the TH3D* for every pmu cosmu bin
  llh_total = 0.0;
  // Loop over the psyche samples
  for (int i = 0; i < SampleId::kNSamples; ++i) {

    // Skip disabled samples
    if (DataHist[i] == NULL || NoOverflowIntegral(DataHist[i]) == 0) continue;

    // Count the -2LLH for each histogram
    double negLogL_Mean = 0.0;
    double negLogL_Mode = 0.0;

    std::cout << "DEBUG FIRST LOOP INT " << i << std::endl;
    // Loop over each pmu cosmu bin
    for (int j = 1; j < DataHist[i]->GetNumberOfBins(); ++j) {

      // Just make a little fancy name
        std::cout << "DEBUG SECOND NAME " << j <<std::endl;
      std::string name = PriorHist[i][j]->GetName();
      std::cout << "DEBUG LOOP NAME " <<name.c_str() <<std::endl;
      //        std::stringstream ss;
      //ss << "_px_" << j << "_" ;
      
      // Make the prior predictive projection on z
      // The z axis of PriorPredictive is the bin content
      // Essentailly zooming in on one bin and looking at the mean and mode of that bin
      TH1D *Projection = (TH1D*)PriorHist[i][j]->Clone();//ProjectionZ((name+ss.str()).c_str(), j+1, j+1, k+1, k+1);
      TH1D *W2Projection = (TH1D*)w2Hist[i][j]->Clone();
      Projection->SetAxisRange(Projection->GetMean()-16*Projection->GetRMS(), Projection->GetMean()+16*Projection->GetRMS());
      W2Projection->SetAxisRange(W2Projection->GetMean()-16*W2Projection->GetRMS(), W2Projection->GetMean()+16*W2Projection->GetRMS());
      
      TH2PolyBin* bin = (TH2PolyBin*)DataHist[i]->GetBins()->At(j-1)->Clone();
      
      // Make the title
      std::stringstream ss2;
      ss2 << "p_{#mu} (" << bin->GetXMin() << "-" << bin->GetXMax() << ")";
      ss2 << " cos#theta_{#mu} (" << bin->GetYMin() << "-" << bin->GetYMax() << ")";
      Projection->SetNameTitle(ss2.str().c_str(), ss2.str().c_str());
      W2Projection->SetNameTitle(("w2"+ss2.str()).c_str(), ("w2"+ss2.str()).c_str());
      // Data content for the j,kth bin
      double nData = DataHist[i]->GetBinContent(j);
      
      // Get the mean for this projection for all the samples
      // This is the mean prediction for this given j,k bin
      double nMean = Projection->GetMean();
      double nMode = Projection->GetBinCenter(Projection->GetMaximumBin());
      double nW2Mean = W2Projection->GetMean();
      double nW2Mode = W2Projection->GetBinCenter(W2Projection->GetMaximumBin());
      
      double TempLLH_Mean = 0.0;
      double TempLLH_Mode = 0.0;
      double newMean = nMean;
      double newMode = nMode;
      double penaltyMean = 0.0;
      double penaltyMode = 0.0;
      double statMean = 0.0;
      double statMode = 0.0;
      
      // Getting LLH for mean and mode. Really should link this to helper function
      if(likelihood == kBarlowBeeston) {
	double fractional = sqrt(nW2Mean)/nMean;
	double temp = nMean*fractional*fractional-1;
	double temp2 = temp*temp + 4*nData*fractional*fractional;
	double beta = (-1*temp+sqrt(temp2))/2.;
	newMean = nMean*beta;
	if (fractional > 0) penaltyMean = (beta-1)*(beta-1)/(2*fractional*fractional);
	else penaltyMean = 0;
      }
      if (nData == 0) statMean = newMean;
      else if (newMean > 0) statMean = newMean-nData+nData*log(nData/newMean);
      
      if (likelihood == kIceCube) {
	// If there for some reason is 0 mc uncertainty, return the Poisson LLH
	if (nW2Mean == 0) {
	  penaltyMean = 0.0;
	}
	// Reset the penalties if there is mc uncertainty
	statMean = 0.0;
	penaltyMean = 0.0;
	// Auxillary variables
	long double b = nMean/nW2Mean;
	long double a = nMean*b+1;
	long double k = nData;
	// Use C99's implementation of log of gamma function to not be C++11 dependent
	statMean = -1*(a * logl(b) + lgammal(k+a) - lgammal(k+(long double)1) - ((k+a)*log1pl(b)) - lgammal(a));
      }
      
      if(nMean ==0)
	TempLLH_Mean=0;
      else{
	TempLLH_Mean = statMean+penaltyMean;
      }
      if(likelihood == kBarlowBeeston) {
	double fractional = sqrt(nW2Mode)/nMode;
	double temp = nMode*fractional*fractional-1;
	double temp2 = temp*temp + 4*nData*fractional*fractional;
	double beta = (-1*temp+sqrt(temp2))/2.;
	newMode = nMode*beta;
	if (fractional > 0) penaltyMode = (beta-1)*(beta-1)/(2*fractional*fractional);
	else penaltyMode = 0;
      }
      if (nData == 0) statMode = newMode;
      else if (newMode > 0) statMode = newMode-nData+nData*log(nData/newMode);
      if (likelihood == kIceCube) {
	// Ifn there for some reason is 0 mc uncertainty, return the Poisson LLH
	if (nW2Mode == 0) {
	  penaltyMode = 0.0;
	}
	// Reset the penalties if there is mc uncertainty
	statMode = 0.0;
	penaltyMode = 0.0;
	// Auxillary variables
	long double b = nMode/nW2Mode;
	long double a = nMode*b+1;
	long double k = nData;
	// Use C99's implementation of log of gamma function to not be C++11 dependent
	statMode = -1*(a * logl(b) + lgammal(k+a) - lgammal(k+(long double)1) - ((k+a)*log1pl(b)) - lgammal(a));
      }
      if(nMode ==0)
	TempLLH_Mode=0;
      else
	TempLLH_Mode = statMode+penaltyMode; 
      
      // Increment -2LLH
      negLogL_Mean += 2*TempLLH_Mean;
      negLogL_Mode += 2*TempLLH_Mode;
      
      // Set the content to the mean in the bin	
      MeanHist[i]->SetBinContent(j, MeanHist[i]->GetBinContent(j)+nMean);
      // Set the content to the mode in the bin
      ModeHist[i]->SetBinContent(j, ModeHist[i]->GetBinContent(j)+nMode);
      // Set the content to the mean in the bin
      W2MeanHist[i]->SetBinContent(j, W2MeanHist[i]->GetBinContent(j)+nW2Mean);
      // Set the content to the mode in the bin
      W2ModeHist[i]->SetBinContent(j, W2ModeHist[i]->GetBinContent(j)+nW2Mode);
      
      // Set the mean and average LLH for this given bin
      // Can use these hists to see where the largest -2LLH hists come from
      lnLHist_Mean[i]->SetBinContent(j, fabs(2.0*TempLLH_Mean));
      lnLHist_Mode[i]->SetBinContent(j, fabs(2.0*TempLLH_Mode));
      
      lnLHist_Mean1D[i]->Fill(fabs(2.0*TempLLH_Mean));
      lnLHist_Mode1D[i]->Fill(fabs(2.0*TempLLH_Mode));
      
      delete Projection;
      delete W2Projection;
    } // End loop over  bins
    llh_total += negLogL_Mean;
  } // End loop over samples

  // Now we have our prior predictive histogram and it's LLH
  std::cout << "Prior predictive LLH mean (sample only) = " << llh_total << std::endl;
  std::stringstream ss;
  ss << llh_total;
  lnLHist->SetTitle((std::string(lnLHist->GetTitle())+"_"+ss.str()).c_str());
  lnLHist_draw->SetTitle((std::string(lnLHist_draw->GetTitle())+"_"+ss.str()).c_str());

  // Now make the fluctuated hists of the MeanHist and ModeHist
  MakeChi2Hists();

  // Get the 1D LLH dists
  MakeCutLLH();

} // End MakePriorPredictive() function

// *******************
// Make the fluctuated histograms (2D and 1D) for the chi2s
// Essentially taking the MCMC draws and calculating their LLH to the Prior predicitve distribution
// And additionally taking the data histogram and calculating the LLH to the predictive distribution
// Additionally we calculate the chi2 of the draws (fluctuated) of  the MC with the prior predictive and plot it vs the chi2 from the draws of MCMC and the data
void SampleSummary::MakeChi2Hists() {
  // *******************

  std::cout << "Making the chi2 histograms..." << std::endl;
  // Have this to signify if we're doing the first pass
  first_pass = true;

  double AveragePenalty = 0;

  // Loop over the draws
  // Should look into multi-threading this. Would require temporary THxx structures from arrays
  for (int i = 0; i < nThrows; ++i) {

    if (i % (nThrows/10) == 0) {
      std::cout << "   On throw " << i << "/" << nThrows << " (" << int(double(i)*100.0/double(nThrows)) << "%)"<< std::endl;
    }

    // Set the total LLH to zero to initialise
    total_llh_data_draw = 0.0;
    total_llh_data_drawfluc = 0.0;
    total_llh_data_predfluc = 0.0;
    total_llh_draw_pred = 0.0;
    total_llh_drawfluc_pred = 0.0;
    total_llh_drawfluc_predfluc = 0.0;
    total_llh_drawfluc_draw = 0.0;
    total_llh_predfluc_pred = 0.0;
    total_llh_predfluc_draw = 0.0;
    event_rate = 0.0;

    // Save the double that gets written to file
    llh_penalty = LLHPenaltyVector[i];
    AveragePenalty += llh_penalty;

    // Loop over the samples
    int StdIt = 0;
    for (std::vector<int>::iterator it = PsycheSampleMap.begin(); it != PsycheSampleMap.end(); ++it, StdIt++) {

      int j = *it;
      // Get the ith draw for the jth psyche sample
      TH2Poly *DrawHist = MCVector[i][j];
      TH2Poly *DrawW2Hist = W2MCVector[i][j];
      // Skip empty samples
      if (DrawHist == NULL) continue;

      // Data vs Draw
      llh_data_draw[StdIt] = 0.0;//llh_penalty;
      // Data vs Fluctuated Draw
      llh_data_drawfluc[StdIt] = 0.0;//llh_penalty;
      // Data vs Fluctuated Predictive
      llh_data_predfluc[StdIt] = 0.0;

      // Draw vs Predictive
      llh_draw_pred[StdIt] = 0.0;//llh_penalty;

      // Fluctuated Draw vs Predictive
      llh_drawfluc_pred[StdIt] = 0.0;//llh_penalty;
      // Fluctuated Draw vs Fluctuated Predictive
      llh_drawfluc_predfluc[StdIt] = 0.0;// llh_penalty;
      // Fluctuated Draw vs Draw
      llh_drawfluc_draw[StdIt] = 0.0;//llh_penalty;
      // Fluctuated Predictive vs Predictive
      llh_predfluc_pred[StdIt] = 0.0;
      // Fluctuated Predicitve vs Draw
      llh_predfluc_draw[StdIt] = 0.0;//llh_penalty;

      TH2Poly *FluctHist = (TH2Poly*)(MeanHist[j]->Clone());
      TH2Poly *FluctDrawHist = (TH2Poly*)(MeanHist[j]->Clone());

      // Make the Poisson fluctuated hist
      FluctHist->Reset("");
      // Also Poisson fluctuate the drawn MCMC hist
      FluctDrawHist->Reset("");

      for (int i = 1; i <= FluctHist->GetNumberOfBins(); ++i) {
          // Get the prior predictive bin content
          double MeanContent = MeanHist[j]->GetBinContent(i);
          // Get a Poisson fluctuation of the content
          double Random = rnd->PoissonD(MeanContent);
          // Set the fluctuated histogram content to the Poisson variation of the prior predictive histogram
          FluctHist->SetBinContent(i,Random);

          // Do the same but fluctuate the drawn MCMC step
          double DrawContent = DrawHist->GetBinContent(i);
          double RandomDraw = rnd->PoissonD(DrawContent);
          FluctDrawHist->SetBinContent(i, RandomDraw);
        }
      

      // Likelihood between the drawn histogram and the data
      double DataDrawLLH = GetLLH(DataHist[j], DrawHist, DrawW2Hist);
      llh_data_draw[StdIt] += DataDrawLLH;
      total_llh_data_draw += DataDrawLLH;

      // Likelihood between the fluctuated drawn histogram and the data
      double DataDrawFlucLLH = GetLLH(DataHist[j], FluctDrawHist, DrawW2Hist);
      llh_data_drawfluc[StdIt] += DataDrawFlucLLH;
      total_llh_data_drawfluc += DataDrawFlucLLH;

      // Likelihood between the drawn histogram and the data
      double DataPredFlucLLH = GetLLH(DataHist[j], FluctHist, W2MeanHist[j]);
      llh_data_predfluc[StdIt] += DataPredFlucLLH;
      total_llh_data_predfluc += DataPredFlucLLH;

      // Likelihood between the drawn hist and the Prior Predictive
      double DrawPredLLH = GetLLH(DrawHist, MeanHist[j], W2MeanHist[j]);
      llh_draw_pred[StdIt] += DrawPredLLH;
      total_llh_draw_pred += DrawPredLLH;

      // Likelihood between fluctuated drawn and predictive
      double DrawFlucPredLLH = GetLLH(FluctDrawHist, MeanHist[j], W2MeanHist[j]);
      llh_drawfluc_pred[StdIt]  += DrawFlucPredLLH;
      total_llh_drawfluc_pred  += DrawFlucPredLLH;

      // Likelihood between drawn histogram and fluctuated drawn histogram
      double DrawFlucPredFlucLLH = GetLLH(FluctDrawHist, FluctHist, W2MeanHist[j]);
      llh_drawfluc_predfluc[StdIt] += DrawFlucPredFlucLLH;
      total_llh_drawfluc_predfluc += DrawFlucPredFlucLLH;

      // Likelihood between drawn histogram and fluctuated drawn histogram
      double DrawFlucDrawLLH = GetLLH(FluctDrawHist, DrawHist, DrawW2Hist);
      llh_drawfluc_draw[StdIt] += DrawFlucDrawLLH;
      total_llh_drawfluc_draw += DrawFlucDrawLLH;

      // Likelihood between the fluctuated drawn histogram and the prior predictive
      double PredFlucPredLLH = GetLLH(FluctHist, MeanHist[j], W2MeanHist[j]);
      llh_predfluc_pred[StdIt] += PredFlucPredLLH;
      total_llh_predfluc_pred += PredFlucPredLLH;

      // Likelihood between drawn histogram and fluctuated prior predictive distribution
      double PredFlucDrawLLH = GetLLH(FluctHist, DrawHist, DrawW2Hist);
      llh_predfluc_draw[StdIt] += PredFlucDrawLLH;
      total_llh_predfluc_draw += PredFlucDrawLLH;

      event_rate += NoOverflowIntegral(DrawHist);

      // Fill the random draw and prior predictive likelihood
      if (first_pass) {
        lnLHist_Sample[j]->SetBins(lnLHist_Sample[j]->GetXaxis()->GetNbins(), DataDrawLLH*0.2, DataDrawLLH*2.5);
      }
      lnLHist_Sample[j]->Fill(DataDrawLLH);

      // Delete the fluctuated histograms
      delete FluctHist;
      delete FluctDrawHist;
      delete DrawHist;
      delete DrawW2Hist;
    } // End loop over samples (still looping throws)


    // Add LLH penalties from the systematics to the LLH that use the drawn histogram
    total_llh_data_draw     += llh_penalty;
    total_llh_data_drawfluc += llh_penalty;
    total_llh_draw_pred     += llh_penalty;
    total_llh_drawfluc_pred += llh_penalty;
    total_llh_drawfluc_predfluc += llh_penalty;
    total_llh_drawfluc_draw += llh_penalty;
    total_llh_predfluc_draw += llh_penalty;


    if (first_pass) {
      first_pass = false;
      // Set the 1D hists
      lnLHist->SetBins(lnLHist->GetXaxis()->GetNbins(), 0.8*total_llh_predfluc_pred, 1.2*total_llh_predfluc_pred);
      lnLHist_draw->SetBins(lnLHist_draw->GetXaxis()->GetNbins(), 0.8*total_llh_draw_pred, 1.4*total_llh_draw_pred);
      lnLHist_drawdata->SetBins(lnLHist_drawdata->GetXaxis()->GetNbins(), 0.9*total_llh_data_draw, 1.1*total_llh_data_draw);
      lnLHist_drawfluc->SetBins(lnLHist_drawfluc->GetXaxis()->GetNbins(), 0.8*total_llh_predfluc_draw, 1.2*total_llh_predfluc_draw);
      lnLHist_drawflucdraw->SetBins(lnLHist_drawflucdraw->GetXaxis()->GetNbins(), 0.8*total_llh_drawfluc_draw, 1.2*total_llh_drawfluc_draw);

      // Set the 1D hists
      lnLDrawHist->SetBins(lnLDrawHist->GetXaxis()->GetNbins(), total_llh_predfluc_draw*0.8, total_llh_predfluc_draw*1.2, lnLDrawHist->GetYaxis()->GetNbins(), total_llh_data_draw*0.9, total_llh_data_draw*1.1);
      lnLFlucHist->SetBins(lnLFlucHist->GetXaxis()->GetNbins(), total_llh_drawfluc_draw*0.8, total_llh_drawfluc_draw*1.2, lnLFlucHist->GetYaxis()->GetNbins(), total_llh_data_draw*0.9, total_llh_data_draw*1.1);
      EventHist->SetBins(EventHist->GetXaxis()->GetNbins(), event_rate*0.98, event_rate*1.02);
    }

    lnLHist->Fill(total_llh_predfluc_pred);
    lnLHist_draw->Fill(total_llh_draw_pred);
    lnLHist_drawdata->Fill(total_llh_data_draw);
    lnLHist_drawfluc->Fill(total_llh_predfluc_draw);
    lnLHist_drawflucdraw->Fill(total_llh_drawfluc_draw);

    lnLDrawHist->Fill(total_llh_predfluc_draw, total_llh_data_draw);
    lnLFlucHist->Fill(total_llh_drawfluc_draw, total_llh_data_draw);

    EventHist->Fill(event_rate);

    // Also save to arrays to make sure we have the utmost super accuracy
    LLH_DrawFluc_V.push_back(total_llh_predfluc_draw);
    LLH_DrawData_V.push_back(total_llh_data_draw);
    LLH_DrawFlucDraw_V.push_back(total_llh_drawfluc_draw);

    // Write to the output tree
    OutputTree->Fill();
  } // End loop over throws

  AveragePenalty = AveragePenalty/double(nThrows);
  std::cout << "Average LLH penalty over toys is " << AveragePenalty << std::endl;

  // Calculate exact p-value instead of binned
  unsigned int Steps = LLH_DrawFluc_V.size();
  unsigned int Accept = 0;
  for (size_t i = 0; i < Steps; ++i) {
    if (LLH_DrawData_V[i] > LLH_DrawFlucDraw_V[i]) {
      Accept++;
    }
  }
  double pvalue = double(Accept)/double(Steps);
  std::stringstream ss;
  ss << pvalue << std::endl;
  std::cout << "Calculated exact p-value is " << pvalue << std::endl;
  lnLFlucHist->SetTitle((std::string(lnLFlucHist->GetTitle())+"_"+ss.str()).c_str());

  // Make the TCanvas for the total event rate
  TCanvas *TempCanv = new TCanvas((std::string(EventHist->GetName())+"_canv").c_str(), (std::string(EventHist->GetName())+"_canv").c_str(), 1024, 1024);
  double DataRate = 0.0;
  for (int i = 0; i < SampleId::kNSamples; ++i) {
    if (DataHist[i] == NULL) continue;
    DataRate += NoOverflowIntegral(DataHist[i]);
  }
  TLine *Line = new TLine(DataRate, EventHist->GetMinimum(), DataRate, EventHist->GetMaximum());
  Line->SetLineColor(kRed);
  Line->SetLineWidth(2);
  TF1 *Fitter = new TF1("Fit", "gaus", EventHist->GetBinLowEdge(1), EventHist->GetBinLowEdge(EventHist->GetNbinsX()+1));
  EventHist->Fit(Fitter, "RQ");
  Fitter->SetLineColor(kRed-5);
  // Calculate a p-value
  double Above = 0.0;
  for (int z = 0; z < EventHist->GetNbinsX(); ++z) {
    double xvalue = EventHist->GetBinCenter(z+1);
    if (xvalue >= EventHist->Integral()) {
      Above += EventHist->GetBinContent(z+1);
    }
  }
  pvalue = Above/EventHist->Integral();
  TLegend *Legend = new TLegend(0.6, 0.6, 0.9, 0.9);
  Legend->SetFillColor(0);
  Legend->SetFillStyle(0);
  Legend->SetLineWidth(0);
  Legend->SetLineColor(0);
  Legend->AddEntry(Line, Form("Data rate, %.0f, p-value=%.2f", DataRate, pvalue), "l");
  Legend->AddEntry(EventHist, Form("Event rate, #mu=%.1f#pm%.1f", EventHist->GetMean(), EventHist->GetRMS()), "l");
  Legend->AddEntry(Fitter, Form("Gauss, #mu=%.1f#pm%.1f", Fitter->GetParameter(1), Fitter->GetParameter(2)), "l");
  TempCanv->SetGridx();
  TempCanv->SetGridy();
  TempCanv->SetRightMargin(0.03);
  TempCanv->SetBottomMargin(0.08);
  TempCanv->SetLeftMargin(0.10);
  TempCanv->SetTopMargin(0.06);
  TempCanv->cd();
  EventHist->Draw();
  Line->Draw("same");
  Fitter->Draw("same");
  Legend->Draw("same");
  TempCanv->Write();
  delete TempCanv;
  delete Line;
  delete Legend;
  delete Fitter;
}

// *******************
// Make the cut LLH histogram
void SampleSummary::MakeCutLLH() {
  // *******************
  MakeCutLLH1D(lnLHist);
  MakeCutLLH1D(lnLHist_draw);
  MakeCutLLH1D(lnLHist_drawfluc);
  MakeCutLLH1D(lnLHist_drawdata);
  MakeCutLLH1D(lnLHist_drawflucdraw);
  MakeCutLLH2D(lnLDrawHist);
  MakeCutLLH2D(lnLFlucHist);
}

// ****************
// Make the 1D cut distribution and give the 1D p-value
void SampleSummary::MakeCutLLH1D(TH1D *Histogram, TH1D* Reference, TH1D* RefW2) {
  // ****************
  double TotalIntegral = Histogram->Integral();
  double Above = 0.0;
  // Get the LLH reference from total llh or some reference histogram
  double llh_reference = 0.0;
  if (Reference != NULL && RefW2 != NULL) {
    llh_reference = GetLLH(Reference, Histogram, RefW2);
  } else {
    llh_reference = llh_total;
  }
  for (int i = 0; i < Histogram->GetXaxis()->GetNbins(); ++i) {
    double xvalue = Histogram->GetBinCenter(i+1);
    if (xvalue >= llh_reference) {
      Above += Histogram->GetBinContent(i+1);
    }
  }
  double pvalue = Above/TotalIntegral;
  std::stringstream ss;
  ss << int(Above) << "/" << int(TotalIntegral) << "=" << pvalue;
  Histogram->SetTitle((std::string(Histogram->GetTitle())+"_"+ss.str()).c_str());

  // Write a TCanvas and make a line and a filled histogram
  TLine *TempLine = new TLine(llh_reference , Histogram->GetMinimum(), llh_reference, Histogram->GetMaximum());
  TempLine->SetLineColor(kBlack);
  TempLine->SetLineWidth(2);

  // Make the fill histogram
  TH1D *TempHistogram = (TH1D*)(Histogram->Clone());
  TempHistogram->SetFillStyle(1001);
  TempHistogram->SetFillColor(kRed);
  for (int i = 0; i < TempHistogram->GetNbinsX(); ++i) {
    if (TempHistogram->GetBinCenter(i+1) < llh_reference) {
      TempHistogram->SetBinContent(i+1, 0.0);
    }
  }

  std::string Title = Histogram->GetName();
  Title += "_canv";
  TCanvas *TempCanvas = new TCanvas(Title.c_str(), Title.c_str(), 1024, 1024);
  TempCanvas->SetGridx();
  TempCanvas->SetGridy();
  TempCanvas->cd();
  Histogram->Draw();
  TempHistogram->Draw("same");
  TempLine->Draw("same");

  Outputfile->cd();
  TempCanvas->Write();

  delete TempLine;
  delete TempHistogram;
  delete TempCanvas;
}


// ****************
// Make the 2D cut distribution and give the 2D p-value
void SampleSummary::MakeCutLLH2D(TH2D *Histogram) {
  // ****************

  double TotalIntegral = Histogram->Integral();
  // Count how many fills are above y=x axis
  // This is the 2D p-value
  double Above = 0.0;
  for (int i = 0; i < Histogram->GetXaxis()->GetNbins(); ++i) {
    double xvalue = Histogram->GetXaxis()->GetBinCenter(i+1);
    for (int j = 0; j < Histogram->GetYaxis()->GetNbins(); ++j) {
      double yvalue = Histogram->GetYaxis()->GetBinCenter(j+1);
      // We're only interested in being _ABOVE_ the y=x axis
      if (xvalue >= yvalue) {
        Above += Histogram->GetBinContent(i+1, j+1);
      }
    }
  }
  double pvalue = Above/TotalIntegral;
  std::stringstream ss;
  ss << int(Above) << "/" << int(TotalIntegral) << "=" << pvalue;
  Histogram->SetTitle((std::string(Histogram->GetTitle())+"_"+ss.str()).c_str());

  // Now add the TLine going diagonally
  double minimum = Histogram->GetXaxis()->GetBinLowEdge(1);
  if (Histogram->GetYaxis()->GetBinLowEdge(1) > minimum) {
    minimum = Histogram->GetYaxis()->GetBinLowEdge(1);
  }
  double maximum = Histogram->GetXaxis()->GetBinLowEdge(Histogram->GetXaxis()->GetNbins());
  if (Histogram->GetYaxis()->GetBinLowEdge(Histogram->GetYaxis()->GetNbins()) < maximum) {
    maximum = Histogram->GetYaxis()->GetBinLowEdge(Histogram->GetYaxis()->GetNbins());
  }
  TLine *TempLine = new TLine(minimum, minimum, maximum, maximum);
  TempLine->SetLineColor(kRed);
  TempLine->SetLineWidth(2);

  std::string Title = Histogram->GetName();
  Title += "_canv";
  TCanvas *TempCanvas = new TCanvas(Title.c_str(), Title.c_str(), 1024, 1024);
  TempCanvas->SetGridx();
  TempCanvas->SetGridy();
  TempCanvas->cd();
  gStyle->SetPalette(81);
  Histogram->SetMinimum(-0.01);
  Histogram->Draw("colz");
  TempLine->Draw("same");

  TempCanvas->Write();
  delete TempLine;
  delete TempCanvas;
}

// ****************
// Make a ratio histogram
template<class HistType>
HistType* SampleSummary::RatioHists(HistType *NumHist, HistType *DenomHist) {
  // ****************

  HistType *NumCopy = (HistType*)(NumHist->Clone());
  std::string title = std::string(DenomHist->GetName()) + "_ratio";
  NumCopy->SetNameTitle(title.c_str(), title.c_str());
  NumCopy->Divide(DenomHist);
  NumCopy->SetMinimum(0.4);
  NumCopy->SetMaximum(1.6);

  return NumCopy;
}

// ****************
// Make a ratio th2poly
TH2Poly* SampleSummary::RatioPolys(TH2Poly *NumHist, TH2Poly *DenomHist) {
  // ****************

  TH2Poly *NumCopy = (TH2Poly*)(NumHist->Clone());
  std::string title = std::string(DenomHist->GetName()) + "_ratio";
  NumCopy->SetNameTitle(title.c_str(), title.c_str());

  for(int i=1; i<=NumCopy->GetNumberOfBins(); i++){
    NumCopy->SetBinContent(i,NumHist->GetBinContent(i)/DenomHist->GetBinContent(i));
  }

  NumCopy->SetMinimum(0.6);
  NumCopy->SetMaximum(1.4);

  return NumCopy;
}

// ****************
// Normalise a histogram
template<class HistType>
HistType* SampleSummary::NormaliseHist(HistType *Histogram) {
  // ****************

  HistType* HistCopy = (HistType*)(Histogram->Clone());
  HistCopy->Scale(1./HistCopy->Integral("width"), "width");
  std::string title = std::string(HistCopy->GetName())+"_norm";
  HistCopy->SetNameTitle(title.c_str(), title.c_str());

  return HistCopy;
}

// ****************
// Normalise a th2poly
TH2Poly* SampleSummary::NormalisePoly(TH2Poly *Histogram) {
  // ****************

  TH2Poly* HistCopy = (TH2Poly*)(Histogram->Clone());
  double IntegralWidth = PolyIntegralWidth(HistCopy);
  HistCopy = PolyScaleWidth(HistCopy, IntegralWidth);
  std::string title = std::string(HistCopy->GetName())+"_norm";
  HistCopy->SetNameTitle(title.c_str(), title.c_str());

  return HistCopy;
}

// ****************
// Scale a TH2Poly and divide by bin width
TH2Poly* SampleSummary::PolyScaleWidth(TH2Poly *Histogram, double scale) {
  // ****************

  TH2Poly* HistCopy = (TH2Poly*)(Histogram->Clone());
  double integral=0;
  double xlow, xup, ylow, yup, area;

  for(int i=1; i<HistCopy->GetNumberOfBins()+1; i++)
    {
      TH2PolyBin* bin = (TH2PolyBin*)HistCopy->GetBins()->At(i-1)->Clone();
      xlow=bin->GetXMin();
      xup=bin->GetXMax();
      ylow=bin->GetYMin();
      yup=bin->GetYMax();
      area = (xup-xlow)*(yup-ylow);
      HistCopy->SetBinContent(i, Histogram->GetBinContent(i)/(area*scale));
    }

  return HistCopy;
}

// ****************
// Integral of TH2Poly multiplied by bin width
double SampleSummary::PolyIntegralWidth(TH2Poly *Histogram) {
  // ****************

  double integral=0;
  double xlow, xup, ylow, yup, area;

  for(int i=1; i<Histogram->GetNumberOfBins()+1; i++)
    {
      TH2PolyBin* bin = (TH2PolyBin*)Histogram->GetBins()->At(i-1)->Clone();
      xlow=bin->GetXMin();
      xup=bin->GetXMax();
      ylow=bin->GetYMin();
      yup=bin->GetYMax();
      area = (xup-xlow)*(yup-ylow);
      integral += Histogram->GetBinContent(i)*area;
    }

  return integral;
}

// ****************
// Calculate the LLH for TH1D, set the LLH to title of MCHist
void SampleSummary::CalcLLH(TH1D * const & DataHist, TH1D * const & MCHist, TH1D * const & W2Hist) {
  // ****************
  double llh = GetLLH(DataHist, MCHist, W2Hist);
  std::stringstream ss;
  ss << "__n2LLH=" << llh;
  MCHist->SetTitle((std::string(MCHist->GetTitle())+ss.str()).c_str());
  std::cout << std::setw(45) << std::left << MCHist->GetName() << std::setw(10) << DataHist->Integral() << std::setw(10) << MCHist->Integral() << std::setw(10) << llh << std::endl;
}

// ****************
// Calculate the LLH for TH1D, set the LLH to title of MCHist
void SampleSummary::CalcLLH(TH2Poly * const & DataHist, TH2Poly * const & MCHist, TH2Poly * const & W2Hist) {
  // ****************
  double llh = GetLLH(DataHist, MCHist, W2Hist);
  std::stringstream ss;
  ss << "__n2LLH_" << llh;
  MCHist->SetTitle((std::string(MCHist->GetTitle())+ss.str()).c_str());
  std::cout << std::setw(45) << std::left << MCHist->GetName() << std::setw(10) << NoOverflowIntegral(DataHist) << std::setw(10) << NoOverflowIntegral(MCHist) << std::setw(10) << llh << std::endl;
}

// ****************
double SampleSummary::GetLLH(TH2Poly * const & DataHist, TH2Poly * const & MCHist, TH2Poly * const & W2Hist) {
  // ****************
  double llh = 0.0;
  for (int i = 1; i <= DataHist->GetNumberOfBins(); ++i) {
    double data = DataHist->GetBinContent(i);
    double mc = MCHist->GetBinContent(i);
    double w2 = W2Hist->GetBinContent(i);
      // Need some MC
    if (mc == 0) continue;

    // The MC used in the likeliihood calculation
    // Is allowed to be changed by Barlow Beeston beta parameters
    double newmc = mc;

    // Not full Barlow-Beeston or what is referred to as "light": we're not introducing any more parameters
    // Assume the MC has a Gaussian distribution around generated
    // As in https://arxiv.org/abs/1103.0354 eq 10, 11
    // The penalty from MC statistics using Barlow-Beeston
    double penalty = 0;
    if (likelihood == kBarlowBeeston) {
      // Barlow-Beeston uses fractional uncertainty on MC, so sqrt(sum[w^2])/mc
      double fractional = sqrt(w2)/mc;
      // -b/2a in quadratic equation
      double temp = mc*fractional*fractional-1;
      // b^2 - 4ac in quadratic equation
      double temp2 = temp*temp + 4*data*fractional*fractional;
      if (temp2 < 0) {
	std::cerr << "Negative square root in Barlow Beeston coefficient calculation!" << std::endl;
	std::cerr << __FILE__ << ":" << __LINE__ << std::endl;
	throw;
      }
      // Solve for the positive beta
      double beta = (-1*temp+sqrt(temp2))/2.;
      newmc = mc*beta;
      // And penalise the movement in beta relative the mc uncertainty
      if (fractional > 0) penalty = (beta-1)*(beta-1)/(2*fractional*fractional);
      else penalty = 0;
    }

    // Calculate the new Poisson likelihood
    // For Barlow-Beeston newmc is modified, so can only calculate Poisson likelihood after Barlow-Beeston
    // For the Poisson likelihood, this is just the usual calculation
    // For IceCube likelihood, we calculate it later
    double stat = 0;
    // All likelihood calculations may use the bare Poisson likelihood, so calculate here
    if (data == 0) stat = newmc;
    else if (newmc > 0) stat = newmc-data+data*TMath::Log(data/newmc);

    // Also try the IceCube likelihood
    // It does not modify the MC content
    // https://arxiv.org/abs/1901.04645
    // Argüelles, C.A., Schneider, A. & Yuan, T. J. High Energ. Phys. (2019) 2019: 30. https://doi.org/10.1007/JHEP06(2019)030
    // We essentially construct eq 3.16 and take the logarithm
    // in eq 3.16, mu is MC, sigma2 is w2, k is data
    if (likelihood == kIceCube) {
      // If there for some reason is 0 mc uncertainty, return the Poisson LLH
      if (w2 == 0) {
	llh+=stat;
	continue;
      }

      // Reset the penalties if there is mc uncertainty
      stat = 0.0;
      penalty = 0.0;
      // Auxillary variables
      long double b = mc/w2;
      long double a = mc*b+1;
      long double k = data;
      // Use C99's implementation of log of gamma function to not be C++11 dependent
      stat = -1*(a * logl(b) + lgammal(k+a) - lgammal(k+(long double)1) - ((k+a)*log1pl(b)) - lgammal(a));
    }

    // Return the statistical contribution and penalty
    llh += stat+penalty;
    /*
    if (nMC == 0) continue;//nMC = 1E-8;
    if (nData > 0 && nMC > 0) {
      llh += 2*(nMC - nData + nData * log(nData/nMC));
    } else if (nData == 0 && nMC > 0) {
      llh += 2*nMC;
      }*/
  }
  return 2*llh;
}

// ****************
double SampleSummary::GetLLH(TH1D * const & DataHist, TH1D * const & MCHist, TH1D * const & W2Hist) {
  // ****************
  double llh = 0.0;
  for (int i = 1; i <= DataHist->GetXaxis()->GetNbins(); ++i) {
    double data = DataHist->GetBinContent(i);
    double mc = MCHist->GetBinContent(i);
    double w2 = W2Hist->GetBinContent(i);
    
    // Need some MC
    if (mc == 0) continue;

    // The MC used in the likeliihood calculation
    // Is allowed to be changed by Barlow Beeston beta parameters
    double newmc = mc;

    // Not full Barlow-Beeston or what is referred to as "light": we're not introducing any more parameters
    // Assume the MC has a Gaussian distribution around generated
    // As in https://arxiv.org/abs/1103.0354 eq 10, 11

    // The penalty from MC statistics using Barlow-Beeston
    double penalty = 0;
    if (likelihood == kBarlowBeeston) {
      // Barlow-Beeston uses fractional uncertainty on MC, so sqrt(sum[w^2])/mc
      double fractional = sqrt(w2)/mc;
      // -b/2a in quadratic equation
      double temp = mc*fractional*fractional-1;
      // b^2 - 4ac in quadratic equation
      double temp2 = temp*temp + 4*data*fractional*fractional;
      if (temp2 < 0) {
	std::cerr << "Negative square root in Barlow Beeston coefficient calculation!" << std::endl;
	std::cerr << __FILE__ << ":" << __LINE__ << std::endl;
        throw;
      }
      // Solve for the positive beta
      double beta = (-1*temp+sqrt(temp2))/2.;
      newmc = mc*beta;
      // And penalise the movement in beta relative the mc uncertainty
      if (fractional > 0) penalty = (beta-1)*(beta-1)/(2*fractional*fractional);
      else penalty = 0;
    }

    // Calculate the new Poisson likelihood
    // For Barlow-Beeston newmc is modified, so can only calculate Poisson likelihood after Barlow-Beeston
    // For the Poisson likelihood, this is just the usual calculation
    // For IceCube likelihood, we calculate it later
    double stat = 0;
    // All likelihood calculations may use the bare Poisson likelihood, so calculate here
    if (data == 0) stat = newmc;
    else if (newmc > 0) stat = newmc-data+data*TMath::Log(data/newmc);

    // Also try the IceCube likelihood
    // It does not modify the MC content
    // https://arxiv.org/abs/1901.04645
    // Argüelles, C.A., Schneider, A. & Yuan, T. J. High Energ. Phys. (2019) 2019: 30. https://doi.org/10.1007/JHEP06(2019)030
    // We essentially construct eq 3.16 and take the logarithm
    // in eq 3.16, mu is MC, sigma2 is w2, k is data
    if (likelihood == kIceCube) {
      // If there for some reason is 0 mc uncertainty, return the Poisson LLH
      if (w2 == 0) {
	llh+=stat;
	continue;
      }

      // Reset the penalties if there is mc uncertainty
      stat = 0.0;
      penalty = 0.0;
      // Auxillary variables
      long double b = mc/w2;
      long double a = mc*b+1;
      long double k = data;
      // Use C99's implementation of log of gamma function to not be C++11 dependent
      stat = -1*(a * logl(b) + lgammal(k+a) - lgammal(k+(long double)1) - ((k+a)*log1pl(b)) - lgammal(a));
    }

    // Return the statistical contribution and penalty
    llh += stat+penalty;

    /*if (nMC == 0) nMC = 1E-8;
    if (nData > 0 && nMC > 0) {
      llh += 2*(nMC - nData + nData * log(nData/nMC));
    } else if (nData == 0 && nMC > 0) {
      llh += 2*nMC;
      }*/
  }
  return 2*llh;
}

// ****************
// Make a projection
TH1D* SampleSummary::ProjectHist(TH2D* Histogram, bool ProjectX) {
  // ****************

  TH1D* Projection = NULL;
  std::string name;
  if (ProjectX) {
    name = std::string(Histogram->GetName()) + "_x";
    Projection = Histogram->ProjectionX(name.c_str(), 1, Histogram->GetYaxis()->GetNbins(), "e");
  } else {
    name = std::string(Histogram->GetName()) + "_y";
    Projection = Histogram->ProjectionY(name.c_str(), 1, Histogram->GetXaxis()->GetNbins(), "e");
  }

  return Projection;
}

// ****************
// Make a projection
TH1D* SampleSummary::ProjectPoly(TH2Poly* Histogram, bool ProjectX, int selection) {
  // ****************

  std::vector<double> xbins;
  std::vector<double> ybins;

  SetBinning(selection, xbins, ybins);
  TH1D* Projection = NULL;
  std::string name;
  if (ProjectX) {
    name = std::string(Histogram->GetName()) + "_x";
    Projection = PolyProjectionX(Histogram,name.c_str(),xbins);
  } else {
    name = std::string(Histogram->GetName()) + "_y";
    Projection = PolyProjectionY(Histogram,name.c_str(),ybins);
  }

  return Projection;
}

//Basically copy SetupBinning from samplePDF. Used for the 1d axis in projections (have to define your axis if you want to project a poly). We have functions to do it (assuming uniform distribution of events in a bin when they overlap), but need to hard code the axis
void SampleSummary::SetBinning(SampleId::SampleEnum Selection, std::vector<double> & BinningX,std::vector<double> & BinningY) {

  switch (Selection) {

  case (SampleId::kFGD1NuMuCC0Pi):
  case (SampleId::kFGD2NuMuCC0Pi):
  case (SampleId::kFGD1NuMuCC0PiNp): //WARNING
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


// *******************
// Finally, the main
int main (int argc, char **argv) {
  // *******************

  if (argc != 2) {
    std::cout << "ND280_PriorPredictive_2016 runs MCMC at ND280" << std::endl;
    std::cout << "Syntax is $: ND280_PriorPredictive_2016 config.cfg" << std::endl;
    std::cout << "Where config.cfg is a valid config file, compatible with the manager class (manager/manager.cpp/h); an example is provided in example_config.cfg" << std::endl;
    exit(-1);
  }

  manager *fitMan = new manager(argv[1]);

  // there's a check inside the manager class that does this; left here for demonstrative purposes
  if (fitMan->getGoodConfig() == false) {
    std::cerr << "Didn't find a good config in input configuration" << std::endl;
    throw;
  }

  // Number of toys
  int Ntoys = fitMan->getNtoy();

  // Use the full likelihood for the prior predictive pvalue
  bool FullLLH = fitMan->getFullLLH();

  // Check if we've already made all the data and MC
  std::string OutputName = fitMan->getOutputFilename();
  std::string PriorName = fitMan->getPosteriorFiles();
  if (PriorName == "EMPTY") {
    PriorName = OutputName;
    PriorName.replace(PriorName.find(".root"), 5, std::string("_PriorPredStoreW2.root"));
  }
  TFile* Outfile = new TFile(PriorName.c_str(), "READ");

  std::vector<TH2Poly*> NominalVector;
  std::vector<TH2Poly*> DataVector;
  std::vector<TH2Poly*> W2NomVector;
  std::vector< std::vector<TH2Poly*> > MasterSampleVector;
  std::vector< std::vector<TH2Poly*> > MasterW2Vector;
  // Know that these guys are going to be exist for every psyche sample, sometimes just NULL though
  NominalVector.resize(SampleId::kNSamples);
  DataVector.resize(SampleId::kNSamples);
  W2NomVector.resize(SampleId::kNSamples);
  int nEntries = -1;
  std::vector<double> PenaltyVector;

  // If the output file doesn't exist
  if (Outfile->IsZombie()) {
    delete Outfile;
    Outfile = NULL;

    MCMCProcessor Processor(OutputName, false);

    // Get inputted systematic parameters covariance matrices
    TString xsecCovMatrixFile = Processor.GetXSecCov();
    TString fluxCovMatrixFile = Processor.GetFluxCov();
    TString ndDetCovMatrixFile = Processor.GetND280Cov();

    // Check the ND runs in the run MCMC vs the given psyche
    std::string MCMCNDruns = Processor.GetNDruns();
    std::string ManNDruns = std::string(fitMan->getNDRuns());
    if (MCMCNDruns != ManNDruns) {
      std::cout << "*** WARNING: " << std::endl;
      std::cout << "    Running Prior predictive with different ND280 runs than the MCMC in " << OutputName << " was sampled with" << std::endl;
      std::cout << "    MCMC runs: " << MCMCNDruns << std::endl;
      std::cout << "    ManNDruns: " << ManNDruns << std::endl;
      std::cout << "    This is _ENTIRELY FINE_ if you wanted to do this!" << std::endl;
      sleep(3);
    }
    // Check the ND selections
    std::vector<std::string> MCMCSel = Processor.GetNDsel();
    std::vector<std::string> ManSel = fitMan->getNDsel();
    size_t sizet = MCMCSel.size();
    std::cout << sizet << std::endl;
    if (sizet != ManSel.size()) {
      std::cout << "*** WARNING: " << std::endl;
      std::cout << "    Running Prior predictive with different ND280 selections in the MCMC in " << OutputName << " was sampled with" << std::endl;
      std::cout << "    MCMC sels size: " << MCMCSel.size() << std::endl;
      std::cout << "    Man sels size:  " << ManSel.size() << std::endl;
      std::cout << "    This is _ENTIRELY FINE_ if you wanted to do this!" << std::endl;
      sleep(3);
    }
    for (int i = 0; i < sizet; ++i) {
      std::cout << MCMCSel[i] << " " << ManSel[i] << std::endl;
      if (MCMCSel[i] != ManSel[i]) {
        std::cout << "*** WARNING: " << std::endl;
        std::cout << "    Running Prior predictive with different ND280 selections in the MCMC in " << OutputName << " was sampled with" << std::endl;
        std::cout << "    MCMC sels: " << MCMCSel[i] << std::endl;
        std::cout << "    Man sels:  " << ManSel[i] << std::endl;
        std::cout << "    This is _ENTIRELY FINE_ if you wanted to do this!" << std::endl;
        sleep(3);
      }
    }


#ifdef CUDA
    samplePDFND2019GPU* sample = new samplePDFND2019GPU(fitMan);
#else
    samplePDFND2019* sample = new samplePDFND2019(fitMan);
#endif

    // Setup the covariance matrices
    covarianceXsec2015 *xsec = new covarianceXsec2015("xsec_cov", xsecCovMatrixFile);
    covarianceFlux* flux = new covarianceFlux("total_flux_cov", fluxCovMatrixFile);
    covarianceNDDet_2019Poly* det = new covarianceNDDet_2019Poly("nddet_cov", ndDetCovMatrixFile);

    // Get the flat parameters
    std::vector<int> NDDetFlatParams = fitMan->getNdDetFlat();
    std::vector<int> FluxFlatParams  = fitMan->getFluxFlat();
    std::vector<int> XsecFlatParams  = fitMan->getXsecFlat();
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

    xsec->setParameters();
    flux->setParameters();
    det->setParameters();

    sample->setXsecCov(xsec);
    sample->setFluxCov(flux);
    sample->setSimpleDetCov(det);

    sample->fillDataFromSamples();
    sample->fillReweigtingBins();
#ifdef CUDA
    sample->fillGPUSplines();
#endif

    // Do a reweight and save the nominal distributions
    double *fake = NULL;
    sample->reweight(fake);

    // If we're running fake-data fits, we should load up this as data
    bool fakeDataFit = fitMan->getFakeDataFitFlag();
    if (fakeDataFit) {
      // Maybe make a method that takes some parameters?
      sample->setAsimovFakeData(fitMan->getCustomReWeight());
    }

    for (int j = 0; j < SampleId::kNSamples; ++j) {
      if (sample->getPDF(j) == NULL) {
        NominalVector[j] = NULL;
        DataVector[j] = NULL;
	W2NomVector[j] = NULL;
        continue;
      }
      std::string name = std::string(sample->getPDF(j)->GetName());
      if(j==4) //WARNING
      {
        name="FGD1_numuCC_0pi_Np";
      }
      std::cout<<" DEBUG KURWA NAME "<<name.c_str()<<" num "<<j<<std::endl;
      
      TH2Poly *TempDist = (TH2Poly*)(sample->getPDF(j)->Clone());
      TH2Poly *TempDataDist = (TH2Poly*)(sample->getData(j)->Clone());
      TH2Poly *TempW2Dist = sample->getW2(j)->Clone();
      TempW2Dist->SetNameTitle((name+"_W2nom").c_str(), (name+"_W2nom").c_str());
      TempDist->SetNameTitle((name+"_nom").c_str(), (name+"_nom").c_str());
      TempDataDist->SetNameTitle((name+"_data").c_str(), (name+"_data").c_str());
      NominalVector[j] = TempDist;
      DataVector[j] = TempDataDist;
      W2NomVector[j] = TempW2Dist;
    }
    // Now have the nominal vectors in NominalVector

    PenaltyVector.reserve(Ntoys);
    TRandom3 *rnd = new TRandom3();

    std::cout << "Generating " << Ntoys << std::endl;
    for (int i = 0; i < Ntoys; i++) {

      // Set the flux xsec and ND280 parameters to what the MCMC stepped
      flux->throwParameters();
      xsec->throwParameters();
      det->throwParameters();

      // Reweight the sample with the new systematic variations
      sample->reweight(fake);

      // Calculate the likelihood
      double Sample_LLH = sample->getLikelihood();
      double Flux_LLH = flux->getLikelihood();
      double Xsec_LLH = xsec->getLikelihood();
      double ND280_LLH = det->getLikelihood();

      // Output some info for the user
      if (i % (Ntoys/10) == 0) {
        std::cout << "On toy " << i << "/" << Ntoys << " (" << int(double(i)/double(Ntoys)*100.0) << "%)" << std::endl;
	}

      // Calculate the total combined likelihood which we can compared to the saved likelihood in the ROOT file
      double PenaltyLLH = Flux_LLH + Xsec_LLH + ND280_LLH;

      PenaltyVector[i] = 2.0*PenaltyLLH;

      std::stringstream ss;
      ss << "_" << i;

      std::vector<TH2Poly*> SampleVector;
      std::vector<TH2Poly*> W2Vector;
      SampleVector.resize(SampleId::kNSamples);
      W2Vector.resize(SampleId::kNSamples);

      // Loop over the psyche samples and write them to file
      for (int j = 0; j < SampleId::kNSamples; ++j) {
        // Skip unloaded samples
        if (sample->getPDF(j) == NULL) {
          SampleVector[j] = NULL;
          continue;
        }
        std::string name = sample->getPDF(j)->GetName() + ss.str();
        if(j==4) //WARNING
        {
            name="FGD1_numuCC_0pi_Np";
        }
        std::cout << "DEBUG LOOP at sample  "<< name.c_str() <<"     "<<j <<std::endl;
        
        TH2Poly *TempDist = (TH2Poly*)(sample->getPDF(j)->Clone());
        TempDist->SetNameTitle(name.c_str(), name.c_str());
        SampleVector[j] = TempDist;
	std::string namew2 = name + "w2";
	TH2Poly *W2PolyTemp = (TH2Poly*)(sample->getW2(j)->Clone());
	W2PolyTemp->SetNameTitle(namew2.c_str(), namew2.c_str());
	W2Vector[j] = W2PolyTemp;
      }
      MasterSampleVector.push_back(SampleVector);
      MasterW2Vector.push_back(W2Vector);
      
      std::cout << " DEBUG LOOP at sample  "<< j << std::endl;
    }

    // The output file
    TFile* Outfile = new TFile(PriorName.c_str(), "RECREATE");
    // Write the penalty for the jth toy to file
    double Penalty;
    TTree *tree = new TTree("ToySummary", "ToySummary");
    tree->Branch("Penalty", &Penalty, "Penalty/D");
    for (int j = 0; j < Ntoys; ++j) {
      Penalty = PenaltyVector[j];
      tree->Fill();
    }

    // Write all the templates to file
    for (int i = 0; i < SampleId::kNSamples; ++i) {
      if (DataVector[i] == NULL || NoOverflowIntegral(DataVector[i]) == 0) continue;
      DataVector[i]->Write();
      NominalVector[i]->Write();
      W2NomVector[i]->Write();
      for (int j = 0; j < Ntoys; ++j) {
        MasterSampleVector[j][i]->Write();
	MasterW2Vector[j][i]->Write();
      }
    }

    Outfile->cd();
    tree->Write();
    std::cout << "Wrote " << Ntoys << " output toys to " << Outfile->GetName() << std::endl;
    Outfile->Close();
    Outfile = NULL;
  }

  std::cout << "Done making templates and reweighting... Now making the SampleSummary instance" << std::endl;

  // Set the output name depending on if we've done the full LLH or not
  if (FullLLH) {
    PriorName.replace(PriorName.find(".root"), 5, std::string("_FullLLH.root"));
  } else {
    PriorName.replace(PriorName.find(".root"), 5, std::string("_SampLLH.root"));
  }
  SampleSummary Samples(SampleId::kNSamples, PriorName);
  likelihood = fitMan->getNDLikelihood();

  // Add in the Data and nominal to the SampleSummary class
  Samples.AddData(DataVector);
  Samples.AddNominal(NominalVector,W2NomVector);
  // Now we have the MasterSampleVector filled with our toys
  // Add the throws

  for (int i = 0; i < Ntoys; ++i) {
    Samples.AddThrow(MasterSampleVector[i], MasterW2Vector[i], PenaltyVector[i]);
  }
  std::cout << "Finished adding throws to SampleSummary, now writing..." << std::endl;

  // Calculate the prior predictive p-values and write the samples to file
  Samples.Write();

  return 0;
}

