//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R8_P20_sm_qq_wpqq.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u > w+ u d WEIGHTED<=99 @8
// Process: c c > w+ c s WEIGHTED<=99 @8
// Process: u d > w+ d d WEIGHTED<=99 @8
// Process: c s > w+ s s WEIGHTED<=99 @8
// Process: u d > w- u u WEIGHTED<=99 @8
// Process: c s > w- c c WEIGHTED<=99 @8
// Process: u u~ > w+ d u~ WEIGHTED<=99 @8
// Process: c c~ > w+ s c~ WEIGHTED<=99 @8
// Process: u u~ > w- u d~ WEIGHTED<=99 @8
// Process: c c~ > w- c s~ WEIGHTED<=99 @8
// Process: u d~ > w+ u u~ WEIGHTED<=99 @8
// Process: c s~ > w+ c c~ WEIGHTED<=99 @8
// Process: u d~ > w+ d d~ WEIGHTED<=99 @8
// Process: c s~ > w+ s s~ WEIGHTED<=99 @8
// Process: d d > w- u d WEIGHTED<=99 @8
// Process: s s > w- c s WEIGHTED<=99 @8
// Process: d u~ > w- u u~ WEIGHTED<=99 @8
// Process: s c~ > w- c c~ WEIGHTED<=99 @8
// Process: d u~ > w- d d~ WEIGHTED<=99 @8
// Process: s c~ > w- s s~ WEIGHTED<=99 @8
// Process: d d~ > w+ d u~ WEIGHTED<=99 @8
// Process: s s~ > w+ s c~ WEIGHTED<=99 @8
// Process: d d~ > w- u d~ WEIGHTED<=99 @8
// Process: s s~ > w- c s~ WEIGHTED<=99 @8
// Process: u~ u~ > w- u~ d~ WEIGHTED<=99 @8
// Process: c~ c~ > w- c~ s~ WEIGHTED<=99 @8
// Process: u~ d~ > w+ u~ u~ WEIGHTED<=99 @8
// Process: c~ s~ > w+ c~ c~ WEIGHTED<=99 @8
// Process: u~ d~ > w- d~ d~ WEIGHTED<=99 @8
// Process: c~ s~ > w- s~ s~ WEIGHTED<=99 @8
// Process: d~ d~ > w+ u~ d~ WEIGHTED<=99 @8
// Process: s~ s~ > w+ c~ s~ WEIGHTED<=99 @8
// Process: u c > w+ u s WEIGHTED<=99 @8
// Process: u c > w+ c d WEIGHTED<=99 @8
// Process: u s > w+ d s WEIGHTED<=99 @8
// Process: c d > w+ s d WEIGHTED<=99 @8
// Process: u s > w- u c WEIGHTED<=99 @8
// Process: c d > w- c u WEIGHTED<=99 @8
// Process: u u~ > w+ s c~ WEIGHTED<=99 @8
// Process: c c~ > w+ d u~ WEIGHTED<=99 @8
// Process: u u~ > w- c s~ WEIGHTED<=99 @8
// Process: c c~ > w- u d~ WEIGHTED<=99 @8
// Process: u c~ > w+ d c~ WEIGHTED<=99 @8
// Process: c u~ > w+ s u~ WEIGHTED<=99 @8
// Process: u c~ > w- u s~ WEIGHTED<=99 @8
// Process: c u~ > w- c d~ WEIGHTED<=99 @8
// Process: u d~ > w+ c c~ WEIGHTED<=99 @8
// Process: c s~ > w+ u u~ WEIGHTED<=99 @8
// Process: u d~ > w+ s s~ WEIGHTED<=99 @8
// Process: c s~ > w+ d d~ WEIGHTED<=99 @8
// Process: u s~ > w+ u c~ WEIGHTED<=99 @8
// Process: c d~ > w+ c u~ WEIGHTED<=99 @8
// Process: u s~ > w+ d s~ WEIGHTED<=99 @8
// Process: c d~ > w+ s d~ WEIGHTED<=99 @8
// Process: d s > w- u s WEIGHTED<=99 @8
// Process: d s > w- c d WEIGHTED<=99 @8
// Process: d u~ > w- c c~ WEIGHTED<=99 @8
// Process: s c~ > w- u u~ WEIGHTED<=99 @8
// Process: d u~ > w- s s~ WEIGHTED<=99 @8
// Process: s c~ > w- d d~ WEIGHTED<=99 @8
// Process: d c~ > w- u c~ WEIGHTED<=99 @8
// Process: s u~ > w- c u~ WEIGHTED<=99 @8
// Process: d c~ > w- d s~ WEIGHTED<=99 @8
// Process: s u~ > w- s d~ WEIGHTED<=99 @8
// Process: d d~ > w+ s c~ WEIGHTED<=99 @8
// Process: s s~ > w+ d u~ WEIGHTED<=99 @8
// Process: d d~ > w- c s~ WEIGHTED<=99 @8
// Process: s s~ > w- u d~ WEIGHTED<=99 @8
// Process: d s~ > w+ d c~ WEIGHTED<=99 @8
// Process: s d~ > w+ s u~ WEIGHTED<=99 @8
// Process: d s~ > w- u s~ WEIGHTED<=99 @8
// Process: s d~ > w- c d~ WEIGHTED<=99 @8
// Process: u~ c~ > w- u~ s~ WEIGHTED<=99 @8
// Process: u~ c~ > w- c~ d~ WEIGHTED<=99 @8
// Process: u~ s~ > w+ u~ c~ WEIGHTED<=99 @8
// Process: c~ d~ > w+ c~ u~ WEIGHTED<=99 @8
// Process: u~ s~ > w- d~ s~ WEIGHTED<=99 @8
// Process: c~ d~ > w- s~ d~ WEIGHTED<=99 @8
// Process: d~ s~ > w+ u~ s~ WEIGHTED<=99 @8
// Process: d~ s~ > w+ c~ d~ WEIGHTED<=99 @8

// Exception class
class PY8MEs_R8_P20_sm_qq_wpqqException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R8_P20_sm_qq_wpqq'."; 
  }
}
PY8MEs_R8_P20_sm_qq_wpqq_exception; 

std::set<int> PY8MEs_R8_P20_sm_qq_wpqq::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R8_P20_sm_qq_wpqq::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
    -1}, {-1, -1, -1, -1, 1}, {-1, -1, -1, 1, -1}, {-1, -1, -1, 1, 1}, {-1, -1,
    0, -1, -1}, {-1, -1, 0, -1, 1}, {-1, -1, 0, 1, -1}, {-1, -1, 0, 1, 1}, {-1,
    -1, 1, -1, -1}, {-1, -1, 1, -1, 1}, {-1, -1, 1, 1, -1}, {-1, -1, 1, 1, 1},
    {-1, 1, -1, -1, -1}, {-1, 1, -1, -1, 1}, {-1, 1, -1, 1, -1}, {-1, 1, -1, 1,
    1}, {-1, 1, 0, -1, -1}, {-1, 1, 0, -1, 1}, {-1, 1, 0, 1, -1}, {-1, 1, 0, 1,
    1}, {-1, 1, 1, -1, -1}, {-1, 1, 1, -1, 1}, {-1, 1, 1, 1, -1}, {-1, 1, 1, 1,
    1}, {1, -1, -1, -1, -1}, {1, -1, -1, -1, 1}, {1, -1, -1, 1, -1}, {1, -1,
    -1, 1, 1}, {1, -1, 0, -1, -1}, {1, -1, 0, -1, 1}, {1, -1, 0, 1, -1}, {1,
    -1, 0, 1, 1}, {1, -1, 1, -1, -1}, {1, -1, 1, -1, 1}, {1, -1, 1, 1, -1}, {1,
    -1, 1, 1, 1}, {1, 1, -1, -1, -1}, {1, 1, -1, -1, 1}, {1, 1, -1, 1, -1}, {1,
    1, -1, 1, 1}, {1, 1, 0, -1, -1}, {1, 1, 0, -1, 1}, {1, 1, 0, 1, -1}, {1, 1,
    0, 1, 1}, {1, 1, 1, -1, -1}, {1, 1, 1, -1, 1}, {1, 1, 1, 1, -1}, {1, 1, 1,
    1, 1}};

