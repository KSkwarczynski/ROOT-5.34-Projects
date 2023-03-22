


void pval() {


  TFile *file = new TFile("Posterior_Predictive.root");
  TTree *tree = (TTree*)file->Get("LLH_draws");


  const int nSample = 22;
  /*
  std::string SampleNames[nSample] = {
    "FGD1 numuCC 0pi 0 protons no photon",
    "FGD1 numuCC 0pi N protons no photon",
    "FGD1 numuCC 1pi no photon",
    "FGD1 numuCC other no photon",
    "FGD1 numuCC photon",

    "FGD2 numuCC 0pi 0 protons no photon",
    "FGD2 numuCC 0pi N protons no photon",
    "FGD2 numuCC 1pi no photon",
    "FGD2 numuCC other no photon",
    "FGD2 numuCC photon",

    "FGD1 anti-numuCC 0pi",
    "FGD1 anti-numuCC 1pi",
    "FGD1 anti-numuCC other",

    "FGD1 NuMuBkg CC0pi in AntiNu Mode",
    "FGD1 NuMuBkg CC1pi in AntiNu Mode",
    "FGD1 NuMuBkg CCother in AntiNu Mode",

    "FGD2 anti-numuCC 0pi",
    "FGD2 anti-numuCC 1pi",
    "FGD2 anti-numuCC other",

    "FGD2 NuMuBkg CC0pi in AntiNu Mode",
    "FGD2 NuMuBkg CC1pi in AntiNu Mode",
    "FGD2 NuMuBkg CCother in AntiNu Mode"};
 */

  std::string SampleNames[nSample] = {

    "FGD1 numuCC other no photon",
    "FGD2 numuCC other no photon",
    "FGD2 numuCC 0pi N protons no photon",
    "FGD2 NuMuBkg CCother in AntiNu Mode",
    "FGD2 anti-numuCC 1pi",


    "FGD2 numuCC 1pi no photon",
    "FGD2 numuCC photon",
    "FGD2 anti-numuCC other",
    "FGD1 NuMuBkg CCother in AntiNu Mode",
    "FGD1 numuCC 0pi N protons no photon",



    "FGD1 anti-numuCC 0pi",
    "FGD2 NuMuBkg CC0pi in AntiNu Mode",
    "FGD1 numuCC 0pi 0 protons no photon",


    "FGD1 numuCC 1pi no photon",
    "FGD2 numuCC 0pi 0 protons no photon",
    "FGD1 anti-numuCC 1pi",

    "FGD1 anti-numuCC other",
    "FGD1 NuMuBkg CC0pi in AntiNu Mode",
    "FGD1 NuMuBkg CC1pi in AntiNu Mode",


    "FGD2 anti-numuCC 0pi",
    "FGD2 NuMuBkg CC1pi in AntiNu Mode",
    "FGD1 numuCC photon"
};


    const int Types = 2;
    std::string LLHs[Types] =
    {
      "_predfluc_draw",
      "_data_draw"
    };


    double LLH[nSample][Types];
    std::string BranchNames[nSample][Types];

    tree->SetBranchStatus("*", false);

    TH2D ** Pvalue = new TH2D*[nSample];
    for (int is = 0; is < nSample; ++is)
    {
        Pvalue[is] = new TH2D(SampleNames[is].c_str(), SampleNames[is].c_str(), 50, 1, -1, 50, 1, -1);
        Pvalue[is]->GetXaxis()->SetTitle("-2LLH_{Pred Fluc, Draw}");
        Pvalue[is]->GetYaxis()->SetTitle("-2LLH_{Data, Draw}");

        for (int il = 0; il < Types; ++il)
        {
            BranchNames[is][il] = SampleNames[is] + LLHs[il];
            while (BranchNames[is][il].find(" ") != std::string::npos) {
                BranchNames[is][il].replace(BranchNames[is][il].find(" "), 1, std::string("_"));
            }

            while (BranchNames[is][il].find("-") != std::string::npos) {
                BranchNames[is][il].replace(BranchNames[is][il].find("-"), 1, std::string("_"));
            }

            std::cout<<BranchNames[is][il]<<std::endl;

            tree->SetBranchStatus(BranchNames[is][il].c_str(), true);
            tree->SetBranchAddress(BranchNames[is][il].c_str(), &LLH[is][il]);
        }
    }

    for (int i = 0; i < tree->GetEntries(); ++i)
    {
        if (i % (1000) == 0) std::cout<<i<<std::endl;
        tree->GetEntry(i);

        double LLHtemp[2] = {0., 0.};
        for (int is = 0; is < nSample; ++is)
        {
          //Pvalue[is]->Fill(LLH[is][0], LLH[is][1]);

          LLHtemp[0] += LLH[is][0];
          LLHtemp[1] += LLH[is][1];
          Pvalue[is]->Fill(LLHtemp[0], LLHtemp[1]);
        }
    }

    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    c1->SetTopMargin(0.12);
    c1->SetBottomMargin(0.12);
    c1->SetRightMargin(0.14);
    c1->SetLeftMargin(0.10);
    gPad->SetGrid();

    gStyle->SetPalette(51);
    gStyle->SetOptStat(0); //Set 0 to disable statystic box

    c1->Print("pval.pdf[");
    for (int is = 0; is < nSample; ++is)
    {

        const double TotalIntegral = Pvalue[is]->Integral();
        // Count how many fills are above y=x axis
        // This is the 2D p-value
        double Above = 0.0;
        for (int i = 0; i < Pvalue[is]->GetXaxis()->GetNbins(); ++i) {
          const double xvalue = Pvalue[is]->GetXaxis()->GetBinCenter(i+1);
          for (int j = 0; j < Pvalue[is]->GetYaxis()->GetNbins(); ++j) {
            const double yvalue = Pvalue[is]->GetYaxis()->GetBinCenter(j+1);
            // We're only interested in being _ABOVE_ the y=x axis
            if (xvalue >= yvalue) {
              Above += Pvalue[is]->GetBinContent(i+1, j+1);
            }
          }
        }
        const double pvalue = Above/TotalIntegral;
        std::stringstream ss;
        ss << int(Above) << "/" << int(TotalIntegral) << "=" << pvalue;
        Pvalue[is]->SetTitle((std::string(Pvalue[is]->GetTitle())+"_"+ss.str()).c_str());

        // Now add the TLine going diagonally
        double minimum = Pvalue[is]->GetXaxis()->GetBinLowEdge(1);
        if (Pvalue[is]->GetYaxis()->GetBinLowEdge(1) > minimum) {
          minimum = Pvalue[is]->GetYaxis()->GetBinLowEdge(1);
        }
        double maximum = Pvalue[is]->GetXaxis()->GetBinLowEdge(Pvalue[is]->GetXaxis()->GetNbins());
        if (Pvalue[is]->GetYaxis()->GetBinLowEdge(Pvalue[is]->GetYaxis()->GetNbins()) < maximum) {
          maximum = Pvalue[is]->GetYaxis()->GetBinLowEdge(Pvalue[is]->GetYaxis()->GetNbins());
          //KS: Extend by bin width to perfectly fit canvas
          maximum += Pvalue[is]->GetYaxis()->GetBinWidth(Pvalue[is]->GetYaxis()->GetNbins());
        }
        else maximum += Pvalue[is]->GetXaxis()->GetBinWidth(Pvalue[is]->GetXaxis()->GetNbins());
        TLine *TempLine = new TLine(minimum, minimum, maximum, maximum);
        TempLine->SetLineColor(kRed);
        TempLine->SetLineWidth(2);

        Pvalue[is]->SetMinimum(-0.01);
        Pvalue[is]->Draw("colz");
        TempLine->Draw("same");
        c1->Print("pval.pdf");
    }

    c1->Print("pval.pdf]");
}
