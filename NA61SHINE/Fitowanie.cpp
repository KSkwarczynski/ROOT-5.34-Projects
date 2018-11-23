{
    TFile *file = new TFile("histograms.root");
//deklaracja graphow
    TGraph* g1=new TGraph();
       g1->SetLineWidth(4);
       g1->SetMarkerSize(1.5);
       g1->SetMarkerStyle(8);
       g1->SetTitle("Rozklad szerokosci rokladu #sigma dla dyskryminatora LED");
    TGraph* g2=new TGraph();
       g2->SetLineWidth(4);
       g2->SetMarkerSize(1.5);
       g2->SetMarkerStyle(8);
       g2->SetTitle("Rozklad szerokosci rokladu #sigma dla dyskryminatora CFD");
    int i=0;
    int k=0;


 ///////LED//////////////
for(int LED=10; LED<=25; LED+=1){
       //wczytanie histogramu
       TH1F *hpx1 = (TH1F*)file->Get( Form("LED%d;1",LED) );

       int binmax1 = hpx1->GetMaximumBin();
       double x1 = hpx1->GetXaxis()->GetBinCenter(binmax1);

       TF1 *f1 = new TF1("f1","gaus",x1-0.03*4 , x1+0.03*4 );
       hpx1->Fit(f1,"Q");
       TF1 *fitResult1 = hpx1->GetFunction("f1");

       float sigma1=fitResult1->GetParameter(2);
       g1->SetPoint(i, LED, sigma1);
       i++;
    }

for(int CFD=10; CFD<=25; CFD+=1){
       //wczytanie histogramu
       TH1F *hpx2 = (TH1F*)file->Get( Form("CFD%d;1",CFD) );

       int binmax2 = hpx2->GetMaximumBin();
       double x2 = hpx2->GetXaxis()->GetBinCenter(binmax2);

       TF1 *f2 = new TF1("f2","gaus",x2-0.03*4  , x2+0.03*4 );
       hpx2->Fit(f2,"Q");
       TF1 *fitResult2 = hpx2->GetFunction("f2");

       float sigma2=fitResult2->GetParameter(2);
       g2->SetPoint(k, CFD, sigma2);
       k++;
    }

c1= new TCanvas("c1", "Porównanie sigm ", 1000, 1000);
c1->Divide(2,1);

c1->cd(1);
g1->Draw("AP");
g1->GetXaxis()->SetTitle("prog (LED)");
g1->GetYaxis()->SetTitle("szerokosc rozkladu #sigma");
g1->GetYaxis()->SetTitleOffset(1.6);

c1->cd(2);
g2->Draw("AP");
g2->GetXaxis()->SetTitle("procent maksimum (CFD) [%]");
g2->GetYaxis()->SetTitle("szerokosc rozkladu #sigma");
g2->GetYaxis()->SetTitleOffset(1.6);
}
