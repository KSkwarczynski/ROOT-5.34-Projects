#include <fstream>
#include <iostream>
#include <iomanip>
#include <TMath.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <iomanip>
#include <TColor.h>
#include <TEfficiency.h>
#include <TF1.h>
#include <TFitResultPtr.h>
#include "TBinomialEfficiencyFitter.h"
#include "SetStyle.C"
using namespace std;

void setRange(TEfficiency* eff, TCanvas* c){
  c->Update();
  eff->GetPaintedGraph()->GetYaxis()->SetRangeUser(0,1.0);
}

void setOverlayColor(TEfficiency* effData, TEfficiency* effMc,TString plotTitle, TCanvas* c){

  cout << plotTitle << endl;
  effData->Draw();
  c->Update();
  TGraphAsymmErrors* tmgData = effData->GetPaintedGraph();
  tmgData->SetMarkerSize(20);
  tmgData->SetMarkerSize(0.6);
  tmgData->SetMarkerColor(kRed);
  tmgData->SetLineColor(kRed);
  tmgData->SetMinimum(0.0);
  tmgData->SetMaximum(1.0);

  effMc->Draw();
  c->Update();
  TGraphAsymmErrors* tmgMc = effMc->GetPaintedGraph();
  tmgMc->SetMarkerStyle(21);
  tmgMc->SetMarkerSize(0.6);
  tmgMc->SetMarkerColor(kBlue);
  tmgMc->SetLineColor(kBlue);
  tmgMc->SetMinimum(0.0);
  tmgMc->SetMaximum(1.0);


  c->Clear();
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(tmgData);
  mg->Add(tmgMc);
  mg->Draw("ap");
  mg->SetTitle(plotTitle);
  c->Update();


  // Change the axis limits
  gPad->Modified();
  //mg->GetXaxis()->SetLimits(300,1100);
  mg->SetMinimum(0.);
  mg->SetMaximum(1.); 
  mg->SetTitle(plotTitle);
  c->Modified();
  //c->BuildLegend();


  TLegend *legend=new TLegend(0.65,0.65,0.85,0.85);
  //legend->SetTextFont(72);
  legend->SetTextSize(0.05);
  legend->SetFillColor(0); 
  legend->AddEntry(tmgData,"Data","l");
  legend->AddEntry(tmgMc,"MC","l");
  legend->Draw();

}

double QuadError( double R , double f1 , double f2 ){
  cout << "R="<<R <<", f1=" << f1 << ", f2=" << f2 << endl;
  return R*TMath::Sqrt( f1*f1 + f2*f2 );
}

