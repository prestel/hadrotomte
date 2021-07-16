
#include "Dire/DireProcesses.h"

namespace Pythia8 {

//--------------------------------------------------------------------------

void DireSigmaHelper::init(Info* infoPtrIn, Settings* settingsPtrIn,
  ParticleData* particleDataPtrIn, Rndm*,
  BeamParticle* beamAPtrIn, BeamParticle* beamBPtrIn,
  Couplings* couplingsPtrIn, SusyLesHouches*, DireWeightContainer* weightsPtrIn,
  DireHooks* hooksPtrIn) {

  infoPtr         = infoPtrIn;
  settingsPtr     = settingsPtrIn;
  particleDataPtr = particleDataPtrIn;
  beamAPtr        = beamAPtrIn;
  beamBPtr        = beamBPtrIn;
  couplingsPtr    = couplingsPtrIn;
  weightsPtr      = weightsPtrIn;
  hooksPtr        = hooksPtrIn;

  // Renormalization scale rescaling.
  renormMultFac = settingsPtrIn->parm("SigmaProcess:renormMultFac");
  // Factorization scale rescaling.
  factorMultFac = settingsPtrIn->parm("SigmaProcess:factorMultFac");
  usePDFalphas  = settingsPtrIn->flag("ShowerPDF:usePDFalphas");

  hasExternalHook = (hooksPtr != 0);
  canSetMUR       = hasExternalHook && hooksPtr->canSetRenScale();
  canSetMUF       = hasExternalHook && hooksPtr->canSetFacScale();
  canSetMUQ       = hasExternalHook && hooksPtr->canSetStartScale();

  isInit        = true;
}

//--------------------------------------------------------------------------

double DireSigmaHelper::muRsq( double x1, double x2, double sH, double tH,
  double uH, bool massless, double m1sq, double m2sq, double m3sq,
  double m4sq) {
  if (false) cout << x1*x2*sH*tH*uH*massless*m1sq*m2sq*m3sq*m4sq;
  double ret = (massless) ?  tH * uH / sH : (tH * uH - m3sq * m4sq) / sH;
  // Scale setting for dijet process different from default Pythia.
  ret = -1./ (1/sH + 1/tH + 1/uH) / 2;
  ret *= renormMultFac;

  if (canSetMUR) ret = hooksPtr->doGetRenScale(x1, x2, sH, tH, uH, massless,
    m1sq, m2sq, m3sq, m4sq);

  return ret;
}

//--------------------------------------------------------------------------

double DireSigmaHelper::muFsq( double x1, double x2, double sH, double tH,
  double uH, bool massless, double m1sq, double m2sq, double m3sq,
  double m4sq) {
  if (false) cout << x1*x2*sH*tH*uH*massless*m1sq*m2sq*m3sq*m4sq;
  double ret = (massless) ?  tH * uH / sH : (tH * uH - m3sq * m4sq) / sH;
  // Scale setting for dijet process different from default Pythia.
  ret = -1./ (1/sH + 1/tH + 1/uH) / 2; 
  ret *= factorMultFac;

  if (canSetMUF) ret = hooksPtr->doGetFacScale(x1, x2, sH, tH, uH, massless,
    m1sq, m2sq, m3sq, m4sq);

  return ret;
}

//--------------------------------------------------------------------------

double DireSigmaHelper::muQsq( double x1, double x2, double sH, double tH,
  double uH, bool massless, double m1sq, double m2sq, double m3sq,
  double m4sq) {
  if (false) cout << x1*x2*sH*tH*uH*massless*m1sq*m2sq*m3sq*m4sq;
  double ret = (massless) ?  tH * uH / sH : (tH * uH - m3sq * m4sq) / sH;
  // Scale setting for dijet process different from default Pythia.
  ret = -1./ (1/sH + 1/tH + 1/uH) / 2;

  if (canSetMUQ) ret = hooksPtr->doGetStartScale(x1, x2, sH, tH, uH, massless,
    m1sq, m2sq, m3sq, m4sq);

  return ret;
}

//==========================================================================
 
void DireSigma2gg2gg::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in, double runBW4in)
  {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2qqbar2qqbarNew::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2qqbar2gg::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2qq2qq::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2qg2qg::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2gg2qqbar::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2gg2QQbar::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigma2qqbar2QQbar::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = sigmaHelperPtr->muRsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  Q2FacSave = sigmaHelperPtr->muFsq( x1in, x2in, sH, tH, uH, masslessKin, 0., 0.,
    s3, s4);
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

//==========================================================================
 
void DireSigmaSigma2ff2fft_neutral_current::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  //bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  bool masslessKin = false;
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = -tH;
  Q2FacSave = -tH;
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

  double mAnow   = particleDataPtr->m0(beamAPtr->id());
  double mBnow   = particleDataPtr->m0(beamBPtr->id());
  double mH1  = 0.;
  double mH2  = 0.;
  double eCM  = infoPtr->eCM();
  double s    = eCM * eCM;
  if ( beamAPtr->isLepton() && beamBPtr->isHadron() ) {
    double eCM1 = 0.5 * ( s + pow2(mAnow) - pow2(mBnow) ) / eCM;
    double eCM2 = 0.5 * (x2Save * s - pow2(mH1))
               / ( eCM1 + sqrt( pow2(eCM1) - pow2(mH1) ) );
    x1new = 2.*eCM1 / sqrt(s);
    x2new = 2.*eCM2 / sqrt(s);
  } else if ( beamBPtr->isLepton() && beamAPtr->isHadron() ) {
    double eCM2 = 0.5 * ( s - pow2(mAnow) + pow2(mBnow) ) / eCM;
    double eCM1 = 0.5 * (x1Save * s - pow2(mH2))
               / ( eCM2 + sqrt( pow2(eCM2) - pow2(mH2) ) );
    x1new = 2.*eCM1 / sqrt(s);
    x2new = 2.*eCM2 / sqrt(s);
  }

}

