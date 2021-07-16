
#include "Dire/SplittingsQCD2.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

namespace Pythia8 {


//==========================================================================

// The SplittingQCD class.

const double CSSplittingQCD::SMALL_TEVOL = 2.0;

//-------------------------------------------------------------------------

void CSSplittingQCD::init() {

  //CA = 3.;
  //TR = 0.5;
  //CF = 4./3.;

  // Colour factors.
  CA = settingsPtr->parm("DireColorQCD:CA") > 0.0
     ? settingsPtr->parm("DireColorQCD:CA") : 3.0;
  CF = settingsPtr->parm("DireColorQCD:CF") > 0.0
     ? settingsPtr->parm("DireColorQCD:CF") : 4./3.;
  TR = settingsPtr->parm("DireColorQCD:TR") > 0.
     ? settingsPtr->parm("DireColorQCD:TR") : 0.5;

  NF_qcd_fsr      = settingsPtr->mode("TimeShower:nGluonToQuark");

  // Parameters of alphaS.
  alphaSvalue        = settingsPtr->parm("SpaceShower:alphaSvalue");
  int alphaSorder    = settingsPtr->mode("SpaceShower:alphaSorder");
  int alphaSnfmax    = settingsPtr->mode("StandardModel:alphaSnfmax");
  bool alphaSuseCMW  = settingsPtr->flag("SpaceShower:alphaSuseCMW");
  // Initialize alphaS.
  alphaS.init( alphaSvalue, alphaSorder, alphaSnfmax, alphaSuseCMW);

  // Set up alphaS
  pTmin              = settingsPtr->parm("SpaceShower:pTmin");
  pTmin              = min(pTmin,settingsPtr->parm("TimeShower:pTmin"));
  usePDFalphas       = settingsPtr->flag("ShowerPDF:usePDFalphas");
  pT2minVariations   = pow2(max(0.,settingsPtr->parm("Variations:pTmin")));

  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id())) ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id())) ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }
  alphaS2pi          = (usePDFalphas && beam != NULL)
                        ? beam->alphaS(pTmin*pTmin) * 0.5/M_PI
                        : (alphaSorder > 0)
                        ? alphaS.alphaS(pTmin*pTmin) *0.5/M_PI
                        :  0.5 * 0.5/M_PI;

  if (!usePDFalphas && alphaSorder == 0) alphaS2pi = alphaSvalue*0.5/M_PI;

  doCorrelations     = settingsPtr->mode("DireTimes:kernelOrder") == 4
                    || settingsPtr->mode("DireSpace:kernelOrder") == 4;

  orderSave = (is_fsr) ? settingsPtr->mode("DireTimes:kernelOrder")
                       : settingsPtr->mode("DireSpace:kernelOrder");

}

//-------------------------------------------------------------------------

// Auxiliary function to get number of flavours.

double CSSplittingQCD::getNF(double pT2) {
  double NF = 6.;

  pT2       = max( pT2, pow2(pTmin) );

  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id())) ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id())) ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }

  // Get current number of flavours.
  if ( !usePDFalphas || beam == NULL) {
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

//--------------------------------------------------------------------------

double CSSplittingQCD::GammaQCD2 (double NF) {
  return (67./18.-pow2(M_PI)/6.)*CA - 10./9.*NF*TR;
}

//--------------------------------------------------------------------------

double CSSplittingQCD::GammaQCD3 (double NF) {
  return 1./4.* (CA*CA*(245./6.-134./27.*pow2(M_PI)+11./45.*pow(M_PI,4)
                        +22./3.*ZETA3)
                +CA*NF*TR*(-418./27.+40./27.*pow2(M_PI)-56./3.*ZETA3)
                +CF*NF*TR*(-55./3.+16.*ZETA3)-16./27.*pow2(NF*TR));
}

//--------------------------------------------------------------------------

double CSSplittingQCD::betaQCD0 (double NF)
  { return 11./6.*CA - 2./3.*NF*TR;}

//--------------------------------------------------------------------------

double CSSplittingQCD::betaQCD1 (double NF)
  { return 17./6.*pow2(CA) - (5./3.*CA+CF)*NF*TR;}

//--------------------------------------------------------------------------

double CSSplittingQCD::betaQCD2 (double NF)
  { return 2857./432.*pow(CA,3)
    + (-1415./216.*pow2(CA) - 205./72.*CA*CF + pow2(CF)/4.) *TR*NF
    + ( 79.*CA + 66.*CF)/108.*pow2(TR*NF); }

//--------------------------------------------------------------------------

// Function to calculate the correct alphaS/2*Pi value, including
// renormalisation scale variations + threshold matching.

double CSSplittingQCD::as2Pi( double pT2, int orderNow, double renormMultFacNow){

  // Get beam for PDF alphaS, if necessary.
  BeamParticle* beam = NULL;
  if (beamAPtr != NULL || beamBPtr != NULL) {
    beam = (beamAPtr != NULL && particleDataPtr->isHadron(beamAPtr->id())) ? beamAPtr
         : (beamBPtr != NULL && particleDataPtr->isHadron(beamBPtr->id())) ? beamBPtr : NULL;
    if (beam == NULL && beamAPtr != 0) beam = beamAPtr;
    if (beam == NULL && beamBPtr != 0) beam = beamBPtr;
  }
  double scale       = pT2 * ( (renormMultFacNow > 0.)
                              ? renormMultFacNow : renormMultFac);
  scale              = max(scale, pow2(pTmin) );

  // Get alphaS(k*pT^2) and subtractions.
  double asPT2pi      = (usePDFalphas && beam != NULL)
                      ? beam->alphaS(scale)  / (2.*M_PI)
                      : alphaS.alphaS(scale) / (2.*M_PI);

  //int order = (orderNow > 0) ? orderNow : correctionOrder;
  int order = (orderNow > -1) ? orderNow : correctionOrder;
  order -= 1;

  // Now find the necessary thresholds so that alphaS can be matched
  // correctly.
  double m2cPhys = (usePDFalphas && beam != NULL) 
                 ? pow2(max(0.,beam->mQuarkPDF(4)))
                 : alphaS.muThres2(4);
  if ( !( (scale > m2cPhys && pT2 < m2cPhys)
       || (scale < m2cPhys && pT2 > m2cPhys) ) ) m2cPhys = -1.;
  double m2bPhys = (usePDFalphas && beam != NULL)
                 ? pow2(max(0.,beam->mQuarkPDF(5)))
                 : alphaS.muThres2(5);
  if ( !( (scale > m2bPhys && pT2 < m2bPhys)
       || (scale < m2bPhys && pT2 > m2bPhys) ) ) m2bPhys = -1.;
  vector<double> scales;
  scales.push_back(scale);
  scales.push_back(pT2);
  if (m2cPhys > 0.) scales.push_back(m2cPhys);
  if (m2bPhys > 0.) scales.push_back(m2bPhys);
  sort( scales.begin(), scales.end());
  if (scale > pT2) reverse(scales.begin(), scales.end());

  double asPT2piCorr  = asPT2pi; 
  for ( int i = 1; i< int(scales.size()); ++i) {
    double NF    = getNF( 0.5*(scales[i]+scales[i-1]) );
    double L     = log( scales[i]/scales[i-1] );
    double subt  = 0.;
    if (order > 0) subt += asPT2piCorr * betaQCD0(NF) * L;
    if (order > 2) subt += pow2( asPT2piCorr ) * ( betaQCD1(NF)*L 
                                   - pow2(betaQCD0(NF)*L) );
    if (order > 4) subt += pow( asPT2piCorr, 3) * ( betaQCD2(NF)*L
                                   - 2.5 * betaQCD0(NF)*betaQCD1(NF)*L*L
                                   + pow( betaQCD0(NF)*L, 3) );
    asPT2piCorr *= 1.0 - subt;
  }

  // Done.
  return asPT2piCorr;

}

//--------------------------------------------------------------------------

// Helper function to calculate dilogarithm.

double CSSplittingQCD::polevl(double x,double* coef,int N ) {
  double ans;
  int i;
  double *p;

  p = coef;
  ans = *p++;
  i = N;
    
  do
    ans = ans * x  +  *p++;
  while( --i );
    
  return ans;
}
  
//--------------------------------------------------------------------------

// Function to calculate dilogarithm.

double CSSplittingQCD::DiLog(double x) {

  static double cof_A[8] = {
    4.65128586073990045278E-5,
    7.31589045238094711071E-3,
    1.33847639578309018650E-1,
    8.79691311754530315341E-1,
    2.71149851196553469920E0,
    4.25697156008121755724E0,
    3.29771340985225106936E0,
    1.00000000000000000126E0,
  };
  static double cof_B[8] = {
    6.90990488912553276999E-4,
    2.54043763932544379113E-2,
    2.82974860602568089943E-1,
    1.41172597751831069617E0,
    3.63800533345137075418E0,
    5.03278880143316990390E0,
    3.54771340985225096217E0,
    9.99999999999999998740E-1,
  };

  if( x >1. ) {
    return -DiLog(1./x)+M_PI*M_PI/3.-0.5*pow2(log(x));
  }

  x = 1.-x;
  double w, y, z;
  int flag;
  if( x == 1.0 )
    return( 0.0 );
  if( x == 0.0 )
    return( M_PI*M_PI/6.0 );
    
  flag = 0;
    
  if( x > 2.0 ) {
    x = 1.0/x;
    flag |= 2;
  }
    
  if( x > 1.5 ) {
    w = (1.0/x) - 1.0;
    flag |= 2;
  }
    
  else if( x < 0.5 ) {
    w = -x;
    flag |= 1;
  }
    
  else
    w = x - 1.0;
    
  y = -w * polevl( w, cof_A, 7) / polevl( w, cof_B, 7 );
    
  if( flag & 1 )
    y = (M_PI * M_PI)/6.0  - log(x) * log(1.0-x) - y;
    
  if( flag & 2 ) {
    z = log(x);
    y = -0.5 * z * z  -  y;
  }
    
  return y;

}

//--------------------------------------------------------------------------

double CSSplittingQCD::softRescaleInt(int order) {
  double rescale = 1.;

  // No inclusive cusp rescaling for differential NLO.
  if (order > 3) return 1.;

  if (order > 0) rescale += alphaS2pi*GammaQCD2(3.);
  if (order > 1) rescale += pow2(alphaS2pi)*GammaQCD3(3.);
  return rescale;
}

//--------------------------------------------------------------------------

double CSSplittingQCD::softRescaleDiff(int order, double pT2,
  double renormMultFacNow) {
  double rescale = 1.;
  // Get alphaS and number of flavours, attach cusp factors.
  double NF      = getNF(pT2 * ( (renormMultFacNow > 0.)
                                ? renormMultFacNow : renormMultFac) );
  double asPT2pi = as2Pi(pT2, order, renormMultFacNow); 

  // No inclusive cusp rescaling for differential NLO.
  if (order > 3) return 1.;

  if (order > 0) rescale += asPT2pi       * GammaQCD2(NF);
  if (order > 1) rescale += pow2(asPT2pi) * GammaQCD3(NF);
  return rescale;
}

//--------------------------------------------------------------------------

vector<int> CSSplittingQCD::sharedColor(const Event& event, int iRad,
  int iRec) {
  vector<int> ret;
  int radCol(event[iRad].col()), radAcl(event[iRad].acol()),
      recCol(event[iRec].col()), recAcl(event[iRec].acol());
  if ( event[iRad].isFinal() && event[iRec].isFinal() ) {
    if (radCol != 0 && radCol == recAcl) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recCol) ret.push_back(radAcl);
  } else if ( event[iRad].isFinal() && !event[iRec].isFinal() ) {
    if (radCol != 0 && radCol == recCol) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recAcl) ret.push_back(radAcl);
  } else if (!event[iRad].isFinal() && event[iRec].isFinal() )  {
    if (radCol != 0 && radCol == recCol) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recAcl) ret.push_back(radAcl);
  } else if (!event[iRad].isFinal() && !event[iRec].isFinal() ) {
    if (radCol != 0 && radCol == recAcl) ret.push_back(radCol);
    if (radAcl != 0 && radAcl == recCol) ret.push_back(radAcl);
  }
  return ret;
}

