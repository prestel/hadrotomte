
#include "Dire/SplittingsQED.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

namespace Pythia8 {

//==========================================================================

double chgprefac = 0.0;

// The SplittingQED class.

//--------------------------------------------------------------------------

void DireSplittingQED::init() {

  // Parameters of alphaEM.
  int alphaEMorder = settingsPtr->mode("SpaceShower:alphaEMorder");
  // Initialize alphaEM.
  alphaEM.init( alphaEMorder, settingsPtr);
  aem0              = settingsPtr->parm("StandardModel:alphaEM0");

  doFSRQEDshowerByQ = settingsPtr->flag("TimeShower:QEDshowerByQ");
  doISRQEDshowerByQ = settingsPtr->flag("SpaceShower:QEDshowerByQ");
  doFSRQEDshowerByL = settingsPtr->flag("TimeShower:QEDshowerByL");
  doISRQEDshowerByL = settingsPtr->flag("SpaceShower:QEDshowerByL");
  doForcePos        = settingsPtr->flag("Dire:QED:doForcePosChgCorrelators");
  double pTminForcePos = settingsPtr->parm("Dire:QED:pTminForcePos");
  pT2minForcePos    = pTminForcePos > 0.0 ? pow2(pTminForcePos) : -1.0;
  double pTminAllowNeg = settingsPtr->parm("Dire:QED:pTminAllowNeg");
  pT2minAllowNeg    = pTminAllowNeg > 0.0 ? pow2(pTminAllowNeg) : -1.0;
  pT2min            = (is_fsr)
                    ? pow2(settingsPtr->parm("TimeShower:pTmin"))
                    : pow2(settingsPtr->parm("SpaceShower:pTmin"));
  pT2minL           = (is_fsr)
                    ? pow2(settingsPtr->parm("DireTimes:QED:pTminChgL"))
                    : pow2(settingsPtr->parm("DireSpace:QED:pTminChgL"));
  pT2minQ           = (is_fsr)
                    ? pow2(settingsPtr->parm("DireTimes:QED:pTminChgQ"))
                    : pow2(settingsPtr->parm("DireSpace:QED:pTminChgQ"));
  pT2minA           = min(pT2minL,pT2minQ);
  //pT2min            = pow2(settingsPtr->parm("TimeShower:pTmin"));
  //pT2minL           = pow2(settingsPtr->parm("TimeShower:pTminChgL"));
  //pT2minQ           = pow2(settingsPtr->parm("TimeShower:pTminChgQ"));
  double pTminMECs  = settingsPtr->parm("Dire:pTminMECs");
  pT2minMECs        = pTminMECs > 0. ? pow2(pTminMECs) : -1.;

  overInt1 = overInt2 = 0.;
}

//--------------------------------------------------------------------------

// Function to calculate the correct alphaem/2*Pi value, including
// renormalisation scale variations + threshold matching.

double DireSplittingQED::aem2Pi( double pT2, int ) {

  double scale       = pT2*renormMultFac;

  // Get alphaEM(k*pT^2) and subtractions.
  double aemPT2pi = alphaEM.alphaEM(scale) / (2.*M_PI);

  // Done.
  return aemPT2pi;

}

//--------------------------------------------------------------------------

double DireSplittingQED::tCutoff( const Particle& radBef,
  const Particle&, PartonSystems*) {
  if (particleDataPtr->isLepton(radBef.id())) return pT2minL;
  if (particleDataPtr->isQuark(radBef.id()))  return pT2minQ;
  if (radBef.id()==22)  return pT2minA;
  return -1.;
}

//--------------------------------------------------------------------------

bool DireSplittingQED::aboveCutoff( double t, const Particle& radBef,
  const Particle&, int, PartonSystems*) {

  if (particleDataPtr->isLepton(radBef.id()) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(radBef.id())  && t < pT2minQ )
    return false;
  if (radBef.id()==22  && t < pT2minA )
    return false;
  //if ((iSys == 0 || partonSystemsPtr->hasInAB(iSys)) && t < pT2min) 
  //  return false;
  return true;
}

//--------------------------------------------------------------------------

bool DireSplittingQED::dipoleAboveCutoff( double t, int radID, int recID,
  double tcut) {
  if (tcut > 0. && t < tcut) return false;
  if (particleDataPtr->isLepton(radID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(radID)  && t < pT2minQ )
    return false;
  if (radID==22  && t < pT2minA )
    return false;
  if (particleDataPtr->isLepton(recID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(recID)  && t < pT2minQ )
    return false;
  if (recID==22  && t < pT2minA )
    return false;
  return true;
}

//--------------------------------------------------------------------------

bool DireSplittingQED::allowedRec(const Event& state, int iRec) {

  // Consider possible combinations of lepton-lepton QED dipoles.
  bool isAllowed_final_lepton_rec
    =   state[iRec].isFinal() && state[iRec].isLepton()
     && state[iRec].isCharged() && doFSRQEDshowerByL;
  bool isAllowed_initial_lepton_rec
    =   !state[iRec].isFinal() && state[iRec].isLepton()
     && state[iRec].isCharged() && doISRQEDshowerByL;

  bool isAllowed_final_quark_rec
    =   state[iRec].isFinal() && state[iRec].isQuark()
     && doFSRQEDshowerByQ;
  bool isAllowed_initial_quark_rec
    =   !state[iRec].isFinal() && state[iRec].isQuark()
     && doISRQEDshowerByQ;

  return isAllowed_initial_lepton_rec
    ||   isAllowed_final_lepton_rec
    ||   isAllowed_initial_quark_rec
    ||   isAllowed_final_quark_rec;
}

//--------------------------------------------------------------------------

bool DireSplittingQED::allowedQuarkRadRecPair(const Event& state,
  int iRadBef, int iRecBef) {

  // Consider possible combinations of quark-quark QED dipoles.
  bool isAllowed_QQpair_FFdip
    =   (state[iRadBef].isFinal() && state[iRecBef].isFinal())
     && (state[iRadBef].isQuark() && state[iRecBef].isQuark())
     &&  doFSRQEDshowerByQ;
  bool isAllowed_QQpair_FIdip
    =   (state[iRadBef].isFinal() && !state[iRecBef].isFinal())
     && (state[iRadBef].isQuark() && state[iRecBef].isQuark())
     &&  doFSRQEDshowerByQ && doISRQEDshowerByQ;
  bool isAllowed_QQpair_IFdip
    =   (!state[iRadBef].isFinal() && state[iRecBef].isFinal())
     && (state[iRadBef].isQuark() && state[iRecBef].isQuark())
     &&  doFSRQEDshowerByQ && doISRQEDshowerByQ;
  bool isAllowed_QQpair_IIdip
    =   (!state[iRadBef].isFinal() && !state[iRecBef].isFinal())
     && (state[iRadBef].isQuark() && state[iRecBef].isQuark())
     &&  doISRQEDshowerByQ;

  // Consider possible combinations of quark-lepton QED dipoles.
  bool isAllowed_QLpair_FFdip
    =   (state[iRadBef].isFinal()   && state[iRecBef].isFinal())
     && (state[iRadBef].isQuark()   && state[iRecBef].isLepton())
     &&  state[iRecBef].isCharged()
     &&  doFSRQEDshowerByQ && doFSRQEDshowerByL;
  bool isAllowed_QLpair_FIdip
    =   (state[iRadBef].isFinal()   && !state[iRecBef].isFinal())
     && (state[iRadBef].isQuark()   && state[iRecBef].isLepton())
     &&  state[iRecBef].isCharged()
     &&  doFSRQEDshowerByQ && doISRQEDshowerByL;
  bool isAllowed_QLpair_IFdip
    =   (!state[iRadBef].isFinal()  && state[iRecBef].isFinal())
     && (state[iRadBef].isQuark()   && state[iRecBef].isLepton())
     &&  state[iRecBef].isCharged()
     && doISRQEDshowerByQ && doFSRQEDshowerByL;
  bool isAllowed_QLpair_IIdip
    =   (!state[iRadBef].isFinal()  && !state[iRecBef].isFinal())
     && (state[iRadBef].isQuark()   && state[iRecBef].isLepton())
     &&  state[iRecBef].isCharged()
     && doISRQEDshowerByQ && doISRQEDshowerByL;

  return isAllowed_QQpair_FFdip
    ||   isAllowed_QQpair_FIdip
    ||   isAllowed_QQpair_IFdip
    ||   isAllowed_QQpair_IIdip
    ||   isAllowed_QLpair_FFdip
    ||   isAllowed_QLpair_FIdip
    ||   isAllowed_QLpair_IFdip
    ||   isAllowed_QLpair_IIdip;

}

//--------------------------------------------------------------------------

bool DireSplittingQED::allowedLeptonRadRecPair(const Event& state,
  int iRadBef, int iRecBef) {

  // Consider possible combinations of lepton-lepton QED dipoles.
  bool isAllowed_LLpair_FFdip
    =   (state[iRadBef].isFinal()   && state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isLepton())
     && (state[iRadBef].isCharged() && state[iRecBef].isCharged())
     && doFSRQEDshowerByL;
  bool isAllowed_LLpair_FIdip
    =   (state[iRadBef].isFinal()   && !state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isLepton())
     && (state[iRadBef].isCharged() && state[iRecBef].isCharged())
     && doFSRQEDshowerByL && doISRQEDshowerByL;
  bool isAllowed_LLpair_IFdip
    =   (!state[iRadBef].isFinal()   && state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isLepton())
     && (state[iRadBef].isCharged() && state[iRecBef].isCharged())
     && doFSRQEDshowerByL && doISRQEDshowerByL;
  bool isAllowed_LLpair_IIdip
    =   (!state[iRadBef].isFinal()   && !state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isLepton())
     && (state[iRadBef].isCharged() && state[iRecBef].isCharged())
     && doISRQEDshowerByL;

  // Consider possible combinations of lepton-quark QED dipoles.
  bool isAllowed_LQpair_FFdip
    =   (state[iRadBef].isFinal()   && state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isQuark())
     &&  state[iRadBef].isCharged()
     &&  doFSRQEDshowerByL && doFSRQEDshowerByQ;
  bool isAllowed_LQpair_FIdip
    =   (state[iRadBef].isFinal()   && !state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isQuark())
     &&  state[iRadBef].isCharged()
     &&  doFSRQEDshowerByL && doISRQEDshowerByQ;
  bool isAllowed_LQpair_IFdip
    =   (!state[iRadBef].isFinal()   && state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isQuark())
     &&  state[iRadBef].isCharged()
     &&  doISRQEDshowerByL && doFSRQEDshowerByQ;
  bool isAllowed_LQpair_IIdip
    =   (!state[iRadBef].isFinal()   && !state[iRecBef].isFinal())
     && (state[iRadBef].isLepton()  && state[iRecBef].isQuark())
     &&  state[iRadBef].isCharged()
     &&  doISRQEDshowerByL && doISRQEDshowerByQ;

  return isAllowed_LLpair_FFdip
    ||   isAllowed_LLpair_FIdip
    ||   isAllowed_LLpair_IFdip
    ||   isAllowed_LLpair_IIdip
    ||   isAllowed_LQpair_FFdip
    ||   isAllowed_LQpair_FIdip
    ||   isAllowed_LQpair_IFdip
    ||   isAllowed_LQpair_IIdip;
}

//--------------------------------------------------------------------------

double DireSplittingQED::forceChargeFactor(double charge, double pT2,
  const Event& state) {

  bool hasME = pT2 > pT2minMECs && doMECs;
  if (hasME) {
  // Construct flavor after splitting to check if ME exists
  vector <int> in, out;
  //for (int i=0; i < state.size(); ++i) {
  //  if (state[i].isFinal()) out.push_back(state[i].id());
  //  if (state[i].mother1() == 1 && state[i].mother2() == 0)
  //    in.push_back(state[i].id());
  //  if (state[i].mother1() == 2 && state[i].mother2() == 0)
  //    in.push_back(state[i].id());
  //}
  //out.push_back(22);
  for (int i=0; i < state.size(); ++i) {
    if (i == splitInfo.iRadBef) continue;
    if (state[i].isFinal()) out.push_back(state[i].id());
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      in.push_back(state[i].id());
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      in.push_back(state[i].id());
  }
  int idRad   = splitInfo.radBef()->id; 
  int colType = 0;
  vector<int> re = radAndEmt( idRad, colType);
  if (is_isr) in.push_back(re[0]);
  else       out.push_back(re[0]);
  for (int i=1; i < int(re.size()); ++i) out.push_back(re[i]);

  //bool hasME = pT2 > pT2minMECs && doMECs;
  if      (is_fsr) hasME = hasME && fsr->weights->hasME(in,out);
  else if (is_isr) hasME = hasME && fsr->weights->hasME(in,out);
  else             hasME = false;
  }

  double chg = charge;
  if (hasME && chg < 0.0) chg = abs(chg);

  int signrad = splitInfo.radBef()->isFinal ? 1 : -1;
  int signrec = splitInfo.recBef()->isFinal ? 1 : -1;
  if ( doForcePos
    && ( chg < 0.
      || signrad*splitInfo.radBef()->id != -signrec*splitInfo.recBef()->id)
    && ( hasME || (pT2minForcePos > 0. && pT2 > pT2minForcePos)))
    chg = chgprefac*abs(chg);
  if (!hasME && pT2 < pT2minAllowNeg
    && ( chg < 0.
      || signrad*splitInfo.radBef()->id != -signrec*splitInfo.recBef()->id))
    chg = 0.;

  return chg;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_Q2QA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isQuark() && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"]);
}

bool Dire_fsr_qed_Q2QA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return state[iRadBef].isFinal() && state[iRadBef].isQuark()
    && allowedQuarkRadRecPair(state, iRadBef, iRecBef);
}

int Dire_fsr_qed_Q2QA::kinMap()                 { return 1;}
int Dire_fsr_qed_Q2QA::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_Q2QA::sisterID(int)            { return 22;}

double Dire_fsr_qed_Q2QA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_qed_Q2QA::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_Q2QA::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isQuark(idRad) && idEmt == 22 ) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_qed_Q2QA::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_Q2QA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !state[iRad].isQuark() 
    || state[iEmt].id() != 22) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedQuarkRadRecPair(state, iRad, i))          continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_qed_Q2QA::zSplit(double zMinAbs, double, double m2dip) {
  /*double Rz = rndmPtr->flat();
  double kappa2 = pT2minQ/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;*/

  double res = -1.;
  double Rz = rndmPtr->flat();
  double kappa2 = pT2minQ/m2dip;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;

}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_Q2QA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  /*double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;*/

  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double wt2 = preFac * 2. * 0.25 / (1.-xbef)
         * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    overInt2 = wt2;
    wt += wt2;
  }*/
  return wt;

}

