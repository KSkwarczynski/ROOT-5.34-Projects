{
    //Program liczy liczbe lini
    int number_of_linesS1 = 0;
    int number_of_linesR1 = 0;
    string lineS1;
    string lineR1;
    ifstream myfileS1("UW0962_PLsng_s600_exc532nm_2x10s_maxP.txt");
    ifstream myfileR1("UW0962_PLsng_s600_exc532nm_2x10s_maxP_ramka.txt");

    if(myfileS1.is_open()){
        while(!myfileS1.eof()){
            getline(myfileS1,lineS1);
            number_of_linesS1++;
        }
        myfileS1.close();
    }
     if(myfileR1.is_open()){
        while(!myfileR1.eof()){
            getline(myfileR1,lineR1);
            number_of_linesR1++;
        }
        myfileR1.close();
    }
    //czary mary aby dzia³a³o
    int const zS1=number_of_linesS1;
    float ES1[zS1], xS1[zS1], yS1[zS1];

    int const zR1=number_of_linesR1;
    float ER1[zR1],xR1[zR1], yR1[zR1];


//W³aœciwy program s³uz¹cy do odczytu
    fstream plikS1;
    plikS1.open("UW0962_PLsng_s600_exc532nm_2x10s_maxP.txt", ios::in);

    fstream plikR1;
    plikR1.open("UW0962_PLsng_s600_exc532nm_2x10s_maxP_ramka.txt", ios::in);


for(int i=0; i<zS1 ; i++)
    {
        plikS1 >> xS1[i] >> yS1[i];
        ES1[i]=1239.8/xS1[i];
    }
    plikS1.close();

for(int k=0; k<zR1 ; k++)
    {
        plikR1 >> xR1[k] >> yR1[k];
        ER1[k]=1239.8/xR1[k];
    }
    plikR1.close();
///////////////////////////////////////////////////////////////
	TGraph *S1=new TGraph(zS1, ES1, yS1);
    S1->SetMarkerSize(0.4);
    S1->SetMarkerStyle(32);
    S1->SetMarkerColor(2);

	TGraph *R1=new TGraph(zR1,ER1,yR1);
    R1->SetMarkerSize(0.4);
    R1->SetMarkerStyle(8);
    R1->SetMarkerColor(4);

	TMultiGraph *mg=new TMultiGraph();
    mg->Add(S1);
    mg->Add(R1);

	mg->Draw("AP");
    mg->GetXaxis()->SetTitle("Energy [eV]");
    mg->GetYaxis()->SetTitle("Intensity");
    mg->GetHistogram()->SetTitle("Luminescence (UW0962)");
    gPad->Modified();


   auto legend = new TLegend(0.7,0.8,0.905,0.9);
   legend->AddEntry(S1,"Center","p");
   legend->AddEntry(R1,"Edge","p");
   legend->Draw();

}