// Initialize process.
void DireSigmaSigma2ff2fft_neutral_current::initProc() {

  // Store Z0 mass for propagator. Common coupling factor.
  gmZmode   = settingsPtr->mode("WeakZ0:gmZmode");
  mZ        = particleDataPtr->m0(23);
  mZS       = mZ*mZ;
  thetaWRat = 1. / (16. * couplingsPtr->sin2thetaW()
            * couplingsPtr->cos2thetaW());

}

// Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour.
void DireSigmaSigma2ff2fft_neutral_current::sigmaKin() {

  // Cross section part common for all incoming flavours.
  double sigma0 = (M_PI / sH2) * pow2(alpEM);
  double mNsq = pow2(particleDataPtr->m0(900012));
  // Couplings for current flavour combination.
  int id1Abs = abs(id1);
  double  e1 = couplingsPtr->ef(id1Abs);
  int id2Abs = abs(id2);
  double  v2 = couplingsPtr->vf(id2Abs); // vector coupling
  double  a2 = couplingsPtr->af(id2Abs); // axial coupling

  // Kinematical functions for gamma-gamma, gamma-Z and Z-Z parts.
  sigmagmgm = sigma0 * 2. * (sH2 + uH2) / tH2;
  sigmagmZ  = sigma0 * 4. * thetaWRat * sH2 / (tH * (tH - mZS));
  // mixing^2!
  sigmaZZ   = sigma0 * 8. * pow2(thetaWRat) / pow2(tH - mZS);
  sigmaZZ *= sH*(sH-mNsq)*pow2(v2-a2)/4.
           - 4.*pow2(e1)*pow2(couplingsPtr->sin2thetaW())*(sH+tH)*(mNsq-sH-tH);
  if (gmZmode == 1) {sigmagmZ = 0.; sigmaZZ = 0.;}
  if (gmZmode == 2) {sigmagmgm = 0.; sigmagmZ = 0.;}

  double sigma0X = 1./(8.*M_PI*sH2);
  double mZpS = particleDataPtr->m0(900032);
  double factor = (2.*(sH2 + sH*tH)+tH2 - mNsq*(2.*sH+tH));
  // multiply by   g^2 gX eps theta^2 Qq (4 Qq sw^2 - tau3q) / cw^2
  sigmaZZp  = sigma0X/4. * factor / (tH-mZS) / (tH-mZpS) ; 
  // multiply by    gX^2 eps^2 theta^2 Qq^2
  sigmaZpZp = sigma0X * factor / pow2(tH-mZpS) ;

  if (x1new > 1. || x1new < 0. || x2new > 1. || x2new < 0.)
    sigmagmgm = sigmagmZ = sigmaZZ = sigma0X = sigmaZZp = sigmaZpZp = 0.;

  if (1. - beamAPtr->m()/beamAPtr->e() - x1Save < 0.)
    sigmagmgm = sigmagmZ = sigmaZZ = sigma0X = sigmaZZp = sigmaZpZp = 0.;
  if (1. - beamBPtr->m()/beamBPtr->e() - x2Save < 0.)
    sigmagmgm = sigmagmZ = sigmaZZ = sigma0X = sigmaZZp = sigmaZpZp = 0.;
  
}

