#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

// ROOT includes
#include "TObjArray.h"
#include "TChain.h"
#include "TFile.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include "TH1.h"
#include "TF1.h"
#include "TH2.h"
#include "TGraphErrors.h"
#include "TVectorD.h"
#include "TColor.h"

void SetT2Kstyl();

const int NFiles = 3;
std::string TitleName = "#nu_{#mu} ^{12}C";
double Knots[6] = {0, 0.2, 0.3, 0.5, 0.7, 1};
const Style_t CredibleRegionStyle[6] = {kSolid, kDotted, kDashed, kDotted, kDashed, kSolid};
Color_t RelevantModesColors[6] = {kRed, kGreen+1, kBlue+1, kOrange+1, kCyan+2, kTeal};
std::string Titles[NFiles];

inline void MakePlot(TH1F** hist, TCanvas* c1)
{
    double Maximum = 0;
    for(int i = 0; i < NFiles; i++)
    {
       //hist[i]->Scale(1/hist[i]->Integral());

        if(hist[i]->GetMaximum() > Maximum) Maximum = hist[i]->GetMaximum();
        hist[i]->SetLineColorAlpha(RelevantModesColors[i], 1);
        hist[i]->SetLineStyle(CredibleRegionStyle[i]);
    }
    Maximum = Maximum+Maximum*0.1;
    hist[0]->SetMaximum(Maximum);
    hist[0]->Draw("");
    hist[0]->SetTitle(TitleName.c_str());
    for(int i = 1; i < NFiles; i++)
    {
       hist[i]->Draw("same");
    }

    TLegend* legend = new TLegend(0.4,0.7,0.9,0.9);
    for(int i = NFiles-1; i >= 0; i--)
    {
       legend->AddEntry(hist[i], Titles[i].c_str(),"l");
    }
    legend->SetTextSize(0.035);
    legend->SetLineColor(0);
    legend->SetLineStyle(0);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->Draw("same");
    c1->Print("Reweight.pdf");

    delete legend;
}


