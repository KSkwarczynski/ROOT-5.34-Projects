
void ResolutionSFGD(TString fname)
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

    Double_t         RecoMuonMom;
    tree->SetBranchStatus( "Pmu", true);
    tree->SetBranchAddress("Pmu", &RecoMuonMom);
    
    Double_t         TrueMuonMom;
    tree->SetBranchStatus( "TruePmu", true);
    tree->SetBranchAddress("TruePmu", &TrueMuonMom);

    
    int AllEvents = tree->GetEntries();
    
   std::cout<< "\033[1;34mNumber of all events in the tree \033[0m " <<AllEvents<<std::endl;
       
    const int momBinCount = 100;
    const int momBinMax = 2000;
    const int momBinMin = 0;
    
    
    TH2F *hResolution[2];
    TH1F *hRMS_nProt[2];
    TH1F *hMeanRMS_nProt[2];
    
    std::string SampleName[2] = {"SFGD CC0#pi-0p", "SFGD CC0#pi-Np"};
    hResolution[0] = new TH2F("SFGD CC0#pi-0p", "SFGD CC0#pi-0p", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
    hResolution[1] = new TH2F("SFGD CC0#pi-Np", "SFGD CC0#pi-Np", momBinCount, momBinMin, momBinMax, momBinCount, momBinMin, momBinMax);
     
    hRMS_nProt[0] = new TH1F("RMS for SFGD CC0#pi-0p", "RMS for SFGD CC0#pi-0p", momBinCount, momBinMin, momBinMax);
    hRMS_nProt[1] = new TH1F(Form("hRMS_nProt_FGD%i",1), "RMS for SFGD CC0#pi-Np", momBinCount, momBinMin, momBinMax);

    hMeanRMS_nProt[0] = new TH1F("Mean and RMS for SFGD CC0#pi-0p", "Mean and RMS for SFGD CC0#pi-0p", momBinCount, momBinMin, momBinMax);
    hMeanRMS_nProt[1] = new TH1F(Form("hMeanRMS_nProt_FGD%i",1), "Mean and RMS for SFGD CC0#pi-Np", momBinCount, momBinMin, momBinMax);

    TH1F *Gauss_NProt[2][momBinCount];
    TH1F *Gauss_NProt_Transvers[2][momBinCount];
    
    for(int i = 0;i<2;i++)
    {

        hResolution[i] ->GetXaxis()->SetTitle("True Momentum #mu (MeV/c)");
        hResolution[i] ->GetYaxis()->SetTitle("Reco Momentum #mu (MeV/c)");
        
        hRMS_nProt[i]->GetXaxis()->SetTitle("True Momentum #mu (MeV/c)");
        
        hMeanRMS_nProt[i]->GetXaxis()->SetTitle("True Momentum #mu (MeV/c)");


        for(int ig=0;ig<momBinCount;ig++)
        {
            Gauss_NProt[i][ig] = new TH1F(Form("Gauss_NProt%ig_FGD%i",ig,i+1), "Gauss_NProt", momBinCount, momBinMin, momBinMax);
            Gauss_NProt_Transvers[i][ig] = new TH1F(Form("Gauss_NProt_Transvers%ig_FGD%i",ig,i+1), "Gauss_NProt_Transvers", momBinCount, momBinMin, momBinMax);
        }  
        
    }
   
    int TPCproton = 1;
    int FGDproton = 2;
    
    int CC0Pi0P = 101;
    int CC0PiNp = 102;

    for(int i=0;  i<AllEvents; i++)
    //for(int i=0;  i<100; i++)
    {
        tree->GetEntry(i);
        
        if(i%10000==0) cout<<i<<endl;
     
        //std::cout<<RecoMuonMom<<std::endl;
        if(SelectedSample == CC0Pi0P)
        {
            hResolution[0]->Fill(TrueMuonMom, RecoMuonMom);
        }
        
        if(SelectedSample == CC0PiNp)//CCOPi-Np FGD1
        {
             hResolution[1]->Fill(TrueMuonMom, RecoMuonMom);   
        }
    }
    
    for(int i = 0;i<2;i++)
    {
        for(int ix=1;ix<hResolution[i]->GetNbinsX() + 1; ix++)
        {
            double RMS = 0;
            double Mean = 0;
            for(int iy=1;iy<hResolution[i]->GetNbinsY() + 1; iy++)
            {  
                double BinTempCont = hResolution[i]->GetBinContent(ix,iy);
                Gauss_NProt[i][ix-1]->SetBinContent(iy,BinTempCont);

            }
                Mean= Gauss_NProt[i][ix-1]->GetMean();
                RMS = Gauss_NProt[i][ix-1]->GetRMS();
                
                hMeanRMS_nProt[i]->SetBinContent(ix,  Mean);
                hMeanRMS_nProt[i]->SetBinError(ix,  RMS);
                hRMS_nProt[i]->SetBinContent(ix,  RMS);
        }
    }
    
    c1->Print(Form("%s.pdf[",fname.Data()), "pdf");  
    
    for(int i = 0;i < 2;i++)
    {
        hResolution[i]->Draw("COLZ");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hRMS_nProt[i]->Draw("");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
        
        hMeanRMS_nProt[i]->Draw("");
        c1->Print(Form("%s.pdf",fname.Data()), "pdf");
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



