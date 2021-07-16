//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R5_P14_sm_qq_qqa.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u > u u a WEIGHTED<=99 @5
// Process: c c > c c a WEIGHTED<=99 @5
// Process: u u~ > u u~ a WEIGHTED<=99 @5
// Process: c c~ > c c~ a WEIGHTED<=99 @5
// Process: d d > d d a WEIGHTED<=99 @5
// Process: s s > s s a WEIGHTED<=99 @5
// Process: d d~ > d d~ a WEIGHTED<=99 @5
// Process: s s~ > s s~ a WEIGHTED<=99 @5
// Process: u~ u~ > u~ u~ a WEIGHTED<=99 @5
// Process: c~ c~ > c~ c~ a WEIGHTED<=99 @5
// Process: d~ d~ > d~ d~ a WEIGHTED<=99 @5
// Process: s~ s~ > s~ s~ a WEIGHTED<=99 @5
// Process: u d > u d a WEIGHTED<=99 @5
// Process: c s > c s a WEIGHTED<=99 @5
// Process: u u~ > d d~ a WEIGHTED<=99 @5
// Process: c c~ > s s~ a WEIGHTED<=99 @5
// Process: u d~ > u d~ a WEIGHTED<=99 @5
// Process: c s~ > c s~ a WEIGHTED<=99 @5
// Process: d u~ > d u~ a WEIGHTED<=99 @5
// Process: s c~ > s c~ a WEIGHTED<=99 @5
// Process: d d~ > u u~ a WEIGHTED<=99 @5
// Process: s s~ > c c~ a WEIGHTED<=99 @5
// Process: u~ d~ > u~ d~ a WEIGHTED<=99 @5
// Process: c~ s~ > c~ s~ a WEIGHTED<=99 @5
// Process: u c > u c a WEIGHTED<=99 @5
// Process: u s > u s a WEIGHTED<=99 @5
// Process: c d > c d a WEIGHTED<=99 @5
// Process: u u~ > c c~ a WEIGHTED<=99 @5
// Process: c c~ > u u~ a WEIGHTED<=99 @5
// Process: u u~ > s s~ a WEIGHTED<=99 @5
// Process: c c~ > d d~ a WEIGHTED<=99 @5
// Process: u c~ > u c~ a WEIGHTED<=99 @5
// Process: c u~ > c u~ a WEIGHTED<=99 @5
// Process: u s~ > u s~ a WEIGHTED<=99 @5
// Process: c d~ > c d~ a WEIGHTED<=99 @5
// Process: d s > d s a WEIGHTED<=99 @5
// Process: d c~ > d c~ a WEIGHTED<=99 @5
// Process: s u~ > s u~ a WEIGHTED<=99 @5
// Process: d d~ > c c~ a WEIGHTED<=99 @5
// Process: s s~ > u u~ a WEIGHTED<=99 @5
// Process: d d~ > s s~ a WEIGHTED<=99 @5
// Process: s s~ > d d~ a WEIGHTED<=99 @5
// Process: d s~ > d s~ a WEIGHTED<=99 @5
// Process: s d~ > s d~ a WEIGHTED<=99 @5
// Process: u~ c~ > u~ c~ a WEIGHTED<=99 @5
// Process: u~ s~ > u~ s~ a WEIGHTED<=99 @5
// Process: c~ d~ > c~ d~ a WEIGHTED<=99 @5
// Process: d~ s~ > d~ s~ a WEIGHTED<=99 @5
// Process: u s > c d a WEIGHTED<=99 @5
// Process: c d > u s a WEIGHTED<=99 @5
// Process: u c~ > d s~ a WEIGHTED<=99 @5
// Process: c u~ > s d~ a WEIGHTED<=99 @5
// Process: u d~ > c s~ a WEIGHTED<=99 @5
// Process: c s~ > u d~ a WEIGHTED<=99 @5
// Process: d u~ > s c~ a WEIGHTED<=99 @5
// Process: s c~ > d u~ a WEIGHTED<=99 @5
// Process: d s~ > u c~ a WEIGHTED<=99 @5
// Process: s d~ > c u~ a WEIGHTED<=99 @5
// Process: u~ s~ > c~ d~ a WEIGHTED<=99 @5
// Process: c~ d~ > u~ s~ a WEIGHTED<=99 @5

// Exception class
class PY8MEs_R5_P14_sm_qq_qqaException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R5_P14_sm_qq_qqa'."; 
  }
}
PY8MEs_R5_P14_sm_qq_qqa_exception; 

std::set<int> PY8MEs_R5_P14_sm_qq_qqa::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R5_P14_sm_qq_qqa::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
    -1}, {-1, -1, -1, -1, 1}, {-1, -1, -1, 1, -1}, {-1, -1, -1, 1, 1}, {-1, -1,
    1, -1, -1}, {-1, -1, 1, -1, 1}, {-1, -1, 1, 1, -1}, {-1, -1, 1, 1, 1}, {-1,
    1, -1, -1, -1}, {-1, 1, -1, -1, 1}, {-1, 1, -1, 1, -1}, {-1, 1, -1, 1, 1},
    {-1, 1, 1, -1, -1}, {-1, 1, 1, -1, 1}, {-1, 1, 1, 1, -1}, {-1, 1, 1, 1, 1},
    {1, -1, -1, -1, -1}, {1, -1, -1, -1, 1}, {1, -1, -1, 1, -1}, {1, -1, -1, 1,
    1}, {1, -1, 1, -1, -1}, {1, -1, 1, -1, 1}, {1, -1, 1, 1, -1}, {1, -1, 1, 1,
    1}, {1, 1, -1, -1, -1}, {1, 1, -1, -1, 1}, {1, 1, -1, 1, -1}, {1, 1, -1, 1,
    1}, {1, 1, 1, -1, -1}, {1, 1, 1, -1, 1}, {1, 1, 1, 1, -1}, {1, 1, 1, 1, 1}};

