// Merging.h is a part of the PYTHIA event generator.
// Merging.h is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

#ifndef Pythia8_DireMerging_H
#define Pythia8_DireMerging_H

#define DIRE_MERGING_VERSION "2.004"

#include "Pythia8/Basics.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/Event.h"
#include "Pythia8/Info.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PartonLevel.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/StandardModel.h"
#include "Pythia8/Merging.h"
#include "Pythia8/MergingHooks.h"
#include "Pythia8/LesHouches.h"

#include "Dire/History.h"
#include "Dire/MergingHooks.h"
#include "Dire/WeightContainer.h"

namespace Pythia8 {

class DireSpace;
class DireTimes;

//==========================================================================

// Merging is a wrapper class for the interface of matrix element merging and
// Pythia8.

class DireMerging : public Merging {

public:

  // Constructor.
  DireMerging() : totalProbSave(createvector<double>(0.)(0.)(0.)) {
    vector<double> tmp(createvector<double>(0.)(0.)(0.));
    signalProbSave.insert(make_pair("higgs",tmp));
    bkgrndProbSave.insert(make_pair("higgs",tmp));
    signalProbSave.insert(make_pair("higgs-subt",tmp));
    bkgrndProbSave.insert(make_pair("higgs-subt",tmp));
    signalProbSave.insert(make_pair("higgs-nosud",tmp));
    bkgrndProbSave.insert(make_pair("higgs-nosud",tmp));
    signalProbSave.insert(make_pair("qed",tmp));
    bkgrndProbSave.insert(make_pair("qed",tmp));
    signalProbSave.insert(make_pair("qcd",tmp));
    bkgrndProbSave.insert(make_pair("qcd",tmp));
    signalProbSave.insert(make_pair("bsm",tmp));
    bkgrndProbSave.insert(make_pair("bsm",tmp));
    settingsPtr = 0; infoPtr = 0; particleDataPtr = 0; rndmPtr = 0;
    beamAPtr = 0; beamBPtr = 0; trialPartonLevelPtr = 0;
    mergingHooksPtr = 0; myHistory = 0; myLHEF3Ptr = 0; hasOwnLHEF3 = false;
    fsr = 0; isr = 0; 
    direInfoPtr = 0;
    enforceCutOnLHE = doMOPS = applyTMSCut = doMerging
      //= doMcAtNloDelta
      = allowReject = doMECs = doMEM = doGenerateSubtractions
      = doGenerateMergingWeights = doExitAfterMerging
      = allowIncompleteReal = doWeakMerging = false;
    usePDF = true;
    usePDFmass = false;
    applyVeto = true;
    nQuarksMerge = 5;
    unitarizationFactorSave = 1.;
    evtUtils = 0;

    /*tomteInfo.history = 0;
    tomteInfo.pathIndex = 0.;
    tomteInfo.nSteps = 0;
    tomteInfo.nRequested = 0;
    tomteInfo.containsRealKin = false;*/

  }

  void setWeightsPtr( DireWeightContainer* wgtsIn ) { psweights = wgtsIn; } 
  void setShowerPtrs( DireTimes* timesPtr, DireSpace* spacePtr) {
    fsr = timesPtr; isr = spacePtr; }

  void initPtrs( DireWeightContainer* wgtsIn, DireTimes* timesPtr,
    DireSpace* spacePtr, DireInfo* direInfoIn) {
    psweights = wgtsIn;
    fsr = timesPtr;
    isr = spacePtr;
    direInfoPtr = direInfoIn;
  }

  void setLHEF3Ptr(LHEF3FromPythia8* in) {
    if (myLHEF3Ptr) delete myLHEF3Ptr;
    myLHEF3Ptr = in;
    hasOwnLHEF3 = false;
  }

  DireTimes* fsr;
  DireSpace* isr;
  DireInfo* direInfoPtr;
  int ntries;

  // Destructor.
  ~DireMerging(){
    if (myLHEF3Ptr) myLHEF3Ptr->closeLHEF(true);
    if (hasOwnLHEF3 && myLHEF3Ptr)
      delete myLHEF3Ptr;
    if (myHistory) delete myHistory;
  }

  // Initialisation function for internal use inside Pythia source code
  virtual void init();
  void initOnEvent(const Event& process);
  void initSettings();
  void reset();

  // Function to print statistics.
  virtual void statistics();

  //----------------------------------------------------------------------//
  // Functions that implement matrix element merging.
  //----------------------------------------------------------------------//

  // Function to steer different merging prescriptions.
  virtual int mergeProcess( Event& process);

