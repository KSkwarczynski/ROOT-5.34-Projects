#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

// Function to create histograms for a specific mode
void createHistograms(TTree *treeBefore, TTree *treeAfter, int mode) {
    TLorentzVector *PFSLep = new TLorentzVector();
    TLorentzVector *PHMFSCPi = new TLorentzVector();
    TLorentzVector *PISNu = new TLorentzVector();

    double weight;
    float Q2;
    int Mode;

    // Set branch addresses
    treeBefore->SetBranchAddress("PFSLep", &PFSLep);
    treeBefore->SetBranchAddress("PHMFSCPi", &PHMFSCPi);
    treeBefore->SetBranchAddress("Q2", &Q2);
    treeBefore->SetBranchAddress("Mode", &Mode);
    treeBefore->SetBranchAddress("weight", &weight);
    treeBefore->SetBranchAddress("PISNu", &PISNu);

    // Create histograms for given mode
    TH1D *hBefore = new TH1D(Form("hBefore_mode%d", mode), Form("Momentum PFSLep for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *hAfter = new TH1D(Form("hAfter_mode%d", mode), Form("Momentum PFSLep for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);

    // Create histograms for PHMFSCPi momentum
    TH1D *hBeforePi = new TH1D(Form("hBeforePi_mode%d", mode), Form("Momentum PHMFSCPi for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *hAfterPi = new TH1D(Form("hAfterPi_mode%d", mode), Form("Momentum PHMFSCPi for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);

    // Create histograms for Q2
    TH1D *hBeforeQ2 = new TH1D(Form("hBeforeQ2_mode%d", mode), Form("Q2 for Mode==%d;Q2 (GeV^2);Events", mode), 20, 0, 2);
    TH1D *hAfterQ2 = new TH1D(Form("hAfterQ2_mode%d", mode), Form("Q2 for Mode==%d;Q2 (GeV^2);Events", mode), 20, 0, 2);

    // Create histograms for PISNu energy
    TH1D *hBeforePISNu = new TH1D(Form("hBeforePISNu_mode%d", mode), Form("Energy PISNu for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);
    TH1D *hAfterPISNu = new TH1D(Form("hAfterPISNu_mode%d", mode), Form("Energy PISNu for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);

    // Loop over entries in each file for the current mode
    for (int i = 0; i < treeBefore->GetEntries(); ++i) {
        treeBefore->GetEntry(i);
        if (Mode == mode) {
            hBefore->Fill(PFSLep->Vect().Mag(), weight);
            hBeforePi->Fill(PHMFSCPi->Vect().Mag(), weight);
            hBeforeQ2->Fill(Q2, weight);
            hBeforePISNu->Fill(PISNu->E(), weight);  // Fill histogram for PISNu energy
        }
    }

    treeAfter->SetBranchAddress("PFSLep", &PFSLep);
    treeAfter->SetBranchAddress("PHMFSCPi", &PHMFSCPi);
    treeAfter->SetBranchAddress("Q2", &Q2);
    treeAfter->SetBranchAddress("Mode", &Mode);
    treeAfter->SetBranchAddress("weight", &weight);
    treeAfter->SetBranchAddress("PISNu", &PISNu);

    for (int i = 0; i < treeAfter->GetEntries(); ++i) {
        treeAfter->GetEntry(i);
        if (Mode == mode) {
            hAfter->Fill(PFSLep->Vect().Mag(), weight);
            hAfterPi->Fill(PHMFSCPi->Vect().Mag(), weight);
            hAfterQ2->Fill(Q2, weight);
            hAfterPISNu->Fill(PISNu->E(), weight);  // Fill histogram for PISNu energy
        }
    }

    // Plotting
    TCanvas *c1 = new TCanvas(Form("c1_mode%d", mode), Form("Comparison of Momentum PFSLep for Mode %d", mode), 800, 600);
    c1->SaveAs(Form("comparison_mode%d.pdf[", mode));

    // Draw histograms for PFSLep momentum
    hBefore->SetLineColor(kRed);
    hAfter->SetLineColor(kBlue);
    hBefore->Draw("hist");
    hAfter->Draw("hist same");

    // Add a legend for PFSLep
    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(hBefore, "No Eb", "l");
    legend->AddEntry(hAfter, "+Eb=60MeV", "l");
    legend->Draw();
    c1->SaveAs(Form("comparison_mode%d.pdf", mode));

    // Draw histograms for PHMFSCPi momentum
    hBeforePi->SetLineColor(kRed);
    hAfterPi->SetLineColor(kBlue);
    hBeforePi->Draw("hist");
    hAfterPi->Draw("hist same");

    // Add a legend for PHMFSCPi
    TLegend *legendPi = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendPi->AddEntry(hBeforePi, "No Eb", "l");
    legendPi->AddEntry(hAfterPi, "+Eb=60MeV", "l");
    legendPi->Draw();
    c1->SaveAs(Form("comparison_mode%d.pdf", mode));

    // Draw histograms for Q2
    hBeforeQ2->SetLineColor(kRed);
    hAfterQ2->SetLineColor(kBlue);
    hBeforeQ2->Draw("hist");
    hAfterQ2->Draw("hist same");

    // Add a legend for Q2
    TLegend *legendQ2 = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendQ2->AddEntry(hBeforeQ2, "No Eb", "l");
    legendQ2->AddEntry(hAfterQ2, "+Eb=60MeV", "l");
    legendQ2->Draw();

    // Draw histograms for PISNu energy
    hBeforePISNu->SetLineColor(kRed);
    hAfterPISNu->SetLineColor(kBlue);
    hBeforePISNu->Draw("hist");
    hAfterPISNu->Draw("hist same");

    // Add a legend for PISNu energy
    TLegend *legendPISNu = new TLegend(0.7, 0.7, 0.9, 0.9);
    legendPISNu->AddEntry(hBeforePISNu, "No Eb", "l");
    legendPISNu->AddEntry(hAfterPISNu, "+Eb=60MeV", "l");
    legendPISNu->Draw();

    c1->SaveAs(Form("comparison_mode%d.pdf", mode));
    c1->SaveAs(Form("comparison_mode%d.pdf]", mode));

    // Cleanup
    delete PFSLep;
    delete PHMFSCPi;
    delete PISNu;
}

void compareFiles() {
    // Open the files
    TFile *fileBefore = TFile::Open("Before.root");
    TFile *fileAfter = TFile::Open("After3.root");

    // Get the T2KRWFlatTree tree
    TTree *treeBefore = (TTree*)fileBefore->Get("T2KRWFlatTree");
    TTree *treeAfter = (TTree*)fileAfter->Get("T2KRWFlatTree");

    // Create histograms for each mode
    createHistograms(treeBefore, treeAfter, 11);
    createHistograms(treeBefore, treeAfter, 12);
    createHistograms(treeBefore, treeAfter, 13);
    createHistograms(treeBefore, treeAfter, 31);
    createHistograms(treeBefore, treeAfter, 32);
    createHistograms(treeBefore, treeAfter, 33);
    createHistograms(treeBefore, treeAfter, 34);

    // Cleanup
    fileBefore->Close();
    fileAfter->Close();
}
