//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 28 17:53:05 2016 by ROOT version 5.34/09
// from TTree tnuwro/NuwroSimpleTree
// found on file: events.allchannels-mecnieves.ND280FGD1active13.simple3-antinu.root
//////////////////////////////////////////////////////////

#ifndef tnuwro_h
#define tnuwro_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class tnuwro {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           event_num;
   Int_t           channel;
   Int_t           neutrino_pid;
   Float_t         neutrino_p;
   Float_t         neutrino_px;
   Float_t         neutrino_py;
   Float_t         neutrino_pz;
   Int_t           target_pid;
   Float_t         target_p;
   Float_t         target_px;
   Float_t         target_py;
   Float_t         target_pz;
   Int_t           countPrim;
   vector<int>     *pidPrim;
   vector<float>   *pPrim;
   vector<float>   *pxPrim;
   vector<float>   *pyPrim;
   vector<float>   *pzPrim;
   Int_t           count;
   vector<int>     *pid;
   vector<float>   *p;
   vector<float>   *px;
   vector<float>   *py;
   vector<float>   *pz;

   // List of branches
   TBranch        *b_event_num;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_neutrino_pid;   //!
   TBranch        *b_neutrino_p;   //!
   TBranch        *b_neutrino_px;   //!
   TBranch        *b_neutrino_py;   //!
   TBranch        *b_neutrino_pz;   //!
   TBranch        *b_target_pid;   //!
   TBranch        *b_target_p;   //!
   TBranch        *b_target_px;   //!
   TBranch        *b_target_py;   //!
   TBranch        *b_target_pz;   //!
   TBranch        *b_countPrim;   //!
   TBranch        *b_pidPrim;   //!
   TBranch        *b_pPrim;   //!
   TBranch        *b_pxPrim;   //!
   TBranch        *b_pyPrim;   //!
   TBranch        *b_pzPrim;   //!
   TBranch        *b_count;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_p;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!

   tnuwro(TTree *tree=0);
   virtual ~tnuwro();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef tnuwro_cxx
tnuwro::tnuwro(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("events.allchannels-mecnieves.ND280FGD1active13.simple4-antinu.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("events.allchannels-mecnieves.ND280FGD1active13.simple4-antinu.root");
      }
      f->GetObject("tnuwro",tree);

   }
   Init(tree);
}

tnuwro::~tnuwro()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tnuwro::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tnuwro::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void tnuwro::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   pidPrim = 0;
   pPrim = 0;
   pxPrim = 0;
   pyPrim = 0;
   pzPrim = 0;
   pid = 0;
   p = 0;
   px = 0;
   py = 0;
   pz = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event_num", &event_num, &b_event_num);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("neutrino_pid", &neutrino_pid, &b_neutrino_pid);
   fChain->SetBranchAddress("neutrino_p", &neutrino_p, &b_neutrino_p);
   fChain->SetBranchAddress("neutrino_px", &neutrino_px, &b_neutrino_px);
   fChain->SetBranchAddress("neutrino_py", &neutrino_py, &b_neutrino_py);
   fChain->SetBranchAddress("neutrino_pz", &neutrino_pz, &b_neutrino_pz);
   fChain->SetBranchAddress("target_pid", &target_pid, &b_target_pid);
   fChain->SetBranchAddress("target_p", &target_p, &b_target_p);
   fChain->SetBranchAddress("target_px", &target_px, &b_target_px);
   fChain->SetBranchAddress("target_py", &target_py, &b_target_py);
   fChain->SetBranchAddress("target_pz", &target_pz, &b_target_pz);
   fChain->SetBranchAddress("countPrim", &countPrim, &b_countPrim);
   fChain->SetBranchAddress("pidPrim", &pidPrim, &b_pidPrim);
   fChain->SetBranchAddress("pPrim", &pPrim, &b_pPrim);
   fChain->SetBranchAddress("pxPrim", &pxPrim, &b_pxPrim);
   fChain->SetBranchAddress("pyPrim", &pyPrim, &b_pyPrim);
   fChain->SetBranchAddress("pzPrim", &pzPrim, &b_pzPrim);
   fChain->SetBranchAddress("count", &count, &b_count);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("p", &p, &b_p);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   Notify();
}

Bool_t tnuwro::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tnuwro::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t tnuwro::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef tnuwro_cxx
