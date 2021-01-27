#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

void nucleon_fate_fsi_plot(TString fname)
{
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    bool DEBUGMODE=false;
    bool VERBOSE=true;
    
    TFile *file=TFile::Open( Form("%s", fname.Data() ) );
    TTree *tree;
    file->GetObject("ProcessedTree",tree);

//*******************************************************************************//      
   // Declaration of leaf types
  // Declaration of leaf types
   Int_t           target;
   Int_t           target_A;
   Int_t           mode;
   Double_t        Enu;
   Double_t        EnuRecQE;
   Double_t        xsec;
   Int_t           pdg_nu;
   Int_t           pdg_lep;
   Double_t        p_lep;
   Double_t        theta_lep;
 //TLorentzVector  *V_lepton;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
 //TVector3        *V_other;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Double_t        fX;
   Double_t        fY;
   Double_t        fZ;
 //TLorentzVector  *V_nu;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        dphit;
   Double_t        dpt;
   Double_t        dpty;
   Double_t        dptx;
   Double_t        dat;    
   vector<Int_t>   *PDGprimary =0;
   vector<Int_t>   *PDGpostFSI =0;
   Int_t           NprimaryPart;
   Int_t           NfinalPart;
    
    vector<Double_t>   *PXprimary =0;
    vector<Double_t>   *PYprimary =0;
    vector<Double_t>   *PZprimary =0;
    vector<Double_t>   *Eprimary =0;
    vector<Double_t>   *PXpostFSI =0;
    vector<Double_t>   *PYpostFSI =0;
    vector<Double_t>   *PZpostFSI =0;
    vector<Double_t>   *EpostFSI =0;

    // List of branches
    TBranch        *b_target;   //!
    TBranch        *b_target_A;   //!
    TBranch        *b_mode;   //!
    TBranch        *b_Enu;   //!
    TBranch        *b_EnuRecQE;   //!
    TBranch        *b_xsec;   //!
    TBranch        *b_pdg_nu;   //!
    TBranch        *b_pdg_lep;   //!
    TBranch        *b_p_lep;   //!
    TBranch        *b_theta_lep;   //!
    TBranch        *b_V_lepton_fUniqueID;   //!
    TBranch        *b_V_lepton_fBits;   //!
    TBranch        *b_V_lepton_fP_fUniqueID;   //!
    TBranch        *b_V_lepton_fP_fBits;   //!
    TBranch        *b_V_lepton_fP_fX;   //!
    TBranch        *b_V_lepton_fP_fY;   //!
    TBranch        *b_V_lepton_fP_fZ;   //!
    TBranch        *b_V_lepton_fE;   //!
    TBranch        *b_V_other_fUniqueID;   //!
    TBranch        *b_V_other_fBits;   //!
    TBranch        *b_V_other_fX;   //!
    TBranch        *b_V_other_fY;   //!
    TBranch        *b_V_other_fZ;   //!
    TBranch        *b_V_nu_fUniqueID;   //!
    TBranch        *b_V_nu_fBits;   //!
    TBranch        *b_V_nu_fP_fUniqueID;   //!
    TBranch        *b_V_nu_fP_fBits;   //!
    TBranch        *b_V_nu_fP_fX;   //!
    TBranch        *b_V_nu_fP_fY;   //!
    TBranch        *b_V_nu_fP_fZ;   //!
    TBranch        *b_V_nu_fE;   //!
    TBranch        *b_dphit;   //!
    TBranch        *b_dpt;   //!
    TBranch        *b_dpty;   //!
    TBranch        *b_dptx;   //!
    TBranch        *b_dat;   //!
    TBranch        *b_PDGprimary=0;   //!
    TBranch        *b_PDGpostFSI=0;   //!
    TBranch        *b_NprimaryPart;   //!
    TBranch        *b_NfinalPart;   //!
    TBranch        *b_PXprimary=0;   //!
    TBranch        *b_PYprimary=0;   //!
    TBranch        *b_PZprimary=0;   //!
    TBranch        *b_Eprimary=0;   //!
    TBranch        *b_PXpostFSI=0;   //!
    TBranch        *b_PYpostFSI=0;   //!
    TBranch        *b_PZpostFSI=0;   //!
    TBranch        *b_EpostFSI=0;   //!
    
   tree->SetBranchAddress("target", &target, &b_target);
   tree->SetBranchAddress("target_A", &target_A, &b_target_A);
   tree->SetBranchAddress("mode", &mode, &b_mode);
   tree->SetBranchAddress("Enu", &Enu, &b_Enu);
   tree->SetBranchAddress("EnuRecQE", &EnuRecQE, &b_EnuRecQE);
   tree->SetBranchAddress("xsec", &xsec, &b_xsec);
   tree->SetBranchAddress("pdg_nu", &pdg_nu, &b_pdg_nu);
   tree->SetBranchAddress("pdg_lep", &pdg_lep, &b_pdg_lep);
   tree->SetBranchAddress("p_lep", &p_lep, &b_p_lep);
   tree->SetBranchAddress("theta_lep", &theta_lep, &b_theta_lep);
   tree->SetBranchAddress("fUniqueID", &fUniqueID, &b_V_lepton_fUniqueID);
   tree->SetBranchAddress("fBits", &fBits, &b_V_lepton_fBits);
   tree->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_V_lepton_fP_fUniqueID);
   tree->SetBranchAddress("fP.fBits", &fP_fBits, &b_V_lepton_fP_fBits);
   tree->SetBranchAddress("fP.fX", &fP_fX, &b_V_lepton_fP_fX);
   tree->SetBranchAddress("fP.fY", &fP_fY, &b_V_lepton_fP_fY);
   tree->SetBranchAddress("fP.fZ", &fP_fZ, &b_V_lepton_fP_fZ);
   tree->SetBranchAddress("fE", &fE, &b_V_lepton_fE);
