{
    //Program liczy liczbe lini
    int number_of_lines1 = 0;
    int number_of_lines2 = 0;
    string line1;
    string line2;
    ifstream myfile1("UW0962_RAM_sng_s1800_exc532nm_3x5s_maxP.txt");
    ifstream myfile2("UW0962_RAM_sng_s1800_exc532nm_3x5s_maxP.ramka.txt");

    if(myfile1.is_open()){
        while(!myfile1.eof()){
            getline(myfile1,line1);
            number_of_lines1++;
        }
        myfile1.close();
    }
     if(myfile2.is_open()){
        while(!myfile2.eof()){
            getline(myfile2,line2);
            number_of_lines2++;
        }
        myfile2.close();
    }
    //czary mary aby działało
    int const z1=number_of_lines1;
    cout<<number_of_lines1<<endl;
    float x1[z1], y1[z1];

    int const z2=number_of_lines2;
    float x2[z2], y2[z2];
    cout<<number_of_lines2<<endl;

//Właściwy program słuzący do odczytu
    fstream plik1;
    plik1.open("UW0962_RAM_sng_s1800_exc532nm_3x5s_maxP.txt", ios::in);

    fstream plik2;
    plik2.open("UW0962_RAM_sng_s1800_exc532nm_3x5s_maxP.ramka.txt", ios::in);


for(int i=0; i<z1 ; i++)
    {
        plik1 >> x1[i] >> y1[i];
    }
    plik1.close();

for(int k=0; k<z2 ; k++)
    {
        plik2 >> x2[k] >> y2[k];
    }
    plik2.close();
///////////////////////////////////////////////////////////////

	TMultiGraph *mg=new TMultiGraph();


	TGraph *gr1=new TGraph(z1, x1, y1);
    gr1->SetMarkerSize(0.6);
    gr1->SetMarkerStyle(32);
    gr1->SetMarkerColor(6);
    gr1->SetLineColor(6);
    gr1->SetLineWidth(2);

///////////////////////WSTAW Z///////
	TGraph *gr2=new TGraph(z2,x2, y2);
    gr2->SetMarkerSize(0.6);
    gr2->SetMarkerStyle(8);
    gr2->SetMarkerColor(7);
    gr2->SetLineColor(7);
    gr2->SetLineWidth(2);

    mg->Add(gr1);
	mg->Add(gr2);

	mg->Draw("ACP");
    mg->GetXaxis()->SetTitle("Raman shift/cm-1");
    mg->GetYaxis()->SetTitle("Intensity");
    mg->GetHistogram()->SetTitle("Raman scattering (UW0962)");
    gPad->Modified();

   auto legend = new TLegend(0.7,0.8,0.905,0.9);
   legend->AddEntry(gr1,"Center","lp");
   legend->AddEntry(gr2,"Edge","lp");
   legend->Draw();
}


