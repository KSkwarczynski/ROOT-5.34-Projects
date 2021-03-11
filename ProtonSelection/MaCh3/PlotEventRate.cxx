void PlotEventRate(TString postfitfile) {

    TCanvas *c1 = new TCanvas("c1"," ", 0, 0, 800,630);
    SetT2Kstyl();
    gPad->SetGrid();
    gStyle->SetPalette(51);
    
    
    TFile *InputFile = TFile::Open(postfitfile);
        
    TH2Poly* CC0pi_0p_Data     = (TH2Poly*)(InputFile->Get("DATA_FGD1_numuCC_0pi_0_protons"));
    TH2Poly* CC0pi_0p_CCQE     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CCQE"));
    TH2Poly* CC0pi_0p_2p2h     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_2p2h"));
    TH2Poly* CC0pi_0p_CC1pi     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CC1pi"));
    TH2Poly* CC0pi_0p_CCcoh     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CCcoh"));
    TH2Poly* CC0pi_0p_CCMpi     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CCMpi"));     
    TH2Poly* CC0pi_0p_CCDIS     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CCDIS"));
    TH2Poly* CC0pi_0p_NC1pi0    = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_NC1pi0"));
    TH2Poly* CC0pi_0p_NC1pipm    = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_NC1pipm"));
    TH2Poly* CC0pi_0p_NCcoh     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_NCcoh"));
    TH2Poly* CC0pi_0p_NCoth     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_NCoth"));
    TH2Poly* CC0pi_0p_NC1gam     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_NC1gam"));
    TH2Poly* CC0pi_0p_CCMisc     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_CCMisc"));
    TH2Poly* CC0pi_0p_UNKNOWN_BAD     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_0_protons_UNKNOWN_BAD"));
        
    
    TH2Poly* CC0pi_Np_Data     = (TH2Poly*)(InputFile->Get("DATA_FGD1_numuCC_0pi_N_protons"));
    TH2Poly* CC0pi_Np_CCQE     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CCQE"));
    TH2Poly* CC0pi_Np_2p2h     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_2p2h"));
    TH2Poly* CC0pi_Np_CC1pi     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CC1pi"));
    TH2Poly* CC0pi_Np_CCcoh     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CCcoh"));
    TH2Poly* CC0pi_Np_CCMpi     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CCMpi"));     
    TH2Poly* CC0pi_Np_CCDIS     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CCDIS"));
    TH2Poly* CC0pi_Np_NC1pi0    = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_NC1pi0"));
    TH2Poly* CC0pi_Np_NC1pipm    = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_NC1pipm"));
    TH2Poly* CC0pi_Np_NCcoh     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_NCcoh"));
    TH2Poly* CC0pi_Np_NCoth     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_NCoth"));
    TH2Poly* CC0pi_Np_NC1gam     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_NC1gam"));
    TH2Poly* CC0pi_Np_CCMisc     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_CCMisc"));
    TH2Poly* CC0pi_Np_UNKNOWN_BAD     = (TH2Poly*)(InputFile->Get("MC_FGD1_numuCC_0pi_N_protons_UNKNOWN_BAD"));
        
    std::vector<double> CC0Pi0p_Mom;
    CC0Pi0p_Mom.push_back(0.);
    CC0Pi0p_Mom.push_back(200.);
    CC0Pi0p_Mom.push_back(300.);
    CC0Pi0p_Mom.push_back(400.);
    CC0Pi0p_Mom.push_back(500.);
    CC0Pi0p_Mom.push_back(600.);
    CC0Pi0p_Mom.push_back(700.);
    CC0Pi0p_Mom.push_back(800.);
    CC0Pi0p_Mom.push_back(900.);
    CC0Pi0p_Mom.push_back(1000.);
    CC0Pi0p_Mom.push_back(1100.);
    CC0Pi0p_Mom.push_back(1200.);
    CC0Pi0p_Mom.push_back(1300.);
    CC0Pi0p_Mom.push_back(1400.);
    CC0Pi0p_Mom.push_back(1500.);
    CC0Pi0p_Mom.push_back(1600.);
    CC0Pi0p_Mom.push_back(1800.);
    CC0Pi0p_Mom.push_back(2000.);
    CC0Pi0p_Mom.push_back(2500.);
    CC0Pi0p_Mom.push_back(3000.);
    CC0Pi0p_Mom.push_back(3500.);
    CC0Pi0p_Mom.push_back(5000.);
    CC0Pi0p_Mom.push_back(30000.);

    std::vector<double> CC0PiNp_Mom;
    CC0PiNp_Mom.push_back(0.);
    CC0PiNp_Mom.push_back(200.);
    CC0PiNp_Mom.push_back(300.);
    CC0PiNp_Mom.push_back(400.);
    CC0PiNp_Mom.push_back(500.);
    CC0PiNp_Mom.push_back(600.);
    CC0PiNp_Mom.push_back(700.);
    CC0PiNp_Mom.push_back(800.);
    CC0PiNp_Mom.push_back(900.);
    CC0PiNp_Mom.push_back(1000.);
    CC0PiNp_Mom.push_back(1100.);
    CC0PiNp_Mom.push_back(1200.);
    CC0PiNp_Mom.push_back(1300.);
    CC0PiNp_Mom.push_back(1400.);
    CC0PiNp_Mom.push_back(1500.);
    CC0PiNp_Mom.push_back(1600.);
    CC0PiNp_Mom.push_back(1800.);
    CC0PiNp_Mom.push_back(2000.);
    CC0PiNp_Mom.push_back(2500.);
    CC0PiNp_Mom.push_back(3000.);
    CC0PiNp_Mom.push_back(3500.);
    CC0PiNp_Mom.push_back(5000.);
    CC0PiNp_Mom.push_back(30000.); 
       

    TH1D* CC0pi_0p_Data_momentum = PolyProjectionX(CC0pi_0p_Data, "CC0pi 0p_Data_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CCQE_momentum = PolyProjectionX(CC0pi_0p_CCQE, "CC0pi_0p_CCQE_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_2p2h_momentum = PolyProjectionX(CC0pi_0p_2p2h, "CC0pi_0p_2p2h_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CC1pi_momentum = PolyProjectionX(CC0pi_0p_CC1pi, "CC0pi_0p_CC1pi_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CCcoh_momentum = PolyProjectionX(CC0pi_0p_CCcoh, "CC0pi_0p_CCcoh_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CCMpi_momentum = PolyProjectionX(CC0pi_0p_CCMpi, "CC0pi_0p_CCMpi_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CCDIS_momentum = PolyProjectionX(CC0pi_0p_CCDIS, "CC0pi_0p_CCDIS_momentum", CC0Pi0p_Mom); 
    TH1D* CC0pi_0p_NC1pi0_momentum = PolyProjectionX(CC0pi_0p_NC1pi0, "CC0pi_0p_NC1pi0_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_NC1pipm_momentum = PolyProjectionX(CC0pi_0p_NC1pipm, "CC0pi_0p_NC1pipm_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_NCcoh_momentum = PolyProjectionX(CC0pi_0p_NCcoh, "CC0pi_0p_NCcoh_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_NCoth_momentum = PolyProjectionX(CC0pi_0p_NCoth, "CC0pi_0p_NCoth_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_NC1gam_momentum = PolyProjectionX(CC0pi_0p_NC1gam, "CC0pi_0p_NC1gam_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_CCMisc_momentum = PolyProjectionX(CC0pi_0p_CCMisc, "CC0pi_0p_CCMisc_momentum", CC0Pi0p_Mom);
    TH1D* CC0pi_0p_UNKNOWN_BAD_momentum = PolyProjectionX(CC0pi_0p_UNKNOWN_BAD, "CC0pi_0p_UNKNOWN_BAD_momentum", CC0Pi0p_Mom);

    
    TH1D* CC0pi_Np_Data_momentum = PolyProjectionX(CC0pi_Np_Data, "CC0pi_Np_Data_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CCQE_momentum = PolyProjectionX(CC0pi_Np_CCQE, "CC0pi_Np_CCQE_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_2p2h_momentum = PolyProjectionX(CC0pi_Np_2p2h, "CC0pi_Np_2p2h_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CC1pi_momentum = PolyProjectionX(CC0pi_Np_CC1pi, "CC0pi_Np_CC1pi_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CCcoh_momentum = PolyProjectionX(CC0pi_Np_CCcoh, "CC0pi_Np_CCcoh_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CCMpi_momentum = PolyProjectionX(CC0pi_Np_CCMpi, "CC0pi_Np_CCMpi_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CCDIS_momentum = PolyProjectionX(CC0pi_Np_CCDIS, "CC0pi_Np_CCDIS_momentum", CC0PiNp_Mom); 
    TH1D* CC0pi_Np_NC1pi0_momentum = PolyProjectionX(CC0pi_Np_NC1pi0, "CC0pi_Np_NC1pi0_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_NC1pipm_momentum = PolyProjectionX(CC0pi_Np_NC1pipm, "CC0pi_Np_NC1pipm_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_NCcoh_momentum = PolyProjectionX(CC0pi_Np_NCcoh, "CC0pi_Np_NCcoh_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_NCoth_momentum = PolyProjectionX(CC0pi_Np_NCoth, "CC0pi_Np_NCoth_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_NC1gam_momentum = PolyProjectionX(CC0pi_Np_NC1gam, "CC0pi_Np_NC1gam_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_CCMisc_momentum = PolyProjectionX(CC0pi_Np_CCMisc, "CC0pi_Np_CCMisc_momentum", CC0PiNp_Mom);
    TH1D* CC0pi_Np_UNKNOWN_BAD_momentum = PolyProjectionX(CC0pi_Np_UNKNOWN_BAD, "CC0pi_Np_UNKNOWN_BAD_momentum", CC0PiNp_Mom);
    
    
    THStack *CC0pi_0p_Stack = new THStack( "CC0pi_0p_Stack", "CC0pi_0p_Stack" );
    
    CC0pi_0p_CCQE_momentum->SetFillColor(kRed);
    CC0pi_0p_CCQE_momentum->SetFillStyle(3001);
    CC0pi_0p_CCQE_momentum->SetLineColor(kRed);

    CC0pi_0p_2p2h_momentum->SetFillColor(kMagenta);
    CC0pi_0p_2p2h_momentum->SetFillStyle(3001);
    CC0pi_0p_2p2h_momentum->SetLineColor(kMagenta);
    
    CC0pi_0p_CC1pi_momentum->SetFillColor(kGreen);
    CC0pi_0p_CC1pi_momentum->SetFillStyle(3001);
    CC0pi_0p_CC1pi_momentum->SetLineColor(kGreen);
    
    CC0pi_0p_CCcoh_momentum->SetFillColor(kCyan);
    CC0pi_0p_CCcoh_momentum->SetFillStyle(3001);
    CC0pi_0p_CCcoh_momentum->SetLineColor(kCyan);
    
    CC0pi_0p_CCMpi_momentum->SetFillColor(kTeal);
    CC0pi_0p_CCMpi_momentum->SetFillStyle(3001);
    CC0pi_0p_CCMpi_momentum->SetLineColor(kTeal);
    
    CC0pi_0p_CCDIS_momentum->SetFillColor(kBlue);
    CC0pi_0p_CCDIS_momentum->SetFillStyle(3001);
    CC0pi_0p_CCDIS_momentum->SetLineColor(kBlue);
    
    CC0pi_0p_NC1pi0_momentum->SetFillColor(kPink );
    CC0pi_0p_NC1pi0_momentum->SetFillStyle(3001);
    CC0pi_0p_NC1pi0_momentum->SetLineColor(kPink );
    
    CC0pi_0p_NC1pipm_momentum->SetFillColor(kOrange );
    CC0pi_0p_NC1pipm_momentum->SetFillStyle(3001);
    CC0pi_0p_NC1pipm_momentum->SetLineColor(kOrange );
     
    CC0pi_0p_NCcoh_momentum->SetFillColor(kViolet );
    CC0pi_0p_NCcoh_momentum->SetFillStyle(3001);
    CC0pi_0p_NCcoh_momentum->SetLineColor(kViolet );
    
    CC0pi_0p_NCoth_momentum->SetFillColor(kGray );
    CC0pi_0p_NCoth_momentum->SetFillStyle(3001);
    CC0pi_0p_NCoth_momentum->SetLineColor(kGray );
    
    CC0pi_0p_NC1gam_momentum->SetFillColor(kSpring  );
    CC0pi_0p_NC1gam_momentum->SetFillStyle(3001);
    CC0pi_0p_NC1gam_momentum->SetLineColor(kSpring  );
    
    CC0pi_0p_CCMisc_momentum->SetFillColor(kYellow  );
    CC0pi_0p_CCMisc_momentum->SetFillStyle(3001);
    CC0pi_0p_CCMisc_momentum->SetLineColor(kYellow  );
    
    CC0pi_0p_UNKNOWN_BAD_momentum->SetFillColor(kBlack   );
    CC0pi_0p_UNKNOWN_BAD_momentum->SetFillStyle(3001);
    CC0pi_0p_UNKNOWN_BAD_momentum->SetLineColor(kBlack   );
    
    CC0pi_0p_Stack->Add( CC0pi_0p_UNKNOWN_BAD_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CCMisc_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_NC1gam_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_NCoth_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_NCcoh_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_NC1pipm_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_NC1pi0_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CCDIS_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CCMpi_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CCcoh_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CC1pi_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_2p2h_momentum );
    CC0pi_0p_Stack->Add( CC0pi_0p_CCQE_momentum );
    
    THStack *CC0pi_Np_Stack = new THStack( "CC0pi_Np_Stack", "CC0pi_Np_Stack" );
    
    CC0pi_Np_CCQE_momentum->SetFillColor(kRed);
    CC0pi_Np_CCQE_momentum->SetFillStyle(3001);
    CC0pi_Np_CCQE_momentum->SetLineColor(kRed);

    CC0pi_Np_2p2h_momentum->SetFillColor(kMagenta);
    CC0pi_Np_2p2h_momentum->SetFillStyle(3001);
    CC0pi_Np_2p2h_momentum->SetLineColor(kMagenta);
    
    CC0pi_Np_CC1pi_momentum->SetFillColor(kGreen);
    CC0pi_Np_CC1pi_momentum->SetFillStyle(3001);
    CC0pi_Np_CC1pi_momentum->SetLineColor(kGreen);
    
    CC0pi_Np_CCcoh_momentum->SetFillColor(kCyan);
    CC0pi_Np_CCcoh_momentum->SetFillStyle(3001);
    CC0pi_Np_CCcoh_momentum->SetLineColor(kCyan);
    
    CC0pi_Np_CCMpi_momentum->SetFillColor(kTeal);
    CC0pi_Np_CCMpi_momentum->SetFillStyle(3001);
    CC0pi_Np_CCMpi_momentum->SetLineColor(kTeal);
    
    CC0pi_Np_CCDIS_momentum->SetFillColor(kBlue);
    CC0pi_Np_CCDIS_momentum->SetFillStyle(3001);
    CC0pi_Np_CCDIS_momentum->SetLineColor(kBlue);
    
    CC0pi_Np_NC1pi0_momentum->SetFillColor(kPink );
    CC0pi_Np_NC1pi0_momentum->SetFillStyle(3001);
    CC0pi_Np_NC1pi0_momentum->SetLineColor(kPink );
    
    CC0pi_Np_NC1pipm_momentum->SetFillColor(kOrange );
    CC0pi_Np_NC1pipm_momentum->SetFillStyle(3001);
    CC0pi_Np_NC1pipm_momentum->SetLineColor(kOrange );
     
    CC0pi_Np_NCcoh_momentum->SetFillColor(kViolet );
    CC0pi_Np_NCcoh_momentum->SetFillStyle(3001);
    CC0pi_Np_NCcoh_momentum->SetLineColor(kViolet );
    
    CC0pi_Np_NCoth_momentum->SetFillColor(kGray );
    CC0pi_Np_NCoth_momentum->SetFillStyle(3001);
    CC0pi_Np_NCoth_momentum->SetLineColor(kGray );
    
    CC0pi_Np_NC1gam_momentum->SetFillColor(kSpring  );
    CC0pi_Np_NC1gam_momentum->SetFillStyle(3001);
    CC0pi_Np_NC1gam_momentum->SetLineColor(kSpring  );
    
    CC0pi_Np_CCMisc_momentum->SetFillColor(kYellow  );
    CC0pi_Np_CCMisc_momentum->SetFillStyle(3001);
    CC0pi_Np_CCMisc_momentum->SetLineColor(kYellow  );
    
    CC0pi_Np_UNKNOWN_BAD_momentum->SetFillColor(kBlack   );
    CC0pi_Np_UNKNOWN_BAD_momentum->SetFillStyle(3001);
    CC0pi_Np_UNKNOWN_BAD_momentum->SetLineColor(kBlack   );
    
    CC0pi_Np_Stack->Add( CC0pi_Np_UNKNOWN_BAD_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CCMisc_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_NC1gam_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_NCoth_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_NCcoh_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_NC1pipm_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_NC1pi0_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CCDIS_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CCMpi_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CCcoh_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CC1pi_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_2p2h_momentum );
    CC0pi_Np_Stack->Add( CC0pi_Np_CCQE_momentum );
    
    //WARNING
    CC0pi_0p_Data_momentum->GetXaxis()->SetRangeUser(0, 2000.); 
    CC0pi_Np_Data_momentum->GetXaxis()->SetRangeUser(0, 2000.);
    
    CC0pi_0p_Data_momentum->SetTitle("CC0Pi 0p FGD1");
    CC0pi_Np_Data_momentum->SetTitle("CC0Pi Np FGD1");
    
    c1->Print("EventRate.pdf[", "pdf");
    
    CC0pi_0p_Data_momentum->Draw("pe");
    CC0pi_0p_Stack->Draw("SAME");
    
    TLegend *legend = new TLegend(0.75,0.45,0.9,0.9);
    legend->AddEntry(CC0pi_0p_Data_momentum, "Data","pe");
    legend->AddEntry(CC0pi_0p_CCQE_momentum, "CCQE","l");
    legend->AddEntry(CC0pi_0p_2p2h_momentum, "2p2h","l");
    legend->AddEntry(CC0pi_0p_CC1pi_momentum, "CC1pi","l"); 
    legend->AddEntry(CC0pi_0p_CCcoh_momentum, "CCcoh","l"); 
    legend->AddEntry(CC0pi_0p_CCMpi_momentum, "CCMpi","l"); 
    legend->AddEntry(CC0pi_0p_CCDIS_momentum, "CCDIS","l"); 
    legend->AddEntry(CC0pi_0p_NC1pi0_momentum, "NC1pi0","l"); 
    legend->AddEntry(CC0pi_0p_NC1pipm_momentum, "NC1pipm","l"); 
    legend->AddEntry(CC0pi_0p_NCcoh_momentum, "NCcoh","l"); 
    legend->AddEntry(CC0pi_0p_NCoth_momentum, "NCoth","l");   
    legend->AddEntry(CC0pi_0p_NC1gam_momentum, "NC1gam","l");   
    legend->AddEntry(CC0pi_0p_CCMisc_momentum, "CCMisc","l"); 
    legend->AddEntry(CC0pi_0p_UNKNOWN_BAD_momentum, "Unknown","l");  
    legend->SetTextSize(0.04);
    legend->Draw();
    
    c1->Print("EventRate.pdf", "pdf");
    
    CC0pi_Np_Data_momentum->Draw("pe");
    CC0pi_Np_Stack->Draw("SAME");
    
    TLegend *legend = new TLegend(0.75,0.45,0.9,0.9);
    legend->AddEntry(CC0pi_Np_Data_momentum, "Data","pe");
    legend->AddEntry(CC0pi_Np_CCQE_momentum, "CCQE","l");
    legend->AddEntry(CC0pi_Np_2p2h_momentum, "2p2h","l");
    legend->AddEntry(CC0pi_Np_CC1pi_momentum, "CC1pi","l"); 
    legend->AddEntry(CC0pi_Np_CCcoh_momentum, "CCcoh","l"); 
    legend->AddEntry(CC0pi_Np_CCMpi_momentum, "CCMpi","l"); 
    legend->AddEntry(CC0pi_Np_CCDIS_momentum, "CCDIS","l"); 
    legend->AddEntry(CC0pi_Np_NC1pi0_momentum, "NC1pi0","l"); 
    legend->AddEntry(CC0pi_Np_NC1pipm_momentum, "NC1pipm","l"); 
    legend->AddEntry(CC0pi_Np_NCcoh_momentum, "NCcoh","l"); 
    legend->AddEntry(CC0pi_Np_NCoth_momentum, "NCoth","l");   
    legend->AddEntry(CC0pi_Np_NC1gam_momentum, "NC1gam","l");   
    legend->AddEntry(CC0pi_Np_CCMisc_momentum, "CCMisc","l"); 
    legend->AddEntry(CC0pi_Np_UNKNOWN_BAD_momentum, "Unknown","l");
    legend->SetTextSize(0.04);
    legend->Draw();
    
    
    c1->Print("EventRate.pdf", "pdf");
    
    
    c1->Print("EventRate.pdf]", "pdf");
}

TH1D* PolyProjectionX(TObject* poly, std::string TempName, std::vector<double> xbins) {
  // **************************************************

  TH1D* hProjX = new TH1D((TempName+"_x").c_str(),(TempName+"_x").c_str(),xbins.size()-1,&xbins[0]);
  double xlow, xup, frac=0;

  //loop over bins in the poly
  for(int i=0; i<((TH2Poly*)poly)->GetNumberOfBins(); i++)
    {
      //get bin and its edges
      TH2PolyBin* bin = (TH2PolyBin*)((TH2Poly*)poly)->GetBins()->At(i)->Clone();
      xlow=bin->GetXMin();
      xup=bin->GetXMax();

      //Loop over projected bins, find fraction of poly bin in each
      for(int dx=0; dx<int(xbins.size()); dx++)
        {
          if(xbins[dx+1]<=xlow || xbins[dx]>=xup)
            {
              frac=0;
            }
          else if(xbins[dx]<=xlow && xbins[dx+1]>=xup)
            {
              frac=1;
            }
          else if(xbins[dx]<=xlow && xbins[dx+1]<=xup)
            {
              frac=(xbins[dx+1]-xlow)/(xup-xlow);
            }
          else if(xbins[dx]>=xlow && xbins[dx+1]>=xup)
            {
              frac=(xup-xbins[dx])/(xup-xlow);
            }
          else if(xbins[dx]>=xlow && xbins[dx+1]<=xup)
            {
              frac=(xbins[dx+1]-xbins[dx])/(xup-xlow);
            }
          else
            {
              frac=0;
            }
          hProjX->SetBinContent(dx+1,hProjX->GetBinContent(dx+1)+frac*bin->GetContent());
        }
    }
    return hProjX;
} // end project poly X function

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
    