//--------------------------------------------------------------------------

int CSSplittingQCD::findCol(int col, vector<int> iExc, const Event& event,
    int type) {

  int index = 0;

  int inA = 0, inB = 0;
  for (int i=event.size()-1; i > 0; --i) {
    if ( event[i].mother1() == 1 && event[i].status() != -31
      && event[i].status() != -34) { if (inA == 0) inA = i; }
    if ( event[i].mother1() == 2 && event[i].status() != -31
      && event[i].status() != -34) { if (inB == 0) inB = i; }
  }

  // Search event record for matching colour & anticolour
  for(int n = 0; n < event.size(); ++n) {
    // Skip if this index is excluded.
    if ( find(iExc.begin(), iExc.end(), n) != iExc.end() ) continue;
    if ( event[n].colType() != 0 &&  event[n].status() > 0 ) {
       if ( event[n].acol() == col ) {
        index = -n;
        break;
      }
      if ( event[n].col()  == col ) {
        index =  n;
        break;
      }
    }
  }
  // Search event record for matching colour & anticolour
  for(int n = event.size()-1; n > 0; --n) {
    // Skip if this index is excluded.
    if ( find(iExc.begin(), iExc.end(), n) != iExc.end() ) continue;
    if ( index == 0 && event[n].colType() != 0
      && ( n == inA || n == inB) ) {  // Check incoming
       if ( event[n].acol() == col ) {
        index = -n;
        break;
      }
      if ( event[n].col()  == col ) {
        index =  n;
        break;
      }
    }
  }
  // if no matching colour / anticolour has been found, return false
  if ( type == 1 && index < 0) return abs(index);
  if ( type == 2 && index > 0) return abs(index);
  return 0;

}
//--------------------------------------------------------------------------

// Function to convert ordering variables etc. to the phase space variables
// pT2 (in Dire default definition), z (in Dire default definition), 
// sai (in Dire default definition) and xa (in Dire default definition).

unordered_map<string,double> CSSplittingQCD::getPhasespaceVars( const Event& state,
  PartonSystems*) {

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
  //double xNew(-1.0);
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
    ret.insert(make_pair("m2Dip",m2dip));
    ret.insert(make_pair("pT2",tdire_fi(z,pT2,m2dip)));
    ret.insert(make_pair("pT2Old",splitInfo.kinematics()->pT2Old));
    ret.insert(make_pair("z",zdire_fi(z,pT2,m2dip)));
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
    ret.insert(make_pair("xInAft", xRecBef/z));

  // Initial-final
  } else if (!splitInfo.radBef()->isFinal && splitInfo.recBef()->isFinal ) {
    ret.insert(make_pair("m2Dip",m2dip));
    ret.insert(make_pair("pT2",tdire_if(z,pT2,m2dip)));
    ret.insert(make_pair("pT2Old",splitInfo.kinematics()->pT2Old));
    ret.insert(make_pair("z",zdire_if(z,pT2,m2dip)));
    ret.insert(make_pair("phi",splitInfo.kinematics()->phi));
    ret.insert(make_pair("sai",splitInfo.kinematics()->sai));
    ret.insert(make_pair("xa",splitInfo.kinematics()->xa));
    ret.insert(make_pair("phi2",splitInfo.kinematics()->phi2));
    ret.insert(make_pair("m2RadBef",m2RadBef));
    ret.insert(make_pair("m2Rec",m2Rec));
    ret.insert(make_pair("m2RadAft",m2Rad));
    ret.insert(make_pair("m2EmtAft",m2Emt));
    ret.insert(make_pair("m2EmtAft2",m2Emt2));

    double xRadBef = 2.* state[splitInfo.iRadBef].e()
                       / (beamAPtr->e() + beamBPtr->e());
    ret.insert(make_pair("xInAft", xRadBef/z));

  // Initial-initial
  } else if (!splitInfo.radBef()->isFinal && !splitInfo.recBef()->isFinal ) {
    ret.insert(make_pair("m2Dip",m2dip));
    ret.insert(make_pair("pT2",tdire_ii(z,pT2,m2dip)));
    ret.insert(make_pair("pT2Old",splitInfo.kinematics()->pT2Old));
    ret.insert(make_pair("z",zdire_ii(z,pT2,m2dip)));
    ret.insert(make_pair("phi",splitInfo.kinematics()->phi));
    ret.insert(make_pair("sai",splitInfo.kinematics()->sai));
    ret.insert(make_pair("xa",splitInfo.kinematics()->xa));
    ret.insert(make_pair("phi2",splitInfo.kinematics()->phi2));
    ret.insert(make_pair("m2RadBef",m2RadBef));
    ret.insert(make_pair("m2Rec",m2Rec));
    ret.insert(make_pair("m2RadAft",m2Rad));
    ret.insert(make_pair("m2EmtAft",m2Emt));
    ret.insert(make_pair("m2EmtAft2",m2Emt2));

    double xRadBef = 2.* state[splitInfo.iRadBef].e()
                       / (beamAPtr->e() + beamBPtr->e());
    ret.insert(make_pair("xInAft", xRadBef/z));

  }

  // Done.
  //ret.insert(make_pair("xInAft", xNew));
  return ret;
}