// Return overestimate for new splitting.
double Dire_fsr_qed_Q2QA::overestimateDiff(double z, double m2dip, int) {
  /*double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;*/

  double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    wt += preFac * 2. * 0.25 / ( (1.-z)*(1-xbef) + kappaOld2);
  }*/
  return wt;

}

// Return kernel for new splitting.
bool Dire_fsr_qed_Q2QA::calc(const Event& state, int orderNow) { 

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac
                = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceChargeFactor(chargeFac, pT2,state);
  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  double ztilde = z;
  if (splitType>0) {
    double yCS = kappa2 / (1.-z);
    ztilde = (z-yCS) / (1.-yCS);
  }
  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) {
    wt  += -preFac * ( 1.+ztilde );
  }
  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) wt  += -preFac * ( 1.+z );

  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) {
  //  // splitType == 2 -> Massive FF
  //  if (splitType > 0) {
  //    double yCS = kappa2 / (1.-z);
  //    wt  += -preFac * (1-yCS) * ( 1.+z );
  //  } else {
  //    wt  += -preFac * ( 1.+z );
  //  }
  //}

  //if (!doMassive && orderNow >= 0) wt  += preFac * ( 1.-z );

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    double massCorr = -vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  wt *= z; 

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_Q2AQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isQuark() && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"]);
}

bool Dire_fsr_qed_Q2AQ::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return state[iRadBef].isFinal() && state[iRadBef].isQuark()
    && allowedQuarkRadRecPair(state, iRadBef, iRecBef);
}

int Dire_fsr_qed_Q2AQ::kinMap()                 { return 1;}
int Dire_fsr_qed_Q2AQ::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_Q2AQ::sisterID(int)            { return 22;}

double Dire_fsr_qed_Q2AQ::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_qed_Q2AQ::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_Q2AQ::radBefID(int idRad, int idEmt) {
  if (idRad == 22 && particleDataPtr->isQuark(idEmt)) return idEmt;
  if (idEmt == 22 && particleDataPtr->isQuark(idRad)) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_qed_Q2AQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_Q2AQ::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !state[iRad].isQuark() 
    || state[iEmt].id() != 22) return recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedQuarkRadRecPair(state, iRad, i))          continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_qed_Q2AQ::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_Q2AQ::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_Q2AQ::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_Q2AQ::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double wt = 0.;

  double chargeFac
                = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  double ztilde = z;
  if (splitType>0) {
    double yCS = kappa2 / (1.-z);
    ztilde = (z-yCS) / (1.-yCS);
  }
  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) {
    wt  += -preFac * ( 1.+ztilde );
  }
  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) wt  += -preFac * ( 1.+z );
  //if (!doMassive && orderNow >= 0) wt  += preFac * ( 1.-z );
  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) {
  //  // splitType == 2 -> Massive FF
  //  if (splitType > 0) {
  //    double yCS = kappa2 / (1.-z);
  //    wt  += -preFac * (1-yCS) * ( 1.+z );
  //  } else {
  //    wt  += -preFac * ( 1.+z );
  //  }
  //}

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    double massCorr = -vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  wt *= ( 1. - z ); 

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_L2LA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isLepton() && state[ints.first].isCharged()
        && state[ints.second].isCharged()
        && bools["doQEDshowerByL"]);
}

