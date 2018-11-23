//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 06 15:52:42 2017 by ROOT version 5.34/36
// from TTree event/Generator level event from Whizard
// found on file: tt_dm100_2hdm_clic380_parton.root
//////////////////////////////////////////////////////////

#ifndef Sygnal_h
#define Sygnal_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Sygnal : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           header_Ievt;
   Int_t           header_Npar;
   Int_t           header_Nout;
   Int_t           header_Nrem;
   Float_t         header_w;
   Float_t         header_Etot;
   Float_t         header_Pxtot;
   Float_t         header_Pytot;
   Float_t         header_Pztot;
   Float_t         header_Et;
   Float_t         header_Pt;
   Int_t           Status[19];   //[Npar]
   Int_t           PDGcode[19];   //[Npar]
   Int_t           FirstDaughter[19];   //[Npar]
   Int_t           LastDaughter[19];   //[Npar]
   Float_t         Px[19];   //[Npar]
   Float_t         Py[19];   //[Npar]
   Float_t         Pz[19];   //[Npar]
   Float_t         E[19];   //[Npar]
   Float_t         Minv[19];   //[Npar]

   // List of branches
   TBranch        *b_header;   //!
   TBranch        *b_Status;   //!
   TBranch        *b_PDGcode;   //!
   TBranch        *b_FirstDaughter;   //!
   TBranch        *b_LastDaughter;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_E;   //!
   TBranch        *b_Minv;   //!

   Sygnal(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Sygnal() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Sygnal,0);
};

#endif

#ifdef Sygnal_cxx
void Sygnal::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("header", &header_Ievt, &b_header);
   fChain->SetBranchAddress("Status", Status, &b_Status);
   fChain->SetBranchAddress("PDGcode", PDGcode, &b_PDGcode);
   fChain->SetBranchAddress("FirstDaughter", FirstDaughter, &b_FirstDaughter);
   fChain->SetBranchAddress("LastDaughter", LastDaughter, &b_LastDaughter);
   fChain->SetBranchAddress("Px", Px, &b_Px);
   fChain->SetBranchAddress("Py", Py, &b_Py);
   fChain->SetBranchAddress("Pz", Pz, &b_Pz);
   fChain->SetBranchAddress("E", E, &b_E);
   fChain->SetBranchAddress("Minv", Minv, &b_Minv);
}

Bool_t Sygnal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Sygnal_cxx
