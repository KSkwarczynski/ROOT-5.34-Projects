#include "NIWG/Interface/NIWGEvent.h"
#include "NIWG/Utils/InteractionUtils.h"

#include "TChain.h"
#include "TCanvas.h"
#include "TVector3.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"

#include <iostream>
#include <fstream>

TCanvas* c1 = nullptr;

void MakeOverlayPlot(const std::string& file_EDRMF, const std::string& file_SF, const std::string& target, const std::string& beam)
{
    auto getHist = [&target, &beam](const std::string& file, const std::string& tag) {
        TChain niwgtree("NIWGTree");
        niwgtree.Add(file.c_str());

        niwg::NIWGEvent* nwev = nullptr;
        niwgtree.SetBranchAddress("NIWGEvent", &nwev);

        TH1D* h_emiss = new TH1D(("h_emiss_" + tag).c_str(), ("Emiss " + target + " " + beam).c_str(), 100, 0.0, 0.15);
        TH1D* h_pmiss = new TH1D(("h_pmiss_" + tag).c_str(), ("Pmiss " + target + " " + beam).c_str(), 100, 0.0, 1.0);

        h_emiss->GetXaxis()->SetTitle("Emiss [GeV]");
        h_emiss->GetYaxis()->SetTitle("Events");
        h_pmiss->GetXaxis()->SetTitle("Pmiss [GeV/c]");
        h_pmiss->GetYaxis()->SetTitle("Events");

        h_emiss->SetStats(0);
        h_pmiss->SetStats(0);

        Long64_t nevents = niwgtree.GetEntries();
        for (Long64_t i = 0; i < nevents; ++i)
        {
            niwgtree.GetEntry(i);
            if (!niwg::utils::isCCQE(nwev->neutmode)) continue;

            h_emiss->Fill(nwev->Emiss);
            h_pmiss->Fill(nwev->Pmiss);
        }

        return std::make_pair(h_emiss, h_pmiss);
    };

    auto [h_emiss_edrmf, h_pmiss_edrmf] = getHist(file_EDRMF, "EDRMF");
    auto [h_emiss_sf, h_pmiss_sf] = getHist(file_SF, "SF");

    h_emiss_edrmf->SetLineColor(kBlue);
    h_emiss_sf->SetLineColor(kRed);
    h_pmiss_edrmf->SetLineColor(kBlue);
    h_pmiss_sf->SetLineColor(kRed);

    h_emiss_edrmf->SetLineWidth(2);
    h_emiss_sf->SetLineWidth(2);
    h_pmiss_edrmf->SetLineWidth(2);
    h_pmiss_sf->SetLineWidth(2);

    TLegend* leg_emiss = new TLegend(0.65, 0.75, 0.88, 0.88);
    leg_emiss->AddEntry(h_emiss_edrmf, "EDRMF", "l");
    leg_emiss->AddEntry(h_emiss_sf, "SF", "l");

    TLegend* leg_pmiss = new TLegend(0.65, 0.75, 0.88, 0.88);
    leg_pmiss->AddEntry(h_pmiss_edrmf, "EDRMF", "l");
    leg_pmiss->AddEntry(h_pmiss_sf, "SF", "l");

    gStyle->SetOptStat(0);

    // Emiss
    if (h_emiss_sf->GetMaximum() > h_emiss_edrmf->GetMaximum())
        h_emiss_edrmf->SetMaximum(h_emiss_sf->GetMaximum() * 1.05);
    h_emiss_edrmf->Draw("HIST");
    h_emiss_sf->Draw("HIST SAME");
    leg_emiss->Draw();
    c1->Print("Shells.pdf");

    // Pmiss
    if (h_pmiss_sf->GetMaximum() > h_pmiss_edrmf->GetMaximum())
        h_pmiss_edrmf->SetMaximum(h_pmiss_sf->GetMaximum() * 1.05);
    h_pmiss_edrmf->Draw("HIST");
    h_pmiss_sf->Draw("HIST SAME");
    leg_pmiss->Draw();
    c1->Print("Shells.pdf");

    delete h_emiss_edrmf;
    delete h_emiss_sf;
    delete h_pmiss_edrmf;
    delete h_pmiss_sf;
    delete leg_emiss;
    delete leg_pmiss;
}

void Make2DPlot(const std::string& file, const std::string& tag, const std::string& target, const std::string& beam)
{
    TChain niwgtree("NIWGTree");
    niwgtree.Add(file.c_str());

    niwg::NIWGEvent* nwev = nullptr;
    niwgtree.SetBranchAddress("NIWGEvent", &nwev);

    TH2D* h2d = new TH2D(("h2d_" + tag).c_str(),
                         ("Pmiss vs Emiss " + tag + " " + target + " " + beam).c_str(),
                         100, 0.0, 1.0,    // X axis: Pmiss [GeV/c]
                         100, 0.0, 0.15);  // Y axis: Emiss [GeV]

    h2d->GetXaxis()->SetTitle("Pmiss [GeV/c]");
    h2d->GetYaxis()->SetTitle("Emiss [GeV]");
    h2d->SetStats(0);

    Long64_t nevents = niwgtree.GetEntries();
    for (Long64_t i = 0; i < nevents; ++i)
    {
        niwgtree.GetEntry(i);
        if (!niwg::utils::isCCQE(nwev->neutmode)) continue;

        h2d->Fill(nwev->Pmiss, nwev->Emiss);
    }

    h2d->Draw("COLZ");
    c1->Print("Shells.pdf");

    delete h2d;
}

void ProcessTarget(const std::string& sp, const std::string& target, const std::string& basePath)
{
    std::string file_edrmf = basePath + sp + "_" + target + "_EDRMF_0.root";
    std::string file_sf    = basePath + sp + "_" + target + "_SF_0.root";

    std::ifstream fedrmf(file_edrmf), fsf(file_sf);
    if (!fedrmf.good()) {
        std::cerr << "File not found: " << file_edrmf << "\n";
        return;
    }
    if (!fsf.good()) {
        std::cerr << "File not found: " << file_sf << "\n";
        return;
    }

    std::string beam = (sp == "numu") ? "#nu_{#mu}" : "#bar{#nu}_{#mu}";

    std::cout << "Processing target " << target << ":\n"
    << "  " << file_edrmf << "\n"
    << "  " << file_sf << "\n";

    MakeOverlayPlot(file_edrmf, file_sf, target, beam);
    Make2DPlot(file_edrmf, "EDRMF", target, beam);
    Make2DPlot(file_sf, "SF", target, beam);
}

int main()
{
    c1 = new TCanvas("c1", "Canvas", 800, 600);
    c1->SetGrid();

    c1->Print("Shells.pdf[");

    std::string basePath = "/mnt/home/kskwarczynski/T2K_OA/NEUT/EDRMF/Template/NIWG_Output/Correct/";

    ProcessTarget("numu", "C", basePath);
    ProcessTarget("numu", "O", basePath);
    ProcessTarget("numubar", "C", basePath);
    ProcessTarget("numubar", "O", basePath);

    c1->Print("Shells.pdf]");

    delete c1;
    return 0;
}
