(Sorry about not LaTeXing this...)

Correct as of February 2018, written by Clarence Wret (clarence.wret@gmail.com)

# Background:

The ND280 code for MaCh3 closely follows the BANFF implementation.

The general executables are found in src/ND280_***.cxx

Generally speaking, the implementation follows:
<ol>

<li> Load up an instance of the ND280 sample probability distribution functions (e.g. samplePDFND2018)
The instance might be a GPU version (wrapped in an #ifdef CUDA) or a CPU version (the #else in the #ifdef CUDA)
The GPU support is handled by the CUDAPATH environment variable (see $MACH3/src/Makefile and look for #ifdef CUDAPATH) which simply defines the CUDA variable for the preprocessor in the src/Makefile
Conventionally, we export the CUDAPATH variable in the '$MACH3/setup.sh' setup script and rebuild the install by 'make clean && make'

<li> The ND280 sample instance contains everything you need for the ND280 fit. Binning, paths to data and MC (controlled by the MACH3_DATA and MACH3_MC environment variables if they can be found, or a hardcoded path), reweighting, and so on.

<li> We then need to create the systematics we want to consider for the sample. Looking at src/ND280_MCMC_2019.cxx we make various covarianceXYZ instances. These are simply classes containing information about the systematics, their central values and priors, parameter names, and so on.

<li> The ND280 sample also needs to be linked to a set of systematics, found in covariance/covariance***. The linking between ND280 and the systematics happens in the samplePDFND2018::setXsecCov, setFluxCov and setSimpleDetCov (some defined in the header).

<li> Once we've linked the sample to the systematics, we need to see how the sample should respond to a change in systematics.
In MaCh3 we run this on an event-by-event basis (so we look at how each event responds to a parameter variation), and for the ND280 implementation we run all the systematics on an event by event basis (not bin by bin as in at SK). So for ND280 the for loop is over the events, and the systematics are evaluated for every individual event.

The ND280 event response is relatively complex: the input MC contains "splines" (essentially a function for the weight applied for each parameter to an event as a function of the parameter variation, e.g. w(x)) attached to every single event (which is why the input MC is so large). The splines are linked to the sample and events in samplePDFND2018::fillReweigtingBins (see multiple SetBranchAddress) and the call to samplePDFND2018::SetSplines (which sets up the splines for each event)

The cross-section splines are applied on a parameter by parameter, event by event basis. This means we miss out on some internal correlations in the sline evaluation: e.g. the MARES spline is made by varying the MARES parameter whilst keeping the others fixed. MARES correlates heavily with CA5, so the response of an event to a variation of MARES is actually also a function of CA5. This _IS NOT_ accounted for in our variations since we use 1D splines. Fixing this would require a multi-dimensional spline.

In the main reweight loop we loop over the events and calculate the weight for each event for the current parameter variations. The parameter variations are determined by some external driver application, e.g. src/ND280_MCMC_2019.cxx or src/ND280_LLHscan_2016.cxx. 
 
<li> We then define some likelihood for the sample and the systematics (e.g. samplePDFND2018::getLikelihood and covarianceXsec2015::getLikelihood). For every reweight and feed this back and forth to the Markov Chain and we explore the parameter space

<li> Make all sorts of fun plots!
</ol>


# Description of making inputs:
<ol>


<li> Cross-section covariance matrix (aka NIWG covariance matrix)
  Use MaCh3 xsecMatrixMaker

<li> ND280 detector covariance matrix
  Currently, ask BANFF!

<li> flux covariance matrix
  Get it straight from the flux group and point to it in your config file
  If you're using the fluxweight from psyche you need to point to it in your psycheSteering.parameters.dat file
  Also make sure that when input MC and Sand were processed that the psycheSteering.parameters.dat file was pointing to a correct flux file

<li> Input Data, MC and Sand
  Probably the hardest thing to do, but fret not, here are some steps
<ol>
<li> First thing's first, ask the NuMu group for flat-trees that have been processed in highland. The NuMu group are now (2016ish) responsible for providing fitters with flattrees, which reduces the workload on you
An example of finding such flattrees on iRODS can be found by doing "ils asg2018oa/NuMu/MC/run2a_FlatTree_highland2", which will give you the MC for run2a     Download all of these. If you don't know how to get iRODS it can automagically be installed by MaCh3/SetMeUp.sh. The full t2k.org documentation is at https://t2k.org/asg/oagroup/gadatastorage/index_html

<li> You need OAGenWeightsApps https://github.com/t2k-software/OAGenWeightsApps/ this requier many dependencies

psych/highland: https://git.t2k.org/nd280/highland2Software/highland2SoftwarePilot
NEUT: https://github.com/neut-devel/neut/
NIWG: https://github.com/t2k-software/NIWGReWeight/
T2KReWeight: https://github.com/t2k-software/T2KReWeight

Each respository has quite good REAMDE which should help you with instalation, this is mine setup to source everything.

    source <path>/ROOT_5.34.34.00/Linux-ScientificCERNSLC_6.9-gcc_4.9-x86_64/bin/thisroot.sh
    cd <path>/highland_2.67/nd280SoftwarePilot
    ./configure.sh
    . nd280SoftwarePilot.profile

    #Highland
    source <path>/highland_2.67/psycheMaster_3.69/Linux-ScientificCERNSLC_6.10-gcc_4.9-x86_64/setup.sh
    source <path>/highland_2.67/highland2Master_2.67/Linux-ScientificCERNSLC_6.10-gcc_4.9-x86_64/setup.sh
    source <path>/highland_2.67/oaAnalysisReader_2.23/Linux-ScientificCERNSLC_6.10-gcc_4.9-x86_64/setup.sh
    export ND280PROD=prod6T
    #NEUT
    source <path>/NEUT/OA2021/build/Linux/setup.sh
    #NIWGRW
    source <path>/OA_T2K/NIWGReWeight/OA2021/build/Linux/setup.sh
    #T2K RW
    source <path>/OA_T2K/T2KReWeight/OA2021/build/Linux/setup.sh
    #OAWeighGenApps
    source <path>/OA_T2K/OAGenWeightsApps/OA2021/build/Linux/setup.sh

Hopefully this builds everything "just fine", but it's likely that some of the libraries won't be linked properly, or that there's some version mismatched
For an example, in Feb 2018 I used the official NEUT 5.3.3 version for the analysis, which did not include axial form factors enumerators, required in src/T2KNeutUtils.cxx. So I had had to comment out those parts of T2KNeutUtils.cxx (since they aren't used in our analysis this year).
If you're having build issues, check the libraries and includes you're linking against and make sure the build configure was correct by looking at make/Make.config

<li> Making the input Data and MC
You should now be able to run executables like ND280GenWeights in OAGenWeightsApps.
do <code>./ND280GenWeights</code>  to get what options you should provide to the executable
The input files (-i option) are the files provided by the NuMu group, which psyche reads and processes to produce detector weights and flux weights.
As stressed before, be careful to use an appropriate psycheSteering.parameters.dat file in your $PSYCHESTEERINGROOT install. If you don't know what this means, ask Mark Scott, Asher Kaboth, Alexandr Izmaylov, Anselmo Cervera, Simon Bienstock or Clarence Wret.

</ol>
A valid run of the executable on MC file NuMu_file.root with output file NuMu_file_output.root would be 

<code>ND280GenWeights -i NuMu_file.root -o NuMu_file_output.root -c config.toml </code> 

You can then use hadd to collect the files and cut them into runs (e.g. Run2a, 2w, 4a)

You should now have output files that have been processed through psyche and OAWeighGenApps to give you nominal detector weight corrections, flux corrections and splines from NEUT and NIWGReWeight!

This are then the inputs for the ND280 code in MaCh3, see MaCh3/samplePDF/samplePDFND2019.cpp, searching for SampleGroup. 
      
</ol>

# Running Executables and Making post-fit plots:


MaCh3 ND Executables and Plotting Scripts

How to run the ND side of MaCh3. Focus is on which executables/scripts to use, rather than how they works.


Submit job to cluster:
```
./clusters/submit_ND280.sh ExecutableName config.cfg JobName NumberOfJobs NumberOfSteps
```
You may have to add your own clusters into the script, and adapt load up + s/step for the Walltime


**Running a fit:**
```
ND280_MCMC_2019 ./config.cfg
```
Initially loads up samplePDF, systematics, data. Reweighta MC to prior values. Then start a Markov Chain

Output contains TTree 'posteriors'. In this is every parameter value for every step, and each contribution to the LLH for every step


**Plotting Postfit Parameter Values and Distributions:**
```
cd nd280_utils
./DrawComp FitOutput.root
```
This draws 1D distribution for each flux and cross-section parameter, and a plot of them all at the end. Saved in a root and pdf file

To make correlations:
```
./DrawComp FitOutput.root drawcorr
```
And to compare Fits:
```
./DrawComp FitOutput1.root FitOutput2.root (FitOutput3.root)
```
For nicer more aesthetic plots, run over the root file output of DrawComp:
```
GetAsimovPlots_HPDOnly.C("DrawCompOutput.root")
```
Uses Higher Posterior Density for each parameter. This has some hardcoding in for eg scaling Eb, plotting a higher z axis for CC Misc. DrawComp and GetAsimovPlots_HPDOnly could be combined. 
	 
Can compare two DrawComp outputs:
```
GetAsimovPlots_HPDOnly2Fits.C("DrawCompOutput1.root","DrawCompOutput2.root")
```
This could also be combined into one nice exec with GetAsimovPlots_HPD and DrawComp


**Chain Diagnostics:**
```
cd nd280_utils`	
./DiagMCMC FitOutput.root
```
This makes parameter traces, LLH trace, batched means, and auto correlations. Very useful for testing chain convergence and step size tuning. Output is a root file with plots in directories. To put every plot in a pdf:
```
loopit.C("DiagMCMCOutput.root")
```
Loopit is a generic script which just takes in a root file, loops through everything in the file (recursively over directories), and plots any TH1, TH2, or canvas.


**Posterior Predictions:**
```
ND280_PosteriorPredictive_2016 config.cfg
```
In the config you specify the OutputChain.root you want to run over. The executable draws 20000 random steps, reweights the MC to each step. Then for each sample for each bin you have 20000 bin contents. Fit a guassian and take the central value and uncertainty as the bin contents and error for that bin in the prediction. Also throws and compares to make p values. NOTE: Will is in process of updating this for OA 2020 to use TH2Polys

Again can save plots to pdf with:
```
loopit.C("PosteriorPredictionOutput.root")
```

**LLH Scans:**
```
ND280_LLHscan_2019 config.cfg
```
Loads up stuff in similar way to ND280_MCMC_2019. Then scrolls through parameters one by one, setting them each to 150 different values between +/-1sigma, while everything else is nominal. Reweights MC to each value and calculates the LLH. Output is a root file with plot of LLH vs parameter value for every parameter, and every LLH contribution

Can loop over file to get pdf of output with:
```
loopit.C("LLHScanOutput.root")
```
Or to compare two different LLH Scans:
```
loopdir.C("LLHScanOutput1.root","LLHScanOutput2.root")
```
Watch out for hard coding of eg not plotting NDDet parameters if it's not what you intend.

Or, to compare a MaCh3 LLH Scan with a BANFF LLH Scan:
```
BANFF_MaCh3_LLH_comp BANFFLLHScan.root MaCh3LLHScan.root
```
This is hard coded for the current NIWG Model. Also need to be careful of parameter order. BANFF have FSI at the beginning as they don't use them in their PCA. We have FSI at the end so there's some shuffling.


**Sigma Variations:**
```
ND280_SigmaVar_2019 config.cfg
```

Loads up stuff in similar way to MCMC and LLHscan. Then sets each parameter one by one to +/- 1,3 sigma and reweights MC with everything else nominal. Integrals for each sample are printed to the log file. Usually we send that log file to the BANFF and they make a nice latex comparison table.

Can plot ratios of +/-1,3 sigma to nominal for each parameter with:
```
cd nd280_utils
compareSigVar.C("OutputSigmaVar.root")
```

Currently assumes you ran with `plotbymode=true` in the config (which only plots 2p2h as well as all in sigma var). So there's some hard coding to loop over the 2p2h only histograms. Does this using a counter of histograms in each directory as can't just use 2p2h suffix as an identifier as some parameters end like that. Makes a root file and pdf of all the ratio plots.


**TH2Poly Making:**

In the config you can set POLYFILE. In that file should be 18 TH2Polys named appropriately for each sample. Look in `inputs` for an example. These are then used as templates for the fit binning. Maybe you want to make such a file but with TH2D binning for some validations. Firstly make some histograms with:
```
cd nd280_utils
`makeTH2D.C()
```

Inside makeTH2D the binning is hard coded for each axis for each sample. Just set them to be whatever you want and it makes a root file with 18 TH2Ds. These can then be converted to TH2Polys by:
```
convertTH2DToPoly.C()
```

You'll have to set the input and output files by hand in the script, but it just spits out 18 TH2Polys with the same rectangular binning as for the input TH2D file. 

But now let's say you've run with uniform binning but a TH2Poly object, and you want to convert back to TH2D for eg comparisons with BANFF. Just do:
```
convertPolytoTH2D.C("TH2PolyFile.root")
```

As long as each poly has uniform rectangular binning, it will convert it to a TH2D with the same bin contents.

NOTE: When these were written they were never intended to be committed so aren't as generic as they could/should be. 


**Xsec Cov:**

Firstly make a nice xml file to reflect the NIWGs latest model. Examples are in `nd280_utils/xsecMatrixMaker/`. Then make it into the root file with:
```
cd nd280_utils/xsecMatrixMaker
makeXSecMatrix.py xseccov.xml xseccov.root
```
Then send round to your friendly fellow analysers. 


**NDDet Cov:**

Normally the BANFF make this and we just convert it into a format compatible with MaCh3. For 2020, Will made them inside the BANFF and made it be able to TH2Poly Binning. Hopefully that's what was used to make yours as then you can convert with:
```
cd nd280_utils/xsecMatrixMaker
ConvertPolyND280Bin banffNDCov.root
```
     
The TH2Poly templates should be saved within the BANFFs NDDetCov file, so there's no hard coding of binning anymore.


**Flux Cov:**

Usually just get from beam group and lob in `inputs`. Make sure psyche is using the correct tuning version in `psyche/psycheND280_utils/v*r*/parameters/psycheND280Utils.parameters.dat`