//--------------------------------------------------------------------------

double CSSplittingQCD::getJacobian( const Event&, PartonSystems*) {

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), t(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
    //m2RadBef(splitInfo.kinematics()->m2RadBef),
    //m2Rad(splitInfo.kinematics()->m2RadAft),
    //m2Rec(splitInfo.kinematics()->m2Rec),
    //m2Emt(splitInfo.kinematics()->m2EmtAft),
    //m2Emt2(splitInfo.kinematics()->m2EmtAft2),
    //sai(splitInfo.kinematics()->sai), xa(splitInfo.kinematics()->xa),
    //phi(splitInfo.kinematics()->phi);

  double jacobian = 1.0;
  // Final-final jacobian.
  if ( splitInfo.radBef()->isFinal && splitInfo.recBef()->isFinal ) {
    double ycs = ycs_ff(z,t,m2dip);
    jacobian = 1.-ycs;
  // Final-initial jacobian
  } else if (splitInfo.radBef()->isFinal  && !splitInfo.recBef()->isFinal ) {
  ;
  // Initial-final jacobian
  } else if (!splitInfo.radBef()->isFinal &&  splitInfo.recBef()->isFinal ) {
  ;
  // Initial-initial jacobian
  } else if (!splitInfo.radBef()->isFinal && !splitInfo.recBef()->isFinal ) {
  ;
  }

  return jacobian;
}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2QG::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2QG::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2QG::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2QG::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2QG::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2QG::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2QG::radBefID(int idRA, int) {
  if (particleDataPtr->isQuark(idRA)) return idRA;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2QG::radBefCols(
  int colRadAfter, int, 
  int colEmtAfter, int acolEmtAfter) {
  bool isQuark = (colRadAfter > 0);
  if (isQuark) return make_pair(colEmtAfter,0);
  return make_pair(0,acolEmtAfter);
}

vector <int> CS_fsr_qcd_Q2QG::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
} 

// Pick z for new splitting.
double CS_fsr_qcd_Q2QG::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2QG::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*softRescaleInt(order)*2./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2QG::overestimateDiff(double z, double m2dip, int orderNow) {
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *2. * (1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * softRescaleInt(order)
                * 2./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2QG::calc(const Event& state, int orderNow) { 

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double xcsfi(xcs_fi(z,pT2,m2dip)), zcsfi(zcs_fi(z,pT2,m2dip));

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;
  if (splitType > 0) wt_base_as1 = preFac * 2. / (1.-zcsff*(1.-ycsff));
  else               wt_base_as1 = preFac * 2. / (1.-zcsfi +1.-xcsfi);

  wts.insert( make_pair("base", softRescaleDiff( order, scale2, renormMultFac)
    * wt_base_as1 ) );
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
        * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
        ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
        * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
        ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac ) ));
  }

  // Add collinear term for massless splittings.
  double znow = (splitType>0) ? zcsff : zcsfi; 
  if (order >= 0) {
    wt_base_as1 += -preFac * ( 1.+znow );
    for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
      it->second +=  -preFac * ( 1.+znow );
  }

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2GQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2GQ::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2GQ::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2GQ::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2GQ::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2GQ::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2GQ::radBefID(int idRad, int idEmt) {
  if (idRad == 21 && particleDataPtr->isQuark(idEmt)) return idEmt;
  if (idEmt == 21 && particleDataPtr->isQuark(idRad)) return idRad;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2GQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colE  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colEmtAfter : colRadAfter; 
  int colR  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colRadAfter : colEmtAfter; 
  int acolR = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? acolRadAfter : acolEmtAfter; 

  bool isQuark = (colE > 0);
  if (isQuark) return make_pair(colR,0);
  return make_pair(0,acolR);
}

vector <int> CS_fsr_qcd_Q2GQ::recPositions( const Event& state, int iRad, int iEmt) {

  // For Q->GQ, swap radiator and emitted, since we now have to trace the
  // radiator's colour connections.
  if ( state[iEmt].idAbs() < 20 && state[iRad].id() == 21) swap( iRad, iEmt);

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_Q2GQ::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2GQ::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*2./(1.-ymin)*log(1./ymin);
  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  if ( ( correctionOrder > 0 && correctionOrder <= 2 )
    || ( orderNow > -1       && orderNow <= 2 ) )
    wt *= softRescaleInt(order);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2GQ::overestimateDiff(double z, double m2dip, int orderNow) {
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * 2./(1.-z*(1.-ymin));
  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  if ( ( correctionOrder > 0 && correctionOrder <= 2 )
    || ( orderNow > -1       && orderNow <= 2 ) )
    wt *= softRescaleInt(order);
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2GQ::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double xcsfi(xcs_fi(z,pT2,m2dip)), zcsfi(zcs_fi(z,pT2,m2dip));

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;
  if (splitType > 0) wt_base_as1 = preFac * 2. / (1.-zcsff*(1.-ycsff));
  else               wt_base_as1 = preFac * 2. / (1.-zcsfi +1.-xcsfi);

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown",  wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp",  wt_base_as1 ));
  }

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  bool doRescale = ( ( correctionOrder > 0 && correctionOrder <= 2 )
                  || ( orderNow > -1       && orderNow <= 2 ) );
  if (doRescale) {
  wts["base"] *= softRescaleDiff( order, scale2, renormMultFac);
  if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
    wts["Variations:muRfsrDown"] *= softRescaleDiff( order, scale2,
      (scale2 > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac
      : renormMultFac);
  if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
    wts["Variations:muRfsrUp"] *= softRescaleDiff( order, scale2,
      (scale2 > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac
      : renormMultFac);
  }

  // Add collinear term for massless splittings.
  double znow = (splitType>0) ? zcsff : zcsfi; 
  if (order >= 0) {
    for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
      it->second += -preFac * ( 1.+znow );
     wt_base_as1 += -preFac * ( 1.+znow );
  }

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG1::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG1::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG1::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG1::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG1::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG1::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG1::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG1::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG1::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG1::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, R );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  double res  = splitInfo.recBef()->isFinal
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG1::overestimateInt(double, double,
  double, double m2dip, int orderNow) {

  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //double wt   = splitInfo.recBef()->isFinal
  double wt   = preFac* softRescaleInt(order) * 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG1::overestimateDiff(double z, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *(1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //double wt   = splitInfo.recBef()->isFinal
  double wt   = preFac * softRescaleInt(order)
                * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG1::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double xcsfi(xcs_fi(z,pT2,m2dip)), zcsfi(zcs_fi(z,pT2,m2dip));
  double znow = (splitType > 0) ? zcsff : zcsfi;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.
  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.

  if (splitType > 0) wt_base_as1 = preFac * 1./(1.-zcsff*(1.-ycsff));
  else               wt_base_as1 = preFac * 1./(1.-zcsfi +1.-xcsfi);

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations) 
      ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac) ));
  }

  // Add collinear term for massless splittings.
  double coll = (order >= 0)
                ? preFac * ( -1. + 0.5 * znow*(1.-znow) ) : 0.;
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    it->second += coll;
  wt_base_as1 += coll;

  // Multiply with z to project out part where emitted gluon is soft.
  // (the radiator is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG2::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG2::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG2::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG2::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG2::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG2::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG2::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG2::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG2::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  // Find partons connected via radiator colour line.
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }

  // Find partons connected via radiator anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG2::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
  //double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //kappaMin2 = pow4(kappaMin2);
  //double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, R );
  //double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG2::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //kappaMin2 = pow4(kappaMin2);
  //double wt        = preFac * softRescaleInt(order)
  //                   *0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac* softRescaleInt(order)
                * 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG2::overestimateDiff(double z, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //kappaMin2 = pow4(kappaMin2);
  //double wt        = preFac * softRescaleInt(order)
  //                   *(1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * softRescaleInt(order)
                * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG2::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double xcsfi(xcs_fi(z,pT2,m2dip)), zcsfi(zcs_fi(z,pT2,m2dip));
  double znow = (splitType > 0) ? zcsff : zcsfi;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.
  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.
  if (splitType > 0) wt_base_as1 = preFac * 1./(1.-zcsff*(1.-ycsff));
  else               wt_base_as1 = preFac * 1./(1.-zcsfi +1.-xcsfi);

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations) 
      ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac) ));
  }

  // Add collinear term for massless splittings.
  double coll = (order >= 0)
                ? preFac * ( -1. + 0.5 * znow*(1.-znow) ) : 0.;
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    it->second += coll;
  wt_base_as1 += coll;

  // Multiply with 1-z to project out part where radiating gluon is soft.
  // (the emission is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->QQ (FSR)

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2QQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2QQ::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

