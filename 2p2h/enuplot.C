void enuplot(){

    //gROOT->SetStyle("T2K");
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
    gStyle->SetPalette(1,0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

// MC NEUT
    char filename[200];
    sprintf(filename,"/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/histograms.root");
    TFile *file = new TFile(filename,"READ");
    file->IsOpen();
////////////PROTON MOMENTUM//////
    TH1F*   h_CCQE_proton = (TH1F*) file->Get("h_CCQE_proton");
    h_CCQE_proton->SetFillColor(kRed);
    h_CCQE_proton->SetMarkerStyle(21);
    h_CCQE_proton->SetMarkerColor(kRed);
    TH1F*   h_2p2h_proton = (TH1F*) file->Get("h_2p2h_proton");
    h_2p2h_proton->SetFillColor(kBlue);
    h_2p2h_proton->SetMarkerStyle(21);
    h_2p2h_proton->SetMarkerColor(kBlue);
    TH1F*   h_RES_proton = (TH1F*) file->Get("h_RES_proton");
    h_RES_proton->SetFillColor(kGreen);
    h_RES_proton->SetMarkerStyle(21);
    h_RES_proton->SetMarkerColor(kGreen);
    TH1F*   h_DIS_proton = (TH1F*) file->Get("h_DIS_proton");
    h_DIS_proton->SetFillColor(kYellow);
    h_DIS_proton->SetMarkerStyle(21);
    h_DIS_proton->SetMarkerColor(kYellow);

    THStack *stackHisto = new THStack("stackHisto","Final proton momentum distribution");
    stackHisto->Add(h_DIS_proton);
    stackHisto->Add(h_2p2h_proton);
    stackHisto->Add(h_RES_proton);
    stackHisto->Add(h_CCQE_proton);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    stackHisto->Draw("");
    stackHisto->GetXaxis()->SetTitle("Momentum [MeV/c]");
    stackHisto->GetYaxis()->SetTitle("Number of events");
    stackHisto->GetYaxis()->SetTitleOffset(1.4);
    gPad->Modified();

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_RES_proton,"RES","f");
    legend->AddEntry(h_2p2h_proton,"2p2h","f");
    legend->AddEntry(h_CCQE_proton,"CCQE","f");
    legend->AddEntry(h_DIS_proton,"DIS","f");
    legend->Draw();

    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMomentumStack.pdf");

    delete c1;
    delete legend;
    delete stackHisto;
//////////PROTON MAX MOMENTUM////
    TH1F*   h_CCQE_proton_max = (TH1F*) file->Get("h_CCQE_proton_max");
    TH1F *h_CCQE_proton_max_2 = (TH1F*)(h_CCQE_proton_max->Clone("h_CCQE_proton_max_2"));
    h_CCQE_proton_max->SetFillColor(kRed);
    h_CCQE_proton_max->SetMarkerStyle(21);
    h_CCQE_proton_max->SetMarkerColor(kRed);

TH1F*   h_2p2h_proton_max = (TH1F*) file->Get("h_2p2h_proton_max");
    TH1F *h_2p2h_proton_max_2 = (TH1F*)(h_2p2h_proton_max->Clone("h_2p2h_proton_max_2"));
    h_2p2h_proton_max->SetFillColor(kBlue);
    h_2p2h_proton_max->SetMarkerStyle(21);
    h_2p2h_proton_max->SetMarkerColor(kBlue);

    TH1F*   h_RES_proton_max = (TH1F*) file->Get("h_RES_proton_max");
    TH1F *h_RES_proton_max_2 = (TH1F*)(h_RES_proton_max->Clone("h_RES_proton_max_2"));
    h_RES_proton_max->SetFillColor(kGreen);
    h_RES_proton_max->SetMarkerStyle(21);
    h_RES_proton_max->SetMarkerColor(kGreen);

    TH1F*   h_DIS_proton_max = (TH1F*) file->Get("h_DIS_proton_max");
    TH1F *h_DIS_proton_max_2 = (TH1F*)(h_DIS_proton_max->Clone("h_DIS_proton_max_2"));
    h_DIS_proton_max->SetFillColor(kYellow);
    h_DIS_proton_max->SetMarkerStyle(21);
    h_DIS_proton_max->SetMarkerColor(kYellow);

    THStack *stackHisto = new THStack("stackHisto","Final proton max momentum distribution");
    stackHisto->Add(h_DIS_proton_max);
    stackHisto->Add(h_CCQE_proton_max);
    stackHisto->Add(h_2p2h_proton_max);
    stackHisto->Add(h_RES_proton_max);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    stackHisto->Draw("");
    stackHisto->GetXaxis()->SetTitle("Momentum [MeV/c]");
    stackHisto->GetYaxis()->SetTitle("Number of events");
    stackHisto->GetYaxis()->SetTitleOffset(1.4);
    gPad->Modified();

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_RES_proton_max,"RES","f");
    legend->AddEntry(h_2p2h_proton_max,"2p2h","f");
    legend->AddEntry(h_CCQE_proton_max,"CCQE","f");
    legend->AddEntry(h_DIS_proton_max,"DIS","f");
    legend->Draw();

    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMaxMomentumStack.pdf");
    delete c1;
    delete legend;
    delete stackHisto;
    /////////Not stacked//////

    h_CCQE_proton_max_2->SetLineColorAlpha(kRed, 1);
    h_CCQE_proton_max_2->SetLineWidth(1.5);

    h_2p2h_proton_max_2->SetLineColorAlpha(kBlue, 1);
    h_2p2h_proton_max_2->SetLineWidth(1.5);

    h_RES_proton_max_2->SetLineColorAlpha(kGreen, 1 );
    h_RES_proton_max_2->SetLineWidth(1.5);

    h_DIS_proton_max_2->SetLineColorAlpha(kOrange, 1);
    h_DIS_proton_max_2->SetLineWidth(1.5);

    h_CCQE_proton_max_2->SetNameTitle("h_CCQE_proton_max_2","Anti numu max proton momentum distribution");
    h_CCQE_proton_max_2->GetXaxis()->SetTitle("Momentum [MeV/c]");
    h_CCQE_proton_max_2->GetYaxis()->SetTitle("Number of events");
    h_CCQE_proton_max_2->GetYaxis()->SetTitleOffset(1.4);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    gPad->Modified();
    h_CCQE_proton_max_2->Draw("HIST");
    h_RES_proton_max_2->Draw("HIST SAME");
    h_DIS_proton_max_2->Draw("HIST SAME");;
    h_2p2h_proton_max_2->Draw("HIST SAME");

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_RES_proton_max_2,"RES","l");
    legend->AddEntry(h_2p2h_proton_max_2,"2p2h","l");
    legend->AddEntry(h_CCQE_proton_max_2,"CCQE","l");
    legend->AddEntry(h_DIS_proton_max_2,"DIS","l");
    legend->Draw();



    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMaxMomentum.pdf");
    delete c1;
    delete legend;

