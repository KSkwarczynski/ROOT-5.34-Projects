#include "TMinuit.h
////GLOBALNE PARAMETRY////
TH1F* E1;
int *wyborciec;
double *MaksEnergia;

//////////FUNKCJA KTORA BEDZIE MINIMALIZOWANA/////////////////
void chi2( Int_t & /*nPar*/, Double_t * /*grad*/ , Double_t &fval, Double_t *par, Int_t /*iflag */  ){
///////////////////////////////////////////////
    TFile *f2= TFile::Open("MC.root");
	TTree *t2;
	Float_t Energia2;
    Float_t Good2;
    Float_t Trklen2;
    Float_t Charge2;
    Float_t Sigmax2;
    Float_t Spher2;
    Float_t Mnstp2;
	f2->GetObject("t2",t2);
  	t2->SetBranchAddress("evisgev2", &Energia2);
	t2->SetBranchAddress("goodstdtrack2", &Good2);
    t2->SetBranchAddress("trklen2", &Trklen2);
    t2->SetBranchAddress("charge2", &Charge2);
    t2->SetBranchAddress("sigmax2", &Sigmax2);
    t2->SetBranchAddress("spher2", &Spher2);
    t2->SetBranchAddress("mnstp2", &Mnstp2);
    int max2=t2->GetEntries();
////WARTOSCI POMOCNE//////////////////////////
    int binowanie=E1->GetNbinsX();
    float mini= E1->GetXaxis()->GetXmin();
    float maxi= E1->GetXaxis()->GetXmax();
    float zakres=maxi-mini;
    double bin1;
    double bin2;
    double error;
    double Energia;
////////DEKLARACJA HISTOGRAMOW/////////////
    TH1F *h1 = (TH1F*)(E1->Clone("h1"));
    TH1F* E2 = new TH1F("E2", "MC", binowanie, mini, maxi);
    E2->Sumw2();
        if(wyborciec==1){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=par[0]*Energia2+par[1];
                    if(Good2==1 && Energia<MaksEnergia){
                        E2->Fill(Energia);
                                                }
                                }
                        }
        if(wyborciec==2){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=par[0]*Energia2+par[1];
                    if(Good2==1 && Energia<MaksEnergia && Energia>2 && Trklen2>40){
                        E2->Fill(Energia);
                                                }
                                    }
                }
        if(wyborciec==3){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=par[0]*Energia2+par[1];
                    if(Good2==1 && Energia<MaksEnergia && Mnstp2<=3 && Trklen2>20 && Charge2<0 && Sigmax2>0 && Sigmax2<15 && Spher2<0.1){
                        E2->Fill(Energia);
                                                }
                                    }
                }
//////////////////NORMALIZACJA///////////////////
     long double norm1 = 0;
     long double norm2 = 0;

            for(int i=1;i<=binowanie;i++){
                    norm1+=h1->GetBinContent(i);
                    norm2+=E2->GetBinContent(i);
                                        }

    int norma=norm1;
    h1->Scale(norma/norm1);
    E2->Scale(norma/norm2);
////////////////ROZNICA KWADRATOW///////////////
            double Chi=0;
            for(int i=1;i<=binowanie;i++){
                    bin1=h1->GetBinContent(i);
                    bin2=E2->GetBinContent(i);
                    error=h1->GetBinError(i);
                    if(error!=0){
                    Chi+=(bin1-bin2)*(bin1-bin2)/(error*error);
                            }
                                }

    delete h1;
    delete E2;
    delete f2;

    fval = Chi;
}