double CS_fsr_qcd_G2QQ::gaugeFactor ( int, int )        { return NF_qcd_fsr*TR;}
double CS_fsr_qcd_G2QQ::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2QQ::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2QQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int col  = (colRadAfter  > 0) ? colRadAfter  : colEmtAfter;
  int acol = (acolRadAfter > 0) ? acolRadAfter : acolEmtAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2QQ::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;

  // Find partons connected via emitted colour line.
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2QQ::zSplit(double zMinAbs, double zMaxAbs, double) {
  return (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2QQ::overestimateInt(double zMinAbs,double zMaxAbs,
  double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = 2.*preFac * 0.5 * ( zMaxAbs - zMinAbs);
  if (!splitInfo.recBef()->isFinal) wt *= 2.;
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2QQ::overestimateDiff(double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = 2.*preFac * 0.5;
  if (!splitInfo.recBef()->isFinal) wt *= 2.;
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2QQ::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double /*ycsff(ycs_ff(z,pT2,m2dip)),*/ zcsff(zcs_ff(z,pT2,m2dip));
  double /*xcsfi(xcs_fi(z,pT2,m2dip)),*/ zcsfi(zcs_fi(z,pT2,m2dip));
  double znow = (splitType > 0) ? zcsff : zcsfi;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;

  // Uncorrelated g->qq splitting.
  wt_base_as1 = preFac * ( pow(1.-znow,2.) + pow(znow,2.) );

  // Switch off splitting when only considering double log contributions.
  if (order == -1) wt_base_as1 = 0.0;

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1 ));
  }

  // Multiply with z to project out part where emitted quark is soft,
  // and antiquark is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (idRadAfterSave> 0) ? znow : 1.-znow;    
  wt_base_as1 *= (idRadAfterSave> 0) ? znow : 1.-znow;

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}









//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2QG_soft::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2QG_soft::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2QG_soft::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2QG_soft::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2QG_soft::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2QG_soft::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2QG_soft::radBefID(int idRA, int) {
  if (particleDataPtr->isQuark(idRA)) return idRA;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2QG_soft::radBefCols(
  int colRadAfter, int, 
  int colEmtAfter, int acolEmtAfter) {
  bool isQuark = (colRadAfter > 0);
  if (isQuark) return make_pair(colEmtAfter,0);
  return make_pair(0,acolEmtAfter);
}

vector <int> CS_fsr_qcd_Q2QG_soft::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
} 

// Pick z for new splitting.
double CS_fsr_qcd_Q2QG_soft::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2QG_soft::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*softRescaleInt(order)*2./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2QG_soft::overestimateDiff(double z, double m2dip, int orderNow) {
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * softRescaleInt(order)
//                     *2. * (1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * softRescaleInt(order)
                * 2./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2QG_soft::calc(const Event& state, int orderNow) { 

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out Q->QQ,
  // i.e. the gluon is soft and the quark is identified.
  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * (2. / (1.-zcsff*(1.-ycsff))-2);

  wts.insert( make_pair("base", softRescaleDiff( order, scale2, renormMultFac)
    * wt_base_as1 ) );
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
        * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
        ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
        * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
        ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac ) ));
  }

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2GQ_soft::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2GQ_soft::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2GQ_soft::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2GQ_soft::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2GQ_soft::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2GQ_soft::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2GQ_soft::radBefID(int idRad, int idEmt) {
  if (idRad == 21 && particleDataPtr->isQuark(idEmt)) return idEmt;
  if (idEmt == 21 && particleDataPtr->isQuark(idRad)) return idRad;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2GQ_soft::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colE  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colEmtAfter : colRadAfter; 
  int colR  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colRadAfter : colEmtAfter; 
  int acolR = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? acolRadAfter : acolEmtAfter; 

  bool isQuark = (colE > 0);
  if (isQuark) return make_pair(colR,0);
  return make_pair(0,acolR);
}

vector <int> CS_fsr_qcd_Q2GQ_soft::recPositions( const Event& state, int iRad, int iEmt) {

  // For Q->GQ, swap radiator and emitted, since we now have to trace the
  // radiator's colour connections.
  if ( state[iEmt].idAbs() < 20 && state[iRad].id() == 21) swap( iRad, iEmt);

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_Q2GQ_soft::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2GQ_soft::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*2./(1.-ymin)*log(1./ymin);
  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  if ( ( correctionOrder > 0 && correctionOrder <= 2 )
    || ( orderNow > -1       && orderNow <= 2 ) )
    wt *= softRescaleInt(order);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2GQ_soft::overestimateDiff(double z, double m2dip, int orderNow) {
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double wt        = preFac * 2.* (1.-z) / ( pow2(1.-z) + kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * 2./(1.-z*(1.-ymin));
  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  if ( ( correctionOrder > 0 && correctionOrder <= 2 )
    || ( orderNow > -1       && orderNow <= 2 ) )
    wt *= softRescaleInt(order);
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2GQ_soft::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with 1-z to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * (2. / (1.-zcsff*(1.-ycsff)) - 2.);

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown",  wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp",  wt_base_as1 ));
  }

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Rescale with soft cusp term only if NLO corrections are absent.
  // This choice is purely heuristical to improve LEP description.
  bool doRescale = ( ( correctionOrder > 0 && correctionOrder <= 2 )
                  || ( orderNow > -1       && orderNow <= 2 ) );
  if (doRescale) {
  wts["base"] *= softRescaleDiff( order, scale2, renormMultFac);
  if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
    wts["Variations:muRfsrDown"] *= softRescaleDiff( order, scale2,
      (scale2 > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac
      : renormMultFac);
  if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
    wts["Variations:muRfsrUp"] *= softRescaleDiff( order, scale2,
      (scale2 > pT2minVariations) ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac
      : renormMultFac);
  }

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG1_soft::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG1_soft::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG1_soft::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG1_soft::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG1_soft::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG1_soft::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG1_soft::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG1_soft::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG1_soft::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG1_soft::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG1_soft::overestimateInt(double, double,
  double, double m2dip, int orderNow) {

  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac* softRescaleInt(order) * 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG1_soft::overestimateDiff(double z, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * softRescaleInt(order)
                * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG1_soft::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * (1./(1.-zcsff*(1.-ycsff))-1.);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations) 
      ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac) ));
  }

  // Multiply with z to project out part where emitted gluon is soft.
  // (the radiator is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG2_soft::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG2_soft::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG2_soft::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG2_soft::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG2_soft::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG2_soft::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG2_soft::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG2_soft::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG2_soft::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  // Find partons connected via radiator colour line.
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }

  // Find partons connected via radiator anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG2_soft::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG2_soft::overestimateInt(double, double,
  double, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac* softRescaleInt(order)
                * 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG2_soft::overestimateDiff(double z, double m2dip, int orderNow) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * softRescaleInt(order)
                * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG2_soft::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double ycsff(ycs_ff(z,pT2,m2dip)), zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.
  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * (1./(1.-zcsff*(1.-ycsff))-1.);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations) 
      ? settingsPtr->parm("Variations:muRfsrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRfsrUp")*renormMultFac : renormMultFac) ));
  }

  // Multiply with 1-z to project out part where radiating gluon is soft.
  // (the emission is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->QG (FSR)

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2QG_coll::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2QG_coll::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2QG_coll::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2QG_coll::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2QG_coll::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2QG_coll::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2QG_coll::radBefID(int idRA, int) {
  if (particleDataPtr->isQuark(idRA)) return idRA;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2QG_coll::radBefCols(
  int colRadAfter, int, 
  int colEmtAfter, int acolEmtAfter) {
  bool isQuark = (colRadAfter > 0);
  if (isQuark) return make_pair(colEmtAfter,0);
  return make_pair(0,acolEmtAfter);
}

vector <int> CS_fsr_qcd_Q2QG_coll::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
} 

