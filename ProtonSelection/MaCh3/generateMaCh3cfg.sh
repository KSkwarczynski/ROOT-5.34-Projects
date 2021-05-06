#!/bin/bash
# $SAMPLE="default"
rm ND280_Fit*

FitType=ASIMOVFIT
#FitType=REALDATAFIT
POLYFILE=proton_TH2Poly_binning.root
MCMC_STEPS=2000000
XSEC_COV_FILE="xsec_covariance_2020a_v14.root"
ND_DETCOV_FILE="ProtonBANFFcovMatrix.root"

for ik in {0..2}
do

filename=ND280_Fit_$ik.cfg
echo "////////////////////////////" >> $filename
echo "// General settings" >> $filename
echo "////////////////////////////" >> $filename
echo "  " >> $filename

echo "OUTPUTNAME = \"output/ND280_Fit_$ik.root\"" >> $filename
echo "POLYFILE = \"inputs/$POLYFILE\"" >> $filename
echo "ND_LIKELIHOOD = \"Barlow-Beeston\"" >> $filename
echo "  " >> $filename

echo "////////////////////////////" >> $filename
echo "// MCMC settings" >> $filename
echo "////////////////////////////" >> $filename
echo "NSTEPS = $MCMC_STEPS" >> $filename
echo "STEPSCALEXSEC   = 0.01" >> $filename
echo "STEPSCALENDDET  = 0.04" >> $filename
echo "  " >> $filename

echo "////////////////////////////" >> $filename
echo "// ND RUN SETTINGS" >> $filename
echo "////////////////////////////" >> $filename
echo "NDRUNS = \"P6T 2a 2w 3 4a 4w 5 6 7 8a 8w 9\"" >> $filename
echo "ND_SEL = [\"kTrackerNumuCCMultiPiProton\", \"kTrackerAntiNumuCCMultiPi\", \"kTrackerNumuInAntiNuModeCCMultiPi\", \"kTrackerNumuCCMultiPiProtonFGD2\", "kTrackerAntiNumuCCMultiPiFGD2\", \"kTrackerNumuInAntiNuModeCCMultiPiFGD2\"]" >> $filename
echo "ND_SAM = [\"FGD1 nu CC0pi 0 protons\", \"FGD1 nu CC0pi N protons\", \"FGD1 nu CC1pi\", "FGD1 nu CCOth\", \"FGD1 anu CC0pi\", \"FGD1 anu CC1pi\", \"FGD1 anu CCOth\", \"FGD1 anu nu CC0pi\", \"FGD1 anu nu CC1pi\", \"FGD1 anu nu CCOth\",  \"FGD2 nu CC0pi 0 protons\", \"FGD2 nu CC0pi N protons\", \"FGD2 nu CC1pi\", \"FGD2 nu CCOth\",\"FGD2 anu CC0pi\", \"FGD2 anu CC1pi\", \"FGD2 anu CCOth\", \"FGD2 anu nu CC0pi\", \"FGD2 anu nu CC1pi\", \"FGD2 anu nu CCOth\"]" >> $filename
echo "  " >> $filename


echo "////////////////////////////" >> $filename
echo "/// Fit type" >> $filename
echo "////////////////////////////" >> $filename
echo "$FitType = true" >> $filename
echo "  " >> $filename

echo "////////////////////////////" >> $filename
echo "// Covariances" >> $filename
echo "////////////////////////////" >> $filename
echo "XSECCOVFILE = \"inputs/$XSEC_COV_FILE\"" >> $filename
echo "NDDETCOVFILE = \"inputs/$ND_DETCOV_FILE\"" >> $filename
echo "XSECPARAMFLAT = [1,2,6,7,8,9,10,11,12,13,14]" >> $filename
echo "XSECPARAMFIX = [20]" >> $filename
echo "  " >> $filename


echo "////////////////////////////" >> $filename
echo "// Beta options " >> $filename
echo "////////////////////////////" >> $filename
echo "USEBETA=false"  >> $filename
echo "FLIPBETA=false"  >> $filename
echo "APPLYBETANUE=false"  >> $filename
echo "APPLYBETADIAG=false"  >> $filename




done