///////////////WLASCIWY PROGRAM//////////////
void analiza(){
////TUTAJ WYBIERA SIE ZESTAW CIEC 1, 2 LUB 3 ZMIENIAJAC WARTOSC ZMIENNEJ "WYBORCIEC"////
    wyborciec=1;
////MAKSYMALNA ENERGIA DLA WSZYSTKICH ZESTAWOW CIEC///////////////////
    MaksEnergia=8;
////DEKLARACJ HISTOGRAMOW I PRZYDATNYCH ZMIENNYCH//////////////////////////////////////////
////ZMIENIAJAC BINOWANIE I ZASIEG E1 ZMIENI SIE WE WSZYSTKICH POZOSTALYCH HISTOGRAMACH//
    E1 = new TH1F("E1", "Dane", 80, 0, 8);
    E1->Sumw2();
    int binowanie=E1->GetNbinsX();
    float mini= E1->GetXaxis()->GetXmin();
    float maxi= E1->GetXaxis()->GetXmax();
    float zakres=maxi-mini;
    long double bin1;
    long double bin2;
    double NDF=binowanie-3;
    TH1F* E2 = new TH1F("E2", "MC", binowanie, mini, maxi);
////OTWORZENIE DRZEWA////////1->Dane/////////2->MC///////////////////////////////////////
    TFile *f1= TFile::Open("Dane.root");
	TTree *t1;
	Float_t Energia1;
    Float_t Good1;
    Float_t Trklen1;
    Float_t Charge1;
    Float_t Sigmax1;
    Float_t Spher1;
    Float_t Mnstp1;
	f1->GetObject("t1",t1);
  	t1->SetBranchAddress("evisgev1", &Energia1);
	t1->SetBranchAddress("goodstdtrack1", &Good1);
    t1->SetBranchAddress("trklen1", &Trklen1);
    t1->SetBranchAddress("charge1", &Charge1);
    t1->SetBranchAddress("sigmax1", &Sigmax1);
    t1->SetBranchAddress("spher1", &Spher1);
    t1->SetBranchAddress("mnstp1", &Mnstp1);
    int max1=t1->GetEntries();

    TFile *f2= TFile::Open("MC.root");
	TTree *t2;
	Float_t Energia2;
    Float_t Good2;
    Float_t Trklen2;
    Float_t Charge2;
    Float_t Sigmax2;
    Float_t Spher2;
    Float_t Mnstp2;
	f2->GetObject("t2",t2);
  	t2->SetBranchAddress("evisgev2", &Energia2);
	t2->SetBranchAddress("goodstdtrack2", &Good2);
    t2->SetBranchAddress("trklen2", &Trklen2);
    t2->SetBranchAddress("charge2", &Charge2);
    t2->SetBranchAddress("sigmax2", &Sigmax2);
    t2->SetBranchAddress("spher2", &Spher2);
    t2->SetBranchAddress("mnstp2", &Mnstp2);
    int max2=t2->GetEntries();
/////////////////////////////////////////WYPELNIENIE HISTOGRAMU W ZALEZNOSCI OD ZESTAWU CIEC//////////////////////////////////////////////////
        double Energia=0;
if(wyborciec==1){
        for(int i=0; i<max1 ;i++){
        t1->GetEntry(i);
            Energia=Energia1;
            if(Good1==1 && Energia<MaksEnergia){
                E1->Fill(Energia);
                        }
                                }
                    }
if(wyborciec==2){
        for(int i=0; i<max1 ;i++){
        t1->GetEntry(i);
            Energia=Energia1;
            if(Good1==1 && Energia<MaksEnergia && Energia>2 && Trklen1>40){
                E1->Fill(Energia);
                        }
                                }
                    }
if(wyborciec==3){
        for(int i=0; i<max1 ;i++){
        t1->GetEntry(i);
            Energia=Energia1;
            if(Good1==1 && Energia<MaksEnergia && Mnstp1<=3 && Trklen1>20 && Charge1<0 && Sigmax1>0 && Sigmax1<15 && Spher1<0.1){
                E1->Fill(Energia);
                        }
                                }
                    }
////////////////DEKLARACJA TABLICY Z PARAMETRAMI POTRZEBNYMI DO TMINUIT I INNE ZMIENNE////////////////////////
double par[2];
double minParams[2];
double parErrors[2];
double A=0;
double B=0;
long double ErrorA=0;
long double ErrorB=0;
double ChiComparison=100000;
double krokA=0;
double krokB=0;
////////TMINUIT ZALEZY OD WARTOSCI POCZATKOWYCH DLATEGO PETLA ZMIENIAJACA ZIARNO////////
for(float a=0.96;a<=0.96;a+=1.0){
        for(float b=0.015;b<=0.045;b+=0.015){
////////////////MINIMALIZACJA FUNKCJI chi2 ZA POMOCA TMINUIT///////////////
        TVirtualFitter* minuit = TVirtualFitter::Fitter( 0, 2 );
        minuit->SetParameter(0, "a",  0.96, 10.0, 0, 0 );
        minuit->SetParameter(1, "b",     b, 10.0, 0, 0 );
        minuit->SetFCN( chi2 );

        double arglist[100];
        arglist[0] = 0;
        minuit->ExecuteCommand("SET PRINT",arglist, 1 );

        arglist[0] = 5000;
        arglist[1] = 0.01;
        //minuit->ExecuteCommand("MINOS",arglist,2);
        minuit->ExecuteCommand("MIGRAD",arglist,2);
        minuit->ExecuteCommand("HESSE",arglist,2);

            for (int i = 0; i < 2; ++i) {
                minParams[i] = minuit->GetParameter(i);
                parErrors[i] = minuit->GetParError(i);
                printf( "%d-th para = %6.3f, err = %6.3f\n", i, minParams[i], parErrors[i] );
////////////////DODATKOWE PARAMETRY DO UZYSKANIA Z TMINUIT/////////////
            double chi2, edm, errdef;
            int nvpar, nparx;
            minuit->GetStats(chi2,edm,errdef,nvpar,nparx);                                        }
////////////////////////////////////////////////////////////////////////
        TH1F *h2 = new TH1F("h2", "MC after correction", binowanie , mini, maxi);
        if(wyborciec==1){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=minParams[0]*Energia2+minParams[1];
                    if(Good2==1 && Energia<MaksEnergia){
                        h2->Fill(Energia);
                                                }
                                }
                        }
        if(wyborciec==2){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=minParams[0]*Energia2+minParams[1];
                    if(Good2==1 && Energia<MaksEnergia && Energia>2 && Trklen2>40){
                        h2->Fill(Energia);
                                                }
                                    }
                }
        if(wyborciec==3){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=minParams[0]*Energia2+minParams[1];
                    if(Good2==1 && Energia<MaksEnergia && Mnstp2<=3 && Trklen2>20 && Charge2<0 && Sigmax2>0 && Sigmax2<15 && Spher2<0.1){
                        h2->Fill(Energia);
                                                }
                                    }
                }
