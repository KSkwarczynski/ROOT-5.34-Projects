#include "TH2.h"
#include "TPad.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMatrixDSym.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TFile.h"
#include "TObjArray.h"
#include "TObjString.h"
#include <string>
#include <iostream>

void PlotObsNorm(TString postfitfile) {
    gStyle->SetOptStat(0);
    gStyle->SetTextFont(40);
    gROOT->SetBatch(kTRUE);

    TStyle *t2kStyle= new TStyle("T2K","T2K approved plots style");

    // use plain black on white colors
    t2kStyle->SetFrameBorderMode(0);
    t2kStyle->SetCanvasBorderMode(0);
    t2kStyle->SetPadBorderMode(0);
    t2kStyle->SetPadColor(0);
    t2kStyle->SetCanvasColor(0);
    t2kStyle->SetStatColor(0);
    t2kStyle->SetLegendBorderSize(1); 

    // set the paper & margin sizes
    t2kStyle->SetPaperSize(20,26);
    t2kStyle->SetPadTopMargin(0.10);
    t2kStyle->SetPadRightMargin(0.16);
    t2kStyle->SetPadBottomMargin(0.16);
    t2kStyle->SetPadLeftMargin(0.13);

    // use large Times-Roman fonts
    t2kStyle->SetTextFont(132);
    t2kStyle->SetTextSize(0.06);
    t2kStyle->SetLabelFont(132,"x");
    t2kStyle->SetLabelFont(132,"y");
    t2kStyle->SetLabelFont(132,"z");
    t2kStyle->SetLabelSize(0.05,"x");
    t2kStyle->SetTitleSize(0.06,"x");
    t2kStyle->SetLabelSize(0.05,"y");
    t2kStyle->SetTitleSize(0.06,"y");
    t2kStyle->SetTitleOffset(0.9,"y");
    t2kStyle->SetTitleOffset(0.75,"z");
    t2kStyle->SetLabelSize(0.05,"z");
    t2kStyle->SetTitleSize(0.06,"z");
    t2kStyle->SetLabelFont(132,"t");
    t2kStyle->SetTitleFont(132,"x");
    t2kStyle->SetTitleFont(132,"y");
    t2kStyle->SetTitleFont(132,"z");
    t2kStyle->SetTitleFont(132,"t"); 
    t2kStyle->SetTitleFillColor(0);
    t2kStyle->SetTitleX(0.25);
    t2kStyle->SetTitleFontSize(0.06);
    t2kStyle->SetTitleFont(132,"pad");

    t2kStyle->SetTitleBorderSize(1);    
    t2kStyle->SetPadBorderSize(1);    
    t2kStyle->SetCanvasBorderSize(1);    
 
    // use bold lines and markers
    t2kStyle->SetMarkerStyle(20);
    t2kStyle->SetHistLineWidth(1.85);
    t2kStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    t2kStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
//    t2kStyle->SetOptTitle(0);
    t2kStyle->SetOptStat(0);
    t2kStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    t2kStyle->SetPadTickX(1);
    t2kStyle->SetPadTickY(1);

    // Add a greyscale palette for 2D plots
    int ncol=50;
    double dcol = 1./float(ncol);
    double gray = 1;

    TColor **theCols = new TColor*[ncol];

    for (int i=0;i<ncol;i++) theCols[i] = new TColor(999-i,0.0,0.7,0.7);

    for (int j = 0; j < ncol; j++) {
        theCols[j]->SetRGB(gray,gray,gray);
        gray -= dcol;
    }

    int ColJul[100];
    for  (int i=0; i<100; i++) ColJul[i]=999-i;
    //t2kStyle->SetPalette(ncol,ColJul);

//    // Define a nicer color palette (red->blue)
//    // Uncomment these lines for a color palette (default is B&W)
    //t2kStyle->SetPalette(1,0);  // use the nice red->blue palette
    
    const Int_t NCont = 255;

//    // Uncomment these colours for the rainbow (blue -> yellow -> red) palette
//    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
//    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
//    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
//    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

//    // Uncomment these to use the black-bady palette
//    Double_t white[3]   = {1, 1, 1};
//    Double_t yellow[3]  = {1, 1, 0};
//    Double_t orange[3]  = {1, 0.5, 0};
//    Double_t crimson[3]     = {1, 0, 0};
//    Double_t black[3]   = {0, 0, 0};
//    Double_t red[NRGBs]    = {black[0], crimson[0], orange[0], yellow[0], white[0]};
//    Double_t green[NRGBs]  = {black[1], crimson[1], orange[1], yellow[1], white[1]};
//    Double_t blue[NRGBs]   = {black[2], crimson[2], orange[2], yellow[2], white[2]};
//    Double_t stops[NRGBs]  = {   0.00,    0.25,       0.5,      0.75,     1.00};

//    // Uncomment these to use the blue->white->red palette (good for correlation matrices)
    const Int_t NRGBs = 3;
    Double_t stops[NRGBs] = { 0.00, 0.50, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 1.00, 1.00 };
    Double_t green[NRGBs] = { 0.00, 1.00, 0.00 };
    Double_t blue[NRGBs]  = { 1.00, 1.00, 0.00 };

//    //Uncomment these lines to apply any coloured palette
    TColor::CreateGradientColorTable(NRGBs,stops,red,green,blue,NCont);
    t2kStyle->SetNumberContours(NCont+1); 
    //t2kStyle->SetPalette(NRGBs,0);

    // End of definition of t2kStyle
    gROOT->SetStyle("T2K");
    //gROOT->ForceStyle();
    gStyle->SetPaintTextFormat("4.2f");
    
    TFile *InputFile = TFile::Open(postfitfile);

     
    //TMatrixDSym* cov     = (TMatrixDSym*)(InputFile->Get("obsNorm_cov")); //WARNING
    TMatrixDSym* cov     = (TMatrixDSym*)(InputFile->Get("Covariance_Matrix")); //WARNING
    
    
    //int n_dete  = 574; //WARNING
    int n_dete  = 701; //WARNING

    TH2D cov_dete("Detector_Covariance_Matrix", "Detector Covariance Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    TH2D corr_dete("Detector_Correlation_Matrix", "Detector Correlation Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    
        // Detector correlation matrix
	for(int i = 0; i < n_dete; i++){
		for(int j = 0; j < n_dete; j++){
            cov_dete.SetBinContent(cov_dete.GetBin(i+1,j+1), (*cov)(i,j));
            correlation = (*cov)(i,j) / sqrt((*cov)(i,i) * (*cov)(j,j));
			if (fabs(correlation) > 0.01) { corr_dete.SetBinContent(corr_dete.GetBin(i+1,j+1), correlation); }
		}
	}
    
    
    
    TCanvas c7("c7","Detector Postfit",1600,1200);
    corr_dete.GetXaxis()->SetRangeUser(0,n_dete);
    corr_dete.GetYaxis()->SetRangeUser(0,n_dete);
    corr_dete.GetZaxis()->SetRangeUser(-0.99, 1.00);
	corr_dete.GetXaxis()->SetTitle("Parameter Number");
	corr_dete.GetYaxis()->SetTitle("Parameter Number");
    corr_dete.Draw("COLZ");
    c7.Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    
}

string GetFileName(string name_in){//please find a smarter way to do this...
   int size = name_in.size();
   return name_in.substr(12, size-5);
   std::cout << "Filename short " << name_in.substr(12, size-5) <<std::endl;
}
