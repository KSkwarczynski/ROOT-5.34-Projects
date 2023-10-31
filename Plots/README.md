# OAGenWeightsApps

## Quick build

### Dependencies

Check in `scripts/try_build_dependencies.sh` to see an example of how to pull down and set up the packages that we will depend on.

### Package build

Configure like:

```
mkdir build; cd build;
cmake ../ [-DUSE_OPENMP=<ON,OFF>]
```
And for installation:
```
make [-j<Ncores>]
make install
```

last but not least
```
source Linux/bin/setup.OAGen.sh
```

Dependencies are resolved in `cmake/psycheSetup.cmake` and via `T2KReWeightConfig.cmake`. 
If `T2KReWeightConfig.cmake` cannot be found, then the configure step will fail.
The way that this file is found is via the `T2KReWeight_ROOT` environment variable, so the
first point of debugging a failed configure is to make sure that `$T2KReWeight_ROOT/cmake/T2KReWeight/T2KReWeightConfig.cmake` exists.
Hopefully error messages should be helpful if things other configure issues are encountered.

`-DUSE_OPENMP` option - by default multithreading is turned off. Only a few exe uses it for example **MakeND280Cov**. If you wonder where your code can gain anything from multithreading look for **pragma omp**.

### Features

There are two features available right now, ND280 and SK.

ND280 part of the code will compile only if T2KReWeight is built with OAanalysisReader support. If you are unsure check the output of `t2kreweight-config --features` for example:
```
t2kreweight-config --features
NEUT NIWG OAAnalysisReader Prob3plusplus SK
```
ND280 code relies on NRootracker reader and psyche to do selection, it is mandatory to use psyche.

SK on the other doesn't require any other libraries, as of right now it will compile by default.

## Apps

### ND280

**ND280GenWeights** - this is the main app resposnible for generating ND280 cross section splines
```
ND280GenWeights -i <flat-tree> -o <outputfile_name> -c <config_file>
```
*config_file* can be found in `<path>/app/Configs`. *config_file* determines which dial will be loaded by the app,
as well as knots selection, through config you can also define if you want to use mirroring for splines or not.

*Fake Data* generation of fake data is done with the same exe, you only need to pass corresponding config file. Then in sample sum you will have additional variables like `FDSWeight[nFakeDatas]`, this holds weight coming from declared fake data, you can check to which fake data give weight corresponds by looking at `FDSNames` variable.

**MakeND280SystSplines** - will generate the ND280 detector systematic splines
```
MakeND280SystSplines -i <inputFileName.root> -o <outputFileName.root> -c <configFile.toml> [-h]
```
*Input file* should be the output of **ND280GenWeights**

*configFile* specifies the psyche parameters that correspond to what spline parameters. Example can be found in `<path>/app/Configs/ND_Syst_Merge_Def.toml`.

**GetPOTweight** - Will add POT weight to spline. To calcualte POT weight we need full data and MC spline. Furthermore, this allow to easily create sand splines.
```
GetPOTweight <DataSpline.root>  <MCspline.root> <OutputSpline.root> [-h]
```

**genWeightFromPsyche** - this app will reweight psyche toy from *RunSyst_New*, output from this app
is used for generating ND280 covariance matrix. 
```
genWeightFromPsyche -i <RunSyst_New_file.root> -o <outputfile.root< -c <config.toml>
```

**MakeND280Cov** - this app creates an ND covariance matrix, you need psyche throws, same as for *genWeightFromPsyche*, NIWG toys are not necessary to use but for final production need them. Binning is loaded via toml config.
```
MakeND280Cov  <config.toml>  <ToysList.txt> <NIWGList.txt> <OutputName>
```
or
```
MakeND280Cov  <config.toml>  <ToysList.txt> <OutputName>
```

**plotND280Cov**  - this app will plot the errors, nominal weights, and distribution of toy throws for each bin from an ND bin covariance matrix made by MakeND280Cov. Can provide multiple files and it will plot them all of the same plots.
```
plotND280Cov [-g] [-s] [-l <label string>] [-o <name of plot file>] <file1.root> [<file2.root> <file3.root> ...]
```
-g draw a grid on plots

-s split the plots by sample

*label string* a string specifying the labels to show for each file, should be in the format "label1;label2;..."

*name of plot file* is the name of the file to save plots to

*fileN.root* are the covariance matrices to plot, can give any number of files

**StudyLinearity.cxx** - Loop over all splines and finds which are linear. It is advised to reduce number of knots to two for linear splines.
```
./StudyLinearity Spline1 Spline2 Spline3
```

**compareSplineTypes** - will check all of the splines in a file and compare different interpolation methods, e.g. linear interpolation, TSpline3, monotonic spline etc. It will make plots of particularly poorly behaved splines by looking at their deviation from the truth splines (if provided) or from a TSpline3 if not.
```
CompareSplineTypes -i SplineFile [-t TruthFile -n NExamplesToSave -p plotPrefix -h]
```
*SplineFile* should be the output of *ND280GenWeights* or *MakeND280SystSplines*

*TruthFile* is an optional baseline truth file containing "true" splines, this can be made by using **ND280GenWeights** and/or **MakeND280SystSplines** to make splines with very high number of knots (few hundred - a thousand) so that the effects of interpolation can be ignored and they essentially represent the output of the underlying weight engine. If provided, these "truth" splines will also be drawn on plots for comparisson with their interpolated, small number of knots, counterparts.

*NExamplesToSave* the maximum number of example plots to save, default is 50.

*plotPrefix* string to prepend to plot pdf files so that you can put them in a folder, e.g. make a folder called `splinePlots` and provide `-p splinePlots/` when running


Furthermore in scripts folder you can find useful ND280 scipts
**RunSplineComparison.sh** which will plot spline for each event, for particular dial, moreover you can turn option to except TGraph plot TSpline3, by parsing `true` instead of `false`.

**SplineValidation.cxx** - will generate validation plot from splines, how to use 
```
.x SplineValidation.cxx("path to spline","dial_name")
```

### SK
**SKGenWeights .cxx** - The main app used for generating SK splines. All the dials and their properties are loaded via config files
```
./SKGenWeights -s <SK_mtuple> -o <Output File> -c <toml.config>
```

**add_info_to_mtuples.cxx** - Add usefull NIWG realted variables to mtuples which are neccesary for the fitter but not provided by T2K-SK.
```
./add_deltapmiss_sk -s <SK_mtuple>
```


## Active Maintainers
* [Kamil Skwarczynski](mailto:Kamil.Skwarczynski@rhul.ac.uk)<br>
  Royal Holloway, University of London, UK