// Pick z for new splitting.
double CS_fsr_qcd_Q2QG_coll::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2QG_coll::overestimateInt(double, double,
  double, double m2dip, int) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*2./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2QG_coll::overestimateDiff(double z, double m2dip, int) {
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac
                * 2./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2QG_coll::calc(const Event& state, int orderNow) { 

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff; 

  // Calculate kernel.
  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * ( 1.-znow );

  wts.insert( make_pair("base", wt_base_as1));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1));
  }

  // Now multiply with z to project out Q->QG,
  // i.e. the gluon is soft and the quark is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->GQ (FSR)
// At leading order, this can be combined with Q->QG because of symmetry. Since
// this is no longer possible at NLO, we keep the kernels separately.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_Q2GQ_coll::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_fsr_qcd_Q2GQ_coll::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_fsr_qcd_Q2GQ_coll::motherID(int idDaughter) { return idDaughter;}
int CS_fsr_qcd_Q2GQ_coll::sisterID(int)            { return 21;}
double CS_fsr_qcd_Q2GQ_coll::gaugeFactor ( int, int )        { return CF;}
double CS_fsr_qcd_Q2GQ_coll::symmetryFactor ( int, int )     { return 1.;}

int CS_fsr_qcd_Q2GQ_coll::radBefID(int idRad, int idEmt) {
  if (idRad == 21 && particleDataPtr->isQuark(idEmt)) return idEmt;
  if (idEmt == 21 && particleDataPtr->isQuark(idRad)) return idRad;
  return 0;
}

pair<int,int> CS_fsr_qcd_Q2GQ_coll::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colE  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colEmtAfter : colRadAfter; 
  int colR  = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? colRadAfter : colEmtAfter; 
  int acolR = (colEmtAfter*acolEmtAfter == 0 && colRadAfter*acolRadAfter != 0)
            ? acolRadAfter : acolEmtAfter; 

  bool isQuark = (colE > 0);
  if (isQuark) return make_pair(colR,0);
  return make_pair(0,acolR);
}

vector <int> CS_fsr_qcd_Q2GQ_coll::recPositions( const Event& state, int iRad, int iEmt) {

  // For Q->GQ, swap radiator and emitted, since we now have to trace the
  // radiator's colour connections.
  if ( state[iEmt].idAbs() < 20 && state[iRad].id() == 21) swap( iRad, iEmt);

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_Q2GQ_coll::zSplit(double, double, double m2dip) {
  double Rz        = rndmPtr->flat();
//  double kappaMin2 = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
//  kappaMin2 = pow4(kappaMin2);
//  double p         = pow( 1. + pow2(1-zMinAbs)/kappaMin2, Rz );
//  double res       = 1. - sqrt( p - 1. )*sqrt(kappaMin2);
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-Rz));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_Q2GQ_coll::overestimateInt(double, double,
  double, double m2dip, int) {
  // Q -> QG, soft part (currently also used for collinear part).
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac*2./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_Q2GQ_coll::overestimateDiff(double z, double m2dip, int) {
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * 2./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_Q2GQ_coll::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff; 

  // Calculate kernel.
  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * ( 1.-znow );

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown",  wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp",  wt_base_as1 ));
  }

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  // Now multiply with (1-z) to project out Q->GQ,
  // i.e. the quark is soft and the gluon is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG1_coll::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG1_coll::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG1_coll::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG1_coll::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG1_coll::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG1_coll::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG1_coll::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG1_coll::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG1_coll::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG1_coll::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG1_coll::overestimateInt(double, double,
  double, double m2dip, int) {

  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  //double wt   = splitInfo.recBef()->isFinal
  double wt   = preFac* 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG1_coll::overestimateDiff(double z, double m2dip, int) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac
                * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG1_coll::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  // Note: We are calculating the z <--> 1-z symmetrised kernel here,
  // and later multiply with z to project out one part.
  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * 0.5 * znow*(1.-znow);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  wts.insert( make_pair("base", wt_base_as1));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1));
  }

  // Multiply with z to project out part where emitted gluon is soft.
  // (the radiator is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    it->second *= znow;    

  wt_base_as1 *= znow;
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (FSR)
// We now split this kernel into two pieces, as the soft emitted gluon
// is identified as NLO. Thus, it is good to have two kernels for g -> g1 g2,
// one where g1 is soft, and one where g2 is soft.

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2GG2_coll::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2GG2_coll::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_fsr_qcd_G2GG2_coll::motherID(int)            { return 21;}
int CS_fsr_qcd_G2GG2_coll::sisterID(int)            { return 21;}
double CS_fsr_qcd_G2GG2_coll::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_fsr_qcd_G2GG2_coll::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2GG2_coll::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2GG2_coll::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == acolEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter == colRemove)
                ? colEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? acolEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2GG2_coll::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  // Find partons connected via radiator colour line.
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }

  // Find partons connected via radiator anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2GG2_coll::zSplit(double, double, double m2dip) {
  // Just pick according to soft.
  double R         = rndmPtr->flat();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double res  = 1./(1.-ymin)*(1.-pow(ymin,1.-R));
  return res;
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2GG2_coll::overestimateInt(double, double,
  double, double m2dip, int) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * 1./(1.-ymin)*log(1./ymin);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2GG2_coll::overestimateDiff(double z, double m2dip, int) {
  // Overestimate by soft
  double preFac    = symmetryFactor() * gaugeFactor();
  double ymin = pow2(settingsPtr->parm("TimeShower:pTmin"))/m2dip;
  double wt   = preFac * 1./(1.-z*(1.-ymin));
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2GG2_coll::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  // Calculate kernel.
  unordered_map<string,double> wts;
  double wt_base_as1 = preFac * 0.5 * znow*(1.-znow);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  wts.insert( make_pair("base", wt_base_as1));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1));
  }

  // Multiply with 1-z to project out part where radiating gluon is soft.
  // (the emission is identified)
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (1-znow);    

  wt_base_as1 *= (1-znow);
  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->QQ (FSR)

// Return true if this kernel should partake in the evolution.
bool CS_fsr_qcd_G2QQ_coll::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_fsr_qcd_G2QQ_coll::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

double CS_fsr_qcd_G2QQ_coll::gaugeFactor ( int, int )        { return NF_qcd_fsr*TR;}
double CS_fsr_qcd_G2QQ_coll::symmetryFactor ( int, int )     { return 0.5;}

int CS_fsr_qcd_G2QQ_coll::radBefID(int, int){ return 21;}
pair<int,int> CS_fsr_qcd_G2QQ_coll::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int col  = (colRadAfter  > 0) ? colRadAfter  : colEmtAfter;
  int acol = (acolRadAfter > 0) ? acolRadAfter : acolEmtAfter;
  return make_pair(col,acol);
}

vector <int> CS_fsr_qcd_G2QQ_coll::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;

  // Find partons connected via emitted colour line.
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_fsr_qcd_G2QQ_coll::zSplit(double zMinAbs, double zMaxAbs, double) {
  return (zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs));
}

// New overestimates, z-integrated versions.
double CS_fsr_qcd_G2QQ_coll::overestimateInt(double zMinAbs,double zMaxAbs,
  double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = 2.*preFac * 0.5 * ( zMaxAbs - zMinAbs);
  return wt;
}

// Return overestimate for new splitting.
double CS_fsr_qcd_G2QQ_coll::overestimateDiff(double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = 2.*preFac * 0.5;
  return wt;
}

