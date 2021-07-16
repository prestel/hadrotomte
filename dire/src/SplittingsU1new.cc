
#include "Dire/SplittingsU1new.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

namespace Pythia8 {

//==========================================================================

// The SplittingU1new class.

//--------------------------------------------------------------------------

void DireSplittingU1new::init() {

  ax0 = settingsPtr->parm("Dire:U1new:alphaX");
  splitInfo.canUseForBranching(true);

  doU1NEWfsrByQ = settingsPtr->flag("TimeShower:U1newShowerByQ");
  doU1NEWfsrByL = settingsPtr->flag("TimeShower:U1newShowerByL");
  doU1NEWisrByQ = settingsPtr->flag("SpaceShower:U1newShowerByQ");
  doU1NEWisrByL = settingsPtr->flag("SpaceShower:U1newShowerByL");

  pT2min           = (is_fsr)
                   ? pow2(settingsPtr->parm("TimeShower:pTmin"))
                   : pow2(settingsPtr->parm("SpaceShower:pTmin"));
  pT2minL          = (is_fsr)
                   ? pow2(settingsPtr->parm("DireTimes:U1new:pTminChgL"))
                   : pow2(settingsPtr->parm("DireSpace:U1new:pTminChgL"));
  pT2minQ          = (is_fsr)
                   ? pow2(settingsPtr->parm("DireTimes:U1new:pTminChgQ"))
                   : pow2(settingsPtr->parm("DireSpace:U1new:pTminChgQ"));
  pT2minA           = min(pT2minL,pT2minQ);

  double pTminForcePos = settingsPtr->parm("Dire:U1new:pTminForcePos");
  pT2minForcePosU1    = pTminForcePos > 0.0 ? pow2(pTminForcePos) : -1.0;
  double pTminAllowNeg = settingsPtr->parm("Dire:U1new:pTminAllowNeg");
  pT2minAllowNegU1    = pTminAllowNeg > 0.0 ? pow2(pTminAllowNeg) : -1.0;

  idZprime =settingsPtr->mode("Dire:U1new:idZprime");
  if (idZprime==0) idZprime = 1023;
  epsilon = settingsPtr->parm("Dire:U1new:epsilon");

  if (epsilon < 0. && !slhaInterfacePtr->slha.getEntry("hidden", 3, epsilon) ) epsilon = 0.1;
  //if (!slhaInterfacePtr->slha.getEntry("hidden", 1, epsilon) ) epsilon = 0.1;

  if (epsilon==0.5)   epsilon=sqrt(3.12501392994550098e-01);
  if (epsilon==0.1)   epsilon=sqrt(8.54486339593736426e-03);
  if (epsilon==0.01)  epsilon=sqrt(8.43477144948686763e-05);
  if (epsilon==0.001) epsilon=sqrt(8.43242588244030976e-07);

//epsilon=3.;
  alphaEMDark = pow2(epsilon) * settingsPtr->parm("StandardModel:alphaEM0");

  overInt1 = overInt2 = 0.;
}

//--------------------------------------------------------------------------

double DireSplittingU1new::coupling (double z, double pT2, double m2dip,
  double renormMultFacNow, pair<int,bool> radBef, pair<int,bool> recBef) {
  return alphaEMDark/(2.*M_PI);
  if (pT2< 0.) return (alphaEMDark/(2.*M_PI));
  double scale2 = couplingScale2 ( z, pT2, m2dip, radBef, recBef);
  if (scale2 < 0.) scale2 = pT2;
  if (z      < 0.) scale2 = pT2;
  if (renormMultFacNow>0.) pT2 *= renormMultFacNow;
  // Return coupling.
  return pow2(epsilon)*aem2Pi(scale2);
}

//--------------------------------------------------------------------------

double DireSplittingU1new::tCutoff( const Particle& radBef,
  const Particle&, PartonSystems*) {
  if (particleDataPtr->isLepton(radBef.id())) return pT2minL;
  if (particleDataPtr->isQuark(radBef.id()))  return pT2minQ;
  if (radBef.id()==idZprime)  return pT2minA;
  return -1.;
}

//--------------------------------------------------------------------------

bool DireSplittingU1new::aboveCutoff( double t, const Particle& radBef,
  const Particle&, int, PartonSystems*) {

  if (particleDataPtr->isLepton(radBef.id()) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(radBef.id())  && t < pT2minQ )
    return false;
  if (radBef.id()==idZprime && t < pT2minA)  return false;
  return true;
}

//--------------------------------------------------------------------------

bool DireSplittingU1new::dipoleAboveCutoff( double t, int radID, int recID,
  double tcut) {
  if (tcut > 0. && t < tcut) return false;
  if (particleDataPtr->isLepton(radID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(radID)  && t < pT2minQ )
    return false;
  if (radID==idZprime && t < pT2minA)  return false;
  if (particleDataPtr->isLepton(recID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(recID)  && t < pT2minQ )
    return false;
  if (recID==idZprime && t < pT2minA)  return false;
  return true;
}

//--------------------------------------------------------------------------

bool DireSplittingU1new::allowedRec(const Event& state, int iRec) {

  // Consider possible combinations of lepton-lepton QED dipoles.
  bool isAllowed_final_lepton_rec
    =   state[iRec].isFinal() && state[iRec].isLepton()
     && state[iRec].isCharged() && doU1NEWfsrByL;
  bool isAllowed_initial_lepton_rec
    =   !state[iRec].isFinal() && state[iRec].isLepton()
     && state[iRec].isCharged() && doU1NEWisrByL;

  bool isAllowed_final_quark_rec
    =   state[iRec].isFinal() && state[iRec].isQuark()
     && doU1NEWfsrByQ;
  bool isAllowed_initial_quark_rec
    =   !state[iRec].isFinal() && state[iRec].isQuark()
     && doU1NEWfsrByQ;

  bool isAllowed_final_bsm_rec
    =   state[iRec].isFinal()
     && (state[iRec].idAbs() == 900012 || state[iRec].idAbs() == 900040)
     && doU1NEWfsrByL;
  bool isAllowed_initial_bsm_rec
    =   !state[iRec].isFinal()
     && (state[iRec].idAbs() == 900012 || state[iRec].idAbs() == 900040)
     && doU1NEWisrByL;

  return isAllowed_initial_lepton_rec
    ||   isAllowed_final_lepton_rec
    ||   isAllowed_initial_quark_rec
    ||   isAllowed_final_quark_rec
    ||   isAllowed_final_bsm_rec
    ||   isAllowed_initial_bsm_rec;

}

//--------------------------------------------------------------------------

double DireSplittingU1new::forceCouplingFactor(double charge, double pT2,
  const Event& state) {

  bool hasME = pT2 > pT2minMECs && doMECs;
  if (hasME) {
  // Construct flavor after splitting to check if ME exists
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
    && ( hasME || (pT2minForcePosU1 > 0. && pT2 > pT2minForcePosU1)))
    chg = 0.0*abs(chg);
  if (!hasME && pT2 < pT2minAllowNegU1
   && ( chg < 0.
     || signrad*splitInfo.radBef()->id != -signrec*splitInfo.recBef()->id))
   chg = 0.;

  return chg;

}

//==========================================================================

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_u1new_Q2QA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isQuark() && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"]);
}

bool Dire_fsr_u1new_Q2QA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        && state[iRadBef].isQuark()
        && doU1NEWfsrByQ
        && allowedRec(state, iRecBef));
}

