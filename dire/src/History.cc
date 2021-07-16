// History.cc is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

#include "Dire/History.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

#include "apfel/apfelxx.h"

namespace Pythia8 {

//==========================================================================

string stringFlavs(const Event& event) {
  ostringstream os;
  os << " (";
  for (int i=0; i < event.size(); ++i)
    if (event[i].status() == -21) os << " " << event[i].id();
  os << " ) -->> (";
  for (int i=0; i < event.size(); ++i) {
    if (event[i].status() ==  23) os << " " << event[i].id();
    if (event[i].status() ==  22) os << " " << event[i].id();
  }
  os << " ) ";
  return os.str();
}

void listFlavs(const Event& event, bool includeEndl = false) {
  cout << std::left << setw(30) << stringFlavs(event);
  if (includeEndl) cout << endl;
}

//--------------------------------------------------------------------------

// Helper class for setEffectiveScales.

class CouplFunction : public DireFunction {

public:

  CouplFunction(AlphaStrong* asIn) : as(asIn), aem(NULL) {};
  CouplFunction(AlphaEM* aemIn)    : as(NULL), aem(aemIn) {};
  CouplFunction(AlphaStrong* asIn, int asPowIn,
    AlphaEM* aemIn, int aemPowIn) : as(asIn), aem(aemIn), asPow(asPowIn),
    aemPow(aemPowIn) {};
  double f(double x) {
    double ret = (as==NULL)  ? 1. : pow(as->alphaS(x),asPow);
    ret       *= (aem==NULL) ? 1. : pow(aem->alphaEM(x),aemPow);
    return ret;
  } 
  double f(double x, double) {
    double ret = (as==NULL)  ? 1. : pow(as->alphaS(x),asPow);
    ret       *= (aem==NULL) ? 1. : pow(aem->alphaEM(x),aemPow);
    return ret;
  } 
  double f(double x, vector<double>) {
    double ret = (as==NULL)  ? 1. : pow(as->alphaS(x),asPow);
    ret       *= (aem==NULL) ? 1. : pow(aem->alphaEM(x),aemPow);
    return ret;
  } 
  AlphaStrong* as;
  AlphaEM*     aem;
  int asPow, aemPow;

};

//==========================================================================

// The Clustering class.

//--------------------------------------------------------------------------

// Declaration of Clustering class
// This class holds information about one radiator, recoiler,
// emitted system.
// This class is a container class for DireHistory class use.

// print for debug
string DireClustering::listString() const {
  ostringstream os;
  os << " rad " << radPos   << " (" << radSave->id() << ")" 
     << " emt1 " << emt1Pos << " (" << emt1Save->id() << ")"
     << " emt2 " << emt2Pos << " (-1)"
     << " rec " << recPos   << " (" << recSave->id() << ")"
     << " partner " << partner
     << " pT2 " << pow2(pTscale)
     << " name " << name();
  return os.str();
}

void DireClustering::list() const {
  cout << " rad " << radPos
       << " emt1 " << emt1Pos
       << " emt2 " << emt2Pos
       << " rec " << recPos
       << " partner " << partner
       << " pT2 " << pow2(pTscale)
       << " name " << name()  << endl;
}

//==========================================================================

// The DireHistory class.

// A DireHistory object represents an event in a given step in the CKKW-L
// clustering procedure. It defines a tree-like recursive structure,
// where the root node represents the state with n jets as given by
// the matrix element generator, and is characterized by the member
// variable mother being null. The leaves on the tree corresponds to a
// fully clustered paths where the original n-jets has been clustered
// down to the Born-level state. Also states which cannot be clustered
// down to the Born-level are possible - these will be called
// incomplete. The leaves are characterized by the vector of children
// being empty.

//--------------------------------------------------------------------------

// Number of trial emission to use for calculating the average number of
// emissions
const int DireHistory::NTRIAL = 20;

const double DireHistory::MCWINDOW = 0.1;
const double DireHistory::MBWINDOW = 0.1;
//const double DireHistory::PROBMAXFAC = 1e-5;
const double DireHistory::PROBMAXFAC = 0.0;

//--------------------------------------------------------------------------

// Declaration of DireHistory class
// The only constructor. Default arguments are used when creating
// the initial history node. The \a depth is the maximum number of
// clusterings requested. \a scalein is the scale at which the \a
// statein was clustered (should be set to the merging scale for the
// initial history node. \a beamAIn and beamBIn are needed to
// calcutate PDF ratios, \a particleDataIn to have access to the
// correct masses of particles. If \a isOrdered is true, the previous
// clusterings has been ordered. \a is the PDF ratio for this
// clustering (=1 for FSR clusterings). \a probin is the accumulated
// probabilities for the previous clusterings, and \ mothin is the
// previous history node (null for the initial node).

DireHistory::DireHistory( int depthIn,
         double scalein,
         Event statein,
         DireClustering c,
         MergingHooks* mergingHooksPtrIn,
         BeamParticle beamAIn,
         BeamParticle beamBIn,
         ParticleData* particleDataPtrIn,
         Info* infoPtrIn,
         PartonLevel* showersIn,
         DireTimes* fsrIn,
         DireSpace* isrIn,
         DireWeightContainer* psweightsIn,
         CoupSM* coupSMPtrIn,
         bool isOrdered = true,
         bool isAllowed = true,
         bool isHistoryForRealCorrectionIn = false,
         double clusterProbIn = 1.0,
         double clusterCouplIn = 1.0,
         double prodOfProbsIn = 1.0,
         double prodOfProbsFullIn = 1.0,
         DireHistory * mothin = 0)
    : state(statein),
      generation(depth),
      mother(mothin),
      selectedChild(-1),
      sumpath(0.0),
      sumGoodBranches(0.0),
      sumBadBranches(0.0),
      sumbranches(0.0),
      foundOrderedPath(false),
      foundAllowedPath(false),
      foundCompletePath(false),
      foundOrderedChildren(true),
      scale(scalein),
      scaleEffective(0.),
      couplEffective(-1.),
      isHistoryForRealCorrection(isHistoryForRealCorrectionIn),
      clusterProb(clusterProbIn),
      clusterCoupl(clusterCouplIn),
      prodOfProbs(prodOfProbsIn),
      prodOfProbsFull(prodOfProbsFullIn),
      clusterIn(c),
      iReclusteredOld(0),
      doInclude(true),
      hasMEweight(false),
      hasMEweightMultiplied(false),
      MECnum(1.0),
      MECden(1.0),
      MECcontrib(1.0),
      mergingHooksPtr(mergingHooksPtrIn),
      beamA(beamAIn),
      beamB(beamBIn),
      particleDataPtr(particleDataPtrIn),
      infoPtr(infoPtrIn),
      showers(showersIn),
      fsr(fsrIn),
      isr(isrIn),
      coupSMPtr(coupSMPtrIn),
      psweights(psweightsIn),
      doSingleLegSudakovs(
        mergingHooksPtr->settingsPtr->flag("Dire:doSingleLegSudakovs")),
      probMaxSave(-1.),
      depth(depthIn),
      minDepthSave(-1),
      nMaxOrd(0),
      erase(false),
      couplingPowCount(3,0) {

  //couplingPowCount.insert(make_pair("qed",0));
  //couplingPowCount.insert(make_pair("qcd",0));
  //couplingPowCount.insert(make_pair("heft",0));

  Q2minMEs = pow2(max(0.,mergingHooksPtr->settingsPtr->parm("Dire:QminMECs")));

  fsr->direInfoPtr->message(1)
    << scientific << setprecision(4)
    << __FILE__ << " " << __func__
    << " " << __LINE__ << " : New history node "
    << state.size() << " " << depth << " " << stringFlavs(state) << " at "
    << clusterIn.name() << " " 
    << (clusterIn.rad()  ? clusterIn.rad()->id()  : 0) << " " 
    << (clusterIn.emt1() ? clusterIn.emt1()->id() : 0) << " " 
    << (clusterIn.emt2() ? clusterIn.emt2()->id() : 0) << " " 
    << (clusterIn.rec()  ? clusterIn.rec()->id()  : 0) << " "
    //<< clusterProb << " "
    //<< clusterCoupl << " "
    //<< prodOfProbs << " "
    << "\t\t bare prob = " << clusterProb*pow2(clusterIn.pT())
    //<< " pT = " << pow2(clusterIn.pT())
    << " pT2 = " << pow2(clusterIn.pT())
    << endl;

  // Initialize.
  goodBranches.clear();
  badBranches.clear();
  branches.clear();
  paths.clear();

  // Remember how many steps in total were supposed to be taken.
  if (!mother) nStepsMax = depth;
  else         nStepsMax = mother->nStepsMax;

  // Initialise beam particles
  setupBeams();

  // Update probability with PDF ratio
  if (mother && mergingHooksPtr->includeRedundant()) {
    double pdfFac    = pdfForSudakov();
    clusterProb     *= pdfFac;
    prodOfProbs     *= pdfFac;
    prodOfProbsFull *= pdfFac;
  }

  // Remember reclustered radiator in lower multiplicity state
  if ( mother ) iReclusteredOld = mother->iReclusteredNew;

  // Check if more steps should be taken.
  int nFinalHeavy = 0, nFinalLight = 0;
  for ( int i = 0; i < int(state.size()); ++i )
    if ( state[i].status() > 0) {
      if ( state[i].idAbs() == 23
        || state[i].idAbs() == 24
        || state[i].idAbs() == 25)
        nFinalHeavy++;
      if ( state[i].colType() != 0
        || state[i].idAbs() == 22
        || (state[i].idAbs() > 10 && state[i].idAbs() < 20) )
        nFinalLight++;
    }
  if (nFinalHeavy == 1 && nFinalLight == 0) depth = 0;

  // Update generation index.
  generation = depth;

  // If this is not the fully clustered state, try to find possible
  // QCD clusterings.
  vector<DireClustering> clusterings;
  if ( depth > 0 ) clusterings = getAllClusterings(state);

  if (nFinalHeavy == 0 && nFinalLight == 2 && clusterings.empty()) depth = 0;

  if ( clusterings.empty() ) {
    hasMEweight = psweights->hasME(state, Q2minMEs);
    if (hasMEweight) MECnum = psweights->getME(state, Q2minMEs);
    else MECnum    = hardProcessME(state);
    /*fsr->direInfoPtr->message(1)
    << scientific << setprecision(4)
    << __FILE__ << " " << __func__
    << " " << __LINE__ << " Zero clusterings. Hard ME for "
    << stringFlavs(state) << " found? " << hasMEweight << " ME "
    << MECnum << endl;*/
  } else {
    // Check if fixed-order ME calculation for this state exists.
    hasMEweight = psweights->hasME(state, Q2minMEs);

    // Calculate ME
    if (hasMEweight) MECnum = psweights->getME(state, Q2minMEs);
    /*fsr->direInfoPtr->message(1)
    << scientific << setprecision(4)
    << __FILE__ << " " << __func__
    << " " << __LINE__ << " Some clusterings. Hard ME for "
    << stringFlavs(state) << " found? " << hasMEweight << " ME "
    << MECnum << endl;*/
  }

  /*fsr->direInfoPtr->message(1)
    << scientific << setprecision(4)
    << __FILE__ //<< " " << __func__
    << " " << __LINE__ << " : Node "
    //<< state.size() << " " << depth << " "
    << stringFlavs(state) << " via clustering: "
    << clusterIn.name()
    << " iRad="   << clusterIn.radPos
    << " iEmt1="  << clusterIn.emt1Pos
    //<< " iEmt2=" << clusterIn.emt2Pos
    << " iRec="   << clusterIn.recPos
    << " idRad="  << (clusterIn.rad()  ? clusterIn.rad()->id()  : 0)
    << " idEmt1=" << (clusterIn.emt1() ? clusterIn.emt1()->id() : 0)
    << " idEmt2=" << (clusterIn.emt2() ? clusterIn.emt2()->id() : 0)
    << " idRec="  << (clusterIn.rec()  ? clusterIn.rec()->id()  : 0)
    //<< " " << clusterProb << " "
    //<< clusterCoupl << " "
    //<< prodOfProbs << " "
    << " bare prob = " << clusterProb*pow2(clusterIn.pT())
    << " ME = " << MECnum
    //<< " pT = " << pow2(clusterIn.pT())
    << " pT = " << clusterIn.pT() << " " << pow2(clusterIn.pT())
    << endl;*/

  // If no clusterings were found, the recursion is done and we
  // register this node.
  if ( clusterings.empty() ) {

    // Multiply with hard process matrix element.
    prodOfProbs     *= MECnum;
    prodOfProbsFull *= MECnum;

    // Divide out all couplings in hard process matrix element.
    double MECnumCoupl = hardProcessCouplings(state);
    if (MECnumCoupl != 0.0) {
      prodOfProbs     /= MECnumCoupl;
      prodOfProbsFull /= MECnumCoupl;
    // If the coupling exactly vanishes, force weight to zero.
    } else {
      prodOfProbs     = 0.0;
      prodOfProbsFull = 0.0;
    }

    // Set the effective coupling of the hard process (to be used
    // to extract the effective scale).
    double QRen    = hardProcessScale(state);
    couplEffective = hardProcessCouplings(state, 1, QRen*QRen,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaEM_FSR(),
      false, false );

    if (std::isnan(prodOfProbs) ) {
      fsr->direInfoPtr->printMessages(1);
      prodOfProbs = prodOfProbsFull = 0.;
    }

    // Additional ordering requirement between shower starting scale and
    // scale of first emission.
    if ( mergingHooksPtr->orderHistories()
      || ( mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
        && mergingHooksPtr->settingsPtr->mode("Merging:nRequested") < 2) ) 
      isOrdered = isOrdered && (scale < hardStartScale(state) );

    if (registerPath( this, isOrdered, isAllowed, depth == 0 )) {
      updateMinDepth(depth, NULL);
      double nord = nOrdered (infoPtr->eCM(), NULL);
      if (nord>-1) updateNmaxOrdered(nord, NULL);
    } else {
#if (PYTHIA_VERSION_INTEGER >= 8242)
      state.free();
#else
      state.clear();
#endif
      erase = true;
    }
    return;
  }

  // Now we sort the possible clusterings so that we try the
  // smallest scale first.
  multimap<double, DireClustering *> sorted;
  for ( size_t i = 0; i < clusterings.size(); ++i ) {
    sorted.insert(make_pair(clusterings[i].pT(), &clusterings[i]));
  }

  bool foundChild = false;
  for ( multimap<double, DireClustering *>::iterator it = sorted.begin();
  it != sorted.end(); ++it ) {

    // Check if reclustering follows ordered sequence.
    bool ordered = isOrdered;
    if ( mergingHooksPtr->orderHistories() ) {
      // If this path is not ordered in pT and we already have found an
      // ordered path, then we don't need to continue along this path, unless
      // we have not yet found an allowed path.
      if ( !ordered || ( mother && (it->first < scale) ) ) {
        if ( depth >= minDepth(NULL) && onlyOrderedPaths()
          && onlyAllowedPaths() )
          continue;
        ordered = false;
      }
    }

    //if (!ordered || (mother && (it->first < scale))) ordered = false;
    if (!ordered || it->first < scale) ordered = false;

    Event newState(cluster(*it->second));
    if (newState.size()<3) continue;

    // Check if reclustered state should be disallowed.
    bool doCut = mergingHooksPtr->canCutOnRecState()
              || mergingHooksPtr->allowCutOnRecState();
    bool allowed = isAllowed;
    if (  doCut
      && mergingHooksPtr->doCutOnRecState(newState) ) {
      if ( onlyAllowedPaths()  ) continue;
      allowed = false;
    }

    // Get probability of splitting.
    pair <double,double> probs = getProb(*it->second);

    //if ( probs.second == 0. || hardProcessCouplings(newState) == 0.
    //  || ( psweights->hasME(newState, Q2minMEs)
    //    && psweights->getME(newState, Q2minMEs) < 1e-20)) {
    //  //fsr->direInfoPtr->eatCout();
    //  //it->second->list();  
    //  //cout << scientific << setprecision(15)
    //  //  << __FILE__ //<< " " << __func__
    //  //  << " " << __LINE__ << " : Prob " << probs.second << endl;
    //  //fsr->direInfoPtr->freeCout();
    //}

    fsr->direInfoPtr->message(1)
      << scientific << setprecision(10)
      << __FILE__ << " " << __func__
      << " " << __LINE__ << " : Clustering: " << it->second->listString()
      << "\t Prob=" << probs.second
      << " HardProccouplings=" << hardProcessCouplings(newState)
      << " hasME=" << psweights->hasME(newState, Q2minMEs)
      << " getME=" << psweights->getME(newState, Q2minMEs)
      << " product=" << abs(probs.second)*prodOfProbs
      << " max=" << PROBMAXFAC*probMax() << endl;

    // Skip clustering with vanishing probability.
    if ( probs.second == 0. || hardProcessCouplings(newState) == 0.
      || ( psweights->hasME(newState, Q2minMEs)
        && psweights->getME(newState, Q2minMEs) < 1e-20))
      continue;
    // Skip if this branch is already strongly suppressed.
    if (abs(probs.second)*prodOfProbs < PROBMAXFAC*probMax())
      continue;

    // Perform the clustering and recurse and construct the next
    // history node.
    children.push_back(new DireHistory(depth - 1,it->first, newState,
           *it->second, mergingHooksPtr, beamA, beamB, particleDataPtr,
           infoPtr, showers, fsr, isr, psweights, coupSMPtr, ordered, allowed,
           isHistoryForRealCorrection, probs.second, probs.first,
           abs(probs.second)*prodOfProbs, probs.second*prodOfProbsFull, this));
    if (children.back()->erase) {
      DireHistory* histToDetach = children.back();
      removeHistoryFromTree(histToDetach);
      delete histToDetach;
      histToDetach = 0;
      continue;
    }
    foundChild = true;
  }

  // Register as valid history if no children allowed.
  if (!foundChild) {

    // Multiply with hard process matrix element.
    prodOfProbs     *= MECnum;
    prodOfProbsFull *= MECnum;

    // Divide out all couplings in hard process matrix element.
    double MECnumCoupl = hardProcessCouplings(state);
    if (MECnumCoupl != 0.0) {
      prodOfProbs     /= MECnumCoupl;
      prodOfProbsFull /= MECnumCoupl;
    // If the coupling exactly vanishes, force weight to zero.
    } else {
      prodOfProbs     = 0.0;
      prodOfProbsFull = 0.0;
    }

    //registerPath( *this, isOrdered, isAllowed, true );
    //if (registerPath( *this, isOrdered, isAllowed, depth == 0 ))
    //  updateMinDepth(depth);
    if (registerPath( this, isOrdered, isAllowed, depth == 0 )) {
      updateMinDepth(depth, NULL);
      double nord = nOrdered (infoPtr->eCM(), NULL);
      if (nord>-1) updateNmaxOrdered(nord, NULL);
    } else {
#if (PYTHIA_VERSION_INTEGER >= 8242)
      state.free();
#else
      state.clear();
#endif
      erase = true;
    }
  }

  if (clearPaths()) erase = true;

  // Done.

}

//--------------------------------------------------------------------------

// Function to project all possible paths onto only the desired paths.

bool DireHistory::projectOntoDesiredHistories() {

  // In MOPS, discard states that yield clusterings below the shower cut-off.
  bool foundGoodMOPS=true;
  if ( mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")) {
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      if (!it->second->hasScalesAboveCutoff()) { foundGoodMOPS=false; break; }
    }
  }

  // Trim to desirable histories.
  bool foundGood = trimHistories();

  collectGenerations();

  // Loop through branches and set the set of "good" children in mother nodes.
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it )
    it->second->setGoodChildren();

  // Set good sisters.
  setGoodSisters();

  // Multiply couplings and ME corrections to probability.
  for (map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it)
    it->second->setCouplingOrderCount(it->second);

  /*// Loop through the good branches and set their correct probabilities, if
  // necessary.
  if (branches.size() > 0) {
    // Set probabilities from next-to-lowest multi --> highest multi. If
    // lowest multi == highest multi, no need to set probabilities.
    DireHistory* deepest = NULL;
    // Set probabilities from next-to-lowest multi --> highest multi. If
    // lowest multi == highest multi, no need to set probabilities.
    int generationMin = 1000000000;
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      if (it->second->generation < generationMin) {
        generationMin = it->second->generation;
        deepest = it->second;
      }
    }
    if (deepest->mother) deepest->mother->setProbabilitiesOld();
    //if (deepest->mother) deepest->mother->setEffectiveScalesOld();
  }*/

  setProbabilities();
  setEffectiveScales();
  //printGenerations();

  // Multiply couplings and ME corrections to probability.
  map<double, DireHistory*> newPaths;
  /*for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (!it->second->hasMEweightMultiplied)
      it->second->multiplyMEsToPath(it->second);
  }

  // Reset path indices after multiplying MEs.
  sumbranches=0.;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;*/

  return (mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
    ? foundGoodMOPS : foundGood);

}

//--------------------------------------------------------------------------

// In the initial history node, select one of the paths according to
// the probabilities. This function should be called for the initial
// history node.
// IN  trialShower*    : Previously initialised trialShower object,
//                       to perform trial showering and as
//                       repository of pointers to initialise alphaS
//     PartonSystems* : PartonSystems object needed to initialise
//                      shower objects
// OUT double         : (Sukadov) , (alpha_S ratios) , (PDF ratios)

double DireHistory::weightMOPS(PartonLevel* trial, AlphaStrong * /*as*/,
  AlphaEM * /*aem*/, double RN) {

  // Read alpha_S in ME calculation and maximal scale (eCM)
  //double asME     = infoPtr->alphaS();
  //double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Select a path of clusterings
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Keep only unordered paths, since all ordered paths have been corrected 
  // with matrix element corrections.
  if (foundOrderedPath) { return 0.;}

  // Calculate no-emission probability with trial shower.
  bool nZero = false;
  vector<double> ret(createvector<double>(1.)(1.)(1.));
  vector<double> noemwt = selected->weightEmissionsVec(trial,1,-1,-1,maxScale);
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= noemwt[i];
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;
  double sudakov = noemwt.front();

  // Calculate PDF ratios.
  double pdfwt = 1.;
  if (nZero) pdfwt = selected->weightPDFs( maxScale, selected->clusterIn.pT());
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= pdfwt;
  nZero = false;
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;

  // Calculate coupling ratios.
  vector<double> couplwt(createvector<double>(1.)(1.)(1.));
  if (nZero) couplwt = selected->weightCouplingsDenominator();
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= couplwt[i];
  nZero = false;
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;

  double coupwt = couplEffective/couplwt.front();

/*  if (nZero) {
    vector<double> vars(createvector<double>(1.)(0.25)(4.));
    double QRen  = selected->hardProcessScale(selected->state);
    double coupl = selected->hardProcessCouplings(selected->state, 1,
      QRen*QRen, as, aem);
    for (size_t i=0; i < vars.size(); ++i) {
      double ratio = selected->hardProcessCouplings(selected->state, 1,
        vars[i]*QRen*QRen, as, aem) / coupl;
      ret[i] *= ratio;
    }
  }*/

  // MPI no-emission probability
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = 1.;

  if (mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI")) mpiwt
    = selected->weightEmissions( trial, -1, 0, njetsMaxMPI, maxScale );

  // Done
  return (sudakov*coupwt*pdfwt*mpiwt);

  /*// Set hard process renormalisation scale to default Pythia value.
  bool resetScales = mergingHooksPtr->resetHardQRen();

  // For pure QCD dijet events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>jj") == 0) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow2(runningCoupling);
  } else if (mergingHooksPtr->doWeakClustering()
    && isQCD2to2(selected->state)) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow2(runningCoupling);
  }

  // For W clustering, correct the \alpha_em.
  if (mergingHooksPtr->doWeakClustering() && isEW2to1(selected->state)) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*aemFSR).alphaEM(newQ2Ren) / aemME;
    aemWeight *= runningCoupling;
  }

  // For prompt photon events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>aj") == 0) {
    // Reset to a running coupling. In prompt photon always ISR.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling =
      (*asISR).alphaS( newQ2Ren + pow(mergingHooksPtr->pT0ISR(),2) ) / asME;
    asWeight *= runningCoupling;
  }

  // For DIS, set the hard process scale to Q2.
  if ( resetScales
    && ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
      || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0)) {
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double pT20     = pow(mergingHooksPtr->pT0ISR(),2);
    if ( isMassless2to2(selected->state) ) {
      int nIncP(0), nOutP(0);
      for ( int i=0; i < selected->state.size(); ++i ) {
        if ( selected->state[i].isFinal()
          && selected->state[i].colType() != 0)
          nOutP++;
        if ( selected->state[i].status() == -21
          && selected->state[i].colType() != 0)
          nIncP++;
        }
      if (nIncP == 2 && nOutP == 2)
        asWeight *= pow2( (*asISR).alphaS(newQ2Ren+pT20) / asME );
      if (nIncP == 1 && nOutP == 2)
        asWeight *= (*asISR).alphaS(newQ2Ren+pT20) / asME
                  * (*aemFSR).alphaEM(newQ2Ren) / aemME;
    }
  }*/

//  // Done
//  return (sudakov*asWeight*aemWeight*pdfWeight*mpiwt);

}

//--------------------------------------------------------------------------

vector<double> DireHistory::weightMEM(PartonLevel* trial, AlphaStrong * as,
  AlphaEM * aem, double RN) {

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Select a path of clusterings
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Calculate no-emission probability with trial shower.
  bool nZero = false;
  vector<double> ret(createvector<double>(1.)(1.)(1.));
  vector<double> noemwt = selected->weightEmissionsVec(trial,1,-1,-1,maxScale);
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= noemwt[i];
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;

  // Calculate PDF ratios.
  double pdfwt = 1.;
  if (nZero) pdfwt = selected->weightPDFs( maxScale, selected->clusterIn.pT());
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= pdfwt;
  nZero = false;
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;

  // Calculate coupling ratios.
  vector<double> couplwt(createvector<double>(1.)(1.)(1.));
  if (nZero) couplwt = selected->weightCouplings();
  for (size_t i=0; i < ret.size(); ++i) ret[i] *= couplwt[i];
  nZero = false;
  for (size_t i=0; i < ret.size(); ++i) if (abs(ret[i]) > 1e-12) nZero = true;

  if (nZero) {
    vector<double> vars(createvector<double>(1.)(0.25)(4.));
    double QRen  = selected->hardProcessScale(selected->state);
    double coupl = selected->hardProcessCouplings(selected->state, 1,
      QRen*QRen, as, aem);
    for (size_t i=0; i < vars.size(); ++i) {
      double ratio = selected->hardProcessCouplings(selected->state, 1,
        vars[i]*QRen*QRen, as, aem) / coupl;
      ret[i] *= ratio;
    }
  }

  //// Include MPI no-emission probability.
  //double mpiwt = 1.;
  //if (mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI") && nZero) mpiwt = 
  //  selected->weightEmissions(trial,-1,0,mergingHooksPtr->nMinMPI(),maxScale);
  //for (size_t i=0; i < ret.size(); ++i) ret[i] *= mpiwt;

  return ret;

}

//--------------------------------------------------------------------------

// In the initial history node, select one of the paths according to
// the probabilities. This function should be called for the initial
// history node.
// IN  trialShower*    : Previously initialised trialShower object,
//                       to perform trial showering and as
//                       repository of pointers to initialise alphaS
//     PartonSystems* : PartonSystems object needed to initialise
//                      shower objects
// OUT double         : (Sukadov) , (alpha_S ratios) , (PDF ratios)

double DireHistory::weightTREE(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN) {

  if ( mergingHooksPtr->canCutOnRecState() && !foundAllowedPath ) {
    string message="Warning in DireHistory::weightTREE: No allowed history";
    message+=" found. Using disallowed history.";
    infoPtr->errorMsg(message);
  }

  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in DireHistory::weightTREE: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
  }
  if ( mergingHooksPtr->canCutOnRecState()
    && mergingHooksPtr->orderHistories()
    && !foundAllowedPath && !foundOrderedPath ) {
    string message="Warning in DireHistory::weightTREE: No allowed or ordered";
    message+=" history found.";
    infoPtr->errorMsg(message);
  }

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Select a path of clusterings
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Get weight.
  double sudakov   = 1.;
  double asWeight  = 1.;
  double aemWeight = 1.;
  double pdfWeight = 1.;

  // Do trial shower, calculation of alpha_S ratios, PDF ratios
  bool useEffScale = selected->useEffectiveScale();
  sudakov  = selected->weight( trial, asME, aemME, maxScale,
    selected->clusterIn.pT(), asFSR, asISR, aemFSR, aemISR, useEffScale,
    asWeight, aemWeight, pdfWeight );

  // MPI no-emission probability
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                   maxScale );

  if (mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI")) mpiwt
    = selected->weightEmissions( trial, -1, 0, njetsMaxMPI, maxScale );

  // Set hard process renormalisation scale to default Pythia value.
  bool resetScales = mergingHooksPtr->resetHardQRen();

  // For pure QCD dijet events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>jj") == 0) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow2(runningCoupling);
  } else if (/*mergingHooksPtr->doWeakClustering()
    &&*/ isQCD2to2(selected->state)) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow2(runningCoupling);
  }

  // For W clustering, correct the \alpha_em.
  if (/*mergingHooksPtr->doWeakClustering() &&*/ isEW2to1(selected->state)) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*aemFSR).alphaEM(newQ2Ren) / aemME;
    aemWeight *= runningCoupling;
  }

  // For prompt photon events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>aj") == 0) {
    // Reset to a running coupling. In prompt photon always ISR.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling =
      (*asISR).alphaS( newQ2Ren + pow(mergingHooksPtr->pT0ISR(),2) ) / asME;
    asWeight *= runningCoupling;
  }

  // For DIS, set the hard process scale to Q2.
  if ( resetScales
    && ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
      || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0)) {
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double pT20     = pow(mergingHooksPtr->pT0ISR(),2);
    if ( isMassless2to2(selected->state) ) {
      int nIncP(0), nOutP(0);
      for ( int i=0; i < selected->state.size(); ++i ) {
        if ( selected->state[i].isFinal()
          && selected->state[i].colType() != 0)
          nOutP++;
        if ( selected->state[i].status() == -21
          && selected->state[i].colType() != 0)
          nIncP++;
        }
      if (nIncP == 2 && nOutP == 2)
        asWeight *= pow2( (*asISR).alphaS(newQ2Ren+pT20) / asME );
      if (nIncP == 1 && nOutP == 2)
        asWeight *= (*asISR).alphaS(newQ2Ren+pT20) / asME
                  * (*aemFSR).alphaEM(newQ2Ren) / aemME;
    }
  }

  // Done
  return (sudakov*asWeight*aemWeight*pdfWeight*mpiwt);

}

//--------------------------------------------------------------------------

map<string,double> DireHistory::weightAllOrder(PartonLevel* trial,
  AlphaStrong * asFSR, AlphaStrong * asISR, AlphaEM * aemFSR,
  AlphaEM * aemISR, double RN) {

  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in DireHistory::weightTREE: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
  }

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Select a path of clusterings
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Get weight.
  double asWeight  = 1.;
  double aemWeight = 1.;
  double pdfWeight = 1.;

  // Do trial shower, calculation of alpha_S ratios, PDF ratios
  bool useEffScale = selected->useEffectiveScale();
  map<string,double> terms;
  selected->weight( trial, asME, aemME, maxScale,
    selected->clusterIn.pT(), asFSR, asISR, aemFSR, aemISR, useEffScale,
    asWeight, aemWeight, pdfWeight, terms );

  // Done
  return terms;

}

//--------------------------------------------------------------------------

// Function to return weight of virtual correction and subtractive events
// for NL3 merging

double DireHistory::weightLOOP(PartonLevel* trial, double RN ) {

  if ( mergingHooksPtr->canCutOnRecState() && !foundAllowedPath ) {
    string message="Warning in DireHistory::weightLOOP: No allowed history";
    message+=" found. Using disallowed history.";
    infoPtr->errorMsg(message);
  }

  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in DireHistory::weightLOOP: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
  }
  if ( mergingHooksPtr->canCutOnRecState()
    && mergingHooksPtr->orderHistories()
    && !foundAllowedPath && !foundOrderedPath ) {
    string message="Warning in DireHistory::weightLOOP: No allowed or ordered";
    message+=" history found.";
    infoPtr->errorMsg(message);
  }

  // Select a path of clusterings
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // So far, no reweighting
  double wt = 1.;

  //// Weight to to dynamic scale choice of hard process.
  //double wtHard = selected->weightHardState( selected->state,
  //  infoPtr->alphaS(),
  //  mergingHooksPtr->AlphaS_FSR(),
  //  infoPtr->alphaEM(),
  //  mergingHooksPtr->AlphaEM_FSR());

  // Only reweighting with MPI no-emission probability
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                   maxScale );
  wt = mpiwt;

  // Done
  return wt;
}

//--------------------------------------------------------------------------

double DireHistory::weight_UMEPS_TREE(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN) {
  // No difference to CKKW-L. Recycle CKKW-L function.
  return weightTREE( trial, asFSR, asISR, aemFSR, aemISR, RN);
}

//--------------------------------------------------------------------------

// Function to return weight of virtual correction events for NLO merging

double DireHistory::weight_UMEPS_SUBT(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN ) {

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();
  // Select a path of clusterings
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Get weight.
  double sudakov   = 1.;
  double asWeight  = 1.;
  double aemWeight = 1.;
  double pdfWeight = 1.;

  // Do trial shower, calculation of alpha_S ratios, PDF ratios
  bool useEffScale = selected->useEffectiveScale();
  sudakov   = selected->weight(trial, asME, aemME, maxScale,
    selected->clusterIn.pT(), asFSR, asISR, aemFSR, aemISR, useEffScale,
    asWeight, aemWeight, pdfWeight);

  // MPI no-emission probability.
  //int njetsMaxMPI = mergingHooksPtr->nMinMPI()+1;
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                   maxScale );

  // Set hard process renormalisation scale to default Pythia value.
  bool resetScales = mergingHooksPtr->resetHardQRen();
  // For pure QCD dijet events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>jj") == 0) {
    // Reset to a running coupling. Here we choose FSR for simplicity.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling = (*asFSR).alphaS(newQ2Ren) / asME;
    asWeight *= pow(runningCoupling,2);
  }

  // For prompt photon events, evaluate the coupling of the hard process at
  // a more reasonable pT, rather than evaluation \alpha_s at a fixed
  // arbitrary scale.
  if ( resetScales
    && mergingHooksPtr->getProcessString().compare("pp>aj") == 0) {
    // Reset to a running coupling. In prompt photon always ISR.
    double newQ2Ren = pow2( selected->hardRenScale(selected->state) );
    double runningCoupling =
      (*asISR).alphaS( newQ2Ren + pow(mergingHooksPtr->pT0ISR(),2) ) / asME;
    asWeight *= runningCoupling;
  }

  // Done
  return (sudakov*asWeight*aemWeight*pdfWeight*mpiwt);

}

//--------------------------------------------------------------------------

double DireHistory::weight_UNLOPS_TREE(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
  int depthIn) {

  if ( mergingHooksPtr->canCutOnRecState() && !foundAllowedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_TREE: No allowed history";
    message+=" found. Using disallowed history.";
    infoPtr->errorMsg(message);
  }

  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_TREE: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
    //fsr->direInfoPtr->printMessages(1);
    //printLeaves();
  }
  if ( mergingHooksPtr->canCutOnRecState()
    && mergingHooksPtr->orderHistories()
    && !foundAllowedPath && !foundOrderedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_TREE: No allowed or ordered";
    message+=" history found.";
    infoPtr->errorMsg(message);
  }

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath) ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();
  // Select a path of clusterings
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Get weight.
  double asWeight  = 1.;
  double aemWeight = 1.;
  double pdfWeight = 1.;

  // Do trial shower, calculation of alpha_S ratios, PDF ratios
  double wt = 1.;
  bool useEffScale = selected->useEffectiveScale();
  if (depthIn < 0) wt = selected->weight(trial, asME, aemME, maxScale,
    selected->clusterIn.pT(), asFSR, asISR, aemFSR, aemISR, useEffScale,
    asWeight, aemWeight, pdfWeight);
  else {
    wt   = selected->weightEmissions( trial, 1, 0, depthIn, maxScale );
    if (wt != 0.) asWeight  = selected->weightALPHAS( asME, asFSR, asISR,
      0, depthIn, useEffScale);
    if (wt != 0.) aemWeight = selected->weightALPHAEM( aemME, aemFSR,
      aemISR, 0, depthIn, useEffScale);
    if (wt != 0.) pdfWeight = selected->weightPDFs( maxScale,
      selected->clusterIn.pT(), 0, depthIn);
  }

  // MPI no-emission probability.
  int njetsMaxMPI = mergingHooksPtr->nMinMPI();
  double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                   maxScale );

  // Weight to to dynamic scale choice of hard process.
  double wtHard = selected->weightHardState( selected->state,
    infoPtr->alphaS(),
    mergingHooksPtr->AlphaS_FSR(),
    infoPtr->alphaEM(),
    mergingHooksPtr->AlphaEM_FSR());

  //mpiwt = asWeight = aemWeight = pdfWeight = wtHard = 1.;

//  if ( !foundOrderedPath ) { int bla; cin >> bla; }

  // Done
  return (wt*asWeight*aemWeight*pdfWeight*mpiwt*wtHard);

}

//--------------------------------------------------------------------------

double DireHistory::weight_UNLOPS_LOOP(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
  int depthIn) {
  // No difference to default NL3
  if (depthIn < 0) return weightLOOP(trial, RN);
  else return weight_UNLOPS_TREE(trial, asFSR,asISR, aemFSR,aemISR, RN,depthIn);
}

//--------------------------------------------------------------------------

double DireHistory::weight_UNLOPS_SUBT(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
  int depthIn) {

  if ( mergingHooksPtr->canCutOnRecState() && !foundAllowedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_SUBT: No allowed history";
    message+=" found. Using disallowed history.";
    infoPtr->errorMsg(message);
  }

  if ( mergingHooksPtr->orderHistories() && !foundOrderedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_SUBT: No ordered history";
    message+=" found. Using unordered history.";
    infoPtr->errorMsg(message);
  }
  if ( mergingHooksPtr->canCutOnRecState()
    && mergingHooksPtr->orderHistories()
    && !foundAllowedPath && !foundOrderedPath ) {
    string message="Warning in DireHistory::weight_UNLOPS_SUBT: No allowed or ordered";
    message+=" history found.";
    infoPtr->errorMsg(message);
  }

  // Select a path of clusterings
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();
  // So far, no reweighting
  double wt = 1.;

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  double aemME    = infoPtr->alphaEM();
  double maxScale = (foundCompletePath)
                  ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Only allow two clusterings if all intermediate states above the
  // merging scale.
  double nSteps = mergingHooksPtr->getNumberOfClusteringSteps(state);
  if ( nSteps == 2 && mergingHooksPtr->nRecluster() == 2
    && ( !foundCompletePath
      || !selected->allIntermediateAboveRhoMS( mergingHooksPtr->tms() )) )
    return 0.;

  // Get weights: alpha_S ratios and PDF ratios
  double asWeight  = 1.;
  double aemWeight = 1.;
  double pdfWeight = 1.;
  bool useEffScale = selected->useEffectiveScale();
  // Do trial shower, calculation of alpha_S ratios, PDF ratios
  double sudakov = 1.;
  if (depthIn < 0)
    sudakov = selected->weight(trial, asME, aemME, maxScale,
      selected->clusterIn.pT(), asFSR, asISR, aemFSR, aemISR, useEffScale,
      asWeight, aemWeight, pdfWeight);
  else {
    sudakov   = selected->weightEmissions( trial, 1, 0, depthIn, maxScale );
    if (sudakov > 0.) asWeight  = selected->weightALPHAS( asME, asFSR,
      asISR, 0, depthIn, useEffScale);
    if (sudakov > 0.) aemWeight  = selected->weightALPHAEM( aemME, aemFSR,
      aemISR, 0, depthIn, useEffScale);
    if (sudakov > 0.) pdfWeight = selected->weightPDFs( maxScale,
      selected->clusterIn.pT(), 0, depthIn);
  }

  // MPI no-emission probability.
  int njetsMaxMPI = mergingHooksPtr->nMinMPI()+1;
  double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                   maxScale );

  // Weight to to dynamic scale choice of hard process.
  double wtHard = selected->weightHardState( selected->state,
    infoPtr->alphaS(),
    mergingHooksPtr->AlphaS_FSR(),
    infoPtr->alphaEM(),
    mergingHooksPtr->AlphaEM_FSR());

  //mpiwt = asWeight = aemWeight = pdfWeight = wtHard = 1.;

  // Set weight
  wt = ( mergingHooksPtr->nRecluster() == 2 ) ? 1.
     : asWeight*aemWeight*pdfWeight*sudakov*mpiwt*wtHard;

  // Done
  return wt;

}

//--------------------------------------------------------------------------

double DireHistory::weight_UNLOPS_SUBTNLO(PartonLevel* trial, AlphaStrong * asFSR,
  AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
  int depthIn) {

  if (depthIn < 0) {

    // Select a path of clusterings
    DireHistory *  selected = select(RN);
    // Set scales in the states to the scales pythia would have set
    selected->setScalesInHistory();
    // So far, no reweighting
    double wt = 1.;
    // Only reweighting with MPI no-emission probability
    double maxScale = (foundCompletePath) ? infoPtr->eCM()
                    : mergingHooksPtr->muFinME();
//    int njetsMaxMPI = mergingHooksPtr->nMinMPI()+1;
    int njetsMaxMPI = mergingHooksPtr->nMinMPI();
    double mpiwt = selected->weightEmissions( trial, -1, 0, njetsMaxMPI,
                     maxScale );
    wt = mpiwt;
    // Done
    return wt;

  } else return weight_UNLOPS_SUBT(trial, asFSR, asISR, aemFSR, aemISR, RN,
                                   depthIn);

}

//--------------------------------------------------------------------------

// Function to calculate O(\alpha_s)-term of CKKWL-weight for NLO merging

double DireHistory::weight_UNLOPS_CORRECTION( int order, PartonLevel* trial,
  AlphaStrong* asFSR, AlphaStrong* asISR, AlphaEM * aemFSR, AlphaEM * aemISR,
  double RN, Rndm* rndmPtr ) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << aemFSR << aemISR;

  // Already done if no correction should be calculated
  if ( order < 0 ) return 0.;

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  //double aemME    = infoPtr->alphaEM();
  double muR      = mergingHooksPtr->muRinME();
  double maxScale = (foundCompletePath)
                  ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Pick path of clusterings
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  double nSteps = mergingHooksPtr->getNumberOfClusteringSteps(state);
  // Get the lowest order k-factor and add first two terms in expansion
  double kFactor = asME * mergingHooksPtr->k1Factor(nSteps);

  // If using Bbar, which includes a tree-level part, subtract an
  // additional one, i.e. the O(\as^0) contribution as well
  double wt = 1.;

  // If only O(\alpha_s^0)-term is to be calculated, done already.
  if ( order == 0 ) return wt;

  // Start by adding the O(\alpha_s^1)-term of the k-factor.
  wt += kFactor;

  // Calculate sum of O(\alpha_s^1)-terms of the ckkw-l weight WITHOUT
  // the O(\alpha_s^1)-term of the last no-emission probability.
  bool fixpdf = true;
  bool fixas  = true;
  // Get first term in expansion of alpha_s ratios.
  bool useEffScale = selected->useEffectiveScale();
  double wA   = selected->weightAlphasExpanded( 1, asME, muR, asFSR, asISR,
    useEffScale);
  // Add logarithm from \alpha_s expansion to weight.
  wt         += (fixas) ? wA : 0.;

  // Get first term in expansion of hard state reweighting.
  double wH = selected->weightHardStateExpanded(1,selected->state, asME, muR);
  wt         += wH;

  // Generate true average, not only one-point.
  double nWeight = 0.;
  for ( int i=0; i < NTRIAL; ++i ) {
    // Get average number of emissions.
    double wE   = selected->weightEmissionsExpanded(1,trial,asME, maxScale,
      asFSR, asISR, fixpdf, fixas );
    // Add average number of emissions off reconstructed states to weight.
    nWeight    += wE;
    // Get first term in expansion of PDF ratios.
    double pscale = selected->clusterIn.pT();
    double wP   = selected->weightFirstPDFs(asME, maxScale, pscale, rndmPtr);
    // Add integral of DGLAP shifted PDF ratios from \alpha_s expansion to wt.
    nWeight    += (fixpdf) ? wP : 0.;
  }
  wt += nWeight/double(NTRIAL);

  // If O(\alpha_s^1)-term + O(\alpha_s^1)-term is to be calculated, done.
  if ( order == 1 ) return wt;

  // So far, no calculation of  O(\alpha_s^2)-term
  return 0.;

}

//--------------------------------------------------------------------------

map<string,double> DireHistory::weightAllOrderExpanded(int order,
  PartonLevel* trial, AlphaStrong * asFSR, AlphaStrong * asISR,
  AlphaEM * aemFSR, AlphaEM * aemISR, double RN) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << aemFSR << aemISR;

  map<string,double> terms;

  // Already done if no correction should be calculated
  if ( order < 0 ) return terms;

  // Read alpha_S in ME calculation and maximal scale (eCM)
  double asME     = infoPtr->alphaS();
  //double aemME    = infoPtr->alphaEM();
  double muR      = mergingHooksPtr->muRinME();
  double maxScale = (foundCompletePath)
                  ? infoPtr->eCM()
                  : mergingHooksPtr->muFinME();

  // Pick path of clusterings
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // If using Bbar, which includes a tree-level part, subtract an
  // additional one, i.e. the O(\as^0) contribution as well
  double wt = 1.;

  // If only O(\alpha_s^0)-term is to be calculated, done already.
  if ( order == 0 ) return terms;

  // Calculate sum of O(\alpha_s^1)-terms of the ckkw-l weight WITHOUT
  // the O(\alpha_s^1)-term of the last no-emission probability.
  // Get first term in expansion of alpha_s ratios.
  bool useEffScale = selected->useEffectiveScale();
  double wA   = selected->weightAlphasExpanded( order, asME, muR, asFSR,
    asISR, useEffScale, terms);
  // Add logarithm from \alpha_s expansion to weight.
  wt         += wA;

  // Generate true average, not only one-point.
  double nWeight = 0.;
  map<string,double> sumterms;
  for ( int i=0; i < NTRIAL; ++i ) {
    // Get average number of emissions.
    double wE   = selected->weightEmissionsExpanded(order, trial,asME,
      maxScale, asFSR, asISR, true, true, sumterms );
    // Add average number of emissions off reconstructed states to weight.
    nWeight    += wE;
  }
  wt += nWeight/double(NTRIAL);

  for ( map<string,double>::iterator
    it = sumterms.begin(); it != sumterms.end(); ++it )
    it->second /= double(NTRIAL);
  terms.insert(sumterms.begin(),sumterms.end());

  selected->weightPDFExpanded( order, asME, maxScale, terms);

  //for ( map<string,double>::iterator
  //  it = terms.begin(); it != terms.end(); ++it )
  //  cout << it->first << " " << it->second << endl;

  // Done.
  return terms;

}

//--------------------------------------------------------------------------

// Function to set the state with complete scales for evolution.

void DireHistory::getStartingConditions( const double RN, Event& outState ) {

  // Select the history
  DireHistory *  selected = select(RN);

  // Set scales in the states to the scales pythia would have set
  selected->setScalesInHistory();

  // Get number of clustering steps.
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(state);

  // Update the lowest order process.
  if (!selected->mother) {
    int nFinal = 0;
    for(int i=0; i < int(state.size()); ++i)
      if ( state[i].isFinal()) nFinal++;

    if (nSteps == 0) {
      double startingScale = hardStartScale(state);
      state.scale(startingScale);
      for (int i = 3;i < state.size();++i)
        state[i].scale(startingScale);
    }

    // Save information on last splitting, to allow the next
    // emission in the shower to have smaller rapidity with
    // respect to the last ME splitting.
    // For hard process, use dummy values.
    if (mergingHooksPtr->getNumberOfClusteringSteps(state) == 0) {
      infoPtr->zNowISR(0.5);
      infoPtr->pT2NowISR(pow(state[0].e(),2));
      infoPtr->hasHistory(true);
    // For incomplete process, try to use real values.
    } else {
      infoPtr->zNowISR(0.5);
      infoPtr->pT2NowISR(pow(state[0].e(),2));
      infoPtr->hasHistory(true);
    }

  } else {

    // Save information on last splitting, to allow the next
    // emission in the shower to have smaller rapidity with
    // respect to the last ME splitting.
    infoPtr->zNowISR(0.5);
    infoPtr->pT2NowISR(pow(state[0].e(),2));
    infoPtr->hasHistory(true);

  }

  // Copy the output state.
  outState = state;

  // Save MPI starting scale.
  if (nSteps == 0)
    mergingHooksPtr->muMI(infoPtr->eCM());
  else
    mergingHooksPtr->muMI(outState.scale());

  mergingHooksPtr->setShowerStoppingScale(0.0);

}

//--------------------------------------------------------------------------

// Function to print the history that would be chosen from the number RN.

void DireHistory::printHistory( const double RN ) {
  DireHistory *  selected = select(RN);
  selected->printStates();
  // Done
}

//--------------------------------------------------------------------------

// Function to print the states in a history, starting from the hard process.

void DireHistory::printStates() {
  if ( !mother ) {
    cout << scientific << setprecision(4) << "Probability="
         << prodOfProbs << endl;
    //state.list(true,true);
    //state.list();
    cout << "State:\t\t\t"; listFlavs(state,true);
    return;
  }

  // Print.
  double p = (mother) ? prodOfProbs/mother->prodOfProbs : prodOfProbs;
  cout << scientific << setprecision(4) << "Probabilities:"
       << "\n\t Product =              "
       << prodOfProbs << " " << prodOfProbsFull
       << "\n\t Single with coupling = " << p
       << "\n\t Cluster probability  = " << clusterProb
       << "\t\t" << clusterIn.name()
       << "\nScale=" << clusterIn.pT() << endl;
  cout << "State:\t\t\t"; listFlavs(state,true);
  cout << "rad=" << clusterIn.radPos
       << " emt1=" << clusterIn.emt1Pos
       << " emt2=" << clusterIn.emt2Pos
       << " rec=" << clusterIn.recPos << endl;
  // Recurse
  mother->printStates();
  // Done
  return;
}

//--------------------------------------------------------------------------

void DireHistory::printLeaves() {

  for ( map<double, DireHistory*>::iterator
    it  = paths.begin();
    it != paths.end(); ++it ) {
    vector<double> sc = it->second->scales(this);

    cout << scientific << setprecision(4)
         << " New leaf with scales ";
    for (size_t i=0; i< sc.size(); ++i)
      cout << " " << sc[i];
    cout << endl;

    /*cout << scientific << setprecision(4)
         << " New leaf with prob " << it->first
         << " " << it->second->prodOfProbsFull
         << " " << it->second->prodOfProbs
         << "\n Lowest multiplicity state :" << endl;
    it->second->state.list(false,false,10);
    it->second->printStates();*/
  }

  for ( map<double, DireHistory*>::iterator
    it  = goodBranches.begin();
    it != goodBranches.end(); ++it ) {
    vector<double> sc = it->second->scales(this);
    cout << scientific << setprecision(4)
         << " New good leaf with scales ";
    for (size_t i=0; i< sc.size(); ++i)
      cout << " " << sc[i];
    cout << endl;


    /*cout << scientific << setprecision(4)
         << " New good leaf with prob " << it->first
         << " " << it->second->prodOfProbsFull
         << " " << it->second->prodOfProbs
         << "\n Lowest multiplicity state :" << endl;
    it->second->state.list(false,false,10);
    it->second->printStates();*/
  }

}

//--------------------------------------------------------------------------

void DireHistory::collectGenerations() {
  for ( map<double, DireHistory*>::iterator
    it  = branches.begin();
    it != branches.end(); ++it ) {
    it->second->attachNodes();
  }
}

//--------------------------------------------------------------------------

void DireHistory::attachNodes() {
  storeNode(this,depth);
  if (mother) mother->attachNodes();
}

//--------------------------------------------------------------------------

void DireHistory::storeNode(DireHistory* hist, int gen) {
  if (!mother) appendNode(hist, gen);
  else mother->storeNode(hist, gen);
}

//--------------------------------------------------------------------------

void DireHistory::appendNode(DireHistory* hist, int gen) {
  map<int, vector<DireHistory*> >::iterator it
    = generations.find(gen);
  if ( it != generations.end() ) {
    if (find(generations[gen].begin(), generations[gen].end(), hist)
      == generations[gen].end()) {
      //generations[gen].push_back(hist);
      generations[gen].push_back(0);
      generations[gen].back() = hist;
    }
  } else {
    generations.insert(make_pair(gen, createvector<DireHistory*>(hist)));
  }
}

//--------------------------------------------------------------------------

void DireHistory::printGenerations() {
  for ( map<int, vector<DireHistory*> >::iterator it
    = generations.begin(); it != generations.end(); ++it ) {
    cout << "generation " << it->first
    << " : size " << it->second.size() << endl;
    for (size_t i=0; i< it->second.size(); ++i)
      cout << "  " << (it->second)[i] << "\t\t"
      << " state size=" << (it->second)[i]->state.size()
      << " children size=" << (it->second)[i]->children.size()
      << " couplEffective=" << (it->second)[i]->couplEffective
      << " tEffective=" << (it->second)[i]->scaleEffective
      << " MECnum/MECden=" << (it->second)[i]->MECnum/(it->second)[i]->MECden
      << endl;
  }

}

//--------------------------------------------------------------------------

void DireHistory::printTree() {
  for ( map<double, DireHistory*>::iterator
    it  = branches.begin();
    it != branches.end(); ++it ) {
    cout << "\nAscend from new leaf " << it->second << endl;
    it->second->printPath();
  }
}

//--------------------------------------------------------------------------

void DireHistory::printPath() {
  cout << scientific << setprecision(4)
       << " New node " << this
       << " size state=" << state.size()
       << endl;

  cout << " size children=" << children.size() << endl;
  for (int i = 0;i < int(children.size());++i)
    cout << "   child[" << i << "]=" << children[i] << endl;
  
  cout << " size goodChildren= " << goodChildIndex.size() << endl;
  for (int i = 0;i < int(goodChildIndex.size());++i) 
    cout << "   child[" << i << goodChildIndex[i] << "] size="
         << children[goodChildIndex[i]]->state.size() << " "
         << children[goodChildIndex[i]] << endl;

  cout << " size sisters=" << goodSisters.size() << endl;
  for (int i = 0;i < int(goodSisters.size());++i) 
    cout << "   sister[" << i << "] size=" << goodSisters[i]->state.size()
    << " " << goodSisters[i] << endl;

  if (mother) mother->printPath();

}

//--------------------------------------------------------------------------

// Function to set the state with complete scales for evolution.

bool DireHistory::getClusteredEvent( const double RN, int nSteps,
                Event& outState) {

  // Select history
  DireHistory *  selected = select(RN);
  // Set scales in the states to the scales pythia would have set
  // (Only needed if not done before in calculation of weights or
  //  setting of starting conditions)
  selected->setScalesInHistory();
  // If the history does not allow for nSteps clusterings (e.g. because the
  // history is incomplete), return false
  if (nSteps > selected->nClusterings(this)) return false;
  // Return event with nSteps-1 additional partons (i.e. recluster the last
  // splitting) and copy the output state
  outState = selected->clusteredState(nSteps-1);
  // Done.
  return true;

}

//--------------------------------------------------------------------------

bool DireHistory::getFirstClusteredEventAboveTMS( const double RN, int nDesired,
                Event& process, int& nPerformed, bool doUpdate ) {

  // Do reclustering (looping) steps. Remember process scale.
  int nTried  = nDesired - 1;
  // Get number of clustering steps.
  int nSteps   = select(RN)->nClusterings(this);
  // Set scales in the states to the scales pythia would have set.
  select(RN)->setScalesInHistory();

  // Recluster until reclustered event is above the merging scale.
  Event dummy(15);
  bool isBelowTMS=false;
  int nRecluster = mergingHooksPtr->nReclusterSave;
  do {

    // Initialise temporary output of reclustering.
    dummy.clear();
    dummy.init( "(hard process-modified)", particleDataPtr );
    dummy.clear();
    // Recluster once more.
    nTried++;
    // If reclustered event does not exist, exit.
    if ( !getClusteredEvent( RN, nSteps-nTried+1, dummy ) ) return false;
    if ( nTried >= nSteps ) break;
    mergingHooksPtr->nReclusterSave = nTried;
    double tnowNew  = mergingHooksPtr->tmsNow( dummy);
    isBelowTMS      = tnowNew < mergingHooksPtr->tms();
    // If merging scale is not well-defined, check veto code instead!
    int vetoCode = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->ktTypeSave=-99;
    if (tnowNew <= 0. && vetoCode!=-99) {
      if (vetoCode == -1) isBelowTMS = true;
      else                isBelowTMS = false;
    }
    mergingHooksPtr->nReclusterSave = nRecluster;

    // Continue loop if reclustered event has unresolved partons.
  } while (mergingHooksPtr->getNumberOfClusteringSteps(dummy) > 0
        && isBelowTMS);

  // Update the hard process.
  if ( doUpdate ) process = dummy;

  // Failed to produce output state.
  if ( nTried > nSteps ) return false;

  nPerformed = nTried;
  if ( doUpdate ) {
    // Update to the actual number of steps.
    mergingHooksPtr->nReclusterSave = nPerformed;
    // Save MPI starting scale
    if (mergingHooksPtr->getNumberOfClusteringSteps(state) == 0)
      mergingHooksPtr->muMI(infoPtr->eCM());
    else
      mergingHooksPtr->muMI(state.scale());

    mergingHooksPtr->setShowerStoppingScale(0.0);
  }

  // Done
  return true;

}

//--------------------------------------------------------------------------

// Calculate and return pdf ratio.

double DireHistory::getPDFratio( int side, bool forSudakov, bool useHardPDFs,
                    int flavNum, double xNum, double muNum,
                    int flavDen, double xDen, double muDen) {

  // Do nothing for e+e- beams
  if ( particleDataPtr->colType(flavNum) == 0) return 1.0;
  if ( particleDataPtr->colType(flavDen) == 0) return 1.0;

  // Now calculate PDF ratio if necessary
  double pdfRatio = 1.0;

  // Get mother and daughter pdfs
  double pdfNum = 0.0;
  double pdfDen = 0.0;

  // Use hard process PDFs (i.e. PDFs NOT used in ISR, FSR or MPI).
  if ( useHardPDFs ) {
    if (side == 1) {
      if (forSudakov)
        pdfNum = mother->beamA.xfHard( flavNum, xNum, muNum*muNum);
      else
        pdfNum = beamA.xfHard( flavNum, xNum, muNum*muNum);
      if (forSudakov)
        pdfDen = max(1e-10, beamA.xfHard( flavDen, xDen, muDen*muDen));
      else
        pdfDen = max(1e-10, beamA.xfHard( flavDen, xDen, muDen*muDen));
    } else {
      if (forSudakov)
        pdfNum = mother->beamB.xfHard( flavNum, xNum, muNum*muNum);
      else
        pdfNum = beamB.xfHard( flavNum, xNum, muNum*muNum);

      if (forSudakov)
        pdfDen = max(1e-10,beamB.xfHard( flavDen, xDen, muDen*muDen));
      else
        pdfDen = max(1e-10,beamB.xfHard( flavDen, xDen, muDen*muDen));
    }

  // Use rescaled PDFs in the presence of multiparton interactions
  } else {
    if (side == 1) {
      if (forSudakov)
        pdfNum = mother->beamA.xfISR(0, flavNum, xNum, muNum*muNum);
      else
        pdfNum = beamA.xfISR(0, flavNum, xNum, muNum*muNum);
      if (forSudakov)
        pdfDen = max(1e-10, beamA.xfISR(0, flavDen, xDen, muDen*muDen));
      else
        pdfDen = max(1e-10, beamA.xfISR(0, flavDen, xDen, muDen*muDen));

    } else {
      if (forSudakov)
        pdfNum = mother->beamB.xfISR(0, flavNum, xNum, muNum*muNum);
      else
        pdfNum = beamB.xfISR(0, flavNum, xNum, muNum*muNum);
      if (forSudakov)
        pdfDen = max(1e-10,beamB.xfISR(0, flavDen, xDen, muDen*muDen));
      else
        pdfDen = max(1e-10,beamB.xfISR(0, flavDen, xDen, muDen*muDen));
    }
  }

  // Cut out charm threshold.
  if ( forSudakov && abs(flavNum) ==4 && abs(flavDen) == 4 && muDen == muNum
    && muNum < particleDataPtr->m0(4))
    pdfDen = pdfNum = 1.0;

  // Return ratio of pdfs
  if ( pdfNum > 1e-15 && pdfDen > 1e-10 ) {
    pdfRatio *= pdfNum / pdfDen;
  } else if ( pdfNum < pdfDen ) {
    pdfRatio = 0.;
  } else if ( pdfNum > pdfDen ) {
    pdfRatio = 1.;
  }

  // Done
  return pdfRatio;

}

//--------------------------------------------------------------------------

/*--------------- METHODS USED FOR ONLY ONE PATH OF HISTORY NODES ------- */

// Function to set all scales in the sequence of states. This is a
// wrapper routine for setScales and setEventScales methods

void DireHistory::setScalesInHistory() {

  // Find correct links from n+1 to n states (mother --> child), as
  // needed for enforcing ordered scale sequences
  vector<int> ident;
  findPath(ident);

  // Set production scales in the states to the scales pythia would
  // have set and enforce ordering
  bool useEffScale = useEffectiveScale();
  setScales(ident, true, useEffScale);

  // Set the overall event scales to the scale of the last branching
  setEventScales();

}

//--------------------------------------------------------------------------

// Function to find the index (in the mother histories) of the
// child history, thus providing a way access the path from both
// initial history (mother == 0) and final history (all children == 0)
// IN vector<int> : The index of each child in the children vector
//                  of the current history node will be saved in
//                  this vector
// NO OUTPUT

void DireHistory::findPath(vector<int>& out) {

  // If the initial and final nodes are identical, return
  if (!mother && int(children.size()) < 1) return;

  // Find the child by checking the children vector for the perfomed
  // clustering
  int iChild=-1;
  if ( mother ) {
    int size = int(mother->children.size());
    // Loop through children and identify child chosen
    for ( int i=0; i < size; ++i) {
      if ( mother->children[i]->scale == scale
        && mother->children[i]->prodOfProbs == prodOfProbs
        && equalClustering(mother->children[i]->clusterIn,clusterIn)) {
        iChild = i;
        break;
      }
    }
    // Save the index of the child in the children vector and recurse
    if (iChild >-1)
      out.push_back(iChild);
    mother->findPath(out);
  }
}

//--------------------------------------------------------------------------

// Functions to set the  parton production scales and enforce
// ordering on the scales of the respective clusterings stored in
// the History node:
// Method will start from lowest multiplicity state and move to
// higher states, setting the production scales the shower would
// have used.
// When arriving at the highest multiplicity, the method will switch
// and go back in direction of lower states to check and enforce
// ordering for unordered histories.
// IN vector<int> : Vector of positions of the chosen child
//                  in the mother history to allow to move
//                  in direction initial->final along path
//    bool        : True: Move in direction low->high
//                       multiplicity and set production scales
//                  False: Move in direction high->low
//                       multiplicity and check and enforce
//                       ordering
// NO OUTPUT

void DireHistory::setScales( vector<int> index, bool forward,
  bool useEffScale) {

  // Scale setting less conventional for MOPS --> separate code.

  // CKKW-L scale setting.
  if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")) {

  // First, set the scales of the hard process to the kinematial
  // limit (=s)
  if ( children.empty() && forward ) {
    // New "incomplete" configurations showered from mu
    if (!mother) {
      double scaleNew = 1.;
      if (mergingHooksPtr->incompleteScalePrescip()==0) {
        scaleNew = mergingHooksPtr->muF();
      } else if (mergingHooksPtr->incompleteScalePrescip()==1) {
        Vec4 pOut;
        pOut.p(0.,0.,0.,0.);
        for(int i=0; i<int(state.size()); ++i)
          if (state[i].isFinal())
            pOut += state[i].p();
        scaleNew = pOut.mCalc();
      } else if (mergingHooksPtr->incompleteScalePrescip()==2) {
        scaleNew = state[0].e();
      }

      scaleNew = max( mergingHooksPtr->pTcut(), scaleNew);

      state.scale(scaleNew);
      for(int i=3; i < int(state.size());++i)
        if (state[i].colType() != 0)
          state[i].scale(scaleNew);
    } else {
      // 2->2 with non-parton particles showered from eCM
      state.scale( state[0].e() );
      // Count final partons
      bool isLEP = ( state[3].isLepton() && state[4].isLepton() );
      int nFinal = 0;
      int nFinalPartons = 0;
      int nFinalPhotons = 0;
      for ( int i=0; i < int(state.size()); ++i ) {
        if ( state[i].isFinal() ) {
          nFinal++;
          if ( state[i].colType() != 0 ) nFinalPartons++;
          if ( state[i].id() == 22 )     nFinalPhotons++;
        }
      }
      bool isQCD = ( nFinal == 2 && nFinal == nFinalPartons );
      bool isPPh = ( nFinal == 2 && nFinalPartons == 1 && nFinalPhotons == 1);
      // If 2->2, purely partonic, set event scale to kinematic pT
      if ( !isLEP && ( isQCD || isPPh ) ) {
        double scaleNew = hardFacScale(state);
        state.scale( scaleNew );
      }

      // For DIS, set the hard process scale to Q2.
      if ( ( isDIS2to2(state) || isMassless2to2(state) )
        && ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
          || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0) )
        state.scale( hardFacScale(state) );

    }

    for (int i=0; i<state.size(); ++i) {
      if (state[i].status()==-21 || state[i].status()==23) {
        state[i].scale(state.scale());
      }
    }

  }
  // Set all particle production scales, starting from lowest
  // multiplicity (final) state
  if (mother && forward) {
    // When choosing splitting scale, beware of unordered splittings:
    double scaleNew = 1.;
    if ( mergingHooksPtr->unorderedScalePrescip() == 0) {
      // Use larger scale as common splitting scale for mother and child
      scaleNew = max( mergingHooksPtr->pTcut(), max(scale,mother->scale));
    } else if ( mergingHooksPtr->unorderedScalePrescip() == 1) {
      // Use smaller scale as common splitting scale for mother and child
      if (scale < mother->scale)
        scaleNew = max( mergingHooksPtr->pTcut(), min(scale,mother->scale));
      else
        scaleNew = max( mergingHooksPtr->pTcut(), max(scale,mother->scale));
    }

    //if (useEffectiveScale() && mother->scaleEffective > 0.) {
    if (useEffScale && mother->scaleEffective > 0.) {
      scaleNew = mother->scaleEffective;
    }

    // Rescale the mother state partons to the clustering scales
    // that have been found along the path
    mother->state[clusterIn.emt1Pos].scale(scaleNew);
    mother->state[clusterIn.radPos].scale(scaleNew);
    mother->state[clusterIn.recPos].scale(scaleNew);

    // Find unchanged copies of partons in higher multiplicity states
    // and rescale those
    mother->scaleCopies(clusterIn.emt1Pos, mother->state, scaleNew);
    mother->scaleCopies(clusterIn.radPos, mother->state, scaleNew);
    mother->scaleCopies(clusterIn.recPos, mother->state, scaleNew);

    // Recurse
    mother->setScales(index,true, useEffScale);
  }

  // Now, check and correct ordering from the highest multiplicity
  // state backwards to all the clustered states
  if (!mother || !forward) {
    // Get index of child along the path
    int iChild = -1;
    if ( int(index.size()) > 0 ) {
      iChild = index.back();
      index.pop_back();
    }

    // Check that the reclustered scale is above the shower cut
    if (mother) {
      scale = max(mergingHooksPtr->pTcut(), scale);
      //if (useEffectiveScale() && mother->scaleEffective > 0.) {
      if (useEffScale && mother->scaleEffective > 0.) {
        scale = max( max(mergingHooksPtr->pTcut(), mother->scale),
                     mother->scaleEffective);
      }
    }
    // If this is NOT the 2->2 process, check and enforce ordering
    if (iChild != -1 && !children.empty()) {

      //if (useEffectiveScale() && scaleEffective > 0.) {
      if (useEffScale && scaleEffective > 0.) {

        double scaleEffNow = (mother) ? mother->scaleEffective : 0.;

        //scale = max( mergingHooksPtr->pTcut(), scaleEffective);
        //if (mother) scale = max(scale, mother->scaleEffective); 
        scale = max(max(mergingHooksPtr->pTcut(),scale), scaleEffNow); 

        if (scale > children[iChild]->scale ) {
          // Enforce ordering in particle production scales
          for( int i = 0; i < int(children[iChild]->state.size()); ++i)
            if (children[iChild]->state[i].scale() == children[iChild]->scale)
              children[iChild]->state[i].scale(scale);
          // Enforce ordering in saved clustering scale
          children[iChild]->scale = scale;
        }

        double scalemin = state[0].e();
        for( int i = 0; i < int(state.size()); ++i)
          if (state[i].colType() != 0)
            scalemin = max(mergingHooksPtr->pTcut(),
                         min(scalemin,state[i].scale()));
        state.scale(scalemin);
        /*scale = max(mergingHooksPtr->pTcut(), scale);*/

      } else if (scale > children[iChild]->scale ) {

        if ( mergingHooksPtr->unorderedScalePrescip() == 0) {
          // Use larger scale as common splitting scale for mother and child
          double scaleNew = max( mergingHooksPtr->pTcut(),
                              max(scale,children[iChild]->scale));
          // Enforce ordering in particle production scales
          for( int i = 0; i < int(children[iChild]->state.size()); ++i)
            if (children[iChild]->state[i].scale() == children[iChild]->scale)
              children[iChild]->state[i].scale(scaleNew);
          // Enforce ordering in saved clustering scale
          children[iChild]->scale = scaleNew;

        } else if ( mergingHooksPtr->unorderedScalePrescip() == 1) {
           // Use smaller scale as common splitting scale for mother & child
           double scaleNew = max(mergingHooksPtr->pTcut(),
                               min(scale,children[iChild]->scale));
           // Enforce ordering in particle production scales
           for( int i = 0; i < int(state.size()); ++i)
             if (state[i].scale() == scale)
               state[i].scale(scaleNew);
           // Enforce ordering in saved clustering scale
           scale = scaleNew;
        }
      
      // Just set the overall event scale to the minimal scale
      } else {

        double scalemin = state[0].e();
        for( int i = 0; i < int(state.size()); ++i)
          if (state[i].colType() != 0)
            scalemin = max(mergingHooksPtr->pTcut(),
                         min(scalemin,state[i].scale()));
        state.scale(scalemin);
        scale = max(mergingHooksPtr->pTcut(), scale);
      }
      //Recurse
      children[iChild]->setScales(index, false, useEffScale);
    }
  }

  // Done with CKKW-L scale setting.
  // MOPS scale setting.
  } else {

  // First, set the scales of the hard process to the kinematial
  // limit (=s)
  if ( children.empty() && forward ) {
    // New "incomplete" configurations showered from mu
    if (!mother) {
      double scaleNew = 1.;
      if (mergingHooksPtr->incompleteScalePrescip()==0) {
        scaleNew = mergingHooksPtr->muF();
      } else if (mergingHooksPtr->incompleteScalePrescip()==1) {
        Vec4 pOut;
        pOut.p(0.,0.,0.,0.);
        for(int i=0; i<int(state.size()); ++i)
          if (state[i].isFinal())
            pOut += state[i].p();
        scaleNew = pOut.mCalc();
      } else if (mergingHooksPtr->incompleteScalePrescip()==2) {
        scaleNew = state[0].e();
      }

      scaleNew = max( mergingHooksPtr->pTcut(), scaleNew);

      state.scale(scaleNew);
      for(int i=3; i < int(state.size());++i)
        if (state[i].colType() != 0)
          state[i].scale(scaleNew);
    } else {
      // 2->2 with non-parton particles showered from eCM
      state.scale( state[0].e() );
      // Count final partons
      bool isLEP = ( state[3].isLepton() && state[4].isLepton() );
      int nFinal = 0;
      int nFinalPartons = 0;
      int nFinalPhotons = 0;
      for ( int i=0; i < int(state.size()); ++i ) {
        if ( state[i].isFinal() ) {
          nFinal++;
          if ( state[i].colType() != 0 ) nFinalPartons++;
          if ( state[i].id() == 22 )     nFinalPhotons++;
        }
      }
      bool isQCD = ( nFinal == 2 && nFinal == nFinalPartons );
      bool isPPh = ( nFinal == 2 && nFinalPartons == 1 && nFinalPhotons == 1);
      // If 2->2, purely partonic, set event scale to kinematic pT
      if ( !isLEP && ( isQCD || isPPh ) ) {
        double scaleNew = hardFacScale(state);
        state.scale( scaleNew );
      }

      // For DIS, set the hard process scale to Q2.
      if ( ( isDIS2to2(state) || isMassless2to2(state) )
        && ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
          || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0) )
        state.scale( hardFacScale(state) );

      double hardScale = hardStartScale(state);
      state.scale(hardScale);


    }
  }

  // Set all particle production scales, starting from lowest
  // multiplicity (final) state
  if (mother && forward) {
    //double scaleNew = (scaleEffective > 0.) ? scaleEffective : scale;
    double scaleNew
      = ( mother->scaleEffective > 0.) ? mother->scaleEffective : scale;
    scale = max(mergingHooksPtr->pTcut(), scaleNew);

    double scaleProduction
      = max( mergingHooksPtr->pTcut(), mother->scaleEffective);
    scaleProduction = max(scaleProduction,scaleNew);

    // Rescale the mother state partons to the clustering scales
    // that have been found along the path
    mother->state[clusterIn.emt1Pos].scale(scaleProduction);
    mother->state[clusterIn.radPos].scale(scaleProduction);
    mother->state[clusterIn.recPos].scale(scaleProduction);

    // Find unchanged copies of partons in higher multiplicity states
    // and rescale those
    mother->scaleCopies(clusterIn.emt1Pos, mother->state, scaleProduction);
    mother->scaleCopies(clusterIn.radPos, mother->state, scaleProduction);
    mother->scaleCopies(clusterIn.recPos, mother->state, scaleProduction);

    // Recurse
    mother->setScales(index,true, useEffScale);
  }

  // Now, check and correct ordering from the highest multiplicity
  // state backwards to all the clustered states
  if (!mother || !forward) {

    // Get index of child along the path
    int iChild = -1;
    if ( int(index.size()) > 0 ) {
      iChild = index.back();
      index.pop_back();
    }

    // Check that the reclustered scale is above the shower cut
    if (mother) {
      scale = max(mergingHooksPtr->pTcut(), scale);
      if (mergingHooksPtr->settingsPtr->flag("Dire:doMOPS"))
        scale = max(scale,mother->scaleEffective);
    }
    // If this is NOT the 2->2 process, check and enforce ordering
    if (iChild != -1 && !children.empty()) {
      if (scale > children[iChild]->scale ) {

        //double scaleNew = max( mergingHooksPtr->pTcut(), 
        //  max(children[iChild]->scale, scaleEffective));
        //if (mother) scaleNew = max(scaleNew, mother->scaleEffective); 

        double scaleEffNow = (mother) ? mother->scaleEffective : 0.;
        double scaleNew
          = max( max( mergingHooksPtr->pTcut(), children[iChild]->scale),
                 scaleEffNow);

        // Enforce ordering in particle production scales
        for( int i = 0; i < int(children[iChild]->state.size()); ++i) {
          if (children[iChild]->state[i].scale() == children[iChild]->scale)
            children[iChild]->state[i].scale(scaleNew);
        }
        // Enforce ordering in saved clustering scale
        children[iChild]->scale = scaleNew;

      } else {
        double scalemin = state[0].e();
        for( int i = 0; i < int(state.size()); ++i)
          if (state[i].colType() != 0)
            scalemin = max(mergingHooksPtr->pTcut(),
                         min(scalemin,state[i].scale()));
        state.scale(scalemin);
        scale = max(mergingHooksPtr->pTcut(), scale);
      }
      //Recurse
      children[iChild]->setScales(index, false, useEffScale);
    }
  }

  // Done with MOPS scale setting.
  }


}

//--------------------------------------------------------------------------

// Function to find a particle in all higher multiplicity events
// along the history path and set its production scale to the input
// scale
// IN  int iPart       : Parton in refEvent to be checked / rescaled
//     Event& refEvent : Reference event for iPart
//     double scale    : Scale to be set as production scale for
//                       unchanged copies of iPart in subsequent steps

void DireHistory::scaleCopies(int iPart, const Event& refEvent, double rho) {

  // Check if any parton recently rescaled is found unchanged:
  // Same charge, colours in mother->state
  if ( mother ) {
    for( int i=0; i < mother->state.size(); ++i) {
      if ( ( mother->state[i].id()         == refEvent[iPart].id()
          && mother->state[i].colType()    == refEvent[iPart].colType()
          && mother->state[i].chargeType() == refEvent[iPart].chargeType()
          && mother->state[i].col()        == refEvent[iPart].col()
          && mother->state[i].acol()       == refEvent[iPart].acol() )
         ) {
        // Rescale the unchanged parton
        mother->state[i].scale(rho);
        // Recurse
         if (mother->mother)
          mother->scaleCopies( iPart, refEvent, rho );
       } // end if found unchanged parton case
    } // end loop over particle entries in event
  }
}

//--------------------------------------------------------------------------

// Functions to set the OVERALL EVENT SCALES [=state.scale()] to
// the scale of the last clustering
// NO INPUT
// NO OUTPUT

void DireHistory::setEventScales() {
  // Set the event scale to the scale of the last clustering,
  // except for the very lowest multiplicity state
  if (mother) {
    mother->state.scale(scale);
    // Recurse
    mother->setEventScales();
  }
}

//--------------------------------------------------------------------------

// Function to return the depth of the history (i.e. the number of
// reclustered splittings)
// NO INPUT
// OUTPUT int  : Depth of history

int DireHistory::nClusterings(DireHistory* end) {
  if ( this == end)  return 0;
  if (!mother) return 0;
  int w = mother->nClusterings(end);
  w += 1;
  return w;
}

int DireHistory::nOrdered( double maxscale, DireHistory* end ) {
  //return -1;
  vector<double> s = scales(end);
  if (s.empty()) return 0;
  s.push_back(maxscale);
  int no(0), nomax(0);
  for (size_t i=0; i < s.size()-1; ++i) {
    if (s[i]<s[i+1]) no++;
    if (s[i]>s[i+1]) no=0;
    nomax = max(no,nomax);
  }
  return nomax;
}

vector<double> DireHistory::scales(DireHistory* end) {
  if ( this == end) return vector<double>();
  if ( !mother ) return vector<double>();
  vector<double> ret = mother->scales(end);
  ret.push_back(clusterIn.pT());
  return ret;
}


//--------------------------------------------------------------------------

// Functions to return the event after nSteps splittings of the 2->2 process
// Example: nSteps = 1 -> return event with one additional parton
// INPUT  int   : Number of splittings in the event,
//                as counted from core 2->2 process
// OUTPUT Event : event with nSteps additional partons

Event DireHistory::clusteredState(int nSteps) {

  // Save state
  Event outState = state;
  // As long as there are steps to do, recursively save state
  if (mother && nSteps > 0)
    outState = mother->clusteredState(nSteps - 1);
  // Done
  return outState;

}

//--------------------------------------------------------------------------

// Function to choose a path from all paths in the tree
// according to their splitting probabilities
// IN double    : Random number
// OUT DireHistory* : Leaf of history path chosen

DireHistory * DireHistory::select(double rnd) {

  // No need to choose if no paths have been constructed.
  if ( branches.empty()
    && goodBranches.empty()
    && badBranches.empty() ) return this;

  // Choose history according to probability, be careful about upper bound
  if ( rnd != 1. ) {
    return branches.upper_bound(sumbranches*rnd)->second;
  } else {
    return branches.lower_bound(sumbranches*rnd)->second;
  }

  // Done
}

//--------------------------------------------------------------------------

// Pick an underlying Born randomly.
pair<double,DireHistory*> DireHistory::getDemocraticLeaf(Rndm* rndmPtr) {

  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (it->second->hasMEweightMultiplied) {
      it->second->removeMEsFromPath(it->second);
cout << __func__ << endl;
}
  }

  sumbranches=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;

  goodChildren.clear();
  for (size_t i=0; i< children.size(); ++i) {
    DireHistory* childNow = children[i];
    bool isPartOfPath=false;

    /*double nrec = mergingHooksPtr->nReclusterSave;
    int kttype  = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->nReclusterSave = 1;
    double tnowNew  = mergingHooksPtr->tmsNow(childNow->state);
    bool isBelowTMS = tnowNew < mergingHooksPtr->tms();
    // If merging scale is not well-defined, check veto code instead!
    int vetoCode = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->ktTypeSave=kttype;
    if (tnowNew <= 0.&& vetoCode!=-99) {
      if (vetoCode == -1) isBelowTMS = true;
      else                isBelowTMS = false;
    } else isBelowTMS = false;
    mergingHooksPtr->nReclusterSave = nrec;
    if (isBelowTMS) { continue;}*/

    bool isBelowTMS = childNow->scale < mergingHooksPtr->tms();
    if (isBelowTMS) continue;

    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfPath = true; break; }
        node = node->mother;
      }
      if (isPartOfPath) break;
    }
    bool isPartOfBranch = false;
    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfBranch = true; break; }
        node = node->mother;
      }
      if (isPartOfBranch) break;
    }
    if (isPartOfPath && isPartOfBranch) 
      goodChildren.push_back(childNow);
  }

  if (goodChildren.empty()) return make_pair(1.,nullptr);

  // Pick one child with democratic distribution.
  vector<double> pick_probs(goodChildren.size(),1.);

  int childIndex = rndmPtr->pick(pick_probs);
  return make_pair(1./double(goodChildren.size()),goodChildren[childIndex]);

}

//--------------------------------------------------------------------------

// Pick an underlying Born randomly.
pair<double,DireHistory*> DireHistory::getProbabilisticLeaf(Rndm* rndmPtr) {

  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (it->second->hasMEweightMultiplied)
      it->second->removeMEsFromPath(it->second);
  }

  sumbranches=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;

  goodChildren.clear();
  for (size_t i=0; i< children.size(); ++i) {
    DireHistory* childNow = children[i];
    bool isPartOfPath=false;

    /*double nrec = mergingHooksPtr->nReclusterSave;
    int kttype  = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->nReclusterSave = 1;
    double tnowNew  = mergingHooksPtr->tmsNow(childNow->state);
    bool isBelowTMS = tnowNew < mergingHooksPtr->tms();
    // If merging scale is not well-defined, check veto code instead!
    int vetoCode = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->ktTypeSave=kttype;
    if (tnowNew <= 0.&& vetoCode!=-99) {
      if (vetoCode == -1) isBelowTMS = true;
      else                isBelowTMS = false;
    } else isBelowTMS = false;
    mergingHooksPtr->nReclusterSave = nrec;
    if (isBelowTMS) {continue;}*/

    bool isBelowTMS = childNow->scale < mergingHooksPtr->tms();
    if (isBelowTMS) {continue;}

    //bool hasW = false;
    //for (int ip=0; ip < childNow->state.size(); ++ip)
    //  if (childNow->state[ip].idAbs()==24) hasW = true;
    //if (!hasW) continue;

    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfPath = true; break; }
        node = node->mother;
      }
      if (isPartOfPath) break;
    }
    bool isPartOfBranch = false;
    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfBranch = true; break; }
        node = node->mother;
      }
      if (isPartOfBranch) break;
    }
    if (isPartOfPath && isPartOfBranch) goodChildren.push_back(childNow);
  }

  //if (goodChildren.empty()) goodChildren = children;
  if (goodChildren.empty()) return make_pair(1.,nullptr);

  // Pick child according to clustering probability.
  double probsum = 0.;
  vector<double> pick_probs;
  map<double,int> pickmap;
  for (size_t i=0; i< goodChildren.size(); ++i){
    probsum += goodChildren[i]->prodOfProbs;
    pickmap.insert(make_pair(probsum,i));
    pick_probs.push_back(goodChildren[i]->prodOfProbs);
  }
  double rn = rndmPtr->flat();
  int childIndex = pickmap.upper_bound(probsum*rn)->second;
  return make_pair(goodChildren[childIndex]->prodOfProbs/probsum,
    goodChildren[childIndex]);

}

//--------------------------------------------------------------------------

// Pick an underlying Born according to full probability of the path.

pair<double,DireHistory*> DireHistory::getProbabilisticFullLeaf(Rndm* rndmPtr,
  DireHistory*& chosen_starting_leaf) {

  // Select history
  double RN = rndmPtr->flat();
  //DireHistory *  selected = select(RN);
  chosen_starting_leaf = select(RN);
  // Return next-to-highest multiplicity history node.
  //DireHistory *  leaf = selected;
  DireHistory *  leaf = chosen_starting_leaf;
  while (leaf != this && leaf->mother && leaf->mother != this)
    leaf = leaf->mother;

  leaf->extractBranches(branches);

//cout << scientific << setprecision(15) << endl;
//cout << " " << __FILE__ << " " << __LINE__ << " " << leaf << " " << this << " " << leaf->sumbranches << " " << this->sumbranches << endl;

  vector<DireHistory*> gc;
  for (size_t i=0; i< children.size(); ++i) {
    DireHistory* childNow = children[i];
    bool isPartOfPath=false;

    bool isBelowTMS = childNow->scale < mergingHooksPtr->tms();
    if (isBelowTMS) continue;

    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfPath = true; break; }
        node = node->mother;
      }
      if (isPartOfPath) break;
    }
    bool isPartOfBranch = false;
    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfBranch = true; break; }
        node = node->mother;
      }
      if (isPartOfBranch) break;
    }
    if (isPartOfPath && isPartOfBranch) 
      gc.push_back(childNow);
  }

  if (gc.empty()) return make_pair(1.,nullptr);
  //if (gc.size()==0) {cout << __func__ << " no good children!" << endl; abort();}

  /*int iLeaf = -1;
  for ( int i=0; i < gc.size(); ++i) if (gc[i]==leaf) { iLeaf = i; break;}



cout << __func__ << " " << gc.size() << " " << iLeaf << " " << branches.size() << " " << paths.size() << endl;
*/
  double sumProbToLeaf = leaf->sumbranches / this->sumbranches;

/*if (abs(sumProbToLeaf-1.) < 1e-6) {
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) cout << "this " << it->first << endl;
  for ( map<double, DireHistory*>::iterator it = leaf->branches.begin();
    it != leaf->branches.end(); ++it ) cout << "leaf " << it->first << endl;
abort();
}*/

  return make_pair(sumProbToLeaf,leaf);
}

//--------------------------------------------------------------------------

pair<double,DireHistory*> DireHistory::getNextProbabilisticFullLeaf(
  DireHistory* oldLeaf) {

  // Return next-to-highest multiplicity history node.
  DireHistory *  leaf = oldLeaf;
  while (leaf != this && leaf->mother && leaf->mother != this)
    leaf = leaf->mother;

  if (!leaf->extractBranches(branches)) {
  for ( map<double, DireHistory*>::iterator it = leaf->paths.begin();
    it != leaf->paths.end(); ++it ) cout << "path " << it->second << endl;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) cout << "branch " << it->second << endl;
  }

  double sumProbToLeaf = leaf->sumbranches / this->sumbranches;

  return make_pair(sumProbToLeaf,leaf);
}

//--------------------------------------------------------------------------

// Pick an underlying Born randomly.
double DireHistory::getSelectionRateDemocratic(DireHistory* ) {

  /*for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (it->second->hasMEweightMultiplied)
      it->second->removeMEsFromPath(it->second);
  }

  sumbranches=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;*/

  goodChildren.clear();
  for (size_t i=0; i< children.size(); ++i) {
    DireHistory* childNow = children[i];
    bool isPartOfPath=false;

    bool isBelowTMS = childNow->scale < mergingHooksPtr->tms();
    if (isBelowTMS) continue;

    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfPath = true; break; }
        node = node->mother;
      }
      if (isPartOfPath) break;
    }
    bool isPartOfBranch = false;
    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfBranch = true; break; }
        node = node->mother;
      }
      if (isPartOfBranch) break;
    }
    if (isPartOfPath && isPartOfBranch) 
      goodChildren.push_back(childNow);
  }

  if (goodChildren.empty()) return 1.;
/*  int iLeaf = -1;
  for ( int i=0; i < goodChildren.size(); ++i) if (goodChildren[i]==leaf) { iLeaf = i; break;}

cout << __func__ << " " << goodChildren.size() << " " << iLeaf << " " << branches.size() << " " << paths.size() << endl;
//cout << __FILE__ << " " << __func__ << " " << children.size() << "  " << paths.size() << "  " << branches.size() << " " << goodChildren.size() << endl;
*/

  return 1./double(goodChildren.size());

}

//--------------------------------------------------------------------------

// Pick an underlying Born randomly.
double DireHistory::getSelectionRateProbabilistic(DireHistory* leaf) {

  /*for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (it->second->hasMEweightMultiplied)
      it->second->removeMEsFromPath(it->second);
  }

  sumbranches=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;*/

  goodChildren.clear();
  for (size_t i=0; i< children.size(); ++i) {
    DireHistory* childNow = children[i];
    bool isPartOfPath=false;

    bool isBelowTMS = childNow->scale < mergingHooksPtr->tms();
    if (isBelowTMS) {continue;}

    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfPath = true; break; }
        node = node->mother;
      }
      if (isPartOfPath) break;
    }

    bool isPartOfBranch = false;
    // Check if child is part of any allowed path.
    for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      DireHistory* node = it->second;
      // Check if history is still allowed, and remove if already disallowed.
      while ( node->mother ) {
        if (node==childNow) { isPartOfBranch = true; break; }
        node = node->mother;
      }
      if (isPartOfBranch) break;
    }

    if (isPartOfPath && isPartOfBranch) {
      goodChildren.push_back(childNow);
    }
  }

  if (goodChildren.empty()) {
//cout << " " << __FILE__ << " " << __LINE__ << endl;
return 1.;
}
//cout << __FILE__ << " " << __func__ << " " << children.size() << "  " << paths.size() << "  " << branches.size() << " " << goodChildren.size() << endl;

  // Pick child according to clustering probability.
  double probsum = 0.;
  for (size_t i=0; i< goodChildren.size(); ++i){
    probsum += goodChildren[i]->prodOfProbs;
  }

//cout << " " << __FILE__ << " " << __LINE__ << " " << leaf->prodOfProbs << " " << probsum << endl;
  return leaf->prodOfProbs/probsum;

}

//--------------------------------------------------------------------------

// Pick an underlying Born according to full probability of the path.

double DireHistory::getSelectionRateProbabilisticFull(DireHistory* leaf) {

  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    if (!it->second->hasMEweightMultiplied)
      it->second->multiplyMEsToPath(it->second);
  }

  sumbranches=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumbranches += it->second->prodOfProbs;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;

  leaf->extractBranches(branches);

  double sumProbToLeaf = leaf->sumbranches / this->sumbranches;
  return sumProbToLeaf;
}

//--------------------------------------------------------------------------

void DireHistory::rescaleProbs() {

  double clusProbFull   = /*clusterCoupl * */clusterProb;
  double removeProbFull = clusProbFull*mother->MECnum/mother->MECden;
  double removeProb     = abs(clusProbFull*mother->MECnum/mother->MECden);

  // Reset the cluster probabilities to default values.
  clusterProb = clusterCoupl = prodOfProbs = prodOfProbsFull = 1.;

  // Reset path indices after removing probability to split to mother.
  vector<DireHistory*> wasRescaled;
  sumpath=0.;
  map<double, DireHistory*> newPaths;
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it ) {
    sumpath += it->second->prodOfProbs/removeProb;
    it->second->prodOfProbs     /= removeProb;
    it->second->prodOfProbsFull /= removeProbFull;
    wasRescaled.push_back(it->second);
    newPaths.insert(make_pair(sumpath,it->second));
  }
  paths = newPaths;

  newPaths.clear();
  sumbranches = 0.;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    double removeProbNow=removeProb;
    double removeProbFullNow=removeProbFull;
    if ( find(wasRescaled.begin(),wasRescaled.end(),it->second)
      != wasRescaled.end())
      removeProbNow = removeProbFullNow = 1.;
    sumbranches += it->second->prodOfProbs/removeProbNow;
    it->second->prodOfProbs     /= removeProbNow;
    it->second->prodOfProbsFull /= removeProbFullNow;
    newPaths.insert(make_pair(sumbranches,it->second));
  }
  branches = newPaths;

  newPaths.clear();
  sumGoodBranches = 0.;
  for ( map<double, DireHistory*>::iterator it = goodBranches.begin();
    it != goodBranches.end(); ++it ) {
    double removeProbNow=removeProb;
    double removeProbFullNow=removeProbFull;
    if ( find(wasRescaled.begin(),wasRescaled.end(),it->second)
      != wasRescaled.end())
      removeProbNow = removeProbFullNow = 1.;
    sumGoodBranches += it->second->prodOfProbs/removeProbNow;
    it->second->prodOfProbs     /= removeProbNow;
    it->second->prodOfProbsFull /= removeProbFullNow;
    newPaths.insert(make_pair(sumGoodBranches,it->second));
  }
  goodBranches = newPaths;

}

//--------------------------------------------------------------------------

// Function to project paths onto desired paths.

bool DireHistory::trimHistories() {

  // Do nothing if no paths have been constructed.
  if ( paths.empty() ) return false;

  DireHistory* end = this;

  // Loop through all constructed paths. Check all removal conditions.
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it ) {
    // Check if history is allowed.
    if ( it->second->keep() && !it->second->keepHistory(end) )
      it->second->remove();
    //// Keep only maximally ordered histories.
    //int nord = it->second->nOrdered(infoPtr->eCM(),end);
    //if ( it->second->keep() && nord >-1
    //  && nord != nMaxOrdered(end))
    //  it->second->remove();
  }

  // Project onto desired / undesired branches.
  double sumold(0.), sumnew(0.), mismatch(0.);
  // Loop through all constructed paths and store allowed paths.
  // Skip undesired paths.
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it ) {
    // Update index
    sumnew = it->first;
    if ( it->second->keep() ) {
      // Fill branches with allowed paths.
      goodBranches.insert( make_pair( sumnew - mismatch, it->second) );
      // Add probability of this path.
      sumGoodBranches = sumnew - mismatch;

    } else {
      // Update mismatch in probabilities resulting from not including this
      // path
      double mismatchOld = mismatch;
      mismatch += sumnew - sumold;
      // Fill branches with allowed paths.
      badBranches.insert( make_pair( mismatchOld + sumnew - sumold,
        it->second ) );
      // Add probability of this path.
      sumBadBranches = mismatchOld  + sumnew - sumold;

    }

    // remember index of this path in order to caclulate probability of
    // subsequent path.
    sumold = it->first;
  }

  if (!goodBranches.empty()) {
    branches = goodBranches;
    sumbranches = sumGoodBranches;
  } else {
    branches = badBranches;
    sumbranches = sumBadBranches;
  }

  // Done
  return !goodBranches.empty();
}

/*//--------------------------------------------------------------------------

int DireHistory::nHistoriesPassTMScuts() {

  // Do nothing if no paths have been constructed.
  if ( paths.empty() ) return 0;

  DireHistory* end = this;

  int npass = 0;

  // Loop through all constructed paths. Check all removal conditions.
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it ) {
    // Check if history is allowed.
    if ( it->second->keep() && it->second->passTMScuts(end) )
      npass++;
  }

  return npass;

}*/

//--------------------------------------------------------------------------

bool DireHistory::extractBranches(
  map<double,DireHistory*> motherBranches) {

  if ( paths.empty() || motherBranches.empty()) { return false; }

  double newsump = 0.;
  map<double,DireHistory*> newpaths;
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it ) {
    bool found = false;
    double p = 0.;
    for ( map<double, DireHistory*>::iterator iit = motherBranches.begin();
      iit != motherBranches.end(); ++iit ) {
      if (it->second == iit->second) {
        found = true;
        p = iit->second->prodOfProbs;
      }
    }
    if (!found) continue;
    newsump += p;
    newpaths.insert(make_pair(newsump,it->second));
  }

  sumbranches  = newsump;
  branches     = newpaths;
  goodBranches = branches;
  badBranches.clear();

  return (branches.size()!=0);

}

//--------------------------------------------------------------------------

// Function implementing checks on a paths, deciding if the path is valid.

bool DireHistory::keepHistory(DireHistory* end) {
  bool keepPath = true;

  double hardScale = hardStartScale(state);

  // Tag unordered paths for removal.
  if ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
    || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
    || isQCD2to2(state)   ) {
    // Tag unordered paths for removal. Include scale of hard 2->2 process
    // into the ordering definition.
    hardScale = hardStartScale(state);
  }

  // Set starting scale to mass of Drell-Yan for 2->1.
  if (isEW2to1(state)) {
    Vec4 pSum(0,0,0,0);
    for (int i = 0;i < state.size(); ++i)
      if (state[i].isFinal()) pSum += state[i].p();
    hardScale = pSum.mCalc();
  }

  // For DIS, set the hard process scale to Q2.
  if ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
    || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0 ) {
    // Tag unordered paths for removal. Include scale of hard 2->2 process
    // into the ordering definition.
    hardScale = hardFacScale(state);
  }

  //double hardScale = hardStartScale(state);
  keepPath = isOrderedPath( hardScale, end);
  
  if ( !mergingHooksPtr->orderHistories() ) keepPath = true;

  // Now apply cuts (i.e. classify history as undesirable if cuts on hard
  // process fail)
  keepPath = keepPath && passHardProcessCuts(state);

  /*// For NLO real-emission events, only keep histories in which the first
  // clustering *is* a QCD-like clustering.
  if (isHistoryForRealCorrection) {
    DireHistory * leaf = this;
    while (leaf->mother) leaf = leaf->mother;
    bool hasW = false;
    for (int ip=0; ip < leaf->state.size(); ++ip)
      if (leaf->state[ip].idAbs()==24) hasW = true;
    if (!hasW) keepPath=false;
  }*/

  keepPath = keepPath && nPartonStateAboveTMS(3, mergingHooksPtr->tms());

//begin comment when using histories below tms

  if ( mergingHooksPtr->settingsPtr->flag("Merging:makeToyCalculation")
    //|| mergingHooksPtr->doCheckBasic()
    //|| mergingHooksPtr->doCheckSudakov()
    || mergingHooksPtr->settingsPtr->flag("Dire:doTOMTE") ) {
    bool firstPass  = firstClusteringAboveTMS(mergingHooksPtr->tms());
    bool secondPass = nPartonStateAboveTMS(1, mergingHooksPtr->tms());
    bool thirdPass = nPartonStateAboveTMS(2, mergingHooksPtr->tms());
    bool fourthPass = nPartonStateAboveTMS(3, mergingHooksPtr->tms());
    keepPath = keepPath && firstPass && secondPass && thirdPass && fourthPass;
  }
//end comment when using histories below tms

  // More stringent criterion.
  //keepPath = keepPath && allIntermediateAboveRhoMS( mergingHooksPtr->tms() );

  //Done
  return keepPath;
}

/*//--------------------------------------------------------------------------

bool DireHistory::passTMScuts(DireHistory* end) {
  bool keepPath = true;
  if ( mergingHooksPtr->settingsPtr->flag("Merging:makeToyCalculation")
    || mergingHooksPtr->settingsPtr->flag("Merging:checkBiasesBasic")
    || mergingHooksPtr->settingsPtr->flag("Merging:checkBiasesSudakov")
    || mergingHooksPtr->settingsPtr->flag("Dire:doTOMTE")) {
    bool firstPass  = firstClusteringAboveTMS(mergingHooksPtr->tms());
    bool secondPass = nPartonStateAboveTMS(1, mergingHooksPtr->tms());
    bool thirdPass = nPartonStateAboveTMS(2, mergingHooksPtr->tms());
    bool fourthPass = nPartonStateAboveTMS(3, mergingHooksPtr->tms());
    keepPath = keepPath && firstPass && secondPass && thirdPass && fourthPass;
  }
  //Done
  return keepPath;
}*/

//--------------------------------------------------------------------------

bool DireHistory::contains(DireHistory* node) {
  bool found = false;
  if (this == node) found = true;
  if (mother) found = found || mother->contains(node);
  return found;
}

//--------------------------------------------------------------------------

double DireHistory::getPathIndexRandom(Rndm* rndmPtr, bool useAll,
  double& sumAll, double& sumFullAll) {

  if (!useAll) return rndmPtr->flat();

  // Setup to choose shower starting conditions randomly.
  sumAll = sumFullAll = 0.;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it ) {
    sumAll     += it->second->prodOfProbs;
    sumFullAll += it->second->prodOfProbsFull;
  }
  // Store a double with which to access each of the paths.
  double lastp(0.);
  vector<double> path_index;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
      it != branches.end(); ++it ) {
      // Double to access path.
      double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
      path_index.push_back(indexNow);
      lastp = it->first;
  }

  // Randomly pick path.
  int sizeBranches = branches.size();
  int iPosRN = (sizeBranches > 0)
             ? rndmPtr->pick(
                 vector<double>(sizeBranches, 1./double(sizeBranches)) )
             : 0;
  double RN  = (sizeBranches > 0) ? path_index[iPosRN] : rndmPtr->flat();

  return RN;
}

//--------------------------------------------------------------------------

// Function to check if a path is ordered in evolution pT.

bool DireHistory::isOrderedPath( double maxscale, DireHistory* end ) {
  double newscale = clusterIn.pT();
  if ( mother && this == end) return true;
  if ( !mother)               return (maxscale > scale);
  bool ordered = mother->isOrderedPath(newscale, end);
  if ( !ordered || maxscale < newscale) {
    return false;
  }
  return ordered;
}




//--------------------------------------------------------------------------

bool DireHistory::firstClusteringAboveTMS( double tms ) {
  DireHistory* node = this;
  while (node->mother && node->mother->mother) node = node->mother;
  if (node->scale < tms) return false;
  return true;
}

//--------------------------------------------------------------------------

bool DireHistory::nPartonStateAboveTMS(int nReq, double tms, bool good ) {
  // If one state below the merging scale has already been found, no need to
  // check further.
  if ( !good ) return false;
  if ( !mother ) return good;
  if (depth+1>=nReq && scale < tms) { good = false; }
  if ( !mother ) return good;
  if (mother && mother->mother)
    return good && mother->nPartonStateAboveTMS(nReq, tms, good);
  return good;
}

//--------------------------------------------------------------------------

// Function to check if all reconstucted states in a path pass the merging
// scale cut.

bool DireHistory::allIntermediateAboveRhoMS( double rhoms, bool good ) {
  // If one state below the merging scale has already been found, no need to
  // check further.
  if ( !good ) return false;
  // Check merging scale for states with more than 0 jets
  int nFinal = 0;
  for ( int i = 0; i < state.size(); ++i )
    if ( state[i].isFinal() && state[i].colType() != 0 )
      nFinal++;
  double rhoNew = (nFinal > 0 ) ? mergingHooksPtr->tmsNow( state )
                : state[0].e();
  // If merging scale is not well-defined, check veto code instead!
  int vetoCode = mergingHooksPtr->ktTypeSave;
  mergingHooksPtr->ktTypeSave=-99;
  if (rhoNew <= 0. && vetoCode!=-99) {
    if (vetoCode == -1) rhoNew = 0.;
    else                rhoNew = state[0].e();
  }
  // Assume state from ME generator passes merging scale cut.
  if ( !mother ) return good;
  // Recurse.
  return good && mother->allIntermediateAboveRhoMS( rhoms, (rhoNew > rhoms) );
}

//--------------------------------------------------------------------------

// Function to check if any ordered paths were found (and kept).

bool DireHistory::foundAnyOrderedPaths() {
  //Do nothing if no paths were found
  if ( paths.empty() ) return false;
  //double maxscale = infoPtr->eCM();
  double maxscale = hardStartScale(state);
  // Loop through paths. Divide probability into ordered and unordered pieces.
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it )
    if ( it->second->isOrderedPath(maxscale, this) )
      return true;
  // Done
  return false;
}

//--------------------------------------------------------------------------

// Function to check if a path contains any clustering scales below the
// shower cut-off.

bool DireHistory::hasScalesAboveCutoff() {
  if ( !mother ) return true;
  return ( clusterIn.pT() > mergingHooksPtr->pTcut()
        && mother->hasScalesAboveCutoff() );
}

//--------------------------------------------------------------------------

bool DireHistory::allPathsAboveCutoff() {
  bool above = true;
  for ( map<double, DireHistory*>::iterator it = branches.begin();
    it != branches.end(); ++it )
    above = above && it->second->isPathAboveCutoff();
  return above;
}

//--------------------------------------------------------------------------

bool DireHistory::isPathAboveCutoff() {
  if (!mother) return true;
  bool above = clusterIn.isAboveCutoff && mother->isPathAboveCutoff();
  return above;
}

//--------------------------------------------------------------------------

bool DireHistory::allPathsAboveTMS() {
  bool above = true;
  for ( map<double, DireHistory*>::iterator it = paths.begin();
    it != paths.end(); ++it )
    above = above && it->second->isPathAboveTMS();
  return above;
}

//--------------------------------------------------------------------------

bool DireHistory::isPathAboveTMS() {

  /*// Igore unordered paths for this check!
  if (children.size()==0
    && mergingHooksPtr->orderHistories()) { 
    double hardScale = hardStartScale(state);
    if (!isOrderedPath(hardScale,NULL)) return true;
  } */ 
  if (!mother) return true;
  bool above = clusterIn.pT() > mergingHooksPtr->tms()
    && mother->isPathAboveTMS();
  return above;
}

//--------------------------------------------------------------------------

// For a full path, find the weight calculated from the ratio of
// couplings, the no-emission probabilities, and possible PDF
// ratios. This function should only be called for the last history
// node of a full path.
// IN  TimeShower : Already initialised shower object to be used as
//                  trial shower
//     double     : alpha_s value used in ME calculation
//     double     : Maximal mass scale of the problem (e.g. E_CM)
//     AlphaStrong: Initialised shower alpha_s object for FSR
//                  alpha_s ratio calculation
//     AlphaStrong: Initialised shower alpha_s object for ISR
//                  alpha_s ratio calculation (can be different from previous)

double DireHistory::weight(PartonLevel* trial, double as0, double aem0,
  double maxscale, double pdfScale, AlphaStrong * asFSR, AlphaStrong * asISR,
  AlphaEM * aemFSR, AlphaEM * aemISR, bool useEffScale,
  double& asWeight, double& aemWeight, double& pdfWeight,
  map<string,double>& terms) {

  // Use correct scale
  double newScale = scale;
  stringstream nameA; nameA << "pdfratioA_" << depth;
  stringstream nameB; nameB << "pdfratioB_" << depth;
  if (terms.find(nameA.str())==terms.end()) terms[nameA.str()] = 1.;
  if (terms.find(nameB.str())==terms.end()) terms[nameB.str()] = 1.;

  // For ME state, just multiply by PDF ratios
  if ( !mother ) {

    int sideRad = (state[3].pz() > 0) ? 1 :-1;
    int sideRec = (state[4].pz() > 0) ? 1 :-1;

    //stringstream s;
    //s << "pdfratio" << depth; 
    //if (terms.find(s.str())==terms.end()) terms[s.str()] = 1.;

    // Calculate PDF first leg
    if (state[3].colType() != 0) {
      // Find x value and flavour
      double x = 2.*state[3].e() / state[0].e();
      int flav = state[3].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // For initial parton, multiply by PDF ratio
      double ratio = getPDFratio(sideRad, false, false, flav, x, scaleNum,
                       flav, x, scaleDen);
      pdfWeight *= ratio;
      terms[nameA.str()] *= ratio;
    }

    // Calculate PDF ratio for second leg
    if (state[4].colType() != 0) {
      // Find x value and flavour
      double x = 2.*state[4].e() / state[0].e();
      int flav = state[4].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // For initial parton, multiply with PDF ratio
      double ratio = getPDFratio(sideRec, false, false, flav, x, scaleNum,
                       flav, x, scaleDen);
      pdfWeight *= ratio;
      terms[nameB.str()] *= ratio;
    }

    return 1.0;
  }

  // Remember new PDF scale n case true scale should be used for un-ordered
  // splittings.
  double newPDFscale = newScale;
  if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
    &&  mergingHooksPtr->unorderedPDFscalePrescip() == 1)
    newPDFscale = clusterIn.pT();

  // Recurse
  double w = mother->weight(trial, as0, aem0, newScale, newPDFscale,
    asFSR, asISR, aemFSR, aemISR, useEffScale,
    asWeight, aemWeight, pdfWeight, terms);

  // Do nothing for empty state
  if (state.size() < 3) return 1.0;
  // Do trial shower on current state, return zero if not successful
  double sudsum = 0.;
  for (int i=0; i < NTRIAL; ++i)
    sudsum += doTrialShower(trial, 1, maxscale).front();
  double sud = sudsum/double(NTRIAL);
  w *= sud;

  stringstream s; s << "delta_" << depth;
  terms[s.str()] = sud;

  //int emtType = mother->state[clusterIn.emt1Pos].colType();
  //bool isQCD = emtType != 0;
  //bool isQED = emtType == 0;

  int radType = mother->state[clusterIn.radPos].colType();
  int emtType = mother->state[clusterIn.emt1Pos].colType();
  bool isQCD = (radType != 0 && emtType != 0);
  bool isQED = !isQCD;

  pair<int,double> coup = getCoupling(mother->state, clusterIn.radPos,
    clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name());

  s.str(""); s << "alphasratio_" << depth + 1;
  if (terms.find(s.str())==terms.end()) terms[s.str()] = 1.;

  //if (!useEffectiveScale() && coup.first > 0) { 
  if (!useEffScale && coup.first > 0) { 
    isQCD = isQED = false;
    if (coup.first == 1) {
      asWeight  *= coup.second * 2.*M_PI / as0;
      terms[s.str()] *= coup.second * 2.*M_PI / as0;
    }
    if (coup.first == 2 || coup.first == 3)
      aemWeight *= coup.second * 2.*M_PI / aem0;
  }

  // Calculate alpha_s ratio for current state.
  if ( asFSR && asISR && isQCD) {
    double asScale = pow2( newScale );
    if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
      &&  mergingHooksPtr->unorderedASscalePrescip() == 1)
      asScale = pow2( clusterIn.pT() );
    // Add regularisation scale to initial state alpha_s.
    bool FSR = mother->state[clusterIn.radPos].isFinal();
    if (!FSR) asScale += pow2(mergingHooksPtr->pT0ISR());
    // Directly get argument of running alpha_s from shower plugin.
    asScale = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleAS", asScale);
    if (mergingHooksPtr->settingsPtr->flag("Dire:doMOPS"))
      asScale = pow2(newScale);
    //if (useEffectiveScale() ) asScale = pow2(scale); 
    if (useEffScale) asScale = pow2(scale); 

    double alphaSinPS = (FSR) ? (*asFSR).alphaS(asScale)
                              : (*asISR).alphaS(asScale);
    asWeight *= alphaSinPS / as0;
    terms[s.str()] *= alphaSinPS / as0;
  }

  // Calculate alpha_em ratio for current state.
  if ( aemFSR && aemISR && isQED ) {
    double aemScale = pow2( newScale );
    if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
      &&  mergingHooksPtr->unorderedASscalePrescip() == 1)
      aemScale = pow2( clusterIn.pT() );
    // Add regularisation scale to initial state alpha_s.
    bool FSR = mother->state[clusterIn.radPos].isFinal();
    if (!FSR) aemScale += pow2(mergingHooksPtr->pT0ISR());
    // Directly get argument of running alpha_em from shower plugin.
    aemScale = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleEM", aemScale);
    //if (useEffectiveScale() ) aemScale = pow2(scale); 
    if (useEffScale) aemScale = pow2(scale); 

    double alphaEMinPS = (FSR) ? (*aemFSR).alphaEM(aemScale)
                               : (*aemISR).alphaEM(aemScale);
    aemWeight *= alphaEMinPS / aem0;
  }

  // Calculate pdf ratios: Get both sides of event
  int inP = 3;
  int inM = 4;
  int sideP = (mother->state[inP].pz() > 0) ? 1 :-1;
  int sideM = (mother->state[inM].pz() > 0) ? 1 :-1;

  //s.str(""); s << "pdfratio_" << depth;
  //if (terms.find(s.str())==terms.end()) terms[s.str()] = 1.;

  if ( mother->state[inP].colType() != 0 ) {
    // Find x value and flavour
    double x = getCurrentX(sideP);
    int flav = getCurrentFlav(sideP);
    // Find numerator scale
    double scaleNum = (children.empty())
                    ? hardFacScale(state)
                    : ( (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                       && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                      ? pdfScale : maxscale );
    double scaleDen = (  !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                       && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                    ? clusterIn.pT() : newScale;
    // Multiply PDF ratio
    double ratio = getPDFratio(sideP, false, false, flav, x, scaleNum,
                     flav, x, scaleDen);

    pdfWeight *= ratio;
    terms[nameA.str()] *= ratio;
  }

  if ( mother->state[inM].colType() != 0 ) {
    // Find x value and flavour
    double x = getCurrentX(sideM);
    int flav = getCurrentFlav(sideM);
    // Find numerator scale
    double scaleNum = (children.empty())
                    ? hardFacScale(state)
                    : ( (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                       && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                      ? pdfScale : maxscale );
    double scaleDen = (  !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                       && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                    ? clusterIn.pT() : newScale;
    // Multiply PDF ratio
    double ratio = getPDFratio(sideM, false, false, flav, x, scaleNum,
                     flav, x, scaleDen);

    pdfWeight *= ratio;
    terms[nameB.str()] *= ratio;
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the \alpha_s-ratio part of the CKKWL weight of a path.

double DireHistory::weightALPHAS( double as0, AlphaStrong * asFSR,
  AlphaStrong * asISR, int njetMin, int njetMax, bool useEffScale) {

  // For ME state, do nothing.
  if ( !mother ) return 1.;
  // Recurse
  double w = mother->weightALPHAS( as0, asFSR, asISR, njetMin, njetMax,
    useEffScale);
  // Do nothing for empty state
  if (state.size() < 3) return w;

  // If this node has too many jets, no not calculate no-emission probability.
  int njetNow = mergingHooksPtr->getNumberOfClusteringSteps( state) ;
  if (njetNow >= njetMax) return 1.0;

  // Store variables for easy use.
  bool FSR = mother->state[clusterIn.radPos].isFinal();
  int emtID = mother->state[clusterIn.emt1Pos].id();

  // Do not correct alphaS if it is an EW emission.
  if (abs(emtID) == 22 || abs(emtID) == 23 || abs(emtID) == 24) return w;

  if (njetNow < njetMin ) w *= 1.0;
  else {
  // Calculate alpha_s ratio for current state
  if ( asFSR && asISR ) {
    double asScale = pow2( scale );
    if (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
      && mergingHooksPtr->unorderedASscalePrescip() == 1)
      asScale = pow2( clusterIn.pT() );
    // Add regularisation scale to initial state alpha_s.
    if (!FSR) asScale += pow2(mergingHooksPtr->pT0ISR());
    // Directly get argument of running alpha_s from shower plugin.
    asScale = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleAS", asScale);
    //if (useEffectiveScale() ) asScale = pow2(scale); 
    if (useEffScale) asScale = pow2(scale); 

    double alphaSinPS = (FSR) ? (*asFSR).alphaS(asScale)
                              : (*asISR).alphaS(asScale);
    w *= alphaSinPS / as0;
  }
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the \alpha_s-ratio part of the CKKWL weight of a path.

vector<double> DireHistory::weightCouplings() {

  // For ME state, do nothing.
  if ( !mother ) return createvector<double>(1.)(1.)(1.);
  // Recurse
  vector<double> w = mother->weightCouplings();
  // Do nothing for empty state
  if (state.size() < 3) return w;

  // Get local copies of input system
  int rad     = clusterIn.radPos;
  int rec     = clusterIn.recPos;
  int emt     = clusterIn.emt1Pos;
  string name = clusterIn.name();

  if (!(fsr && isr)) return createvector<double>(1.)(1.)(1.);
  bool isFSR = fsr->isTimelike(mother->state, rad, emt, rec, "");
  bool isISR = isr->isSpacelike(mother->state, rad, emt, rec, "");
  double t      = pow2(scale);
  double renormMultFacFSR
    = mergingHooksPtr->settingsPtr->parm("TimeShower:renormMultFac");
  double renormMultFacISR
    = mergingHooksPtr->settingsPtr->parm("SpaceShower:renormMultFac");
  if      (isFSR) t *= renormMultFacFSR;
  else if (isISR) t *= renormMultFacISR;

  double couplingOld(1.), couplingNew(1.);
  if (isFSR) couplingOld = fsr->getCoupling(-1., name);
  if (isISR) couplingOld = isr->getCoupling(-1., name);
  vector<double> variations(createvector<double>(1.)(0.25)(4.));
  for (size_t i=0; i<variations.size(); ++i) {
    if (isFSR) couplingNew = fsr->getCoupling( variations[i]*t, name);
    if (isISR) couplingNew = isr->getCoupling( variations[i]*t, name);
    w[i] *= couplingNew / couplingOld;
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the \alpha_s-ratio part of the CKKWL weight of a path.

vector<double> DireHistory::weightCouplingsDenominator() {

  // For ME state, do nothing.
  if ( !mother ) return createvector<double>(1.)(1.)(1.);
  // Recurse
  vector<double> w = mother->weightCouplingsDenominator();
  // Do nothing for empty state
  if (state.size() < 3) return w;
  // Get local copies of input system
  if (!(fsr && isr)) return createvector<double>(1.)(1.)(1.);
  for (size_t i=0; i<w.size(); ++i) {
    w[i] *= clusterCoupl*2.*M_PI;
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the \alpha_em-ratio part of the CKKWL weight of a path.

double DireHistory::weightALPHAEM( double aem0, AlphaEM * aemFSR,
  AlphaEM * aemISR, int njetMin, int njetMax, bool useEffScale) {

  // For ME state, do nothing.
  if ( !mother ) return 1.;
  // Recurse
  double w = mother->weightALPHAEM( aem0, aemFSR, aemISR, njetMin, njetMax,
    useEffScale);
  // Do nothing for empty state
  if (state.size() < 3) return w;

  // If this node has too many jets, no not calculate no-emission probability.
  int njetNow = mergingHooksPtr->getNumberOfClusteringSteps( state) ;
  if (njetNow >= njetMax) return 1.0;

  // Store variables for easy use.
  bool FSR = mother->state[clusterIn.radPos].isFinal();
  int emtID = mother->state[clusterIn.emt1Pos].id();

  // Do not correct alpha EM if it not an EW emission.
  if (!(abs(emtID) == 22 || abs(emtID) == 23 || abs(emtID) == 24)) return w;

  if (njetNow < njetMin ) w *= 1.0;
  else {
  // Calculate alpha_s ratio for current state
  if ( aemFSR && aemISR ) {
    double aemScale = pow2( scale );
    if (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
      && mergingHooksPtr->unorderedASscalePrescip() == 1)
      aemScale = pow2( clusterIn.pT() );
    // Add regularisation scale to initial state alpha_em.
    if (!FSR) aemScale += pow2(mergingHooksPtr->pT0ISR());
    // Directly get argument of running alpha_em from shower plugin.
    aemScale = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleEM", aemScale);
    //if (useEffectiveScale() ) aemScale = pow2(scale); 
    if (useEffScale) aemScale = pow2(scale); 

    double alphaEMinPS = (FSR) ? (*aemFSR).alphaEM(aemScale)
                               : (*aemISR).alphaEM(aemScale);
    w *= alphaEMinPS / aem0;
  }
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the PDF-ratio part of the CKKWL weight of a path.

double DireHistory::weightPDFs( double maxscale, double pdfScale,
  int njetMin, int njetMax ) {

  // Use correct scale
  double newScale = scale;
  int njetNow = mergingHooksPtr->getNumberOfClusteringSteps( state);

  // For ME state, just multiply by PDF ratios
  if ( !mother ) {

    // If this node has too many jets, no not calculate PDF ratio.
    if (njetMax > -1 && njetNow > njetMax) return 1.0;

    double wt = 1.;
    int sideRad = (state[3].pz() > 0) ? 1 :-1;
    int sideRec = (state[4].pz() > 0) ? 1 :-1;

    // Calculate PDF first leg
    if (state[3].colType() != 0) {
      // Find x value and flavour
      double x = 2.*state[3].e() / state[0].e();
      int flav = state[3].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // For initial parton, multiply by PDF ratio
      if (njetMin > -1 && njetNow >= njetMin ) wt *= getPDFratio(sideRad, 
        false, false, flav, x, scaleNum, flav, x, scaleDen);
      else if (njetMin == -1)                  wt *= getPDFratio(sideRad,
        false, false, flav, x, scaleNum, flav, x, scaleDen);
    }

    // Calculate PDF ratio for second leg
    if (state[4].colType() != 0) {
      // Find x value and flavour
      double x = 2.*state[4].e() / state[0].e();
      int flav = state[4].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // For initial parton, multiply with PDF ratio
      //if (njetNow >= njetMin )
      //wt *= getPDFratio(sideRec, false, false, flav, x, scaleNum, flav, x,
      //        scaleDen);
      if (njetMin > -1 && njetNow >= njetMin ) wt *= getPDFratio(sideRec, 
        false, false, flav, x, scaleNum, flav, x, scaleDen);
      else if (njetMin == -1)                  wt *= getPDFratio(sideRec,
        false, false, flav, x, scaleNum, flav, x, scaleDen);
    }

    return wt;
  }

  // Remember new PDF scale n case true scale should be used for un-ordered
  // splittings.
  double newPDFscale = newScale;
  if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
    &&  mergingHooksPtr->unorderedPDFscalePrescip() == 1)
    newPDFscale = clusterIn.pT();

  // Recurse
  double w = mother->weightPDFs( newScale, newPDFscale, njetMin, njetMax);

  // check if this makes sense!!
  //int njetNow = mergingHooksPtr->getNumberOfClusteringSteps(state) ;
  if (njetNow > -1 && njetNow >= njetMax) return 1.0;

  // Do nothing for empty state
  if (state.size() < 3) return w;

  // Calculate pdf ratios: Get both sides of event
  int inP = 3;
  int inM = 4;
  int sideP = (mother->state[inP].pz() > 0) ? 1 :-1;
  int sideM = (mother->state[inM].pz() > 0) ? 1 :-1;

  if ( mother->state[inP].colType() != 0 ) {
    // Find x value and flavour
    double x = getCurrentX(sideP);
    int flav = getCurrentFlav(sideP);
    // Find numerator scale
    double scaleNum = (children.empty())
                ? hardFacScale(state)
                  : ( (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                    && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                  ? pdfScale : maxscale );
    double scaleDen = (  !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                ? clusterIn.pT() : newScale;
    double xDen = (njetMax > -1 && njetNow == njetMax)
                ? mother->getCurrentX(sideP) : x;
    int flavDen = (njetMax > -1 && njetNow == njetMax)
                ? mother->getCurrentFlav(sideP) : flav;
    double sDen = (njetMax > -1 && njetNow == njetMax)
                ? mergingHooksPtr->muFinME() : scaleDen;
    //double ratio = getPDFratio(sideP, false, false, flav, x, scaleNum,
    //                 flavDen, xDen, sDen);
    //if (njetNow >= njetMin )
    //w *= ratio;
    if (njetMin > -1 && njetNow >= njetMin ) w *= getPDFratio(sideP, 
      false, false, flav, x, scaleNum, flavDen, xDen, sDen);
    else if (njetMin == -1)                  w *= getPDFratio(sideP,
      false, false, flav, x, scaleNum, flavDen, xDen, sDen);
  }

  if ( mother->state[inM].colType() != 0 ) {
    // Find x value and flavour
    double x = getCurrentX(sideM);
    int flav = getCurrentFlav(sideM);
    // Find numerator scale
    double scaleNum = (children.empty())
                ? hardFacScale(state)
                  : ( (!mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                    && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                  ? pdfScale : maxscale );
    double scaleDen = (  !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
                && mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                ? clusterIn.pT() : newScale;
    double xDen = (njetMax > -1 && njetNow == njetMax)
                ? mother->getCurrentX(sideM) : x;
    int flavDen = (njetMax > -1 && njetNow == njetMax)
                ? mother->getCurrentFlav(sideM) : flav;
    double sDen = (njetMax > -1 && njetNow == njetMax)
                ? mergingHooksPtr->muFinME() : scaleDen;
    //double ratio = getPDFratio(sideM, false, false, flav, x, scaleNum,
    //                 flavDen, xDen, sDen);
    //if (njetNow >= njetMin )
    //w *= ratio;
    if (njetMin > -1 && njetNow >= njetMin ) w *= getPDFratio(sideM, 
      false, false, flav, x, scaleNum, flavDen, xDen, sDen);
    else if (njetMin == -1)                  w *= getPDFratio(sideM,
      false, false, flav, x, scaleNum, flavDen, xDen, sDen);
  }

  // Done
  return w;
}

//--------------------------------------------------------------------------

// Function to return the no-emission probability part of the CKKWL weight.

double DireHistory::weightEmissions( PartonLevel* trial, int type,
  int njetMin, int njetMax, double maxscale ) {

  // Use correct scale
  double newScale = scale;

  // No no-MPI-probability if MPI turned off.
  if (type == -1 && !mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI"))
    return 1.;

  // No no-emission-probability if showers turned off.
  if (type > 0 && !(mergingHooksPtr->settingsPtr->flag("PartonLevel:FSR")
    && mergingHooksPtr->settingsPtr->flag("PartonLevel:ISR")))
    return 1.;

  if ( !mother ) return 1.0;
  // Recurse
  double w = mother->weightEmissions(trial,type,njetMin,njetMax,newScale);
  // Do nothing for empty state
  if (state.size() < 3) return 1.0;
  // If up to now, trial shower was not successful, return zero
  if ( w < 1e-12 ) return 0.0;
  // If this node has too many jets, no not calculate no-emission probability.
  int njetNow = mergingHooksPtr->getNumberOfClusteringSteps( state) ;

  if (njetMax > -1 && njetNow >= njetMax) return 1.0;
  if (njetMin > -1 && njetNow < njetMin ) w *= 1.0;
  // Do trial shower on current state, return zero if not successful
  else w *= doTrialShower(trial, type, maxscale).front();

  if ( abs(w) < 1e-12 ) return 0.0;
  // Done
  return w;

}

//--------------------------------------------------------------------------

// Function to return the no-emission probability part of the CKKWL weight.

vector<double> DireHistory::weightEmissionsVec( PartonLevel* trial, int type,
  int njetMin, int njetMax, double maxscale ) {

  // Use correct scale
  double newScale = scale;

  // No no-MPI-probability if MPI turned off.
  if (type == -1 && !mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI"))
    return createvector<double>(1.)(1.)(1.);

  // No no-emission-probability if showers turned off.
  if (type > 0 && !(mergingHooksPtr->settingsPtr->flag("PartonLevel:FSR")
    && mergingHooksPtr->settingsPtr->flag("PartonLevel:ISR")))
    return createvector<double>(1.)(1.)(1.);

  // Done if at the highest multiplicity node.
  if (!mother) return createvector<double>(1.)(1.)(1.);

  // Recurse
  vector<double> w = mother->weightEmissionsVec(trial, type, njetMin, njetMax,
    newScale);
  // Do nothing for empty state
  if (state.size() < 3) return createvector<double>(1.)(1.)(1.);
  // If up to now, trial shower was not successful, return zero
  bool nonZero = false;
  for (size_t i=0; i < w.size(); ++i) if (abs(w[i]) > 1e-12) nonZero = true;
  if (!nonZero) return createvector<double>(0.)(0.)(0.);
  // If this node has too many jets, no not calculate no-emission probability.
  int njetNow = mergingHooksPtr->getNumberOfClusteringSteps(state);
  if (njetMax > -1 && njetNow >= njetMax)
    return createvector<double>(1.)(1.)(1.);

  // Do nothing for too few jets.
  if (njetMin > -1 && njetNow < njetMin ) ;
  // Do trial shower on current state, return zero if not successful
  else {
    vector<double> wem = doTrialShower(trial, type, maxscale);
    for (size_t i=0; i < w.size(); ++i) w[i] *= wem[i];
  }

  nonZero = false;
  for (size_t i=0; i < w.size(); ++i) if (abs(w[i]) > 1e-12) nonZero = true;
  if (!nonZero) return createvector<double>(0.)(0.)(0.);

  // Done
  return w;

}

//--------------------------------------------------------------------------

// Function to generate the O(\alpha_s)-term of the \alpha_s-ratios
// appearing in the CKKWL-weight.

double DireHistory::weightAlphasExpanded( int order, double as0, double muR,
  AlphaStrong * asFSR, AlphaStrong * asISR, bool useEffScale,
  map<string,double>& terms) {

  // Use correct scale
  double newScale = scale;
  // Done
  if ( !mother ) return 0.;
  // Recurse
  double w = mother->weightAlphasExpanded( order, as0, muR, asFSR, asISR,
    useEffScale, terms);

  stringstream s1;
  s1 << "alphasratio_" << depth + 1 << "_1";
  if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
  stringstream s2;
  s2 << "alphasratio_" << depth + 1 << "_2";
  if (terms.find(s2.str())==terms.end()) terms[s2.str()] = 0.;

  // Get information about coupling.
  int radType = mother->state[clusterIn.radPos].colType();
  int emtType = mother->state[clusterIn.emt1Pos].colType();
  bool isQCD = (radType != 0 && emtType != 0);
  //bool isQED = emtType == 0;
  //pair<int,double> coup = getCoupling(mother->state, clusterIn.radPos,
  //  clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name());
  //if (coup.first > 0) isQCD = isQED = false;

  // Calculate alpha_s ratio for current state.
  if ( asFSR && asISR && isQCD) {

    double asScale = pow2( newScale );
    if ( !mergingHooksPtr->settingsPtr->flag("Dire:doMOPS")
      &&  mergingHooksPtr->unorderedASscalePrescip() == 1)
      asScale = pow2( clusterIn.pT() );
    // Add regularisation scale to initial state alpha_s.
    bool FSR = mother->state[clusterIn.radPos].isFinal();
    if (!FSR) asScale += pow2(mergingHooksPtr->pT0ISR());
    // Directly get argument of running alpha_s from shower plugin.
    asScale = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleAS", asScale);
    if (mergingHooksPtr->settingsPtr->flag("Dire:doMOPS"))
      asScale = pow2(newScale);
    //if (useEffectiveScale() ) asScale = pow2(scale); 
    if (useEffScale) asScale = pow2(scale); 

    double b = 1.;

    if ( mother->state[clusterIn.radPos].isFinal()
      && mother->state[clusterIn.recPos].isFinal()) b = 4.;

    // Find summand beta_0 / 2 * ln(muR^2/t_i) due to as expansion.
    //double NF = 4.;
    //double BETA0 = 11. - 2./3.* NF;
    double NF
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->getNF(asScale);
    double BETA0
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->betaQCD0(NF);
    double BETA1
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->betaQCD1(NF);

    // For fixed \alpha_s in matrix element
    if (order == 1 || order == 12) {
      double exp = as0 / (4.*M_PI) * BETA0 * log( (muR*muR) / (b*asScale) );
      w += exp;
      terms[s1.str()] += exp;
    }
    if (order == 2 || order == 12) {
      double exp
        = pow2(as0 / (4.*M_PI)) * BETA1 * log( (muR*muR) / (b*asScale));
        // not included because it would anyway cancel in the final result!
        //+ pow2(as0 / (4.*M_PI) * BETA0 * log( (muR*muR) / (b*asScale)));
      w += exp;
      terms[s2.str()] += exp;
    }

    /*if ( ( showerType==-1
        && mergingHooksPtr->settingsPtr->flag("SpaceShower:alphaSuseCMW"))
      || ( showerType==1
       && mergingHooksPtr->settingsPtr->flag("TimeShower::alphaSuseCMW")) ) {
      double CA = 3.;
      double Kg = CA*(67/18-M_PI*M_PI/6)-5/9*NF;
      w += as0/ (2.*M_PI) * Kg;
    }*/
  }

  // Done
  return w;

}

//--------------------------------------------------------------------------

// Function to generate the O(\alpha_s)-term of the PDF-ratios
// appearing in the CKKWL-weight.

double DireHistory::weightFirstPDFs( double as0, double maxscale,
  double pdfScale, Rndm* rndmPtr,
  map<string,double>& terms) {

  // Use correct scale
  double newScale = scale;

  if ( !mother ) {

    double wt = 0.;

    // Calculate PDF first leg
    if (state[3].colType() != 0) {
      // Find x value and flavour
      double x        = 2.*state[3].e() / state[0].e();
      int flav        = state[3].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // Monte Carlo integrand.
      wt += monteCarloPDFratios(flav, x, scaleNum, scaleDen,
                          mergingHooksPtr->muFinME(), as0, rndmPtr);
    }
    // Calculate PDF ratio for second leg
    if (state[4].colType() != 0) {
      // Find x value and flavour
      double x        = 2.*state[4].e() / state[0].e();
      int flav        = state[4].id();
      // Find numerator/denominator scale
      double scaleNum = (children.empty()) ? hardFacScale(state) : maxscale;
      double scaleDen = mergingHooksPtr->muFinME();
      // Monte Carlo integrand.
      wt += monteCarloPDFratios(flav, x, scaleNum, scaleDen,
                         mergingHooksPtr->muFinME(), as0, rndmPtr);
    }

    // Done
    return wt;
  }

  // Remember new PDF scale n case true scale should be used for un-ordered
  // splittings.
  double newPDFscale = newScale;
  if (mergingHooksPtr->unorderedPDFscalePrescip() == 1)
    newPDFscale      = clusterIn.pT();

  // Recurse
  double w = mother->weightFirstPDFs( as0, newScale, newPDFscale, rndmPtr,
    terms);

  // Calculate pdf ratios: Get both sides of event
  int inP   = 3;
  int inM   = 4;
  int sideP = (mother->state[inP].pz() > 0) ? 1 :-1;
  int sideM = (mother->state[inM].pz() > 0) ? 1 :-1;

  if ( mother->state[inP].colType() != 0 ) {
    // Find x value and flavour
    double x        = getCurrentX(sideP);
    int flav        = getCurrentFlav(sideP);
    // Find numerator / denominator scales
    double scaleNum = (children.empty())
                    ? hardFacScale(state)
                    : ( (mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                      ? pdfScale : maxscale );
    double scaleDen = (mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                    ? clusterIn.pT() : newScale;
    // Monte Carlo integrand.
    w += monteCarloPDFratios(flav, x, scaleNum, scaleDen,
                        mergingHooksPtr->muFinME(), as0, rndmPtr);
  }

  if ( mother->state[inM].colType() != 0 ) {
    // Find x value and flavour
    double x        = getCurrentX(sideM);
    int flav        = getCurrentFlav(sideM);
    // Find numerator / denominator scales
    double scaleNum = (children.empty())
                    ? hardFacScale(state)
                    : ( (mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                      ? pdfScale : maxscale );
    double scaleDen = (mergingHooksPtr->unorderedPDFscalePrescip() == 1)
                    ? clusterIn.pT() : newScale;
    // Monte Carlo integrand.
    w += monteCarloPDFratios(flav, x, scaleNum, scaleDen,
                        mergingHooksPtr->muFinME(), as0, rndmPtr);
  }

  // Done
  return w;

}

//--------------------------------------------------------------------------

// Function to generate the expansion of the PDF terms
// appearing in the CKKWL-weight.

double DireHistory::weightPDFExpanded( int order, double as0,
  double maxscale, map<string,double>& terms) {

  double muf2 = pow2(mergingHooksPtr->muFinME());
  double mur2 = pow2(mergingHooksPtr->muRinME());
  double t    = children.empty() ? hardFacScale(state) : maxscale;

  stringstream nameA1; nameA1 << "pdfratioA_" << depth << "_1";
  stringstream nameB1; nameB1 << "pdfratioB_" << depth << "_1";
  stringstream nameA2; nameA2 << "pdfratioA_" << depth << "_2";
  stringstream nameB2; nameB2 << "pdfratioB_" << depth << "_2";
  if (terms.find(nameA1.str())==terms.end()) terms[nameA1.str()] = 0.;
  if (terms.find(nameB1.str())==terms.end()) terms[nameB1.str()] = 0.;
  if (terms.find(nameA2.str())==terms.end()) terms[nameA2.str()] = 0.;
  if (terms.find(nameB2.str())==terms.end()) terms[nameB2.str()] = 0.;

  if ( !mother ) {

    double w = 0.;
    if (state[3].colType() != 0) {
    // Find x value and flavour
    double xA = 2.*state[3].e() / state[0].e();
    int flavA = state[3].id();
    double pdfDen = max(1e-10,beamA.xfHard( flavA, xA, muf2));
    vector<double> pdfExp = pdfExpansion(order, 1, flavA, xA, t, muf2, mur2);
    w += pdfExp[1] / pdfDen;
    //stringstream s1; s1 << nameA1.str();
    //if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
    if (order == 1 || order == 12) terms[nameA1.str()] = pdfExp[1] / pdfDen;
    if (order == 2 || order == 12) terms[nameA2.str()] = pdfExp[2] / pdfDen;
    }

    // Find x value and flavour for second beam
    if (state[4].colType() != 0) {
    double xB = 2.*state[4].e() / state[0].e();
    int flavB = state[4].id();
    double pdfDen = max(1e-10,beamB.xfHard( flavB, xB, muf2));
    vector<double> pdfExp = pdfExpansion(order,-1, flavB, xB, t, muf2, mur2);
    w += pdfExp[1] / pdfDen;
    //stringstream s1; s1 << nameB1.str();
    //if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
    //terms[s1.str()] = pdfExp / pdfDen;
    if (order == 1 || order == 12) terms[nameB1.str()] = pdfExp[1] / pdfDen;
    if (order == 2 || order == 12) terms[nameB2.str()] = pdfExp[2] / pdfDen;
    }
    // Done
    return w;
  }

  // Recurse
  double w = mother->weightPDFExpanded( order, as0, scale, terms);

  // Calculate pdf ratios: Get both sides of event
  int inP   = 3;
  int inM   = 4;
  int sideP = (mother->state[inP].pz() > 0) ? 1 :-1;
  int sideM = (mother->state[inM].pz() > 0) ? 1 :-1;

  if ( mother->state[inP].colType() != 0 ) {
    // Find x value and flavour
    double x        = getCurrentX(sideP);
    int flav        = getCurrentFlav(sideP);
    double pdfDen = max(1e-10,beamA.xfHard( flav, x, muf2));
    vector<double> pdfExp = pdfExpansion(order,1, flav, x, t, muf2, mur2);
    w += pdfExp[1] / pdfDen;
    //stringstream s1; s1 << nameA1.str();
    //if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
    //terms[s1.str()] = pdfExp / pdfDen;
    if (order == 1 || order == 12) terms[nameA1.str()] = pdfExp[1] / pdfDen;
    if (order == 2 || order == 12) terms[nameA2.str()] = pdfExp[2] / pdfDen;
  }

  if ( mother->state[inM].colType() != 0 ) {
    // Find x value and flavour
    double x        = getCurrentX(sideM);
    int flav        = getCurrentFlav(sideM);
    double pdfDen = max(1e-10,beamB.xfHard( flav, x, muf2));
    vector<double> pdfExp = pdfExpansion(order,-1, flav, x, t, muf2, mur2);
    w += pdfExp[1] / pdfDen;
    //stringstream s1; s1 << nameB1.str();
    //if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
    //terms[s1.str()] = pdfExp / pdfDen;
    if (order == 1 || order == 12) terms[nameB1.str()] = pdfExp[1] / pdfDen;
    if (order == 2 || order == 12) terms[nameB2.str()] = pdfExp[2] / pdfDen;
  }

  // Done
  return w;

}

//--------------------------------------------------------------------------

vector<double> DireHistory::pdfExpansion(int order, int side, int flav, double x,
  double t, double muf, double mur) {

  const apfel::Grid g{{apfel::SubGrid{80,1e-5,3},
    apfel::SubGrid{50,1e-1,3}, apfel::SubGrid{40,8e-1,3}}};

  // Return 0th, 1st and 2nd-order terms of expansion.
  vector<double> ret;
  ret.push_back(1.);
  ret.push_back(0.);
  ret.push_back(0.);

  return ret;

}

//--------------------------------------------------------------------------

// Function to generate the expansion of the no-emission
// probabilities appearing in the CKKWL-weight.

double DireHistory::weightEmissionsExpanded(int order, PartonLevel* trial,
  double as0, double maxscale, AlphaStrong * asFSR, AlphaStrong * asISR,
  bool fixpdf, bool fixas, map<string,double>& terms) {

  // Use correct scale
  double newScale = scale;
  if ( !mother ) return 0.0;
  // Recurse
  double w = mother->weightEmissionsExpanded(order,trial, as0, newScale,
    asFSR, asISR, fixpdf, fixas, terms);

  stringstream s1;
  s1 << "delta_" << depth << "_1";
  if (terms.find(s1.str())==terms.end()) terms[s1.str()] = 0.;
  stringstream s2;
  s2 << "delta_" << depth << "_2";
  if (terms.find(s2.str())==terms.end()) terms[s2.str()] = 0.;

  // Do nothing for empty state
  if (state.size() < 3) return 0.0;
  // Generate true average.
  double nWeight1 = 0.;
  double nWeight2 = 0.;
  for(int i=0; i < NTRIAL; ++i) {
    // Get number of emissions
    vector<double> unresolvedEmissionTerm = countEmissions(trial,
      maxscale, newScale, 2, as0, asFSR, asISR, 3, fixpdf, fixas, order);
    nWeight1 += (order == 1 || order == 12) ? unresolvedEmissionTerm[1] : 0.;
    nWeight2 += (order == 2 || order == 12) ? unresolvedEmissionTerm[2] : 0.;
  }

  if (order == 1 || order == 12) {
    w += nWeight1/double(NTRIAL);
    terms[s1.str()] += nWeight1/double(NTRIAL);
  }

  if (order == 2 || order == 12) {
    w += nWeight2/double(NTRIAL);
    terms[s2.str()] += nWeight2/double(NTRIAL);
  }

  // Done
  return w;

}

//--------------------------------------------------------------------------

double DireHistory::weightHardState(const Event& event, double asME,
  AlphaStrong * as, double aemME, AlphaEM * aem) {

  double wt = 1.;
  
  if (mergingHooksPtr->resetHardQRen()) {
    // Get power of QCD/QED couplings.
    //map<string,int>::iterator it = couplingPowCount.find("qcd");
    //map<int,int>::iterator it = couplingPowCount.find(QCD);
    //int nqcd = (it == couplingPowCount.end()) ? 0 : it->second;
    int nqcd = couplingPowCount[QCD];
    //it = couplingPowCount.find("qed");
    //it = couplingPowCount.find(QED);
    //int nqed = (it == couplingPowCount.end()) ? 0 : it->second;
    int nqed = couplingPowCount[QED];
    // Reweight with running coupling factors.
    double newQ2Ren = pow2(hardRenScale(event));
    wt *= pow(  (*as).alphaS(newQ2Ren)  / asME,  nqcd)
        * pow( (*aem).alphaEM(newQ2Ren) / aemME, nqed);
  }

  // Done
  return wt;

}

//--------------------------------------------------------------------------

double DireHistory::weightHardStateExpanded(int order, const Event& event,
  double asME, double muR) {

  double wt = 0.;
  
  if (mergingHooksPtr->resetHardQRen()) {
    // Get power of QCD couplings.
    //map<string,int>::iterator it = couplingPowCount.find("qcd");
    //map<int,int>::iterator it = couplingPowCount.find(QCD);
    //int nqcd = (it == couplingPowCount.end()) ? 0 : it->second;
    int nqcd = couplingPowCount[QCD];
    // Add one running coupling log per one power of alphaS reweighting.
    double asScale = pow2(hardRenScale(event));
    double b = 1.;
    //double NF = 4.;
    //double BETA0 = 11. - 2./3.* NF;
    double NF
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->getNF(asScale);
    double BETA0
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->betaQCD0(NF);
    double BETA1
    = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->betaQCD1(NF);
    for (int i=0; i < nqcd; ++i) {
      double exp = (order==1 || order ==12)
        ? asME / (4.*M_PI) * BETA0 * log( (muR*muR) / (b*asScale) )
        : 0.;
      exp = (order==2 || order ==12)
        ? pow2(asME / (4.*M_PI) * BETA0 * log( (muR*muR) / (b*asScale)))
        + pow2(asME / (4.*M_PI)) * BETA1 * log( (muR*muR) / (b*asScale))
        : 0.;
      wt += exp;
    }
  }

  // Done
  return wt;

}

//--------------------------------------------------------------------------

// Function to return the factorisation scale of the hard process in Pythia.

double DireHistory::hardFacScale(const Event& event) {

  // Declare output scale.
  double hardscale = 0.;
  // If scale should not be reset, done.
  if ( !mergingHooksPtr->resetHardQFac() ) return mergingHooksPtr->muF();

  // For pure QCD dijet events, calculate the hadronic cross section
  // of the hard process at the pT of the dijet system, rather than at fixed
  // arbitrary scale.
  if ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
    || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
    || isQCD2to2(event)) {
    // Find the mT in the hard sub-process.
    vector <double> mT;
    for ( int i=0; i < event.size(); ++i)
      if ( event[i].isFinal() && event[i].colType() != 0 )
        mT.push_back( abs(event[i].mT2()) );
    if ( int(mT.size()) != 2 )
      hardscale = infoPtr->QFac();
    else
      hardscale = sqrt( min( mT[0], mT[1] ) );

  // For DIS, set the hard process scale to Q2.
  } else if ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
           || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0) {
    // Use Q2 as core scale.
    if ( isDIS2to2(event)) {
      int iInEl(0), iOutEl(0);
      for ( int i=0; i < event.size(); ++i )
        if ( event[i].idAbs() == 11 ) {
          if ( event[i].status() == -21 ) iInEl  = i;
          if ( event[i].isFinal() )       iOutEl = i;
        }
      hardscale = sqrt( -(event[iInEl].p()-event[iOutEl].p()).m2Calc() );

    // Use pT2 as core scale.
    } else if (isMassless2to2(event)) {

      // Find the mT in the hard sub-process.
      vector <double> mT;
      for ( int i=0; i < event.size(); ++i)
        if ( event[i].isFinal() && event[i].colType() != 0 )
          mT.push_back( abs(event[i].mT2()) );
      if ( int(mT.size()) != 2 )
        hardscale = infoPtr->QFac();
      else
        hardscale = sqrt( min( mT[0], mT[1] ) );
    
    } else hardscale = mergingHooksPtr->muF();

  } else {
    hardscale = mergingHooksPtr->muF();
  }
  // Done
  return hardscale;
}

//--------------------------------------------------------------------------

// Function to return the factorisation scale of the hard process in Pythia.

double DireHistory::hardRenScale(const Event& event) {
  // Declare output scale.
  double hardscale = 0.;
  // If scale should not be reset, done.
  if ( !mergingHooksPtr->resetHardQRen() ) return mergingHooksPtr->muR();
  // For pure QCD dijet events, calculate the hadronic cross section
  // of the hard process at the pT of the dijet system, rather than at fixed
  // arbitrary scale.
  if ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
       || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
       || isQCD2to2(event)) {
    // Find the mT in the hard sub-process.
    vector <double> mT;
    for ( int i=0; i < event.size(); ++i)
      if ( event[i].isFinal()
        && ( event[i].colType() != 0 || event[i].id() == 22 ) )
        mT.push_back( abs(event[i].mT()) );
    if ( int(mT.size()) != 2 )
      hardscale = infoPtr->QRen();
    else
      hardscale = sqrt( mT[0]*mT[1] );

  // For DIS, set the hard process scale to Q2.
  } else if ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
           || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0) {
    // Use Q2 as core scale.
    if ( isDIS2to2(event)) {
      int iInEl(0), iOutEl(0);
      for ( int i=0; i < state.size(); ++i )
        if ( state[i].idAbs() == 11 ) {
          if ( state[i].status() == -21 ) iInEl  = i;
          if ( state[i].isFinal() )       iOutEl = i;
        }
      hardscale = sqrt( -(state[iInEl].p()-state[iOutEl].p()).m2Calc() );

    // Use pT2 as core scale.
    } else if (isMassless2to2(event)) {

      // Find the mT in the hard sub-process.
      vector <double> mT;
      for ( int i=0; i < event.size(); ++i)
        if ( event[i].isFinal() && event[i].colType() != 0 )
          mT.push_back( abs(event[i].mT2()) );
      if ( int(mT.size()) != 2 )
        hardscale = infoPtr->QFac();
      else
        hardscale = sqrt( min( mT[0], mT[1] ) );

    } else hardscale = mergingHooksPtr->muF();

  } else {
    hardscale = mergingHooksPtr->muR();
  }
  // Done
  return hardscale;
}

//--------------------------------------------------------------------------

// Function to return the factorisation scale of the hard process in Pythia.

double DireHistory::hardStartScale(const Event& event) {

  // Starting scale of initial state showers.
  map<string,double> stateVarsISR;
  if (isr) stateVarsISR
    = isr->getStateVariables(event,0,0,0,"");

  // Starting scale of final state showers.
  map<string,double> stateVarsFSR;
  if (fsr) stateVarsFSR
    = fsr->getStateVariables(event,0,0,0,"");

  // Find maximal scale.
  double hardscale = 0.;
  for ( map<string,double>::iterator it = stateVarsISR.begin();
    it != stateVarsISR.end(); ++it )
    if ( it->first.find("scalePDF") != string::npos )
      hardscale = max( hardscale, sqrt(it->second) );
  for ( map<string,double>::iterator it = stateVarsFSR.begin();
    it != stateVarsFSR.end(); ++it )
    if ( it->first.find("scalePDF") != string::npos )
      hardscale = max( hardscale, sqrt(it->second) );

  // Done
  return hardscale;
}

//--------------------------------------------------------------------------

// Perform a trial shower using the \a pythia object between
// maxscale down to this scale and return the corresponding Sudakov
// form factor.
// IN  trialShower : Shower object used as trial shower
//     double     : Maximum scale for trial shower branching
// OUT  0.0       : trial shower emission outside allowed pT range
//      1.0       : trial shower successful (any emission was below
//                  the minimal scale )

vector<double> DireHistory::doTrialShower( PartonLevel* trial, int type,
  double maxscaleIn, double minscaleIn) {

  vector <double> wtv(createvector<double>(1.)(1.)(1.));

  // Do nothing if evolution is switched off.
  if ( (type == -1 && !mergingHooksPtr->settingsPtr->flag("PartonLevel:MPI"))
    || (type ==  1 && !mergingHooksPtr->settingsPtr->flag("PartonLevel:FSR")
                   && !mergingHooksPtr->settingsPtr->flag("PartonLevel:ISR")))
    return wtv;

  // Copy state to local process
  Event process        = state;
  // Set starting scale.
  double startingScale = maxscaleIn;
  // Careful when setting shower starting scale for pure QCD and prompt
  // photon case.
  if ( mergingHooksPtr->getNumberOfClusteringSteps(process) == 0
    && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
         || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
         || isQCD2to2(state) ) )
      startingScale = min( startingScale, hardFacScale(process) );

  // For DIS, set starting scale to Q2 or pT2.
  if ( mergingHooksPtr->getNumberOfClusteringSteps(process) == 0
    && ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
      || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0))
      //startingScale = min( startingScale, hardFacScale(process) );
      startingScale = hardFacScale(process);

  if ( mergingHooksPtr->getNumberOfClusteringSteps(process) == 0 )
    startingScale = hardStartScale(process);

  // Set output.
  //bool doVeto          = false;
  double wt            = 1.;
  //vector <double> wtv(createvector<double>(1.)(1.)(1.));
  int nFSRtry(0), nISRtry(0), nMPItry(0);

  while (true) {

    // Reset trialShower object
    psweights->reset();
    trial->resetTrial();
    // Construct event to be showered
    Event event(15);
    event.init("(hard process-modified)", particleDataPtr);
    event.initColTag(process.lastColTag()+1000);
    //event.clear();

    // Reset process scale so that shower starting scale is correctly set.
    process.scale(startingScale);

    // Get pT before reclustering
    double minScale = (minscaleIn > 0.) ? minscaleIn : scale;

    mergingHooksPtr->setShowerStoppingScale(minScale);

    // Give up generating no-MPI probability if ISR completely dominates.
    if (type == -1 && nFSRtry+nISRtry > 500) { break;}

    // If the maximal scale and the minimal scale coincide (as would
    // be the case for the corrected scales of unordered histories),
    // do not generate Sudakov
    if (minScale >= startingScale) break;

    // Find z and pT values at which the current state was formed, to
    // ensure that the showers can order the next emission correctly in
    // rapidity, if required.
    // NOT CORRECTLY SET FOR HIGHEST MULTIPLICITY STATE!
    double z = ( mergingHooksPtr->getNumberOfClusteringSteps(state) == 0
               || !mother )
             ? 0.5
             : mother->getCurrentZ(clusterIn.radPos,clusterIn.recPos,
                 clusterIn.emt1Pos, clusterIn.flavRadBef);
    // Store z and pT values at which the current state was formed.
    infoPtr->zNowISR(z);
    infoPtr->pT2NowISR(pow(startingScale,2));
    infoPtr->hasHistory(true);

    // Perform trial shower emission
    trial->next(process,event);
    // Get trial shower pT.
    double pTtrial   = trial->pTLastInShower();
    int typeTrial    = trial->typeLastInShower();

    if      (typeTrial == 1) nMPItry++;
    else if (typeTrial == 2) nISRtry++;
    else                     nFSRtry++;

    // Clear parton systems.
    trial->resetTrial();

    double t = (pTtrial <= 0.) ? pow2(minScale) : pow2(pTtrial);

    pair<double,double> wtShower = psweights->getWeight(t);
    pair<double,double> wt_isr_1 = psweights->getWeight(t, "Variations:muRisrDown");
    pair<double,double> wt_isr_2 = psweights->getWeight(t, "Variations:muRisrUp");
    pair<double,double> wt_fsr_1 = psweights->getWeight(t, "Variations:muRfsrDown");
    pair<double,double> wt_fsr_2 = psweights->getWeight(t, "Variations:muRfsrUp");

    double enhancement = 1.; 
    if ( pTtrial > minScale) enhancement
      = psweights->getTrialEnhancement( pow2(pTtrial));
    psweights->reset();
    if (pTtrial>0.) psweights->init();
    psweights->clearTrialEnhancements();

    //// Get veto (merging) scale value
    //double vetoScale  = (mother) ? 0. : mergingHooksPtr->tms();
    //// Get merging scale in current event
    //double tnow = mergingHooksPtr->tmsNow( event );

    // Done if evolution scale has fallen below minimum
    if ( pTtrial < minScale ) {
      wt     *= wtShower.second;
      wtv[0] *= wtShower.second;
      wtv[1] *= wt_isr_1.second*wt_fsr_1.second;
      wtv[2] *= wt_isr_2.second*wt_fsr_2.second;
      break;
    }

    // Reset starting scale.
    startingScale = pTtrial;

    //// Continue if this state is below the veto scale
    //if ( tnow < vetoScale && vetoScale > 0. ) continue;

    // Retry if the trial emission was not allowed.
    if ( mergingHooksPtr->canVetoTrialEmission()
      && mergingHooksPtr->doVetoTrialEmission( process, event) ) continue;

    int iRecAft = event.size() - 1;
    int iEmt    = event.size() - 2;
    int iRadAft = event.size() - 3;
    if ( (event[iRecAft].status() != 52 && event[iRecAft].status() != -53) ||
         event[iEmt].status() != 51 || event[iRadAft].status() != 51)
      iRecAft = iEmt = iRadAft = -1;
    for (int i = event.size() - 1; i > 0; i--) {
      if      (iRadAft == -1 && event[i].status() == -41) iRadAft = i;
      else if (iEmt    == -1 && event[i].status() ==  43) iEmt    = i;
      else if (iRecAft == -1 && event[i].status() == -42) iRecAft = i;
      if (iRadAft != -1 && iEmt != -1 && iRecAft != -1) break;
    }

    // Check if the splitting occured in a small window around a flavour
    // threshold.
    bool onCthreshold(false), onBthreshold(false);
    if ( iEmt > 0 && iEmt < event.size()
      && (process[3].colType() != 0 || process[4].colType() != 0)) {
      bool usePDFalphas
        = mergingHooksPtr->settingsPtr->flag("ShowerPDF:usePDFalphas");
      BeamParticle* beam = (particleDataPtr->isHadron(beamA.id())) ? &beamA
                         : (particleDataPtr->isHadron(beamB.id())) ? &beamB
                                                        : NULL;
      double m2cPhys     = (usePDFalphas) ? pow2(max(0.,beam->mQuarkPDF(4)))
                         : mergingHooksPtr->AlphaS_ISR()->muThres2(4);
      double m2bPhys     = (usePDFalphas) ? pow2(max(0.,beam->mQuarkPDF(5)))
                         : mergingHooksPtr->AlphaS_ISR()->muThres2(5);
      if ( event[iEmt].idAbs() == 4 && minScale < sqrt(m2cPhys)
        && pTtrial > (1. - MCWINDOW)*sqrt(m2cPhys)
        && pTtrial < (1. + MCWINDOW)*sqrt(m2cPhys)) onCthreshold = true;
      if ( event[iEmt].idAbs() == 5 && minScale < sqrt(m2bPhys)
        && pTtrial > (1. - MBWINDOW)*sqrt(m2bPhys)
        && pTtrial < (1. + MBWINDOW)*sqrt(m2bPhys)) onBthreshold = true;
    }

    // Only consider allowed emissions for veto:
    // Only allow MPI for MPI no-emission probability.
    if ( type == -1 && typeTrial != 1 ) { 
      // If an initial-state splitting occured because of a flavour threshold,
      // then the showers will always win competition against MPI, meaning that
      // no MPI emission will be produced, i.e. the no-MPI-probability = 1
      if (onCthreshold || onBthreshold) { break; }
      continue;
    }
    // Only allow ISR or FSR for radiative no-emission probability.
    if ( type ==  1 && !(typeTrial == 2 || typeTrial >= 3) ) continue;

    if (pTtrial > minScale) {
      wt     *= wtShower.first*wtShower.second * (1.-1./enhancement);
      wtv[0] *= wtShower.first*wtShower.second * (1.-1./enhancement);
      wtv[1] *= wt_isr_1.first*wt_isr_1.second*wt_fsr_1.first*wt_fsr_1.second
                *(1.-1./enhancement);
      wtv[2] *= wt_isr_2.first*wt_isr_2.second*wt_fsr_2.first*wt_fsr_2.second
                *(1.-1./enhancement);
    }
    if (wt == 0.) break;

    if (pTtrial > minScale) continue;

    // For 2 -> 2 pure QCD state, do not allow multiparton interactions
    // above the kinematical pT of the 2 -> 2 state.
    if ( type == -1
      && typeTrial == 1
      && mergingHooksPtr->getNumberOfClusteringSteps(process) == 0
      && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
        || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
           || isQCD2to2(state))
      && pTtrial > hardFacScale(process) )
      return createvector<double>(0.)(0.)(0.);

    // Done
    break;

  }

  // Reset trialShower object
  psweights->reset();
  trial->resetTrial();

  // Done
  return wtv;

}

//--------------------------------------------------------------------------

// Assume we have a vector of i elements containing indices into
// another vector with N elements. Update the indices so that all
// unique combinations (starting from 0,1,2,3, ...) are
// covered. Return false when all combinations have been ehausted.

bool DireHistory::updateind(vector<int> & ind, int i, int N) {
  if ( i < 0 ) return false;
  if ( ++ind[i] < N ) return true;
  if ( !updateind(ind, i - 1, N - 1) ) return false;
  ind[i] = ind[i - 1] + 1;
  return true;
}

//--------------------------------------------------------------------------

// Return the expansion of the no-emission probability up to the Nth
// term. Optionally calculate the the terms using fixed alphaS
// and/or PDF ratios.

vector<double>
DireHistory::countEmissions(PartonLevel* trial, double maxscale,
  double minscaleIn, int showerType, double as0,
  AlphaStrong * asFSR, AlphaStrong * asISR, int N, bool fixpdf, bool fixas,
  int order) {

  if ( N < 0 ) return vector<double>();
  vector<double> result(N+1);
  result[0] = 1.0;
  if ( N < 1 ) return result;

  // Copy state to local process
  Event process = state;

  double startingScale   = maxscale;
  // Careful when setting shower starting scale for pure QCD and prompt
  // photon case.
  if ( mergingHooksPtr->getNumberOfClusteringSteps(process) == 0
    && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
      || mergingHooksPtr->getProcessString().compare("pp>aj") == 0
         || isQCD2to2(state) ) )
      startingScale = min( startingScale, hardFacScale(process) );

  if ( mergingHooksPtr->getNumberOfClusteringSteps(process) == 0 )
    startingScale = hardStartScale(process);

  vector<double> wts;
  double mixed_expansion_wt = 0.;

  // Typically, we only want the expansion in terms of lowest-order
  // kernels, to avoid unnecessarily subtracting higher-order terms.
  int kernelOrderFSROld = fsr->getKernelOrder();
  int kernelOrderISROld = isr->getKernelOrder();
  if (order > -99) {
    int kernelOrderNow = 0;
    if (order>1) kernelOrderNow = 1;
    fsr->setKernelOrder(kernelOrderNow);
    isr->setKernelOrder(kernelOrderNow);
  }

  while ( true ) {

    // Reset trialShower object
    psweights->reset();
    trial->resetTrial();
    // Construct event to be showered
    Event event(15);
    event.init("(hard process-modified)", particleDataPtr);
    event.initColTag(process.lastColTag()+1000);

    // Reset process scale
    process.scale(startingScale);

    // Get pT before reclustering
    double minScale = (minscaleIn > 0.) ? minscaleIn : scale;

    mergingHooksPtr->setShowerStoppingScale(minScale);

    // If the maximal scale and the minimal scale coincide (as would
    // be the case for the corrected scales of unordered histories),
    // do not generate Sudakov
    if (minScale >= startingScale) {
      if (order > -99) {
        fsr->setKernelOrder(kernelOrderFSROld);
        isr->setKernelOrder(kernelOrderISROld);
      }
      return result;
    }

    // Find z and pT values at which the current state was formed, to
    // ensure that the showers can order the next emission correctly in
    // rapidity, if required
    if ( mother ) {
      double z = ( mergingHooksPtr->getNumberOfClusteringSteps(state) == 0)
               ? 0.5
               : mother->getCurrentZ(clusterIn.radPos,clusterIn.recPos,
                   clusterIn.emt1Pos);
      // Store z and pT values at which the current state was formed
      infoPtr->zNowISR(z);
      infoPtr->pT2NowISR(pow(startingScale,2));
      infoPtr->hasHistory(true);
    }

    // Perform trial shower emission
    trial->next(process,event);

    // Get trial shower pT
    double pTtrial = trial->pTLastInShower();
    int typeTrial  = trial->typeLastInShower();

    // Clear parton systems.
    trial->resetTrial();

    double t = (pTtrial <= 0.) ? pow2(minScale) : pow2(pTtrial);
    pair<double,double> wtShower = psweights->getWeight(t);
    double enhancement = 1.; 
    if ( pTtrial > minScale) enhancement
      = psweights->getTrialEnhancement( pow2(pTtrial));
    psweights->reset();
    if (pTtrial>0.) psweights->init();
    psweights->clearTrialEnhancements();

    // Done if evolution scale has fallen below minimum
    if ( pTtrial < minScale ) {
      //wt     *= wtShower.second;
      break;
    }

    // Save scale of current state.
    startingScale   = pTtrial;

    // Check if a new emission should be generated, either because
    // the latest emission was not of the desired kind or if the
    // emission was above the minimal scale
    double alphaSinPS = as0;
    double pdfs = 1.0;

    double asScale2 = pTtrial*pTtrial;
    // Directly get argument of running alpha_s from shower plugin.
    asScale2 = getShowerPluginScale(mother->state, clusterIn.radPos,
      clusterIn.emt1Pos, clusterIn.recPos, clusterIn.name(),
      "scaleAS", asScale2);

    // Initial state splittings.
    if ( (showerType == -1 || showerType == 2) && typeTrial == 2 ) {
      // Get weight to translate to alpha_s at fixed renormalisation scale.
      if ( fixas ) alphaSinPS = (*asISR).alphaS(asScale2);
      // Get weight to translate to PDFs at fixed factorisation scale.
      if ( fixpdf )
        //pdfs = pdfFactor( event, typeTrial, pTtrial,
        //                  mergingHooksPtr->muFinME() );
        pdfs = pdfFactor( process, event, typeTrial, pTtrial,
                          mergingHooksPtr->muFinME() );
    // Final state splittings.
    } else if ( (showerType == 1 || showerType == 2) && typeTrial >= 3 ) {
      // Get weight to translate to alpha_s at fixed renormalisation scale.
      if ( fixas ) alphaSinPS = (*asFSR).alphaS(asScale2);
      // Get weight to translate to PDFs at fixed factorisation scale. Needed
      // for final state splittings with initial state recoiler.
      if ( fixpdf )
        pdfs = pdfFactor( process, event, typeTrial, pTtrial,
                          mergingHooksPtr->muFinME() );
    }

    // Save weight correcting to emission generated with fixed scales.
    if ( typeTrial == 2 || typeTrial >= 3 ) {
      //pair<double,double> wtShower = psweights->getWeight(pow2(pTtrial));
      double w = as0/alphaSinPS * pdfs * wtShower.first * 1./enhancement;
      wts.push_back(w);
      // For second-order expansions, need to add the mixing terms
      // for alphaS-expansion in Sudakov exponent and PDF-expansion in
      // Sudakov exponent. Only former included so far.
      if (order > 1 && mergingHooksPtr->settingsPtr->flag("Dire:doTOMTE:AlphasRatios")) {
        double kernel_base = psweights->getSelectedKernel(pow2(pTtrial), "base");
        double kernel_base_oas2 = psweights->getSelectedKernel(pow2(pTtrial), "base_order_as2");
        double NF
        = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->getNF(pow2(pTtrial));
        double BETA0
        = ((DireSplittingQCD*)fsr->splits["Dire_fsr_qcd_1->1&21"])->betaQCD0(NF);
        double b=1.;
        vector<int> split = getSplittingPos(event, typeTrial);
        if ( event[split[2]].isFinal() && event[split[4]].isFinal()) b = 4.;
        w *= as0/(4.*M_PI) * BETA0 * log( pow2(minScale) / (b*pow2(pTtrial)));
        // Mixed terms should only depend on leading-order part of kernel
        if (kernel_base!=0.) w *= (kernel_base-kernel_base_oas2)/kernel_base;
        mixed_expansion_wt += w;
      }
    }
  }

  for ( int n = 1; n <= min(N, int(wts.size())); ++n ) {
    vector<int> ind(N);
    for ( int i = 0; i < N; ++i ) ind[i] = i;
    do {
      double x = 1.0;
      for ( int j = 0; j < n; ++j ) x *= wts[ind[j]];
      result[n] += x;
    }  while ( updateind(ind, n - 1, wts.size()) );
    if ( n%2 ) result[n] *= -1.0;
  }

  // Add mixed-expansion term to to third entry of return vector.
  // Note: This term does not include (Delta|_O(as1))^2 contributions,
  // since these would anyway cancel in the final result.
  if (order>1 && result.size()>2) result[2] += mixed_expansion_wt; 

  // Reset trialShower object
  psweights->reset();
  trial->resetTrial();

  if (order > -99) {
    fsr->setKernelOrder(kernelOrderFSROld);
    isr->setKernelOrder(kernelOrderISROld);
  }

  // Done
  return result;
}

//--------------------------------------------------------------------------

// Function to integrate PDF ratios between two scales over x and t,
// where the PDFs are always evaluated at the lower t-integration limit

double DireHistory::monteCarloPDFratios(int flav, double x, double maxScale,
         double minScale, double pdfScale, double asME, Rndm* rndmPtr) {

  // Perform numerical integration for PDF ratios
  // Prefactor is as/2PI
  double factor = asME / (2.*M_PI);
  // Scale integration just produces a multiplicative logarithm
  factor *= log(maxScale/minScale);

  // For identical scales, done
  if (factor == 0.) return 0.;

  // Declare constants
  double CF = 4./3.;
  double CA = 3.;
  double NF = 4.;
  double TR = 1./2.;

  double integral = 0.;
  double RN = rndmPtr->flat();

  if (flav == 21) {
    double zTrial = pow(x,RN);
    integral  = -log(x) * zTrial *
                integrand(flav, x, pdfScale, zTrial);
    integral += 1./6.*(11.*CA - 4.*NF*TR)
              + 2.*CA*log(1.-x);
  } else {
    double zTrial = x + RN*(1. - x);
    integral  = (1.-x) *
                integrand(flav, x, pdfScale, zTrial);
    integral += 3./2.*CF
              + 2.*CF*log(1.-x);
  }

  // Done
  return (factor*integral);
}

/*--------------- METHODS USED FOR CONTRUCTION OF ALL HISTORIES --------- */

// Check if a ordered (and complete) path has been found in the
// initial node, in which case we will no longer be interested in
// any unordered paths.

bool DireHistory::onlyOrderedPaths() {
  if ( !mother || foundOrderedPath ) return foundOrderedPath;
  return  foundOrderedPath = mother->onlyOrderedPaths();
}

//--------------------------------------------------------------------------

// Check if an allowed (according to user-criterion) path has been found in
// the initial node, in which case we will no longer be interested in
// any forbidden paths.

bool DireHistory::onlyAllowedPaths() {
  if ( !mother || foundAllowedPath ) return foundAllowedPath;
  return foundAllowedPath = mother->onlyAllowedPaths();
}

//--------------------------------------------------------------------------

// When a full path has been found, register it with the initial
// history node.
// IN  History : History to be registered as path
//     bool    : Specifying if clusterings so far were ordered
//     bool    : Specifying if path is complete down to 2->2 process
// OUT true if History object forms a plausible path (eg prob>0 ...)

//bool DireHistory::registerPath(DireHistory & l, bool isOrdered,
bool DireHistory::registerPath(DireHistory * l, bool isOrdered,
       bool isAllowed, bool isComplete) {

  // We are not interested in improbable paths.
  //if ( l.prodOfProbs <= 0.0 || l.state.size()<3)
  if ( l->prodOfProbs <= 0.0 || l->state.size()<3)
    return false;

  if ( mother ) mother->registerPath(l, isOrdered,
                         isAllowed, isComplete);

  bool isOrderedNow = (mother)
    ? l->isOrderedPath(hardStartScale(l->state), this) : isOrdered;

  // We are not interested in improbable paths, or incomplete, unordered or
  // disallowed paths if any reasonable paths were already registered.
  if (rejectBadPath(l, isOrderedNow, isAllowed, isComplete))
    return false;

  // Check and possibly set flags to remember ordering and completeness of
  // path.
  setGoodPathFlags(isOrderedNow, isAllowed, isComplete);

  DireHistory* end = this;
  int nord = l->nOrdered (infoPtr->eCM(), end);
  if ( mergingHooksPtr->orderHistories()
    && nord>-1 && nord + maxDepth() - depth < l->nMaxOrdered(end))
      return false;
  if ( mergingHooksPtr->orderHistories()
    && nord>-1 && nord + maxDepth() - depth > l->nMaxOrdered(end)
    && l->nMaxOrdered(end) > 0) {
    for ( map<double, DireHistory*>::iterator it = paths.begin();
      it != paths.end(); ++it ) {
#if (PYTHIA_VERSION_INTEGER >= 8242)
      it->second->state.free();
#else
      it->second->state.clear();
#endif
      it->second->erase = true;
    }
    map<double, DireHistory *>().swap(paths);
    paths.clear();
    sumpath = 0.0;
  }
  l->updateMinDepth(l->depth, end);
  l->updateNmaxOrdered(nord, end);

  // Index path by probability
  sumpath += l->prodOfProbs;
  paths[sumpath] = l;
  /*//paths[sumpath] = &l;
  map<double,DireHistory*>::iterator it = paths.find(sumpath);
  if ( it != paths.end() 
        && !(paths.key_comp()(sumpath,it->first))) { ; }
  else { 
    //paths.emplace(sumpath,&l);
    paths.insert(std::map<double,DireHistory*>::value_type(sumpath,l));
    //paths.insert(make_pair(sumpath,&l));
  }*/

  if (!mother) updateProbMax(l->prodOfProbs, isComplete);

  return true;
}

//--------------------------------------------------------------------------

bool DireHistory::rejectBadPath(DireHistory * l, bool isOrdered,
  bool isAllowed, bool isComplete) {

  bool foundAllowed = foundAllowedPath;
  bool foundOrdered = foundOrderedPath;
  bool foundComplete = foundCompletePath;
  DireHistory* leaf = this;
  while (leaf->mother) {
    foundAllowed = mother->foundAllowedPath;
    foundOrdered = mother->foundOrderedPath;
    foundComplete = mother->foundCompletePath;
    leaf = leaf->mother;
  }

  // Again, we are not interested in improbable paths.
  if ( sumpath == sumpath + l->prodOfProbs )
    return true;
  if ( mergingHooksPtr->canCutOnRecState()
    && foundAllowed/*Path*/ && !isAllowed )
    return true;
  if ( mergingHooksPtr->orderHistories()
    && foundOrdered/*Path*/ && !isOrdered ) {
    // Prefer complete or allowed paths to ordered paths.
    if ( (!foundComplete/*Path*/ && isComplete)
      || (!foundAllowed/*Path*/ && isAllowed) ) ;
    else return true;
  }
  if ( foundComplete/*Path*/ && !isComplete)
    return true;

  return false;

}

//--------------------------------------------------------------------------

void DireHistory::setGoodPathFlags(bool isOrdered, bool isAllowed,
  bool isComplete) {

  bool foundAllowed = foundAllowedPath;
  bool foundOrdered = foundOrderedPath;
  bool foundComplete = foundCompletePath;
  DireHistory* leaf = this;
  while (leaf->mother) {
    foundAllowed = mother->foundAllowedPath;
    foundOrdered = mother->foundOrderedPath;
    foundComplete = mother->foundCompletePath;
    leaf = leaf->mother;
  }

  // Again, we are not interested in improbable paths.
  if ( !mergingHooksPtr->canCutOnRecState()
    && !mergingHooksPtr->allowCutOnRecState() )
    foundAllowedPath = true;

  if ( mergingHooksPtr->canCutOnRecState() && isAllowed && isComplete) {
    if ( !foundAllowed/*Path*/ || !foundComplete/*Path*/ ) {
      // If this is the first complete, allowed path, discard the
      // old, disallowed or incomplete ones.
      map<double,DireHistory *>().swap(paths);
      paths.clear();
      sumpath = 0.0;
    }
    foundAllowedPath = true;
  }

  if (isOrdered && isComplete) {
    if ( mergingHooksPtr->orderHistories()
      && (!foundOrdered/*Path*/ || !foundComplete/*Path*/)) {
      // If this is the first complete, ordered path, discard the
      // old, non-ordered or incomplete ones.
      map<double,DireHistory *>().swap(paths);
      paths.clear();
      sumpath = 0.0;
    }
    foundOrderedPath = true;
    foundCompletePath = true;
  }

  if ( isComplete ) {
    if ( !foundComplete/*Path*/ ) {
      // If this is the first complete path, discard the old,
      // incomplete ones.
      map<double,DireHistory *>().swap(paths);
      paths.clear();
      sumpath = 0.0;
    }
    foundCompletePath = true;
  }

  // Remember, if this path is ordered, even if no ordering is required
  if ( isOrdered ) {
    foundOrderedPath = true;
  }

}

//--------------------------------------------------------------------------

// For one given state, find all possible clusterings.
// IN  Event : state to be investigated
// OUT vector of all (rad,rec,emt) systems in the state

vector<DireClustering> DireHistory::getAllClusterings( const Event& event) {

  fsr->direInfoPtr->message(1)
  << " Attempt finding clusterings" 
  << fsr->evtUtils->listEvent(event)
  << endl;

  vector<DireClustering> ret;
  vector<DireClustering> systems;

  // Get all clusterings of one emission.
  for (int i=0; i < event.size(); ++i) { // loop over emissions
    if ( event[i].isFinal() ) {
      for (int j=0; j < event.size(); ++j) { // loop over radiators
        if ( i == j) continue;
        bool isInitial = (event[j].status() == -21
                     || event[j].status() == -41 || event[j].status() == -42
                     || event[j].status() == -53
                     || event[j].status() == -31 || event[j].status() == -34);
        if (!isInitial && !event[j].isFinal() ) continue;
        systems = getClusterings( j, i, -1, event);
        ret.insert(ret.end(), systems.begin(), systems.end());
        systems.resize(0);
      }
    }
  }

  // Loop over splitting names and get possible double-emission kernels.
  vector<pair<int,int> > doubleEmtIds;
  for ( unordered_map<string,DireSplitting*>::iterator it = fsr->splits.begin();
    it != fsr->splits.end(); ++it ) {
    if (it->second->nEmissions() !=2 ) continue;
    vector<int> re = it->second->radAndEmt(0,999);
    if (re.size()>2) doubleEmtIds.push_back(make_pair(re[1],re[2]));
  }

  // Get all clusterings of two emissions.
  if (!doubleEmtIds.empty()) {
  for (int i=0; i < event.size(); ++i) { // loop over emissions
    for (int j=0; j < event.size(); ++j) { // loop over emissions
      if ( !event[i].isFinal() || !event[j].isFinal() || i == j) continue;
      pair<int,int> emtsNow = make_pair(event[i].id(),event[j].id());
      if (find(doubleEmtIds.begin(), doubleEmtIds.end(), emtsNow)
        == doubleEmtIds.end()) continue;
      for (int k=0; k < event.size(); ++k) { // loop over radiators
        if ( i == k || j == k) continue;
        bool isInitial = (event[k].status() == -21
                     || event[k].status() == -41 || event[k].status() == -42
                     || event[k].status() == -53
                     || event[k].status() == -31 || event[k].status() == -34);
        if (!isInitial && !event[k].isFinal() ) continue;
        systems = getClusterings( k, i, j, event);
        ret.insert(ret.end(), systems.begin(), systems.end());
        systems.resize(0);
      }
    }
  }
  }

  // Now remove any clustering that appears more than once.
  vector<int> iRemove;
  for (unsigned int i=0; i < ret.size(); ++i) {
    for (unsigned int j=i; j < ret.size(); ++j) {
      if (i == j) continue;
      if (find(iRemove.begin(), iRemove.end(), j) != iRemove.end()) continue;
      if ( equalClustering(ret[i], ret[j])) iRemove.push_back(j);
    }
  }
  sort (iRemove.begin(), iRemove.end());
  for (int i = iRemove.size()-1; i >= 0; --i) {
    ret[iRemove[i]] = ret.back();
    ret.pop_back();
  }

  fsr->direInfoPtr->message(1) << "List of all clusterings for "
    << stringFlavs(event) << endl;
  for (unsigned int i=0; i < ret.size(); ++i) 
    fsr->direInfoPtr->message(1) << i << " " << ret[i].listString() <<endl;

  return ret;
}

//--------------------------------------------------------------------------

// Function to attach (spin-dependent duplicates of) a clustering.

void DireHistory::attachClusterings (vector<DireClustering>& clus, int iRad,
  int iEmt1, int iEmt2, int iRec, int iPartner, double pT, string name,
  const Event& event) {

  //Do nothing for unphysical clustering.
  if (pT <= 0.) {
    //fsr->direInfoPtr->eatCout();
    ////event.list(false,false,10);
    //cout << scientific << setprecision(15)
    ////<< __FILE__ << " " << __func__
    //<< " " << __LINE__ << " Reject unphysical clustering " << name << " of "
    //<< iRad << " " << iEmt1 << " " << iEmt2 << " " << iRec
    //<< " since pT=" << pT << endl;
    //fsr->direInfoPtr->freeCout();
    return;
  } else if (pT == 0.) { ;
    //fsr->direInfoPtr->eatCout();
    //event.list(false,false,10);
    //cout << scientific << setprecision(15)
    //<< __FILE__ << " " << __func__
    //<< " " << __LINE__ << " Clustering " << name << " of "
    //<< iRad << " " << iEmt1 << " " << iEmt2 << " " << iRec
    //<< " has vanishing pT=" << pT << endl;
    //fsr->direInfoPtr->freeCout();
  }

  bool isFSR = (fsr) ? fsr->isTimelike(event, iRad, iEmt1, iRec, name) : false;
  int radBeforeFlav = (isFSR)
    ? fsr->splits[name]->radBefID(event[iRad].id(), event[iEmt1].id())
    : (isr) ? isr->splits[name]->radBefID(event[iRad].id(), event[iEmt1].id()) : 0;
  double tcut
    = pow2(max(0.,mergingHooksPtr->settingsPtr->parm("Dire:pTminMECs")));
  //double tcut = pow2(0.075);
  bool isAboveCut = (isFSR)
    ? fsr->splits[name]->dipoleAboveCutoff(pow2(pT), radBeforeFlav,
      event[iRec].id(), tcut)
      : (isr) ? isr->splits[name]->dipoleAboveCutoff(pow2(pT), radBeforeFlav,
                event[iRec].id(),tcut)
        : true;
  clus.push_back( DireClustering(iRad, iEmt1, iEmt2, iRec, iPartner, pT,
    &event[iRad], &event[iEmt1], (iEmt2>0?  &event[iEmt2] : nullptr),
    &event[iRec], name, radBeforeFlav, 0, 0, 0, isAboveCut));

  return;

}

//--------------------------------------------------------------------------

// Function to construct (rad,rec,emt) triples from the event
// IN  int   : Position of Emitted in event record for which
//             dipoles should be constructed
//     int   : Colour topogy to be tested
//             1= g -> qqbar, causing 2 -> 2 dipole splitting
//             2= q(bar) -> q(bar) g && g -> gg,
//              causing a 2 -> 3 dipole splitting
//     Event : event record to be checked for ptential partners
// OUT vector of all allowed radiator+recoiler+emitted triples

//vector<DireClustering> DireHistory::getClusterings (int emt, int rad,
vector<DireClustering> DireHistory::getClusterings (int rad, int emt1,
  int emt2, const Event& event ) {

  //fsr->direInfoPtr->eatCout();
  //event.list(false,false,10);
  fsr->direInfoPtr->message(1)
  << " Attempt finding clustering for positions "
  << rad << " " << emt1 << " " << emt2 << " and ids "
  << event[rad].id() << " " << event[emt1].id() << " "
  << ((emt2<0) ? 0 : event[emt2].id())
  << " " << stringFlavs(event)
  << endl;
  //fsr->direInfoPtr->freeCout();

  vector<DireClustering> clus;

  // Check if this configuration is result of a splitting.
  vector<string> fsrNames, isrNames;
  if (fsr) fsrNames = (emt2<0)
    ? fsr->getSplittingName(event,rad,emt1)
    : fsr->getSplittingName(event,rad,emt1,emt2);
  if (isr) isrNames = (emt2<0)
    ? isr->getSplittingName(event,rad,emt1)
    : isr->getSplittingName(event,rad,emt1,emt2);

  fsr->direInfoPtr->message(1) << " Found fsrNames ";
  for ( int iName=0; iName < int(fsrNames.size()); ++iName)
    fsr->direInfoPtr->message(1) << "\n    " << fsrNames[iName];
  fsr->direInfoPtr->message(1) << endl;
  fsr->direInfoPtr->message(1) << " Found isrNames ";
  for ( int iName=0; iName < int(isrNames.size()); ++iName)
    fsr->direInfoPtr->message(1) << "\n    " << isrNames[iName];
  fsr->direInfoPtr->message(1) << endl;

  for ( int iName=0; iName < int(fsrNames.size()); ++iName) {
    vector<int> recsNow = fsr->getRecoilers(event, rad, emt1, emt2,
      fsrNames[iName]);

    fsr->direInfoPtr->message(1)  << fsrNames[iName]
    << " " << event[rad].id() << " " << event[emt1].id()
    << " " << recsNow.size() << endl;   

    for ( int i = 0; i < int(recsNow.size()); ++i ) {
      bool allowed = (emt2<0) ? allowedClustering( rad, emt1, recsNow[i], 
        recsNow[i], fsrNames[iName], event) : true;
      double pT =pTLund(event,rad,emt1,emt2,recsNow[i],fsrNames[iName]);

      if (!allowed) fsr->direInfoPtr->message(1)
      << " Disallowed clustering " << fsrNames[iName] << " of " << rad << " " 
      << emt1 << " " << emt2 << " " << recsNow[i] << endl;
      else fsr->direInfoPtr->message(1)
      << " Allowed clustering " << fsrNames[iName] << " of " << rad << " " 
      << emt1 << " " << emt2 << " " << recsNow[i] << " pT=" << pT << endl;

      if (allowed) {
        //double pT =pTLund(event,rad,emt1,emt2,recsNow[i],fsrNames[iName]);
        attachClusterings (clus, rad, emt1, emt2, recsNow[i], recsNow[i], pT,
          fsrNames[iName], event);
      }
    }
  }

  for ( int iName=0; iName < int(isrNames.size()); ++iName) {
    vector<int> recsNow = isr->getRecoilers(event, rad, emt1, emt2, 
      isrNames[iName]);
    for ( int i = 0; i < int(recsNow.size()); ++i ) {
      bool allowed = (emt2<0) ? allowedClustering( rad, emt1, recsNow[i], 
        recsNow[i], isrNames[iName], event) : true;
      double pT =pTLund(event,rad,emt1,emt2,recsNow[i],isrNames[iName]);

      if (!allowed) fsr->direInfoPtr->message(1)
      << " Disallowed clustering " << isrNames[iName] << " of " << rad << " " 
      << emt1 << " " << emt2 << " " << recsNow[i] << endl;
      else fsr->direInfoPtr->message(1)
      << " Allowed clustering " << isrNames[iName] << " of " << rad << " " 
      << emt1 << " " << emt2 << " " << recsNow[i] << " pT=" << pT << endl;

      if (allowed) {
        attachClusterings (clus, rad, emt1, emt2, recsNow[i], recsNow[i], pT,
          //pTLund(event, rad, emt1, emt2, recsNow[i], isrNames[iName]),
          isrNames[iName], event);
      }
    }
  }

  // Done
  return clus;
}

//--------------------------------------------------------------------------

// Calculate and return the probability of a clustering.
// IN  Clustering : rad,rec,emt - System for which the splitting
//                  probability should be calcuated
// OUT splitting probability

pair<double,double> DireHistory::getProb(const DireClustering & clus) {

  // Get local copies of input system
  int rad     = clus.radPos;
  int rec     = clus.recPos;
  int emt1    = clus.emt1Pos;
  int emt2    = clus.emt2Pos;
  string name = clus.name();

  // If the splitting resulted in disallowed evolution variable,
  // disallow the splitting
  if (clus.pT() <= 0.) { return make_pair(1.,0.);}

  bool isFSR = (fsr) ? fsr->isTimelike(state, rad, emt1, rec, "")  : false;
  bool isISR = (isr) ? isr->isSpacelike(state, rad, emt1, rec, "") : false;
  bool isAboveCut = clus.isAboveCutoff;

  name += "-0";
  double pr(0.), coupling(1.);
  if (isFSR) {
    // Ask shower for splitting probability.
    double p = fsr->getSplittingProb( state, rad, emt1, emt2, rec, name, false);
    if (!isAboveCut) p = abs(p);
    pr += p;
    // Scale with correct coupling factor.
    name=name.substr( 0, name.size()-2);
    coupling      = fsr->getCoupling(-1., name);
  }

  if (isISR) {
    // Ask shower for splitting probability.
    double p = isr->getSplittingProb( state, rad, emt1, emt2, rec, name, false);
    if (!isAboveCut) p = abs(p);
    pr += p;
    // Scale with correct coupling factor.
    name=name.substr( 0, name.size()-2);
    coupling      = isr->getCoupling(-1., name);
  }

  // Done.
  return make_pair(coupling,pr);

}

//--------------------------------------------------------------------------

// Set up the beams (fill the beam particles with the correct
// current incoming particles) to allow calculation of splitting
// probability.
// For interleaved evolution, set assignments dividing PDFs into
// sea and valence content. This assignment is, until a history path
// is chosen and a first trial shower performed, not fully correct
// (since content is chosen form too high x and too low scale). The
// assignment used for reweighting will be corrected after trial
// showering

void DireHistory::setupBeams() {

  // Do nothing for empty event, possible if sequence of
  // clusterings was ill-advised in that it results in
  // colour-disconnected states
  if (state.size() < 4) return;

  // Do nothing for e+e- beams
  if ( state[3].colType() == 0 && state[4].colType() == 0 ) return;

  // Incoming partons to hard process are stored in slots 3 and 4.
  int inS = 0;
  int inP = 0;
  int inM = 0;
  for(int i=0;i< int(state.size()); ++i) {
    if (state[i].mother1() == 1) inP = i;
    if (state[i].mother1() == 2) inM = i;
  }

  /*// Save some info before clearing beams
  // Mothers of incoming partons companion code
  int motherPcompRes = -1;
  int motherMcompRes = -1;

  bool sameFlavP = false;
  bool sameFlavM = false;

  if (mother) {
    int inMotherP = 0;
    int inMotherM = 0;
    for(int i=0;i< int(mother->state.size()); ++i) {
      if (mother->state[i].mother1() == 1) inMotherP = i;
      if (mother->state[i].mother1() == 2) inMotherM = i;
    }
    sameFlavP = (state[inP].id() == mother->state[inMotherP].id());
    sameFlavM = (state[inM].id() == mother->state[inMotherM].id());

    motherPcompRes = (sameFlavP) ? beamA[0].companion() : -2;
    motherMcompRes = (sameFlavM) ? beamB[0].companion() : -2;
  }*/

  // Append the current incoming particles to the beam
  beamA.clear();
  beamB.clear();

  // Get energy of incoming particles
  double Ep = 2. * state[inP].e();
  double Em = 2. * state[inM].e();

  // If incoming partons are massive then recalculate to put them massless.
  if (state[inP].m() != 0. || state[inM].m() != 0.) {
    Ep = state[inP].pPos() + state[inM].pPos();
    Em = state[inP].pNeg() + state[inM].pNeg();
  }

  // Add incoming hard-scattering partons to list in beam remnants.
  double x1 = Ep / state[inS].m();
  beamA.append( inP, state[inP].id(), x1);
  double x2 = Em / state[inS].m();
  beamB.append( inM, state[inM].id(), x2);

  /*// Scale. For ME multiplicity history, put scale to mu_F
  // (since sea/valence quark content is chosen from this scale)
  double scalePDF = (mother) ? scale : infoPtr->QFac();
  // Find whether incoming partons are valence or sea. Store.
  // Can I do better, e.g. by setting the scale to the hard process
  // scale (= M_W) or by replacing one of the x values by some x/z??
  beamA.xfISR( 0, state[inP].id(), x1, scalePDF*scalePDF);
  if (!mother) {
    beamA.pickValSeaComp();
  }  else {
    beamA[0].companion(motherPcompRes);
  }
  beamB.xfISR( 0, state[inM].id(), x2, scalePDF*scalePDF);
  if (!mother) {
    beamB.pickValSeaComp();
  } else {
    beamB[0].companion(motherMcompRes);
  }*/

}

//--------------------------------------------------------------------------

// Calculate the PDF ratio used in the argument of the no-emission
// probability

double DireHistory::pdfForSudakov() {

  // Do nothing for e+e- beams
  if ( state[3].colType() == 0 ) return 1.0;
  if ( state[4].colType() == 0 ) return 1.0;

  // Check if splittings was ISR or FSR
  bool FSR = (   mother->state[clusterIn.radPos].isFinal()
             && mother->state[clusterIn.recPos].isFinal());
  bool FSRinRec = (   mother->state[clusterIn.radPos].isFinal()
                  && !mother->state[clusterIn.recPos].isFinal());

  // Done for pure FSR
  if (FSR) return 1.0;

  int iInMother = (FSRinRec)? clusterIn.recPos : clusterIn.radPos;
  //  Find side of event that was reclustered
  int side = ( mother->state[iInMother].pz() > 0 ) ? 1 : -1;

  int inP = 0;
  int inM = 0;
  for(int i=0;i< int(state.size()); ++i) {
    if (state[i].mother1() == 1) inP = i;
    if (state[i].mother1() == 2) inM = i;
  }

  // Save mother id
  int idMother = mother->state[iInMother].id();
  // Find daughter position and id
  int iDau = (side == 1) ? inP : inM;
  int idDaughter = state[iDau].id();
  // Get mother x value
  double xMother = 2. * mother->state[iInMother].e() / mother->state[0].e();
  // Get daughter x value of daughter
  double xDaughter = 2.*state[iDau].e() / state[0].e(); // x1 before isr

  // Calculate pdf ratio
  double ratio = getPDFratio(side, true, false, idMother, xMother, scale,
                   idDaughter, xDaughter, scale);

  // For FSR with incoming recoiler, maximally return 1.0, as
  // is done in Pythia::TimeShower.
  // For ISR, return ratio
  return ( (FSRinRec)? min(1.,ratio) : ratio);
}

//--------------------------------------------------------------------------

// Calculate the hard process matrix element to include in the selection
// probability.

double DireHistory::hardProcessME( const Event& event ) {

  // Calculate prob for Drell-Yan process.
  if (isEW2to1(event)) {

    // qqbar -> W.
    if (event[5].idAbs() == 24) {
      int idIn1  = event[3].id();
      int idIn2  = event[4].id();
      double mW = particleDataPtr->m0(24);
      double gW = particleDataPtr->mWidth(24) / mW;
      double sH = (event[3].p()+event[4].p()).m2Calc();

      double thetaWRat = 1. / (12. * coupSMPtr->sin2thetaW());
      double ckmW = coupSMPtr->V2CKMid(abs(idIn1), abs(idIn2));

      double bwW = 12. * M_PI / ( pow2(sH - pow2(mW)) + pow2(sH * gW) );
      double preFac = thetaWRat * sqrt(sH) * particleDataPtr->mWidth(24);
      return ckmW * preFac * bwW;
    }

    // qqbar -> Z. No interference with gamma included.
    else if (event[5].idAbs() == 23) {
      double mZ = particleDataPtr->m0(23);
      double gZ = particleDataPtr->mWidth(23) / mZ;
      double sH = (event[3].p()+event[4].p()).m2Calc();
      int flav  = (mother) ? abs(clusterIn.flavRadBef) : event[3].idAbs();
      double thetaZRat =
        (pow2(coupSMPtr->rf( flav )) + pow2(coupSMPtr->lf( flav ))) /
        (24. * coupSMPtr->sin2thetaW() * coupSMPtr->cos2thetaW());
      double bwW = 12. * M_PI / ( pow2(sH - pow2(mZ)) + pow2(sH * gZ) );
      double preFac = thetaZRat * sqrt(sH) * particleDataPtr->mWidth(23);
      return preFac * bwW;
    }

    else {
      string message="Warning in DireHistory::hardProcessME: Only Z/W are";
      message+=" supported as 2->1 processes. Skipping history.";
      infoPtr->errorMsg(message);
      return 0;
    }
  }
  // 2 to 2 process, assume QCD.
    else if (isQCD2to2(event)) {
    int idIn1  = event[3].id();
    int idIn2  = event[4].id();
    int idOut1 = event[5].id();
    int idOut2 = event[6].id();

    double sH = (event[3].p()+event[4].p()).m2Calc();
    double tH = (event[3].p()-event[5].p()).m2Calc();
    double uH = (event[3].p()-event[6].p()).m2Calc();

    // Verify that it is QCD.
    bool isQCD = true;
    if (!(abs(idIn1) < 10 || abs(idIn1) == 21) ) isQCD = false;
    if (!(abs(idIn2) < 10 || abs(idIn2) == 21) ) isQCD = false;
    if (!(abs(idOut1) < 10 || abs(idOut1) == 21) ) isQCD = false;
    if (!(abs(idOut2) < 10 || abs(idOut2) == 21) ) isQCD = false;

    // Overall phase-space constant (dsigma/dcos(theta)).
    //double cor = M_PI / (9. * pow2(sH));
    double cor = 1. / (9. * pow2(sH));

    // Multiply with overall factor (g_s^4) / (16Pi^2) = as^2
    double mu2Ren = pow2(mergingHooksPtr->muR());
    cor *= pow2( mergingHooksPtr->AlphaS_ISR()->alphaS(mu2Ren) );

    // If it is QCD calculate cross section.
    if (isQCD) {
      // Find out which 2->2 process it is.

      // incoming gluon pair.
      if (abs(idIn1) == 21 && abs(idIn2) == 21) {
        if (abs(idOut1) == 21 && abs(idOut2) == 21)
          return cor * weakShowerMEs.getMEgg2gg(sH, tH, uH);
        else return cor * weakShowerMEs.getMEgg2qqbar(sH, tH, uH);

      // Incoming single gluon
      } else if (abs(idIn1) == 21 || abs(idIn2) == 21) {
        if (idIn1 != idOut1) swap(uH, tH);
        return cor * weakShowerMEs.getMEqg2qg(sH, tH, uH);
      }

      // Incoming quarks
      else {
        if (abs(idOut1) == 21 && abs(idOut2) == 21) {
          return cor * weakShowerMEs.getMEqqbar2gg(sH, tH, uH);
        }

        if (idIn1 == -idIn2) {
          if (abs(idIn1) == abs(idOut1)) {
            if (idIn1 != idOut1) swap(uH, tH);
            return cor * weakShowerMEs.getMEqqbar2qqbar(sH, tH, uH, true);
          }
          else {
            return cor * weakShowerMEs.getMEqqbar2qqbar(sH, tH, uH, false);
          }
        }
        else if (idIn1 == idIn2)
          return cor * weakShowerMEs.getMEqq2qq(sH, tH, uH, true);
        else {
          if (idIn1 == idOut1) swap(uH,tH);
          return cor * weakShowerMEs.getMEqq2qq(sH, tH, uH, false);
        }
      }
    }
  }

  // Hard process MEs for DIS.
  if ( isDIS2to2(event) ) {

    //int iIncEl(0), iOutEl(0), iIncP(0), iOutP(0);
    int iIncEl(0), iOutEl(0), iIncP(0);
    for ( int i=0; i < event.size(); ++i ) {
      if ( event[i].idAbs() == 11 ) {
        if ( event[i].status() == -21 ) iIncEl = i;
        if ( event[i].isFinal() )       iOutEl = i;
      }
      if ( event[i].colType() != 0 ) {
        if ( event[i].status() == -21 ) iIncP  = i;
      }
    }
    Vec4 pgam( event[iIncEl].p() - event[iOutEl].p() );
    Vec4 pprot( (event[iIncP].mother1() == 1) ? event[1].p() : event[2].p() ); 
    double s  = pow2(event[0].m()); 
    double Q2 = -pgam.m2Calc();
    double y  = (pprot*pgam) / (pprot*event[iIncEl].p());
    double x  = Q2 / (2.*pprot*pgam); 
    double res = 4.*M_PI / (s*pow2(x)*pow2(y))*(1. - y + 0.5*pow2(y));
    return res;

  // 2 to 2 process, assume QCD.
  } else if (isMassless2to2(event)) {
    int idIn1  = event[3].id();
    int idIn2  = event[4].id();
    int idOut1 = event[5].id();
    int idOut2 = event[6].id();

    double sH = (event[3].p()+event[4].p()).m2Calc();
    double tH = (event[3].p()-event[5].p()).m2Calc();
    double uH = (event[3].p()-event[6].p()).m2Calc();

    // Verify that it is QCD.
    int inc1Type = particleDataPtr->colType(idIn1);
    int inc2Type = particleDataPtr->colType(idIn2);
    int out1Type = particleDataPtr->colType(idOut1);
    int out2Type = particleDataPtr->colType(idOut2);
    bool isQCD = (inc1Type*inc2Type*out1Type*out2Type != 0);

    // Overall phase-space constant (dsigma/dcos(theta)).
    double cor = M_PI / (9. * pow2(sH));

    // If it is QCD calculate cross section.
    if (isQCD) {
      // Find out which 2->2 process it is.

      // incoming gluon pair.
      if (abs(idIn1) == 21 && abs(idIn2) == 21) {
        if (abs(idOut1) == 21 && abs(idOut2) == 21)
          return cor * weakShowerMEs.getMEgg2gg(sH, tH, uH);
        else return cor * weakShowerMEs.getMEgg2qqbar(sH, tH, uH);

      // Incoming single gluon
      } else if (abs(idIn1) == 21 || abs(idIn2) == 21) {
        if (idIn1 != idOut1) swap(uH, tH);
        return cor * weakShowerMEs.getMEqg2qg(sH, tH, uH);
      }

      // Incoming quarks
      else {
        if (abs(idOut1) == 21 && abs(idOut2) == 21)
          return cor * weakShowerMEs.getMEqqbar2gg(sH, tH, uH);
        if (idIn1 == -idIn2) {
          if (abs(idIn1) == abs(idOut1)) {
            if (idIn1 != idOut1) swap(uH, tH);
            return cor * weakShowerMEs.getMEqqbar2qqbar(sH, tH, uH, true);
          }
          else {
            return cor * weakShowerMEs.getMEqqbar2qqbar(sH, tH, uH, false);
          }
        }
        else if (idIn1 == idIn2)
          return cor * weakShowerMEs.getMEqq2qq(sH, tH, uH, true);
        else {
          if (idIn1 == idOut1) swap(uH,tH);
          return cor * weakShowerMEs.getMEqq2qq(sH, tH, uH, false);
        }
      }
    }

    // Photon-gluon scattering, use gg->qq~ as proxy.
    if ( (idIn1 == 21 && idIn2 == 22) || (idIn1 == 22 && idIn2 == 21) )
      return cor * weakShowerMEs.getMEgg2qqbar(sH, tH, uH);

    // Photon-quark scattering, use gq->gq as proxy.
    if ( (abs(idIn1) < 10 && idIn2 == 22) || (idIn1 == 22 && abs(idIn2) < 10)){
        if (idIn1 != idOut1) swap(uH, tH);
        return cor * weakShowerMEs.getMEqg2qg(sH, tH, uH);
    }

  }

  // Get hard process.
  string process = mergingHooksPtr->getProcessString();
  double result = 1.;

  if ( process.compare("pp>e+ve") == 0
    || process.compare("pp>e-ve~") == 0
    || process.compare("pp>LEPTONS,NEUTRINOS") == 0 ) {
    // Do nothing for incomplete process.
    int nFinal = 0;
    for ( int i=0; i < int(event.size()); ++i )
      if ( event[i].isFinal() ) nFinal++;
    if ( nFinal != 2 ) return 1.;
    // Get W-boson mass and width.
    double mW = particleDataPtr->m0(24);
    double gW = particleDataPtr->mWidth(24) / mW;
    // Get incoming particles.
    int inP = (event[3].pz() > 0) ? 3 : 4;
    int inM = (event[3].pz() > 0) ? 4 : 3;
    // Get outgoing particles.
    int outP = 0;
    for ( int i=0; i < int(event.size()); ++i ) {
      if ( event[i].isFinal() && event[i].px() > 0 ) outP = i;
    }
    // Get Mandelstam variables.
    double sH = (event[inP].p() + event[inM].p()).m2Calc();
    double tH = (event[inP].p() - event[outP].p()).m2Calc();
    double uH = - sH - tH;

    // Return kinematic part of matrix element.
    result = ( 1. + (tH - uH)/sH ) / ( pow2(sH - mW*mW) + pow2(sH*gW) );
  } else
    result = mergingHooksPtr->hardProcessME(event);

  return result;

}

//bool DireHistory::updateCouplingPowCount(string key, int value) {
bool DireHistory::updateCouplingPowCount(int key, int value) {
//  if ( couplingPowCount.find(key) != couplingPowCount.end() )
    couplingPowCount[key]+=value; 
//  else
//    couplingPowCount.insert(make_pair(key, value));
  return true;
}

//--------------------------------------------------------------------------

// Function to return the couplings present in the hard process ME (for correct
// relative normalization of histories with different hard process, coupling
// should be stripped off).

double DireHistory::hardProcessCouplings( const Event& event, int order,
  double scale2, AlphaStrong* alphaS, AlphaEM* alphaEM,
  bool fillCouplCounters, bool with2Pi) {

  vector<int> nwp, nwm, nz, nh, na, nl, nlq, ng, nq, nqb;
  int in1(0), in2(0); 
  for (int i=0; i < event.size(); ++i) {
    if (event[i].mother1() == 1 && event[i].mother2() == 0) in1 = i;
    if (event[i].mother1() == 2 && event[i].mother2() == 0) in2 = i;
    if (event[i].isFinal()) {
      if (event[i].id() == 21) ng.push_back(i);
      if (event[i].id() == 22) na.push_back(i);
      if (event[i].id() == 23) nz.push_back(i);
      if (event[i].id() == 24) nwp.push_back(i);
      if (event[i].id() ==-24) nwm.push_back(i);
      if (event[i].id() == 25) nh.push_back(i);
      if (event[i].isLepton()) nl.push_back(i);
      if (event[i].colType() == 1) nq.push_back(i);
      if (event[i].colType() ==-1) nqb.push_back(i);
    }
  }

  double twopi = (with2Pi) ? 2.*M_PI : 1.;
  double as2pi  = (order == 0)
    ? mergingHooksPtr->settingsPtr->parm("SigmaProcess:alphaSvalue")/twopi
    : alphaS->alphaS(scale2)/twopi;
  double aem2pi = (order == 0)
    ? mergingHooksPtr->settingsPtr->parm("StandardModel:alphaEM0")/twopi
    : alphaEM->alphaEM(scale2)/twopi;

  double result = 1.;
  // One power of aEM for each outgoing photon.
  result *= pow(aem2pi,na.size());
  //if (fillCouplCounters) couplingPowCount["qed"]+=na.size(); 
  //if (fillCouplCounters) updateCouplingPowCount("qed", na.size()); 
  if (fillCouplCounters) updateCouplingPowCount(QED, na.size()); 
  // One power of aEM for each outgoing W- and Z-boson.
  result *= pow(aem2pi,nwp.size()+nwm.size()+nz.size());
  //if (fillCouplCounters) couplingPowCount["qed"]+=nwp.size()+nwm.size()+nz.size(); 
  if (fillCouplCounters) updateCouplingPowCount(QED,nwp.size()+nwm.size()+nz.size()); 
  // One power of aS for each outgoing gluon.
  result *= pow(as2pi,ng.size());
  //if (fillCouplCounters) couplingPowCount["qcd"]+=ng.size(); 
  if (fillCouplCounters) updateCouplingPowCount(QCD,ng.size()); 

  // Couplings for outgoing quarks.
  if (
       (event[in1].colType() == 0 && event[in2].colType() == 0)
    && (nq.size() == 1 && nqb.size() == 1)
    && (event[nq[0]].id() == -event[nqb[0]].id()) ) {
    // Two powers of aEM for single quark pair coupling to incoming lepton pair.
    result *= pow(aem2pi,2.0);
    //if (fillCouplCounters) couplingPowCount["qed"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QED,2); 
  } else if (
       (event[in1].colType() == 0 && event[in2].colType() == 1)
    && (nq.size() == 1 && event[in2].id() == event[nq[0]].id()) ) {
    // Two powers of aEM for eq->eq scattering.
    result *= pow(aem2pi,2.0);
    //if (fillCouplCounters) couplingPowCount["qed"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QED,2); 
  } else if (
       (event[in2].colType() == 0 && event[in1].colType() == 1)
    && (nq.size() == 1 && event[in1].id() == event[nq[0]].id()) ) {
    // Two powers of aEM for eq->eq scattering.
    result *= pow(aem2pi,2.0);
    //if (fillCouplCounters) couplingPowCount["qed"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QED,2); 
  } else if (
       (event[in1].colType() == 0 && event[in2].colType() ==-1)
    && (nqb.size() == 1 && event[in2].id() == event[nqb[0]].id()) ) {
    // Two powers of aEM for eqbar->eqbar scattering.
    result *= pow(aem2pi,2.0);
    //if (fillCouplCounters) couplingPowCount["qed"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QED,2); 
  } else if (
       (event[in2].colType() == 0 && event[in1].colType() ==-1)
    && (nqb.size() == 1 && event[in1].id() == event[nqb[0]].id()) ) {
    // Two powers of aEM for eq->eq scattering.
    result *= pow(aem2pi,2.0);
    //if (fillCouplCounters) couplingPowCount["qed"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QED,2); 
  } else {
    // One power of aS for each outgoing quark/antiquark.
    result *= pow(as2pi,nq.size()+nqb.size());
    //if (fillCouplCounters) couplingPowCount["qcd"]+=nq.size()+nqb.size(); 
    if (fillCouplCounters) updateCouplingPowCount(QCD,nq.size()+nqb.size()); 
  }

  // Coupling for outgoing Higgs to initial state.
  if ( nh.size() > 0 ) {

    double sH = event[nh.front()].m2Calc();
    double mH = sqrt(sH);

    double width = 0.;
    if (event[in1].id() == event[in2].id() && event[in1].id()  == 21)
      width = particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH,21,21)/64;
    else if (event[in1].id() == -event[in2].id() && event[in1].idAbs() < 9)
      width = particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH, event[in1].id(), -event[in1].id()) / 9.;
    else if (event[in1].id() == 21 && event[in2].idAbs() < 9)
      width = max(particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH, 21, 21) / 64,
        particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH, event[in1].id(), -event[in1].id()) / 9.);
    else if (event[in2].id() == 21 && event[in1].idAbs() < 9)
      width = max(particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH, 21, 21) / 64,
        particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
        mH, event[in2].id(), -event[in2].id()) / 9.);

    double m2Res = pow2(particleDataPtr->m0(25));
    double widthTot
      = particleDataPtr->particleDataEntryPtr(25)->resWidth(25,mH);

    // Check if Higgs can couple to final state
    if (width/widthTot < 1e-4) {
      for (int i=0; i < event.size(); ++i) {
        if (i != nh.front() && event[i].isFinal()) {
          int sign = particleDataPtr->hasAnti(event[i].id()) ? -1 : 1;
          double widthNew
            = particleDataPtr->particleDataEntryPtr(25)->resWidthChan(
            mH, event[i].id(), sign*event[i].id());
          if (event[i].id()  == 21) widthNew /= 64.;
          if (event[i].idAbs() < 9) widthNew /= 9.;
          if (widthNew/widthTot > 1e-4 && widthNew/widthTot > width/widthTot){
            width = widthNew; break;
          }
        }
      }
    }

    // Also remove Breit-Wigner (since contained in clustering probability)
    double sigBW  = 8. * M_PI/ ( pow2(sH - m2Res) + pow2(mH * widthTot) );

    // Discard things with extremely small branching fraction.
    if (width/widthTot < 1e-4) width = 0.;

    double asRatio = (order==0) ? 1.
      : pow2(alphaS->alphaS(scale2)/alphaS->alphaS(125.*125.));
    double res = pow(width*sigBW*asRatio,nh.size());

    result *= res;
    //if (fillCouplCounters) couplingPowCount["qcd"]+=2; 
    if (fillCouplCounters) updateCouplingPowCount(QCD,2); 
    //if (fillCouplCounters) couplingPowCount["heft"]++; 
    if (fillCouplCounters) updateCouplingPowCount(HEFT,1); 

  }

  return result;

}

//--------------------------------------------------------------------------

bool DireHistory::passHardProcessCuts(const Event& event) {

  bool passCut = true;

  vector<int> nwp, nwm, nz, nh, na, nl, ng, nq, nqb;
  int in1(0), in2(0); 
  for (int i=0; i < event.size(); ++i) {
    if (event[i].mother1() == 1 && event[i].mother2() == 0) in1 = i;
    if (event[i].mother1() == 2 && event[i].mother2() == 0) in2 = i;
    if (event[i].isFinal()) {
      if (event[i].id() == 21) ng.push_back(i);
      if (event[i].id() == 22) na.push_back(i);
      if (event[i].id() == 23) nz.push_back(i);
      if (event[i].id() == 24) nwp.push_back(i);
      if (event[i].id() ==-24) nwm.push_back(i);
      if (event[i].id() == 25) nh.push_back(i);
      if (event[i].isLepton()) nl.push_back(i);
      if (event[i].colType() == 1) nq.push_back(i);
      if (event[i].colType() ==-1) nqb.push_back(i);
    }
  }

  int nwpIn(0), nwmIn(0), nzIn(0), nhIn(0), naIn(0), nlIn(0), ngIn(0),
      nqIn(0), nqbIn(0);
  for (int iIn=0; iIn < 2; ++iIn) {
    int i = (iIn==0) ? in1 : in2;
    if (event[i].id() == 21) ngIn++;
    if (event[i].id() == 22) naIn++;
    if (event[i].id() == 23) nzIn++;
    if (event[i].id() == 24) nwpIn++;
    if (event[i].id() ==-24) nwmIn++;
    if (event[i].id() == 25) nhIn++;
    if (event[i].isLepton()) nlIn++;
    if (event[i].colType() == 1) nqIn++;
    if (event[i].colType() ==-1) nqbIn++;
  }

  // Cuts for two outgoing light particles given two light incoming particles.
  if (naIn+ngIn+nqIn+nqbIn == 2
    && na.size()+ng.size()+nq.size()+nqb.size() == 2) {
    for (size_t i=0; i < na.size(); ++i)
      passCut = passCut && event[na[i]].pT() > mergingHooksPtr->tms();
    for (size_t i=0; i < ng.size(); ++i)
      passCut = passCut && event[ng[i]].pT() > mergingHooksPtr->tms();
    for (size_t i=0; i < nq.size(); ++i)
      passCut = passCut && event[nq[i]].pT() > mergingHooksPtr->tms();
    for (size_t i=0; i < nqb.size(); ++i)
      passCut = passCut && event[nqb[i]].pT() > mergingHooksPtr->tms();

  } else { ;
  }

  //// Cuts on Higgs states.
  //if ( nh.size() > 0 ) { }

  return passCut;

}

//--------------------------------------------------------------------------

double DireHistory::hardProcessScale( const Event& event) {

  // Find the mT in the hard sub-process.
  double nFinal(0.), mTprod(1.);
  for ( int i=0; i < event.size(); ++i)
    if ( event[i].isFinal() ) {
      nFinal += 1.;
      mTprod *= abs(event[i].mT());
    }
  double hardScale = (mTprod!=1.) ? pow(mTprod, 1./nFinal) : infoPtr->QRen();

  // Done.
  return hardScale;

}

//--------------------------------------------------------------------------

// Perform the clustering of the current state and return the
// clustered state.
// IN Clustering : rad,rec,emt triple to be clustered to two partons
// OUT clustered state

Event DireHistory::cluster( DireClustering & clus) {

  // Initialise tags of particles to be changed
  int rad     = clus.radPos;
  int rec     = clus.recPos;
  int emt1    = clus.emt1Pos;
  int emt2    = clus.emt2Pos;
  string name = clus.name();

  // Construct the clustered event
  Event newEvent(15);
  newEvent.init("(hard process-modified)", particleDataPtr);
  newEvent.initColTag(state.lastColTag()+1000);
  //newEvent.clear();

  bool isFSR = (fsr) ? fsr->isTimelike(state, rad, emt1, rec, "") : false;
  if (isFSR)     newEvent = fsr->clustered( state, rad, emt1, emt2, rec, name);
  else if (isr)  newEvent = isr->clustered( state, rad, emt1, emt2, rec, name);

  // Store radiator and recoiler positions.
  if (newEvent.size() > 0) {
    clus.recBef = newEvent[0].mother2();
    clus.radBef = newEvent[0].mother1();
    newEvent[0].mothers(0,0);
  }

  // Done
  return newEvent;
}

//--------------------------------------------------------------------------

// Function to properly colour-connect the radiator to the rest of
// the event, as needed during clustering
// IN  Particle& : Particle to be connected
//     Particle  : Recoiler forming a dipole with Radiator
//     Event     : event to which Radiator shall be appended
// OUT true               : Radiator could be connected to the event
//     false              : Radiator could not be connected to the
//                          event or the resulting event was
//                          non-valid

bool DireHistory::connectRadiator( Particle& Radiator, const int RadType,
                      const Particle& Recoiler, const int RecType,
                      const Event& event ) {

  // Start filling radiator colour indices with dummy values
  Radiator.cols( -1, -1 );

  // Radiator should always be colour-connected to recoiler.
  // Three cases (rad = Anti-Quark, Quark, Gluon) to be considered
  if ( Radiator.colType() == -1 ) {
    // For final state antiquark radiator, the anticolour is fixed
    // by the final / initial state recoiler colour / anticolour
    if ( RadType + RecType == 2 )
      Radiator.cols( 0, Recoiler.col());
    else if ( RadType + RecType == 0 )
      Radiator.cols( 0, Recoiler.acol());
    // For initial state antiquark radiator, the anticolour is fixed
    // by the colour of the emitted gluon (which will be the
    // leftover anticolour of a final state particle or the leftover
    // colour of an initial state particle ( = the recoiler))
    else {
      // Set colour of antiquark radiator to zero
      Radiator.col( 0 );
      for (int i = 0; i < event.size(); ++i) {
        int col = event[i].col();
        int acl = event[i].acol();

        if ( event[i].isFinal()) {
          // Search for leftover anticolour in final / initial state
          if ( acl > 0 && FindCol(acl,i,0,event,1,true) == 0
              && FindCol(acl,i,0,event,2,true) == 0 )
            Radiator.acol(event[i].acol());
        } else {
          // Search for leftover colour in initial / final state
          if ( col > 0 && FindCol(col,i,0,event,1,true) == 0
              && FindCol(col,i,0,event,2,true) == 0 )
            Radiator.acol(event[i].col());
        }
      } // end loop over particles in event record
    }

  } else if ( Radiator.colType() == 1 ) {
    // For final state quark radiator, the colour is fixed
    // by the final / initial state recoiler anticolour / colour
    if ( RadType + RecType == 2 )
      Radiator.cols( Recoiler.acol(), 0);

    else if ( RadType + RecType == 0 )
      Radiator.cols( Recoiler.col(), 0);
    // For initial state quark radiator, the colour is fixed
    // by the anticolour of the emitted gluon (which will be the
    // leftover colour of a final state particle or the leftover
    // anticolour of an initial state particle ( = the recoiler))

    else {
      // Set anticolour of quark radiator to zero
      Radiator.acol( 0 );
      for (int i = 0; i < event.size(); ++i) {
        int col = event[i].col();
        int acl = event[i].acol();

        if ( event[i].isFinal()) {
          // Search for leftover colour in final / initial state
          if ( col > 0 && FindCol(col,i,0,event,1,true) == 0
              && FindCol(col,i,0,event,2,true) == 0)
            Radiator.col(event[i].col());
        } else {
          // Search for leftover anticolour in initial / final state
          if ( acl > 0 && FindCol(acl,i,0,event,1,true) == 0
              && FindCol(acl,i,0,event,2,true) == 0)
            Radiator.col(event[i].acol());
        }
      } // end loop over particles in event record

    } // end distinction between fsr / fsr+initial recoiler / isr

  } else if ( Radiator.colType() == 2 ) {
    // For a gluon radiator, one (anticolour) colour index is defined
    // by the recoiler colour (anticolour).
    // The remaining index is chosen to match the free index in the
    // event
    // Search for leftover colour (anticolour) in the final state
    for (int i = 0; i < event.size(); ++i) {
      int col = event[i].col();
      int acl = event[i].acol();
      int iEx = i;

      if ( event[i].isFinal()) {
        if ( col > 0 && FindCol(col,iEx,0,event,1,true) == 0
          && FindCol(col,iEx,0,event,2,true) == 0) {
          if (Radiator.status() < 0 ) Radiator.col(event[i].col());
          else Radiator.acol(event[i].col());
        }
        if ( acl > 0 && FindCol(acl,iEx,0,event,2,true) == 0
          && FindCol(acl,iEx,0,event,1,true) == 0 ) {
          if (Radiator.status() < 0 )  Radiator.acol(event[i].acol());
          else Radiator.col(event[i].acol());
        }
      } else {
        if ( col > 0 && FindCol(col,iEx,0,event,1,true) == 0
          && FindCol(col,iEx,0,event,2,true) == 0) {
          if (Radiator.status() < 0 ) Radiator.acol(event[i].col());
          else Radiator.col(event[i].col());
        }
        if ( acl > 0 && (FindCol(acl,iEx,0,event,2,true) == 0
          && FindCol(acl,iEx,0,event,1,true) == 0)) {
          if (Radiator.status() < 0 ) Radiator.col(event[i].acol());
          else Radiator.acol(event[i].acol());
        }
      }
    } // end loop over particles in event record
  } // end cases of different radiator colour type

  // If either colour or anticolour has not been set, return false
  if (Radiator.col() < 0 || Radiator.acol() < 0) return false;
  // Done
  return true;
}

//--------------------------------------------------------------------------

// Function to find a colour (anticolour) index in the input event
// IN  int col       : Colour tag to be investigated
//     int iExclude1 : Identifier of first particle to be excluded
//                     from search
//     int iExclude2 : Identifier of second particle to be excluded
//                     from  search
//     Event event   : event to be searched for colour tag
//     int type      : Tag to define if col should be counted as
//                      colour (type = 1) [->find anti-colour index
//                                         contracted with col]
//                      anticolour (type = 2) [->find colour index
//                                         contracted with col]
// OUT int           : Position of particle in event record
//                     contraced with col [0 if col is free tag]

int DireHistory::FindCol(int col, int iExclude1, int iExclude2,
            const Event& event, int type, bool isHardIn) {

  bool isHard = isHardIn;
  int index = 0;

  if (isHard) {
    // Search event record for matching colour & anticolour
    for(int n = 0; n < event.size(); ++n) {
      if ( n != iExclude1 && n != iExclude2
        && event[n].colType() != 0
        &&(   event[n].status() > 0          // Check outgoing
           || event[n].status() == -21) ) {  // Check incoming
         if ( event[n].acol() == col ) {
          index = -n;
          break;
        }
        if ( event[n].col()  == col ) {
          index =  n;
          break;
        }
      }
    }
  } else {

    // Search event record for matching colour & anticolour
    for(int n = 0; n < event.size(); ++n) {
      if (  n != iExclude1 && n != iExclude2
        && event[n].colType() != 0
        &&(   event[n].status() == 43        // Check outgoing from ISR
           || event[n].status() == 51        // Check outgoing from FSR
           || event[n].status() == -41       // first initial
           || event[n].status() == -42) ) {  // second initial
        if ( event[n].acol() == col ) {
          index = -n;
          break;
        }
        if ( event[n].col()  == col ) {
          index =  n;
          break;
        }
      }
    }
  }
  // if no matching colour / anticolour has been found, return false
  if ( type == 1 && index < 0) return abs(index);
  if ( type == 2 && index > 0) return abs(index);

  return 0;
}

//--------------------------------------------------------------------------

// Function to in the input event find a particle with quantum
// numbers matching those of the input particle
// IN  Particle : Particle to be searched for
//     Event    : Event to be searched in
// OUT int      : > 0 : Position of matching particle in event
//                < 0 : No match in event

int DireHistory::FindParticle( const Particle& particle, const Event& event,
  bool checkStatus ) {

  int index = -1;

  for ( int i = int(event.size()) - 1; i > 0; --i )
    if ( event[i].id()         == particle.id()
      && event[i].colType()    == particle.colType()
      && event[i].chargeType() == particle.chargeType()
      && event[i].col()        == particle.col()
      && event[i].acol()       == particle.acol()
      && event[i].charge()     == particle.charge() ) {
      index = i;
      break;
    }

  if ( checkStatus && event[index].status() != particle.status() )
    index = -1;

  return index;
}

//--------------------------------------------------------------------------

  // Function to get the parton connected to in by a colour line
  // IN  int   : Position of parton for which partner should be found
  //     Event : Reference event
  // OUT int   : If a colour line connects the "in" parton with another
  //             parton, return the Position of the partner, else return 0

int DireHistory::getColPartner(const int in, const Event& event) {

  if (event[in].col() == 0) return 0;

  int partner = 0;
  // Try to find anticolour index first
  partner = FindCol(event[in].col(),in,0,event,1,true);
  // If no anticolour index has been found, try colour
  if (partner == 0)
   partner = FindCol(event[in].col(),in,0,event,2,true);

  return partner;

}

//--------------------------------------------------------------------------

  // Function to get the parton connected to in by an anticolour line
  // IN  int   : Position of parton for which partner should be found
  //     Event : Reference event
  // OUT int   : If an anticolour line connects the "in" parton with another
  //             parton, return the Position of the partner, else return 0

int DireHistory::getAcolPartner(const int in, const Event& event) {

  if (event[in].acol() == 0) return 0;

  int partner = 0;
  // Try to find colour index first
  partner = FindCol(event[in].acol(),in,0,event,2,true);
  // If no colour index has been found, try anticolour
  if (partner == 0)
   partner = FindCol(event[in].acol(),in,0,event,1,true);

  return partner;

}

//--------------------------------------------------------------------------

// Function to extract a chain of colour-connected partons in
// the event
// IN     int          : Type of parton from which to start extracting a
//                       parton chain. If the starting point is a quark
//                       i.e. flavType = 1, a chain of partons that are
//                       consecutively connected by colour-lines will be
//                       extracted. If the starting point is an antiquark
//                       i.e. flavType =-1, a chain of partons that are
//                       consecutively connected by anticolour-lines
//                       will be extracted.
// IN      int         : Position of the parton from which a
//                       colour-connected chain should be derived
// IN      Event       : Refernence event
// IN/OUT  vector<int> : Partons that should be excluded from the search.
// OUT     vector<int> : Positions of partons along the chain
// OUT     bool        : Found singlet / did not find singlet

bool DireHistory::getColSinglet( const int flavType, const int iParton,
  const Event& event, vector<int>& exclude, vector<int>& colSinglet) {

  // If no possible flavour to start from has been found
  if (iParton < 0) return false;

  // If no further partner has been found in a previous iteration,
  // and the whole final state has been excluded, we're done
  if (iParton == 0) {

    // Count number of final state partons
    int nFinal = 0;
    for(int i=0; i < int(event.size()); ++i)
      if ( event[i].isFinal() && event[i].colType() != 0)
        nFinal++;

    // Get number of initial state partons in the list of
    // excluded partons
    int nExclude = int(exclude.size());
    int nInitExclude = 0;
    if (!event[exclude[2]].isFinal())
      nInitExclude++;
    if (!event[exclude[3]].isFinal())
      nInitExclude++;

    // If the whole final state has been considered, return
    if (nFinal == nExclude - nInitExclude)
      return true;
    else
      return false;

  }

  // Declare colour partner
  int colP = 0;
  // Save the colour partner
  colSinglet.push_back(iParton);
  // Remove the partner from the list
  exclude.push_back(iParton);
  // When starting out from a quark line, follow the colour lines
  if (flavType == 1)
    colP = getColPartner(iParton,event);
  // When starting out from an antiquark line, follow the anticolour lines
  else
    colP = getAcolPartner(iParton,event);

  // Do not count excluded partons twice
  for(int i = 0; i < int(exclude.size()); ++i)
    if (colP == exclude[i])
      return true;

  // Recurse
  return getColSinglet(flavType,colP,event,exclude,colSinglet);

}

//--------------------------------------------------------------------------

// Function to check that a set of partons forms a colour singlet
// IN  Event       : Reference event
// IN  vector<int> : Positions of the partons in the set
// OUT bool        : Is a colour singlet / is not

bool DireHistory::isColSinglet( const Event& event,
  vector<int> system ) {

  // Check if system forms a colour singlet
  for(int i=0; i < int(system.size()); ++i ) {
    // Match quark and gluon colours
    if ( system[i] > 0
      && (event[system[i]].colType() == 1
       || event[system[i]].colType() == 2) ) {
      for(int j=0; j < int(system.size()); ++j)
        // If flavour matches, remove both partons and continue
        if ( system[i] > 0
          && system[j] > 0
          && event[system[i]].col() == event[system[j]].acol()) {
          // Remove index and break
          system[i] = 0;
          system[j] = 0;
          break;
        }
    }
    // Match antiquark and gluon anticolours
    if ( system[i] > 0
      && (event[system[i]].colType() == -1
       || event[system[i]].colType() == 2) ) {
      for(int j=0; j < int(system.size()); ++j)
        // If flavour matches, remove both partons and continue
        if ( system[i] > 0
          && system[j] > 0
          && event[system[i]].acol() == event[system[j]].col()) {
          // Remove index and break
          system[i] = 0;
          system[j] = 0;
          break;
        }
    }

  }

  // The system is a colour singlet if for all colours,
  // an anticolour was found
  bool isColSing = true;
  for(int i=0; i < int(system.size()); ++i)
    if ( system[i] != 0 )
      isColSing = false;

  // Return
  return isColSing;


}

//--------------------------------------------------------------------------

// Function to check that a set of partons forms a flavour singlet
// IN  Event       : Reference event
// IN  vector<int> : Positions of the partons in the set
// IN  int         : Flavour of all the quarks in the set, if
//                   all quarks in a set should have a fixed flavour
// OUT bool        : Is a flavour singlet / is not

bool DireHistory::isFlavSinglet( const Event& event,
  vector<int> system, int flav) {

  // If a decoupled colour singlet has been found, check if this is also
  // a flavour singlet
  // Check that each quark matches an antiquark
  for(int i=0; i < int(system.size()); ++i)
    if ( system[i] > 0 ) {
      for(int j=0; j < int(system.size()); ++j) {
        // If flavour of outgoing partons matches,
        // remove both partons and continue.
        // Skip all bosons
        if ( event[i].idAbs() != 21
          && event[i].idAbs() != 22
          && event[i].idAbs() != 23
          && event[i].idAbs() != 24
          && system[i] > 0
          && system[j] > 0
          && event[system[i]].isFinal()
          && event[system[j]].isFinal()
          && event[system[i]].id() == -1*event[system[j]].id()) {
          // If we want to check if only one flavour of quarks
          // exists
          if (abs(flav) > 0 && event[system[i]].idAbs() != flav)
            return false;
          // Remove index and break
          system[i] = 0;
          system[j] = 0;
          break;
        }
        // If flavour of outgoing and incoming partons match,
        // remove both partons and continue.
        // Skip all bosons
        if ( event[i].idAbs() != 21
          && event[i].idAbs() != 22
          && event[i].idAbs() != 23
          && event[i].idAbs() != 24
          && system[i] > 0
          && system[j] > 0
          && ( ( !event[system[i]].isFinal() && event[system[j]].isFinal())
             ||( !event[system[j]].isFinal() && event[system[i]].isFinal()) )
          && event[system[i]].id() == event[system[j]].id()) {
          // If we want to check if only one flavour of quarks
          // exists
          if (abs(flav) > 0 && event[system[i]].idAbs() != flav)
            return false;
          // Remove index and break
          system[i] = 0;
          system[j] = 0;
          break;
        }

      }
    }

  // The colour singlet is a flavour singlet if for all quarks,
  // an antiquark was found
  bool isFlavSing = true;
  for(int i=0; i < int(system.size()); ++i)
    if ( system[i] != 0 )
      isFlavSing = false;

  // Return
  return isFlavSing;

}

//--------------------------------------------------------------------------

// Function to check if rad,emt,rec triple is allowed for clustering
// IN int rad,emt,rec : Positions (in event record) of the three
//                      particles considered for clustering
//    Event event     : Reference event

bool DireHistory::allowedClustering( int rad, int emt, int rec, int partner,
  string name, const Event& event ) {

  //fsr->direInfoPtr->message(1) << " Check clustering "
  //<< rad << " " << emt << " " << rec << " " << name << endl;

  // Declare output
  bool allowed = true;

  // Check if the triple forms a colour singlett
  bool isSing    = isSinglett(rad,emt,partner,event);
  bool hasColour = event[rad].colType() != 0 || event[emt].colType() != 0;
  int type       = (event[rad].isFinal()) ? 1 :-1;

  if (name.compare("Dire_fsr_qcd_1->21&1") == 0) swap(rad,emt);
  if (name.compare("Dire_fsr_qed_1->22&1") == 0) swap(rad,emt);
  if (name.compare("Dire_fsr_qed_11->22&11") == 0) swap(rad,emt);
  if (name.compare("Dire_fsr_u1new_11->22&11") == 0) swap(rad,emt);

  bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt, rec, "") : false;
  bool isISR = (isr) ? isr->isSpacelike(event, rad, emt, rec, "") : false;

  Event clustered;
  if (isFSR) clustered = fsr->clustered(event,rad,emt,-1,rec,name);
  if (isISR) clustered = isr->clustered(event,rad,emt,-1,rec,name);
  if (clustered.size()==0) {
    fsr->direInfoPtr->message(1) << __LINE__ << " " << __func__
    << " Return false. name=" << name
    << " t=" << pow2(pTLund(event, rad, emt, rec, name)) << endl;
    return false; 
  }
  if (psweights->hasME(state) && !psweights->hasME(clustered)) {
    fsr->direInfoPtr->message(1) << __LINE__ << " " << __func__
    << " Return false. name=" << name
    << " t=" << pow2(pTLund(event, rad, emt, rec, name)) << endl;
    return false;
  }

  double tEvol = pTLund(event, rad, emt, rec, name);
  // Only allow clustering if the evolution scale is well-defined.
  if ( tEvol < 0.0) {
    fsr->direInfoPtr->message(1) << __LINE__ << " " << __func__
    << " Return false. name=" << name
    << " t=" << pow2(pTLund(event, rad, emt, rec, name)) << endl;
    return false;
  }

  // Get flavour of radiator after potential clustering
  //int radBeforeFlav = int(stateVars["radBefID"]);
  int radBeforeFlav = (isFSR)
    ? fsr->splits[name]->radBefID(state[rad].id(), state[emt].id())
    : isr->splits[name]->radBefID(state[rad].id(), state[emt].id());

  // Count coloured partons in hard process
  int nPartonInHard = 0;
  for(int i=0; i < int(event.size()); ++i)
    // Check all final state partons
    if ( event[i].isFinal()
      && event[i].colType() != 0
      && mergingHooksPtr->hardProcess->matchesAnyOutgoing(i, event) )
      nPartonInHard++;

  // Count coloured final state partons in event, excluding
  // rad, rec, emt and hard process
  int nPartons = 0;
  for(int i=0; i < int(event.size()); ++i)
    // Check all final state partons
    if ( i!=emt && i!=rad && i!=rec
      &&  event[i].isFinal()
      &&  event[i].colType() != 0
      && !mergingHooksPtr->hardProcess->matchesAnyOutgoing(i, event) )
      nPartons++;

  // Count number of initial state partons
  int nInitialPartons = 0;
  for(int i=0; i < int(event.size()); ++i)
    if ( event[i].status() == -21
      && event[i].colType() != 0 )
      nInitialPartons++;

  // Get number of non-charged final state particles
  int nFinalEW = 0;
  for(int i=0; i < int(event.size()); ++i)
    if ( event[i].isFinal()
      &&(  event[i].id() == 22
        || event[i].id() == 23
        || event[i].idAbs() == 24
        ||(event[i].idAbs() > 10 && event[i].idAbs() < 20)
        ||(event[i].idAbs() > 10 && event[i].idAbs() < 20)
        ||(event[i].idAbs() > 1000010 && event[i].idAbs() < 1000020)
        ||(event[i].idAbs() > 2000010 && event[i].idAbs() < 2000020) ))
      nFinalEW++;

  int nFinalH = 0;
  for(int i=0; i < int(event.size()); ++i)
    if ( event[i].isFinal() && event[i].id() == 25)
      nFinalH++;

  // Check if event after potential clustering contains an even
  // number of quarks and/or antiquarks
  // (otherwise no electroweak vertex could be formed!)
  // Get number of final quarks
  int nFinalQuark = 0;
  int nFinalGluon = 0;
  // Get number of excluded final state quarks as well
  int nFinalQuarkExc = 0;
  for(int i=0; i < int(event.size()); ++i) {
    if (i !=rad && i != emt && i != rec) {
      if (event[i].isFinal() && abs(event[i].colType()) == 1 ) {
        if ( !mergingHooksPtr->hardProcess->matchesAnyOutgoing(i,event) )
          nFinalQuark++;
        else
          nFinalQuarkExc++;
      }
      if (event[i].isFinal() && event[i].isGluon()
        && !mergingHooksPtr->hardProcess->matchesAnyOutgoing(i,event) ) {
          nFinalGluon++;
      }
    }
  }

  // Add recoiler to number of final quarks
  if (event[rec].isFinal() && event[rec].isQuark()) nFinalQuark++;
  if (event[rec].isFinal() && event[rec].isGluon()) nFinalGluon++;
  // Add radiator after clustering to number of final quarks
  if (event[rad].isFinal() && abs(radBeforeFlav) < 10) nFinalQuark++;
  if (event[rad].isFinal() && radBeforeFlav == 21)     nFinalGluon++;

  // Get number of initial quarks
  int nInitialQuark = 0;
  if (type == 1) {
    if (event[rec].isFinal()) {
      if (event[3].isQuark())        nInitialQuark++;
      if (event[4].isQuark())        nInitialQuark++;
    } else {
      int iOtherIn = (rec == 3) ? 4 : 3;
      if (event[rec].isQuark())      nInitialQuark++;
      if (event[iOtherIn].isQuark()) nInitialQuark++;
    }
  } else {
    if (event[rec].isFinal()) {
      int iOtherIn = (rad == 3) ? 4 : 3;
      if (abs(radBeforeFlav) < 10)   nInitialQuark++;
      if (event[iOtherIn].isQuark()) nInitialQuark++;
    } else {
      if (abs(radBeforeFlav) < 10)   nInitialQuark++;
      if (event[rec].isQuark())      nInitialQuark++;
    }
  }

  // Get number of initial leptons.
  int nInitialLepton = 0;
  if (type == 1) {
    if (event[rec].isFinal()) {
      if (event[3].isLepton()) nInitialLepton++;
      if (event[4].isLepton()) nInitialLepton++;
    } else {
      int iOtherIn = (rec == 3) ? 4 : 3;
      if (event[rec].isLepton()) nInitialLepton++;
      if (event[iOtherIn].isLepton()) nInitialLepton++;
    }
  } else {
    // Add recoiler to number of initial quarks
    if (event[rec].isLepton()) nInitialLepton++;
    // Add radiator after clustering to number of initial quarks
    if (abs(radBeforeFlav) > 10 && abs(radBeforeFlav) < 20 ) nInitialLepton++;
  }

  // Store incoming and outgoing flavours after clustering.
  vector<int> in;
  for(int i=0; i < int(event.size()); ++i)
    if ( i!=emt && i!=rad && i!=rec
      && (event[i].mother1() == 1 || event[i].mother1() == 2))
      in.push_back(event[i].id());
  if (!event[rad].isFinal()) in.push_back(radBeforeFlav);
  if (!event[rec].isFinal()) in.push_back(event[rec].id());
  vector<int> out;
  for(int i=0; i < int(event.size()); ++i)
    if ( i!=emt && i!=rad && i!=rec && event[i].isFinal())
      out.push_back(event[i].id());
  if (event[rad].isFinal()) out.push_back(radBeforeFlav);
  if (event[rec].isFinal()) out.push_back(event[rec].id());

  // Do not allow clusterings that lead to a disallowed proton content.
  int proton[] = {1,2,3,4,5,21,22,23,24};
  bool isInProton = false;
  for(int i=0; i < 9; ++i)
    if (abs(radBeforeFlav) == proton[i]) isInProton = true;
  if ( type == -1 && particleDataPtr->colType(radBeforeFlav) != 0
    && !isInProton) return false;
  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering at line"
  //  << __LINE__ << endl;

  // If triple forms colour singlett, check that resulting state
  // matches hard core process
  if (hasColour && isSing)
    allowed = false;
  if (hasColour && isSing && (abs(radBeforeFlav)<10 && event[rec].isQuark()) )
    allowed = true;

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering at line"
  //  << __LINE__ << endl;

  // Colour singlet in DIS hard process
  if (hasColour && isSing && abs(radBeforeFlav)<10 && nPartons == 0
    && nInitialPartons == 1)
    allowed = true;

  //fsr->direInfoPtr->eatCout();
  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  // Never recluster any outgoing partons of the core V -> qqbar' splitting!
  if ( mergingHooksPtr->hardProcess->matchesAnyOutgoing(emt,event) ) {
    // Check if any other particle could replace "emt" as part of the candidate
    // core process. If so, replace emt with the new candidate and allow the
    // clustering.
    bool canReplace = mergingHooksPtr->hardProcess->findOtherCandidates(emt,
                        event, true);
    if (canReplace) allowed = true;
    else allowed = false;
  }

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  // Never remove so many particles that the hard process cannot
  // be set up afterwards.
  //int nIncPartHardProc = mergingHooksPtr->hardProcess->nQuarksIn();
  int nOutPartHardProc = mergingHooksPtr->hardProcess->nQuarksOut();
  // Add recoiler to number of final quarks
  int nOutPartNow(nPartons);
  // Add non-participating hard process partons.
  for(int i=0; i < int(event.size()); ++i)
    // Check all final state partons
    if ( i!=emt && i!=rad && i!=rec
      &&  event[i].isFinal()
      &&  event[i].colType() != 0
      &&  mergingHooksPtr->hardProcess->matchesAnyOutgoing(i, event) )
      nOutPartNow++;
  if (event[rec].isFinal() && event[rec].colType() != 0) nOutPartNow++;
  // Add radiator after clustering to number of final quarks
  if (event[rad].isFinal() && particleDataPtr->colType(radBeforeFlav) != 0)
    nOutPartNow++;
  if (nOutPartNow < nOutPartHardProc) allowed = false;

  //fsr->direInfoPtr->eatCout();
  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  // Never allow clustering of any outgoing partons of the hard process
  // which would change the flavour of one of the hard process partons!
  if ( mergingHooksPtr->hardProcess->matchesAnyOutgoing(rad,event) 
      && event[rad].id() != radBeforeFlav ) {
    // Check if any other particle could replace "emt" as part of the candidate
    // core process. If so, replace emt with the new candidate and allow the
    // clustering.
    bool canReplace = mergingHooksPtr->hardProcess->findOtherCandidates(rad,
                        event, true);
    if (canReplace) allowed = true;
    else allowed = false;
  }

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  // If only gluons in initial state and no quarks in final state,
  // reject (no electroweak vertex can be formed)
  if ( nFinalEW   != 0     && nInitialQuark == 0 && nFinalQuark == 0
    && nFinalQuarkExc == 0 && nInitialLepton == 0 
    && !mayHaveEffectiveVertex( mergingHooksPtr->getProcessString(), in, out))
    allowed = false;

  // If only gluons in final state and no partons in initial state,
  // reject (no electroweak vertex can be formed)
  if ( nInitialLepton == 2
    && nFinalQuark == 0 && nFinalQuarkExc == 0
    && nFinalGluon > 0
    && !mayHaveEffectiveVertex( mergingHooksPtr->getProcessString(), in, out))
    allowed = false;

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  if ( (nInitialQuark + nFinalQuark + nFinalQuarkExc)%2 != 0 )
    allowed = false;

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering " << name
  //  << " at line " << __LINE__ << endl;

  map<int,int> nIncIDs, nOutIDs;
  for ( int i = 0; i < event.size(); ++i) {
    if ( i != emt && i != rad && event[i].isFinal() ) {
      if (nOutIDs.find(event[i].id()) != nOutIDs.end() )
        nOutIDs[event[i].id()]++;
      else
        nOutIDs.insert(make_pair(event[i].id(),1));
    }
    if ( i != emt && i != rad && event[i].status() == -21 ){
      if (nIncIDs.find(event[i].id()) != nIncIDs.end() )
        nIncIDs[event[i].id()]++;
      else
        nIncIDs.insert(make_pair(event[i].id(),1));
    }
  }
  if (type > 0 ) {
    if (nOutIDs.find(radBeforeFlav) != nOutIDs.end()) nOutIDs[radBeforeFlav]++;
    else nOutIDs.insert(make_pair(radBeforeFlav,1));
  }
  if (type < 0 ) {
    if (nIncIDs.find(radBeforeFlav) != nIncIDs.end()) nIncIDs[radBeforeFlav]++;
    else nIncIDs.insert(make_pair(radBeforeFlav,1));
  }

  if (!canConnectFlavs(nIncIDs,nOutIDs) ) allowed = false;

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering at line"
  //  << __LINE__ << endl;

  // Disallow clusterings that lead to a 2->1 massless state.
  // To check, only look at final state flavours.
  int nMassless(0), nOther(0);
  for ( map<int, int>::iterator it = nOutIDs.begin();
    it != nOutIDs.end(); ++it )
    if ( abs(it->first) < 20 || abs(it->first) == 21
      || abs(it->first) == 22) nMassless += it->second;
    else nOther++;
  if (nMassless == 1 && nOther == 0) allowed = false;

  //if (!allowed)
  //  fsr->direInfoPtr->message(1) << " Disallowed clustering at line"
  //  << __LINE__ << endl;

  // Disallow final state splittings that lead to a purely gluonic final
  // state, while having a completely colour-connected initial state.
  // This means that the clustering is discarded if it does not lead to the
  // t-channel gluon needed to connect the final state to a qq~ initial state.
  // Here, partons excluded from clustering are not counted as possible
  // partners to form a t-channel gluon
  if ( event[3].colType() == 2 && event[4].colType() == 2
    && event[3].col()  == event[4].acol()
    && event[3].acol() == event[4].col()
    && !mayHaveEffectiveVertex( mergingHooksPtr->getProcessString(), in, out)
    && nFinalQuark == 0){
    // Careful if rad and rec are the only quarks in the final state, but
    // were both excluded from the list of final state quarks.
    int nTripletts = abs(event[rec].colType())
                   + abs(particleDataPtr->colType(radBeforeFlav));
    if (event[3].isGluon())                            allowed = false;
    else if (nTripletts != 2 && nFinalQuarkExc%2 == 0) allowed = false;
  }

  // Done
  return allowed;

}

//--------------------------------------------------------------------------

bool DireHistory::hasConnections( int, int nIncIDs[], int nOutIDs[]) {

  bool foundQuarks = false;
  for (int i=-6; i < 6; i++)
    if (nIncIDs[i] > 0 || nOutIDs[i] > 0) foundQuarks = true;

  if ( nIncIDs[-11] == 1 && nOutIDs[-11] == 1 && !foundQuarks) return false;

  return true;
}


bool DireHistory::canConnectFlavs( map<int,int> nIncIDs,
  map<int,int> nOutIDs) {

  bool foundIncQuarks(false), foundOutQuarks(false);
  for (int i=-6; i < 6; i++) {
    if (nIncIDs[i] > 0) foundIncQuarks = true;
    if (nOutIDs[i] > 0) foundOutQuarks = true;
  }

  int nIncEle = (nIncIDs.find(11)  != nIncIDs.end()) ? nIncIDs[11]  : 0;
  int nIncPos = (nIncIDs.find(-11) != nIncIDs.end()) ? nIncIDs[-11] : 0;
  int nOutEle = (nOutIDs.find(11)  != nOutIDs.end()) ? nOutIDs[11]  : 0;
  int nOutPos = (nOutIDs.find(-11) != nOutIDs.end()) ? nOutIDs[-11] : 0;

  // Cannot couple positron to other electric charge.
  if ( nIncPos == 1 && nOutPos == 1 && !foundOutQuarks && !foundIncQuarks)
    return false;

  // Cannot couple electron to other electric charge.
  if ( nIncEle == 1 && nOutEle == 1 && !foundOutQuarks && !foundIncQuarks)
    return false;

  return true;
}

//--------------------------------------------------------------------------

// Function to check if rad,emt,rec triple is results in
// colour singlet radBefore+recBefore
// IN int rad,emt,rec : Positions (in event record) of the three
//                      particles considered for clustering
//    Event event     : Reference event

bool DireHistory::isSinglett( int rad, int emt, int rec, const Event& event ) {

  int radCol = event[rad].col();
  int emtCol = event[emt].col();
  int recCol = event[rec].col();
  int radAcl = event[rad].acol();
  int emtAcl = event[emt].acol();
  int recAcl = event[rec].acol();
  int recType = event[rec].isFinal() ? 1 : -1;

  bool isSing = false;

  if ( ( recType == -1
       && radCol + emtCol == recCol && radAcl + emtAcl == recAcl)
    ||( recType == 1
       && radCol + emtCol == recAcl && radAcl + emtAcl == recCol) )
    isSing = true;

  return isSing;

}

//--------------------------------------------------------------------------

// Function to check if event is sensibly constructed: Meaning
// that all colour indices are contracted and that the charge in
// initial and final states matches
// IN  event : event to be checked
// OUT TRUE  : event is properly construced
//     FALSE : event not valid

bool DireHistory::validEvent( const Event& event ) {

  // Check if event is coloured
  bool validColour = true;
  for ( int i = 0; i < event.size(); ++i)
   // Check colour of quarks
   if ( event[i].isFinal() && event[i].colType() == 1
          // No corresponding anticolour in final state
       && ( FindCol(event[i].col(),i,0,event,1,true) == 0
          // No corresponding colour in initial state
         && FindCol(event[i].col(),i,0,event,2,true) == 0 )) {
     validColour = false;
     break;
   // Check anticolour of antiquarks
   } else if ( event[i].isFinal() && event[i].colType() == -1
          // No corresponding colour in final state
       && ( FindCol(event[i].acol(),i,0,event,2,true) == 0
          // No corresponding anticolour in initial state
         && FindCol(event[i].acol(),i,0,event,1,true) == 0 )) {
     validColour = false;
     break;
   // No uncontracted colour (anticolour) charge of gluons
   } else if ( event[i].isFinal() && event[i].colType() == 2
          // No corresponding anticolour in final state
       && ( FindCol(event[i].col(),i,0,event,1,true) == 0
          // No corresponding colour in initial state
         && FindCol(event[i].col(),i,0,event,2,true) == 0 )
          // No corresponding colour in final state
       && ( FindCol(event[i].acol(),i,0,event,2,true) == 0
          // No corresponding anticolour in initial state
         && FindCol(event[i].acol(),i,0,event,1,true) == 0 )) {
     validColour = false;
     break;
   }

  // Check charge sum in initial and final state
  bool validCharge = true;
  double initCharge = event[3].charge() + event[4].charge();
  double finalCharge = 0.0;
  for(int i = 0; i < event.size(); ++i)
    if (event[i].isFinal()) finalCharge += event[i].charge();
  if (abs(initCharge-finalCharge) > 1e-12) validCharge = false;

  return (validColour && validCharge);

}

//--------------------------------------------------------------------------

// Function to check whether two clusterings are identical, used
// for finding the history path in the mother -> children direction

bool DireHistory::equalClustering( DireClustering c1 , DireClustering c2 ) {

  // Check if clustering members are equal.
  bool isIdenticalClustering
    =  (c1.radPos      == c2.radPos)
    && (c1.emt1Pos     == c2.emt1Pos)
    && (c1.emt2Pos     == c2.emt2Pos)
    && (c1.recPos      == c2.recPos)
    && (c1.partner     == c2.partner)
    && (c1.pT()        == c2.pT())
    && (c1.spinRadBef  == c2.spinRadBef)
    && (c1.flavRadBef  == c2.flavRadBef)
    && (c1.splitName   == c2.splitName);
  if (isIdenticalClustering) return true;

  // Require identical recoiler.
  if (c1.recPos != c2.recPos) return false;
  // Require same names.
  if (c1.name() != c2.name())     return false;

  // For unequal clusterings, splitting can still be identical, if symmetric
  // in radiator and emission.
  if (c1.radPos != c2.emt1Pos || c1.emt1Pos != c2.radPos) return false;

  bool isIdenticalSplitting = false;
  if (fsr && c1.rad()->isFinal() && c2.rad()->isFinal())
    isIdenticalSplitting = fsr->isSymmetric(c1.name(),c1.rad(),c1.emt1());
  else if (isr && !c1.rad()->isFinal() && !c2.rad()->isFinal())
    isIdenticalSplitting = isr->isSymmetric(c1.name(),c1.rad(),c1.emt1());

  return isIdenticalSplitting;

}

//--------------------------------------------------------------------------

// Chose dummy scale for event construction. By default, choose
//     sHat     for 2->Boson(->2)+ n partons processes and
//     M_Boson  for 2->Boson(->)             processes

double DireHistory::choseHardScale( const Event& event ) const {

  // Get sHat
  double mHat = (event[3].p() + event[4].p()).mCalc();

  // Find number of final state particles and bosons
  int nFinal = 0;
  int nFinBos= 0;
  int nBosons= 0;
  double mBos = 0.0;
  for(int i = 0; i < event.size(); ++i)
    if ( event[i].isFinal() ) {
      nFinal++;
      // Remember final state unstable bosons
      if ( event[i].idAbs() == 23
        || event[i].idAbs() == 24 ) {
          nFinBos++;
          nBosons++;
          mBos += event[i].m();
      }
    } else if ( abs(event[i].status()) == 22
             && (  event[i].idAbs() == 23
                || event[i].idAbs() == 24 )) {
      nBosons++;
      mBos += event[i].m(); // Real mass
    }

  // Return averaged boson masses
  if ( nBosons > 0 && (nFinal + nFinBos*2) <= 3)
    return (mBos / double(nBosons));
  else return
    mHat;
}


//--------------------------------------------------------------------------

// If the state has an incoming hadron return the flavour of the
// parton entering the hard interaction. Otherwise return 0

int DireHistory::getCurrentFlav(const int side) const {
  int in = (side == 1) ? 3 : 4;
  return state[in].id();
}

//--------------------------------------------------------------------------

double DireHistory::getCurrentX(const int side) const {
  int in = (side == 1) ? 3 : 4;
  return ( 2.*state[in].e()/state[0].e() );
}

//--------------------------------------------------------------------------

double DireHistory::getCurrentZ(const int rad,
  const int rec, const int emt, int idRadBef) const {

  int type = state[rad].isFinal() ? 1 : -1;
  double z = 0.;

  if (type == 1) {

    Vec4 radAfterBranch(state[rad].p());
    Vec4 recAfterBranch(state[rec].p());
    Vec4 emtAfterBranch(state[emt].p());

    // Store masses both after and prior to emission.
    double m2RadAft = radAfterBranch.m2Calc();
    double m2EmtAft = emtAfterBranch.m2Calc();
    double m2RadBef = 0.;
    if ( state[rad].idAbs() != 21 && state[rad].idAbs() != 22
      && state[emt].idAbs() != 24 && state[rad].idAbs() != state[emt].idAbs())
      m2RadBef = m2RadAft;
    else if ( state[emt].idAbs() == 24) {
      if (idRadBef != 0)
        m2RadBef = pow2(particleDataPtr->m0(abs(idRadBef)));
    }

    double Qsq   = (radAfterBranch + emtAfterBranch).m2Calc();

    // Calculate dipole invariant mass.
    double m2final
      = (radAfterBranch + recAfterBranch + emtAfterBranch).m2Calc();
    // More complicated for initial state recoiler.
    if ( !state[rec].isFinal() ){
      double mar2  = m2final - 2. * Qsq + 2. * m2RadBef;
       recAfterBranch *=  (1. - (Qsq - m2RadBef)/(mar2 - m2RadBef))
                         /(1. + (Qsq - m2RadBef)/(mar2 - m2RadBef));
       // If Qsq is larger than mar2 the event is not kinematically possible.
       // Just return random z, since clustering will be discarded.
       if (Qsq > mar2) return 0.5;
    }

    Vec4   sum   = radAfterBranch + recAfterBranch + emtAfterBranch;
    double m2Dip = sum.m2Calc();
    // Construct 2->3 variables for FSR
    double x1 = 2. * (sum * radAfterBranch) / m2Dip;
    double x2 = 2. * (sum * recAfterBranch) / m2Dip;

    // Prepare for more complicated z definition for massive splittings.
    double lambda13 = sqrt( pow2(Qsq - m2RadAft - m2EmtAft )
                         - 4.*m2RadAft*m2EmtAft);
    double k1 = ( Qsq - lambda13 + (m2EmtAft - m2RadAft ) ) / ( 2. * Qsq );
    double k3 = ( Qsq - lambda13 - (m2EmtAft - m2RadAft ) ) / ( 2. * Qsq );
    // Calculate z of splitting, different for FSR
    z = 1./ ( 1- k1 -k3) * ( x1 / (2.-x2) - k3);

  } else {
    // Construct momenta of dipole before/after splitting for ISR
    Vec4 qBR(state[rad].p() - state[emt].p() + state[rec].p());
    Vec4 qAR(state[rad].p() + state[rec].p());
    // Calculate z of splitting, different for ISR
    z = (qBR.m2Calc())/( qAR.m2Calc());
  }

  return z;

}

//--------------------------------------------------------------------------

// Function to compute "pythia pT separation" from Particle input

double DireHistory::pTLund(const Event& event, int rad, int emt, int rec, 
  string name) {
  //string) {

  double tEvol = -1.;

  int evType
    = fsr->splits[name]->typeEvolutionMeasure();
  bool canUseSplitInfo
    = fsr->splits[name]->canUseForBranching();
  int idRadBef
    = fsr->splits[name]->radBefID(event[rad].id(), event[emt].id());
  //bool isRes
  //  = particleDataPtr->isResonance(idRadBef);
  double mRes
    = particleDataPtr->m0(idRadBef);
  double m2Res = pow2(mRes);
  /*if (event[rad].isFinal() && canUseSplitInfo && isRes) {
    if (evType==0)     tEvol = (event[rad].p() + event[emt].p()).m2Calc()
                         - m2Res;
    else if (evType>0) tEvol = (event[rad].p() + event[emt].p()).m2Calc(); 
    else if (evType<0) tEvol = pow2(2.*mRes
                         - (event[rad].p() + event[emt].p()).mCalc());
    return tEvol>0. ? sqrt(tEvol) : -1.;
  }*/

  if (event[rad].isFinal() && canUseSplitInfo && evType!=0) {
    if (evType==2)
      tEvol = (event[rad].p() + event[emt].p()).m2Calc() - m2Res;
    else if (evType==1)
      tEvol = (event[rad].p() + event[emt].p()).m2Calc(); 
    else if (evType==-1)
      tEvol = pow2(max(0.,2.*mRes-(event[rad].p() + event[emt].p()).mCalc()));
    return tEvol>0. ? sqrt(tEvol) : -1.;
  }

  // Use external shower for merging.
  //map<string,double> stateVars;
  //bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt, rec, "") : false;
  //if (isFSR)    stateVars = fsr->getStateVariables(event, rad,emt,rec, name);
  //else if (isr) stateVars = isr->getStateVariables(event, rad,emt,rec, name);
  //return ( (stateVars.size() > 0 && stateVars.find("t") != stateVars.end())
  //         ? sqrt(stateVars["t"]) : -1.0 );
  bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt, rec, "") : false;
  tEvol = (isFSR)
    ? fsr->kinRels->tEvol(event[rad],event[emt],event[rec])
    : isr->kinRels->tEvol(event[rad],event[emt],event[rec]);

  return tEvol>0. ? sqrt(tEvol) : -1.;

}

//--------------------------------------------------------------------------

// Function to compute "pythia pT separation" from Particle input

double DireHistory::pTLund(const Event& event, int rad, int emt1, int emt2,
  //int rec, string) {
  int rec, string name) {
  double ret = -1.;
  bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt1, rec, "") : false;
  if (isFSR) {
    ret = (emt2<0)
        ? fsr->kinRels->tEvolTimes(event[rad],event[emt1],event[rec])
        : fsr->kinRels->tEvolTimes(event[rad],event[emt1],event[emt2],
            event[rec]);

    if (emt2<0) {
      double tEvol = -1.;
      int evType
        = fsr->splits[name]->typeEvolutionMeasure();
      bool canUseSplitInfo
        = fsr->splits[name]->canUseForBranching();
      int idRadBef
        = fsr->splits[name]->radBefID(event[rad].id(), event[emt1].id());
      double mRes
        = particleDataPtr->m0(idRadBef);
      double m2Res = pow2(mRes);
      if (event[rad].isFinal() && canUseSplitInfo && evType!=0) {
        if (evType==2)
          tEvol = (event[rad].p() + event[emt1].p()).m2Calc() - m2Res;
        else if (evType==1)
          tEvol = (event[rad].p() + event[emt1].p()).m2Calc(); 
        else if (evType==-1)
          tEvol = pow2(max(0.,2.*mRes
                           -(event[rad].p() + event[emt1].p()).mCalc()));
        return tEvol>0. ? sqrt(tEvol) : -1.;
      }
    }

  } else if (isr) {
    ret = (emt2<0)
        ? isr->kinRels->tEvolSpace(event[rad],event[emt1],event[rec])
        : isr->kinRels->tEvolSpace(event[rad],event[emt1],event[emt2],
            event[rec]);
  }
  return (ret>0.) ? sqrt(ret) : 0.;
}

//--------------------------------------------------------------------------

// Function to return the position of the initial line before (or after)
// a single (!) splitting.

int DireHistory::posChangedIncoming(const Event& event, bool before) {

  // Check for initial state splittings.
  // Consider a splitting to exist if both mother and sister were found.
  // Find sister
  int iSister = 0;
  for (int i =0; i < event.size(); ++i)
    if (event[i].status() == 43) {
      iSister = i;
      break;
    }
  // Find mother
  int iMother = 0;
  if (iSister > 0) iMother = event[iSister].mother1();

  // Initial state splitting has been found.
  if (iSister > 0 && iMother > 0) {

    // Find flavour, mother flavour
    int flavSister  = event[iSister].id();
    int flavMother  = event[iMother].id();

    // Find splitting flavour
    int flavDaughter = 0;
    if ( abs(flavMother) < 21 && flavSister     == 21)
      flavDaughter = flavMother;
    else if ( flavMother     == 21 && flavSister     == 21)
      flavDaughter = flavMother;
    else if ( flavMother     == 21 && abs(flavSister) < 21)
      flavDaughter = -1*flavSister;
    else if ( abs(flavMother) < 21 && abs(flavSister) < 21)
      flavDaughter = 21;

    // Find initial state (!) daughter
    int iDaughter = 0;
    for (int i =0; i < event.size(); ++i)
      if ( !event[i].isFinal()
        && event[i].mother1() == iMother
        && event[i].id()      == flavDaughter )
        iDaughter = i;

    // Done for initial state splitting.
    if ( !before ) return iMother;
    else return iDaughter;

  }

  // Check for final state splittings with initial state recoiler.
  // Consider a splitting to exist if both mother and daughter were found.
  // Find new mother
  iMother = 0;
  for (int i =0; i < event.size(); ++i)
    if ( abs(event[i].status()) == 53 || abs(event[i].status()) == 54) {
      iMother = i;
      break;
    }
  // Find daughter
  int iDaughter = 0;
  if (iMother > 0) iDaughter = event[iMother].daughter1();

  // Done if final state splitting has been found.
  if (iDaughter > 0 && iMother > 0) {

    // Done for final state splitting.
    if ( !before ) return iMother;
    else return iDaughter;

  }

  // If no splitting has been found, return zero.
  return 0;

}

//--------------------------------------------------------------------------

vector<int> DireHistory::getSplittingPos(const Event& e, int type) {

  // Get radiators and recoilers before and after splitting.
  int iRadBef(-1), iRecBef(-1), iRadAft(-1), iEmt(-1), iRecAft(-1);
  // ISR
  if (type == 2) {
    // Loop through event to find new particles.
    for (int i = e.size() - 1; i > 0; i--) {
      if      ( iRadAft == -1 && e[i].status() == -41) iRadAft = i;
      else if ( iEmt    == -1 && e[i].status() ==  43) iEmt    = i;
      else if ( iRecAft == -1
             && (e[i].status() == -42 || e[i].status() == 48) ) iRecAft = i;
      if (iRadAft != -1 && iEmt != -1 && iRecAft != -1) break;
    }
    // Radiator before emission.
    iRadBef = (iRadAft > 0) ?  e[iRadAft].daughter2() : -1;
    // Recoiler before emission.
    iRecBef = (iRecAft > 0) ? (e[iRecAft].isFinal()
            ? e[iRecAft].mother1() : e[iRecAft].daughter1()) : -1;

  // FSR
  } else if (type >= 3) {

    // Recoiler after branching.
    if ( e[e.size() - 1].status() ==  52
      || e[e.size() - 1].status() == -53
      || e[e.size() - 1].status() == -54) iRecAft = (e.size() - 1);
    // Emission after branching.
    if ( e[e.size() - 2].status() == 51) iEmt = (e.size() - 2);
    // Radiator after branching.
    if ( e[e.size() - 3].status() == 51) iRadAft = (e.size() - 3);
    // Radiator before emission.
    iRadBef = (iRadAft > 0) ?  e[iRadAft].mother1() : -1;
    // Recoiler before emission.
    iRecBef = (iRecAft > 0) ? (e[iRecAft].isFinal()
            ? e[iRecAft].mother1() : e[iRecAft].daughter1()) : -1;
  }

  vector<int> ret;
  if ( iRadBef != -1
    && iRecBef != -1
    && iRadAft != -1
    && iEmt    != -1
    && iRecAft != -1)
    ret = createvector<int>(iRadBef)(iRecBef)(iRadAft)(iRecAft)(iEmt);

  return ret;

}

double DireHistory::pdfFactor( const Event&, const Event& e, const int type,
  double pdfScale, double mu ) {

  double wt = 1.;

  // Do nothing for MPI
  if (type < 2) return 1.0;  

  // Get radiators and recoilers before and after splitting.
  vector<int> splitPos = getSplittingPos(e, type);
  if (splitPos.size() < 5) return 1.0;
  int iRadBef = splitPos[0];
  int iRecBef = splitPos[1];
  int iRadAft = splitPos[2];
  int iRecAft = splitPos[3];

  bool useSummedPDF
    = mergingHooksPtr->settingsPtr->flag("ShowerPDF:useSummedPDF");

  // Final-final splittings
  if        ( e[iRadAft].isFinal() &&  e[iRecAft].isFinal() ) {
    return 1.0;

  // Final-initial splittings
  } else if ( e[iRadAft].isFinal() && !e[iRecAft].isFinal() ) {

    // Find flavour and x values.
    int flavAft    = e[iRecAft].id();
    int flavBef    = e[iRecBef].id();
    double xAft    = 2.*e[iRecAft].e() / e[0].e();
    double xBef    = 2.*e[iRecBef].e() / e[0].e();
    bool hasPDFAft = (particleDataPtr->colType(flavAft) != 0);
    bool hasPDFBef = (particleDataPtr->colType(flavBef) != 0);

    // Calculate PDF weight to reweight emission to emission evaluated at
    // constant factorisation scale. No need to include the splitting kernel in
    // the weight, since it will drop out anyway.
    int sideSplit = ( e[iRecAft].pz() > 0.) ? 1 : -1;
    double pdfDen1, pdfDen2, pdfNum1, pdfNum2;
    pdfDen1 = pdfDen2 = pdfNum1 = pdfNum2 = 1.;
    if ( sideSplit == 1 ) {
      pdfDen1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavBef, xBef, pow2(mu)) 
              : beamA.xfISR(0, flavBef, xBef, pow2(mu));
      pdfNum1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavBef, xBef, pow2(pdfScale)) 
              : beamA.xfISR(0, flavBef, xBef, pow2(pdfScale));
      pdfNum2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavAft, xAft, pow2(mu)) 
              : beamA.xfISR(0, flavAft, xAft, pow2(mu));
      pdfDen2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavAft, xAft, pow2(pdfScale)) 
              : beamA.xfISR(0, flavAft, xAft, pow2(pdfScale));
    } else {
      //pdfDen1 = beamB.xfISR(0, flavBef, xBef, pow2(mu));
      //pdfNum1 = beamB.xfISR(0, flavBef, xBef, pow2(pdfScale));
      //pdfNum2 = beamB.xfISR(0, flavAft, xAft, pow2(mu));
      //pdfDen2 = beamB.xfISR(0, flavAft, xAft, pow2(pdfScale));
      pdfDen1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavBef, xBef, pow2(mu)) 
              : beamB.xfISR(0, flavBef, xBef, pow2(mu));
      pdfNum1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavBef, xBef, pow2(pdfScale)) 
              : beamB.xfISR(0, flavBef, xBef, pow2(pdfScale));
      pdfNum2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavAft, xAft, pow2(mu)) 
              : beamB.xfISR(0, flavAft, xAft, pow2(mu));
      pdfDen2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavAft, xAft, pow2(pdfScale)) 
              : beamB.xfISR(0, flavAft, xAft, pow2(pdfScale));
    }
    wt = (pdfNum1/pdfDen1) * (pdfNum2)/(pdfDen2);

  // Initial-final splittings
  } else if ( !e[iRadAft].isFinal() &&  e[iRecAft].isFinal() ) {

    // Find flavour and x values.
    int flavAft    = e[iRadAft].id();
    int flavBef    = e[iRadBef].id();
    double xAft    = 2.*e[iRadAft].e() / e[0].e();
    double xBef    = 2.*e[iRadBef].e() / e[0].e();
    bool hasPDFAft = (particleDataPtr->colType(flavAft) != 0);
    bool hasPDFBef = (particleDataPtr->colType(flavBef) != 0);

    // Calculate PDF weight to reweight emission to emission evaluated at
    // constant factorisation scale. No need to include the splitting kernel in
    // the weight, since it will drop out anyway.
    int sideSplit = ( e[iRadAft].pz() > 0.) ? 1 : -1;
    double pdfDen1, pdfDen2, pdfNum1, pdfNum2;
    pdfDen1 = pdfDen2 = pdfNum1 = pdfNum2 = 1.;
    if ( sideSplit == 1 ) {
      pdfDen1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavBef, xBef, pow2(mu)) 
              : beamA.xfISR(0, flavBef, xBef, pow2(mu));
      pdfNum1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavBef, xBef, pow2(pdfScale)) 
              : beamA.xfISR(0, flavBef, xBef, pow2(pdfScale));
      pdfNum2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavAft, xAft, pow2(mu)) 
              : beamA.xfISR(0, flavAft, xAft, pow2(mu));
      pdfDen2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamA.xf(flavAft, xAft, pow2(pdfScale)) 
              : beamA.xfISR(0, flavAft, xAft, pow2(pdfScale));
    } else {
      //pdfDen1 = beamB.xfISR(0, flavBef, xBef, pow2(mu));
      //pdfNum1 = beamB.xfISR(0, flavBef, xBef, pow2(pdfScale));
      //pdfNum2 = beamB.xfISR(0, flavAft, xAft, pow2(mu));
      //pdfDen2 = beamB.xfISR(0, flavAft, xAft, pow2(pdfScale));
      pdfDen1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavBef, xBef, pow2(mu)) 
              : beamB.xfISR(0, flavBef, xBef, pow2(mu));
      pdfNum1 = (!hasPDFBef) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavBef, xBef, pow2(pdfScale)) 
              : beamB.xfISR(0, flavBef, xBef, pow2(pdfScale));
      pdfNum2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavAft, xAft, pow2(mu)) 
              : beamB.xfISR(0, flavAft, xAft, pow2(mu));
      pdfDen2 = (!hasPDFAft) ? 1.0 : (useSummedPDF)
              ? beamB.xf(flavAft, xAft, pow2(pdfScale)) 
              : beamB.xfISR(0, flavAft, xAft, pow2(pdfScale));
    }
    wt = (pdfNum1/pdfDen1) * (pdfNum2)/(pdfDen2);


  // Initial-initial splittings
  } else if ( !e[iRadAft].isFinal() && !e[iRecAft].isFinal() ) {

    // Find flavour and x values.
    int flavAft    = e[iRadAft].id();
    int flavBef    = e[iRadBef].id();
    double xAft    = 2.*e[iRadAft].e() / e[0].e();
    double xBef    = 2.*e[iRadBef].e() / e[0].e();
    //bool hasPDFAft = (particleDataPtr->colType(flavAft) != 0);
    //bool hasPDFBef = (particleDataPtr->colType(flavBef) != 0);

    // Calculate PDF weight to reweight emission to emission evaluated at
    // constant factorisation scale. No need to include the splitting kernel
    // in the weight, since it will drop out anyway.
    int sideSplit = ( e[iRadAft].pz() > 0.) ? 1 : -1;
    double ratio1 = getPDFratio( sideSplit, false, false, flavBef,
                      xBef, pdfScale, flavBef, xBef, mu );
    double ratio2 = getPDFratio( sideSplit, false, false, flavAft,
                      xAft, mu, flavAft, xAft, pdfScale );

    wt = ratio1*ratio2;

  }

  // Done
  return wt;
}

//--------------------------------------------------------------------------

// Function giving the product of splitting kernels and PDFs so that the
// resulting flavour is given by flav. This is used as a helper routine
// to dgauss

double DireHistory::integrand(int flav, double x, double scaleInt, double z) {

  // Declare constants
  //double CF = 4./3.;
  //double TR = 1./2.;
  //double CA = 3.;

  // Colour factors.
  double CA = mergingHooksPtr->settingsPtr->parm("DireColorQCD:CA") > 0.0
            ? mergingHooksPtr->settingsPtr->parm("DireColorQCD:CA") : 3.0;
  double CF = mergingHooksPtr->settingsPtr->parm("DireColorQCD:CF") > 0.0
            ? mergingHooksPtr->settingsPtr->parm("DireColorQCD:CF") : 4./3.;
  double TR = mergingHooksPtr->settingsPtr->parm("DireColorQCD:TR") > 0.
            ? mergingHooksPtr->settingsPtr->parm("DireColorQCD:TR") : 0.5;

  double result = 0.;

  // Integrate NLL sudakov remainder
  if (flav==0) {

    AlphaStrong* as = mergingHooksPtr->AlphaS_ISR();
    double asNow = (*as).alphaS(z);
    result = 1./z *asNow*asNow* ( log(scaleInt/z) -3./2. );

  // Integrand for PDF ratios. Careful about factors if 1/z, since formulae
  // are expressed in terms if f(x,mu), while Pythia uses x*f(x,mu)!
  } else if (flav==21) {

    double measure1 = 1./(1. - z);
    double measure2 = 1.;

    double integrand1 =
      2.*CA
      * z * beamB.xf( 21,x/z,pow(scaleInt,2))
          / beamB.xf( 21,x,  pow(scaleInt,2))
    - 2.*CA;

    double integrand2 =
      // G -> G terms
      2.*CA  *((1. -z)/z + z*(1.-z))
      * beamB.xf( 21,x/z,pow(scaleInt,2))
      / beamB.xf( 21,x,  pow(scaleInt,2))
      // G -> Q terms
    + CF * ((1+pow(1-z,2))/z)
      *( beamB.xf(  1, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf( -1, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf(  2, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf( -2, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf(  3, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf( -3, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf(  4, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2))
       + beamB.xf( -4, x/z,pow(scaleInt,2))
       / beamB.xf( 21, x,  pow(scaleInt,2)) );

    // Done
    result = integrand1*measure1 + integrand2*measure2;

  } else {

    double measure1 = 1./(1. -z);
    double measure2 = 1.;

    // Q -> Q terms
    double integrand1 =
      CF * (1+pow(z,2))
      * beamB.xf( flav, x/z, pow(scaleInt,2))
      / beamB.xf( flav, x,   pow(scaleInt,2))
    - 2.*CF;

    // Q -> G terms
    double integrand2 =
    + TR * (pow(z,2) + pow(1-z,2))
      * beamB.xf( 21,   x/z, pow(scaleInt,2))
      / beamB.xf( flav, x,   pow(scaleInt,2));

    // Done
    result = measure1*integrand1 + measure2*integrand2;
  }

  return result;

}

//--------------------------------------------------------------------------

// Check if an event reclustered into a 2 -> 2 dijet.
// (Only enabled if W reclustering is used).
bool DireHistory::isQCD2to2(const Event& event) {

  //if (!mergingHooksPtr->doWeakClustering()) return false;
  int nFinalPartons = 0, nFinal = 0;
  for (int i = 0;i < event.size();++i)
    if (event[i].isFinal()) {
      nFinal++;
      if (event[i].isParton() && !event[i].isDiquark())
        nFinalPartons++;
    }
  if (nFinalPartons == 2 && nFinal == 2) return true;
  else return false;

}

//--------------------------------------------------------------------------

// Check if an event reclustered into a 2 -> 1 Drell-Yan.
// (Only enabled if W reclustering is used).
bool DireHistory::isEW2to1(const Event& event) {

  //if (!mergingHooksPtr->doWeakClustering()) return false;
  int nVector = 0;
  for (int i = 0;i < event.size();++i) {
    if (event[i].isFinal()) {
      if (event[i].idAbs() == 23 ||
         event[i].idAbs() == 24 ||
         event[i].idAbs() == 22) nVector++;
      else return false;
    }
  }

  // Only true if a single vector boson as outgoing process.
  if (nVector == 1) return true;

  // Done
  return false;

}

//--------------------------------------------------------------------------

// Check if an event reclustered into massless 2 -> 2.

bool DireHistory::isMassless2to2(const Event& event) {

  int nFmassless(0), nFinal(0), nImassless(0);
  for (int i = 0;i < event.size();++i)
    if (event[i].isFinal()) {
      nFinal++;
      //if ( event[i].idAbs() < 10
      //  || event[i].idAbs() == 21
      if ((event[i].isParton() && !event[i].isDiquark())
        || event[i].idAbs() == 22) nFmassless++;
    } else if ( event[i].status() == -21 ) {
      //if ( event[i].idAbs() < 10
      //  || event[i].idAbs() == 21
      if ((event[i].isParton() && !event[i].isDiquark())
        || event[i].idAbs() == 22) nImassless++;
    }
  if (nFmassless == 2 && nFinal == 2 && nImassless == 2) return true;

  // Done
  return false;

}

//--------------------------------------------------------------------------

// Check if an event reclustered into DIS 2 -> 2.
bool DireHistory::isDIS2to2(const Event& event) {

  int nFpartons(0), nFleptons(0), nIpartons(0), nIleptons(0), nFinal(0);
  for (int i = 0;i < event.size();++i)
    if (event[i].isFinal()) {
      if ( event[i].isLepton() )     nFleptons++;
      if ( event[i].colType() != 0 ) nFpartons++;
      nFinal++;
    } else if ( event[i].status() == -21 ) {
      if ( event[i].isLepton() )     nIleptons++;
      if ( event[i].colType() != 0 ) nIpartons++;
    }
  bool isDIS =  nFinal == 2 && nFpartons == 1 && nFleptons == 1
             && nIpartons == 1 && nIleptons == 1;
  if (isDIS) return true;

  // Done.
  return false;
}

// Function to allow effective gg -> EW boson couplings.
bool DireHistory::mayHaveEffectiveVertex( string process, vector<int> in,
  vector<int> out) {

  if ( process.compare("ta+ta->jj") == 0 
    || process.compare("ta-ta+>jj") == 0 ) {
    int nInFermions(0), nOutFermions(0), nOutBosons(0);
    for (int i=0; i < int(in.size()); ++i)
      if (abs(in[i])<20) nInFermions++;
    for (int i=0; i < int(out.size()); ++i) {
      if (abs(out[i])<20) nOutFermions++;
      if (abs(out[i])>20) nOutBosons++;
    }
    return (nInFermions%2==0 && nOutFermions%2==0);
  }

  int nInG(0), nOutZ(0), nOutWp(0), nOutWm(0), nOutH(0), nOutA(0), nOutG(0);
  for (int i=0; i < int(in.size()); ++i)
    if (in[i]==21) nInG++;
  for (int i=0; i < int(out.size()); ++i) {
    if (out[i] == 21) nOutG++;
    if (out[i] == 22) nOutA++;
    if (out[i] == 23) nOutZ++;
    if (out[i] == 24) nOutWp++;
    if (out[i] ==-24) nOutWm++;
    if (out[i] == 25) nOutH++;
  }

  if ( nInG==2 && nOutWp+nOutWm > 0 && nOutWp+nOutWm == int(out.size())
    && nOutWp-nOutWm == 0)
    return true;
  if (nInG+nOutG>0 && nOutH > 0)
    return true;

  if ( process.find("Hinc") != string::npos
    && process.find("Ainc") != string::npos
    && (nOutH > 0 || nOutA%2==0) )
    return true;

  return false;
}

//--------------------------------------------------------------------------

// Set selected child indices.

void DireHistory::setSelectedChild() {

  if (mother == 0) return;
  if (!mother) return;
  if (mother==NULL) return;

  for (int i = 0;i < int(mother->children.size());++i)
    if (mother->children[i] == this) mother->selectedChild = i;
  if (mother) mother->setSelectedChild();
}

//--------------------------------------------------------------------------

// Store index of children that pass "trimHistories".

void DireHistory::setGoodChildren() {
  if (mother == 0 || !mother || mother==NULL) return;
  for (int i = 0;i < int(mother->children.size());++i)
    if (mother->children[i] == this) {
      // Nothing to be done if good child is already tagged.
      if (find(mother->goodChildIndex.begin(),mother->goodChildIndex.end(),i)
        != mother->goodChildIndex.end() ) continue;
     mother->goodChildIndex.push_back(i);
    }
  mother->setGoodChildren();
}

//--------------------------------------------------------------------------

// Store map of good siblings once good children have been determined.

void DireHistory::setGoodSisters() {

  for (int i = 0;i < int(goodChildIndex.size());++i) {
    for (int j = 0;j < int(goodChildIndex.size());++j) {
      if(find(
           children[goodChildIndex[i]]->goodSisters.begin(),
           children[goodChildIndex[i]]->goodSisters.end(),
           children[goodChildIndex[j]])
           != children[goodChildIndex[i]]->goodSisters.end()) continue;
      children[goodChildIndex[i]]->goodSisters.push_back(
        children[goodChildIndex[j]]);
    }
    children[goodChildIndex[i]]->setGoodSisters();
  }
  if (!mother) goodSisters.push_back(this);

}

//--------------------------------------------------------------------------

// List matrix elements for states in history.

void DireHistory::printMECS() {

  if ( !mother && children.size() > 0 && (MECnum/MECden > 1e2 )) {
    cout << scientific << setprecision(4);
    listFlavs(state);
    cout << " " << goodChildIndex.size() << " num " << MECnum
         << " den " << MECden << endl;
  }
  if (mother ) mother->printMECS();
  return;

}

//--------------------------------------------------------------------------

bool fuzzyLarger (double left, double right) {
  double norm = min(left,right);
  if (norm<=0.) norm = max(left,right);
  if (norm<=0.) norm = 1.;
  //if ( left > right || abs(left-right)/norm < 1e-6) return true;
  //if (left > right || abs(left-right)/norm < 1e-1) return true;
  if (left > right || abs(left-right)/norm < 1e-2) return true;
  return false;
}

//--------------------------------------------------------------------------

bool DireHistory::isOrderedBranching(DireHistory* childNow,
  DireHistory* sisterNow) {

  // Always ordered if branching in child node happens at larger scale than
  // branching in mother node.
  if (fuzzyLarger(childNow->clusterIn.pT(), sisterNow->clusterIn.pT()))
    return true;

  // Always ordered if branching is a resonance decay.
  /*string name  = childNow->clusterIn.name();
  int evType   = fsr->splits[name]->typeEvolutionMeasure();
  double tEvol = pow2(childNow->clusterIn.pT());
  double mRes = particleDataPtr->m0(
    childNow->clusterIn.flavRadBef);*/
  string name  = sisterNow->clusterIn.name();
  int evType   = fsr->splits[name]->typeEvolutionMeasure();
  double tEvol = pow2(sisterNow->clusterIn.pT());
  double mRes = particleDataPtr->m0(
    sisterNow->clusterIn.flavRadBef);
  double m2Res = pow2(mRes);
  if (abs(evType)==1 && tEvol < 4.*m2Res && tEvol > m2Res) return true;

  return false;

}

//--------------------------------------------------------------------------

void DireHistory::setProbabilities() {

  for ( map<int, vector<DireHistory*> >::iterator it
    = generations.begin(); it != generations.end(); ++it ) {
    for (size_t i=0; i< it->second.size(); ++i) {
      DireHistory* sisterNow = (it->second)[i];
      bool foundOrdered=false;
      double denominator=0.;
      double contrib=0.;
      double denominator_unconstrained=0.;
      double contrib_unconstrained=0.;

      // Nothing to be done for lowest multiplicity nodes.
      if ( sisterNow->children.empty()) continue;

      // Do nothing if no ME found for this node.
      if (sisterNow->MECnum == 1.) {
        sisterNow->MECden = sisterNow->MECcontrib = 1.0;
        continue;
      }

      for (int j = 0;j < int( sisterNow->goodChildIndex.size());++j) {
        DireHistory* childNow
          = sisterNow->children[sisterNow->goodChildIndex[j]];
        // Get probability, multiply with ME and coupling.
        double bareProb = getBareProb(childNow);
        double dd = bareProb
                  * childNow->MECnum
                  / childNow->MECden
                  * childNow->MECcontrib;
        dd *= childNow->clusterCoupl * 2. * M_PI;
        if (childNow->clusterIn.emt2Pos>0) dd *= 2. * M_PI;
        denominator_unconstrained += dd;

        fsr->direInfoPtr->message(1)
        << " " <<
         bareProb
        << " " <<
        childNow->MECnum
        << " " <<
        childNow->MECden
        << " " <<
        childNow->MECcontrib
        << " " <<
        childNow->clusterCoupl
        << " " << 
        childNow->goodChildIndex.size()
        << " " <<
        isOrderedBranching(childNow, sisterNow)
        <<endl;

        // Remember if this child contributes to the next-higher denominator.
        //if ( childNow->clusterIn.pT() > sisterNow->clusterIn.pT()
        //  || abs(childNow->clusterIn.pT() - sisterNow->clusterIn.pT())
        //     / min(childNow->clusterIn.pT(),sisterNow->clusterIn.pT()) < 1e-8){
        //if (fuzzyLarger(childNow->clusterIn.pT(), sisterNow->clusterIn.pT())) {
        if (isOrderedBranching(childNow, sisterNow)) {
          contrib_unconstrained += dd;
          foundOrdered=true;
        }

        // Careful about first emissions above the factorization scale.
        if ( int(childNow->goodChildIndex.size()) == 0
          //&& hardStartScale(childNow->state) > childNow->clusterIn.pT()) {
          && fuzzyLarger(hardStartScale(childNow->state),
             childNow->clusterIn.pT()) ) {
          denominator += dd;
          //if (childNow->clusterIn.pT() > sisterNow->clusterIn.pT())
          //if (fuzzyLarger(childNow->clusterIn.pT(), sisterNow->clusterIn.pT()))
          if (isOrderedBranching(childNow, sisterNow))
            contrib += dd;
        } else if (int(childNow->goodChildIndex.size()) > 0) {
          denominator += dd;
          //if (childNow->clusterIn.pT() > sisterNow->clusterIn.pT())
         //if (fuzzyLarger(childNow->clusterIn.pT(), sisterNow->clusterIn.pT()))
          if (isOrderedBranching(childNow, sisterNow))
            contrib += dd;
        }

        //fsr->direInfoPtr->eatCout();
        //childNow->clusterIn.list();
        //sisterNow->clusterIn.list();
        //fsr->direInfoPtr->freeCout();

        /*fsr->direInfoPtr->message(1)
        << scientific << setprecision(10)
        << " " << setw(25) << childNow->clusterIn.name()
        //<< " " << stringFlavs(childNow->state)
        << " pTchild  " << childNow->clusterIn.pT() //<< " " << childNow->scale
        //<< " " << stringFlavs(sisterNow->state)
        << " pTsister " << sisterNow->clusterIn.pT() //<< " " << sisterNow->scale
        << " hardpT   " << hardStartScale(childNow->state)
        << " dd       " << dd
        << " contrib  " << contrib
        << endl;*/

        fsr->direInfoPtr->message(1)
        << "Add"
        //<< " " << setw(6) << childNow->clusterIn.radPos
        //<< " " << setw(6) << childNow->clusterIn.emt1Pos
        //<< " " << setw(6) << childNow->clusterIn.recPos
        << " " << setw(23) << childNow->clusterIn.name()
        << " prob=" << setw(10) << bareProb
        << " coup=" << childNow->clusterCoupl*2.*M_PI
        << " ME  =" << setw(10) << childNow->MECnum
        //<< " contribNow=" << contrib
        //<< " contrib=" << childNow->MECcontrib
        << " denom=" << childNow->MECden
        << " contrib/denom=" << childNow->MECcontrib/childNow->MECden
        << " dd  =" << dd << " to MEC denominator: "
        << denominator
        //<< " contrib " << contrib
        << " at child pT2 " << pow2(childNow->clusterIn.pT())
        << " sister pT2 " << pow2(sisterNow->clusterIn.pT())
        << endl;
        //if (childNow->MECnum>1e3)
        //  fsr->direInfoPtr->message(1)
        //  << fsr->evtUtils->listEvent(childNow->state)
        //  << fsr->evtUtils->printSIJstring(childNow->state)
        //  << endl;
      }

      // Update ME correction pieces in sister node.
      if (sisterNow->goodChildIndex.size() > 0) {
        if (denominator != 0.0) sisterNow->MECden = denominator;
        sisterNow->MECcontrib = contrib;
        if (denominator == 0. && contrib == 0.) {
          if (denominator_unconstrained != 0.0) 
            sisterNow->MECden = denominator_unconstrained;
          sisterNow->MECcontrib = contrib_unconstrained;
        }
        if (!foundOrdered) sisterNow->foundOrderedChildren = false;
      }

    // Now we could again shower the decay system.
      //fsr->direInfoPtr->eatCout();
      fsr->direInfoPtr->message(1)
      //cout 
      << "Current MEC for state "
      << stringFlavs(sisterNow->state)
      //<< fsr->evtUtils->listEvent(sisterNow->state)
      //<< fsr->evtUtils->printSIJstring(sisterNow->state)
      //<< endl;
      //sisterNow->state.list();
      //fsr->direInfoPtr->message(1)
      //cout
      << " MEC : " << sisterNow->MECnum << " / " << sisterNow->MECden
      << " = " << sisterNow->MECnum / sisterNow->MECden
      << endl;
      //fsr->direInfoPtr->freeCout();

    }

  }

  return;

}

//--------------------------------------------------------------------------

void DireHistory::setProbabilitiesOld() {

  for (int i = 0;i < int(goodSisters.size());++i) {

    DireHistory* sisterNow = goodSisters[i];
    bool foundOrdered=false;
    double denominator=0.;
    double contrib=0.;
    double denominator_unconstrained=0.;
    double contrib_unconstrained=0.;

    // Do nothing if no ME found for this node.
    if (sisterNow->MECnum == 1.) { MECden = MECcontrib = 1.0; continue; }

    for (int j = 0;j < int(sisterNow->goodChildIndex.size());++j) {

      DireHistory* childNow=sisterNow->children[sisterNow->goodChildIndex[j]];

      // Get clustering variables.
      int rad = childNow->clusterIn.radPos;
      int emt1 = childNow->clusterIn.emt1Pos;
      int emt2 = childNow->clusterIn.emt2Pos;
      int rec = childNow->clusterIn.recPos;

      const Particle* radPart  = childNow->clusterIn.radSave;
      const Particle* emt1Part = childNow->clusterIn.emt1Save;
      const Particle* emt2Part = childNow->clusterIn.emt2Save;
      const Particle* recPart  = childNow->clusterIn.recSave;

      double virtuality = 2.*childNow->clusterIn.rad()->p()*
                              childNow->clusterIn.emt1()->p();
      if (emt2>0) virtuality
        += 2.*childNow->clusterIn.rad()->p()*childNow->clusterIn.emt2()->p()
         + 2.*childNow->clusterIn.emt1()->p()*childNow->clusterIn.emt2()->p();

      bool isFSR = (fsr)
        ? fsr->isTimelike(sisterNow->state, rad, emt1, rec, "") : false;
      //bool isISR = (isr)
      //  ? isr->isSpacelike(sisterNow->state, rad, emt1, rec, "") : false;
      //map<string,double> stateVars;
      //if (isFSR)
      //  stateVars = fsr->getStateVariables(sisterNow->state,rad,emt1,rec,"");
      //else if (isISR)
      //  stateVars = isr->getStateVariables(sisterNow->state,rad,emt1,rec,"");

      double z = (!radPart->isFinal())
        //? stateVars["z"]
        ? isr->kinRels->zEvol(*radPart, *emt1Part, *recPart)
        : ( (emt2<0) ? fsr->kinRels->zTimes( *radPart, *emt1Part, *recPart)
                     : fsr->kinRels->zTimes( *radPart, *emt1Part, *emt2Part, *recPart));
      double t   = pow2(childNow->clusterIn.pT());
      double Q2  = pow2(childNow->clusterIn.mass());
      double xCS = 1.;
      // For splittings with initial-state particles, remember initial
      // momentum rescaling.
      if        ( !isFSR && !sisterNow->state[rec].isFinal() ) {
        double kappa2 = t/Q2;
        xCS = (z*(1-z) - kappa2) / (1 -z);
      } else if ( !isFSR &&  sisterNow->state[rec].isFinal() ) {
        xCS = z;
      } else if (  isFSR && !sisterNow->state[rec].isFinal() ) {
        double tDire = t;
        if (fsr->kinRels->ISRevolutionMode==1)
          tDire = fsr->kinRels->t_fi_dire_from_cs(z, t, Q2);
        double kappa2 = tDire/Q2;
        xCS    = 1 - kappa2/(1.-z);
        if (abs(Q2) < 1e-5) xCS = 1.;
      }

      // Construct next component of the denominator. Note that the naive
      // splitting probability is vanishing belowthe PS cut-off.
      double probNow = childNow->clusterProb;

      //// Disallow below cut-off.
      //if (isFSR) {
      //  if (fsr->pT2cut(sisterNow->state[emt1].id()) > t)
      //    probNow = 0.;
      //  if (!fsr->splits[childNow->clusterIn.name()]->aboveCutoff( t,
      //       sisterNow->state[rad], sisterNow->state[rec], 0,
      //       mergingHooksPtr->partonSystemsPtr))
      //    probNow = 0.;
      //} else if (isISR) {
      //}

      double dd = childNow->MECnum
                // * abs(childNow->clusterProb)
                * probNow
                // clusterProb includes 1/pT2, but here, we only want
                // the propagator factor 1/(2.*pipj)
                * t / virtuality
                // extra factor left-over from 8*Pi*alphaS of dipole ME
                // factorization:
                // |Mn+1|^2 ~ 8*Pi*alphaS*1/(2.pipj)*1/x*dipole*|Mn|^2
                //          = 2g^2 *1/(2.pipj)*1/x*dipole*|Mn|^2
                //          compared with using g^2=1 in MG5 MEs.
                // * 2.
                // Part of the definition of dipole factorization.
                * 1 / xCS
                / childNow->MECden * childNow->MECcontrib;

      // Multiply coupling.
      dd *= childNow->clusterCoupl * 2. * M_PI * 8. * M_PI;
      if (emt2>0) dd *= t / virtuality * 2. * M_PI * 8. * M_PI;

      //fsr->direInfoPtr->message(1)
      //<<  __func__ << " " << __LINE__
      //<< " Add " << childNow->clusterIn.name()
      //<< " [" << rad << " " << emt1 << " " << emt2 << " " << rec << "]"
      //<< " to MEC denom. for " << stringFlavs(childNow->state)
      //<< " -->> " << stringFlavs(sisterNow->state) << " den="
      //<< denominator_unconstrained << " " << dd
      //<< " . Rate: "
      //<< childNow->clusterProb << " " << probNow << " above cut? "
      //<< (fsr->pT2cut(sisterNow->state[emt1].id()) < t) << " "
      //<< fsr->splits[childNow->clusterIn.name()]->aboveCutoff( t,
      //        sisterNow->state[rad], sisterNow->state[rec], 0,
      //        mergingHooksPtr->partonSystemsPtr)
      //<< " at scale " << childNow->clusterIn.pT() << endl;

      denominator_unconstrained += dd;

      // Remember if this child contributes to the next-higher denominator.
      if (childNow->clusterIn.pT() > sisterNow->clusterIn.pT()) {
        contrib_unconstrained += dd;
        foundOrdered=true;
      }

      // Careful about first emissions above the factorization scale.
      if ( int(childNow->goodChildIndex.size()) == 0
        && hardStartScale(childNow->state) > childNow->clusterIn.pT()) {
        denominator += dd;
        if (childNow->clusterIn.pT() > sisterNow->clusterIn.pT())
          contrib += dd;
      } else if (int(childNow->goodChildIndex.size()) > 0) {
        denominator += dd;
        if (childNow->clusterIn.pT() > sisterNow->clusterIn.pT())
          contrib += dd;
      }

    }

    // Update ME correction pieces in sister node.
    if (sisterNow->children.size() > 0) {
      if (denominator != 0.0) goodSisters[i]->MECden = denominator;
      goodSisters[i]->MECcontrib = contrib;
      if (denominator == 0. && contrib == 0.) {
        if (denominator_unconstrained != 0.0) 
          goodSisters[i]->MECden = denominator_unconstrained;
        goodSisters[i]->MECcontrib = contrib_unconstrained;
      }

      if (!foundOrdered) goodSisters[i]->foundOrderedChildren = false;

      //fsr->direInfoPtr->message(1)
      //<< "Current MEC for state "
      //<< stringFlavs(sisterNow->state) << endl;
      //fsr->direInfoPtr->message(1)
      //<< " MEC : " << goodSisters[i]->MECnum << " " << goodSisters[i]->MECden
      //<< " -->> " << goodSisters[i]->MECnum / goodSisters[i]->MECden
      //<< endl;

    }

  }

  if (mother) mother->setProbabilities();

  return;

}

//--------------------------------------------------------------------------

void DireHistory::setEffectiveScales() {

  for ( map<int, vector<DireHistory*> >::iterator it
    = generations.begin(); it != generations.end(); ++it ) {
    for (size_t i=0; i< it->second.size(); ++i) {
      DireHistory* auntNow = (it->second)[i];
      if ( auntNow->children.empty()) { 
        auntNow->scaleEffective = scale;
        continue;
      } else {
        double tmax(0.), tmin(1e15);
        double alphasOftEff_num(0.), alphasOftEff_den(0.);
        bool set = false;
        for (int j = 0;j < int( auntNow->goodChildIndex.size());++j) {
          DireHistory* childNow=auntNow->children[auntNow->goodChildIndex[j]];
          double scale2_coupling = pow2(childNow->clusterIn.pT());
          pair<double,double> blub
            = childNow->getEffCouplNumDen(childNow, scale2_coupling);

          // Do not include this transition in the overall rate, if
          // the splitting would have been below the PS cut-off.
          if (scale2_coupling<pow2(mergingHooksPtr->pTcut())) continue;

          tmax = max(tmax,scale2_coupling);
          tmin = min(tmin,scale2_coupling);
          alphasOftEff_num += blub.first;
          alphasOftEff_den += blub.second;
          if (alphasOftEff_num != 0.) set = true;
        }

        if (!set) {
          auntNow->scaleEffective = 0.;
          auntNow->couplEffective = 0.;
          continue;
        }

        // Set the effective scale for currect history.
        double alphasOftEffRatio = alphasOftEff_num/alphasOftEff_den;
        double teff = auntNow->calculateEffectiveScale(tmin, tmax,
          alphasOftEffRatio);
        auntNow->scaleEffective = sqrt(teff);
        auntNow->couplEffective = alphasOftEffRatio;

      }
    }
  }

}

//--------------------------------------------------------------------------

double DireHistory::getBareProb( DireHistory* childNow) {

  // Scale with correct coupling factor.
  double tEvol(pow2(childNow->clusterIn.pT()));
  int emt2                 = childNow->clusterIn.emt2Pos;
  const Particle* radPart  = childNow->clusterIn.radSave;
  const Particle* emt1Part = childNow->clusterIn.emt1Save;
  const Particle* emt2Part = childNow->clusterIn.emt2Save;
  const Particle* recPart  = childNow->clusterIn.recSave;
  double virtuality        = 2.*childNow->clusterIn.rad()->p()*
                                childNow->clusterIn.emt1()->p();
  if (emt2>0) virtuality
    += 2.*childNow->clusterIn.rad()->p()*childNow->clusterIn.emt2()->p()
    + 2.*childNow->clusterIn.emt1()->p()*childNow->clusterIn.emt2()->p();

  if (radPart->isFinal()) {
    Vec4 pij = childNow->clusterIn.rad()->p()+childNow->clusterIn.emt1()->p();
    if (emt2>0) pij += childNow->clusterIn.emt2()->p();
    double m2ij = pow2(particleDataPtr->m0(childNow->clusterIn.flavRadBef));
    virtuality = pij.m2Calc() - m2ij; 
  }

  //fsr->direInfoPtr->message(1)
  //<< __func__ << " " << __LINE__ << " " << childNow << " " << childNow->clusterIn.name()
  //<< " t=" << sqrt(tEvol) << " " << tEvol
  //<< endl;

  bool isFSR = (fsr) ? radPart->isFinal() : false;

  double z = (!radPart->isFinal())
    ? isr->kinRels->zEvol(*radPart,*emt1Part, *recPart)
    : ( (emt2<0)
      ? fsr->kinRels->zTimes( *radPart, *emt1Part, *recPart)
      : fsr->kinRels->zTimes( *radPart, *emt1Part, *emt2Part, *recPart));
  //double z   = childNow->clusterIn.z();
  double Q2  = pow2(childNow->clusterIn.mass());
  double xCS = 1.;
  // For splittings with initial-state particles, remember initial
  // momentum rescaling.
  if        ( !isFSR && !recPart->isFinal() ) {
    double kappa2 = tEvol/Q2;
    xCS = (z*(1-z) - kappa2) / (1 -z);
  } else if ( !isFSR &&  recPart->isFinal() ) {
    xCS = z;
  } else if (  isFSR && !recPart->isFinal() ) {
    double tDire  = tEvol;
    if (fsr->kinRels->ISRevolutionMode==1)
      tDire = fsr->kinRels->t_fi_dire_from_cs(z, tEvol, Q2);
    double kappa2 = tDire/Q2;
    xCS    = 1 - kappa2/(1.-z);
    if (abs(Q2) < 1e-5) xCS = 1.;
    //fsr->direInfoPtr->message(1)
    //<< fsr->kinRels->ISRevolutionMode
    //<< " tDire " << sqrt(tDire) << " pT " << sqrt(t)
    //<< " x " << xCS 
    //<< endl;
  }

  string name  = childNow->clusterIn.name();
  int evType           = fsr->splits[name]->typeEvolutionMeasure();
  bool canUseSplitInfo = fsr->splits[name]->canUseForBranching();
  double mRes = particleDataPtr->m0(
    childNow->clusterIn.flavRadBef);
  double m2Res = pow2(mRes);
  int type     = recPart->isFinal() ? 1 : -1;

  //if (isFSR && !recPart->isFinal() && evType!=0) {
  if (isFSR && !recPart->isFinal() && abs(evType)==1) {
    double virt = (evType > 0
      ? tEvol : pow2(2.*mRes-sqrt(tEvol)) );
    xCS = Q2/(Q2+virt);
  }

  if (isFSR && !recPart->isFinal() && evType==2) {
    double virt = tEvol + m2Res;
    xCS = Q2/(Q2+virt);
  }

  fsr->splits[name]->splitInfo.save();
  fsr->splits[name]->splitInfo.clear();
  fsr->splits[name]->splitInfo.storeInfo(name, type, 0, 0, 0, 
    childNow->clusterIn.radBef, childNow->clusterIn.recBef, childNow->state,
    emt1Part->id(), radPart->id(),
    1, Q2, tEvol, tEvol, z, 0.0, m2Res, 0.,
    0., 0., 0.0, 0.0, 0.0, 0.0, 0., 0.);
  fsr->splits[name]->splitInfo.setSiblings(DireSingleColChain());

  double massJacobian = (canUseSplitInfo)
    ? fsr->splits[name]->getJacobian(childNow->state) : 1.;
  fsr->splits[name]->splitInfo.clear();
  fsr->splits[name]->splitInfo.restore();

  // clusterProb includes 1/pT2, but here, we only want
  // the propagator factor 1/(2.*pipj)
  // (we will want to choose an effective scale by solving
  // as(teff) = (sum of kernel*propagator*MEC) . Note that we DO NOT
  // include the Jacobian here, and consequently have to remove its
  // contribution from clusterProb.)
  double normToVirtuality = tEvol / virtuality;
  //if (evType!=0 || (evType==0 && abs(childNow->clusterIn.flavRadBef)>1000))
  if (evType==2 || abs(evType)==1)
    normToVirtuality = 1.;

  double prob =
    childNow->clusterProb
    * normToVirtuality
    // Part of the definition of initial-state factorization.
    * 1 / xCS
    // Multiply with factor 8*Pi left-over from dipole ME factorization:
    // |Mn+1|^2 ~ 8*Pi*alphaS*1/(2.pipj)*1/x*dipole*|Mn|^2
    //          = 2g^2 *1/(2.pipj)*1/x*dipole*|Mn|^2
    //          compared with using g^2=1 in MG5 MEs.
    * 8. * M_PI;

  if (emt2>0) prob *= normToVirtuality * 8. * M_PI;

  // Remove jacobian from massive CDST phase space.
  prob *= 1./massJacobian;

  //fsr->direInfoPtr->message(1)
  //<< childNow->clusterIn.name()
  //<< " " << childNow->clusterIn.radPos
  //<< " " << childNow->clusterIn.emt1Pos
  //<< " virt " << sqrt(virtuality) << " pT " << sqrt(t)
  //<< " z " << z 
  //<< endl;

  fsr->direInfoPtr->message(1)
  << __func__ << " " << __LINE__ << " " << childNow->clusterIn.name()
  << ( (recPart->isFinal() && radPart->isFinal()) ? " FF"
       : (!recPart->isFinal() && radPart->isFinal()) ? " FI"
       : (recPart->isFinal() && !radPart->isFinal()) ? " IF" : " II")
  << " t=" << tEvol
  << " z=" << z
  << " q2=" << virtuality 
  //<< " 1/x=" << 1/xCS 
  << " n=" << normToVirtuality
  << " 1/j=" << 1/massJacobian
  << " p=" << childNow->clusterProb
  << " prob=" << prob
  << endl;

  // Done.
  return prob;

}

//--------------------------------------------------------------------------

pair<double,double> DireHistory::getEffCouplNumDen( DireHistory* childNow,
  double& scale2_coupling) {

  // Scale with correct coupling factor.
  double t(pow2(childNow->clusterIn.pT()));
  int emt2                 = childNow->clusterIn.emt2Pos;
  const Particle* radPart  = childNow->clusterIn.radSave;
  const Particle* emt1Part = childNow->clusterIn.emt1Save;
  const Particle* emt2Part = childNow->clusterIn.emt2Save;
  const Particle* recPart  = childNow->clusterIn.recSave;
  //double virtuality        = 2.*childNow->clusterIn.rad()->p()*
  //                              childNow->clusterIn.emt1()->p();
  //if (emt2>0) virtuality
  //  += 2.*childNow->clusterIn.rad()->p()*childNow->clusterIn.emt2()->p()
  //  + 2.*childNow->clusterIn.emt1()->p()*childNow->clusterIn.emt2()->p();

  bool isFSR = (fsr) ? radPart->isFinal() : false;

  double z = (!radPart->isFinal())
    ? isr->kinRels->zEvol(*radPart,*emt1Part, *recPart)
    : ( (emt2<0)
      ? fsr->kinRels->zTimes( *radPart, *emt1Part, *recPart)
      : fsr->kinRels->zTimes( *radPart, *emt1Part, *emt2Part, *recPart));
  double Q2  = pow2(childNow->clusterIn.mass());

  double prob = abs(getBareProb(childNow));

  // Get running coupling and its argument.
  string name = childNow->clusterIn.name();
  double running_coupling = (isFSR)
    ? fsr->splits[name]->coupling (z, t, Q2, -1., 
        make_pair(radPart->id(), radPart->isFinal()),
        make_pair(recPart->id(), recPart->isFinal()))
    : isr->splits[name]->coupling (z, t, Q2, -1., 
        make_pair(radPart->id(), radPart->isFinal()),
        make_pair(recPart->id(), recPart->isFinal()));
  running_coupling *= 2. * M_PI;
  scale2_coupling = (isFSR)
    ? fsr->splits[name]->couplingScale2 (z, t, Q2, 
        make_pair(radPart->id(), radPart->isFinal()),
        make_pair(recPart->id(), recPart->isFinal()))
    : isr->splits[name]->couplingScale2 (z, t, Q2, 
        make_pair(radPart->id(), radPart->isFinal()),
        make_pair(recPart->id(), recPart->isFinal()));
  if (scale2_coupling< 0.) scale2_coupling = t;
  //if (emt2>0) prob *= t/virtuality*8.*M_PI;
  if (emt2>0) running_coupling *= 2.*M_PI;

  // Include alphaS at effective scale of previous order.
  double alphasOftEff_num = prob * childNow->MECnum
                    * childNow->couplEffective
                    * running_coupling;
  double alphasOftEff_den = prob * childNow->MECnum;

  // Done.
  return make_pair(alphasOftEff_num,alphasOftEff_den);

}

//--------------------------------------------------------------------------

double DireHistory::calculateEffectiveScale( double tmin, double tmax,
  double alphasOftEffRatio) {

  double tmincut = pow2(mergingHooksPtr->pTcut());
  double tmaxcut = pow2(infoPtr->eCM());

  // Force scales to be equal if too identical, so that we'll later on simply
  // pick the single scale.
  if (abs(tmax-tmin)/tmax < 1e-4) tmin = tmax;

  // Calculate the effective scale.
  // Note: For negative probabilities, it might be necessary to increase the
  // scale range for root finding.
  CouplFunction  couplFunc(  mergingHooksPtr->AlphaS_FSR(),
    //couplingPowCount["qcd"], mergingHooksPtr->AlphaEM_FSR(),
    //couplingPowCount["qed"]);
    couplingPowCount[QCD], mergingHooksPtr->AlphaEM_FSR(),
    couplingPowCount[QED]);

  // The algorithm fails for tmin < 1. or if tmax is too close
  // to tmin. These values can give reasonable results most
  // of the time.
  tmin=max(tmin,tmincut);
  //tmin=max(tmin,1.);
  tmax=max(tmax,1.03);

  // Adjust lower and upper scale in case the current values
  // are too restrictive to find a sensible effective scale.
  double as_tmin = couplFunc.f(tmin,vector<double>());
  double as_tmax = couplFunc.f(tmax,vector<double>());
  double headroom = 1.;
  bool failed = false;
  int ntried = 0;
  while ( tmin < tmax
    && ( ( as_tmin-alphasOftEffRatio > 0
        && as_tmax-alphasOftEffRatio > 0)
      || ( as_tmin-alphasOftEffRatio < 0
        && as_tmax-alphasOftEffRatio < 0))) {
    ntried++;
    if (pow(tmax, headroom)>tmaxcut || ntried>1000) {
      failed = true;
      break;
    }
    headroom *= 1.005;
    if (tmin>1.) as_tmin = couplFunc.f(pow(tmin,1./headroom),vector<double>());
    as_tmax = couplFunc.f(pow(tmax, headroom),vector<double>());
  }
  double tminNow = (tmin>1.) ? pow(tmin,1./headroom) : tmin;
  double tmaxNow = (tmax>1.) ? min(tmaxcut,pow(tmax,headroom)) : tmax;
  if (failed) {
    tminNow = 0.5;//tmincut;
    tmaxNow = tmaxcut;
    failed = false;
  }

  // Now find effective scale.
  double teff = 0.;
  DireRootFinder direRootFinder;
  if  (abs(tmaxNow-tminNow)/tmaxNow < 1e-4) teff = tmaxNow;
  else teff = direRootFinder.findRoot1D( &couplFunc, tminNow, tmaxNow,
    alphasOftEffRatio, vector<double>(), 100);
  if (std::isnan(teff)) teff = 0.;

  // Done.
  return (teff>tmincut) ? teff : 0.;

}

//--------------------------------------------------------------------------

void DireHistory::setEffectiveScalesOld() {

  for (int i = 0;i < int(goodSisters.size());++i) {

    DireHistory* sisterNow = goodSisters[i];

    // Nothing to do if there are no children.
    if (sisterNow->goodChildIndex.size()==0) continue;

    double alphasOftEff_num(0.), alphasOftEff_den(0.), tmin(1e15), tmax(-1.0);

    for (int j = 0;j < int(sisterNow->goodChildIndex.size());++j) {

      DireHistory* childNow=sisterNow->children[sisterNow->goodChildIndex[j]];

      /*// Scale with correct coupling factor.
      double t(pow2(childNow->clusterIn.pT()));
      int rad                  = childNow->clusterIn.radPos;
      int emt1                 = childNow->clusterIn.emt1Pos;
      int emt2                 = childNow->clusterIn.emt2Pos;
      int rec                  = childNow->clusterIn.recPos;
      const Particle* radPart  = childNow->clusterIn.radSave;
      const Particle* emt1Part = childNow->clusterIn.emt1Save;
      const Particle* emt2Part = childNow->clusterIn.emt2Save;
      const Particle* recPart  = childNow->clusterIn.recSave;
      double virtuality        = 2.*childNow->clusterIn.rad()->p()*
                                    childNow->clusterIn.emt1()->p();
      if (emt2>0) virtuality
        += 2.*childNow->clusterIn.rad()->p()*childNow->clusterIn.emt2()->p()
         + 2.*childNow->clusterIn.emt1()->p()*childNow->clusterIn.emt2()->p();

      bool isFSR = (fsr)
        ? fsr->isTimelike(sisterNow->state, rad, emt1, rec, "")
        : false;
      //bool isISR = (isr) ? isr->isSpacelike(sisterNow->state, rad, emt1, rec, "") : false;
      //map<string,double> stateVars;
      //if (isFSR)      stateVars = fsr->getStateVariables(sisterNow->state,rad,emt1,rec,"");
      //else if (isISR) stateVars = isr->getStateVariables(sisterNow->state,rad,emt1,rec,"");

      double z = (!radPart->isFinal())
        //? stateVars["z"]
        ? isr->kinRels->zEvol(*radPart,*emt1Part, *recPart)
        : ( (emt2<0)
          ? fsr->kinRels->zTimes( *radPart, *emt1Part, *recPart)
          : fsr->kinRels->zTimes( *radPart, *emt1Part, *emt2Part, *recPart));
      double Q2  = pow2(childNow->clusterIn.mass());
      double xCS = 1.;
      // For splittings with initial-state particles, remember initial
      // momentum rescaling.
      if        ( !isFSR && !sisterNow->state[rec].isFinal() ) {
        double kappa2 = t/Q2;
        xCS = (z*(1-z) - kappa2) / (1 -z);
      } else if ( !isFSR &&  sisterNow->state[rec].isFinal() ) {
        xCS = z;
      } else if (  isFSR && !sisterNow->state[rec].isFinal() ) {
        double tDire  = t;
        if (fsr->kinRels->ISRevolutionMode==1)
          tDire = fsr->kinRels->t_fi_dire_from_cs(z, t, Q2);
        double kappa2 = tDire/Q2;
        xCS    = 1 - kappa2/(1.-z);
        if (abs(Q2) < 1e-5) xCS = 1.;
      }

      double prob =
        abs(childNow->clusterProb)
        // clusterProb includes 1/pT2, but here, we only want
        // the propagator factor 1/(2.*pipj)
        // (we will want to choose an effective scale by solving
        // as(teff) = (sum of kernel*propagator*MEC) . Note that we DO NOT
        // include the Jacobian here, and consequently have to remove its
        // contribution from clusterProb.)
        * t / virtuality
        // Part of the definition of initial-state factorization.
        * 1 / xCS
        // Multiply with factor 8*Pi left-over from dipole ME factorization:
        // |Mn+1|^2 ~ 8*Pi*alphaS*1/(2.pipj)*1/x*dipole*|Mn|^2
        //          = 2g^2 *1/(2.pipj)*1/x*dipole*|Mn|^2
        //          compared with using g^2=1 in MG5 MEs.
        * 8. * M_PI;

      // Get coupling.
      //double coupling(1.);
      //string name = childNow->clusterIn.name();
      double coupling = childNow->clusterCoupl * 2. * M_PI;

      string name = childNow->clusterIn.name();
      double running_coupling = (isFSR)
        ? fsr->splits[name]->coupling (z, t, Q2, -1., 
            make_pair(radPart->id(), radPart->isFinal()),
            make_pair(recPart->id(), recPart->isFinal()))
        : isr->splits[name]->coupling (z, t, Q2, -1., 
            make_pair(radPart->id(), radPart->isFinal()),
            make_pair(recPart->id(), recPart->isFinal()));
      running_coupling *= 2. * M_PI;

      double scale2_coupling = (isFSR)
        ? fsr->splits[name]->couplingScale2 (z, t, Q2, 
            make_pair(radPart->id(), radPart->isFinal()),
            make_pair(recPart->id(), recPart->isFinal()))
        : isr->splits[name]->couplingScale2 (z, t, Q2, 
            make_pair(radPart->id(), radPart->isFinal()),
            make_pair(recPart->id(), recPart->isFinal()));
      if (scale2_coupling< 0.) scale2_coupling = t;
      tmax = max(tmax,scale2_coupling);
      tmin = min(tmin,scale2_coupling);

      if (emt2>0) prob *= t/virtuality*8.*M_PI;
      if (emt2>0) coupling *= 2.*M_PI;
      if (emt2>0) running_coupling *= 2.*M_PI;

      // Include alphaS at effective scale of previous order.
      double alphasOftEffPrev(childNow->couplEffective);

      //alphasOftEff_num += prob * childNow->MECnum * alphasOftEffPrev * coupling;
      alphasOftEff_num += prob * childNow->MECnum
                        * alphasOftEffPrev
                        * running_coupling;
      alphasOftEff_den += prob * childNow->MECnum;*/

      double scale2_coupling = pow2(childNow->clusterIn.pT());
      pair<double,double> blub = getEffCouplNumDen(childNow, scale2_coupling);
      tmax = max(tmax,scale2_coupling);
      tmin = min(tmin,scale2_coupling);
      alphasOftEff_num += blub.first;
      alphasOftEff_den += blub.second;

    }

    // Force scales to be equal if too identical, so that we'll later on simply
    // pick the single scale.
    if (abs(tmax-tmin)/tmax < 1e-4) tmin = tmax;

    // Calculate the effective scale.
    // Note: For negative probabilities, it might be necessary to increase the
    // scale range for root finding.
    CouplFunction  couplFunc(  mergingHooksPtr->AlphaS_FSR(),
      //couplingPowCount["qcd"], mergingHooksPtr->AlphaEM_FSR(),
      //couplingPowCount["qed"]);
      couplingPowCount[QCD], mergingHooksPtr->AlphaEM_FSR(),
      couplingPowCount[QED]);

    double as_tmin = couplFunc.f(tmin,vector<double>());
    double as_tmax = couplFunc.f(tmax,vector<double>());
    double headroom = 1.;
    bool failed = false;
    double alphasOftEffRatio = pow(alphasOftEff_num/alphasOftEff_den,1.);
    while ( tmin/headroom < tmax*headroom
      && ( ( as_tmin-alphasOftEffRatio > 0
          && as_tmax-alphasOftEffRatio > 0)
        || ( as_tmin-alphasOftEffRatio < 0
          && as_tmax-alphasOftEffRatio < 0))) {
      if (tmin/headroom < 1.) { failed = true; break;}
      headroom *= 1.01;
      as_tmin = couplFunc.f(tmin/headroom,vector<double>());
      as_tmax = couplFunc.f(tmax*headroom,vector<double>());
    }

    if ((abs(alphasOftEffRatio-alphasOftEffRatio) > 1e5
         || alphasOftEffRatio != alphasOftEffRatio) 
      || alphasOftEff_num/alphasOftEff_den < 0.) {
      cout << __FILE__ << " " << __LINE__
           << " Error setting effective scale: " << alphasOftEff_num
           << " " << alphasOftEff_den << " " << alphasOftEffRatio << endl;
    }

    // Include correct power for effective alphaS.
    DireRootFinder direRootFinder;
    double teff = 1.;
    double tminNow(tmin/headroom), tmaxNow(tmax*headroom);
    if (!failed) { 
      if  (abs(tmaxNow-tminNow)/tmaxNow < 1e-4) teff = tmaxNow;
      else teff = direRootFinder.findRoot1D( &couplFunc, tminNow, tmaxNow,
        alphasOftEffRatio, vector<double>(), 100);
    }

    // Set the effective scale for currect sister.
    sisterNow->scaleEffective = sqrt(teff);
    sisterNow->couplEffective = alphasOftEffRatio;

  }

  if (mother) mother->setEffectiveScalesOld();

  return;

}

//--------------------------------------------------------------------------

// Function to retrieve scale information from external showers.

double DireHistory::getShowerPluginScale(const Event& event, int rad, int emt,
  int rec, string name, string key, double) {

  map<string,double> stateVars;
  bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt, rec, "") : false;
  bool isISR = (isr) ? isr->isSpacelike(event, rad, emt, rec, "") : false;
  if (isFSR)      stateVars = fsr->getStateVariables(event, rad, emt, rec, name);
  else if (isISR) stateVars = isr->getStateVariables(event, rad, emt, rec, name);
  return ( (stateVars.size() > 0 && stateVars.find(key) != stateVars.end())
           ? stateVars[key] : -1.0 );

}

//--------------------------------------------------------------------------

// Function to retrieve type of splitting from external showers.

pair<int,double> DireHistory::getCoupling(const Event& event, int rad, int emt,
  int rec, string name) {

  // Retrieve state variables.
  map<string,double> stateVars;
  bool isFSR = (fsr) ? fsr->isTimelike(event, rad, emt, rec, "") : false;
  bool isISR = (isr) ? isr->isSpacelike(event, rad, emt, rec, "") : false;
  //if (isFSR)      stateVars = fsr->getStateVariables(event, rad, emt, rec, name);
  //else if (isISR) stateVars = isr->getStateVariables(event, rad, emt, rec, name);
  //
  //// Get coupling type (identifier of interaction), and get coupling value for
  //// the current splitting, i.e. 1 / [4\pi] * g^2 {splitting variables}
  //int type     = ( (stateVars.size() > 0
  //               && stateVars.find("couplingType") != stateVars.end())
  //             ?  stateVars["couplingType"] : -1);
  //double value = ( (stateVars.size() > 0
  //               && stateVars.find("couplingValue") != stateVars.end())
  //             ?  stateVars["couplingValue"] : -1.0);

  int type     = -1;
  double value = -1.0;
  if (isFSR) {
    //type  = (name != "")
    type  = (!name.empty())
       ? fsr->splits[name]->couplingType(event[rad].id(), event[emt].id())
       : -1;
    //value = (name != "")
    double t = fsr->kinRels->tEvol(event[rad],event[emt],event[rec]);
    if (event[rec].isFinal()) t *= 4.;

    value = (!name.empty())
       ? fsr->splits[name]->coupling(
           fsr->kinRels->zEvol(event[rad],event[emt],event[rec]), t,
           //fsr->kinRels->tEvol(event[rad],event[emt],event[rec]),
           fsr->kinRels->m2dip(event[rad],event[emt],event[rec]), -1.,
           make_pair(event[rad].id(), event[rad].isFinal()),
           make_pair(event[rec].id(), event[rec].isFinal()))
       : -1.0;

  } else if (isISR) {
    //type  = (name != "")
    type  = (!name.empty())
       ? isr->splits[name]->couplingType(event[rad].id(), event[emt].id())
       : -1;
    //value = (name != "")
    value = (!name.empty())
       ? isr->splits[name]->coupling(
           isr->kinRels->zEvol(event[rad],event[emt],event[rec]),
           isr->kinRels->tEvol(event[rad],event[emt],event[rec]),
           isr->kinRels->m2dip(event[rad],event[emt],event[rec]), -1.,
           make_pair(event[rad].id(), event[rad].isFinal()),
           make_pair(event[rec].id(), event[rec].isFinal()))
       : -1.0;
  }

  // Done.
  return make_pair(type,value);

}

//--------------------------------------------------------------------------

// Store if path is considered "signal" or "background" according to a
// user-defined criterion.

void DireHistory::tagPath(DireHistory* leaf) {

  int nHiggs = 0;
  for (int i=0; i < state.size(); ++i) 
    if (state[i].isFinal() && state[i].id() == 25) nHiggs++;
  //if ( nHiggs > 0) {
  //  leaf->tagSave = 0;
  //  return;
  //}
  // Tag as Higgs signal.
  if (nHiggs > 0) leaf->tagSave.push_back("higgs");

  // Tag as BSM signal.
  int nBSM = 0;
  for (int i=0; i < state.size(); ++i) 
    if (state[i].isFinal() && state[i].idAbs() > 30) nBSM++;
  if (nBSM > 0) leaf->tagSave.push_back("bsm");

  if (leaf == this) {
    int nFinal(0), nFinalPartons(0), nFinalGamma(0);
    for (int i = 0;i < state.size();++i) {
      if (state[i].isFinal()) {
        nFinal++;
        if ( state[i].idAbs() < 10
          || state[i].idAbs() == 21) nFinalPartons++;
        if ( state[i].idAbs() == 22) nFinalGamma++;
      }
    }
    // Tag as QCD signal.
    if (nFinal == 2 && nFinalPartons == 2)
      leaf->tagSave.push_back("qcd");
    // Tag as QED signal.
    if (nFinal == 2 && nFinalGamma == 2)
      leaf->tagSave.push_back("qed");
    // Tag as QCD and QED signal.
    if (nFinal == 2 && nFinalGamma == 1 && nFinalPartons == 1) {
      leaf->tagSave.push_back("qed");
      leaf->tagSave.push_back("qcd");
    }
  }

  if (mother) mother->tagPath(leaf);
  return;

}

//--------------------------------------------------------------------------

// Multiply ME corrections to the probability of the path.

void DireHistory::multiplyMEsToPath(DireHistory* leaf) {

  if (leaf == this) {
    leaf->prodOfProbsFull *= hardProcessCouplings(state)*clusterCoupl;
    leaf->prodOfProbs     *= abs(hardProcessCouplings(state)*clusterCoupl);
    leaf->hasMEweightMultiplied = true;
  } else if (mother) {
    leaf->prodOfProbsFull *= MECnum/MECden*clusterCoupl;
    leaf->prodOfProbs     *= abs(MECnum/MECden*clusterCoupl);
    leaf->hasMEweightMultiplied = true;
  } else {
    leaf->prodOfProbsFull *= 1./MECden;
    leaf->prodOfProbs     *= abs(1./MECden);
    leaf->hasMEweightMultiplied = true;
  }

  //if (!mother) {
  //state.list();
  //cout << clusterCoupl << " " << MECcontrib << " "
  //<< MECnum << " " << MECden << endl;
  //int bla; cin >> bla;
  //}

  if (mother) mother->multiplyMEsToPath(leaf);

  return;
}

//--------------------------------------------------------------------------

// Multiply ME corrections to the probability of the path.

void DireHistory::removeMEsFromPath(DireHistory* leaf) {

  if (leaf == this) {
    leaf->prodOfProbsFull /= hardProcessCouplings(state)*clusterCoupl;
    leaf->prodOfProbs     /= abs(hardProcessCouplings(state)*clusterCoupl);
    leaf->hasMEweightMultiplied = false;
  } else if (mother) {
    leaf->prodOfProbsFull /= MECnum/MECden*clusterCoupl;
    leaf->prodOfProbs     /= abs(MECnum/MECden*clusterCoupl);
    leaf->hasMEweightMultiplied = false;
  } else {
    leaf->prodOfProbsFull /= 1./MECden;
    leaf->prodOfProbs     /= abs(1./MECden);
    leaf->hasMEweightMultiplied = false;
  }

  if (mother) mother->removeMEsFromPath(leaf);

  return;
}

//--------------------------------------------------------------------------

// Set coupling power counters in the path.

void DireHistory::setCouplingOrderCount(DireHistory* leaf,
  //map<string,int> count) {
  vector<int> count) {

  string name  = clusterIn.name();
  if (leaf == this) {
    // Count hard process couplings.
    hardProcessCouplings(state, 0, 1., NULL, NULL, true);
    // Update with coupling order of clustering.
    count = couplingPowCount;
  } else if (couplingPowCount.empty()) {
    couplingPowCount = count;
  }

  //if ( name.find("qcd") != string::npos) count["qcd"]++;
  //if ( name.find("qed") != string::npos) count["qed"]++;
  //if ( name.find("ew")  != string::npos) count["qed"]++;
  if ( name.find("qcd") != string::npos) count[QCD]++;
  if ( name.find("qed") != string::npos) count[QED]++;
  if ( name.find("ew")  != string::npos) count[QED]++;

  if (mother) mother->setCouplingOrderCount(leaf, count);

  return;
}

//==========================================================================

} // end namespace Pythia8
