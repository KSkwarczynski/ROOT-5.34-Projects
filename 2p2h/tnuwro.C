#define tnuwro_cxx
#include "tnuwro.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>


void tnuwro::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L tnuwro.C
//      Root > tnuwro t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

if (fChain == 0) return;
//////////////////RozneNeutrina////////////////////////////////
    int CCQELiczbaCzastek[2]={0, 0}; //0-primary  1-wylatujacy
    int MecLiczbaCzastek[2]={0, 0};  //0-primary  1-wylatujacy
    int RESLiczbaCzastek[2]={0, 0};  //0-primary  1-wylatujacy
    int DISLiczbaCzastek[2]={0, 0};  //0-primary  1-wylatujacy
    int COHLiczbaCzastek[2]={0, 0};  //0-primary  1-wylatujacy
    int MecNuMuLiczbaCzastek[2]={0, 0};  //0-primary  1-wylatujacy
    int n_numu=0, n_anti_numu=0, n_nue=0, n_anti_nue=0;
    int n_CCQE =0, n_2p2h=0, n_res=0, n_DIS=0, n_Coh=0, n_NCQE=0, n_NCres=0, n_NCdis=0, n_NCcoh=0;

    TH1F *h_numu = new TH1F("h_numu", "Neutrino momentum distribution of muon neutrino", 250, 0, 5000.0);
    h_numu->GetYaxis()->SetTitle("Number of events");
    h_numu->GetXaxis()->SetTitle("Neutrino momentum [MeV]");

    TH1F *h_anti_numu = (TH1F*)(h_numu->Clone("h_anti_numu"));
    h_anti_numu->SetNameTitle("h_anti_numu","Neutrino momentum distribution of anti muon neutrino");
    TH1F *h_nue = (TH1F*)(h_numu->Clone("h_nue"));
    h_nue->SetNameTitle("h_nue","Neutrino momentum distribution of electron neutrino");
    TH1F *h_anti_nue = (TH1F*)(h_numu->Clone("h_anti_nue"));
    h_anti_nue->SetNameTitle("h_anti_nue","Neutrino momentum distribution of anti electron neutrino");

//////////////////////Rozne Kanaly dla anti mu//////////////////////
    TH1F *h_CCQE = new TH1F("h_CCQE", "Momentum distribution for CCQE", 250, 0, 5000.0);
    h_CCQE->GetYaxis()->SetTitle("Number of events");
    h_CCQE->GetXaxis()->SetTitle("Neutrino momentum [GeV]");

    TH1F *h_2p2h = (TH1F*)(h_CCQE->Clone("h_2p2h"));
    h_2p2h->SetNameTitle("h_2p2h","Neutrino momentum distribution for 2p2h");
    TH1F *h_res = (TH1F*)(h_CCQE->Clone("h_res"));
    h_res->SetNameTitle("h_res","Neutrino momentum distribution for res");
    TH1F *h_DIS = (TH1F*)(h_CCQE->Clone("h_DIS"));
    h_DIS->SetNameTitle("h_DIS","Neutrino momentum distribution for DIS");
    TH1F *h_Coh = (TH1F*)(h_CCQE->Clone("h_Coh"));
    h_Coh->SetNameTitle("h_Coh","Neutrino momentum distribution for Coh");

    TH1F *h_NCQE = (TH1F*)(h_CCQE->Clone("h_NCQE"));
    h_NCQE->SetNameTitle("h_NCQE","Neutrino momentum distribution for NCQE");
    TH1F *h_NCres = (TH1F*)(h_CCQE->Clone("h_NCres"));
    h_NCres->SetNameTitle("h_NCres","Neutrino momentum distribution for NC Res");
    TH1F *h_NCdis = (TH1F*)(h_CCQE->Clone("h_NCdis"));
    h_NCdis->SetNameTitle("h_NCdis","Neutrino momentum distribution for NC Dis");
    TH1F *h_NCcoh = (TH1F*)(h_CCQE->Clone("h_NCcoh"));
    h_NCcoh->SetNameTitle("h_NCcoh","Neutrino momentum distribution for NC Coh");

////////////////////////////CCQE///////////////////////
    TH1F *h_CCQE_neutron = new TH1F("h_CCQE_neutron", "Primary neutron momentum distribution for CCQE", 250, 0, 5000.0);
    h_CCQE_neutron->GetYaxis()->SetTitle("Number of events");
    h_CCQE_neutron->GetXaxis()->SetTitle("Neutrino momentum [MeV]");
    TH1F *h_CCQE_proton = new TH1F("h_CCQE_proton", "Proton final state momentum distribution for CCQE", 150, 0, 2500.0);
    h_CCQE_proton->GetYaxis()->SetTitle("Number of events");
    h_CCQE_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_CCQE_proton_max = (TH1F*)(h_CCQE_proton->Clone("h_CCQE_proton_max"));
    h_CCQE_proton_max->SetNameTitle("h_CCQE_proton_max"," Momentum distribution for proton highest momentum, final state, CCQE");
    TH1F *h_CCQE_proton_max_cut = new TH1F("h_CCQE_proton_max_cut", "Highest momentum proton, after cut final state, CCQE", 150, 0, 2500.0);

    TH1F *h_CCQE_proton_counter = new TH1F("h_CCQE_proton_counter", "CCQE proton final state counter", 80, 0, 8.0);
    TH1F *h_CCQE_proton_counter_cut = new TH1F("h_CCQE_proton_counter_cut", "CCQE proton final state counter momentum >450 MeV", 80, 0, 8.0);
