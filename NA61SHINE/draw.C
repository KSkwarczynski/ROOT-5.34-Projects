using namespace std;

void add(Float_t *arr, Float_t val)
{
    for(int i=0;i<1024;i++)
    {
	arr[i]+=val;
    }
}
//funkcja ktora znajduje czas kiedy przekroczono threshold dla LED
float timing1(float *wvfm, float *time, float discriminator){
    float t;
    int licznik;
//znalezienie kiedy przekracza threshold
    for(int i=0 ; i<1024 ; i++){
    if(wvfm[i]>discriminator){
        t=time[i];
        licznik=i;
        break;
        }
            }
//fitowanie w okolicy threshold do funkcji kwadratowej i na tej podstawie znalezienie dokladnej wartosci kiedy przebija threshold
    TGraph* g=new TGraph(10,wvfm+licznik-5,time+licznik-5);
	TF1  *f1 = new TF1("f1","[0]*x^2+[1]*x+[2]",0,200);
    g->Fit(f1 , "Q");
    t=g->Eval(discriminator);
    delete g;
    delete f1;

return t;
}


//funkcja ktora znajduje czas kiedy przekroczono threshold dla CFD
float timing2(float *wvfm, float *time, float discriminator){
    float t;
    int licznik;
    float srednia = TMath::Mean(100,wvfm);
    int lokalne=TMath::LocMax(1024,wvfm);
//dopasowanie w okolicy maksimum do funkcji kwadratowej
    TGraph* g1=new TGraph(20,time+lokalne-10,wvfm+lokalne-10);
    TF1  *f2 = new TF1("f2","[0]*x^2+[1]*x+[2]",0,200);
    g1->Fit(f2,"Q");
    //TF1 *fitResult = g1->GetFunction("f2");
//parametry dopasowania
    float a=f2->GetParameter(0);
    float b=f2->GetParameter(1);
    float c=f2->GetParameter(2);

    float maksimum= -b/(2*a);
//majac maksimum mozemy obliczyc theshold ktory jest procentem maksimum
    float dyskriminator = (maksimum-srednia)*discriminator/100;
//orientacyjne szukanie threshold
    for(int i=0 ; i<1024 ; i++){
      if(wvfm[i]>dyskriminator){
        t=time[i];
        licznik=i;
        break;
        }
            }
//dokladne szukanie threshold na podstawie dopasowania
    TGraph* g=new TGraph(10,wvfm+licznik-5,time+licznik-5);
	TF1  *f1 = new TF1("f1","[0]*x^2+[1]*x+[2]",0,200);
    g->Fit(f1,"Q");
    t=g->Eval(dyskriminator);

    delete g;
    delete f1;
    delete g1;
    delete f2;
return t;
}

void draw(TString fname, int ev=0) //-1 evs_to_process means all
{
    //wczytanie danych
	TFile *f=TFile::Open(fname);
	TTree *t;
	f->GetObject("t",t);
	float wvfm[2][1024];
	float time[2][1024];
	TCanvas *c=new TCanvas("c","",1024,768);
	t->SetBranchAddress("y1",wvfm[0]);
	t->SetBranchAddress("x1",time[0]);
	t->SetBranchAddress("y2",wvfm[1]);
	t->SetBranchAddress("x2",time[1]);
	//t->GetEntry(ev);
/////////////////////////////////////////////////

    TFile *plik = new TFile("histograms.root","RECREATE");
    float dt1;
    float dt2;
    float t1;
    float t2;
    float t3;
    float t4;
///////petla dla LED////////
int max=t->GetEntries();
//int max=10000;


for(int LED=10; LED<=25; LED+=1){
    //tworzenie histogramow dla odpowiedniej wartosci LED
  TH1F *h1 = new TH1F(Form("LED%d",LED),Form("Histogram for LED=%d",LED), 600, -8, 8);
    for(int m=0; m <max; m++){
        if(m%1000==0)
        cout<<m<<endl;
        t->GetEntry(m);
        float max1=TMath::MaxElement(1024,wvfm[0]);
        float max2=TMath::MaxElement(1024,wvfm[1]);
//////wycinamy niektore przypadki na podstawie wykresu amplitud///
        if(max1<=140 || max2<=180){continue;}

            t1=timing1(wvfm[0],time[0], LED);
            t2=timing1(wvfm[1],time[1], LED);
        ////interesuje nas roznica czasow dlatego dt1/////
            dt1=t2-t1;
            h1->Fill(dt1);


        }
    h1->GetXaxis()->SetTitle("roznica czasow [ns]");
    h1->Write();
    delete h1;
            }

//////petla dala CFD//////
for(int CFD=10; CFD<=25; CFD+=1){
    //tworzenie histogramow dla odpowiedniej wartosci LED
   TH1F *h2 = new TH1F( Form("CFD%d",CFD),Form("Histogram for CFD=%d",CFD), 600, -8, 8);
    for(int m=0; m < max; m++){
        //licznik
        if(m%1000==0)
        cout<<m<<endl;
        t->GetEntry(m);
        float max1=TMath::MaxElement(1024,wvfm[0]);
        float max2=TMath::MaxElement(1024,wvfm[1]);

        if(max1<=140 || max2<=180){continue;}
            t3=timing2(wvfm[0],time[0], CFD);
            t4=timing2(wvfm[1],time[1], CFD);
        ////interesuje nas roznica czasow dlatego dt2/////
            dt2=t4-t3;
            h2->Fill(dt2);

                    }
    h2->GetXaxis()->SetTitle("roznica czasow [ns]");
    h2->Write();
    delete h2;
        }

plik->Close();
delete plik;
}