  // Return CKKW-L weight.
  void getSudakovs( double & wt )  const { wt = sudakovs;  return; }
  void getASratios( double & wt )  const { wt = asRatios;  return; }
  void getPDFratios( double & wt ) const { wt = pdfRatios; return; }

  void getSudakovExp( int order, double & wt )  const {
    wt = 0.;
    if (order >= 0 && order < int(sudakovsExp.size()))
      wt = sudakovsExp[order];
    return;
  }
  void getASratioExp( int order, double & wt )  const {
    wt = 0.;
    if (order >= 0 && order < int(asRatiosExp.size()))
      wt = asRatiosExp[order];
    return;
  }
  void getPDFratioExp( int order, double & wt ) const {
    wt = 0.;
    if (order >= 0 && order <= int(pdfRatiosExp.size()))
      wt = pdfRatiosExp[order];
    return;
  }

  void nRealSubtractions (int & nsub) {
    nsub = int(subtractions.size());
    return;
  }
  void getRealSubtraction (const int& iSub, const int& charSize,
    double& val, char * psppoint ) {
    val = subtractions[iSub].first;
    myLHEF3Ptr->setEventPtr(&subtractions[iSub].second);
    myLHEF3Ptr->setEvent();
    string helper = myLHEF3Ptr->getEventString();
    // Right-pad string with whitespace.
    helper.insert(helper.end(), charSize - helper.size(), ' ');
    std::copy(helper.begin(), helper.end(),psppoint);
    psppoint[helper.size()] = '\0';
    return;
  }

  void clearInfos() {
    stoppingScalesSave.clear();
    startingScalesSave.clear();
    mDipSave.clear();
    radSave.clear();
    emtSave.clear();
    recSave.clear();
  }
  void storeInfos();

  Event stripResonances  (const Event& inputEventIn);
  Event insertResonances (const Event& inputEventIn);

  int vetoEvent() {
    mergingHooksPtr->setWeightCKKWL(0.);
    mergingHooksPtr->setWeightFIRST(0.);
    if (mergingHooksPtr->includeWGTinXSEC()) infoPtr->updateWeight(0.);
    if (allowReject) return -1;
    else             return  1;
  }

  double unitarizationFactorSave;
  double unitarizationFactor() { return unitarizationFactorSave; }
  void unitarizationFactor( double in) {unitarizationFactorSave = in;}

  vector<double> getStoppingScales() { 
    return stoppingScalesSave;
  }
  vector<double> getStartingScales() { 
    return startingScalesSave;
  }
  void getStoppingInfo(double scales [100][100], double masses [100][100]);
  vector<double> stoppingScalesSave, startingScalesSave, mDipSave;
  vector<int>    radSave, emtSave, recSave;

  double generateSingleSudakov ( double pTbegAll, 
   double pTendAll, double m2dip, int idA, int type, double s = -1.,
   double x = -1.);
  //int genSud( Event& process);

  vector<double> getSignalProb(string key) { return signalProbSave[key]; }
  vector<double> getBkgrndProb(string key) { return bkgrndProbSave[key]; }
  vector<double> getTotalProb() { return totalProbSave; }
  vector<double> totalProbSave;
  map<string, vector<double> > signalProbSave, bkgrndProbSave;
  void clearClassifier() {
    for ( map<string, vector<double> >::iterator it = signalProbSave.begin();
      it != signalProbSave.end(); ++it) for (size_t i=0; i<it->second.size();
        ++i) it->second[i]=0.;
    for ( map<string, vector<double> >::iterator it = bkgrndProbSave.begin();
      it != bkgrndProbSave.end(); ++it) for (size_t i=0; i<it->second.size();
        ++i) it->second[i]=0.;
    for (size_t i=0; i<totalProbSave.size(); ++i) totalProbSave[i]=0.;
  }

  void setHelpersPtr(DireHelpers* in ){
    helpersPtr = in;
    evtUtils   = &helpersPtr->evtUtils;
    kinRels    = &helpersPtr->kinRels;
  }

  struct TomteState {
    double wt;
    string name;
    Event state;
    map<string,string> attributes;
    TomteState(double w, string n, Event s, map<string,string> a = map<string,string>()){
      wt = w;
      name = n;
      state = s;
      attributes = a;
    }
  };

  struct TomteInfo {
    DireHistory* history = 0;
    double pathIndex = 0.;
    vector<TomteState> states;
    int nSteps = 0;
    int nRequested = 0;
    bool containsRealKin = false;
    double sumExternalWeights = 0.;
    double sumExternalWeightsPassCut = 0.;
    void clear () {
      states.clear();
      nSteps = -1;
      nRequested = -1;
      containsRealKin = false;
    }
  };
  TomteInfo tomteInfo;

protected:

