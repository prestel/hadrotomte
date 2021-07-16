//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R8_P15_sm_qq_zqq.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u > z u u WEIGHTED<=99 @8
// Process: c c > z c c WEIGHTED<=99 @8
// Process: u u~ > z u u~ WEIGHTED<=99 @8
// Process: c c~ > z c c~ WEIGHTED<=99 @8
// Process: d d > z d d WEIGHTED<=99 @8
// Process: s s > z s s WEIGHTED<=99 @8
// Process: d d~ > z d d~ WEIGHTED<=99 @8
// Process: s s~ > z s s~ WEIGHTED<=99 @8
// Process: u~ u~ > z u~ u~ WEIGHTED<=99 @8
// Process: c~ c~ > z c~ c~ WEIGHTED<=99 @8
// Process: d~ d~ > z d~ d~ WEIGHTED<=99 @8
// Process: s~ s~ > z s~ s~ WEIGHTED<=99 @8
// Process: u d > z u d WEIGHTED<=99 @8
// Process: c s > z c s WEIGHTED<=99 @8
// Process: u u~ > z d d~ WEIGHTED<=99 @8
// Process: c c~ > z s s~ WEIGHTED<=99 @8
// Process: u d~ > z u d~ WEIGHTED<=99 @8
// Process: c s~ > z c s~ WEIGHTED<=99 @8
// Process: d u~ > z d u~ WEIGHTED<=99 @8
// Process: s c~ > z s c~ WEIGHTED<=99 @8
// Process: d d~ > z u u~ WEIGHTED<=99 @8
// Process: s s~ > z c c~ WEIGHTED<=99 @8
// Process: u~ d~ > z u~ d~ WEIGHTED<=99 @8
// Process: c~ s~ > z c~ s~ WEIGHTED<=99 @8
// Process: u c > z u c WEIGHTED<=99 @8
// Process: u s > z u s WEIGHTED<=99 @8
// Process: c d > z c d WEIGHTED<=99 @8
// Process: u u~ > z c c~ WEIGHTED<=99 @8
// Process: c c~ > z u u~ WEIGHTED<=99 @8
// Process: u u~ > z s s~ WEIGHTED<=99 @8
// Process: c c~ > z d d~ WEIGHTED<=99 @8
// Process: u c~ > z u c~ WEIGHTED<=99 @8
// Process: c u~ > z c u~ WEIGHTED<=99 @8
// Process: u s~ > z u s~ WEIGHTED<=99 @8
// Process: c d~ > z c d~ WEIGHTED<=99 @8
// Process: d s > z d s WEIGHTED<=99 @8
// Process: d c~ > z d c~ WEIGHTED<=99 @8
// Process: s u~ > z s u~ WEIGHTED<=99 @8
// Process: d d~ > z c c~ WEIGHTED<=99 @8
// Process: s s~ > z u u~ WEIGHTED<=99 @8
// Process: d d~ > z s s~ WEIGHTED<=99 @8
// Process: s s~ > z d d~ WEIGHTED<=99 @8
// Process: d s~ > z d s~ WEIGHTED<=99 @8
// Process: s d~ > z s d~ WEIGHTED<=99 @8
// Process: u~ c~ > z u~ c~ WEIGHTED<=99 @8
// Process: u~ s~ > z u~ s~ WEIGHTED<=99 @8
// Process: c~ d~ > z c~ d~ WEIGHTED<=99 @8
// Process: d~ s~ > z d~ s~ WEIGHTED<=99 @8
// Process: u s > z c d WEIGHTED<=99 @8
// Process: c d > z u s WEIGHTED<=99 @8
// Process: u c~ > z d s~ WEIGHTED<=99 @8
// Process: c u~ > z s d~ WEIGHTED<=99 @8
// Process: u d~ > z c s~ WEIGHTED<=99 @8
// Process: c s~ > z u d~ WEIGHTED<=99 @8
// Process: d u~ > z s c~ WEIGHTED<=99 @8
// Process: s c~ > z d u~ WEIGHTED<=99 @8
// Process: d s~ > z u c~ WEIGHTED<=99 @8
// Process: s d~ > z c u~ WEIGHTED<=99 @8
// Process: u~ s~ > z c~ d~ WEIGHTED<=99 @8
// Process: c~ d~ > z u~ s~ WEIGHTED<=99 @8

// Exception class
class PY8MEs_R8_P15_sm_qq_zqqException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R8_P15_sm_qq_zqq'."; 
  }
}
PY8MEs_R8_P15_sm_qq_zqq_exception; 

std::set<int> PY8MEs_R8_P15_sm_qq_zqq::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R8_P15_sm_qq_zqq::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R8_P15_sm_qq_zqq::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
int PY8MEs_R8_P15_sm_qq_zqq::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R8_P15_sm_qq_zqq::denom_iden[nprocesses] = {2, 1, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R8_P15_sm_qq_zqq::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u u > z u u WEIGHTED<=99 @8
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

  // Color flows of process Process: u u~ > z u u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #1
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[1].push_back(0); 

  // Color flows of process Process: d d > z d d WEIGHTED<=99 @8
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

  // Color flows of process Process: d d~ > z d d~ WEIGHTED<=99 @8
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

  // Color flows of process Process: u~ u~ > z u~ u~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: d~ d~ > z d~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[5].push_back(0); 

  // Color flows of process Process: u d > z u d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: u u~ > z d d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: u d~ > z u d~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d u~ > z d u~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d d~ > z u u~ WEIGHTED<=99 @8
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

  // Color flows of process Process: u~ d~ > z u~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: u c > z u c WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: u s > z u s WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: u u~ > z c c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: u u~ > z s s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: u c~ > z u c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: u s~ > z u s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[17].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[17].push_back(0); 
  // JAMP #1
  color_configs[17].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[17].push_back(0); 

  // Color flows of process Process: d s > z d s WEIGHTED<=99 @8
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

  // Color flows of process Process: d c~ > z d c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[19].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[19].push_back(0); 
  // JAMP #1
  color_configs[19].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[19].push_back(0); 

  // Color flows of process Process: d d~ > z c c~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d d~ > z s s~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d s~ > z d s~ WEIGHTED<=99 @8
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

  // Color flows of process Process: u~ c~ > z u~ c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[23].push_back(0); 
  // JAMP #1
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[23].push_back(0); 

  // Color flows of process Process: u~ s~ > z u~ s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[24].push_back(0); 
  // JAMP #1
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[24].push_back(0); 

  // Color flows of process Process: d~ s~ > z d~ s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[25].push_back(0); 
  // JAMP #1
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[25].push_back(0); 

  // Color flows of process Process: u s > z c d WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[26].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[26].push_back(0); 

  // Color flows of process Process: u c~ > z d s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[27].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[27].push_back(0); 

  // Color flows of process Process: u d~ > z c s~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[28].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[28].push_back(0); 

  // Color flows of process Process: d u~ > z s c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[29].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[29].push_back(0); 

  // Color flows of process Process: d s~ > z u c~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[30].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[30].push_back(0); 

  // Color flows of process Process: u~ s~ > z c~ d~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[31].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[31].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R8_P15_sm_qq_zqq::~PY8MEs_R8_P15_sm_qq_zqq() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R8_P15_sm_qq_zqq::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R8_P15_sm_qq_zqq::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R8_P15_sm_qq_zqq::getColorConfigs(int
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
int PY8MEs_R8_P15_sm_qq_zqq::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R8_P15_sm_qq_zqq::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
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
int PY8MEs_R8_P15_sm_qq_zqq::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R8_P15_sm_qq_zqq': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R8_P15_sm_qq_zqq::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R8_P15_sm_qq_zqq': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
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
int PY8MEs_R8_P15_sm_qq_zqq::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R8_P15_sm_qq_zqq': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
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
      " 'PY8MEs_R8_P15_sm_qq_zqq': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R8_P15_sm_qq_zqq::getAllResults(int
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
double PY8MEs_R8_P15_sm_qq_zqq::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
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
    " 'PY8MEs_R8_P15_sm_qq_zqq': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R8_P15_sm_qq_zqq::static_getPY8ME(vector<int>
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
  const int nprocs = 112; 
  const int proc_IDS[nprocs] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
      8, 8, 9, 9, 10, 10, 11, 11, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17,
      18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 27, 28,
      28, 29, 29, 30, 30, 31, 31, 1, 1, 3, 3, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10,
      11, 11, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20,
      21, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30,
      31, 31};
  const int in_pdgs[nprocs][ninitial] = {{2, 2}, {4, 4}, {2, -2}, {4, -4}, {1,
      1}, {3, 3}, {1, -1}, {3, -3}, {-2, -2}, {-4, -4}, {-1, -1}, {-3, -3}, {2,
      1}, {4, 3}, {2, -2}, {4, -4}, {2, -1}, {4, -3}, {1, -2}, {3, -4}, {1,
      -1}, {3, -3}, {-2, -1}, {-4, -3}, {2, 4}, {2, 3}, {4, 1}, {2, -2}, {4,
      -4}, {2, -2}, {4, -4}, {2, -4}, {4, -2}, {2, -3}, {4, -1}, {1, 3}, {1,
      -4}, {3, -2}, {1, -1}, {3, -3}, {1, -1}, {3, -3}, {1, -3}, {3, -1}, {-2,
      -4}, {-2, -3}, {-4, -1}, {-1, -3}, {2, 3}, {4, 1}, {2, -4}, {4, -2}, {2,
      -1}, {4, -3}, {1, -2}, {3, -4}, {1, -3}, {3, -1}, {-2, -3}, {-4, -1},
      {-2, 2}, {-4, 4}, {-1, 1}, {-3, 3}, {1, 2}, {3, 4}, {-2, 2}, {-4, 4},
      {-1, 2}, {-3, 4}, {-2, 1}, {-4, 3}, {-1, 1}, {-3, 3}, {-1, -2}, {-3, -4},
      {4, 2}, {3, 2}, {1, 4}, {-2, 2}, {-4, 4}, {-2, 2}, {-4, 4}, {-4, 2}, {-2,
      4}, {-3, 2}, {-1, 4}, {3, 1}, {-4, 1}, {-2, 3}, {-1, 1}, {-3, 3}, {-1,
      1}, {-3, 3}, {-3, 1}, {-1, 3}, {-4, -2}, {-3, -2}, {-1, -4}, {-3, -1},
      {3, 2}, {1, 4}, {-4, 2}, {-2, 4}, {-1, 2}, {-3, 4}, {-2, 1}, {-4, 3},
      {-3, 1}, {-1, 3}, {-3, -2}, {-1, -4}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{23, 2, 2}, {23, 4, 4},
      {23, 2, -2}, {23, 4, -4}, {23, 1, 1}, {23, 3, 3}, {23, 1, -1}, {23, 3,
      -3}, {23, -2, -2}, {23, -4, -4}, {23, -1, -1}, {23, -3, -3}, {23, 2, 1},
      {23, 4, 3}, {23, 1, -1}, {23, 3, -3}, {23, 2, -1}, {23, 4, -3}, {23, 1,
      -2}, {23, 3, -4}, {23, 2, -2}, {23, 4, -4}, {23, -2, -1}, {23, -4, -3},
      {23, 2, 4}, {23, 2, 3}, {23, 4, 1}, {23, 4, -4}, {23, 2, -2}, {23, 3,
      -3}, {23, 1, -1}, {23, 2, -4}, {23, 4, -2}, {23, 2, -3}, {23, 4, -1},
      {23, 1, 3}, {23, 1, -4}, {23, 3, -2}, {23, 4, -4}, {23, 2, -2}, {23, 3,
      -3}, {23, 1, -1}, {23, 1, -3}, {23, 3, -1}, {23, -2, -4}, {23, -2, -3},
      {23, -4, -1}, {23, -1, -3}, {23, 4, 1}, {23, 2, 3}, {23, 1, -3}, {23, 3,
      -1}, {23, 4, -3}, {23, 2, -1}, {23, 3, -4}, {23, 1, -2}, {23, 2, -4},
      {23, 4, -2}, {23, -4, -1}, {23, -2, -3}, {23, 2, -2}, {23, 4, -4}, {23,
      1, -1}, {23, 3, -3}, {23, 2, 1}, {23, 4, 3}, {23, 1, -1}, {23, 3, -3},
      {23, 2, -1}, {23, 4, -3}, {23, 1, -2}, {23, 3, -4}, {23, 2, -2}, {23, 4,
      -4}, {23, -2, -1}, {23, -4, -3}, {23, 2, 4}, {23, 2, 3}, {23, 4, 1}, {23,
      4, -4}, {23, 2, -2}, {23, 3, -3}, {23, 1, -1}, {23, 2, -4}, {23, 4, -2},
      {23, 2, -3}, {23, 4, -1}, {23, 1, 3}, {23, 1, -4}, {23, 3, -2}, {23, 4,
      -4}, {23, 2, -2}, {23, 3, -3}, {23, 1, -1}, {23, 1, -3}, {23, 3, -1},
      {23, -2, -4}, {23, -2, -3}, {23, -4, -1}, {23, -1, -3}, {23, 4, 1}, {23,
      2, 3}, {23, 1, -3}, {23, 3, -1}, {23, 4, -3}, {23, 2, -1}, {23, 3, -4},
      {23, 1, -2}, {23, 2, -4}, {23, 4, -2}, {23, -4, -1}, {23, -2, -3}};

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
void PY8MEs_R8_P15_sm_qq_zqq::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P15_sm_qq_zqq': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R8_P15_sm_qq_zqq::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R8_P15_sm_qq_zqq::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R8_P15_sm_qq_zqq::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R8_P15_sm_qq_zqq::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R8_P15_sm_qq_zqq::initProc() 
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
  jamp2 = vector < vec_double > (32); 
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
  jamp2[26] = vector<double> (1, 0.); 
  jamp2[27] = vector<double> (1, 0.); 
  jamp2[28] = vector<double> (1, 0.); 
  jamp2[29] = vector<double> (1, 0.); 
  jamp2[30] = vector<double> (1, 0.); 
  jamp2[31] = vector<double> (1, 0.); 
  all_results = vector < vec_vec_double > (32); 
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
  all_results[26] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[27] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[28] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[29] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[30] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
  all_results[31] = vector < vec_double > (ncomb + 1, vector<double> (1 + 1,
      0.));
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R8_P15_sm_qq_zqq::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->ZERO; 
  mME[2] = pars->mdl_MZ; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->ZERO; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R8_P15_sm_qq_zqq::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R8_P15_sm_qq_zqq::getMasses() 
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
void PY8MEs_R8_P15_sm_qq_zqq::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R8_P15_sm_qq_zqq': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R8_P15_sm_qq_zqq_exception; 
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

