// MergingHooks.h is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

#ifndef Pythia8_DireMergingHooks_H
#define Pythia8_DireMergingHooks_H

#define DIRE_MERGINGHOOKS_VERSION "2.004"

#include "Pythia8/Basics.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/Event.h"
#include "Pythia8/Info.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PartonSystems.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/Analysis.h"

#include "Dire/DireBasics.h"

namespace Pythia8 {

class PartonLevel;

//==========================================================================

// Declaration of hard process class
// This class holds information on the desired hard 2->2 process
// for the merging.
// This class is a container class for History class use.

class DireHardProcess : public HardProcess {

public:

  // Constructor with core process input
  void initOnProcess( string process, ParticleData* particleData);

  // Function to translate the process string (in MG/ME notation)
  void translateProcessString( string process);

  // Function to check whether the sets of candidates Pos1, Pos2, together
  // with the proposed candidate iPos give an allowed hard process state
#if (PYTHIA_VERSION_INTEGER >= 8242)
  bool allowCandidates(int iPos, vector<pair<int,int> > Pos1,
    vector<pair<int,int> > Pos2, const Event& event);
#else
  bool allowCandidates(int iPos, vector<int> Pos1, vector<int> Pos2,
    const Event& event);
#endif
  // Function to identify the hard subprocess in the current event
  void storeCandidates( const Event& event, string process);
  void storeCandidates( const Event& event, string process, ParticleData*) {
    return storeCandidates(event, process);
  }
  // Function to check if the particle event[iPos] matches any of
  // the stored outgoing particles of the hard subprocess
  bool matchesAnyOutgoing(int iPos, const Event& event);
  // Function to check if instead of the particle event[iCandidate], another
  // particle could serve as part of the hard process. Assumes that iCandidate
  // is already stored as part of the hard process.
  bool findOtherCandidates(int iPos, const Event& event, bool doReplace);

  // Function to exchange a stored hard process candidate with another choice.
  bool exchangeCandidates( vector<int> candidates1, vector<int> candidates2,
    unordered_map<int,int> further1, unordered_map<int,int> further2);

  bool swapCandidates( vector<int> candidates1,
    vector<int> candidates2, vector< pair<int,int> > further1,
    vector< pair<int,int> > further2);

  void initPtrs(ParticleData* pdIn) { particleDataPtr = pdIn; }
  ParticleData* particleDataPtr;

};

//==========================================================================

// DireMergingHooks is base class for user input to the merging procedure.

class DireMergingHooks : public MergingHooks {

public:

  DireMergingHooks() : MergingHooks(),
    jetAlgorithm(1, 0.4, 0.0, 100., 2, 2, NULL, true) {
    direInfoPtr   = 0;
    evtUtils = 0;
    isInit        = false;
    isStored      = false;
    njInc = 0;
    naInc = 0;
    nzInc = 0;
    nwInc = 0;
    nhInc = 0;
  }

  // Check if particle at position iPos is part of the hard sub-system
  bool isInHardScattering( int iPos, const Event& event, int iSys = 0);

  // Function to return the number of clustering steps for the current event
  virtual int getNumberOfClusteringSteps(const Event& event,
    bool resetNjetMax = false);

  //----------------------------------------------------------------------//
  // Functions used as default merging scales
  //----------------------------------------------------------------------//

  // Function to check if the input particle is a light jet, i.e. should be
  // checked against the merging scale defintion.
  bool checkAgainstCut( const Particle& particle);
  // Function to return the value of the merging scale function in the
  // current event.
  double tmsNow( const Event& event );
  // Find the minimal Lund pT between coloured partons in the event
  //double scalems( const Event& event, bool withColour);
  double scalems( const Event& event);
  double scalept( const Event& event);

  // Dirty trick to use some base class members to transfer integer-type
  // information.
  void setVeto(int in){ ktTypeSave = in; return; }

  //----------------------------------------------------------------------//
  // Functions to steer shower evolution (public to allow for PS plugin)
  //----------------------------------------------------------------------//

  // Flag to indicate trial shower usage.
  void doIgnoreEmissions( bool doIgnoreIn ) {
    doIgnoreEmissionsSave = doIgnoreIn;
  }
  // Function to allow not counting a trial emission.
  bool canVetoEmission() { return !doIgnoreEmissionsSave; }
  // Function to check if emission should be rejected.
  bool doVetoEmission( const Event& );

