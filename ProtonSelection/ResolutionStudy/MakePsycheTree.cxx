#include <cstdlib>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TClonesArray.h"
#include "TFile.h"
#include "TGraph.h"
#include "TLorentzVector.h"
#include "TObjString.h"
#include "TTree.h"

#include "T2KReWeight/WeightEngines/T2KReWeightFactory.h"

#include "T2KReWeight/WeightEngines/NIWG/T2KNIWGUtils.h"

#include "AnalysisManager.hxx"
#include "AnalysisUtils.hxx"
#include "Parameters.hxx"
#include "SampleId.hxx"
#include "ToyMakerExample.hxx"
#include "ND280AnalysisUtils.hxx"

#include "Utils/NEUTCards.h"

#include "toml/toml_helper.h"

#include "TROOT.h"

using namespace t2krew;

int fNEvts = -1;
int fToys = 1;
std::string fInputFile = "";
std::string fOutputFile = "";
std::string fRunPeriod = "";
std::string fInputConfig = "";
bool data = 0;

void Usage();
void ParseArgs(int argc, char **argv);
TVector3 GetVectorInTPlane(const TVector3 &inp, const TVector3 &planarNormal); 
//KS:Checks if input file is MC, data or sand, this is automatically set to be less prone to errors
std::string GetRunType(std::string InputFile);

