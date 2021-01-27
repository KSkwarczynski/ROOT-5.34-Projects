
using namespace std;

void Analyse2p2h(TString fname)
{
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    bool DEBUGMODE=false;
    bool VERBOSE=true;
    
    TFile *file=TFile::Open( Form("%s", fname.Data() ) );
    TTree *tree;
    file->GetObject("FlatTree_VARS",tree);

//*******************************************************************************//      
   // Declaration of leaf types
   Int_t           Mode;
   Int_t           TgtA;
   Int_t           TgtZ;
   Int_t           PDGnu;
   Float_t         Enu_true;
   Int_t           Nleptons;
   Float_t         MLep;
   Float_t         ELep;
   Float_t         TLep;
   Float_t         CosLep;
   Float_t         CosPmuPpip;
   Float_t         CosPmuPpim;
   Float_t         CosPmuPpi0;
   Float_t         CosPmuPprot;
   Float_t         CosPmuPneut;
   Int_t           Nprotons;
   Float_t         MPr;
   Float_t         EPr;
   Float_t         TPr;
   Float_t         CosPr;
   Float_t         CosPprotPneut;
   Int_t           Nneutrons;
   Float_t         MNe;
   Float_t         ENe;
   Float_t         TNe;
   Float_t         CosNe;
   Int_t           Npiplus;
   Float_t         MPiP;
   Float_t         EPiP;
   Float_t         TPiP;
   Float_t         CosPiP;
   Float_t         CosPpipPprot;
   Float_t         CosPpipPneut;
   Float_t         CosPpipPpim;
   Float_t         CosPpipPpi0;
   Int_t           Npineg;
   Float_t         MPiN;
   Float_t         EPiN;
   Float_t         TPiN;
   Float_t         CosPiN;
   Float_t         CosPpimPprot;
   Float_t         CosPpimPneut;
   Float_t         CosPpimPpi0;
   Int_t           Npi0;
   Float_t         MPi0;
   Float_t         EPi0;
   Float_t         TPi0;
   Float_t         CosPi0;
   Float_t         CosPi0Pprot;
   Float_t         CosPi0Pneut;
   Int_t           Nkplus;
   Int_t           Nkneg;
   Int_t           Nother;
   Float_t         Q2_true;
   Float_t         q0_true;
   Float_t         q3_true;
   Float_t         stv_dpt;
   Float_t         stv_dphit;
   Float_t         stv_dat;
   Float_t         pn_rec;
   Float_t         Enu_QE;
   Float_t         Q2_QE;
   Float_t         W_nuc_rest;
   Float_t         bjorken_x;
   Float_t         bjorken_y;
   Float_t         Erecoil_true;
   Float_t         Erecoil_charged;
   Float_t         Erecoil_minerva;
   Int_t           Nleptons_vect;
   Int_t           Nprotons_vect;
   Int_t           Nneutrons_vect;
   Int_t           Npiplus_vect;
   Int_t           Npineg_vect;
   Int_t           Npi0_vect;
   Int_t           Nkplus_vect;
   Int_t           Nkneg_vect;
   Int_t           Nother_vect;
   Float_t         Weight;
   Float_t         InputWeight;
   Float_t         RWWeight;
   Float_t         FluxWeight;
   Double_t        fScaleFactor;
   Bool_t          flagCCINC;
   Bool_t          flagNCINC;
   Bool_t          flagCCQE;
   Bool_t          flagCC0pi;
   Bool_t          flagCCQELike;
   Bool_t          flagNCEL;
   Bool_t          flagNC0pi;
   Bool_t          flagCCcoh;
   Bool_t          flagNCcoh;
   Bool_t          flagCC1pip;
   Bool_t          flagNC1pip;
   Bool_t          flagCC1pim;
   Bool_t          flagNC1pim;
   Bool_t          flagCC1pi0;
   Bool_t          flagNC1pi0;
   
   //TLorentzVector hm_pprot_4mom = 0;
    TLorentzVector* hm_pprot_4mom = NULL;
      // List of branches
   TBranch        *b_Mode;   //!
   TBranch        *b_TgtA;   //!
   TBranch        *b_TgtZ;   //!
   TBranch        *b_PDGnu;   //!
   TBranch        *b_Enu_true;   //!
   TBranch        *b_Nleptons;   //!
   TBranch        *b_MLep;   //!
   TBranch        *b_ELep;   //!
   TBranch        *b_TLep;   //!
   TBranch        *b_CosLep;   //!
   TBranch        *b_CosPmuPpip;   //!
   TBranch        *b_CosPmuPpim;   //!
   TBranch        *b_CosPmuPpi0;   //!
   TBranch        *b_CosPmuPprot;   //!
   TBranch        *b_CosPmuPneut;   //!
   TBranch        *b_Nprotons;   //!
   TBranch        *b_MPr;   //!
   TBranch        *b_EPr;   //!
   TBranch        *b_TPr;   //!
   TBranch        *b_CosPr;   //!
   TBranch        *b_CosPprotPneut;   //!
   TBranch        *b_Nneutrons;   //!
   TBranch        *b_MNe;   //!
   TBranch        *b_ENe;   //!
   TBranch        *b_TNe;   //!
   TBranch        *b_CosNe;   //!
   TBranch        *b_Npiplus;   //!
   TBranch        *b_MPiP;   //!
   TBranch        *b_EPiP;   //!
   TBranch        *b_TPiP;   //!
   TBranch        *b_CosPiP;   //!
   TBranch        *b_CosPpipProt;   //!
   TBranch        *b_CosPpipPneut;   //!
   TBranch        *b_CosPpipPpim;   //!
   TBranch        *b_CosPpipPpi0;   //!
   TBranch        *b_Npineg;   //!
   TBranch        *b_MPiN;   //!
   TBranch        *b_EPiN;   //!
   TBranch        *b_TPiN;   //!
   TBranch        *b_CosPiN;   //!
   TBranch        *b_CosPpimPprot;   //!
   TBranch        *b_CosPpimPneut;   //!
   TBranch        *b_CosPpimPpi0;   //!
   TBranch        *b_Npi0;   //!
   TBranch        *b_MPi0;   //!
   TBranch        *b_EPi0;   //!
   TBranch        *b_TPi0;   //!
   TBranch        *b_CosPi0;   //!
   TBranch        *b_CosPi0Pprot;   //!
   TBranch        *b_CosPi0Pneut;   //!
   TBranch        *b_Nkplus;   //!
   TBranch        *b_Nkneg;   //!
   TBranch        *b_Nother;   //!
   TBranch        *b_Q2_true;   //!
   TBranch        *b_q0_true;   //!
   TBranch        *b_q3_true;   //!
   TBranch        *b_stv_dpt;   //!
   TBranch        *b_stv_dphit;   //!
   TBranch        *b_stv_dat;   //!
   TBranch        *b_pn_rec;   //!
   TBranch        *b_Enu_QE;   //!
   TBranch        *b_Q2_QE;   //!
   TBranch        *b_W_nuc_rest;   //!
   TBranch        *b_bjorken_x;   //!
   TBranch        *b_bjorken_y;   //!
   TBranch        *b_Erecoil_true;   //!
   TBranch        *b_Erecoil_charged;   //!
   TBranch        *b_Erecoil_minerva;   //!
   TBranch        *b_Nleptons_vect;   //!
   TBranch        *b_Nprotons_vect;   //!
   TBranch        *b_Nneutrons_vect;   //!
   TBranch        *b_Npiplus_vect;   //!
   TBranch        *b_Npineg_vect;   //!
   TBranch        *b_Npi0_vect;   //!
   TBranch        *b_Nkplus_vect;   //!
   TBranch        *b_Nkneg_vect;   //!
   TBranch        *b_Nother_vect;   //!
   TBranch        *b_Weight;   //!
   TBranch        *b_InputWeight;   //!
   TBranch        *b_RWWeight;   //!
   TBranch        *b_FluxWeight;   //!
   TBranch        *b_fScaleFactor;   //!
   TBranch        *b_flagCCINC;   //!
   TBranch        *b_flagNCINC;   //!
   TBranch        *b_flagCCQE;   //!
   TBranch        *b_flagCC0pi;   //!
   TBranch        *b_flagCCQELike;   //!
   TBranch        *b_flagNCEL;   //!
   TBranch        *b_flagNC0pi;   //!
   TBranch        *b_flagCCcoh;   //!
   TBranch        *b_flagNCcoh;   //!
   TBranch        *b_flagCC1pip;   //!
   TBranch        *b_flagNC1pip;   //!
   TBranch        *b_flagCC1pim;   //!
   TBranch        *b_flagNC1pim;   //!
   TBranch        *b_flagCC1pi0;   //!
   TBranch        *b_flagNC1pi0;   //!

   
     tree->SetBranchAddress("Mode", &Mode, &b_Mode);
   tree->SetBranchAddress("TgtA", &TgtA, &b_TgtA);
   tree->SetBranchAddress("TgtZ", &TgtZ, &b_TgtZ);
   tree->SetBranchAddress("PDGnu", &PDGnu, &b_PDGnu);
   tree->SetBranchAddress("Enu_true", &Enu_true, &b_Enu_true);
   tree->SetBranchAddress("Nleptons", &Nleptons, &b_Nleptons);
   tree->SetBranchAddress("MLep", &MLep, &b_MLep);
   tree->SetBranchAddress("ELep", &ELep, &b_ELep);
   tree->SetBranchAddress("TLep", &TLep, &b_TLep);
   tree->SetBranchAddress("CosLep", &CosLep, &b_CosLep);
   tree->SetBranchAddress("CosPmuPpip", &CosPmuPpip, &b_CosPmuPpip);
   tree->SetBranchAddress("CosPmuPpim", &CosPmuPpim, &b_CosPmuPpim);
   tree->SetBranchAddress("CosPmuPpi0", &CosPmuPpi0, &b_CosPmuPpi0);
   tree->SetBranchAddress("CosPmuPprot", &CosPmuPprot, &b_CosPmuPprot);
   tree->SetBranchAddress("CosPmuPneut", &CosPmuPneut, &b_CosPmuPneut);
   tree->SetBranchAddress("Nprotons", &Nprotons, &b_Nprotons);
   tree->SetBranchAddress("MPr", &MPr, &b_MPr);
   tree->SetBranchAddress("EPr", &EPr, &b_EPr);
   tree->SetBranchAddress("TPr", &TPr, &b_TPr);
   tree->SetBranchAddress("CosPr", &CosPr, &b_CosPr);
   tree->SetBranchAddress("CosPprotPneut", &CosPprotPneut, &b_CosPprotPneut);
   tree->SetBranchAddress("Nneutrons", &Nneutrons, &b_Nneutrons);
   tree->SetBranchAddress("MNe", &MNe, &b_MNe);
   tree->SetBranchAddress("ENe", &ENe, &b_ENe);
   tree->SetBranchAddress("TNe", &TNe, &b_TNe);
   tree->SetBranchAddress("CosNe", &CosNe, &b_CosNe);
   tree->SetBranchAddress("Npiplus", &Npiplus, &b_Npiplus);
   tree->SetBranchAddress("MPiP", &MPiP, &b_MPiP);
   tree->SetBranchAddress("EPiP", &EPiP, &b_EPiP);
   tree->SetBranchAddress("TPiP", &TPiP, &b_TPiP);
   tree->SetBranchAddress("CosPiP", &CosPiP, &b_CosPiP);
   tree->SetBranchAddress("CosPpipPprot", &CosPpipPprot, &b_CosPpipProt);
   tree->SetBranchAddress("CosPpipPneut", &CosPpipPneut, &b_CosPpipPneut);
   tree->SetBranchAddress("CosPpipPpim", &CosPpipPpim, &b_CosPpipPpim);
   tree->SetBranchAddress("CosPpipPpi0", &CosPpipPpi0, &b_CosPpipPpi0);
   tree->SetBranchAddress("Npineg", &Npineg, &b_Npineg);
   tree->SetBranchAddress("MPiN", &MPiN, &b_MPiN);
   tree->SetBranchAddress("EPiN", &EPiN, &b_EPiN);
   tree->SetBranchAddress("TPiN", &TPiN, &b_TPiN);
   tree->SetBranchAddress("CosPiN", &CosPiN, &b_CosPiN);
   tree->SetBranchAddress("CosPpimPprot", &CosPpimPprot, &b_CosPpimPprot);
   tree->SetBranchAddress("CosPpimPneut", &CosPpimPneut, &b_CosPpimPneut);
   tree->SetBranchAddress("CosPpimPpi0", &CosPpimPpi0, &b_CosPpimPpi0);
   tree->SetBranchAddress("Npi0", &Npi0, &b_Npi0);
   tree->SetBranchAddress("MPi0", &MPi0, &b_MPi0);
   tree->SetBranchAddress("EPi0", &EPi0, &b_EPi0);
   tree->SetBranchAddress("TPi0", &TPi0, &b_TPi0);
   tree->SetBranchAddress("CosPi0", &CosPi0, &b_CosPi0);
   tree->SetBranchAddress("CosPi0Pprot", &CosPi0Pprot, &b_CosPi0Pprot);
   tree->SetBranchAddress("CosPi0Pneut", &CosPi0Pneut, &b_CosPi0Pneut);
   tree->SetBranchAddress("Nkplus", &Nkplus, &b_Nkplus);
   tree->SetBranchAddress("Nkneg", &Nkneg, &b_Nkneg);
   tree->SetBranchAddress("Nother", &Nother, &b_Nother);
   tree->SetBranchAddress("Q2_true", &Q2_true, &b_Q2_true);
   tree->SetBranchAddress("q0_true", &q0_true, &b_q0_true);
   tree->SetBranchAddress("q3_true", &q3_true, &b_q3_true);
   tree->SetBranchAddress("stv_dpt", &stv_dpt, &b_stv_dpt);
   tree->SetBranchAddress("stv_dphit", &stv_dphit, &b_stv_dphit);
   tree->SetBranchAddress("stv_dat", &stv_dat, &b_stv_dat);
   tree->SetBranchAddress("pn_rec", &pn_rec, &b_pn_rec);
   tree->SetBranchAddress("Enu_QE", &Enu_QE, &b_Enu_QE);
   tree->SetBranchAddress("Q2_QE", &Q2_QE, &b_Q2_QE);
   tree->SetBranchAddress("W_nuc_rest", &W_nuc_rest, &b_W_nuc_rest);
   tree->SetBranchAddress("bjorken_x", &bjorken_x, &b_bjorken_x);
   tree->SetBranchAddress("bjorken_y", &bjorken_y, &b_bjorken_y);
   tree->SetBranchAddress("Erecoil_true", &Erecoil_true, &b_Erecoil_true);
   tree->SetBranchAddress("Erecoil_charged", &Erecoil_charged, &b_Erecoil_charged);
   tree->SetBranchAddress("Erecoil_minerva", &Erecoil_minerva, &b_Erecoil_minerva);
   tree->SetBranchAddress("Nleptons_vect", &Nleptons_vect, &b_Nleptons_vect);
   tree->SetBranchAddress("Nprotons_vect", &Nprotons_vect, &b_Nprotons_vect);
   tree->SetBranchAddress("Nneutrons_vect", &Nneutrons_vect, &b_Nneutrons_vect);
   tree->SetBranchAddress("Npiplus_vect", &Npiplus_vect, &b_Npiplus_vect);
   tree->SetBranchAddress("Npineg_vect", &Npineg_vect, &b_Npineg_vect);
   tree->SetBranchAddress("Npi0_vect", &Npi0_vect, &b_Npi0_vect);
   tree->SetBranchAddress("Nkplus_vect", &Nkplus_vect, &b_Nkplus_vect);
   tree->SetBranchAddress("Nkneg_vect", &Nkneg_vect, &b_Nkneg_vect);
   tree->SetBranchAddress("Nother_vect", &Nother_vect, &b_Nother_vect);
   tree->SetBranchAddress("Weight", &Weight, &b_Weight);
   tree->SetBranchAddress("InputWeight", &InputWeight, &b_InputWeight);
   tree->SetBranchAddress("RWWeight", &RWWeight, &b_RWWeight);
   tree->SetBranchAddress("FluxWeight", &FluxWeight, &b_FluxWeight);
   tree->SetBranchAddress("fScaleFactor", &fScaleFactor, &b_fScaleFactor);
   tree->SetBranchAddress("flagCCINC", &flagCCINC, &b_flagCCINC);
   tree->SetBranchAddress("flagNCINC", &flagNCINC, &b_flagNCINC);
   tree->SetBranchAddress("flagCCQE", &flagCCQE, &b_flagCCQE);
   tree->SetBranchAddress("flagCC0pi", &flagCC0pi, &b_flagCC0pi);
   tree->SetBranchAddress("flagCCQELike", &flagCCQELike, &b_flagCCQELike);
   tree->SetBranchAddress("flagNCEL", &flagNCEL, &b_flagNCEL);
   tree->SetBranchAddress("flagNC0pi", &flagNC0pi, &b_flagNC0pi);
   tree->SetBranchAddress("flagCCcoh", &flagCCcoh, &b_flagCCcoh);
   tree->SetBranchAddress("flagNCcoh", &flagNCcoh, &b_flagNCcoh);
   tree->SetBranchAddress("flagCC1pip", &flagCC1pip, &b_flagCC1pip);
   tree->SetBranchAddress("flagNC1pip", &flagNC1pip, &b_flagNC1pip);
   tree->SetBranchAddress("flagCC1pim", &flagCC1pim, &b_flagCC1pim);
   tree->SetBranchAddress("flagNC1pim", &flagNC1pim, &b_flagNC1pim);
   tree->SetBranchAddress("flagCC1pi0", &flagCC1pi0, &b_flagCC1pi0);
   tree->SetBranchAddress("flagNC1pi0", &flagNC1pi0, &b_flagNC1pi0);
      
   //tree->SetBranchAddress("hm_pprot_4mom", &hm_pprot_4mom);
   tree->SetBranchAddress("hm_pprot_4mom", &hm_pprot_4mom );
//*******************************************************************************//   
                
    int AllEvents = tree->GetEntries();
    
    if(VERBOSE) std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<AllEvents<<std::endl;
    
    if(DEBUGMODE) AllEvents=100;
    
    int ReactionCode_CCQE = 1;
    int ReactionCode_2p2h = 2;
    
    double pnCounter = 0;
    double nnCounter = 0;

    TString Model="UNKNOWN";
    string Name = fname.Data();
    if (Name.find("NEUT") != string::npos)
    {
        Model="VALENCIA";
    }
    if (Name.find("GENIE") != string::npos)
    {
        Model="SuSaV2";
    }
    
    TH1F *MuMomentumPP = new TH1F("MuMomentumPP", Form("Muon Momentum %s",Model.Data() ), 20, 0, 1400);
    MuMomentumPP->GetXaxis()->SetTitle("Muon momentum (MeV)");
    
    TH1F *MuMomentumPPcos1 = new TH1F("MuMomentumPPcos1", Form("0.6<cos(#theta)<0.7 %s",Model.Data()), 20, 0, 1400);
    MuMomentumPPcos1->GetXaxis()->SetTitle("Muon momentum (MeV)");
    
    TH1F *MuMomentumPPcos2 = new TH1F("MuMomentumPPcos2", Form("0.9<cos(#theta)<0.94 %s",Model.Data()), 20, 0, 1400);
    MuMomentumPPcos2->GetXaxis()->SetTitle("Muon momentum (MeV)");
    
    TH1F *MuMomentumNP = new TH1F("MuMomentumNP", Form("Muon Momentum %s",Model.Data() ), 20, 0, 1400);
    MuMomentumNP->GetXaxis()->SetTitle("Muon momentum (MeV)");
   
    TH1F *MuMomentumNPcos1 = new TH1F("MuMomentumNPcos1", Form("0.6<cos(#theta)<0.7 %s",Model.Data()), 20, 0, 1400);
    MuMomentumNPcos1->GetXaxis()->SetTitle("Muon momentum (MeV)");
    
    TH1F *MuMomentumNPcos2 = new TH1F("MuMomentumNPcos2", Form("0.9<cos(#theta)<0.94 %s",Model.Data()), 20, 0, 1400);
    MuMomentumNPcos2->GetXaxis()->SetTitle("Muon momentum (MeV)");
    
    
    TH1F *EnuPP = new TH1F("EnuPP", Form("Enu %s",Model.Data() ), 20, 0, 2000);
    EnuPP->GetXaxis()->SetTitle("True Enu (MeV)");
    
    TH1F *EnuNP = new TH1F("EnuNP", Form("Enu %s",Model.Data() ), 20, 0, 2000);
    EnuNP->GetXaxis()->SetTitle("True Enu (MeV)");
    
    
    TH2F *transfer = new TH2F("transfer", Form("q3/q0 %s",Model.Data() ), 40, 0, 1400, 40, 0, 1400);
    transfer->GetXaxis()->SetTitle("True q3 [MeV]");
    transfer->GetYaxis()->SetTitle("True q0 [MeV]");
    
    
    TH2F *PPtransfer = new TH2F("PPtransfer", Form("pn q3/q0 %s",Model.Data() ), 40, 0, 1400, 40, 0, 1400);
    PPtransfer->GetXaxis()->SetTitle("True q3 [MeV]");
    PPtransfer->GetYaxis()->SetTitle("True q0 [MeV]");

    TH2F *PPtransfercos1 = new TH2F("PPtransfercos1",Form("pn q3/q0 0.6<cos(#theta)<0.7 %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    PPtransfercos1->GetXaxis()->SetTitle("True q3 [MeV]");
    PPtransfercos1->GetYaxis()->SetTitle("True q0 [MeV]");
    
    TH2F *PPtransfercos2 = new TH2F("PPtransfercos2",Form("pn q3/q0 0.9<cos(#theta)<0.94 %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    PPtransfercos2->GetXaxis()->SetTitle("True q3 [MeV]");
    PPtransfercos2->GetYaxis()->SetTitle("True q0 [MeV]");
    
    
    TH2F *PPtransferEnu = new TH2F("PPtransferEnu", Form("pn q3/Enu %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    PPtransferEnu->GetXaxis()->SetTitle("True q3 [MeV]");
    PPtransferEnu->GetYaxis()->SetTitle("True Enu [MeV]");
    
    TH2F *PPtransferq0Enu = new TH2F("PPtransferq0Enu", Form("pn q0/Enu %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    PPtransferq0Enu->GetXaxis()->SetTitle("True q0 [MeV]");
    PPtransferq0Enu->GetYaxis()->SetTitle("True Enu [MeV]");
    
    
///////////////////////////////////////////////////////////////////    
    TH2F *NPtransfer = new TH2F("NPtransfer", Form("nn q3/q0 %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    NPtransfer->GetXaxis()->SetTitle("True q3 [MeV]");
    NPtransfer->GetYaxis()->SetTitle("True q0 [MeV]");
    
    TH2F *NPtransfercos1 = new TH2F("NPtransfercos1", Form("nn q3/q0 0.6<cos(#theta)<0.7 %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    NPtransfercos1->GetXaxis()->SetTitle("True q3 [MeV]");
    NPtransfercos1->GetYaxis()->SetTitle("True q0 [MeV]");
    
    
    TH2F *NPtransfercos2 = new TH2F("NPtransfercos2",Form("nn q3/q0 0.9<cos(#theta)<0.94 %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    NPtransfercos2->GetXaxis()->SetTitle("True q3 [MeV]");
    NPtransfercos2->GetYaxis()->SetTitle("True q0 [MeV]");
    
    TH2F *NPtransferEnu = new TH2F("NPtransferEnu",Form("nn q3/Enu %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    NPtransferEnu->GetXaxis()->SetTitle("True q3 [MeV]");
    NPtransferEnu->GetYaxis()->SetTitle("True Enu [MeV]");
    
    TH2F *NPtransferq0Enu = new TH2F("NPtransferq0Enu",Form("nn q0/Enu %s",Model.Data()), 40, 0, 1400, 40, 0, 1400);
    NPtransferq0Enu->GetXaxis()->SetTitle("True q0 [MeV]");
    NPtransferq0Enu->GetYaxis()->SetTitle("True Enu [MeV]");
    
    
///////////////////////////////////    
    const int BINmom = 24;
    const int BINCos = 21;
    const double MomentumEdges[BINmom] = {0, 100, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000, 1050, 1100, 1200, 1500, 2000};
    const double CosEdges[BINCos] = {-1, -0.8, -0.5, -0.2, 0.0, 0.2, 0.3, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8, 0.85, 0.88, 0.9, 0.92, 0.95, 0.96, 0.98, 1.};

    TH2D *hpn_PrimaryProt = new TH2D("hpn_PrimaryProt", Form("pn proton kinemtaics %s",Model.Data()), BINmom-1 ,MomentumEdges, BINCos-1, CosEdges);
    hpn_PrimaryProt->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    hpn_PrimaryProt->GetYaxis()->SetTitle("proton Cos#theta");
    
    TH2D *hnn_PrimaryProt = new TH2D("hnn_PrimaryProt", Form("nn proton kinemtaics %s",Model.Data()), BINmom-1 ,MomentumEdges, BINCos-1, CosEdges); 
    hnn_PrimaryProt->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    hnn_PrimaryProt->GetYaxis()->SetTitle("Proton Cos#theta");
    
    TH1D *hpn_PrimaryProtMom = new TH1D("hpn_PrimaryProtMom", Form("pn/nn proton momentum %s",Model.Data()), BINmom-1 ,MomentumEdges);
    hpn_PrimaryProtMom->GetXaxis()->SetTitle("Proton Momentum [MeV]");
    TH1D *hnn_PrimaryProtMom = new TH1D("hnn_PrimaryProtMom", Form("pn/nn proton momentum %s",Model.Data()), BINmom-1 ,MomentumEdges); 
    hnn_PrimaryProtMom->GetXaxis()->SetTitle("Proton Momentum [MeV]");
        
    for(int i=0;  i<AllEvents; i++)
    {
        tree->GetEntry(i);

        if(Mode==ReactionCode_2p2h )
        {
            transfer->Fill(q3_true, q0_true*(-1));
            if(Nprotons==2 && Nneutrons==0) //PP pair
            {
                MuMomentumPP->Fill(TLep);
                EnuPP->Fill(Enu_true);
                
                PPtransfer->Fill(q3_true, q0_true*(-1));
                PPtransferEnu->Fill(q3_true, Enu_true);
                PPtransferq0Enu->Fill(q0_true*(-1), Enu_true);
                
                hpn_PrimaryProt->Fill(hm_pprot_4mom->Vect().Mag(), hm_pprot_4mom->CosTheta());
                hpn_PrimaryProtMom->Fill(hm_pprot_4mom->Vect().Mag());
                
                if(CosLep>0.6 && CosLep<0.7)
                {
                    MuMomentumPPcos1->Fill(TLep); 
                    PPtransfercos1->Fill(q3_true, q0_true*(-1));
                }
                if(CosLep>0.9 && CosLep<0.94)
                {
                    MuMomentumPPcos2->Fill(TLep);
                    PPtransfercos2->Fill(q3_true, q0_true*(-1));
                }
                
                pnCounter++;
            }
            if(Nprotons==1 && Nneutrons==1) //NP pair
            {
                MuMomentumNP->Fill(TLep); 
                EnuNP->Fill(Enu_true);

                                
                NPtransfer->Fill(q3_true, q0_true*(-1));
                NPtransferEnu->Fill(q3_true, Enu_true);
                NPtransferq0Enu->Fill(q0_true*(-1), Enu_true);
                
                hnn_PrimaryProt->Fill(hm_pprot_4mom->Vect().Mag(), hm_pprot_4mom->CosTheta());
                hnn_PrimaryProtMom->Fill(hm_pprot_4mom->Vect().Mag());
                
                if(CosLep>0.6 && CosLep<0.7)
                {
                    MuMomentumNPcos1->Fill(TLep); 
                    NPtransfercos1->Fill(q3_true, q0_true*(-1));
                }
                if(CosLep>0.9 && CosLep<0.94)
                {
                    MuMomentumNPcos2->Fill(TLep); 
                    NPtransfercos2->Fill(q3_true, q0_true*(-1));
                }
                nnCounter++;

            }
        }

    }
        
    MuMomentumPP->SetLineColorAlpha(kRed, 1);
    MuMomentumNP->SetLineColorAlpha(kBlue, 1);
        
    MuMomentumPP->Draw("");
    MuMomentumNP->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumPP, "pn","l");
    legend->AddEntry(MuMomentumNP,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
        
    c1->Print(Form("%s.pdf(",fname.Data()), "pdf");

    
    MuMomentumPPcos1->SetLineColorAlpha(kRed, 1);
    MuMomentumNPcos1->SetLineColorAlpha(kBlue, 1);
       
    MuMomentumPPcos1->Draw("");
    MuMomentumNPcos1->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumPPcos1, "pn","l");
    legend->AddEntry(MuMomentumNPcos1,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    MuMomentumPPcos2->SetLineColorAlpha(kRed, 1);
    MuMomentumNPcos2->SetLineColorAlpha(kBlue, 1);
       
    MuMomentumPPcos2->Draw("");
    MuMomentumNPcos2->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(MuMomentumPPcos2, "pn","l");
    legend->AddEntry(MuMomentumNPcos2,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    transfer->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        
    double norm = 1/PPtransfer->Integral();
    PPtransfer->Scale(norm);
    //PPtransfer->GetZaxis()->SetRangeUser(0, 0.03);
    
    PPtransfer->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    double norm = 1/NPtransfer->Integral();
    NPtransfer->Scale(norm);
    //NPtransfer->GetZaxis()->SetRangeUser(0, 0.03);
    
    NPtransfer->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");

    PPtransfercos1->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    NPtransfercos1->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    PPtransfercos2->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    NPtransfercos2->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");

    
    PPtransferEnu->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    NPtransferEnu->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    PPtransferq0Enu->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    NPtransferq0Enu->Draw("COLZ");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    
    EnuPP->SetLineColorAlpha(kRed, 1);
    EnuNP->SetLineColorAlpha(kBlue, 1);
        
    EnuPP->Draw("");
    EnuNP->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(EnuPP, "pn","l");
    legend->AddEntry(EnuNP,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    
    double norm = 1/EnuPP->Integral();
    EnuPP->Scale(norm);
    double norm = 1/EnuNP->Integral();
    EnuNP->Scale(norm);
    
    EnuPP->Draw("");
    EnuNP->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(EnuPP, "pn","l");
    legend->AddEntry(EnuNP,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");   
    
    hpn_PrimaryProt->Draw("colz");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    hnn_PrimaryProt->Draw("colz");
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    double norm = 1/hpn_PrimaryProtMom->Integral();
    hpn_PrimaryProtMom->Scale(norm);
    double norm = 1/hnn_PrimaryProtMom->Integral();
    hnn_PrimaryProtMom->Scale(norm);
    
    hpn_PrimaryProtMom->SetLineColorAlpha(kRed, 1);
    hnn_PrimaryProtMom->SetLineColorAlpha(kBlue, 1);
    
    hnn_PrimaryProtMom->Draw("");
    hpn_PrimaryProtMom->Draw("SAME");
    
    legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(hpn_PrimaryProtMom, "pn","l");
    legend->AddEntry(hnn_PrimaryProtMom,"nn","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    
    c1->Print(Form("%s.pdf)",fname.Data()), "pdf");
    
    
    if(VERBOSE) std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
    std::cout<< "\033[1;31m pn pair counter \033[0m "<<pnCounter<<std::endl;
    std::cout<< "\033[1;31m nn pair counter \033[0m "<<nnCounter<<std::endl;
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
        FontSizeTitle = 0.040;
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
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.075); // 0.075 -> 0.13 for colz option
    gStyle->SetPadLeftMargin(0.13);//to include both large/small font options

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
    gStyle->SetLabelOffset(0.012, "x");
    gStyle->SetLabelOffset(0.012, "y");
    gStyle->SetLabelOffset(0.002, "z");

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