int Dire_fsr_u1new_Q2QA::kinMap()                 { return 1;}
int Dire_fsr_u1new_Q2QA::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_u1new_Q2QA::sisterID(int)            { return idZprime;}

double Dire_fsr_u1new_Q2QA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_u1new_Q2QA::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_u1new_Q2QA::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isQuark(idRad) && idEmt == idZprime ) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_u1new_Q2QA::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_u1new_Q2QA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !state[iRad].isQuark() 
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if (allowedRec(state,i)) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_u1new_Q2QA::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  //return res;
  // Generation of z split between two overestimates.
  double res = -1.;
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_Q2QA::overestimateInt(double zMinAbs, double /*zMaxAbs*/,
  double, double m2dip, int) {
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;

  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    //double tau2 = kappa2/(1.-xbef);
    //double wt2 = 0.1*preFac * 2. / (1.-xbef)
    //     * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    //overInt2 = wt2;
    //wt += wt2;
    double Imax = -1.*preFac*2.*0.1 / (1.-xbef)
                  *log((1.-zMaxAbs)*(1.-xbef) + kappa2);
    double Imin = -1.*preFac*2.*0.1 / (1.-xbef)
                  *log((1.-zMinAbs)*(1.-xbef) + kappa2);
    overInt2    = Imax-Imin;
    wt         += overInt2;
  }*/

  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
//  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
//    wt *= 10.;
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_u1new_Q2QA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);

  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    wt += 0.1*preFac * 2. / ( (1.-z)*(1-xbef) + kappaOld2);
  }*/

  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
//  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
//    wt *= 10.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_u1new_Q2QA::calc(const Event& state, int orderNow) { 

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

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2.* z * (1.-z) / ( pow2(1.-z) + kappa2) );
  double nu2Emt = m2Emt/m2dip; 
  //wt  *= pow2(1.+nu2Emt);

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  double ztilde = z;

  // Add collinear term for massless splittings.
  if (!doMassive && orderNow >= 0) {
    wt  += -preFac * ( 1.+ztilde );
  }
  // Add collinear term for massless splittings.
  //if (!doMassive && orderNow >= 0) wt  += -preFac * ( 1.+z );
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
      //double nu2Emt = m2Emt/m2dip; 
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
    double massCorr = -1.*vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    //wt += preFac*massCorr;
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj
    //                - nu2Emt/(2.*pipj) - 2.*nu2Emt);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  wt *= z; 

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_u1new_Q2AQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && state[ints.first].isQuark() && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"]);
}

bool Dire_fsr_u1new_Q2AQ::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        && state[iRadBef].isQuark()
        && doU1NEWfsrByQ
        && allowedRec(state, iRecBef));
}

int Dire_fsr_u1new_Q2AQ::kinMap()                 { return 1;}
int Dire_fsr_u1new_Q2AQ::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_u1new_Q2AQ::sisterID(int)            { return idZprime;}

double Dire_fsr_u1new_Q2AQ::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_u1new_Q2AQ::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_u1new_Q2AQ::radBefID(int idRad, int idEmt) {
  if (idRad == idZprime && particleDataPtr->isQuark(idEmt)) return idEmt;
  if (idEmt == idZprime && particleDataPtr->isQuark(idRad)) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_u1new_Q2AQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_u1new_Q2AQ::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !state[iRad].isQuark() 
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if (find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if (allowedRec(state, i)) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_u1new_Q2AQ::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  //return res;
  // Generation of z split between two overestimates.
  double res = -1.;
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_Q2AQ::overestimateInt(double zMinAbs, double /*zMaxAbs*/,
  double, double m2dip, int) {
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;

/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    //double tau2 = kappa2/(1.-xbef);
    //double wt2 = 0.1*preFac * 2. / (1.-xbef)
    //     * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    //overInt2 = wt2;
    //wt += wt2;
    double Imax = -1.*preFac*2.*0.1 / (1.-xbef)
                  *log((1.-zMaxAbs)*(1.-xbef) + kappa2);
    double Imin = -1.*preFac*2.*0.1 / (1.-xbef)
                  *log((1.-zMinAbs)*(1.-xbef) + kappa2);
    overInt2    = Imax-Imin;
    wt         += overInt2;
  }
*/
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
//  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
//    wt *= 2.;
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_u1new_Q2AQ::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgQ"))/m2dip;
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);

/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    wt += 0.1*preFac * 2. / ( (1.-z)*(1-xbef) + kappaOld2);
  }
*/
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
//  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
//    wt *= 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_u1new_Q2AQ::calc(const Event& state, int orderNow) {
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

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2.* z * (1.-z) / ( pow2(1.-z) + kappa2) );
  double nu2Emt = m2Emt/m2dip; nu2Emt = 0.; 
  //wt  *= pow2(1.+nu2Emt);

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

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      //double nu2Emt = m2Emt/m2dip; 
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
    double massCorr = -1.*vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    //wt += preFac*massCorr;
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj
    //                - nu2Emt/(2.*pipj) - 2.*nu2Emt);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    wt += preFac*massCorr;

  }

  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  wt *= ( 1. - z ); 

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_u1new_L2LA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        && (state[ints.first].isLepton() || state[ints.first].idAbs() == 900012 || state[ints.first].idAbs() == 900040)
        && (state[ints.second].isLepton() || state[ints.second].idAbs() == 900012 || state[ints.second].idAbs() == 900040)
        && bools["doQEDshowerByL"]);
}

