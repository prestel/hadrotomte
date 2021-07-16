// DireNeutrinoFlux.h is a part of the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel, Torbjorn Sjostrand.
// PYTHIA is licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// Author: Stefan Prestel, Pedro Machado.

#ifndef Pythia8_DireNeutrinoFlux_H
#define Pythia8_DireNeutrinoFlux_H

// Includes
#include "Pythia8/Pythia.h"

namespace Pythia8 {

//==========================================================================

// A simple scaling PDF. Not realistic; only to check that it works.

class MiniBooneNeutrinoFlux : public PDF {

public:

  // Constructor.
  MiniBooneNeutrinoFlux(int idBeamIn = 2212) : PDF(idBeamIn) {}

private:

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

};

//--------------------------------------------------------------------------

// No dependence on Q2, so leave out name for last argument.

void MiniBooneNeutrinoFlux::xfUpdate(int id, double x, double ) {

  xlepton = 0.;
  // This is x*f(x)
  if (abs(id) == 12 || abs(id) == 14) {
    if (0.6 - 5*x<0)
      xlepton = x*(35.365207899973
                 *pow(exp(-108.13148788927333*pow(-0.12 + x,2)),2.5)
                 -2.005e-17);
    if (0.6 - 5*x>=0)
      xlepton = x*(35.36520789997301
                 *exp(-54.25347222222223*pow(-0.12 + x,2))-2.005e-17);
    xlepton = max(xlepton,1e-15);
  }

  // No quarks, gluons, etc in flux
  xg = xu = xd = xubar = xdbar = xs = xc = xb = xuVal = xuSea = xdVal
     = xdSea = 0.;

  // idSav = 9 to indicate that all flavours reset.
  idSav = 9;

}

//==========================================================================

// A simple scaling PDF. Not realistic; only to check that it works.

class GaussNeutrinoFlux : public PDF {

public:

  // Constructor.
  GaussNeutrinoFlux(int idBeamIn, double eMaxIn, double normIn,
   double muIn, double sigmaIn)
    : PDF(idBeamIn), eMax(eMaxIn), norm(normIn), mu(muIn),
      sigma(sigmaIn) {}

private:

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

  double gauss(double x);
  double eMax, norm, mu, sigma;

};

//--------------------------------------------------------------------------

double GaussNeutrinoFlux::gauss(double x) {
  return norm*exp(-0.5* pow2((eMax*x- mu)/sigma));
}

//--------------------------------------------------------------------------

// No dependence on Q2, so leave out name for last argument.

void GaussNeutrinoFlux::xfUpdate(int id, double x, double ) {

  xlepton = 0.;
  if (abs(id) == 12 || abs(id) == 14)
    xlepton = x * gauss(x);    

  // No quarks, gluons, etc in flux
  xg = xu = xd = xubar = xdbar = xs = xc = xb = xuVal = xuSea = xdVal
     = xdSea = 0.;

  // idSav = 9 to indicate that all flavours reset.
  idSav = 9;

}

//==========================================================================

// A simple scaling PDF. Not realistic; only to check that it works.

class GenericNeutrinoFlux : public PDF {

public:

  // Constructor.
  GenericNeutrinoFlux(int idBeamIn, double eMaxIn)
    : PDF(idBeamIn), eMax(eMaxIn) {}

private:

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

  double eMax;

};

//--------------------------------------------------------------------------

// No dependence on Q2, so leave out name for last argument.

void GenericNeutrinoFlux::xfUpdate(int id, double x, double ) {
  xlepton = 0.;
  //double xreg = x+0.000001;
  // This is x*f(x)
  //// This function rises towards small x, until it flattens and
  //// is cut-off
  //if (abs(id) == 12 || abs(id) == 14) xlepton = x*log(1/x)/xreg;
  // This function rises, but then has a maximum at 0.2 and then drops off.  
  if (abs(id) == 12 || abs(id) == 14) xlepton = x*log(1/x)/sqrt(x);    

  // No quarks, gluons, etc in flux
  xg = xu = xd = xubar = xdbar = xs = xc = xb = xuVal = xuSea = xdVal
     = xdSea = 0.;

  // idSav = 9 to indicate that all flavours reset.
  idSav = 9;

}

//==========================================================================

class TestDuneNeutrinoFlux : public PDF {

public:

  // Constructor.
  TestDuneNeutrinoFlux(int idBeamIn)
    : PDF(idBeamIn) {}

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

};

//--------------------------------------------------------------------------

void TestDuneNeutrinoFlux::xfUpdate(int id, double x, double ) {

  xlepton = 0.;
  if (abs(id) == 12 || abs(id) == 14) {

    double emax = 25;
    double unit = 5.57946e+01;

    double normal1_mean    = 1.22406e+02;
    double normal1_sigmasq = 8.15575e+01;

    double normal2_mean    = 2.88042e+02;
    double normal2_sigmasq = 3.97070e+01;

    double lognormal_mean    = 8.56329e+01;
    double lognormal_sigmasq = 1.45793e+01;

    double normal1_norm = 1.98732e+01;
    double normal2_norm = 1.52529e+01;
    double lognormal_norm = 4.87707e+01;

    xlepton = x*unit
      *( normal1_norm/(normal1_sigmasq/unit)
        *exp(-(x*emax-normal1_mean/unit)*(x*emax-normal1_mean/unit)/ (2*normal1_sigmasq/unit))
        +normal2_norm/(normal2_sigmasq/unit)
        *exp(-(x*emax-normal2_mean/unit)*(x*emax-normal2_mean/unit)/ (2*normal2_sigmasq/unit))
        +lognormal_norm/(x*emax)/(lognormal_sigmasq/unit)
        *exp(-(log(x*emax)-lognormal_mean/unit)*(log(x*emax)-lognormal_mean/unit)/ (2*lognormal_sigmasq/unit)));

  }

  // No quarks, gluons, etc in flux
  xg = xu = xd = xubar = xdbar = xs = xc = xb = xuVal = xuSea = xdVal
     = xdSea = 0.;

  // idSav = 9 to indicate that all flavours reset.
  idSav = 9;

}

//==========================================================================

class DuneNeutrinoFlux : public PDF {

public:

  // Constructor.
  DuneNeutrinoFlux(int idBeamIn, double eMaxIn, double normIn,
   double muIn, double sigmaIn)
    : PDF(idBeamIn), eMax(eMaxIn), norm(normIn), mu(muIn),
      sigma(sigmaIn) {}

  // Update PDF values.
  void xfUpdate(int id, double x, double Q2);

  double eMax, norm, mu, sigma;

};

//--------------------------------------------------------------------------

void DuneNeutrinoFlux::xfUpdate(int id, double x, double ) {

  xlepton = 0.;
  if (abs(id) == 12)
    xlepton = 0.0;
  if (abs(id) == 14)
    xlepton = x * norm * exp(-0.5* pow2((eMax*x- mu)/sigma));  

  // No quarks, gluons, etc in flux
  xg = xu = xd = xubar = xdbar = xs = xc = xb = xuVal = xuSea = xdVal
     = xdSea = 0.;

  // idSav = 9 to indicate that all flavours reset.
  idSav = 9;

}

//==========================================================================

} // end namespace Pythia8

#endif
