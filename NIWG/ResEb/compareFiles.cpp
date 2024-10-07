#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

const double XMN = 0.938919008;  // Neutron mass (GeV)
const double XMN2 = XMN * XMN; // Neutron mass squared (GeV^2)

double calculateResEb(double E, double Q2, double W, double ELEPL) {
  // Calculate W^2
  double W2 = W * W;

  // Calculate the numerator for RESEB
  double numerator = (2 * E * XMN) + XMN2 - Q2 - W2;

  //std::cout<<"E="<<E<<" numerator="<<numerator<<" 2 * XMN="<<2 * XMN<<"  ELEPL="<<ELEPL<<std::endl;
  // Calculate RESEB
  double RESEB = numerator / (2 * XMN) - ELEPL;

  return RESEB;
}

// Function to create histograms for a specific mode
void createHistograms(TTree *treeBefore, TTree *tree10MeV, TTree *tree25MeV, int mode) {
    TLorentzVector *PFSLep = new TLorentzVector();
    TLorentzVector *PHMFSCPi = new TLorentzVector();
    TLorentzVector *PISNu = new TLorentzVector();

    double weight;
    float Q2, W;
    int Mode;

    // Set branch addresses
    treeBefore->SetBranchAddress("PFSLep", &PFSLep);
    treeBefore->SetBranchAddress("PHMFSCPi", &PHMFSCPi);
    treeBefore->SetBranchAddress("Q2", &Q2);
    treeBefore->SetBranchAddress("Mode", &Mode);
    treeBefore->SetBranchAddress("weight", &weight);
    treeBefore->SetBranchAddress("PISNu", &PISNu);
    treeBefore->SetBranchAddress("PISNu", &PISNu);

    // Create histograms for given mode
    TH1D *hBefore = new TH1D(Form("hBefore_mode%d", mode), Form("Momentum PFSLep for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *h10MeV = new TH1D(Form("h10MeV_mode%d", mode), Form("Momentum PFSLep for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *h25MeV = new TH1D(Form("h25MeV_mode%d", mode), Form("Momentum PFSLep for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);

    // Repeat for PHMFSCPi
    TH1D *hBeforePi = new TH1D(Form("hBeforePi_mode%d", mode), Form("Momentum PHMFSCPi for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *h10MeVPi = new TH1D(Form("h10MeVPi_mode%d", mode), Form("Momentum PHMFSCPi for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);
    TH1D *h25MeVPi = new TH1D(Form("h25MeVPi_mode%d", mode), Form("Momentum PHMFSCPi for Mode==%d;Momentum (GeV);Events", mode), 20, 0, 2);

    // Repeat for Q2
    TH1D *hBeforeQ2 = new TH1D(Form("hBeforeQ2_mode%d", mode), Form("Q2 for Mode==%d;Q2 (GeV^2);Events", mode), 20, 0, 2);
    TH1D *h10MeVQ2 = new TH1D(Form("h10MeVQ2_mode%d", mode), Form("Q2 for Mode==%d;Q2 (GeV^2);Events", mode), 20, 0, 2);
    TH1D *h25MeVQ2 = new TH1D(Form("h25MeVQ2_mode%d", mode), Form("Q2 for Mode==%d;Q2 (GeV^2);Events", mode), 20, 0, 2);

    // Repeat for PISNu energy
    TH1D *hBeforePISNu = new TH1D(Form("hBeforePISNu_mode%d", mode), Form("Energy PISNu for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);
    TH1D *h10MeVPISNu = new TH1D(Form("h10MeVPISNu_mode%d", mode), Form("Energy PISNu for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);
    TH1D *h25MeVPISNu = new TH1D(Form("h25MeVPISNu_mode%d", mode), Form("Energy PISNu for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);

    // Repeat for PISNu energy
    TH1D *hBeforeResEb = new TH1D(Form("hBeforeResEb_mode%d", mode), Form("ResEb  for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);
    TH1D *h10MeVResEb  = new TH1D(Form("h10MeVResEb_mode%d", mode), Form("ResEb  for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);
    TH1D *h25MeVResEb  = new TH1D(Form("h25MeVResEb_mode%d", mode), Form("ResEb  for Mode==%d;Energy (GeV);Events", mode), 20, 0, 2);

    // Loop over entries in each file for the current mode (no Eb)
    for (int i = 0; i < treeBefore->GetEntries(); ++i) {
        treeBefore->GetEntry(i);
        if (Mode == mode) {
            hBefore->Fill(PFSLep->Vect().Mag(), weight);
            hBeforePi->Fill(PHMFSCPi->Vect().Mag(), weight);
            hBeforeQ2->Fill(Q2, weight);
            hBeforePISNu->Fill(PISNu->E(), weight);

            hBeforeResEb->Fill(calculateResEb(PISNu->E(), Q2, W, PFSLep->E()), weight);
        }
    }

    // Loop over entries in the +Eb=10MeV file
    tree10MeV->SetBranchAddress("PFSLep", &PFSLep);
    tree10MeV->SetBranchAddress("PHMFSCPi", &PHMFSCPi);
    tree10MeV->SetBranchAddress("Q2", &Q2);
    tree10MeV->SetBranchAddress("Mode", &Mode);
    tree10MeV->SetBranchAddress("weight", &weight);
    tree10MeV->SetBranchAddress("PISNu", &PISNu);

    for (int i = 0; i < tree10MeV->GetEntries(); ++i) {
        tree10MeV->GetEntry(i);
        if (Mode == mode) {
            h10MeV->Fill(PFSLep->Vect().Mag(), weight);
            h10MeVPi->Fill(PHMFSCPi->Vect().Mag(), weight);
            h10MeVQ2->Fill(Q2, weight);
            h10MeVPISNu->Fill(PISNu->E(), weight);

            h10MeVResEb->Fill(calculateResEb(PISNu->E(), Q2, W, PFSLep->E()), weight);
        }
    }

    // Loop over entries in the +Eb=25MeV file
    tree25MeV->SetBranchAddress("PFSLep", &PFSLep);
    tree25MeV->SetBranchAddress("PHMFSCPi", &PHMFSCPi);
    tree25MeV->SetBranchAddress("Q2", &Q2);
    tree25MeV->SetBranchAddress("Mode", &Mode);
    tree25MeV->SetBranchAddress("weight", &weight);
    tree25MeV->SetBranchAddress("PISNu", &PISNu);

    for (int i = 0; i < tree25MeV->GetEntries(); ++i) {
        tree25MeV->GetEntry(i);
        if (Mode == mode) {
            h25MeV->Fill(PFSLep->Vect().Mag(), weight);
            h25MeVPi->Fill(PHMFSCPi->Vect().Mag(), weight);
            h25MeVQ2->Fill(Q2, weight);
            h25MeVPISNu->Fill(PISNu->E(), weight);

            h25MeVResEb->Fill(calculateResEb(PISNu->E(), Q2, W, PFSLep->E()), weight);
        }
    }

    // Plotting all histograms
    TCanvas *c1 = new TCanvas(Form("c1_mode%d", mode), Form("Comparison for Mode %d", mode), 800, 600);
    c1->SaveAs(Form("comparison_mode%d.pdf[", mode));  // Start PDF

    // PFSLep momentum
    hBefore->SetLineColor(kRed);
    h10MeV->SetLineColor(kBlue);
    h25MeV->SetLineColor(kGreen);
    hBefore->SetMaximum(hBefore->GetMaximum() * 1.5);
    hBefore->Draw("hist");
    h10MeV->Draw("hist same");
    h25MeV->Draw("hist same");

    TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    legend->AddEntry(hBefore, "No Eb", "l");
    legend->AddEntry(h10MeV, "+Eb=10MeV", "l");
    legend->AddEntry(h25MeV, "+Eb=25MeV", "l");
    legend->Draw();
    c1->SaveAs(Form("comparison_mode%d.pdf", mode));  // Save page for PFSLep

    // PHMFSCPi momentum
    hBeforePi->SetLineColor(kRed);
    h10MeVPi->SetLineColor(kBlue);
    h25MeVPi->SetLineColor(kGreen);
    hBeforePi->SetMaximum(hBeforePi->GetMaximum() * 1.5);
    hBeforePi->Draw("hist");
    h10MeVPi->Draw("hist same");
    h25MeVPi->Draw("hist same");

    legend->Draw();
    c1->SaveAs(Form("comparison_mode%d.pdf", mode));  // Save page for PHMFSCPi

    // Q2
    hBeforeQ2->SetLineColor(kRed);
    h10MeVQ2->SetLineColor(kBlue);
    h25MeVQ2->SetLineColor(kGreen);
    hBeforeQ2->SetMaximum(hBeforeQ2->GetMaximum() * 1.5);
    hBeforeQ2->Draw("hist");
    h10MeVQ2->Draw("hist same");
    h25MeVQ2->Draw("hist same");

    legend->Draw();
    c1->SaveAs(Form("comparison_mode%d.pdf", mode));  // Save page for Q2

    // PISNu energy
    hBeforePISNu->SetLineColor(kRed);
    h10MeVPISNu->SetLineColor(kBlue);
    h25MeVPISNu->SetLineColor(kGreen);
    hBeforePISNu->SetMaximum(hBeforePISNu->GetMaximum() * 1.5);
    hBeforePISNu->Draw("hist");
    h10MeVPISNu->Draw("hist same");
    h25MeVPISNu->Draw("hist same");

    legend->Draw();

    c1->SaveAs(Form("comparison_mode%d.pdf", mode));  // Save page for Enu

    hBeforeResEb->SetLineColor(kRed);
    h10MeVResEb->SetLineColor(kBlue);
    h25MeVResEb->SetLineColor(kGreen);
    hBeforeResEb->SetMaximum(hBeforePISNu->GetMaximum() * 1.5);
    hBeforeResEb->Draw("hist");
    h10MeVResEb->Draw("hist same");
    h25MeVResEb->Draw("hist same");

    legend->Draw();

    c1->SaveAs(Form("comparison_mode%d.pdf", mode));  // Save page for Enu


    c1->SaveAs(Form("comparison_mode%d.pdf]", mode)); //end PDF

    // Cleanup
    delete c1;
    delete hBefore;
    delete h10MeV;
    delete h25MeV;
    delete hBeforePi;
    delete h10MeVPi;
    delete h25MeVPi;
    delete hBeforeQ2;
    delete h10MeVQ2;
    delete h25MeVQ2;
    delete hBeforePISNu;
    delete h10MeVPISNu;
    delete h25MeVPISNu;
}

void compareFiles() {
    // Open the files
    TFile *fileNoEb = TFile::Open("flat_t2kflux_numu_C_0MeV.root");
    TFile *fileEb10MeV = TFile::Open("flat_t2kflux_numu_C_10MeV.root");
    TFile *fileEb25MeV = TFile::Open("flat_t2kflux_numu_C_25MeV.root");

    // Get the T2KRWFlatTree tree from each file
    TTree *treeNoEb = (TTree*)fileNoEb->Get("T2KRWFlatTree");
    TTree *treeEb10MeV = (TTree*)fileEb10MeV->Get("T2KRWFlatTree");
    TTree *treeEb25MeV = (TTree*)fileEb25MeV->Get("T2KRWFlatTree");

    // Create histograms for each mode
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 11);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 12);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 13);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 31);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 32);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 33);
    createHistograms(treeNoEb, treeEb10MeV, treeEb25MeV, 34);

    // Cleanup
    fileNoEb->Close();
    fileEb10MeV->Close();
    fileEb25MeV->Close();
}
