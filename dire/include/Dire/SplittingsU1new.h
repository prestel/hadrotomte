
#ifndef Pythia8_DireSplittingsU1new_H
#define Pythia8_DireSplittingsU1new_H

#define DIRE_SPLITTINGSU1NEW_VERSION "2.004"

#include "Pythia8/Basics.h"
#include "Pythia8/Pythia.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/StandardModel.h"

#include "Dire/SplittingsQED.h"

namespace Pythia8 {

//==========================================================================

class DireSplittingU1new : public DireSplittingQED {

public:  

  // Constructor and destructor.
  DireSplittingU1new(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) : DireSplittingQED(idIn,
      softRS,settings,particleData,rndm,beamA,beamB,coupSM,info, direInfo) {
    slhaInterfacePtr = slhaInterface;
    //idZprime = 900032;
    idZprime = 1023;
    //idZprime = 9000001;
    init();
  }
  virtual ~DireSplittingU1new() {}

  void init();

  // VARIABLES
  int idZprime;
  double ax0, epsilon, alphaEMDark, pT2minForcePosU1, pT2minAllowNegU1;
  bool doU1NEWfsrByQ, doU1NEWfsrByL, doU1NEWisrByQ, doU1NEWisrByL;
  //double overInt1, overInt2;

  bool useFastFunctions() { return true; }

  virtual int * radAndEmtArr (int idDaughter, int) {
    radAndEmtArray [0] = motherID(idDaughter);
    radAndEmtArray [1] = sisterID(idDaughter);
    radAndEmtArray [2] = 0;
    return radAndEmtArray;
  }
  virtual vector <int> radAndEmt(int idDaughter, int)
   { return createvector<int>(motherID(idDaughter))(sisterID(idDaughter)); } 
  virtual int nEmissions()  { return 1; }
  virtual bool isPartial()  { return true; }

  virtual bool canUseForBranching() { return true; }

  virtual int couplingType (int, int) { return 2; }
  virtual double coupling (double z =-1., double pT2 =-1., double m2dip =-1.,
    double renormMultFacNow = -1.,
    pair<int,bool> radBef = pair<int,bool>(),
    pair<int,bool> recBef = pair<int,bool>());

  double pT2min, pT2minL, pT2minQ;
  virtual double tCutoff( const Particle& radBef, const Particle& recBef,
    PartonSystems* partonSystemsPtr = NULL);
  virtual bool aboveCutoff( double t, const Particle& radBef,
    const Particle& recBef, int iSys = 0,
    PartonSystems* partonSystemsPtr = NULL);
  virtual bool dipoleAboveCutoff( double, int = 0, int = 0, double = -1.);

  virtual bool allowedRec(const Event& state, int iRec);
  double forceCouplingFactor(double charge, double pT2, const Event & state);

  double logistic(double x, double a, double c, double x0) {
    return 1./(1.+exp(-a*(x-c*x0)/x0));
  }

};

//==========================================================================

class Dire_fsr_u1new_Q2QA : public DireSplittingU1new {

public:  

  Dire_fsr_u1new_Q2QA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  //bool allowedRec(const Event& state, int iRec) {
  //  return state[iRec].isCharged() /*&& state[iRec].isQuark()*/;
  //}

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

//==========================================================================

class Dire_fsr_u1new_Q2AQ : public DireSplittingU1new {

public:  

  Dire_fsr_u1new_Q2AQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

  //bool allowedRec(const Event& state, int iRec) {
  //  return state[iRec].isCharged() /*&& state[iRec].isQuark()*/;
  //}

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

//==========================================================================

class Dire_fsr_u1new_L2LA : public DireSplittingU1new {

public:  

  Dire_fsr_u1new_L2LA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  //bool allowedRec(const Event& state, int iRec) {
  //  return (state[iRec].isLepton()
  //       || state[iRec].isCharged()
  //  //return ((state[iRec].isLepton() && state[iRec].isCharged())
  //       || state[iRec].idAbs() == 900012
  //       || state[iRec].idAbs() == 900040);
  //}

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    vector< pair<int,int> > ret
     = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
    return ret;
  }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

  double x20;

};

//==========================================================================

class Dire_fsr_u1new_L2AL : public DireSplittingU1new {

public:  

