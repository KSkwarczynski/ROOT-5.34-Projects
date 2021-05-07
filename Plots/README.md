# Developers
Edward Atkin, Daniel Barrow, Casey Bojechko, Richard Calland, Alex Carter, Kirsty Duffy, Patrick Dunne, Evan Goodman, Leila Haegel, Thomas Holvey, Asher Kaboth, Xiaoyue Liu, William Parker, Dave Payne, Patrick de Perio, Elder Pinzon, Balint Radics, Kamil Skwarczynski, Artur Sztuc, Abraham Teklu, Kevin Wood, Clarence Wret, Tomoyo Yoshida 


# Git instructions
<ol>
<li> The default branch you get when checking out MaCh3 is "main". </li>
   <ol>
   <li> This branch is at the most recent point where the analysis had been validated for a public release </li>
   <li> Master is only ever changed by pull requests with approval from an administrator </li>
   </ol>
<li> Development work is done around the "develop" branch. 
   <ol>
   <li> This branch is where work on the analysis under current preparation is being done. </li>
   <li> To make changes branch off develop using a name of the format feature_XYZ, do some development, then make a pull request to merge your changes back into develop. </li>
   <li> Changes should be merged back into develop frequently, but also checked to make sure they don't break the code for others. </li>
   </ol>
<li> If you're preparing an analysis that you think doesn't fit well with the above model bring it up at a MaCh3 meeting and we can discuss </li>
</ol>

# MaCh3 Instructions

## Install
<ol>
<li> In a suitable directory run: git clone git@github.com:t2k-software/MaCh3.git </li>
  <ol>
  <li> in order to do this you'll need to be a member of the t2k-software github organisation and have your ssh key set up with github. </li>
  </ol>
<li> Make sure you have cmake and a root install in your path. </li>
<li> You will also need to have set up your ssh key on git.t2k.org and be able to see repositories in the nd280 group `git.t2k.org/nd280`. </li>
<li> **./setup_psyche.sh** </li>
  <ol>
  <li> This is not obligatory, you can use MaCh3 without psyche </li>
  </ol>
<li> Edit **setup.sh** if you are on a resource we don't typically use:
   `export CUDAPATH="/srv/localstage/akaboth/cuda-7.0"` <- if you have a CUDA installation, put the path to the CUDA libraries here, if not comment this line out
   Most of the common clusters like IC, RHUL, RAL and compute canada should automatically find the right CUDA path with no edits </li>
<li> **./setup_niwgreweight.sh** </li>
<li> **source setup.sh** </li>
<li> **make** </li>
</ol>
## Configuration File

All programs can use a .cfg file to pass information to the fitter, for example:
```
SKjoint_ND280_2012 example_config.cfg
```

To run a toy fit, add the following 3 lines to the config file:
```
  TOYFIT = true
  NTOY = <n> // the toy dataset number you want to fit
  TOYFILE = "/path/to/toyfile.root" // file containing all toy datasets
```

For information on what can be put in the config file, look at the source code of the manager class.

## GIT Instructions
Probably the most important thing is to always work on your own branch and use pull requests to propagate any changes you want to share. You shouuld never directly work on or edit the master branch.

To make your own branch, after following the installation instructions above you should do:
```
git branch MYBRANCHNAME
git checkout MYBRANCHNAME
```

If you haven't used git before you are strongly advised to read Chapters 1-3 of https://git-scm.com/book/en/v1/Getting-Started 

If you are comfortable with git but would like a quick reminder of some commonly used commands see below:
List all the git branches in the repository (the one you are on should have a * next to it).
```
git branch -a
```
See the list of files modified and those staged for commit on your branch
```
git status
```
Add a new file to version control or stage a modified file for commit
```
git add MYFILE
```
Commit all staged changes to the current branch
```
git commit -m "this message tells what I changed"
```
Commiting only changes the local repository, to propagate changes to the remote repository (called origin by default) you should do:
```
git push
```
If you have not pushed the branch you are on before you will be given a message asking you to choose an upstream repository, if you are using the default names this can be fixed with
```
git push -u origin MYBRANCHNAME
```
To merge your commits into the master branch, open your favourite browser and go to the page :
   https://github.com/pjdunne/MaCh3
   Select your branch from the dropdown branch list, click new pull request and follow the instructions (the base branch is the one you are asking to change, and the compare branch is the one the changes are coming from)
   A list of the commits to merge is made and you should leave time for the group can look at it and comment before approving the merge request.
   Note that if you push a new commit after having done a merge request that was not approved yet, the new commits will be automatically added to the merge request.

PS: some of those actions are synchronised with Slack and will appear in the `mach3_github` by magic so everybody can track the change easily !

# Inputs

It is usual to keep all the inputs required in one common place for all your analysis work and use symlinks in the **MaCh3 inputs directory**. Scripts for doing this can be found in doc/external_files.

The list of up to date inputs for each OA iteration can be found here: https://www.t2k.org/asg/oagroup/inputs

Most of the files needed can be obtained from nextCloud or iRods.


## Old List of Inputs for Reference

For ND280, at the moment we have two sets of splines: one for RHC Multi Pi and one for RHC Multi Track. Going forward we will be using RHC Multi Pi, but until this is fully validated use RHC Multi Track for SK development work.

The splines are here for RHC Multi Pi: http://neutsrv2.triumf.ca/neutshare/jmorrison/Final_Thesis_Inputs/RHCMultiPi_NoRun4w_v3r34_HEAD/
and here for RHC Multi Track:
http://neutsrv2.triumf.ca/neutshare/jmorrison/Final_Thesis_Inputs/RHCMultiTrack_NoRun4w_v3r34_HEAD/

Ask Will if either of those links don't work. Once you've got these, you may have to edit your psycheSteering.parameters.dat file to be set for RHC Multi Pi/Track. Look in doc/nd280 for some example 3b event rates to check everything's worked out the box.

## Even older!!!

the old inputs can be found in the music input folder on the repo:
https://repo.nd280.org/viewvc/T2K/GlobalAnalysisTools/GlobalFitters/numuMCMC/inputs/

and the renamed nue splines from here:
http://hep.ph.liv.ac.uk/~rcalland/MaCh3/splines/

for the SKMC 13a mtuples and splines, download from these links:

numu samples:
http://www-he.scphys.kyoto-u.ac.jp/~minamino/t2k/ana13epshep/numu/smallnt/

numu splines:
http://www.phy.duke.edu/~tmw23/numu_analysis/splines/20130623/without_old_pdd_cutoff/ <- OLD!
http://www.phy.duke.edu/~tmw23/numu_analysis/splines/201307018/ <- PLEASE USE THESE ONES

nue samples:
http://www.phy.duke.edu/~ah243/mtuple_13a_wohecut_2rpi0/
http://www.phy.duke.edu/~ah243/mtuple_13a_wohecut_2rpi0_fitqunpi0cut/

nue splines:
http://hep.ph.liv.ac.uk/~rcalland/MaCh3/splines/13a

note: the 13a nuesplines are renamed versions from:
http://www.phy.duke.edu/~ah243/mtuple_13a_wohecut_2rpi0_weights/run1-4/
http://www.phy.duke.edu/~ah243/mtuple_13a_wohecut_2rpi0_fitqunpi0cut_weights/run1-4/
They have been renamed for formatting purposes, no changes to the splines were made.

### 26th November 2013
Latest splines are found here. This should be the last update for the full run1-4 analysis:

nue:
http://www.phy.duke.edu/~ah243/mtuple_13a_wohecut_2rpi0_weights/run1-4full/

numu (KDI):
http://www.phy.duke.edu/~tmw23/numu_analysis/splines/20131016/