////////////////////////////2p2h///////////////////////
                    /////PRIMARY////
    TH1F *h_2p2h_Prim_neutron = new TH1F("h_2p2h_Prim_neutron", "Neutron momentum distribution for 2p2h primary neutron", 400, 0, 5000.0);
    h_2p2h_Prim_neutron->GetYaxis()->SetTitle("Number of events");
    h_2p2h_Prim_neutron->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_2p2h_Prim_proton = (TH1F*)(h_2p2h_Prim_neutron->Clone("h_2p2h_Prim_proton"));
    h_2p2h_Prim_proton->SetNameTitle("h_2p2h_Prim_proton","Primary proton momentum distribution for 2p2h");

    TH1F *h_2p2h_Prim_particle_counter = new TH1F("h_2p2h_Prim_particle_counter", "2p2h neutron or proton primary counter", 80, 0, 8.0);
    TH1F *h_2p2h_Prim_proton_counter = new TH1F("h_2p2h_Prim_proton_counter", "2p2h proton primary counter", 80, 0, 8.0);
    TH1F *h_2p2h_Prim_neutron_counter = new TH1F("h_2p2h_Prim_neutron_counter", "2p2h neutron primary counter", 80, 0, 8.0);

    TH1F *h_2p2h_target_neutron_counter = new TH1F("h_2p2h_target_neutron_counter", "2p2h neutron target", 40, 0, 4.0);
    TH1F *h_2p2h_target_proton_counter = new TH1F("h_2p2h_target_proton_counter", "2p2h proton target", 40, 0, 4.0);
                        //////FINAL/////
    TH1F *h_2p2h_proton = new TH1F("h_2p2h_proton", "Proton momentum distribution for 2p2h", 150, 0, 2500.0);
    h_2p2h_proton->GetYaxis()->SetTitle("Number of events");
    h_2p2h_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_2p2h_proton_counter = new TH1F("h_2p2h_proton_counter", "2p2h proton final state counter", 80, 0, 8.0);
    TH1F *h_2p2h_proton_counter_cut = new TH1F("h_2p2h_proton_counter_cut", "2p2h proton final state counter momentum >450 MeV", 80, 0, 8.0);

    TH1F *h_2p2h_particle_counter = new TH1F("h_2p2h_particle_counter", "2p2h proton or neutron final state counter", 80, 0, 8.0);
    TH1F *h_2p2h_neutron_counter = new TH1F("h_2p2h_neutron_counter", "2p2h neutron final state counter", 80, 0, 8.0);

    TH1F *h_2p2h_proton_max = (TH1F*)(h_2p2h_proton->Clone("h_2p2h_proton_max"));
    h_2p2h_proton_max->SetNameTitle("h_2p2h_proton_max"," Momentum distribution for proton highest momentum, final state, 2p2h");
    TH1F *h_2p2h_proton_max_cut= new TH1F("h_2p2h_proton_max_cut", "Highest momentum proton, after cut final state, 2p2h", 150, 0, 2500.0);

    TH1F *h_2p2h_ifsingle_proton_counter = new TH1F("h_2p2h_ifsingle_proton_counter", "2p2h proton final state counter if one proton in primary", 80, 0, 8.0);
    TH1F *h_2p2h_ifdouble_proton_counter = new TH1F("h_2p2h_ifdouble_proton_counter", "2p2h proton final state counter if two protons in primary", 80, 0, 8.0);
    TH1F *h_2p2h_ifsingle_neutron_counter = new TH1F("h_2p2h_ifsingle_neutron_counter", "2p2h neutron final state counter if one proton in primary", 80, 0, 8.0);
    TH1F *h_2p2h_ifdouble_neutron_counter = new TH1F("h_2p2h_ifdouble_neutron_counter", "2p2h neutron final state counter if two protons in primary", 80, 0, 8.0);
