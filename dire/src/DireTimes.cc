// DireTimes.cc is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

// Function definitions (not found in the header) for the DireTimes class.

#include "Dire/DireTimes.h"
#include "Dire/DireSpace.h"
#include "Dire/History.h"

namespace Pythia8 {

//const string DireTimes::testname="Dire_fsr_qed_11->11&22";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_qed_11->22&11";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_11->11&22";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_11->22&11";
//const string DireTimes::testps="FF";

//const string DireTimes::testname="Dire_fsr_qed_11->11&22";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_qed_11->22&11";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_11->11&22";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_11->22&11";
//const string DireTimes::testps="FI";

//const string DireTimes::testname="Dire_fsr_qed_22->13&13a";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_qed_22->13&13b";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13a";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13b";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13aResA";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13bResA";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13aResB";
//const string DireTimes::testps="FF";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13bResB";
//const string DireTimes::testps="FF";

//const string DireTimes::testname="Dire_fsr_qed_22->13&13a";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_qed_22->13&13b";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13a";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13b";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13aResA";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13bResA";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13aResB";
//const string DireTimes::testps="FI";
//const string DireTimes::testname="Dire_fsr_u1new_22->13&13bResB";
//const string DireTimes::testps="FI";

const string DireTimes::testname="N/A";
const string DireTimes::testps="N/A";

//==========================================================================

// The DireTimesEnd class.

bool operator==(const DireTimesEnd& dip1, const DireTimesEnd& dip2) {
  return dip1.iRadiator == dip2.iRadiator
      && dip1.iRecoiler == dip2.iRecoiler
      && dip1.colType == dip2.colType
      && dip1.isrType == dip2.isrType
      && dip1.allowedEmissions == dip2.allowedEmissions;
}

//==========================================================================

// The DireTimes class.

//--------------------------------------------------------------------------

// Constants: could be changed here if desired, but normally should not.
// These are of technical nature, as described for each.

// Minimal allowed c and b quark masses, for flavour thresholds.
const double DireTimes::MCMIN        = 1.2;
const double DireTimes::MBMIN        = 4.0;

// For small x approximate 1 - sqrt(1 - x) by x/2.
const double DireTimes::SIMPLIFYROOT = 1e-8;

// Do not allow x too close to 0 or 1 in matrix element expressions.
// Warning: cuts into phase space for E_CM > 2 * pTmin * sqrt(1/XMARGIN),
// i.e. will become problem roughly for E_CM > 10^6 GeV.
const double DireTimes::XMARGIN      = 1e-12;
const double DireTimes::XMARGINCOMB  = 1e-4;

// Lower limit on PDF value in order to avoid division by zero.
const double DireTimes::TINYPDF      = 1e-5;

// Leftover companion can give PDF > 0 at small Q2 where other PDF's = 0,
// and then one can end in infinite loop of impossible kinematics.
const int    DireTimes::MAXLOOPTINYPDF = 10;

// Big starting value in search for smallest invariant-mass pair.
const double DireTimes::LARGEM2      = 1e20;

// In g -> q qbar or gamma -> f fbar require m2_pair > this * m2_q/f.
const double DireTimes::THRESHM2     = 4.004;

// Never pick pT so low that alphaS is evaluated too close to Lambda_3.
const double DireTimes::LAMBDA3MARGIN = 1.1;

// Value (in GeV) below which particles are considered massless
const double DireTimes::TINYMASS = 1e-3;

// Lower limit on estimated evolution rate, below which stop.
const double DireTimes::TINYOVERESTIMATE  = 1e-15;

// pT2 above which PDF is used in overestimates for FI splittings.
const double DireTimes::PT2MIN_PDF_IN_OVERESTIMATE = 5.;

// pT2 below which PDF overestimates for FI with gluon recoiler is included.
const double DireTimes::PT2_INCREASE_OVERESTIMATE = 2.;

const double DireTimes::KERNEL_HEADROOM = 10.;

// Maximal energy fraction of lepton in lepton -> lepton photon branching.
// Needed because massive phase space does not cut off zCS->1.
const double DireTimes::LEPTONXMIN     = 1e-5;
const double DireTimes::LEPTONXMAX     = 1. - 1e-5;
const double DireTimes::LEPTONZMAX     = 1. - 1e-4;

//--------------------------------------------------------------------------

// Initialize alphaStrong, alphaEM and related pTmin parameters.

void DireTimes::init( BeamParticle* beamAPtrIn,
  BeamParticle* beamBPtrIn) {

  // Header.
  printBanner = printBanner && !settingsPtr->flag("Print:quiet");
  if (printBanner) {
  cout << "\n"
       << " *-----------------  Welcome to DIRE version " << DIRE_TIMES_VERSION
       << "  ----------------*\n"
       << " |                                                "
       << "                  |\n"
       << " | Please consider citing Eur.Phys.J. C75 (2015)"
       << " 9, 461             |\n"
       << " | if you use this program for scientific purposes."
       << "                 |\n";
  cout << " |                                                "
       << "                  |\n";
  cout << " | You are using DIRE as timelike shower.         "
       << "                  |\n";
  cout << " |                                                "
       << "                  |\n"
       << " *-----------------  Dire times end.  ------------"
       << "------------------*" << endl;
  printBanner = false;}

  // Colour factors.
  CA = settingsPtr->parm("DireColorQCD:CA") > 0.0
     ? settingsPtr->parm("DireColorQCD:CA") : 3.0;
  CF = settingsPtr->parm("DireColorQCD:CF") > 0.0
     ? settingsPtr->parm("DireColorQCD:CF") : 4./3.;
  TR = settingsPtr->parm("DireColorQCD:TR") > 0.
     ? settingsPtr->parm("DireColorQCD:TR") : 0.5;
  NC = settingsPtr->parm("DireColorQCD:NC") > 0.
     ? settingsPtr->parm("DireColorQCD:NC") : 3.0;

  // Alternatively only initialize resonance decays.
  processLevel.initDecays( infoPtr, *settingsPtr,
    particleDataPtr, rndmPtr, NULL);

  // Store input pointers for future use.
  beamAPtr           = beamAPtrIn;
  beamBPtr           = beamBPtrIn;

  // Main flags.
  doQCDshower        = settingsPtr->flag("TimeShower:QCDshower");
  doQEDshowerByQ     = settingsPtr->flag("TimeShower:QEDshowerByQ");
  doQEDshowerByL     = settingsPtr->flag("TimeShower:QEDshowerByL");
  doDecaysAsShower   = settingsPtr->flag("DireTimes:DecaysAsShower");

  doMEcorrections    = settingsPtr->flag("Dire:doMECs")
                    || settingsPtr->flag("Dire:doMOPS");

  doMEafterFirst     = settingsPtr->flag("TimeShower:MEafterFirst");
  doPhiPolAsym       = settingsPtr->flag("TimeShower:phiPolAsym");
  doInterleave       = settingsPtr->flag("TimeShower:interleave");
  allowBeamRecoil    = settingsPtr->flag("TimeShower:allowBeamRecoil");
  dampenBeamRecoil   = settingsPtr->flag("TimeShower:dampenBeamRecoil");
  recoilToColoured   = settingsPtr->flag("TimeShower:recoilToColoured");

  // Matching in pT of hard interaction or MPI to shower evolution.
  pTmaxMatch         = settingsPtr->mode("TimeShower:pTmaxMatch");
  pTdampMatch        = settingsPtr->mode("TimeShower:pTdampMatch");
  pTmaxFudge         = settingsPtr->parm("TimeShower:pTmaxFudge");
  pTmaxFudgeMPI      = settingsPtr->parm("TimeShower:pTmaxFudgeMPI");
  pTdampFudge        = settingsPtr->parm("TimeShower:pTdampFudge");
  pT2minVariations   = pow2(max(0.,settingsPtr->parm("Variations:pTmin")));
  pT2minEnhance      = pow2(max(0.,settingsPtr->parm("Enhance:pTmin")));
  pT2minMECs         = pow2(max(0.,settingsPtr->parm("Dire:pTminMECs")));
  Q2minMECs          = pow2(max(0.,settingsPtr->parm("Dire:QminMECs")));
  nFinalMaxMECs      = settingsPtr->mode("Dire:nFinalMaxMECs");
  suppressLargeMECs  = settingsPtr->flag("Dire:suppressLargeMECs");
  allowMECsBelowCutoff = settingsPtr->flag("Dire:allowMECsBelowCutoff");
  pT2recombine       = pow2(max(0.,settingsPtr->parm("DireTimes:pTrecombine")));

  // Charm and bottom mass thresholds.
  mc                 = max( MCMIN, particleDataPtr->m0(4));
  mb                 = max( MBMIN, particleDataPtr->m0(5));
  m2c                = mc * mc;
  m2b                = mb * mb;

  // Parameters of scale choices (inherited from Pythia).
  renormMultFac     = settingsPtr->parm("TimeShower:renormMultFac");
  factorMultFac     = settingsPtr->parm("TimeShower:factorMultFac");
  useFixedFacScale  = settingsPtr->flag("TimeShower:useFixedFacScale");
  fixedFacScale2    = pow2(settingsPtr->parm("TimeShower:fixedFacScale"));

  // Parameters of alphaStrong generation.
  alphaSvalue        = settingsPtr->parm("TimeShower:alphaSvalue");
  alphaSorder        = settingsPtr->mode("TimeShower:alphaSorder");
  alphaSnfmax        = settingsPtr->mode("StandardModel:alphaSnfmax");
  alphaSuseCMW       = settingsPtr->flag("TimeShower:alphaSuseCMW");
  alphaS2pi          = 0.5 * alphaSvalue / M_PI;
  asScheme           = settingsPtr->mode("DireTimes:alphasScheme");

  // Set flavour thresholds by default Pythia masses, unless zero.
  double mcpy = particleDataPtr->m0(4);
  double mbpy = particleDataPtr->m0(5);
  double mtpy = particleDataPtr->m0(6);
  if (mcpy > 0.0 && mbpy > 0.0 && mtpy > 0.0)
    alphaS.setThresholds(mcpy, mbpy, mtpy);

  // Initialize alphaStrong generation.
  alphaS.init( alphaSvalue, alphaSorder, alphaSnfmax, alphaSuseCMW);

  //// Set flavour thresholds by default Pythia masses, unless zero.
  //double mcpy = particleDataPtr->m0(4);
  //double mbpy = particleDataPtr->m0(5);
  //double mtpy = particleDataPtr->m0(6);
  //if (mcpy > 0.0 && mbpy > 0.0 && mtpy > 0.0)
  //  alphaS.setThresholds(mcpy, mbpy, mtpy);

  // Lambda for 5, 4 and 3 flavours.
  Lambda3flav        = alphaS.Lambda3();
  Lambda4flav        = alphaS.Lambda4();
  Lambda5flav        = alphaS.Lambda5();
  Lambda5flav2       = pow2(Lambda5flav);
  Lambda4flav2       = pow2(Lambda4flav);
  Lambda3flav2       = pow2(Lambda3flav);

  // Parameters of QCD evolution. Warn if pTmin must be raised.
  nGluonToQuark      = settingsPtr->mode("TimeShower:nGluonToQuark");
  pTcolCutMin        = settingsPtr->parm("TimeShower:pTmin");
  if (pTcolCutMin > LAMBDA3MARGIN * Lambda3flav / sqrt(renormMultFac))
    pTcolCut         = pTcolCutMin;
  else {
    pTcolCut         = LAMBDA3MARGIN * Lambda3flav / sqrt(renormMultFac);
    ostringstream newPTcolCut;
    newPTcolCut << fixed << setprecision(3) << pTcolCut;
    infoPtr->errorMsg("Warning in DireTimes::init: pTmin too low",
                      ", raised to " + newPTcolCut.str() );
    infoPtr->setTooLowPTmin(true);
  }
  pT2colCut          = pow2(pTcolCut);
  m2colCut           = pT2colCut;
  mTolErr            = settingsPtr->parm("Check:mTolErr");

  double pT2minQED = pow2(settingsPtr->parm("DireTimes:QED:pTminChgQ"));
  pT2minQED = min(pT2minQED, pow2(settingsPtr->parm("DireSpace:QED:pTminChgL")));
  pT2cutSave = create_unordered_map<int,double>
    (21,pT2colCut)
    (1,pT2colCut)(-1,pT2colCut)(2,pT2colCut)(-2,pT2colCut)
    (3,pT2colCut)(-3,pT2colCut)(4,pT2colCut)(-4,pT2colCut)
    (5,pT2colCut)(-5,pT2colCut)(6,pT2colCut)(-6,pT2colCut)
    (22,pT2minQED)
    (11,pT2minQED)(-11,pT2minQED)(13,pT2minQED)(-13,pT2minQED)
    (15,pT2minQED)(-15,pT2minQED)
    (1023,pT2minQED)(5000001,pT2minQED)(9000001,pT2minQED)
    (900032,pT2minQED)(900012,pT2minQED)
    (900040,pT2minQED);

  // Parameters of Pythia QED evolution.
  pTchgQCut          = settingsPtr->parm("DireTimes:QED:pTminChgQ");
  pT2chgQCut         = pow2(pTchgQCut);
  pTchgLCut          = settingsPtr->parm("DireTimes:QED:pTminChgL");
  pT2chgLCut         = pow2(pTchgLCut);

  bool_settings = create_unordered_map<string,bool>("doQEDshowerByL",doQEDshowerByL)
    ("doQEDshowerByQ",doQEDshowerByQ);

  usePDFalphas       = settingsPtr->flag("ShowerPDF:usePDFalphas");
  useSummedPDF       = settingsPtr->flag("ShowerPDF:useSummedPDF");
  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id())) ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id())) ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }
  alphaS2piOverestimate = (usePDFalphas && beam != NULL)
                        ? beam->alphaS(pT2colCut) * 0.5/M_PI
                        : (alphaSorder > 0) ? alphaS.alphaS(pT2colCut)*0.5/M_PI
                                            :  0.5 * 0.5/M_PI;
  usePDFlepton       = settingsPtr->flag("PDF:lepton");
  isLHAPDF           = (toLower(settingsPtr->word("PDF:pSet")).find("lhapdf")
                          != string::npos);
  m2cPhys = (usePDFalphas) ? pow2(max(0.,beam->mQuarkPDF(4)))
          : alphaS.muThres2(4);
  m2bPhys = (usePDFalphas) ? pow2(max(0.,beam->mQuarkPDF(5)))
          : alphaS.muThres2(5);

  // Parameters of alphaEM generation.
  alphaEMorder       = settingsPtr->mode("TimeShower:alphaEMorder");

  // Initialize alphaEM generation.
  alphaEM.init( alphaEMorder, settingsPtr);

  // Parameters of QED evolution, sums of charges, as necessary to pick flavor.
  nGammaToQuark      = settingsPtr->mode("TimeShower:nGammaToQuark");
  nGammaToLepton     = settingsPtr->mode("TimeShower:nGammaToLepton");
  sumCharge2L        = max(0, min(3, nGammaToLepton));
  sumCharge2Q        = 0.;
  if      (nGammaToQuark > 4) sumCharge2Q = 11. / 9.;
  else if (nGammaToQuark > 3) sumCharge2Q = 10. / 9.;
  else if (nGammaToQuark > 2) sumCharge2Q =  6. / 9.;
  else if (nGammaToQuark > 1) sumCharge2Q =  5. / 9.;
  else if (nGammaToQuark > 0) sumCharge2Q =  1. / 9.;
  sumCharge2Tot      = sumCharge2L + 3. * sumCharge2Q;

  // Allow massive incoming particles. Currently not supported by Pythia.
  useMassiveBeams    = settingsPtr->flag("Beams:massiveLeptonBeams");

  // Z0 and W+- properties needed for gamma/Z0 mixing and weak showers.
  mZ                 = particleDataPtr->m0(23);
  gammaZ             = particleDataPtr->mWidth(23);
  thetaW             = 1. / (16. * coupSMPtr->sin2thetaW()
                       * coupSMPtr->cos2thetaW());
  mW                 = particleDataPtr->m0(24);
  gammaW             = particleDataPtr->mWidth(24);

  nFinalMax          = settingsPtr->mode("DireTimes:nFinalMax");
  usePDFmasses       = settingsPtr->flag("ShowerPDF:usePDFmasses");

  // Mode for higher-order kernels.
  kernelOrder        = settingsPtr->mode("DireTimes:kernelOrder");
  kernelOrderMPI     = settingsPtr->mode("DireTimes:kernelOrderMPI");

  // Create maps of accept/reject weights
  string key = "base";
  rejectProbability.insert( make_pair(key, multimap<double,double>() ));
  acceptProbability.insert( make_pair(key, map<double,double>() ));
  doVariations = settingsPtr->flag("Variations:doVariations");
  nSysVar      = settingsPtr->mode("Variations:nSystemsToVary");
  splittingSelName.clear();
  splittingNowName.clear();

  // Number of MPI, in case MPI forces intervention in shower weights.
  nMPI = 0;

  // Set splitting library, if already exists.
  initSplits();

  // May have to fix up recoils related to rescattering.
  allowRescatter     = settingsPtr->flag("PartonLevel:MPI")
    && settingsPtr->flag("MultipartonInteractions:allowRescatter");

  // Possibility of two predetermined hard emissions in event.
  doSecondHard    = settingsPtr->flag("SecondHard:generate");

  // Possibility to allow user veto of emission step.
  hasUserHooks       = (userHooksPtr != 0);
  canVetoEmission    = (userHooksPtr != 0)
                     ? userHooksPtr->canVetoFSREmission() : false;

  // Set initial value, just in case.
  dopTdamp           = false;
  pT2damp            = 0.;

  // Default value for TimeShower-internal settings to avoid illdefined
  // behavior.
  //hasWeaklyRadiated = false;

  // Done.
  isInitSave = true;

}

//--------------------------------------------------------------------------

// Initialize bookkeeping of shower variations.

void DireTimes::initVariations() {

  // Create maps of accept/reject weights
  for ( int i=0; i < weights->sizeWeights(); ++i) {
    string key = weights->weightName(i);
    if ( key.compare("base") == 0) continue;
    if ( key.find("isr") != string::npos) continue;
    rejectProbability.insert( make_pair(key, multimap<double,double>() ));
    acceptProbability.insert( make_pair(key, map<double,double>() ));
  }

  for ( unordered_map<string, multimap<double,double> >::iterator
    it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
    it->second.clear();
  for ( unordered_map<string, map<double,double> >::iterator
    it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
    it->second.clear();

  // Done.
}

//--------------------------------------------------------------------------

// Find whether to limit maximum scale of emissions.
// Also allow for dampening at factorization or renormalization scale.

//bool DireTimes::limitPTmax( Event& event, double Q2Fac, double) {
bool DireTimes::limitPTmax( Event& event, double, double) {

  //direInfoPtr->message(1) << scientific << setprecision(8)
  //  << __FILE__ << ":" << __func__ 
  //  << endl;

  // Find whether to limit pT. Begin by user-set cases.
  bool dopTlimit = false;
  dopTlimit1 = dopTlimit2 = false;
  int nHeavyCol = 0;
  if      (pTmaxMatch == 1) dopTlimit = dopTlimit1 = dopTlimit2 = true;
  else if (pTmaxMatch == 2) dopTlimit = dopTlimit1 = dopTlimit2 = false;

  // Always restrict SoftQCD processes.
  else if (infoPtr->isNonDiffractive() || infoPtr->isDiffractiveA()
    || infoPtr->isDiffractiveB() || infoPtr->isDiffractiveC() )
    dopTlimit = dopTlimit1 = dopTlimit2 = true;

  // Look if any quark (u, d, s, c, b), gluon or photon in final state.
  // Also count number of heavy coloured particles, like top. 
  else {
    int n21 = 0;
    for (int i = 5; i < event.size(); ++i) {
      if (event[i].status() == -21) ++n21;
      else if (n21 == 0) {
        int idAbs = event[i].idAbs();
        if (idAbs <= 5 || idAbs == 21 || idAbs == 22) dopTlimit1 = true;
        if ( (event[i].col() != 0 || event[i].acol() != 0)
          && idAbs > 5 && idAbs != 21 ) ++nHeavyCol;        
      } else if (n21 == 2) {
        int idAbs = event[i].idAbs();
        if (idAbs <= 5 || idAbs == 21 || idAbs == 22) dopTlimit2 = true;
      }
    }
    dopTlimit = (doSecondHard) ? (dopTlimit1 && dopTlimit2) : dopTlimit1;
  }

  // Dampening at factorization or renormalization scale; only for hardest.
  dopTdamp   = false;
  pT2damp    = 0.;

  /*// Now reset the event scale to the desired PS starting scale.
  // This is only necessary for the processes 2 -> N non-QCD,
  // 2 -> 2 (massless), 2 -> 2 (heavy). Scales for processes with additional
  // final partons will be set through merging.
  int npIn, npOut, naIn, naOut, nlIn, nlOut, nhOut, nbOut, nInOther, nOutOther;
  npIn = npOut = naIn = naOut = nlIn = nlOut = nhOut = nbOut = nInOther
       = nOutOther= 0;
  for (int i = 0; i < event.size(); ++i) {
    if (event[i].status() == -21 ) {
      if      ( event[i].colType() != 0 )   ++npIn;
      else if ( event[i].isLepton() )       ++nlIn;
      else if ( event[i].id() == 22 )       ++naIn;
      else                                  ++nInOther;
    } else if ( event[i].status() == 22 || event[i].status() == 23) {
      if      ( event[i].colType() != 0 && event[i].idAbs() != 6)  ++npOut;
      else if ( event[i].idAbs() == 6)                             ++nhOut;
      else if ( event[i].isLepton() )                              ++nlOut;
      else if ( event[i].id() == 22 )                              ++naOut;
      else if ( event[i].idAbs() > 22 && event[i].idAbs() < 26)    ++nbOut;
      else                                                         ++nOutOther;
    }
  }
  bool nonQCD       = (npIn==2) && (npOut==0) && (nhOut==0);
  bool massless2to2 = (npIn+naIn==2) && (npOut+naOut==2)
                   && (nhOut+nlOut+nbOut+nOutOther==0);
  bool heavy2to2    = (npIn+naIn==2) && (npOut+nhOut==2)
                   && (naOut+nlOut+nbOut+nOutOther==0);
  bool dis2to2      = (npIn==1) && (nlIn==1) && (npOut==1) && (nlOut==1)
                   && (nhOut+naOut+nbOut+nOutOther==0);

  if (nonQCD || massless2to2 || heavy2to2 || dis2to2) {
    dopTlimit = true;
    double pTstart = 0.0;
    map<string,double> stateVars = getStateVariables(event,0,0,0,"");
    for ( map<string,double>::iterator it = stateVars.begin();
      it != stateVars.end(); ++it )
      if ( it->first.find("scalePDF") != string::npos )
        pTstart = max( pTstart, sqrt(it->second) );
    if (pTstart == 0.0) pTstart = infoPtr->QFac();

    // Reset the event scale.
    event.scale(pTstart);

    // Reset the production scale of incoming particles, to ensure that correct
    // scale is used.
    for (int i = 0; i < event.size(); ++i)
      if (event[i].isFinal() && event[i].colType() != 0)
        event[i].scale(pTstart);
  }*/

  // Done.
  return dopTlimit;

}

//--------------------------------------------------------------------------

void DireTimes::finalize( Event& event) {

  direInfoPtr->usePTLast(false);
  direInfoPtr->pTLast(-1.);
  direInfoPtr->pTLastMin(-1.);

  //direInfoPtr->message(1) << "End event evolution" << endl << endl;
  //direInfoPtr->printMessages(1);

  return;

  // Perform resonance decays if some shower-produced resonances are
  // still left-over after evolution terminates.
  int resSize = direInfoPtr->sizeResPos();
  for ( int i=0; i < resSize; ++i){
    int iRes = direInfoPtr->getResPos(i);
    int sizeOld = event.size();
    // Construct the decay products.
    Event decays;
    decays.init("(decays)", particleDataPtr);
    //decays.clear();
    decays.initColTag(event.lastColTag()+1000);
    int iMother = event[iRes].mother1();
    decays.append(event[iMother]);
    decays.append(event[iRes]);
    decays[decays.size()-1].mother1(0);
    processLevel.nextDecays(decays);
    if (decays.size() < 3) {
      // Force decay!
      Vec4 pRadBef = event[iRes].p();
      double m2Bef = event[iRes].p().m2Calc();
      Vec4 pRecBef(0.,0.,sqrt(m2Bef),sqrt(m2Bef));
      double m2s   = pRecBef.m2Calc();

      int NTRYCHANNEL=10;
      for (int iTryChannel = 0; iTryChannel < NTRYCHANNEL; ++iTryChannel) {
        // Pick decay channel. Find multiplicity.
        DecayChannel& channel = event[iRes].particleDataEntry().pickChannel();
        int mult = channel.multiplicity();
        // Read out flavours.
        int id0 = event[iRes].id();
        vector<int> ids;
        for (int ii = 1; ii <= mult; ++ii) {
          int idNow = channel.product(ii - 1);
          if (id0 < 0 && particleDataPtr->hasAnti(idNow)) idNow = -idNow;
          ids.push_back( idNow);
        }
        if (ids.size()!=2) continue;

        // Calculate derived variables.
        double m2r = pow2(particleDataPtr->m0(ids[0]));
        double m2e = pow2(particleDataPtr->m0(ids[1]));
        double q2  = (pRadBef+pRecBef).m2Calc();
        double yCS = (m2Bef - m2e - m2r)
                   / (m2Bef - m2e - m2r + 2.*pRadBef*pRecBef);
        double zCS = 0.;
        double kT2 =-1.;
        int nTries=0;
        int nMaxTries=10000;
        while (nTries>nMaxTries || kT2<0.){
          nTries++;
          zCS = rndmPtr->flat();
          double sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2r+m2e);
          double zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
                     * (zCS - m2s/gABC(q2,sij,m2s)
                             *(sij + m2r - m2e)/(q2-sij-m2s));
          kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2r - zbar*m2e; 
        }
        if (nTries>=nMaxTries) continue;

        // Construct kinematics of 1->2 decay.
        double phi_kt = 2.*M_PI*rndmPtr->flat();
        pair < Vec4, Vec4 > momsAfter = decayWithOnshellRec( zCS, yCS,
          phi_kt, m2s, m2r, m2e, pRadBef, pRecBef );
        Vec4 pRad(momsAfter.first);
        Vec4 pEmt(momsAfter.second);
        decays.append(Particle(ids[0],51,iRes,0,0,0,0,0,pRad,sqrt(m2r),0.));
        decays.append(Particle(ids[1],51,iRes,0,0,0,0,0,pEmt,sqrt(m2e),0.));
        break;
      }

      // If none of the decays were successful, give up.
      if (decays.size() < 3) {
        infoPtr->errorMsg("Error in DireTimes::finalize: "
          "Failed to decay shower-induced resonance");
         continue;
       }
    }
    // Attach decay products to event.
    int iDauMin = sizeOld;
    int iDauMax = sizeOld + decays.size()-3;
    event[direInfoPtr->getResPos(i)].statusNeg();
    event[direInfoPtr->getResPos(i)].daughters(iDauMin,iDauMax);
    //int iBeg = event.size()-1;
    int iBeg = sizeOld;
    int iEnd = iBeg;
    for (int iDecay = 2; iDecay < decays.size(); ++iDecay) {
      if (!decays[iDecay].isFinal()) continue;
      event.append(decays[iDecay]);
      event[event.size()-1].mothers(direInfoPtr->getResPos(i),0);
      iEnd++;
    }

    /*// Complicated scenario: Put decays into new system, shower that
    // system, then reinsert into production system.
    int oldSysSize = partonSystemsPtr->sizeSys();
    // Add new system, automatically with two empty beam slots.
    int iSys = partonSystemsPtr->addSys();
    partonSystemsPtr->setInRes( iSys, iRes);
    // Loop over allowed range to find all final-state particles.
    Vec4 pSum;
    //for (int ii = iBeg; ii <= iEnd; ++ii) if (event[ii].isFinal()) {
    for (int ii = iBeg; ii < iEnd; ++ii) if (event[ii].isFinal()) {
      partonSystemsPtr->addOut( iSys, ii);
      pSum += event[ii].p();
    }
    partonSystemsPtr->setSHat( iSys, pSum.m2Calc());
    partonSystemsPtr->setPTHat( iSys, pSum.mCalc());

    // Now we could again shower the decay system.

    // Finally, reassign new decay products to production system,
    // else beam remnant will incorrectly treat systems w/o incoming partons.
    int iSysRes = partonSystemsPtr->getSystemOf(iRes,true);
    for (int iOut = 0; iOut < partonSystemsPtr->sizeOut(iSys); ++iOut)
      partonSystemsPtr->addOut(iSysRes, partonSystemsPtr->getOut(iSys, iOut));
    partonSystemsPtr->setSizeSys(oldSysSize);*/

    // Easy scenario: Put decays into production system.
    int iSysRes = partonSystemsPtr->getSystemOf(iRes,true);
    partonSystemsPtr->replace(iSysRes, iRes, iBeg);
    //for (int ii = iBeg; ii <= iEnd; ++ii)
    for (int ii = iBeg+1; ii < iEnd; ++ii)
      if (ii < event.size() && event[ii].isFinal())
        partonSystemsPtr->addOut( iSysRes, ii);

  }
  // Clear resonances (even if not decayed)
  direInfoPtr->clearResPos();

  // Currently, do nothing to not break other things.
  return;

}


//--------------------------------------------------------------------------

// Top-level routine to do a full time-like shower in resonance decay.

int DireTimes::shower( int iBeg, int iEnd, Event& event, double pTmax,
  int nBranchMax) {

  // Add new system, automatically with two empty beam slots.
  int iSys = partonSystemsPtr->addSys();

  // Loop over allowed range to find all final-state particles.
  Vec4 pSum;
  for (int i = iBeg; i <= iEnd; ++i) if (event[i].isFinal()) {
    partonSystemsPtr->addOut( iSys, i);
    pSum += event[i].p();
  }
  partonSystemsPtr->setSHat( iSys, pSum.m2Calc() );

  // Let prepare routine do the setup.
  dopTlimit1        = true;
  dopTlimit2        = true;
  dopTdamp          = false;
  prepare( iSys, event, true);

  // Begin evolution down in pT from hard pT scale.
  int nBranch  = 0;
  pTLastBranch = 0.;
  do {
    double pTtimes = pTnext( event, pTmax, 0.);

    // Do a final-state emission (if allowed).
    if (pTtimes > 0.) {
      if (branch( event)) {
        ++nBranch;
        pTLastBranch = pTtimes;
      }
      pTmax = pTtimes;
    }

    // Keep on evolving until nothing is left to be done.
    else pTmax = 0.;
  } while (pTmax > 0. && (nBranchMax <= 0 || nBranch < nBranchMax));

  // Return number of emissions that were performed.
  return nBranch;

}

//--------------------------------------------------------------------------

// Top-level routine for QED radiation in hadronic decay to two leptons.
// Intentionally only does photon radiation, i.e. no photon branchings.

int DireTimes::showerQED( int i1, int i2, Event& event, double pTmax) {

  // Add new system, automatically with two empty beam slots.
  int iSys = partonSystemsPtr->addSys();
  partonSystemsPtr->addOut( iSys, i1);
  partonSystemsPtr->addOut( iSys, i2);
  partonSystemsPtr->setSHat( iSys, m2(event[i1], event[i2]) );

  // Reset scales to allow setting up dipoles.
  double scale1 = event[i1].scale();
  event[i1].scale(pTmax);
  double scale2 = event[i2].scale();
  event[i2].scale(pTmax);

  // Prepare all dipoles for evolution.
  dopTlimit1        = true;
  dopTlimit2        = true;
  dopTdamp          = false;
  prepare( iSys, event, false);

  // Begin evolution down in pT from hard pT scale.
  int nBranch  = 0;
  pTLastBranch = 0.;
  do {

    double pTsel = pTnext( event, pTmax, 0., false, false);

    // Do a final-state emission (if allowed).
    if (pTsel > 0.) {
      if (branch(event)) {
        // Done with branching
        ++nBranch;
        pTLastBranch = pTsel;
       }
       pTmax = pTsel;
    // Keep on evolving until nothing is left to be done.
    } else pTmax = 0.;
  } while (pTmax > 0.);

  // Undo scale setting.
  event[i1].scale(scale1);
  event[i2].scale(scale2);

  // Return number of emissions that were performed.
  return nBranch;

}

//--------------------------------------------------------------------------

// Global recoil not used, but abuse function to reset some generic things.

void DireTimes::prepareGlobal( Event& ) {

  //direInfoPtr->message(1) << scientific << setprecision(8)
  //  << __FILE__ << ":" << __func__ 
  //  << endl;

  // Initialize weight container.
  weights->init();

  // Clear event-by-event diagnostic messages.
  direInfoPtr->clearAll();

  // Clear accept/reject weights.
  weights->reset();
  for ( unordered_map<string, multimap<double,double> >::iterator
    it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
    it->second.clear();
  for ( unordered_map<string, map<double,double> >::iterator
    it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
    it->second.clear();

  // Now also attempt to reset ISR weights!
  unordered_map<string,DireSplitting*> tmpSplits = splittingsPtr->getSplittings();
  for ( unordered_map<string,DireSplitting*>::iterator it = tmpSplits.begin();
    it != tmpSplits.end(); ++it ) {
    if (it->second->isr) { it->second->isr->resetWeights(); break; }
  }

  return;
}

//--------------------------------------------------------------------------

// Prepare system for evolution; identify ME.

void DireTimes::prepare( int iSys, Event& event, bool limitPTmaxIn) {

  //direInfoPtr->message(1) << scientific << setprecision(8)
  //  << __FILE__ << ":" << __func__ 
  //  << endl;

  if (iSys>0 && !partonSystemsPtr->hasInAB(iSys)) {
    weights->calcWeight(pow2(infoPtr->pTnow()));
    weights->reset();
    // Clear accept/reject weights.
    for ( unordered_map<string, multimap<double,double> >::iterator
      it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
      it->second.clear();
    for ( unordered_map<string, map<double,double> >::iterator
      it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
      it->second.clear();
  }

  // Calculate remainder shower weight after MPI.
  if (nMPI < infoPtr->getCounter(23) && iSys == infoPtr->getCounter(23) ) {
    weights->calcWeight(pow2(infoPtr->pTnow()));
    weights->reset();
    // Clear accept/reject weights.
    for ( unordered_map<string, multimap<double,double> >::iterator
      it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
      it->second.clear();
    for ( unordered_map<string, map<double,double> >::iterator
      it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
      it->second.clear();
  }
  // Store number of MPI, in case a subsequent MPI forces calculation and
  // reset of shower weights.
  nMPI = infoPtr->getCounter(23);

  // Reset dipole-ends list for first interaction and for resonance decays.
  int iInA = partonSystemsPtr->getInA(iSys);
  int iInB = partonSystemsPtr->getInB(iSys);
  if (iSys == 0 || iInA == 0) dipEnd.resize(0);
  int dipEndSizeBeg = dipEnd.size();

  // Clear evolution windows.
  evolutionWindows.clear();
  iWindowSel = iWindowNow = -1;

  // Set splitting library.
  initSplits();

  // No dipoles for 2 -> 1 processes.
  if (partonSystemsPtr->sizeOut(iSys) < 2) {
    // Loop through final state of system to find possible decays.
    for (int i = 0; i < partonSystemsPtr->sizeOut(iSys); ++i) {
      int iRad = partonSystemsPtr->getOut( iSys, i);
      if ( event[iRad].isFinal()
        && event[iRad].scale() > 0.
        && event[iRad].isResonance())
        // Setup decay dipoles.
        if (doDecaysAsShower) setupDecayDip( iSys, iRad, event, dipEnd);
    }
    return;
  }

  // In case of DPS overwrite limitPTmaxIn by saved value.
  if (doSecondHard && iSys == 0) limitPTmaxIn = dopTlimit1;
  if (doSecondHard && iSys == 1) limitPTmaxIn = dopTlimit2;

  dipSel = 0;

  // Loop through final state of system to find possible dipole ends.
  for (int i = 0; i < partonSystemsPtr->sizeOut(iSys); ++i) {
    int iRad = partonSystemsPtr->getOut( iSys, i);

    if (event[iRad].isFinal() && event[iRad].scale() > 0.) {

      // Find dipole end formed by colour index.
      int colTag = event[iRad].col();
      if (doQCDshower && colTag > 0) setupQCDdip( iSys, i,  colTag,  1, event,
        false, limitPTmaxIn);

      // Find dipole end formed by anticolour index.
      int acolTag = event[iRad].acol();
      if (doQCDshower && acolTag > 0) setupQCDdip( iSys, i, acolTag, -1, event,
        false, limitPTmaxIn);

      // Now find non-QCD dipoles and/or update the existing dipoles.
      getGenDip( iSys, i, iRad, event, limitPTmaxIn, dipEnd);

    // End loop over system final state. Have now found the dipole ends.
    }

    // Setup decay dipoles.
    if (doDecaysAsShower && event[iRad].isResonance())
      setupDecayDip( iSys, iRad, event, dipEnd);

  }

  // Loop through dipole ends and set matrix element correction flag.
  for (int iDip = dipEndSizeBeg; iDip < int(dipEnd.size()); ++iDip)
    dipEnd[iDip].MEtype = 0;

  // Now update masses and allowed emissions. (Not necessary here, since
  // ensured in setupQCDdip etc.)
  updateDipoles(event, iSys);

  bornColors.resize(0);
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    int colRad  = event[dipEnd[iDip].iRadiator].col();
    int acolRad = event[dipEnd[iDip].iRadiator].acol();
    if ( dipEnd[iDip].colType > 0
     && find(bornColors.begin(), bornColors.end(), colRad) == bornColors.end())
     bornColors.push_back(colRad);
    if ( dipEnd[iDip].colType < 0
      && find(bornColors.begin(), bornColors.end(), acolRad) == bornColors.end())
      bornColors.push_back(acolRad);
  }

  // Update dipole list after a multiparton interactions rescattering.
  if (iSys > 0 && ( (iInA > 0 && event[iInA].status() == -34)
    || (iInB > 0 && event[iInB].status() == -34) ) )
    rescatterUpdate( iSys, event);

  // Counter of proposed emissions.
  nProposedPT.clear();
  if ( nProposedPT.find(iSys) == nProposedPT.end() )
    nProposedPT.insert(make_pair(iSys,0));

  splittingSelName.clear();
  splittingNowName.clear();

  // Clear weighted shower book-keeping.
  for ( unordered_map<string, multimap<double,double> >::iterator
    it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
    it->second.clear();
  for ( unordered_map<string, map<double,double> >::iterator
    it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
    it->second.clear();

}

//--------------------------------------------------------------------------

void DireTimes::clear() {

  dipEnd.resize(0);
  weights->reset();
  dipSel = 0;

  splittingSelName.clear();
  splittingNowName.clear();

  // Clear weighted shower book-keeping.
  for ( unordered_map<string, multimap<double,double> >::iterator
    it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
    it->second.clear();
  for ( unordered_map<string, map<double,double> >::iterator
    it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
    it->second.clear();

}

//--------------------------------------------------------------------------

// Update dipole list after a multiparton interactions rescattering.

void DireTimes::rescatterUpdate( int iSys, Event& event) {

  // Loop over two incoming partons in system; find their rescattering mother.
  // (iOut is outgoing from old system = incoming iIn of rescattering system.)
  for (int iResc = 0; iResc < 2; ++iResc) {
    int iIn = (iResc == 0) ? partonSystemsPtr->getInA(iSys)
                           : partonSystemsPtr->getInB(iSys);
    if (iIn == 0 || event[iIn].status() != -34) continue;
    int iOut = event[iIn].mother1();

    // Loop over all dipoles.
    int dipEndSize = dipEnd.size();
    for (int iDip = 0; iDip < dipEndSize; ++iDip) {
      DireTimesEnd& dipNow = dipEnd[iDip];

      // Kill dipoles where rescattered parton is radiator.
      if (dipNow.iRadiator == iOut) {
        dipNow.colType = 0;
        dipNow.chgType = 0;
        dipNow.gamType = 0;
        continue;
      }
      // No matrix element for dipoles between scatterings.
      if (dipNow.iMEpartner == iOut) {
        dipNow.MEtype     =  0;
        dipNow.iMEpartner = -1;
      }

      // Update dipoles where outgoing rescattered parton is recoiler.
      if (dipNow.iRecoiler == iOut) {
        int iRad = dipNow.iRadiator;

        // Colour dipole: recoil in final state, initial state or new.
        if (dipNow.colType > 0) {
          int colTag = event[iRad].col();
          bool done  = false;
          for (int i = 0; i < partonSystemsPtr->sizeOut(iSys); ++i) {
            int iRecNow = partonSystemsPtr->getOut( iSys, i);
            if (event[iRecNow].acol() == colTag) {
              dipNow.iRecoiler = iRecNow;
              dipNow.systemRec = iSys;
              dipNow.MEtype    = 0;
              done             = true;
              break;
            }
          }
          if (!done) {
            int iIn2 = (iResc == 0) ? partonSystemsPtr->getInB(iSys)
                                    : partonSystemsPtr->getInA(iSys);
            if (event[iIn2].col() == colTag) {
              dipNow.iRecoiler = iIn2;
              dipNow.systemRec = iSys;
              dipNow.MEtype    = 0;
              int isrType      = event[iIn2].mother1();
              // This line in case mother is a rescattered parton.
              while (isrType > 2 + beamOffset)
                isrType = event[isrType].mother1();
              if (isrType > 2) isrType -= beamOffset;
              dipNow.isrType   = isrType;
              done             = true;
            }
          }
          // If above options failed, then create new dipole.
          if (!done) {
            int iRadNow = partonSystemsPtr->getIndexOfOut(dipNow.system, iRad);
            if (iRadNow != -1)
              setupQCDdip(dipNow.system, iRadNow, event[iRad].col(), 1,
                          event, dipNow.isOctetOnium, true);
            else
              infoPtr->errorMsg("Warning in DireTimes::rescatterUpdate: "
              "failed to locate radiator in system");

            dipNow.colType = 0;
            dipNow.chgType = 0;
            dipNow.gamType = 0;

            infoPtr->errorMsg("Warning in DireTimes::rescatterUpdate: "
            "failed to locate new recoiling colour partner");
          }

        // Anticolour dipole: recoil in final state, initial state or new.
        } else if (dipNow.colType < 0) {
          int  acolTag = event[iRad].acol();
          bool done    = false;
          for (int i = 0; i < partonSystemsPtr->sizeOut(iSys); ++i) {
            int iRecNow = partonSystemsPtr->getOut( iSys, i);
            if (event[iRecNow].col() == acolTag) {
              dipNow.iRecoiler = iRecNow;
              dipNow.systemRec = iSys;
              dipNow.MEtype    = 0;
              done             = true;
              break;
            }
          }
          if (!done) {
            int iIn2 = (iResc == 0) ? partonSystemsPtr->getInB(iSys)
                                    : partonSystemsPtr->getInA(iSys);
            if (event[iIn2].acol() == acolTag) {
              dipNow.iRecoiler = iIn2;
              dipNow.systemRec = iSys;
              dipNow.MEtype    = 0;
              int isrType      = event[iIn2].mother1();
              // This line in case mother is a rescattered parton.
              while (isrType > 2 + beamOffset)
                isrType = event[isrType].mother1();
              if (isrType > 2) isrType -= beamOffset;
              dipNow.isrType   = isrType;
              done             = true;
            }
          }
          // If above options failed, then create new dipole.
          if (!done) {
            int iRadNow = partonSystemsPtr->getIndexOfOut(dipNow.system, iRad);
            if (iRadNow != -1)
              setupQCDdip(dipNow.system, iRadNow, event[iRad].acol(), -1,
                          event, dipNow.isOctetOnium, true);
            else
              infoPtr->errorMsg("Warning in DireTimes::rescatterUpdate: "
              "failed to locate radiator in system");

            dipNow.colType = 0;
            dipNow.chgType = 0;
            dipNow.gamType = 0;

            infoPtr->errorMsg("Warning in DireTimes::rescatterUpdate: "
            "failed to locate new recoiling colour partner");
          }
        }
      }

    // End of loop over dipoles and two incoming sides.
    }
  }

}

//--------------------------------------------------------------------------

// Update dipole list after each ISR emission (so not used for resonances).

void DireTimes::update( int iSys, Event& event, bool) {

  // Store dipoles in other systems.
  vector <DireTimesEnd> dipLT;
  vector <DireTimesEnd> dipGT;
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    if (dipEnd[iDip].system < iSys) dipLT.push_back(dipEnd[iDip]);
    if (dipEnd[iDip].system > iSys) dipGT.push_back(dipEnd[iDip]);
  }

  // Reset dipole-ends.
  dipEnd.resize(0);
  dipSel = 0;

  // No dipoles for 2 -> 1 processes.
  if (partonSystemsPtr->sizeOut(iSys) < 2) return;

  // Loop through final state of system to find possible dipole ends.
  for (int i = 0; i < partonSystemsPtr->sizeOut(iSys); ++i) {
    int iRad = partonSystemsPtr->getOut( iSys, i);

    if (event[iRad].isFinal() && event[iRad].scale() > 0.) {

      // Find dipole end formed by colour index.
      int colTag = event[iRad].col();
      if (doQCDshower && colTag > 0) setupQCDdip( iSys, i,  colTag,  1, event,
        false, true);

      // Find dipole end formed by anticolour index.
      int acolTag = event[iRad].acol();
      if (doQCDshower && acolTag > 0) setupQCDdip( iSys, i, acolTag, -1, event,
        false, true);

      // Now find non-QCD dipoles and/or update the existing dipoles.
      getGenDip( iSys, i, iRad, event, false, dipEnd);

    // End loop over system final state. Have now found the dipole ends.
    }

    // Setup decay dipoles.
    if (doDecaysAsShower && event[iRad].isResonance())
      setupDecayDip( iSys, iRad, event, dipEnd);

  }

  dipEnd.insert( dipEnd.begin(), dipLT.begin(), dipLT.end());
  dipEnd.insert( dipEnd.end(),   dipGT.begin(), dipGT.end());

  // Now update masses and allowed emissions.
  updateDipoles(event, iSys);

}

//--------------------------------------------------------------------------

// Setup a dipole end for a QCD colour charge.

void DireTimes::setupQCDdip( int iSys, int i, int colTag, int colSign,
  Event& event, bool isOctetOnium, bool limitPTmaxIn) {

  // Initial values. Find if allowed to hook up beams.
  int iRad     = partonSystemsPtr->getOut(iSys, i);
  int iRec     = 0;
  int sizeAllA = partonSystemsPtr->sizeAll(iSys);
  int sizeOut  = partonSystemsPtr->sizeOut(iSys);
  int sizeAll  = ( allowBeamRecoil ) ? sizeAllA : sizeOut;
  int sizeIn   = sizeAll - sizeOut;
  int sizeInA  = sizeAllA - sizeIn - sizeOut;
  int iOffset  = i + sizeAllA - sizeOut;
  bool otherSystemRec = false;
  bool allowInitial   = (partonSystemsPtr->hasInAB(iSys)) ? true : false;
  vector<int> iRecVec(0);

  // Colour: other end by same index in beam or opposite in final state.
  // Exclude rescattered incoming and not final outgoing.
  if (colSign > 0)
  for (int j = 0; j < sizeAll; ++j) if (j + sizeInA != iOffset) {
    int iRecNow = partonSystemsPtr->getAll(iSys, j + sizeInA);
    if ( ( j <  sizeIn && event[iRecNow].col()  == colTag
      && !event[iRecNow].isRescatteredIncoming() )
      || ( j >= sizeIn && event[iRecNow].acol() == colTag
      && event[iRecNow].isFinal() ) ) {
      iRec = iRecNow;
      break;
    }
  }

  // Anticolour: other end by same index in beam or opposite in final state.
  // Exclude rescattered incoming and not final outgoing.
  if (colSign < 0)
  for (int j = 0; j < sizeAll; ++j) if (j + sizeInA != iOffset) {
    int iRecNow = partonSystemsPtr->getAll(iSys, j + sizeInA);
    if ( ( j <  sizeIn && event[iRecNow].acol()  == colTag
      && !event[iRecNow].isRescatteredIncoming() )
      || ( j >= sizeIn && event[iRecNow].col() == colTag
      && event[iRecNow].isFinal() ) ) {
      iRec = iRecNow;
      break;
    }
  }

  // Resonance decays (= no instate):
  // other end to nearest recoiler in same system final state,
  // by (p_i + p_j)^2 - (m_i + m_j)^2 = 2 (p_i p_j - m_i m_j).
  // (junction colours more involved, so keep track if junction colour)
  bool hasJunction = false;
  if (iRec == 0 && !allowInitial) {
    for (int iJun = 0; iJun < event.sizeJunction(); ++ iJun) {
      // For types 1&2, all legs in final state
      // For types 3&4, two legs in final state
      // For types 5&6, one leg in final state
      int iBeg = (event.kindJunction(iJun)-1)/2;
      for (int iLeg = iBeg; iLeg < 3; ++iLeg)
        if (event.endColJunction( iJun, iLeg) == colTag) hasJunction  = true;
    }
    double ppMin = LARGEM2;
    for (int j = 0; j < sizeOut; ++j) if (j != i) {
        int iRecNow  = partonSystemsPtr->getOut(iSys, j);
        if (!event[iRecNow].isFinal()) continue;
        double ppNow = event[iRecNow].p() * event[iRad].p()
          - event[iRecNow].m() * event[iRad].m();
        if (ppNow < ppMin) {
          iRec  = iRecNow;
          ppMin = ppNow;
        }
      }
  }

  // If no success then look for matching (anti)colour anywhere in final state.
  if ( iRec == 0 ) {
    for (int j = 0; j < event.size(); ++j) if (event[j].isFinal()) {
      if ( (colSign > 0 && event[j].acol() == colTag)
        || (colSign < 0 && event[j].col()  == colTag) ) {
        iRec = j;
        otherSystemRec = true;
        break;
      }
    }

    // If no success then look for match to non-rescattered in initial state.
    if (iRec == 0 && allowInitial) {
      for (int iSysR = 0; iSysR < partonSystemsPtr->sizeSys(); ++iSysR)
      if (iSysR != iSys) {
        int j = partonSystemsPtr->getInA(iSysR);
        if (j > 0 && event[j].isRescatteredIncoming()) j = 0;
        if (j > 0 && ( (colSign > 0 && event[j].col() == colTag)
          || (colSign < 0 && event[j].acol()  == colTag) ) ) {
          iRec = j;
          otherSystemRec = true;
          break;
        }
        j = partonSystemsPtr->getInB(iSysR);
        if (j > 0 && event[j].isRescatteredIncoming()) j = 0;
        if (j > 0 && ( (colSign > 0 && event[j].col() == colTag)
          || (colSign < 0 && event[j].acol()  == colTag) ) ) {
          iRec = j;
          otherSystemRec = true;
          break;
        }
      }
    }
  }

  // Junctions
  // For types 1&2: all legs in final state
  //                half-strength dipoles between all legs
  // For types 3&4, two legs in final state
  //                full-strength dipole between final-state legs
  // For types 5&6, one leg in final state
  //                no final-state dipole end

  if (hasJunction) {
    for (int iJun = 0; iJun < event.sizeJunction(); ++ iJun) {
      int kindJun = event.kindJunction(iJun);
      int iBeg = (kindJun-1)/2;
      for (int iLeg = iBeg; iLeg < 3; ++iLeg) {
        if (event.endColJunction( iJun, iLeg) == colTag) {
          // For types 5&6, no other leg to recoil against. Switch off if
          // no other particles at all, since radiation then handled by ISR.
          // Example: qq -> ~t* : no radiation off ~t*
          // Allow radiation + recoil if unconnected partners available
          // Example: qq -> ~t* -> tbar ~chi0 : allow radiation off tbar,
          //                                    with ~chi0 as recoiler
          if (kindJun >= 5) {
            if (sizeOut == 1) return;
            else break;
          }
          // For junction types 3 & 4, span one full-strength dipole
          // (only look inside same decay system)
          else if (kindJun >= 3) {
            int iLegRec = 3-iLeg;
            int colTagRec = event.endColJunction( iJun, iLegRec);
            for (int j = 0; j < sizeOut; ++j) if (j != i) {
                int iRecNow  = partonSystemsPtr->getOut(iSys, j);
                if (!event[iRecNow].isFinal()) continue;
                if ( (colSign > 0 && event[iRecNow].col()  == colTagRec)
                  || (colSign < 0 && event[iRecNow].acol() == colTagRec) ) {
                  // Only accept if staying inside same system
                  iRec = iRecNow;
                  break;
                }
              }
          }
          // For junction types 1 & 2, span two half-strength dipoles
          // (only look inside same decay system)
          else {
            // Loop over two half-strength dipole connections
            for (int jLeg = 1; jLeg <= 2; jLeg++) {
              int iLegRec = (iLeg + jLeg) % 3;
              int colTagRec = event.endColJunction( iJun, iLegRec);
              for (int j = 0; j < sizeOut; ++j) if (j != i) {
                  int iRecNow  = partonSystemsPtr->getOut(iSys, j);
                  if (!event[iRecNow].isFinal()) continue;
                  if ( (colSign > 0 && event[iRecNow].col()  == colTagRec)
                    || (colSign < 0 && event[iRecNow].acol() == colTagRec) ) {
                    // Store recoilers in temporary array
                    iRecVec.push_back(iRecNow);
                    // Set iRec != 0 for checks below
                    iRec = iRecNow;
                  }
                }
            }

          }     // End if-then-else of junction kinds

        }       // End if leg has right color tag
      }         // End of loop over junction legs
    }           // End loop over junctions

  }             // End main junction if

  // If fail, then other end to nearest recoiler in same system final state,
  // by (p_i + p_j)^2 - (m_i + m_j)^2 = 2 (p_i p_j - m_i m_j).
  if (iRec == 0) {
    double ppMin = LARGEM2;
    for (int j = 0; j < sizeOut; ++j) if (j != i) {
      int iRecNow  = partonSystemsPtr->getOut(iSys, j);
      if (!event[iRecNow].isFinal()) continue;
      double ppNow = event[iRecNow].p() * event[iRad].p()
                   - event[iRecNow].m() * event[iRad].m();
      if (ppNow < ppMin) {
        iRec  = iRecNow;
        ppMin = ppNow;
      }
    }
  }

  // If fail, then other end to nearest recoiler in any system final state,
  // by (p_i + p_j)^2 - (m_i + m_j)^2 = 2 (p_i p_j - m_i m_j).
  if (iRec == 0) {
    double ppMin = LARGEM2;
    for (int iRecNow = 0; iRecNow < event.size(); ++iRecNow)
    if (iRecNow != iRad && event[iRecNow].isFinal()) {
      double ppNow = event[iRecNow].p() * event[iRad].p()
                   - event[iRecNow].m() * event[iRad].m();
      if (ppNow < ppMin) {
        iRec  = iRecNow;
        otherSystemRec = true;
        ppMin = ppNow;
      }
    }
  }
  if (iRecVec.size() == 0 && iRec != 0) iRecVec.push_back(iRec);

  // Remove any zero recoilers from normalization
  int nRec = iRecVec.size();
  for (unsigned int mRec = 0; mRec < iRecVec.size(); ++mRec)
    if (iRecVec[mRec] <= 0) nRec--;

  // Check for failure to locate any recoiler
  if ( nRec <= 0 ) {
    infoPtr->errorMsg("Error in DireTimes::setupQCDdip: "
                      "failed to locate any recoiling partner");
    return;
  }

  // Store dipole colour end(s).
  for (unsigned int mRec = 0; mRec < iRecVec.size(); ++mRec) {
    iRec = iRecVec[mRec];
    if (iRec <= 0) continue;
    // Max scale either by parton scale or by dipole mass.
    double pTmax = event[iRad].scale();
    if (limitPTmaxIn) {
      if (iSys == 0 || (iSys == 1 && doSecondHard)) pTmax *= pTmaxFudge;
      else if (sizeIn > 0) pTmax *= pTmaxFudgeMPI;
    //} else pTmax = 0.5 * m( event[iRad], event[iRec]);
    } else pTmax = m( event[iRad], event[iRec]);

    // Force maximal pT to LHEF input value.
    if ( abs(event[iRad].status()) > 20 &&  abs(event[iRad].status()) < 24
      && settingsPtr->flag("Beams:setProductionScalesFromLHEF")
      && event[iRad].scale() > 0.)
      pTmax = event[iRad].scale();

    int colType  = (event[iRad].id() == 21) ? 2 * colSign : colSign;
    int isrType  = (event[iRec].isFinal()) ? 0 : event[iRec].mother1();
    // This line in case mother is a rescattered parton.
    while (isrType > 2 + beamOffset) isrType = event[isrType].mother1();
    if (isrType > 2) isrType -= beamOffset;
    appendDipole( event, iRad, iRec, pTmax, colType, 0, 0, 0, isrType, iSys,
      -1, -1, 0, isOctetOnium, /*false, false, -1, -1,*/ dipEnd);

    // If hooked up with other system then find which.
    if (otherSystemRec) {
      int systemRec = partonSystemsPtr->getSystemOf(iRec, true);
      if (systemRec >= 0) dipEnd.back().systemRec = systemRec;
      dipEnd.back().MEtype = 0;
    }

  }

}

//--------------------------------------------------------------------------

// Setup a dipole end for a QCD colour charge.

void DireTimes::setupDecayDip( int iSys, int iRad, const Event& event,
  vector<DireTimesEnd>& dipEnds) {

  // Initial values. Find if allowed to hook up beams.
  int iRec          = 0;
  int sizeOut       = partonSystemsPtr->sizeOut(iSys);
  bool allowInitial = (partonSystemsPtr->hasInAB(iSys)) ? true : false;

  // First try nearest recoiler in same system in final state,
  // by (p_i + p_j)^2 - (m_i + m_j)^2 = 2 (p_i p_j - m_i m_j).
  if (iRec == 0) {
    double ppMin = LARGEM2;
    for (int j = 0; j < sizeOut; ++j) {
      int iRecNow  = partonSystemsPtr->getOut(iSys, j);
      if (iRecNow == iRad || !event[iRecNow].isFinal()) continue;
      double ppNow = event[iRecNow].p() * event[iRad].p()
                   - event[iRecNow].m() * event[iRad].m();
      if (ppNow < ppMin) {
        iRec  = iRecNow;
        ppMin = ppNow;
      }
    }
  }

  // Now try nearest recoiler in same system in initial state,
  // by -(p_i - p_j)^2 - (m_i + m_j)^2 = 2 (p_i p_j - m_i m_j).
  if (iRec == 0 && allowInitial) {
    double ppMin = LARGEM2;
    // Check first beam.
    int iRecNow = partonSystemsPtr->getInA(iSys);
    double ppNow = event[iRecNow].p() * event[iRad].p()
          - event[iRecNow].m() * event[iRad].m();
    if (ppNow < ppMin) {
      iRec  = iRecNow;
      ppMin = ppNow;
    }

    // Check second beam.
    iRecNow     = partonSystemsPtr->getInB(iSys);
    ppNow       = event[iRecNow].p() * event[iRad].p()
                - event[iRecNow].m() * event[iRad].m();
    if (ppNow < ppMin) {
      iRec  = iRecNow;
      ppMin = ppNow;
    }
  }

  double pTmax = event[iRad].scale();
  pTmax = m( event[iRad], event[iRec]);
  int colType  = event[iRad].colType();
  int isrType  = (event[iRec].isFinal()) ? 0 : event[iRec].mother1();
  // This line in case mother is a rescattered parton.
  while (isrType > 2 + beamOffset) isrType = event[isrType].mother1();
  if (isrType > 2) isrType -= beamOffset;
  if (iRec > 0) {
    appendDipole( event, iRad, iRec, pTmax, colType, 0, 0, 0, isrType, 0,
          -1, -1, 0, false, dipEnds);
  }

}

//--------------------------------------------------------------------------

// Setup a dipole end for a QCD colour charge.

void DireTimes::getGenDip( int iSys, int i, int iRadIn,
  const Event& event, bool limitPTmaxIn, vector<DireTimesEnd>& dipEnds) {

  // Initial values.
  int iRad     = (iSys > -1) ? partonSystemsPtr->getOut(iSys, i) : iRadIn;
  int sizeAllA = (iSys > -1) ? partonSystemsPtr->sizeAll(iSys) : event.size();
  int sizeOut  = (iSys > -1) ? partonSystemsPtr->sizeOut(iSys) : event.size();
  int sizeAll  = (iSys > -1) ? (( allowBeamRecoil ) ? sizeAllA : sizeOut)
               : event.size();
  int sizeIn   = (iSys > -1) ? sizeAll - sizeOut : 0;
  int sizeInA  = (iSys > -1) ? sizeAllA - sizeIn - sizeOut : 0;
  int iOffset  = (iSys > -1) ? i + sizeAllA - sizeOut : 0;
  int beamA = (iSys>-1) ? event[getInA(iSys)].mother1() : 1;
  int beamB = (iSys>-1) ? event[getInB(iSys)].mother1() : 2;

  for (int j = 0; j < sizeAll; ++j) if (iSys < 0 || j + sizeInA != iOffset) {

    int iRecNow = (iSys > -1) ? partonSystemsPtr->getAll(iSys, j+sizeInA) : j;
    if ( !event[iRecNow].isFinal()
       && event[iRecNow].mother1() != beamA
       && event[iRecNow].mother1() != beamB) continue;

    // Skip radiator.
    if ( iRecNow == iRad) continue;

    // Skip if dipole already exists, attempt to update the dipole end (a)
    // for the current a-b dipole.
    vector<int> iDip;
    for (int k = 0; k < int(dipEnds.size()); ++k)
      if ( dipEnds[k].iRadiator == iRad && dipEnds[k].iRecoiler == iRecNow )
        iDip.push_back(k);
    if ( int(iDip.size()) > 0) {
      for (int k = 0; k < int(iDip.size()); ++k)
        updateAllowedEmissions(event, &dipEnds[iDip[k]]);
      continue;
    }

    double pTmax = event[iRad].scale();
    if (limitPTmaxIn) {
      if (iSys == 0 || (iSys == 1 && doSecondHard)) pTmax *= pTmaxFudge;
      else if (sizeIn > 0) pTmax *= pTmaxFudgeMPI;
    } else pTmax = m( event[iRad], event[iRecNow]);
    int isrType  = (event[iRecNow].isFinal()) ? 0 : event[iRecNow].mother1();
    // This line in case mother is a rescattered parton.
    while (isrType > 2 + beamOffset) isrType = event[isrType].mother1();
    if (isrType > 2) isrType -= beamOffset;

    appendDipole( event, iRad, iRecNow, pTmax, 0, 0, 0, 0, isrType,
      (iSys > -1) ? iSys : 0, -1, -1, 0, false, dipEnds);
  }

  // Done.
  return;

}

//--------------------------------------------------------------------------

// Setup a dipole end for a QCD colour charge.

void DireTimes::getQCDdip( int iRad, int colTag, int colSign,
  const Event& event, vector<DireTimesEnd>& dipEnds) {

  // Initial values. Find if allowed to hook up beams.
  int iRec     = 0;

  // Colour: other end by same index in beam or opposite in final state.
  // Exclude rescattered incoming and not final outgoing.
  if (colSign > 0)
  for (int iRecNow = 0; iRecNow < event.size(); ++iRecNow) {
    if (iRecNow == iRad) continue;
    if ( ( event[iRecNow].col()  == colTag
      && !event[iRecNow].isFinal() && !event[iRecNow].isRescatteredIncoming() )
      || ( event[iRecNow].acol() == colTag
      && event[iRecNow].isFinal() ) ) {
      iRec = iRecNow;
      break;
    }
  }

  // Anticolour: other end by same index in beam or opposite in final state.
  // Exclude rescattered incoming and not final outgoing.
  if (colSign < 0)
  for (int iRecNow = 0; iRecNow < event.size(); ++iRecNow) {
    if (iRecNow == iRad) continue;
    if ( ( event[iRecNow].acol()  == colTag
      && !event[iRecNow].isFinal() && !event[iRecNow].isRescatteredIncoming() )
      || ( event[iRecNow].col() == colTag
      && event[iRecNow].isFinal() ) ) {
      iRec = iRecNow;
      break;
    }
  }

  double pTmax = event[iRad].scale();
  pTmax = m( event[iRad], event[iRec]);
  int colType  = (event[iRad].id() == 21) ? 2 * colSign : colSign;
  int isrType  = (event[iRec].isFinal()) ? 0 : event[iRec].mother1();
  // This line in case mother is a rescattered parton.
  while (isrType > 2 + beamOffset) isrType = event[isrType].mother1();
  if (isrType > 2) isrType -= beamOffset;
  if (iRec > 0) {
    appendDipole( event, iRad, iRec, pTmax, colType, 0, 0, 0,
          isrType, 0, -1, -1, 0, false, dipEnds);
  }

}

//--------------------------------------------------------------------------

// Function to set up and append a new dipole.

bool DireTimes::appendDipole( const Event& state, int iRad, int iRec,
  double pTmax, int colType, int chgType, int gamType, int weakType,
  int isrType, int iSys, int MEtype, int iMEpartner, int weakPol, 
  bool isOctetOnium, vector<DireTimesEnd>& dipEnds) {

  // Do not append if the dipole is already known!
  for (int i = 0; i < int(dipEnds.size()); ++i)
    if (dipEnds[i].iRadiator == iRad
     && dipEnds[i].iRecoiler == iRec
     && dipEnds[i].colType   == colType)
      return false;

  // Check and reset color type.
  if (colType == 0 && state[iRad].colType() != 0) {
    vector<int> shared = sharedColor(state[iRad], state[iRec]);
    // Loop through dipoles to check if a dipole with the current rad, rec
    // and colType already exists. If not, reset colType.
    int colTypeNow(0);
    for ( int i=0; i < int(shared.size()); ++i) {
      if ( state[iRad].colType() == 2 && state[iRad].col() == shared[i])
        colTypeNow = 2;
      if ( state[iRad].colType() == 2 && state[iRad].acol() == shared[i])
        colTypeNow =-2;
      if ( state[iRad].colType() == 1 && state[iRad].id() > 0
        && state[iRad].col() == shared[i])
        colTypeNow = 1;
      if ( state[iRad].colType() ==-1 && state[iRad].id() < 0
        && state[iRad].acol() == shared[i])
        colTypeNow =-1;
      bool found = false;
      for ( int j=0; j < int(dipEnds.size()); ++j) {
        if ( dipEnds[j].iRadiator == iRad && dipEnds[j].iRecoiler == iRec
          && dipEnds[j].colType == colTypeNow) { found = true; break; }
      }
      // Reset if color tag has not been found.
      if (!found) break;
    }
    colType = colTypeNow;
  }

  // Check and reset isr type.
  if (isrType == 0 && !state[iRec].isFinal()) isrType = state[iRec].mother1();
  int isrTypeNow  = isrType;
  while (isrTypeNow > 2 + beamOffset) isrTypeNow = state[isrTypeNow].mother1();
  if (isrTypeNow > 2) isrTypeNow -= beamOffset;

  // Check if designated color charge is connected.
  if (colType != 0) {
    vector<int> share = sharedColor(state[iRad], state[iRec]);
    if (colType > 0 && find(share.begin(), share.end(), state[iRad].col())
      == share.end()) return false;
    if (colType < 0 && find(share.begin(), share.end(), state[iRad].acol())
      == share.end()) return false;
  }

  // Construct dipole.
  DireTimesEnd dipNow = DireTimesEnd( iRad, iRec, pTmax, colType, chgType,
    gamType, weakType, isrTypeNow, iSys, MEtype, iMEpartner, weakPol,
    isOctetOnium);
  dipNow.clearAllowedEmt();
  dipNow.init(state);

  if (updateAllowedEmissions(state, &dipNow)) {
    dipEnds.push_back(dipNow);
    return true;
  }

  // Done.
  return false;
}

//--------------------------------------------------------------------------

vector<int> DireTimes::sharedColor(const Particle& rad, const Particle& rec) {
  vector<int> ret;
  int radCol(rad.col()), radAcl(rad.acol()),
      recCol(rec.col()), recAcl(rec.acol());
  if ( rad.isFinal() && rec.isFinal() ) {
    if (radCol != 0 && radCol == recAcl) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recCol) ret.push_back(radAcl);
  } else if ( rad.isFinal() && !rec.isFinal() ) {
    if (radCol != 0 && radCol == recCol) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recAcl) ret.push_back(radAcl);
  } else if (!rad.isFinal() && rec.isFinal() )  {
    if (radCol != 0 && radCol == recCol) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recAcl) ret.push_back(radAcl);
  } else if (!rad.isFinal() && !rec.isFinal() ) {
    if (radCol != 0 && radCol == recAcl) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recCol) ret.push_back(radAcl);
  }
  return ret;
}

//--------------------------------------------------------------------------

// Function to update the list of all dipoles.

void DireTimes::saveSiblings(const Event& state, int iSys) {

  int sizeAllSys = partonSystemsPtr->sizeSys();
  for (int iSystem=0; iSystem < sizeAllSys; ++iSystem) {

  if (iSys > -1 && iSystem != iSys) continue;

  // Get kernel order.
  int order = kernelOrder;
  // Use simple kernels for showering secondary scatterings.
  bool hasInA = (partonSystemsPtr->getInA(iSystem) != 0);
  bool hasInB = (partonSystemsPtr->getInB(iSystem) != 0);
  if (iSystem != 0 && hasInA && hasInB) order = kernelOrderMPI;
  if (order != 4) return;
  
  int beamA = (iSys>-1) ? state[getInA(iSystem)].mother1() : 1;
  int beamB = (iSys>-1) ? state[getInB(iSystem)].mother1() : 2;

  vector<int> q, qb, g;
  int sizeSystem(partonSystemsPtr->sizeAll(iSystem)), nFinal(0);
  for ( int i = 0; i < sizeSystem; ++i) {

    int iPos = partonSystemsPtr->getAll(iSystem, i);
    if ( state[iPos].isFinal()) nFinal++;

    if (!state[iPos].isFinal()
      && state[iPos].mother1() != beamA
      && state[iPos].mother1() != beamB) continue; 

    // Check if this is a hadron decay system.
    bool hasHadMother=false;
    int iPosNow = iPos;
    while (state[iPosNow].mother1() > 0) {
      hasHadMother = (state[iPosNow].statusAbs() > 60);
      if (hasHadMother) break;
      iPosNow = state[iPosNow].mother1();
    }
    if (hasHadMother) continue;

    if ( state[iPos].isFinal() && state[iPos].colType() == 1
      && find(q.begin(),q.end(),iPos) == q.end())
      q.push_back(iPos);

    if (!state[iPos].isFinal() && state[iPos].colType() ==-1
      && find(q.begin(),q.end(),iPos) == q.end())
      q.push_back(iPos);

    if ( state[iPos].isFinal() && state[iPos].colType() ==-1
      && find(qb.begin(),qb.end(),iPos) == qb.end())
      qb.push_back(iPos);

    if (!state[iPos].isFinal() && state[iPos].colType() == 1
      && find(qb.begin(),qb.end(),iPos) == qb.end())
      qb.push_back(iPos);

    if ( abs(state[iPos].colType()) == 2
      && find(g.begin(),g.end(),iPos) == g.end())
      g.push_back(iPos);
  }

  // Find all chains of gluon-connected dipoles.
  DireColChains chains;
  if (nFinal > 0) {
    // Start with quark ends.
    for (int i = 0; i < int(q.size()); ++i) {
      if (chains.chainOf(q[i]).size() != 0) continue;
      chains.addChain( DireSingleColChain(q[i],state, partonSystemsPtr));
    }
    // Try all antiquark ends.
    for (int i = 0; i < int(qb.size()); ++i) {
      if (chains.chainOf(qb[i]).size() != 0) continue;
      chains.addChain( DireSingleColChain(qb[i],state, partonSystemsPtr));
    }
    // Try all gluon ends.
    for (int i = 0; i < int(g.size()); ++i) {
      // Try both color ends.
      if (chains.chainOf(g[i]).size() != 0) continue;
      chains.addChain( DireSingleColChain(g[i],state, partonSystemsPtr));
    }
  }

  // For each radiator, store siblings (dipole and next adjacent dipole)
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    if (dipEnd[iDip].system != iSystem) continue;
    if (dipEnd[iDip].colType == 0) dipEnd[iDip].clearSiblings();
    else {
      int col = dipEnd[iDip].colType > 0
              ? state[dipEnd[iDip].iRadiator].col()
              : state[dipEnd[iDip].iRadiator].acol();
      dipEnd[iDip].setSiblings(chains.chainFromCol( dipEnd[iDip].iRadiator,
        col, 2, state));
    }
  }

  }

  // Done.
}

//--------------------------------------------------------------------------

// Function to update the list of all dipoles.

void DireTimes::updateDipoles(const Event& state, int iSys) {

  // Update the dipoles, and if necesarry, flag inactive dipoles for removal.
  vector<int> iRemove;
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    if (!updateAllowedEmissions(state, &dipEnd[iDip])
      && find(iRemove.begin(), iRemove.end(), iDip) == iRemove.end())
      iRemove.push_back(iDip);
    dipEnd[iDip].init(state);
  }

  // Now remove inactive dipoles.
  sort (iRemove.begin(), iRemove.end());  
  for (int i = iRemove.size()-1; i >= 0; --i) {
    dipEnd[iRemove[i]] = dipEnd.back();
    dipEnd.pop_back();
  }

  // Check the list of dipoles.
  checkDipoles(state);
  saveSiblings(state, iSys);

}

//--------------------------------------------------------------------------

// Function to check a new dipole.

void DireTimes::checkDipoles(const Event& state) {

  // Update the dipoles, and if necessary, flag inactive dipoles for removal.
  vector<int> iRemove;
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    DireTimesEnd& dipi = dipEnd[iDip];
    for (int jDip = iDip+1; jDip < int(dipEnd.size()); ++jDip) {
      DireTimesEnd& dipj = dipEnd[jDip];

      // Remove double-counted dipoles.
      if (dipi == dipj && find(iRemove.begin(), iRemove.end(), iDip)
        == iRemove.end()) iRemove.push_back(iDip);

      // Check with identical radiator.
      if (dipi.iRadiator == dipj.iRadiator) {
        // If both dipoles are allowed to radiate gluons, keep only dipoles
        // with colored recoiler.
        bool iEmtGlue = find(dipi.allowedEmissions.begin(),
          dipi.allowedEmissions.end(), 21) != dipi.allowedEmissions.end();
        bool jEmtGlue = find(dipj.allowedEmissions.begin(),
          dipj.allowedEmissions.end(), 21) != dipj.allowedEmissions.end();
        if (iEmtGlue && jEmtGlue) {
          bool connectI = int(sharedColor(state[dipi.iRadiator],
            state[dipi.iRecoiler]).size()) > 0;
          bool connectJ = int(sharedColor(state[dipj.iRadiator],
            state[dipj.iRecoiler]).size()) > 0;
          if ( connectI && !connectJ) dipj.removeAllowedEmt(21);
          if (!connectI &&  connectJ) dipi.removeAllowedEmt(21);
        }

        // If both dipoles are allowed to radiate quarks, keep only dipoles
        // with colored recoiler.
        bool iEmtQ = find(dipi.allowedEmissions.begin(),
          dipi.allowedEmissions.end(), 1) != dipi.allowedEmissions.end();
        bool jEmtQ = find(dipj.allowedEmissions.begin(),
          dipj.allowedEmissions.end(), 1) != dipj.allowedEmissions.end();
        if ( state[dipi.iRadiator].colType() != 0 && iEmtQ
          && state[dipj.iRadiator].colType() != 0 && jEmtQ) {
          bool connectI = int(sharedColor(state[dipi.iRadiator],
            state[dipi.iRecoiler]).size()) > 0;
          bool connectJ = int(sharedColor(state[dipj.iRadiator],
            state[dipj.iRecoiler]).size()) > 0;
          if ( connectI && !connectJ) dipj.removeAllowedEmt(1);
          if (!connectI &&  connectJ) dipi.removeAllowedEmt(1);
        }

        // If both dipoles are allowed to radiate photons, keep only dipoles
        // with charged recoiler.
        bool iEmtA = find(dipi.allowedEmissions.begin(),
          dipi.allowedEmissions.end(), 22) != dipi.allowedEmissions.end();
        bool jEmtA = find(dipj.allowedEmissions.begin(),
          dipj.allowedEmissions.end(), 22) != dipj.allowedEmissions.end();
        if (iEmtA && jEmtA) {
          bool connectI = state[dipi.iRecoiler].isCharged();
          bool connectJ = state[dipj.iRecoiler].isCharged();
          if ( connectI && !connectJ) dipj.removeAllowedEmt(22);
          if (!connectI &&  connectJ) dipi.removeAllowedEmt(22);
        }

      }
    }
  }

  // Flag inactive dipoles for removal.
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    if (!dipEnd[iDip].canEmit() && find(iRemove.begin(), iRemove.end(), iDip)
       == iRemove.end()) iRemove.push_back(iDip);
  }

  // Now remove problematic dipoles.
  sort (iRemove.begin(), iRemove.end());
  for (int i = iRemove.size()-1; i >= 0; --i) {
    dipEnd[iRemove[i]] = dipEnd.back();
    dipEnd.pop_back();
  }

  // Now go through dipole list and perform rudimentary checks.
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
    DireTimesEnd* dip = &dipEnd[iDip];
    int iRad = dip->iRadiator;
    int iRec = dip->iRecoiler;
    // Check and reset color type.
    if (dip->colType == 0 && state[iRad].colType() != 0) {
      vector<int> shared = sharedColor(state[iRad], state[iRec]);
      // Loop through dipoles to check if a dipole with the current rad, rec
      // and colType already exists. If not, reset colType.
      int colTypeNow(0);
      for ( int i=0; i < int(shared.size()); ++i) {
        if ( state[iRad].colType() == 2 && state[iRad].col() == shared[i])
          colTypeNow = 2;
        if ( state[iRad].colType() == 2 && state[iRad].acol() == shared[i])
          colTypeNow =-2;
        if ( state[iRad].colType() == 1 && state[iRad].id() > 0
          && state[iRad].col() == shared[i])
          colTypeNow = 1;
        if ( state[iRad].colType() ==-1 && state[iRad].id() < 0
          && state[iRad].acol() == shared[i])
          colTypeNow =-1;
      }
      dip->colType = colTypeNow;
    }
    // Check and reset isr type.
    if ( dip->isrType == 0 && !state[iRec].isFinal() ) {
      int type = state[iRec].mother1();
      while (type > 2 + beamOffset) type = state[type].mother1();
      if (type > 2) type -= beamOffset;
      dip->isrType = type;
    }
  }

}

//--------------------------------------------------------------------------

bool DireTimes::updateAllowedEmissions(const Event& state, DireTimesEnd* dip) {
  // Clear any allowed emissions.
  dip->clearAllowedEmt();
  // Append all possible emissions.
  return appendAllowedEmissions(state, dip);
}

//--------------------------------------------------------------------------

// Function to set up and append a new dipole.

bool DireTimes::appendAllowedEmissions(const Event& state, DireTimesEnd* dip) {

  // Now loop through all splitting kernels to find which emissions are
  // allowed from the current radiator-recoiler combination.
  bool isAllowed = false;
  int iRad(dip->iRadiator), iRec(dip->iRecoiler);
  pair<int,int> iRadRec(make_pair(iRad, iRec));
  pair<int,int> iRecRad(make_pair(iRec, iRad));

  for (size_t i = 0; i < splitsVec.size(); ++i) {

    DireSplitting* splitNow = splitsVec[i];

    // Check if splitting is allowed.
    bool allowed = splitNow->useFastFunctions()
                 ? splitNow->canRadiate(state,iRad,iRec)
                 : splitNow->canRadiate(state,iRadRec,bool_settings);

    if (!allowed) continue;

    // Get emission id.
    int * re = splitNow->radAndEmtArr( state[iRad].id(), dip->colType);

    // Do not decay resonances that were not generated by previous emissions.
    if ( particleDataPtr->isResonance(state[iRad].id())
      && !direInfoPtr->isRes(iRad) && state[iRad].id() != re[0])
      continue;

    //for (int iEmtAft=1; iEmtAft < int(re.size()); ++iEmtAft) {
    for (int iEmtAft=1; iEmtAft < 3; ++iEmtAft) {

      int idEmtAft = re[iEmtAft];

      if (idEmtAft==0) break;

      if (splitNow->is_qcd) {
        idEmtAft = abs(idEmtAft);
        if (idEmtAft<10) idEmtAft = 1;
      }

      if (!splitNow->isPartial()) {
        dip->appendAllowedEmt(idEmtAft);
        isAllowed = true;
      } else {
        // Now check that emission also allowed when radiating from recoiler.
        bool isPartialFractioned = false;
        for (size_t j=0; j < splitsVec.size(); ++j) {

          if ( isPartialFractioned ) break;

          DireSplitting* splitRec = splitsVec[j];

          bool allowedRec = splitRec->useFastFunctions()
                 ? splitRec->canRadiate(state,iRec,iRad)
                 : splitRec->canRadiate(state,iRecRad,bool_settings);

          if (!allowedRec) continue;

          // Get emission id.
          int colTypeRec
            = state[iRec].isFinal() ? -dip->colType : dip->colType;
          int * reRec
            = splitRec->radAndEmtArr( state[iRec].id(), colTypeRec);

          //for (int iEmtAftRec=1; iEmtAftRec<int(reRec.size()); ++iEmtAftRec) {
          for (int iEmtAftRec=1; iEmtAftRec<3; ++iEmtAftRec) {
            int idEmtAftRec = reRec[iEmtAftRec];
            if (idEmtAftRec==0) break;
            if (splitRec->is_qcd) {
              idEmtAftRec = abs(idEmtAftRec);
              if (idEmtAftRec<10) idEmtAftRec = 1;
            }
            if (idEmtAftRec == idEmtAft) { isPartialFractioned = true; break;}
          }
        }
        // Only allow if the emission can be performed from both dipole ends.
        if (isPartialFractioned) {
          dip->appendAllowedEmt(idEmtAft);
          isAllowed = true;
        }
      }
    }
  }

  // Done.
  return isAllowed;
}

//--------------------------------------------------------------------------

// Select next pT in downwards evolution of the existing dipoles.
// Classical Sudakov veto algorithm to produce next set of state variables.

double DireTimes::pTnext( Event& event, double pTbegAll, double pTendAll,
  bool, bool doTrialIn ) {

  if (direInfoPtr->usePTLast()) {
    pTbegAll = direInfoPtr->pTLast();
    if (evolutionWindows.size()>0) pTbegAll = direInfoPtr->pTLastMin();
  }

  direInfoPtr->message(1) << scientific << setprecision(8)
    << "Next FSR starting from " << pow2(pTbegAll)
    << " . Current PS weights "
    << weights->getShowerWeight() << " " 
    << weights->getShowerWeight("scaleUp") << " " 
    << weights->getShowerWeight("scaleDown") << " "
    << endl;

  // Begin loop over all possible radiating dipole ends.
  double pT2sel = pTendAll * pTendAll;
  double pT2beg = pTbegAll*pTbegAll;
  clearInfos();

  // Remember if this is a trial emission.
  doTrialNow    = doTrialIn;

  if (evolutionWindows.empty()) evolutionWindows.insert(
    EvolutionWindow(pT2sel, pT2beg, evolutionWindows.size()));

  int nWindows = evolutionWindows.size();

  for (auto w : evolutionWindows) {

    // Find the boundaries of the evolution window.
    double tMaxNow    = w.tMax;
    double tMinNow    = w.tMin;
    bool resEvolution = w.isResonant;

    bool inclusiveEvolution
      = (find(w.evolvingIds.begin(),w.evolvingIds.end(),0)
        != end(w.evolvingIds));

    iWindowNow = w.iWindow;

    // Now propose a transition for each dipole.
    for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {
      DireTimesEnd& dip = dipEnd[iDip];

      // Limit final state multiplicity. For debugging only
      int nfmax = settingsPtr->mode("DireTimes:nFinalMax");
      int nFinal = 0;
      for (int i=0; i < event.size(); ++i)
        if (event[i].isFinal()) nFinal++;
      if (nfmax > -10 && nFinal > nfmax) continue;

      // Dipole properties.
      int iR     = dip.iRadiator;
      int iS     = dip.iRecoiler;
      int idRad  = event[iR].id();
      bool isRes = particleDataPtr->isResonance(idRad);
      if (resEvolution && !isRes) continue;

      if (!inclusiveEvolution && find(w.evolvingIds.begin(),w.evolvingIds.end(),
        idRad) == end(w.evolvingIds)) continue;

      dip.mRad   = event[iR].m();
      dip.mRec   = event[iS].m();
      dip.mDip   = sqrt( abs(2. * event[iR].p() * event[iS].p()) );
      dip.m2Rad  = pow2(dip.mRad);
      dip.m2Rec  = pow2(dip.mRec);
      dip.m2Dip  = pow2(dip.mDip);

      // Find maximum mass scale for dipole.
      dip.m2DipCorr    = dip.m2Dip;

      double pT2start = min( dip.m2Dip, tMaxNow);
      //double pT2stop  = max( pT2cutMin(&dip), pTendAll*pTendAll);
      double pT2stop  = max( pT2cutMin(&dip), tMinNow);

      direInfoPtr->message(1) << scientific << setprecision(8)
      << "Next FSR starting scale " << pT2start << " " << iWindowNow << endl;

      // For only one evolution window, can adjust the pT cut to
      // last selection to increase performance.
      if (nWindows==1) pT2stop = max( pT2stop, pT2sel);

      // Reset emission properties.
      dip.pT2         =  0.0;
      dip.z           = -1.0;
      dip.phi         = -1.0;
      // Reset properties of 1->3 splittings.
      dip.sa1         =  0.0;
      dip.xa          = -1.0;
      dip.phia1       = -1.0;
      dip.mass.clear();
      dip.idRadAft = 0;
      dip.idEmtAft = 0;

      // Do not try splitting if the corrected dipole mass is negative.
      if (dip.m2DipCorr < 0.) {
        infoPtr->errorMsg("Warning in DireTimes::pTnext: "
        "negative dipole mass.");
        continue;
      }

      // Evolution.
      if (pT2start > pT2sel) {

        // Store start/end scales.
        dip.pT2start = pT2start;
        dip.pT2stop  = pT2stop;

        // Do evolution if it makes sense.
        if ( dip.canEmit() ) {

          if (!resEvolution)
            pT2nextQCD(pT2start, pT2stop, dip, event, -1., 0.,false);
          else 
            tNextDecay(pT2start, pT2stop, dip, event, -1., 0.,false);

          // Update if found pT larger than current maximum.
          if (dip.pT2 > pT2sel) {
            pT2sel  = dip.pT2;
            dipSel  = &dip;
            iDipSel = iDip;
            dipSelStore = DireTimesEnd(dip);
            splittingSelName = splittingNowName;
            splitInfoSel.store(splits[splittingSelName]->splitInfo);
            splittingSel = splits[splittingSelName];
            kernelSel = kernelNow;
            auxSel    = auxNow;
            overSel   = overNow;
            boostSel  = boostNow;
            iWindowSel = iWindowNow;
          }
        }
      }
    }
  }

  // Recover selected dipole if overwritten by subsequent trials.
  if (dipSel) dipEnd[iDipSel] = dipSelStore;

  // Update the number of proposed timelike emissions.
  if (dipSel != 0 && nProposedPT.find(dipSel->system) != nProposedPT.end())
    ++nProposedPT[dipSel->system];

  // Insert additional weights.
  for ( unordered_map<string, multimap<double,double> >::iterator
    itR = rejectProbability.begin(); itR != rejectProbability.end(); ++itR)
    weights->insertWeights(acceptProbability[itR->first], itR->second,
      itR->first);

  for ( unordered_map<string, multimap<double,double> >::iterator
    it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
    it->second.clear();
  for ( unordered_map<string, map<double,double> >::iterator
    it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
    it->second.clear();

  resetOverheadFactors();

  // Timelike shower of resonances: Finalize in case resonances where produced.
  bool hasInAB = false;
  for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) 
    if (partonSystemsPtr->hasInAB(dipEnd[iDip].system)) hasInAB = true;
  if (dipSel == 0 && !hasInAB ) finalize(event);

  //if (dipSel!=0) direInfoPtr->message(1) << scientific << setprecision(8)
  //  << "Next FSR splitting proposed at tEvol=" << pT2sel << endl;
  //else direInfoPtr->message(1) << scientific << setprecision(8)
  //  << "No next FSR splitting found above " << pTendAll*pTendAll << endl;

  return (dipSel == 0) ? 0. : sqrt(pT2sel);

}

//--------------------------------------------------------------------------

double DireTimes::newPoint( const Event& inevt) {

  int asOrderSave = alphaSorder;
  double pT2minMECsSave = pT2minMECs;
  alphaSorder = 0.;
  pT2minMECs = 0.;
  double tFreeze = 1.;

  Event event(inevt);

  // Begin loop over all possible radiating dipole ends.
  double pTendAll = 0.;
  double pT2sel = pTendAll * pTendAll;
  clearInfos();

  int nTrials=0;
  int nTrialsMax=200;
  while (pT2sel==0.) {

    nTrials++;
    if (nTrials>=nTrialsMax) break;

    for (int iDip = 0; iDip < int(dipEnd.size()); ++iDip) {

      DireTimesEnd& dip = dipEnd[iDip];

      // Dipole properties.
      dip.mRad   = event[dip.iRadiator].m();
      dip.mRec   = event[dip.iRecoiler].m();
      dip.mDip   =
        sqrt( abs(2. * event[dip.iRadiator].p() * event[dip.iRecoiler].p()) );
      dip.m2Rad  = pow2(dip.mRad);
      dip.m2Rec  = pow2(dip.mRec);
      dip.m2Dip  = pow2(dip.mDip);

      // Find maximum mass scale for dipole.
      dip.m2DipCorr    = dip.m2Dip;

      double pT2start = m2Max(iDip, event);
      double pT2stop  = pTendAll*pTendAll;

      // Reset emission properties.
      dip.pT2         =  0.0;
      dip.z           = -1.0;
      dip.phi         = -1.0;
      // Reset properties of 1->3 splittings.
      dip.sa1         =  0.0;
      dip.xa          = -1.0;
      dip.phia1       = -1.0;
      dip.mass.clear();
      dip.idRadAft = 0;
      dip.idEmtAft = 0;

      // Store start/end scales.
      dip.pT2start = pT2start;
      dip.pT2stop  = pT2stop;

      // Do evolution if it makes sense.
      if (dip.canEmit())
        pT2nextQCD(pT2start,0.,dip,event,0.,tFreeze,true);

      if (dip.pT2 > pT2sel) {
        pT2sel = dip.pT2;
        dipSel  = &dip;
        iDipSel = iDip;
        splittingSelName = splittingNowName;
        splitInfoSel.store(splits[splittingSelName]->splitInfo);
        splittingSel = splits[splittingSelName];
        kernelSel = kernelNow;
      }
    }

    if (dipSel) {
      bool hasBranched = false;
      if ( event[dipSel->iRecoiler].isFinal())
           hasBranched = branch_FF(event, true, &splitInfoSel);
      else hasBranched = branch_FI(event, true, &splitInfoSel);
      if (!hasBranched) {
        dipSel  = 0;
        iDipSel =-1;
        pT2sel  = 0.;
        splitInfoSel.clear();
        splittingSel = 0;
      }
    }

  }

  alphaSorder = asOrderSave;
  pT2minMECs  = pT2minMECsSave;

  // Unable to produce splitting.
  if (dipSel == 0) return 0.;

  // Return nonvanishing value if found pT bigger than already found.
  return sqrt(pT2sel);

}

//--------------------------------------------------------------------------

double DireTimes::enhanceOverestimateFurther( string name, int, double tOld) {

  if (tOld < pT2minEnhance) return 1.;
  double enhance = splits[name]->getEnhanceFactor();
  if (enhance != 1.) splits[name]->setIsEnhanced(true);
  return enhance;

}

//--------------------------------------------------------------------------

double DireTimes::overheadFactorsMEC( const Event&, DireSplitInfo*, string) {
  return 1.;
}

//--------------------------------------------------------------------------

double DireTimes::overheadFactors( DireTimesEnd* dip, const Event& state, 
  string name, double, double tOld, double xOld) {

  double factor = 1.;
  double MARGIN = 1.;
  // For very low cut-offs, reduce headroom factor.
  if (tOld < pT2colCut*1.25) MARGIN = 1.; 
  factor *= MARGIN;
  double idRec       = state[dip->iRecoiler].id();
  int    iSysRec     = dip->systemRec;

  // Additional enhancement if PDFs vary significantly when increasing x.
  if (tOld > PT2MIN_PDF_IN_OVERESTIMATE && tOld > pT2colCut
    && !state[dip->iRecoiler].isFinal()
    && particleDataPtr->colType(state[dip->iRecoiler].id()) != 0) {

    BeamParticle* beam = NULL;
    if (beamAPtr != NULL || beamBPtr != NULL) {
      if (dip->isrType == 1 && beamAPtr != NULL) beam = beamAPtr;
      if (dip->isrType != 1 && beamBPtr != NULL) beam = beamBPtr;
    }

    if (beam != NULL) {

      double scale2      = max(tOld, pT2colCut);
      bool   inOld       = beam->insideBounds(xOld, scale2); 
      double xPDFOld     = getXPDF(idRec, xOld, scale2, iSysRec, beam);

      // Try to find largest PDF ratio for initial gluon at low scale (where 
      // small changes in x can have a very large numerical effect.
      if (idRec == 21 && scale2 < PT2_INCREASE_OVERESTIMATE) {
        double xPDFmother = xPDFOld;
        int NTSTEPS(3), NXSTEPS(3);
        for (int i=1; i <= NTSTEPS; ++i) {
          double tNew = pT2colCut + double(i)/double(NTSTEPS)*(scale2-pT2colCut);
          for (int j=1; j <= NXSTEPS; ++j) {
            double xNew = xOld + double(j)/double(NXSTEPS)*(0.999999-xOld);
            double xPDFnew = getXPDF(21, xNew, tNew, iSysRec, beam);
            if ( beam->insideBounds(xNew, tNew) )
              xPDFmother = max(xPDFmother, xPDFnew);
          }
        }
        if ( inOld && abs(xPDFOld) > tinypdf(xOld) && xPDFmother/xPDFOld > 1.)
          factor *= xPDFmother / xPDFOld;

      } else {
        double tNew1       = pT2colCut;
        double tNew2       = pT2colCut + 0.5 * ( scale2 - pT2colCut );
        double xNew1       = xOld;
        double xNew2       = xOld + 0.5 * ( 0.999999 - xOld );
        bool   inNew       =   beam->insideBounds(xNew1, tNew1)
                            || beam->insideBounds(xNew1, tNew2) 
                            || beam->insideBounds(xNew2, tNew1) 
                            || beam->insideBounds(xNew2, tNew2); 
        double xPDFNew1    = getXPDF(idRec, xNew1, tNew1, iSysRec, beam);
        double xPDFNew2    = getXPDF(idRec, xNew1, tNew2, iSysRec, beam);
        double xPDFNew3    = getXPDF(idRec, xNew2, tNew1, iSysRec, beam);
        double xPDFNew4    = getXPDF(idRec, xNew2, tNew2, iSysRec, beam);
        double PDFNew      = max( 1./xNew1 * max(xPDFNew1,xPDFNew2),
                                  1./xNew2 * max(xPDFNew3,xPDFNew4) );
        if ( inOld && inNew && xPDFOld > tinypdf(xOld)
          && abs((PDFNew)/(1./xOld*xPDFOld)) > 10)
          factor *= abs(PDFNew/(1./xOld*xPDFOld));

      }
    }

  } else if (tOld > PT2MIN_PDF_IN_OVERESTIMATE && tOld > pT2colCut
     && !state[dip->iRecoiler].isFinal()
     && particleDataPtr->isLepton(idRec) ) {

    BeamParticle* beam = NULL;
    if (beamAPtr != NULL || beamBPtr != NULL) {
      if (dip->isrType == 1 && beamAPtr != NULL) beam = beamAPtr;
      if (dip->isrType != 1 && beamBPtr != NULL) beam = beamBPtr;
    }

    if (beam != NULL) {

      double scale2      = tOld; //max(tOld, pT2colCut);
      double xPDFOld     = getXPDF(idRec, xOld, scale2, iSysRec, beam);

      double xMax = 1. - LEPTONXMIN*0.1;
      double xNew = xMax - 1./100*(xMax-xOld);
      double xPDFNew
        = max(getXPDF(idRec,xOld, scale2, iSysRec, beam),
              getXPDF(idRec,xNew, scale2, iSysRec, beam));
      factor *= xPDFNew/xPDFOld;
    }
  }

  if ( !state[dip->iRecoiler].isFinal()
    && max(tOld, pT2colCut) < PT2_INCREASE_OVERESTIMATE
    && ( name == "Dire_fsr_qcd_1->1&21" || name == "Dire_fsr_qcd_21->21&21a"
      || name == "Dire_fsr_qcd_21->1&1a")) factor *= 2.;

  if (!state[dip->iRecoiler].isFinal() && name.find("_qed_") != string::npos)
    factor *= 1.5;
  if (!state[dip->iRecoiler].isFinal() && name.find("_u1new_") != string::npos)
    factor *= 1.5;

  // Multiply dynamically adjusted overhead factor.
  if ( overhead.find(name) != overhead.end() ) factor *= overhead[name];

  return max(1.,factor);

}

//--------------------------------------------------------------------------

// Function to generate new user-defined overestimates to evolution.

void DireTimes::getNewOverestimates( DireTimesEnd* dip, const Event& state,
  double tOld, double /*tEnd*/, double xOld, double zMinAbs, double zMaxAbs,
  multimap<double,string> newOverestimates []) {

  double sum [3] = {0.,0.,0.};
  pair<int,int> iRadRec(make_pair(dip->iRadiator, dip->iRecoiler));

  // Loop over splitting names and get overestimates.
  for ( unordered_map<string,DireSplitting*>::iterator it = splits.begin();
    it != splits.end(); ++it ) {

    double zMinAbsNow = zMinAbs;
    double zMaxAbsNow = zMaxAbs;

    // Clear any information still stored in the splitting kernel.
    it->second->splitInfo.clear();
    it->second->setIsEnhanced(false);

    string name = it->first; 

    // Check if splitting should partake in evolution.
    bool allowed = it->second->useFastFunctions()
                 ? it->second->canRadiate(state,dip->iRadiator,dip->iRecoiler)
                 : it->second->canRadiate(state,iRadRec,bool_settings);

    // Skip if splitting is not allowed.
    if (!allowed) continue;

    // Check if dipole end can really radiate this particle.
    int * re = it->second->radAndEmtArr(state[dip->iRadiator].id(),
      dip->colType);
    if (re[0]==0 || re[1]==0) continue;

    int evType = it->second->typeEvolutionMeasure();

    for (int iEmtAft=1; iEmtAft < 3; ++iEmtAft) {
      int idEmtAft = re[iEmtAft];
      if (idEmtAft==0) break;
      if (it->second->is_qcd) {
        idEmtAft = abs(idEmtAft);
        if (idEmtAft<10) idEmtAft = 1;
      }
      if (find(dip->allowedEmissions.begin(), dip->allowedEmissions.end(),
        idEmtAft) == dip->allowedEmissions.end() ) allowed = false;
      // Disallow emissions below cut-off.
      if      (!it->second->is_qed && pT2cut(idEmtAft) > tOld) {
        allowed = false;
      } else if (it->second->is_qed) {
        if ( idEmtAft == 22
          && pT2cut(idEmtAft) > tOld)
          allowed = false;
        if ( state[dip->iRadiator].id() == 22
          && pT2cut(state[dip->iRadiator].id()) > tOld)
          allowed = false;
      } else {
        if ( particleDataPtr->spinType(idEmtAft) != 2
          && pT2cut(idEmtAft) > tOld)
          allowed = false;
        if ( particleDataPtr->spinType(state[dip->iRadiator].id()) != 2
          && pT2cut(state[dip->iRadiator].id()) > tOld)
          allowed = false;
      }
    }

    // Skip if splitting is not allowed.
    if (!allowed) continue;

    it->second->splitInfo.set_pT2Old  ( tOld );
    it->second->splitInfo.set_xBef    ( xOld );
    it->second->splitInfo.storeRadBef(state[dip->iRadiator]);
    it->second->splitInfo.storeRecBef(state[dip->iRecoiler]);
    it->second->splitInfo.storeRadRecBefPos(dip->iRadiator, dip->iRecoiler);

    // Discard below the cut-off for the splitting.
    if (!it->second->aboveCutoff( tOld, state[dip->iRadiator],
      state[dip->iRecoiler], dip->system, partonSystemsPtr)) continue;

    // Get kernel order.
    int order = kernelOrder;
    // Use simple kernels for showering secondary scatterings.
    bool hasInA = (partonSystemsPtr->getInA(dip->system) != 0);
    bool hasInB = (partonSystemsPtr->getInB(dip->system) != 0);
    if (dip->system != 0 && hasInA && hasInB) order = kernelOrderMPI;

    // Check if this is a hadron decay system.
    bool hasHadMother=false;
    int iPos = dip->iRadiator;
    while (state[iPos].mother1() > 0) {
      hasHadMother = (state[iPos].statusAbs() > 60);
      if (hasHadMother) break;
      iPos = state[iPos].mother1();
    }
    if (hasHadMother) order = kernelOrderMPI;

    if ( evType == 0 && state[dip->iRecoiler].isFinal()) {
      double kappaMin2 = it->second->tCutoff(state[dip->iRadiator],
        state[dip->iRecoiler], partonSystemsPtr) / dip->m2Dip;
      if (kappaMin2<0.) kappaMin2 = pow2(pTcolCutMin)/dip->m2Dip;
     zMinAbsNow = (it->second->nEmissions() == 1)
             ? 0.5*(1 - sqrt(1-4.*kappaMin2)) : 0.;
     zMaxAbsNow = min(0.5*(1 + sqrt(1-4.*kappaMin2)), 1-kappaMin2);
    }
    if (std::isnan(zMinAbsNow) || std::isnan(zMaxAbsNow)) continue;

    double wt = it->second->overestimateInt(zMinAbsNow, zMaxAbsNow, tOld,
                                           dip->m2Dip, order);

    // Adjust overestimate for non-QCD splittings.
    if (!it->second->is_qcd) {
      double cpl = it->second->coupling();
      double as    = alphaS2piOverestimate;
      if (cpl>as)
        as = alphaS.alphaS(infoPtr->eCM())*0.5/M_PI;

//cout << __LINE__ << " " << name << " " << evType << " " << cpl/as << endl;
      //if (cpl>as) as = alphaS2pi;
      //if (cpl>as) as = cpl;
//cout << cpl << " " << as << " " << alphaS.alphaS(infoPtr->eCM())*0.5/M_PI << endl;

//cout << __LINE__ << " " << name << " " << cpl/as << endl;

      if (evType == 0)
        wt *= cpl/as;
      else if (evType == 2)
        wt *= cpl/as;
      //if (evType == 0)
      //  wt *= it->second->coupling()/alphaS2piOverestimate;
      //else if (evType == 2)
      //  wt *= it->second->coupling()/alphaS2piOverestimate;
      else {
        double coupl = it->second->coupling();
        double mRes
          = particleDataPtr->m0(state[dip->iRadiator].id());
        double width
          = particleDataPtr->particleDataEntryPtr(
              state[dip->iRadiator].id())->resWidth(
                state[dip->iRadiator].id(),mRes);
        wt *= coupl/width;
      }
    }

    // Include artificial enhancements.
    wt *= overheadFactors(dip, state, name, dip->m2Dip, tOld, xOld);

    // Now add user-defined enhance factor.
    double enhanceFurther
      = enhanceOverestimateFurther(name, state[dip->iRadiator].id(), tOld);
    wt *= enhanceFurther;

    // Remember enhancement.
    if (enhanceFurther != 1.) it->second->setIsEnhanced(true);

    // Save this overestimate.
    // Do not include zeros (could lead to trouble with lower_bound?)
    if (wt != 0.) {
      // Bookkeep overestimate of virtuality-ordered splitting together with
      // pT-ordered splittings.
      if (evType==2) evType = 0;
      sum[evType+1] += abs(wt);
      newOverestimates[evType+1].insert(make_pair(sum[evType+1],name));
      //newOverestimates[1].insert(make_pair(sum,name));
    }
  }

}

//--------------------------------------------------------------------------

// Function to generate new user-defined overestimates to evolution.

void DireTimes::getNewSplitting( const Event& state, DireTimesEnd* dip,
  double tOld, double xOld, double t, double zMinAbs, double zMaxAbs,
  int idMother, string name, bool forceFixedAs, int typeEvolutionMeasure,
  int& idDaughter, int& idSister, double& z, double& wt,
  unordered_map<string,double>& full, double& over) {

  string pstype = (state[dip->iRecoiler].isFinal() ? "FF" : "FI" );
  // Pointer to splitting for easy/fast access. 
  DireSplitting* splitNow = splits[name];

  typeEvolutionMeasure = splitNow->typeEvolutionMeasure();

  splitNow->splitInfo.storeRadBef ( state[dip->iRadiator]);
  splitNow->splitInfo.storeRecBef ( state[dip->iRecoiler]);
  splitNow->splitInfo.storeRadRecBefPos(dip->iRadiator, dip->iRecoiler);

  // Return mother and sister ids.
  int * re = splitNow->radAndEmtArr(idMother, dip->colType);
  // Exit if final state after splitting is not well-defined.
  if (re[0]==0 || re[1]==0) { wt = over = 0.; full.clear(); return; }
  idDaughter = re[0];
  idSister   = re[1];
  int nEmissions = splitNow->nEmissions();

  /*int nfinal=0;
  for (int i=0; i < state.size(); ++i)
    if (state[i].isFinal()) nfinal++;
  if (nfinal>2 && (idDaughter != -idSister || abs(idDaughter) != 1) )
    { wt = over = 0.; full.clear(); return; }*/

  // Set flavours.
  int flavour = 0;
  if (idSister > 20) flavour = idSister;

  // Check if emission is below cut-off, and if so, reject.
  bool allowed = true;
  if (!splitNow->is_qed && pT2cut(idSister) > t) {
    allowed = false;
  } else if (splitNow->is_qed) {
    if ( idSister == 22
      && pT2cut(idSister) > t)
      allowed = false;
    if ( state[dip->iRadiator].id() == 22
      && pT2cut(state[dip->iRadiator].id()) > t)
      allowed = false;
  } else {
    if ( particleDataPtr->spinType(idSister) != 2
      && pT2cut(idSister) > t)
      allowed = false;
    if ( particleDataPtr->spinType(state[dip->iRadiator].id()) != 2
      && pT2cut(state[dip->iRadiator].id()) > t)
      allowed = false;
  }

  if (!allowed) { wt = over = 0.; full.clear(); return; }

  //double kappaMin2 = pow2(pTcolCutMin)/dip->m2Dip;
  double kappaMin2 = splitNow->tCutoff(state[dip->iRadiator],
    state[dip->iRecoiler], partonSystemsPtr) / dip->m2Dip;
  if (kappaMin2<0.) kappaMin2 = pow2(pTcolCutMin)/dip->m2Dip;
  if ( typeEvolutionMeasure==0 && state[dip->iRecoiler].isFinal()){
   zMinAbs = (nEmissions == 1) ? 0.5*(1 - sqrt(1-4.*kappaMin2)) : 0.;
   zMaxAbs = min(0.5*(1 + sqrt(1-4.*kappaMin2)), 1-kappaMin2);
  }
  if (std::isnan(zMinAbs) || std::isnan(zMaxAbs)) {
    wt = over = 0.; full.clear(); return;
  }

  // Return auxiliary variable, mother and sister ids.
  if (z<0.) z = splitNow->zSplit(zMinAbs, zMaxAbs, dip->m2Dip);

  // Hard cut-off on lepton energy fraction.
  if (splitNow->is(splittingsPtr->fsrQED_11_to_11_and_22_notPartial)
    && z > LEPTONZMAX) { wt = over = 0.; full.clear(); return; }

  // Discard below the cut-off for the splitting.
  if (!splitNow->aboveCutoff( t, state[dip->iRadiator], state[dip->iRecoiler],
    dip->system, partonSystemsPtr)) { wt = over = 0.; full.clear(); return; }

  // Flavour choice for g --> q qbar, or for q -> q'
  double RNflav = rndmPtr->flat();
  int sign = (idSister > 0) ? 1 : -1;
  if ( flavour == 0 && splitNow->is_dire && !splitNow->canUseForBranching()) {

    // Choose flavour for g --> qq~ splitting.
    if ( splitNow->is(splittingsPtr->fsrQCD_21_to_1_and_1a)
      || splitNow->is(splittingsPtr->fsrQCD_21_to_1_and_1b))
      idSister = sign*min(5, 1 + int(nGluonToQuark * RNflav));

    // Choose flavour for g --> qq~ splitting.
    if ( splitNow->is(splittingsPtr->fsrQCD_21_to_1_and_1_notPartial)) {
      idSister = sign*min(5, 1 + int(nGluonToQuark * RNflav));
      if (rndmPtr->flat() < 0.5) idSister *= -1;
    }

    // Choose flavour for q --> q' splitting.
    if (splitNow->is(splittingsPtr->fsrQCD_1_to_2_and_1_and_2)) {
      int index = int((2*nGluonToQuark - 2)*RNflav);
      vector<int> quarks;
      for (int i =-nGluonToQuark; i <=nGluonToQuark; ++i)
        if (abs(i) != state[dip->iRadiator].idAbs() && i != 0)
          quarks.push_back(i);
      idSister = quarks[index];
    }

    // Choose flavour for q --> qbar splitting.
    if (splitNow->is(splittingsPtr->fsrQCD_1_to_1_and_1_and_1))
      idSister = -idMother;
   
    flavour    = idSister;
    idDaughter = -idSister;

    // For 1->3 splittings, radiator keeps flavour.
    if (nEmissions == 2) idDaughter = state[dip->iRadiator].id();

  } else
    flavour    = idSister;

  // Store the flavour of the splitting.
  dip->flavour       = flavour;

  bool canUseSplitInfo = splitNow->canUseForBranching();
  if (canUseSplitInfo) {
    flavour    = re[1];
    idDaughter = re[0];
  }

  // Get particle masses.
  // Radiator before splitting.
  double m2Bef = particleDataPtr->isResonance(state[dip->iRadiator].id())
               ? getMass(state[dip->iRadiator].id(),3,
                         state[dip->iRadiator].mCalc())
               : (state[dip->iRadiator].idAbs() < 6
               || state[dip->iRadiator].id() == 21
               || state[dip->iRadiator].id() == 22)
               ? getMass(state[dip->iRadiator].id(),2)
               : getMass(state[dip->iRadiator].id(),1);
  if (abs(typeEvolutionMeasure)==1) m2Bef = 0.;

  // Radiator after splitting.
  double m2r   = particleDataPtr->isResonance(idDaughter)
                 && idDaughter == state[dip->iRadiator].id()
               ? getMass(idDaughter,3,state[dip->iRadiator].mCalc())
               : (abs(idDaughter) < 6 || idDaughter == 21 || idDaughter == 22)
               ? getMass(idDaughter,2)
               : getMass(idDaughter,1);
  // Recoiler. 
  double m2s = 0.0;
  int type   = (state[dip->iRecoiler].isFinal()) ? 1 : -1;
  if (type == 1) {
    m2s        = particleDataPtr->isResonance(state[dip->iRecoiler].id())
               ? getMass(state[dip->iRecoiler].id(),3,
                         state[dip->iRecoiler].mCalc())
               : (state[dip->iRecoiler].idAbs() < 6
               || state[dip->iRecoiler].id() == 21
               || state[dip->iRecoiler].id() == 22)
               ? getMass(state[dip->iRecoiler].id(),2)
               : getMass(state[dip->iRecoiler].id(),1);
  }
  // Emission.
  double m2e = (abs(flavour) < 6 || flavour == 21 || flavour == 22)
             ? getMass(flavour,2) : getMass(flavour,1);

  // Special case for resonance decay.
  if ( particleDataPtr->isResonance(idDaughter)
    && idDaughter != state[dip->iRadiator].id() ) {
    // Radiator after splitting.
    m2r = pow2(particleDataPtr->mSel(idDaughter));
    // Emission.
    if ( particleDataPtr->isResonance(flavour) ) {
      m2e = pow2(particleDataPtr->mSel(flavour));
    }
    if (particleDataPtr->isResonance(state[dip->iRadiator].id())
      && sqrt(m2Bef) < sqrt(m2r) + sqrt(m2e) )
      m2e = pow2( sqrt(m2Bef) - sqrt(m2r));
    type = 0;
  }

  // Upate type if this is a massive splitting.
  if (  type != 0
    && (m2Bef > TINYMASS || m2r > TINYMASS || m2s > TINYMASS || m2e > TINYMASS)) 
    type = type/abs(type)*2;

  // Recalculate the kinematicaly available dipole mass.
  int massSign = (type > -1) ? 1 : -1;
  // Dipole invariant mass.
  double q2 = ( state[dip->iRecoiler].p() 
              + massSign*state[dip->iRadiator].p() ).m2Calc();
  // Recalculate the kinematicaly available dipole mass.
  double Q2 = dip->m2Dip + massSign*(m2Bef - m2r - m2e);

  // Set kinematics mapping, as needed to check limits. 
  // 1 --> Dire
  // 2 --> Catani-Seymour
  int kinType = splitNow->kinMap();

  dip->z = z;
  dip->pT2 = t;
  // Already pick phi value here, since we may need to construct the
  // momenta to evaluate the splitting probability.
  dip->phi   = 2.*M_PI*rndmPtr->flat();

  // Remember masses.
  double m2a = getMass(-idSister,2); 
  double m2i = getMass( idSister,2); 
  double m2j = m2r;
  if (canUseSplitInfo) {
    m2a = getMass(re[0],2);
    // Note: m2i and m2j are swapped, since it is assumed 
    // that j is radiated first.
    m2i = getMass(re[1],2);
    if (re[2] != 0) {
      m2j = getMass(re[2],2);
      swap (m2i, m2j);
    }
  }

  dip->mass.clear();
  dip->idRadAft = 0;
  dip->idEmtAft = 0;
  splitNow->splitInfo.clearRadAft();
  splitNow->splitInfo.clearEmtAft();
  splitNow->splitInfo.clearEmtAft2();

  // Generate additional variables for 1->3 splitting.
  if ( nEmissions == 2 ) {
    dip->mass.push_back(m2a);
    dip->mass.push_back(m2i);
    dip->mass.push_back(m2j);
    dip->mass.push_back(m2s);
    // Consider endpoint projections.
    if (splitNow->allow_sai_endpoint_for_kinematics())
      splitNow->try_sai_endpoint();
    if (splitNow->allow_xa_endpoint_for_kinematics())
      splitNow->try_xa_endpoint();
    // Choose xa flat in [z, 1.0]
    if (!splitNow->is_xa_endpoint())  getNextZCollQCD( dip, dip->z, 1. ); 
    else                              dip->xa = 1.;
    // Choose sai.
    if (!splitNow->is_sai_endpoint()) getNextVirtQCD( dip, 0.0, dip->m2Dip); 
    else                              dip->sa1 = 0.;

    // Choose phi flat in [0, 2Pi]
    dip->phia1 = 2.*M_PI*rndmPtr->flat();
  }

  // Set correct variables for 1->3 splitting.
  vector <double> aux;
  if ( nEmissions == 2 ) {
    type       = (state[dip->iRecoiler].isFinal()) ? 2 : -2;
    aux.push_back( dip->m2Dip );
    if (type > 0) aux.push_back( (state[dip->iRadiator].p()
                                 +state[dip->iRecoiler].p()).m2Calc() );
    else          aux.push_back( (state[dip->iRadiator].p()
                                 -state[dip->iRecoiler].p()).m2Calc() );
    aux.push_back(dip->pT2);
    aux.push_back(dip->sa1);
    aux.push_back(dip->z);
    aux.push_back(dip->xa);
    aux.push_back(m2Bef);
    aux.push_back(m2a);
    aux.push_back(m2i);
    aux.push_back(m2j);
    aux.push_back(m2s);
  }

  // Note: m2i and m2j were swapped, since it is assumed 
  // that j is radiated first. For correct storage, swap back.
  if (canUseSplitInfo) swap (m2i, m2j);

  // Setup splitting information.
  double xBef = (type > 0) ? 0.0 : 2.*state[dip->iRecoiler].e()/state[0].m();
  splitNow->splitInfo.storeInfo(name, type, dip->system, dip->systemRec, 0,
    dip->iRadiator, dip->iRecoiler, state, 
    dip->flavour, idDaughter, nEmissions, Q2, dip->pT2, dip->pT2Old, 
    dip->z, dip->phi, m2Bef, m2s, (nEmissions == 1 ? m2r : m2a),
    (nEmissions == 1 ? m2e : m2i), dip->sa1, dip->xa, dip->phia1, m2j,
    xBef, -1.);
  splitNow->splitInfo.setSiblings(dip->iSiblings);
  if (canUseSplitInfo) {
    splitNow->splitInfo.setRadAft(re[0]);
    splitNow->splitInfo.setEmtAft(re[1]);
    if (nEmissions==2) splitNow->splitInfo.setEmtAft2(re[2]);
    splitNow->splitInfo.canUseForBranching(true);
  } else {
    splitNow->splitInfo.setRadAft(idDaughter);
    splitNow->splitInfo.setEmtAft(idSister);
    if (nEmissions==2) splitNow->splitInfo.setEmtAft2(-idSister);
  }

  // Check phase space limits.
  double zcheck(z), tcheck(t);
  if (name==testname && testps==pstype) direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << pstype << " " << name
  << " " << state[dip->iRecoiler].id() << " tevol=" << t
  << " z=" << z << " zcheck=" << zcheck << " xbj=" << xOld << endl;
  if (canUseSplitInfo) {
    zcheck = splitNow->getZDire(state[dip->iRadiator].isFinal(),
      state[dip->iRecoiler].isFinal(), z, t, Q2);
    tcheck = splitNow->getTDire(state[dip->iRadiator].isFinal(),
      state[dip->iRecoiler].isFinal(), z, t, Q2);
  }

  if (kinRels->FSRevolutionMode==1 && !state[dip->iRecoiler].isFinal()) {
    zcheck = kinRels->z_fi_dire_from_cs(z, t, Q2);
    tcheck = kinRels->t_fi_dire_from_cs(z, t, Q2);
  }

  if (name==testname && testps==pstype) direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << name << " " << state[dip->iRecoiler].id()
  << " tevol=" << t << " z=" << z << " zcheck=" << zcheck
  << " xbj=" << xOld << endl;

  if ( !inAllowedPhasespace( kinType, zcheck, tcheck, Q2, q2,
          xOld, type, m2Bef, m2r, m2s, m2e, aux, splitNow) )
    { wt = over = 0.; full.clear(); return; }

  // Get kernel order.
  int order = kernelOrder;
  // Use simple kernels for showering secondary scatterings.
  bool hasInA = (partonSystemsPtr->getInA(dip->system) != 0);
  bool hasInB = (partonSystemsPtr->getInB(dip->system) != 0);
  if (dip->system != 0 && hasInA && hasInB) order = kernelOrderMPI;

  // Check if this is a hadron decay system.
  bool hasHadMother=false;
  int iPos = dip->iRadiator;
  while (state[iPos].mother1() > 0) {
    hasHadMother = (state[iPos].statusAbs() > 60);
    if (hasHadMother) break;
    iPos = state[iPos].mother1();
  }
  if (hasHadMother) order = kernelOrderMPI;

  // Set splitting colors, if necessary.
  if (canUseSplitInfo) {
    vector< pair<int,int> > cols
      = splitNow->radAndEmtCols( dip->iRadiator, dip->colType, state);
    splitNow->splitInfo.setRadAft(re[0], cols[0].first, cols[0].second);
    splitNow->splitInfo.setEmtAft(re[1], cols[1].first, cols[1].second);
    if (nEmissions==2) splitNow->splitInfo.setEmtAft2(re[2], cols[2].first,
      cols[2].second);
  }

  dip->idRadAft = idDaughter;
  dip->idEmtAft = idSister;

  // Return overestimate.
  over        = splitNow->overestimateDiff(z, dip->m2Dip, order);
  // Adjust overestimate for non-QCD splittings.
  if (!splitNow->is_qcd) {
//cout << __LINE__ << " " << name << " " << typeEvolutionMeasure << " " << splitNow->coupling()/alphaS2piOverestimate  << " " << alphaS2piOverestimate << " " << alphasNow(t, renormMultFac, dip->system) << endl;
    double cpl = splitNow->coupling();
    double as  = alphaS2piOverestimate;
    //if (cpl>as) as = splitNow->coupling();
    //if (cpl>as) as = cpl;
    //if (cpl>as) as = alphaS2pi;
//cout << __LINE__ << " " << name << " " << cpl/as << endl;
//cout << __LINE__ << " " << forceFixedAs << " " << name << " " << cpl/as << endl;
    if (cpl>as)
      as = alphaS.alphaS(infoPtr->eCM())*0.5/M_PI;
    if (typeEvolutionMeasure == 0)
      over *= cpl/as;
    else if (typeEvolutionMeasure == 2)
      over *= cpl/as;
    //if      (typeEvolutionMeasure == 0)
    //  over *= splitNow->coupling()/alphaS2piOverestimate; 
    //else if (typeEvolutionMeasure == 2)
    //  over *= splitNow->coupling()/alphaS2piOverestimate; 
    else if (abs(typeEvolutionMeasure) == 1) {
      double coupl = splitNow->coupling();
      double mRes
        = particleDataPtr->m0(state[dip->iRadiator].id());
      double width
        = particleDataPtr->particleDataEntryPtr(
            state[dip->iRadiator].id())->resWidth(
              state[dip->iRadiator].id(),mRes);
      over *= coupl/width;
    }
  }

  if (name==testname && testps==pstype) direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << pstype << " " << name
  << " " << (state[dip->iRecoiler].isFinal() ? " FF " : " FI " )
  << " enter kernel calculation " << z << endl;

  // Get complete kernel.
  if (splitNow->calc( state, order) ) full = splitNow->getKernelVals();
  if (abs(full["base"]) < 1e-10*over) { wt = over = 0.; full.clear(); return; }

  // For small values of pT, recombine with Q2QG kernel to avoid large
  // numerical cancellations:
  // - Set Q2GQ kernel to zero, add to Q2QG
  // - Set G2GG2 kernel to zero, add to G2GG1
  // - Set G2QQ2 kernel to zero, add to G2QQ1
  if ( !state[dip->iRecoiler].isFinal()
    && max(tOld, pT2colCut) < pT2recombine ) {
    if ( splitNow->is(splittingsPtr->fsrQCD_1_to_21_and_1)
      || splitNow->is(splittingsPtr->fsrQCD_21_to_21_and_21b)
      || splitNow->is(splittingsPtr->fsrQCD_21_to_1_and_1b))
      for (unordered_map<string,double>::iterator it=full.begin(); it != full.end(); ++it) 
       it->second = 0.;
    //string name_recombine="";
    string name_recombine;
    if (splitNow->is(splittingsPtr->fsrQCD_1_to_1_and_21)) 
      name_recombine="Dire_fsr_qcd_1->21&1";
    if (splitNow->is(splittingsPtr->fsrQCD_21_to_21_and_21a))
      name_recombine="Dire_fsr_qcd_21->21&21b";
    if (splitNow->is(splittingsPtr->fsrQCD_21_to_1_and_1a))
      name_recombine="Dire_fsr_qcd_21->1&1b";
    // Recombine with other kernels.
    //if (name_recombine != "" && splits.find(name_recombine) != splits.end() ) {
    if (!name_recombine.empty() && splits.find(name_recombine) != splits.end() ) {
      splits[name_recombine]->splitInfo.storeRadBef(state[dip->iRadiator]);
      splits[name_recombine]->splitInfo.storeRecBef(state[dip->iRecoiler]);
      splits[name_recombine]->splitInfo.storeRadRecBefPos(dip->iRadiator, dip->iRecoiler);
      splits[name_recombine]->splitInfo.storeInfo(name_recombine, type,
        dip->system, dip->systemRec, 0, dip->iRadiator,
        dip->iRecoiler, state,
        dip->flavour, idDaughter, nEmissions, Q2, dip->pT2, dip->pT2Old, dip->z,
        dip->phi, m2Bef, m2s, (nEmissions == 1 ? m2r : m2a),
        (nEmissions == 1 ? m2e : m2i), dip->sa1, dip->xa, dip->phia1, m2r,
        xBef, -1.);
      splits[name_recombine]->splitInfo.setRadAft(idDaughter);
      splits[name_recombine]->splitInfo.setEmtAft(idSister);
      splits[name_recombine]->splitInfo.setSiblings(dip->iSiblings);

      // Calculate other kernel and add to previous result.
      unordered_map<string,double> full_recombine;
      if (splits[name_recombine]->calc( state, order) )
        full_recombine = splits[name_recombine]->getKernelVals();
      for ( unordered_map<string,double>::iterator it = full_recombine.begin();
        it != full_recombine.end(); ++it ) full[it->first] += it->second;
    }
  }

  // Reweight with coupling factor if necessary.
  double coupl = splitNow->coupling(dip->z, dip->pT2, Q2, -1.,
      make_pair(state[dip->iRadiator].id(), state[dip->iRadiator].isFinal()),
      make_pair(state[dip->iRecoiler].id(), state[dip->iRecoiler].isFinal()));
  // Retrieve argument of alphaS.
  double scale2 = splitNow->couplingScale2(dip->z, dip->pT2, Q2,
    make_pair (state[dip->iRadiator].id(), state[dip->iRadiator].isFinal()),
    make_pair (state[dip->iRecoiler].id(), state[dip->iRecoiler].isFinal()));
  if (scale2 < 0.) scale2 = dip->pT2;
  double talpha           = max(scale2, pT2colCut);
  double renormMultFacNow = renormMultFac;
  if (forceFixedAs) renormMultFacNow = 1.0;

  if (!splitNow->is_qcd && coupl > 0.) {
    double as = forceFixedAs ? alphaS2piOverestimate
              : alphasNow(talpha, renormMultFacNow, dip->system);
    if (typeEvolutionMeasure == 0 || typeEvolutionMeasure == 2)
      full["base"] *= coupl / as;
    else if (abs(typeEvolutionMeasure) == 1){
      double mRes
        = particleDataPtr->m0(state[dip->iRadiator].id());
      double width
        = particleDataPtr->particleDataEntryPtr(
            state[dip->iRadiator].id())->resWidth(
              state[dip->iRadiator].id(),mRes);
      full["base"] *= coupl/width;
    }

//cout << __LINE__ << " " << forceFixedAs << " " << name << " " << coupl/as << endl;
//cout << __LINE__ << " " << name << " " << coupl / as << " " << as << " " << alphaS2pi << endl;

    //if (name.find("qcd") == string::npos) {
      for ( unordered_map<string,double>::iterator it = full.begin();
        it != full.end(); ++it ) {
        if (it->first.find("base") != string::npos) continue;
        double cpl = splitNow->coupling(dip->z, dip->pT2, Q2, 
          ((dip->pT2 > pT2minVariations)
            ? settingsPtr->parm(it->first)*renormMultFac : -1.),
          make_pair(state[dip->iRadiator].id(),
                    state[dip->iRadiator].isFinal()),
          make_pair(state[dip->iRecoiler].id(),
                    state[dip->iRecoiler].isFinal()));
        it->second *= cpl / as;
      }
    //}
  }

  // Acceptance weight.
  wt          = full["base"]/over;

  // Divide out artificial enhancements.
  double headRoom = overheadFactors(dip, state, name, dip->m2Dip, tOld, xOld);
  wt   /= headRoom;
  over *= headRoom;

  // Ensure positive weight.
  wt = abs(wt);

}

//--------------------------------------------------------------------------

pair<bool, pair<double,double> >  DireTimes::getMEC ( const Event& state,
  DireSplitInfo* splitInfo) {

  double MECnum(1.0), MECden(1.0);
  bool hasME = weights->hasME(evtUtils->makeHardEvent(
    max(0,splitInfo->system), state, false));

  if (splittingSelName==testname) direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << splittingSelName << " " << hasME << endl;

  if (hasME) {

    direInfoPtr->message(1) << __FILE__ << " " << __func__
    << " calculate mec for branching " << splittingSelName
    //<< " " << (state[splitInfo->iRecAft].isFinal() ? " FF " : " FI " )
    << " at tEvol=" 
    << splitInfo->kinematics()->pT2
    << " z=" << splitInfo->kinematics()->z
    << endl;

    // Store previous mergingHooks setup.
    mergingHooksPtr->init();

    // For now, prefer construction of ordered histories.
    mergingHooksPtr->orderHistories(false);
    // For pp > h, allow cut on state, so that underlying processes
    // can be clustered to gg > h
    if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0)
      mergingHooksPtr->allowCutOnRecState(true);

    // Prepare process record for merging. If Pythia has already decayed
    // resonances used to define the hard process, remove resonance decay
    // products.
    Event newProcess( evtUtils->eventForMerging( 
      evtUtils->makeHardEvent(max(0,splitInfo->system), state, false), true));

    // Store candidates for the splitting.
    mergingHooksPtr->storeHardProcessCandidates( newProcess );

    // Calculate number of clustering steps
    int nSteps = mergingHooksPtr->getNumberOfClusteringSteps( newProcess, true);

    // Set dummy process scale.
    newProcess.scale(0.0);
    // Generate all histories
    DireHistory myHistory( nSteps, 0.0, newProcess, DireClustering(),
      mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
      NULL, splits.begin()->second->fsr, splits.begin()->second->isr, weights,
      coupSMPtr, true, true, false, 1.0, 1.0, 1.0, 1.0, 0);
    // Project histories onto desired branches, e.g. only ordered paths.
    myHistory.projectOntoDesiredHistories();

    if (!allowMECsBelowCutoff && !myHistory.allPathsAboveCutoff()) {
      MECnum = MECden = 1.;
    } else {
      MECnum = myHistory.MECnum;
      MECden = myHistory.MECden;
    }

    // Restore to previous mergingHooks setup.
    mergingHooksPtr->init();

  // Done.
  }

  if (abs(MECden) < 1e-15) direInfoPtr->message(1) 
    << scientific << setprecision(8) << __FILE__ //<< " " << __func__
    << " " << __LINE__ << " : Small MEC denominator="
    << MECden << " for numerator=" << MECnum << endl;
  if (abs(MECnum/MECden) > 1e2) direInfoPtr->message(1)
    << scientific << setprecision(8) << __FILE__ //<< " " << __func__
    << " " << __LINE__ << " : Large MEC. Denominator="
    << MECden << " Numerator=" << MECnum << " at pT="
    << sqrt(splitInfo->kinematics()->pT2) << " "
    << endl;

  return make_pair(hasME, make_pair(MECnum,MECden));

}

//--------------------------------------------------------------------------

bool DireTimes::applyMEC ( const Event& state, DireSplitInfo* splitInfo,
  int iRad, int iEmt, int iRec) {

  // Get value of ME correction.
  pair<bool, pair<double, double> > mec = getMEC ( state, splitInfo);
  bool hasME    = mec.first;
  double MECnum = mec.second.first;
  double MECden = mec.second.second;
  if (!hasME || (MECnum ==1. && MECden == 1.)) return false;
  // Remember O(alphaS^2) term and remove from list of variations.
  double kernel = kernelSel["base"];
  bool reject    = false;

  // Remember O(alphaS^2) term and remove from list of variations.
  double oas2    = 0.;
  if (kernelSel.find("base_order_as2") != kernelSel.end() ) {
    oas2 = kernelSel["base_order_as2"];
    kernelSel.erase(kernelSel.find("base_order_as2"));
  }
  double baseNew = ((kernel - oas2) * MECnum/MECden + oas2);

  string pstype = (state[iRec].isFinal() ? "FF" : "FI" );

#pragma omp critical
{
  cout << scientific << setprecision(6) << setw(20) << splittingSelName
  << " " << pstype << " pT2=:" << (state[iRad].p() + state[iEmt].p()).m2Calc()
  << ": z=:" << splitInfo->kinematics()->z << ": phi=:"
  << splitInfo->kinematics()->phi << ": mec=:" << MECnum/MECden
  << ":" << " menum=:" << MECnum << ": meden=:" << MECden << ":" << endl;
}

  if (hasME) {

    // Now check if the splitting should be vetoed/accepted given new kernel.
    double auxNew  = kernel;
    double overNew = kernel;

    // Ensure that accept probability is positive.
    if (baseNew/auxNew < 0.) auxNew *= -1.;
    //if (suppressLargeMECs)  while (baseNew/auxNew < 5e-2) auxNew /= 5.;
    // Reset overestimate if necessary.
    if (baseNew/auxNew > 1.) {
      //scaleMEOverheadFactor(splittingSelName, 3.);
      //double rescale = baseNew/auxNew * 1.15;
      double rescale = baseNew/auxNew * 1.5;
      auxNew *= rescale;
    }
    double wt = baseNew/auxNew;
    // New rejection weight.
    double wvNow = auxNew/overNew * (overNew - baseNew)
                                  / (auxNew  - baseNew);
    // New acceptance weight.
    double waNow = auxNew/overNew;

    if (wt < rndmPtr->flat()) {

      if (abs(wvNow) > 1.1) {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wvNow
        << "\t for kernel=" << baseNew << " overestimate=" << overNew
        << "\t aux. overestimate=" << auxNew << " at pT="
        << sqrt(splitInfo->kinematics()->pT2)
        <<  " for " << splittingSelName << endl;
      }

      // Loop through and reset weights.
      for (unordered_map<string,double>::iterator it= kernelSel.begin();
        it != kernelSel.end(); ++it) {
        // Get old accept weight.
        double waOld = weights->getAcceptWeight( splitInfo->kinematics()->pT2,
          it->first);
        // Remove previous acceptance weight and replace rejection weight.
        weights->eraseAcceptWeight(splitInfo->kinematics()->pT2, it->first);
        weights->resetRejectWeight(splitInfo->kinematics()->pT2, wvNow*waOld,
          it->first);
      }
      reject = true;
    } else {

      if (abs(waNow) > 1.1) {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large accept weight=" << waNow
        << "\t for kernel=" << baseNew << " overestimate=" << overNew
        << "\t aux. overestimate=" << auxNew << " at pT="
        << sqrt(splitInfo->kinematics()->pT2)
        << " for " << splittingSelName << endl;
      }

      // Loop through and reset weights.
      for (unordered_map<string,double>::iterator it= kernelSel.begin();
        it != kernelSel.end(); ++it) {
        // Get old accept weight.
        double waOld = weights->getAcceptWeight( splitInfo->kinematics()->pT2,
          it->first);
        // Remove previous reject weight and replace accept weight.
        weights->eraseRejectWeight(splitInfo->kinematics()->pT2, it->first);
        weights->resetAcceptWeight(splitInfo->kinematics()->pT2, waNow*waOld,
          it->first);
      }
    }

  }

  // Done.
  return reject;

}

//--------------------------------------------------------------------------

// Check if variables are in allowed phase space.
// Note that the vector of auxiliary inputs "aux" (needed to check the phase
// space of 1->3 splittings) has the following ordering:
// +2.pRadBef*pRecBef, (pRadBef +- pRecBef)^2, pT2, sa1, za, xa, m_{0,a12)^2,
// m_{0,a}^2, m_{0,1}^2, m_{0,2}^2, m_{0,b}^2

bool DireTimes::inAllowedPhasespace( int kinType, double z, double pT2,
  double m2dip, double q2, double xOld, int splitType, double m2RadBef,
  double m2r, double m2s, double m2e, vector<double> aux,
  DireSplitting* split) {

  double xIncoming = usePDF ? xOld : 0.;

  int evType = 0;
  if (split) {
    evType   = split->typeEvolutionMeasure();
  }

  string pstype = (splitType>0) ? "FF" : "FI";

  // Checks on input values.
  if ( z < 0. || z > 1. || pT2 < 0. || m2dip < 1e-5
    || xIncoming > 1.)                                 return false;
  if (std::isinf(z)         || std::isnan(z))          return false;
  if (std::isinf(pT2)       || std::isnan(pT2))        return false;
  if (std::isinf(xIncoming) || std::isnan(xIncoming))  return false;

  // Simple (massive) 1->2 decay.
  if (splitType == 0) {

    double zCS = z;
    double yCS = (m2RadBef - m2e - m2r)
               / (m2RadBef - m2e - m2r + q2 - m2RadBef - m2s);
    // Calculate derived variables.
    double sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2r+m2e);
    double zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
               * (zCS - m2s/gABC(q2,sij,m2s)
                       *(sij + m2r - m2e)/(q2-sij-m2s));
    double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2r - zbar*m2e; 
    if (kT2 < 0.0) return false;

  // splitType == 1 -> Massless FF
  } else if (splitType == 1) {

    // Calculate CS variables.
    double yCS = pT2/m2dip / (1.-z);
    double zCS = ( 1. - z - pT2/m2dip - pow2(1.-z) )
               / ( 1. - z - pT2/m2dip);

    // CS variables directly.
    if (kinType == 2) {
      zCS = z;
      yCS = pT2 / (m2dip*z*(1.-z)) ;
    } 

    // Note: For evType!=0, coverting to tDire before entering this function
    // ensures correct yCS and zCS definitions here.
    // changes for virtuality ordering
    if (abs(evType)==1) {
      double tEvol = split->splitInfo.kinematics()->pT2;
      m2RadBef = split->splitInfo.kinematics()->m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip - m2RadBef;
      double virt = (evType > 0 ? tEvol : pow2(2.*sqrt(m2RadBef)-sqrt(tEvol)));
      yCS = virt/m2;
      zCS = 1. - (1.-z)/(1.-yCS);
    }

    if (evType==2) { 
      double tEvol = split->splitInfo.kinematics()->pT2;
      double virt  = tEvol + m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip - m2RadBef;
      yCS = virt / m2;
      zCS = 1. - (1.-z)/(1.-yCS);
    }

    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < 0. || zCS > 1. || yCS < 0. || yCS > 1.) return false;

  // splitType == 2 -> Massive FF
  } else if (splitType == 2 && aux.size() == 0) {

    // Phase space limits - CS style.
    // Calculate CS variables.
    double yCS = pT2/m2dip / (1.-z);
    double zCS = ( 1. - z - pT2/m2dip - pow2(1.-z) )
               / ( 1. - z - pT2/m2dip);

    // Evolution in CS variables directly.
    if (kinType == 2) {
      zCS = z;
      yCS = pT2 / (m2dip*z*(1.-z)) ;
    }

    // changes for virtuality ordering
    if (abs(evType)==1) {
      double tEvol = split->splitInfo.kinematics()->pT2;
      m2RadBef = split->splitInfo.kinematics()->m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip - m2RadBef;
      double virt = (evType > 0 ? tEvol : pow2(2.*sqrt(m2RadBef)-sqrt(tEvol)));
      yCS = virt/m2;
      zCS = 1. - (1.-z)/(1.-yCS);
    }

    if (evType==2) { 
      double tEvol = split->splitInfo.kinematics()->pT2;
      double virt  = tEvol + m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip - m2RadBef;
      yCS = virt / m2;
      zCS = 1. - (1.-z)/(1.-yCS);
    }

    // Calculate derived variables.
    double sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2r+m2e);

    //if (evType!=0) {
    if (abs(evType)==1) {
      sij  = yCS * (q2 - m2RadBef - m2s) + (1.-yCS)*(m2r+m2e);
    }
    //if (evType==0 && idRadBef>1000) {
    if (evType==2) {
      sij  = yCS * (q2 - m2RadBef - m2s) + (1.-yCS)*(m2r+m2e);
    }

    double zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
                * (zCS - m2s/gABC(q2,sij,m2s)
                        *(sij + m2r - m2e)/(q2-sij-m2s));
    double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2r - zbar*m2e; 

    // Not possible to construct kinematics if kT2 < 0.0
    if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5) return false;

    // Get yCS-boundaries.
    double mu2Rad = m2r/q2; 
    double mu2Emt = m2e/q2; 
    double mu2Rec = m2s/q2; 
    double yCSminMassive = 2.*sqrt(mu2Rad)*sqrt(mu2Emt)
                         / ( 1 - mu2Rad - mu2Emt - mu2Rec);   
    double yCSmaxMassive = 1.
                         - 2.*sqrt(mu2Rec)*( 1 - sqrt(mu2Rec) )
                         / ( 1 - mu2Rad - mu2Emt - mu2Rec);

    // Forbidden emission if outside allowed y range for given pT2.
    if ( yCS < yCSminMassive || yCS > yCSmaxMassive) return false;

    // Get zCS-boundaries.
    double nu2Rad = m2r/m2dip; 
    double nu2Emt = m2e/m2dip; 
    double nu2Rec = m2s/m2dip; 
    double vijk   = pow2(1.-yCS) - 4.*(yCS + nu2Rad + nu2Emt)*nu2Rec;
    double viji   = pow2(yCS) - 4.*nu2Rad*nu2Emt;
    if (vijk < 0. || viji < 0.) return false;
    vijk          = sqrt(vijk) / (1-yCS);
    viji          = sqrt(viji) / (yCS + 2.*nu2Rad);
    double prefac = (m2dip*yCS + 2.*m2r) / (2.*m2dip*yCS + 2.*m2r + 2.*m2e);
    double zCSminMassive = ( 1 - vijk*viji) * prefac;
    double zCSmaxMassive = ( 1 + vijk*viji) * prefac;
    
    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < zCSminMassive || zCS > zCSmaxMassive) return false;

  // splitType == 2 -> Massive 1->3 FF
  } else if (splitType == 2 && aux.size() > 0) {

    // Not correctly set up!
    if ( int(aux.size()) < 11) return false;

    //double Q2     = aux[0];
    double q2_1   = aux[1];
    double t      = aux[2];
    double sai    = aux[3];
    double za     = aux[4];
    double xa     = aux[5];
    double m2aij  = aux[6];
    double m2a    = aux[7];
    double m2i    = aux[8];
    double m2j    = aux[9];
    double m2k    = aux[10];
    double m2ai   = sai + m2a + m2i;

    // Calculate CS variables from 1->3 variables
    double yCS = t / (q2_1 - m2ai - m2j - m2k) * xa / za;
    double zCS = za / (xa *(1. - yCS))
                * (q2_1 - m2aij - m2k) / (q2_1 - m2ai - m2j - m2k);

    // Calculate derived variables.
    double sij  = yCS * (q2_1 - m2k) + (1.-yCS)*(m2ai+m2j);
    double zbar = (q2_1-sij-m2k) / bABC(q2_1,sij,m2k)
                * (zCS - m2k/gABC(q2_1,sij,m2k)
                        *(sij + m2ai - m2j)/(q2_1-sij-m2k));
    double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2ai - zbar*m2j; 

    // Not possible to construct kinematics if kT2 < 0.0
    if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5) return false;
  
    // Get yCS-boundaries.
    double mu2Rad = m2ai/q2_1; 
    double mu2Emt = m2j/q2_1; 
    double mu2Rec = m2k/q2_1; 
    double yCSminMassive = 2.*sqrt(mu2Rad)*sqrt(mu2Emt)
                         / ( 1 - mu2Rad - mu2Emt - mu2Rec);   
    double yCSmaxMassive = 1.
                         - 2.*sqrt(mu2Rec)*( 1 - sqrt(mu2Rec) )
                         / ( 1 - mu2Rad - mu2Emt - mu2Rec);

    // Forbidden emission if outside allowed y range for given pT2.
    if ( yCS < yCSminMassive || yCS > yCSmaxMassive) return false;

    // Get zCS-boundaries.
    double nu2Rad = m2ai/(q2_1 - m2ai - m2j - m2k + m2aij + m2k); 
    double nu2Emt = m2j/(q2_1 - m2ai - m2j - m2k + m2aij + m2k); 
    double nu2Rec = m2k/(q2_1 - m2ai - m2j - m2k + m2aij + m2k); 
    double vijk   = pow2(1.-yCS) - 4.*(yCS + nu2Rad + nu2Emt)*nu2Rec;
    double viji   = pow2(yCS) - 4.*nu2Rad*nu2Emt;
    if (vijk < 0. || viji < 0.) return false;
    vijk          = sqrt(vijk) / (1-yCS);
    viji          = sqrt(viji) / (yCS + 2.*nu2Rad);
    double prefac = ((q2_1 - m2ai - m2j - m2k + m2aij + m2k)*yCS + 2.*m2ai)
                   / (2.*(q2_1 - m2ai - m2j - m2k + m2aij + m2k)*yCS
                    + 2.*m2ai + 2.*m2j);
    double zCSminMassive = ( 1 - vijk*viji) * prefac;
    double zCSmaxMassive = ( 1 + vijk*viji) * prefac;
    
    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < zCSminMassive || zCS > zCSmaxMassive) return false;

    // Calculate CS variables.
    double q2_2   = za/xa*(q2_1 - m2aij - m2k) + m2ai + m2k;
    double zCS_2  = xa; 
    double yCS_2  = (m2ai - m2a - m2i)
                  / (m2ai - m2a - m2i + q2_2 - m2ai - m2k); 

    // Calculate derived variables.
    sij  = yCS_2 * (q2_2 - m2k) + (1.-yCS_2)*(m2a+m2i);
    zbar = (q2_2-sij-m2k) / bABC(q2_2,sij,m2k)
               * (zCS_2 - m2k/gABC(q2_2,sij,m2k)
                       *(sij + m2a - m2i)/(q2_2-sij-m2k));
    kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2a - zbar*m2i; 

    if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5) return false;

  // Extremely conservative technical cut-off on z for final-final splittings. 
  } else if (splitType == 3) {

    // pT2 can't be larger than the invariant mass of the dipole.
    if (pT2 > m2dip) return false;

    double kappa2 = pow2(pTcolCutMin/10.)
                  / pow2(0.5*(beamAPtr->e() + beamBPtr->e()));
    // Minimal cut on energy fraction for final-final.
    double yCS =  kappa2 / (1.-z);
    double zCS = ( 1. - z - kappa2 - pow2(1.-z) )
               / ( 1. - z - kappa2);
    if ( zCS < 0. || zCS > 1. || yCS < 0. || yCS > 1.) return false;

  // splitType ==-1 -> Massless FI
  } else if (splitType ==-1) {

    // Calculate CS variables.
    double kappa2 =  pT2/m2dip;
    double zCS = z;
    double xCS = 1 - kappa2/(1.-z);

    // CS variables directly.
    if (kinType == 2) {
      zCS = z;
      xCS = m2dip*zCS*(1.-zCS) / ( pT2 + m2dip*zCS*(1.-zCS) ) ;
    } 

    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < 0. || zCS > 1. || xCS < xIncoming || xCS > 1.) return false;

  // splitType ==-2 -> Massive FI
  } else if (splitType == -2 && aux.size() == 0) {

    // Phase space limits - CS style
    // Calculate CS variables.
    double kappa2 =  pT2/m2dip;
    double zCS = z;
    double xCS = 1 - kappa2/(1.-z);

    // CS variables directly.
    if (kinType == 2) {
      zCS = z;
      xCS = m2dip*zCS*(1.-zCS) / ( pT2 + m2dip*zCS*(1.-zCS) ) ;
    } 

    // changes for virtuality ordering
    if (abs(evType)==1) {
      double tEvol = split->splitInfo.kinematics()->pT2;
      m2RadBef = split->splitInfo.kinematics()->m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip + m2RadBef;
      double virt = (evType > 0
                  ? tEvol : pow2(2.*sqrt(m2RadBef)-sqrt(tEvol)) );
      xCS = m2/(m2+virt);
    }

    if (evType==2) { 
      double tEvol = split->splitInfo.kinematics()->pT2;
      m2RadBef = split->splitInfo.kinematics()->m2RadBef;
      double m2    = split->splitInfo.kinematics()->m2Dip + m2RadBef;
      double virt = tEvol + m2RadBef;
      xCS = m2 / (m2 + virt);
    }

    // Get xCS-boundaries.
    double xCDST = xCS / m2dip * (m2dip + m2RadBef-m2r-m2e);
    double pijpa_tilde = m2dip - m2r - m2e + m2RadBef;
    double pijpa     = pijpa_tilde/xCDST;
    double mu2RadBef = m2RadBef/pijpa;
    double muRad     = sqrt(m2r/pijpa);
    double muEmt     = sqrt(m2e/pijpa);
    double xCSmaxMassive = 1. + mu2RadBef - pow2(muRad + muEmt);

    // Forbidden emission if outside allowed x range for given pT2.
    if ( xCDST < xIncoming || xCDST > xCSmaxMassive) return false;

    // Get zCS-boundaries.
    double nu2Rad = m2r/m2dip; 
    double nu2Emt = m2e/m2dip; 
    double viji   = pow2(1.-xCS) - 4. * xCS*nu2Rad * xCS*nu2Emt; 
    if (viji < 0.) return false;
    viji   = sqrt( viji ) / (1.-xCS+2.*nu2Rad*xCS); 
    double vijk   = 1.; 
    double prefac = 0.5 * ( 1.-xCS + 2.*xCS*nu2Rad )
                  / ( 1.-xCS + xCS*nu2Rad + xCS*nu2Emt);
    double zCSminMassive = prefac * ( 1. - viji*vijk );
    double zCSmaxMassive = prefac * ( 1. + viji*vijk );

    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < zCSminMassive || zCS > zCSmaxMassive) return false;

  // splitType ==-2 -> Massive 1->3 FI
  } else if (splitType == -2 && aux.size() > 0) {

    // Not correctly set up!
    if ( int(aux.size()) < 11) return false;

    //double Q2     = aux[0];
    double q2_1   = aux[1];
    double t      = aux[2];
    double sai    = aux[3];
    double za     = aux[4];
    double xa     = aux[5];
    double m2aij  = aux[6];
    double m2a    = aux[7];
    double m2i    = aux[8];
    double m2j    = aux[9];
    double m2k    = aux[10];
    double m2ai   = sai + m2a + m2i;

    swap(m2ai,m2j);

    // Calculate CS variables from 1->3 variables
    double zCS = za / xa;
    double xCS = (q2_1 - m2ai - m2j - m2k)
               / (q2_1 - m2ai - m2j - m2k - t * xa/za );

    // Get xCS-boundaries.
    double xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2_1-m2ai-m2j-m2k) );

    //double pijpa_tilde = Q2 - m2j - m2ai + m2aij;
    double pijpa_tilde = -q2_1 + m2aij + m2k;
    double pijpa     = pijpa_tilde/xCDST;
    double mu2RadBef = m2aij/pijpa;
    double muRad     = sqrt(m2j/pijpa);
    double muEmt     = sqrt(m2ai/pijpa);
    double xCSmaxMassive = 1. + mu2RadBef - pow2(muRad + muEmt);

    // Forbidden emission if outside allowed x range for given pT2.
    if ( xCDST < xIncoming || xCDST > xCSmaxMassive) return false;

    // Get zCS-boundaries.
    double root = pow2(1. - xCDST + mu2RadBef - muRad*muRad - muEmt*muEmt)
      - 4.*pow2(muRad*muEmt);
    if (root < 0.) return false;
    double zCSminMassive = (1. - xCDST + mu2RadBef + muRad*muRad - muEmt*muEmt
      - sqrt(root)) / ( 2.*(1. - xCDST + mu2RadBef) );
    double zCSmaxMassive = (1. - xCDST + mu2RadBef + muRad*muRad - muEmt*muEmt
      + sqrt(root)) / ( 2.*(1. - xCDST + mu2RadBef) );

    // Forbidden emission if outside allowed z range for given pT2.
    if ( zCS < zCSminMassive || zCS > zCSmaxMassive) return false;

    // Check validity of second, FF-like step.
    swap(m2ai,m2j);

    // Calculate CS variables.
    double q2_2 = m2ai + m2k - za/xa * ( q2_1 - m2k - m2ai - m2j - t*xa/za);
    double yCS  = (m2ai - m2a - m2i) / (m2ai - m2a - m2i + q2_2 - m2ai - m2k);
    zCS         = xa;
    // Calculate derived variables.
    double sij  = yCS * (q2_2 - m2k) + (1.-yCS)*(m2a+m2i);
    double zbar = (q2_2-sij-m2k) / bABC(q2_2,sij,m2k)
                * (zCS - m2k/gABC(q2_2,sij,m2k)
                       *(sij + m2a - m2i)/(q2_2-sij-m2k));
    double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2a - zbar*m2i; 

    // Not possible to construct second step if kT2 < 0.0
    if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5) return false;

  // Extremely conservative technical z-cut-off for final-initial splittings. 
  } else if (splitType ==-3) {

    // pT2 can't be larger than the invariant mass of the dipole.
    if (pT2 > m2dip) return false;

    double kappa2 = pow2(pTcolCutMin/10.)
                  / pow2(0.5*(beamAPtr->e() + beamBPtr->e()));
    // Minimal cut on energy fraction for final-initial.
    double zCS = z;
    double xCS = 1 - kappa2/(1.-z);

    if ( zCS < 0. || zCS > 1. || xCS < xIncoming/1000. || xCS > 1.) return false;

  }

  return true;

}

//--------------------------------------------------------------------------

// Function to add user-defined overestimates to old overestimate.

void DireTimes::addNewOverestimates(
  multimap<double,string> newOverestimates [],
  double oldOverestimate []) {

  // No other tricks necessary at the moment.
  if (!newOverestimates[0].empty())
    oldOverestimate[0] += newOverestimates[0].rbegin()->first;
  if (!newOverestimates[1].empty())
    oldOverestimate[1] += newOverestimates[1].rbegin()->first;
  if (!newOverestimates[2].empty())
    oldOverestimate[2] += newOverestimates[2].rbegin()->first;

  // Done.

}

//--------------------------------------------------------------------------

// Function to attach the correct alphaS weights to the kernels.

void DireTimes::alphasReweight(double, double talpha, int iSys,
  bool forceFixedAs, double& weight, double& fullWeight, double& overWeight,
  double renormMultFacNow, double numeratorMultFac) {

  if (forceFixedAs) renormMultFacNow = 1.0;
  talpha = max(talpha, pT2colCut);

  double scale       = talpha*renormMultFacNow;

  // Save-guard against scales below shower cut-off
  scale = max(scale, pT2colCut);

  // Get current alphaS value.
  double asPT2piCorr
    = alphasNow(talpha*numeratorMultFac, renormMultFacNow, iSys);

  // Begin with multiplying alphaS to overestimate.
  double asOver = 1.;
  if (usePDFalphas)        asOver = alphaS2piOverestimate;
  else if (alphaSorder==0) asOver = alphaS2pi;
  else                     asOver = alphaS.alphaS(scale) / (2.*M_PI);
  // Multiply alphaS to full splitting kernel.
  double asFull = 1.;
  if (alphaSorder == 0)    asFull = alphaS2pi; 
  else                     asFull = asPT2piCorr;

  fullWeight *= asFull;
  overWeight *= asOver;
  weight     *= asFull/asOver;

  // Done.

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end in pT2.

void DireTimes::pT2nextQCD(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  if (event[dip.iRecoiler].isFinal())
    pT2nextQCD_FF(pT2begDip, pT2sel, dip, event, pT2endForce,
    pT2freeze, forceBranching);
  else
    //pT2nextQCD_FI(pT2begDip, pT2sel, dip, event, pT2endForce, pT2freeze,
    //forceBranching);
    pT2nextQCD_FI_test(pT2begDip, pT2sel, dip, event, pT2endForce,
    pT2freeze, forceBranching);

  // Clear enhance information still stored in the splitting kernel.
  for ( unordered_map<string,DireSplitting*>::iterator it = splits.begin();
    it != splits.end(); ++it )
    it->second->setIsEnhanced(false);
  for ( unordered_map<string,DireSplitting*>::iterator it = splits.begin();
    it != splits.end(); ++it )
    it->second->unsetForceSplitting();

  // Done.
  return;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end in pT2.

void DireTimes::tNextDecay(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  if (event[dip.iRecoiler].isFinal())
    tNextDecay_FF(pT2begDip, pT2sel, dip, event, pT2endForce,
    pT2freeze, forceBranching);
  else
    tNextDecay_FI(pT2begDip, pT2sel, dip, event, pT2endForce,
    pT2freeze, forceBranching);

  // Clear enhance information still stored in the splitting kernel.
  for ( unordered_map<string,DireSplitting*>::iterator it = splits.begin();
    it != splits.end(); ++it )
    it->second->setIsEnhanced(false);
  for ( unordered_map<string,DireSplitting*>::iterator it = splits.begin();
    it != splits.end(); ++it )
    it->second->unsetForceSplitting();

  // Done.
  return;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end.

bool DireTimes::pT2nextQCD_FF(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, const Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  // Lower cut for evolution. Return if no evolution range.
  double pT2endDip = max( pT2sel, pT2cutMin(&dip));
  if (pT2endForce >= 0.) pT2endDip = pT2endForce;
  if (pT2begDip < pT2endDip) return false;

  // Variables used inside evolution loop. (Mainly dummy start values.)
  dip.pT2              = pT2begDip;
  double zMinAbs       = 0.0;
  double zMaxAbs       = 1.0;
  double teval         = pT2begDip;
  double wt            = 0.;
  bool   mustFindRange = true;

  // Check if this is a resonance that should be branched in another 
  // evolution sequence.
  int idRadiator  = event[dip.iRadiator].id();
  double m2RadBef = pow2(particleDataPtr->m0(idRadiator));
  bool isRes      = particleDataPtr->isResonance(idRadiator);
  double tDiscard = -1.;
  for (auto w : evolutionWindows) 
    if ( isRes && w.isResonant && w.iWindow != iWindowNow
      && find(w.evolvingIds.begin(), w.evolvingIds.end(),idRadiator)
         != w.evolvingIds.end()) { tDiscard = max(tDiscard,w.tMax); }

  multimap<double,string> newOverestimates [3];
  double overestimateSum [3];

  unordered_map<string,double> fullWeightsNow;
  int    nContinue(0), nContinueMax(10000);
  double fullWeightNow(0.), overWeightNow(0.), auxWeightNow(0.), daux(0.);

  int iSysRad          = partonSystemsPtr->getSystemOf(dip.iRadiator,true);
  bool hasIn           = partonSystemsPtr->hasInAB(iSysRad);
  bool doVariationsNow = doVariations && (iSysRad<=nSysVar || !hasIn);

  // Begin evolution loop towards smaller pT values.
  do {

    wt          = 0.;
    double tnow = (!forceBranching) ? dip.pT2 : pT2begDip;
    // Reset emission properties.
    double zsave = dip.z;
    dip.z        = -1.0;
    dip.phi      = -1.0;
    dip.sa1      =  0.0;
    dip.xa       = -1.0;
    dip.phia1    = -1.0;
    dip.idRadAft = 0;
    dip.idEmtAft = 0;
    dip.mass.clear();

    // Force exit if non-Sudakov style forced branching is stuck.
    if (forceBranching && nContinue >= nContinueMax) {
      wt = 0.0; dip.pT2 = tnow = 0.;
      break;
    }

    // Update event weight after one step. 
    if ( fullWeightNow != 0. && overWeightNow != 0. ) {

      //double enhanceFurther
      //  = enhanceOverestimateFurther(splittingNowName, idRadiator, teval);
      //if (tnow < teval) enhanceFurther = 1.;
      //double enhanceFurther = splittingNowName != ""
      double enhanceFurther = !splittingNowName.empty()
        && splits[splittingNowName]->isEnhanced()
        ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

      if (doTrialNow) enhanceFurther = 1.;
      kernelNow = fullWeightsNow;
      auxNow    = auxWeightNow;
      overNow   = overWeightNow;
      boostNow  = enhanceFurther;
      for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
        it != fullWeightsNow.end(); ++it ) {

        // No weight bookkeeping for non-variation components of kernel vector. 
        if (it->first == "base_order_as2") continue;

        double wv = auxWeightNow/overWeightNow
                 * (overWeightNow- it->second/enhanceFurther)
                 / (auxWeightNow - fullWeightNow);
        if (abs(wv) > 1.1 && it->first == "base") {
        direInfoPtr->message(1)
        << scientific << setprecision(8) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wv
        << "\t for " << it->first << " kernel=" << it->second
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow) << " z=" << zsave << " m2dip=" << dip.m2Dip
        <<  " for " << splittingNowName << " " << it->first
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
        }
        rejectProbability[it->first].insert( make_pair(tnow,wv));
      }
    }

    splittingNowName.clear();
    fullWeightsNow.clear();
    fullWeightNow = overWeightNow = auxWeightNow = 0.;

    if (mustFindRange) {

      newOverestimates[0].clear();
      newOverestimates[1].clear();
      newOverestimates[2].clear();
      teval       = tnow;
      overestimateSum[0] = 0.;
      overestimateSum[1] = 0.;
      overestimateSum[2] = 0.;

      // Calculate and add user-defined overestimates.
      getNewOverestimates( &dip, event, tnow, pT2endDip, 1., zMinAbs, zMaxAbs,
        newOverestimates);
      addNewOverestimates(newOverestimates, overestimateSum);

      // Store pT at which overestimate has been evaluated. 
      dip.pT2Old = teval;

      // Initialization done for current range.
      mustFindRange = false;

    }

    if (overestimateSum[1] < TINYOVERESTIMATE) { dip.pT2 = 0.0; return false; }
    if (newOverestimates[1].empty())       { dip.pT2 = 0.0; return false; }

    // Try user-defined splittings first.
    double R = overestimateSum[1]*rndmPtr->flat();
    // Pick splitting.
    if (newOverestimates[1].lower_bound(R) == newOverestimates[1].end())
      splittingNowName = newOverestimates[1].rbegin()->second;
    else
      splittingNowName = newOverestimates[1].lower_bound(R)->second;

    // Generate next evolution scale.
    bool forceFixedAs = (tnow <= pT2colCut)
                     //|| !splits[splittingNowName]->is_qcd
                     || (event[dip.iRadiator].colType() == 0);
    tnow  = getNextTQCD( &dip, overestimateSum[1], tnow, pT2endDip, pT2freeze,
      (forceBranching ? -1 : 1), forceFixedAs);
    if (tnow < 0.) { 
      wt = 0.0; dip.pT2 = tnow = 0.;
      //double R0 = overestimateSum[1]*rndmPtr->flat();
      //if (!newOverestimates[1].empty()) {
      //  if (newOverestimates[1].lower_bound(R0) == newOverestimates[1].end())
      //    splittingNowName = newOverestimates[1].rbegin()->second;
      //  else
      //    splittingNowName = newOverestimates[1].lower_bound(R0)->second;
      //}
      break;
    }

    wt = 0.0;
    dip.pT2      = tnow;

    // Abort evolution if below cutoff scale, or below another branching.
    if ( tnow < pT2endDip ) { dip.pT2 = tnow = wt = 0.; break; }

    // Abort evolution if fallen below cut-off on resonance decay. 
    if ( tnow + m2RadBef < tDiscard ) { dip.pT2 = tnow = wt = 0.; break; }

    if ( teval > pT2colCut && tnow < pT2colCut
      && !splits[splittingNowName]->is_qcd) {
      mustFindRange = true;
      dip.pT2 = tnow = pT2colCut; wt = 0.;
      continue;
    }

    // Try user-defined splittings first.
    //double R = overestimateSum[1]*rndmPtr->flat();
    double z = -1.;
    int idDaughter, idSister;
    idDaughter = idSister = 0;
    if (!newOverestimates[1].empty()) {

      //// Pick splitting.
      //if (newOverestimates[1].lower_bound(R) == newOverestimates[1].end())
      //  splittingNowName = newOverestimates[1].rbegin()->second;
      //else
      //  splittingNowName = newOverestimates[1].lower_bound(R)->second;

      // Generate z value and calculate splitting probability.
      getNewSplitting( event, &dip, teval, 0., tnow, zMinAbs,
        zMaxAbs, idRadiator, splittingNowName, forceFixedAs, 0,
        idDaughter, idSister, z, wt, fullWeightsNow, overWeightNow);

      dip.z      = z;
    }

    // Done for vanishing accept probability.
    if ( wt == 0. || z < 0.) {
      //mustFindRange = true;
      if (tDiscard>0.) mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    fullWeightNow = fullWeightsNow["base"];

    // Get particle masses.
    // Radiator before splitting.
    double m2Bef = particleDataPtr->isResonance(event[dip.iRadiator].id())
                 ? getMass(event[dip.iRadiator].id(),3,
                           event[dip.iRadiator].mCalc())
                 : (abs(event[dip.iRadiator].id()) < 6
                     || event[dip.iRadiator].id() == 21
                     || event[dip.iRadiator].id() == 22)
                 ? getMass(event[dip.iRadiator].id(),2)
                 : getMass(event[dip.iRadiator].id(),1);
    // Radiator after splitting.
    double m2r   = particleDataPtr->isResonance(idDaughter)
                   && idDaughter == event[dip.iRadiator].id()
                 ? getMass(idDaughter,3,event[dip.iRadiator].mCalc())
                 : (abs(idDaughter) < 6 || idDaughter == 21
                     || idDaughter == 22)
                 ? getMass(idDaughter,2)
                 : getMass(idDaughter,1);
    // Recoiler. 
    double m2s   = particleDataPtr->isResonance(event[dip.iRecoiler].id())
                 ? getMass(event[dip.iRecoiler].id(),3,
                           event[dip.iRecoiler].mCalc())
                 : (event[dip.iRecoiler].idAbs() < 6
                 || event[dip.iRecoiler].id() == 21
                 || event[dip.iRecoiler].id() == 22)
                 ? getMass(event[dip.iRecoiler].id(),2)
                 : getMass(event[dip.iRecoiler].id(),1);
    // Emission.
    double m2e = (abs(dip.flavour) < 6 || dip.flavour == 21
                   || dip.flavour == 22)
               ? getMass(dip.flavour,2) : getMass(dip.flavour,1);

    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    if (canUseSplitInfo) {
      m2r = splits[splittingNowName]->splitInfo.kinematics()->m2RadAft;
      m2e = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft;
    }
    int nEmissions = splits[splittingNowName]->nEmissions();

    // Recalculate the kinematicaly available dipole mass.
    double Q2 = dip.m2Dip + m2Bef - m2r - m2e;
    double q2 = (event[dip.iRadiator].p() +event[dip.iRecoiler].p()).m2Calc();

    // Discard this 1->3 splitting if the pT has fallen below mEmission (since
    // such splittings would not be included in the virtual corrections to the
    // 1->2 kernels. Note that the threshold is pT>mEmission,since alphaS is
    // evaluated at pT, not virtuality sa1).
    if ( nEmissions == 2
      && ( (abs(dip.flavour) == 4 && tnow < m2cPhys)
        || (abs(dip.flavour) == 5 && tnow < m2bPhys))) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Pick remaining variables for 1->3 splitting.
    double m2aij(m2Bef), m2a(m2e), m2i(m2e), m2j(m2r), m2k(m2s);
    if (canUseSplitInfo)
      m2j = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft2;

    double jacobian(1.);
    if (canUseSplitInfo) {
      jacobian = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
    } else {
      // Calculate CS variables and scaled masses.
      double yCS = tnow/Q2 / (1. - z);
      double mu2RadBef = m2Bef/ q2;
      double mu2Rad    = m2r/ q2;
      double mu2Rec    = m2s/ q2;
      double mu2Emt    = m2e/ q2;
      // Calculate Jacobian.
      double jac1 = ( 1. - mu2Rad - mu2Rec - mu2Emt)
                  / sqrt(lABC(1.,mu2RadBef,mu2Rec));
      double jac2 = 1. + ( mu2Rad + mu2Emt - mu2RadBef)
                        /( yCS*(1. - mu2Rad - mu2Rec - mu2Emt));

      // Jacobian for 1->3 splittings, in CS variables.
      if (nEmissions == 2) {
        jac1 = jac2 = 1.;
        double sai   = dip.sa1;
        double m2ai  = sai + m2a + m2i;
        // Jacobian for competing steps, i.e. applied to over-all splitting rate.
        jac1 = (q2 - m2aij - m2k) / sqrt( lABC(q2, m2aij, m2k) );
        // Additional jacobian for non-competing steps.
        double m2aik = (dip.sa1 + m2a + m2i) + m2k
                     +  dip.z/dip.xa * (q2 - m2Bef - m2k);
        jac1 *= (m2aik - m2ai - m2k) / sqrt( lABC(m2aik, m2ai, m2k) );
        // Additional factor from massive propagator.
        jac2 = 1 + (m2ai + m2j - m2aij) / (dip.pT2*dip.xa/dip.z);
      }
      jacobian = jac1/jac2;
    }

    // Multiply with Jacobian.
    fullWeightNow *= jacobian;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= jacobian;

    // Before generating kinematics: Reset sai if the kernel fell on an
    // endpoint contribution.
    if ( nEmissions == 2
      && splits[splittingNowName]->splitInfo.kinematics()->sai == 0.)
        dip.sa1 = 0.;

    if (fullWeightNow == 0. ) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Retrieve argument of alphaS.
    double scale2 =  splits[splittingNowName]->couplingScale2 ( z, tnow, Q2,
      make_pair (event[dip.iRadiator].id(), event[dip.iRadiator].isFinal()),
      make_pair (event[dip.iRecoiler].id(), event[dip.iRecoiler].isFinal()));
    if (scale2 < 0.) scale2 = tnow;
//double talpha = 4. * max(scale2, pT2colCut);
    double talpha = max(scale2, pT2colCut);

    double extraFac = 4.;

    // Reweight to match PDF alpha_s, including corrective terms for
    // renormalisation scale variation.
    alphasReweight( tnow, talpha, dip.system, forceFixedAs, wt, fullWeightNow,
      overWeightNow, renormMultFac, extraFac);
    auxWeightNow   = overWeightNow;

    // Create muR-variations.
    double asw = 1.;
    alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
      renormMultFac, extraFac);
    fullWeightsNow["base"] *= asw;
    if (fullWeightsNow.find("base_order_as2") != fullWeightsNow.end())
      fullWeightsNow["base_order_as2"] *= asw;
    if (doVariationsNow && splittingNowName.find("qcd") != string::npos) {
      if (settingsPtr->parm("Variations:muRfsrDown") != 1.) {
        asw = 1.;
        alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
          (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrDown")
          : renormMultFac, extraFac);
        fullWeightsNow["Variations:muRfsrDown"] *= asw;
      }
      if (settingsPtr->parm("Variations:muRfsrUp")   != 1.) {
        asw = 1.;
        alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
          (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrUp")
          : renormMultFac, extraFac);
        fullWeightsNow["Variations:muRfsrUp"] *= asw;
      }
    } else {
      fullWeightsNow["Variations:muRfsrUp"]   *= asw;
      fullWeightsNow["Variations:muRfsrDown"] *= asw;
    }

    if (splits[splittingNowName]->giveUpAndForceSplitting()) {wt=1.; auxWeightNow=overWeightNow; break;}

    // Ensure that accept probability is positive.
    if (fullWeightNow < 0.) {
      direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Negative splitting kernel="
        << fullWeightNow
        << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
        << " and z=" << z << endl;
      auxWeightNow *= -1.;
    }

    // Reset overestimate if necessary.
    if (fullWeightNow > 0. && fullWeightNow/auxWeightNow > 1e0) {
      direInfoPtr->message(1)
        << scientific << setprecision(8) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large acceptance weight="
        << fullWeightNow/auxWeightNow
        << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
        << "  z=" << z << " m2dip=" << dip.m2Dip
        << " full=" << fullWeightNow << " over=" << overWeightNow << endl;
      if (fullWeightNow/auxWeightNow > 2.)
        scaleOverheadFactor(splittingNowName, 2.);
      double rescale = fullWeightNow/auxWeightNow * 1.15;
      auxWeightNow *= rescale;
      infoPtr->errorMsg("Info in DireTimes::pT2nextQCD_FF: Found large "
                        "acceptance weight for " + splittingNowName);
    }

    // Make overestimate worse to draw sufficiently many rejections for the
    // enhancement algorithm to work for high enhancements.
    double enhanceFurther = !splittingNowName.empty()
      && splits[splittingNowName]->isEnhanced()
      ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;
    if (enhanceFurther>=10.)  auxWeightNow *= 2.;
    if (enhanceFurther>=100.) auxWeightNow *= 5.;
    wt = fullWeightNow/auxWeightNow;
  // Iterate until acceptable pT (or have fallen below pTmin).
  } while (wt < rndmPtr->flat());

  // Not possible to find splitting.
  if ( wt == 0.) return false;

  if (splits[splittingNowName]->giveUpAndForceSplitting()) {
    cout << __PRETTY_FUNCTION__ <<": Forced splitting! " << splittingNowName << endl;
  }
  // Update accepted event weight. No weighted shower for first 
  // "pseudo-emission" step in 1->3 splitting.
  if ( fullWeightNow != 0. && overWeightNow != 0. ) {
    //double enhanceFurther
    //  = enhanceOverestimateFurther(splittingNowName, idRadiator, teval);

    //double enhanceFurther = splittingNowName != ""
    double enhanceFurther = !splittingNowName.empty()
      && splits[splittingNowName]->isEnhanced()
      ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

    double tnow = dip.pT2;
    //if (tnow < teval) enhanceFurther = 1.;
    //else { cout << "accept enhanced" << endl; }
    if (doTrialNow) {
      weights->addTrialEnhancement(tnow, enhanceFurther);
      enhanceFurther = 1.;
    }
    kernelNow = fullWeightsNow;
    auxNow    = auxWeightNow;
    overNow   = overWeightNow;
    boostNow  = enhanceFurther;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it ) {
      // No weight bookkeeping for non-variation components of kernel vector. 
      if (it->first == "base_order_as2") continue;
      double wa = auxWeightNow/overWeightNow * 1./enhanceFurther
                * it->second/fullWeightNow;
      acceptProbability[it->first].insert(make_pair(tnow,wa));
      if (abs(wa) > 1.1 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large accept weight=" << wa
        << "\t for " << it->first << " kernel=" << it->second
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
      }

      if (auxWeightNow == fullWeightNow && overWeightNow == fullWeightNow)
        //rejectProbability[it->first].insert( make_pair(tnow, 1.));
        rejectProbability[it->first].insert( make_pair(tnow, 1. - 1./enhanceFurther));
      else {
        double wv  = auxWeightNow/overWeightNow
                  * (overWeightNow- it->second/enhanceFurther)
                  / (auxWeightNow - fullWeightNow);
        if (abs(wv) > 1.1 && it->first == "base") {
        direInfoPtr->message(1)
        << scientific << setprecision(8) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wv
        << "\t for " << it->first << " kernel=" << it->second << " " << fullWeightNow
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow  << " enhance=" << enhanceFurther << " at pT="
        << sqrt(tnow) << " z=" << dip.z << " m2dip=" << dip.m2Dip
        <<  " for " << splittingNowName << " " << it->first
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
        }
        rejectProbability[it->first].insert( make_pair(tnow, wv));
      }
    }
  }
  //if (splittingNowName != "") splits[splittingNowName]->setIsEnhanced(false);
  if (!splittingNowName.empty()) splits[splittingNowName]->setIsEnhanced(false);

  // Done
  return true;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end.

bool DireTimes::pT2nextQCD_FI(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, const Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  // Lower cut for evolution. Return if no evolution range.
  //double pT2endDip = max( pT2sel, pT2colCut);
  double pT2endDip = max( pT2sel, pT2cutMin(&dip));
  if (pT2endForce >= 0.) pT2endDip = pT2endForce;
  if (pT2begDip < pT2endDip) { dip.pT2 = 0.; return false; }

  BeamParticle& beam = (dip.isrType == 1) ? *beamAPtr : *beamBPtr;

  // Variables used inside evolution loop. (Mainly dummy start values.)
  dip.pT2              = pT2begDip;
  int    nFlavour      = 3;
  double zMinAbs       = 0.0;
  double zMaxAbs       = 1.0;
  double teval         = pT2begDip;
  double xPDFrecoiler  = 0.;
  double wt            = 0.;
  bool   mustFindRange = true;
  int idRadiator       = event[dip.iRadiator].id();
  int idRecoiler       = event[dip.iRecoiler].id();
  bool isColoredRec    = event[dip.iRecoiler].colType()!=0;
  int iSysRec          = dip.systemRec;
  double xRecoiler     = beam[iSysRec].x();
  bool   hasPDFrec     = hasPDF(idRecoiler);

  int iSysRad          = partonSystemsPtr->getSystemOf(dip.iRadiator,true);
  bool hasIn           = partonSystemsPtr->hasInAB(iSysRad)
                      && partonSystemsPtr->hasInAB(iSysRec);
  bool doVariationsNow = doVariations && (iSysRad<=nSysVar || !hasIn);

  double pT2minPDF = pT2cutMin(&dip);
  if (particleDataPtr->colType(idRecoiler) != 0) pT2minPDF = pT2colCut;

  // Get momentum of other beam, since this might be needed to calculate
  // the Jacobian.
  int iOther = (dip.isrType == 1) ? partonSystemsPtr->getInB(iSysRec)
                                  : partonSystemsPtr->getInA(iSysRec);
  Vec4 pOther(event[iOther].p());

  multimap<double,string> newOverestimates [3];
  double overestimateSum [3];
  unordered_map<string,double> fullWeightsNow;
  double fullWeightNow(0.), overWeightNow(0.), auxWeightNow(0.), daux(0.);

  // Begin evolution loop towards smaller pT values.
  int    loopTinyPDFdau = 0;
  int    nContinue(0), nContinueMax(10000);
  bool   hasTinyPDFdau  = false;
  do {

    wt          = 0.;
    //double tnow = dip.pT2;
    double tnow = (!forceBranching) ? dip.pT2 : pT2begDip;
    dip.z       = -1.;
    dip.xa      = -1.;
    dip.sa1     = 0.;
    dip.phi     = -1.;
    dip.phia1   = -1.;

    // Force exit if non-Sudakov style forced branching is stuck.
    if (forceBranching && nContinue >= nContinueMax) {
      wt = 0.0; dip.pT2 = tnow = 0.;
      break;
    }

    // Update event weight after one step. 
    if ( fullWeightNow != 0. && overWeightNow != 0. ) {
      //double enhanceFurther
      //  = enhanceOverestimateFurther(splittingNowName, idRadiator, teval);
      //if (tnow < teval) enhanceFurther = 1.;

      //double enhanceFurther = splittingNowName != ""
      double enhanceFurther = !splittingNowName.empty()
        && splits[splittingNowName]->isEnhanced()
        ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

      if (doTrialNow) enhanceFurther = 1.;

      kernelNow = fullWeightsNow;
      auxNow    = auxWeightNow;
      overNow   = overWeightNow;
      boostNow  = enhanceFurther;
      for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
        it != fullWeightsNow.end(); ++it ) {
        // No weight bookkeeping for non-variation components of kernel vector. 
        if (it->first == "base_order_as2") continue;
        double wv = auxWeightNow/overWeightNow
                 * (overWeightNow- it->second/enhanceFurther)
                 / (auxWeightNow - fullWeightNow);
        if (abs(wv) > 1.1 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wv
        << "\t for " << it->first << " kernel=" << it->second 
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
        }
        rejectProbability[it->first].insert( make_pair(tnow,wv));
      }
    }
 
    //if (splittingNowName != "") splits[splittingNowName]->setIsEnhanced(false);
    if (!splittingNowName.empty()) splits[splittingNowName]->setIsEnhanced(false);
    splittingNowName.clear();
    fullWeightsNow.clear();
    fullWeightNow = overWeightNow = auxWeightNow = 0.;

    // Leave unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Finish evolution if PDF vanishes.
    double tnew = (useFixedFacScale) ? fixedFacScale2 : factorMultFac*tnow;
    bool inNew  = (hasPDFrec)
                ? beam.insideBounds(xRecoiler, max(tnew, pT2colCut) ) : 1.0;

    if (hasPDFrec && !inNew) { dip.pT2 = 0.0; return false; }

    // Bad sign if repeated looping with small daughter PDF, so fail.
    // (Example: if all PDF's = 0 below Q_0, except for c/b companion.)
    if (hasTinyPDFdau) ++loopTinyPDFdau;
    if (hasPDFrec && loopTinyPDFdau > MAXLOOPTINYPDF) {
      infoPtr->errorMsg("Warning in DireTimes::pT2nextQCD_FI: "
      "small daughter PDF");
      dip.pT2 = 0.0;
      return false;
    }

    // Initialize evolution coefficients at the beginning and
    // reinitialize when crossing c and b flavour thresholds.
    double pdfScale2 = useFixedFacScale ? fixedFacScale2 : factorMultFac*tnow;
    pdfScale2        = max(pdfScale2, pT2minPDF);
    if (mustFindRange
      || tnow < evalpdfstep(event[dip.iRecoiler].id(), tnow, m2cPhys, m2bPhys)*teval) {

      newOverestimates[0].clear();
      newOverestimates[1].clear();
      newOverestimates[2].clear();
      teval       = tnow;
      overestimateSum[0] = 0.;
      overestimateSum[1] = 0.;
      overestimateSum[2] = 0.;

      if (tnow > m2b)      nFlavour = 5;
      else if (tnow > m2c) nFlavour = 4;
      else                 nFlavour = 3;

      // Parton density of daughter at current scale.
      //pdfScale2    = (useFixedFacScale) ? fixedFacScale2 : factorMultFac*tnow;
      //pdfScale2    = max(pdfScale2, pT2minPDF);
      xPDFrecoiler = getXPDF(idRecoiler, xRecoiler, pdfScale2, iSysRec, &beam);
      if ( hasPDFrec && xPDFrecoiler != 0.
        && abs(xPDFrecoiler) < 1e-15) {
        int sign      = (xPDFrecoiler > 0.) ? 1 : -1;
        xPDFrecoiler  = sign*tinypdf(xRecoiler);
        hasTinyPDFdau = true;
      }

      double xMin = (hasPDFrec) ? xRecoiler : 0.;

      // Calculate and add user-defined overestimates.
      getNewOverestimates(&dip, event, tnow, pT2endDip, xMin, zMinAbs, zMaxAbs,
        newOverestimates);
      addNewOverestimates(newOverestimates, overestimateSum);

      // Store pT at which overestimate has been evaluated. 
      dip.pT2Old = teval;

      // Initialization done for current range.
      mustFindRange = false;
    }

    if (overestimateSum[1] < TINYOVERESTIMATE) { dip.pT2 = 0.0; return false; }
    if (newOverestimates[1].empty())       { dip.pT2 = 0.0; return false; }

    // Generate next evolution scale.
    bool forceFixedAs = (tnow < pT2colCut)
                     || (event[dip.iRadiator].colType() == 0);
    tnow  = getNextTQCD( &dip, overestimateSum[1], tnow, pT2endDip, pT2freeze,
      (forceBranching ? -1 : 1), forceFixedAs);
    if (tnow < 0.) { 
      wt = 0.0; dip.pT2 = tnow = 0.;
      double R0 = overestimateSum[1]*rndmPtr->flat();
      if (!newOverestimates[1].empty()) {
        if (newOverestimates[1].lower_bound(R0) == newOverestimates[1].end())
          splittingNowName = newOverestimates[1].rbegin()->second;
        else
          splittingNowName = newOverestimates[1].lower_bound(R0)->second;
      }
      break;
    }

    wt      = 0.0;
    dip.pT2 = tnow;

    // If crossed b threshold, continue evolution from this threshold.
    if        ( nFlavour == 5 && tnow < m2bPhys ) {
      mustFindRange = true;
    // If crossed c threshold, continue evolution from this threshold.
    } else if ( nFlavour == 4 && tnow < m2cPhys ) {
      mustFindRange = true;
    }

    // Leave incoming heavy quarks below threshold unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Abort evolution if below cutoff scale, or below another branching.
    if ( tnow < pT2endDip ) { dip.pT2 = tnow = 0.; break; }

    // Try user-defined splittings first.
    double R = overestimateSum[1]*rndmPtr->flat();
    double z = -1.;
    int idDaughter, idSister;
    idDaughter = idSister = 0;

    if (!newOverestimates[1].empty()) {

      if (newOverestimates[1].lower_bound(R) == newOverestimates[1].end())
        splittingNowName = newOverestimates[1].rbegin()->second;
      else
        splittingNowName = newOverestimates[1].lower_bound(R)->second;

      // Generate z value and calculate splitting probability.
      double xMin = (hasPDFrec) ? xRecoiler : 0.;
      getNewSplitting( event, &dip, teval, xMin, tnow, zMinAbs,
        zMaxAbs, idRadiator, splittingNowName, forceFixedAs, 0,
        idDaughter, idSister, z, wt, fullWeightsNow, overWeightNow);

      // Store z value for the splitting.
      dip.z      = z;
    }

    // Done for vanishing accept probability.
    if (wt == 0.) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    fullWeightNow = fullWeightsNow["base"];

    // Get particle masses.
    // Radiator before splitting.
    double m2Bef = particleDataPtr->isResonance(event[dip.iRadiator].id())
                 ? getMass(event[dip.iRadiator].id(),3,
                           event[dip.iRadiator].mCalc())
                 : (event[dip.iRadiator].idAbs() < 6
                 || event[dip.iRadiator].id() == 21
                 || event[dip.iRadiator].id() == 22)
                 ? getMass(event[dip.iRadiator].id(),2)
                 : getMass(event[dip.iRadiator].id(),1);
    // Radiator after splitting.
    double m2r   = particleDataPtr->isResonance(idDaughter)
                   && idDaughter == event[dip.iRadiator].id()
                 ? getMass(idDaughter,3,event[dip.iRadiator].mCalc())
                 : (abs(idDaughter) < 6
                     || idDaughter == 21
                     || event[dip.iRadiator].id() == 22)
                 ? getMass(idDaughter,2)
                 : getMass(idDaughter,1);
    // Emission.
    double m2e   = (abs(dip.flavour) < 6
                     || dip.flavour == 21
                     || dip.flavour == 22)
                 ? getMass(dip.flavour,2)
                 : getMass(dip.flavour,1);

    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    if (canUseSplitInfo) {
      m2Bef = splits[splittingNowName]->splitInfo.kinematics()->m2RadBef;
      m2r   = splits[splittingNowName]->splitInfo.kinematics()->m2RadAft;
      m2e   = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft;
    }
    int nEmissions = splits[splittingNowName]->nEmissions();

    double q2    = (event[dip.iRecoiler].p()
                   -event[dip.iRadiator].p()).m2Calc();
    // Recalculate the kinematicaly available dipole mass.
    double Q2    = dip.m2Dip - m2Bef + m2r + m2e;

    // Disallow gluon -> heavy quarks if pT has fallen below 2*mQuark.
    if ( event[dip.iRecoiler].idAbs() == 5 && nEmissions == 2
      && tnow <= 4.*m2bPhys) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    } else if ( event[dip.iRecoiler].idAbs() == 4 && nEmissions == 2
      && tnow <= 4.*m2cPhys) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Discard this 1->3 splitting if the pT has fallen below mEmission (since
    // such splittings would not be included in the virtual corrections to the
    // 1->2 kernels. Note that the threshold is pT>mEmission,since alphaS is
    // evaluated at pT, not virtuality sa1).
    if ( nEmissions == 2
      && ( (abs(dip.flavour) == 4 && tnow < m2cPhys)
        || (abs(dip.flavour) == 5 && tnow < m2bPhys))) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    double m2a(m2e), m2i(m2e), m2j(m2Bef), m2aij(m2Bef), m2k(0.0);
    if (canUseSplitInfo)
      m2j = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft2;

    double tDire = tnow;
    if (kinRels->FSRevolutionMode==1)
      tDire = kinRels->t_fi_dire_from_cs(z,tnow,Q2);
    // Recalculate the kinematicaly available dipole mass.
    // Calculate CS variables.
    double kappa2 =  tDire/Q2;
    double xCS    = 1 - kappa2/(1.-z);
    double xCDST  = xCS*( 1. + (m2Bef-m2r-m2e)/Q2 );
    double xNew   = xRecoiler / xCDST;

    // f(xNew) not stable for xNew excessively close to unity. 
    // As a last resort, reject this splitting.
    if (!canUseSplitInfo && abs(xRecoiler-xCDST)/xRecoiler < 1e-5) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Jacobian factors.
    double jacobian = 1.;
    if (canUseSplitInfo) {
      jacobian
        = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
      unordered_map<string,double> psvars
        = splits[splittingNowName]->getPhasespaceVars( event, partonSystemsPtr);
      xNew = psvars["xInAft"];
    }

    // Firstly reduce by PDF ratio.
    double pdfRatio = 1.;
    pdfScale2 = (useFixedFacScale) ? fixedFacScale2
      : factorMultFac * tnow;
    pdfScale2 = max(pdfScale2, pT2minPDF);
    double pdfScale2Old = pdfScale2;
    double pdfScale2New = pdfScale2;
    if (forceBranching) pdfScale2Old = infoPtr->Q2Fac();
    if (forceBranching) pdfScale2New = infoPtr->Q2Fac();
    bool inD = hasPDFrec ? beam.insideBounds(xRecoiler, pdfScale2Old) : true; 
    bool inM = hasPDFrec ? beam.insideBounds(xNew, pdfScale2New)      : true; 
    double pdfOld = getXPDF(idRecoiler, xRecoiler, pdfScale2Old, iSysRec,
      &beam, false, z, dip.m2Dip);
    double pdfNew = getXPDF(idRecoiler, xNew, pdfScale2New, iSysRec,
      &beam, false, z, dip.m2Dip);

    if ( hasPDFrec && pdfOld != 0.
      && abs(pdfOld) < tinypdf(xRecoiler) ) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    if (hasPDFrec && pdfOld == 0.) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Extreme case of low-scale gluon, for which denominator rapidly
    // approaches zero. In this case, cut off branching probability if
    // daughter PDF fell too rapidly, to avoid large shower weights.
    // (Note: Last resort - would like something more physical here!)
    double xPDFrecoilerLow = getXPDF(idRecoiler, xRecoiler,
      pdfScale2Old*pdfScale2Old/max(teval, pT2minPDF), iSysRec, &beam);
    if ( idRecoiler == 21
      && ( abs(pdfOld/xPDFrecoiler) < 1e-4
        || abs(xPDFrecoilerLow/pdfOld) < 1e-4) ) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Reject the splitting if PDF after emission is identically zero.
    if (hasPDFrec && pdfNew == 0.) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Set PDF ratio to zero if x-/pT-values are out-of-bounds.
    pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;

    if (!canUseSplitInfo) {
      // Jacobian for 1->2 splittings, in CS variables.
      if ( nEmissions!= 2 ) jacobian   = ( 1.- xCS) / ( 1. - xCDST); 

      // Jacobian for 1->3 splittings, in CS variables.
      if ( nEmissions == 2 ) {
        double m2ai  = dip.sa1 + m2a + m2i;
        xCS          = (q2 - m2ai - m2a - m2i)
                     / (q2 - m2ai - m2a - m2i - dip.pT2 * dip.xa/dip.z);

        // Jacobian for competing steps, i.e. applied to over-all splitting rate.
        double saij = (xCS - 1.)/xCS * (q2 - m2a) + (m2ai + m2j)/xCS;
        double xbar = (q2 - m2aij - m2k) / (q2 - saij - m2k);

        // Calculate the partonic eCM before the splitting.
        double sHatBefore = (event[dip.iRecoiler].p() + pOther).m2Calc();
        double m2OtherBeam = 0.;

        // Now construct the new recoiler momentum.
        Vec4 q(event[dip.iRecoiler].p()-event[dip.iRadiator].p());
        Vec4 pRadBef(event[dip.iRadiator].p());
        Vec4 pRecBef(event[dip.iRecoiler].p());
        Vec4 qpar(q.px()+pRadBef.px(), q.py()+pRadBef.py(), q.pz(), q.e());
        double qpar2 = qpar.m2Calc();
        double pT2ijt = pow2(pRadBef.px()) + pow2(pRadBef.py());
        Vec4 pRec( (pRecBef - (qpar*pRecBef)/qpar2 * qpar)
                  * sqrt( (lABC(q2,saij,m2k)   - 4.*m2k*pT2ijt)
                         /(lABC(q2,m2aij,m2k) - 4.*m2k*pT2ijt))
                  + qpar * (q2+m2k-saij)/(2.*qpar2) );
        // Calculate the partonic eCM after the splitting.
        double sHatAfter = (pOther + pRec).m2Calc();

        // Calculate Jacobian.
        double rho_bai = sqrt( lABC(sHatBefore, m2k, m2OtherBeam)
                             / lABC(sHatAfter,  m2k, m2OtherBeam) );
        jacobian = rho_bai/xbar
                 * (saij + m2k - q2) / sqrt( lABC(saij, m2k, q2) );

        // Additional jacobian for non-competing steps.
        double saib = m2ai + m2k
          + dip.z/dip.xa * (q2 - m2k - m2ai - m2j - dip.pT2*dip.xa/dip.z);
        jacobian *= (m2ai + m2k - saib) / sqrt( lABC(m2ai, m2k, saib) );

        xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
        // Extra correction from massless to massive propagator.
        jacobian   *= ( 1.- xCS) / ( 1. - xCDST); 

        // Recalculate PDF ratio.
        xNew     = xRecoiler / xCDST;
        inM      = (!hasPDFrec) ? true : beam.insideBounds(xNew, pdfScale2); 
        pdfNew   = getXPDF(idRecoiler, xNew, pdfScale2, iSysRec, &beam);
        pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;
      }
    }

    // f(xMother) not stable for xMother excessively close to unity. 
    // As a last resort, reject this splitting.
    if (isColoredRec && (abs(1.- 1./xNew) < 1e-3 || 1.-xNew < 1e-3)) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // More last resort.
    if (idRecoiler == 21 && pdfScale2 == pT2minPDF
      && pdfRatio > 50.)
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && pdfRatio > 10.)
      pdfRatio = 0.;
    if (std::isinf(pdfRatio) || std::isnan(pdfRatio))
      pdfRatio = 0.;

    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = min(pdfRatio,5.);

    if (kinRels->FSRevolutionMode==1) jacobian = kinRels->xcs_fi(z,tnow,Q2);

    fullWeightNow  *= pdfRatio*jacobian;

    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= pdfRatio*jacobian;

    // Before generating kinematics: Reset sai if the kernel fell on an
    // endpoint contribution.
    if ( nEmissions == 2
      && splits[splittingNowName]->splitInfo.kinematics()->sai == 0.)
      dip.sa1 = 0.;

    if (fullWeightNow == 0. ) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Retrieve argument of alphaS.
    double scale2 =  splits[splittingNowName]->couplingScale2 ( z, tnow, Q2,
      make_pair (event[dip.iRadiator].id(), event[dip.iRadiator].isFinal()),
      make_pair (event[dip.iRecoiler].id(), event[dip.iRecoiler].isFinal()));
    if (scale2 < 0.) scale2 = tnow;
    double talpha = max(scale2, pT2colCut);

    // Reweight to match PDF alpha_s, including corrective terms for
    // renormalisation scale variation. For NLO splitting, all coupling
    // factors have already been covered in the competing phase.
    alphasReweight(tnow, talpha, dip.system, forceFixedAs, wt, fullWeightNow,
      overWeightNow, renormMultFac);
    auxWeightNow   = overWeightNow;

    // Create muR-variations.
    double asw = 1.;
    alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
      renormMultFac);
    fullWeightsNow["base"] *= asw;
    if (fullWeightsNow.find("base_order_as2") != fullWeightsNow.end())
      fullWeightsNow["base_order_as2"] *= asw;
    if (doVariationsNow && splittingNowName.find("qcd") != string::npos) {
      if (settingsPtr->parm("Variations:muRfsrDown") != 1.) {
        asw = 1.;
        alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
          (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrDown")
          : renormMultFac);
        fullWeightsNow["Variations:muRfsrDown"] *= asw;
      }
      if (settingsPtr->parm("Variations:muRfsrUp")   != 1.) {
        asw = 1.;
        alphasReweight(tnow, talpha, dip.system, forceFixedAs, daux, asw, daux,
          (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrUp")
          : renormMultFac);
        fullWeightsNow["Variations:muRfsrUp"] *= asw;
      }

      // PDF variations.
      if (hasPDFrec && settingsPtr->flag("Variations:PDFup") ) {
        int valSea = (beam[iSysRec].isValence()) ? 1 : 0;
        if( beam[iSysRec].isUnmatched() ) valSea = 2;
        beam.calcPDFEnvelope( make_pair(idRecoiler, idRecoiler),
          make_pair(xNew,xRecoiler), pdfScale2, valSea);
        PDF::PDFEnvelope ratioPDFEnv = beam.getPDFEnvelope();
        double deltaPDFplus
          = min(ratioPDFEnv.errplusPDF  / ratioPDFEnv.centralPDF, 10.);
        double deltaPDFminus
          = min(ratioPDFEnv.errminusPDF / ratioPDFEnv.centralPDF, 10.);
        fullWeightsNow["Variations:PDFup"]   = fullWeightsNow["base"]
          * ((tnow > pT2minVariations) ? (1.0 + deltaPDFplus) : 1.0);
        fullWeightsNow["Variations:PDFdown"] = fullWeightsNow["base"]
          * ((tnow > pT2minVariations) ? (1.0 - deltaPDFminus) : 1.0);
      }
    } else {
      fullWeightsNow["Variations:muRfsrUp"]   *= asw;
      fullWeightsNow["Variations:muRfsrDown"] *= asw;
    }

    if (splits[splittingNowName]->giveUpAndForceSplitting()) {wt=1.; auxWeightNow=overWeightNow; break;}

    // Ensure that accept probability is positive.
    if (fullWeightNow < 0.) {
      direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Negative splitting kernel="
        << fullWeightNow
        << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
        << " and z=" << z << endl;
      auxWeightNow *= -1.;
    }

    // Reset overestimate if necessary.
    if ( fullWeightNow/auxWeightNow > 1.0) {
      direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large acceptance weight="
        << fullWeightNow/auxWeightNow
        << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
        << " and z=" << z << " " << xCDST << "\t(PDF ratio=" << pdfRatio
        << " = " << pdfNew << " / " << pdfOld 
        << " at xNew=" << xNew << " xOld=" << xRecoiler
        << " id=" << idRecoiler << ") "
        << jacobian << endl;
        /*cout
        << " " << __LINE__ << " : Large acceptance weight="
        << fullWeightNow/auxWeightNow
        << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
        << " and z=" << z << " " << xCDST << "\t(PDF ratio=" << pdfRatio
        << " = " << pdfNew << " / " << pdfOld 
        << " at xNew=" << xNew << " xOld=" << xRecoiler
        << " id=" << idRecoiler << ") "
        << jacobian << endl;*/
      double rescale = fullWeightNow/auxWeightNow * 1.15;
      auxWeightNow *= rescale;
      infoPtr->errorMsg("Info in DireTimes::pT2nextQCD_FI: Found large "
                        "acceptance weight for " + splittingNowName);
    }

    wt = fullWeightNow/auxWeightNow;

  // Iterate until acceptable pT (or have fallen below pTmin).
  } while (wt < rndmPtr->flat());

  // Not possible to find splitting.
  if ( wt == 0.) return false;

  if (splits[splittingNowName]->giveUpAndForceSplitting()) {
    cout << __PRETTY_FUNCTION__ <<": Forced splitting!" << endl;
  }
  // Update accepted event weight. No weighted shower for first 
  // "pseudo-emission" step in 1->3 splitting.
  if ( fullWeightNow != 0. && overWeightNow != 0. ) {
    //double enhanceFurther
    //  = enhanceOverestimateFurther(splittingNowName, idRadiator, teval);
    double tnow = dip.pT2;
    //if (tnow < teval) enhanceFurther = 1.;
    //else { cout << "accept enhanced" << endl; }

    //double enhanceFurther = splittingNowName != ""
    double enhanceFurther = !splittingNowName.empty()
      && splits[splittingNowName]->isEnhanced()
      ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

    if (doTrialNow) {
      weights->addTrialEnhancement(tnow, enhanceFurther);
      enhanceFurther = 1.;
    }
    kernelNow = fullWeightsNow;
    auxNow    = auxWeightNow;
    overNow   = overWeightNow;
    boostNow  = enhanceFurther;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it ) {
      // No weight bookkeeping for non-variation components of kernel vector. 
      if (it->first == "base_order_as2") continue;
      double wa = auxWeightNow/overWeightNow * 1./enhanceFurther
                * it->second/fullWeightNow;
      acceptProbability[it->first].insert(make_pair(tnow,wa));
      if (abs(wa) > 0.0 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large accept weight=" << wa
        << "\t for " << it->first << " kernel=" << it->second << " " << fullWeightNow 
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
      }

      if (auxWeightNow == fullWeightNow && overWeightNow == fullWeightNow)
        rejectProbability[it->first].insert( make_pair(tnow, 1.0));
      else {
        double wv  = auxWeightNow/overWeightNow
                  * (overWeightNow- it->second/enhanceFurther)
                  / (auxWeightNow - fullWeightNow);
        if (abs(wv) > 1.1 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wv
        << "\t for " << it->first << " kernel=" << it->second 
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
        }
        rejectProbability[it->first].insert( make_pair(tnow, wv));
      }
    }
  }
  if (!splittingNowName.empty()) splits[splittingNowName]->setIsEnhanced(false);

  // Done
  return true;

}

//--------------------------------------------------------------------------

void DireTimes::updateWeightsAfterRejection(const double & tnow,
  const double & teval, const unordered_map<string,double> & fullWeightsNow,
  const double & fullWeightNow, const double & overWeightNow,
  const double& auxWeightNow) {

  // Update event weight after one step. 
  if ( fullWeightNow != 0. && overWeightNow != 0. ) {
    double enhanceFurther = !splittingNowName.empty()
      && splits[splittingNowName]->isEnhanced()
      ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

    if (doTrialNow) enhanceFurther = 1.;

    kernelNow = fullWeightsNow;
    auxNow    = auxWeightNow;
    overNow   = overWeightNow;
    boostNow  = enhanceFurther;

    for ( unordered_map<string,double>::const_iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it ) {
      // No weight bookkeeping for non-variation components of kernel vector. 
      if (it->first == "base_order_as2") continue;
      double wv = auxWeightNow/overWeightNow
               * (overWeightNow- it->second/enhanceFurther)
               / (auxWeightNow - fullWeightNow);
      if (abs(wv) > 1.1 && it->first == "base") {
      direInfoPtr->message(1) << __FILE__ //<< " " << __func__
      << " " << __LINE__ << " : Large reject weight=" << wv
      << "\t for " << it->first << " kernel=" << it->second
      << " base=" << fullWeightNow 
      << "\t overestimate=" << overNow
      << "\t aux. overestimate=" << auxNow << " at pT="
      << sqrt(tnow)
      <<  " for " << splittingNowName
      << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
      << endl;
      }
      rejectProbability[it->first].insert( make_pair(tnow,wv));
    }
  }

  // Done.
  return;

}

//--------------------------------------------------------------------------

void DireTimes::setupForNextEvolutionStep( double &wt, DireTimesEnd& dip,
  unordered_map<string,double> & fullWeightsNow, double & fullWeightNow,
  double & overWeightNow, double& auxWeightNow) {

  wt          = 0.;
  dip.z       = -1.;
  dip.xa      = -1.;
  dip.sa1     = 0.;
  dip.phi     = -1.;
  dip.phia1   = -1.;
  splittingNowName.clear();
  fullWeightsNow.clear();
  fullWeightNow = overWeightNow = auxWeightNow = 0.;

  // Done.
  return;

}

//--------------------------------------------------------------------------

void DireTimes::calculateMURvariations(const bool & doVariationsNow,
  const double & tnow,
  const double & talpha, const int & system, const bool & forceFixedAs,
  unordered_map<string,double> & fullWeightsNow){

  double daux(0.), asw(1.);
  alphasReweight(tnow, talpha, system, forceFixedAs, daux, asw, daux,
    renormMultFac);
  fullWeightsNow["base"] *= asw;
  if (fullWeightsNow.find("base_order_as2") != fullWeightsNow.end())
    fullWeightsNow["base_order_as2"] *= asw;
  if (doVariationsNow && splittingNowName.find("qcd") != string::npos) {
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.) {
      asw = 1.;
      alphasReweight(tnow, talpha, system, forceFixedAs, daux, asw, daux,
        (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrDown")
        : renormMultFac);
      fullWeightsNow["Variations:muRfsrDown"] *= asw;
    }
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.) {
      asw = 1.;
      alphasReweight(tnow, talpha, system, forceFixedAs, daux, asw, daux,
        (tnow > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrUp")
        : renormMultFac);
      fullWeightsNow["Variations:muRfsrUp"] *= asw;
    }

  } else {
    fullWeightsNow["Variations:muRfsrUp"]   *= asw;
    fullWeightsNow["Variations:muRfsrDown"] *= asw;
  }

  // Done.
  return;

}

//--------------------------------------------------------------------------

void DireTimes::calculatePDFvariations(const bool & doVariationsNow,
  const double & tnow, const bool & hasPDFrec,
  const int & iSysRec, const int & idRecoiler, const double & xNew,
  const double & xRecoiler, const double & pdfScale2,
  BeamParticle* beamPtr, unordered_map<string,double> & fullWeightsNow) {
  if (doVariationsNow) {
    // PDF variations.
    if (hasPDFrec && settingsPtr->flag("Variations:PDFup") ) {
      int valSea = (*beamPtr)[iSysRec].isValence() ? 1 : 0;
      if( (*beamPtr)[iSysRec].isUnmatched() ) valSea = 2;
      beamPtr->calcPDFEnvelope( make_pair(idRecoiler, idRecoiler),
        make_pair(xNew,xRecoiler), pdfScale2, valSea);
      PDF::PDFEnvelope ratioPDFEnv = beamPtr->getPDFEnvelope();
      double deltaPDFplus
        = min(ratioPDFEnv.errplusPDF  / ratioPDFEnv.centralPDF, 10.);
      double deltaPDFminus
        = min(ratioPDFEnv.errminusPDF / ratioPDFEnv.centralPDF, 10.);
      fullWeightsNow["Variations:PDFup"]   = fullWeightsNow["base"]
        * ((tnow > pT2minVariations) ? (1.0 + deltaPDFplus) : 1.0);
      fullWeightsNow["Variations:PDFdown"] = fullWeightsNow["base"]
        * ((tnow > pT2minVariations) ? (1.0 - deltaPDFminus) : 1.0);
    }
  }

  // Done.
  return;

}

//--------------------------------------------------------------------------

void DireTimes::updateWeightsAfterAcceptance(const double & tnow,
  const double & teval, const unordered_map<string,double> & fullWeightsNow,
  const double & fullWeightNow, const double & overWeightNow,
  const double& auxWeightNow) {

  // Update accepted event weight. No weighted shower for first 
  // "pseudo-emission" step in 1->3 splitting.
  if ( fullWeightNow != 0. && overWeightNow != 0. ) {

    double enhanceFurther = !splittingNowName.empty()
      && splits[splittingNowName]->isEnhanced()
      ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;

    if (doTrialNow) {
      weights->addTrialEnhancement(tnow, enhanceFurther);
      enhanceFurther = 1.;
    }
    kernelNow = fullWeightsNow;
    auxNow    = auxWeightNow;
    overNow   = overWeightNow;
    boostNow  = enhanceFurther;

    for ( unordered_map<string,double>::const_iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it ) {
      // No weight bookkeeping for non-variation components of kernel vector. 
      if (it->first == "base_order_as2") continue;
      double wa = auxWeightNow/overWeightNow * 1./enhanceFurther
                * it->second/fullWeightNow;
      acceptProbability[it->first].insert(make_pair(tnow,wa));
      if (abs(wa) > 0.0 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large accept weight=" << wa
        << "\t for " << it->first << " kernel=" << it->second << " " << fullWeightNow 
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
      }

      if (auxWeightNow == fullWeightNow && overWeightNow == fullWeightNow)
        rejectProbability[it->first].insert( make_pair(tnow, 1.0));
      else {
        double wv  = auxWeightNow/overWeightNow
                  * (overWeightNow- it->second/enhanceFurther)
                  / (auxWeightNow - fullWeightNow);
        if (abs(wv) > 1.1 && it->first == "base") {
        direInfoPtr->message(1) << __FILE__ //<< " " << __func__
        << " " << __LINE__ << " : Large reject weight=" << wv
        << "\t for " << it->first << " kernel=" << it->second 
        << "\t overestimate=" << overNow
        << "\t aux. overestimate=" << auxNow << " at pT="
        << sqrt(tnow)
        <<  " for " << splittingNowName
        << "\t enhance=" << enhanceFurther << " at t=" << sqrt(teval)
        << endl;
        }
        rejectProbability[it->first].insert( make_pair(tnow, wv));
      }
    }
  }

  // Done
  return;

}

//--------------------------------------------------------------------------

void DireTimes::getMassesforSplitting(const DireTimesEnd & dip,
  const Event& event, const int & idDaughter,
  double & m2Bef, double & m2r, double & m2e, double & m2s, double & m2a,
  double & m2i, double & m2j, double & m2aij, double & m2k) {

  // Get particle masses.

  // Radiator before splitting.
  m2Bef = particleDataPtr->isResonance(event[dip.iRadiator].id())
               ? getMass(event[dip.iRadiator].id(),3,
                         event[dip.iRadiator].mCalc())
               : (event[dip.iRadiator].idAbs() < 6
               || event[dip.iRadiator].id() == 21
               || event[dip.iRadiator].id() == 22)
               ? getMass(event[dip.iRadiator].id(),2)
               : getMass(event[dip.iRadiator].id(),1);

  // Radiator after splitting.
  m2r   = particleDataPtr->isResonance(idDaughter)
                 && idDaughter == event[dip.iRadiator].id()
               ? getMass(idDaughter,3,event[dip.iRadiator].mCalc())
               : (abs(idDaughter) < 6
                   || idDaughter == 21
                   // || idDaughter == 22) should it be this??
                   || event[dip.iRadiator].id() == 22)
               ? getMass(idDaughter,2)
               : getMass(idDaughter,1);
  // Emission.
  m2e   = (abs(dip.flavour) < 6
                   || dip.flavour == 21
                   || dip.flavour == 22)
               ? getMass(dip.flavour,2)
               : getMass(dip.flavour,1);

  // Recoiler. 
  m2s   = particleDataPtr->isResonance(event[dip.iRecoiler].id())
             ? getMass(event[dip.iRecoiler].id(),3,
                       event[dip.iRecoiler].mCalc())
             : (event[dip.iRecoiler].idAbs() < 6
             || event[dip.iRecoiler].id() == 21
             || event[dip.iRecoiler].id() == 22)
             ? getMass(event[dip.iRecoiler].id(),2)
             : getMass(event[dip.iRecoiler].id(),1);
  if (!event[dip.iRecoiler].isFinal()) m2s = 0.;

  bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
  if (canUseSplitInfo) {
    m2Bef = splits[splittingNowName]->splitInfo.kinematics()->m2RadBef;
    m2r   = splits[splittingNowName]->splitInfo.kinematics()->m2RadAft;
    m2e   = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft;
  }

  m2a   = m2e;
  m2i   = m2e;
  m2j   = m2Bef;
  m2aij = m2Bef;
  m2k   = m2s;
  if (canUseSplitInfo)
    m2j = splits[splittingNowName]->splitInfo.kinematics()->m2EmtAft2;

  // Done.
  return;

}

//--------------------------------------------------------------------------

void DireTimes::setVetoWeight(const double & tnow, const double & z,
  double & fullWeightNow, double & auxWeightNow, double & wt) {

  // Ensure that accept probability is positive.
  if (fullWeightNow < 0.) {
    direInfoPtr->message(1) << __FILE__ //<< " " << __func__
      << " " << __LINE__ << " : Negative splitting kernel="
      << fullWeightNow
      << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
      << " and z=" << z << endl;
    auxWeightNow *= -1.;
  }

  // Reset overestimate if necessary.
  if ( fullWeightNow/auxWeightNow > 1.0) {
    direInfoPtr->message(1) << __FILE__ //<< " " << __func__
      << " " << __LINE__ << " : Large acceptance weight="
      << fullWeightNow/auxWeightNow
      << " for splitting " << splittingNowName << " at pT=" << sqrt(tnow)
      << " and z=" << z
      << endl;
    double fact = 1.15;
    if (fullWeightNow/auxWeightNow > 2.)
      scaleOverheadFactor(splittingNowName, 2.);
    double rescale = fullWeightNow/auxWeightNow * fact;
    auxWeightNow *= rescale;
    infoPtr->errorMsg("Info in DireTimes: Found large "
                      "acceptance weight for " + splittingNowName);
  }

  // Make overestimate worse to draw sufficiently many rejections for the
  // enhancement algorithm to work for high enhancements.
  double enhanceFurther = !splittingNowName.empty()
    && splits[splittingNowName]->isEnhanced()
    ?  splits[splittingNowName]->getEnhanceFactor() : 1.0;
  if (enhanceFurther>=10.)  auxWeightNow *= 2.;
  if (enhanceFurther>=100.) auxWeightNow *= 5.;

  wt = fullWeightNow/auxWeightNow;

  // Done
  return;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end.

bool DireTimes::pT2nextQCD_FI_test(double pT2begDip, double pT2sel,
  //double pT2forceDec,
  DireTimesEnd& dip, const Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  // Lower cut for evolution. Return if no evolution range.
  double pT2endDip = max( pT2sel, pT2cutMin(&dip));
  if (pT2endForce >= 0.) pT2endDip = pT2endForce;
  if (pT2begDip < pT2endDip) { dip.pT2 = 0.; return false; }

  BeamParticle& beam = (dip.isrType == 1) ? *beamAPtr : *beamBPtr;

  // Variables used inside evolution loop. (Mainly dummy start values.)
  dip.pT2              = pT2begDip;
  int    nFlavour      = 3;
  double zMinAbs       = 0.0;
  double zMaxAbs       = 1.0;
  double teval         = pT2begDip;
  double xPDFrecoiler  = 0.;
  double wt            = 0.;
  bool   mustFindRange = true;
  int idRadiator       = event[dip.iRadiator].id();
  int idRecoiler       = event[dip.iRecoiler].id();
  double m2RadBef      = pow2(particleDataPtr->m0(idRadiator));
  bool isColoredRec    = event[dip.iRecoiler].colType()!=0;
  int iSysRec          = dip.systemRec;
  double xRecoiler     = beam[iSysRec].x();
  bool   hasPDFrec     = hasPDF(idRecoiler);

  // Check if this is a resonance that should be branched in another 
  // evolution sequence.
  bool isRes     = particleDataPtr->isResonance(idRadiator);
  double tDiscard = -1.;
  for (auto w : evolutionWindows) 
    if ( isRes && w.isResonant && w.iWindow != iWindowNow
      && find(w.evolvingIds.begin(), w.evolvingIds.end(),idRadiator)
         != w.evolvingIds.end()) { tDiscard = max(tDiscard,w.tMax); }

  int iSysRad          = partonSystemsPtr->getSystemOf(dip.iRadiator,true);
  bool hasIn           = partonSystemsPtr->hasInAB(iSysRad)
                      && partonSystemsPtr->hasInAB(iSysRec);
  bool doVariationsNow = doVariations && (iSysRad<=nSysVar || !hasIn);

  double pT2minPDF = pT2cutMin(&dip);
  if (particleDataPtr->colType(idRecoiler) != 0) pT2minPDF = pT2colCut;

  // Get momentum of other beam, since this might be needed to calculate
  // the Jacobian.
  int iOther = (dip.isrType == 1) ? partonSystemsPtr->getInB(iSysRec)
                                  : partonSystemsPtr->getInA(iSysRec);
  Vec4 pOther(event[iOther].p());

  multimap<double,string> newOverestimates [3];
  double overestimateSum [3];

  unordered_map<string,double> fullWeightsNow;
  double fullWeightNow(0.), overWeightNow(0.), auxWeightNow(0.);

  // Begin evolution loop towards smaller pT values.
  int    loopTinyPDFdau = 0;
  int    nContinue(0), nContinueMax(2000000);
  bool   hasTinyPDFdau  = false;
  do {

    double tnow = (!forceBranching) ? dip.pT2 : pT2begDip;

    // Force exit if non-Sudakov style forced branching is stuck.
    if (forceBranching && nContinue >= nContinueMax) {
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.0;
      dip.pT2 = tnow = 0.;
      break;
    }

    updateWeightsAfterRejection(tnow, teval, fullWeightsNow, fullWeightNow,
      overWeightNow, auxWeightNow);

    setupForNextEvolutionStep(wt, dip, fullWeightsNow, fullWeightNow,
      overWeightNow, auxWeightNow);

    // Leave unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Finish evolution if PDF vanishes.
    double tnew = (useFixedFacScale) ? fixedFacScale2 : factorMultFac*tnow;
    bool inNew  = (hasPDFrec)
                ? beam.insideBounds(xRecoiler, max(tnew, pT2colCut) ) : 1.0;

    if (hasPDFrec && !inNew) { dip.pT2 = 0.0; return false; }

    // Bad sign if repeated looping with small daughter PDF, so fail.
    // (Example: if all PDF's = 0 below Q_0, except for c/b companion.)
    if (hasTinyPDFdau) ++loopTinyPDFdau;
    if (hasPDFrec && loopTinyPDFdau > MAXLOOPTINYPDF) {
      infoPtr->errorMsg("Warning in DireTimes::pT2nextQCD_FI: "
      "small daughter PDF");
      dip.pT2 = 0.0;
      return false;
    }

    // Initialize evolution coefficients at the beginning and
    // reinitialize when crossing c and b flavour thresholds.
    double pdfScale2 = useFixedFacScale ? fixedFacScale2 : factorMultFac*tnow;
    pdfScale2        = max(pdfScale2, pT2minPDF);
    if (mustFindRange
      || tnow < evalpdfstep(event[dip.iRecoiler].id(), tnow, m2cPhys, m2bPhys)*teval) {

      newOverestimates[0].clear();
      newOverestimates[1].clear();
      newOverestimates[2].clear();
      teval       = tnow;
      overestimateSum[0] = 0.;
      overestimateSum[1] = 0.;
      overestimateSum[2] = 0.;

      if (tnow > m2b)      nFlavour = 5;
      else if (tnow > m2c) nFlavour = 4;
      else                 nFlavour = 3;

      // Parton density of daughter at current scale.
      xPDFrecoiler = getXPDF(idRecoiler, xRecoiler, pdfScale2, iSysRec, &beam);
      if ( hasPDFrec && xPDFrecoiler != 0.
        && abs(xPDFrecoiler) < 1e-15) {
        int sign      = (xPDFrecoiler > 0.) ? 1 : -1;
        xPDFrecoiler  = sign*tinypdf(xRecoiler);
        hasTinyPDFdau = true;
      }

      double xMin = (hasPDFrec) ? xRecoiler : 0.;

      // Calculate and add user-defined overestimates.
      getNewOverestimates( &dip, event, tnow, pT2endDip, xMin, zMinAbs,
        zMaxAbs, newOverestimates);
      addNewOverestimates(newOverestimates, overestimateSum);

      // Store pT at which overestimate has been evaluated. 
      dip.pT2Old = teval;

      // Initialization done for current range.
      mustFindRange = false;
    }

    if ( overestimateSum[0] + overestimateSum[1]
      +  overestimateSum[2] < TINYOVERESTIMATE) {
      dip.pT2 = 0.0; return false; }

    if ( newOverestimates[0].empty() && newOverestimates[1].empty()
      && newOverestimates[2].empty()) {
      dip.pT2 = 0.0; return false; }

    // Now pick type of evolution measure by probability.
    int evType=0;

    // Try user-defined splittings first.
    double R = overestimateSum[evType+1]*rndmPtr->flat();
    if (!newOverestimates[evType+1].empty()) {
      if (newOverestimates[evType+1].lower_bound(R) == newOverestimates[evType+1].end())
        splittingNowName = newOverestimates[evType+1].rbegin()->second;
      else
        splittingNowName = newOverestimates[evType+1].lower_bound(R)->second;
    }

    // Generate next evolution scale.
    bool forceFixedAs
         = (tnow <= pT2colCut) || (event[dip.iRadiator].colType() == 0);
    pair<double,double> rets = getNextEvolutionScale( &dip, event,
      overestimateSum[evType+1], tnow, pT2endDip,
      pT2endDip, pT2freeze, (forceBranching ? -1 : 1), forceFixedAs, evType);
    tnow = rets.first;
    //double wtGen = max(1.,rets.second);
    if (tnow < 0.) { 
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      dip.pT2 = tnow = 0.;
      break;
    }

    wt      = 0.0;
    dip.pT2 = tnow;

    // If crossed b threshold, continue evolution from this threshold.
    if        ( nFlavour == 5 && tnow < m2bPhys ) {
      mustFindRange = true;
    // If crossed c threshold, continue evolution from this threshold.
    } else if ( nFlavour == 4 && tnow < m2cPhys ) {
      mustFindRange = true;
    }

    // Leave incoming heavy quarks below threshold unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Abort evolution if below cutoff scale, or below another branching.
    if ( tnow < pT2endDip ) { 
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      dip.pT2 = tnow = 0.;
      break;
    }

    // Abort evolution if fallen below cut-off on resonance decay. 
    if ( tnow + m2RadBef < tDiscard ) {
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      dip.pT2 = tnow = 0.; break;
    }

    if ( teval > pT2colCut && tnow < pT2colCut
      && !splits[splittingNowName]->is_qcd) {
      mustFindRange = true;
      dip.pT2 = tnow = pT2colCut; wt = 0.;
      continue;
    }

    // Try user-defined splittings first.
    double z = -1.;
    int idDaughter, idSister;
    idDaughter = idSister = 0;
    if (!newOverestimates[evType+1].empty()) {
      // Generate z value and calculate splitting probability.
      double xMin = (hasPDFrec) ? xRecoiler : 0.;
      getNewSplitting( event, &dip, teval, xMin, tnow, zMinAbs,
        zMaxAbs,idRadiator,splittingNowName,forceFixedAs, evType,
        idDaughter, idSister, z, wt, fullWeightsNow, overWeightNow);
      // Store z value for the splitting.
      dip.z      = z;
    }

    // Done for vanishing accept probability.
    if (wt == 0.) {
      if (tDiscard>0) mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      //nContinue++;
      continue;
    }

    fullWeightNow = fullWeightsNow["base"];

    double m2Bef(0.), m2r(0.), m2e(0.), m2s(0.), m2a(0.), m2i(0.),
      m2j(0.), m2aij(0.), m2k(0.);
    getMassesforSplitting(dip, event, idDaughter,
      m2Bef, m2r, m2e, m2s, m2a, m2i, m2j, m2aij, m2k);

    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    int nEmissions = splits[splittingNowName]->nEmissions();

    /*if (!passFlavorCheck(event[dip.iRecoiler].idAbs(), abs(dip.flavour),
        nEmissions, tnow)){
    // Disallow gluon -> heavy quarks if pT has fallen below 2*mQuark.
    if ( event[dip.iRecoiler].idAbs() == 5 && nEmissions == 2
      && tnow <= 4.*m2bPhys)
      return false;
    else if ( event[dip.iRecoiler].idAbs() == 4 && nEmissions == 2
      && tnow <= 4.*m2cPhys)
      return false;

    // Discard this 1->3 splitting if the pT has fallen below mEmission (since
    // such splittings would not be included in the virtual corrections to the
    // 1->2 kernels. Note that the threshold is pT>mEmission,since alphaS is
    // evaluated at pT, not virtuality sa1).
    if ( nEmissions == 2
      && ( (abs(dip.flavour) == 4 && tnow < m2cPhys)
        || (abs(dip.flavour) == 5 && tnow < m2bPhys))) 
      return false;
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }*/

    // Disallow gluon -> heavy quarks if pT has fallen below 2*mQuark.
    if ( event[dip.iRecoiler].idAbs() == 5 && nEmissions == 2
      && tnow <= 4.*m2bPhys) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    } else if ( event[dip.iRecoiler].idAbs() == 4 && nEmissions == 2
      && tnow <= 4.*m2cPhys) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Discard this 1->3 splitting if the pT has fallen below mEmission (since
    // such splittings would not be included in the virtual corrections to the
    // 1->2 kernels. Note that the threshold is pT>mEmission,since alphaS is
    // evaluated at pT, not virtuality sa1).
    if ( nEmissions == 2
      && ( (abs(dip.flavour) == 4 && tnow < m2cPhys)
        || (abs(dip.flavour) == 5 && tnow < m2bPhys))) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    /*if (!getNewX(dip, splittingNowName, xRecoiler, z, tnow,             xNew)) {

    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    int nEmissions = splits[splittingNowName]->nEmissions();
    // Recalculate the kinematicaly available dipole mass.
    double Q2    = dip.m2Dip - m2Bef + m2r + m2e;
    double tDire = tnow;
    if (kinRels->FSRevolutionMode==1)
      tDire = kinRels->t_fi_dire_from_cs(z,tnow,Q2);
    // Recalculate the kinematicaly available dipole mass.
    // Calculate CS variables.
    double kappa2 =  tDire/Q2;
    double xCS    = 1 - kappa2/(1.-z);

    if (evType!=0) {
      double virt = (evType > 0
                  ? tnow : 2.*m2RadBef-tnow);
      xCS = dip.m2Dip/(dip.m2Dip+virt);
      xCS = Q2/(Q2+virt);
    }

    double xCDST  = xCS*( 1. + (m2Bef-m2r-m2e)/Q2 );
    xNew   = xRecoiler / xCDST;

    // f(xNew) not stable for xNew excessively close to unity. 
    // As a last resort, reject this splitting.
    if (!canUseSplitInfo
     && (abs(xRecoiler-xCDST)/xRecoiler < 1e-5 || xNew > 1.))
     return false;

    // Jacobian factors.
    if (canUseSplitInfo) {
      unordered_map<string,double> psvars
        = splits[splittingNowName]->getPhasespaceVars( event, partonSystemsPtr);
      xNew = psvars["xInAft"];
    }

    if (!canUseSplitInfo && nEmissions == 2 ) {
      double q2    = (event[dip.iRecoiler].p()
                     -event[dip.iRadiator].p()).m2Calc();
      double m2ai  = dip.sa1 + m2a + m2i;
      xCS          = (q2 - m2ai - m2a - m2i)
                   / (q2 - m2ai - m2a - m2i - dip.pT2 * dip.xa/dip.z);
      xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
      xNew     = xRecoiler / xCDST;
    }

    // f(xMother) not stable for xMother excessively close to unity. 
    // As a last resort, reject this splitting.
    if (isColoredRec && (abs(1.- 1./xNew) < 1e-3 || 1.-xNew < 1e-3)) 
      return false;


      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }*/

    // Recalculate the kinematicaly available dipole mass.
    double Q2    = dip.m2Dip - m2Bef + m2r + m2e;
    double tDire = tnow;
    if (kinRels->FSRevolutionMode==1)
      tDire = kinRels->t_fi_dire_from_cs(z,tnow,Q2);
    // Recalculate the kinematicaly available dipole mass.
    // Calculate CS variables.
    double kappa2 =  tDire/Q2;
    double xCS    = 1 - kappa2/(1.-z);

    if (abs(evType)==1) {
      double virt = (evType > 0 ? tnow : pow2(2.*sqrt(m2RadBef)-sqrt(tnow)) );
      xCS = dip.m2Dip/(dip.m2Dip+virt);
    }

    if (evType==2) {
      double virt = tnow + m2RadBef;
      xCS = dip.m2Dip/(dip.m2Dip+virt);
    }

    double xCDST  = xCS*( 1. + (m2Bef-m2r-m2e)/Q2 );
    double xNew   = xRecoiler / xCDST;

    // f(xNew) not stable for xNew excessively close to unity. 
    // As a last resort, reject this splitting.
    if (!canUseSplitInfo
     && (abs(xRecoiler-xCDST)/xRecoiler < 1e-5 || xNew > 1.)) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Jacobian factors.
    double jacobian = 1.;
    if (canUseSplitInfo) {
      jacobian
        = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
      unordered_map<string,double> psvars
        = splits[splittingNowName]->getPhasespaceVars( event, partonSystemsPtr);
      xNew = psvars["xInAft"];
    }

    /*multiplyJacobian(dip, event, splittingNowName, fullWeightNow, fullWeightsNow) {
    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    int nEmissions = splits[splittingNowName]->nEmissions();
    double jacobian = 1.;
    if (canUseSplitInfo) {
      jacobian
        = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
    } else {

      // Jacobian for 1->2 splittings, in CS variables.
      if ( nEmissions!= 2 ) {
        //jacobian   = ( 1.- xCS) / ( 1. - xCDST);
        jacobian   = (1.-xCDST) > 1e-5
                   ? min(100.,abs(( 1.- xCS) / ( 1. - xCDST)))
                   : 1.;
      // Jacobian for 1->3 splittings, in CS variables.
      } else {
        double q2    = (event[dip.iRecoiler].p()
                       -event[dip.iRadiator].p()).m2Calc();
        double m2ai  = dip.sa1 + m2a + m2i;
        xCS          = (q2 - m2ai - m2a - m2i)
                     / (q2 - m2ai - m2a - m2i - dip.pT2 * dip.xa/dip.z);

        // Jacobian for competing steps, i.e. applied to over-all splitting rate.
        double saij = (xCS - 1.)/xCS * (q2 - m2a) + (m2ai + m2j)/xCS;
        double xbar = (q2 - m2aij - m2k) / (q2 - saij - m2k);

        // Calculate the partonic eCM before the splitting.
        double sHatBefore = (event[dip.iRecoiler].p() + pOther).m2Calc();
        double m2OtherBeam = 0.;

        // Now construct the new recoiler momentum.
        Vec4 q(event[dip.iRecoiler].p()-event[dip.iRadiator].p());
        Vec4 pRadBef(event[dip.iRadiator].p());
        Vec4 pRecBef(event[dip.iRecoiler].p());
        Vec4 qpar(q.px()+pRadBef.px(), q.py()+pRadBef.py(), q.pz(), q.e());
        double qpar2 = qpar.m2Calc();
        double pT2ijt = pow2(pRadBef.px()) + pow2(pRadBef.py());
        Vec4 pRec( (pRecBef - (qpar*pRecBef)/qpar2 * qpar)
                  * sqrt( (lABC(q2,saij,m2k)   - 4.*m2k*pT2ijt)
                         /(lABC(q2,m2aij,m2k) - 4.*m2k*pT2ijt))
                  + qpar * (q2+m2k-saij)/(2.*qpar2) );
        // Calculate the partonic eCM after the splitting.
        double sHatAfter = (pOther + pRec).m2Calc();

        // Calculate Jacobian.
        double rho_bai = sqrt( lABC(sHatBefore, m2k, m2OtherBeam)
                             / lABC(sHatAfter,  m2k, m2OtherBeam) );
        jacobian = rho_bai/xbar
                 * (saij + m2k - q2) / sqrt( lABC(saij, m2k, q2) );

        // Additional jacobian for non-competing steps.
        double saib = m2ai + m2k
          + dip.z/dip.xa * (q2 - m2k - m2ai - m2j - dip.pT2*dip.xa/dip.z);
        jacobian *= (m2ai + m2k - saib) / sqrt( lABC(m2ai, m2k, saib) );

        xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
        // Extra correction from massless to massive propagator.
        jacobian   *= ( 1.- xCS) / ( 1. - xCDST); 

      }
    }

    //if (kinRels->FSRevolutionMode==1) jacobian = kinRels->xcs_fi(z,tnow,Q2);
    if (kinRels->FSRevolutionMode==1)
      jacobian = kinRels->xcs_fi(z,tnow,dip.m2Dip - m2Bef + m2r + m2e);

    fullWeightNow  *= pdfRatio*jacobian;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= pdfRatio*jacobian;

    }*/


    /*if (!multiplyPDFratio(dip, event, splittingNowName, xRecoiler, xNew, idRecoiler, tnow, evType, fullWeightNow, fullWeightsNow) {

    // Firstly reduce by PDF ratio.
    double pdfRatio = 1.;
    pdfScale2 = (useFixedFacScale) ? fixedFacScale2
      : factorMultFac * tnow;
    if (evType > 0) pdfScale2 = tnow;
    if (evType < 0) pdfScale2 = 2.*m2RadBef - tnow;

    pdfScale2 = max(pdfScale2, pT2minPDF);
    double pdfScale2Old = pdfScale2;
    double pdfScale2New = pdfScale2;
    if (forceBranching) pdfScale2Old = infoPtr->Q2Fac();
    if (forceBranching) pdfScale2New = infoPtr->Q2Fac();
    bool inD = hasPDFrec ? beam.insideBounds(xRecoiler, pdfScale2Old) : true; 
    bool inM = hasPDFrec ? beam.insideBounds(xNew, pdfScale2New)      : true; 
    double pdfOld = getXPDF(idRecoiler, xRecoiler, pdfScale2Old, iSysRec,
      &beam, false, z, dip.m2Dip);
    double pdfNew = getXPDF(idRecoiler, xNew, pdfScale2New, iSysRec,
      &beam, false, z, dip.m2Dip);

    if ( hasPDFrec && pdfOld != 0.
      && abs(pdfOld) < tinypdf(xRecoiler) ) return false:

    if (hasPDFrec && pdfOld == 0.) return false;

    // Extreme case of low-scale gluon, for which denominator rapidly
    // approaches zero. In this case, cut off branching probability if
    // daughter PDF fell too rapidly, to avoid large shower weights.
    // (Note: Last resort - would like something more physical here!)
    double xPDFrecoilerLow = getXPDF(idRecoiler, xRecoiler,
      pdfScale2Old*pdfScale2Old/max(teval, pT2minPDF), iSysRec, &beam);
    if ( idRecoiler == 21
      && ( abs(pdfOld/xPDFrecoiler) < 1e-4
        || abs(xPDFrecoilerLow/pdfOld) < 1e-4) ) return false;

    // Reject the splitting if PDF after emission is identically zero.
    if (hasPDFrec && pdfNew == 0.) return false;

    // Set PDF ratio to zero if x-/pT-values are out-of-bounds.
    pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;

    if (!canUseSplitInfo && nEmissons == 2) {
        // Recalculate PDF ratio.
        inM      = (!hasPDFrec) ? true : beam.insideBounds(xNew, pdfScale2); 
        pdfNew   = getXPDF(idRecoiler, xNew, pdfScale2, iSysRec, &beam);
        pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;
    }

    // More last resort.
    if (idRecoiler == 21 && pdfScale2 == pT2minPDF
      && pdfRatio > 50.)
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && pdfRatio > 10.)
      pdfRatio = 0.;
    if (std::isinf(pdfRatio) || std::isnan(pdfRatio))
      pdfRatio = 0.;

    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = min(pdfRatio,5.);

    fullWeightNow  *= pdfRatio;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= pdfRatio;

      mustFindRange = true;
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;

    }*/

    // Firstly reduce by PDF ratio.
    double pdfRatio = 1.;
    pdfScale2 = (useFixedFacScale) ? fixedFacScale2
      : factorMultFac * tnow;
    if (evType == 1) pdfScale2 = tnow;
    if (evType ==-1) pdfScale2 = pow2(2.*sqrt(m2RadBef)-sqrt(tnow));
    if (evType == 2) pdfScale2 = tnow + m2RadBef;

    pdfScale2 = max(pdfScale2, pT2minPDF);
    double pdfScale2Old = pdfScale2;
    double pdfScale2New = pdfScale2;
    if (forceBranching) pdfScale2Old = infoPtr->Q2Fac();
    if (forceBranching) pdfScale2New = infoPtr->Q2Fac();
    bool inD = hasPDFrec ? beam.insideBounds(xRecoiler, pdfScale2Old) : true; 
    bool inM = hasPDFrec ? beam.insideBounds(xNew, pdfScale2New)      : true; 
    double pdfOld = getXPDF(idRecoiler, xRecoiler, pdfScale2Old, iSysRec,
      &beam, false, z, dip.m2Dip);
    double pdfNew = getXPDF(idRecoiler, xNew, pdfScale2New, iSysRec,
      &beam, false, z, dip.m2Dip);

    if ( hasPDFrec && pdfOld != 0.
      && abs(pdfOld) < tinypdf(xRecoiler) ) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    if (hasPDFrec && pdfOld == 0.) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Extreme case of low-scale gluon, for which denominator rapidly
    // approaches zero. In this case, cut off branching probability if
    // daughter PDF fell too rapidly, to avoid large shower weights.
    // (Note: Last resort - would like something more physical here!)
    double xPDFrecoilerLow = getXPDF(idRecoiler, xRecoiler,
      pdfScale2Old*pdfScale2Old/max(teval, pT2minPDF), iSysRec, &beam);
    if ( idRecoiler == 21
      && ( abs(pdfOld/xPDFrecoiler) < 1e-4
        || abs(xPDFrecoilerLow/pdfOld) < 1e-4) ) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Reject the splitting if PDF after emission is identically zero.
    if (hasPDFrec && pdfNew == 0.) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Set PDF ratio to zero if x-/pT-values are out-of-bounds.
    pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;

    if (!canUseSplitInfo) {
      // Jacobian for 1->2 splittings, in CS variables.
      if ( nEmissions!= 2 ) {
        //jacobian   = ( 1.- xCS) / ( 1. - xCDST);
        jacobian   = (1.-xCDST) > 1e-5
                   ? min(100.,abs(( 1.- xCS) / ( 1. - xCDST)))
                   : 1.;
      }

      // Jacobian for 1->3 splittings, in CS variables.
      if ( nEmissions == 2 ) {
        double q2    = (event[dip.iRecoiler].p()
                       -event[dip.iRadiator].p()).m2Calc();
        double m2ai  = dip.sa1 + m2a + m2i;
        xCS          = (q2 - m2ai - m2a - m2i)
                     / (q2 - m2ai - m2a - m2i - dip.pT2 * dip.xa/dip.z);

        // Jacobian for competing steps, i.e. applied to over-all splitting rate.
        double saij = (xCS - 1.)/xCS * (q2 - m2a) + (m2ai + m2j)/xCS;
        double xbar = (q2 - m2aij - m2k) / (q2 - saij - m2k);

        // Calculate the partonic eCM before the splitting.
        double sHatBefore = (event[dip.iRecoiler].p() + pOther).m2Calc();
        double m2OtherBeam = 0.;

        // Now construct the new recoiler momentum.
        Vec4 q(event[dip.iRecoiler].p()-event[dip.iRadiator].p());
        Vec4 pRadBef(event[dip.iRadiator].p());
        Vec4 pRecBef(event[dip.iRecoiler].p());
        Vec4 qpar(q.px()+pRadBef.px(), q.py()+pRadBef.py(), q.pz(), q.e());
        double qpar2 = qpar.m2Calc();
        double pT2ijt = pow2(pRadBef.px()) + pow2(pRadBef.py());
        Vec4 pRec( (pRecBef - (qpar*pRecBef)/qpar2 * qpar)
                  * sqrt( (lABC(q2,saij,m2k)   - 4.*m2k*pT2ijt)
                         /(lABC(q2,m2aij,m2k) - 4.*m2k*pT2ijt))
                  + qpar * (q2+m2k-saij)/(2.*qpar2) );
        // Calculate the partonic eCM after the splitting.
        double sHatAfter = (pOther + pRec).m2Calc();

        // Calculate Jacobian.
        double rho_bai = sqrt( lABC(sHatBefore, m2k, m2OtherBeam)
                             / lABC(sHatAfter,  m2k, m2OtherBeam) );
        jacobian = rho_bai/xbar
                 * (saij + m2k - q2) / sqrt( lABC(saij, m2k, q2) );

        // Additional jacobian for non-competing steps.
        double saib = m2ai + m2k
          + dip.z/dip.xa * (q2 - m2k - m2ai - m2j - dip.pT2*dip.xa/dip.z);
        jacobian *= (m2ai + m2k - saib) / sqrt( lABC(m2ai, m2k, saib) );

        xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
        // Extra correction from massless to massive propagator.
        jacobian   *= ( 1.- xCS) / ( 1. - xCDST); 

        // Recalculate PDF ratio.
        xNew     = xRecoiler / xCDST;
        inM      = (!hasPDFrec) ? true : beam.insideBounds(xNew, pdfScale2); 
        pdfNew   = getXPDF(idRecoiler, xNew, pdfScale2, iSysRec, &beam);
        pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;
      }
    }

    // f(xMother) not stable for xMother excessively close to unity. 
    // As a last resort, reject this splitting.
    if (isColoredRec && (abs(1.- 1./xNew) < 1e-3 || 1.-xNew < 1e-3)) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // More last resort.
    if (idRecoiler == 21 && pdfScale2 == pT2minPDF
      && pdfRatio > 50.)
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && pdfRatio > 10.)
      pdfRatio = 0.;
    if (std::isinf(pdfRatio) || std::isnan(pdfRatio))
      pdfRatio = 0.;

    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = min(pdfRatio,5.);

    if (kinRels->FSRevolutionMode==1)
      jacobian = kinRels->xcs_fi(z,tnow,dip.m2Dip - m2Bef + m2r + m2e);

    fullWeightNow  *= pdfRatio*jacobian;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= pdfRatio*jacobian;

    // Before generating kinematics: Reset sai if the kernel fell on an
    // endpoint contribution.
    if ( nEmissions == 2
      && splits[splittingNowName]->splitInfo.kinematics()->sai == 0.)
      dip.sa1 = 0.;

    if (fullWeightNow == 0. ) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Retrieve argument of alphaS.
    double scale2 =  splits[splittingNowName]->couplingScale2 ( z, tnow, Q2,
      make_pair (event[dip.iRadiator].id(), event[dip.iRadiator].isFinal()),
      make_pair (event[dip.iRecoiler].id(), event[dip.iRecoiler].isFinal()));
    if (scale2 < 0.) scale2 = tnow;
    double talpha = max(scale2, pT2colCut);

    // Reweight to match PDF alpha_s, including corrective terms for
    // renormalisation scale variation. For NLO splitting, all coupling
    // factors have already been covered in the competing phase.
    if (evType==0 || evType==2) alphasReweight(tnow, talpha, dip.system,
      forceFixedAs, wt, fullWeightNow, overWeightNow, renormMultFac);
    auxWeightNow   = overWeightNow;

    // Create muR-variations.
    if (evType==0 || evType==2) calculateMURvariations(doVariationsNow, tnow,
      talpha, dip.system, forceFixedAs, fullWeightsNow);

    // PDF variations.
    if (evType==0 || evType==2) calculatePDFvariations(doVariationsNow, tnow,
      hasPDFrec, iSysRec, idRecoiler, xNew, xRecoiler, pdfScale2, &beam,
      fullWeightsNow);

    if (splits[splittingNowName]->giveUpAndForceSplitting()) {
      wt = 1.;
      auxWeightNow = overWeightNow;
      break;
    }

    setVetoWeight(tnow, z, fullWeightNow, auxWeightNow, wt);

  // Iterate until acceptable pT (or have fallen below pTmin).
  } while (wt < rndmPtr->flat());

  // Not possible to find splitting.
  if ( wt == 0.) return false;

  if (splits[splittingNowName]->giveUpAndForceSplitting()) {
    cout << __PRETTY_FUNCTION__ <<": Forced splitting!" << endl;
  }

  updateWeightsAfterAcceptance(dip.pT2, teval, fullWeightsNow, fullWeightNow,
    overWeightNow, auxWeightNow);

  if (!splittingNowName.empty()) splits[splittingNowName]->setIsEnhanced(false);

  // Done
  return true;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end.

bool DireTimes::tNextDecay_FF(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, const Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  // Lower cut for evolution. Return if no evolution range.
  double pT2endDip = max( pT2sel, pT2cutMin(&dip));
  if (pT2endForce >= 0.) pT2endDip = pT2endForce;
  if (pT2begDip < pT2endDip) { dip.pT2 = 0.; return false; }

  // Variables used inside evolution loop. (Mainly dummy start values.)
  dip.pT2              = pT2begDip;
  double zMinAbs       = 0.0;
  double zMaxAbs       = 1.0;
  double teval         = pT2begDip;
  double wt            = 0.;
  bool   mustFindRange = true;
  int idRadiator       = event[dip.iRadiator].id();
  double m2RadBef      = pow2(particleDataPtr->m0(idRadiator));

  multimap<double,string> newOverestimates [3];
  double overestimateSum [3];

  unordered_map<string,double> fullWeightsNow;
  double fullWeightNow(0.), overWeightNow(0.), auxWeightNow(0.);

  double small_cut = m2RadBef*(1.+1e-3);
  double intFull = getIntBW(idRadiator, 4.*m2RadBef, m2RadBef);

  // Begin evolution loop towards smaller pT values.
  int    nContinue(0), nContinueMax(2000000);

  double enhance = 0.5;
  double enhanceNow = enhance;

  do {

    //double tnow = pT2begDip;
    double tnow = dip.pT2;
    double intNow = getIntBW(idRadiator, tnow, m2RadBef);

    // Force exit if non-Sudakov style forced branching is stuck.
    //if (forceBranching && nContinue >= nContinueMax) {
    if (nContinue >= nContinueMax) {
      ostringstream nc;
      nc << "Warning in DireTimes::" << __func__
         << " giving up proposing resonance decay after " << nContinue
         << " trials ";
      infoPtr->errorMsg(nc.str());
      wt = 0.0; dip.pT2 = tnow = 0.;
      enhanceNow = enhance;
      break;
    }

    // Update event weight after one step. 
    if (wt != 0.) {
      kernelNow = fullWeightsNow;
      for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
        it != fullWeightsNow.end(); ++it ) {
        if (it->first == "base_order_as2") continue;
        double wv = (1. - wt/enhance) / (1.-wt);
        double wv2 = auxWeightNow/overWeightNow
                 * (overWeightNow- it->second)
                 / (auxWeightNow - fullWeightNow);
        rejectProbability[it->first].insert( make_pair(tnow,wv*wv2));
      }
    }

    splittingNowName.clear();
    setupForNextEvolutionStep(wt, dip, fullWeightsNow, fullWeightNow,
      overWeightNow, auxWeightNow);
    enhanceNow = enhance;

    // Leave unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Initialize evolution coefficients at the beginning and
    // reinitialize when crossing c and b flavour thresholds.
    if (mustFindRange
      || tnow < evalpdfstep(event[dip.iRecoiler].id(), tnow, m2cPhys, m2bPhys)*teval) {

      newOverestimates[0].clear();
      newOverestimates[1].clear();
      newOverestimates[2].clear();
      teval       = tnow;
      overestimateSum[0] = 0.;
      overestimateSum[1] = 0.;
      overestimateSum[2] = 0.;

      // Calculate and add user-defined overestimates.
      getNewOverestimates( &dip, event, tnow, m2RadBef, 0., zMinAbs, zMaxAbs,
        newOverestimates);
      addNewOverestimates(newOverestimates, overestimateSum);

      // Store pT at which overestimate has been evaluated. 
      dip.pT2Old = teval;

      // Initialization done for current range.
      mustFindRange = false;
    }

    overestimateSum[1] = 0.;
    newOverestimates[1].clear();
    if ( overestimateSum[0] + overestimateSum[2] < TINYOVERESTIMATE) 
      { dip.pT2 = 0.0; return false; }
    if ( newOverestimates[0].empty() && newOverestimates[2].empty()) 
      { dip.pT2 = 0.0; return false; }

    // Now pick type of evolution measure by probability.
    int evType = getEvolutionMeasureType(&dip, event, overestimateSum,
      tnow, m2RadBef);
    if (evType==-99) { dip.pT2 = 0.0; return false; }

    // Skip any non-resonant splittings.
    if (evType==0 || evType==2) { wt = 0.; continue; }

    // Generate next evolution scale.
    bool forceFixedAs
         = (tnow < pT2colCut) || (event[dip.iRadiator].colType() == 0);
    pair<double,double> rets = getNextEvolutionScale( &dip, event,
      overestimateSum[evType+1], tnow, m2RadBef,
      pT2endDip, pT2freeze, (forceBranching ? -1 : 1), forceFixedAs, evType);
    tnow = rets.first;

    double sij = (evType > 0 ? tnow : pow2(2.*sqrt(m2RadBef)-sqrt(tnow)) );
    if ( evType < 0
      && !splits["Dire_fsr_u1new_22->13hard&-13ResB"]->dipoleAboveCutoff(tnow,
      event[dip.iRadiator].id(), event[dip.iRecoiler].id())){
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      dip.pT2 = tnow;
      continue;
    }

    if (tnow < 0.) { 
      wt = 0.0; dip.pT2 = tnow = 0.;
      double R0 = overestimateSum[evType+1]*rndmPtr->flat();
      if (!newOverestimates[evType+1].empty()) {
        if (newOverestimates[evType+1].lower_bound(R0) == newOverestimates[evType+1].end())
          splittingNowName = newOverestimates[evType+1].rbegin()->second;
        else
          splittingNowName = newOverestimates[evType+1].lower_bound(R0)->second;
      }
      break;
    }

    // Abort evolution if below cutoff scale, or below another branching.
    if ( tnow < pT2endDip ) { dip.pT2 = tnow = wt = 0.; break; }
    if ( tnow < small_cut ) { dip.pT2 = tnow = wt = 0.; break; }

    wt      = 0.0;
    dip.pT2 = tnow;

    // Try user-defined splittings first.
    double R = overestimateSum[evType+1]*rndmPtr->flat();
    double z = -1.;
    int idDaughter, idSister;
    idDaughter = idSister = 0;

    if (!newOverestimates[evType+1].empty()) {

      if (newOverestimates[evType+1].lower_bound(R) == newOverestimates[evType+1].end())
        splittingNowName = newOverestimates[evType+1].rbegin()->second;
      else
        splittingNowName = newOverestimates[evType+1].lower_bound(R)->second;

      // Generate z value and calculate splitting probability.
      getNewSplitting( event, &dip, teval, 0., tnow, zMinAbs,
        zMaxAbs,idRadiator,splittingNowName,forceFixedAs, evType,
        idDaughter, idSister, z, wt, fullWeightsNow, overWeightNow);

      // Store z value for the splitting.
      dip.z      = z;
    }

    // Done for vanishing accept probability.
    if (wt == 0.) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++;
      continue;
    }

    fullWeightNow = fullWeightsNow["base"];

    // Jacobian factors.
    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();
    double jacobian = 1.;
    if (canUseSplitInfo) {
      jacobian
        = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
    }

    fullWeightNow  *= jacobian;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= jacobian;

    if (fullWeightNow == 0. ) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    
    auxWeightNow   = overWeightNow;
    double fac = intNow/intFull;
    fac *= enhanceNow;

    // Multiply with Jacobian.
    fullWeightNow *= fac;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= fac;

    // Ensure that accept probability is positive.
    if (fullWeightNow < 0.) {
      auxWeightNow *= -1.;
    }

    // Reset overestimate if necessary.
    if (fullWeightNow > 0. && fullWeightNow/auxWeightNow > 1e0) {
      double rescale = fullWeightNow/auxWeightNow * 1.15;
      auxWeightNow *= rescale;
    }

    wt = fullWeightNow/auxWeightNow;

    if (wt > 1.) cout << __func__ << " " << __LINE__
    << " " << splittingNowName << " Large weight "
    << wt << " t[gev]=" << sqrt(tnow) << " sij[gev]="
    << sqrt(sij) << endl;

  } while (wt < rndmPtr->flat());

  // Not possible to find splitting.
  if ( wt == 0.) return false;

  if ( fullWeightNow != 0. && overWeightNow != 0. ) {
    double tnow = dip.pT2;
    kernelNow = fullWeightsNow;
    auxNow    = auxWeightNow;
    overNow   = overWeightNow;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it ) {
      // No weight bookkeeping for non-variation components of kernel vector. 
      if (it->first == "base_order_as2") continue;
    double wa = 1./enhanceNow;
      double wa2 = auxWeightNow/overWeightNow
                * it->second/fullWeightNow;
      acceptProbability[it->first].insert(make_pair(tnow,wa*wa2));
        double wv = (1. - wt/enhance) / (1.-wt);

      if (auxWeightNow == fullWeightNow && overWeightNow == fullWeightNow)
        rejectProbability[it->first].insert( make_pair(tnow, wv));
      else {
        double wv2  = auxWeightNow/overWeightNow
                  * (overWeightNow- it->second)
                  / (auxWeightNow - fullWeightNow);
        rejectProbability[it->first].insert( make_pair(tnow, wv*wv2));
      }
    }
  }

  // Done
  return true;

}

//--------------------------------------------------------------------------

// Evolve a QCD dipole end.

bool DireTimes::tNextDecay_FI(double pT2begDip, double pT2sel,
  DireTimesEnd& dip, const Event& event, double pT2endForce, double pT2freeze,
  bool forceBranching) {

  // Lower cut for evolution. Return if no evolution range.
  double pT2endDip = max( pT2sel, pT2cutMin(&dip));
  if (pT2endForce >= 0.) pT2endDip = pT2endForce;
  if (pT2begDip < pT2endDip) { dip.pT2 = 0.; return false; }

  BeamParticle& beam = (dip.isrType == 1) ? *beamAPtr : *beamBPtr;

  // Variables used inside evolution loop. (Mainly dummy start values.)
  dip.pT2              = pT2begDip;
  double zMinAbs       = 0.0;
  double zMaxAbs       = 1.0;
  double teval         = pT2begDip;
  double xPDFrecoiler  = 0.;
  double wt            = 0.;
  bool   mustFindRange = true;
  int idRadiator       = event[dip.iRadiator].id();
  int idRecoiler       = event[dip.iRecoiler].id();
  double m2RadBef      = pow2(particleDataPtr->m0(idRadiator));
  bool isColoredRec    = event[dip.iRecoiler].colType()!=0;
  int iSysRec          = dip.systemRec;
  double xRecoiler     = beam[iSysRec].x();
  bool   hasPDFrec     = hasPDF(idRecoiler);

  // Return if no Bjorken-x larger than the current value can be produced, or
  // if the starting scale is below the resonance peak.
  if (1.-m2RadBef/dip.m2Dip < xRecoiler || pT2begDip < m2RadBef) {
    dip.pT2 = 0.; return false;
  }

  double pT2minPDF = pT2cutMin(&dip);
  if (particleDataPtr->colType(idRecoiler) != 0) pT2minPDF = pT2colCut;

  multimap<double,string> newOverestimates [3];
  double overestimateSum [3];

  unordered_map<string,double> fullWeightsNow;
  double fullWeightNow(0.), overWeightNow(0.), auxWeightNow(0.);

  double small_cut = m2RadBef*(1.+1e-3);
  double intFull = getIntBW(idRadiator, 4.*m2RadBef, m2RadBef);

  // Begin evolution loop towards smaller pT values.
  int    loopTinyPDFdau = 0;
  int    nContinue(0), nContinueMax(2000000);
  bool   hasTinyPDFdau  = false;

  double enhance = 1.;

  do {

    //double tnow = pT2begDip;
    double tnow = dip.pT2;
    double intNow = getIntBW(idRadiator, tnow, m2RadBef);

    // Force exit if non-Sudakov style forced branching is stuck.
    //if (forceBranching && nContinue >= nContinueMax) {
    if (nContinue >= nContinueMax) {
      ostringstream nc;
      nc << "Warning in DireTimes::" << __func__
         << " giving up proposing resonance decay after " << nContinue
         << " trials ";
      infoPtr->errorMsg(nc.str());
      wt = 0.0; dip.pT2 = tnow = 0.;
      break;
    }

    // Update event weight after one step. 
    if (wt != 0.) {
      kernelNow = fullWeightsNow;
      for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
        it != fullWeightsNow.end(); ++it ) {
        if (it->first == "base_order_as2") continue;
        double wv = (1. - wt/enhance) / (1.-wt);
        rejectProbability[it->first].insert( make_pair(tnow,wv));
      }
    }

    splittingNowName.clear();
    setupForNextEvolutionStep(wt, dip, fullWeightsNow, fullWeightNow,
      overWeightNow, auxWeightNow);

    // Leave unconverted for now.
    if ( event[dip.iRecoiler].idAbs() == 4 && tnow <= m2cPhys) {
      dip.pT2 = 0.; return false;
    }
    if ( event[dip.iRecoiler].idAbs() == 5 && tnow <= m2bPhys) {
      dip.pT2 = 0.; return false;
    }

    // Finish evolution if PDF vanishes.
    double tnew = (useFixedFacScale) ? fixedFacScale2 : factorMultFac*tnow;
    bool inNew  = (hasPDFrec)
                ? beam.insideBounds(xRecoiler, max(tnew, pT2colCut) ) : 1.0;

    if (hasPDFrec && !inNew) { dip.pT2 = 0.0; return false; }

    // Bad sign if repeated looping with small daughter PDF, so fail.
    // (Example: if all PDF's = 0 below Q_0, except for c/b companion.)
    if (hasTinyPDFdau) ++loopTinyPDFdau;
    if (hasPDFrec && loopTinyPDFdau > MAXLOOPTINYPDF) {
      infoPtr->errorMsg("Warning in DireTimes::pT2nextQCD_FI: "
      "small daughter PDF");
      dip.pT2 = 0.0;
      return false;
    }

    // Initialize evolution coefficients at the beginning and
    // reinitialize when crossing c and b flavour thresholds.
    double pdfScale2 = useFixedFacScale ? fixedFacScale2 : factorMultFac*tnow;
    pdfScale2        = max(pdfScale2, pT2minPDF);
    if (mustFindRange
      || tnow < evalpdfstep(event[dip.iRecoiler].id(), tnow, m2cPhys, m2bPhys)*teval) {

      newOverestimates[0].clear();
      newOverestimates[1].clear();
      newOverestimates[2].clear();
      teval       = tnow;
      overestimateSum[0] = 0.;
      overestimateSum[1] = 0.;
      overestimateSum[2] = 0.;

      // Parton density of daughter at current scale.
      xPDFrecoiler = getXPDF(idRecoiler, xRecoiler, pdfScale2, iSysRec, &beam);
      if ( hasPDFrec && xPDFrecoiler != 0.
        && abs(xPDFrecoiler) < 1e-15) {
        int sign      = (xPDFrecoiler > 0.) ? 1 : -1;
        xPDFrecoiler  = sign*tinypdf(xRecoiler);
        hasTinyPDFdau = true;
      }

      double xMin = (hasPDFrec) ? xRecoiler : 0.;

      // Calculate and add user-defined overestimates.
      getNewOverestimates( &dip, event, tnow, m2RadBef, xMin, zMinAbs, zMaxAbs,
        newOverestimates);
      addNewOverestimates(newOverestimates, overestimateSum);

      // Store pT at which overestimate has been evaluated. 
      dip.pT2Old = teval;

      // Initialization done for current range.
      mustFindRange = false;
    }

    overestimateSum[1] = 0.;
    newOverestimates[1].clear();
    if ( overestimateSum[0] + overestimateSum[2] < TINYOVERESTIMATE) 
      { dip.pT2 = 0.0; return false; }
    if ( newOverestimates[0].empty() && newOverestimates[2].empty()) 
      { dip.pT2 = 0.0; return false; }

    // Now pick type of evolution measure by probability.
    int evType = getEvolutionMeasureType(&dip, event, overestimateSum,
      tnow, m2RadBef);
    if (evType==-99) { dip.pT2 = 0.0; return false; }

    // Skip any non-resonant splittings.
    if (evType==0 || evType==2) { wt = 0.; continue; }

    // Generate next evolution scale.
    bool forceFixedAs
         = (tnow < pT2colCut) || (event[dip.iRadiator].colType() == 0);
    pair<double,double> rets = getNextEvolutionScale( &dip, event,
      overestimateSum[evType+1], tnow, m2RadBef,
      pT2endDip, pT2freeze, (forceBranching ? -1 : 1), forceFixedAs, evType);
    tnow = rets.first;

    if (tnow < 0.) { 
      wt = 0.0; dip.pT2 = tnow = 0.;
      double R0 = overestimateSum[evType+1]*rndmPtr->flat();
      if (!newOverestimates[evType+1].empty()) {
        if (newOverestimates[evType+1].lower_bound(R0) == newOverestimates[evType+1].end())
          splittingNowName = newOverestimates[evType+1].rbegin()->second;
        else
          splittingNowName = newOverestimates[evType+1].lower_bound(R0)->second;
      }
      break;
    }

    // Abort evolution if below cutoff scale, or below another branching.
    if ( tnow < pT2endDip ) { dip.pT2 = tnow = wt = 0.; break; }
    if ( tnow < small_cut ) { dip.pT2 = tnow = wt = 0.; break; }

    wt      = 0.0;
    dip.pT2 = tnow;

    // Try user-defined splittings first.
    double R = overestimateSum[evType+1]*rndmPtr->flat();
    double z = -1.;
    int idDaughter, idSister;
    idDaughter = idSister = 0;

    if (!newOverestimates[evType+1].empty()) {

      if (newOverestimates[evType+1].lower_bound(R) == newOverestimates[evType+1].end())
        splittingNowName = newOverestimates[evType+1].rbegin()->second;
      else
        splittingNowName = newOverestimates[evType+1].lower_bound(R)->second;

      // Generate z value and calculate splitting probability.
      double xMin = (hasPDFrec) ? xRecoiler : 0.;
      getNewSplitting( event, &dip, teval, xMin, tnow, zMinAbs,
        zMaxAbs,idRadiator,splittingNowName,forceFixedAs, evType,
        idDaughter, idSister, z, wt, fullWeightsNow, overWeightNow);

      // Store z value for the splitting.
      dip.z      = z;
    }

    // Done for vanishing accept probability.
    if (wt == 0.) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++;
      continue;
    }

    fullWeightNow = fullWeightsNow["base"];

    double m2Bef(0.), m2r(0.), m2e(0.), m2s(0.), m2a(0.), m2i(0.),
      m2j(0.), m2aij(0.), m2k(0.);
    getMassesforSplitting(dip, event, idDaughter,
      m2Bef, m2r, m2e, m2s, m2a, m2i, m2j, m2aij, m2k);

    bool canUseSplitInfo = splits[splittingNowName]->canUseForBranching();

    // Recalculate the kinematicaly available dipole mass.
    double Q2     = dip.m2Dip - m2Bef + m2r + m2e;
    double virt   = (evType > 0 ? tnow : pow2(2.*sqrt(m2RadBef)-sqrt(tnow)) );
    double xCS    = dip.m2Dip/(dip.m2Dip+virt);
    double xCDST  = xCS*( 1. + (m2Bef-m2r-m2e)/Q2 );
    double xNew   = xRecoiler / xCDST;

    // Jacobian factors.
    double jacobian = 1.;
    if (canUseSplitInfo) {
      jacobian
        = splits[splittingNowName]->getJacobian(event,partonSystemsPtr);
      unordered_map<string,double> psvars
        = splits[splittingNowName]->getPhasespaceVars( event, partonSystemsPtr);
      xNew = psvars["xInAft"];
    }

    // Firstly reduce by PDF ratio.
    double pdfRatio = 1.;
    pdfScale2 = (useFixedFacScale) ? fixedFacScale2
      : factorMultFac * tnow;
    if (evType > 0) pdfScale2 = tnow;
    if (evType < 0) pdfScale2 = pow2(2.*sqrt(m2RadBef)-sqrt(tnow));

    pdfScale2 = max(pdfScale2, pT2minPDF);
    double pdfScale2Old = pdfScale2;
    double pdfScale2New = pdfScale2;
    bool inD = hasPDFrec ? beam.insideBounds(xRecoiler, pdfScale2Old) : true; 
    bool inM = hasPDFrec ? beam.insideBounds(xNew, pdfScale2New)      : true; 
    double pdfOld = getXPDF(idRecoiler, xRecoiler, pdfScale2Old, iSysRec,
      &beam, false, z, dip.m2Dip);
    double pdfNew = getXPDF(idRecoiler, xNew, pdfScale2New, iSysRec,
      &beam, false, z, dip.m2Dip);

    if ( hasPDFrec && pdfOld != 0.
      && abs(pdfOld) < tinypdf(xRecoiler) ) {
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    if (hasPDFrec && pdfOld == 0.) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Extreme case of low-scale gluon, for which denominator rapidly
    // approaches zero. In this case, cut off branching probability if
    // daughter PDF fell too rapidly, to avoid large shower weights.
    // (Note: Last resort - would like something more physical here!)
    double xPDFrecoilerLow = getXPDF(idRecoiler, xRecoiler,
      pdfScale2Old*pdfScale2Old/max(teval, pT2minPDF), iSysRec, &beam);
    if ( idRecoiler == 21
      && ( abs(pdfOld/xPDFrecoiler) < 1e-4
        || abs(xPDFrecoilerLow/pdfOld) < 1e-4) ) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Reject the splitting if PDF after emission is identically zero.
    if (hasPDFrec && pdfNew == 0.) {
      hasTinyPDFdau = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // Set PDF ratio to zero if x-/pT-values are out-of-bounds.
    pdfRatio = (inD && inM) ? pdfNew/pdfOld : 0.;

    // f(xMother) not stable for xMother excessively close to unity. 
    // As a last resort, reject this splitting.
    if (isColoredRec && (abs(1.- 1./xNew) < 1e-3 || 1.-xNew < 1e-3)) {
      mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    // More last resort.
    if (idRecoiler == 21 && pdfScale2 == pT2minPDF
      && pdfRatio > 50.)
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && pdfRatio > 10.)
      pdfRatio = 0.;
    if (std::isinf(pdfRatio) || std::isnan(pdfRatio))
      pdfRatio = 0.;

    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = 0.;
    if (abs(idRecoiler) == 11 && (xNew < LEPTONXMIN || xNew > LEPTONXMAX))
      pdfRatio = min(pdfRatio,5.);

    if (kinRels->FSRevolutionMode==1) jacobian = kinRels->xcs_fi(z, tnow, Q2);

    fullWeightNow  *= pdfRatio*jacobian;
    for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
      it != fullWeightsNow.end(); ++it )
      it->second   *= pdfRatio*jacobian;

    if (fullWeightNow == 0. ) {
      //mustFindRange = true;
      fullWeightsNow.clear();
      wt = fullWeightNow = overWeightNow = auxWeightNow = 0.;
      nContinue++; continue;
    }

    auxWeightNow   = overWeightNow;
    wt = fullWeightNow/auxWeightNow;

    wt *= intNow/intFull;
    wt *= enhance;

    if (wt > 1.) cout << __func__ << " "
    << __LINE__ << " Large weight " << wt << endl;

  // Iterate until acceptable pT (or have fallen below pTmin).
  } while (wt < rndmPtr->flat());

  // Not possible to find splitting.
  if ( wt == 0.) return false;

  // Update accepted event weight.
  double tnow = dip.pT2;
  kernelNow = fullWeightsNow;
  for ( unordered_map<string,double>::iterator it = fullWeightsNow.begin();
    it != fullWeightsNow.end(); ++it ) {
    if (it->first == "base_order_as2") continue;
    double wa = 1./enhance;
    acceptProbability[it->first].insert(make_pair(tnow,wa));
    rejectProbability[it->first].insert( make_pair(tnow, 1.0));
  }

  // Done
  return true;

}

//--------------------------------------------------------------------------

pair<double,double> DireTimes::getNextEvolutionScale( DireTimesEnd* dip,
  const Event & event, double overestimateInt, double tOld, double tMin,
  double pT2endDip, double tFreeze, int algoType, bool fixedCoupling,
  int evType) {

  double tRet = 0.;
  int idRad
    = event[dip->iRadiator].id();
  double mRes
    = particleDataPtr->m0(idRad);
  double width
    = particleDataPtr->particleDataEntryPtr(idRad)->resWidth(idRad,mRes);
  double weight = 1.;

  //if (evType==0) tRet = getNextTQCD( dip, overestimateInt, tOld,
  if (evType==0 || evType==2) tRet = getNextTQCD( dip, overestimateInt, tOld,
    pT2endDip, tFreeze, algoType, fixedCoupling);
  // Note: For resonance case, assume that overestimateInt is already
  // multiplied by coupling factors.
  else tRet = getNextQ2Res( dip, width, mRes, tOld, tMin);

  return make_pair(tRet,weight);

}

//--------------------------------------------------------------------------

double DireTimes::getIntBW(int idRad, double tMax, double tMin) {

  if (tMax < tMin) return 0.0;

  // Get rate of Breit-Wigner-type branchings.
  double mRes
    = particleDataPtr->m0(idRad);
  double width
    = particleDataPtr->particleDataEntryPtr(idRad)->resWidth(idRad,mRes);
  double m2Res = pow2(mRes);

  bool hasBW = (mRes>TINYMASS && width>1e-10);
  if (!hasBW) return 0.0;

  // Calculate primitive at integration boundaries.
  double bwImin = (hasBW) ? atan((tMin-m2Res)/(mRes*width)) : 0.;
  double bwImax = (hasBW) ? atan((tMax-m2Res)/(mRes*width)) : 0.;

  // Integral over complete phase space.
  return (bwImax-bwImin);

}

//--------------------------------------------------------------------------

int DireTimes::getEvolutionMeasureType(DireTimesEnd* dip, const Event & event,
  double zIntOverestimate [], double tMax,
  double tMin) {

  int ret = -99;

  if ( zIntOverestimate[1]>TINYOVERESTIMATE
    && zIntOverestimate[0]<TINYOVERESTIMATE
    && zIntOverestimate[2]<TINYOVERESTIMATE) {
    return 0;
  }

  // Get rate of Breit-Wigner-type branchings.
  int idRad
    = event[dip->iRadiator].id();
  double mRes
    = particleDataPtr->m0(idRad);
  double width
    = particleDataPtr->particleDataEntryPtr(idRad)->resWidth(idRad,mRes);
  double m2Res = pow2(mRes);
  double smax = tMax;
  double smin = tMin;

  bool hasBW = (mRes>TINYMASS && width>1e-10);

  // Calculate primitive at integration boundaries.
  double bwImin = (hasBW) ? atan((smin-m2Res)/(mRes*width)) : 0.;
  double bwImax = (hasBW) ? atan((smax-m2Res)/(mRes*width)) : 0.;
  // Integral over complete phase space.
  double bwInt=(bwImax-bwImin);
  double prob0 = bwInt * zIntOverestimate[0];
  double prob2 = bwInt * zIntOverestimate[2];
  //double prob0 = bwInt;
  //double prob2 = bwInt;

  // Get rate of Sudakov-type branchings;
  double couplint = alphaS2piOverestimate*zIntOverestimate[1];
  double prob1 = 0.;
  if (zIntOverestimate[1]>TINYOVERESTIMATE) {
    if (tMin < TINYMASS) {
      prob1 = 1.; // sudakov normalized if splitting function diverges.
    } else {
      prob1 = 1. - exp (-(couplint*log(tMax)-couplint*log(tMin)));
    }
  }

  double prob01=prob0+prob1;
  double prob012=prob0+prob1+prob2;
  double typeRN = prob012*rndmPtr->flat();

  if (typeRN < prob0)                     ret = -1;
  if (typeRN > prob0  && typeRN < prob01) ret =  0;
  if (typeRN > prob01)                    ret =  1;

  return ret;

}

//--------------------------------------------------------------------------

double DireTimes::getNextTQCD( DireTimesEnd*, double overestimateInt,
  double tOld, double tMin, double tFreeze, int algoType,
  bool fixedCoupling) {

  // Return if below cut-off.
  double asOver     = (usePDFalphas || fixedCoupling)
                    ? alphaS2piOverestimate : alphaS2pi;
  double rnd        = rndmPtr->flat();

  // Use cut-off on random numbers to account for minimal t. Only implemented
  // for t-independent overestimates.
  if (usePDFalphas || alphaSorder == 0) {
    double rndMin     = pow( tMin/tOld, asOver * overestimateInt);
    if (rnd < rndMin) return -1.*tMin;
  }

  // Determine LambdaQCD.
  double b0            = 4.5;
  double Lambda2       = Lambda3flav2;
  if (tOld > m2b) {
    b0       = 23./6.;
    Lambda2  = Lambda5flav2;
  } else if (tOld > m2c) {
    b0       = 25./6.;
    Lambda2  = Lambda4flav2;
  } else {
    b0       = 27./6.;
    Lambda2  = Lambda3flav2;
  }
  // A change of renormalization scale expressed by a change of Lambda.
  Lambda2 /= renormMultFac;

  // Generate next evolution scale.
  double tForAlphaS=tOld;
  double tnow = tOld;

  if (algoType<0)
    return pow(tMin+tFreeze,rnd) / pow(tnow+tFreeze,rnd-1) - tFreeze;

  if (usePDFalphas || fixedCoupling) {
    double fac = pow( rnd, 1. / (alphaS2piOverestimate * overestimateInt));
    tnow = (tnow+tFreeze) * fac - tFreeze;

  } else if (alphaSorder == 0) {
    tnow = (tnow+tFreeze) * pow( rnd,
      1. / (alphaS2pi * overestimateInt) ) - tFreeze;

  } else if (alphaSorder == 1) {
    tnow = Lambda2 * pow( (tnow+tFreeze) / Lambda2,
      pow( rnd, b0 / overestimateInt) ) - tFreeze;

  } else {
    do {
      tnow = Lambda2 * pow( (tnow+tFreeze) / Lambda2,
        pow(rndmPtr->flat(), b0 / overestimateInt) ) - tFreeze;
      tForAlphaS = renormMultFac * max( tnow+tFreeze,
        pow2(LAMBDA3MARGIN) * Lambda3flav2);
    } while (alphaS.alphaS2OrdCorr(tForAlphaS) < rndmPtr->flat()
      && tnow > tMin);
  }

  // Done.
  return tnow;

}

//--------------------------------------------------------------------------

double DireTimes::getNextQ2Res( DireTimesEnd*,
  double widthRes, double mRes, double smax, double smin) {

  double m2Res = pow2(mRes);

  // Calculate primitive at integration boundaries.
  double Imin = 1./(mRes*widthRes)*atan((smin-m2Res)/(mRes*widthRes));
  double Imax = 1./(mRes*widthRes)*atan((smax-m2Res)/(mRes*widthRes));
  // Integral over complete phase space.
  double intBW=(Imax-Imin);

  //smin -= m2Res;
  //smax -= m2Res;
  //double nummin = m2Res*pow2(widthRes) + pow2(smin-m2Res);
  //double nummax = m2Res*pow2(widthRes) + pow2(smax-m2Res);

  double ret = 0.;
  double ntries = 0.; 

  // Generate q2 according to Breit-Wigner.
  bool success = true;
  do {

    ntries += 1.;
    double rn = rndmPtr->flat();
    double q2 = m2Res + mRes*widthRes*tan( mRes*widthRes*(Imax-rn*intBW));
    //double p = 1. / (pow(nummax/nummin,rn) / nummax);  
    //double q2 = m2Res + sqrt(p-m2Res*pow2(widthRes));
    ret = q2; 
    if (q2>smax || q2<smin || ret < 0.) {success = false; continue; }
    success = true;

  } while (!success);

  return ret;

}

//--------------------------------------------------------------------------

// Get auxiliary variable for brnaching of a QCD dipole end.

bool DireTimes::getNextZCollQCD( DireTimesEnd* dip, double zMin, double zMax,
  double, double ) {

  // Choose logarithmically.
  dip->xa = zMax * pow( zMax/zMin, -rndmPtr->flat());

  // Done
  return true;

}

//--------------------------------------------------------------------------

bool DireTimes::getNextVirtQCD( DireTimesEnd* dip, double, double,
  double, double) {

  double v   = rndmPtr->flat();
  double m2j = dip->mass[2];
  dip->sa1 = v / (1.-v) * ( dip->pT2*dip->xa/dip->z + m2j);

  // Done
  return true;

}

//--------------------------------------------------------------------------

bool DireTimes::branch( Event& event, bool ) {

  if (abs(dipSel->pT2 - pT2cutMin(dipSel)) < 1e-10) return false;

  double pT2 = (dipSel != 0) ? dipSel->pT2 : 0.;
  int isFin = (dipSel != 0) ? event[dipSel->iRecoiler].isFinal() : -1;

  // This function is a wrapper for setting up the branching
  // kinematics.
  bool hasBranched = false;
  if ( event[dipSel->iRecoiler].isFinal())
       hasBranched = branch_FF(event, false, &splitInfoSel);
  else hasBranched = branch_FI(event, false, &splitInfoSel);

  if ( isFin && hasBranched) infoPtr->errorMsg(
    "Info in DireTimes: Successfully performed FF branching " + splittingSelName);
  if (!isFin && hasBranched) infoPtr->errorMsg(
    "Info in DireTimes: Successfully performed FI branching " + splittingSelName);

  if (hasBranched) direInfoPtr->message(1) << __func__ << ":" << __LINE__
  << " generated " << splittingSelName << " at tEvol=" << pT2 << endl;

  if (hasBranched) {
    if (abs(splits[splittingSelName]->typeEvolutionMeasure())==1)
      direInfoPtr->usePTLast(true);
    direInfoPtr->pTLast(sqrt(pT2));
    direInfoPtr->pTLastMin(min(direInfoPtr->pTLastMin(),sqrt(pT2)));
  }

  // Done.
  return hasBranched;

}

//--------------------------------------------------------------------------

// ME corrections and kinematics that may give failure.
// Notation: radBef, recBef = radiator, recoiler before emission,
//           rad, rec, emt = radiator, recoiler, emitted efter emission.
//           (rad, emt distinguished by colour flow for g -> q qbar.)

bool DireTimes::branch_FF( Event& event, bool trial,
  DireSplitInfo* split ) {

  // Check if the first emission should be studied for removal.
  bool physical      = true;
  bool canMergeFirst = (mergingHooksPtr != 0)
                     ? mergingHooksPtr->canVetoEmission() : false;

  // Find initial radiator and recoiler particles in dipole branching.
  int iRadBef      = (!trial) ? dipSel->iRadiator : split->iRadBef;
  int iRecBef      = (!trial) ? dipSel->iRecoiler : split->iRecBef;

  // Find their momenta, with special sum for global recoil.
  Vec4 pRadBef(event[iRadBef].p());
  Vec4 pRecBef(event[iRecBef].p());

  // Get splitting variables.
  string name = (!trial) ? splittingSelName : split->splittingSelName;
  if (!trial) splits[name]->splitInfo.store(*split);

  unordered_map<string,double> psp(splits[name]->getPhasespaceVars(event, partonSystemsPtr));

  //double pT2    = (!trial) ? dipSel->pT2   : split->kinematics()->pT2;
  double tEvol  = (!trial) ? dipSel->pT2   : split->kinematics()->pT2;
  double tDire  = tEvol;
  double z      = (!trial) ? dipSel->z     : split->kinematics()->z ;
  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { tDire = psp["pT2"]; z = psp["z"]; }

  if (name==testname && testps=="FF") direInfoPtr->message(1)
  << endl << endl << __func__ << " name=" << name
  << " " << event[iRecBef].id() << " tEvol=" << tEvol << endl;

  double m2Dip  = (!trial) ? dipSel->m2Dip : split->kinematics()->m2Dip;
  // Calculate CS variables.
  double yCS    = tDire/m2Dip / (1.-z);
  double zCS    = ( 1. - z - tDire/m2Dip - pow2(1.-z) )
                / ( 1. - z - tDire/m2Dip);

  // Get flavour of splitting.
  int flavour = (!trial) ? dipSel->flavour : split->emtAft()->id;
  // Name of the splitting.
  int nEmissions = splits[name]->nEmissions();

  // Evolution type, in case different from default Dire definition.
  int evType = splits[name]->typeEvolutionMeasure();

  if ( nEmissions == 2 && !split->useForBranching) {
    if ((!trial && splittingSel->is_qcd) || (trial && splits[name]->is_qcd))
      flavour = 21;
    else
      flavour = 22;
  }

  // Default flavours and colour tags for new particles in dipole branching.
  int idRad        = event[iRadBef].id();
  int idEmt        = abs(flavour);
  int colRad       = event[iRadBef].col();
  int acolRad      = event[iRadBef].acol();
  int colEmt       = 0;
  int acolEmt      = 0;
  iSysSel          = (!trial) ? dipSel->system : split->system;
  int iSysSelRec   = (!trial) ? dipSel->systemRec : split->system;
  int colType = -2;
  if (!trial && dipSel->colType > 0) colType = 2;
  if ( trial && idRad > 0)           colType = 2;
  if (!trial && (dipSel->gamType == 1 || abs(dipSel->weakType) > 0)) colType=0;
  if ( trial && (idRad==22 || idRad==23 || idRad==24 || idRad==25))  colType=0;

  if ( split->useForBranching
    && (particleDataPtr->colType(split->emtAft()->id)  == 0
    || (particleDataPtr->colType(split->emtAft2()->id) == 0
      && nEmissions == 2)))
    colType = 0;

  if (flavour == 22 || flavour == 23 || flavour == 25) ;

  // New colour tag required for gluon emission.
  else if (flavour == 21 && colType > 0) {
    colEmt  = colRad;
    colRad  = event.nextColTag();
    acolEmt = colRad;
  } else if (flavour == 21) {
    acolEmt = acolRad;
    acolRad = event.nextColTag();
    colEmt  = acolRad;
  // New flavours for g -> q qbar; split colours.
  } else if (colType > 0) {
    idEmt   = abs(flavour);
    idRad   = -idEmt;
    colEmt  = colRad;
    colRad  = 0;
  } else if (colType < 0) {
    idEmt   = -abs(flavour);
    idRad   = -idEmt;
    acolEmt  = acolRad;
    acolRad  = 0;
  }

  if (split->useForBranching) {
    idRad   = event[iRadBef].id();
    colRad  = event[iRadBef].col();
    acolRad = event[iRadBef].acol();
    colEmt  = 0;
    acolEmt = 0;
    // Now reset if splitting information is available.
    if (split->radAft()->id   != 0) idRad   = split->radAft()->id;
    if (split->emtAft()->id   != 0) idEmt   = split->emtAft()->id;
    if (split->radAft()->col  > -1) colRad  = split->radAft()->col;
    if (split->radAft()->acol > -1) acolRad = split->radAft()->acol;
    if (split->emtAft()->col  > -1) colEmt  = split->emtAft()->col;
    if (split->emtAft()->acol > -1) acolEmt = split->emtAft()->acol;

    if (nEmissions == 2) {
      /*if ( split->extras.find("idRadInt") != split->extras.end() )
        idRad = int(split->extras["idRadInt"]);
      if ( split->extras.find("idEmtInt") != split->extras.end() )
        idEmt = int(split->extras["idEmtInt"]);
      if ( split->extras.find("colRadInt") != split->extras.end() )
        colRad = int(split->extras["colRadInt"]);
      if ( split->extras.find("acolRadInt") != split->extras.end() )
        acolRad = int(split->extras["acolRadInt"]);
      if ( split->extras.find("colEmtInt") != split->extras.end() )
        colEmt = int(split->extras["colEmtInt"]);
      if ( split->extras.find("acolEmtInt") != split->extras.end() )
        acolEmt = int(split->extras["acolEmtInt"]);*/
      if ( split->idRadInt != 0)    idRad   = split->idRadInt;
      if ( split->idEmtInt != 0)    idEmt   = split->idEmtInt;
      if ( split->colRadInt != -1)  colRad  = split->colRadInt;
      if ( split->acolRadInt != -1) acolRad = split->acolRadInt;
      if ( split->colEmtInt != -1)  colEmt  = split->colEmtInt;
      if ( split->acolEmtInt != -1) acolEmt = split->acolEmtInt;
    }
  }

  // Get particle masses.
  // Radiator before splitting.
  double m2Bef = particleDataPtr->isResonance(event[iRadBef].id())
               ? getMass(event[iRadBef].id(),3,event[iRadBef].mCalc())
               : (event[iRadBef].idAbs() < 6 || event[iRadBef].id() == 21
               || event[iRadBef].id() == 22)
               ? getMass(event[iRadBef].id(),2)
               : getMass(event[iRadBef].id(),1);
  // Radiator after splitting.
  double m2r   = particleDataPtr->isResonance(idRad)
                 && idRad == event[iRadBef].id()
               ? getMass(idRad,3,event[iRadBef].mCalc())
               : (abs(idRad) < 6 || idRad == 21 || idRad == 22)
               ? getMass(idRad,2)
               : getMass(idRad,1);
  // Recoiler. 
  double m2s   = particleDataPtr->isResonance(event[iRecBef].id())
               ? getMass(event[iRecBef].id(),3,event[iRecBef].mCalc())
               : (event[iRecBef].idAbs() < 6 || event[iRecBef].id() == 21
               || event[iRecBef].id() == 22)
               ? getMass(event[iRecBef].id(),2)
               : getMass(event[iRecBef].id(),1);
  // Emission.
  double m2ex = (abs(idEmt) < 6 || idEmt == 21 || idEmt == 22)
              ? getMass(idEmt,2) : getMass(idEmt,1);
  double m2e  = (!trial) ? m2ex
    : ( (split->kinematics()->m2EmtAft > 0.) ? split->kinematics()->m2EmtAft
                                            : m2ex);
  if (split->useForBranching) {
    m2r = split->kinematics()->m2RadAft;
    m2e = split->kinematics()->m2EmtAft;
  }

  // Adjust the dipole kinematical mass to accomodate masses after branching.
  double Q2  = m2Dip + m2Bef - m2r - m2e;
  // Q2 already correctly stored in splitInfo.
  if (trial) Q2 = m2Dip;

  // Calculate CS variables.
  double kappa2 = tDire/Q2;
  yCS           = kappa2 / (1.-z);
  zCS           = ( 1. - z - kappa2 - pow2(1.-z) ) / ( 1. - z - kappa2);

  // changes for virtuality ordering
  if (abs(evType)==1) {
    double virt = (evType > 0 ? tEvol : pow2(2.*sqrt(m2Bef)-sqrt(tEvol)));
    yCS = virt/m2Dip;
    zCS = 1. - (1.-z)/(1.-yCS);
  }

  if (evType==2) { 
    double virt = tEvol + m2Bef;
    yCS = virt / m2Dip;
    zCS = 1. - (1.-z)/(1.-yCS);
  }

  double m2Emt  = m2e;
  double m2Rad  = m2r;
  double sai    = (!trial) ? dipSel->sa1 : split->kinematics()->sai;
  double xa     = (!trial) ? dipSel->xa  : split->kinematics()->xa;
  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { sai = psp["sai"]; xa = psp["xa"]; }

  // Auxiliary angle.
  double phi_kt = (!trial)
    ? ((dipSel->phi >= 0.)              ? dipSel->phi
                                        : 2.*M_PI*rndmPtr->flat())
    : ((split->kinematics()->phi >= 0.) ? split->kinematics()->phi
                                        : 2.*M_PI*rndmPtr->flat());

  // Second angle for 1->3 splitting.
  double phiX = 0.0;
  if (nEmissions == 2)
    phiX = (!trial)
      ? ((dipSel->phia1 >= 0.)             ? dipSel->phia1
                                           : 2.*M_PI*rndmPtr->flat())
      : ((split->kinematics()->phi2 >= 0.) ? split->kinematics()->phi2
                                           : 2.*M_PI*rndmPtr->flat());

  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { phi_kt = psp["phi"]; phiX = psp["phi2"]; }

  Vec4 pRad, pEmt, pRec;
  // Get dipole 4-momentum.
  Vec4 q(pRadBef + pRecBef);
  double q2 = q.m2Calc();

  // 1->3 splittings generated in CS variables directly.
  double m2a(0.), m2i(0.), m2j(0.), m2ai(0.), m2k(0.), m2aij(0.);
  if (nEmissions == 2) {
    m2a   = getMass((!trial) ? dipSel->flavour : split->emtAft()->id,2); 
    m2i   = getMass((!trial) ? dipSel->flavour : split->emtAft()->id,2); 
    m2j   = m2r;
    m2k   = m2s;
    if (split->useForBranching) {
      m2a = split->kinematics()->m2RadAft;
      m2i = split->kinematics()->m2EmtAft;
      m2j = split->kinematics()->m2EmtAft2;
    }
    m2aij = m2Bef;
    m2ai  = sai + m2a + m2i;
    Q2    = m2Dip + m2aij + m2k - m2ai - m2j - m2k;
    yCS   = tDire/(q2 - m2ai - m2j - m2k) * xa / z;
    zCS   = z / (xa*(1-yCS)) * (q2 - m2aij - m2k) / (q2 - m2ai - m2j - m2k);
    m2Emt = m2Rad;
    m2Rad = m2ai;
    if (split->useForBranching) m2Emt = split->kinematics()->m2EmtAft;
    if (split->useForBranching) m2Rad = sai + m2a + m2j;
    if (split->useForBranching) m2ai  = sai + m2a + m2j;
  }

  if (name==testname && testps=="FF") direInfoPtr->message(1) << __LINE__
  << " " << name << " z=" << z << " tDire=" << dipSel->pT2
  << " Q2=" << Q2 << " q2=" << q2 << " xmin=" << -1
  << " m2bef=" << m2Bef << endl;

  // Calculate derived variables.
  double sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2Rad+m2Emt);

  //if (evType!=0)
  if (abs(evType)==1)
    sij  = yCS * (q2 - m2Bef - m2s) + (1.-yCS)*(m2Rad+m2Emt);
  //if (evType==0 && event[iRadBef].idAbs()>1000)
  if (evType==2)
    sij  = yCS * (q2 - m2Bef - m2s) + (1.-yCS)*(m2Rad+m2Emt);
  double zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
              * (zCS - m2s/gABC(q2,sij,m2s)
                      *(sij + m2Rad - m2Emt)/(q2-sij-m2s));
  double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2Rad - zbar*m2Emt; 

  // Not possible to construct kinematics if kT2 < 0.0
  if (kT2 < 0.) {
    infoPtr->errorMsg("Warning in DireTimes::branch_FF: Reject state "
      "with kinematically forbidden kT^2.");
    physical = false;
  }

  // NaN kT2 can happen for a 1->3 splitting in which the g->QQ~ produces
  // massive quarks Q. 
  if (kT2!=kT2 || abs(kT2-kT2) > 1e5) {
    infoPtr->errorMsg("Warning in DireTimes::branch_FF: Reject state "
      "with not-a-number kT^2 for branching " + name);
    physical = false;
  }

  // Now construct the new recoiler momentum in the lab frame.
  pRec.p( (pRecBef - (q*pRecBef)/q2 * q)
            * sqrt(lABC(q2,sij,m2s)/lABC(q2,m2Bef,m2s))
            + q * (q2+m2s-sij)/(2.*q2) );

  // Construct left-over dipole momentum by momentum conservation.
  Vec4 pij(q-pRec);

  // Set up transverse momentum vector by using two perpendicular four-vectors.
  pair<Vec4, Vec4> pTvecs = getTwoPerpendicular(pRec, pij);
  Vec4 kTmom( sqrt(kT2)*sin(phi_kt)*pTvecs.first
         + sqrt(kT2)*cos(phi_kt)*pTvecs.second);

  // Construct new radiator momentum.
  pRad.p( zbar * (gABC(q2,sij,m2s)*pij - sij*pRec) / bABC(q2,sij,m2s)
            + (m2Rad+kT2) / (zbar*bABC(q2,sij,m2s))
              * (pRec - m2s/gABC(q2,sij,m2s)*pij)
            + kTmom);

  // Contruct the emission momentum by momentum conservation.
  pEmt.p(q-pRad-pRec);

  // Ensure that radiator is on mass-shell
  double errMass = abs(pRad.mCalc() - sqrt(m2Rad)) / max( 1.0, pRad.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRad.m2Calc() - m2Rad;
    pRad.e(sqrtpos(pow2(pRad.e()) - deltam2));
  }
  // Ensure that emission is on mass-shell
  errMass = abs(pEmt.mCalc() - sqrt(m2Emt)) / max( 1.0, pEmt.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pEmt.m2Calc() - m2Emt;
    pEmt.e(sqrtpos(pow2(pEmt.e()) - deltam2));
  }
  // Ensure that recoiler is on mass-shell
  errMass = abs(pRec.mCalc() - sqrt(m2s)) / max( 1.0, pRec.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRec.m2Calc() - m2s;
    pRec.e(sqrtpos(pow2(pRec.e()) - deltam2));
  }

  // Swap emitted and radiator properties for first part of
  // 1->3 splitting (q -> "massive gluon" + q)
  if ( nEmissions == 2 && !split->useForBranching) {
    swap(idRad,idEmt);
    swap(colRad,colEmt);
    swap(acolRad,acolEmt);
  }

  // For emitted color singlet, redefine the colors of the "massive gluon".
  if ( nEmissions == 2 && split->useForBranching
    && particleDataPtr->colType(split->emtAft()->id)  == 0)
    { colRad = event[iRadBef].col(); acolRad = event[iRadBef].acol(); }

  // Define new particles from dipole branching.
  double pTsel = sqrt(tEvol);
  Particle rad = Particle(idRad, 51, iRadBef, 0, 0, 0,
    colRad, acolRad, pRad, sqrt(m2Rad), pTsel);

  // Exempt off-shell radiator from Pythia momentum checks.
  if ( nEmissions == 2) rad.status(59);

  Particle emt = Particle(idEmt, 51, iRadBef, 0, 0, 0,
    colEmt, acolEmt, pEmt, sqrt(m2Emt), pTsel);

  // Default to stored color info for intermediate step in 1->3 branching. 
  if ( nEmissions == 2 && split->useForBranching ) {
    /*if ( split->extras.find("colRadInt") != split->extras.end() )
      rad.col(int(split->extras["colRadInt"]));
    if ( split->extras.find("acolRadInt") != split->extras.end() )
      rad.acol(int(split->extras["acolRadInt"]));
    if ( split->extras.find("colEmtInt") != split->extras.end() )
      emt.col(int(split->extras["colEmtInt"]));
    if ( split->extras.find("acolEmtInt") != split->extras.end() )
      emt.acol(int(split->extras["acolEmtInt"]));*/
    if ( split->colRadInt != -1)  rad.col(split->colRadInt);
    if ( split->acolRadInt != -1) rad.acol(split->acolRadInt);
    if ( split->colEmtInt != -1)  emt.col(split->colEmtInt);
    if ( split->acolEmtInt != -1) emt.acol(split->acolEmtInt);
  }

  Particle rec = Particle(event[iRecBef].id(), 52, iRecBef, iRecBef, 0, 0,
    event[iRecBef].col(), event[iRecBef].acol(), pRec, sqrt(m2s), pTsel);

  // Save properties to be restored in case of user-hook veto of emission.
  int evSizeOld    = event.size();
  int iRadStatusV  = event[iRadBef].status();
  int iRadDau1V    = event[iRadBef].daughter1();
  int iRadDau2V    = event[iRadBef].daughter2();
  int iRecStatusV  = event[iRecBef].status();
  int iRecDau1V    = event[iRecBef].daughter1();
  int iRecDau2V    = event[iRecBef].daughter2();

  // Shower may occur at a displaced vertex.
  if (event[iRadBef].hasVertex()) {
    rad.vProd( event[iRadBef].vProd() );
    emt.vProd( event[iRadBef].vProd() );
  }
  if (event[iRecBef].hasVertex()) rec.vProd( event[iRecBef].vProd() );

  // Put new particles into the event record.
  // Mark original dipole partons as branched and set daughters/mothers.
  int iRad(event.append(rad));
  int iEmt(event.append(emt));
  int iEmt2(iEmt);
  event[iRadBef].statusNeg();
  event[iRadBef].daughters( iRad, iEmt);
  int iRec(event.append(rec));
  event[iRecBef].statusNeg();
  event[iRecBef].daughters( iRec, iRec);

  if ( nEmissions == 2 && !split->useForBranching) swap(iRad,iEmt);

  // Store flavour again, in case dipSel gets removed.
  int flavourNow = (!trial) ? dipSel->flavour : split->emtAft()->id; 

  // Check user veto for 1->2 branchings.
  bool inResonance = (partonSystemsPtr->getInA(iSysSel) == 0) ? true : false;
  bool doVeto      = false;
  if (nEmissions != 2) 
    doVeto = (( canVetoEmission && userHooksPtr->doVetoFSREmission(
                evSizeOld,event,iSysSel,inResonance) )
          ||  ( canMergeFirst && mergingHooksPtr->doVetoEmission(
                event) ));
  bool doMECreject = false; 

  if ( nEmissions != 2) {

    // Check momenta.
    if ( !validMomentum( rad.p(), idRad, 1)
      || !validMomentum( emt.p(), idEmt, 1)
      || !validMomentum( rec.p(), event[iRecBef].id(), 1))
      physical = false;

    // Apply ME correction if necessary.
    bool isHardSystem = partonSystemsPtr->getSystemOf(iRadBef,true) == 0
                     && partonSystemsPtr->getSystemOf(iRecBef,true) == 0;

    // Try to find incoming particle in other systems, i.e. if the current
    // system arose from a resonance decay.
    bool sys = partonSystemsPtr->getSystemOf(iRadBef,true);
    int sizeSys = partonSystemsPtr->sizeSys();
    int in1 = partonSystemsPtr->getInA(sys);
    int in2 = partonSystemsPtr->getInB(sys);
    if ( in1 == 0 && in2 == 0 ) {
      int iParentInOther = 0;
      int nSys = partonSystemsPtr->sizeAll(sys);
      for (int iInSys = 0; iInSys < nSys; ++iInSys){
        int iNow = partonSystemsPtr->getAll(sys,iInSys);
        for (int iOtherSys = 0; iOtherSys < sizeSys; ++iOtherSys){
          if (iOtherSys == sys) continue;
          int nOtherSys = partonSystemsPtr->sizeAll(iOtherSys);
          for (int iInOtherSys = 0; iInOtherSys < nOtherSys; ++iInOtherSys){
            int iOtherNow = partonSystemsPtr->getAll(iOtherSys,iInOtherSys);
            if (event[iNow].isAncestor(iOtherNow)) {
              iParentInOther = iOtherNow;
            }
          }
        }
      }
      if (iParentInOther) isHardSystem = true;
    }

    if ( isHardSystem && physical && doMEcorrections
      && tEvol > pT2minMECs) {

#ifdef MG5MES

      // Finally update the list of all partons in all systems.
      partonSystemsPtr->replace(iSysSel, iRadBef, iRad);
      partonSystemsPtr->addOut(iSysSel, iEmt);
      partonSystemsPtr->replace(iSysSelRec, iRecBef, iRec);

      if ( evtUtils->checkSIJhard(event, iSysSel, false, Q2minMECs)
        && (nFinalMaxMECs < 0
        || nFinalMaxMECs > partonSystemsPtr->sizeOut(iSysSel)))
        doMECreject = applyMEC (event, split, iRad, iEmt, iRec);

      partonSystemsPtr->replace(iSysSel, iRad, iRadBef);
      partonSystemsPtr->replace(iSysSelRec, iRec, iRecBef);
      partonSystemsPtr->popBackOut(iSysSel);

#else

      doMECreject = false;

#endif

    }

    // Update dipoles and beams.
    if (physical && !doVeto && !trial && !doMECreject) updateAfterFF( iSysSel,
      iSysSelRec, event, iRadBef, iRecBef, iRad, iEmt, iRec, flavour, colType,
      pTsel);

  // Heavy particle 1->2 decay for "second step" in 1->3 splitting.
  } else {

    // Check momenta.
    if ( !validMomentum( emt.p(), idEmt, 1)
      || !validMomentum( rec.p(), event[iRecBef].id(), 1))
      physical = false;

    int iRadOld = int(event.size())-3;
    int iEmtOld = int(event.size())-2;
    int iRecOld = int(event.size())-1;

    // Swap emitted and radiator indices.
    swap(iRadOld,iEmtOld);

    if (!split->useForBranching) {
      // Flavours already fixed by 1->3 kernel.
      idEmt        = -flavourNow;
      idRad        =  flavourNow;
      // Colour tags for new particles in branching.
      if (idEmt < 0) {
        colEmt  = 0;
        acolEmt = event[iEmtOld].acol();
        colRad  = event[iEmtOld].col();
        acolRad = 0;
      } else {
        colEmt  = event[iEmtOld].col();
        acolEmt = 0;
        colRad  = 0;
        acolRad = event[iEmtOld].acol();
      }
    // Already correctly read id and colors from SplitInfo object.
    } else {
      idRad   = split->radAft()->id;
      idEmt   = split->emtAft2()->id;
      colRad  = split->radAft()->col;
      acolRad = split->radAft()->acol;
      colEmt  = split->emtAft2()->col;
      acolEmt = split->emtAft2()->acol;

      //if (int(split->extras["swapped"]) == 1) {
      if (split->swapped) {
        idRad   = split->emtAft()->id;
        idEmt   = split->emtAft2()->id;
        colRad  = split->emtAft()->col;
        acolRad = split->emtAft()->acol;
        colEmt  = split->emtAft2()->col;
        acolEmt = split->emtAft2()->acol;
      }

    }

    // Get particle masses.
    m2Bef = m2ai;
    // Radiator after splitting.
    m2r   = particleDataPtr->isResonance(idRad)
              && idRad == event[iRadBef].id()
          ? getMass(idRad,3,event[iRadBef].mCalc())
          : (abs(idRad) < 6 || idRad == 21 || idRad == 22)
          ? getMass(idRad,2)
          : getMass(idRad,1);
    // Recoiler. 
    m2s   = particleDataPtr->isResonance(event[iRecBef].id())
          ? getMass(event[iRecBef].id(),3,event[iRecBef].mCalc())
          : (event[iRecBef].idAbs() < 6 || event[iRecBef].id() == 21
          || event[iRecBef].id() == 22)
          ? getMass(event[iRecBef].id(),2)
          : getMass(event[iRecBef].id(),1);
    // Emission.
    m2e   = (abs(idEmt) < 6 || idEmt == 21 || idEmt == 22)
          ? getMass(idEmt,2) : getMass(idEmt,1);

    if (split->useForBranching) {
      m2r = split->kinematics()->m2RadAft;
      m2e = split->kinematics()->m2EmtAft2;
    }

    // Construct FF dipole momentum.
    Vec4 pa1(event[iEmtOld].p());
    q.p(pa1 + pRec);
    q2 = q.m2Calc();

    // Calculate CS variables.
    m2Emt      = m2e;
    m2Rad      = m2e;
    if (split->useForBranching) {
      m2Rad = split->kinematics()->m2RadAft;
      m2Emt = split->kinematics()->m2EmtAft2;
    }
    zCS        = xa;
    yCS = (m2ai-m2Emt-m2Rad) / (m2ai-m2Emt-m2Rad + 2.*pa1*pRec);

    // Calculate derived variables.
    sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2Rad+m2Emt);
    zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
               * (zCS - m2s/gABC(q2,sij,m2s)
                       *(sij + m2Rad - m2Emt)/(q2-sij-m2s));
    kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2Rad - zbar*m2Emt; 

    if(kT2 < 0.) physical = false;

    // Construct left-over dipole momentum by momentum conservation.
    pij.p(q-pRec);

    // Set up transverse momentum vector by using two perpendicular 4-vectors.
    pTvecs = getTwoPerpendicular(pRec, pij);
    kTmom.p( sqrt(kT2)*sin(phiX)*pTvecs.first
           + sqrt(kT2)*cos(phiX)*pTvecs.second);

    // Construct new radiator momentum.
    pRad.p( zbar * (gABC(q2,sij,m2s)*pij - sij*pRec) / bABC(q2,sij,m2s)
              + (m2Rad+kT2) / (zbar*bABC(q2,sij,m2s))
                * (pRec - m2s/gABC(q2,sij,m2s)*pij)
              + kTmom);

    // Contruct the emission momentum by momentum conservation.
    pEmt.p(q-pRad-pRec);

    // Recoiler unchanged.
    pRec.p(event[iRecOld].p());

    // Define new particles from dipole branching.
    Particle rad2 = Particle(idRad, 51, iEmtOld, 0, 0, 0,
      colRad, acolRad, pRad, sqrt(m2r), pTsel);
    Particle emt2 = Particle(idEmt, 51, iEmtOld, 0, 0, 0,
      colEmt, acolEmt, pEmt, sqrt(m2e), pTsel);
    Particle rec2 = Particle(event[iRecOld].id(), 52, iRecOld, iRecOld, 0, 0,
      event[iRecOld].col(), event[iRecOld].acol(), pRec, sqrt(m2s), pTsel);

    // Check momenta.
    if ( !validMomentum( rad2.p(), idRad, 1)
      || !validMomentum( emt2.p(), idEmt, 1)
      || !validMomentum( rec2.p(), event[iRecOld].id(), 1) )
      physical = false;

    // Check invariants.
    if ( false ) {
      Vec4 pa(pRad), pk(pRec), pj(emt.p()), pi(pEmt);
      double saix(2.*pa*pi), sakx(2.*pa*pk), sajx(2.*pa*pj), sikx(2.*pi*pk),
             sjkx(2.*pj*pk), sijx(2.*pi*pj);
      double pptt = (sajx+sijx)*(sakx+sikx)
                  / ( (event[iRadBef].p()+event[iRecBef].p()).m2Calc()
                     - event[iRadBef].m2Calc() - event[iRecBef].m2Calc() );
      double ssaaii = saix; 
      double zzaa = sakx
                  / ( (event[iRadBef].p()+event[iRecBef].p()).m2Calc()
                     - event[iRadBef].m2Calc() - event[iRecBef].m2Calc() );
      double xxaa = sakx / ( sakx + sikx );
      if ( physical &&
           (abs(pptt-tEvol) > 1e-5 || abs(ssaaii-sai) > 1e-5 ||
            abs(zzaa-z) > 1e-5   || abs(xxaa-xa) > 1e-5) ){
        cout << scientific << setprecision(8);
        cout << "Error in branch_FF: Invariant masses after branching do not "
             << "match chosen values." << endl;
        cout << "Chosen:    "
             << " Q2 " << (event[iRadBef].p()+event[iRecBef].p()).m2Calc()
             << " pT2 " << tEvol
             << " sai " << sai
             << " za " << z
             << " xa " << xa << endl;
        cout << "Generated: "
             << " Q2 " << sakx+saix+sajx+sijx+sikx+sjkx
             << " pT2 " << pptt
             << " sai " << ssaaii
             << " za " << zzaa
             << " xa " << xxaa << endl;
        physical = false;
      }
    }

    // Update bookkeeping
    if (physical) {

      // Update dipoles and beams.
      if (!trial) updateAfterFF( iSysSel, iSysSelRec, event,
        iRadBef, iRecBef, iRad, iEmt, iRec, flavour, colType, pTsel);

      // Shower may occur at a displaced vertex.
      if (!trial) {
        if (event[iEmtOld].hasVertex()) {
          rad2.vProd( event[iEmtOld].vProd() );
          emt2.vProd( event[iEmtOld].vProd() );
        }
        if (event[iRecOld].hasVertex()) rec2.vProd( event[iRecOld].vProd() );
      }

      // Put new particles into the event record.
      // Mark original dipole partons as branched and set daughters/mothers.
      iRad = event.append(rad2);
      iEmt = event.append(emt2);
      event[iEmtOld].statusNeg();
      event[iEmtOld].daughters( iRad, iEmt);
      iRec = event.append(rec2);
      event[iRecOld].statusNeg();
      event[iRecOld].daughters( iRec, iRec);

      // Update dipoles and beams.
      if (!trial) {
        int colTypeNow = colType;
        updateAfterFF( iSysSel, iSysSelRec, event, iEmtOld, iRecOld, iRad,
          iEmt,iRec, flavourNow, colTypeNow, pTsel);
      }
    }
  }

  if (name==testname && testps=="FF" && tEvol > pT2minMECs) {
    direInfoPtr->printMessages(1); abort();
  }

  physical = physical && !doVeto;

  // Ungraceful exit for incorrect event.
  bool isHadronic = false;
  for (int i = 0; i < event.size(); ++i)
    if (event[i].statusAbs() > 60) isHadronic = true;
  // Only check competing steps (first part of 1->3 splitting will contain
  // a massive pseudo-gluon).
  if ( physical && !trial && !doMECreject && !isHadronic
    && !validEvent(event, false, iSysSel)
    && infoPtr->weight() != 0.) {
    infoPtr->errorMsg("Error in DireTimes::branch_FF: State after "
                      "branching not valid, thus reject.");
    //puppybort(__func__);
    physical = false;
  }

  // Check if mother-daughter relations are correctly set. Check only
  // possible if no MPI are present.
  if ( physical && !trial && !doMECreject 
    && !validMotherDaughter(event)) {
    infoPtr->errorMsg("Error in DireTimes::branch_FF: Mother-daughter "
                      "relations after branching not valid.");
    physical = false;
  }

  // Allow veto of branching. If so restore event record to before emission.
  if ( !physical || doMECreject ) {
    event.popBack( event.size() - evSizeOld);
    event[iRadBef].status( iRadStatusV);
    event[iRadBef].daughters( iRadDau1V, iRadDau2V);
    event[iRecBef].status( iRecStatusV);
    event[iRecBef].daughters( iRecDau1V, iRecDau2V);

    // This case is identical to the case where the probability to accept the
    // emission was indeed zero all along. In this case, neither
    // acceptProbability nor rejectProbability would have been filled. Thus,
    // remove the relevant entries from the weight container!
    if (!trial && !physical) {
      for ( unordered_map<string, multimap<double,double> >::iterator
        it = rejectProbability.begin(); it != rejectProbability.end(); ++it){
        weights->eraseAcceptWeight(tEvol, it->first);
        weights->eraseRejectWeight(tEvol, it->first);
      }
    }

    if (!trial && doMECreject) {
      weights->calcWeight(tEvol, false, true);
      weights->reset();
     // Clear accept/reject weights.
      for ( unordered_map<string, multimap<double,double> >::iterator
        it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
        it->second.clear();
      for ( unordered_map<string, map<double,double> >::iterator
        it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
        it->second.clear();
    }

    return false;
  }

  // Store positions of new particles.
  if (trial && !split->useForBranching) split->storePosAfter( iRad, iRec, iEmt,
    (nEmissions < 2) ? 0 : iEmt2);
  if (trial &&  split->useForBranching) split->storePosAfter( iRad, iRec, iEmt2,
    (nEmissions < 2) ? 0 : iEmt);

  // Set shower weight.
  if (!trial) {
    weights->setSelectedKernel(tEvol, kernelSel);
    if (!doTrialNow) {
      weights->calcWeight(tEvol);
      weights->reset();
      // Store positions of new soft particles.
      if (nEmissions == 1) {
        direInfoPtr->updateSoftPos( iRadBef, iEmt );
        direInfoPtr->updateSoftPosIfMatch( iRecBef, iRec );
      // For 1->3 splitting, do not tag emissions as "soft".
      } else {
        direInfoPtr->updateSoftPos( iRadBef, iRad );
      }

      updateDipoles(event, iSysSel);
    }

    // Clear accept/reject weights.
    for ( unordered_map<string, multimap<double,double> >::iterator
      it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
      it->second.clear();
    for ( unordered_map<string, map<double,double> >::iterator
      it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
      it->second.clear();

    updateEvolutionWindows (idEmt, tEvol, iWindowSel);

  }

  // Relabel shower=produced Z- and W-bosons as id's 93 and 94, to avoid that
  // Pythia decays the particles inadvertantly.
  if (doTrialNow) {
    evtUtils->shiftWZbosonID(event, iRad);
    evtUtils->shiftWZbosonID(event, iEmt);
    evtUtils->shiftWZbosonID(event, iEmt2);
    evtUtils->shiftWZbosonID(event, iRec);
  }

  // Done.
  return true;

}

//--------------------------------------------------------------------------

void DireTimes::updateAfterFF( int iSysSelNow, int iSysSelRec, 
  Event& event, int iRadBef, int iRecBef, int iRad, int iEmt, int iRec,
  int, int colType, double pTsel) {

  vector<int> iDipEndCorr, iDipEndRem;
  bool inResonance = (partonSystemsPtr->getInA(iSysSelNow)==0) ? true : false;
  int idEmt        = event[iEmt].id();
  bool hasDipSel   = (dipSel != 0);

  // Bookkeep shower-induced resonances.
  if ( direInfoPtr->isRes(iRadBef) && 
    event[iRadBef].id() != event[iRad].id() )
    direInfoPtr->removeResPos(iRadBef);
  if ( particleDataPtr->isResonance(event[iRad].id()) ) {
    if ( direInfoPtr->isRes(iRadBef) )
         direInfoPtr->updateResPos(iRadBef,iRad);
  }
  if ( direInfoPtr->isRes(iRecBef) )
    direInfoPtr->updateResPos(iRecBef,iRec);
  if ( particleDataPtr->isResonance(event[iEmt].id()) )
    direInfoPtr->addResPos(iEmt);

  // Gluon emission: update both dipole ends and add two new ones.
  if (particleDataPtr->colType(idEmt) == 2) {

    if (hasDipSel) {
      dipSel->iRadiator  = iRad;
      dipSel->iRecoiler  = iEmt;
      dipSel->systemRec  = iSysSelRec;
      dipSel->isrType    = 0;
      dipSel->pTmax      = pTsel;
      dipSel->MEtype     = 0;
    }

    for (int i = 0; i < int(dipEnd.size()); ++i) {
      DireTimesEnd& dip = dipEnd[i];
      if (dip.iRadiator == iRecBef && dip.iRecoiler == iRadBef
        && dip.colType != 0) {
        dip.iRadiator = iRec;
        dip.iRecoiler = iEmt;
        dip.MEtype = 0;
        // Strive to match colour to anticolour inside closed system.
        if ( dip.colType * colType > 0) dip.iRecoiler = iRad;
        dip.pTmax = pTsel;
        iDipEndCorr.push_back(i);
      }
    }

    int colTypeNow = (colType > 0) ? 2 : -2 ;
    // When recoiler was uncoloured particle, in resonance decays,
    // assign recoil to coloured particle.
    int iRecMod = iRec;
    if (recoilToColoured && inResonance && event[iRec].col() == 0
      && event[iRec].acol() == 0) iRecMod = iRad;
    if (appendDipole( event, iEmt, iRecMod, pTsel, colTypeNow, 0, 0, 0, 0,
          iSysSelNow, 0, -1, 0, false, dipEnd)) {
      iDipEndCorr.push_back(dipEnd.size()-1);
      // Set dipole mass properties.
      DireTimesEnd& dip1 = dipEnd.back();
      dip1.systemRec = iSysSelRec;
    }

    if (appendDipole( event, iEmt, iRad, pTsel,-colTypeNow, 0, 0, 0, 0,
          iSysSelNow, 0, -1, 0, false, dipEnd)) {
      iDipEndCorr.push_back(dipEnd.size()-1);
    }

  // Gluon branching to q qbar: update current dipole and other of gluon.
  } else if (particleDataPtr->colType(idEmt) != 0) {

    // Update dipoles for second step in 1->3 splitting.
    //if ( splittingsPtr->nEmissions(splittingSelName) == 2 ){
    if ( splits[splittingSelName]->nEmissions() == 2 ){
      for (int i = 0; i < int(dipEnd.size()); ++i) {

        DireTimesEnd& dip = dipEnd[i];

        if ( dip.iRadiator == iRecBef ) { 
          dip.iRadiator = iRec;
        }
        if ( dip.iRecoiler == iRecBef ) {
          dip.iRecoiler = iRec;
        }

        if ( dip.iRadiator == iRadBef ) {
          if (dip.colType > 0)
            dip.iRadiator = (event[iEmt].id() > 0) ? iEmt : iRad;
          if (dip.colType < 0)
            dip.iRadiator = (event[iEmt].id() < 0) ? iEmt : iRad;

          if (abs(dip.colType) == 2
            && event[dip.iRadiator].id()    > 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = abs(dip.colType)/2;
          if (abs(dip.colType) == 2
            && event[dip.iRadiator].id()    < 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = -abs(dip.colType)/2;

          iDipEndCorr.push_back(i);
        }

        if ( dip.iRecoiler == iRadBef ) {
          if (dip.colType > 0)
            dip.iRecoiler = (event[iEmt].id() < 0) ? iEmt : iRad;
          if (dip.colType < 0)
            dip.iRecoiler = (event[iEmt].id() > 0) ? iEmt : iRad;

          if (abs(dip.colType) == 2) dipEnd[i].colType /= 2;

          if (abs(dip.colType) == 1
            && event[dip.iRadiator].id()    > 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = 1;

          if (abs(dip.colType) == 1
            && event[dip.iRadiator].id()    < 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = -1;

          iDipEndCorr.push_back(i);
        }
      }
    }

    for (int i = 0; i < int(dipEnd.size()); ++i) {
      // Nothing to be done if dipole end has already been updated.
      if ( find(iDipEndCorr.begin(), iDipEndCorr.end(), i)
        != iDipEndCorr.end() ) continue;
      DireTimesEnd& dip = dipEnd[i];
      // Strive to match colour to anticolour inside closed system.
      if ( dip.iRecoiler == iRadBef && dip.colType * colType < 0 ) {
        dip.iRecoiler = iEmt;
      }
      if (dip.iRadiator == iRadBef && abs(dip.colType) == 2) {
        dip.colType /= 2;

        if (hasDipSel && &dipEnd[i] == dipSel) dip.iRadiator  = iEmt;
        else                                   dip.iRadiator  = iRad;
        if (hasDipSel && &dipEnd[i] == dipSel) dip.iRecoiler  = iRec;

        dip.colType = (event[dip.iRadiator].id() > 0)
                    ? abs(dip.colType) : -abs(dip.colType);

        iDipEndCorr.push_back(i);

        if (dip.system != dip.systemRec) continue;
        dip.MEtype = 0;
        if (hasDipSel && &dipEnd[i] == dipSel) dip.iMEpartner = iRad;
        else                      dip.iMEpartner = iEmt;

      }
    }

    // Nothing to be done if dipole end has already been updated.
    bool updateSel=true;
    for (int j = 0; j < int(iDipEndCorr.size()); ++j)
      if ( hasDipSel && &dipEnd[iDipEndCorr[j]] == dipSel) updateSel = false;

    if (hasDipSel) {
      if (updateSel) {
        dipSel->iRadiator = iEmt;
        dipSel->iRecoiler = iRec;
      }
      // Always update the production pT.
      dipSel->pTmax     = pTsel;
    }

  } else {

    int iRadOld = (hasDipSel) ? dipSel->iRadiator : iRadBef;
    int iRecOld = (hasDipSel) ? dipSel->iRecoiler : iRecBef;
    // Just update old radiator/recoiler to current outgoing particles.
    for (int i = 0; i < int(dipEnd.size()); ++i) {
      DireTimesEnd& dip = dipEnd[i];
      // Update radiator-recoiler end.
      if ( dip.iRecoiler == iRecOld && dip.iRadiator == iRadOld ) {
        dip.iRadiator = iRad;
        dip.iRecoiler = iRec;
        dip.pTmax  = pTsel;
        iDipEndCorr.push_back(i);
      }
      // Update recoiler-radiator end.
      if ( dip.iRecoiler == iRadOld && dip.iRadiator == iRecOld ) {
        dip.iRadiator = iRec;
        dip.iRecoiler = iRad;
        dip.pTmax = pTsel;
        iDipEndCorr.push_back(i);
      }
    }
  }

  // Now update other dipoles that also involved the radiator or recoiler.
  for (int i = 0; i < int(dipEnd.size()); ++i) {
    // Nothing to be done if dipole end has already been updated.
    if ( find(iDipEndCorr.begin(), iDipEndCorr.end(), i)
      != iDipEndCorr.end() ) continue;
    DireTimesEnd& dip = dipEnd[i];
    if (dip.iRadiator  == iRadBef) dip.iRadiator  = iRad;
    if (dip.iRecoiler  == iRadBef) dip.iRecoiler  = iRad;
    if (dip.iMEpartner == iRadBef) dip.iMEpartner = iRad;
    if (dip.iRadiator  == iRecBef) dip.iRadiator  = iRec;
    if (dip.iRecoiler  == iRecBef) dip.iRecoiler  = iRec;
    if (dip.iMEpartner == iRecBef) dip.iMEpartner = iRec;
  }

  // Now update or construct new dipoles if the radiator or emission allow
  // for new types of emissions.
  vector<pair<int, int> > rad_rec (createvector< pair<int,int> >
    (make_pair(iRad,iEmt))
    (make_pair(iEmt,iRec))
    (make_pair(iRec,iEmt))
    (make_pair(iEmt,iRad))
    (make_pair(iRad,iRec))
    (make_pair(iRec,iRad)));
  for (int i=0; i < int(rad_rec.size()); ++i) {
    int iRadNow = rad_rec[i].first;
    int iRecNow = rad_rec[i].second;
    // Now check if a new dipole end a-b should be added:
    // First check if the dipole end is already existing.
    vector<int> iDip;
    for (int j = 0; j < int(dipEnd.size()); ++j)
      if ( dipEnd[j].iRadiator == iRadNow
        && dipEnd[j].iRecoiler == iRecNow )
        iDip.push_back(j);
    // If the dipole end exists, attempt to update the dipole end (a)
    // for the current a-b dipole. 
    if ( int(iDip.size()) > 0) for (int j = 0; j < int(iDip.size()); ++j)
      updateAllowedEmissions(event, &dipEnd[iDip[j]]);
    // If no dipole exists and idEmtAfter != 0, create new dipole end (a).
    else appendDipole( event, iRadNow, iRecNow, pTsel, 0, 0, 0, 0, 0,
      iSysSelNow, -1, -1, 0, false, dipEnd);
  }

  // Copy or set lifetime for new final state.
  if (event[iRad].id() == event[iRadBef].id())
    event[iRad].tau( event[iRadBef].tau() );
  else {
    event[iRad].tau( event[iRad].tau0() * rndmPtr->exp() );
    event[iEmt].tau( event[iEmt].tau0() * rndmPtr->exp() );
  }
  event[iRec].tau( event[iRecBef].tau() );

  // Finally update the list of all partons in all systems.
  partonSystemsPtr->replace(iSysSelNow, iRadBef, iRad);
  partonSystemsPtr->addOut(iSysSelNow, iEmt);
  partonSystemsPtr->replace(iSysSelRec, iRecBef, iRec);

  // Loop through final state of system to find possible new dipole ends.
  for (int i = 0; i < partonSystemsPtr->sizeOut(iSysSelNow); ++i) {
    int iNow = partonSystemsPtr->getOut( iSysSelNow, i);
    if (event[iNow].isFinal() && event[iNow].scale() > 0.) {
      // Find dipole end formed by colour index.
      int colTag = event[iNow].col();
      if (doQCDshower && colTag > 0) setupQCDdip( iSysSelNow, i,  colTag,  1,
        event, false, true);
      // Find dipole end formed by anticolour index.
      int acolTag = event[iNow].acol();
      if (doQCDshower && acolTag > 0) setupQCDdip( iSysSelNow, i, acolTag, -1,
        event, false, true);
      // Now find non-QCD dipoles and/or update the existing dipoles.
      getGenDip( iSysSelNow, i, iNow, event, false, dipEnd);
    }
    // Setup decay dipoles.
    if (doDecaysAsShower && event[iNow].isResonance())
      setupDecayDip( iSysSelNow, iNow, event, dipEnd);
  }

  // Now remove inactive dipoles.
  sort (iDipEndRem.begin(), iDipEndRem.end());  
  for (int i = iDipEndRem.size()-1; i >= 0; --i) {
    dipEnd[iDipEndRem[i]] = dipEnd.back();
    dipEnd.pop_back();
  }

  // Now update all dipoles.
  dipSel = 0;
  updateDipoles(event, iSysSelNow);

  int nFinal = 0;
  for (int i=0; i < event.size(); ++i) if (event[i].isFinal()) nFinal++;
  if (nFinal == 3) {
    int col = (colType> 0) ? event[iRadBef].col() : event[iRadBef].acol();
    vector<int>::iterator iRem = find(bornColors.begin(), bornColors.end(), col);    
    if (iRem != bornColors.end()) bornColors.erase(iRem++);
  }

  // Done.
}

//--------------------------------------------------------------------------

// ME corrections and kinematics that may give failure.
// Notation: radBef, recBef = radiator, recoiler before emission,
//           rad, rec, emt = radiator, recoiler, emitted efter emission.
//           (rad, emt distinguished by colour flow for g -> q qbar.)

bool DireTimes::branch_FI( Event& event, bool trial,
  DireSplitInfo* split ) {

  // Check if the first emission should be studied for removal.
  bool physical      = true;
  bool canMergeFirst = (mergingHooksPtr != 0)
                     ? mergingHooksPtr->canVetoEmission() : false;

  // Find initial radiator and recoiler particles in dipole branching.
  int iRadBef      = (!trial) ? dipSel->iRadiator : split->iRadBef;
  int iRecBef      = (!trial) ? dipSel->iRecoiler : split->iRecBef;
  bool   hasPDFrec = hasPDF(event[iRecBef].id());
  int isrType      = event[iRecBef].mother1();
  while (isrType > 2 + beamOffset) isrType = event[isrType].mother1();
  if (isrType > 2) isrType -= beamOffset;

  bool isHardSystem = partonSystemsPtr->getSystemOf(iRadBef,true) == 0
                   && partonSystemsPtr->getSystemOf(iRecBef,true) == 0;

  // Find their momenta, with special sum for global recoil.
  Vec4 pRadBef     = event[iRadBef].p();
  Vec4 pRecBef     = event[iRecBef].p();

  // Get splitting variables.
  string name = (!trial) ? splittingSelName : split->splittingSelName;
  if (!trial) splits[name]->splitInfo.store(*split);
  double tEvol  = (!trial) ? dipSel->pT2   : split->kinematics()->pT2;
  double tDire  = tEvol;
  double z      = (!trial) ? dipSel->z     : split->kinematics()->z;
  unordered_map<string,double>
    psp(splits[name]->getPhasespaceVars(event, partonSystemsPtr));
  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { tDire = psp["pT2"]; z = psp["z"]; }
  double m2Dip  = (!trial) ? dipSel->m2Dip : split->kinematics()->m2Dip;

  if (kinRels->FSRevolutionMode==1) {
    z     = kinRels->z_fi_dire_from_cs(z, tEvol, m2Dip);
    tDire = kinRels->t_fi_dire_from_cs(z, tEvol, m2Dip);
  }

  if (name==testname && testps=="FI") {
    BeamParticle& beam = (dipSel->isrType == 1) ? *beamAPtr : *beamBPtr;
    int iSysRec          = dipSel->systemRec;
    double xRecoiler     = beam[iSysRec].x();
    direInfoPtr->message(1) << endl << endl << __func__ << " name="
    << name << " " << event[iRecBef].id() << " tEvol=" << tEvol
    << " xbj=" << xRecoiler << endl;
  }

  // Calculate CS variables.
  double kappa2 = tDire/m2Dip;
  double zCS    = z;
  double xCS    = 1 - kappa2/(1.-z);

  // Get flavour of splitting.
  int flavour = (!trial) ? dipSel->flavour : split->emtAft()->id;
  // Store flavour again, in case dipSel gets removed or flavour gets reset.
  int flavourSave = flavour; 
  // Name of the splitting.
  int nEmissions = splits[name]->nEmissions();

  // Evolution type, in case different from default Dire definition.
  int evType = splits[name]->typeEvolutionMeasure();

  //if ( nEmissions == 2 && !split->useForBranching) flavour = 21;
  if ( nEmissions == 2 && !split->useForBranching) {
    if (splits[name]->is_qcd) flavour = 21;
    else                      flavour = 22;
  }

  // Default flavours and colour tags for new particles in dipole branching.
  int idRad        = event[iRadBef].id();
  int idEmt        = abs(flavour);
  int colRad       = event[iRadBef].col();
  int acolRad      = event[iRadBef].acol();
  int colEmt       = 0;
  int acolEmt      = 0;
  iSysSel          = (!trial) ? dipSel->system : split->system;
  int iSysSelRec   = (!trial) ? dipSel->systemRec : split->system;

  int colType = -2;
  if (!trial && dipSel->colType > 0) colType = 2;
  if ( trial && idRad > 0)           colType = 2;
  if (!trial && (dipSel->gamType == 1 || abs(dipSel->weakType) > 0)) colType=0;
  if ( trial && (idRad==22 || idRad==23 || idRad==24 || idRad==25))  colType=0;

  if ( split->useForBranching
    && (particleDataPtr->colType(split->emtAft()->id)  == 0
    || (particleDataPtr->colType(split->emtAft2()->id) == 0
      && nEmissions == 2)))
    colType = 0;

  if (flavour == 22 || flavour == 23 || flavour == 25) ;

  // New colour tag required for gluon emission.
  else if (flavour == 21 && colType > 0) {
    colEmt  = colRad;
    colRad  = event.nextColTag();
    acolEmt = colRad;
  } else if (flavour == 21) {
    acolEmt = acolRad;
    acolRad = event.nextColTag();
    colEmt  = acolRad;
  // New flavours for g -> q qbar; split colours.
  } else if (colType > 0) {
    idEmt   = abs(flavour);
    idRad   = -idEmt;
    colEmt  = colRad;
    colRad  = 0;
  } else if (colType < 0) {
    idEmt   = -abs(flavour);
    idRad   = -idEmt;
    acolEmt  = acolRad;
    acolRad  = 0;
  }

  if (split->useForBranching) {
    idRad   = event[iRadBef].id();
    colRad  = event[iRadBef].col();
    acolRad = event[iRadBef].acol();
    colEmt  = 0;
    acolEmt = 0;
    // Now reset if splitting information is available.
    if (split->radAft()->id   != 0) idRad   = split->radAft()->id;
    if (split->emtAft()->id   != 0) idEmt   = split->emtAft()->id;
    if (split->radAft()->col  > -1) colRad  = split->radAft()->col;
    if (split->radAft()->acol > -1) acolRad = split->radAft()->acol;
    if (split->emtAft()->col  > -1) colEmt  = split->emtAft()->col;
    if (split->emtAft()->acol > -1) acolEmt = split->emtAft()->acol;
  }

  // Get particle masses.
  // Radiator before splitting.
  double m2Bef = particleDataPtr->isResonance(event[iRadBef].id())
               ? getMass(event[iRadBef].id(),3,event[iRadBef].mCalc())
               : (event[iRadBef].idAbs() < 6 || event[iRadBef].id() == 21
               || event[iRadBef].id() == 22)
               ? getMass(event[iRadBef].id(),2)
               : getMass(event[iRadBef].id(),1);

  // Radiator after splitting.
  double m2r   = particleDataPtr->isResonance(idRad)
                 && idRad == event[iRadBef].id()
               ? getMass(idRad,3,event[iRadBef].mCalc())
               : (abs(idRad) < 6 || idRad == 21 || idRad == 22)
               ? getMass(idRad,2)
               : getMass(idRad,1);
  // Emission.
  double m2ex = (abs(idEmt) < 6 || idEmt == 21 || idEmt == 22)
              ? getMass(idEmt,2) : getMass(idEmt,1);
  double m2e  = (!trial) ? m2ex
    : ( (split->kinematics()->m2EmtAft > 0.) ? split->kinematics()->m2EmtAft
                                            : m2ex);

  if (split->useForBranching) {
    m2r = split->kinematics()->m2RadAft;
    m2e = split->kinematics()->m2EmtAft;
  }

  // Initial state recoiler always assumed massless. 
  double m2s = 0.0;
  // Recoiler mass
  if ( useMassiveBeams && (event[iRecBef].idAbs() == 11
                        || event[iRecBef].idAbs() == 13
                        || event[iRecBef].idAbs() > 900000))
    m2s   = getMass(event[iRecBef].id(),1);

  // Recalculate the kinematicaly available dipole mass.
  double Q2 = m2Dip - m2Bef + m2r + m2e;

  // Calculate CS variables.
  kappa2       = tDire/Q2;
  xCS          = 1 - kappa2/(1.-z);

  // changes for virtuality ordering
  if (abs(evType)==1) {
    double virt = (evType > 0
                ? tEvol : pow2(2.*sqrt(m2Bef)-sqrt(tEvol)) );
    xCS = m2Dip/(m2Dip+virt);
  }

  if (evType==2) { 
    double virt = tEvol + m2Bef;
    xCS = m2Dip / (m2Dip + virt);
  }

  if (name==testname && testps=="FI") direInfoPtr->message(1) << __LINE__
  << " " << name << " xcs=" << xCS << " z=" << z << " tEvol=" << tEvol
  << " tDire=" << tDire << endl;

  double m2Emt = m2e;
  double m2Rad = m2r;
  double sai   = (!trial) ? dipSel->sa1 : split->kinematics()->sai;
  double xa    = (!trial) ? dipSel->xa  : split->kinematics()->xa;

  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { sai = psp["sai"]; xa = psp["xa"]; }

  // Auxiliary angle.
  double phi_kt = (!trial)
    ? ((dipSel->phi >= 0.)              ? dipSel->phi
                                        : 2.*M_PI*rndmPtr->flat())
    : ((split->kinematics()->phi >= 0.) ? split->kinematics()->phi
                                        : 2.*M_PI*rndmPtr->flat());
  // Second angle for 1->3 splitting.
  double phiX = 0.0;
  if (nEmissions == 2)
    phiX = (!trial)
      ? ((dipSel->phia1 >= 0.)             ? dipSel->phia1
                                           : 2.*M_PI*rndmPtr->flat())
      : ((split->kinematics()->phi2 >= 0.) ? split->kinematics()->phi2
                                           : 2.*M_PI*rndmPtr->flat());

  // Allow splitting kernel to overwrite phase space variables. 
  if (split->useForBranching) { phi_kt = psp["phi"]; phiX = psp["phi2"]; }

  Vec4 pRad, pEmt, pRec;
  // Get dipole 4-momentum.
  Vec4 q(pRecBef-pRadBef);
  double q2 = q.m2Calc();

  // 1->3 splittings generated in CS variables directly.
  double m2a(0.), m2i(0.), m2j(0.), m2ai(0.); 
  if (nEmissions == 2) {
    m2a   = (abs(flavourSave) < 6
              || flavourSave == 21
              || flavourSave == 22)
          ? getMass(flavourSave,2)
          : getMass(flavourSave,1);
    m2i   = m2a;
    m2j   = m2Bef;
    if (split->useForBranching) {
      m2a = split->kinematics()->m2RadAft;
      m2i = split->kinematics()->m2EmtAft;
      m2j = split->kinematics()->m2EmtAft2;
    }
    m2ai  = sai + m2a + m2i;
    Q2    = m2Dip - m2Bef + m2ai + m2j + m2s;
    zCS   = z / xa;
    xCS   = (q2 - m2ai - m2j - m2s)
          / (q2 - m2ai - m2j - m2s - tDire * xa/z);
    m2Emt = m2r;
    m2Rad = m2ai;
    if (split->useForBranching) {
      m2Emt = split->kinematics()->m2EmtAft;
      m2Rad = sai + m2a + m2j;
      m2ai  = sai + m2a + m2j;
    }
  }

  Vec4 qpar(q.px()+pRadBef.px(), q.py()+pRadBef.py(), q.pz(), q.e());
  double qpar2 = qpar.m2Calc();
  double pT2ijt = pow2(pRadBef.px()) + pow2(pRadBef.py());

  // Calculate derived variables.
  double sij  = (1.-1./xCS) * (q2 - m2s) + (m2Rad+m2Emt) / xCS;

  // changes for virtuality ordering
  if (abs(evType)==1)
    sij  = (1.-1./xCS) * (q2 - m2Bef - m2s) + (m2Rad+m2Emt) / xCS;
  if (evType==2)
    sij  = (1.-1./xCS) * (q2 - m2Bef - m2s) + (m2Rad+m2Emt) / xCS;

  double zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
              * (zCS - m2s/gABC(q2,sij,m2s)
                    *(sij + m2Rad - m2Emt)/(q2-sij-m2s));
  double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2Rad - zbar*m2Emt; 

  if (name==testname && testps=="FI") direInfoPtr->message(1) << __LINE__
  << " " << name << " z=" << z << " tEvol=" << tEvol << endl;

  // Not possible to construct kinematics if kT2 < 0.0
  if (kT2 < 0.) {
    infoPtr->errorMsg("Warning in DireTimes::branch_FI: Reject state "
      "with kinematically forbidden kT^2.");
    physical = false;
  }

  // NaN kT2 can happen for a 1->3 splitting in which the g->QQ~ produces
  // massive quarks Q. 
  if (physical && (kT2!=kT2 || abs(kT2-kT2) > 1e5) ) {
    infoPtr->errorMsg("Warning in DireTimes::branch_FI: Reject state "
      "with not-a-number kT^2 for branching " + name);
    physical = false;
  }

  // Now construct the new recoiler momentum in the lab frame.
  pRec.p( (pRecBef - (q*pRecBef)/qpar2 * qpar)
            * sqrt( (lABC(q2,sij,m2s)   - 4.*m2s*pT2ijt)
                   /(lABC(q2,m2Bef,m2s) - 4.*m2s*pT2ijt))
            + qpar * (q2+m2s-sij)/(2.*qpar2) );

  // Construct left-over dipole momentum by momentum conservation.
  Vec4 pij(-q+pRec);

  // Set up transverse momentum vector by using two perpendicular four-vectors.
  pair<Vec4, Vec4> pTvecs = getTwoPerpendicular(pRec, pij);
  Vec4 kTmom( sqrt(kT2)*sin(phi_kt)*pTvecs.first
         + sqrt(kT2)*cos(phi_kt)*pTvecs.second);

  // Construct new radiator momentum.
  pRad.p( zbar * (gABC(q2,sij,m2s)*pij + sij*pRec) / bABC(q2,sij,m2s)
           + (m2Rad+kT2) / (zbar*bABC(q2,sij,m2s))
             * (-pRec - m2s/gABC(q2,sij,m2s)*pij)
           + kTmom);

  // Contruct the emission momentum by momentum conservation.
  pEmt.p(-q-pRad+pRec);

  if ( abs(q.m2Calc()) < 1e-5 && pRadBef.m2Calc() > 0.) { 
    double yCS = (m2Bef - m2Emt - m2Rad)
               / (m2Bef - m2Emt - m2Rad + 2.*pRadBef*pRecBef);
    // Construct FF dipole momentum.
    q.p(pRadBef + pRecBef);
    q2 = q.m2Calc();
    // Calculate derived variables.
    sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2Rad+m2Emt);
    zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
              * (zCS - m2s/gABC(q2,sij,m2s)
                      *(sij + m2Rad - m2Emt)/(q2-sij-m2s));
    kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2Rad - zbar*m2Emt; 

    if (kT2 > 0. ) {
      if (!trial) infoPtr->errorMsg("Info in DireTimes::branch_FI: Recued state "
      "with previously forbidden kT^2.");
      physical = true;
    }

    pair < Vec4, Vec4 > momsAfter = decayWithOnshellRec( zCS, yCS,
    phi_kt, m2s, m2Rad, m2Emt, pRadBef, pRecBef );
    pRad.p(momsAfter.first);
    pEmt.p(momsAfter.second);
    pRec.p(pRecBef);

    if ( abs(pRad.e()-pRad.e()) > 1e5 || pRad.e()  !=pRad.e()
      || abs(pRad.px()-pRad.px())>1e5 || pRad.px() !=pRad.px()
      || abs(pRad.py()-pRad.py())>1e5 || pRad.py() !=pRad.py()
      || abs(pRad.pz()-pRad.pz())>1e5 || pRad.pz() !=pRad.pz())
      physical = false;

  } else {
    if ( abs(pRad.e()-pRad.e()) > 1e5 || pRad.e()  !=pRad.e()
      || abs(pRad.px()-pRad.px())>1e5 || pRad.px() !=pRad.px()
      || abs(pRad.py()-pRad.py())>1e5 || pRad.py() !=pRad.py()
      || abs(pRad.pz()-pRad.pz())>1e5 || pRad.pz() !=pRad.pz())
      physical = false;
  }

  // Ensure that radiator is on mass-shell
  double errMass = abs(pRad.mCalc() - sqrt(m2Rad)) / max( 1.0, pRad.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRad.m2Calc() - m2Rad;
    pRad.e(sqrtpos(pow2(pRad.e()) - deltam2));
  }
  // Ensure that emission is on mass-shell
  errMass = abs(pEmt.mCalc() - sqrt(m2Emt)) / max( 1.0, pEmt.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pEmt.m2Calc() - m2Emt;
    pEmt.e(sqrtpos(pow2(pEmt.e()) - deltam2));
  }
  // Ensure that recoiler is on mass-shell
  errMass = abs(pRec.mCalc() - sqrt(m2s)) / max( 1.0, pRec.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRec.m2Calc() - m2s;
    pRec.e(sqrtpos(pow2(pRec.e()) - deltam2));
  }

  // New: Return if the x-value for the incoming recoiler is nonsense.
  if ( hasPDFrec && physical
    && particleDataPtr->colType(event[iRecBef].id()) != 0
    && 2.*pRec.e()/event[0].m() > 1. ) {
    infoPtr->errorMsg("Error in DireTimes::branch_FI: "
            "Larger than unity Bjorken x value");
    physical = false;
  }

  // Swap emitted and radiator properties for first part of
  // 1->3 splitting (q -> "massive gluon" + q)
  if ( nEmissions == 2 && !split->useForBranching) {
    swap(idRad,idEmt);
    swap(colRad,colEmt);
    swap(acolRad,acolEmt);
  }

  // For emitted color singlet, redefine the colors of the "massive gluon".
  if ( nEmissions == 2 && split->useForBranching
    && particleDataPtr->colType(split->emtAft()->id)  == 0)
    { colRad = event[iRadBef].col(); acolRad = event[iRadBef].acol(); }

  // Define new particles from dipole branching.
  double pTsel = sqrt(tEvol);
  Particle rad = Particle(idRad, 51, iRadBef, 0, 0, 0,
    colRad, acolRad, pRad, sqrt(m2Rad), pTsel);

  // Exempt off-shell radiator from Pythia momentum checks.
  if ( nEmissions == 2 ) rad.status(59);

  Particle emt = Particle(idEmt, 51, iRadBef, 0, 0, 0,
    colEmt, acolEmt, pEmt, sqrt(m2Emt), pTsel);
  Particle rec = Particle(event[iRecBef].id(), -53, 0, 0, iRecBef, iRecBef,
    event[iRecBef].col(), event[iRecBef].acol(), pRec, 0., pTsel);

  // Default to stored color info for intermediate step in 1->3 branching. 
  if ( nEmissions == 2 && split->useForBranching ) {
    /*if ( split->extras.find("colRadInt") != split->extras.end() )
      rad.col(int(split->extras["colRadInt"]));
    if ( split->extras.find("acolRadInt") != split->extras.end() )
      rad.acol(int(split->extras["acolRadInt"]));
    if ( split->extras.find("colEmtInt") != split->extras.end() )
      emt.col(int(split->extras["colEmtInt"]));
    if ( split->extras.find("acolEmtInt") != split->extras.end() )
      emt.acol(int(split->extras["acolEmtInt"]));*/
    if ( split->colRadInt != -1)  rad.col(split->colRadInt);
    if ( split->acolRadInt != -1) rad.acol(split->acolRadInt);
    if ( split->colEmtInt != -1)  emt.col(split->colEmtInt);
    if ( split->acolEmtInt != -1) emt.acol(split->acolEmtInt);
  }

  // Save properties to be restored in case of user-hook veto of emission.
  int evSizeOld    = event.size();
  int iRadStatusV  = event[iRadBef].status();
  int iRadDau1V    = event[iRadBef].daughter1();
  int iRadDau2V    = event[iRadBef].daughter2();
  int iRecMot1V    = event[iRecBef].mother1();
  int iRecMot2V    = event[iRecBef].mother2();
  int beamOff1     = 1 + beamOffset;
  int beamOff2     = 2 + beamOffset;
  int ev1Dau1V     = event[beamOff1].daughter1();
  int ev2Dau1V     = event[beamOff2].daughter1();

  // Shower may occur at a displaced vertex.
  if (event[iRadBef].hasVertex()) {
    rad.vProd( event[iRadBef].vProd() );
    emt.vProd( event[iRadBef].vProd() );
  }
  if (event[iRecBef].hasVertex()) rec.vProd( event[iRecBef].vProd() );

  // Put new particles into the event record.
  // Mark original dipole partons as branched and set daughters/mothers.
  int iRad = int(event.append(rad));
  int iEmt = int(event.append(emt));
  int iEmt2(iEmt);
  event[iRadBef].statusNeg();
  event[iRadBef].daughters( iRad, iEmt);
  int iRec = event.append(rec);
  event[iRecBef].mothers( iRec, iRec);
  event[iRec].mothers( iRecMot1V, iRecMot2V);
  int iBeam1Dau1 = event[beamOff1].daughter1();
  int iBeam2Dau1 = event[beamOff2].daughter1();
  if (iSysSelRec == 0 && iRecMot1V == beamOff1) event[beamOff1].daughter1( iRec);
  if (iSysSelRec == 0 && iRecMot1V == beamOff2) event[beamOff2].daughter1( iRec);

  if ( nEmissions == 2 && !split->useForBranching) swap(iRad,iEmt);

  if (name==testname && testps=="FI") direInfoPtr->message(1) << __LINE__
  << " " << name << " z=" << z << " tEvol=" << tEvol << endl;

  bool doVeto = false;
  bool doMECreject = false; 
  if ( nEmissions != 2) {

    // Check momenta.
    if ( !validMomentum( rad.p(), idRad, 1)
      || !validMomentum( emt.p(), idEmt, 1)
      || !validMomentum( rec.p(), event[iRecBef].id(), -1) )
      physical = false;

    bool inResonance = (partonSystemsPtr->getInA(iSysSel) == 0) ? true : false;
    doVeto = (( canVetoEmission && userHooksPtr->doVetoFSREmission(
                evSizeOld,event,iSysSel,inResonance) )
          ||  ( canMergeFirst && mergingHooksPtr->doVetoEmission(
                event) ));

    double xm = 2. * pRec.e() / (beamAPtr->e() + beamBPtr->e());

    // Reject if momentum fraction is unphysical.
    if (hasPDFrec && xm > 1.) physical = false;

    // Check that beam still has leftover momentum.
    BeamParticle& beamRec = (isrType == 1) ? *beamAPtr : *beamBPtr;
    if (hasPDFrec && beamRec.size() > 0) {
      double xOld = beamRec[iSysSelRec].x();
      beamRec[iSysSelRec].iPos(iRec);
      beamRec[iSysSelRec].x(xm);
      if (beamRec.xMax(-1) < 0.0) {
        if (!trial) infoPtr->errorMsg("Warning in DireTimes::branch_FI: "
          "used up beam momentum; discard splitting.");
        physical = false;
      }

      // Restore old beams.
      beamRec[iSysSelRec].iPos(iRecBef);
      beamRec[iSysSelRec].x(xOld);
    }

    // Apply ME correction if necessary.
    if ( isHardSystem && physical && doMEcorrections && !trial
      && tEvol > pT2minMECs /*&& checkSIJ(event,Q2minMECs)*/) {

#ifdef MG5MES

      // Temporarily update parton systems.
      partonSystemsPtr->replace(iSysSel, iRadBef, iRad);
      partonSystemsPtr->addOut(iSysSel, iEmt);
      partonSystemsPtr->replace(iSysSelRec, iRecBef, iRec);

      if ( evtUtils->checkSIJhard(event, iSysSel, false, Q2minMECs)
        && ( nFinalMaxMECs < 0
          || nFinalMaxMECs > partonSystemsPtr->sizeOut(iSysSel)))
        doMECreject = applyMEC (event, split, iRad, iEmt, iRec);

      // Undo update of parton systems.
      partonSystemsPtr->replace(iSysSel, iRad, iRadBef);
      partonSystemsPtr->replace(iSysSelRec, iRec, iRecBef);
      partonSystemsPtr->popBackOut(iSysSel);

#else

      doMECreject = false;

#endif

    }

    // Just update dipoles and beams.
    if ( physical && !doVeto && !trial && !doMECreject) updateAfterFI( iSysSel, iSysSelRec,
      event, iRadBef, iRecBef, iRad, iEmt, iRec, flavour, colType, pTsel, xm);

  // Heavy particle 1->2 decay for "second step" in 1->3 splitting.
  } else {

    // Check momenta.
    if ( !validMomentum( emt.p(), idEmt, 1)
      || !validMomentum( rec.p(), event[iRecBef].id(), -1)) {
      physical = false;}

    int iRadOld = int(event.size())-3;
    int iEmtOld = int(event.size())-2;
    int iRecOld = int(event.size())-1;

    // Swap emitted and radiator indices.
    swap(iRadOld,iEmtOld);

    if (!split->useForBranching) {
      // Flavours already fixed by 1->3 kernel.
      idEmt        = -flavourSave;
      idRad        =  flavourSave;
      // Colour tags for new particles in branching.
      if (idEmt < 0) {
        colEmt  = 0;
        acolEmt = event[iEmtOld].acol();
        colRad  = event[iEmtOld].col();
        acolRad = 0;
      } else {
        colEmt  = event[iEmtOld].col();
        acolEmt = 0;
        colRad  = 0;
        acolRad = event[iEmtOld].acol();
      }
    // Already correctly read id and colors from SplitInfo object.
    } else {
      idRad   = split->radAft()->id;
      idEmt   = split->emtAft2()->id;
      colRad  = split->radAft()->col;
      acolRad = split->radAft()->acol;
      colEmt  = split->emtAft2()->col;
      acolEmt = split->emtAft2()->acol;
    }

    // Get particle masses.
    m2Bef = m2ai;
    m2r   = particleDataPtr->isResonance(idRad)
              && idRad == event[iRadBef].id()
          ? getMass(idRad,3,event[iRadBef].mCalc())
          : (abs(idRad) < 6 || idRad == 21 || idRad == 22)
          ? getMass(idRad,2)
          : getMass(idRad,1);
    m2e   = (abs(idEmt) < 6 || idEmt == 21 || idEmt == 22)
          ? getMass(idEmt,2) : getMass(idEmt,1);

    if (split->useForBranching) {
      m2r = split->kinematics()->m2RadAft;
      m2e = split->kinematics()->m2EmtAft2;
    }

    // Construct FF dipole momentum.
    Vec4 pa1(event[iEmtOld].p());
    Vec4 pb(event[iRecOld].p());
    q.p(pa1 + pb);
    q2 = q.m2Calc();

    // Calculate CS variables.
    m2Emt      = m2e;
    m2Rad      = m2e;

    if (split->useForBranching) {
      m2Rad = split->kinematics()->m2RadAft;
      m2Emt = split->kinematics()->m2EmtAft2;
    }

    zCS        = xa;
    double yCS = (m2ai - m2Emt - m2Rad) / (m2ai - m2Emt - m2Rad + 2.*pa1*pb);

    // Calculate derived variables.
    sij  = yCS * (q2 - m2s) + (1.-yCS)*(m2Rad+m2Emt);
    zbar = (q2-sij-m2s) / bABC(q2,sij,m2s)
                * (zCS - m2s/gABC(q2,sij,m2s)
                       *(sij + m2Rad - m2Emt)/(q2-sij-m2s));
    kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2Rad - zbar*m2Emt; 

    // Not possible to construct kinematics if kT2 < 0.0
    if (kT2 < 0.) {
      infoPtr->errorMsg("Warning in DireTimes::branch_FI: Reject state "
        "with kinematically forbidden kT^2.");
      physical = false;
    }

    // NaN kT2 can happen for a 1->3 splitting in which the g->QQ~ produces
    // massive quarks Q. 
    if (physical && (kT2!=kT2 || abs(kT2-kT2) > 1e5) ) {
      infoPtr->errorMsg("Warning in DireTimes::branch_FI: Reject state "
        "with not-a-number kT^2 for branching " + name);
      physical = false;
    }

    // Update dipoles and beams.
    double xm = 2. * event[iRecOld].e() / (beamAPtr->e() + beamBPtr->e());

    // Check that beam still has leftover momentum.
    BeamParticle& beamRec = (isrType == 1) ? *beamAPtr : *beamBPtr;
    if (hasPDFrec && beamRec.size() > 0) {
      double xOld = beamRec[iSysSelRec].x();
      beamRec[iSysSelRec].iPos(iRec);
      beamRec[iSysSelRec].x(xm);
      if (beamRec.xMax(-1) < 0.0) {
        if (!trial) infoPtr->errorMsg("Warning in DireTimes::branch_FI: "
          "used up beam momentum; discard splitting.");
        physical = false;
      }
      // Restore old beams.
      beamRec[iSysSelRec].iPos(iRecBef);
      beamRec[iSysSelRec].x(xOld);
    }

    // Boost the transverse momentum vector into the lab frame.
    // Construct left-over dipole momentum by momentum conservation.
    pij.p(q-pb);

    // Set up transverse momentum vector by using two perpendicular four-vectors.
    pTvecs = getTwoPerpendicular(pb, pij);
    kTmom.p( sqrt(kT2)*sin(phiX)*pTvecs.first
           + sqrt(kT2)*cos(phiX)*pTvecs.second);

    // Construct new radiator momentum.
    pRad.p( zbar * (gABC(q2,sij,m2s)*pij - sij*pb) / bABC(q2,sij,m2s)
              + (m2Rad+kT2) / (zbar*bABC(q2,sij,m2s))
                * (pb - m2s/gABC(q2,sij,m2s)*pij)
              + kTmom);

    // Contruct the emission momentum by momentum conservation.
    pEmt.p(q-pRad-pb);

    // Recoiler unchanged.
    pRec.p(event[iRecOld].p());

    // Check invariants.
    if ( false ) {
      Vec4 pa(pRad), pk(pRec), pj(emt.p()), pi(pEmt);
      double saix(2.*pa*pi), sakx(2.*pa*pk), sajx(2.*pa*pj), sikx(2.*pi*pk),
             sjkx(2.*pj*pk), sijx(2.*pi*pj);
      double pptt = (sajx+sijx)*(sakx+sikx)/( sakx + sikx + sjkx);
      double ssaaii = saix; 
      double zzaa = sakx / ( sakx + sikx + sjkx );
      double xxaa = sakx / ( sakx + sikx ); 

      if ( physical &&
          (abs(pptt-tEvol) > 1e-5 || abs(ssaaii-sai) > 1e-5 ||
           abs(zzaa-z) > 1e-5   || abs(xxaa-xa) > 1e-5) ){

        cout << scientific << setprecision(8);
        cout << "Error in branch_FI: Invariant masses after branching do not "
             << "match chosen values." << endl;
        cout << "Chosen:    "
             << " Q2 " << (event[iRadBef].p()-event[iRecBef].p()).m2Calc()
             << " pT2 " << tEvol
             << " sai " << sai
             << " za " << z
             << " xa " << xa << endl;
        cout << "Generated: "
             << " Q2 " << -sakx + saix + sajx +sijx -sikx - sjkx
             << " pT2 " << pptt
             << " sai " << ssaaii
             << " za " << zzaa
             << " xa " << xxaa << endl;
        physical = false;
      }
    }

    // Check momenta.
    if ( !validMomentum( pRad, idRad, 1)
      || !validMomentum( pEmt, idEmt, 1)
      || !validMomentum( pRec, event[iRecOld].id(), -1) ) {
      physical = false;}

    // Check that beam still has leftover momentum.
    if ( particleDataPtr->colType(event[iRecOld].id()) != 0
      && beamRec.size() > 0) {
      double xOld = beamRec[iSysSelRec].x();
      int iOld    = beamRec[iSysSelRec].iPos();
      double xNew = 2.*pRec.e() / (beamAPtr->e() + beamBPtr->e());
      int iNew    = event.append(Particle(event[iRecOld].id(), -53, 0, 0, iRecOld,
        iRecOld, event[iRecOld].col(), event[iRecOld].acol(), pRec, 0., pTsel));
      beamRec[iSysSelRec].iPos(iNew);
      beamRec[iSysSelRec].x(xNew);
      if (beamRec.xMax(-1) < 0.0) {
        if (!trial) infoPtr->errorMsg("Warning in DireTimes::branch_FI: "
          "used up beam momentum; discard splitting.");
        physical = false;
      }
      // Restore old beams.
      event.popBack();
      beamRec[iSysSelRec].iPos(iOld);
      beamRec[iSysSelRec].x(xOld);
    }

    // Update bookkeeping
    int iRadNew(0), iEmtNew(0);
    if (physical) {

      // Define new particles from dipole branching.
      Particle rad2 = Particle(idRad, 51, iEmtOld, 0, 0, 0,
        //colRad, acolRad, pRad, sqrt(m2r), pTsel);
        colRad, acolRad, pRad, sqrt(m2Rad), pTsel);
      Particle emt2 = Particle(idEmt, 51, iEmtOld, 0, 0, 0,
        //colEmt, acolEmt, pEmt, sqrt(m2e), pTsel);
        colEmt, acolEmt, pEmt, sqrt(m2Emt), pTsel);
      Particle rec2 = Particle(event[iRecOld].id(), -53, 0, 0, iRecOld,
        iRecOld, event[iRecOld].col(), event[iRecOld].acol(), pRec, 0., pTsel);

      // Shower may occur at a displaced vertex.
      if (!trial) {
        if (event[iEmtOld].hasVertex()) {
          rad2.vProd( event[iEmtOld].vProd() );
          emt2.vProd( event[iEmtOld].vProd() );
        }
        if (event[iRecOld].hasVertex()) rec2.vProd( event[iRecOld].vProd() );
      }

      // Put new particles into the event record.
      // Mark original dipole partons as branched and set daughters/mothers.
      iRadNew = event.append(rad2);
      iEmtNew = event.append(emt2);
      event[iEmtOld].statusNeg();
      event[iEmtOld].daughters( iRadNew, iEmtNew);

      iRecMot1V    = event[iRecOld].mother1();
      iRecMot2V    = event[iRecOld].mother2();
      iRec = event.append(rec2);
      event[iRecOld].statusNeg();
      event[iRecOld].mothers( iRec, iRec);
      event[iRec].mothers( iRecMot1V, iRecMot2V);
      if (iRecMot1V == beamOff1) event[beamOff1].daughter1( iRec);
      if (iRecMot1V == beamOff2) event[beamOff2].daughter1( iRec);

    }

    // Apply ME correction if necessary.
    if ( isHardSystem && physical && doMEcorrections && !trial
      && tEvol > pT2minMECs) {

#ifdef MG5MES

      // Temporarily update parton systems.
      partonSystemsPtr->replace(iSysSel, iRadBef, iRad);
      partonSystemsPtr->addOut(iSysSel, iEmt);
      partonSystemsPtr->replace(iSysSelRec, iRecBef, iRec);
      // Temporarily update parton systems.
      partonSystemsPtr->replace(iSysSel, iRad, iRadNew);
      partonSystemsPtr->addOut(iSysSel, iEmtNew);

      if ( evtUtils->checkSIJhard(event, iSysSel, false, Q2minMECs)
        && ( nFinalMaxMECs < 0
          || nFinalMaxMECs > partonSystemsPtr->sizeOut(iSysSel)))
        doMECreject = applyMEC (event, split, iRad, iEmt, iRec);

      // Undo update of parton systems.
      partonSystemsPtr->replace(iSysSel, iRadNew, iRadBef);
      partonSystemsPtr->replace(iSysSelRec, iRec, iRecBef);
      partonSystemsPtr->popBackOut(iSysSel);
      partonSystemsPtr->popBackOut(iSysSel);

#else

      doMECreject = false;

#endif

    }

    double xx0 = 2. * event[iRecOld].e() / (beamAPtr->e() + beamBPtr->e());
    double xx1 = 2. * event[iRec].e()    / (beamAPtr->e() + beamBPtr->e());

    // Reject if momentum fraction is unphysical.
    if (xx1 > 1.) physical = false;

    if ( physical && !trial && !doMECreject) updateAfterFI( iSysSel, 
      iSysSelRec, event, iRadBef, iRecBef, iRad, iEmt, iRec, flavour, colType,
      pTsel, xx0);
    if ( physical && !trial && !doMECreject) updateAfterFI( iSysSel, 
      iSysSelRec, event, iEmtOld, iRecOld, iRadNew, iEmtNew, iRec, flavourSave,
      colType, pTsel, xx1);

    // Reset particle positions for later storage.
    iEmt = iEmtNew;
    iRad = iRadNew;

  }

  if (tEvol > pT2minMECs && name==testname && testps=="FI") {
    direInfoPtr->printMessages(1); abort();
  }

  physical = physical && !doVeto;

  // Ungraceful exit for incorrect event.
  bool isHadronic        = false;
  for (int i = 0; i < event.size(); ++i)
    if (event[i].statusAbs() > 60) isHadronic = true;
  // Only check competing steps (first part of 1->3 splitting will contain
  // a massive pseudo-gluon).
  if ( physical && !trial && !doMECreject && !isHadronic
    && !validEvent(event)
    && infoPtr->weight() != 0.) {
    infoPtr->errorMsg("Error in DireTimes::branch_FI: State after "
                      "branching not valid, thus reject.");
    //puppybort(__func__);
    physical = false;
  }

  // Temporarily set the daughters in the beams to zero, to
  // allow mother-daughter relation checks.
  if (iSysSelRec > 0) {
    if (iRecMot1V == beamOff1) event[beamOff1].daughter1( iRec);
    if (iRecMot1V == beamOff2) event[beamOff2].daughter1( iRec);
  }

  // Check if mother-daughter relations are correctly set. Check only
  // possible if no MPI are present.
  if ( physical && !trial && !doMECreject && !validMotherDaughter(event)) {
    infoPtr->errorMsg("Error in DireTimes::branch_FI: Mother-daughter "
                      "relations after branching not valid.");
    physical = false;
  }

  // Restore correct daughters in the beams.
  if (iSysSelRec > 0) {
    if (iRecMot1V == beamOff1) event[beamOff1].daughter1(iBeam1Dau1);
    if (iRecMot1V == beamOff2) event[beamOff2].daughter1(iBeam2Dau1);
  }

  // Allow veto of branching. If so restore event record to before emission.
  if ( !physical || doMECreject) {

    event.popBack( event.size() - evSizeOld);
    event[iRadBef].status( iRadStatusV);
    event[iRadBef].daughters( iRadDau1V, iRadDau2V);
    event[iRecBef].mothers( iRecMot1V, iRecMot2V);
    if (iSysSelRec == 0 && iRecMot1V == beamOff1) event[beamOff1].daughter1( ev1Dau1V);
    if (iSysSelRec == 0 && iRecMot1V == beamOff2) event[beamOff2].daughter1( ev2Dau1V);

    // This case is identical to the case where the probability to accept the
    // emission was indeed zero all along. In this case, neither
    // acceptProbability nor rejectProbability would have been filled. Thus,
    // remove the relevant entries from the weight container!
    if (!trial && !physical) {
      for ( unordered_map<string, multimap<double,double> >::iterator
        it = rejectProbability.begin(); it != rejectProbability.end(); ++it){
        weights->eraseAcceptWeight(tEvol, it->first);
        weights->eraseRejectWeight(tEvol, it->first);
      }
    }

    if (!trial && doMECreject) {
      //weights->calcWeight(pT2);
      weights->calcWeight(tEvol, false, true);
      weights->reset();
     // Clear accept/reject weights.
      for ( unordered_map<string, multimap<double,double> >::iterator
        it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
        it->second.clear();
      for ( unordered_map<string, map<double,double> >::iterator
        it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
        it->second.clear();
    }

    return false;
  }

  // Store positions of new particles.
  if (trial && !split->useForBranching) split->storePosAfter( iRad, iRec, iEmt,
    (nEmissions < 2) ? 0 : iEmt2);
  if (trial &&  split->useForBranching) split->storePosAfter( iRad, iRec, iEmt2,
    (nEmissions < 2) ? 0 : iEmt);

  // Set shower weight.
  if (!trial) {
    weights->setSelectedKernel(tEvol, kernelSel);
    if (!doTrialNow) {
      weights->calcWeight(tEvol);
      weights->reset();

      // Store positions of new soft particles.
      direInfoPtr->updateSoftPos( iRadBef, iEmt );
      direInfoPtr->updateSoftPosIfMatch( iRecBef, iRec );
      if (nEmissions > 1) direInfoPtr->addSoftPos( iEmt2 );
      updateDipoles(event, iSysSel);
    }

    // Clear accept/reject weights.
    for ( unordered_map<string, multimap<double,double> >::iterator
      it = rejectProbability.begin(); it != rejectProbability.end(); ++it )
      it->second.clear();
    for ( unordered_map<string, map<double,double> >::iterator
      it = acceptProbability.begin(); it != acceptProbability.end(); ++it )
      it->second.clear();

    updateEvolutionWindows (idEmt, tEvol, iWindowSel);

  }

  // Relabel shower=produced Z- and W-bosons as id's 93 and 94, to avoid that
  // Pythia decays the particles inadvertantly.
  if (doTrialNow) {
    evtUtils->shiftWZbosonID(event, iRad);
    evtUtils->shiftWZbosonID(event, iEmt);
    evtUtils->shiftWZbosonID(event, iEmt2);
    evtUtils->shiftWZbosonID(event, iRec);
  }

  // Done.
  return true;

}

//--------------------------------------------------------------------------

void DireTimes::updateAfterFI( int iSysSelNow, int iSysSelRec, 
  Event& event, int iRadBef, int iRecBef, int iRad, int iEmt, int iRec,
  int, int colType, double pTsel, double xNew) {

  bool hasDipSel   = (dipSel != 0);
  int isrType      = (hasDipSel) ? dipSel->isrType : event[iRec].mother1();
  bool inResonance = (partonSystemsPtr->getInA(iSysSelNow)==0) ? true : false;
  int idEmt        = event[iEmt].id();
  vector<int> iDipEndCorr;

  // For initial-state recoiler also update beam and sHat info.
  BeamParticle& beamRec = (isrType == 1) ? *beamAPtr : *beamBPtr;
  double xOld = beamRec[iSysSelRec].x();
  beamRec[iSysSelRec].iPos( iRec);
  beamRec[iSysSelRec].x( xNew);
  partonSystemsPtr->setSHat( iSysSelRec,
  partonSystemsPtr->getSHat(iSysSelRec) * xNew / xOld);

  // Bookkeep shower-induced resonances.
  if ( direInfoPtr->isRes(iRadBef) && 
    event[iRadBef].id() != event[iRad].id() )
    direInfoPtr->removeResPos(iRadBef);
  if ( particleDataPtr->isResonance(event[iRad].id()) ) {
    if ( direInfoPtr->isRes(iRadBef) )
         direInfoPtr->updateResPos(iRadBef,iRad);
  }
  if ( direInfoPtr->isRes(iRecBef) )
    direInfoPtr->updateResPos(iRecBef,iRec);
  if ( particleDataPtr->isResonance(event[iEmt].id()) )
    direInfoPtr->addResPos(iEmt);

  if (particleDataPtr->colType(idEmt) == 2) {

    if (hasDipSel) {
      dipSel->iRadiator  = iRad;
      dipSel->iRecoiler  = iEmt;
      dipSel->systemRec  = iSysSelRec;
      dipSel->pTmax      = pTsel;
      dipSel->MEtype     = 0;
    }

    for (int i = 0; i < int(dipEnd.size()); ++i) {
      if (dipEnd[i].iRadiator == iRecBef && dipEnd[i].iRecoiler == iRadBef
        && dipEnd[i].colType != 0) {
        dipEnd[i].iRadiator = iRec;
        dipEnd[i].iRecoiler = iEmt;
        dipEnd[i].MEtype = 0;
        // Strive to match colour to anticolour inside closed system.
        if ( dipEnd[i].colType * colType > 0)
          dipEnd[i].iRecoiler = iRad;
        dipEnd[i].pTmax = pTsel;
        iDipEndCorr.push_back(i);
      }
    }
    int colTypeNow = (colType > 0) ? 2 : -2 ;
    // When recoiler was uncoloured particle, in resonance decays,
    // assign recoil to coloured particle.
    int iRecMod = iRec;
    if (recoilToColoured && inResonance && event[iRec].col() == 0
      && event[iRec].acol() == 0) iRecMod = iRad;

    if (appendDipole(event, iEmt, iRecMod, pTsel, colTypeNow, 0, 0, 0, isrType,
          iSysSelNow, 0, -1, 0, false, dipEnd)) {
      iDipEndCorr.push_back(dipEnd.size()-1);
      // Set dipole mass properties.
      DireTimesEnd& dip1 = dipEnd.back();
      dip1.systemRec = iSysSelRec;
    }
    if (appendDipole(event, iEmt, iRad, pTsel, -colTypeNow, 0, 0, 0, 0,
          iSysSelNow, 0, -1, 0, false, dipEnd)) {
      iDipEndCorr.push_back(dipEnd.size()-1);
      // Set dipole mass properties.
      DireTimesEnd& dip2 = dipEnd.back();
      dip2.systemRec = iSysSelRec;
    }

  // Gluon branching to q qbar: update current dipole and other of gluon.
  } else if (particleDataPtr->colType(idEmt) != 0) {

    // Update dipoles for second step in 1->3 splitting.
    //if ( splittingsPtr->nEmissions(splittingSelName) == 2 ){
    if ( splits[splittingSelName]->nEmissions() == 2 ){
      for (int i = 0; i < int(dipEnd.size()); ++i) {

        DireTimesEnd& dip = dipEnd[i];

        if ( dip.iRadiator == iRecBef ) dip.iRadiator = iRec;
        if ( dip.iRecoiler == iRecBef ) dip.iRecoiler = iRec;
        if ( dip.iRadiator == iRadBef ) {
          if (dip.colType > 0)
            dip.iRadiator = (event[iEmt].id() > 0) ? iEmt : iRad;
          if (dip.colType < 0)
            dip.iRadiator = (event[iEmt].id() < 0) ? iEmt : iRad;

          if (abs(dip.colType) == 2
            && event[dip.iRadiator].id()    > 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = abs(dip.colType)/2;
          if (abs(dip.colType) == 2
            && event[dip.iRadiator].id()    < 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = -abs(dip.colType)/2;
          iDipEndCorr.push_back(i);
        }

        if ( dip.iRecoiler == iRadBef ) {
          if (dip.colType > 0)
            dip.iRecoiler = (event[iEmt].id() < 0) ? iEmt : iRad;
          if (dip.colType < 0)
            dip.iRecoiler = (event[iEmt].id() > 0) ? iEmt : iRad;

          if (abs(dip.colType) == 2) dipEnd[i].colType /= 2;

          if (abs(dip.colType) == 1
            && event[dip.iRadiator].id()    > 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = 1;

          if (abs(dip.colType) == 1
            && event[dip.iRadiator].id()    < 0 
            && event[dip.iRadiator].idAbs() < 10)
            dip.colType = -1;
          iDipEndCorr.push_back(i);
        }
      }
    }

    for (int i = 0; i < int(dipEnd.size()); ++i) {
      // Nothing to be done if dipole end has already been updated.
      if ( find(iDipEndCorr.begin(), iDipEndCorr.end(), i)
        != iDipEndCorr.end() ) continue;
      // Strive to match colour to anticolour inside closed system.
      if ( dipEnd[i].iRecoiler == iRadBef
        && dipEnd[i].colType * colType < 0 ) {
        dipEnd[i].iRecoiler = iEmt;
      }
      if (dipEnd[i].iRadiator == iRadBef && abs(dipEnd[i].colType) == 2) {
        dipEnd[i].colType /= 2;

        if (hasDipSel && &dipEnd[i] == dipSel) dipEnd[i].iRadiator  = iEmt;
        else                                   dipEnd[i].iRadiator  = iRad;
        if (hasDipSel && &dipEnd[i] == dipSel) dipEnd[i].iRecoiler  = iRec;

        dipEnd[i].colType = (event[dipEnd[i].iRadiator].id() > 0)
                    ? abs(dipEnd[i].colType) : -abs(dipEnd[i].colType);

        iDipEndCorr.push_back(i);

        if (dipEnd[i].system != dipEnd[i].systemRec) continue;
        dipEnd[i].MEtype = 0;
        if (hasDipSel && &dipEnd[i] == dipSel) dipEnd[i].iMEpartner = iRad;
        else                      dipEnd[i].iMEpartner = iEmt;
      }
    }

    // Nothing to be done if dipole end has already been updated.
    bool updateSel=true;
    for (int j = 0; j < int(iDipEndCorr.size()); ++j)
      if ( hasDipSel && &dipEnd[iDipEndCorr[j]] == dipSel) updateSel = false;

    if (hasDipSel) {
      if (updateSel) {
        dipSel->iRadiator = iEmt;
        dipSel->iRecoiler = iRec;
      }
      // Always update the production pT.
      dipSel->pTmax     = pTsel;
    }

  } else {

    int iRadOld = (hasDipSel) ? dipSel->iRadiator : iRadBef;
    int iRecOld = (hasDipSel) ? dipSel->iRecoiler : iRecBef;

    // Just update old radiator/recoiler to current outgoing particles.
    for (int i = 0; i < int(dipEnd.size()); ++i) {
      DireTimesEnd& dip = dipEnd[i];
      // Update radiator-recoiler end.
      if ( dip.iRecoiler == iRecOld && dip.iRadiator == iRadOld ) {
        dip.iRadiator = iRad;
        dip.iRecoiler = iRec;
        dip.pTmax  = pTsel;
        iDipEndCorr.push_back(i);
      }
      // Update recoiler-radiator end.
      if ( dip.iRecoiler == iRadOld && dip.iRadiator == iRecOld ) {
        dip.iRadiator = iRec;
        dip.iRecoiler = iRad;
        dip.pTmax  = pTsel;
        iDipEndCorr.push_back(i);
      }
    }
  }

  // Now update other dipoles that also involved the radiator or recoiler.
  // Note: For 1->3 splittings, this step has already been done earlier!
  for (int i = 0; i < int(dipEnd.size()); ++i) {
    // Nothing to be done if dipole end has already been updated.
    if ( find(iDipEndCorr.begin(), iDipEndCorr.end(), i)
      != iDipEndCorr.end() ) continue;
    if (dipEnd[i].iRadiator  == iRadBef) dipEnd[i].iRadiator  = iRad;
    if (dipEnd[i].iRecoiler  == iRadBef) dipEnd[i].iRecoiler  = iRad;
    if (dipEnd[i].iMEpartner == iRadBef) dipEnd[i].iMEpartner = iRad;
    if (dipEnd[i].iRadiator  == iRecBef) dipEnd[i].iRadiator  = iRec;
    if (dipEnd[i].iRecoiler  == iRecBef) dipEnd[i].iRecoiler  = iRec;
    if (dipEnd[i].iMEpartner == iRecBef) dipEnd[i].iMEpartner = iRec;
  }

  // Now update or construct new dipoles if the radiator or emission allow
  // for new types of emissions. Careful: do not include initial recoiler
  // as potential radiator.
  vector<pair<int, int> > rad_rec (createvector< pair<int,int> >
    (make_pair(iRad,iEmt))
    (make_pair(iEmt,iRec))
    (make_pair(iEmt,iRad))
    (make_pair(iRad,iRec)));
  for (int i=0; i < int(rad_rec.size()); ++i) {
    int iRadNow = rad_rec[i].first;
    int iRecNow = rad_rec[i].second;
    // Now check if a new dipole end a-b should be added:
    // First check if the dipole end is already existing.
    vector<int> iDip;
    for (int j = 0; j < int(dipEnd.size()); ++j)
      if ( dipEnd[j].iRadiator == iRadNow
        && dipEnd[j].iRecoiler == iRecNow )
        iDip.push_back(j);
    // If the dipole end exists, attempt to update the dipole end (a)
    // for the current a-b dipole. 
    if ( int(iDip.size()) > 0) for (int j = 0; j < int(iDip.size()); ++j)
      updateAllowedEmissions(event, &dipEnd[iDip[j]]);
    // If no dipole exists and idEmtAfter != 0, create new dipole end (a).
    else appendDipole( event, iRadNow, iRecNow, pTsel, 0, 0, 0, 0, 0,
      iSysSelNow, -1, -1, 0, false, dipEnd);
  }

  // Copy or set lifetime for new final state.
  if (event[iRad].id() == event[iRadBef].id()) {
    event[iRad].tau( event[iRadBef].tau() );
  } else {
    event[iRad].tau( event[iRad].tau0() * rndmPtr->exp() );
    event[iEmt].tau( event[iEmt].tau0() * rndmPtr->exp() );
  }
  event[iRec].tau( event[iRecBef].tau() );

  // Finally update the list of all partons in all systems.
  partonSystemsPtr->replace(iSysSel, iRadBef, iRad);
  partonSystemsPtr->addOut(iSysSel, iEmt);
  partonSystemsPtr->replace(iSysSelRec, iRecBef, iRec);

  // Loop through final state of system to find possible new dipole ends.
  for (int i = 0; i < partonSystemsPtr->sizeOut(iSysSelNow); ++i) {
    int iNow = partonSystemsPtr->getOut( iSysSelNow, i);
    if (event[iNow].isFinal() && event[iNow].scale() > 0.) {
      // Find dipole end formed by colour index.
      int colTag = event[iNow].col();
      if (doQCDshower && colTag > 0) setupQCDdip( iSysSelNow, i,  colTag,  1,
        event, false, true);
      // Find dipole end formed by anticolour index.
      int acolTag = event[iNow].acol();
      if (doQCDshower && acolTag > 0) setupQCDdip( iSysSelNow, i, acolTag, -1,
        event, false, true);
      // Now find non-QCD dipoles and/or update the existing dipoles.
      getGenDip( iSysSelNow, i, iNow, event, false, dipEnd);
    }
    // Setup decay dipoles.
    if (doDecaysAsShower && event[iNow].isResonance())
      setupDecayDip( iSysSelNow, iNow, event, dipEnd);
  }

  // Now update all dipoles.
  dipSel = 0;
  updateDipoles(event, iSysSel);

  // Done.
}

//--------------------------------------------------------------------------

pair < Vec4, Vec4 > DireTimes::decayWithOnshellRec( double zCS, double yCS,
  double phi, double m2Rec, double m2RadAft, double m2EmtAft,
  Vec4 pRadBef, Vec4 pRecBef ) {

  // Construct FF dipole momentum.
  Vec4 q(pRadBef + pRecBef);
  double q2 = q.m2Calc();

  // Calculate derived variables.
  double sij  = yCS * (q2 - m2Rec) + (1.-yCS)*(m2RadAft+m2EmtAft);
  double zbar = (q2-sij-m2Rec) / bABC(q2,sij,m2Rec)
             * (zCS - m2Rec/gABC(q2,sij,m2Rec)
                     *(sij + m2RadAft - m2EmtAft)/(q2-sij-m2Rec));
  double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2RadAft - zbar*m2EmtAft; 

  double physical = true;
  if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5 ) physical = false;
  if (abs(kT2) < 1e-9) kT2 = 0.0;

  // Construct left-over dipole momentum by momentum conservation.
  Vec4 pij(q-pRecBef);

  // Set up transverse momentum vector by using two perpendicular 4-vectors.
  pair <Vec4, Vec4> pTvecs = getTwoPerpendicular(pRecBef, pij);
  Vec4 kTmom( sqrt(kT2)*sin(phi)*pTvecs.first
            + sqrt(kT2)*cos(phi)*pTvecs.second);

  // Construct new radiator momentum.
  Vec4 pRad( zbar * (gABC(q2,sij,m2Rec)*pij - sij*pRecBef)/bABC(q2,sij,m2Rec)
            + (m2RadAft+kT2) / (zbar*bABC(q2,sij,m2Rec))
              * (pRecBef - m2Rec/gABC(q2,sij,m2Rec)*pij)
            + kTmom);

  // Contruct the emission momentum by momentum conservation.
  Vec4 pEmt(q-pRad-pRecBef);
  // Recoiler unchanged.
  Vec4 pRec(pRecBef);

  // Store and return.
  pair < Vec4, Vec4 > ret;
  if (physical) ret = make_pair(pRad,pEmt);
  return ret;

}

//--------------------------------------------------------------------------

pair <Vec4, Vec4> DireTimes::decayWithOffshellRec( double zCS, double yCS,
  double phi, double m2RadBef, double m2RadAft, double m2EmtAft,
  Vec4 pRadBef, Vec4 pRecBef ) {

  Vec4 q(pRadBef + pRecBef);
  double q2 = q.m2Calc();
  // Calculate derived variables.
  double sij  = yCS * (q2 - m2RadBef) + (1.-yCS)*(m2RadAft+m2EmtAft);
  double zbar = (q2-sij-m2RadBef) / bABC(q2,sij,m2RadBef)
              * (zCS - m2RadBef/gABC(q2,sij,m2RadBef)
                     *(sij + m2RadAft - m2EmtAft)/(q2-sij-m2RadBef));
  double kT2  = zbar*(1.-zbar)*sij - (1.-zbar)*m2RadAft - zbar*m2EmtAft; 

  // Not possible to construct kinematics if kT2 < 0.0
  bool physical = true;
  if (kT2 < 0. || kT2!=kT2 || abs(kT2-kT2) > 1e5 ) physical = false;

  // Construct left-over dipole momentum by momentum conservation.
  Vec4 pij(q-pRadBef);

  // Set up transverse momentum vector by using two perpendicular four-vectors.
  pair < Vec4, Vec4> pTvecs = getTwoPerpendicular(pRadBef, pij);
  Vec4 kTmom( sqrt(kT2)*sin(phi)*pTvecs.first
            + sqrt(kT2)*cos(phi)*pTvecs.second);

  // Construct new radiator momentum.
  Vec4 pRec2( zbar * (gABC(q2,sij,m2RadBef)*pij - sij*pRadBef) / bABC(q2,sij,m2RadBef)
            + (m2RadAft+kT2) / (zbar*bABC(q2,sij,m2RadBef))
              * (pRadBef - m2RadBef/gABC(q2,sij,m2RadBef)*pij)
            + kTmom);

  // Contruct the emission momentum by momentum conservation.
  Vec4 pRec1(q-pRec2-pRadBef);

  // Store and return.
  pair < Vec4, Vec4 > ret;
  if (physical) ret = make_pair(pRec1,pRec2);
  return ret;

}

//--------------------------------------------------------------------------

//Event DireTimes::clustered( const Event& state, int iRad, int iEmt, int iRec,
//  string name ) {
pair <Event, pair<int,int> > DireTimes::clustered_internal( const Event& state,
  int iRad, int iEmt1, int iEmt2, int iRec, string name ) {

  if (name.compare("Dire_fsr_qcd_1->21&1") == 0 && state[iRad].id() == 21)
    swap(iRad,iEmt1);
  if (name.compare("Dire_fsr_qed_1->22&1") == 0 && state[iRad].id() == 22)
    swap(iRad,iEmt1);
  if (name.compare("Dire_fsr_qed_11->22&11") == 0 && state[iRad].id() == 22)
    swap(iRad,iEmt1);

  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iRec));
  if (iEmt2>0) iExc.push_back(iEmt2);

  // Flags for type of radiation
  int radType = state[iRad].isFinal() ? 1 : -1;
  int recType = state[iRec].isFinal() ? 1 : -1;

  // Construct the clustered event
  Event NewEvent(15);
  NewEvent.init("(hard process-modified)", particleDataPtr);
  NewEvent.initColTag(state.lastColTag()+1000);
  //NewEvent.clear();
  // Copy all unchanged particles to NewEvent
  for (int i = 0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    //if ( i != iRad && i != iRec && i != iEmt1 && i != iEmt2)
    NewEvent.append( state[i] );
  }

  // Copy all the junctions one by one
  for (int i = 0; i < state.sizeJunction(); ++i)
    NewEvent.appendJunction( state.getJunction(i) );
  // Find an appropriate scale for the hard process
  double mu = infoPtr->QFac();
  // Initialise scales for new event
  NewEvent.saveSize();
  NewEvent.saveJunctionSize();
  NewEvent.scale(mu);
  NewEvent.scaleSecond(mu);

  // Set properties of radiator/recoiler after the clustering
  // Recoiler properties will be unchanged
  Particle RecBefore = Particle( state[iRec] );
  RecBefore.setEvtPtr(&NewEvent);
  RecBefore.daughters(0,0);

  // Find flavour of radiator before splitting
  int radID = splits[name]->radBefID(state[iRad].id(), state[iEmt1].id());
  int recID = state[iRec].id();
  Particle RadBefore = Particle( state[iRad] );
  RadBefore.setEvtPtr(&NewEvent);
  RadBefore.id(radID);
  RadBefore.daughters(0,0);
  // Put dummy values for colours
  RadBefore.cols(RecBefore.acol(),RecBefore.col());

  // Reset status if the reclustered radiator is a resonance.
  if ( particleDataPtr->isResonance(radID) && radType == 1)
    RadBefore.status(22);

  // Put mass for radiator and recoiler
  double radMass = particleDataPtr->m0(radID);
  double recMass = particleDataPtr->m0(recID);
  if (radType == 1 ) RadBefore.m(radMass);
  else RadBefore.m(0.0);
  if (recType == 1 ) RecBefore.m(recMass);
  else RecBefore.m(0.0);

  if ( particleDataPtr->isResonance(radID) && radType == 1 )
    RadBefore.m( (state[iRad].p()+state[iEmt1].p()).mCalc() );
  if ( particleDataPtr->isResonance(recID) && radType == 1 )
    RadBefore.m(  state[iRec].mCalc() );

  // Construct momenta and  colours of clustered particles.
  bool validState = false;
  if ( state[iRec].isFinal()) validState = cluster_FF(state, iRad, iEmt1,
    iEmt2, iRec, radID, name, RadBefore, RecBefore);
  else                        validState = cluster_FI(state, iRad, iEmt1,
    iEmt2, iRec, radID, name, RadBefore, RecBefore);

  // Put some dummy production scales for RecBefore, RadBefore
  RecBefore.scale(mu);
  RadBefore.scale(mu);

  // Append new recoiler and find new radiator colour
  NewEvent.append(RecBefore);

  // Assign the correct colour to re-clustered radiator.
  pair<int,int> cols = splits[name]->radBefCols( state[iRad].col(),
    state[iRad].acol(), state[iEmt1].col(), state[iEmt1].acol());
  RadBefore.cols( cols.first, cols.second );

  // Build the clustered event
  Event outState(15);
  outState.init("(hard process-modified)", particleDataPtr);
  outState.initColTag(NewEvent.lastColTag());

  // Clustering might not be possible due to phase space constraints.
  if (!validState) { return make_pair(outState, make_pair(0,0)); }

  // Copy system and incoming beam particles to outState
  for (int i = 0; i < 3; ++i)
    outState.append( NewEvent[i] );
  // Copy all the junctions one by one
  for (int i = 0; i < state.sizeJunction(); ++i)
    outState.appendJunction( state.getJunction(i) );
  // Initialise scales for new event
  outState.saveSize();
  outState.saveJunctionSize();
  outState.scale(mu);
  outState.scaleSecond(mu);
  bool radAppended = false;
  bool recAppended = false;
  int size = int(outState.size());
  // Save position of radiator in new event record
  int radPos(0), recPos(0);

  // Append first incoming particle
  if ( RecBefore.mother1() == 1) {
    recPos = outState.append( RecBefore );
    recAppended = true;
  } else if ( RadBefore.mother1() == 1 ) {
    radPos = outState.append( RadBefore );
    radAppended = true;
  } else {
    // Find second incoming in input event
    int in1 = 0;
    for(int i=0; i < int(state.size()); ++i)
      if (state[i].mother1() == 1) in1 =i;
    outState.append( state[in1] );
    size++;
  }
  // Append second incoming particle
  if ( RecBefore.mother1() == 2) {
    recPos = outState.append( RecBefore );
    recAppended = true;
  } else if ( RadBefore.mother1() == 2 ) {
    radPos = outState.append( RadBefore );
    radAppended = true;
  } else {
    // Find second incoming in input event
    int in2 = 0;
    for(int i=0; i < int(state.size()); ++i)
      if (state[i].mother1() == 2) in2 =i;

    outState.append( state[in2] );
    size++;
  }

  // Append new recoiler if not done already
  if (!recAppended && !RecBefore.isFinal()) {
    recAppended = true;
    recPos = outState.append( RecBefore);
  }
  // Append new radiator if not done already
  if (!radAppended && !RadBefore.isFinal()) {
    radAppended = true;
    radPos = outState.append( RadBefore);
  }

  // Append intermediate particle
  // (careful not to append reclustered recoiler)
  for (int i = 0; i < int(NewEvent.size()-1); ++i) {
    if (NewEvent[i].status() != -22) continue;
    if ( NewEvent[i].daughter1() == NewEvent[i].daughter2()
      && NewEvent[i].daughter1() > 0) continue;
    outState.append( NewEvent[i] );
  }

  // Append final state particles, resonances first
  for (int i = 0; i < int(NewEvent.size()-1); ++i)
    if (NewEvent[i].status() == 22) {
      outState.append( NewEvent[i] );
    }

  // Then start appending partons
  if (!radAppended && RadBefore.statusAbs() == 22)
    radPos = outState.append(RadBefore);
  if (!recAppended)
    recPos= outState.append(RecBefore);
  if (!radAppended && RadBefore.statusAbs() != 22)
    radPos = outState.append(RadBefore);
  // Then partons (not reclustered recoiler)
  for(int i = 0; i < int(NewEvent.size()-1); ++i)
    if ( NewEvent[i].status()  != 22
      && NewEvent[i].colType() != 0
      && NewEvent[i].isFinal())
      outState.append( NewEvent[i] );
  // Then the rest
  for(int i = 0; i < int(NewEvent.size()-1); ++i)
    if ( NewEvent[i].status() != 22
      && NewEvent[i].colType() == 0
      && NewEvent[i].isFinal() )
      outState.append( NewEvent[i]);

  // Find intermediate and respective daughters
  vector<int> PosIntermediate;
  vector<int> PosDaughter1;
  vector<int> PosDaughter2;
  for(int i=0; i < int(outState.size()); ++i) {
    if (outState[i].status() == -22) {
      PosIntermediate.push_back(i);
      int d1 = outState[i].daughter1();
      int d2 = outState[i].daughter2();
      // Find daughters in output state. To work properly, daughter1 should
      // always be smaller than daughter2.
      int daughter1 = FindParticle( state[d1], outState);
      int daughter2 = FindParticle( state[d2], outState);

// DEBUG!
//      if (daughter1 == -1 && daughter2 > -1) swap (daughter1,daughter2);
      if ( daughter1 == -1 || daughter2 == -1) daughter1 = daughter2 = -1;
      if ( daughter1 == -1 && daughter2 == -1
        && daughter1 > daughter2) swap (daughter1,daughter2);

      // If both daughters found, done
      // Else put first final particle as first daughter
      // and last final particle as second daughter
      if (daughter1 > -1)
        PosDaughter1.push_back( daughter1);
      else {
        daughter1 = 0;
        while(!outState[daughter1].isFinal() ) daughter1++;
        PosDaughter1.push_back( daughter1);
      }
      if (daughter2 > -1)
        PosDaughter2.push_back( daughter2);
      else {
        daughter2 = outState.size()-1;
        while(!outState[daughter2].isFinal() ) daughter2--;
        PosDaughter2.push_back( daughter2);
      }

    }
  }

  int iOut1 = 0;
  while(!outState[iOut1].isFinal() ) iOut1++;
  int iOut2 = outState.size()-1;
  while(!outState[iOut2].isFinal() ) iOut2--;

  // Set daughters and mothers
  for(int i=0; i < int(PosIntermediate.size()); ++i) {
    outState[PosIntermediate[i]].daughters(PosDaughter1[i],PosDaughter2[i]);
    outState[PosDaughter1[i]].mother1(PosIntermediate[i]);
    outState[PosDaughter2[i]].mother1(PosIntermediate[i]);
    outState[PosDaughter1[i]].mother2(0);
    outState[PosDaughter2[i]].mother2(0);
  }

  // Force outgoing particles to be part of hard process.
  for ( int i=0; i < int(outState.size()); ++i) {
    if (outState[i].isFinal()) outState[i].status(23);
  }

  // Find range of final state partons
  int minParFinal = int(outState.size());
  int maxParFinal = 0;
  for(int i=0; i < int(outState.size()); ++i)
    if (outState[i].mother1() == 3 && outState[i].mother2() == 4) {
      minParFinal = min(i,minParFinal);
      maxParFinal = max(i,maxParFinal);
    }

  if (minParFinal == maxParFinal) maxParFinal = 0;
  outState[3].daughters(minParFinal,maxParFinal);
  outState[4].daughters(minParFinal,maxParFinal);

  // Update event properties
  outState.saveSize();
  outState.saveJunctionSize();

  // Almost there...
  // If an intermediate coloured parton exists which was directly
  // colour connected to the radiator before the splitting, and the
  // radiator before and after the splitting had only one colour, problems
  // will arise since the colour of the radiator will be changed, whereas
  // the intermediate parton still has the old colour. In effect, this
  // means that when setting up a event for trial showering, one colour will
  // be free.
  // Hence, check for an intermediate coloured triplet resonance has been
  // colour-connected to the "old" radiator.
  // Find resonance
  int iColRes = 0;
  if ( radType == -1 && state[iRad].colType() == 1) {
      // Find resonance connected to initial colour
      for(int i=0; i < int(state.size()); ++i) {
        if (find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
        if (state[i].status() == -22 && state[i].col() == state[iRad].col() )
          iColRes = i;
      }
  } else if ( radType == -1 && state[iRad].colType() == -1) {
      // Find resonance connected to initial anticolour
      for(int i=0; i < int(state.size()); ++i) {
        if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
        if (state[i].status() == -22 && state[i].acol() == state[iRad].acol() )
          iColRes = i;
      }
  } else if ( radType == 1 && state[iRad].colType() == 1) {
      // Find resonance connected to final state colour
      for(int i=0; i < int(state.size()); ++i) {
        if (find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
        if (state[i].status() == -22 && state[i].col() == state[iRad].col() )
          iColRes = i;
      }
  } else if ( radType == 1 && state[iRad].colType() == -1) {
      // Find resonance connected to final state anticolour
      for(int i=0; i < int(state.size()); ++i) {
        if (find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
        if (state[i].status() == -22 && state[i].acol() == state[iRad].acol() )
          iColRes = i;
      }
  }

  if (iColRes > 0) {
    // Now find this resonance in the reclustered state
    int iColResNow = FindParticle( state[iColRes], outState);

    // Find reclustered radiator colours
    int radCol = outState[radPos].col();
    int radAcl = outState[radPos].acol();
    // Find resonance radiator colours
    int resCol = iColResNow>-1 ? outState[iColResNow].col()  : -1;
    int resAcl = iColResNow>-1 ? outState[iColResNow].acol() : -1;
    // Check if any of the reclustered radiators colours match the resonance
    bool matchesRes =  (radCol > 0
                          && ( radCol == resCol || radCol == resAcl))
                    || (radAcl > 0
                          && ( radAcl == resCol || radAcl == resAcl));

    // If a resonance has been found, but no colours match, change
    // the colour of the resonance
    if (!matchesRes && iColResNow > -1) {
      if ( radType == -1 && outState[radPos].colType() == 1)
        outState[iColResNow].col(radCol);
      else if ( radType ==-1 && outState[radPos].colType() ==-1)
        outState[iColResNow].acol(radAcl);
      else if ( radType == 1 && outState[radPos].colType() == 1)
        outState[iColResNow].col(radCol);
      else if ( radType == 1 && outState[radPos].colType() ==-1)
        outState[iColResNow].acol(radAcl);
    }

    // If a resonance has been found, but no colours match, and the position
    // of the resonance in the event record has been changed, update the
    // radiator mother
    if (!matchesRes && iColResNow > 0 && iColRes != iColResNow)
      outState[radPos].mother1(iColResNow);

  }

  // Force outgoing particles to be part of hard process.
  for ( int i=0; i < int(outState.size()); ++i) {
    if (outState[i].isFinal()) outState[i].status(23);
  }

  // Force incoming to be part of the hard process.
  outState[3].status(-21);
  outState[4].status(-21);

  // Now check event.
  for ( int i = 0; i < outState.size(); ++i) {
    if ( outState[i].status() == 23
      && particleDataPtr->isResonance(outState[i].id())) outState[i].status(22);
  }

  // Check if the state is valid. If not, return empty state.
  if (!validEvent( outState, true )) outState.clear();

  // Done
  return make_pair(outState, make_pair(radPos,recPos));

}

bool DireTimes::cluster_FF( const Event& state, int iRad, int iEmt1, int iEmt2,
  int iRec, int idRadBef, string name, Particle& radBef, Particle& recBef ) {

  int nEmissions = (iEmt2<0) ? 1 : 2;

  // Calculate CS variables.
  double tDire = (nEmissions==1)
    ? kinRels->tEvolDire_FF(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->tEvolDire_FF(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(), state[iRec].p());
  double z     = (nEmissions==1)
    ? kinRels->z_FF(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->z_FF(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(), state[iRec].p());
  double tEvol = (kinRels->FSRevolutionMode==1 && !state[iRec].isFinal()) 
    ? kinRels->tEvolCSTimes(state[iRad], state[iEmt1], state[iRec]) : tDire;

  int evType     = splits[name]->typeEvolutionMeasure();

  if (name==testname && testps=="FF") direInfoPtr->message(1) << __LINE__
  << " " << name << " " << state[iRec].id() << " tevol=" << tEvol
  << " z=" << z << endl;

  bool canUseSplitInfo = splits[name]->canUseForBranching();
  if (canUseSplitInfo) {
    double mRes = particleDataPtr->m0(idRadBef);
    double m2Res = pow2(mRes);
    if (evType==2)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc() - m2Res;
    else if (evType== 1)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc(); 
    else if (evType==-1)
      tEvol = pow2(max(0.,2.*mRes - (state[iRad].p() + state[iEmt1].p()).mCalc()));
    // Resonance decay rate zero too far from threshold.
    if (abs(evType)==1 && tEvol > 4.*m2Res) return false;
    // Resonance decay rate zero below threshold.
    if (abs(evType)==1 && tEvol < m2Res) return false;
    // Shower decay rate zero too close to resonance.
    if (evType== 2 && tEvol + m2Res < 4.*m2Res) return false;
  }

  bool isFlipped=false;
  if ( (evType==2 && state[iRec].isFinal())
    || (abs(evType)==1 && state[iRec].isFinal())) {
    double ycs = (state[iRad].p()+state[iEmt1].p()).m2Calc()
               / ( (state[iRad].p()+state[iEmt1].p()+state[iRec].p()).m2Calc()
                 - pow2(particleDataPtr->m0(idRadBef)) );
    double zcs = state[iRad].p()*state[iRec].p()
               / ( state[iRad].p()*state[iRec].p()
                 + state[iEmt1].p()*state[iRec].p() );
    z = 1.- (1 - zcs)*(1-ycs);
    isFlipped=true;
  }

  if (name==testname && testps=="FF") direInfoPtr->message(1) << __LINE__
  << " " << name << " " << state[iRec].id() << " tevol=" << tEvol
  << " z=" << z << endl;

  // Do not check phase space limits if pT2 is vanishing.
  bool checkLimits = true;
  if (abs(tEvol) < 1e-10) checkLimits = false;

  // Get particle masses.
  double m2Bef = ( abs(idRadBef) < 6 || idRadBef == 21 || idRadBef == 22)
               ? getMass(idRadBef,2)
               : (idRadBef == state[iRad].id())
                  ? getMass(idRadBef,3,state[iRad].mCalc())
                  : getMass(idRadBef,2);
  double m2BefSave = m2Bef;
  if (abs(evType)==1) m2Bef = 0.;

  Vec4 pRad(state[iRad].p());
  Vec4 pRec(state[iRec].p());
  Vec4 pEmt(state[iEmt1].p());
  if (nEmissions==2) pEmt += state[iEmt2].p();
  double m2r   = pRad.m2Calc();
  double m2e   = pEmt.m2Calc();
  double m2s   = pRec.m2Calc();
  double m2D = (nEmissions==1)
    ? kinRels->m2dip_FF(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->m2dip_FF(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(),
        state[iRec].p());
  double Q2 = m2D;

  // Get dipole 4-momentum.
  Vec4 q(pRad + pEmt + pRec);
  double q2 = q.m2Calc();

  int type     = 1;
  // Upate type if this is a massive splitting.
  if ( m2Bef > TINYMASS || m2r > TINYMASS || m2s > TINYMASS
    || m2e > TINYMASS ) type = 2;

  // Set correct variables for 1->3 splitting.
  vector <double> aux;
  if ( nEmissions == 2 ) {
    double sai = 2.*state[iRad].p()*state[iEmt1].p();
    double xa = kinRels->xa_FF(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(), state[iRec].p());
    double m2aij = m2Bef;
    double m2a(state[iRad].p().m2Calc()), m2i(state[iEmt1].p().m2Calc()),
      m2j(state[iEmt2].p().m2Calc()), m2k(state[iRec].p().m2Calc());
    type       =  2;
    aux.push_back(m2D);
    aux.push_back(q2);
    aux.push_back(tDire);
    aux.push_back(sai);
    aux.push_back(z);
    aux.push_back(xa);
    aux.push_back(m2aij);
    aux.push_back(m2a);
    aux.push_back(m2i);
    aux.push_back(m2j);
    aux.push_back(m2k);
  }

  //if (canUseSplitInfo) {
    splits[name]->splitInfo.save();
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.storeInfo(name, type, 0, 0, 0, 
      iRad, iRec, state,
      state[iEmt1].id(), state[iRad].id(),
      nEmissions, m2D, tEvol, tEvol, z, 0.0, m2BefSave, m2s,
      (nEmissions == 1 ? m2r : aux[7]),
      (nEmissions == 1 ? m2e : aux[8]),
      (nEmissions == 1 ? 0.0 : aux[3]),
      (nEmissions == 1 ? 0.0 : aux[5]),
      (nEmissions == 1 ? 0.0 : 0.0),
      (nEmissions == 1 ? 0.0 : aux[9]), 0., 0.);
    splits[name]->splitInfo.setSiblings(DireSingleColChain());
    if (canUseSplitInfo && !isFlipped) {
      z     = splits[name]->getZDire(state[iRad].isFinal(),
        state[iRec].isFinal(), z, tEvol, Q2);
    }
    if (canUseSplitInfo) tDire = splits[name]->getTDire(state[iRad].isFinal(),
      state[iRec].isFinal(), z, tEvol, Q2);
  //  splits[name]->splitInfo.clear();
  //  splits[name]->splitInfo.restore();
  //}

  double zcheck=z;

  if (name==testname && testps=="FF") direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << name << " " << state[iRec].id()
  << " tevol=" << tEvol << " z=" << zcheck << endl;

  // Check phase space constraints.
  if (checkLimits && !inAllowedPhasespace(1, zcheck, tDire, Q2, q2, 0.0, type, m2Bef,
    m2r, m2s, m2e, aux, splits[name]) ) {
    direInfoPtr->message(1) << " Return false at line " << __LINE__ << endl; 
    // Reset again.
    splits[name]->splitInfo.checkCuts = true;
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.restore();
    return false;
  }

  // Calculate derived variables.
  double sij  = (pRad + pEmt).m2Calc();
  
  // Now construct the new recoiler momentum in the lab frame.
  Vec4 pRecBef( (pRec - (q*pRec)/q2 * q)
            * sqrt(lABC(q2,m2BefSave,m2s)/lABC(q2,sij,m2s))
            + q * (q2+m2s-m2BefSave)/(2.*q2) );

  // Get momentum of radiator my momentum conservation.
  Vec4 pRadBef(q-pRecBef);

  radBef.p(pRadBef);
  recBef.p(pRecBef);
  radBef.m(sqrtpos(m2Bef));
  recBef.m(sqrtpos(m2s));

  // Reset again.
  splits[name]->splitInfo.checkCuts = true;
  splits[name]->splitInfo.clear();
  splits[name]->splitInfo.restore();

  // Done
  return true;
}

bool DireTimes::cluster_FI( const Event& state, int iRad, int iEmt1, int iEmt2,
  int iRec, int idRadBef, string name, Particle& radBef, Particle& recBef ) {

  int nEmissions = (iEmt2<0) ? 1 : 2;
  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iRec));
  if (nEmissions==2) iExc.push_back(iEmt2);

  // Calculate CS variables.
  double tDire = (nEmissions==1)
    ? kinRels->tEvolDire_FI(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->tEvolDire_FI(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(), state[iRec].p());
  double z     = (nEmissions==1)
    ? kinRels->z_FI(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->z_FI(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(), state[iRec].p());
  double tEvol = (kinRels->FSRevolutionMode==1 && !state[iRec].isFinal()) 
    ? kinRels->tEvolCSTimes(state[iRad], state[iEmt1], state[iRec]) : tDire;

  int evType     = splits[name]->typeEvolutionMeasure();
  bool canUseSplitInfo = splits[name]->canUseForBranching();
  if (canUseSplitInfo) {
    double mRes = particleDataPtr->m0(idRadBef);
    double m2Res = pow2(mRes);
    if (evType==2)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc() - m2Res;
    else if (evType==1)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc(); 
    else if (evType==-1)
      tEvol = pow2(max(0.,2.*mRes - (state[iRad].p() + state[iEmt1].p()).mCalc()));
    // Resonance decay rate zero too far from threshold.
    if (abs(evType)==1 && tEvol > 4.*m2Res) return false;
    // Resonance decay rate zero below threshold.
    if (abs(evType)==1 && tEvol < m2Res) return false;
    // Shower decay rate zero too close to resonance.
    if (evType== 2 && tEvol + m2Res < 4.*m2Res) return false;
  }

  // Do not check phase space limits if pT2 is vanishing.
  bool checkLimits = true;
  if (abs(tEvol) < 1e-10) checkLimits = false;

  // Get particle masses.
  double m2Bef = ( abs(idRadBef) < 6 || idRadBef == 21 || idRadBef == 22)
               ? getMass(idRadBef,2)
               : (idRadBef == state[iRad].id())
                  ? getMass(idRadBef,3,state[iRad].mCalc())
                  : getMass(idRadBef,2);
  double m2BefSave = m2Bef;
  if (abs(evType)==1) m2Bef = 0.;

  Vec4 pRad(state[iRad].p());
  Vec4 pRec(state[iRec].p());
  Vec4 pEmt(state[iEmt1].p());
  if (nEmissions==2) pEmt += state[iEmt2].p();

  double m2r   = pRad.m2Calc();
  double m2e   = pEmt.m2Calc();
  double m2s   = pRec.m2Calc();
  double m2D = (nEmissions==1)
    ? kinRels->m2dip_FI(state[iRad].p(), state[iEmt1].p(), state[iRec].p())
    : kinRels->m2dip_FI(state[iRad].p(), state[iEmt1].p(), state[iEmt2].p(),
        state[iRec].p());
  double Q2 = m2D;

  // Get dipole 4-momentum.
  Vec4 q(-pRad - pEmt + pRec);
  double q2 = q.m2Calc();

  vector<int> iOther;
  for (int i=3; i < state.size(); ++i) {
    if (find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    iOther.push_back(i);
  }

  if ( (iOther.size() == 1 || abs(q.m2Calc()) < TINYMASS) && m2BefSave > 0.) { 

    // Get momentum of radiator my momentum conservation.
    Vec4 pRadBef(pRad + pEmt);

    // Ensure that radiator is on mass-shell
    double errMass = abs(pRadBef.mCalc() - sqrt(m2BefSave)) / max( 1.0, pRadBef.e());
    if ( errMass > mTolErr*1e-2 ) {
      double deltam2 = pRadBef.m2Calc() - m2BefSave;
      pRadBef.e(sqrtpos(pow2(pRadBef.e()) - deltam2));
    }
    Vec4 pRecBef(pRec);
    // Ensure that recoiler is on mass-shell
    errMass = abs(pRecBef.mCalc() - sqrt(m2s)) / max( 1.0, pRecBef.e());
    if ( errMass > mTolErr*1e-2 ) {
      double deltam2 = pRecBef.m2Calc() - m2s;
      pRecBef.e(sqrtpos(pow2(pRecBef.e()) - deltam2));
    }
    radBef.p(pRadBef);
    recBef.p(pRecBef);
    radBef.m(sqrtpos(m2BefSave));
    recBef.m(sqrtpos(m2s));
    // Done
    return true;
  }

  // Check phase space constraints.
  double xNew = 2. * state[iRec].e() / state[0].m();

  // Calculate CS variables.
  double kappa2 =  tDire/Q2;
  double xCS = 1 - kappa2/(1.-z);

  if (abs(evType)==1) {
    double virt = (evType > 0
                ? tEvol : pow2(2.*sqrt(m2BefSave)-sqrt(tEvol)) );
    xCS = Q2/(Q2+virt);
  }

  if (evType==2) {
    double virt = tEvol + m2BefSave;
    xCS = Q2/(Q2+virt);
  }

  double xCDST = xCS*( 1. + (m2BefSave-m2r-m2e)/Q2 );
  double xOld  = xNew * xCDST;

  if (name==testname && testps=="FI") direInfoPtr->message(1) << __LINE__
  << " " << __func__ << " " << name << state[iRec].id() << " tevol=" << tEvol
  << " z=" << z << " xcs=" << xCS << " xbj=" << xOld << endl;

  int type     = -1;
  // Upate type if this is a massive splitting.
  if ( m2Bef > TINYMASS || m2r > TINYMASS || m2s > TINYMASS
    || m2e > TINYMASS ) type = -2;

  // Set correct variables for 1->3 splitting.
  vector <double> aux;
  if ( nEmissions == 2 ) {
    double sai = 2.*state[iRad].p()*state[iEmt1].p();
    double xa = kinRels->xa_FI(state[iRad].p(),  state[iEmt1].p(),
                      state[iEmt2].p(), state[iRec].p());
    double m2aij = m2Bef;

    double m2a(state[iRad].p().m2Calc()), m2i(state[iEmt1].p().m2Calc()),
      m2j(state[iEmt2].p().m2Calc()), m2k(state[iRec].p().m2Calc());

    double m2ai  = sai + m2a + m2i;
    xCS          = (q2 - m2ai - m2a - m2i)
                 / (q2 - m2ai - m2a - m2i - tDire * xa/z);
    xCDST = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
    xOld = xNew*xCDST;
    type       =  -2;
    aux.push_back(m2D);
    aux.push_back(q2);
    aux.push_back(tDire);
    aux.push_back(sai);
    aux.push_back(z);
    aux.push_back(xa);
    aux.push_back(m2aij);
    aux.push_back(m2a);
    aux.push_back(m2i);
    aux.push_back(m2j);
    aux.push_back(m2k);
  }

//  if (canUseSplitInfo) {
    splits[name]->splitInfo.save();
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.storeInfo(name, type, 0, 0, 0, 
      iRad, iRec, state,
      state[iEmt1].id(), state[iRad].id(),
      nEmissions, m2D, tEvol, tEvol, z, 0.0, m2BefSave, m2s,
      (nEmissions == 1 ? m2r : aux[7]),
      (nEmissions == 1 ? m2e : aux[8]),
      (nEmissions == 1 ? 0.0 : aux[3]),
      (nEmissions == 1 ? 0.0 : aux[5]),
      (nEmissions == 1 ? 0.0 : 0.0),
      (nEmissions == 1 ? 0.0 : aux[9]), xOld, xNew);
    splits[name]->splitInfo.setSiblings(DireSingleColChain());
    if (canUseSplitInfo) z     = splits[name]->getZDire(state[iRad].isFinal(),
      state[iRec].isFinal(), z, tEvol, Q2);
    if (canUseSplitInfo) tDire = splits[name]->getTDire(state[iRad].isFinal(),
      state[iRec].isFinal(), z, tEvol, Q2);
//    splits[name]->splitInfo.clear();
//    splits[name]->splitInfo.restore();
//  }

  bool   hasPDFrec = hasPDF(state[iRec].id());
  double xMin = (hasPDFrec) ? xOld : 0.;

  double zcheck=z;

  direInfoPtr->message(1) <<scientific << setprecision(6);
  direInfoPtr->message(1) << __LINE__ << " " << __func__ << " " << name
  << state[iRec].id() << " tevol=" << tEvol << " z=" << zcheck
  << " xcs=" << xCS << " xbj=" << xOld
  << " " << splits[name]->splitInfo.kinematics()->m2Dip << " " << m2D << endl;
  direInfoPtr->message(1) << __LINE__ << " " << __func__ << " " << name
  << state[iRec].id() << " " << checkLimits << " " << zcheck << " " << tDire
  << " " << Q2 << " " << q2 << " " << xMin << " " << m2Bef << " " << m2r
  << " " << m2s << " " << m2e << endl;

  if (checkLimits && !inAllowedPhasespace( 1, zcheck, tDire, Q2, q2, xMin, type,
    m2Bef, m2r, m2s, m2e, aux, splits[name]) ) {
    direInfoPtr->message(1) << " Return false at line " << __LINE__ << endl; 
    // Reset again.
    splits[name]->splitInfo.checkCuts = true;
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.restore();
    return false;
  }

  Vec4 qpar(q.px()+pRad.px()+pEmt.px(),
            q.py()+pRad.py()+pEmt.py(),
            q.pz(), q.e());
  double qpar2 = qpar.m2Calc();
  double pT2ijt = pow2(pRad.px()+pEmt.px()) + pow2(pRad.py()+pEmt.py());

  // Calculate derived variables.
  double sij  = (pRad + pEmt).m2Calc();

  // Now construct the new recoiler momentum in the lab frame.
  Vec4 pRecBef( (pRec - (q*pRec)/qpar2 * qpar)
            * sqrt( (lABC(q2,m2BefSave,m2s) - 4.*m2s*pT2ijt)
            //* sqrt( (lABC(q2,0.0,m2s)   - 4.*m2s*pT2ijt)
                   /(lABC(q2,sij,m2s)   - 4.*m2s*pT2ijt))
            + qpar * (q2+m2s-m2BefSave)/(2.*qpar2) );
            //+ qpar * (q2+m2s-0.0)/(2.*qpar2) );

  // Get momentum of radiator my momentum conservation.
  Vec4 pRadBef(-q+pRecBef);

  // Ensure that radiator is on mass-shell
  double errMass = abs(pRadBef.mCalc() - sqrt(m2BefSave)) / max( 1.0, pRadBef.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRadBef.m2Calc() - m2BefSave;
    pRadBef.e(sqrtpos(pow2(pRadBef.e()) - deltam2));
  }
  // Ensure that recoiler is on mass-shell
  errMass = abs(pRecBef.mCalc() - sqrt(m2s)) / max( 1.0, pRecBef.e());
  if ( errMass > mTolErr*1e-2 ) {
    double deltam2 = pRecBef.m2Calc() - m2s;
    pRecBef.e(sqrtpos(pow2(pRecBef.e()) - deltam2));
  }

  radBef.p(pRadBef);
  recBef.p(pRecBef);
  radBef.m(sqrtpos(m2BefSave));
  recBef.m(sqrtpos(m2s));

  // Reset again.
  splits[name]->splitInfo.checkCuts = true;
  splits[name]->splitInfo.clear();
  splits[name]->splitInfo.restore();

  // Done
  return true;
}

//--------------------------------------------------------------------------

// Function to in the input event find a particle with quantum
// numbers matching those of the input particle
// IN  Particle : Particle to be searched for
//     Event    : Event to be searched in
// OUT int      : > 0 : Position of matching particle in event
//                < 0 : No match in event

int DireTimes::FindParticle( const Particle& particle, const Event& event,
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

  if ( checkStatus && index >-1
    && event[index].status() != particle.status() )
    index = -1;

  return index;
}

//--------------------------------------------------------------------------

// From Pythia version 8.218 onwards.
// Return the evolution variable and splitting information. More comments
// in the header.

map<string, double> DireTimes::getStateVariables (const Event& state,
  int rad, int emt, int rec, string name) {
  map<string,double> ret;

  // Kinematical variables.
  if (rad > 0 && emt > 0 && rec > 0) {

    double tEvol = kinRels->tEvolTimes ( state[rad], state[emt], state[rec]);
    double z     = kinRels->zTimes ( state[rad], state[emt], state[rec]);
    ret.insert(make_pair("t",tEvol));
    ret.insert(make_pair("tRS",tEvol));

    // Get scales for running coupling and PDF.
    double m2dip = kinRels->m2dipTimes ( state[rad], state[emt], state[rec]);
    ret.insert(make_pair("m2dip", m2dip));
    double mu2 = tEvol;

    if (!name.empty()) mu2 = (*splittingsPtr)[name]->couplingScale2(z, tEvol,
      m2dip,
      make_pair(state[rad].id(), state[rad].isFinal()),
      make_pair(state[rec].id(), state[rec].isFinal()));
    if (mu2<0.) mu2 = tEvol; 
    ret.insert(make_pair("scaleAS",mu2));
    ret.insert(make_pair("scaleEM",mu2));
    ret.insert(make_pair("scalePDF",mu2));
    ret.insert(make_pair("z",z));

    // Book-keeping for particle before emission.
    int radBefID
       = (!name.empty())
       ? (*splittingsPtr)[name]->radBefID(state[rad].id(), state[emt].id())
       : 0;
    pair<int,int> radBefCols
       = (!name.empty())
       ? (*splittingsPtr)[name]->radBefCols(state[rad].col(),
             state[rad].acol(), state[emt].col(), state[emt].acol())
       : make_pair(0,0);
    ret.insert(make_pair("radBefID", radBefID));
    ret.insert(make_pair("radBefCol", radBefCols.first));
    ret.insert(make_pair("radBefAcol", radBefCols.second));

    int couplingType 
       = (!name.empty())
       ? (*splittingsPtr)[name]->couplingType(state[rad].id(), state[emt].id())
       : -1;
    ret.insert(make_pair("scaleForCoupling "+std::to_string(couplingType),tEvol));
    ret.insert(make_pair("couplingType",couplingType));
    double couplingValue
       = (!name.empty())
       ? (*splittingsPtr)[name]->coupling(z, tEvol, m2dip, -1.,
         make_pair(state[rad].id(), state[rad].isFinal()),
         make_pair(state[rec].id(), state[rec].isFinal()))
       : -1.0;
    ret.insert(make_pair("couplingValue",couplingValue));
    ret.insert(make_pair("couplingValue",couplingValue));

  // Variables defining the PS starting scales.
  } else {

    // In this case, insert only dummy information except for PDF scale.
    ret.insert(make_pair("t",0.));
    ret.insert(make_pair("tRS",0.));
    ret.insert(make_pair("scaleAS",0.));
    ret.insert(make_pair("scaleEM",0.));
    ret.insert(make_pair("z",0.));
    ret.insert(make_pair("radBefID", 0));
    ret.insert(make_pair("radBefCol", 0));
    ret.insert(make_pair("radBefAcol", 0));
    //ret.insert(make_pair("scaleForCoupling "+STRING(-1),0.));
    ret.insert(make_pair("scaleForCoupling "+std::to_string(-1),0.));
    ret.insert(make_pair("couplingType",-1));
    ret.insert(make_pair("couplingValue",-1.));

    // Find the shower starting scale.
    vector<DireTimesEnd> dipEnds;

    // Loop through final state of system to find possible dipole ends.
    for (int iRad = 0; iRad < state.size(); ++iRad) {

      if ( !state[iRad].isFinal() ) continue;

      // Find dipole end formed by colour index.
      int colTag = state[iRad].col();
      if (colTag > 0) getQCDdip( iRad,  colTag,  1, state, dipEnds);
      // Find dipole end formed by anticolour index.
      int acolTag = state[iRad].acol();
      if (acolTag > 0) getQCDdip( iRad, acolTag, -1, state, dipEnds);
      // Now find non-QCD dipoles and/or update the existing dipoles.
      getGenDip( -1, 0, iRad, state, false, dipEnds);

    }

    // Get x for both beams.
    int in1(3), in2(4);
    double x1 = state[3].pPos() / state[0].m();
    double x2 = state[4].pNeg() / state[0].m();

    // Store invariant masses of all dipole ends.
    stringstream oss;
    for (int iDip = 0; iDip < int(dipEnds.size()); ++iDip) {
      double m2 = abs(2.*state[dipEnds[iDip].iRadiator].p()
                        *state[dipEnds[iDip].iRecoiler].p());
      if ( dipEnds[iDip].iRecoiler == in1) m2 /= x1;
      if ( dipEnds[iDip].iRecoiler == in2) m2 /= x2;
      oss.str("");
      oss << "scalePDF-" << dipEnds[iDip].iRadiator
           << "-"        << dipEnds[iDip].iRecoiler;
      ret.insert(make_pair(oss.str(),m2));
    }

  }

  return ret; 
}

//--------------------------------------------------------------------------

// Compute splitting probability.

// From Pythia version 8.215 onwards.
double DireTimes::getSplittingProb( const Event& state, int iRad,
  int iEmt1, int iEmt2, int iRec, string name, bool checkPTMINcut) {

  direInfoPtr->message(1) << __func__ << " " << __LINE__ << " " << name
  << " checkcut=" << checkPTMINcut << endl;

  // Get kernel order.
  int order = atoi( (char*)name.substr( name.find("-",0)+1, name.size() ).c_str() );
  name=name.substr( 0, name.size()-2);

  // Do nothing if kernel says so, e.g. to avoid infinite loops
  // if the kernel uses the History class.
  if ( splits[name]->splitInfo.unitKernel) return 1.;

  int evType     = splits[name]->typeEvolutionMeasure();
  int nEmissions = (iEmt2<0) ? 1 : 2;
  double z       = (nEmissions==1)
    ? kinRels->zTimes(state[iRad], state[iEmt1], state[iRec])
    : kinRels->zTimes(state[iRad], state[iEmt1], state[iEmt2], state[iRec]);
  double tDire   = (nEmissions==1) 
    ? kinRels->tEvolDireTimes(state[iRad], state[iEmt1], state[iRec])
    : kinRels->tEvolDireTimes(state[iRad], state[iEmt1], state[iEmt2], state[iRec]);
  double m2D     = (nEmissions==1) 
    ? kinRels->m2dipTimes(state[iRad], state[iEmt1], state[iRec])
    : kinRels->m2dipTimes(state[iRad], state[iEmt1], state[iEmt2], state[iRec]);
  double tEvol   = (kinRels->FSRevolutionMode==1 && !state[iRec].isFinal()) 
    ? kinRels->tEvolCSTimes(state[iRad], state[iEmt1], state[iRec]) : tDire;
  int idRadBef   = splits[name]->radBefID(state[iRad].id(), state[iEmt1].id());

  bool isFlipped = false;
  if ( (evType==2 && state[iRec].isFinal())
    || (abs(evType)==1 && state[iRec].isFinal())) {
    double ycs = (state[iRad].p()+state[iEmt1].p()).m2Calc()
               / ( (state[iRad].p()+state[iEmt1].p()+state[iRec].p()).m2Calc()
                 - pow2(particleDataPtr->m0(idRadBef)) );
    double zcs = state[iRad].p()*state[iRec].p()
               / ( state[iRad].p()*state[iRec].p()
                 + state[iEmt1].p()*state[iRec].p() );
    z = 1.- (1 - zcs)*(1-ycs);
    isFlipped = true;
  }

  bool canUseSplitInfo = splits[name]->canUseForBranching();
  if (canUseSplitInfo) {
    double mRes = particleDataPtr->m0(idRadBef);
    double m2Res = pow2(mRes);
    if (evType==2)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc()
            - m2Res;
    else if (evType== 1)
      tEvol = (state[iRad].p() + state[iEmt1].p()).m2Calc(); 
    else if (evType==-1)
      tEvol = pow2(max(0.,2.*mRes - (state[iRad].p() + state[iEmt1].p()).mCalc()));
    // Resonance decay rate zero too far from threshold.
    if (abs(evType)==1 && tEvol > 4.*m2Res)     return 0.;
    // Resonance decay rate zero below threshold.
    if (abs(evType)==1 && tEvol < m2Res)        return 0.;
    // Shower decay rate zero too close to resonance.
    if (evType== 2 && tEvol + m2Res < 4.*m2Res) return 0.;
  }

  string pstype=(state[iRec].isFinal() ? "FF" : "FI" );

  direInfoPtr->message(1) << __func__ << " " << __LINE__ << " " << name
  << " tevol=" << tEvol << " virt=" << 2*state[iRad].p()*state[iEmt1].p()
  << endl;

  if (name==testname && testps==pstype) direInfoPtr->message(1) << __LINE__
  << " " << name << " " << state[iRec].id() << " " << __func__
  << (state[iRec].isFinal() ? " FF " : " FI " ) << " tevol=" << tEvol
  << " z=" << z << endl;

  // Disallow below cut-off.
  if (checkPTMINcut) {
    bool allowed = true;
    if (!splits[name]->is_qed && pT2cut(state[iEmt1].id()) > tEvol)
      allowed = false;
    if (splits[name]->is_qed) {
      if ( state[iEmt1].id() == 22
        && pT2cut(state[iEmt1].id()) > tEvol)
       allowed = false;
      if ( idRadBef == 22
        && pT2cut(idRadBef) > tEvol)
        allowed = false;
    }
    if (!allowed) {
      direInfoPtr->message(1) << __func__ << " " << __LINE__
      << " " << name << " return" << endl;
      return 0.;
    }
  }

  if (checkPTMINcut && !splits[name]->aboveCutoff( tEvol, state[iRad],
    state[iRec], 0, partonSystemsPtr)) {
    direInfoPtr->message(1) << __func__ << " " << __LINE__ << " " << name
    << " return" << endl;
    return 0.;
  }

  // Return unity as default probability if pT2 is vanishing.
  if (!checkPTMINcut && abs(tEvol) < 1e-10) return 1.;

  double m2Bef = ( abs(idRadBef) < 6 || idRadBef == 21 || idRadBef == 22)
               ? getMass(idRadBef,2)
               : (idRadBef == state[iRad].id())
                  ? getMass(idRadBef,3,state[iRad].mCalc())
                  : getMass(idRadBef,2);
  double m2BefSave = m2Bef;
  //if (evType!=0) m2Bef = 0.;
  if (abs(evType)==1) m2Bef = 0.;

  double m2r   = state[iRad].p().m2Calc();
  double m2e   = state[iEmt1].p().m2Calc();
  double m2s   = state[iRec].p().m2Calc();
  int type     = state[iRec].isFinal() ? 1 : -1;

  // Upate type if this is a massive splitting.
  if (type == 1 && (m2Bef > TINYMASS || m2r > TINYMASS || m2s > TINYMASS
    || m2e > TINYMASS) ) type = 2;
  if (type ==-1 && (m2Bef > TINYMASS || m2r > TINYMASS || m2s > TINYMASS
    || m2e > TINYMASS) ) type =-2;

  // Recalculate the kinematicaly available dipole mass.
  int massSign  = (type > 0) ? 1 : -1;
  Vec4 q(state[iRec].p()+massSign*state[iRad].p()+massSign*state[iEmt1].p());
  if (nEmissions==2) q += massSign*state[iEmt2].p();
  double q2     = q.m2Calc();
  double Q2     = m2D;

  double kappa2 =  tDire/Q2;
  double xCS    = 1 - kappa2/(1.-z);

  if (type < 0 && abs(evType)==1) {
    double virt = (evType > 0
                ? tEvol : pow2(2.*sqrt(m2BefSave)-sqrt(tEvol)) );
    xCS = Q2/(Q2+virt);
  }

  if (type < 0 && evType==2) {
    double virt = tEvol + m2BefSave;
    xCS = Q2/(Q2+virt);
  }

  double xCDST = xCS*( 1. + (m2BefSave-m2r-m2e)/Q2 );
  double xNew   = (type > 0) ? 0.0 : 2.*state[iRec].e() / state[0].m(); 
  double xOld   = (type > 0) ? 0.0 : xCDST * xNew;

  // Check phase space constraints.
  bool   hasPDFrec = type < 0 && hasPDF(state[iRec].id());
  double xMin = (hasPDFrec) ? xOld : 0.;

  if (abs(q2) < 1e-5) {
    q2 = Q2 = (state[iRad].p() + state[iEmt1].p()).m2Calc();
    xMin = 0.;
    type = 0;
  }

  if (name.compare("Dire_fsr_qcd_1->21&1") == 0) swap(iRad,iEmt1);
  if (name.compare("Dire_fsr_qed_1->22&1") == 0) swap(iRad,iEmt1);
  if (name.compare("Dire_fsr_qed_11->22&11") == 0) swap(iRad,iEmt1);

  // Set correct variables for 1->3 splitting.
  vector <double> aux;
  if ( nEmissions == 2 ) {
    double sai = 2.*state[iRad].p()*state[iEmt1].p();
    double xa = kinRels->xaTimes(state[iRad], state[iEmt1], state[iEmt2], state[iRec]);
    double m2aij = m2Bef;
    double m2a(state[iRad].p().m2Calc()), m2i(state[iEmt1].p().m2Calc()),
      m2j(state[iEmt2].p().m2Calc()), m2k(state[iRec].p().m2Calc());
    double m2ai  = sai + m2a + m2i;
    xCS          = (q2 - m2ai - m2a - m2i)
                 / (q2 - m2ai - m2a - m2i - tDire * xa/z);
    xCDST        = xCS * ( 1. - (m2aij-m2ai-m2j)/ (q2-m2ai-m2j-m2k) );
    xOld         = state[iRec].isFinal() ? 0. : xNew*xCDST;
    type         = state[iRec].isFinal() ? 2 : -2;
    aux.push_back(m2D);
    aux.push_back(q2);
    aux.push_back(tDire);
    aux.push_back(sai);
    aux.push_back(z);
    aux.push_back(xa);
    aux.push_back(m2aij);
    aux.push_back(m2a);
    aux.push_back(m2i);
    aux.push_back(m2j);
    aux.push_back(m2k);
  }

  //if (canUseSplitInfo) {
    splits[name]->splitInfo.save();
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.storeInfo(name, type, 0, 0, 0, 
      iRad, iRec, state,
      state[iEmt1].id(), state[iRad].id(),
      nEmissions, m2D, tEvol, tEvol, z, 0.0, m2BefSave, m2s,
      (nEmissions == 1 ? m2r : aux[7]),
      (nEmissions == 1 ? m2e : aux[8]),
      (nEmissions == 1 ? 0.0 : aux[3]),
      (nEmissions == 1 ? 0.0 : aux[5]),
      (nEmissions == 1 ? 0.0 : 0.0),
      (nEmissions == 1 ? 0.0 : aux[9]), xOld, xNew);
    splits[name]->splitInfo.setSiblings(DireSingleColChain());
 
    if (canUseSplitInfo && !isFlipped) { 
      z     = splits[name]->getZDire(state[iRad].isFinal(),
        state[iRec].isFinal(), z, tEvol, Q2);
    }

    if (canUseSplitInfo) tDire = splits[name]->getTDire(state[iRad].isFinal(),
      state[iRec].isFinal(), z, tEvol, Q2);

  //  splits[name]->splitInfo.clear();
  //  splits[name]->splitInfo.restore();
  //
  //}

  double zcheck=z;

  if (name==testname && testps==pstype) direInfoPtr->message(1) << __LINE__
  << " " << name << " " << __func__ << (state[iRec].isFinal() ? " FF ":" FI ")
  << name << " " << state[iRec].id() << " tevol=" << tEvol << " z=" << zcheck
  << " xCS=" << xCS << " " << xCDST << " xbj=" << xMin << " " << xCS*xNew << endl;

  if ( !inAllowedPhasespace( 1, zcheck, tDire, Q2, q2, xMin, type, m2Bef, m2r, m2s,
        m2e, aux, splits[name]) ) { 
    // Reset again.
    splits[name]->splitInfo.checkCuts = true;
    splits[name]->splitInfo.clear();
    splits[name]->splitInfo.restore();
    return 0.0;
  }

  // Calculate splitting probability.
  double p = 0.;

  double zbranch=z;
  // Get phi angle.
  pair<Vec4, Vec4> pTdirection = getTwoPerpendicular(state[iRec].p(),
    state[iRad].p()+state[iEmt1].p());
  double px   = -pTdirection.first*state[iRad].p();
  double py   = -pTdirection.second*state[iRad].p();
  double kT2  = pow2(px)+pow2(py);
  double phi1 = atan2(px/sqrt(kT2), py/sqrt(kT2));
  if (phi1 < 0.) phi1 = 2.*M_PI+phi1;

  double phi2 = (nEmissions!=2) ? -1. : phi1; 
  if (nEmissions==2) {
    // Get primary phi angle in case of two emissions.
    pTdirection = getTwoPerpendicular(state[iRec].p(),
      state[iRad].p()+state[iEmt1].p()+state[iEmt2].p());
    px   = -pTdirection.first*(state[iRad].p()+state[iEmt1].p());
    py   = -pTdirection.second*(state[iRad].p()+state[iEmt1].p());
    kT2  = pow2(px)+pow2(py);
    phi1 = atan2(px/sqrt(kT2), py/sqrt(kT2));
    if (phi1 < 0.) phi1 = 2.*M_PI+phi1;
  }

  pair <Event, pair<int,int> > born(clustered_internal( state, iRad, iEmt1,
    iEmt2, iRec, name ));

  double m2dipBef = abs(2.*born.first[born.second.first].p()
                          *born.first[born.second.second].p());
  splits[name]->splitInfo.storeInfo(name, type, 0, 0, 0, 
    born.second.first, born.second.second, born.first,
    state[iEmt1].id(), state[iRad].id(),
    nEmissions, m2dipBef, tEvol, tEvol, zbranch, phi1, m2BefSave, m2s,
    (nEmissions == 1 ? m2r : aux[7]),
    (nEmissions == 1 ? m2e : aux[8]),
    (nEmissions == 1 ? 0.0 : aux[3]),
    (nEmissions == 1 ? 0.0 : aux[5]),
    (nEmissions == 1 ? 0.0 : phi2),
    (nEmissions == 1 ? 0.0 : aux[9]), xOld, xNew);
  splits[name]->splitInfo.setSiblings(DireSingleColChain());
  if (!checkPTMINcut) splits[name]->splitInfo.checkCuts = false;

  direInfoPtr->message(1) << __LINE__ << " " << name << " " << __func__
  << (state[iRec].isFinal() ? " FF " : " FI " ) << " enter kernel calculation "
  << zbranch << endl;

  // Get splitting probability.
  unordered_map < string, double > kernels;
  // Get complete kernel.
  if (splits[name]->calc(born.first, order) )
    kernels = splits[name]->getKernelVals();
  if ( kernels.find("base") != kernels.end() )
    p += kernels["base"];
  direInfoPtr->message(1) << __func__ << " " << __LINE__ << " " << name
  << " tevol=" << tEvol << " virt=" << 2*state[iRad].p()*state[iEmt1].p()
  << " p=" << p << endl;

  // Multiply with 1/pT^2. Note: No additional Jacobian factors, since for our
  // choice of variables, we always have
  // Jacobian_{mass to CS} * Jacobian_{CS to DIRE} * Propagator = 1/pT2
  double pEvol = 1.;
  if (evType==0 || evType==2) {
    pEvol = 1./tEvol;
  } else if (abs(evType)==1) {
    double width
      = particleDataPtr->particleDataEntryPtr(idRadBef)
                       ->resWidth(idRadBef,sqrt(m2BefSave));
    pEvol = 1./( pow2(tEvol-m2BefSave) + m2BefSave*pow2(width));
  }
  p *= pEvol;

  // Jacobian factors for massive generation
  double massJacobian = canUseSplitInfo
    ? splits[name]->getJacobian(born.first) : 1.;

  // Reset again.
  splits[name]->splitInfo.checkCuts = true;
  splits[name]->splitInfo.clear();
  splits[name]->splitInfo.restore();

  p *= massJacobian;

  direInfoPtr->message(1) << __func__ << " " << __LINE__ << " " << name
  << " tevol=" << tEvol << " j=" << massJacobian << " p=" << p << endl;

  // Note: The additional factor 1/xCS for rescaling the initial flux is NOT
  // included, so that we can apply PDF ratios [x1 f(x1)] / [x0 f(x0) ] later.

  return p;

}

//--------------------------------------------------------------------------

vector<int> DireTimes::getRecoilers( const Event& state, int iRad, int iEmt,
  string name) {
  // List of recoilers.
  return splits[name]->recPositions(state, iRad, iEmt);
}

//--------------------------------------------------------------------------

vector<int> DireTimes::getRecoilers( const Event& state, int iRad, int iEmt1,
  int iEmt2, string name) {
  // List of recoilers.
  return ((iEmt2<0) ? splits[name]->recPositions(state, iRad, iEmt1)
                    : splits[name]->recPositions(state, iRad, iEmt1, iEmt2));
}

//--------------------------------------------------------------------------

// Print the list of dipoles.

void DireTimes::list() const {

  // Header.
  cout << "\n --------  DIRE DireTimes Dipole Listing  ------------------"
       << "--------------------------------------------------------------"
       << "----------\n\n"
       << "   i     rad    rec       pTmax     col    isr"
       << "   sys   sysR            m2          siblings        allowedIds\n"
       << fixed << setprecision(3);

  // Loop over dipole list and print it.
  for (int i = 0; i < int(dipEnd.size()); ++i) {
  cout << scientific << setprecision(4) 
     << setw(4) << i << " | "
     << setw(4) << dipEnd[i].iRadiator << " | "
     << setw(4) << dipEnd[i].iRecoiler << " | "
     << setw(11) << dipEnd[i].pTmax  << " | "
     << setw(3) << dipEnd[i].colType  << " | "
     << setw(4) << dipEnd[i].isrType << " | "
     << setw(4) << dipEnd[i].system << " | "
     << setw(4) << dipEnd[i].systemRec << " | "
     << setw(11) << dipEnd[i].m2Dip << " | ";
    ostringstream os;
    os << dipEnd[i].iSiblings.listPos();
    cout << setw(15) << os.str() << " | ";
    os.str("");
    for (int j = 0; j < int(dipEnd[i].allowedEmissions.size()); ++j)
      os << setw(4) << dipEnd[i].allowedEmissions[j];
    cout << setw(15) << os.str() << endl;
  }

  // Done.
  cout << "\n --------  End DIRE DireTimes Dipole Listing  --------------"
       << "--------------------------------------------------------------"
       << "----------" << endl;

}

//--------------------------------------------------------------------------

// Function to calculate the correct alphaS/2*Pi value, including
// renormalisation scale variations + threshold matching.

double DireTimes::alphasNow( double pT2, double renormMultFacNow, int iSys ) {

  // Get beam for PDF alphaS, if necessary.
  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id()))
         ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id()))
         ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }
  double scale       = pT2*renormMultFacNow;
  scale              = max(scale, pT2colCut);

  // Get alphaS(k*pT^2) and subtractions.
  double asPT2pi      = (usePDFalphas && beam != NULL)
                      ? beam->alphaS(scale)  / (2.*M_PI)
                      : alphaS.alphaS(scale) / (2.*M_PI);

  // Get kernel order.
  int order = kernelOrder-1;
  // Use simple kernels for showering secondary scatterings.
  bool hasInA = (partonSystemsPtr->getInA(iSys) != 0);
  bool hasInB = (partonSystemsPtr->getInB(iSys) != 0);
  if (iSys != 0 && hasInA && hasInB) order = kernelOrderMPI-1;

  // Now find the necessary thresholds so that alphaS can be matched
  // correctly.
  /*double m2cPhys = (usePDFalphas && beam != NULL)
                 ? pow2(max(0.,beam->mQuarkPDF(4)))
                 : alphaS.muThres2(4);*/
  double m2cNow = m2cPhys;
  if ( !( (scale > m2cNow && pT2 < m2cNow)
       || (scale < m2cNow && pT2 > m2cNow) )) m2cNow = -1.;
  double m2bNow = m2bPhys;
  /*double m2bPhys = (usePDFalphas && beam != NULL)
                 ? pow2(max(0.,beam->mQuarkPDF(5)))
                 : alphaS.muThres2(5);*/
  if ( !( (scale > m2bNow && pT2 < m2bNow)
       || (scale < m2bNow && pT2 > m2bNow) ) ) m2bNow = -1.;
  vector<double> scales;
  scales.push_back(scale);
  scales.push_back(pT2);
  if (m2cNow > 0.) scales.push_back(m2cNow);
  if (m2bNow > 0.) scales.push_back(m2bNow);
  sort( scales.begin(), scales.end());
  if (scale > pT2) reverse(scales.begin(), scales.end());

  double asPT2piCorr  = asPT2pi; 
  for ( int i = 1; i< int(scales.size()); ++i) {
    double NF    = getNF( 0.5*(scales[i]+scales[i-1]) );
    double L     = log( scales[i]/scales[i-1] );
    double subt  = 0.;
    if (order > 0) subt += asPT2piCorr * beta0(NF) * L;
    if (order > 2) subt += pow2( asPT2piCorr ) * ( beta1(NF)*L 
                                   - pow2(beta0(NF)*L) );
//    if (order > 4) subt += pow( asPT2piCorr, 3) * ( beta2(NF)*L
//                                   - 2.5 * beta0(NF)*beta1(NF)*L*L
//                                   + pow( beta0(NF)*L, 3) );
    asPT2piCorr *= 1.0 - subt;
  }

  // Done.
  return asPT2piCorr;

}

//-------------------------------------------------------------------------

// Function to calculate the correct alphaem/2*Pi value, including
// renormalisation scale variations + threshold matching.

double DireTimes::alphaemNow( double pT2, double renormMultFacNow, int ) {

  double scale       = pT2*renormMultFacNow;
  scale              = max(scale, pT2colCut);

  // Get alphaEM(k*pT^2) and subtractions.
  double aemPT2pi = alphaEM.alphaEM(scale) / (2.*M_PI);

  // Done.
  return aemPT2pi;

}

//-------------------------------------------------------------------------

// Auxiliary function to get number of flavours.

double DireTimes::getNF(double pT2) {

  double NF = 6.;

  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id()))
         ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id()))
         ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }
  // Get current number of flavours.
  if ( !usePDFalphas || beam == NULL ) {
    if ( pT2 > pow2( max(0., particleDataPtr->m0(5) ) )
      && pT2 < pow2( particleDataPtr->m0(6)) )                 NF = 5.;
    else if ( pT2 > pow2( max( 0., particleDataPtr->m0(4)) ) ) NF = 4.; 
    else if ( pT2 > pow2( max( 0., particleDataPtr->m0(3)) ) ) NF = 3.; 
  } else {
    if ( pT2 > pow2( max(0., beam->mQuarkPDF(5) ) )
      && pT2 < pow2( particleDataPtr->m0(6)) )                 NF = 5.;
    else if ( pT2 > pow2( max( 0., beam->mQuarkPDF(4)) ) )     NF = 4.; 
    else if ( pT2 > pow2( max( 0., beam->mQuarkPDF(3)) ) )     NF = 3.; 
  }
  return NF;
}

//==========================================================================

} // end namespace Pythia8
