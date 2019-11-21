
void MakeSelector()
{
    TFile *f=TFile::Open("XsecRun5AntiNumuMultiPiAccum0.root");
    TTree *t;
    f->GetObject("default", t);
    t->MakeSelector("kurwa");
}
