
#ifndef Pythia8_DireSplittingsQCD_H
#define Pythia8_DireSplittingsQCD_H

#define ZETA3 1.202056903159594
#define DIRE_SPLITTINGSQCD_VERSION "2.004"

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

class DireSplittingQCD : public DireSplitting {

public:  

  // Constructor and destructor.
  DireSplittingQCD(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) : DireSplitting(idIn,
      softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo)
    { init();
      asSchemeISR=settingsPtr->mode("DireSpace:alphasScheme");
      asSchemeFSR=settingsPtr->mode("DireTimes:alphasScheme");
     }
  virtual ~DireSplittingQCD() {}

  void init();

  // VARIABLES
  double CA, TR, CF, pTmin, pT2minVariations;
  int NF_qcd_fsr, orderSave;
  bool usePDFalphas, doCorrelations;
  double alphaSvalue, alphaSorder, alphaS2pi;

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
  double beta0Endpoint(int order, double m2dip, double pT2, double z, 
    double renormMultFacNow = -1.);

  double polevl(double x,double* coef,int N );
  double  DiLog(double x);

  vector<int> sharedColor(const Event& event, int iRad, int iRec);
  bool hasSharedColor(const Event& event, int iRad, int iRec);

  int findCol(int col, vector<int> iExc, const Event&, int type);

  bool useFastFunctions() { return true; }

  virtual int * radAndEmtArr (int idDaughter, int) {
    radAndEmtArray [0] = motherID(idDaughter);
    radAndEmtArray [1] = sisterID(idDaughter);
    radAndEmtArray [2] = 0;
    return radAndEmtArray;
  }
  virtual vector <int> radAndEmt(int idDaughter, int)
   { return createvector<int>(motherID(idDaughter))(sisterID(idDaughter)); } 
  virtual bool isPartial()  { return true; }

  virtual int couplingType (int, int) { return 1; }
  virtual double coupling (double z =-1., double pT2 =-1., double m2dip =-1.,
    double renormMultFacNow = -1.,
    pair<int,bool> radBef = pair<int,bool>(),
    pair<int,bool> recBef = pair<int,bool>()) {

    //pT2 *= 4.;

    // Return fixed reference coupling value (e.g. for norm in merging).
    if (pT2< 0.) return (alphaSvalue / (2.*M_PI));

    if (!usePDFalphas && alphaSorder == 0) return alphaS2pi;
    double scale2 = couplingScale2 ( z, pT2, m2dip, radBef, recBef);
    if (scale2 < 0.) scale2 = pT2;
    if (z      < 0.) scale2 = pT2;
    // Return coupling. Set up such the argument is NOT RESCALED in as2Pi 
    // function - rather guarantee that INPUT pT2/scale has desired value.
    double fac = (renormMultFacNow > 0.) ? renormMultFacNow : renormMultFac;
    return as2Pi(scale2, orderSave, fac);
  }

  // Function determining the argument of the running coupling based on the
  // splitting variables. Current default: Evolution variable.
  // DireTimes:alphasScheme = 0 : default
  // DireTimes:alphasScheme = 1 : collinear kinematic kT for all splittings
  //                              involving incoming particles.
  // DireTimes:alphasScheme = 2 : eikonal factor sij*sjk/sik
  int asSchemeISR, asSchemeFSR;
  virtual double couplingScale2 (double z, double pT2, double m2dip,
    pair<int,bool> radBef, pair<int,bool> recBef);

  virtual int kinMap() {
    return 1;
  }

  // Functions that allow different ordering variables for emissions.
  // Note: Only works after splitInfo has been properly filled.
  virtual double getJacobian( const Event& = Event(),
    PartonSystems* partonSystems = 0);
  virtual unordered_map<string, double> getPhasespaceVars(const Event& = Event(),
    PartonSystems* = 0);

  bool useBackboneGluons, doGeneralizedKernel;
  double sCoef(int powz) { vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:softCoeffs:" + name());
    return tmp[powz+1]; }
  double sExp(int powz) { vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:softExps:" + name());
    return tmp[powz+1]; }
  double kCoef(int powz) { vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:kappaCoeffs:" + name());
    return tmp[powz+1]; }
  double kExp(int powz){ vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:kappaExps:" + name());
    return tmp[powz+1]; }
  double cCoef(int powz) { vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:collCoeffs:" + name());
    return tmp[powz+1]; }
  double cExp(int powz) { vector<double> tmp
    = settingsPtr->pvec("DireGeneralizedKernel:collExps:" + name());
    return tmp[powz+1]; }
  double fCoef() { double tmp
    = settingsPtr->parm("DireGeneralizedKernel:finCoeffs:" + name());
    return tmp; }

  //bool hasMECBef(const Event& state, double pT2);
  //bool hasMECAft(const Event& state, double pT2);

