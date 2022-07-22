using namespace std;

void BetheBloch()
{
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    gPad->SetGrid();
    gStyle->SetPalette(51); 
   
    
    bool DEBUGMODE=false;
    bool VERBOSE=true;
    
    TFile *file=TFile::Open("/mnt/home/kskwarczynski/ProtonKinem/Run4MC.root");
    TTree *tree;
    file->GetObject("default",tree);
    
    Int_t           accum_level[1][2][10];   //[NTOYS]
    Int_t           sel_prot_truePDG;
    Float_t         sel_prot_truemom;
    Float_t         sel_prot_truedir[3];

    tree->SetBranchStatus("*", false);
    tree->SetBranchStatus( "accum_level", true);
    tree->SetBranchAddress("accum_level", &accum_level);
    
    tree->SetBranchStatus( "sel_prot_truePDG", true);
    tree->SetBranchAddress("sel_prot_truePDG", &sel_prot_truePDG);
    
    tree->SetBranchStatus( "sel_prot_truemom", true);
    tree->SetBranchAddress("sel_prot_truemom", &sel_prot_truemom);

    tree->SetBranchStatus( "sel_prot_truedir", true);
    tree->SetBranchAddress("sel_prot_truedir", &sel_prot_truedir);

    
    int AllEvents=tree->GetEntries();
    if(VERBOSE) cout<< "\033[1;34mNumber of all events \033[0m" <<AllEvents<<endl;
    
    if(DEBUGMODE) AllEvents=100;    
    
    TH1D *PDG_Proton = new TH1D("PDGProton","Proton Pull",50, 0, 2000);
    TH1D *PDG_PiPlus = new TH1D("PDGPiPlus","Proton Pull",50, 0, 2000);
    TH1D *PDG_Muon = new TH1D("PDG_Muon","Proton Pull",50, 0, 2000);
    TH1D *PDG_NonProton = new TH1D("PDGNonProton","Proton Pull",50, 0, 2000);

    PDG_Proton->GetXaxis()->SetTitle("Proton Pull");


    for(int i=0;  i<AllEvents; i++)
    {
        tree->GetEntry(i);
        //std::cout<<accum_level[0][0][2]<<" "<<sel_prot_truePDG<<"  "<<sel_prot_truemom<<std::endl;
        if(accum_level[0][0][2]>8)
        {
            if(sel_prot_truePDG==2212)
            {
                PDG_Proton->Fill( sel_prot_truemom);

            }
            if(sel_prot_truePDG==211)
            {
                PDG_PiPlus->Fill( sel_prot_truemom);
            }
            if(sel_prot_truePDG==13)
            {
                PDG_Muon->Fill( sel_prot_truemom);

            }
            if(sel_prot_truePDG!=2212 && sel_prot_truePDG!=13 && sel_prot_truePDG!=211)
            {
                PDG_NonProton->Fill( sel_prot_truePDG);

            }
        }
    }

    THStack *PDG_Stack= new THStack( "PDG_Stack", "CC0#pi-Np-0#gamma FGD1" );
    PDG_Stack->Add( PDG_NonProton );
    PDG_Stack->Add( PDG_Muon );
    PDG_Stack->Add( PDG_PiPlus );
    PDG_Stack->Add( PDG_Proton );
    
    PDG_Proton->SetFillColor(kGreen);
    PDG_Proton->SetFillStyle(3001);
    PDG_Proton->SetLineColor(kGreen);

    PDG_NonProton->SetFillColor(kBlack);
    PDG_NonProton->SetFillStyle(3001);
    PDG_NonProton->SetLineColor(kBlack);
    
    PDG_PiPlus->SetFillColor(kBlue);
    PDG_PiPlus->SetFillStyle(3001);
    PDG_PiPlus->SetLineColor(kBlue);
    
    PDG_Muon->SetFillColor(kRed);
    PDG_Muon->SetFillStyle(3001);
    PDG_Muon->SetLineColor(kRed);
    
    c1->Print("BetheBloch.pdf[", "pdf");    

    PDG_Stack->Draw("");
    
    TLegend *legend = new TLegend(0.70,0.75,0.85,0.9);
    legend->AddEntry(PDG_Proton, "Proton","l");
    legend->AddEntry(PDG_PiPlus, "#pi+","l");
    legend->AddEntry(PDG_Muon, "#mu","l");
    legend->AddEntry(PDG_NonProton, "Other","l");
    legend->SetTextSize(0.04);
    legend->Draw();
    
    PDG_Stack->GetXaxis();
    PDG_Stack->GetXaxis()->SetTitle("True Proton Momentum of Proton Candidate");
    
    c1->Print("BetheBloch.pdf", "pdf");
        
    c1->Print("BetheBloch.pdf]", "pdf");
}

    