double PY8MEs_R8_P15_sm_qq_zqq::sigmaKin() 
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
  for(int i = 0; i < 1; i++ )
    jamp2[26][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[27][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[28][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[29][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[30][i] = 0.; 
  for(int i = 0; i < 1; i++ )
    jamp2[31][i] = 0.; 

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
    for(int i = 0; i < 1; i++ )
      jamp2[26][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[27][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[28][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[29][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[30][i] = 0.; 
    for(int i = 0; i < 1; i++ )
      jamp2[31][i] = 0.; 

    if (proc_ID == 0)
      t = matrix_8_uu_zuu(); 
    if (proc_ID == 1)
      t = matrix_8_uux_zuux(); 
    if (proc_ID == 2)
      t = matrix_8_dd_zdd(); 
    if (proc_ID == 3)
      t = matrix_8_ddx_zddx(); 
    if (proc_ID == 4)
      t = matrix_8_uxux_zuxux(); 
    if (proc_ID == 5)
      t = matrix_8_dxdx_zdxdx(); 
    if (proc_ID == 6)
      t = matrix_8_ud_zud(); 
    if (proc_ID == 7)
      t = matrix_8_uux_zddx(); 
    if (proc_ID == 8)
      t = matrix_8_udx_zudx(); 
    if (proc_ID == 9)
      t = matrix_8_dux_zdux(); 
    if (proc_ID == 10)
      t = matrix_8_ddx_zuux(); 
    if (proc_ID == 11)
      t = matrix_8_uxdx_zuxdx(); 
    if (proc_ID == 12)
      t = matrix_8_uc_zuc(); 
    if (proc_ID == 13)
      t = matrix_8_us_zus(); 
    if (proc_ID == 14)
      t = matrix_8_uux_zccx(); 
    if (proc_ID == 15)
      t = matrix_8_uux_zssx(); 
    if (proc_ID == 16)
      t = matrix_8_ucx_zucx(); 
    if (proc_ID == 17)
      t = matrix_8_usx_zusx(); 
    if (proc_ID == 18)
      t = matrix_8_ds_zds(); 
    if (proc_ID == 19)
      t = matrix_8_dcx_zdcx(); 
    if (proc_ID == 20)
      t = matrix_8_ddx_zccx(); 
    if (proc_ID == 21)
      t = matrix_8_ddx_zssx(); 
    if (proc_ID == 22)
      t = matrix_8_dsx_zdsx(); 
    if (proc_ID == 23)
      t = matrix_8_uxcx_zuxcx(); 
    if (proc_ID == 24)
      t = matrix_8_uxsx_zuxsx(); 
    if (proc_ID == 25)
      t = matrix_8_dxsx_zdxsx(); 
    if (proc_ID == 26)
      t = matrix_8_us_zcd(); 
    if (proc_ID == 27)
      t = matrix_8_ucx_zdsx(); 
    if (proc_ID == 28)
      t = matrix_8_udx_zcsx(); 
    if (proc_ID == 29)
      t = matrix_8_dux_zscx(); 
    if (proc_ID == 30)
      t = matrix_8_dsx_zucx(); 
    if (proc_ID == 31)
      t = matrix_8_uxsx_zcxdx(); 

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

void PY8MEs_R8_P15_sm_qq_zqq::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  vxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  FFV2_5_2(w[0], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO, w[5]); 
  FFV1P0_3(w[1], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[1], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[7]); 
  FFV2_5_3(w[1], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[8]);
  FFV1P0_3(w[1], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[9]); 
  FFV1P0_3(w[1], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[10]); 
  FFV2_5_3(w[1], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV1P0_3(w[0], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[12]); 
  FFV2_5_2(w[1], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[13]);
  FFV1P0_3(w[0], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[14]); 
  FFV2_5_3(w[0], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[15]);
  FFV2_5_1(w[4], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[16]);
  FFV1P0_3(w[0], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[17]); 
  FFV1P0_3(w[0], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[18]); 
  FFV2_5_3(w[0], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[19]);
  FFV2_5_1(w[3], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[20]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[21]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[22]); 
  FFV1P0_3(w[22], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[23]); 
  FFV1P0_3(w[22], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[24]); 
  FFV2_5_3(w[22], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[25]);
  FFV1P0_3(w[22], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[26]); 
  FFV1P0_3(w[22], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[27]); 
  FFV2_5_3(w[22], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[28]);
  FFV1P0_3(w[0], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[29]); 
  FFV2_5_2(w[22], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[30]);
  FFV1P0_3(w[0], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[31]); 
  FFV2_5_3(w[0], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[32]);
  FFV2_5_1(w[21], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[33]);
  FFV2_3_2(w[0], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[34]);
  FFV1P0_3(w[1], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[35]); 
  FFV2_3_3(w[1], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[36]);
  FFV1P0_3(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[37]); 
  FFV2_3_3(w[1], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[38]);
  FFV1P0_3(w[0], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[39]); 
  FFV2_3_2(w[1], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[40]);
  FFV2_3_3(w[0], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[41]);
  FFV2_3_1(w[4], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[42]);
  FFV1P0_3(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[43]); 
  FFV2_3_3(w[0], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[44]);
  FFV2_3_1(w[3], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[45]);
  FFV1P0_3(w[22], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[46]); 
  FFV2_3_3(w[22], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[47]);
  FFV1P0_3(w[22], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[48]); 
  FFV2_3_3(w[22], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[49]);
  FFV1P0_3(w[0], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[50]); 
  FFV2_3_2(w[22], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[51]);
  FFV2_3_3(w[0], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[52]);
  FFV2_3_1(w[21], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[53]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[54]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[55]); 
  FFV2_5_2(w[55], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[56]);
  FFV1P0_3(w[22], w[54], pars->GC_2, pars->ZERO, pars->ZERO, w[57]); 
  FFV1P0_3(w[22], w[54], pars->GC_11, pars->ZERO, pars->ZERO, w[58]); 
  FFV2_5_3(w[22], w[54], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[59]);
  FFV1P0_3(w[55], w[54], pars->GC_2, pars->ZERO, pars->ZERO, w[60]); 
  FFV1P0_3(w[55], w[54], pars->GC_11, pars->ZERO, pars->ZERO, w[61]); 
  FFV2_5_3(w[55], w[54], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[62]);
  FFV1P0_3(w[55], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[63]); 
  FFV1P0_3(w[55], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[64]); 
  FFV2_5_3(w[55], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[65]);
  FFV2_5_1(w[54], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[66]);
  FFV2_3_2(w[55], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[67]);
  FFV1P0_3(w[22], w[54], pars->GC_1, pars->ZERO, pars->ZERO, w[68]); 
  FFV2_3_3(w[22], w[54], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[69]);
  FFV1P0_3(w[55], w[54], pars->GC_1, pars->ZERO, pars->ZERO, w[70]); 
  FFV2_3_3(w[55], w[54], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[71]);
  FFV1P0_3(w[55], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[72]); 
  FFV2_3_3(w[55], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[73]);
  FFV2_3_1(w[54], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[74]);
  FFV2_3(w[1], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[75]); 
  FFV2_3(w[0], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[76]); 
  FFV2_3(w[22], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[77]); 
  FFV2_3(w[0], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[78]); 
  FFV2_3(w[22], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[79]); 
  FFV2_3(w[0], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[80]); 
  FFV2_3(w[22], w[54], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[81]); 
  FFV2_3(w[55], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[82]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[5], w[4], w[6], pars->GC_2, amp[0]); 
  FFV1_0(w[5], w[4], w[7], pars->GC_11, amp[1]); 
  FFV2_5_0(w[5], w[4], w[8], pars->GC_51, pars->GC_58, amp[2]); 
  FFV1_0(w[5], w[3], w[9], pars->GC_2, amp[3]); 
  FFV1_0(w[5], w[3], w[10], pars->GC_11, amp[4]); 
  FFV2_5_0(w[5], w[3], w[11], pars->GC_51, pars->GC_58, amp[5]); 
  FFV1_0(w[13], w[4], w[12], pars->GC_2, amp[6]); 
  FFV1_0(w[13], w[4], w[14], pars->GC_11, amp[7]); 
  FFV2_5_0(w[13], w[4], w[15], pars->GC_51, pars->GC_58, amp[8]); 
  FFV1_0(w[1], w[16], w[12], pars->GC_2, amp[9]); 
  FFV1_0(w[1], w[16], w[14], pars->GC_11, amp[10]); 
  FFV2_5_0(w[1], w[16], w[15], pars->GC_51, pars->GC_58, amp[11]); 
  FFV1_0(w[13], w[3], w[17], pars->GC_2, amp[12]); 
  FFV1_0(w[13], w[3], w[18], pars->GC_11, amp[13]); 
  FFV2_5_0(w[13], w[3], w[19], pars->GC_51, pars->GC_58, amp[14]); 
  FFV1_0(w[1], w[20], w[17], pars->GC_2, amp[15]); 
  FFV1_0(w[1], w[20], w[18], pars->GC_11, amp[16]); 
  FFV2_5_0(w[1], w[20], w[19], pars->GC_51, pars->GC_58, amp[17]); 
  FFV1_0(w[0], w[16], w[6], pars->GC_2, amp[18]); 
  FFV1_0(w[0], w[16], w[7], pars->GC_11, amp[19]); 
  FFV2_5_0(w[0], w[16], w[8], pars->GC_51, pars->GC_58, amp[20]); 
  FFV1_0(w[0], w[20], w[9], pars->GC_2, amp[21]); 
  FFV1_0(w[0], w[20], w[10], pars->GC_11, amp[22]); 
  FFV2_5_0(w[0], w[20], w[11], pars->GC_51, pars->GC_58, amp[23]); 
  FFV1_0(w[5], w[3], w[23], pars->GC_2, amp[24]); 
  FFV1_0(w[5], w[3], w[24], pars->GC_11, amp[25]); 
  FFV2_5_0(w[5], w[3], w[25], pars->GC_51, pars->GC_58, amp[26]); 
  FFV1_0(w[5], w[21], w[26], pars->GC_2, amp[27]); 
  FFV1_0(w[5], w[21], w[27], pars->GC_11, amp[28]); 
  FFV2_5_0(w[5], w[21], w[28], pars->GC_51, pars->GC_58, amp[29]); 
  FFV1_0(w[30], w[3], w[29], pars->GC_2, amp[30]); 
  FFV1_0(w[30], w[3], w[31], pars->GC_11, amp[31]); 
  FFV2_5_0(w[30], w[3], w[32], pars->GC_51, pars->GC_58, amp[32]); 
  FFV1_0(w[22], w[20], w[29], pars->GC_2, amp[33]); 
  FFV1_0(w[22], w[20], w[31], pars->GC_11, amp[34]); 
  FFV2_5_0(w[22], w[20], w[32], pars->GC_51, pars->GC_58, amp[35]); 
  FFV1_0(w[30], w[21], w[12], pars->GC_2, amp[36]); 
  FFV1_0(w[30], w[21], w[14], pars->GC_11, amp[37]); 
  FFV2_5_0(w[30], w[21], w[15], pars->GC_51, pars->GC_58, amp[38]); 
  FFV1_0(w[22], w[33], w[12], pars->GC_2, amp[39]); 
  FFV1_0(w[22], w[33], w[14], pars->GC_11, amp[40]); 
  FFV2_5_0(w[22], w[33], w[15], pars->GC_51, pars->GC_58, amp[41]); 
  FFV1_0(w[0], w[20], w[23], pars->GC_2, amp[42]); 
  FFV1_0(w[0], w[20], w[24], pars->GC_11, amp[43]); 
  FFV2_5_0(w[0], w[20], w[25], pars->GC_51, pars->GC_58, amp[44]); 
  FFV1_0(w[0], w[33], w[26], pars->GC_2, amp[45]); 
  FFV1_0(w[0], w[33], w[27], pars->GC_11, amp[46]); 
  FFV2_5_0(w[0], w[33], w[28], pars->GC_51, pars->GC_58, amp[47]); 
  FFV1_0(w[34], w[4], w[35], pars->GC_1, amp[48]); 
  FFV1_0(w[34], w[4], w[7], pars->GC_11, amp[49]); 
  FFV2_3_0(w[34], w[4], w[36], pars->GC_50, pars->GC_58, amp[50]); 
  FFV1_0(w[34], w[3], w[37], pars->GC_1, amp[51]); 
  FFV1_0(w[34], w[3], w[10], pars->GC_11, amp[52]); 
  FFV2_3_0(w[34], w[3], w[38], pars->GC_50, pars->GC_58, amp[53]); 
  FFV1_0(w[40], w[4], w[39], pars->GC_1, amp[54]); 
  FFV1_0(w[40], w[4], w[14], pars->GC_11, amp[55]); 
  FFV2_3_0(w[40], w[4], w[41], pars->GC_50, pars->GC_58, amp[56]); 
  FFV1_0(w[1], w[42], w[39], pars->GC_1, amp[57]); 
  FFV1_0(w[1], w[42], w[14], pars->GC_11, amp[58]); 
  FFV2_3_0(w[1], w[42], w[41], pars->GC_50, pars->GC_58, amp[59]); 
  FFV1_0(w[40], w[3], w[43], pars->GC_1, amp[60]); 
  FFV1_0(w[40], w[3], w[18], pars->GC_11, amp[61]); 
  FFV2_3_0(w[40], w[3], w[44], pars->GC_50, pars->GC_58, amp[62]); 
  FFV1_0(w[1], w[45], w[43], pars->GC_1, amp[63]); 
  FFV1_0(w[1], w[45], w[18], pars->GC_11, amp[64]); 
  FFV2_3_0(w[1], w[45], w[44], pars->GC_50, pars->GC_58, amp[65]); 
  FFV1_0(w[0], w[42], w[35], pars->GC_1, amp[66]); 
  FFV1_0(w[0], w[42], w[7], pars->GC_11, amp[67]); 
  FFV2_3_0(w[0], w[42], w[36], pars->GC_50, pars->GC_58, amp[68]); 
  FFV1_0(w[0], w[45], w[37], pars->GC_1, amp[69]); 
  FFV1_0(w[0], w[45], w[10], pars->GC_11, amp[70]); 
  FFV2_3_0(w[0], w[45], w[38], pars->GC_50, pars->GC_58, amp[71]); 
  FFV1_0(w[34], w[3], w[46], pars->GC_1, amp[72]); 
  FFV1_0(w[34], w[3], w[24], pars->GC_11, amp[73]); 
  FFV2_3_0(w[34], w[3], w[47], pars->GC_50, pars->GC_58, amp[74]); 
  FFV1_0(w[34], w[21], w[48], pars->GC_1, amp[75]); 
  FFV1_0(w[34], w[21], w[27], pars->GC_11, amp[76]); 
  FFV2_3_0(w[34], w[21], w[49], pars->GC_50, pars->GC_58, amp[77]); 
  FFV1_0(w[51], w[3], w[50], pars->GC_1, amp[78]); 
  FFV1_0(w[51], w[3], w[31], pars->GC_11, amp[79]); 
  FFV2_3_0(w[51], w[3], w[52], pars->GC_50, pars->GC_58, amp[80]); 
  FFV1_0(w[22], w[45], w[50], pars->GC_1, amp[81]); 
  FFV1_0(w[22], w[45], w[31], pars->GC_11, amp[82]); 
  FFV2_3_0(w[22], w[45], w[52], pars->GC_50, pars->GC_58, amp[83]); 
  FFV1_0(w[51], w[21], w[39], pars->GC_1, amp[84]); 
  FFV1_0(w[51], w[21], w[14], pars->GC_11, amp[85]); 
  FFV2_3_0(w[51], w[21], w[41], pars->GC_50, pars->GC_58, amp[86]); 
  FFV1_0(w[22], w[53], w[39], pars->GC_1, amp[87]); 
  FFV1_0(w[22], w[53], w[14], pars->GC_11, amp[88]); 
  FFV2_3_0(w[22], w[53], w[41], pars->GC_50, pars->GC_58, amp[89]); 
  FFV1_0(w[0], w[45], w[46], pars->GC_1, amp[90]); 
  FFV1_0(w[0], w[45], w[24], pars->GC_11, amp[91]); 
  FFV2_3_0(w[0], w[45], w[47], pars->GC_50, pars->GC_58, amp[92]); 
  FFV1_0(w[0], w[53], w[48], pars->GC_1, amp[93]); 
  FFV1_0(w[0], w[53], w[27], pars->GC_11, amp[94]); 
  FFV2_3_0(w[0], w[53], w[49], pars->GC_50, pars->GC_58, amp[95]); 
  FFV1_0(w[56], w[21], w[57], pars->GC_2, amp[96]); 
  FFV1_0(w[56], w[21], w[58], pars->GC_11, amp[97]); 
  FFV2_5_0(w[56], w[21], w[59], pars->GC_51, pars->GC_58, amp[98]); 
  FFV1_0(w[56], w[54], w[23], pars->GC_2, amp[99]); 
  FFV1_0(w[56], w[54], w[24], pars->GC_11, amp[100]); 
  FFV2_5_0(w[56], w[54], w[25], pars->GC_51, pars->GC_58, amp[101]); 
  FFV1_0(w[30], w[21], w[60], pars->GC_2, amp[102]); 
  FFV1_0(w[30], w[21], w[61], pars->GC_11, amp[103]); 
  FFV2_5_0(w[30], w[21], w[62], pars->GC_51, pars->GC_58, amp[104]); 
  FFV1_0(w[22], w[33], w[60], pars->GC_2, amp[105]); 
  FFV1_0(w[22], w[33], w[61], pars->GC_11, amp[106]); 
  FFV2_5_0(w[22], w[33], w[62], pars->GC_51, pars->GC_58, amp[107]); 
  FFV1_0(w[30], w[54], w[63], pars->GC_2, amp[108]); 
  FFV1_0(w[30], w[54], w[64], pars->GC_11, amp[109]); 
  FFV2_5_0(w[30], w[54], w[65], pars->GC_51, pars->GC_58, amp[110]); 
  FFV1_0(w[22], w[66], w[63], pars->GC_2, amp[111]); 
  FFV1_0(w[22], w[66], w[64], pars->GC_11, amp[112]); 
  FFV2_5_0(w[22], w[66], w[65], pars->GC_51, pars->GC_58, amp[113]); 
  FFV1_0(w[55], w[33], w[57], pars->GC_2, amp[114]); 
  FFV1_0(w[55], w[33], w[58], pars->GC_11, amp[115]); 
  FFV2_5_0(w[55], w[33], w[59], pars->GC_51, pars->GC_58, amp[116]); 
  FFV1_0(w[55], w[66], w[23], pars->GC_2, amp[117]); 
  FFV1_0(w[55], w[66], w[24], pars->GC_11, amp[118]); 
  FFV2_5_0(w[55], w[66], w[25], pars->GC_51, pars->GC_58, amp[119]); 
  FFV1_0(w[67], w[21], w[68], pars->GC_1, amp[120]); 
  FFV1_0(w[67], w[21], w[58], pars->GC_11, amp[121]); 
  FFV2_3_0(w[67], w[21], w[69], pars->GC_50, pars->GC_58, amp[122]); 
  FFV1_0(w[67], w[54], w[46], pars->GC_1, amp[123]); 
  FFV1_0(w[67], w[54], w[24], pars->GC_11, amp[124]); 
  FFV2_3_0(w[67], w[54], w[47], pars->GC_50, pars->GC_58, amp[125]); 
  FFV1_0(w[51], w[21], w[70], pars->GC_1, amp[126]); 
  FFV1_0(w[51], w[21], w[61], pars->GC_11, amp[127]); 
  FFV2_3_0(w[51], w[21], w[71], pars->GC_50, pars->GC_58, amp[128]); 
  FFV1_0(w[22], w[53], w[70], pars->GC_1, amp[129]); 
  FFV1_0(w[22], w[53], w[61], pars->GC_11, amp[130]); 
  FFV2_3_0(w[22], w[53], w[71], pars->GC_50, pars->GC_58, amp[131]); 
  FFV1_0(w[51], w[54], w[72], pars->GC_1, amp[132]); 
  FFV1_0(w[51], w[54], w[64], pars->GC_11, amp[133]); 
  FFV2_3_0(w[51], w[54], w[73], pars->GC_50, pars->GC_58, amp[134]); 
  FFV1_0(w[22], w[74], w[72], pars->GC_1, amp[135]); 
  FFV1_0(w[22], w[74], w[64], pars->GC_11, amp[136]); 
  FFV2_3_0(w[22], w[74], w[73], pars->GC_50, pars->GC_58, amp[137]); 
  FFV1_0(w[55], w[53], w[68], pars->GC_1, amp[138]); 
  FFV1_0(w[55], w[53], w[58], pars->GC_11, amp[139]); 
  FFV2_3_0(w[55], w[53], w[69], pars->GC_50, pars->GC_58, amp[140]); 
  FFV1_0(w[55], w[74], w[46], pars->GC_1, amp[141]); 
  FFV1_0(w[55], w[74], w[24], pars->GC_11, amp[142]); 
  FFV2_3_0(w[55], w[74], w[47], pars->GC_50, pars->GC_58, amp[143]); 
  FFV2_0(w[5], w[4], w[75], pars->GC_100, amp[144]); 
  FFV1_0(w[5], w[3], w[37], pars->GC_2, amp[145]); 
  FFV1_0(w[5], w[3], w[10], pars->GC_11, amp[146]); 
  FFV2_5_0(w[5], w[3], w[38], pars->GC_51, pars->GC_58, amp[147]); 
  FFV1_0(w[40], w[4], w[12], pars->GC_1, amp[148]); 
  FFV1_0(w[40], w[4], w[14], pars->GC_11, amp[149]); 
  FFV2_3_0(w[40], w[4], w[15], pars->GC_50, pars->GC_58, amp[150]); 
  FFV1_0(w[1], w[42], w[12], pars->GC_1, amp[151]); 
  FFV1_0(w[1], w[42], w[14], pars->GC_11, amp[152]); 
  FFV2_3_0(w[1], w[42], w[15], pars->GC_50, pars->GC_58, amp[153]); 
  FFV2_0(w[40], w[3], w[76], pars->GC_100, amp[154]); 
  VVV1_0(w[76], w[75], w[2], pars->GC_53, amp[155]); 
  FFV2_0(w[1], w[20], w[76], pars->GC_100, amp[156]); 
  FFV2_0(w[0], w[42], w[75], pars->GC_100, amp[157]); 
  FFV1_0(w[0], w[20], w[37], pars->GC_2, amp[158]); 
  FFV1_0(w[0], w[20], w[10], pars->GC_11, amp[159]); 
  FFV2_5_0(w[0], w[20], w[38], pars->GC_51, pars->GC_58, amp[160]); 
  FFV2_0(w[5], w[3], w[77], pars->GC_100, amp[161]); 
  FFV1_0(w[5], w[21], w[48], pars->GC_2, amp[162]); 
  FFV1_0(w[5], w[21], w[27], pars->GC_11, amp[163]); 
  FFV2_5_0(w[5], w[21], w[49], pars->GC_51, pars->GC_58, amp[164]); 
  FFV1_0(w[51], w[3], w[29], pars->GC_1, amp[165]); 
  FFV1_0(w[51], w[3], w[31], pars->GC_11, amp[166]); 
  FFV2_3_0(w[51], w[3], w[32], pars->GC_50, pars->GC_58, amp[167]); 
  FFV1_0(w[22], w[45], w[29], pars->GC_1, amp[168]); 
  FFV1_0(w[22], w[45], w[31], pars->GC_11, amp[169]); 
  FFV2_3_0(w[22], w[45], w[32], pars->GC_50, pars->GC_58, amp[170]); 
  FFV2_0(w[51], w[21], w[78], pars->GC_100, amp[171]); 
  VVV1_0(w[78], w[77], w[2], pars->GC_53, amp[172]); 
  FFV2_0(w[22], w[33], w[78], pars->GC_100, amp[173]); 
  FFV2_0(w[0], w[45], w[77], pars->GC_100, amp[174]); 
  FFV1_0(w[0], w[33], w[48], pars->GC_2, amp[175]); 
  FFV1_0(w[0], w[33], w[27], pars->GC_11, amp[176]); 
  FFV2_5_0(w[0], w[33], w[49], pars->GC_51, pars->GC_58, amp[177]); 
  FFV2_0(w[5], w[21], w[79], pars->GC_100, amp[178]); 
  FFV1_0(w[5], w[3], w[46], pars->GC_2, amp[179]); 
  FFV1_0(w[5], w[3], w[24], pars->GC_11, amp[180]); 
  FFV2_5_0(w[5], w[3], w[47], pars->GC_51, pars->GC_58, amp[181]); 
  FFV1_0(w[51], w[21], w[12], pars->GC_1, amp[182]); 
  FFV1_0(w[51], w[21], w[14], pars->GC_11, amp[183]); 
  FFV2_3_0(w[51], w[21], w[15], pars->GC_50, pars->GC_58, amp[184]); 
  FFV1_0(w[22], w[53], w[12], pars->GC_1, amp[185]); 
  FFV1_0(w[22], w[53], w[14], pars->GC_11, amp[186]); 
  FFV2_3_0(w[22], w[53], w[15], pars->GC_50, pars->GC_58, amp[187]); 
  FFV2_0(w[51], w[3], w[80], pars->GC_100, amp[188]); 
  VVV1_0(w[80], w[79], w[2], pars->GC_53, amp[189]); 
  FFV2_0(w[22], w[20], w[80], pars->GC_100, amp[190]); 
  FFV2_0(w[0], w[53], w[79], pars->GC_100, amp[191]); 
  FFV1_0(w[0], w[20], w[46], pars->GC_2, amp[192]); 
  FFV1_0(w[0], w[20], w[24], pars->GC_11, amp[193]); 
  FFV2_5_0(w[0], w[20], w[47], pars->GC_51, pars->GC_58, amp[194]); 
  FFV2_0(w[30], w[3], w[80], pars->GC_100, amp[195]); 
  FFV1_0(w[30], w[21], w[39], pars->GC_2, amp[196]); 
  FFV1_0(w[30], w[21], w[14], pars->GC_11, amp[197]); 
  FFV2_5_0(w[30], w[21], w[41], pars->GC_51, pars->GC_58, amp[198]); 
  FFV1_0(w[34], w[3], w[23], pars->GC_1, amp[199]); 
  FFV1_0(w[34], w[3], w[24], pars->GC_11, amp[200]); 
  FFV2_3_0(w[34], w[3], w[25], pars->GC_50, pars->GC_58, amp[201]); 
  FFV1_0(w[0], w[45], w[23], pars->GC_1, amp[202]); 
  FFV1_0(w[0], w[45], w[24], pars->GC_11, amp[203]); 
  FFV2_3_0(w[0], w[45], w[25], pars->GC_50, pars->GC_58, amp[204]); 
  FFV2_0(w[34], w[21], w[79], pars->GC_100, amp[205]); 
  VVV1_0(w[79], w[80], w[2], pars->GC_53, amp[206]); 
  FFV2_0(w[0], w[33], w[79], pars->GC_100, amp[207]); 
  FFV2_0(w[22], w[45], w[80], pars->GC_100, amp[208]); 
  FFV1_0(w[22], w[33], w[39], pars->GC_2, amp[209]); 
  FFV1_0(w[22], w[33], w[14], pars->GC_11, amp[210]); 
  FFV2_5_0(w[22], w[33], w[41], pars->GC_51, pars->GC_58, amp[211]); 
  FFV2_0(w[30], w[21], w[78], pars->GC_100, amp[212]); 
  FFV1_0(w[30], w[3], w[50], pars->GC_2, amp[213]); 
  FFV1_0(w[30], w[3], w[31], pars->GC_11, amp[214]); 
  FFV2_5_0(w[30], w[3], w[52], pars->GC_51, pars->GC_58, amp[215]); 
  FFV1_0(w[34], w[21], w[26], pars->GC_1, amp[216]); 
  FFV1_0(w[34], w[21], w[27], pars->GC_11, amp[217]); 
  FFV2_3_0(w[34], w[21], w[28], pars->GC_50, pars->GC_58, amp[218]); 
  FFV1_0(w[0], w[53], w[26], pars->GC_1, amp[219]); 
  FFV1_0(w[0], w[53], w[27], pars->GC_11, amp[220]); 
  FFV2_3_0(w[0], w[53], w[28], pars->GC_50, pars->GC_58, amp[221]); 
  FFV2_0(w[34], w[3], w[77], pars->GC_100, amp[222]); 
  VVV1_0(w[77], w[78], w[2], pars->GC_53, amp[223]); 
  FFV2_0(w[0], w[20], w[77], pars->GC_100, amp[224]); 
  FFV2_0(w[22], w[53], w[78], pars->GC_100, amp[225]); 
  FFV1_0(w[22], w[20], w[50], pars->GC_2, amp[226]); 
  FFV1_0(w[22], w[20], w[31], pars->GC_11, amp[227]); 
  FFV2_5_0(w[22], w[20], w[52], pars->GC_51, pars->GC_58, amp[228]); 
  FFV2_0(w[56], w[21], w[81], pars->GC_100, amp[229]); 
  FFV1_0(w[56], w[54], w[46], pars->GC_2, amp[230]); 
  FFV1_0(w[56], w[54], w[24], pars->GC_11, amp[231]); 
  FFV2_5_0(w[56], w[54], w[47], pars->GC_51, pars->GC_58, amp[232]); 
  FFV1_0(w[51], w[21], w[60], pars->GC_1, amp[233]); 
  FFV1_0(w[51], w[21], w[61], pars->GC_11, amp[234]); 
  FFV2_3_0(w[51], w[21], w[62], pars->GC_50, pars->GC_58, amp[235]); 
  FFV1_0(w[22], w[53], w[60], pars->GC_1, amp[236]); 
  FFV1_0(w[22], w[53], w[61], pars->GC_11, amp[237]); 
  FFV2_3_0(w[22], w[53], w[62], pars->GC_50, pars->GC_58, amp[238]); 
  FFV2_0(w[51], w[54], w[82], pars->GC_100, amp[239]); 
  VVV1_0(w[82], w[81], w[2], pars->GC_53, amp[240]); 
  FFV2_0(w[22], w[66], w[82], pars->GC_100, amp[241]); 
  FFV2_0(w[55], w[53], w[81], pars->GC_100, amp[242]); 
  FFV1_0(w[55], w[66], w[46], pars->GC_2, amp[243]); 
  FFV1_0(w[55], w[66], w[24], pars->GC_11, amp[244]); 
  FFV2_5_0(w[55], w[66], w[47], pars->GC_51, pars->GC_58, amp[245]); 
  FFV1_0(w[5], w[3], w[9], pars->GC_2, amp[246]); 
  FFV1_0(w[5], w[3], w[10], pars->GC_11, amp[247]); 
  FFV2_5_0(w[5], w[3], w[11], pars->GC_51, pars->GC_58, amp[248]); 
  FFV1_0(w[13], w[4], w[12], pars->GC_2, amp[249]); 
  FFV1_0(w[13], w[4], w[14], pars->GC_11, amp[250]); 
  FFV2_5_0(w[13], w[4], w[15], pars->GC_51, pars->GC_58, amp[251]); 
  FFV1_0(w[1], w[16], w[12], pars->GC_2, amp[252]); 
  FFV1_0(w[1], w[16], w[14], pars->GC_11, amp[253]); 
  FFV2_5_0(w[1], w[16], w[15], pars->GC_51, pars->GC_58, amp[254]); 
  FFV1_0(w[0], w[20], w[9], pars->GC_2, amp[255]); 
  FFV1_0(w[0], w[20], w[10], pars->GC_11, amp[256]); 
  FFV2_5_0(w[0], w[20], w[11], pars->GC_51, pars->GC_58, amp[257]); 
  FFV1_0(w[5], w[3], w[37], pars->GC_2, amp[258]); 
  FFV1_0(w[5], w[3], w[10], pars->GC_11, amp[259]); 
  FFV2_5_0(w[5], w[3], w[38], pars->GC_51, pars->GC_58, amp[260]); 
  FFV1_0(w[40], w[4], w[12], pars->GC_1, amp[261]); 
  FFV1_0(w[40], w[4], w[14], pars->GC_11, amp[262]); 
  FFV2_3_0(w[40], w[4], w[15], pars->GC_50, pars->GC_58, amp[263]); 
  FFV1_0(w[1], w[42], w[12], pars->GC_1, amp[264]); 
  FFV1_0(w[1], w[42], w[14], pars->GC_11, amp[265]); 
  FFV2_3_0(w[1], w[42], w[15], pars->GC_50, pars->GC_58, amp[266]); 
  FFV1_0(w[0], w[20], w[37], pars->GC_2, amp[267]); 
  FFV1_0(w[0], w[20], w[10], pars->GC_11, amp[268]); 
  FFV2_5_0(w[0], w[20], w[38], pars->GC_51, pars->GC_58, amp[269]); 
  FFV1_0(w[5], w[21], w[26], pars->GC_2, amp[270]); 
  FFV1_0(w[5], w[21], w[27], pars->GC_11, amp[271]); 
  FFV2_5_0(w[5], w[21], w[28], pars->GC_51, pars->GC_58, amp[272]); 
  FFV1_0(w[30], w[3], w[29], pars->GC_2, amp[273]); 
  FFV1_0(w[30], w[3], w[31], pars->GC_11, amp[274]); 
  FFV2_5_0(w[30], w[3], w[32], pars->GC_51, pars->GC_58, amp[275]); 
  FFV1_0(w[22], w[20], w[29], pars->GC_2, amp[276]); 
  FFV1_0(w[22], w[20], w[31], pars->GC_11, amp[277]); 
  FFV2_5_0(w[22], w[20], w[32], pars->GC_51, pars->GC_58, amp[278]); 
  FFV1_0(w[0], w[33], w[26], pars->GC_2, amp[279]); 
  FFV1_0(w[0], w[33], w[27], pars->GC_11, amp[280]); 
  FFV2_5_0(w[0], w[33], w[28], pars->GC_51, pars->GC_58, amp[281]); 
  FFV1_0(w[5], w[21], w[48], pars->GC_2, amp[282]); 
  FFV1_0(w[5], w[21], w[27], pars->GC_11, amp[283]); 
  FFV2_5_0(w[5], w[21], w[49], pars->GC_51, pars->GC_58, amp[284]); 
  FFV1_0(w[51], w[3], w[29], pars->GC_1, amp[285]); 
  FFV1_0(w[51], w[3], w[31], pars->GC_11, amp[286]); 
  FFV2_3_0(w[51], w[3], w[32], pars->GC_50, pars->GC_58, amp[287]); 
  FFV1_0(w[22], w[45], w[29], pars->GC_1, amp[288]); 
  FFV1_0(w[22], w[45], w[31], pars->GC_11, amp[289]); 
  FFV2_3_0(w[22], w[45], w[32], pars->GC_50, pars->GC_58, amp[290]); 
  FFV1_0(w[0], w[33], w[48], pars->GC_2, amp[291]); 
  FFV1_0(w[0], w[33], w[27], pars->GC_11, amp[292]); 
  FFV2_5_0(w[0], w[33], w[49], pars->GC_51, pars->GC_58, amp[293]); 
  FFV1_0(w[5], w[3], w[23], pars->GC_2, amp[294]); 
  FFV1_0(w[5], w[3], w[24], pars->GC_11, amp[295]); 
  FFV2_5_0(w[5], w[3], w[25], pars->GC_51, pars->GC_58, amp[296]); 
  FFV1_0(w[30], w[21], w[12], pars->GC_2, amp[297]); 
  FFV1_0(w[30], w[21], w[14], pars->GC_11, amp[298]); 
  FFV2_5_0(w[30], w[21], w[15], pars->GC_51, pars->GC_58, amp[299]); 
  FFV1_0(w[22], w[33], w[12], pars->GC_2, amp[300]); 
  FFV1_0(w[22], w[33], w[14], pars->GC_11, amp[301]); 
  FFV2_5_0(w[22], w[33], w[15], pars->GC_51, pars->GC_58, amp[302]); 
  FFV1_0(w[0], w[20], w[23], pars->GC_2, amp[303]); 
  FFV1_0(w[0], w[20], w[24], pars->GC_11, amp[304]); 
  FFV2_5_0(w[0], w[20], w[25], pars->GC_51, pars->GC_58, amp[305]); 
  FFV1_0(w[5], w[3], w[46], pars->GC_2, amp[306]); 
  FFV1_0(w[5], w[3], w[24], pars->GC_11, amp[307]); 
  FFV2_5_0(w[5], w[3], w[47], pars->GC_51, pars->GC_58, amp[308]); 
  FFV1_0(w[51], w[21], w[12], pars->GC_1, amp[309]); 
  FFV1_0(w[51], w[21], w[14], pars->GC_11, amp[310]); 
  FFV2_3_0(w[51], w[21], w[15], pars->GC_50, pars->GC_58, amp[311]); 
  FFV1_0(w[22], w[53], w[12], pars->GC_1, amp[312]); 
  FFV1_0(w[22], w[53], w[14], pars->GC_11, amp[313]); 
  FFV2_3_0(w[22], w[53], w[15], pars->GC_50, pars->GC_58, amp[314]); 
  FFV1_0(w[0], w[20], w[46], pars->GC_2, amp[315]); 
  FFV1_0(w[0], w[20], w[24], pars->GC_11, amp[316]); 
  FFV2_5_0(w[0], w[20], w[47], pars->GC_51, pars->GC_58, amp[317]); 
  FFV1_0(w[34], w[3], w[37], pars->GC_1, amp[318]); 
  FFV1_0(w[34], w[3], w[10], pars->GC_11, amp[319]); 
  FFV2_3_0(w[34], w[3], w[38], pars->GC_50, pars->GC_58, amp[320]); 
  FFV1_0(w[40], w[4], w[39], pars->GC_1, amp[321]); 
  FFV1_0(w[40], w[4], w[14], pars->GC_11, amp[322]); 
  FFV2_3_0(w[40], w[4], w[41], pars->GC_50, pars->GC_58, amp[323]); 
  FFV1_0(w[1], w[42], w[39], pars->GC_1, amp[324]); 
  FFV1_0(w[1], w[42], w[14], pars->GC_11, amp[325]); 
  FFV2_3_0(w[1], w[42], w[41], pars->GC_50, pars->GC_58, amp[326]); 
  FFV1_0(w[0], w[45], w[37], pars->GC_1, amp[327]); 
  FFV1_0(w[0], w[45], w[10], pars->GC_11, amp[328]); 
  FFV2_3_0(w[0], w[45], w[38], pars->GC_50, pars->GC_58, amp[329]); 
  FFV1_0(w[30], w[21], w[39], pars->GC_2, amp[330]); 
  FFV1_0(w[30], w[21], w[14], pars->GC_11, amp[331]); 
  FFV2_5_0(w[30], w[21], w[41], pars->GC_51, pars->GC_58, amp[332]); 
  FFV1_0(w[34], w[3], w[23], pars->GC_1, amp[333]); 
  FFV1_0(w[34], w[3], w[24], pars->GC_11, amp[334]); 
  FFV2_3_0(w[34], w[3], w[25], pars->GC_50, pars->GC_58, amp[335]); 
  FFV1_0(w[0], w[45], w[23], pars->GC_1, amp[336]); 
  FFV1_0(w[0], w[45], w[24], pars->GC_11, amp[337]); 
  FFV2_3_0(w[0], w[45], w[25], pars->GC_50, pars->GC_58, amp[338]); 
  FFV1_0(w[22], w[33], w[39], pars->GC_2, amp[339]); 
  FFV1_0(w[22], w[33], w[14], pars->GC_11, amp[340]); 
  FFV2_5_0(w[22], w[33], w[41], pars->GC_51, pars->GC_58, amp[341]); 
  FFV1_0(w[30], w[3], w[50], pars->GC_2, amp[342]); 
  FFV1_0(w[30], w[3], w[31], pars->GC_11, amp[343]); 
  FFV2_5_0(w[30], w[3], w[52], pars->GC_51, pars->GC_58, amp[344]); 
  FFV1_0(w[34], w[21], w[26], pars->GC_1, amp[345]); 
  FFV1_0(w[34], w[21], w[27], pars->GC_11, amp[346]); 
  FFV2_3_0(w[34], w[21], w[28], pars->GC_50, pars->GC_58, amp[347]); 
  FFV1_0(w[0], w[53], w[26], pars->GC_1, amp[348]); 
  FFV1_0(w[0], w[53], w[27], pars->GC_11, amp[349]); 
  FFV2_3_0(w[0], w[53], w[28], pars->GC_50, pars->GC_58, amp[350]); 
  FFV1_0(w[22], w[20], w[50], pars->GC_2, amp[351]); 
  FFV1_0(w[22], w[20], w[31], pars->GC_11, amp[352]); 
  FFV2_5_0(w[22], w[20], w[52], pars->GC_51, pars->GC_58, amp[353]); 
  FFV1_0(w[34], w[21], w[48], pars->GC_1, amp[354]); 
  FFV1_0(w[34], w[21], w[27], pars->GC_11, amp[355]); 
  FFV2_3_0(w[34], w[21], w[49], pars->GC_50, pars->GC_58, amp[356]); 
  FFV1_0(w[51], w[3], w[50], pars->GC_1, amp[357]); 
  FFV1_0(w[51], w[3], w[31], pars->GC_11, amp[358]); 
  FFV2_3_0(w[51], w[3], w[52], pars->GC_50, pars->GC_58, amp[359]); 
  FFV1_0(w[22], w[45], w[50], pars->GC_1, amp[360]); 
  FFV1_0(w[22], w[45], w[31], pars->GC_11, amp[361]); 
  FFV2_3_0(w[22], w[45], w[52], pars->GC_50, pars->GC_58, amp[362]); 
  FFV1_0(w[0], w[53], w[48], pars->GC_1, amp[363]); 
  FFV1_0(w[0], w[53], w[27], pars->GC_11, amp[364]); 
  FFV2_3_0(w[0], w[53], w[49], pars->GC_50, pars->GC_58, amp[365]); 
  FFV1_0(w[34], w[3], w[46], pars->GC_1, amp[366]); 
  FFV1_0(w[34], w[3], w[24], pars->GC_11, amp[367]); 
  FFV2_3_0(w[34], w[3], w[47], pars->GC_50, pars->GC_58, amp[368]); 
  FFV1_0(w[51], w[21], w[39], pars->GC_1, amp[369]); 
  FFV1_0(w[51], w[21], w[14], pars->GC_11, amp[370]); 
  FFV2_3_0(w[51], w[21], w[41], pars->GC_50, pars->GC_58, amp[371]); 
  FFV1_0(w[22], w[53], w[39], pars->GC_1, amp[372]); 
  FFV1_0(w[22], w[53], w[14], pars->GC_11, amp[373]); 
  FFV2_3_0(w[22], w[53], w[41], pars->GC_50, pars->GC_58, amp[374]); 
  FFV1_0(w[0], w[45], w[46], pars->GC_1, amp[375]); 
  FFV1_0(w[0], w[45], w[24], pars->GC_11, amp[376]); 
  FFV2_3_0(w[0], w[45], w[47], pars->GC_50, pars->GC_58, amp[377]); 
  FFV1_0(w[56], w[54], w[23], pars->GC_2, amp[378]); 
  FFV1_0(w[56], w[54], w[24], pars->GC_11, amp[379]); 
  FFV2_5_0(w[56], w[54], w[25], pars->GC_51, pars->GC_58, amp[380]); 
  FFV1_0(w[30], w[21], w[60], pars->GC_2, amp[381]); 
  FFV1_0(w[30], w[21], w[61], pars->GC_11, amp[382]); 
  FFV2_5_0(w[30], w[21], w[62], pars->GC_51, pars->GC_58, amp[383]); 
  FFV1_0(w[22], w[33], w[60], pars->GC_2, amp[384]); 
  FFV1_0(w[22], w[33], w[61], pars->GC_11, amp[385]); 
  FFV2_5_0(w[22], w[33], w[62], pars->GC_51, pars->GC_58, amp[386]); 
  FFV1_0(w[55], w[66], w[23], pars->GC_2, amp[387]); 
  FFV1_0(w[55], w[66], w[24], pars->GC_11, amp[388]); 
  FFV2_5_0(w[55], w[66], w[25], pars->GC_51, pars->GC_58, amp[389]); 
  FFV1_0(w[56], w[54], w[46], pars->GC_2, amp[390]); 
  FFV1_0(w[56], w[54], w[24], pars->GC_11, amp[391]); 
  FFV2_5_0(w[56], w[54], w[47], pars->GC_51, pars->GC_58, amp[392]); 
  FFV1_0(w[51], w[21], w[60], pars->GC_1, amp[393]); 
  FFV1_0(w[51], w[21], w[61], pars->GC_11, amp[394]); 
  FFV2_3_0(w[51], w[21], w[62], pars->GC_50, pars->GC_58, amp[395]); 
  FFV1_0(w[22], w[53], w[60], pars->GC_1, amp[396]); 
  FFV1_0(w[22], w[53], w[61], pars->GC_11, amp[397]); 
  FFV2_3_0(w[22], w[53], w[62], pars->GC_50, pars->GC_58, amp[398]); 
  FFV1_0(w[55], w[66], w[46], pars->GC_2, amp[399]); 
  FFV1_0(w[55], w[66], w[24], pars->GC_11, amp[400]); 
  FFV2_5_0(w[55], w[66], w[47], pars->GC_51, pars->GC_58, amp[401]); 
  FFV1_0(w[67], w[54], w[46], pars->GC_1, amp[402]); 
  FFV1_0(w[67], w[54], w[24], pars->GC_11, amp[403]); 
  FFV2_3_0(w[67], w[54], w[47], pars->GC_50, pars->GC_58, amp[404]); 
  FFV1_0(w[51], w[21], w[70], pars->GC_1, amp[405]); 
  FFV1_0(w[51], w[21], w[61], pars->GC_11, amp[406]); 
  FFV2_3_0(w[51], w[21], w[71], pars->GC_50, pars->GC_58, amp[407]); 
  FFV1_0(w[22], w[53], w[70], pars->GC_1, amp[408]); 
  FFV1_0(w[22], w[53], w[61], pars->GC_11, amp[409]); 
  FFV2_3_0(w[22], w[53], w[71], pars->GC_50, pars->GC_58, amp[410]); 
  FFV1_0(w[55], w[74], w[46], pars->GC_1, amp[411]); 
  FFV1_0(w[55], w[74], w[24], pars->GC_11, amp[412]); 
  FFV2_3_0(w[55], w[74], w[47], pars->GC_50, pars->GC_58, amp[413]); 
  FFV2_0(w[5], w[4], w[75], pars->GC_100, amp[414]); 
  FFV2_0(w[40], w[3], w[76], pars->GC_100, amp[415]); 
  VVV1_0(w[76], w[75], w[2], pars->GC_53, amp[416]); 
  FFV2_0(w[1], w[20], w[76], pars->GC_100, amp[417]); 
  FFV2_0(w[0], w[42], w[75], pars->GC_100, amp[418]); 
  FFV2_0(w[5], w[3], w[77], pars->GC_100, amp[419]); 
  FFV2_0(w[51], w[21], w[78], pars->GC_100, amp[420]); 
  VVV1_0(w[78], w[77], w[2], pars->GC_53, amp[421]); 
  FFV2_0(w[22], w[33], w[78], pars->GC_100, amp[422]); 
  FFV2_0(w[0], w[45], w[77], pars->GC_100, amp[423]); 
  FFV2_0(w[5], w[21], w[79], pars->GC_100, amp[424]); 
  FFV2_0(w[51], w[3], w[80], pars->GC_100, amp[425]); 
  VVV1_0(w[80], w[79], w[2], pars->GC_53, amp[426]); 
  FFV2_0(w[22], w[20], w[80], pars->GC_100, amp[427]); 
  FFV2_0(w[0], w[53], w[79], pars->GC_100, amp[428]); 
  FFV2_0(w[30], w[3], w[80], pars->GC_100, amp[429]); 
  FFV2_0(w[34], w[21], w[79], pars->GC_100, amp[430]); 
  VVV1_0(w[79], w[80], w[2], pars->GC_53, amp[431]); 
  FFV2_0(w[0], w[33], w[79], pars->GC_100, amp[432]); 
  FFV2_0(w[22], w[45], w[80], pars->GC_100, amp[433]); 
  FFV2_0(w[30], w[21], w[78], pars->GC_100, amp[434]); 
  FFV2_0(w[34], w[3], w[77], pars->GC_100, amp[435]); 
  VVV1_0(w[77], w[78], w[2], pars->GC_53, amp[436]); 
  FFV2_0(w[0], w[20], w[77], pars->GC_100, amp[437]); 
  FFV2_0(w[22], w[53], w[78], pars->GC_100, amp[438]); 
  FFV2_0(w[56], w[21], w[81], pars->GC_100, amp[439]); 
  FFV2_0(w[51], w[54], w[82], pars->GC_100, amp[440]); 
  VVV1_0(w[82], w[81], w[2], pars->GC_53, amp[441]); 
  FFV2_0(w[22], w[66], w[82], pars->GC_100, amp[442]); 
  FFV2_0(w[55], w[53], w[81], pars->GC_100, amp[443]); 


}
double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uu_zuu() 
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
  jamp[0] = +1./2. * amp[1] - amp[3] + 1./6. * amp[4] - amp[5] - amp[6] + 1./6.
      * amp[7] - amp[8] - amp[9] + 1./6. * amp[10] - amp[11] + 1./2. * amp[13]
      + 1./2. * amp[16] + 1./2. * amp[19] - amp[21] + 1./6. * amp[22] - amp[23];
  jamp[1] = +amp[0] - 1./6. * amp[1] + amp[2] - 1./2. * amp[4] - 1./2. * amp[7]
      - 1./2. * amp[10] + amp[12] - 1./6. * amp[13] + amp[14] + amp[15] - 1./6.
      * amp[16] + amp[17] + amp[18] - 1./6. * amp[19] + amp[20] - 1./2. *
      amp[22];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uux_zuux() 
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
  jamp[0] = +1./2. * amp[25] - amp[27] + 1./6. * amp[28] - amp[29] - amp[30] +
      1./6. * amp[31] - amp[32] - amp[33] + 1./6. * amp[34] - amp[35] + 1./2. *
      amp[37] + 1./2. * amp[40] + 1./2. * amp[43] - amp[45] + 1./6. * amp[46] -
      amp[47];
  jamp[1] = +amp[24] - 1./6. * amp[25] + amp[26] - 1./2. * amp[28] - 1./2. *
      amp[31] - 1./2. * amp[34] + amp[36] - 1./6. * amp[37] + amp[38] + amp[39]
      - 1./6. * amp[40] + amp[41] + amp[42] - 1./6. * amp[43] + amp[44] - 1./2.
      * amp[46];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dd_zdd() 
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
  jamp[0] = +1./2. * amp[49] - amp[51] + 1./6. * amp[52] - amp[53] - amp[54] +
      1./6. * amp[55] - amp[56] - amp[57] + 1./6. * amp[58] - amp[59] + 1./2. *
      amp[61] + 1./2. * amp[64] + 1./2. * amp[67] - amp[69] + 1./6. * amp[70] -
      amp[71];
  jamp[1] = +amp[48] - 1./6. * amp[49] + amp[50] - 1./2. * amp[52] - 1./2. *
      amp[55] - 1./2. * amp[58] + amp[60] - 1./6. * amp[61] + amp[62] + amp[63]
      - 1./6. * amp[64] + amp[65] + amp[66] - 1./6. * amp[67] + amp[68] - 1./2.
      * amp[70];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ddx_zddx() 
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
  jamp[0] = +1./2. * amp[73] - amp[75] + 1./6. * amp[76] - amp[77] - amp[78] +
      1./6. * amp[79] - amp[80] - amp[81] + 1./6. * amp[82] - amp[83] + 1./2. *
      amp[85] + 1./2. * amp[88] + 1./2. * amp[91] - amp[93] + 1./6. * amp[94] -
      amp[95];
  jamp[1] = +amp[72] - 1./6. * amp[73] + amp[74] - 1./2. * amp[76] - 1./2. *
      amp[79] - 1./2. * amp[82] + amp[84] - 1./6. * amp[85] + amp[86] + amp[87]
      - 1./6. * amp[88] + amp[89] + amp[90] - 1./6. * amp[91] + amp[92] - 1./2.
      * amp[94];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uxux_zuxux() 
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
  jamp[0] = +1./2. * amp[97] - amp[99] + 1./6. * amp[100] - amp[101] - amp[102]
      + 1./6. * amp[103] - amp[104] - amp[105] + 1./6. * amp[106] - amp[107] +
      1./2. * amp[109] + 1./2. * amp[112] + 1./2. * amp[115] - amp[117] + 1./6.
      * amp[118] - amp[119];
  jamp[1] = +amp[96] - 1./6. * amp[97] + amp[98] - 1./2. * amp[100] - 1./2. *
      amp[103] - 1./2. * amp[106] + amp[108] - 1./6. * amp[109] + amp[110] +
      amp[111] - 1./6. * amp[112] + amp[113] + amp[114] - 1./6. * amp[115] +
      amp[116] - 1./2. * amp[118];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dxdx_zdxdx() 
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
  jamp[0] = +1./2. * amp[121] - amp[123] + 1./6. * amp[124] - amp[125] -
      amp[126] + 1./6. * amp[127] - amp[128] - amp[129] + 1./6. * amp[130] -
      amp[131] + 1./2. * amp[133] + 1./2. * amp[136] + 1./2. * amp[139] -
      amp[141] + 1./6. * amp[142] - amp[143];
  jamp[1] = +amp[120] - 1./6. * amp[121] + amp[122] - 1./2. * amp[124] - 1./2.
      * amp[127] - 1./2. * amp[130] + amp[132] - 1./6. * amp[133] + amp[134] +
      amp[135] - 1./6. * amp[136] + amp[137] + amp[138] - 1./6. * amp[139] +
      amp[140] - 1./2. * amp[142];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ud_zud() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[145] + 1./6. * amp[146] - amp[147] - amp[148] + 1./6. *
      amp[149] - amp[150] - amp[151] + 1./6. * amp[152] - amp[153] - amp[158] +
      1./6. * amp[159] - amp[160];
  jamp[1] = +amp[144] - 1./2. * amp[146] - 1./2. * amp[149] - 1./2. * amp[152]
      + amp[154] + amp[155] + amp[156] + amp[157] - 1./2. * amp[159];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uux_zddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[162] + 1./6. * amp[163] - amp[164] - amp[165] + 1./6. *
      amp[166] - amp[167] - amp[168] + 1./6. * amp[169] - amp[170] - amp[175] +
      1./6. * amp[176] - amp[177];
  jamp[1] = +amp[161] - 1./2. * amp[163] - 1./2. * amp[166] - 1./2. * amp[169]
      + amp[171] + amp[172] + amp[173] + amp[174] - 1./2. * amp[176];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_udx_zudx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[178] + 1./2. * amp[180] + 1./2. * amp[183] + 1./2. * amp[186]
      - amp[188] - amp[189] - amp[190] - amp[191] + 1./2. * amp[193];
  jamp[1] = +amp[179] - 1./6. * amp[180] + amp[181] + amp[182] - 1./6. *
      amp[183] + amp[184] + amp[185] - 1./6. * amp[186] + amp[187] + amp[192] -
      1./6. * amp[193] + amp[194];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dux_zdux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[195] + 1./2. * amp[197] + 1./2. * amp[200] + 1./2. * amp[203]
      - amp[205] - amp[206] - amp[207] - amp[208] + 1./2. * amp[210];
  jamp[1] = +amp[196] - 1./6. * amp[197] + amp[198] + amp[199] - 1./6. *
      amp[200] + amp[201] + amp[202] - 1./6. * amp[203] + amp[204] + amp[209] -
      1./6. * amp[210] + amp[211];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ddx_zuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[213] + 1./6. * amp[214] - amp[215] - amp[216] + 1./6. *
      amp[217] - amp[218] - amp[219] + 1./6. * amp[220] - amp[221] - amp[226] +
      1./6. * amp[227] - amp[228];
  jamp[1] = +amp[212] - 1./2. * amp[214] - 1./2. * amp[217] - 1./2. * amp[220]
      + amp[222] + amp[223] + amp[224] + amp[225] - 1./2. * amp[227];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uxdx_zuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = -amp[230] + 1./6. * amp[231] - amp[232] - amp[233] + 1./6. *
      amp[234] - amp[235] - amp[236] + 1./6. * amp[237] - amp[238] - amp[243] +
      1./6. * amp[244] - amp[245];
  jamp[1] = +amp[229] - 1./2. * amp[231] - 1./2. * amp[234] - 1./2. * amp[237]
      + amp[239] + amp[240] + amp[241] + amp[242] - 1./2. * amp[244];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uc_zuc() 
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
  jamp[0] = -amp[246] + 1./6. * amp[247] - amp[248] - amp[249] + 1./6. *
      amp[250] - amp[251] - amp[252] + 1./6. * amp[253] - amp[254] - amp[255] +
      1./6. * amp[256] - amp[257];
  jamp[1] = +1./2. * (-amp[247] - amp[250] - amp[253] - amp[256]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_us_zus() 
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
  jamp[0] = -amp[258] + 1./6. * amp[259] - amp[260] - amp[261] + 1./6. *
      amp[262] - amp[263] - amp[264] + 1./6. * amp[265] - amp[266] - amp[267] +
      1./6. * amp[268] - amp[269];
  jamp[1] = +1./2. * (-amp[259] - amp[262] - amp[265] - amp[268]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uux_zccx() 
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
  jamp[0] = -amp[270] + 1./6. * amp[271] - amp[272] - amp[273] + 1./6. *
      amp[274] - amp[275] - amp[276] + 1./6. * amp[277] - amp[278] - amp[279] +
      1./6. * amp[280] - amp[281];
  jamp[1] = +1./2. * (-amp[271] - amp[274] - amp[277] - amp[280]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uux_zssx() 
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
  jamp[0] = -amp[282] + 1./6. * amp[283] - amp[284] - amp[285] + 1./6. *
      amp[286] - amp[287] - amp[288] + 1./6. * amp[289] - amp[290] - amp[291] +
      1./6. * amp[292] - amp[293];
  jamp[1] = +1./2. * (-amp[283] - amp[286] - amp[289] - amp[292]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ucx_zucx() 
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
  jamp[0] = +1./2. * (+amp[295] + amp[298] + amp[301] + amp[304]); 
  jamp[1] = +amp[294] - 1./6. * amp[295] + amp[296] + amp[297] - 1./6. *
      amp[298] + amp[299] + amp[300] - 1./6. * amp[301] + amp[302] + amp[303] -
      1./6. * amp[304] + amp[305];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_usx_zusx() 
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
  jamp[0] = +1./2. * (+amp[307] + amp[310] + amp[313] + amp[316]); 
  jamp[1] = +amp[306] - 1./6. * amp[307] + amp[308] + amp[309] - 1./6. *
      amp[310] + amp[311] + amp[312] - 1./6. * amp[313] + amp[314] + amp[315] -
      1./6. * amp[316] + amp[317];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ds_zds() 
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
  jamp[0] = -amp[318] + 1./6. * amp[319] - amp[320] - amp[321] + 1./6. *
      amp[322] - amp[323] - amp[324] + 1./6. * amp[325] - amp[326] - amp[327] +
      1./6. * amp[328] - amp[329];
  jamp[1] = +1./2. * (-amp[319] - amp[322] - amp[325] - amp[328]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dcx_zdcx() 
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
  jamp[0] = +1./2. * (+amp[331] + amp[334] + amp[337] + amp[340]); 
  jamp[1] = +amp[330] - 1./6. * amp[331] + amp[332] + amp[333] - 1./6. *
      amp[334] + amp[335] + amp[336] - 1./6. * amp[337] + amp[338] + amp[339] -
      1./6. * amp[340] + amp[341];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ddx_zccx() 
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
  jamp[0] = -amp[342] + 1./6. * amp[343] - amp[344] - amp[345] + 1./6. *
      amp[346] - amp[347] - amp[348] + 1./6. * amp[349] - amp[350] - amp[351] +
      1./6. * amp[352] - amp[353];
  jamp[1] = +1./2. * (-amp[343] - amp[346] - amp[349] - amp[352]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ddx_zssx() 
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
  jamp[0] = -amp[354] + 1./6. * amp[355] - amp[356] - amp[357] + 1./6. *
      amp[358] - amp[359] - amp[360] + 1./6. * amp[361] - amp[362] - amp[363] +
      1./6. * amp[364] - amp[365];
  jamp[1] = +1./2. * (-amp[355] - amp[358] - amp[361] - amp[364]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dsx_zdsx() 
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
  jamp[0] = +1./2. * (+amp[367] + amp[370] + amp[373] + amp[376]); 
  jamp[1] = +amp[366] - 1./6. * amp[367] + amp[368] + amp[369] - 1./6. *
      amp[370] + amp[371] + amp[372] - 1./6. * amp[373] + amp[374] + amp[375] -
      1./6. * amp[376] + amp[377];

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uxcx_zuxcx() 
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
  jamp[0] = -amp[378] + 1./6. * amp[379] - amp[380] - amp[381] + 1./6. *
      amp[382] - amp[383] - amp[384] + 1./6. * amp[385] - amp[386] - amp[387] +
      1./6. * amp[388] - amp[389];
  jamp[1] = +1./2. * (-amp[379] - amp[382] - amp[385] - amp[388]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uxsx_zuxsx() 
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
  jamp[0] = -amp[390] + 1./6. * amp[391] - amp[392] - amp[393] + 1./6. *
      amp[394] - amp[395] - amp[396] + 1./6. * amp[397] - amp[398] - amp[399] +
      1./6. * amp[400] - amp[401];
  jamp[1] = +1./2. * (-amp[391] - amp[394] - amp[397] - amp[400]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dxsx_zdxsx() 
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
  jamp[0] = -amp[402] + 1./6. * amp[403] - amp[404] - amp[405] + 1./6. *
      amp[406] - amp[407] - amp[408] + 1./6. * amp[409] - amp[410] - amp[411] +
      1./6. * amp[412] - amp[413];
  jamp[1] = +1./2. * (-amp[403] - amp[406] - amp[409] - amp[412]); 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_us_zcd() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[414] + amp[415] + amp[416] + amp[417] + amp[418]; 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_ucx_zdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[419] + amp[420] + amp[421] + amp[422] + amp[423]; 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_udx_zcsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[424] - amp[425] - amp[426] - amp[427] - amp[428]; 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dux_zscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = -amp[429] - amp[430] - amp[431] - amp[432] - amp[433]; 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_dsx_zucx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[434] + amp[435] + amp[436] + amp[437] + amp[438]; 

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

double PY8MEs_R8_P15_sm_qq_zqq::matrix_8_uxsx_zcxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 5;
  const int ncolor = 1; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1}; 
  static const double cf[ncolor][ncolor] = {{9}}; 

  // Calculate color flows
  jamp[0] = +amp[439] + amp[440] + amp[441] + amp[442] + amp[443]; 

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


}  // end namespace PY8MEs_namespace

