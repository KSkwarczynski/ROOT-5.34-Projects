#include <sstream>
#include <iomanip>
#include <TROOT.h>
#include <vector>
#include <sstream>
#include <TH1F.h>
#include <TFile.h>
#include <TCanvas.h>

void PlotsFromCanvas()
{
    TFile* File = TFile::Open("histograms.root");
    
    //TDirectory* dir = File->GetDirectory("Directory"); //Dealing when histograms are in directory
    //TCanvas *Canvas4 = (TCanvas*)dir->Get("Canvas4");
    
    TCanvas *Canvas2 = (TCanvas*)File->Get("Canvas2");
    
    TGraphAsymmErrors *gr1 = (TGraphAsymmErrors*)Canvas2->GetPrimitive("Graph_from_sample2_R7mc0_all_22_23");
    Canvas2->Clear();
    //Canvas2->Draw();
    
    //gr1->GetXaxis()->SetTitle("TESTUJEMY");
    //gr1->Draw("p");
    
    TCanvas *Canvas3 = (TCanvas*)File->Get("Canvas3");
    
    TGraphAsymmErrors *gr2 = (TGraphAsymmErrors*)Canvas3->GetPrimitive("Graph_from_sample2_R7mc0_all_26_27");
    Canvas3->Clear();
    //Canvas3->Draw();
    
    //gr2->Draw("p SAME");
    
    TCanvas *Canvas4 = (TCanvas*)File->Get("Canvas4");
    
    TH2D *h1 = (TH2D*)Canvas4->GetPrimitive("sample2_R7mc0_all_30_31");
    h1->GetXaxis()->SetTitle("h1");
    Canvas4->Clear();
    //Canvas4->Draw();

    //h1->Draw("COLZ");
    
    TH2D *h2 = (TH2D*)Canvas5->GetPrimitive("sample2_R7mc0_all_32_33");
    h2->GetXaxis()->SetTitle("h2");
    //h2->Add(h1,-1);
    Canvas5->Clear();
    //Canvas5->Draw();

    //h2->Draw("COLZ");
    /*
    TMultiGraph *mg=new TMultiGraph();
    
    mg->Add(gr1);
    gr1->SetLineColor(kRed);
    gr1->SetLineWidth(2);
    gr1->SetMarkerColor(kRed);
    
    mg->Add(gr2);
    gr2->SetLineColor(kBlue);
    gr2->SetLineWidth(2);
    gr2->SetMarkerColor(kBlue);

    mg->Draw("p");
    
    auto legend = new TLegend(0.1,0.7,0.48,0.9);
    legend->AddEntry(gr1,"truelepton_costheta","pe");
    legend->AddEntry(gr2,"truepi_costheta","pe");
    legend->Draw();
    */
    Canvas = new TCanvas("Canvas","CanvasNowy",10,10,800,600);
    TH2F *h3 = (TH2F*)(h2->Clone("h3"));
    h3->GetXaxis()->SetTitle("Ja zyje");
    h3->GetZaxis()->SetRangeUser(0., 100.);
    h3->Add(h1,-1);
    
    h3->Draw("COLZ");
    h3->GetZaxis()->SetRangeUser(0., 60.);
   // h3->SetMaximum(400);
////////////////BONUS////////////
//How to get inforamtion about plot in Canvas
   //TList *p = Canvas4->GetListOfPrimitives(); //way to get primitive
    //p->Print();    
    
    //OR
    
    //Canvas2->ls();
    
}
