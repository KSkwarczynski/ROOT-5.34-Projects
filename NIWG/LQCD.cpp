{
    // Create a canvas
    TCanvas *c1 = new TCanvas("c1", "Comparison of Meyer and LQCD", 800, 600);

    // Define Q^2 values (x-axis)
    Double_t Q2[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0};

    // Approximate Meyer values (y-axis) from the left plot
    Double_t Meyer[] = {0, 5, 10, 20, 35, 50, 65, 80, 90, 95, 97, 98, 99, 99.5, 100, 100};

    // Approximate LQCD values (y-axis) from the right plot
    Double_t LQCD[] = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5};

    // Create TGraph objects
    TGraph *grMeyer = new TGraph(16, Q2, Meyer);
    TGraph *grLQCD = new TGraph(16, Q2, LQCD);

    // Set graph styles
    grMeyer->SetLineColor(kRed);
    grMeyer->SetLineWidth(2);
    grMeyer->SetMarkerStyle(20);
    grMeyer->SetMarkerColor(kRed);

    grLQCD->SetLineColor(kBlue);
    grLQCD->SetLineWidth(2);
    grLQCD->SetMarkerStyle(20);
    grLQCD->SetMarkerColor(kBlue);

    // Create a multi-graph
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(grMeyer);
    mg->Add(grLQCD);

    // Draw the multi-graph
    mg->Draw("ALP");

    // Set axis titles
    mg->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
    mg->GetYaxis()->SetTitle("Max Factorability (%)");

    // Create a legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    legend->AddEntry(grMeyer, "Meyer", "l");
    legend->AddEntry(grLQCD, "LQCD", "l");
    legend->Draw();

    // Update the canvas
    c1->Update();
    c1->Print("LQCD.pdf");
}
