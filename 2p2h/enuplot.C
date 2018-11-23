void enuplot(){

gROOT->SetStyle("T2K");
gStyle->SetOptStat(1111);
gStyle->SetOptFit(111);
gStyle->SetPalette(1,0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);
gPad->SetLeftMargin(0.15)

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

THStack *stackHisto = new THStack("stackHisto","Final proton momemtum distribution");
    stackHisto->Add(h_DIS_proton);
    stackHisto->Add(h_CCQE_proton);
    stackHisto->Add(h_2p2h_proton);
    stackHisto->Add(h_RES_proton);


c1 = new TCanvas("c1"," ",10,10,1400,1000);
stackHisto->Draw("");
stackHisto->GetXaxis()->SetTitle("Momemtum [Mev]");
stackHisto->GetYaxis()->SetTitle("Number of events");
stackHisto->GetYaxis()->SetTitleOffset(1.4);
gPad->Modified();

TLegend *legend = new TLegend(0.68,0.72,0.98,0.92);
    legend->AddEntry(h_RES_proton,"RES","f");
    legend->AddEntry(h_2p2h_proton,"2p2h","f");
    legend->AddEntry(h_CCQE_proton,"CCQE","f");
    legend->AddEntry(h_DIS_proton,"DIS","f");
    legend->Draw();

c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMomemntumStack.pdf");

delete c1;
delete legend;
delete stackHisto;
//////////PROTON MAX MOMENTUM////
TH1F*   h_CCQE_proton_max = (TH1F*) file->Get("h_CCQE_proton_max");
    h_CCQE_proton_max->SetFillColor(kRed);
    h_CCQE_proton_max->SetMarkerStyle(21);
    h_CCQE_proton_max->SetMarkerColor(kRed);
TH1F*   h_2p2h_proton_max = (TH1F*) file->Get("h_2p2h_proton_max");
   h_2p2h_proton_max->SetFillColor(kBlue);
   h_2p2h_proton_max->SetMarkerStyle(21);
   h_2p2h_proton_max->SetMarkerColor(kBlue);
TH1F*   h_RES_proton_max = (TH1F*) file->Get("h_RES_proton_max");
   h_RES_proton_max->SetFillColor(kGreen);
   h_RES_proton_max->SetMarkerStyle(21);
   h_RES_proton_max->SetMarkerColor(kGreen);
TH1F*   h_DIS_proton_max = (TH1F*) file->Get("h_DIS_proton_max");
   h_DIS_proton_max->SetFillColor(kYellow);
   h_DIS_proton_max->SetMarkerStyle(21);
   h_DIS_proton_max->SetMarkerColor(kYellow);

THStack *stackHisto = new THStack("stackHisto","Final proton max momemtum distribution");
    stackHisto->Add(h_DIS_proton_max);
    stackHisto->Add(h_CCQE_proton_max);
    stackHisto->Add(h_2p2h_proton_max);
    stackHisto->Add(h_RES_proton_max);

c1 = new TCanvas("c1"," ",10,10,1400,1000);
stackHisto->Draw("");
stackHisto->GetXaxis()->SetTitle("Momemtum [Mev]");
stackHisto->GetYaxis()->SetTitle("Number of events");
stackHisto->GetYaxis()->SetTitleOffset(1.4);
gPad->Modified();

TLegend *legend = new TLegend(0.68,0.72,0.98,0.92);
    legend->AddEntry(h_RES_proton_max,"RES","f");
    legend->AddEntry(h_2p2h_proton_max,"2p2h","f");
    legend->AddEntry(h_CCQE_proton_max,"CCQE","f");
    legend->AddEntry(h_DIS_proton_max,"DIS","f");
    legend->Draw();

c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/ProtonMaxMomemntumStack.pdf");
delete c1;
delete legend;
delete stackHisto;

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
h_CCQE->GetXaxis()->SetTitle("Momemtum [Mev]");
h_CCQE->GetYaxis()->SetTitle("Number of events");
h_CCQE->GetYaxis()->SetTitleOffset(1.4);
c1 = new TCanvas("c1"," ",10,10,1400,1000);
c1->SetLogy();
h_CCQE->Draw("");
h_2p2h->Draw("SAME");
h_res->Draw("SAME");
h_DIS->Draw("SAME");
h_Coh->Draw("SAME");

TLegend *legend = new TLegend(0.68,0.72,0.98,0.92);
    legend->AddEntry(h_CCQE,"CCQE","l");
    legend->AddEntry(h_res,"RES","l");
    legend->AddEntry(h_2p2h,"2p2h","l");
    legend->AddEntry(h_Coh,"COH","l");
    legend->AddEntry(h_DIS,"DIS","l");
    legend->Draw();

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
h_anti_numu->GetXaxis()->SetTitle("Momemtum [Mev]");
h_anti_numu->GetYaxis()->SetTitle("Number of events");
h_anti_numu->GetYaxis()->SetTitleOffset(1.4);
c1 = new TCanvas("c1"," ",10,10,1400,1000);
c1->SetLogy();
h_anti_numu->Draw("");
h_numu->Draw("SAME");
h_nue->Draw("SAME");
h_anti_nue->Draw("SAME");

TLegend *legend = new TLegend(0.68,0.72,0.98,0.92);
    legend->AddEntry(h_anti_numu,"anti_numu","l");
    legend->AddEntry(h_numu,"numu","l");
    legend->AddEntry(h_nue,"nue","l");
    legend->AddEntry(h_anti_nue,"anti_nue","l");
    legend->Draw();

c1->Print("/Users/kolos/Desktop/root_v5.34.36/1.Programy/2p2h/output/FlavourNeutrinoMomentum.pdf");

file->Close();
}