void DrawNormalizedRatioTH1(TEfficiency* dataEff, TEfficiency* mcEff, TString plotTitle, TString fileName, TCanvas* c, TString particle, int doFit=0){

  c->Clear();
  dataEff->Draw();
  c->Update();
  TGraphAsymmErrors* tmgData = dataEff->GetPaintedGraph();
  double* xdata = tmgData->GetX();
  double* ydata = tmgData->GetY();
  double* yehidata = tmgData->GetEYhigh();
  double* yelodata = tmgData->GetEYlow();

  c->Clear();
  mcEff->Draw();
  c->Update();
  TGraphAsymmErrors* tmgMc = mcEff->GetPaintedGraph();
  double* xmc = tmgMc->GetX();
  double* ymc = tmgMc->GetY();
  double* yehimc = tmgMc->GetEYhigh();
  double* yelomc = tmgMc->GetEYlow();

  //should be same size between data and mc
  int npoints = tmgMc->GetN();
  double* yratio = 0;
  double* yehiratio =0;
  double* yeloratio =0;
  yratio = new double[npoints];
  yehiratio = new double[npoints];
  yeloratio = new double[npoints];
  xel = new double[npoints];
  xeh = new double[npoints];

  float err=0;
  for(int n =0; n < npoints; n++){
    cout << n <<"("<<xdata[n]<<") "<< "=" << ydata[n]/ymc[n] << endl;
    yratio[n] = ydata[n]/ymc[n];
    err = QuadError( yratio[n] , yehidata[n]/ydata[n] , yehimc[n]/ymc[n] );
    yehiratio[n]=err;
    err = QuadError( yratio[n] , yelodata[n]/ydata[n] , yelomc[n]/ymc[n] );
    yeloratio[n]=err;
    xel[n]=0;
    xeh[n]=0;
  }

  TGraphAsymmErrors* ratio = new TGraphAsymmErrors(npoints,xdata,yratio,xel,xeh,yeloratio, yehiratio);

  ratio->SetMaximum(1.5);
  ratio->SetMinimum(0.5);
  ratio->SetTitle(plotTitle);
  ratio->Draw("ap");
  c->SetGridy(1);
  if(doFit==1){
    //TODO
    string JakisTytul = plotTitle.Data();
    if (JakisTytul.find("Cos(") != string::npos)
    {
        if(particle=="proton")
        {
            TF1 *f1 = new TF1("f1","pol0",-1,1);
        }
        else if(particle=="pionM" || particle=="pionP")
        {
            TF1 *f1 = new TF1("f1","pol0",-1,1);
        }
    }
    else
    {
        if(particle=="proton")
        {
            TF1 *f1 = new TF1("f1","pol0",400,1000);
        }
        else if(particle=="pionM" || particle=="pionP")
        {
            TF1 *f1 = new TF1("f1","pol0",100,300);
        }
    }
    
    
    f1->SetLineColor(kRed);
    f1->SetLineStyle(2);
    TFitResultPtr myFit = ratio->Fit("f1", "R");
  }

  c->Print(fileName);
  //c->Print(fileName.c_str());

  c->SetGridy(0);
  delete []yratio;
  delete []yehiratio;
  delete []yeloratio;
  delete []xel;
  delete []xeh;

}


void DrawNormalizedRatio(TEfficiency* dataEff, TEfficiency* mcEff, TString plotTitle, TString fileName, TCanvas* c){

  //clone data hist
  dataEff->Draw("colz");
  c->Update();
  TH2F* hData = dataEff->GetPaintedHistogram();

  //clone mc hist
  mcEff->Draw("colz");
  c->Update();
  TH2F* hMC =  mcEff->GetPaintedHistogram();

  //form normalized ratio of data/mc 
  hData->Divide(hMC);

  hData->SetTitle(plotTitle);
  hData->SetStats(0);
  hData->SetMinimum(0.50);
  hData->SetMaximum(1.50);
  hData->Draw("colz");

  c->Print(fileName);

}


//inputfile = root file with standard calib plots
//tag = category for naming files

