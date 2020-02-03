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
    TCanvas* c1[6][30][6];
    
    
    TString Cuts[5]={"accum_level[0][0]>1", "accum_level[0][0]>1 && selmu_endpos[2]>2500", "accum_level[0][0]>1 && selmu_endpos[2]<2500", "accum_level[0][0]>1 && selmu_endpos[2]>2500", "accum_level[0][0]>1 && selmu_endpos[2]<2500"};

    TString Variable[5]={"selmu_endpos[2]", "selmu_endpos[0]", "selmu_endpos[0]", "selmu_endpos[1]", "selmu_endpos[1]"};
    
    TString OutputName[5]={"EndPos-Z", "EndPos-X-ifZ>2500", "EndPos-X-ifZ<2500", "EndPos-Y-ifZ>2500", "EndPos-Y-ifZ<2500"};
    for(int ig=200; ig<2001; ig=ig+100)
    {
        for(int ik=0; ik<6; ik++)
        {
            //cout<<"plik "<<Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100)<<endl;
           
            if(!gSystem->AccessPathName( Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) ) )
            {
                cout<<"opening "<< Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) <<endl;
                
                DataSample* ParticleGunSample = new DataSample( Form("%sParticleGun-%s-%i-00-Accum0.root",Directory.Data(), Particle[ik].Data(), ig/100) );
                for(int ic=0; ic<5; ic++)
                {
                    c1[ic][ig/100][ik] = new TCanvas( Form("c1-%i-%i-%i",ic , ig, ik), Form("c1-%i-%i-%i", ic, ig, ik), 10,10,800,600);
                    draw.SetTitle( Form("%s-%s-E%i", OutputName[ic].Data(), Particle[ik].Data(), ig) );
                    draw.SetTitleX("endpos [cm]");
                    draw.SetLegendPos("tl");
                    if(ic>0) 
                    {
                        draw.SetLegendPos("tr");
                    }
                    draw.Draw(*ParticleGunSample, Form("%s", Variable[ic].Data() ), 40, 0., 3500,"topology", Form("%s", Cuts[ic].Data() ));
                    c1[ic][ig/100][ik]->Print( Form("%s%s-%s-E%i.pdf", PathName.Data(), OutputName[ic].Data(), Particle[ik].Data(), ig) );
                    delete c1[ic][ig/100][ik];
                
                }
                
                c1[5][ig/100][ik] = new TCanvas( Form("c1-5-%i-%i",ic , ig, ik), Form("c1-5-%i-%i", ig, ik), 10,10,800,600);
                draw.SetTitle( Form("CosTheta-%s-E%i", Particle[ik].Data(), ig) );
                draw.SetTitleX("CosTheta");
                draw.SetLegendPos("tl");
                    
                draw.Draw(*ParticleGunSample,"selmu_costheta", 40,0.0,1.0 ,"topology","accum_level[0][0]>1");
                c1[5][ig/100][ik]->Print( Form("%sCosTheta-%s-E%i.pdf", PathName.Data(), Particle[ik].Data(), ig) );
                delete c1[5][ig/100][ik];
                
                delete ParticleGunSample;
            }
        }
    }
}