///////////////////////////RES////////////////
            ////PRIMARY
    TH1F *h_RES_Prim_proton = new TH1F("h_RES_Prim_proton", "Primary proton momentum distribution for RES", 150, 0, 2500.0);
    h_RES_Prim_proton->GetYaxis()->SetTitle("Number of events");
    h_RES_Prim_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_RES_Prim_proton_counter = new TH1F("h_RES_Prim_proton_counter", "RES proton primary state counter", 80, 0, 8.0);

    TH1F *h_RES_Prim_neutron = new TH1F("h_RES_Prim_neutron", "Primary neutron momentum distribution for RES", 150, 0, 2500.0);
    h_RES_Prim_neutron->GetYaxis()->SetTitle("Number of events");
    h_RES_Prim_neutron->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_RES_Prim_neutron_counter = new TH1F("h_RES_Prim_neutron_counter", "RES neutron primary state counter", 80, 0, 8.0);
    TH1F *h_RES_Prim_positron_counter = new TH1F("h_RES_Prim_positron_counter", "RES postiron primary interactions counter", 80, 0, 8.0);
                    //////PRIMARY PION////
    TH1F *h_RES_Prim_piplus = new TH1F("h_RES_Prim_piplus", "Primary Pi+ momentum distribution for RES", 150, 0, 2500.0);
    h_RES_Prim_piplus->GetYaxis()->SetTitle("Number of events");
    h_RES_Prim_piplus->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_Prim_piplus_counter = new TH1F("h_RES_Prim_piplus_counter", "RES Pi+ primary state counter", 80, 0, 8.0);

    TH1F *h_RES_Prim_pizero = new TH1F("h_RES_Prim_pizero", "Primary Pi0 momentum distribution for RES", 150, 0, 2500.0);
    h_RES_Prim_pizero->GetYaxis()->SetTitle("Number of events");
    h_RES_Prim_pizero->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_Prim_pizero_counter = new TH1F("h_RES_Prim_pizero_counter", "RES Pi0 primary state counter", 80, 0, 8.0);

    TH1F *h_RES_Prim_piminus = new TH1F("h_RES_Prim_piminus", "Primary Pi- momentum distribution for RES", 150, 0, 2500.0);
    h_RES_Prim_piminus->GetYaxis()->SetTitle("Number of events");
    h_RES_Prim_piminus->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_Prim_piminus_counter = new TH1F("h_RES_Prim_piminus_counter", "RES Pi- primary state counter", 80, 0, 8.0);
            ///////FINAL///////
    TH1F *h_RES_proton = new TH1F("h_RES_proton", "Final proton momentum distribution for RES", 150, 0, 2500.0);
    h_RES_proton->GetYaxis()->SetTitle("Number of events");
    h_RES_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_RES_proton_max = (TH1F*)(h_RES_proton->Clone("h_RES_proton_max"));
    h_RES_proton_max->SetNameTitle("h_RES_proton_max"," Momentum distribution for proton highest momentum, final state, RES");

    TH1F *h_RES_proton_counter = new TH1F("h_RES_proton_counter", "RES proton final state counter", 80, 0, 8.0);
    TH1F *h_RES_proton_counter_cut = new TH1F("h_RES_proton_counter_cut", "RES proton final state counter momentum >450 MeV", 80, 0, 8.0);
    TH1F *h_RES_positron_counter = new TH1F("h_RES_positron_counter", "RES postiron final state counter", 80, 0, 8.0);

    TH1F *h_RES_neutron = new TH1F("h_RES_neutron", "Final neutron momentum distribution for RES", 150, 0, 2500.0);
    h_RES_neutron->GetYaxis()->SetTitle("Number of events");
    h_RES_neutron->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_RES_neutron_counter = new TH1F("h_RES_neutron_counter", "RES neutron final state counter", 100, 0, 10.0);

                    //////FINAL PION////
    TH1F *h_RES_piplus = new TH1F("h_RES_piplus", "Final Pi+ momentum distribution for RES", 150, 0, 2500.0);
    h_RES_piplus->GetYaxis()->SetTitle("Number of events");
    h_RES_piplus->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_piplus_counter = new TH1F("h_RES_piplus_counter", "RES Pi+ final state counter", 80, 0, 8.0);

    TH1F *h_RES_pizero = new TH1F("h_RES_pizero", "Final Pi0 momentum distribution for RES", 150, 0, 2500.0);
    h_RES_pizero->GetYaxis()->SetTitle("Number of events");
    h_RES_pizero->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_pizero_counter = new TH1F("h_RES_pizero_counter", "RES Pi0 final state counter", 80, 0, 8.0);

    TH1F *h_RES_piminus = new TH1F("h_RES_piminus", "Final Pi- momentum distribution for RES", 150, 0, 2500.0);
    h_RES_piminus->GetYaxis()->SetTitle("Number of events");
    h_RES_piminus->GetXaxis()->SetTitle("Momentum [MeV]");
    TH1F *h_RES_piminus_counter = new TH1F("h_RES_piminus_counter", "RES Pi- final state counter", 80, 0, 8.0);

    TH1F *h_RES_proton_max_cut = new TH1F("h_RES_proton_max_cut", "Highest momentum proton, after cut final state, RES", 150, 0, 2500.0);
/////////////////DIS/////////
    TH1F *h_DIS_proton = new TH1F("h_DIS_proton", "Final proton momentum distribution for DIS", 150, 0, 2500.0);
    h_DIS_proton->GetYaxis()->SetTitle("Number of events");
    h_DIS_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_DIS_proton_max = new TH1F("h_DIS_proton_max", "Momentum distribution for proton highest momentum, final state, DIS", 150, 0, 2500.0);
    h_DIS_proton_max->GetYaxis()->SetTitle("Number of events");
    h_DIS_proton_max->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_DIS_proton_max_cut = new TH1F("h_DIS_proton_max_cut", "Highest momentum proton, after cut final state, DIS", 150, 0, 2500.0);

///////////////COH///////////
    TH1F *h_COH_proton = new TH1F("h_COH_proton", "Final proton momentum distribution for COH", 150, 0, 2500.0);
    h_COH_proton->GetYaxis()->SetTitle("Number of events");
    h_COH_proton->GetXaxis()->SetTitle("Momentum [MeV]");
