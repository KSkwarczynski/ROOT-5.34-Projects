//__________________________________________
// Program for flattening raw NEUT output
//    files
//
// Authors:
//    C. Bronner
//    J. Morrison
//
// History:
//    Summer 2016    - J. Morrison
//    6 October 2017 - J. Morrison
//__________________________________________

//   make app/NeutOutputAnalysis.exe
#include "neutfsipart.h"
#include "neutfsivert.h"
#include "neutpart.h"
#include "neutvect.h"
#include "neutvtx.h"

#include "TChain.h"
#include "TFile.h"
#include "TLorentzVector.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

std::string Fldr;
std::string Fin;
std::string Fout;
int FSIMode = 1;
int LiteMode = 0;
double EbForERecQE_MeV = 0;

void Usage(char const *argv[]) {
  std::cout << "[USAGE]: " << argv[0]
            << " -f <input folder> -o <output file> -i "
               "<input file pattern> [--primary-particles] [--lite-mode] "
               "[--BindE <E_MeV]"
            << std::endl;
}

TVector3 GetVectorInTPlane(const TVector3 &inp, const TVector3 &planarNormal) {
  TVector3 pnUnit = planarNormal.Unit();
  double inpProjectPN = inp.Dot(pnUnit);

  TVector3 InPlanarInput = inp - (inpProjectPN * pnUnit);
  return InPlanarInput;
}

TVector3 GetUnitVectorInTPlane(const TVector3 &inp,
                               const TVector3 &planarNormal) {
  return GetVectorInTPlane(inp, planarNormal).Unit();
}

Double_t GetDeltaPhiT(TVector3 const &V_lepton, TVector3 const &V_other,
                      TVector3 const &Normal, bool PiMinus = false) {
  TVector3 V_lepton_T = GetUnitVectorInTPlane(V_lepton, Normal);

  TVector3 V_other_T = GetUnitVectorInTPlane(V_other, Normal);

  return PiMinus ? acos(V_lepton_T.Dot(V_other_T))
                 : (M_PI - acos(V_lepton_T.Dot(V_other_T)));
}

TVector3 GetDeltaPT(TVector3 const &V_lepton, TVector3 const &V_other,
                    TVector3 const &Normal) {
  TVector3 V_lepton_T = GetVectorInTPlane(V_lepton, Normal);

  TVector3 V_other_T = GetVectorInTPlane(V_other, Normal);

  return V_lepton_T + V_other_T;
}

Double_t GetDeltaAlphaT(TVector3 const &V_lepton, TVector3 const &V_other,
                        TVector3 const &Normal, bool PiMinus = false) {
  TVector3 DeltaPT = GetDeltaPT(V_lepton, V_other, Normal);

  return GetDeltaPhiT(V_lepton, DeltaPT, Normal, PiMinus);
}

void ParseOpts(int argc, char const *argv[]) {
  int OptFlags = 0;
  for (int opt_it = 1; opt_it < argc; opt_it++) {
    std::string arg = argv[opt_it];
    if ((arg == "-h") || (arg == "-?") || (arg == "--help")) {
      Usage(argv);
      exit(0);
    } else if (arg == "--primary-particles") {
      std::cout << "\t--Flattening pre-FSI particle vector." << std::endl;
      FSIMode = 0;
    } else if (arg == "--lite-mode") {
      std::cout << "\t--Using minimal output tree." << std::endl;
      LiteMode = 0;
    } else if ((opt_it + 1) < argc) {
      if (arg == "-f") {
        Fldr = argv[++opt_it];
        std::cout << "\t--Reading input from directory: " << Fldr << std::endl;
      } else if (arg == "-o") {
        Fout = argv[++opt_it];
        std::cout << "\t--Writing output to: " << Fout << std::endl;
        OptFlags ^= 1;
      } else if (arg == "-i") {
        Fin = argv[++opt_it];
        std::cout << "\t--Reading input file: " << Fin << std::endl;
        OptFlags ^= 2;
      } else if (arg == "--BindE") {
        EbForERecQE_MeV = atof(argv[++opt_it]);
        std::cout << "\t--Using: " << EbForERecQE_MeV
                  << " as ERecQE binding energy." << std::endl;
      }
    }
  }
  if (OptFlags != 3) {
    std::cerr << "[ERROR]: Not all required options recieved: (-i, -o)."
              << std::endl;
    Usage(argv);
    exit(1);
  }
}

