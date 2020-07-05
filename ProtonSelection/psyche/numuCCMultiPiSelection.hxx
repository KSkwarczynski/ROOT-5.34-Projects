#ifndef numuCCMultiPiSelection_h
#define numuCCMultiPiSelection_h

#include "numuCCSelection.hxx"
#include "Parameters.hxx"
#include "CutUtils.hxx"

class numuCCMultiPiSelection: public SelectionBase{

public:
  numuCCMultiPiSelection(bool forceBreak=true);
  virtual ~numuCCMultiPiSelection(){}

  void DefineSteps();
  void DefineDetectorFV();
  inline ToyBoxB* MakeToyBox();
  bool FillEventSummary(AnaEventC& event, Int_t allCutsPassed[]);
  SampleId_h GetSampleId(){return SampleId::kFGD1NuMuCC0Pi;}
  bool IsRelevantRecObjectForSystematic(const AnaEventC& event, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematic(const AnaEventC& event, AnaTrueObjectC* trueObj, SystId_h systId, Int_t branch) const;

  bool IsRelevantRecObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaRecObjectC* recObj, SystId_h systId, Int_t branch) const;
  bool IsRelevantTrueObjectForSystematicInToy(const AnaEventC& event, const ToyBoxB& box, AnaTrueObjectC* trueTrack, SystId_h systId, Int_t branch) const;

  bool IsRelevantSystematic(const AnaEventC& event, const ToyBoxB& box, SystId_h systId, Int_t branch) const;
  void InitializeEvent(AnaEventC& event);
  bool CheckRedoSelection(const AnaEventC& event, const ToyBoxB& PreviousToyBox,  Int_t& redoFromStep);

  Int_t GetRelevantRecObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;
  Int_t GetRelevantTrueObjectGroupsForSystematic(SystId_h systId, Int_t* IDs, Int_t branch) const;

  void SetDetectorFV(SubDetId_h det, Int_t ibranch=-1){
    SelectionBase::SetDetectorFV(det, ibranch);
    // Set to the selection that is used
    _numuCCSelection.SetDetectorFV(det, ibranch);
  }

  // Set externally whether to use ECal pi-zero veto
  void SetUseECalPiZeroInfo(bool use){
    _useECalPiZeroInfo = use;
  }

  // Get whether to use ECal pi-zero veto
  bool GetUseECalPiZeroInfo() const{
    return _useECalPiZeroInfo;
  }


protected:
  numuCCSelection _numuCCSelection;

  Int_t _MuonPIDCutIndex;
  Int_t _FindPionsStepIndex;  
  bool  _useECalPiZeroInfo;
};

class ToyBoxCCMultiPi: public ToyBoxTracker{

public:
  ToyBoxCCMultiPi(){}

  virtual ~ToyBoxCCMultiPi(){}

  void Reset(){
    pionBox.Reset();
  }

  multipart::MultiParticleBox pionBox;

  virtual const multipart::MultiParticleBox* GetMultiParticleBox() const{
    return &pionBox;
  }

};

inline ToyBoxB* numuCCMultiPiSelection::MakeToyBox(){return new ToyBoxCCMultiPi();}

namespace numuCCMultiPi{

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box);
};


class NoPionCut: public cutUtils::numuCCTrkMultiPi::NoPionCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new NoPionCut();}
};

class OnePionCut: public cutUtils::numuCCTrkMultiPi::OnePionCutBase{  
public:

  OnePionCut(bool posPionMode): cutUtils::numuCCTrkMultiPi::OnePionCutBase(posPionMode){}
  virtual ~OnePionCut(){}

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new OnePionCut(_posPionMode);}
};

//WARNING
class nProtonCut: public cutUtils::numuCCTrkMultiPi::nProtonCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new nProtonCut();}
};

//WARNING
class ZeroProtonCut: public cutUtils::numuCCTrkMultiPi::ZeroProtonCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new ZeroProtonCut();}
};

class OthersCut: public cutUtils::numuCCTrkMultiPi::OthersCutBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }
  StepBase* MakeClone(){return new OthersCut();}
};

class EcalPi0VetoCut: public cutUtils::numuCCTrkMultiPi::ECalPi0VetoCutBase{  
public:
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new EcalPi0VetoCut();}
};


class FillSummaryAction_numuCCMultiPi: public StepBase{
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FillSummaryAction_numuCCMultiPi();}
};

class FindPionsAction: public StepBase{
public:
  using StepBase::Apply;
  FindPionsAction(){
    pionSelParams.useTPCPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseTPCPions");
    pionSelParams.useME                       = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseME");
    pionSelParams.useFGDPions                 = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseFGDPions");
    pionSelParams.useOldSecondaryPID          = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.OldSecondaryPID");
    pionSelParams.useECalPiZeroInfo           = (bool)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.UseECalPiZeroInfo");

    pionSelParams.ECalMostUpstreamLayerHitCut = (Int_t)ND::params().GetParameterI("psycheSelections.numuCCMultiPi.MostUpstreamLayerHitCut");
    // Default
    pionSelParams.ECalEMEnergyCut = 30.;
    pionSelParams.ECalPIDMipEmCut = 0.;
  } 
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FindPionsAction();}

protected:
  mutable multipart::PionSelectionParams pionSelParams;
};

class FindProtonsAction: public StepBase{
public:
  using StepBase::Apply;
  FindProtonsAction(){
    protonSelParams.tpcPIDCut  = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.TPCPIDCut");
    protonSelParams.fgd1PIDCut = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.FGD1PIDCut");
    protonSelParams.fgd2PIDCut = (Float_t)ND::params().GetParameterD("psycheSelections.numuCCMultiPi.Protons.FGD2PIDCut");
  } 
  bool Apply(AnaEventC& event, ToyBoxB& box) const;  
  StepBase* MakeClone(){return new FindProtonsAction();}

protected:
  mutable multipart::ProtonSelectionParams protonSelParams;
};


class SetVertexToBoxAction: public StepBase, cutUtils::numuCCTrkMultiPi::MultiParticleBoxGetter{  
public:
  using StepBase::Apply;
  bool Apply(AnaEventC& event, ToyBoxB& box) const;

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new SetVertexToBoxAction();}

};

class FillFgdIsoPionsKinVertexAction: public cutUtils::numuCCTrkMultiPi::FillFgdIsoPionsKinVertexActionBase{  
public:

  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }

  StepBase* MakeClone(){return new FillFgdIsoPionsKinVertexAction();}
};

class FillFgdIsoProtonsKinVertexAction: public cutUtils::numuCCTrkMultiPi::FillFgdIsoProtonsKinVertexActionBase{  
public:
  const multipart::MultiParticleBox& GetPionBox(const ToyBoxB& box) const{
    return numuCCMultiPi::GetPionBox(box);  
  }    
  StepBase* MakeClone(){return new FillFgdIsoProtonsKinVertexAction();}
};




#endif