//////////2p2h for normal neutrinos test//////
                    /////PRIMARY////
    TH1F *h_numu_2p2h_Prim_neutron = new TH1F("h_numu_2p2h_Prim_neutron", "Neutron momentum distribution for 2p2h primary neutron", 400, 0, 5000.0);
    h_numu_2p2h_Prim_neutron->GetYaxis()->SetTitle("Number of events");
    h_numu_2p2h_Prim_neutron->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_numu_2p2h_Prim_proton = (TH1F*)(h_numu_2p2h_Prim_neutron->Clone("h_numu_2p2h_Prim_proton"));
    h_numu_2p2h_Prim_proton->SetNameTitle("h_numu_2p2h_Prim_proton","Primary proton momentum distribution for 2p2h");

    TH1F *h_numu_2p2h_Prim_particle_counter = new TH1F("h_numu_2p2h_Prim_particle_counter", "2p2h neutron or proton primary counter", 80, 0, 8.0);
    TH1F *h_numu_2p2h_Prim_proton_counter = new TH1F("h_numu_2p2h_Prim_proton_counter", "2p2h proton primary counter", 80, 0, 8.0);
    TH1F *h_numu_2p2h_Prim_neutron_counter = new TH1F("h_numu_2p2h_Prim_neutron_counter", "2p2h neutron primary counter", 80, 0, 8.0);

    TH1F *h_numu_2p2h_target_neutron_counter = new TH1F("h_numu_2p2h_target_neutron_counter", "2p2h neutron target", 40, 0, 4.0);
    TH1F *h_numu_2p2h_target_proton_counter = new TH1F("h_numu_2p2h_target_proton_counter", "2p2h proton target", 40, 0, 4.0);
                        //////FINAL/////
    TH1F *h_numu_2p2h_proton = new TH1F("h_numu_2p2h_proton", "Proton momentum distribution for 2p2h", 150, 0, 2500.0);
    h_numu_2p2h_proton->GetYaxis()->SetTitle("Number of events");
    h_numu_2p2h_proton->GetXaxis()->SetTitle("Momentum [MeV]");

    TH1F *h_numu_2p2h_proton_counter = new TH1F("h_numu_2p2h_proton_counter", "2p2h proton final state counter", 80, 0, 8.0);
    TH1F *h_numu_2p2h_proton_counter_cut = new TH1F("h_numu_2p2h_proton_counter_cut", "2p2h proton final state counter momentum >450 MeV", 80, 0, 8.0);

    TH1F *h_numu_2p2h_particle_counter = new TH1F("h_numu_2p2h_particle_counter", "2p2h proton or neutron final state counter", 80, 0, 8.0);
    TH1F *h_numu_2p2h_neutron_counter = new TH1F("h_numu_2p2h_neutron_counter", "2p2h neutron final state counter", 80, 0, 8.0);

    TH1F *h_numu_2p2h_proton_max = (TH1F*)(h_numu_2p2h_proton->Clone("h_numu_2p2h_proton_max"));
    h_numu_2p2h_proton_max->SetNameTitle("h_numu_2p2h_proton_max"," Momentum distribution for proton highest momentum, final state, 2p2h");
    TH1F *h_numu_2p2h_proton_max_cut= new TH1F("h_numu_2p2h_proton_max_cut", "Highest momentum proton, after cut final state, 2p2h", 150, 0, 2500.0);