namespace PhysConst {
const double mass_proton = 0.93827203; // Proton mass in GeV
const double mass_neutron = 0.93956536;
const double mass_muon = 0.10565837; // Muon mass in GeV
} // namespace PhysConst

double EnuQErec(double pl, double costh, double binding, bool neutrino) {
  if (pl < 0)
    return 0.; // Make sure nobody is silly

  double mN_eff = PhysConst::mass_neutron - binding / 1000.;
  double mN_oth = PhysConst::mass_proton;

  if (!neutrino) {
    mN_eff = PhysConst::mass_proton - binding / 1000.;
    mN_oth = PhysConst::mass_neutron;
  }
  double ml = PhysConst::mass_muon;
  double el = sqrt(pl * pl + ml * ml);

  double rEnu =
      (2 * mN_eff * el - ml * ml + mN_oth * mN_oth - mN_eff * mN_eff) /
      (2 * (mN_eff - el + pl * costh));

  return rEnu;
};

//####################################################
void ChainProcess() {
  // Init reading of NEUT files
  NeutVtx *nvtx;
  NeutVect *nvect;

  TChain *tn = new TChain("neuttree");

  std::stringstream inpPattern("");
  if (Fldr.length()) {
    inpPattern << Fldr;
    if (Fldr[Fldr.length() - 1] != '/') {
      inpPattern << "/";
    }
  }
  inpPattern << Fin;

  tn->Add(inpPattern.str().c_str());

  nvtx = new NeutVtx();
  bool BranchesOkay = true;
  BranchesOkay =
      BranchesOkay && (tn->SetBranchAddress("vertexbranch", &nvtx) >= 0);

  nvect = new NeutVect();
  BranchesOkay =
      BranchesOkay && (tn->SetBranchAddress("vectorbranch", &nvect) >= 0);

  if (!BranchesOkay) {
    std::cerr << "[ERROR]: Failed to SetBranchAddress for \"vertexbranch\" "
                 "and/or \"vectorbranch\" for input descriptor: \""
              << inpPattern.str() << "\". Is this a NEUT output vector?"
              << std::endl;
    exit(1);
  }

  Long64_t nevents = tn->GetEntries();

  if (!nevents) {
    std::cerr << "[ERROR]: Found no input entries." << std::endl;
    exit(1);
  }

  std::cout << "[INFO]: Processing " << nevents << " entries." << std::endl;

  // Create output tree
  double W2, Enu, Q2, cos_theta, theta_lep, p_lep, pF, RF_cos_theta, RF_p_lep,
      x, y, xsec, EnuRecQE;
  double dphit, dpt, dpty, dptx, dat;
  int pdg_nu, pdg_lep, target, target_A, outgoing, mode;

  //WARNING
    std::vector<int> PDGprimary;
    std::vector<int> PDGpostFSI;
    std::vector<double> PXprimary;
    std::vector<double> PYprimary;
    std::vector<double> PZprimary;
    std::vector<double> Eprimary;
    std::vector<double> PXpostFSI;
    std::vector<double> PYpostFSI;
    std::vector<double> PZpostFSI;
    std::vector<double> EpostFSI;
              
  int  NprimaryPart, NfinalPart;
  TLorentzVector *V_lepton = 0;
  TVector3 *V_other = 0;
  TLorentzVector *V_nu = 0;

  TFile *out1 = new TFile(Fout.c_str(), "RECREATE");
  TTree *ProcessedTree = new TTree("ProcessedTree", "tree");

  ProcessedTree->Branch("target", &target, "target/I");
  ProcessedTree->Branch("target_A", &target_A, "target_A/I");
  ProcessedTree->Branch("mode", &mode, "mode/I");
  ProcessedTree->Branch("Enu", &Enu, "Enu/D");
  ProcessedTree->Branch("EnuRecQE", &EnuRecQE, "EnuRecQE/D");
  ProcessedTree->Branch("xsec", &xsec, "xsec/D");
  ProcessedTree->Branch("pdg_nu", &pdg_nu, "pdg_nu/I");
  ProcessedTree->Branch("pdg_lep", &pdg_lep, "pdg_lep/I");
  ProcessedTree->Branch("p_lep", &p_lep, "p_lep/D");
  ProcessedTree->Branch("theta_lep", &theta_lep, "theta_lep/D");
  ProcessedTree->Branch("V_lepton", &V_lepton);
  ProcessedTree->Branch("V_other", &V_other);
  ProcessedTree->Branch("V_nu", &V_nu);
  ProcessedTree->Branch("dphit", &dphit, "dphit/D");
  ProcessedTree->Branch("dpt", &dpt, "dpt/D");
  ProcessedTree->Branch("dpty", &dpty, "dpty/D");
  ProcessedTree->Branch("dptx", &dptx, "dptx/D");
  ProcessedTree->Branch("dat", &dat, "dat/D");
  
  //WARNING
    ProcessedTree->Branch("PDGprimary", &PDGprimary);
    ProcessedTree->Branch("PDGpostFSI", &PDGpostFSI);
    ProcessedTree->Branch("PXprimary", &PXprimary);
    ProcessedTree->Branch("PYprimary", &PYprimary);
    ProcessedTree->Branch("PZprimary", &PZprimary);
    ProcessedTree->Branch("Eprimary", &Eprimary);
    ProcessedTree->Branch("PXpostFSI", &PXpostFSI);
    ProcessedTree->Branch("PYpostFSI", &PYpostFSI);
    ProcessedTree->Branch("PZpostFSI", &PZpostFSI);
    ProcessedTree->Branch("EpostFSI", &EpostFSI);
    
  ProcessedTree->Branch("NprimaryPart", &NprimaryPart, "NprimaryPart/I");
  ProcessedTree->Branch("NfinalPart", &NfinalPart, "NfinalPart/I");
  
  size_t interval = nevents / 10;
  interval = interval ? interval : 1;

  for (Long64_t ent_it = 0; ent_it < nevents; ent_it++) {
    if (ent_it && !(ent_it % interval)) {
      std::cout << "[INFO]: Processed: " << ent_it << " entries." << std::endl;
    }
    tn->GetEntry(ent_it);

    // Read event info
    pdg_nu = (nvect->PartInfo(0))->fPID;
    target = (nvect->PartInfo(1))->fPID;
    target_A = nvect->TargetA;
    pdg_lep = (nvect->PartInfo(2))->fPID;
    outgoing = (nvect->PartInfo(3))->fPID;
    mode = nvect->Mode;
    Enu = (nvect->PartInfo(0))->fP.E() / 1.e3;
    xsec = nvect->Totcrs;

    //WARNING
    NprimaryPart = nvect->Nprimary();
    NfinalPart = nvect->Npart();
    // Compute W
    double Ehad = ((nvect->PartInfo(0))->fP.E() + (nvect->PartInfo(1))->fP.E() -
                   (nvect->PartInfo(2))->fP.E()) /
                  1.e3;
    double Phad[3];

    Phad[0] = ((nvect->PartInfo(0))->fP.Px() + (nvect->PartInfo(1))->fP.Px() -
               (nvect->PartInfo(2))->fP.Px()) /
              1.e3;
    Phad[1] = ((nvect->PartInfo(0))->fP.Py() + (nvect->PartInfo(1))->fP.Py() -
               (nvect->PartInfo(2))->fP.Py()) /
              1.e3;
    Phad[2] = ((nvect->PartInfo(0))->fP.Pz() + (nvect->PartInfo(1))->fP.Pz() -
               (nvect->PartInfo(2))->fP.Pz()) /
              1.e3;

    W2 =
        Ehad * Ehad - Phad[0] * Phad[0] - Phad[1] * Phad[1] - Phad[2] * Phad[2];

    // Compute Q2
    double scal =
        (nvect->PartInfo(0))->fP.E() * (nvect->PartInfo(2))->fP.E() -
        (nvect->PartInfo(0))->fP.Px() * (nvect->PartInfo(2))->fP.Px() -
        (nvect->PartInfo(0))->fP.Py() * (nvect->PartInfo(2))->fP.Py() -
        (nvect->PartInfo(0))->fP.Pz() * (nvect->PartInfo(2))->fP.Pz();
    Q2 = (2. * scal - pow((nvect->PartInfo(2))->fMass, 2)) / 1.e6;

    // Compute cos(theta_lep) and p_lep (in GeV)
    p_lep = sqrt(nvect->PartInfo(2)->fP.Px() * nvect->PartInfo(2)->fP.Px() +
                 nvect->PartInfo(2)->fP.Py() * nvect->PartInfo(2)->fP.Py() +
                 nvect->PartInfo(2)->fP.Pz() * nvect->PartInfo(2)->fP.Pz());
    double ScalarProduct =
        (nvect->PartInfo(0))->fP.Px() * (nvect->PartInfo(2))->fP.Px() +
        (nvect->PartInfo(0))->fP.Py() * (nvect->PartInfo(2))->fP.Py() +
        (nvect->PartInfo(0))->fP.Pz() * (nvect->PartInfo(2))->fP.Pz();
    if (p_lep > 0)
      cos_theta = ScalarProduct / (nvect->PartInfo(0)->fP.E() * p_lep);
    else
      cos_theta = 0;

    // Calculate theta_lep in degrees
    theta_lep = std::acos(cos_theta) * 180.0 / TMath::Pi();

    (*V_lepton) = nvect->PartInfo(2)->fP;
    (*V_other) = nvect->PartInfo(3)->fP.Vect();
    (*V_nu) = nvect->PartInfo(0)->fP;
    TVector3 Normal = V_nu->Vect().Unit();
    TLorentzVector FourMomTransfer = (*V_nu) - (*V_lepton);
    TVector3 FMTInPlane = FourMomTransfer.Vect();
    FMTInPlane[2] = 0;
    TVector3 FMTPerpInPlane = FMTInPlane.Unit().Cross(Normal).Unit();

    dphit = GetDeltaPhiT(V_lepton->Vect(), (*V_other), Normal);
    TVector3 dptv = GetDeltaPT(V_lepton->Vect(), (*V_other), Normal);
    dpt = dptv.Mag();
    dpty = dptv.Dot(FourMomTransfer.Vect().Unit());
    dptx = dptv.Dot(FMTPerpInPlane.Unit());
    dat = GetDeltaAlphaT(V_lepton->Vect(), (*V_other), Normal);

    // Compute Fermi momentum
    pF = sqrt(nvect->PartInfo(1)->fP.Px() * nvect->PartInfo(1)->fP.Px() +
              nvect->PartInfo(1)->fP.Py() * nvect->PartInfo(1)->fP.Py() +
              nvect->PartInfo(1)->fP.Pz() * nvect->PartInfo(1)->fP.Pz());

    //
    // Compute lepton kinematics in the target nucleon rest frame
    //
    // Compute boost velocity beta_f
    double beta_f[3];
    beta_f[0] = nvect->PartInfo(1)->fP.Px() / nvect->PartInfo(1)->fP.E();
    beta_f[1] = nvect->PartInfo(1)->fP.Py() / nvect->PartInfo(1)->fP.E();
    beta_f[2] = nvect->PartInfo(1)->fP.Pz() / nvect->PartInfo(1)->fP.E();

    // Quadri-vectors to be boosted
    TLorentzVector LV_nu(
        nvect->PartInfo(0)->fP.Px(), nvect->PartInfo(0)->fP.Py(),
        nvect->PartInfo(0)->fP.Pz(), nvect->PartInfo(0)->fP.E());
    TLorentzVector LV_lep(
        nvect->PartInfo(2)->fP.Px(), nvect->PartInfo(2)->fP.Py(),
        nvect->PartInfo(2)->fP.Pz(), nvect->PartInfo(2)->fP.E());

    LV_nu.Boost(-beta_f[0], -beta_f[1], -beta_f[2]);
    LV_lep.Boost(-beta_f[0], -beta_f[1], -beta_f[2]);

    RF_p_lep = LV_lep.Vect().Mag();
    RF_cos_theta = LV_nu.Vect().Dot(LV_lep.Vect()) /
                   (LV_lep.Vect().Mag() * LV_nu.Vect().Mag());

    double Mnuc;
    if (target == 2212) {
      Mnuc = PhysConst::mass_proton;
    } else {
      Mnuc = PhysConst::mass_neutron;
    }

    y = 1. - (LV_lep.E() / LV_nu.E());
    x = Q2 * 1.e6 / (2. * Mnuc * y * LV_nu.E());

    EnuRecQE =
        EnuQErec(p_lep / 1000.0, cos(theta_lep), EbForERecQE_MeV, pdg_lep > 0);

    PDGprimary.clear();
    PDGpostFSI.clear();
    
    PXprimary.clear();
    PYprimary.clear();
    PZprimary.clear();
    Eprimary.clear();
    PXpostFSI.clear();
    PYpostFSI.clear();
    PZpostFSI.clear();
    EpostFSI.clear();

    //WARNING
    // Loop over particles to count
    FSIMode=0; //First we want priamry aprticles
    for (int i = 2; i < nvect->Npart(); i++) 
    {
        if (FSIMode == 1 && (nvect->PartInfo(i))->fIsAlive != 1) continue;
        if (FSIMode == 0 && (nvect->ParentIdx(i)) > 2) continue;
      
        PDGprimary.push_back( (nvect->PartInfo(i))->fPID );
        PXprimary.push_back( nvect->PartInfo(i)->fP.Px() );
        PYprimary.push_back( nvect->PartInfo(i)->fP.Py() );
        PZprimary.push_back( nvect->PartInfo(i)->fP.Pz() );
        Eprimary.push_back( nvect->PartInfo(i)->fP.E() );
    }
    FSIMode=1; //Now we want post FSI particles
    for (int i = 2; i < nvect->Npart(); i++) 
    {
        if (FSIMode == 1 && (nvect->PartInfo(i))->fIsAlive != 1) continue;
        if (FSIMode == 0 && (nvect->ParentIdx(i)) > 2) continue;
      
        PDGpostFSI.push_back( (nvect->PartInfo(i))->fPID );
        PXpostFSI.push_back( nvect->PartInfo(i)->fP.Px() );
        PYpostFSI.push_back( nvect->PartInfo(i)->fP.Py() );
        PZpostFSI.push_back( nvect->PartInfo(i)->fP.Pz() );
        EpostFSI.push_back( nvect->PartInfo(i)->fP.E() );
    }

    ProcessedTree->Fill();
  } // end event loop

  // Write output to file
  ProcessedTree->Write();
  out1->Write();
  out1->Close();
}
//############################################

//####################################################
int main(int argc, char const *argv[]) {
  ParseOpts(argc, argv);

  ChainProcess();
}
//####################################################