  //----------------------------------------------------------------------//
  // The members
  //----------------------------------------------------------------------//

  // Make Pythia class friend
  friend class Pythia;

  // Function to perform CKKW-L merging on the event.
  int mergeProcessCKKWL( Event& process);

  // Function to perform UMEPS merging on the event.
  int mergeProcessUMEPS( Event& process);

  // Function to perform UNLOPS merging on the event.
  int mergeProcessUNLOPS( Event& process);

  // Function to apply the merging scale cut on an input event.
  bool cutOnProcess( Event& process);

  // Function to perform CKKW-L merging on the event.
  int calculate( Event& process);

  vector<double> reweight(const Event& state);
  int makeToyCalculation(Event& process);

  bool doN3LO () { return doN3LOs; }
  bool doTOMTE () { return doTOMTEs; }
  bool doCheckBasic () { return doCheckBasics;}
  bool doCheckSudakov () { return doCheckSudakovs;}
  bool makeToy () { return makeToys; }

  int checkBiasCorrectionBasic(Event& process);
  int checkBiasCorrectionIncludingSudakov(Event& process);

  int cutForN3LO ( Event& process);
  int matchN3LO ( Event& process);
  int initForN3LO ( const Event& process);
  int createHistoryForN3LO ();
  int createMatchedEventsForN3LO ();
  int assembleOutputsForN3LO ();
  int getStartingConditionsForN3LO( Event& process );
  double pathIndexForN3LO(DireHistory* starting_leaf,
    map<double, DireHistory*> branches);

  DireHistory* myHistory;

  bool   generateHistories( const Event& process, bool orderedOnly = true);
  void   tagHistories();

  double getPathIndex( bool useAll = false);
  int    calculateWeights( double RNpath, bool useAll = false);
  int    getStartingConditions( double RNpath, Event& process );

  void   setSudakovs( double wt )  { sudakovs = wt;  return; }
  void   setASratios( double wt )  { asRatios = wt;  return; }
  void   setPDFratios( double wt ) { pdfRatios = wt; return; }

  void setSudakovExp( vector<double> wts ) {
    // Clear previous results.
    sudakovsExp.clear();
    // Store coefficients of Sudakov expansion.
    sudakovsExp.insert(sudakovsExp.end(), wts.begin(), wts.end());
    return;
  }
  void setASratioExp( vector<double> wts ) {
    // Clear previous results.
    asRatiosExp.clear();
    // Store coefficients of Sudakov expansion.
    asRatiosExp.insert(asRatiosExp.end(), wts.begin(), wts.end());
    return;
  }
  void setPDFratiosExp( vector<double> wts ) {
    // Clear previous results.
    pdfRatiosExp.clear();
    // Store coefficients of Sudakov expansion.
    pdfRatiosExp.insert(pdfRatiosExp.end(), wts.begin(), wts.end());
    return;
  }

  void clearSubtractions() { subtractions.clear(); }
  void appendSubtraction( double wt, const Event& event ) {
    subtractions.push_back( make_pair(wt, event) );
    return;
  }
  bool calculateSubtractions();

  double sudakovs, asRatios, pdfRatios;
  vector<double> sudakovsExp, asRatiosExp, pdfRatiosExp;
  vector<pair<double,Event> > subtractions;

  // Create and open file for LHEF 3.0 output.
  LHEF3FromPythia8* myLHEF3Ptr;
  bool hasOwnLHEF3;
  DireWeightContainer* psweights;

  bool enforceCutOnLHE, doMOPS, applyTMSCut, doMerging,
       // doMcAtNloDelta,
       usePDF, usePDFmass, allowReject, doMECs, doMEM, doN3LOs,
       doTOMTEs, doCheckBasics, doCheckSudakovs, makeToys,
       doGenerateSubtractions,
       doGenerateMergingWeights, doExitAfterMerging, allowIncompleteReal,
       applyVeto, doWeakMerging;
  int nQuarksMerge;

  bool doTOMTESudakovs, doTOMTEAlphasRatios, doTOMTEPDFRatios;
  int clusterMode, correctionMode;

  bool first;

  // Cross section conversion factor to undo stupid conversions done in
  // info.weight() calls.
  double CONVERTMB2PB;

  DireHelpers* helpersPtr;
  DireEventUtils* evtUtils;
  DireKinRelations* kinRels;

};

//==========================================================================

} // end namespace Pythia8

#endif