// Evaluate d(sigmaHat)/d(tHat), including incoming flavour dependence.
double DireSigmaSigma2ff2fft_neutral_current::sigmaHat() {

  sigmaKin();

  // Couplings for current flavour combination.
  int id1Abs = abs(id1);
  int id2Abs = abs(id2);
  double  v2 = couplingsPtr->vf(id2Abs); // vector coupling

  // redefined xsecs
  double numixsq = settingsPtr->parm("Dire:U1new:numixsq");
  double aX = settingsPtr->parm("Dire:U1new:alphaX");
  double gX = sqrt(4.*M_PI*aX);
  double KinMix = settingsPtr->parm("Dire:U1new:KinMix");
  // PM: the sign of v2 is the opposite from my convention!
  double factorinterference = 4.*M_PI*(couplingsPtr->alphaEM(0))
    /(couplingsPtr->cos2thetaW())/(couplingsPtr->sin2thetaW()) * gX * KinMix
    * (particleDataPtr->charge(id2Abs)) * (-v2);
  double factorZp = 4. * M_PI * aX * pow2(KinMix)
    * pow2(particleDataPtr->charge(id2Abs));

  double LambdaElastic = settingsPtr->parm("Dire:U1new:LambdaElastic");
  double pElastic = settingsPtr->parm("Dire:U1new:pElastic");
  double ElasticFormFactor = pow(LambdaElastic,2.0*pElastic)
    /(pow(-tH,pElastic)+pow(LambdaElastic,2.0*pElastic));
  double sigma = (1.0 - ElasticFormFactor) *
                 numixsq * (sigmaZZ
               + factorinterference * sigmaZZp
               + factorZp * sigmaZpZp);
  
  // Spin-state extra factor 2 per incoming neutrino.
  if (id1Abs == 12 || id1Abs == 14 || id1Abs == 16) sigma *= 2.;
  if (id2Abs == 12 || id2Abs == 14 || id2Abs == 16) sigma *= 2.;

  if (x1new > 1. || x1new < 0. || x2new > 1. || x2new < 0.)
    sigma = 0.;

  if (1. - beamAPtr->m()/beamAPtr->e() - x1Save < 0.)
    sigma = 0.;
  if (1. - beamBPtr->m()/beamBPtr->e() - x2Save < 0.)
    sigma = 0.;

  // Answer.
  return sigma;

}

// Select identity, colour and anticolour.
void DireSigmaSigma2ff2fft_neutral_current::setIdColAcol() {

  // Trivial flavours: out = in.
  id3 = id1;
  id4 = id2;
  // Change to heavy neutrino.
  if (particleDataPtr->isLepton(id1)) id3 = 900012;
  if (particleDataPtr->isLepton(id2)) id4 = 900012;

  setId( id1, id2, id3, id4);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9 && abs(id2) < 9 && id1*id2 > 0)
                         setColAcol( 1, 0, 2, 0, 1, 0, 2, 0);
  else if (abs(id1) < 9 && abs(id2) < 9)
                         setColAcol( 1, 0, 0, 2, 1, 0, 0, 2);
  else if (abs(id1) < 9) setColAcol( 1, 0, 0, 0, 1, 0, 0, 0);
  else if (abs(id2) < 9) setColAcol( 0, 0, 1, 0, 0, 0, 1, 0);
  else                   setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if ( (abs(id1) < 9 && id1 < 0) || (abs(id1) > 10 && id2 < 0) )
    swapColAcol();

}


