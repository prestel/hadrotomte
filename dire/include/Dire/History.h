// History.h is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

#ifndef Pythia8_DireHistory_H
#define Pythia8_DireHistory_H

#include "Pythia8/Basics.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/Event.h"
#include "Pythia8/Info.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PartonLevel.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/StandardModel.h"
#include "Pythia8/MergingHooks.h"

// Include Pythia header to get version number.
#include "Pythia8/Pythia.h"
#if (PYTHIA_VERSION_INTEGER < 8240)
#include "Pythia8/WeakShowerMEs.h"
#else
#include "Pythia8/SimpleWeakShowerMEs.h"
#endif

#include "Dire/WeightContainer.h"

namespace Pythia8 {

class DireTimes;
class DireSpace;

//==========================================================================

// Declaration of Clustering class.
// This class holds information about one radiator, recoiler, emitted system.
// This class is a container class for MyHistory class use.

class DireClustering {

public:

  const Particle* rad() { return radSave; }
  const Particle* emt1() { return emt1Save; }
  const Particle* emt2() { return emt2Save; }
  const Particle* rec() { return recSave; }

  // The emittor parton
  int radPos;
  // The emitted parton location.
  int emt1Pos, emt2Pos;
  // The recoiler parton.
  int recPos;
  // The colour connected recoiler (Can be different for ISR)
  int partner;
  // The scale associated with this clustering.
  double pTscale;

  const Particle* radSave;
  const Particle* emt1Save;
  const Particle* emt2Save;
  const Particle* recSave;

  // The flavour of the radiator prior to the emission.
  int flavRadBef;
  // Spin of the radiator before the splitting.
  int spinRadBef;
  // The radiator before the splitting.
  int radBef;
  // The recoiler before the splitting.
  int recBef;

  // Name of the splitting.
  string splitName;

  bool isAboveCutoff;

  string name() const { return splitName;}

  bool operator==(const DireClustering & b) {
    return (emt1Pos == b.emt1Pos
      &&    emt2Pos == b.emt2Pos
      &&    radPos  == b.radPos
      &&    recPos  == b.recPos
      &&    partner == b.partner
      &&    pTscale == b.pTscale
      &&    flavRadBef == b.flavRadBef
      &&    spinRadBef == b.spinRadBef
      &&    radBef     == b.radBef
      &&    recBef     == b.recBef
      &&    splitName  == b.splitName
      &&    isAboveCutoff == b.isAboveCutoff);
  }
  inline bool operator!=(const DireClustering & b) {
    return !(*(this)==b);
  }

  // Default constructor
  DireClustering(){
    emt1Pos       = 0;
    emt2Pos       = 0;
    radPos        = 0;
    recPos        = 0;
    partner    = 0;
    pTscale    = 0.;
    radSave    = 0;
    recSave    = 0;
    emt1Save    = 0;
    emt2Save    = 0;
    flavRadBef = 0;
    spinRadBef = 9;
    recBef     = 0;
    radBef     = 0;
    splitName.clear();
    isAboveCutoff = true;
  }

  // Default destructor
  ~DireClustering(){}

  // Copy constructor
  DireClustering( const DireClustering& inSystem ){
    emt1Pos       = inSystem.emt1Pos;
    emt2Pos       = inSystem.emt2Pos;
    radPos        = inSystem.radPos;
    recPos        = inSystem.recPos;
    partner    = inSystem.partner;
    pTscale    = inSystem.pTscale;
    flavRadBef = inSystem.flavRadBef;
    spinRadBef = inSystem.spinRadBef;
    radBef     = inSystem.radBef;
    recBef     = inSystem.recBef;
    radSave    = inSystem.radSave;
    emt1Save   = inSystem.emt1Save;
    emt2Save   = inSystem.emt2Save;
    recSave    = inSystem.recSave;
    splitName  = inSystem.splitName;
    isAboveCutoff = inSystem.isAboveCutoff;
  }

  // Constructor with input
  //DireClustering( int emtPosIn, int radPosIn, int recPosIn, int partnerIn,
  DireClustering( int radPosIn, int emt1PosIn, int emt2PosIn, int recPosIn,
    int partnerIn, double pTscaleIn, const Particle* radIn,
    const Particle* emt1In, const Particle* emt2In, const Particle* recIn,
    string splitNameIn, int flavRadBefIn = 0, int spinRadBefIn = 9,
    int radBefIn = 0, int recBefIn = 0, bool isAboveCutoffIn = true)
    : radPos(radPosIn), emt1Pos(emt1PosIn), emt2Pos(emt2PosIn), recPos(recPosIn),
      partner(partnerIn), pTscale(pTscaleIn), radSave(radIn), emt1Save(emt1In),
      emt2Save(emt2In), recSave(recIn), flavRadBef(flavRadBefIn),
      spinRadBef(spinRadBefIn), radBef(radBefIn), recBef(recBefIn),
      splitName(splitNameIn), isAboveCutoff(isAboveCutoffIn) {}

  // Function to return pythia pT scale of clustering
  double pT() const { return pTscale; }

