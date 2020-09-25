//void ProtonSystematic(TString PathName, TString FileName)
void ProtonSystematic()
{
    
    TString PathName="/mnt/home/share/t2k/kskwarczynski/BANFF/NewSelection/";
    TString FileName="CheckRun7Prod6TPlayground";
    DrawingTools* draw = new DrawingTools(Form("%sOutput/%s.root",PathName.Data(), FileName.Data()));

    //draw->SetStackFillStyle(3254);

    Experiment exp("nd280");

    DataSample* magnet_mc_run = new DataSample(Form("%sOutput/%s.root",PathName.Data(), FileName.Data()));

    SampleGroup run("run");
    run.AddMCSample("magnet",magnet_mc_run);

    exp.AddSampleGroup("run" , run);

    //string syst_name[] = {"bfield_syst" , "momresol_syst" , "momscale_syst" , "tpcpid_syst"  , "fgdpid_syst" , "chargeideff_syst" , "tpctrackeff_syst" , "tpcfgdmatcheff_syst" , "tpcclustereff_syst" , "michel_syst" , "fgdhybridtrackeff_syst" , "pileup_syst" ,  "fgdmass_syst" , "oofv_syst" , "tpc_ecal_matcheff_syst", "sipion_syst" , "siproton_syst" , /*"flux_syst",*/ "all_syst"};
    
    string syst_name[] = {"tpcpid_syst", "fgdpid_syst",  "chargeideff_syst", "tpctrackeff_syst", "tpcfgdmatcheff_syst", "sipion_syst", "siproton_syst", "fgdhybridtrackeff_syst", "all_syst"};
    
    const int NSyst = sizeof(syst_name)/sizeof(string);
    
    streambuf *psbuf, *backup;
    ofstream file_output;
    file_output.open(Form("%splots/%s_ERRORS.txt", PathName.Data(), FileName.Data()));
    backup = cout.rdbuf();       // back up cout's streambuf
    psbuf = file_output.rdbuf(); // get file's streambuf
    cout.rdbuf(psbuf);           // assign streambuf to cout
    
    TCanvas* c1 = new TCanvas("c1","c1",0, 0, 800,630);
    c1->Print( Form("%splots/ProtonSystematic.pdf(", PathName.Data() ), "pdf");
    for(int isy=0; isy<NSyst; isy++)
    //for(int isy=12; isy<13; isy++)
    {
        string _syst_name;
        _syst_name=syst_name[isy];
        TString syst_nazwa=syst_name[isy];
        exp.GetMCSample("run" , "magnet")->SetCurrentTree(_syst_name);
        
        if(isy < 2)
        {
            cout<<"CC-0Pi-0p below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][0]>8", "", "SYS");
            cout<<"CC-0Pi-Np below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][1]>8", "", "SYS");
            cout<<"CC-1Pi below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][2]>7", "", "SYS");
            cout<<" przerwa "<<endl;
                
            draw->SetTitleX(("CC-0Pi-0p  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][0]>8" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");

            draw->SetTitleX(("CC-0Pi-Np  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][1]>8" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");
            
            draw->SetTitleX(("CC-1Pi  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][2]>7" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");
        }
        
        else
        {
            
            cout<<"CC-0Pi-0p below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][0]>8 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
            cout<<"CC-0Pi-Np below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][1]>8 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
            cout<<"CC-1Pi below  "<<_syst_name<<endl;
            draw->DrawRelativeErrors(exp,"0.",1,-1,1,"accum_level[][2]>7 && weight_syst_total<10 && weight_syst_total > 0", "", "SYS");
            cout<<" przerwa "<<endl;
                
            
            draw->SetTitleX(("CC-0Pi-0p  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][0]>8 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");

            draw->SetTitleX(("CC-0Pi-Np  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][1]>8 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");
            
            draw->SetTitleX(("CC-1Pi  "+_syst_name).c_str());
            draw->DrawRelativeErrors(exp,"selmu_mom",20, 0., 5000., "accum_level[][2]>7 && weight_syst_total<10 && weight_syst_total > 0" , "", "SYS");
            c1->Print(Form("%splots/ProtonSystematic.pdf",PathName.Data()), "pdf");
        }
        
    }
    
    cout.rdbuf(backup);// restore cout's original streambuf
    file_output.close();

    c1->Print(Form("%splots/ProtonSystematic.pdf)",PathName.Data()), "pdf");
    delete c1;
}
