
void Resolution(TString fname)
{
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    TFile *file=TFile::Open( Form("%s", fname.Data() ) );
    TTree *tree;
    file->GetObject("sample_sum",tree);

    // Set all the branches to off
    tree->SetBranchStatus("*", false);

    Int_t           SelectedSample;
    tree->SetBranchStatus( "SelectedSample", true);
    tree->SetBranchAddress("SelectedSample", &SelectedSample);

    Int_t sel_prot_truePDG;
    tree->SetBranchStatus( "sel_prot_truePDG", true);
    tree->SetBranchAddress("sel_prot_truePDG", &sel_prot_truePDG);
            
    Int_t RecoProton_Topo;
    tree->SetBranchStatus( "RecoProton_Topo", true);
    tree->SetBranchAddress("RecoProton_Topo", &RecoProton_Topo);

    Double_t         RecoProtonMom;
    tree->SetBranchStatus( "RecoProtonMom", true);
    tree->SetBranchAddress("RecoProtonMom", &RecoProtonMom);
      
    Double_t         RecoProtonMom_NoCorrection;
    tree->SetBranchStatus( "RecoProtonMom_NoCorrection", true);
    tree->SetBranchAddress("RecoProtonMom_NoCorrection", &RecoProtonMom_NoCorrection);
    
    Double_t         TrueProtonMom;
    tree->SetBranchStatus( "TrueProtonMom", true);
    tree->SetBranchAddress("TrueProtonMom", &TrueProtonMom);

    Double_t    sel_prot_trueDpt;
    TBranch        *b_sel_prot_trueDpt;   //!
    tree->SetBranchStatus( "sel_prot_trueDpt", true);
    tree->SetBranchAddress("sel_prot_trueDpt", &sel_prot_trueDpt);
    
    Double_t   sel_prot_recoDpt;
    tree->SetBranchStatus( "sel_prot_recoDpt", true);
    tree->SetBranchAddress("sel_prot_recoDpt", &sel_prot_recoDpt);
    
    int AllEvents = tree->GetEntries();
    
   std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<AllEvents<<std::endl;
       
    const int momBinCount = 100;
    const int momBinMax = 1200;
    const int momBinMin = 0;
    
    
    TH2F *hResolution_nProt[2];
    TH1F *hRMS_nProt[2];
    TH1F *hMeanRMS_nProt[2];
    
    
    TH2F *hResolution_Tranverse_nProt[2];
    TH1F *hRMS_Tranverse_nProt[2];
    TH1F *hMeanRMS_Tranverse_nProt[2];
        
    TH1F *Gauss_NProt[2][momBinCount];
    TH1F *Gauss_NProt_Transvers[2][momBinCount];
    
    for(int i = 0;i<2;i++)
    {
        hResolution_nProt[i] = new TH2F(Form("hResolution_nProt_FGD%i",i), Form("CC0Pi-Np FGD%i PDG==2212",i+1), momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
        hResolution_nProt[i] ->GetXaxis()->SetTitle("True Pproton (MeV/c)");
        hResolution_nProt[i] ->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
        
        hRMS_nProt[i] = new TH1F(Form("hRMS_nProt_FGD%i",i), "CC0Pi-Np RMS PDG==2212", momBinCount, momBinMin, momBinMax);
        hRMS_nProt[i]->GetXaxis()->SetTitle("True Pproton (MeV/c)");
        
        hMeanRMS_nProt[i] = new TH1F(Form("hMeanRMS_nProt_FGD%i",i), Form("Mean and RMS CC0Pi-Np FGD%i PDG==2212",i+1), momBinCount, momBinMin, momBinMax);
        hMeanRMS_nProt[i]->GetXaxis()->SetTitle("True Pproton (MeV/c)");

        
        hResolution_Tranverse_nProt[i] = new TH2F(Form("hResolution_Tranverse_nProt_FGD%i",i+1), Form("CC0Pi-Np FGD%i PDG==2212",i+1), momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
        hResolution_Tranverse_nProt[i]->GetXaxis()->SetTitle("True dPt (MeV/c)");
        hResolution_Tranverse_nProt[i]->GetYaxis()->SetTitle("Reco dPt (MeV/c)");
        
        hRMS_Tranverse_nProt[i] = new TH1F(Form("hRMS_Tranverse_nProt_FGD%i",i), Form("CC0Pi-Np RMS FGD%i PDG==2212",i+1), momBinCount, momBinMin, momBinMax);
        hRMS_Tranverse_nProt[i]->GetXaxis()->SetTitle("True dPt (MeV/c)");
        
        hMeanRMS_Tranverse_nProt[i] = new TH1F(Form("hMeanRMS_Tranverse_nProt_FGD%i",i), Form("Mean and RMS CC0Pi-Np FGD%i PDG==2212",i+1), momBinCount, momBinMin, momBinMax);
        hMeanRMS_Tranverse_nProt[i]->GetXaxis()->SetTitle("True dPt (MeV/c)");

        for(int ig=0;ig<momBinCount;ig++)
        {
            Gauss_NProt[i][ig] = new TH1F(Form("Gauss_NProt%ig_FGD%i",ig,i+1), "Gauss_NProt", momBinCount, momBinMin, momBinMax);
            Gauss_NProt_Transvers[i][ig] = new TH1F(Form("Gauss_NProt_Transvers%ig_FGD%i",ig,i+1), "Gauss_NProt_Transvers", momBinCount, momBinMin, momBinMax);
        }  
        
    }
    
    TH2F* hResolution_All[3];
    hResolution_All [0]= new TH2F("hResolution_All", "All selection All True PDG", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    hResolution_All [1]= new TH2F("hResolution_Allproton", "All selection PDG==2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    hResolution_All [2]= new TH2F("hResolution_AllnonProton", "All selection PDG!=2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
        
    int TPCproton = 1;
    int FGDproton = 2;
    
    int CC0PiNpNoPhotonFGD1 = 8;
    int CC0PiNpNoPhotonFGD2 = 32;
    
    TH2F* hResolution_nProt_Topology[2][2];
    
    hResolution_nProt_Topology[0][0] = new TH2F("hResolution_nProt_TopTPC_FGD1", "CC0Pi-Np FGD1 TPCprot PDG==2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    hResolution_nProt_Topology[0][1] = new TH2F("hResolution_nProt_TopFGD_FGD1", "CC0Pi-Np FGD1 FGDprot PDG==2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
          
    hResolution_nProt_Topology[1][0] = new TH2F("hResolution_nProt_TopTPC_FGD2", "CC0Pi-Np FGD2 TPCprot PDG==2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    hResolution_nProt_Topology[1][1] = new TH2F("hResolution_nProt_TopFGD_FGD2", "CC0Pi-Np FGD2 FGDprot PDG==2212", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    
    TH1F *hProtMom[2][3];
    TH1F *hProtMom_NoCorrection[2][3];
    
    hProtMom[0][0] = new TH1F("TH1F_All_FGD1", "FGD1 ProtMome PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom[0][1] = new TH1F("TH1F_All_FGD1_TPCprot", "FGD1 TPCprot ProtMome PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom[0][2] = new TH1F("TH1F_All_FGD1_FGDprot", "FGD1 FGDprot ProtMome PDG==2212", momBinCount, momBinMin, momBinMax);

    hProtMom[1][0] = new TH1F("TH1F_All_FGD2", "FGD2 ProtMome", momBinCount, momBinMin, momBinMax);
    hProtMom[1][1] = new TH1F("TH1F_All_FGD2_TPCprot", "FGD2 TPCprot ProtMome", momBinCount, momBinMin, momBinMax);
    hProtMom[1][2] = new TH1F("TH1F_All_FGD2_FGDprot", "FGD2 FGDprot ProtMome", momBinCount, momBinMin, momBinMax);
    
    hProtMom_NoCorrection[0][0] = new TH1F("TH1F_All_FGD1_NoCorr", "FGD1 ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom_NoCorrection[0][1] = new TH1F("TH1F_All_FGD1_TPCprot_NoCorr", "FGD1 TPCprot ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom_NoCorrection[0][2] = new TH1F("TH1F_All_FGD1_FGDprot_NoCorr", "FGD1 FGDprot ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);

    hProtMom_NoCorrection[1][0] = new TH1F("TH1F_All_FGD2_NoCorr", "FGD2 ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom_NoCorrection[1][1] = new TH1F("TH1F_All_FGD2_TPCprot_NoCorr", "FGD2 TPCprot ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);
    hProtMom_NoCorrection[1][2] = new TH1F("TH1F_All_FGD2_FGDprot_NoCorr", "FGD2 FGDprot ProtMome_NoCorr PDG==2212", momBinCount, momBinMin, momBinMax);
    
    for(int i = 0;i<3;i++)
    {
        hResolution_All[i] ->GetXaxis()->SetTitle("True Pproton (MeV/c)");
        hResolution_All[i] ->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
        
        hProtMom[0][i]->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
        hProtMom[1][i]->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
    }
    for(int i = 0;i<2;i++)
    {
        hResolution_nProt_Topology[0][i] ->GetXaxis()->SetTitle("True Pproton (MeV/c)");
        hResolution_nProt_Topology[0][i] ->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
        
        hResolution_nProt_Topology[1][i] ->GetXaxis()->SetTitle("True Pproton (MeV/c)");
        hResolution_nProt_Topology[1][i] ->GetYaxis()->SetTitle("Reco Pproton (MeV/c)");
    }
    

    for(int i=0;  i<AllEvents; i++)
    //for(int i=0;  i<100; i++)
    {
        tree->GetEntry(i);
        
        if(i%1000==0) cout<<i<<endl;
     
        //std::cout<<RecoProtonMom<<std::endl;
        if(RecoProtonMom>0)
        {
            hResolution_All[0]->Fill(TrueProtonMom[0], RecoProtonMom);  
            if(sel_prot_truePDG == 2212) hResolution_All[1]->Fill(TrueProtonMom, RecoProtonMom); 
            if(sel_prot_truePDG != 2212) hResolution_All[2]->Fill(TrueProtonMom, RecoProtonMom);  
            
            if(sel_prot_truePDG == 2212 && SelectedSample<20) //FGD1
            {
                hProtMom[0][0]->Fill(RecoProtonMom);
                hProtMom_NoCorrection[0][0]->Fill(RecoProtonMom_NoCorrection);
                
                if(RecoProton_Topo == TPCproton)
                {
                    hProtMom[0][1]->Fill(RecoProtonMom);
                    hProtMom_NoCorrection[0][1]->Fill(RecoProtonMom_NoCorrection);
                }
                if(RecoProton_Topo == FGDproton)
                {
                    hProtMom[0][2]->Fill(RecoProtonMom);
                    hProtMom_NoCorrection[0][2]->Fill(RecoProtonMom_NoCorrection);
                }
            }
            
            if(sel_prot_truePDG == 2212 && SelectedSample>20) //FGD2
            {
                hProtMom[1][0]->Fill(RecoProtonMom);
                hProtMom_NoCorrection[1][0]->Fill(RecoProtonMom_NoCorrection);
                
                if(RecoProton_Topo == TPCproton)
                {
                    hProtMom[1][1]->Fill(RecoProtonMom);
                    hProtMom_NoCorrection[1][1]->Fill(RecoProtonMom_NoCorrection);
                }
                if(RecoProton_Topo == FGDproton)
                {
                    hProtMom[1][2]->Fill(RecoProtonMom);
                    hProtMom_NoCorrection[1][2]->Fill(RecoProtonMom_NoCorrection);
                }
            }
            
        }
        
        if(SelectedSample == CC0PiNpNoPhotonFGD1 && sel_prot_truePDG == 2212)//CCOPi-Np FGD1
        {
             hResolution_nProt[0]->Fill(TrueProtonMom, RecoProtonMom);        
             hResolution_Tranverse_nProt[0]->Fill(sel_prot_trueDpt,  sel_prot_recoDpt );
             
             if(RecoProton_Topo == TPCproton)
             { 
                 hResolution_nProt_Topology[0][0]->Fill(TrueProtonMom, RecoProtonMom); 
             }
             if(RecoProton_Topo == FGDproton)
             {
                 hResolution_nProt_Topology[0][1]->Fill(TrueProtonMom, RecoProtonMom); 
             }
        }
        
        
        if(SelectedSample == CC0PiNpNoPhotonFGD2 && sel_prot_truePDG == 2212)//CCOPi-Np FGD2
        {
            hResolution_nProt[1]->Fill(TrueProtonMom, RecoProtonMom);
            hResolution_Tranverse_nProt[1]->Fill(sel_prot_trueDpt,  sel_prot_recoDpt );
            
             if(RecoProton_Topo == TPCproton)
             { 
                 hResolution_nProt_Topology[1][0]->Fill(TrueProtonMom, RecoProtonMom); 
             }
             if(RecoProton_Topo == FGDproton)
             {
                 hResolution_nProt_Topology[1][1]->Fill(TrueProtonMom, RecoProtonMom); 
             }
        }
    }
    
    for(int i = 0;i<2;i++)
    {
        for(int ix=1;ix<hResolution_nProt[i]->GetNbinsX() + 1; ix++)
        {
            double RMS = 0;
            double Mean = 0;
            for(int iy=1;iy<hResolution_nProt[i]->GetNbinsY() + 1; iy++)
            {  
                double BinTempCont = hResolution_nProt[i]->GetBinContent(ix,iy);
                Gauss_NProt[i][ix-1]->SetBinContent(iy,BinTempCont);

            }
                Mean= Gauss_NProt[i][ix-1]->GetMean();
                RMS = Gauss_NProt[i][ix-1]->GetRMS();
                
                hMeanRMS_nProt[i]->SetBinContent(ix,  Mean);
                hMeanRMS_nProt[i]->SetBinError(ix,  RMS);
                hRMS_nProt[i]->SetBinContent(ix,  RMS);
        }

        for(int ix=1;ix<hResolution_Tranverse_nProt[i]->GetNbinsX() + 1; ix++)
        {
            double RMS = 0;
            double Mean = 0;
            for(int iy=1;iy<hResolution_Tranverse_nProt[i]->GetNbinsY() + 1; iy++)
            {  
                double BinTempCont = hResolution_Tranverse_nProt[i]->GetBinContent(ix,iy);
                Gauss_NProt_Transvers[i][ix-1]->SetBinContent(iy,BinTempCont);

            }
                Mean= Gauss_NProt_Transvers[i][ix-1]->GetMean();
                RMS = Gauss_NProt_Transvers[i][ix-1]->GetRMS();
                
                hMeanRMS_Tranverse_nProt[i]->SetBinContent(ix,  Mean);
                hMeanRMS_Tranverse_nProt[i]->SetBinError(ix,  RMS);
                hRMS_Tranverse_nProt[i]->SetBinContent(ix,  RMS);
        }
    }
    
    c1->Print(Form("%s.pdf[",fname.Data()), "pdf");  
      
    for(int i = 0;i<3;i++)
    {
        hResolution_All[i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    }
    
    for(int i = 0;i<2;i++)
    {
        hResolution_nProt[i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hMeanRMS_nProt[i]->Draw("LE");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hRMS_nProt[i]->Draw();
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hResolution_Tranverse_nProt[i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hMeanRMS_Tranverse_nProt[i]->Draw("LE");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hRMS_Tranverse_nProt[i]->Draw();
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    }
    
    
    for(int i = 0;i<2;i++)
    {        
        hResolution_nProt_Topology[0][i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hResolution_nProt_Topology[1][i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
    }
    
    
    
    for(int i = 0;i<2;i++)
    {        
        for(int ik = 0;ik<3;ik++)
        { 
            hProtMom[i][ik]->SetLineStyle(kSolid);
            hProtMom[i][ik]->SetLineWidth(3);
            hProtMom[i][ik]->SetLineColor(kRed);

            hProtMom_NoCorrection[i][ik]->SetLineStyle(kDashed);
            hProtMom_NoCorrection[i][ik]->SetLineWidth(3);
            hProtMom_NoCorrection[i][ik]->SetLineColor(kBlue);
        
            hProtMom[i][ik]->Draw("");
            hProtMom_NoCorrection[i][ik]->Draw("SAME");
            
            TLegend *leg = new TLegend(0.35, 0.5, 0.8, 0.75);
            leg->AddEntry(hProtMom[i][ik], "EventSummary->ProtonMomentum", "l");
            leg->AddEntry(hProtMom_NoCorrection[i][ik], "ProtonCandidate->Momentum", "l");
            leg->SetFillColor(0);
            leg->SetFillStyle(0);
            leg->SetLineWidth(0);
            leg->SetLineColor(0);
            leg->Draw("same");
    
            c1->Print(Form("%s.pdf",fname.Data()), "pdf");
            delete leg;
        }
    }
    
    
    
    
    
    c1->Print(Form("%s.pdf]",fname.Data()), "pdf");    

    
    
    c1->Print("Gauss.pdf[", "pdf"); 
    for(int i=0;i<momBinCount;i++)
    {
        Gauss_NProt[0][i]->Draw();
         c1->Print("Gauss.pdf", "pdf");
    }
     c1->Print("Gauss.pdf]", "pdf");
    
    std::cout<< "\033[1;31mFinished ploting :)\033[0m "<<std::endl;
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