// Normalization factors the various processes
// Denominators: spins, colors and identical particles
int PY8MEs_R8_P20_sm_qq_wpqq::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
int PY8MEs_R8_P20_sm_qq_wpqq::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R8_P20_sm_qq_wpqq::denom_iden[nprocesses] = {1, 2, 2, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R8_P20_sm_qq_wpqq::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u u > w+ u d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #1
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[0].push_back(0); 

  // Color flows of process Process: u d > w+ d d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #1
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[1].push_back(0); 

  // Color flows of process Process: u d > w- u u WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: u u~ > w+ d u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #1
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[3].push_back(0); 

  // Color flows of process Process: u u~ > w- u d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: u d~ > w+ u u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[5].push_back(0); 

  // Color flows of process Process: u d~ > w+ d d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: d d > w- u d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: d u~ > w- u u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #1
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[8].push_back(0); 

  // Color flows of process Process: d u~ > w- d d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[9].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #1
  color_configs[9].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[9].push_back(0); 

  // Color flows of process Process: d d~ > w+ d u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #1
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[10].push_back(0); 

  // Color flows of process Process: d d~ > w- u d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: u~ u~ > w- u~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: u~ d~ > w+ u~ u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: u~ d~ > w- d~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: d~ d~ > w+ u~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: u c > w+ u s WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: u c > w+ c d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[17].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[17].push_back(0); 
  // JAMP #1
  color_configs[17].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[17].push_back(0); 

  // Color flows of process Process: u s > w+ d s WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[18].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[18].push_back(0); 
  // JAMP #1
  color_configs[18].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[18].push_back(0); 

  // Color flows of process Process: u s > w- u c WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[19].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[19].push_back(0); 
  // JAMP #1
  color_configs[19].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[19].push_back(0); 

  // Color flows of process Process: u u~ > w+ s c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[20].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[20].push_back(0); 
  // JAMP #1
  color_configs[20].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[20].push_back(0); 

  // Color flows of process Process: u u~ > w- c s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[21].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[21].push_back(0); 
  // JAMP #1
  color_configs[21].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[21].push_back(0); 

  // Color flows of process Process: u c~ > w+ d c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[22].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[22].push_back(0); 
  // JAMP #1
  color_configs[22].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[22].push_back(0); 

  // Color flows of process Process: u c~ > w- u s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[23].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[23].push_back(0); 
  // JAMP #1
  color_configs[23].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[23].push_back(0); 

  // Color flows of process Process: u d~ > w+ c c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[24].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[24].push_back(0); 
  // JAMP #1
  color_configs[24].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[24].push_back(0); 

  // Color flows of process Process: u d~ > w+ s s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[25].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[25].push_back(0); 
  // JAMP #1
  color_configs[25].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[25].push_back(0); 

  // Color flows of process Process: u s~ > w+ u c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[26].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[26].push_back(0); 
  // JAMP #1
  color_configs[26].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[26].push_back(0); 

  // Color flows of process Process: u s~ > w+ d s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[27].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[27].push_back(0); 
  // JAMP #1
  color_configs[27].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[27].push_back(0); 

  // Color flows of process Process: d s > w- u s WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[28].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[28].push_back(0); 
  // JAMP #1
  color_configs[28].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[28].push_back(0); 

  // Color flows of process Process: d s > w- c d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[29].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[29].push_back(0); 
  // JAMP #1
  color_configs[29].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[29].push_back(0); 

  // Color flows of process Process: d u~ > w- c c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[30].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[30].push_back(0); 
  // JAMP #1
  color_configs[30].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[30].push_back(0); 

  // Color flows of process Process: d u~ > w- s s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[31].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[31].push_back(0); 
  // JAMP #1
  color_configs[31].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[31].push_back(0); 

  // Color flows of process Process: d c~ > w- u c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[32].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[32].push_back(0); 
  // JAMP #1
  color_configs[32].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[32].push_back(0); 

  // Color flows of process Process: d c~ > w- d s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[33].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[33].push_back(0); 
  // JAMP #1
  color_configs[33].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[33].push_back(0); 

  // Color flows of process Process: d d~ > w+ s c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[34].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[34].push_back(0); 
  // JAMP #1
  color_configs[34].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[34].push_back(0); 

  // Color flows of process Process: d d~ > w- c s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[35].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[35].push_back(0); 
  // JAMP #1
  color_configs[35].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[35].push_back(0); 

  // Color flows of process Process: d s~ > w+ d c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[36].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[36].push_back(0); 
  // JAMP #1
  color_configs[36].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[36].push_back(0); 

  // Color flows of process Process: d s~ > w- u s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[37].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[37].push_back(0); 
  // JAMP #1
  color_configs[37].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[37].push_back(0); 

  // Color flows of process Process: u~ c~ > w- u~ s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[38].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[38].push_back(0); 
  // JAMP #1
  color_configs[38].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[38].push_back(0); 

  // Color flows of process Process: u~ c~ > w- c~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[39].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[39].push_back(0); 
  // JAMP #1
  color_configs[39].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[39].push_back(0); 

  // Color flows of process Process: u~ s~ > w+ u~ c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[40].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[40].push_back(0); 
  // JAMP #1
  color_configs[40].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[40].push_back(0); 

  // Color flows of process Process: u~ s~ > w- d~ s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[41].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[41].push_back(0); 
  // JAMP #1
  color_configs[41].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[41].push_back(0); 

  // Color flows of process Process: d~ s~ > w+ u~ s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[42].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[42].push_back(0); 
  // JAMP #1
  color_configs[42].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[42].push_back(0); 

  // Color flows of process Process: d~ s~ > w+ c~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[43].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[43].push_back(0); 
  // JAMP #1
  color_configs[43].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[43].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R8_P20_sm_qq_wpqq::~PY8MEs_R8_P20_sm_qq_wpqq() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R8_P20_sm_qq_wpqq::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R8_P20_sm_qq_wpqq::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R8_P20_sm_qq_wpqq::getColorConfigs(int
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
int PY8MEs_R8_P20_sm_qq_wpqq::getColorFlowRelativeNCPower(int color_flow_ID,
    int specify_proc_ID)
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
vector<int> PY8MEs_R8_P20_sm_qq_wpqq::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
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
int PY8MEs_R8_P20_sm_qq_wpqq::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R8_P20_sm_qq_wpqq::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
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
int PY8MEs_R8_P20_sm_qq_wpqq::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R8_P20_sm_qq_wpqq': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
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
      " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R8_P20_sm_qq_wpqq::getAllResults(int
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
double PY8MEs_R8_P20_sm_qq_wpqq::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
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
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R8_P20_sm_qq_wpqq::static_getPY8ME(vector<int> initial_pdgs, vector<int> final_pdgs, set<int> schannels) 
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
  const int nprocs = 152; 
  const int proc_IDS[nprocs] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
      8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 17, 18,
      18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27,
      27, 28, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37,
      37, 38, 39, 40, 40, 41, 41, 42, 43, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
      8, 8, 9, 9, 10, 10, 11, 11, 13, 13, 14, 14, 16, 17, 18, 18, 19, 19, 20,
      20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 29, 30,
      30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 39, 40,
      40, 41, 41, 42, 43};
  const int in_pdgs[nprocs][ninitial] = {{2, 2}, {4, 4}, {2, 1}, {4, 3}, {2,
      1}, {4, 3}, {2, -2}, {4, -4}, {2, -2}, {4, -4}, {2, -1}, {4, -3}, {2,
      -1}, {4, -3}, {1, 1}, {3, 3}, {1, -2}, {3, -4}, {1, -2}, {3, -4}, {1,
      -1}, {3, -3}, {1, -1}, {3, -3}, {-2, -2}, {-4, -4}, {-2, -1}, {-4, -3},
      {-2, -1}, {-4, -3}, {-1, -1}, {-3, -3}, {2, 4}, {2, 4}, {2, 3}, {4, 1},
      {2, 3}, {4, 1}, {2, -2}, {4, -4}, {2, -2}, {4, -4}, {2, -4}, {4, -2}, {2,
      -4}, {4, -2}, {2, -1}, {4, -3}, {2, -1}, {4, -3}, {2, -3}, {4, -1}, {2,
      -3}, {4, -1}, {1, 3}, {1, 3}, {1, -2}, {3, -4}, {1, -2}, {3, -4}, {1,
      -4}, {3, -2}, {1, -4}, {3, -2}, {1, -1}, {3, -3}, {1, -1}, {3, -3}, {1,
      -3}, {3, -1}, {1, -3}, {3, -1}, {-2, -4}, {-2, -4}, {-2, -3}, {-4, -1},
      {-2, -3}, {-4, -1}, {-1, -3}, {-1, -3}, {1, 2}, {3, 4}, {1, 2}, {3, 4},
      {-2, 2}, {-4, 4}, {-2, 2}, {-4, 4}, {-1, 2}, {-3, 4}, {-1, 2}, {-3, 4},
      {-2, 1}, {-4, 3}, {-2, 1}, {-4, 3}, {-1, 1}, {-3, 3}, {-1, 1}, {-3, 3},
      {-1, -2}, {-3, -4}, {-1, -2}, {-3, -4}, {4, 2}, {4, 2}, {3, 2}, {1, 4},
      {3, 2}, {1, 4}, {-2, 2}, {-4, 4}, {-2, 2}, {-4, 4}, {-4, 2}, {-2, 4},
      {-4, 2}, {-2, 4}, {-1, 2}, {-3, 4}, {-1, 2}, {-3, 4}, {-3, 2}, {-1, 4},
      {-3, 2}, {-1, 4}, {3, 1}, {3, 1}, {-2, 1}, {-4, 3}, {-2, 1}, {-4, 3},
      {-4, 1}, {-2, 3}, {-4, 1}, {-2, 3}, {-1, 1}, {-3, 3}, {-1, 1}, {-3, 3},
      {-3, 1}, {-1, 3}, {-3, 1}, {-1, 3}, {-4, -2}, {-4, -2}, {-3, -2}, {-1,
      -4}, {-3, -2}, {-1, -4}, {-3, -1}, {-3, -1}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{24, 2, 1}, {24, 4, 3},
      {24, 1, 1}, {24, 3, 3}, {-24, 2, 2}, {-24, 4, 4}, {24, 1, -2}, {24, 3,
      -4}, {-24, 2, -1}, {-24, 4, -3}, {24, 2, -2}, {24, 4, -4}, {24, 1, -1},
      {24, 3, -3}, {-24, 2, 1}, {-24, 4, 3}, {-24, 2, -2}, {-24, 4, -4}, {-24,
      1, -1}, {-24, 3, -3}, {24, 1, -2}, {24, 3, -4}, {-24, 2, -1}, {-24, 4,
      -3}, {-24, -2, -1}, {-24, -4, -3}, {24, -2, -2}, {24, -4, -4}, {-24, -1,
      -1}, {-24, -3, -3}, {24, -2, -1}, {24, -4, -3}, {24, 2, 3}, {24, 4, 1},
      {24, 1, 3}, {24, 3, 1}, {-24, 2, 4}, {-24, 4, 2}, {24, 3, -4}, {24, 1,
      -2}, {-24, 4, -3}, {-24, 2, -1}, {24, 1, -4}, {24, 3, -2}, {-24, 2, -3},
      {-24, 4, -1}, {24, 4, -4}, {24, 2, -2}, {24, 3, -3}, {24, 1, -1}, {24, 2,
      -4}, {24, 4, -2}, {24, 1, -3}, {24, 3, -1}, {-24, 2, 3}, {-24, 4, 1},
      {-24, 4, -4}, {-24, 2, -2}, {-24, 3, -3}, {-24, 1, -1}, {-24, 2, -4},
      {-24, 4, -2}, {-24, 1, -3}, {-24, 3, -1}, {24, 3, -4}, {24, 1, -2}, {-24,
      4, -3}, {-24, 2, -1}, {24, 1, -4}, {24, 3, -2}, {-24, 2, -3}, {-24, 4,
      -1}, {-24, -2, -3}, {-24, -4, -1}, {24, -2, -4}, {24, -4, -2}, {-24, -1,
      -3}, {-24, -3, -1}, {24, -2, -3}, {24, -4, -1}, {24, 1, 1}, {24, 3, 3},
      {-24, 2, 2}, {-24, 4, 4}, {24, 1, -2}, {24, 3, -4}, {-24, 2, -1}, {-24,
      4, -3}, {24, 2, -2}, {24, 4, -4}, {24, 1, -1}, {24, 3, -3}, {-24, 2, -2},
      {-24, 4, -4}, {-24, 1, -1}, {-24, 3, -3}, {24, 1, -2}, {24, 3, -4}, {-24,
      2, -1}, {-24, 4, -3}, {24, -2, -2}, {24, -4, -4}, {-24, -1, -1}, {-24,
      -3, -3}, {24, 2, 3}, {24, 4, 1}, {24, 1, 3}, {24, 3, 1}, {-24, 2, 4},
      {-24, 4, 2}, {24, 3, -4}, {24, 1, -2}, {-24, 4, -3}, {-24, 2, -1}, {24,
      1, -4}, {24, 3, -2}, {-24, 2, -3}, {-24, 4, -1}, {24, 4, -4}, {24, 2,
      -2}, {24, 3, -3}, {24, 1, -1}, {24, 2, -4}, {24, 4, -2}, {24, 1, -3},
      {24, 3, -1}, {-24, 2, 3}, {-24, 4, 1}, {-24, 4, -4}, {-24, 2, -2}, {-24,
      3, -3}, {-24, 1, -1}, {-24, 2, -4}, {-24, 4, -2}, {-24, 1, -3}, {-24, 3,
      -1}, {24, 3, -4}, {24, 1, -2}, {-24, 4, -3}, {-24, 2, -1}, {24, 1, -4},
      {24, 3, -2}, {-24, 2, -3}, {-24, 4, -1}, {-24, -2, -3}, {-24, -4, -1},
      {24, -2, -4}, {24, -4, -2}, {-24, -1, -3}, {-24, -3, -1}, {24, -2, -3},
      {24, -4, -1}};

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
void PY8MEs_R8_P20_sm_qq_wpqq::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P20_sm_qq_wpqq': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R8_P20_sm_qq_wpqq::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R8_P20_sm_qq_wpqq::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R8_P20_sm_qq_wpqq::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R8_P20_sm_qq_wpqq::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R8_P20_sm_qq_wpqq::initProc() 
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
  jamp2 = vector < vec_double > (44); 
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
  all_results = vector < vec_vec_double > (44); 
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
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R8_P20_sm_qq_wpqq::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->ZERO; 
  mME[2] = pars->mdl_MW; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->ZERO; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R8_P20_sm_qq_wpqq::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R8_P20_sm_qq_wpqq::getMasses() 
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
void PY8MEs_R8_P20_sm_qq_wpqq::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R8_P20_sm_qq_wpqq': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R8_P20_sm_qq_wpqq_exception; 
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

double PY8MEs_R8_P20_sm_qq_wpqq::sigmaKin() 
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

    if (proc_ID == 0)
      t = matrix_8_uu_wpud(); 
    if (proc_ID == 1)
      t = matrix_8_ud_wpdd(); 
    if (proc_ID == 2)
      t = matrix_8_ud_wmuu(); 
    if (proc_ID == 3)
      t = matrix_8_uux_wpdux(); 
    if (proc_ID == 4)
      t = matrix_8_uux_wmudx(); 
    if (proc_ID == 5)
      t = matrix_8_udx_wpuux(); 
    if (proc_ID == 6)
      t = matrix_8_udx_wpddx(); 
    if (proc_ID == 7)
      t = matrix_8_dd_wmud(); 
    if (proc_ID == 8)
      t = matrix_8_dux_wmuux(); 
    if (proc_ID == 9)
      t = matrix_8_dux_wmddx(); 
    if (proc_ID == 10)
      t = matrix_8_ddx_wpdux(); 
    if (proc_ID == 11)
      t = matrix_8_ddx_wmudx(); 
    if (proc_ID == 12)
      t = matrix_8_uxux_wmuxdx(); 
    if (proc_ID == 13)
      t = matrix_8_uxdx_wpuxux(); 
    if (proc_ID == 14)
      t = matrix_8_uxdx_wmdxdx(); 
    if (proc_ID == 15)
      t = matrix_8_dxdx_wpuxdx(); 
    if (proc_ID == 16)
      t = matrix_8_uc_wpus(); 
    if (proc_ID == 17)
      t = matrix_8_uc_wpcd(); 
    if (proc_ID == 18)
      t = matrix_8_us_wpds(); 
    if (proc_ID == 19)
      t = matrix_8_us_wmuc(); 
    if (proc_ID == 20)
      t = matrix_8_uux_wpscx(); 
    if (proc_ID == 21)
      t = matrix_8_uux_wmcsx(); 
    if (proc_ID == 22)
      t = matrix_8_ucx_wpdcx(); 
    if (proc_ID == 23)
      t = matrix_8_ucx_wmusx(); 
    if (proc_ID == 24)
      t = matrix_8_udx_wpccx(); 
    if (proc_ID == 25)
      t = matrix_8_udx_wpssx(); 
    if (proc_ID == 26)
      t = matrix_8_usx_wpucx(); 
    if (proc_ID == 27)
      t = matrix_8_usx_wpdsx(); 
    if (proc_ID == 28)
      t = matrix_8_ds_wmus(); 
    if (proc_ID == 29)
      t = matrix_8_ds_wmcd(); 
    if (proc_ID == 30)
      t = matrix_8_dux_wmccx(); 
    if (proc_ID == 31)
      t = matrix_8_dux_wmssx(); 
    if (proc_ID == 32)
      t = matrix_8_dcx_wmucx(); 
    if (proc_ID == 33)
      t = matrix_8_dcx_wmdsx(); 
    if (proc_ID == 34)
      t = matrix_8_ddx_wpscx(); 
    if (proc_ID == 35)
      t = matrix_8_ddx_wmcsx(); 
    if (proc_ID == 36)
      t = matrix_8_dsx_wpdcx(); 
    if (proc_ID == 37)
      t = matrix_8_dsx_wmusx(); 
    if (proc_ID == 38)
      t = matrix_8_uxcx_wmuxsx(); 
    if (proc_ID == 39)
      t = matrix_8_uxcx_wmcxdx(); 
    if (proc_ID == 40)
      t = matrix_8_uxsx_wpuxcx(); 
    if (proc_ID == 41)
      t = matrix_8_uxsx_wmdxsx(); 
    if (proc_ID == 42)
      t = matrix_8_dxsx_wpuxsx(); 
    if (proc_ID == 43)
      t = matrix_8_dxsx_wpcxdx(); 

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

void PY8MEs_R8_P20_sm_qq_wpqq::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  vxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  FFV2_2(w[0], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[5]); 
  FFV1P0_3(w[1], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[1], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[7]); 
  FFV2_5_3(w[1], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[8]);
  FFV2_3(w[1], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[9]); 
  FFV1P0_3(w[0], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[10]); 
  FFV2_2(w[1], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[11]); 
  FFV1P0_3(w[0], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[12]); 
  FFV2_5_3(w[0], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[13]);
  FFV2_1(w[4], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[14]); 
  FFV2_3(w[0], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[15]); 
  FFV1P0_3(w[1], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[16]); 
  FFV2_3_3(w[1], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[17]);
  FFV1P0_3(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[18]); 
  FFV1P0_3(w[1], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[19]); 
  FFV2_3_3(w[1], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[20]);
  FFV2_3(w[0], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[21]); 
  FFV2_1(w[3], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[22]); 
  FFV1P0_3(w[0], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[23]); 
  FFV1P0_3(w[0], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[24]); 
  FFV2_5_3(w[0], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[25]);
  FFV2_3(w[1], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[26]); 
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[27]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[28]); 
  FFV1P0_3(w[28], w[27], pars->GC_2, pars->ZERO, pars->ZERO, w[29]); 
  FFV1P0_3(w[28], w[27], pars->GC_11, pars->ZERO, pars->ZERO, w[30]); 
  FFV2_5_3(w[28], w[27], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[31]);
  FFV2_3(w[28], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[32]); 
  FFV1P0_3(w[0], w[27], pars->GC_2, pars->ZERO, pars->ZERO, w[33]); 
  FFV2_2(w[28], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[34]); 
  FFV1P0_3(w[0], w[27], pars->GC_11, pars->ZERO, pars->ZERO, w[35]); 
  FFV2_5_3(w[0], w[27], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[36]);
  FFV2_3(w[28], w[27], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[37]); 
  FFV2_1(w[27], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[38]); 
  FFV1P0_3(w[28], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[39]); 
  FFV1P0_3(w[28], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[40]); 
  FFV2_5_3(w[28], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[41]);
  FFV2_3(w[0], w[27], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[42]); 
  FFV1P0_3(w[28], w[27], pars->GC_1, pars->ZERO, pars->ZERO, w[43]); 
  FFV2_3_3(w[28], w[27], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[44]);
  FFV1P0_3(w[28], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[45]); 
  FFV2_3_3(w[28], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[46]);
  FFV1P0_3(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[47]); 
  FFV2_3_3(w[0], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[48]);
  FFV1P0_3(w[0], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[49]); 
  FFV2_3_3(w[0], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[50]);
  FFV1P0_3(w[0], w[27], pars->GC_1, pars->ZERO, pars->ZERO, w[51]); 
  FFV2_3_3(w[0], w[27], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[52]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[53]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[54]); 
  FFV1P0_3(w[54], w[53], pars->GC_2, pars->ZERO, pars->ZERO, w[55]); 
  FFV1P0_3(w[54], w[53], pars->GC_11, pars->ZERO, pars->ZERO, w[56]); 
  FFV2_5_3(w[54], w[53], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[57]);
  FFV1P0_3(w[54], w[27], pars->GC_2, pars->ZERO, pars->ZERO, w[58]); 
  FFV1P0_3(w[54], w[27], pars->GC_11, pars->ZERO, pars->ZERO, w[59]); 
  FFV2_5_3(w[54], w[27], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[60]);
  FFV2_3(w[28], w[53], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[61]); 
  FFV2_1(w[53], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[62]); 
  FFV2_2(w[54], w[2], pars->GC_100, pars->ZERO, pars->ZERO, w[63]); 
  FFV1P0_3(w[28], w[53], pars->GC_2, pars->ZERO, pars->ZERO, w[64]); 
  FFV1P0_3(w[28], w[53], pars->GC_11, pars->ZERO, pars->ZERO, w[65]); 
  FFV2_5_3(w[28], w[53], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[66]);
  FFV2_3(w[54], w[27], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[67]); 
  FFV2_3(w[54], w[53], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[68]); 
  FFV1P0_3(w[54], w[27], pars->GC_1, pars->ZERO, pars->ZERO, w[69]); 
  FFV2_3_3(w[54], w[27], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[70]);
  FFV1P0_3(w[28], w[53], pars->GC_1, pars->ZERO, pars->ZERO, w[71]); 
  FFV2_3_3(w[28], w[53], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[72]);

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[5], w[4], w[6], pars->GC_1, amp[0]); 
  FFV1_0(w[5], w[4], w[7], pars->GC_11, amp[1]); 
  FFV2_3_0(w[5], w[4], w[8], pars->GC_50, pars->GC_58, amp[2]); 
  FFV2_0(w[5], w[3], w[9], pars->GC_100, amp[3]); 
  FFV1_0(w[11], w[4], w[10], pars->GC_1, amp[4]); 
  FFV1_0(w[11], w[4], w[12], pars->GC_11, amp[5]); 
  FFV2_3_0(w[11], w[4], w[13], pars->GC_50, pars->GC_58, amp[6]); 
  VVV1_0(w[10], w[9], w[2], pars->GC_4, amp[7]); 
  VVV1_0(w[9], w[2], w[13], pars->GC_53, amp[8]); 
  FFV1_0(w[1], w[14], w[10], pars->GC_2, amp[9]); 
  FFV1_0(w[1], w[14], w[12], pars->GC_11, amp[10]); 
  FFV2_5_0(w[1], w[14], w[13], pars->GC_51, pars->GC_58, amp[11]); 
  FFV2_0(w[11], w[3], w[15], pars->GC_100, amp[12]); 
  VVV1_0(w[6], w[15], w[2], pars->GC_4, amp[13]); 
  VVV1_0(w[15], w[2], w[8], pars->GC_53, amp[14]); 
  FFV1_0(w[0], w[14], w[6], pars->GC_2, amp[15]); 
  FFV1_0(w[0], w[14], w[7], pars->GC_11, amp[16]); 
  FFV2_5_0(w[0], w[14], w[8], pars->GC_51, pars->GC_58, amp[17]); 
  FFV1_0(w[5], w[4], w[16], pars->GC_1, amp[18]); 
  FFV2_3_0(w[5], w[4], w[17], pars->GC_50, pars->GC_58, amp[19]); 
  FFV1_0(w[5], w[3], w[18], pars->GC_1, amp[20]); 
  FFV1_0(w[5], w[3], w[19], pars->GC_11, amp[21]); 
  FFV2_3_0(w[5], w[3], w[20], pars->GC_50, pars->GC_58, amp[22]); 
  VVV1_0(w[18], w[21], w[2], pars->GC_4, amp[23]); 
  VVV1_0(w[21], w[2], w[20], pars->GC_53, amp[24]); 
  FFV2_0(w[1], w[14], w[21], pars->GC_100, amp[25]); 
  VVV1_0(w[16], w[15], w[2], pars->GC_4, amp[26]); 
  VVV1_0(w[15], w[2], w[17], pars->GC_53, amp[27]); 
  FFV2_0(w[1], w[22], w[15], pars->GC_100, amp[28]); 
  FFV1_0(w[0], w[14], w[16], pars->GC_2, amp[29]); 
  FFV1_0(w[0], w[14], w[7], pars->GC_11, amp[30]); 
  FFV2_5_0(w[0], w[14], w[17], pars->GC_51, pars->GC_58, amp[31]); 
  FFV1_0(w[0], w[22], w[18], pars->GC_2, amp[32]); 
  FFV1_0(w[0], w[22], w[19], pars->GC_11, amp[33]); 
  FFV2_5_0(w[0], w[22], w[20], pars->GC_51, pars->GC_58, amp[34]); 
  FFV1_0(w[11], w[4], w[10], pars->GC_2, amp[35]); 
  FFV1_0(w[11], w[4], w[12], pars->GC_11, amp[36]); 
  FFV2_5_0(w[11], w[4], w[13], pars->GC_51, pars->GC_58, amp[37]); 
  VVV1_0(w[10], w[2], w[9], pars->GC_4, amp[38]); 
  VVV1_0(w[2], w[9], w[13], pars->GC_53, amp[39]); 
  FFV1_0(w[1], w[14], w[10], pars->GC_1, amp[40]); 
  FFV1_0(w[1], w[14], w[12], pars->GC_11, amp[41]); 
  FFV2_3_0(w[1], w[14], w[13], pars->GC_50, pars->GC_58, amp[42]); 
  FFV1_0(w[11], w[3], w[23], pars->GC_2, amp[43]); 
  FFV1_0(w[11], w[3], w[24], pars->GC_11, amp[44]); 
  FFV2_5_0(w[11], w[3], w[25], pars->GC_51, pars->GC_58, amp[45]); 
  VVV1_0(w[23], w[2], w[26], pars->GC_4, amp[46]); 
  VVV1_0(w[2], w[26], w[25], pars->GC_53, amp[47]); 
  FFV1_0(w[1], w[22], w[23], pars->GC_1, amp[48]); 
  FFV1_0(w[1], w[22], w[24], pars->GC_11, amp[49]); 
  FFV2_3_0(w[1], w[22], w[25], pars->GC_50, pars->GC_58, amp[50]); 
  FFV2_0(w[0], w[14], w[26], pars->GC_100, amp[51]); 
  FFV2_0(w[0], w[22], w[9], pars->GC_100, amp[52]); 
  FFV1_0(w[5], w[3], w[29], pars->GC_1, amp[53]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[54]); 
  FFV2_3_0(w[5], w[3], w[31], pars->GC_50, pars->GC_58, amp[55]); 
  FFV2_0(w[5], w[27], w[32], pars->GC_100, amp[56]); 
  FFV1_0(w[34], w[3], w[33], pars->GC_1, amp[57]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[58]); 
  FFV2_3_0(w[34], w[3], w[36], pars->GC_50, pars->GC_58, amp[59]); 
  VVV1_0(w[33], w[32], w[2], pars->GC_4, amp[60]); 
  VVV1_0(w[32], w[2], w[36], pars->GC_53, amp[61]); 
  FFV1_0(w[28], w[22], w[33], pars->GC_2, amp[62]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[63]); 
  FFV2_5_0(w[28], w[22], w[36], pars->GC_51, pars->GC_58, amp[64]); 
  FFV2_0(w[34], w[27], w[21], pars->GC_100, amp[65]); 
  VVV1_0(w[29], w[21], w[2], pars->GC_4, amp[66]); 
  VVV1_0(w[21], w[2], w[31], pars->GC_53, amp[67]); 
  FFV1_0(w[0], w[22], w[29], pars->GC_2, amp[68]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[69]); 
  FFV2_5_0(w[0], w[22], w[31], pars->GC_51, pars->GC_58, amp[70]); 
  FFV1_0(w[34], w[3], w[33], pars->GC_2, amp[71]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[72]); 
  FFV2_5_0(w[34], w[3], w[36], pars->GC_51, pars->GC_58, amp[73]); 
  VVV1_0(w[33], w[2], w[32], pars->GC_4, amp[74]); 
  VVV1_0(w[2], w[32], w[36], pars->GC_53, amp[75]); 
  FFV1_0(w[28], w[22], w[33], pars->GC_1, amp[76]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[77]); 
  FFV2_3_0(w[28], w[22], w[36], pars->GC_50, pars->GC_58, amp[78]); 
  FFV1_0(w[34], w[27], w[10], pars->GC_2, amp[79]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[80]); 
  FFV2_5_0(w[34], w[27], w[13], pars->GC_51, pars->GC_58, amp[81]); 
  VVV1_0(w[10], w[2], w[37], pars->GC_4, amp[82]); 
  VVV1_0(w[2], w[37], w[13], pars->GC_53, amp[83]); 
  FFV1_0(w[28], w[38], w[10], pars->GC_1, amp[84]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[85]); 
  FFV2_3_0(w[28], w[38], w[13], pars->GC_50, pars->GC_58, amp[86]); 
  FFV2_0(w[0], w[22], w[37], pars->GC_100, amp[87]); 
  FFV2_0(w[0], w[38], w[32], pars->GC_100, amp[88]); 
  FFV1_0(w[5], w[27], w[39], pars->GC_1, amp[89]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[90]); 
  FFV2_3_0(w[5], w[27], w[41], pars->GC_50, pars->GC_58, amp[91]); 
  FFV2_0(w[5], w[3], w[37], pars->GC_100, amp[92]); 
  FFV1_0(w[34], w[27], w[10], pars->GC_1, amp[93]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[94]); 
  FFV2_3_0(w[34], w[27], w[13], pars->GC_50, pars->GC_58, amp[95]); 
  VVV1_0(w[10], w[37], w[2], pars->GC_4, amp[96]); 
  VVV1_0(w[37], w[2], w[13], pars->GC_53, amp[97]); 
  FFV1_0(w[28], w[38], w[10], pars->GC_2, amp[98]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[99]); 
  FFV2_5_0(w[28], w[38], w[13], pars->GC_51, pars->GC_58, amp[100]); 
  FFV2_0(w[34], w[3], w[42], pars->GC_100, amp[101]); 
  VVV1_0(w[39], w[42], w[2], pars->GC_4, amp[102]); 
  VVV1_0(w[42], w[2], w[41], pars->GC_53, amp[103]); 
  FFV1_0(w[0], w[38], w[39], pars->GC_2, amp[104]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[105]); 
  FFV2_5_0(w[0], w[38], w[41], pars->GC_51, pars->GC_58, amp[106]); 
  FFV1_0(w[5], w[3], w[43], pars->GC_1, amp[107]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[108]); 
  FFV2_3_0(w[5], w[3], w[44], pars->GC_50, pars->GC_58, amp[109]); 
  FFV1_0(w[5], w[27], w[45], pars->GC_1, amp[110]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[111]); 
  FFV2_3_0(w[5], w[27], w[46], pars->GC_50, pars->GC_58, amp[112]); 
  VVV1_0(w[45], w[42], w[2], pars->GC_4, amp[113]); 
  VVV1_0(w[42], w[2], w[46], pars->GC_53, amp[114]); 
  FFV2_0(w[28], w[22], w[42], pars->GC_100, amp[115]); 
  VVV1_0(w[43], w[21], w[2], pars->GC_4, amp[116]); 
  VVV1_0(w[21], w[2], w[44], pars->GC_53, amp[117]); 
  FFV2_0(w[28], w[38], w[21], pars->GC_100, amp[118]); 
  FFV1_0(w[0], w[22], w[43], pars->GC_2, amp[119]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[120]); 
  FFV2_5_0(w[0], w[22], w[44], pars->GC_51, pars->GC_58, amp[121]); 
  FFV1_0(w[0], w[38], w[45], pars->GC_2, amp[122]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[123]); 
  FFV2_5_0(w[0], w[38], w[46], pars->GC_51, pars->GC_58, amp[124]); 
  FFV2_0(w[5], w[4], w[26], pars->GC_100, amp[125]); 
  FFV1_0(w[5], w[3], w[18], pars->GC_2, amp[126]); 
  FFV1_0(w[5], w[3], w[19], pars->GC_11, amp[127]); 
  FFV2_5_0(w[5], w[3], w[20], pars->GC_51, pars->GC_58, amp[128]); 
  FFV2_0(w[11], w[4], w[21], pars->GC_100, amp[129]); 
  VVV1_0(w[18], w[2], w[21], pars->GC_4, amp[130]); 
  VVV1_0(w[2], w[21], w[20], pars->GC_53, amp[131]); 
  FFV1_0(w[11], w[3], w[47], pars->GC_2, amp[132]); 
  FFV1_0(w[11], w[3], w[24], pars->GC_11, amp[133]); 
  FFV2_5_0(w[11], w[3], w[48], pars->GC_51, pars->GC_58, amp[134]); 
  VVV1_0(w[47], w[2], w[26], pars->GC_4, amp[135]); 
  VVV1_0(w[2], w[26], w[48], pars->GC_53, amp[136]); 
  FFV1_0(w[1], w[22], w[47], pars->GC_1, amp[137]); 
  FFV1_0(w[1], w[22], w[24], pars->GC_11, amp[138]); 
  FFV2_3_0(w[1], w[22], w[48], pars->GC_50, pars->GC_58, amp[139]); 
  FFV1_0(w[0], w[22], w[18], pars->GC_1, amp[140]); 
  FFV1_0(w[0], w[22], w[19], pars->GC_11, amp[141]); 
  FFV2_3_0(w[0], w[22], w[20], pars->GC_50, pars->GC_58, amp[142]); 
  FFV1_0(w[5], w[3], w[29], pars->GC_2, amp[143]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[144]); 
  FFV2_5_0(w[5], w[3], w[31], pars->GC_51, pars->GC_58, amp[145]); 
  VVV1_0(w[29], w[2], w[21], pars->GC_4, amp[146]); 
  VVV1_0(w[2], w[21], w[31], pars->GC_53, amp[147]); 
  FFV1_0(w[0], w[22], w[29], pars->GC_1, amp[148]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[149]); 
  FFV2_3_0(w[0], w[22], w[31], pars->GC_50, pars->GC_58, amp[150]); 
  FFV1_0(w[5], w[27], w[39], pars->GC_2, amp[151]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[152]); 
  FFV2_5_0(w[5], w[27], w[41], pars->GC_51, pars->GC_58, amp[153]); 
  VVV1_0(w[39], w[2], w[42], pars->GC_4, amp[154]); 
  VVV1_0(w[2], w[42], w[41], pars->GC_53, amp[155]); 
  FFV1_0(w[0], w[38], w[39], pars->GC_1, amp[156]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[157]); 
  FFV2_3_0(w[0], w[38], w[41], pars->GC_50, pars->GC_58, amp[158]); 
  FFV2_0(w[28], w[22], w[42], pars->GC_100, amp[159]); 
  FFV2_0(w[28], w[38], w[21], pars->GC_100, amp[160]); 
  FFV2_0(w[5], w[3], w[37], pars->GC_100, amp[161]); 
  FFV1_0(w[5], w[27], w[45], pars->GC_2, amp[162]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[163]); 
  FFV2_5_0(w[5], w[27], w[46], pars->GC_51, pars->GC_58, amp[164]); 
  FFV2_0(w[34], w[3], w[42], pars->GC_100, amp[165]); 
  VVV1_0(w[45], w[2], w[42], pars->GC_4, amp[166]); 
  VVV1_0(w[2], w[42], w[46], pars->GC_53, amp[167]); 
  FFV1_0(w[34], w[27], w[49], pars->GC_2, amp[168]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[169]); 
  FFV2_5_0(w[34], w[27], w[50], pars->GC_51, pars->GC_58, amp[170]); 
  VVV1_0(w[49], w[2], w[37], pars->GC_4, amp[171]); 
  VVV1_0(w[2], w[37], w[50], pars->GC_53, amp[172]); 
  FFV1_0(w[28], w[38], w[49], pars->GC_1, amp[173]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[174]); 
  FFV2_3_0(w[28], w[38], w[50], pars->GC_50, pars->GC_58, amp[175]); 
  FFV1_0(w[0], w[38], w[45], pars->GC_1, amp[176]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[177]); 
  FFV2_3_0(w[0], w[38], w[46], pars->GC_50, pars->GC_58, amp[178]); 
  FFV1_0(w[34], w[3], w[51], pars->GC_1, amp[179]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[180]); 
  FFV2_3_0(w[34], w[3], w[52], pars->GC_50, pars->GC_58, amp[181]); 
  FFV1_0(w[34], w[27], w[49], pars->GC_1, amp[182]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[183]); 
  FFV2_3_0(w[34], w[27], w[50], pars->GC_50, pars->GC_58, amp[184]); 
  VVV1_0(w[49], w[37], w[2], pars->GC_4, amp[185]); 
  VVV1_0(w[37], w[2], w[50], pars->GC_53, amp[186]); 
  FFV2_0(w[0], w[22], w[37], pars->GC_100, amp[187]); 
  VVV1_0(w[51], w[32], w[2], pars->GC_4, amp[188]); 
  VVV1_0(w[32], w[2], w[52], pars->GC_53, amp[189]); 
  FFV2_0(w[0], w[38], w[32], pars->GC_100, amp[190]); 
  FFV1_0(w[28], w[22], w[51], pars->GC_2, amp[191]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[192]); 
  FFV2_5_0(w[28], w[22], w[52], pars->GC_51, pars->GC_58, amp[193]); 
  FFV1_0(w[28], w[38], w[49], pars->GC_2, amp[194]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[195]); 
  FFV2_5_0(w[28], w[38], w[50], pars->GC_51, pars->GC_58, amp[196]); 
  FFV2_0(w[5], w[27], w[32], pars->GC_100, amp[197]); 
  FFV1_0(w[5], w[3], w[43], pars->GC_2, amp[198]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[199]); 
  FFV2_5_0(w[5], w[3], w[44], pars->GC_51, pars->GC_58, amp[200]); 
  FFV2_0(w[34], w[27], w[21], pars->GC_100, amp[201]); 
  VVV1_0(w[43], w[2], w[21], pars->GC_4, amp[202]); 
  VVV1_0(w[2], w[21], w[44], pars->GC_53, amp[203]); 
  FFV1_0(w[34], w[3], w[51], pars->GC_2, amp[204]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[205]); 
  FFV2_5_0(w[34], w[3], w[52], pars->GC_51, pars->GC_58, amp[206]); 
  VVV1_0(w[51], w[2], w[32], pars->GC_4, amp[207]); 
  VVV1_0(w[2], w[32], w[52], pars->GC_53, amp[208]); 
  FFV1_0(w[28], w[22], w[51], pars->GC_1, amp[209]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[210]); 
  FFV2_3_0(w[28], w[22], w[52], pars->GC_50, pars->GC_58, amp[211]); 
  FFV1_0(w[0], w[22], w[43], pars->GC_1, amp[212]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[213]); 
  FFV2_3_0(w[0], w[22], w[44], pars->GC_50, pars->GC_58, amp[214]); 
  FFV1_0(w[34], w[27], w[55], pars->GC_2, amp[215]); 
  FFV1_0(w[34], w[27], w[56], pars->GC_11, amp[216]); 
  FFV2_5_0(w[34], w[27], w[57], pars->GC_51, pars->GC_58, amp[217]); 
  VVV1_0(w[55], w[2], w[37], pars->GC_4, amp[218]); 
  VVV1_0(w[2], w[37], w[57], pars->GC_53, amp[219]); 
  FFV1_0(w[28], w[38], w[55], pars->GC_1, amp[220]); 
  FFV1_0(w[28], w[38], w[56], pars->GC_11, amp[221]); 
  FFV2_3_0(w[28], w[38], w[57], pars->GC_50, pars->GC_58, amp[222]); 
  FFV1_0(w[34], w[53], w[58], pars->GC_2, amp[223]); 
  FFV1_0(w[34], w[53], w[59], pars->GC_11, amp[224]); 
  FFV2_5_0(w[34], w[53], w[60], pars->GC_51, pars->GC_58, amp[225]); 
  VVV1_0(w[58], w[2], w[61], pars->GC_4, amp[226]); 
  VVV1_0(w[2], w[61], w[60], pars->GC_53, amp[227]); 
  FFV1_0(w[28], w[62], w[58], pars->GC_1, amp[228]); 
  FFV1_0(w[28], w[62], w[59], pars->GC_11, amp[229]); 
  FFV2_3_0(w[28], w[62], w[60], pars->GC_50, pars->GC_58, amp[230]); 
  FFV2_0(w[54], w[38], w[61], pars->GC_100, amp[231]); 
  FFV2_0(w[54], w[62], w[37], pars->GC_100, amp[232]); 
  FFV1_0(w[63], w[27], w[64], pars->GC_1, amp[233]); 
  FFV1_0(w[63], w[27], w[65], pars->GC_11, amp[234]); 
  FFV2_3_0(w[63], w[27], w[66], pars->GC_50, pars->GC_58, amp[235]); 
  FFV2_0(w[63], w[53], w[37], pars->GC_100, amp[236]); 
  FFV1_0(w[34], w[27], w[55], pars->GC_1, amp[237]); 
  FFV1_0(w[34], w[27], w[56], pars->GC_11, amp[238]); 
  FFV2_3_0(w[34], w[27], w[57], pars->GC_50, pars->GC_58, amp[239]); 
  VVV1_0(w[55], w[37], w[2], pars->GC_4, amp[240]); 
  VVV1_0(w[37], w[2], w[57], pars->GC_53, amp[241]); 
  FFV1_0(w[28], w[38], w[55], pars->GC_2, amp[242]); 
  FFV1_0(w[28], w[38], w[56], pars->GC_11, amp[243]); 
  FFV2_5_0(w[28], w[38], w[57], pars->GC_51, pars->GC_58, amp[244]); 
  FFV2_0(w[34], w[53], w[67], pars->GC_100, amp[245]); 
  VVV1_0(w[64], w[67], w[2], pars->GC_4, amp[246]); 
  VVV1_0(w[67], w[2], w[66], pars->GC_53, amp[247]); 
  FFV1_0(w[54], w[38], w[64], pars->GC_2, amp[248]); 
  FFV1_0(w[54], w[38], w[65], pars->GC_11, amp[249]); 
  FFV2_5_0(w[54], w[38], w[66], pars->GC_51, pars->GC_58, amp[250]); 
  FFV2_0(w[63], w[27], w[61], pars->GC_100, amp[251]); 
  FFV1_0(w[63], w[53], w[43], pars->GC_2, amp[252]); 
  FFV1_0(w[63], w[53], w[30], pars->GC_11, amp[253]); 
  FFV2_5_0(w[63], w[53], w[44], pars->GC_51, pars->GC_58, amp[254]); 
  FFV2_0(w[34], w[27], w[68], pars->GC_100, amp[255]); 
  VVV1_0(w[43], w[2], w[68], pars->GC_4, amp[256]); 
  VVV1_0(w[2], w[68], w[44], pars->GC_53, amp[257]); 
  FFV1_0(w[34], w[53], w[69], pars->GC_2, amp[258]); 
  FFV1_0(w[34], w[53], w[59], pars->GC_11, amp[259]); 
  FFV2_5_0(w[34], w[53], w[70], pars->GC_51, pars->GC_58, amp[260]); 
  VVV1_0(w[69], w[2], w[61], pars->GC_4, amp[261]); 
  VVV1_0(w[2], w[61], w[70], pars->GC_53, amp[262]); 
  FFV1_0(w[28], w[62], w[69], pars->GC_1, amp[263]); 
  FFV1_0(w[28], w[62], w[59], pars->GC_11, amp[264]); 
  FFV2_3_0(w[28], w[62], w[70], pars->GC_50, pars->GC_58, amp[265]); 
  FFV1_0(w[54], w[62], w[43], pars->GC_1, amp[266]); 
  FFV1_0(w[54], w[62], w[30], pars->GC_11, amp[267]); 
  FFV2_3_0(w[54], w[62], w[44], pars->GC_50, pars->GC_58, amp[268]); 
  FFV1_0(w[63], w[27], w[71], pars->GC_1, amp[269]); 
  FFV1_0(w[63], w[27], w[65], pars->GC_11, amp[270]); 
  FFV2_3_0(w[63], w[27], w[72], pars->GC_50, pars->GC_58, amp[271]); 
  FFV1_0(w[63], w[53], w[43], pars->GC_1, amp[272]); 
  FFV1_0(w[63], w[53], w[30], pars->GC_11, amp[273]); 
  FFV2_3_0(w[63], w[53], w[44], pars->GC_50, pars->GC_58, amp[274]); 
  VVV1_0(w[43], w[68], w[2], pars->GC_4, amp[275]); 
  VVV1_0(w[68], w[2], w[44], pars->GC_53, amp[276]); 
  FFV2_0(w[28], w[38], w[68], pars->GC_100, amp[277]); 
  VVV1_0(w[71], w[67], w[2], pars->GC_4, amp[278]); 
  VVV1_0(w[67], w[2], w[72], pars->GC_53, amp[279]); 
  FFV2_0(w[28], w[62], w[67], pars->GC_100, amp[280]); 
  FFV1_0(w[54], w[38], w[71], pars->GC_2, amp[281]); 
  FFV1_0(w[54], w[38], w[65], pars->GC_11, amp[282]); 
  FFV2_5_0(w[54], w[38], w[72], pars->GC_51, pars->GC_58, amp[283]); 
  FFV1_0(w[54], w[62], w[43], pars->GC_2, amp[284]); 
  FFV1_0(w[54], w[62], w[30], pars->GC_11, amp[285]); 
  FFV2_5_0(w[54], w[62], w[44], pars->GC_51, pars->GC_58, amp[286]); 
  FFV2_0(w[5], w[3], w[9], pars->GC_100, amp[287]); 
  FFV1_0(w[11], w[4], w[10], pars->GC_1, amp[288]); 
  FFV1_0(w[11], w[4], w[12], pars->GC_11, amp[289]); 
  FFV2_3_0(w[11], w[4], w[13], pars->GC_50, pars->GC_58, amp[290]); 
  VVV1_0(w[10], w[9], w[2], pars->GC_4, amp[291]); 
  VVV1_0(w[9], w[2], w[13], pars->GC_53, amp[292]); 
  FFV1_0(w[1], w[14], w[10], pars->GC_2, amp[293]); 
  FFV1_0(w[1], w[14], w[12], pars->GC_11, amp[294]); 
  FFV2_5_0(w[1], w[14], w[13], pars->GC_51, pars->GC_58, amp[295]); 
  FFV2_0(w[11], w[3], w[15], pars->GC_100, amp[296]); 
  VVV1_0(w[6], w[15], w[2], pars->GC_4, amp[297]); 
  VVV1_0(w[15], w[2], w[8], pars->GC_53, amp[298]); 
  FFV1_0(w[0], w[14], w[6], pars->GC_2, amp[299]); 
  FFV1_0(w[0], w[14], w[7], pars->GC_11, amp[300]); 
  FFV2_5_0(w[0], w[14], w[8], pars->GC_51, pars->GC_58, amp[301]); 
  FFV1_0(w[5], w[3], w[18], pars->GC_1, amp[302]); 
  FFV1_0(w[5], w[3], w[19], pars->GC_11, amp[303]); 
  FFV2_3_0(w[5], w[3], w[20], pars->GC_50, pars->GC_58, amp[304]); 
  VVV1_0(w[18], w[21], w[2], pars->GC_4, amp[305]); 
  VVV1_0(w[21], w[2], w[20], pars->GC_53, amp[306]); 
  FFV2_0(w[1], w[14], w[21], pars->GC_100, amp[307]); 
  FFV1_0(w[0], w[22], w[18], pars->GC_2, amp[308]); 
  FFV1_0(w[0], w[22], w[19], pars->GC_11, amp[309]); 
  FFV2_5_0(w[0], w[22], w[20], pars->GC_51, pars->GC_58, amp[310]); 
  FFV1_0(w[11], w[4], w[10], pars->GC_2, amp[311]); 
  FFV1_0(w[11], w[4], w[12], pars->GC_11, amp[312]); 
  FFV2_5_0(w[11], w[4], w[13], pars->GC_51, pars->GC_58, amp[313]); 
  VVV1_0(w[10], w[2], w[9], pars->GC_4, amp[314]); 
  VVV1_0(w[2], w[9], w[13], pars->GC_53, amp[315]); 
  FFV1_0(w[1], w[14], w[10], pars->GC_1, amp[316]); 
  FFV1_0(w[1], w[14], w[12], pars->GC_11, amp[317]); 
  FFV2_3_0(w[1], w[14], w[13], pars->GC_50, pars->GC_58, amp[318]); 
  FFV2_0(w[0], w[22], w[9], pars->GC_100, amp[319]); 
  FFV2_0(w[5], w[27], w[32], pars->GC_100, amp[320]); 
  FFV1_0(w[34], w[3], w[33], pars->GC_1, amp[321]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[322]); 
  FFV2_3_0(w[34], w[3], w[36], pars->GC_50, pars->GC_58, amp[323]); 
  VVV1_0(w[33], w[32], w[2], pars->GC_4, amp[324]); 
  VVV1_0(w[32], w[2], w[36], pars->GC_53, amp[325]); 
  FFV1_0(w[28], w[22], w[33], pars->GC_2, amp[326]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[327]); 
  FFV2_5_0(w[28], w[22], w[36], pars->GC_51, pars->GC_58, amp[328]); 
  FFV1_0(w[34], w[3], w[33], pars->GC_2, amp[329]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[330]); 
  FFV2_5_0(w[34], w[3], w[36], pars->GC_51, pars->GC_58, amp[331]); 
  VVV1_0(w[33], w[2], w[32], pars->GC_4, amp[332]); 
  VVV1_0(w[2], w[32], w[36], pars->GC_53, amp[333]); 
  FFV1_0(w[28], w[22], w[33], pars->GC_1, amp[334]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[335]); 
  FFV2_3_0(w[28], w[22], w[36], pars->GC_50, pars->GC_58, amp[336]); 
  FFV2_0(w[0], w[38], w[32], pars->GC_100, amp[337]); 
  FFV1_0(w[5], w[3], w[29], pars->GC_1, amp[338]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[339]); 
  FFV2_3_0(w[5], w[3], w[31], pars->GC_50, pars->GC_58, amp[340]); 
  FFV2_0(w[34], w[27], w[21], pars->GC_100, amp[341]); 
  VVV1_0(w[29], w[21], w[2], pars->GC_4, amp[342]); 
  VVV1_0(w[21], w[2], w[31], pars->GC_53, amp[343]); 
  FFV1_0(w[0], w[22], w[29], pars->GC_2, amp[344]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[345]); 
  FFV2_5_0(w[0], w[22], w[31], pars->GC_51, pars->GC_58, amp[346]); 
  FFV1_0(w[34], w[27], w[10], pars->GC_2, amp[347]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[348]); 
  FFV2_5_0(w[34], w[27], w[13], pars->GC_51, pars->GC_58, amp[349]); 
  VVV1_0(w[10], w[2], w[37], pars->GC_4, amp[350]); 
  VVV1_0(w[2], w[37], w[13], pars->GC_53, amp[351]); 
  FFV1_0(w[28], w[38], w[10], pars->GC_1, amp[352]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[353]); 
  FFV2_3_0(w[28], w[38], w[13], pars->GC_50, pars->GC_58, amp[354]); 
  FFV2_0(w[0], w[22], w[37], pars->GC_100, amp[355]); 
  FFV1_0(w[5], w[27], w[39], pars->GC_1, amp[356]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[357]); 
  FFV2_3_0(w[5], w[27], w[41], pars->GC_50, pars->GC_58, amp[358]); 
  FFV2_0(w[34], w[3], w[42], pars->GC_100, amp[359]); 
  VVV1_0(w[39], w[42], w[2], pars->GC_4, amp[360]); 
  VVV1_0(w[42], w[2], w[41], pars->GC_53, amp[361]); 
  FFV1_0(w[0], w[38], w[39], pars->GC_2, amp[362]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[363]); 
  FFV2_5_0(w[0], w[38], w[41], pars->GC_51, pars->GC_58, amp[364]); 
  FFV1_0(w[5], w[27], w[45], pars->GC_1, amp[365]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[366]); 
  FFV2_3_0(w[5], w[27], w[46], pars->GC_50, pars->GC_58, amp[367]); 
  VVV1_0(w[45], w[42], w[2], pars->GC_4, amp[368]); 
  VVV1_0(w[42], w[2], w[46], pars->GC_53, amp[369]); 
  FFV2_0(w[28], w[22], w[42], pars->GC_100, amp[370]); 
  FFV1_0(w[0], w[38], w[45], pars->GC_2, amp[371]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[372]); 
  FFV2_5_0(w[0], w[38], w[46], pars->GC_51, pars->GC_58, amp[373]); 
  FFV2_0(w[5], w[3], w[37], pars->GC_100, amp[374]); 
  FFV1_0(w[34], w[27], w[10], pars->GC_1, amp[375]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[376]); 
  FFV2_3_0(w[34], w[27], w[13], pars->GC_50, pars->GC_58, amp[377]); 
  VVV1_0(w[10], w[37], w[2], pars->GC_4, amp[378]); 
  VVV1_0(w[37], w[2], w[13], pars->GC_53, amp[379]); 
  FFV1_0(w[28], w[38], w[10], pars->GC_2, amp[380]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[381]); 
  FFV2_5_0(w[28], w[38], w[13], pars->GC_51, pars->GC_58, amp[382]); 
  FFV1_0(w[5], w[3], w[43], pars->GC_1, amp[383]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[384]); 
  FFV2_3_0(w[5], w[3], w[44], pars->GC_50, pars->GC_58, amp[385]); 
  VVV1_0(w[43], w[21], w[2], pars->GC_4, amp[386]); 
  VVV1_0(w[21], w[2], w[44], pars->GC_53, amp[387]); 
  FFV2_0(w[28], w[38], w[21], pars->GC_100, amp[388]); 
  FFV1_0(w[0], w[22], w[43], pars->GC_2, amp[389]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[390]); 
  FFV2_5_0(w[0], w[22], w[44], pars->GC_51, pars->GC_58, amp[391]); 
  FFV1_0(w[5], w[3], w[18], pars->GC_2, amp[392]); 
  FFV1_0(w[5], w[3], w[19], pars->GC_11, amp[393]); 
  FFV2_5_0(w[5], w[3], w[20], pars->GC_51, pars->GC_58, amp[394]); 
  FFV2_0(w[11], w[4], w[21], pars->GC_100, amp[395]); 
  VVV1_0(w[18], w[2], w[21], pars->GC_4, amp[396]); 
  VVV1_0(w[2], w[21], w[20], pars->GC_53, amp[397]); 
  FFV1_0(w[0], w[22], w[18], pars->GC_1, amp[398]); 
  FFV1_0(w[0], w[22], w[19], pars->GC_11, amp[399]); 
  FFV2_3_0(w[0], w[22], w[20], pars->GC_50, pars->GC_58, amp[400]); 
  FFV2_0(w[5], w[4], w[26], pars->GC_100, amp[401]); 
  FFV1_0(w[11], w[3], w[47], pars->GC_2, amp[402]); 
  FFV1_0(w[11], w[3], w[24], pars->GC_11, amp[403]); 
  FFV2_5_0(w[11], w[3], w[48], pars->GC_51, pars->GC_58, amp[404]); 
  VVV1_0(w[47], w[2], w[26], pars->GC_4, amp[405]); 
  VVV1_0(w[2], w[26], w[48], pars->GC_53, amp[406]); 
  FFV1_0(w[1], w[22], w[47], pars->GC_1, amp[407]); 
  FFV1_0(w[1], w[22], w[24], pars->GC_11, amp[408]); 
  FFV2_3_0(w[1], w[22], w[48], pars->GC_50, pars->GC_58, amp[409]); 
  FFV1_0(w[5], w[27], w[39], pars->GC_2, amp[410]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[411]); 
  FFV2_5_0(w[5], w[27], w[41], pars->GC_51, pars->GC_58, amp[412]); 
  VVV1_0(w[39], w[2], w[42], pars->GC_4, amp[413]); 
  VVV1_0(w[2], w[42], w[41], pars->GC_53, amp[414]); 
  FFV1_0(w[0], w[38], w[39], pars->GC_1, amp[415]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[416]); 
  FFV2_3_0(w[0], w[38], w[41], pars->GC_50, pars->GC_58, amp[417]); 
  FFV2_0(w[28], w[22], w[42], pars->GC_100, amp[418]); 
  FFV1_0(w[5], w[27], w[45], pars->GC_2, amp[419]); 
  FFV1_0(w[5], w[27], w[40], pars->GC_11, amp[420]); 
  FFV2_5_0(w[5], w[27], w[46], pars->GC_51, pars->GC_58, amp[421]); 
  FFV2_0(w[34], w[3], w[42], pars->GC_100, amp[422]); 
  VVV1_0(w[45], w[2], w[42], pars->GC_4, amp[423]); 
  VVV1_0(w[2], w[42], w[46], pars->GC_53, amp[424]); 
  FFV1_0(w[0], w[38], w[45], pars->GC_1, amp[425]); 
  FFV1_0(w[0], w[38], w[40], pars->GC_11, amp[426]); 
  FFV2_3_0(w[0], w[38], w[46], pars->GC_50, pars->GC_58, amp[427]); 
  FFV1_0(w[5], w[3], w[29], pars->GC_2, amp[428]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[429]); 
  FFV2_5_0(w[5], w[3], w[31], pars->GC_51, pars->GC_58, amp[430]); 
  VVV1_0(w[29], w[2], w[21], pars->GC_4, amp[431]); 
  VVV1_0(w[2], w[21], w[31], pars->GC_53, amp[432]); 
  FFV1_0(w[0], w[22], w[29], pars->GC_1, amp[433]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[434]); 
  FFV2_3_0(w[0], w[22], w[31], pars->GC_50, pars->GC_58, amp[435]); 
  FFV2_0(w[28], w[38], w[21], pars->GC_100, amp[436]); 
  FFV2_0(w[5], w[3], w[37], pars->GC_100, amp[437]); 
  FFV1_0(w[34], w[27], w[49], pars->GC_2, amp[438]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[439]); 
  FFV2_5_0(w[34], w[27], w[50], pars->GC_51, pars->GC_58, amp[440]); 
  VVV1_0(w[49], w[2], w[37], pars->GC_4, amp[441]); 
  VVV1_0(w[2], w[37], w[50], pars->GC_53, amp[442]); 
  FFV1_0(w[28], w[38], w[49], pars->GC_1, amp[443]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[444]); 
  FFV2_3_0(w[28], w[38], w[50], pars->GC_50, pars->GC_58, amp[445]); 
  FFV1_0(w[34], w[3], w[51], pars->GC_1, amp[446]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[447]); 
  FFV2_3_0(w[34], w[3], w[52], pars->GC_50, pars->GC_58, amp[448]); 
  VVV1_0(w[51], w[32], w[2], pars->GC_4, amp[449]); 
  VVV1_0(w[32], w[2], w[52], pars->GC_53, amp[450]); 
  FFV2_0(w[0], w[38], w[32], pars->GC_100, amp[451]); 
  FFV1_0(w[28], w[22], w[51], pars->GC_2, amp[452]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[453]); 
  FFV2_5_0(w[28], w[22], w[52], pars->GC_51, pars->GC_58, amp[454]); 
  FFV2_0(w[5], w[27], w[32], pars->GC_100, amp[455]); 
  FFV1_0(w[34], w[3], w[51], pars->GC_2, amp[456]); 
  FFV1_0(w[34], w[3], w[35], pars->GC_11, amp[457]); 
  FFV2_5_0(w[34], w[3], w[52], pars->GC_51, pars->GC_58, amp[458]); 
  VVV1_0(w[51], w[2], w[32], pars->GC_4, amp[459]); 
  VVV1_0(w[2], w[32], w[52], pars->GC_53, amp[460]); 
  FFV1_0(w[28], w[22], w[51], pars->GC_1, amp[461]); 
  FFV1_0(w[28], w[22], w[35], pars->GC_11, amp[462]); 
  FFV2_3_0(w[28], w[22], w[52], pars->GC_50, pars->GC_58, amp[463]); 
  FFV1_0(w[34], w[27], w[49], pars->GC_1, amp[464]); 
  FFV1_0(w[34], w[27], w[12], pars->GC_11, amp[465]); 
  FFV2_3_0(w[34], w[27], w[50], pars->GC_50, pars->GC_58, amp[466]); 
  VVV1_0(w[49], w[37], w[2], pars->GC_4, amp[467]); 
  VVV1_0(w[37], w[2], w[50], pars->GC_53, amp[468]); 
  FFV2_0(w[0], w[22], w[37], pars->GC_100, amp[469]); 
  FFV1_0(w[28], w[38], w[49], pars->GC_2, amp[470]); 
  FFV1_0(w[28], w[38], w[12], pars->GC_11, amp[471]); 
  FFV2_5_0(w[28], w[38], w[50], pars->GC_51, pars->GC_58, amp[472]); 
  FFV1_0(w[5], w[3], w[43], pars->GC_2, amp[473]); 
  FFV1_0(w[5], w[3], w[30], pars->GC_11, amp[474]); 
  FFV2_5_0(w[5], w[3], w[44], pars->GC_51, pars->GC_58, amp[475]); 
  FFV2_0(w[34], w[27], w[21], pars->GC_100, amp[476]); 
  VVV1_0(w[43], w[2], w[21], pars->GC_4, amp[477]); 
  VVV1_0(w[2], w[21], w[44], pars->GC_53, amp[478]); 
  FFV1_0(w[0], w[22], w[43], pars->GC_1, amp[479]); 
  FFV1_0(w[0], w[22], w[30], pars->GC_11, amp[480]); 
  FFV2_3_0(w[0], w[22], w[44], pars->GC_50, pars->GC_58, amp[481]); 
  FFV1_0(w[34], w[27], w[55], pars->GC_2, amp[482]); 
  FFV1_0(w[34], w[27], w[56], pars->GC_11, amp[483]); 
  FFV2_5_0(w[34], w[27], w[57], pars->GC_51, pars->GC_58, amp[484]); 
  VVV1_0(w[55], w[2], w[37], pars->GC_4, amp[485]); 
  VVV1_0(w[2], w[37], w[57], pars->GC_53, amp[486]); 
  FFV1_0(w[28], w[38], w[55], pars->GC_1, amp[487]); 
  FFV1_0(w[28], w[38], w[56], pars->GC_11, amp[488]); 
  FFV2_3_0(w[28], w[38], w[57], pars->GC_50, pars->GC_58, amp[489]); 
  FFV2_0(w[54], w[62], w[37], pars->GC_100, amp[490]); 
  FFV1_0(w[34], w[53], w[58], pars->GC_2, amp[491]); 
  FFV1_0(w[34], w[53], w[59], pars->GC_11, amp[492]); 
  FFV2_5_0(w[34], w[53], w[60], pars->GC_51, pars->GC_58, amp[493]); 
  VVV1_0(w[58], w[2], w[61], pars->GC_4, amp[494]); 
  VVV1_0(w[2], w[61], w[60], pars->GC_53, amp[495]); 
  FFV1_0(w[28], w[62], w[58], pars->GC_1, amp[496]); 
  FFV1_0(w[28], w[62], w[59], pars->GC_11, amp[497]); 
  FFV2_3_0(w[28], w[62], w[60], pars->GC_50, pars->GC_58, amp[498]); 
  FFV2_0(w[54], w[38], w[61], pars->GC_100, amp[499]); 
  FFV2_0(w[63], w[53], w[37], pars->GC_100, amp[500]); 
  FFV1_0(w[34], w[27], w[55], pars->GC_1, amp[501]); 
  FFV1_0(w[34], w[27], w[56], pars->GC_11, amp[502]); 
  FFV2_3_0(w[34], w[27], w[57], pars->GC_50, pars->GC_58, amp[503]); 
  VVV1_0(w[55], w[37], w[2], pars->GC_4, amp[504]); 
  VVV1_0(w[37], w[2], w[57], pars->GC_53, amp[505]); 
  FFV1_0(w[28], w[38], w[55], pars->GC_2, amp[506]); 
  FFV1_0(w[28], w[38], w[56], pars->GC_11, amp[507]); 
  FFV2_5_0(w[28], w[38], w[57], pars->GC_51, pars->GC_58, amp[508]); 
  FFV1_0(w[63], w[53], w[43], pars->GC_2, amp[509]); 
  FFV1_0(w[63], w[53], w[30], pars->GC_11, amp[510]); 
  FFV2_5_0(w[63], w[53], w[44], pars->GC_51, pars->GC_58, amp[511]); 
  FFV2_0(w[34], w[27], w[68], pars->GC_100, amp[512]); 
  VVV1_0(w[43], w[2], w[68], pars->GC_4, amp[513]); 
  VVV1_0(w[2], w[68], w[44], pars->GC_53, amp[514]); 
  FFV1_0(w[54], w[62], w[43], pars->GC_1, amp[515]); 
  FFV1_0(w[54], w[62], w[30], pars->GC_11, amp[516]); 
  FFV2_3_0(w[54], w[62], w[44], pars->GC_50, pars->GC_58, amp[517]); 
  FFV1_0(w[63], w[53], w[43], pars->GC_1, amp[518]); 
  FFV1_0(w[63], w[53], w[30], pars->GC_11, amp[519]); 
  FFV2_3_0(w[63], w[53], w[44], pars->GC_50, pars->GC_58, amp[520]); 
  VVV1_0(w[43], w[68], w[2], pars->GC_4, amp[521]); 
  VVV1_0(w[68], w[2], w[44], pars->GC_53, amp[522]); 
  FFV2_0(w[28], w[38], w[68], pars->GC_100, amp[523]); 
  FFV1_0(w[54], w[62], w[43], pars->GC_2, amp[524]); 
  FFV1_0(w[54], w[62], w[30], pars->GC_11, amp[525]); 
  FFV2_5_0(w[54], w[62], w[44], pars->GC_51, pars->GC_58, amp[526]); 
  FFV1_0(w[63], w[27], w[71], pars->GC_1, amp[527]); 
  FFV1_0(w[63], w[27], w[65], pars->GC_11, amp[528]); 
  FFV2_3_0(w[63], w[27], w[72], pars->GC_50, pars->GC_58, amp[529]); 
  VVV1_0(w[71], w[67], w[2], pars->GC_4, amp[530]); 
  VVV1_0(w[67], w[2], w[72], pars->GC_53, amp[531]); 
  FFV2_0(w[28], w[62], w[67], pars->GC_100, amp[532]); 
  FFV1_0(w[54], w[38], w[71], pars->GC_2, amp[533]); 
  FFV1_0(w[54], w[38], w[65], pars->GC_11, amp[534]); 
  FFV2_5_0(w[54], w[38], w[72], pars->GC_51, pars->GC_58, amp[535]); 


}
double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uu_wpud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[1] - amp[3] - amp[4] + 1./6. * amp[5] - amp[6] -
      amp[7] - amp[8] - amp[9] + 1./6. * amp[10] - amp[11] + 1./2. * amp[16];
  jamp[1] = +amp[0] - 1./6. * amp[1] + amp[2] - 1./2. * amp[5] - 1./2. *
      amp[10] + amp[12] + amp[13] + amp[14] + amp[15] - 1./6. * amp[16] +
      amp[17];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ud_wpdd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[1] - amp[20] + 1./6. * amp[21] - amp[22] - amp[23] -
      amp[24] - amp[25] + 1./2. * amp[30] - amp[32] + 1./6. * amp[33] - amp[34];
  jamp[1] = +amp[18] - 1./6. * amp[1] + amp[19] - 1./2. * amp[21] + amp[26] +
      amp[27] + amp[28] + amp[29] - 1./6. * amp[30] + amp[31] - 1./2. * amp[33];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ud_wmuu() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[35] + 1./6. * amp[36] - amp[37] - amp[38] - amp[39] - amp[40]
      + 1./6. * amp[41] - amp[42] + 1./2. * amp[44] + 1./2. * amp[49] - amp[52];
  jamp[1] = -1./2. * amp[36] - 1./2. * amp[41] + amp[43] - 1./6. * amp[44] +
      amp[45] + amp[46] + amp[47] + amp[48] - 1./6. * amp[49] + amp[50] +
      amp[51];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uux_wpdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[54] - amp[56] - amp[57] + 1./6. * amp[58] - amp[59] -
      amp[60] - amp[61] - amp[62] + 1./6. * amp[63] - amp[64] + 1./2. * amp[69];
  jamp[1] = +amp[53] - 1./6. * amp[54] + amp[55] - 1./2. * amp[58] - 1./2. *
      amp[63] + amp[65] + amp[66] + amp[67] + amp[68] - 1./6. * amp[69] +
      amp[70];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uux_wmudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[71] + 1./6. * amp[72] - amp[73] - amp[74] - amp[75] - amp[76]
      + 1./6. * amp[77] - amp[78] + 1./2. * amp[80] + 1./2. * amp[85] - amp[88];
  jamp[1] = -1./2. * amp[72] - 1./2. * amp[77] + amp[79] - 1./6. * amp[80] +
      amp[81] + amp[82] + amp[83] + amp[84] - 1./6. * amp[85] + amp[86] +
      amp[87];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_udx_wpuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[89] + 1./6. * amp[90] - amp[91] + 1./2. * amp[94] + 1./2. *
      amp[99] - amp[101] - amp[102] - amp[103] - amp[104] + 1./6. * amp[105] -
      amp[106];
  jamp[1] = -1./2. * amp[90] + amp[92] + amp[93] - 1./6. * amp[94] + amp[95] +
      amp[96] + amp[97] + amp[98] - 1./6. * amp[99] + amp[100] - 1./2. *
      amp[105];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_udx_wpddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[108] - amp[110] + 1./6. * amp[111] - amp[112] -
      amp[113] - amp[114] - amp[115] + 1./2. * amp[120] - amp[122] + 1./6. *
      amp[123] - amp[124];
  jamp[1] = +amp[107] - 1./6. * amp[108] + amp[109] - 1./2. * amp[111] +
      amp[116] + amp[117] + amp[118] + amp[119] - 1./6. * amp[120] + amp[121] -
      1./2. * amp[123];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dd_wmud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[126] + 1./6. * amp[127] - amp[128] - amp[129] - amp[130] -
      amp[131] + 1./2. * amp[133] + 1./2. * amp[138] - amp[140] + 1./6. *
      amp[141] - amp[142];
  jamp[1] = +amp[125] - 1./2. * amp[127] + amp[132] - 1./6. * amp[133] +
      amp[134] + amp[135] + amp[136] + amp[137] - 1./6. * amp[138] + amp[139] -
      1./2. * amp[141];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dux_wmuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[144] + 1./2. * amp[149] - amp[151] + 1./6. * amp[152]
      - amp[153] - amp[154] - amp[155] - amp[156] + 1./6. * amp[157] - amp[158]
      - amp[159];
  jamp[1] = +amp[143] - 1./6. * amp[144] + amp[145] + amp[146] + amp[147] +
      amp[148] - 1./6. * amp[149] + amp[150] - 1./2. * amp[152] - 1./2. *
      amp[157] + amp[160];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dux_wmddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[162] + 1./6. * amp[163] - amp[164] - amp[165] - amp[166] -
      amp[167] + 1./2. * amp[169] + 1./2. * amp[174] - amp[176] + 1./6. *
      amp[177] - amp[178];
  jamp[1] = +amp[161] - 1./2. * amp[163] + amp[168] - 1./6. * amp[169] +
      amp[170] + amp[171] + amp[172] + amp[173] - 1./6. * amp[174] + amp[175] -
      1./2. * amp[177];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ddx_wpdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[179] + 1./6. * amp[180] - amp[181] + 1./2. * amp[183] -
      amp[188] - amp[189] - amp[190] - amp[191] + 1./6. * amp[192] - amp[193] +
      1./2. * amp[195];
  jamp[1] = -1./2. * amp[180] + amp[182] - 1./6. * amp[183] + amp[184] +
      amp[185] + amp[186] + amp[187] - 1./2. * amp[192] + amp[194] - 1./6. *
      amp[195] + amp[196];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ddx_wmudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[197] + 1./2. * amp[199] - amp[204] + 1./6. * amp[205] -
      amp[206] - amp[207] - amp[208] - amp[209] + 1./6. * amp[210] - amp[211] +
      1./2. * amp[213];
  jamp[1] = +amp[198] - 1./6. * amp[199] + amp[200] + amp[201] + amp[202] +
      amp[203] - 1./2. * amp[205] - 1./2. * amp[210] + amp[212] - 1./6. *
      amp[213] + amp[214];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxux_wmuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[215] + 1./6. * amp[216] - amp[217] - amp[218] - amp[219] -
      amp[220] + 1./6. * amp[221] - amp[222] + 1./2. * amp[224] + 1./2. *
      amp[229] - amp[232];
  jamp[1] = -1./2. * amp[216] - 1./2. * amp[221] + amp[223] - 1./6. * amp[224]
      + amp[225] + amp[226] + amp[227] + amp[228] - 1./6. * amp[229] + amp[230]
      + amp[231];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxdx_wpuxux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[234] - amp[236] - amp[237] + 1./6. * amp[238] -
      amp[239] - amp[240] - amp[241] - amp[242] + 1./6. * amp[243] - amp[244] +
      1./2. * amp[249];
  jamp[1] = +amp[233] - 1./6. * amp[234] + amp[235] - 1./2. * amp[238] - 1./2.
      * amp[243] + amp[245] + amp[246] + amp[247] + amp[248] - 1./6. * amp[249]
      + amp[250];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxdx_wmdxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[252] + 1./6. * amp[253] - amp[254] - amp[255] - amp[256] -
      amp[257] + 1./2. * amp[259] + 1./2. * amp[264] - amp[266] + 1./6. *
      amp[267] - amp[268];
  jamp[1] = +amp[251] - 1./2. * amp[253] + amp[258] - 1./6. * amp[259] +
      amp[260] + amp[261] + amp[262] + amp[263] - 1./6. * amp[264] + amp[265] -
      1./2. * amp[267];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dxdx_wpuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 18;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * amp[270] - amp[272] + 1./6. * amp[273] - amp[274] -
      amp[275] - amp[276] - amp[277] + 1./2. * amp[282] - amp[284] + 1./6. *
      amp[285] - amp[286];
  jamp[1] = +amp[269] - 1./6. * amp[270] + amp[271] - 1./2. * amp[273] +
      amp[278] + amp[279] + amp[280] + amp[281] - 1./6. * amp[282] + amp[283] -
      1./2. * amp[285];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uc_wpus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[287] - amp[288] + 1./6. * amp[289] - amp[290] - amp[291] -
      amp[292] - amp[293] + 1./6. * amp[294] - amp[295];
  jamp[1] = +1./2. * (-amp[289] - amp[294]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uc_wpcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[1] + amp[300]); 
  jamp[1] = +amp[0] - 1./6. * amp[1] + amp[2] + amp[296] + amp[297] + amp[298]
      + amp[299] - 1./6. * amp[300] + amp[301];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_us_wpds() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[302] + 1./6. * amp[303] - amp[304] - amp[305] - amp[306] -
      amp[307] - amp[308] + 1./6. * amp[309] - amp[310];
  jamp[1] = +1./2. * (-amp[303] - amp[309]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_us_wmuc() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[311] + 1./6. * amp[312] - amp[313] - amp[314] - amp[315] -
      amp[316] + 1./6. * amp[317] - amp[318] - amp[319];
  jamp[1] = +1./2. * (-amp[312] - amp[317]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uux_wpscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[320] - amp[321] + 1./6. * amp[322] - amp[323] - amp[324] -
      amp[325] - amp[326] + 1./6. * amp[327] - amp[328];
  jamp[1] = +1./2. * (-amp[322] - amp[327]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uux_wmcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[329] + 1./6. * amp[330] - amp[331] - amp[332] - amp[333] -
      amp[334] + 1./6. * amp[335] - amp[336] - amp[337];
  jamp[1] = +1./2. * (-amp[330] - amp[335]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ucx_wpdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[339] + amp[345]); 
  jamp[1] = +amp[338] - 1./6. * amp[339] + amp[340] + amp[341] + amp[342] +
      amp[343] + amp[344] - 1./6. * amp[345] + amp[346];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ucx_wmusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[348] + amp[353]); 
  jamp[1] = +amp[347] - 1./6. * amp[348] + amp[349] + amp[350] + amp[351] +
      amp[352] - 1./6. * amp[353] + amp[354] + amp[355];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_udx_wpccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[356] + 1./6. * amp[357] - amp[358] - amp[359] - amp[360] -
      amp[361] - amp[362] + 1./6. * amp[363] - amp[364];
  jamp[1] = +1./2. * (-amp[357] - amp[363]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_udx_wpssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[365] + 1./6. * amp[366] - amp[367] - amp[368] - amp[369] -
      amp[370] - amp[371] + 1./6. * amp[372] - amp[373];
  jamp[1] = +1./2. * (-amp[366] - amp[372]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_usx_wpucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[376] + amp[381]); 
  jamp[1] = +amp[374] + amp[375] - 1./6. * amp[376] + amp[377] + amp[378] +
      amp[379] + amp[380] - 1./6. * amp[381] + amp[382];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_usx_wpdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[384] + amp[390]); 
  jamp[1] = +amp[383] - 1./6. * amp[384] + amp[385] + amp[386] + amp[387] +
      amp[388] + amp[389] - 1./6. * amp[390] + amp[391];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ds_wmus() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[392] + 1./6. * amp[393] - amp[394] - amp[395] - amp[396] -
      amp[397] - amp[398] + 1./6. * amp[399] - amp[400];
  jamp[1] = +1./2. * (-amp[393] - amp[399]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ds_wmcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[403] + amp[408]); 
  jamp[1] = +amp[401] + amp[402] - 1./6. * amp[403] + amp[404] + amp[405] +
      amp[406] + amp[407] - 1./6. * amp[408] + amp[409];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dux_wmccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[410] + 1./6. * amp[411] - amp[412] - amp[413] - amp[414] -
      amp[415] + 1./6. * amp[416] - amp[417] - amp[418];
  jamp[1] = +1./2. * (-amp[411] - amp[416]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dux_wmssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[419] + 1./6. * amp[420] - amp[421] - amp[422] - amp[423] -
      amp[424] - amp[425] + 1./6. * amp[426] - amp[427];
  jamp[1] = +1./2. * (-amp[420] - amp[426]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dcx_wmucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[429] + amp[434]); 
  jamp[1] = +amp[428] - 1./6. * amp[429] + amp[430] + amp[431] + amp[432] +
      amp[433] - 1./6. * amp[434] + amp[435] + amp[436];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dcx_wmdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[439] + amp[444]); 
  jamp[1] = +amp[437] + amp[438] - 1./6. * amp[439] + amp[440] + amp[441] +
      amp[442] + amp[443] - 1./6. * amp[444] + amp[445];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ddx_wpscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[446] + 1./6. * amp[447] - amp[448] - amp[449] - amp[450] -
      amp[451] - amp[452] + 1./6. * amp[453] - amp[454];
  jamp[1] = +1./2. * (-amp[447] - amp[453]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_ddx_wmcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[455] - amp[456] + 1./6. * amp[457] - amp[458] - amp[459] -
      amp[460] - amp[461] + 1./6. * amp[462] - amp[463];
  jamp[1] = +1./2. * (-amp[457] - amp[462]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dsx_wpdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[465] + amp[471]); 
  jamp[1] = +amp[464] - 1./6. * amp[465] + amp[466] + amp[467] + amp[468] +
      amp[469] + amp[470] - 1./6. * amp[471] + amp[472];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dsx_wmusx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[474] + amp[480]); 
  jamp[1] = +amp[473] - 1./6. * amp[474] + amp[475] + amp[476] + amp[477] +
      amp[478] + amp[479] - 1./6. * amp[480] + amp[481];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxcx_wmuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[482] + 1./6. * amp[483] - amp[484] - amp[485] - amp[486] -
      amp[487] + 1./6. * amp[488] - amp[489] - amp[490];
  jamp[1] = +1./2. * (-amp[483] - amp[488]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxcx_wmcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[492] + amp[497]); 
  jamp[1] = +amp[491] - 1./6. * amp[492] + amp[493] + amp[494] + amp[495] +
      amp[496] - 1./6. * amp[497] + amp[498] + amp[499];

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxsx_wpuxcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[500] - amp[501] + 1./6. * amp[502] - amp[503] - amp[504] -
      amp[505] - amp[506] + 1./6. * amp[507] - amp[508];
  jamp[1] = +1./2. * (-amp[502] - amp[507]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_uxsx_wmdxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[509] + 1./6. * amp[510] - amp[511] - amp[512] - amp[513] -
      amp[514] - amp[515] + 1./6. * amp[516] - amp[517];
  jamp[1] = +1./2. * (-amp[510] - amp[516]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dxsx_wpuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[518] + 1./6. * amp[519] - amp[520] - amp[521] - amp[522] -
      amp[523] - amp[524] + 1./6. * amp[525] - amp[526];
  jamp[1] = +1./2. * (-amp[519] - amp[525]); 

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

double PY8MEs_R8_P20_sm_qq_wpqq::matrix_8_dxsx_wpcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 9;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[528] + amp[534]); 
  jamp[1] = +amp[527] - 1./6. * amp[528] + amp[529] + amp[530] + amp[531] +
      amp[532] + amp[533] - 1./6. * amp[534] + amp[535];

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


}  // end namespace PY8MEs_namespace

