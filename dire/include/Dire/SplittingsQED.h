
#ifndef Pythia8_DireSplittingsQED_H
#define Pythia8_DireSplittingsQED_H

#define DIRE_SPLITTINGSQED_VERSION "2.004"

#include "Pythia8/Basics.h"
#include "Pythia8/Pythia.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/StandardModel.h"

#include "Dire/SplittingsQCD.h"

namespace Pythia8 {

//==========================================================================

class DireSplittingQED : public DireSplittingQCD {

public:  

  // Constructor and destructor.
  DireSplittingQED(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) : DireSplittingQCD(idIn,
      softRS,settings,particleData,rndm,beamA,beamB,coupSM,info, direInfo)
    { init(); }
  virtual ~DireSplittingQED() {}

  void init();

  // VARIABLES
  double aem0, pT2min,
         pT2minL, pT2minQ, pT2minA, pT2minForcePos, pT2minAllowNeg, pT2minMECs;
  bool doFSRQEDshowerByQ, doFSRQEDshowerByL;
  bool doISRQEDshowerByQ, doISRQEDshowerByL;
  bool doForcePos;
  double overInt1, overInt2, xInProxy;

  AlphaEM     alphaEM;

  // Function to calculate the correct running coupling/2*Pi value, including
  // renormalisation scale variations + threshold matching.
  double aem2Pi ( double pT2, int = 0);

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

  virtual int couplingType (int, int) { return 2; }

  virtual double coupling (double z=-1., double pT2=-1., double m2dip=-1.,
    double renormMultFacNow = -1.,
    pair<int,bool> radBef = pair<int,bool>(),
    pair<int,bool> recBef = pair<int,bool>()) {
    // At present, we only use the Thompson value of the coupling, i.e. at
    // zero momemtum transfer.
    return (aem0 / (2.*M_PI));
//return 0.1 / (2.*M_PI);
    // Return fixed reference coupling value (e.g. for norm in merging).
    //return 1./(2.*M_PI);
    //return 10.*settingsPtr->parm("StandardModel:alphaEM0")/(2.*M_PI);
    if (pT2< 0.) return (aem0 / (2.*M_PI));
    double scale2 = couplingScale2 ( z, pT2, m2dip, radBef, recBef);
    if (scale2 < 0.) scale2 = pT2;
    if (z      < 0.) scale2 = pT2;
    if (renormMultFacNow>0.) pT2 *= renormMultFacNow;
    // Return coupling.
    return aem2Pi(scale2);
  }

  virtual double couplingScale2 (double z, double pT2, double m2dip,
    pair<int,bool> radBef, pair<int,bool> recBef) {
    //return -1.;
    return pT2;
    if        ( radBef.second &&  recBef.second) {
      double ycs = pT2/m2dip/(1.-z);
      double sij = ycs*m2dip;
      return sij;
    } else if ( radBef.second && !recBef.second) {
      double zcs = z;
      double xcs = m2dip * zcs * (1.-zcs) / (pT2 + m2dip * zcs * (1.-zcs));
      return m2dip * (1.-xcs) / xcs;
    } else if (!radBef.second &&  recBef.second) {
      double xcs = z;
      return m2dip * (1-xcs) / xcs;
    } else if (!radBef.second && !recBef.second) {
      double xcs = ( z * (1.-z) - pT2/m2dip) / (1.-z);
      return m2dip / xcs;
    }
    return -1.;
  }

  virtual double tCutoff( const Particle& radBef, const Particle& recBef,
    PartonSystems* partonSystemsPtr = NULL);
  virtual bool aboveCutoff( double t, const Particle& radBef,
    const Particle& recBef, int iSys = 0,
    PartonSystems* partonSystemsPtr = NULL);
  virtual bool dipoleAboveCutoff( double, int = 0, int = 0, double = -1.);

  bool allowedRec(const Event& state, int iRec);
  bool allowedQuarkRadRecPair(const Event& state, int iRad, int iRec);
  bool allowedLeptonRadRecPair(const Event& state, int iRad, int iRec);
  double forceChargeFactor(double charge, double pT2, const Event & state);

  virtual double chargeFactor ( int idRadBef, int idRecBef, bool) {
    return gaugeFactor (idRadBef, idRecBef);
  }

};

//==========================================================================

class Dire_fsr_qed_Q2QA : public DireSplittingQED {

public:  

  Dire_fsr_qed_Q2QA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

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

class Dire_fsr_qed_Q2AQ : public DireSplittingQED {

public:  

  Dire_fsr_qed_Q2AQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

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

class Dire_fsr_qed_L2LA : public DireSplittingQED {

public:  

  Dire_fsr_qed_L2LA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0, 0));
  }

  double gaugeFactor ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 );

  double chargeFactor ( int idRadBef, int idRecBef, bool /*isOverEst*/) {
    double chg = gaugeFactor (idRadBef, idRecBef);
    //if (chg < 0. && isOverEst) chg = 10.*abs(chg);
    return chg;
  }

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

class Dire_fsr_qed_L2AL : public DireSplittingQED {

public:  

  Dire_fsr_qed_L2AL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0, 0));
  }

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

class Dire_fsr_qed_A2FF : public DireSplittingQED {

public:  

  int idRadAfterSave;
  bool hasHardRadiator;
  double nchSaved;

  Dire_fsr_qed_A2FF(int idRadAfterIn, bool hasHardRadIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) : DireSplittingQED(idIn, 
    softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo),
    idRadAfterSave(idRadAfterIn), hasHardRadiator(hasHardRadIn), nchSaved(1) {
    radAndEmtArray [0] = idRadAfterSave;
    radAndEmtArray [1] =-idRadAfterSave;
    radAndEmtArray [2] = 0;
  }