bool Dire_fsr_qed_L2LA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return state[iRadBef].isFinal()
    && allowedLeptonRadRecPair(state, iRadBef, iRecBef);
}

int Dire_fsr_qed_L2LA::kinMap()                 { return 1;}
int Dire_fsr_qed_L2LA::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_L2LA::sisterID(int)            { return 22;}

double Dire_fsr_qed_L2LA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_qed_L2LA::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_L2LA::radBefID(int idRad, int idEmt) {
  if (idEmt == 22 && particleDataPtr->isLepton(idRad)
    && particleDataPtr->charge(idRad) != 0) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_qed_L2LA::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_L2LA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !(state[iRad].isLepton() && state[iRad].isCharged()) 
    || state[iEmt].id() != 22) return recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedLeptonRadRecPair(state, iRad, i))         continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_qed_L2LA::zSplit(double zMinAbs, double, double m2dip) {
  /*double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;*/
  double res = -1.;
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_L2LA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  /*double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;*/
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double wt2 = preFac * 2. * 0.25 / (1.-xbef)
         * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    overInt2 = wt2;
    wt += wt2;
  }*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_L2LA::overestimateDiff(double z, double m2dip, int) {
  /*double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;*/
  double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    wt += preFac * 2. * 0.25 / ( (1.-z)*(1-xbef) + kappaOld2);
  }*/
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_L2LA::calc(const Event& state, int orderNow) { 

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  double ztilde = z;
  if (splitType>0) {
    double yCS = kappa2 / (1.-z);
    ztilde = (z-yCS) / (1.-yCS);
  }
  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) {
    // splitType == 2 -> Massive FF
//    if (splitType > 0) {
// /     double yCS = kappa2 / (1.-z);
//      wt  += -preFac * (1-yCS) * ( 1.+z );
//    } else {
      wt  += -preFac * ( 1.+ztilde );
//    }
  }

  //if (!doMassive && orderNow >= 0) wt  += preFac * ( 1.-z );

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    double massCorr = -vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  wt *= z; 

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_L2AL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isLepton() && state[ints.first].isCharged()
        && state[ints.second].isCharged()
        && bools["doQEDshowerByL"]);
}

bool Dire_fsr_qed_L2AL::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return state[iRadBef].isFinal()
    && allowedLeptonRadRecPair(state, iRadBef, iRecBef);
}

int Dire_fsr_qed_L2AL::kinMap()                 { return 1;}
int Dire_fsr_qed_L2AL::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_L2AL::sisterID(int)            { return 22;}

double Dire_fsr_qed_L2AL::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_qed_L2AL::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_L2AL::radBefID(int idRad, int idEmt) {
  if (idRad == 22 && particleDataPtr->isLepton(idEmt)
    && particleDataPtr->charge(idEmt) != 0) return idEmt;
  if (idEmt == 22 && particleDataPtr->isLepton(idRad)
    && particleDataPtr->charge(idRad) != 0) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_qed_L2AL::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_L2AL::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !(state[iRad].isLepton() && state[iRad].isCharged())  
    || state[iEmt].id() != 22) return recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedLeptonRadRecPair(state, iRad, i))         continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_qed_L2AL::zSplit(double zMinAbs, double, double m2dip) {
  /*double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;*/
  double res = -1.;
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=0.;
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_L2AL::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  /*double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;*/
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=0.;
    double tau2 = kappa2/(1.-xbef);
    double wt2 = preFac * 2. / (1.-xbef)
         * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    overInt2 = wt2;
    wt += wt2;
  }*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_L2AL::overestimateDiff(double z, double m2dip, int) {
  /*double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;*/
  double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=0.;
    wt += preFac * 2. / ( (1.-z)*(1-xbef) + kappaOld2);
  }*/
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_L2AL::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  double ztilde = z;
  if (splitType>0) {
    double yCS = kappa2 / (1.-z);
    ztilde = (z-yCS) / (1.-yCS);
  }
  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) {
    wt  += -preFac * ( 1.+ztilde );
  }

  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) wt  += -preFac * ( 1.+z );
  //if (!doMassive && orderNow >= 0) wt  += preFac * ( 1. - z );

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    double massCorr = -vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  wt *= ( 1. - z ); 

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->QG (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_Q2QA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isQuark()
        && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_qed_Q2QA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return !state[iRadBef].isFinal()
    && allowedQuarkRadRecPair(state, iRadBef, iRecBef);
}

int Dire_isr_qed_Q2QA::kinMap()                 { return 1;}
int Dire_isr_qed_Q2QA::motherID(int idDaughter) { return idDaughter;} 
int Dire_isr_qed_Q2QA::sisterID(int)            { return 22;}

double Dire_isr_qed_Q2QA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_isr_qed_Q2QA::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_qed_Q2QA::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isQuark(idRad) && idEmt == 22 ) return idRad;
  return 0;
}

pair<int,int> Dire_isr_qed_Q2QA::radBefCols( int colRadAfter, int acolRadAfter, int,
  int) {
  bool isQuark  = (colRadAfter > 0);
  if (isQuark) return make_pair(colRadAfter,0); 
  return make_pair(0,acolRadAfter); 
}

vector<int>Dire_isr_qed_Q2QA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( state[iRad].isFinal() || !state[iRad].isQuark()
    || state[iEmt].id() != 22) return recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedQuarkRadRecPair(state, iRad, i))          continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_isr_qed_Q2QA::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_Q2QA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  //double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);

  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_Q2QA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  //double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_Q2QA::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  double tDire(pT2);
  if ( isr->kinRels->ISRevolutionMode!=0
    && state[splitInfo.iRecBef].isFinal())
    tDire = isr->kinRels->t_if_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrDown") != 1.)
        storeKernelVal("Variations:muRisrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrUp")   != 1.)
        storeKernelVal("Variations:muRisrUp", 0.);
      return true;
  }*/

  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   =  preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) wt += -preFac * (1.+z);
  //wt   =  preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  //if (orderNow >= 0) wt += preFac * (1.-z);
  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function G->QQ (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_A2QQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isQuark()
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_qed_A2QQ::canRadiate ( const Event& state, int iRadBef,
  int, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].isQuark()
        && doISRQEDshowerByQ);
}

int Dire_isr_qed_A2QQ::kinMap()                 { return 1;}
int Dire_isr_qed_A2QQ::motherID(int)            { return 22;} 
int Dire_isr_qed_A2QQ::sisterID(int idDaughter) { return -idDaughter;} 
double Dire_isr_qed_A2QQ::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_qed_A2QQ::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_qed_A2QQ::radBefID(int, int idEA){ return -idEA;}
pair<int,int> Dire_isr_qed_A2QQ::radBefCols( int, int, int colEmtAfter,
  int acolEmtAfter) {
  if ( acolEmtAfter > 0 ) return make_pair(acolEmtAfter,0);
  return make_pair(0, colEmtAfter);
}

// Pick z for new splitting.
double Dire_isr_qed_A2QQ::zSplit(double zMinAbs, double zMaxAbs, double) {
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  double res = zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_A2QQ::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt  = preFac 
      * 2. * ( zMaxAbs - zMinAbs);
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_A2QQ::overestimateDiff(double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt = preFac 
     * 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_A2QQ::calc(const Event& state, int orderNow) {


  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2);

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * (pow(1.-z,2.) + pow(z,2.));

  if (orderNow >= 0) wt = 0.;

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->AQ (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_Q2AQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].id() == 22
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_qed_Q2AQ::canRadiate ( const Event& state, int iRadBef,
  int, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].id() == 22
        && doISRQEDshowerByQ);
}

int Dire_isr_qed_Q2AQ::kinMap()                 { return 1;}
int Dire_isr_qed_Q2AQ::motherID(int)            { return 1;} // Use 1 as dummy 
int Dire_isr_qed_Q2AQ::sisterID(int)            { return 1;} // Use 1 as dummy
double Dire_isr_qed_Q2AQ::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_qed_Q2AQ::symmetryFactor ( int, int )     { return 0.5;}

int Dire_isr_qed_Q2AQ::radBefID(int, int){ return 22;}
pair<int,int> Dire_isr_qed_Q2AQ::radBefCols( int, int, int, int) {
  return make_pair(0,0); }

