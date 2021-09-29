#!/bin/bash
# $SAMPLE="default"
rm ND280_Fit*

FitType=ASIMOVFIT
#FitType=REALDATAFIT
POLYFILE="MultiPiPhotonProton_PolyBins_BANFFTH2Ds_v2.root"
MCMC_STEPS=2000000
XSEC_COV_FILE="xsec_covariance_2021a_v13_AlphaQ3.root"
ND_DETCOV_FILE="MultiPiPhotonProton_NDCovMatrix_convertedToMaCh3_v5.root"

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

echo "// Save the logger output in mcmc/mcmc.cpp" >> $filename
echo "SUMMARY = false" >> $filename
echo "// Save the nominal" >> $filename
echo "SAVENOM = false" >> $filename
echo "// Save mode by mode at ND280" >> $filename
echo "PLOT_BY_MODE = false" >> $filename


echo "////////////////////////////" >> $filename
echo "// MCMC settings" >> $filename
echo "////////////////////////////" >> $filename
echo "NSTEPS = $MCMC_STEPS" >> $filename
echo "STEPSCALEXSEC   = 0.01" >> $filename
echo "STEPSCALENDDET  = 0.06" >> $filename
echo "  " >> $filename

echo "////////////////////////////" >> $filename
echo "// ND RUN SETTINGS" >> $filename
echo "////////////////////////////" >> $filename
echo "NDRUNS = \"P6T 2a 2w 3 4a 4w 5 6 7 8a 8w 9\"" >> $filename

echo "USEND280_SAND=true" >> $filename
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
echo "// Which are flat?" >> $filename
echo "XSECPARAMFLAT = [20,21,22,23,25,26,27,28,42,55,56,57,74]" >> $filename
echo "// Which are fixed?" >> $filename
echo "XSECPARAMFIX = [36]" >> $filename
echo "// Which parameters are linear: Pauli Blocking dials need linear response" >> $filename
echo "ND_XSEC_LINEAR_SPLINE = [16,17,18,19]" >> $filename
echo "  " >> $filename


echo "////////////////////////////" >> $filename
echo "// Beta options " >> $filename
echo "////////////////////////////" >> $filename
echo "USEBETA=false"  >> $filename
echo "FLIPBETA=false"  >> $filename
echo "APPLYBETANUE=false"  >> $filename
echo "APPLYBETADIAG=false"  >> $filename




done