///////////
    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;

    for (Long64_t jentry=0; jentry<nentries; jentry++)
    { //loop start
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        // if (Cut(ientry) < 0) continue;

//////////////////RozneNeutrina////////////////////////////////

        if(neutrino_pid == 14){
            h_numu->Fill(neutrino_p);
            n_numu++;
            }
        if(neutrino_pid == -14){
            h_anti_numu->Fill(neutrino_p);
            n_anti_numu++;
            }
        if(neutrino_pid == 12){
            h_nue->Fill(neutrino_p);
            n_nue++;
            }
        if(neutrino_pid == -12){
            h_anti_nue->Fill(neutrino_p);
            n_anti_nue++;
            }
//////////////////////Rozne Kanaly dla anti mu//////////////////////
        if(neutrino_pid == -14){
            if(channel==1){
                h_CCQE->Fill(neutrino_p);
                n_CCQE++;
                }
            if(channel == 9){
                h_2p2h->Fill(neutrino_p);
                n_2p2h++;
                }
            if(channel == 16){
                h_res->Fill(neutrino_p);
                n_res++;
                }
            if(channel == 91){
                h_DIS->Fill(neutrino_p);
                n_DIS++;
                }
            if(channel == 96){
                h_Coh->Fill(neutrino_p);
                n_Coh++;
                }

            if(channel == 2){
                h_NCQE->Fill(neutrino_p);
                n_NCQE++;
                }
            if(channel == 17){
                h_NCres->Fill(neutrino_p);
                n_NCres++;
                }
            if(channel == 92){
                h_NCdis->Fill(neutrino_p);
                n_NCdis++;
                }
            if(channel == 97){
                h_NCcoh->Fill(neutrino_p);
                n_NCcoh++;
                }
            }
//////////////////////CCQE////////////
        if(channel == 1 && neutrino_pid == -14){
            CCQELiczbaCzastek[0]=pidPrim->size();
            CCQELiczbaCzastek[1]=pid->size();
            for(int i=0; i < CCQELiczbaCzastek[0] ; i++){
                if(pidPrim->at(i)==2112){
                    h_CCQE_neutron->Fill(pPrim->at(i));
                }
            }

            int CCQEProtonCounter=0;
            int CCQEProtonCounterCut=0;
            int MomentumMaxCut=0;
            int MomentumMax=0;
            for(int i=0; i < CCQELiczbaCzastek[1] ; i++){
                if(pid->at(i)==2212){
                    h_CCQE_proton->Fill( p->at(i) );
                    CCQEProtonCounter++;
                    if( p->at(i) >= 450 ){
                        CCQEProtonCounterCut++;
                        if(p->at(i)>=MomentumMax){
                            MomentumMaxCut=p->at(i);
                        }
                    }
                    if(p->at(i)>=MomentumMax){
                        MomentumMax=p->at(i);
                    }
                }
            }
            if(MomentumMax!=0){
                h_CCQE_proton_max->Fill(MomentumMax);
            }
            if(MomentumMaxCut!=0){
                h_CCQE_proton_max_cut->Fill(MomentumMaxCut);
            }
            if(CCQEProtonCounter!=0){
                h_CCQE_proton_counter->Fill(CCQEProtonCounter);
            }
            if(CCQEProtonCounterCut!=0){
                h_CCQE_proton_counter_cut->Fill(CCQEProtonCounterCut);
            }
        }
////////////////////////////2p2h///////////////////////
        if(channel == 9 && neutrino_pid == -14){
            MecLiczbaCzastek[0]=pidPrim->size();
            MecLiczbaCzastek[1]=pid->size();
            /////Primary//////
            int MecPrimProtonCounter=0;
            int MecPrimNeutronCounter=0;
            int MecPrimParticleCounter=0;

            int MecTargetProtonCounter=0;
            int MecTargetNeutronCounter=0;

            if(target_pid==2212){
                    MecTargetProtonCounter++;
                }
            if(target_pid==2112){
                    MecTargetNeutronCounter++;
                }
            for(int i=0; i < MecLiczbaCzastek[0] ; i++){
                if(pidPrim->at(i)==2112){
                    h_2p2h_Prim_neutron->Fill(pPrim->at(i));
                    MecPrimNeutronCounter++;
                }
                if(pidPrim->at(i)==2212){
                    h_2p2h_Prim_proton->Fill(pPrim->at(i));
                    MecPrimProtonCounter++;
                }
                if(pidPrim->at(i)==2212 || pidPrim->at(i)==2112){
                    MecPrimParticleCounter++;
                }
            }

            if(MecTargetProtonCounter!=0){
                h_2p2h_target_proton_counter->Fill(MecTargetProtonCounter);
            }
            if(MecTargetNeutronCounter!=0){
                h_2p2h_target_neutron_counter->Fill(MecTargetNeutronCounter);
            }
            if(MecPrimProtonCounter!=0){
                h_2p2h_Prim_proton_counter->Fill(MecPrimProtonCounter);
            }
            if(MecPrimNeutronCounter!=0){
                h_2p2h_Prim_neutron_counter->Fill(MecPrimNeutronCounter);
            }
            if(MecPrimParticleCounter!=0){
                h_2p2h_Prim_particle_counter->Fill(MecPrimParticleCounter);
            }
            //////Final/////
            int MecProtonCounter=0;
            int MecProtonCounterCut=0;
            int MecNeutronCounter=0;
            int MecParticleCounter=0;

            int MecIfPrimSingleProtonCounter=0;
            int MecIfPrimDoubleProtonCounter=0;
            int MecIfPrimSingleNeutronCounter=0;
            int MecIfPrimDoubleNeutronCounter=0;

            int MomentumMax=0;
            int MomentumMaxCut=0;

            for(int i=0; i < MecLiczbaCzastek[1] ; i++){
                if(pid->at(i)==2212){
                    h_2p2h_proton->Fill( p->at(i) );
                    MecProtonCounter++;
                    if(p->at(i)>=450){
                        MecProtonCounterCut++;
                        if(p->at(i)>=MomentumMax){
                            MomentumMaxCut=p->at(i);
                        }
                    }
                    if(p->at(i)>=MomentumMax){
                        MomentumMax=p->at(i);
                    }
                    if(MecPrimProtonCounter==1){
                        MecIfPrimSingleProtonCounter++;
                    }
                    if(MecPrimProtonCounter==2 ){
                        MecIfPrimDoubleProtonCounter++;
                    }
                }
                if(pid->at(i)==2112){
                    MecNeutronCounter++;
                    if(MecPrimProtonCounter==1){
                        MecIfPrimSingleNeutronCounter++;
                    }
                    if(MecPrimProtonCounter==2){
                        MecIfPrimDoubleNeutronCounter++;
                    }
                }
                if(pid->at(i)==2212 || pid->at(i)==2112){
                    MecParticleCounter++;
                }
            }
            if(MomentumMax!=0){
                h_2p2h_proton_max->Fill(MomentumMax);
            }
            if(MomentumMaxCut!=0){
                h_2p2h_proton_max_cut->Fill(MomentumMaxCut);
            }
            if(MecProtonCounter!=0){
                h_2p2h_proton_counter->Fill(MecProtonCounter);
            }
            if(MecProtonCounterCut!=0){
                h_2p2h_proton_counter_cut->Fill(MecProtonCounterCut);
            }
            if(MecNeutronCounter!=0){
                h_2p2h_neutron_counter->Fill(MecNeutronCounter);
            }
            if(MecParticleCounter!=0){
                h_2p2h_particle_counter->Fill(MecParticleCounter);
            }

            if(MecIfPrimSingleNeutronCounter!=0){
                h_2p2h_ifsingle_neutron_counter->Fill(MecIfPrimSingleNeutronCounter);
            }
            if(MecIfPrimSingleProtonCounter!=0){
                h_2p2h_ifsingle_proton_counter->Fill(MecIfPrimSingleProtonCounter);
            }
            if(MecIfPrimDoubleProtonCounter!=0){
                h_2p2h_ifdouble_proton_counter->Fill(MecIfPrimDoubleProtonCounter);
            }
            if(MecIfPrimDoubleNeutronCounter!=0){
                h_2p2h_ifdouble_neutron_counter->Fill(MecIfPrimDoubleNeutronCounter);
            }
        }
/////////////////////////RES//////////////
        if(channel == 16 && neutrino_pid == -14){
            RESLiczbaCzastek[0]=pidPrim->size();
            RESLiczbaCzastek[1]=pid->size();
        /////Primary/////
            int RESPrimProtonCounter=0;
            int RESPrimNeutronCounter=0;
            int RESPrimPositronCounter=0;

            int RESPrimPiPlusCounter=0;
            int RESPrimPiZeroCounter=0;
            int RESPrimPiMinusCounter=0;
            for(int i=0; i < RESLiczbaCzastek[0] ; i++){
                if(pidPrim->at(i)==2212){
                    h_RES_Prim_proton->Fill( pPrim->at(i) );
                    RESPrimProtonCounter++;
                }
                if(pidPrim->at(i) == 2112){
                    h_RES_Prim_neutron->Fill( pPrim->at(i) );
                    RESPrimNeutronCounter++;
                }
                if(pidPrim->at(i) == 211){
                    h_RES_Prim_piplus->Fill( pPrim->at(i) );
                    RESPrimPiPlusCounter++;
                }
                if(pidPrim->at(i) == 111){
                    h_RES_Prim_pizero->Fill( pPrim->at(i) );
                    RESPrimPiZeroCounter++;
                }
                if(pidPrim->at(i) == -211){
                    h_RES_Prim_piminus->Fill( pPrim->at(i) );
                    RESPrimPiMinusCounter++;
                }
                if(pidPrim->at(i) == -11){
                    RESPrimPositronCounter++;
                }
            }
            if(RESPrimProtonCounter!=0){
                h_RES_Prim_proton_counter->Fill(RESPrimProtonCounter);
            }
            if(RESPrimNeutronCounter!=0){
                h_RES_Prim_neutron_counter->Fill(RESPrimNeutronCounter);
            }
            if(RESPrimPositronCounter!=0){
                h_RES_Prim_positron_counter->Fill(RESPrimPositronCounter);
            }

            if(RESPrimPiPlusCounter!=0){
                h_RES_Prim_piplus_counter->Fill(RESPrimPiPlusCounter);
            }
            if(RESPrimPiZeroCounter!=0){
                h_RES_Prim_pizero_counter->Fill(RESPrimPiZeroCounter);
            }
            if(RESPrimPiMinusCounter!=0){
                h_RES_Prim_piminus_counter->Fill(RESPrimPiMinusCounter);
            }
        ///////Final///////
            int RESProtonCounter=0;
            int RESProtonCounterCut=0;
            int RESNeutronCounter=0;
            int RESPositronCounter=0;

            int RESPiPlusCounter=0;
            int RESPiZeroCounter=0;
            int RESPiMinusCounter=0;

            int MomentumMax=0;
            int MomentumMaxCut=0;
            for(int i=0; i < RESLiczbaCzastek[1] ; i++){
                if(pid->at(i) == 2212){
                    h_RES_proton->Fill( p->at(i) );
                    RESProtonCounter++;
                    if( p->at(i) >= 450 ){
                        RESProtonCounterCut++;
                        if(p->at(i)>=MomentumMaxCut){
                            MomentumMaxCut=p->at(i);
                        }
                    }
                    if(p->at(i)>=MomentumMax){
                        MomentumMax=p->at(i);
                    }
                }
                if(pid->at(i) == 2112){
                    h_RES_neutron->Fill( p->at(i) );
                    RESNeutronCounter++;
                }
                if(pid->at(i) == -11){
                    RESPositronCounter++;
                }
                if(pid->at(i) == 211){
                    h_RES_piplus->Fill( p->at(i) );
                    RESPiPlusCounter++;
                }
                if(pid->at(i) == 111){
                    h_RES_pizero->Fill( p->at(i) );
                    RESPiZeroCounter++;
                }
                if(pid->at(i) == -211){
                    h_RES_piminus->Fill( p->at(i) );
                    RESPiMinusCounter++;
                }

            }
            if(RESProtonCounter!=0){
                h_RES_proton_counter->Fill(RESProtonCounter);
            }
            if(RESProtonCounterCut!=0){
                h_RES_proton_counter_cut->Fill(RESProtonCounterCut);
            }
            if(RESNeutronCounter!=0){
                h_RES_neutron_counter->Fill(RESNeutronCounter);
            }
            if(RESPositronCounter!=0){
                h_RES_positron_counter->Fill(RESPositronCounter);
            }

            if(RESPiPlusCounter!=0){
                h_RES_piplus_counter->Fill(RESPiPlusCounter);
            }
            if(RESPiZeroCounter!=0){
                h_RES_pizero_counter->Fill(RESPiZeroCounter);
            }
            if(RESPiMinusCounter!=0){
                h_RES_piminus_counter->Fill(RESPiMinusCounter);
            }
            if(MomentumMax!=0){
                h_RES_proton_max->Fill(MomentumMax);
            }
            if(MomentumMaxCut!=0){
                h_RES_proton_max_cut->Fill(MomentumMaxCut);
            }
        }
////////////DIS////////
        if(channel == 91 && neutrino_pid == -14){
            DISLiczbaCzastek[0]=pidPrim->size();
            DISLiczbaCzastek[1]=pid->size();
            int MomentumMax=0;
            int MomentumMaxCut=0;
            for(int i=0; i < DISLiczbaCzastek[1] ; i++){
                if(pid->at(i)==2212){
                    h_DIS_proton->Fill( p->at(i) );
                    if(p->at(i)>=450){
                        if(p->at(i)>=MomentumMaxCut){
                            MomentumMaxCut=p->at(i);
                        }
                    }
                    if(p->at(i)>=MomentumMax){
                        MomentumMax=p->at(i);
                    }
                }
            }
            if(MomentumMax != 0){
                h_DIS_proton_max->Fill(MomentumMax);
            }
            if(MomentumMaxCut != 0){
                h_DIS_proton_max_cut->Fill(MomentumMaxCut);
            }
        }
///////////COH/////////
        if(channel == 96 && neutrino_pid == -14){
            COHLiczbaCzastek[0]=pidPrim->size();
            COHLiczbaCzastek[1]=pid->size();

            for(int i=0; i < COHLiczbaCzastek[1] ; i++){
                if(pid->at(i)==2212){
                    h_COH_proton->Fill(p->at(i));
                }
            }
        }
/////////////////2p2h normalne neutrino TEST/////
        if(channel == 9 && neutrino_pid == 14){
            MecNuMuLiczbaCzastek[0]=pidPrim->size();
            MecNuMuLiczbaCzastek[1]=pid->size();
            /////Primary//////
            int MecNuMuPrimProtonCounter=0;
            int MecNuMuPrimNeutronCounter=0;
            int MecNuMuPrimParticleCounter=0;

            int MecNuMuTargetProtonCounter=0;
            int MecNuMuTargetNeutronCounter=0;

            if(target_pid==2212){
                    MecNuMuTargetProtonCounter++;
                }
            if(target_pid==2112){
                    MecNuMuTargetNeutronCounter++;
                }
            for(int i=0; i < MecNuMuLiczbaCzastek[0] ; i++){
                if(pidPrim->at(i)==2112){
                    h_numu_2p2h_Prim_neutron->Fill(pPrim->at(i));
                    MecNuMuPrimNeutronCounter++;
                }
                if(pidPrim->at(i)==2212){
                    h_numu_2p2h_Prim_proton->Fill(pPrim->at(i));
                    MecNuMuPrimProtonCounter++;
                }
                if(pidPrim->at(i)==2212 || pidPrim->at(i)==2112){
                    MecNuMuPrimParticleCounter++;
                }
            }

            if(MecNuMuTargetProtonCounter!=0){
                h_numu_2p2h_target_proton_counter->Fill(MecNuMuTargetProtonCounter);
            }
            if(MecNuMuTargetNeutronCounter!=0){
                h_numu_2p2h_target_neutron_counter->Fill(MecNuMuTargetNeutronCounter);
            }
            if(MecNuMuPrimProtonCounter!=0){
                h_numu_2p2h_Prim_proton_counter->Fill(MecNuMuPrimProtonCounter);
            }
            if(MecNuMuPrimNeutronCounter!=0){
                h_numu_2p2h_Prim_neutron_counter->Fill(MecNuMuPrimNeutronCounter);
            }
            if(MecNuMuPrimParticleCounter!=0){
                h_numu_2p2h_Prim_particle_counter->Fill(MecNuMuPrimParticleCounter);
            }
            //////Final/////
            int MecNuMuProtonCounter=0;
            int MecNuMuProtonCounterCut=0;
            int MecNuMuNeutronCounter=0;
            int MecNuMuParticleCounter=0;

            int MomentumMax=0;
            int MomentumMaxCut=0;
            int i=0;
            for(int i=0; i < MecNuMuLiczbaCzastek[1] ; i++){
                if(pid->at(i)==2212){
                    h_numu_2p2h_proton->Fill( p->at(i) );
                    MecNuMuProtonCounter++;
                    if(p->at(i)>=450){
                        MecNuMuProtonCounterCut++;
                        if(p->at(i)>=MomentumMax){
                            MomentumMaxCut=p->at(i);
                        }
                    }
                    if(p->at(i)>=MomentumMax){
                        MomentumMax=p->at(i);
                    }
                }
                if(pid->at(i)==2112){
                    MecNuMuNeutronCounter++;
                }
                if(pid->at(i)==2212 || pid->at(i)==2112){
                    MecNuMuParticleCounter++;
                }
            }
            if(MomentumMax!=0){
                h_numu_2p2h_proton_max->Fill(MomentumMax);
            }
            if(MomentumMaxCut!=0){
                h_numu_2p2h_proton_max_cut->Fill(MomentumMaxCut);
            }
            if(MecNuMuProtonCounter!=0){
                h_numu_2p2h_proton_counter->Fill(MecNuMuProtonCounter);
            }
            if(MecNuMuProtonCounterCut!=0){
                h_numu_2p2h_proton_counter_cut->Fill(MecNuMuProtonCounterCut);
            }
            if(MecNuMuNeutronCounter!=0){
                h_numu_2p2h_neutron_counter->Fill(MecNuMuNeutronCounter);
            }
            if(MecNuMuParticleCounter!=0){
                h_numu_2p2h_particle_counter->Fill(MecNuMuParticleCounter);
            }
        }
/////Wypluwanie eventow///////
    if(event_num%1000==0)
    cout<<"Event= "<<event_num<<endl;
   } // end loop