// Normalization factors the various processes
// Denominators: spins, colors and identical particles
int PY8MEs_R5_P14_sm_qq_qqa::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
int PY8MEs_R5_P14_sm_qq_qqa::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R5_P14_sm_qq_qqa::denom_iden[nprocesses] = {2, 1, 2, 1, 2, 2, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R5_P14_sm_qq_qqa::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u u > u u a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #1
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[0].push_back(0); 

  // Color flows of process Process: u u~ > u u~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #1
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[1].push_back(0); 

  // Color flows of process Process: d d > d d a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: d d~ > d d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #1
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[3].push_back(0); 

  // Color flows of process Process: u~ u~ > u~ u~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: d~ d~ > d~ d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[5].push_back(0); 

  // Color flows of process Process: u d > u d a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: u u~ > d d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: u d~ > u d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #1
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[8].push_back(0); 

  // Color flows of process Process: d u~ > d u~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[9].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #1
  color_configs[9].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[9].push_back(0); 

  // Color flows of process Process: d d~ > u u~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #1
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[10].push_back(0); 

  // Color flows of process Process: u~ d~ > u~ d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: u c > u c a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: u s > u s a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: u u~ > c c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: u u~ > s s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: u c~ > u c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: u s~ > u s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[17].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[17].push_back(0); 
  // JAMP #1
  color_configs[17].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[17].push_back(0); 

  // Color flows of process Process: d s > d s a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[18].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[18].push_back(0); 
  // JAMP #1
  color_configs[18].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[18].push_back(0); 

  // Color flows of process Process: d c~ > d c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[19].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[19].push_back(0); 
  // JAMP #1
  color_configs[19].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[19].push_back(0); 

  // Color flows of process Process: d d~ > c c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[20].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[20].push_back(0); 
  // JAMP #1
  color_configs[20].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[20].push_back(0); 

  // Color flows of process Process: d d~ > s s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[21].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[21].push_back(0); 
  // JAMP #1
  color_configs[21].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[21].push_back(0); 

  // Color flows of process Process: d s~ > d s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[22].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[22].push_back(0); 
  // JAMP #1
  color_configs[22].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[22].push_back(0); 

  // Color flows of process Process: u~ c~ > u~ c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[23].push_back(0); 
  // JAMP #1
  color_configs[23].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[23].push_back(0); 

  // Color flows of process Process: u~ s~ > u~ s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[24].push_back(0); 
  // JAMP #1
  color_configs[24].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[24].push_back(0); 

  // Color flows of process Process: d~ s~ > d~ s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(1)(0)(2)(0)(0)));
  jamp_nc_relative_power[25].push_back(0); 
  // JAMP #1
  color_configs[25].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[25].push_back(0); 

  // Color flows of process Process: u s > c d a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[26].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(1)(0)(2)(0)(0)(0)));
  jamp_nc_relative_power[26].push_back(0); 

  // Color flows of process Process: u c~ > d s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[27].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[27].push_back(0); 

  // Color flows of process Process: u d~ > c s~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[28].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[28].push_back(0); 

  // Color flows of process Process: d u~ > s c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[29].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(2)(0)(0)(2)(0)(0)));
  jamp_nc_relative_power[29].push_back(0); 

  // Color flows of process Process: d s~ > u c~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[30].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(2)(0)(0)(1)(0)(0)));
  jamp_nc_relative_power[30].push_back(0); 

  // Color flows of process Process: u~ s~ > c~ d~ a WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[31].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(2)(0)(1)(0)(0)));
  jamp_nc_relative_power[31].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R5_P14_sm_qq_qqa::~PY8MEs_R5_P14_sm_qq_qqa() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R5_P14_sm_qq_qqa::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R5_P14_sm_qq_qqa::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R5_P14_sm_qq_qqa::getColorConfigs(int
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
int PY8MEs_R5_P14_sm_qq_qqa::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R5_P14_sm_qq_qqa::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
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
int PY8MEs_R5_P14_sm_qq_qqa::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R5_P14_sm_qq_qqa': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R5_P14_sm_qq_qqa::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R5_P14_sm_qq_qqa': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
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
int PY8MEs_R5_P14_sm_qq_qqa::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R5_P14_sm_qq_qqa': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
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
      " 'PY8MEs_R5_P14_sm_qq_qqa': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R5_P14_sm_qq_qqa::getAllResults(int
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
double PY8MEs_R5_P14_sm_qq_qqa::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
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
    " 'PY8MEs_R5_P14_sm_qq_qqa': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R5_P14_sm_qq_qqa::static_getPY8ME(vector<int>
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
  const int out_pdgs[nprocs][nexternal - ninitial] = {{2, 2, 22}, {4, 4, 22},
      {2, -2, 22}, {4, -4, 22}, {1, 1, 22}, {3, 3, 22}, {1, -1, 22}, {3, -3,
      22}, {-2, -2, 22}, {-4, -4, 22}, {-1, -1, 22}, {-3, -3, 22}, {2, 1, 22},
      {4, 3, 22}, {1, -1, 22}, {3, -3, 22}, {2, -1, 22}, {4, -3, 22}, {1, -2,
      22}, {3, -4, 22}, {2, -2, 22}, {4, -4, 22}, {-2, -1, 22}, {-4, -3, 22},
      {2, 4, 22}, {2, 3, 22}, {4, 1, 22}, {4, -4, 22}, {2, -2, 22}, {3, -3,
      22}, {1, -1, 22}, {2, -4, 22}, {4, -2, 22}, {2, -3, 22}, {4, -1, 22}, {1,
      3, 22}, {1, -4, 22}, {3, -2, 22}, {4, -4, 22}, {2, -2, 22}, {3, -3, 22},
      {1, -1, 22}, {1, -3, 22}, {3, -1, 22}, {-2, -4, 22}, {-2, -3, 22}, {-4,
      -1, 22}, {-1, -3, 22}, {4, 1, 22}, {2, 3, 22}, {1, -3, 22}, {3, -1, 22},
      {4, -3, 22}, {2, -1, 22}, {3, -4, 22}, {1, -2, 22}, {2, -4, 22}, {4, -2,
      22}, {-4, -1, 22}, {-2, -3, 22}, {2, -2, 22}, {4, -4, 22}, {1, -1, 22},
      {3, -3, 22}, {2, 1, 22}, {4, 3, 22}, {1, -1, 22}, {3, -3, 22}, {2, -1,
      22}, {4, -3, 22}, {1, -2, 22}, {3, -4, 22}, {2, -2, 22}, {4, -4, 22},
      {-2, -1, 22}, {-4, -3, 22}, {2, 4, 22}, {2, 3, 22}, {4, 1, 22}, {4, -4,
      22}, {2, -2, 22}, {3, -3, 22}, {1, -1, 22}, {2, -4, 22}, {4, -2, 22}, {2,
      -3, 22}, {4, -1, 22}, {1, 3, 22}, {1, -4, 22}, {3, -2, 22}, {4, -4, 22},
      {2, -2, 22}, {3, -3, 22}, {1, -1, 22}, {1, -3, 22}, {3, -1, 22}, {-2, -4,
      22}, {-2, -3, 22}, {-4, -1, 22}, {-1, -3, 22}, {4, 1, 22}, {2, 3, 22},
      {1, -3, 22}, {3, -1, 22}, {4, -3, 22}, {2, -1, 22}, {3, -4, 22}, {1, -2,
      22}, {2, -4, 22}, {4, -2, 22}, {-4, -1, 22}, {-2, -3, 22}};

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
void PY8MEs_R5_P14_sm_qq_qqa::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R5_P14_sm_qq_qqa': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R5_P14_sm_qq_qqa::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R5_P14_sm_qq_qqa::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R5_P14_sm_qq_qqa::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R5_P14_sm_qq_qqa::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R5_P14_sm_qq_qqa::initProc() 
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
void PY8MEs_R5_P14_sm_qq_qqa::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->ZERO; 
  mME[2] = pars->ZERO; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->ZERO; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R5_P14_sm_qq_qqa::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R5_P14_sm_qq_qqa::getMasses() 
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
void PY8MEs_R5_P14_sm_qq_qqa::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R5_P14_sm_qq_qqa': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R5_P14_sm_qq_qqa_exception; 
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

double PY8MEs_R5_P14_sm_qq_qqa::sigmaKin() 
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
      t = matrix_5_uu_uua(); 
    if (proc_ID == 1)
      t = matrix_5_uux_uuxa(); 
    if (proc_ID == 2)
      t = matrix_5_dd_dda(); 
    if (proc_ID == 3)
      t = matrix_5_ddx_ddxa(); 
    if (proc_ID == 4)
      t = matrix_5_uxux_uxuxa(); 
    if (proc_ID == 5)
      t = matrix_5_dxdx_dxdxa(); 
    if (proc_ID == 6)
      t = matrix_5_ud_uda(); 
    if (proc_ID == 7)
      t = matrix_5_uux_ddxa(); 
    if (proc_ID == 8)
      t = matrix_5_udx_udxa(); 
    if (proc_ID == 9)
      t = matrix_5_dux_duxa(); 
    if (proc_ID == 10)
      t = matrix_5_ddx_uuxa(); 
    if (proc_ID == 11)
      t = matrix_5_uxdx_uxdxa(); 
    if (proc_ID == 12)
      t = matrix_5_uc_uca(); 
    if (proc_ID == 13)
      t = matrix_5_us_usa(); 
    if (proc_ID == 14)
      t = matrix_5_uux_ccxa(); 
    if (proc_ID == 15)
      t = matrix_5_uux_ssxa(); 
    if (proc_ID == 16)
      t = matrix_5_ucx_ucxa(); 
    if (proc_ID == 17)
      t = matrix_5_usx_usxa(); 
    if (proc_ID == 18)
      t = matrix_5_ds_dsa(); 
    if (proc_ID == 19)
      t = matrix_5_dcx_dcxa(); 
    if (proc_ID == 20)
      t = matrix_5_ddx_ccxa(); 
    if (proc_ID == 21)
      t = matrix_5_ddx_ssxa(); 
    if (proc_ID == 22)
      t = matrix_5_dsx_dsxa(); 
    if (proc_ID == 23)
      t = matrix_5_uxcx_uxcxa(); 
    if (proc_ID == 24)
      t = matrix_5_uxsx_uxsxa(); 
    if (proc_ID == 25)
      t = matrix_5_dxsx_dxsxa(); 
    if (proc_ID == 26)
      t = matrix_5_us_cda(); 
    if (proc_ID == 27)
      t = matrix_5_ucx_dsxa(); 
    if (proc_ID == 28)
      t = matrix_5_udx_csxa(); 
    if (proc_ID == 29)
      t = matrix_5_dux_scxa(); 
    if (proc_ID == 30)
      t = matrix_5_dsx_ucxa(); 
    if (proc_ID == 31)
      t = matrix_5_uxsx_cxdxa(); 

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

void PY8MEs_R5_P14_sm_qq_qqa::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  vxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  FFV1P0_3(w[0], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[5]); 
  FFV1_2(w[1], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[0], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[7]); 
  FFV2_5_3(w[0], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[8]);
  FFV1_1(w[3], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[9]); 
  FFV1P0_3(w[0], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[10]); 
  FFV1P0_3(w[0], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[11]); 
  FFV2_5_3(w[0], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[12]);
  FFV1_1(w[2], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[13]); 
  FFV1_2(w[0], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[14]); 
  FFV1P0_3(w[1], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[15]); 
  FFV1P0_3(w[1], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[16]); 
  FFV2_5_3(w[1], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[17]);
  FFV1P0_3(w[1], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[18]); 
  FFV1P0_3(w[1], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[19]); 
  FFV2_5_3(w[1], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[20]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[21]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[22]); 
  FFV1P0_3(w[0], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[23]); 
  FFV1_2(w[22], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[24]); 
  FFV1P0_3(w[0], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[25]); 
  FFV2_5_3(w[0], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[26]);
  FFV1_1(w[21], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[27]); 
  FFV1P0_3(w[22], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[28]); 
  FFV1P0_3(w[22], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[29]); 
  FFV2_5_3(w[22], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[30]);
  FFV1P0_3(w[22], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[31]); 
  FFV1P0_3(w[22], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[32]); 
  FFV2_5_3(w[22], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[33]);
  FFV1P0_3(w[0], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[34]); 
  FFV1_2(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[35]); 
  FFV2_3_3(w[0], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[36]);
  FFV1_1(w[3], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[37]); 
  FFV1P0_3(w[0], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[38]); 
  FFV2_3_3(w[0], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[39]);
  FFV1_1(w[2], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[40]); 
  FFV1_2(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[41]); 
  FFV1P0_3(w[1], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[42]); 
  FFV2_3_3(w[1], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[43]);
  FFV1P0_3(w[1], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[44]); 
  FFV2_3_3(w[1], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[45]);
  FFV1P0_3(w[0], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[46]); 
  FFV1_2(w[22], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[47]); 
  FFV2_3_3(w[0], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[48]);
  FFV1_1(w[21], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[49]); 
  FFV1P0_3(w[22], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[50]); 
  FFV2_3_3(w[22], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[51]);
  FFV1P0_3(w[22], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[52]); 
  FFV2_3_3(w[22], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[53]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[54]); 
  ixxxxx(p[perm[2]], mME[2], hel[2], -1, w[55]); 
  FFV1P0_3(w[55], w[54], pars->GC_2, pars->ZERO, pars->ZERO, w[56]); 
  FFV1P0_3(w[55], w[54], pars->GC_11, pars->ZERO, pars->ZERO, w[57]); 
  FFV2_5_3(w[55], w[54], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[58]);
  FFV1P0_3(w[55], w[21], pars->GC_2, pars->ZERO, pars->ZERO, w[59]); 
  FFV1P0_3(w[55], w[21], pars->GC_11, pars->ZERO, pars->ZERO, w[60]); 
  FFV2_5_3(w[55], w[21], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[61]);
  FFV1_1(w[54], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[62]); 
  FFV1_2(w[55], w[4], pars->GC_2, pars->ZERO, pars->ZERO, w[63]); 
  FFV1P0_3(w[22], w[54], pars->GC_2, pars->ZERO, pars->ZERO, w[64]); 
  FFV1P0_3(w[22], w[54], pars->GC_11, pars->ZERO, pars->ZERO, w[65]); 
  FFV2_5_3(w[22], w[54], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[66]);
  FFV1P0_3(w[55], w[54], pars->GC_1, pars->ZERO, pars->ZERO, w[67]); 
  FFV2_3_3(w[55], w[54], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[68]);
  FFV1P0_3(w[55], w[21], pars->GC_1, pars->ZERO, pars->ZERO, w[69]); 
  FFV2_3_3(w[55], w[21], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[70]);
  FFV1_1(w[54], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[71]); 
  FFV1_2(w[55], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[72]); 
  FFV1P0_3(w[22], w[54], pars->GC_1, pars->ZERO, pars->ZERO, w[73]); 
  FFV2_3_3(w[22], w[54], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[74]);
  FFV2_3(w[0], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[75]); 
  FFV2_3(w[1], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[76]); 
  FFV2_3(w[0], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[77]); 
  FFV2_3(w[22], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[78]); 
  FFV2_3(w[0], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[79]); 
  FFV2_3(w[22], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[80]); 
  FFV2_3(w[55], w[21], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[81]); 
  FFV2_3(w[22], w[54], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[82]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[6], w[3], w[5], pars->GC_2, amp[0]); 
  FFV1_0(w[6], w[3], w[7], pars->GC_11, amp[1]); 
  FFV2_5_0(w[6], w[3], w[8], pars->GC_51, pars->GC_58, amp[2]); 
  FFV1_0(w[1], w[9], w[5], pars->GC_2, amp[3]); 
  FFV1_0(w[1], w[9], w[7], pars->GC_11, amp[4]); 
  FFV2_5_0(w[1], w[9], w[8], pars->GC_51, pars->GC_58, amp[5]); 
  FFV1_0(w[6], w[2], w[10], pars->GC_2, amp[6]); 
  FFV1_0(w[6], w[2], w[11], pars->GC_11, amp[7]); 
  FFV2_5_0(w[6], w[2], w[12], pars->GC_51, pars->GC_58, amp[8]); 
  FFV1_0(w[1], w[13], w[10], pars->GC_2, amp[9]); 
  FFV1_0(w[1], w[13], w[11], pars->GC_11, amp[10]); 
  FFV2_5_0(w[1], w[13], w[12], pars->GC_51, pars->GC_58, amp[11]); 
  FFV1_0(w[14], w[3], w[15], pars->GC_2, amp[12]); 
  FFV1_0(w[14], w[3], w[16], pars->GC_11, amp[13]); 
  FFV2_5_0(w[14], w[3], w[17], pars->GC_51, pars->GC_58, amp[14]); 
  FFV1_0(w[14], w[2], w[18], pars->GC_2, amp[15]); 
  FFV1_0(w[14], w[2], w[19], pars->GC_11, amp[16]); 
  FFV2_5_0(w[14], w[2], w[20], pars->GC_51, pars->GC_58, amp[17]); 
  FFV1_0(w[0], w[9], w[15], pars->GC_2, amp[18]); 
  FFV1_0(w[0], w[9], w[16], pars->GC_11, amp[19]); 
  FFV2_5_0(w[0], w[9], w[17], pars->GC_51, pars->GC_58, amp[20]); 
  FFV1_0(w[0], w[13], w[18], pars->GC_2, amp[21]); 
  FFV1_0(w[0], w[13], w[19], pars->GC_11, amp[22]); 
  FFV2_5_0(w[0], w[13], w[20], pars->GC_51, pars->GC_58, amp[23]); 
  FFV1_0(w[24], w[2], w[23], pars->GC_2, amp[24]); 
  FFV1_0(w[24], w[2], w[25], pars->GC_11, amp[25]); 
  FFV2_5_0(w[24], w[2], w[26], pars->GC_51, pars->GC_58, amp[26]); 
  FFV1_0(w[22], w[13], w[23], pars->GC_2, amp[27]); 
  FFV1_0(w[22], w[13], w[25], pars->GC_11, amp[28]); 
  FFV2_5_0(w[22], w[13], w[26], pars->GC_51, pars->GC_58, amp[29]); 
  FFV1_0(w[24], w[21], w[5], pars->GC_2, amp[30]); 
  FFV1_0(w[24], w[21], w[7], pars->GC_11, amp[31]); 
  FFV2_5_0(w[24], w[21], w[8], pars->GC_51, pars->GC_58, amp[32]); 
  FFV1_0(w[22], w[27], w[5], pars->GC_2, amp[33]); 
  FFV1_0(w[22], w[27], w[7], pars->GC_11, amp[34]); 
  FFV2_5_0(w[22], w[27], w[8], pars->GC_51, pars->GC_58, amp[35]); 
  FFV1_0(w[14], w[2], w[28], pars->GC_2, amp[36]); 
  FFV1_0(w[14], w[2], w[29], pars->GC_11, amp[37]); 
  FFV2_5_0(w[14], w[2], w[30], pars->GC_51, pars->GC_58, amp[38]); 
  FFV1_0(w[14], w[21], w[31], pars->GC_2, amp[39]); 
  FFV1_0(w[14], w[21], w[32], pars->GC_11, amp[40]); 
  FFV2_5_0(w[14], w[21], w[33], pars->GC_51, pars->GC_58, amp[41]); 
  FFV1_0(w[0], w[13], w[28], pars->GC_2, amp[42]); 
  FFV1_0(w[0], w[13], w[29], pars->GC_11, amp[43]); 
  FFV2_5_0(w[0], w[13], w[30], pars->GC_51, pars->GC_58, amp[44]); 
  FFV1_0(w[0], w[27], w[31], pars->GC_2, amp[45]); 
  FFV1_0(w[0], w[27], w[32], pars->GC_11, amp[46]); 
  FFV2_5_0(w[0], w[27], w[33], pars->GC_51, pars->GC_58, amp[47]); 
  FFV1_0(w[35], w[3], w[34], pars->GC_1, amp[48]); 
  FFV1_0(w[35], w[3], w[7], pars->GC_11, amp[49]); 
  FFV2_3_0(w[35], w[3], w[36], pars->GC_50, pars->GC_58, amp[50]); 
  FFV1_0(w[1], w[37], w[34], pars->GC_1, amp[51]); 
  FFV1_0(w[1], w[37], w[7], pars->GC_11, amp[52]); 
  FFV2_3_0(w[1], w[37], w[36], pars->GC_50, pars->GC_58, amp[53]); 
  FFV1_0(w[35], w[2], w[38], pars->GC_1, amp[54]); 
  FFV1_0(w[35], w[2], w[11], pars->GC_11, amp[55]); 
  FFV2_3_0(w[35], w[2], w[39], pars->GC_50, pars->GC_58, amp[56]); 
  FFV1_0(w[1], w[40], w[38], pars->GC_1, amp[57]); 
  FFV1_0(w[1], w[40], w[11], pars->GC_11, amp[58]); 
  FFV2_3_0(w[1], w[40], w[39], pars->GC_50, pars->GC_58, amp[59]); 
  FFV1_0(w[41], w[3], w[42], pars->GC_1, amp[60]); 
  FFV1_0(w[41], w[3], w[16], pars->GC_11, amp[61]); 
  FFV2_3_0(w[41], w[3], w[43], pars->GC_50, pars->GC_58, amp[62]); 
  FFV1_0(w[41], w[2], w[44], pars->GC_1, amp[63]); 
  FFV1_0(w[41], w[2], w[19], pars->GC_11, amp[64]); 
  FFV2_3_0(w[41], w[2], w[45], pars->GC_50, pars->GC_58, amp[65]); 
  FFV1_0(w[0], w[37], w[42], pars->GC_1, amp[66]); 
  FFV1_0(w[0], w[37], w[16], pars->GC_11, amp[67]); 
  FFV2_3_0(w[0], w[37], w[43], pars->GC_50, pars->GC_58, amp[68]); 
  FFV1_0(w[0], w[40], w[44], pars->GC_1, amp[69]); 
  FFV1_0(w[0], w[40], w[19], pars->GC_11, amp[70]); 
  FFV2_3_0(w[0], w[40], w[45], pars->GC_50, pars->GC_58, amp[71]); 
  FFV1_0(w[47], w[2], w[46], pars->GC_1, amp[72]); 
  FFV1_0(w[47], w[2], w[25], pars->GC_11, amp[73]); 
  FFV2_3_0(w[47], w[2], w[48], pars->GC_50, pars->GC_58, amp[74]); 
  FFV1_0(w[22], w[40], w[46], pars->GC_1, amp[75]); 
  FFV1_0(w[22], w[40], w[25], pars->GC_11, amp[76]); 
  FFV2_3_0(w[22], w[40], w[48], pars->GC_50, pars->GC_58, amp[77]); 
  FFV1_0(w[47], w[21], w[34], pars->GC_1, amp[78]); 
  FFV1_0(w[47], w[21], w[7], pars->GC_11, amp[79]); 
  FFV2_3_0(w[47], w[21], w[36], pars->GC_50, pars->GC_58, amp[80]); 
  FFV1_0(w[22], w[49], w[34], pars->GC_1, amp[81]); 
  FFV1_0(w[22], w[49], w[7], pars->GC_11, amp[82]); 
  FFV2_3_0(w[22], w[49], w[36], pars->GC_50, pars->GC_58, amp[83]); 
  FFV1_0(w[41], w[2], w[50], pars->GC_1, amp[84]); 
  FFV1_0(w[41], w[2], w[29], pars->GC_11, amp[85]); 
  FFV2_3_0(w[41], w[2], w[51], pars->GC_50, pars->GC_58, amp[86]); 
  FFV1_0(w[41], w[21], w[52], pars->GC_1, amp[87]); 
  FFV1_0(w[41], w[21], w[32], pars->GC_11, amp[88]); 
  FFV2_3_0(w[41], w[21], w[53], pars->GC_50, pars->GC_58, amp[89]); 
  FFV1_0(w[0], w[40], w[50], pars->GC_1, amp[90]); 
  FFV1_0(w[0], w[40], w[29], pars->GC_11, amp[91]); 
  FFV2_3_0(w[0], w[40], w[51], pars->GC_50, pars->GC_58, amp[92]); 
  FFV1_0(w[0], w[49], w[52], pars->GC_1, amp[93]); 
  FFV1_0(w[0], w[49], w[32], pars->GC_11, amp[94]); 
  FFV2_3_0(w[0], w[49], w[53], pars->GC_50, pars->GC_58, amp[95]); 
  FFV1_0(w[24], w[21], w[56], pars->GC_2, amp[96]); 
  FFV1_0(w[24], w[21], w[57], pars->GC_11, amp[97]); 
  FFV2_5_0(w[24], w[21], w[58], pars->GC_51, pars->GC_58, amp[98]); 
  FFV1_0(w[22], w[27], w[56], pars->GC_2, amp[99]); 
  FFV1_0(w[22], w[27], w[57], pars->GC_11, amp[100]); 
  FFV2_5_0(w[22], w[27], w[58], pars->GC_51, pars->GC_58, amp[101]); 
  FFV1_0(w[24], w[54], w[59], pars->GC_2, amp[102]); 
  FFV1_0(w[24], w[54], w[60], pars->GC_11, amp[103]); 
  FFV2_5_0(w[24], w[54], w[61], pars->GC_51, pars->GC_58, amp[104]); 
  FFV1_0(w[22], w[62], w[59], pars->GC_2, amp[105]); 
  FFV1_0(w[22], w[62], w[60], pars->GC_11, amp[106]); 
  FFV2_5_0(w[22], w[62], w[61], pars->GC_51, pars->GC_58, amp[107]); 
  FFV1_0(w[63], w[21], w[64], pars->GC_2, amp[108]); 
  FFV1_0(w[63], w[21], w[65], pars->GC_11, amp[109]); 
  FFV2_5_0(w[63], w[21], w[66], pars->GC_51, pars->GC_58, amp[110]); 
  FFV1_0(w[63], w[54], w[28], pars->GC_2, amp[111]); 
  FFV1_0(w[63], w[54], w[29], pars->GC_11, amp[112]); 
  FFV2_5_0(w[63], w[54], w[30], pars->GC_51, pars->GC_58, amp[113]); 
  FFV1_0(w[55], w[27], w[64], pars->GC_2, amp[114]); 
  FFV1_0(w[55], w[27], w[65], pars->GC_11, amp[115]); 
  FFV2_5_0(w[55], w[27], w[66], pars->GC_51, pars->GC_58, amp[116]); 
  FFV1_0(w[55], w[62], w[28], pars->GC_2, amp[117]); 
  FFV1_0(w[55], w[62], w[29], pars->GC_11, amp[118]); 
  FFV2_5_0(w[55], w[62], w[30], pars->GC_51, pars->GC_58, amp[119]); 
  FFV1_0(w[47], w[21], w[67], pars->GC_1, amp[120]); 
  FFV1_0(w[47], w[21], w[57], pars->GC_11, amp[121]); 
  FFV2_3_0(w[47], w[21], w[68], pars->GC_50, pars->GC_58, amp[122]); 
  FFV1_0(w[22], w[49], w[67], pars->GC_1, amp[123]); 
  FFV1_0(w[22], w[49], w[57], pars->GC_11, amp[124]); 
  FFV2_3_0(w[22], w[49], w[68], pars->GC_50, pars->GC_58, amp[125]); 
  FFV1_0(w[47], w[54], w[69], pars->GC_1, amp[126]); 
  FFV1_0(w[47], w[54], w[60], pars->GC_11, amp[127]); 
  FFV2_3_0(w[47], w[54], w[70], pars->GC_50, pars->GC_58, amp[128]); 
  FFV1_0(w[22], w[71], w[69], pars->GC_1, amp[129]); 
  FFV1_0(w[22], w[71], w[60], pars->GC_11, amp[130]); 
  FFV2_3_0(w[22], w[71], w[70], pars->GC_50, pars->GC_58, amp[131]); 
  FFV1_0(w[72], w[21], w[73], pars->GC_1, amp[132]); 
  FFV1_0(w[72], w[21], w[65], pars->GC_11, amp[133]); 
  FFV2_3_0(w[72], w[21], w[74], pars->GC_50, pars->GC_58, amp[134]); 
  FFV1_0(w[72], w[54], w[50], pars->GC_1, amp[135]); 
  FFV1_0(w[72], w[54], w[29], pars->GC_11, amp[136]); 
  FFV2_3_0(w[72], w[54], w[51], pars->GC_50, pars->GC_58, amp[137]); 
  FFV1_0(w[55], w[49], w[73], pars->GC_1, amp[138]); 
  FFV1_0(w[55], w[49], w[65], pars->GC_11, amp[139]); 
  FFV2_3_0(w[55], w[49], w[74], pars->GC_50, pars->GC_58, amp[140]); 
  FFV1_0(w[55], w[71], w[50], pars->GC_1, amp[141]); 
  FFV1_0(w[55], w[71], w[29], pars->GC_11, amp[142]); 
  FFV2_3_0(w[55], w[71], w[51], pars->GC_50, pars->GC_58, amp[143]); 
  FFV1_0(w[35], w[3], w[5], pars->GC_1, amp[144]); 
  FFV1_0(w[35], w[3], w[7], pars->GC_11, amp[145]); 
  FFV2_3_0(w[35], w[3], w[8], pars->GC_50, pars->GC_58, amp[146]); 
  FFV1_0(w[1], w[37], w[5], pars->GC_1, amp[147]); 
  FFV1_0(w[1], w[37], w[7], pars->GC_11, amp[148]); 
  FFV2_3_0(w[1], w[37], w[8], pars->GC_50, pars->GC_58, amp[149]); 
  VVV1_0(w[4], w[75], w[76], pars->GC_4, amp[150]); 
  FFV2_0(w[35], w[2], w[75], pars->GC_100, amp[151]); 
  FFV2_0(w[1], w[13], w[75], pars->GC_100, amp[152]); 
  FFV2_0(w[14], w[3], w[76], pars->GC_100, amp[153]); 
  FFV1_0(w[14], w[2], w[44], pars->GC_2, amp[154]); 
  FFV1_0(w[14], w[2], w[19], pars->GC_11, amp[155]); 
  FFV2_5_0(w[14], w[2], w[45], pars->GC_51, pars->GC_58, amp[156]); 
  FFV2_0(w[0], w[37], w[76], pars->GC_100, amp[157]); 
  FFV1_0(w[0], w[13], w[44], pars->GC_2, amp[158]); 
  FFV1_0(w[0], w[13], w[19], pars->GC_11, amp[159]); 
  FFV2_5_0(w[0], w[13], w[45], pars->GC_51, pars->GC_58, amp[160]); 
  FFV1_0(w[47], w[2], w[23], pars->GC_1, amp[161]); 
  FFV1_0(w[47], w[2], w[25], pars->GC_11, amp[162]); 
  FFV2_3_0(w[47], w[2], w[26], pars->GC_50, pars->GC_58, amp[163]); 
  FFV1_0(w[22], w[40], w[23], pars->GC_1, amp[164]); 
  FFV1_0(w[22], w[40], w[25], pars->GC_11, amp[165]); 
  FFV2_3_0(w[22], w[40], w[26], pars->GC_50, pars->GC_58, amp[166]); 
  VVV1_0(w[4], w[77], w[78], pars->GC_4, amp[167]); 
  FFV2_0(w[47], w[21], w[77], pars->GC_100, amp[168]); 
  FFV2_0(w[22], w[27], w[77], pars->GC_100, amp[169]); 
  FFV2_0(w[14], w[2], w[78], pars->GC_100, amp[170]); 
  FFV1_0(w[14], w[21], w[52], pars->GC_2, amp[171]); 
  FFV1_0(w[14], w[21], w[32], pars->GC_11, amp[172]); 
  FFV2_5_0(w[14], w[21], w[53], pars->GC_51, pars->GC_58, amp[173]); 
  FFV2_0(w[0], w[40], w[78], pars->GC_100, amp[174]); 
  FFV1_0(w[0], w[27], w[52], pars->GC_2, amp[175]); 
  FFV1_0(w[0], w[27], w[32], pars->GC_11, amp[176]); 
  FFV2_5_0(w[0], w[27], w[53], pars->GC_51, pars->GC_58, amp[177]); 
  FFV1_0(w[47], w[21], w[5], pars->GC_1, amp[178]); 
  FFV1_0(w[47], w[21], w[7], pars->GC_11, amp[179]); 
  FFV2_3_0(w[47], w[21], w[8], pars->GC_50, pars->GC_58, amp[180]); 
  FFV1_0(w[22], w[49], w[5], pars->GC_1, amp[181]); 
  FFV1_0(w[22], w[49], w[7], pars->GC_11, amp[182]); 
  FFV2_3_0(w[22], w[49], w[8], pars->GC_50, pars->GC_58, amp[183]); 
  VVV1_0(w[4], w[79], w[80], pars->GC_4, amp[184]); 
  FFV2_0(w[47], w[2], w[79], pars->GC_100, amp[185]); 
  FFV2_0(w[22], w[13], w[79], pars->GC_100, amp[186]); 
  FFV2_0(w[14], w[21], w[80], pars->GC_100, amp[187]); 
  FFV1_0(w[14], w[2], w[50], pars->GC_2, amp[188]); 
  FFV1_0(w[14], w[2], w[29], pars->GC_11, amp[189]); 
  FFV2_5_0(w[14], w[2], w[51], pars->GC_51, pars->GC_58, amp[190]); 
  FFV2_0(w[0], w[49], w[80], pars->GC_100, amp[191]); 
  FFV1_0(w[0], w[13], w[50], pars->GC_2, amp[192]); 
  FFV1_0(w[0], w[13], w[29], pars->GC_11, amp[193]); 
  FFV2_5_0(w[0], w[13], w[51], pars->GC_51, pars->GC_58, amp[194]); 
  FFV1_0(w[41], w[2], w[28], pars->GC_1, amp[195]); 
  FFV1_0(w[41], w[2], w[29], pars->GC_11, amp[196]); 
  FFV2_3_0(w[41], w[2], w[30], pars->GC_50, pars->GC_58, amp[197]); 
  FFV1_0(w[0], w[40], w[28], pars->GC_1, amp[198]); 
  FFV1_0(w[0], w[40], w[29], pars->GC_11, amp[199]); 
  FFV2_3_0(w[0], w[40], w[30], pars->GC_50, pars->GC_58, amp[200]); 
  VVV1_0(w[4], w[80], w[79], pars->GC_4, amp[201]); 
  FFV2_0(w[41], w[21], w[80], pars->GC_100, amp[202]); 
  FFV2_0(w[0], w[27], w[80], pars->GC_100, amp[203]); 
  FFV2_0(w[24], w[2], w[79], pars->GC_100, amp[204]); 
  FFV1_0(w[24], w[21], w[34], pars->GC_2, amp[205]); 
  FFV1_0(w[24], w[21], w[7], pars->GC_11, amp[206]); 
  FFV2_5_0(w[24], w[21], w[36], pars->GC_51, pars->GC_58, amp[207]); 
  FFV2_0(w[22], w[40], w[79], pars->GC_100, amp[208]); 
  FFV1_0(w[22], w[27], w[34], pars->GC_2, amp[209]); 
  FFV1_0(w[22], w[27], w[7], pars->GC_11, amp[210]); 
  FFV2_5_0(w[22], w[27], w[36], pars->GC_51, pars->GC_58, amp[211]); 
  FFV1_0(w[41], w[21], w[31], pars->GC_1, amp[212]); 
  FFV1_0(w[41], w[21], w[32], pars->GC_11, amp[213]); 
  FFV2_3_0(w[41], w[21], w[33], pars->GC_50, pars->GC_58, amp[214]); 
  FFV1_0(w[0], w[49], w[31], pars->GC_1, amp[215]); 
  FFV1_0(w[0], w[49], w[32], pars->GC_11, amp[216]); 
  FFV2_3_0(w[0], w[49], w[33], pars->GC_50, pars->GC_58, amp[217]); 
  VVV1_0(w[4], w[78], w[77], pars->GC_4, amp[218]); 
  FFV2_0(w[41], w[2], w[78], pars->GC_100, amp[219]); 
  FFV2_0(w[0], w[13], w[78], pars->GC_100, amp[220]); 
  FFV2_0(w[24], w[21], w[77], pars->GC_100, amp[221]); 
  FFV1_0(w[24], w[2], w[46], pars->GC_2, amp[222]); 
  FFV1_0(w[24], w[2], w[25], pars->GC_11, amp[223]); 
  FFV2_5_0(w[24], w[2], w[48], pars->GC_51, pars->GC_58, amp[224]); 
  FFV2_0(w[22], w[49], w[77], pars->GC_100, amp[225]); 
  FFV1_0(w[22], w[13], w[46], pars->GC_2, amp[226]); 
  FFV1_0(w[22], w[13], w[25], pars->GC_11, amp[227]); 
  FFV2_5_0(w[22], w[13], w[48], pars->GC_51, pars->GC_58, amp[228]); 
  FFV1_0(w[47], w[21], w[56], pars->GC_1, amp[229]); 
  FFV1_0(w[47], w[21], w[57], pars->GC_11, amp[230]); 
  FFV2_3_0(w[47], w[21], w[58], pars->GC_50, pars->GC_58, amp[231]); 
  FFV1_0(w[22], w[49], w[56], pars->GC_1, amp[232]); 
  FFV1_0(w[22], w[49], w[57], pars->GC_11, amp[233]); 
  FFV2_3_0(w[22], w[49], w[58], pars->GC_50, pars->GC_58, amp[234]); 
  VVV1_0(w[4], w[81], w[82], pars->GC_4, amp[235]); 
  FFV2_0(w[47], w[54], w[81], pars->GC_100, amp[236]); 
  FFV2_0(w[22], w[62], w[81], pars->GC_100, amp[237]); 
  FFV2_0(w[63], w[21], w[82], pars->GC_100, amp[238]); 
  FFV1_0(w[63], w[54], w[50], pars->GC_2, amp[239]); 
  FFV1_0(w[63], w[54], w[29], pars->GC_11, amp[240]); 
  FFV2_5_0(w[63], w[54], w[51], pars->GC_51, pars->GC_58, amp[241]); 
  FFV2_0(w[55], w[49], w[82], pars->GC_100, amp[242]); 
  FFV1_0(w[55], w[62], w[50], pars->GC_2, amp[243]); 
  FFV1_0(w[55], w[62], w[29], pars->GC_11, amp[244]); 
  FFV2_5_0(w[55], w[62], w[51], pars->GC_51, pars->GC_58, amp[245]); 
  FFV1_0(w[14], w[2], w[18], pars->GC_2, amp[246]); 
  FFV1_0(w[14], w[2], w[19], pars->GC_11, amp[247]); 
  FFV2_5_0(w[14], w[2], w[20], pars->GC_51, pars->GC_58, amp[248]); 
  FFV1_0(w[0], w[13], w[18], pars->GC_2, amp[249]); 
  FFV1_0(w[0], w[13], w[19], pars->GC_11, amp[250]); 
  FFV2_5_0(w[0], w[13], w[20], pars->GC_51, pars->GC_58, amp[251]); 
  FFV1_0(w[35], w[3], w[5], pars->GC_1, amp[252]); 
  FFV1_0(w[35], w[3], w[7], pars->GC_11, amp[253]); 
  FFV2_3_0(w[35], w[3], w[8], pars->GC_50, pars->GC_58, amp[254]); 
  FFV1_0(w[1], w[37], w[5], pars->GC_1, amp[255]); 
  FFV1_0(w[1], w[37], w[7], pars->GC_11, amp[256]); 
  FFV2_3_0(w[1], w[37], w[8], pars->GC_50, pars->GC_58, amp[257]); 
  FFV1_0(w[14], w[2], w[44], pars->GC_2, amp[258]); 
  FFV1_0(w[14], w[2], w[19], pars->GC_11, amp[259]); 
  FFV2_5_0(w[14], w[2], w[45], pars->GC_51, pars->GC_58, amp[260]); 
  FFV1_0(w[0], w[13], w[44], pars->GC_2, amp[261]); 
  FFV1_0(w[0], w[13], w[19], pars->GC_11, amp[262]); 
  FFV2_5_0(w[0], w[13], w[45], pars->GC_51, pars->GC_58, amp[263]); 
  FFV1_0(w[24], w[2], w[23], pars->GC_2, amp[264]); 
  FFV1_0(w[24], w[2], w[25], pars->GC_11, amp[265]); 
  FFV2_5_0(w[24], w[2], w[26], pars->GC_51, pars->GC_58, amp[266]); 
  FFV1_0(w[22], w[13], w[23], pars->GC_2, amp[267]); 
  FFV1_0(w[22], w[13], w[25], pars->GC_11, amp[268]); 
  FFV2_5_0(w[22], w[13], w[26], pars->GC_51, pars->GC_58, amp[269]); 
  FFV1_0(w[14], w[21], w[31], pars->GC_2, amp[270]); 
  FFV1_0(w[14], w[21], w[32], pars->GC_11, amp[271]); 
  FFV2_5_0(w[14], w[21], w[33], pars->GC_51, pars->GC_58, amp[272]); 
  FFV1_0(w[0], w[27], w[31], pars->GC_2, amp[273]); 
  FFV1_0(w[0], w[27], w[32], pars->GC_11, amp[274]); 
  FFV2_5_0(w[0], w[27], w[33], pars->GC_51, pars->GC_58, amp[275]); 
  FFV1_0(w[47], w[2], w[23], pars->GC_1, amp[276]); 
  FFV1_0(w[47], w[2], w[25], pars->GC_11, amp[277]); 
  FFV2_3_0(w[47], w[2], w[26], pars->GC_50, pars->GC_58, amp[278]); 
  FFV1_0(w[22], w[40], w[23], pars->GC_1, amp[279]); 
  FFV1_0(w[22], w[40], w[25], pars->GC_11, amp[280]); 
  FFV2_3_0(w[22], w[40], w[26], pars->GC_50, pars->GC_58, amp[281]); 
  FFV1_0(w[14], w[21], w[52], pars->GC_2, amp[282]); 
  FFV1_0(w[14], w[21], w[32], pars->GC_11, amp[283]); 
  FFV2_5_0(w[14], w[21], w[53], pars->GC_51, pars->GC_58, amp[284]); 
  FFV1_0(w[0], w[27], w[52], pars->GC_2, amp[285]); 
  FFV1_0(w[0], w[27], w[32], pars->GC_11, amp[286]); 
  FFV2_5_0(w[0], w[27], w[53], pars->GC_51, pars->GC_58, amp[287]); 
  FFV1_0(w[24], w[21], w[5], pars->GC_2, amp[288]); 
  FFV1_0(w[24], w[21], w[7], pars->GC_11, amp[289]); 
  FFV2_5_0(w[24], w[21], w[8], pars->GC_51, pars->GC_58, amp[290]); 
  FFV1_0(w[22], w[27], w[5], pars->GC_2, amp[291]); 
  FFV1_0(w[22], w[27], w[7], pars->GC_11, amp[292]); 
  FFV2_5_0(w[22], w[27], w[8], pars->GC_51, pars->GC_58, amp[293]); 
  FFV1_0(w[14], w[2], w[28], pars->GC_2, amp[294]); 
  FFV1_0(w[14], w[2], w[29], pars->GC_11, amp[295]); 
  FFV2_5_0(w[14], w[2], w[30], pars->GC_51, pars->GC_58, amp[296]); 
  FFV1_0(w[0], w[13], w[28], pars->GC_2, amp[297]); 
  FFV1_0(w[0], w[13], w[29], pars->GC_11, amp[298]); 
  FFV2_5_0(w[0], w[13], w[30], pars->GC_51, pars->GC_58, amp[299]); 
  FFV1_0(w[47], w[21], w[5], pars->GC_1, amp[300]); 
  FFV1_0(w[47], w[21], w[7], pars->GC_11, amp[301]); 
  FFV2_3_0(w[47], w[21], w[8], pars->GC_50, pars->GC_58, amp[302]); 
  FFV1_0(w[22], w[49], w[5], pars->GC_1, amp[303]); 
  FFV1_0(w[22], w[49], w[7], pars->GC_11, amp[304]); 
  FFV2_3_0(w[22], w[49], w[8], pars->GC_50, pars->GC_58, amp[305]); 
  FFV1_0(w[14], w[2], w[50], pars->GC_2, amp[306]); 
  FFV1_0(w[14], w[2], w[29], pars->GC_11, amp[307]); 
  FFV2_5_0(w[14], w[2], w[51], pars->GC_51, pars->GC_58, amp[308]); 
  FFV1_0(w[0], w[13], w[50], pars->GC_2, amp[309]); 
  FFV1_0(w[0], w[13], w[29], pars->GC_11, amp[310]); 
  FFV2_5_0(w[0], w[13], w[51], pars->GC_51, pars->GC_58, amp[311]); 
  FFV1_0(w[35], w[3], w[34], pars->GC_1, amp[312]); 
  FFV1_0(w[35], w[3], w[7], pars->GC_11, amp[313]); 
  FFV2_3_0(w[35], w[3], w[36], pars->GC_50, pars->GC_58, amp[314]); 
  FFV1_0(w[1], w[37], w[34], pars->GC_1, amp[315]); 
  FFV1_0(w[1], w[37], w[7], pars->GC_11, amp[316]); 
  FFV2_3_0(w[1], w[37], w[36], pars->GC_50, pars->GC_58, amp[317]); 
  FFV1_0(w[41], w[2], w[44], pars->GC_1, amp[318]); 
  FFV1_0(w[41], w[2], w[19], pars->GC_11, amp[319]); 
  FFV2_3_0(w[41], w[2], w[45], pars->GC_50, pars->GC_58, amp[320]); 
  FFV1_0(w[0], w[40], w[44], pars->GC_1, amp[321]); 
  FFV1_0(w[0], w[40], w[19], pars->GC_11, amp[322]); 
  FFV2_3_0(w[0], w[40], w[45], pars->GC_50, pars->GC_58, amp[323]); 
  FFV1_0(w[41], w[2], w[28], pars->GC_1, amp[324]); 
  FFV1_0(w[41], w[2], w[29], pars->GC_11, amp[325]); 
  FFV2_3_0(w[41], w[2], w[30], pars->GC_50, pars->GC_58, amp[326]); 
  FFV1_0(w[0], w[40], w[28], pars->GC_1, amp[327]); 
  FFV1_0(w[0], w[40], w[29], pars->GC_11, amp[328]); 
  FFV2_3_0(w[0], w[40], w[30], pars->GC_50, pars->GC_58, amp[329]); 
  FFV1_0(w[24], w[21], w[34], pars->GC_2, amp[330]); 
  FFV1_0(w[24], w[21], w[7], pars->GC_11, amp[331]); 
  FFV2_5_0(w[24], w[21], w[36], pars->GC_51, pars->GC_58, amp[332]); 
  FFV1_0(w[22], w[27], w[34], pars->GC_2, amp[333]); 
  FFV1_0(w[22], w[27], w[7], pars->GC_11, amp[334]); 
  FFV2_5_0(w[22], w[27], w[36], pars->GC_51, pars->GC_58, amp[335]); 
  FFV1_0(w[41], w[21], w[31], pars->GC_1, amp[336]); 
  FFV1_0(w[41], w[21], w[32], pars->GC_11, amp[337]); 
  FFV2_3_0(w[41], w[21], w[33], pars->GC_50, pars->GC_58, amp[338]); 
  FFV1_0(w[0], w[49], w[31], pars->GC_1, amp[339]); 
  FFV1_0(w[0], w[49], w[32], pars->GC_11, amp[340]); 
  FFV2_3_0(w[0], w[49], w[33], pars->GC_50, pars->GC_58, amp[341]); 
  FFV1_0(w[24], w[2], w[46], pars->GC_2, amp[342]); 
  FFV1_0(w[24], w[2], w[25], pars->GC_11, amp[343]); 
  FFV2_5_0(w[24], w[2], w[48], pars->GC_51, pars->GC_58, amp[344]); 
  FFV1_0(w[22], w[13], w[46], pars->GC_2, amp[345]); 
  FFV1_0(w[22], w[13], w[25], pars->GC_11, amp[346]); 
  FFV2_5_0(w[22], w[13], w[48], pars->GC_51, pars->GC_58, amp[347]); 
  FFV1_0(w[47], w[2], w[46], pars->GC_1, amp[348]); 
  FFV1_0(w[47], w[2], w[25], pars->GC_11, amp[349]); 
  FFV2_3_0(w[47], w[2], w[48], pars->GC_50, pars->GC_58, amp[350]); 
  FFV1_0(w[22], w[40], w[46], pars->GC_1, amp[351]); 
  FFV1_0(w[22], w[40], w[25], pars->GC_11, amp[352]); 
  FFV2_3_0(w[22], w[40], w[48], pars->GC_50, pars->GC_58, amp[353]); 
  FFV1_0(w[41], w[21], w[52], pars->GC_1, amp[354]); 
  FFV1_0(w[41], w[21], w[32], pars->GC_11, amp[355]); 
  FFV2_3_0(w[41], w[21], w[53], pars->GC_50, pars->GC_58, amp[356]); 
  FFV1_0(w[0], w[49], w[52], pars->GC_1, amp[357]); 
  FFV1_0(w[0], w[49], w[32], pars->GC_11, amp[358]); 
  FFV2_3_0(w[0], w[49], w[53], pars->GC_50, pars->GC_58, amp[359]); 
  FFV1_0(w[47], w[21], w[34], pars->GC_1, amp[360]); 
  FFV1_0(w[47], w[21], w[7], pars->GC_11, amp[361]); 
  FFV2_3_0(w[47], w[21], w[36], pars->GC_50, pars->GC_58, amp[362]); 
  FFV1_0(w[22], w[49], w[34], pars->GC_1, amp[363]); 
  FFV1_0(w[22], w[49], w[7], pars->GC_11, amp[364]); 
  FFV2_3_0(w[22], w[49], w[36], pars->GC_50, pars->GC_58, amp[365]); 
  FFV1_0(w[41], w[2], w[50], pars->GC_1, amp[366]); 
  FFV1_0(w[41], w[2], w[29], pars->GC_11, amp[367]); 
  FFV2_3_0(w[41], w[2], w[51], pars->GC_50, pars->GC_58, amp[368]); 
  FFV1_0(w[0], w[40], w[50], pars->GC_1, amp[369]); 
  FFV1_0(w[0], w[40], w[29], pars->GC_11, amp[370]); 
  FFV2_3_0(w[0], w[40], w[51], pars->GC_50, pars->GC_58, amp[371]); 
  FFV1_0(w[24], w[21], w[56], pars->GC_2, amp[372]); 
  FFV1_0(w[24], w[21], w[57], pars->GC_11, amp[373]); 
  FFV2_5_0(w[24], w[21], w[58], pars->GC_51, pars->GC_58, amp[374]); 
  FFV1_0(w[22], w[27], w[56], pars->GC_2, amp[375]); 
  FFV1_0(w[22], w[27], w[57], pars->GC_11, amp[376]); 
  FFV2_5_0(w[22], w[27], w[58], pars->GC_51, pars->GC_58, amp[377]); 
  FFV1_0(w[63], w[54], w[28], pars->GC_2, amp[378]); 
  FFV1_0(w[63], w[54], w[29], pars->GC_11, amp[379]); 
  FFV2_5_0(w[63], w[54], w[30], pars->GC_51, pars->GC_58, amp[380]); 
  FFV1_0(w[55], w[62], w[28], pars->GC_2, amp[381]); 
  FFV1_0(w[55], w[62], w[29], pars->GC_11, amp[382]); 
  FFV2_5_0(w[55], w[62], w[30], pars->GC_51, pars->GC_58, amp[383]); 
  FFV1_0(w[47], w[21], w[56], pars->GC_1, amp[384]); 
  FFV1_0(w[47], w[21], w[57], pars->GC_11, amp[385]); 
  FFV2_3_0(w[47], w[21], w[58], pars->GC_50, pars->GC_58, amp[386]); 
  FFV1_0(w[22], w[49], w[56], pars->GC_1, amp[387]); 
  FFV1_0(w[22], w[49], w[57], pars->GC_11, amp[388]); 
  FFV2_3_0(w[22], w[49], w[58], pars->GC_50, pars->GC_58, amp[389]); 
  FFV1_0(w[63], w[54], w[50], pars->GC_2, amp[390]); 
  FFV1_0(w[63], w[54], w[29], pars->GC_11, amp[391]); 
  FFV2_5_0(w[63], w[54], w[51], pars->GC_51, pars->GC_58, amp[392]); 
  FFV1_0(w[55], w[62], w[50], pars->GC_2, amp[393]); 
  FFV1_0(w[55], w[62], w[29], pars->GC_11, amp[394]); 
  FFV2_5_0(w[55], w[62], w[51], pars->GC_51, pars->GC_58, amp[395]); 
  FFV1_0(w[47], w[21], w[67], pars->GC_1, amp[396]); 
  FFV1_0(w[47], w[21], w[57], pars->GC_11, amp[397]); 
  FFV2_3_0(w[47], w[21], w[68], pars->GC_50, pars->GC_58, amp[398]); 
  FFV1_0(w[22], w[49], w[67], pars->GC_1, amp[399]); 
  FFV1_0(w[22], w[49], w[57], pars->GC_11, amp[400]); 
  FFV2_3_0(w[22], w[49], w[68], pars->GC_50, pars->GC_58, amp[401]); 
  FFV1_0(w[72], w[54], w[50], pars->GC_1, amp[402]); 
  FFV1_0(w[72], w[54], w[29], pars->GC_11, amp[403]); 
  FFV2_3_0(w[72], w[54], w[51], pars->GC_50, pars->GC_58, amp[404]); 
  FFV1_0(w[55], w[71], w[50], pars->GC_1, amp[405]); 
  FFV1_0(w[55], w[71], w[29], pars->GC_11, amp[406]); 
  FFV2_3_0(w[55], w[71], w[51], pars->GC_50, pars->GC_58, amp[407]); 
  VVV1_0(w[4], w[75], w[76], pars->GC_4, amp[408]); 
  FFV2_0(w[35], w[2], w[75], pars->GC_100, amp[409]); 
  FFV2_0(w[1], w[13], w[75], pars->GC_100, amp[410]); 
  FFV2_0(w[14], w[3], w[76], pars->GC_100, amp[411]); 
  FFV2_0(w[0], w[37], w[76], pars->GC_100, amp[412]); 
  VVV1_0(w[4], w[77], w[78], pars->GC_4, amp[413]); 
  FFV2_0(w[47], w[21], w[77], pars->GC_100, amp[414]); 
  FFV2_0(w[22], w[27], w[77], pars->GC_100, amp[415]); 
  FFV2_0(w[14], w[2], w[78], pars->GC_100, amp[416]); 
  FFV2_0(w[0], w[40], w[78], pars->GC_100, amp[417]); 
  VVV1_0(w[4], w[79], w[80], pars->GC_4, amp[418]); 
  FFV2_0(w[47], w[2], w[79], pars->GC_100, amp[419]); 
  FFV2_0(w[22], w[13], w[79], pars->GC_100, amp[420]); 
  FFV2_0(w[14], w[21], w[80], pars->GC_100, amp[421]); 
  FFV2_0(w[0], w[49], w[80], pars->GC_100, amp[422]); 
  VVV1_0(w[4], w[80], w[79], pars->GC_4, amp[423]); 
  FFV2_0(w[41], w[21], w[80], pars->GC_100, amp[424]); 
  FFV2_0(w[0], w[27], w[80], pars->GC_100, amp[425]); 
  FFV2_0(w[24], w[2], w[79], pars->GC_100, amp[426]); 
  FFV2_0(w[22], w[40], w[79], pars->GC_100, amp[427]); 
  VVV1_0(w[4], w[78], w[77], pars->GC_4, amp[428]); 
  FFV2_0(w[41], w[2], w[78], pars->GC_100, amp[429]); 
  FFV2_0(w[0], w[13], w[78], pars->GC_100, amp[430]); 
  FFV2_0(w[24], w[21], w[77], pars->GC_100, amp[431]); 
  FFV2_0(w[22], w[49], w[77], pars->GC_100, amp[432]); 
  VVV1_0(w[4], w[81], w[82], pars->GC_4, amp[433]); 
  FFV2_0(w[47], w[54], w[81], pars->GC_100, amp[434]); 
  FFV2_0(w[22], w[62], w[81], pars->GC_100, amp[435]); 
  FFV2_0(w[63], w[21], w[82], pars->GC_100, amp[436]); 
  FFV2_0(w[55], w[49], w[82], pars->GC_100, amp[437]); 


}
double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uu_uua() 
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
  jamp[0] = -amp[0] + 1./6. * amp[1] - amp[2] - amp[3] + 1./6. * amp[4] -
      amp[5] + 1./2. * amp[7] + 1./2. * amp[10] + 1./2. * amp[13] - amp[15] +
      1./6. * amp[16] - amp[17] + 1./2. * amp[19] - amp[21] + 1./6. * amp[22] -
      amp[23];
  jamp[1] = -1./2. * amp[1] - 1./2. * amp[4] + amp[6] - 1./6. * amp[7] + amp[8]
      + amp[9] - 1./6. * amp[10] + amp[11] + amp[12] - 1./6. * amp[13] +
      amp[14] - 1./2. * amp[16] + amp[18] - 1./6. * amp[19] + amp[20] - 1./2. *
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uux_uuxa() 
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
  jamp[0] = -amp[24] + 1./6. * amp[25] - amp[26] - amp[27] + 1./6. * amp[28] -
      amp[29] + 1./2. * amp[31] + 1./2. * amp[34] + 1./2. * amp[37] - amp[39] +
      1./6. * amp[40] - amp[41] + 1./2. * amp[43] - amp[45] + 1./6. * amp[46] -
      amp[47];
  jamp[1] = -1./2. * amp[25] - 1./2. * amp[28] + amp[30] - 1./6. * amp[31] +
      amp[32] + amp[33] - 1./6. * amp[34] + amp[35] + amp[36] - 1./6. * amp[37]
      + amp[38] - 1./2. * amp[40] + amp[42] - 1./6. * amp[43] + amp[44] - 1./2.
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dd_dda() 
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
  jamp[0] = -amp[48] + 1./6. * amp[49] - amp[50] - amp[51] + 1./6. * amp[52] -
      amp[53] + 1./2. * amp[55] + 1./2. * amp[58] + 1./2. * amp[61] - amp[63] +
      1./6. * amp[64] - amp[65] + 1./2. * amp[67] - amp[69] + 1./6. * amp[70] -
      amp[71];
  jamp[1] = -1./2. * amp[49] - 1./2. * amp[52] + amp[54] - 1./6. * amp[55] +
      amp[56] + amp[57] - 1./6. * amp[58] + amp[59] + amp[60] - 1./6. * amp[61]
      + amp[62] - 1./2. * amp[64] + amp[66] - 1./6. * amp[67] + amp[68] - 1./2.
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ddx_ddxa() 
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
  jamp[0] = -amp[72] + 1./6. * amp[73] - amp[74] - amp[75] + 1./6. * amp[76] -
      amp[77] + 1./2. * amp[79] + 1./2. * amp[82] + 1./2. * amp[85] - amp[87] +
      1./6. * amp[88] - amp[89] + 1./2. * amp[91] - amp[93] + 1./6. * amp[94] -
      amp[95];
  jamp[1] = -1./2. * amp[73] - 1./2. * amp[76] + amp[78] - 1./6. * amp[79] +
      amp[80] + amp[81] - 1./6. * amp[82] + amp[83] + amp[84] - 1./6. * amp[85]
      + amp[86] - 1./2. * amp[88] + amp[90] - 1./6. * amp[91] + amp[92] - 1./2.
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uxux_uxuxa() 
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
  jamp[0] = -amp[96] + 1./6. * amp[97] - amp[98] - amp[99] + 1./6. * amp[100] -
      amp[101] + 1./2. * amp[103] + 1./2. * amp[106] + 1./2. * amp[109] -
      amp[111] + 1./6. * amp[112] - amp[113] + 1./2. * amp[115] - amp[117] +
      1./6. * amp[118] - amp[119];
  jamp[1] = -1./2. * amp[97] - 1./2. * amp[100] + amp[102] - 1./6. * amp[103] +
      amp[104] + amp[105] - 1./6. * amp[106] + amp[107] + amp[108] - 1./6. *
      amp[109] + amp[110] - 1./2. * amp[112] + amp[114] - 1./6. * amp[115] +
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dxdx_dxdxa() 
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
  jamp[0] = -amp[120] + 1./6. * amp[121] - amp[122] - amp[123] + 1./6. *
      amp[124] - amp[125] + 1./2. * amp[127] + 1./2. * amp[130] + 1./2. *
      amp[133] - amp[135] + 1./6. * amp[136] - amp[137] + 1./2. * amp[139] -
      amp[141] + 1./6. * amp[142] - amp[143];
  jamp[1] = -1./2. * amp[121] - 1./2. * amp[124] + amp[126] - 1./6. * amp[127]
      + amp[128] + amp[129] - 1./6. * amp[130] + amp[131] + amp[132] - 1./6. *
      amp[133] + amp[134] - 1./2. * amp[136] + amp[138] - 1./6. * amp[139] +
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ud_uda() 
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
  jamp[0] = -amp[144] + 1./6. * amp[145] - amp[146] - amp[147] + 1./6. *
      amp[148] - amp[149] - amp[154] + 1./6. * amp[155] - amp[156] - amp[158] +
      1./6. * amp[159] - amp[160];
  jamp[1] = -1./2. * amp[145] - 1./2. * amp[148] + amp[150] + amp[151] +
      amp[152] + amp[153] - 1./2. * amp[155] + amp[157] - 1./2. * amp[159];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uux_ddxa() 
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
  jamp[0] = -amp[161] + 1./6. * amp[162] - amp[163] - amp[164] + 1./6. *
      amp[165] - amp[166] - amp[171] + 1./6. * amp[172] - amp[173] - amp[175] +
      1./6. * amp[176] - amp[177];
  jamp[1] = -1./2. * amp[162] - 1./2. * amp[165] + amp[167] + amp[168] +
      amp[169] + amp[170] - 1./2. * amp[172] + amp[174] - 1./2. * amp[176];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_udx_udxa() 
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
  jamp[0] = +1./2. * amp[179] + 1./2. * amp[182] - amp[184] - amp[185] -
      amp[186] - amp[187] + 1./2. * amp[189] - amp[191] + 1./2. * amp[193];
  jamp[1] = +amp[178] - 1./6. * amp[179] + amp[180] + amp[181] - 1./6. *
      amp[182] + amp[183] + amp[188] - 1./6. * amp[189] + amp[190] + amp[192] -
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dux_duxa() 
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
  jamp[0] = +1./2. * amp[196] + 1./2. * amp[199] - amp[201] - amp[202] -
      amp[203] - amp[204] + 1./2. * amp[206] - amp[208] + 1./2. * amp[210];
  jamp[1] = +amp[195] - 1./6. * amp[196] + amp[197] + amp[198] - 1./6. *
      amp[199] + amp[200] + amp[205] - 1./6. * amp[206] + amp[207] + amp[209] -
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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ddx_uuxa() 
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
  jamp[0] = -amp[212] + 1./6. * amp[213] - amp[214] - amp[215] + 1./6. *
      amp[216] - amp[217] - amp[222] + 1./6. * amp[223] - amp[224] - amp[226] +
      1./6. * amp[227] - amp[228];
  jamp[1] = -1./2. * amp[213] - 1./2. * amp[216] + amp[218] + amp[219] +
      amp[220] + amp[221] - 1./2. * amp[223] + amp[225] - 1./2. * amp[227];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uxdx_uxdxa() 
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
  jamp[0] = -amp[229] + 1./6. * amp[230] - amp[231] - amp[232] + 1./6. *
      amp[233] - amp[234] - amp[239] + 1./6. * amp[240] - amp[241] - amp[243] +
      1./6. * amp[244] - amp[245];
  jamp[1] = -1./2. * amp[230] - 1./2. * amp[233] + amp[235] + amp[236] +
      amp[237] + amp[238] - 1./2. * amp[240] + amp[242] - 1./2. * amp[244];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uc_uca() 
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
  jamp[0] = -amp[0] + 1./6. * amp[1] - amp[2] - amp[3] + 1./6. * amp[4] -
      amp[5] - amp[246] + 1./6. * amp[247] - amp[248] - amp[249] + 1./6. *
      amp[250] - amp[251];
  jamp[1] = +1./2. * (-amp[1] - amp[4] - amp[247] - amp[250]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_us_usa() 
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
  jamp[0] = -amp[252] + 1./6. * amp[253] - amp[254] - amp[255] + 1./6. *
      amp[256] - amp[257] - amp[258] + 1./6. * amp[259] - amp[260] - amp[261] +
      1./6. * amp[262] - amp[263];
  jamp[1] = +1./2. * (-amp[253] - amp[256] - amp[259] - amp[262]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uux_ccxa() 
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
  jamp[0] = -amp[264] + 1./6. * amp[265] - amp[266] - amp[267] + 1./6. *
      amp[268] - amp[269] - amp[270] + 1./6. * amp[271] - amp[272] - amp[273] +
      1./6. * amp[274] - amp[275];
  jamp[1] = +1./2. * (-amp[265] - amp[268] - amp[271] - amp[274]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uux_ssxa() 
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
  jamp[0] = -amp[276] + 1./6. * amp[277] - amp[278] - amp[279] + 1./6. *
      amp[280] - amp[281] - amp[282] + 1./6. * amp[283] - amp[284] - amp[285] +
      1./6. * amp[286] - amp[287];
  jamp[1] = +1./2. * (-amp[277] - amp[280] - amp[283] - amp[286]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ucx_ucxa() 
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
  jamp[0] = +1./2. * (+amp[289] + amp[292] + amp[295] + amp[298]); 
  jamp[1] = +amp[288] - 1./6. * amp[289] + amp[290] + amp[291] - 1./6. *
      amp[292] + amp[293] + amp[294] - 1./6. * amp[295] + amp[296] + amp[297] -
      1./6. * amp[298] + amp[299];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_usx_usxa() 
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
  jamp[0] = +1./2. * (+amp[301] + amp[304] + amp[307] + amp[310]); 
  jamp[1] = +amp[300] - 1./6. * amp[301] + amp[302] + amp[303] - 1./6. *
      amp[304] + amp[305] + amp[306] - 1./6. * amp[307] + amp[308] + amp[309] -
      1./6. * amp[310] + amp[311];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ds_dsa() 
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
  jamp[0] = -amp[312] + 1./6. * amp[313] - amp[314] - amp[315] + 1./6. *
      amp[316] - amp[317] - amp[318] + 1./6. * amp[319] - amp[320] - amp[321] +
      1./6. * amp[322] - amp[323];
  jamp[1] = +1./2. * (-amp[313] - amp[316] - amp[319] - amp[322]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dcx_dcxa() 
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
  jamp[0] = +1./2. * (+amp[325] + amp[328] + amp[331] + amp[334]); 
  jamp[1] = +amp[324] - 1./6. * amp[325] + amp[326] + amp[327] - 1./6. *
      amp[328] + amp[329] + amp[330] - 1./6. * amp[331] + amp[332] + amp[333] -
      1./6. * amp[334] + amp[335];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ddx_ccxa() 
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
  jamp[0] = -amp[336] + 1./6. * amp[337] - amp[338] - amp[339] + 1./6. *
      amp[340] - amp[341] - amp[342] + 1./6. * amp[343] - amp[344] - amp[345] +
      1./6. * amp[346] - amp[347];
  jamp[1] = +1./2. * (-amp[337] - amp[340] - amp[343] - amp[346]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ddx_ssxa() 
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
  jamp[0] = -amp[348] + 1./6. * amp[349] - amp[350] - amp[351] + 1./6. *
      amp[352] - amp[353] - amp[354] + 1./6. * amp[355] - amp[356] - amp[357] +
      1./6. * amp[358] - amp[359];
  jamp[1] = +1./2. * (-amp[349] - amp[352] - amp[355] - amp[358]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dsx_dsxa() 
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
  jamp[0] = +1./2. * (+amp[361] + amp[364] + amp[367] + amp[370]); 
  jamp[1] = +amp[360] - 1./6. * amp[361] + amp[362] + amp[363] - 1./6. *
      amp[364] + amp[365] + amp[366] - 1./6. * amp[367] + amp[368] + amp[369] -
      1./6. * amp[370] + amp[371];

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uxcx_uxcxa() 
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
  jamp[0] = -amp[372] + 1./6. * amp[373] - amp[374] - amp[375] + 1./6. *
      amp[376] - amp[377] - amp[378] + 1./6. * amp[379] - amp[380] - amp[381] +
      1./6. * amp[382] - amp[383];
  jamp[1] = +1./2. * (-amp[373] - amp[376] - amp[379] - amp[382]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uxsx_uxsxa() 
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
  jamp[0] = -amp[384] + 1./6. * amp[385] - amp[386] - amp[387] + 1./6. *
      amp[388] - amp[389] - amp[390] + 1./6. * amp[391] - amp[392] - amp[393] +
      1./6. * amp[394] - amp[395];
  jamp[1] = +1./2. * (-amp[385] - amp[388] - amp[391] - amp[394]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dxsx_dxsxa() 
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
  jamp[0] = -amp[396] + 1./6. * amp[397] - amp[398] - amp[399] + 1./6. *
      amp[400] - amp[401] - amp[402] + 1./6. * amp[403] - amp[404] - amp[405] +
      1./6. * amp[406] - amp[407];
  jamp[1] = +1./2. * (-amp[397] - amp[400] - amp[403] - amp[406]); 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_us_cda() 
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
  jamp[0] = +amp[408] + amp[409] + amp[410] + amp[411] + amp[412]; 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_ucx_dsxa() 
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
  jamp[0] = +amp[413] + amp[414] + amp[415] + amp[416] + amp[417]; 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_udx_csxa() 
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
  jamp[0] = -amp[418] - amp[419] - amp[420] - amp[421] - amp[422]; 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dux_scxa() 
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
  jamp[0] = -amp[423] - amp[424] - amp[425] - amp[426] - amp[427]; 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_dsx_ucxa() 
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
  jamp[0] = +amp[428] + amp[429] + amp[430] + amp[431] + amp[432]; 

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

double PY8MEs_R5_P14_sm_qq_qqa::matrix_5_uxsx_cxdxa() 
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
  jamp[0] = +amp[433] + amp[434] + amp[435] + amp[436] + amp[437]; 

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

