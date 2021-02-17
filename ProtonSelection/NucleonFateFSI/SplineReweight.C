void SplineReweight() {
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    
    TFile *file = new TFile("run4.root");
    TTree *tree = (TTree*)file->Get("sample_sum");

    int nentries = tree->GetEntries();
    
    std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<nentries<<std::endl;
        
    TObjArray *nucleonFateFSI;
    
    
    const int nPsycheSamples = 89; //WARNING hardcoded
    int mode_a    [nPsycheSamples];
  
  
    double Enu  [nPsycheSamples];
    double TruePmu  [nPsycheSamples];
    double TrueCosThetamu  [nPsycheSamples];
    
    
    double PprotPrimary  [nPsycheSamples];
    double CosThetaProtPrimary  [nPsycheSamples];
    
    double Pprot  [nPsycheSamples];
    double CosThetaProt  [nPsycheSamples];
    
    tree->SetBranchStatus( "ReactionCode", true);
    tree->SetBranchAddress("ReactionCode",     &(mode_a));        
    
    tree->SetBranchStatus( "Enu", true);
    tree->SetBranchAddress("Enu",   &Enu);
    
    tree->SetBranchStatus( "TruePmu", true);
    tree->SetBranchAddress("TruePmu",   &TruePmu);
    
    tree->SetBranchStatus( "TrueCosThetamu", true);
    tree->SetBranchAddress("TrueCosThetamu",   &TrueCosThetamu);
    
    tree->SetBranchStatus( "PprotPrimary", true);
    tree->SetBranchAddress("PprotPrimary",   &PprotPrimary);
    
    tree->SetBranchStatus( "CosThetaProtPrimary", true);
    tree->SetBranchAddress("CosThetaProtPrimary",   &CosThetaProtPrimary);
    
    tree->SetBranchStatus( "Pprot", true);
    tree->SetBranchAddress("Pprot",   &Pprot);
    
    tree->SetBranchStatus( "CosThetaProt", true);
    tree->SetBranchAddress("CosThetaProt",   &CosThetaProt);
    
    
    tree->SetBranchAddress("nucleonFateFSIGraph", &nucleonFateFSI);
    
    
    const int BINmom = 24;
    const int BINCos = 21;
    const double MomentumEdges[BINmom] = {0, 100, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1500, 2000};
    const double CosEdges[BINCos] = {-1, -0.8, -0.5, -0.2, 0.0, 0.2, 0.3, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.95, 0.96, 0.98, 1.};

    
    TH2F *PrimaryProtCCQE_m06 = new TH2F("PrimaryProtCCQE_m06","CCQE, Primary,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtCCQE_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtCCQE_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProtCCQE_0 = new TH2F("PrimaryProtCCQE_0","CCQE, Primary, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtCCQE_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtCCQE_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProtCCQE_06 = new TH2F("PrimaryProtCCQE_06","CCQE, Primary, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtCCQE_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtCCQE_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
   
    TH2F *PostProtCCQE_m06 = new TH2F("PostProtCCQE_m06","CCQE, Post,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtCCQE_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtCCQE_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProtCCQE_0 = new TH2F("PostProtCCQE_0","CCQE, Post, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtCCQE_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtCCQE_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProtCCQE_06 = new TH2F("PostProtCCQE_06","CCQE, Post, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtCCQE_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtCCQE_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    
    
    TH2F *PrimaryProt2p2h_m06 = new TH2F("PrimaryProt2p2h_m06","2p2h, Primary,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_0 = new TH2F("PrimaryProt2p2h_0","2p2h, Primary, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_06 = new TH2F("PrimaryProt2p2h_06","2p2h, Primary, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
   
    TH2F *PostProt2p2h_m06 = new TH2F("PostProt2p2h_m06","2p2h, Post,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProt2p2h_0 = new TH2F("PostProt2p2h_0","2p2h, Post, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProt2p2h_06 = new TH2F("PostProt2p2h_06","2p2h, Post, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    
    TH2F *PrimaryProtRES_m06 = new TH2F("PrimaryProtRES_m06","RES, Primary,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtRES_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtRES_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProtRES_0 = new TH2F("PrimaryProtRES_0","RES, Primary, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtRES_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtRES_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProtRES_06 = new TH2F("PrimaryProtRES_06","RES, Primary, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtRES_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtRES_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
   
    TH2F *PostProtRES_m06 = new TH2F("PostProtRES_m06","RES, Post,NucleonFSI==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtRES_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtRES_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProtRES_0 = new TH2F("PostProtRES_0","RES, Post, NucleonFSI==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtRES_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtRES_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProtRES_06 = new TH2F("PostProtRES_06","RES, Post, NucleonFSI==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtRES_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtRES_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    //TODO skoncz to kurde
    TH1F *MuMomentumCCQE_m06 = new TH1F("MuMomentumCCQE_m06","CCQE NucleonFSI==-0.6", 20, 0, 1.4);
    MuMomentumCCQE_m06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumCCQE_0 = new TH1F("MuMomentumCCQE_0","CCQE NucleonFSI==0", 20, 0, 1.4);
    MuMomentumCCQE_0->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumCCQE_06 = new TH1F("MuMomentumCCQE_06","CCQE NucleonFSI==0.6", 20, 0, 1.4);
    MuMomentumCCQE_06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentum2p2h_m06 = new TH1F("MuMomentum2p2h_m06","2p2h NucleonFSI==-0.6", 20, 0, 1.4);
    MuMomentum2p2h_m06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentum2p2h_0 = new TH1F("MuMomentum2p2h_0","2p2h NucleonFSI==0", 20, 0, 1.4);
    MuMomentum2p2h_0->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentum2p2h_06 = new TH1F("MuMomentum2p2h_06","2p2h NucleonFSI==0.6", 20, 0, 1.4);
    MuMomentum2p2h_06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumRES_m06 = new TH1F("MuMomentumRES_m06","RES NucleonFSI==-0.6", 20, 0, 1.4);
    MuMomentumRES_m06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumRES_0 = new TH1F("MuMomentumRES_0","RES NucleonFSI==0", 20, 0, 1.4);
    MuMomentumRES_0->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumRES_06 = new TH1F("MuMomentumRES_06","RES NucleonFSI==0.6", 20, 0, 1.4);
    MuMomentumRES_06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    for (int i = 0; i < nentries; ++i) {
    //for (int i = 0; i < 1000; ++i) {
        tree->GetEntry(i);

        TGraph *graphFSI = (TGraph*)(nucleonFateFSI->At(0));
        
        double weight = 1.;

        if(mode_a[0]==1)
        {
            weight = graphFSI->Eval(-0.6);
            PrimaryProtCCQE_m06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtCCQE_m06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumCCQE_m06->Fill(TruePmu[0], weight); 
                        
            weight = graphFSI->Eval(0.0);
            PrimaryProtCCQE_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtCCQE_0->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumCCQE_0->Fill(TruePmu[0], weight);         
                        
            weight = graphFSI->Eval(0.6);
            PrimaryProtCCQE_06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtCCQE_06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumCCQE_06->Fill(TruePmu[0], weight); 
        }
        
        
        if(mode_a[0]==2)
        {
            weight = graphFSI->Eval(-0.6);
            PrimaryProt2p2h_m06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_m06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentum2p2h_m06->Fill(TruePmu[0], weight); 
        
            weight = graphFSI->Eval(0.0);
            PrimaryProt2p2h_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_0->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentum2p2h_0->Fill(TruePmu[0], weight);      
            
            weight = graphFSI->Eval(0.6);
            PrimaryProt2p2h_06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentum2p2h_06->Fill(TruePmu[0], weight); 
        }
        
        if( (11<=mode_a[0]&&mode_a[0]<=13) || mode_a[0]==17 || mode_a[0]==22 || mode_a[0]==23)
        {
            weight = graphFSI->Eval(-0.6);
            PrimaryProtRES_m06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtRES_m06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumRES_m06->Fill(TruePmu[0], weight);  
        
            weight = graphFSI->Eval(0.0);
            PrimaryProtRES_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtRES_0->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumRES_0->Fill(TruePmu[0], weight);    
            
            weight = graphFSI->Eval(0.6);
            PrimaryProtRES_06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProtRES_06->Fill(Pprot[0], CosThetaProt[0], weight);
            MuMomentumRES_06->Fill(TruePmu[0], weight);
        }
        
        
        
        
        
    }
    
    TH2F *h1 = (TH2F*)(PostProtCCQE_m06->Clone("h1"));
    h1->SetTitle("CCQE NucleonFSI==-0.6 minus NucleonFSI==0.6");
    h1->Divide(PostProtCCQE_06);
    //h1->Add(PostProtCCQE_06,-1);
    
    
    c1->Print("Reweight.pdf[");
    
      
    PrimaryProtCCQE_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProtCCQE_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProtCCQE_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PostProtCCQE_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProtCCQE_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProtCCQE_06->Draw("COLZ");
    c1->Print("Reweight.pdf");  
    

    
    
    PrimaryProt2p2h_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProt2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProt2p2h_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PostProt2p2h_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProt2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProt2p2h_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PrimaryProtRES_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProtRES_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProtRES_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PostProtRES_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProtRES_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProtRES_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    
    
    MuMomentumCCQE_m06->SetLineColorAlpha(kRed, 1);
    MuMomentum2p2h_m06->SetLineColorAlpha(kViolet, 1);
    MuMomentumRES_m06->SetLineColorAlpha(kGreen, 1);
         
    MuMomentumCCQE_m06->Draw("");
    MuMomentum2p2h_m06->Draw("SAME");
    MuMomentumRES_m06->Draw("SAME");
        
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumCCQE_m06,"CCQE","l");
    legend->AddEntry(MuMomentum2p2h_m06,"2p2h","l");
    legend->AddEntry(MuMomentumRES_m06,"RES","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
    
    MuMomentumCCQE_0->SetLineColorAlpha(kRed, 1);
    MuMomentum2p2h_0->SetLineColorAlpha(kViolet, 1);
    MuMomentumRES_0->SetLineColorAlpha(kGreen, 1);
         
    MuMomentumCCQE_0->Draw("");
    MuMomentum2p2h_0->Draw("SAME");
    MuMomentumRES_0->Draw("SAME");
        
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumCCQE_0,"CCQE","l");
    legend->AddEntry(MuMomentum2p2h_0,"2p2h","l");
    legend->AddEntry(MuMomentumRES_0,"RES","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
    
       
    MuMomentumCCQE_06->SetLineColorAlpha(kRed, 1);
    MuMomentum2p2h_06->SetLineColorAlpha(kViolet, 1);
    MuMomentumRES_06->SetLineColorAlpha(kGreen, 1);
         
    MuMomentumCCQE_06->Draw("");
    MuMomentum2p2h_06->Draw("SAME");
    MuMomentumRES_06->Draw("SAME");
        
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumCCQE_06,"CCQE","l");
    legend->AddEntry(MuMomentum2p2h_06,"2p2h","l");
    legend->AddEntry(MuMomentumRES_06,"RES","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
    
       
    //gStyle->SetPalette(1); //WARNING
    h1->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
        
    c1->Print("Reweight.pdf]");
    
    std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
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
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadRightMargin(0.12); // 0.075 -> 0.13 for colz option
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
    
    gROOT->ForceStyle();    
}