// Return kernel for new splitting.
bool CS_fsr_qcd_G2QQ_coll::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  double zcsff(zcs_ff(z,pT2,m2dip));
  double znow = zcsff;

  double preFac = symmetryFactor() * gaugeFactor();
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;

  // Uncorrelated g->qq splitting.
  wt_base_as1 = preFac * ( pow(1.-znow,2.) + pow(znow,2.) );

  // Switch off splitting when only considering double log contributions.
  if (order == -1) wt_base_as1 = 0.0;

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRfsrDown") != 1.)
      wts.insert( make_pair("Variations:muRfsrDown", wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRfsrUp")   != 1.)
      wts.insert( make_pair("Variations:muRfsrUp", wt_base_as1 ));
  }

  // Multiply with z to project out part where emitted quark is soft,
  // and antiquark is identified.
  for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it )
    it->second *= (idRadAfterSave> 0) ? znow : 1.-znow;    
  wt_base_as1 *= (idRadAfterSave> 0) ? znow : 1.-znow;

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}































































//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->QG (ISR)

// Return true if this kernel should partake in the evolution.
bool CS_isr_qcd_Q2QG::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return (!state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_isr_qcd_Q2QG::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( !state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_isr_qcd_Q2QG::motherID(int idDaughter) { return idDaughter;} 
int CS_isr_qcd_Q2QG::sisterID(int)            { return 21;} 
double CS_isr_qcd_Q2QG::gaugeFactor ( int, int )        { return CF;}
double CS_isr_qcd_Q2QG::symmetryFactor ( int, int )     { return 1.;}

int CS_isr_qcd_Q2QG::radBefID(int idRA, int) { 
  if (particleDataPtr->isQuark(idRA)) return idRA;
  return 0;
  //return idRA;
}
pair<int,int> CS_isr_qcd_Q2QG::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  bool isQuark  = (colRadAfter > 0);
  int colRemove = (colRadAfter == colEmtAfter)
                ? colRadAfter : 0;
  int col       = (colRadAfter  == colRemove)
                ? acolEmtAfter : colRadAfter;
  if (isQuark) return make_pair(col,0); 
  colRemove = (acolRadAfter == acolEmtAfter)
                ? acolRadAfter : 0;
  int acol      = (acolRadAfter  == colRemove)
                ? colEmtAfter : acolRadAfter;
  return make_pair(0,acol); 
}

vector <int> CS_isr_qcd_Q2QG::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == colEmt) ? colEmt
                : (acolRad > 0 && acolEmt == acolRad) ? acolEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
} 

// Pick z for new splitting.
double CS_isr_qcd_Q2QG::zSplit(double zMinAbs, double zMaxAbs, double m2dip) {
  double Rz = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  //kappa2 = pow4(kappa2);
  //double p = pow( 1. + pow2(1-zMinAbs)/kappa2, Rz );
  //double res = 1. - sqrt( p - 1. )*sqrt(kappa2);
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  double res = 1. + vmin - pow(1.-zMinAbs+vmin,1-Rz)*pow(1.-zMaxAbs+vmin,Rz);
  return res;
}

// New overestimates, z-integrated versions.
double CS_isr_qcd_Q2QG::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double m2dip, int orderNow) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  //kappa2 = pow4(kappa2);
  //wt  = preFac * softRescaleInt(order)
  //    * 2. * 0.5 * log( 1. + pow2(1.-zMinAbs)/kappa2);
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  wt  = preFac * softRescaleInt(order)
      * 2. * log( (1.-zMinAbs+vmin)/(1.-zMaxAbs+vmin) );
  return wt;
}

// Return overestimate for new splitting.
double CS_isr_qcd_Q2QG::overestimateDiff(double z, double m2dip, int orderNow) {
  double wt        = 0.;
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  //kappaOld2 = pow4(kappaOld2);
  //wt  = preFac * softRescaleInt(order)
  //    * 2.* (1.-z) / ( pow2(1.-z) + kappaOld2);
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  wt  = preFac * softRescaleInt(order)
      * 2. / ( 1. - z + vmin);
  return wt;
}

// Return kernel for new splitting.
bool CS_isr_qcd_Q2QG::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ucsif(ucs_if(z,pT2,m2dip)), xcsif(xcs_if(z,pT2,m2dip));
  double vcsii(vcs_ii(z,pT2,m2dip)), xcsii(xcs_ii(z,pT2,m2dip));
  double xnow = (splitType > 0) ? xcsif : xcsii;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 = 0.;
  if (splitType > 0) wt_base_as1 = preFac * 2. / (1.-xcsif+ucsif);
  else               wt_base_as1 = preFac * 2. / (1.-xcsii+vcsii);

  if (order >= 0) wt_base_as1 += -preFac*(1.+xnow);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRisrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRisrUp")*renormMultFac : renormMultFac) ));
  }

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (ISR)

// Return true if this kernel should partake in the evolution.
bool CS_isr_qcd_G2GG1::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return (!state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_isr_qcd_G2GG1::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( !state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_isr_qcd_G2GG1::motherID(int)            { return 21;} 
int CS_isr_qcd_G2GG1::sisterID(int)            { return 21;} 
double CS_isr_qcd_G2GG1::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_isr_qcd_G2GG1::symmetryFactor ( int, int )     { return 0.5;}

int CS_isr_qcd_G2GG1::radBefID(int idRA, int){
  if (idRA == 21) return 21;
  return 0;
}
pair<int,int> CS_isr_qcd_G2GG1::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == colEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter  == colRemove)
                ? acolEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? colEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_isr_qcd_G2GG1::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == colEmt) ? colEmt
                : (acolRad > 0 && acolEmt == acolRad) ? acolEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_isr_qcd_G2GG1::zSplit(double zMinAbs, double zMaxAbs, double m2dip) {
  double R = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  // Pick according to soft + 1/z
  //double res = (-2.*pow(kappa2,R)*pow(zMinAbs,2.*R) +
  //           sqrt(4.*pow(kappa2,2.*R)
  //                 *pow(zMinAbs,4.*R)
  //              + 4.*(pow(kappa2,R) + pow(kappa2,1. + R))
  //                 *pow(zMinAbs,2.*R)
  //                 *(-(pow(kappa2,R)*pow(zMinAbs,2.*R))
  //                   + kappa2
  //                     *pow(1. + kappa2 - 2.*zMinAbs + pow(zMinAbs,2.),R))))
  //        / (2.*(-(pow(kappa2,R)*pow(zMinAbs,2.*R))
  //               + kappa2
  //                 *pow(1. + kappa2 - 2.*zMinAbs + pow(zMinAbs,2.),R)));
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  double res = 1. + vmin - pow(1.-zMinAbs+vmin,1-R)*pow(1.-zMaxAbs+vmin,R);
  return res;
}

// New overestimates, z-integrated versions.
double CS_isr_qcd_G2GG1::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double m2dip, int orderNow) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/z
  //wt   = preFac * softRescaleInt(order)
  //     *0.5*( log(1./pow2(zMinAbs) + pow2(1.-zMinAbs)/(kappa2*pow2(zMinAbs))));
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  wt  = preFac * softRescaleInt(order)
        * log( (1.-zMinAbs+vmin)/(1.-zMaxAbs+vmin) );
  return wt;
}

// Return overestimate for new splitting.
double CS_isr_qcd_G2GG1::overestimateDiff(double z, double m2dip, int orderNow) {
  double wt        = 0.;
  double preFac    = symmetryFactor() * gaugeFactor();
  //int order        = (orderNow > 0) ? orderNow : correctionOrder;
  int order        = (orderNow > -1) ? orderNow : correctionOrder;
  //double kappaOld2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  // Overestimate by soft + 1/z
  //wt  = preFac * softRescaleInt(order)
  //    * ((1.-z) / ( pow2(1.-z) + kappaOld2) + 1./z);
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  wt  = preFac * softRescaleInt(order) * 1. / ( 1. - z + vmin);
  return wt;
}

