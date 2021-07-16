//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R5_P11_sm_gq_qqq.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: g u > u u u~ WEIGHTED<=99 @5
// Process: g c > c c c~ WEIGHTED<=99 @5
// Process: g d > d d d~ WEIGHTED<=99 @5
// Process: g s > s s s~ WEIGHTED<=99 @5
// Process: g u~ > u u~ u~ WEIGHTED<=99 @5
// Process: g c~ > c c~ c~ WEIGHTED<=99 @5
// Process: g d~ > d d~ d~ WEIGHTED<=99 @5
// Process: g s~ > s s~ s~ WEIGHTED<=99 @5
// Process: g u > u d d~ WEIGHTED<=99 @5
// Process: g c > c s s~ WEIGHTED<=99 @5
// Process: g d > u d u~ WEIGHTED<=99 @5
// Process: g s > c s c~ WEIGHTED<=99 @5
// Process: g u~ > d u~ d~ WEIGHTED<=99 @5
// Process: g c~ > s c~ s~ WEIGHTED<=99 @5
// Process: g d~ > u u~ d~ WEIGHTED<=99 @5
// Process: g s~ > c c~ s~ WEIGHTED<=99 @5
// Process: g u > u c c~ WEIGHTED<=99 @5
// Process: g c > c u u~ WEIGHTED<=99 @5
// Process: g u > u s s~ WEIGHTED<=99 @5
// Process: g c > c d d~ WEIGHTED<=99 @5
// Process: g d > c d c~ WEIGHTED<=99 @5
// Process: g s > u s u~ WEIGHTED<=99 @5
// Process: g d > d s s~ WEIGHTED<=99 @5
// Process: g s > s d d~ WEIGHTED<=99 @5
// Process: g u~ > c u~ c~ WEIGHTED<=99 @5
// Process: g c~ > u c~ u~ WEIGHTED<=99 @5
// Process: g u~ > s u~ s~ WEIGHTED<=99 @5
// Process: g c~ > d c~ d~ WEIGHTED<=99 @5
// Process: g d~ > c c~ d~ WEIGHTED<=99 @5
// Process: g s~ > u u~ s~ WEIGHTED<=99 @5
// Process: g d~ > s d~ s~ WEIGHTED<=99 @5
// Process: g s~ > d s~ d~ WEIGHTED<=99 @5
// Process: g u > c d s~ WEIGHTED<=99 @5
// Process: g c > u s d~ WEIGHTED<=99 @5
// Process: g d > u s c~ WEIGHTED<=99 @5
// Process: g s > c d u~ WEIGHTED<=99 @5
// Process: g u~ > s c~ d~ WEIGHTED<=99 @5
// Process: g c~ > d u~ s~ WEIGHTED<=99 @5
// Process: g d~ > c u~ s~ WEIGHTED<=99 @5
// Process: g s~ > u c~ d~ WEIGHTED<=99 @5

// Exception class
class PY8MEs_R5_P11_sm_gq_qqqException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R5_P11_sm_gq_qqq'."; 
  }
}
PY8MEs_R5_P11_sm_gq_qqq_exception; 

std::set<int> PY8MEs_R5_P11_sm_gq_qqq::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R5_P11_sm_gq_qqq::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R5_P11_sm_gq_qqq::denom_colors[nprocesses] = {24, 24, 24, 24, 24,
    24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24};
