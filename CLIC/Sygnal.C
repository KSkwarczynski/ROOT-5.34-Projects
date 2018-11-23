#define Sygnal_cxx

#include "Sygnal.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>

#include<iostream>
#include<ctime>
#include<cstdlib>
//tworzenie histogramow

TH1F *Mqhist;
TH1F *Mthist;

TH1F *M1hist;
TH1F *M2hist;
TH1F *M3hist;

TH1F *E1hist;
TH1F *E2hist;
TH1F *E3hist;

TH1F *PT1hist;
TH1F *PT2hist;
TH1F *PT3hist;

TH1F *PTghist;
TH1F *Eghist;
TH1F *Mghist;

TH1F *PTkhist;
TH1F *Ekhist;

TH2F *PXYhist;
TH2F *PTEhist;
TH2F *MEhist;
TH2F *PTEghist;

TRandom3 *rand;
TFile *plik;
void Sygnal::Begin(TTree * /*tree*/)
{

    TString option = GetOption();
   //dalsza deklracja histgramow

   if( gDirectory->FindObject("Mqhist")!=NULL) gDirectory->Delete("Mqhist");
   Mqhist = new TH1F("Mqhist","Brakujaca masa",100, -10., 400.);

   if( gDirectory->FindObject("Mthist")!=NULL) gDirectory->Delete("Mthist");
   Mthist = new TH1F("Mthist","Masa niezmiennicza kwarku t",100, -10., 400.);
/////////////////////////////////////////////////////////////////////////////////////////////////

   if( gDirectory->FindObject("M1hist")!=NULL) gDirectory->Delete("M1hist");
   M1hist = new TH1F("M1hist","Masa niezmiennicza bozonu W",100, - 20., 400.);

   if( gDirectory->FindObject("M2hist")!=NULL) gDirectory->Delete("M2hist");
   M2hist = new TH1F("M2hist","Masa niezmiennicza kwarku b",100, -20., 400.);

   if( gDirectory->FindObject("M3hist")!=NULL) gDirectory->Delete("M3hist");
   M3hist = new TH1F("M3hist","Masa niezmiennicza wszystkich kwarkow",100, -20., 400.);
/////////////////////////////////////////////////////////////////////////////////////////////////

   if( gDirectory->FindObject("E1hist")!=NULL) gDirectory->Delete("E1hist");
   E1hist = new TH1F("E1hist","Energia bozonu W",100, - 20., 400.);

   if( gDirectory->FindObject("E2hist")!=NULL) gDirectory->Delete("E2hist");
   E2hist = new TH1F("E2hist","Energia kwarku b",100, -20., 400.);

   if( gDirectory->FindObject("E3hist")!=NULL) gDirectory->Delete("E3hist");
   E3hist = new TH1F("E3hist","Energia wszystkich kwarkow",100, -20., 400.);
/////////////////////////////////////////////////////////////////////////////////////////////////

   if( gDirectory->FindObject("PT1hist")!=NULL) gDirectory->Delete("PT1hist");
   PT1hist = new TH1F("PT1hist","Ped poprzeczny bozonu W",100, - 20., 400.);

   if( gDirectory->FindObject("PT2hist")!=NULL) gDirectory->Delete("PT2hist");
   PT2hist = new TH1F("PT2hist","Ped poprzeczny kwarku b",100, -20., 400.);

   if( gDirectory->FindObject("PT3hist")!=NULL) gDirectory->Delete("PT3hist");
   PT3hist = new TH1F("PT3hist","Ped poprzeczny kwarkow",100, -20., 400.);
///////////////////////////////////////////////////////////////////////////////////////////////////

    if( gDirectory->FindObject("PTghist")!=NULL) gDirectory->Delete("PTghist");
   PTghist = new TH1F("PTghist","Ped poprzeczny kwarkow NB",100, - 20., 400.);

   if( gDirectory->FindObject("Eghist")!=NULL) gDirectory->Delete("Eghist");
   Eghist = new TH1F("Eghist","Energia kwarkow NB",100, -20., 400.);

   if( gDirectory->FindObject("Mghist")!=NULL) gDirectory->Delete("Mghist");
   Mghist = new TH1F("Mghist","Masa kwarkow NB",100, -20., 400.);

///////////////////////////////////////////////////////////////////////////////////////////////////

    if( gDirectory->FindObject("PTkhist")!=NULL) gDirectory->Delete("PTkhist");
   PTkhist = new TH1F("PTkhist","Ped poprzeczny trzeciego kwarka",100, - 20., 400.);

   if( gDirectory->FindObject("Ekhist")!=NULL) gDirectory->Delete("Ekhist");
   Ekhist = new TH1F("Ekhist","Energia trzeciego kwarka",100, -20., 400.);

/////////////////////////////////////////////////////////////////////////////////////////////////

   if( gDirectory->FindObject("PXYhist")!=NULL) gDirectory->Delete("PXYhist");
   PXYhist = new TH2F("PXYhist","Ped X i Y bozonu wszystkich kwarków",100, -200., 200.,100., -200., 200.);

   if( gDirectory->FindObject("PTEhist")!=NULL) gDirectory->Delete("PTEhist");
   PTEhist = new TH2F("PTEhist","Ped T i energia wszystkich kwarków",100, -20., 400.,100., -20., 400.);

   if( gDirectory->FindObject("MEhist")!=NULL) gDirectory->Delete("MEhist");
   MEhist = new TH2F("MEhist","Masa i energia wszystkich kwarków",100, -20., 400.,100., -20., 400.);

   if( gDirectory->FindObject("PTEghist")!=NULL) gDirectory->Delete("PTEghist");
   PTEghist = new TH2F("PTEghist","Ped T i energia trzeciego kwarków",100, -20., 400.,100., -20., 400.);

   if( gDirectory->FindObject("rand")!=NULL) gDirectory->Delete("rand");
   rand = new TRandom3(0);

   if( gDirectory->FindObject("plik")!=NULL) gDirectory->Delete("plik");
   plik = new TFile("wykresy.root","RECREATE");
}