  virtual double tCutoff( const Particle& radBef, const Particle& recBef,
    PartonSystems* partonSystemsPtr = NULL);
  virtual bool aboveCutoff( double, const Particle&, const Particle&, int = 0,
    PartonSystems* = NULL);
  virtual bool dipoleAboveCutoff( double, int = 0, int = 0, double = -1.);

};

//==========================================================================

class Dire_fsr_qcd_Q2QGG : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2QGG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), is_sai_endpoint_save(false) {
    radAndEmtArray [1] = 21;
    radAndEmtArray [2] = 21;
  }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int * radAndEmtArr (int idDaughter, int) {
    radAndEmtArray [0] = idDaughter;
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int idDaughter, int) {
    return createvector<int>(idDaughter)(21)(21);}
  int nEmissions()          { return 2; }
  int kinMap()              { return 2;}
  bool canUseForBranching() { return true; }

  vector<pair<int,int> > radAndEmtCols(int iRad, int colType, Event state); 

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

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

  double counterTerm(double si1, double si2, double sj1,
    double sj2, double sij, double s12);

  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return true; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = (rndmPtr->flat() < 0.5); }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

//==========================================================================

class Dire_fsr_qcd_G2GGG : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2GGG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), is_sai_endpoint_save(false) {
    radAndEmtArray [0] = 21;
    radAndEmtArray [1] = 21;
    radAndEmtArray [2] = 21;
  }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int * radAndEmtArr (int, int) {
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int,int) { return createvector<int>(21)(21)(21);}
  int nEmissions()                { return 2; }
  int kinMap()                    { return 2;}
  bool canUseForBranching()       { return true; }

  vector<pair<int,int> > radAndEmtCols(int iRad, int colType, Event state);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

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

  double counterTerm(double si1, double si2, double sj1,
    double sj2, double sij, double s12);

  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return true; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = (rndmPtr->flat() < 0.5); }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

//==========================================================================

class Dire_fsr_qcd_Q2Qqqbar : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2Qqqbar(int idEmtAfterIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idEmtAfterSave(idEmtAfterIn),
      is_sai_endpoint_save(false) {
    nGluonToQuark = settingsPtr->mode("TimeShower:nGluonToQuark");
    radAndEmtArray [1] = idEmtAfterSave;
    radAndEmtArray [2] =-idEmtAfterSave;
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

  double counterTerm(double si1, double si2, double sj1,
    double sj2, double sij, double s12);

  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return true; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = (rndmPtr->flat() < 0.5); }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

//==========================================================================

class Dire_fsr_qcd_G2Gqqbar : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2Gqqbar(int idEmtAfterIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo), idEmtAfterSave(idEmtAfterIn)
      { nGluonToQuark = settingsPtr->mode("TimeShower:nGluonToQuark"); }

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int * radAndEmtArr (int, int colType) {
    int sign = (colType > 0) ? 1 : -1; 
    int idEmtAft = sign * idEmtAfterSave;
    radAndEmtArray [0] = 21;
    radAndEmtArray [1] = idEmtAft;
    radAndEmtArray [2] =-idEmtAft;
    return radAndEmtArray;
  }
  vector <int> radAndEmt(int, int colType) { 
    int sign = (colType > 0) ? 1 : -1; 
    int idEmtAft = sign * idEmtAfterSave;
    return createvector<int>(21)(idEmtAft)(-idEmtAft);
  }

  int nEmissions()            { return 2; }
  int kinMap()                { return 2;}
  bool canUseForBranching()   { return true; }

  vector<pair<int,int> > radAndEmtCols(int iRad, int colType, Event state);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int colRadAfter, int acolRadAfter, 
    int colEmtAfter, int acolEmtAfter);

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

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

  double counterTerm(double si1, double si2, double sj1,
    double sj2, double sij, double s12);

  // Treatment of additional virtual corrections.
  bool allow_sai_endpoint_for_kinematics() { return true; }
  bool allow_xa_endpoint_for_kinematics()  { return false; }
  // Functions to set if kernel should contribute to a kinematical endpoint. 
  void try_sai_endpoint() { is_sai_endpoint_save = (rndmPtr->flat() < 0.5); }
  void try_xa_endpoint()                   { return; }
  // Return endpoint information. 
  bool is_sai_endpoint()                   { return is_sai_endpoint_save; }
  bool is_xa_endpoint()                    { return false; }
  bool is_sai_endpoint_save;

};

//==========================================================================

class Dire_fsr_qcd_Q2QG : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2QG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  int nEmissions() { return 1; }

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  //int kinMap ();

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