bool Dire_fsr_u1new_L2LA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        //&& (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012)
        //&& (state[iRecBef].isLepton() || state[iRecBef].idAbs() == 900012)
        && (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012 || state[iRadBef].idAbs() == 900040)
        && doU1NEWfsrByL
        && allowedRec(state, iRecBef));
}

int Dire_fsr_u1new_L2LA::kinMap()                 { return 1;}
int Dire_fsr_u1new_L2LA::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_u1new_L2LA::sisterID(int)            { return idZprime;}

double Dire_fsr_u1new_L2LA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_u1new_L2LA::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_u1new_L2LA::radBefID(int idRad, int idEmt) {
  if (idEmt == idZprime
    && ( particleDataPtr->isLepton(idRad) || abs(idRad) ==  900012) ) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_u1new_L2LA::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_u1new_L2LA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !(state[iRad].isLepton() || state[iRad].idAbs() == 900012)
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( allowedRec(state,i) ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_u1new_L2LA::zSplit(double zMinAbs, double /*zMaxAbs*/, double m2dip) {
  double res = -1.;
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double tau2 = kappa2/(1.-x20);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
/*
    double Imax = -1/(1+kappa2) * tan (-zMaxAbs/(1+kappa2));
    double Imin = -1/(1+kappa2) * tan (-zMinAbs/(1+kappa2));
    res = -1*(1+kappa2)*atan(-1*(1+kappa2)*(Imin + Rz*(Imax-Imin)));
*/

  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_L2LA::overestimateInt(double zMinAbs, double /*zMaxAbs*/,
  double, double m2dip, int) {
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
//xbef=0.;
    x20=pow(xbef,200);
    //double tau2 = kappa2/(1.-xbef);
    //double wt2 = preFac * 2. * 0.25 / (1.-xbef)
    //     * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    //overInt2 = wt2;
    //wt += wt2;
    double Imax = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMaxAbs)*(1.-x20) + kappa2);
    double Imin = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMinAbs)*(1.-x20) + kappa2);
    overInt2    = Imax-Imin;
    wt         += overInt2;
  }
*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_u1new_L2LA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    wt += preFac * 2. / ( (1.-z)*(1-x20) + kappaOld2);
  }*/
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_u1new_L2LA::calc(const Event& state, int orderNow) { 

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

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2.* z * (1.-z) / ( pow2(1.-z) + kappa2) );
  double nu2Emt = m2Emt/m2dip; 
  //wt  *= pow2(1.+nu2Emt);

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

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      //double nu2Emt = m2Emt/m2dip; 
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
    double massCorr = -1.*vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    //double massCorr = -1.*vijkt/vijk*( 1. + z + m2RadBef/pipj + nu2Emt/(2.*pipj) + 2.*nu2Emt);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj
    //                - nu2Emt/(2.*pipj) - 2.*nu2Emt);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
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

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool Dire_fsr_u1new_L2AL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return ( state[ints.first].isFinal()
        //&& (state[ints.first].isLepton() || state[ints.first].idAbs() == 900012)
        //&& (state[ints.second].isLepton() || state[ints.second].idAbs() == 900012)
        && (state[ints.first].isLepton() || state[ints.first].idAbs() == 900012 || state[ints.first].idAbs() == 900040)
        && (state[ints.second].isLepton() || state[ints.second].idAbs() == 900012 || state[ints.second].idAbs() == 900040)
        && bools["doQEDshowerByL"]);
}

bool Dire_fsr_u1new_L2AL::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return ( state[iRadBef].isFinal()
        //&& (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012)
        //&& (state[iRecBef].isLepton() || state[iRecBef].idAbs() == 900012)
        && (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012 || state[iRadBef].idAbs() == 900040)
        && doU1NEWfsrByL
        && allowedRec(state, iRecBef));
}

int Dire_fsr_u1new_L2AL::kinMap()                 { return 1;}
int Dire_fsr_u1new_L2AL::motherID(int idDaughter) { return idDaughter;}
int Dire_fsr_u1new_L2AL::sisterID(int)            { return idZprime;}

double Dire_fsr_u1new_L2AL::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_fsr_u1new_L2AL::symmetryFactor ( int, int ) { return 1.;}

int Dire_fsr_u1new_L2AL::radBefID(int idRad, int idEmt) {
  if (idRad == idZprime && (particleDataPtr->isLepton(idEmt) || abs(idEmt) == 900012)
    && particleDataPtr->charge(idEmt) != 0) return idEmt;
  if (idEmt == idZprime && (particleDataPtr->isLepton(idRad) || abs(idRad) == 900012)
    && particleDataPtr->charge(idRad) != 0) return idRad;
  return 0;
}

pair<int,int> Dire_fsr_u1new_L2AL::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int, int) { return make_pair(colRadAfter,acolRadAfter); }

vector<int>Dire_fsr_u1new_L2AL::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( !state[iRad].isFinal()
    || !(state[iRad].isLepton() || state[iRad].idAbs() == 900012)  
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( allowedRec(state, i) ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_fsr_u1new_L2AL::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  double res=-1.;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
//    double xbef = splitInfo.kinematics()->xBef;
//xbef=0.;
    double tau2 = kappa2/(1.-x20);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_L2AL::overestimateInt(double zMinAbs, double /*zMaxAbs*/,
  double, double m2dip, int) {
  //double wt = 0.;
  //double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  //double preFac = symmetryFactor() * abs(charge);
  //// Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  //wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double xbef = splitInfo.kinematics()->xBef;
    x20=pow(xbef,200);
//xbef=0.;
    //double wt2 = 0.1*preFac * 2. / (1.-xbef)
    //     * log (
    //         abs( (kappa2/(1.-xbef))
    //            / (1.- zMinAbs + kappa2/(1.-xbef))));
    //double tau2 = kappa2/(1.-xbef);
    //double wt2 = preFac * 2. * 0.25 / (1.-xbef)
    //     * log ( abs(tau2 / (1.- zMinAbs + tau2)) );
    //overInt2 = wt2;
    //wt += wt2;
    double Imax = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMaxAbs)*(1.-x20) + kappa2);
    double Imin = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMinAbs)*(1.-x20) + kappa2);
    overInt2    = Imax-Imin;
    wt         += overInt2;
  }*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_fsr_u1new_L2AL::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  //double kappaOld2 = pow2(settingsPtr->parm("TimeShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
