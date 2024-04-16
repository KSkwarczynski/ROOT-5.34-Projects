
#include <TMath.h>
#include <TGraph2D.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH1.h>

void graph2dfit()
{
   gStyle->SetOptStat(0);
   gStyle->SetOptFit();

   auto c = new TCanvas("c","Graph2D example",0,0,600,800);
   c->Divide(2,3);

   double rnd, x, y, z;
   double e = 0.3;
   int nd = 400;
   int np = 10000;

   TRandom r;
   double fl = 6;
   auto f2 = new TF2("f2","1000*(([0]*sin(x)/x)*([1]*sin(y)/y))+200",
      -fl,fl,-fl,fl);
   f2->SetParameters(1,1);
   auto dt = new TGraph2D();

   // Fill the 2D graph
   double zmax = 0;
   for (int N=0; N<nd; N++) {
      f2->GetRandom2(x,y);
      // Generate a random number in [-e,e]
      rnd = 2*r.Rndm()*e-e;
      z = f2->Eval(x,y)*(1+rnd);
      if (z>zmax) zmax = z;
      dt->SetPoint(N,x,y,z);
   }

   double hr = 350;
   auto h1 = new TH1D("h1",
   "#splitline{Difference between Original}{#splitline{function and Function}{with noise}}",
   100, -hr, hr);
   auto h2 = new TH1D("h2",
   "#splitline{Difference between Original}{#splitline{function and Delaunay triangles}{interpolation}}",
   100, -hr, hr);
   auto h3 = new TH1D("h3",
   "#splitline{Difference between Original}{function and Minuit fit}",
   500, -hr, hr);

   f2->SetParameters(0.5,1.5);
   dt->Fit(f2);
   auto fit2 = (TF2*)dt->FindObject("f2");

   f2->SetParameters(1,1);

   for (int N=0; N<np; N++) {
      f2->GetRandom2(x,y);
      // Generate a random number in [-e,e]
      rnd = 2*r.Rndm()*e-e;
      z = f2->Eval(x,y)*(1+rnd);
      h1->Fill(f2->Eval(x,y)-z);
      z = dt->Interpolate(x,y);
      h2->Fill(f2->Eval(x,y)-z);
      z = fit2->Eval(x,y);
      h3->Fill(f2->Eval(x,y)-z);
   }

   c->cd(1);
   gStyle->SetHistTopMargin(0);
   dt->SetTitle("Graph2D with P0");
   dt->Draw("PCOL");

   c->cd(2);
   dt->SetTitle("Graph2D with PCOL");
   gStyle->SetHistTopMargin(0);
   dt->Draw("P0");

   c->cd(3);
   dt->SetMargin(0.1);
   dt->SetFillColor(36);
   dt->SetTitle("Graph2D produced with Delaunay interpolation");
   dt->Draw("surf4");

   c->cd(4);
   dt->SetTitle("Graph2D produced with Delaunay interpolation");
   dt->Draw("TRI2");


   c->cd(5);
   //dt->SetTitle("Graph2D with CONT");
   dt->Draw("CONT");
   TH2D* Dupa = dt->GetHistogram();
  //Dupa->SetTitle("Histogram");
   Dupa->Draw("colz");


   auto graph = new TGraph2D();
   Dupa->Smooth();
   // Loop over all bins of the histogram
   for (int ix = 1; ix <= Dupa->GetNbinsX(); ++ix) {
     for (int iy = 1; iy <= Dupa->GetNbinsY(); ++iy) {
       // Get the content of the bin
       double content = Dupa->GetBinContent(ix, iy);

       // Get the bin center coordinates
       double x = Dupa->GetXaxis()->GetBinCenter(ix);
       double y = Dupa->GetYaxis()->GetBinCenter(iy);

       // Add a point to the TGraph2D
       int pointIndex = graph->GetN();
       graph->SetPoint(pointIndex, x, y, content);
     }
   }


   c->cd(6);
   graph->SetTitle("Graph2D after conversion");
   graph->Draw("TRI2");

   /*
   h1->SetFillColor(47);
   h2->SetFillColor(38);
   h3->SetFillColor(29);

   c->cd(2); h1->Fit("gaus","Q") ; h1->Draw();
   c->cd(4); h2->Fit("gaus","Q") ; h2->Draw();
   c->cd(6); h3->Fit("gaus","Q") ; h3->Draw();
   */
   c->cd();
}
