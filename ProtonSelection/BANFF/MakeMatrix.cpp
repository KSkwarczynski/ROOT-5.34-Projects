void MakeMatrix(TString fname) {

    TFile *f1 = TFile::Open(fname);


    TH2D *CovarainceMatrix; 
    TH2D *CorrelationMatrix; 
    TH1D* mc_sys_error;
    
    CovarainceMatrix = (TH2D*) f1->Get( "Total_Covariance_Matrix"  );
    CorrelationMatrix = (TH2D*) f1->Get( "Total_Correlation_Matrix" );

    cov_var = (TH2D*) f1->Get( "Covariance_Matrix_NoMCStats" );
    corr_var = (TH2D*) f1->Get( "Correlation_Matrix_NoMCStats" );
        
    mc_sys_error = (TH1D*) f1->Get( "MC_Sys_Error" );
        
        
    gStyle->SetOptFit(111);

    // Open a TCanvas to write the posterior onto
    TCanvas* c0 = new TCanvas("c0", "c0", 0, 0, 1600,1200);
    c0->SetGrid();
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    c0->SetTickx();
    c0->SetTicky();
    c0->SetBottomMargin(0.1);
    c0->SetTopMargin(0.02);
    c0->SetRightMargin(0.15);
    c0->SetLeftMargin(0.10);
        
        
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
    
    CovarainceMatrix->GetXaxis()->SetLabelSize(0.015);
    CovarainceMatrix->GetYaxis()->SetLabelSize(0.015);
    CovarainceMatrix->SetMinimum(-0.015);
    CovarainceMatrix->SetMaximum(0.015);
    CovarainceMatrix->GetZaxis()->SetTitle("Covariance");
    
    cov_var->GetXaxis()->SetLabelSize(0.015);
    cov_var->GetYaxis()->SetLabelSize(0.015);
    cov_var->SetMinimum(-0.015);
    cov_var->SetMaximum(0.015);
    cov_var->GetZaxis()->SetTitle("Covariance");

        
    CorrelationMatrix->GetXaxis()->SetLabelSize(0.015);
    CorrelationMatrix->GetYaxis()->SetLabelSize(0.015);
    CorrelationMatrix->SetMinimum(-1);
    CorrelationMatrix->SetMaximum(1);
    CorrelationMatrix->GetZaxis()->SetTitle("Correaltion");
        
    corr_var->GetYaxis()->SetLabelSize(0.015);
    corr_var->GetXaxis()->SetLabelSize(0.015);
    corr_var->SetMinimum(-1);
    corr_var->SetMaximum(1);
    corr_var->GetZaxis()->SetTitle("Correaltion");
    

    
    c0->Print(Form("%s.pdf[",fname.Data()), "pdf");
        
    CovarainceMatrix->Draw("COLZ");
    c0->Print(Form("%s.pdf",fname.Data()), "pdf");
    c0->Print("CovarainceMatrix.png");
           
    corr_var->Draw("COLZ");
    c0->Print(Form("%s.pdf",fname.Data()), "pdf");
    c0->Print("corr_var.png");
    
    CorrelationMatrix->Draw("COLZ");
    c0->Print(Form("%s.pdf",fname.Data()), "pdf");
    c0->Print("CorrelationMatrix.png");

    cov_var->Draw("COLZ");
    c0->Print(Form("%s.pdf",fname.Data()), "pdf");
    c0->Print("cov_var.png");
    
    
    mc_sys_error->Draw("");
    c0->Print(Form("%s.pdf",fname.Data()), "pdf");
    c0->Print("mc_sys_error.png");
    c0->Print(Form("%s.pdf]",fname.Data()), "pdf");
}