//    tree->SetBranchAddress("fUniqueID", &fUniqueID, &b_V_other_fUniqueID);
//    tree->SetBranchAddress("fBits", &fBits, &b_V_other_fBits);
   tree->SetBranchAddress("fX", &fX, &b_V_other_fX);
   tree->SetBranchAddress("fY", &fY, &b_V_other_fY);
   tree->SetBranchAddress("fZ", &fZ, &b_V_other_fZ);
//    tree->SetBranchAddress("fUniqueID", &fUniqueID, &b_V_nu_fUniqueID);
//    tree->SetBranchAddress("fBits", &fBits, &b_V_nu_fBits);
//    tree->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_V_nu_fP_fUniqueID);
//    tree->SetBranchAddress("fP.fBits", &fP_fBits, &b_V_nu_fP_fBits);
//    tree->SetBranchAddress("fP.fX", &fP_fX, &b_V_nu_fP_fX);
//    tree->SetBranchAddress("fP.fY", &fP_fY, &b_V_nu_fP_fY);
//    tree->SetBranchAddress("fP.fZ", &fP_fZ, &b_V_nu_fP_fZ);
//    tree->SetBranchAddress("fE", &fE, &b_V_nu_fE);
   tree->SetBranchAddress("dphit", &dphit, &b_dphit);
   tree->SetBranchAddress("dpt", &dpt, &b_dpt);
   tree->SetBranchAddress("dpty", &dpty, &b_dpty);
   tree->SetBranchAddress("dptx", &dptx, &b_dptx);
   tree->SetBranchAddress("dat", &dat, &b_dat);
   tree->SetBranchAddress("PDGprimary", &PDGprimary, &b_PDGprimary);
   tree->SetBranchAddress("PDGpostFSI", &PDGpostFSI, &b_PDGpostFSI);
   tree->SetBranchAddress("NprimaryPart", &NprimaryPart, &b_NprimaryPart);
   tree->SetBranchAddress("NfinalPart", &NfinalPart, &b_NfinalPart);
   tree->SetBranchAddress("PXprimary", &PXprimary, &b_PXprimary);
    tree->SetBranchAddress("PYprimary", &PYprimary, &b_PYprimary);
    tree->SetBranchAddress("PZprimary", &PZprimary, &b_PZprimary);
    tree->SetBranchAddress("Eprimary", &Eprimary, &b_Eprimary);
    tree->SetBranchAddress("PXpostFSI", &PXpostFSI, &b_PXpostFSI);
    tree->SetBranchAddress("PYpostFSI", &PYpostFSI, &b_PYpostFSI);
    tree->SetBranchAddress("PZpostFSI", &PZpostFSI, &b_PZpostFSI);
    tree->SetBranchAddress("EpostFSI", &EpostFSI, &b_EpostFSI);
   