  Dire_fsr_u1new_L2AL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  //bool allowedRec(const Event& state, int iRec) {
  //  return (state[iRec].isLepton()
  //       || state[iRec].isCharged()
  //  //return ((state[iRec].isLepton() && state[iRec].isCharged())
  //       || state[iRec].idAbs() == 900012
  //       || state[iRec].idAbs() == 900040);
  //}

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    vector< pair<int,int> > ret
     = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
    return ret;
  }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

  double x20;

};

//==========================================================================

class Dire_fsr_u1new_A2FF : public DireSplittingU1new {

public:  

  int idRadAfterSave;
  bool hasHardRadiator;
  double nchSaved;

  Dire_fsr_u1new_A2FF(int idRadAfterIn, bool hasHardRadIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) : DireSplittingU1new(idIn, 
    softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo, slhaInterface),
    idRadAfterSave(idRadAfterIn), hasHardRadiator(hasHardRadIn), nchSaved(1) {
    m2Res    = pow2(particleDataPtr->m0(idZprime));
    radAndEmtArray [0] = idRadAfterSave;
    radAndEmtArray [1] =-idRadAfterSave;
    radAndEmtArray [2] = 0;
  }

  // Virtuality ordering.
  int typeEvolutionMeasure() { return 2; }

  double m2Res;

  bool canRadiate ( const Event& state, pair<int,int> ints,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event& state, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap () { return 1;};
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }

  double getZDire(bool finRad, bool finRec, double z, double t, double m2dip) {
    double zNow = -1;
    if (finRad &&  finRec) zNow = zdire_ff(z,t,m2dip);
    if (finRad && !finRec) zNow = zdire_fi(z,t,m2dip);
    return zNow;
  }
  double getTDire(bool finRad, bool finRec, double z, double t, double m2dip) {
    double tNow = -1;
    if (finRad &&  finRec) tNow = tdire_ff(z,t,m2dip);
    if (finRad && !finRec) tNow = tdire_fi(z,t,m2dip);
    return tNow;
  }
  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double, double t, double m2dip)
    { return (t+m2Res)/m2dip; }
  double zcs_ff(double z, double t, double m2dip) {
    double yCS = ycs_ff(z,t,m2dip);
    double zCS = 1. - (1.-z)/(1.-yCS);
    return zCS; 
  }
  double xcs_fi(double, double t, double m2dip) {
    double virt = t+m2Res;
    double x = m2dip / (m2dip + virt);
    return x;
  }
  double zcs_fi(double z, double, double)
    { return z; }
  // Functions to calculate Dire variables from the evolution variables.
  double tdire_ff(double z, double t, double m2dip) { 
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return ycs*(1-ycs)*(1-zcs)*m2dip;
  }
  double zdire_ff(double z, double t, double m2dip) {
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return 1.-(1-ycs)*(1-zcs);
  }
  double tdire_fi(double z, double t, double m2dip) {
    double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return m2dip*(1-xcs)*(1.-zcs);
  }
  double zdire_fi(double z, double t, double m2dip) {
    //double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return zcs;
  }

  // Functions that allow different ordering variables for emissions.
  // Note: Only works after splitInfo has been properly filled.
  double getJacobian( const Event& = Event(),
    PartonSystems* partonSystems = 0);
  unordered_map<string, double> getPhasespaceVars(const Event& = Event(),
    PartonSystems* = 0);

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state);

  // Return id of mother after splitting.
  int motherID(int) 
    { return idRadAfterSave; }
  int sisterID(int)
    { return -idRadAfterSave; }
  int * radAndEmtArr (int, int) {
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int, int)       
    { return createvector<int>(idRadAfterSave)(-idRadAfterSave); }
    //{ return createvector<int>(1)(-1); }
  double gaugeFactor    ( int=0, int=0 ) {
    //return pow2(particleDataPtr->charge(idRadAfterSave));
    double chg = pow2(particleDataPtr->charge(idRadAfterSave));
    if (abs(idRadAfterSave)<10) chg *= 3;
    return chg;
  }
  double symmetryFactor ( int=0, int=0 )
    { return 1./double(nchSaved) * 0.5; }
    //{ return 1.; /* heuristic fix to make agree better with MEC */ }
  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int, int, int, int) { return make_pair(0,0); }

  // All charged particles are potential recoilers.
  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // All charged particles are potential recoilers.
  int set_nCharged( const Event& state);
  int get_nCharged( const Event& state, int radID = 0, double t = -1.);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double /*m2dip*/);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double /*pT2Old*/, double /*m2dip*/, int /*order*/ = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double /*z*/, double /*m2dip*/, int /*order*/ = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state, int orderNow);

  //double generalizedLogistic(double x, double a, double b, double c, double x0) {
  //  double Q = -1 + pow(2,b);
  //  return 1./pow(1.+Q*exp(-a*b*(x-c*x0)/x0), 1./b);
  //}
  double x20;

};

