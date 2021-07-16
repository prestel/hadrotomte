//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R7_P1_sm_qq_llqq.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u > e- e+ u u WEIGHTED<=99 @7
// Process: u u > mu- mu+ u u WEIGHTED<=99 @7
// Process: c c > e- e+ c c WEIGHTED<=99 @7
// Process: c c > mu- mu+ c c WEIGHTED<=99 @7
// Process: u u~ > e- e+ u u~ WEIGHTED<=99 @7
// Process: u u~ > mu- mu+ u u~ WEIGHTED<=99 @7
// Process: c c~ > e- e+ c c~ WEIGHTED<=99 @7
// Process: c c~ > mu- mu+ c c~ WEIGHTED<=99 @7
// Process: d d > e- e+ d d WEIGHTED<=99 @7
// Process: d d > mu- mu+ d d WEIGHTED<=99 @7
// Process: s s > e- e+ s s WEIGHTED<=99 @7
// Process: s s > mu- mu+ s s WEIGHTED<=99 @7
// Process: d d~ > e- e+ d d~ WEIGHTED<=99 @7
// Process: d d~ > mu- mu+ d d~ WEIGHTED<=99 @7
// Process: s s~ > e- e+ s s~ WEIGHTED<=99 @7
// Process: s s~ > mu- mu+ s s~ WEIGHTED<=99 @7
// Process: u~ u~ > e- e+ u~ u~ WEIGHTED<=99 @7
// Process: u~ u~ > mu- mu+ u~ u~ WEIGHTED<=99 @7
// Process: c~ c~ > e- e+ c~ c~ WEIGHTED<=99 @7
// Process: c~ c~ > mu- mu+ c~ c~ WEIGHTED<=99 @7
// Process: d~ d~ > e- e+ d~ d~ WEIGHTED<=99 @7
// Process: d~ d~ > mu- mu+ d~ d~ WEIGHTED<=99 @7
// Process: s~ s~ > e- e+ s~ s~ WEIGHTED<=99 @7
// Process: s~ s~ > mu- mu+ s~ s~ WEIGHTED<=99 @7
// Process: u d > e- e+ u d WEIGHTED<=99 @7
// Process: u d > mu- mu+ u d WEIGHTED<=99 @7
// Process: c s > e- e+ c s WEIGHTED<=99 @7
// Process: c s > mu- mu+ c s WEIGHTED<=99 @7
// Process: u u~ > e- e+ d d~ WEIGHTED<=99 @7
// Process: u u~ > mu- mu+ d d~ WEIGHTED<=99 @7
// Process: c c~ > e- e+ s s~ WEIGHTED<=99 @7
// Process: c c~ > mu- mu+ s s~ WEIGHTED<=99 @7
// Process: u d~ > e- e+ u d~ WEIGHTED<=99 @7
// Process: u d~ > mu- mu+ u d~ WEIGHTED<=99 @7
// Process: c s~ > e- e+ c s~ WEIGHTED<=99 @7
// Process: c s~ > mu- mu+ c s~ WEIGHTED<=99 @7
// Process: d u~ > e- e+ d u~ WEIGHTED<=99 @7
// Process: d u~ > mu- mu+ d u~ WEIGHTED<=99 @7
// Process: s c~ > e- e+ s c~ WEIGHTED<=99 @7
// Process: s c~ > mu- mu+ s c~ WEIGHTED<=99 @7
// Process: d d~ > e- e+ u u~ WEIGHTED<=99 @7
// Process: d d~ > mu- mu+ u u~ WEIGHTED<=99 @7
// Process: s s~ > e- e+ c c~ WEIGHTED<=99 @7
// Process: s s~ > mu- mu+ c c~ WEIGHTED<=99 @7
// Process: u~ d~ > e- e+ u~ d~ WEIGHTED<=99 @7
// Process: u~ d~ > mu- mu+ u~ d~ WEIGHTED<=99 @7
// Process: c~ s~ > e- e+ c~ s~ WEIGHTED<=99 @7
// Process: c~ s~ > mu- mu+ c~ s~ WEIGHTED<=99 @7
// Process: u c > e- e+ u c WEIGHTED<=99 @7
// Process: u c > mu- mu+ u c WEIGHTED<=99 @7
// Process: u s > e- e+ u s WEIGHTED<=99 @7
// Process: u s > mu- mu+ u s WEIGHTED<=99 @7
// Process: c d > e- e+ c d WEIGHTED<=99 @7
// Process: c d > mu- mu+ c d WEIGHTED<=99 @7
// Process: u u~ > e- e+ c c~ WEIGHTED<=99 @7
// Process: u u~ > mu- mu+ c c~ WEIGHTED<=99 @7
// Process: c c~ > e- e+ u u~ WEIGHTED<=99 @7
// Process: c c~ > mu- mu+ u u~ WEIGHTED<=99 @7
// Process: u u~ > e- e+ s s~ WEIGHTED<=99 @7
// Process: u u~ > mu- mu+ s s~ WEIGHTED<=99 @7
// Process: c c~ > e- e+ d d~ WEIGHTED<=99 @7
// Process: c c~ > mu- mu+ d d~ WEIGHTED<=99 @7
// Process: u c~ > e- e+ u c~ WEIGHTED<=99 @7
// Process: u c~ > mu- mu+ u c~ WEIGHTED<=99 @7
// Process: c u~ > e- e+ c u~ WEIGHTED<=99 @7
// Process: c u~ > mu- mu+ c u~ WEIGHTED<=99 @7
// Process: u s~ > e- e+ u s~ WEIGHTED<=99 @7
// Process: u s~ > mu- mu+ u s~ WEIGHTED<=99 @7
// Process: c d~ > e- e+ c d~ WEIGHTED<=99 @7
// Process: c d~ > mu- mu+ c d~ WEIGHTED<=99 @7
// Process: d s > e- e+ d s WEIGHTED<=99 @7
// Process: d s > mu- mu+ d s WEIGHTED<=99 @7
// Process: d c~ > e- e+ d c~ WEIGHTED<=99 @7
// Process: d c~ > mu- mu+ d c~ WEIGHTED<=99 @7
// Process: s u~ > e- e+ s u~ WEIGHTED<=99 @7
// Process: s u~ > mu- mu+ s u~ WEIGHTED<=99 @7
// Process: d d~ > e- e+ c c~ WEIGHTED<=99 @7
// Process: d d~ > mu- mu+ c c~ WEIGHTED<=99 @7
// Process: s s~ > e- e+ u u~ WEIGHTED<=99 @7
// Process: s s~ > mu- mu+ u u~ WEIGHTED<=99 @7
// Process: d d~ > e- e+ s s~ WEIGHTED<=99 @7
// Process: d d~ > mu- mu+ s s~ WEIGHTED<=99 @7
// Process: s s~ > e- e+ d d~ WEIGHTED<=99 @7
// Process: s s~ > mu- mu+ d d~ WEIGHTED<=99 @7
// Process: d s~ > e- e+ d s~ WEIGHTED<=99 @7
// Process: d s~ > mu- mu+ d s~ WEIGHTED<=99 @7
// Process: s d~ > e- e+ s d~ WEIGHTED<=99 @7
// Process: s d~ > mu- mu+ s d~ WEIGHTED<=99 @7
// Process: u~ c~ > e- e+ u~ c~ WEIGHTED<=99 @7
// Process: u~ c~ > mu- mu+ u~ c~ WEIGHTED<=99 @7
// Process: u~ s~ > e- e+ u~ s~ WEIGHTED<=99 @7
// Process: u~ s~ > mu- mu+ u~ s~ WEIGHTED<=99 @7
// Process: c~ d~ > e- e+ c~ d~ WEIGHTED<=99 @7
// Process: c~ d~ > mu- mu+ c~ d~ WEIGHTED<=99 @7
// Process: d~ s~ > e- e+ d~ s~ WEIGHTED<=99 @7
// Process: d~ s~ > mu- mu+ d~ s~ WEIGHTED<=99 @7
// Process: u u > ve ve~ u u WEIGHTED<=99 @7
// Process: u u > vm vm~ u u WEIGHTED<=99 @7
// Process: c c > ve ve~ c c WEIGHTED<=99 @7
// Process: c c > vm vm~ c c WEIGHTED<=99 @7
// Process: u u~ > ve ve~ u u~ WEIGHTED<=99 @7
// Process: u u~ > vm vm~ u u~ WEIGHTED<=99 @7
// Process: c c~ > ve ve~ c c~ WEIGHTED<=99 @7
// Process: c c~ > vm vm~ c c~ WEIGHTED<=99 @7
// Process: d d > ve ve~ d d WEIGHTED<=99 @7
// Process: d d > vm vm~ d d WEIGHTED<=99 @7
// Process: s s > ve ve~ s s WEIGHTED<=99 @7
// Process: s s > vm vm~ s s WEIGHTED<=99 @7
// Process: d d~ > ve ve~ d d~ WEIGHTED<=99 @7
// Process: d d~ > vm vm~ d d~ WEIGHTED<=99 @7
// Process: s s~ > ve ve~ s s~ WEIGHTED<=99 @7
// Process: s s~ > vm vm~ s s~ WEIGHTED<=99 @7
// Process: u~ u~ > ve ve~ u~ u~ WEIGHTED<=99 @7
// Process: u~ u~ > vm vm~ u~ u~ WEIGHTED<=99 @7
// Process: c~ c~ > ve ve~ c~ c~ WEIGHTED<=99 @7
// Process: c~ c~ > vm vm~ c~ c~ WEIGHTED<=99 @7
// Process: d~ d~ > ve ve~ d~ d~ WEIGHTED<=99 @7
// Process: d~ d~ > vm vm~ d~ d~ WEIGHTED<=99 @7
// Process: s~ s~ > ve ve~ s~ s~ WEIGHTED<=99 @7
// Process: s~ s~ > vm vm~ s~ s~ WEIGHTED<=99 @7
// Process: u u > ve e+ u d WEIGHTED<=99 @7
// Process: u u > vm mu+ u d WEIGHTED<=99 @7
// Process: c c > ve e+ c s WEIGHTED<=99 @7
// Process: c c > vm mu+ c s WEIGHTED<=99 @7
// Process: u d > e- ve~ u u WEIGHTED<=99 @7
// Process: u d > mu- vm~ u u WEIGHTED<=99 @7
// Process: c s > e- ve~ c c WEIGHTED<=99 @7
// Process: c s > mu- vm~ c c WEIGHTED<=99 @7
// Process: u d > ve e+ d d WEIGHTED<=99 @7
// Process: u d > vm mu+ d d WEIGHTED<=99 @7
// Process: c s > ve e+ s s WEIGHTED<=99 @7
// Process: c s > vm mu+ s s WEIGHTED<=99 @7
// Process: u u~ > e- ve~ u d~ WEIGHTED<=99 @7
// Process: u u~ > mu- vm~ u d~ WEIGHTED<=99 @7
// Process: c c~ > e- ve~ c s~ WEIGHTED<=99 @7
// Process: c c~ > mu- vm~ c s~ WEIGHTED<=99 @7
// Process: u u~ > ve e+ d u~ WEIGHTED<=99 @7
// Process: u u~ > vm mu+ d u~ WEIGHTED<=99 @7
// Process: c c~ > ve e+ s c~ WEIGHTED<=99 @7
// Process: c c~ > vm mu+ s c~ WEIGHTED<=99 @7
// Process: u d~ > ve e+ u u~ WEIGHTED<=99 @7
// Process: u d~ > vm mu+ u u~ WEIGHTED<=99 @7
// Process: c s~ > ve e+ c c~ WEIGHTED<=99 @7
// Process: c s~ > vm mu+ c c~ WEIGHTED<=99 @7
// Process: u d~ > ve e+ d d~ WEIGHTED<=99 @7
// Process: u d~ > vm mu+ d d~ WEIGHTED<=99 @7
// Process: c s~ > ve e+ s s~ WEIGHTED<=99 @7
// Process: c s~ > vm mu+ s s~ WEIGHTED<=99 @7
// Process: d d > e- ve~ u d WEIGHTED<=99 @7
// Process: d d > mu- vm~ u d WEIGHTED<=99 @7
// Process: s s > e- ve~ c s WEIGHTED<=99 @7
// Process: s s > mu- vm~ c s WEIGHTED<=99 @7
// Process: d u~ > e- ve~ u u~ WEIGHTED<=99 @7
// Process: d u~ > mu- vm~ u u~ WEIGHTED<=99 @7
// Process: s c~ > e- ve~ c c~ WEIGHTED<=99 @7
// Process: s c~ > mu- vm~ c c~ WEIGHTED<=99 @7
// Process: d u~ > e- ve~ d d~ WEIGHTED<=99 @7
// Process: d u~ > mu- vm~ d d~ WEIGHTED<=99 @7
// Process: s c~ > e- ve~ s s~ WEIGHTED<=99 @7
// Process: s c~ > mu- vm~ s s~ WEIGHTED<=99 @7
// Process: d d~ > e- ve~ u d~ WEIGHTED<=99 @7
// Process: d d~ > mu- vm~ u d~ WEIGHTED<=99 @7
// Process: s s~ > e- ve~ c s~ WEIGHTED<=99 @7
// Process: s s~ > mu- vm~ c s~ WEIGHTED<=99 @7
// Process: d d~ > ve e+ d u~ WEIGHTED<=99 @7
// Process: d d~ > vm mu+ d u~ WEIGHTED<=99 @7
// Process: s s~ > ve e+ s c~ WEIGHTED<=99 @7
// Process: s s~ > vm mu+ s c~ WEIGHTED<=99 @7
// Process: u~ u~ > e- ve~ u~ d~ WEIGHTED<=99 @7
// Process: u~ u~ > mu- vm~ u~ d~ WEIGHTED<=99 @7
// Process: c~ c~ > e- ve~ c~ s~ WEIGHTED<=99 @7
// Process: c~ c~ > mu- vm~ c~ s~ WEIGHTED<=99 @7
// Process: u~ d~ > e- ve~ d~ d~ WEIGHTED<=99 @7
// Process: u~ d~ > mu- vm~ d~ d~ WEIGHTED<=99 @7
// Process: c~ s~ > e- ve~ s~ s~ WEIGHTED<=99 @7
// Process: c~ s~ > mu- vm~ s~ s~ WEIGHTED<=99 @7
// Process: u~ d~ > ve e+ u~ u~ WEIGHTED<=99 @7
// Process: u~ d~ > vm mu+ u~ u~ WEIGHTED<=99 @7
// Process: c~ s~ > ve e+ c~ c~ WEIGHTED<=99 @7
// Process: c~ s~ > vm mu+ c~ c~ WEIGHTED<=99 @7
// Process: d~ d~ > ve e+ u~ d~ WEIGHTED<=99 @7
// Process: d~ d~ > vm mu+ u~ d~ WEIGHTED<=99 @7
// Process: s~ s~ > ve e+ c~ s~ WEIGHTED<=99 @7
// Process: s~ s~ > vm mu+ c~ s~ WEIGHTED<=99 @7
// Process: u d > ve ve~ u d WEIGHTED<=99 @7
// Process: u d > vm vm~ u d WEIGHTED<=99 @7
// Process: c s > ve ve~ c s WEIGHTED<=99 @7
// Process: c s > vm vm~ c s WEIGHTED<=99 @7
// Process: u u~ > ve ve~ d d~ WEIGHTED<=99 @7
// Process: u u~ > vm vm~ d d~ WEIGHTED<=99 @7
// Process: c c~ > ve ve~ s s~ WEIGHTED<=99 @7
// Process: c c~ > vm vm~ s s~ WEIGHTED<=99 @7
// Process: u d~ > ve ve~ u d~ WEIGHTED<=99 @7
// Process: u d~ > vm vm~ u d~ WEIGHTED<=99 @7
// Process: c s~ > ve ve~ c s~ WEIGHTED<=99 @7
// Process: c s~ > vm vm~ c s~ WEIGHTED<=99 @7
// Process: d u~ > ve ve~ d u~ WEIGHTED<=99 @7
// Process: d u~ > vm vm~ d u~ WEIGHTED<=99 @7
// Process: s c~ > ve ve~ s c~ WEIGHTED<=99 @7
// Process: s c~ > vm vm~ s c~ WEIGHTED<=99 @7
// Process: d d~ > ve ve~ u u~ WEIGHTED<=99 @7
// Process: d d~ > vm vm~ u u~ WEIGHTED<=99 @7
// Process: s s~ > ve ve~ c c~ WEIGHTED<=99 @7
// Process: s s~ > vm vm~ c c~ WEIGHTED<=99 @7
// Process: u~ d~ > ve ve~ u~ d~ WEIGHTED<=99 @7
// Process: u~ d~ > vm vm~ u~ d~ WEIGHTED<=99 @7
// Process: c~ s~ > ve ve~ c~ s~ WEIGHTED<=99 @7
// Process: c~ s~ > vm vm~ c~ s~ WEIGHTED<=99 @7
// Process: u c > ve ve~ u c WEIGHTED<=99 @7
// Process: u c > vm vm~ u c WEIGHTED<=99 @7
// Process: u s > ve ve~ u s WEIGHTED<=99 @7
// Process: u s > vm vm~ u s WEIGHTED<=99 @7
// Process: c d > ve ve~ c d WEIGHTED<=99 @7
// Process: c d > vm vm~ c d WEIGHTED<=99 @7
// Process: u u~ > ve ve~ c c~ WEIGHTED<=99 @7
// Process: u u~ > vm vm~ c c~ WEIGHTED<=99 @7
// Process: c c~ > ve ve~ u u~ WEIGHTED<=99 @7
// Process: c c~ > vm vm~ u u~ WEIGHTED<=99 @7
// Process: u u~ > ve ve~ s s~ WEIGHTED<=99 @7
// Process: u u~ > vm vm~ s s~ WEIGHTED<=99 @7
// Process: c c~ > ve ve~ d d~ WEIGHTED<=99 @7
// Process: c c~ > vm vm~ d d~ WEIGHTED<=99 @7
// Process: u c~ > ve ve~ u c~ WEIGHTED<=99 @7
// Process: u c~ > vm vm~ u c~ WEIGHTED<=99 @7
// Process: c u~ > ve ve~ c u~ WEIGHTED<=99 @7
// Process: c u~ > vm vm~ c u~ WEIGHTED<=99 @7
// Process: u s~ > ve ve~ u s~ WEIGHTED<=99 @7
// Process: u s~ > vm vm~ u s~ WEIGHTED<=99 @7
// Process: c d~ > ve ve~ c d~ WEIGHTED<=99 @7
// Process: c d~ > vm vm~ c d~ WEIGHTED<=99 @7
// Process: d s > ve ve~ d s WEIGHTED<=99 @7
// Process: d s > vm vm~ d s WEIGHTED<=99 @7
// Process: d c~ > ve ve~ d c~ WEIGHTED<=99 @7
// Process: d c~ > vm vm~ d c~ WEIGHTED<=99 @7
// Process: s u~ > ve ve~ s u~ WEIGHTED<=99 @7
// Process: s u~ > vm vm~ s u~ WEIGHTED<=99 @7
// Process: d d~ > ve ve~ c c~ WEIGHTED<=99 @7
// Process: d d~ > vm vm~ c c~ WEIGHTED<=99 @7
// Process: s s~ > ve ve~ u u~ WEIGHTED<=99 @7
// Process: s s~ > vm vm~ u u~ WEIGHTED<=99 @7
// Process: d d~ > ve ve~ s s~ WEIGHTED<=99 @7
// Process: d d~ > vm vm~ s s~ WEIGHTED<=99 @7
// Process: s s~ > ve ve~ d d~ WEIGHTED<=99 @7
// Process: s s~ > vm vm~ d d~ WEIGHTED<=99 @7
// Process: d s~ > ve ve~ d s~ WEIGHTED<=99 @7
// Process: d s~ > vm vm~ d s~ WEIGHTED<=99 @7
// Process: s d~ > ve ve~ s d~ WEIGHTED<=99 @7
// Process: s d~ > vm vm~ s d~ WEIGHTED<=99 @7
// Process: u~ c~ > ve ve~ u~ c~ WEIGHTED<=99 @7
// Process: u~ c~ > vm vm~ u~ c~ WEIGHTED<=99 @7
// Process: u~ s~ > ve ve~ u~ s~ WEIGHTED<=99 @7
// Process: u~ s~ > vm vm~ u~ s~ WEIGHTED<=99 @7
// Process: c~ d~ > ve ve~ c~ d~ WEIGHTED<=99 @7
// Process: c~ d~ > vm vm~ c~ d~ WEIGHTED<=99 @7
// Process: d~ s~ > ve ve~ d~ s~ WEIGHTED<=99 @7
// Process: d~ s~ > vm vm~ d~ s~ WEIGHTED<=99 @7
// Process: u c > ve e+ u s WEIGHTED<=99 @7
// Process: u c > vm mu+ u s WEIGHTED<=99 @7
// Process: u c > ve e+ c d WEIGHTED<=99 @7
// Process: u c > vm mu+ c d WEIGHTED<=99 @7
// Process: u s > e- ve~ u c WEIGHTED<=99 @7
// Process: u s > mu- vm~ u c WEIGHTED<=99 @7
// Process: c d > e- ve~ c u WEIGHTED<=99 @7
// Process: c d > mu- vm~ c u WEIGHTED<=99 @7
// Process: u s > ve e+ d s WEIGHTED<=99 @7
// Process: u s > vm mu+ d s WEIGHTED<=99 @7
// Process: c d > ve e+ s d WEIGHTED<=99 @7
// Process: c d > vm mu+ s d WEIGHTED<=99 @7
// Process: u u~ > e- ve~ c s~ WEIGHTED<=99 @7
// Process: u u~ > mu- vm~ c s~ WEIGHTED<=99 @7
// Process: c c~ > e- ve~ u d~ WEIGHTED<=99 @7
// Process: c c~ > mu- vm~ u d~ WEIGHTED<=99 @7
// Process: u u~ > ve e+ s c~ WEIGHTED<=99 @7
// Process: u u~ > vm mu+ s c~ WEIGHTED<=99 @7
// Process: c c~ > ve e+ d u~ WEIGHTED<=99 @7
// Process: c c~ > vm mu+ d u~ WEIGHTED<=99 @7
// Process: u c~ > e- ve~ u s~ WEIGHTED<=99 @7
// Process: u c~ > mu- vm~ u s~ WEIGHTED<=99 @7
// Process: c u~ > e- ve~ c d~ WEIGHTED<=99 @7
// Process: c u~ > mu- vm~ c d~ WEIGHTED<=99 @7
// Process: u c~ > ve e+ d c~ WEIGHTED<=99 @7
// Process: u c~ > vm mu+ d c~ WEIGHTED<=99 @7
// Process: c u~ > ve e+ s u~ WEIGHTED<=99 @7
// Process: c u~ > vm mu+ s u~ WEIGHTED<=99 @7
// Process: u d~ > ve e+ c c~ WEIGHTED<=99 @7
// Process: u d~ > vm mu+ c c~ WEIGHTED<=99 @7
// Process: c s~ > ve e+ u u~ WEIGHTED<=99 @7
// Process: c s~ > vm mu+ u u~ WEIGHTED<=99 @7
// Process: u d~ > ve e+ s s~ WEIGHTED<=99 @7
// Process: u d~ > vm mu+ s s~ WEIGHTED<=99 @7
// Process: c s~ > ve e+ d d~ WEIGHTED<=99 @7
// Process: c s~ > vm mu+ d d~ WEIGHTED<=99 @7
// Process: u s~ > ve e+ u c~ WEIGHTED<=99 @7
// Process: u s~ > vm mu+ u c~ WEIGHTED<=99 @7
// Process: c d~ > ve e+ c u~ WEIGHTED<=99 @7
// Process: c d~ > vm mu+ c u~ WEIGHTED<=99 @7
// Process: u s~ > ve e+ d s~ WEIGHTED<=99 @7
// Process: u s~ > vm mu+ d s~ WEIGHTED<=99 @7
// Process: c d~ > ve e+ s d~ WEIGHTED<=99 @7
// Process: c d~ > vm mu+ s d~ WEIGHTED<=99 @7
// Process: d s > e- ve~ u s WEIGHTED<=99 @7
// Process: d s > mu- vm~ u s WEIGHTED<=99 @7
// Process: d s > e- ve~ c d WEIGHTED<=99 @7
// Process: d s > mu- vm~ c d WEIGHTED<=99 @7
// Process: d u~ > e- ve~ c c~ WEIGHTED<=99 @7
// Process: d u~ > mu- vm~ c c~ WEIGHTED<=99 @7
// Process: s c~ > e- ve~ u u~ WEIGHTED<=99 @7
// Process: s c~ > mu- vm~ u u~ WEIGHTED<=99 @7
// Process: d u~ > e- ve~ s s~ WEIGHTED<=99 @7
// Process: d u~ > mu- vm~ s s~ WEIGHTED<=99 @7
// Process: s c~ > e- ve~ d d~ WEIGHTED<=99 @7
// Process: s c~ > mu- vm~ d d~ WEIGHTED<=99 @7
// Process: d c~ > e- ve~ u c~ WEIGHTED<=99 @7
// Process: d c~ > mu- vm~ u c~ WEIGHTED<=99 @7
// Process: s u~ > e- ve~ c u~ WEIGHTED<=99 @7
// Process: s u~ > mu- vm~ c u~ WEIGHTED<=99 @7
// Process: d c~ > e- ve~ d s~ WEIGHTED<=99 @7
// Process: d c~ > mu- vm~ d s~ WEIGHTED<=99 @7
// Process: s u~ > e- ve~ s d~ WEIGHTED<=99 @7
// Process: s u~ > mu- vm~ s d~ WEIGHTED<=99 @7
// Process: d d~ > e- ve~ c s~ WEIGHTED<=99 @7
// Process: d d~ > mu- vm~ c s~ WEIGHTED<=99 @7
// Process: s s~ > e- ve~ u d~ WEIGHTED<=99 @7
// Process: s s~ > mu- vm~ u d~ WEIGHTED<=99 @7
// Process: d d~ > ve e+ s c~ WEIGHTED<=99 @7
// Process: d d~ > vm mu+ s c~ WEIGHTED<=99 @7
// Process: s s~ > ve e+ d u~ WEIGHTED<=99 @7
// Process: s s~ > vm mu+ d u~ WEIGHTED<=99 @7
// Process: d s~ > e- ve~ u s~ WEIGHTED<=99 @7
// Process: d s~ > mu- vm~ u s~ WEIGHTED<=99 @7
// Process: s d~ > e- ve~ c d~ WEIGHTED<=99 @7
// Process: s d~ > mu- vm~ c d~ WEIGHTED<=99 @7
// Process: d s~ > ve e+ d c~ WEIGHTED<=99 @7
// Process: d s~ > vm mu+ d c~ WEIGHTED<=99 @7
// Process: s d~ > ve e+ s u~ WEIGHTED<=99 @7
// Process: s d~ > vm mu+ s u~ WEIGHTED<=99 @7
// Process: u~ c~ > e- ve~ u~ s~ WEIGHTED<=99 @7
// Process: u~ c~ > mu- vm~ u~ s~ WEIGHTED<=99 @7
// Process: u~ c~ > e- ve~ c~ d~ WEIGHTED<=99 @7
// Process: u~ c~ > mu- vm~ c~ d~ WEIGHTED<=99 @7
// Process: u~ s~ > e- ve~ d~ s~ WEIGHTED<=99 @7
// Process: u~ s~ > mu- vm~ d~ s~ WEIGHTED<=99 @7
// Process: c~ d~ > e- ve~ s~ d~ WEIGHTED<=99 @7
// Process: c~ d~ > mu- vm~ s~ d~ WEIGHTED<=99 @7
// Process: u~ s~ > ve e+ u~ c~ WEIGHTED<=99 @7
// Process: u~ s~ > vm mu+ u~ c~ WEIGHTED<=99 @7
// Process: c~ d~ > ve e+ c~ u~ WEIGHTED<=99 @7
// Process: c~ d~ > vm mu+ c~ u~ WEIGHTED<=99 @7
// Process: d~ s~ > ve e+ u~ s~ WEIGHTED<=99 @7
// Process: d~ s~ > vm mu+ u~ s~ WEIGHTED<=99 @7
// Process: d~ s~ > ve e+ c~ d~ WEIGHTED<=99 @7
// Process: d~ s~ > vm mu+ c~ d~ WEIGHTED<=99 @7
// Process: u s > e- e+ c d WEIGHTED<=99 @7
// Process: u s > mu- mu+ c d WEIGHTED<=99 @7
// Process: c d > e- e+ u s WEIGHTED<=99 @7
// Process: c d > mu- mu+ u s WEIGHTED<=99 @7
// Process: u c~ > e- e+ d s~ WEIGHTED<=99 @7
// Process: u c~ > mu- mu+ d s~ WEIGHTED<=99 @7
// Process: c u~ > e- e+ s d~ WEIGHTED<=99 @7
// Process: c u~ > mu- mu+ s d~ WEIGHTED<=99 @7
// Process: u d~ > e- e+ c s~ WEIGHTED<=99 @7
// Process: u d~ > mu- mu+ c s~ WEIGHTED<=99 @7
// Process: c s~ > e- e+ u d~ WEIGHTED<=99 @7
// Process: c s~ > mu- mu+ u d~ WEIGHTED<=99 @7
// Process: d u~ > e- e+ s c~ WEIGHTED<=99 @7
// Process: d u~ > mu- mu+ s c~ WEIGHTED<=99 @7
// Process: s c~ > e- e+ d u~ WEIGHTED<=99 @7
// Process: s c~ > mu- mu+ d u~ WEIGHTED<=99 @7
// Process: d s~ > e- e+ u c~ WEIGHTED<=99 @7
// Process: d s~ > mu- mu+ u c~ WEIGHTED<=99 @7
// Process: s d~ > e- e+ c u~ WEIGHTED<=99 @7
// Process: s d~ > mu- mu+ c u~ WEIGHTED<=99 @7
// Process: u~ s~ > e- e+ c~ d~ WEIGHTED<=99 @7
// Process: u~ s~ > mu- mu+ c~ d~ WEIGHTED<=99 @7
// Process: c~ d~ > e- e+ u~ s~ WEIGHTED<=99 @7
// Process: c~ d~ > mu- mu+ u~ s~ WEIGHTED<=99 @7
// Process: u s > ve ve~ c d WEIGHTED<=99 @7
// Process: u s > vm vm~ c d WEIGHTED<=99 @7
// Process: c d > ve ve~ u s WEIGHTED<=99 @7
// Process: c d > vm vm~ u s WEIGHTED<=99 @7
// Process: u c~ > ve ve~ d s~ WEIGHTED<=99 @7
// Process: u c~ > vm vm~ d s~ WEIGHTED<=99 @7
// Process: c u~ > ve ve~ s d~ WEIGHTED<=99 @7
// Process: c u~ > vm vm~ s d~ WEIGHTED<=99 @7
// Process: u d~ > ve ve~ c s~ WEIGHTED<=99 @7
// Process: u d~ > vm vm~ c s~ WEIGHTED<=99 @7
// Process: c s~ > ve ve~ u d~ WEIGHTED<=99 @7
// Process: c s~ > vm vm~ u d~ WEIGHTED<=99 @7
// Process: d u~ > ve ve~ s c~ WEIGHTED<=99 @7
// Process: d u~ > vm vm~ s c~ WEIGHTED<=99 @7
// Process: s c~ > ve ve~ d u~ WEIGHTED<=99 @7
// Process: s c~ > vm vm~ d u~ WEIGHTED<=99 @7
// Process: d s~ > ve ve~ u c~ WEIGHTED<=99 @7
// Process: d s~ > vm vm~ u c~ WEIGHTED<=99 @7
// Process: s d~ > ve ve~ c u~ WEIGHTED<=99 @7
// Process: s d~ > vm vm~ c u~ WEIGHTED<=99 @7
// Process: u~ s~ > ve ve~ c~ d~ WEIGHTED<=99 @7
// Process: u~ s~ > vm vm~ c~ d~ WEIGHTED<=99 @7
// Process: c~ d~ > ve ve~ u~ s~ WEIGHTED<=99 @7
// Process: c~ d~ > vm vm~ u~ s~ WEIGHTED<=99 @7

// Exception class
class PY8MEs_R7_P1_sm_qq_llqqException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R7_P1_sm_qq_llqq'."; 
  }
}
PY8MEs_R7_P1_sm_qq_llqq_exception; 

std::set<int> PY8MEs_R7_P1_sm_qq_llqq::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R7_P1_sm_qq_llqq::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
    -1, -1}, {-1, -1, -1, -1, -1, 1}, {-1, -1, -1, -1, 1, -1}, {-1, -1, -1, -1,
    1, 1}, {-1, -1, -1, 1, -1, -1}, {-1, -1, -1, 1, -1, 1}, {-1, -1, -1, 1, 1,
    -1}, {-1, -1, -1, 1, 1, 1}, {-1, -1, 1, -1, -1, -1}, {-1, -1, 1, -1, -1,
    1}, {-1, -1, 1, -1, 1, -1}, {-1, -1, 1, -1, 1, 1}, {-1, -1, 1, 1, -1, -1},
    {-1, -1, 1, 1, -1, 1}, {-1, -1, 1, 1, 1, -1}, {-1, -1, 1, 1, 1, 1}, {-1, 1,
    -1, -1, -1, -1}, {-1, 1, -1, -1, -1, 1}, {-1, 1, -1, -1, 1, -1}, {-1, 1,
    -1, -1, 1, 1}, {-1, 1, -1, 1, -1, -1}, {-1, 1, -1, 1, -1, 1}, {-1, 1, -1,
    1, 1, -1}, {-1, 1, -1, 1, 1, 1}, {-1, 1, 1, -1, -1, -1}, {-1, 1, 1, -1, -1,
    1}, {-1, 1, 1, -1, 1, -1}, {-1, 1, 1, -1, 1, 1}, {-1, 1, 1, 1, -1, -1},
    {-1, 1, 1, 1, -1, 1}, {-1, 1, 1, 1, 1, -1}, {-1, 1, 1, 1, 1, 1}, {1, -1,
    -1, -1, -1, -1}, {1, -1, -1, -1, -1, 1}, {1, -1, -1, -1, 1, -1}, {1, -1,
    -1, -1, 1, 1}, {1, -1, -1, 1, -1, -1}, {1, -1, -1, 1, -1, 1}, {1, -1, -1,
    1, 1, -1}, {1, -1, -1, 1, 1, 1}, {1, -1, 1, -1, -1, -1}, {1, -1, 1, -1, -1,
    1}, {1, -1, 1, -1, 1, -1}, {1, -1, 1, -1, 1, 1}, {1, -1, 1, 1, -1, -1}, {1,
    -1, 1, 1, -1, 1}, {1, -1, 1, 1, 1, -1}, {1, -1, 1, 1, 1, 1}, {1, 1, -1, -1,
    -1, -1}, {1, 1, -1, -1, -1, 1}, {1, 1, -1, -1, 1, -1}, {1, 1, -1, -1, 1,
    1}, {1, 1, -1, 1, -1, -1}, {1, 1, -1, 1, -1, 1}, {1, 1, -1, 1, 1, -1}, {1,
    1, -1, 1, 1, 1}, {1, 1, 1, -1, -1, -1}, {1, 1, 1, -1, -1, 1}, {1, 1, 1, -1,
    1, -1}, {1, 1, 1, -1, 1, 1}, {1, 1, 1, 1, -1, -1}, {1, 1, 1, 1, -1, 1}, {1,
    1, 1, 1, 1, -1}, {1, 1, 1, 1, 1, 1}};

// Normalization factors the various processes
// Denominators: spins, colors and identical particles
int PY8MEs_R7_P1_sm_qq_llqq::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9};
int PY8MEs_R7_P1_sm_qq_llqq::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R7_P1_sm_qq_llqq::denom_iden[nprocesses] = {2, 1, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 1,
    2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R7_P1_sm_qq_llqq::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u u > e- e+ u u WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #1
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[0].push_back(0); 

  // Color flows of process Process: u u~ > e- e+ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #1
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[1].push_back(0); 

  // Color flows of process Process: d d > e- e+ d d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: d d~ > e- e+ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #1
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[3].push_back(0); 

  // Color flows of process Process: u~ u~ > e- e+ u~ u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: d~ d~ > e- e+ d~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[5].push_back(0); 

  // Color flows of process Process: u d > e- e+ u d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: u u~ > e- e+ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: u d~ > e- e+ u d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #1
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[8].push_back(0); 

  // Color flows of process Process: d u~ > e- e+ d u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[9].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #1
  color_configs[9].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[9].push_back(0); 

  // Color flows of process Process: d d~ > e- e+ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #1
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[10].push_back(0); 

  // Color flows of process Process: u~ d~ > e- e+ u~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: u c > e- e+ u c WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: u s > e- e+ u s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: u u~ > e- e+ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: u u~ > e- e+ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: u c~ > e- e+ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: u s~ > e- e+ u s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[17].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[17].push_back(0); 
  // JAMP #1
  color_configs[17].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[17].push_back(0); 

  // Color flows of process Process: d s > e- e+ d s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[18].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[18].push_back(0); 
  // JAMP #1
  color_configs[18].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[18].push_back(0); 

  // Color flows of process Process: d c~ > e- e+ d c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[19].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[19].push_back(0); 
  // JAMP #1
  color_configs[19].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[19].push_back(0); 

  // Color flows of process Process: d d~ > e- e+ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[20].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[20].push_back(0); 
  // JAMP #1
  color_configs[20].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[20].push_back(0); 

  // Color flows of process Process: d d~ > e- e+ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[21].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[21].push_back(0); 
  // JAMP #1
  color_configs[21].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[21].push_back(0); 

  // Color flows of process Process: d s~ > e- e+ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[22].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[22].push_back(0); 
  // JAMP #1
  color_configs[22].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[22].push_back(0); 

  // Color flows of process Process: u~ c~ > e- e+ u~ c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[23].push_back(0); 
  // JAMP #1
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[23].push_back(0); 

  // Color flows of process Process: u~ s~ > e- e+ u~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[24].push_back(0); 
  // JAMP #1
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[24].push_back(0); 

  // Color flows of process Process: d~ s~ > e- e+ d~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[25].push_back(0); 
  // JAMP #1
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[25].push_back(0); 

  // Color flows of process Process: u u > ve ve~ u u WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[26].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[26].push_back(0); 
  // JAMP #1
  color_configs[26].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[26].push_back(0); 

  // Color flows of process Process: u u~ > ve ve~ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[27].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[27].push_back(0); 
  // JAMP #1
  color_configs[27].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[27].push_back(0); 

  // Color flows of process Process: d d > ve ve~ d d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[28].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[28].push_back(0); 
  // JAMP #1
  color_configs[28].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[28].push_back(0); 

  // Color flows of process Process: d d~ > ve ve~ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[29].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[29].push_back(0); 
  // JAMP #1
  color_configs[29].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[29].push_back(0); 

  // Color flows of process Process: u~ u~ > ve ve~ u~ u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[30].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[30].push_back(0); 
  // JAMP #1
  color_configs[30].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[30].push_back(0); 

  // Color flows of process Process: d~ d~ > ve ve~ d~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[31].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[31].push_back(0); 
  // JAMP #1
  color_configs[31].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[31].push_back(0); 

  // Color flows of process Process: u u > ve e+ u d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[32].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[32].push_back(0); 
  // JAMP #1
  color_configs[32].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[32].push_back(0); 

  // Color flows of process Process: u d > e- ve~ u u WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[33].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[33].push_back(0); 
  // JAMP #1
  color_configs[33].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[33].push_back(0); 

  // Color flows of process Process: u d > ve e+ d d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[34].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[34].push_back(0); 
  // JAMP #1
  color_configs[34].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[34].push_back(0); 

  // Color flows of process Process: u u~ > e- ve~ u d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[35].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[35].push_back(0); 
  // JAMP #1
  color_configs[35].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[35].push_back(0); 

  // Color flows of process Process: u u~ > ve e+ d u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[36].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[36].push_back(0); 
  // JAMP #1
  color_configs[36].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[36].push_back(0); 

  // Color flows of process Process: u d~ > ve e+ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[37].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[37].push_back(0); 
  // JAMP #1
  color_configs[37].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[37].push_back(0); 

  // Color flows of process Process: u d~ > ve e+ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[38].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[38].push_back(0); 
  // JAMP #1
  color_configs[38].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[38].push_back(0); 

  // Color flows of process Process: d d > e- ve~ u d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[39].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[39].push_back(0); 
  // JAMP #1
  color_configs[39].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[39].push_back(0); 

  // Color flows of process Process: d u~ > e- ve~ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[40].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[40].push_back(0); 
  // JAMP #1
  color_configs[40].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[40].push_back(0); 

  // Color flows of process Process: d u~ > e- ve~ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[41].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[41].push_back(0); 
  // JAMP #1
  color_configs[41].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[41].push_back(0); 

  // Color flows of process Process: d d~ > e- ve~ u d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[42].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[42].push_back(0); 
  // JAMP #1
  color_configs[42].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[42].push_back(0); 

  // Color flows of process Process: d d~ > ve e+ d u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[43].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[43].push_back(0); 
  // JAMP #1
  color_configs[43].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[43].push_back(0); 

  // Color flows of process Process: u~ u~ > e- ve~ u~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[44].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[44].push_back(0); 
  // JAMP #1
  color_configs[44].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[44].push_back(0); 

  // Color flows of process Process: u~ d~ > e- ve~ d~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[45].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[45].push_back(0); 
  // JAMP #1
  color_configs[45].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[45].push_back(0); 

  // Color flows of process Process: u~ d~ > ve e+ u~ u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[46].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[46].push_back(0); 
  // JAMP #1
  color_configs[46].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[46].push_back(0); 

  // Color flows of process Process: d~ d~ > ve e+ u~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[47].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[47].push_back(0); 
  // JAMP #1
  color_configs[47].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[47].push_back(0); 

  // Color flows of process Process: u d > ve ve~ u d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[48].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[48].push_back(0); 
  // JAMP #1
  color_configs[48].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[48].push_back(0); 

  // Color flows of process Process: u u~ > ve ve~ d d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[49].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[49].push_back(0); 
  // JAMP #1
  color_configs[49].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[49].push_back(0); 

  // Color flows of process Process: u d~ > ve ve~ u d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[50].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[50].push_back(0); 
  // JAMP #1
  color_configs[50].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[50].push_back(0); 

  // Color flows of process Process: d u~ > ve ve~ d u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[51].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[51].push_back(0); 
  // JAMP #1
  color_configs[51].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[51].push_back(0); 

  // Color flows of process Process: d d~ > ve ve~ u u~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[52].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[52].push_back(0); 
  // JAMP #1
  color_configs[52].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[52].push_back(0); 

  // Color flows of process Process: u~ d~ > ve ve~ u~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[53].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[53].push_back(0); 
  // JAMP #1
  color_configs[53].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[53].push_back(0); 

  // Color flows of process Process: u c > ve ve~ u c WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[54].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[54].push_back(0); 
  // JAMP #1
  color_configs[54].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[54].push_back(0); 

  // Color flows of process Process: u s > ve ve~ u s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[55].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[55].push_back(0); 
  // JAMP #1
  color_configs[55].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[55].push_back(0); 

  // Color flows of process Process: u u~ > ve ve~ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[56].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[56].push_back(0); 
  // JAMP #1
  color_configs[56].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[56].push_back(0); 

  // Color flows of process Process: u u~ > ve ve~ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[57].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[57].push_back(0); 
  // JAMP #1
  color_configs[57].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[57].push_back(0); 

  // Color flows of process Process: u c~ > ve ve~ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[58].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[58].push_back(0); 
  // JAMP #1
  color_configs[58].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[58].push_back(0); 

  // Color flows of process Process: u s~ > ve ve~ u s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[59].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[59].push_back(0); 
  // JAMP #1
  color_configs[59].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[59].push_back(0); 

  // Color flows of process Process: d s > ve ve~ d s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[60].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[60].push_back(0); 
  // JAMP #1
  color_configs[60].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[60].push_back(0); 

  // Color flows of process Process: d c~ > ve ve~ d c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[61].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[61].push_back(0); 
  // JAMP #1
  color_configs[61].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[61].push_back(0); 

  // Color flows of process Process: d d~ > ve ve~ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[62].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[62].push_back(0); 
  // JAMP #1
  color_configs[62].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[62].push_back(0); 

  // Color flows of process Process: d d~ > ve ve~ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[63].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[63].push_back(0); 
  // JAMP #1
  color_configs[63].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[63].push_back(0); 

  // Color flows of process Process: d s~ > ve ve~ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[64].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[64].push_back(0); 
  // JAMP #1
  color_configs[64].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[64].push_back(0); 

  // Color flows of process Process: u~ c~ > ve ve~ u~ c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[65].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[65].push_back(0); 
  // JAMP #1
  color_configs[65].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[65].push_back(0); 

  // Color flows of process Process: u~ s~ > ve ve~ u~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[66].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[66].push_back(0); 
  // JAMP #1
  color_configs[66].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[66].push_back(0); 

  // Color flows of process Process: d~ s~ > ve ve~ d~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[67].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[67].push_back(0); 
  // JAMP #1
  color_configs[67].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[67].push_back(0); 

  // Color flows of process Process: u c > ve e+ u s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[68].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[68].push_back(0); 
  // JAMP #1
  color_configs[68].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[68].push_back(0); 

  // Color flows of process Process: u c > ve e+ c d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[69].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[69].push_back(0); 
  // JAMP #1
  color_configs[69].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[69].push_back(0); 

  // Color flows of process Process: u s > e- ve~ u c WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[70].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[70].push_back(0); 
  // JAMP #1
  color_configs[70].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[70].push_back(0); 

  // Color flows of process Process: u s > ve e+ d s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[71].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[71].push_back(0); 
  // JAMP #1
  color_configs[71].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[71].push_back(0); 

  // Color flows of process Process: u u~ > e- ve~ c s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[72].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[72].push_back(0); 
  // JAMP #1
  color_configs[72].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[72].push_back(0); 

  // Color flows of process Process: u u~ > ve e+ s c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[73].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[73].push_back(0); 
  // JAMP #1
  color_configs[73].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[73].push_back(0); 

  // Color flows of process Process: u c~ > e- ve~ u s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[74].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[74].push_back(0); 
  // JAMP #1
  color_configs[74].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[74].push_back(0); 

  // Color flows of process Process: u c~ > ve e+ d c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[75].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[75].push_back(0); 
  // JAMP #1
  color_configs[75].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[75].push_back(0); 

  // Color flows of process Process: u d~ > ve e+ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[76].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[76].push_back(0); 
  // JAMP #1
  color_configs[76].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[76].push_back(0); 

  // Color flows of process Process: u d~ > ve e+ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[77].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[77].push_back(0); 
  // JAMP #1
  color_configs[77].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[77].push_back(0); 

  // Color flows of process Process: u s~ > ve e+ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[78].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[78].push_back(0); 
  // JAMP #1
  color_configs[78].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[78].push_back(0); 

  // Color flows of process Process: u s~ > ve e+ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[79].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[79].push_back(0); 
  // JAMP #1
  color_configs[79].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[79].push_back(0); 

  // Color flows of process Process: d s > e- ve~ u s WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[80].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[80].push_back(0); 
  // JAMP #1
  color_configs[80].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[80].push_back(0); 

  // Color flows of process Process: d s > e- ve~ c d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[81].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[81].push_back(0); 
  // JAMP #1
  color_configs[81].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[81].push_back(0); 

  // Color flows of process Process: d u~ > e- ve~ c c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[82].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[82].push_back(0); 
  // JAMP #1
  color_configs[82].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[82].push_back(0); 

  // Color flows of process Process: d u~ > e- ve~ s s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[83].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[83].push_back(0); 
  // JAMP #1
  color_configs[83].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[83].push_back(0); 

  // Color flows of process Process: d c~ > e- ve~ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[84].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[84].push_back(0); 
  // JAMP #1
  color_configs[84].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[84].push_back(0); 

  // Color flows of process Process: d c~ > e- ve~ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[85].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[85].push_back(0); 
  // JAMP #1
  color_configs[85].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[85].push_back(0); 

  // Color flows of process Process: d d~ > e- ve~ c s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[86].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[86].push_back(0); 
  // JAMP #1
  color_configs[86].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[86].push_back(0); 

  // Color flows of process Process: d d~ > ve e+ s c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[87].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[87].push_back(0); 
  // JAMP #1
  color_configs[87].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[87].push_back(0); 

  // Color flows of process Process: d s~ > e- ve~ u s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[88].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[88].push_back(0); 
  // JAMP #1
  color_configs[88].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[88].push_back(0); 

  // Color flows of process Process: d s~ > ve e+ d c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[89].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[89].push_back(0); 
  // JAMP #1
  color_configs[89].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[89].push_back(0); 

  // Color flows of process Process: u~ c~ > e- ve~ u~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[90].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[90].push_back(0); 
  // JAMP #1
  color_configs[90].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[90].push_back(0); 

  // Color flows of process Process: u~ c~ > e- ve~ c~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[91].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[91].push_back(0); 
  // JAMP #1
  color_configs[91].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[91].push_back(0); 

  // Color flows of process Process: u~ s~ > e- ve~ d~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[92].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[92].push_back(0); 
  // JAMP #1
  color_configs[92].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[92].push_back(0); 

  // Color flows of process Process: u~ s~ > ve e+ u~ c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[93].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[93].push_back(0); 
  // JAMP #1
  color_configs[93].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[93].push_back(0); 

  // Color flows of process Process: d~ s~ > ve e+ u~ s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[94].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[94].push_back(0); 
  // JAMP #1
  color_configs[94].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[94].push_back(0); 

  // Color flows of process Process: d~ s~ > ve e+ c~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[95].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[95].push_back(0); 
  // JAMP #1
  color_configs[95].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[95].push_back(0); 

  // Color flows of process Process: u s > e- e+ c d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[96].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[96].push_back(0); 

  // Color flows of process Process: u c~ > e- e+ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[97].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[97].push_back(0); 

  // Color flows of process Process: u d~ > e- e+ c s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[98].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[98].push_back(0); 

  // Color flows of process Process: d u~ > e- e+ s c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[99].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[99].push_back(0); 

  // Color flows of process Process: d s~ > e- e+ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[100].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[100].push_back(0); 

  // Color flows of process Process: u~ s~ > e- e+ c~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[101].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[101].push_back(0); 

  // Color flows of process Process: u s > ve ve~ c d WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[102].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[102].push_back(0); 

  // Color flows of process Process: u c~ > ve ve~ d s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[103].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[103].push_back(0); 

  // Color flows of process Process: u d~ > ve ve~ c s~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[104].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[104].push_back(0); 

  // Color flows of process Process: d u~ > ve ve~ s c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[105].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[105].push_back(0); 

  // Color flows of process Process: d s~ > ve ve~ u c~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[106].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[106].push_back(0); 

  // Color flows of process Process: u~ s~ > ve ve~ c~ d~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[107].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[107].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R7_P1_sm_qq_llqq::~PY8MEs_R7_P1_sm_qq_llqq() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R7_P1_sm_qq_llqq::invert_mapping(vector<int> mapping) 
{
  vector<int> inverted_mapping; 
  for (unsigned int i = 0; i < mapping.size(); i++ )
  {
    for (unsigned int j = 0; j < mapping.size(); j++ )
    {
      if (mapping[j] == ((int)i))
      {
        inverted_mapping.push_back(j); 
        break; 
      }
    }
  }
  return inverted_mapping; 
}

//--------------------------------------------------------------------------
// Return the list of possible helicity configurations
vector < vec_int > PY8MEs_R7_P1_sm_qq_llqq::getHelicityConfigs(vector<int>
    permutation)
{
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = perm; 
  }
  else
  {
    chosenPerm = permutation; 
  }
  vector < vec_int > res(ncomb, vector<int> (nexternal, 0)); 
  for (unsigned int ihel = 0; ihel < ncomb; ihel++ )
  {
    for(unsigned int j = 0; j < nexternal; j++ )
    {
      res[ihel][chosenPerm[j]] = helicities[ihel][j]; 
    }
  }
  return res; 
}

//--------------------------------------------------------------------------
// Return the list of possible color configurations
vector < vec_int > PY8MEs_R7_P1_sm_qq_llqq::getColorConfigs(int
    specify_proc_ID, vector<int> permutation)
{
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = perm; 
  }
  else
  {
    chosenPerm = permutation; 
  }
  vector < vec_int > res(color_configs[chosenProcID].size(), vector<int>
      (nexternal * 2, 0));
  for (unsigned int icol = 0; icol < color_configs[chosenProcID].size(); icol++
      )
  {
    for(unsigned int j = 0; j < (2 * nexternal); j++ )
    {
      res[icol][chosenPerm[j/2] * 2 + j%2] =
          color_configs[chosenProcID][icol][j];
    }
  }
  return res; 
}

//--------------------------------------------------------------------------
// Get JAMP relative N_c power
int PY8MEs_R7_P1_sm_qq_llqq::getColorFlowRelativeNCPower(int color_flow_ID, int
    specify_proc_ID)
{
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  return jamp_nc_relative_power[chosenProcID][color_flow_ID]; 
}

//--------------------------------------------------------------------------
// Implements the map Helicity ID -> Helicity Config
vector<int> PY8MEs_R7_P1_sm_qq_llqq::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = perm; 
  }
  else
  {
    chosenPerm = permutation; 
  }
  vector<int> res(nexternal, 0); 
  for (unsigned int j = 0; j < nexternal; j++ )
  {
    res[chosenPerm[j]] = helicities[hel_ID][j]; 
  }
  return res; 
}

//--------------------------------------------------------------------------
// Implements the map Helicity Config -> Helicity ID
int PY8MEs_R7_P1_sm_qq_llqq::getHelicityIDForConfig(vector<int> hel_config,
    vector<int> permutation)
{
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = invert_mapping(perm); 
  }
  else
  {
    chosenPerm = invert_mapping(permutation); 
  }
  int user_ihel = -1; 
  if (hel_config.size() > 0)
  {
    bool found = false; 
    for(unsigned int i = 0; i < ncomb; i++ )
    {
      found = true; 
      for (unsigned int j = 0; j < nexternal; j++ )
      {
        if (helicities[i][chosenPerm[j]] != hel_config[j])
        {
          found = false; 
          break; 
        }
      }
      if ( !found)
        continue; 
      else
      {
        user_ihel = i; 
        break; 
      }
    }
    if (user_ihel == -1)
    {
      cerr <<  "Error in function 'getHelicityIDForConfig' of class" << 
      " 'PY8MEs_R7_P1_sm_qq_llqq': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R7_P1_sm_qq_llqq::getColorConfigForID(int color_ID, int
    specify_proc_ID, vector<int> permutation)
{
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  if (color_ID < 0 || color_ID >= int(color_configs[chosenProcID].size()))
  {
    cerr <<  "Error in function 'getColorConfigForID' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = perm; 
  }
  else
  {
    chosenPerm = permutation; 
  }
  vector<int> res(color_configs[chosenProcID][color_ID].size(), 0); 
  for (unsigned int j = 0; j < (2 * nexternal); j++ )
  {
    res[chosenPerm[j/2] * 2 + j%2] = color_configs[chosenProcID][color_ID][j]; 
  }
  return res; 
}

//--------------------------------------------------------------------------
// Implements the map Color Config -> Color ID
int PY8MEs_R7_P1_sm_qq_llqq::getColorIDForConfig(vector<int> color_config, int
    specify_proc_ID, vector<int> permutation)
{
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  vector<int> chosenPerm; 
  if (permutation.size() == 0)
  {
    chosenPerm = invert_mapping(perm); 
  }
  else
  {
    chosenPerm = invert_mapping(permutation); 
  }
  // Find which color configuration is asked for
  // -1 indicates one wants to sum over all color configurations
  int user_icol = -1; 
  if (color_config.size() > 0)
  {
    bool found = false; 
    for(unsigned int i = 0; i < color_configs[chosenProcID].size(); i++ )
    {
      found = true; 
      for (unsigned int j = 0; j < (nexternal * 2); j++ )
      {

        // If colorless then make sure it matches
        // The little arithmetics in the color index is just
        // the permutation applies on the particle list which is
        // twice smaller since each particle can have two color indices.
        if (color_config[j] == 0)
        {
          if (color_configs[chosenProcID][i][chosenPerm[j/2] * 2 + j%2] != 0)
          {
            found = false; 
            break; 
          }
          // Otherwise check that the color linked position matches
        }
        else
        {
          int color_linked_pos = -1; 
          // Find the other end of the line in the user color config
          for (unsigned int k = 0; k < (nexternal * 2); k++ )
          {
            if (k == j)
              continue; 
            if (color_config[j] == color_config[k])
            {
              color_linked_pos = k; 
              break; 
            }
          }
          if (color_linked_pos == -1)
          {
            cerr <<  "Error in function 'getColorIDForConfig' of class" << 
            " 'PY8MEs_R7_P1_sm_qq_llqq': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
          }
          // Now check whether the color line matches
          if (color_configs[chosenProcID][i][chosenPerm[j/2] * 2 + j%2] !=
              color_configs[chosenProcID][i][chosenPerm[color_linked_pos/2] * 2
              + color_linked_pos%2])
          {
            found = false; 
            break; 
          }
        }
      }
      if ( !found)
        continue; 
      else
      {
        user_icol = i; 
        break; 
      }
    }

    if (user_icol == -1)
    {
      cerr <<  "Error in function 'getColorIDForConfig' of class" << 
      " 'PY8MEs_R7_P1_sm_qq_llqq': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R7_P1_sm_qq_llqq::getAllResults(int
    specify_proc_ID)
{
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  return all_results[chosenProcID]; 
}

//--------------------------------------------------------------------------
// Returns a result previously computed in SigmaKin for a specific helicity
// and color ID. -1 means avg and summed over that characteristic.
double PY8MEs_R7_P1_sm_qq_llqq::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  int chosenProcID = -1; 
  if (specify_proc_ID == -1)
  {
    chosenProcID = proc_ID; 
  }
  else
  {
    chosenProcID = specify_proc_ID; 
  }
  if (color_ID < - 1 || color_ID >= int(color_configs[chosenProcID].size()))
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R7_P1_sm_qq_llqq::static_getPY8ME(vector<int>
    initial_pdgs, vector<int> final_pdgs, set<int> schannels)
{

  // Not available return value
  pair < vector<int> , int > NA(vector<int> (), -1); 

  // Check if s-channel requirements match
  if (nreq_s_channels > 0)
  {
    if (schannels != s_channel_proc)
      return NA; 
  }
  else
  {
    if (schannels.size() != 0)
      return NA; 
  }

  // Check number of final state particles
  if (final_pdgs.size() != (nexternal - ninitial))
    return NA; 

  // Check number of initial state particles
  if (initial_pdgs.size() != ninitial)
    return NA; 

  // List of processes available in this class
  const int nprocs = 752; 
  const int proc_IDS[nprocs] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
      4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9,
      10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14,
      15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 19, 19, 19, 19,
      20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 24, 24, 24, 24,
      25, 25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 29,
      30, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 34, 34,
      34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 38,
      39, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42, 43, 43,
      43, 43, 44, 44, 44, 44, 45, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 47,
      48, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52,
      52, 52, 53, 53, 53, 53, 54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57,
      57, 57, 58, 58, 58, 58, 59, 59, 59, 59, 60, 60, 61, 61, 61, 61, 62, 62,
      62, 62, 63, 63, 63, 63, 64, 64, 64, 64, 65, 65, 66, 66, 66, 66, 67, 67,
      68, 68, 69, 69, 70, 70, 70, 70, 71, 71, 71, 71, 72, 72, 72, 72, 73, 73,
      73, 73, 74, 74, 74, 74, 75, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77,
      78, 78, 78, 78, 79, 79, 79, 79, 80, 80, 81, 81, 82, 82, 82, 82, 83, 83,
      83, 83, 84, 84, 84, 84, 85, 85, 85, 85, 86, 86, 86, 86, 87, 87, 87, 87,
      88, 88, 88, 88, 89, 89, 89, 89, 90, 90, 91, 91, 92, 92, 92, 92, 93, 93,
      93, 93, 94, 94, 95, 95, 96, 96, 96, 96, 97, 97, 97, 97, 98, 98, 98, 98,
      99, 99, 99, 99, 100, 100, 100, 100, 101, 101, 101, 101, 102, 102, 102,
      102, 103, 103, 103, 103, 104, 104, 104, 104, 105, 105, 105, 105, 106,
      106, 106, 106, 107, 107, 107, 107, 1, 1, 1, 1, 3, 3, 3, 3, 6, 6, 6, 6, 7,
      7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12,
      13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17,
      17, 17, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22,
      22, 22, 23, 23, 24, 24, 24, 24, 25, 25, 27, 27, 27, 27, 29, 29, 29, 29,
      33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37,
      37, 37, 38, 38, 38, 38, 40, 40, 40, 40, 41, 41, 41, 41, 42, 42, 42, 42,
      43, 43, 43, 43, 45, 45, 45, 45, 46, 46, 46, 46, 48, 48, 48, 48, 49, 49,
      49, 49, 50, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 52, 53, 53, 53, 53,
      54, 54, 55, 55, 55, 55, 56, 56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 58,
      59, 59, 59, 59, 60, 60, 61, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63,
      64, 64, 64, 64, 65, 65, 66, 66, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70,
      70, 70, 71, 71, 71, 71, 72, 72, 72, 72, 73, 73, 73, 73, 74, 74, 74, 74,
      75, 75, 75, 75, 76, 76, 76, 76, 77, 77, 77, 77, 78, 78, 78, 78, 79, 79,
      79, 79, 80, 80, 81, 81, 82, 82, 82, 82, 83, 83, 83, 83, 84, 84, 84, 84,
      85, 85, 85, 85, 86, 86, 86, 86, 87, 87, 87, 87, 88, 88, 88, 88, 89, 89,
      89, 89, 90, 90, 91, 91, 92, 92, 92, 92, 93, 93, 93, 93, 94, 94, 95, 95,
      96, 96, 96, 96, 97, 97, 97, 97, 98, 98, 98, 98, 99, 99, 99, 99, 100, 100,
      100, 100, 101, 101, 101, 101, 102, 102, 102, 102, 103, 103, 103, 103,
      104, 104, 104, 104, 105, 105, 105, 105, 106, 106, 106, 106, 107, 107,
      107, 107};
  const int in_pdgs[nprocs][ninitial] = {{2, 2}, {2, 2}, {4, 4}, {4, 4}, {2,
      -2}, {2, -2}, {4, -4}, {4, -4}, {1, 1}, {1, 1}, {3, 3}, {3, 3}, {1, -1},
      {1, -1}, {3, -3}, {3, -3}, {-2, -2}, {-2, -2}, {-4, -4}, {-4, -4}, {-1,
      -1}, {-1, -1}, {-3, -3}, {-3, -3}, {2, 1}, {2, 1}, {4, 3}, {4, 3}, {2,
      -2}, {2, -2}, {4, -4}, {4, -4}, {2, -1}, {2, -1}, {4, -3}, {4, -3}, {1,
      -2}, {1, -2}, {3, -4}, {3, -4}, {1, -1}, {1, -1}, {3, -3}, {3, -3}, {-2,
      -1}, {-2, -1}, {-4, -3}, {-4, -3}, {2, 4}, {2, 4}, {2, 3}, {2, 3}, {4,
      1}, {4, 1}, {2, -2}, {2, -2}, {4, -4}, {4, -4}, {2, -2}, {2, -2}, {4,
      -4}, {4, -4}, {2, -4}, {2, -4}, {4, -2}, {4, -2}, {2, -3}, {2, -3}, {4,
      -1}, {4, -1}, {1, 3}, {1, 3}, {1, -4}, {1, -4}, {3, -2}, {3, -2}, {1,
      -1}, {1, -1}, {3, -3}, {3, -3}, {1, -1}, {1, -1}, {3, -3}, {3, -3}, {1,
      -3}, {1, -3}, {3, -1}, {3, -1}, {-2, -4}, {-2, -4}, {-2, -3}, {-2, -3},
      {-4, -1}, {-4, -1}, {-1, -3}, {-1, -3}, {2, 2}, {2, 2}, {4, 4}, {4, 4},
      {2, -2}, {2, -2}, {4, -4}, {4, -4}, {1, 1}, {1, 1}, {3, 3}, {3, 3}, {1,
      -1}, {1, -1}, {3, -3}, {3, -3}, {-2, -2}, {-2, -2}, {-4, -4}, {-4, -4},
      {-1, -1}, {-1, -1}, {-3, -3}, {-3, -3}, {2, 2}, {2, 2}, {4, 4}, {4, 4},
      {2, 1}, {2, 1}, {4, 3}, {4, 3}, {2, 1}, {2, 1}, {4, 3}, {4, 3}, {2, -2},
      {2, -2}, {4, -4}, {4, -4}, {2, -2}, {2, -2}, {4, -4}, {4, -4}, {2, -1},
      {2, -1}, {4, -3}, {4, -3}, {2, -1}, {2, -1}, {4, -3}, {4, -3}, {1, 1},
      {1, 1}, {3, 3}, {3, 3}, {1, -2}, {1, -2}, {3, -4}, {3, -4}, {1, -2}, {1,
      -2}, {3, -4}, {3, -4}, {1, -1}, {1, -1}, {3, -3}, {3, -3}, {1, -1}, {1,
      -1}, {3, -3}, {3, -3}, {-2, -2}, {-2, -2}, {-4, -4}, {-4, -4}, {-2, -1},
      {-2, -1}, {-4, -3}, {-4, -3}, {-2, -1}, {-2, -1}, {-4, -3}, {-4, -3},
      {-1, -1}, {-1, -1}, {-3, -3}, {-3, -3}, {2, 1}, {2, 1}, {4, 3}, {4, 3},
      {2, -2}, {2, -2}, {4, -4}, {4, -4}, {2, -1}, {2, -1}, {4, -3}, {4, -3},
      {1, -2}, {1, -2}, {3, -4}, {3, -4}, {1, -1}, {1, -1}, {3, -3}, {3, -3},
      {-2, -1}, {-2, -1}, {-4, -3}, {-4, -3}, {2, 4}, {2, 4}, {2, 3}, {2, 3},
      {4, 1}, {4, 1}, {2, -2}, {2, -2}, {4, -4}, {4, -4}, {2, -2}, {2, -2}, {4,
      -4}, {4, -4}, {2, -4}, {2, -4}, {4, -2}, {4, -2}, {2, -3}, {2, -3}, {4,
      -1}, {4, -1}, {1, 3}, {1, 3}, {1, -4}, {1, -4}, {3, -2}, {3, -2}, {1,
      -1}, {1, -1}, {3, -3}, {3, -3}, {1, -1}, {1, -1}, {3, -3}, {3, -3}, {1,
      -3}, {1, -3}, {3, -1}, {3, -1}, {-2, -4}, {-2, -4}, {-2, -3}, {-2, -3},
      {-4, -1}, {-4, -1}, {-1, -3}, {-1, -3}, {2, 4}, {2, 4}, {2, 4}, {2, 4},
      {2, 3}, {2, 3}, {4, 1}, {4, 1}, {2, 3}, {2, 3}, {4, 1}, {4, 1}, {2, -2},
      {2, -2}, {4, -4}, {4, -4}, {2, -2}, {2, -2}, {4, -4}, {4, -4}, {2, -4},
      {2, -4}, {4, -2}, {4, -2}, {2, -4}, {2, -4}, {4, -2}, {4, -2}, {2, -1},
      {2, -1}, {4, -3}, {4, -3}, {2, -1}, {2, -1}, {4, -3}, {4, -3}, {2, -3},
      {2, -3}, {4, -1}, {4, -1}, {2, -3}, {2, -3}, {4, -1}, {4, -1}, {1, 3},
      {1, 3}, {1, 3}, {1, 3}, {1, -2}, {1, -2}, {3, -4}, {3, -4}, {1, -2}, {1,
      -2}, {3, -4}, {3, -4}, {1, -4}, {1, -4}, {3, -2}, {3, -2}, {1, -4}, {1,
      -4}, {3, -2}, {3, -2}, {1, -1}, {1, -1}, {3, -3}, {3, -3}, {1, -1}, {1,
      -1}, {3, -3}, {3, -3}, {1, -3}, {1, -3}, {3, -1}, {3, -1}, {1, -3}, {1,
      -3}, {3, -1}, {3, -1}, {-2, -4}, {-2, -4}, {-2, -4}, {-2, -4}, {-2, -3},
      {-2, -3}, {-4, -1}, {-4, -1}, {-2, -3}, {-2, -3}, {-4, -1}, {-4, -1},
      {-1, -3}, {-1, -3}, {-1, -3}, {-1, -3}, {2, 3}, {2, 3}, {4, 1}, {4, 1},
      {2, -4}, {2, -4}, {4, -2}, {4, -2}, {2, -1}, {2, -1}, {4, -3}, {4, -3},
      {1, -2}, {1, -2}, {3, -4}, {3, -4}, {1, -3}, {1, -3}, {3, -1}, {3, -1},
      {-2, -3}, {-2, -3}, {-4, -1}, {-4, -1}, {2, 3}, {2, 3}, {4, 1}, {4, 1},
      {2, -4}, {2, -4}, {4, -2}, {4, -2}, {2, -1}, {2, -1}, {4, -3}, {4, -3},
      {1, -2}, {1, -2}, {3, -4}, {3, -4}, {1, -3}, {1, -3}, {3, -1}, {3, -1},
      {-2, -3}, {-2, -3}, {-4, -1}, {-4, -1}, {-2, 2}, {-2, 2}, {-4, 4}, {-4,
      4}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {1, 2}, {1, 2}, {3, 4}, {3, 4},
      {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3, 4},
      {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3},
      {-1, -2}, {-1, -2}, {-3, -4}, {-3, -4}, {4, 2}, {4, 2}, {3, 2}, {3, 2},
      {1, 4}, {1, 4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-2, 2}, {-2, 2},
      {-4, 4}, {-4, 4}, {-4, 2}, {-4, 2}, {-2, 4}, {-2, 4}, {-3, 2}, {-3, 2},
      {-1, 4}, {-1, 4}, {3, 1}, {3, 1}, {-4, 1}, {-4, 1}, {-2, 3}, {-2, 3},
      {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3},
      {-3, 1}, {-3, 1}, {-1, 3}, {-1, 3}, {-4, -2}, {-4, -2}, {-3, -2}, {-3,
      -2}, {-1, -4}, {-1, -4}, {-3, -1}, {-3, -1}, {-2, 2}, {-2, 2}, {-4, 4},
      {-4, 4}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {1, 2}, {1, 2}, {3, 4}, {3,
      4}, {1, 2}, {1, 2}, {3, 4}, {3, 4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4},
      {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3, 4},
      {-1, 2}, {-1, 2}, {-3, 4}, {-3, 4}, {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3},
      {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3},
      {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-1, -2}, {-1, -2}, {-3, -4}, {-3,
      -4}, {-1, -2}, {-1, -2}, {-3, -4}, {-3, -4}, {1, 2}, {1, 2}, {3, 4}, {3,
      4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3,
      4}, {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3,
      3}, {-1, -2}, {-1, -2}, {-3, -4}, {-3, -4}, {4, 2}, {4, 2}, {3, 2}, {3,
      2}, {1, 4}, {1, 4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-2, 2}, {-2, 2},
      {-4, 4}, {-4, 4}, {-4, 2}, {-4, 2}, {-2, 4}, {-2, 4}, {-3, 2}, {-3, 2},
      {-1, 4}, {-1, 4}, {3, 1}, {3, 1}, {-4, 1}, {-4, 1}, {-2, 3}, {-2, 3},
      {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3},
      {-3, 1}, {-3, 1}, {-1, 3}, {-1, 3}, {-4, -2}, {-4, -2}, {-3, -2}, {-3,
      -2}, {-1, -4}, {-1, -4}, {-3, -1}, {-3, -1}, {4, 2}, {4, 2}, {4, 2}, {4,
      2}, {3, 2}, {3, 2}, {1, 4}, {1, 4}, {3, 2}, {3, 2}, {1, 4}, {1, 4}, {-2,
      2}, {-2, 2}, {-4, 4}, {-4, 4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4}, {-4,
      2}, {-4, 2}, {-2, 4}, {-2, 4}, {-4, 2}, {-4, 2}, {-2, 4}, {-2, 4}, {-1,
      2}, {-1, 2}, {-3, 4}, {-3, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3, 4}, {-3,
      2}, {-3, 2}, {-1, 4}, {-1, 4}, {-3, 2}, {-3, 2}, {-1, 4}, {-1, 4}, {3,
      1}, {3, 1}, {3, 1}, {3, 1}, {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-2, 1},
      {-2, 1}, {-4, 3}, {-4, 3}, {-4, 1}, {-4, 1}, {-2, 3}, {-2, 3}, {-4, 1},
      {-4, 1}, {-2, 3}, {-2, 3}, {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-1, 1},
      {-1, 1}, {-3, 3}, {-3, 3}, {-3, 1}, {-3, 1}, {-1, 3}, {-1, 3}, {-3, 1},
      {-3, 1}, {-1, 3}, {-1, 3}, {-4, -2}, {-4, -2}, {-4, -2}, {-4, -2}, {-3,
      -2}, {-3, -2}, {-1, -4}, {-1, -4}, {-3, -2}, {-3, -2}, {-1, -4}, {-1,
      -4}, {-3, -1}, {-3, -1}, {-3, -1}, {-3, -1}, {3, 2}, {3, 2}, {1, 4}, {1,
      4}, {-4, 2}, {-4, 2}, {-2, 4}, {-2, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3,
      4}, {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-3, 1}, {-3, 1}, {-1, 3}, {-1,
      3}, {-3, -2}, {-3, -2}, {-1, -4}, {-1, -4}, {3, 2}, {3, 2}, {1, 4}, {1,
      4}, {-4, 2}, {-4, 2}, {-2, 4}, {-2, 4}, {-1, 2}, {-1, 2}, {-3, 4}, {-3,
      4}, {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}, {-3, 1}, {-3, 1}, {-1, 3}, {-1,
      3}, {-3, -2}, {-3, -2}, {-1, -4}, {-1, -4}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{11, -11, 2, 2}, {13,
      -13, 2, 2}, {11, -11, 4, 4}, {13, -13, 4, 4}, {11, -11, 2, -2}, {13, -13,
      2, -2}, {11, -11, 4, -4}, {13, -13, 4, -4}, {11, -11, 1, 1}, {13, -13, 1,
      1}, {11, -11, 3, 3}, {13, -13, 3, 3}, {11, -11, 1, -1}, {13, -13, 1, -1},
      {11, -11, 3, -3}, {13, -13, 3, -3}, {11, -11, -2, -2}, {13, -13, -2, -2},
      {11, -11, -4, -4}, {13, -13, -4, -4}, {11, -11, -1, -1}, {13, -13, -1,
      -1}, {11, -11, -3, -3}, {13, -13, -3, -3}, {11, -11, 2, 1}, {13, -13, 2,
      1}, {11, -11, 4, 3}, {13, -13, 4, 3}, {11, -11, 1, -1}, {13, -13, 1, -1},
      {11, -11, 3, -3}, {13, -13, 3, -3}, {11, -11, 2, -1}, {13, -13, 2, -1},
      {11, -11, 4, -3}, {13, -13, 4, -3}, {11, -11, 1, -2}, {13, -13, 1, -2},
      {11, -11, 3, -4}, {13, -13, 3, -4}, {11, -11, 2, -2}, {13, -13, 2, -2},
      {11, -11, 4, -4}, {13, -13, 4, -4}, {11, -11, -2, -1}, {13, -13, -2, -1},
      {11, -11, -4, -3}, {13, -13, -4, -3}, {11, -11, 2, 4}, {13, -13, 2, 4},
      {11, -11, 2, 3}, {13, -13, 2, 3}, {11, -11, 4, 1}, {13, -13, 4, 1}, {11,
      -11, 4, -4}, {13, -13, 4, -4}, {11, -11, 2, -2}, {13, -13, 2, -2}, {11,
      -11, 3, -3}, {13, -13, 3, -3}, {11, -11, 1, -1}, {13, -13, 1, -1}, {11,
      -11, 2, -4}, {13, -13, 2, -4}, {11, -11, 4, -2}, {13, -13, 4, -2}, {11,
      -11, 2, -3}, {13, -13, 2, -3}, {11, -11, 4, -1}, {13, -13, 4, -1}, {11,
      -11, 1, 3}, {13, -13, 1, 3}, {11, -11, 1, -4}, {13, -13, 1, -4}, {11,
      -11, 3, -2}, {13, -13, 3, -2}, {11, -11, 4, -4}, {13, -13, 4, -4}, {11,
      -11, 2, -2}, {13, -13, 2, -2}, {11, -11, 3, -3}, {13, -13, 3, -3}, {11,
      -11, 1, -1}, {13, -13, 1, -1}, {11, -11, 1, -3}, {13, -13, 1, -3}, {11,
      -11, 3, -1}, {13, -13, 3, -1}, {11, -11, -2, -4}, {13, -13, -2, -4}, {11,
      -11, -2, -3}, {13, -13, -2, -3}, {11, -11, -4, -1}, {13, -13, -4, -1},
      {11, -11, -1, -3}, {13, -13, -1, -3}, {12, -12, 2, 2}, {14, -14, 2, 2},
      {12, -12, 4, 4}, {14, -14, 4, 4}, {12, -12, 2, -2}, {14, -14, 2, -2},
      {12, -12, 4, -4}, {14, -14, 4, -4}, {12, -12, 1, 1}, {14, -14, 1, 1},
      {12, -12, 3, 3}, {14, -14, 3, 3}, {12, -12, 1, -1}, {14, -14, 1, -1},
      {12, -12, 3, -3}, {14, -14, 3, -3}, {12, -12, -2, -2}, {14, -14, -2, -2},
      {12, -12, -4, -4}, {14, -14, -4, -4}, {12, -12, -1, -1}, {14, -14, -1,
      -1}, {12, -12, -3, -3}, {14, -14, -3, -3}, {12, -11, 2, 1}, {14, -13, 2,
      1}, {12, -11, 4, 3}, {14, -13, 4, 3}, {11, -12, 2, 2}, {13, -14, 2, 2},
      {11, -12, 4, 4}, {13, -14, 4, 4}, {12, -11, 1, 1}, {14, -13, 1, 1}, {12,
      -11, 3, 3}, {14, -13, 3, 3}, {11, -12, 2, -1}, {13, -14, 2, -1}, {11,
      -12, 4, -3}, {13, -14, 4, -3}, {12, -11, 1, -2}, {14, -13, 1, -2}, {12,
      -11, 3, -4}, {14, -13, 3, -4}, {12, -11, 2, -2}, {14, -13, 2, -2}, {12,
      -11, 4, -4}, {14, -13, 4, -4}, {12, -11, 1, -1}, {14, -13, 1, -1}, {12,
      -11, 3, -3}, {14, -13, 3, -3}, {11, -12, 2, 1}, {13, -14, 2, 1}, {11,
      -12, 4, 3}, {13, -14, 4, 3}, {11, -12, 2, -2}, {13, -14, 2, -2}, {11,
      -12, 4, -4}, {13, -14, 4, -4}, {11, -12, 1, -1}, {13, -14, 1, -1}, {11,
      -12, 3, -3}, {13, -14, 3, -3}, {11, -12, 2, -1}, {13, -14, 2, -1}, {11,
      -12, 4, -3}, {13, -14, 4, -3}, {12, -11, 1, -2}, {14, -13, 1, -2}, {12,
      -11, 3, -4}, {14, -13, 3, -4}, {11, -12, -2, -1}, {13, -14, -2, -1}, {11,
      -12, -4, -3}, {13, -14, -4, -3}, {11, -12, -1, -1}, {13, -14, -1, -1},
      {11, -12, -3, -3}, {13, -14, -3, -3}, {12, -11, -2, -2}, {14, -13, -2,
      -2}, {12, -11, -4, -4}, {14, -13, -4, -4}, {12, -11, -2, -1}, {14, -13,
      -2, -1}, {12, -11, -4, -3}, {14, -13, -4, -3}, {12, -12, 2, 1}, {14, -14,
      2, 1}, {12, -12, 4, 3}, {14, -14, 4, 3}, {12, -12, 1, -1}, {14, -14, 1,
      -1}, {12, -12, 3, -3}, {14, -14, 3, -3}, {12, -12, 2, -1}, {14, -14, 2,
      -1}, {12, -12, 4, -3}, {14, -14, 4, -3}, {12, -12, 1, -2}, {14, -14, 1,
      -2}, {12, -12, 3, -4}, {14, -14, 3, -4}, {12, -12, 2, -2}, {14, -14, 2,
      -2}, {12, -12, 4, -4}, {14, -14, 4, -4}, {12, -12, -2, -1}, {14, -14, -2,
      -1}, {12, -12, -4, -3}, {14, -14, -4, -3}, {12, -12, 2, 4}, {14, -14, 2,
      4}, {12, -12, 2, 3}, {14, -14, 2, 3}, {12, -12, 4, 1}, {14, -14, 4, 1},
      {12, -12, 4, -4}, {14, -14, 4, -4}, {12, -12, 2, -2}, {14, -14, 2, -2},
      {12, -12, 3, -3}, {14, -14, 3, -3}, {12, -12, 1, -1}, {14, -14, 1, -1},
      {12, -12, 2, -4}, {14, -14, 2, -4}, {12, -12, 4, -2}, {14, -14, 4, -2},
      {12, -12, 2, -3}, {14, -14, 2, -3}, {12, -12, 4, -1}, {14, -14, 4, -1},
      {12, -12, 1, 3}, {14, -14, 1, 3}, {12, -12, 1, -4}, {14, -14, 1, -4},
      {12, -12, 3, -2}, {14, -14, 3, -2}, {12, -12, 4, -4}, {14, -14, 4, -4},
      {12, -12, 2, -2}, {14, -14, 2, -2}, {12, -12, 3, -3}, {14, -14, 3, -3},
      {12, -12, 1, -1}, {14, -14, 1, -1}, {12, -12, 1, -3}, {14, -14, 1, -3},
      {12, -12, 3, -1}, {14, -14, 3, -1}, {12, -12, -2, -4}, {14, -14, -2, -4},
      {12, -12, -2, -3}, {14, -14, -2, -3}, {12, -12, -4, -1}, {14, -14, -4,
      -1}, {12, -12, -1, -3}, {14, -14, -1, -3}, {12, -11, 2, 3}, {14, -13, 2,
      3}, {12, -11, 4, 1}, {14, -13, 4, 1}, {11, -12, 2, 4}, {13, -14, 2, 4},
      {11, -12, 4, 2}, {13, -14, 4, 2}, {12, -11, 1, 3}, {14, -13, 1, 3}, {12,
      -11, 3, 1}, {14, -13, 3, 1}, {11, -12, 4, -3}, {13, -14, 4, -3}, {11,
      -12, 2, -1}, {13, -14, 2, -1}, {12, -11, 3, -4}, {14, -13, 3, -4}, {12,
      -11, 1, -2}, {14, -13, 1, -2}, {11, -12, 2, -3}, {13, -14, 2, -3}, {11,
      -12, 4, -1}, {13, -14, 4, -1}, {12, -11, 1, -4}, {14, -13, 1, -4}, {12,
      -11, 3, -2}, {14, -13, 3, -2}, {12, -11, 4, -4}, {14, -13, 4, -4}, {12,
      -11, 2, -2}, {14, -13, 2, -2}, {12, -11, 3, -3}, {14, -13, 3, -3}, {12,
      -11, 1, -1}, {14, -13, 1, -1}, {12, -11, 2, -4}, {14, -13, 2, -4}, {12,
      -11, 4, -2}, {14, -13, 4, -2}, {12, -11, 1, -3}, {14, -13, 1, -3}, {12,
      -11, 3, -1}, {14, -13, 3, -1}, {11, -12, 2, 3}, {13, -14, 2, 3}, {11,
      -12, 4, 1}, {13, -14, 4, 1}, {11, -12, 4, -4}, {13, -14, 4, -4}, {11,
      -12, 2, -2}, {13, -14, 2, -2}, {11, -12, 3, -3}, {13, -14, 3, -3}, {11,
      -12, 1, -1}, {13, -14, 1, -1}, {11, -12, 2, -4}, {13, -14, 2, -4}, {11,
      -12, 4, -2}, {13, -14, 4, -2}, {11, -12, 1, -3}, {13, -14, 1, -3}, {11,
      -12, 3, -1}, {13, -14, 3, -1}, {11, -12, 4, -3}, {13, -14, 4, -3}, {11,
      -12, 2, -1}, {13, -14, 2, -1}, {12, -11, 3, -4}, {14, -13, 3, -4}, {12,
      -11, 1, -2}, {14, -13, 1, -2}, {11, -12, 2, -3}, {13, -14, 2, -3}, {11,
      -12, 4, -1}, {13, -14, 4, -1}, {12, -11, 1, -4}, {14, -13, 1, -4}, {12,
      -11, 3, -2}, {14, -13, 3, -2}, {11, -12, -2, -3}, {13, -14, -2, -3}, {11,
      -12, -4, -1}, {13, -14, -4, -1}, {11, -12, -1, -3}, {13, -14, -1, -3},
      {11, -12, -3, -1}, {13, -14, -3, -1}, {12, -11, -2, -4}, {14, -13, -2,
      -4}, {12, -11, -4, -2}, {14, -13, -4, -2}, {12, -11, -2, -3}, {14, -13,
      -2, -3}, {12, -11, -4, -1}, {14, -13, -4, -1}, {11, -11, 4, 1}, {13, -13,
      4, 1}, {11, -11, 2, 3}, {13, -13, 2, 3}, {11, -11, 1, -3}, {13, -13, 1,
      -3}, {11, -11, 3, -1}, {13, -13, 3, -1}, {11, -11, 4, -3}, {13, -13, 4,
      -3}, {11, -11, 2, -1}, {13, -13, 2, -1}, {11, -11, 3, -4}, {13, -13, 3,
      -4}, {11, -11, 1, -2}, {13, -13, 1, -2}, {11, -11, 2, -4}, {13, -13, 2,
      -4}, {11, -11, 4, -2}, {13, -13, 4, -2}, {11, -11, -4, -1}, {13, -13, -4,
      -1}, {11, -11, -2, -3}, {13, -13, -2, -3}, {12, -12, 4, 1}, {14, -14, 4,
      1}, {12, -12, 2, 3}, {14, -14, 2, 3}, {12, -12, 1, -3}, {14, -14, 1, -3},
      {12, -12, 3, -1}, {14, -14, 3, -1}, {12, -12, 4, -3}, {14, -14, 4, -3},
      {12, -12, 2, -1}, {14, -14, 2, -1}, {12, -12, 3, -4}, {14, -14, 3, -4},
      {12, -12, 1, -2}, {14, -14, 1, -2}, {12, -12, 2, -4}, {14, -14, 2, -4},
      {12, -12, 4, -2}, {14, -14, 4, -2}, {12, -12, -4, -1}, {14, -14, -4, -1},
      {12, -12, -2, -3}, {14, -14, -2, -3}, {11, -11, 2, -2}, {13, -13, 2, -2},
      {11, -11, 4, -4}, {13, -13, 4, -4}, {11, -11, 1, -1}, {13, -13, 1, -1},
      {11, -11, 3, -3}, {13, -13, 3, -3}, {11, -11, 2, 1}, {13, -13, 2, 1},
      {11, -11, 4, 3}, {13, -13, 4, 3}, {11, -11, 1, -1}, {13, -13, 1, -1},
      {11, -11, 3, -3}, {13, -13, 3, -3}, {11, -11, 2, -1}, {13, -13, 2, -1},
      {11, -11, 4, -3}, {13, -13, 4, -3}, {11, -11, 1, -2}, {13, -13, 1, -2},
      {11, -11, 3, -4}, {13, -13, 3, -4}, {11, -11, 2, -2}, {13, -13, 2, -2},
      {11, -11, 4, -4}, {13, -13, 4, -4}, {11, -11, -2, -1}, {13, -13, -2, -1},
      {11, -11, -4, -3}, {13, -13, -4, -3}, {11, -11, 2, 4}, {13, -13, 2, 4},
      {11, -11, 2, 3}, {13, -13, 2, 3}, {11, -11, 4, 1}, {13, -13, 4, 1}, {11,
      -11, 4, -4}, {13, -13, 4, -4}, {11, -11, 2, -2}, {13, -13, 2, -2}, {11,
      -11, 3, -3}, {13, -13, 3, -3}, {11, -11, 1, -1}, {13, -13, 1, -1}, {11,
      -11, 2, -4}, {13, -13, 2, -4}, {11, -11, 4, -2}, {13, -13, 4, -2}, {11,
      -11, 2, -3}, {13, -13, 2, -3}, {11, -11, 4, -1}, {13, -13, 4, -1}, {11,
      -11, 1, 3}, {13, -13, 1, 3}, {11, -11, 1, -4}, {13, -13, 1, -4}, {11,
      -11, 3, -2}, {13, -13, 3, -2}, {11, -11, 4, -4}, {13, -13, 4, -4}, {11,
      -11, 2, -2}, {13, -13, 2, -2}, {11, -11, 3, -3}, {13, -13, 3, -3}, {11,
      -11, 1, -1}, {13, -13, 1, -1}, {11, -11, 1, -3}, {13, -13, 1, -3}, {11,
      -11, 3, -1}, {13, -13, 3, -1}, {11, -11, -2, -4}, {13, -13, -2, -4}, {11,
      -11, -2, -3}, {13, -13, -2, -3}, {11, -11, -4, -1}, {13, -13, -4, -1},
      {11, -11, -1, -3}, {13, -13, -1, -3}, {12, -12, 2, -2}, {14, -14, 2, -2},
      {12, -12, 4, -4}, {14, -14, 4, -4}, {12, -12, 1, -1}, {14, -14, 1, -1},
      {12, -12, 3, -3}, {14, -14, 3, -3}, {11, -12, 2, 2}, {13, -14, 2, 2},
      {11, -12, 4, 4}, {13, -14, 4, 4}, {12, -11, 1, 1}, {14, -13, 1, 1}, {12,
      -11, 3, 3}, {14, -13, 3, 3}, {11, -12, 2, -1}, {13, -14, 2, -1}, {11,
      -12, 4, -3}, {13, -14, 4, -3}, {12, -11, 1, -2}, {14, -13, 1, -2}, {12,
      -11, 3, -4}, {14, -13, 3, -4}, {12, -11, 2, -2}, {14, -13, 2, -2}, {12,
      -11, 4, -4}, {14, -13, 4, -4}, {12, -11, 1, -1}, {14, -13, 1, -1}, {12,
      -11, 3, -3}, {14, -13, 3, -3}, {11, -12, 2, -2}, {13, -14, 2, -2}, {11,
      -12, 4, -4}, {13, -14, 4, -4}, {11, -12, 1, -1}, {13, -14, 1, -1}, {11,
      -12, 3, -3}, {13, -14, 3, -3}, {11, -12, 2, -1}, {13, -14, 2, -1}, {11,
      -12, 4, -3}, {13, -14, 4, -3}, {12, -11, 1, -2}, {14, -13, 1, -2}, {12,
      -11, 3, -4}, {14, -13, 3, -4}, {11, -12, -1, -1}, {13, -14, -1, -1}, {11,
      -12, -3, -3}, {13, -14, -3, -3}, {12, -11, -2, -2}, {14, -13, -2, -2},
      {12, -11, -4, -4}, {14, -13, -4, -4}, {12, -12, 2, 1}, {14, -14, 2, 1},
      {12, -12, 4, 3}, {14, -14, 4, 3}, {12, -12, 1, -1}, {14, -14, 1, -1},
      {12, -12, 3, -3}, {14, -14, 3, -3}, {12, -12, 2, -1}, {14, -14, 2, -1},
      {12, -12, 4, -3}, {14, -14, 4, -3}, {12, -12, 1, -2}, {14, -14, 1, -2},
      {12, -12, 3, -4}, {14, -14, 3, -4}, {12, -12, 2, -2}, {14, -14, 2, -2},
      {12, -12, 4, -4}, {14, -14, 4, -4}, {12, -12, -2, -1}, {14, -14, -2, -1},
      {12, -12, -4, -3}, {14, -14, -4, -3}, {12, -12, 2, 4}, {14, -14, 2, 4},
      {12, -12, 2, 3}, {14, -14, 2, 3}, {12, -12, 4, 1}, {14, -14, 4, 1}, {12,
      -12, 4, -4}, {14, -14, 4, -4}, {12, -12, 2, -2}, {14, -14, 2, -2}, {12,
      -12, 3, -3}, {14, -14, 3, -3}, {12, -12, 1, -1}, {14, -14, 1, -1}, {12,
      -12, 2, -4}, {14, -14, 2, -4}, {12, -12, 4, -2}, {14, -14, 4, -2}, {12,
      -12, 2, -3}, {14, -14, 2, -3}, {12, -12, 4, -1}, {14, -14, 4, -1}, {12,
      -12, 1, 3}, {14, -14, 1, 3}, {12, -12, 1, -4}, {14, -14, 1, -4}, {12,
      -12, 3, -2}, {14, -14, 3, -2}, {12, -12, 4, -4}, {14, -14, 4, -4}, {12,
      -12, 2, -2}, {14, -14, 2, -2}, {12, -12, 3, -3}, {14, -14, 3, -3}, {12,
      -12, 1, -1}, {14, -14, 1, -1}, {12, -12, 1, -3}, {14, -14, 1, -3}, {12,
      -12, 3, -1}, {14, -14, 3, -1}, {12, -12, -2, -4}, {14, -14, -2, -4}, {12,
      -12, -2, -3}, {14, -14, -2, -3}, {12, -12, -4, -1}, {14, -14, -4, -1},
      {12, -12, -1, -3}, {14, -14, -1, -3}, {12, -11, 2, 3}, {14, -13, 2, 3},
      {12, -11, 4, 1}, {14, -13, 4, 1}, {11, -12, 2, 4}, {13, -14, 2, 4}, {11,
      -12, 4, 2}, {13, -14, 4, 2}, {12, -11, 1, 3}, {14, -13, 1, 3}, {12, -11,
      3, 1}, {14, -13, 3, 1}, {11, -12, 4, -3}, {13, -14, 4, -3}, {11, -12, 2,
      -1}, {13, -14, 2, -1}, {12, -11, 3, -4}, {14, -13, 3, -4}, {12, -11, 1,
      -2}, {14, -13, 1, -2}, {11, -12, 2, -3}, {13, -14, 2, -3}, {11, -12, 4,
      -1}, {13, -14, 4, -1}, {12, -11, 1, -4}, {14, -13, 1, -4}, {12, -11, 3,
      -2}, {14, -13, 3, -2}, {12, -11, 4, -4}, {14, -13, 4, -4}, {12, -11, 2,
      -2}, {14, -13, 2, -2}, {12, -11, 3, -3}, {14, -13, 3, -3}, {12, -11, 1,
      -1}, {14, -13, 1, -1}, {12, -11, 2, -4}, {14, -13, 2, -4}, {12, -11, 4,
      -2}, {14, -13, 4, -2}, {12, -11, 1, -3}, {14, -13, 1, -3}, {12, -11, 3,
      -1}, {14, -13, 3, -1}, {11, -12, 2, 3}, {13, -14, 2, 3}, {11, -12, 4, 1},
      {13, -14, 4, 1}, {11, -12, 4, -4}, {13, -14, 4, -4}, {11, -12, 2, -2},
      {13, -14, 2, -2}, {11, -12, 3, -3}, {13, -14, 3, -3}, {11, -12, 1, -1},
      {13, -14, 1, -1}, {11, -12, 2, -4}, {13, -14, 2, -4}, {11, -12, 4, -2},
      {13, -14, 4, -2}, {11, -12, 1, -3}, {13, -14, 1, -3}, {11, -12, 3, -1},
      {13, -14, 3, -1}, {11, -12, 4, -3}, {13, -14, 4, -3}, {11, -12, 2, -1},
      {13, -14, 2, -1}, {12, -11, 3, -4}, {14, -13, 3, -4}, {12, -11, 1, -2},
      {14, -13, 1, -2}, {11, -12, 2, -3}, {13, -14, 2, -3}, {11, -12, 4, -1},
      {13, -14, 4, -1}, {12, -11, 1, -4}, {14, -13, 1, -4}, {12, -11, 3, -2},
      {14, -13, 3, -2}, {11, -12, -2, -3}, {13, -14, -2, -3}, {11, -12, -4,
      -1}, {13, -14, -4, -1}, {11, -12, -1, -3}, {13, -14, -1, -3}, {11, -12,
      -3, -1}, {13, -14, -3, -1}, {12, -11, -2, -4}, {14, -13, -2, -4}, {12,
      -11, -4, -2}, {14, -13, -4, -2}, {12, -11, -2, -3}, {14, -13, -2, -3},
      {12, -11, -4, -1}, {14, -13, -4, -1}, {11, -11, 4, 1}, {13, -13, 4, 1},
      {11, -11, 2, 3}, {13, -13, 2, 3}, {11, -11, 1, -3}, {13, -13, 1, -3},
      {11, -11, 3, -1}, {13, -13, 3, -1}, {11, -11, 4, -3}, {13, -13, 4, -3},
      {11, -11, 2, -1}, {13, -13, 2, -1}, {11, -11, 3, -4}, {13, -13, 3, -4},
      {11, -11, 1, -2}, {13, -13, 1, -2}, {11, -11, 2, -4}, {13, -13, 2, -4},
      {11, -11, 4, -2}, {13, -13, 4, -2}, {11, -11, -4, -1}, {13, -13, -4, -1},
      {11, -11, -2, -3}, {13, -13, -2, -3}, {12, -12, 4, 1}, {14, -14, 4, 1},
      {12, -12, 2, 3}, {14, -14, 2, 3}, {12, -12, 1, -3}, {14, -14, 1, -3},
      {12, -12, 3, -1}, {14, -14, 3, -1}, {12, -12, 4, -3}, {14, -14, 4, -3},
      {12, -12, 2, -1}, {14, -14, 2, -1}, {12, -12, 3, -4}, {14, -14, 3, -4},
      {12, -12, 1, -2}, {14, -14, 1, -2}, {12, -12, 2, -4}, {14, -14, 2, -4},
      {12, -12, 4, -2}, {14, -14, 4, -2}, {12, -12, -4, -1}, {14, -14, -4, -1},
      {12, -12, -2, -3}, {14, -14, -2, -3}};

  bool in_pdgs_used[ninitial]; 
  bool out_pdgs_used[nexternal - ninitial]; 
  for(unsigned int i = 0; i < nprocs; i++ )
  {
    int permutations[nexternal]; 

    // Reinitialize initial state look-up variables
    for(unsigned int j = 0; j < ninitial; j++ )
    {
      in_pdgs_used[j] = false; 
      permutations[j] = -1; 
    }
    // Look for initial state matches
    for(unsigned int j = 0; j < ninitial; j++ )
    {
      for(unsigned int k = 0; k < ninitial; k++ )
      {
        // Make sure it has not been used already
        if (in_pdgs_used[k])
          continue; 
        if (initial_pdgs[k] == in_pdgs[i][j])
        {
          permutations[j] = k; 
          in_pdgs_used[k] = true; 
          break; 
        }
      }
      // If no match found for this particular initial state,
      // proceed with the next process
      if (permutations[j] == -1)
        break; 
    }
    // Proceed with next process if not match found
    if (permutations[ninitial - 1] == -1)
      continue; 

    // Reinitialize final state look-up variables
    for(unsigned int j = 0; j < (nexternal - ninitial); j++ )
    {
      out_pdgs_used[j] = false; 
      permutations[ninitial + j] = -1; 
    }
    // Look for final state matches
    for(unsigned int j = 0; j < (nexternal - ninitial); j++ )
    {
      for(unsigned int k = 0; k < (nexternal - ninitial); k++ )
      {
        // Make sure it has not been used already
        if (out_pdgs_used[k])
          continue; 
        if (final_pdgs[k] == out_pdgs[i][j])
        {
          permutations[ninitial + j] = ninitial + k; 
          out_pdgs_used[k] = true; 
          break; 
        }
      }
      // If no match found for this particular initial state,
      // proceed with the next process
      if (permutations[ninitial + j] == -1)
        break; 
    }
    // Proceed with next process if not match found
    if (permutations[nexternal - 1] == -1)
      continue; 

    // Return process found
    return pair < vector<int> , int > (vector<int> (permutations, permutations
        + nexternal), proc_IDS[i]);
  }

  // No process found
  return NA; 
}

//--------------------------------------------------------------------------
// Set momenta
void PY8MEs_R7_P1_sm_qq_llqq::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P1_sm_qq_llqq': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R7_P1_sm_qq_llqq::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R7_P1_sm_qq_llqq::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R7_P1_sm_qq_llqq::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R7_P1_sm_qq_llqq::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R7_P1_sm_qq_llqq::initProc() 
{

  // Initialize flags
  include_symmetry_factors = true; 
  include_helicity_averaging_factors = true; 
  include_color_averaging_factors = true; 

  // Initialize vectors.
  perm = vector<int> (nexternal, 0); 
  user_colors = vector<int> (2 * nexternal, 0); 
  user_helicities = vector<int> (nexternal, 0); 
  p = vector < double * > (); 
  for (unsigned int i = 0; i < nexternal; i++ )
  {
    p.push_back(new double[4]); 
  }
  initColorConfigs(); 
  // Synchronize local variables dependent on the model with the active model.
  mME = vector<double> (nexternal, 0.); 
  syncProcModelParams(); 
  jamp2 = vector < vec_double > (108); 
  jamp2[0] = vector<double> (2, 0.); 
  jamp2[1] = vector<double> (2, 0.); 
  jamp2[2] = vector<double> (2, 0.); 
  jamp2[3] = vector<double> (2, 0.); 
  jamp2[4] = vector<double> (2, 0.); 
  jamp2[5] = vector<double> (2, 0.); 
  jamp2[6] = vector<double> (2, 0.); 
  jamp2[7] = vector<double> (2, 0.); 
  jamp2[8] = vector<double> (2, 0.); 
  jamp2[9] = vector<double> (2, 0.); 
  jamp2[10] = vector<double> (2, 0.); 
  jamp2[11] = vector<double> (2, 0.); 
  jamp2[12] = vector<double> (2, 0.); 
  jamp2[13] = vector<double> (2, 0.); 
  jamp2[14] = vector<double> (2, 0.); 
  jamp2[15] = vector<double> (2, 0.); 
  jamp2[16] = vector<double> (2, 0.); 
  jamp2[17] = vector<double> (2, 0.); 
  jamp2[18] = vector<double> (2, 0.); 
  jamp2[19] = vector<double> (2, 0.); 
  jamp2[20] = vector<double> (2, 0.); 
  jamp2[21] = vector<double> (2, 0.); 
  jamp2[22] = vector<double> (2, 0.); 
  jamp2[23] = vector<double> (2, 0.); 
  jamp2[24] = vector<double> (2, 0.); 
  jamp2[25] = vector<double> (2, 0.); 
  jamp2[26] = vector<double> (2, 0.); 
  jamp2[27] = vector<double> (2, 0.); 
  jamp2[28] = vector<double> (2, 0.); 
  jamp2[29] = vector<double> (2, 0.); 
  jamp2[30] = vector<double> (2, 0.); 
  jamp2[31] = vector<double> (2, 0.); 
  jamp2[32] = vector<double> (2, 0.); 
  jamp2[33] = vector<double> (2, 0.); 
  jamp2[34] = vector<double> (2, 0.); 
  jamp2[35] = vector<double> (2, 0.); 
  jamp2[36] = vector<double> (2, 0.); 
  jamp2[37] = vector<double> (2, 0.); 
  jamp2[38] = vector<double> (2, 0.); 
  jamp2[39] = vector<double> (2, 0.); 
  jamp2[40] = vector<double> (2, 0.); 
  jamp2[41] = vector<double> (2, 0.); 
  jamp2[42] = vector<double> (2, 0.); 
  jamp2[43] = vector<double> (2, 0.); 
  jamp2[44] = vector<double> (2, 0.); 
  jamp2[45] = vector<double> (2, 0.); 
  jamp2[46] = vector<double> (2, 0.); 
  jamp2[47] = vector<double> (2, 0.); 
  jamp2[48] = vector<double> (2, 0.); 
  jamp2[49] = vector<double> (2, 0.); 
  jamp2[50] = vector<double> (2, 0.); 
  jamp2[51] = vector<double> (2, 0.); 
  jamp2[52] = vector<double> (2, 0.); 
  jamp2[53] = vector<double> (2, 0.); 
  jamp2[54] = vector<double> (2, 0.); 
  jamp2[55] = vector<double> (2, 0.); 
  jamp2[56] = vector<double> (2, 0.); 
  jamp2[57] = vector<double> (2, 0.); 
  jamp2[58] = vector<double> (2, 0.); 
  jamp2[59] = vector<double> (2, 0.); 
  jamp2[60] = vector<double> (2, 0.); 
  jamp2[61] = vector<double> (2, 0.); 
  jamp2[62] = vector<double> (2, 0.); 
  jamp2[63] = vector<double> (2, 0.); 
  jamp2[64] = vector<double> (2, 0.); 
  jamp2[65] = vector<double> (2, 0.); 
  jamp2[66] = vector<double> (2, 0.); 
  jamp2[67] = vector<double> (2, 0.); 
  jamp2[68] = vector<double> (2, 0.); 
  jamp2[69] = vector<double> (2, 0.); 
  jamp2[70] = vector<double> (2, 0.); 
  jamp2[71] = vector<double> (2, 0.); 
  jamp2[72] = vector<double> (2, 0.); 
  jamp2[73] = vector<double> (2, 0.); 
  jamp2[74] = vector<double> (2, 0.); 
  jamp2[75] = vector<double> (2, 0.); 
  jamp2[76] = vector<double> (2, 0.); 
  jamp2[77] = vector<double> (2, 0.); 
  jamp2[78] = vector<double> (2, 0.); 
  jamp2[79] = vector<double> (2, 0.); 
  jamp2[80] = vector<double> (2, 0.); 
  jamp2[81] = vector<double> (2, 0.); 
  jamp2[82] = vector<double> (2, 0.); 
  jamp2[83] = vector<double> (2, 0.); 
  jamp2[84] = vector<double> (2, 0.); 
  jamp2[85] = vector<double> (2, 0.); 
  jamp2[86] = vector<double> (2, 0.); 
  jamp2[87] = vector<double> (2, 0.); 
  jamp2[88] = vector<double> (2, 0.); 
  jamp2[89] = vector<double> (2, 0.); 
  jamp2[90] = vector<double> (2, 0.); 
  jamp2[91] = vector<double> (2, 0.); 
  jamp2[92] = vector<double> (2, 0.); 
  jamp2[93] = vector<double> (2, 0.); 
  jamp2[94] = vector<double> (2, 0.); 
  jamp2[95] = vector<double> (2, 0.); 
  jamp2[96] = vector<double> (1, 0.); 
  jamp2[97] = vector<double> (1, 0.); 
  jamp2[98] = vector<double> (1, 0.); 
  jamp2[99] = vector<double> (1, 0.); 
  jamp2[100] = vector<double> (1, 0.); 
  jamp2[101] = vector<double> (1, 0.); 
  jamp2[102] = vector<double> (1, 0.); 
  jamp2[103] = vector<double> (1, 0.); 
  jamp2[104] = vector<double> (1, 0.); 
  jamp2[105] = vector<double> (1, 0.); 
  jamp2[106] = vector<double> (1, 0.); 
  jamp2[107] = vector<double> (1, 0.); 
  all_results = vector < vec_vec_double > (108); 
  // The first entry is always the color or helicity avg/summed matrix element.
  all_results[0] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[1] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[2] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[3] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[4] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[5] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[6] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[7] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[8] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[9] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[10] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[11] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[12] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[13] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[14] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[15] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[16] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[17] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[18] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[19] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[20] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[21] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[22] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[23] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[24] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[25] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[26] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[27] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[28] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[29] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[30] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[31] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[32] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[33] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[34] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[35] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[36] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[37] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[38] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[39] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[40] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[41] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[42] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[43] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[44] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[45] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[46] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[47] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[48] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[49] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[50] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[51] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[52] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[53] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[54] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[55] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[56] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[57] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[58] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[59] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[60] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[61] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[62] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[63] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[64] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[65] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[66] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[67] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[68] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[69] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[70] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[71] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[72] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[73] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[74] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[75] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[76] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[77] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[78] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[79] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[80] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[81] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[82] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[83] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[84] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[85] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[86] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[87] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[88] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[89] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[90] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[91] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[92] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[93] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[94] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[95] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[96] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[97] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[98] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[99] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[100] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[101] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[102] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[103] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[104] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[105] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[106] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[107] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R7_P1_sm_qq_llqq::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->ZERO; 
  mME[2] = pars->ZERO; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->ZERO; 
  mME[5] = pars->ZERO; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R7_P1_sm_qq_llqq::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R7_P1_sm_qq_llqq::getMasses() 
{

  vec_double external_masses; 
  vector<int> invertedPerm; 
  invertedPerm = invert_mapping(perm); 
  for (unsigned int i = 0; i < mME.size(); i++ )
  {
    external_masses.push_back(mME[invertedPerm[i]]); 
  }
  return external_masses; 

}


// Set all values of the external masses to float(-mode) where mode can be
// 0 : Mass taken from the model
// 1 : Mass taken from p_i^2 if not massless to begin with
// 2 : Mass always taken from p_i^2.
void PY8MEs_R7_P1_sm_qq_llqq::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R7_P1_sm_qq_llqq': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R7_P1_sm_qq_llqq_exception; 
  }
  if (mode == 0)
  {
    syncProcModelParams(); 
  }
  else if (mode == 1)
  {
    for (unsigned int j = 0; j < mME.size(); j++ )
    {
      if (mME[j] != pars->ZERO)
      {
        mME[j] = -1.0; 
      }
    }
  }
  else if (mode == 2)
  {
    for (unsigned int j = 0; j < mME.size(); j++ )
    {
      mME[j] = -1.0; 
    }
  }
}

//--------------------------------------------------------------------------
// Evaluate the squared matrix element.

double PY8MEs_R7_P1_sm_qq_llqq::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(); 
  pars->setDependentCouplings(); 
  // Reset color flows
  for(int i = 0; i < 2; i++ )
    jamp2[0][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[1][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[2][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[3][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[4][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[5][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[6][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[7][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[8][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[9][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[10][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[11][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[12][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[13][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[14][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[15][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[16][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[17][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[18][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[19][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[20][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[21][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[22][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[23][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[24][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[25][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[26][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[27][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[28][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[29][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[30][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[31][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[32][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[33][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[34][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[35][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[36][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[37][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[38][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[39][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[40][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[41][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[42][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[43][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[44][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[45][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[46][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[47][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[48][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[49][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[50][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[51][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[52][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[53][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[54][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[55][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[56][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[57][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[58][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[59][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[60][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[61][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[62][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[63][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[64][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[65][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[66][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[67][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[68][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[69][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[70][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[71][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[72][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[73][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[74][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[75][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[76][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[77][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[78][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[79][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[80][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[81][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[82][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[83][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[84][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[85][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[86][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[87][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[88][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[89][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[90][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[91][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[92][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[93][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[94][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[95][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[96][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[97][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[98][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[99][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[100][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[101][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[102][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[103][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[104][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[105][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[106][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[107][i] = 0.; 

  // Save previous values of mME
  vector<double> saved_mME(mME.size(), 0.0); 
  for (unsigned int i = 0; i < mME.size(); i++ )
  {
    if (mME[i] < 0.0)
    {
      saved_mME[i] = mME[i]; 
      mME[i] = sqrt(abs(pow(p[perm[i]][0], 2) - 
      (pow(p[perm[i]][1], 2) + pow(p[perm[i]][2], 2) + pow(p[perm[i]][3],
          2))));
    }
  }

  // Local variables and constants
  const int max_tries = 10; 
  vector < vec_bool > goodhel(nprocesses, vec_bool(ncomb, false)); 
  vec_int ntry(nprocesses, 0); 
  double t = 0.; 
  double result = 0.; 

  if (ntry[proc_ID] <= max_tries)
    ntry[proc_ID] = ntry[proc_ID] + 1; 

  // Find which helicity configuration is asked for
  // -1 indicates one wants to sum over helicities
  int user_ihel = getHelicityIDForConfig(user_helicities); 

  // Find which color configuration is asked for
  // -1 indicates one wants to sum over all color configurations
  int user_icol = getColorIDForConfig(user_colors); 

  // Reset the list of results that will be recomputed here
  // Starts with -1 which are the summed results
  for (int ihel = -1; ihel + 1 < ((int)all_results[proc_ID].size()); ihel++ )
  {
    // Only if it is the helicity picked
    if (user_ihel != -1 && ihel != user_ihel)
      continue; 
    for (int icolor = -1; icolor + 1 < ((int)all_results[proc_ID][ihel +
        1].size()); icolor++ )
    {
      // Only if color picked
      if (user_icol != -1 && icolor != user_icol)
        continue; 
      all_results[proc_ID][ihel + 1][icolor + 1] = 0.; 
    }
  }

  // Calculate the matrix element for all helicities
  // unless already detected as vanishing
  for(int ihel = 0; ihel < ncomb; ihel++ )
  {
    // Skip helicity if already detected as vanishing
    if ((ntry[proc_ID] >= max_tries) && !goodhel[proc_ID][ihel])
      continue; 

    // Also skip helicity if user asks for a specific one
    if ((ntry[proc_ID] >= max_tries) && user_ihel != -1 && user_ihel != ihel)
      continue; 

    calculate_wavefunctions(helicities[ihel]); 

    // Reset locally computed color flows
    for(int i = 0; i < 2; i++ )
      jamp2[0][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[1][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[2][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[3][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[4][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[5][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[6][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[7][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[8][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[9][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[10][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[11][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[12][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[13][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[14][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[15][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[16][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[17][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[18][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[19][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[20][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[21][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[22][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[23][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[24][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[25][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[26][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[27][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[28][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[29][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[30][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[31][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[32][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[33][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[34][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[35][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[36][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[37][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[38][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[39][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[40][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[41][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[42][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[43][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[44][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[45][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[46][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[47][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[48][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[49][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[50][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[51][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[52][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[53][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[54][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[55][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[56][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[57][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[58][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[59][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[60][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[61][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[62][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[63][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[64][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[65][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[66][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[67][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[68][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[69][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[70][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[71][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[72][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[73][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[74][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[75][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[76][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[77][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[78][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[79][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[80][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[81][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[82][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[83][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[84][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[85][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[86][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[87][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[88][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[89][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[90][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[91][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[92][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[93][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[94][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[95][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[96][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[97][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[98][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[99][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[100][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[101][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[102][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[103][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[104][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[105][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[106][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[107][i] = 0.; 

    if (proc_ID == 0)
      t = matrix_7_uu_emepuu(); 
    if (proc_ID == 1)
      t = matrix_7_uux_emepuux(); 
    if (proc_ID == 2)
      t = matrix_7_dd_emepdd(); 
    if (proc_ID == 3)
      t = matrix_7_ddx_emepddx(); 
    if (proc_ID == 4)
      t = matrix_7_uxux_emepuxux(); 
    if (proc_ID == 5)
      t = matrix_7_dxdx_emepdxdx(); 
    if (proc_ID == 6)
      t = matrix_7_ud_emepud(); 
    if (proc_ID == 7)
      t = matrix_7_uux_emepddx(); 
    if (proc_ID == 8)
      t = matrix_7_udx_emepudx(); 
    if (proc_ID == 9)
      t = matrix_7_dux_emepdux(); 
    if (proc_ID == 10)
      t = matrix_7_ddx_emepuux(); 
    if (proc_ID == 11)
      t = matrix_7_uxdx_emepuxdx(); 
    if (proc_ID == 12)
      t = matrix_7_uc_emepuc(); 
    if (proc_ID == 13)
      t = matrix_7_us_emepus(); 
    if (proc_ID == 14)
      t = matrix_7_uux_emepccx(); 
    if (proc_ID == 15)
      t = matrix_7_uux_emepssx(); 
    if (proc_ID == 16)
      t = matrix_7_ucx_emepucx(); 
    if (proc_ID == 17)
      t = matrix_7_usx_emepusx(); 
    if (proc_ID == 18)
      t = matrix_7_ds_emepds(); 
    if (proc_ID == 19)
      t = matrix_7_dcx_emepdcx(); 
    if (proc_ID == 20)
      t = matrix_7_ddx_emepccx(); 
    if (proc_ID == 21)
      t = matrix_7_ddx_emepssx(); 
    if (proc_ID == 22)
      t = matrix_7_dsx_emepdsx(); 
    if (proc_ID == 23)
      t = matrix_7_uxcx_emepuxcx(); 
    if (proc_ID == 24)
      t = matrix_7_uxsx_emepuxsx(); 
    if (proc_ID == 25)
      t = matrix_7_dxsx_emepdxsx(); 
    if (proc_ID == 26)
      t = matrix_7_uu_vevexuu(); 
    if (proc_ID == 27)
      t = matrix_7_uux_vevexuux(); 
    if (proc_ID == 28)
      t = matrix_7_dd_vevexdd(); 
    if (proc_ID == 29)
      t = matrix_7_ddx_vevexddx(); 
    if (proc_ID == 30)
      t = matrix_7_uxux_vevexuxux(); 
    if (proc_ID == 31)
      t = matrix_7_dxdx_vevexdxdx(); 
    if (proc_ID == 32)
      t = matrix_7_uu_veepud(); 
    if (proc_ID == 33)
      t = matrix_7_ud_emvexuu(); 
    if (proc_ID == 34)
      t = matrix_7_ud_veepdd(); 
    if (proc_ID == 35)
      t = matrix_7_uux_emvexudx(); 
    if (proc_ID == 36)
      t = matrix_7_uux_veepdux(); 
    if (proc_ID == 37)
      t = matrix_7_udx_veepuux(); 
    if (proc_ID == 38)
      t = matrix_7_udx_veepddx(); 
    if (proc_ID == 39)
      t = matrix_7_dd_emvexud(); 
    if (proc_ID == 40)
      t = matrix_7_dux_emvexuux(); 
    if (proc_ID == 41)
      t = matrix_7_dux_emvexddx(); 
    if (proc_ID == 42)
      t = matrix_7_ddx_emvexudx(); 
    if (proc_ID == 43)
      t = matrix_7_ddx_veepdux(); 
    if (proc_ID == 44)
      t = matrix_7_uxux_emvexuxdx(); 
    if (proc_ID == 45)
      t = matrix_7_uxdx_emvexdxdx(); 
    if (proc_ID == 46)
      t = matrix_7_uxdx_veepuxux(); 
    if (proc_ID == 47)
      t = matrix_7_dxdx_veepuxdx(); 
    if (proc_ID == 48)
      t = matrix_7_ud_vevexud(); 
    if (proc_ID == 49)
      t = matrix_7_uux_vevexddx(); 
    if (proc_ID == 50)
      t = matrix_7_udx_vevexudx(); 
    if (proc_ID == 51)
      t = matrix_7_dux_vevexdux(); 
    if (proc_ID == 52)
      t = matrix_7_ddx_vevexuux(); 
    if (proc_ID == 53)
      t = matrix_7_uxdx_vevexuxdx(); 
    if (proc_ID == 54)
      t = matrix_7_uc_vevexuc(); 
    if (proc_ID == 55)
      t = matrix_7_us_vevexus(); 
    if (proc_ID == 56)
      t = matrix_7_uux_vevexccx(); 
    if (proc_ID == 57)
      t = matrix_7_uux_vevexssx(); 
    if (proc_ID == 58)
      t = matrix_7_ucx_vevexucx(); 
    if (proc_ID == 59)
      t = matrix_7_usx_vevexusx(); 
    if (proc_ID == 60)
      t = matrix_7_ds_vevexds(); 
    if (proc_ID == 61)
      t = matrix_7_dcx_vevexdcx(); 
    if (proc_ID == 62)
      t = matrix_7_ddx_vevexccx(); 
    if (proc_ID == 63)
      t = matrix_7_ddx_vevexssx(); 
    if (proc_ID == 64)
      t = matrix_7_dsx_vevexdsx(); 
    if (proc_ID == 65)
      t = matrix_7_uxcx_vevexuxcx(); 
    if (proc_ID == 66)
      t = matrix_7_uxsx_vevexuxsx(); 
    if (proc_ID == 67)
      t = matrix_7_dxsx_vevexdxsx(); 
    if (proc_ID == 68)
      t = matrix_7_uc_veepus(); 
    if (proc_ID == 69)
      t = matrix_7_uc_veepcd(); 
    if (proc_ID == 70)
      t = matrix_7_us_emvexuc(); 
    if (proc_ID == 71)
      t = matrix_7_us_veepds(); 
    if (proc_ID == 72)
      t = matrix_7_uux_emvexcsx(); 
    if (proc_ID == 73)
      t = matrix_7_uux_veepscx(); 
    if (proc_ID == 74)
      t = matrix_7_ucx_emvexusx(); 
    if (proc_ID == 75)
      t = matrix_7_ucx_veepdcx(); 
    if (proc_ID == 76)
      t = matrix_7_udx_veepccx(); 
    if (proc_ID == 77)
      t = matrix_7_udx_veepssx(); 
    if (proc_ID == 78)
      t = matrix_7_usx_veepucx(); 
    if (proc_ID == 79)
      t = matrix_7_usx_veepdsx(); 
    if (proc_ID == 80)
      t = matrix_7_ds_emvexus(); 
    if (proc_ID == 81)
      t = matrix_7_ds_emvexcd(); 
    if (proc_ID == 82)
      t = matrix_7_dux_emvexccx(); 
    if (proc_ID == 83)
      t = matrix_7_dux_emvexssx(); 
    if (proc_ID == 84)
      t = matrix_7_dcx_emvexucx(); 
    if (proc_ID == 85)
      t = matrix_7_dcx_emvexdsx(); 
    if (proc_ID == 86)
      t = matrix_7_ddx_emvexcsx(); 
    if (proc_ID == 87)
      t = matrix_7_ddx_veepscx(); 
    if (proc_ID == 88)
      t = matrix_7_dsx_emvexusx(); 
    if (proc_ID == 89)
      t = matrix_7_dsx_veepdcx(); 
    if (proc_ID == 90)
      t = matrix_7_uxcx_emvexuxsx(); 
    if (proc_ID == 91)
      t = matrix_7_uxcx_emvexcxdx(); 
    if (proc_ID == 92)
      t = matrix_7_uxsx_emvexdxsx(); 
    if (proc_ID == 93)
      t = matrix_7_uxsx_veepuxcx(); 
    if (proc_ID == 94)
      t = matrix_7_dxsx_veepuxsx(); 
    if (proc_ID == 95)
      t = matrix_7_dxsx_veepcxdx(); 
    if (proc_ID == 96)
      t = matrix_7_us_emepcd(); 
    if (proc_ID == 97)
      t = matrix_7_ucx_emepdsx(); 
    if (proc_ID == 98)
      t = matrix_7_udx_emepcsx(); 
    if (proc_ID == 99)
      t = matrix_7_dux_emepscx(); 
    if (proc_ID == 100)
      t = matrix_7_dsx_emepucx(); 
    if (proc_ID == 101)
      t = matrix_7_uxsx_emepcxdx(); 
    if (proc_ID == 102)
      t = matrix_7_us_vevexcd(); 
    if (proc_ID == 103)
      t = matrix_7_ucx_vevexdsx(); 
    if (proc_ID == 104)
      t = matrix_7_udx_vevexcsx(); 
    if (proc_ID == 105)
      t = matrix_7_dux_vevexscx(); 
    if (proc_ID == 106)
      t = matrix_7_dsx_vevexucx(); 
    if (proc_ID == 107)
      t = matrix_7_uxsx_vevexcxdx(); 

    // Store which helicities give non-zero result
    if ((ntry[proc_ID] < max_tries) && t != 0. && !goodhel[proc_ID][ihel])
      goodhel[proc_ID][ihel] = true; 

    // Aggregate results
    if (user_ihel == -1 || user_ihel == ihel)
    {
      if (user_icol == -1)
      {
        result = result + t; 
        if (user_ihel == -1)
        {
          all_results[proc_ID][0][0] += t; 
          for (unsigned int i = 0; i < jamp2[proc_ID].size(); i++ )
          {
            all_results[proc_ID][0][i + 1] += jamp2[proc_ID][i]; 
          }
        }
        all_results[proc_ID][ihel + 1][0] += t; 
        for (unsigned int i = 0; i < jamp2[proc_ID].size(); i++ )
        {
          all_results[proc_ID][ihel + 1][i + 1] += jamp2[proc_ID][i]; 
        }
      }
      else
      {
        result = result + jamp2[proc_ID][user_icol]; 
        if (user_ihel == -1)
        {
          all_results[proc_ID][0][user_icol + 1] += jamp2[proc_ID][user_icol]; 
        }
        all_results[proc_ID][ihel + 1][user_icol + 1] +=
            jamp2[proc_ID][user_icol];
      }
    }

  }

  // Normalize results with the identical particle factor
  if (include_symmetry_factors)
  {
    result = result/denom_iden[proc_ID]; 
  }
  // Starts with -1 which are the summed results
  for (int ihel = -1; ihel + 1 < ((int)all_results[proc_ID].size()); ihel++ )
  {
    // Only if it is the helicity picked
    if (user_ihel != -1 && ihel != user_ihel)
      continue; 
    for (int icolor = -1; icolor + 1 < ((int)all_results[proc_ID][ihel +
        1].size()); icolor++ )
    {
      // Only if color picked
      if (user_icol != -1 && icolor != user_icol)
        continue; 
      if (include_symmetry_factors)
      {
        all_results[proc_ID][ihel + 1][icolor + 1] /= denom_iden[proc_ID]; 
      }
    }
  }


  // Normalize when when summing+averaging over helicity configurations
  if (user_ihel == -1 && include_helicity_averaging_factors)
  {
    result /= denom_hels[proc_ID]; 
    if (user_icol == -1)
    {
      all_results[proc_ID][0][0] /= denom_hels[proc_ID]; 
      for (unsigned int i = 0; i < jamp2[proc_ID].size(); i++ )
      {
        all_results[proc_ID][0][i + 1] /= denom_hels[proc_ID]; 
      }
    }
    else
    {
      all_results[proc_ID][0][user_icol + 1] /= denom_hels[proc_ID]; 
    }
  }

  // Normalize when summing+averaging over color configurations
  if (user_icol == -1 && include_color_averaging_factors)
  {
    result /= denom_colors[proc_ID]; 
    if (user_ihel == -1)
    {
      all_results[proc_ID][0][0] /= denom_colors[proc_ID]; 
      for (unsigned int i = 0; i < ncomb; i++ )
      {
        all_results[proc_ID][i + 1][0] /= denom_colors[proc_ID]; 
      }
    }
    else
    {
      all_results[proc_ID][user_ihel + 1][0] /= denom_colors[proc_ID]; 
    }
  }

  // Reinstate previous values of mME
  for (unsigned int i = 0; i < mME.size(); i++ )
  {
    if (saved_mME[i] < 0.0)
    {
      mME[i] = saved_mME[i]; 
    }
  }

  // Finally return it
  return result; 
}

//==========================================================================
// Private class member functions

//--------------------------------------------------------------------------
// Evaluate |M|^2 for each subprocess

void PY8MEs_R7_P1_sm_qq_llqq::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  oxxxxx(p[perm[5]], mME[5], hel[5], +1, w[5]); 
  FFV1P0_3(w[0], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[1], w[5], pars->GC_2, pars->ZERO, pars->ZERO, w[7]); 
  FFV1_1(w[2], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[8]); 
  FFV1_2(w[3], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[9]); 
  FFV2_5_3(w[1], w[5], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[10]);
  FFV2_5_3(w[0], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV2_4_1(w[2], w[11], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[12]);
  FFV2_4_2(w[3], w[11], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[13]);
  FFV1P0_3(w[3], w[2], pars->GC_3, pars->ZERO, pars->ZERO, w[14]); 
  FFV1_2(w[1], w[6], pars->GC_2, pars->ZERO, pars->ZERO, w[15]); 
  FFV1_1(w[5], w[6], pars->GC_2, pars->ZERO, pars->ZERO, w[16]); 
  FFV2_4_3(w[3], w[2], pars->GC_50, pars->GC_59, pars->mdl_MZ, pars->mdl_WZ,
      w[17]);
  FFV1P0_3(w[0], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[18]); 
  FFV1_2(w[1], w[18], pars->GC_11, pars->ZERO, pars->ZERO, w[19]); 
  FFV1_1(w[5], w[18], pars->GC_11, pars->ZERO, pars->ZERO, w[20]); 
  FFV2_5_2(w[1], w[11], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[21]);
  FFV2_5_1(w[5], w[11], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[22]);
  FFV1P0_3(w[0], w[5], pars->GC_2, pars->ZERO, pars->ZERO, w[23]); 
  FFV1P0_3(w[1], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[24]); 
  FFV1_1(w[2], w[23], pars->GC_3, pars->ZERO, pars->ZERO, w[25]); 
  FFV1_2(w[3], w[23], pars->GC_3, pars->ZERO, pars->ZERO, w[26]); 
  FFV2_5_3(w[1], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[27]);
  FFV2_5_3(w[0], w[5], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[28]);
  FFV2_4_1(w[2], w[28], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[29]);
  FFV2_4_2(w[3], w[28], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[30]);
  FFV1_2(w[1], w[23], pars->GC_2, pars->ZERO, pars->ZERO, w[31]); 
  FFV1_1(w[4], w[23], pars->GC_2, pars->ZERO, pars->ZERO, w[32]); 
  FFV1P0_3(w[0], w[5], pars->GC_11, pars->ZERO, pars->ZERO, w[33]); 
  FFV1_2(w[1], w[33], pars->GC_11, pars->ZERO, pars->ZERO, w[34]); 
  FFV1_1(w[4], w[33], pars->GC_11, pars->ZERO, pars->ZERO, w[35]); 
  FFV2_5_2(w[1], w[28], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[36]);
  FFV2_5_1(w[4], w[28], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[37]);
  FFV1_2(w[0], w[24], pars->GC_2, pars->ZERO, pars->ZERO, w[38]); 
  FFV1_2(w[0], w[14], pars->GC_2, pars->ZERO, pars->ZERO, w[39]); 
  FFV2_5_2(w[0], w[17], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[40]);
  FFV1P0_3(w[1], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[41]); 
  FFV1_2(w[0], w[41], pars->GC_11, pars->ZERO, pars->ZERO, w[42]); 
  FFV2_5_2(w[0], w[27], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[43]);
  FFV1_2(w[0], w[7], pars->GC_2, pars->ZERO, pars->ZERO, w[44]); 
  FFV1P0_3(w[1], w[5], pars->GC_11, pars->ZERO, pars->ZERO, w[45]); 
  FFV1_2(w[0], w[45], pars->GC_11, pars->ZERO, pars->ZERO, w[46]); 
  FFV2_5_2(w[0], w[10], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[47]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[48]); 
  ixxxxx(p[perm[5]], mME[5], hel[5], -1, w[49]); 
  FFV1P0_3(w[0], w[48], pars->GC_2, pars->ZERO, pars->ZERO, w[50]); 
  FFV1P0_3(w[49], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[51]); 
  FFV1_1(w[2], w[50], pars->GC_3, pars->ZERO, pars->ZERO, w[52]); 
  FFV1_2(w[3], w[50], pars->GC_3, pars->ZERO, pars->ZERO, w[53]); 
  FFV2_5_3(w[49], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[54]);
  FFV2_5_3(w[0], w[48], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[55]);
  FFV2_4_1(w[2], w[55], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[56]);
  FFV2_4_2(w[3], w[55], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[57]);
  FFV1_2(w[49], w[50], pars->GC_2, pars->ZERO, pars->ZERO, w[58]); 
  FFV1_1(w[4], w[50], pars->GC_2, pars->ZERO, pars->ZERO, w[59]); 
  FFV1P0_3(w[0], w[48], pars->GC_11, pars->ZERO, pars->ZERO, w[60]); 
  FFV1_2(w[49], w[60], pars->GC_11, pars->ZERO, pars->ZERO, w[61]); 
  FFV1_1(w[4], w[60], pars->GC_11, pars->ZERO, pars->ZERO, w[62]); 
  FFV2_5_2(w[49], w[55], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[63]);
  FFV2_5_1(w[4], w[55], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[64]);
  FFV1P0_3(w[49], w[48], pars->GC_2, pars->ZERO, pars->ZERO, w[65]); 
  FFV2_5_3(w[49], w[48], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[66]);
  FFV1_2(w[49], w[6], pars->GC_2, pars->ZERO, pars->ZERO, w[67]); 
  FFV1_1(w[48], w[6], pars->GC_2, pars->ZERO, pars->ZERO, w[68]); 
  FFV1_2(w[49], w[18], pars->GC_11, pars->ZERO, pars->ZERO, w[69]); 
  FFV1_1(w[48], w[18], pars->GC_11, pars->ZERO, pars->ZERO, w[70]); 
  FFV2_5_2(w[49], w[11], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[71]);
  FFV2_5_1(w[48], w[11], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[72]);
  FFV1_2(w[0], w[65], pars->GC_2, pars->ZERO, pars->ZERO, w[73]); 
  FFV1P0_3(w[49], w[48], pars->GC_11, pars->ZERO, pars->ZERO, w[74]); 
  FFV1_2(w[0], w[74], pars->GC_11, pars->ZERO, pars->ZERO, w[75]); 
  FFV2_5_2(w[0], w[66], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[76]);
  FFV1_2(w[0], w[51], pars->GC_2, pars->ZERO, pars->ZERO, w[77]); 
  FFV1P0_3(w[49], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[78]); 
  FFV1_2(w[0], w[78], pars->GC_11, pars->ZERO, pars->ZERO, w[79]); 
  FFV2_5_2(w[0], w[54], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[80]);
  FFV1P0_3(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[81]); 
  FFV1P0_3(w[1], w[5], pars->GC_1, pars->ZERO, pars->ZERO, w[82]); 
  FFV1_1(w[2], w[81], pars->GC_3, pars->ZERO, pars->ZERO, w[83]); 
  FFV1_2(w[3], w[81], pars->GC_3, pars->ZERO, pars->ZERO, w[84]); 
  FFV2_3_3(w[1], w[5], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[85]);
  FFV2_3_3(w[0], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[86]);
  FFV2_4_1(w[2], w[86], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[87]);
  FFV2_4_2(w[3], w[86], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[88]);
  FFV1_2(w[1], w[81], pars->GC_1, pars->ZERO, pars->ZERO, w[89]); 
  FFV1_1(w[5], w[81], pars->GC_1, pars->ZERO, pars->ZERO, w[90]); 
  FFV2_3_2(w[1], w[86], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[91]);
  FFV2_3_1(w[5], w[86], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[92]);
  FFV1P0_3(w[0], w[5], pars->GC_1, pars->ZERO, pars->ZERO, w[93]); 
  FFV1P0_3(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[94]); 
  FFV1_1(w[2], w[93], pars->GC_3, pars->ZERO, pars->ZERO, w[95]); 
  FFV1_2(w[3], w[93], pars->GC_3, pars->ZERO, pars->ZERO, w[96]); 
  FFV2_3_3(w[1], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[97]);
  FFV2_3_3(w[0], w[5], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[98]);
  FFV2_4_1(w[2], w[98], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[99]);
  FFV2_4_2(w[3], w[98], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[100]);
  FFV1_2(w[1], w[93], pars->GC_1, pars->ZERO, pars->ZERO, w[101]); 
  FFV1_1(w[4], w[93], pars->GC_1, pars->ZERO, pars->ZERO, w[102]); 
  FFV2_3_2(w[1], w[98], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[103]);
  FFV2_3_1(w[4], w[98], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[104]);
  FFV1_2(w[0], w[94], pars->GC_1, pars->ZERO, pars->ZERO, w[105]); 
  FFV1_2(w[0], w[14], pars->GC_1, pars->ZERO, pars->ZERO, w[106]); 
  FFV2_3_2(w[0], w[17], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[107]);
  FFV2_3_2(w[0], w[97], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[108]);
  FFV1_2(w[0], w[82], pars->GC_1, pars->ZERO, pars->ZERO, w[109]); 
  FFV2_3_2(w[0], w[85], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[110]);
  FFV1P0_3(w[0], w[48], pars->GC_1, pars->ZERO, pars->ZERO, w[111]); 
  FFV1P0_3(w[49], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[112]); 
  FFV1_1(w[2], w[111], pars->GC_3, pars->ZERO, pars->ZERO, w[113]); 
  FFV1_2(w[3], w[111], pars->GC_3, pars->ZERO, pars->ZERO, w[114]); 
  FFV2_3_3(w[49], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[115]);
  FFV2_3_3(w[0], w[48], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[116]);
  FFV2_4_1(w[2], w[116], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[117]);
  FFV2_4_2(w[3], w[116], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[118]);
  FFV1_2(w[49], w[111], pars->GC_1, pars->ZERO, pars->ZERO, w[119]); 
  FFV1_1(w[4], w[111], pars->GC_1, pars->ZERO, pars->ZERO, w[120]); 
  FFV2_3_2(w[49], w[116], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[121]);
  FFV2_3_1(w[4], w[116], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[122]);
  FFV1P0_3(w[49], w[48], pars->GC_1, pars->ZERO, pars->ZERO, w[123]); 
  FFV2_3_3(w[49], w[48], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[124]);
  FFV1_2(w[49], w[81], pars->GC_1, pars->ZERO, pars->ZERO, w[125]); 
  FFV1_1(w[48], w[81], pars->GC_1, pars->ZERO, pars->ZERO, w[126]); 
  FFV2_3_2(w[49], w[86], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[127]);
  FFV2_3_1(w[48], w[86], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[128]);
  FFV1_2(w[0], w[123], pars->GC_1, pars->ZERO, pars->ZERO, w[129]); 
  FFV2_3_2(w[0], w[124], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[130]);
  FFV1_2(w[0], w[112], pars->GC_1, pars->ZERO, pars->ZERO, w[131]); 
  FFV2_3_2(w[0], w[115], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[132]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[133]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[134]); 
  FFV1P0_3(w[134], w[133], pars->GC_2, pars->ZERO, pars->ZERO, w[135]); 
  FFV1_1(w[2], w[135], pars->GC_3, pars->ZERO, pars->ZERO, w[136]); 
  FFV1_2(w[3], w[135], pars->GC_3, pars->ZERO, pars->ZERO, w[137]); 
  FFV2_5_3(w[134], w[133], pars->GC_51, pars->GC_58, pars->mdl_MZ,
      pars->mdl_WZ, w[138]);
  FFV2_4_1(w[2], w[138], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[139]);
  FFV2_4_2(w[3], w[138], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[140]);
  FFV1_2(w[49], w[135], pars->GC_2, pars->ZERO, pars->ZERO, w[141]); 
  FFV1_1(w[48], w[135], pars->GC_2, pars->ZERO, pars->ZERO, w[142]); 
  FFV1P0_3(w[134], w[133], pars->GC_11, pars->ZERO, pars->ZERO, w[143]); 
  FFV1_2(w[49], w[143], pars->GC_11, pars->ZERO, pars->ZERO, w[144]); 
  FFV1_1(w[48], w[143], pars->GC_11, pars->ZERO, pars->ZERO, w[145]); 
  FFV2_5_2(w[49], w[138], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[146]);
  FFV2_5_1(w[48], w[138], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[147]);
  FFV1P0_3(w[134], w[48], pars->GC_2, pars->ZERO, pars->ZERO, w[148]); 
  FFV1P0_3(w[49], w[133], pars->GC_2, pars->ZERO, pars->ZERO, w[149]); 
  FFV1_1(w[2], w[148], pars->GC_3, pars->ZERO, pars->ZERO, w[150]); 
  FFV1_2(w[3], w[148], pars->GC_3, pars->ZERO, pars->ZERO, w[151]); 
  FFV2_5_3(w[49], w[133], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[152]);
  FFV2_5_3(w[134], w[48], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[153]);
  FFV2_4_1(w[2], w[153], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[154]);
  FFV2_4_2(w[3], w[153], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[155]);
  FFV1_2(w[49], w[148], pars->GC_2, pars->ZERO, pars->ZERO, w[156]); 
  FFV1_1(w[133], w[148], pars->GC_2, pars->ZERO, pars->ZERO, w[157]); 
  FFV1P0_3(w[134], w[48], pars->GC_11, pars->ZERO, pars->ZERO, w[158]); 
  FFV1_2(w[49], w[158], pars->GC_11, pars->ZERO, pars->ZERO, w[159]); 
  FFV1_1(w[133], w[158], pars->GC_11, pars->ZERO, pars->ZERO, w[160]); 
  FFV2_5_2(w[49], w[153], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[161]);
  FFV2_5_1(w[133], w[153], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[162]);
  FFV1_2(w[134], w[149], pars->GC_2, pars->ZERO, pars->ZERO, w[163]); 
  FFV1_2(w[134], w[14], pars->GC_2, pars->ZERO, pars->ZERO, w[164]); 
  FFV2_5_2(w[134], w[17], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[165]);
  FFV1P0_3(w[49], w[133], pars->GC_11, pars->ZERO, pars->ZERO, w[166]); 
  FFV1_2(w[134], w[166], pars->GC_11, pars->ZERO, pars->ZERO, w[167]); 
  FFV2_5_2(w[134], w[152], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[168]);
  FFV1_2(w[134], w[65], pars->GC_2, pars->ZERO, pars->ZERO, w[169]); 
  FFV1_2(w[134], w[74], pars->GC_11, pars->ZERO, pars->ZERO, w[170]); 
  FFV2_5_2(w[134], w[66], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[171]);
  FFV1P0_3(w[134], w[133], pars->GC_1, pars->ZERO, pars->ZERO, w[172]); 
  FFV1_1(w[2], w[172], pars->GC_3, pars->ZERO, pars->ZERO, w[173]); 
  FFV1_2(w[3], w[172], pars->GC_3, pars->ZERO, pars->ZERO, w[174]); 
  FFV2_3_3(w[134], w[133], pars->GC_50, pars->GC_58, pars->mdl_MZ,
      pars->mdl_WZ, w[175]);
  FFV2_4_1(w[2], w[175], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[176]);
  FFV2_4_2(w[3], w[175], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[177]);
  FFV1_2(w[49], w[172], pars->GC_1, pars->ZERO, pars->ZERO, w[178]); 
  FFV1_1(w[48], w[172], pars->GC_1, pars->ZERO, pars->ZERO, w[179]); 
  FFV2_3_2(w[49], w[175], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[180]);
  FFV2_3_1(w[48], w[175], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[181]);
  FFV1P0_3(w[134], w[48], pars->GC_1, pars->ZERO, pars->ZERO, w[182]); 
  FFV1P0_3(w[49], w[133], pars->GC_1, pars->ZERO, pars->ZERO, w[183]); 
  FFV1_1(w[2], w[182], pars->GC_3, pars->ZERO, pars->ZERO, w[184]); 
  FFV1_2(w[3], w[182], pars->GC_3, pars->ZERO, pars->ZERO, w[185]); 
  FFV2_3_3(w[49], w[133], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[186]);
  FFV2_3_3(w[134], w[48], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[187]);
  FFV2_4_1(w[2], w[187], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[188]);
  FFV2_4_2(w[3], w[187], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[189]);
  FFV1_2(w[49], w[182], pars->GC_1, pars->ZERO, pars->ZERO, w[190]); 
  FFV1_1(w[133], w[182], pars->GC_1, pars->ZERO, pars->ZERO, w[191]); 
  FFV2_3_2(w[49], w[187], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[192]);
  FFV2_3_1(w[133], w[187], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[193]);
  FFV1_2(w[134], w[183], pars->GC_1, pars->ZERO, pars->ZERO, w[194]); 
  FFV1_2(w[134], w[14], pars->GC_1, pars->ZERO, pars->ZERO, w[195]); 
  FFV2_3_2(w[134], w[17], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[196]);
  FFV2_3_2(w[134], w[186], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[197]);
  FFV1_2(w[134], w[123], pars->GC_1, pars->ZERO, pars->ZERO, w[198]); 
  FFV2_3_2(w[134], w[124], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[199]);
  FFV1_2(w[1], w[6], pars->GC_1, pars->ZERO, pars->ZERO, w[200]); 
  FFV1_1(w[5], w[6], pars->GC_1, pars->ZERO, pars->ZERO, w[201]); 
  FFV2_3_2(w[1], w[11], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[202]);
  FFV2_3_1(w[5], w[11], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[203]);
  FFV2_3(w[0], w[5], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[204]); 
  FFV2_3(w[1], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[205]); 
  FFV2_2(w[3], w[204], pars->GC_100, pars->ZERO, pars->ZERO, w[206]); 
  FFV2_2(w[1], w[204], pars->GC_100, pars->ZERO, pars->ZERO, w[207]); 
  FFV2_1(w[4], w[204], pars->GC_100, pars->ZERO, pars->ZERO, w[208]); 
  FFV2_2(w[0], w[205], pars->GC_100, pars->ZERO, pars->ZERO, w[209]); 
  FFV1_2(w[0], w[82], pars->GC_2, pars->ZERO, pars->ZERO, w[210]); 
  FFV2_5_2(w[0], w[85], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[211]);
  FFV1_2(w[49], w[50], pars->GC_1, pars->ZERO, pars->ZERO, w[212]); 
  FFV1_1(w[4], w[50], pars->GC_1, pars->ZERO, pars->ZERO, w[213]); 
  FFV2_3_2(w[49], w[55], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[214]);
  FFV2_3_1(w[4], w[55], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[215]);
  FFV2_3(w[0], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[216]); 
  FFV2_3(w[49], w[48], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[217]); 
  FFV2_2(w[3], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[218]); 
  FFV2_2(w[49], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[219]); 
  FFV2_1(w[48], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[220]); 
  FFV2_2(w[0], w[217], pars->GC_100, pars->ZERO, pars->ZERO, w[221]); 
  FFV1_2(w[0], w[112], pars->GC_2, pars->ZERO, pars->ZERO, w[222]); 
  FFV2_5_2(w[0], w[115], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[223]);
  FFV1_2(w[49], w[6], pars->GC_1, pars->ZERO, pars->ZERO, w[224]); 
  FFV1_1(w[48], w[6], pars->GC_1, pars->ZERO, pars->ZERO, w[225]); 
  FFV2_3_2(w[49], w[11], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[226]);
  FFV2_3_1(w[48], w[11], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[227]);
  FFV2_3(w[0], w[48], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[228]); 
  FFV2_3(w[49], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[229]); 
  FFV2_2(w[3], w[228], pars->GC_100, pars->ZERO, pars->ZERO, w[230]); 
  FFV2_2(w[49], w[228], pars->GC_100, pars->ZERO, pars->ZERO, w[231]); 
  FFV2_1(w[4], w[228], pars->GC_100, pars->ZERO, pars->ZERO, w[232]); 
  FFV2_2(w[0], w[229], pars->GC_100, pars->ZERO, pars->ZERO, w[233]); 
  FFV1_2(w[0], w[123], pars->GC_2, pars->ZERO, pars->ZERO, w[234]); 
  FFV2_5_2(w[0], w[124], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[235]);
  FFV1_1(w[2], w[65], pars->GC_3, pars->ZERO, pars->ZERO, w[236]); 
  FFV1_2(w[3], w[65], pars->GC_3, pars->ZERO, pars->ZERO, w[237]); 
  FFV2_4_1(w[2], w[66], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[238]);
  FFV2_4_2(w[3], w[66], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[239]);
  FFV1_2(w[0], w[65], pars->GC_1, pars->ZERO, pars->ZERO, w[240]); 
  FFV1_1(w[4], w[65], pars->GC_1, pars->ZERO, pars->ZERO, w[241]); 
  FFV1_1(w[4], w[74], pars->GC_11, pars->ZERO, pars->ZERO, w[242]); 
  FFV2_3_2(w[0], w[66], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[243]);
  FFV2_3_1(w[4], w[66], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[244]);
  FFV2_2(w[3], w[229], pars->GC_100, pars->ZERO, pars->ZERO, w[245]); 
  FFV2_1(w[48], w[229], pars->GC_100, pars->ZERO, pars->ZERO, w[246]); 
  FFV1_2(w[49], w[14], pars->GC_2, pars->ZERO, pars->ZERO, w[247]); 
  FFV2_5_2(w[49], w[17], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[248]);
  FFV1_2(w[49], w[81], pars->GC_2, pars->ZERO, pars->ZERO, w[249]); 
  FFV2_5_2(w[49], w[86], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[250]);
  FFV1_1(w[2], w[51], pars->GC_3, pars->ZERO, pars->ZERO, w[251]); 
  FFV1_2(w[3], w[51], pars->GC_3, pars->ZERO, pars->ZERO, w[252]); 
  FFV2_4_1(w[2], w[54], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[253]);
  FFV2_4_2(w[3], w[54], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[254]);
  FFV1_2(w[0], w[51], pars->GC_1, pars->ZERO, pars->ZERO, w[255]); 
  FFV1_1(w[48], w[51], pars->GC_1, pars->ZERO, pars->ZERO, w[256]); 
  FFV1_1(w[48], w[78], pars->GC_11, pars->ZERO, pars->ZERO, w[257]); 
  FFV2_3_2(w[0], w[54], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[258]);
  FFV2_3_1(w[48], w[54], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[259]);
  FFV2_2(w[3], w[217], pars->GC_100, pars->ZERO, pars->ZERO, w[260]); 
  FFV2_1(w[4], w[217], pars->GC_100, pars->ZERO, pars->ZERO, w[261]); 
  FFV1_2(w[49], w[111], pars->GC_2, pars->ZERO, pars->ZERO, w[262]); 
  FFV2_5_2(w[49], w[116], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[263]);
  FFV1_2(w[49], w[135], pars->GC_1, pars->ZERO, pars->ZERO, w[264]); 
  FFV1_1(w[48], w[135], pars->GC_1, pars->ZERO, pars->ZERO, w[265]); 
  FFV2_3_2(w[49], w[138], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[266]);
  FFV2_3_1(w[48], w[138], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[267]);
  FFV2_3(w[134], w[48], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[268]); 
  FFV2_3(w[49], w[133], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[269]); 
  FFV2_2(w[3], w[268], pars->GC_100, pars->ZERO, pars->ZERO, w[270]); 
  FFV2_2(w[49], w[268], pars->GC_100, pars->ZERO, pars->ZERO, w[271]); 
  FFV2_1(w[133], w[268], pars->GC_100, pars->ZERO, pars->ZERO, w[272]); 
  FFV2_2(w[134], w[269], pars->GC_100, pars->ZERO, pars->ZERO, w[273]); 
  FFV1_2(w[134], w[123], pars->GC_2, pars->ZERO, pars->ZERO, w[274]); 
  FFV2_5_2(w[134], w[124], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[275]);
  FFV2_1(w[2], w[11], pars->GC_62, pars->ZERO, pars->ZERO, w[276]); 
  FFV2_2(w[3], w[11], pars->GC_62, pars->ZERO, pars->ZERO, w[277]); 
  FFV2_3(w[3], w[2], pars->GC_62, pars->mdl_MZ, pars->mdl_WZ, w[278]); 
  FFV2_1(w[2], w[28], pars->GC_62, pars->ZERO, pars->ZERO, w[279]); 
  FFV2_2(w[3], w[28], pars->GC_62, pars->ZERO, pars->ZERO, w[280]); 
  FFV2_5_2(w[0], w[278], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[281]);
  FFV2_1(w[2], w[55], pars->GC_62, pars->ZERO, pars->ZERO, w[282]); 
  FFV2_2(w[3], w[55], pars->GC_62, pars->ZERO, pars->ZERO, w[283]); 
  FFV2_1(w[2], w[86], pars->GC_62, pars->ZERO, pars->ZERO, w[284]); 
  FFV2_2(w[3], w[86], pars->GC_62, pars->ZERO, pars->ZERO, w[285]); 
  FFV2_1(w[2], w[98], pars->GC_62, pars->ZERO, pars->ZERO, w[286]); 
  FFV2_2(w[3], w[98], pars->GC_62, pars->ZERO, pars->ZERO, w[287]); 
  FFV2_3_2(w[0], w[278], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[288]);
  FFV2_1(w[2], w[116], pars->GC_62, pars->ZERO, pars->ZERO, w[289]); 
  FFV2_2(w[3], w[116], pars->GC_62, pars->ZERO, pars->ZERO, w[290]); 
  FFV2_1(w[2], w[138], pars->GC_62, pars->ZERO, pars->ZERO, w[291]); 
  FFV2_2(w[3], w[138], pars->GC_62, pars->ZERO, pars->ZERO, w[292]); 
  FFV2_1(w[2], w[153], pars->GC_62, pars->ZERO, pars->ZERO, w[293]); 
  FFV2_2(w[3], w[153], pars->GC_62, pars->ZERO, pars->ZERO, w[294]); 
  FFV2_5_2(w[134], w[278], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[295]);
  FFV2_1(w[2], w[175], pars->GC_62, pars->ZERO, pars->ZERO, w[296]); 
  FFV2_2(w[3], w[175], pars->GC_62, pars->ZERO, pars->ZERO, w[297]); 
  FFV2_1(w[2], w[187], pars->GC_62, pars->ZERO, pars->ZERO, w[298]); 
  FFV2_2(w[3], w[187], pars->GC_62, pars->ZERO, pars->ZERO, w[299]); 
  FFV2_3_2(w[134], w[278], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[300]);
  FFV2_3(w[1], w[5], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[301]); 
  FFV2_3(w[3], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[302]); 
  FFV2_1(w[2], w[204], pars->GC_100, pars->ZERO, pars->ZERO, w[303]); 
  FFV2_2(w[0], w[302], pars->GC_100, pars->ZERO, pars->ZERO, w[304]); 
  FFV1_2(w[1], w[23], pars->GC_1, pars->ZERO, pars->ZERO, w[305]); 
  FFV2_3_2(w[1], w[28], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[306]);
  FFV2_2(w[0], w[301], pars->GC_100, pars->ZERO, pars->ZERO, w[307]); 
  FFV2_1(w[2], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[308]); 
  FFV2_2(w[1], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[309]); 
  FFV1_2(w[0], w[94], pars->GC_2, pars->ZERO, pars->ZERO, w[310]); 
  FFV2_5_2(w[0], w[97], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[311]);
  FFV2_1(w[2], w[228], pars->GC_100, pars->ZERO, pars->ZERO, w[312]); 
  FFV2_1(w[5], w[216], pars->GC_100, pars->ZERO, pars->ZERO, w[313]); 
  FFV1_1(w[4], w[93], pars->GC_2, pars->ZERO, pars->ZERO, w[314]); 
  FFV2_5_1(w[4], w[98], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[315]);
  FFV2_2(w[3], w[66], pars->GC_62, pars->ZERO, pars->ZERO, w[316]); 
  FFV1_1(w[4], w[65], pars->GC_2, pars->ZERO, pars->ZERO, w[317]); 
  FFV2_5_1(w[4], w[66], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[318]);
  FFV2_2(w[3], w[54], pars->GC_62, pars->ZERO, pars->ZERO, w[319]); 
  FFV1_1(w[48], w[51], pars->GC_2, pars->ZERO, pars->ZERO, w[320]); 
  FFV2_5_1(w[48], w[54], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[321]);
  FFV1_1(w[48], w[81], pars->GC_2, pars->ZERO, pars->ZERO, w[322]); 
  FFV2_5_1(w[48], w[86], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[323]);
  FFV1_1(w[4], w[111], pars->GC_2, pars->ZERO, pars->ZERO, w[324]); 
  FFV2_5_1(w[4], w[116], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[325]);
  FFV2_1(w[2], w[217], pars->GC_100, pars->ZERO, pars->ZERO, w[326]); 
  FFV2_1(w[2], w[229], pars->GC_100, pars->ZERO, pars->ZERO, w[327]); 
  FFV2_2(w[49], w[302], pars->GC_100, pars->ZERO, pars->ZERO, w[328]); 
  FFV1_2(w[49], w[148], pars->GC_1, pars->ZERO, pars->ZERO, w[329]); 
  FFV2_3_2(w[49], w[153], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[330]);
  FFV2_2(w[134], w[217], pars->GC_100, pars->ZERO, pars->ZERO, w[331]); 
  FFV2_3(w[134], w[133], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[332]); 
  FFV2_2(w[3], w[332], pars->GC_100, pars->ZERO, pars->ZERO, w[333]); 
  FFV2_1(w[2], w[332], pars->GC_100, pars->ZERO, pars->ZERO, w[334]); 
  FFV2_1(w[48], w[332], pars->GC_100, pars->ZERO, pars->ZERO, w[335]); 
  FFV1_1(w[133], w[182], pars->GC_2, pars->ZERO, pars->ZERO, w[336]); 
  FFV2_5_1(w[133], w[187], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[337]);
  FFV2_2(w[134], w[302], pars->GC_100, pars->ZERO, pars->ZERO, w[338]); 
  FFV2_1(w[2], w[268], pars->GC_100, pars->ZERO, pars->ZERO, w[339]); 
  FFV2_2(w[49], w[332], pars->GC_100, pars->ZERO, pars->ZERO, w[340]); 
  FFV1_2(w[134], w[183], pars->GC_2, pars->ZERO, pars->ZERO, w[341]); 
  FFV2_5_2(w[134], w[186], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[342]);
  FFV2_1(w[2], w[66], pars->GC_62, pars->ZERO, pars->ZERO, w[343]); 
  FFV2_5_2(w[49], w[278], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[344]);
  FFV2_1(w[2], w[54], pars->GC_62, pars->ZERO, pars->ZERO, w[345]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[3], w[8], w[7], pars->GC_3, amp[0]); 
  FFV1_0(w[9], w[2], w[7], pars->GC_3, amp[1]); 
  FFV2_4_0(w[3], w[8], w[10], pars->GC_50, pars->GC_59, amp[2]); 
  FFV2_4_0(w[9], w[2], w[10], pars->GC_50, pars->GC_59, amp[3]); 
  FFV1_0(w[3], w[12], w[7], pars->GC_3, amp[4]); 
  FFV1_0(w[13], w[2], w[7], pars->GC_3, amp[5]); 
  FFV2_4_0(w[3], w[12], w[10], pars->GC_50, pars->GC_59, amp[6]); 
  FFV2_4_0(w[13], w[2], w[10], pars->GC_50, pars->GC_59, amp[7]); 
  FFV1_0(w[15], w[5], w[14], pars->GC_2, amp[8]); 
  FFV1_0(w[1], w[16], w[14], pars->GC_2, amp[9]); 
  FFV2_5_0(w[15], w[5], w[17], pars->GC_51, pars->GC_58, amp[10]); 
  FFV2_5_0(w[1], w[16], w[17], pars->GC_51, pars->GC_58, amp[11]); 
  FFV1_0(w[19], w[5], w[14], pars->GC_2, amp[12]); 
  FFV1_0(w[1], w[20], w[14], pars->GC_2, amp[13]); 
  FFV2_5_0(w[19], w[5], w[17], pars->GC_51, pars->GC_58, amp[14]); 
  FFV2_5_0(w[1], w[20], w[17], pars->GC_51, pars->GC_58, amp[15]); 
  FFV1_0(w[21], w[5], w[14], pars->GC_2, amp[16]); 
  FFV1_0(w[1], w[22], w[14], pars->GC_2, amp[17]); 
  FFV2_5_0(w[21], w[5], w[17], pars->GC_51, pars->GC_58, amp[18]); 
  FFV2_5_0(w[1], w[22], w[17], pars->GC_51, pars->GC_58, amp[19]); 
  FFV1_0(w[3], w[25], w[24], pars->GC_3, amp[20]); 
  FFV1_0(w[26], w[2], w[24], pars->GC_3, amp[21]); 
  FFV2_4_0(w[3], w[25], w[27], pars->GC_50, pars->GC_59, amp[22]); 
  FFV2_4_0(w[26], w[2], w[27], pars->GC_50, pars->GC_59, amp[23]); 
  FFV1_0(w[3], w[29], w[24], pars->GC_3, amp[24]); 
  FFV1_0(w[30], w[2], w[24], pars->GC_3, amp[25]); 
  FFV2_4_0(w[3], w[29], w[27], pars->GC_50, pars->GC_59, amp[26]); 
  FFV2_4_0(w[30], w[2], w[27], pars->GC_50, pars->GC_59, amp[27]); 
  FFV1_0(w[31], w[4], w[14], pars->GC_2, amp[28]); 
  FFV1_0(w[1], w[32], w[14], pars->GC_2, amp[29]); 
  FFV2_5_0(w[31], w[4], w[17], pars->GC_51, pars->GC_58, amp[30]); 
  FFV2_5_0(w[1], w[32], w[17], pars->GC_51, pars->GC_58, amp[31]); 
  FFV1_0(w[34], w[4], w[14], pars->GC_2, amp[32]); 
  FFV1_0(w[1], w[35], w[14], pars->GC_2, amp[33]); 
  FFV2_5_0(w[34], w[4], w[17], pars->GC_51, pars->GC_58, amp[34]); 
  FFV2_5_0(w[1], w[35], w[17], pars->GC_51, pars->GC_58, amp[35]); 
  FFV1_0(w[36], w[4], w[14], pars->GC_2, amp[36]); 
  FFV1_0(w[1], w[37], w[14], pars->GC_2, amp[37]); 
  FFV2_5_0(w[36], w[4], w[17], pars->GC_51, pars->GC_58, amp[38]); 
  FFV2_5_0(w[1], w[37], w[17], pars->GC_51, pars->GC_58, amp[39]); 
  FFV1_0(w[38], w[5], w[14], pars->GC_2, amp[40]); 
  FFV1_0(w[39], w[5], w[24], pars->GC_2, amp[41]); 
  FFV2_5_0(w[38], w[5], w[17], pars->GC_51, pars->GC_58, amp[42]); 
  FFV1_0(w[40], w[5], w[24], pars->GC_2, amp[43]); 
  FFV1_0(w[42], w[5], w[14], pars->GC_2, amp[44]); 
  FFV1_0(w[39], w[5], w[41], pars->GC_11, amp[45]); 
  FFV2_5_0(w[42], w[5], w[17], pars->GC_51, pars->GC_58, amp[46]); 
  FFV1_0(w[40], w[5], w[41], pars->GC_11, amp[47]); 
  FFV1_0(w[43], w[5], w[14], pars->GC_2, amp[48]); 
  FFV2_5_0(w[39], w[5], w[27], pars->GC_51, pars->GC_58, amp[49]); 
  FFV2_5_0(w[43], w[5], w[17], pars->GC_51, pars->GC_58, amp[50]); 
  FFV2_5_0(w[40], w[5], w[27], pars->GC_51, pars->GC_58, amp[51]); 
  FFV1_0(w[44], w[4], w[14], pars->GC_2, amp[52]); 
  FFV1_0(w[39], w[4], w[7], pars->GC_2, amp[53]); 
  FFV2_5_0(w[44], w[4], w[17], pars->GC_51, pars->GC_58, amp[54]); 
  FFV1_0(w[40], w[4], w[7], pars->GC_2, amp[55]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_2, amp[56]); 
  FFV1_0(w[39], w[4], w[45], pars->GC_11, amp[57]); 
  FFV2_5_0(w[46], w[4], w[17], pars->GC_51, pars->GC_58, amp[58]); 
  FFV1_0(w[40], w[4], w[45], pars->GC_11, amp[59]); 
  FFV1_0(w[47], w[4], w[14], pars->GC_2, amp[60]); 
  FFV2_5_0(w[39], w[4], w[10], pars->GC_51, pars->GC_58, amp[61]); 
  FFV2_5_0(w[47], w[4], w[17], pars->GC_51, pars->GC_58, amp[62]); 
  FFV2_5_0(w[40], w[4], w[10], pars->GC_51, pars->GC_58, amp[63]); 
  FFV1_0(w[3], w[52], w[51], pars->GC_3, amp[64]); 
  FFV1_0(w[53], w[2], w[51], pars->GC_3, amp[65]); 
  FFV2_4_0(w[3], w[52], w[54], pars->GC_50, pars->GC_59, amp[66]); 
  FFV2_4_0(w[53], w[2], w[54], pars->GC_50, pars->GC_59, amp[67]); 
  FFV1_0(w[3], w[56], w[51], pars->GC_3, amp[68]); 
  FFV1_0(w[57], w[2], w[51], pars->GC_3, amp[69]); 
  FFV2_4_0(w[3], w[56], w[54], pars->GC_50, pars->GC_59, amp[70]); 
  FFV2_4_0(w[57], w[2], w[54], pars->GC_50, pars->GC_59, amp[71]); 
  FFV1_0(w[58], w[4], w[14], pars->GC_2, amp[72]); 
  FFV1_0(w[49], w[59], w[14], pars->GC_2, amp[73]); 
  FFV2_5_0(w[58], w[4], w[17], pars->GC_51, pars->GC_58, amp[74]); 
  FFV2_5_0(w[49], w[59], w[17], pars->GC_51, pars->GC_58, amp[75]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_2, amp[76]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_2, amp[77]); 
  FFV2_5_0(w[61], w[4], w[17], pars->GC_51, pars->GC_58, amp[78]); 
  FFV2_5_0(w[49], w[62], w[17], pars->GC_51, pars->GC_58, amp[79]); 
  FFV1_0(w[63], w[4], w[14], pars->GC_2, amp[80]); 
  FFV1_0(w[49], w[64], w[14], pars->GC_2, amp[81]); 
  FFV2_5_0(w[63], w[4], w[17], pars->GC_51, pars->GC_58, amp[82]); 
  FFV2_5_0(w[49], w[64], w[17], pars->GC_51, pars->GC_58, amp[83]); 
  FFV1_0(w[3], w[8], w[65], pars->GC_3, amp[84]); 
  FFV1_0(w[9], w[2], w[65], pars->GC_3, amp[85]); 
  FFV2_4_0(w[3], w[8], w[66], pars->GC_50, pars->GC_59, amp[86]); 
  FFV2_4_0(w[9], w[2], w[66], pars->GC_50, pars->GC_59, amp[87]); 
  FFV1_0(w[3], w[12], w[65], pars->GC_3, amp[88]); 
  FFV1_0(w[13], w[2], w[65], pars->GC_3, amp[89]); 
  FFV2_4_0(w[3], w[12], w[66], pars->GC_50, pars->GC_59, amp[90]); 
  FFV2_4_0(w[13], w[2], w[66], pars->GC_50, pars->GC_59, amp[91]); 
  FFV1_0(w[67], w[48], w[14], pars->GC_2, amp[92]); 
  FFV1_0(w[49], w[68], w[14], pars->GC_2, amp[93]); 
  FFV2_5_0(w[67], w[48], w[17], pars->GC_51, pars->GC_58, amp[94]); 
  FFV2_5_0(w[49], w[68], w[17], pars->GC_51, pars->GC_58, amp[95]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_2, amp[96]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_2, amp[97]); 
  FFV2_5_0(w[69], w[48], w[17], pars->GC_51, pars->GC_58, amp[98]); 
  FFV2_5_0(w[49], w[70], w[17], pars->GC_51, pars->GC_58, amp[99]); 
  FFV1_0(w[71], w[48], w[14], pars->GC_2, amp[100]); 
  FFV1_0(w[49], w[72], w[14], pars->GC_2, amp[101]); 
  FFV2_5_0(w[71], w[48], w[17], pars->GC_51, pars->GC_58, amp[102]); 
  FFV2_5_0(w[49], w[72], w[17], pars->GC_51, pars->GC_58, amp[103]); 
  FFV1_0(w[73], w[4], w[14], pars->GC_2, amp[104]); 
  FFV1_0(w[39], w[4], w[65], pars->GC_2, amp[105]); 
  FFV2_5_0(w[73], w[4], w[17], pars->GC_51, pars->GC_58, amp[106]); 
  FFV1_0(w[40], w[4], w[65], pars->GC_2, amp[107]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_2, amp[108]); 
  FFV1_0(w[39], w[4], w[74], pars->GC_11, amp[109]); 
  FFV2_5_0(w[75], w[4], w[17], pars->GC_51, pars->GC_58, amp[110]); 
  FFV1_0(w[40], w[4], w[74], pars->GC_11, amp[111]); 
  FFV1_0(w[76], w[4], w[14], pars->GC_2, amp[112]); 
  FFV2_5_0(w[39], w[4], w[66], pars->GC_51, pars->GC_58, amp[113]); 
  FFV2_5_0(w[76], w[4], w[17], pars->GC_51, pars->GC_58, amp[114]); 
  FFV2_5_0(w[40], w[4], w[66], pars->GC_51, pars->GC_58, amp[115]); 
  FFV1_0(w[77], w[48], w[14], pars->GC_2, amp[116]); 
  FFV1_0(w[39], w[48], w[51], pars->GC_2, amp[117]); 
  FFV2_5_0(w[77], w[48], w[17], pars->GC_51, pars->GC_58, amp[118]); 
  FFV1_0(w[40], w[48], w[51], pars->GC_2, amp[119]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_2, amp[120]); 
  FFV1_0(w[39], w[48], w[78], pars->GC_11, amp[121]); 
  FFV2_5_0(w[79], w[48], w[17], pars->GC_51, pars->GC_58, amp[122]); 
  FFV1_0(w[40], w[48], w[78], pars->GC_11, amp[123]); 
  FFV1_0(w[80], w[48], w[14], pars->GC_2, amp[124]); 
  FFV2_5_0(w[39], w[48], w[54], pars->GC_51, pars->GC_58, amp[125]); 
  FFV2_5_0(w[80], w[48], w[17], pars->GC_51, pars->GC_58, amp[126]); 
  FFV2_5_0(w[40], w[48], w[54], pars->GC_51, pars->GC_58, amp[127]); 
  FFV1_0(w[3], w[83], w[82], pars->GC_3, amp[128]); 
  FFV1_0(w[84], w[2], w[82], pars->GC_3, amp[129]); 
  FFV2_4_0(w[3], w[83], w[85], pars->GC_50, pars->GC_59, amp[130]); 
  FFV2_4_0(w[84], w[2], w[85], pars->GC_50, pars->GC_59, amp[131]); 
  FFV1_0(w[3], w[87], w[82], pars->GC_3, amp[132]); 
  FFV1_0(w[88], w[2], w[82], pars->GC_3, amp[133]); 
  FFV2_4_0(w[3], w[87], w[85], pars->GC_50, pars->GC_59, amp[134]); 
  FFV2_4_0(w[88], w[2], w[85], pars->GC_50, pars->GC_59, amp[135]); 
  FFV1_0(w[89], w[5], w[14], pars->GC_1, amp[136]); 
  FFV1_0(w[1], w[90], w[14], pars->GC_1, amp[137]); 
  FFV2_3_0(w[89], w[5], w[17], pars->GC_50, pars->GC_58, amp[138]); 
  FFV2_3_0(w[1], w[90], w[17], pars->GC_50, pars->GC_58, amp[139]); 
  FFV1_0(w[19], w[5], w[14], pars->GC_1, amp[140]); 
  FFV1_0(w[1], w[20], w[14], pars->GC_1, amp[141]); 
  FFV2_3_0(w[19], w[5], w[17], pars->GC_50, pars->GC_58, amp[142]); 
  FFV2_3_0(w[1], w[20], w[17], pars->GC_50, pars->GC_58, amp[143]); 
  FFV1_0(w[91], w[5], w[14], pars->GC_1, amp[144]); 
  FFV1_0(w[1], w[92], w[14], pars->GC_1, amp[145]); 
  FFV2_3_0(w[91], w[5], w[17], pars->GC_50, pars->GC_58, amp[146]); 
  FFV2_3_0(w[1], w[92], w[17], pars->GC_50, pars->GC_58, amp[147]); 
  FFV1_0(w[3], w[95], w[94], pars->GC_3, amp[148]); 
  FFV1_0(w[96], w[2], w[94], pars->GC_3, amp[149]); 
  FFV2_4_0(w[3], w[95], w[97], pars->GC_50, pars->GC_59, amp[150]); 
  FFV2_4_0(w[96], w[2], w[97], pars->GC_50, pars->GC_59, amp[151]); 
  FFV1_0(w[3], w[99], w[94], pars->GC_3, amp[152]); 
  FFV1_0(w[100], w[2], w[94], pars->GC_3, amp[153]); 
  FFV2_4_0(w[3], w[99], w[97], pars->GC_50, pars->GC_59, amp[154]); 
  FFV2_4_0(w[100], w[2], w[97], pars->GC_50, pars->GC_59, amp[155]); 
  FFV1_0(w[101], w[4], w[14], pars->GC_1, amp[156]); 
  FFV1_0(w[1], w[102], w[14], pars->GC_1, amp[157]); 
  FFV2_3_0(w[101], w[4], w[17], pars->GC_50, pars->GC_58, amp[158]); 
  FFV2_3_0(w[1], w[102], w[17], pars->GC_50, pars->GC_58, amp[159]); 
  FFV1_0(w[34], w[4], w[14], pars->GC_1, amp[160]); 
  FFV1_0(w[1], w[35], w[14], pars->GC_1, amp[161]); 
  FFV2_3_0(w[34], w[4], w[17], pars->GC_50, pars->GC_58, amp[162]); 
  FFV2_3_0(w[1], w[35], w[17], pars->GC_50, pars->GC_58, amp[163]); 
  FFV1_0(w[103], w[4], w[14], pars->GC_1, amp[164]); 
  FFV1_0(w[1], w[104], w[14], pars->GC_1, amp[165]); 
  FFV2_3_0(w[103], w[4], w[17], pars->GC_50, pars->GC_58, amp[166]); 
  FFV2_3_0(w[1], w[104], w[17], pars->GC_50, pars->GC_58, amp[167]); 
  FFV1_0(w[105], w[5], w[14], pars->GC_1, amp[168]); 
  FFV1_0(w[106], w[5], w[94], pars->GC_1, amp[169]); 
  FFV2_3_0(w[105], w[5], w[17], pars->GC_50, pars->GC_58, amp[170]); 
  FFV1_0(w[107], w[5], w[94], pars->GC_1, amp[171]); 
  FFV1_0(w[42], w[5], w[14], pars->GC_1, amp[172]); 
  FFV1_0(w[106], w[5], w[41], pars->GC_11, amp[173]); 
  FFV2_3_0(w[42], w[5], w[17], pars->GC_50, pars->GC_58, amp[174]); 
  FFV1_0(w[107], w[5], w[41], pars->GC_11, amp[175]); 
  FFV1_0(w[108], w[5], w[14], pars->GC_1, amp[176]); 
  FFV2_3_0(w[106], w[5], w[97], pars->GC_50, pars->GC_58, amp[177]); 
  FFV2_3_0(w[108], w[5], w[17], pars->GC_50, pars->GC_58, amp[178]); 
  FFV2_3_0(w[107], w[5], w[97], pars->GC_50, pars->GC_58, amp[179]); 
  FFV1_0(w[109], w[4], w[14], pars->GC_1, amp[180]); 
  FFV1_0(w[106], w[4], w[82], pars->GC_1, amp[181]); 
  FFV2_3_0(w[109], w[4], w[17], pars->GC_50, pars->GC_58, amp[182]); 
  FFV1_0(w[107], w[4], w[82], pars->GC_1, amp[183]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_1, amp[184]); 
  FFV1_0(w[106], w[4], w[45], pars->GC_11, amp[185]); 
  FFV2_3_0(w[46], w[4], w[17], pars->GC_50, pars->GC_58, amp[186]); 
  FFV1_0(w[107], w[4], w[45], pars->GC_11, amp[187]); 
  FFV1_0(w[110], w[4], w[14], pars->GC_1, amp[188]); 
  FFV2_3_0(w[106], w[4], w[85], pars->GC_50, pars->GC_58, amp[189]); 
  FFV2_3_0(w[110], w[4], w[17], pars->GC_50, pars->GC_58, amp[190]); 
  FFV2_3_0(w[107], w[4], w[85], pars->GC_50, pars->GC_58, amp[191]); 
  FFV1_0(w[3], w[113], w[112], pars->GC_3, amp[192]); 
  FFV1_0(w[114], w[2], w[112], pars->GC_3, amp[193]); 
  FFV2_4_0(w[3], w[113], w[115], pars->GC_50, pars->GC_59, amp[194]); 
  FFV2_4_0(w[114], w[2], w[115], pars->GC_50, pars->GC_59, amp[195]); 
  FFV1_0(w[3], w[117], w[112], pars->GC_3, amp[196]); 
  FFV1_0(w[118], w[2], w[112], pars->GC_3, amp[197]); 
  FFV2_4_0(w[3], w[117], w[115], pars->GC_50, pars->GC_59, amp[198]); 
  FFV2_4_0(w[118], w[2], w[115], pars->GC_50, pars->GC_59, amp[199]); 
  FFV1_0(w[119], w[4], w[14], pars->GC_1, amp[200]); 
  FFV1_0(w[49], w[120], w[14], pars->GC_1, amp[201]); 
  FFV2_3_0(w[119], w[4], w[17], pars->GC_50, pars->GC_58, amp[202]); 
  FFV2_3_0(w[49], w[120], w[17], pars->GC_50, pars->GC_58, amp[203]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_1, amp[204]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_1, amp[205]); 
  FFV2_3_0(w[61], w[4], w[17], pars->GC_50, pars->GC_58, amp[206]); 
  FFV2_3_0(w[49], w[62], w[17], pars->GC_50, pars->GC_58, amp[207]); 
  FFV1_0(w[121], w[4], w[14], pars->GC_1, amp[208]); 
  FFV1_0(w[49], w[122], w[14], pars->GC_1, amp[209]); 
  FFV2_3_0(w[121], w[4], w[17], pars->GC_50, pars->GC_58, amp[210]); 
  FFV2_3_0(w[49], w[122], w[17], pars->GC_50, pars->GC_58, amp[211]); 
  FFV1_0(w[3], w[83], w[123], pars->GC_3, amp[212]); 
  FFV1_0(w[84], w[2], w[123], pars->GC_3, amp[213]); 
  FFV2_4_0(w[3], w[83], w[124], pars->GC_50, pars->GC_59, amp[214]); 
  FFV2_4_0(w[84], w[2], w[124], pars->GC_50, pars->GC_59, amp[215]); 
  FFV1_0(w[3], w[87], w[123], pars->GC_3, amp[216]); 
  FFV1_0(w[88], w[2], w[123], pars->GC_3, amp[217]); 
  FFV2_4_0(w[3], w[87], w[124], pars->GC_50, pars->GC_59, amp[218]); 
  FFV2_4_0(w[88], w[2], w[124], pars->GC_50, pars->GC_59, amp[219]); 
  FFV1_0(w[125], w[48], w[14], pars->GC_1, amp[220]); 
  FFV1_0(w[49], w[126], w[14], pars->GC_1, amp[221]); 
  FFV2_3_0(w[125], w[48], w[17], pars->GC_50, pars->GC_58, amp[222]); 
  FFV2_3_0(w[49], w[126], w[17], pars->GC_50, pars->GC_58, amp[223]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_1, amp[224]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_1, amp[225]); 
  FFV2_3_0(w[69], w[48], w[17], pars->GC_50, pars->GC_58, amp[226]); 
  FFV2_3_0(w[49], w[70], w[17], pars->GC_50, pars->GC_58, amp[227]); 
  FFV1_0(w[127], w[48], w[14], pars->GC_1, amp[228]); 
  FFV1_0(w[49], w[128], w[14], pars->GC_1, amp[229]); 
  FFV2_3_0(w[127], w[48], w[17], pars->GC_50, pars->GC_58, amp[230]); 
  FFV2_3_0(w[49], w[128], w[17], pars->GC_50, pars->GC_58, amp[231]); 
  FFV1_0(w[129], w[4], w[14], pars->GC_1, amp[232]); 
  FFV1_0(w[106], w[4], w[123], pars->GC_1, amp[233]); 
  FFV2_3_0(w[129], w[4], w[17], pars->GC_50, pars->GC_58, amp[234]); 
  FFV1_0(w[107], w[4], w[123], pars->GC_1, amp[235]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_1, amp[236]); 
  FFV1_0(w[106], w[4], w[74], pars->GC_11, amp[237]); 
  FFV2_3_0(w[75], w[4], w[17], pars->GC_50, pars->GC_58, amp[238]); 
  FFV1_0(w[107], w[4], w[74], pars->GC_11, amp[239]); 
  FFV1_0(w[130], w[4], w[14], pars->GC_1, amp[240]); 
  FFV2_3_0(w[106], w[4], w[124], pars->GC_50, pars->GC_58, amp[241]); 
  FFV2_3_0(w[130], w[4], w[17], pars->GC_50, pars->GC_58, amp[242]); 
  FFV2_3_0(w[107], w[4], w[124], pars->GC_50, pars->GC_58, amp[243]); 
  FFV1_0(w[131], w[48], w[14], pars->GC_1, amp[244]); 
  FFV1_0(w[106], w[48], w[112], pars->GC_1, amp[245]); 
  FFV2_3_0(w[131], w[48], w[17], pars->GC_50, pars->GC_58, amp[246]); 
  FFV1_0(w[107], w[48], w[112], pars->GC_1, amp[247]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_1, amp[248]); 
  FFV1_0(w[106], w[48], w[78], pars->GC_11, amp[249]); 
  FFV2_3_0(w[79], w[48], w[17], pars->GC_50, pars->GC_58, amp[250]); 
  FFV1_0(w[107], w[48], w[78], pars->GC_11, amp[251]); 
  FFV1_0(w[132], w[48], w[14], pars->GC_1, amp[252]); 
  FFV2_3_0(w[106], w[48], w[115], pars->GC_50, pars->GC_58, amp[253]); 
  FFV2_3_0(w[132], w[48], w[17], pars->GC_50, pars->GC_58, amp[254]); 
  FFV2_3_0(w[107], w[48], w[115], pars->GC_50, pars->GC_58, amp[255]); 
  FFV1_0(w[3], w[136], w[65], pars->GC_3, amp[256]); 
  FFV1_0(w[137], w[2], w[65], pars->GC_3, amp[257]); 
  FFV2_4_0(w[3], w[136], w[66], pars->GC_50, pars->GC_59, amp[258]); 
  FFV2_4_0(w[137], w[2], w[66], pars->GC_50, pars->GC_59, amp[259]); 
  FFV1_0(w[3], w[139], w[65], pars->GC_3, amp[260]); 
  FFV1_0(w[140], w[2], w[65], pars->GC_3, amp[261]); 
  FFV2_4_0(w[3], w[139], w[66], pars->GC_50, pars->GC_59, amp[262]); 
  FFV2_4_0(w[140], w[2], w[66], pars->GC_50, pars->GC_59, amp[263]); 
  FFV1_0(w[141], w[48], w[14], pars->GC_2, amp[264]); 
  FFV1_0(w[49], w[142], w[14], pars->GC_2, amp[265]); 
  FFV2_5_0(w[141], w[48], w[17], pars->GC_51, pars->GC_58, amp[266]); 
  FFV2_5_0(w[49], w[142], w[17], pars->GC_51, pars->GC_58, amp[267]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_2, amp[268]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_2, amp[269]); 
  FFV2_5_0(w[144], w[48], w[17], pars->GC_51, pars->GC_58, amp[270]); 
  FFV2_5_0(w[49], w[145], w[17], pars->GC_51, pars->GC_58, amp[271]); 
  FFV1_0(w[146], w[48], w[14], pars->GC_2, amp[272]); 
  FFV1_0(w[49], w[147], w[14], pars->GC_2, amp[273]); 
  FFV2_5_0(w[146], w[48], w[17], pars->GC_51, pars->GC_58, amp[274]); 
  FFV2_5_0(w[49], w[147], w[17], pars->GC_51, pars->GC_58, amp[275]); 
  FFV1_0(w[3], w[150], w[149], pars->GC_3, amp[276]); 
  FFV1_0(w[151], w[2], w[149], pars->GC_3, amp[277]); 
  FFV2_4_0(w[3], w[150], w[152], pars->GC_50, pars->GC_59, amp[278]); 
  FFV2_4_0(w[151], w[2], w[152], pars->GC_50, pars->GC_59, amp[279]); 
  FFV1_0(w[3], w[154], w[149], pars->GC_3, amp[280]); 
  FFV1_0(w[155], w[2], w[149], pars->GC_3, amp[281]); 
  FFV2_4_0(w[3], w[154], w[152], pars->GC_50, pars->GC_59, amp[282]); 
  FFV2_4_0(w[155], w[2], w[152], pars->GC_50, pars->GC_59, amp[283]); 
  FFV1_0(w[156], w[133], w[14], pars->GC_2, amp[284]); 
  FFV1_0(w[49], w[157], w[14], pars->GC_2, amp[285]); 
  FFV2_5_0(w[156], w[133], w[17], pars->GC_51, pars->GC_58, amp[286]); 
  FFV2_5_0(w[49], w[157], w[17], pars->GC_51, pars->GC_58, amp[287]); 
  FFV1_0(w[159], w[133], w[14], pars->GC_2, amp[288]); 
  FFV1_0(w[49], w[160], w[14], pars->GC_2, amp[289]); 
  FFV2_5_0(w[159], w[133], w[17], pars->GC_51, pars->GC_58, amp[290]); 
  FFV2_5_0(w[49], w[160], w[17], pars->GC_51, pars->GC_58, amp[291]); 
  FFV1_0(w[161], w[133], w[14], pars->GC_2, amp[292]); 
  FFV1_0(w[49], w[162], w[14], pars->GC_2, amp[293]); 
  FFV2_5_0(w[161], w[133], w[17], pars->GC_51, pars->GC_58, amp[294]); 
  FFV2_5_0(w[49], w[162], w[17], pars->GC_51, pars->GC_58, amp[295]); 
  FFV1_0(w[163], w[48], w[14], pars->GC_2, amp[296]); 
  FFV1_0(w[164], w[48], w[149], pars->GC_2, amp[297]); 
  FFV2_5_0(w[163], w[48], w[17], pars->GC_51, pars->GC_58, amp[298]); 
  FFV1_0(w[165], w[48], w[149], pars->GC_2, amp[299]); 
  FFV1_0(w[167], w[48], w[14], pars->GC_2, amp[300]); 
  FFV1_0(w[164], w[48], w[166], pars->GC_11, amp[301]); 
  FFV2_5_0(w[167], w[48], w[17], pars->GC_51, pars->GC_58, amp[302]); 
  FFV1_0(w[165], w[48], w[166], pars->GC_11, amp[303]); 
  FFV1_0(w[168], w[48], w[14], pars->GC_2, amp[304]); 
  FFV2_5_0(w[164], w[48], w[152], pars->GC_51, pars->GC_58, amp[305]); 
  FFV2_5_0(w[168], w[48], w[17], pars->GC_51, pars->GC_58, amp[306]); 
  FFV2_5_0(w[165], w[48], w[152], pars->GC_51, pars->GC_58, amp[307]); 
  FFV1_0(w[169], w[133], w[14], pars->GC_2, amp[308]); 
  FFV1_0(w[164], w[133], w[65], pars->GC_2, amp[309]); 
  FFV2_5_0(w[169], w[133], w[17], pars->GC_51, pars->GC_58, amp[310]); 
  FFV1_0(w[165], w[133], w[65], pars->GC_2, amp[311]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_2, amp[312]); 
  FFV1_0(w[164], w[133], w[74], pars->GC_11, amp[313]); 
  FFV2_5_0(w[170], w[133], w[17], pars->GC_51, pars->GC_58, amp[314]); 
  FFV1_0(w[165], w[133], w[74], pars->GC_11, amp[315]); 
  FFV1_0(w[171], w[133], w[14], pars->GC_2, amp[316]); 
  FFV2_5_0(w[164], w[133], w[66], pars->GC_51, pars->GC_58, amp[317]); 
  FFV2_5_0(w[171], w[133], w[17], pars->GC_51, pars->GC_58, amp[318]); 
  FFV2_5_0(w[165], w[133], w[66], pars->GC_51, pars->GC_58, amp[319]); 
  FFV1_0(w[3], w[173], w[123], pars->GC_3, amp[320]); 
  FFV1_0(w[174], w[2], w[123], pars->GC_3, amp[321]); 
  FFV2_4_0(w[3], w[173], w[124], pars->GC_50, pars->GC_59, amp[322]); 
  FFV2_4_0(w[174], w[2], w[124], pars->GC_50, pars->GC_59, amp[323]); 
  FFV1_0(w[3], w[176], w[123], pars->GC_3, amp[324]); 
  FFV1_0(w[177], w[2], w[123], pars->GC_3, amp[325]); 
  FFV2_4_0(w[3], w[176], w[124], pars->GC_50, pars->GC_59, amp[326]); 
  FFV2_4_0(w[177], w[2], w[124], pars->GC_50, pars->GC_59, amp[327]); 
  FFV1_0(w[178], w[48], w[14], pars->GC_1, amp[328]); 
  FFV1_0(w[49], w[179], w[14], pars->GC_1, amp[329]); 
  FFV2_3_0(w[178], w[48], w[17], pars->GC_50, pars->GC_58, amp[330]); 
  FFV2_3_0(w[49], w[179], w[17], pars->GC_50, pars->GC_58, amp[331]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_1, amp[332]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_1, amp[333]); 
  FFV2_3_0(w[144], w[48], w[17], pars->GC_50, pars->GC_58, amp[334]); 
  FFV2_3_0(w[49], w[145], w[17], pars->GC_50, pars->GC_58, amp[335]); 
  FFV1_0(w[180], w[48], w[14], pars->GC_1, amp[336]); 
  FFV1_0(w[49], w[181], w[14], pars->GC_1, amp[337]); 
  FFV2_3_0(w[180], w[48], w[17], pars->GC_50, pars->GC_58, amp[338]); 
  FFV2_3_0(w[49], w[181], w[17], pars->GC_50, pars->GC_58, amp[339]); 
  FFV1_0(w[3], w[184], w[183], pars->GC_3, amp[340]); 
  FFV1_0(w[185], w[2], w[183], pars->GC_3, amp[341]); 
  FFV2_4_0(w[3], w[184], w[186], pars->GC_50, pars->GC_59, amp[342]); 
  FFV2_4_0(w[185], w[2], w[186], pars->GC_50, pars->GC_59, amp[343]); 
  FFV1_0(w[3], w[188], w[183], pars->GC_3, amp[344]); 
  FFV1_0(w[189], w[2], w[183], pars->GC_3, amp[345]); 
  FFV2_4_0(w[3], w[188], w[186], pars->GC_50, pars->GC_59, amp[346]); 
  FFV2_4_0(w[189], w[2], w[186], pars->GC_50, pars->GC_59, amp[347]); 
  FFV1_0(w[190], w[133], w[14], pars->GC_1, amp[348]); 
  FFV1_0(w[49], w[191], w[14], pars->GC_1, amp[349]); 
  FFV2_3_0(w[190], w[133], w[17], pars->GC_50, pars->GC_58, amp[350]); 
  FFV2_3_0(w[49], w[191], w[17], pars->GC_50, pars->GC_58, amp[351]); 
  FFV1_0(w[159], w[133], w[14], pars->GC_1, amp[352]); 
  FFV1_0(w[49], w[160], w[14], pars->GC_1, amp[353]); 
  FFV2_3_0(w[159], w[133], w[17], pars->GC_50, pars->GC_58, amp[354]); 
  FFV2_3_0(w[49], w[160], w[17], pars->GC_50, pars->GC_58, amp[355]); 
  FFV1_0(w[192], w[133], w[14], pars->GC_1, amp[356]); 
  FFV1_0(w[49], w[193], w[14], pars->GC_1, amp[357]); 
  FFV2_3_0(w[192], w[133], w[17], pars->GC_50, pars->GC_58, amp[358]); 
  FFV2_3_0(w[49], w[193], w[17], pars->GC_50, pars->GC_58, amp[359]); 
  FFV1_0(w[194], w[48], w[14], pars->GC_1, amp[360]); 
  FFV1_0(w[195], w[48], w[183], pars->GC_1, amp[361]); 
  FFV2_3_0(w[194], w[48], w[17], pars->GC_50, pars->GC_58, amp[362]); 
  FFV1_0(w[196], w[48], w[183], pars->GC_1, amp[363]); 
  FFV1_0(w[167], w[48], w[14], pars->GC_1, amp[364]); 
  FFV1_0(w[195], w[48], w[166], pars->GC_11, amp[365]); 
  FFV2_3_0(w[167], w[48], w[17], pars->GC_50, pars->GC_58, amp[366]); 
  FFV1_0(w[196], w[48], w[166], pars->GC_11, amp[367]); 
  FFV1_0(w[197], w[48], w[14], pars->GC_1, amp[368]); 
  FFV2_3_0(w[195], w[48], w[186], pars->GC_50, pars->GC_58, amp[369]); 
  FFV2_3_0(w[197], w[48], w[17], pars->GC_50, pars->GC_58, amp[370]); 
  FFV2_3_0(w[196], w[48], w[186], pars->GC_50, pars->GC_58, amp[371]); 
  FFV1_0(w[198], w[133], w[14], pars->GC_1, amp[372]); 
  FFV1_0(w[195], w[133], w[123], pars->GC_1, amp[373]); 
  FFV2_3_0(w[198], w[133], w[17], pars->GC_50, pars->GC_58, amp[374]); 
  FFV1_0(w[196], w[133], w[123], pars->GC_1, amp[375]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_1, amp[376]); 
  FFV1_0(w[195], w[133], w[74], pars->GC_11, amp[377]); 
  FFV2_3_0(w[170], w[133], w[17], pars->GC_50, pars->GC_58, amp[378]); 
  FFV1_0(w[196], w[133], w[74], pars->GC_11, amp[379]); 
  FFV1_0(w[199], w[133], w[14], pars->GC_1, amp[380]); 
  FFV2_3_0(w[195], w[133], w[124], pars->GC_50, pars->GC_58, amp[381]); 
  FFV2_3_0(w[199], w[133], w[17], pars->GC_50, pars->GC_58, amp[382]); 
  FFV2_3_0(w[196], w[133], w[124], pars->GC_50, pars->GC_58, amp[383]); 
  FFV1_0(w[3], w[8], w[82], pars->GC_3, amp[384]); 
  FFV1_0(w[9], w[2], w[82], pars->GC_3, amp[385]); 
  FFV2_4_0(w[3], w[8], w[85], pars->GC_50, pars->GC_59, amp[386]); 
  FFV2_4_0(w[9], w[2], w[85], pars->GC_50, pars->GC_59, amp[387]); 
  FFV1_0(w[3], w[12], w[82], pars->GC_3, amp[388]); 
  FFV1_0(w[13], w[2], w[82], pars->GC_3, amp[389]); 
  FFV2_4_0(w[3], w[12], w[85], pars->GC_50, pars->GC_59, amp[390]); 
  FFV2_4_0(w[13], w[2], w[85], pars->GC_50, pars->GC_59, amp[391]); 
  FFV1_0(w[200], w[5], w[14], pars->GC_1, amp[392]); 
  FFV1_0(w[1], w[201], w[14], pars->GC_1, amp[393]); 
  FFV2_3_0(w[200], w[5], w[17], pars->GC_50, pars->GC_58, amp[394]); 
  FFV2_3_0(w[1], w[201], w[17], pars->GC_50, pars->GC_58, amp[395]); 
  FFV1_0(w[19], w[5], w[14], pars->GC_1, amp[396]); 
  FFV1_0(w[1], w[20], w[14], pars->GC_1, amp[397]); 
  FFV2_3_0(w[19], w[5], w[17], pars->GC_50, pars->GC_58, amp[398]); 
  FFV2_3_0(w[1], w[20], w[17], pars->GC_50, pars->GC_58, amp[399]); 
  FFV1_0(w[202], w[5], w[14], pars->GC_1, amp[400]); 
  FFV1_0(w[1], w[203], w[14], pars->GC_1, amp[401]); 
  FFV2_3_0(w[202], w[5], w[17], pars->GC_50, pars->GC_58, amp[402]); 
  FFV2_3_0(w[1], w[203], w[17], pars->GC_50, pars->GC_58, amp[403]); 
  FFV2_0(w[206], w[2], w[205], pars->GC_100, amp[404]); 
  VVV1_0(w[14], w[204], w[205], pars->GC_4, amp[405]); 
  VVV1_0(w[204], w[205], w[17], pars->GC_53, amp[406]); 
  FFV1_0(w[207], w[4], w[14], pars->GC_2, amp[407]); 
  FFV1_0(w[1], w[208], w[14], pars->GC_1, amp[408]); 
  FFV2_5_0(w[207], w[4], w[17], pars->GC_51, pars->GC_58, amp[409]); 
  FFV2_3_0(w[1], w[208], w[17], pars->GC_50, pars->GC_58, amp[410]); 
  FFV1_0(w[209], w[5], w[14], pars->GC_1, amp[411]); 
  FFV2_0(w[39], w[5], w[205], pars->GC_100, amp[412]); 
  FFV2_3_0(w[209], w[5], w[17], pars->GC_50, pars->GC_58, amp[413]); 
  FFV2_0(w[40], w[5], w[205], pars->GC_100, amp[414]); 
  FFV1_0(w[210], w[4], w[14], pars->GC_2, amp[415]); 
  FFV1_0(w[39], w[4], w[82], pars->GC_2, amp[416]); 
  FFV2_5_0(w[210], w[4], w[17], pars->GC_51, pars->GC_58, amp[417]); 
  FFV1_0(w[40], w[4], w[82], pars->GC_2, amp[418]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_2, amp[419]); 
  FFV1_0(w[39], w[4], w[45], pars->GC_11, amp[420]); 
  FFV2_5_0(w[46], w[4], w[17], pars->GC_51, pars->GC_58, amp[421]); 
  FFV1_0(w[40], w[4], w[45], pars->GC_11, amp[422]); 
  FFV1_0(w[211], w[4], w[14], pars->GC_2, amp[423]); 
  FFV2_5_0(w[39], w[4], w[85], pars->GC_51, pars->GC_58, amp[424]); 
  FFV2_5_0(w[211], w[4], w[17], pars->GC_51, pars->GC_58, amp[425]); 
  FFV2_5_0(w[40], w[4], w[85], pars->GC_51, pars->GC_58, amp[426]); 
  FFV1_0(w[3], w[52], w[112], pars->GC_3, amp[427]); 
  FFV1_0(w[53], w[2], w[112], pars->GC_3, amp[428]); 
  FFV2_4_0(w[3], w[52], w[115], pars->GC_50, pars->GC_59, amp[429]); 
  FFV2_4_0(w[53], w[2], w[115], pars->GC_50, pars->GC_59, amp[430]); 
  FFV1_0(w[3], w[56], w[112], pars->GC_3, amp[431]); 
  FFV1_0(w[57], w[2], w[112], pars->GC_3, amp[432]); 
  FFV2_4_0(w[3], w[56], w[115], pars->GC_50, pars->GC_59, amp[433]); 
  FFV2_4_0(w[57], w[2], w[115], pars->GC_50, pars->GC_59, amp[434]); 
  FFV1_0(w[212], w[4], w[14], pars->GC_1, amp[435]); 
  FFV1_0(w[49], w[213], w[14], pars->GC_1, amp[436]); 
  FFV2_3_0(w[212], w[4], w[17], pars->GC_50, pars->GC_58, amp[437]); 
  FFV2_3_0(w[49], w[213], w[17], pars->GC_50, pars->GC_58, amp[438]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_1, amp[439]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_1, amp[440]); 
  FFV2_3_0(w[61], w[4], w[17], pars->GC_50, pars->GC_58, amp[441]); 
  FFV2_3_0(w[49], w[62], w[17], pars->GC_50, pars->GC_58, amp[442]); 
  FFV1_0(w[214], w[4], w[14], pars->GC_1, amp[443]); 
  FFV1_0(w[49], w[215], w[14], pars->GC_1, amp[444]); 
  FFV2_3_0(w[214], w[4], w[17], pars->GC_50, pars->GC_58, amp[445]); 
  FFV2_3_0(w[49], w[215], w[17], pars->GC_50, pars->GC_58, amp[446]); 
  FFV2_0(w[218], w[2], w[217], pars->GC_100, amp[447]); 
  VVV1_0(w[14], w[216], w[217], pars->GC_4, amp[448]); 
  VVV1_0(w[216], w[217], w[17], pars->GC_53, amp[449]); 
  FFV1_0(w[219], w[48], w[14], pars->GC_2, amp[450]); 
  FFV1_0(w[49], w[220], w[14], pars->GC_1, amp[451]); 
  FFV2_5_0(w[219], w[48], w[17], pars->GC_51, pars->GC_58, amp[452]); 
  FFV2_3_0(w[49], w[220], w[17], pars->GC_50, pars->GC_58, amp[453]); 
  FFV1_0(w[221], w[4], w[14], pars->GC_1, amp[454]); 
  FFV2_0(w[39], w[4], w[217], pars->GC_100, amp[455]); 
  FFV2_3_0(w[221], w[4], w[17], pars->GC_50, pars->GC_58, amp[456]); 
  FFV2_0(w[40], w[4], w[217], pars->GC_100, amp[457]); 
  FFV1_0(w[222], w[48], w[14], pars->GC_2, amp[458]); 
  FFV1_0(w[39], w[48], w[112], pars->GC_2, amp[459]); 
  FFV2_5_0(w[222], w[48], w[17], pars->GC_51, pars->GC_58, amp[460]); 
  FFV1_0(w[40], w[48], w[112], pars->GC_2, amp[461]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_2, amp[462]); 
  FFV1_0(w[39], w[48], w[78], pars->GC_11, amp[463]); 
  FFV2_5_0(w[79], w[48], w[17], pars->GC_51, pars->GC_58, amp[464]); 
  FFV1_0(w[40], w[48], w[78], pars->GC_11, amp[465]); 
  FFV1_0(w[223], w[48], w[14], pars->GC_2, amp[466]); 
  FFV2_5_0(w[39], w[48], w[115], pars->GC_51, pars->GC_58, amp[467]); 
  FFV2_5_0(w[223], w[48], w[17], pars->GC_51, pars->GC_58, amp[468]); 
  FFV2_5_0(w[40], w[48], w[115], pars->GC_51, pars->GC_58, amp[469]); 
  FFV1_0(w[3], w[8], w[123], pars->GC_3, amp[470]); 
  FFV1_0(w[9], w[2], w[123], pars->GC_3, amp[471]); 
  FFV2_4_0(w[3], w[8], w[124], pars->GC_50, pars->GC_59, amp[472]); 
  FFV2_4_0(w[9], w[2], w[124], pars->GC_50, pars->GC_59, amp[473]); 
  FFV1_0(w[3], w[12], w[123], pars->GC_3, amp[474]); 
  FFV1_0(w[13], w[2], w[123], pars->GC_3, amp[475]); 
  FFV2_4_0(w[3], w[12], w[124], pars->GC_50, pars->GC_59, amp[476]); 
  FFV2_4_0(w[13], w[2], w[124], pars->GC_50, pars->GC_59, amp[477]); 
  FFV1_0(w[224], w[48], w[14], pars->GC_1, amp[478]); 
  FFV1_0(w[49], w[225], w[14], pars->GC_1, amp[479]); 
  FFV2_3_0(w[224], w[48], w[17], pars->GC_50, pars->GC_58, amp[480]); 
  FFV2_3_0(w[49], w[225], w[17], pars->GC_50, pars->GC_58, amp[481]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_1, amp[482]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_1, amp[483]); 
  FFV2_3_0(w[69], w[48], w[17], pars->GC_50, pars->GC_58, amp[484]); 
  FFV2_3_0(w[49], w[70], w[17], pars->GC_50, pars->GC_58, amp[485]); 
  FFV1_0(w[226], w[48], w[14], pars->GC_1, amp[486]); 
  FFV1_0(w[49], w[227], w[14], pars->GC_1, amp[487]); 
  FFV2_3_0(w[226], w[48], w[17], pars->GC_50, pars->GC_58, amp[488]); 
  FFV2_3_0(w[49], w[227], w[17], pars->GC_50, pars->GC_58, amp[489]); 
  FFV2_0(w[230], w[2], w[229], pars->GC_100, amp[490]); 
  VVV1_0(w[14], w[228], w[229], pars->GC_4, amp[491]); 
  VVV1_0(w[228], w[229], w[17], pars->GC_53, amp[492]); 
  FFV1_0(w[231], w[4], w[14], pars->GC_2, amp[493]); 
  FFV1_0(w[49], w[232], w[14], pars->GC_1, amp[494]); 
  FFV2_5_0(w[231], w[4], w[17], pars->GC_51, pars->GC_58, amp[495]); 
  FFV2_3_0(w[49], w[232], w[17], pars->GC_50, pars->GC_58, amp[496]); 
  FFV1_0(w[233], w[48], w[14], pars->GC_1, amp[497]); 
  FFV2_0(w[39], w[48], w[229], pars->GC_100, amp[498]); 
  FFV2_3_0(w[233], w[48], w[17], pars->GC_50, pars->GC_58, amp[499]); 
  FFV2_0(w[40], w[48], w[229], pars->GC_100, amp[500]); 
  FFV1_0(w[234], w[4], w[14], pars->GC_2, amp[501]); 
  FFV1_0(w[39], w[4], w[123], pars->GC_2, amp[502]); 
  FFV2_5_0(w[234], w[4], w[17], pars->GC_51, pars->GC_58, amp[503]); 
  FFV1_0(w[40], w[4], w[123], pars->GC_2, amp[504]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_2, amp[505]); 
  FFV1_0(w[39], w[4], w[74], pars->GC_11, amp[506]); 
  FFV2_5_0(w[75], w[4], w[17], pars->GC_51, pars->GC_58, amp[507]); 
  FFV1_0(w[40], w[4], w[74], pars->GC_11, amp[508]); 
  FFV1_0(w[235], w[4], w[14], pars->GC_2, amp[509]); 
  FFV2_5_0(w[39], w[4], w[124], pars->GC_51, pars->GC_58, amp[510]); 
  FFV2_5_0(w[235], w[4], w[17], pars->GC_51, pars->GC_58, amp[511]); 
  FFV2_5_0(w[40], w[4], w[124], pars->GC_51, pars->GC_58, amp[512]); 
  FFV1_0(w[3], w[236], w[81], pars->GC_3, amp[513]); 
  FFV1_0(w[237], w[2], w[81], pars->GC_3, amp[514]); 
  FFV2_4_0(w[3], w[236], w[86], pars->GC_50, pars->GC_59, amp[515]); 
  FFV2_4_0(w[237], w[2], w[86], pars->GC_50, pars->GC_59, amp[516]); 
  FFV1_0(w[3], w[238], w[81], pars->GC_3, amp[517]); 
  FFV1_0(w[239], w[2], w[81], pars->GC_3, amp[518]); 
  FFV2_4_0(w[3], w[238], w[86], pars->GC_50, pars->GC_59, amp[519]); 
  FFV2_4_0(w[239], w[2], w[86], pars->GC_50, pars->GC_59, amp[520]); 
  FFV1_0(w[240], w[4], w[14], pars->GC_1, amp[521]); 
  FFV1_0(w[0], w[241], w[14], pars->GC_1, amp[522]); 
  FFV2_3_0(w[240], w[4], w[17], pars->GC_50, pars->GC_58, amp[523]); 
  FFV2_3_0(w[0], w[241], w[17], pars->GC_50, pars->GC_58, amp[524]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_1, amp[525]); 
  FFV1_0(w[0], w[242], w[14], pars->GC_1, amp[526]); 
  FFV2_3_0(w[75], w[4], w[17], pars->GC_50, pars->GC_58, amp[527]); 
  FFV2_3_0(w[0], w[242], w[17], pars->GC_50, pars->GC_58, amp[528]); 
  FFV1_0(w[243], w[4], w[14], pars->GC_1, amp[529]); 
  FFV1_0(w[0], w[244], w[14], pars->GC_1, amp[530]); 
  FFV2_3_0(w[243], w[4], w[17], pars->GC_50, pars->GC_58, amp[531]); 
  FFV2_3_0(w[0], w[244], w[17], pars->GC_50, pars->GC_58, amp[532]); 
  FFV2_0(w[245], w[2], w[228], pars->GC_100, amp[533]); 
  VVV1_0(w[14], w[229], w[228], pars->GC_4, amp[534]); 
  VVV1_0(w[229], w[228], w[17], pars->GC_53, amp[535]); 
  FFV1_0(w[233], w[48], w[14], pars->GC_2, amp[536]); 
  FFV1_0(w[0], w[246], w[14], pars->GC_1, amp[537]); 
  FFV2_5_0(w[233], w[48], w[17], pars->GC_51, pars->GC_58, amp[538]); 
  FFV2_3_0(w[0], w[246], w[17], pars->GC_50, pars->GC_58, amp[539]); 
  FFV1_0(w[231], w[4], w[14], pars->GC_1, amp[540]); 
  FFV2_0(w[247], w[4], w[228], pars->GC_100, amp[541]); 
  FFV2_3_0(w[231], w[4], w[17], pars->GC_50, pars->GC_58, amp[542]); 
  FFV2_0(w[248], w[4], w[228], pars->GC_100, amp[543]); 
  FFV1_0(w[249], w[48], w[14], pars->GC_2, amp[544]); 
  FFV1_0(w[247], w[48], w[81], pars->GC_2, amp[545]); 
  FFV2_5_0(w[249], w[48], w[17], pars->GC_51, pars->GC_58, amp[546]); 
  FFV1_0(w[248], w[48], w[81], pars->GC_2, amp[547]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_2, amp[548]); 
  FFV1_0(w[247], w[48], w[18], pars->GC_11, amp[549]); 
  FFV2_5_0(w[69], w[48], w[17], pars->GC_51, pars->GC_58, amp[550]); 
  FFV1_0(w[248], w[48], w[18], pars->GC_11, amp[551]); 
  FFV1_0(w[250], w[48], w[14], pars->GC_2, amp[552]); 
  FFV2_5_0(w[247], w[48], w[86], pars->GC_51, pars->GC_58, amp[553]); 
  FFV2_5_0(w[250], w[48], w[17], pars->GC_51, pars->GC_58, amp[554]); 
  FFV2_5_0(w[248], w[48], w[86], pars->GC_51, pars->GC_58, amp[555]); 
  FFV1_0(w[3], w[251], w[111], pars->GC_3, amp[556]); 
  FFV1_0(w[252], w[2], w[111], pars->GC_3, amp[557]); 
  FFV2_4_0(w[3], w[251], w[116], pars->GC_50, pars->GC_59, amp[558]); 
  FFV2_4_0(w[252], w[2], w[116], pars->GC_50, pars->GC_59, amp[559]); 
  FFV1_0(w[3], w[253], w[111], pars->GC_3, amp[560]); 
  FFV1_0(w[254], w[2], w[111], pars->GC_3, amp[561]); 
  FFV2_4_0(w[3], w[253], w[116], pars->GC_50, pars->GC_59, amp[562]); 
  FFV2_4_0(w[254], w[2], w[116], pars->GC_50, pars->GC_59, amp[563]); 
  FFV1_0(w[255], w[48], w[14], pars->GC_1, amp[564]); 
  FFV1_0(w[0], w[256], w[14], pars->GC_1, amp[565]); 
  FFV2_3_0(w[255], w[48], w[17], pars->GC_50, pars->GC_58, amp[566]); 
  FFV2_3_0(w[0], w[256], w[17], pars->GC_50, pars->GC_58, amp[567]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_1, amp[568]); 
  FFV1_0(w[0], w[257], w[14], pars->GC_1, amp[569]); 
  FFV2_3_0(w[79], w[48], w[17], pars->GC_50, pars->GC_58, amp[570]); 
  FFV2_3_0(w[0], w[257], w[17], pars->GC_50, pars->GC_58, amp[571]); 
  FFV1_0(w[258], w[48], w[14], pars->GC_1, amp[572]); 
  FFV1_0(w[0], w[259], w[14], pars->GC_1, amp[573]); 
  FFV2_3_0(w[258], w[48], w[17], pars->GC_50, pars->GC_58, amp[574]); 
  FFV2_3_0(w[0], w[259], w[17], pars->GC_50, pars->GC_58, amp[575]); 
  FFV2_0(w[260], w[2], w[216], pars->GC_100, amp[576]); 
  VVV1_0(w[14], w[217], w[216], pars->GC_4, amp[577]); 
  VVV1_0(w[217], w[216], w[17], pars->GC_53, amp[578]); 
  FFV1_0(w[221], w[4], w[14], pars->GC_2, amp[579]); 
  FFV1_0(w[0], w[261], w[14], pars->GC_1, amp[580]); 
  FFV2_5_0(w[221], w[4], w[17], pars->GC_51, pars->GC_58, amp[581]); 
  FFV2_3_0(w[0], w[261], w[17], pars->GC_50, pars->GC_58, amp[582]); 
  FFV1_0(w[219], w[48], w[14], pars->GC_1, amp[583]); 
  FFV2_0(w[247], w[48], w[216], pars->GC_100, amp[584]); 
  FFV2_3_0(w[219], w[48], w[17], pars->GC_50, pars->GC_58, amp[585]); 
  FFV2_0(w[248], w[48], w[216], pars->GC_100, amp[586]); 
  FFV1_0(w[262], w[4], w[14], pars->GC_2, amp[587]); 
  FFV1_0(w[247], w[4], w[111], pars->GC_2, amp[588]); 
  FFV2_5_0(w[262], w[4], w[17], pars->GC_51, pars->GC_58, amp[589]); 
  FFV1_0(w[248], w[4], w[111], pars->GC_2, amp[590]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_2, amp[591]); 
  FFV1_0(w[247], w[4], w[60], pars->GC_11, amp[592]); 
  FFV2_5_0(w[61], w[4], w[17], pars->GC_51, pars->GC_58, amp[593]); 
  FFV1_0(w[248], w[4], w[60], pars->GC_11, amp[594]); 
  FFV1_0(w[263], w[4], w[14], pars->GC_2, amp[595]); 
  FFV2_5_0(w[247], w[4], w[116], pars->GC_51, pars->GC_58, amp[596]); 
  FFV2_5_0(w[263], w[4], w[17], pars->GC_51, pars->GC_58, amp[597]); 
  FFV2_5_0(w[248], w[4], w[116], pars->GC_51, pars->GC_58, amp[598]); 
  FFV1_0(w[3], w[136], w[123], pars->GC_3, amp[599]); 
  FFV1_0(w[137], w[2], w[123], pars->GC_3, amp[600]); 
  FFV2_4_0(w[3], w[136], w[124], pars->GC_50, pars->GC_59, amp[601]); 
  FFV2_4_0(w[137], w[2], w[124], pars->GC_50, pars->GC_59, amp[602]); 
  FFV1_0(w[3], w[139], w[123], pars->GC_3, amp[603]); 
  FFV1_0(w[140], w[2], w[123], pars->GC_3, amp[604]); 
  FFV2_4_0(w[3], w[139], w[124], pars->GC_50, pars->GC_59, amp[605]); 
  FFV2_4_0(w[140], w[2], w[124], pars->GC_50, pars->GC_59, amp[606]); 
  FFV1_0(w[264], w[48], w[14], pars->GC_1, amp[607]); 
  FFV1_0(w[49], w[265], w[14], pars->GC_1, amp[608]); 
  FFV2_3_0(w[264], w[48], w[17], pars->GC_50, pars->GC_58, amp[609]); 
  FFV2_3_0(w[49], w[265], w[17], pars->GC_50, pars->GC_58, amp[610]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_1, amp[611]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_1, amp[612]); 
  FFV2_3_0(w[144], w[48], w[17], pars->GC_50, pars->GC_58, amp[613]); 
  FFV2_3_0(w[49], w[145], w[17], pars->GC_50, pars->GC_58, amp[614]); 
  FFV1_0(w[266], w[48], w[14], pars->GC_1, amp[615]); 
  FFV1_0(w[49], w[267], w[14], pars->GC_1, amp[616]); 
  FFV2_3_0(w[266], w[48], w[17], pars->GC_50, pars->GC_58, amp[617]); 
  FFV2_3_0(w[49], w[267], w[17], pars->GC_50, pars->GC_58, amp[618]); 
  FFV2_0(w[270], w[2], w[269], pars->GC_100, amp[619]); 
  VVV1_0(w[14], w[268], w[269], pars->GC_4, amp[620]); 
  VVV1_0(w[268], w[269], w[17], pars->GC_53, amp[621]); 
  FFV1_0(w[271], w[133], w[14], pars->GC_2, amp[622]); 
  FFV1_0(w[49], w[272], w[14], pars->GC_1, amp[623]); 
  FFV2_5_0(w[271], w[133], w[17], pars->GC_51, pars->GC_58, amp[624]); 
  FFV2_3_0(w[49], w[272], w[17], pars->GC_50, pars->GC_58, amp[625]); 
  FFV1_0(w[273], w[48], w[14], pars->GC_1, amp[626]); 
  FFV2_0(w[164], w[48], w[269], pars->GC_100, amp[627]); 
  FFV2_3_0(w[273], w[48], w[17], pars->GC_50, pars->GC_58, amp[628]); 
  FFV2_0(w[165], w[48], w[269], pars->GC_100, amp[629]); 
  FFV1_0(w[274], w[133], w[14], pars->GC_2, amp[630]); 
  FFV1_0(w[164], w[133], w[123], pars->GC_2, amp[631]); 
  FFV2_5_0(w[274], w[133], w[17], pars->GC_51, pars->GC_58, amp[632]); 
  FFV1_0(w[165], w[133], w[123], pars->GC_2, amp[633]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_2, amp[634]); 
  FFV1_0(w[164], w[133], w[74], pars->GC_11, amp[635]); 
  FFV2_5_0(w[170], w[133], w[17], pars->GC_51, pars->GC_58, amp[636]); 
  FFV1_0(w[165], w[133], w[74], pars->GC_11, amp[637]); 
  FFV1_0(w[275], w[133], w[14], pars->GC_2, amp[638]); 
  FFV2_5_0(w[164], w[133], w[124], pars->GC_51, pars->GC_58, amp[639]); 
  FFV2_5_0(w[275], w[133], w[17], pars->GC_51, pars->GC_58, amp[640]); 
  FFV2_5_0(w[165], w[133], w[124], pars->GC_51, pars->GC_58, amp[641]); 
  FFV1_0(w[44], w[4], w[14], pars->GC_2, amp[642]); 
  FFV1_0(w[39], w[4], w[7], pars->GC_2, amp[643]); 
  FFV2_5_0(w[44], w[4], w[17], pars->GC_51, pars->GC_58, amp[644]); 
  FFV1_0(w[40], w[4], w[7], pars->GC_2, amp[645]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_2, amp[646]); 
  FFV1_0(w[39], w[4], w[45], pars->GC_11, amp[647]); 
  FFV2_5_0(w[46], w[4], w[17], pars->GC_51, pars->GC_58, amp[648]); 
  FFV1_0(w[40], w[4], w[45], pars->GC_11, amp[649]); 
  FFV1_0(w[47], w[4], w[14], pars->GC_2, amp[650]); 
  FFV2_5_0(w[39], w[4], w[10], pars->GC_51, pars->GC_58, amp[651]); 
  FFV2_5_0(w[47], w[4], w[17], pars->GC_51, pars->GC_58, amp[652]); 
  FFV2_5_0(w[40], w[4], w[10], pars->GC_51, pars->GC_58, amp[653]); 
  FFV1_0(w[3], w[8], w[82], pars->GC_3, amp[654]); 
  FFV1_0(w[9], w[2], w[82], pars->GC_3, amp[655]); 
  FFV2_4_0(w[3], w[8], w[85], pars->GC_50, pars->GC_59, amp[656]); 
  FFV2_4_0(w[9], w[2], w[85], pars->GC_50, pars->GC_59, amp[657]); 
  FFV1_0(w[3], w[12], w[82], pars->GC_3, amp[658]); 
  FFV1_0(w[13], w[2], w[82], pars->GC_3, amp[659]); 
  FFV2_4_0(w[3], w[12], w[85], pars->GC_50, pars->GC_59, amp[660]); 
  FFV2_4_0(w[13], w[2], w[85], pars->GC_50, pars->GC_59, amp[661]); 
  FFV1_0(w[200], w[5], w[14], pars->GC_1, amp[662]); 
  FFV1_0(w[1], w[201], w[14], pars->GC_1, amp[663]); 
  FFV2_3_0(w[200], w[5], w[17], pars->GC_50, pars->GC_58, amp[664]); 
  FFV2_3_0(w[1], w[201], w[17], pars->GC_50, pars->GC_58, amp[665]); 
  FFV1_0(w[19], w[5], w[14], pars->GC_1, amp[666]); 
  FFV1_0(w[1], w[20], w[14], pars->GC_1, amp[667]); 
  FFV2_3_0(w[19], w[5], w[17], pars->GC_50, pars->GC_58, amp[668]); 
  FFV2_3_0(w[1], w[20], w[17], pars->GC_50, pars->GC_58, amp[669]); 
  FFV1_0(w[202], w[5], w[14], pars->GC_1, amp[670]); 
  FFV1_0(w[1], w[203], w[14], pars->GC_1, amp[671]); 
  FFV2_3_0(w[202], w[5], w[17], pars->GC_50, pars->GC_58, amp[672]); 
  FFV2_3_0(w[1], w[203], w[17], pars->GC_50, pars->GC_58, amp[673]); 
  FFV1_0(w[210], w[4], w[14], pars->GC_2, amp[674]); 
  FFV1_0(w[39], w[4], w[82], pars->GC_2, amp[675]); 
  FFV2_5_0(w[210], w[4], w[17], pars->GC_51, pars->GC_58, amp[676]); 
  FFV1_0(w[40], w[4], w[82], pars->GC_2, amp[677]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_2, amp[678]); 
  FFV1_0(w[39], w[4], w[45], pars->GC_11, amp[679]); 
  FFV2_5_0(w[46], w[4], w[17], pars->GC_51, pars->GC_58, amp[680]); 
  FFV1_0(w[40], w[4], w[45], pars->GC_11, amp[681]); 
  FFV1_0(w[211], w[4], w[14], pars->GC_2, amp[682]); 
  FFV2_5_0(w[39], w[4], w[85], pars->GC_51, pars->GC_58, amp[683]); 
  FFV2_5_0(w[211], w[4], w[17], pars->GC_51, pars->GC_58, amp[684]); 
  FFV2_5_0(w[40], w[4], w[85], pars->GC_51, pars->GC_58, amp[685]); 
  FFV1_0(w[3], w[52], w[51], pars->GC_3, amp[686]); 
  FFV1_0(w[53], w[2], w[51], pars->GC_3, amp[687]); 
  FFV2_4_0(w[3], w[52], w[54], pars->GC_50, pars->GC_59, amp[688]); 
  FFV2_4_0(w[53], w[2], w[54], pars->GC_50, pars->GC_59, amp[689]); 
  FFV1_0(w[3], w[56], w[51], pars->GC_3, amp[690]); 
  FFV1_0(w[57], w[2], w[51], pars->GC_3, amp[691]); 
  FFV2_4_0(w[3], w[56], w[54], pars->GC_50, pars->GC_59, amp[692]); 
  FFV2_4_0(w[57], w[2], w[54], pars->GC_50, pars->GC_59, amp[693]); 
  FFV1_0(w[58], w[4], w[14], pars->GC_2, amp[694]); 
  FFV1_0(w[49], w[59], w[14], pars->GC_2, amp[695]); 
  FFV2_5_0(w[58], w[4], w[17], pars->GC_51, pars->GC_58, amp[696]); 
  FFV2_5_0(w[49], w[59], w[17], pars->GC_51, pars->GC_58, amp[697]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_2, amp[698]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_2, amp[699]); 
  FFV2_5_0(w[61], w[4], w[17], pars->GC_51, pars->GC_58, amp[700]); 
  FFV2_5_0(w[49], w[62], w[17], pars->GC_51, pars->GC_58, amp[701]); 
  FFV1_0(w[63], w[4], w[14], pars->GC_2, amp[702]); 
  FFV1_0(w[49], w[64], w[14], pars->GC_2, amp[703]); 
  FFV2_5_0(w[63], w[4], w[17], pars->GC_51, pars->GC_58, amp[704]); 
  FFV2_5_0(w[49], w[64], w[17], pars->GC_51, pars->GC_58, amp[705]); 
  FFV1_0(w[77], w[48], w[14], pars->GC_2, amp[706]); 
  FFV1_0(w[39], w[48], w[51], pars->GC_2, amp[707]); 
  FFV2_5_0(w[77], w[48], w[17], pars->GC_51, pars->GC_58, amp[708]); 
  FFV1_0(w[40], w[48], w[51], pars->GC_2, amp[709]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_2, amp[710]); 
  FFV1_0(w[39], w[48], w[78], pars->GC_11, amp[711]); 
  FFV2_5_0(w[79], w[48], w[17], pars->GC_51, pars->GC_58, amp[712]); 
  FFV1_0(w[40], w[48], w[78], pars->GC_11, amp[713]); 
  FFV1_0(w[80], w[48], w[14], pars->GC_2, amp[714]); 
  FFV2_5_0(w[39], w[48], w[54], pars->GC_51, pars->GC_58, amp[715]); 
  FFV2_5_0(w[80], w[48], w[17], pars->GC_51, pars->GC_58, amp[716]); 
  FFV2_5_0(w[40], w[48], w[54], pars->GC_51, pars->GC_58, amp[717]); 
  FFV1_0(w[3], w[52], w[112], pars->GC_3, amp[718]); 
  FFV1_0(w[53], w[2], w[112], pars->GC_3, amp[719]); 
  FFV2_4_0(w[3], w[52], w[115], pars->GC_50, pars->GC_59, amp[720]); 
  FFV2_4_0(w[53], w[2], w[115], pars->GC_50, pars->GC_59, amp[721]); 
  FFV1_0(w[3], w[56], w[112], pars->GC_3, amp[722]); 
  FFV1_0(w[57], w[2], w[112], pars->GC_3, amp[723]); 
  FFV2_4_0(w[3], w[56], w[115], pars->GC_50, pars->GC_59, amp[724]); 
  FFV2_4_0(w[57], w[2], w[115], pars->GC_50, pars->GC_59, amp[725]); 
  FFV1_0(w[212], w[4], w[14], pars->GC_1, amp[726]); 
  FFV1_0(w[49], w[213], w[14], pars->GC_1, amp[727]); 
  FFV2_3_0(w[212], w[4], w[17], pars->GC_50, pars->GC_58, amp[728]); 
  FFV2_3_0(w[49], w[213], w[17], pars->GC_50, pars->GC_58, amp[729]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_1, amp[730]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_1, amp[731]); 
  FFV2_3_0(w[61], w[4], w[17], pars->GC_50, pars->GC_58, amp[732]); 
  FFV2_3_0(w[49], w[62], w[17], pars->GC_50, pars->GC_58, amp[733]); 
  FFV1_0(w[214], w[4], w[14], pars->GC_1, amp[734]); 
  FFV1_0(w[49], w[215], w[14], pars->GC_1, amp[735]); 
  FFV2_3_0(w[214], w[4], w[17], pars->GC_50, pars->GC_58, amp[736]); 
  FFV2_3_0(w[49], w[215], w[17], pars->GC_50, pars->GC_58, amp[737]); 
  FFV1_0(w[222], w[48], w[14], pars->GC_2, amp[738]); 
  FFV1_0(w[39], w[48], w[112], pars->GC_2, amp[739]); 
  FFV2_5_0(w[222], w[48], w[17], pars->GC_51, pars->GC_58, amp[740]); 
  FFV1_0(w[40], w[48], w[112], pars->GC_2, amp[741]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_2, amp[742]); 
  FFV1_0(w[39], w[48], w[78], pars->GC_11, amp[743]); 
  FFV2_5_0(w[79], w[48], w[17], pars->GC_51, pars->GC_58, amp[744]); 
  FFV1_0(w[40], w[48], w[78], pars->GC_11, amp[745]); 
  FFV1_0(w[223], w[48], w[14], pars->GC_2, amp[746]); 
  FFV2_5_0(w[39], w[48], w[115], pars->GC_51, pars->GC_58, amp[747]); 
  FFV2_5_0(w[223], w[48], w[17], pars->GC_51, pars->GC_58, amp[748]); 
  FFV2_5_0(w[40], w[48], w[115], pars->GC_51, pars->GC_58, amp[749]); 
  FFV1_0(w[3], w[8], w[65], pars->GC_3, amp[750]); 
  FFV1_0(w[9], w[2], w[65], pars->GC_3, amp[751]); 
  FFV2_4_0(w[3], w[8], w[66], pars->GC_50, pars->GC_59, amp[752]); 
  FFV2_4_0(w[9], w[2], w[66], pars->GC_50, pars->GC_59, amp[753]); 
  FFV1_0(w[3], w[12], w[65], pars->GC_3, amp[754]); 
  FFV1_0(w[13], w[2], w[65], pars->GC_3, amp[755]); 
  FFV2_4_0(w[3], w[12], w[66], pars->GC_50, pars->GC_59, amp[756]); 
  FFV2_4_0(w[13], w[2], w[66], pars->GC_50, pars->GC_59, amp[757]); 
  FFV1_0(w[67], w[48], w[14], pars->GC_2, amp[758]); 
  FFV1_0(w[49], w[68], w[14], pars->GC_2, amp[759]); 
  FFV2_5_0(w[67], w[48], w[17], pars->GC_51, pars->GC_58, amp[760]); 
  FFV2_5_0(w[49], w[68], w[17], pars->GC_51, pars->GC_58, amp[761]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_2, amp[762]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_2, amp[763]); 
  FFV2_5_0(w[69], w[48], w[17], pars->GC_51, pars->GC_58, amp[764]); 
  FFV2_5_0(w[49], w[70], w[17], pars->GC_51, pars->GC_58, amp[765]); 
  FFV1_0(w[71], w[48], w[14], pars->GC_2, amp[766]); 
  FFV1_0(w[49], w[72], w[14], pars->GC_2, amp[767]); 
  FFV2_5_0(w[71], w[48], w[17], pars->GC_51, pars->GC_58, amp[768]); 
  FFV2_5_0(w[49], w[72], w[17], pars->GC_51, pars->GC_58, amp[769]); 
  FFV1_0(w[73], w[4], w[14], pars->GC_2, amp[770]); 
  FFV1_0(w[39], w[4], w[65], pars->GC_2, amp[771]); 
  FFV2_5_0(w[73], w[4], w[17], pars->GC_51, pars->GC_58, amp[772]); 
  FFV1_0(w[40], w[4], w[65], pars->GC_2, amp[773]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_2, amp[774]); 
  FFV1_0(w[39], w[4], w[74], pars->GC_11, amp[775]); 
  FFV2_5_0(w[75], w[4], w[17], pars->GC_51, pars->GC_58, amp[776]); 
  FFV1_0(w[40], w[4], w[74], pars->GC_11, amp[777]); 
  FFV1_0(w[76], w[4], w[14], pars->GC_2, amp[778]); 
  FFV2_5_0(w[39], w[4], w[66], pars->GC_51, pars->GC_58, amp[779]); 
  FFV2_5_0(w[76], w[4], w[17], pars->GC_51, pars->GC_58, amp[780]); 
  FFV2_5_0(w[40], w[4], w[66], pars->GC_51, pars->GC_58, amp[781]); 
  FFV1_0(w[3], w[8], w[123], pars->GC_3, amp[782]); 
  FFV1_0(w[9], w[2], w[123], pars->GC_3, amp[783]); 
  FFV2_4_0(w[3], w[8], w[124], pars->GC_50, pars->GC_59, amp[784]); 
  FFV2_4_0(w[9], w[2], w[124], pars->GC_50, pars->GC_59, amp[785]); 
  FFV1_0(w[3], w[12], w[123], pars->GC_3, amp[786]); 
  FFV1_0(w[13], w[2], w[123], pars->GC_3, amp[787]); 
  FFV2_4_0(w[3], w[12], w[124], pars->GC_50, pars->GC_59, amp[788]); 
  FFV2_4_0(w[13], w[2], w[124], pars->GC_50, pars->GC_59, amp[789]); 
  FFV1_0(w[224], w[48], w[14], pars->GC_1, amp[790]); 
  FFV1_0(w[49], w[225], w[14], pars->GC_1, amp[791]); 
  FFV2_3_0(w[224], w[48], w[17], pars->GC_50, pars->GC_58, amp[792]); 
  FFV2_3_0(w[49], w[225], w[17], pars->GC_50, pars->GC_58, amp[793]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_1, amp[794]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_1, amp[795]); 
  FFV2_3_0(w[69], w[48], w[17], pars->GC_50, pars->GC_58, amp[796]); 
  FFV2_3_0(w[49], w[70], w[17], pars->GC_50, pars->GC_58, amp[797]); 
  FFV1_0(w[226], w[48], w[14], pars->GC_1, amp[798]); 
  FFV1_0(w[49], w[227], w[14], pars->GC_1, amp[799]); 
  FFV2_3_0(w[226], w[48], w[17], pars->GC_50, pars->GC_58, amp[800]); 
  FFV2_3_0(w[49], w[227], w[17], pars->GC_50, pars->GC_58, amp[801]); 
  FFV1_0(w[234], w[4], w[14], pars->GC_2, amp[802]); 
  FFV1_0(w[39], w[4], w[123], pars->GC_2, amp[803]); 
  FFV2_5_0(w[234], w[4], w[17], pars->GC_51, pars->GC_58, amp[804]); 
  FFV1_0(w[40], w[4], w[123], pars->GC_2, amp[805]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_2, amp[806]); 
  FFV1_0(w[39], w[4], w[74], pars->GC_11, amp[807]); 
  FFV2_5_0(w[75], w[4], w[17], pars->GC_51, pars->GC_58, amp[808]); 
  FFV1_0(w[40], w[4], w[74], pars->GC_11, amp[809]); 
  FFV1_0(w[235], w[4], w[14], pars->GC_2, amp[810]); 
  FFV2_5_0(w[39], w[4], w[124], pars->GC_51, pars->GC_58, amp[811]); 
  FFV2_5_0(w[235], w[4], w[17], pars->GC_51, pars->GC_58, amp[812]); 
  FFV2_5_0(w[40], w[4], w[124], pars->GC_51, pars->GC_58, amp[813]); 
  FFV1_0(w[3], w[83], w[82], pars->GC_3, amp[814]); 
  FFV1_0(w[84], w[2], w[82], pars->GC_3, amp[815]); 
  FFV2_4_0(w[3], w[83], w[85], pars->GC_50, pars->GC_59, amp[816]); 
  FFV2_4_0(w[84], w[2], w[85], pars->GC_50, pars->GC_59, amp[817]); 
  FFV1_0(w[3], w[87], w[82], pars->GC_3, amp[818]); 
  FFV1_0(w[88], w[2], w[82], pars->GC_3, amp[819]); 
  FFV2_4_0(w[3], w[87], w[85], pars->GC_50, pars->GC_59, amp[820]); 
  FFV2_4_0(w[88], w[2], w[85], pars->GC_50, pars->GC_59, amp[821]); 
  FFV1_0(w[89], w[5], w[14], pars->GC_1, amp[822]); 
  FFV1_0(w[1], w[90], w[14], pars->GC_1, amp[823]); 
  FFV2_3_0(w[89], w[5], w[17], pars->GC_50, pars->GC_58, amp[824]); 
  FFV2_3_0(w[1], w[90], w[17], pars->GC_50, pars->GC_58, amp[825]); 
  FFV1_0(w[19], w[5], w[14], pars->GC_1, amp[826]); 
  FFV1_0(w[1], w[20], w[14], pars->GC_1, amp[827]); 
  FFV2_3_0(w[19], w[5], w[17], pars->GC_50, pars->GC_58, amp[828]); 
  FFV2_3_0(w[1], w[20], w[17], pars->GC_50, pars->GC_58, amp[829]); 
  FFV1_0(w[91], w[5], w[14], pars->GC_1, amp[830]); 
  FFV1_0(w[1], w[92], w[14], pars->GC_1, amp[831]); 
  FFV2_3_0(w[91], w[5], w[17], pars->GC_50, pars->GC_58, amp[832]); 
  FFV2_3_0(w[1], w[92], w[17], pars->GC_50, pars->GC_58, amp[833]); 
  FFV1_0(w[109], w[4], w[14], pars->GC_1, amp[834]); 
  FFV1_0(w[106], w[4], w[82], pars->GC_1, amp[835]); 
  FFV2_3_0(w[109], w[4], w[17], pars->GC_50, pars->GC_58, amp[836]); 
  FFV1_0(w[107], w[4], w[82], pars->GC_1, amp[837]); 
  FFV1_0(w[46], w[4], w[14], pars->GC_1, amp[838]); 
  FFV1_0(w[106], w[4], w[45], pars->GC_11, amp[839]); 
  FFV2_3_0(w[46], w[4], w[17], pars->GC_50, pars->GC_58, amp[840]); 
  FFV1_0(w[107], w[4], w[45], pars->GC_11, amp[841]); 
  FFV1_0(w[110], w[4], w[14], pars->GC_1, amp[842]); 
  FFV2_3_0(w[106], w[4], w[85], pars->GC_50, pars->GC_58, amp[843]); 
  FFV2_3_0(w[110], w[4], w[17], pars->GC_50, pars->GC_58, amp[844]); 
  FFV2_3_0(w[107], w[4], w[85], pars->GC_50, pars->GC_58, amp[845]); 
  FFV1_0(w[3], w[236], w[81], pars->GC_3, amp[846]); 
  FFV1_0(w[237], w[2], w[81], pars->GC_3, amp[847]); 
  FFV2_4_0(w[3], w[236], w[86], pars->GC_50, pars->GC_59, amp[848]); 
  FFV2_4_0(w[237], w[2], w[86], pars->GC_50, pars->GC_59, amp[849]); 
  FFV1_0(w[3], w[238], w[81], pars->GC_3, amp[850]); 
  FFV1_0(w[239], w[2], w[81], pars->GC_3, amp[851]); 
  FFV2_4_0(w[3], w[238], w[86], pars->GC_50, pars->GC_59, amp[852]); 
  FFV2_4_0(w[239], w[2], w[86], pars->GC_50, pars->GC_59, amp[853]); 
  FFV1_0(w[240], w[4], w[14], pars->GC_1, amp[854]); 
  FFV1_0(w[0], w[241], w[14], pars->GC_1, amp[855]); 
  FFV2_3_0(w[240], w[4], w[17], pars->GC_50, pars->GC_58, amp[856]); 
  FFV2_3_0(w[0], w[241], w[17], pars->GC_50, pars->GC_58, amp[857]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_1, amp[858]); 
  FFV1_0(w[0], w[242], w[14], pars->GC_1, amp[859]); 
  FFV2_3_0(w[75], w[4], w[17], pars->GC_50, pars->GC_58, amp[860]); 
  FFV2_3_0(w[0], w[242], w[17], pars->GC_50, pars->GC_58, amp[861]); 
  FFV1_0(w[243], w[4], w[14], pars->GC_1, amp[862]); 
  FFV1_0(w[0], w[244], w[14], pars->GC_1, amp[863]); 
  FFV2_3_0(w[243], w[4], w[17], pars->GC_50, pars->GC_58, amp[864]); 
  FFV2_3_0(w[0], w[244], w[17], pars->GC_50, pars->GC_58, amp[865]); 
  FFV1_0(w[249], w[48], w[14], pars->GC_2, amp[866]); 
  FFV1_0(w[247], w[48], w[81], pars->GC_2, amp[867]); 
  FFV2_5_0(w[249], w[48], w[17], pars->GC_51, pars->GC_58, amp[868]); 
  FFV1_0(w[248], w[48], w[81], pars->GC_2, amp[869]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_2, amp[870]); 
  FFV1_0(w[247], w[48], w[18], pars->GC_11, amp[871]); 
  FFV2_5_0(w[69], w[48], w[17], pars->GC_51, pars->GC_58, amp[872]); 
  FFV1_0(w[248], w[48], w[18], pars->GC_11, amp[873]); 
  FFV1_0(w[250], w[48], w[14], pars->GC_2, amp[874]); 
  FFV2_5_0(w[247], w[48], w[86], pars->GC_51, pars->GC_58, amp[875]); 
  FFV2_5_0(w[250], w[48], w[17], pars->GC_51, pars->GC_58, amp[876]); 
  FFV2_5_0(w[248], w[48], w[86], pars->GC_51, pars->GC_58, amp[877]); 
  FFV1_0(w[3], w[251], w[111], pars->GC_3, amp[878]); 
  FFV1_0(w[252], w[2], w[111], pars->GC_3, amp[879]); 
  FFV2_4_0(w[3], w[251], w[116], pars->GC_50, pars->GC_59, amp[880]); 
  FFV2_4_0(w[252], w[2], w[116], pars->GC_50, pars->GC_59, amp[881]); 
  FFV1_0(w[3], w[253], w[111], pars->GC_3, amp[882]); 
  FFV1_0(w[254], w[2], w[111], pars->GC_3, amp[883]); 
  FFV2_4_0(w[3], w[253], w[116], pars->GC_50, pars->GC_59, amp[884]); 
  FFV2_4_0(w[254], w[2], w[116], pars->GC_50, pars->GC_59, amp[885]); 
  FFV1_0(w[255], w[48], w[14], pars->GC_1, amp[886]); 
  FFV1_0(w[0], w[256], w[14], pars->GC_1, amp[887]); 
  FFV2_3_0(w[255], w[48], w[17], pars->GC_50, pars->GC_58, amp[888]); 
  FFV2_3_0(w[0], w[256], w[17], pars->GC_50, pars->GC_58, amp[889]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_1, amp[890]); 
  FFV1_0(w[0], w[257], w[14], pars->GC_1, amp[891]); 
  FFV2_3_0(w[79], w[48], w[17], pars->GC_50, pars->GC_58, amp[892]); 
  FFV2_3_0(w[0], w[257], w[17], pars->GC_50, pars->GC_58, amp[893]); 
  FFV1_0(w[258], w[48], w[14], pars->GC_1, amp[894]); 
  FFV1_0(w[0], w[259], w[14], pars->GC_1, amp[895]); 
  FFV2_3_0(w[258], w[48], w[17], pars->GC_50, pars->GC_58, amp[896]); 
  FFV2_3_0(w[0], w[259], w[17], pars->GC_50, pars->GC_58, amp[897]); 
  FFV1_0(w[262], w[4], w[14], pars->GC_2, amp[898]); 
  FFV1_0(w[247], w[4], w[111], pars->GC_2, amp[899]); 
  FFV2_5_0(w[262], w[4], w[17], pars->GC_51, pars->GC_58, amp[900]); 
  FFV1_0(w[248], w[4], w[111], pars->GC_2, amp[901]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_2, amp[902]); 
  FFV1_0(w[247], w[4], w[60], pars->GC_11, amp[903]); 
  FFV2_5_0(w[61], w[4], w[17], pars->GC_51, pars->GC_58, amp[904]); 
  FFV1_0(w[248], w[4], w[60], pars->GC_11, amp[905]); 
  FFV1_0(w[263], w[4], w[14], pars->GC_2, amp[906]); 
  FFV2_5_0(w[247], w[4], w[116], pars->GC_51, pars->GC_58, amp[907]); 
  FFV2_5_0(w[263], w[4], w[17], pars->GC_51, pars->GC_58, amp[908]); 
  FFV2_5_0(w[248], w[4], w[116], pars->GC_51, pars->GC_58, amp[909]); 
  FFV1_0(w[3], w[113], w[112], pars->GC_3, amp[910]); 
  FFV1_0(w[114], w[2], w[112], pars->GC_3, amp[911]); 
  FFV2_4_0(w[3], w[113], w[115], pars->GC_50, pars->GC_59, amp[912]); 
  FFV2_4_0(w[114], w[2], w[115], pars->GC_50, pars->GC_59, amp[913]); 
  FFV1_0(w[3], w[117], w[112], pars->GC_3, amp[914]); 
  FFV1_0(w[118], w[2], w[112], pars->GC_3, amp[915]); 
  FFV2_4_0(w[3], w[117], w[115], pars->GC_50, pars->GC_59, amp[916]); 
  FFV2_4_0(w[118], w[2], w[115], pars->GC_50, pars->GC_59, amp[917]); 
  FFV1_0(w[119], w[4], w[14], pars->GC_1, amp[918]); 
  FFV1_0(w[49], w[120], w[14], pars->GC_1, amp[919]); 
  FFV2_3_0(w[119], w[4], w[17], pars->GC_50, pars->GC_58, amp[920]); 
  FFV2_3_0(w[49], w[120], w[17], pars->GC_50, pars->GC_58, amp[921]); 
  FFV1_0(w[61], w[4], w[14], pars->GC_1, amp[922]); 
  FFV1_0(w[49], w[62], w[14], pars->GC_1, amp[923]); 
  FFV2_3_0(w[61], w[4], w[17], pars->GC_50, pars->GC_58, amp[924]); 
  FFV2_3_0(w[49], w[62], w[17], pars->GC_50, pars->GC_58, amp[925]); 
  FFV1_0(w[121], w[4], w[14], pars->GC_1, amp[926]); 
  FFV1_0(w[49], w[122], w[14], pars->GC_1, amp[927]); 
  FFV2_3_0(w[121], w[4], w[17], pars->GC_50, pars->GC_58, amp[928]); 
  FFV2_3_0(w[49], w[122], w[17], pars->GC_50, pars->GC_58, amp[929]); 
  FFV1_0(w[131], w[48], w[14], pars->GC_1, amp[930]); 
  FFV1_0(w[106], w[48], w[112], pars->GC_1, amp[931]); 
  FFV2_3_0(w[131], w[48], w[17], pars->GC_50, pars->GC_58, amp[932]); 
  FFV1_0(w[107], w[48], w[112], pars->GC_1, amp[933]); 
  FFV1_0(w[79], w[48], w[14], pars->GC_1, amp[934]); 
  FFV1_0(w[106], w[48], w[78], pars->GC_11, amp[935]); 
  FFV2_3_0(w[79], w[48], w[17], pars->GC_50, pars->GC_58, amp[936]); 
  FFV1_0(w[107], w[48], w[78], pars->GC_11, amp[937]); 
  FFV1_0(w[132], w[48], w[14], pars->GC_1, amp[938]); 
  FFV2_3_0(w[106], w[48], w[115], pars->GC_50, pars->GC_58, amp[939]); 
  FFV2_3_0(w[132], w[48], w[17], pars->GC_50, pars->GC_58, amp[940]); 
  FFV2_3_0(w[107], w[48], w[115], pars->GC_50, pars->GC_58, amp[941]); 
  FFV1_0(w[3], w[83], w[123], pars->GC_3, amp[942]); 
  FFV1_0(w[84], w[2], w[123], pars->GC_3, amp[943]); 
  FFV2_4_0(w[3], w[83], w[124], pars->GC_50, pars->GC_59, amp[944]); 
  FFV2_4_0(w[84], w[2], w[124], pars->GC_50, pars->GC_59, amp[945]); 
  FFV1_0(w[3], w[87], w[123], pars->GC_3, amp[946]); 
  FFV1_0(w[88], w[2], w[123], pars->GC_3, amp[947]); 
  FFV2_4_0(w[3], w[87], w[124], pars->GC_50, pars->GC_59, amp[948]); 
  FFV2_4_0(w[88], w[2], w[124], pars->GC_50, pars->GC_59, amp[949]); 
  FFV1_0(w[125], w[48], w[14], pars->GC_1, amp[950]); 
  FFV1_0(w[49], w[126], w[14], pars->GC_1, amp[951]); 
  FFV2_3_0(w[125], w[48], w[17], pars->GC_50, pars->GC_58, amp[952]); 
  FFV2_3_0(w[49], w[126], w[17], pars->GC_50, pars->GC_58, amp[953]); 
  FFV1_0(w[69], w[48], w[14], pars->GC_1, amp[954]); 
  FFV1_0(w[49], w[70], w[14], pars->GC_1, amp[955]); 
  FFV2_3_0(w[69], w[48], w[17], pars->GC_50, pars->GC_58, amp[956]); 
  FFV2_3_0(w[49], w[70], w[17], pars->GC_50, pars->GC_58, amp[957]); 
  FFV1_0(w[127], w[48], w[14], pars->GC_1, amp[958]); 
  FFV1_0(w[49], w[128], w[14], pars->GC_1, amp[959]); 
  FFV2_3_0(w[127], w[48], w[17], pars->GC_50, pars->GC_58, amp[960]); 
  FFV2_3_0(w[49], w[128], w[17], pars->GC_50, pars->GC_58, amp[961]); 
  FFV1_0(w[129], w[4], w[14], pars->GC_1, amp[962]); 
  FFV1_0(w[106], w[4], w[123], pars->GC_1, amp[963]); 
  FFV2_3_0(w[129], w[4], w[17], pars->GC_50, pars->GC_58, amp[964]); 
  FFV1_0(w[107], w[4], w[123], pars->GC_1, amp[965]); 
  FFV1_0(w[75], w[4], w[14], pars->GC_1, amp[966]); 
  FFV1_0(w[106], w[4], w[74], pars->GC_11, amp[967]); 
  FFV2_3_0(w[75], w[4], w[17], pars->GC_50, pars->GC_58, amp[968]); 
  FFV1_0(w[107], w[4], w[74], pars->GC_11, amp[969]); 
  FFV1_0(w[130], w[4], w[14], pars->GC_1, amp[970]); 
  FFV2_3_0(w[106], w[4], w[124], pars->GC_50, pars->GC_58, amp[971]); 
  FFV2_3_0(w[130], w[4], w[17], pars->GC_50, pars->GC_58, amp[972]); 
  FFV2_3_0(w[107], w[4], w[124], pars->GC_50, pars->GC_58, amp[973]); 
  FFV1_0(w[3], w[136], w[65], pars->GC_3, amp[974]); 
  FFV1_0(w[137], w[2], w[65], pars->GC_3, amp[975]); 
  FFV2_4_0(w[3], w[136], w[66], pars->GC_50, pars->GC_59, amp[976]); 
  FFV2_4_0(w[137], w[2], w[66], pars->GC_50, pars->GC_59, amp[977]); 
  FFV1_0(w[3], w[139], w[65], pars->GC_3, amp[978]); 
  FFV1_0(w[140], w[2], w[65], pars->GC_3, amp[979]); 
  FFV2_4_0(w[3], w[139], w[66], pars->GC_50, pars->GC_59, amp[980]); 
  FFV2_4_0(w[140], w[2], w[66], pars->GC_50, pars->GC_59, amp[981]); 
  FFV1_0(w[141], w[48], w[14], pars->GC_2, amp[982]); 
  FFV1_0(w[49], w[142], w[14], pars->GC_2, amp[983]); 
  FFV2_5_0(w[141], w[48], w[17], pars->GC_51, pars->GC_58, amp[984]); 
  FFV2_5_0(w[49], w[142], w[17], pars->GC_51, pars->GC_58, amp[985]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_2, amp[986]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_2, amp[987]); 
  FFV2_5_0(w[144], w[48], w[17], pars->GC_51, pars->GC_58, amp[988]); 
  FFV2_5_0(w[49], w[145], w[17], pars->GC_51, pars->GC_58, amp[989]); 
  FFV1_0(w[146], w[48], w[14], pars->GC_2, amp[990]); 
  FFV1_0(w[49], w[147], w[14], pars->GC_2, amp[991]); 
  FFV2_5_0(w[146], w[48], w[17], pars->GC_51, pars->GC_58, amp[992]); 
  FFV2_5_0(w[49], w[147], w[17], pars->GC_51, pars->GC_58, amp[993]); 
  FFV1_0(w[169], w[133], w[14], pars->GC_2, amp[994]); 
  FFV1_0(w[164], w[133], w[65], pars->GC_2, amp[995]); 
  FFV2_5_0(w[169], w[133], w[17], pars->GC_51, pars->GC_58, amp[996]); 
  FFV1_0(w[165], w[133], w[65], pars->GC_2, amp[997]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_2, amp[998]); 
  FFV1_0(w[164], w[133], w[74], pars->GC_11, amp[999]); 
  FFV2_5_0(w[170], w[133], w[17], pars->GC_51, pars->GC_58, amp[1000]); 
  FFV1_0(w[165], w[133], w[74], pars->GC_11, amp[1001]); 
  FFV1_0(w[171], w[133], w[14], pars->GC_2, amp[1002]); 
  FFV2_5_0(w[164], w[133], w[66], pars->GC_51, pars->GC_58, amp[1003]); 
  FFV2_5_0(w[171], w[133], w[17], pars->GC_51, pars->GC_58, amp[1004]); 
  FFV2_5_0(w[165], w[133], w[66], pars->GC_51, pars->GC_58, amp[1005]); 
  FFV1_0(w[3], w[136], w[123], pars->GC_3, amp[1006]); 
  FFV1_0(w[137], w[2], w[123], pars->GC_3, amp[1007]); 
  FFV2_4_0(w[3], w[136], w[124], pars->GC_50, pars->GC_59, amp[1008]); 
  FFV2_4_0(w[137], w[2], w[124], pars->GC_50, pars->GC_59, amp[1009]); 
  FFV1_0(w[3], w[139], w[123], pars->GC_3, amp[1010]); 
  FFV1_0(w[140], w[2], w[123], pars->GC_3, amp[1011]); 
  FFV2_4_0(w[3], w[139], w[124], pars->GC_50, pars->GC_59, amp[1012]); 
  FFV2_4_0(w[140], w[2], w[124], pars->GC_50, pars->GC_59, amp[1013]); 
  FFV1_0(w[264], w[48], w[14], pars->GC_1, amp[1014]); 
  FFV1_0(w[49], w[265], w[14], pars->GC_1, amp[1015]); 
  FFV2_3_0(w[264], w[48], w[17], pars->GC_50, pars->GC_58, amp[1016]); 
  FFV2_3_0(w[49], w[265], w[17], pars->GC_50, pars->GC_58, amp[1017]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_1, amp[1018]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_1, amp[1019]); 
  FFV2_3_0(w[144], w[48], w[17], pars->GC_50, pars->GC_58, amp[1020]); 
  FFV2_3_0(w[49], w[145], w[17], pars->GC_50, pars->GC_58, amp[1021]); 
  FFV1_0(w[266], w[48], w[14], pars->GC_1, amp[1022]); 
  FFV1_0(w[49], w[267], w[14], pars->GC_1, amp[1023]); 
  FFV2_3_0(w[266], w[48], w[17], pars->GC_50, pars->GC_58, amp[1024]); 
  FFV2_3_0(w[49], w[267], w[17], pars->GC_50, pars->GC_58, amp[1025]); 
  FFV1_0(w[274], w[133], w[14], pars->GC_2, amp[1026]); 
  FFV1_0(w[164], w[133], w[123], pars->GC_2, amp[1027]); 
  FFV2_5_0(w[274], w[133], w[17], pars->GC_51, pars->GC_58, amp[1028]); 
  FFV1_0(w[165], w[133], w[123], pars->GC_2, amp[1029]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_2, amp[1030]); 
  FFV1_0(w[164], w[133], w[74], pars->GC_11, amp[1031]); 
  FFV2_5_0(w[170], w[133], w[17], pars->GC_51, pars->GC_58, amp[1032]); 
  FFV1_0(w[165], w[133], w[74], pars->GC_11, amp[1033]); 
  FFV1_0(w[275], w[133], w[14], pars->GC_2, amp[1034]); 
  FFV2_5_0(w[164], w[133], w[124], pars->GC_51, pars->GC_58, amp[1035]); 
  FFV2_5_0(w[275], w[133], w[17], pars->GC_51, pars->GC_58, amp[1036]); 
  FFV2_5_0(w[165], w[133], w[124], pars->GC_51, pars->GC_58, amp[1037]); 
  FFV1_0(w[3], w[173], w[123], pars->GC_3, amp[1038]); 
  FFV1_0(w[174], w[2], w[123], pars->GC_3, amp[1039]); 
  FFV2_4_0(w[3], w[173], w[124], pars->GC_50, pars->GC_59, amp[1040]); 
  FFV2_4_0(w[174], w[2], w[124], pars->GC_50, pars->GC_59, amp[1041]); 
  FFV1_0(w[3], w[176], w[123], pars->GC_3, amp[1042]); 
  FFV1_0(w[177], w[2], w[123], pars->GC_3, amp[1043]); 
  FFV2_4_0(w[3], w[176], w[124], pars->GC_50, pars->GC_59, amp[1044]); 
  FFV2_4_0(w[177], w[2], w[124], pars->GC_50, pars->GC_59, amp[1045]); 
  FFV1_0(w[178], w[48], w[14], pars->GC_1, amp[1046]); 
  FFV1_0(w[49], w[179], w[14], pars->GC_1, amp[1047]); 
  FFV2_3_0(w[178], w[48], w[17], pars->GC_50, pars->GC_58, amp[1048]); 
  FFV2_3_0(w[49], w[179], w[17], pars->GC_50, pars->GC_58, amp[1049]); 
  FFV1_0(w[144], w[48], w[14], pars->GC_1, amp[1050]); 
  FFV1_0(w[49], w[145], w[14], pars->GC_1, amp[1051]); 
  FFV2_3_0(w[144], w[48], w[17], pars->GC_50, pars->GC_58, amp[1052]); 
  FFV2_3_0(w[49], w[145], w[17], pars->GC_50, pars->GC_58, amp[1053]); 
  FFV1_0(w[180], w[48], w[14], pars->GC_1, amp[1054]); 
  FFV1_0(w[49], w[181], w[14], pars->GC_1, amp[1055]); 
  FFV2_3_0(w[180], w[48], w[17], pars->GC_50, pars->GC_58, amp[1056]); 
  FFV2_3_0(w[49], w[181], w[17], pars->GC_50, pars->GC_58, amp[1057]); 
  FFV1_0(w[198], w[133], w[14], pars->GC_1, amp[1058]); 
  FFV1_0(w[195], w[133], w[123], pars->GC_1, amp[1059]); 
  FFV2_3_0(w[198], w[133], w[17], pars->GC_50, pars->GC_58, amp[1060]); 
  FFV1_0(w[196], w[133], w[123], pars->GC_1, amp[1061]); 
  FFV1_0(w[170], w[133], w[14], pars->GC_1, amp[1062]); 
  FFV1_0(w[195], w[133], w[74], pars->GC_11, amp[1063]); 
  FFV2_3_0(w[170], w[133], w[17], pars->GC_50, pars->GC_58, amp[1064]); 
  FFV1_0(w[196], w[133], w[74], pars->GC_11, amp[1065]); 
  FFV1_0(w[199], w[133], w[14], pars->GC_1, amp[1066]); 
  FFV2_3_0(w[195], w[133], w[124], pars->GC_50, pars->GC_58, amp[1067]); 
  FFV2_3_0(w[199], w[133], w[17], pars->GC_50, pars->GC_58, amp[1068]); 
  FFV2_3_0(w[196], w[133], w[124], pars->GC_50, pars->GC_58, amp[1069]); 
  FFV2_0(w[3], w[276], w[10], pars->GC_62, amp[1070]); 
  FFV2_0(w[277], w[2], w[10], pars->GC_62, amp[1071]); 
  FFV2_5_0(w[15], w[5], w[278], pars->GC_51, pars->GC_58, amp[1072]); 
  FFV2_5_0(w[1], w[16], w[278], pars->GC_51, pars->GC_58, amp[1073]); 
  FFV2_5_0(w[19], w[5], w[278], pars->GC_51, pars->GC_58, amp[1074]); 
  FFV2_5_0(w[1], w[20], w[278], pars->GC_51, pars->GC_58, amp[1075]); 
  FFV2_5_0(w[21], w[5], w[278], pars->GC_51, pars->GC_58, amp[1076]); 
  FFV2_5_0(w[1], w[22], w[278], pars->GC_51, pars->GC_58, amp[1077]); 
  FFV2_0(w[3], w[279], w[27], pars->GC_62, amp[1078]); 
  FFV2_0(w[280], w[2], w[27], pars->GC_62, amp[1079]); 
  FFV2_5_0(w[31], w[4], w[278], pars->GC_51, pars->GC_58, amp[1080]); 
  FFV2_5_0(w[1], w[32], w[278], pars->GC_51, pars->GC_58, amp[1081]); 
  FFV2_5_0(w[34], w[4], w[278], pars->GC_51, pars->GC_58, amp[1082]); 
  FFV2_5_0(w[1], w[35], w[278], pars->GC_51, pars->GC_58, amp[1083]); 
  FFV2_5_0(w[36], w[4], w[278], pars->GC_51, pars->GC_58, amp[1084]); 
  FFV2_5_0(w[1], w[37], w[278], pars->GC_51, pars->GC_58, amp[1085]); 
  FFV2_5_0(w[38], w[5], w[278], pars->GC_51, pars->GC_58, amp[1086]); 
  FFV1_0(w[281], w[5], w[24], pars->GC_2, amp[1087]); 
  FFV2_5_0(w[42], w[5], w[278], pars->GC_51, pars->GC_58, amp[1088]); 
  FFV1_0(w[281], w[5], w[41], pars->GC_11, amp[1089]); 
  FFV2_5_0(w[43], w[5], w[278], pars->GC_51, pars->GC_58, amp[1090]); 
  FFV2_5_0(w[281], w[5], w[27], pars->GC_51, pars->GC_58, amp[1091]); 
  FFV2_5_0(w[44], w[4], w[278], pars->GC_51, pars->GC_58, amp[1092]); 
  FFV1_0(w[281], w[4], w[7], pars->GC_2, amp[1093]); 
  FFV2_5_0(w[46], w[4], w[278], pars->GC_51, pars->GC_58, amp[1094]); 
  FFV1_0(w[281], w[4], w[45], pars->GC_11, amp[1095]); 
  FFV2_5_0(w[47], w[4], w[278], pars->GC_51, pars->GC_58, amp[1096]); 
  FFV2_5_0(w[281], w[4], w[10], pars->GC_51, pars->GC_58, amp[1097]); 
  FFV2_0(w[3], w[282], w[54], pars->GC_62, amp[1098]); 
  FFV2_0(w[283], w[2], w[54], pars->GC_62, amp[1099]); 
  FFV2_5_0(w[58], w[4], w[278], pars->GC_51, pars->GC_58, amp[1100]); 
  FFV2_5_0(w[49], w[59], w[278], pars->GC_51, pars->GC_58, amp[1101]); 
  FFV2_5_0(w[61], w[4], w[278], pars->GC_51, pars->GC_58, amp[1102]); 
  FFV2_5_0(w[49], w[62], w[278], pars->GC_51, pars->GC_58, amp[1103]); 
  FFV2_5_0(w[63], w[4], w[278], pars->GC_51, pars->GC_58, amp[1104]); 
  FFV2_5_0(w[49], w[64], w[278], pars->GC_51, pars->GC_58, amp[1105]); 
  FFV2_0(w[3], w[276], w[66], pars->GC_62, amp[1106]); 
  FFV2_0(w[277], w[2], w[66], pars->GC_62, amp[1107]); 
  FFV2_5_0(w[67], w[48], w[278], pars->GC_51, pars->GC_58, amp[1108]); 
  FFV2_5_0(w[49], w[68], w[278], pars->GC_51, pars->GC_58, amp[1109]); 
  FFV2_5_0(w[69], w[48], w[278], pars->GC_51, pars->GC_58, amp[1110]); 
  FFV2_5_0(w[49], w[70], w[278], pars->GC_51, pars->GC_58, amp[1111]); 
  FFV2_5_0(w[71], w[48], w[278], pars->GC_51, pars->GC_58, amp[1112]); 
  FFV2_5_0(w[49], w[72], w[278], pars->GC_51, pars->GC_58, amp[1113]); 
  FFV2_5_0(w[73], w[4], w[278], pars->GC_51, pars->GC_58, amp[1114]); 
  FFV1_0(w[281], w[4], w[65], pars->GC_2, amp[1115]); 
  FFV2_5_0(w[75], w[4], w[278], pars->GC_51, pars->GC_58, amp[1116]); 
  FFV1_0(w[281], w[4], w[74], pars->GC_11, amp[1117]); 
  FFV2_5_0(w[76], w[4], w[278], pars->GC_51, pars->GC_58, amp[1118]); 
  FFV2_5_0(w[281], w[4], w[66], pars->GC_51, pars->GC_58, amp[1119]); 
  FFV2_5_0(w[77], w[48], w[278], pars->GC_51, pars->GC_58, amp[1120]); 
  FFV1_0(w[281], w[48], w[51], pars->GC_2, amp[1121]); 
  FFV2_5_0(w[79], w[48], w[278], pars->GC_51, pars->GC_58, amp[1122]); 
  FFV1_0(w[281], w[48], w[78], pars->GC_11, amp[1123]); 
  FFV2_5_0(w[80], w[48], w[278], pars->GC_51, pars->GC_58, amp[1124]); 
  FFV2_5_0(w[281], w[48], w[54], pars->GC_51, pars->GC_58, amp[1125]); 
  FFV2_0(w[3], w[284], w[85], pars->GC_62, amp[1126]); 
  FFV2_0(w[285], w[2], w[85], pars->GC_62, amp[1127]); 
  FFV2_3_0(w[89], w[5], w[278], pars->GC_50, pars->GC_58, amp[1128]); 
  FFV2_3_0(w[1], w[90], w[278], pars->GC_50, pars->GC_58, amp[1129]); 
  FFV2_3_0(w[19], w[5], w[278], pars->GC_50, pars->GC_58, amp[1130]); 
  FFV2_3_0(w[1], w[20], w[278], pars->GC_50, pars->GC_58, amp[1131]); 
  FFV2_3_0(w[91], w[5], w[278], pars->GC_50, pars->GC_58, amp[1132]); 
  FFV2_3_0(w[1], w[92], w[278], pars->GC_50, pars->GC_58, amp[1133]); 
  FFV2_0(w[3], w[286], w[97], pars->GC_62, amp[1134]); 
  FFV2_0(w[287], w[2], w[97], pars->GC_62, amp[1135]); 
  FFV2_3_0(w[101], w[4], w[278], pars->GC_50, pars->GC_58, amp[1136]); 
  FFV2_3_0(w[1], w[102], w[278], pars->GC_50, pars->GC_58, amp[1137]); 
  FFV2_3_0(w[34], w[4], w[278], pars->GC_50, pars->GC_58, amp[1138]); 
  FFV2_3_0(w[1], w[35], w[278], pars->GC_50, pars->GC_58, amp[1139]); 
  FFV2_3_0(w[103], w[4], w[278], pars->GC_50, pars->GC_58, amp[1140]); 
  FFV2_3_0(w[1], w[104], w[278], pars->GC_50, pars->GC_58, amp[1141]); 
  FFV2_3_0(w[105], w[5], w[278], pars->GC_50, pars->GC_58, amp[1142]); 
  FFV1_0(w[288], w[5], w[94], pars->GC_1, amp[1143]); 
  FFV2_3_0(w[42], w[5], w[278], pars->GC_50, pars->GC_58, amp[1144]); 
  FFV1_0(w[288], w[5], w[41], pars->GC_11, amp[1145]); 
  FFV2_3_0(w[108], w[5], w[278], pars->GC_50, pars->GC_58, amp[1146]); 
  FFV2_3_0(w[288], w[5], w[97], pars->GC_50, pars->GC_58, amp[1147]); 
  FFV2_3_0(w[109], w[4], w[278], pars->GC_50, pars->GC_58, amp[1148]); 
  FFV1_0(w[288], w[4], w[82], pars->GC_1, amp[1149]); 
  FFV2_3_0(w[46], w[4], w[278], pars->GC_50, pars->GC_58, amp[1150]); 
  FFV1_0(w[288], w[4], w[45], pars->GC_11, amp[1151]); 
  FFV2_3_0(w[110], w[4], w[278], pars->GC_50, pars->GC_58, amp[1152]); 
  FFV2_3_0(w[288], w[4], w[85], pars->GC_50, pars->GC_58, amp[1153]); 
  FFV2_0(w[3], w[289], w[115], pars->GC_62, amp[1154]); 
  FFV2_0(w[290], w[2], w[115], pars->GC_62, amp[1155]); 
  FFV2_3_0(w[119], w[4], w[278], pars->GC_50, pars->GC_58, amp[1156]); 
  FFV2_3_0(w[49], w[120], w[278], pars->GC_50, pars->GC_58, amp[1157]); 
  FFV2_3_0(w[61], w[4], w[278], pars->GC_50, pars->GC_58, amp[1158]); 
  FFV2_3_0(w[49], w[62], w[278], pars->GC_50, pars->GC_58, amp[1159]); 
  FFV2_3_0(w[121], w[4], w[278], pars->GC_50, pars->GC_58, amp[1160]); 
  FFV2_3_0(w[49], w[122], w[278], pars->GC_50, pars->GC_58, amp[1161]); 
  FFV2_0(w[3], w[284], w[124], pars->GC_62, amp[1162]); 
  FFV2_0(w[285], w[2], w[124], pars->GC_62, amp[1163]); 
  FFV2_3_0(w[125], w[48], w[278], pars->GC_50, pars->GC_58, amp[1164]); 
  FFV2_3_0(w[49], w[126], w[278], pars->GC_50, pars->GC_58, amp[1165]); 
  FFV2_3_0(w[69], w[48], w[278], pars->GC_50, pars->GC_58, amp[1166]); 
  FFV2_3_0(w[49], w[70], w[278], pars->GC_50, pars->GC_58, amp[1167]); 
  FFV2_3_0(w[127], w[48], w[278], pars->GC_50, pars->GC_58, amp[1168]); 
  FFV2_3_0(w[49], w[128], w[278], pars->GC_50, pars->GC_58, amp[1169]); 
  FFV2_3_0(w[129], w[4], w[278], pars->GC_50, pars->GC_58, amp[1170]); 
  FFV1_0(w[288], w[4], w[123], pars->GC_1, amp[1171]); 
  FFV2_3_0(w[75], w[4], w[278], pars->GC_50, pars->GC_58, amp[1172]); 
  FFV1_0(w[288], w[4], w[74], pars->GC_11, amp[1173]); 
  FFV2_3_0(w[130], w[4], w[278], pars->GC_50, pars->GC_58, amp[1174]); 
  FFV2_3_0(w[288], w[4], w[124], pars->GC_50, pars->GC_58, amp[1175]); 
  FFV2_3_0(w[131], w[48], w[278], pars->GC_50, pars->GC_58, amp[1176]); 
  FFV1_0(w[288], w[48], w[112], pars->GC_1, amp[1177]); 
  FFV2_3_0(w[79], w[48], w[278], pars->GC_50, pars->GC_58, amp[1178]); 
  FFV1_0(w[288], w[48], w[78], pars->GC_11, amp[1179]); 
  FFV2_3_0(w[132], w[48], w[278], pars->GC_50, pars->GC_58, amp[1180]); 
  FFV2_3_0(w[288], w[48], w[115], pars->GC_50, pars->GC_58, amp[1181]); 
  FFV2_0(w[3], w[291], w[66], pars->GC_62, amp[1182]); 
  FFV2_0(w[292], w[2], w[66], pars->GC_62, amp[1183]); 
  FFV2_5_0(w[141], w[48], w[278], pars->GC_51, pars->GC_58, amp[1184]); 
  FFV2_5_0(w[49], w[142], w[278], pars->GC_51, pars->GC_58, amp[1185]); 
  FFV2_5_0(w[144], w[48], w[278], pars->GC_51, pars->GC_58, amp[1186]); 
  FFV2_5_0(w[49], w[145], w[278], pars->GC_51, pars->GC_58, amp[1187]); 
  FFV2_5_0(w[146], w[48], w[278], pars->GC_51, pars->GC_58, amp[1188]); 
  FFV2_5_0(w[49], w[147], w[278], pars->GC_51, pars->GC_58, amp[1189]); 
  FFV2_0(w[3], w[293], w[152], pars->GC_62, amp[1190]); 
  FFV2_0(w[294], w[2], w[152], pars->GC_62, amp[1191]); 
  FFV2_5_0(w[156], w[133], w[278], pars->GC_51, pars->GC_58, amp[1192]); 
  FFV2_5_0(w[49], w[157], w[278], pars->GC_51, pars->GC_58, amp[1193]); 
  FFV2_5_0(w[159], w[133], w[278], pars->GC_51, pars->GC_58, amp[1194]); 
  FFV2_5_0(w[49], w[160], w[278], pars->GC_51, pars->GC_58, amp[1195]); 
  FFV2_5_0(w[161], w[133], w[278], pars->GC_51, pars->GC_58, amp[1196]); 
  FFV2_5_0(w[49], w[162], w[278], pars->GC_51, pars->GC_58, amp[1197]); 
  FFV2_5_0(w[163], w[48], w[278], pars->GC_51, pars->GC_58, amp[1198]); 
  FFV1_0(w[295], w[48], w[149], pars->GC_2, amp[1199]); 
  FFV2_5_0(w[167], w[48], w[278], pars->GC_51, pars->GC_58, amp[1200]); 
  FFV1_0(w[295], w[48], w[166], pars->GC_11, amp[1201]); 
  FFV2_5_0(w[168], w[48], w[278], pars->GC_51, pars->GC_58, amp[1202]); 
  FFV2_5_0(w[295], w[48], w[152], pars->GC_51, pars->GC_58, amp[1203]); 
  FFV2_5_0(w[169], w[133], w[278], pars->GC_51, pars->GC_58, amp[1204]); 
  FFV1_0(w[295], w[133], w[65], pars->GC_2, amp[1205]); 
  FFV2_5_0(w[170], w[133], w[278], pars->GC_51, pars->GC_58, amp[1206]); 
  FFV1_0(w[295], w[133], w[74], pars->GC_11, amp[1207]); 
  FFV2_5_0(w[171], w[133], w[278], pars->GC_51, pars->GC_58, amp[1208]); 
  FFV2_5_0(w[295], w[133], w[66], pars->GC_51, pars->GC_58, amp[1209]); 
  FFV2_0(w[3], w[296], w[124], pars->GC_62, amp[1210]); 
  FFV2_0(w[297], w[2], w[124], pars->GC_62, amp[1211]); 
  FFV2_3_0(w[178], w[48], w[278], pars->GC_50, pars->GC_58, amp[1212]); 
  FFV2_3_0(w[49], w[179], w[278], pars->GC_50, pars->GC_58, amp[1213]); 
  FFV2_3_0(w[144], w[48], w[278], pars->GC_50, pars->GC_58, amp[1214]); 
  FFV2_3_0(w[49], w[145], w[278], pars->GC_50, pars->GC_58, amp[1215]); 
  FFV2_3_0(w[180], w[48], w[278], pars->GC_50, pars->GC_58, amp[1216]); 
  FFV2_3_0(w[49], w[181], w[278], pars->GC_50, pars->GC_58, amp[1217]); 
  FFV2_0(w[3], w[298], w[186], pars->GC_62, amp[1218]); 
  FFV2_0(w[299], w[2], w[186], pars->GC_62, amp[1219]); 
  FFV2_3_0(w[190], w[133], w[278], pars->GC_50, pars->GC_58, amp[1220]); 
  FFV2_3_0(w[49], w[191], w[278], pars->GC_50, pars->GC_58, amp[1221]); 
  FFV2_3_0(w[159], w[133], w[278], pars->GC_50, pars->GC_58, amp[1222]); 
  FFV2_3_0(w[49], w[160], w[278], pars->GC_50, pars->GC_58, amp[1223]); 
  FFV2_3_0(w[192], w[133], w[278], pars->GC_50, pars->GC_58, amp[1224]); 
  FFV2_3_0(w[49], w[193], w[278], pars->GC_50, pars->GC_58, amp[1225]); 
  FFV2_3_0(w[194], w[48], w[278], pars->GC_50, pars->GC_58, amp[1226]); 
  FFV1_0(w[300], w[48], w[183], pars->GC_1, amp[1227]); 
  FFV2_3_0(w[167], w[48], w[278], pars->GC_50, pars->GC_58, amp[1228]); 
  FFV1_0(w[300], w[48], w[166], pars->GC_11, amp[1229]); 
  FFV2_3_0(w[197], w[48], w[278], pars->GC_50, pars->GC_58, amp[1230]); 
  FFV2_3_0(w[300], w[48], w[186], pars->GC_50, pars->GC_58, amp[1231]); 
  FFV2_3_0(w[198], w[133], w[278], pars->GC_50, pars->GC_58, amp[1232]); 
  FFV1_0(w[300], w[133], w[123], pars->GC_1, amp[1233]); 
  FFV2_3_0(w[170], w[133], w[278], pars->GC_50, pars->GC_58, amp[1234]); 
  FFV1_0(w[300], w[133], w[74], pars->GC_11, amp[1235]); 
  FFV2_3_0(w[199], w[133], w[278], pars->GC_50, pars->GC_58, amp[1236]); 
  FFV2_3_0(w[300], w[133], w[124], pars->GC_50, pars->GC_58, amp[1237]); 
  FFV2_0(w[9], w[2], w[301], pars->GC_100, amp[1238]); 
  FFV2_0(w[3], w[276], w[301], pars->GC_100, amp[1239]); 
  FFV2_0(w[13], w[2], w[301], pars->GC_100, amp[1240]); 
  VVV1_0(w[6], w[301], w[302], pars->GC_4, amp[1241]); 
  VVV1_0(w[301], w[302], w[11], pars->GC_53, amp[1242]); 
  FFV2_0(w[15], w[5], w[302], pars->GC_100, amp[1243]); 
  FFV2_0(w[1], w[201], w[302], pars->GC_100, amp[1244]); 
  FFV2_0(w[19], w[5], w[302], pars->GC_100, amp[1245]); 
  FFV2_0(w[1], w[20], w[302], pars->GC_100, amp[1246]); 
  FFV2_0(w[21], w[5], w[302], pars->GC_100, amp[1247]); 
  FFV2_0(w[1], w[203], w[302], pars->GC_100, amp[1248]); 
  FFV1_0(w[3], w[303], w[24], pars->GC_3, amp[1249]); 
  FFV2_4_0(w[3], w[303], w[27], pars->GC_50, pars->GC_59, amp[1250]); 
  FFV2_0(w[206], w[2], w[27], pars->GC_62, amp[1251]); 
  VVV1_0(w[24], w[204], w[302], pars->GC_4, amp[1252]); 
  VVV1_0(w[204], w[302], w[27], pars->GC_53, amp[1253]); 
  FFV2_0(w[1], w[208], w[302], pars->GC_100, amp[1254]); 
  FFV2_0(w[38], w[5], w[302], pars->GC_100, amp[1255]); 
  FFV1_0(w[304], w[5], w[24], pars->GC_1, amp[1256]); 
  FFV2_0(w[42], w[5], w[302], pars->GC_100, amp[1257]); 
  FFV1_0(w[304], w[5], w[41], pars->GC_11, amp[1258]); 
  FFV2_0(w[43], w[5], w[302], pars->GC_100, amp[1259]); 
  FFV2_3_0(w[304], w[5], w[27], pars->GC_50, pars->GC_58, amp[1260]); 
  FFV2_0(w[304], w[4], w[301], pars->GC_100, amp[1261]); 
  FFV2_0(w[3], w[8], w[301], pars->GC_100, amp[1262]); 
  FFV2_0(w[3], w[12], w[301], pars->GC_100, amp[1263]); 
  FFV2_0(w[277], w[2], w[301], pars->GC_100, amp[1264]); 
  VVV1_0(w[6], w[302], w[301], pars->GC_4, amp[1265]); 
  VVV1_0(w[302], w[301], w[11], pars->GC_53, amp[1266]); 
  FFV2_0(w[200], w[5], w[302], pars->GC_100, amp[1267]); 
  FFV2_0(w[1], w[16], w[302], pars->GC_100, amp[1268]); 
  FFV2_0(w[19], w[5], w[302], pars->GC_100, amp[1269]); 
  FFV2_0(w[1], w[20], w[302], pars->GC_100, amp[1270]); 
  FFV2_0(w[202], w[5], w[302], pars->GC_100, amp[1271]); 
  FFV2_0(w[1], w[22], w[302], pars->GC_100, amp[1272]); 
  FFV2_0(w[3], w[25], w[205], pars->GC_100, amp[1273]); 
  FFV2_0(w[3], w[29], w[205], pars->GC_100, amp[1274]); 
  FFV2_0(w[280], w[2], w[205], pars->GC_100, amp[1275]); 
  VVV1_0(w[23], w[302], w[205], pars->GC_4, amp[1276]); 
  VVV1_0(w[302], w[205], w[28], pars->GC_53, amp[1277]); 
  FFV2_0(w[305], w[4], w[302], pars->GC_100, amp[1278]); 
  FFV2_0(w[1], w[32], w[302], pars->GC_100, amp[1279]); 
  FFV2_0(w[34], w[4], w[302], pars->GC_100, amp[1280]); 
  FFV2_0(w[1], w[35], w[302], pars->GC_100, amp[1281]); 
  FFV2_0(w[306], w[4], w[302], pars->GC_100, amp[1282]); 
  FFV2_0(w[1], w[37], w[302], pars->GC_100, amp[1283]); 
  FFV2_0(w[209], w[5], w[302], pars->GC_100, amp[1284]); 
  FFV2_0(w[307], w[4], w[302], pars->GC_100, amp[1285]); 
  FFV1_0(w[3], w[308], w[82], pars->GC_3, amp[1286]); 
  FFV2_4_0(w[3], w[308], w[85], pars->GC_50, pars->GC_59, amp[1287]); 
  FFV2_0(w[218], w[2], w[85], pars->GC_62, amp[1288]); 
  VVV1_0(w[82], w[216], w[302], pars->GC_4, amp[1289]); 
  VVV1_0(w[216], w[302], w[85], pars->GC_53, amp[1290]); 
  FFV2_0(w[309], w[5], w[302], pars->GC_100, amp[1291]); 
  FFV1_0(w[3], w[303], w[94], pars->GC_3, amp[1292]); 
  FFV2_4_0(w[3], w[303], w[97], pars->GC_50, pars->GC_59, amp[1293]); 
  FFV2_0(w[206], w[2], w[97], pars->GC_62, amp[1294]); 
  VVV1_0(w[94], w[204], w[302], pars->GC_4, amp[1295]); 
  VVV1_0(w[204], w[302], w[97], pars->GC_53, amp[1296]); 
  FFV2_0(w[207], w[4], w[302], pars->GC_100, amp[1297]); 
  FFV2_0(w[310], w[5], w[302], pars->GC_100, amp[1298]); 
  FFV1_0(w[304], w[5], w[94], pars->GC_1, amp[1299]); 
  FFV2_0(w[42], w[5], w[302], pars->GC_100, amp[1300]); 
  FFV1_0(w[304], w[5], w[41], pars->GC_11, amp[1301]); 
  FFV2_0(w[311], w[5], w[302], pars->GC_100, amp[1302]); 
  FFV2_3_0(w[304], w[5], w[97], pars->GC_50, pars->GC_58, amp[1303]); 
  FFV2_0(w[210], w[4], w[302], pars->GC_100, amp[1304]); 
  FFV1_0(w[304], w[4], w[82], pars->GC_1, amp[1305]); 
  FFV2_0(w[46], w[4], w[302], pars->GC_100, amp[1306]); 
  FFV1_0(w[304], w[4], w[45], pars->GC_11, amp[1307]); 
  FFV2_0(w[211], w[4], w[302], pars->GC_100, amp[1308]); 
  FFV2_3_0(w[304], w[4], w[85], pars->GC_50, pars->GC_58, amp[1309]); 
  FFV2_0(w[3], w[52], w[229], pars->GC_100, amp[1310]); 
  FFV2_0(w[3], w[56], w[229], pars->GC_100, amp[1311]); 
  FFV2_0(w[283], w[2], w[229], pars->GC_100, amp[1312]); 
  VVV1_0(w[50], w[302], w[229], pars->GC_4, amp[1313]); 
  VVV1_0(w[302], w[229], w[55], pars->GC_53, amp[1314]); 
  FFV2_0(w[212], w[4], w[302], pars->GC_100, amp[1315]); 
  FFV2_0(w[49], w[59], w[302], pars->GC_100, amp[1316]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[1317]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[1318]); 
  FFV2_0(w[214], w[4], w[302], pars->GC_100, amp[1319]); 
  FFV2_0(w[49], w[64], w[302], pars->GC_100, amp[1320]); 
  FFV2_0(w[3], w[8], w[217], pars->GC_100, amp[1321]); 
  FFV2_0(w[3], w[12], w[217], pars->GC_100, amp[1322]); 
  FFV2_0(w[277], w[2], w[217], pars->GC_100, amp[1323]); 
  VVV1_0(w[6], w[302], w[217], pars->GC_4, amp[1324]); 
  VVV1_0(w[302], w[217], w[11], pars->GC_53, amp[1325]); 
  FFV2_0(w[224], w[48], w[302], pars->GC_100, amp[1326]); 
  FFV2_0(w[49], w[68], w[302], pars->GC_100, amp[1327]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[1328]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[1329]); 
  FFV2_0(w[226], w[48], w[302], pars->GC_100, amp[1330]); 
  FFV2_0(w[49], w[72], w[302], pars->GC_100, amp[1331]); 
  FFV2_0(w[221], w[4], w[302], pars->GC_100, amp[1332]); 
  FFV2_0(w[233], w[48], w[302], pars->GC_100, amp[1333]); 
  FFV2_0(w[53], w[2], w[229], pars->GC_100, amp[1334]); 
  FFV2_0(w[3], w[282], w[229], pars->GC_100, amp[1335]); 
  FFV2_0(w[57], w[2], w[229], pars->GC_100, amp[1336]); 
  VVV1_0(w[50], w[229], w[302], pars->GC_4, amp[1337]); 
  VVV1_0(w[229], w[302], w[55], pars->GC_53, amp[1338]); 
  FFV2_0(w[58], w[4], w[302], pars->GC_100, amp[1339]); 
  FFV2_0(w[49], w[213], w[302], pars->GC_100, amp[1340]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[1341]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[1342]); 
  FFV2_0(w[63], w[4], w[302], pars->GC_100, amp[1343]); 
  FFV2_0(w[49], w[215], w[302], pars->GC_100, amp[1344]); 
  FFV1_0(w[3], w[308], w[65], pars->GC_3, amp[1345]); 
  FFV2_4_0(w[3], w[308], w[66], pars->GC_50, pars->GC_59, amp[1346]); 
  FFV2_0(w[218], w[2], w[66], pars->GC_62, amp[1347]); 
  VVV1_0(w[65], w[216], w[302], pars->GC_4, amp[1348]); 
  VVV1_0(w[216], w[302], w[66], pars->GC_53, amp[1349]); 
  FFV2_0(w[49], w[220], w[302], pars->GC_100, amp[1350]); 
  FFV2_0(w[73], w[4], w[302], pars->GC_100, amp[1351]); 
  FFV1_0(w[304], w[4], w[65], pars->GC_1, amp[1352]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[1353]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[1354]); 
  FFV2_0(w[76], w[4], w[302], pars->GC_100, amp[1355]); 
  FFV2_3_0(w[304], w[4], w[66], pars->GC_50, pars->GC_58, amp[1356]); 
  FFV2_0(w[304], w[48], w[229], pars->GC_100, amp[1357]); 
  FFV2_0(w[9], w[2], w[217], pars->GC_100, amp[1358]); 
  FFV2_0(w[3], w[276], w[217], pars->GC_100, amp[1359]); 
  FFV2_0(w[13], w[2], w[217], pars->GC_100, amp[1360]); 
  VVV1_0(w[6], w[217], w[302], pars->GC_4, amp[1361]); 
  VVV1_0(w[217], w[302], w[11], pars->GC_53, amp[1362]); 
  FFV2_0(w[67], w[48], w[302], pars->GC_100, amp[1363]); 
  FFV2_0(w[49], w[225], w[302], pars->GC_100, amp[1364]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[1365]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[1366]); 
  FFV2_0(w[71], w[48], w[302], pars->GC_100, amp[1367]); 
  FFV2_0(w[49], w[227], w[302], pars->GC_100, amp[1368]); 
  FFV1_0(w[3], w[312], w[51], pars->GC_3, amp[1369]); 
  FFV2_4_0(w[3], w[312], w[54], pars->GC_50, pars->GC_59, amp[1370]); 
  FFV2_0(w[230], w[2], w[54], pars->GC_62, amp[1371]); 
  VVV1_0(w[51], w[228], w[302], pars->GC_4, amp[1372]); 
  VVV1_0(w[228], w[302], w[54], pars->GC_53, amp[1373]); 
  FFV2_0(w[49], w[232], w[302], pars->GC_100, amp[1374]); 
  FFV2_0(w[77], w[48], w[302], pars->GC_100, amp[1375]); 
  FFV1_0(w[304], w[48], w[51], pars->GC_1, amp[1376]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[1377]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[1378]); 
  FFV2_0(w[80], w[48], w[302], pars->GC_100, amp[1379]); 
  FFV2_3_0(w[304], w[48], w[54], pars->GC_50, pars->GC_58, amp[1380]); 
  FFV2_0(w[304], w[4], w[217], pars->GC_100, amp[1381]); 
  FFV1_0(w[3], w[312], w[112], pars->GC_3, amp[1382]); 
  FFV2_4_0(w[3], w[312], w[115], pars->GC_50, pars->GC_59, amp[1383]); 
  FFV2_0(w[230], w[2], w[115], pars->GC_62, amp[1384]); 
  VVV1_0(w[112], w[228], w[302], pars->GC_4, amp[1385]); 
  VVV1_0(w[228], w[302], w[115], pars->GC_53, amp[1386]); 
  FFV2_0(w[231], w[4], w[302], pars->GC_100, amp[1387]); 
  FFV1_0(w[3], w[308], w[123], pars->GC_3, amp[1388]); 
  FFV2_4_0(w[3], w[308], w[124], pars->GC_50, pars->GC_59, amp[1389]); 
  FFV2_0(w[218], w[2], w[124], pars->GC_62, amp[1390]); 
  VVV1_0(w[123], w[216], w[302], pars->GC_4, amp[1391]); 
  VVV1_0(w[216], w[302], w[124], pars->GC_53, amp[1392]); 
  FFV2_0(w[219], w[48], w[302], pars->GC_100, amp[1393]); 
  FFV2_0(w[234], w[4], w[302], pars->GC_100, amp[1394]); 
  FFV1_0(w[304], w[4], w[123], pars->GC_1, amp[1395]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[1396]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[1397]); 
  FFV2_0(w[235], w[4], w[302], pars->GC_100, amp[1398]); 
  FFV2_3_0(w[304], w[4], w[124], pars->GC_50, pars->GC_58, amp[1399]); 
  FFV2_0(w[222], w[48], w[302], pars->GC_100, amp[1400]); 
  FFV1_0(w[304], w[48], w[112], pars->GC_1, amp[1401]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[1402]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[1403]); 
  FFV2_0(w[223], w[48], w[302], pars->GC_100, amp[1404]); 
  FFV2_3_0(w[304], w[48], w[115], pars->GC_50, pars->GC_58, amp[1405]); 
  FFV1_0(w[218], w[2], w[82], pars->GC_3, amp[1406]); 
  FFV2_0(w[3], w[308], w[85], pars->GC_62, amp[1407]); 
  FFV2_4_0(w[218], w[2], w[85], pars->GC_50, pars->GC_59, amp[1408]); 
  VVV1_0(w[82], w[302], w[216], pars->GC_4, amp[1409]); 
  VVV1_0(w[302], w[216], w[85], pars->GC_53, amp[1410]); 
  FFV2_0(w[1], w[313], w[302], pars->GC_100, amp[1411]); 
  FFV2_0(w[3], w[95], w[205], pars->GC_100, amp[1412]); 
  FFV2_0(w[3], w[99], w[205], pars->GC_100, amp[1413]); 
  FFV2_0(w[287], w[2], w[205], pars->GC_100, amp[1414]); 
  VVV1_0(w[93], w[302], w[205], pars->GC_4, amp[1415]); 
  VVV1_0(w[302], w[205], w[98], pars->GC_53, amp[1416]); 
  FFV2_0(w[101], w[4], w[302], pars->GC_100, amp[1417]); 
  FFV2_0(w[1], w[314], w[302], pars->GC_100, amp[1418]); 
  FFV2_0(w[34], w[4], w[302], pars->GC_100, amp[1419]); 
  FFV2_0(w[1], w[35], w[302], pars->GC_100, amp[1420]); 
  FFV2_0(w[103], w[4], w[302], pars->GC_100, amp[1421]); 
  FFV2_0(w[1], w[315], w[302], pars->GC_100, amp[1422]); 
  FFV2_0(w[304], w[5], w[205], pars->GC_100, amp[1423]); 
  FFV2_0(w[109], w[4], w[302], pars->GC_100, amp[1424]); 
  FFV1_0(w[304], w[4], w[82], pars->GC_2, amp[1425]); 
  FFV2_0(w[46], w[4], w[302], pars->GC_100, amp[1426]); 
  FFV1_0(w[304], w[4], w[45], pars->GC_11, amp[1427]); 
  FFV2_0(w[110], w[4], w[302], pars->GC_100, amp[1428]); 
  FFV2_5_0(w[304], w[4], w[85], pars->GC_51, pars->GC_58, amp[1429]); 
  FFV2_0(w[3], w[236], w[216], pars->GC_100, amp[1430]); 
  FFV2_0(w[3], w[238], w[216], pars->GC_100, amp[1431]); 
  FFV2_0(w[316], w[2], w[216], pars->GC_100, amp[1432]); 
  VVV1_0(w[65], w[302], w[216], pars->GC_4, amp[1433]); 
  VVV1_0(w[302], w[216], w[66], pars->GC_53, amp[1434]); 
  FFV2_0(w[240], w[4], w[302], pars->GC_100, amp[1435]); 
  FFV2_0(w[0], w[317], w[302], pars->GC_100, amp[1436]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[1437]); 
  FFV2_0(w[0], w[242], w[302], pars->GC_100, amp[1438]); 
  FFV2_0(w[243], w[4], w[302], pars->GC_100, amp[1439]); 
  FFV2_0(w[0], w[318], w[302], pars->GC_100, amp[1440]); 
  FFV2_0(w[3], w[251], w[228], pars->GC_100, amp[1441]); 
  FFV2_0(w[3], w[253], w[228], pars->GC_100, amp[1442]); 
  FFV2_0(w[319], w[2], w[228], pars->GC_100, amp[1443]); 
  VVV1_0(w[51], w[302], w[228], pars->GC_4, amp[1444]); 
  VVV1_0(w[302], w[228], w[54], pars->GC_53, amp[1445]); 
  FFV2_0(w[255], w[48], w[302], pars->GC_100, amp[1446]); 
  FFV2_0(w[0], w[320], w[302], pars->GC_100, amp[1447]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[1448]); 
  FFV2_0(w[0], w[257], w[302], pars->GC_100, amp[1449]); 
  FFV2_0(w[258], w[48], w[302], pars->GC_100, amp[1450]); 
  FFV2_0(w[0], w[321], w[302], pars->GC_100, amp[1451]); 
  FFV2_0(w[231], w[4], w[302], pars->GC_100, amp[1452]); 
  FFV2_0(w[219], w[48], w[302], pars->GC_100, amp[1453]); 
  FFV1_0(w[230], w[2], w[112], pars->GC_3, amp[1454]); 
  FFV2_0(w[3], w[312], w[115], pars->GC_62, amp[1455]); 
  FFV2_4_0(w[230], w[2], w[115], pars->GC_50, pars->GC_59, amp[1456]); 
  VVV1_0(w[112], w[302], w[228], pars->GC_4, amp[1457]); 
  VVV1_0(w[302], w[228], w[115], pars->GC_53, amp[1458]); 
  FFV2_0(w[49], w[232], w[302], pars->GC_100, amp[1459]); 
  FFV2_0(w[3], w[83], w[217], pars->GC_100, amp[1460]); 
  FFV2_0(w[3], w[87], w[217], pars->GC_100, amp[1461]); 
  FFV2_0(w[285], w[2], w[217], pars->GC_100, amp[1462]); 
  VVV1_0(w[81], w[302], w[217], pars->GC_4, amp[1463]); 
  VVV1_0(w[302], w[217], w[86], pars->GC_53, amp[1464]); 
  FFV2_0(w[125], w[48], w[302], pars->GC_100, amp[1465]); 
  FFV2_0(w[49], w[322], w[302], pars->GC_100, amp[1466]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[1467]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[1468]); 
  FFV2_0(w[127], w[48], w[302], pars->GC_100, amp[1469]); 
  FFV2_0(w[49], w[323], w[302], pars->GC_100, amp[1470]); 
  FFV2_0(w[304], w[4], w[217], pars->GC_100, amp[1471]); 
  FFV2_0(w[131], w[48], w[302], pars->GC_100, amp[1472]); 
  FFV1_0(w[304], w[48], w[112], pars->GC_2, amp[1473]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[1474]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[1475]); 
  FFV2_0(w[132], w[48], w[302], pars->GC_100, amp[1476]); 
  FFV2_5_0(w[304], w[48], w[115], pars->GC_51, pars->GC_58, amp[1477]); 
  FFV1_0(w[218], w[2], w[123], pars->GC_3, amp[1478]); 
  FFV2_0(w[3], w[308], w[124], pars->GC_62, amp[1479]); 
  FFV2_4_0(w[218], w[2], w[124], pars->GC_50, pars->GC_59, amp[1480]); 
  VVV1_0(w[123], w[302], w[216], pars->GC_4, amp[1481]); 
  VVV1_0(w[302], w[216], w[124], pars->GC_53, amp[1482]); 
  FFV2_0(w[49], w[220], w[302], pars->GC_100, amp[1483]); 
  FFV2_0(w[3], w[113], w[229], pars->GC_100, amp[1484]); 
  FFV2_0(w[3], w[117], w[229], pars->GC_100, amp[1485]); 
  FFV2_0(w[290], w[2], w[229], pars->GC_100, amp[1486]); 
  VVV1_0(w[111], w[302], w[229], pars->GC_4, amp[1487]); 
  VVV1_0(w[302], w[229], w[116], pars->GC_53, amp[1488]); 
  FFV2_0(w[119], w[4], w[302], pars->GC_100, amp[1489]); 
  FFV2_0(w[49], w[324], w[302], pars->GC_100, amp[1490]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[1491]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[1492]); 
  FFV2_0(w[121], w[4], w[302], pars->GC_100, amp[1493]); 
  FFV2_0(w[49], w[325], w[302], pars->GC_100, amp[1494]); 
  FFV2_0(w[304], w[48], w[229], pars->GC_100, amp[1495]); 
  FFV2_0(w[129], w[4], w[302], pars->GC_100, amp[1496]); 
  FFV1_0(w[304], w[4], w[123], pars->GC_2, amp[1497]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[1498]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[1499]); 
  FFV2_0(w[130], w[4], w[302], pars->GC_100, amp[1500]); 
  FFV2_5_0(w[304], w[4], w[124], pars->GC_51, pars->GC_58, amp[1501]); 
  FFV1_0(w[3], w[326], w[81], pars->GC_3, amp[1502]); 
  FFV2_4_0(w[3], w[326], w[86], pars->GC_50, pars->GC_59, amp[1503]); 
  FFV2_0(w[260], w[2], w[86], pars->GC_62, amp[1504]); 
  VVV1_0(w[81], w[217], w[302], pars->GC_4, amp[1505]); 
  VVV1_0(w[217], w[302], w[86], pars->GC_53, amp[1506]); 
  FFV2_0(w[221], w[4], w[302], pars->GC_100, amp[1507]); 
  FFV1_0(w[3], w[327], w[111], pars->GC_3, amp[1508]); 
  FFV2_4_0(w[3], w[327], w[116], pars->GC_50, pars->GC_59, amp[1509]); 
  FFV2_0(w[245], w[2], w[116], pars->GC_62, amp[1510]); 
  VVV1_0(w[111], w[229], w[302], pars->GC_4, amp[1511]); 
  VVV1_0(w[229], w[302], w[116], pars->GC_53, amp[1512]); 
  FFV2_0(w[233], w[48], w[302], pars->GC_100, amp[1513]); 
  FFV2_0(w[262], w[4], w[302], pars->GC_100, amp[1514]); 
  FFV1_0(w[328], w[4], w[111], pars->GC_1, amp[1515]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[1516]); 
  FFV1_0(w[328], w[4], w[60], pars->GC_11, amp[1517]); 
  FFV2_0(w[263], w[4], w[302], pars->GC_100, amp[1518]); 
  FFV2_3_0(w[328], w[4], w[116], pars->GC_50, pars->GC_58, amp[1519]); 
  FFV2_0(w[249], w[48], w[302], pars->GC_100, amp[1520]); 
  FFV1_0(w[328], w[48], w[81], pars->GC_1, amp[1521]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[1522]); 
  FFV1_0(w[328], w[48], w[18], pars->GC_11, amp[1523]); 
  FFV2_0(w[250], w[48], w[302], pars->GC_100, amp[1524]); 
  FFV2_3_0(w[328], w[48], w[86], pars->GC_50, pars->GC_58, amp[1525]); 
  FFV2_0(w[3], w[136], w[217], pars->GC_100, amp[1526]); 
  FFV2_0(w[3], w[139], w[217], pars->GC_100, amp[1527]); 
  FFV2_0(w[292], w[2], w[217], pars->GC_100, amp[1528]); 
  VVV1_0(w[135], w[302], w[217], pars->GC_4, amp[1529]); 
  VVV1_0(w[302], w[217], w[138], pars->GC_53, amp[1530]); 
  FFV2_0(w[264], w[48], w[302], pars->GC_100, amp[1531]); 
  FFV2_0(w[49], w[142], w[302], pars->GC_100, amp[1532]); 
  FFV2_0(w[144], w[48], w[302], pars->GC_100, amp[1533]); 
  FFV2_0(w[49], w[145], w[302], pars->GC_100, amp[1534]); 
  FFV2_0(w[266], w[48], w[302], pars->GC_100, amp[1535]); 
  FFV2_0(w[49], w[147], w[302], pars->GC_100, amp[1536]); 
  FFV2_0(w[3], w[150], w[269], pars->GC_100, amp[1537]); 
  FFV2_0(w[3], w[154], w[269], pars->GC_100, amp[1538]); 
  FFV2_0(w[294], w[2], w[269], pars->GC_100, amp[1539]); 
  VVV1_0(w[148], w[302], w[269], pars->GC_4, amp[1540]); 
  VVV1_0(w[302], w[269], w[153], pars->GC_53, amp[1541]); 
  FFV2_0(w[329], w[133], w[302], pars->GC_100, amp[1542]); 
  FFV2_0(w[49], w[157], w[302], pars->GC_100, amp[1543]); 
  FFV2_0(w[159], w[133], w[302], pars->GC_100, amp[1544]); 
  FFV2_0(w[49], w[160], w[302], pars->GC_100, amp[1545]); 
  FFV2_0(w[330], w[133], w[302], pars->GC_100, amp[1546]); 
  FFV2_0(w[49], w[162], w[302], pars->GC_100, amp[1547]); 
  FFV2_0(w[273], w[48], w[302], pars->GC_100, amp[1548]); 
  FFV2_0(w[331], w[133], w[302], pars->GC_100, amp[1549]); 
  FFV1_0(w[333], w[2], w[123], pars->GC_3, amp[1550]); 
  FFV2_0(w[3], w[334], w[124], pars->GC_62, amp[1551]); 
  FFV2_4_0(w[333], w[2], w[124], pars->GC_50, pars->GC_59, amp[1552]); 
  VVV1_0(w[123], w[302], w[332], pars->GC_4, amp[1553]); 
  VVV1_0(w[302], w[332], w[124], pars->GC_53, amp[1554]); 
  FFV2_0(w[49], w[335], w[302], pars->GC_100, amp[1555]); 
  FFV2_0(w[3], w[184], w[269], pars->GC_100, amp[1556]); 
  FFV2_0(w[3], w[188], w[269], pars->GC_100, amp[1557]); 
  FFV2_0(w[299], w[2], w[269], pars->GC_100, amp[1558]); 
  VVV1_0(w[182], w[302], w[269], pars->GC_4, amp[1559]); 
  VVV1_0(w[302], w[269], w[187], pars->GC_53, amp[1560]); 
  FFV2_0(w[190], w[133], w[302], pars->GC_100, amp[1561]); 
  FFV2_0(w[49], w[336], w[302], pars->GC_100, amp[1562]); 
  FFV2_0(w[159], w[133], w[302], pars->GC_100, amp[1563]); 
  FFV2_0(w[49], w[160], w[302], pars->GC_100, amp[1564]); 
  FFV2_0(w[192], w[133], w[302], pars->GC_100, amp[1565]); 
  FFV2_0(w[49], w[337], w[302], pars->GC_100, amp[1566]); 
  FFV2_0(w[338], w[48], w[269], pars->GC_100, amp[1567]); 
  FFV2_0(w[198], w[133], w[302], pars->GC_100, amp[1568]); 
  FFV1_0(w[338], w[133], w[123], pars->GC_2, amp[1569]); 
  FFV2_0(w[170], w[133], w[302], pars->GC_100, amp[1570]); 
  FFV1_0(w[338], w[133], w[74], pars->GC_11, amp[1571]); 
  FFV2_0(w[199], w[133], w[302], pars->GC_100, amp[1572]); 
  FFV2_5_0(w[338], w[133], w[124], pars->GC_51, pars->GC_58, amp[1573]); 
  FFV2_0(w[137], w[2], w[217], pars->GC_100, amp[1574]); 
  FFV2_0(w[3], w[291], w[217], pars->GC_100, amp[1575]); 
  FFV2_0(w[140], w[2], w[217], pars->GC_100, amp[1576]); 
  VVV1_0(w[135], w[217], w[302], pars->GC_4, amp[1577]); 
  VVV1_0(w[217], w[302], w[138], pars->GC_53, amp[1578]); 
  FFV2_0(w[141], w[48], w[302], pars->GC_100, amp[1579]); 
  FFV2_0(w[49], w[265], w[302], pars->GC_100, amp[1580]); 
  FFV2_0(w[144], w[48], w[302], pars->GC_100, amp[1581]); 
  FFV2_0(w[49], w[145], w[302], pars->GC_100, amp[1582]); 
  FFV2_0(w[146], w[48], w[302], pars->GC_100, amp[1583]); 
  FFV2_0(w[49], w[267], w[302], pars->GC_100, amp[1584]); 
  FFV1_0(w[3], w[339], w[149], pars->GC_3, amp[1585]); 
  FFV2_4_0(w[3], w[339], w[152], pars->GC_50, pars->GC_59, amp[1586]); 
  FFV2_0(w[270], w[2], w[152], pars->GC_62, amp[1587]); 
  VVV1_0(w[149], w[268], w[302], pars->GC_4, amp[1588]); 
  VVV1_0(w[268], w[302], w[152], pars->GC_53, amp[1589]); 
  FFV2_0(w[49], w[272], w[302], pars->GC_100, amp[1590]); 
  FFV2_0(w[163], w[48], w[302], pars->GC_100, amp[1591]); 
  FFV1_0(w[338], w[48], w[149], pars->GC_1, amp[1592]); 
  FFV2_0(w[167], w[48], w[302], pars->GC_100, amp[1593]); 
  FFV1_0(w[338], w[48], w[166], pars->GC_11, amp[1594]); 
  FFV2_0(w[168], w[48], w[302], pars->GC_100, amp[1595]); 
  FFV2_3_0(w[338], w[48], w[152], pars->GC_50, pars->GC_58, amp[1596]); 
  FFV2_0(w[338], w[133], w[217], pars->GC_100, amp[1597]); 
  FFV1_0(w[3], w[334], w[123], pars->GC_3, amp[1598]); 
  FFV2_4_0(w[3], w[334], w[124], pars->GC_50, pars->GC_59, amp[1599]); 
  FFV2_0(w[333], w[2], w[124], pars->GC_62, amp[1600]); 
  VVV1_0(w[123], w[332], w[302], pars->GC_4, amp[1601]); 
  VVV1_0(w[332], w[302], w[124], pars->GC_53, amp[1602]); 
  FFV2_0(w[340], w[48], w[302], pars->GC_100, amp[1603]); 
  FFV1_0(w[3], w[339], w[183], pars->GC_3, amp[1604]); 
  FFV2_4_0(w[3], w[339], w[186], pars->GC_50, pars->GC_59, amp[1605]); 
  FFV2_0(w[270], w[2], w[186], pars->GC_62, amp[1606]); 
  VVV1_0(w[183], w[268], w[302], pars->GC_4, amp[1607]); 
  VVV1_0(w[268], w[302], w[186], pars->GC_53, amp[1608]); 
  FFV2_0(w[271], w[133], w[302], pars->GC_100, amp[1609]); 
  FFV2_0(w[341], w[48], w[302], pars->GC_100, amp[1610]); 
  FFV1_0(w[338], w[48], w[183], pars->GC_1, amp[1611]); 
  FFV2_0(w[167], w[48], w[302], pars->GC_100, amp[1612]); 
  FFV1_0(w[338], w[48], w[166], pars->GC_11, amp[1613]); 
  FFV2_0(w[342], w[48], w[302], pars->GC_100, amp[1614]); 
  FFV2_3_0(w[338], w[48], w[186], pars->GC_50, pars->GC_58, amp[1615]); 
  FFV2_0(w[274], w[133], w[302], pars->GC_100, amp[1616]); 
  FFV1_0(w[338], w[133], w[123], pars->GC_1, amp[1617]); 
  FFV2_0(w[170], w[133], w[302], pars->GC_100, amp[1618]); 
  FFV1_0(w[338], w[133], w[74], pars->GC_11, amp[1619]); 
  FFV2_0(w[275], w[133], w[302], pars->GC_100, amp[1620]); 
  FFV2_3_0(w[338], w[133], w[124], pars->GC_50, pars->GC_58, amp[1621]); 
  FFV2_0(w[3], w[276], w[85], pars->GC_62, amp[1622]); 
  FFV2_0(w[277], w[2], w[85], pars->GC_62, amp[1623]); 
  FFV2_3_0(w[200], w[5], w[278], pars->GC_50, pars->GC_58, amp[1624]); 
  FFV2_3_0(w[1], w[201], w[278], pars->GC_50, pars->GC_58, amp[1625]); 
  FFV2_3_0(w[19], w[5], w[278], pars->GC_50, pars->GC_58, amp[1626]); 
  FFV2_3_0(w[1], w[20], w[278], pars->GC_50, pars->GC_58, amp[1627]); 
  FFV2_3_0(w[202], w[5], w[278], pars->GC_50, pars->GC_58, amp[1628]); 
  FFV2_3_0(w[1], w[203], w[278], pars->GC_50, pars->GC_58, amp[1629]); 
  FFV2_0(w[3], w[303], w[205], pars->GC_100, amp[1630]); 
  VVV1_0(w[204], w[205], w[278], pars->GC_53, amp[1631]); 
  FFV2_5_0(w[207], w[4], w[278], pars->GC_51, pars->GC_58, amp[1632]); 
  FFV2_3_0(w[1], w[208], w[278], pars->GC_50, pars->GC_58, amp[1633]); 
  FFV2_3_0(w[209], w[5], w[278], pars->GC_50, pars->GC_58, amp[1634]); 
  FFV2_0(w[281], w[5], w[205], pars->GC_100, amp[1635]); 
  FFV2_5_0(w[210], w[4], w[278], pars->GC_51, pars->GC_58, amp[1636]); 
  FFV1_0(w[281], w[4], w[82], pars->GC_2, amp[1637]); 
  FFV2_5_0(w[46], w[4], w[278], pars->GC_51, pars->GC_58, amp[1638]); 
  FFV1_0(w[281], w[4], w[45], pars->GC_11, amp[1639]); 
  FFV2_5_0(w[211], w[4], w[278], pars->GC_51, pars->GC_58, amp[1640]); 
  FFV2_5_0(w[281], w[4], w[85], pars->GC_51, pars->GC_58, amp[1641]); 
  FFV2_0(w[3], w[282], w[115], pars->GC_62, amp[1642]); 
  FFV2_0(w[283], w[2], w[115], pars->GC_62, amp[1643]); 
  FFV2_3_0(w[212], w[4], w[278], pars->GC_50, pars->GC_58, amp[1644]); 
  FFV2_3_0(w[49], w[213], w[278], pars->GC_50, pars->GC_58, amp[1645]); 
  FFV2_3_0(w[61], w[4], w[278], pars->GC_50, pars->GC_58, amp[1646]); 
  FFV2_3_0(w[49], w[62], w[278], pars->GC_50, pars->GC_58, amp[1647]); 
  FFV2_3_0(w[214], w[4], w[278], pars->GC_50, pars->GC_58, amp[1648]); 
  FFV2_3_0(w[49], w[215], w[278], pars->GC_50, pars->GC_58, amp[1649]); 
  FFV2_0(w[3], w[308], w[217], pars->GC_100, amp[1650]); 
  VVV1_0(w[216], w[217], w[278], pars->GC_53, amp[1651]); 
  FFV2_5_0(w[219], w[48], w[278], pars->GC_51, pars->GC_58, amp[1652]); 
  FFV2_3_0(w[49], w[220], w[278], pars->GC_50, pars->GC_58, amp[1653]); 
  FFV2_3_0(w[221], w[4], w[278], pars->GC_50, pars->GC_58, amp[1654]); 
  FFV2_0(w[281], w[4], w[217], pars->GC_100, amp[1655]); 
  FFV2_5_0(w[222], w[48], w[278], pars->GC_51, pars->GC_58, amp[1656]); 
  FFV1_0(w[281], w[48], w[112], pars->GC_2, amp[1657]); 
  FFV2_5_0(w[79], w[48], w[278], pars->GC_51, pars->GC_58, amp[1658]); 
  FFV1_0(w[281], w[48], w[78], pars->GC_11, amp[1659]); 
  FFV2_5_0(w[223], w[48], w[278], pars->GC_51, pars->GC_58, amp[1660]); 
  FFV2_5_0(w[281], w[48], w[115], pars->GC_51, pars->GC_58, amp[1661]); 
  FFV2_0(w[3], w[276], w[124], pars->GC_62, amp[1662]); 
  FFV2_0(w[277], w[2], w[124], pars->GC_62, amp[1663]); 
  FFV2_3_0(w[224], w[48], w[278], pars->GC_50, pars->GC_58, amp[1664]); 
  FFV2_3_0(w[49], w[225], w[278], pars->GC_50, pars->GC_58, amp[1665]); 
  FFV2_3_0(w[69], w[48], w[278], pars->GC_50, pars->GC_58, amp[1666]); 
  FFV2_3_0(w[49], w[70], w[278], pars->GC_50, pars->GC_58, amp[1667]); 
  FFV2_3_0(w[226], w[48], w[278], pars->GC_50, pars->GC_58, amp[1668]); 
  FFV2_3_0(w[49], w[227], w[278], pars->GC_50, pars->GC_58, amp[1669]); 
  FFV2_0(w[3], w[312], w[229], pars->GC_100, amp[1670]); 
  VVV1_0(w[228], w[229], w[278], pars->GC_53, amp[1671]); 
  FFV2_5_0(w[231], w[4], w[278], pars->GC_51, pars->GC_58, amp[1672]); 
  FFV2_3_0(w[49], w[232], w[278], pars->GC_50, pars->GC_58, amp[1673]); 
  FFV2_3_0(w[233], w[48], w[278], pars->GC_50, pars->GC_58, amp[1674]); 
  FFV2_0(w[281], w[48], w[229], pars->GC_100, amp[1675]); 
  FFV2_5_0(w[234], w[4], w[278], pars->GC_51, pars->GC_58, amp[1676]); 
  FFV1_0(w[281], w[4], w[123], pars->GC_2, amp[1677]); 
  FFV2_5_0(w[75], w[4], w[278], pars->GC_51, pars->GC_58, amp[1678]); 
  FFV1_0(w[281], w[4], w[74], pars->GC_11, amp[1679]); 
  FFV2_5_0(w[235], w[4], w[278], pars->GC_51, pars->GC_58, amp[1680]); 
  FFV2_5_0(w[281], w[4], w[124], pars->GC_51, pars->GC_58, amp[1681]); 
  FFV2_0(w[3], w[343], w[86], pars->GC_62, amp[1682]); 
  FFV2_0(w[316], w[2], w[86], pars->GC_62, amp[1683]); 
  FFV2_3_0(w[240], w[4], w[278], pars->GC_50, pars->GC_58, amp[1684]); 
  FFV2_3_0(w[0], w[241], w[278], pars->GC_50, pars->GC_58, amp[1685]); 
  FFV2_3_0(w[75], w[4], w[278], pars->GC_50, pars->GC_58, amp[1686]); 
  FFV2_3_0(w[0], w[242], w[278], pars->GC_50, pars->GC_58, amp[1687]); 
  FFV2_3_0(w[243], w[4], w[278], pars->GC_50, pars->GC_58, amp[1688]); 
  FFV2_3_0(w[0], w[244], w[278], pars->GC_50, pars->GC_58, amp[1689]); 
  FFV2_0(w[3], w[327], w[228], pars->GC_100, amp[1690]); 
  VVV1_0(w[229], w[228], w[278], pars->GC_53, amp[1691]); 
  FFV2_5_0(w[233], w[48], w[278], pars->GC_51, pars->GC_58, amp[1692]); 
  FFV2_3_0(w[0], w[246], w[278], pars->GC_50, pars->GC_58, amp[1693]); 
  FFV2_3_0(w[231], w[4], w[278], pars->GC_50, pars->GC_58, amp[1694]); 
  FFV2_0(w[344], w[4], w[228], pars->GC_100, amp[1695]); 
  FFV2_5_0(w[249], w[48], w[278], pars->GC_51, pars->GC_58, amp[1696]); 
  FFV1_0(w[344], w[48], w[81], pars->GC_2, amp[1697]); 
  FFV2_5_0(w[69], w[48], w[278], pars->GC_51, pars->GC_58, amp[1698]); 
  FFV1_0(w[344], w[48], w[18], pars->GC_11, amp[1699]); 
  FFV2_5_0(w[250], w[48], w[278], pars->GC_51, pars->GC_58, amp[1700]); 
  FFV2_5_0(w[344], w[48], w[86], pars->GC_51, pars->GC_58, amp[1701]); 
  FFV2_0(w[3], w[345], w[116], pars->GC_62, amp[1702]); 
  FFV2_0(w[319], w[2], w[116], pars->GC_62, amp[1703]); 
  FFV2_3_0(w[255], w[48], w[278], pars->GC_50, pars->GC_58, amp[1704]); 
  FFV2_3_0(w[0], w[256], w[278], pars->GC_50, pars->GC_58, amp[1705]); 
  FFV2_3_0(w[79], w[48], w[278], pars->GC_50, pars->GC_58, amp[1706]); 
  FFV2_3_0(w[0], w[257], w[278], pars->GC_50, pars->GC_58, amp[1707]); 
  FFV2_3_0(w[258], w[48], w[278], pars->GC_50, pars->GC_58, amp[1708]); 
  FFV2_3_0(w[0], w[259], w[278], pars->GC_50, pars->GC_58, amp[1709]); 
  FFV2_0(w[3], w[326], w[216], pars->GC_100, amp[1710]); 
  VVV1_0(w[217], w[216], w[278], pars->GC_53, amp[1711]); 
  FFV2_5_0(w[221], w[4], w[278], pars->GC_51, pars->GC_58, amp[1712]); 
  FFV2_3_0(w[0], w[261], w[278], pars->GC_50, pars->GC_58, amp[1713]); 
  FFV2_3_0(w[219], w[48], w[278], pars->GC_50, pars->GC_58, amp[1714]); 
  FFV2_0(w[344], w[48], w[216], pars->GC_100, amp[1715]); 
  FFV2_5_0(w[262], w[4], w[278], pars->GC_51, pars->GC_58, amp[1716]); 
  FFV1_0(w[344], w[4], w[111], pars->GC_2, amp[1717]); 
  FFV2_5_0(w[61], w[4], w[278], pars->GC_51, pars->GC_58, amp[1718]); 
  FFV1_0(w[344], w[4], w[60], pars->GC_11, amp[1719]); 
  FFV2_5_0(w[263], w[4], w[278], pars->GC_51, pars->GC_58, amp[1720]); 
  FFV2_5_0(w[344], w[4], w[116], pars->GC_51, pars->GC_58, amp[1721]); 
  FFV2_0(w[3], w[291], w[124], pars->GC_62, amp[1722]); 
  FFV2_0(w[292], w[2], w[124], pars->GC_62, amp[1723]); 
  FFV2_3_0(w[264], w[48], w[278], pars->GC_50, pars->GC_58, amp[1724]); 
  FFV2_3_0(w[49], w[265], w[278], pars->GC_50, pars->GC_58, amp[1725]); 
  FFV2_3_0(w[144], w[48], w[278], pars->GC_50, pars->GC_58, amp[1726]); 
  FFV2_3_0(w[49], w[145], w[278], pars->GC_50, pars->GC_58, amp[1727]); 
  FFV2_3_0(w[266], w[48], w[278], pars->GC_50, pars->GC_58, amp[1728]); 
  FFV2_3_0(w[49], w[267], w[278], pars->GC_50, pars->GC_58, amp[1729]); 
  FFV2_0(w[3], w[339], w[269], pars->GC_100, amp[1730]); 
  VVV1_0(w[268], w[269], w[278], pars->GC_53, amp[1731]); 
  FFV2_5_0(w[271], w[133], w[278], pars->GC_51, pars->GC_58, amp[1732]); 
  FFV2_3_0(w[49], w[272], w[278], pars->GC_50, pars->GC_58, amp[1733]); 
  FFV2_3_0(w[273], w[48], w[278], pars->GC_50, pars->GC_58, amp[1734]); 
  FFV2_0(w[295], w[48], w[269], pars->GC_100, amp[1735]); 
  FFV2_5_0(w[274], w[133], w[278], pars->GC_51, pars->GC_58, amp[1736]); 
  FFV1_0(w[295], w[133], w[123], pars->GC_2, amp[1737]); 
  FFV2_5_0(w[170], w[133], w[278], pars->GC_51, pars->GC_58, amp[1738]); 
  FFV1_0(w[295], w[133], w[74], pars->GC_11, amp[1739]); 
  FFV2_5_0(w[275], w[133], w[278], pars->GC_51, pars->GC_58, amp[1740]); 
  FFV2_5_0(w[295], w[133], w[124], pars->GC_51, pars->GC_58, amp[1741]); 
  FFV2_0(w[3], w[276], w[10], pars->GC_62, amp[1742]); 
  FFV2_0(w[277], w[2], w[10], pars->GC_62, amp[1743]); 
  FFV2_5_0(w[15], w[5], w[278], pars->GC_51, pars->GC_58, amp[1744]); 
  FFV2_5_0(w[1], w[16], w[278], pars->GC_51, pars->GC_58, amp[1745]); 
  FFV2_5_0(w[19], w[5], w[278], pars->GC_51, pars->GC_58, amp[1746]); 
  FFV2_5_0(w[1], w[20], w[278], pars->GC_51, pars->GC_58, amp[1747]); 
  FFV2_5_0(w[21], w[5], w[278], pars->GC_51, pars->GC_58, amp[1748]); 
  FFV2_5_0(w[1], w[22], w[278], pars->GC_51, pars->GC_58, amp[1749]); 
  FFV2_5_0(w[44], w[4], w[278], pars->GC_51, pars->GC_58, amp[1750]); 
  FFV1_0(w[281], w[4], w[7], pars->GC_2, amp[1751]); 
  FFV2_5_0(w[46], w[4], w[278], pars->GC_51, pars->GC_58, amp[1752]); 
  FFV1_0(w[281], w[4], w[45], pars->GC_11, amp[1753]); 
  FFV2_5_0(w[47], w[4], w[278], pars->GC_51, pars->GC_58, amp[1754]); 
  FFV2_5_0(w[281], w[4], w[10], pars->GC_51, pars->GC_58, amp[1755]); 
  FFV2_0(w[3], w[276], w[85], pars->GC_62, amp[1756]); 
  FFV2_0(w[277], w[2], w[85], pars->GC_62, amp[1757]); 
  FFV2_3_0(w[200], w[5], w[278], pars->GC_50, pars->GC_58, amp[1758]); 
  FFV2_3_0(w[1], w[201], w[278], pars->GC_50, pars->GC_58, amp[1759]); 
  FFV2_3_0(w[19], w[5], w[278], pars->GC_50, pars->GC_58, amp[1760]); 
  FFV2_3_0(w[1], w[20], w[278], pars->GC_50, pars->GC_58, amp[1761]); 
  FFV2_3_0(w[202], w[5], w[278], pars->GC_50, pars->GC_58, amp[1762]); 
  FFV2_3_0(w[1], w[203], w[278], pars->GC_50, pars->GC_58, amp[1763]); 
  FFV2_5_0(w[210], w[4], w[278], pars->GC_51, pars->GC_58, amp[1764]); 
  FFV1_0(w[281], w[4], w[82], pars->GC_2, amp[1765]); 
  FFV2_5_0(w[46], w[4], w[278], pars->GC_51, pars->GC_58, amp[1766]); 
  FFV1_0(w[281], w[4], w[45], pars->GC_11, amp[1767]); 
  FFV2_5_0(w[211], w[4], w[278], pars->GC_51, pars->GC_58, amp[1768]); 
  FFV2_5_0(w[281], w[4], w[85], pars->GC_51, pars->GC_58, amp[1769]); 
  FFV2_0(w[3], w[282], w[54], pars->GC_62, amp[1770]); 
  FFV2_0(w[283], w[2], w[54], pars->GC_62, amp[1771]); 
  FFV2_5_0(w[58], w[4], w[278], pars->GC_51, pars->GC_58, amp[1772]); 
  FFV2_5_0(w[49], w[59], w[278], pars->GC_51, pars->GC_58, amp[1773]); 
  FFV2_5_0(w[61], w[4], w[278], pars->GC_51, pars->GC_58, amp[1774]); 
  FFV2_5_0(w[49], w[62], w[278], pars->GC_51, pars->GC_58, amp[1775]); 
  FFV2_5_0(w[63], w[4], w[278], pars->GC_51, pars->GC_58, amp[1776]); 
  FFV2_5_0(w[49], w[64], w[278], pars->GC_51, pars->GC_58, amp[1777]); 
  FFV2_5_0(w[77], w[48], w[278], pars->GC_51, pars->GC_58, amp[1778]); 
  FFV1_0(w[281], w[48], w[51], pars->GC_2, amp[1779]); 
  FFV2_5_0(w[79], w[48], w[278], pars->GC_51, pars->GC_58, amp[1780]); 
  FFV1_0(w[281], w[48], w[78], pars->GC_11, amp[1781]); 
  FFV2_5_0(w[80], w[48], w[278], pars->GC_51, pars->GC_58, amp[1782]); 
  FFV2_5_0(w[281], w[48], w[54], pars->GC_51, pars->GC_58, amp[1783]); 
  FFV2_0(w[3], w[282], w[115], pars->GC_62, amp[1784]); 
  FFV2_0(w[283], w[2], w[115], pars->GC_62, amp[1785]); 
  FFV2_3_0(w[212], w[4], w[278], pars->GC_50, pars->GC_58, amp[1786]); 
  FFV2_3_0(w[49], w[213], w[278], pars->GC_50, pars->GC_58, amp[1787]); 
  FFV2_3_0(w[61], w[4], w[278], pars->GC_50, pars->GC_58, amp[1788]); 
  FFV2_3_0(w[49], w[62], w[278], pars->GC_50, pars->GC_58, amp[1789]); 
  FFV2_3_0(w[214], w[4], w[278], pars->GC_50, pars->GC_58, amp[1790]); 
  FFV2_3_0(w[49], w[215], w[278], pars->GC_50, pars->GC_58, amp[1791]); 
  FFV2_5_0(w[222], w[48], w[278], pars->GC_51, pars->GC_58, amp[1792]); 
  FFV1_0(w[281], w[48], w[112], pars->GC_2, amp[1793]); 
  FFV2_5_0(w[79], w[48], w[278], pars->GC_51, pars->GC_58, amp[1794]); 
  FFV1_0(w[281], w[48], w[78], pars->GC_11, amp[1795]); 
  FFV2_5_0(w[223], w[48], w[278], pars->GC_51, pars->GC_58, amp[1796]); 
  FFV2_5_0(w[281], w[48], w[115], pars->GC_51, pars->GC_58, amp[1797]); 
  FFV2_0(w[3], w[276], w[66], pars->GC_62, amp[1798]); 
  FFV2_0(w[277], w[2], w[66], pars->GC_62, amp[1799]); 
  FFV2_5_0(w[67], w[48], w[278], pars->GC_51, pars->GC_58, amp[1800]); 
  FFV2_5_0(w[49], w[68], w[278], pars->GC_51, pars->GC_58, amp[1801]); 
  FFV2_5_0(w[69], w[48], w[278], pars->GC_51, pars->GC_58, amp[1802]); 
  FFV2_5_0(w[49], w[70], w[278], pars->GC_51, pars->GC_58, amp[1803]); 
  FFV2_5_0(w[71], w[48], w[278], pars->GC_51, pars->GC_58, amp[1804]); 
  FFV2_5_0(w[49], w[72], w[278], pars->GC_51, pars->GC_58, amp[1805]); 
  FFV2_5_0(w[73], w[4], w[278], pars->GC_51, pars->GC_58, amp[1806]); 
  FFV1_0(w[281], w[4], w[65], pars->GC_2, amp[1807]); 
  FFV2_5_0(w[75], w[4], w[278], pars->GC_51, pars->GC_58, amp[1808]); 
  FFV1_0(w[281], w[4], w[74], pars->GC_11, amp[1809]); 
  FFV2_5_0(w[76], w[4], w[278], pars->GC_51, pars->GC_58, amp[1810]); 
  FFV2_5_0(w[281], w[4], w[66], pars->GC_51, pars->GC_58, amp[1811]); 
  FFV2_0(w[3], w[276], w[124], pars->GC_62, amp[1812]); 
  FFV2_0(w[277], w[2], w[124], pars->GC_62, amp[1813]); 
  FFV2_3_0(w[224], w[48], w[278], pars->GC_50, pars->GC_58, amp[1814]); 
  FFV2_3_0(w[49], w[225], w[278], pars->GC_50, pars->GC_58, amp[1815]); 
  FFV2_3_0(w[69], w[48], w[278], pars->GC_50, pars->GC_58, amp[1816]); 
  FFV2_3_0(w[49], w[70], w[278], pars->GC_50, pars->GC_58, amp[1817]); 
  FFV2_3_0(w[226], w[48], w[278], pars->GC_50, pars->GC_58, amp[1818]); 
  FFV2_3_0(w[49], w[227], w[278], pars->GC_50, pars->GC_58, amp[1819]); 
  FFV2_5_0(w[234], w[4], w[278], pars->GC_51, pars->GC_58, amp[1820]); 
  FFV1_0(w[281], w[4], w[123], pars->GC_2, amp[1821]); 
  FFV2_5_0(w[75], w[4], w[278], pars->GC_51, pars->GC_58, amp[1822]); 
  FFV1_0(w[281], w[4], w[74], pars->GC_11, amp[1823]); 
  FFV2_5_0(w[235], w[4], w[278], pars->GC_51, pars->GC_58, amp[1824]); 
  FFV2_5_0(w[281], w[4], w[124], pars->GC_51, pars->GC_58, amp[1825]); 
  FFV2_0(w[3], w[284], w[85], pars->GC_62, amp[1826]); 
  FFV2_0(w[285], w[2], w[85], pars->GC_62, amp[1827]); 
  FFV2_3_0(w[89], w[5], w[278], pars->GC_50, pars->GC_58, amp[1828]); 
  FFV2_3_0(w[1], w[90], w[278], pars->GC_50, pars->GC_58, amp[1829]); 
  FFV2_3_0(w[19], w[5], w[278], pars->GC_50, pars->GC_58, amp[1830]); 
  FFV2_3_0(w[1], w[20], w[278], pars->GC_50, pars->GC_58, amp[1831]); 
  FFV2_3_0(w[91], w[5], w[278], pars->GC_50, pars->GC_58, amp[1832]); 
  FFV2_3_0(w[1], w[92], w[278], pars->GC_50, pars->GC_58, amp[1833]); 
  FFV2_3_0(w[109], w[4], w[278], pars->GC_50, pars->GC_58, amp[1834]); 
  FFV1_0(w[288], w[4], w[82], pars->GC_1, amp[1835]); 
  FFV2_3_0(w[46], w[4], w[278], pars->GC_50, pars->GC_58, amp[1836]); 
  FFV1_0(w[288], w[4], w[45], pars->GC_11, amp[1837]); 
  FFV2_3_0(w[110], w[4], w[278], pars->GC_50, pars->GC_58, amp[1838]); 
  FFV2_3_0(w[288], w[4], w[85], pars->GC_50, pars->GC_58, amp[1839]); 
  FFV2_0(w[3], w[343], w[86], pars->GC_62, amp[1840]); 
  FFV2_0(w[316], w[2], w[86], pars->GC_62, amp[1841]); 
  FFV2_3_0(w[240], w[4], w[278], pars->GC_50, pars->GC_58, amp[1842]); 
  FFV2_3_0(w[0], w[241], w[278], pars->GC_50, pars->GC_58, amp[1843]); 
  FFV2_3_0(w[75], w[4], w[278], pars->GC_50, pars->GC_58, amp[1844]); 
  FFV2_3_0(w[0], w[242], w[278], pars->GC_50, pars->GC_58, amp[1845]); 
  FFV2_3_0(w[243], w[4], w[278], pars->GC_50, pars->GC_58, amp[1846]); 
  FFV2_3_0(w[0], w[244], w[278], pars->GC_50, pars->GC_58, amp[1847]); 
  FFV2_5_0(w[249], w[48], w[278], pars->GC_51, pars->GC_58, amp[1848]); 
  FFV1_0(w[344], w[48], w[81], pars->GC_2, amp[1849]); 
  FFV2_5_0(w[69], w[48], w[278], pars->GC_51, pars->GC_58, amp[1850]); 
  FFV1_0(w[344], w[48], w[18], pars->GC_11, amp[1851]); 
  FFV2_5_0(w[250], w[48], w[278], pars->GC_51, pars->GC_58, amp[1852]); 
  FFV2_5_0(w[344], w[48], w[86], pars->GC_51, pars->GC_58, amp[1853]); 
  FFV2_0(w[3], w[345], w[116], pars->GC_62, amp[1854]); 
  FFV2_0(w[319], w[2], w[116], pars->GC_62, amp[1855]); 
  FFV2_3_0(w[255], w[48], w[278], pars->GC_50, pars->GC_58, amp[1856]); 
  FFV2_3_0(w[0], w[256], w[278], pars->GC_50, pars->GC_58, amp[1857]); 
  FFV2_3_0(w[79], w[48], w[278], pars->GC_50, pars->GC_58, amp[1858]); 
  FFV2_3_0(w[0], w[257], w[278], pars->GC_50, pars->GC_58, amp[1859]); 
  FFV2_3_0(w[258], w[48], w[278], pars->GC_50, pars->GC_58, amp[1860]); 
  FFV2_3_0(w[0], w[259], w[278], pars->GC_50, pars->GC_58, amp[1861]); 
  FFV2_5_0(w[262], w[4], w[278], pars->GC_51, pars->GC_58, amp[1862]); 
  FFV1_0(w[344], w[4], w[111], pars->GC_2, amp[1863]); 
  FFV2_5_0(w[61], w[4], w[278], pars->GC_51, pars->GC_58, amp[1864]); 
  FFV1_0(w[344], w[4], w[60], pars->GC_11, amp[1865]); 
  FFV2_5_0(w[263], w[4], w[278], pars->GC_51, pars->GC_58, amp[1866]); 
  FFV2_5_0(w[344], w[4], w[116], pars->GC_51, pars->GC_58, amp[1867]); 
  FFV2_0(w[3], w[289], w[115], pars->GC_62, amp[1868]); 
  FFV2_0(w[290], w[2], w[115], pars->GC_62, amp[1869]); 
  FFV2_3_0(w[119], w[4], w[278], pars->GC_50, pars->GC_58, amp[1870]); 
  FFV2_3_0(w[49], w[120], w[278], pars->GC_50, pars->GC_58, amp[1871]); 
  FFV2_3_0(w[61], w[4], w[278], pars->GC_50, pars->GC_58, amp[1872]); 
  FFV2_3_0(w[49], w[62], w[278], pars->GC_50, pars->GC_58, amp[1873]); 
  FFV2_3_0(w[121], w[4], w[278], pars->GC_50, pars->GC_58, amp[1874]); 
  FFV2_3_0(w[49], w[122], w[278], pars->GC_50, pars->GC_58, amp[1875]); 
  FFV2_3_0(w[131], w[48], w[278], pars->GC_50, pars->GC_58, amp[1876]); 
  FFV1_0(w[288], w[48], w[112], pars->GC_1, amp[1877]); 
  FFV2_3_0(w[79], w[48], w[278], pars->GC_50, pars->GC_58, amp[1878]); 
  FFV1_0(w[288], w[48], w[78], pars->GC_11, amp[1879]); 
  FFV2_3_0(w[132], w[48], w[278], pars->GC_50, pars->GC_58, amp[1880]); 
  FFV2_3_0(w[288], w[48], w[115], pars->GC_50, pars->GC_58, amp[1881]); 
  FFV2_0(w[3], w[284], w[124], pars->GC_62, amp[1882]); 
  FFV2_0(w[285], w[2], w[124], pars->GC_62, amp[1883]); 
  FFV2_3_0(w[125], w[48], w[278], pars->GC_50, pars->GC_58, amp[1884]); 
  FFV2_3_0(w[49], w[126], w[278], pars->GC_50, pars->GC_58, amp[1885]); 
  FFV2_3_0(w[69], w[48], w[278], pars->GC_50, pars->GC_58, amp[1886]); 
  FFV2_3_0(w[49], w[70], w[278], pars->GC_50, pars->GC_58, amp[1887]); 
  FFV2_3_0(w[127], w[48], w[278], pars->GC_50, pars->GC_58, amp[1888]); 
  FFV2_3_0(w[49], w[128], w[278], pars->GC_50, pars->GC_58, amp[1889]); 
  FFV2_3_0(w[129], w[4], w[278], pars->GC_50, pars->GC_58, amp[1890]); 
  FFV1_0(w[288], w[4], w[123], pars->GC_1, amp[1891]); 
  FFV2_3_0(w[75], w[4], w[278], pars->GC_50, pars->GC_58, amp[1892]); 
  FFV1_0(w[288], w[4], w[74], pars->GC_11, amp[1893]); 
  FFV2_3_0(w[130], w[4], w[278], pars->GC_50, pars->GC_58, amp[1894]); 
  FFV2_3_0(w[288], w[4], w[124], pars->GC_50, pars->GC_58, amp[1895]); 
  FFV2_0(w[3], w[291], w[66], pars->GC_62, amp[1896]); 
  FFV2_0(w[292], w[2], w[66], pars->GC_62, amp[1897]); 
  FFV2_5_0(w[141], w[48], w[278], pars->GC_51, pars->GC_58, amp[1898]); 
  FFV2_5_0(w[49], w[142], w[278], pars->GC_51, pars->GC_58, amp[1899]); 
  FFV2_5_0(w[144], w[48], w[278], pars->GC_51, pars->GC_58, amp[1900]); 
  FFV2_5_0(w[49], w[145], w[278], pars->GC_51, pars->GC_58, amp[1901]); 
  FFV2_5_0(w[146], w[48], w[278], pars->GC_51, pars->GC_58, amp[1902]); 
  FFV2_5_0(w[49], w[147], w[278], pars->GC_51, pars->GC_58, amp[1903]); 
  FFV2_5_0(w[169], w[133], w[278], pars->GC_51, pars->GC_58, amp[1904]); 
  FFV1_0(w[295], w[133], w[65], pars->GC_2, amp[1905]); 
  FFV2_5_0(w[170], w[133], w[278], pars->GC_51, pars->GC_58, amp[1906]); 
  FFV1_0(w[295], w[133], w[74], pars->GC_11, amp[1907]); 
  FFV2_5_0(w[171], w[133], w[278], pars->GC_51, pars->GC_58, amp[1908]); 
  FFV2_5_0(w[295], w[133], w[66], pars->GC_51, pars->GC_58, amp[1909]); 
  FFV2_0(w[3], w[291], w[124], pars->GC_62, amp[1910]); 
  FFV2_0(w[292], w[2], w[124], pars->GC_62, amp[1911]); 
  FFV2_3_0(w[264], w[48], w[278], pars->GC_50, pars->GC_58, amp[1912]); 
  FFV2_3_0(w[49], w[265], w[278], pars->GC_50, pars->GC_58, amp[1913]); 
  FFV2_3_0(w[144], w[48], w[278], pars->GC_50, pars->GC_58, amp[1914]); 
  FFV2_3_0(w[49], w[145], w[278], pars->GC_50, pars->GC_58, amp[1915]); 
  FFV2_3_0(w[266], w[48], w[278], pars->GC_50, pars->GC_58, amp[1916]); 
  FFV2_3_0(w[49], w[267], w[278], pars->GC_50, pars->GC_58, amp[1917]); 
  FFV2_5_0(w[274], w[133], w[278], pars->GC_51, pars->GC_58, amp[1918]); 
  FFV1_0(w[295], w[133], w[123], pars->GC_2, amp[1919]); 
  FFV2_5_0(w[170], w[133], w[278], pars->GC_51, pars->GC_58, amp[1920]); 
  FFV1_0(w[295], w[133], w[74], pars->GC_11, amp[1921]); 
  FFV2_5_0(w[275], w[133], w[278], pars->GC_51, pars->GC_58, amp[1922]); 
  FFV2_5_0(w[295], w[133], w[124], pars->GC_51, pars->GC_58, amp[1923]); 
  FFV2_0(w[3], w[296], w[124], pars->GC_62, amp[1924]); 
  FFV2_0(w[297], w[2], w[124], pars->GC_62, amp[1925]); 
  FFV2_3_0(w[178], w[48], w[278], pars->GC_50, pars->GC_58, amp[1926]); 
  FFV2_3_0(w[49], w[179], w[278], pars->GC_50, pars->GC_58, amp[1927]); 
  FFV2_3_0(w[144], w[48], w[278], pars->GC_50, pars->GC_58, amp[1928]); 
  FFV2_3_0(w[49], w[145], w[278], pars->GC_50, pars->GC_58, amp[1929]); 
  FFV2_3_0(w[180], w[48], w[278], pars->GC_50, pars->GC_58, amp[1930]); 
  FFV2_3_0(w[49], w[181], w[278], pars->GC_50, pars->GC_58, amp[1931]); 
  FFV2_3_0(w[198], w[133], w[278], pars->GC_50, pars->GC_58, amp[1932]); 
  FFV1_0(w[300], w[133], w[123], pars->GC_1, amp[1933]); 
  FFV2_3_0(w[170], w[133], w[278], pars->GC_50, pars->GC_58, amp[1934]); 
  FFV1_0(w[300], w[133], w[74], pars->GC_11, amp[1935]); 
  FFV2_3_0(w[199], w[133], w[278], pars->GC_50, pars->GC_58, amp[1936]); 
  FFV2_3_0(w[300], w[133], w[124], pars->GC_50, pars->GC_58, amp[1937]); 
  FFV2_0(w[9], w[2], w[301], pars->GC_100, amp[1938]); 
  FFV2_0(w[3], w[276], w[301], pars->GC_100, amp[1939]); 
  FFV2_0(w[13], w[2], w[301], pars->GC_100, amp[1940]); 
  VVV1_0(w[6], w[301], w[302], pars->GC_4, amp[1941]); 
  VVV1_0(w[301], w[302], w[11], pars->GC_53, amp[1942]); 
  FFV2_0(w[15], w[5], w[302], pars->GC_100, amp[1943]); 
  FFV2_0(w[1], w[201], w[302], pars->GC_100, amp[1944]); 
  FFV2_0(w[19], w[5], w[302], pars->GC_100, amp[1945]); 
  FFV2_0(w[1], w[20], w[302], pars->GC_100, amp[1946]); 
  FFV2_0(w[21], w[5], w[302], pars->GC_100, amp[1947]); 
  FFV2_0(w[1], w[203], w[302], pars->GC_100, amp[1948]); 
  FFV2_0(w[304], w[4], w[301], pars->GC_100, amp[1949]); 
  FFV1_0(w[3], w[303], w[24], pars->GC_3, amp[1950]); 
  FFV2_4_0(w[3], w[303], w[27], pars->GC_50, pars->GC_59, amp[1951]); 
  FFV2_0(w[206], w[2], w[27], pars->GC_62, amp[1952]); 
  VVV1_0(w[24], w[204], w[302], pars->GC_4, amp[1953]); 
  VVV1_0(w[204], w[302], w[27], pars->GC_53, amp[1954]); 
  FFV2_0(w[1], w[208], w[302], pars->GC_100, amp[1955]); 
  FFV2_0(w[38], w[5], w[302], pars->GC_100, amp[1956]); 
  FFV1_0(w[304], w[5], w[24], pars->GC_1, amp[1957]); 
  FFV2_0(w[42], w[5], w[302], pars->GC_100, amp[1958]); 
  FFV1_0(w[304], w[5], w[41], pars->GC_11, amp[1959]); 
  FFV2_0(w[43], w[5], w[302], pars->GC_100, amp[1960]); 
  FFV2_3_0(w[304], w[5], w[27], pars->GC_50, pars->GC_58, amp[1961]); 
  FFV2_0(w[3], w[8], w[301], pars->GC_100, amp[1962]); 
  FFV2_0(w[3], w[12], w[301], pars->GC_100, amp[1963]); 
  FFV2_0(w[277], w[2], w[301], pars->GC_100, amp[1964]); 
  VVV1_0(w[6], w[302], w[301], pars->GC_4, amp[1965]); 
  VVV1_0(w[302], w[301], w[11], pars->GC_53, amp[1966]); 
  FFV2_0(w[200], w[5], w[302], pars->GC_100, amp[1967]); 
  FFV2_0(w[1], w[16], w[302], pars->GC_100, amp[1968]); 
  FFV2_0(w[19], w[5], w[302], pars->GC_100, amp[1969]); 
  FFV2_0(w[1], w[20], w[302], pars->GC_100, amp[1970]); 
  FFV2_0(w[202], w[5], w[302], pars->GC_100, amp[1971]); 
  FFV2_0(w[1], w[22], w[302], pars->GC_100, amp[1972]); 
  FFV2_0(w[307], w[4], w[302], pars->GC_100, amp[1973]); 
  FFV1_0(w[3], w[308], w[82], pars->GC_3, amp[1974]); 
  FFV2_4_0(w[3], w[308], w[85], pars->GC_50, pars->GC_59, amp[1975]); 
  FFV2_0(w[218], w[2], w[85], pars->GC_62, amp[1976]); 
  VVV1_0(w[82], w[216], w[302], pars->GC_4, amp[1977]); 
  VVV1_0(w[216], w[302], w[85], pars->GC_53, amp[1978]); 
  FFV2_0(w[309], w[5], w[302], pars->GC_100, amp[1979]); 
  FFV2_0(w[210], w[4], w[302], pars->GC_100, amp[1980]); 
  FFV1_0(w[304], w[4], w[82], pars->GC_1, amp[1981]); 
  FFV2_0(w[46], w[4], w[302], pars->GC_100, amp[1982]); 
  FFV1_0(w[304], w[4], w[45], pars->GC_11, amp[1983]); 
  FFV2_0(w[211], w[4], w[302], pars->GC_100, amp[1984]); 
  FFV2_3_0(w[304], w[4], w[85], pars->GC_50, pars->GC_58, amp[1985]); 
  FFV2_0(w[3], w[52], w[229], pars->GC_100, amp[1986]); 
  FFV2_0(w[3], w[56], w[229], pars->GC_100, amp[1987]); 
  FFV2_0(w[283], w[2], w[229], pars->GC_100, amp[1988]); 
  VVV1_0(w[50], w[302], w[229], pars->GC_4, amp[1989]); 
  VVV1_0(w[302], w[229], w[55], pars->GC_53, amp[1990]); 
  FFV2_0(w[212], w[4], w[302], pars->GC_100, amp[1991]); 
  FFV2_0(w[49], w[59], w[302], pars->GC_100, amp[1992]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[1993]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[1994]); 
  FFV2_0(w[214], w[4], w[302], pars->GC_100, amp[1995]); 
  FFV2_0(w[49], w[64], w[302], pars->GC_100, amp[1996]); 
  FFV2_0(w[233], w[48], w[302], pars->GC_100, amp[1997]); 
  FFV2_0(w[53], w[2], w[229], pars->GC_100, amp[1998]); 
  FFV2_0(w[3], w[282], w[229], pars->GC_100, amp[1999]); 
  FFV2_0(w[57], w[2], w[229], pars->GC_100, amp[2000]); 
  VVV1_0(w[50], w[229], w[302], pars->GC_4, amp[2001]); 
  VVV1_0(w[229], w[302], w[55], pars->GC_53, amp[2002]); 
  FFV2_0(w[58], w[4], w[302], pars->GC_100, amp[2003]); 
  FFV2_0(w[49], w[213], w[302], pars->GC_100, amp[2004]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[2005]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[2006]); 
  FFV2_0(w[63], w[4], w[302], pars->GC_100, amp[2007]); 
  FFV2_0(w[49], w[215], w[302], pars->GC_100, amp[2008]); 
  FFV2_0(w[304], w[48], w[229], pars->GC_100, amp[2009]); 
  FFV2_0(w[3], w[8], w[217], pars->GC_100, amp[2010]); 
  FFV2_0(w[3], w[12], w[217], pars->GC_100, amp[2011]); 
  FFV2_0(w[277], w[2], w[217], pars->GC_100, amp[2012]); 
  VVV1_0(w[6], w[302], w[217], pars->GC_4, amp[2013]); 
  VVV1_0(w[302], w[217], w[11], pars->GC_53, amp[2014]); 
  FFV2_0(w[224], w[48], w[302], pars->GC_100, amp[2015]); 
  FFV2_0(w[49], w[68], w[302], pars->GC_100, amp[2016]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[2017]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[2018]); 
  FFV2_0(w[226], w[48], w[302], pars->GC_100, amp[2019]); 
  FFV2_0(w[49], w[72], w[302], pars->GC_100, amp[2020]); 
  FFV2_0(w[221], w[4], w[302], pars->GC_100, amp[2021]); 
  FFV1_0(w[3], w[308], w[65], pars->GC_3, amp[2022]); 
  FFV2_4_0(w[3], w[308], w[66], pars->GC_50, pars->GC_59, amp[2023]); 
  FFV2_0(w[218], w[2], w[66], pars->GC_62, amp[2024]); 
  VVV1_0(w[65], w[216], w[302], pars->GC_4, amp[2025]); 
  VVV1_0(w[216], w[302], w[66], pars->GC_53, amp[2026]); 
  FFV2_0(w[49], w[220], w[302], pars->GC_100, amp[2027]); 
  FFV2_0(w[73], w[4], w[302], pars->GC_100, amp[2028]); 
  FFV1_0(w[304], w[4], w[65], pars->GC_1, amp[2029]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[2030]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[2031]); 
  FFV2_0(w[76], w[4], w[302], pars->GC_100, amp[2032]); 
  FFV2_3_0(w[304], w[4], w[66], pars->GC_50, pars->GC_58, amp[2033]); 
  FFV1_0(w[3], w[312], w[51], pars->GC_3, amp[2034]); 
  FFV2_4_0(w[3], w[312], w[54], pars->GC_50, pars->GC_59, amp[2035]); 
  FFV2_0(w[230], w[2], w[54], pars->GC_62, amp[2036]); 
  VVV1_0(w[51], w[228], w[302], pars->GC_4, amp[2037]); 
  VVV1_0(w[228], w[302], w[54], pars->GC_53, amp[2038]); 
  FFV2_0(w[49], w[232], w[302], pars->GC_100, amp[2039]); 
  FFV2_0(w[77], w[48], w[302], pars->GC_100, amp[2040]); 
  FFV1_0(w[304], w[48], w[51], pars->GC_1, amp[2041]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[2042]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[2043]); 
  FFV2_0(w[80], w[48], w[302], pars->GC_100, amp[2044]); 
  FFV2_3_0(w[304], w[48], w[54], pars->GC_50, pars->GC_58, amp[2045]); 
  FFV1_0(w[3], w[312], w[112], pars->GC_3, amp[2046]); 
  FFV2_4_0(w[3], w[312], w[115], pars->GC_50, pars->GC_59, amp[2047]); 
  FFV2_0(w[230], w[2], w[115], pars->GC_62, amp[2048]); 
  VVV1_0(w[112], w[228], w[302], pars->GC_4, amp[2049]); 
  VVV1_0(w[228], w[302], w[115], pars->GC_53, amp[2050]); 
  FFV2_0(w[231], w[4], w[302], pars->GC_100, amp[2051]); 
  FFV2_0(w[222], w[48], w[302], pars->GC_100, amp[2052]); 
  FFV1_0(w[304], w[48], w[112], pars->GC_1, amp[2053]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[2054]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[2055]); 
  FFV2_0(w[223], w[48], w[302], pars->GC_100, amp[2056]); 
  FFV2_3_0(w[304], w[48], w[115], pars->GC_50, pars->GC_58, amp[2057]); 
  FFV2_0(w[9], w[2], w[217], pars->GC_100, amp[2058]); 
  FFV2_0(w[3], w[276], w[217], pars->GC_100, amp[2059]); 
  FFV2_0(w[13], w[2], w[217], pars->GC_100, amp[2060]); 
  VVV1_0(w[6], w[217], w[302], pars->GC_4, amp[2061]); 
  VVV1_0(w[217], w[302], w[11], pars->GC_53, amp[2062]); 
  FFV2_0(w[67], w[48], w[302], pars->GC_100, amp[2063]); 
  FFV2_0(w[49], w[225], w[302], pars->GC_100, amp[2064]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[2065]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[2066]); 
  FFV2_0(w[71], w[48], w[302], pars->GC_100, amp[2067]); 
  FFV2_0(w[49], w[227], w[302], pars->GC_100, amp[2068]); 
  FFV2_0(w[304], w[4], w[217], pars->GC_100, amp[2069]); 
  FFV1_0(w[3], w[308], w[123], pars->GC_3, amp[2070]); 
  FFV2_4_0(w[3], w[308], w[124], pars->GC_50, pars->GC_59, amp[2071]); 
  FFV2_0(w[218], w[2], w[124], pars->GC_62, amp[2072]); 
  VVV1_0(w[123], w[216], w[302], pars->GC_4, amp[2073]); 
  VVV1_0(w[216], w[302], w[124], pars->GC_53, amp[2074]); 
  FFV2_0(w[219], w[48], w[302], pars->GC_100, amp[2075]); 
  FFV2_0(w[234], w[4], w[302], pars->GC_100, amp[2076]); 
  FFV1_0(w[304], w[4], w[123], pars->GC_1, amp[2077]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[2078]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[2079]); 
  FFV2_0(w[235], w[4], w[302], pars->GC_100, amp[2080]); 
  FFV2_3_0(w[304], w[4], w[124], pars->GC_50, pars->GC_58, amp[2081]); 
  FFV1_0(w[218], w[2], w[82], pars->GC_3, amp[2082]); 
  FFV2_0(w[3], w[308], w[85], pars->GC_62, amp[2083]); 
  FFV2_4_0(w[218], w[2], w[85], pars->GC_50, pars->GC_59, amp[2084]); 
  VVV1_0(w[82], w[302], w[216], pars->GC_4, amp[2085]); 
  VVV1_0(w[302], w[216], w[85], pars->GC_53, amp[2086]); 
  FFV2_0(w[1], w[313], w[302], pars->GC_100, amp[2087]); 
  FFV2_0(w[109], w[4], w[302], pars->GC_100, amp[2088]); 
  FFV1_0(w[304], w[4], w[82], pars->GC_2, amp[2089]); 
  FFV2_0(w[46], w[4], w[302], pars->GC_100, amp[2090]); 
  FFV1_0(w[304], w[4], w[45], pars->GC_11, amp[2091]); 
  FFV2_0(w[110], w[4], w[302], pars->GC_100, amp[2092]); 
  FFV2_5_0(w[304], w[4], w[85], pars->GC_51, pars->GC_58, amp[2093]); 
  FFV2_0(w[3], w[95], w[205], pars->GC_100, amp[2094]); 
  FFV2_0(w[3], w[99], w[205], pars->GC_100, amp[2095]); 
  FFV2_0(w[287], w[2], w[205], pars->GC_100, amp[2096]); 
  VVV1_0(w[93], w[302], w[205], pars->GC_4, amp[2097]); 
  VVV1_0(w[302], w[205], w[98], pars->GC_53, amp[2098]); 
  FFV2_0(w[101], w[4], w[302], pars->GC_100, amp[2099]); 
  FFV2_0(w[1], w[314], w[302], pars->GC_100, amp[2100]); 
  FFV2_0(w[34], w[4], w[302], pars->GC_100, amp[2101]); 
  FFV2_0(w[1], w[35], w[302], pars->GC_100, amp[2102]); 
  FFV2_0(w[103], w[4], w[302], pars->GC_100, amp[2103]); 
  FFV2_0(w[1], w[315], w[302], pars->GC_100, amp[2104]); 
  FFV2_0(w[304], w[5], w[205], pars->GC_100, amp[2105]); 
  FFV2_0(w[3], w[251], w[228], pars->GC_100, amp[2106]); 
  FFV2_0(w[3], w[253], w[228], pars->GC_100, amp[2107]); 
  FFV2_0(w[319], w[2], w[228], pars->GC_100, amp[2108]); 
  VVV1_0(w[51], w[302], w[228], pars->GC_4, amp[2109]); 
  VVV1_0(w[302], w[228], w[54], pars->GC_53, amp[2110]); 
  FFV2_0(w[255], w[48], w[302], pars->GC_100, amp[2111]); 
  FFV2_0(w[0], w[320], w[302], pars->GC_100, amp[2112]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[2113]); 
  FFV2_0(w[0], w[257], w[302], pars->GC_100, amp[2114]); 
  FFV2_0(w[258], w[48], w[302], pars->GC_100, amp[2115]); 
  FFV2_0(w[0], w[321], w[302], pars->GC_100, amp[2116]); 
  FFV2_0(w[231], w[4], w[302], pars->GC_100, amp[2117]); 
  FFV1_0(w[230], w[2], w[112], pars->GC_3, amp[2118]); 
  FFV2_0(w[3], w[312], w[115], pars->GC_62, amp[2119]); 
  FFV2_4_0(w[230], w[2], w[115], pars->GC_50, pars->GC_59, amp[2120]); 
  VVV1_0(w[112], w[302], w[228], pars->GC_4, amp[2121]); 
  VVV1_0(w[302], w[228], w[115], pars->GC_53, amp[2122]); 
  FFV2_0(w[49], w[232], w[302], pars->GC_100, amp[2123]); 
  FFV2_0(w[131], w[48], w[302], pars->GC_100, amp[2124]); 
  FFV1_0(w[304], w[48], w[112], pars->GC_2, amp[2125]); 
  FFV2_0(w[79], w[48], w[302], pars->GC_100, amp[2126]); 
  FFV1_0(w[304], w[48], w[78], pars->GC_11, amp[2127]); 
  FFV2_0(w[132], w[48], w[302], pars->GC_100, amp[2128]); 
  FFV2_5_0(w[304], w[48], w[115], pars->GC_51, pars->GC_58, amp[2129]); 
  FFV2_0(w[3], w[236], w[216], pars->GC_100, amp[2130]); 
  FFV2_0(w[3], w[238], w[216], pars->GC_100, amp[2131]); 
  FFV2_0(w[316], w[2], w[216], pars->GC_100, amp[2132]); 
  VVV1_0(w[65], w[302], w[216], pars->GC_4, amp[2133]); 
  VVV1_0(w[302], w[216], w[66], pars->GC_53, amp[2134]); 
  FFV2_0(w[240], w[4], w[302], pars->GC_100, amp[2135]); 
  FFV2_0(w[0], w[317], w[302], pars->GC_100, amp[2136]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[2137]); 
  FFV2_0(w[0], w[242], w[302], pars->GC_100, amp[2138]); 
  FFV2_0(w[243], w[4], w[302], pars->GC_100, amp[2139]); 
  FFV2_0(w[0], w[318], w[302], pars->GC_100, amp[2140]); 
  FFV2_0(w[219], w[48], w[302], pars->GC_100, amp[2141]); 
  FFV2_0(w[3], w[83], w[217], pars->GC_100, amp[2142]); 
  FFV2_0(w[3], w[87], w[217], pars->GC_100, amp[2143]); 
  FFV2_0(w[285], w[2], w[217], pars->GC_100, amp[2144]); 
  VVV1_0(w[81], w[302], w[217], pars->GC_4, amp[2145]); 
  VVV1_0(w[302], w[217], w[86], pars->GC_53, amp[2146]); 
  FFV2_0(w[125], w[48], w[302], pars->GC_100, amp[2147]); 
  FFV2_0(w[49], w[322], w[302], pars->GC_100, amp[2148]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[2149]); 
  FFV2_0(w[49], w[70], w[302], pars->GC_100, amp[2150]); 
  FFV2_0(w[127], w[48], w[302], pars->GC_100, amp[2151]); 
  FFV2_0(w[49], w[323], w[302], pars->GC_100, amp[2152]); 
  FFV2_0(w[304], w[4], w[217], pars->GC_100, amp[2153]); 
  FFV2_0(w[3], w[113], w[229], pars->GC_100, amp[2154]); 
  FFV2_0(w[3], w[117], w[229], pars->GC_100, amp[2155]); 
  FFV2_0(w[290], w[2], w[229], pars->GC_100, amp[2156]); 
  VVV1_0(w[111], w[302], w[229], pars->GC_4, amp[2157]); 
  VVV1_0(w[302], w[229], w[116], pars->GC_53, amp[2158]); 
  FFV2_0(w[119], w[4], w[302], pars->GC_100, amp[2159]); 
  FFV2_0(w[49], w[324], w[302], pars->GC_100, amp[2160]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[2161]); 
  FFV2_0(w[49], w[62], w[302], pars->GC_100, amp[2162]); 
  FFV2_0(w[121], w[4], w[302], pars->GC_100, amp[2163]); 
  FFV2_0(w[49], w[325], w[302], pars->GC_100, amp[2164]); 
  FFV2_0(w[304], w[48], w[229], pars->GC_100, amp[2165]); 
  FFV1_0(w[3], w[327], w[111], pars->GC_3, amp[2166]); 
  FFV2_4_0(w[3], w[327], w[116], pars->GC_50, pars->GC_59, amp[2167]); 
  FFV2_0(w[245], w[2], w[116], pars->GC_62, amp[2168]); 
  VVV1_0(w[111], w[229], w[302], pars->GC_4, amp[2169]); 
  VVV1_0(w[229], w[302], w[116], pars->GC_53, amp[2170]); 
  FFV2_0(w[233], w[48], w[302], pars->GC_100, amp[2171]); 
  FFV2_0(w[262], w[4], w[302], pars->GC_100, amp[2172]); 
  FFV1_0(w[328], w[4], w[111], pars->GC_1, amp[2173]); 
  FFV2_0(w[61], w[4], w[302], pars->GC_100, amp[2174]); 
  FFV1_0(w[328], w[4], w[60], pars->GC_11, amp[2175]); 
  FFV2_0(w[263], w[4], w[302], pars->GC_100, amp[2176]); 
  FFV2_3_0(w[328], w[4], w[116], pars->GC_50, pars->GC_58, amp[2177]); 
  FFV1_0(w[218], w[2], w[123], pars->GC_3, amp[2178]); 
  FFV2_0(w[3], w[308], w[124], pars->GC_62, amp[2179]); 
  FFV2_4_0(w[218], w[2], w[124], pars->GC_50, pars->GC_59, amp[2180]); 
  VVV1_0(w[123], w[302], w[216], pars->GC_4, amp[2181]); 
  VVV1_0(w[302], w[216], w[124], pars->GC_53, amp[2182]); 
  FFV2_0(w[49], w[220], w[302], pars->GC_100, amp[2183]); 
  FFV2_0(w[129], w[4], w[302], pars->GC_100, amp[2184]); 
  FFV1_0(w[304], w[4], w[123], pars->GC_2, amp[2185]); 
  FFV2_0(w[75], w[4], w[302], pars->GC_100, amp[2186]); 
  FFV1_0(w[304], w[4], w[74], pars->GC_11, amp[2187]); 
  FFV2_0(w[130], w[4], w[302], pars->GC_100, amp[2188]); 
  FFV2_5_0(w[304], w[4], w[124], pars->GC_51, pars->GC_58, amp[2189]); 
  FFV1_0(w[3], w[326], w[81], pars->GC_3, amp[2190]); 
  FFV2_4_0(w[3], w[326], w[86], pars->GC_50, pars->GC_59, amp[2191]); 
  FFV2_0(w[260], w[2], w[86], pars->GC_62, amp[2192]); 
  VVV1_0(w[81], w[217], w[302], pars->GC_4, amp[2193]); 
  VVV1_0(w[217], w[302], w[86], pars->GC_53, amp[2194]); 
  FFV2_0(w[221], w[4], w[302], pars->GC_100, amp[2195]); 
  FFV2_0(w[249], w[48], w[302], pars->GC_100, amp[2196]); 
  FFV1_0(w[328], w[48], w[81], pars->GC_1, amp[2197]); 
  FFV2_0(w[69], w[48], w[302], pars->GC_100, amp[2198]); 
  FFV1_0(w[328], w[48], w[18], pars->GC_11, amp[2199]); 
  FFV2_0(w[250], w[48], w[302], pars->GC_100, amp[2200]); 
  FFV2_3_0(w[328], w[48], w[86], pars->GC_50, pars->GC_58, amp[2201]); 
  FFV2_0(w[3], w[136], w[217], pars->GC_100, amp[2202]); 
  FFV2_0(w[3], w[139], w[217], pars->GC_100, amp[2203]); 
  FFV2_0(w[292], w[2], w[217], pars->GC_100, amp[2204]); 
  VVV1_0(w[135], w[302], w[217], pars->GC_4, amp[2205]); 
  VVV1_0(w[302], w[217], w[138], pars->GC_53, amp[2206]); 
  FFV2_0(w[264], w[48], w[302], pars->GC_100, amp[2207]); 
  FFV2_0(w[49], w[142], w[302], pars->GC_100, amp[2208]); 
  FFV2_0(w[144], w[48], w[302], pars->GC_100, amp[2209]); 
  FFV2_0(w[49], w[145], w[302], pars->GC_100, amp[2210]); 
  FFV2_0(w[266], w[48], w[302], pars->GC_100, amp[2211]); 
  FFV2_0(w[49], w[147], w[302], pars->GC_100, amp[2212]); 
  FFV2_0(w[331], w[133], w[302], pars->GC_100, amp[2213]); 
  FFV2_0(w[3], w[150], w[269], pars->GC_100, amp[2214]); 
  FFV2_0(w[3], w[154], w[269], pars->GC_100, amp[2215]); 
  FFV2_0(w[294], w[2], w[269], pars->GC_100, amp[2216]); 
  VVV1_0(w[148], w[302], w[269], pars->GC_4, amp[2217]); 
  VVV1_0(w[302], w[269], w[153], pars->GC_53, amp[2218]); 
  FFV2_0(w[329], w[133], w[302], pars->GC_100, amp[2219]); 
  FFV2_0(w[49], w[157], w[302], pars->GC_100, amp[2220]); 
  FFV2_0(w[159], w[133], w[302], pars->GC_100, amp[2221]); 
  FFV2_0(w[49], w[160], w[302], pars->GC_100, amp[2222]); 
  FFV2_0(w[330], w[133], w[302], pars->GC_100, amp[2223]); 
  FFV2_0(w[49], w[162], w[302], pars->GC_100, amp[2224]); 
  FFV2_0(w[273], w[48], w[302], pars->GC_100, amp[2225]); 
  FFV1_0(w[333], w[2], w[123], pars->GC_3, amp[2226]); 
  FFV2_0(w[3], w[334], w[124], pars->GC_62, amp[2227]); 
  FFV2_4_0(w[333], w[2], w[124], pars->GC_50, pars->GC_59, amp[2228]); 
  VVV1_0(w[123], w[302], w[332], pars->GC_4, amp[2229]); 
  VVV1_0(w[302], w[332], w[124], pars->GC_53, amp[2230]); 
  FFV2_0(w[49], w[335], w[302], pars->GC_100, amp[2231]); 
  FFV2_0(w[198], w[133], w[302], pars->GC_100, amp[2232]); 
  FFV1_0(w[338], w[133], w[123], pars->GC_2, amp[2233]); 
  FFV2_0(w[170], w[133], w[302], pars->GC_100, amp[2234]); 
  FFV1_0(w[338], w[133], w[74], pars->GC_11, amp[2235]); 
  FFV2_0(w[199], w[133], w[302], pars->GC_100, amp[2236]); 
  FFV2_5_0(w[338], w[133], w[124], pars->GC_51, pars->GC_58, amp[2237]); 
  FFV2_0(w[137], w[2], w[217], pars->GC_100, amp[2238]); 
  FFV2_0(w[3], w[291], w[217], pars->GC_100, amp[2239]); 
  FFV2_0(w[140], w[2], w[217], pars->GC_100, amp[2240]); 
  VVV1_0(w[135], w[217], w[302], pars->GC_4, amp[2241]); 
  VVV1_0(w[217], w[302], w[138], pars->GC_53, amp[2242]); 
  FFV2_0(w[141], w[48], w[302], pars->GC_100, amp[2243]); 
  FFV2_0(w[49], w[265], w[302], pars->GC_100, amp[2244]); 
  FFV2_0(w[144], w[48], w[302], pars->GC_100, amp[2245]); 
  FFV2_0(w[49], w[145], w[302], pars->GC_100, amp[2246]); 
  FFV2_0(w[146], w[48], w[302], pars->GC_100, amp[2247]); 
  FFV2_0(w[49], w[267], w[302], pars->GC_100, amp[2248]); 
  FFV2_0(w[338], w[133], w[217], pars->GC_100, amp[2249]); 
  FFV1_0(w[3], w[334], w[123], pars->GC_3, amp[2250]); 
  FFV2_4_0(w[3], w[334], w[124], pars->GC_50, pars->GC_59, amp[2251]); 
  FFV2_0(w[333], w[2], w[124], pars->GC_62, amp[2252]); 
  VVV1_0(w[123], w[332], w[302], pars->GC_4, amp[2253]); 
  VVV1_0(w[332], w[302], w[124], pars->GC_53, amp[2254]); 
  FFV2_0(w[340], w[48], w[302], pars->GC_100, amp[2255]); 
  FFV2_0(w[274], w[133], w[302], pars->GC_100, amp[2256]); 
  FFV1_0(w[338], w[133], w[123], pars->GC_1, amp[2257]); 
  FFV2_0(w[170], w[133], w[302], pars->GC_100, amp[2258]); 
  FFV1_0(w[338], w[133], w[74], pars->GC_11, amp[2259]); 
  FFV2_0(w[275], w[133], w[302], pars->GC_100, amp[2260]); 
  FFV2_3_0(w[338], w[133], w[124], pars->GC_50, pars->GC_58, amp[2261]); 
  FFV1_0(w[3], w[339], w[183], pars->GC_3, amp[2262]); 
  FFV2_4_0(w[3], w[339], w[186], pars->GC_50, pars->GC_59, amp[2263]); 
  FFV2_0(w[270], w[2], w[186], pars->GC_62, amp[2264]); 
  VVV1_0(w[183], w[268], w[302], pars->GC_4, amp[2265]); 
  VVV1_0(w[268], w[302], w[186], pars->GC_53, amp[2266]); 
  FFV2_0(w[271], w[133], w[302], pars->GC_100, amp[2267]); 
  FFV2_0(w[341], w[48], w[302], pars->GC_100, amp[2268]); 
  FFV1_0(w[338], w[48], w[183], pars->GC_1, amp[2269]); 
  FFV2_0(w[167], w[48], w[302], pars->GC_100, amp[2270]); 
  FFV1_0(w[338], w[48], w[166], pars->GC_11, amp[2271]); 
  FFV2_0(w[342], w[48], w[302], pars->GC_100, amp[2272]); 
  FFV2_3_0(w[338], w[48], w[186], pars->GC_50, pars->GC_58, amp[2273]); 
  FFV2_0(w[206], w[2], w[205], pars->GC_100, amp[2274]); 
  VVV1_0(w[14], w[204], w[205], pars->GC_4, amp[2275]); 
  VVV1_0(w[204], w[205], w[17], pars->GC_53, amp[2276]); 
  FFV1_0(w[207], w[4], w[14], pars->GC_2, amp[2277]); 
  FFV1_0(w[1], w[208], w[14], pars->GC_1, amp[2278]); 
  FFV2_5_0(w[207], w[4], w[17], pars->GC_51, pars->GC_58, amp[2279]); 
  FFV2_3_0(w[1], w[208], w[17], pars->GC_50, pars->GC_58, amp[2280]); 
  FFV1_0(w[209], w[5], w[14], pars->GC_1, amp[2281]); 
  FFV2_0(w[39], w[5], w[205], pars->GC_100, amp[2282]); 
  FFV2_3_0(w[209], w[5], w[17], pars->GC_50, pars->GC_58, amp[2283]); 
  FFV2_0(w[40], w[5], w[205], pars->GC_100, amp[2284]); 
  FFV2_0(w[218], w[2], w[217], pars->GC_100, amp[2285]); 
  VVV1_0(w[14], w[216], w[217], pars->GC_4, amp[2286]); 
  VVV1_0(w[216], w[217], w[17], pars->GC_53, amp[2287]); 
  FFV1_0(w[219], w[48], w[14], pars->GC_2, amp[2288]); 
  FFV1_0(w[49], w[220], w[14], pars->GC_1, amp[2289]); 
  FFV2_5_0(w[219], w[48], w[17], pars->GC_51, pars->GC_58, amp[2290]); 
  FFV2_3_0(w[49], w[220], w[17], pars->GC_50, pars->GC_58, amp[2291]); 
  FFV1_0(w[221], w[4], w[14], pars->GC_1, amp[2292]); 
  FFV2_0(w[39], w[4], w[217], pars->GC_100, amp[2293]); 
  FFV2_3_0(w[221], w[4], w[17], pars->GC_50, pars->GC_58, amp[2294]); 
  FFV2_0(w[40], w[4], w[217], pars->GC_100, amp[2295]); 
  FFV2_0(w[230], w[2], w[229], pars->GC_100, amp[2296]); 
  VVV1_0(w[14], w[228], w[229], pars->GC_4, amp[2297]); 
  VVV1_0(w[228], w[229], w[17], pars->GC_53, amp[2298]); 
  FFV1_0(w[231], w[4], w[14], pars->GC_2, amp[2299]); 
  FFV1_0(w[49], w[232], w[14], pars->GC_1, amp[2300]); 
  FFV2_5_0(w[231], w[4], w[17], pars->GC_51, pars->GC_58, amp[2301]); 
  FFV2_3_0(w[49], w[232], w[17], pars->GC_50, pars->GC_58, amp[2302]); 
  FFV1_0(w[233], w[48], w[14], pars->GC_1, amp[2303]); 
  FFV2_0(w[39], w[48], w[229], pars->GC_100, amp[2304]); 
  FFV2_3_0(w[233], w[48], w[17], pars->GC_50, pars->GC_58, amp[2305]); 
  FFV2_0(w[40], w[48], w[229], pars->GC_100, amp[2306]); 
  FFV2_0(w[245], w[2], w[228], pars->GC_100, amp[2307]); 
  VVV1_0(w[14], w[229], w[228], pars->GC_4, amp[2308]); 
  VVV1_0(w[229], w[228], w[17], pars->GC_53, amp[2309]); 
  FFV1_0(w[233], w[48], w[14], pars->GC_2, amp[2310]); 
  FFV1_0(w[0], w[246], w[14], pars->GC_1, amp[2311]); 
  FFV2_5_0(w[233], w[48], w[17], pars->GC_51, pars->GC_58, amp[2312]); 
  FFV2_3_0(w[0], w[246], w[17], pars->GC_50, pars->GC_58, amp[2313]); 
  FFV1_0(w[231], w[4], w[14], pars->GC_1, amp[2314]); 
  FFV2_0(w[247], w[4], w[228], pars->GC_100, amp[2315]); 
  FFV2_3_0(w[231], w[4], w[17], pars->GC_50, pars->GC_58, amp[2316]); 
  FFV2_0(w[248], w[4], w[228], pars->GC_100, amp[2317]); 
  FFV2_0(w[260], w[2], w[216], pars->GC_100, amp[2318]); 
  VVV1_0(w[14], w[217], w[216], pars->GC_4, amp[2319]); 
  VVV1_0(w[217], w[216], w[17], pars->GC_53, amp[2320]); 
  FFV1_0(w[221], w[4], w[14], pars->GC_2, amp[2321]); 
  FFV1_0(w[0], w[261], w[14], pars->GC_1, amp[2322]); 
  FFV2_5_0(w[221], w[4], w[17], pars->GC_51, pars->GC_58, amp[2323]); 
  FFV2_3_0(w[0], w[261], w[17], pars->GC_50, pars->GC_58, amp[2324]); 
  FFV1_0(w[219], w[48], w[14], pars->GC_1, amp[2325]); 
  FFV2_0(w[247], w[48], w[216], pars->GC_100, amp[2326]); 
  FFV2_3_0(w[219], w[48], w[17], pars->GC_50, pars->GC_58, amp[2327]); 
  FFV2_0(w[248], w[48], w[216], pars->GC_100, amp[2328]); 
  FFV2_0(w[270], w[2], w[269], pars->GC_100, amp[2329]); 
  VVV1_0(w[14], w[268], w[269], pars->GC_4, amp[2330]); 
  VVV1_0(w[268], w[269], w[17], pars->GC_53, amp[2331]); 
  FFV1_0(w[271], w[133], w[14], pars->GC_2, amp[2332]); 
  FFV1_0(w[49], w[272], w[14], pars->GC_1, amp[2333]); 
  FFV2_5_0(w[271], w[133], w[17], pars->GC_51, pars->GC_58, amp[2334]); 
  FFV2_3_0(w[49], w[272], w[17], pars->GC_50, pars->GC_58, amp[2335]); 
  FFV1_0(w[273], w[48], w[14], pars->GC_1, amp[2336]); 
  FFV2_0(w[164], w[48], w[269], pars->GC_100, amp[2337]); 
  FFV2_3_0(w[273], w[48], w[17], pars->GC_50, pars->GC_58, amp[2338]); 
  FFV2_0(w[165], w[48], w[269], pars->GC_100, amp[2339]); 
  FFV2_0(w[3], w[303], w[205], pars->GC_100, amp[2340]); 
  VVV1_0(w[204], w[205], w[278], pars->GC_53, amp[2341]); 
  FFV2_5_0(w[207], w[4], w[278], pars->GC_51, pars->GC_58, amp[2342]); 
  FFV2_3_0(w[1], w[208], w[278], pars->GC_50, pars->GC_58, amp[2343]); 
  FFV2_3_0(w[209], w[5], w[278], pars->GC_50, pars->GC_58, amp[2344]); 
  FFV2_0(w[281], w[5], w[205], pars->GC_100, amp[2345]); 
  FFV2_0(w[3], w[308], w[217], pars->GC_100, amp[2346]); 
  VVV1_0(w[216], w[217], w[278], pars->GC_53, amp[2347]); 
  FFV2_5_0(w[219], w[48], w[278], pars->GC_51, pars->GC_58, amp[2348]); 
  FFV2_3_0(w[49], w[220], w[278], pars->GC_50, pars->GC_58, amp[2349]); 
  FFV2_3_0(w[221], w[4], w[278], pars->GC_50, pars->GC_58, amp[2350]); 
  FFV2_0(w[281], w[4], w[217], pars->GC_100, amp[2351]); 
  FFV2_0(w[3], w[312], w[229], pars->GC_100, amp[2352]); 
  VVV1_0(w[228], w[229], w[278], pars->GC_53, amp[2353]); 
  FFV2_5_0(w[231], w[4], w[278], pars->GC_51, pars->GC_58, amp[2354]); 
  FFV2_3_0(w[49], w[232], w[278], pars->GC_50, pars->GC_58, amp[2355]); 
  FFV2_3_0(w[233], w[48], w[278], pars->GC_50, pars->GC_58, amp[2356]); 
  FFV2_0(w[281], w[48], w[229], pars->GC_100, amp[2357]); 
  FFV2_0(w[3], w[327], w[228], pars->GC_100, amp[2358]); 
  VVV1_0(w[229], w[228], w[278], pars->GC_53, amp[2359]); 
  FFV2_5_0(w[233], w[48], w[278], pars->GC_51, pars->GC_58, amp[2360]); 
  FFV2_3_0(w[0], w[246], w[278], pars->GC_50, pars->GC_58, amp[2361]); 
  FFV2_3_0(w[231], w[4], w[278], pars->GC_50, pars->GC_58, amp[2362]); 
  FFV2_0(w[344], w[4], w[228], pars->GC_100, amp[2363]); 
  FFV2_0(w[3], w[326], w[216], pars->GC_100, amp[2364]); 
  VVV1_0(w[217], w[216], w[278], pars->GC_53, amp[2365]); 
  FFV2_5_0(w[221], w[4], w[278], pars->GC_51, pars->GC_58, amp[2366]); 
  FFV2_3_0(w[0], w[261], w[278], pars->GC_50, pars->GC_58, amp[2367]); 
  FFV2_3_0(w[219], w[48], w[278], pars->GC_50, pars->GC_58, amp[2368]); 
  FFV2_0(w[344], w[48], w[216], pars->GC_100, amp[2369]); 
  FFV2_0(w[3], w[339], w[269], pars->GC_100, amp[2370]); 
  VVV1_0(w[268], w[269], w[278], pars->GC_53, amp[2371]); 
  FFV2_5_0(w[271], w[133], w[278], pars->GC_51, pars->GC_58, amp[2372]); 
  FFV2_3_0(w[49], w[272], w[278], pars->GC_50, pars->GC_58, amp[2373]); 
  FFV2_3_0(w[273], w[48], w[278], pars->GC_50, pars->GC_58, amp[2374]); 
  FFV2_0(w[295], w[48], w[269], pars->GC_100, amp[2375]); 


}
double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uu_emepuu() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[0] + amp[1] + amp[2] + amp[3] + amp[4] + amp[5] + amp[6] +
      amp[7] + amp[8] + amp[9] + amp[10] + amp[11] - 1./6. * amp[12] - 1./6. *
      amp[13] - 1./6. * amp[14] - 1./6. * amp[15] + amp[16] + amp[17] + amp[18]
      + amp[19] - 1./2. * amp[32] - 1./2. * amp[33] - 1./2. * amp[34] - 1./2. *
      amp[35] - 1./2. * amp[44] - 1./2. * amp[45] - 1./2. * amp[46] - 1./2. *
      amp[47] + amp[52] + amp[53] + amp[54] + amp[55] - 1./6. * amp[56] - 1./6.
      * amp[57] - 1./6. * amp[58] - 1./6. * amp[59] + amp[60] + amp[61] +
      amp[62] + amp[63];
  jamp[1] = +1./2. * amp[12] + 1./2. * amp[13] + 1./2. * amp[14] + 1./2. *
      amp[15] - amp[20] - amp[21] - amp[22] - amp[23] - amp[24] - amp[25] -
      amp[26] - amp[27] - amp[28] - amp[29] - amp[30] - amp[31] + 1./6. *
      amp[32] + 1./6. * amp[33] + 1./6. * amp[34] + 1./6. * amp[35] - amp[36] -
      amp[37] - amp[38] - amp[39] - amp[40] - amp[41] - amp[42] - amp[43] +
      1./6. * amp[44] + 1./6. * amp[45] + 1./6. * amp[46] + 1./6. * amp[47] -
      amp[48] - amp[49] - amp[50] - amp[51] + 1./2. * amp[56] + 1./2. * amp[57]
      + 1./2. * amp[58] + 1./2. * amp[59];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[0][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emepuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[64] + amp[65] + amp[66] + amp[67] + amp[68] + amp[69] +
      amp[70] + amp[71] + amp[72] + amp[73] + amp[74] + amp[75] - 1./6. *
      amp[76] - 1./6. * amp[77] - 1./6. * amp[78] - 1./6. * amp[79] + amp[80] +
      amp[81] + amp[82] + amp[83] - 1./2. * amp[96] - 1./2. * amp[97] - 1./2. *
      amp[98] - 1./2. * amp[99] - 1./2. * amp[108] - 1./2. * amp[109] - 1./2. *
      amp[110] - 1./2. * amp[111] + amp[116] + amp[117] + amp[118] + amp[119] -
      1./6. * amp[120] - 1./6. * amp[121] - 1./6. * amp[122] - 1./6. * amp[123]
      + amp[124] + amp[125] + amp[126] + amp[127];
  jamp[1] = +1./2. * amp[76] + 1./2. * amp[77] + 1./2. * amp[78] + 1./2. *
      amp[79] - amp[84] - amp[85] - amp[86] - amp[87] - amp[88] - amp[89] -
      amp[90] - amp[91] - amp[92] - amp[93] - amp[94] - amp[95] + 1./6. *
      amp[96] + 1./6. * amp[97] + 1./6. * amp[98] + 1./6. * amp[99] - amp[100]
      - amp[101] - amp[102] - amp[103] - amp[104] - amp[105] - amp[106] -
      amp[107] + 1./6. * amp[108] + 1./6. * amp[109] + 1./6. * amp[110] + 1./6.
      * amp[111] - amp[112] - amp[113] - amp[114] - amp[115] + 1./2. * amp[120]
      + 1./2. * amp[121] + 1./2. * amp[122] + 1./2. * amp[123];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[1][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dd_emepdd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[128] + amp[129] + amp[130] + amp[131] + amp[132] + amp[133] +
      amp[134] + amp[135] + amp[136] + amp[137] + amp[138] + amp[139] - 1./6. *
      amp[140] - 1./6. * amp[141] - 1./6. * amp[142] - 1./6. * amp[143] +
      amp[144] + amp[145] + amp[146] + amp[147] - 1./2. * amp[160] - 1./2. *
      amp[161] - 1./2. * amp[162] - 1./2. * amp[163] - 1./2. * amp[172] - 1./2.
      * amp[173] - 1./2. * amp[174] - 1./2. * amp[175] + amp[180] + amp[181] +
      amp[182] + amp[183] - 1./6. * amp[184] - 1./6. * amp[185] - 1./6. *
      amp[186] - 1./6. * amp[187] + amp[188] + amp[189] + amp[190] + amp[191];
  jamp[1] = +1./2. * amp[140] + 1./2. * amp[141] + 1./2. * amp[142] + 1./2. *
      amp[143] - amp[148] - amp[149] - amp[150] - amp[151] - amp[152] -
      amp[153] - amp[154] - amp[155] - amp[156] - amp[157] - amp[158] -
      amp[159] + 1./6. * amp[160] + 1./6. * amp[161] + 1./6. * amp[162] + 1./6.
      * amp[163] - amp[164] - amp[165] - amp[166] - amp[167] - amp[168] -
      amp[169] - amp[170] - amp[171] + 1./6. * amp[172] + 1./6. * amp[173] +
      1./6. * amp[174] + 1./6. * amp[175] - amp[176] - amp[177] - amp[178] -
      amp[179] + 1./2. * amp[184] + 1./2. * amp[185] + 1./2. * amp[186] + 1./2.
      * amp[187];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[2][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emepddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[192] + amp[193] + amp[194] + amp[195] + amp[196] + amp[197] +
      amp[198] + amp[199] + amp[200] + amp[201] + amp[202] + amp[203] - 1./6. *
      amp[204] - 1./6. * amp[205] - 1./6. * amp[206] - 1./6. * amp[207] +
      amp[208] + amp[209] + amp[210] + amp[211] - 1./2. * amp[224] - 1./2. *
      amp[225] - 1./2. * amp[226] - 1./2. * amp[227] - 1./2. * amp[236] - 1./2.
      * amp[237] - 1./2. * amp[238] - 1./2. * amp[239] + amp[244] + amp[245] +
      amp[246] + amp[247] - 1./6. * amp[248] - 1./6. * amp[249] - 1./6. *
      amp[250] - 1./6. * amp[251] + amp[252] + amp[253] + amp[254] + amp[255];
  jamp[1] = +1./2. * amp[204] + 1./2. * amp[205] + 1./2. * amp[206] + 1./2. *
      amp[207] - amp[212] - amp[213] - amp[214] - amp[215] - amp[216] -
      amp[217] - amp[218] - amp[219] - amp[220] - amp[221] - amp[222] -
      amp[223] + 1./6. * amp[224] + 1./6. * amp[225] + 1./6. * amp[226] + 1./6.
      * amp[227] - amp[228] - amp[229] - amp[230] - amp[231] - amp[232] -
      amp[233] - amp[234] - amp[235] + 1./6. * amp[236] + 1./6. * amp[237] +
      1./6. * amp[238] + 1./6. * amp[239] - amp[240] - amp[241] - amp[242] -
      amp[243] + 1./2. * amp[248] + 1./2. * amp[249] + 1./2. * amp[250] + 1./2.
      * amp[251];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[3][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxux_emepuxux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[256] + amp[257] + amp[258] + amp[259] + amp[260] + amp[261] +
      amp[262] + amp[263] + amp[264] + amp[265] + amp[266] + amp[267] - 1./6. *
      amp[268] - 1./6. * amp[269] - 1./6. * amp[270] - 1./6. * amp[271] +
      amp[272] + amp[273] + amp[274] + amp[275] - 1./2. * amp[288] - 1./2. *
      amp[289] - 1./2. * amp[290] - 1./2. * amp[291] - 1./2. * amp[300] - 1./2.
      * amp[301] - 1./2. * amp[302] - 1./2. * amp[303] + amp[308] + amp[309] +
      amp[310] + amp[311] - 1./6. * amp[312] - 1./6. * amp[313] - 1./6. *
      amp[314] - 1./6. * amp[315] + amp[316] + amp[317] + amp[318] + amp[319];
  jamp[1] = +1./2. * amp[268] + 1./2. * amp[269] + 1./2. * amp[270] + 1./2. *
      amp[271] - amp[276] - amp[277] - amp[278] - amp[279] - amp[280] -
      amp[281] - amp[282] - amp[283] - amp[284] - amp[285] - amp[286] -
      amp[287] + 1./6. * amp[288] + 1./6. * amp[289] + 1./6. * amp[290] + 1./6.
      * amp[291] - amp[292] - amp[293] - amp[294] - amp[295] - amp[296] -
      amp[297] - amp[298] - amp[299] + 1./6. * amp[300] + 1./6. * amp[301] +
      1./6. * amp[302] + 1./6. * amp[303] - amp[304] - amp[305] - amp[306] -
      amp[307] + 1./2. * amp[312] + 1./2. * amp[313] + 1./2. * amp[314] + 1./2.
      * amp[315];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[4][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxdx_emepdxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 64;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[320] + amp[321] + amp[322] + amp[323] + amp[324] + amp[325] +
      amp[326] + amp[327] + amp[328] + amp[329] + amp[330] + amp[331] - 1./6. *
      amp[332] - 1./6. * amp[333] - 1./6. * amp[334] - 1./6. * amp[335] +
      amp[336] + amp[337] + amp[338] + amp[339] - 1./2. * amp[352] - 1./2. *
      amp[353] - 1./2. * amp[354] - 1./2. * amp[355] - 1./2. * amp[364] - 1./2.
      * amp[365] - 1./2. * amp[366] - 1./2. * amp[367] + amp[372] + amp[373] +
      amp[374] + amp[375] - 1./6. * amp[376] - 1./6. * amp[377] - 1./6. *
      amp[378] - 1./6. * amp[379] + amp[380] + amp[381] + amp[382] + amp[383];
  jamp[1] = +1./2. * amp[332] + 1./2. * amp[333] + 1./2. * amp[334] + 1./2. *
      amp[335] - amp[340] - amp[341] - amp[342] - amp[343] - amp[344] -
      amp[345] - amp[346] - amp[347] - amp[348] - amp[349] - amp[350] -
      amp[351] + 1./6. * amp[352] + 1./6. * amp[353] + 1./6. * amp[354] + 1./6.
      * amp[355] - amp[356] - amp[357] - amp[358] - amp[359] - amp[360] -
      amp[361] - amp[362] - amp[363] + 1./6. * amp[364] + 1./6. * amp[365] +
      1./6. * amp[366] + 1./6. * amp[367] - amp[368] - amp[369] - amp[370] -
      amp[371] + 1./2. * amp[376] + 1./2. * amp[377] + 1./2. * amp[378] + 1./2.
      * amp[379];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[5][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ud_emepud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[384] + amp[385] + amp[386] + amp[387] + amp[388] + amp[389] +
      amp[390] + amp[391] + amp[392] + amp[393] + amp[394] + amp[395] - 1./6. *
      amp[396] - 1./6. * amp[397] - 1./6. * amp[398] - 1./6. * amp[399] +
      amp[400] + amp[401] + amp[402] + amp[403] + amp[415] + amp[416] +
      amp[417] + amp[418] - 1./6. * amp[419] - 1./6. * amp[420] - 1./6. *
      amp[421] - 1./6. * amp[422] + amp[423] + amp[424] + amp[425] + amp[426];
  jamp[1] = +1./2. * amp[396] + 1./2. * amp[397] + 1./2. * amp[398] + 1./2. *
      amp[399] - amp[404] - amp[405] - amp[406] - amp[407] - amp[408] -
      amp[409] - amp[410] - amp[411] - amp[412] - amp[413] - amp[414] + 1./2. *
      amp[419] + 1./2. * amp[420] + 1./2. * amp[421] + 1./2. * amp[422];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[6][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emepddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[427] + amp[428] + amp[429] + amp[430] + amp[431] + amp[432] +
      amp[433] + amp[434] + amp[435] + amp[436] + amp[437] + amp[438] - 1./6. *
      amp[439] - 1./6. * amp[440] - 1./6. * amp[441] - 1./6. * amp[442] +
      amp[443] + amp[444] + amp[445] + amp[446] + amp[458] + amp[459] +
      amp[460] + amp[461] - 1./6. * amp[462] - 1./6. * amp[463] - 1./6. *
      amp[464] - 1./6. * amp[465] + amp[466] + amp[467] + amp[468] + amp[469];
  jamp[1] = +1./2. * amp[439] + 1./2. * amp[440] + 1./2. * amp[441] + 1./2. *
      amp[442] - amp[447] - amp[448] - amp[449] - amp[450] - amp[451] -
      amp[452] - amp[453] - amp[454] - amp[455] - amp[456] - amp[457] + 1./2. *
      amp[462] + 1./2. * amp[463] + 1./2. * amp[464] + 1./2. * amp[465];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[7][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_emepudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[482] - 1./2. * amp[483] - 1./2. * amp[484] - 1./2. *
      amp[485] + amp[490] + amp[491] + amp[492] + amp[493] + amp[494] +
      amp[495] + amp[496] + amp[497] + amp[498] + amp[499] + amp[500] - 1./2. *
      amp[505] - 1./2. * amp[506] - 1./2. * amp[507] - 1./2. * amp[508];
  jamp[1] = -amp[470] - amp[471] - amp[472] - amp[473] - amp[474] - amp[475] -
      amp[476] - amp[477] - amp[478] - amp[479] - amp[480] - amp[481] + 1./6. *
      amp[482] + 1./6. * amp[483] + 1./6. * amp[484] + 1./6. * amp[485] -
      amp[486] - amp[487] - amp[488] - amp[489] - amp[501] - amp[502] -
      amp[503] - amp[504] + 1./6. * amp[505] + 1./6. * amp[506] + 1./6. *
      amp[507] + 1./6. * amp[508] - amp[509] - amp[510] - amp[511] - amp[512];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[8][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emepdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[525] - 1./2. * amp[526] - 1./2. * amp[527] - 1./2. *
      amp[528] + amp[533] + amp[534] + amp[535] + amp[536] + amp[537] +
      amp[538] + amp[539] + amp[540] + amp[541] + amp[542] + amp[543] - 1./2. *
      amp[548] - 1./2. * amp[549] - 1./2. * amp[550] - 1./2. * amp[551];
  jamp[1] = -amp[513] - amp[514] - amp[515] - amp[516] - amp[517] - amp[518] -
      amp[519] - amp[520] - amp[521] - amp[522] - amp[523] - amp[524] + 1./6. *
      amp[525] + 1./6. * amp[526] + 1./6. * amp[527] + 1./6. * amp[528] -
      amp[529] - amp[530] - amp[531] - amp[532] - amp[544] - amp[545] -
      amp[546] - amp[547] + 1./6. * amp[548] + 1./6. * amp[549] + 1./6. *
      amp[550] + 1./6. * amp[551] - amp[552] - amp[553] - amp[554] - amp[555];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[9][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emepuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[556] + amp[557] + amp[558] + amp[559] + amp[560] + amp[561] +
      amp[562] + amp[563] + amp[564] + amp[565] + amp[566] + amp[567] - 1./6. *
      amp[568] - 1./6. * amp[569] - 1./6. * amp[570] - 1./6. * amp[571] +
      amp[572] + amp[573] + amp[574] + amp[575] + amp[587] + amp[588] +
      amp[589] + amp[590] - 1./6. * amp[591] - 1./6. * amp[592] - 1./6. *
      amp[593] - 1./6. * amp[594] + amp[595] + amp[596] + amp[597] + amp[598];
  jamp[1] = +1./2. * amp[568] + 1./2. * amp[569] + 1./2. * amp[570] + 1./2. *
      amp[571] - amp[576] - amp[577] - amp[578] - amp[579] - amp[580] -
      amp[581] - amp[582] - amp[583] - amp[584] - amp[585] - amp[586] + 1./2. *
      amp[591] + 1./2. * amp[592] + 1./2. * amp[593] + 1./2. * amp[594];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[10][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxdx_emepuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 43;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[599] + amp[600] + amp[601] + amp[602] + amp[603] + amp[604] +
      amp[605] + amp[606] + amp[607] + amp[608] + amp[609] + amp[610] - 1./6. *
      amp[611] - 1./6. * amp[612] - 1./6. * amp[613] - 1./6. * amp[614] +
      amp[615] + amp[616] + amp[617] + amp[618] + amp[630] + amp[631] +
      amp[632] + amp[633] - 1./6. * amp[634] - 1./6. * amp[635] - 1./6. *
      amp[636] - 1./6. * amp[637] + amp[638] + amp[639] + amp[640] + amp[641];
  jamp[1] = +1./2. * amp[611] + 1./2. * amp[612] + 1./2. * amp[613] + 1./2. *
      amp[614] - amp[619] - amp[620] - amp[621] - amp[622] - amp[623] -
      amp[624] - amp[625] - amp[626] - amp[627] - amp[628] - amp[629] + 1./2. *
      amp[634] + 1./2. * amp[635] + 1./2. * amp[636] + 1./2. * amp[637];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[11][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uc_emepuc() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[0] + amp[1] + amp[2] + amp[3] + amp[4] + amp[5] + amp[6] +
      amp[7] + amp[8] + amp[9] + amp[10] + amp[11] - 1./6. * amp[12] - 1./6. *
      amp[13] - 1./6. * amp[14] - 1./6. * amp[15] + amp[16] + amp[17] + amp[18]
      + amp[19] + amp[642] + amp[643] + amp[644] + amp[645] - 1./6. * amp[646]
      - 1./6. * amp[647] - 1./6. * amp[648] - 1./6. * amp[649] + amp[650] +
      amp[651] + amp[652] + amp[653];
  jamp[1] = +1./2. * (+amp[12] + amp[13] + amp[14] + amp[15] + amp[646] +
      amp[647] + amp[648] + amp[649]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[12][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_emepus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[654] + amp[655] + amp[656] + amp[657] + amp[658] + amp[659] +
      amp[660] + amp[661] + amp[662] + amp[663] + amp[664] + amp[665] - 1./6. *
      amp[666] - 1./6. * amp[667] - 1./6. * amp[668] - 1./6. * amp[669] +
      amp[670] + amp[671] + amp[672] + amp[673] + amp[674] + amp[675] +
      amp[676] + amp[677] - 1./6. * amp[678] - 1./6. * amp[679] - 1./6. *
      amp[680] - 1./6. * amp[681] + amp[682] + amp[683] + amp[684] + amp[685];
  jamp[1] = +1./2. * (+amp[666] + amp[667] + amp[668] + amp[669] + amp[678] +
      amp[679] + amp[680] + amp[681]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[13][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emepccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[686] + amp[687] + amp[688] + amp[689] + amp[690] + amp[691] +
      amp[692] + amp[693] + amp[694] + amp[695] + amp[696] + amp[697] - 1./6. *
      amp[698] - 1./6. * amp[699] - 1./6. * amp[700] - 1./6. * amp[701] +
      amp[702] + amp[703] + amp[704] + amp[705] + amp[706] + amp[707] +
      amp[708] + amp[709] - 1./6. * amp[710] - 1./6. * amp[711] - 1./6. *
      amp[712] - 1./6. * amp[713] + amp[714] + amp[715] + amp[716] + amp[717];
  jamp[1] = +1./2. * (+amp[698] + amp[699] + amp[700] + amp[701] + amp[710] +
      amp[711] + amp[712] + amp[713]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[14][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emepssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[718] + amp[719] + amp[720] + amp[721] + amp[722] + amp[723] +
      amp[724] + amp[725] + amp[726] + amp[727] + amp[728] + amp[729] - 1./6. *
      amp[730] - 1./6. * amp[731] - 1./6. * amp[732] - 1./6. * amp[733] +
      amp[734] + amp[735] + amp[736] + amp[737] + amp[738] + amp[739] +
      amp[740] + amp[741] - 1./6. * amp[742] - 1./6. * amp[743] - 1./6. *
      amp[744] - 1./6. * amp[745] + amp[746] + amp[747] + amp[748] + amp[749];
  jamp[1] = +1./2. * (+amp[730] + amp[731] + amp[732] + amp[733] + amp[742] +
      amp[743] + amp[744] + amp[745]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[15][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_emepucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[762] - amp[763] - amp[764] - amp[765] - amp[774] -
      amp[775] - amp[776] - amp[777]);
  jamp[1] = -amp[750] - amp[751] - amp[752] - amp[753] - amp[754] - amp[755] -
      amp[756] - amp[757] - amp[758] - amp[759] - amp[760] - amp[761] + 1./6. *
      amp[762] + 1./6. * amp[763] + 1./6. * amp[764] + 1./6. * amp[765] -
      amp[766] - amp[767] - amp[768] - amp[769] - amp[770] - amp[771] -
      amp[772] - amp[773] + 1./6. * amp[774] + 1./6. * amp[775] + 1./6. *
      amp[776] + 1./6. * amp[777] - amp[778] - amp[779] - amp[780] - amp[781];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[16][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_usx_emepusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[794] - amp[795] - amp[796] - amp[797] - amp[806] -
      amp[807] - amp[808] - amp[809]);
  jamp[1] = -amp[782] - amp[783] - amp[784] - amp[785] - amp[786] - amp[787] -
      amp[788] - amp[789] - amp[790] - amp[791] - amp[792] - amp[793] + 1./6. *
      amp[794] + 1./6. * amp[795] + 1./6. * amp[796] + 1./6. * amp[797] -
      amp[798] - amp[799] - amp[800] - amp[801] - amp[802] - amp[803] -
      amp[804] - amp[805] + 1./6. * amp[806] + 1./6. * amp[807] + 1./6. *
      amp[808] + 1./6. * amp[809] - amp[810] - amp[811] - amp[812] - amp[813];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[17][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ds_emepds() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[814] + amp[815] + amp[816] + amp[817] + amp[818] + amp[819] +
      amp[820] + amp[821] + amp[822] + amp[823] + amp[824] + amp[825] - 1./6. *
      amp[826] - 1./6. * amp[827] - 1./6. * amp[828] - 1./6. * amp[829] +
      amp[830] + amp[831] + amp[832] + amp[833] + amp[834] + amp[835] +
      amp[836] + amp[837] - 1./6. * amp[838] - 1./6. * amp[839] - 1./6. *
      amp[840] - 1./6. * amp[841] + amp[842] + amp[843] + amp[844] + amp[845];
  jamp[1] = +1./2. * (+amp[826] + amp[827] + amp[828] + amp[829] + amp[838] +
      amp[839] + amp[840] + amp[841]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[18][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dcx_emepdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[858] - amp[859] - amp[860] - amp[861] - amp[870] -
      amp[871] - amp[872] - amp[873]);
  jamp[1] = -amp[846] - amp[847] - amp[848] - amp[849] - amp[850] - amp[851] -
      amp[852] - amp[853] - amp[854] - amp[855] - amp[856] - amp[857] + 1./6. *
      amp[858] + 1./6. * amp[859] + 1./6. * amp[860] + 1./6. * amp[861] -
      amp[862] - amp[863] - amp[864] - amp[865] - amp[866] - amp[867] -
      amp[868] - amp[869] + 1./6. * amp[870] + 1./6. * amp[871] + 1./6. *
      amp[872] + 1./6. * amp[873] - amp[874] - amp[875] - amp[876] - amp[877];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[19][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emepccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[878] + amp[879] + amp[880] + amp[881] + amp[882] + amp[883] +
      amp[884] + amp[885] + amp[886] + amp[887] + amp[888] + amp[889] - 1./6. *
      amp[890] - 1./6. * amp[891] - 1./6. * amp[892] - 1./6. * amp[893] +
      amp[894] + amp[895] + amp[896] + amp[897] + amp[898] + amp[899] +
      amp[900] + amp[901] - 1./6. * amp[902] - 1./6. * amp[903] - 1./6. *
      amp[904] - 1./6. * amp[905] + amp[906] + amp[907] + amp[908] + amp[909];
  jamp[1] = +1./2. * (+amp[890] + amp[891] + amp[892] + amp[893] + amp[902] +
      amp[903] + amp[904] + amp[905]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[20][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emepssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[910] + amp[911] + amp[912] + amp[913] + amp[914] + amp[915] +
      amp[916] + amp[917] + amp[918] + amp[919] + amp[920] + amp[921] - 1./6. *
      amp[922] - 1./6. * amp[923] - 1./6. * amp[924] - 1./6. * amp[925] +
      amp[926] + amp[927] + amp[928] + amp[929] + amp[930] + amp[931] +
      amp[932] + amp[933] - 1./6. * amp[934] - 1./6. * amp[935] - 1./6. *
      amp[936] - 1./6. * amp[937] + amp[938] + amp[939] + amp[940] + amp[941];
  jamp[1] = +1./2. * (+amp[922] + amp[923] + amp[924] + amp[925] + amp[934] +
      amp[935] + amp[936] + amp[937]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[21][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_emepdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[954] - amp[955] - amp[956] - amp[957] - amp[966] -
      amp[967] - amp[968] - amp[969]);
  jamp[1] = -amp[942] - amp[943] - amp[944] - amp[945] - amp[946] - amp[947] -
      amp[948] - amp[949] - amp[950] - amp[951] - amp[952] - amp[953] + 1./6. *
      amp[954] + 1./6. * amp[955] + 1./6. * amp[956] + 1./6. * amp[957] -
      amp[958] - amp[959] - amp[960] - amp[961] - amp[962] - amp[963] -
      amp[964] - amp[965] + 1./6. * amp[966] + 1./6. * amp[967] + 1./6. *
      amp[968] + 1./6. * amp[969] - amp[970] - amp[971] - amp[972] - amp[973];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[22][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxcx_emepuxcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[974] + amp[975] + amp[976] + amp[977] + amp[978] + amp[979] +
      amp[980] + amp[981] + amp[982] + amp[983] + amp[984] + amp[985] - 1./6. *
      amp[986] - 1./6. * amp[987] - 1./6. * amp[988] - 1./6. * amp[989] +
      amp[990] + amp[991] + amp[992] + amp[993] + amp[994] + amp[995] +
      amp[996] + amp[997] - 1./6. * amp[998] - 1./6. * amp[999] - 1./6. *
      amp[1000] - 1./6. * amp[1001] + amp[1002] + amp[1003] + amp[1004] +
      amp[1005];
  jamp[1] = +1./2. * (+amp[986] + amp[987] + amp[988] + amp[989] + amp[998] +
      amp[999] + amp[1000] + amp[1001]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[23][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_emepuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1006] + amp[1007] + amp[1008] + amp[1009] + amp[1010] +
      amp[1011] + amp[1012] + amp[1013] + amp[1014] + amp[1015] + amp[1016] +
      amp[1017] - 1./6. * amp[1018] - 1./6. * amp[1019] - 1./6. * amp[1020] -
      1./6. * amp[1021] + amp[1022] + amp[1023] + amp[1024] + amp[1025] +
      amp[1026] + amp[1027] + amp[1028] + amp[1029] - 1./6. * amp[1030] - 1./6.
      * amp[1031] - 1./6. * amp[1032] - 1./6. * amp[1033] + amp[1034] +
      amp[1035] + amp[1036] + amp[1037];
  jamp[1] = +1./2. * (+amp[1018] + amp[1019] + amp[1020] + amp[1021] +
      amp[1030] + amp[1031] + amp[1032] + amp[1033]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[24][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxsx_emepdxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 32;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1038] + amp[1039] + amp[1040] + amp[1041] + amp[1042] +
      amp[1043] + amp[1044] + amp[1045] + amp[1046] + amp[1047] + amp[1048] +
      amp[1049] - 1./6. * amp[1050] - 1./6. * amp[1051] - 1./6. * amp[1052] -
      1./6. * amp[1053] + amp[1054] + amp[1055] + amp[1056] + amp[1057] +
      amp[1058] + amp[1059] + amp[1060] + amp[1061] - 1./6. * amp[1062] - 1./6.
      * amp[1063] - 1./6. * amp[1064] - 1./6. * amp[1065] + amp[1066] +
      amp[1067] + amp[1068] + amp[1069];
  jamp[1] = +1./2. * (+amp[1050] + amp[1051] + amp[1052] + amp[1053] +
      amp[1062] + amp[1063] + amp[1064] + amp[1065]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[25][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uu_vevexuu() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1070] + amp[1071] + amp[1072] + amp[1073] - 1./6. * amp[1074]
      - 1./6. * amp[1075] + amp[1076] + amp[1077] - 1./2. * amp[1082] - 1./2. *
      amp[1083] - 1./2. * amp[1088] - 1./2. * amp[1089] + amp[1092] + amp[1093]
      - 1./6. * amp[1094] - 1./6. * amp[1095] + amp[1096] + amp[1097];
  jamp[1] = +1./2. * amp[1074] + 1./2. * amp[1075] - amp[1078] - amp[1079] -
      amp[1080] - amp[1081] + 1./6. * amp[1082] + 1./6. * amp[1083] - amp[1084]
      - amp[1085] - amp[1086] - amp[1087] + 1./6. * amp[1088] + 1./6. *
      amp[1089] - amp[1090] - amp[1091] + 1./2. * amp[1094] + 1./2. * amp[1095];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[26][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_vevexuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1098] + amp[1099] + amp[1100] + amp[1101] - 1./6. * amp[1102]
      - 1./6. * amp[1103] + amp[1104] + amp[1105] - 1./2. * amp[1110] - 1./2. *
      amp[1111] - 1./2. * amp[1116] - 1./2. * amp[1117] + amp[1120] + amp[1121]
      - 1./6. * amp[1122] - 1./6. * amp[1123] + amp[1124] + amp[1125];
  jamp[1] = +1./2. * amp[1102] + 1./2. * amp[1103] - amp[1106] - amp[1107] -
      amp[1108] - amp[1109] + 1./6. * amp[1110] + 1./6. * amp[1111] - amp[1112]
      - amp[1113] - amp[1114] - amp[1115] + 1./6. * amp[1116] + 1./6. *
      amp[1117] - amp[1118] - amp[1119] + 1./2. * amp[1122] + 1./2. * amp[1123];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[27][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dd_vevexdd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1126] + amp[1127] + amp[1128] + amp[1129] - 1./6. * amp[1130]
      - 1./6. * amp[1131] + amp[1132] + amp[1133] - 1./2. * amp[1138] - 1./2. *
      amp[1139] - 1./2. * amp[1144] - 1./2. * amp[1145] + amp[1148] + amp[1149]
      - 1./6. * amp[1150] - 1./6. * amp[1151] + amp[1152] + amp[1153];
  jamp[1] = +1./2. * amp[1130] + 1./2. * amp[1131] - amp[1134] - amp[1135] -
      amp[1136] - amp[1137] + 1./6. * amp[1138] + 1./6. * amp[1139] - amp[1140]
      - amp[1141] - amp[1142] - amp[1143] + 1./6. * amp[1144] + 1./6. *
      amp[1145] - amp[1146] - amp[1147] + 1./2. * amp[1150] + 1./2. * amp[1151];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[28][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_vevexddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1154] + amp[1155] + amp[1156] + amp[1157] - 1./6. * amp[1158]
      - 1./6. * amp[1159] + amp[1160] + amp[1161] - 1./2. * amp[1166] - 1./2. *
      amp[1167] - 1./2. * amp[1172] - 1./2. * amp[1173] + amp[1176] + amp[1177]
      - 1./6. * amp[1178] - 1./6. * amp[1179] + amp[1180] + amp[1181];
  jamp[1] = +1./2. * amp[1158] + 1./2. * amp[1159] - amp[1162] - amp[1163] -
      amp[1164] - amp[1165] + 1./6. * amp[1166] + 1./6. * amp[1167] - amp[1168]
      - amp[1169] - amp[1170] - amp[1171] + 1./6. * amp[1172] + 1./6. *
      amp[1173] - amp[1174] - amp[1175] + 1./2. * amp[1178] + 1./2. * amp[1179];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[29][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxux_vevexuxux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1182] + amp[1183] + amp[1184] + amp[1185] - 1./6. * amp[1186]
      - 1./6. * amp[1187] + amp[1188] + amp[1189] - 1./2. * amp[1194] - 1./2. *
      amp[1195] - 1./2. * amp[1200] - 1./2. * amp[1201] + amp[1204] + amp[1205]
      - 1./6. * amp[1206] - 1./6. * amp[1207] + amp[1208] + amp[1209];
  jamp[1] = +1./2. * amp[1186] + 1./2. * amp[1187] - amp[1190] - amp[1191] -
      amp[1192] - amp[1193] + 1./6. * amp[1194] + 1./6. * amp[1195] - amp[1196]
      - amp[1197] - amp[1198] - amp[1199] + 1./6. * amp[1200] + 1./6. *
      amp[1201] - amp[1202] - amp[1203] + 1./2. * amp[1206] + 1./2. * amp[1207];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[30][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxdx_vevexdxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 28;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1210] + amp[1211] + amp[1212] + amp[1213] - 1./6. * amp[1214]
      - 1./6. * amp[1215] + amp[1216] + amp[1217] - 1./2. * amp[1222] - 1./2. *
      amp[1223] - 1./2. * amp[1228] - 1./2. * amp[1229] + amp[1232] + amp[1233]
      - 1./6. * amp[1234] - 1./6. * amp[1235] + amp[1236] + amp[1237];
  jamp[1] = +1./2. * amp[1214] + 1./2. * amp[1215] - amp[1218] - amp[1219] -
      amp[1220] - amp[1221] + 1./6. * amp[1222] + 1./6. * amp[1223] - amp[1224]
      - amp[1225] - amp[1226] - amp[1227] + 1./6. * amp[1228] + 1./6. *
      amp[1229] - amp[1230] - amp[1231] + 1./2. * amp[1234] + 1./2. * amp[1235];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[31][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uu_veepud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1238] + amp[1239] + amp[1240] + amp[1241] + amp[1242] +
      amp[1243] + amp[1244] - 1./6. * amp[1245] - 1./6. * amp[1246] + amp[1247]
      + amp[1248] - 1./2. * amp[1257] - 1./2. * amp[1258] + amp[1261];
  jamp[1] = +1./2. * amp[1245] + 1./2. * amp[1246] - amp[1249] - amp[1250] -
      amp[1251] - amp[1252] - amp[1253] - amp[1254] - amp[1255] - amp[1256] +
      1./6. * amp[1257] + 1./6. * amp[1258] - amp[1259] - amp[1260];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[32][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ud_emvexuu() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1262] + amp[1263] + amp[1264] + amp[1265] + amp[1266] +
      amp[1267] + amp[1268] - 1./6. * amp[1269] - 1./6. * amp[1270] + amp[1271]
      + amp[1272] - 1./2. * amp[1280] - 1./2. * amp[1281] + amp[1285];
  jamp[1] = +1./2. * amp[1269] + 1./2. * amp[1270] - amp[1273] - amp[1274] -
      amp[1275] - amp[1276] - amp[1277] - amp[1278] - amp[1279] + 1./6. *
      amp[1280] + 1./6. * amp[1281] - amp[1282] - amp[1283] - amp[1284];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[33][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ud_veepdd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1286] + amp[1287] + amp[1288] + amp[1289] + amp[1290] +
      amp[1291] - 1./2. * amp[1300] - 1./2. * amp[1301] + amp[1304] + amp[1305]
      - 1./6. * amp[1306] - 1./6. * amp[1307] + amp[1308] + amp[1309];
  jamp[1] = -amp[1292] - amp[1293] - amp[1294] - amp[1295] - amp[1296] -
      amp[1297] - amp[1298] - amp[1299] + 1./6. * amp[1300] + 1./6. * amp[1301]
      - amp[1302] - amp[1303] + 1./2. * amp[1306] + 1./2. * amp[1307];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[34][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emvexudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1310] + amp[1311] + amp[1312] + amp[1313] + amp[1314] +
      amp[1315] + amp[1316] - 1./6. * amp[1317] - 1./6. * amp[1318] + amp[1319]
      + amp[1320] - 1./2. * amp[1328] - 1./2. * amp[1329] + amp[1333];
  jamp[1] = +1./2. * amp[1317] + 1./2. * amp[1318] - amp[1321] - amp[1322] -
      amp[1323] - amp[1324] - amp[1325] - amp[1326] - amp[1327] + 1./6. *
      amp[1328] + 1./6. * amp[1329] - amp[1330] - amp[1331] - amp[1332];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[35][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_veepdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1334] + amp[1335] + amp[1336] + amp[1337] + amp[1338] +
      amp[1339] + amp[1340] - 1./6. * amp[1341] - 1./6. * amp[1342] + amp[1343]
      + amp[1344] - 1./2. * amp[1353] - 1./2. * amp[1354] + amp[1357];
  jamp[1] = +1./2. * amp[1341] + 1./2. * amp[1342] - amp[1345] - amp[1346] -
      amp[1347] - amp[1348] - amp[1349] - amp[1350] - amp[1351] - amp[1352] +
      1./6. * amp[1353] + 1./6. * amp[1354] - amp[1355] - amp[1356];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[36][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_veepuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[1365] - 1./2. * amp[1366] + amp[1369] + amp[1370] +
      amp[1371] + amp[1372] + amp[1373] + amp[1374] + amp[1375] + amp[1376] -
      1./6. * amp[1377] - 1./6. * amp[1378] + amp[1379] + amp[1380];
  jamp[1] = -amp[1358] - amp[1359] - amp[1360] - amp[1361] - amp[1362] -
      amp[1363] - amp[1364] + 1./6. * amp[1365] + 1./6. * amp[1366] - amp[1367]
      - amp[1368] + 1./2. * amp[1377] + 1./2. * amp[1378] - amp[1381];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[37][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_veepddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1382] + amp[1383] + amp[1384] + amp[1385] + amp[1386] +
      amp[1387] - 1./2. * amp[1396] - 1./2. * amp[1397] + amp[1400] + amp[1401]
      - 1./6. * amp[1402] - 1./6. * amp[1403] + amp[1404] + amp[1405];
  jamp[1] = -amp[1388] - amp[1389] - amp[1390] - amp[1391] - amp[1392] -
      amp[1393] - amp[1394] - amp[1395] + 1./6. * amp[1396] + 1./6. * amp[1397]
      - amp[1398] - amp[1399] + 1./2. * amp[1402] + 1./2. * amp[1403];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[38][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dd_emvexud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1406] + amp[1407] + amp[1408] + amp[1409] + amp[1410] +
      amp[1411] - 1./2. * amp[1419] - 1./2. * amp[1420] + amp[1424] + amp[1425]
      - 1./6. * amp[1426] - 1./6. * amp[1427] + amp[1428] + amp[1429];
  jamp[1] = -amp[1412] - amp[1413] - amp[1414] - amp[1415] - amp[1416] -
      amp[1417] - amp[1418] + 1./6. * amp[1419] + 1./6. * amp[1420] - amp[1421]
      - amp[1422] - amp[1423] + 1./2. * amp[1426] + 1./2. * amp[1427];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[39][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emvexuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[1437] - 1./2. * amp[1438] + amp[1441] + amp[1442] +
      amp[1443] + amp[1444] + amp[1445] + amp[1446] + amp[1447] - 1./6. *
      amp[1448] - 1./6. * amp[1449] + amp[1450] + amp[1451] + amp[1452];
  jamp[1] = -amp[1430] - amp[1431] - amp[1432] - amp[1433] - amp[1434] -
      amp[1435] - amp[1436] + 1./6. * amp[1437] + 1./6. * amp[1438] - amp[1439]
      - amp[1440] + 1./2. * amp[1448] + 1./2. * amp[1449] - amp[1453];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[40][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emvexddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1454] + amp[1455] + amp[1456] + amp[1457] + amp[1458] +
      amp[1459] - 1./2. * amp[1467] - 1./2. * amp[1468] + amp[1472] + amp[1473]
      - 1./6. * amp[1474] - 1./6. * amp[1475] + amp[1476] + amp[1477];
  jamp[1] = -amp[1460] - amp[1461] - amp[1462] - amp[1463] - amp[1464] -
      amp[1465] - amp[1466] + 1./6. * amp[1467] + 1./6. * amp[1468] - amp[1469]
      - amp[1470] - amp[1471] + 1./2. * amp[1474] + 1./2. * amp[1475];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[41][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emvexudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1484] + amp[1485] + amp[1486] + amp[1487] + amp[1488] +
      amp[1489] + amp[1490] - 1./6. * amp[1491] - 1./6. * amp[1492] + amp[1493]
      + amp[1494] + amp[1495] - 1./2. * amp[1498] - 1./2. * amp[1499];
  jamp[1] = -amp[1478] - amp[1479] - amp[1480] - amp[1481] - amp[1482] -
      amp[1483] + 1./2. * amp[1491] + 1./2. * amp[1492] - amp[1496] - amp[1497]
      + 1./6. * amp[1498] + 1./6. * amp[1499] - amp[1500] - amp[1501];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[42][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_veepdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1508] + amp[1509] + amp[1510] + amp[1511] + amp[1512] +
      amp[1513] + amp[1514] + amp[1515] - 1./6. * amp[1516] - 1./6. * amp[1517]
      + amp[1518] + amp[1519] - 1./2. * amp[1522] - 1./2. * amp[1523];
  jamp[1] = -amp[1502] - amp[1503] - amp[1504] - amp[1505] - amp[1506] -
      amp[1507] + 1./2. * amp[1516] + 1./2. * amp[1517] - amp[1520] - amp[1521]
      + 1./6. * amp[1522] + 1./6. * amp[1523] - amp[1524] - amp[1525];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[43][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxux_emvexuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1526] + amp[1527] + amp[1528] + amp[1529] + amp[1530] +
      amp[1531] + amp[1532] - 1./6. * amp[1533] - 1./6. * amp[1534] + amp[1535]
      + amp[1536] - 1./2. * amp[1544] - 1./2. * amp[1545] + amp[1549];
  jamp[1] = +1./2. * amp[1533] + 1./2. * amp[1534] - amp[1537] - amp[1538] -
      amp[1539] - amp[1540] - amp[1541] - amp[1542] - amp[1543] + 1./6. *
      amp[1544] + 1./6. * amp[1545] - amp[1546] - amp[1547] - amp[1548];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[44][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxdx_emvexdxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1550] + amp[1551] + amp[1552] + amp[1553] + amp[1554] +
      amp[1555] - 1./2. * amp[1563] - 1./2. * amp[1564] + amp[1568] + amp[1569]
      - 1./6. * amp[1570] - 1./6. * amp[1571] + amp[1572] + amp[1573];
  jamp[1] = -amp[1556] - amp[1557] - amp[1558] - amp[1559] - amp[1560] -
      amp[1561] - amp[1562] + 1./6. * amp[1563] + 1./6. * amp[1564] - amp[1565]
      - amp[1566] - amp[1567] + 1./2. * amp[1570] + 1./2. * amp[1571];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[45][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxdx_veepuxux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1574] + amp[1575] + amp[1576] + amp[1577] + amp[1578] +
      amp[1579] + amp[1580] - 1./6. * amp[1581] - 1./6. * amp[1582] + amp[1583]
      + amp[1584] - 1./2. * amp[1593] - 1./2. * amp[1594] + amp[1597];
  jamp[1] = +1./2. * amp[1581] + 1./2. * amp[1582] - amp[1585] - amp[1586] -
      amp[1587] - amp[1588] - amp[1589] - amp[1590] - amp[1591] - amp[1592] +
      1./6. * amp[1593] + 1./6. * amp[1594] - amp[1595] - amp[1596];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[46][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxdx_veepuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 24;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1598] + amp[1599] + amp[1600] + amp[1601] + amp[1602] +
      amp[1603] - 1./2. * amp[1612] - 1./2. * amp[1613] + amp[1616] + amp[1617]
      - 1./6. * amp[1618] - 1./6. * amp[1619] + amp[1620] + amp[1621];
  jamp[1] = -amp[1604] - amp[1605] - amp[1606] - amp[1607] - amp[1608] -
      amp[1609] - amp[1610] - amp[1611] + 1./6. * amp[1612] + 1./6. * amp[1613]
      - amp[1614] - amp[1615] + 1./2. * amp[1618] + 1./2. * amp[1619];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[47][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ud_vevexud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1622] + amp[1623] + amp[1624] + amp[1625] - 1./6. * amp[1626]
      - 1./6. * amp[1627] + amp[1628] + amp[1629] + amp[1636] + amp[1637] -
      1./6. * amp[1638] - 1./6. * amp[1639] + amp[1640] + amp[1641];
  jamp[1] = +1./2. * amp[1626] + 1./2. * amp[1627] - amp[1630] - amp[1631] -
      amp[1632] - amp[1633] - amp[1634] - amp[1635] + 1./2. * amp[1638] + 1./2.
      * amp[1639];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[48][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_vevexddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1642] + amp[1643] + amp[1644] + amp[1645] - 1./6. * amp[1646]
      - 1./6. * amp[1647] + amp[1648] + amp[1649] + amp[1656] + amp[1657] -
      1./6. * amp[1658] - 1./6. * amp[1659] + amp[1660] + amp[1661];
  jamp[1] = +1./2. * amp[1646] + 1./2. * amp[1647] - amp[1650] - amp[1651] -
      amp[1652] - amp[1653] - amp[1654] - amp[1655] + 1./2. * amp[1658] + 1./2.
      * amp[1659];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[49][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_vevexudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[1666] - 1./2. * amp[1667] + amp[1670] + amp[1671] +
      amp[1672] + amp[1673] + amp[1674] + amp[1675] - 1./2. * amp[1678] - 1./2.
      * amp[1679];
  jamp[1] = -amp[1662] - amp[1663] - amp[1664] - amp[1665] + 1./6. * amp[1666]
      + 1./6. * amp[1667] - amp[1668] - amp[1669] - amp[1676] - amp[1677] +
      1./6. * amp[1678] + 1./6. * amp[1679] - amp[1680] - amp[1681];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[50][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_vevexdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -1./2. * amp[1686] - 1./2. * amp[1687] + amp[1690] + amp[1691] +
      amp[1692] + amp[1693] + amp[1694] + amp[1695] - 1./2. * amp[1698] - 1./2.
      * amp[1699];
  jamp[1] = -amp[1682] - amp[1683] - amp[1684] - amp[1685] + 1./6. * amp[1686]
      + 1./6. * amp[1687] - amp[1688] - amp[1689] - amp[1696] - amp[1697] +
      1./6. * amp[1698] + 1./6. * amp[1699] - amp[1700] - amp[1701];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[51][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_vevexuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1702] + amp[1703] + amp[1704] + amp[1705] - 1./6. * amp[1706]
      - 1./6. * amp[1707] + amp[1708] + amp[1709] + amp[1716] + amp[1717] -
      1./6. * amp[1718] - 1./6. * amp[1719] + amp[1720] + amp[1721];
  jamp[1] = +1./2. * amp[1706] + 1./2. * amp[1707] - amp[1710] - amp[1711] -
      amp[1712] - amp[1713] - amp[1714] - amp[1715] + 1./2. * amp[1718] + 1./2.
      * amp[1719];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[52][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxdx_vevexuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 20;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1722] + amp[1723] + amp[1724] + amp[1725] - 1./6. * amp[1726]
      - 1./6. * amp[1727] + amp[1728] + amp[1729] + amp[1736] + amp[1737] -
      1./6. * amp[1738] - 1./6. * amp[1739] + amp[1740] + amp[1741];
  jamp[1] = +1./2. * amp[1726] + 1./2. * amp[1727] - amp[1730] - amp[1731] -
      amp[1732] - amp[1733] - amp[1734] - amp[1735] + 1./2. * amp[1738] + 1./2.
      * amp[1739];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[53][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uc_vevexuc() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1742] + amp[1743] + amp[1744] + amp[1745] - 1./6. * amp[1746]
      - 1./6. * amp[1747] + amp[1748] + amp[1749] + amp[1750] + amp[1751] -
      1./6. * amp[1752] - 1./6. * amp[1753] + amp[1754] + amp[1755];
  jamp[1] = +1./2. * (+amp[1746] + amp[1747] + amp[1752] + amp[1753]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[54][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_vevexus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1756] + amp[1757] + amp[1758] + amp[1759] - 1./6. * amp[1760]
      - 1./6. * amp[1761] + amp[1762] + amp[1763] + amp[1764] + amp[1765] -
      1./6. * amp[1766] - 1./6. * amp[1767] + amp[1768] + amp[1769];
  jamp[1] = +1./2. * (+amp[1760] + amp[1761] + amp[1766] + amp[1767]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[55][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_vevexccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1770] + amp[1771] + amp[1772] + amp[1773] - 1./6. * amp[1774]
      - 1./6. * amp[1775] + amp[1776] + amp[1777] + amp[1778] + amp[1779] -
      1./6. * amp[1780] - 1./6. * amp[1781] + amp[1782] + amp[1783];
  jamp[1] = +1./2. * (+amp[1774] + amp[1775] + amp[1780] + amp[1781]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[56][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_vevexssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1784] + amp[1785] + amp[1786] + amp[1787] - 1./6. * amp[1788]
      - 1./6. * amp[1789] + amp[1790] + amp[1791] + amp[1792] + amp[1793] -
      1./6. * amp[1794] - 1./6. * amp[1795] + amp[1796] + amp[1797];
  jamp[1] = +1./2. * (+amp[1788] + amp[1789] + amp[1794] + amp[1795]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[57][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_vevexucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[1802] - amp[1803] - amp[1808] - amp[1809]); 
  jamp[1] = -amp[1798] - amp[1799] - amp[1800] - amp[1801] + 1./6. * amp[1802]
      + 1./6. * amp[1803] - amp[1804] - amp[1805] - amp[1806] - amp[1807] +
      1./6. * amp[1808] + 1./6. * amp[1809] - amp[1810] - amp[1811];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[58][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_usx_vevexusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[1816] - amp[1817] - amp[1822] - amp[1823]); 
  jamp[1] = -amp[1812] - amp[1813] - amp[1814] - amp[1815] + 1./6. * amp[1816]
      + 1./6. * amp[1817] - amp[1818] - amp[1819] - amp[1820] - amp[1821] +
      1./6. * amp[1822] + 1./6. * amp[1823] - amp[1824] - amp[1825];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[59][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ds_vevexds() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1826] + amp[1827] + amp[1828] + amp[1829] - 1./6. * amp[1830]
      - 1./6. * amp[1831] + amp[1832] + amp[1833] + amp[1834] + amp[1835] -
      1./6. * amp[1836] - 1./6. * amp[1837] + amp[1838] + amp[1839];
  jamp[1] = +1./2. * (+amp[1830] + amp[1831] + amp[1836] + amp[1837]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[60][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dcx_vevexdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[1844] - amp[1845] - amp[1850] - amp[1851]); 
  jamp[1] = -amp[1840] - amp[1841] - amp[1842] - amp[1843] + 1./6. * amp[1844]
      + 1./6. * amp[1845] - amp[1846] - amp[1847] - amp[1848] - amp[1849] +
      1./6. * amp[1850] + 1./6. * amp[1851] - amp[1852] - amp[1853];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[61][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_vevexccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1854] + amp[1855] + amp[1856] + amp[1857] - 1./6. * amp[1858]
      - 1./6. * amp[1859] + amp[1860] + amp[1861] + amp[1862] + amp[1863] -
      1./6. * amp[1864] - 1./6. * amp[1865] + amp[1866] + amp[1867];
  jamp[1] = +1./2. * (+amp[1858] + amp[1859] + amp[1864] + amp[1865]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[62][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_vevexssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1868] + amp[1869] + amp[1870] + amp[1871] - 1./6. * amp[1872]
      - 1./6. * amp[1873] + amp[1874] + amp[1875] + amp[1876] + amp[1877] -
      1./6. * amp[1878] - 1./6. * amp[1879] + amp[1880] + amp[1881];
  jamp[1] = +1./2. * (+amp[1872] + amp[1873] + amp[1878] + amp[1879]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[63][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_vevexdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[1886] - amp[1887] - amp[1892] - amp[1893]); 
  jamp[1] = -amp[1882] - amp[1883] - amp[1884] - amp[1885] + 1./6. * amp[1886]
      + 1./6. * amp[1887] - amp[1888] - amp[1889] - amp[1890] - amp[1891] +
      1./6. * amp[1892] + 1./6. * amp[1893] - amp[1894] - amp[1895];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[64][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxcx_vevexuxcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1896] + amp[1897] + amp[1898] + amp[1899] - 1./6. * amp[1900]
      - 1./6. * amp[1901] + amp[1902] + amp[1903] + amp[1904] + amp[1905] -
      1./6. * amp[1906] - 1./6. * amp[1907] + amp[1908] + amp[1909];
  jamp[1] = +1./2. * (+amp[1900] + amp[1901] + amp[1906] + amp[1907]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[65][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_vevexuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1910] + amp[1911] + amp[1912] + amp[1913] - 1./6. * amp[1914]
      - 1./6. * amp[1915] + amp[1916] + amp[1917] + amp[1918] + amp[1919] -
      1./6. * amp[1920] - 1./6. * amp[1921] + amp[1922] + amp[1923];
  jamp[1] = +1./2. * (+amp[1914] + amp[1915] + amp[1920] + amp[1921]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[66][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxsx_vevexdxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 14;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1924] + amp[1925] + amp[1926] + amp[1927] - 1./6. * amp[1928]
      - 1./6. * amp[1929] + amp[1930] + amp[1931] + amp[1932] + amp[1933] -
      1./6. * amp[1934] - 1./6. * amp[1935] + amp[1936] + amp[1937];
  jamp[1] = +1./2. * (+amp[1928] + amp[1929] + amp[1934] + amp[1935]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[67][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uc_veepus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1938] + amp[1939] + amp[1940] + amp[1941] + amp[1942] +
      amp[1943] + amp[1944] - 1./6. * amp[1945] - 1./6. * amp[1946] + amp[1947]
      + amp[1948] + amp[1949];
  jamp[1] = +1./2. * (+amp[1945] + amp[1946]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[68][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uc_veepcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[1958] - amp[1959]); 
  jamp[1] = -amp[1950] - amp[1951] - amp[1952] - amp[1953] - amp[1954] -
      amp[1955] - amp[1956] - amp[1957] + 1./6. * amp[1958] + 1./6. * amp[1959]
      - amp[1960] - amp[1961];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[69][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_emvexuc() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1962] + amp[1963] + amp[1964] + amp[1965] + amp[1966] +
      amp[1967] + amp[1968] - 1./6. * amp[1969] - 1./6. * amp[1970] + amp[1971]
      + amp[1972] + amp[1973];
  jamp[1] = +1./2. * (+amp[1969] + amp[1970]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[70][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_veepds() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1974] + amp[1975] + amp[1976] + amp[1977] + amp[1978] +
      amp[1979] + amp[1980] + amp[1981] - 1./6. * amp[1982] - 1./6. * amp[1983]
      + amp[1984] + amp[1985];
  jamp[1] = +1./2. * (+amp[1982] + amp[1983]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[71][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_emvexcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1986] + amp[1987] + amp[1988] + amp[1989] + amp[1990] +
      amp[1991] + amp[1992] - 1./6. * amp[1993] - 1./6. * amp[1994] + amp[1995]
      + amp[1996] + amp[1997];
  jamp[1] = +1./2. * (+amp[1993] + amp[1994]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[72][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uux_veepscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[1998] + amp[1999] + amp[2000] + amp[2001] + amp[2002] +
      amp[2003] + amp[2004] - 1./6. * amp[2005] - 1./6. * amp[2006] + amp[2007]
      + amp[2008] + amp[2009];
  jamp[1] = +1./2. * (+amp[2005] + amp[2006]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[73][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_emvexusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2017] - amp[2018]); 
  jamp[1] = -amp[2010] - amp[2011] - amp[2012] - amp[2013] - amp[2014] -
      amp[2015] - amp[2016] + 1./6. * amp[2017] + 1./6. * amp[2018] - amp[2019]
      - amp[2020] - amp[2021];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[74][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_veepdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2030] - amp[2031]); 
  jamp[1] = -amp[2022] - amp[2023] - amp[2024] - amp[2025] - amp[2026] -
      amp[2027] - amp[2028] - amp[2029] + 1./6. * amp[2030] + 1./6. * amp[2031]
      - amp[2032] - amp[2033];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[75][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_veepccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2034] + amp[2035] + amp[2036] + amp[2037] + amp[2038] +
      amp[2039] + amp[2040] + amp[2041] - 1./6. * amp[2042] - 1./6. * amp[2043]
      + amp[2044] + amp[2045];
  jamp[1] = +1./2. * (+amp[2042] + amp[2043]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[76][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_veepssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2046] + amp[2047] + amp[2048] + amp[2049] + amp[2050] +
      amp[2051] + amp[2052] + amp[2053] - 1./6. * amp[2054] - 1./6. * amp[2055]
      + amp[2056] + amp[2057];
  jamp[1] = +1./2. * (+amp[2054] + amp[2055]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[77][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_usx_veepucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2065] - amp[2066]); 
  jamp[1] = -amp[2058] - amp[2059] - amp[2060] - amp[2061] - amp[2062] -
      amp[2063] - amp[2064] + 1./6. * amp[2065] + 1./6. * amp[2066] - amp[2067]
      - amp[2068] - amp[2069];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[78][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_usx_veepdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2078] - amp[2079]); 
  jamp[1] = -amp[2070] - amp[2071] - amp[2072] - amp[2073] - amp[2074] -
      amp[2075] - amp[2076] - amp[2077] + 1./6. * amp[2078] + 1./6. * amp[2079]
      - amp[2080] - amp[2081];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[79][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ds_emvexus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2082] + amp[2083] + amp[2084] + amp[2085] + amp[2086] +
      amp[2087] + amp[2088] + amp[2089] - 1./6. * amp[2090] - 1./6. * amp[2091]
      + amp[2092] + amp[2093];
  jamp[1] = +1./2. * (+amp[2090] + amp[2091]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[80][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ds_emvexcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2101] - amp[2102]); 
  jamp[1] = -amp[2094] - amp[2095] - amp[2096] - amp[2097] - amp[2098] -
      amp[2099] - amp[2100] + 1./6. * amp[2101] + 1./6. * amp[2102] - amp[2103]
      - amp[2104] - amp[2105];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[81][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emvexccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2106] + amp[2107] + amp[2108] + amp[2109] + amp[2110] +
      amp[2111] + amp[2112] - 1./6. * amp[2113] - 1./6. * amp[2114] + amp[2115]
      + amp[2116] + amp[2117];
  jamp[1] = +1./2. * (+amp[2113] + amp[2114]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[82][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emvexssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2118] + amp[2119] + amp[2120] + amp[2121] + amp[2122] +
      amp[2123] + amp[2124] + amp[2125] - 1./6. * amp[2126] - 1./6. * amp[2127]
      + amp[2128] + amp[2129];
  jamp[1] = +1./2. * (+amp[2126] + amp[2127]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[83][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dcx_emvexucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2137] - amp[2138]); 
  jamp[1] = -amp[2130] - amp[2131] - amp[2132] - amp[2133] - amp[2134] -
      amp[2135] - amp[2136] + 1./6. * amp[2137] + 1./6. * amp[2138] - amp[2139]
      - amp[2140] - amp[2141];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[84][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dcx_emvexdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2149] - amp[2150]); 
  jamp[1] = -amp[2142] - amp[2143] - amp[2144] - amp[2145] - amp[2146] -
      amp[2147] - amp[2148] + 1./6. * amp[2149] + 1./6. * amp[2150] - amp[2151]
      - amp[2152] - amp[2153];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[85][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_emvexcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2154] + amp[2155] + amp[2156] + amp[2157] + amp[2158] +
      amp[2159] + amp[2160] - 1./6. * amp[2161] - 1./6. * amp[2162] + amp[2163]
      + amp[2164] + amp[2165];
  jamp[1] = +1./2. * (+amp[2161] + amp[2162]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[86][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ddx_veepscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2166] + amp[2167] + amp[2168] + amp[2169] + amp[2170] +
      amp[2171] + amp[2172] + amp[2173] - 1./6. * amp[2174] - 1./6. * amp[2175]
      + amp[2176] + amp[2177];
  jamp[1] = +1./2. * (+amp[2174] + amp[2175]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[87][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_emvexusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2186] - amp[2187]); 
  jamp[1] = -amp[2178] - amp[2179] - amp[2180] - amp[2181] - amp[2182] -
      amp[2183] - amp[2184] - amp[2185] + 1./6. * amp[2186] + 1./6. * amp[2187]
      - amp[2188] - amp[2189];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[88][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_veepdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2198] - amp[2199]); 
  jamp[1] = -amp[2190] - amp[2191] - amp[2192] - amp[2193] - amp[2194] -
      amp[2195] - amp[2196] - amp[2197] + 1./6. * amp[2198] + 1./6. * amp[2199]
      - amp[2200] - amp[2201];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[89][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxcx_emvexuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2202] + amp[2203] + amp[2204] + amp[2205] + amp[2206] +
      amp[2207] + amp[2208] - 1./6. * amp[2209] - 1./6. * amp[2210] + amp[2211]
      + amp[2212] + amp[2213];
  jamp[1] = +1./2. * (+amp[2209] + amp[2210]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[90][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxcx_emvexcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2221] - amp[2222]); 
  jamp[1] = -amp[2214] - amp[2215] - amp[2216] - amp[2217] - amp[2218] -
      amp[2219] - amp[2220] + 1./6. * amp[2221] + 1./6. * amp[2222] - amp[2223]
      - amp[2224] - amp[2225];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[91][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_emvexdxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2226] + amp[2227] + amp[2228] + amp[2229] + amp[2230] +
      amp[2231] + amp[2232] + amp[2233] - 1./6. * amp[2234] - 1./6. * amp[2235]
      + amp[2236] + amp[2237];
  jamp[1] = +1./2. * (+amp[2234] + amp[2235]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[92][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_veepuxcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2238] + amp[2239] + amp[2240] + amp[2241] + amp[2242] +
      amp[2243] + amp[2244] - 1./6. * amp[2245] - 1./6. * amp[2246] + amp[2247]
      + amp[2248] + amp[2249];
  jamp[1] = +1./2. * (+amp[2245] + amp[2246]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[93][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxsx_veepuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[2250] + amp[2251] + amp[2252] + amp[2253] + amp[2254] +
      amp[2255] + amp[2256] + amp[2257] - 1./6. * amp[2258] - 1./6. * amp[2259]
      + amp[2260] + amp[2261];
  jamp[1] = +1./2. * (+amp[2258] + amp[2259]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[94][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dxsx_veepcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 12;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[2270] - amp[2271]); 
  jamp[1] = -amp[2262] - amp[2263] - amp[2264] - amp[2265] - amp[2266] -
      amp[2267] - amp[2268] - amp[2269] + 1./6. * amp[2270] + 1./6. * amp[2271]
      - amp[2272] - amp[2273];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[95][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_emepcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2274] - amp[2275] - amp[2276] - amp[2277] - amp[2278] -
      amp[2279] - amp[2280] - amp[2281] - amp[2282] - amp[2283] - amp[2284];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[96][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_emepdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2285] - amp[2286] - amp[2287] - amp[2288] - amp[2289] -
      amp[2290] - amp[2291] - amp[2292] - amp[2293] - amp[2294] - amp[2295];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[97][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_emepcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[2296] + amp[2297] + amp[2298] + amp[2299] + amp[2300] +
      amp[2301] + amp[2302] + amp[2303] + amp[2304] + amp[2305] + amp[2306];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[98][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_emepscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[2307] + amp[2308] + amp[2309] + amp[2310] + amp[2311] +
      amp[2312] + amp[2313] + amp[2314] + amp[2315] + amp[2316] + amp[2317];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[99][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_emepucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2318] - amp[2319] - amp[2320] - amp[2321] - amp[2322] -
      amp[2323] - amp[2324] - amp[2325] - amp[2326] - amp[2327] - amp[2328];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[100][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_emepcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 11;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2329] - amp[2330] - amp[2331] - amp[2332] - amp[2333] -
      amp[2334] - amp[2335] - amp[2336] - amp[2337] - amp[2338] - amp[2339];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[101][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_us_vevexcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2340] - amp[2341] - amp[2342] - amp[2343] - amp[2344] -
      amp[2345];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[102][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_ucx_vevexdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2346] - amp[2347] - amp[2348] - amp[2349] - amp[2350] -
      amp[2351];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[103][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_udx_vevexcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[2352] + amp[2353] + amp[2354] + amp[2355] + amp[2356] +
      amp[2357];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[104][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dux_vevexscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[2358] + amp[2359] + amp[2360] + amp[2361] + amp[2362] +
      amp[2363];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[105][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_dsx_vevexucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2364] - amp[2365] - amp[2366] - amp[2367] - amp[2368] -
      amp[2369];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[106][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}

double PY8MEs_R7_P1_sm_qq_llqq::matrix_7_uxsx_vevexcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 6;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[2370] - amp[2371] - amp[2372] - amp[2373] - amp[2374] -
      amp[2375];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
  for(i = 0; i < ncolor; i++ )
  {
    ztemp = 0.; 
    for(j = 0; j < ncolor; j++ )
      ztemp = ztemp + cf[i][j] * jamp[j]; 
    matrix = matrix + real(ztemp * conj(jamp[i]))/denom[i]; 
  }

  // Store the leading color flows for choice of color
  for(i = 0; i < ncolor; i++ )
    jamp2[107][i] += real(jamp[i] * conj(jamp[i])) * (cf[i][i]/denom[i]); 

  return matrix; 
}


}  // end namespace PY8MEs_namespace