  // Function to calculate the hard process matrix element - override Pythia,
  // which incorrectly returns 1.0.
//double hardProcessME( const Event& ) { return 0.; }
  double hardProcessME( const Event& ) { return 1.; }

  void init();
  void initDirePtrs(DireInfo* direInfoPtrIn) { direInfoPtr = direInfoPtrIn;}
  bool isFirstEmt(const Event& event);

protected:

  //----------------------------------------------------------------------//
  //----------------------------------------------------------------------//
  // Functions to steer merging code
  //----------------------------------------------------------------------//

  // Flag to indicate if events should be vetoed.
  void doIgnoreStep( bool doIgnoreIn ) { doIgnoreStepSave = doIgnoreIn; }
  // Function to allow event veto.
  bool canVetoStep() { return !doIgnoreStepSave; }

public:

  // Function to check event veto.
  virtual bool doVetoStep( const Event& process, const Event& event,
    bool doResonance = false );

  // Set starting scales
  virtual bool setShowerStartingScales( bool isTrial, bool doMergeFirstEmm,
    double& pTscaleIn, const Event& event,
    double& pTmaxFSRIn, bool& limitPTmaxFSRin,
    double& pTmaxISRIn, bool& limitPTmaxISRin,
    double& pTmaxMPIIn, bool& limitPTmaxMPIin );

  bool doMOPSSave;
  bool doMOPS() { return doMOPSSave; }
  bool doMEMSave;
  bool doMEM() { return doMEMSave; }

  vector<double> stoppingScales() { return stoppingScalesSave; }

  void setHelpersPtr(DireHelpers* in ){
    helpersPtr = in;
    evtUtils   = &helpersPtr->evtUtils;
    kinRels    = &helpersPtr->kinRels;
  }

  bool doMerge () { return doUserMergingSave || doPTLundMergingSave 
    || doUNLOPSTreeSave || doUNLOPSLoopSave|| doUNLOPSSubtSave
    || doUNLOPSSubtNLOSave || doUMEPSTreeSave || doUMEPSSubtSave;
  }

  void storeHardCandidates (const Event& event) {
    hardProc.storeCandidates(event,getProcessString(), particleDataPtr);
  }

  int nHardFinal () {
    return (hardProcess->hardOutgoing1.size()
          + hardProcess->hardOutgoing2.size());
  }

protected:

  //----------------------------------------------------------------------//
  // Functions for internal merging scale definions
  //----------------------------------------------------------------------//

  // Function to compute "pythia pT separation" from Particle input
  double tevol(const Event& event, int rad, int emt, int rec,
    int ShowerType);

  bool isInit, isStored;
  void store();
  void restore();

  double forced_tcut;
  double forced_t_cutoff() { return forced_tcut; }

  //----------------------------------------------------------------------//
  // Member variables to store and restore to.
  //----------------------------------------------------------------------//

  int    nReclusterStore, nRequestedStore, nJetMaxStore, nJetMaxNLOStore, 
         nMinMPIStore, nJetMaxLocalStore, nJetMaxNLOLocalStore, nHardNowStore,
         nJetNowStore, ktTypeStore;
  double pT0ISRStore, pTcutStore, muMIStore, tmsValueStore, tmsValueNowStore,
         DparameterStore, muFStore, muRStore, muFinMEStore, muRinMEStore,
         pTstore, tmsHardNowStore, tmsNowStore;
  bool   doOrderHistoriesStore, doIgnoreEmissionsStore, doIgnoreStepStore,
         hasJetMaxLocalStore;
  Event inputEventStore;
  vector< pair<int,int> > resonancesStore;

  DireHardProcess hardProc;
  DireHardProcess hardProcessStore;

  vector<double> stoppingScalesSave;

  DireInfo* direInfoPtr;
  DireHelpers* helpersPtr;
  DireEventUtils* evtUtils;
  DireKinRelations* kinRels;

  // Jet algorithm
  SlowJet jetAlgorithm;
  int njInc, naInc;
  int nzInc, nwInc;
  int nhInc;

};

//==========================================================================

} // end namespace Pythia8

#endif