void Sygnal::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}

Bool_t Sygnal::Process(Long64_t entry)
{
   //wczytanie drzewa
   b_header->GetEntry(entry);
   b_Status->GetEntry(entry);
   b_PDGcode->GetEntry(entry);
   b_Px->GetEntry(entry);
   b_Py->GetEntry(entry);
   b_Pz->GetEntry(entry);
   b_E->GetEntry(entry);
   b_Minv->GetEntry(entry);
   b_FirstDaughter->GetEntry(entry);
   b_LastDaughter->GetEntry(entry);


   // Loop over particles
////////////////deklaracja zmiennyvch////
   double px=0; double py=0; double pz=0; double pT=0; double p=0; double kosinus=0; double sigma=0; double Energy=0; double cosinus=0;

   double pxq=0; double pyq=0; double pzq=0; double eq=0;

   int nn=0;

   double pxn=0; double pyn=0; double pzn=0; double en=0; ;

   double px1=0; double py1=0; double pz1=0; double e1=0;

   double px2=0; double py2=0; double pz2=0; double e2=0;

   double px3=0; double py3=0; double pz3=0; double e3=0;

   double px4=0; double py4=0; double pz4=0; double e4=0; double sigma4=0;

   double pxt=0; double pyt=0; double pzt=0; double et=0;

   int n1=0; int n2=0; int n3=0; int n4=0;

   int licznikB=0; double zapachB[10]; double energiaB[10]; double pedxB[10]; double pedyB[10]; double pedzB[10];

   int licznikNB=0; double zapachNB[10]; double energiaNB[10]; double pedxNB[10]; double pedyNB[10]; double pedzNB[10];

   double skalowanie=0;

   double pxa=0; double pya=0; double pza=0; double ea=0;

   double pxb=0; double pyb=0; double pzb=0; double eb=0;

   double pxc=0; double pyc=0; double pzc=0; double ec=0;

   double pxnb=0; double pynb=0; double pznb=0; double enb=0;

   double pxg=0; double pyg=0; double pzg=0; double eg=0; int g=0;

/////petla po danych////
for(int ipar=0;ipar<header_Npar;ipar++)
     {
       int apdg = abs(PDGcode[ipar]);
 	   int pdg = PDGcode[ipar];
 	   px=Px[ipar];
	   py=Py[ipar];
	   pz=Pz[ipar];
	   pT=sqrt(px*px+py*py);
	   p=sqrt(px*px+py*py+pz*pz);
       kosinus=abs(pz/p);


if(Status[ipar]!=1)continue;

    if( (apdg == 11 || apdg == 13 || apdg == 15) && (kosinus <=0.995) )
	 {

//////////dokladnosc detekytora///////
        if( E[ipar]<= 100){ sigma4 =  50/sqrt(E[ipar]) ; }

        if( E[ipar]>100 ){sigma4 = 5 ;}

       en = rand->Gaus( E[ipar] , sigma4 );
       skalowanie=en/E[ipar];
       pxn=Px[ipar]*skalowanie;
	   pyn=Py[ipar]*skalowanie;
	   pzn=Pz[ipar]*skalowanie;
       cosinus=abs(pzn/( sqrt(pxn*pxn+pyn*pyn+pzn*pzn) ) ) ;
	  if(cosinus <=0.995){nn++;}
	 }

    if( (apdg <= 6 ) && (kosinus <=0.975) )
	 {
	   px4=Px[ipar];
	   py4=Py[ipar];
	   pz4=Pz[ipar];
//////////dokladnosæ detekytora///////
        if( E[ipar]<= 100){ sigma4 =  50/sqrt(E[ipar]) ; }

        if( E[ipar]>100 ){sigma4 = 5 ;}

       e4 = rand->Gaus( E[ipar] , sigma4 );
       skalowanie=e4/E[ipar];
////////////////////////warunki rozpoznawiania////////////////////////
           if(apdg<=3){
                    double propability=rand->Uniform(100);
                        if(propability <=0.2){
                            zapachB[licznikB]=5;

                            energiaB[licznikB]=e4;
                            pedxB[licznikB]=px4*skalowanie;
                            pedyB[licznikB]=py4*skalowanie;
                            pedzB[licznikB]=pz4*skalowanie;

                            licznikB++;
}
                        if(propability >0.2){
                            zapachNB[licznikNB]=apdg;

                            energiaNB[licznikNB]=e4;
                            pedxNB[licznikNB]=px4*skalowanie;
                            pedyNB[licznikNB]=py4*skalowanie;
                            pedzNB[licznikNB]=pz4*skalowanie;

                            licznikNB++;
                                }
                        }
            if(apdg==4){
                    double propability=rand->Uniform(100);
                        if(propability <=2){
                            zapachB[licznikB]=5;

                            energiaB[licznikB]=e4;
                            pedxB[licznikB]=px4*skalowanie;
                            pedyB[licznikB]=py4*skalowanie;
                            pedzB[licznikB]=pz4*skalowanie;

                            licznikB++;
                                }
                        if(propability >2){
                            zapachNB[licznikNB]=apdg;

                            energiaNB[licznikNB]=e4;
                            pedxNB[licznikNB]=px4*skalowanie;
                            pedyNB[licznikNB]=py4*skalowanie;
                            pedzNB[licznikNB]=pz4*skalowanie;

                            licznikNB++;
                                }
                        }
            if(apdg==5){
                    double propability=rand->Uniform(100);
                        if(propability <=70){
                             zapachB[licznikB]=5;

                            energiaB[licznikB]=e4;
                            pedxB[licznikB]=px4*skalowanie;
                            pedyB[licznikB]=py4*skalowanie;
                            pedzB[licznikB]=pz4*skalowanie;

                            licznikB++;
                                }
                        if(propability >70){
                            zapachNB[licznikNB]=apdg;

                            energiaNB[licznikNB]=e4;
                            pedxNB[licznikNB]=px4*skalowanie;
                            pedyNB[licznikNB]=py4*skalowanie;
                            pedzNB[licznikNB]=pz4*skalowanie;

                            licznikNB++;
                        }
                    }
            n4++;
            }
     }

/////////sprawdzanie kombinacji kwarkowej/////////
	   pxa=pedxNB[0]+pedxNB[1];
	   pya=pedyNB[0]+pedyNB[1];
	   pza=pedzNB[0]+pedzNB[1];
       ea =energiaNB[0]+energiaNB[1];

	   pxb=pedxNB[0]+pedxNB[2];
	   pyb=pedyNB[0]+pedyNB[2];
	   pzb=pedzNB[0]+pedzNB[2];
       eb =energiaNB[0]+energiaNB[2];

	   pxc=pedxNB[1]+pedxNB[2];
	   pyc=pedyNB[1]+pedyNB[2];
	   pzc=pedzNB[1]+pedzNB[2];
       ec =energiaNB[1]+energiaNB[2];
/*
       double ma=sqrt(ea*ea-pxa*pxa-pya*pya-pza*pza);
       double mb=sqrt(eb*eb-pxb*pxb-pyb*pyb-pzb*pzb);
       double mc=sqrt(ec*ec-pxc*pxc-pyc*pyc-pzc*pzc);
        if(ma>=90 || ma<=70){ma=0; pxa=0; pya=0; pza=0; ea=0;}
        if(mb>=90 || mb<=70){mb=0; pxb=0; pyb=0; pzb=0; eb=0;}
        if(mc>=90 || mc<=70){mc=0; pxc=0, pyc=0; pzc=0; ec=0;}
        double m1=ma+mb+mc;
        e1=ea+eb+ec; px1=pxa+pxb+pxc; py1=pya+pyb+pyc; pz1=pza+pzb+pzc;
*/
       double ma=sqrt(ea*ea-pxa*pxa-pya*pya-pza*pza);
       double mb=sqrt(eb*eb-pxb*pxb-pyb*pyb-pzb*pzb);
       double mc=sqrt(ec*ec-pxc*pxc-pyc*pyc-pzc*pzc);

        if(ma<=90 && ma>=70){pxg=pedxNB[2]; pyg=pedyNB[2]; pzg=pedzNB[2]; eg=energiaNB[2]; g++; px1=pxa; py1=pya; pz1=pza; e1=ea;}
        if(mb<=90 && mb>=70){pxg=pedxNB[1]; pyg=pedyNB[1]; pzg=pedzNB[1]; eg=energiaNB[1]; g++; px1=pxb; py1=pyb; pz1=pzb; e1=eb;}
        if(mc<=90 && mc>=70){pxg=pedxNB[0]; pyg=pedyNB[0]; pzg=pedzNB[0]; eg=energiaNB[0]; g++; px1=pxc; py1=pyc; pz1=pzc; e1=ec;}

        double pTg=sqrt(pxg*pxg+pyg*pyg);
        double mg=sqrt(eg*eg-pxg*pxg-pyg*pyg-pzg*pzg);


for(int i=0;i<3 ;i++){
	   px3+=pedxNB[i];
	   py3+=pedyNB[i];
	   pz3+=pedzNB[i];
       e3 +=energiaNB[i];

	   pxnb+=pedxNB[i];
	   pynb+=pedyNB[i];
	   pznb+=pedzNB[i];
       enb +=energiaNB[i];

}
for(int k=0;k<1 ;k++){
	   px3+=pedxB[k];
	   py3+=pedyB[k];
	   pz3+=pedzB[k];
       e3 +=energiaB[k];

       px2+=pedxB[k];
	   py2+=pedyB[k];
	   pz2+=pedzB[k];
       e2 +=energiaB[k];

       n2++;
}
	   pxt=px1+px2;
	   pyt=py1+py2;
	   pzt=pz1+pz2;
       et =e1+e2;

       double pT1=sqrt(px1*px1+py1*py1);
       double pT2=sqrt(px2*px2+py2*py2);
       double pT3=sqrt(px3*px3+py3*py3);

       double m1=sqrt(e1*e1-px1*px1-py1*py1-pz1*pz1);
       double m2=sqrt(e2*e2-px2*px2-py2*py2-pz2*pz2);
       double m3=sqrt(e3*e3-px3*px3-py3*py3-pz3*pz3);

       double mt=sqrt(et*et-pxt*pxt-pyt*pyt-pzt*pzt);
       double mq=sqrt((380-e3)*(380-e3)-px3*px3-py3*py3-pz3*pz3);


       double pTnb=sqrt(pxnb*pxnb+pynb*pynb);
       double mnb=sqrt(enb*enb-pxnb*pxnb-pynb*pynb-pznb*pznb);

      //pierwsze ciecie
      //if(n4==4 && licznikB==1 && g==1 && m1<=90 && m1>=70 && mt>=150 && mt<=200 && pT3>=30 && pT3<=80 && mnb<=140 && mnb>=90 && e3<=250 && eg>=10 && eg<=60 && pTg<=50 && mg<=5 && enb<=160){
      //drugie ciece
      //if(n4==4 && licznikB==1 && g==1 & m1<=90 && m1>=70 && mt>=150 && mt<=200 && pT3>=30 && pT3<=80 && mnb>=90 && eg>=10 && mg<=5 && eg>=70 && pTg>=70 && mq<=70 ){
////////////////////
      //if(n4==4 && licznikB==1 && g==1 && pT3>=30 && mt>=150 && mt<=200 && e3<=240 && pT3<=80 && enb<=150){
      //if(n4==4 && licznikB==1 && g==1 && pT3>=30 && mt>=150 && mt<=200 && e3>=250 && mg<=1.5 && pTg>=50){
      if(n4==4 && licznikB==1 && g==1 && pT3>=30 && mt>=150 && mt<=200 && e3>=250 && mg<=1.5 && pTg>=50 && mq<=60){

        M1hist->Fill(m1);
        M2hist->Fill(m2);
        M3hist->Fill(m3);

        E1hist->Fill(e1);
        E2hist->Fill(e2);
        E3hist->Fill(e3);

        PT1hist->Fill(pT1);
        PT2hist->Fill(pT2);
        PT3hist->Fill(pT3);

        Eghist->Fill(enb);
        PTghist->Fill(pTnb);
        Mghist->Fill(mnb);

        Ekhist->Fill(eg);
        PTkhist->Fill(pTg);

        Mqhist->Fill(mq);
        Mthist->Fill(mt);

        PXYhist->Fill(px3,py3);
        PTEhist->Fill(pT3,e3);
        MEhist->Fill(m3,e3);
        PTEghist->Fill(pTg,eg);

        }



   return kTRUE;
}

