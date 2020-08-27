using namespace std;

void CombPlotMaker()
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
        FontSizeTitle = 0.05;
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
    gStyle->SetTitleBorderSize(0);

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
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.13); // 0.075 -> 0.13 for colz option
    gStyle->SetPadLeftMargin(0.16);//to include both large/small font options

    // Fonts, sizes, offsets
    gStyle->SetTextFont(FontStyle);
    gStyle->SetTextSize(0.08);

    gStyle->SetLabelFont(FontStyle, "x");
    gStyle->SetLabelFont(FontStyle, "y");
    gStyle->SetLabelFont(FontStyle, "z");
    gStyle->SetLabelFont(FontStyle, "t");
    gStyle->SetLabelSize(FontSizeLabel, "x");
    gStyle->SetLabelSize(FontSizeLabel, "y");
    gStyle->SetLabelSize(FontSizeLabel, "z");
    gStyle->SetLabelOffset(0.015, "x");
    gStyle->SetLabelOffset(0.015, "y");
    gStyle->SetLabelOffset(0.015, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleOffset(1.14, "x");
    gStyle->SetTitleOffset(YOffsetTitle, "y");
    gStyle->SetTitleOffset(1.2, "z");

    gStyle->SetTitleStyle(0);
    gStyle->SetTitleFontSize(0.06);//0.08
    gStyle->SetTitleFont(FontStyle, "pad");
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleX(0.1f);
    gStyle->SetTitleW(0.8f);

    // use bold lines and markers
    gStyle->SetMarkerStyle(20);
    gStyle->SetHistLineWidth( Width_t(2.5) );
    gStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    gStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    gStyle->SetOptFit(0);

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
/////////////////////////////////////////////////////////////////////  
/////////////////////////////////////////////////////////////////////     
/////////////////////////////////////////////////////////////////////  
   
    
    bool DEBUGMODE=false;
    bool VERBOSE=false;
    
    TString PathName="/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/plots/";
    
    //TFile *file=TFile::Open("Run4_6M_Data.root");
    TFile *file=TFile::Open("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/Output/Run4Prod6T.root");
    TTree *tree;
    file->GetObject("default",tree);
    
    Int_t           accum_level[1][3];   //[NTOYS]
    Int_t           nProtonsTPC;
    Int_t           nProtonsFGD;
    Float_t         selmu_truemom;
    Float_t         selmu_mom[1];   //[NTOYS]
    Float_t         selmu_costheta[1];   //[NTOYS]
    Float_t         selmu_truecosTheta;
    
    
    
    TBranch        *b_accum_level;   //!
    TBranch        *b_nProtonsTPC;   //!
    TBranch        *b_nProtonsFGD;   //!
    TBranch        *b_selmu_truemom;   //!
    TBranch        *b_selmu_mom;   //!
    TBranch        *b_selmu_costheta;   //!
    TBranch        *b_selmu_truecosTheta;   //
       
    tree->SetBranchAddress("accum_level", accum_level, &b_accum_level);
    tree->SetBranchAddress("nProtonsTPC", &nProtonsTPC, &b_nProtonsTPC);
    tree->SetBranchAddress("nProtonsFGD", &nProtonsFGD, &b_nProtonsFGD);      
    tree->SetBranchAddress("selmu_truemom", &selmu_truemom, &b_selmu_truemom);
    tree->SetBranchAddress("selmu_mom", selmu_mom, &b_selmu_mom);
    tree->SetBranchAddress("selmu_costheta", selmu_costheta, &b_selmu_costheta);
    tree->SetBranchAddress("selmu_truecosTheta", &selmu_truecosTheta, &b_selmu_truecosTheta);
     
     
    int AllEvents=tree->GetEntries();
    if(VERBOSE) cout<< "\033[1;34mNumber of all events\033[0m" <<AllEvents<<endl;
    
    if(DEBUGMODE) AllEvents=100;
    
    
    TH1F *hmomentumCC0Pi0p= new TH1F("hmomentumCC0Pi0p", "hmomentumCC0Pi0p", 40, -0.8, 0.8);
    hmomentumCC0Pi0p->SetTitle("(accum[0][0]>7 && 0 protons)");
    hmomentumCC0Pi0p->GetXaxis()->SetTitle("muon candidate (p^{true}-p^{reco}/p^{true})");
    
    TH1F *hmomentumCC0PiNp= new TH1F("hmomentumCC0PiNp", "hmomentumCC0PiNp", 40, -0.8, 0.8);
    hmomentumCC0PiNp->SetTitle("(accum[0][0]>7 && N protons)");
    hmomentumCC0PiNp->GetXaxis()->SetTitle("muon candidate (p^{true}-p^{reco}/p^{true})");
    
    TH1F *hCosThetaCC0Pi0p= new TH1F("hCosThetaCC0Pi0p", "hCosThetaCC0Pi0p", 40, -0.15, 0.15);
    hCosThetaCC0Pi0p->SetTitle("(accum[0][0]>7 && 0 protons)");
    hCosThetaCC0Pi0p->GetXaxis()->SetTitle("muon candidate (cos#theta^{true}-cos#theta^{reco}/cos#theta^{true})");
    
    TH1F *hCosThetaCC0PiNp= new TH1F("hCosThetaCC0PiNp", "hCosThetaCC0PiNp", 40, -0.15, 0.15);
    hCosThetaCC0PiNp->SetTitle("(accum[0][0]>7 && N protons)");
    hCosThetaCC0PiNp->GetXaxis()->SetTitle("muon candidate (cos#theta^{true}-cos#theta^{reco}/cos#theta^{true})");

    for(int i=0;  i<AllEvents; i++)
    {
        tree->GetEntry(i);

        if(accum_level[0][0]>7)
        {
            if( (nProtonsTPC+nProtonsFGD)==0 )
            {
                hmomentumCC0Pi0p->Fill( (selmu_truemom-selmu_mom[0])/selmu_truemom );
                hCosThetaCC0Pi0p->Fill( (selmu_truecosTheta-selmu_costheta[0])/selmu_truecosTheta );
            }
            if( (nProtonsTPC+nProtonsFGD)>0 )
            {
                hmomentumCC0PiNp->Fill( (selmu_truemom-selmu_mom[0])/selmu_truemom );
                hCosThetaCC0PiNp->Fill( (selmu_truecosTheta-selmu_costheta[0])/selmu_truecosTheta );
            }
        }
    }
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    
    c1->Print( Form("%sCombFHCPlots.pdf(", PathName.Data() ), "pdf");
    
    long double normalizacja[2];
    normalizacja[0]=0;
    normalizacja[1]=0;
    int norma=1;
    int binowanie=hmomentumCC0Pi0p->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=hmomentumCC0Pi0p->GetBinContent(i);
        normalizacja[1]+=hmomentumCC0PiNp->GetBinContent(i);
    }
    
    hmomentumCC0Pi0p->Scale(norma/normalizacja[0]);
    hmomentumCC0PiNp->Scale(norma/normalizacja[1]);
    
    hmomentumCC0Pi0p->SetLineColor(kBlue);
    hmomentumCC0Pi0p->SetLineStyle(2);
            
    hmomentumCC0PiNp->SetLineStyle(7);
    hmomentumCC0PiNp->SetLineColor(kRed);
    
    hmomentumCC0Pi0p->Draw("");
    hmomentumCC0PiNp->Draw("SAME");
    
    TLegend * legend = new TLegend(0.65,0.65,0.85,0.85);
    legend->AddEntry(hmomentumCC0Pi0p, "CC0Pi0p","l");
    legend->AddEntry(hmomentumCC0PiNp, "CC0PiNp","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    
    c1->Print(Form("%sCombFHCPlots.pdf",PathName.Data()), "pdf");
    
    normalizacja[0]=0;
    normalizacja[1]=0;
    binowanie=hCosThetaCC0Pi0p->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=hCosThetaCC0Pi0p->GetBinContent(i);
        normalizacja[1]+=hCosThetaCC0PiNp->GetBinContent(i);
    }
    
    hCosThetaCC0Pi0p->Scale(norma/normalizacja[0]);
    hCosThetaCC0PiNp->Scale(norma/normalizacja[1]);
    
    hCosThetaCC0Pi0p->SetLineColor(kBlue);
    hCosThetaCC0Pi0p->SetLineStyle(2);
            
    hCosThetaCC0PiNp->SetLineStyle(7);
    hCosThetaCC0PiNp->SetLineColor(kRed);
    
    hCosThetaCC0Pi0p->Draw("");
    hCosThetaCC0PiNp->Draw("SAME");

    delete legend;
    TLegend *legend = new TLegend(0.65,0.65,0.85,0.85);
    legend->AddEntry(hCosThetaCC0Pi0p, "CC0Pi0p","l");
    legend->AddEntry(hCosThetaCC0PiNp, "CC0PiNp","l");
    legend->SetTextSize(0.035);
    legend->Draw();
    
    c1->Print(Form("%sCombFHCPlots.pdf)",PathName.Data()), "pdf");
    
}