//////////////////////////////////////////////////////////////////
        Double_t norm1 = 0;
        Double_t norm2 = 0;
        for(int i=1;i<binowanie;i++){
                norm1+=E1->GetBinContent(i);
                norm2+=h2->GetBinContent(i);
                                    }
        E1->Scale(norm2/norm1);
/////////WYBIERAMY PARAMETRY DLA KTORYCH MAMY NAJMNIEJSZE CHI2////////
        const int tabela=binowanie;
        double res[tabela];
        int ndf=0, igood=0;
        double ChiF=0;
        h2->Chi2TestX(E1, ChiF, ndf, igood, "UU NORM", res);
                    if(ChiF<ChiComparison){
                    A=minParams[0];
                    B=minParams[1];
                    ErrorA=parErrors[0];
                    ErrorB=parErrors[1];
                    ChiComparison=ChiF;
                    krokA=a;
                    krokB=b;
                        }
        delete h2;
        delete minuit;
                                    }
                            }
///////////HISTOGRAM MC PO POPRAWCE DLA ROZNYCH ZESTAWOW CIEC//////////
        TH1F *h2 = new TH1F("h2", "MC after correction", binowanie , mini, maxi);
        if(wyborciec==1){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=A*Energia2+B;
                    if(Good2==1 && Energia<MaksEnergia){
                        h2->Fill(Energia);
                                                }
                                }
                        }
        if(wyborciec==2){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=A*Energia2+B;
                    if(Good2==1 && Energia<MaksEnergia && Energia>2 && Trklen2>40){
                        h2->Fill(Energia);
                                                }
                                    }
                }
        if(wyborciec==3){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=A*Energia2+B;
                    if(Good2==1 && Energia<MaksEnergia && Mnstp2<=3 && Trklen2>20 && Charge2<0 && Sigmax2>0 && Sigmax2<15 && Spher2<0.1){
                        h2->Fill(Energia);
                                                }
                                    }
                }