//==========================================================================
 
void DireSigmaSigma2ff2fft_charged_current::store2Kin( double x1in, double x2in, double sHin,
  double tHin, double m3in, double m4in, double runBW3in,
  double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = -tH;
  Q2FacSave = -tH;
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

}

// Initialize process.
void DireSigmaSigma2ff2fft_charged_current::initProc() {

  // Store W+- mass for propagator. Common coupling factor.
  mW        = particleDataPtr->m0(24);
  mWS       = mW*mW;
  thetaWRat = 1. / (4. * couplingsPtr->sin2thetaW());

}

// Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour.
void DireSigmaSigma2ff2fft_charged_current::sigmaKin() {

  // Cross section part common for all incoming flavours.
  sigma0 = (M_PI / sH2) * pow2(alpEM * thetaWRat)
    * 4. * sH2 / pow2(tH - mWS);

}

// Evaluate d(sigmaHat)/d(tHat), including incoming flavour dependence.
double DireSigmaSigma2ff2fft_charged_current::sigmaHat() {

  // Some flavour combinations not possible.
  int id1Abs = abs(id1);
  int id2Abs = abs(id2);
  if ( (id1Abs%2 == id2Abs%2 && id1 * id2 > 0)
    || (id1Abs%2 != id2Abs%2 && id1 * id2 < 0) ) return 0.;

  // Basic cross section.
  double sigma = sigma0;
  if (id1 * id2 < 0) sigma *= uH2 / sH2;

  // CKM factors for final states.
  sigma *= couplingsPtr->V2CKMsum(id1Abs) *  couplingsPtr->V2CKMsum(id2Abs);

  // Spin-state extra factor 2 per incoming neutrino.
  if (id1Abs == 12 || id1Abs == 14 || id1Abs == 16) sigma *= 2.;
  if (id2Abs == 12 || id2Abs == 14 || id2Abs == 16) sigma *= 2.;

  // Answer.
  return sigma;

}

// Select identity, colour and anticolour.
void DireSigmaSigma2ff2fft_charged_current::setIdColAcol() {

  // Pick out-flavours by relative CKM weights.
  id3 = couplingsPtr->V2CKMpick(id1);
  id4 = couplingsPtr->V2CKMpick(id2);
  setId( id1, id2, id3, id4);

  // Colour flow topologies. Swap when antiquarks.
  if      (abs(id1) < 9 && abs(id2) < 9 && id1*id2 > 0)
                         setColAcol( 1, 0, 2, 0, 1, 0, 2, 0);
  else if (abs(id1) < 9 && abs(id2) < 9)
                         setColAcol( 1, 0, 0, 2, 1, 0, 0, 2);
  else if (abs(id1) < 9) setColAcol( 1, 0, 0, 0, 1, 0, 0, 0);
  else if (abs(id2) < 9) setColAcol( 0, 0, 1, 0, 0, 0, 1, 0);
  else                   setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if ( (abs(id1) < 9 && id1 < 0) || (abs(id1) > 10 && id2 < 0) )
    swapColAcol();

}

//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------

// // PM: ELASTIC CROSS SECTION