  // Function to return the dipole mass for this clustering.
  double mass() const {
    double sik = 2.*radSave->p()*recSave->p();
    double sij = 2.*radSave->p()*emt1Save->p();
    double sjk = 2.*emt1Save->p()*recSave->p();

    double s2i = (emt2Pos>0) ? 2.*radSave->p()*emt2Save->p() : 0.;
    double s2k = (emt2Pos>0) ? 2.*emt2Save->p()*recSave->p() : 0.;
    double s2j = (emt2Pos>0) ? 2.*emt2Save->p()*emt1Save->p() : 0.;

    double m2=-1.;
    if      ( radSave->isFinal() &&  recSave->isFinal())
      m2 = sik+sij+sjk+s2i+s2k+s2j;
    else if ( radSave->isFinal() && !recSave->isFinal())
      m2 =-sik+sij-sjk+s2i-s2k+s2j;
    else if (!radSave->isFinal() &&  recSave->isFinal())
      m2 =-sik-sij+sjk-s2i+s2k+s2j;
    else if (!radSave->isFinal() && !recSave->isFinal())
      m2 = sik-sij-sjk-s2i-s2k+s2j;
    return sqrt(abs(m2));
  }

  // print for debug
  void list() const;
  string listString() const;

};

//==========================================================================

// Declaration of MyHistory class
//
// A MyHistory object represents an event in a given step in the CKKW-L
// clustering procedure. It defines a tree-like recursive structure,
// where the root node represents the state with n jets as given by
// the matrix element generator, and is characterized by the member
// variable mother being null. The leaves on the tree corresponds to a
// fully clustered paths where the original n-jets has been clustered
// down to the Born-level state. Also states which cannot be clustered
// down to the Born-level are possible - these will be called
// incomplete. The leaves are characterized by the vector of children
// being empty.

class DireHistory {

public:

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
  DireHistory( int depthIn,
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
           bool isOrdered,
           bool isAllowed,
           bool isHistoryForRealCorrectionIn,
           double clusterProbIn,
           double clusterCouplIn,
           double prodOfProbsIn,
           double prodOfProbsFullIn,
           DireHistory * mothin);

  // The destructor deletes each child.
  ~DireHistory() { clear(); }

  void clear() {
    map<double,DireHistory *>().swap(paths);
    map<double,DireHistory *>().swap(goodBranches);
    map<double,DireHistory *>().swap(badBranches);
    map<double,DireHistory *>().swap(branches);
    for ( int i = 0, N = children.size(); i < N; ++i ) delete children[i];
    vector<DireHistory *>().swap(children);
    //map<string,int>().swap(couplingPowCount);
  }

  bool clearPaths() {
    bool allClear=true;
    for ( int i = 0, N = children.size(); i < N; ++i )
      if (children[i]->state.size()!= 0) allClear = false;
    // If no children exist, also minimize memory footprint of this path.
    // However, ensurethat at least the top level node is filled with an
    // event. Otherwise, the history cannot be reliably used for anything. 
    if (allClear && mother) {
#if (PYTHIA_VERSION_INTEGER >= 8242)
      state.free();
#else
      state.clear();
#endif
      erase = true;
      return true;
    }
    return false;
  }

  // Function to remove a histoy from the tree.
  void removeHistoryFromTree(DireHistory* hist) {
    // Remove history from list of children.
    vector<DireHistory*>::iterator it
      = find(children.begin(), children.end(), hist);
    if ( it != children.end() ) children.erase(it++);
    // Remove from list of paths.
    map<double, DireHistory*>::iterator ip_remove = paths.end();
    for ( map<double, DireHistory*>::iterator ip = paths.begin();
      ip != paths.end(); ++ip) if (ip->second == hist) ip_remove = ip;
    if (ip_remove!=paths.end()) {paths.erase(ip_remove->first);


//cout << __FILE__ << " " << __LINE__ << endl;
}
    // Recurse, to also remove history from paths to other nodes.
    if (mother) mother->removeHistoryFromTree(hist);
  }

  // Function to project paths onto desired paths.
  bool projectOntoDesiredHistories();

  // For CKKW-L, NL3 and UMEPS:
  // In the initial history node, select one of the paths according to
  // the probabilities. This function should be called for the initial
  // history node.
  // IN  trialShower*    : Previously initialised trialShower object,
  //                       to perform trial showering and as
  //                       repository of pointers to initialise alphaS
  //     PartonSystems* : PartonSystems object needed to initialise
  //                      shower objects
  // OUT double         : (Sukadov) , (alpha_S ratios) , (PDF ratios)
  double weightTREE(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN);

  map<string,double> weightAllOrder(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN);
  map<string,double> weightAllOrderExpanded(int order, PartonLevel* trial,
    AlphaStrong * asFSR, AlphaStrong * asISR, AlphaEM * aemFSR,
    AlphaEM * aemISR, double RN);

  double weightMOPS(PartonLevel* trial, AlphaStrong * as, AlphaEM * aem, 
    double RN);
  vector<double> weightMEM(PartonLevel* trial, AlphaStrong* as, AlphaEM* aem,
    double RN);
  double weightMEC() { return MECnum/MECden; }

  // For default NL3:
  // Return weight of virtual correction and subtractive for NL3 merging
  double weightLOOP(PartonLevel* trial, double RN);
  // Return O(\alpha_s)-term of CKKWL-weight for NL3 merging

  // For UMEPS:
  double weight_UMEPS_TREE(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN);
  double weight_UMEPS_SUBT(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN);