int main(int argc, char *argv[]) 
{
  utils::UseNEUT_DCard();
  auto T2KRW = t2krew::MakeT2KReWeightInstance(t2krew::Event::kNRooTracker);

  // Reads the input file, Run Period, and output file name from the command line.
  ParseArgs(argc, argv);

  
  Int_t MAX_VERTEX;
  if (fToys > 1) MAX_VERTEX = 5;
  else MAX_VERTEX = 1;

// Set up custom summary trees
  Int_t NVertexID;
  Int_t VertexID[MAX_VERTEX];
  Int_t NeutrinoCode[MAX_VERTEX];
  Double_t Enu[MAX_VERTEX];
  Double_t TrueNeutrinoDirX;
  Double_t TrueNeutrinoDirY;
  Double_t TrueNeutrinoDirZ;

  Int_t RunNumber;
  Int_t SubRunNumber;
  Int_t EventNumber;
  
  Int_t TrueLepPDG;
  Double_t TrueLepMom[MAX_VERTEX];
  Double_t TrueCosThetamu[MAX_VERTEX];
  Double_t TrueLepDirX;
  Double_t TrueLepDirY;
  Double_t TrueLepDirZ;
  Double_t RecoLepMom[MAX_VERTEX];
  Double_t RecoLepDirX;
  Double_t RecoLepDirY;
  Double_t RecoLepDirZ[MAX_VERTEX];

  Int_t TruePreFSIPiPDG;
  Double_t TruePreFSIPiMom;
  Double_t TruePreFSIPiDirX;
  Double_t TruePreFSIPiDirY;
  Double_t TruePreFSIPiDirZ;
  Int_t TruePostFSIPiPDG;
  Double_t TruePostFSIPiMom;
  Double_t TruePostFSIPiDirX;
  Double_t TruePostFSIPiDirY;
  Double_t TruePostFSIPiDirZ;
  Double_t RecoPiMom;
  Double_t RecoPiDirX;
  Double_t RecoPiDirY;
  Double_t RecoPiDirZ;
  Int_t RecoPi_Topo;
  
  Double_t RecoProtonMom;
  Double_t RecoProtonDirX;
  Double_t RecoProtonDirY;
  Double_t RecoProtonDirZ;
  
  Double_t RecoProtonMom_NoCorrection;
  Double_t TrueProtonMom;
  Double_t TrueProtonDirX;
  Double_t TrueProtonDirY;
  Double_t TrueProtonDirZ;
  
  Int_t RecoProton_Topo;
  Int_t sel_prot_truePDG;
  
  Double_t sel_prot_trueDpt;
  Double_t sel_prot_recoDpt;

  Double_t  POTWeight;
  Double_t  PileUpWeight;
  Int_t  isRHC;
  Int_t  passedPsyche;
  
  Int_t isSRC;
  Double_t Emiss;
  Double_t Pmiss;
  Double_t DeltaPForEMiss0;
    
  Double_t q3;
  Double_t q0;
  
  Int_t ReactionCode[MAX_VERTEX];
  Int_t NuParent[MAX_VERTEX];
  Double_t Q2[MAX_VERTEX];
  Double_t Q2QE[MAX_VERTEX];
  Bool_t HaveTruth[MAX_VERTEX];
  Int_t TgtMat[MAX_VERTEX];
  Double_t FluxWeight[MAX_VERTEX];
  Int_t TruthVtx[MAX_VERTEX];

  Int_t Run;

  // Read the parameters files following the package hierarchy
  // first the top level package. Set the parameters as fixed
  ND::params().LoadParametersFiles(anaUtils::GetPackageHierarchy(), true);

  // Make sure no parameters have been accessed yet
  ND::params().SetReadParamOverrideFilePointPassed();

  AnalysisManager _man;

  // Need to initialize the input first.
  if (!_man.input().Initialize(fInputFile.c_str(), "", false))
    return false;

  int nmax_entries = fNEvts;
  int nmax_events = -1;

  // Get the number of entries in the tree
  if (fNEvts < 0) {
    nmax_entries = (int)_man.input().GetEntries();
  } else {
    nmax_entries = std::min(nmax_entries, (int)_man.input().GetEntries());
  }

  std::cout << " We will process ";
  if (nmax_events == -1) {
    // Get the numer of events
    nmax_events = _man.input().GetNEvents(nmax_entries);
    std::cout << nmax_entries << " entries." << std::endl;
  } else
    std::cout << nmax_events << " events." << std::endl;

  
  fRunPeriod = GetRunType(fInputFile);
  Run = 0;
  if (fRunPeriod == "MC")
    Run = 1;
  else if (fRunPeriod == "sand")
    Run = -1;
  else if (fRunPeriod == "data") {
    Run = 2;
    data = true;
  } else {
    std::cout << "\nInvalid run type set\n" << std::endl;
    Usage();
    throw;
  }

  std::cout << " We are running over " << fRunPeriod << " files" << std::endl;
  std::cout << "Finished Reading tracker tree" << std::endl;

  // Start at the 0th RooTrackerVtx tree entry.
  Int_t rtvi = 0;
  Int_t prevRTV = 0;

  // Start at the 0th psyche_syst tree entry.
  Int_t systEntry = 0;
  Int_t prevSyst = 0;

  TFile *inputFile = TFile::Open(fInputFile.c_str());

  TTree *def = (TTree *)inputFile->Get("flattree");
  TTree *hdr = (TTree *)inputFile->Get("header");
  TTree *RTV = NULL;
  TTree *all_syst = NULL;
  if (!data) {
    RTV = (TTree *)inputFile->Get("NRooTrackerVtx");
    if (fToys > 1) {
      all_syst = (TTree *)inputFile->Get("all");
    }
  }

  int psycheSyst_Run = -999;
  int psycheSyst_SubRun = -999;
  int psycheSyst_EventNumber = -999;
  int psycheSyst_SelectionNom = -999;
  double psycheSyst_TrueEnuNom = -999.;
  int psycheSyst_TrueNuPDGNom = -999;
  int psycheSyst_TrueVertexIDNom = -999;
  double psycheSyst_LeptonMomNom = -999.;
  double psycheSyst_LeptonCosNom = -999.;
  double psycheSyst_WeightNom = -999.;
  double psycheSyst_FluxWeightNom = -999.;
  int psycheSyst_NToys = -999;
  int psycheSyst_TrueVertexIDToy[fToys];
  int psycheSyst_SelectionToy[fToys];
  double psycheSyst_TrueEnuToy[fToys];
  int psycheSyst_TrueNuPDGToy[fToys];
  double psycheSyst_LeptonMomToy[fToys];
  double psycheSyst_LeptonCosToy[fToys];
  double psycheSyst_WeightToy[fToys];
  double psycheSyst_FluxWeightToy[fToys];

  for (int itoy = 0; itoy > fToys; itoy++) {
    psycheSyst_TrueVertexIDToy[itoy] = -999;
    psycheSyst_SelectionToy[itoy] = -999;
    psycheSyst_TrueEnuToy[itoy] = -999.;
    psycheSyst_TrueNuPDGToy[itoy] = -999;
    psycheSyst_LeptonMomToy[itoy] = -999.;
    psycheSyst_LeptonCosToy[itoy] = -999.;
    psycheSyst_WeightToy[itoy] = -999.;
    psycheSyst_FluxWeightToy[itoy] = -999.;
  }

  TClonesArray *nRooVtxs = new TClonesArray("ND::NRooTrackerVtx", 100);
  int NRooVtx = 0;
  if (!data) {
    // RTV->GetBranch("Vtx")->SetAutoDelete(kFALSE);
    RTV->SetBranchAddress("Vtx", &nRooVtxs);
    RTV->SetBranchAddress("NVtx", &NRooVtx);

    if (fToys > 1) {
      all_syst->SetBranchAddress("Run", &psycheSyst_Run);
      all_syst->SetBranchAddress("SubRun", &psycheSyst_SubRun);
      all_syst->SetBranchAddress("EventNumber", &psycheSyst_EventNumber);
      all_syst->SetBranchAddress("SelectionNom", &psycheSyst_SelectionNom);
      all_syst->SetBranchAddress("TrueEnuNom", &psycheSyst_TrueEnuNom);
      all_syst->SetBranchAddress("TrueNuPDGNom", &psycheSyst_TrueNuPDGNom);
      all_syst->SetBranchAddress("TrueVertexIDNom", &psycheSyst_TrueVertexIDNom);
      all_syst->SetBranchAddress("LeptonMomNom", &psycheSyst_LeptonMomNom);
      all_syst->SetBranchAddress("LeptonCosNom", &psycheSyst_LeptonCosNom);
      all_syst->SetBranchAddress("WeightNom", &psycheSyst_WeightNom);
      all_syst->SetBranchAddress("FluxWeightNom", &psycheSyst_FluxWeightNom);
      all_syst->SetBranchAddress("nToys", &psycheSyst_NToys);
      all_syst->SetBranchAddress("TrueVertexIDToy", psycheSyst_TrueVertexIDToy);
      all_syst->SetBranchAddress("SelectionToy", psycheSyst_SelectionToy);
      all_syst->SetBranchAddress("TrueEnuToy", psycheSyst_TrueEnuToy);
      all_syst->SetBranchAddress("TrueNuPDGToy", psycheSyst_TrueNuPDGToy);
      all_syst->SetBranchAddress("LeptonMomToy", psycheSyst_LeptonMomToy);
      all_syst->SetBranchAddress("LeptonCosToy", psycheSyst_LeptonCosToy);
      all_syst->SetBranchAddress("WeightToy", psycheSyst_WeightToy);
      all_syst->SetBranchAddress("FluxWeightToy", psycheSyst_FluxWeightToy);
    }
  }

  TFile fout(fOutputFile.c_str(), "RECREATE");
  TTree *config = (TTree *)inputFile->Get("config");
  TTree *config1 = config->CloneTree(-1);
  fout.cd();
  config1->Write("config");

  //KS:Loop over all selection to disable them
   for (std::vector<SelectionBase*>::iterator it=_man.sel().GetSelections().begin(); it!=_man.sel().GetSelections().end();it++)
   {
    (*it)->Disable();
   }
  //KS:Now that we disable all of them we can enable only those which we have in config file
  auto const &card_toml = toml_h::parse_card(fInputConfig.c_str());
  auto const &Settings = toml_h::find(card_toml, "Settings");
  std::vector<std::string> PsycheSelections = toml_h::find<std::vector<std::string>>(Settings, "psycheSelections");
  for(unsigned int ip=0; ip < PsycheSelections.size(); ip++)
  {
    _man.sel().EnableSelection( PsycheSelections[ip].c_str() );
    std::cout<< "Adding Selection: \033[1;32m" << PsycheSelections[ip].c_str() <<"\033[0m" << std::endl;
  }
   
  TTree *enabledsampleid = new TTree("EnabledSampleID", "EnabledSampleID");
  int selectionID = -999;
  int enabledselection = 0;
  enabledsampleid->Branch("SelectionID", &selectionID, "SelectionID/I");
  enabledsampleid->Branch("IsEnabled", &enabledselection, "IsEnabled/I");
  
  for (std::vector<SelectionBase*>::iterator it=_man.sel().GetSelections().begin(); it!=_man.sel().GetSelections().end();it++)
  {
    selectionID = (*it)->GetSampleId();
    enabledselection = (*it)->IsEnabled();
    enabledsampleid->Fill();
  }
  fout.cd();
  enabledsampleid->Write();

  // We want to fill the flat-tree only with events that pass selection
  // So this gets updated when an event passes selection in loop
  // Here we only clone the structure
  TTree *def1 = def->CloneTree(0);
  // We want to fill the POT info with all the MC we have, so copy over full
  // tree Don't fill as we loop through the tree
  TTree *hdr1 = hdr->CloneTree(-1);

  TTree ssum_tree("sample_sum", "Tracker Numu Summary");

  int sNTrueVertices = 0;
  int sEvt = 0;
  def->SetBranchAddress("sEvt", &sEvt);
  def->SetBranchAddress("sNTrueVertices", &sNTrueVertices);

  Int_t NSamples = SampleId::kNSamples;
  Int_t SelectedSample = 0;
  double DetNomWeight;
  double NIWGWeightToy[fToys];
  Int_t iVertexID[fToys];

  ssum_tree.Branch("NVertexID", &NVertexID, "NVertexID/I");
  ssum_tree.Branch("MAX_VERTEX", &MAX_VERTEX, "MAX_VERTEX/I");
  ssum_tree.Branch("VertexID", VertexID, "VertexID[MAX_VERTEX]/I");
  ssum_tree.Branch("NSamples", &NSamples, "NSamples/I");
  ssum_tree.Branch("SelectedSample", &SelectedSample, "SelectedSample/I");
  ssum_tree.Branch("Run", &Run, "Run/I");

  ssum_tree.Branch("RunNumber", &RunNumber, "RunNumber/I");
  ssum_tree.Branch("SubRunNumber", &SubRunNumber, "SubRunNumber/I");
  ssum_tree.Branch("EventNumber", &EventNumber, "EventNumber/I");
  ssum_tree.Branch("DetNomWeight", &DetNomWeight, "DetNomWeight/D");

  ssum_tree.Branch("NeutrinoCode", NeutrinoCode, "NeutrinoCode[MAX_VERTEX]/I");
  ssum_tree.Branch("Enu", Enu, "Enu[MAX_VERTEX]/D");
  ssum_tree.Branch("TrueNeutrinoDirX", &TrueNeutrinoDirX, "TrueNeutrinoDirX/D");
  ssum_tree.Branch("TrueNeutrinoDirY", &TrueNeutrinoDirY, "TrueNeutrinoDirY/D");
  ssum_tree.Branch("TrueNeutrinoDirZ", &TrueNeutrinoDirZ, "TrueNeutrinoDirZ/D");

  ssum_tree.Branch("TrueLepPDG", &TrueLepPDG, "TrueLepPDG/I");
  ssum_tree.Branch("TruePmu", TrueLepMom, "TruePmu[MAX_VERTEX]/D");
  ssum_tree.Branch("TrueLepDirX", &TrueLepDirX, "TrueLepDirX/D");
  ssum_tree.Branch("TrueLepDirY", &TrueLepDirY, "TrueLepDirY/D");
  ssum_tree.Branch("TrueLepDirZ", &TrueLepDirZ, "TrueLepDirZ/D");
  ssum_tree.Branch("TrueCosThetamu", TrueCosThetamu,
                   "TrueCosThetamu[MAX_VERTEX]/D");

  ssum_tree.Branch("Pmu", RecoLepMom, "Pmu[MAX_VERTEX]/D");
  ssum_tree.Branch("RecoLepDirX", &RecoLepDirX, "RecoLepDirX/D");
  ssum_tree.Branch("RecoLepDirY", &RecoLepDirY, "RecoLepDirY/D");
  ssum_tree.Branch("RecoLepDirZ", RecoLepDirZ, "RecoLepDirZ[MAX_VERTEX]/D");
  ssum_tree.Branch("CosThetamu", RecoLepDirZ, "CosThetamu[MAX_VERTEX]/D");

  ssum_tree.Branch("TruePostFSIPiPDG", &TruePostFSIPiPDG, "TruePostFSIPiPDG/I");
  ssum_tree.Branch("TruePostFSIPiMom", &TruePostFSIPiMom, "TruePostFSIPiMom/D");
  ssum_tree.Branch("TruePostFSIPiDirX", &TruePostFSIPiDirX, "TruePostFSIPiDirX/D");
  ssum_tree.Branch("TruePostFSIPiDirY", &TruePostFSIPiDirY, "TruePostFSIPiDirY/D");
  ssum_tree.Branch("TruePostFSIPiDirZ", &TruePostFSIPiDirZ, "TruePostFSIPiDirZ/D");
  ssum_tree.Branch("TruePreFSIPiPDG", &TruePreFSIPiPDG, "TruePreFSIPiPDG/I");
  ssum_tree.Branch("TruePreFSIPiMom", &TruePreFSIPiMom, "TruePreFSIPiMom/D");
  ssum_tree.Branch("TruePreFSIPiDirX", &TruePreFSIPiDirX, "TruePreFSIPiDirX/D");
  ssum_tree.Branch("TruePreFSIPiDirY", &TruePreFSIPiDirY, "TruePreFSIPiDirY/D");
  ssum_tree.Branch("TruePreFSIPiDirZ", &TruePreFSIPiDirZ, "TruePreFSIPiDirZ/D");
  ssum_tree.Branch("RecoPiMom", &RecoPiMom, "RecoPiMom/D");
  ssum_tree.Branch("RecoPiDirX", &RecoPiDirX, "RecoPiDirX/D");
  ssum_tree.Branch("RecoPiDirY", &RecoPiDirY, "RecoPiDirY/D");
  ssum_tree.Branch("RecoPiDirZ", &RecoPiDirZ, "RecoPiDirZ/D");
  ssum_tree.Branch("RecoPi_Topo", &RecoPi_Topo, "RecoPi_Topo/I");
  
  ssum_tree.Branch("RecoProtonMom", &RecoProtonMom, "RecoProtonMom/D");
  ssum_tree.Branch("RecoProtonDirX", &RecoProtonDirX, "RecoProtonDirX/D");
  ssum_tree.Branch("RecoProtonDirY", &RecoProtonDirY, "RecoProtonDirY/D");
  ssum_tree.Branch("RecoProtonDirZ", &RecoProtonDirZ, "RecoProtonDirZ/D");
  ssum_tree.Branch("RecoProton_Topo", &RecoProton_Topo, "RecoProton_Topo/I");
  
  ssum_tree.Branch("RecoProtonMom_NoCorrection", &RecoProtonMom_NoCorrection, "RecoProtonMom_NoCorrection/D");

  ssum_tree.Branch("TrueProtonMom", &TrueProtonMom, "TrueProtonMom/D");
  ssum_tree.Branch("TrueProtonDirX", &TrueProtonDirX, "TrueProtonDirX/D");
  ssum_tree.Branch("TrueProtonDirY", &TrueProtonDirY, "TrueProtonDirY/D");
  ssum_tree.Branch("TrueProtonDirZ", &TrueProtonDirZ, "TrueProtonDirZ/D");
  
  ssum_tree.Branch("sel_prot_truePDG", &sel_prot_truePDG, "sel_prot_truePDG/I");

  ssum_tree.Branch("sel_prot_trueDpt", &sel_prot_trueDpt, "sel_prot_trueDpt/D");
  ssum_tree.Branch("sel_prot_recoDpt", &sel_prot_recoDpt, "sel_prot_recoDpt/D");

  ssum_tree.Branch("POTWeight", &POTWeight, "POTWeight/D");
  ssum_tree.Branch("PileUpWeight", &PileUpWeight, "PileUpWeight/D");
  ssum_tree.Branch("isRHC", &isRHC, "isRHC/I");
  ssum_tree.Branch("passedPsyche", &passedPsyche, "passedPsyche/I");
  
  ssum_tree.Branch("ReactionCode", ReactionCode, "ReactionCode[MAX_VERTEX]/I");
  ssum_tree.Branch("NuParent", NuParent, "NuParent[MAX_VERTEX]/I");
  ssum_tree.Branch("Q2", Q2, "Q2[MAX_VERTEX]/D");
  ssum_tree.Branch("Q2QE", Q2QE, "Q2QE[MAX_VERTEX]/D");
  ssum_tree.Branch("HaveTruth", HaveTruth, "HaveTruth[MAX_VERTEX]/B");
  ssum_tree.Branch("TgtMat", TgtMat, "TgtMat[MAX_VERTEX]/I");
  ssum_tree.Branch("FluxWeight", FluxWeight, "FluxWeight[MAX_VERTEX]/D");
  ssum_tree.Branch("TruthVtx", TruthVtx, "TruthVtx[MAX_VERTEX]/I");

  ssum_tree.Branch("q3", &q3, "q3/D");
  ssum_tree.Branch("q0", &q0, "q0/D");
  
  ssum_tree.Branch("isSRC", &isSRC, "isSRC/I");
  ssum_tree.Branch("Emiss", &Emiss, "Emiss/D");
  ssum_tree.Branch("Pmiss", &Pmiss, "Pmiss/D");
  ssum_tree.Branch("DeltaPForEMiss0", &DeltaPForEMiss0, "DeltaPForEMiss0/D");
  
  
  ssum_tree.Branch("T2KRW_nToys", &fToys, "T2KRW_nToys/I");
  ssum_tree.Branch("T2KRW_NIWGWeightToy", NIWGWeightToy,
                   "T2KRW_NIWGWeightToy[T2KRW_nToys]/D");
  ssum_tree.Branch("Toy_TrueEnuNom", &psycheSyst_TrueEnuNom,
                   "psycheSyst_TrueEnuNom/D");
  ssum_tree.Branch("Toy_TrueVertexID", psycheSyst_TrueVertexIDToy,
                   "psycheSyst_TrueVertexIDToy[T2KRW_nToys]/I");
  ssum_tree.Branch("Toy_Selection", psycheSyst_SelectionToy,
                   "psycheSyst_SelectionToy[T2KRW_nToys]/I");
  ssum_tree.Branch("Toy_iVertexID", iVertexID,
                   "psycheSyst_iVertexID[T2KRW_nToys]/I");
  ssum_tree.Branch("Toy_LeptonMom", psycheSyst_LeptonMomToy,
                   "psycheSyst_LeptonMomToy[T2KRW_nToys]/D");
  ssum_tree.Branch("Toy_LeptonCos", psycheSyst_LeptonCosToy,
                   "psycheSyst_LeptonCosToy[T2KRW_nToys]/D");
  ssum_tree.Branch("Toy_DetWeight", psycheSyst_WeightToy,
                   "psycheSyst_WeightToy[T2KRW_nToys]/D");

  int evtNumber = -1;
  int lastRunFound = -1;

  inputFile->cd();

  // Save the index of the last selected event
  int last_event_selected = -1;

  // Set a ToyMaker to configure the toy experiment. Initialize it with a random
  // seed. Apply variation if throwing toys.
  bool zero_var = true;
  ToyMaker *toyMaker =
      new ToyMakerExample((UInt_t)ND::params().GetParameterI(
        "psycheSteering.Systematics.RandomSeed"), zero_var);

  // Create and fill the Toy experiment with the appropriate format (number of
  // systematics and number of parameters for each systematic)
  toyMaker->CreateToyExperiments(1, _man.syst().GetSystematics());

  // Create the array of PreviousToyBox
  _man.sel().CreateToyBoxArray(nmax_events);

  // Create the array of SystBox
  _man.syst().Initialize(_man.sel(), nmax_events);

  int test_iterator = 0;
  Long64_t entry = 0;
  Int_t evt = 0;
  int ProcessEntries =
      (nmax_entries > nmax_events ? nmax_entries : nmax_events);

  int npassed = 0;
  while (entry < ProcessEntries) {
    if (entry % (1000) == 0) {
      std::cout << "Processed "
                << 100. * ((double)entry) / ((double)ProcessEntries) << "% -> "
                << entry << " entries out of "
                << (nmax_entries > nmax_events ? nmax_entries : nmax_events)
                << std::endl;
    }

    Weight_h totalWeightSyst;
    Weight_h fluxWeightSyst;

    int q = int(entry);

    def->GetEntry(q);
    hdr->GetEntry(q);
    config->GetEntry(q);

    // Fill the event structure
    if (!_man.LoadEvent(entry)) continue;

    // Get the event to be modified. This is the only one used in the analysis
    AnaEventB *event = static_cast<AnaEventB *>(_man.input().GetSuperEvent().Event);

    // Fill the EventBox
    _man.sel().InitializeEvent(*event);

    // Initialize The SystBox for variation systematics
    _man.syst().InitializeEventSystematics(_man.sel(), *event);

    // Get event number
    evtNumber = event->EventInfo.Event;

    std::set<int> samples;

    // Set default values
    for (int sample = 0; sample < MAX_VERTEX; ++sample) {


      VertexID[sample] = -999;
      NeutrinoCode[sample] = -999;
      Enu[sample] = -999;

      TrueLepMom[sample] = -999;
      TrueCosThetamu[sample] = -999;

      RecoLepDirZ[sample] = -999;
      RecoLepMom[sample] = -999;

      ReactionCode[sample] = -999;
      NuParent[sample] = -999;
      Q2[sample] = -999;
      Q2QE[sample] = -999;
      HaveTruth[sample] = false;
      TgtMat[sample] = -999;
      FluxWeight[sample] = -999;
      TruthVtx[sample] = -999;
    }

    for (int iToy = 0; iToy < fToys; iToy++) {
      NIWGWeightToy[iToy] = -999;
      iVertexID[iToy] = -999;
      // psycheSyst_TrueVertexIDToy [iToy] = -999;
      // psycheSyst_LeptonMomToy    [iToy] = -999;
      // psycheSyst_LeptonCosToy    [iToy] = -999;
      // psycheSyst_WeightToy       [iToy] = -999;
    }

    TrueNeutrinoDirX = -999;
    TrueNeutrinoDirY = -999;
    TrueNeutrinoDirZ = -999;

    TrueLepPDG = -999;
    TrueLepDirX = -999;
    TrueLepDirY = -999;
    TrueLepDirZ = -999;
    RecoLepDirX = -999;
    RecoLepDirY = -999;

    TruePostFSIPiPDG = -999;
    TruePostFSIPiMom = -999;
    TruePostFSIPiDirX = -999;
    TruePostFSIPiDirY = -999;
    TruePostFSIPiDirZ = -999;
    TruePreFSIPiPDG = -999;
    TruePreFSIPiMom = -999;
    TruePreFSIPiDirX = -999;
    TruePreFSIPiDirY = -999;
    TruePreFSIPiDirZ = -999;
    RecoPiMom = -999;
    RecoPiDirX = -999;
    RecoPiDirY = -999;
    RecoPiDirZ = -999;
    RecoPi_Topo = -999;
    
    RecoProtonMom = -999;
    RecoProtonDirX = -999;
    RecoProtonDirY = -999;
    RecoProtonDirZ = -999;
    
    RecoProtonMom_NoCorrection = -999;
    TrueProtonMom = -999;
    TrueProtonDirX = -999;
    TrueProtonDirY = -999;
    TrueProtonDirZ = -999;
    
    sel_prot_truePDG = -999;
    RecoProton_Topo = -999;
    
    isSRC = -999;
    Emiss = -999;
    Pmiss =  -999;
    DeltaPForEMiss0 = 999; //KS: For this better to give crazy high value as MaCh3 look for std::min(ebshift,deltap) 
    
    q0 =  -999;
    q3 =  -999;
    
    DetNomWeight = -999;
    POTWeight = -999;
    PileUpWeight = -999;
    isRHC = -999;
    passedPsyche = -999;
    
    //  Gets the ToyExperiment with index itoy from the ToyMaker
    ToyExperiment *toy = toyMaker->GetToyExperiment(0);

    bool passed =
        _man.ProcessEvent(*toy, *event, totalWeightSyst, fluxWeightSyst);
    
    DetNomWeight = (double)totalWeightSyst.Correction;
    passedPsyche = (bool)passed;
    POTWeight = 0;
    isRHC = anaUtils::IsRHC(event->EventInfo.Run);
    PileUpWeight = event->Weight;
    
    RunNumber = event->EventInfo.Run;
    SubRunNumber = event->EventInfo.SubRun;
    EventNumber = event->EventInfo.Event;
    
    AnaEventSummaryB *summary = static_cast<AnaEventSummaryB *>(event->Summary);
    // Generated skimmed spline files -> only save events if something passes
    // one of the psyche selections If not, reset the event containers
    if (!passed) {
      // Delete the SystBox array
      _man.syst().FinalizeEventSystematics(*event);
      // Reset the PreviousToyBox
      _man.sel().FinalizeEvent(*event);
      evt++;
      continue;
    } else if (samples.find(int(summary->EventSample)) != samples.end())
      continue;
    else
      samples.insert(int(summary->EventSample));
    npassed++;

    if (!data) {

      SelectedSample = summary->EventSample;

      if (summary->TrueVertex[SelectedSample] == NULL) {
        std::cerr << "weird error, the event has been selected but doesn't "
                     "have true vertex"<< std::endl;
      }

      if (fToys > 1) {
        // Find corresponding psyche systematic entry
        bool psycheSyst_found = false;
        bool new_run = lastRunFound != event->EventInfo.Run;
        prevSyst = systEntry;
        while (!psycheSyst_found) {
          all_syst->GetEntry(systEntry);
          if (psycheSyst_EventNumber == event->EventInfo.Event &&
              psycheSyst_TrueVertexIDNom ==
                  static_cast<AnaParticleMomB *>(
                      summary->LeptonCandidate[summary->EventSample])
                      ->GetTrueParticle()
                      ->VertexID &&
              fabs(psycheSyst_TrueEnuNom -
                   (Double_t)(
                       summary->TrueVertex[summary->EventSample]->NuEnergy)) < 0.1
              //&&
              // psycheSyst_Run == event->EventInfo.Run &&
              // psycheSyst_SubRun == event->EventInfo.SubRun
          ) {
            psycheSyst_found = true;
            lastRunFound = event->EventInfo.Run;
            break;
          }
          if (psycheSyst_EventNumber > evtNumber && !new_run) {
            break;
          }
          if (!psycheSyst_found)
            systEntry++;
          if (systEntry == all_syst->GetEntries())
            systEntry = 0;
          if (systEntry == prevSyst - 1)
            break;
        }
        if (!psycheSyst_found) {
          std::cout << "No psyche syst entry found" << std::endl;
          // Delete the SystBox array
          _man.syst().FinalizeEventSystematics(*event);
          // Reset the PreviousToyBox
          _man.sel().FinalizeEvent(*event);
          evt++;
          continue;
        }
        test_iterator++;
      }
      NVertexID = 0;
      // Loop through toys
      for (int itoy = 0; itoy < fToys; itoy++) {

        iVertexID[itoy] = 0;

        if (fToys > 1) {
          // Skip if no true vertex from psyche systematic throwing
          if (psycheSyst_TrueVertexIDToy[itoy] == -999) {
            continue;
          }

          // If first valid throw increment number of vertices and store vertex ID
          if (NVertexID == 0) {
            NVertexID++;
            VertexID[0] = psycheSyst_TrueVertexIDToy[itoy];
          }

          // Look through vertices to see if this one has already been used
          bool found_vertex = false;
          for (int i = 0; i < NVertexID; i++) {
            // std::cout << "VertexID[i]: " << VertexID[i] << std::endl;
            if (VertexID[i] == psycheSyst_TrueVertexIDToy[itoy]) {
              iVertexID[itoy] = i;
              found_vertex = true;
              break;
            }
          }
          // If this is a new vertex ID use next index
          if (!found_vertex) {
            VertexID[NVertexID] = psycheSyst_TrueVertexIDToy[itoy];
            iVertexID[itoy] = NVertexID;
            NVertexID++;
          }
          // Skip if already found truth
          if (HaveTruth[iVertexID[itoy]] == true) continue;
        }
        // If not toy throwing need to store that there is only one vertex ID
        else {
          NVertexID = 1;
        }

        int sample = int(summary->EventSample);

        if (summary->TrueVertex[SelectedSample] != NULL) {
          // Save stuff
          AnaParticleMomB *leptonCandidate = static_cast<AnaParticleMomB *>(
              summary->LeptonCandidate[summary->EventSample]);

          RecoLepMom[iVertexID[itoy]] = leptonCandidate->Momentum;
          RecoLepDirX = leptonCandidate->DirectionStart[0];
          RecoLepDirY = leptonCandidate->DirectionStart[1];
          RecoLepDirZ[iVertexID[itoy]] = leptonCandidate->DirectionStart[2];
            
          if (leptonCandidate->GetTrueParticle()) 
          {
            TrueLepPDG = leptonCandidate->GetTrueParticle()->PDG;
            TruthVtx[iVertexID[itoy]] = leptonCandidate->GetTrueParticle()->VertexID;
          }
          
          AnaParticleMomB* PionCandidate = dynamic_cast<AnaParticleMomB*>(summary->PionCandidate[summary->EventSample]);
          RecoPi_Topo = summary->SelPionTopo[SelectedSample];
          
          if (PionCandidate != NULL)
          {
                //This way we get pion momentum with correction
                RecoPiMom = (summary->PionMomentum[summary->EventSample]); 
                RecoPiDirX = PionCandidate->DirectionStart[0];
                RecoPiDirY = PionCandidate->DirectionStart[1];
                RecoPiDirZ = PionCandidate->DirectionStart[2];
          }
          
          AnaParticleMomB* ProtonCandidate = dynamic_cast<AnaParticleMomB*>(summary->ProtonCandidate[summary->EventSample]);
          RecoProton_Topo = summary->SelProtonTopo[SelectedSample];

          if (ProtonCandidate != NULL)
          {
                //This way we get proton momentum with correction
                RecoProtonMom = (summary->ProtonMomentum[summary->EventSample]); 
                RecoProtonDirX = ProtonCandidate->DirectionStart[0];
                RecoProtonDirY = ProtonCandidate->DirectionStart[1];
                RecoProtonDirZ = ProtonCandidate->DirectionStart[2];
                
                RecoProtonMom_NoCorrection = ProtonCandidate->Momentum;
                
                TVector3 NuP(-0.0128224, -0.0249785, 0.999586);        
                Float_t selmuMom = leptonCandidate->Momentum;
                
                Float_t selmuDis[3] = {-999};
                
                anaUtils::CopyArray(leptonCandidate->DirectionStart, selmuDis, 3);
                
                TVector3 V_leptonReco(selmuDis[0]*selmuMom, selmuDis[1]*selmuMom, selmuDis[2]*selmuMom);
            
                TVector3 V_otherReco(RecoProtonDirX*RecoProtonMom,RecoProtonDirY*RecoProtonMom,RecoProtonDirZ*RecoProtonMom);
                
                TVector3 V_lepton_TReco = GetVectorInTPlane(V_leptonReco, NuP);
                TVector3 V_other_TReco = GetVectorInTPlane(V_otherReco, NuP);
        
                TVector3 dptReco = V_lepton_TReco + V_other_TReco;
                
                sel_prot_recoDpt = dptReco.Mag();
                
                if(  leptonCandidate->GetTrueParticle() && ProtonCandidate->GetTrueParticle()) 
                {
                    Float_t selmuTruemom = leptonCandidate->GetTrueParticle()->Momentum;
                    Float_t selmuTrueDis[3] = {-999};
                    anaUtils::CopyArray(leptonCandidate->GetTrueParticle()->Direction, selmuTrueDis, 3);
                    
                    TrueProtonMom = ProtonCandidate->GetTrueParticle()->Momentum;
                    TrueProtonDirX = ProtonCandidate->GetTrueParticle()->Direction[0];
                    TrueProtonDirY = ProtonCandidate->GetTrueParticle()->Direction[1];
                    TrueProtonDirZ = ProtonCandidate->GetTrueParticle()->Direction[2];
                                    
                    ///////////////////
                    TVector3 V_leptonTrue(selmuTrueDis[0]*selmuTruemom, selmuTrueDis[1]*selmuTruemom, selmuTrueDis[1]*selmuTruemom);
                
                    TVector3 V_otherTrue(TrueProtonDirX*TrueProtonMom,TrueProtonDirY*TrueProtonMom,TrueProtonDirZ*TrueProtonMom);
                    
                    TVector3 V_lepton_Ttrue = GetVectorInTPlane(V_leptonTrue, NuP);
                    TVector3 V_other_Ttrue = GetVectorInTPlane(V_otherTrue, NuP);
            
                    TVector3 dptTrue = V_lepton_Ttrue + V_other_Ttrue;
                    sel_prot_trueDpt = dptTrue.Mag();
                    
                    sel_prot_truePDG = ProtonCandidate->GetTrueParticle()->PDG;
                }
            }
            //NOW BONKERS SUMMARY
            
            
    
          int id = summary->TrueVertex[SelectedSample]->ID;
          if (TruthVtx[iVertexID[itoy]] != id) {
            std::cerr << "WARNING: TruthVtx[" << iVertexID[itoy] << "]("
                      << TruthVtx[iVertexID[itoy]]
                      << ") != event->Summary->TrueVertex[sample]->ID (" << id
                      << ")" << std::endl;
            std::cerr << "MACH3 and BANFF wont agree!!" << std::endl;
            throw;
          }
        }

        ND::NRooTrackerVtx *vtx = NULL;

        int flavor = -999;
        (void)flavor;
        FluxWeight[iVertexID[itoy]] = 1.0;
        Double_t weight = 1.0;

        if (RecoLepMom[iVertexID[itoy]] < 0)
          continue;

        if (psycheSyst_SelectionToy[itoy] <= SampleId::kUnassigned && fToys > 1)
          continue;

        // Pull out the correct RooTrackerVtx tree entry.
        if (psycheSyst_TrueVertexIDToy[itoy] != -999 && fToys > 1) {
          prevRTV = rtvi;
          while (vtx == NULL) {
            RTV->GetEntry(rtvi);
            // Use the TruthVertexID to get the RooTrackerVertex corresponding
            // to this event.
            for (int i = 0; i < NRooVtx; ++i) {
              vtx = (ND::NRooTrackerVtx *)(*nRooVtxs)[i];
              if (vtx->TruthVertexID == psycheSyst_TrueVertexIDToy[itoy] &&
                  fabs(vtx->StdHepP4[0][3] * 1000 -
                       psycheSyst_TrueEnuToy[itoy]) < 0.1) {
                break;
              }
              vtx = NULL;
            }
            if (vtx == NULL) rtvi++;
            if (rtvi == RTV->GetEntries()) {
              std::cout << "Looping to find correct vertex Toy" << itoy
                        << ". VtxID: " << psycheSyst_TrueVertexIDToy[itoy]
                        << std::endl;
              rtvi = 0;
            }
            if (rtvi == prevRTV - 1) {
              std::cout << "Event failed to find ANY vertex Toy" << itoy
                        << ". VtxID: " << psycheSyst_TrueVertexIDToy[itoy]
                        << std::endl;
              break;
            }
          }
        } else if (fToys == 1) {
          int rtv_entries = RTV->GetEntries();
          if (TruthVtx[iVertexID[itoy]] > -1) {
            int rtv_curr = rtvi;
            while (vtx == NULL) {
              RTV->GetEntry(rtvi);
              // Use the TruthVertexID to get the RooTrackerVertex corresponding
              // to this event.
              for (int i = 0; i < NRooVtx; ++i) {
                vtx = (ND::NRooTrackerVtx *)nRooVtxs->At(i);
                if (vtx->TruthVertexID == TruthVtx[iVertexID[itoy]] &&
                    fabs(vtx->StdHepP4[0][3] * 1000 -
                         summary->TrueVertex[sample]->NuEnergy) < 0.1)
                  break;
                vtx = NULL;
              }
              if (vtx == NULL)
                rtvi++;
              if (rtvi == rtv_entries) {
                rtvi = rtv_curr;
                break;
              }
            }
          }
        }
        bool vtx_match = true;
        // If there is no RooTrackerVertex, or we are looking at sand events,
        // set it all to nominal
        if (vtx == NULL || Run == -1) {
          std::cout << "Cannot find NRooTrackerVtx object - skipping weight "
                       "for this vertex!" << std::endl;
          vtx_match = false;
        } else {
          auto t2krewev = t2krew::Event::Make(vtx);
          // Save the truth information
          ReactionCode[iVertexID[itoy]] =
              atoi(((vtx->EvtCode)->String()).Data());
          NeutrinoCode[iVertexID[itoy]] = 0;
          if (vtx->NuParentDecMode < 20) {
            NeutrinoCode[iVertexID[itoy]] = 14;
            flavor = 0;
          } else if (vtx->NuParentDecMode < 30) {
            NeutrinoCode[iVertexID[itoy]] = -14;
            flavor = 1;
          } else if (vtx->NuParentDecMode < 40) {
            NeutrinoCode[iVertexID[itoy]] = 12;
            flavor = 2;
          } else if (vtx->NuParentDecMode < 50) {
            NeutrinoCode[iVertexID[itoy]] = -12;
            flavor = 3;
          }
          Enu[iVertexID[itoy]] = vtx->StdHepP4[0][3];
          // This branch of the summary tree is used to make sure events are
          // matched to the truth in psycheInterface Enu can change depending on
          // the vertex selected by the toy throws Need to set if no toys are
          // thrown
          if (fToys == 1) psycheSyst_TrueEnuNom = vtx->StdHepP4[0][3] * 1000.0;
          
          FluxWeight[iVertexID[itoy]] = fluxWeightSyst.Correction;

          auto niwgev = t2krew::NIWGUtils::MakeNIWGEvent(t2krewev);

          TVector3 nu = niwgev.part_stack[niwgev.nu_index].p.Vect();
          TVector3 mu = niwgev.part_stack[niwgev.fslep_index].p.Vect();
          //KS:SF works only for CCQE, Emiss/Pmiss calcualtion works only on C and O
          if(abs(niwgev.neutmode)==1 && (niwgev.targetA == 12 || niwgev.targetA == 16) )
          {
                isSRC = niwgev.isSRC;
                Emiss = 1000*niwgev.Emiss; //Converts to MeV
                Pmiss = 1000*niwgev.Pmiss; //Converts to MeV
                //KS: This is used to get limits for 2D Eb shift        
                DeltaPForEMiss0 = 1000 * niwgev.GetDeltaPForEMiss0();  //Converts to MeV
          }
    
          TrueLepMom[iVertexID[itoy]] = mu.Mag();
          TrueLepDirX = mu.X() / mu.Mag();
          TrueLepDirY = mu.Y() / mu.Mag();
          TrueLepDirZ = mu.Z() / mu.Mag();
          TrueNeutrinoDirX = nu.X() / nu.Mag();
          TrueNeutrinoDirY = nu.Y() / nu.Mag();
          TrueNeutrinoDirZ = nu.Z() / nu.Mag();
          double costheta_lep = mu.Unit().Dot(nu.Unit());
          TrueCosThetamu[iVertexID[itoy]] = costheta_lep;
          //KS: We need q3 for correction to Eb, since Eb is in MeV,
          //it is better to convert it here
          q3 =  niwgev.q3 * 1000; //Converts to MeV
          q0 =  niwgev.q0 * 1000; //Converts to MeV
          Q2[iVertexID[itoy]] = niwgev.Q2;
          Q2QE[iVertexID[itoy]] =
              niwg::Q2QErec(vtx->StdHepP4[niwgev.fslep_index][3], mu.Mag(),
                            costheta_lep, 0, niwgev.neutmode > 0);
          TgtMat[iVertexID[itoy]] = niwgev.targetA;
          NuParent[iVertexID[itoy]] = vtx->NuParentPdg;
          int reac = TMath::Abs(ReactionCode[iVertexID[itoy]]);

          for (int ipart = 0; ipart < vtx->NEnvc; ++ipart) {
            if (TMath::Abs(vtx->NEipvc[ipart]) != 211 &&
                TMath::Abs(vtx->NEipvc[ipart]) != 111) continue;
            TVector3 pi(vtx->NEpvc[ipart][0], vtx->NEpvc[ipart][1],
                        vtx->NEpvc[ipart][2]);

            if (vtx->NEicrnvc[ipart] == 1 &&
                pi.Mag() > TruePostFSIPiMom) { // the pion exits the nucleus
                                               // (takes the most energetic)
              TruePostFSIPiPDG = vtx->NEipvc[ipart];
              TruePostFSIPiMom = pi.Mag();
              TruePostFSIPiDirX = pi.X() / pi.Mag();
              TruePostFSIPiDirY = pi.Y() / pi.Mag();
              TruePostFSIPiDirZ = pi.Z() / pi.Mag();
            }
            if (vtx->NEiorgvc[ipart] - 1 == 1 &&
                pi.Mag() > TruePreFSIPiMom) { // take the one whose parent is
                                              // the initial state (primary)
              TruePreFSIPiPDG = vtx->NEipvc[ipart];
              TruePreFSIPiMom = pi.Mag();
              TruePreFSIPiDirX = pi.X() / pi.Mag();
              TruePreFSIPiDirY = pi.Y() / pi.Mag();
              TruePreFSIPiDirZ = pi.Z() / pi.Mag();
            }
          }

          // Calculate the NIWG weight
          NIWGWeightToy[itoy] = T2KRW->CalcWeight(t2krewev);
          if (NIWGWeightToy[itoy] > 100 || NIWGWeightToy[itoy] < 0) {
            std::cout << "NIWGWeightToy[" << itoy
                      << "] = " << NIWGWeightToy[itoy] << " setting it to 1."
                      << std::endl;
            NIWGWeightToy[itoy] = 1;
          }
        }

        HaveTruth[iVertexID[itoy]] = true;
        if (!vtx_match) {
          std::cout << "Could not match NRooTrackerVtx" << std::endl;
          HaveTruth[iVertexID[itoy]] = false;
        }
        // break;
      } // for itoy
    }   // if !data

    // Fill summary tree
    bool selected = false;
    if (data) {
      selected = true;
    } else {
      for (int i = 0; i < MAX_VERTEX; ++i) {
        if (TruthVtx[i] > -1)
          selected = true;
      }
    }

    // sNTrueVertices == 0 can be zero if there are no events in the first bunch
    // We may still have selected an event in a later bunch
    if (sNTrueVertices == 0 && selected && !data) {
      // Remember the current event number in the file
      int currEventNum = evtNumber;
      int count = 1;
      while (currEventNum == evtNumber) {
        // The event number saved in the file
        def->GetEntry(q - count);
        currEventNum = sEvt;
        // Check the entry before this event to see if it contains any true
        // vertices Make sure the event number matches our event number
        if (sNTrueVertices > 0 && currEventNum == evtNumber) {
          // Make sure we aren't double counting earlier events
          if ((q - count) <= last_event_selected)
            break;
          def1->Fill();
          ssum_tree.Fill();
          break;
        }
        // Check the next event down (read q-count-1)
        count++;
      }
      // Go back to reading our original entry
      def->GetEntry(q);
    }

    if (selected) {
      // Update which event we last selected
      last_event_selected = q;
      // Fill the event
      def1->Fill();
      if (!data) {
        ssum_tree.Fill();
      }
    }
    // Delete the SystBox array
    _man.syst().FinalizeEventSystematics(*event);

    // Reset the PreviousToyBox
    _man.sel().FinalizeEvent(*event);

    evt++;
  } // number of events
  std::cout << "Event loop done!!" << std::endl;
  std::cout << npassed << " events passed" << std::endl;

  fout.cd();

  if (!data)
    ssum_tree.Write("sample_sum");
  def1->Write("flattree");
  hdr1->Write("header");
  fout.Close();

  inputFile->Close();
  return 0;
}