//*******************************************************************************//   
    
   const Int_t binNumber = 5;
   const char *FSItype[binNumber] = {"no FSI","elastic FSI", "Inelastic FSI", "pion prod FSI", "pion abs FSI"};
   double eps = 0.0001;
   TH1F *hFSI_fate = new TH1F("hFSI_fate", "FSI mode", binNumber, 0, binNumber);
    int FSImodeCounter[5];
   
    int AllEvents = tree->GetEntries();
    
    if(VERBOSE) std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<AllEvents<<std::endl;
    
    if(DEBUGMODE) AllEvents=5000;
    size_t interval = AllEvents / 100;
    interval = interval ? interval : 1;
    
    for(int i=0;  i<AllEvents; i++)
    {
        if (i && !(i % interval))
        {
            std::cout << "[INFO]: Processed: " << i << " entries." << std::endl;
        }
        tree->GetEntry(i);
        
         //cout<<"PDGprimary "<<PDGprimary->size()<<endl; 
         //cout<<"PDGpostFSI "<<PDGpostFSI->size()<<endl; 
        if(mode<30) //// all CC modes
        {        
            
            
            std::vector<TLorentzVector> pvert;
            std::vector<TLorentzVector> pfs;
            
            for (Int_t ij = 0; ij<PXprimary->size(); ij++)
            {    
                TLorentzVector temp(PXprimary->at(ij), PYprimary->at(ij), PZprimary->at(ij), Eprimary->at(ij));
                pvert.push_back(temp);
            }
            for (Int_t ij = 0; ij<PXpostFSI->size(); ij++)
            {
                TLorentzVector temp(PXpostFSI->at(ij), PYpostFSI->at(ij), PZpostFSI->at(ij), EpostFSI->at(ij));
                pfs.push_back(temp);
            }
            //cout<<"DEBUG "<<PXprimary->at(0)<<"   "<<(pvert.at(0)).Px()<<endl;
            
            bool samePartVertFS = SameParticlesVertFS(*PDGprimary, *PDGpostFSI);

            //cout<<"  samePartVertFS "<<samePartVertFS<<endl;
            if (samePartVertFS == true)
            {
                // Same particles => either no FSI or elastic FSI
                // Get the momenta and evaluate the variation
                //std::cout<<"no or elas FSI"<<std::endl;
                //FIXME  
                //std::vector<TLorentzVector> pvert = FitUtils::GetPvert(fevt), pfs = FitUtils::GetPfs(fevt);
                bool noFSI = IsNoFSI(*PDGprimary, pvert, *PDGpostFSI, pfs, eps);
                //bool noFSI = false;
                //cout<<" kkuuuuuurwa "<<noFSI<<endl;
                if (noFSI == true)
                {
                    //std::cout<<"noFSI"<<std::endl;
                    FSImodeCounter[0]++; // no FSI
                    
                }
                else
                {
                    FSImodeCounter[1]++; // elastic
                   //std::cout<<"elasFSI"<<std::endl;
                }
            }
            else
            {
                //std::cout<<"inelasFSI"<<std::endl;
                // The particles changed due to FSI
                // Inelactic: either no extra pions produced, exta pion production, or pion absorption
                
                int Npivert = GetNpi(PDGprimary);
                int Npifs = GetNpi(PDGpostFSI);

                //cout<<"Npifs  "<<Npifs<<endl;
                //cout<<"Npivert  "<<Npivert<<endl;
                if (Npifs>Npivert) // Pion production
                {
                    FSImodeCounter[3]++;
                }
                else if (Npifs<Npivert) // Pion absorption
                {
                    FSImodeCounter[4]++;
                }
                else // Inelastic
                {
                    FSImodeCounter[2]++;
                }
            }
        }
    }

   for (int ig=1;ig<=binNumber;ig++)
   {
       //cout<<" FINAL TEST  "<< ig<<" counter "<<FSImodeCounter[ig-1]<<" name "<<FSItype[ig-1]<<endl;
       hFSI_fate->Fill(ig-1, FSImodeCounter[ig-1]);
       hFSI_fate->GetXaxis()->SetBinLabel(ig,FSItype[ig-1]);
   }
  
    hFSI_fate->Draw();
    c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    
    
    if(VERBOSE) std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
}



