//==========================================================================
// This file has been automatically generated for Pythia 8
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#ifndef PY8MEs_R7_P1_sm_qq_llqq_H
#define PY8MEs_R7_P1_sm_qq_llqq_H

#include "Complex.h" 
#include <vector> 
#include <set> 
#include <exception> 
#include <iostream> 

#include "Parameters_sm.h"
#include "PY8MEs.h"

using namespace std; 

namespace PY8MEs_namespace 
{
//==========================================================================
// A class for calculating the matrix elements for
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
//--------------------------------------------------------------------------

typedef vector<double> vec_double; 
typedef vector < vec_double > vec_vec_double; 
typedef vector<int> vec_int; 
typedef vector<bool> vec_bool; 
typedef vector < vec_int > vec_vec_int; 

class PY8MEs_R7_P1_sm_qq_llqq : public PY8ME
{
  public:

    // Check for the availability of the requested proces.
    // If available, this returns the corresponding permutation and Proc_ID  to
    // use.
    // If not available, this returns a negative Proc_ID.
    static pair < vector<int> , int > static_getPY8ME(vector<int> initial_pdgs,
        vector<int> final_pdgs, set<int> schannels = set<int> ());

    // Constructor.
    PY8MEs_R7_P1_sm_qq_llqq(Parameters_sm * model) : pars(model) {initProc();}

    // Destructor.
    ~PY8MEs_R7_P1_sm_qq_llqq(); 

    // Initialize process.
    virtual void initProc(); 

    // Calculate squared ME.
    virtual double sigmaKin(); 

    // Info on the subprocess.
    virtual string name() const {return "qq_llqq (sm)";}

    virtual int code() const {return 10701;}

    virtual string inFlux() const {return "qq";}

    virtual vector<double> getMasses(); 

    virtual void setMasses(vec_double external_masses); 
    // Set all values of the external masses to an integer mode:
    // 0 : Mass taken from the model
    // 1 : Mass taken from p_i^2 if not massless to begin with
    // 2 : Mass always taken from p_i^2.
    virtual void setExternalMassesMode(int mode); 

    // Synchronize local variables of the process that depend on the model
    // parameters
    virtual void syncProcModelParams(); 

    // Tell Pythia that sigmaHat returns the ME^2
    virtual bool convertM2() const {return true;}

    // Access to getPY8ME with polymorphism from a non-static context
    virtual pair < vector<int> , int > getPY8ME(vector<int> initial_pdgs,
        vector<int> final_pdgs, set<int> schannels = set<int> ())
    {
      return static_getPY8ME(initial_pdgs, final_pdgs, schannels); 
    }

    // Set momenta
    virtual void setMomenta(vector < vec_double > momenta_picked); 

    // Set color configuration to use. An empty vector means sum over all.
    virtual void setColors(vector<int> colors_picked); 

    // Set the helicity configuration to use. Am empty vector means sum over
    // all.
    virtual void setHelicities(vector<int> helicities_picked); 

    // Set the permutation to use (will apply to momenta, colors and helicities)
    virtual void setPermutation(vector<int> perm_picked); 

    // Set the proc_ID to use
    virtual void setProcID(int procID_picked); 

    // Access to all the helicity and color configurations for a given process
    virtual vector < vec_int > getColorConfigs(int specify_proc_ID = -1,
        vector<int> permutation = vector<int> ());
    virtual vector < vec_int > getHelicityConfigs(vector<int> permutation =
        vector<int> ());

    // Maps of Helicity <-> hel_ID and ColorConfig <-> colorConfig_ID.
    virtual vector<int> getHelicityConfigForID(int hel_ID, vector<int>
        permutation = vector<int> ());
    virtual int getHelicityIDForConfig(vector<int> hel_config, vector<int>
        permutation = vector<int> ());
    virtual vector<int> getColorConfigForID(int color_ID, int specify_proc_ID =
        -1, vector<int> permutation = vector<int> ());
    virtual int getColorIDForConfig(vector<int> color_config, int
        specify_proc_ID = -1, vector<int> permutation = vector<int> ());
    virtual int getColorFlowRelativeNCPower(int color_flow_ID, int
        specify_proc_ID = -1);

    // Access previously computed results
    virtual vector < vec_double > getAllResults(int specify_proc_ID = -1); 
    virtual double getResult(int helicity_ID, int color_ID, int specify_proc_ID
        = -1);

    // Accessors
    Parameters_sm * getModel() {return pars;}
    void setModel(Parameters_sm * model) {pars = model;}

