void PlotXsecNominal(TString postfitfile) {

      gStyle->SetOptFit(111);

    // Open a TCanvas to write the posterior onto
    TCanvas* c0 = new TCanvas("c0", "c0", 0, 0, 1024, 1024);
    c0->SetGrid();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    gStyle->SetPaintTextFormat("4.1f"); //Precision of value in matrix element

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
    
    int n_dete  = 47; //WARNING
    TH2D cov_dete("Covariance_Matrix", "Covariance Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    TH2D corr_dete("Correlation_Matrix", "Correlation Matrix",n_dete , 0, n_dete , n_dete , 0, n_dete );
    
        // Detector correlation matrix
	for(int i = 0; i < n_dete; i++){
		for(int j = 0; j < n_dete; j++){
            hcov->SetBinContent(hcov->GetBin(i+1,j+1), 0);
            hcov->SetBinContent(hcov->GetBin(i+1,j+1), (*xsec_cov)(i,j));
            
            cov_dete.SetBinContent(cov_dete.GetBin(i+1,j+1), (*xsec_cov)(i,j));
            correlation = (*xsec_cov)(i,j) / sqrt((*xsec_cov)(i,i) * (*xsec_cov)(j,j));
			if (fabs(correlation) > 0.01) { corr_dete.SetBinContent(corr_dete.GetBin(i+1,j+1), correlation); }
		}
	}
	c0->Print(Form("CorrelationMatrix_%s.pdf[", "pdf"));
    hcov->GetXaxis()->SetLabelSize(0.015);
    hcov->GetYaxis()->SetLabelSize(0.015);
    hcov->GetZaxis()->SetLabelSize(0.015);
    hcov->SetMarkerSize(0.3);
    hcov->GetZaxis()->SetTitle("Covariance");
    hcov->GetZaxis()->SetRangeUser(-0.10, 0.10);
    hcov->GetXaxis()->SetRangeUser(0., n_dete);
    hcov->GetYaxis()->SetRangeUser(0., n_dete);
    hcov->Draw("COLZ TEXT"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    
    cov_dete.GetXaxis().SetLabelSize(0.015);
    cov_dete.GetYaxis().SetLabelSize(0.015);
    cov_dete.GetZaxis().SetLabelSize(0.015);
    cov_dete->SetMarkerSize(0.3);
    cov_dete.GetZaxis().SetTitle("Covariance");
    cov_dete.Draw("COLZ TEXT"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    
    corr_dete.GetXaxis().SetLabelSize(0.015);
    corr_dete.GetYaxis().SetLabelSize(0.015);
    corr_dete.GetZaxis().SetLabelSize(0.015);
    corr_dete->SetMarkerSize(0.3);
    corr_dete.GetZaxis().SetTitle("Correaltion");
    corr_dete.Draw("COLZ TEXT"); //Plot matrix element content
    c0->Print(Form("CorrelationMatrix_%s.pdf", "pdf"));
    
    
    
 c0->Print(Form("CorrelationMatrix_%s.pdf]", "pdf"));   
}