bool SameParticlesVertFS(std::vector<int> &PDGvert, std::vector<int> &PDGfs)
{
    // Check if we have the same particles at vert and fs
    int const nvertp = PDGvert.size();
    int const nfsp = PDGfs.size();

    if (nfsp != nvertp) return false;
    //FIXME ROOT 5 is retarded so we have to transfrom vector into array
    int PDGvert_sorted[nvertp];
    int PDGfs_sorted[nfsp];
    for (Int_t i = 0; i<PDGvert.size(); i++)
    {
       PDGvert_sorted[i]=PDGvert.at(i); 
    }
    for (Int_t i = 0; i<PDGfs.size(); i++)
    {
       PDGfs_sorted[i]=PDGfs.at(i); 
    }
    
    sort(PDGvert_sorted, PDGvert_sorted+nvertp);
    sort(PDGfs_sorted, PDGfs_sorted+nfsp);

    for (Int_t i = 0; i<nvertp; i++)
    {
        //cout<<"sorted PDG"<<PDGvert_sorted[i]<<endl;
        if (PDGvert_sorted[i] != PDGfs_sorted[i] )
        return false;
    }
    return true;
}


int GetNpi(std::vector<int> *PDG)
{
    int Npi = 0;
    //cout<<" zaraza "<< PDG->size()<<endl;
    for (int i = 0; i<PDG->size(); i++)
    {
    //cout<<" kurdebele "<<PDG->at(i)<<endl;
      if (abs(PDG->at(i)) == 211 || abs(PDG->at(i)) == 111) Npi++;
    }
  return Npi;
}

bool IsNoFSI(std::vector<int> &PDGvert, std::vector<TLorentzVector> pvert, std::vector<int> &PDGfs, std::vector<TLorentzVector> pfs, double eps)
{
    // Check if we have the same particles at vert and fs
        
    //bool samePartVertFS = SameParticlesVertFS(PDGvert, PDGfs);
        
    //if (samePartVertFS == false)
    //    return false;
        
    // Now we know that we have the same particles in both vert and fs
    // Let's check how much the momentum changes
    int const nvertp = PDGvert.size();
    bool visited[nvertp]={};
    //cout<<"DEBUG W noFSI "<<visited[0]<<endl;
    //cout<<"DEBUG W noFSI "<<endl;
    for (int k = 0; k<nvertp; k++)
    {
        int l = 0;
        for (l = 0; l<nvertp; l++)
        {
            if (PDGvert.at(k) == PDGfs.at(l) && visited[l] == false)
            {
                TLorentzVector diff = pvert.at(k) - pfs.at(l);
//cout<<"DEBUG diff "<<diff.Px()<<" pvert  "<<(pvert.at(k)).Px()<<" pfs  "<<(pfs.at(k)).Px()<<endl;
                double dist = diff.Vect().Mag();
                //cout<<" kurwa dist "<<dist<<endl;
                if (dist < eps * pvert[k].Vect().Mag())
                {
                    visited[l] = true;
                    break;
                }
            }
        }
        //if (l == nvertp) cout<<" no i chuj no i czesc "<<endl;
        if (l == nvertp) return false;
    }
    return true;
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

    gStyle->SetLegendBorderSize(0); //This option dsables legends borders
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