/////////////////NEUTRINO MOMENTUM////
    TH1F*   h_CCQE = (TH1F*) file->Get("h_CCQE");
    h_CCQE->SetLineColorAlpha(kRed, 1);
    h_CCQE->SetLineWidth(1.5);

    TH1F*   h_2p2h = (TH1F*) file->Get("h_2p2h");
    h_2p2h->SetLineColorAlpha(kBlue, 1);
    h_2p2h->SetLineWidth(1.5);

    TH1F*   h_res = (TH1F*) file->Get("h_res");
    h_res->SetLineColorAlpha(kGreen, 1 );
    h_res->SetLineWidth(1.5);

    TH1F*   h_DIS = (TH1F*) file->Get("h_DIS");
    h_DIS->SetLineColorAlpha(kOrange, 1);
    h_DIS->SetLineWidth(1.5);

    TH1F*   h_Coh = (TH1F*) file->Get("h_Coh");
    h_Coh->SetLineColorAlpha(kViolet, 1);
    h_Coh->SetLineWidth(1.5);

    h_CCQE->SetNameTitle("h_CCQE","Anti numu momentum distribution");
    h_CCQE->GetXaxis()->SetTitle("Momentum [MeV/c]");
    h_CCQE->GetYaxis()->SetTitle("Number of events");
    h_CCQE->GetYaxis()->SetTitleOffset(1.4);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    c1->SetLogy();
    h_CCQE->Draw("");
    h_2p2h->Draw("SAME");
    h_res->Draw("SAME");
    h_DIS->Draw("SAME");
    h_Coh->Draw("SAME");


    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_CCQE,"CCQE","l");
    legend->AddEntry(h_res,"RES","l");
    legend->AddEntry(h_2p2h,"2p2h","l");
    legend->AddEntry(h_Coh,"COH","l");
    legend->AddEntry(h_DIS,"DIS","l");
    legend->Draw();

    gPad->Modified();

    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/AntyNeutrinoMomentum.pdf");
    delete c1;
    delete legend;