  // For unitary NL3:
  double weight_UNLOPS_TREE(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
    int depthIn = -1);
  double weight_UNLOPS_SUBT(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
    int depthIn = -1);
  double weight_UNLOPS_LOOP(PartonLevel* trial, AlphaStrong * asFSR,
     AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
     int depthIn = -1);
  double weight_UNLOPS_SUBTNLO(PartonLevel* trial, AlphaStrong * asFSR,
    AlphaStrong * asISR, AlphaEM * aemFSR, AlphaEM * aemISR, double RN,
    int depthIn = -1);
  double weight_UNLOPS_CORRECTION( int order, PartonLevel* trial,
    AlphaStrong* asFSR, AlphaStrong * asISR, AlphaEM * aemFSR,
    AlphaEM * aemISR, double RN, Rndm* rndmPtr );

  // Function to check if any allowed histories were found
  bool foundAllowedHistories() {
    return (children.size() > 0 && foundAllowedPath); }
  // Function to check if any ordered histories were found
  bool foundOrderedHistories() {
    return (children.size() > 0 && foundOrderedPath); }

  bool useEffectiveScale() {
//cout << __LINE__ << " " << endl;
    double hardScale = hardStartScale(state);
//cout << __LINE__ << " " << endl;
    bool isOrdered   = isOrderedPath( hardScale, NULL);
//cout << __LINE__ << " " << endl;
    return (foundOnlyUnorderedHistories() || !isOrdered);
  }

  bool foundOnlyUnorderedHistories() {
    bool useEffScale = !foundOrderedPath;
    DireHistory* node = this;
    while (node->mother) {
      useEffScale = !node->mother->foundOrderedPath;
      node = node->mother;
    }
    return useEffScale;
  }

  /*bool useEffectiveScale() {
    bool useEffScale = !foundOrderedPath;
    DireHistory* node = this;
    while (node->mother) {
      useEffScale = !node->mother->foundOrderedPath;
      node = node->mother;
    }
    return useEffScale;
  }*/

  // Function to check if any ordered histories were found
  bool foundCompleteHistories() {
    return (children.size() > 0 && foundCompletePath); }

  // Function to set the state with complete scales for evolution
  void getStartingConditions( const double RN, Event& outState );
  // Function to get the state with complete scales for evolution
  bool getClusteredEvent( const double RN, int nSteps, Event& outState);
  // Function to get the first reclustered state above the merging scale.
  bool getFirstClusteredEventAboveTMS( const double RN, int nDesired,
    Event& process, int & nPerformed, bool updateProcess = true );
  // Function to return the depth of the history (i.e. the number of
  // reclustered splittings)
  int nClusterings(DireHistory* end);
  int nOrdered(double maxscale, DireHistory* end);
  vector<double> scales(DireHistory* end);

  // Function to get the lowest multiplicity reclustered event
  Event lowestMultProc( const double RN) {
    // Return lowest multiplicity state
    return (select(RN)->state);
  }

  // Calculate and return pdf ratio
  double getPDFratio( int side, bool forSudakov, bool useHardPDF,
                      int flavNum, double xNum, double muNum,
                      int flavDen, double xDen, double muDen);

  // Function to print the history that would be chosen from the random number
  // RN. Mainly for debugging.
  void printHistory( const double RN );
  // Function to print the states in a history, starting from the hard process.
  // Mainly for debugging.
  void printStates();
  void printLeaves();
  void printTree();
  void printPath();

  // Make Pythia class friend
  friend class Pythia;
  // Make Merging class friend
  friend class DireMerging;
  friend class DireTimes;
  friend class DireSpace;

private:

  // Number of trial emission to use for calculating the average number of
  // emissions
  static const int NTRIAL;

  // Define size of windows around the charm and bottom thresholds. This
  // parameter is needed to define the flavour threshold region.
  static const double MCWINDOW, MBWINDOW, PROBMAXFAC;

  // Function to set all scales in the sequence of states. This is a
  // wrapper routine for setScales and setEventScales methods
  void setScalesInHistory();

  // Function to find the index (in the mother histories) of the
  // child history, thus providing a way access the path from both
  // initial history (mother == 0) and final history (all children == 0)
  // IN vector<int> : The index of each child in the children vector
  //                  of the current history node will be saved in
  //                  this vector
  // NO OUTPUT
  void findPath(vector<int>& out);

  // Functions to set the  parton production scales and enforce
  // ordering on the scales of the respective clusterings stored in
  // the MyHistory node:
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
  void setScales( vector<int> index, bool forward, bool useEffScale);

  // Function to find a particle in all higher multiplicity events
  // along the history path and set its production scale to the input
  // scale
  // IN  int iPart       : Parton in refEvent to be checked / rescaled
  //     Event& refEvent : Reference event for iPart
  //     double scale    : Scale to be set as production scale for
  //                       unchanged copies of iPart in subsequent steps
  void scaleCopies(int iPart, const Event& refEvent, double rho);

  // Function to set the OVERALL EVENT SCALES [=state.scale()] to
  // the scale of the last clustering
  // NO INPUT
  // NO OUTPUT
  void setEventScales();

