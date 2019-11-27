using namespace std;

void add(Float_t *arr, Float_t val)
{
    for(int i=0;i<1024;i++)
    {
	arr[i]+=val;
    }
}

void drawMultiGraph(TString fname, int ev=0) //-1 evs_to_process means all
{
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
	t->GetEntry(ev);
	TMultiGraph *mg=new TMultiGraph();

	TGraph *gr1=new TGraph(1000,time[0]+12,wvfm[0]+12);
	gr1->SetLineColor(kRed);
	gr1->SetLineWidth(2);
	TGraph *gr2=new TGraph(1000,time[1]+12,wvfm[1]+12);
	gr2->SetLineColor(kBlue);
	gr2->SetLineWidth(2);


    mg->Add(gr1);
	//mg->Add(gr2);

	mg->Draw("AL");
    mg->GetXaxis()->SetTitle("czas t [ns]");
    gPad->Modified();

    auto legend = new TLegend(0.1,0.7,0.48,0.9);
   legend->SetHeader("Legenda"); // option "C" allows to center the header
   legend->AddEntry(gr1,"Sygnal ''start''","l");
   legend->AddEntry(gr2,"Sygnal ''stop''","l");
   legend->Draw();

//Aby odpaliæ .x draw("nazwa pliku")
}
