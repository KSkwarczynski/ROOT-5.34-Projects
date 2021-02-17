void SplineReweight() {
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    
    TFile *file = new TFile("run4.root");
    TTree *tree = (TTree*)file->Get("sample_sum");

    int nentries = tree->GetEntries();

    std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<nentries<<std::endl;
    
    TObjArray *Shape_2p2h;
    TObjArray *PNNN_shape;
    
    
    const int nPsycheSamples = 89; //WARNING hardcoded
    int mode_a    [nPsycheSamples];
    int target_a    [nPsycheSamples];
      
    int pn_pair_a  [nPsycheSamples];
    int nn_pair_a  [nPsycheSamples];
  
    double Enu  [nPsycheSamples];
    double TruePmu  [nPsycheSamples];
    double TrueCosThetamu  [nPsycheSamples];
    
    
    double PprotPrimary  [nPsycheSamples];
    double CosThetaProtPrimary  [nPsycheSamples];
    
    double Pprot  [nPsycheSamples];
    double CosThetaProt  [nPsycheSamples];
    
    tree->SetBranchStatus( "ReactionCode", true);
    tree->SetBranchAddress("ReactionCode",     &(mode_a));

    tree->SetBranchStatus( "TgtMat", true);
    tree->SetBranchAddress("TgtMat",     &(target_a));
    
    tree->SetBranchStatus( "pn_pair", true);
    tree->SetBranchAddress("pn_pair",   &pn_pair_a);

    tree->SetBranchStatus( "nn_pair", true);
    tree->SetBranchAddress("nn_pair",   &nn_pair_a);
        
    
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
    
    
    
    tree->SetBranchAddress("PDD_CGraph", &Shape_2p2h);
    tree->SetBranchAddress("PNNN_ShapeGraph", &PNNN_shape);
    
    const int BINmom = 24;
    const int BINCos = 21;
    const double MomentumEdges[BINmom] = {0, 100, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1500, 2000};
    const double CosEdges[BINCos] = {-1, -0.8, -0.5, -0.2, 0.0, 0.2, 0.3, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.95, 0.96, 0.98, 1.};
    

    TH2F *transfer2p2h_m1 = new TH2F("transfer2p2h_m1", "2p2h Shape_2p2h==-1", 40, 0, 1.4, 40, 0, 1.4);
    transfer2p2h_m1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfer2p2h_m1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transfer2p2h_0 = new TH2F("transfer2p2h_0", "2p2h Shape_2p2h==0", 40, 0, 1.4, 40, 0, 1.4);
    transfer2p2h_0->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfer2p2h_0->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transfer2p2h_1 = new TH2F("transfer2p2h_1", "2p2h Shape_2p2h==1", 40, 0, 1.4, 40, 0, 1.4);
    transfer2p2h_1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfer2p2h_1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    
        
    TH2F *transferpn_m1 = new TH2F("transferpn_m1", "pn Shape_2p2h==-1", 40, 0, 1.4, 40, 0, 1.4);
    transferpn_m1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transferpn_m1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transferpn_0 = new TH2F("transferpn_0", "pn Shape_2p2h==0", 40, 0, 1.4, 40, 0, 1.4);
    transferpn_0->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transferpn_0->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transferpn_1 = new TH2F("transferpn_1", "pn Shape_2p2h==1", 40, 0, 1.4, 40, 0, 1.4);
    transferpn_1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transferpn_1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    
    TH2F *transfernn_m1 = new TH2F("transfernn_m1", "nn Shape_2p2h==-1", 40, 0, 1.4, 40, 0, 1.4);
    transfernn_m1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfernn_m1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transfernn_0 = new TH2F("transfernn_0", "nn Shape_2p2h==0", 40, 0, 1.4, 40, 0, 1.4);
    transfernn_0->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfernn_0->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *transfernn_1 = new TH2F("transfernn_1", "nn Shape_2p2h==1", 40, 0, 1.4, 40, 0, 1.4);
    transfernn_1->GetXaxis()->SetTitle("True q_{3} [GeV]");
    transfernn_1->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    
    TH1F *MuMomentumpn_m1_Shape = new TH1F("MuMomentumpn_m1_Shape","Shape_2p2h==-1", 20, 0, 1.4);
    MuMomentumpn_m1_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumpn_0_Shape = new TH1F("MuMomentumpn_0_Shape","Shape_2p2h==0", 20, 0, 1.4);
    MuMomentumpn_0_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumpn_1_Shape = new TH1F("MuMomentumpn_1_Shape","Shape_2p2h==1", 20, 0, 1.4);
    MuMomentumpn_1_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_m1_Shape = new TH1F("MuMomentumnn_m1_Shape","Shape_2p2h==1", 20, 0, 1.4);
    MuMomentumnn_m1_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_0_Shape = new TH1F("MuMomentumnn_0_Shape","Shape_2p2h==0", 20, 0, 1.4);
    MuMomentumnn_0_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_1_Shape = new TH1F("MuMomentumnn_1_Shape","Shape_2p2h==1", 20, 0, 1.4);
    MuMomentumnn_1_Shape->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    
    
        
    TH2F *PrimaryProt2p2h_m1_Shape = new TH2F("PrimaryProt2p2h_m1_Shape","2p2h, Primary, Shape_2p2h==-1", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_m1_Shape->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_m1_Shape->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_0_Shape = new TH2F("PrimaryProt2p2h_0_Shape","2p2h, Primary, Shape_2p2h==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_0_Shape->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_0_Shape->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_1_Shape = new TH2F("PrimaryProt2p2h_1_Shape","2p2h, Primary, Shape_2p2h==1", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_1_Shape->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_1_Shape->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    
    
    TH2F *PNNNtransfer2p2h_m06 = new TH2F("PNNNtransfer2p2h_m06", "2p2h PNNN_shape==-0.6", 40, 0, 1.4, 40, 0, 1.4);
    PNNNtransfer2p2h_m06->GetXaxis()->SetTitle("True q_{3} [GeV]");
    PNNNtransfer2p2h_m06->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *PNNNtransfer2p2h_0 = new TH2F("PNNNtransfer2p2h_0", "2p2h PNNN_shape==0", 40, 0, 1.4, 40, 0, 1.4);
    PNNNtransfer2p2h_0->GetXaxis()->SetTitle("True q_{3} [GeV]");
    PNNNtransfer2p2h_0->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    TH2F *PNNNtransfer2p2h_06 = new TH2F("PNNNtransfer2p2h_06", "2p2h PNNN_shape==0.6", 40, 0, 1.4, 40, 0, 1.4);
    PNNNtransfer2p2h_06->GetXaxis()->SetTitle("True q_{3} [GeV]");
    PNNNtransfer2p2h_06->GetYaxis()->SetTitle("True q_{0} [GeV]");
    
    

    
    TH2F *PrimaryProt2p2h_m06 = new TH2F("PrimaryProt2p2h_m06","2p2h, Primary,PNNN_shape==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_0 = new TH2F("PrimaryProt2p2h_0","2p2h, Primary, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PrimaryProt2p2h_06 = new TH2F("PrimaryProt2p2h_06","2p2h, Primary, PNNN_shape==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProt2p2h_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProt2p2h_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    TH2F *PrimaryProtpn_0 = new TH2F("PrimaryProtpn_0","pn, Primary, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtpn_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtpn_0->GetYaxis()->SetTitle("Proton Cos#theta");
      
    TH2F *PrimaryProtnn_0 = new TH2F("PrimaryProtnn_0","nn, Primary, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PrimaryProtnn_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PrimaryProtnn_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
   
    TH2F *PostProt2p2h_m06 = new TH2F("PostProt2p2h_m06","2p2h, Post,PNNN_shape==-0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_m06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_m06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProt2p2h_0 = new TH2F("PostProt2p2h_0","2p2h, Post, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH2F *PostProt2p2h_06 = new TH2F("PostProt2p2h_06","2p2h, Post, PNNN_shape==0.6", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProt2p2h_06->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProt2p2h_06->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    TH2F *PostProtpn_0 = new TH2F("PostProtpn_0","pn, Post, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtpn_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtpn_0->GetYaxis()->SetTitle("Proton Cos#theta");
      
    TH2F *PostProtnn_0 = new TH2F("PostProtnn_0","nn, Post, PNNN_shape==0", BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    PostProtnn_0->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    PostProtnn_0->GetYaxis()->SetTitle("Proton Cos#theta");
    
    
    
    TH1F *MuMomentumpn_m06 = new TH1F("MuMomentumpn_m06","PNNN_shape==-0.6", 20, 0, 1.4);
    MuMomentumpn_m06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumpn_0 = new TH1F("MuMomentumpn_0","PNNN_shape==0", 20, 0, 1.4);
    MuMomentumpn_0->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumpn_06 = new TH1F("MuMomentumpn_06","PNNN_shape==0.6", 20, 0, 1.4);
    MuMomentumpn_06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_m06 = new TH1F("MuMomentumnn_m06","PNNN_shape==-0.6", 20, 0, 1.4);
    MuMomentumnn_m06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_0 = new TH1F("MuMomentumnn_0","PNNN_shape==0", 20, 0, 1.4);
    MuMomentumnn_0->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    TH1F *MuMomentumnn_06 = new TH1F("MuMomentumnn_06","PNNN_shape==0.6", 20, 0, 1.4);
    MuMomentumnn_06->GetXaxis()->SetTitle("Muon momentum (GeV)");
    
    
    

    
    
    int count2p2h = 0;
    int countpn = 0;
    int countnn = 0;
    double muon_mass = 0.105658;
    for (int i = 0; i < nentries; ++i) {
    //for (int i = 0; i < 20000; ++i) {
        tree->GetEntry(i);

        TGraph *graph2p2h = (TGraph*)(Shape_2p2h->At(0));
        TGraph *graphPNNN = (TGraph*)(PNNN_shape->At(0));
        
        double q3 = sqrt(Enu[0]*Enu[0] + TruePmu[0]*TruePmu[0] - 2*Enu[0]*TruePmu[0]*TrueCosThetamu[0]);
        
        double Emu = sqrt(TruePmu[0]*TruePmu[0] + 0.105*0.105);
        double q0 = fabs(Enu[0]-sqrt(TruePmu[0]*TruePmu[0] + muon_mass*muon_mass));
        
        double weight = 1.;
        
        if(pn_pair_a[0] == 1)
        {
            countpn++; 
        }
        if(nn_pair_a[0] == 1)
        {
            countnn++; 
        }
        
        if(mode_a[0]==2)
        {
            count2p2h++;
            weight = graph2p2h->Eval(-1);
            transfer2p2h_m1->Fill(q3, q0, weight);
            PrimaryProt2p2h_m1_Shape->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            if(pn_pair_a[0] == 1)
            {
                transferpn_m1->Fill(q3, q0, weight);  
                MuMomentumpn_m1_Shape->Fill(TruePmu[0], weight);
            }
            if(nn_pair_a[0] == 1)
            {
                transfernn_m1->Fill(q3, q0, weight); 
                MuMomentumnn_m1_Shape->Fill(TruePmu[0], weight);
            }
            
            
            weight = graph2p2h->Eval(0);
            transfer2p2h_0->Fill(q3, q0, weight);
            PrimaryProt2p2h_0_Shape->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            if(pn_pair_a[0] == 1)
            {
                transferpn_0->Fill(q3, q0, weight);
                MuMomentumpn_0_Shape->Fill(TruePmu[0], weight);
            }
            if(nn_pair_a[0] == 1)
            {
                transfernn_0->Fill(q3, q0, weight); 
                MuMomentumnn_0_Shape->Fill(TruePmu[0], weight);
            }
            
            weight = graph2p2h->Eval(1);
            transfer2p2h_1->Fill(q3, q0, weight);
            PrimaryProt2p2h_1_Shape->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            if(pn_pair_a[0] == 1)
            {
                transferpn_1->Fill(q3, q0, weight); 
                MuMomentumpn_1_Shape->Fill(TruePmu[0], weight);
            }
            if(nn_pair_a[0] == 1)
            {
                transfernn_1->Fill(q3, q0, weight);  
                MuMomentumnn_1_Shape->Fill(TruePmu[0], weight);
            }
        }
        
        if(mode_a[0]==2)
        {
            weight = graphPNNN->Eval(-0.6);
            PNNNtransfer2p2h_m06->Fill(q3, q0, weight); 
            PrimaryProt2p2h_m06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_m06->Fill(Pprot[0], CosThetaProt[0], weight);
            
        
            weight = graphPNNN->Eval(0.0);
            PNNNtransfer2p2h_0->Fill(q3, q0, weight);
            PrimaryProt2p2h_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_0->Fill(Pprot[0], CosThetaProt[0], weight);
                        
            if(pn_pair_a[0] == 1)
            {
                PrimaryProtpn_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight); 
                PostProtpn_0->Fill(Pprot[0], CosThetaProt[0], weight); 
            }
            if(nn_pair_a[0] == 1)
            {
                PrimaryProtnn_0->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
                PostProtnn_0->Fill(Pprot[0], CosThetaProt[0], weight);
            }
            
            weight = graphPNNN->Eval(0.6);
            PNNNtransfer2p2h_06->Fill(q3, q0, weight);
            PrimaryProt2p2h_06->Fill(PprotPrimary[0], CosThetaProtPrimary[0], weight);
            PostProt2p2h_06->Fill(Pprot[0], CosThetaProt[0], weight);
        }
        
        if(pn_pair_a[0] == 1)
        {
            weight = graphPNNN->Eval(-0.6);
            MuMomentumpn_m06->Fill(TruePmu[0], weight);
            
            weight = graphPNNN->Eval(0.0);
            MuMomentumpn_0->Fill(TruePmu[0], weight);
            
            weight = graphPNNN->Eval(0.6);
            MuMomentumpn_06->Fill(TruePmu[0], weight);
        }
        
        if(nn_pair_a[0] == 1)
        {
            weight = graphPNNN->Eval(-0.6);
            MuMomentumnn_m06->Fill(TruePmu[0], weight);
            
            weight = graphPNNN->Eval(0.0);
            MuMomentumnn_0->Fill(TruePmu[0], weight);
            
            weight = graphPNNN->Eval(0.6);
            MuMomentumnn_06->Fill(TruePmu[0], weight);
        }
        
    }
    
    TH2F *h1 = (TH2F*)(PostProt2p2h_m06->Clone("h1"));
    h1->SetTitle("PNNN_shape==-0.6 minus PNNN_shape==0.6");
    //h1->Divide(PostProt2p2h_06);
    h1->Add(PostProt2p2h_06,-1);
    
    
    c1->Print("Reweight.pdf[");
    
    transfer2p2h_m1->Draw("COLZ");
    c1->Print("Reweight.pdf");
      
    transfer2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    transfer2p2h_1->Draw("COLZ");
    c1->Print("Reweight.pdf");

    
    transferpn_m1->Draw("COLZ");
    c1->Print("Reweight.pdf");
      
    transferpn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    transferpn_1->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    transfernn_m1->Draw("COLZ");
    c1->Print("Reweight.pdf");
      
    transfernn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    transfernn_1->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PrimaryProt2p2h_m1_Shape->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    PrimaryProt2p2h_0_Shape->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProt2p2h_1_Shape->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    
    MuMomentumpn_m1_Shape->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_m1_Shape->SetLineColorAlpha(kBlue, 1);
        
   
    MuMomentumpn_m1_Shape->Draw("");
    MuMomentumnn_m1_Shape->Draw("SAME");

     
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_m1_Shape, "pn","l");
    legend->AddEntry(MuMomentumnn_m1_Shape,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");        
        
    MuMomentumpn_0_Shape->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_0_Shape->SetLineColorAlpha(kBlue, 1);
        
    MuMomentumpn_0_Shape->Draw("");
    MuMomentumnn_0_Shape->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_0_Shape, "pn","l");
    legend->AddEntry(MuMomentumnn_0_Shape,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
        
       
    
    MuMomentumpn_1_Shape->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_1_Shape->SetLineColorAlpha(kBlue, 1);
        
    MuMomentumpn_1_Shape->Draw("");
    MuMomentumnn_1_Shape->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_1_Shape, "pn","l");
    legend->AddEntry(MuMomentumnn_1_Shape,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
    
    
    
    
    
    
    PNNNtransfer2p2h_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
      
    PNNNtransfer2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    PNNNtransfer2p2h_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    
    PrimaryProtpn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    PrimaryProtnn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PrimaryProt2p2h_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProt2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PrimaryProt2p2h_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    
    
    PostProtpn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    PostProtnn_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    PostProt2p2h_m06->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProt2p2h_0->Draw("COLZ");
    c1->Print("Reweight.pdf");
        
    PostProt2p2h_06->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    MuMomentumpn_m06->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_m06->SetLineColorAlpha(kBlue, 1);
        
   
    MuMomentumnn_m06->Draw("");
    MuMomentumpn_m06->Draw("SAME");
     
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_m06, "pn","l");
    legend->AddEntry(MuMomentumnn_m06,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
        
        
    MuMomentumpn_0->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_0->SetLineColorAlpha(kBlue, 1);
        
    MuMomentumpn_0->Draw("");
    MuMomentumnn_0->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_0, "pn","l");
    legend->AddEntry(MuMomentumnn_0,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
        
       
    
    MuMomentumpn_06->SetLineColorAlpha(kRed, 1);
    MuMomentumnn_06->SetLineColorAlpha(kBlue, 1);
        
    MuMomentumpn_06->Draw("");
    MuMomentumnn_06->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumpn_06, "pn","l");
    legend->AddEntry(MuMomentumnn_06,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print("Reweight.pdf");
    
    
    gStyle->SetPalette(1); //WARNING
//     h1->Draw("COLZ");
    c1->Print("Reweight.pdf");
    
    
    c1->Print("Reweight.pdf]");
    
    
    std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
    std::cout<< "\033[1;31m 2p2h counter \033[0m "<<count2p2h<<std::endl;
    std::cout<< "\033[1;31m pn pair counter \033[0m "<<countpn<<std::endl;
    std::cout<< "\033[1;31m nn pair counter \033[0m "<<countnn<<std::endl;
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