// Return kernel for new splitting.
bool CS_isr_qcd_G2GG1::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ucsif(ucs_if(z,pT2,m2dip)), xcsif(xcs_if(z,pT2,m2dip));
  double vcsii(vcs_ii(z,pT2,m2dip)), xcsii(xcs_ii(z,pT2,m2dip));
  double xnow = (splitType > 0) ? xcsif : xcsii;
  double vnow = (splitType > 0) ? ucsif : vcsii;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  //double wt_base_as1 = preFac * ( (1.-z) / (pow2(1.-z)+kappa2) );
  double wt_base_as1 = 0.;
  if (splitType > 0) wt_base_as1 = preFac * 1. / (1.-xcsif+ucsif);
  else               wt_base_as1 = preFac * 1. / (1.-xcsii+vcsii);

  // Calculate argument of alphaS.
  double scale2 = couplingScale2 ( z, pT2, m2dip,
    make_pair (splitInfo.radBef()->id, splitInfo.radBef()->isFinal),
    make_pair (splitInfo.recBef()->id, splitInfo.recBef()->isFinal));
  if (scale2 < 0.) scale2 = pT2;

  wts.insert( make_pair("base", wt_base_as1
    * softRescaleDiff( order, scale2, renormMultFac) ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRisrDown")*renormMultFac : renormMultFac) ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt_base_as1
      * softRescaleDiff( order, scale2, (scale2 > pT2minVariations)
      ? settingsPtr->parm("Variations:muRisrUp")*renormMultFac : renormMultFac) ));
  }

  if (order >= 0) {
    //for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
    //  it->second += preFac * 0.5 * ( z / ( pow2(z) + kappa2) - 1. ) - preFac;
    //wt_base_as1 += preFac * 0.5 * ( z / ( pow2(z) + kappa2) - 1. ) - preFac;
    for ( unordered_map<string,double>::iterator it = wts.begin(); it != wts.end(); ++it)
      it->second += preFac * 0.5 * ( 1. / (xnow + vnow*(1-xnow)/xnow) - 1. ) - preFac;
    wt_base_as1 += preFac * 0.5 * ( 1. / (xnow + vnow*(1-xnow)/xnow) - 1. ) - preFac;
  }

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->GG (ISR)

// Return true if this kernel should partake in the evolution.
bool CS_isr_qcd_G2GG2::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return (!state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_isr_qcd_G2GG2::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( !state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

int CS_isr_qcd_G2GG2::motherID(int)            { return 21;} 
int CS_isr_qcd_G2GG2::sisterID(int)            { return 21;} 
double CS_isr_qcd_G2GG2::gaugeFactor ( int, int )        { return 2.*CA;}
double CS_isr_qcd_G2GG2::symmetryFactor ( int, int )     { return 0.5;}

int CS_isr_qcd_G2GG2::radBefID(int idRA, int){
 if (idRA==21) return 21;
 return 0;
}
pair<int,int> CS_isr_qcd_G2GG2::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int colRemove = (colRadAfter == colEmtAfter)
                ? colRadAfter : acolRadAfter;
  int col       = (colRadAfter  == colRemove)
                ? acolEmtAfter : colRadAfter;
  int acol      = (acolRadAfter == colRemove)
                ? colEmtAfter : acolRadAfter;
  return make_pair(col,acol);
}

vector <int> CS_isr_qcd_G2GG2::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == colEmt) ? colEmt
                : (acolRad > 0 && acolEmt == acolRad) ? acolEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_isr_qcd_G2GG2::zSplit(double zMinAbs, double zMaxAbs, double m2dip) {
  double R      = rndmPtr->flat();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;

  // For small values of pT, increase overestimate to avoid large weights.
  //double tOld(splitInfo.kinematics()->pT2Old);
  //if (tOld > 0. && tOld < SMALL_TEVOL) kappa2 *= sqrt(kappa2);

  // Pick according to soft + 1/z
  //double res = (-2.*pow(kappa2,R)*pow(zMinAbs,2.*R) +
  //           sqrt(4.*pow(kappa2,2.*R)
  //                 *pow(zMinAbs,4.*R)
  //              + 4.*(pow(kappa2,R) + pow(kappa2,1. + R))
  //                 *pow(zMinAbs,2.*R)
  //                 *(-(pow(kappa2,R)*pow(zMinAbs,2.*R))
  //                   + kappa2
  //                     *pow(1. + kappa2 - 2.*zMinAbs + pow(zMinAbs,2.),R))))
  //        / (2.*(-(pow(kappa2,R)*pow(zMinAbs,2.*R))
  //               + kappa2
  //                 *pow(1. + kappa2 - 2.*zMinAbs + pow(zMinAbs,2.),R)));
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  double res = 1. + vmin - pow(1.-zMinAbs+vmin,1-R)*pow(1.-zMaxAbs+vmin,R);
  return res;
}

// New overestimates, z-integrated versions.
double CS_isr_qcd_G2GG2::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double m2dip, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  //double kappa2 = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;

  // For small values of pT, increase overestimate to avoid large weights.
  //double tOld(splitInfo.kinematics()->pT2Old);
  //if (tOld > 0. && tOld < SMALL_TEVOL) kappa2 *= sqrt(kappa2);
  // Overestimate by soft + 1/z
  //wt   = preFac
  //     *0.5*( log(1./pow2(zMinAbs) + pow2(1.-zMinAbs)/(kappa2*pow2(zMinAbs))));
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  zMaxAbs = min(zMaxAbs,1.-vmin);
  wt  = preFac * log( (1.-zMinAbs+vmin)/(1.-zMaxAbs+vmin) );
  return wt;
}

// Return overestimate for new splitting.
double CS_isr_qcd_G2GG2::overestimateDiff(double z, double m2dip, int) {
  double wt        = 0.;
  double preFac    = symmetryFactor() * gaugeFactor();
  //double kappa2    = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;

  // For small values of pT, increase overestimate to avoid large weights.
  //double tOld(splitInfo.kinematics()->pT2Old);
  //if (tOld > 0. && tOld < SMALL_TEVOL) kappa2 *= sqrt(kappa2);

  //// Overestimate by soft + 1/z
  //wt  = preFac
  //    * ((1.-z) / ( pow2(1.-z) + kappa2) + 1./z);
  double vmin = pow2(settingsPtr->parm("SpaceShower:pTmin"))/m2dip;
  wt  = preFac * 1. / ( 1. - z + vmin);
  return wt;
}

// Return kernel for new splitting.
bool CS_isr_qcd_G2GG2::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ucsif(ucs_if(z,pT2,m2dip)), xcsif(xcs_if(z,pT2,m2dip));
  double vcsii(vcs_ii(z,pT2,m2dip)), xcsii(xcs_ii(z,pT2,m2dip));
  double xnow = (splitType > 0) ? xcsif : xcsii;
  double vnow = (splitType > 0) ? ucsif : vcsii;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  //double wt_base_as1 = preFac * 0.5 * ( z / ( pow2(z) + kappa2) - 1. )
  //                   + preFac * z*(1.-z);
  //double wt_base_as1 = preFac * 0.5 * z / ( pow2(z) + kappa2);
  double wt_base_as1 = preFac * 0.5 / (xnow + vnow*(1-xnow)/xnow);

  if (order >= 0) wt_base_as1 += -preFac*0.5 + preFac*xnow*(1.-xnow); 

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt_base_as1 ));
  }

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function G->QQ (ISR)

// Return true if this kernel should partake in the evolution.
bool CS_isr_qcd_G2QQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return (!state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].isQuark() );
}

bool CS_isr_qcd_G2QQ::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( !state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].isQuark());
}

int CS_isr_qcd_G2QQ::motherID(int)            { return 21;} 
int CS_isr_qcd_G2QQ::sisterID(int idDaughter) { return -idDaughter;} 
double CS_isr_qcd_G2QQ::gaugeFactor ( int, int )        { return TR;}
double CS_isr_qcd_G2QQ::symmetryFactor ( int, int )     { return 1.0;}

int CS_isr_qcd_G2QQ::radBefID(int, int idEA){ 
  if (particleDataPtr->isQuark(idEA)) return -idEA;
  return 0;
  //return -idEA;
}
pair<int,int> CS_isr_qcd_G2QQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  bool isQuark  = (acolEmtAfter > 0);
  int colRemove = (colRadAfter  == colEmtAfter)
                ? colRadAfter : 0;
  int col       = (colRadAfter  == colRemove)
                ? acolEmtAfter : colRadAfter;
  if (isQuark) return make_pair(col,0);
  colRemove     = (acolRadAfter == acolEmtAfter)
                ? acolRadAfter : 0;
  int acol      = (acolRadAfter == colRemove)
                ? colEmtAfter : acolRadAfter;
  return make_pair(0,acol);
}

vector <int> CS_isr_qcd_G2QQ::recPositions( const Event& state, int iRad, int iEmt) {

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  // Find partons connected via emitted anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_isr_qcd_G2QQ::zSplit(double zMinAbs, double zMaxAbs, double) {
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  double res = zMinAbs + rndmPtr->flat() * (zMaxAbs - zMinAbs);
  return res;
}

