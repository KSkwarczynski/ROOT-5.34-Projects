void MakeMatrix(TString fname) {

    TFile *f1 = TFile::Open(fname);


    TH2D *CovarainceMatrix; 
    TH2D *CorrelationMatrix; 

    CovarainceMatrix = (TH2D*) f1->Get( "Total_Correlation_Matrix" );
    CorrelationMatrix = (TH2D*) f1->Get( "Total_Covariance_Matrix" );

    
    gStyle->SetOptFit(111);

    // Open a TCanvas to write the posterior onto
    TCanvas* c0 = new TCanvas("c0", "c0", 0, 0, 1024, 1024);
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
    CorrelationMatrix->GetXaxis()->SetLabelSize(0.015);
    CorrelationMatrix->GetYaxis()->SetLabelSize(0.015);
    CorrelationMatrix->SetMinimum(-1);
    CorrelationMatrix->SetMaximum(1);
    
    CovarainceMatrix->Draw("COLZ");
    c0->Print(Form("%s.pdf(",fname.Data()), "pdf");
    c0->Print("CovarainceMatrix.png");
            
    CorrelationMatrix->Draw("COLZ");
    c0->Print(Form("%s.pdf)",fname.Data()), "pdf");
    c0->Print("CorrelationMatrix.png");
}
