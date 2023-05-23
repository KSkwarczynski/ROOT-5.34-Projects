#include <cmath>

void SetT2Kstyl();
double GetPmissShapeWeight(const double Pmiss, const int target);

const double Pmiss_Bins[] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};
const double Pmiss_SRC_weight_C[] = {1.03828, 1.04218, 0.881711, 0.845165, 1.1546, 0.874676, 0.908355, 1.18892, 1.24608, 2.09019};
const double Pmiss_SRC_weight_O[] = {0.978954, 1.07854, 0.980071, 0.865904, 1.06439, 0.849815, 0.975878, 1.32599, 1.8081, 1.9782};
TH1D* SRC_C;
TH1D* SRC_O;


double FromValue = 0.;
double ToValue = 1.;
const int Target = 12;
void SRC_Dial_Achilles()
{

  SRC_C = new TH1D("SRC_C", "SRC_C", 10, Pmiss_Bins);
  for(int i = 0; i < SRC_C->GetXaxis()->GetNbins(); i++)
  {
    SRC_C->SetBinContent(SRC_C->FindBin(Pmiss_Bins[i]), Pmiss_SRC_weight_C[i]);
  }

  SRC_O = new TH1D("SRC_O", "SRC_O", 10, Pmiss_Bins);
  for(int i = 0; i < SRC_O->GetXaxis()->GetNbins(); i++)
  {
    SRC_O->SetBinContent(SRC_O->FindBin(Pmiss_Bins[i]), Pmiss_SRC_weight_O[i]);
  }
  TCanvas *Canvas = new TCanvas("Canvas", "Canvas", 1024, 1024);
  SetT2Kstyl();
  Canvas->Print("SRC_Dial_Achilles.pdf[", "pdf");

  TFile *file = new TFile("numu_O_Compareison_Pauli.root");
  TTree *tree = (TTree*)file->Get("sample_sum");

  int isSRC;
  double Pmiss;

  tree->SetBranchStatus("*", false);

  tree->SetBranchStatus( "isSRC", true);
  tree->SetBranchAddress("isSRC", &(isSRC));

  tree->SetBranchStatus( "Pmiss", true);
  tree->SetBranchAddress("Pmiss", &(Pmiss));


  const int Nbins = 10;
  double Binning[] = {300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800};

  TH1F* hPmiss = new TH1F("hPmiss", "hPmiss",  Nbins, Binning);
  hPmiss->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss->SetLineColor(kBlue);
  hPmiss->SetLineWidth(2);

  TH1F* hPmiss_Paper = new TH1F("hPmiss_Paper", "hPmiss_Paper",  Nbins, Binning);
  hPmiss_Paper->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss_Paper->SetLineColor(kMagenta);
  hPmiss_Paper->SetLineWidth(2);

  TH1F* hPmiss_reweight = new TH1F("hPmiss_reweight", "hPmiss_reweight",  Nbins, Binning);
  hPmiss_reweight->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss_reweight->SetLineColor(kRed);
  hPmiss_reweight->SetLineStyle(kDotted);
  hPmiss_reweight->SetLineWidth(2);


  TH1F* hPmiss_MF = new TH1F("hPmiss_MF", "hPmiss_MF",  50, 0, 800);
  hPmiss_MF->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss_MF->SetFillColor(kBlue);
  hPmiss_MF->SetLineColor(kBlue);
  hPmiss_MF->SetLineWidth(2);

  TH1F* hPmiss_SRC = new TH1F("hPmiss_SRC", "hPmiss_SRC",  50, 0, 800);
  hPmiss_SRC->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss_SRC->SetFillColor(kRed);
  hPmiss_SRC->SetLineColor(kRed);
  hPmiss_SRC->SetLineWidth(2);


  TH1F* hPmiss_SRC_reweight = new TH1F("hPmiss_SRC_reweight", "hPmiss_SRC_reweight",  50, 0, 800);
  hPmiss_SRC_reweight->GetXaxis()->SetTitle("p_{miss} [MeV/c]");
  hPmiss_SRC_reweight->SetLineColor(kGreen);
  hPmiss_SRC_reweight->SetLineWidth(2);

  for (int i = 0; i < tree->GetEntries(); ++i)
  {
      if (i % (1000) == 0) std::cout<<i<<std::endl;
      tree->GetEntry(i);

      if(isSRC)
      {
       hPmiss_SRC->Fill(Pmiss);
       double weight = GetPmissShapeWeight(Pmiss, Target);
       hPmiss_SRC_reweight->Fill(Pmiss, weight);
      }
      else
        hPmiss_MF->Fill(Pmiss);

      if(isSRC && Pmiss > 300)
      {
        hPmiss->Fill(Pmiss);
        double weight = GetPmissShapeWeight(Pmiss, Target);
        hPmiss_reweight->Fill(Pmiss, weight);
      }
  }
  TLegend *legend1 = new TLegend(0.60,0.52,0.80,0.88);
  legend1->AddEntry(hPmiss_MF, "MF NEUT","lfe");
  legend1->AddEntry(hPmiss_SRC, "SRC NEUT","lfe");
  legend1->AddEntry(hPmiss_SRC_reweight, "SRC reweighted","lfe");
  legend1->SetTextSize(0.038);

  THStack* Stack = new THStack("stack", "stack");
  Stack->Add( hPmiss_SRC );
  Stack->Add( hPmiss_MF );

  Stack->Draw();
  hPmiss_SRC_reweight->Draw("hist same");
  legend1->Draw("same");

  Stack->GetXaxis();
  Stack->GetXaxis()->SetTitle("p_{miss} [MeV/c]");

  Canvas->Print("SRC_Dial_Achilles.pdf", "pdf");

  Canvas->SetLogy(true);
  Canvas->Update();
  Canvas->Print("SRC_Dial_Achilles.pdf", "pdf");

  Canvas->SetLogy(false);

  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(300), 0.280);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(350), 0.150);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(400), 0.090);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(450), 0.060);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(500), 0.050);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(550), 0.025);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(600), 0.018);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(650), 0.012);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(700), 0.007);
  hPmiss_Paper->SetBinContent(hPmiss_Paper->FindBin(750), 0.004);

  TLegend *legend= new TLegend(0.40,0.52,0.60,0.88);
  legend->AddEntry(hPmiss, "Neut","lfe");
  legend->AddEntry(hPmiss_Paper, "Achilles","lfe");
  //legend->AddEntry(hPmiss_reweight, "Reweighted","lfe");
  legend->SetTextSize(0.038);

  hPmiss->Scale(1/hPmiss->Integral());
  hPmiss_Paper->Scale(1/hPmiss_Paper->Integral());
  hPmiss_reweight->Scale(1/hPmiss_reweight->Integral());

  if(hPmiss_Paper->GetMaximum() > hPmiss->GetMaximum() ) hPmiss->SetMaximum(hPmiss_Paper->GetMaximum()*1.1);

  hPmiss->Draw("hist");
  hPmiss_Paper->Draw("hist same");
  //hPmiss_reweight->Draw("hist same");

  legend->Draw("SAME");
  Canvas->Print("SRC_Dial_Achilles.pdf", "pdf");

  Canvas->SetLogy(true);
  Canvas->Update();
  Canvas->Print("SRC_Dial_Achilles.pdf", "pdf");

  Canvas->SetLogy(false);

  for (int i = 1; i <= hPmiss->GetXaxis()->GetNbins(); i++)
  {
      std::cout<< hPmiss_Paper->GetBinContent(i)/hPmiss->GetBinContent(i)<<std::endl;
  }
  Canvas->Print("SRC_Dial_Achilles.pdf]", "pdf");
}


//KS: Based on Phys. Rev. D 107, 033007
double GetPmissShapeWeight(const double Pmiss, const int target)
{
  //KS: Neut doesn't have much events above 800 so no point reweighting
  if(Pmiss < 300 || Pmiss > 800) return 1;
  double weight = 1;

  // Carbon
  if (target == 12)
    weight = SRC_C->GetBinContent(SRC_C->FindBin(Pmiss));
  else if (target == 16)
    weight = SRC_O->GetBinContent(SRC_O->FindBin(Pmiss));
  else return 1;

  //KS: Basically linear interpolation if ToValue is different than 1
  weight = (weight-1) * ToValue + (1-FromValue);

  if(weight < 0) return 0;
  return weight;

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
    gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    //gStyle->SetOptFit(0);

    gStyle->SetPaintTextFormat("4.1f"); //Precision of value in matrix element

    gROOT->ForceStyle();
}
