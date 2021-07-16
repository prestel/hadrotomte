
#ifndef Pythia8_Dire_H
#define Pythia8_Dire_H

#define DIRE_VERSION "2.004"

// DIRE includes.
#include "Dire/SplittingLibrary.h"
#include "Dire/Merging.h"
#include "Dire/DireTimes.h"
#include "Dire/DireSpace.h"
#include "Dire/WeightContainer.h"
#include "Dire/Hooks.h"
#include "Dire/DireProcesses.h"

// Pythia includes.
#include "Pythia8/Pythia.h"
#include <iostream>
#include <sstream>

namespace Pythia8 {

//==========================================================================

class Dire {

  public:

  Dire() : weightsPtr(NULL), timesPtr(NULL), timesDecPtr(NULL), spacePtr(NULL),
    splittings(NULL), hooksPtr(NULL), userHooksPtr(NULL), mergingPtr(NULL),
    hardProcessPtr(NULL), mergingHooksPtr(NULL), hasOwnWeights(false),
    hasOwnTimes(false), hasOwnTimesDec(false), hasOwnSpace(false),
    hasOwnSplittings(false), hasOwnHooks(false), hasUserHooks(false),
    hasOwnHardProcess(false), hasOwnMerging(false), hasOwnMergingHooks(false),
    initNewSettings(false) {}

 ~Dire() {
    if (hasOwnWeights)      delete weightsPtr;
    if (hasOwnTimes)        delete timesPtr;
    if (hasOwnTimesDec)     delete timesDecPtr;
    if (hasOwnSpace)        delete spacePtr;
    if (hasOwnSplittings)   delete splittings;
    if (hasOwnHardProcess)  delete hardProcessPtr;
    if (hasOwnMerging)      delete mergingPtr;
    if (hasOwnMergingHooks) delete mergingHooksPtr;
    for (int i=0; i < int(sigmaPtr.size()); ++i) delete sigmaPtr[i];
  }

  bool init(Pythia& pythia, char const* settingsFile = "", int subrun = -999,
    UserHooks* userHooks = NULL, DireHooks* hooks = NULL);
  void initSettings(Pythia& pythia);
  void initTune(Pythia& pythia);
  void initShowersAndWeights(Pythia& pythia, UserHooks* userHooks,
    DireHooks* hooks);
  void setup(Pythia& pythia);

  DireWeightContainer* weightsPtr;
  DireTimes* timesPtr;
  DireTimes* timesDecPtr;
  DireSpace* spacePtr;
  DireSplittingLibrary* splittings;

  DireHooks* hooksPtr;
  UserHooks* userHooksPtr;

  DireInfo direInfo;
  DireHelpers helpers;

  // Pointer to Dire merging objects.
  DireMerging*      mergingPtr;
  DireHardProcess*  hardProcessPtr;
  DireMergingHooks* mergingHooksPtr;

  bool hasOwnWeights, hasOwnTimes, hasOwnTimesDec, hasOwnSpace,
       hasOwnSplittings, hasOwnHooks, hasUserHooks,
       hasOwnHardProcess, hasOwnMerging, hasOwnMergingHooks, initNewSettings;

  map<string,bool> reset_flags;
  void resetFlag(string name, bool value) {
    reset_flags.insert(make_pair(name,value));
  }
  void setFlags(Pythia& pythia) {
    for ( map<string,bool>::iterator it = reset_flags.begin();
      it != reset_flags.end(); ++it )
      pythia.settings.flag(it->first,it->second);
    reset_flags.clear();
  }

  // Dire-internal hard processes, to overwrite Pythia's hard processes.
  vector<SigmaProcess*> sigmaPtr;
  DireSigmaHelper sigmaHelper;

  Pythia* pythiaPtr;
  bool next() { return pythiaPtr->next(); }
  void stat() { pythiaPtr->stat(); }
  bool doMerge() { return mergingHooksPtr->doMerge(); }

};

//==========================================================================

} // end namespace Pythia8

#endif
