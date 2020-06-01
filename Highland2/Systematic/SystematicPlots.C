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
    
    TString Type[4] = {"DEFAULT", "NEW", "ANTY", "PI-"};
     
    /// \Run4_DEFAULT_CC0Pi_FGD1
    SysError_DEFAULT_R4[0][0]=new TH1D(Form("SysError_DEFAULT_R4_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[0][0]->SetBinContent(1,0.0007952473);
    SysError_DEFAULT_R4[0][0]->SetBinContent(2,0.0005736167);
    SysError_DEFAULT_R4[0][0]->SetBinContent(3,0.001026492);
    SysError_DEFAULT_R4[0][0]->SetBinContent(4,0.001379292);
    SysError_DEFAULT_R4[0][0]->SetBinContent(5,0.001262157);
    SysError_DEFAULT_R4[0][0]->SetBinContent(6,0.002486748);
    SysError_DEFAULT_R4[0][0]->SetBinContent(7,0.002437555);
    SysError_DEFAULT_R4[0][0]->SetBinContent(8,0.002816097);
    SysError_DEFAULT_R4[0][0]->SetBinContent(9,0.004039241);
    SysError_DEFAULT_R4[0][0]->SetBinContent(10,0.002174534);
    SysError_DEFAULT_R4[0][0]->SetBinContent(11,0.004097483);
    SysError_DEFAULT_R4[0][0]->SetBinContent(12,0.002649323);
    SysError_DEFAULT_R4[0][0]->SetBinContent(13,0.004276335);
    SysError_DEFAULT_R4[0][0]->SetBinContent(14,0.005389913);
    SysError_DEFAULT_R4[0][0]->SetBinContent(15,0.002509073);
    SysError_DEFAULT_R4[0][0]->SetBinContent(16,0.005985625);
    SysError_DEFAULT_R4[0][0]->SetBinContent(17,0.002806424);
    SysError_DEFAULT_R4[0][0]->SetBinContent(18,0.002965063);
    SysError_DEFAULT_R4[0][0]->SetBinContent(19,0.003508772);
    SysError_DEFAULT_R4[0][0]->SetBinContent(20,0.002092726);
    SysError_DEFAULT_R4[0][0]->SetBinContent(21,1024.017);
    //SysError_DEFAULT_R4[0][0]->SetBinError(21,32.00026);
    //SysError_DEFAULT_R4[0][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[0][0]->SetMaximum(0.006584187);
    //SysError_DEFAULT_R4[0][0]->SetEntries(1.341452e+007);
    
    SysError_DEFAULT_R4[1][0]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[1][0]->SetBinContent(1,0.00158603);
    SysError_DEFAULT_R4[1][0]->SetBinContent(2,0.002421074);
    SysError_DEFAULT_R4[1][0]->SetBinContent(3,0.001927795);
    SysError_DEFAULT_R4[1][0]->SetBinContent(4,0.002256206);
    SysError_DEFAULT_R4[1][0]->SetBinContent(5,0.001508078);
    SysError_DEFAULT_R4[1][0]->SetBinContent(6,0.001727117);
    SysError_DEFAULT_R4[1][0]->SetBinContent(7,0.002288137);
    SysError_DEFAULT_R4[1][0]->SetBinContent(8,0.002148921);
    SysError_DEFAULT_R4[1][0]->SetBinContent(9,0.001921127);
    SysError_DEFAULT_R4[1][0]->SetBinContent(10,0.003921423);
    SysError_DEFAULT_R4[1][0]->SetBinContent(11,0.001696459);
    SysError_DEFAULT_R4[1][0]->SetBinContent(12,0.002209883);
    SysError_DEFAULT_R4[1][0]->SetBinContent(13,0.00106223);
    SysError_DEFAULT_R4[1][0]->SetBinContent(14,0.002408727);
    SysError_DEFAULT_R4[1][0]->SetBinContent(15,0.005356803);
    SysError_DEFAULT_R4[1][0]->SetBinContent(16,0.003624154);
    SysError_DEFAULT_R4[1][0]->SetBinContent(17,0.003023877);
    SysError_DEFAULT_R4[1][0]->SetBinContent(18,0.003091608);
    SysError_DEFAULT_R4[1][0]->SetBinContent(19,0.004609059);
    SysError_DEFAULT_R4[1][0]->SetBinContent(20,0.002935373);
    SysError_DEFAULT_R4[1][0]->SetBinContent(21,411.8953);
    //SysError_DEFAULT_R4[1][0]->SetBinError(21,20.2952);
    //SysError_DEFAULT_R4[1][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[1][0]->SetMaximum(0.005892483);
    //SysError_DEFAULT_R4[1][0]->SetEntries(3247520);
    
    SysError_DEFAULT_R4[2][0]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("Run4 %s FGD%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[2][0]->SetBinContent(1,0.002285895);
    SysError_DEFAULT_R4[2][0]->SetBinContent(2,0.003774925);
    SysError_DEFAULT_R4[2][0]->SetBinContent(3,0.00579577);
    SysError_DEFAULT_R4[2][0]->SetBinContent(4,0.004601133);
    SysError_DEFAULT_R4[2][0]->SetBinContent(5,0.005185529);
    SysError_DEFAULT_R4[2][0]->SetBinContent(6,0.003002676);
    SysError_DEFAULT_R4[2][0]->SetBinContent(7,0.004422273);
    SysError_DEFAULT_R4[2][0]->SetBinContent(8,0.005913951);
    SysError_DEFAULT_R4[2][0]->SetBinContent(9,0.002762641);
    SysError_DEFAULT_R4[2][0]->SetBinContent(10,0.004437009);
    SysError_DEFAULT_R4[2][0]->SetBinContent(11,0.005600794);
    SysError_DEFAULT_R4[2][0]->SetBinContent(12,0.003734316);
    SysError_DEFAULT_R4[2][0]->SetBinContent(13,0.008861421);
    SysError_DEFAULT_R4[2][0]->SetBinContent(14,0.005268146);
    SysError_DEFAULT_R4[2][0]->SetBinContent(15,0.005386169);
    SysError_DEFAULT_R4[2][0]->SetBinContent(16,0.003374156);
    SysError_DEFAULT_R4[2][0]->SetBinContent(17,0.002770782);
    SysError_DEFAULT_R4[2][0]->SetBinContent(18,0.002335074);
    SysError_DEFAULT_R4[2][0]->SetBinContent(19,0.00301609);
    SysError_DEFAULT_R4[2][0]->SetBinContent(20,0.006227048);
    SysError_DEFAULT_R4[2][0]->SetBinContent(21,503.075);
    //SysError_DEFAULT_R4[2][0]->SetBinError(21,22.42933);
    //SysError_DEFAULT_R4[2][0]->SetMinimum(0);
    //SysError_DEFAULT_R4[2][0]->SetMaximum(0.009747563);
    //SysError_DEFAULT_R4[2][0]->SetEntries(2553520);
    
    /// \Run4_DEFAULT_CC0Pi_FGD1
    SysError_DEFAULT_R4[0][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[0][1]->SetBinContent(1,0.0001125795);
    SysError_DEFAULT_R4[0][1]->SetBinContent(2,0.000102459);
    SysError_DEFAULT_R4[0][1]->SetBinContent(3,0.0001849125);
    SysError_DEFAULT_R4[0][1]->SetBinContent(4,0.0002910385);
    SysError_DEFAULT_R4[0][1]->SetBinContent(5,0.000426468);
    SysError_DEFAULT_R4[0][1]->SetBinContent(6,0.0002881875);
    SysError_DEFAULT_R4[0][1]->SetBinContent(7,0.0005277104);
    SysError_DEFAULT_R4[0][1]->SetBinContent(8,0.0006013698);
    SysError_DEFAULT_R4[0][1]->SetBinContent(9,0.0006772348);
    SysError_DEFAULT_R4[0][1]->SetBinContent(10,0.0006222964);
    SysError_DEFAULT_R4[0][1]->SetBinContent(11,0.0008929652);
    SysError_DEFAULT_R4[0][1]->SetBinContent(12,0.000515313);
    SysError_DEFAULT_R4[0][1]->SetBinContent(13,0.0004382517);
    SysError_DEFAULT_R4[0][1]->SetBinContent(14,0.001042469);
    SysError_DEFAULT_R4[0][1]->SetBinContent(15,0.0003989369);
    SysError_DEFAULT_R4[0][1]->SetBinContent(16,0.001494427);
    SysError_DEFAULT_R4[0][1]->SetBinContent(17,0.0008886507);
    SysError_DEFAULT_R4[0][1]->SetBinContent(18,0.0005957207);
    SysError_DEFAULT_R4[0][1]->SetBinContent(19,0.0008337382);
    SysError_DEFAULT_R4[0][1]->SetBinContent(20,0.001046935);
    SysError_DEFAULT_R4[0][1]->SetBinContent(21,1006.77);
    //SysError_DEFAULT_R4[0][1]->SetBinError(21,31.72964);
    //SysError_DEFAULT_R4[0][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[0][1]->SetMaximum(0.00164387);
    //SysError_DEFAULT_R4[0][1]->SetEntries(1.378352e+007);
   
    SysError_DEFAULT_R4[1][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[1][1]->SetBinContent(1,0.0001992151);
    SysError_DEFAULT_R4[1][1]->SetBinContent(2,0.0005143192);
    SysError_DEFAULT_R4[1][1]->SetBinContent(3,0.0005255857);
    SysError_DEFAULT_R4[1][1]->SetBinContent(4,0.0006394757);
    SysError_DEFAULT_R4[1][1]->SetBinContent(5,0.000815419);
    SysError_DEFAULT_R4[1][1]->SetBinContent(6,0.0005522727);
    SysError_DEFAULT_R4[1][1]->SetBinContent(7,0.0006860741);
    SysError_DEFAULT_R4[1][1]->SetBinContent(8,0.0004689595);
    SysError_DEFAULT_R4[1][1]->SetBinContent(9,0.0003487089);
    SysError_DEFAULT_R4[1][1]->SetBinContent(10,0.0006803615);
    SysError_DEFAULT_R4[1][1]->SetBinContent(11,0.0008021418);
    SysError_DEFAULT_R4[1][1]->SetBinContent(12,0.0007682661);
    SysError_DEFAULT_R4[1][1]->SetBinContent(13,0.0011317);
    SysError_DEFAULT_R4[1][1]->SetBinContent(14,0.0009835111);
    SysError_DEFAULT_R4[1][1]->SetBinContent(15,0.0008869159);
    SysError_DEFAULT_R4[1][1]->SetBinContent(16,0.001545549);
    SysError_DEFAULT_R4[1][1]->SetBinContent(17,0.001325771);
    SysError_DEFAULT_R4[1][1]->SetBinContent(18,0.002064919);
    SysError_DEFAULT_R4[1][1]->SetBinContent(19,0.001360607);
    SysError_DEFAULT_R4[1][1]->SetBinContent(20,0.002270538);
    SysError_DEFAULT_R4[1][1]->SetBinContent(21,326.0709);
    //SysError_DEFAULT_R4[1][1]->SetBinError(21,18.05743);
    //SysError_DEFAULT_R4[1][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[1][1]->SetMaximum(0.002497592);
    //SysError_DEFAULT_R4[1][1]->SetEntries(2745520);
   
    SysError_DEFAULT_R4[2][1]=new TH1D(Form( "SysError_DEFAULT_R4_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("Run4 %s FGD%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R4[2][1]->SetBinContent(1,0.0008612585);
    SysError_DEFAULT_R4[2][1]->SetBinContent(2,0.0007704307);
    SysError_DEFAULT_R4[2][1]->SetBinContent(3,0.0008427713);
    SysError_DEFAULT_R4[2][1]->SetBinContent(4,0.0009843911);
    SysError_DEFAULT_R4[2][1]->SetBinContent(5,0.0008255638);
    SysError_DEFAULT_R4[2][1]->SetBinContent(6,0.0008621359);
    SysError_DEFAULT_R4[2][1]->SetBinContent(7,0.0008949349);
    SysError_DEFAULT_R4[2][1]->SetBinContent(8,0.001134875);
    SysError_DEFAULT_R4[2][1]->SetBinContent(9,0.001285261);
    SysError_DEFAULT_R4[2][1]->SetBinContent(10,0.0007320266);
    SysError_DEFAULT_R4[2][1]->SetBinContent(11,0.0006382734);
    SysError_DEFAULT_R4[2][1]->SetBinContent(12,0.0007439169);
    SysError_DEFAULT_R4[2][1]->SetBinContent(13,0.0008156286);
    SysError_DEFAULT_R4[2][1]->SetBinContent(14,0.0008708473);
    SysError_DEFAULT_R4[2][1]->SetBinContent(15,0.0008633785);
    SysError_DEFAULT_R4[2][1]->SetBinContent(16,0.001450887);
    SysError_DEFAULT_R4[2][1]->SetBinContent(17,0.002170357);
    SysError_DEFAULT_R4[2][1]->SetBinContent(18,0.001494305);
    SysError_DEFAULT_R4[2][1]->SetBinContent(19,0.001233602);
    SysError_DEFAULT_R4[2][1]->SetBinContent(20,0.0007991895);
    SysError_DEFAULT_R4[2][1]->SetBinContent(21,554.4649);
    //SysError_DEFAULT_R4[2][1]->SetBinError(21,23.54708);
    //SysError_DEFAULT_R4[2][1]->SetMinimum(0);
    //SysError_DEFAULT_R4[2][1]->SetMaximum(0.002387393);
    //SysError_DEFAULT_R4[2][1]->SetEntries(2504020);
    
    /// \Run4_NEW_CC0Pi_FGD1
    SysError_NEW_R4[0][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[0][0]->SetBinContent(1,0.001006704);
    SysError_NEW_R4[0][0]->SetBinContent(2,0.0003976553);
    SysError_NEW_R4[0][0]->SetBinContent(3,0.0005301745);
    SysError_NEW_R4[0][0]->SetBinContent(4,0.000625071);
    SysError_NEW_R4[0][0]->SetBinContent(5,0.0007198134);
    SysError_NEW_R4[0][0]->SetBinContent(6,0.001136055);
    SysError_NEW_R4[0][0]->SetBinContent(7,0.001292603);
    SysError_NEW_R4[0][0]->SetBinContent(8,0.001275331);
    SysError_NEW_R4[0][0]->SetBinContent(9,0.001860288);
    SysError_NEW_R4[0][0]->SetBinContent(10,0.001798745);
    SysError_NEW_R4[0][0]->SetBinContent(11,0.00223433);
    SysError_NEW_R4[0][0]->SetBinContent(12,0.001336201);
    SysError_NEW_R4[0][0]->SetBinContent(13,0.002080358);
    SysError_NEW_R4[0][0]->SetBinContent(14,0.002638226);
    SysError_NEW_R4[0][0]->SetBinContent(15,0.002888727);
    SysError_NEW_R4[0][0]->SetBinContent(16,0.002800602);
    SysError_NEW_R4[0][0]->SetBinContent(17,0.001837732);
    SysError_NEW_R4[0][0]->SetBinContent(18,0.002544623);
    SysError_NEW_R4[0][0]->SetBinContent(19,0.001635571);
    SysError_NEW_R4[0][0]->SetBinContent(20,0.001995895);
    SysError_NEW_R4[0][0]->SetBinContent(21,1026.474);
    //SysError_NEW_R4[0][0]->SetBinError(21,32.03863);
    //SysError_NEW_R4[0][0]->SetMinimum(0);
    //SysError_NEW_R4[0][0]->SetMaximum(0.0031776);
    //SysError_NEW_R4[0][0]->SetEntries(1.341452e+007);
    
    SysError_NEW_R4[1][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[1][0]->SetBinContent(1,0.0008876204);
    SysError_NEW_R4[1][0]->SetBinContent(2,0.002318848);
    SysError_NEW_R4[1][0]->SetBinContent(3,0.00189822);
    SysError_NEW_R4[1][0]->SetBinContent(4,0.00208847);
    SysError_NEW_R4[1][0]->SetBinContent(5,0.001429602);
    SysError_NEW_R4[1][0]->SetBinContent(6,0.001788777);
    SysError_NEW_R4[1][0]->SetBinContent(7,0.002299727);
    SysError_NEW_R4[1][0]->SetBinContent(8,0.002305054);
    SysError_NEW_R4[1][0]->SetBinContent(9,0.001818655);
    SysError_NEW_R4[1][0]->SetBinContent(10,0.00309251);
    SysError_NEW_R4[1][0]->SetBinContent(11,0.001794224);
    SysError_NEW_R4[1][0]->SetBinContent(12,0.002425373);
    SysError_NEW_R4[1][0]->SetBinContent(13,0.001148315);
    SysError_NEW_R4[1][0]->SetBinContent(14,0.002207924);
    SysError_NEW_R4[1][0]->SetBinContent(15,0.004724267);
    SysError_NEW_R4[1][0]->SetBinContent(16,0.0045357);
    SysError_NEW_R4[1][0]->SetBinContent(17,0.001890102);
    SysError_NEW_R4[1][0]->SetBinContent(18,0.003461209);
    SysError_NEW_R4[1][0]->SetBinContent(19,0.004160951);
    SysError_NEW_R4[1][0]->SetBinContent(20,0.001932028);
    SysError_NEW_R4[1][0]->SetBinContent(21,411.5276);
    //SysError_NEW_R4[1][0]->SetBinError(21,20.28614);
    //SysError_NEW_R4[1][0]->SetMinimum(0);
    //SysError_NEW_R4[1][0]->SetMaximum(0.005196693);
    //SysError_NEW_R4[1][0]->SetEntries(3247520);
   
    SysError_NEW_R4[2][0]=new TH1D(Form( "SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R4[2][0]->SetBinContent(1,0.001885167);
    SysError_NEW_R4[2][0]->SetBinContent(2,0.002998779);
    SysError_NEW_R4[2][0]->SetBinContent(3,0.004641218);
    SysError_NEW_R4[2][0]->SetBinContent(4,0.00401859);
    SysError_NEW_R4[2][0]->SetBinContent(5,0.004131759);
    SysError_NEW_R4[2][0]->SetBinContent(6,0.002362421);
    SysError_NEW_R4[2][0]->SetBinContent(7,0.003529346);
    SysError_NEW_R4[2][0]->SetBinContent(8,0.005062501);
    SysError_NEW_R4[2][0]->SetBinContent(9,0.002137576);
    SysError_NEW_R4[2][0]->SetBinContent(10,0.003963562);
    SysError_NEW_R4[2][0]->SetBinContent(11,0.005533864);
    SysError_NEW_R4[2][0]->SetBinContent(12,0.003650303);
    SysError_NEW_R4[2][0]->SetBinContent(13,0.008541874);
    SysError_NEW_R4[2][0]->SetBinContent(14,0.005778603);
    SysError_NEW_R4[2][0]->SetBinContent(15,0.004150287);
    SysError_NEW_R4[2][0]->SetBinContent(16,0.002950051);
    SysError_NEW_R4[2][0]->SetBinContent(17,0.0027914);
    SysError_NEW_R4[2][0]->SetBinContent(18,0.001964697);
    SysError_NEW_R4[2][0]->SetBinContent(19,0.003302813);
    SysError_NEW_R4[2][0]->SetBinContent(20,0.006315368);
    SysError_NEW_R4[2][0]->SetBinContent(21,502.3655);
    //SysError_NEW_R4[2][0]->SetBinError(21,22.41351);
    //SysError_NEW_R4[2][0]->SetMinimum(0);
    //SysError_NEW_R4[2][0]->SetMaximum(0.009396062);
    //SysError_NEW_R4[2][0]->SetEntries(2553520);
    
    /// \Run4_NEW_CC0Pi_FGD2
    
    SysError_NEW_R4[0][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[0][1]->SetBinContent(1,0.0001873479);
    SysError_NEW_R4[0][1]->SetBinContent(2,0.0003466847);
    SysError_NEW_R4[0][1]->SetBinContent(3,0.0003675644);
    SysError_NEW_R4[0][1]->SetBinContent(4,0.000331528);
    SysError_NEW_R4[0][1]->SetBinContent(5,0.001304762);
    SysError_NEW_R4[0][1]->SetBinContent(6,0.0008832066);
    SysError_NEW_R4[0][1]->SetBinContent(7,0.001436952);
    SysError_NEW_R4[0][1]->SetBinContent(8,0.001935311);
    SysError_NEW_R4[0][1]->SetBinContent(9,0.002075048);
    SysError_NEW_R4[0][1]->SetBinContent(10,0.001983226);
    SysError_NEW_R4[0][1]->SetBinContent(11,0.002299119);
    SysError_NEW_R4[0][1]->SetBinContent(12,0.001410449);
    SysError_NEW_R4[0][1]->SetBinContent(13,0.001102824);
    SysError_NEW_R4[0][1]->SetBinContent(14,0.003394943);
    SysError_NEW_R4[0][1]->SetBinContent(15,0.001137527);
    SysError_NEW_R4[0][1]->SetBinContent(16,0.004467742);
    SysError_NEW_R4[0][1]->SetBinContent(17,0.001836384);
    SysError_NEW_R4[0][1]->SetBinContent(18,0.001885167);
    SysError_NEW_R4[0][1]->SetBinContent(19,0.002422542);
    SysError_NEW_R4[0][1]->SetBinContent(20,0.003322184);
    SysError_NEW_R4[0][1]->SetBinContent(21,1008.694);
    //SysError_NEW_R4[0][1]->SetBinError(21,31.75994);
    //SysError_NEW_R4[0][1]->SetMinimum(0);
    //SysError_NEW_R4[0][1]->SetMaximum(0.004914516);
    //SysError_NEW_R4[0][1]->SetEntries(1.378352e+007);
    
    SysError_NEW_R4[1][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[1][1]->SetBinContent(1,0.0005755971);
    SysError_NEW_R4[1][1]->SetBinContent(2,0.001374307);
    SysError_NEW_R4[1][1]->SetBinContent(3,0.001056478);
    SysError_NEW_R4[1][1]->SetBinContent(4,0.001695937);
    SysError_NEW_R4[1][1]->SetBinContent(5,0.001939601);
    SysError_NEW_R4[1][1]->SetBinContent(6,0.001611489);
    SysError_NEW_R4[1][1]->SetBinContent(7,0.001605361);
    SysError_NEW_R4[1][1]->SetBinContent(8,0.001157321);
    SysError_NEW_R4[1][1]->SetBinContent(9,0.001066348);
    SysError_NEW_R4[1][1]->SetBinContent(10,0.001663518);
    SysError_NEW_R4[1][1]->SetBinContent(11,0.002538134);
    SysError_NEW_R4[1][1]->SetBinContent(12,0.002500762);
    SysError_NEW_R4[1][1]->SetBinContent(13,0.003374801);
    SysError_NEW_R4[1][1]->SetBinContent(14,0.00249242);
    SysError_NEW_R4[1][1]->SetBinContent(15,0.00215648);
    SysError_NEW_R4[1][1]->SetBinContent(16,0.003736045);
    SysError_NEW_R4[1][1]->SetBinContent(17,0.00324301);
    SysError_NEW_R4[1][1]->SetBinContent(18,0.004993733);
    SysError_NEW_R4[1][1]->SetBinContent(19,0.003077209);
    SysError_NEW_R4[1][1]->SetBinContent(20,0.00545959);
    SysError_NEW_R4[1][1]->SetBinContent(21,326.3856);
    //SysError_NEW_R4[1][1]->SetBinError(21,18.06615);
    //SysError_NEW_R4[1][1]->SetMinimum(0);
    //SysError_NEW_R4[1][1]->SetMaximum(0.006005549);
    //SysError_NEW_R4[1][1]->SetEntries(2745520);
   
    SysError_NEW_R4[2][1]=new TH1D(Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_NEW_R4_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R4[2][1]->SetBinContent(1,0.002041717);
    SysError_NEW_R4[2][1]->SetBinContent(2,0.001938324);
    SysError_NEW_R4[2][1]->SetBinContent(3,0.002040177);
    SysError_NEW_R4[2][1]->SetBinContent(4,0.002495014);
    SysError_NEW_R4[2][1]->SetBinContent(5,0.002307688);
    SysError_NEW_R4[2][1]->SetBinContent(6,0.002136964);
    SysError_NEW_R4[2][1]->SetBinContent(7,0.002254385);
    SysError_NEW_R4[2][1]->SetBinContent(8,0.002850952);
    SysError_NEW_R4[2][1]->SetBinContent(9,0.003487578);
    SysError_NEW_R4[2][1]->SetBinContent(10,0.001877884);
    SysError_NEW_R4[2][1]->SetBinContent(11,0.002256881);
    SysError_NEW_R4[2][1]->SetBinContent(12,0.002440909);
    SysError_NEW_R4[2][1]->SetBinContent(13,0.002354678);
    SysError_NEW_R4[2][1]->SetBinContent(14,0.002298639);
    SysError_NEW_R4[2][1]->SetBinContent(15,0.002054923);
    SysError_NEW_R4[2][1]->SetBinContent(16,0.003569911);
    SysError_NEW_R4[2][1]->SetBinContent(17,0.005077444);
    SysError_NEW_R4[2][1]->SetBinContent(18,0.003830619);
    SysError_NEW_R4[2][1]->SetBinContent(19,0.003215455);
    SysError_NEW_R4[2][1]->SetBinContent(20,0.002056718);
    SysError_NEW_R4[2][1]->SetBinContent(21,552.1521);
    //SysError_NEW_R4[2][1]->SetBinError(21,23.49792);
    //SysError_NEW_R4[2][1]->SetMinimum(0);
    //SysError_NEW_R4[2][1]->SetMaximum(0.005585188);
    //SysError_NEW_R4[2][1]->SetEntries(2504020);
    
    
    /// \Run7_DEFAULT_CC0Pi_FGD1
    SysError_DEFAULT_R7[0][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[0][0]->SetBinContent(1,0.0003563851);
    SysError_DEFAULT_R7[0][0]->SetBinContent(2,0.0002946458);
    SysError_DEFAULT_R7[0][0]->SetBinContent(3,0.0002270575);
    SysError_DEFAULT_R7[0][0]->SetBinContent(4,0.0004091085);
    SysError_DEFAULT_R7[0][0]->SetBinContent(5,0.0007907087);
    SysError_DEFAULT_R7[0][0]->SetBinContent(6,0.001715434);
    SysError_DEFAULT_R7[0][0]->SetBinContent(7,0.001735239);
    SysError_DEFAULT_R7[0][0]->SetBinContent(8,0.00181217);
    SysError_DEFAULT_R7[0][0]->SetBinContent(9,0.0007640516);
    SysError_DEFAULT_R7[0][0]->SetBinContent(10,0.002235256);
    SysError_DEFAULT_R7[0][0]->SetBinContent(11,0.001637601);
    SysError_DEFAULT_R7[0][0]->SetBinContent(12,0.001519593);
    SysError_DEFAULT_R7[0][0]->SetBinContent(13,0.0021521);
    SysError_DEFAULT_R7[0][0]->SetBinContent(14,0.001281924);
    SysError_DEFAULT_R7[0][0]->SetBinContent(15,0.003836235);
    SysError_DEFAULT_R7[0][0]->SetBinContent(16,0.00234663);
    SysError_DEFAULT_R7[0][0]->SetBinContent(17,0.002384959);
    SysError_DEFAULT_R7[0][0]->SetBinContent(18,0.002577565);
    SysError_DEFAULT_R7[0][0]->SetBinContent(19,0.003080999);
    SysError_DEFAULT_R7[0][0]->SetBinContent(20,0.003709231);
    SysError_DEFAULT_R7[0][0]->SetBinContent(21,438.9766);
    //SysError_DEFAULT_R7[0][0]->SetBinError(21,20.95177);
    //SysError_DEFAULT_R7[0][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[0][0]->SetMaximum(0.004219859);
    //SysError_DEFAULT_R7[0][0]->SetEntries(6962520);
    
    SysError_DEFAULT_R7[1][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[1][0]->SetBinContent(1,0.0191732);
    SysError_DEFAULT_R7[1][0]->SetBinContent(2,0.007697472);
    SysError_DEFAULT_R7[1][0]->SetBinContent(3,0.003979707);
    SysError_DEFAULT_R7[1][0]->SetBinContent(4,0.005660918);
    SysError_DEFAULT_R7[1][0]->SetBinContent(5,0.001362726);
    SysError_DEFAULT_R7[1][0]->SetBinContent(6,0.001685425);
    SysError_DEFAULT_R7[1][0]->SetBinContent(7,0.002544606);
    SysError_DEFAULT_R7[1][0]->SetBinContent(8,0.002389383);
    SysError_DEFAULT_R7[1][0]->SetBinContent(9,0.002845598);
    SysError_DEFAULT_R7[1][0]->SetBinContent(10,0.003373473);
    SysError_DEFAULT_R7[1][0]->SetBinContent(11,0.001007973);
    SysError_DEFAULT_R7[1][0]->SetBinContent(12,0.004972818);
    SysError_DEFAULT_R7[1][0]->SetBinContent(13,0.002882418);
    SysError_DEFAULT_R7[1][0]->SetBinContent(14,0.004161932);
    SysError_DEFAULT_R7[1][0]->SetBinContent(15,0.004355434);
    SysError_DEFAULT_R7[1][0]->SetBinContent(16,0.007087838);
    SysError_DEFAULT_R7[1][0]->SetBinContent(17,0.009305901);
    SysError_DEFAULT_R7[1][0]->SetBinContent(18,0.002489224);
    SysError_DEFAULT_R7[1][0]->SetBinContent(19,0.01821054);
    SysError_DEFAULT_R7[1][0]->SetBinContent(20,0.009548101);
    SysError_DEFAULT_R7[1][0]->SetBinContent(21,77.13961);
    //SysError_DEFAULT_R7[1][0]->SetBinError(21,8.782916);
    //SysError_DEFAULT_R7[1][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[1][0]->SetMaximum(0.02109052);
    //SysError_DEFAULT_R7[1][0]->SetEntries(558020);
    
    
    
    SysError_DEFAULT_R7[2][0]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("Run7 %s FGD%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[2][0]->SetBinContent(1,0.0004959739);
    SysError_DEFAULT_R7[2][0]->SetBinContent(2,0.001709525);
    SysError_DEFAULT_R7[2][0]->SetBinContent(3,0.004706564);
    SysError_DEFAULT_R7[2][0]->SetBinContent(4,0.00368449);
    SysError_DEFAULT_R7[2][0]->SetBinContent(5,0.001293839);
    SysError_DEFAULT_R7[2][0]->SetBinContent(6,0.002271827);
    SysError_DEFAULT_R7[2][0]->SetBinContent(7,0.005512997);
    SysError_DEFAULT_R7[2][0]->SetBinContent(8,0.006067652);
    SysError_DEFAULT_R7[2][0]->SetBinContent(9,0.004778143);
    SysError_DEFAULT_R7[2][0]->SetBinContent(10,0.004084312);
    SysError_DEFAULT_R7[2][0]->SetBinContent(11,0.001633016);
    SysError_DEFAULT_R7[2][0]->SetBinContent(12,0.005111476);
    SysError_DEFAULT_R7[2][0]->SetBinContent(13,0.00631978);
    SysError_DEFAULT_R7[2][0]->SetBinContent(14,0.006065448);
    SysError_DEFAULT_R7[2][0]->SetBinContent(15,0.003593157);
    SysError_DEFAULT_R7[2][0]->SetBinContent(16,0.00416051);
    SysError_DEFAULT_R7[2][0]->SetBinContent(17,0.003878726);
    SysError_DEFAULT_R7[2][0]->SetBinContent(18,0.006326031);
    SysError_DEFAULT_R7[2][0]->SetBinContent(19,0.008410368);
    SysError_DEFAULT_R7[2][0]->SetBinContent(20,0.008520474);
    SysError_DEFAULT_R7[2][0]->SetBinContent(21,232.7144);
    //SysError_DEFAULT_R7[2][0]->SetBinError(21,15.25498);
    //SysError_DEFAULT_R7[2][0]->SetMinimum(0);
    //SysError_DEFAULT_R7[2][0]->SetMaximum(0.009372522);
    //SysError_DEFAULT_R7[2][0]->SetEntries(1045520);
    
    
    /// \Run7_NEW_CC0Pi_FGD1
    SysError_NEW_R7[0][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[0][0]->SetBinContent(1,0.0003724535);
    SysError_NEW_R7[0][0]->SetBinContent(2,0.0003299417);
    SysError_NEW_R7[0][0]->SetBinContent(3,0.0002084536);
    SysError_NEW_R7[0][0]->SetBinContent(4,0.0003036609);
    SysError_NEW_R7[0][0]->SetBinContent(5,0.000841479);
    SysError_NEW_R7[0][0]->SetBinContent(6,0.001495421);
    SysError_NEW_R7[0][0]->SetBinContent(7,0.001228888);
    SysError_NEW_R7[0][0]->SetBinContent(8,0.001691013);
    SysError_NEW_R7[0][0]->SetBinContent(9,0.00113151);
    SysError_NEW_R7[0][0]->SetBinContent(10,0.001208084);
    SysError_NEW_R7[0][0]->SetBinContent(11,0.001410226);
    SysError_NEW_R7[0][0]->SetBinContent(12,0.001015198);
    SysError_NEW_R7[0][0]->SetBinContent(13,0.002183343);
    SysError_NEW_R7[0][0]->SetBinContent(14,0.001808675);
    SysError_NEW_R7[0][0]->SetBinContent(15,0.002530684);
    SysError_NEW_R7[0][0]->SetBinContent(16,0.002174193);
    SysError_NEW_R7[0][0]->SetBinContent(17,0.002386927);
    SysError_NEW_R7[0][0]->SetBinContent(18,0.004537792);
    SysError_NEW_R7[0][0]->SetBinContent(19,0.003042469);
    SysError_NEW_R7[0][0]->SetBinContent(20,0.003660928);
    SysError_NEW_R7[0][0]->SetBinContent(21,439.677);
    //SysError_NEW_R7[0][0]->SetBinError(21,20.96848);
    //SysError_NEW_R7[0][0]->SetMinimum(0);
    //SysError_NEW_R7[0][0]->SetMaximum(0.004991571);
    //SysError_NEW_R7[0][0]->SetEntries(6962520);

    SysError_NEW_R7[1][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[1][0]->SetBinContent(1,0.009553708);
    SysError_NEW_R7[1][0]->SetBinContent(2,0.007599085);
    SysError_NEW_R7[1][0]->SetBinContent(3,0.004025446);
    SysError_NEW_R7[1][0]->SetBinContent(4,0.005543505);
    SysError_NEW_R7[1][0]->SetBinContent(5,0.001745696);
    SysError_NEW_R7[1][0]->SetBinContent(6,0.002262788);
    SysError_NEW_R7[1][0]->SetBinContent(7,0.002462464);
    SysError_NEW_R7[1][0]->SetBinContent(8,0.002086449);
    SysError_NEW_R7[1][0]->SetBinContent(9,0.002574739);
    SysError_NEW_R7[1][0]->SetBinContent(10,0.002810081);
    SysError_NEW_R7[1][0]->SetBinContent(11,0.001132397);
    SysError_NEW_R7[1][0]->SetBinContent(12,0.004678889);
    SysError_NEW_R7[1][0]->SetBinContent(13,0.003087848);
    SysError_NEW_R7[1][0]->SetBinContent(14,0.003494954);
    SysError_NEW_R7[1][0]->SetBinContent(15,0.007045393);
    SysError_NEW_R7[1][0]->SetBinContent(16,0.003353005);
    SysError_NEW_R7[1][0]->SetBinContent(17,0.01159761);
    SysError_NEW_R7[1][0]->SetBinContent(18,0.001611425);
    SysError_NEW_R7[1][0]->SetBinContent(19,0.01004827);
    SysError_NEW_R7[1][0]->SetBinContent(20,0.009409289);
    SysError_NEW_R7[1][0]->SetBinContent(21,77.26782);
    //SysError_NEW_R7[1][0]->SetBinError(21,8.790211);
    //SysError_NEW_R7[1][0]->SetMinimum(0);
    //SysError_NEW_R7[1][0]->SetMaximum(0.01275737);
    //SysError_NEW_R7[1][0]->SetEntries(558020);   

    SysError_NEW_R7[2][0]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_NEW_R7[2][0]->SetBinContent(1,0.0005621465);
    SysError_NEW_R7[2][0]->SetBinContent(2,0.001911903);
    SysError_NEW_R7[2][0]->SetBinContent(3,0.004423862);
    SysError_NEW_R7[2][0]->SetBinContent(4,0.003269475);
    SysError_NEW_R7[2][0]->SetBinContent(5,0.001333155);
    SysError_NEW_R7[2][0]->SetBinContent(6,0.002686982);
    SysError_NEW_R7[2][0]->SetBinContent(7,0.00518121);
    SysError_NEW_R7[2][0]->SetBinContent(8,0.005824096);
    SysError_NEW_R7[2][0]->SetBinContent(9,0.004895982);
    SysError_NEW_R7[2][0]->SetBinContent(10,0.002883145);
    SysError_NEW_R7[2][0]->SetBinContent(11,0.002086633);
    SysError_NEW_R7[2][0]->SetBinContent(12,0.005038046);
    SysError_NEW_R7[2][0]->SetBinContent(13,0.00485735);
    SysError_NEW_R7[2][0]->SetBinContent(14,0.00584749);
    SysError_NEW_R7[2][0]->SetBinContent(15,0.003376139);
    SysError_NEW_R7[2][0]->SetBinContent(16,0.004325206);
    SysError_NEW_R7[2][0]->SetBinContent(17,0.005252472);
    SysError_NEW_R7[2][0]->SetBinContent(18,0.009325034);
    SysError_NEW_R7[2][0]->SetBinContent(19,0.01124545);
    SysError_NEW_R7[2][0]->SetBinContent(20,0.006939329);
    SysError_NEW_R7[2][0]->SetBinContent(21,232.7823);
    //SysError_NEW_R7[2][0]->SetBinError(21,15.2572);
    //SysError_NEW_R7[2][0]->SetMinimum(0);
    //SysError_NEW_R7[2][0]->SetMaximum(0.01236999);
    //SysError_NEW_R7[2][0]->SetEntries(1045520);
    

    /// \Run7_ANTY_CC0Pi_FGD1
    SysError_ANTY_R7[0][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[0][0]->SetBinContent(1,0.0003692655);
    SysError_ANTY_R7[0][0]->SetBinContent(2,0.000280205);
    SysError_ANTY_R7[0][0]->SetBinContent(3,0.000175347);
    SysError_ANTY_R7[0][0]->SetBinContent(4,0.0002567158);
    SysError_ANTY_R7[0][0]->SetBinContent(5,0.0008464025);
    SysError_ANTY_R7[0][0]->SetBinContent(6,0.001306014);
    SysError_ANTY_R7[0][0]->SetBinContent(7,0.0009323772);
    SysError_ANTY_R7[0][0]->SetBinContent(8,0.001281059);
    SysError_ANTY_R7[0][0]->SetBinContent(9,0.0007180551);
    SysError_ANTY_R7[0][0]->SetBinContent(10,0.0008765685);
    SysError_ANTY_R7[0][0]->SetBinContent(11,0.0008579007);
    SysError_ANTY_R7[0][0]->SetBinContent(12,0.0008359335);
    SysError_ANTY_R7[0][0]->SetBinContent(13,0.001935874);
    SysError_ANTY_R7[0][0]->SetBinContent(14,0.00167145);
    SysError_ANTY_R7[0][0]->SetBinContent(15,0.001353875);
    SysError_ANTY_R7[0][0]->SetBinContent(16,0.001808869);
    SysError_ANTY_R7[0][0]->SetBinContent(17,0.001746582);
    SysError_ANTY_R7[0][0]->SetBinContent(18,0.003908188);
    SysError_ANTY_R7[0][0]->SetBinContent(19,0.003934169);
    SysError_ANTY_R7[0][0]->SetBinContent(20,0.003103566);
    SysError_ANTY_R7[0][0]->SetBinContent(21,440.4027);
    //SysError_ANTY_R7[0][0]->SetBinError(21,20.98577);
    //SysError_ANTY_R7[0][0]->SetMinimum(0);
    //SysError_ANTY_R7[0][0]->SetMaximum(0.004327585);
    //SysError_ANTY_R7[0][0]->SetEntries(6962520);

    SysError_ANTY_R7[1][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[1][0]->SetBinContent(1,0.01155397);
    SysError_ANTY_R7[1][0]->SetBinContent(2,0.006712195);
    SysError_ANTY_R7[1][0]->SetBinContent(3,0.00356164);
    SysError_ANTY_R7[1][0]->SetBinContent(4,0.004794143);
    SysError_ANTY_R7[1][0]->SetBinContent(5,0.001585964);
    SysError_ANTY_R7[1][0]->SetBinContent(6,0.001548324);
    SysError_ANTY_R7[1][0]->SetBinContent(7,0.002170346);
    SysError_ANTY_R7[1][0]->SetBinContent(8,0.001949537);
    SysError_ANTY_R7[1][0]->SetBinContent(9,0.002910827);
    SysError_ANTY_R7[1][0]->SetBinContent(10,0.002341397);
    SysError_ANTY_R7[1][0]->SetBinContent(11,0.001106165);
    SysError_ANTY_R7[1][0]->SetBinContent(12,0.004302091);
    SysError_ANTY_R7[1][0]->SetBinContent(13,0.00344977);
    SysError_ANTY_R7[1][0]->SetBinContent(14,0.003071047);
    SysError_ANTY_R7[1][0]->SetBinContent(15,0.006732935);
    SysError_ANTY_R7[1][0]->SetBinContent(16,0.0023975);
    SysError_ANTY_R7[1][0]->SetBinContent(17,0.006443726);
    SysError_ANTY_R7[1][0]->SetBinContent(18,0.001308092);
    SysError_ANTY_R7[1][0]->SetBinContent(19,0.007476402);
    SysError_ANTY_R7[1][0]->SetBinContent(20,0.008714151);
    SysError_ANTY_R7[1][0]->SetBinContent(21,77.18055);
    //SysError_ANTY_R7[1][0]->SetBinError(21,8.785246);
    //SysError_ANTY_R7[1][0]->SetMinimum(0);
    //SysError_ANTY_R7[1][0]->SetMaximum(0.01270936);
    //SysError_ANTY_R7[1][0]->SetEntries(558020);

    SysError_ANTY_R7[2][0]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[2][0]->SetBinContent(1,0.0006309369);
    SysError_ANTY_R7[2][0]->SetBinContent(2,0.001481893);
    SysError_ANTY_R7[2][0]->SetBinContent(3,0.003827086);
    SysError_ANTY_R7[2][0]->SetBinContent(4,0.003019989);
    SysError_ANTY_R7[2][0]->SetBinContent(5,0.001581729);
    SysError_ANTY_R7[2][0]->SetBinContent(6,0.002428408);
    SysError_ANTY_R7[2][0]->SetBinContent(7,0.004514832);
    SysError_ANTY_R7[2][0]->SetBinContent(8,0.005000499);
    SysError_ANTY_R7[2][0]->SetBinContent(9,0.004083075);
    SysError_ANTY_R7[2][0]->SetBinContent(10,0.002521996);
    SysError_ANTY_R7[2][0]->SetBinContent(11,0.001777678);
    SysError_ANTY_R7[2][0]->SetBinContent(12,0.004674803);
    SysError_ANTY_R7[2][0]->SetBinContent(13,0.004731213);
    SysError_ANTY_R7[2][0]->SetBinContent(14,0.005287975);
    SysError_ANTY_R7[2][0]->SetBinContent(15,0.003612548);
    SysError_ANTY_R7[2][0]->SetBinContent(16,0.004328516);
    SysError_ANTY_R7[2][0]->SetBinContent(17,0.002217384);
    SysError_ANTY_R7[2][0]->SetBinContent(18,0.008693606);
    SysError_ANTY_R7[2][0]->SetBinContent(19,0.01056632);
    SysError_ANTY_R7[2][0]->SetBinContent(20,0.006467401);
    SysError_ANTY_R7[2][0]->SetBinContent(21,229.6893);
    //SysError_ANTY_R7[2][0]->SetBinError(21,15.1555);
    //SysError_ANTY_R7[2][0]->SetMinimum(0);
    //SysError_ANTY_R7[2][0]->SetMaximum(0.01162296);
    //SysError_ANTY_R7[2][0]->SetEntries(1045520);
    
    /// \Run7_PI-_CC0Pi_FGD1
    SysError_PI_R7[0][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[0][0]->SetBinContent(1,0.0003503107);
    SysError_PI_R7[0][0]->SetBinContent(2,0.0002944912);
    SysError_PI_R7[0][0]->SetBinContent(3,0.0002012828);
    SysError_PI_R7[0][0]->SetBinContent(4,0.0002750026);
    SysError_PI_R7[0][0]->SetBinContent(5,0.0006162159);
    SysError_PI_R7[0][0]->SetBinContent(6,0.001097678);
    SysError_PI_R7[0][0]->SetBinContent(7,0.0007727942);
    SysError_PI_R7[0][0]->SetBinContent(8,0.002035432);
    SysError_PI_R7[0][0]->SetBinContent(9,0.0007603499);
    SysError_PI_R7[0][0]->SetBinContent(10,0.0008868986);
    SysError_PI_R7[0][0]->SetBinContent(11,0.0008904408);
    SysError_PI_R7[0][0]->SetBinContent(12,0.0008852759);
    SysError_PI_R7[0][0]->SetBinContent(13,0.001661735);
    SysError_PI_R7[0][0]->SetBinContent(14,0.001391386);
    SysError_PI_R7[0][0]->SetBinContent(15,0.001296609);
    SysError_PI_R7[0][0]->SetBinContent(16,0.001502927);
    SysError_PI_R7[0][0]->SetBinContent(17,0.001301493);
    SysError_PI_R7[0][0]->SetBinContent(18,0.003891436);
    SysError_PI_R7[0][0]->SetBinContent(19,0.002031968);
    SysError_PI_R7[0][0]->SetBinContent(20,0.002891982);
    SysError_PI_R7[0][0]->SetBinContent(21,440.2079);
    //SysError_PI_R7[0][0]->SetBinError(21,20.98113);
    //SysError_PI_R7[0][0]->SetMinimum(0);
    //SysError_PI_R7[0][0]->SetMaximum(0.004280579);
    //SysError_PI_R7[0][0]->SetEntries(6962520);

    SysError_PI_R7[1][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[1][0]->SetBinContent(1,0.01340698);
    SysError_PI_R7[1][0]->SetBinContent(2,0.005504255);
    SysError_PI_R7[1][0]->SetBinContent(3,0.003774503);
    SysError_PI_R7[1][0]->SetBinContent(4,0.003916822);
    SysError_PI_R7[1][0]->SetBinContent(5,0.001546815);
    SysError_PI_R7[1][0]->SetBinContent(6,0.002089985);
    SysError_PI_R7[1][0]->SetBinContent(7,0.001832301);
    SysError_PI_R7[1][0]->SetBinContent(8,0.001604219);
    SysError_PI_R7[1][0]->SetBinContent(9,0.002644031);
    SysError_PI_R7[1][0]->SetBinContent(10,0.002457775);
    SysError_PI_R7[1][0]->SetBinContent(11,0.0013912);
    SysError_PI_R7[1][0]->SetBinContent(12,0.00597924);
    SysError_PI_R7[1][0]->SetBinContent(13,0.002487806);
    SysError_PI_R7[1][0]->SetBinContent(14,0.002608511);
    SysError_PI_R7[1][0]->SetBinContent(15,0.006684872);
    SysError_PI_R7[1][0]->SetBinContent(16,0.001937482);
    SysError_PI_R7[1][0]->SetBinContent(17,0.005646951);
    SysError_PI_R7[1][0]->SetBinContent(18,0.001308092);
    SysError_PI_R7[1][0]->SetBinContent(19,0.006592614);
    SysError_PI_R7[1][0]->SetBinContent(20,0.006969797);
    SysError_PI_R7[1][0]->SetBinContent(21,77.17842);
    //SysError_PI_R7[1][0]->SetBinError(21,8.785125);
    //SysError_PI_R7[1][0]->SetMinimum(0);
    //SysError_PI_R7[1][0]->SetMaximum(0.01474767);
    //SysError_PI_R7[1][0]->SetEntries(558020); 

    SysError_PI_R7[2][0]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[0].Data()),Form("SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[0].Data()) ,20, 0, 5000);
    SysError_PI_R7[2][0]->SetBinContent(1,0.0007669186);
    SysError_PI_R7[2][0]->SetBinContent(2,0.002560339);
    SysError_PI_R7[2][0]->SetBinContent(3,0.003234835);
    SysError_PI_R7[2][0]->SetBinContent(4,0.003361363);
    SysError_PI_R7[2][0]->SetBinContent(5,0.001337949);
    SysError_PI_R7[2][0]->SetBinContent(6,0.002494774);
    SysError_PI_R7[2][0]->SetBinContent(7,0.004237673);
    SysError_PI_R7[2][0]->SetBinContent(8,0.004140546);
    SysError_PI_R7[2][0]->SetBinContent(9,0.00499989);
    SysError_PI_R7[2][0]->SetBinContent(10,0.002512971);
    SysError_PI_R7[2][0]->SetBinContent(11,0.002263098);
    SysError_PI_R7[2][0]->SetBinContent(12,0.003745798);
    SysError_PI_R7[2][0]->SetBinContent(13,0.004302551);
    SysError_PI_R7[2][0]->SetBinContent(14,0.005228871);
    SysError_PI_R7[2][0]->SetBinContent(15,0.003324836);
    SysError_PI_R7[2][0]->SetBinContent(16,0.003851542);
    SysError_PI_R7[2][0]->SetBinContent(17,0.002250239);
    SysError_PI_R7[2][0]->SetBinContent(18,0.0094037);
    SysError_PI_R7[2][0]->SetBinContent(19,0.01257664);
    SysError_PI_R7[2][0]->SetBinContent(20,0.006790344);
    SysError_PI_R7[2][0]->SetBinContent(21,229.7711);
    //SysError_PI_R7[2][0]->SetBinError(21,15.1582);
    //SysError_PI_R7[2][0]->SetMinimum(0);
    //SysError_PI_R7[2][0]->SetMaximum(0.01383431);
    //SysError_PI_R7[2][0]->SetEntries(1045520);
    
    
    
    /// \Run7_DEFAULT_CC0Pi_FGD2
    SysError_DEFAULT_R7[0][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[0][1]->SetBinContent(1,0.0001090055);
    SysError_DEFAULT_R7[0][1]->SetBinContent(2,7.568441e-005);
    SysError_DEFAULT_R7[0][1]->SetBinContent(3,6.243293e-005);
    SysError_DEFAULT_R7[0][1]->SetBinContent(4,6.887594e-005);
    SysError_DEFAULT_R7[0][1]->SetBinContent(5,0.0004410151);
    SysError_DEFAULT_R7[0][1]->SetBinContent(6,0.000167483);
    SysError_DEFAULT_R7[0][1]->SetBinContent(7,0.0002727449);
    SysError_DEFAULT_R7[0][1]->SetBinContent(8,0.0003113257);
    SysError_DEFAULT_R7[0][1]->SetBinContent(9,0.0009094375);
    SysError_DEFAULT_R7[0][1]->SetBinContent(10,0.0007293056);
    SysError_DEFAULT_R7[0][1]->SetBinContent(11,0.0002882282);
    SysError_DEFAULT_R7[0][1]->SetBinContent(12,0.0004762332);
    SysError_DEFAULT_R7[0][1]->SetBinContent(13,0.0004515529);
    SysError_DEFAULT_R7[0][1]->SetBinContent(14,0.0006058381);
    SysError_DEFAULT_R7[0][1]->SetBinContent(15,0.0007530693);
    SysError_DEFAULT_R7[0][1]->SetBinContent(16,0.000524678);
    SysError_DEFAULT_R7[0][1]->SetBinContent(17,0.0005994095);
    SysError_DEFAULT_R7[0][1]->SetBinContent(18,0.001454002);
    SysError_DEFAULT_R7[0][1]->SetBinContent(19,0.0008374341);
    SysError_DEFAULT_R7[0][1]->SetBinContent(20,0.0006147485);
    SysError_DEFAULT_R7[0][1]->SetBinContent(21,389.8028);
    //SysError_DEFAULT_R7[0][1]->SetBinError(21,19.74342);
    //SysError_DEFAULT_R7[0][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[0][1]->SetMaximum(0.001599402);
    //SysError_DEFAULT_R7[0][1]->SetEntries(6529020);
    
    SysError_DEFAULT_R7[1][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[1][1]->SetBinContent(1,0.005152212);
    SysError_DEFAULT_R7[1][1]->SetBinContent(2,0.002422842);
    SysError_DEFAULT_R7[1][1]->SetBinContent(3,0.001004447);
    SysError_DEFAULT_R7[1][1]->SetBinContent(4,0.00268074);
    SysError_DEFAULT_R7[1][1]->SetBinContent(5,0.0004912668);
    SysError_DEFAULT_R7[1][1]->SetBinContent(6,0.0006346996);
    SysError_DEFAULT_R7[1][1]->SetBinContent(7,0.0006932698);
    SysError_DEFAULT_R7[1][1]->SetBinContent(8,0.001041178);
    SysError_DEFAULT_R7[1][1]->SetBinContent(9,0.003373182);
    SysError_DEFAULT_R7[1][1]->SetBinContent(10,0.001643137);
    SysError_DEFAULT_R7[1][1]->SetBinContent(11,0.0009276369);
    SysError_DEFAULT_R7[1][1]->SetBinContent(12,0.004039354);
    SysError_DEFAULT_R7[1][1]->SetBinContent(13,0.002568346);
    SysError_DEFAULT_R7[1][1]->SetBinContent(14,0.004620512);
    SysError_DEFAULT_R7[1][1]->SetBinContent(15,0.003019116);
    SysError_DEFAULT_R7[1][1]->SetBinContent(16,0.0004136843);
    SysError_DEFAULT_R7[1][1]->SetBinContent(17,0.0005775732);
    SysError_DEFAULT_R7[1][1]->SetBinContent(18,0.004032083);
    SysError_DEFAULT_R7[1][1]->SetBinContent(19,0.00897317);
    SysError_DEFAULT_R7[1][1]->SetBinContent(20,0.0009474543);
    SysError_DEFAULT_R7[1][1]->SetBinContent(21,80.91214);
    //SysError_DEFAULT_R7[1][1]->SetBinError(21,8.995117);
    //SysError_DEFAULT_R7[1][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[1][1]->SetMaximum(0.009870487);
    //SysError_DEFAULT_R7[1][1]->SetEntries(484520);
    
    SysError_DEFAULT_R7[2][1]=new TH1D(Form("SysError_DEFAULT_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("Run7 %s FGD%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_DEFAULT_R7[2][1]->SetBinContent(1,0.000368598);
    SysError_DEFAULT_R7[2][1]->SetBinContent(2,0.0004976625);
    SysError_DEFAULT_R7[2][1]->SetBinContent(3,0.0003437496);
    SysError_DEFAULT_R7[2][1]->SetBinContent(4,0.0008075358);
    SysError_DEFAULT_R7[2][1]->SetBinContent(5,0.0002972212);
    SysError_DEFAULT_R7[2][1]->SetBinContent(6,0.0006672894);
    SysError_DEFAULT_R7[2][1]->SetBinContent(7,0.0006721038);
    SysError_DEFAULT_R7[2][1]->SetBinContent(8,0.0009740036);
    SysError_DEFAULT_R7[2][1]->SetBinContent(9,0.001315325);
    SysError_DEFAULT_R7[2][1]->SetBinContent(10,0.0004837407);
    SysError_DEFAULT_R7[2][1]->SetBinContent(11,0.0009418997);
    SysError_DEFAULT_R7[2][1]->SetBinContent(12,0.0007230632);
    SysError_DEFAULT_R7[2][1]->SetBinContent(13,0.0005798771);
    SysError_DEFAULT_R7[2][1]->SetBinContent(14,0.0004429312);
    SysError_DEFAULT_R7[2][1]->SetBinContent(15,0.001662038);
    SysError_DEFAULT_R7[2][1]->SetBinContent(16,0.003884687);
    SysError_DEFAULT_R7[2][1]->SetBinContent(17,0.001971118);
    SysError_DEFAULT_R7[2][1]->SetBinContent(18,0.001237667);
    SysError_DEFAULT_R7[2][1]->SetBinContent(19,0.001820208);
    SysError_DEFAULT_R7[2][1]->SetBinContent(20,0.001247904);
    SysError_DEFAULT_R7[2][1]->SetBinContent(21,197.0885);
    //SysError_DEFAULT_R7[2][1]->SetBinError(21,14.03882);
    //SysError_DEFAULT_R7[2][1]->SetMinimum(0);
    //SysError_DEFAULT_R7[2][1]->SetMaximum(0.004273156);
    //SysError_DEFAULT_R7[2][1]->SetEntries(933020);
    
    
    /// \Run7_NEW_CC0Pi_FGD2
    SysError_NEW_R7[0][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[0][1]->SetBinContent(1,0.0002783306);
    SysError_NEW_R7[0][1]->SetBinContent(2,0.0002063328);
    SysError_NEW_R7[0][1]->SetBinContent(3,0.0001914643);
    SysError_NEW_R7[0][1]->SetBinContent(4,0.0002068806);
    SysError_NEW_R7[0][1]->SetBinContent(5,0.001035764);
    SysError_NEW_R7[0][1]->SetBinContent(6,0.0003796424);
    SysError_NEW_R7[0][1]->SetBinContent(7,0.001028214);
    SysError_NEW_R7[0][1]->SetBinContent(8,0.0008892022);
    SysError_NEW_R7[0][1]->SetBinContent(9,0.002004566);
    SysError_NEW_R7[0][1]->SetBinContent(10,0.001917842);
    SysError_NEW_R7[0][1]->SetBinContent(11,0.0008424893);
    SysError_NEW_R7[0][1]->SetBinContent(12,0.002026263);
    SysError_NEW_R7[0][1]->SetBinContent(13,0.001686232);
    SysError_NEW_R7[0][1]->SetBinContent(14,0.001676144);
    SysError_NEW_R7[0][1]->SetBinContent(15,0.00188675);
    SysError_NEW_R7[0][1]->SetBinContent(16,0.0009458202);
    SysError_NEW_R7[0][1]->SetBinContent(17,0.002021192);
    SysError_NEW_R7[0][1]->SetBinContent(18,0.003465161);
    SysError_NEW_R7[0][1]->SetBinContent(19,0.002870062);
    SysError_NEW_R7[0][1]->SetBinContent(20,0.001552912);
    SysError_NEW_R7[0][1]->SetBinContent(21,390.6543);
    //SysError_NEW_R7[0][1]->SetBinError(21,19.76498);
    //SysError_NEW_R7[0][1]->SetMinimum(0);
    //SysError_NEW_R7[0][1]->SetMaximum(0.003811677);
    //SysError_NEW_R7[0][1]->SetEntries(6529020);

    SysError_NEW_R7[1][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[1][1]->SetBinContent(1,0.01680344);
    SysError_NEW_R7[1][1]->SetBinContent(2,0.005662653);
    SysError_NEW_R7[1][1]->SetBinContent(3,0.002246445);
    SysError_NEW_R7[1][1]->SetBinContent(4,0.006142054);
    SysError_NEW_R7[1][1]->SetBinContent(5,0.001196905);
    SysError_NEW_R7[1][1]->SetBinContent(6,0.001729217);
    SysError_NEW_R7[1][1]->SetBinContent(7,0.00134922);
    SysError_NEW_R7[1][1]->SetBinContent(8,0.002409636);
    SysError_NEW_R7[1][1]->SetBinContent(9,0.008027408);
    SysError_NEW_R7[1][1]->SetBinContent(10,0.005697072);
    SysError_NEW_R7[1][1]->SetBinContent(11,0.002064395);
    SysError_NEW_R7[1][1]->SetBinContent(12,0.009586548);
    SysError_NEW_R7[1][1]->SetBinContent(13,0.006821906);
    SysError_NEW_R7[1][1]->SetBinContent(14,0.01001307);
    SysError_NEW_R7[1][1]->SetBinContent(15,0.006923772);
    SysError_NEW_R7[1][1]->SetBinContent(16,0.001354737);
    SysError_NEW_R7[1][1]->SetBinContent(17,0.002624721);
    SysError_NEW_R7[1][1]->SetBinContent(18,0.008198054);
    SysError_NEW_R7[1][1]->SetBinContent(19,0.01304393);
    SysError_NEW_R7[1][1]->SetBinContent(20,0.001007012);
    SysError_NEW_R7[1][1]->SetBinContent(21,81.13042);
    //SysError_NEW_R7[1][1]->SetBinError(21,9.007243);
    //SysError_NEW_R7[1][1]->SetMinimum(0);
    //SysError_NEW_R7[1][1]->SetMaximum(0.01848378);
    //SysError_NEW_R7[1][1]->SetEntries(484520);

    SysError_NEW_R7[2][1]=new TH1D(Form( "SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_NEW_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_NEW_R7[2][1]->SetBinContent(1,0.0006498255);
    SysError_NEW_R7[2][1]->SetBinContent(2,0.001222968);
    SysError_NEW_R7[2][1]->SetBinContent(3,0.0007092882);
    SysError_NEW_R7[2][1]->SetBinContent(4,0.002025357);
    SysError_NEW_R7[2][1]->SetBinContent(5,0.001033585);
    SysError_NEW_R7[2][1]->SetBinContent(6,0.00191843);
    SysError_NEW_R7[2][1]->SetBinContent(7,0.002320694);
    SysError_NEW_R7[2][1]->SetBinContent(8,0.00265238);
    SysError_NEW_R7[2][1]->SetBinContent(9,0.003079301);
    SysError_NEW_R7[2][1]->SetBinContent(10,0.001436202);
    SysError_NEW_R7[2][1]->SetBinContent(11,0.00232716);
    SysError_NEW_R7[2][1]->SetBinContent(12,0.002135928);
    SysError_NEW_R7[2][1]->SetBinContent(13,0.001784067);
    SysError_NEW_R7[2][1]->SetBinContent(14,0.0011741);
    SysError_NEW_R7[2][1]->SetBinContent(15,0.006385149);
    SysError_NEW_R7[2][1]->SetBinContent(16,0.008415529);
    SysError_NEW_R7[2][1]->SetBinContent(17,0.004964468);
    SysError_NEW_R7[2][1]->SetBinContent(18,0.002898512);
    SysError_NEW_R7[2][1]->SetBinContent(19,0.004379019);
    SysError_NEW_R7[2][1]->SetBinContent(20,0.004113224);
    SysError_NEW_R7[2][1]->SetBinContent(21,196.844);
    //SysError_NEW_R7[2][1]->SetBinError(21,14.03011);
    //SysError_NEW_R7[2][1]->SetMinimum(0);
    //SysError_NEW_R7[2][1]->SetMaximum(0.009257082);
    //SysError_NEW_R7[2][1]->SetEntries(933020);
    
    
        /// \Run7_ANTY_CC0Pi_FGD2
    SysError_ANTY_R7[0][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[0][1]->SetBinContent(1,0.0002649299);
    SysError_ANTY_R7[0][1]->SetBinContent(2,0.0001494037);
    SysError_ANTY_R7[0][1]->SetBinContent(3,0.0001402518);
    SysError_ANTY_R7[0][1]->SetBinContent(4,0.0002155677);
    SysError_ANTY_R7[0][1]->SetBinContent(5,0.000521786);
    SysError_ANTY_R7[0][1]->SetBinContent(6,0.0003461577);
    SysError_ANTY_R7[0][1]->SetBinContent(7,0.0007832458);
    SysError_ANTY_R7[0][1]->SetBinContent(8,0.0007877356);
    SysError_ANTY_R7[0][1]->SetBinContent(9,0.001670037);
    SysError_ANTY_R7[0][1]->SetBinContent(10,0.0009469945);
    SysError_ANTY_R7[0][1]->SetBinContent(11,0.0005094844);
    SysError_ANTY_R7[0][1]->SetBinContent(12,0.001192002);
    SysError_ANTY_R7[0][1]->SetBinContent(13,0.001299872);
    SysError_ANTY_R7[0][1]->SetBinContent(14,0.001038231);
    SysError_ANTY_R7[0][1]->SetBinContent(15,0.001348565);
    SysError_ANTY_R7[0][1]->SetBinContent(16,0.001961272);
    SysError_ANTY_R7[0][1]->SetBinContent(17,0.001401076);
    SysError_ANTY_R7[0][1]->SetBinContent(18,0.002173986);
    SysError_ANTY_R7[0][1]->SetBinContent(19,0.002935469);
    SysError_ANTY_R7[0][1]->SetBinContent(20,0.001008608);
    SysError_ANTY_R7[0][1]->SetBinContent(21,390.3381);
    //SysError_ANTY_R7[0][1]->SetBinError(21,19.75698);
    //SysError_ANTY_R7[0][1]->SetMinimum(0);
    //SysError_ANTY_R7[0][1]->SetMaximum(0.003229016);
    //SysError_ANTY_R7[0][1]->SetEntries(6529020);

    SysError_ANTY_R7[1][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[1][1]->SetBinContent(1,0.01477581);
    SysError_ANTY_R7[1][1]->SetBinContent(2,0.003000616);
    SysError_ANTY_R7[1][1]->SetBinContent(3,0.001787923);
    SysError_ANTY_R7[1][1]->SetBinContent(4,0.002780693);
    SysError_ANTY_R7[1][1]->SetBinContent(5,0.001051145);
    SysError_ANTY_R7[1][1]->SetBinContent(6,0.00124441);
    SysError_ANTY_R7[1][1]->SetBinContent(7,0.001897817);
    SysError_ANTY_R7[1][1]->SetBinContent(8,0.002180119);
    SysError_ANTY_R7[1][1]->SetBinContent(9,0.004025159);
    SysError_ANTY_R7[1][1]->SetBinContent(10,0.003921613);
    SysError_ANTY_R7[1][1]->SetBinContent(11,0.001636269);
    SysError_ANTY_R7[1][1]->SetBinContent(12,0.004865664);
    SysError_ANTY_R7[1][1]->SetBinContent(13,0.008360295);
    SysError_ANTY_R7[1][1]->SetBinContent(14,0.006237308);
    SysError_ANTY_R7[1][1]->SetBinContent(15,0.003214336);
    SysError_ANTY_R7[1][1]->SetBinContent(16,0.001369065);
    SysError_ANTY_R7[1][1]->SetBinContent(17,0.001783072);
    SysError_ANTY_R7[1][1]->SetBinContent(18,0.01011344);
    SysError_ANTY_R7[1][1]->SetBinContent(19,0.02784639);
    SysError_ANTY_R7[1][1]->SetBinContent(20,0.001545321);
    SysError_ANTY_R7[1][1]->SetBinContent(21,80.96223);
    //SysError_ANTY_R7[1][1]->SetBinError(21,8.997901);
    //SysError_ANTY_R7[1][1]->SetMinimum(0);
    //SysError_ANTY_R7[1][1]->SetMaximum(0.03063103);
    //SysError_ANTY_R7[1][1]->SetEntries(484520);

    SysError_ANTY_R7[2][1]=new TH1D(Form( "SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_ANTY_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_ANTY_R7[2][1]->SetBinContent(1,0.0005891582);
    SysError_ANTY_R7[2][1]->SetBinContent(2,0.001086969);
    SysError_ANTY_R7[2][1]->SetBinContent(3,0.0007658804);
    SysError_ANTY_R7[2][1]->SetBinContent(4,0.001601198);
    SysError_ANTY_R7[2][1]->SetBinContent(5,0.0009178493);
    SysError_ANTY_R7[2][1]->SetBinContent(6,0.001465329);
    SysError_ANTY_R7[2][1]->SetBinContent(7,0.001677417);
    SysError_ANTY_R7[2][1]->SetBinContent(8,0.001486192);
    SysError_ANTY_R7[2][1]->SetBinContent(9,0.002228334);
    SysError_ANTY_R7[2][1]->SetBinContent(10,0.001486887);
    SysError_ANTY_R7[2][1]->SetBinContent(11,0.002191935);
    SysError_ANTY_R7[2][1]->SetBinContent(12,0.001279956);
    SysError_ANTY_R7[2][1]->SetBinContent(13,0.001199154);
    SysError_ANTY_R7[2][1]->SetBinContent(14,0.001089327);
    SysError_ANTY_R7[2][1]->SetBinContent(15,0.003073688);
    SysError_ANTY_R7[2][1]->SetBinContent(16,0.008309921);
    SysError_ANTY_R7[2][1]->SetBinContent(17,0.006967563);
    SysError_ANTY_R7[2][1]->SetBinContent(18,0.001581779);
    SysError_ANTY_R7[2][1]->SetBinContent(19,0.002487091);
    SysError_ANTY_R7[2][1]->SetBinContent(20,0.004345134);
    SysError_ANTY_R7[2][1]->SetBinContent(21,197.0025);
    //SysError_ANTY_R7[2][1]->SetBinError(21,14.03576);
    //SysError_ANTY_R7[2][1]->SetMinimum(0);
    //SysError_ANTY_R7[2][1]->SetMaximum(0.009140913);
    //SysError_ANTY_R7[2][1]->SetEntries(933020);
    
    
    /// \Run7_PI-_CC0Pi_FGD1
    SysError_PI_R7[0][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[0].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[0][1]->SetBinContent(1,0.0003082762);
    SysError_PI_R7[0][1]->SetBinContent(2,0.0001414935);
    SysError_PI_R7[0][1]->SetBinContent(3,0.0001358722);
    SysError_PI_R7[0][1]->SetBinContent(4,0.0001953771);
    SysError_PI_R7[0][1]->SetBinContent(5,0.0004678549);
    SysError_PI_R7[0][1]->SetBinContent(6,0.0003983949);
    SysError_PI_R7[0][1]->SetBinContent(7,0.0007676184);
    SysError_PI_R7[0][1]->SetBinContent(8,0.0007758723);
    SysError_PI_R7[0][1]->SetBinContent(9,0.001957403);
    SysError_PI_R7[0][1]->SetBinContent(10,0.0008552075);
    SysError_PI_R7[0][1]->SetBinContent(11,0.0004736373);
    SysError_PI_R7[0][1]->SetBinContent(12,0.001168084);
    SysError_PI_R7[0][1]->SetBinContent(13,0.001563428);
    SysError_PI_R7[0][1]->SetBinContent(14,0.0009409506);
    SysError_PI_R7[0][1]->SetBinContent(15,0.00128675);
    SysError_PI_R7[0][1]->SetBinContent(16,0.002663752);
    SysError_PI_R7[0][1]->SetBinContent(17,0.001334488);
    SysError_PI_R7[0][1]->SetBinContent(18,0.002038755);
    SysError_PI_R7[0][1]->SetBinContent(19,0.002355634);
    SysError_PI_R7[0][1]->SetBinContent(20,0.0009551824);
    SysError_PI_R7[0][1]->SetBinContent(21,390.2274);
    //SysError_PI_R7[0][1]->SetBinError(21,19.75417);
    //SysError_PI_R7[0][1]->SetMinimum(0);
    //SysError_PI_R7[0][1]->SetMaximum(0.002930128);
    //SysError_PI_R7[0][1]->SetEntries(6529020);

    SysError_PI_R7[1][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[1].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[1][1]->SetBinContent(1,0.01132362);
    SysError_PI_R7[1][1]->SetBinContent(2,0.002666572);
    SysError_PI_R7[1][1]->SetBinContent(3,0.002177753);
    SysError_PI_R7[1][1]->SetBinContent(4,0.00231316);
    SysError_PI_R7[1][1]->SetBinContent(5,0.001157844);
    SysError_PI_R7[1][1]->SetBinContent(6,0.001251522);
    SysError_PI_R7[1][1]->SetBinContent(7,0.002456017);
    SysError_PI_R7[1][1]->SetBinContent(8,0.002168075);
    SysError_PI_R7[1][1]->SetBinContent(9,0.00352321);
    SysError_PI_R7[1][1]->SetBinContent(10,0.003774109);
    SysError_PI_R7[1][1]->SetBinContent(11,0.00187148);
    SysError_PI_R7[1][1]->SetBinContent(12,0.004299859);
    SysError_PI_R7[1][1]->SetBinContent(13,0.01073709);
    SysError_PI_R7[1][1]->SetBinContent(14,0.005869945);
    SysError_PI_R7[1][1]->SetBinContent(15,0.002695556);
    SysError_PI_R7[1][1]->SetBinContent(16,0.001369065);
    SysError_PI_R7[1][1]->SetBinContent(17,0.001711354);
    SysError_PI_R7[1][1]->SetBinContent(18,0.01337886);
    SysError_PI_R7[1][1]->SetBinContent(19,0.03703955);
    SysError_PI_R7[1][1]->SetBinContent(20,0.001545321);
    SysError_PI_R7[1][1]->SetBinContent(21,80.89757);
    //SysError_PI_R7[1][1]->SetBinError(21,8.994307);
    //SysError_PI_R7[1][1]->SetMinimum(0);
    //SysError_PI_R7[1][1]->SetMaximum(0.04074351);
    //SysError_PI_R7[1][1]->SetEntries(484520);

    SysError_PI_R7[2][1]=new TH1D(Form( "SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[1].Data()),Form("SysError_PI_R7_%s_%s", Sample[2].Data(), FGD[1].Data()) ,20, 0, 5000);
    SysError_PI_R7[2][1]->SetBinContent(1,0.0005973433);
    SysError_PI_R7[2][1]->SetBinContent(2,0.001377389);
    SysError_PI_R7[2][1]->SetBinContent(3,0.0009222685);
    SysError_PI_R7[2][1]->SetBinContent(4,0.00170994);
    SysError_PI_R7[2][1]->SetBinContent(5,0.0009581321);
    SysError_PI_R7[2][1]->SetBinContent(6,0.001584768);
    SysError_PI_R7[2][1]->SetBinContent(7,0.001887365);
    SysError_PI_R7[2][1]->SetBinContent(8,0.001320305);
    SysError_PI_R7[2][1]->SetBinContent(9,0.002615262);
    SysError_PI_R7[2][1]->SetBinContent(10,0.001684523);
    SysError_PI_R7[2][1]->SetBinContent(11,0.002526578);
    SysError_PI_R7[2][1]->SetBinContent(12,0.00125522);
    SysError_PI_R7[2][1]->SetBinContent(13,0.001121117);
    SysError_PI_R7[2][1]->SetBinContent(14,0.001222239);
    SysError_PI_R7[2][1]->SetBinContent(15,0.003038295);
    SysError_PI_R7[2][1]->SetBinContent(16,0.01059055);
    SysError_PI_R7[2][1]->SetBinContent(17,0.009006513);
    SysError_PI_R7[2][1]->SetBinContent(18,0.001508539);
    SysError_PI_R7[2][1]->SetBinContent(19,0.002485404);
    SysError_PI_R7[2][1]->SetBinContent(20,0.004058099);
    SysError_PI_R7[2][1]->SetBinContent(21,197.1252);
    //SysError_PI_R7[2][1]->SetBinError(21,14.04013);
    //SysError_PI_R7[2][1]->SetMinimum(0);
    //SysError_PI_R7[2][1]->SetMaximum(0.0116496);
    //SysError_PI_R7[2][1]->SetEntries(933020);
   
    
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
            
            maximum=0;
            if(i==1)
            {
                maximum = SysError_NEW_R7[2][1]->GetMaximum();
                SysError_DEFAULT_R7[is][i]->SetMaximum(maximum);
                
            }
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