//////////////////HIST MC BEZ POPRAWKI/////////////////////////////////////////
    TH1F *h4 = new TH1F("h4", "MC", binowanie , mini, maxi);
if(wyborciec==1){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=Energia2;
                    if(Good2==1 && Energia<MaksEnergia){
                        h4->Fill(Energia);
                                                }
                                    }
                }
if(wyborciec==2){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=Energia2;
                    if(Good2==1 && Energia<MaksEnergia && Energia>2 && Trklen2>40){
                        h4->Fill(Energia);
                                                }
                                    }
                }
if(wyborciec==3){
            for(int i=0; i<max2 ;i++){
                t2->GetEntry(i);
                Energia=Energia2;
                    if(Good2==1 && Energia<MaksEnergia && Mnstp2<=3 && Trklen2>20 && Charge2<0 && Sigmax2>0 && Sigmax2<15 && Spher2<0.1){
                        h4->Fill(Energia);
                                                }
                                    }
                }
/////////////NORMALIZACJA DO JEDYNKI HISTOGRAMOW//////////
    Double_t norm1 = 0;
    Double_t norm2 = 0;
    Double_t norm4 = 0;
            for(int i=1;i<binowanie;i++){
                    norm1+=E1->GetBinContent(i);
                    norm2+=h2->GetBinContent(i);
                    norm4+=h4->GetBinContent(i);
                                }

    double normalizacja=norm2;
    E1->Scale(normalizacja/norm1);

    h2->Scale(normalizacja/norm2);

    h4->Scale(normalizacja/norm4);
///////////////////////////////CHI2 I WYNIKI///////////////////////////
    const int tabela=binowanie;
    double res[tabela];
	int ndf, igood;
	double ChiF;
	h2->Chi2TestX(E1, ChiF, ndf, igood, "UU NORM", res);
//////DLA ZESTAWU 2 JEST MNIEJ BINOW BO ENERGIA OD 2GeV DLATEGO TRZEBA POPRAWIC NDF/////////////
if(wyborciec==2){
NDF=binowanie*(maxi-mini)/maxi;
}
cout<<"krok a "<<krokA<<" krok b "<< krokB<<endl;
cout<<"a= "<<A<<"+/-"<<ErrorA<<" b= "<<B<<"+/-"<<ErrorB<<" Chi2/ndf= "<<ChiF/NDF<<endl;
/////////////////////////RYSOWANIE////////////////////////////////////
        TCanvas *c1 = new TCanvas("c1","c1");
        gStyle->SetOptTitle(kFALSE);
        gStyle->SetOptStat(0);

        E1->SetLineColor(1);
        E1->SetLineWidth(2);
        E1->SetMarkerStyle(kFullCircle);
        E1->SetMarkerSize(0.8);

        h2->SetLineColor(kBlue);
        h2->SetLineWidth(2);

        h4->SetLineColor(kGreen);
        h4->SetLineWidth(2);

        E1->Draw("PLC PMC");
        E1->GetYaxis()->SetTitle("number of events");
        E1->GetXaxis()->SetTitle("Reconstructed energy [GeV]");
        h2->Draw("SAME");
        h4->Draw("SAME");
////////////////////////LEGENDA//////////////////////////////////
   auto legend = new TLegend(0.1,0.7,0.4,0.9);
   legend->AddEntry(E1,"Data from MINOS+","leP");
   legend->AddEntry(h2,"Monte Carlo after correction","l");
   legend->AddEntry(h4,"Monte Carlo","l");
   legend->Draw();
}
