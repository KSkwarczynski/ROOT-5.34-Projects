void MakeLookUp(TString fname) {

    TFile *f1 = TFile::Open(fname);


    TH1D *hFSImodeCCQEfull; 
    TH1D *hFSImode2p2hfull; 
    TH1D *hFSImodeRESfull; 
    TH1D *hFSImodeOtherfull;
    
    hFSImodeCCQEfull = (TH1D*) f1->Get( "hFSImodeCCQEfull" );
    hFSImode2p2hfull = (TH1D*) f1->Get( "hFSImode2p2hfull" );
    hFSImodeRESfull = (TH1D*) f1->Get( "hFSImodeRESfull" );
    hFSImodeOtherfull = (TH1D*) f1->Get( "hFSImodeOtherfull" );

    TFile *Output = new TFile("nucleonFataFSI_LookUpTable.root","RECREATE");
    
    
    hFSImodeCCQEfull->Write();
    hFSImode2p2hfull->Write();
    hFSImodeRESfull->Write();
    hFSImodeOtherfull->Write();
    
    Output->Close();
    
}
