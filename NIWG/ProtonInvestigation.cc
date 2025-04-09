void ProtonInvestigation() {
  gStyle->SetOptStat(0);

  struct Sample {
    std::string label;
    std::string filename;
    int color;
    int linestyle;
  };

  // Define your samples with colors and line styles
  std::vector<Sample> samples = {
    {"NEUT 5.9.0 FSI OFF",  "NEUT_NUISFLAT.root",     kRed,        kSolid},
    {"NuWro 21.09 FSI OFF", "NuWro_NUISFLAT.root",    kBlue,       kDashed},
    {"NEUT 5.9.0 FSI ON",   "NEUT_FSI_NUISFLAT.root", kGreen + 2,  kDotted},
    {"NuWro 21.09 FSI ON",  "NuWro_FSI_NUISFLAT.root", kOrange + 7, kDashDotted}
  };

  const int Nbins = 10;
  const int Pbins = 100;

  std::map<std::string, std::vector<TH1F*>> hists = {
    {"protons",   {}},
    {"neutrons",  {}},
    {"piplus",    {}},
    {"pi0",       {}},
    {"pmax",      {}},
    {"costheta",  {}}
  };

  for (const auto& sample : samples) {
    TFile *file = TFile::Open(sample.filename.c_str());
    if (!file || file->IsZombie()) {
      std::cerr << "Failed to open file: " << sample.filename << std::endl;
      continue;
    }

    TTree *tree = (TTree*)file->Get("FlatTree_VARS");
    if (!tree) {
      std::cerr << "Tree 'FlatTree_VARS' not found in file: " << sample.filename << std::endl;
      continue;
    }

    // Variables
    Int_t nfsp, pdg[1000], Mode;
    Float_t px[1000], py[1000], pz[1000];
    double Weight;

    tree->SetBranchAddress("nfsp", &nfsp);
    tree->SetBranchAddress("pdg", pdg);
    tree->SetBranchAddress("px", px);
    tree->SetBranchAddress("py", py);
    tree->SetBranchAddress("pz", pz);
    tree->SetBranchAddress("fScaleFactor", &Weight);
    tree->SetBranchAddress("Mode", &Mode);

    auto make_hist = [&](const std::string& name, const std::string& title,
                         int bins, double xmin, double xmax) {
      std::string hname = "h_" + name + "_" + sample.label;
      std::string htitle = title + " (" + sample.label + ")";
      TH1F* h = new TH1F(hname.c_str(), htitle.c_str(), bins, xmin, xmax);
      h->SetLineColor(sample.color);
      h->SetLineStyle(sample.linestyle);
      h->SetLineWidth(2);
      return h;
                         };

  TH1F *h_p     = make_hist("protons",  "N_{p} per Event",     Nbins, 0, 10);
  TH1F *h_n     = make_hist("neutrons", "N_{n} per Event",     Nbins, 0, 10);
  TH1F *h_pip   = make_hist("piplus",   "N_{#pi^{+}} per Event", Nbins, 0, 10);
  TH1F *h_pi0   = make_hist("pi0",      "N_{#pi^{0}} per Event", Nbins, 0, 10);
  TH1F *h_pmax  = make_hist("pmax",     "Max Proton Momentum [GeV/c]", Pbins, 0, 4);
  TH1F *h_costh = make_hist("costheta", "cos#theta of Max P Proton", Pbins, -1, 1);

  hists["protons"].push_back(h_p);
  hists["neutrons"].push_back(h_n);
  hists["piplus"].push_back(h_pip);
  hists["pi0"].push_back(h_pi0);
  hists["pmax"].push_back(h_pmax);
  hists["costheta"].push_back(h_costh);

  Long64_t nentries = tree->GetEntries();
  for (Long64_t i = 0; i < nentries; ++i) {
    tree->GetEntry(i);
    if (Mode != 26 && Mode != 21) continue;

    int n_protons = 0, n_neutrons = 0, n_piplus = 0, n_pi0 = 0;
    float max_p = -1.0;
    int max_p_index = -1;

    for (int j = 0; j < nfsp; ++j) {
      switch (pdg[j]) {
        case 2212:
          ++n_protons;
          {
            float p = std::sqrt(px[j]*px[j] + py[j]*py[j] + pz[j]*pz[j]);
            if (p > max_p) {
              max_p = p;
              max_p_index = j;
            }
          }
          break;
        case 2112: ++n_neutrons; break;
        case 211:  ++n_piplus;   break;
        case 111:  ++n_pi0;      break;
      }
    }

    Weight = 1; // You can re-enable weight if needed
    h_p->Fill(n_protons, Weight);
    h_n->Fill(n_neutrons, Weight);
    h_pip->Fill(n_piplus, Weight);
    h_pi0->Fill(n_pi0, Weight);
    if (max_p > 0 && max_p_index >= 0) {
      h_pmax->Fill(max_p, Weight);
      float cos_theta = pz[max_p_index] / max_p;
      h_costh->Fill(cos_theta, Weight);
    }
  }
  }

  // Drawing section
  TCanvas *c1 = new TCanvas("c1", "Comparison", 800, 600);
  c1->Print("ProtonComparison.pdf[");

  auto draw_comparison = [&](const std::string& key, const std::string& ytitle) {
    bool first = true;
    TLegend *leg = new TLegend(0.65, 0.7, 0.88, 0.88);
    for (size_t i = 0; i < hists[key].size(); ++i) {
      TH1F* h = hists[key][i];
      double integral = h->Integral();
      if (integral > 0) h->Scale(1.0 / integral);

      h->GetYaxis()->SetTitle(ytitle.c_str());
      h->GetXaxis()->SetTitle(h->GetTitle());
      h->SetTitle("");
      h->Draw(first ? "HIST" : "HIST SAME");
      leg->AddEntry(h, samples[i].label.c_str(), "l");
      first = false;
    }
    leg->Draw();
    c1->Print("ProtonComparison.pdf");
  };

  draw_comparison("protons",   "Normalized Events");
  draw_comparison("neutrons",  "Normalized Events");
  draw_comparison("piplus",    "Normalized Events");
  draw_comparison("pi0",       "Normalized Events");
  draw_comparison("pmax",      "Normalized Events");
  draw_comparison("costheta",  "Normalized Events");

  c1->Print("ProtonComparison.pdf]");
  }
