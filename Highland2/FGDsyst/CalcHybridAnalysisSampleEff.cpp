
void CalcHybridAnalysisSampleEff()
{

    TFile *file = TFile::Open("/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/Prod7/Efficiency/Output/Run4MCProd7.root");
    TTree *tree;
    file->GetObject("default",tree);

    Int_t           accum_level[1][2][5];   //[NTOYS]
    Int_t           fgdhybtr1_fhc_nwrong[50];
    Int_t           fgdhybtr1_fhc_ncorrect[50];
    Int_t           fgdhybtr1_rhc_nwrong[50];
    Int_t           fgdhybtr1_rhc_ncorrect[50];
    Int_t           fgdhybtr2_fhc_nwrong[50];
    Int_t           fgdhybtr2_fhc_ncorrect[50];
    Int_t           fgdhybtr2_rhc_nwrong[50];
    Int_t           fgdhybtr2_rhc_ncorrect[50];

    tree->SetBranchStatus("*", false);

    tree->SetBranchStatus( "accum_level", true);
    tree->SetBranchAddress("accum_level", &(accum_level));

    tree->SetBranchStatus( "fgdhybtr1_fhc_nwrong", true);
    tree->SetBranchAddress("fgdhybtr1_fhc_nwrong", &(fgdhybtr1_fhc_nwrong));

    tree->SetBranchStatus( "fgdhybtr1_fhc_ncorrect", true);
    tree->SetBranchAddress("fgdhybtr1_fhc_ncorrect", &(fgdhybtr1_fhc_ncorrect));

    tree->SetBranchStatus( "fgdhybtr2_fhc_nwrong", true);
    tree->SetBranchAddress("fgdhybtr2_fhc_nwrong", &(fgdhybtr2_fhc_nwrong));

    tree->SetBranchStatus( "fgdhybtr2_fhc_ncorrect", true);
    tree->SetBranchAddress("fgdhybtr2_fhc_ncorrect", &(fgdhybtr2_fhc_ncorrect));



    tree->SetBranchStatus( "fgdhybtr1_rhc_nwrong", true);
    tree->SetBranchAddress("fgdhybtr1_rhc_nwrong", &(fgdhybtr1_rhc_nwrong));

    tree->SetBranchStatus( "fgdhybtr1_rhc_ncorrect", true);
    tree->SetBranchAddress("fgdhybtr1_rhc_ncorrect", &(fgdhybtr1_rhc_ncorrect));

    tree->SetBranchStatus( "fgdhybtr2_rhc_nwrong", true);
    tree->SetBranchAddress("fgdhybtr2_rhc_nwrong", &(fgdhybtr2_rhc_nwrong));

    tree->SetBranchStatus( "fgdhybtr2_rhc_ncorrect", true);
    tree->SetBranchAddress("fgdhybtr2_rhc_ncorrect", &(fgdhybtr2_rhc_ncorrect));


    int AllEvents = tree->GetEntries();

    const int Nbins = 50;
    const int N_FGDs = 2;
    int nCorrect[N_FGDs][Nbins] = {0};
    int nWrong[N_FGDs][Nbins] = {0};
    double Efficiency[N_FGDs][Nbins] = {0};

    int nCorrect_RHC[N_FGDs][Nbins] = {0};
    int nWrong_RHC[N_FGDs][Nbins] = {0};
    double Efficiency_RHC[N_FGDs][Nbins] = {0};

    const int AccumCut = 5;
    for(int i = 0;  i < AllEvents; i++)
    {
        tree->GetEntry(i);

        if(accum_level[0][0][0] > AccumCut)
        {
            for(int j = 0;  j < Nbins; j++)
            {
                nCorrect[0][j] +=  fgdhybtr1_fhc_ncorrect[j];
                nWrong[0][j]   +=  fgdhybtr1_fhc_nwrong[j];
            }
        }

        if(accum_level[0][1][0] > AccumCut)
        {
            for(int j = 0;  j < Nbins; j++)
            {
                nCorrect[1][j] +=  fgdhybtr2_fhc_ncorrect[j];
                nWrong[1][j]   +=  fgdhybtr2_fhc_nwrong[j];
            }
        }
        //RHC
        if(accum_level[0][0][0] > AccumCut)
        {
            for(int j = 0;  j < Nbins; j++)
            {
                nCorrect_RHC[0][j] +=  fgdhybtr1_rhc_ncorrect[j];
                nWrong_RHC[0][j]   +=  fgdhybtr1_rhc_nwrong[j];
            }
        }

        if(accum_level[0][1][0] > AccumCut)
        {
            for(int j = 0;  j < Nbins; j++)
            {
                nCorrect_RHC[1][j] +=  fgdhybtr2_rhc_ncorrect[j];
                nWrong_RHC[1][j]   +=  fgdhybtr2_rhc_nwrong[j];
            }
        }
    }



    //Pront Efficiency
    for(int d = 0;  d < N_FGDs; d++)
    {
        std::cout<<" FGD "<<d+1<<std::endl;
        for(int j = 0;  j < Nbins; j++)
        {
            int denominator = nCorrect[d][j]+nWrong[d][j];
            if(denominator > 0) Efficiency[d][j] = double(nCorrect[d][j])/double(denominator);

            std::cout<<Efficiency[d][j]<<std::endl;
        }
    }

    std::cout<<" Now RHC "<<std::endl;
    for(int d = 0;  d < N_FGDs; d++)
    {
        std::cout<<" FGD "<<d+1<<std::endl;
        for(int j = 0;  j < Nbins; j++)
        {

            int denominator = nCorrect_RHC[d][j]+nWrong_RHC[d][j];
            if(denominator > 0) Efficiency_RHC[d][j] = nCorrect_RHC[d][j]/(denominator);

            std::cout<<Efficiency[d][j]<<std::endl;
        }
    }
}