int PY8MEs_R5_P11_sm_gq_qqq::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R5_P11_sm_gq_qqq::denom_iden[nprocesses] = {2, 2, 2, 2, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R5_P11_sm_gq_qqq::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: g u > u u u~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #1
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #2
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #3
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[0].push_back(0); 

  // Color flows of process Process: g d > d d d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #1
  color_configs[1].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #2
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[1].push_back(0); 
  // JAMP #3
  color_configs[1].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[1].push_back(0); 

  // Color flows of process Process: g u~ > u u~ u~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #2
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #3
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: g d~ > d d~ d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #1
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #2
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #3
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[3].push_back(0); 

  // Color flows of process Process: g u > u d d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #2
  color_configs[4].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #3
  color_configs[4].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: g d > u d u~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #2
  color_configs[5].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #3
  color_configs[5].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[5].push_back(0); 

  // Color flows of process Process: g u~ > d u~ d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #2
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #3
  color_configs[6].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: g d~ > u u~ d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #2
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #3
  color_configs[7].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: g u > u c c~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #1
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #2
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #3
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[8].push_back(0); 

  // Color flows of process Process: g u > u s s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[9].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #1
  color_configs[9].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #2
  color_configs[9].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[9].push_back(0); 
  // JAMP #3
  color_configs[9].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[9].push_back(0); 

  // Color flows of process Process: g d > c d c~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #1
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #2
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #3
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[10].push_back(0); 

  // Color flows of process Process: g d > d s s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #2
  color_configs[11].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #3
  color_configs[11].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: g u~ > c u~ c~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #2
  color_configs[12].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #3
  color_configs[12].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: g u~ > s u~ s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #2
  color_configs[13].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #3
  color_configs[13].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: g d~ > c c~ d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #2
  color_configs[14].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #3
  color_configs[14].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: g d~ > s d~ s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #2
  color_configs[15].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #3
  color_configs[15].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: g u > c d s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(3)(2)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(3)(3)(0)(1)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: g d > u s c~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[17].push_back(vec_int(createvector<int>
      (1)(3)(3)(0)(1)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[17].push_back(0); 
  // JAMP #1
  color_configs[17].push_back(vec_int(createvector<int>
      (2)(3)(1)(0)(1)(0)(2)(0)(0)(3)));
  jamp_nc_relative_power[17].push_back(0); 

  // Color flows of process Process: g u~ > s c~ d~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[18].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(2)(0)(3)));
  jamp_nc_relative_power[18].push_back(0); 
  // JAMP #1
  color_configs[18].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(3)(0)(1)));
  jamp_nc_relative_power[18].push_back(0); 

  // Color flows of process Process: g d~ > c u~ s~ WEIGHTED<=99 @5
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[19].push_back(vec_int(createvector<int>
      (1)(3)(0)(1)(2)(0)(0)(3)(0)(2)));
  jamp_nc_relative_power[19].push_back(0); 
  // JAMP #1
  color_configs[19].push_back(vec_int(createvector<int>
      (2)(3)(0)(1)(2)(0)(0)(1)(0)(3)));
  jamp_nc_relative_power[19].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R5_P11_sm_gq_qqq::~PY8MEs_R5_P11_sm_gq_qqq() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R5_P11_sm_gq_qqq::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R5_P11_sm_gq_qqq::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R5_P11_sm_gq_qqq::getColorConfigs(int
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
int PY8MEs_R5_P11_sm_gq_qqq::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R5_P11_sm_gq_qqq::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
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
int PY8MEs_R5_P11_sm_gq_qqq::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R5_P11_sm_gq_qqq': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R5_P11_sm_gq_qqq::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R5_P11_sm_gq_qqq': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
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
int PY8MEs_R5_P11_sm_gq_qqq::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R5_P11_sm_gq_qqq': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
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
      " 'PY8MEs_R5_P11_sm_gq_qqq': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R5_P11_sm_gq_qqq::getAllResults(int
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
double PY8MEs_R5_P11_sm_gq_qqq::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
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
    " 'PY8MEs_R5_P11_sm_gq_qqq': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R5_P11_sm_gq_qqq::static_getPY8ME(vector<int>
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
  const int nprocs = 80; 
  const int proc_IDS[nprocs] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
      8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17,
      17, 18, 18, 19, 19, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
      9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18,
      18, 19, 19};
  const int in_pdgs[nprocs][ninitial] = {{21, 2}, {21, 4}, {21, 1}, {21, 3},
      {21, -2}, {21, -4}, {21, -1}, {21, -3}, {21, 2}, {21, 4}, {21, 1}, {21,
      3}, {21, -2}, {21, -4}, {21, -1}, {21, -3}, {21, 2}, {21, 4}, {21, 2},
      {21, 4}, {21, 1}, {21, 3}, {21, 1}, {21, 3}, {21, -2}, {21, -4}, {21,
      -2}, {21, -4}, {21, -1}, {21, -3}, {21, -1}, {21, -3}, {21, 2}, {21, 4},
      {21, 1}, {21, 3}, {21, -2}, {21, -4}, {21, -1}, {21, -3}, {2, 21}, {4,
      21}, {1, 21}, {3, 21}, {-2, 21}, {-4, 21}, {-1, 21}, {-3, 21}, {2, 21},
      {4, 21}, {1, 21}, {3, 21}, {-2, 21}, {-4, 21}, {-1, 21}, {-3, 21}, {2,
      21}, {4, 21}, {2, 21}, {4, 21}, {1, 21}, {3, 21}, {1, 21}, {3, 21}, {-2,
      21}, {-4, 21}, {-2, 21}, {-4, 21}, {-1, 21}, {-3, 21}, {-1, 21}, {-3,
      21}, {2, 21}, {4, 21}, {1, 21}, {3, 21}, {-2, 21}, {-4, 21}, {-1, 21},
      {-3, 21}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{2, 2, -2}, {4, 4, -4},
      {1, 1, -1}, {3, 3, -3}, {2, -2, -2}, {4, -4, -4}, {1, -1, -1}, {3, -3,
      -3}, {2, 1, -1}, {4, 3, -3}, {2, 1, -2}, {4, 3, -4}, {1, -2, -1}, {3, -4,
      -3}, {2, -2, -1}, {4, -4, -3}, {2, 4, -4}, {4, 2, -2}, {2, 3, -3}, {4, 1,
      -1}, {4, 1, -4}, {2, 3, -2}, {1, 3, -3}, {3, 1, -1}, {4, -2, -4}, {2, -4,
      -2}, {3, -2, -3}, {1, -4, -1}, {4, -4, -1}, {2, -2, -3}, {3, -1, -3}, {1,
      -3, -1}, {4, 1, -3}, {2, 3, -1}, {2, 3, -4}, {4, 1, -2}, {3, -4, -1}, {1,
      -2, -3}, {4, -2, -3}, {2, -4, -1}, {2, 2, -2}, {4, 4, -4}, {1, 1, -1},
      {3, 3, -3}, {2, -2, -2}, {4, -4, -4}, {1, -1, -1}, {3, -3, -3}, {2, 1,
      -1}, {4, 3, -3}, {2, 1, -2}, {4, 3, -4}, {1, -2, -1}, {3, -4, -3}, {2,
      -2, -1}, {4, -4, -3}, {2, 4, -4}, {4, 2, -2}, {2, 3, -3}, {4, 1, -1}, {4,
      1, -4}, {2, 3, -2}, {1, 3, -3}, {3, 1, -1}, {4, -2, -4}, {2, -4, -2}, {3,
      -2, -3}, {1, -4, -1}, {4, -4, -1}, {2, -2, -3}, {3, -1, -3}, {1, -3, -1},
      {4, 1, -3}, {2, 3, -1}, {2, 3, -4}, {4, 1, -2}, {3, -4, -1}, {1, -2, -3},
      {4, -2, -3}, {2, -4, -1}};

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
void PY8MEs_R5_P11_sm_gq_qqq::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R5_P11_sm_gq_qqq': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R5_P11_sm_gq_qqq::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R5_P11_sm_gq_qqq::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R5_P11_sm_gq_qqq::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R5_P11_sm_gq_qqq::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R5_P11_sm_gq_qqq::initProc() 
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
  jamp2 = vector < vec_double > (20); 
  jamp2[0] = vector<double> (4, 0.); 
  jamp2[1] = vector<double> (4, 0.); 
  jamp2[2] = vector<double> (4, 0.); 
  jamp2[3] = vector<double> (4, 0.); 
  jamp2[4] = vector<double> (4, 0.); 
  jamp2[5] = vector<double> (4, 0.); 
  jamp2[6] = vector<double> (4, 0.); 
  jamp2[7] = vector<double> (4, 0.); 
  jamp2[8] = vector<double> (4, 0.); 
  jamp2[9] = vector<double> (4, 0.); 
  jamp2[10] = vector<double> (4, 0.); 
  jamp2[11] = vector<double> (4, 0.); 
  jamp2[12] = vector<double> (4, 0.); 
  jamp2[13] = vector<double> (4, 0.); 
  jamp2[14] = vector<double> (4, 0.); 
  jamp2[15] = vector<double> (4, 0.); 
  jamp2[16] = vector<double> (2, 0.); 
  jamp2[17] = vector<double> (2, 0.); 
  jamp2[18] = vector<double> (2, 0.); 
  jamp2[19] = vector<double> (2, 0.); 
  all_results = vector < vec_vec_double > (20); 
  // The first entry is always the color or helicity avg/summed matrix element.
  all_results[0] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[1] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[2] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[3] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[4] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[5] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[6] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[7] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[8] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[9] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[10] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[11] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[12] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[13] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[14] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[15] = vector < vec_double > (ncomb + 1, vector<double> (4 + 1,
      0.));
  all_results[16] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[17] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[18] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
  all_results[19] = vector < vec_double > (ncomb + 1, vector<double> (2 + 1,
      0.));
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R5_P11_sm_gq_qqq::syncProcModelParams() 
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
void PY8MEs_R5_P11_sm_gq_qqq::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R5_P11_sm_gq_qqq::getMasses() 
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
void PY8MEs_R5_P11_sm_gq_qqq::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R5_P11_sm_gq_qqq': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R5_P11_sm_gq_qqq_exception; 
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

double PY8MEs_R5_P11_sm_gq_qqq::sigmaKin() 
{
  // Set the parameters which change event by event
  pars->setDependentParameters(); 
  pars->setDependentCouplings(); 
  // Reset color flows
  for(int i = 0; i < 4; i++ )
    jamp2[0][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[1][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[2][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[3][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[4][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[5][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[6][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[7][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[8][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[9][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[10][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[11][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[12][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[13][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[14][i] = 0.; 
  for(int i = 0; i < 4; i++ )
    jamp2[15][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[16][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[17][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[18][i] = 0.; 
  for(int i = 0; i < 2; i++ )
    jamp2[19][i] = 0.; 

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
    for(int i = 0; i < 4; i++ )
      jamp2[0][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[1][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[2][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[3][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[4][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[5][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[6][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[7][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[8][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[9][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[10][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[11][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[12][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[13][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[14][i] = 0.; 
    for(int i = 0; i < 4; i++ )
      jamp2[15][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[16][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[17][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[18][i] = 0.; 
    for(int i = 0; i < 2; i++ )
      jamp2[19][i] = 0.; 

    if (proc_ID == 0)
      t = matrix_5_gu_uuux(); 
    if (proc_ID == 1)
      t = matrix_5_gd_dddx(); 
    if (proc_ID == 2)
      t = matrix_5_gux_uuxux(); 
    if (proc_ID == 3)
      t = matrix_5_gdx_ddxdx(); 
    if (proc_ID == 4)
      t = matrix_5_gu_uddx(); 
    if (proc_ID == 5)
      t = matrix_5_gd_udux(); 
    if (proc_ID == 6)
      t = matrix_5_gux_duxdx(); 
    if (proc_ID == 7)
      t = matrix_5_gdx_uuxdx(); 
    if (proc_ID == 8)
      t = matrix_5_gu_uccx(); 
    if (proc_ID == 9)
      t = matrix_5_gu_ussx(); 
    if (proc_ID == 10)
      t = matrix_5_gd_cdcx(); 
    if (proc_ID == 11)
      t = matrix_5_gd_dssx(); 
    if (proc_ID == 12)
      t = matrix_5_gux_cuxcx(); 
    if (proc_ID == 13)
      t = matrix_5_gux_suxsx(); 
    if (proc_ID == 14)
      t = matrix_5_gdx_ccxdx(); 
    if (proc_ID == 15)
      t = matrix_5_gdx_sdxsx(); 
    if (proc_ID == 16)
      t = matrix_5_gu_cdsx(); 
    if (proc_ID == 17)
      t = matrix_5_gd_uscx(); 
    if (proc_ID == 18)
      t = matrix_5_gux_scxdx(); 
    if (proc_ID == 19)
      t = matrix_5_gdx_cuxsx(); 

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

void PY8MEs_R5_P11_sm_gq_qqq::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  vxxxxx(p[perm[0]], mME[0], hel[0], -1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[4]); 
  FFV1_2(w[1], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[5]); 
  FFV1P0_3(w[4], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[4], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[7]); 
  FFV2_5_3(w[4], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[8]);
  FFV1P0_3(w[4], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[9]); 
  FFV1P0_3(w[4], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[10]); 
  FFV2_5_3(w[4], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV1_1(w[2], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[12]); 
  FFV1P0_3(w[1], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[13]); 
  FFV1P0_3(w[1], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[14]); 
  FFV2_5_3(w[1], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[15]);
  FFV1_1(w[3], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[16]); 
  FFV1P0_3(w[1], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[17]); 
  FFV1P0_3(w[1], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[18]); 
  FFV2_5_3(w[1], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[19]);
  FFV1_2(w[4], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[20]); 
  FFV1P0_3(w[4], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[21]); 
  FFV2_3_3(w[4], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[22]);
  FFV1P0_3(w[4], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[23]); 
  FFV2_3_3(w[4], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[24]);
  FFV1P0_3(w[1], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[25]); 
  FFV2_3_3(w[1], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[26]);
  FFV1P0_3(w[1], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[27]); 
  FFV2_3_3(w[1], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[28]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[29]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[30]); 
  FFV1_2(w[30], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[31]); 
  FFV1P0_3(w[4], w[29], pars->GC_2, pars->ZERO, pars->ZERO, w[32]); 
  FFV1P0_3(w[4], w[29], pars->GC_11, pars->ZERO, pars->ZERO, w[33]); 
  FFV2_5_3(w[4], w[29], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[34]);
  FFV1_1(w[29], w[0], pars->GC_11, pars->ZERO, pars->ZERO, w[35]); 
  FFV1P0_3(w[30], w[2], pars->GC_2, pars->ZERO, pars->ZERO, w[36]); 
  FFV1P0_3(w[30], w[2], pars->GC_11, pars->ZERO, pars->ZERO, w[37]); 
  FFV2_5_3(w[30], w[2], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[38]);
  FFV1P0_3(w[30], w[29], pars->GC_2, pars->ZERO, pars->ZERO, w[39]); 
  FFV1P0_3(w[30], w[29], pars->GC_11, pars->ZERO, pars->ZERO, w[40]); 
  FFV2_5_3(w[30], w[29], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[41]);
  FFV1P0_3(w[4], w[29], pars->GC_1, pars->ZERO, pars->ZERO, w[42]); 
  FFV2_3_3(w[4], w[29], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[43]);
  FFV1P0_3(w[30], w[2], pars->GC_1, pars->ZERO, pars->ZERO, w[44]); 
  FFV2_3_3(w[30], w[2], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[45]);
  FFV1P0_3(w[30], w[29], pars->GC_1, pars->ZERO, pars->ZERO, w[46]); 
  FFV2_3_3(w[30], w[29], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[47]);
  FFV2_3(w[4], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[48]); 
  FFV2_3(w[1], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[49]); 
  FFV2_3(w[1], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[50]); 
  FFV2_3(w[4], w[3], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[51]); 
  FFV2_3(w[4], w[29], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[52]); 
  FFV2_3(w[30], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[53]); 
  FFV2_3(w[30], w[29], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[54]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[5], w[3], w[6], pars->GC_2, amp[0]); 
  FFV1_0(w[5], w[3], w[7], pars->GC_11, amp[1]); 
  FFV2_5_0(w[5], w[3], w[8], pars->GC_51, pars->GC_58, amp[2]); 
  FFV1_0(w[5], w[2], w[9], pars->GC_2, amp[3]); 
  FFV1_0(w[5], w[2], w[10], pars->GC_11, amp[4]); 
  FFV2_5_0(w[5], w[2], w[11], pars->GC_51, pars->GC_58, amp[5]); 
  FFV1_0(w[4], w[12], w[13], pars->GC_2, amp[6]); 
  FFV1_0(w[4], w[12], w[14], pars->GC_11, amp[7]); 
  FFV2_5_0(w[4], w[12], w[15], pars->GC_51, pars->GC_58, amp[8]); 
  FFV1_0(w[1], w[12], w[9], pars->GC_2, amp[9]); 
  FFV1_0(w[1], w[12], w[10], pars->GC_11, amp[10]); 
  FFV2_5_0(w[1], w[12], w[11], pars->GC_51, pars->GC_58, amp[11]); 
  FFV1_0(w[4], w[16], w[17], pars->GC_2, amp[12]); 
  FFV1_0(w[4], w[16], w[18], pars->GC_11, amp[13]); 
  FFV2_5_0(w[4], w[16], w[19], pars->GC_51, pars->GC_58, amp[14]); 
  FFV1_0(w[1], w[16], w[6], pars->GC_2, amp[15]); 
  FFV1_0(w[1], w[16], w[7], pars->GC_11, amp[16]); 
  FFV2_5_0(w[1], w[16], w[8], pars->GC_51, pars->GC_58, amp[17]); 
  FFV1_0(w[20], w[3], w[17], pars->GC_2, amp[18]); 
  FFV1_0(w[20], w[3], w[18], pars->GC_11, amp[19]); 
  FFV2_5_0(w[20], w[3], w[19], pars->GC_51, pars->GC_58, amp[20]); 
  FFV1_0(w[20], w[2], w[13], pars->GC_2, amp[21]); 
  FFV1_0(w[20], w[2], w[14], pars->GC_11, amp[22]); 
  FFV2_5_0(w[20], w[2], w[15], pars->GC_51, pars->GC_58, amp[23]); 
  VVV1_0(w[0], w[18], w[10], pars->GC_10, amp[24]); 
  VVV1_0(w[0], w[14], w[7], pars->GC_10, amp[25]); 
  FFV1_0(w[5], w[3], w[21], pars->GC_1, amp[26]); 
  FFV2_3_0(w[5], w[3], w[22], pars->GC_50, pars->GC_58, amp[27]); 
  FFV1_0(w[5], w[2], w[23], pars->GC_1, amp[28]); 
  FFV2_3_0(w[5], w[2], w[24], pars->GC_50, pars->GC_58, amp[29]); 
  FFV1_0(w[4], w[12], w[25], pars->GC_1, amp[30]); 
  FFV2_3_0(w[4], w[12], w[26], pars->GC_50, pars->GC_58, amp[31]); 
  FFV1_0(w[1], w[12], w[23], pars->GC_1, amp[32]); 
  FFV2_3_0(w[1], w[12], w[24], pars->GC_50, pars->GC_58, amp[33]); 
  FFV1_0(w[4], w[16], w[27], pars->GC_1, amp[34]); 
  FFV2_3_0(w[4], w[16], w[28], pars->GC_50, pars->GC_58, amp[35]); 
  FFV1_0(w[1], w[16], w[21], pars->GC_1, amp[36]); 
  FFV2_3_0(w[1], w[16], w[22], pars->GC_50, pars->GC_58, amp[37]); 
  FFV1_0(w[20], w[3], w[27], pars->GC_1, amp[38]); 
  FFV2_3_0(w[20], w[3], w[28], pars->GC_50, pars->GC_58, amp[39]); 
  FFV1_0(w[20], w[2], w[25], pars->GC_1, amp[40]); 
  FFV2_3_0(w[20], w[2], w[26], pars->GC_50, pars->GC_58, amp[41]); 
  FFV1_0(w[31], w[2], w[32], pars->GC_2, amp[42]); 
  FFV1_0(w[31], w[2], w[33], pars->GC_11, amp[43]); 
  FFV2_5_0(w[31], w[2], w[34], pars->GC_51, pars->GC_58, amp[44]); 
  FFV1_0(w[31], w[29], w[6], pars->GC_2, amp[45]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[46]); 
  FFV2_5_0(w[31], w[29], w[8], pars->GC_51, pars->GC_58, amp[47]); 
  FFV1_0(w[4], w[35], w[36], pars->GC_2, amp[48]); 
  FFV1_0(w[4], w[35], w[37], pars->GC_11, amp[49]); 
  FFV2_5_0(w[4], w[35], w[38], pars->GC_51, pars->GC_58, amp[50]); 
  FFV1_0(w[30], w[35], w[6], pars->GC_2, amp[51]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[52]); 
  FFV2_5_0(w[30], w[35], w[8], pars->GC_51, pars->GC_58, amp[53]); 
  FFV1_0(w[4], w[12], w[39], pars->GC_2, amp[54]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[55]); 
  FFV2_5_0(w[4], w[12], w[41], pars->GC_51, pars->GC_58, amp[56]); 
  FFV1_0(w[30], w[12], w[32], pars->GC_2, amp[57]); 
  FFV1_0(w[30], w[12], w[33], pars->GC_11, amp[58]); 
  FFV2_5_0(w[30], w[12], w[34], pars->GC_51, pars->GC_58, amp[59]); 
  FFV1_0(w[20], w[2], w[39], pars->GC_2, amp[60]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[61]); 
  FFV2_5_0(w[20], w[2], w[41], pars->GC_51, pars->GC_58, amp[62]); 
  FFV1_0(w[20], w[29], w[36], pars->GC_2, amp[63]); 
  FFV1_0(w[20], w[29], w[37], pars->GC_11, amp[64]); 
  FFV2_5_0(w[20], w[29], w[38], pars->GC_51, pars->GC_58, amp[65]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[66]); 
  VVV1_0(w[0], w[37], w[33], pars->GC_10, amp[67]); 
  FFV1_0(w[31], w[2], w[42], pars->GC_1, amp[68]); 
  FFV1_0(w[31], w[2], w[33], pars->GC_11, amp[69]); 
  FFV2_3_0(w[31], w[2], w[43], pars->GC_50, pars->GC_58, amp[70]); 
  FFV1_0(w[31], w[29], w[21], pars->GC_1, amp[71]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[72]); 
  FFV2_3_0(w[31], w[29], w[22], pars->GC_50, pars->GC_58, amp[73]); 
  FFV1_0(w[4], w[35], w[44], pars->GC_1, amp[74]); 
  FFV1_0(w[4], w[35], w[37], pars->GC_11, amp[75]); 
  FFV2_3_0(w[4], w[35], w[45], pars->GC_50, pars->GC_58, amp[76]); 
  FFV1_0(w[30], w[35], w[21], pars->GC_1, amp[77]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[78]); 
  FFV2_3_0(w[30], w[35], w[22], pars->GC_50, pars->GC_58, amp[79]); 
  FFV1_0(w[4], w[12], w[46], pars->GC_1, amp[80]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[81]); 
  FFV2_3_0(w[4], w[12], w[47], pars->GC_50, pars->GC_58, amp[82]); 
  FFV1_0(w[30], w[12], w[42], pars->GC_1, amp[83]); 
  FFV1_0(w[30], w[12], w[33], pars->GC_11, amp[84]); 
  FFV2_3_0(w[30], w[12], w[43], pars->GC_50, pars->GC_58, amp[85]); 
  FFV1_0(w[20], w[2], w[46], pars->GC_1, amp[86]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[87]); 
  FFV2_3_0(w[20], w[2], w[47], pars->GC_50, pars->GC_58, amp[88]); 
  FFV1_0(w[20], w[29], w[44], pars->GC_1, amp[89]); 
  FFV1_0(w[20], w[29], w[37], pars->GC_11, amp[90]); 
  FFV2_3_0(w[20], w[29], w[45], pars->GC_50, pars->GC_58, amp[91]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[92]); 
  VVV1_0(w[0], w[37], w[33], pars->GC_10, amp[93]); 
  FFV2_0(w[5], w[3], w[48], pars->GC_100, amp[94]); 
  FFV1_0(w[5], w[2], w[23], pars->GC_2, amp[95]); 
  FFV1_0(w[5], w[2], w[10], pars->GC_11, amp[96]); 
  FFV2_5_0(w[5], w[2], w[24], pars->GC_51, pars->GC_58, amp[97]); 
  FFV2_0(w[4], w[12], w[49], pars->GC_100, amp[98]); 
  FFV1_0(w[1], w[12], w[23], pars->GC_2, amp[99]); 
  FFV1_0(w[1], w[12], w[10], pars->GC_11, amp[100]); 
  FFV2_5_0(w[1], w[12], w[24], pars->GC_51, pars->GC_58, amp[101]); 
  FFV1_0(w[4], w[16], w[17], pars->GC_1, amp[102]); 
  FFV1_0(w[4], w[16], w[18], pars->GC_11, amp[103]); 
  FFV2_3_0(w[4], w[16], w[19], pars->GC_50, pars->GC_58, amp[104]); 
  FFV2_0(w[1], w[16], w[48], pars->GC_100, amp[105]); 
  FFV1_0(w[20], w[3], w[17], pars->GC_1, amp[106]); 
  FFV1_0(w[20], w[3], w[18], pars->GC_11, amp[107]); 
  FFV2_3_0(w[20], w[3], w[19], pars->GC_50, pars->GC_58, amp[108]); 
  FFV2_0(w[20], w[2], w[49], pars->GC_100, amp[109]); 
  VVV1_0(w[0], w[18], w[10], pars->GC_10, amp[110]); 
  FFV2_0(w[20], w[3], w[50], pars->GC_100, amp[111]); 
  FFV1_0(w[20], w[2], w[25], pars->GC_2, amp[112]); 
  FFV1_0(w[20], w[2], w[14], pars->GC_11, amp[113]); 
  FFV2_5_0(w[20], w[2], w[26], pars->GC_51, pars->GC_58, amp[114]); 
  FFV2_0(w[1], w[12], w[51], pars->GC_100, amp[115]); 
  FFV1_0(w[4], w[12], w[25], pars->GC_2, amp[116]); 
  FFV1_0(w[4], w[12], w[14], pars->GC_11, amp[117]); 
  FFV2_5_0(w[4], w[12], w[26], pars->GC_51, pars->GC_58, amp[118]); 
  FFV1_0(w[1], w[16], w[6], pars->GC_1, amp[119]); 
  FFV1_0(w[1], w[16], w[7], pars->GC_11, amp[120]); 
  FFV2_3_0(w[1], w[16], w[8], pars->GC_50, pars->GC_58, amp[121]); 
  FFV2_0(w[4], w[16], w[50], pars->GC_100, amp[122]); 
  FFV1_0(w[5], w[3], w[6], pars->GC_1, amp[123]); 
  FFV1_0(w[5], w[3], w[7], pars->GC_11, amp[124]); 
  FFV2_3_0(w[5], w[3], w[8], pars->GC_50, pars->GC_58, amp[125]); 
  FFV2_0(w[5], w[2], w[51], pars->GC_100, amp[126]); 
  VVV1_0(w[0], w[7], w[14], pars->GC_10, amp[127]); 
  FFV2_0(w[31], w[2], w[52], pars->GC_100, amp[128]); 
  FFV1_0(w[31], w[29], w[21], pars->GC_2, amp[129]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[130]); 
  FFV2_5_0(w[31], w[29], w[22], pars->GC_51, pars->GC_58, amp[131]); 
  FFV2_0(w[4], w[35], w[53], pars->GC_100, amp[132]); 
  FFV1_0(w[30], w[35], w[21], pars->GC_2, amp[133]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[134]); 
  FFV2_5_0(w[30], w[35], w[22], pars->GC_51, pars->GC_58, amp[135]); 
  FFV1_0(w[4], w[12], w[39], pars->GC_1, amp[136]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[137]); 
  FFV2_3_0(w[4], w[12], w[41], pars->GC_50, pars->GC_58, amp[138]); 
  FFV2_0(w[30], w[12], w[52], pars->GC_100, amp[139]); 
  FFV1_0(w[20], w[2], w[39], pars->GC_1, amp[140]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[141]); 
  FFV2_3_0(w[20], w[2], w[41], pars->GC_50, pars->GC_58, amp[142]); 
  FFV2_0(w[20], w[29], w[53], pars->GC_100, amp[143]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[144]); 
  FFV2_0(w[31], w[29], w[48], pars->GC_100, amp[145]); 
  FFV1_0(w[31], w[2], w[42], pars->GC_2, amp[146]); 
  FFV1_0(w[31], w[2], w[33], pars->GC_11, amp[147]); 
  FFV2_5_0(w[31], w[2], w[43], pars->GC_51, pars->GC_58, amp[148]); 
  FFV2_0(w[4], w[12], w[54], pars->GC_100, amp[149]); 
  FFV1_0(w[30], w[12], w[42], pars->GC_2, amp[150]); 
  FFV1_0(w[30], w[12], w[33], pars->GC_11, amp[151]); 
  FFV2_5_0(w[30], w[12], w[43], pars->GC_51, pars->GC_58, amp[152]); 
  FFV1_0(w[4], w[35], w[36], pars->GC_1, amp[153]); 
  FFV1_0(w[4], w[35], w[37], pars->GC_11, amp[154]); 
  FFV2_3_0(w[4], w[35], w[38], pars->GC_50, pars->GC_58, amp[155]); 
  FFV2_0(w[30], w[35], w[48], pars->GC_100, amp[156]); 
  FFV1_0(w[20], w[29], w[36], pars->GC_1, amp[157]); 
  FFV1_0(w[20], w[29], w[37], pars->GC_11, amp[158]); 
  FFV2_3_0(w[20], w[29], w[38], pars->GC_50, pars->GC_58, amp[159]); 
  FFV2_0(w[20], w[2], w[54], pars->GC_100, amp[160]); 
  VVV1_0(w[0], w[37], w[33], pars->GC_10, amp[161]); 
  FFV1_0(w[5], w[2], w[9], pars->GC_2, amp[162]); 
  FFV1_0(w[5], w[2], w[10], pars->GC_11, amp[163]); 
  FFV2_5_0(w[5], w[2], w[11], pars->GC_51, pars->GC_58, amp[164]); 
  FFV1_0(w[1], w[12], w[9], pars->GC_2, amp[165]); 
  FFV1_0(w[1], w[12], w[10], pars->GC_11, amp[166]); 
  FFV2_5_0(w[1], w[12], w[11], pars->GC_51, pars->GC_58, amp[167]); 
  FFV1_0(w[4], w[16], w[17], pars->GC_2, amp[168]); 
  FFV1_0(w[4], w[16], w[18], pars->GC_11, amp[169]); 
  FFV2_5_0(w[4], w[16], w[19], pars->GC_51, pars->GC_58, amp[170]); 
  FFV1_0(w[20], w[3], w[17], pars->GC_2, amp[171]); 
  FFV1_0(w[20], w[3], w[18], pars->GC_11, amp[172]); 
  FFV2_5_0(w[20], w[3], w[19], pars->GC_51, pars->GC_58, amp[173]); 
  VVV1_0(w[0], w[18], w[10], pars->GC_10, amp[174]); 
  FFV1_0(w[5], w[2], w[23], pars->GC_2, amp[175]); 
  FFV1_0(w[5], w[2], w[10], pars->GC_11, amp[176]); 
  FFV2_5_0(w[5], w[2], w[24], pars->GC_51, pars->GC_58, amp[177]); 
  FFV1_0(w[1], w[12], w[23], pars->GC_2, amp[178]); 
  FFV1_0(w[1], w[12], w[10], pars->GC_11, amp[179]); 
  FFV2_5_0(w[1], w[12], w[24], pars->GC_51, pars->GC_58, amp[180]); 
  FFV1_0(w[4], w[16], w[17], pars->GC_1, amp[181]); 
  FFV1_0(w[4], w[16], w[18], pars->GC_11, amp[182]); 
  FFV2_3_0(w[4], w[16], w[19], pars->GC_50, pars->GC_58, amp[183]); 
  FFV1_0(w[20], w[3], w[17], pars->GC_1, amp[184]); 
  FFV1_0(w[20], w[3], w[18], pars->GC_11, amp[185]); 
  FFV2_3_0(w[20], w[3], w[19], pars->GC_50, pars->GC_58, amp[186]); 
  VVV1_0(w[0], w[18], w[10], pars->GC_10, amp[187]); 
  FFV1_0(w[20], w[2], w[25], pars->GC_2, amp[188]); 
  FFV1_0(w[20], w[2], w[14], pars->GC_11, amp[189]); 
  FFV2_5_0(w[20], w[2], w[26], pars->GC_51, pars->GC_58, amp[190]); 
  FFV1_0(w[4], w[12], w[25], pars->GC_2, amp[191]); 
  FFV1_0(w[4], w[12], w[14], pars->GC_11, amp[192]); 
  FFV2_5_0(w[4], w[12], w[26], pars->GC_51, pars->GC_58, amp[193]); 
  FFV1_0(w[1], w[16], w[6], pars->GC_1, amp[194]); 
  FFV1_0(w[1], w[16], w[7], pars->GC_11, amp[195]); 
  FFV2_3_0(w[1], w[16], w[8], pars->GC_50, pars->GC_58, amp[196]); 
  FFV1_0(w[5], w[3], w[6], pars->GC_1, amp[197]); 
  FFV1_0(w[5], w[3], w[7], pars->GC_11, amp[198]); 
  FFV2_3_0(w[5], w[3], w[8], pars->GC_50, pars->GC_58, amp[199]); 
  VVV1_0(w[0], w[7], w[14], pars->GC_10, amp[200]); 
  FFV1_0(w[5], w[2], w[23], pars->GC_1, amp[201]); 
  FFV1_0(w[5], w[2], w[10], pars->GC_11, amp[202]); 
  FFV2_3_0(w[5], w[2], w[24], pars->GC_50, pars->GC_58, amp[203]); 
  FFV1_0(w[1], w[12], w[23], pars->GC_1, amp[204]); 
  FFV1_0(w[1], w[12], w[10], pars->GC_11, amp[205]); 
  FFV2_3_0(w[1], w[12], w[24], pars->GC_50, pars->GC_58, amp[206]); 
  FFV1_0(w[4], w[16], w[27], pars->GC_1, amp[207]); 
  FFV1_0(w[4], w[16], w[18], pars->GC_11, amp[208]); 
  FFV2_3_0(w[4], w[16], w[28], pars->GC_50, pars->GC_58, amp[209]); 
  FFV1_0(w[20], w[3], w[27], pars->GC_1, amp[210]); 
  FFV1_0(w[20], w[3], w[18], pars->GC_11, amp[211]); 
  FFV2_3_0(w[20], w[3], w[28], pars->GC_50, pars->GC_58, amp[212]); 
  VVV1_0(w[0], w[18], w[10], pars->GC_10, amp[213]); 
  FFV1_0(w[31], w[29], w[6], pars->GC_2, amp[214]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[215]); 
  FFV2_5_0(w[31], w[29], w[8], pars->GC_51, pars->GC_58, amp[216]); 
  FFV1_0(w[30], w[35], w[6], pars->GC_2, amp[217]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[218]); 
  FFV2_5_0(w[30], w[35], w[8], pars->GC_51, pars->GC_58, amp[219]); 
  FFV1_0(w[4], w[12], w[39], pars->GC_2, amp[220]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[221]); 
  FFV2_5_0(w[4], w[12], w[41], pars->GC_51, pars->GC_58, amp[222]); 
  FFV1_0(w[20], w[2], w[39], pars->GC_2, amp[223]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[224]); 
  FFV2_5_0(w[20], w[2], w[41], pars->GC_51, pars->GC_58, amp[225]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[226]); 
  FFV1_0(w[31], w[29], w[21], pars->GC_2, amp[227]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[228]); 
  FFV2_5_0(w[31], w[29], w[22], pars->GC_51, pars->GC_58, amp[229]); 
  FFV1_0(w[30], w[35], w[21], pars->GC_2, amp[230]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[231]); 
  FFV2_5_0(w[30], w[35], w[22], pars->GC_51, pars->GC_58, amp[232]); 
  FFV1_0(w[4], w[12], w[39], pars->GC_1, amp[233]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[234]); 
  FFV2_3_0(w[4], w[12], w[41], pars->GC_50, pars->GC_58, amp[235]); 
  FFV1_0(w[20], w[2], w[39], pars->GC_1, amp[236]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[237]); 
  FFV2_3_0(w[20], w[2], w[41], pars->GC_50, pars->GC_58, amp[238]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[239]); 
  FFV1_0(w[31], w[2], w[42], pars->GC_2, amp[240]); 
  FFV1_0(w[31], w[2], w[33], pars->GC_11, amp[241]); 
  FFV2_5_0(w[31], w[2], w[43], pars->GC_51, pars->GC_58, amp[242]); 
  FFV1_0(w[30], w[12], w[42], pars->GC_2, amp[243]); 
  FFV1_0(w[30], w[12], w[33], pars->GC_11, amp[244]); 
  FFV2_5_0(w[30], w[12], w[43], pars->GC_51, pars->GC_58, amp[245]); 
  FFV1_0(w[4], w[35], w[36], pars->GC_1, amp[246]); 
  FFV1_0(w[4], w[35], w[37], pars->GC_11, amp[247]); 
  FFV2_3_0(w[4], w[35], w[38], pars->GC_50, pars->GC_58, amp[248]); 
  FFV1_0(w[20], w[29], w[36], pars->GC_1, amp[249]); 
  FFV1_0(w[20], w[29], w[37], pars->GC_11, amp[250]); 
  FFV2_3_0(w[20], w[29], w[38], pars->GC_50, pars->GC_58, amp[251]); 
  VVV1_0(w[0], w[37], w[33], pars->GC_10, amp[252]); 
  FFV1_0(w[31], w[29], w[21], pars->GC_1, amp[253]); 
  FFV1_0(w[31], w[29], w[7], pars->GC_11, amp[254]); 
  FFV2_3_0(w[31], w[29], w[22], pars->GC_50, pars->GC_58, amp[255]); 
  FFV1_0(w[30], w[35], w[21], pars->GC_1, amp[256]); 
  FFV1_0(w[30], w[35], w[7], pars->GC_11, amp[257]); 
  FFV2_3_0(w[30], w[35], w[22], pars->GC_50, pars->GC_58, amp[258]); 
  FFV1_0(w[4], w[12], w[46], pars->GC_1, amp[259]); 
  FFV1_0(w[4], w[12], w[40], pars->GC_11, amp[260]); 
  FFV2_3_0(w[4], w[12], w[47], pars->GC_50, pars->GC_58, amp[261]); 
  FFV1_0(w[20], w[2], w[46], pars->GC_1, amp[262]); 
  FFV1_0(w[20], w[2], w[40], pars->GC_11, amp[263]); 
  FFV2_3_0(w[20], w[2], w[47], pars->GC_50, pars->GC_58, amp[264]); 
  VVV1_0(w[0], w[40], w[7], pars->GC_10, amp[265]); 
  FFV2_0(w[5], w[3], w[48], pars->GC_100, amp[266]); 
  FFV2_0(w[4], w[12], w[49], pars->GC_100, amp[267]); 
  FFV2_0(w[1], w[16], w[48], pars->GC_100, amp[268]); 
  FFV2_0(w[20], w[2], w[49], pars->GC_100, amp[269]); 
  FFV2_0(w[20], w[3], w[50], pars->GC_100, amp[270]); 
  FFV2_0(w[1], w[12], w[51], pars->GC_100, amp[271]); 
  FFV2_0(w[4], w[16], w[50], pars->GC_100, amp[272]); 
  FFV2_0(w[5], w[2], w[51], pars->GC_100, amp[273]); 
  FFV2_0(w[31], w[2], w[52], pars->GC_100, amp[274]); 
  FFV2_0(w[4], w[35], w[53], pars->GC_100, amp[275]); 
  FFV2_0(w[30], w[12], w[52], pars->GC_100, amp[276]); 
  FFV2_0(w[20], w[29], w[53], pars->GC_100, amp[277]); 
  FFV2_0(w[31], w[29], w[48], pars->GC_100, amp[278]); 
  FFV2_0(w[4], w[12], w[54], pars->GC_100, amp[279]); 
  FFV2_0(w[30], w[35], w[48], pars->GC_100, amp[280]); 
  FFV2_0(w[20], w[2], w[54], pars->GC_100, amp[281]); 


}
double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gu_uuux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 26;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * amp[1] - amp[3] + 1./6. * amp[4] - amp[5] + 1./2. * amp[7]
      - amp[9] + 1./6. * amp[10] - amp[11] - 1./2. * Complex<double> (0, 1) *
      amp[25];
  jamp[1] = +amp[6] - 1./6. * amp[7] + amp[8] - 1./2. * amp[10] - 1./2. *
      amp[19] + amp[21] - 1./6. * amp[22] + amp[23] - 1./2. * Complex<double>
      (0, 1) * amp[24];
  jamp[2] = +amp[0] - 1./6. * amp[1] + amp[2] - 1./2. * amp[4] - 1./2. *
      amp[13] + amp[15] - 1./6. * amp[16] + amp[17] + 1./2. * Complex<double>
      (0, 1) * amp[24];
  jamp[3] = -amp[12] + 1./6. * amp[13] - amp[14] + 1./2. * amp[16] - amp[18] +
      1./6. * amp[19] - amp[20] + 1./2. * amp[22] + 1./2. * Complex<double> (0,
      1) * amp[25];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gd_dddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 26;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * amp[1] - amp[28] + 1./6. * amp[4] - amp[29] + 1./2. *
      amp[7] - amp[32] + 1./6. * amp[10] - amp[33] - 1./2. * Complex<double>
      (0, 1) * amp[25];
  jamp[1] = +amp[30] - 1./6. * amp[7] + amp[31] - 1./2. * amp[10] - 1./2. *
      amp[19] + amp[40] - 1./6. * amp[22] + amp[41] - 1./2. * Complex<double>
      (0, 1) * amp[24];
  jamp[2] = +amp[26] - 1./6. * amp[1] + amp[27] - 1./2. * amp[4] - 1./2. *
      amp[13] + amp[36] - 1./6. * amp[16] + amp[37] + 1./2. * Complex<double>
      (0, 1) * amp[24];
  jamp[3] = -amp[34] + 1./6. * amp[13] - amp[35] + 1./2. * amp[16] - amp[38] +
      1./6. * amp[19] - amp[39] + 1./2. * amp[22] + 1./2. * Complex<double> (0,
      1) * amp[25];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gux_uuxux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 26;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * amp[43] - amp[45] + 1./6. * amp[46] - amp[47] + 1./2. *
      amp[49] - amp[51] + 1./6. * amp[52] - amp[53] - 1./2. * Complex<double>
      (0, 1) * amp[67];
  jamp[1] = +amp[48] - 1./6. * amp[49] + amp[50] - 1./2. * amp[52] - 1./2. *
      amp[61] + amp[63] - 1./6. * amp[64] + amp[65] - 1./2. * Complex<double>
      (0, 1) * amp[66];
  jamp[2] = +amp[42] - 1./6. * amp[43] + amp[44] - 1./2. * amp[46] - 1./2. *
      amp[55] + amp[57] - 1./6. * amp[58] + amp[59] + 1./2. * Complex<double>
      (0, 1) * amp[66];
  jamp[3] = -amp[54] + 1./6. * amp[55] - amp[56] + 1./2. * amp[58] - amp[60] +
      1./6. * amp[61] - amp[62] + 1./2. * amp[64] + 1./2. * Complex<double> (0,
      1) * amp[67];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gdx_ddxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 26;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * amp[69] - amp[71] + 1./6. * amp[72] - amp[73] + 1./2. *
      amp[75] - amp[77] + 1./6. * amp[78] - amp[79] - 1./2. * Complex<double>
      (0, 1) * amp[93];
  jamp[1] = +amp[74] - 1./6. * amp[75] + amp[76] - 1./2. * amp[78] - 1./2. *
      amp[87] + amp[89] - 1./6. * amp[90] + amp[91] - 1./2. * Complex<double>
      (0, 1) * amp[92];
  jamp[2] = +amp[68] - 1./6. * amp[69] + amp[70] - 1./2. * amp[72] - 1./2. *
      amp[81] + amp[83] - 1./6. * amp[84] + amp[85] + 1./2. * Complex<double>
      (0, 1) * amp[92];
  jamp[3] = -amp[80] + 1./6. * amp[81] - amp[82] + 1./2. * amp[84] - amp[86] +
      1./6. * amp[87] - amp[88] + 1./2. * amp[90] + 1./2. * Complex<double> (0,
      1) * amp[93];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gu_uddx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[95] + 1./6. * amp[96] - amp[97] - amp[99] + 1./6. * amp[100] -
      amp[101];
  jamp[1] = +amp[98] - 1./2. * amp[100] - 1./2. * amp[107] + amp[109] - 1./2. *
      Complex<double> (0, 1) * amp[110];
  jamp[2] = +amp[94] - 1./2. * amp[96] - 1./2. * amp[103] + amp[105] + 1./2. *
      Complex<double> (0, 1) * amp[110];
  jamp[3] = -amp[102] + 1./6. * amp[103] - amp[104] - amp[106] + 1./6. *
      amp[107] - amp[108];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gd_udux() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[115] + 1./2. * amp[117] + 1./2. * amp[124] - amp[126] + 1./2.
      * Complex<double> (0, 1) * amp[127];
  jamp[1] = +amp[112] - 1./6. * amp[113] + amp[114] + amp[116] - 1./6. *
      amp[117] + amp[118];
  jamp[2] = +amp[119] - 1./6. * amp[120] + amp[121] + amp[123] - 1./6. *
      amp[124] + amp[125];
  jamp[3] = -amp[111] + 1./2. * amp[113] + 1./2. * amp[120] - amp[122] - 1./2.
      * Complex<double> (0, 1) * amp[127];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gux_duxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[129] + 1./6. * amp[130] - amp[131] - amp[133] + 1./6. *
      amp[134] - amp[135];
  jamp[1] = +amp[132] - 1./2. * amp[134] - 1./2. * amp[141] + amp[143] - 1./2.
      * Complex<double> (0, 1) * amp[144];
  jamp[2] = +amp[128] - 1./2. * amp[130] - 1./2. * amp[137] + amp[139] + 1./2.
      * Complex<double> (0, 1) * amp[144];
  jamp[3] = -amp[136] + 1./6. * amp[137] - amp[138] - amp[140] + 1./6. *
      amp[141] - amp[142];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gdx_uuxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 17;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[145] + 1./2. * amp[147] + 1./2. * amp[154] - amp[156] - 1./2.
      * Complex<double> (0, 1) * amp[161];
  jamp[1] = +amp[153] - 1./6. * amp[154] + amp[155] + amp[157] - 1./6. *
      amp[158] + amp[159];
  jamp[2] = +amp[146] - 1./6. * amp[147] + amp[148] + amp[150] - 1./6. *
      amp[151] + amp[152];
  jamp[3] = -amp[149] + 1./2. * amp[151] + 1./2. * amp[158] - amp[160] + 1./2.
      * Complex<double> (0, 1) * amp[161];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gu_uccx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[162] + 1./6. * amp[163] - amp[164] - amp[165] + 1./6. *
      amp[166] - amp[167];
  jamp[1] = +1./2. * (-amp[166] - amp[172] - Complex<double> (0, 1) *
      amp[174]);
  jamp[2] = +1./2. * (-amp[163] - amp[169] + Complex<double> (0, 1) *
      amp[174]);
  jamp[3] = -amp[168] + 1./6. * amp[169] - amp[170] - amp[171] + 1./6. *
      amp[172] - amp[173];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gu_ussx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[175] + 1./6. * amp[176] - amp[177] - amp[178] + 1./6. *
      amp[179] - amp[180];
  jamp[1] = +1./2. * (-amp[179] - amp[185] - Complex<double> (0, 1) *
      amp[187]);
  jamp[2] = +1./2. * (-amp[176] - amp[182] + Complex<double> (0, 1) *
      amp[187]);
  jamp[3] = -amp[181] + 1./6. * amp[182] - amp[183] - amp[184] + 1./6. *
      amp[185] - amp[186];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gd_cdcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[192] + amp[198] + Complex<double> (0, 1) *
      amp[200]);
  jamp[1] = +amp[188] - 1./6. * amp[189] + amp[190] + amp[191] - 1./6. *
      amp[192] + amp[193];
  jamp[2] = +amp[194] - 1./6. * amp[195] + amp[196] + amp[197] - 1./6. *
      amp[198] + amp[199];
  jamp[3] = +1./2. * (+amp[189] + amp[195] - Complex<double> (0, 1) *
      amp[200]);

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gd_dssx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[201] + 1./6. * amp[202] - amp[203] - amp[204] + 1./6. *
      amp[205] - amp[206];
  jamp[1] = +1./2. * (-amp[205] - amp[211] - Complex<double> (0, 1) *
      amp[213]);
  jamp[2] = +1./2. * (-amp[202] - amp[208] + Complex<double> (0, 1) *
      amp[213]);
  jamp[3] = -amp[207] + 1./6. * amp[208] - amp[209] - amp[210] + 1./6. *
      amp[211] - amp[212];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gux_cuxcx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[214] + 1./6. * amp[215] - amp[216] - amp[217] + 1./6. *
      amp[218] - amp[219];
  jamp[1] = +1./2. * (-amp[218] - amp[224] - Complex<double> (0, 1) *
      amp[226]);
  jamp[2] = +1./2. * (-amp[215] - amp[221] + Complex<double> (0, 1) *
      amp[226]);
  jamp[3] = -amp[220] + 1./6. * amp[221] - amp[222] - amp[223] + 1./6. *
      amp[224] - amp[225];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gux_suxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[227] + 1./6. * amp[228] - amp[229] - amp[230] + 1./6. *
      amp[231] - amp[232];
  jamp[1] = +1./2. * (-amp[231] - amp[237] - Complex<double> (0, 1) *
      amp[239]);
  jamp[2] = +1./2. * (-amp[228] - amp[234] + Complex<double> (0, 1) *
      amp[239]);
  jamp[3] = -amp[233] + 1./6. * amp[234] - amp[235] - amp[236] + 1./6. *
      amp[237] - amp[238];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gdx_ccxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = +1./2. * (+amp[241] + amp[247] - Complex<double> (0, 1) *
      amp[252]);
  jamp[1] = +amp[246] - 1./6. * amp[247] + amp[248] + amp[249] - 1./6. *
      amp[250] + amp[251];
  jamp[2] = +amp[240] - 1./6. * amp[241] + amp[242] + amp[243] - 1./6. *
      amp[244] + amp[245];
  jamp[3] = +1./2. * (+amp[244] + amp[250] + Complex<double> (0, 1) *
      amp[252]);

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gdx_sdxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 4; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1, 1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 4, 4, 0}, {4, 12, 0, 4}, {4,
      0, 12, 4}, {0, 4, 4, 12}};

  // Calculate color flows
  jamp[0] = -amp[253] + 1./6. * amp[254] - amp[255] - amp[256] + 1./6. *
      amp[257] - amp[258];
  jamp[1] = +1./2. * (-amp[257] - amp[263] - Complex<double> (0, 1) *
      amp[265]);
  jamp[2] = +1./2. * (-amp[254] - amp[260] + Complex<double> (0, 1) *
      amp[265]);
  jamp[3] = -amp[259] + 1./6. * amp[260] - amp[261] - amp[262] + 1./6. *
      amp[263] - amp[264];

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gu_cdsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 4;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 0}, {0, 12}}; 

  // Calculate color flows
  jamp[0] = +amp[267] + amp[269]; 
  jamp[1] = +amp[266] + amp[268]; 

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gd_uscx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 4;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 0}, {0, 12}}; 

  // Calculate color flows
  jamp[0] = -amp[271] - amp[273]; 
  jamp[1] = -amp[270] - amp[272]; 

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gux_scxdx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 4;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 0}, {0, 12}}; 

  // Calculate color flows
  jamp[0] = +amp[275] + amp[277]; 
  jamp[1] = +amp[274] + amp[276]; 

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

double PY8MEs_R5_P11_sm_gq_qqq::matrix_5_gdx_cuxsx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 4;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{12, 0}, {0, 12}}; 

  // Calculate color flows
  jamp[0] = -amp[278] - amp[280]; 
  jamp[1] = -amp[279] - amp[281]; 

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


}  // end namespace PY8MEs_namespace