void SplineReweight() {

    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    c1->SetTopMargin(0.12);
    c1->SetBottomMargin(0.12);
    c1->SetRightMargin(0.075);
    c1->SetLeftMargin(0.12);
    gPad->SetGrid();
    gStyle->SetPalette(51);


    TFile *file[NFiles] = {NULL};
    TTree *tree[NFiles] = {NULL};

    file[0] = new TFile("18MeV_2p2h_Event.root");
    Titles[0] = "Eb = 18MeV";

    file[1] = new TFile("Default_2p2h_Event.root");
    Titles[1] = "Default Eb~25MeV";

    file[2] = new TFile("36MeV_2p2h_Event.root");
    Titles[2] = "Eb = 36MeV";

    //file[3] = new TFile("Default_Federico_2p2h_Event.root");
    //Titles[3] = "Eb~25MeV NV2P2HQVAL=2";

    int nentries[NFiles];
    int NFSprot[NFiles], NFSneut[NFiles];
    double HMprotonMom[NFiles], HMneutronMom[NFiles], HMprotonTheta[NFiles], HMneutronTheta[NFiles], Q2[NFiles];
    double q0[NFiles], q3[NFiles], PFSLep[NFiles];

    double CosFSLep[NFiles], Enu[NFiles], EnuQErec[NFiles], kERecQEBias[NFiles];

    for(int i = 0; i < NFiles; i++)
    {
     tree[i] = (TTree*)file[i]->Get("sample_sum");
     nentries[i] = tree[i]->GetEntries();

      tree[i]->SetBranchStatus("*", false);

      tree[i]->SetBranchStatus( "NFSprot", true);
      tree[i]->SetBranchAddress("NFSprot", &(NFSprot[i]));

      tree[i]->SetBranchStatus( "NFSneut", true);
      tree[i]->SetBranchAddress("NFSneut", &(NFSneut[i]));

      tree[i]->SetBranchStatus( "HMprotonMom", true);
      tree[i]->SetBranchAddress("HMprotonMom", &(HMprotonMom[i]));

      tree[i]->SetBranchStatus( "HMneutronMom", true);
      tree[i]->SetBranchAddress("HMneutronMom", &(HMneutronMom[i]));

      tree[i]->SetBranchStatus( "HMprotonTheta", true);
      tree[i]->SetBranchAddress("HMprotonTheta", &(HMprotonTheta[i]));

      tree[i]->SetBranchStatus( "HMneutronTheta", true);
      tree[i]->SetBranchAddress("HMneutronTheta", &(HMneutronTheta[i]));

      tree[i]->SetBranchStatus( "Q2", true);
      tree[i]->SetBranchAddress("Q2", &(Q2[i]));

      tree[i]->SetBranchStatus( "q0", true);
      tree[i]->SetBranchAddress("q0", &(q0[i]));

      tree[i]->SetBranchStatus( "q3", true);
      tree[i]->SetBranchAddress("q3", &(q3[i]));

      tree[i]->SetBranchStatus( "PFSLep", true);
      tree[i]->SetBranchAddress("PFSLep", &(PFSLep[i]));

      tree[i]->SetBranchStatus( "CosFSLep", true);
      tree[i]->SetBranchAddress("CosFSLep", &(CosFSLep[i]));

      tree[i]->SetBranchStatus( "Enu", true);
      tree[i]->SetBranchAddress("Enu", &(Enu[i]));

      tree[i]->SetBranchStatus( "EnuQErec", true);
      tree[i]->SetBranchAddress("EnuQErec", &(EnuQErec[i]));

      tree[i]->SetBranchStatus( "kERecQEBias", true);
      tree[i]->SetBranchAddress("kERecQEBias", &(kERecQEBias[i]));

    }

    std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<nentries[0]<<std::endl;

    TH1F ** Nprotshist = new TH1F*[NFiles];
    TH1F ** Nneutshist = new TH1F*[NFiles];

    TH1F ** ProtMomhist = new TH1F*[NFiles];
    TH1F ** NeutMomhist = new TH1F*[NFiles];

    TH1F ** ProtThetaist = new TH1F*[NFiles];
    TH1F ** NeutThetahist = new TH1F*[NFiles];

    TH1F ** Q2hist = new TH1F*[NFiles];
    TH1F ** q0hist = new TH1F*[NFiles];
    TH1F ** q3hist = new TH1F*[NFiles];

   TH1F ** lephist = new TH1F*[NFiles];
   TH1F ** lepCoshist = new TH1F*[NFiles];

   TH1F ** EnuHist = new TH1F*[NFiles];
   TH1F ** EnuQEHist = new TH1F*[NFiles];
   TH1F ** kERecQEBiasHist = new TH1F*[NFiles];

    for(int i = 0; i < NFiles; i++)
    {
       lephist[i] = new TH1F(Form("lephisthist_knot=%.1f",Knots[i]),Form("lephisthist_knot=%.1f",Knots[i]), 50, 0., 2000.);
       lephist[i]->GetXaxis()->SetTitle("p_{Lep} MeV");
       lephist[i]->GetYaxis()->SetTitle("Events");

       lepCoshist[i] = new TH1F(Form("lepCoshist_knot=%.1f",Knots[i]),Form("lepCoshist_knot=%.1f",Knots[i]), 50, -1., 1.);
       lepCoshist[i]->GetXaxis()->SetTitle("Cos#theta_{lep}");
       lepCoshist[i]->GetYaxis()->SetTitle("Events");

       EnuHist[i] = new TH1F(Form("EnuHist=%.1f",Knots[i]),Form("EnuHist=%.1f",Knots[i]), 50, 0., 2000);
       EnuHist[i]->GetXaxis()->SetTitle("Enu MeV");
       EnuHist[i]->GetYaxis()->SetTitle("Events");

       EnuQEHist[i] = new TH1F(Form("EnuQEHist=%.1f",Knots[i]),Form("EnuQEHist=%.1f",Knots[i]), 50, 0., 2000);
       EnuQEHist[i]->GetXaxis()->SetTitle("EnuQE MeV");
       EnuQEHist[i]->GetYaxis()->SetTitle("Events");

       kERecQEBiasHist[i] = new TH1F(Form("kERecQEBiasHist=%.1f",Knots[i]),Form("kERecQEBiasHist=%.1f",Knots[i]), 50, -1., 1);
       kERecQEBiasHist[i]->GetXaxis()->SetTitle("EnuQE Bias");
       kERecQEBiasHist[i]->GetYaxis()->SetTitle("Events");

       Nprotshist[i] = new TH1F(Form("Nprotshist_knot=%.1f",Knots[i]),Form("Nprotshist_knot=%.1f",Knots[i]), 6, 0, 6);
       Nprotshist[i]->GetXaxis()->SetTitle("N true protons");
       Nprotshist[i]->GetYaxis()->SetTitle("Events");

       Nneutshist[i] = new TH1F(Form("Nneutshist_knot=%.1f",Knots[i]),Form("Nneutshist_knot=%.1f",Knots[i]), 6, 0, 6);
       Nneutshist[i]->GetXaxis()->SetTitle("N true neutrons");
       Nneutshist[i]->GetYaxis()->SetTitle("Events");

       ProtMomhist[i] = new TH1F(Form("ProtMomhist_knot=%.1f",Knots[i]),Form("ProtMomhist_knot=%.1f",Knots[i]), 50, 0, 1400);
       ProtMomhist[i]->GetXaxis()->SetTitle("true HM proton momentum [MeV/c]");
       ProtMomhist[i]->GetYaxis()->SetTitle("Events");

       NeutMomhist[i] = new TH1F(Form("NeutMomhist_knot=%.1f",Knots[i]),Form("NeutMomhist_knot=%.1f",Knots[i]), 50, 0, 1000);
       NeutMomhist[i]->GetXaxis()->SetTitle("true HM neutron momentum [MeV/c]");
       NeutMomhist[i]->GetYaxis()->SetTitle("Events");

       ProtThetaist[i] = new TH1F(Form("ProtThetaist_knot=%.1f",Knots[i]),Form("ProtThetaist_knot=%.1f",Knots[i]), 50, -1., 1.);
       ProtThetaist[i]->GetXaxis()->SetTitle("true HM proton Cos#theta");
       ProtThetaist[i]->GetYaxis()->SetTitle("Events");

       NeutThetahist[i] = new TH1F(Form("NeutMomhist_knot=%.1f",Knots[i]),Form("NeutMomhist_knot=%.1f",Knots[i]), 50, -1., 1.);
       NeutThetahist[i]->GetXaxis()->SetTitle("true HM neutron Cos#theta");
       NeutThetahist[i]->GetYaxis()->SetTitle("Events");

       Q2hist[i] = new TH1F(Form("Q2hist_knot=%.1f",Knots[i]),Form("Q2hist_knot=%.1f",Knots[i]), 50, 0., 2000.);
       Q2hist[i]->GetXaxis()->SetTitle("true Q^{2}");
       Q2hist[i]->GetYaxis()->SetTitle("Events");

       q0hist[i] = new TH1F(Form("q0hist_knot=%.1f",Knots[i]),Form("Q0hist_knot=%.1f",Knots[i]), 50, 0., 1200.);
       q0hist[i]->GetXaxis()->SetTitle("true q_{0}");
       q0hist[i]->GetYaxis()->SetTitle("Events");

       q3hist[i] = new TH1F(Form("q3hist_knot=%.1f",Knots[i]),Form("q3hist_knot=%.1f",Knots[i]), 50, 0., 1200.);
       q3hist[i]->GetXaxis()->SetTitle("true q_{3}");
       q3hist[i]->GetYaxis()->SetTitle("Events");
    }
    std::cout<<" starting"<<std::endl;
    for(int ik = 0; ik < NFiles; ik++)
    {
      for (int i = 0; i < nentries[ik]; ++i)
      {
         if (i % (1000) == 0) std::cout<<i<<std::endl;
         tree[ik]->GetEntry(i);

         double weight = 1.;

         lephist[ik]->Fill(PFSLep[ik], weight);
         lepCoshist[ik]->Fill(CosFSLep[ik], weight);

         EnuHist[ik]->Fill(Enu[ik], weight);
         EnuQEHist[ik]->Fill(EnuQErec[ik], weight);
         kERecQEBiasHist[ik]->Fill(kERecQEBias[ik], weight);

         Nprotshist[ik]->Fill(NFSprot[ik], weight);
         Nneutshist[ik]->Fill(NFSneut[ik], weight);

         ProtMomhist[ik]->Fill(HMprotonMom[ik], weight);
         NeutMomhist[ik]->Fill(HMneutronMom[ik], weight);

         ProtThetaist[ik]->Fill(HMprotonTheta[ik], weight);
         NeutThetahist[ik]->Fill(HMneutronTheta[ik], weight);

         Q2hist[ik]->Fill(Q2[ik], weight);
         q0hist[ik]->Fill(q0[ik], weight);
         q3hist[ik]->Fill(q3[ik], weight);
      }
    }

    c1->Print("Reweight.pdf[");


    MakePlot(EnuHist, c1);
    MakePlot(EnuQEHist, c1);
    MakePlot(kERecQEBiasHist, c1);
    MakePlot(lephist, c1);
    MakePlot(lepCoshist, c1);
   MakePlot(ProtMomhist, c1);
   MakePlot(NeutMomhist, c1);
   MakePlot(ProtThetaist, c1);
   MakePlot(NeutThetahist, c1);
   MakePlot(Q2hist, c1);
   MakePlot(q0hist, c1);
   MakePlot(q3hist, c1);

    c1->Print("Reweight.pdf]");
}





