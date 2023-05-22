#include <cmath>

void SetT2Kstyl();

void SF_Analysis()
{

  TChain* Chain = new TChain("FlatTree_VARS","FlatTree_VARS");
  Chain->Add("t2k.flat.mono.root");

  const int NPart_Final = 3;
  const int NPart_Init = 2;

  int pdg[NPart_Final];
  float px[NPart_Final];
  float py[NPart_Final];
  float pz[NPart_Final];
  float E[NPart_Final];

  int pdg_init[NPart_Init];
  float px_init[NPart_Init];
  float py_init[NPart_Init];
  float pz_init[NPart_Init];
  float E_init[NPart_Init];

  float q0, q3, Q2;

  Chain->SetBranchStatus("*", false);
  //lepton = 0, proton = 1, target = 2
  Chain->SetBranchStatus("pdg", true);
  Chain->SetBranchAddress("pdg", &pdg);
  Chain->SetBranchStatus("px", true);
  Chain->SetBranchAddress("px", &px);
  Chain->SetBranchStatus("py", true);
  Chain->SetBranchAddress("py", &py);
  Chain->SetBranchStatus("pz", true);
  Chain->SetBranchAddress("pz", &pz);
  Chain->SetBranchStatus("E", true);
  Chain->SetBranchAddress("E", &E);

  //Target = 0, neutrino = 1
  Chain->SetBranchStatus("pdg_init", true);
  Chain->SetBranchAddress("pdg_init", &pdg_init);
  Chain->SetBranchStatus("px_init", true);
  Chain->SetBranchAddress("px_init", &px_init);
  Chain->SetBranchStatus("py_init", true);
  Chain->SetBranchAddress("py_init", &py_init);
  Chain->SetBranchStatus("pz_init", true);
  Chain->SetBranchAddress("pz_init", &pz_init);
  Chain->SetBranchStatus("E_init", true);
  Chain->SetBranchAddress("E_init", &E_init);

  Chain->SetBranchStatus("q0", true);
  Chain->SetBranchAddress("q0", &q0);
  Chain->SetBranchStatus("q3", true);
  Chain->SetBranchAddress("q3", &q3);
  Chain->SetBranchStatus("Q2", true);
  Chain->SetBranchAddress("Q2", &Q2);

  TCanvas *Canvas = new TCanvas("Canvas", "Canvas", 1024, 1024);
  SetT2Kstyl();
  Canvas->Print("SF_anal.pdf[", "pdf");


  TH1F* Enu = new TH1F("Enu", "Enu", 50, 0, 1000);
  Enu->GetXaxis()->SetTitle("E_{#{nu}} [MeV]");
  Enu->SetLineWidth(2);
  Enu->SetLineColor(kBlue);

  TH1F* LepMom = new TH1F("LepMom", "LepMom", 50, 0, 1000);
  LepMom->GetXaxis()->SetTitle("true p_{#mu} [MeV/c]");
  LepMom->SetLineWidth(2);
  LepMom->SetLineColor(kBlue);

  TH1F* NucleonMom = new TH1F("NucleonMom", "NucleonMom", 50, 0, 1000);
  NucleonMom->GetXaxis()->SetTitle("true p_{proton} [MeV/c]");
  NucleonMom->SetLineWidth(2);
  NucleonMom->SetLineColor(kBlue);

  TH1F* NucleonTheta = new TH1F("NucleonTheta", "NucleonTheta", 50, -1, 1);
  NucleonTheta->GetXaxis()->SetTitle("true cos(#theta_{proton})");
  NucleonTheta->SetLineWidth(2);
  NucleonTheta->SetLineColor(kBlue);

  TH1F* Pmiss = new TH1F("Pmiss", "Pmiss", 50, 0, 400);
  Pmiss->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  Pmiss->SetLineWidth(2);
  Pmiss->SetLineColor(kBlue);

  TH1F* Emiss = new TH1F("Emiss", "Emiss", 50, 0, 100);
  Emiss->GetXaxis()->SetTitle("E_{miss} [MeV]");
  Emiss->SetLineWidth(2);
  Emiss->SetLineColor(kBlue);

  TH1F* hq0 = new TH1F("hq0", "hq0", 50, 0, 1000);
  hq0->GetXaxis()->SetTitle("q_{0} [MeV]");
  hq0->SetLineWidth(2);
  hq0->SetLineColor(kBlue);

  TH1F* hq3 = new TH1F("hq3", "hq3", 50, 0, 1000);
  hq3->GetXaxis()->SetTitle("q_{3} [MeV]");
  hq3->SetLineWidth(2);
  hq3->SetLineColor(kBlue);

  TH1F* hQ2 = new TH1F("hQ2", "hQ2", 50, 0, 1000);
  hQ2->GetXaxis()->SetTitle("Q^{2} [MeV]");
  hQ2->SetLineWidth(2);
  hQ2->SetLineColor(kBlue);

  TH2D* Spectral = new TH2D("Spectral", "Spectral", 50, 0, 400, 50, 0, 100);
  Spectral->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  Spectral->GetYaxis()->SetTitle("E_{miss} [MeV]");

  const float Dalton_GeV = 0.93149410242;
  const float massRemnant = 11.01143260 * Dalton_GeV;
  const float mass_proton = 0.938272;

  for(int i = 0 ; i< Chain->GetEntries(); i++)
  {
    Chain->GetEntry(i);

    TLorentzVector  Neutrino(px_init[1], py_init[1], pz_init[1], E_init[1]);
    TLorentzVector  Lepton(px[0], py[0], pz[0], E[0]);
    TLorentzVector  Nucleon(px[1], py[1], pz[1], E[1]);

    const float p_miss = (Neutrino - Lepton - Nucleon).Vect().Mag();
    const float Trem = std::sqrt(std::pow(p_miss, 2) + std::pow(massRemnant, 2)) - massRemnant;
    const float E_miss = Neutrino.E() + mass_proton - Lepton.E() - Nucleon.E() - Trem;

    Enu->Fill(Neutrino.E()*1000);
    LepMom->Fill(Lepton.Vect().Mag()*1000);
    NucleonMom->Fill(Nucleon.Vect().Mag()*1000);

    NucleonTheta->Fill( Nucleon.Vect().Unit().Dot(Neutrino.Vect().Unit()));

    Pmiss->Fill(p_miss*1000);
    Emiss->Fill(E_miss*1000);
    Spectral->Fill(p_miss*1000, E_miss*1000);

    hq0->Fill(q0*1000);
    hq3->Fill(q3*1000);
    hQ2->Fill(Q2*1000);
  }

  Enu->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  LepMom->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  NucleonMom->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  NucleonTheta->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  Pmiss->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  Emiss->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  hq0->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  hq3->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  hQ2->Draw();
  Canvas->Print("SF_anal.pdf", "pdf");

  Spectral->Draw("colz");
  Canvas->Print("SF_anal.pdf", "pdf");


  TFile *file = new TFile("C_Numu_NoPauli.root");
  TTree *tree = (TTree*)file->Get("sample_sum");

  int NFSprot, NFSneut;
  double HMprotonMom, HMneutronMom, HMprotonTheta, HMneutronTheta, q00, q33,Q22, Pmiss_dN, Emiss_dN;

  tree->SetBranchStatus("*", false);

  tree->SetBranchStatus( "NFSprot", true);
  tree->SetBranchAddress("NFSprot", &(NFSprot));

  tree->SetBranchStatus( "NFSneut", true);
  tree->SetBranchAddress("NFSneut", &(NFSneut));

  tree->SetBranchStatus( "HMprotonMom", true);
  tree->SetBranchAddress("HMprotonMom", &(HMprotonMom));

  tree->SetBranchStatus( "HMneutronMom", true);
  tree->SetBranchAddress("HMneutronMom", &(HMneutronMom));

  tree->SetBranchStatus( "HMprotonTheta", true);
  tree->SetBranchAddress("HMprotonTheta", &(HMprotonTheta));

  tree->SetBranchStatus( "HMneutronTheta", true);
  tree->SetBranchAddress("HMneutronTheta", &(HMneutronTheta));

  tree->SetBranchStatus( "q0", true);
  tree->SetBranchAddress("q0", &(q00));

  tree->SetBranchStatus( "q3", true);
  tree->SetBranchAddress("q3", &(q33));

  tree->SetBranchStatus( "Q2", true);
  tree->SetBranchAddress("Q2", &(Q22));

  tree->SetBranchStatus( "Pmiss", true);
  tree->SetBranchAddress("Pmiss", &(Pmiss_dN));

  tree->SetBranchStatus( "Emiss", true);
  tree->SetBranchAddress("Emiss", &(Emiss_dN));


  TH1F* LepMom_N = new TH1F("LepMom_N", "LepMom_N", 50, 0, 1000);
  LepMom_N->GetXaxis()->SetTitle("true p_{#mu} [MeV/c]");
  LepMom_N->SetLineColor(kRed);
  LepMom_N->SetLineWidth(2);

  TH1F* NucleonMom_N = new TH1F("NucleonMom_N", "NucleonMom_N", 50, 0, 1000);
  NucleonMom_N->GetXaxis()->SetTitle("true p_{proton} [MeV/c]");
  NucleonMom_N->SetLineColor(kRed);
  NucleonMom_N->SetLineWidth(2);

  TH1F* NucleonTheta_N = new TH1F("NucleonTheta_N", "NucleonTheta_N", 50, -1, 1);
  NucleonTheta_N->GetXaxis()->SetTitle("true #cos{#theta_{proton}}");
  NucleonTheta_N->SetLineColor(kRed);
  NucleonTheta_N->SetLineWidth(2);

  TH1F* Pmiss_N = new TH1F("Pmiss_N", "Pmiss_N", 50, 0, 400);
  Pmiss_N->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  Pmiss_N->SetLineColor(kRed);
  Pmiss_N->SetLineWidth(2);

  TH1F* Emiss_N = new TH1F("Emiss_N", "Emiss_N", 50, 0, 100);
  Emiss_N->GetXaxis()->SetTitle("E_{miss} [MeV]");
  Emiss_N->SetLineColor(kRed);
  Emiss_N->SetLineWidth(2);

  TH1F* hq0_N = new TH1F("hq0_N", "hq0_N", 50, 0, 1000);
  hq0_N->GetXaxis()->SetTitle("q_{0} [MeV]");
  hq0_N->SetLineWidth(2);
  hq0_N->SetLineColor(kRed);

  TH1F* hq3_N = new TH1F("hq3_N", "hq3_N", 50, 0, 1000);
  hq3_N->GetXaxis()->SetTitle("q_{3} [MeV]");
  hq3_N->SetLineWidth(2);
  hq3_N->SetLineColor(kRed);

  TH1F* hQ2_N = new TH1F("hQ2_N", "hQ2_N", 50, 0, 1000);
  hQ2_N->GetXaxis()->SetTitle("Q^{2} [MeV]");
  hQ2_N->SetLineWidth(2);
  hQ2_N->SetLineColor(kRed);

  for (int i = 0; i < tree->GetEntries(); ++i)
  {
      if (i % (1000) == 0) std::cout<<i<<std::endl;
      tree->GetEntry(i);
      NucleonMom_N->Fill(HMprotonMom);
      NucleonTheta_N->Fill(HMprotonTheta);
      Pmiss_N->Fill(Pmiss_dN);
      Emiss_N->Fill(Emiss_dN);

      hq0_N->Fill(q00);
      hq3_N->Fill(q33);
      hQ2_N->Fill(Q22);
  }

  TLegend *legend= new TLegend(0.40,0.52,0.60,0.88);
  legend->AddEntry(NucleonMom, "Achilles C","lfe");
  legend->AddEntry(NucleonMom_N, "NEUT C","lfe");
  legend->SetTextSize(0.038);

  NucleonMom->Scale(1/NucleonMom->Integral());
  NucleonMom_N->Scale(1/NucleonMom_N->Integral());
  if(NucleonMom_N->GetMaximum() > NucleonMom->GetMaximum() ) NucleonMom->SetMaximum(NucleonMom_N->GetMaximum()*1.1);
  NucleonMom->Draw("h");
  NucleonMom_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");

  NucleonTheta->Scale(1/NucleonTheta->Integral());
  NucleonTheta_N->Scale(1/NucleonTheta_N->Integral());
  if(NucleonTheta_N->GetMaximum() > NucleonTheta->GetMaximum() ) NucleonTheta->SetMaximum(NucleonTheta_N->GetMaximum()*1.1);
  NucleonTheta->Draw("h");
  NucleonTheta_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");

  hq0->Scale(1/hq0->Integral());
  hq0_N->Scale(1/hq0_N->Integral());
  hq0->Draw("h");
  hq0_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");

  hq3->Scale(1/Pmiss->Integral());
  hq3_N->Scale(1/hq3_N->Integral());
  hq3->Draw("h");
  hq3_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");


  hQ2->Scale(1/hQ2->Integral());
  hQ2_N->Scale(1/hQ2_N->Integral());
  hQ2->Draw("h");
  hQ2_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");


  Pmiss->Scale(1/Pmiss->Integral());
  Pmiss_N->Scale(1/Pmiss_N->Integral());
  Pmiss->Draw("h");
  Pmiss_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");

  Emiss->Scale(1/Emiss->Integral());
  Emiss_N->Scale(1/Emiss_N->Integral());
  Emiss->Draw("h");
  Emiss_N->Draw("h same");
  legend->Draw("same");
  Canvas->Print("SF_anal.pdf", "pdf");

  Canvas->Print("SF_anal.pdf]", "pdf");
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

    gStyle->SetLegendBorderSize(0); //This option dsables legends borders
    gStyle->SetFillStyle(0);
    gStyle->SetLegendFont(FontStyle);

    // Fonts, sizes, offsets
    gStyle->SetTextFont(FontStyle);
    gStyle->SetTextSize(FontSizeTitle);

    gStyle->SetLabelFont(FontStyle, "x");
    gStyle->SetLabelFont(FontStyle, "y");
    gStyle->SetLabelFont(FontStyle, "z");
    gStyle->SetLabelFont(FontStyle, "t");
    gStyle->SetLabelSize(FontSizeLabel, "x");
    gStyle->SetLabelSize(FontSizeLabel, "y");
    gStyle->SetLabelSize(FontSizeLabel, "z");
    gStyle->SetLabelOffset(0.015, "x");
    gStyle->SetLabelOffset(0.015, "y");
    gStyle->SetLabelOffset(0.015, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleSize(FontSizeTitle, "t");
    gStyle->SetTitleOffset(1.0, "x");
    gStyle->SetTitleOffset(1.0, "y");
    gStyle->SetTitleOffset(1.0, "z");

    gStyle->SetTitleStyle(0);
    gStyle->SetTitleFontSize(0.045);//0.08
    gStyle->SetTitleFont(FontStyle, "pad");
    gStyle->SetTitleX(0.6);
    gStyle->SetTitleY(0.96);
    //gStyle->SetTitleW(0.8f);

    // do not display any of the standard histogram decorations
    //gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    //gStyle->SetOptFit(0);

    gStyle->SetPaintTextFormat("4.1f"); //Precision of value in matrix element

    gROOT->ForceStyle();
}