//    double xbef = splitInfo.kinematics()->xBef;
//xbef=0.;
    wt += preFac * 2. / ( (1.-z)*(1-x20) + kappaOld2);
  }*/
  return wt;
}

// Return kernel for new splitting.
bool Dire_fsr_u1new_L2AL::calc(const Event& state, int orderNow) {

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

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  wt   = preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //wt   = preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  double nu2Emt = m2Emt/m2dip; 
  //wt  *= pow2(1.+nu2Emt);

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

  // Add collinear term for massive splittings.
  if (doMassive && orderNow >= 0) {

    double pipj = 0., vijkt = 1., vijk = 1.;

    // splitType == 2 -> Massive FF
    if (splitType == 2) {

      // Calculate CS variables.
      double yCS = kappa2 / (1.-z);
      double nu2RadBef = m2RadBef/m2dip; 
      double nu2Rad = m2Rad/m2dip; 
      //double nu2Emt = m2Emt/m2dip; 
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
    double massCorr = -1.*vijkt/vijk*( 1. + ztilde + m2RadBef/pipj);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
    //wt += preFac*massCorr;
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj
    //                - nu2Emt/(2.*pipj) - 2.*nu2Emt);
    //double massCorr = vijkt/vijk*( 1. - z - m2RadBef/pipj);
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

unordered_map<string,double> Dire_fsr_u1new_A2FF::getPhasespaceVars(
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

double Dire_fsr_u1new_A2FF::getJacobian( const Event&, PartonSystems*) {

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), t(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  double jacobian = 1.0;
  // Final-final jacobian.
  if ( splitInfo.radBef()->isFinal && splitInfo.recBef()->isFinal ) {
    double ycs = ycs_ff(z,t,m2dip);
    double jacobian_cs = 1.-ycs;
    double jacobian_zcs_to_zdire = 1/(1.-ycs);
    jacobian = jacobian_cs*jacobian_zcs_to_zdire;
  // Final-initial jacobian
  } else if (splitInfo.radBef()->isFinal  && !splitInfo.recBef()->isFinal ) {
    double xcs = xcs_fi(z,t,m2dip);
    jacobian = xcs;
  }

  return jacobian;
}

//--------------------------------------------------------------------------

bool Dire_fsr_u1new_A2FF::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.first].id() == idZprime
        && (state[ints.second].isLepton()
         || state[ints.second].idAbs() == 900012));
}

bool Dire_fsr_u1new_A2FF::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  double doRadiate = ( state[iRadBef].isFinal()
        && state[iRadBef].id() == idZprime
        && allowedRec(state, iRecBef) );
  // Set number of recoilers.
  //if (doRadiate) set_nCharged(state);
  return doRadiate;
}