// Pick z for new splitting.
double Dire_isr_qed_Q2AQ::zSplit(double zMinAbs, double, double) {
  double R = rndmPtr->flat();
  double res = pow(zMinAbs,3./4.)
          / ( pow(1. + R*(-1. + pow(zMinAbs,-3./8.)),2./3.)
             *pow(R - (-1. + R)*pow(zMinAbs,3./8.),2.));
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_Q2AQ::overestimateInt(double zMinAbs, double,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2./3. * (8.*(-1. + pow(zMinAbs,-3./8.)));
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_Q2AQ::overestimateDiff(double z, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2. / pow(z,11./8.);
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_Q2AQ::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2Rec(splitInfo.kinematics()->m2Rec);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( isr->kinRels->ISRevolutionMode!=0
    && state[splitInfo.iRecBef].isFinal())
    tDire = isr->kinRels->t_if_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrDown") != 1.)
        storeKernelVal("Variations:muRisrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrUp")   != 1.)
        storeKernelVal("Variations:muRisrUp", 0.);
      return true;
  }*/

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  double kappa2 = tDire / m2dip;
  wt   = preFac * 2.*z / (pow2(z)+kappa2);
  if (orderNow >= 0) wt += preFac*(z-2);
  //wt   = preFac * 2.*z*(1.-z) / (pow2(z)+kappa2);
  //if (orderNow >= 0) wt += preFac*z;

  // Correction for massive IF splittings.
  bool doMassive = ( m2Rec > 0. && splitType == 2);

  if (doMassive && orderNow >= 0) {
    // Construct CS variables.
    double uCS = kappa2 / (1-z);

    double massCorr = -2. * m2Rec / m2dip * uCS / (1.-uCS);
    // Add correction.
    wt += preFac * massCorr;

  }

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function L->LA (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_L2LA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isLepton() && state[ints.first].isCharged()
        && state[ints.second].isCharged()
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_qed_L2LA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return !state[iRadBef].isFinal()
    && allowedLeptonRadRecPair(state, iRadBef, iRecBef);
}

int Dire_isr_qed_L2LA::kinMap()                 { return 1;}
int Dire_isr_qed_L2LA::motherID(int idDaughter) { return idDaughter;} 
int Dire_isr_qed_L2LA::sisterID(int)            { return 22;} 

double Dire_isr_qed_L2LA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_isr_qed_L2LA::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_qed_L2LA::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isLepton(idRad) && particleDataPtr->charge(idRad) != 0
    && idEmt == 22 ) return idRad;
  return 0;
}


pair<int,int> Dire_isr_qed_L2LA::radBefCols( int colRadAfter, int acolRadAfter, int,
  int) {
  bool isQuark  = (colRadAfter > 0);
  if (isQuark) return make_pair(colRadAfter,0); 
  return make_pair(0,acolRadAfter); 
}

vector<int>Dire_isr_qed_L2LA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( state[iRad].isFinal()
    || !(state[iRad].isLepton() && state[iRad].isCharged())
    || state[iEmt].id() != 22) return recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedLeptonRadRecPair(state, iRad, i))         continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;

} 





// Pick z for new splitting.
double Dire_isr_qed_L2LA::zSplit(double zMinAbs, double, double m2dip) {

  /*double Rz = rndmPtr->flat();
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;*/

  double res = -1.;
  double Rz = rndmPtr->flat();
  double kappa2 = pT2minL/m2dip;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_L2LA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {

  /*double wt = 0.;
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;*/

  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    double tau2 = kappa2/(1.-xbef);
    double wt2 = preFac * 2. * 0.25 / (1.-xbef)
         * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    overInt2 = wt2;
    wt += wt2;
  }*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_L2LA::overestimateDiff(double z, double m2dip, int) {

  /*double wt = 0.;
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;*/

  double wt = 0.;
  double charge = chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true);
  double preFac = symmetryFactor() * abs(charge);
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    xbef=pow(xbef,200);
    wt += preFac * 2. * 0.25 / ( (1.-z)*(1-xbef) + kappaOld2);
  }*/
  return wt;
}

/*// Pick z for new splitting.
double Dire_isr_qed_L2LA::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_L2LA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  //double preFac = symmetryFactor()
  //  * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_L2LA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  //double preFac = symmetryFactor()
  //  * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  double preFac = symmetryFactor() * abs(chargeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id, true));
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  return wt;
}*/

// Return kernel for new splitting.
bool Dire_isr_qed_L2LA::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  double tDire(pT2);
  if ( isr->kinRels->ISRevolutionMode!=0
    && state[splitInfo.iRecBef].isFinal())
    tDire = isr->kinRels->t_if_dire_from_cs(z, pT2, m2dip);

//  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
//    state[splitInfo.iRecBef])) {
////cout << __LINE__ << endl;
//    return zero();
//  }

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrDown") != 1.)
        storeKernelVal("Variations:muRisrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrUp")   != 1.)
        storeKernelVal("Variations:muRisrUp", 0.);
      return true;
  }*/

  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   =  preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) wt += -preFac * (1.+z);
  //wt   =  preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  //if (orderNow >= 0) wt += preFac * (1.-z);

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function A->LL (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_A2LL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isLepton() && state[ints.first].isCharged()
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_qed_A2LL::canRadiate ( const Event& state, int iRadBef,
  int, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].isLepton()
        && state[iRadBef].isCharged()
        && doISRQEDshowerByL);
}

int Dire_isr_qed_A2LL::kinMap()                 { return 1;}
int Dire_isr_qed_A2LL::motherID(int)            { return 22;} 
int Dire_isr_qed_A2LL::sisterID(int idDaughter) { return -idDaughter;} 
double Dire_isr_qed_A2LL::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_qed_A2LL::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_qed_A2LL::radBefID(int, int idEA){ return -idEA;}
pair<int,int> Dire_isr_qed_A2LL::radBefCols( int, int, int colEmtAfter,
  int acolEmtAfter) {
  if ( acolEmtAfter > 0 ) return make_pair(acolEmtAfter,0);
  return make_pair(0, colEmtAfter);
}

// Pick z for new splitting.
double Dire_isr_qed_A2LL::zSplit(double zMinAbs, double zMaxAbs, double) {
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  double res = zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_A2LL::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt  = preFac 
      * 2. * ( zMaxAbs - zMinAbs);

  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_A2LL::overestimateDiff(double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt = preFac 
     * 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_A2LL::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2);

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * (pow(1.-z,2.) + pow(z,2.));

  if (orderNow == -1) wt = 0.0;

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function L->AL (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_L2AL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].id() == 22
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_qed_L2AL::canRadiate ( const Event& state, int iRadBef,
  int, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].id() == 22
        && doISRQEDshowerByL);
}

int Dire_isr_qed_L2AL::kinMap()                 { return 1;}
int Dire_isr_qed_L2AL::motherID(int)            { return 1;} // Use 1 as dummy 
int Dire_isr_qed_L2AL::sisterID(int)            { return 1;} // Use 1 as dummy
double Dire_isr_qed_L2AL::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_qed_L2AL::symmetryFactor ( int, int )     { return 0.5;}

int Dire_isr_qed_L2AL::radBefID(int, int){ return 22;}
pair<int,int> Dire_isr_qed_L2AL::radBefCols( int, int, int, int) {
  return make_pair(0,0); }

// Pick z for new splitting.
double Dire_isr_qed_L2AL::zSplit(double zMinAbs, double, double) {
  double R = rndmPtr->flat();
  double res = pow(zMinAbs,3./4.)
          / ( pow(1. + R*(-1. + pow(zMinAbs,-3./8.)),2./3.)
             *pow(R - (-1. + R)*pow(zMinAbs,3./8.),2.));
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_L2AL::overestimateInt(double zMinAbs, double,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2./3. * (8.*(-1. + pow(zMinAbs,-3./8.)));
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_L2AL::overestimateDiff(double z, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2. / pow(z,11./8.);
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_L2AL::calc(const Event& state, int orderNow) {

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2Rec(splitInfo.kinematics()->m2Rec);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( isr->kinRels->ISRevolutionMode!=0
    && state[splitInfo.iRecBef].isFinal())
    tDire = isr->kinRels->t_if_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrDown") != 1.)
        storeKernelVal("Variations:muRisrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRisrUp")   != 1.)
        storeKernelVal("Variations:muRisrUp", 0.);
      return true;
  }*/

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  double kappa2 = tDire / m2dip;
  wt   = preFac * 2.*z / (pow2(z)+kappa2);
  if (orderNow >= 0) wt += preFac*(z-2.);
  //wt   = preFac * 2.*z*(1.-z) / (pow2(z)+kappa2);
  //if (orderNow >= 0) wt += preFac*z;

  // Correction for massive IF splittings.
  bool doMassive = ( m2Rec > 0. && splitType == 2);

  if (doMassive && orderNow >= 0) {
    // Construct CS variables.
    double uCS = kappa2 / (1-z);

    double massCorr = -2. * m2Rec / m2dip * uCS / (1.-uCS);
    // Add correction.
    wt += preFac * massCorr;

  }

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_Q2QA_notPartial::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isQuark() && !state[ints.second].isCharged()
        && bools["doQEDshowerByQ"]);
}

bool Dire_fsr_qed_Q2QA_notPartial::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        && state[iRadBef].isQuark() && !state[iRecBef].isCharged()
        && doFSRQEDshowerByQ);
}

int Dire_fsr_qed_Q2QA_notPartial::kinMap()                 { return 1;}
int Dire_fsr_qed_Q2QA_notPartial::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_Q2QA_notPartial::sisterID(int)            { return 22;}