    // Invert the permutation mapping
    vector<int> invert_mapping(vector<int> mapping); 

    // Control whether to include the symmetry factors or not
    virtual void setIncludeSymmetryFactors(bool OnOff) 
    {
      include_symmetry_factors = OnOff; 
    }
    virtual bool getIncludeSymmetryFactors() {return include_symmetry_factors;}
    virtual int getSymmetryFactor() {return denom_iden[proc_ID];}

    // Control whether to include helicity averaging factors or not
    virtual void setIncludeHelicityAveragingFactors(bool OnOff) 
    {
      include_helicity_averaging_factors = OnOff; 
    }
    virtual bool getIncludeHelicityAveragingFactors() 
    {
      return include_helicity_averaging_factors; 
    }
    virtual int getHelicityAveragingFactor() {return denom_hels[proc_ID];}

    // Control whether to include color averaging factors or not
    virtual void setIncludeColorAveragingFactors(bool OnOff) 
    {
      include_color_averaging_factors = OnOff; 
    }
    virtual bool getIncludeColorAveragingFactors() 
    {
      return include_color_averaging_factors; 
    }
    virtual int getColorAveragingFactor() {return denom_colors[proc_ID];}

  private:

    // Private functions to calculate the matrix element for all subprocesses
    // Calculate wavefunctions
    void calculate_wavefunctions(const int hel[]); 
    static const int nwavefuncs = 346; 
    Complex<double> w[nwavefuncs][18]; 
    static const int namplitudes = 2376; 
    Complex<double> amp[namplitudes]; 
    double matrix_7_uu_emepuu(); 
    double matrix_7_uux_emepuux(); 
    double matrix_7_dd_emepdd(); 
    double matrix_7_ddx_emepddx(); 
    double matrix_7_uxux_emepuxux(); 
    double matrix_7_dxdx_emepdxdx(); 
    double matrix_7_ud_emepud(); 
    double matrix_7_uux_emepddx(); 
    double matrix_7_udx_emepudx(); 
    double matrix_7_dux_emepdux(); 
    double matrix_7_ddx_emepuux(); 
    double matrix_7_uxdx_emepuxdx(); 
    double matrix_7_uc_emepuc(); 
    double matrix_7_us_emepus(); 
    double matrix_7_uux_emepccx(); 
    double matrix_7_uux_emepssx(); 
    double matrix_7_ucx_emepucx(); 
    double matrix_7_usx_emepusx(); 
    double matrix_7_ds_emepds(); 
    double matrix_7_dcx_emepdcx(); 
    double matrix_7_ddx_emepccx(); 
    double matrix_7_ddx_emepssx(); 
    double matrix_7_dsx_emepdsx(); 
    double matrix_7_uxcx_emepuxcx(); 
    double matrix_7_uxsx_emepuxsx(); 
    double matrix_7_dxsx_emepdxsx(); 
    double matrix_7_uu_vevexuu(); 
    double matrix_7_uux_vevexuux(); 
    double matrix_7_dd_vevexdd(); 
    double matrix_7_ddx_vevexddx(); 
    double matrix_7_uxux_vevexuxux(); 
    double matrix_7_dxdx_vevexdxdx(); 
    double matrix_7_uu_veepud(); 
    double matrix_7_ud_emvexuu(); 
    double matrix_7_ud_veepdd(); 
    double matrix_7_uux_emvexudx(); 
    double matrix_7_uux_veepdux(); 
    double matrix_7_udx_veepuux(); 
    double matrix_7_udx_veepddx(); 
    double matrix_7_dd_emvexud(); 
    double matrix_7_dux_emvexuux(); 
    double matrix_7_dux_emvexddx(); 
    double matrix_7_ddx_emvexudx(); 
    double matrix_7_ddx_veepdux(); 
    double matrix_7_uxux_emvexuxdx(); 
    double matrix_7_uxdx_emvexdxdx(); 
    double matrix_7_uxdx_veepuxux(); 
    double matrix_7_dxdx_veepuxdx(); 
    double matrix_7_ud_vevexud(); 
    double matrix_7_uux_vevexddx(); 
    double matrix_7_udx_vevexudx(); 
    double matrix_7_dux_vevexdux(); 
    double matrix_7_ddx_vevexuux(); 
    double matrix_7_uxdx_vevexuxdx(); 
    double matrix_7_uc_vevexuc(); 
    double matrix_7_us_vevexus(); 
    double matrix_7_uux_vevexccx(); 
    double matrix_7_uux_vevexssx(); 
    double matrix_7_ucx_vevexucx(); 
    double matrix_7_usx_vevexusx(); 
    double matrix_7_ds_vevexds(); 
    double matrix_7_dcx_vevexdcx(); 
    double matrix_7_ddx_vevexccx(); 
    double matrix_7_ddx_vevexssx(); 
    double matrix_7_dsx_vevexdsx(); 
    double matrix_7_uxcx_vevexuxcx(); 
    double matrix_7_uxsx_vevexuxsx(); 
    double matrix_7_dxsx_vevexdxsx(); 
    double matrix_7_uc_veepus(); 
    double matrix_7_uc_veepcd(); 
    double matrix_7_us_emvexuc(); 
    double matrix_7_us_veepds(); 
    double matrix_7_uux_emvexcsx(); 
    double matrix_7_uux_veepscx(); 
    double matrix_7_ucx_emvexusx(); 
    double matrix_7_ucx_veepdcx(); 
    double matrix_7_udx_veepccx(); 
    double matrix_7_udx_veepssx(); 
    double matrix_7_usx_veepucx(); 
    double matrix_7_usx_veepdsx(); 
    double matrix_7_ds_emvexus(); 
    double matrix_7_ds_emvexcd(); 
    double matrix_7_dux_emvexccx(); 
    double matrix_7_dux_emvexssx(); 
    double matrix_7_dcx_emvexucx(); 
    double matrix_7_dcx_emvexdsx(); 
    double matrix_7_ddx_emvexcsx(); 
    double matrix_7_ddx_veepscx(); 
    double matrix_7_dsx_emvexusx(); 
    double matrix_7_dsx_veepdcx(); 
    double matrix_7_uxcx_emvexuxsx(); 
    double matrix_7_uxcx_emvexcxdx(); 
    double matrix_7_uxsx_emvexdxsx(); 
    double matrix_7_uxsx_veepuxcx(); 
    double matrix_7_dxsx_veepuxsx(); 
    double matrix_7_dxsx_veepcxdx(); 
    double matrix_7_us_emepcd(); 
    double matrix_7_ucx_emepdsx(); 
    double matrix_7_udx_emepcsx(); 
    double matrix_7_dux_emepscx(); 
    double matrix_7_dsx_emepucx(); 
    double matrix_7_uxsx_emepcxdx(); 
    double matrix_7_us_vevexcd(); 
    double matrix_7_ucx_vevexdsx(); 
    double matrix_7_udx_vevexcsx(); 
    double matrix_7_dux_vevexscx(); 
    double matrix_7_dsx_vevexucx(); 
    double matrix_7_uxsx_vevexcxdx(); 

