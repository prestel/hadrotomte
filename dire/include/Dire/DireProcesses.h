
// Pythia includes.
#include "Pythia8/Pythia.h"
#include "Pythia8/SigmaQCD.h"
#include "Pythia8/SigmaEW.h"

#include "Dire/DireBasics.h"
#include "Dire/WeightContainer.h"
#include "Dire/Hooks.h"

namespace Pythia8 {

class DireSigmaHelper {

public:

  DireSigmaHelper() : isInit(false), usePDFalphas(false),
    hasExternalHook(false), canSetMUF(false), canSetMUR(false),
    canSetMUQ(false), renormMultFac(1.0), factorMultFac(1.0), infoPtr(0),
    settingsPtr(0), particleDataPtr(0), beamAPtr(0), beamBPtr(0),
    couplingsPtr(0), weightsPtr(0), hooksPtr(0) {}

  double muRsq( double x1, double x2, double sH, double tH, double uH, 
    bool massless, double m1sq, double m2sq, double m3sq, double m4sq);
  double muFsq( double x1, double x2, double sH, double tH, double uH, 
    bool massless, double m1sq, double m2sq, double m3sq, double m4sq);
  double muQsq( double x1, double x2, double sH, double tH, double uH, 
    bool massless, double m1sq, double m2sq, double m3sq, double m4sq);

  double alpS( double mu2R) {
    double ret = couplingsPtr->alphaS(mu2R); 
    if (usePDFalphas) ret
      = (beamAPtr != 0) ? beamAPtr->alphaS(mu2R)
                        : (beamBPtr != 0) ? beamBPtr->alphaS(mu2R)
                                          : ret;
    return ret;
  }

  void init(Info* infoPtrIn, Settings* settingsPtrIn,
    ParticleData* particleDataPtrIn, Rndm*,
    BeamParticle* beamAPtrIn, BeamParticle* beamBPtrIn,
    Couplings* couplingsPtrIn, SusyLesHouches*,
    DireWeightContainer* weightsPtrIn = 0, DireHooks* hooksPtrIn = 0);

  bool isInit, usePDFalphas, hasExternalHook, canSetMUF, canSetMUR, canSetMUQ;
  double renormMultFac, factorMultFac;

  Info* infoPtr;
  Settings* settingsPtr;
  ParticleData* particleDataPtr;
  BeamParticle* beamAPtr;
  BeamParticle* beamBPtr;
  Couplings* couplingsPtr;

