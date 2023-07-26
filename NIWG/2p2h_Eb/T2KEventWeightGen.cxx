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
#include "TChain.h"
#include "neutvect.h"

#include "T2KReWeight/WeightEngines/T2KReWeightFactory.h"
#include "T2KReWeight/WeightEngines/NIWG/T2KNIWGUtils.h"
#include "T2KReWeight/WeightEngines/NEUT/T2KNEUTReWeight.h"
#include "T2KReWeight/WeightEngines/NEUT/T2KNEUTUtils.h"

#include "NIWG/Utils/InteractionUtils.h"

#include "toml/toml_helper.h"

#include "TROOT.h"

using namespace t2krew;

int fNEvts = -1;
int fToys = 1;
std::string fInputFile = "";
std::string fOutputFile = "";
std::string fRunPeriod = "";
std::string fInputConfig = "";
bool data = false;

void Usage();
void ParseArgs(int argc, char **argv);

int main(int argc, char *argv[])
{
  // Reads the input file, Run Period, and output file name from the command line.
  ParseArgs(argc, argv);
  auto const &card_toml = toml_h::parse_card(fInputConfig.c_str());

  //KS:Load additional informations from config, like whether to use mirroring
  //some addtional informations for psyche and neut card name
  auto const &Settings = toml_h::find(card_toml, "Settings");
  std::string NeutCardName = toml_h::find<std::string>(Settings, "NeutCard");
  t2krew::T2KNEUTUtils::SetCardFile(NeutCardName);
  auto T2KRW = t2krew::MakeT2KReWeightInstance(t2krew::Event::Event::kNEUT);

  std::vector<std::vector<float>> dial_values;
  std::vector<t2krew::T2KSyst_t> dials;
  std::vector<std::string> dial_names;
  std::vector<TClonesArray *> dial_graphs;

  std::vector<double> fromValue_vec;
  std::vector<double> OneTurn_vec;


  Int_t MAX_VERTEX = 1;

  auto const &reweights = toml_h::find(card_toml, "reweights");

  // Loop over the dials in setup
  for (auto const &dg :toml_h::find<std::vector<std::string>>(reweights, "dials")) {

    // Search through the settings for matching dials
    for (auto const &d : toml_h::find<toml::array>(reweights, dg)) {
      auto tweak_name = toml_h::find<std::string>(d, 0);
      auto tweak_values = toml_h::find<std::vector<double>>(d, 1);

      auto unitconv = toml_h::find<std::string>(d, 2);

      if (unitconv != "sig" && unitconv != "abs")
      {
          std::cerr << "Third argument of "<< tweak_name << " doesn't have valid dial type: " << unitconv << std::endl;
          std::cerr << "Should be \"sig\" or \"abs\"" << std::endl;
          throw;
      }

      dials.push_back(T2KRW->DialFromString(tweak_name));
      dial_names.push_back(dg);
      std::vector<float> temp_vec;
      //KS: Knots in units of sigma
      if (unitconv == "sig")
      {
        double TempFromValue = T2KRW->GetDial_From_Value(dials.back());
        double TempOneTurn = T2KRW->GetDial_OneTurn(dials.back(),1);

        //Some dials don't have defined error, in such case we take 1
        if(TempOneTurn == 0) TempOneTurn=1;

        //Pion FSI can get crazy weights, for more details see above note by: JW 20200124
        for (auto t : tweak_values) {
          temp_vec.push_back( TempFromValue+TempOneTurn*t );
        }
      }
      //KS: Knots in absolute values
      else if(unitconv == "abs")
      {
        for (auto t : tweak_values)
        {
            double TempTweak = t;
            temp_vec.push_back(TempTweak);
        }
       }
      dial_values.push_back(temp_vec);
      TClonesArray *temp_graph = new TClonesArray("TGraph", MAX_VERTEX);
      dial_graphs.push_back(temp_graph);
    }
  }
  for (unsigned int sys_iter = 0; sys_iter < dial_names.size(); sys_iter++)
  {
    fromValue_vec.push_back(T2KRW->GetDial_From_Value(dials[sys_iter]));
    OneTurn_vec.push_back(T2KRW->GetDial_OneTurn(dials[sys_iter],1));
  }

  //This will print useful information for all loaded dials
  std::cout<<"****************DIAL SETUP****************"<<std::endl;
  for (unsigned int sys_iter = 0; sys_iter < dial_names.size(); sys_iter++)
  {
    std::cout<<sys_iter<<" "<<"\033[1;32m"<<dial_names[sys_iter]<<"\033[0m" <<" FromValue "<<fromValue_vec[sys_iter]<<" OneTurn "<<OneTurn_vec[sys_iter]<<std::endl;
    std::cout<<"\033[1;34m Knots \033[0m";
    for(size_t dial_iter = 0; dial_iter < dial_values[sys_iter].size(); dial_iter++)
    {
      std::cout<<" "<< dial_values[sys_iter][dial_iter]<<" ";
    }
    std::cout<<std::endl;
  }

  std::cout<<"*******************************************"<<std::endl;

  int Mode;
  int PDGHMFSNuc;
  int PDGSRCnonSpcNuc;
  int PDGHMPrimaryNuc;

  // Basic interaction kinematics
  /*
  TLorentzVector *PISNu;
  TLorentzVector *PFSLep;
  TLorentzVector *PHMFSNuc;
  TLorentzVector *PSRCnonSpcNuc;
  TLorentzVector *PHMPrimaryNuc;
  */
  double Q2;
  double q0;
  double q3;
  double Emiss;
  double Pmiss;
  int   isSRC;

  int NFSprot;
  int NFSneut;

  int NToChase;

  double weight;
  double Enu;
  double EnuQErec;
  double kERecQEBias;

  double PFSLep;
  double CosFSLep;

  double HMprotonMom;
  double HMprotonTheta;

  double HMneutronMom;
  double HMneutronTheta;


  std::vector<double> theta_partToNu;
  std::vector<double> theta_part;

  std::cout << "Finished Reading tracker tree" << std::endl;

  TChain *inputFile = new TChain("neuttree");
  inputFile->Add(fInputFile.c_str());
  NeutVect *nvct = nullptr;
  inputFile->SetBranchAddress("vectorbranch", &nvct);

  TFile fout(fOutputFile.c_str(), "RECREATE");

  TTree ssum_tree("sample_sum", "Tracker Numu Summary");
  ssum_tree.Branch("Mode", &Mode, "Mode/I");
  ssum_tree.Branch("PDGHMFSNuc", &PDGHMFSNuc, "PDGHMFSNuc/I");
  ssum_tree.Branch("PDGSRCnonSpcNuc", &PDGSRCnonSpcNuc, "PDGSRCnonSpcNuc/I");
  ssum_tree.Branch("PDGHMPrimaryNuc", &PDGHMPrimaryNuc, "PDGHMPrimaryNuc/I");

  // Basic interaction kinematics
  /*
  ssum_tree.Branch("PISNu", &PISNu);
  ssum_tree.Branch("PFSLep", &PFSLep);
  ssum_tree.Branch("PHMFSNuc", &PHMFSNuc);
  ssum_tree.Branch("PSRCnonSpcNuc", &PSRCnonSpcNuc);
  ssum_tree.Branch("PHMPrimaryNuc", &PHMPrimaryNuc);
  */


  ssum_tree.Branch("Enu", &Enu, "Enu/D");
  ssum_tree.Branch("EnuQErec", &EnuQErec, "EnuQErec/D");
  ssum_tree.Branch("kERecQEBias", &kERecQEBias, "kERecQEBias/D");

  ssum_tree.Branch("PFSLep", &PFSLep, "PFSLep/D");
  ssum_tree.Branch("CosFSLep", &CosFSLep, "CosFSLep/D");

  ssum_tree.Branch("HMprotonMom", &HMprotonMom, "HMprotonMom/D");
  ssum_tree.Branch("HMprotonTheta", &HMprotonTheta, "HMprotonTheta/D");
  ssum_tree.Branch("HMneutronMom", &HMneutronMom, "HMneutronMom/D");
  ssum_tree.Branch("HMneutronTheta", &HMneutronTheta, "HMneutronTheta/D");

  ssum_tree.Branch("Q2", &Q2, "Q2/D");
  ssum_tree.Branch("q0", &q0, "q0/D");
  ssum_tree.Branch("q3", &q3, "q3/D");
  ssum_tree.Branch("Emiss", &Emiss, "Emiss/D");
  ssum_tree.Branch("Pmiss", &Pmiss, "Pmiss/D");
  ssum_tree.Branch("isSRC", &isSRC, "isSRC/I");

  ssum_tree.Branch("NFSprot", &NFSprot, "NFSprot/I");
  ssum_tree.Branch("NFSneut", &NFSneut, "NFSneut/I");

  // Construct the graphs
    // Construct the graphs
    for (unsigned int i = 0; i < dial_graphs.size(); i++) {
        ssum_tree.Branch(Form("%sGraph", dial_names[i].c_str()), "TClonesArray", &(dial_graphs[i]), 256000, 0);
    }

   //TODO
    for (unsigned int i = 0; i < inputFile->GetEntries(); ++i) {
    //for (unsigned int i = 0; i < 50000; ++i) {
    if (i % (1000) == 0) std::cout<<i<<std::endl;
    inputFile->GetEntry(i);

    // Clear all the old graphs
    for (unsigned int i = 0; i < dial_graphs.size(); i++) {
      (dial_graphs[i])->Clear();
    }

    // Set default values
    for (unsigned int sys_iter = 0; sys_iter < dial_names.size(); sys_iter++) {
      TGraph *graph = (TGraph *)dial_graphs[sys_iter]->ConstructedAt(0);
      graph->SetName(Form("%s_gr", dial_names[sys_iter].c_str()));
      for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
        graph->RemovePoint(piter);
      graph->SetPoint(0, 0.0, 1.0);
    }
      auto t2krewev = t2krew::Event::Make(nvct);
      auto niwgev = t2krew::NIWGUtils::MakeNIWGEvent(t2krewev);

      //if(!niwgev.isSRC) continue;

      Mode = 0;
      Mode = niwgev.neutmode;

    q3 = -999;
    q0 = -999;
    Q2 = -999;

    q3 =  niwgev.q3 * 1000.0; //Converts to MeV
    q0 =  niwgev.q0 * 1000.0; //Converts to MeV

    Q2 = niwgev.Q2 * 1000.0;
    isSRC = niwgev.isSRC;
    Emiss = 1000.0*niwgev.Emiss; //Converts to MeV
    Pmiss = 1000.0*niwgev.Pmiss; //Converts to MeV

    int NFSlep = 0;
    NFSlep++;

    PDGHMFSNuc = 0;
    PDGSRCnonSpcNuc = 0;
    PDGHMPrimaryNuc = 0;

    HMprotonMom = -999;
    HMprotonTheta = -999;

    HMneutronMom = -999;
    HMneutronTheta = -999;

    PFSLep = -999;
    CosFSLep = -999;
    Enu = -999;
    EnuQErec = -999;
    kERecQEBias = -999;

    /*
    *PISNu = TLorentzVector(0, 0, 0, 0);
    *PFSLep = TLorentzVector(0, 0, 0, 0);
    *PHMFSNuc = TLorentzVector(0, 0, 0, 0);
    *PSRCnonSpcNuc = TLorentzVector(0, 0, 0, 0);
    *TLorentzVector PHMPrimaryNuc = TLorentzVector(0, 0, 0, 0);
*/
    NFSprot = 0;
    NFSneut = 0;

    int PDGnu = 0;
    TLorentzVector IS4Mom(0, 0, 0, 0);


    int NISneut = 0;
    int NISprot = 0;
    int NPrimaryLepFound = 0;


    TVector3 nu = niwgev.part_stack[niwgev.nu_index].p.Vect();
    TVector3 mu = niwgev.part_stack[niwgev.fslep_index].p.Vect();

    PFSLep = mu.Mag()*1000;

    CosFSLep = mu.Unit().Dot(nu.Unit());

    Enu = niwgev.TrueEnu*1000;

    TLorentzVector PFSLep_Vec = niwgev.part_stack[niwgev.fslep_index].p;

    double binding = 0;
    EnuQErec = 1000*niwg::EnuQErec(PFSLep_Vec.E(), mu.Mag(), CosFSLep, binding, 14);
    kERecQEBias = (EnuQErec / Enu) - 1.0;;

    for (size_t i = 0; i < niwgev.part_stack.size(); ++i) {

      niwg::NIWGParticle const &part = niwgev.part_stack[i];
      bool islep = (std::abs(part.pdg) >= 11) && (std::abs(part.pdg) <= 16);
      bool isnu = islep && (!(part.pdg % 2));

      NToChase += part.chase;

      //theta_partToNu.push_back(niwgev.theta_partToNu[i]);
      //theta_part.push_back(part.p.Theta());
/*
      if ((NPrimaryLepFound == 2) && part.isAtPrimaryVertex &&
          ((part.pdg == 2212) || (part.pdg == 2112))) {
        if (abs(Mode) == 1 && part.parent == -1) {
          isSRC = true;
          PDGSRCnonSpcNuc = niwgev.part_stack[3].pdg;
          *PSRCnonSpcNuc = niwgev.part_stack[3].p;
        }
        if (part.p.Vect().Mag() > PHMPrimaryNuc->Vect().Mag()) {
          *PHMPrimaryNuc = part.p;
          PDGHMPrimaryNuc = part.pdg;
        }
      }
*/
      if (part.chase || ((NPrimaryLepFound == 1) && isnu)) { // isalive or is a neutrino
        if (islep) {
          bool same_as_nu = (part.pdg == PDGnu);
          bool clep_for_nu = (std::abs(part.pdg) == (std::abs(PDGnu) - 1));
          if ((NPrimaryLepFound == 1) && (same_as_nu || clep_for_nu)) {
            //*PFSLep = part.p;
            NPrimaryLepFound++;
            NFSlep++;
            continue;
          }
        }

        switch (part.pdg) {
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16: {
          NFSlep++;
          break;
        }
        case 2212: {
          NFSprot++;
          //std::cout<<i<<" prot mom before "<<HMprotonMom<<" post "<<part.p.Vect().Mag()*1000<<std::endl;
          if (part.p.Vect().Mag() > HMprotonMom) {
            HMprotonMom = part.p.Vect().Mag()*1000;

            TVector3 part = niwgev.part_stack[i].p.Vect();
            HMprotonTheta = part.Unit().Dot(nu.Unit());
          }
          break;
        }
        case 2112: {
          NFSneut++;
          if (part.p.Vect().Mag() > HMneutronMom) {
            HMneutronMom = part.p.Vect().Mag()*1000;

            TVector3 part = niwgev.part_stack[i].p.Vect();
            HMneutronTheta = part.Unit().Dot(nu.Unit());
          }
          break;
        }
        }
      } else {
        if (NPrimaryLepFound < 2) { // initial state particles
          /*
          if (isnu) {               // Nu
            *PISNu = part.p;
            NPrimaryLepFound++;
            IS4Mom = IS4Mom + part.p;
            continue;
          }
          */

          if (part.pdg == 2112) {
            NISneut++;
            IS4Mom = IS4Mom + part.p;
          } else if (part.pdg == 2212) {
            NISprot++;
            IS4Mom = IS4Mom + part.p;
          }
        }
      }
    } // end particle loop

    //std::cout<<"dupa final "<<HMprotonMom<<std::endl;
      // Iterate through the systematics to make splines
      for (unsigned int sys_iter = 0; sys_iter < dial_names.size(); sys_iter++) {
        // Set name of TGraph
        TGraph *graph =
          (TGraph *)dial_graphs[sys_iter]->ConstructedAt(0);
        graph->SetName(Form("%s_gr", dial_names[sys_iter].c_str()));
        for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
          graph->RemovePoint(piter);

        // Iterate through dial of interest
        //bool flat = true;

        // Initialise dials to nominal
        T2KRW->Reset();
        T2KRW->Reconfigure();

        for (unsigned int dial_iter = 0; dial_iter < dial_values[sys_iter].size(); dial_iter++)
        {
          weight = 1.;

          T2KRW->Reset();
          T2KRW->Reconfigure();

          T2KRW->SetDial_To_Value(dials[sys_iter], dial_values[sys_iter][dial_iter]);
          T2KRW->Reconfigure();
          weight = T2KRW->CalcWeight(t2krewev);

          //if (fabs(weight - 1.0) > 1.e-5) flat = false;

            graph->SetPoint(dial_iter, dial_values[sys_iter][dial_iter], weight);
        }
        /*
        if (flat) {
          for (int piter = (graph->GetN() - 1); piter >= 0; piter--)
            graph->RemovePoint(piter);
          graph->SetPoint(0, 0.0, 1.0);
        }
        */
      } //end loop over systmeatic

    ssum_tree.Fill();
  } // number of events
  std::cout << "Event loop done!!" << std::endl;
  fout.cd();

  ssum_tree.Write("sample_sum");
  fout.Close();

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