  // Function to print information on the reconstructed scales in one path.
  // For debug only.
  void printScales() {
    int type = (!mother) ? 0
             : ( clusterIn.rad()->isFinal() &&  clusterIn.rec()->isFinal()) ? 2
             : ( clusterIn.rad()->isFinal() && !clusterIn.rec()->isFinal()) ? 1
             : (!clusterIn.rad()->isFinal() &&  clusterIn.rec()->isFinal()) ?
               -1 : -2;
    cout << scientific << setprecision(6);
    cout << " size " << state.size() << " scale " << scale
    << " clusterIn " << clusterIn.pT() << " state.scale() " << state.scale()
    << " scaleEffective " << scaleEffective;
    if (type==-2) cout << "\t\t" << " II splitting emt="
      << clusterIn.emt1()->id() << endl;
    if (type==-1) cout << "\t\t" << " IF splitting emt="
      << clusterIn.emt1()->id() << endl;
    if (type== 1) cout << "\t\t" << " FI splitting emt="
      << clusterIn.emt1()->id() << endl;
    if (type== 2) cout << "\t\t" << " FF splitting emt="
      << clusterIn.emt1()->id() << endl;
    if ( mother ) mother->printScales();
  }

  // Function to project paths onto desired paths.
  bool trimHistories();
  //int  nHistoriesPassTMScuts();
  bool extractBranches(map<double,DireHistory*> motherBranches);
  // Function to tag history for removal.
  void remove(){ doInclude = false; }
  // Function to return flag of allowed histories to choose from.
  bool keep(){ return doInclude; }
  // Function implementing checks on a paths, for deciding if the path should
  // be considered valid or not.
  bool keepHistory(DireHistory* end);
  //bool passTMScuts(DireHistory* end);
  bool contains(DireHistory* node);
  // Function to check if a path is ordered in evolution pT.
  bool isOrderedPath( double maxscale, DireHistory* end);

  bool hasScalesAboveCutoff();
  bool isPathAboveCutoff();
  bool allPathsAboveCutoff();

  bool followsInputPath();

  bool isPathAboveTMS();
  bool allPathsAboveTMS();

  // Function to check if all reconstucted states in a path pass the merging
  // scale cut.
  bool allIntermediateAboveRhoMS( double rhoms, bool good = true );
  // Function to check if any ordered paths were found (and kept).
  bool foundAnyOrderedPaths();

  bool firstClusteringAboveTMS(double tms);
  bool nPartonStateAboveTMS(int nReq, double tms, bool good = true);

  // Functions to return the event with nSteps additional partons
  // INPUT  int   : Number of splittings in the event,
  //                as counted from core 2->2 process
  // OUTPUT Event : event with nSteps additional partons
  Event clusteredState( int nSteps);

  // Function to choose a path from all paths in the tree
  // according to their splitting probabilities
  // IN double    : Random number
  // OUT MyHistory* : Leaf of history path chosen
  DireHistory * select(double rnd);

  pair<double,DireHistory*> getDemocraticLeaf (Rndm* rndmPtr);
  pair<double,DireHistory*> getProbabilisticLeaf (Rndm* rndmPtr);
  pair<double,DireHistory*> getProbabilisticFullLeaf (Rndm* rndmPtr,
    DireHistory*& chosen_starting_leaf);
  pair<double,DireHistory*> getNextProbabilisticFullLeaf(
    DireHistory* oldLeaf);
  double getSelectionRateDemocratic (DireHistory*);
  double getSelectionRateProbabilistic (DireHistory* leaf);
  double getSelectionRateProbabilisticFull (DireHistory* leaf);
  void rescaleProbs();

  double getPathIndexRandom(Rndm* rndmPtr, bool useAll,
    double& sumAll, double& sumFullAll);

  // For a full path, find the weight calculated from the ratio of
  // couplings, the no-emission probabilities, and possible PDF
  // ratios. This function should only be called for the last history
  // node of a full path.
  // IN  TimeShower : Already initialised shower object to be used as
  //                  trial shower
  //     double     : alpha_s value used in ME calculation
  //     double     : Maximal mass scale of the problem (e.g. E_CM)
  //     AlphaStrong: Initialised shower alpha_s object for FSR alpha_s
  //                  ratio calculation
  //     AlphaStrong: Initialised shower alpha_s object for ISR alpha_s
  //                  ratio calculation (can be different from previous)
  double weight(PartonLevel* trial, double as0, double aem0,
    double maxscale, double pdfScale, AlphaStrong * asFSR, AlphaStrong * asISR,
    AlphaEM * aemFSR, AlphaEM * aemISR, bool useEffScale,
    double& asWeight, double& aemWeight, double& pdfWeight,
    map <string,double>& terms);
  double weight(PartonLevel* trial, double as0, double aem0,
    double maxscale, double pdfScale, AlphaStrong * asFSR, AlphaStrong * asISR,
    AlphaEM * aemFSR, AlphaEM * aemISR, bool useEffScale,
    double& asWeight, double& aemWeight, double& pdfWeight) {
    map<string,double> dummy;
    return weight(trial, as0, aem0, maxscale, pdfScale, asFSR, asISR,
      aemFSR, aemISR, useEffScale, asWeight, aemWeight, pdfWeight, dummy);
  }

  // Function to return the \alpha_s-ratio part of the CKKWL weight.
  double weightALPHAS( double as0, AlphaStrong * asFSR,
    AlphaStrong * asISR,  int njetMin, int njetMax, bool useEffScale);
  // Function to return the \alpha_em-ratio part of the CKKWL weight.
  double weightALPHAEM( double aem0, AlphaEM * aemFSR,
    AlphaEM * aemISR, int njetMin, int njetMax, bool useEffScale);
  // Function to return the coupling ratio part of the CKKWL weight.
  vector<double> weightCouplings();
  vector<double> weightCouplingsDenominator();
  // Function to return the PDF-ratio part of the CKKWL weight.
  double weightPDFs( double maxscale, double pdfScale, int njetMin = -1,
    int njetMax = -1 );
  // Function to return the no-emission probability part of the CKKWL weight.
  double weightEmissions( PartonLevel* trial, int type, int njetMin,
    int njetMax, double maxscale );
  vector<double> weightEmissionsVec( PartonLevel* trial, int type,
    int njetMin, int njetMax, double maxscale );

