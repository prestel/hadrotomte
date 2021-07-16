
#ifndef Pythia8_DireSplittingsQCDCS_H
#define Pythia8_DireSplittingsQCDCS_H

#define ZETA3 1.202056903159594
#define DIRE_SPLITTINGSQCDCS_VERSION "2.004"

#include "Pythia8/Basics.h"
#include "Pythia8/Pythia.h"
#include "Pythia8/BeamParticle.h"
#include "Pythia8/ParticleData.h"
#include "Pythia8/PythiaStdlib.h"
#include "Pythia8/Settings.h"
#include "Pythia8/StandardModel.h"

#include "Dire/Splittings.h"

namespace Pythia8 {

//==========================================================================

class CSSplittingQCD : public DireSplitting {

public:  

  // Constructor and destructor.
  CSSplittingQCD(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) : DireSplitting(idIn,
      softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo)
    { init(); }
  virtual ~CSSplittingQCD() {}

  void init();

  // VARIABLES
  double CA, TR, CF, pTmin, pT2minVariations;
  int NF_qcd_fsr, orderSave;
  double alphaSvalue;
  bool usePDFalphas, doCorrelations;
  double alphaS2pi;

  AlphaStrong alphaS;

  static const double SMALL_TEVOL;

  // AUXILIARY FUNCTIONS
  double getNF(double pT2);
  double GammaQCD2(double NF=5.);
  double GammaQCD3(double NF=5.);
  double betaQCD0(double NF=5.);
  double betaQCD1(double NF=5.);
  double betaQCD2(double NF=5.);

  // Function to calculate the correct running coupling/2*Pi value, including
  // renormalisation scale variations + threshold matching.
  double as2Pi  ( double pT2, int orderNow = -1, double renormMultFacNow = -1.);

  double softRescaleInt(int order);
  double softRescaleDiff(int order, double pT2, double renormMultFacNow = -1.);

  double polevl(double x,double* coef,int N );
  double  DiLog(double x);

  vector<int> sharedColor(const Event& event, int iRad, int iRec);
  int findCol(int col, vector<int> iExc, const Event&, int type);

  bool useFastFunctions() { return true; }
  virtual bool canUseForBranching() { return true; }
  int nEmissions() { return 1; }

  virtual vector <int> radAndEmt(int idDaughter, int)
   { return createvector<int>(motherID(idDaughter))(sisterID(idDaughter)); } 

