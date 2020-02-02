#include <fstream>
#include <iostream>
#include "TMath.h"

void ParticleGun()
{
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    TString Directory ="/mnt/home/kskwarczynski/T2K/work/v11r31/nd280Control/v1r67/HighlandOutput/";
    
    //DrawingTools draw( Form("%sParticleGun-mu--2-00-Accum0.root",Directory.Data()), false );
    DrawingTools draw("/mnt/home/kskwarczynski/T2K/work/v11r31/highland2/antiNumuCCMultiPiAnalysis/v2r6/Linux-x86_64/Run5AntiNumuMultiPiAccum0.root", false);
    
    TString Particle[6]={"mu-", "mu+", "anti_proton", "proton", "pi-", "pi+"};
    
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/ParticleGunDistance/";
    TCanvas* c1[30][6];
    
    for(int ig=200; ig<2001; ig=ig+100)
    {
        for(int ik=0; ik<6; ik++)
        {
            //cout<<"plik "<<Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100)<<endl;
           
            if(!gSystem->AccessPathName( Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) ) )
            {
                cout<<"opening "<< Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) <<endl;
                
                DataSample* ParticleGunSample = new DataSample( Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) );
                c1[ig/100][ik] = new TCanvas( Form("c1-%i-%i",ig, ik), Form("c1-%i-%i",ig, ik), 10,10,800,600);
   
                draw.SetTitle( Form("EndPosEnergy-%s-E%i.pdf", Particle[ik].Data(), ig) );
                draw.SetTitleX("endpos [cm]");
                draw.SetLegendPos("tr");
        
                draw.Draw(*ParticleGunSample,"selmu_endpos[2]", 40, 0., 3500,"topology","accum_level[0][0]>1");
                c1[ig/100][ik]->Print( Form("%sEndPosEnergy-%s-E%i.pdf", PathName.Data(), Particle[ik].Data(), ig) );
                delete c1[ig/100][ik];
                delete ParticleGunSample;
            }
        }
    }
}