  DireWeightContainer* weightsPtr;
  DireHooks* hooksPtr;

};

//==========================================================================
 
class DireSigma2gg2gg : public Pythia8::Sigma2gg2gg {
public:
  DireSigma2gg2gg() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2qqbar2qqbarNew : public Pythia8::Sigma2qqbar2qqbarNew {
public:
  DireSigma2qqbar2qqbarNew() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2qqbar2gg : public Pythia8::Sigma2qqbar2gg {
public:
  DireSigma2qqbar2gg() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2qq2qq : public Pythia8::Sigma2qq2qq {
public:
  DireSigma2qq2qq() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2qg2qg : public Pythia8::Sigma2qg2qg {
public:
  DireSigma2qg2qg() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2gg2qqbar : public Pythia8::Sigma2gg2qqbar {
public:
  DireSigma2gg2qqbar() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2gg2QQbar : public Pythia8::Sigma2gg2QQbar {
public:
  DireSigma2gg2QQbar(int in1, int in2) : Pythia8::Sigma2gg2QQbar(in1,in2)
    { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigma2qqbar2QQbar : public Pythia8::Sigma2qqbar2QQbar {
public:
  DireSigma2qqbar2QQbar(int in1, int in2) : Pythia8::Sigma2qqbar2QQbar(in1,in2)
    { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;
  
};

//==========================================================================
 
class DireSigmaSigma2ff2fft_neutral_current : public Pythia8::Sigma2ff2fftgmZ {
public:
  DireSigmaSigma2ff2fft_neutral_current(int idIn = 0) : idNew(idIn)
    { sigmaHelperPtr = 0; }

  // Input and complement kinematics for resolved 2 -> 2 process.
  void set2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in) { store2Kin( x1in, x2in, sHin, tHin, m3in, m4in,
    runBW3in, runBW4in); /*sigmaKin();*/}

  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;

  void initProc();
  void sigmaKin(); 
  double sigmaHat();

  double sigmaPDF(bool, bool, bool, double x1New, double x2New) {
    // Evaluate and store the required parton densities.
    for (int j = 0; j < sizeBeamA(); ++j) {
      if ( idNew != 0 &&  abs(inBeamA[j].id) < 10
        && abs(inBeamA[j].id) != abs(idNew)) {
        inBeamA[j].pdf = 0.0;
        continue;
      }
      if ( x1New <= 0.)
        inBeamA[j].pdf = beamAPtr->xfMax( inBeamA[j].id, x1Save, Q2FacSave);
      else
        inBeamA[j].pdf = beamAPtr->xfHard( inBeamA[j].id, x1New, Q2FacSave);
    }
    for (int j = 0; j < sizeBeamB(); ++j){
      if ( idNew != 0 && abs(inBeamB[j].id) < 10
        && abs(inBeamB[j].id) != abs(idNew)) {
        inBeamB[j].pdf = 0.0;
        continue;
      }
      if ( x2New <= 0.)
        inBeamB[j].pdf = beamBPtr->xfMax( inBeamB[j].id, x2Save, Q2FacSave);
      else
        inBeamB[j].pdf = beamBPtr->xfHard( inBeamB[j].id, x2New, Q2FacSave);
    }

    // Loop over allowed incoming channels.
    sigmaSumSave = 0.;
    for (int i = 0; i < sizePair(); ++i) {
      if ( idNew != 0 && abs(inPair[i].idA) < 10
       && abs(inPair[i].idA) != abs(idNew)) {
        inPair[i].pdfA     = 0.0;
        inPair[i].pdfSigma = 0.0;
        continue;
      }
      if ( idNew != 0 && abs(inPair[i].idB) < 10
       && abs(inPair[i].idB) != abs(idNew)) {
        inPair[i].pdfB     = 0.0;
        inPair[i].pdfSigma = 0.0;
        continue;
      }
      // Evaluate hard-scattering cross section. Include K factor.
      inPair[i].pdfSigma = sigmaHatWrap(inPair[i].idA, inPair[i].idB);
      // Multiply by respective parton densities.
      for (int j = 0; j < sizeBeamA(); ++j)
      if (inPair[i].idA == inBeamA[j].id) {
        inPair[i].pdfA      = inBeamA[j].pdf;
        inPair[i].pdfSigma *= inBeamA[j].pdf;
        break;
      }
      for (int j = 0; j < sizeBeamB(); ++j)
      if (inPair[i].idB == inBeamB[j].id) {
        inPair[i].pdfB      = inBeamB[j].pdf;
        inPair[i].pdfSigma *= inBeamB[j].pdf;
        break;
      }
      // Sum for all channels.
      sigmaSumSave += inPair[i].pdfSigma;
    }
    return sigmaSumSave;
  }

  int    id3Mass()         const {return 900012;}
  int    id4Mass()         const {return idNew;}
  //int    id4Mass()         const {return 2;}
  //int    id4Mass()         const {return 2212;}

  void setIdColAcol(); 
  string name()   const {return "f_1 f_2 -> f_3 f_4 (Zp current)";}

private:

  //  Z parameters for propagator.
  int    gmZmode, idNew;
  double mZ, mZS, thetaWRat, sigmagmgm, sigmagmZ, sigmaZZ, sigmaZZp,
         sigmaZpZp, x1new, x2new;

};

//==========================================================================

class DireSigmaSigma2ff2fft_neutral_current_elastic : public Pythia8::Sigma2ff2fftgmZ {
public:
  DireSigmaSigma2ff2fft_neutral_current_elastic() { sigmaHelperPtr = 0; }
   // Input and complement kinematics for resolved 2 -> 2 process.
  void set2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in) { store2Kin( x1in, x2in, sHin, tHin, m3in, m4in,
    runBW3in, runBW4in); /*sigmaKin();*/}
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
		  double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;

  void initProc();
  void sigmaKin();
  double sigmaHat();

  int    id3Mass()         const {return 900012;}
  int    id4Mass()         const {return 2212;}

  double sigmaPDF(bool, bool, bool, double x1New, double) {
    int idNow = inPair.front().idA;
    sigmaSumSave = sigmaHatWrap(idNow, 2212);
    double pdfA = beamAPtr->xfHard(idNow, (x1New>0.) ? x1New : x1Save, Q2FacSave);
    double pdfB = 1.;
    sigmaSumSave *= pdfA*pdfB;
    return sigmaSumSave;
  }

  void setIdColAcol();
  string name()   const {return "f_1 f_2 -> f_3 f_4 (Zp current - elastic)";}

private:

  //  Z parameters for propagator.
  int    gmZmode;
  double mZ, mZS, thetaWRat, sigmagmgm, sigmagmZ, sigmaZZ, sigmaZZp,
         sigmaZpZp, x1new, x2new;

};

//==========================================================================
 
class DireSigmaSigma2ff2fft_charged_current : public Pythia8::Sigma2ff2fftW {
public:
  DireSigmaSigma2ff2fft_charged_current() { sigmaHelperPtr = 0; }
  void store2Kin( double x1in, double x2in, double sHin,
    double tHin, double m3in, double m4in, double runBW3in,
    double runBW4in);
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;

  void initProc();
  void sigmaKin(); 
  double sigmaHat();
  void setIdColAcol(); 
  string name()   const {return "f_1 f_2 -> f_3 f_4 (Wp current)";}

private:

  //  W parameters for propagator.
  double mW, mWS, thetaWRat, sigma0;
 
};

//==========================================================================

class DireSigmaSigma2ff2fftW : public Pythia8::Sigma2ff2fftW {

public:

  // Constructor.
  DireSigmaSigma2ff2fftW(int id3In = 0, int id4In = 0) 
    : mWS(), thetaWRat(), sigma0(), id3Save(id3In), id4Save(id4In) {
    sigmaHelperPtr = 0;
  }
  void setHelper( DireSigmaHelper* sigmaHelperPtrIn) {
    sigmaHelperPtr = sigmaHelperPtrIn;
  }
  DireSigmaHelper* sigmaHelperPtr;

  /*// Initialize process.
  virtual void initProc();

  // Calculate flavour-independent parts of cross section.
  virtual void sigmaKin();

  // Evaluate sigmaHat(sHat).
  virtual double sigmaHat();

  // Select flavour, colour and anticolour.
  virtual void setIdColAcol();

  // Info on the subprocess.
  virtual string name()   const {return "f_1 f_2 -> f_3 f_4 (t-channel W+-)";}
  virtual int    code()   const {return 212;}
  virtual string inFlux() const {return "ff";}*/

  int    id3Mass()         const {return id3Save;}
  int    id4Mass()         const {return id4Save;}

private:

  //  W parameters for propagator.
  double mW, mWS, thetaWRat, sigma0;
  int id3Save, id4Save;

};

}