class Dire_fsr_qcd_Q2GQ : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2GQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_fsr_qcd_G2GG1 : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2GG1(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_fsr_qcd_G2GG2 : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2GG2(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_fsr_qcd_G2FF : public DireSplittingQCD {

public:  

  int idRadAfterSave;
  bool hasHardRadiator;

  Dire_fsr_qcd_G2FF(int idRadAfterIn, bool hasHardRadIn, string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) : DireSplittingQCD(idIn, 
    softRS, settings, particleData, rndm, beamA, beamB, coupSM, info, direInfo),
    idRadAfterSave(idRadAfterIn), hasHardRadiator(hasHardRadIn) {
    radAndEmtArray [0] = idRadAfterSave;
    radAndEmtArray [1] =-idRadAfterSave;
    radAndEmtArray [2] = 0;
  }

  bool canRadiate ( const Event& state, pair<int,int> ints,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);
  bool canRadiate ( const Event& state, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int kinMap () { return 1;};
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }

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
  double gaugeFactor ( int=0, int=0 )        { return TR;}
  double symmetryFactor ( int=0, int=0 )
    { return 1./2. /*gluon has two recoilers*/ * 0.5 /*0.5 because each flavor appears twice*/; }

  // Return id of recombined radiator (before splitting!)
  int radBefID(int idRadAfter, int idEmtAfter);

  // Return colours of recombined radiator (before splitting!)
  pair<int,int> radBefCols(int, int, int, int);

  // All charged particles are potential recoilers.
  vector <int> recPositions( const Event& state, int iRad, int iEmt);

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

class Dire_fsr_qcd_G2QQ1 : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2QQ1(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }
  bool isPartial() { return false; }
  //int kinMap ();

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

class Dire_fsr_qcd_G2QQ2 : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2QQ2(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }
  bool isPartial() { return false; }

  //int kinMap ();

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

class Dire_fsr_qcd_Q2qQqbarDist : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2qQqbarDist(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 2; }
  bool isPartial() { return false; }

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

//==========================================================================

class Dire_fsr_qcd_Q2QbarQQId : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2QbarQQId(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 2; }
  bool isPartial() { return false; }

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

//==========================================================================

class Dire_isr_qcd_Q2QG : public DireSplittingQCD {

public:  

  Dire_isr_qcd_Q2QG(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_isr_qcd_G2GG1 : public DireSplittingQCD {

public:  

  Dire_isr_qcd_G2GG1(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_isr_qcd_G2GG2 : public DireSplittingQCD {

public:  

  Dire_isr_qcd_G2GG2(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  //int kinMap ();

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

class Dire_isr_qcd_G2QQ : public DireSplittingQCD {

public:  

  Dire_isr_qcd_G2QQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }
  bool isPartial() { return false; }

  //int kinMap ();

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

class Dire_isr_qcd_Q2GQ : public DireSplittingQCD {

public:  

  Dire_isr_qcd_Q2GQ(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }
  bool isPartial() { return false; }

  //int kinMap ();

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

// Class inheriting from SplittingQCD class.
class Dire_isr_qcd_Q2qQqbarDist : public DireSplittingQCD {

public:  

  Dire_isr_qcd_Q2qQqbarDist(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 2; }
  bool isPartial() { return false; }

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

//==========================================================================

class Dire_isr_qcd_Q2QbarQQId : public DireSplittingQCD {

public:  

  Dire_isr_qcd_Q2QbarQQId(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 2; }
  bool isPartial() { return false; }

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

//==========================================================================

class Dire_fsr_qcd_Q2QG_notPartial : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_Q2QG_notPartial(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  int kinMap ();
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }
  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state);

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

class Dire_fsr_qcd_G2GG_notPartial : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2GG_notPartial(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  int kinMap ();
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }
  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state);

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

class Dire_fsr_qcd_G2QQ_notPartial : public DireSplittingQCD {

public:  

  Dire_fsr_qcd_G2QQ_notPartial(string idIn, int softRS, Settings* settings,
    ParticleData* particleData, Rndm* rndm, BeamParticle* beamA,
    BeamParticle* beamB, CoupSM* coupSM, Info* info, DireInfo* direInfo) :
    DireSplittingQCD(idIn, softRS, settings, particleData, rndm, beamA, beamB,
      coupSM, info, direInfo){}

  bool canRadiate ( const Event&, pair<int,int>,
    unordered_map<string,bool> = unordered_map<string,bool>(), Settings* = NULL,
    PartonSystems* = NULL, BeamParticle* = NULL);

  bool canRadiate ( const Event&, int iRadBef, int iRecBef,
    Settings* = NULL, PartonSystems* = NULL, BeamParticle* = NULL);

  int nEmissions() { return 1; }

  int kinMap ();
  bool canUseForBranching() { return true; }
  bool isPartial()  { return false; }
  vector<pair<int,int> > radAndEmtCols(int iRad, int, Event state);

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

} // end namespace Pythia8

#endif