  // Function to generate the O(\alpha_s)-term of the \alpha_s-ratios
  // appearing in the CKKWL-weight.
  double weightAlphasExpanded( int order, double as0, double muR,
    AlphaStrong * asFSR, AlphaStrong * asISR, bool useEffScale,
    map <string,double>& terms);
  double weightAlphasExpanded( int order, double as0, double muR,
    AlphaStrong * asFSR, AlphaStrong * asISR, bool useEffScale) {
    map<string,double> dummy;
    return weightAlphasExpanded(order, as0, muR, asFSR, asISR, useEffScale,
      dummy);
  }
  // Function to generate the O(\alpha_em)-term of the \alpha_em-ratios
  // appearing in the CKKWL-weight.
  double weightFirstALPHAEM( double aem0, double muR, AlphaEM * aemFSR,
    AlphaEM * aemISR, bool useEffScale, map <string,double>& terms);
  double weightFirstALPHAEM( double aem0, double muR, AlphaEM * aemFSR,
    AlphaEM * aemISR, bool useEffScale) {
    map<string,double> dummy;
    return weightFirstALPHAEM(aem0, muR, aemFSR, aemISR, useEffScale, dummy);
  }
  // Function to generate the O(\alpha_s)-term of the PDF-ratios
  // appearing in the CKKWL-weight.
  double weightFirstPDFs( double as0, double maxscale, double pdfScale,
    Rndm* rndmPtr, map <string,double>& terms);
  double weightFirstPDFs( double as0, double maxscale, double pdfScale,
    Rndm* rndmPtr ) {
    map<string,double> dummy;
    return weightFirstPDFs(as0, maxscale, pdfScale, rndmPtr, dummy);
  }
  double weightPDFExpanded( int order, double as0, double maxscale,
    map <string,double>& terms);
  double weightPDFExpanded( int order, double as0, double maxscale) {
    map<string,double> dummy;
    return weightPDFExpanded(order, as0, maxscale, dummy);
  }

  vector<double> pdfExpansion(int order, int side, int flav, double x, double t,
    double muf, double mur);

  // Function to generate the O(\alpha_s)-term of the no-emission
  // probabilities appearing in the CKKWL-weight.
  double weightEmissionsExpanded(int order, PartonLevel* trial, double as0,
    double maxscale, AlphaStrong * asFSR, AlphaStrong * asISR,
    bool fixpdf, bool fixas, map <string,double>& terms );
  double weightEmissionsExpanded(int order, PartonLevel* trial, double as0,
    double maxscale, AlphaStrong * asFSR, AlphaStrong * asISR,
    bool fixpdf, bool fixas ) {
    map<string,double> dummy;
    return weightEmissionsExpanded(order, trial, as0, maxscale, asFSR, asISR,
      fixpdf, fixas, dummy);
  }

  double weightHardState(const Event& event, double asME, AlphaStrong * as,
    double aemME, AlphaEM * aem);
  double weightHardStateExpanded(int order, const Event& event,
    double asME, double muR);

  // Function to return the default factorisation scale of the hard process.
  double hardFacScale(const Event& event);
  // Function to return the default renormalisation scale of the hard process.
  double hardRenScale(const Event& event);
  double hardProcessScale( const Event& event);
  double hardStartScale(const Event& event);

  // Perform a trial shower using the \a pythia object between
  // maxscale down to this scale and return the corresponding Sudakov
  // form factor.
  // IN  trialShower : Shower object used as trial shower
  //     double     : Maximum scale for trial shower branching
  // OUT  0.0       : trial shower emission outside allowed pT range
  //      1.0       : trial shower successful (any emission was below
  //                  the minimal scale )
  vector<double> doTrialShower(PartonLevel* trial, int type, double maxscale,
    double minscale = 0.);

  // Function to bookkeep the indices of weights generated in countEmissions
  bool updateind(vector<int> & ind, int i, int N);

  // Function to count number of emissions between two scales for NLO merging
  vector<double> countEmissions(PartonLevel* trial, double maxscale,
    double minscale, int showerType, double as0, AlphaStrong * asFSR,
    AlphaStrong * asISR, int N = 1, bool fixpdf = true, bool fixas = false,
    int order = -99);

  // Function to integrate PDF ratios between two scales over x and t,
  // where the PDFs are always evaluated at the lower t-integration limit
  double monteCarloPDFratios(int flav, double x, double maxScale,
           double minScale, double pdfScale, double asME, Rndm* rndmPtr);

  // Default: Check if a ordered (and complete) path has been found in
  // the initial node, in which case we will no longer be interested in
  // any unordered paths.
  bool onlyOrderedPaths();

  // Check if an allowed (according to user-criterion) path has been found in
  // the initial node, in which case we will no longer be interested in
  // any forbidden paths.
  bool onlyAllowedPaths();

