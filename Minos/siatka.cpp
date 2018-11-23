{
///////////1->Dane/////////2->MC/////////////
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
////////////////////////////////////////////////////////////////////////
    TH1F *E1 = new TH1F("E1", "Dane", 60, 2, 8);


/////////////////////////////////////////////////////////CIECIA////////////////////////////////////////////////////////
/////0////if(Good1==1)
/////1////if(Good1==1 && Energia1<8)
/////2////if(Good1==1 && Energia1<8 && Energia1>2 && Trklen1>40)
/////3////if(Good1==1 && Energia1<8 && Mnstp1<=3 && Trklen1>20 && Charge1<0 && Sigmax1>0 && Sigmax1<15 && Spher1<0.1)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int norma=100000;

        for(int i=0; i<max1 ;i++){
        t1->GetEntry(i);
            if(Good1==1){
                E1->Fill(Energia1);
                        }
                                }
        Double_t norm1 = E1->GetEntries();
        E1->Scale(norma/norm1);

/////////////////////////////////////////////////////////////////
long double Chi2=10000000;

float A=0;
float B=0;

int binowanie=E1->GetNbinsX();
float mini= E1->GetXaxis()->GetXmin();
float maxi= E1->GetXaxis()->GetXmax();
float zakres=maxi-mini;
float f_E;
long double bin1;
long double bin2;
Int_t igood=0;
Int_t ndf=binowanie-3;

for(float a=0.9;a<+1.1;a+=0.005){
        for(float b=-1.2;b<+1.2;b+=0.04){
        cout<<a<<" "<<b<<endl;
                TH1F *E2 = new TH1F("E2", "MC", binowanie, mini, maxi);

                for(int i=0; i<max2 ;i++){
                    t2->GetEntry(i);
                        if(Good2==1){
                            E2->Fill(a*Energia2+b);
                                                    }
                                            }

                Double_t norm2 = E2->GetEntries();
                E2->Scale(norma/norm2);

                long double Chi=0;


            for(int i=1;i<binowanie;i++){
                    bin1=E1->GetBinContent(i);
                    bin2=E2->GetBinContent(i);
                    Chi+=fabs((bin1-bin2)*(bin1-bin2));
                                }

                if(Chi<Chi2){
                    A=a;
                    B=b;
                    Chi2=Chi;
                        }

                delete E2;
                            }
              }
delete E1;
//////////////////////////////////////////////////////////////////////////////
TH1F *E1 = new TH1F("E1", "Dane", binowanie, mini, maxi);
TH1F *E2 = new TH1F("E2", "Fixed MC", binowanie, mini, maxi);
TH1F *E3 = new TH1F("E3", "MC", binowanie, mini, maxi);
    for(int i=0; i<max1 ;i++){
        t1->GetEntry(i);
            if(Good1==1){
                E1->Fill(Energia1);
                        }
                                }

    for(int i=0; i<max2 ;i++){
        t2->GetEntry(i);
        if(Good2==1){
            E3->Fill(Energia2);
            E2->Fill(A*Energia2+B);
                                    }
                                }
Double_t norm1 = E1->GetEntries();
E1->Scale(1/norm1);

Double_t norm2 = E2->GetEntries();
E2->Scale(1/norm2);

Double_t norm3 = E3->GetEntries();
E3->Scale(1/norm3);
        long double Chi=0;

                for(int i=1;i<=binowanie;i++){
                    bin1=E1->GetBinContent(i);
                    bin2=E2->GetBinContent(i);
                    Chi+=fabs((bin1-bin2)*(bin1-bin2));
                                }

cout<<"A="<<A<<" "<<"B="<<B<<" "<<"Chi2 "<<Chi/ndf<<endl;


////////////////////////////////////////////////////////////////////////
        TCanvas *c1 = new TCanvas("c1","c1");
        gStyle->SetOptTitle(kFALSE);
        gStyle->SetOptStat(0);
        E1->SetLineColor(kRed);
        E1->SetLineWidth(2);

        E2->SetLineColor(kBlue);
        E2->SetLineWidth(2);

        E3->SetLineColor(kGreen);
        E3->SetLineWidth(2);

        E1->Draw();
        E1->GetYaxis()->SetTitle("number of events");
        E1->GetXaxis()->SetTitle("Energy GeV");
        E2->Draw("SAME");
        E3->Draw("SAME");

   auto legend = new TLegend(0.1,0.7,0.4,0.9);
   legend->AddEntry(E1,"Data from MINOS+","l");
   legend->AddEntry(E2,"Monte Carlo after correction","l");
   legend->AddEntry(E3,"Monte Carlo","l");
   legend->Draw();
}
