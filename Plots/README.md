# OAGenWeightsApps

## Quick build

### Dependencies

Check in `scripts/try_build_dependencies.sh` to see an example of how to pull down and set up the packages that we will depend on.

### Package build

Configure like:

```
mkdir build; cd build;
cmake ../ -DUSE_ND280=<ON,OFF> -DUSE_SK=<ON,OFF>
```

Most dependencies are resolved through T2KReWeight by using `t2kreweight-config`.
Hopefully the error messages should be helpful if things cannot be found.

## Apps

# ND280

**ND280GenWeights** - this is the main app resposnible for generating ND280 splines
```
ND280GenWeights -i <flat-tree> -o <outputfile_name> -c <config_file>
```
*config_file* can be found in `<path>/app/Configs`

**genWeightFromPsyche** - this app will reweight psyche toy from *RunSyst_New*, output from this app
is used for generating ND280 covariance matrix. 
```
genWeightFromPsyche -i <RunSyst_New_file.root> -o <outputfile.root< -c <config.toml>
```
# SK
This will be filled by SK expert