void DireSigmaSigma2ff2fft_neutral_current_elastic::store2Kin( double x1in, 
  double x2in, double sHin, double tHin, double m3in, double m4in,
  double runBW3in, double runBW4in) {

  // Store inputs.
  // Default ordering of particles 3 and 4.
  swapTU   = false;
  // Incoming parton momentum fractions.
  x1Save   = x1in;
  x2Save   = x2in;
  // Incoming masses and their squares.
  //bool masslessKin = (id3Mass() == 0) && (id4Mass() == 0);
  bool masslessKin = false;
  if (masslessKin) {
    m3     = 0.;
    m4     = 0.;
  } else {
    m3     = m3in;
    m4     = m4in;
  }
  mSave[3] = m3;
  mSave[4] = m4;
  s3       = m3 * m3;
  s4       = m4 * m4;
  // Standard Mandelstam variables and their squares.
  sH       = sHin;
  tH       = tHin;
  uH       = (masslessKin) ? -(sH + tH) : s3 + s4 - (sH + tH);
  mH       = sqrt(sH);
  sH2      = sH * sH;
  tH2      = tH * tH;
  uH2      = uH * uH;
  // The nominal Breit-Wigner factors with running width.
  runBW3   = runBW3in;
  runBW4   = runBW4in;
  // Calculate squared transverse momentum.
  pT2 = (masslessKin) ?  tH * uH / sH : (tH * uH - s3 * s4) / sH;

  // Get scales and alphaS
  Q2RenSave = -tH;
  Q2FacSave = -tH;
  alpS  = sigmaHelperPtr->alpS(Q2RenSave);

  // Evaluate alpha_EM.
  alpEM = couplingsPtr->alphaEM(Q2RenSave);

  double mAnow   = particleDataPtr->m0(beamAPtr->id());
  double mBnow   = particleDataPtr->m0(beamBPtr->id());
  double mH1  = 0.;
  double mH2  = 0.;
  double eCM  = infoPtr->eCM();
  double s    = eCM * eCM;
  if ( beamAPtr->isLepton() && beamBPtr->isHadron() ) {
    double eCM1 = 0.5 * ( s + pow2(mAnow) - pow2(mBnow) ) / eCM;
    double eCM2 = 0.5 * (x2Save * s - pow2(mH1))
               / ( eCM1 + sqrt( pow2(eCM1) - pow2(mH1) ) );
    x1new = 2.*eCM1 / sqrt(s);
    x2new = 2.*eCM2 / sqrt(s);
  } else if ( beamBPtr->isLepton() && beamAPtr->isHadron() ) {
    double eCM2 = 0.5 * ( s - pow2(mAnow) + pow2(mBnow) ) / eCM;
    double eCM1 = 0.5 * (x1Save * s - pow2(mH2))
               / ( eCM2 + sqrt( pow2(eCM2) - pow2(mH2) ) );
    x1new = 2.*eCM1 / sqrt(s);
    x2new = 2.*eCM2 / sqrt(s);
  }

}

// Initialize process.
void DireSigmaSigma2ff2fft_neutral_current_elastic::initProc() {

  // Store Z0 mass for propagator. Common coupling factor.
  gmZmode   = settingsPtr->mode("WeakZ0:gmZmode");
  mZ        = particleDataPtr->m0(23);
  mZS       = mZ*mZ;
  thetaWRat = 1. / (16. * couplingsPtr->sin2thetaW()
            * couplingsPtr->cos2thetaW());

}


// // Evaluate d(sigmaHat)/d(tHat), part independent of incoming flavour.
void DireSigmaSigma2ff2fft_neutral_current_elastic::sigmaKin() {

  // Cross section part common for all incoming flavours.
  double sigma0 = (M_PI / sH2) * pow2(alpEM);
  double mNsq = pow2(particleDataPtr->m0(900012));

  // Kinematical functions for gamma-gamma, gamma-Z and Z-Z parts.
  sigmagmgm = sigma0 * 2. * (sH2 + uH2) / tH2;
  sigmagmZ  = sigma0 * 4. * thetaWRat * sH2 / (tH * (tH - mZS));
  // PM: matches my mathematica

  double swsq=couplingsPtr->sin2thetaW();
  double cwsq=1-swsq;
  double mp = particleDataPtr->m0(2212); // proton mass
  double mpsq = mp*mp;		// proton mass squared
  // g^4 = (e/sw)^4 = 16*pi^2*alpEM^2/sw^4
  // !!!Mixing square will be introduced in next function!!!
  double coeff1 = M_PI*pow2(alpEM)/(64.*swsq*swsq*cwsq*cwsq)/pow2(sH-mpsq); // ok
  double coeff2 = alpEM/(16.*cwsq)/pow2(sH-mpsq); // multiply by gX*KinMix in next function
  double coeff3 = 1/(8.*M_PI)/pow2(sH-mpsq); // multiply by gX^2*KinMix^2 in next function
  sigmaZZ   = coeff1 * 2.*mZS*mZS*(sH+tH-mpsq)*(sH+tH-mpsq-mNsq)
    + 2.*mNsq*mpsq*mZS*(mNsq-tH) + mNsq*mpsq*tH*(tH-mNsq);
  sigmaZZ /= mZS*mZS*pow2(tH-mZS);
  if (gmZmode == 1) {sigmagmZ = 0.; sigmaZZ = 0.;}
  if (gmZmode == 2) {sigmagmgm = 0.; sigmagmZ = 0.;}

  double mZpS = particleDataPtr->m0(900032);
  sigmaZZp   = 2.*sH*sH + 2.*sH*tH + tH*tH - 4.*sH*mpsq - mNsq*(2.*sH+tH) + 2.*mpsq*mpsq;
  sigmaZZp  *= coeff2/((mZS-tH)*(tH-mZpS));
  sigmaZpZp  = 2.*sH*sH + 2.*sH*tH + tH*tH - 4.*sH*mpsq - mNsq*(2.*sH+tH) + 2.*mpsq*mpsq;
  sigmaZpZp *= coeff3/pow2(tH-mZpS);

  if (x1new > 1. || x1new < 0. || x2new > 1. || x2new < 0.)
    sigmagmgm = sigmagmZ = sigmaZZ = sigmaZZp = sigmaZpZp = 0.;

}
  