///////Saving to root file/////
TFile *fout = new TFile("histograms.root","RECREATE");

    h_numu->Write();
    h_anti_numu->Write();
    h_nue->Write();
    h_anti_nue->Write();

    h_CCQE->Write();
    h_2p2h->Write();
    h_res->Write();
    h_DIS->Write();
    h_Coh->Write();
    h_NCQE->Write();
    h_NCres->Write();
    h_NCdis->Write();
    h_NCcoh->Write();

    h_CCQE_neutron->Write();
    h_CCQE_proton->Write();
    h_CCQE_proton_max->Write();
    h_CCQE_proton_max_cut->Write();
    h_CCQE_proton_counter->Write();
    h_CCQE_proton_counter_cut->Write();

    h_2p2h_target_neutron_counter->Write();
    h_2p2h_target_proton_counter->Write();

    h_2p2h_Prim_neutron->Write();
    h_2p2h_Prim_proton->Write();
    h_2p2h_Prim_proton_counter->Write();
    h_2p2h_Prim_neutron_counter->Write();
    h_2p2h_Prim_particle_counter->Write();

    h_2p2h_proton->Write();
    h_2p2h_proton_max->Write();
    h_2p2h_proton_max_cut->Write();
    h_2p2h_particle_counter->Write();
    h_2p2h_neutron_counter->Write();
    h_2p2h_proton_counter->Write();
    h_2p2h_proton_counter_cut->Write();

    h_2p2h_ifsingle_neutron_counter->Write();
    h_2p2h_ifsingle_proton_counter->Write();
    h_2p2h_ifdouble_neutron_counter->Write();
    h_2p2h_ifdouble_proton_counter->Write();

    h_RES_Prim_proton->Write();
    h_RES_Prim_proton_counter->Write();
    h_RES_Prim_neutron->Write();
    h_RES_Prim_neutron_counter->Write();
    h_RES_Prim_positron_counter->Write();

    h_RES_Prim_piplus->Write();
    h_RES_Prim_piplus_counter->Write();
    h_RES_Prim_pizero->Write();
    h_RES_Prim_pizero_counter->Write();
    h_RES_Prim_piminus->Write();
    h_RES_Prim_piminus_counter->Write();

    h_RES_proton->Write();
    h_RES_proton_max->Write();
    h_RES_proton_max_cut->Write();
    h_RES_proton_counter->Write();
    h_RES_proton_counter_cut->Write();
    h_RES_neutron->Write();
    h_RES_neutron_counter->Write();
    h_RES_positron_counter->Write();

    h_RES_piplus->Write();
    h_RES_piplus_counter->Write();
    h_RES_pizero->Write();
    h_RES_pizero_counter->Write();
    h_RES_piminus->Write();
    h_RES_piminus_counter->Write();

    h_DIS_proton->Write();
    h_DIS_proton_max->Write();
    h_DIS_proton_max_cut->Write();
    h_COH_proton->Write();

    h_numu_2p2h_target_neutron_counter->Write();
    h_numu_2p2h_target_proton_counter->Write();

    h_numu_2p2h_Prim_neutron->Write();
    h_numu_2p2h_Prim_proton->Write();
    h_numu_2p2h_Prim_proton_counter->Write();
    h_numu_2p2h_Prim_neutron_counter->Write();
    h_numu_2p2h_Prim_particle_counter->Write();

    h_numu_2p2h_proton->Write();
    h_numu_2p2h_proton_max->Write();
    h_numu_2p2h_proton_max_cut->Write();
    h_numu_2p2h_particle_counter->Write();
    h_numu_2p2h_neutron_counter->Write();
    h_numu_2p2h_proton_counter->Write();
    h_numu_2p2h_proton_counter_cut->Write();

    fout->Close();
///////saving to txt file///////

    fstream plik;
    plik.open("Event_Counter.txt", ios::out);
    plik<< "numu "<< n_numu << endl;
    plik<< "anti_numu " << n_anti_numu <<endl;
    plik<< "nue "<< n_nue  << endl;
    plik<< "anti_nue " << n_anti_nue << endl;

    plik<< "CCQE " << n_CCQE << endl;
    plik<< "2p2h " << n_2p2h << endl;
    plik<< "res " << n_res << endl;
    plik<< "DIS " << n_DIS << endl;
    plik<< "Coh " << n_Coh << endl;

    plik<< "NCQE " << n_NCQE << endl;
    plik<< "NCres " << n_NCres << endl;
    plik<< "NCdis " << n_NCdis << endl;
    plik<< "NCcoh " << n_NCcoh << endl;

    plik.close();
}
