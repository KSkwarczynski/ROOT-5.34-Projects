{

    S1=new TGraph("UW0961_RAM_sng_s1800_exc532nm_3x5s_maxP.txt");
    S1->SetMarkerSize(0.7);
    S1->SetMarkerStyle(32);
    S1->SetMarkerColor(46);
    S1->SetLineColor(46);
    S1->SetLineWidth(1.5);

    R1=new TGraph("UW0962_RAM_sng_s1800_exc532nm_3x5s_maxP.ramka.txt");
    R1->SetMarkerSize(0.3);
    R1->SetMarkerStyle(32);
    R1->SetMarkerColor(3);
    R1->SetLineColor(3);
    R1->SetLineWidth(2);

	TMultiGraph *mg=new TMultiGraph();
    mg->Add(S1);
    mg->Add(R1);
	mg->Draw("ACP");
    mg->GetXaxis()->SetTitle("Raman shift/cm-1");
    mg->GetYaxis()->SetTitle("Intensity");
    mg->GetHistogram()->SetTitle("Raman scattering (UW0961)");
    gPad->Modified();

   auto legend = new TLegend(0.7,0.8,0.905,0.9);
   legend->AddEntry(S1,"Center","lp");
   legend->AddEntry(R1,"Edge","lp");
   legend->Draw();
}