// Evaluate d(sigmaHat)/d(tHat), including incoming flavour dependence.
double DireSigmaSigma2ff2fft_neutral_current_elastic::sigmaHat() {

  sigmaKin();
  
  // Couplings for current flavour combination.
  int id1Abs = abs(id1);
  int id2Abs = abs(id2);

  // PM: redefined xsecs
  double numixsq = settingsPtr->parm("Dire:U1new:numixsq");
  double aX = settingsPtr->parm("Dire:U1new:alphaX");
  double gX = sqrt(4.*M_PI*aX);
  double KinMix = settingsPtr->parm("Dire:U1new:KinMix");
  double LambdaElastic = settingsPtr->parm("Dire:U1new:LambdaElastic");
  double pElastic = settingsPtr->parm("Dire:U1new:pElastic");
  double ElasticFormFactor = pow(LambdaElastic,2.*pElastic)
    /(pow(-tH,pElastic)+pow(LambdaElastic,2.*pElastic));
     
  double sigma = ElasticFormFactor *
    numixsq * (sigmaZZ + gX * KinMix * sigmaZZp + gX*gX * KinMix*KinMix * sigmaZpZp);
  
  // Spin-state extra factor 2 per incoming neutrino.
  if (id1Abs == 12 || id1Abs == 14 || id1Abs == 16) sigma *= 2.;
  if (id2Abs == 12 || id2Abs == 14 || id2Abs == 16) sigma *= 2.;

  if (x1new > 1. || x1new < 0. || x2new > 1. || x2new < 0.)
    sigma = 0.;

  // Answer.
  return sigma;

}

// Select identity, colour and anticolour.
void DireSigmaSigma2ff2fft_neutral_current_elastic::setIdColAcol() {

  // Trivial flavours: out = in.
  id3 = id1;
  id4 = id2;
  // Change to heavy neutrino.
  if (particleDataPtr->isLepton(id1)) id3 = 900012;
  if (particleDataPtr->isLepton(id2)) id4 = 900012;

  setId( id1, id2, id3, id4);

  // Colour flow topologies. Swap when antiquarks.
  if (abs(id1) < 9 && abs(id2) < 9 && id1*id2 > 0)
                         setColAcol( 1, 0, 2, 0, 1, 0, 2, 0);
  else if (abs(id1) < 9 && abs(id2) < 9)
                         setColAcol( 1, 0, 0, 2, 1, 0, 0, 2);
  else if (abs(id1) < 9) setColAcol( 1, 0, 0, 0, 1, 0, 0, 0);
  else if (abs(id2) < 9) setColAcol( 0, 0, 1, 0, 0, 0, 1, 0);
  else                   setColAcol( 0, 0, 0, 0, 0, 0, 0, 0);
  if ( (abs(id1) < 9 && id1 < 0) || (abs(id1) > 10 && id2 < 0) )
    swapColAcol();

}

}