///////////////Neutrino flavour//////
    TH1F*   h_anti_numu = (TH1F*) file->Get("h_anti_numu");
    h_anti_numu->SetLineColorAlpha(kBlue, 1);
    h_anti_numu->SetLineWidth(1.5);

    TH1F*   h_numu = (TH1F*) file->Get("h_numu");
    h_numu->SetLineColorAlpha(kRed, 1);
    h_numu->SetLineWidth(1.5);


    TH1F*   h_nue = (TH1F*) file->Get("h_nue");
    h_nue->SetLineColorAlpha(kOrange, 1);
    h_nue->SetLineWidth(1.5);

    TH1F*   h_anti_nue = (TH1F*) file->Get("h_anti_nue");
    h_anti_nue->SetLineColorAlpha(kViolet, 1);
    h_anti_nue->SetLineWidth(1.5);

    h_anti_numu->SetNameTitle("h_numu","Neutrino momentum distribution for anti numu beam");
    h_anti_numu->GetXaxis()->SetTitle("Momentum [MeV/c]");
    h_anti_numu->GetYaxis()->SetTitle("Number of events");
    h_anti_numu->GetYaxis()->SetTitleOffset(1.4);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    c1->SetLogy();
    h_anti_numu->Draw("");
    h_numu->Draw("SAME");
    h_nue->Draw("SAME");
    h_anti_nue->Draw("SAME");

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_anti_numu,"anti numu","l");
    legend->AddEntry(h_numu,"numu","l");
    legend->AddEntry(h_nue,"nue","l");
    legend->AddEntry(h_anti_nue,"anti nue","l");
    legend->Draw();

    gPad->Modified();
    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/FlavourNeutrinoMomentum.pdf");

    delete c1;
    delete legend;