  // When a full path has been found, register it with the initial
  // history node.
  // IN  MyHistory : MyHistory to be registered as path
  //     bool    : Specifying if clusterings so far were ordered
  //     bool    : Specifying if path is complete down to 2->2 process
  // OUT true if MyHistory object forms a plausible path (eg prob>0 ...)
  bool registerPath(DireHistory * l, bool isOrdered,
         bool isAllowed, bool isComplete);
  bool rejectBadPath(DireHistory * l, bool isOrdered,
    bool isAllowed, bool isComplete);
  void setGoodPathFlags(bool isOrdered, bool isAllowed, bool isComplete);

  // For one given state, find all possible clusterings.
  // IN  Event : state to be investigated
  // OUT vector of all (rad,rec,emt) systems in the state
  vector<DireClustering> getAllClusterings( const Event& event);
  //vector<DireClustering> getClusterings( int emt, int rad, const Event& event);
  vector<DireClustering> getClusterings( int rad, int emt1, int emt2,
    const Event& event);
  // Function to attach (spin-dependent duplicates of) a clustering.
  //void attachClusterings (vector<DireClustering>& clus, int iEmt, int iRad,
  void attachClusterings (vector<DireClustering>& clus, int iRad, int iEmt1,
    int iEmt2, int iRec, int iPartner, double pT, string name,
    const Event& event);

  // Calculate and return the probability of a clustering.
  // IN  Clustering : rad,rec,emt - System for which the splitting
  //                  probability should be calcuated
  // OUT splitting probability
  pair <double,double> getProb(const DireClustering & SystemIn);

  // Set up the beams (fill the beam particles with the correct
  // current incoming particles) to allow calculation of splitting
  // probability.
  // For interleaved evolution, set assignments dividing PDFs into
  // sea and valence content. This assignment is, until a history path
  // is chosen and a first trial shower performed, not fully correct
  // (since content is chosen form too high x and too low scale). The
  // assignment used for reweighting will be corrected after trial
  // showering
  void setupBeams();

  // Calculate the PDF ratio used in the argument of the no-emission
  // probability.
  double pdfForSudakov();

  // Calculate the hard process matrix element to include in the selection
  // probability.
  double hardProcessME(const Event& event);
  //bool updateCouplingPowCount(string key, int value);
  bool updateCouplingPowCount(int key, int value);
  double hardProcessCouplings( const Event& event, int order = 0,
    double renormMultFac = 1., AlphaStrong* alphaS = NULL,
    AlphaEM* alphaEM = NULL, bool fillCouplCounters = false,
    bool with2pi = true);
  bool passHardProcessCuts(const Event& event);

  // Perform the clustering of the current state and return the
  // clustered state.
  // IN Clustering : rad,rec,emt triple to be clustered to two partons
  // OUT clustered state
  Event cluster( DireClustering & inSystem);

  // Function to get the parton connected to in by a colour line
  // IN  int   : Position of parton for which partner should be found
  //     Event : Reference event
  // OUT int   : If a colour line connects the "in" parton with another
  //             parton, return the Position of the partner, else return 0
  int getColPartner(const int in, const Event& event);

  // Function to get the parton connected to in by an anticolour line
  // IN  int   : Position of parton for which partner should be found
  //     Event : Reference event
  // OUT int   : If an anticolour line connects the "in" parton with another
  //             parton, return the Position of the partner, else return 0
  int getAcolPartner(const int in, const Event& event);

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
  bool getColSinglet(const int flavType, const int iParton,
    const Event& event, vector<int>& exclude,
    vector<int>& colSinglet);

  // Function to check that a set of partons forms a colour singlet
  // IN  Event       : Reference event
  // IN  vector<int> : Positions of the partons in the set
  // OUT bool        : Is a colour singlet / is not
  bool isColSinglet( const Event& event, vector<int> system);
  // Function to check that a set of partons forms a flavour singlet
  // IN  Event       : Reference event
  // IN  vector<int> : Positions of the partons in the set
  // IN  int         : Flavour of all the quarks in the set, if
  //                   all quarks in a set should have a fixed flavour
  // OUT bool        : Is a flavour singlet / is not
  bool isFlavSinglet( const Event& event,
    vector<int> system, int flav=0);

  // Function to properly colour-connect the radiator to the rest of
  // the event, as needed during clustering
  // IN  Particle& : Particle to be connected
  //     Particle  : Recoiler forming a dipole with Radiator
  //     Event     : event to which Radiator shall be appended
  // OUT true               : Radiator could be connected to the event
  //     false              : Radiator could not be connected to the
  //                          event or the resulting event was
  //                          non-valid
  bool connectRadiator( Particle& radiator, const int radType,
                        const Particle& recoiler, const int recType,
                        const Event& event );

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
  int FindCol(int col, int iExclude1, int iExclude2,
              const Event& event, int type, bool isHardIn);

  // Function to in the input event find a particle with quantum
  // numbers matching those of the input particle
  // IN  Particle : Particle to be searched for
  //     Event    : Event to be searched in
  // OUT int      : > 0 : Position of matching particle in event
  //                < 0 : No match in event
  int FindParticle( const Particle& particle, const Event& event,
    bool checkStatus = true );

  // Function to check if rad,emt,rec triple is allowed for clustering
  // IN int rad,emt,rec,partner : Positions (in event record) of the three
  //                      particles considered for clustering, and the
  //                      correct colour-connected recoiler (=partner)
  //    Event event     : Reference event
  bool allowedClustering( int rad, int emt, int rec, int partner,
    string name, const Event& event );

