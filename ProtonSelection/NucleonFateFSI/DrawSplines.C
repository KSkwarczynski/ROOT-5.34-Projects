void DrawSplines() {
  TFile *file = new TFile("Newrun4aMCsplines_001.root");
  TTree *tree = (TTree*)file->Get("sample_sum");
  int nentries = tree->GetEntries();
  TObjArray *MAQE;
  TObjArray *PDD_C;
  TObjArray *CA5;
  TObjArray *nucleonFateFSI;
  
  int sample;
  //tree->SetBranchStatus("*", false);
  //tree->SetBranchStatus("FSI_PI_ABSGraph", true);
  //tree->SetBranchStatus("SelectedSample", true);
  //tree->SetBranchAddress("FSI_PI_ABSGraph", &blarb);
  //tree->SetBranchAddress("SelectedSample", &sample);
  
    tree->SetBranchAddress("MAQEGraph", &MAQE);
    tree->SetBranchAddress("PDD_CGraph", &PDD_C);
    tree->SetBranchAddress("CA5Graph", &CA5);
    tree->SetBranchAddress("nucleonFateFSIGraph", &nucleonFateFSI);
            
    tree->SetBranchAddress("SelectedSample", &sample);
  
  TCanvas *canv = new TCanvas("canv", "canv", 1024, 1024);
  canv->Print("asdf.pdf[");
  int count = 0;
  for (int i = 0; i < nentries; ++i) {
  //for (int i = 0; i < 10; ++i) {
    tree->GetEntry(i);
    //TGraph *graph = (TGraph*)(blarb->At(sample));
    TGraph *graphMAQE = (TGraph*)(MAQE->At(0));
    TGraph *graphPDD_CGraph = (TGraph*)(PDD_C->At(0));
    TGraph *graphCA5 = (TGraph*)(CA5->At(0));
    TGraph *graphnucleonFateFSI = (TGraph*)(nucleonFateFSI->At(0));
    
    //if (graph->GetN() == 1) continue;
    count++;
    canv->Clear();
    canv->Divide(2,2);
    canv->cd(1);
    graphMAQE->SetTitle(Form("MAQE - Event %i", i));
    graphMAQE->GetYaxis()->SetTitle("weight");
    graphMAQE->GetXaxis()->SetTitle("parameter variation");
    graphMAQE->Draw();
    
    canv->cd(2);
    graphPDD_CGraph->SetTitle(Form("PDD_C - Event %i", i));
    graphPDD_CGraph->GetYaxis()->SetTitle("weight");
    graphPDD_CGraph->GetXaxis()->SetTitle("parameter variation");
    graphPDD_CGraph->Draw();
    
    canv->cd(3);
    graphCA5->SetTitle(Form("CA5 - Event %i", i));
    graphCA5->GetYaxis()->SetTitle("weight");
    graphCA5->GetXaxis()->SetTitle("parameter variation");
    graphCA5->Draw();
    
    canv->cd(4);
    graphnucleonFateFSI->SetTitle(Form("nucleon FSI - Event %i", i));
    graphnucleonFateFSI->GetYaxis()->SetTitle("weight");
    graphnucleonFateFSI->GetXaxis()->SetTitle("parameter variation");
    graphnucleonFateFSI->Draw();

    
    
    canv->Print("asdf.pdf");
  }
  std::cout << "Found " << count << " graphs" << std::endl;
  canv->Print("asdf.pdf]");
}
