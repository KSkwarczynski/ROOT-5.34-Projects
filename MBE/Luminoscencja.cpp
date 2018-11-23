{
    //Program liczy liczbe lini
    int number_of_linesS1 = 0;
    int number_of_linesS2 = 0;
    int number_of_linesS3 = 0;
    int number_of_linesS4 = 0;
    int number_of_linesS5 = 0;
    int number_of_linesR1 = 0;
    int number_of_linesR2 = 0;
    int number_of_linesR3 = 0;
    int number_of_linesR4 = 0;
    int number_of_linesR5 = 0;
    string lineS1;
    string lineS2;
    string lineS3;
    string lineS4;
    string lineS5;
    string lineR1;
    string lineR2;
    string lineR3;
    string lineR4;
    string lineR5;
    ifstream myfileS1("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_600nm.txt");
    ifstream myfileS2("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_660nm.txt");
    ifstream myfileS3("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_720nm.txt");
    ifstream myfileS4("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_770nm.txt");
    ifstream myfileS5("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_830nm.txt");
    ifstream myfileR1("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_600nm.txt");
    ifstream myfileR2("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_660nm.txt");
    ifstream myfileR3("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_720nm.txt");
    ifstream myfileR4("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_780nm.txt");
    ifstream myfileR5("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_830nm.txt");

    if(myfileS1.is_open()){
        while(!myfileS1.eof()){
            getline(myfileS1,lineS1);
            number_of_linesS1++;
        }
        myfileS1.close();
    }
    if(myfileS2.is_open()){
        while(!myfileS2.eof()){
            getline(myfileS2,lineS2);
            number_of_linesS2++;
        }
        myfileS2.close();
    }
    if(myfileS3.is_open()){
        while(!myfileS3.eof()){
            getline(myfileS3,lineS3);
            number_of_linesS3++;
        }
        myfileS3.close();
    }
    if(myfileS4.is_open()){
        while(!myfileS4.eof()){
            getline(myfileS4,lineS4);
            number_of_linesS4++;
        }
        myfileS4.close();
    }
    if(myfileS5.is_open()){
        while(!myfileS5.eof()){
            getline(myfileS5,lineS5);
            number_of_linesS5++;
        }
        myfileS5.close();
    }
     if(myfileR1.is_open()){
        while(!myfileR1.eof()){
            getline(myfileR1,lineR1);
            number_of_linesR1++;
        }
        myfileR1.close();
    }
    if(myfileR2.is_open()){
        while(!myfileR2.eof()){
            getline(myfileR2,lineR2);
            number_of_linesR2++;
        }
        myfileS2.close();
    }
    if(myfileR3.is_open()){
        while(!myfileR3.eof()){
            getline(myfileR3,lineR3);
            number_of_linesR3++;
        }
        myfileR3.close();
    }
    if(myfileR4.is_open()){
        while(!myfileR4.eof()){
            getline(myfileR4,lineR4);
            number_of_linesR4++;
        }
        myfileR4.close();
    }
    if(myfileR5.is_open()){
        while(!myfileR5.eof()){
            getline(myfileR5,lineR5);
            number_of_linesR5++;
        }
        myfileR5.close();
    }
    /////////////////////////////////////////
    int const zS1=number_of_linesS1;
    float ES1[zS1], xS1[zS1], yS1[zS1];

    int const zS2=number_of_linesS2;
    float ES2[zS2], xS2[zS2], yS2[zS2];

    int const zS3=number_of_linesS3;
    float ES3[zS3], xS3[zS3], yS3[zS3];

    int const zS4=number_of_linesS4;
    float ES4[zS4], xS4[zS4], yS4[zS4];

    int const zS5=number_of_linesS5;
    float ES5[zS5], xS5[zS5], yS5[zS5];

    int const zR1=number_of_linesR1;
    float ER1[zR1],xR1[zR1], yR1[zR1];

    int const zR2=number_of_linesR2;
    float ER2[zR2], xR2[zR2], yR2[zR2];

    int const zR3=number_of_linesR3;
    float ER3[zR3], xR3[zR3], yR3[zR3];

    int const zR4=number_of_linesR4;
    float ER4[zR4], xR4[zR4], yR4[zR4];

    int const zR5=number_of_linesR5;
    float ER5[zR5], xR5[zR5], yR5[zR5];
////////////////////////////////////////////////////////////////////////////
    fstream plikS1;
    plikS1.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_600nm.txt", ios::in);

    fstream plikS2;
    plikS2.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_660nm.txt", ios::in);

    fstream plikS3;
    plikS3.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_720nm.txt", ios::in);

    fstream plikS4;
    plikS4.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_770nm.txt", ios::in);

    fstream plikS5;
    plikS5.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_punkt4_830nm.txt", ios::in);

    fstream plikR1;
    plikR1.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_600nm.txt", ios::in);

    fstream plikR2;
    plikR2.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_660nm.txt", ios::in);

    fstream plikR3;
    plikR3.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_720nm.txt", ios::in);

    fstream plikR4;
    plikR4.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_780nm.txt", ios::in);

    fstream plikR5;
    plikR5.open("UW0968_PLsng_s600_exc532nm_2x10s_mocF2_ramka_830nm.txt", ios::in);
/////////////////////////////////////////////////
for(int i=0; i<zS1 ; i++)
    {
        plikS1 >> xS1[i] >> yS1[i];
        ES1[i]=1239.8/xS1[i];
    }
    plikS1.close();

for(int i=0; i<zS2 ; i++)
    {
        plikS2 >> xS2[i] >> yS2[i];
        ES2[i]=1239.8/xS2[i];
    }
    plikS2.close();

for(int i=0; i<zS3 ; i++)
    {
        plikS3 >> xS3[i] >> yS3[i];
        ES3[i]=1239.8/xS3[i];
    }
    plikS3.close();

for(int i=0; i<zS4 ; i++)
    {
        plikS4 >> xS4[i] >> yS4[i];
        ES4[i]=1239.8/xS4[i];
    }
    plikS4.close();

for(int i=0; i<zS5 ; i++)
    {
        plikS5 >> xS5[i] >> yS5[i];
        ES5[i]=1239.8/xS5[i];
    }
    plikS5.close();

for(int k=0; k<zR1 ; k++)
    {
        plikR1 >> xR1[k] >> yR1[k];
        ER1[k]=1239.8/xR1[k];
    }
    plikR1.close();

for(int i=0; i<zR2 ; i++)
    {
        plikR2 >> xR2[i] >> yR2[i];
        ER2[i]=1239.8/xR2[i];
    }
    plikR2.close();

for(int i=0; i<zR3 ; i++)
    {
        plikR3 >> xR3[i] >> yR3[i];
        ER3[i]=1239.8/xR3[i];
    }
    plikR3.close();

for(int i=0; i<zR4 ; i++)
    {
        plikR4 >> xR4[i] >> yR4[i];
        ER4[i]=1239.8/xR4[i];
    }
    plikR4.close();

for(int i=0; i<zR5 ; i++)
    {
        plikR5 >> xR5[i] >> yR5[i];
        ER5[i]=1239.8/xR5[i];
    }
    plikR5.close();
///////////////////////////////////////////////////////////////
	TGraph *S1=new TGraph(zS1, ES1, yS1);
    S1->SetMarkerSize(0.4);
    S1->SetMarkerStyle(32);
    S1->SetMarkerColor(2);

    TGraph *S2=new TGraph(zS2, ES2, yS2);
    S2->SetMarkerSize(0.4);
    S2->SetMarkerStyle(32);
    S2->SetMarkerColor(2);

    TGraph *S3=new TGraph(zS3, ES3, yS3);
    S3->SetMarkerSize(0.4);
    S3->SetMarkerStyle(32);
    S3->SetMarkerColor(2);

    TGraph *S4=new TGraph(zS4, ES4, yS4);
    S4->SetMarkerSize(0.4);
    S4->SetMarkerStyle(32);
    S4->SetMarkerColor(2);

    TGraph *S5=new TGraph(zS5, ES5, yS5);
    S5->SetMarkerSize(0.4);
    S5->SetMarkerStyle(32);
    S5->SetMarkerColor(2);

	TGraph *R1=new TGraph(zR1,ER1,yR1);
    R1->SetMarkerSize(0.5);
    R1->SetMarkerStyle(8);
    R1->SetMarkerColor(4);

    TGraph *R2=new TGraph(zR2, ER2, yR2);
    R2->SetMarkerSize(0.5);
    R2->SetMarkerStyle(8);
    R2->SetMarkerColor(4);

    TGraph *R3=new TGraph(zR3, ER3, yR3);
    R3->SetMarkerSize(0.5);
    R3->SetMarkerStyle(8);
    R3->SetMarkerColor(4);

    TGraph *R4=new TGraph(zR4, ER4, yR4);
    R4->SetMarkerSize(0.5);
    R4->SetMarkerStyle(8);
    R4->SetMarkerColor(4);

    TGraph *R5=new TGraph(zR5, ER5, yR5);
    R5->SetMarkerSize(0.5);
    R5->SetMarkerStyle(8);
    R5->SetMarkerColor(4);

	TMultiGraph *mg=new TMultiGraph();
    mg->Add(S1);
    mg->Add(S2);
    mg->Add(S3);
    mg->Add(S4);
    mg->Add(S5);
    mg->Add(R1);
    mg->Add(R2);
    mg->Add(R3);
    mg->Add(R4);
    mg->Add(R5);

	mg->Draw("AP");
    mg->GetXaxis()->SetTitle("Energy [eV]");
    mg->GetYaxis()->SetTitle("Intensity");
    mg->GetHistogram()->SetTitle("Luminescence (UW0968)");
    gPad->Modified();

   auto legend = new TLegend(0.7,0.8,0.905,0.9);
   legend->AddEntry(S1,"Center","p");
   legend->AddEntry(R1,"Edge","p");
   legend->Draw();
}
