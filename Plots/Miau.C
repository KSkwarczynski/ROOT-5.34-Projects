void Miau()
{
    // Creating canvas
    TCanvas *canvas = new TCanvas("canvas", "Cat Multigraph", 800, 600);

    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Cat Multigraph");

    const Int_t nHead = 21;
    Double_t xHead[nHead], yHead[nHead];
    Double_t radiusHead = 1.0;
    for (Int_t i = 0; i < nHead; i++) {
        Double_t angle = 2.0 * TMath::Pi() / (nHead - 1) * i;
        xHead[i] = radiusHead * TMath::Cos(angle);
        yHead[i] = radiusHead * TMath::Sin(angle);
    }

    TGraph *head = new TGraph(nHead, xHead, yHead);

    // Creating ears
    TGraph *leftEar = new TGraph(4);
    leftEar->SetPoint(0, -0.5, 0.7);
    leftEar->SetPoint(1, -0.8, 1.3);
    leftEar->SetPoint(2, -0.2, 1.1);
    leftEar->SetPoint(3, -0.5, 0.7);

    TGraph *rightEar = new TGraph(4);
    rightEar->SetPoint(0, 0.5, 0.7);
    rightEar->SetPoint(1, 0.8, 1.3);
    rightEar->SetPoint(2, 0.2, 1.1);
    rightEar->SetPoint(3, 0.5, 0.7);

    // Creating eyes
    TGraph *leftEye = new TGraph(5);
    leftEye->SetPoint(0, -0.3, 0.3);
    leftEye->SetPoint(1, -0.2, 0.5);
    leftEye->SetPoint(2, -0.1, 0.3);
    leftEye->SetPoint(3, -0.2, 0.1);
    leftEye->SetPoint(4, -0.3, 0.3);

    TGraph *rightEye = new TGraph(5);
    rightEye->SetPoint(0, 0.3, 0.3);
    rightEye->SetPoint(1, 0.2, 0.5);
    rightEye->SetPoint(2, 0.1, 0.3);
    rightEye->SetPoint(3, 0.2, 0.1);
    rightEye->SetPoint(4, 0.3, 0.3);

    // Creating whiskers
    TGraph *leftWhiskers = new TGraph(5);
    leftWhiskers->SetPoint(0, -0.4, 0.1);
    leftWhiskers->SetPoint(1, -0.6, 0.1);

    TGraph *leftWhiskers3 = new TGraph(5);
    leftWhiskers3->SetPoint(0, -0.4, -0.2);
    leftWhiskers3->SetPoint(1, -0.6, -0.2);

    TGraph *leftWhiskers2 = new TGraph(5);
    leftWhiskers2->SetPoint(0, -0.4, -0.4);
    leftWhiskers2->SetPoint(1, -0.6, -0.4);

    TGraph *rightWhiskers = new TGraph(5);
    rightWhiskers->SetPoint(0, +0.4, 0.1);
    rightWhiskers->SetPoint(1, +0.6, 0.1);

    TGraph *rightWhiskers3 = new TGraph(5);
    rightWhiskers3->SetPoint(0, +0.4, -0.2);
    rightWhiskers3->SetPoint(1, +0.6, -0.2);

    TGraph *rightWhiskers2 = new TGraph(5);
    rightWhiskers2->SetPoint(0, +0.4, -0.4);
    rightWhiskers2->SetPoint(1, +0.6, -0.4);


   Double_t lon1 = -2;
   Double_t lon2 =  +2;
   Double_t lat1 =  -2;
   Double_t lat2 =  +2;

   TH2Poly *p = new TH2Poly("Miau Binning", "Miau Binning", lon1,lon2,lat1,lat2);
   p->GetXaxis()->SetTitle("Tokai To Cat");
   p->GetYaxis()->SetTitle("Super- Catokande");


   p->AddBin(head);
   p->AddBin(leftEar);
   p->AddBin(rightEar);
   p->AddBin(leftEye);
   p->AddBin(rightEye);
   p->AddBin(leftWhiskers);
   p->AddBin(leftWhiskers2);
   p->AddBin(leftWhiskers3);
   p->AddBin(rightWhiskers);
   p->AddBin(rightWhiskers2);
   p->AddBin(rightWhiskers3);



   p->SetBinContent(1, 10);
   p->SetBinContent(2, 5);
   p->SetBinContent(3, 5);

   p->SetBinContent(4, 2);
   p->SetBinContent(5, 2);

   p->Draw("colz text");
}
