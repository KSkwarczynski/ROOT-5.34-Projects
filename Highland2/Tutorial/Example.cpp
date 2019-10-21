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
    TString FileNames[7]={"KtoToWidzial.pdf","BrakPomyslowNaTytul.pdf","NieWiemCoSieDzieje.pdf", "CosDziwnego.pdf", "xD.pdf", "TEST.pdf","xDDDD.pdf"};
    TString PrintName[7];
    for(int i=0; i<7; i++)
    {
        PrintName[i]=PathName+FileNames[i];
    }
    
    TText *isniwg = new TText();
    isniwg->SetTextSize(0.10);
  
    draw.SetTitle("Tytul z kieszeni");
    draw.SetTitleX("Muon momentum");
    draw.SetTitleY("Events-test");

    draw.SetLegendPos("tr"); //tr for right or tl for left
    draw.Draw(*data,"selmu_mom",20,0., 5000.,"reaction",scut[2].Data());
    c1->Print(PrintName[0]);
    
    draw.SetTitleX("Muon costheta");
    draw.SetLegendPos("tl");
    draw.Draw(*data,"selmu_costheta",40,0.0,1.0,"topology",scut[0].Data());
    c1->Print(PrintName[1]);
    
    draw.SetTitleX("Muon likelihood");
    draw.Draw(*data,"selmu_likemu",010,0.0,1.0,"particle","accum_level[0][0]>6 && topology<3");
    c1->Print(PrintName[2]);
    
    draw.SetTitle("Nie wiem co to jest");
    draw.SetTitleX("cos z TPC");
    draw.Draw(*data,"TPCSecMom[0]",30,0.0,3000.0,"all",scut[1].Data(),"","SYS E2");
    c1->Print(PrintName[3]);
    
    draw.SetLegendPos("tr"); //tr for right or tl for left
    draw.Draw(*data,"selmu_mom",20,0., 5000.,"detector",scut[2].Data());
    c1->Print(PrintName[4]);
    
    draw.SetTitle("#mu^{#pm}");
    draw.SetTitleX("Muon costheta");
    draw.SetLegendPos("tl");
    draw.Draw(*data,"selmu_costheta",40,0.0,1.0,"primary",scut[0].Data());
    c1->Print(PrintName[5]);
    
    draw.SetLegendPos("tl");
    draw.Draw(*data,"selmu_costheta",40,0.0,1.0,"particle",scut[0].Data());
    isniwg->DrawTextNDC(0.1,0.2,"Probny TextNDC"); //first is x axis second y axis from bottom to top
    c1->Print(PrintName[6]);
    
    draw.PrintPurities(*data,"reaction","accum_level[0][0]>8");
    
    //draw.DumpCategories();  \\diferent drawing options  
    //draw.DumpCuts();         \\Cuts explanation 

}