//==========================================================================

class Dire_fsr_u1new_A2FFres : public DireSplittingU1new {

public:  

  int idRadAfterSave, signT;
  bool hasHardRadiator;
  double nchSaved;

  Dire_fsr_u1new_A2FFres(int idRadAfterIn, int signIn, bool hasHardRadIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) : DireSplittingU1new(idIn, 
    softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo, slhaInterface),
    idRadAfterSave(idRadAfterIn), signT(signIn), hasHardRadiator(hasHardRadIn), nchSaved(1) {
    mRes     = particleDataPtr->m0(idZprime);
    m2Res    = pow2(mRes);
    widthTot = particleDataPtr->particleDataEntryPtr(idZprime)->resWidth(
      idZprime,sqrt(m2Res));
    radAndEmtArray [0] = idRadAfterSave;
    radAndEmtArray [1] =-idRadAfterSave;
    radAndEmtArray [2] = 0;
  }

  virtual double coupling (double z =-1., double pT2 =-1., double m2dip =-1.,
    double renormMultFacNow = -1.,
    pair<int,bool> radBef = pair<int,bool>(),
    pair<int,bool> recBef = pair<int,bool>());

  bool dipoleAboveCutoff( double, int, int, double = -1.);

  bool canRadiate ( const Event& state, pair<int,int> ints,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event& state, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap () { return 0;};
  bool isPartial()  { return false; }
  bool canUseForBranching() { return true; }
  int typeEvolutionMeasure() { return signT; }

  double mRes, m2Res, widthTot;

  double getZDire(bool finRad, bool finRec, double z, double t, double m2dip) {
    double zNow = -1;
    if (finRad &&  finRec) zNow = zdire_ff(z,t,m2dip);
    if (finRad && !finRec) zNow = zdire_fi(z,t,m2dip);
    return zNow;
  }
  double getTDire(bool finRad, bool finRec, double z, double t, double m2dip) {
    double tNow = -1;
    if (finRad &&  finRec) tNow = tdire_ff(z,t,m2dip);
    if (finRad && !finRec) tNow = tdire_fi(z,t,m2dip);
    return tNow;
  }
  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double, double t, double m2dip) {
    double virt = (signT > 0 ? t : pow2(2.*mRes-sqrt(t)));
    return virt/m2dip; }
  double zcs_ff(double z, double t, double m2dip) {
    double yCS = ycs_ff(z,t,m2dip);
    double zCS = 1. - (1.-z)/(1.-yCS);
    return zCS; 
  }
  double xcs_fi(double, double t, double m2dip) {
    double virt = (signT > 0 ? t : pow2(2.*mRes-sqrt(t)));
    double x = m2dip / (m2dip + virt);
    return x;
  }
  double zcs_fi(double z, double, double)
    { return z; }
  // Functions to calculate Dire variables from the evolution variables.
  double tdire_ff(double z, double t, double m2dip) { 
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return ycs*(1-ycs)*(1-zcs)*m2dip;
  }
  double zdire_ff(double z, double t, double m2dip) {
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return 1.-(1-ycs)*(1-zcs);
  }
  double tdire_fi(double z, double t, double m2dip) {
    double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return m2dip*(1-xcs)*(1.-zcs);
  }
  double zdire_fi(double z, double t, double m2dip) {
    //double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return zcs;
  }

