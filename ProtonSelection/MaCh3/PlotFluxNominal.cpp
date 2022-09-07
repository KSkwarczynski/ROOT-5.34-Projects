void PlotFluxNominal(TString postfitfile) {

      gStyle->SetOptFit(111);

    // Open a TCanvas to write the posterior onto
    TCanvas* c0 = new TCanvas("c0", "c0", 0, 0, 1024, 1024);
    c0->SetGrid();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    gStyle->SetPaintTextFormat("4.1f"); //Precision of value in matrix element
    //gStyle->SetPaintTextFormat("5.2f");
    //gStyle->SetPaintTextFormat("6.3f");
	
    c0->SetTickx();
    c0->SetTicky();
    c0->SetLeftMargin(0.1);
    c0->SetBottomMargin(0.1);
    c0->SetTopMargin(0.02);
    c0->SetRightMargin(0.15);
  
    // Take away the stat box
    gStyle->SetOptStat(0);
    // Make pretty correlation colors (red to blue)
    const int NRGBs = 5;
    TColor::InitializeColors();
    Double_t stops[NRGBs] = { 0.00, 0.25, 0.50, 0.75, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.25, 1.00, 1.00, 0.50 };
    Double_t green[NRGBs] = { 0.00, 0.25, 1.00, 0.25, 0.00 };
    Double_t blue[NRGBs]  = { 0.50, 1.00, 1.00, 0.25, 0.00 };
    TColor::CreateGradientColorTable(5, stops, red, green, blue, 255);
    gStyle->SetNumberContours(255);
    
    TFile *InputFile = TFile::Open(postfitfile);

    TMatrixDSym* xsec_cov     = (TMatrixDSym*)(InputFile->Get("xsec_cov")); //WARNING
    TH2D* hcov     = (TH2D*)(InputFile->Get("hcov")); //WARNING
    
    int n_dete  = 100; //WARNING
    TH2D cov_dete("Covariance_Matrix", "Covariance Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    TH2D corr_dete("Correlation_Matrix", "Correlation Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    
        // Detector correlation matrix
	for(int i = 0; i < n_dete; i++){
		for(int j = 0; j < n_dete; j++){
            hcov->SetBinContent(hcov->GetBin(i+1,j+1), 0);
            hcov->SetBinContent(hcov->GetBin(i+1,j+1), (*xsec_cov)(i,j));
            
            hcov->GetXaxis()->SetBinLabel(i+1,"");
            hcov->GetYaxis()->SetBinLabel(j+1,"");
            cov_dete.SetBinContent(cov_dete.GetBin(i+1,j+1), (*xsec_cov)(i,j));
            correlation = (*xsec_cov)(i,j) / sqrt((*xsec_cov)(i,i) * (*xsec_cov)(j,j));
			if (fabs(correlation) > 0.01) { corr_dete.SetBinContent(corr_dete.GetBin(i+1,j+1), correlation); }
		}
	}
	
const int nBinsSameSignMu = 11;
const int nBinsSameSignE = 7;
const int nBinsWrongSignMu = 5;
const int nBinsWrongSignE = 2;

	hcov->GetXaxis()->SetBinLabel(0+1,"ND280 FHC #nu_{#mu}");
    hcov->GetYaxis()->SetBinLabel(0+1,"ND280 FHC #nu_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsSameSignMu+1,"ND280 FHC #nu_{e}");
    hcov->GetYaxis()->SetBinLabel(nBinsSameSignMu+1,"ND280 FHC #nu_{e}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{#mu}");
    hcov->GetYaxis()->SetBinLabel(nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsWrongSignE+nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{e}");
    hcov->GetYaxis()->SetBinLabel(nBinsWrongSignE+nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{e}");
    /////////////////
    hcov->GetXaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{#mu}");
    hcov->GetYaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+nBinsSameSignE+nBinsSameSignMu+1,"ND280 FHC #bar{#nu}_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #bar{#nu}_{#mu}");
    hcov->GetYaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #bar{#nu}_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #bar{#nu}_{e}");
    hcov->GetYaxis()->SetBinLabel(nBinsWrongSignMu+nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #bar{#nu}_{e}");
    
    hcov->GetXaxis()->SetBinLabel(nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #nu_{#mu}");
    hcov->GetYaxis()->SetBinLabel(nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"ND280 RHC #nu_{#mu}");
    /////////////////
    hcov->GetXaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"SK FHC #nu_{#mu}");
    hcov->GetYaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+2*nBinsSameSignMu+1,"SK FHC #nu_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #nu_{e}");
    hcov->GetYaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+2*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #nu_{e}");
    
    hcov->GetXaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #nu_{e}");
    hcov->GetYaxis()->SetBinLabel(2*nBinsWrongSignMu+2*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #nu_{e}");
    
    hcov->GetXaxis()->SetBinLabel(2*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #bar{#nu}_{e}");
    hcov->GetYaxis()->SetBinLabel(2*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #bar{#nu}_{e}");
    /////////////////
    hcov->GetXaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #bar{#nu}_{#mu}");
    hcov->GetYaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+3*nBinsSameSignMu+1,"SK FHC #bar{#nu}_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #bar{#nu}_{#mu}");
    hcov->GetYaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+3*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #bar{#nu}_{#mu}");
    
    hcov->GetXaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+4*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #bar{#nu}_{e}");
    hcov->GetYaxis()->SetBinLabel(3*nBinsWrongSignMu+3*nBinsWrongSignE+4*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #bar{#nu}_{e}");
    
    hcov->GetXaxis()->SetBinLabel(3*nBinsWrongSignMu+4*nBinsWrongSignE+4*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #nu_{#mu}");
    hcov->GetYaxis()->SetBinLabel(3*nBinsWrongSignMu+4*nBinsWrongSignE+4*nBinsSameSignE+4*nBinsSameSignMu+1,"SK RHC #nu_{#mu}");
    
    
	c0->Print(Form("CorrelationMatrix_%s.pdf[", "pdf"));
    hcov->GetXaxis()->SetLabelSize(0.018);
    hcov->GetYaxis()->SetLabelSize(0.018);
    hcov->GetZaxis()->SetLabelSize(0.015);
    hcov->SetMarkerSize(0.4);
    hcov->GetZaxis()->SetTitle("Covariance");
    hcov->GetZaxis()->SetRangeUser(-0.008, 0.008);
    hcov->GetXaxis()->SetRangeUser(0., n_dete);
    hcov->GetYaxis()->SetRangeUser(0., n_dete);
    hcov->Draw("COLZ"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    /*
    cov_dete.GetXaxis().SetLabelSize(0.015);
    cov_dete.GetYaxis().SetLabelSize(0.015);
    cov_dete.GetZaxis().SetLabelSize(0.015);
    cov_dete->SetMarkerSize(0.3);
    cov_dete.GetZaxis().SetTitle("Covariance");
    cov_dete.Draw("COLZ"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    
    corr_dete.GetXaxis().SetLabelSize(0.015);
    corr_dete.GetYaxis().SetLabelSize(0.015);
    corr_dete.GetZaxis().SetLabelSize(0.015);
    corr_dete->GetZaxis()->SetRangeUser(-1., 1.0);
    corr_dete->SetMarkerSize(0.3);
    corr_dete.GetZaxis().SetTitle("Correaltion");
    corr_dete.Draw("COLZ"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    */
    
    
 c0->Print(Form("CorrelationMatrix_%s.pdf]", "pdf"));   
}
