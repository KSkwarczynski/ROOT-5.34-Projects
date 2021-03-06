//WARNING This is terribly hardcoded

#include "/mnt/home/kskwarczynski/T2K/work/protonPlayground/psyche/psycheEventModel/v3r33/src/SampleId.hxx" 

using namespace std;

void EventSummaryAnalysis(TString fname)
{
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    bool DEBUGMODE=false;
    bool VERBOSE=true;
    
    TFile *file=TFile::Open( Form("%s", fname.Data() ) );
    TTree *tree;
    file->GetObject("mc_event_tree",tree);

//*******************************************************************************//      
   // Declaration of leaf types
   Int_t           SampleID;
   Int_t           BeamMode;
   Double_t        RecoMuonMomentum;
   Double_t        RecoPionMomentum;
   Double_t        RecoPionCosTheta;
   Int_t           PionTopology;
   Double_t        RecoProtonMomentum;
   Double_t        RecoProtonCosTheta;
   Int_t           ProtonTopology;
   Double_t        RecoMuonCosTheta;
   Double_t        ERec;
   Double_t        Q2Rec;
   Double_t        Q0Rec;
   Double_t        Q3Rec;
   Double_t        W2Rec;
   Double_t        ERec_NoEb;
   Double_t        Q2Rec_NoEb;
   Double_t        Q0Rec_NoEb;
   Double_t        Q3Rec_NoEb;
   Double_t        W2Rec_NoEb;
   Int_t           NThrows;
   Double_t        TotalWeight[1];   //[NThrows]
   Double_t        POTWeight;
   Double_t        FluxWeight[1];   //[NThrows]
   Double_t        DetWeight;
   Double_t        ObsWeight[1];   //[NThrows]
   Double_t        XSecWeight[1];   //[NThrows]
   Double_t        TrueEnu;
   Double_t        TrueQ2;
   Double_t        TrueQ0;
   Double_t        TrueQ3;
   Double_t        TrueW2;
   Double_t        TrueMuonMomentum;
   Double_t        TruePionMomentum;
   Double_t        TruePionCosTheta;
   Int_t           NTrueFinalStatePions;
   Double_t        TrueMuonCosTheta;
   Int_t           ReactionCode;
   Int_t           NuPDG;
   Int_t           TargetPDG;
   Double_t        fakeWeight;
   Int_t           FakeType;

   // List of branches
   TBranch        *b_SampleID;   //!
   TBranch        *b_BeamMode;   //!
   TBranch        *b_RecoMuonMomentum;   //!
   TBranch        *b_RecoPionMomentum;   //!
   TBranch        *b_RecoPionCosTheta;   //!
   TBranch        *b_PionTopology;   //!
   TBranch        *b_RecoProtonMomentum;   //!
   TBranch        *b_RecoProtonCosTheta;   //!
   TBranch        *b_ProtonTopology;   //!
   TBranch        *b_RecoMuonCosTheta;   //!
   TBranch        *b_ERec;   //!
   TBranch        *b_Q2Rec;   //!
   TBranch        *b_Q0Rec;   //!
   TBranch        *b_Q3Rec;   //!
   TBranch        *b_W2Rec;   //!
   TBranch        *b_ERec_NoEb;   //!
   TBranch        *b_Q2Rec_NoEb;   //!
   TBranch        *b_Q0Rec_NoEb;   //!
   TBranch        *b_Q3Rec_NoEb;   //!
   TBranch        *b_W2Rec_NoEb;   //!
   TBranch        *b_NThrows;   //!
   TBranch        *b_TotalWeight;   //!
   TBranch        *b_POTWeight;   //!
   TBranch        *b_FluxWeight;   //!
   TBranch        *b_DetWeight;   //!
   TBranch        *b_ObsWeight;   //!
   TBranch        *b_XSecWeight;   //!
   TBranch        *b_TrueEnu;   //!
   TBranch        *b_TrueQ2;   //!
   TBranch        *b_TrueQ0;   //!
   TBranch        *b_TrueQ3;   //!
   TBranch        *b_TrueW2;   //!
   TBranch        *b_TrueMuonMomentum;   //!
   TBranch        *b_TruePionMomentum;   //!
   TBranch        *b_TruePionCosTheta;   //!
   TBranch        *b_NTrueFinalStatePions;   //!
   TBranch        *b_TrueMuonCosTheta;   //!
   TBranch        *b_ReactionCode;   //!
   TBranch        *b_NuPDG;   //!
   TBranch        *b_TargetPDG;   //!
   TBranch        *b_fakeWeight;   //!
   TBranch        *b_FakeType;   //!
    
   tree->SetBranchAddress("SampleID", &SampleID, &b_SampleID);
   tree->SetBranchAddress("BeamMode", &BeamMode, &b_BeamMode);
   tree->SetBranchAddress("RecoMuonMomentum", &RecoMuonMomentum, &b_RecoMuonMomentum);
   tree->SetBranchAddress("RecoPionMomentum", &RecoPionMomentum, &b_RecoPionMomentum);
   tree->SetBranchAddress("RecoPionCosTheta", &RecoPionCosTheta, &b_RecoPionCosTheta);
   tree->SetBranchAddress("PionTopology", &PionTopology, &b_PionTopology);
   tree->SetBranchAddress("RecoProtonMomentum", &RecoProtonMomentum, &b_RecoProtonMomentum);
   tree->SetBranchAddress("RecoProtonCosTheta", &RecoProtonCosTheta, &b_RecoProtonCosTheta);
   tree->SetBranchAddress("ProtonTopology", &ProtonTopology, &b_ProtonTopology);
   tree->SetBranchAddress("RecoMuonCosTheta", &RecoMuonCosTheta, &b_RecoMuonCosTheta);
   tree->SetBranchAddress("ERec", &ERec, &b_ERec);
   tree->SetBranchAddress("Q2Rec", &Q2Rec, &b_Q2Rec);
   tree->SetBranchAddress("Q0Rec", &Q0Rec, &b_Q0Rec);
   tree->SetBranchAddress("Q3Rec", &Q3Rec, &b_Q3Rec);
   tree->SetBranchAddress("W2Rec", &W2Rec, &b_W2Rec);
   tree->SetBranchAddress("ERec_NoEb", &ERec_NoEb, &b_ERec_NoEb);
   tree->SetBranchAddress("Q2Rec_NoEb", &Q2Rec_NoEb, &b_Q2Rec_NoEb);
   tree->SetBranchAddress("Q0Rec_NoEb", &Q0Rec_NoEb, &b_Q0Rec_NoEb);
   tree->SetBranchAddress("Q3Rec_NoEb", &Q3Rec_NoEb, &b_Q3Rec_NoEb);
   tree->SetBranchAddress("W2Rec_NoEb", &W2Rec_NoEb, &b_W2Rec_NoEb);
   tree->SetBranchAddress("NThrows", &NThrows, &b_NThrows);
   tree->SetBranchAddress("TotalWeight", TotalWeight, &b_TotalWeight);
   tree->SetBranchAddress("POTWeight", &POTWeight, &b_POTWeight);
   tree->SetBranchAddress("FluxWeight", FluxWeight, &b_FluxWeight);
   tree->SetBranchAddress("DetWeight", &DetWeight, &b_DetWeight);
   tree->SetBranchAddress("ObsWeight", ObsWeight, &b_ObsWeight);
   tree->SetBranchAddress("XSecWeight", XSecWeight, &b_XSecWeight);
   tree->SetBranchAddress("TrueEnu", &TrueEnu, &b_TrueEnu);
   tree->SetBranchAddress("TrueQ2", &TrueQ2, &b_TrueQ2);
   tree->SetBranchAddress("TrueQ0", &TrueQ0, &b_TrueQ0);
   tree->SetBranchAddress("TrueQ3", &TrueQ3, &b_TrueQ3);
   tree->SetBranchAddress("TrueW2", &TrueW2, &b_TrueW2);
   tree->SetBranchAddress("TrueMuonMomentum", &TrueMuonMomentum, &b_TrueMuonMomentum);
   tree->SetBranchAddress("TruePionMomentum", &TruePionMomentum, &b_TruePionMomentum);
   tree->SetBranchAddress("TruePionCosTheta", &TruePionCosTheta, &b_TruePionCosTheta);
   tree->SetBranchAddress("NTrueFinalStatePions", &NTrueFinalStatePions, &b_NTrueFinalStatePions);
   tree->SetBranchAddress("TrueMuonCosTheta", &TrueMuonCosTheta, &b_TrueMuonCosTheta);
   tree->SetBranchAddress("ReactionCode", &ReactionCode, &b_ReactionCode);
   tree->SetBranchAddress("NuPDG", &NuPDG, &b_NuPDG);
   tree->SetBranchAddress("TargetPDG", &TargetPDG, &b_TargetPDG);
   tree->SetBranchAddress("fakeWeight", &fakeWeight, &b_fakeWeight);
   tree->SetBranchAddress("FakeType", &FakeType, &b_FakeType);

   
   
//*******************************************************************************//   
                
    int AllEvents = tree->GetEntries();
    
    if(VERBOSE) std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<AllEvents<<std::endl;
    
    if(DEBUGMODE) AllEvents=100;
    
    const int BIN0PI = 30;
    const double MomentumEdges[BIN0PI] = {0, 200, 300, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 2000, 2500, 3000, 5000, 30000.};
    const double CosEdges[BIN0PI] = {-1, 0.5, 0.6, 0.7, 0.76, 0.78, 0.8, 0.83, 0.85, 0.88, 0.89, 0.9, 0.91, 0.92, 0.925, 0.93, 0.935, 0.94, 0.945, 0.95, 0.955, 0.96, 0.965, 0.97, 0.975, 0.98, 0.985, 0.99, 0.995, 1.};
    
    const int BINPROTON = 12;
    const double MomentumEdgesProton[BINPROTON] = {0., 300., 450., 600., 800., 1000., 1250., 1500., 2000., 3000., 5000., 30000.};
    const double CosEdgesProton[BINPROTON] = {-1.0, 0.5, 0.6, 0.7, 0.75, 0.8, 0.85, 0.9, 0.92, 0.98, 0.99, 1.0};
    
    

    
    //int SelectionCC0Pi0p = SampleId::kFGD1NuMuCC0Pi;       //TODO
    //int SelectionCC0PiNp = SampleId::kFGD1NuMuCC0PiNp;      //TODO
    int SelectionCC0Pi0p = 3;
    int SelectionCC0PiNp = 89;
    int ReactionCode_CCQE = 1;
    int ReactionCode_2p2h = 2;
    
    if(VERBOSE) std::cout<< "\033[1;33mCC0Pi-0p selection number\033[0m " <<SelectionCC0Pi0p<<std::endl;
    if(VERBOSE) std::cout<< "\033[1;33mCC0Pi-Np selection number\033[0m " <<SelectionCC0PiNp<<std::endl;
    
    TH2F *hResolution_ZeroProt = new TH2F("hResolution_ZeroProt", "CC0Pi-0p", 50, 0, 1000, 50, 0, 1000);
    hResolution_ZeroProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    hResolution_ZeroProt->GetYaxis()->SetTitle("Reco P#mu (MeV/c)");
    
    TH1F *hRMS_ZeroProt = new TH1F("hRMS_ZeroProt", "CC0Pi-0p RMS", 50, 0, 1000);
    hRMS_ZeroProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    
    TH1F *hMeanRMS_ZeroProt = new TH1F("hMeanRMS_ZeroProt", "CC0Pi-0p Mean and RMS", 50, 0, 1000);
    hMeanRMS_ZeroProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    
    
    TH2F *hResolution_nProt = new TH2F("hResolution_nProt", "CC0Pi-Np", 50, 0, 1000, 50, 0, 1000);
    hResolution_nProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    hResolution_nProt->GetYaxis()->SetTitle("Reco P#mu (MeV/c)");
     
    TH1F *hRMS_nProt = new TH1F("hRMS_nProt", "CC0Pi-Np RMS", 50, 0, 1000);
    hRMS_nProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    
    TH1F *hMeanRMS_nProt = new TH1F("hMeanRMS_nProt", "CC0Pi-Np Mean and RMS", 50, 0, 1000);
    hMeanRMS_nProt->GetXaxis()->SetTitle("True P#mu (MeV/c)");
    
    
    TH2F *hResolution_ZeroProtAngle = new TH2F("hResolution_ZeroProtAngle", "CC0Pi-0p", 50, 0, 1, 50, 0, 1);
    hResolution_ZeroProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    hResolution_ZeroProtAngle->GetYaxis()->SetTitle("Reco Cos#theta#mu");
    
    TH1F *hRMS_ZeroProtAngle = new TH1F("hRMS_ZeroProtAngle", "CC0Pi-0p RMS", 50, 0, 1);
    hRMS_ZeroProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    
    TH1F *hMeanRMS_ZeroProtAngle = new TH1F("hMeanRMS_ZeroProtAngle", "CC0Pi-0p Mean and RMS", 50, 0, 1);
    hMeanRMS_ZeroProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    
    TH2F *hResolution_nProtAngle = new TH2F("hResolution_nProtAngle", "CC0Pi-Np", 50, 0, 1, 50, 0, 1);
    hResolution_nProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    hResolution_nProtAngle->GetYaxis()->SetTitle("Reco Cos#theta#mu");
    
    TH1F *hRMS_nProtAngle = new TH1F("hRMS_nProtAngle", "CC0Pi-Np RMS", 50, 0, 1);
    hRMS_ZeroProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    
    TH1F *hMeanRMS_nProtAngle = new TH1F("hMeanRMS_nProtAngle", "CC0Pi-Np Mean and RMS", 50, 0, 1);
    hMeanRMS_nProtAngle->GetXaxis()->SetTitle("True Cos#theta#mu");
    
    
    
    TH2F *hTransfer_ZeroProt_Reco = new TH2F("hTransfer_ZeroProt_Reco", "CC0Pi-0p nominal MC (2p2h only)", 50, 0, 1.4, 50, 0, 1.4);
    hTransfer_ZeroProt_Reco->GetXaxis()->SetTitle("reco q_{3} (GeV)");
    hTransfer_ZeroProt_Reco->GetYaxis()->SetTitle("reco q_{0} (GeV)");
    
    TH2F *hTransfer_nProt_Reco = new TH2F("hTransfer_nProt_Reco", "CC0Pi-Np nominal MC (2p2h only)", 50, 0, 1.4, 50, 0, 1.4);
    hTransfer_nProt_Reco->GetXaxis()->SetTitle("reco q_{3} (GeV)");
    hTransfer_nProt_Reco->GetYaxis()->SetTitle("reco q_{0} (GeV)");
    
    TH2F *hTransfer_ZeroProt_True = new TH2F("hTransfer_ZeroProt_True", "CC0Pi-0p nominal MC (2p2h only)", 50, 0, 1.4, 50, 0, 1.4);
    hTransfer_ZeroProt_True->GetXaxis()->SetTitle("true q_{3} (GeV)");
    hTransfer_ZeroProt_True->GetYaxis()->SetTitle("true q_{0} (GeV)");
    
    TH2F *hTransfer_nProt_True = new TH2F("hTransfer_nProt_True", "CC0Pi-Np nominal MC (2p2h only)", 50, 0, 1.4, 50, 0, 1.4);
    hTransfer_nProt_True->GetXaxis()->SetTitle("true q_{3} (GeV)");
    hTransfer_nProt_True->GetYaxis()->SetTitle("true q_{0} (GeV)");
    
    TH2F *hTransferAll_ZeroProt_True = new TH2F("hTransferAll_ZeroProt_True", "CC0Pi-0p nominal MC", 50, 0, 1.4, 50, 0, 1.4);
    hTransferAll_ZeroProt_True->GetXaxis()->SetTitle("true q_{3} (GeV)");
    hTransferAll_ZeroProt_True->GetYaxis()->SetTitle("true q_{0} (GeV)");
    
    TH2F *hTransferAll_nProt_True = new TH2F("hTransferAll_nProt_True", "CC0Pi-Np nominal MC", 50, 0, 1.4, 50, 0, 1.4);
    hTransferAll_nProt_True->GetXaxis()->SetTitle("true q_{3} (GeV)");
    hTransferAll_nProt_True->GetYaxis()->SetTitle("true q_{0} (GeV)");
    
    TH2F *hCC0Pi_0p = new TH2F("hCC0Pi_0p", "CC0Pi-0p nominal MC", BIN0PI-1 ,MomentumEdges, BIN0PI-1, CosEdges);
    hCC0Pi_0p->GetXaxis()->SetTitle("#mu^{-} candidate momentum [MeV/c]");
    hCC0Pi_0p->GetYaxis()->SetTitle("#mu^{-} candidate cos#theta");
    
    TH2F *hCC0Pi_Np = new TH2F("hCC0Pi_Np", "CC0Pi-Np nominal MC", BIN0PI-1 ,MomentumEdges, BIN0PI-1, CosEdges);
    hCC0Pi_Np->GetXaxis()->SetTitle("#mu^{-} candidate momentum [MeV/c]");
    hCC0Pi_Np->GetYaxis()->SetTitle("#mu^{-} candidate cos#theta");
    
    
    TH1F *hEnu_ZeroProt_True = new TH1F("hEnu_ZeroProt_True", "CC0Pi-0p nominal MC (2p2h only)", 100, 0, 2);
    hEnu_ZeroProt_True->GetXaxis()->SetTitle("True E_{nu} (GeV)");
    
    TH1F *hEnu_nProt_True = new TH1F("hEnu_nProt_True", "CC0Pi-Np nominal MC (2p2h only)", 100, 0, 2);
    hEnu_nProt_True->GetXaxis()->SetTitle("True E_{nu} (GeV)");
    
    
    
    TH1F *hQ2_ZeroProt_True = new TH1F("hQ2_ZeroProt_True", "CC0Pi-0p nominal MC (CCQE only)", 100, 0, 1.2);
    hQ2_ZeroProt_True->GetXaxis()->SetTitle("True Q^{2} (GeV)");
    
    TH1F *hQ2_nProt_True = new TH1F("hQ2_nProt_True", "CC0Pi-Np nominal MC (CCQE only)", 100, 0, 1.2);
    hQ2_nProt_True->GetXaxis()->SetTitle("True Q^{2} (GeV)");
    
    
    TH2F *hCC0Pi_Np_proton = new TH2F("hCC0Pi_Np_proton", "CC0Pi-Np nominal MC", BINPROTON-1 ,MomentumEdgesProton, BINPROTON-1, CosEdgesProton);
    hCC0Pi_Np_proton->GetXaxis()->SetTitle("proton candidate momentum [MeV/c]");
    hCC0Pi_Np_proton->GetYaxis()->SetTitle("proton candidate cos#theta");
    
    
    for(int i=0;  i<AllEvents; i++)
    {
        tree->GetEntry(i);
        
        if(SampleID == SelectionCC0Pi0p)
        {
            hResolution_ZeroProt->Fill(TrueMuonMomentum*1000, RecoMuonMomentum);
            hResolution_ZeroProtAngle->Fill(TrueMuonCosTheta, RecoMuonCosTheta);
        }
        if(SampleID == SelectionCC0PiNp)
        {
            hResolution_nProt->Fill(TrueMuonMomentum*1000, RecoMuonMomentum);
            hResolution_nProtAngle->Fill(TrueMuonCosTheta, RecoMuonCosTheta);
        }
        
        
        
        if(SampleID == SelectionCC0Pi0p && ReactionCode == ReactionCode_CCQE )
        {
            hQ2_ZeroProt_True->Fill(TrueQ2);
        }
        if(SampleID == SelectionCC0PiNp && ReactionCode== ReactionCode_CCQE )
        {
            hQ2_nProt_True->Fill(TrueQ2);
        }
            
        if(SampleID == SelectionCC0Pi0p)
        {
            hTransferAll_ZeroProt_True->Fill(TrueQ3, TrueQ0);
        }
        if(SampleID == SelectionCC0PiNp )
        {  
            hTransferAll_nProt_True->Fill(TrueQ3, TrueQ0);
        }
            
        if(SampleID == SelectionCC0Pi0p && ReactionCode == ReactionCode_2p2h )
        {
            hTransfer_ZeroProt_Reco->Fill(Q3Rec , Q0Rec);
            hTransfer_ZeroProt_True->Fill(TrueQ3, TrueQ0);
            hCC0Pi_0p->Fill(RecoMuonMomentum, RecoMuonCosTheta);
            
            hEnu_ZeroProt_True->Fill(TrueEnu);
        }
        if(SampleID == SelectionCC0PiNp && ReactionCode== ReactionCode_2p2h )
        {
            hTransfer_nProt_Reco->Fill(Q3Rec , Q0Rec);
            hTransfer_nProt_True->Fill(TrueQ3, TrueQ0);
            hCC0Pi_Np->Fill(RecoMuonMomentum, RecoMuonCosTheta);
            hCC0Pi_Np_proton->Fill(RecoProtonMomentum, RecoProtonCosTheta);
            
            hEnu_nProt_True->Fill(TrueEnu);
        }
    }
    for(int ix=1;ix<hResolution_ZeroProt->GetNbinsX() + 1; ix++)
    {
        TH1F *Temp = new TH1F("Temp", "Temp", 50, 0, 1000);
        double RMS = 0;
        double Mean = 0;
        for(int iy=1;iy<hResolution_ZeroProt->GetNbinsY() + 1; iy++)
        {  
            double BinTempCont = hResolution_ZeroProt->GetBinContent(ix,iy);
            Temp->SetBinContent(iy,BinTempCont);
        }
            Mean= Temp->GetMean();
            RMS = Temp->GetRMS();
            
            hMeanRMS_ZeroProt->SetBinContent(ix,  Mean);
            hMeanRMS_ZeroProt->SetBinError(ix,  RMS);
            hRMS_ZeroProt->SetBinContent(ix,  RMS);
            delete Temp;
    }
    
    for(int ix=1;ix<hResolution_nProt->GetNbinsX() + 1; ix++)
    {
        TH1F *Temp = new TH1F("Temp", "Temp", 50, 0, 1000);
        double RMS = 0;
        double Mean = 0;
        for(int iy=1;iy<hResolution_nProt->GetNbinsY() + 1; iy++)
        {  
            double BinTempCont = hResolution_nProt->GetBinContent(ix,iy);
            Temp->SetBinContent(iy,BinTempCont);
        }
            Mean= Temp->GetMean();
            RMS = Temp->GetRMS();
            
            hMeanRMS_nProt->SetBinContent(ix,  Mean);
            hMeanRMS_nProt->SetBinError(ix,  RMS);
            hRMS_nProt->SetBinContent(ix,  RMS);
            delete Temp;
    }
    
    
    
       for(int ix=1;ix<hResolution_ZeroProtAngle->GetNbinsX() + 1; ix++)
    {
        TH1F *Temp = new TH1F("Temp", "Temp", 50, 0, 1);
        double RMS = 0;
        double Mean = 0;
        for(int iy=1;iy<hResolution_ZeroProtAngle->GetNbinsY() + 1; iy++)
        {  
            double BinTempCont = hResolution_ZeroProtAngle->GetBinContent(ix,iy);
            Temp->SetBinContent(iy,BinTempCont);
        }
            Mean= Temp->GetMean();
            RMS = Temp->GetRMS();
            
            hMeanRMS_ZeroProtAngle->SetBinContent(ix,  Mean);
            hMeanRMS_ZeroProtAngle->SetBinError(ix,  RMS);
            hRMS_ZeroProtAngle->SetBinContent(ix,  RMS);
            delete Temp;
    }
           for(int ix=1;ix<hResolution_ZeroProtAngle->GetNbinsX() + 1; ix++)
    {
        TH1F *Temp = new TH1F("Temp", "Temp", 50, 0, 1);
        double RMS = 0;
        double Mean = 0;
        for(int iy=1;iy<hResolution_nProtAngle->GetNbinsY() + 1; iy++)
        {  
            double BinTempCont = hResolution_nProtAngle->GetBinContent(ix,iy);
            Temp->SetBinContent(iy,BinTempCont);
        }
            Mean= Temp->GetMean();
            RMS = Temp->GetRMS();
            
            hMeanRMS_nProtAngle->SetBinContent(ix,  Mean);
            hMeanRMS_nProtAngle->SetBinError(ix,  RMS);
            hRMS_nProtAngle->SetBinContent(ix,  RMS);
            delete Temp;
    }
    
    
    c1->Print(Form("%s.pdf[",fname.Data()), "pdf");  
    
    hResolution_ZeroProt->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hMeanRMS_ZeroProt->Draw("LE");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_ZeroProt->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    hResolution_nProt->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hMeanRMS_nProt->Draw("LE");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_nProt->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_ZeroProt->SetLineColor(kBlue);
    hRMS_nProt->SetLineColor(kGreen);
    hRMS_ZeroProt->Draw();
    hRMS_nProt->Draw("SAME");
    
    legend = new TLegend(0.65,0.7,0.9,0.9);
    legend->AddEntry(hRMS_ZeroProt, "CC0Pi-0p","l");
    legend->AddEntry(hRMS_nProt,"CC0Pi-Np","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    
    hResolution_ZeroProtAngle->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hMeanRMS_ZeroProtAngle->Draw("LE");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_ZeroProtAngle->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hResolution_nProtAngle->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
          
    hMeanRMS_nProtAngle->Draw("LE");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_nProtAngle->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hRMS_ZeroProtAngle->SetLineColor(kBlue);
    hRMS_nProtAngle->SetLineColor(kGreen);
    hRMS_ZeroProtAngle->Draw();
    hRMS_nProtAngle->Draw("SAME");
    
    legend = new TLegend(0.65,0.7,0.9,0.9);
    legend->AddEntry(hRMS_ZeroProtAngle, "CC0Pi-0p","l");
    legend->AddEntry(hRMS_nProtAngle,"CC0Pi-Np","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hTransfer_ZeroProt_True->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hTransfer_nProt_True->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hTransferAll_ZeroProt_True->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hTransferAll_nProt_True->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    double norm = 1/hEnu_ZeroProt_True->Integral();
    hEnu_ZeroProt_True->Scale(norm);
    double norm = 1/hEnu_nProt_True->Integral();
    hEnu_nProt_True->Scale(norm);
    
    hEnu_ZeroProt_True->SetLineColor(kBlue);
    hEnu_nProt_True->SetLineColor(kGreen);
    hEnu_ZeroProt_True->Draw("");
    hEnu_nProt_True->Draw("SAME");
    
    legend = new TLegend(0.65,0.7,0.9,0.9);
    legend->AddEntry(hEnu_ZeroProt_True, "CC0Pi-0p (2p2h)","l");
    legend->AddEntry(hEnu_nProt_True,"CC0Pi-Np (2p2h)","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hEnu_ZeroProt_True->SetLineColor(kViolet);
    hEnu_ZeroProt_True->SetFillColor(kViolet);
    hEnu_ZeroProt_True->Draw("");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hEnu_nProt_True->SetLineColor(kViolet);
    hEnu_nProt_True->SetFillColor(kViolet);
    hEnu_nProt_True->Draw("");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    double norm = 1/hQ2_ZeroProt_True->Integral();
    hQ2_ZeroProt_True->Scale(norm);
    double norm = 1/hQ2_nProt_True->Integral();
    hQ2_nProt_True->Scale(norm);
    
    hQ2_ZeroProt_True->SetLineColor(kBlue);
    hQ2_nProt_True->SetLineColor(kGreen);
    hQ2_ZeroProt_True->Draw("");
    hQ2_nProt_True->Draw("SAME");
    
    legend = new TLegend(0.60,0.7,0.9,0.9);
    legend->AddEntry(hQ2_ZeroProt_True, "CC0Pi-0p (CCQE)","l");
    legend->AddEntry(hQ2_nProt_True,"CC0Pi-Np (CCQE)","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    hQ2_ZeroProt_True->SetLineColor(kRed);
    hQ2_ZeroProt_True->SetFillColor(kRed);
    hQ2_ZeroProt_True->Draw("");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hQ2_nProt_True->SetLineColor(kRed);
    hQ2_nProt_True->SetFillColor(kRed);
    hQ2_nProt_True->Draw("");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    /*
    hTransfer_ZeroProt_Reco->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hTransfer_nProt_Reco->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    */

    
    
    hCC0Pi_0p->GetXaxis()->SetRangeUser(0, 5000);
    hCC0Pi_0p->GetYaxis()->SetRangeUser(0.6, 1);
    hCC0Pi_0p->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hCC0Pi_Np->GetXaxis()->SetRangeUser(0, 5000);
    hCC0Pi_Np->GetYaxis()->SetRangeUser(0.6, 1);
    hCC0Pi_Np->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    hCC0Pi_Np_proton->GetXaxis()->SetRangeUser(0, 5000);
    hCC0Pi_Np_proton->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
    c1->Print(Form("%s.pdf]",fname.Data()), "pdf");
    
    
    if(VERBOSE) std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
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
        FontSizeTitle = 0.050;
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
    gStyle->SetLabelSize(FontSizeLabel, "z");
    gStyle->SetLabelOffset(0.012, "x");
    gStyle->SetLabelOffset(0.012, "y");
    gStyle->SetLabelOffset(0.012, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleSize(FontSizeTitle, "t");
    gStyle->SetTitleOffset(0.8, "x");
    gStyle->SetTitleOffset(0.8, "y");
    gStyle->SetTitleOffset(1.0, "z");

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
