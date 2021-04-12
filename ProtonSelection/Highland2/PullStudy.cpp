using namespace std;

void PullStudy()
{
    
    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51); 
   
    
    bool DEBUGMODE=false;
    bool VERBOSE=true;
    
    TFile *file=TFile::Open("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/OutputNewHighland/ProtonRun8a.root");
    TTree *tree;
    file->GetObject("default",tree);
    
    Int_t           accum_level[1][4];   //[NTOYS]
    Int_t           NTPCSec;
    Float_t         TPCSecPrPidLik[16];   //[NTPCSec]
    Int_t           TPCSecTId[16];   //[NTPCSec]
    Float_t         TPCSecPrPull[16];   //[NTPCSec]
    Int_t         TPCSecCharge[16];   //[NTPCSec]
    Int_t           NFGDSec;
    Float_t         FGDSecProtPull[9];   //[NFGDSec]   
    Int_t           FGDSecTId[9];   //[NFGDSec]
       
    TBranch        *b_accum_level;   //!
    TBranch        *b_NTPCSec;   //!
    TBranch        *b_TPCSecPrPidLik;   //!
    TBranch        *b_TPCSecTId;   //!
    TBranch        *b_TPCSecPrPull;   //!
    TBranch        *b_TPCSecCharge;   //!
    TBranch        *b_NFGDSec;   //!
    TBranch        *b_FGDSecProtPull;   //!
    TBranch        *b_FGDSecTId;   //!
    
    tree->SetBranchAddress("accum_level", accum_level, &b_accum_level);
    tree->SetBranchAddress("NTPCSec", &NTPCSec, &b_NTPCSec);
    tree->SetBranchAddress("TPCSecPrPidLik", TPCSecPrPidLik, &b_TPCSecPrPidLik);
    tree->SetBranchAddress("TPCSecTId", TPCSecTId, &b_TPCSecTId);
    tree->SetBranchAddress("TPCSecPrPull", TPCSecPrPull, &b_TPCSecPrPull);
    tree->SetBranchAddress("TPCSecCharge", TPCSecCharge, &b_TPCSecCharge);
    
    tree->SetBranchAddress("NFGDSec", &NFGDSec, &b_NFGDSec);
    tree->SetBranchAddress("FGDSecProtPull", FGDSecProtPull, &b_FGDSecProtPull);
    tree->SetBranchAddress("FGDSecTId", FGDSecTId, &b_FGDSecTId);

    TFile *fileData=TFile::Open("/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/OutputNewHighland/DataProtonRun8a.root");
    TTree *treeData;
    fileData->GetObject("default",treeData);
    
    Int_t           accum_levelData[1][4];   //[NTOYS]
    Int_t           NTPCSecData;
    Float_t         TPCSecPrPidLikData[16];   //[NTPCSec]
    Float_t         TPCSecPrPullData[16];   //[NTPCSec]
    Int_t         TPCSecChargeData[16];   //[NTPCSec]
    Int_t           NFGDSecData;
    Float_t         FGDSecProtPullData[9];   //[NFGDSec]   
       
    TBranch        *b_accum_levelData;   //!
    TBranch        *b_NTPCSecData;   //!
    TBranch        *b_TPCSecPrPidLikData;   //!
    TBranch        *b_TPCSecPrPullData;   //!
    TBranch         *b_TPCSecChargeData;   //[NTPCSec]
    TBranch        *b_NFGDSecData;   //!
    TBranch        *b_FGDSecProtPullData;   //!
    
    treeData->SetBranchAddress("accum_level", accum_levelData, &b_accum_levelData);
    treeData->SetBranchAddress("NTPCSec", &NTPCSecData, &b_NTPCSecData);
    treeData->SetBranchAddress("TPCSecPrPidLik", TPCSecPrPidLikData, &b_TPCSecPrPidLikData);
    treeData->SetBranchAddress("TPCSecCharge", TPCSecChargeData, &b_TPCSecChargeData);

    treeData->SetBranchAddress("TPCSecPrPull", TPCSecPrPullData, &b_TPCSecPrPullData);
    treeData->SetBranchAddress("NFGDSec", &NFGDSecData, &b_NFGDSecData);
    treeData->SetBranchAddress("FGDSecProtPull", FGDSecProtPullData, &b_FGDSecProtPullData);
    
    
    double POTweight = 4.15013E+20 / 4.45319E+21;
     
    int AllEvents=tree->GetEntries();
    if(VERBOSE) cout<< "\033[1;34mNumber of all events \033[0m" <<AllEvents<<endl;
    
    if(DEBUGMODE) AllEvents=100;
    
    
    TH1D *FGDlikelihoodData = new TH1D("FGDlikelihoodData","Proton Pull",40, -10, 8);
    TH1D *FGDlikelihoodProton = new TH1D("FGDlikelihoodProton","Proton Pull",40, -10, 8);
    TH1D *FGDlikelihoodPiPlus = new TH1D("FGDlikelihoodPiPlus","Proton Pull",40, -10, 8);
    TH1D *FGDlikelihoodNonProton = new TH1D("FGDlikelihoodNonProton","Proton Pull",40, -10, 8);

    TH1D *TPClikelihoodData = new TH1D("TPClikelihoodData","Proton Likelihood",20, 0, 1);
    TH1D *TPClikelihoodMuon = new TH1D("TPClikelihoodMuon","Proton Likelihood",20, 0, 1);
    TH1D *TPClikelihoodProton = new TH1D("TPClikelihoodProton","Proton Likelihood",20, 0, 1);
    TH1D *TPClikelihoodPiPlus = new TH1D("TPClikelihoodPiPlus","Proton Likelihood",20, 0, 1);
    TH1D *TPClikelihoodNonProton = new TH1D("TPClikelihoodNonProton","Proton Likelihood",20, 0, 1);

    TH1D *TPCpullData = new TH1D("TPCpullData","Proton Pull",40, -10, 8);
    TH1D *TPCpullMuon = new TH1D("TPCpullMuon","Proton Pull",40, -10, 8);
    TH1D *TPCpullProton = new TH1D("TPCpullProton","Proton Pull",40, -10, 8);
    TH1D *TPCpullPiPlus = new TH1D("TPCpullPiPlus","Proton Pull",40, -10, 8);
    TH1D *TPCpullNonProton = new TH1D("TPCpullNonProton","Proton Pull",40, -10, 8);
    
    FGDlikelihoodData->GetXaxis()->SetTitle("Proton Pull");
    TPCpullData->GetXaxis()->SetTitle("Proton Pull");
    TPClikelihoodData->GetXaxis()->SetTitle("Proton Likelihood"); 

    for(int i=0;  i<AllEvents; i++)
    {
        tree->GetEntry(i);

        if(accum_level[0][0]>5) //CCInclusive
        {
            for(int ig=0;  ig<NTPCSec; ig++)
            {
                if(TPCSecTId[ig]==2212)
                {
                    TPClikelihoodProton->Fill( TPCSecPrPidLik[ig], POTweight );
                    if(TPCSecCharge[ig]>0)TPCpullProton->Fill( TPCSecPrPull[ig], POTweight );

                }
                if(TPCSecTId[ig]==211)
                {
                    TPClikelihoodPiPlus->Fill( TPCSecPrPidLik[ig], POTweight );
                    if(TPCSecCharge[ig]>0)TPCpullPiPlus->Fill( TPCSecPrPull[ig], POTweight );
                }
                
                
                if(TPCSecTId[ig]==13)
                {
                    TPClikelihoodMuon->Fill( TPCSecPrPidLik[ig], POTweight );
                    if(TPCSecCharge[ig]>0) TPCpullMuon->Fill( TPCSecPrPull[ig], POTweight );

                }
                if(TPCSecTId[ig]!=2212 && TPCSecTId[ig]!=13 && TPCSecTId[ig]!=211)
                {
                    TPClikelihoodNonProton->Fill( TPCSecPrPidLik[ig], POTweight );
                    if(TPCSecCharge[ig]>0) TPCpullNonProton->Fill( TPCSecPrPull[ig], POTweight );

                }
            }

            for(int ig=0;  ig<NFGDSec; ig++)
            {
                if(FGDSecTId[ig]==2212)
                {
                    FGDlikelihoodProton->Fill( FGDSecProtPull[ig], POTweight );
                }
                if(FGDSecTId[ig]==211)
                {
                    FGDlikelihoodPiPlus->Fill( FGDSecProtPull[ig], POTweight );
                }
                if(FGDSecTId[ig]!=2212 && FGDSecTId[ig]!=2212)
                {
                    FGDlikelihoodNonProton->Fill( FGDSecProtPull[ig], POTweight );
                }
            }
        }
    }
    
    int AllEvents=treeData->GetEntries();
    for(int i=0;  i<AllEvents; i++)
    {
        treeData->GetEntry(i);

        if(accum_levelData[0][0]>5) //CCInclusive
        {
            for(int ig=0;  ig<NTPCSecData; ig++)
            {
                TPClikelihoodData->Fill( TPCSecPrPidLikData[ig] );
                if(TPCSecChargeData[ig]>0) TPCpullData->Fill( TPCSecPrPullData[ig] );

            }
            
            for(int ig=0;  ig<NFGDSecData; ig++)
            {
                FGDlikelihoodData->Fill( FGDSecProtPullData[ig]);
            }
        }
    }
    
    THStack *FGD_Stack= new THStack( "FGD_Stack", "FGD Proton Pull, CC Inclusive" );
    FGD_Stack->Add( FGDlikelihoodNonProton );
    FGD_Stack->Add( FGDlikelihoodPiPlus );    
    FGD_Stack->Add( FGDlikelihoodProton );    
    
    FGDlikelihoodProton->SetFillColor(kGreen);
    FGDlikelihoodProton->SetFillStyle(3001);
    FGDlikelihoodProton->SetLineColor(kGreen);
    
    FGDlikelihoodPiPlus->SetFillColor(kBlue);
    FGDlikelihoodPiPlus->SetFillStyle(3001);
    FGDlikelihoodPiPlus->SetLineColor(kBlue);
    
    FGDlikelihoodNonProton->SetFillColor(kBlack);
    FGDlikelihoodNonProton->SetFillStyle(3001);
    FGDlikelihoodNonProton->SetLineColor(kBlack);
    
    THStack *TPC_Stack= new THStack( "TPC_Stack", "TPC Proton Likelihood, CC Inclusive" );
    TPC_Stack->Add( TPClikelihoodNonProton );
    TPC_Stack->Add( TPClikelihoodMuon );
    TPC_Stack->Add( TPClikelihoodPiPlus );
    TPC_Stack->Add( TPClikelihoodProton );
    
    TPClikelihoodProton->SetFillColor(kGreen);
    TPClikelihoodProton->SetFillStyle(3001);
    TPClikelihoodProton->SetLineColor(kGreen);

    TPClikelihoodNonProton->SetFillColor(kBlack);
    TPClikelihoodNonProton->SetFillStyle(3001);
    TPClikelihoodNonProton->SetLineColor(kBlack);
    
    TPClikelihoodPiPlus->SetFillColor(kBlue);
    TPClikelihoodPiPlus->SetFillStyle(3001);
    TPClikelihoodPiPlus->SetLineColor(kBlue);
    
    TPClikelihoodMuon->SetFillColor(kRed);
    TPClikelihoodMuon->SetFillStyle(3001);
    TPClikelihoodMuon->SetLineColor(kRed);
    
    THStack *TPC_Stack_pull = new THStack( "TPC_Stack_pull", "TPC Proton Pull, CC Inclusive, positive tracks" );
    TPC_Stack_pull->Add( TPCpullNonProton );
    TPC_Stack_pull->Add( TPCpullPiPlus );
    TPC_Stack_pull->Add( TPCpullMuon );
    TPC_Stack_pull->Add( TPCpullProton );
    
    TPCpullProton->SetFillColor(kGreen);
    TPCpullProton->SetFillStyle(3001);
    TPCpullProton->SetLineColor(kGreen);

    TPCpullPiPlus->SetFillColor(kBlue);
    TPCpullPiPlus->SetFillStyle(3001);
    TPCpullPiPlus->SetLineColor(kBlue);
    
    TPCpullNonProton->SetFillColor(kBlack);
    TPCpullNonProton->SetFillStyle(3001);
    TPCpullNonProton->SetLineColor(kBlack);
    
    TPCpullMuon->SetFillColor(kRed);
    TPCpullMuon->SetFillStyle(3001);
    TPCpullMuon->SetLineColor(kRed);
    
    c1->Print("protonPull.pdf[", "pdf");    

    FGD_Stack->Draw("");
    FGDlikelihoodData->Draw("pe SAME");
    
    TLegend *legend = new TLegend(0.75,0.75,0.9,0.9);
    legend->AddEntry(FGDlikelihoodData, "Data","pe");
    legend->AddEntry(FGDlikelihoodProton, "Proton","l");
    legend->AddEntry(FGDlikelihoodPiPlus, "Pi+","l");
    legend->AddEntry(FGDlikelihoodNonProton, "Other","l");
    legend->SetTextSize(0.04);
    legend->Draw();
    
    FGD_Stack->GetXaxis();
    FGDlikelihoodData->GetXaxis()->SetTitle("Proton Pull");  
    
    c1->Print("protonPull.pdf", "pdf");
  
    TPC_Stack_pull->Draw("");
    TPCpullData->Draw("pe same");
    
    TLegend *legend2 = new TLegend(0.75,0.75,0.9,0.9);
    legend2->AddEntry(TPCpullData, "Data","pe");
    legend2->AddEntry(TPCpullProton, "Proton","l");
    legend2->AddEntry(TPCpullMuon, "Muon","l");
    legend2->AddEntry(TPCpullPiPlus, "Pi+","l");
    legend2->AddEntry(TPCpullNonProton, "Other","l");
    legend2->SetTextSize(0.04);
    legend2->Draw();
    
    TPC_Stack_pull->GetXaxis();
    TPC_Stack_pull->GetXaxis()->SetTitle("Proton Pull");  
    
    c1->Print("protonPull.pdf", "pdf");

        
    c1->SetLogy();
      
    TPC_Stack->Draw("");
    TPClikelihoodData->Draw("pe same");
    
    TLegend *legend3 = new TLegend(0.75,0.75,0.9,0.9);
    legend3->AddEntry(TPClikelihoodData, "Data","pe");
    legend3->AddEntry(TPClikelihoodProton, "Proton","l");
    legend3->AddEntry(TPClikelihoodMuon, "Muon","l");
    legend3->AddEntry(TPClikelihoodPiPlus, "Pi+","l");
    legend3->AddEntry(TPClikelihoodNonProton, "Other","l");
    legend3->SetTextSize(0.04);
    legend3->Draw();
    
    TPC_Stack->GetXaxis();
    TPC_Stack->GetXaxis()->SetTitle("Proton Likelihood");  
        
    c1->Print("protonPull.pdf", "pdf");
        
    c1->Print("protonPull.pdf]", "pdf");
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
        FontSizeTitle = 0.045;
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
    gStyle->SetLabelSize(0.030, "z");
    gStyle->SetLabelOffset(0.008, "x");
    gStyle->SetLabelOffset(0.008, "y");
    gStyle->SetLabelOffset(0.006, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleSize(FontSizeTitle, "t");
    gStyle->SetTitleOffset(1.1, "x");
    gStyle->SetTitleOffset(1.1, "y");
    gStyle->SetTitleOffset(1.1, "z");

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
    