double Dire_fsr_qed_Q2QA_notPartial::gaugeFactor ( int idRadBef, int) {
  if (idRadBef != 0) return pow2(particleDataPtr->charge(idRadBef));
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_qed_Q2QA_notPartial::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_Q2QA_notPartial::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isQuark(idRad) && idEmt == 22 ) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_qed_Q2QA_notPartial::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_Q2QA_notPartial::recPositions(const Event&, int, int) {
  // Not implemented yet.
  vector<int> recs;
  return recs;
} 

// Pick z for new splitting.
double Dire_fsr_qed_Q2QA_notPartial::zSplit(double zMinAbs, double zMaxAbs,
  double /*m2dip*/) {
  double Rz = rndmPtr->flat();
  //double kappa4 = pow4(settingsPtr->parm("TimeShower:pTminChgQ"))/pow2(m2dip);
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa4, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa4);
  double res = 1. - (1.-zMaxAbs) * pow( (1.-zMinAbs)/(1.-zMaxAbs), Rz); 
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_Q2QA_notPartial::overestimateInt(double zMinAbs,
  double zMaxAbs, double, double /*m2dip*/, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa4 = pow4(settingsPtr->parm("TimeShower:pTminChgQ"))/pow2(m2dip);
  //wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa4);
  wt = preFac * 2. * log((1.-zMaxAbs)/(1.-zMinAbs)); 
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_Q2QA_notPartial::overestimateDiff(double z,
  double /*m2dip*/, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappa4 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/pow2(m2dip);
  //wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappa4);
  wt  = preFac * 2. / (1.-z);
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_Q2QA_notPartial::calc(const Event& state, int orderNow) { 

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * 2. * z / (1.-z);

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) wt  += preFac * ( 1.-z );

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    wt += preFac*massCorr;
  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQED class.

// SplittingQED function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_L2LA_notPartial::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isLepton()   && state[ints.first].isCharged()
        && !state[ints.second].isCharged() && bools["doQEDshowerByL"]);
}

bool Dire_fsr_qed_L2LA_notPartial::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        && state[iRadBef].isLepton()   && state[iRadBef].isCharged()
        && !state[iRecBef].isCharged() && doFSRQEDshowerByL);
}

int Dire_fsr_qed_L2LA_notPartial::kinMap()                 { return 1;}
int Dire_fsr_qed_L2LA_notPartial::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_qed_L2LA_notPartial::sisterID(int)            { return 22;}

double Dire_fsr_qed_L2LA_notPartial::gaugeFactor (int idRadBef, int) {
  if (idRadBef != 0) return pow2(particleDataPtr->charge(idRadBef));
  return 0.;
}

double Dire_fsr_qed_L2LA_notPartial::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_qed_L2LA_notPartial::radBefID(int idRad, int idEmt) {
  if (idEmt == 22 && particleDataPtr->isLepton(idRad)
    && particleDataPtr->charge(idRad) != 0) return idRad;
  return 0;
}


pair<int,int> Dire_fsr_qed_L2LA_notPartial::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_qed_L2LA_notPartial::recPositions(const Event&, int, int) {
  // Not implemented yet.
  vector<int> recs;
  return recs;
}

// Pick z for new splitting.
double Dire_fsr_qed_L2LA_notPartial::zSplit(double zMinAbs, double zMaxAbs,
  double /*m2dip*/) {
  double Rz = rndmPtr->flat();
  //double kappa4 = pow4(settingsPtr->parm("TimeShower:pTminChgL"))
  //              / pow2(m2dip);
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa4, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa4);
  double res = 1. - (1.-zMaxAbs) * pow( (1.-zMinAbs)/(1.-zMaxAbs), Rz); 
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_L2LA_notPartial::overestimateInt(double zMinAbs,
  double zMaxAbs, double, double /*m2dip*/, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa4 = pow4(settingsPtr->parm("TimeShower:pTminChgL"))/pow2(m2dip);
  //wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa4);
  wt = preFac * 2. * log((1.-zMaxAbs)/(1.-zMinAbs)); 
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_L2LA_notPartial::overestimateDiff(double z,
  double /*m2dip*/, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappa4 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/pow2(m2dip);
  //wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappa4);
  wt  = preFac * 2. / (1.-z);
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_L2LA_notPartial::calc(const Event& state, int orderNow) { 

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !aboveCutoff(10.*tDire, state[splitInfo.iRadBef],
    state[splitInfo.iRecBef]))
    return zero();
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = tDire/m2dip;
  wt   = preFac * 2. * z / (1.-z);

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) wt  += preFac * ( 1.-z );

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      double Q2mass = m2dip + m2Rad + m2Rec + m2Emt;
      vijkt         = pow2(Q2mass/m2dip - nu2RadBef - nu2Rec)
                    - 4.*nu2RadBef*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      vijkt         = sqrt(vijkt)/ (Q2mass/m2dip - nu2RadBef - nu2Rec);
      pipj          = m2dip * yCS/2.;
    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {

      // Calculate CS variables.
      double xCS = 1 - kappa2/(1.-z);
      vijk   = 1.; 
      vijkt  = 1.;
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Add B1 for massive splittings.
    double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    wt += preFac*massCorr;
  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

unordered_map<string,double> Dire_fsr_qed_A2FF::getPhasespaceVars(
  const Event& state, PartonSystems*) {

  // Read all splitting variables.
  unordered_map<string,double> ret;

  // Now construct Bjorken-x of initial-state after branching, as is necessary
  // to attach PDF ratios.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft),
    m2Emt2(splitInfo.kinematics()->m2EmtAft2);
    //sai(splitInfo.kinematics()->sai), xa(splitInfo.kinematics()->xa);

  // Kinematic variable to enable branching.
  // Final-final
  if (splitInfo.radBef()->isFinal  && splitInfo.recBef()->isFinal ) {
    ret.insert(make_pair("m2Dip",m2dip));
    ret.insert(make_pair("pT2",tdire_ff(z,pT2,m2dip)));
    ret.insert(make_pair("pT2Old",splitInfo.kinematics()->pT2Old));
    ret.insert(make_pair("z",zdire_ff(z,pT2,m2dip)));
    ret.insert(make_pair("phi",splitInfo.kinematics()->phi));
    ret.insert(make_pair("sai",splitInfo.kinematics()->sai));
    ret.insert(make_pair("xa",splitInfo.kinematics()->xa));
    ret.insert(make_pair("phi2",splitInfo.kinematics()->phi2));
    ret.insert(make_pair("m2RadBef",m2RadBef));
    ret.insert(make_pair("m2Rec",m2Rec));
    ret.insert(make_pair("m2RadAft",m2Rad));
    ret.insert(make_pair("m2EmtAft",m2Emt));
    ret.insert(make_pair("m2EmtAft2",m2Emt2));
    ret.insert(make_pair("xInAft", 1.));

  // Final-initial
  } else if (splitInfo.radBef()->isFinal  && !splitInfo.recBef()->isFinal ) {

    double tDire = tdire_fi(z,pT2,m2dip);
    double zDire = zdire_fi(z,pT2,m2dip);

    ret.insert(make_pair("m2Dip",m2dip));
    ret.insert(make_pair("pT2",tDire));
    ret.insert(make_pair("pT2Old",splitInfo.kinematics()->pT2Old));
    ret.insert(make_pair("z",zDire));
    ret.insert(make_pair("phi",splitInfo.kinematics()->phi));
    ret.insert(make_pair("sai",splitInfo.kinematics()->sai));
    ret.insert(make_pair("xa",splitInfo.kinematics()->xa));
    ret.insert(make_pair("phi2",splitInfo.kinematics()->phi2));
    ret.insert(make_pair("m2RadBef",m2RadBef));
    ret.insert(make_pair("m2Rec",m2Rec));
    ret.insert(make_pair("m2RadAft",m2Rad));
    ret.insert(make_pair("m2EmtAft",m2Emt));
    ret.insert(make_pair("m2EmtAft2",m2Emt2));
    double xRecBef = 2.* state[splitInfo.iRecBef].e()
                       / (beamAPtr->e() + beamBPtr->e());
    // Calculate CS variables.
    double Q2     = m2dip - m2RadBef + m2Rad + m2Emt;
    double kappa2 = tDire/Q2;
    double xCS    = 1 - kappa2/(1.-zDire);
    double xCDST  = xCS*( 1. + (m2RadBef-m2Rad-m2Emt)/Q2 );
    double xAft   = xRecBef / xCDST;
    ret.insert(make_pair("xInAft", xAft));

  }

  // Done.
  return ret;
}

//--------------------------------------------------------------------------

double Dire_fsr_qed_A2FF::getJacobian( const Event&, PartonSystems*) {

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), t(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  double jacobian = 1.0;
  // Final-final jacobian.
  if ( splitInfo.radBef()->isFinal && splitInfo.recBef()->isFinal ) {
    double ycs = ycs_ff(z,t,m2dip);
    jacobian = 1.-ycs;
  // Final-initial jacobian
  } else if (splitInfo.radBef()->isFinal  && !splitInfo.recBef()->isFinal ) {
    double xcs = xcs_fi(z,t,m2dip);
    jacobian = xcs;
  }

  return jacobian;
}

//--------------------------------------------------------------------------

bool Dire_fsr_qed_A2FF::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.first].id() == 22
        && allowedRec(state, ints.second));
}