  vector<pair<int,int> > radAndEmtCols(int iRadBef, int colType, Event state) {

    int colRad(0), acolRad(0), colEmt(0), acolEmt(0);

    if (state[iRadBef].isFinal()) {

      // Get flavour of splitting.
      int flavour = splitInfo.emtAft()->id;
      // Default flavours and colours for new particles in dipole branching.
      colRad      = state[iRadBef].col();
      acolRad     = state[iRadBef].acol();
      colEmt      = 0;
      acolEmt     = 0;
      // New colour tag required for gluon emission.
      if (flavour == 21 && colType > 0) {
        colEmt  = colRad;
        colRad  = state.nextColTag();
        acolEmt = colRad;
      } else if (flavour == 21) {
        acolEmt = acolRad;
        acolRad = state.nextColTag();
        colEmt  = acolRad;
      // New flavours for g -> q qbar; split colours.
      } else if (colType > 0) {
        colEmt  = colRad;
        colRad  = 0;
        if (colType > 0 && splitInfo.emtAft()->id < 0) {
          swap(colEmt,colRad);
          swap(acolEmt,acolRad);
        }
      } else if (colType < 0) {
        acolEmt  = acolRad;
        acolRad  = 0;
        if (colType < 0 && splitInfo.emtAft()->id > 0) {
          swap(colEmt,colRad);
          swap(acolEmt,acolRad);
        }
      }

    } else {

      int iRecBef     = splitInfo.iRecBef;
      int idRadBef    = splitInfo.radBef()->id;
      int idRad       = splitInfo.radAft()->id;
      int idEmt       = splitInfo.emtAft()->id;
      int colRadBef   = state[iRadBef].col();
      int acolRadBef  = state[iRadBef].acol();
      int colRecBef   = state[iRecBef].col();
      int acolRecBef  = state[iRecBef].acol();
      bool colMatch   = (state[iRecBef].isFinal())
                      ? (colRecBef  == colRadBef)
                      : (acolRecBef == colRadBef);
      bool acolMatch  = (state[iRecBef].isFinal())
                      ? (acolRecBef == acolRadBef)
                      : (colRecBef  == acolRadBef);
      colRad          = colRadBef;
      acolRad         = acolRadBef;
      colEmt          = 0;
      acolEmt         = 0;
      double RN2 = rndmPtr->flat();
      // q -> q + g and 50% of g -> g + g; need new colour.
      if (idEmt == 21 && ( (idRad > 0 && idRad < 9)
        || ( idRad == 21 && colMatch && acolMatch && RN2 < 0.5) ) ) {
        colRad       = state.nextColTag();
        colEmt       = colRad;
        acolEmt      = colRadBef;
      // qbar -> qbar + g and other 50% of g -> g + g; need new colour.
      } else if (idEmt == 21 && ( (idRad < 0 && idRad > -9)
        || ( idRad == 21 && colMatch && acolMatch) ) ) {
        acolRad      = state.nextColTag();
        acolEmt      = acolRad;
        colEmt       = acolRadBef;
      } else if (idRad == 21 && idEmt == 21 && colMatch && !acolMatch) {
        colRad       = state.nextColTag();
        acolRad      = acolRadBef;
        colEmt       = colRad;
        acolEmt      = colRadBef;
      } else if (idRad == 21 && idEmt == 21 && !colMatch && acolMatch) {
        colRad       = colRadBef;
        acolRad      = state.nextColTag();
        acolEmt      = acolRad;
        colEmt       = acolRadBef;
      // q -> g + q.
      } else if (idRadBef == 21 && idRad > 0) {
        colRad       = colRadBef;
        acolRad      = 0;
        colEmt       = acolRadBef;
      // qbar -> g + qbar
      } else if (idRadBef == 21) {
        acolRad      = acolRadBef;
        colRad       = 0;
        acolEmt      = colRadBef;
      // g -> q + qbar.
      } else if (idRadBef > 0 && idRadBef < 9) {
        acolRad      = state.nextColTag();
        acolEmt      = acolRad;
      // g -> qbar + q.
      } else if (idRadBef < 0 && idRadBef > -9) {
        colRad       = state.nextColTag();
        colEmt       = colRad;
      }
      // Swap colours if radiated gluon carries momentum fraction z
      int colSave = colEmt, acolSave = acolEmt;
      if (swapRadEmt()) {
        colEmt  = acolRad;
        acolEmt = colRad;
        colRad  = acolSave;
        acolRad = colSave;
      }
    }

    // Done.
    return createvector<pair<int,int> >
      (make_pair(colRad,acolRad))(make_pair(colEmt,acolEmt));
  }

  virtual bool isPartial()  { return true; }

  virtual int couplingType (int, int) { return 1; }
  virtual double coupling (double z =-1., double t =-1., double m2dip =-1.,
    double renormMultFacNow = -1.,
    pair<int,bool> radBef = pair<int,bool>(),
    pair<int,bool> recBef = pair<int,bool>()) {

    // Return fixed reference coupling value (e.g. for norm in merging).
    if (t < 0.) return (alphaSvalue / (2.*M_PI));

    double scale2 = couplingScale2 ( z, t, m2dip, radBef, recBef);
    if (scale2 < 0.) scale2 = t;
    if (z      < 0.) scale2 = t;
    // Return coupling. Set up such the argument is NOT RESCALED in as2Pi 
    // function - rather guarantee that INPUT scale has desired value.
    double fac = (renormMultFacNow > 0.) ? renormMultFacNow : renormMultFac;
    return as2Pi(scale2, orderSave, fac);
  }
  virtual double couplingScale2 (double, double t, double, pair<int,bool>,
    pair<int,bool>) {
    return t;
  }