void Sygnal::SlaveTerminate()
{

}

void Sygnal::Terminate()
{

 gROOT->SetStyle("Plain");
 gStyle->SetOptLogy(0);
 gStyle->SetOptStat(1110);
 // gStyle->SetOptStat(0);
 // gStyle->SetOptFit(111);

TCanvas  *ctt = (TCanvas *) gROOT->FindObject("ctt");
 if(!ctt)
     ctt = new TCanvas("ctt","Event histograms",20,20,800,400);

 ctt->Clear();
 ctt->Divide(1,1);

////////partonowo//////
    ctt->cd(1);
    M1hist->Draw();

    //ctt->cd(2);
    //M2hist->Draw();

    //ctt->cd(3);
    //M3hist->Draw();

    //ctt->cd(1);
    //Mqhist->Draw();

    //ctt->cd(2);
    //Mthist->Draw();
/////////////////////////////
    M1hist->Write();
    delete M1hist;

    M2hist->Write();
    delete M2hist;

    M3hist->Write();
    delete M3hist;

    E1hist->Write();
    delete E1hist;

    E2hist->Write();
    delete E2hist;

    E3hist->Write();
    delete E3hist;

    PT1hist->Write();
    delete PT1hist;

    PT2hist->Write();
    delete PT2hist;

    PT3hist->Write();
    delete PT3hist;

    Mthist->Write();
    delete Mthist;

    Mghist->Write();
    delete Mghist;

    PTghist->Write();
    delete PTghist;

    Eghist->Write();
    delete Eghist;

    PTkhist->Write();
    delete PTkhist;

    Ekhist->Write();
    delete Ekhist;

    PXYhist->Write();
    delete PXYhist;

    PTEhist->Write();
    delete PTEhist;

    MEhist->Write();
    delete MEhist;

    PTEghist->Write();
    delete PTEghist;

    Mqhist->Write();
    delete Mqhist;

    plik->Close();
    delete plik;
}