bool Dire_fsr_qed_A2FF::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRadBef].id() == 22
        && allowedRec(state, iRecBef));
}

vector<pair<int,int> > Dire_fsr_qed_A2FF::radAndEmtCols(int iRad, int,
  Event state) {
  vector< pair<int,int> > ret;
  if (state[iRad].id() != 22) return ret;
  ret = createvector<pair<int,int> >(make_pair(0, 0))(make_pair(0, 0));
  if (particleDataPtr->colType(idRadAfterSave) != 0) {
    int sign      = (idRadAfterSave > 0) ? 1 : -1;
    int newCol    = state.nextColTag();
    if (sign> 0) {
      ret[0].first  = newCol;
      ret[0].second = 0;
      ret[1].first  = 0;
      ret[1].second = newCol;
    } else {
      ret[0].first  = 0;
      ret[0].second = newCol;
      ret[1].first  = newCol;
      ret[1].second = 0;
    }
  }
  return ret;
}

// Return id of recombined radiator (before splitting!)
int Dire_fsr_qed_A2FF::radBefID(int idRadAfter, int idEmtAfter) {
  if ( idRadAfter == idRadAfterSave
    && particleDataPtr->isQuark(idRadAfter)
    && idEmtAfter ==-idRadAfterSave
    && particleDataPtr->isQuark(idEmtAfter)) return 22;
  if ( idRadAfter == idRadAfterSave
    && particleDataPtr->isLepton(idRadAfter)
    && particleDataPtr->chargeType(idRadAfter) != 0
    && idEmtAfter ==-idRadAfterSave
    && particleDataPtr->isLepton(idEmtAfter)
    && particleDataPtr->chargeType(idEmtAfter) != 0) return 22;
  return 0;
}

// All charged particles are potential recoilers.
vector <int> Dire_fsr_qed_A2FF::recPositions( const Event& state, int iRad,
  int iEmt) {
  if ( !state[iRad].isFinal() || state[iRad].id() != idRadAfterSave
    || state[iEmt].id() != -idRadAfterSave) return vector<int>();
  if ( state[iRad].col()  != state[iEmt].acol()
    || state[iRad].acol() != state[iEmt].col()) return vector<int>();

  vector<int> recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isCharged() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedRec(state, i))                            continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;
}

double Dire_fsr_qed_A2FF::gaugeFactor( int, int) {
  //return pow2(particleDataPtr->charge(idRadAfterSave));
  double chg = pow2(particleDataPtr->charge(idRadAfterSave));
  if (abs(idRadAfterSave)<10) chg *= 3;
  return chg;
}

// All charged particles are potential recoilers.
int Dire_fsr_qed_A2FF::get_nCharged( const Event& state, int radID,
  double t) {
  // Find charged particles.
  int nch=0;
  for (int i=0; i < state.size(); ++i) {
    if ( allowedRec(state, i)){ 
      if (radID!=0 && t>0. && !dipoleAboveCutoff(t, radID, state[i].id()))
        continue;
      if (state[i].isFinal()) nch++;
      if (state[i].mother1() == 1 && state[i].mother2() == 0) nch++;
      if (state[i].mother1() == 2 && state[i].mother2() == 0) nch++;
    }
  }
  return nch;
}

// All charged particles are potential recoilers.
int Dire_fsr_qed_A2FF::set_nCharged( const Event& state) {
  // Find charged particles.
  int nch=0;
  for (int i=0; i < state.size(); ++i) {
    if ( allowedRec(state, i)){ 
    //if ( state[i].isCharged() ) {
      if (state[i].isFinal()) nch++;
      if (state[i].mother1() == 1 && state[i].mother2() == 0) nch++;
      if (state[i].mother1() == 2 && state[i].mother2() == 0) nch++;
    }
  }
  // Done.
  nchSaved = nch;
  return nch;
}

// Pick z for new splitting.
double Dire_fsr_qed_A2FF::zSplit(double zMinAbs, double zMaxAbs,
  double /*m2dip*/) {
  return (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_A2FF::overestimateInt(double zMinAbs,double zMaxAbs,
  double /*pT2Old*/, double /*m2dip*/, int /*order*/) {
  double preFac = symmetryFactor() * abs(gaugeFactor());
  // Rememember three colors of quarks.
  if (abs(idRadAfterSave)<10) preFac *= 3.0;
  double wt     = 2. * preFac * 0.5 * ( zMaxAbs - zMinAbs);
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  return wt;
}

// Return kernel for new splitting.
double Dire_fsr_qed_A2FF::overestimateDiff(double /*z*/, double /*m2dip*/,
  int /*order*/) {
  double preFac = symmetryFactor() * abs(gaugeFactor());
  // Rememember three colors of quarks.
  if (abs(idRadAfterSave)<10) preFac *= 3.0;
  double wt     = 2. * preFac * 0.5;
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  return wt;
}

// Functions to calculate the kernel from SplitInfo information.
bool Dire_fsr_qed_A2FF::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  double tDire(pT2);
  if ( fsr->kinRels->FSRevolutionMode!=0
    && !state[splitInfo.iRecBef].isFinal())
    tDire = fsr->kinRels->t_fi_dire_from_cs(z, pT2, m2dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tDire,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  /*if (tDire < 0.1*tCutoff(state[splitInfo.iRadBef],state[splitInfo.iRecBef])) {
      storeKernelVal("base", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
        storeKernelVal("Variations:muRfsrDown", 0.);
      if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
        storeKernelVal("Variations:muRfsrUp", 0.);
      return true;
  }*/

  // Set number of recoilers.
  //set_nCharged(state);

  double ztilde = z;
  double y = 0.;
  if (splitType > 0) {
    double virt = pT2 + m2RadBef;
    y = virt / m2dip;
    ztilde = (z -y) / (1-y);
  }

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  double kappa2 = tDire/m2dip;
  wt  = preFac 
      * (pow(1.-ztilde,2.) + pow(ztilde,2.));

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  if (doMassive) {

    double vijk = 1., pipj = 0.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {
      // Calculate CS variables.
      double virt = pT2 + m2RadBef;
      double yCS = virt / m2dip;
      double nu2Rad = m2Rad/m2dip; 
      double nu2Emt = m2Emt/m2dip; 
      double nu2Rec = m2Rec/m2dip; 
      vijk          = pow2(1.-yCS) - 4.*(yCS+nu2Rad+nu2Emt)*nu2Rec;
      vijk          = sqrt(vijk) / (1-yCS);
      pipj          = m2dip * yCS /2.;

    // splitType ==-2 -> Massive FI
    } else if (splitType ==-2) {
      // Calculate CS variables.
      double virt = pT2 + m2RadBef;
      double xCS = m2dip/(m2dip+virt);
      vijk   = 1.; 
      pipj   = m2dip/2. * (1-xCS)/xCS;
    }

    // Reset kernel for massive splittings.
    wt = preFac * 1. / vijk * ( pow2(1.-ztilde) + pow2(ztilde)
                                    + m2Emt / ( pipj + m2Emt) ); 

  }

  // Multiply with z factor
  if (hasHardRadiator) wt *= ztilde;
  else wt *= 1.-ztilde;

  // Set number of recoilers.
  int nch = get_nCharged(state, 22, pT2);
  wt *= (nch>0) ? 1./nch : 0.;

  bool hasME = pT2 > pT2minMECs && doMECs;
  if (hasME) {
    vector <int> in, out;
    for (int i=0; i < state.size(); ++i) {
      if (i == splitInfo.iRadBef) continue;
      if (state[i].isFinal()) out.push_back(state[i].id());
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        in.push_back(state[i].id());
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        in.push_back(state[i].id());
    }
    int idRad   = splitInfo.radBef()->id; 
    int colType = 0;
    vector<int> re = radAndEmt( idRad, colType);
    if (is_isr) in.push_back(re[0]);
    else       out.push_back(re[0]);
    for (int i=1; i < int(re.size()); ++i) out.push_back(re[i]);
    hasME = hasME && fsr->weights->hasME(in,out);
    // Heuristic fudge factor close to peak trying to catch
    // interference enhancements.
    if (hasME) wt *= 2.;
  }

  // Trivial map of values, since kernel does not depend on coupling.
  unordered_map<string,double> wts;
  wts.insert( make_pair("base", wt ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt ));
  }

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;
}

//==========================================================================

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_qed_L2Lffbar::canRadiate (const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  // Not yet implemented.
  return false;
  return ( state[ints.first].isFinal()
        && state[ints.first].isLepton()
        && state[ints.second].isLepton());
}

bool Dire_fsr_qed_L2Lffbar::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  // Not yet implemented.
  return false;
  return ( state[iRadBef].isFinal()
        && state[iRadBef].isLepton()
        && state[iRecBef].isLepton());
}