  bool hasConnections(int arrSize, int nIncIDs[], int nOutIDs[]);
  bool canConnectFlavs( map<int,int> nIncIDs, map<int,int> nOutIDs);

  // Function to check if rad,emt,rec triple is results in
  // colour singlet radBefore+recBefore
  // IN int rad,emt,rec : Positions (in event record) of the three
  //                      particles considered for clustering
  //    Event event     : Reference event
  bool isSinglett( int rad, int emt, int rec, const Event& event );

  // Function to check if event is sensibly constructed: Meaning
  // that all colour indices are contracted and that the charge in
  // initial and final states matches
  // IN  event : event to be checked
  // OUT TRUE  : event is properly construced
  //     FALSE : event not valid
  bool validEvent( const Event& event );

  // Function to check whether two clusterings are identical, used
  // for finding the history path in the mother -> children direction
  bool equalClustering( DireClustering clus1 , DireClustering clus2 );

  // Chose dummy scale for event construction. By default, choose
  //     sHat     for 2->Boson(->2)+ n partons processes and
  //     M_Boson  for 2->Boson(->)             processes
  double choseHardScale( const Event& event ) const;

  // If the state has an incoming hadron return the flavour of the
  // parton entering the hard interaction. Otherwise return 0
  int getCurrentFlav(const int) const;

   // If the state has an incoming hadron return the x-value for the
   // parton entering the hard interaction. Otherwise return 0.
  double getCurrentX(const int) const;

  double getCurrentZ(const int rad, const int rec, const int emt,
    int idRadBef = 0) const;

  // Function to compute "pythia pT separation" from Particle input
  double pTLund(const Event& event, int radAfterBranch, int emtAfterBranch,
    int recAfterBranch, string name);
  double pTLund(const Event& event, int radAft, int emtAft1, int emtAft2,
    int recAft, string name);

  // Function to return the position of the initial line before (or after)
  // a single (!) splitting.
  int posChangedIncoming(const Event& event, bool before);

  vector<int> getSplittingPos(const Event& event, int type);

  // Function to give back the ratio of PDFs and PDF * splitting kernels
  // needed to convert a splitting at scale pdfScale, chosen with running
  // PDFs, to a splitting chosen with PDFs at a fixed scale mu. As needed to
  // properly count emissions.
  double pdfFactor( const Event& process, const Event& event, const int type,
    double pdfScale, double mu );

  // Function giving the product of splitting kernels and PDFs so that the
  // resulting flavour is given by flav. This is used as a helper routine
  // to dgauss
  double integrand(int flav, double x, double scaleInt, double z);

  // Check if an event reclustered into a 2 -> 2 dijet.
  // (Only enabled if W reclustering is used).
  bool isQCD2to2(const Event& event);

  // Check if an event reclustered into a 2 -> 1 Drell-Yan.
  // (Only enabled if W reclustering is used).
  bool isEW2to1(const Event& event);

  // Check if an event reclustered into massless 2 -> 2.
  bool isMassless2to2(const Event& event);
  // Check if an event reclustered into DIS 2 -> 2.
  bool isDIS2to2(const Event& event);

  // Function to allow effective gg -> EW boson couplings.
  bool mayHaveEffectiveVertex( string process, vector<int> in, vector<int> out);

  // Set selected child indices.
  void setSelectedChild();
  void setGoodChildren();
  void setGoodSisters();

  void tagPath(DireHistory* leaf);
  void multiplyMEsToPath(DireHistory* leaf);
  void removeMEsFromPath(DireHistory* leaf);
  bool hasTag(string key) {
    if(find(tagSave.begin(), tagSave.end(), key) != tagSave.end())
      return true;
    return false;
  }

  bool isOrderedBranching(DireHistory*, DireHistory*);

  void setProbabilities();
  void setProbabilitiesOld();
  double getBareProb( DireHistory*);
  void printMECS();

  pair<double,double> getEffCouplNumDen( DireHistory*, double&);
  double calculateEffectiveScale( double, double, double);
  void setEffectiveScales();
  void setEffectiveScalesOld();

  // Functions to retrieve scale information from external showers.
  double getShowerPluginScale(const Event& event, int rad, int emt, int rec,
    string name, string key, double scalePythia);

  pair<int,double> getCoupling(const Event& event, int rad, int emt,
    int rec, string name);

  void setCouplingOrderCount(DireHistory* leaf,
    //map<string,int> count = map<string,int>());
    //map<int,int> count = map<int,int>());
    vector<int> count = vector<int>(3,0));

  //----------------------------------------------------------------------//
  // Class members.
  //----------------------------------------------------------------------//

public:

  // The state of the event correponding to this step in the
  // reconstruction.
  Event state;

  // Index for generation.
  int generation;

private:

  // The previous step from which this step has been clustered. If
  // null, this is the initial step with the n-jet state generated by
  // the matrix element.
  DireHistory * mother;

  // The different steps corresponding to possible clusterings of this
  // state.
  vector<DireHistory *> children;
  vector<DireHistory *> goodChildren;
  vector<DireHistory *> goodSisters;

  // After a path is selected, store the child index.
  int selectedChild;

  // The different paths which have been reconstructed indexed with
  // the (incremental) corresponding probability. This map is empty
  // unless this is the initial step (mother == 0).
  map<double,DireHistory *> paths;