// Print the cmd line syntax
void Usage() {
  std::cout << "Cmd line syntax should be:" << std::endl;
  std::cout << "ND280GenWeights -i flat-tree [data/mc/sand] -o outputfile -c config file [-n n_events = -1 splines = 1 -t n_toys = 1]" << std::endl;
  std::cout << "flat tree is standard ND280 input." << std::endl;
  std::cout << "outputfile is the desired name of the output file." << std::endl;
  std::cout << "example of config file you can find in <OAGenWeightsApps_path>/app/Configs"<< std::endl;
  std::cout << "n_events is the number of events to process - if this is not "
               "set the whole input file will be processed."<< std::endl;
}

// Messy way to process cmd line arguments.
void ParseArgs(int argc, char **argv) {
  int nargs = 1;

  if (argc < (nargs * 2 + 1)) {
    Usage();
    exit(1);
  }
  for (int i = 1; i < argc; i += 2) {
    if (std::string(argv[i]) == "-i")
      fInputFile = argv[i + 1];
    else if (std::string(argv[i]) == "-o")
      fOutputFile = argv[i + 1];
    else if (std::string(argv[i]) == "-c")
      fInputConfig = argv[i + 1];
    else if (std::string(argv[i]) == "-n")
      fNEvts = atoi(argv[i + 1]);
    else if (std::string(argv[i]) == "-t")
      fToys = atoi(argv[i + 1]);

    else {
      std::cout << "Invalid argument:" << argv[i] << " " << argv[i + 1]
                << std::endl;
      Usage();
      exit(1);
    }
  }
  // Final idiot proof check
  if (std::string(fInputFile) == "" || std::string(fOutputFile) == ""
    || std::string(fInputConfig) == "") {
    Usage();
    exit(1);
  }
  //KS:Check if input file exist
  //maybe add some utils.h where such stuff will be
  std::ifstream infile(fInputFile.c_str());
  if (!infile.good()) {
    std::cerr << "*** ERROR ***" << std::endl;
    std::cerr << "Input file " << fInputFile << " does not exist" << std::endl;
    std::cerr << "Please try again" << std::endl;
    std::cerr << "*************" << std::endl;
    throw;
  }
   //KS:Check if config file exist
  std::ifstream inConf(fInputConfig.c_str());
  if (!inConf.good()) {
    std::cerr << "*** ERROR ***" << std::endl;
    std::cerr << "Config file " << fInputConfig << " does not exist" << std::endl;
    std::cerr << "Please try again" << std::endl;
    std::cerr << "*************" << std::endl;
    throw;
  }
  
}
//KS:Checks if input file is MC, data or sand, this is automatically set to be less prone to errors
std::string GetRunType(std::string InputFile)
{
    TFile *FileIn = new TFile(InputFile.c_str(), "READ");
    TTree* flattree = (TTree*)FileIn->Get("flattree"); 
    
    int isMC;
    int isSand;
    
    flattree->SetBranchAddress("sIsMC", &isMC);
    flattree->SetBranchAddress("sIsSand", &isSand);
    flattree->GetEntry(0);
    std::string tempRunPeriod = "";

    if(isMC == 1 && isSand == 0) tempRunPeriod  = "MC";
    if(isMC == 1 && isSand == 1) tempRunPeriod  = "sand";
    //KS:Some data flat-trees have isSand = true be carefull with using isSand for data
    if(isMC == 0) tempRunPeriod  = "data";
    return tempRunPeriod;
}


TVector3 GetVectorInTPlane(const TVector3 &inp, const TVector3 &planarNormal) 
{
  TVector3 pnUnit = planarNormal.Unit();
  double inpProjectPN = inp.Dot(pnUnit);

  TVector3 InPlanarInput = inp - (inpProjectPN * pnUnit);
  return InPlanarInput;
}