// Dummy values, since not used!
double Dire_fsr_qed_L2Lffbar::gaugeFactor ( int, int )        { return 1.;}
double Dire_fsr_qed_L2Lffbar::symmetryFactor ( int, int )     { return 1.;}

vector<pair<int,int> > Dire_fsr_qed_L2Lffbar::radAndEmtCols(int iRad, int,
  Event state) { 

  int colRadAft(0), acolRadAft(0), colEmtAft1(0), acolEmtAft1(0),
      colEmtAft2(0), acolEmtAft2(0);

  // Also remember colors for "intermediate" particles in 1->3 splitting.
  //splitInfo.addExtra("colEmtInt",  0);
  //splitInfo.addExtra("acolEmtInt", 0);
  //splitInfo.addExtra("colRadInt",  state[iRad].col());
  //splitInfo.addExtra("acolRadInt", state[iRad].acol());
  splitInfo.colEmtInt = 0;
  splitInfo.acolEmtInt = 0;
  splitInfo.colRadInt = state[iRad].col();
  splitInfo.acolRadInt = state[iRad].acol();

  return createvector<pair<int,int> >
    (make_pair(colRadAft, acolRadAft))
    (make_pair(colEmtAft1, acolEmtAft1))
    (make_pair(colEmtAft2, acolEmtAft2));

}

int Dire_fsr_qed_L2Lffbar::radBefID(int idRA, int) {
  // Not yet implemented.
  return 0;
  if (particleDataPtr->isLepton(idRA)) return idRA;
  return 0;
}

pair<int,int> Dire_fsr_qed_L2Lffbar::radBefCols(
  int, int, 
  int, int) {
  return make_pair(0,0);
}

// All charged particles are potential recoilers.
vector <int> Dire_fsr_qed_L2Lffbar::recPositions( const Event& state,
  int iRad, int iEmt1, int iEmt2) {
  if ( !state[iRad].isFinal() || state[iEmt1].id() != idEmtAfterSave
    || state[iEmt2].id() != -idEmtAfterSave) return vector<int>();

  // Find charged particles.
  vector<int> recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iEmt2));
  // Find charged particles.
  vector<int> recs;
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isLepton() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iEmt2));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedLeptonRadRecPair(state, iRad, i))         continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }

  // Done.
  return recs;
}

/*// Pick z for new splitting.
double Dire_fsr_qed_L2Lffbar::zSplit(double zMinAbs, double, double m2dip) {
  double R = rndmPtr->flat();
  // Pick according to soft + 1/(z+kappa2)
  double a = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;

double zmin = zMinAbs;

double z1 = (2*pow(a,R) + 4*pow(a,1 + R) + 2*pow(a,2 + R) + 
        2*pow(a,2)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R) - 
        sqrt(pow(-2*pow(a,R) - 4*pow(a,1 + R) - 2*pow(a,2 + R) - 
            2*pow(a,2)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R),2) - 
          4*(pow(a,R) + 2*pow(a,1 + R) + pow(a,2 + R) - 
             a*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R))*
           (pow(a,R) + 3*pow(a,1 + R) + 3*pow(a,2 + R) + pow(a,3 + R) - 
             pow(a,3)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R))))/
      (2.*(pow(a,R) + 2*pow(a,1 + R) + pow(a,2 + R) - 
          a*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R)));

  return z1;

}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_L2Lffbar::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double m2dip, int orderNow) {
  double wt     = 0.;
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;
  double kappa2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/(z+kappa2)
  wt = CF*TR * softRescaleInt(order) * 2. 
     * 0.5 * ( log( (kappa2 + pow2(1-zMinAbs)) / (kappa2 + pow2(1-zMaxAbs)))
               + 2.*log( (kappa2+zMaxAbs)/(kappa2+zMinAbs)) );

  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_L2Lffbar::overestimateDiff(double z, double m2dip,
  int orderNow) {
  double wt        = 0.;
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double kappa2    = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/(z+kappa2)
  wt  = CF*TR * softRescaleInt(order)
      * 2.* ((1.-z) / ( pow2(1.-z) + kappa2) + 1./(z+kappa2));
  return wt;
}*/

// Pick z for new splitting.
double Dire_fsr_qed_L2Lffbar::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_qed_L2Lffbar::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  wt *= coupling()/alphaS2pi;
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_qed_L2Lffbar::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  wt *= coupling()/alphaS2pi;
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_qed_L2Lffbar::calc(const Event& state, int orderNow) { 

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z),
    pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    xa(splitInfo.kinematics()->xa),
    sai(splitInfo.kinematics()->sai),
    //m2i12(splitInfo.kinematics()->m2RadBef),
    m2i(splitInfo.kinematics()->m2RadAft),
    m21(splitInfo.kinematics()->m2EmtAft),
    m22(splitInfo.kinematics()->m2EmtAft2),
    m2j(splitInfo.kinematics()->m2Rec);

  //splitInfo.addExtra("idRadInt",22);
  //splitInfo.addExtra("idEmtInt",state[splitInfo.iRadBef].id());
  //splitInfo.addExtra("swapped",1);
  splitInfo.idRadInt = 22;
  splitInfo.idEmtInt = state[splitInfo.iRadBef].id();
  splitInfo.swapped = true;

  /*// Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;*/

  // Do nothing without other NLO kernels!
  unordered_map<string,double> wts;
  /*if ( m2i12 > 0. || m2i > 0. || m21 > 0. || m22 > 0. || m2j > 0.){
    wts.insert( make_pair("base", 0.) );
    if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", 0.));
    if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", 0.));
    adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);
    return true;
  }*/

  // Generate state after branching to extract momenta.
  Event trialEvent(state);
  bool physical = false;
  if (splitInfo.recBef()->isFinal)
    physical = fsr->branch_FF(trialEvent, true, &splitInfo);
  else
    physical = fsr->branch_FI(trialEvent, true, &splitInfo);
  // Get invariants.
  Vec4 pi(trialEvent[splitInfo.iEmtAft].p());
  Vec4 pj(trialEvent[splitInfo.iRecAft].p());
  Vec4 p1(trialEvent[splitInfo.iRadAft].p());
  Vec4 p2(trialEvent[splitInfo.iEmtAft2].p());

  // Use only massless for now!
  if ( sai > 0.
    && ( abs(pi.m2Calc()-m2i) > sai || abs(p1.m2Calc()-m21) > sai
      || abs(p2.m2Calc()-m22) > sai || abs(pj.m2Calc()-m2j) > sai))
    physical = false;

  if (!physical) {
    wts.insert( make_pair("base", 0.) );
    if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", 0.));
    if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", 0.));
    adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);
    return true;
  }

  // Get invariants.
  double sij(2.*pi*pj), si1(2.*pi*p1), si2(2.*pi*p2),
         sj1(2.*pj*p1), sj2(2.*pj*p2), s12(2.*p1*p2);

  double sign = (splitInfo.recBef()->isFinal) ? 1. : -1.;
  double p2i1(sai + m2i + m21);
  double q2   = sign*(pi+p1+p2+sign*pj).m2Calc();
  double si12 = (pi+p1+p2).m2Calc();
  double yi12 = (splitInfo.recBef()->isFinal) ? si12 / q2 : 0.;
  double z1(z/(1.-yi12)), z2( z/xa/(1-yi12) - z1 ), z3(1-z1-z2);

  // Dummy statement to avoid compiler warnings.
  if (false) cout << sij*si1*si2*sj1*sj2*s12*p2i1*z3;

  double prob = 0.0;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  prob = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) prob += preFac * (1.-z);
  if (orderNow < 0 && chargeFac < 0.) prob = 0.;

//  // From xa integration volume.
//  prob *= log(1/z1);
//  // Weight of sai-selection.
//  prob *= 1. / (1.-p2i1/si12);

  // Remember that this might be an endpoint with vanishing sai.
  if (is_sai_endpoint()) { splitInfo.set_sai(0.0); }

  // Insert value of kernel into kernel list.
  //wts.insert( make_pair("base", prob * aem2Pi(scale2) ));
  wts.insert( make_pair("base", prob));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", prob
        // * aem2Pi(scale2)) );
        ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp",   prob
        // * aem2Pi(scale2)) );
        ));
  }

  // Multiply with z to project out part where emitted gluon pair is soft,
  // and quark is identified.
//  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
//    it->second *= z2/(1.-z3);

  // Store higher order correction separately.
  wts.insert( make_pair("base_order_as2", wts["base"] ));

  // Store kernel values and return.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Return true if this kernel should partake in the evolution.
bool Dire_isr_qed_L2Lffbar::canRadiate (const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  // Not yet implemented.
  return false;
  return ( !state[ints.first].isFinal()
        && state[ints.first].isLepton()
        && state[ints.second].isLepton());
}

bool Dire_isr_qed_L2Lffbar::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  // Not yet implemented.
  return false;
  return ( !state[iRadBef].isFinal()
        && state[iRadBef].isLepton()
        && state[iRecBef].isLepton());
}

// Dummy values, since not used!
double Dire_isr_qed_L2Lffbar::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_qed_L2Lffbar::symmetryFactor ( int, int )     { return 1.;}

