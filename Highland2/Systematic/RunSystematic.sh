#!/bin/bash
#PBS -m bea
DIRECTORY=/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/
export CVSROOT=:ext:anoncvs@repo.nd280.org:/home/trt2kmgr/ND280Repository
export CVS_RSH=ssh
unset CVS_SERVER
export CMTPATH=/mnt/home/kskwarczynski/T2K/work/v11r31/
cd /mnt/home/kskwarczynski/T2K/work/v11r31/highland2/numuCCMultiPiAnalysis/v2r14/cmt/
source setup.sh

cd $DIRECTORY/systematicError/

#DEFAULT
root -l -q -b 'HybridsSystematic.C("/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/systematicError/FGD1/", "Run4MCprod6T-FGD1-nu_DEFAULT")'
root -l -q -b 'HybridsSystematic.C("/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/systematicError/FGD2/", "Run4MCprod6T-FGD2-nu_DEFAULT")'

#NEW
root -l -q -b 'HybridsSystematic.C("/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/systematicError/FGD1/", "Run4MCprod6T-FGD1-nu_NEW")'
root -l -q -b 'HybridsSystematic.C("/mnt/home/share/t2k/kskwarczynski/hybrid_analysis/hybridRun4/systematicError/FGD2/", "Run4MCprod6T-FGD2-nu_NEW")'