    // Constants for array limits
    static const int nexternal = 6; 
    static const int ninitial = 2; 
    static const int nprocesses = 108; 
    static const int nreq_s_channels = 0; 
    static const int ncomb = 64; 

    // Helicities for the process
    static int helicities[ncomb][nexternal]; 

    // Normalization factors the various processes
    static int denom_colors[nprocesses]; 
    static int denom_hels[nprocesses]; 
    static int denom_iden[nprocesses]; 

    // Control whether to include symmetry factors or not
    bool include_symmetry_factors; 
    // Control whether to include helicity averaging factors or not
    bool include_helicity_averaging_factors; 
    // Control whether to include color averaging factors or not
    bool include_color_averaging_factors; 

    // Color flows, used when selecting color
    vector < vec_double > jamp2; 

    // Store individual results (for each color flow, helicity configurations
    // and proc_ID)
    // computed in the last call to sigmaKin().
    vector < vec_vec_double > all_results; 

    // required s-channels specified
    static std::set<int> s_channel_proc; 

    // vector with external particle masses
    vector<double> mME; 

    // vector with momenta (to be changed for each event)
    vector < double * > p; 

    // external particles permutation (to be changed for each event)
    vector<int> perm; 

    // vector with colors (to be changed for each event)
    vector<int> user_colors; 

    // vector with helicities (to be changed for each event)
    vector<int> user_helicities; 

    // Process ID (to be changed for each event)
    int proc_ID; 

    // All color configurations
    void initColorConfigs(); 
    vector < vec_vec_int > color_configs; 

    // Color flows relative N_c power (conventions are such that all elements
    // on the color matrix diagonal are identical).
    vector < vec_int > jamp_nc_relative_power; 

    // Model pointer to be used by this matrix element
    Parameters_sm * pars; 

}; 

}  // end namespace PY8MEs_namespace

#endif  // PY8MEs_R7_P1_sm_qq_llqq_H

