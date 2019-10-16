void Example()
{
//gROOT->SetStyle("T2K");
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);

    DrawingTools draw("AntiNumu.root");
    DataSample* data = new DataSample("AntiNumu.root");
    
    TString scut[3]={"accum_level[0][0]>5","accum_level[0][0]>6","accum_level[0][0]>7."}; //string of cuts
    TString PathName="/mnt/home/kskwarczynski/T2K/PlotOutputs/";
    TString FileNames[4]={"KtoToWidzial.pdf","BrakPomyslowNaTytul.pdf","NieWiemCoSieDzieje", "CosDziwnego.pdf"};
    TString PrintName[4];
    for(int i=0; i<4; i++)
    {
        PrintName[i]=PathName+FileNames[i];
    }
    
    draw.SetTitle("Tytul z kieszeni");
    draw.SetTitleX("Tescik osi X");
    draw.SetTitleY("Evenciki nazwa testowa");

    draw.SetLegendPos("tr"); //tr for right or tl for left
    draw.Draw(*data,"selmu_mom",20,0., 5000.,"reaction",scut[2].Data());
    c1->Print(PrintName[0]);
    
    draw.SetLegendPos("tl");
    draw.Draw(*data,"selmu_costheta",40,0.0,1.0,"topology",scut[0].Data());
    c1->Print(PrintName[1]);
    
    draw.Draw(*data,"selmu_likemu",010,0.0,1.0,"particle","accum_level[0][0]>6 && topology<3");
    c1->Print(PrintName[2]);
    
    draw.Draw(*data,"TPCSecMom[0]",30,0.0,3000.0,"all",scut[1].Data(),"","SYS E2");
    c1->Print(PrintName[3]);
    
    draw.PrintPurities(*data,"reaction","accum_level[0][0]>8");
    
    draw.DumpCategories();   
    //draw.DumpCuts();


}