  // Virtuality ordering.
  int typeEvolutionMeasure() { return 2; }

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
    { return t/m2dip; }
  double zcs_ff(double z, double t, double m2dip) {
    double yCS = ycs_ff(z,t,m2dip);
    double zCS = 1. - (1.-z)/(1.-yCS);
    return zCS; 
  }
  double xcs_fi(double, double t, double m2dip) {
    double virt = t;
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
  double gaugeFactor    ( int=0, int=0 );
  double symmetryFactor ( int=0, int=0 )
    { return 1./double(nchSaved) * 0.5 /*0.5 because each flavor appears twice*/; }

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

class Dire_isr_qed_Q2QA : public DireSplittingQED {

public:  

  Dire_isr_qed_Q2QA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

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

class Dire_isr_qed_A2QQ : public DireSplittingQED {

public:  

  Dire_isr_qed_A2QQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(0, 0))(make_pair(state[iRad].acol(),state[iRad].col()));
  }

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

class Dire_isr_qed_Q2AQ : public DireSplittingQED {

public:  

  Dire_isr_qed_Q2AQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int colType, Event state) {
    int newCol    = state.nextColTag();
    if (colType > 0) return createvector<pair<int,int> >
      (make_pair(newCol,0))(make_pair(newCol,0));
    return createvector<pair<int,int> >
      (make_pair(0,newCol))(make_pair(0,newCol));
  }

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

class Dire_isr_qed_L2LA : public DireSplittingQED {

public:  

  Dire_isr_qed_L2LA(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0,0));
  }

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

class Dire_isr_qed_A2LL : public DireSplittingQED {

public:  

  Dire_isr_qed_A2LL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0,0));
  }

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

class Dire_isr_qed_L2AL : public DireSplittingQED {

public:  

  Dire_isr_qed_L2AL(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

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

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0,0));
  }

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

//==========================================================================

class Dire_fsr_qed_Q2QA_notPartial : public DireSplittingQED {

public:  

  Dire_fsr_qed_Q2QA_notPartial(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state) {
    return createvector<pair<int,int> >
      (make_pair(state[iRad].col(),state[iRad].acol()))(make_pair(0, 0));
  }

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

class Dire_fsr_qed_L2LA_notPartial : public DireSplittingQED {

public:  

  Dire_fsr_qed_L2LA_notPartial(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap ();
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  vector<pair<int,int> > radAndEmtCols(int, int, Event) {
    return createvector<pair<int,int> > (make_pair(0,0))(make_pair(0,0));
  }

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

class Dire_fsr_qed_L2Lffbar : public DireSplittingQED {

public:  

  Dire_fsr_qed_L2Lffbar(int idEmtAfterIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idEmtAfterSave(idEmtAfterIn),
      is_sai_endpoint_save(false) {
    nGluonToQuark = settingsPtr->mode("TimeShower:nGluonToQuark");
    radAndEmtArray [1] = idEmtAfterSave;
    radAndEmtArray [2] =-idEmtAfterSave;
  }

  virtual double coupling (double =-1., double =-1., double =-1., double =-1,
    pair<int,bool> = pair<int,bool>(), pair<int,bool> = pair<int,bool>()) {
    return pow2(aem0 / (2.*M_PI));
  }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int * radAndEmtArr (int idRadBef, int) {
    radAndEmtArray [0] = idRadBef;
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int idRadBef, int) { 
    return createvector<int>(idRadBef)(idEmtAfterSave)(-idEmtAfterSave);
  }

  int nEmissions()            { return 2;}
  int kinMap()                { return 2;}
  bool canUseForBranching()   { return true; }

  vector<pair<int,int> > radAndEmtCols(int iRad, int colType, Event state);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event& state, int iRad, int iEmt1,
    int iEmt2);

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

  int nGluonToQuark, idEmtAfterSave;

  bool isPartial()  { return false; }
  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return false; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = false; }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

//==========================================================================

class Dire_isr_qed_L2Lffbar : public DireSplittingQED {

public:  

  Dire_isr_qed_L2Lffbar(int idEmtAfterIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQED(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idEmtAfterSave(idEmtAfterIn),
      is_sai_endpoint_save(false) {
    nGluonToQuark = settingsPtr->mode("TimeShower:nGluonToQuark");
    radAndEmtArray [1] = idEmtAfterSave;
    radAndEmtArray [2] =-idEmtAfterSave;
  }

  virtual double coupling (double =-1., double =-1., double =-1., double =-1,
    pair<int,bool> = pair<int,bool>(), pair<int,bool> = pair<int,bool>()) {
    return pow2(aem0 / (2.*M_PI));
  }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int * radAndEmtArr (int idRadBef, int) {
    radAndEmtArray [0] = idRadBef;
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int idRadBef, int) { 
    return createvector<int>(idRadBef)(idEmtAfterSave)(-idEmtAfterSave);
  }

  int nEmissions()            { return 2;}
  int kinMap()                { return 2;}
  bool canUseForBranching()   { return true; }

  vector<pair<int,int> > radAndEmtCols(int iRad, int colType, Event state);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);
  vector <int> recPositions( const Event& state, int iRad, int iEmt1,
    int iEmt2);

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

  int nGluonToQuark, idEmtAfterSave;

  bool isPartial()  { return false; }
  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return false; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = false; }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

} // end namespace Pythia8

#endif
