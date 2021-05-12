void PlotFSIplot(TString fname) {

    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    //gPad->SetGrid();
    gStyle->SetPalette(51); 
    
    TFile *f1 = TFile::Open(fname);


    TH1D *hFSImodeCCQE_C12;
    TH1D *hFSImodeCCQE_O16; 
    TH1D *hFSImode2p2h_C12; 
    TH1D *hFSImodeRES_C12; 

        
    hFSImodeCCQE_C12 = (TH1D*) f1->Get( "hFSImodeCCQE_C12" );
    hFSImodeCCQE_O16 = (TH1D*) f1->Get( "hFSImodeCCQE_O16" );
    hFSImode2p2h_C12 = (TH1D*) f1->Get( "hFSImode2p2h_C12" );
    hFSImodeRES_C12 = (TH1D*) f1->Get( "hFSImodeRES_C12" );


    hFSImodeCCQE_C12->SetLineColor(kRed);
        hFSImodeCCQE_O16->SetLineColor(kCyan);
    hFSImode2p2h_C12->SetLineColor(kViolet);
    hFSImodeRES_C12->SetLineColor(kGreen);
              
    double norm = 1/hFSImodeCCQE_C12->Integral();
    hFSImodeCCQE_C12->Scale(norm);
        
    double norm = 1/hFSImodeCCQE_O16->Integral();
    hFSImodeCCQE_O16->Scale(norm);
    
    double norm = 1/hFSImode2p2h_C12->Integral();
    hFSImode2p2h_C12->Scale(norm);
    
    double norm = 1/hFSImodeRES_C12->Integral();
    hFSImodeRES_C12->Scale(norm);
    
    
    hFSImodeRES_C12->GetXaxis()->SetRangeUser(1, 3);
    hFSImodeRES_C12->GetXaxis()->SetBinLabel(2,"no FSI");
    hFSImodeRES_C12->GetXaxis()->SetBinLabel(3,"FSI");
    
    
    c1->Print("nucleonFSI.pdf[", "pdf");  
    
    hFSImodeRES_C12->Draw();
    hFSImode2p2h_C12->Draw("SAME");
    hFSImodeCCQE_C12->Draw("SAME");
    
    TLegend *legend = new TLegend(0.75,0.75,0.9,0.9);
    legend->AddEntry(hFSImodeCCQE_C12, "CCQE","l");
    legend->AddEntry(hFSImode2p2h_C12, "2p2h","l");
    legend->AddEntry(hFSImodeRES_C12, "RES","l");
    legend->SetTextSize(0.04);
    legend->Draw();
    
    c1->Print("nucleonFSI.pdf", "pdf");
    
    hFSImodeCCQE_C12->GetXaxis()->SetRangeUser(1, 3);
    hFSImodeCCQE_C12->GetXaxis()->SetBinLabel(2,"no FSI");
    hFSImodeCCQE_C12->GetXaxis()->SetBinLabel(3,"FSI");
    
    hFSImodeCCQE_C12->Draw();
    hFSImodeCCQE_O16->Draw("SAME");
    
    TLegend *legend = new TLegend(0.70,0.75,0.9,0.9);
    legend->AddEntry(hFSImodeCCQE_C12, "CCQE C12","l");
    legend->AddEntry(hFSImodeCCQE_O16, "CCQE O16","l");
    legend->SetTextSize(0.04);
    legend->Draw();
    
    c1->Print("nucleonFSI.pdf", "pdf");

    c1->Print("nucleonFSI.pdf]", "pdf");  
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
    gStyle->SetLabelSize(0.070, "x");
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
    //gStyle->SetPalette(1);  // use the rainbow color set

    // -- axis --
    gStyle->SetStripDecimals(kFALSE); // don't do 1.0 -> 1
    //  TGaxis::SetMaxDigits(3); // doesn't have an effect
    // no supressed zeroes!
    gStyle->SetHistMinimumZero(kTRUE);       
    
    gROOT->ForceStyle();    
}
    