vector<pair<int,int> > Dire_isr_qed_L2Lffbar::radAndEmtCols(int iRad, int,
  Event state) { 

  int colRadAft(0), acolRadAft(0), colEmtAft1(0), acolEmtAft1(0),
      colEmtAft2(0), acolEmtAft2(0);

  // Also remember colors for "intermediate" particles in 1->3 splitting.
  //splitInfo.addExtra("colEmtInt",  0);
  //splitInfo.addExtra("acolEmtInt", 0);
  //splitInfo.addExtra("colRadInt",  state[iRad].col());
  //splitInfo.addExtra("acolRadInt", state[iRad].acol());
  splitInfo.colEmtInt = 0;
  splitInfo.acolEmtInt = 0;
  splitInfo.colRadInt = state[iRad].col();
  splitInfo.acolRadInt = state[iRad].acol();

  return createvector<pair<int,int> >
    (make_pair(colRadAft, acolRadAft))
    (make_pair(colEmtAft1, acolEmtAft1))
    (make_pair(colEmtAft2, acolEmtAft2));

}

int Dire_isr_qed_L2Lffbar::radBefID(int idRA, int) {
  // Not yet implemented.
  return 0;
  if (particleDataPtr->isLepton(idRA)) return idRA;
  return 0;
}

pair<int,int> Dire_isr_qed_L2Lffbar::radBefCols(
  int, int, 
  int, int) {
  return make_pair(0,0);
}

// All charged particles are potential recoilers.
vector <int> Dire_isr_qed_L2Lffbar::recPositions( const Event& state,
  int iRad, int iEmt1, int iEmt2) {
  if ( state[iRad].isFinal() || state[iEmt1].id() != idEmtAfterSave
    || state[iEmt2].id() != -idEmtAfterSave) return vector<int>();
  // Find charged particles.
  vector<int> recs;

  /*// Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iEmt2));
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( state[i].isLepton() ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }*/

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt1)(iEmt2));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( !state[i].isCharged() )                           continue;
    if ( !allowedLeptonRadRecPair(state, iRad, i))         continue;
    if (state[i].isFinal())
      recs.push_back(i);
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      recs.push_back(i);
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      recs.push_back(i);
  }


  // Done.
  return recs;
}

/*// Pick z for new splitting.
double Dire_isr_qed_L2Lffbar::zSplit(double zMinAbs, double, double m2dip) {
  double R = rndmPtr->flat();
  // Pick according to soft + 1/(z+kappa2)
  double a = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;

double zmin = zMinAbs;

double z1 = (2*pow(a,R) + 4*pow(a,1 + R) + 2*pow(a,2 + R) + 
        2*pow(a,2)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R) - 
        sqrt(pow(-2*pow(a,R) - 4*pow(a,1 + R) - 2*pow(a,2 + R) - 
            2*pow(a,2)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R),2) - 
          4*(pow(a,R) + 2*pow(a,1 + R) + pow(a,2 + R) - 
             a*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R))*
           (pow(a,R) + 3*pow(a,1 + R) + 3*pow(a,2 + R) + pow(a,3 + R) - 
             pow(a,3)*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R))))/
      (2.*(pow(a,R) + 2*pow(a,1 + R) + pow(a,2 + R) - 
          a*pow(1 + a - 2*zmin + pow(zmin,2),R)*pow(1/(a + zmin) + a/(a + zmin),2*R)));

  return z1;

}

// New overestimates, z-integrated versions.
double Dire_isr_qed_L2Lffbar::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double m2dip, int orderNow) {
  double wt     = 0.;
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;
  double kappa2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/(z+kappa2)
  wt = CF*TR * softRescaleInt(order) * 2. 
     * 0.5 * ( log( (kappa2 + pow2(1-zMinAbs)) / (kappa2 + pow2(1-zMaxAbs)))
               + 2.*log( (kappa2+zMaxAbs)/(kappa2+zMinAbs)) );

  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_L2Lffbar::overestimateDiff(double z, double m2dip,
  int orderNow) {
  double wt        = 0.;
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double kappa2    = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/(z+kappa2)
  wt  = CF*TR * softRescaleInt(order)
      * 2.* ((1.-z) / ( pow2(1.-z) + kappa2) + 1./(z+kappa2));
  return wt;
}*/

// Pick z for new splitting.
double Dire_isr_qed_L2Lffbar::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_qed_L2Lffbar::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  wt *= coupling()/alphaS2pi;
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_qed_L2Lffbar::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  wt *= coupling()/alphaS2pi;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_qed_L2Lffbar::calc(const Event& state, int orderNow) { 

  // DEBUG!
  //return zero();


  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z),
    pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    xa(splitInfo.kinematics()->xa),
    sai(splitInfo.kinematics()->sai),
    //m2i12(splitInfo.kinematics()->m2RadBef),
    m2i(splitInfo.kinematics()->m2RadAft),
    m21(splitInfo.kinematics()->m2EmtAft),
    m22(splitInfo.kinematics()->m2EmtAft2),
    m2j(splitInfo.kinematics()->m2Rec);

  //splitInfo.addExtra("idRadInt",22);
  //splitInfo.addExtra("idEmtInt",state[splitInfo.iRadBef].id());
  //splitInfo.addExtra("swapped",1);
  splitInfo.idRadInt = 22;
  splitInfo.idEmtInt = state[splitInfo.iRadBef].id();
  splitInfo.swapped = true;

  /*// Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;*/

  // Do nothing without other NLO kernels!
  unordered_map<string,double> wts;
  /*if ( m2i12 > 0. || m2i > 0. || m21 > 0. || m22 > 0. || m2j > 0.){
    wts.insert( make_pair("base", 0.) );
    if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", 0.));
    if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", 0.));
    adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);
    return true;
  }*/

  // Generate state after branching to extract momenta.
  Event trialEvent(state);
  bool physical = false;
  if (splitInfo.recBef()->isFinal)
    physical = isr->branch_IF(trialEvent, true, &splitInfo);
  else
    physical = isr->branch_II(trialEvent, true, &splitInfo);
  // Get invariants.
  Vec4 pi(trialEvent[splitInfo.iEmtAft].p());
  Vec4 pj(trialEvent[splitInfo.iRecAft].p());
  Vec4 p1(trialEvent[splitInfo.iRadAft].p());
  Vec4 p2(trialEvent[splitInfo.iEmtAft2].p());

  // Use only massless for now!
  if ( sai > 0.
    && ( abs(pi.m2Calc()-m2i) > sai || abs(p1.m2Calc()-m21) > sai
      || abs(p2.m2Calc()-m22) > sai || abs(pj.m2Calc()-m2j) > sai))
    physical = false;

  if (!physical) {
    wts.insert( make_pair("base", 0.) );
    if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", 0.));
    if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", 0.));
    adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);
    return true;
  }

  // Get invariants.
  double sij(2.*pi*pj), si1(2.*pi*p1), si2(2.*pi*p2),
         sj1(2.*pj*p1), sj2(2.*pj*p2), s12(2.*p1*p2);

  double sign = (splitInfo.recBef()->isFinal) ? 1. : -1.;
  double p2i1(sai + m2i + m21);
  double q2   = sign*(pi+p1+p2+sign*pj).m2Calc();
  double si12 = (pi+p1+p2).m2Calc();
  double yi12 = (splitInfo.recBef()->isFinal) ? si12 / q2 : 0.;
  double z1(z/(1.-yi12)), z2( z/xa/(1-yi12) - z1 ), z3(1-z1-z2);

  // Dummy statement to avoid compiler warnings.
  if (false) cout << sij*si1*si2*sj1*sj2*s12*p2i1*z3;

  double prob = 0.0;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac = forceChargeFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  prob = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) prob += preFac * (1.-z);
  if (orderNow < 0 && chargeFac < 0.) prob = 0.;

//  // From xa integration volume.
//  prob *= log(1/z1);
//  // Weight of sai-selection.
//  prob *= 1. / (1.-p2i1/si12);

  // Remember that this might be an endpoint with vanishing sai.
  if (is_sai_endpoint()) { splitInfo.set_sai(0.0); }

  // Insert value of kernel into kernel list.
  //wts.insert( make_pair("base", prob * aem2Pi(scale2) ));
  wts.insert( make_pair("base", prob));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      //wts.insert( make_pair("Variations:muRfsrDown", prob
      //  * aem2Pi(scale2)) );
      wts.insert( make_pair("Variations:muRfsrDown", prob));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      //wts.insert( make_pair("Variations:muRfsrUp",   prob
      //  * aem2Pi(scale2)) );
      wts.insert( make_pair("Variations:muRfsrUp",   prob));
  }

//  // Multiply with z to project out part where emitted gluon pair is soft,
//  // and quark is identified.
//  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
//    it->second *= z2/(1.-z3);

  // Store higher order correction separately.
  wts.insert( make_pair("base_order_as2", wts["base"] ));

  // Store kernel values and return.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================
} // end namespace Pythia8