void SetT2Kstyl()
{
     // -- WhichStyle --
    // 1 = presentation large fonts
    // 2 = presentation small fonts
    // 3 = publication/paper
    Int_t WhichStyle = 3;

    Int_t FontStyle = 22;
    Float_t FontSizeLabel = 0.035;
    Float_t FontSizeTitle = 0.05;
    Float_t YOffsetTitle = 1.3;

  switch(WhichStyle)
  {
    case 1:
        FontStyle = 42;
        FontSizeLabel = 0.05;
        FontSizeTitle = 0.065;
        YOffsetTitle = 1.19;
        break;
    case 2:
        FontStyle = 42;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.05;
        YOffsetTitle = 1.6;
        break;
    case 3:
        FontStyle = 132;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.045;
        YOffsetTitle = 1.6;
        break;
    }
    // use plain black on white colors
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetCanvasBorderSize(0);
    gStyle->SetFrameBorderSize(0);
    gStyle->SetDrawBorder(0);
    gStyle->SetTitleBorderSize(2);
    gStyle->SetStatBorderSize(2);

    gStyle->SetStatX(0.89);
    gStyle->SetStatY(0.89);

    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetStatColor(0);
    gStyle->SetFillColor(0);

    gStyle->SetEndErrorSize(4);
    gStyle->SetStripDecimals(kFALSE);

    //gStyle->SetLegendBorderSize(0); //This option dsables legends borders
    gStyle->SetLegendFont(FontStyle);

    // set the paper & margin sizes
    gStyle->SetPaperSize(20, 26);
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.14);
    gStyle->SetPadRightMargin(0.075); // 0.075 -> 0.13 for colz option
    gStyle->SetPadLeftMargin(0.12);//to include both large/small font options

    // Fonts, sizes, offsets
    gStyle->SetTextFont(FontStyle);
    gStyle->SetTextSize(FontSizeTitle);

    gStyle->SetLabelFont(FontStyle, "x");
    gStyle->SetLabelFont(FontStyle, "y");
    gStyle->SetLabelFont(FontStyle, "z");
    gStyle->SetLabelFont(FontStyle, "t");
    gStyle->SetLabelSize(FontSizeLabel, "x");
    gStyle->SetLabelSize(FontSizeLabel, "y");
    gStyle->SetLabelSize(0.030, "z");
    gStyle->SetLabelOffset(0.008, "x");
    gStyle->SetLabelOffset(0.008, "y");
    gStyle->SetLabelOffset(0.006, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleSize(FontSizeTitle, "t");
    gStyle->SetTitleOffset(1.1, "x");
    gStyle->SetTitleOffset(1.1, "y");
    gStyle->SetTitleOffset(1.1, "z");

    gStyle->SetTitleStyle(0);
    gStyle->SetTitleFontSize(0.045);//0.08
    gStyle->SetTitleFont(FontStyle, "pad");
    gStyle->SetTitleX(0.6);
    gStyle->SetTitleY(0.96);
    //gStyle->SetTitleW(0.8f);

    // use bold lines and markers
    gStyle->SetMarkerStyle(20); //FIXME Coment this for FGD2
    gStyle->SetHistLineWidth( Width_t(2.5) );
    gStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    gStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    //gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    //gStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(0);
    gStyle->SetPadTickY(0);

    // -- color --
    // functions blue
    //gStyle->SetFuncColor(600-4);
    gStyle->SetFuncColor(2);
    gStyle->SetFuncWidth(2);

    gStyle->SetFillColor(1); // make color fillings (not white)
    // - color setup for 2D -
    // - "cold"/ blue-ish -
    Double_t red[]   = { 0.00, 0.00, 0.00 };
    Double_t green[] = { 1.00, 0.00, 0.00 };
    Double_t blue[]  = { 1.00, 1.00, 0.25 };
    // - "warm" red-ish colors -
    //  Double_t red[]   = {1.00, 1.00, 0.25 };
    //  Double_t green[] = {1.00, 0.00, 0.00 };
    //  Double_t blue[]  = {0.00, 0.00, 0.00 };

    Double_t stops[] = { 0.25, 0.75, 1.00 };
    const Int_t NRGBs = 3;
    const Int_t NCont = 500;

    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    // - Rainbow -
    gStyle->SetPalette(1);  // use the rainbow color set

    // -- axis --
    gStyle->SetStripDecimals(kFALSE); // don't do 1.0 -> 1
    //  TGaxis::SetMaxDigits(3); // doesn't have an effect
    // no supressed zeroes!
    gStyle->SetHistMinimumZero(kTRUE);

    //gROOT->ForceStyle();
}