///////////CCQE and 2p2h without protons in primary 
    delete h_CCQE_proton;
    TH1F*   h_CCQE_proton = (TH1F*) file->Get("h_CCQE_proton");
    h_CCQE_proton->SetLineColorAlpha(kRed, 1);
    h_CCQE_proton->SetLineWidth(1.5);

    TH1F*   h_2p2h_ifzero_proton_momentum = (TH1F*) file->Get("h_2p2h_ifzero_proton_momentum");
    h_2p2h_ifzero_proton_momentum->SetLineColorAlpha(kBlue, 1);
    h_2p2h_ifzero_proton_momentum->SetLineWidth(1.5);
    
    TH1F*   h_RES_ifzero_proton_momentum = (TH1F*) file->Get("h_RES_ifzero_proton_momentum");
    h_RES_ifzero_proton_momentum->SetLineColorAlpha(kGreen, 1);
    h_RES_ifzero_proton_momentum->SetLineWidth(1.5);
    
    h_CCQE_proton->SetNameTitle("h_CCQE_proton","Proton momentum");
    h_CCQE_proton->GetXaxis()->SetTitle("Momentum [MeV/c]");
    h_CCQE_proton->GetYaxis()->SetTitle("Number of events");
    
    long double normalizacja[3];
    for(int i=0;i<3;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=h_CCQE_proton->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=h_CCQE_proton->GetBinContent(i);
        normalizacja[1]+=h_2p2h_ifzero_proton_momentum->GetBinContent(i);
        normalizacja[2]+=h_RES_ifzero_proton_momentum->GetBinContent(i);
    }
    int norma=normalizacja[0];
    h_CCQE_proton->Scale(norma/normalizacja[0]);
    h_2p2h_ifzero_proton_momentum->Scale(norma/normalizacja[1]);
    h_RES_ifzero_proton_momentum->Scale(norma/normalizacja[2]);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    c1->SetLogy();
    h_CCQE_proton->Draw("");
    h_2p2h_ifzero_proton_momentum->Draw("SAME");
    //h_RES_ifzero_proton_momentum->Draw("SAME");
    
    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_CCQE_proton,"CCQE","l");
    legend->AddEntry(h_2p2h_ifzero_proton_momentum,"2p2h protons only from FSI","l");
    //legend->AddEntry(h_RES_ifzero_proton_momentum,"RES protons only from FSI","l");
    legend->Draw();

    gPad->Modified();
    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/FSIprotonComparison.pdf");

    delete c1;
    delete legend;
    delete h_2p2h_ifzero_proton_momentum;
    
/////////Protons after cut comparison///
    TH1F*   h_CCQE_proton_picut = (TH1F*) file->Get("h_CCQE_proton_picut");
    h_CCQE_proton_picut->SetFillColor(kRed);
    h_CCQE_proton_picut->SetMarkerStyle(21);
    h_CCQE_proton_picut->SetMarkerColor(kRed);
    TH1F*   h_2p2h_proton_picut = (TH1F*) file->Get("h_2p2h_proton_picut");
    h_2p2h_proton_picut->SetFillColor(kBlue);
    h_2p2h_proton_picut->SetMarkerStyle(21);
    h_2p2h_proton_picut->SetMarkerColor(kBlue);
    TH1F*   h_RES_proton_picut = (TH1F*) file->Get("h_RES_proton_picut");
    h_RES_proton_picut->SetFillColor(kGreen);
    h_RES_proton_picut->SetMarkerStyle(21);
    h_RES_proton_picut->SetMarkerColor(kGreen);
    TH1F*   h_DIS_proton_picut = (TH1F*) file->Get("h_DIS_proton_picut");
    h_DIS_proton_picut->SetFillColor(kYellow);
    h_DIS_proton_picut->SetMarkerStyle(21);
    h_DIS_proton_picut->SetMarkerColor(kYellow);
     
    THStack *stackHisto = new THStack("stackHisto","Final proton momentum distribution after Pion Cut");
    stackHisto->Add(h_DIS_proton_picut);
    stackHisto->Add(h_RES_proton_picut);
    stackHisto->Add(h_2p2h_proton_picut);
    stackHisto->Add(h_CCQE_proton_picut);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    stackHisto->Draw("");
    stackHisto->GetXaxis()->SetTitle("Momentum [MeV/c]");
    stackHisto->GetYaxis()->SetTitle("Number of events");
    stackHisto->GetYaxis()->SetTitleOffset(1.4);
    gPad->Modified();

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_CCQE_proton_picut,"CCQE","f");
    legend->AddEntry(h_2p2h_proton_picut,"2p2h","f");
    legend->AddEntry(h_RES_proton_picut,"RES","f");
    legend->AddEntry(h_DIS_proton_picut,"DIS","f");
    legend->Draw();

    gPad->Modified();
    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMomentumStackAfterPionCut.pdf");
    
    delete c1;
    delete legend;
    delete stackHisto;