// New overestimates, z-integrated versions.
double CS_isr_qcd_G2QQ::overestimateInt(double zMinAbs, double zMaxAbs,
  double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt  = preFac 
      * 2. * ( zMaxAbs - zMinAbs);
  return wt;
}

// Return overestimate for new splitting.
double CS_isr_qcd_G2QQ::overestimateDiff(double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  // Note: Combined with PDF ratio, flat overestimate performs
  // better than using the full splitting kernel as overestimate. 
  wt = preFac 
     * 2.;
  return wt;
}

// Return kernel for new splitting.
bool CS_isr_qcd_G2QQ::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double /*ucsif(ucs_if(z,pT2,m2dip)),*/ xcsif(xcs_if(z,pT2,m2dip));
  double /*vcsii(vcs_ii(z,pT2,m2dip)),*/ xcsii(xcs_ii(z,pT2,m2dip));
  double xnow = (splitType > 0) ? xcsif : xcsii;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  double wt_base_as1 =  preFac * (pow(1.-xnow,2.) + pow(xnow,2.));

  if (order == -1) wt_base_as1 = 0.0;

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt_base_as1 ));
  }

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

// Class inheriting from SplittingQCD class.

// SplittingQCD function Q->GQ (ISR)

// Return true if this kernel should partake in the evolution.
bool CS_isr_qcd_Q2GQ::canRadiate ( const Event& state, pair<int,int> ints,
  unordered_map<string,bool>, Settings*, PartonSystems*, BeamParticle*) {
  return (!state[ints.first].isFinal()
        && state[ints.second].colType() != 0
        && int(sharedColor(state, ints.first, ints.second).size()) > 0
        && state[ints.first].id() == 21 );
}

bool CS_isr_qcd_Q2GQ::canRadiate (const Event& state, int iRadBef,
  int iRecBef, Settings*, PartonSystems*, BeamParticle*) {
  return ( !state[iRadBef].isFinal()
        && state[iRecBef].colType() != 0
        && int(sharedColor(state, iRadBef, iRecBef).size()) > 0
        && state[iRadBef].id() == 21);
}

double CS_isr_qcd_Q2GQ::gaugeFactor ( int, int )        { return CF;}
double CS_isr_qcd_Q2GQ::symmetryFactor ( int, int )     { return 0.5;}

int CS_isr_qcd_Q2GQ::radBefID(int idRA, int){
  if (particleDataPtr->isQuark(idRA)) return 21;
  return 0;
}
pair<int,int> CS_isr_qcd_Q2GQ::radBefCols(
  int colRadAfter, int acolRadAfter, 
  int colEmtAfter, int acolEmtAfter) {
  int col  = (colRadAfter  > 0) ? colRadAfter  : acolEmtAfter;
  int acol = (acolRadAfter > 0) ? acolRadAfter : colEmtAfter;
  return make_pair(col,acol);
}

vector <int> CS_isr_qcd_Q2GQ::recPositions( const Event& state, int iRad, int iEmt) {

  // For Q->GQ, swap radiator and emitted, since we now have to trace the
  // radiator's colour connections.
  //if ( state[iEmt].idAbs() < 20 && state[iRad].id() == 21) swap( iRad, iEmt);

  int colRad  = state[iRad].col();
  int acolRad = state[iRad].acol();
  int colEmt  = state[iEmt].col();
  int acolEmt = state[iEmt].acol();
  int colShared = (colRad  > 0 && colRad == acolEmt) ? colRad
                : (acolRad > 0 && colEmt == acolRad) ? colEmt : 0;
  // Particles to exclude from colour tracing.
  vector<int> iExc(1,iRad); iExc.push_back(iEmt);

  // Find partons connected via emitted colour line.
  vector<int> recs;
  if ( colEmt != 0 && colEmt != colShared) {
    int acolF = findCol(colEmt, iExc, state, 1);
    int  colI = findCol(colEmt, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  iExc.insert(iExc.end(), recs.begin(), recs.end());
  // Find partons connected via emitted anticolour line.
  if ( acolEmt != 0 && acolEmt != colShared) {
    int  colF = findCol(acolEmt, iExc, state, 2);
    int acolI = findCol(acolEmt, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  iExc.insert(iExc.end(), recs.begin(), recs.end());
  // Find partons connected via radiator colour line.
  if ( colRad != 0 && colRad != colShared) {
    int acolF = findCol(colRad, iExc, state, 1);
    int  colI = findCol(colRad, iExc, state, 2);
    if (acolF  > 0 && colI == 0) recs.push_back (acolF);
    if (acolF == 0 && colI >  0) recs.push_back (colI);
  }
  iExc.insert(iExc.end(), recs.begin(), recs.end());
  // Find partons connected via radiator anticolour line.
  if ( acolRad != 0 && acolRad != colShared) {
    int  colF = findCol(acolRad, iExc, state, 2);
    int acolI = findCol(acolRad, iExc, state, 1);
    if ( colF  > 0 && acolI == 0) recs.push_back (colF);
    if ( colF == 0 && acolI >  0) recs.push_back (acolI);
  }
  iExc.insert(iExc.end(), recs.begin(), recs.end());

  // Done.
  return recs;
}

// Pick z for new splitting.
double CS_isr_qcd_Q2GQ::zSplit(double zMinAbs, double, double) {
  double R   = rndmPtr->flat();
  double res = pow(zMinAbs,3./4.)
          / ( pow(1. + R*(-1. + pow(zMinAbs,-3./8.)),2./3.)
             *pow(R - (-1. + R)*pow(zMinAbs,3./8.),2.));
  return res;
}

// New overestimates, z-integrated versions.
double CS_isr_qcd_Q2GQ::overestimateInt(double zMinAbs, double,
  double, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = preFac * 2./3. * (8.*(-1. + pow(zMinAbs,-3./8.)));

  return wt;
}

// Return overestimate for new splitting.
double CS_isr_qcd_Q2GQ::overestimateDiff(double z, double, int) {
  double wt     = 0.;
  double preFac = symmetryFactor() * gaugeFactor();
  wt            = preFac * 2. / pow(z,11./8.);
  return wt;
}

// Return kernel for new splitting.
bool CS_isr_qcd_Q2GQ::calc(const Event& state, int orderNow) {

  // Dummy statement to avoid compiler warnings.
  if (false) cout << state[0].e() << orderNow << endl;

  // Read all splitting variables.
  double z(splitInfo.kinematics()->z), pT2(splitInfo.kinematics()->pT2),
    m2dip(splitInfo.kinematics()->m2Dip);
  int splitType(splitInfo.type);
  double ucsif(ucs_if(z,pT2,m2dip)), xcsif(xcs_if(z,pT2,m2dip));
  double vcsii(vcs_ii(z,pT2,m2dip)), xcsii(xcs_ii(z,pT2,m2dip));
  double xnow = (splitType > 0) ? xcsif : xcsii;
  double vnow = (splitType > 0) ? ucsif : vcsii;

  double preFac = symmetryFactor() * gaugeFactor();
  //int order     = (orderNow > 0) ? orderNow : correctionOrder;
  int order     = (orderNow > -1) ? orderNow : correctionOrder;

  unordered_map<string,double> wts;
  //double wt_base_as1 = preFac*(z + 2.*z/(pow2(z)+kappa2) - 2.);
  double wt_base_as1 = preFac * 2./(xnow + vnow);

  if (order >= 0) wt_base_as1 += preFac*(xnow-2.);

  wts.insert( make_pair("base", wt_base_as1 ));
  if (doVariations) {
    // Create muR-variations.
    if (settingsPtr->parm("Variations:muRisrDown") != 1.)
      wts.insert( make_pair("Variations:muRisrDown", wt_base_as1 ));
    if (settingsPtr->parm("Variations:muRisrUp")   != 1.)
      wts.insert( make_pair("Variations:muRisrUp", wt_base_as1 ));
  }

  // Store higher order correction separately.
  if (order > 0) wts.insert( make_pair("base_order_as2",
    wts["base"] - wt_base_as1 ));

  // Store kernel values.
  adjustKernelVals(wts, state, pT2);
  storeKernelVals(wts);

  return true;

}

//==========================================================================

} // end namespace Pythia8