  // Functions that allow different ordering variables for emissions.
  // Note: Only works after splitInfo has been properly filled.
  double getJacobian( const Event& = Event(),
    PartonSystems* partonSystems = 0);
  unordered_map<string, double> getPhasespaceVars(const Event& = Event(),
    PartonSystems* = 0);

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state);

  // Return id of mother after splitting.
  int motherID(int) 
    { return idRadAfterSave; }
  int sisterID(int)
    { return -idRadAfterSave; }
  int * radAndEmtArr (int, int) {
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int, int)       
    { return createvector<int>(idRadAfterSave)(-idRadAfterSave); }
    //{ return createvector<int>(1)(-1); }
  double gaugeFactor    ( int=0, int=0 ) {
    //return pow2(particleDataPtr->charge(idRadAfterSave));
    double chg = pow2(particleDataPtr->charge(idRadAfterSave));
    if (abs(idRadAfterSave)<10) chg *= 3;
    return chg;
  }
  double symmetryFactor ( int=0, int=0 )
    { return 1./double(nchSaved) * 0.5; }
    //{ return 1.; /* heuristic fix to make agree better with MEC */ }
  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int, int, int, int) { return make_pair(0,0); }

  // All charged particles are potential recoilers.
  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // All charged particles are potential recoilers.
  int set_nCharged( const Event& state);
  int get_nCharged( const Event& state, int radID = 0, double t = -1.);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double /*m2dip*/);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double /*pT2Old*/, double /*m2dip*/, int /*order*/ = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double /*z*/, double /*m2dip*/, int /*order*/ = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state, int orderNow);

};

//==========================================================================

class Dire_fsr_u1new_A2SS : public Dire_fsr_u1new_A2FF {

public:  

  Dire_fsr_u1new_A2SS(int idRadAfterIn, bool hasHardRadIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface)
      : Dire_fsr_u1new_A2FF(idRadAfterIn, hasHardRadIn, idIn, softRS, settings, particleData,
        rndm, beamA, beamB, coupSM, info, direInfo, slhaInterface) {}

};

//==========================================================================

class Dire_isr_u1new_Q2QA : public DireSplittingU1new {

public:  

  Dire_isr_u1new_Q2QA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  //bool allowedRec(const Event& state, int iRec) {
  //  return state[iRec].isCharged() /*&& state[iRec].isQuark()*/;
  //}

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

class Dire_isr_u1new_A2QQ : public DireSplittingU1new {

public:  

  Dire_isr_u1new_A2QQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

class Dire_isr_u1new_Q2AQ : public DireSplittingU1new {

public:  

  Dire_isr_u1new_Q2AQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector<pair<int,int> > radAndEmtCols(int, int colType, Event state) {
    int newCol    = state.nextColTag();
    if (colType > 0) return createvector<pair<int,int> >
      (make_pair(newCol,0))(make_pair(newCol,0));
    return createvector<pair<int,int> >
      (make_pair(0,newCol))(make_pair(0,newCol));
  }

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

class Dire_isr_u1new_L2LA : public DireSplittingU1new {

public:  

  Dire_isr_u1new_L2LA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  //bool allowedRec(const Event& state, int iRec) {
  //  return (state[iRec].isLepton()
  //       || state[iRec].isCharged()
  //  //return ((state[iRec].isLepton() && state[iRec].isCharged())
  //       || state[iRec].idAbs() == 900012
  //       || state[iRec].idAbs() == 900040);
  //}

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    vector< pair<int,int> > ret
     = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
    return ret;
  }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  vector <int> recPositions( const Event& state, int iRad, int iEmt);

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

class Dire_isr_u1new_A2LL : public DireSplittingU1new {

public:  

  Dire_isr_u1new_A2LL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    vector< pair<int,int> > ret
     = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
    return ret;
  }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

class Dire_isr_u1new_L2AL : public DireSplittingU1new {

public:  

  Dire_isr_u1new_L2AL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo,
    SLHAinterface* slhaInterface) :
    DireSplittingU1new(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo, slhaInterface){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    vector< pair<int,int> > ret
     = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
    return ret;
  }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  // Pick z for new splitting.
  double zSplit(double zMinAbs, double zMaxAbs, double m2dip);

  // New overestimates, z-integrated versions.
  double overestimateInt(double zMinAbs,double zMaxAbs,
    double pT2Old, double m2dip, int order = -1);

  // Return kernel for new splitting.
  double overestimateDiff(double z, double m2dip, int order = -1);

  // Functions to calculate the kernel from SplitInfo information.
  bool calc(const Event& state = Event(), int order = -1);

};

} // end namespace Pythia8

#endif