void plotEfficiencyRatiosV3(string inputDataFile, string inputMcFile,  string particle){
    //WARNING Setting style of plots
    SetT2Kstyl();
        
    
    TString particlePlot;
    int ABINS=9; //angle bins

    int PMIN=75;
    int PMAX=1025;
    int PBINS=(PMAX-PMIN)/25;//25MeV bins

    int MMIN=0;//momentum min, single component
    int MMAX=1700;//momentum max, single component
    int MBINS=(MMAX-MMIN)/100;//100 MeV bins for these plots

    int EMIN=100;
    int EMAX=1870;
    int EBINS=(EMAX-EMIN)/50;

  if(particle=="proton"){
    PMIN=375;
    PMAX=1025;
    PBINS=(PMAX-PMIN)/50;//25MeV bins

    MMIN=0;//momentum min, single component
    MMAX=1700;//momentum max, single component
    MBINS=(MMAX-MMIN)/100;//100 MeV bins for these plots

    EMIN=1000;
    EMAX=1400;
    EBINS=(EMAX-EMIN)/50;
    particlePlot="proton";
  }
  if(particle=="pionM"){
    PMIN=75;
    PMAX=375;
    PBINS=(PMAX-PMIN)/50;//25MeV bins

    MMIN=0;//momentum min, single component
    MMAX=375;//momentum max, single component
    MBINS=(MMAX-MMIN)/50;//100 MeV bins for these plots

    EMIN=150;
    EMAX=350;
    EBINS=(EMAX-EMIN)/50;
    particlePlot="#pi-";
  }
    else if(particle=="pionP"){
    PMIN=75;
    PMAX=375;
    PBINS=(PMAX-PMIN)/50;//25MeV bins

    MMIN=0;//momentum min, single component
    MMAX=375;//momentum max, single component
    MBINS=(MMAX-MMIN)/50;//100 MeV bins for these plots

    EMIN=150;
    EMAX=350;
    EBINS=(EMAX-EMIN)/50;
    particlePlot="#pi+";
  }

  //Get data histograms
  gStyle->SetOptStat("e");
  TFile* datafile = TFile::Open(inputDataFile.c_str(),"READ");
  TEfficiency*  data_eMomVsCosThetaEfficiencyNcge1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNcge1");
  TEfficiency*  data_eMomVsCosThetaEfficiencyNge1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNge1");
  TEfficiency*  data_eMomVsCosThetaEfficiencyNce1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNce1");
  TEfficiency*  data_eMomVsCosThetaEfficiencyNe1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNe1");

  TEfficiency*  data_eMomEfficiencyNge1=(TEfficiency*)datafile->Get("eMomEfficiencyNge1");
  TEfficiency*  data_eMomEfficiencyNe1=(TEfficiency*)datafile->Get("eMomEfficiencyNe1");
  TEfficiency*  data_eMomEfficiencyNcge1=(TEfficiency*)datafile->Get("eMomEfficiencyNcge1");
  TEfficiency*  data_eMomEfficiencyNce1=(TEfficiency*)datafile->Get("eMomEfficiencyNce1");

  TEfficiency*  data_eCosThetaEfficiencyNge1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNge1");
  TEfficiency*  data_eCosThetaEfficiencyNe1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNe1");
  TEfficiency*  data_eCosThetaEfficiencyNcge1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNcge1");
  TEfficiency*  data_eCosThetaEfficiencyNce1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNce1");
  
  //TODO
   TEfficiency*  data_eCosHmntStubEfficiencyNge1=(TEfficiency*)datafile->Get("eCosHmntStubEfficiencyNge1");
   TEfficiency*  data_eCosHmntStubGaussEfficiencyNge1=(TEfficiency*)datafile->Get("eCosHmntStubGaussEfficiencyNge1");
    
  //Get MC histograms
  TFile* datafile = TFile::Open(inputMcFile.c_str(),"READ");
  TEfficiency*  mc_eMomVsCosThetaEfficiencyNcge1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNcge1");
  TEfficiency*  mc_eMomVsCosThetaEfficiencyNge1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNge1");
  TEfficiency*  mc_eMomVsCosThetaEfficiencyNce1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNce1");
  TEfficiency*  mc_eMomVsCosThetaEfficiencyNe1=(TEfficiency*)datafile->Get("eMomVsCosThetaEfficiencyNe1");

  TEfficiency*  mc_eMomEfficiencyNge1=(TEfficiency*)datafile->Get("eMomEfficiencyNge1");
  TEfficiency*  mc_eMomEfficiencyNe1=(TEfficiency*)datafile->Get("eMomEfficiencyNe1");
  TEfficiency*  mc_eMomEfficiencyNcge1=(TEfficiency*)datafile->Get("eMomEfficiencyNcge1");
  TEfficiency*  mc_eMomEfficiencyNce1=(TEfficiency*)datafile->Get("eMomEfficiencyNce1");

  TEfficiency*  mc_eCosThetaEfficiencyNge1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNge1");
  TEfficiency*  mc_eCosThetaEfficiencyNe1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNe1");
  TEfficiency*  mc_eCosThetaEfficiencyNcge1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNcge1");
  TEfficiency*  mc_eCosThetaEfficiencyNce1=(TEfficiency*)datafile->Get("eCosThetaEfficiencyNce1");
  
  //TODO
   TEfficiency*  mc_eCosHmntStubEfficiencyNge1=(TEfficiency*)datafile->Get("eCosHmntStubEfficiencyNge1");
   TEfficiency*  mc_eCosHmntStubGaussEfficiencyNge1=(TEfficiency*)datafile->Get("eCosHmntStubGaussEfficiencyNge1");
   
   
  TString filePath="./Efficiencies/" + particle + "/ratios/";

  TCanvas* c = new TCanvas("c0","c0",0, 0, 800,630);
  TString plotTitle="Momentum Vs Cos(#theta),N_{c}#geq1, data/MC ratio ("+particle+")";
  TString fileName ="ratio_MomVsCosThetaNcge1_"+particle+".pdf";
  TString file = filePath+fileName;
  DrawNormalizedRatio(data_eMomVsCosThetaEfficiencyNcge1, mc_eMomVsCosThetaEfficiencyNcge1,plotTitle,file,c); 

  plotTitle="Momentum Vs Cos(#theta),N_{c}=1, data/MC ratio ("+particle+")";
  fileName ="ratio_MomVsCosThetaNce1_"+particle+".pdf";
  file = filePath+fileName;
  DrawNormalizedRatio(data_eMomVsCosThetaEfficiencyNce1, mc_eMomVsCosThetaEfficiencyNce1,plotTitle,file,c); 

  plotTitle="Momentum Vs Cos(#theta),N#geq1, data/MC ratio ("+particle+")";
  fileName ="ratio_MomVsCosThetaNge1_"+particle+".pdf";
  file = filePath+fileName;
  DrawNormalizedRatio(data_eMomVsCosThetaEfficiencyNge1, mc_eMomVsCosThetaEfficiencyNge1,plotTitle,file,c); 

  plotTitle="Momentum Vs Cos(#theta),N=1, data/MC ratio ("+particle+")";
  fileName ="ratio_MomVsCosThetaNe1_"+particle+".pdf";
  file = filePath+fileName;
  DrawNormalizedRatio(data_eMomVsCosThetaEfficiencyNe1, mc_eMomVsCosThetaEfficiencyNe1,plotTitle,file,c); 

  //////
  //////
  TString filePath="./Efficiencies/Overlays/";

  TString plotTitle="Efficiency Vs Cos(#theta), "+particlePlot+";Cos(#theta);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosThetaEfficiencyNge1, mc_eCosThetaEfficiencyNge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNge1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Cos(#theta), N = 1 ("+particle+");Cos(#theta);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosThetaEfficiencyNe1, mc_eCosThetaEfficiencyNe1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNe1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Cos(#theta), N_{c} #geq 1 ("+particle+");Cos(#theta);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosThetaEfficiencyNcge1, mc_eCosThetaEfficiencyNcge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNcge1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Cos(#theta), N_{c} = 1 ("+particle+");Cos(#theta);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosThetaEfficiencyNce1, mc_eCosThetaEfficiencyNce1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNce1_DataMC_Overlay.pdf";
  c->Print(fileName);
  //////
  //////
  TString filePath="./Efficiencies/Overlays/";

  TString plotTitle="Efficiency Vs Momentum, "+particlePlot+";P(MeV/c);Efficiency";
  c->Clear();
  setOverlayColor(data_eMomEfficiencyNge1, mc_eMomEfficiencyNge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsMomNge1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Momentum, N = 1 ("+particle+");P(MeV/c);Efficiency";
  c->Clear();
  setOverlayColor(data_eMomEfficiencyNe1, mc_eMomEfficiencyNe1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsMomNe1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Momentum, N_{c} #geq 1 ("+particle+");P(MeV/c);Efficiency";
  c->Clear();
  setOverlayColor(data_eMomEfficiencyNcge1, mc_eMomEfficiencyNcge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsMomNcge1_DataMC_Overlay.pdf";
  c->Print(fileName);

  TString plotTitle="Efficiency Vs Momentum, N_{c} = 1 ("+particle+");P(MeV/c);Efficiency";
  c->Clear();
  setOverlayColor(data_eMomEfficiencyNce1, mc_eMomEfficiencyNce1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsMomNce1_DataMC_Overlay.pdf";
  c->Print(fileName);
/////////
  //TODO
  TString plotTitle="Efficiency Vs Cos(#theta HMNT Stub), "+particlePlot+";Cos(#theta HMNT Stub);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosHmntStubEfficiencyNge1, mc_eCosHmntStubEfficiencyNge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosHmntStubNge1_DataMC_Overlay.pdf";
  c->Print(fileName);
  
  TString plotTitle="Efficiency Vs Cos(#theta HMNT Stub), "+particlePlot+";Cos(#theta HMNT Stub);Efficiency";
  c->Clear();
  setOverlayColor(data_eCosHmntStubGaussEfficiencyNge1, mc_eCosHmntStubGaussEfficiencyNge1,plotTitle, c);
  fileName = filePath+particle.c_str()+"_eEffVsCosHmntStubGaussNge1_DataMC_Overlay.pdf";
  c->Print(fileName);
  
  //
  TString filePath="./Efficiencies/"+particle+"/ratios/";
  //WARNING
  gStyle->SetOptTitle(0);
  
  int FIT=1;
  plotTitle="Data/MC Ratio, Efficiency Vs Momentum, N_{c} = 1 ("+particle+");P(MeV/c);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsMomNce1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eMomEfficiencyNce1, mc_eMomEfficiencyNce1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Momentum, N_{c} #geq 1 ("+particle+");P(MeV/c);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsMomNcge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eMomEfficiencyNcge1, mc_eMomEfficiencyNcge1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Momentum, "+particlePlot+";P(MeV/c);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsMomNge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eMomEfficiencyNge1, mc_eMomEfficiencyNge1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Momentum, N = 1 ("+particle+");P(MeV/c);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsMomNe1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eMomEfficiencyNe1, mc_eMomEfficiencyNe1,plotTitle,fileName,c,particle,FIT); 
///
  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta), N_{c} = 1 ("+particle+");Cos(#theta);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNce1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosThetaEfficiencyNce1, mc_eCosThetaEfficiencyNce1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta), N_{c} #geq 1 ("+particle+");Cos(#theta);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNcge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosThetaEfficiencyNcge1, mc_eCosThetaEfficiencyNcge1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta), "+particlePlot+";Cos(#theta);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosThetaEfficiencyNge1, mc_eCosThetaEfficiencyNge1,plotTitle,fileName,c,particle,FIT); 

  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta), N = 1 ("+particle+");Cos(#theta);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eEffVsCosThetaNe1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosThetaEfficiencyNe1, mc_eCosThetaEfficiencyNe1,plotTitle,fileName,c,particle,FIT); 
  //TODO  
  
  cout<<" HERE STARTS PART FOR TN TABLE"<<endl;
  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta HMNT Stub), "+particlePlot+";Cos(#theta HMNT Stub);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eCosHmntStubEfficiencyNge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosHmntStubEfficiencyNge1, mc_eCosHmntStubEfficiencyNge1,plotTitle,fileName,c,particle,FIT); 
  
  plotTitle="Data/MC Ratio, Efficiency Vs Cos(#theta HMNT Stub), "+particlePlot+";Cos(#theta HMNT Stub);Ratio";
  c->Clear();
  fileName = filePath+particle.c_str()+"_eCosHmntStubGaussEfficiencyNge1_DataMC_Ratio.pdf";
  DrawNormalizedRatioTH1(data_eCosHmntStubGaussEfficiencyNge1, mc_eCosHmntStubGaussEfficiencyNge1,plotTitle,fileName,c,particle,FIT);
  
  
  //TODO
    cout<<" Table for "<<endl;
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(1)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(1)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(1)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(1)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(1)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(1)<<endl;
    
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(2)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(2)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(2)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(2)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(2)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(2)<<endl;
    
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(3)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(3)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(3)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(3)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(3)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(3)<<endl;
    
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(4)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(4)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(4)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(4)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(4)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(4)<<endl;
    
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(5)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(5)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(5)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(5)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(5)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(5)<<endl;
    
    cout<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(6)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(6)<<" & "<<mc_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(6)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiency(6)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorUp(6)<<" & "<<data_eCosHmntStubGaussEfficiencyNge1->GetEfficiencyErrorLow(6)<<endl;
      
  
}