  // Functions to calculate CS variables from the evolution variables.
  virtual double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
    //double yCS = t/m2dip / (1.-z);
    //return yCS;
  }
  virtual double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
    //double zCS = ( 1. - z - t/m2dip - pow2(1.-z) )
    //           / ( 1. - z - t/m2dip);
    //return zCS;
  }
  virtual double xcs_fi(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  virtual double zcs_fi(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  virtual double xcs_if(double z, double t, double m2dip) { 
    if (false) cout << z*t*m2dip;
    return z;
  }
  virtual double ucs_if(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  virtual double xcs_ii(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  virtual double vcs_ii(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }

  // Functions to calculate Dire variables from the evolution variables.
  virtual double tdire_ff(double z, double t, double m2dip) { 
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return ycs*(1-ycs)*(1-zcs)*m2dip;
  }
  virtual double zdire_ff(double z, double t, double m2dip) {
    double ycs = ycs_ff(z,t,m2dip);
    double zcs = zcs_ff(z,t,m2dip);
    return 1.-(1-ycs)*(1-zcs);
  }
  virtual double tdire_fi(double z, double t, double m2dip) {
    double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return m2dip*(1-xcs)*(1.-zcs);
  }
  virtual double zdire_fi(double z, double t, double m2dip) {
    //double xcs = xcs_fi(z,t,m2dip);
    double zcs = zcs_fi(z,t,m2dip);
    return zcs;
  }
  virtual double tdire_if(double z, double t, double m2dip) {
    double xcs = xcs_if(z,t,m2dip);
    double ucs = ucs_if(z,t,m2dip);
    return m2dip*ucs*(1-xcs);
  }
  virtual double zdire_if(double z, double t, double m2dip) {
    double xcs = xcs_if(z,t,m2dip);
    //double ucs = ucs_if(z,t,m2dip);
    return xcs;
  }
  virtual double tdire_ii(double z, double t, double m2dip) {
    double xcs = xcs_ii(z,t,m2dip);
    double vcs = vcs_ii(z,t,m2dip);
    return m2dip*vcs*(1-vcs-xcs);
  }
  virtual double zdire_ii(double z, double t, double m2dip) {
    double xcs = xcs_ii(z,t,m2dip);
    double vcs = vcs_ii(z,t,m2dip);
    return xcs + vcs;
  }

  int kinMap () { return 99; }

  // Functions that allow different ordering variables for emissions.
  // Note: Only works after splitInfo has been properly filled.
  virtual double getJacobian( const Event& = Event(),
    PartonSystems* partonSystems = 0);
  virtual unordered_map<string, double> getPhasespaceVars(const Event& = Event(),
    PartonSystems* = 0);

};

//==========================================================================

class CS_fsr_qcd_Q2QG : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2QG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_fsr_qcd_Q2GQ : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2GQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_fsr_qcd_G2GG1 : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG1(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_fsr_qcd_G2GG2 : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG2(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool swapRadEmt() { return true; }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_fsr_qcd_G2QQ : public CSSplittingQCD {

public:  

  int idRadAfterSave;

  CS_fsr_qcd_G2QQ(int idRadAftIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idRadAfterSave(idRadAftIn) {}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  bool isPartial() { return false; }

  // Return id of mother after splitting.
  int motherID(int) 
    { return idRadAfterSave; }
  int sisterID(int)
    { return -idRadAfterSave; }
  vector <int> radAndEmt(int, int)       
    { return createvector<int>(idRadAfterSave)(-idRadAfterSave); }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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





//==========================================================================
//==========================================================================
//==========================================================================

class CS_fsr_qcd_Q2QG_soft : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2QG_soft(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip*1./z;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }

  double couplingScale2 (double z, double t, double m2dip,
    pair<int,bool>, pair<int,bool>) {
    double ycs(ycs_ff(z,t,m2dip)), zcs(zcs_ff(z,t,m2dip));
    return m2dip*ycs*(1-zcs)/zcs;
  }

};

//==========================================================================

class CS_fsr_qcd_Q2GQ_soft : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2GQ_soft(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip*1./z;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double z, double t, double m2dip,
    pair<int,bool>, pair<int,bool>) {
    double ycs(ycs_ff(z,t,m2dip)), zcs(zcs_ff(z,t,m2dip));
    return m2dip*ycs*(1-zcs)/zcs;
  }

};

//==========================================================================

class CS_fsr_qcd_G2GG1_soft : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG1_soft(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip*1./z;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double z, double t, double m2dip,
    pair<int,bool>, pair<int,bool>) {
    double ycs(ycs_ff(z,t,m2dip)), zcs(zcs_ff(z,t,m2dip));
    return m2dip*ycs*(1-zcs)/zcs;
  }

};

//==========================================================================

class CS_fsr_qcd_G2GG2_soft : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG2_soft(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool swapRadEmt() { return true; }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip*1./z;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double z, double t, double m2dip,
    pair<int,bool>, pair<int,bool>) {
    double ycs(ycs_ff(z,t,m2dip)), zcs(zcs_ff(z,t,m2dip));
    return m2dip*ycs*(1-zcs)/zcs;
  }

};

//==========================================================================

class CS_fsr_qcd_Q2QG_coll : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2QG_coll(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double, double t, double,
    pair<int,bool>, pair<int,bool>) {
    return t;
  }

};

//==========================================================================

class CS_fsr_qcd_Q2GQ_coll : public CSSplittingQCD {

public:  

  CS_fsr_qcd_Q2GQ_coll(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double, double t, double,
    pair<int,bool>, pair<int,bool>) {
    return t;
  }

};

//==========================================================================

class CS_fsr_qcd_G2GG1_coll : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG1_coll(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double, double t, double,
    pair<int,bool>, pair<int,bool>) {
    return t;
  }

};

//==========================================================================

class CS_fsr_qcd_G2GG2_coll : public CSSplittingQCD {

public:  

  CS_fsr_qcd_G2GG2_coll(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool swapRadEmt() { return true; }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double, double t, double,
    pair<int,bool>, pair<int,bool>) {
    return t;
  }

};

//==========================================================================

class CS_fsr_qcd_G2QQ_coll : public CSSplittingQCD {

public:  

  int idRadAfterSave;

  CS_fsr_qcd_G2QQ_coll(int idRadAftIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idRadAfterSave(idRadAftIn) {}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  bool isPartial() { return false; }

  // Return id of mother after splitting.
  int motherID(int) 
    { return idRadAfterSave; }
  int sisterID(int)
    { return -idRadAfterSave; }
  vector <int> radAndEmt(int, int)       
    { return createvector<int>(idRadAfterSave)(-idRadAfterSave); }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return t/m2dip;
  }
  double zcs_ff(double z, double t, double m2dip) {
    if (false) cout << z*t*m2dip;
    return z;
  }
  double couplingScale2 (double, double t, double,
    pair<int,bool>, pair<int,bool>) {
    return t;
  }

};

//==========================================================================
//==========================================================================
//==========================================================================




















//==========================================================================

class CS_isr_qcd_Q2QG : public CSSplittingQCD {

public:  

  CS_isr_qcd_Q2QG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_isr_qcd_G2GG1 : public CSSplittingQCD {

public:  

  CS_isr_qcd_G2GG1(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_isr_qcd_G2GG2 : public CSSplittingQCD {

public:  

  CS_isr_qcd_G2GG2(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_isr_qcd_G2QQ : public CSSplittingQCD {

public:  

  CS_isr_qcd_G2QQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  bool isPartial() { return false; }

  // Return id of mother after splitting.
  int motherID(int idDaughter);

  // Return id of emission.
  int sisterID(int idDaughter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

class CS_isr_qcd_Q2GQ : public CSSplittingQCD {

public:  

  int idRadAfterSave;
  CS_isr_qcd_Q2GQ(int idRadAftIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    CSSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idRadAfterSave(idRadAftIn) {}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  bool isPartial() { return false; }

  // Return id of mother after splitting.
  int motherID(int) 
    { return idRadAfterSave; }
  int sisterID(int)
    { return idRadAfterSave; }
  vector <int> radAndEmt(int, int)       
    { return createvector<int>(idRadAfterSave)(idRadAfterSave); }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  vector <int> recPositions( const Event&, int, int);

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

//==========================================================================

} // end namespace Pythia8

#endif
