void HybridsSystematic(TString Path, TString FileName)
{
    
    //TString Path="/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/systematicError/FGD1/";
    //TString FileName="Run4MCprod6T-FGD1-nu_DEFAULT";
    DrawingTools* draw = new DrawingTools(Form("%s%s.root",Path.Data(), FileName.Data()), 4);

    //draw->SetStackFillStyle(3254);

    Experiment exp("nd280");

    DataSample* magnet_mc_run = new DataSample(Form("%s%s.root",Path.Data(), FileName.Data()));

    SampleGroup run("run");
    run.AddMCSample("magnet",magnet_mc_run);

    exp.AddSampleGroup("run" , run);

    string syst_name = "fgdhybridtrackeff_syst"; 
    
    Float_t Ntoys = 500.;
    
    streambuf *psbuf, *backup;
    ofstream file_output;
    file_output.open(Form("%s_ERRORS.txt",FileName.Data()));
    backup = cout.rdbuf();       // back up cout's streambuf
    psbuf = file_output.rdbuf(); // get file's streambuf
    cout.rdbuf(psbuf);           // assign streambuf to cout
    

    exp.GetMCSample("run" , "magnet")->SetCurrentTree(syst_name);
    cout<<"CC-0Pi below"<<endl;
    draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][0]>7 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
    cout<<"CC-1Pi below"<<endl;
    draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][1]>7 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
    cout<<"CC-Other below"<<endl;
    draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][2]>7 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
    //draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][2]>6 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS"); //WARNING for neutrino
    
        
    cout.rdbuf(backup);// restore cout's original streambuf
    file_output.close();
    
    TFile *fileout = new TFile(Form("%s_plots.root",FileName.Data()),"RECREATE");
    
    TCanvas* CC0Pi = new TCanvas("CC0Pi","CC0Pi",0, 0, 800,630);
    draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][0]>7 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
    CC0Pi->Write();
    delete CC0Pi;
    
    TCanvas* CC1Pi = new TCanvas("CC1Pi","CC1Pi",0, 0, 800,630);
    draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][1]>7 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
    CC1Pi->Write();
    delete CC1Pi;
    
    TCanvas* CCOther = new TCanvas("CCOther","CCOther",0, 0, 800,630);
    //draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][2]>7 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
    draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][2]>7 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS"); //WARNING for neutrino
    CCOther->Write();
    delete CCOther;
    
    fileout->Close();
    
}