///////////////////Comparison of two 2p2h channels
    TH1F*   h_2p2h_ifsingle_proton_momentum = (TH1F*) file->Get("h_2p2h_ifsingle_proton_momentum");
    h_2p2h_ifsingle_proton_momentum->SetLineColorAlpha(kBlue, 1);
    h_2p2h_ifsingle_proton_momentum->SetLineWidth(1.5);
    
    TH1F*   h_2p2h_ifzero_proton_momentum = (TH1F*) file->Get("h_2p2h_ifzero_proton_momentum");
    h_2p2h_ifzero_proton_momentum->SetLineColorAlpha(kGreen, 1);
    h_2p2h_ifzero_proton_momentum->SetLineWidth(1.5);
    
    long double normalizacja[2];
    for(int i=0;i<2;i++)
    {
       normalizacja[i]=0;
    }
    int binowanie=h_2p2h_ifsingle_proton_momentum->GetNbinsX();

    for(int i=1;i<=binowanie;i++)
    {
        normalizacja[0]+=h_2p2h_ifsingle_proton_momentum->GetBinContent(i);
        normalizacja[1]+=h_2p2h_ifzero_proton_momentum->GetBinContent(i);
    }
    int norma=normalizacja[0];
    h_2p2h_ifsingle_proton_momentum->Scale(norma/normalizacja[0]);
    h_2p2h_ifzero_proton_momentum->Scale(norma/normalizacja[1]);
    
    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    c1->SetLogy();
    h_2p2h_ifsingle_proton_momentum->Draw("");
    h_2p2h_ifzero_proton_momentum->Draw("SAME");
    
    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_2p2h_ifsingle_proton_momentum,"1PaPI","l");
    legend->AddEntry(h_2p2h_ifzero_proton_momentum,"0PaPI","l");
    legend->Draw();

    gPad->Modified();
    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/2p2hChannelComparisonMomentum.pdf");
    
    delete c1;
    delete legend;
    ///////////////
    TH1F*   h_CCQE_muon = (TH1F*) file->Get("h_CCQE_muon");
    h_CCQE_muon->SetLineColorAlpha(kRed, 1);
    h_CCQE_muon->SetLineWidth(1.5);

    TH1F*   h_2p2h_muon = (TH1F*) file->Get("h_2p2h_muon");
    h_2p2h_muon->SetLineColorAlpha(kBlue, 1);
    h_2p2h_muon->SetLineWidth(1.5);

    TH1F*   h_RES_muon = (TH1F*) file->Get("h_RES_muon");
    h_RES_muon->SetLineColorAlpha(kGreen, 1 );
    h_RES_muon->SetLineWidth(1.5);

    TH1F*   h_DIS_muon = (TH1F*) file->Get("h_DIS_muon");
    h_DIS_muon->SetLineColorAlpha(kOrange, 1);
    h_DIS_muon->SetLineWidth(1.5);

    h_CCQE_muon->SetNameTitle("h_CCQE_muon","Muon momentum distribution");
    h_CCQE_muon->GetXaxis()->SetTitle("Momentum [MeV/c]");
    h_CCQE_muon->GetYaxis()->SetTitle("Number of events");
    h_CCQE_muon->GetYaxis()->SetTitleOffset(1.4);

    c1 = new TCanvas("c1"," ",10,10,1400,1000);
    gPad->Modified();
    h_CCQE_muon->Draw("HIST");
    h_RES_muon->Draw("HIST SAME");
    h_DIS_muon->Draw("HIST SAME");;
    h_2p2h_muon->Draw("HIST SAME");

    TLegend *legend = new TLegend(0.7482117,0.6940452,0.9799714,0.9353183);
    legend->AddEntry(h_RES_muon,"RES","l");
    legend->AddEntry(h_2p2h_muon,"2p2h","l");
    legend->AddEntry(h_CCQE_muon,"CCQE","l");
    legend->AddEntry(h_DIS_muon,"DIS","l");
    legend->Draw();
    
    gPad->Modified();
    c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/MuonMomentumComparison.pdf");
    
    delete c1;
    delete legend;
    file->Close();
}