  // The sum of the probabilities of the full paths. This is zero
  // unless this is the initial step (mother == 0).
  double sumpath;

public:

  // The different allowed paths after projection, indexed with
  // the (incremental) corresponding probability. This map is empty
  // unless this is the initial step (mother == 0).
  map<double,DireHistory *> goodBranches, badBranches, branches;

private:

  // The sum of the probabilities of allowed paths after projection. This is
  // zero unless this is the initial step (mother == 0).
  double sumGoodBranches, sumBadBranches, sumbranches;

  // This is set true if an ordered (and complete) path has been found
  // and inserted in paths.
  bool foundOrderedPath;

  // This is set true if an allowed (according to a user criterion) path has
  // been found and inserted in paths.
  bool foundAllowedPath;

  // This is set true if a complete (with the required number of
  // clusterings) path has been found and inserted in paths.
  bool foundCompletePath;

  bool foundOrderedChildren;

  // The scale of this step, corresponding to clustering which
  // constructed the corresponding state (or the merging scale in case
  // mother == 0).
  double scale, scaleEffective, couplEffective;

  bool allowedOrderingPath;

  // Flag indicating if a clustering in the construction of all histories is
  // the next clustering demanded by inout clusterings in LesHouches 2.0
  // accord.
  bool nextInInput;

  bool isHistoryForRealCorrection;

  // The probability associated with this step and the previous steps.
  double clusterProb, clusterCoupl, prodOfProbs, prodOfProbsFull;

  // The partons and scale of the last clustering.
  DireClustering clusterIn;
  int iReclusteredOld, iReclusteredNew;

  // Flag to include the path amongst allowed paths.
  bool doInclude;

  bool hasMEweight, hasMEweightMultiplied;
  double MECnum, MECden, MECcontrib, Q2minMEs;

  vector<int> goodChildIndex;

  // Pointer to MergingHooks object to get all the settings.
  MergingHooks* mergingHooksPtr;

   // The default constructor is private.
  DireHistory() {}

  // The copy-constructor is private.
  DireHistory(const DireHistory &) {}

  // The assignment operator is private.
  DireHistory & operator=(const DireHistory &) {
    return *this;
  }

  // BeamParticle to get access to PDFs
  BeamParticle beamA;
  BeamParticle beamB;
  // ParticleData needed to initialise the shower AND to get the
  // correct masses of partons needed in calculation of probability
  ParticleData* particleDataPtr;

  // Info object to have access to all information read from LHE file
  Info* infoPtr;

  // Class for calculation weak shower ME.
#if (PYTHIA_VERSION_INTEGER < 8240)
  WeakShowerMEs weakShowerMEs;
#else
  SimpleWeakShowerMEs weakShowerMEs;
#endif

  // Pointer to showers, to simplify external clusterings.
  PartonLevel* showers;

  DireTimes* fsr;
  DireSpace* isr;

  // Pointer to standard model couplings.
  CoupSM* coupSMPtr;

  DireWeightContainer* psweights;

  int nStepsMax;
  bool doSingleLegSudakovs;

  //int tagSave;
  vector<string> tagSave;

  double probMaxSave;
  //double probMax() { return probMaxSave; }
  double probMax() { 
    if (mother) return mother->probMax();
    return probMaxSave;
  }
  void updateProbMax(double probIn, bool isComplete = false) {
    if (mother) mother->updateProbMax(probIn, isComplete);
    if (!isComplete && !foundCompletePath) return;
    if (abs(probIn) > probMaxSave) probMaxSave = probIn;
  }

  int depth, minDepthSave;
  int minDepth(DireHistory* end) {
    if ( this == end) return minDepthSave;
    if ( mother ) return mother->minDepth(end);
    return minDepthSave;
  }
  void updateMinDepth(int depthIn, DireHistory* end) {
    if ( this == end) { 
      minDepthSave = (minDepthSave>0) ? min(minDepthSave,depthIn) : depthIn;
      return;
    }
    if ( mother ) return mother->updateMinDepth(depthIn, end);
    minDepthSave = (minDepthSave>0) ? min(minDepthSave,depthIn) : depthIn;
  }

  int nMaxOrd;
  int nMaxOrdered(DireHistory* end) {
    if ( this == end) return nMaxOrd;
    if ( mother ) return mother->nMaxOrdered(end);
    return nMaxOrd;
  }
  void updateNmaxOrdered(int nord, DireHistory* end) { 
    if ( this == end) { nMaxOrd = max(nMaxOrd,nord); return; }
    if ( mother ) mother->updateNmaxOrdered(nord, end);
    nMaxOrd = max(nMaxOrd,nord);
  }
  int maxDepth() {
    if ( mother ) return mother->maxDepth();
    return depth;
  }
  int npaths(DireHistory* end) {
    if ( this == end) { return paths.size(); }
    if ( mother ) return mother->npaths(end);
    return paths.size();
  }

  bool erase;
  enum couplTypes { QCD=0, QED=1, HEFT=2 };
  //map<string,int> couplingPowCount;
  //map<int,int> couplingPowCount;
  vector<int> couplingPowCount;

  // Functions to rearrange the history tree according to
  // generations of equal depth.
  void collectGenerations();
  void attachNodes();
  void storeNode(DireHistory* hist, int gen);
  void appendNode(DireHistory* hist, int gen);
  void printGenerations();
  map<int, vector<DireHistory*> > generations;

};

//==========================================================================

} // end namespace Pythia8

#endif
