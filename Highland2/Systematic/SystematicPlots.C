#include <TStyle.h>


void SystematicPlots()
{
    SetT2Kstyl();
    TH1D *SysError_DEFAULT_R4[3][2];
    TH1D *SysError_NEW_R4[3][2];
    
    TH1D *SysError_DEFAULT_R7[3][2];
    TH1D *SysError_NEW_R7[3][2];
    TH1D *SysError_ANTY_R7[3][2];
    TH1D *SysError_PI_R7[3][2];
    
    TString Sample[3] ={"CC0Pi", "CC1Pi", "CCOther"};
    TString FGD[2]={"1", "2"};
    
    TString Type[4] = {"DEFAULT", "NEW", "ANTI", "PI-"};
     
    /// \Run4_DEFAULT_CC0Pi_FGD1
    SysError_DEFAULT_R4[0][0]=new TH1D(Form("SysError_DEFAULT_R4_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[0][0]->SetBinContent(1,0.0009164005);
    SysError_DEFAULT_R4[0][0]->SetBinContent(2,0.0004964687);
    SysError_DEFAULT_R4[0][0]->SetBinContent(3,0.0009160835);
    SysError_DEFAULT_R4[0][0]->SetBinContent(4,0.00122624);
    SysError_DEFAULT_R4[0][0]->SetBinContent(5,0.001565432);
    SysError_DEFAULT_R4[0][0]->SetBinContent(6,0.002751293);
    SysError_DEFAULT_R4[0][0]->SetBinContent(7,0.002692319);
    SysError_DEFAULT_R4[0][0]->SetBinContent(8,0.002783681);
    SysError_DEFAULT_R4[0][0]->SetBinContent(9,0.00379384);
    SysError_DEFAULT_R4[0][0]->SetBinContent(10,0.00230609);
    SysError_DEFAULT_R4[0][0]->SetBinContent(11,0.004037228);
    SysError_DEFAULT_R4[0][0]->SetBinContent(12,0.002906018);
    SysError_DEFAULT_R4[0][0]->SetBinContent(13,0.004554365);
    SysError_DEFAULT_R4[0][0]->SetBinContent(14,0.006145955);
    SysError_DEFAULT_R4[0][0]->SetBinContent(15,0.002682673);
    SysError_DEFAULT_R4[0][0]->SetBinContent(16,0.006277524);
    SysError_DEFAULT_R4[0][0]->SetBinContent(17,0.004179999);
    SysError_DEFAULT_R4[0][0]->SetBinContent(18,0.004187387);
    SysError_DEFAULT_R4[0][0]->SetBinContent(19,0.00430357);
    SysError_DEFAULT_R4[0][0]->SetBinContent(20,0.002024918);
    SysError_DEFAULT_R4[0][0]->SetBinContent(21,1248.93);
    //SysError_DEFAULT_R4[0][0]->SetBinError(21,35.34021);
    //SysError_DEFAULT_R4[0][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[0][0]->SetMaximum(0.006905277);
    //SysError_DEFAULT_R4[0][0]->SetEntries(1.614002e+007);
    
    SysError_DEFAULT_R4[1][0]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[1][0]->SetBinContent(1,0.0009213501);
    SysError_DEFAULT_R4[1][0]->SetBinContent(2,0.002479474);
    SysError_DEFAULT_R4[1][0]->SetBinContent(3,0.001574576);
    SysError_DEFAULT_R4[1][0]->SetBinContent(4,0.002100486);
    SysError_DEFAULT_R4[1][0]->SetBinContent(5,0.001447405);
    SysError_DEFAULT_R4[1][0]->SetBinContent(6,0.0012483);
    SysError_DEFAULT_R4[1][0]->SetBinContent(7,0.001779013);
    SysError_DEFAULT_R4[1][0]->SetBinContent(8,0.001866376);
    SysError_DEFAULT_R4[1][0]->SetBinContent(9,0.001468929);
    SysError_DEFAULT_R4[1][0]->SetBinContent(10,0.003344982);
    SysError_DEFAULT_R4[1][0]->SetBinContent(11,0.001866746);
    SysError_DEFAULT_R4[1][0]->SetBinContent(12,0.001365317);
    SysError_DEFAULT_R4[1][0]->SetBinContent(13,0.00119989);
    SysError_DEFAULT_R4[1][0]->SetBinContent(14,0.002572833);
    SysError_DEFAULT_R4[1][0]->SetBinContent(15,0.00467693);
    SysError_DEFAULT_R4[1][0]->SetBinContent(16,0.003227296);
    SysError_DEFAULT_R4[1][0]->SetBinContent(17,0.00236605);
    SysError_DEFAULT_R4[1][0]->SetBinContent(18,0.003018203);
    SysError_DEFAULT_R4[1][0]->SetBinContent(19,0.003700419);
    SysError_DEFAULT_R4[1][0]->SetBinContent(20,0.002699551);
    SysError_DEFAULT_R4[1][0]->SetBinContent(21,483.0167);
    //SysError_DEFAULT_R4[1][0]->SetBinError(21,21.97764);
    //SysError_DEFAULT_R4[1][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[1][0]->SetMaximum(0.005144623);
    //SysError_DEFAULT_R4[1][0]->SetEntries(3907520);
    
    SysError_DEFAULT_R4[2][0]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[2][0]->SetBinContent(1,0.002356675);
    SysError_DEFAULT_R4[2][0]->SetBinContent(2,0.003455041);
    SysError_DEFAULT_R4[2][0]->SetBinContent(3,0.005601607);
    SysError_DEFAULT_R4[2][0]->SetBinContent(4,0.004078886);
    SysError_DEFAULT_R4[2][0]->SetBinContent(5,0.005291596);
    SysError_DEFAULT_R4[2][0]->SetBinContent(6,0.004119438);
    SysError_DEFAULT_R4[2][0]->SetBinContent(7,0.004704844);
    SysError_DEFAULT_R4[2][0]->SetBinContent(8,0.006032911);
    SysError_DEFAULT_R4[2][0]->SetBinContent(9,0.003254926);
    SysError_DEFAULT_R4[2][0]->SetBinContent(10,0.00506231);
    SysError_DEFAULT_R4[2][0]->SetBinContent(11,0.005218493);
    SysError_DEFAULT_R4[2][0]->SetBinContent(12,0.003942352);
    SysError_DEFAULT_R4[2][0]->SetBinContent(13,0.007702647);
    SysError_DEFAULT_R4[2][0]->SetBinContent(14,0.005284828);
    SysError_DEFAULT_R4[2][0]->SetBinContent(15,0.005678302);
    SysError_DEFAULT_R4[2][0]->SetBinContent(16,0.003652618);
    SysError_DEFAULT_R4[2][0]->SetBinContent(17,0.002764975);
    SysError_DEFAULT_R4[2][0]->SetBinContent(18,0.003045711);
    SysError_DEFAULT_R4[2][0]->SetBinContent(19,0.002230136);
    SysError_DEFAULT_R4[2][0]->SetBinContent(20,0.006921939);
    SysError_DEFAULT_R4[2][0]->SetBinContent(21,609.798);
    //SysError_DEFAULT_R4[2][0]->SetBinError(21,24.69409);
    //SysError_DEFAULT_R4[2][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[2][0]->SetMaximum(0.008472912);
    //SysError_DEFAULT_R4[2][0]->SetEntries(3080020);
    
    /// \Run4_DEFAULT_CC0Pi_FGD2
    SysError_DEFAULT_R4[0][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[0][1]->SetBinContent(1,0.000118814);
    SysError_DEFAULT_R4[0][1]->SetBinContent(2,0.0001019706);
    SysError_DEFAULT_R4[0][1]->SetBinContent(3,0.000187264);
    SysError_DEFAULT_R4[0][1]->SetBinContent(4,0.000325463);
    SysError_DEFAULT_R4[0][1]->SetBinContent(5,0.0004518068);
    SysError_DEFAULT_R4[0][1]->SetBinContent(6,0.0003282811);
    SysError_DEFAULT_R4[0][1]->SetBinContent(7,0.0004835712);
    SysError_DEFAULT_R4[0][1]->SetBinContent(8,0.0005811998);
    SysError_DEFAULT_R4[0][1]->SetBinContent(9,0.0006410706);
    SysError_DEFAULT_R4[0][1]->SetBinContent(10,0.000514238);
    SysError_DEFAULT_R4[0][1]->SetBinContent(11,0.0008790253);
    SysError_DEFAULT_R4[0][1]->SetBinContent(12,0.0004851654);
    SysError_DEFAULT_R4[0][1]->SetBinContent(13,0.0004988391);
    SysError_DEFAULT_R4[0][1]->SetBinContent(14,0.001084422);
    SysError_DEFAULT_R4[0][1]->SetBinContent(15,0.0004686599);
    SysError_DEFAULT_R4[0][1]->SetBinContent(16,0.00139421);
    SysError_DEFAULT_R4[0][1]->SetBinContent(17,0.000986329);
    SysError_DEFAULT_R4[0][1]->SetBinContent(18,0.0006383492);
    SysError_DEFAULT_R4[0][1]->SetBinContent(19,0.0007231123);
    SysError_DEFAULT_R4[0][1]->SetBinContent(20,0.001081984);
    SysError_DEFAULT_R4[0][1]->SetBinContent(21,1222.558);
    //SysError_DEFAULT_R4[0][1]->SetBinError(21,34.96509);
    //SysError_DEFAULT_R4[0][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[0][1]->SetMaximum(0.001533631);
    //SysError_DEFAULT_R4[0][1]->SetEntries(1.658902e+007);
   
    SysError_DEFAULT_R4[1][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[1][1]->SetBinContent(1,0.0002473002);
    SysError_DEFAULT_R4[1][1]->SetBinContent(2,0.0006028265);
    SysError_DEFAULT_R4[1][1]->SetBinContent(3,0.0004464251);
    SysError_DEFAULT_R4[1][1]->SetBinContent(4,0.0007456648);
    SysError_DEFAULT_R4[1][1]->SetBinContent(5,0.0006154298);
    SysError_DEFAULT_R4[1][1]->SetBinContent(6,0.0005296715);
    SysError_DEFAULT_R4[1][1]->SetBinContent(7,0.0004169772);
    SysError_DEFAULT_R4[1][1]->SetBinContent(8,0.0005699432);
    SysError_DEFAULT_R4[1][1]->SetBinContent(9,0.0003472638);
    SysError_DEFAULT_R4[1][1]->SetBinContent(10,0.0006901035);
    SysError_DEFAULT_R4[1][1]->SetBinContent(11,0.0006741242);
    SysError_DEFAULT_R4[1][1]->SetBinContent(12,0.0009222578);
    SysError_DEFAULT_R4[1][1]->SetBinContent(13,0.0006342054);
    SysError_DEFAULT_R4[1][1]->SetBinContent(14,0.0009453704);
    SysError_DEFAULT_R4[1][1]->SetBinContent(15,0.0007941147);
    SysError_DEFAULT_R4[1][1]->SetBinContent(16,0.001144984);
    SysError_DEFAULT_R4[1][1]->SetBinContent(17,0.00139453);
    SysError_DEFAULT_R4[1][1]->SetBinContent(18,0.001869539);
    SysError_DEFAULT_R4[1][1]->SetBinContent(19,0.001658512);
    SysError_DEFAULT_R4[1][1]->SetBinContent(20,0.001874294);
    SysError_DEFAULT_R4[1][1]->SetBinContent(21,412.041);
    //SysError_DEFAULT_R4[1][1]->SetBinError(21,20.29879);
    //SysError_DEFAULT_R4[1][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[1][1]->SetMaximum(0.002061723);
    //SysError_DEFAULT_R4[1][1]->SetEntries(3298520);
   
    SysError_DEFAULT_R4[2][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[2][1]->SetBinContent(1,0.0008054923);
    SysError_DEFAULT_R4[2][1]->SetBinContent(2,0.0007823092);
    SysError_DEFAULT_R4[2][1]->SetBinContent(3,0.000745859);
    SysError_DEFAULT_R4[2][1]->SetBinContent(4,0.0009109634);
    SysError_DEFAULT_R4[2][1]->SetBinContent(5,0.0007905444);
    SysError_DEFAULT_R4[2][1]->SetBinContent(6,0.000751837);
    SysError_DEFAULT_R4[2][1]->SetBinContent(7,0.0009194255);
    SysError_DEFAULT_R4[2][1]->SetBinContent(8,0.001032332);
    SysError_DEFAULT_R4[2][1]->SetBinContent(9,0.000929426);
    SysError_DEFAULT_R4[2][1]->SetBinContent(10,0.000637733);
    SysError_DEFAULT_R4[2][1]->SetBinContent(11,0.0008027408);
    SysError_DEFAULT_R4[2][1]->SetBinContent(12,0.0006183544);
    SysError_DEFAULT_R4[2][1]->SetBinContent(13,0.0007576786);
    SysError_DEFAULT_R4[2][1]->SetBinContent(14,0.0007540657);
    SysError_DEFAULT_R4[2][1]->SetBinContent(15,0.0009232546);
    SysError_DEFAULT_R4[2][1]->SetBinContent(16,0.001588549);
    SysError_DEFAULT_R4[2][1]->SetBinContent(17,0.001989251);
    SysError_DEFAULT_R4[2][1]->SetBinContent(18,0.001240929);
    SysError_DEFAULT_R4[2][1]->SetBinContent(19,0.001152267);
    SysError_DEFAULT_R4[2][1]->SetBinContent(20,0.0008573091);
    SysError_DEFAULT_R4[2][1]->SetBinContent(21,653.5795);
    //SysError_DEFAULT_R4[2][1]->SetBinError(21,25.5652);
    //SysError_DEFAULT_R4[2][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[2][1]->SetMaximum(0.002188176);
    //SysError_DEFAULT_R4[2][1]->SetEntries(3029520);
    
    /// \Run4_NEW_CC0Pi_FGD1
    SysError_NEW_R4[0][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[0][0]->SetBinContent(1,0.0007733381);
    SysError_NEW_R4[0][0]->SetBinContent(2,0.0004679288);
    SysError_NEW_R4[0][0]->SetBinContent(3,0.0008347099);
    SysError_NEW_R4[0][0]->SetBinContent(4,0.001009572);
    SysError_NEW_R4[0][0]->SetBinContent(5,0.001267397);
    SysError_NEW_R4[0][0]->SetBinContent(6,0.002217847);
    SysError_NEW_R4[0][0]->SetBinContent(7,0.002172524);
    SysError_NEW_R4[0][0]->SetBinContent(8,0.002237825);
    SysError_NEW_R4[0][0]->SetBinContent(9,0.003065773);
    SysError_NEW_R4[0][0]->SetBinContent(10,0.001898638);
    SysError_NEW_R4[0][0]->SetBinContent(11,0.003319783);
    SysError_NEW_R4[0][0]->SetBinContent(12,0.002377744);
    SysError_NEW_R4[0][0]->SetBinContent(13,0.00365861);
    SysError_NEW_R4[0][0]->SetBinContent(14,0.00510556);
    SysError_NEW_R4[0][0]->SetBinContent(15,0.002338831);
    SysError_NEW_R4[0][0]->SetBinContent(16,0.005098848);
    SysError_NEW_R4[0][0]->SetBinContent(17,0.003511573);
    SysError_NEW_R4[0][0]->SetBinContent(18,0.003420549);
    SysError_NEW_R4[0][0]->SetBinContent(19,0.003519954);
    SysError_NEW_R4[0][0]->SetBinContent(20,0.001771041);
    SysError_NEW_R4[0][0]->SetBinContent(21,1250.12);
    //SysError_NEW_R4[0][0]->SetBinError(21,35.35704);
    //SysError_NEW_R4[0][0]->SetMinimum(0);
    //SysError_NEW_R4[0][0]->SetMaximum(0.005616116);
    //SysError_NEW_R4[0][0]->SetEntries(1.614002e+007);
        
    SysError_NEW_R4[1][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[1][0]->SetBinContent(1,0.0008447658);
    SysError_NEW_R4[1][0]->SetBinContent(2,0.002479387);
    SysError_NEW_R4[1][0]->SetBinContent(3,0.001524458);
    SysError_NEW_R4[1][0]->SetBinContent(4,0.002014106);
    SysError_NEW_R4[1][0]->SetBinContent(5,0.001219198);
    SysError_NEW_R4[1][0]->SetBinContent(6,0.001283503);
    SysError_NEW_R4[1][0]->SetBinContent(7,0.001654658);
    SysError_NEW_R4[1][0]->SetBinContent(8,0.001841309);
    SysError_NEW_R4[1][0]->SetBinContent(9,0.001861882);
    SysError_NEW_R4[1][0]->SetBinContent(10,0.003216634);
    SysError_NEW_R4[1][0]->SetBinContent(11,0.001791881);
    SysError_NEW_R4[1][0]->SetBinContent(12,0.001302812);
    SysError_NEW_R4[1][0]->SetBinContent(13,0.0009789725);
    SysError_NEW_R4[1][0]->SetBinContent(14,0.002630165);
    SysError_NEW_R4[1][0]->SetBinContent(15,0.004712799);
    SysError_NEW_R4[1][0]->SetBinContent(16,0.002912253);
    SysError_NEW_R4[1][0]->SetBinContent(17,0.002278386);
    SysError_NEW_R4[1][0]->SetBinContent(18,0.003450647);
    SysError_NEW_R4[1][0]->SetBinContent(19,0.003770643);
    SysError_NEW_R4[1][0]->SetBinContent(20,0.00227798);
    SysError_NEW_R4[1][0]->SetBinContent(21,482.9382);
    //SysError_NEW_R4[1][0]->SetBinError(21,21.97586);
    //SysError_NEW_R4[1][0]->SetMinimum(0);
    //SysError_NEW_R4[1][0]->SetMaximum(0.005184079);
    //SysError_NEW_R4[1][0]->SetEntries(3907520);
   
    SysError_NEW_R4[2][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[2][0]->SetBinContent(1,0.00228353);
    SysError_NEW_R4[2][0]->SetBinContent(2,0.003248759);
    SysError_NEW_R4[2][0]->SetBinContent(3,0.00520363);
    SysError_NEW_R4[2][0]->SetBinContent(4,0.003850681);
    SysError_NEW_R4[2][0]->SetBinContent(5,0.004935351);
    SysError_NEW_R4[2][0]->SetBinContent(6,0.003740351);
    SysError_NEW_R4[2][0]->SetBinContent(7,0.004343931);
    SysError_NEW_R4[2][0]->SetBinContent(8,0.005602039);
    SysError_NEW_R4[2][0]->SetBinContent(9,0.002976271);
    SysError_NEW_R4[2][0]->SetBinContent(10,0.004790032);
    SysError_NEW_R4[2][0]->SetBinContent(11,0.005119512);
    SysError_NEW_R4[2][0]->SetBinContent(12,0.004058274);
    SysError_NEW_R4[2][0]->SetBinContent(13,0.007652531);
    SysError_NEW_R4[2][0]->SetBinContent(14,0.005289048);
    SysError_NEW_R4[2][0]->SetBinContent(15,0.005258858);
    SysError_NEW_R4[2][0]->SetBinContent(16,0.003284734);
    SysError_NEW_R4[2][0]->SetBinContent(17,0.00288705);
    SysError_NEW_R4[2][0]->SetBinContent(18,0.003262125);
    SysError_NEW_R4[2][0]->SetBinContent(19,0.002238345);
    SysError_NEW_R4[2][0]->SetBinContent(20,0.007672405);
    SysError_NEW_R4[2][0]->SetBinContent(21,609.9259);
    //SysError_NEW_R4[2][0]->SetBinError(21,24.69668);
    //SysError_NEW_R4[2][0]->SetMinimum(0);
    //SysError_NEW_R4[2][0]->SetMaximum(0.008439645);
    //SysError_NEW_R4[2][0]->SetEntries(3080020);
    
    /// \Run4_NEW_CC0Pi_FGD2
    
    SysError_NEW_R4[0][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[0][1]->SetBinContent(1,0.0001487315);
    SysError_NEW_R4[0][1]->SetBinContent(2,0.0001004871);
    SysError_NEW_R4[0][1]->SetBinContent(3,0.0001816444);
    SysError_NEW_R4[0][1]->SetBinContent(4,0.0003242405);
    SysError_NEW_R4[0][1]->SetBinContent(5,0.0004232939);
    SysError_NEW_R4[0][1]->SetBinContent(6,0.0003253433);
    SysError_NEW_R4[0][1]->SetBinContent(7,0.000481831);
    SysError_NEW_R4[0][1]->SetBinContent(8,0.0005361918);
    SysError_NEW_R4[0][1]->SetBinContent(9,0.0005640512);
    SysError_NEW_R4[0][1]->SetBinContent(10,0.0004326179);
    SysError_NEW_R4[0][1]->SetBinContent(11,0.000762516);
    SysError_NEW_R4[0][1]->SetBinContent(12,0.0004952932);
    SysError_NEW_R4[0][1]->SetBinContent(13,0.0004744136);
    SysError_NEW_R4[0][1]->SetBinContent(14,0.0009562361);
    SysError_NEW_R4[0][1]->SetBinContent(15,0.0004307932);
    SysError_NEW_R4[0][1]->SetBinContent(16,0.001205862);
    SysError_NEW_R4[0][1]->SetBinContent(17,0.001537593);
    SysError_NEW_R4[0][1]->SetBinContent(18,0.0006880118);
    SysError_NEW_R4[0][1]->SetBinContent(19,0.0006641621);
    SysError_NEW_R4[0][1]->SetBinContent(20,0.0009047728);
    SysError_NEW_R4[0][1]->SetBinContent(21,1223.243);
    //SysError_NEW_R4[0][1]->SetBinError(21,34.97489);
    //SysError_NEW_R4[0][1]->SetMinimum(0);
    //SysError_NEW_R4[0][1]->SetMaximum(0.001691352);
    //SysError_NEW_R4[0][1]->SetEntries(1.658902e+007);
    
    SysError_NEW_R4[1][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[1][1]->SetBinContent(1,0.0002648236);
    SysError_NEW_R4[1][1]->SetBinContent(2,0.0005275381);
    SysError_NEW_R4[1][1]->SetBinContent(3,0.0005210606);
    SysError_NEW_R4[1][1]->SetBinContent(4,0.0006266679);
    SysError_NEW_R4[1][1]->SetBinContent(5,0.0005112839);
    SysError_NEW_R4[1][1]->SetBinContent(6,0.0005338276);
    SysError_NEW_R4[1][1]->SetBinContent(7,0.00033918);
    SysError_NEW_R4[1][1]->SetBinContent(8,0.0005001142);
    SysError_NEW_R4[1][1]->SetBinContent(9,0.0003326876);
    SysError_NEW_R4[1][1]->SetBinContent(10,0.0005282571);
    SysError_NEW_R4[1][1]->SetBinContent(11,0.0006036922);
    SysError_NEW_R4[1][1]->SetBinContent(12,0.001001037);
    SysError_NEW_R4[1][1]->SetBinContent(13,0.0005869855);
    SysError_NEW_R4[1][1]->SetBinContent(14,0.0007558121);
    SysError_NEW_R4[1][1]->SetBinContent(15,0.0008827251);
    SysError_NEW_R4[1][1]->SetBinContent(16,0.001004716);
    SysError_NEW_R4[1][1]->SetBinContent(17,0.001064935);
    SysError_NEW_R4[1][1]->SetBinContent(18,0.001443099);
    SysError_NEW_R4[1][1]->SetBinContent(19,0.001389467);
    SysError_NEW_R4[1][1]->SetBinContent(20,0.001396497);
    SysError_NEW_R4[1][1]->SetBinContent(21,412.1115);
    //SysError_NEW_R4[1][1]->SetBinError(21,20.30053);
    //SysError_NEW_R4[1][1]->SetMinimum(0);
    //SysError_NEW_R4[1][1]->SetMaximum(0.001587409);
    //SysError_NEW_R4[1][1]->SetEntries(3298520);
    
    SysError_NEW_R4[2][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[2][1]->SetBinContent(1,0.0006620744);
    SysError_NEW_R4[2][1]->SetBinContent(2,0.000684615);
    SysError_NEW_R4[2][1]->SetBinContent(3,0.0005905124);
    SysError_NEW_R4[2][1]->SetBinContent(4,0.0007020922);
    SysError_NEW_R4[2][1]->SetBinContent(5,0.000615451);
    SysError_NEW_R4[2][1]->SetBinContent(6,0.0007227387);
    SysError_NEW_R4[2][1]->SetBinContent(7,0.0008006592);
    SysError_NEW_R4[2][1]->SetBinContent(8,0.0008184573);
    SysError_NEW_R4[2][1]->SetBinContent(9,0.001013722);
    SysError_NEW_R4[2][1]->SetBinContent(10,0.0006364228);
    SysError_NEW_R4[2][1]->SetBinContent(11,0.0007030864);
    SysError_NEW_R4[2][1]->SetBinContent(12,0.0007714378);
    SysError_NEW_R4[2][1]->SetBinContent(13,0.0007969852);
    SysError_NEW_R4[2][1]->SetBinContent(14,0.0007285565);
    SysError_NEW_R4[2][1]->SetBinContent(15,0.0007545232);
    SysError_NEW_R4[2][1]->SetBinContent(16,0.001251848);
    SysError_NEW_R4[2][1]->SetBinContent(17,0.001573173);
    SysError_NEW_R4[2][1]->SetBinContent(18,0.00106064);
    SysError_NEW_R4[2][1]->SetBinContent(19,0.001261456);
    SysError_NEW_R4[2][1]->SetBinContent(20,0.0007753882);
    SysError_NEW_R4[2][1]->SetBinContent(21,652.5986);
    //SysError_NEW_R4[2][1]->SetBinError(21,25.54601);
    //SysError_NEW_R4[2][1]->SetMinimum(0);
    //SysError_NEW_R4[2][1]->SetMaximum(0.001730491);
    //SysError_NEW_R4[2][1]->SetEntries(3029520);
    
    /// \Run7_DEFAULT_CC0Pi_FGD1
    SysError_DEFAULT_R7[0][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[0][0]->SetBinContent(1,0.0008797546);
    SysError_DEFAULT_R7[0][0]->SetBinContent(2,0.0002810438);
    SysError_DEFAULT_R7[0][0]->SetBinContent(3,0.0003304125);
    SysError_DEFAULT_R7[0][0]->SetBinContent(4,0.0006581018);
    SysError_DEFAULT_R7[0][0]->SetBinContent(5,0.0007855498);
    SysError_DEFAULT_R7[0][0]->SetBinContent(6,0.0008524142);
    SysError_DEFAULT_R7[0][0]->SetBinContent(7,0.0008878162);
    SysError_DEFAULT_R7[0][0]->SetBinContent(8,0.0006083222);
    SysError_DEFAULT_R7[0][0]->SetBinContent(9,0.001407185);
    SysError_DEFAULT_R7[0][0]->SetBinContent(10,0.002185375);
    SysError_DEFAULT_R7[0][0]->SetBinContent(11,0.002226612);
    SysError_DEFAULT_R7[0][0]->SetBinContent(12,0.002079698);
    SysError_DEFAULT_R7[0][0]->SetBinContent(13,0.001084772);
    SysError_DEFAULT_R7[0][0]->SetBinContent(14,0.004343353);
    SysError_DEFAULT_R7[0][0]->SetBinContent(15,0.003728277);
    SysError_DEFAULT_R7[0][0]->SetBinContent(16,0.003335726);
    SysError_DEFAULT_R7[0][0]->SetBinContent(17,0.002269999);
    SysError_DEFAULT_R7[0][0]->SetBinContent(18,0.001527762);
    SysError_DEFAULT_R7[0][0]->SetBinContent(19,0.0009853197);
    SysError_DEFAULT_R7[0][0]->SetBinContent(20,0.002517252);
    SysError_DEFAULT_R7[0][0]->SetBinContent(21,319.6275);
    //SysError_DEFAULT_R7[0][0]->SetBinError(21,17.87813);
    //SysError_DEFAULT_R7[0][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[0][0]->SetMaximum(0.004777688);
    //SysError_DEFAULT_R7[0][0]->SetEntries(4978020);
    
    SysError_DEFAULT_R7[1][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[1][0]->SetBinContent(1,0.01999868);
    SysError_DEFAULT_R7[1][0]->SetBinContent(2,0.006129469);
    SysError_DEFAULT_R7[1][0]->SetBinContent(3,0.001514378);
    SysError_DEFAULT_R7[1][0]->SetBinContent(4,0.00652789);
    SysError_DEFAULT_R7[1][0]->SetBinContent(5,0.003530372);
    SysError_DEFAULT_R7[1][0]->SetBinContent(6,0.002663696);
    SysError_DEFAULT_R7[1][0]->SetBinContent(7,0.001717799);
    SysError_DEFAULT_R7[1][0]->SetBinContent(8,0.002743309);
    SysError_DEFAULT_R7[1][0]->SetBinContent(9,0.002742724);
    SysError_DEFAULT_R7[1][0]->SetBinContent(10,0.004592235);
    SysError_DEFAULT_R7[1][0]->SetBinContent(11,0.003299203);
    SysError_DEFAULT_R7[1][0]->SetBinContent(12,0.002352749);
    SysError_DEFAULT_R7[1][0]->SetBinContent(13,0.004750125);
    SysError_DEFAULT_R7[1][0]->SetBinContent(14,0.00399087);
    SysError_DEFAULT_R7[1][0]->SetBinContent(15,0.007036058);
    SysError_DEFAULT_R7[1][0]->SetBinContent(16,0.01021558);
    SysError_DEFAULT_R7[1][0]->SetBinContent(17,0.003226834);
    SysError_DEFAULT_R7[1][0]->SetBinContent(18,0.004170619);
    SysError_DEFAULT_R7[1][0]->SetBinContent(19,0.01087276);
    SysError_DEFAULT_R7[1][0]->SetBinContent(20,0.009899047);
    SysError_DEFAULT_R7[1][0]->SetBinContent(21,55.95016);
    //SysError_DEFAULT_R7[1][0]->SetBinError(21,7.479984);
    //SysError_DEFAULT_R7[1][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[1][0]->SetMaximum(0.02199854);
    //SysError_DEFAULT_R7[1][0]->SetEntries(406020);
    
    SysError_DEFAULT_R7[2][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[2][0]->SetBinContent(1,0.001337085);
    SysError_DEFAULT_R7[2][0]->SetBinContent(2,0.00198247);
    SysError_DEFAULT_R7[2][0]->SetBinContent(3,0.002985663);
    SysError_DEFAULT_R7[2][0]->SetBinContent(4,0.002627678);
    SysError_DEFAULT_R7[2][0]->SetBinContent(5,0.002307287);
    SysError_DEFAULT_R7[2][0]->SetBinContent(6,0.004400892);
    SysError_DEFAULT_R7[2][0]->SetBinContent(7,0.001555252);
    SysError_DEFAULT_R7[2][0]->SetBinContent(8,0.002192906);
    SysError_DEFAULT_R7[2][0]->SetBinContent(9,0.003467611);
    SysError_DEFAULT_R7[2][0]->SetBinContent(10,0.004201416);
    SysError_DEFAULT_R7[2][0]->SetBinContent(11,0.001375143);
    SysError_DEFAULT_R7[2][0]->SetBinContent(12,0.003412299);
    SysError_DEFAULT_R7[2][0]->SetBinContent(13,0.007874682);
    SysError_DEFAULT_R7[2][0]->SetBinContent(14,0.002680101);
    SysError_DEFAULT_R7[2][0]->SetBinContent(15,0.006065128);
    SysError_DEFAULT_R7[2][0]->SetBinContent(16,0.003253701);
    SysError_DEFAULT_R7[2][0]->SetBinContent(17,0.008173503);
    SysError_DEFAULT_R7[2][0]->SetBinContent(18,0.01120629);
    SysError_DEFAULT_R7[2][0]->SetBinContent(19,0.01293144);
    SysError_DEFAULT_R7[2][0]->SetBinContent(20,0.003608535);
    SysError_DEFAULT_R7[2][0]->SetBinContent(21,142.7661);
    //SysError_DEFAULT_R7[2][0]->SetBinError(21,11.94848);
    //SysError_DEFAULT_R7[2][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[2][0]->SetMaximum(0.01422458);
    //SysError_DEFAULT_R7[2][0]->SetEntries(759520);
    
    
    /// \Run7_NEW_CC0Pi_FGD1
    SysError_NEW_R7[0][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[0][0]->SetBinContent(1,0.0007089464);
    SysError_NEW_R7[0][0]->SetBinContent(2,0.0002457303);
    SysError_NEW_R7[0][0]->SetBinContent(3,0.0003350788);
    SysError_NEW_R7[0][0]->SetBinContent(4,0.0006737451);
    SysError_NEW_R7[0][0]->SetBinContent(5,0.0007033108);
    SysError_NEW_R7[0][0]->SetBinContent(6,0.0007713517);
    SysError_NEW_R7[0][0]->SetBinContent(7,0.0008295593);
    SysError_NEW_R7[0][0]->SetBinContent(8,0.0006238002);
    SysError_NEW_R7[0][0]->SetBinContent(9,0.001334896);
    SysError_NEW_R7[0][0]->SetBinContent(10,0.001622645);
    SysError_NEW_R7[0][0]->SetBinContent(11,0.001892033);
    SysError_NEW_R7[0][0]->SetBinContent(12,0.001928215);
    SysError_NEW_R7[0][0]->SetBinContent(13,0.001019338);
    SysError_NEW_R7[0][0]->SetBinContent(14,0.003633392);
    SysError_NEW_R7[0][0]->SetBinContent(15,0.003485402);
    SysError_NEW_R7[0][0]->SetBinContent(16,0.003064763);
    SysError_NEW_R7[0][0]->SetBinContent(17,0.002217612);
    SysError_NEW_R7[0][0]->SetBinContent(18,0.001432555);
    SysError_NEW_R7[0][0]->SetBinContent(19,0.0008413245);
    SysError_NEW_R7[0][0]->SetBinContent(20,0.002105646);
    SysError_NEW_R7[0][0]->SetBinContent(21,315.8002);
    //SysError_NEW_R7[0][0]->SetBinError(21,17.77077);
    //SysError_NEW_R7[0][0]->SetMinimum(0);
    //SysError_NEW_R7[0][0]->SetMaximum(0.003996731);
    //SysError_NEW_R7[0][0]->SetEntries(4956520);

    SysError_NEW_R7[1][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[1][0]->SetBinContent(1,0.02108225);
    SysError_NEW_R7[1][0]->SetBinContent(2,0.006619525);
    SysError_NEW_R7[1][0]->SetBinContent(3,0.001425254);
    SysError_NEW_R7[1][0]->SetBinContent(4,0.006536037);
    SysError_NEW_R7[1][0]->SetBinContent(5,0.003248705);
    SysError_NEW_R7[1][0]->SetBinContent(6,0.002554589);
    SysError_NEW_R7[1][0]->SetBinContent(7,0.00148874);
    SysError_NEW_R7[1][0]->SetBinContent(8,0.003056412);
    SysError_NEW_R7[1][0]->SetBinContent(9,0.003100468);
    SysError_NEW_R7[1][0]->SetBinContent(10,0.004631004);
    SysError_NEW_R7[1][0]->SetBinContent(11,0.005055691);
    SysError_NEW_R7[1][0]->SetBinContent(12,0.002179501);
    SysError_NEW_R7[1][0]->SetBinContent(13,0.004623545);
    SysError_NEW_R7[1][0]->SetBinContent(14,0.003254741);
    SysError_NEW_R7[1][0]->SetBinContent(15,0.007837271);
    SysError_NEW_R7[1][0]->SetBinContent(16,0.008932005);
    SysError_NEW_R7[1][0]->SetBinContent(17,0.003603953);
    SysError_NEW_R7[1][0]->SetBinContent(18,0.003638419);
    SysError_NEW_R7[1][0]->SetBinContent(19,0.01138229);
    SysError_NEW_R7[1][0]->SetBinContent(20,0.007834678);
    SysError_NEW_R7[1][0]->SetBinContent(21,55.94262);
    //SysError_NEW_R7[1][0]->SetBinError(21,7.47948);
    //SysError_NEW_R7[1][0]->SetMinimum(0);
    //SysError_NEW_R7[1][0]->SetMaximum(0.02319048);
    //SysError_NEW_R7[1][0]->SetEntries(404520);

    SysError_NEW_R7[2][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[2][0]->SetBinContent(1,0.00115099);
    SysError_NEW_R7[2][0]->SetBinContent(2,0.00177259);
    SysError_NEW_R7[2][0]->SetBinContent(3,0.003050071);
    SysError_NEW_R7[2][0]->SetBinContent(4,0.002501487);
    SysError_NEW_R7[2][0]->SetBinContent(5,0.002144954);
    SysError_NEW_R7[2][0]->SetBinContent(6,0.004098802);
    SysError_NEW_R7[2][0]->SetBinContent(7,0.002134123);
    SysError_NEW_R7[2][0]->SetBinContent(8,0.002073543);
    SysError_NEW_R7[2][0]->SetBinContent(9,0.00344798);
    SysError_NEW_R7[2][0]->SetBinContent(10,0.004135997);
    SysError_NEW_R7[2][0]->SetBinContent(11,0.00113937);
    SysError_NEW_R7[2][0]->SetBinContent(12,0.003726227);
    SysError_NEW_R7[2][0]->SetBinContent(13,0.007656217);
    SysError_NEW_R7[2][0]->SetBinContent(14,0.002881005);
    SysError_NEW_R7[2][0]->SetBinContent(15,0.005690297);
    SysError_NEW_R7[2][0]->SetBinContent(16,0.004056588);
    SysError_NEW_R7[2][0]->SetBinContent(17,0.008917155);
    SysError_NEW_R7[2][0]->SetBinContent(18,0.01149726);
    SysError_NEW_R7[2][0]->SetBinContent(19,0.01111047);
    SysError_NEW_R7[2][0]->SetBinContent(20,0.003823722);
    SysError_NEW_R7[2][0]->SetBinContent(21,142.7813);
    //SysError_NEW_R7[2][0]->SetBinError(21,11.94911);
    //SysError_NEW_R7[2][0]->SetMinimum(0);
    //SysError_NEW_R7[2][0]->SetMaximum(0.01264698);
    //SysError_NEW_R7[2][0]->SetEntries(758020);
    

    /// \Run7_ANTY_CC0Pi_FGD1
    SysError_ANTY_R7[0][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[0][0]->SetBinContent(1,0.0003524796);
    SysError_ANTY_R7[0][0]->SetBinContent(2,9.862004e-005);
    SysError_ANTY_R7[0][0]->SetBinContent(3,0.0001372521);
    SysError_ANTY_R7[0][0]->SetBinContent(4,0.0001917833);
    SysError_ANTY_R7[0][0]->SetBinContent(5,0.0002072148);
    SysError_ANTY_R7[0][0]->SetBinContent(6,0.0003137894);
    SysError_ANTY_R7[0][0]->SetBinContent(7,0.0003924453);
    SysError_ANTY_R7[0][0]->SetBinContent(8,0.0003340002);
    SysError_ANTY_R7[0][0]->SetBinContent(9,0.0005234744);
    SysError_ANTY_R7[0][0]->SetBinContent(10,0.0005254297);
    SysError_ANTY_R7[0][0]->SetBinContent(11,0.0005680501);
    SysError_ANTY_R7[0][0]->SetBinContent(12,0.0007118863);
    SysError_ANTY_R7[0][0]->SetBinContent(13,0.0005156606);
    SysError_ANTY_R7[0][0]->SetBinContent(14,0.0008558279);
    SysError_ANTY_R7[0][0]->SetBinContent(15,0.001334159);
    SysError_ANTY_R7[0][0]->SetBinContent(16,0.0008296622);
    SysError_ANTY_R7[0][0]->SetBinContent(17,0.0007935359);
    SysError_ANTY_R7[0][0]->SetBinContent(18,0.0008659553);
    SysError_ANTY_R7[0][0]->SetBinContent(19,0.0003823039);
    SysError_ANTY_R7[0][0]->SetBinContent(20,0.0005249489);
    SysError_ANTY_R7[0][0]->SetBinContent(21,316.013);
    //SysError_ANTY_R7[0][0]->SetBinError(21,17.77675);
    //SysError_ANTY_R7[0][0]->SetMinimum(0);
    //SysError_ANTY_R7[0][0]->SetMaximum(0.001467575);
    //SysError_ANTY_R7[0][0]->SetEntries(4956520);
   

    SysError_ANTY_R7[1][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[1][0]->SetBinContent(1,0.006908389);
    SysError_ANTY_R7[1][0]->SetBinContent(2,0.002417919);
    SysError_ANTY_R7[1][0]->SetBinContent(3,0.0008027454);
    SysError_ANTY_R7[1][0]->SetBinContent(4,0.00185773);
    SysError_ANTY_R7[1][0]->SetBinContent(5,0.001256205);
    SysError_ANTY_R7[1][0]->SetBinContent(6,0.0007446394);
    SysError_ANTY_R7[1][0]->SetBinContent(7,0.0006517333);
    SysError_ANTY_R7[1][0]->SetBinContent(8,0.001173971);
    SysError_ANTY_R7[1][0]->SetBinContent(9,0.001234057);
    SysError_ANTY_R7[1][0]->SetBinContent(10,0.001482566);
    SysError_ANTY_R7[1][0]->SetBinContent(11,0.001720223);
    SysError_ANTY_R7[1][0]->SetBinContent(12,0.001247867);
    SysError_ANTY_R7[1][0]->SetBinContent(13,0.001352011);
    SysError_ANTY_R7[1][0]->SetBinContent(14,0.000564295);
    SysError_ANTY_R7[1][0]->SetBinContent(15,0.003056127);
    SysError_ANTY_R7[1][0]->SetBinContent(16,0.002163381);
    SysError_ANTY_R7[1][0]->SetBinContent(17,0.001551901);
    SysError_ANTY_R7[1][0]->SetBinContent(18,0.0008317097);
    SysError_ANTY_R7[1][0]->SetBinContent(19,0.003685102);
    SysError_ANTY_R7[1][0]->SetBinContent(20,0.00360041);
    SysError_ANTY_R7[1][0]->SetBinContent(21,55.95895);
    //SysError_ANTY_R7[1][0]->SetBinError(21,7.480572);
    //SysError_ANTY_R7[1][0]->SetMinimum(0);
    //SysError_ANTY_R7[1][0]->SetMaximum(0.007599228);
    //SysError_ANTY_R7[1][0]->SetEntries(404520);

    SysError_ANTY_R7[2][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[2][0]->SetBinContent(1,0.0005467686);
    SysError_ANTY_R7[2][0]->SetBinContent(2,0.0005231592);
    SysError_ANTY_R7[2][0]->SetBinContent(3,0.0008698321);
    SysError_ANTY_R7[2][0]->SetBinContent(4,0.0008822553);
    SysError_ANTY_R7[2][0]->SetBinContent(5,0.0008814769);
    SysError_ANTY_R7[2][0]->SetBinContent(6,0.001610907);
    SysError_ANTY_R7[2][0]->SetBinContent(7,0.001069965);
    SysError_ANTY_R7[2][0]->SetBinContent(8,0.000687239);
    SysError_ANTY_R7[2][0]->SetBinContent(9,0.001152929);
    SysError_ANTY_R7[2][0]->SetBinContent(10,0.001539138);
    SysError_ANTY_R7[2][0]->SetBinContent(11,0.0006095654);
    SysError_ANTY_R7[2][0]->SetBinContent(12,0.001455055);
    SysError_ANTY_R7[2][0]->SetBinContent(13,0.00211178);
    SysError_ANTY_R7[2][0]->SetBinContent(14,0.001480212);
    SysError_ANTY_R7[2][0]->SetBinContent(15,0.001951553);
    SysError_ANTY_R7[2][0]->SetBinContent(16,0.001975351);
    SysError_ANTY_R7[2][0]->SetBinContent(17,0.003046883);
    SysError_ANTY_R7[2][0]->SetBinContent(18,0.004368895);
    SysError_ANTY_R7[2][0]->SetBinContent(19,0.003379202);
    SysError_ANTY_R7[2][0]->SetBinContent(20,0.001577497);
    SysError_ANTY_R7[2][0]->SetBinContent(21,141.8936);
    //SysError_ANTY_R7[2][0]->SetBinError(21,11.91191);
    //SysError_ANTY_R7[2][0]->SetMinimum(0);
    //SysError_ANTY_R7[2][0]->SetMaximum(0.004805784);
    //SysError_ANTY_R7[2][0]->SetEntries(758020);
    
    /// \Run7_PI-_CC0Pi_FGD1
    SysError_PI_R7[0][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[0][0]->SetBinContent(1,0.0004189578);
    SysError_PI_R7[0][0]->SetBinContent(2,0.0001056276);
    SysError_PI_R7[0][0]->SetBinContent(3,0.000119599);
    SysError_PI_R7[0][0]->SetBinContent(4,0.0001830223);
    SysError_PI_R7[0][0]->SetBinContent(5,0.0002184539);
    SysError_PI_R7[0][0]->SetBinContent(6,0.0003145205);
    SysError_PI_R7[0][0]->SetBinContent(7,0.0004091319);
    SysError_PI_R7[0][0]->SetBinContent(8,0.0003629741);
    SysError_PI_R7[0][0]->SetBinContent(9,0.0005126471);
    SysError_PI_R7[0][0]->SetBinContent(10,0.0005788554);
    SysError_PI_R7[0][0]->SetBinContent(11,0.0005679315);
    SysError_PI_R7[0][0]->SetBinContent(12,0.0006986166);
    SysError_PI_R7[0][0]->SetBinContent(13,0.0005347308);
    SysError_PI_R7[0][0]->SetBinContent(14,0.0008577252);
    SysError_PI_R7[0][0]->SetBinContent(15,0.001407726);
    SysError_PI_R7[0][0]->SetBinContent(16,0.0008388201);
    SysError_PI_R7[0][0]->SetBinContent(17,0.0008117346);
    SysError_PI_R7[0][0]->SetBinContent(18,0.0009013437);
    SysError_PI_R7[0][0]->SetBinContent(19,0.0004029793);
    SysError_PI_R7[0][0]->SetBinContent(20,0.0005211802);
    SysError_PI_R7[0][0]->SetBinContent(21,315.978);
    //SysError_PI_R7[0][0]->SetBinError(21,17.77577);
    //SysError_PI_R7[0][0]->SetMinimum(0);
    //SysError_PI_R7[0][0]->SetMaximum(0.001548499);
    //SysError_PI_R7[0][0]->SetEntries(4956520);

    SysError_PI_R7[1][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[1][0]->SetBinContent(1,0.007856382);
    SysError_PI_R7[1][0]->SetBinContent(2,0.002569927);
    SysError_PI_R7[1][0]->SetBinContent(3,0.0008094968);
    SysError_PI_R7[1][0]->SetBinContent(4,0.00181936);
    SysError_PI_R7[1][0]->SetBinContent(5,0.00140112);
    SysError_PI_R7[1][0]->SetBinContent(6,0.0007758759);
    SysError_PI_R7[1][0]->SetBinContent(7,0.0007260846);
    SysError_PI_R7[1][0]->SetBinContent(8,0.0009718906);
    SysError_PI_R7[1][0]->SetBinContent(9,0.001293525);
    SysError_PI_R7[1][0]->SetBinContent(10,0.00158732);
    SysError_PI_R7[1][0]->SetBinContent(11,0.001475476);
    SysError_PI_R7[1][0]->SetBinContent(12,0.001293859);
    SysError_PI_R7[1][0]->SetBinContent(13,0.001330706);
    SysError_PI_R7[1][0]->SetBinContent(14,0.0005575549);
    SysError_PI_R7[1][0]->SetBinContent(15,0.003191046);
    SysError_PI_R7[1][0]->SetBinContent(16,0.002218067);
    SysError_PI_R7[1][0]->SetBinContent(17,0.001299266);
    SysError_PI_R7[1][0]->SetBinContent(18,0.0009330099);
    SysError_PI_R7[1][0]->SetBinContent(19,0.003794521);
    SysError_PI_R7[1][0]->SetBinContent(20,0.003977335);
    SysError_PI_R7[1][0]->SetBinContent(21,55.95666);
    //SysError_PI_R7[1][0]->SetBinError(21,7.480418);
    //SysError_PI_R7[1][0]->SetMinimum(0);
    //SysError_PI_R7[1][0]->SetMaximum(0.00864202);
    //SysError_PI_R7[1][0]->SetEntries(404520);

    SysError_PI_R7[2][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[2][0]->SetBinContent(1,0.0007023712);
    SysError_PI_R7[2][0]->SetBinContent(2,0.0005335459);
    SysError_PI_R7[2][0]->SetBinContent(3,0.0008449281);
    SysError_PI_R7[2][0]->SetBinContent(4,0.0008949309);
    SysError_PI_R7[2][0]->SetBinContent(5,0.00091366);
    SysError_PI_R7[2][0]->SetBinContent(6,0.001702983);
    SysError_PI_R7[2][0]->SetBinContent(7,0.001194728);
    SysError_PI_R7[2][0]->SetBinContent(8,0.000680451);
    SysError_PI_R7[2][0]->SetBinContent(9,0.001230224);
    SysError_PI_R7[2][0]->SetBinContent(10,0.001563502);
    SysError_PI_R7[2][0]->SetBinContent(11,0.000663424);
    SysError_PI_R7[2][0]->SetBinContent(12,0.001322121);
    SysError_PI_R7[2][0]->SetBinContent(13,0.002119785);
    SysError_PI_R7[2][0]->SetBinContent(14,0.001439308);
    SysError_PI_R7[2][0]->SetBinContent(15,0.002045791);
    SysError_PI_R7[2][0]->SetBinContent(16,0.00188717);
    SysError_PI_R7[2][0]->SetBinContent(17,0.003489534);
    SysError_PI_R7[2][0]->SetBinContent(18,0.004185208);
    SysError_PI_R7[2][0]->SetBinContent(19,0.003508385);
    SysError_PI_R7[2][0]->SetBinContent(20,0.001826132);
    SysError_PI_R7[2][0]->SetBinContent(21,141.7889);
    //SysError_PI_R7[2][0]->SetBinError(21,11.90751);
    //SysError_PI_R7[2][0]->SetMinimum(0);
    //SysError_PI_R7[2][0]->SetMaximum(0.004603728);
    //SysError_PI_R7[2][0]->SetEntries(758020);
    
    /// \Run7_DEFAULT_CC0Pi_FGD2
    SysError_DEFAULT_R7[0][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[0][1]->SetBinContent(1,0.0001900113);
    SysError_DEFAULT_R7[0][1]->SetBinContent(2,0.0001497905);
    SysError_DEFAULT_R7[0][1]->SetBinContent(3,3.782125e-005);
    SysError_DEFAULT_R7[0][1]->SetBinContent(4,0.0001191899);
    SysError_DEFAULT_R7[0][1]->SetBinContent(5,0.0001345883);
    SysError_DEFAULT_R7[0][1]->SetBinContent(6,0.0003024027);
    SysError_DEFAULT_R7[0][1]->SetBinContent(7,0.0002789752);
    SysError_DEFAULT_R7[0][1]->SetBinContent(8,0.0001414934);
    SysError_DEFAULT_R7[0][1]->SetBinContent(9,0.0004525033);
    SysError_DEFAULT_R7[0][1]->SetBinContent(10,0.0005896608);
    SysError_DEFAULT_R7[0][1]->SetBinContent(11,0.0004988223);
    SysError_DEFAULT_R7[0][1]->SetBinContent(12,0.0002836058);
    SysError_DEFAULT_R7[0][1]->SetBinContent(13,0.0004361996);
    SysError_DEFAULT_R7[0][1]->SetBinContent(14,0.0007023429);
    SysError_DEFAULT_R7[0][1]->SetBinContent(15,0.0004435079);
    SysError_DEFAULT_R7[0][1]->SetBinContent(16,0.001046068);
    SysError_DEFAULT_R7[0][1]->SetBinContent(17,0.001097176);
    SysError_DEFAULT_R7[0][1]->SetBinContent(18,0.001639715);
    SysError_DEFAULT_R7[0][1]->SetBinContent(19,0.0009375587);
    SysError_DEFAULT_R7[0][1]->SetBinContent(20,0.0008815489);
    SysError_DEFAULT_R7[0][1]->SetBinContent(21,271.8579);
    //SysError_DEFAULT_R7[0][1]->SetBinError(21,16.48811);
    //SysError_DEFAULT_R7[0][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[0][1]->SetMaximum(0.001803686);
    //SysError_DEFAULT_R7[0][1]->SetEntries(4649020);
    
    SysError_DEFAULT_R7[1][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[1][1]->SetBinContent(1,0.006418461);
    SysError_DEFAULT_R7[1][1]->SetBinContent(2,0.002056716);
    SysError_DEFAULT_R7[1][1]->SetBinContent(3,0.0009117537);
    SysError_DEFAULT_R7[1][1]->SetBinContent(4,0.0009473729);
    SysError_DEFAULT_R7[1][1]->SetBinContent(5,0.0009898521);
    SysError_DEFAULT_R7[1][1]->SetBinContent(6,0.001396757);
    SysError_DEFAULT_R7[1][1]->SetBinContent(7,0.001105031);
    SysError_DEFAULT_R7[1][1]->SetBinContent(8,0.001097415);
    SysError_DEFAULT_R7[1][1]->SetBinContent(9,0.001370135);
    SysError_DEFAULT_R7[1][1]->SetBinContent(10,0.0008224992);
    SysError_DEFAULT_R7[1][1]->SetBinContent(11,0.001904979);
    SysError_DEFAULT_R7[1][1]->SetBinContent(12,0.001393446);
    SysError_DEFAULT_R7[1][1]->SetBinContent(13,0.001053947);
    SysError_DEFAULT_R7[1][1]->SetBinContent(14,0.0007949454);
    SysError_DEFAULT_R7[1][1]->SetBinContent(15,0.0007076604);
    SysError_DEFAULT_R7[1][1]->SetBinContent(16,0.002473731);
    SysError_DEFAULT_R7[1][1]->SetBinContent(17,0.0004963908);
    SysError_DEFAULT_R7[1][1]->SetBinContent(18,0.0008094422);
    SysError_DEFAULT_R7[1][1]->SetBinContent(19,6.661338e-016);
    SysError_DEFAULT_R7[1][1]->SetBinContent(20,0.0006453065);
    SysError_DEFAULT_R7[1][1]->SetBinContent(21,44.99788);
    //SysError_DEFAULT_R7[1][1]->SetBinError(21,6.708046);
    //SysError_DEFAULT_R7[1][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[1][1]->SetMaximum(0.007060307);
    //SysError_DEFAULT_R7[1][1]->SetEntries(367020);
    
    SysError_DEFAULT_R7[2][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[2][1]->SetBinContent(1,0.0001577616);
    SysError_DEFAULT_R7[2][1]->SetBinContent(2,0.0002995979);
    SysError_DEFAULT_R7[2][1]->SetBinContent(3,0.0004860798);
    SysError_DEFAULT_R7[2][1]->SetBinContent(4,0.0009369704);
    SysError_DEFAULT_R7[2][1]->SetBinContent(5,0.0006723513);
    SysError_DEFAULT_R7[2][1]->SetBinContent(6,0.0005136315);
    SysError_DEFAULT_R7[2][1]->SetBinContent(7,0.001025008);
    SysError_DEFAULT_R7[2][1]->SetBinContent(8,0.0005674304);
    SysError_DEFAULT_R7[2][1]->SetBinContent(9,0.001230268);
    SysError_DEFAULT_R7[2][1]->SetBinContent(10,0.0003342109);
    SysError_DEFAULT_R7[2][1]->SetBinContent(11,0.00087597);
    SysError_DEFAULT_R7[2][1]->SetBinContent(12,0.001238426);
    SysError_DEFAULT_R7[2][1]->SetBinContent(13,0.001052726);
    SysError_DEFAULT_R7[2][1]->SetBinContent(14,0.003385154);
    SysError_DEFAULT_R7[2][1]->SetBinContent(15,0.0007278066);
    SysError_DEFAULT_R7[2][1]->SetBinContent(16,0.0006392592);
    SysError_DEFAULT_R7[2][1]->SetBinContent(17,0.001192142);
    SysError_DEFAULT_R7[2][1]->SetBinContent(18,0.001860014);
    SysError_DEFAULT_R7[2][1]->SetBinContent(19,0.002576129);
    SysError_DEFAULT_R7[2][1]->SetBinContent(20,0.001637351);
    SysError_DEFAULT_R7[2][1]->SetBinContent(21,171.0061);
    //SysError_DEFAULT_R7[2][1]->SetBinError(21,13.07693);
    //SysError_DEFAULT_R7[2][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[2][1]->SetMaximum(0.00372367);
    //SysError_DEFAULT_R7[2][1]->SetEntries(659520);
    
    
    /// \Run7_NEW_CC0Pi_FGD2
    SysError_NEW_R7[0][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[0][1]->SetBinContent(1,0.0001524046);
    SysError_NEW_R7[0][1]->SetBinContent(2,0.0001130657);
    SysError_NEW_R7[0][1]->SetBinContent(3,3.648108e-005);
    SysError_NEW_R7[0][1]->SetBinContent(4,0.0001029965);
    SysError_NEW_R7[0][1]->SetBinContent(5,0.0002068633);
    SysError_NEW_R7[0][1]->SetBinContent(6,0.0002610323);
    SysError_NEW_R7[0][1]->SetBinContent(7,0.0003541744);
    SysError_NEW_R7[0][1]->SetBinContent(8,0.0001879328);
    SysError_NEW_R7[0][1]->SetBinContent(9,0.0006310291);
    SysError_NEW_R7[0][1]->SetBinContent(10,0.0005759119);
    SysError_NEW_R7[0][1]->SetBinContent(11,0.0006203908);
    SysError_NEW_R7[0][1]->SetBinContent(12,0.0003517895);
    SysError_NEW_R7[0][1]->SetBinContent(13,0.0003452086);
    SysError_NEW_R7[0][1]->SetBinContent(14,0.0005151576);
    SysError_NEW_R7[0][1]->SetBinContent(15,0.000414396);
    SysError_NEW_R7[0][1]->SetBinContent(16,0.0009279693);
    SysError_NEW_R7[0][1]->SetBinContent(17,0.001644511);
    SysError_NEW_R7[0][1]->SetBinContent(18,0.002148771);
    SysError_NEW_R7[0][1]->SetBinContent(19,0.0007400018);
    SysError_NEW_R7[0][1]->SetBinContent(20,0.001326198);
    SysError_NEW_R7[0][1]->SetBinContent(21,272.0347);
    //SysError_NEW_R7[0][1]->SetBinError(21,16.49347);
    //SysError_NEW_R7[0][1]->SetMinimum(0);
    //SysError_NEW_R7[0][1]->SetMaximum(0.002363648);
    //SysError_NEW_R7[0][1]->SetEntries(4649020);
   
    SysError_NEW_R7[1][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[1][1]->SetBinContent(1,0.00435466);
    SysError_NEW_R7[1][1]->SetBinContent(2,0.001532589);
    SysError_NEW_R7[1][1]->SetBinContent(3,0.001032615);
    SysError_NEW_R7[1][1]->SetBinContent(4,0.0006794686);
    SysError_NEW_R7[1][1]->SetBinContent(5,0.001431244);
    SysError_NEW_R7[1][1]->SetBinContent(6,0.001000074);
    SysError_NEW_R7[1][1]->SetBinContent(7,0.001335114);
    SysError_NEW_R7[1][1]->SetBinContent(8,0.0008433089);
    SysError_NEW_R7[1][1]->SetBinContent(9,0.00115129);
    SysError_NEW_R7[1][1]->SetBinContent(10,0.0006441113);
    SysError_NEW_R7[1][1]->SetBinContent(11,0.00291473);
    SysError_NEW_R7[1][1]->SetBinContent(12,0.001224855);
    SysError_NEW_R7[1][1]->SetBinContent(13,0.0007887284);
    SysError_NEW_R7[1][1]->SetBinContent(14,0.0006106468);
    SysError_NEW_R7[1][1]->SetBinContent(15,0.000909125);
    SysError_NEW_R7[1][1]->SetBinContent(16,0.001750147);
    SysError_NEW_R7[1][1]->SetBinContent(17,0.0004170026);
    SysError_NEW_R7[1][1]->SetBinContent(18,0.001020293);
    SysError_NEW_R7[1][1]->SetBinContent(19,6.661338e-016);
    SysError_NEW_R7[1][1]->SetBinContent(20,0.0009685225);
    SysError_NEW_R7[1][1]->SetBinContent(21,45.15628);
    //SysError_NEW_R7[1][1]->SetBinError(21,6.719842);
    //SysError_NEW_R7[1][1]->SetMinimum(0);
    //SysError_NEW_R7[1][1]->SetMaximum(0.004790126);
    //SysError_NEW_R7[1][1]->SetEntries(367020);
   
    SysError_NEW_R7[2][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[2][1]->SetBinContent(1,0.0001432844);
    SysError_NEW_R7[2][1]->SetBinContent(2,0.0003251407);
    SysError_NEW_R7[2][1]->SetBinContent(3,0.0007052488);
    SysError_NEW_R7[2][1]->SetBinContent(4,0.0007487994);
    SysError_NEW_R7[2][1]->SetBinContent(5,0.0007276014);
    SysError_NEW_R7[2][1]->SetBinContent(6,0.00082834);
    SysError_NEW_R7[2][1]->SetBinContent(7,0.0008691547);
    SysError_NEW_R7[2][1]->SetBinContent(8,0.0005584089);
    SysError_NEW_R7[2][1]->SetBinContent(9,0.001050928);
    SysError_NEW_R7[2][1]->SetBinContent(10,0.0003607706);
    SysError_NEW_R7[2][1]->SetBinContent(11,0.0009230744);
    SysError_NEW_R7[2][1]->SetBinContent(12,0.001111574);
    SysError_NEW_R7[2][1]->SetBinContent(13,0.0007773696);
    SysError_NEW_R7[2][1]->SetBinContent(14,0.002864152);
    SysError_NEW_R7[2][1]->SetBinContent(15,0.001118851);
    SysError_NEW_R7[2][1]->SetBinContent(16,0.0006101607);
    SysError_NEW_R7[2][1]->SetBinContent(17,0.001014707);
    SysError_NEW_R7[2][1]->SetBinContent(18,0.001717364);
    SysError_NEW_R7[2][1]->SetBinContent(19,0.001964444);
    SysError_NEW_R7[2][1]->SetBinContent(20,0.001407179);
    SysError_NEW_R7[2][1]->SetBinContent(21,170.9855);
    //SysError_NEW_R7[2][1]->SetBinError(21,13.07614);
    //SysError_NEW_R7[2][1]->SetMinimum(0);
    //SysError_NEW_R7[2][1]->SetMaximum(0.003150567);
    //SysError_NEW_R7[2][1]->SetEntries(659520);
   
    /// \Run7_ANTY_CC0Pi_FGD2
    SysError_ANTY_R7[0][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[0][1]->SetBinContent(1,0.0001585308);
    SysError_ANTY_R7[0][1]->SetBinContent(2,0.0001954881);
    SysError_ANTY_R7[0][1]->SetBinContent(3,6.109271e-005);
    SysError_ANTY_R7[0][1]->SetBinContent(4,8.00999e-005);
    SysError_ANTY_R7[0][1]->SetBinContent(5,0.0001565686);
    SysError_ANTY_R7[0][1]->SetBinContent(6,0.0001978846);
    SysError_ANTY_R7[0][1]->SetBinContent(7,0.0003300298);
    SysError_ANTY_R7[0][1]->SetBinContent(8,0.0001466217);
    SysError_ANTY_R7[0][1]->SetBinContent(9,0.0005146886);
    SysError_ANTY_R7[0][1]->SetBinContent(10,0.000730107);
    SysError_ANTY_R7[0][1]->SetBinContent(11,0.000569108);
    SysError_ANTY_R7[0][1]->SetBinContent(12,0.0003191267);
    SysError_ANTY_R7[0][1]->SetBinContent(13,0.0007412964);
    SysError_ANTY_R7[0][1]->SetBinContent(14,0.0008087598);
    SysError_ANTY_R7[0][1]->SetBinContent(15,0.0004414963);
    SysError_ANTY_R7[0][1]->SetBinContent(16,0.000599289);
    SysError_ANTY_R7[0][1]->SetBinContent(17,0.001208986);
    SysError_ANTY_R7[0][1]->SetBinContent(18,0.002651664);
    SysError_ANTY_R7[0][1]->SetBinContent(19,0.000564382);
    SysError_ANTY_R7[0][1]->SetBinContent(20,0.0008824882);
    SysError_ANTY_R7[0][1]->SetBinContent(21,272.1729);
    //SysError_ANTY_R7[0][1]->SetBinError(21,16.49766);
    //SysError_ANTY_R7[0][1]->SetMinimum(0);
    //SysError_ANTY_R7[0][1]->SetMaximum(0.00291683);
    //SysError_ANTY_R7[0][1]->SetEntries(4649020);

    SysError_ANTY_R7[1][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[1][1]->SetBinContent(1,0.002665747);
    SysError_ANTY_R7[1][1]->SetBinContent(2,0.001098134);
    SysError_ANTY_R7[1][1]->SetBinContent(3,0.000888587);
    SysError_ANTY_R7[1][1]->SetBinContent(4,0.0004514958);
    SysError_ANTY_R7[1][1]->SetBinContent(5,0.001059601);
    SysError_ANTY_R7[1][1]->SetBinContent(6,0.0007820012);
    SysError_ANTY_R7[1][1]->SetBinContent(7,0.002773646);
    SysError_ANTY_R7[1][1]->SetBinContent(8,0.0006006537);
    SysError_ANTY_R7[1][1]->SetBinContent(9,0.002277576);
    SysError_ANTY_R7[1][1]->SetBinContent(10,0.0004797176);
    SysError_ANTY_R7[1][1]->SetBinContent(11,0.002383314);
    SysError_ANTY_R7[1][1]->SetBinContent(12,0.002319741);
    SysError_ANTY_R7[1][1]->SetBinContent(13,0.0006193076);
    SysError_ANTY_R7[1][1]->SetBinContent(14,0.001261152);
    SysError_ANTY_R7[1][1]->SetBinContent(15,0.0009520239);
    SysError_ANTY_R7[1][1]->SetBinContent(16,0.002027734);
    SysError_ANTY_R7[1][1]->SetBinContent(17,0.001306795);
    SysError_ANTY_R7[1][1]->SetBinContent(18,0.001760441);
    SysError_ANTY_R7[1][1]->SetBinContent(19,6.661338e-016);
    SysError_ANTY_R7[1][1]->SetBinContent(20,0.0007761484);
    SysError_ANTY_R7[1][1]->SetBinContent(21,45.0032);
    //SysError_ANTY_R7[1][1]->SetBinError(21,6.708443);
    //SysError_ANTY_R7[1][1]->SetMinimum(0);
    //SysError_ANTY_R7[1][1]->SetMaximum(0.003051011);
    //SysError_ANTY_R7[1][1]->SetEntries(367020);
   

    SysError_ANTY_R7[2][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[2][1]->SetBinContent(1,0.0003120704);
    SysError_ANTY_R7[2][1]->SetBinContent(2,0.0004771039);
    SysError_ANTY_R7[2][1]->SetBinContent(3,0.000622499);
    SysError_ANTY_R7[2][1]->SetBinContent(4,0.0006452241);
    SysError_ANTY_R7[2][1]->SetBinContent(5,0.0008419699);
    SysError_ANTY_R7[2][1]->SetBinContent(6,0.0007101316);
    SysError_ANTY_R7[2][1]->SetBinContent(7,0.0006729142);
    SysError_ANTY_R7[2][1]->SetBinContent(8,0.0007752581);
    SysError_ANTY_R7[2][1]->SetBinContent(9,0.000899998);
    SysError_ANTY_R7[2][1]->SetBinContent(10,0.0005114879);
    SysError_ANTY_R7[2][1]->SetBinContent(11,0.001165468);
    SysError_ANTY_R7[2][1]->SetBinContent(12,0.0008075766);
    SysError_ANTY_R7[2][1]->SetBinContent(13,0.0005383409);
    SysError_ANTY_R7[2][1]->SetBinContent(14,0.002654693);
    SysError_ANTY_R7[2][1]->SetBinContent(15,0.000911803);
    SysError_ANTY_R7[2][1]->SetBinContent(16,0.0004296363);
    SysError_ANTY_R7[2][1]->SetBinContent(17,0.001098898);
    SysError_ANTY_R7[2][1]->SetBinContent(18,0.001557417);
    SysError_ANTY_R7[2][1]->SetBinContent(19,0.003298433);
    SysError_ANTY_R7[2][1]->SetBinContent(20,0.002209711);
    SysError_ANTY_R7[2][1]->SetBinContent(21,170.9435);
    //SysError_ANTY_R7[2][1]->SetBinError(21,13.07454);
    //SysError_ANTY_R7[2][1]->SetMinimum(0);
    //SysError_ANTY_R7[2][1]->SetMaximum(0.003628277);
    //SysError_ANTY_R7[2][1]->SetEntries(659520);
        
    
    /// \Run7_PI-_CC0Pi_FGD2
    SysError_PI_R7[0][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[0][1]->SetBinContent(1,0.000204708);
    SysError_PI_R7[0][1]->SetBinContent(2,0.0001999782);
    SysError_PI_R7[0][1]->SetBinContent(3,6.742271e-005);
    SysError_PI_R7[0][1]->SetBinContent(4,0.0001125504);
    SysError_PI_R7[0][1]->SetBinContent(5,0.0001697725);
    SysError_PI_R7[0][1]->SetBinContent(6,0.000216133);
    SysError_PI_R7[0][1]->SetBinContent(7,0.0003487095);
    SysError_PI_R7[0][1]->SetBinContent(8,0.0001726311);
    SysError_PI_R7[0][1]->SetBinContent(9,0.0008475003);
    SysError_PI_R7[0][1]->SetBinContent(10,0.0007574186);
    SysError_PI_R7[0][1]->SetBinContent(11,0.0005889505);
    SysError_PI_R7[0][1]->SetBinContent(12,0.0003296304);
    SysError_PI_R7[0][1]->SetBinContent(13,0.0007695512);
    SysError_PI_R7[0][1]->SetBinContent(14,0.0008302465);
    SysError_PI_R7[0][1]->SetBinContent(15,0.0004489302);
    SysError_PI_R7[0][1]->SetBinContent(16,0.0006561618);
    SysError_PI_R7[0][1]->SetBinContent(17,0.001254396);
    SysError_PI_R7[0][1]->SetBinContent(18,0.002659036);
    SysError_PI_R7[0][1]->SetBinContent(19,0.000625466);
    SysError_PI_R7[0][1]->SetBinContent(20,0.0009869909);
    SysError_PI_R7[0][1]->SetBinContent(21,272.2477);
    //SysError_PI_R7[0][1]->SetBinError(21,16.49993);
    //SysError_PI_R7[0][1]->SetMinimum(0);
    //SysError_PI_R7[0][1]->SetMaximum(0.00292494);
    //SysError_PI_R7[0][1]->SetEntries(4649020);

    SysError_PI_R7[1][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[1][1]->SetBinContent(1,0.003276264);
    SysError_PI_R7[1][1]->SetBinContent(2,0.001317844);
    SysError_PI_R7[1][1]->SetBinContent(3,0.001158839);
    SysError_PI_R7[1][1]->SetBinContent(4,0.000563306);
    SysError_PI_R7[1][1]->SetBinContent(5,0.001201907);
    SysError_PI_R7[1][1]->SetBinContent(6,0.0009921173);
    SysError_PI_R7[1][1]->SetBinContent(7,0.002798263);
    SysError_PI_R7[1][1]->SetBinContent(8,0.0006723454);
    SysError_PI_R7[1][1]->SetBinContent(9,0.00235815);
    SysError_PI_R7[1][1]->SetBinContent(10,0.00083926);
    SysError_PI_R7[1][1]->SetBinContent(11,0.002407197);
    SysError_PI_R7[1][1]->SetBinContent(12,0.002681535);
    SysError_PI_R7[1][1]->SetBinContent(13,0.0009189399);
    SysError_PI_R7[1][1]->SetBinContent(14,0.001273224);
    SysError_PI_R7[1][1]->SetBinContent(15,0.0009731523);
    SysError_PI_R7[1][1]->SetBinContent(16,0.002148449);
    SysError_PI_R7[1][1]->SetBinContent(17,0.001306795);
    SysError_PI_R7[1][1]->SetBinContent(18,0.001760441);
    SysError_PI_R7[1][1]->SetBinContent(19,6.661338e-016);
    SysError_PI_R7[1][1]->SetBinContent(20,0.0007761484);
    SysError_PI_R7[1][1]->SetBinContent(21,45.02081);
    //SysError_PI_R7[1][1]->SetBinError(21,6.709755);
    //SysError_PI_R7[1][1]->SetMinimum(0);
    //SysError_PI_R7[1][1]->SetMaximum(0.00360389);
    //SysError_PI_R7[1][1]->SetEntries(367020);

    SysError_PI_R7[2][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[2][1]->SetBinContent(1,0.0003132629);
    SysError_PI_R7[2][1]->SetBinContent(2,0.0005801949);
    SysError_PI_R7[2][1]->SetBinContent(3,0.0007876665);
    SysError_PI_R7[2][1]->SetBinContent(4,0.0007634061);
    SysError_PI_R7[2][1]->SetBinContent(5,0.001601287);
    SysError_PI_R7[2][1]->SetBinContent(6,0.001020609);
    SysError_PI_R7[2][1]->SetBinContent(7,0.001565405);
    SysError_PI_R7[2][1]->SetBinContent(8,0.0009376173);
    SysError_PI_R7[2][1]->SetBinContent(9,0.002594422);
    SysError_PI_R7[2][1]->SetBinContent(10,0.0008723141);
    SysError_PI_R7[2][1]->SetBinContent(11,0.001237147);
    SysError_PI_R7[2][1]->SetBinContent(12,0.001493633);
    SysError_PI_R7[2][1]->SetBinContent(13,0.0008554826);
    SysError_PI_R7[2][1]->SetBinContent(14,0.007971132);
    SysError_PI_R7[2][1]->SetBinContent(15,0.001005989);
    SysError_PI_R7[2][1]->SetBinContent(16,0.000728945);
    SysError_PI_R7[2][1]->SetBinContent(17,0.002930549);
    SysError_PI_R7[2][1]->SetBinContent(18,0.00180538);
    SysError_PI_R7[2][1]->SetBinContent(19,0.003825238);
    SysError_PI_R7[2][1]->SetBinContent(20,0.002441874);
    SysError_PI_R7[2][1]->SetBinContent(21,170.8557);
    //SysError_PI_R7[2][1]->SetBinError(21,13.07118);
    //SysError_PI_R7[2][1]->SetMinimum(0);
    //SysError_PI_R7[2][1]->SetMaximum(0.008768246);
    //SysError_PI_R7[2][1]->SetEntries(659520);
   
    
/// \DRAWING_STARTS_HERE   
    TCanvas *Canvas[300];
    TLegend *legend[300];
    int canvasCounter=0;
    float maximum=0;
    for(int is=0; is<3; is++)
    {    
        for(int i=0; i<2; i++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 0, 0, 800,630);

            SysError_DEFAULT_R4[is][i]->SetLineColor(kBlue);
            SysError_DEFAULT_R4[is][i]->SetLineStyle(2);
            SysError_DEFAULT_R4[is][i]->GetYaxis()->SetTitle("Relative error");
            SysError_DEFAULT_R4[is][i]->GetXaxis()->SetTitle("Reconstructed muon momentum (MeV/c)");
            
            SysError_NEW_R4[is][i]->SetLineStyle(7);
            SysError_NEW_R4[is][i]->SetLineColor(kRed);
            maximum=0;
            if(i==1)
            {
                maximum = SysError_NEW_R4[2][1]->GetMaximum();
                SysError_DEFAULT_R4[is][i]->SetMaximum(maximum);
                
            }
            SysError_DEFAULT_R4[is][i]->Draw();
            SysError_NEW_R4[is][i]->Draw("SAME");
            
            legend[canvasCounter] = new TLegend(0.20,0.70,0.4,0.85);
            legend[canvasCounter]->AddEntry(SysError_DEFAULT_R4[is][i],Form("%s",Type[0].Data()),"l");
            legend[canvasCounter]->AddEntry(SysError_NEW_R4[is][i], Form("%s",Type[1].Data()),"l");
            legend[canvasCounter]->SetTextSize(0.035);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print(Form("Run4__%s_FGD%s.pdf", Sample[is].Data(), FGD[i].Data() )); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }
        
    for(int is=0; is<3; is++)
    {    
        for(int i=0; i<2; i++)
        {
            Canvas[canvasCounter] = new TCanvas( Form("Canvas%i",canvasCounter), Form("Canvas%i",canvasCounter), 0, 0, 800,630);

            SysError_DEFAULT_R7[is][i]->SetLineColor(kBlue);
            SysError_DEFAULT_R7[is][i]->SetLineStyle(2);
            SysError_DEFAULT_R7[is][i]->GetYaxis()->SetTitle("Relative error");
            SysError_DEFAULT_R7[is][i]->GetXaxis()->SetTitle("Reconstructed muon momentum (MeV/c)");
            
            SysError_NEW_R7[is][i]->SetLineStyle(7);
            SysError_NEW_R7[is][i]->SetLineColor(kRed);
            
            SysError_ANTY_R7[is][i]->SetLineStyle(1);
            SysError_ANTY_R7[is][i]->SetLineColor(kGreen);
            

            SysError_PI_R7[is][i]->SetLineStyle(4);
            SysError_PI_R7[is][i]->SetLineColor(kMagenta);
            
            /*
            maximum=0;
            if(i==1)
            {
                maximum = SysError_ANTY_R7[is][1]->GetMaximum();
                SysError_DEFAULT_R7[is][i]->SetMaximum(maximum);
                
            }
            */
            SysError_DEFAULT_R7[is][i]->Draw();
            SysError_NEW_R7[is][i]->Draw("SAME");
            SysError_ANTY_R7[is][i]->Draw("SAME");
            SysError_PI_R7[is][i]->Draw("SAME");
            
            
            legend[canvasCounter] = new TLegend(0.20,0.70,0.4,0.85);
            legend[canvasCounter]->AddEntry(SysError_DEFAULT_R7[is][i],Form("%s",Type[0].Data()),"l");
            legend[canvasCounter]->AddEntry(SysError_NEW_R7[is][i], Form("%s",Type[1].Data()),"l");
            legend[canvasCounter]->AddEntry(SysError_ANTY_R7[is][i], Form("%s",Type[2].Data()),"l");
            legend[canvasCounter]->AddEntry(SysError_PI_R7[is][i], Form("%s",Type[3].Data()),"l");
            legend[canvasCounter]->SetTextSize(0.035);
            legend[canvasCounter]->Draw();
            
            gPad->Modified();
            Canvas[canvasCounter]->Print(Form("Run7__%s_FGD%s.pdf", Sample[is].Data(), FGD[i].Data() )); 
            delete Canvas[canvasCounter];
            canvasCounter++;
        }
    }

}


void SetT2Kstyl()
{
     // -- WhichStyle --
    // 1 = presentation large fonts
    // 2 = presentation small fonts
    // 3 = publication/paper
    Int_t WhichStyle = 3;
    
    Int_t FontStyle = 22;
    Float_t FontSizeLabel = 0.035;
    Float_t FontSizeTitle = 0.05;
    Float_t YOffsetTitle = 1.3;

  switch(WhichStyle) 
  {
    case 1:
        FontStyle = 42;
        FontSizeLabel = 0.05;
        FontSizeTitle = 0.065;
        YOffsetTitle = 1.19;
        break;
    case 2:
        FontStyle = 42;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.05;
        YOffsetTitle = 1.6;
        break;
    case 3:
        FontStyle = 132;
        FontSizeLabel = 0.035;
        FontSizeTitle = 0.040;
        YOffsetTitle = 1.6;
        break;
    }
    // use plain black on white colors
    gStyle->SetFrameBorderMode(0);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetCanvasBorderSize(0);
    gStyle->SetFrameBorderSize(0);
    gStyle->SetDrawBorder(0);
    gStyle->SetTitleBorderSize(2);
    gStyle->SetStatBorderSize(0);

    gStyle->SetStatX(0.89);
    gStyle->SetStatY(0.89);
    
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetStatColor(0);
    gStyle->SetFillColor(0);

    gStyle->SetEndErrorSize(4);
    gStyle->SetStripDecimals(kFALSE);

    gStyle->SetLegendBorderSize(0); //This option dsables legends borders
    gStyle->SetLegendFont(FontStyle);

    // set the paper & margin sizes
    gStyle->SetPaperSize(20, 26);
    gStyle->SetPadTopMargin(0.1);
    gStyle->SetPadBottomMargin(0.15);
    gStyle->SetPadRightMargin(0.075); // 0.075 -> 0.13 for colz option
    gStyle->SetPadLeftMargin(0.13);//to include both large/small font options

    // Fonts, sizes, offsets
    gStyle->SetTextFont(FontStyle);
    gStyle->SetTextSize(FontSizeTitle);

    gStyle->SetLabelFont(FontStyle, "x");
    gStyle->SetLabelFont(FontStyle, "y");
    gStyle->SetLabelFont(FontStyle, "z");
    gStyle->SetLabelFont(FontStyle, "t");
    gStyle->SetLabelSize(FontSizeLabel, "x");
    gStyle->SetLabelSize(FontSizeLabel, "y");
    gStyle->SetLabelSize(FontSizeLabel, "z");
    gStyle->SetLabelOffset(0.015, "x");
    gStyle->SetLabelOffset(0.015, "y");
    gStyle->SetLabelOffset(0.015, "z");

    gStyle->SetTitleFont(FontStyle, "x");
    gStyle->SetTitleFont(FontStyle, "y");
    gStyle->SetTitleFont(FontStyle, "z");
    gStyle->SetTitleFont(FontStyle, "t");
    gStyle->SetTitleSize(FontSizeTitle, "y");
    gStyle->SetTitleSize(FontSizeTitle, "x");
    gStyle->SetTitleSize(FontSizeTitle, "z");
    gStyle->SetTitleSize(FontSizeTitle, "t");
    gStyle->SetTitleOffset(1.3, "x");
    gStyle->SetTitleOffset(1.4, "y");
    gStyle->SetTitleOffset(1.2, "z");

    gStyle->SetTitleStyle(0);
    gStyle->SetTitleFontSize(0.045);//0.08
    gStyle->SetTitleFont(FontStyle, "pad");
    gStyle->SetTitleX(0.6);
    gStyle->SetTitleY(0.96);
    //gStyle->SetTitleW(0.8f);

    // use bold lines and markers
    gStyle->SetMarkerStyle(20); //FIXME Coment this for FGD2
    gStyle->SetHistLineWidth( Width_t(2.5) );
    gStyle->SetLineStyleString(2, "[12 12]"); // postscript dashes

    // get rid of X error bars and y error bar caps
    gStyle->SetErrorX(0.001);

    // do not display any of the standard histogram decorations
    //gStyle->SetOptTitle(0); //Set 0 to disable histogram tittle
    gStyle->SetOptStat(0); //Set 0 to disable statystic box
    //gStyle->SetOptFit(0);

    // put tick marks on top and RHS of plots
    gStyle->SetPadTickX(0);
    gStyle->SetPadTickY(0);

    // -- color --
    // functions blue
    //gStyle->SetFuncColor(600-4);
    gStyle->SetFuncColor(2);
    gStyle->SetFuncWidth(2);

    gStyle->SetFillColor(1); // make color fillings (not white)
    // - color setup for 2D -
    // - "cold"/ blue-ish -
    Double_t red[]   = { 0.00, 0.00, 0.00 };
    Double_t green[] = { 1.00, 0.00, 0.00 };
    Double_t blue[]  = { 1.00, 1.00, 0.25 };
    // - "warm" red-ish colors -
    //  Double_t red[]   = {1.00, 1.00, 0.25 };
    //  Double_t green[] = {1.00, 0.00, 0.00 };
    //  Double_t blue[]  = {0.00, 0.00, 0.00 };

    Double_t stops[] = { 0.25, 0.75, 1.00 };
    const Int_t NRGBs = 3;
    const Int_t NCont = 500;

    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);

    // - Rainbow -
    gStyle->SetPalette(1);  // use the rainbow color set

    // -- axis --
    gStyle->SetStripDecimals(kFALSE); // don't do 1.0 -> 1
    //  TGaxis::SetMaxDigits(3); // doesn't have an effect
    // no supressed zeroes!
    gStyle->SetHistMinimumZero(kTRUE);       
    
    gROOT->ForceStyle();    
}
