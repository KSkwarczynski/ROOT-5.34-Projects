{
    //////////////////////////////////////Program liczy liczbe lini///////////////////////////
    long double number_of_lines1 = 0;
    long double number_of_lines2 = 0;
    string line1;
    string line2;
    ifstream myfile1("Dane.txt");
    ifstream myfile2("MonteCarlo.txt");

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

    long double z1=number_of_lines1;
    cout<<z1<<endl;
    Float_t snarl1, run1, subrun1, evissigcor1, evisgev1, evisgevkNN1, shwsigcor1, shwgev1, shwgevkNN1, erecoqe1,
    mnstp1, spher1, evtet1, vtxsig1, nhough1, sigmin1, sigmax1, twoangle1, ntrack1, goodstdtrack1,
    mom1, thet1, pt1, charge1, meanph1, sigfluct1, transvp1, sigfluctKG1, trklen1, trkvtxx1,
    trkvtxy1, trkvtxz1, trkendx1, trkendy1, trkendz1, filetyp1, weight1, energynu1, isQE1, itautype1, selection1;

    long double z2=number_of_lines2;
    cout<<z2<<endl;

    float snarl2, run2, subrun2, evissigcor2, evisgev2, evisgevkNN2, shwsigcor2, shwgev2, shwgevkNN2, erecoqe2,
    mnstp2, spher2, evtet2, vtxsig2, nhough2, sigmin2, sigmax2, twoangle2, ntrack2, goodstdtrack2,
    mom2, thet2, pt2, charge2, meanph2, sigfluct2, transvp2, sigfluctKG2, trklen2, trkvtxx2,
    trkvtxy2, trkvtxz2, trkendx2, trkendy2, trkendz2, filetyp2, weight2, energynu2, isQE2, itautype2, selection2;



//////////////////////////////////////////////////////////////////////////////////////////////////////
    fstream plik1;
    plik1.open("Dane.txt", ios::in);

    fstream plik2;
    plik2.open("MonteCarlo.txt", ios::in);

/////////////////////////////////////////////////////////////////////////////////////////////////////
TTree t1("t1","Dane");

t1.Branch("snarl1", &snarl1, "snarl1/F");
t1.Branch("run1", &run1, "run1/F");
t1.Branch("subrun1", &subrun1, "subrun1/F");
t1.Branch("evissigcor1", &evissigcor1, "evissigcor1/F");
t1.Branch("evisgev1", &evisgev1, "evisgev1/F");
t1.Branch("evisgevkNN1", &evisgevkNN1, "evisgevkNN1/F");
t1.Branch("shwsigcor1", &shwsigcor1, "shwsigcor1/F");
t1.Branch("shwgev1", &shwgev1, "shwgev1/F");
t1.Branch("shwgevkNN1", &shwgevkNN1, "shwgevkNN1/F");
t1.Branch("erecoqe1", &erecoqe1, "erecoqe1/F");
t1.Branch("mnstp1", &mnstp1, "mnstp1/F");
t1.Branch("spher1", &spher1, "spher1/F");
t1.Branch("evtet1", &evtet1, "evtet1/F");
t1.Branch("vtxsig1", &vtxsig1, "vtxsig1/F");
t1.Branch("nhough1", &nhough1, "nhough1/F");
t1.Branch("sigmin1", &sigmin1, "sigmin1/F");
t1.Branch("sigmax1", &sigmax1, "sigmax1/F");
t1.Branch("twoangle1", &twoangle1, "twoangle1/F");
t1.Branch("ntrack1", &ntrack1, "ntrack1/F");
t1.Branch("goodstdtrack1", &goodstdtrack1, "goodstdtrack1/F");
t1.Branch("mom1", &mom1, "mom1/F");
t1.Branch("thet1", &thet1, "thet1/F");
t1.Branch("pt1", &pt1, "pt1/F");
t1.Branch("charge1", &charge1, "charge1/F");
t1.Branch("meanph1", &meanph1, "meanph1/F");
t1.Branch("sigfluct1", &sigfluct1, "sigfluct1/F");
t1.Branch("transvp1", &transvp1, "transvp1/F");
t1.Branch("sigfluctKG1", &sigfluctKG1, "sigfluctKG1/F");
t1.Branch("trklen1", &trklen1, "trklen1/F");
t1.Branch("trkvtxx1", &trkvtxx1, "trkvtxx1/F");
t1.Branch("trkvtxy1", &trkvtxy1, "trkvtxy1/F");
t1.Branch("trkvtxz1", &trkvtxz1, "trkvtxz1/F");
t1.Branch("trkendx1", &trkendx1, "trkendx1/F");
t1.Branch("trkendy1", &trkendy1, "trkendy1/F");
t1.Branch("trkendz1", &trkendz1, "trkendz1/F");
t1.Branch("filetyp1", &filetyp1, "filetyp1/F");
t1.Branch("weight1", &weight1, "weight1/F");
t1.Branch("energynu1", &energynu1, "energynu1/F");
t1.Branch("isQE1", &isQE1, "isQE1/F");
t1.Branch("itautype1", &itautype1, "itautype1/F");
t1.Branch("selection1", &selection1, "selection1/F");
////////////////////////////////////////////////////////
TTree t2("t2","MC");

t2.Branch("snarl2", &snarl2, "snarl2/F");
t2.Branch("run2", &run2, "run2/F");
t2.Branch("subrun2", &subrun2, "subrun2/F");
t2.Branch("evissigcor2", &evissigcor2, "evissigcor2/F");
t2.Branch("evisgev2", &evisgev2, "evisgev2/F");
t2.Branch("evisgevkNN2", &evisgevkNN2, "evisgevkNN2/F");
t2.Branch("shwsigcor2", &shwsigcor2, "shwsigcor2/F");
t2.Branch("shwgev2", &shwgev2, "shwgev2/F");
t2.Branch("shwgevkNN2", &shwgevkNN2, "shwgevkNN2/F");
t2.Branch("erecoqe2", &erecoqe2, "erecoqe2/F");
t2.Branch("mnstp2", &mnstp2, "mnstp2/F");
t2.Branch("spher2", &spher2, "spher2/F");
t2.Branch("evtet2", &evtet2, "evtet2/F");
t2.Branch("vtxsig2", &vtxsig2, "vtxsig2/F");
t2.Branch("nhough2", &nhough2, "nhough2/F");
t2.Branch("sigmin2", &sigmin2, "sigmin2/F");
t2.Branch("sigmax2", &sigmax2, "sigmax2/F");
t2.Branch("twoangle2", &twoangle2, "twoangle2/F");
t2.Branch("ntrack2", &ntrack2, "ntrack2/F");
t2.Branch("goodstdtrack2", &goodstdtrack2, "goodstdtrack2/F");
t2.Branch("mom2", &mom2, "mom2/F");
t2.Branch("thet2", &thet2, "thet2/F");
t2.Branch("pt2", &pt2, "pt2/F");
t2.Branch("charge2", &charge2, "charge2/F");
t2.Branch("meanph2", &meanph2, "meanph2/F");
t2.Branch("sigfluct2", &sigfluct2, "sigfluct2/F");
t2.Branch("transvp2", &transvp2, "transvp2/F");
t2.Branch("sigfluctKG2", &sigfluctKG2, "sigfluctKG2/F");
t2.Branch("trklen2", &trklen2, "trklen2/F");
t2.Branch("trkvtxx2", &trkvtxx2, "trkvtxx2/F");
t2.Branch("trkvtxy2", &trkvtxy2, "trkvtxy2/F");
t2.Branch("trkvtxz2", &trkvtxz2, "trkvtxz2/F");
t2.Branch("trkendx2", &trkendx2, "trkendx2/F");
t2.Branch("trkendy2", &trkendy2, "trkendy2/F");
t2.Branch("trkendz2", &trkendz2, "trkendz2/F");
t2.Branch("filetyp2", &filetyp2, "filetyp2/F");
t2.Branch("weight2", &weight2, "weight2/F");
t2.Branch("energynu2", &energynu2, "energynu2/F");
t2.Branch("isQE2", &isQE2, "isQE2/F");
t2.Branch("itautype2", &itautype2, "itautype2/F");
t2.Branch("selection2", &selection2, "selection2/F");
/////////////////////////////////////////////////////////////////////////////////////////////////////
for(int i=0; i<z1 ; i++)
    {
       plik1 >> snarl1 >> run1 >> subrun1 >> evissigcor1 >> evisgev1 >> evisgevkNN1 >> shwsigcor1 >> shwgev1 >> shwgevkNN1 >> erecoqe1 >> mnstp1
        >> spher1 >> evtet1 >> vtxsig1 >> nhough1 >> sigmin1 >> sigmax1 >> twoangle1 >> ntrack1 >> goodstdtrack1
        >> mom1 >> thet1 >> pt1 >> charge1 >> meanph1 >> sigfluct1 >> transvp1 >> sigfluctKG1 >> trklen1 >> trkvtxx1
        >> trkvtxy1 >> trkvtxz1 >> trkendx1 >> trkendy1 >> trkendz1 >> filetyp1 >> weight1 >> energynu1 >> isQE1 >> itautype1 >> selection1;

    t1.Fill();
    }
    plik1.close();

for(int k=0; k<z2 ; k++)
    {
        plik2 >> snarl2 >> run2 >> subrun2 >> evissigcor2 >> evisgev2 >> evisgevkNN2 >> shwsigcor2 >> shwgev2 >> shwgevkNN2 >> erecoqe2 >> mnstp2
        >> spher2 >> evtet2 >> vtxsig2 >> nhough2 >> sigmin2 >> sigmax2 >> twoangle2 >> ntrack2 >> goodstdtrack2
        >> mom2 >> thet2 >> pt2 >> charge2 >> meanph2 >> sigfluct2 >> transvp2 >> sigfluctKG2 >> trklen2 >> trkvtxx2
        >> trkvtxy2 >> trkvtxz2 >> trkendx2 >> trkendy2 >> trkendz2 >> filetyp2 >> weight2 >> energynu2 >> isQE2 >> itautype2>> selection2;

    t2.Fill();
    }
    plik2.close();




	TFile f1("Dane.root","recreate");
	t1.Write();
	f1.Close();


    TFile f2("MC.root","recreate");
	t2.Write();
	f2.Close();

}