vector<pair<int,int> > Dire_fsr_u1new_A2FF::radAndEmtCols(int iRad, int,
  Event state) {
  vector< pair<int,int> > ret;
  if (state[iRad].id() != idZprime) return ret;
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
int Dire_fsr_u1new_A2FF::radBefID(int idRadAfter, int idEmtAfter) {
  //if ( idRadAfter == idRadAfterSave
  //  && particleDataPtr->isQuark(idRadAfter)
  //  && particleDataPtr->isQuark(idEmtAfter)) return idZprime;
  if ( idRadAfter == idRadAfterSave
    && idEmtAfter ==-idRadAfterSave)
    return idZprime;
  return 0;
}

/*// All charged particles are potential recoilers.
vector <int> Dire_fsr_u1new_A2FF::recPositions( const Event& state, int iRad,
  int iEmt) {
  if ( !state[iRad].isFinal() || state[iRad].id() != idRadAfterSave
    || state[iEmt].id() != -idRadAfterSave) return vector<int>();
  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  vector<int> recs;
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( allowedRec(state,i) ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;
}*/

// All charged particles are potential recoilers.
vector <int> Dire_fsr_u1new_A2FF::recPositions( const Event& state, int iRad,
  int iEmt) {
  if ( !state[iRad].isFinal() || state[iRad].id() != idRadAfterSave
    || state[iEmt].id() != -idRadAfterSave) return vector<int>();
  if ( state[iRad].col()  != state[iEmt].acol()
    || state[iRad].acol() != state[iEmt].col()) return vector<int>();

  vector<int> recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    //if ( !state[i].isCharged() )                           continue;
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

// All charged particles are potential recoilers.
int Dire_fsr_u1new_A2FF::get_nCharged( const Event& state, int radID,
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
int Dire_fsr_u1new_A2FF::set_nCharged( const Event& state) {
  // Find charged particles.
  int nch=0;
  for (int i=0; i < state.size(); ++i) {
    if ( allowedRec(state, i) ) {
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
double Dire_fsr_u1new_A2FF::zSplit(double zMinAbs, double zMaxAbs,
  double m2dip) {
  //return (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
  double res=-1.;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    res = (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
  } else {
    double kappa2 = pT2minL/m2dip;
    double Rz = rndmPtr->flat();
    double tau2 = kappa2/(1.-x20);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;

}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_A2FF::overestimateInt(double zMinAbs,double zMaxAbs,
  double /*pT2Old*/, double m2dip, int /*order*/) {
  //double preFac = symmetryFactor() * gaugeFactor();
  //double wt     = 2. * preFac * 0.5 * ( zMaxAbs - zMinAbs);
  //return wt;
  overInt1 = overInt2 = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor());
  double wt     = 2. * preFac * 0.5 * ( zMaxAbs - zMinAbs);
  overInt1 = wt;
  /*// Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double kappa2 = pT2minL/m2dip;
    double xbef = splitInfo.kinematics()->xBef;
    x20=pow(xbef,200);
    double Imax = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMaxAbs)*(1.-x20) + kappa2);
    double Imin = -1.*preFac*2. / (1.-x20)
                  *log((1.-zMinAbs)*(1.-x20) + kappa2);
    overInt2    = Imax-Imin;
    wt         += overInt2;
  }
*/
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  return wt;
}

// Return kernel for new splitting.
double Dire_fsr_u1new_A2FF::overestimateDiff(double z, double m2dip,
  int /*order*/) {
  //double preFac = symmetryFactor() * gaugeFactor();
  //double wt     = 2. * preFac * 0.5;
  //return wt;
  double preFac = symmetryFactor() * abs(gaugeFactor());
  double wt     = 2. * preFac * 0.5;
/*  // Second part of overestimate, to improve lepton PDF estimate.
  if (!splitInfo.recBef()->isFinal
    && particleDataPtr->isLepton(splitInfo.recBef()->id)) {
    double kappaOld2 = pT2minL/m2dip;
    wt += preFac * 2. / ( (1.-z)*(1-x20) + kappaOld2);
  }*/
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  return wt;

}

// Functions to calculate the kernel from SplitInfo information.
bool Dire_fsr_u1new_A2FF::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), tEvol(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2RadBef(splitInfo.kinematics()->m2RadBef),
    m2Rad(splitInfo.kinematics()->m2RadAft),
    m2Rec(splitInfo.kinematics()->m2Rec),
    m2Emt(splitInfo.kinematics()->m2EmtAft);
  int splitType(splitInfo.type);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(tEvol,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Set number of recoilers.
  //set_nCharged(state);

  double ztilde = z;
  double y = 0.;
  if (splitType > 0) {
    double virt = tEvol + m2RadBef;
    double m2   = m2dip;
    y = virt / m2;
    ztilde = (z -y) / (1-y);
  }


  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac 
      * ((pow(1.-ztilde,2.) + pow(ztilde,2.)) + 2.*sqrt(ztilde * (1.-ztilde)));

  // Correction for massive splittings.
  bool doMassive = (abs(splitType) == 2);

  //double sH = splitInfo.radBef()->m2;

  if (doMassive) {

    double vijk = 1., pipj = 0.;
    // splitType == 2 -> Massive FF
    if (splitType == 2) {
      // Calculate CS variables.
      double virt = tEvol + m2RadBef;
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
      double virt = tEvol + m2RadBef;
      double xCS = m2dip/(m2dip+virt);

      vijk   = 1.; 
      pipj   = m2dip/2. * (1-xCS)/xCS;
      //sH = 2.*pipj + m2Rad + m2Emt;

    }

    // Reset kernel for massive splittings.
    wt = preFac * 1. / vijk * ( pow2(1.-ztilde) + pow2(ztilde) + 2.*sqrt(ztilde * (1.-ztilde))
                                    + m2Emt / ( pipj + m2Emt) );  

  }

  wt *= (tEvol + m2RadBef)/tEvol;
  //double mRes  = particleDataPtr->m0(idZprime);
  //if (sqrt(sH)>mRes && sH < 2.*mRes) wt = 0.;

  // Multiply with z factor
  if (hasHardRadiator) wt *= ztilde;
  else wt *= 1.-ztilde;

  // Set number of recoilers.
  int nch = get_nCharged(state, idZprime, tEvol);
  wt *= (nch>0) ? 1./nch : 0.;

  bool hasME = tEvol > pT2minMECs && doMECs;
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
  adjustKernelVals(wts, state, tEvol);
  storeKernelVals(wts);

  return true;
}

//==========================================================================

// Function to convert ordering variables etc. to the phase space variables
// pT2 (in Dire default definition), z (in Dire default definition), 
// sai (in Dire default definition) and xa (in Dire default definition).

double Dire_fsr_u1new_A2FFres::coupling (double z, double pT2, double m2dip,
  double renormMultFacNow, pair<int,bool> radBef, pair<int,bool> recBef) {
  return alphaEMDark/(2.*M_PI);
}

//--------------------------------------------------------------------------

bool Dire_fsr_u1new_A2FFres::dipoleAboveCutoff( double tin, int radID, int recID,
  double tcut) {
  double t = (signT > 0 ? tin : pow2(2.*sqrt(m2Res)-sqrt(tin)) );
  if (tcut > 0. && t < tcut) return false;
  if (particleDataPtr->isLepton(radID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(radID)  && t < pT2minQ )
    return false;
  if (radID==idZprime && t < pT2minA)  return false;
  if (particleDataPtr->isLepton(recID) && t < pT2minL )
    return false;
  if (particleDataPtr->isQuark(recID)  && t < pT2minQ )
    return false;
  if (recID==idZprime && t < pT2minA)  return false;
  return true;
}

//--------------------------------------------------------------------------

unordered_map<string,double> Dire_fsr_u1new_A2FFres::getPhasespaceVars(
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

double Dire_fsr_u1new_A2FFres::getJacobian( const Event&, PartonSystems*) {

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

bool Dire_fsr_u1new_A2FFres::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.first].id() == idZprime
        && (state[ints.second].isLepton()
         || state[ints.second].idAbs() == 900012));
}

bool Dire_fsr_u1new_A2FFres::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  double doRadiate = ( state[iRadBef].isFinal()
        && state[iRadBef].id() == idZprime
        && allowedRec(state, iRecBef) );
  // Set number of recoilers.
  return doRadiate;
}

vector<pair<int,int> > Dire_fsr_u1new_A2FFres::radAndEmtCols(int iRad, int,
  Event state) {
  vector< pair<int,int> > ret;
  if (state[iRad].id() != idZprime) return ret;
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
int Dire_fsr_u1new_A2FFres::radBefID(int idRadAfter, int idEmtAfter) {
  if ( idRadAfter == idRadAfterSave
    && idEmtAfter ==-idRadAfterSave)
    return idZprime;
  return 0;
}

// All charged particles are potential recoilers.
vector <int> Dire_fsr_u1new_A2FFres::recPositions( const Event& state, int iRad,
  int iEmt) {
  if ( !state[iRad].isFinal() || state[iRad].id() != idRadAfterSave
    || state[iEmt].id() != -idRadAfterSave) return vector<int>();
  if ( state[iRad].col()  != state[iEmt].acol()
    || state[iRad].acol() != state[iEmt].col()) return vector<int>();

  vector<int> recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    //if ( !state[i].isCharged() )                           continue;
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

// All charged particles are potential recoilers.
int Dire_fsr_u1new_A2FFres::get_nCharged( const Event& state, int radID,
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
int Dire_fsr_u1new_A2FFres::set_nCharged( const Event& state) {
  // Find charged particles.
  int nch=0;
  for (int i=0; i < state.size(); ++i) {
    if ( allowedRec(state, i) ) {
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
double Dire_fsr_u1new_A2FFres::zSplit(double /*zMinAbs*/, double /*zMaxAbs*/,
  double /*m2dip*/) {
  double zMinAbs=0.;
  double zMaxAbs=1.;
  return (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
}

// New overestimates, z-integrated versions.
double Dire_fsr_u1new_A2FFres::overestimateInt(double /*zMinAbs*/,double /*zMaxAbs*/,
  double /*pT2Old*/, double /*m2dip*/, int /*order*/) {
  double preFac = symmetryFactor() * gaugeFactor();
  double zMinAbs=0.;
  double zMaxAbs=1.;
  double wt     = 2. * preFac * 0.5 * ( zMaxAbs - zMinAbs);
  wt = 1.;
  return wt;
}

// Return kernel for new splitting.
double Dire_fsr_u1new_A2FFres::overestimateDiff(double /*z*/, double /*m2dip*/,
  int /*order*/) {
  double preFac = symmetryFactor() * gaugeFactor();
  double wt     = 2. * preFac * 0.5;
  wt = 1.;
  return wt;
}

// Functions to calculate the kernel from SplitInfo information.
bool Dire_fsr_u1new_A2FFres::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), t(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);

  double ztilde = z;
  double y = 0.;
  if (splitType > 0) {
    double virt = (signT > 0 ? t : pow2(2.*sqrt(m2Res)-sqrt(t)) );
    y = virt / m2dip;
    ztilde = (z -y) / (1-y);
  }

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * (pow(1.-ztilde,2.) + pow(ztilde,2.));

  // Limit range to close to mass peak.
  if (t>4.*m2Res || t < m2Res) { wt = 0.; }

  // Suppress when sij far away from resonance mass.
  double sij = (signT > 0 ? t : pow2(2.*sqrt(m2Res)-sqrt(t)) );

  // Cut away too small virtualities.
  if ( splitInfo.checkCuts && !dipoleAboveCutoff(t,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  // Multiply with virtuality (would like to include into selection of t,
  // but resulting integral would not be invertable...)
  wt *= sij;
  double width = particleDataPtr->particleDataEntryPtr(idZprime)->resWidth(
    idZprime,sqrt(m2Res));
  wt *= (pow2(sij-m2Res)+pow2(width*mRes)) 
      / (pow2(sij-m2Res)+pow2(width*sij/mRes));


  /*bool hasME = t > pT2minMECs && doMECs;
  //if (!hasME) wt *= sij;
  if (!hasME) wt *= t;
  else {
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
    int colType = (idRad!=21) ? idRad/abs(idRad) : 2;
    vector<int> re = radAndEmt( idRad, colType);
    if (is_isr) in.push_back(re[0]);
    else       out.push_back(re[0]);
    for (int i=1; i < int(re.size()); ++i) out.push_back(re[i]);
    hasME = hasME && fsr->weights->hasME(in,out);
    // Heuristic fudge factor close to peak trying to catch
    // interference enhancements.
    if (hasME) {
      double b = max(0.1, m2Res);
      double exponent = 0.25;
      //double b = max(0.05, m2Res);
      //double exponent = 1.;
      double a = (4*m2Res-b) / (m2Res*pow(3.,exponent));
      //wt *= a*m2Res*pow(sij/m2Res-1,exponent) + b;
      wt *= a*m2Res*pow(t/m2Res-1,exponent) + b;
    }
  }*/

  // Set number of recoilers.
  int nch = get_nCharged(state, idZprime, t);
  wt *= (nch>0) ? 1./nch : 0.;

  // Multiply with z factor
  if (hasHardRadiator) wt *= ztilde;
  else wt *= 1.-ztilde;

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
  adjustKernelVals(wts, state, t);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->QG (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_Q2QA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isQuark()
        && state[ints.second].isCharged()
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_u1new_Q2QA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].isQuark()
        && doU1NEWisrByQ
        && allowedRec(state, iRecBef));
}

int Dire_isr_u1new_Q2QA::kinMap()                 { return 1;}
int Dire_isr_u1new_Q2QA::motherID(int idDaughter) { return idDaughter;} 
int Dire_isr_u1new_Q2QA::sisterID(int)            { return idZprime;}

double Dire_isr_u1new_Q2QA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;

  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_isr_u1new_Q2QA::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_u1new_Q2QA::radBefID(int idRad, int idEmt) {
  if (particleDataPtr->isQuark(idRad) && idEmt == idZprime ) return idRad;
  return 0;
}

pair<int,int> Dire_isr_u1new_Q2QA::radBefCols( int colRadAfter, int acolRadAfter, int,
  int) {
  bool isQuark  = (colRadAfter > 0);
  if (isQuark) return make_pair(colRadAfter,0); 
  return make_pair(0,acolRadAfter); 
}

vector<int>Dire_isr_u1new_Q2QA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( state[iRad].isFinal() || !state[iRad].isQuark()
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( allowedRec(state, i) ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_isr_u1new_Q2QA::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_Q2QA::overestimateInt(double zMinAbs, double,
  double, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappa2 = pT2minQ/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);

  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
    wt *= 2.;
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_u1new_Q2QA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTminChgQ"))/m2dip;
  double kappaOld2 = pT2minQ/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  double told = splitInfo.kinematics()->pT2Old;
  bool hasME = told > pT2minMECs && doMECs;
  if (hasME) wt *= 2.; 
  if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
    wt *= 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_Q2QA::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  wt   =  preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) wt += -preFac * (1.+z);
  if (orderNow < 0 && chargeFac < 0.) wt = 0.;

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
    hasME = hasME && isr->weights->hasME(in,out);
    // Heuristic fudge factor close to peak trying to catch
    // interference enhancements.
    if (hasME) wt *= 2.;
    if (hasME && abs(particleDataPtr->chargeType(splitInfo.radBef()->id))==1)
      wt *= 2.;
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

// Class inheriting from SplittingU1new class.

// SplittingU1new function G->QQ (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_A2QQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isQuark()
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_u1new_A2QQ::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].isQuark()
        && doU1NEWisrByQ
        && allowedRec(state,iRecBef));
}

int Dire_isr_u1new_A2QQ::kinMap()                 { return 1;}
int Dire_isr_u1new_A2QQ::motherID(int)            { return idZprime;} 
int Dire_isr_u1new_A2QQ::sisterID(int idDaughter) { return -idDaughter;} 
double Dire_isr_u1new_A2QQ::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_u1new_A2QQ::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_u1new_A2QQ::radBefID(int, int idEA){ return -idEA;}
pair<int,int> Dire_isr_u1new_A2QQ::radBefCols( int, int, int colEmtAfter,
  int acolEmtAfter) {
  if ( acolEmtAfter > 0 ) return make_pair(acolEmtAfter,0);
  return make_pair(0, colEmtAfter);
}

// Pick z for new splitting.
double Dire_isr_u1new_A2QQ::zSplit(double zMinAbs, double zMaxAbs, double) {
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  double res = zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_A2QQ::overestimateInt(double zMinAbs, double zMaxAbs,
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
double Dire_isr_u1new_A2QQ::overestimateDiff(double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt = preFac 
     * 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_A2QQ::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function Q->AQ (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_Q2AQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].id() == idZprime
        && bools["doQEDshowerByQ"] );
}

bool Dire_isr_u1new_Q2AQ::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].id() == idZprime
        && doU1NEWisrByQ
        && allowedRec(state,iRecBef));
}

int Dire_isr_u1new_Q2AQ::kinMap()                 { return 1;}
int Dire_isr_u1new_Q2AQ::motherID(int)            { return 1;} // Use 1 as dummy 
int Dire_isr_u1new_Q2AQ::sisterID(int)            { return 1;} // Use 1 as dummy
double Dire_isr_u1new_Q2AQ::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_u1new_Q2AQ::symmetryFactor ( int, int )     { return 0.5;}

int Dire_isr_u1new_Q2AQ::radBefID(int, int){ return idZprime;}
pair<int,int> Dire_isr_u1new_Q2AQ::radBefCols( int, int, int, int) {
  return make_pair(0,0); }

// Pick z for new splitting.
double Dire_isr_u1new_Q2AQ::zSplit(double zMinAbs, double, double) {
  double R = rndmPtr->flat();
  double res = pow(zMinAbs,3./4.)
          / ( pow(1. + R*(-1. + pow(zMinAbs,-3./8.)),2./3.)
             *pow(R - (-1. + R)*pow(zMinAbs,3./8.),2.));
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_Q2AQ::overestimateInt(double zMinAbs, double,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2./3. * (8.*(-1. + pow(zMinAbs,-3./8.)));
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_u1new_Q2AQ::overestimateDiff(double z, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2. / pow(z,11./8.);
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_Q2AQ::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2Rec(splitInfo.kinematics()->m2Rec);
  int splitType(splitInfo.type);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  double kappa2 = pT2 / m2dip;
  wt   = preFac * 2.*z / (pow2(z)+kappa2);

  if (orderNow >= 0) wt += preFac*(z-2);

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function L->LA (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_L2LA::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        //&& (state[ints.first].isLepton() || state[ints.first].idAbs() == 900012)
        //&& (state[ints.second].isLepton() || state[ints.second].idAbs() == 900012)
        && (state[ints.first].isLepton() || state[ints.first].idAbs() == 900012 || state[ints.first].idAbs() == 900040)
        && (state[ints.second].isLepton() || state[ints.second].idAbs() == 900012 || state[ints.second].idAbs() == 900040)
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_u1new_L2LA::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        //&& (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012)
        //&& (state[iRecBef].isLepton() || state[iRecBef].idAbs() == 900012)
        && (state[iRadBef].isLepton() || state[iRadBef].idAbs() == 900012 || state[iRadBef].idAbs() == 900040)
        && doU1NEWisrByL
        && allowedRec(state, iRecBef));
}

int Dire_isr_u1new_L2LA::kinMap()                 { return 1;}
int Dire_isr_u1new_L2LA::motherID(int idDaughter) { return idDaughter;} 
int Dire_isr_u1new_L2LA::sisterID(int)            { return idZprime;} 

double Dire_isr_u1new_L2LA::gaugeFactor ( int idRadBef, int idRecBef) {
  double chgRad = particleDataPtr->charge(idRadBef);
  double chgRec = particleDataPtr->charge(idRecBef);
  double charge = -1.*chgRad*chgRec;
  if (!splitInfo.radBef()->isFinal) charge *= -1.;
  if (!splitInfo.recBef()->isFinal) charge *= -1.;
  if (idRadBef != 0 && idRecBef != 0) return charge;
  // Set probability to zero.
  return 0.;
}

double Dire_isr_u1new_L2LA::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_u1new_L2LA::radBefID(int idRad, int idEmt) {
  if ( (particleDataPtr->isLepton(idRad) || abs(idRad) == 900012)
    && idEmt == idZprime ) return idRad;
  return 0;
}


pair<int,int> Dire_isr_u1new_L2LA::radBefCols( int colRadAfter, int acolRadAfter, int,
  int) {
  bool isQuark  = (colRadAfter > 0);
  if (isQuark) return make_pair(colRadAfter,0); 
  return make_pair(0,acolRadAfter); 
}

vector<int>Dire_isr_u1new_L2LA::recPositions(const Event& state, int iRad, int iEmt) {

  vector<int> recs;
  if ( state[iRad].isFinal()
    || !(state[iRad].isLepton() || state[iRad].idAbs() == 900012)
    || state[iEmt].id() != idZprime) return recs;

  // Particles to exclude as recoilers.
  vector<int> iExc(createvector<int>(iRad)(iEmt));
  // Find charged particles.
  for (int i=0; i < state.size(); ++i) {
    if ( find(iExc.begin(), iExc.end(), i) != iExc.end() ) continue;
    if ( allowedRec(state, i) ) {
      if (state[i].isFinal())
        recs.push_back(i);
      if (state[i].mother1() == 1 && state[i].mother2() == 0)
        recs.push_back(i);
      if (state[i].mother1() == 2 && state[i].mother2() == 0)
        recs.push_back(i);
    }
  }
  // Done.
  return recs;

} 

// Pick z for new splitting.
double Dire_isr_u1new_L2LA::zSplit(double zMinAbs, double, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  double res=-1.;
  // Generation of z split between two overestimates.
  if (overInt1 > rndmPtr->flat() * (overInt1+overInt2)) {
    double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
    res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  } else {
    double xbef = splitInfo.kinematics()->xBef;
    double tau2 = kappa2/(1.-xbef);
    double p = pow( 1. + (1-zMinAbs)/tau2, Rz );
    res = 1. - ( p - 1. )*tau2;
  }
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_L2LA::overestimateInt(double zMinAbs, double /*zMaxAbs*/,
  double, double m2dip, int) {
  //double wt = 0.;
  //double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  //wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = overInt2 = 0.;
  double wt = 0.;
  double charge = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  double preFac = symmetryFactor() * abs(charge);
  // Q -> QG, soft part (currently also used for collinear part).
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappa2 = pT2minL/m2dip;
  wt  = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  overInt1 = wt;
  /*// Second part of overestimate.
  double xbef = splitInfo.kinematics()->xBef;
  //double wt2 = 0.1*preFac * 2. / (1.-xbef)
  //     * log (
  //         abs( (kappa2/(1.-xbef))
  //            / (1.- zMinAbs + kappa2/(1.-xbef))));
  //overInt2 = wt2;
  //wt += wt2;
  double Imax = -1.*preFac*2.*0.1 / (1.-xbef)
                *log((1.-zMaxAbs)*(1.-xbef) + kappa2);
  double Imin = -1.*preFac*2.*0.1 / (1.-xbef)
                *log((1.-zMinAbs)*(1.-xbef) + kappa2);
  overInt2    = Imax-Imin;
  wt         += overInt2;*/
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_u1new_L2LA::overestimateDiff(double z, double m2dip, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * abs(gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id));
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTminChgL"))/m2dip;
  double kappaOld2 = pT2minL/m2dip;
  wt  = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  /*// Second part of overestimate.
  double xbef = splitInfo.kinematics()->xBef;
  wt += 0.1*preFac * 2. / ( (1.-z)*(1-xbef) + kappaOld2);*/
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_L2LA::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  double wt = 0.;

  double chargeFac = gaugeFactor(splitInfo.radBef()->id, splitInfo.recBef()->id);
  chargeFac     = forceCouplingFactor(chargeFac, pT2,state);

  double preFac = symmetryFactor() * chargeFac;
  double kappa2 = pT2/m2dip;
  //wt   =  preFac * ( 2.* (1.-z) / ( pow2(1.-z) + kappa2) );
  //if (orderNow >= 0) wt += -preFac * (1.+z);
  wt   =  preFac * ( 2. * z * (1.-z) / ( pow2(1.-z) + kappa2) );
  if (orderNow >= 0) wt += preFac * (1.-z);

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function A->LL (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_A2LL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].isLepton() && state[ints.first].isCharged()
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_u1new_A2LL::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].isLepton()
        && state[iRadBef].isCharged()
        && doU1NEWisrByL
        && allowedRec(state,iRecBef));
}

int Dire_isr_u1new_A2LL::kinMap()                 { return 1;}
int Dire_isr_u1new_A2LL::motherID(int)            { return idZprime;} 
int Dire_isr_u1new_A2LL::sisterID(int idDaughter) { return -idDaughter;} 
double Dire_isr_u1new_A2LL::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_u1new_A2LL::symmetryFactor ( int, int )     { return 1.;}

int Dire_isr_u1new_A2LL::radBefID(int, int idEA){ return -idEA;}
pair<int,int> Dire_isr_u1new_A2LL::radBefCols( int, int, int colEmtAfter,
  int acolEmtAfter) {
  if ( acolEmtAfter > 0 ) return make_pair(acolEmtAfter,0);
  return make_pair(0, colEmtAfter);
}

// Pick z for new splitting.
double Dire_isr_u1new_A2LL::zSplit(double zMinAbs, double zMaxAbs, double) {
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  double res = zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs);
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_A2LL::overestimateInt(double zMinAbs, double zMaxAbs,
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
double Dire_isr_u1new_A2LL::overestimateDiff(double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt = preFac 
     * 2.;
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_A2LL::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

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

// Class inheriting from SplittingU1new class.

// SplittingU1new function L->AL (ISR)

// Return true if this kernel should partake in the evolution.
bool Dire_isr_u1new_L2AL::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool> bools, Settings*, PartonSystems*, BeamParticle*){
  return (!state[ints.first].isFinal()
        && state[ints.first].id() == idZprime
        && bools["doQEDshowerByL"]);
}

bool Dire_isr_u1new_L2AL::canRadiate ( const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*){
  return (!state[iRadBef].isFinal()
        && state[iRadBef].id() == idZprime
        && doU1NEWisrByL
        && allowedRec(state,iRecBef));
}

int Dire_isr_u1new_L2AL::kinMap()                 { return 1;}
int Dire_isr_u1new_L2AL::motherID(int)            { return 1;} // Use 1 as dummy 
int Dire_isr_u1new_L2AL::sisterID(int)            { return 1;} // Use 1 as dummy
double Dire_isr_u1new_L2AL::gaugeFactor ( int, int )        { return 1.;}
double Dire_isr_u1new_L2AL::symmetryFactor ( int, int )     { return 0.5;}

int Dire_isr_u1new_L2AL::radBefID(int, int){ return idZprime;}
pair<int,int> Dire_isr_u1new_L2AL::radBefCols( int, int, int, int) {
  return make_pair(0,0); }

// Pick z for new splitting.
double Dire_isr_u1new_L2AL::zSplit(double zMinAbs, double, double) {
  double R = rndmPtr->flat();
  double res = pow(zMinAbs,3./4.)
          / ( pow(1. + R*(-1. + pow(zMinAbs,-3./8.)),2./3.)
             *pow(R - (-1. + R)*pow(zMinAbs,3./8.),2.));
  return res;
}

// New overestimates, z-integrated versions.
double Dire_isr_u1new_L2AL::overestimateInt(double zMinAbs, double,
  double, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2./3. * (8.*(-1. + pow(zMinAbs,-3./8.)));
  return wt;
}

// Return overestimate for new splitting.
double Dire_isr_u1new_L2AL::overestimateDiff(double z, double, int) {
  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt  = preFac * 2. / pow(z,11./8.);
  return wt;
}

// Return kernel for new splitting.
bool Dire_isr_u1new_L2AL::calc(const Event& state, int orderNow) {
  // DEBUG!
  //return zero();



  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip),
    m2Rec(splitInfo.kinematics()->m2Rec);
  int splitType(splitInfo.type);

  if ( splitInfo.checkCuts && !dipoleAboveCutoff(pT2,
    state[splitInfo.iRadBef].id(), state[splitInfo.iRecBef].id()))
    return zero();

  double wt = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  double kappa2 = pT2 / m2dip;
  wt   = preFac * 2.*z / (pow2(z)+kappa2);

  if (orderNow >= 0) wt += preFac*(z-2.);

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

} // end namespace Pythia8
