//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R7_P8_sm_qb_llqb.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u b > e- e+ u b WEIGHTED<=99 @7
// Process: u b > mu- mu+ u b WEIGHTED<=99 @7
// Process: c b > e- e+ c b WEIGHTED<=99 @7
// Process: c b > mu- mu+ c b WEIGHTED<=99 @7
// Process: u b~ > e- e+ u b~ WEIGHTED<=99 @7
// Process: u b~ > mu- mu+ u b~ WEIGHTED<=99 @7
// Process: c b~ > e- e+ c b~ WEIGHTED<=99 @7
// Process: c b~ > mu- mu+ c b~ WEIGHTED<=99 @7
// Process: d b > e- e+ d b WEIGHTED<=99 @7
// Process: d b > mu- mu+ d b WEIGHTED<=99 @7
// Process: s b > e- e+ s b WEIGHTED<=99 @7
// Process: s b > mu- mu+ s b WEIGHTED<=99 @7
// Process: d b~ > e- e+ d b~ WEIGHTED<=99 @7
// Process: d b~ > mu- mu+ d b~ WEIGHTED<=99 @7
// Process: s b~ > e- e+ s b~ WEIGHTED<=99 @7
// Process: s b~ > mu- mu+ s b~ WEIGHTED<=99 @7
// Process: u~ b > e- e+ u~ b WEIGHTED<=99 @7
// Process: u~ b > mu- mu+ u~ b WEIGHTED<=99 @7
// Process: c~ b > e- e+ c~ b WEIGHTED<=99 @7
// Process: c~ b > mu- mu+ c~ b WEIGHTED<=99 @7
// Process: u~ b~ > e- e+ u~ b~ WEIGHTED<=99 @7
// Process: u~ b~ > mu- mu+ u~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > e- e+ c~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > mu- mu+ c~ b~ WEIGHTED<=99 @7
// Process: d~ b > e- e+ d~ b WEIGHTED<=99 @7
// Process: d~ b > mu- mu+ d~ b WEIGHTED<=99 @7
// Process: s~ b > e- e+ s~ b WEIGHTED<=99 @7
// Process: s~ b > mu- mu+ s~ b WEIGHTED<=99 @7
// Process: d~ b~ > e- e+ d~ b~ WEIGHTED<=99 @7
// Process: d~ b~ > mu- mu+ d~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > e- e+ s~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > mu- mu+ s~ b~ WEIGHTED<=99 @7
// Process: u b > ve ve~ u b WEIGHTED<=99 @7
// Process: u b > vm vm~ u b WEIGHTED<=99 @7
// Process: c b > ve ve~ c b WEIGHTED<=99 @7
// Process: c b > vm vm~ c b WEIGHTED<=99 @7
// Process: u b~ > ve ve~ u b~ WEIGHTED<=99 @7
// Process: u b~ > vm vm~ u b~ WEIGHTED<=99 @7
// Process: c b~ > ve ve~ c b~ WEIGHTED<=99 @7
// Process: c b~ > vm vm~ c b~ WEIGHTED<=99 @7
// Process: d b > ve ve~ d b WEIGHTED<=99 @7
// Process: d b > vm vm~ d b WEIGHTED<=99 @7
// Process: s b > ve ve~ s b WEIGHTED<=99 @7
// Process: s b > vm vm~ s b WEIGHTED<=99 @7
// Process: d b~ > ve ve~ d b~ WEIGHTED<=99 @7
// Process: d b~ > vm vm~ d b~ WEIGHTED<=99 @7
// Process: s b~ > ve ve~ s b~ WEIGHTED<=99 @7
// Process: s b~ > vm vm~ s b~ WEIGHTED<=99 @7
// Process: u~ b > ve ve~ u~ b WEIGHTED<=99 @7
// Process: u~ b > vm vm~ u~ b WEIGHTED<=99 @7
// Process: c~ b > ve ve~ c~ b WEIGHTED<=99 @7
// Process: c~ b > vm vm~ c~ b WEIGHTED<=99 @7
// Process: u~ b~ > ve ve~ u~ b~ WEIGHTED<=99 @7
// Process: u~ b~ > vm vm~ u~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > ve ve~ c~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > vm vm~ c~ b~ WEIGHTED<=99 @7
// Process: d~ b > ve ve~ d~ b WEIGHTED<=99 @7
// Process: d~ b > vm vm~ d~ b WEIGHTED<=99 @7
// Process: s~ b > ve ve~ s~ b WEIGHTED<=99 @7
// Process: s~ b > vm vm~ s~ b WEIGHTED<=99 @7
// Process: d~ b~ > ve ve~ d~ b~ WEIGHTED<=99 @7
// Process: d~ b~ > vm vm~ d~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > ve ve~ s~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > vm vm~ s~ b~ WEIGHTED<=99 @7
// Process: u b > ve e+ d b WEIGHTED<=99 @7
// Process: u b > vm mu+ d b WEIGHTED<=99 @7
// Process: c b > ve e+ s b WEIGHTED<=99 @7
// Process: c b > vm mu+ s b WEIGHTED<=99 @7
// Process: u b~ > ve e+ d b~ WEIGHTED<=99 @7
// Process: u b~ > vm mu+ d b~ WEIGHTED<=99 @7
// Process: c b~ > ve e+ s b~ WEIGHTED<=99 @7
// Process: c b~ > vm mu+ s b~ WEIGHTED<=99 @7
// Process: d b > e- ve~ u b WEIGHTED<=99 @7
// Process: d b > mu- vm~ u b WEIGHTED<=99 @7
// Process: s b > e- ve~ c b WEIGHTED<=99 @7
// Process: s b > mu- vm~ c b WEIGHTED<=99 @7
// Process: d b~ > e- ve~ u b~ WEIGHTED<=99 @7
// Process: d b~ > mu- vm~ u b~ WEIGHTED<=99 @7
// Process: s b~ > e- ve~ c b~ WEIGHTED<=99 @7
// Process: s b~ > mu- vm~ c b~ WEIGHTED<=99 @7
// Process: u~ b > e- ve~ d~ b WEIGHTED<=99 @7
// Process: u~ b > mu- vm~ d~ b WEIGHTED<=99 @7
// Process: c~ b > e- ve~ s~ b WEIGHTED<=99 @7
// Process: c~ b > mu- vm~ s~ b WEIGHTED<=99 @7
// Process: u~ b~ > e- ve~ d~ b~ WEIGHTED<=99 @7
// Process: u~ b~ > mu- vm~ d~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > e- ve~ s~ b~ WEIGHTED<=99 @7
// Process: c~ b~ > mu- vm~ s~ b~ WEIGHTED<=99 @7
// Process: d~ b > ve e+ u~ b WEIGHTED<=99 @7
// Process: d~ b > vm mu+ u~ b WEIGHTED<=99 @7
// Process: s~ b > ve e+ c~ b WEIGHTED<=99 @7
// Process: s~ b > vm mu+ c~ b WEIGHTED<=99 @7
// Process: d~ b~ > ve e+ u~ b~ WEIGHTED<=99 @7
// Process: d~ b~ > vm mu+ u~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > ve e+ c~ b~ WEIGHTED<=99 @7
// Process: s~ b~ > vm mu+ c~ b~ WEIGHTED<=99 @7

// Exception class
class PY8MEs_R7_P8_sm_qb_llqbException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R7_P8_sm_qb_llqb'."; 
  }
}
PY8MEs_R7_P8_sm_qb_llqb_exception; 

std::set<int> PY8MEs_R7_P8_sm_qb_llqb::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R7_P8_sm_qb_llqb::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R7_P8_sm_qb_llqb::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
int PY8MEs_R7_P8_sm_qb_llqb::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
int PY8MEs_R7_P8_sm_qb_llqb::denom_iden[nprocesses] = {1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R7_P8_sm_qb_llqb::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u b > e- e+ u b WEIGHTED<=99 @7
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

  // Color flows of process Process: u b~ > e- e+ u b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: d b > e- e+ d b WEIGHTED<=99 @7
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

  // Color flows of process Process: d b~ > e- e+ d b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: u~ b > e- e+ u~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: u~ b~ > e- e+ u~ b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: d~ b > e- e+ d~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: d~ b~ > e- e+ d~ b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[7].push_back(0); 

  // Color flows of process Process: u b > ve ve~ u b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[8].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[8].push_back(0); 
  // JAMP #1
  color_configs[8].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[8].push_back(0); 

  // Color flows of process Process: u b~ > ve ve~ u b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: d b > ve ve~ d b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[10].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[10].push_back(0); 
  // JAMP #1
  color_configs[10].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[10].push_back(0); 

  // Color flows of process Process: d b~ > ve ve~ d b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[11].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[11].push_back(0); 
  // JAMP #1
  color_configs[11].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[11].push_back(0); 

  // Color flows of process Process: u~ b > ve ve~ u~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[12].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 
  // JAMP #1
  color_configs[12].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[12].push_back(0); 

  // Color flows of process Process: u~ b~ > ve ve~ u~ b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[13].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[13].push_back(0); 
  // JAMP #1
  color_configs[13].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[13].push_back(0); 

  // Color flows of process Process: d~ b > ve ve~ d~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[14].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[14].push_back(0); 
  // JAMP #1
  color_configs[14].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[14].push_back(0); 

  // Color flows of process Process: d~ b~ > ve ve~ d~ b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[15].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[15].push_back(0); 
  // JAMP #1
  color_configs[15].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[15].push_back(0); 

  // Color flows of process Process: u b > ve e+ d b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[16].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[16].push_back(0); 
  // JAMP #1
  color_configs[16].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[16].push_back(0); 

  // Color flows of process Process: u b~ > ve e+ d b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: d b > e- ve~ u b WEIGHTED<=99 @7
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

  // Color flows of process Process: d b~ > e- ve~ u b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: u~ b > e- ve~ d~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[20].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[20].push_back(0); 
  // JAMP #1
  color_configs[20].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[20].push_back(0); 

  // Color flows of process Process: u~ b~ > e- ve~ d~ b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[21].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[21].push_back(0); 
  // JAMP #1
  color_configs[21].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[21].push_back(0); 

  // Color flows of process Process: d~ b > ve e+ u~ b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[22].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[22].push_back(0); 
  // JAMP #1
  color_configs[22].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[22].push_back(0); 

  // Color flows of process Process: d~ b~ > ve e+ u~ b~ WEIGHTED<=99 @7
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
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R7_P8_sm_qb_llqb::~PY8MEs_R7_P8_sm_qb_llqb() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R7_P8_sm_qb_llqb::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R7_P8_sm_qb_llqb::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R7_P8_sm_qb_llqb::getColorConfigs(int
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
int PY8MEs_R7_P8_sm_qb_llqb::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R7_P8_sm_qb_llqb::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
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
int PY8MEs_R7_P8_sm_qb_llqb::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R7_P8_sm_qb_llqb': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R7_P8_sm_qb_llqb::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R7_P8_sm_qb_llqb': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
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
int PY8MEs_R7_P8_sm_qb_llqb::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R7_P8_sm_qb_llqb': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
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
      " 'PY8MEs_R7_P8_sm_qb_llqb': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R7_P8_sm_qb_llqb::getAllResults(int
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
double PY8MEs_R7_P8_sm_qb_llqb::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
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
    " 'PY8MEs_R7_P8_sm_qb_llqb': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R7_P8_sm_qb_llqb::static_getPY8ME(vector<int>
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
  const int nprocs = 192; 
  const int proc_IDS[nprocs] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
      4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9,
      10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14,
      14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18,
      19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23,
      23, 23, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5,
      5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11,
      11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15,
      15, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20,
      20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23};
  const int in_pdgs[nprocs][ninitial] = {{2, 5}, {2, 5}, {4, 5}, {4, 5}, {2,
      -5}, {2, -5}, {4, -5}, {4, -5}, {1, 5}, {1, 5}, {3, 5}, {3, 5}, {1, -5},
      {1, -5}, {3, -5}, {3, -5}, {-2, 5}, {-2, 5}, {-4, 5}, {-4, 5}, {-2, -5},
      {-2, -5}, {-4, -5}, {-4, -5}, {-1, 5}, {-1, 5}, {-3, 5}, {-3, 5}, {-1,
      -5}, {-1, -5}, {-3, -5}, {-3, -5}, {2, 5}, {2, 5}, {4, 5}, {4, 5}, {2,
      -5}, {2, -5}, {4, -5}, {4, -5}, {1, 5}, {1, 5}, {3, 5}, {3, 5}, {1, -5},
      {1, -5}, {3, -5}, {3, -5}, {-2, 5}, {-2, 5}, {-4, 5}, {-4, 5}, {-2, -5},
      {-2, -5}, {-4, -5}, {-4, -5}, {-1, 5}, {-1, 5}, {-3, 5}, {-3, 5}, {-1,
      -5}, {-1, -5}, {-3, -5}, {-3, -5}, {2, 5}, {2, 5}, {4, 5}, {4, 5}, {2,
      -5}, {2, -5}, {4, -5}, {4, -5}, {1, 5}, {1, 5}, {3, 5}, {3, 5}, {1, -5},
      {1, -5}, {3, -5}, {3, -5}, {-2, 5}, {-2, 5}, {-4, 5}, {-4, 5}, {-2, -5},
      {-2, -5}, {-4, -5}, {-4, -5}, {-1, 5}, {-1, 5}, {-3, 5}, {-3, 5}, {-1,
      -5}, {-1, -5}, {-3, -5}, {-3, -5}, {5, 2}, {5, 2}, {5, 4}, {5, 4}, {-5,
      2}, {-5, 2}, {-5, 4}, {-5, 4}, {5, 1}, {5, 1}, {5, 3}, {5, 3}, {-5, 1},
      {-5, 1}, {-5, 3}, {-5, 3}, {5, -2}, {5, -2}, {5, -4}, {5, -4}, {-5, -2},
      {-5, -2}, {-5, -4}, {-5, -4}, {5, -1}, {5, -1}, {5, -3}, {5, -3}, {-5,
      -1}, {-5, -1}, {-5, -3}, {-5, -3}, {5, 2}, {5, 2}, {5, 4}, {5, 4}, {-5,
      2}, {-5, 2}, {-5, 4}, {-5, 4}, {5, 1}, {5, 1}, {5, 3}, {5, 3}, {-5, 1},
      {-5, 1}, {-5, 3}, {-5, 3}, {5, -2}, {5, -2}, {5, -4}, {5, -4}, {-5, -2},
      {-5, -2}, {-5, -4}, {-5, -4}, {5, -1}, {5, -1}, {5, -3}, {5, -3}, {-5,
      -1}, {-5, -1}, {-5, -3}, {-5, -3}, {5, 2}, {5, 2}, {5, 4}, {5, 4}, {-5,
      2}, {-5, 2}, {-5, 4}, {-5, 4}, {5, 1}, {5, 1}, {5, 3}, {5, 3}, {-5, 1},
      {-5, 1}, {-5, 3}, {-5, 3}, {5, -2}, {5, -2}, {5, -4}, {5, -4}, {-5, -2},
      {-5, -2}, {-5, -4}, {-5, -4}, {5, -1}, {5, -1}, {5, -3}, {5, -3}, {-5,
      -1}, {-5, -1}, {-5, -3}, {-5, -3}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{11, -11, 2, 5}, {13,
      -13, 2, 5}, {11, -11, 4, 5}, {13, -13, 4, 5}, {11, -11, 2, -5}, {13, -13,
      2, -5}, {11, -11, 4, -5}, {13, -13, 4, -5}, {11, -11, 1, 5}, {13, -13, 1,
      5}, {11, -11, 3, 5}, {13, -13, 3, 5}, {11, -11, 1, -5}, {13, -13, 1, -5},
      {11, -11, 3, -5}, {13, -13, 3, -5}, {11, -11, -2, 5}, {13, -13, -2, 5},
      {11, -11, -4, 5}, {13, -13, -4, 5}, {11, -11, -2, -5}, {13, -13, -2, -5},
      {11, -11, -4, -5}, {13, -13, -4, -5}, {11, -11, -1, 5}, {13, -13, -1, 5},
      {11, -11, -3, 5}, {13, -13, -3, 5}, {11, -11, -1, -5}, {13, -13, -1, -5},
      {11, -11, -3, -5}, {13, -13, -3, -5}, {12, -12, 2, 5}, {14, -14, 2, 5},
      {12, -12, 4, 5}, {14, -14, 4, 5}, {12, -12, 2, -5}, {14, -14, 2, -5},
      {12, -12, 4, -5}, {14, -14, 4, -5}, {12, -12, 1, 5}, {14, -14, 1, 5},
      {12, -12, 3, 5}, {14, -14, 3, 5}, {12, -12, 1, -5}, {14, -14, 1, -5},
      {12, -12, 3, -5}, {14, -14, 3, -5}, {12, -12, -2, 5}, {14, -14, -2, 5},
      {12, -12, -4, 5}, {14, -14, -4, 5}, {12, -12, -2, -5}, {14, -14, -2, -5},
      {12, -12, -4, -5}, {14, -14, -4, -5}, {12, -12, -1, 5}, {14, -14, -1, 5},
      {12, -12, -3, 5}, {14, -14, -3, 5}, {12, -12, -1, -5}, {14, -14, -1, -5},
      {12, -12, -3, -5}, {14, -14, -3, -5}, {12, -11, 1, 5}, {14, -13, 1, 5},
      {12, -11, 3, 5}, {14, -13, 3, 5}, {12, -11, 1, -5}, {14, -13, 1, -5},
      {12, -11, 3, -5}, {14, -13, 3, -5}, {11, -12, 2, 5}, {13, -14, 2, 5},
      {11, -12, 4, 5}, {13, -14, 4, 5}, {11, -12, 2, -5}, {13, -14, 2, -5},
      {11, -12, 4, -5}, {13, -14, 4, -5}, {11, -12, -1, 5}, {13, -14, -1, 5},
      {11, -12, -3, 5}, {13, -14, -3, 5}, {11, -12, -1, -5}, {13, -14, -1, -5},
      {11, -12, -3, -5}, {13, -14, -3, -5}, {12, -11, -2, 5}, {14, -13, -2, 5},
      {12, -11, -4, 5}, {14, -13, -4, 5}, {12, -11, -2, -5}, {14, -13, -2, -5},
      {12, -11, -4, -5}, {14, -13, -4, -5}, {11, -11, 2, 5}, {13, -13, 2, 5},
      {11, -11, 4, 5}, {13, -13, 4, 5}, {11, -11, 2, -5}, {13, -13, 2, -5},
      {11, -11, 4, -5}, {13, -13, 4, -5}, {11, -11, 1, 5}, {13, -13, 1, 5},
      {11, -11, 3, 5}, {13, -13, 3, 5}, {11, -11, 1, -5}, {13, -13, 1, -5},
      {11, -11, 3, -5}, {13, -13, 3, -5}, {11, -11, -2, 5}, {13, -13, -2, 5},
      {11, -11, -4, 5}, {13, -13, -4, 5}, {11, -11, -2, -5}, {13, -13, -2, -5},
      {11, -11, -4, -5}, {13, -13, -4, -5}, {11, -11, -1, 5}, {13, -13, -1, 5},
      {11, -11, -3, 5}, {13, -13, -3, 5}, {11, -11, -1, -5}, {13, -13, -1, -5},
      {11, -11, -3, -5}, {13, -13, -3, -5}, {12, -12, 2, 5}, {14, -14, 2, 5},
      {12, -12, 4, 5}, {14, -14, 4, 5}, {12, -12, 2, -5}, {14, -14, 2, -5},
      {12, -12, 4, -5}, {14, -14, 4, -5}, {12, -12, 1, 5}, {14, -14, 1, 5},
      {12, -12, 3, 5}, {14, -14, 3, 5}, {12, -12, 1, -5}, {14, -14, 1, -5},
      {12, -12, 3, -5}, {14, -14, 3, -5}, {12, -12, -2, 5}, {14, -14, -2, 5},
      {12, -12, -4, 5}, {14, -14, -4, 5}, {12, -12, -2, -5}, {14, -14, -2, -5},
      {12, -12, -4, -5}, {14, -14, -4, -5}, {12, -12, -1, 5}, {14, -14, -1, 5},
      {12, -12, -3, 5}, {14, -14, -3, 5}, {12, -12, -1, -5}, {14, -14, -1, -5},
      {12, -12, -3, -5}, {14, -14, -3, -5}, {12, -11, 1, 5}, {14, -13, 1, 5},
      {12, -11, 3, 5}, {14, -13, 3, 5}, {12, -11, 1, -5}, {14, -13, 1, -5},
      {12, -11, 3, -5}, {14, -13, 3, -5}, {11, -12, 2, 5}, {13, -14, 2, 5},
      {11, -12, 4, 5}, {13, -14, 4, 5}, {11, -12, 2, -5}, {13, -14, 2, -5},
      {11, -12, 4, -5}, {13, -14, 4, -5}, {11, -12, -1, 5}, {13, -14, -1, 5},
      {11, -12, -3, 5}, {13, -14, -3, 5}, {11, -12, -1, -5}, {13, -14, -1, -5},
      {11, -12, -3, -5}, {13, -14, -3, -5}, {12, -11, -2, 5}, {14, -13, -2, 5},
      {12, -11, -4, 5}, {14, -13, -4, 5}, {12, -11, -2, -5}, {14, -13, -2, -5},
      {12, -11, -4, -5}, {14, -13, -4, -5}};

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
void PY8MEs_R7_P8_sm_qb_llqb::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P8_sm_qb_llqb': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R7_P8_sm_qb_llqb::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R7_P8_sm_qb_llqb::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R7_P8_sm_qb_llqb::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R7_P8_sm_qb_llqb::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R7_P8_sm_qb_llqb::initProc() 
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
  jamp2 = vector < vec_double > (24); 
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
  all_results = vector < vec_vec_double > (24); 
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
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R7_P8_sm_qb_llqb::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->mdl_MB; 
  mME[2] = pars->ZERO; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->ZERO; 
  mME[5] = pars->mdl_MB; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R7_P8_sm_qb_llqb::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R7_P8_sm_qb_llqb::getMasses() 
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
void PY8MEs_R7_P8_sm_qb_llqb::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R7_P8_sm_qb_llqb': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R7_P8_sm_qb_llqb_exception; 
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

double PY8MEs_R7_P8_sm_qb_llqb::sigmaKin() 
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

    if (proc_ID == 0)
      t = matrix_7_ub_emepub(); 
    if (proc_ID == 1)
      t = matrix_7_ubx_emepubx(); 
    if (proc_ID == 2)
      t = matrix_7_db_emepdb(); 
    if (proc_ID == 3)
      t = matrix_7_dbx_emepdbx(); 
    if (proc_ID == 4)
      t = matrix_7_uxb_emepuxb(); 
    if (proc_ID == 5)
      t = matrix_7_uxbx_emepuxbx(); 
    if (proc_ID == 6)
      t = matrix_7_dxb_emepdxb(); 
    if (proc_ID == 7)
      t = matrix_7_dxbx_emepdxbx(); 
    if (proc_ID == 8)
      t = matrix_7_ub_vevexub(); 
    if (proc_ID == 9)
      t = matrix_7_ubx_vevexubx(); 
    if (proc_ID == 10)
      t = matrix_7_db_vevexdb(); 
    if (proc_ID == 11)
      t = matrix_7_dbx_vevexdbx(); 
    if (proc_ID == 12)
      t = matrix_7_uxb_vevexuxb(); 
    if (proc_ID == 13)
      t = matrix_7_uxbx_vevexuxbx(); 
    if (proc_ID == 14)
      t = matrix_7_dxb_vevexdxb(); 
    if (proc_ID == 15)
      t = matrix_7_dxbx_vevexdxbx(); 
    if (proc_ID == 16)
      t = matrix_7_ub_veepdb(); 
    if (proc_ID == 17)
      t = matrix_7_ubx_veepdbx(); 
    if (proc_ID == 18)
      t = matrix_7_db_emvexub(); 
    if (proc_ID == 19)
      t = matrix_7_dbx_emvexubx(); 
    if (proc_ID == 20)
      t = matrix_7_uxb_emvexdxb(); 
    if (proc_ID == 21)
      t = matrix_7_uxbx_emvexdxbx(); 
    if (proc_ID == 22)
      t = matrix_7_dxb_veepuxb(); 
    if (proc_ID == 23)
      t = matrix_7_dxbx_veepuxbx(); 

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

void PY8MEs_R7_P8_sm_qb_llqb::calculate_wavefunctions(const int hel[])
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
  FFV1P0_3(w[3], w[2], pars->GC_3, pars->ZERO, pars->ZERO, w[7]); 
  FFV1_1(w[5], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[8]); 
  FFV1_2(w[1], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[9]); 
  FFV2_4_3(w[3], w[2], pars->GC_50, pars->GC_59, pars->mdl_MZ, pars->mdl_WZ,
      w[10]);
  FFV1P0_3(w[0], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[11]); 
  FFV1_1(w[5], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[12]); 
  FFV1_2(w[1], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[13]); 
  FFV2_5_3(w[0], w[4], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[14]);
  FFV2_3_1(w[5], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[15]);
  FFV2_3_2(w[1], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[16]);
  FFS4_3(w[1], w[5], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[17]); 
  FFV1P0_3(w[1], w[5], pars->GC_1, pars->ZERO, pars->ZERO, w[18]); 
  FFV1_1(w[2], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[19]); 
  FFV1_2(w[3], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[20]); 
  FFV2_3_3(w[1], w[5], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[21]);
  FFV2_4_1(w[2], w[14], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[22]);
  FFV2_4_2(w[3], w[14], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[23]);
  FFV1_2(w[0], w[7], pars->GC_2, pars->ZERO, pars->ZERO, w[24]); 
  FFV1_2(w[0], w[18], pars->GC_2, pars->ZERO, pars->ZERO, w[25]); 
  FFV1P0_3(w[1], w[5], pars->GC_11, pars->ZERO, pars->ZERO, w[26]); 
  FFV1_2(w[0], w[26], pars->GC_11, pars->ZERO, pars->ZERO, w[27]); 
  FFV2_5_2(w[0], w[21], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[28]);
  FFV2_5_2(w[0], w[10], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[29]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[30]); 
  ixxxxx(p[perm[5]], mME[5], hel[5], -1, w[31]); 
  FFV1_1(w[30], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[32]); 
  FFV1_2(w[31], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[33]); 
  FFV1_1(w[30], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[34]); 
  FFV1_2(w[31], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[35]); 
  FFV2_3_1(w[30], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[36]);
  FFV2_3_2(w[31], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[37]);
  FFS4_3(w[31], w[30], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[38]); 
  FFV1P0_3(w[31], w[30], pars->GC_1, pars->ZERO, pars->ZERO, w[39]); 
  FFV2_3_3(w[31], w[30], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[40]);
  FFV1_2(w[0], w[39], pars->GC_2, pars->ZERO, pars->ZERO, w[41]); 
  FFV1P0_3(w[31], w[30], pars->GC_11, pars->ZERO, pars->ZERO, w[42]); 
  FFV1_2(w[0], w[42], pars->GC_11, pars->ZERO, pars->ZERO, w[43]); 
  FFV2_5_2(w[0], w[40], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[44]);
  FFV1P0_3(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[45]); 
  FFV1_1(w[5], w[45], pars->GC_1, pars->mdl_MB, pars->ZERO, w[46]); 
  FFV1_2(w[1], w[45], pars->GC_1, pars->mdl_MB, pars->ZERO, w[47]); 
  FFV2_3_3(w[0], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[48]);
  FFV2_3_1(w[5], w[48], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[49]);
  FFV2_3_2(w[1], w[48], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[50]);
  FFV1_1(w[2], w[45], pars->GC_3, pars->ZERO, pars->ZERO, w[51]); 
  FFV1_2(w[3], w[45], pars->GC_3, pars->ZERO, pars->ZERO, w[52]); 
  FFV2_4_1(w[2], w[48], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[53]);
  FFV2_4_2(w[3], w[48], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[54]);
  FFV1_2(w[0], w[7], pars->GC_1, pars->ZERO, pars->ZERO, w[55]); 
  FFV1_2(w[0], w[18], pars->GC_1, pars->ZERO, pars->ZERO, w[56]); 
  FFV2_3_2(w[0], w[21], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[57]);
  FFV2_3_2(w[0], w[10], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[58]);
  FFV1_1(w[30], w[45], pars->GC_1, pars->mdl_MB, pars->ZERO, w[59]); 
  FFV1_2(w[31], w[45], pars->GC_1, pars->mdl_MB, pars->ZERO, w[60]); 
  FFV2_3_1(w[30], w[48], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[61]);
  FFV2_3_2(w[31], w[48], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[62]);
  FFV1_2(w[0], w[39], pars->GC_1, pars->ZERO, pars->ZERO, w[63]); 
  FFV2_3_2(w[0], w[40], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[64]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[65]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[66]); 
  FFV1P0_3(w[66], w[65], pars->GC_2, pars->ZERO, pars->ZERO, w[67]); 
  FFV1_1(w[5], w[67], pars->GC_1, pars->mdl_MB, pars->ZERO, w[68]); 
  FFV1_2(w[1], w[67], pars->GC_1, pars->mdl_MB, pars->ZERO, w[69]); 
  FFV1P0_3(w[66], w[65], pars->GC_11, pars->ZERO, pars->ZERO, w[70]); 
  FFV1_1(w[5], w[70], pars->GC_11, pars->mdl_MB, pars->ZERO, w[71]); 
  FFV1_2(w[1], w[70], pars->GC_11, pars->mdl_MB, pars->ZERO, w[72]); 
  FFV2_5_3(w[66], w[65], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[73]);
  FFV2_3_1(w[5], w[73], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[74]);
  FFV2_3_2(w[1], w[73], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[75]);
  FFV1_1(w[2], w[67], pars->GC_3, pars->ZERO, pars->ZERO, w[76]); 
  FFV1_2(w[3], w[67], pars->GC_3, pars->ZERO, pars->ZERO, w[77]); 
  FFV2_4_1(w[2], w[73], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[78]);
  FFV2_4_2(w[3], w[73], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[79]);
  FFV1_2(w[66], w[7], pars->GC_2, pars->ZERO, pars->ZERO, w[80]); 
  FFV1_2(w[66], w[18], pars->GC_2, pars->ZERO, pars->ZERO, w[81]); 
  FFV1_2(w[66], w[26], pars->GC_11, pars->ZERO, pars->ZERO, w[82]); 
  FFV2_5_2(w[66], w[21], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[83]);
  FFV2_5_2(w[66], w[10], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[84]);
  FFV1_1(w[30], w[67], pars->GC_1, pars->mdl_MB, pars->ZERO, w[85]); 
  FFV1_2(w[31], w[67], pars->GC_1, pars->mdl_MB, pars->ZERO, w[86]); 
  FFV1_1(w[30], w[70], pars->GC_11, pars->mdl_MB, pars->ZERO, w[87]); 
  FFV1_2(w[31], w[70], pars->GC_11, pars->mdl_MB, pars->ZERO, w[88]); 
  FFV2_3_1(w[30], w[73], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[89]);
  FFV2_3_2(w[31], w[73], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[90]);
  FFV1_2(w[66], w[39], pars->GC_2, pars->ZERO, pars->ZERO, w[91]); 
  FFV1_2(w[66], w[42], pars->GC_11, pars->ZERO, pars->ZERO, w[92]); 
  FFV2_5_2(w[66], w[40], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[93]);
  FFV1P0_3(w[66], w[65], pars->GC_1, pars->ZERO, pars->ZERO, w[94]); 
  FFV1_1(w[5], w[94], pars->GC_1, pars->mdl_MB, pars->ZERO, w[95]); 
  FFV1_2(w[1], w[94], pars->GC_1, pars->mdl_MB, pars->ZERO, w[96]); 
  FFV2_3_3(w[66], w[65], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[97]);
  FFV2_3_1(w[5], w[97], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[98]);
  FFV2_3_2(w[1], w[97], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[99]);
  FFV1_1(w[2], w[94], pars->GC_3, pars->ZERO, pars->ZERO, w[100]); 
  FFV1_2(w[3], w[94], pars->GC_3, pars->ZERO, pars->ZERO, w[101]); 
  FFV2_4_1(w[2], w[97], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[102]);
  FFV2_4_2(w[3], w[97], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[103]);
  FFV1_2(w[66], w[7], pars->GC_1, pars->ZERO, pars->ZERO, w[104]); 
  FFV1_2(w[66], w[18], pars->GC_1, pars->ZERO, pars->ZERO, w[105]); 
  FFV2_3_2(w[66], w[21], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[106]);
  FFV2_3_2(w[66], w[10], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[107]);
  FFV1_1(w[30], w[94], pars->GC_1, pars->mdl_MB, pars->ZERO, w[108]); 
  FFV1_2(w[31], w[94], pars->GC_1, pars->mdl_MB, pars->ZERO, w[109]); 
  FFV2_3_1(w[30], w[97], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[110]);
  FFV2_3_2(w[31], w[97], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[111]);
  FFV1_2(w[66], w[39], pars->GC_1, pars->ZERO, pars->ZERO, w[112]); 
  FFV2_3_2(w[66], w[40], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[113]);
  FFV2_3(w[3], w[2], pars->GC_62, pars->mdl_MZ, pars->mdl_WZ, w[114]); 
  FFV2_1(w[2], w[14], pars->GC_62, pars->ZERO, pars->ZERO, w[115]); 
  FFV2_2(w[3], w[14], pars->GC_62, pars->ZERO, pars->ZERO, w[116]); 
  FFV2_5_2(w[0], w[114], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[117]);
  FFV2_1(w[2], w[48], pars->GC_62, pars->ZERO, pars->ZERO, w[118]); 
  FFV2_2(w[3], w[48], pars->GC_62, pars->ZERO, pars->ZERO, w[119]); 
  FFV2_3_2(w[0], w[114], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[120]);
  FFV2_1(w[2], w[73], pars->GC_62, pars->ZERO, pars->ZERO, w[121]); 
  FFV2_2(w[3], w[73], pars->GC_62, pars->ZERO, pars->ZERO, w[122]); 
  FFV2_5_2(w[66], w[114], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[123]);
  FFV2_1(w[2], w[97], pars->GC_62, pars->ZERO, pars->ZERO, w[124]); 
  FFV2_2(w[3], w[97], pars->GC_62, pars->ZERO, pars->ZERO, w[125]); 
  FFV2_3_2(w[66], w[114], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[126]);
  FFV2_3(w[0], w[4], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[127]); 
  FFV2_3(w[3], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[128]); 
  FFV2_2(w[1], w[127], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[129]); 
  FFV2_1(w[2], w[127], pars->GC_100, pars->ZERO, pars->ZERO, w[130]); 
  FFV2_2(w[3], w[127], pars->GC_100, pars->ZERO, pars->ZERO, w[131]); 
  FFV2_2(w[0], w[128], pars->GC_100, pars->ZERO, pars->ZERO, w[132]); 
  FFV2_2(w[31], w[127], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[133]); 
  FFV2_1(w[5], w[127], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[134]); 
  FFV2_1(w[30], w[127], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[135]); 
  FFV2_3(w[66], w[65], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[136]); 
  FFV2_1(w[5], w[136], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[137]); 
  FFV2_2(w[3], w[136], pars->GC_100, pars->ZERO, pars->ZERO, w[138]); 
  FFV2_1(w[2], w[136], pars->GC_100, pars->ZERO, pars->ZERO, w[139]); 
  FFV2_2(w[66], w[128], pars->GC_100, pars->ZERO, pars->ZERO, w[140]); 
  FFV2_1(w[30], w[136], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[141]); 
  FFV2_2(w[1], w[136], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[142]); 
  FFV2_2(w[31], w[136], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[143]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[1], w[8], w[7], pars->GC_1, amp[0]); 
  FFV1_0(w[9], w[5], w[7], pars->GC_1, amp[1]); 
  FFV2_3_0(w[1], w[8], w[10], pars->GC_50, pars->GC_58, amp[2]); 
  FFV2_3_0(w[9], w[5], w[10], pars->GC_50, pars->GC_58, amp[3]); 
  FFV1_0(w[1], w[12], w[7], pars->GC_1, amp[4]); 
  FFV1_0(w[13], w[5], w[7], pars->GC_1, amp[5]); 
  FFV2_3_0(w[1], w[12], w[10], pars->GC_50, pars->GC_58, amp[6]); 
  FFV2_3_0(w[13], w[5], w[10], pars->GC_50, pars->GC_58, amp[7]); 
  FFV1_0(w[1], w[15], w[7], pars->GC_1, amp[8]); 
  FFV1_0(w[16], w[5], w[7], pars->GC_1, amp[9]); 
  FFV2_3_0(w[1], w[15], w[10], pars->GC_50, pars->GC_58, amp[10]); 
  FFV2_3_0(w[16], w[5], w[10], pars->GC_50, pars->GC_58, amp[11]); 
  VVS1_0(w[14], w[10], w[17], pars->GC_81, amp[12]); 
  FFV1_0(w[3], w[19], w[18], pars->GC_3, amp[13]); 
  FFV1_0(w[20], w[2], w[18], pars->GC_3, amp[14]); 
  FFV2_4_0(w[3], w[19], w[21], pars->GC_50, pars->GC_59, amp[15]); 
  FFV2_4_0(w[20], w[2], w[21], pars->GC_50, pars->GC_59, amp[16]); 
  FFV1_0(w[3], w[22], w[18], pars->GC_3, amp[17]); 
  FFV1_0(w[23], w[2], w[18], pars->GC_3, amp[18]); 
  FFV2_4_0(w[3], w[22], w[21], pars->GC_50, pars->GC_59, amp[19]); 
  FFV2_4_0(w[23], w[2], w[21], pars->GC_50, pars->GC_59, amp[20]); 
  FFV1_0(w[24], w[4], w[18], pars->GC_2, amp[21]); 
  FFV1_0(w[25], w[4], w[7], pars->GC_2, amp[22]); 
  FFV1_0(w[24], w[4], w[26], pars->GC_11, amp[23]); 
  FFV1_0(w[27], w[4], w[7], pars->GC_2, amp[24]); 
  FFV2_5_0(w[24], w[4], w[21], pars->GC_51, pars->GC_58, amp[25]); 
  FFV1_0(w[28], w[4], w[7], pars->GC_2, amp[26]); 
  FFV1_0(w[29], w[4], w[18], pars->GC_2, amp[27]); 
  FFV2_5_0(w[25], w[4], w[10], pars->GC_51, pars->GC_58, amp[28]); 
  FFV1_0(w[29], w[4], w[26], pars->GC_11, amp[29]); 
  FFV2_5_0(w[27], w[4], w[10], pars->GC_51, pars->GC_58, amp[30]); 
  FFV2_5_0(w[29], w[4], w[21], pars->GC_51, pars->GC_58, amp[31]); 
  FFV2_5_0(w[28], w[4], w[10], pars->GC_51, pars->GC_58, amp[32]); 
  FFV1_0(w[31], w[32], w[7], pars->GC_1, amp[33]); 
  FFV1_0(w[33], w[30], w[7], pars->GC_1, amp[34]); 
  FFV2_3_0(w[31], w[32], w[10], pars->GC_50, pars->GC_58, amp[35]); 
  FFV2_3_0(w[33], w[30], w[10], pars->GC_50, pars->GC_58, amp[36]); 
  FFV1_0(w[31], w[34], w[7], pars->GC_1, amp[37]); 
  FFV1_0(w[35], w[30], w[7], pars->GC_1, amp[38]); 
  FFV2_3_0(w[31], w[34], w[10], pars->GC_50, pars->GC_58, amp[39]); 
  FFV2_3_0(w[35], w[30], w[10], pars->GC_50, pars->GC_58, amp[40]); 
  FFV1_0(w[31], w[36], w[7], pars->GC_1, amp[41]); 
  FFV1_0(w[37], w[30], w[7], pars->GC_1, amp[42]); 
  FFV2_3_0(w[31], w[36], w[10], pars->GC_50, pars->GC_58, amp[43]); 
  FFV2_3_0(w[37], w[30], w[10], pars->GC_50, pars->GC_58, amp[44]); 
  VVS1_0(w[14], w[10], w[38], pars->GC_81, amp[45]); 
  FFV1_0(w[3], w[19], w[39], pars->GC_3, amp[46]); 
  FFV1_0(w[20], w[2], w[39], pars->GC_3, amp[47]); 
  FFV2_4_0(w[3], w[19], w[40], pars->GC_50, pars->GC_59, amp[48]); 
  FFV2_4_0(w[20], w[2], w[40], pars->GC_50, pars->GC_59, amp[49]); 
  FFV1_0(w[3], w[22], w[39], pars->GC_3, amp[50]); 
  FFV1_0(w[23], w[2], w[39], pars->GC_3, amp[51]); 
  FFV2_4_0(w[3], w[22], w[40], pars->GC_50, pars->GC_59, amp[52]); 
  FFV2_4_0(w[23], w[2], w[40], pars->GC_50, pars->GC_59, amp[53]); 
  FFV1_0(w[24], w[4], w[39], pars->GC_2, amp[54]); 
  FFV1_0(w[41], w[4], w[7], pars->GC_2, amp[55]); 
  FFV1_0(w[24], w[4], w[42], pars->GC_11, amp[56]); 
  FFV1_0(w[43], w[4], w[7], pars->GC_2, amp[57]); 
  FFV2_5_0(w[24], w[4], w[40], pars->GC_51, pars->GC_58, amp[58]); 
  FFV1_0(w[44], w[4], w[7], pars->GC_2, amp[59]); 
  FFV1_0(w[29], w[4], w[39], pars->GC_2, amp[60]); 
  FFV2_5_0(w[41], w[4], w[10], pars->GC_51, pars->GC_58, amp[61]); 
  FFV1_0(w[29], w[4], w[42], pars->GC_11, amp[62]); 
  FFV2_5_0(w[43], w[4], w[10], pars->GC_51, pars->GC_58, amp[63]); 
  FFV2_5_0(w[29], w[4], w[40], pars->GC_51, pars->GC_58, amp[64]); 
  FFV2_5_0(w[44], w[4], w[10], pars->GC_51, pars->GC_58, amp[65]); 
  FFV1_0(w[1], w[46], w[7], pars->GC_1, amp[66]); 
  FFV1_0(w[47], w[5], w[7], pars->GC_1, amp[67]); 
  FFV2_3_0(w[1], w[46], w[10], pars->GC_50, pars->GC_58, amp[68]); 
  FFV2_3_0(w[47], w[5], w[10], pars->GC_50, pars->GC_58, amp[69]); 
  FFV1_0(w[1], w[49], w[7], pars->GC_1, amp[70]); 
  FFV1_0(w[50], w[5], w[7], pars->GC_1, amp[71]); 
  FFV2_3_0(w[1], w[49], w[10], pars->GC_50, pars->GC_58, amp[72]); 
  FFV2_3_0(w[50], w[5], w[10], pars->GC_50, pars->GC_58, amp[73]); 
  VVS1_0(w[48], w[10], w[17], pars->GC_81, amp[74]); 
  FFV1_0(w[3], w[51], w[18], pars->GC_3, amp[75]); 
  FFV1_0(w[52], w[2], w[18], pars->GC_3, amp[76]); 
  FFV2_4_0(w[3], w[51], w[21], pars->GC_50, pars->GC_59, amp[77]); 
  FFV2_4_0(w[52], w[2], w[21], pars->GC_50, pars->GC_59, amp[78]); 
  FFV1_0(w[3], w[53], w[18], pars->GC_3, amp[79]); 
  FFV1_0(w[54], w[2], w[18], pars->GC_3, amp[80]); 
  FFV2_4_0(w[3], w[53], w[21], pars->GC_50, pars->GC_59, amp[81]); 
  FFV2_4_0(w[54], w[2], w[21], pars->GC_50, pars->GC_59, amp[82]); 
  FFV1_0(w[55], w[4], w[18], pars->GC_1, amp[83]); 
  FFV1_0(w[56], w[4], w[7], pars->GC_1, amp[84]); 
  FFV1_0(w[55], w[4], w[26], pars->GC_11, amp[85]); 
  FFV1_0(w[27], w[4], w[7], pars->GC_1, amp[86]); 
  FFV2_3_0(w[55], w[4], w[21], pars->GC_50, pars->GC_58, amp[87]); 
  FFV1_0(w[57], w[4], w[7], pars->GC_1, amp[88]); 
  FFV1_0(w[58], w[4], w[18], pars->GC_1, amp[89]); 
  FFV2_3_0(w[56], w[4], w[10], pars->GC_50, pars->GC_58, amp[90]); 
  FFV1_0(w[58], w[4], w[26], pars->GC_11, amp[91]); 
  FFV2_3_0(w[27], w[4], w[10], pars->GC_50, pars->GC_58, amp[92]); 
  FFV2_3_0(w[58], w[4], w[21], pars->GC_50, pars->GC_58, amp[93]); 
  FFV2_3_0(w[57], w[4], w[10], pars->GC_50, pars->GC_58, amp[94]); 
  FFV1_0(w[31], w[59], w[7], pars->GC_1, amp[95]); 
  FFV1_0(w[60], w[30], w[7], pars->GC_1, amp[96]); 
  FFV2_3_0(w[31], w[59], w[10], pars->GC_50, pars->GC_58, amp[97]); 
  FFV2_3_0(w[60], w[30], w[10], pars->GC_50, pars->GC_58, amp[98]); 
  FFV1_0(w[31], w[34], w[7], pars->GC_1, amp[99]); 
  FFV1_0(w[35], w[30], w[7], pars->GC_1, amp[100]); 
  FFV2_3_0(w[31], w[34], w[10], pars->GC_50, pars->GC_58, amp[101]); 
  FFV2_3_0(w[35], w[30], w[10], pars->GC_50, pars->GC_58, amp[102]); 
  FFV1_0(w[31], w[61], w[7], pars->GC_1, amp[103]); 
  FFV1_0(w[62], w[30], w[7], pars->GC_1, amp[104]); 
  FFV2_3_0(w[31], w[61], w[10], pars->GC_50, pars->GC_58, amp[105]); 
  FFV2_3_0(w[62], w[30], w[10], pars->GC_50, pars->GC_58, amp[106]); 
  VVS1_0(w[48], w[10], w[38], pars->GC_81, amp[107]); 
  FFV1_0(w[3], w[51], w[39], pars->GC_3, amp[108]); 
  FFV1_0(w[52], w[2], w[39], pars->GC_3, amp[109]); 
  FFV2_4_0(w[3], w[51], w[40], pars->GC_50, pars->GC_59, amp[110]); 
  FFV2_4_0(w[52], w[2], w[40], pars->GC_50, pars->GC_59, amp[111]); 
  FFV1_0(w[3], w[53], w[39], pars->GC_3, amp[112]); 
  FFV1_0(w[54], w[2], w[39], pars->GC_3, amp[113]); 
  FFV2_4_0(w[3], w[53], w[40], pars->GC_50, pars->GC_59, amp[114]); 
  FFV2_4_0(w[54], w[2], w[40], pars->GC_50, pars->GC_59, amp[115]); 
  FFV1_0(w[55], w[4], w[39], pars->GC_1, amp[116]); 
  FFV1_0(w[63], w[4], w[7], pars->GC_1, amp[117]); 
  FFV1_0(w[55], w[4], w[42], pars->GC_11, amp[118]); 
  FFV1_0(w[43], w[4], w[7], pars->GC_1, amp[119]); 
  FFV2_3_0(w[55], w[4], w[40], pars->GC_50, pars->GC_58, amp[120]); 
  FFV1_0(w[64], w[4], w[7], pars->GC_1, amp[121]); 
  FFV1_0(w[58], w[4], w[39], pars->GC_1, amp[122]); 
  FFV2_3_0(w[63], w[4], w[10], pars->GC_50, pars->GC_58, amp[123]); 
  FFV1_0(w[58], w[4], w[42], pars->GC_11, amp[124]); 
  FFV2_3_0(w[43], w[4], w[10], pars->GC_50, pars->GC_58, amp[125]); 
  FFV2_3_0(w[58], w[4], w[40], pars->GC_50, pars->GC_58, amp[126]); 
  FFV2_3_0(w[64], w[4], w[10], pars->GC_50, pars->GC_58, amp[127]); 
  FFV1_0(w[1], w[68], w[7], pars->GC_1, amp[128]); 
  FFV1_0(w[69], w[5], w[7], pars->GC_1, amp[129]); 
  FFV2_3_0(w[1], w[68], w[10], pars->GC_50, pars->GC_58, amp[130]); 
  FFV2_3_0(w[69], w[5], w[10], pars->GC_50, pars->GC_58, amp[131]); 
  FFV1_0(w[1], w[71], w[7], pars->GC_1, amp[132]); 
  FFV1_0(w[72], w[5], w[7], pars->GC_1, amp[133]); 
  FFV2_3_0(w[1], w[71], w[10], pars->GC_50, pars->GC_58, amp[134]); 
  FFV2_3_0(w[72], w[5], w[10], pars->GC_50, pars->GC_58, amp[135]); 
  FFV1_0(w[1], w[74], w[7], pars->GC_1, amp[136]); 
  FFV1_0(w[75], w[5], w[7], pars->GC_1, amp[137]); 
  FFV2_3_0(w[1], w[74], w[10], pars->GC_50, pars->GC_58, amp[138]); 
  FFV2_3_0(w[75], w[5], w[10], pars->GC_50, pars->GC_58, amp[139]); 
  VVS1_0(w[73], w[10], w[17], pars->GC_81, amp[140]); 
  FFV1_0(w[3], w[76], w[18], pars->GC_3, amp[141]); 
  FFV1_0(w[77], w[2], w[18], pars->GC_3, amp[142]); 
  FFV2_4_0(w[3], w[76], w[21], pars->GC_50, pars->GC_59, amp[143]); 
  FFV2_4_0(w[77], w[2], w[21], pars->GC_50, pars->GC_59, amp[144]); 
  FFV1_0(w[3], w[78], w[18], pars->GC_3, amp[145]); 
  FFV1_0(w[79], w[2], w[18], pars->GC_3, amp[146]); 
  FFV2_4_0(w[3], w[78], w[21], pars->GC_50, pars->GC_59, amp[147]); 
  FFV2_4_0(w[79], w[2], w[21], pars->GC_50, pars->GC_59, amp[148]); 
  FFV1_0(w[80], w[65], w[18], pars->GC_2, amp[149]); 
  FFV1_0(w[81], w[65], w[7], pars->GC_2, amp[150]); 
  FFV1_0(w[80], w[65], w[26], pars->GC_11, amp[151]); 
  FFV1_0(w[82], w[65], w[7], pars->GC_2, amp[152]); 
  FFV2_5_0(w[80], w[65], w[21], pars->GC_51, pars->GC_58, amp[153]); 
  FFV1_0(w[83], w[65], w[7], pars->GC_2, amp[154]); 
  FFV1_0(w[84], w[65], w[18], pars->GC_2, amp[155]); 
  FFV2_5_0(w[81], w[65], w[10], pars->GC_51, pars->GC_58, amp[156]); 
  FFV1_0(w[84], w[65], w[26], pars->GC_11, amp[157]); 
  FFV2_5_0(w[82], w[65], w[10], pars->GC_51, pars->GC_58, amp[158]); 
  FFV2_5_0(w[84], w[65], w[21], pars->GC_51, pars->GC_58, amp[159]); 
  FFV2_5_0(w[83], w[65], w[10], pars->GC_51, pars->GC_58, amp[160]); 
  FFV1_0(w[31], w[85], w[7], pars->GC_1, amp[161]); 
  FFV1_0(w[86], w[30], w[7], pars->GC_1, amp[162]); 
  FFV2_3_0(w[31], w[85], w[10], pars->GC_50, pars->GC_58, amp[163]); 
  FFV2_3_0(w[86], w[30], w[10], pars->GC_50, pars->GC_58, amp[164]); 
  FFV1_0(w[31], w[87], w[7], pars->GC_1, amp[165]); 
  FFV1_0(w[88], w[30], w[7], pars->GC_1, amp[166]); 
  FFV2_3_0(w[31], w[87], w[10], pars->GC_50, pars->GC_58, amp[167]); 
  FFV2_3_0(w[88], w[30], w[10], pars->GC_50, pars->GC_58, amp[168]); 
  FFV1_0(w[31], w[89], w[7], pars->GC_1, amp[169]); 
  FFV1_0(w[90], w[30], w[7], pars->GC_1, amp[170]); 
  FFV2_3_0(w[31], w[89], w[10], pars->GC_50, pars->GC_58, amp[171]); 
  FFV2_3_0(w[90], w[30], w[10], pars->GC_50, pars->GC_58, amp[172]); 
  VVS1_0(w[73], w[10], w[38], pars->GC_81, amp[173]); 
  FFV1_0(w[3], w[76], w[39], pars->GC_3, amp[174]); 
  FFV1_0(w[77], w[2], w[39], pars->GC_3, amp[175]); 
  FFV2_4_0(w[3], w[76], w[40], pars->GC_50, pars->GC_59, amp[176]); 
  FFV2_4_0(w[77], w[2], w[40], pars->GC_50, pars->GC_59, amp[177]); 
  FFV1_0(w[3], w[78], w[39], pars->GC_3, amp[178]); 
  FFV1_0(w[79], w[2], w[39], pars->GC_3, amp[179]); 
  FFV2_4_0(w[3], w[78], w[40], pars->GC_50, pars->GC_59, amp[180]); 
  FFV2_4_0(w[79], w[2], w[40], pars->GC_50, pars->GC_59, amp[181]); 
  FFV1_0(w[80], w[65], w[39], pars->GC_2, amp[182]); 
  FFV1_0(w[91], w[65], w[7], pars->GC_2, amp[183]); 
  FFV1_0(w[80], w[65], w[42], pars->GC_11, amp[184]); 
  FFV1_0(w[92], w[65], w[7], pars->GC_2, amp[185]); 
  FFV2_5_0(w[80], w[65], w[40], pars->GC_51, pars->GC_58, amp[186]); 
  FFV1_0(w[93], w[65], w[7], pars->GC_2, amp[187]); 
  FFV1_0(w[84], w[65], w[39], pars->GC_2, amp[188]); 
  FFV2_5_0(w[91], w[65], w[10], pars->GC_51, pars->GC_58, amp[189]); 
  FFV1_0(w[84], w[65], w[42], pars->GC_11, amp[190]); 
  FFV2_5_0(w[92], w[65], w[10], pars->GC_51, pars->GC_58, amp[191]); 
  FFV2_5_0(w[84], w[65], w[40], pars->GC_51, pars->GC_58, amp[192]); 
  FFV2_5_0(w[93], w[65], w[10], pars->GC_51, pars->GC_58, amp[193]); 
  FFV1_0(w[1], w[95], w[7], pars->GC_1, amp[194]); 
  FFV1_0(w[96], w[5], w[7], pars->GC_1, amp[195]); 
  FFV2_3_0(w[1], w[95], w[10], pars->GC_50, pars->GC_58, amp[196]); 
  FFV2_3_0(w[96], w[5], w[10], pars->GC_50, pars->GC_58, amp[197]); 
  FFV1_0(w[1], w[71], w[7], pars->GC_1, amp[198]); 
  FFV1_0(w[72], w[5], w[7], pars->GC_1, amp[199]); 
  FFV2_3_0(w[1], w[71], w[10], pars->GC_50, pars->GC_58, amp[200]); 
  FFV2_3_0(w[72], w[5], w[10], pars->GC_50, pars->GC_58, amp[201]); 
  FFV1_0(w[1], w[98], w[7], pars->GC_1, amp[202]); 
  FFV1_0(w[99], w[5], w[7], pars->GC_1, amp[203]); 
  FFV2_3_0(w[1], w[98], w[10], pars->GC_50, pars->GC_58, amp[204]); 
  FFV2_3_0(w[99], w[5], w[10], pars->GC_50, pars->GC_58, amp[205]); 
  VVS1_0(w[97], w[10], w[17], pars->GC_81, amp[206]); 
  FFV1_0(w[3], w[100], w[18], pars->GC_3, amp[207]); 
  FFV1_0(w[101], w[2], w[18], pars->GC_3, amp[208]); 
  FFV2_4_0(w[3], w[100], w[21], pars->GC_50, pars->GC_59, amp[209]); 
  FFV2_4_0(w[101], w[2], w[21], pars->GC_50, pars->GC_59, amp[210]); 
  FFV1_0(w[3], w[102], w[18], pars->GC_3, amp[211]); 
  FFV1_0(w[103], w[2], w[18], pars->GC_3, amp[212]); 
  FFV2_4_0(w[3], w[102], w[21], pars->GC_50, pars->GC_59, amp[213]); 
  FFV2_4_0(w[103], w[2], w[21], pars->GC_50, pars->GC_59, amp[214]); 
  FFV1_0(w[104], w[65], w[18], pars->GC_1, amp[215]); 
  FFV1_0(w[105], w[65], w[7], pars->GC_1, amp[216]); 
  FFV1_0(w[104], w[65], w[26], pars->GC_11, amp[217]); 
  FFV1_0(w[82], w[65], w[7], pars->GC_1, amp[218]); 
  FFV2_3_0(w[104], w[65], w[21], pars->GC_50, pars->GC_58, amp[219]); 
  FFV1_0(w[106], w[65], w[7], pars->GC_1, amp[220]); 
  FFV1_0(w[107], w[65], w[18], pars->GC_1, amp[221]); 
  FFV2_3_0(w[105], w[65], w[10], pars->GC_50, pars->GC_58, amp[222]); 
  FFV1_0(w[107], w[65], w[26], pars->GC_11, amp[223]); 
  FFV2_3_0(w[82], w[65], w[10], pars->GC_50, pars->GC_58, amp[224]); 
  FFV2_3_0(w[107], w[65], w[21], pars->GC_50, pars->GC_58, amp[225]); 
  FFV2_3_0(w[106], w[65], w[10], pars->GC_50, pars->GC_58, amp[226]); 
  FFV1_0(w[31], w[108], w[7], pars->GC_1, amp[227]); 
  FFV1_0(w[109], w[30], w[7], pars->GC_1, amp[228]); 
  FFV2_3_0(w[31], w[108], w[10], pars->GC_50, pars->GC_58, amp[229]); 
  FFV2_3_0(w[109], w[30], w[10], pars->GC_50, pars->GC_58, amp[230]); 
  FFV1_0(w[31], w[87], w[7], pars->GC_1, amp[231]); 
  FFV1_0(w[88], w[30], w[7], pars->GC_1, amp[232]); 
  FFV2_3_0(w[31], w[87], w[10], pars->GC_50, pars->GC_58, amp[233]); 
  FFV2_3_0(w[88], w[30], w[10], pars->GC_50, pars->GC_58, amp[234]); 
  FFV1_0(w[31], w[110], w[7], pars->GC_1, amp[235]); 
  FFV1_0(w[111], w[30], w[7], pars->GC_1, amp[236]); 
  FFV2_3_0(w[31], w[110], w[10], pars->GC_50, pars->GC_58, amp[237]); 
  FFV2_3_0(w[111], w[30], w[10], pars->GC_50, pars->GC_58, amp[238]); 
  VVS1_0(w[97], w[10], w[38], pars->GC_81, amp[239]); 
  FFV1_0(w[3], w[100], w[39], pars->GC_3, amp[240]); 
  FFV1_0(w[101], w[2], w[39], pars->GC_3, amp[241]); 
  FFV2_4_0(w[3], w[100], w[40], pars->GC_50, pars->GC_59, amp[242]); 
  FFV2_4_0(w[101], w[2], w[40], pars->GC_50, pars->GC_59, amp[243]); 
  FFV1_0(w[3], w[102], w[39], pars->GC_3, amp[244]); 
  FFV1_0(w[103], w[2], w[39], pars->GC_3, amp[245]); 
  FFV2_4_0(w[3], w[102], w[40], pars->GC_50, pars->GC_59, amp[246]); 
  FFV2_4_0(w[103], w[2], w[40], pars->GC_50, pars->GC_59, amp[247]); 
  FFV1_0(w[104], w[65], w[39], pars->GC_1, amp[248]); 
  FFV1_0(w[112], w[65], w[7], pars->GC_1, amp[249]); 
  FFV1_0(w[104], w[65], w[42], pars->GC_11, amp[250]); 
  FFV1_0(w[92], w[65], w[7], pars->GC_1, amp[251]); 
  FFV2_3_0(w[104], w[65], w[40], pars->GC_50, pars->GC_58, amp[252]); 
  FFV1_0(w[113], w[65], w[7], pars->GC_1, amp[253]); 
  FFV1_0(w[107], w[65], w[39], pars->GC_1, amp[254]); 
  FFV2_3_0(w[112], w[65], w[10], pars->GC_50, pars->GC_58, amp[255]); 
  FFV1_0(w[107], w[65], w[42], pars->GC_11, amp[256]); 
  FFV2_3_0(w[92], w[65], w[10], pars->GC_50, pars->GC_58, amp[257]); 
  FFV2_3_0(w[107], w[65], w[40], pars->GC_50, pars->GC_58, amp[258]); 
  FFV2_3_0(w[113], w[65], w[10], pars->GC_50, pars->GC_58, amp[259]); 
  FFV2_3_0(w[1], w[8], w[114], pars->GC_50, pars->GC_58, amp[260]); 
  FFV2_3_0(w[9], w[5], w[114], pars->GC_50, pars->GC_58, amp[261]); 
  FFV2_3_0(w[1], w[12], w[114], pars->GC_50, pars->GC_58, amp[262]); 
  FFV2_3_0(w[13], w[5], w[114], pars->GC_50, pars->GC_58, amp[263]); 
  FFV2_3_0(w[1], w[15], w[114], pars->GC_50, pars->GC_58, amp[264]); 
  FFV2_3_0(w[16], w[5], w[114], pars->GC_50, pars->GC_58, amp[265]); 
  VVS1_0(w[14], w[114], w[17], pars->GC_81, amp[266]); 
  FFV2_0(w[3], w[115], w[21], pars->GC_62, amp[267]); 
  FFV2_0(w[116], w[2], w[21], pars->GC_62, amp[268]); 
  FFV1_0(w[117], w[4], w[18], pars->GC_2, amp[269]); 
  FFV2_5_0(w[25], w[4], w[114], pars->GC_51, pars->GC_58, amp[270]); 
  FFV1_0(w[117], w[4], w[26], pars->GC_11, amp[271]); 
  FFV2_5_0(w[27], w[4], w[114], pars->GC_51, pars->GC_58, amp[272]); 
  FFV2_5_0(w[117], w[4], w[21], pars->GC_51, pars->GC_58, amp[273]); 
  FFV2_5_0(w[28], w[4], w[114], pars->GC_51, pars->GC_58, amp[274]); 
  FFV2_3_0(w[31], w[32], w[114], pars->GC_50, pars->GC_58, amp[275]); 
  FFV2_3_0(w[33], w[30], w[114], pars->GC_50, pars->GC_58, amp[276]); 
  FFV2_3_0(w[31], w[34], w[114], pars->GC_50, pars->GC_58, amp[277]); 
  FFV2_3_0(w[35], w[30], w[114], pars->GC_50, pars->GC_58, amp[278]); 
  FFV2_3_0(w[31], w[36], w[114], pars->GC_50, pars->GC_58, amp[279]); 
  FFV2_3_0(w[37], w[30], w[114], pars->GC_50, pars->GC_58, amp[280]); 
  VVS1_0(w[14], w[114], w[38], pars->GC_81, amp[281]); 
  FFV2_0(w[3], w[115], w[40], pars->GC_62, amp[282]); 
  FFV2_0(w[116], w[2], w[40], pars->GC_62, amp[283]); 
  FFV1_0(w[117], w[4], w[39], pars->GC_2, amp[284]); 
  FFV2_5_0(w[41], w[4], w[114], pars->GC_51, pars->GC_58, amp[285]); 
  FFV1_0(w[117], w[4], w[42], pars->GC_11, amp[286]); 
  FFV2_5_0(w[43], w[4], w[114], pars->GC_51, pars->GC_58, amp[287]); 
  FFV2_5_0(w[117], w[4], w[40], pars->GC_51, pars->GC_58, amp[288]); 
  FFV2_5_0(w[44], w[4], w[114], pars->GC_51, pars->GC_58, amp[289]); 
  FFV2_3_0(w[1], w[46], w[114], pars->GC_50, pars->GC_58, amp[290]); 
  FFV2_3_0(w[47], w[5], w[114], pars->GC_50, pars->GC_58, amp[291]); 
  FFV2_3_0(w[1], w[12], w[114], pars->GC_50, pars->GC_58, amp[292]); 
  FFV2_3_0(w[13], w[5], w[114], pars->GC_50, pars->GC_58, amp[293]); 
  FFV2_3_0(w[1], w[49], w[114], pars->GC_50, pars->GC_58, amp[294]); 
  FFV2_3_0(w[50], w[5], w[114], pars->GC_50, pars->GC_58, amp[295]); 
  VVS1_0(w[48], w[114], w[17], pars->GC_81, amp[296]); 
  FFV2_0(w[3], w[118], w[21], pars->GC_62, amp[297]); 
  FFV2_0(w[119], w[2], w[21], pars->GC_62, amp[298]); 
  FFV1_0(w[120], w[4], w[18], pars->GC_1, amp[299]); 
  FFV2_3_0(w[56], w[4], w[114], pars->GC_50, pars->GC_58, amp[300]); 
  FFV1_0(w[120], w[4], w[26], pars->GC_11, amp[301]); 
  FFV2_3_0(w[27], w[4], w[114], pars->GC_50, pars->GC_58, amp[302]); 
  FFV2_3_0(w[120], w[4], w[21], pars->GC_50, pars->GC_58, amp[303]); 
  FFV2_3_0(w[57], w[4], w[114], pars->GC_50, pars->GC_58, amp[304]); 
  FFV2_3_0(w[31], w[59], w[114], pars->GC_50, pars->GC_58, amp[305]); 
  FFV2_3_0(w[60], w[30], w[114], pars->GC_50, pars->GC_58, amp[306]); 
  FFV2_3_0(w[31], w[34], w[114], pars->GC_50, pars->GC_58, amp[307]); 
  FFV2_3_0(w[35], w[30], w[114], pars->GC_50, pars->GC_58, amp[308]); 
  FFV2_3_0(w[31], w[61], w[114], pars->GC_50, pars->GC_58, amp[309]); 
  FFV2_3_0(w[62], w[30], w[114], pars->GC_50, pars->GC_58, amp[310]); 
  VVS1_0(w[48], w[114], w[38], pars->GC_81, amp[311]); 
  FFV2_0(w[3], w[118], w[40], pars->GC_62, amp[312]); 
  FFV2_0(w[119], w[2], w[40], pars->GC_62, amp[313]); 
  FFV1_0(w[120], w[4], w[39], pars->GC_1, amp[314]); 
  FFV2_3_0(w[63], w[4], w[114], pars->GC_50, pars->GC_58, amp[315]); 
  FFV1_0(w[120], w[4], w[42], pars->GC_11, amp[316]); 
  FFV2_3_0(w[43], w[4], w[114], pars->GC_50, pars->GC_58, amp[317]); 
  FFV2_3_0(w[120], w[4], w[40], pars->GC_50, pars->GC_58, amp[318]); 
  FFV2_3_0(w[64], w[4], w[114], pars->GC_50, pars->GC_58, amp[319]); 
  FFV2_3_0(w[1], w[68], w[114], pars->GC_50, pars->GC_58, amp[320]); 
  FFV2_3_0(w[69], w[5], w[114], pars->GC_50, pars->GC_58, amp[321]); 
  FFV2_3_0(w[1], w[71], w[114], pars->GC_50, pars->GC_58, amp[322]); 
  FFV2_3_0(w[72], w[5], w[114], pars->GC_50, pars->GC_58, amp[323]); 
  FFV2_3_0(w[1], w[74], w[114], pars->GC_50, pars->GC_58, amp[324]); 
  FFV2_3_0(w[75], w[5], w[114], pars->GC_50, pars->GC_58, amp[325]); 
  VVS1_0(w[73], w[114], w[17], pars->GC_81, amp[326]); 
  FFV2_0(w[3], w[121], w[21], pars->GC_62, amp[327]); 
  FFV2_0(w[122], w[2], w[21], pars->GC_62, amp[328]); 
  FFV1_0(w[123], w[65], w[18], pars->GC_2, amp[329]); 
  FFV2_5_0(w[81], w[65], w[114], pars->GC_51, pars->GC_58, amp[330]); 
  FFV1_0(w[123], w[65], w[26], pars->GC_11, amp[331]); 
  FFV2_5_0(w[82], w[65], w[114], pars->GC_51, pars->GC_58, amp[332]); 
  FFV2_5_0(w[123], w[65], w[21], pars->GC_51, pars->GC_58, amp[333]); 
  FFV2_5_0(w[83], w[65], w[114], pars->GC_51, pars->GC_58, amp[334]); 
  FFV2_3_0(w[31], w[85], w[114], pars->GC_50, pars->GC_58, amp[335]); 
  FFV2_3_0(w[86], w[30], w[114], pars->GC_50, pars->GC_58, amp[336]); 
  FFV2_3_0(w[31], w[87], w[114], pars->GC_50, pars->GC_58, amp[337]); 
  FFV2_3_0(w[88], w[30], w[114], pars->GC_50, pars->GC_58, amp[338]); 
  FFV2_3_0(w[31], w[89], w[114], pars->GC_50, pars->GC_58, amp[339]); 
  FFV2_3_0(w[90], w[30], w[114], pars->GC_50, pars->GC_58, amp[340]); 
  VVS1_0(w[73], w[114], w[38], pars->GC_81, amp[341]); 
  FFV2_0(w[3], w[121], w[40], pars->GC_62, amp[342]); 
  FFV2_0(w[122], w[2], w[40], pars->GC_62, amp[343]); 
  FFV1_0(w[123], w[65], w[39], pars->GC_2, amp[344]); 
  FFV2_5_0(w[91], w[65], w[114], pars->GC_51, pars->GC_58, amp[345]); 
  FFV1_0(w[123], w[65], w[42], pars->GC_11, amp[346]); 
  FFV2_5_0(w[92], w[65], w[114], pars->GC_51, pars->GC_58, amp[347]); 
  FFV2_5_0(w[123], w[65], w[40], pars->GC_51, pars->GC_58, amp[348]); 
  FFV2_5_0(w[93], w[65], w[114], pars->GC_51, pars->GC_58, amp[349]); 
  FFV2_3_0(w[1], w[95], w[114], pars->GC_50, pars->GC_58, amp[350]); 
  FFV2_3_0(w[96], w[5], w[114], pars->GC_50, pars->GC_58, amp[351]); 
  FFV2_3_0(w[1], w[71], w[114], pars->GC_50, pars->GC_58, amp[352]); 
  FFV2_3_0(w[72], w[5], w[114], pars->GC_50, pars->GC_58, amp[353]); 
  FFV2_3_0(w[1], w[98], w[114], pars->GC_50, pars->GC_58, amp[354]); 
  FFV2_3_0(w[99], w[5], w[114], pars->GC_50, pars->GC_58, amp[355]); 
  VVS1_0(w[97], w[114], w[17], pars->GC_81, amp[356]); 
  FFV2_0(w[3], w[124], w[21], pars->GC_62, amp[357]); 
  FFV2_0(w[125], w[2], w[21], pars->GC_62, amp[358]); 
  FFV1_0(w[126], w[65], w[18], pars->GC_1, amp[359]); 
  FFV2_3_0(w[105], w[65], w[114], pars->GC_50, pars->GC_58, amp[360]); 
  FFV1_0(w[126], w[65], w[26], pars->GC_11, amp[361]); 
  FFV2_3_0(w[82], w[65], w[114], pars->GC_50, pars->GC_58, amp[362]); 
  FFV2_3_0(w[126], w[65], w[21], pars->GC_50, pars->GC_58, amp[363]); 
  FFV2_3_0(w[106], w[65], w[114], pars->GC_50, pars->GC_58, amp[364]); 
  FFV2_3_0(w[31], w[108], w[114], pars->GC_50, pars->GC_58, amp[365]); 
  FFV2_3_0(w[109], w[30], w[114], pars->GC_50, pars->GC_58, amp[366]); 
  FFV2_3_0(w[31], w[87], w[114], pars->GC_50, pars->GC_58, amp[367]); 
  FFV2_3_0(w[88], w[30], w[114], pars->GC_50, pars->GC_58, amp[368]); 
  FFV2_3_0(w[31], w[110], w[114], pars->GC_50, pars->GC_58, amp[369]); 
  FFV2_3_0(w[111], w[30], w[114], pars->GC_50, pars->GC_58, amp[370]); 
  VVS1_0(w[97], w[114], w[38], pars->GC_81, amp[371]); 
  FFV2_0(w[3], w[124], w[40], pars->GC_62, amp[372]); 
  FFV2_0(w[125], w[2], w[40], pars->GC_62, amp[373]); 
  FFV1_0(w[126], w[65], w[39], pars->GC_1, amp[374]); 
  FFV2_3_0(w[112], w[65], w[114], pars->GC_50, pars->GC_58, amp[375]); 
  FFV1_0(w[126], w[65], w[42], pars->GC_11, amp[376]); 
  FFV2_3_0(w[92], w[65], w[114], pars->GC_50, pars->GC_58, amp[377]); 
  FFV2_3_0(w[126], w[65], w[40], pars->GC_50, pars->GC_58, amp[378]); 
  FFV2_3_0(w[113], w[65], w[114], pars->GC_50, pars->GC_58, amp[379]); 
  FFV2_0(w[129], w[5], w[128], pars->GC_100, amp[380]); 
  VVV1_0(w[18], w[127], w[128], pars->GC_4, amp[381]); 
  VVS1_0(w[127], w[128], w[17], pars->GC_72, amp[382]); 
  VVV1_0(w[127], w[128], w[21], pars->GC_53, amp[383]); 
  FFV1_0(w[3], w[130], w[18], pars->GC_3, amp[384]); 
  FFV2_4_0(w[3], w[130], w[21], pars->GC_50, pars->GC_59, amp[385]); 
  FFV2_0(w[131], w[2], w[21], pars->GC_62, amp[386]); 
  FFV1_0(w[132], w[4], w[18], pars->GC_1, amp[387]); 
  FFV2_0(w[25], w[4], w[128], pars->GC_100, amp[388]); 
  FFV1_0(w[132], w[4], w[26], pars->GC_11, amp[389]); 
  FFV2_0(w[27], w[4], w[128], pars->GC_100, amp[390]); 
  FFV2_3_0(w[132], w[4], w[21], pars->GC_50, pars->GC_58, amp[391]); 
  FFV2_0(w[28], w[4], w[128], pars->GC_100, amp[392]); 
  FFV2_0(w[133], w[30], w[128], pars->GC_100, amp[393]); 
  VVV1_0(w[39], w[127], w[128], pars->GC_4, amp[394]); 
  VVS1_0(w[127], w[128], w[38], pars->GC_72, amp[395]); 
  VVV1_0(w[127], w[128], w[40], pars->GC_53, amp[396]); 
  FFV1_0(w[3], w[130], w[39], pars->GC_3, amp[397]); 
  FFV2_4_0(w[3], w[130], w[40], pars->GC_50, pars->GC_59, amp[398]); 
  FFV2_0(w[131], w[2], w[40], pars->GC_62, amp[399]); 
  FFV1_0(w[132], w[4], w[39], pars->GC_1, amp[400]); 
  FFV2_0(w[41], w[4], w[128], pars->GC_100, amp[401]); 
  FFV1_0(w[132], w[4], w[42], pars->GC_11, amp[402]); 
  FFV2_0(w[43], w[4], w[128], pars->GC_100, amp[403]); 
  FFV2_3_0(w[132], w[4], w[40], pars->GC_50, pars->GC_58, amp[404]); 
  FFV2_0(w[44], w[4], w[128], pars->GC_100, amp[405]); 
  FFV2_0(w[1], w[134], w[128], pars->GC_100, amp[406]); 
  VVV1_0(w[18], w[128], w[127], pars->GC_4, amp[407]); 
  VVS1_0(w[128], w[127], w[17], pars->GC_72, amp[408]); 
  VVV1_0(w[128], w[127], w[21], pars->GC_53, amp[409]); 
  FFV1_0(w[131], w[2], w[18], pars->GC_3, amp[410]); 
  FFV2_0(w[3], w[130], w[21], pars->GC_62, amp[411]); 
  FFV2_4_0(w[131], w[2], w[21], pars->GC_50, pars->GC_59, amp[412]); 
  FFV1_0(w[132], w[4], w[18], pars->GC_2, amp[413]); 
  FFV2_0(w[56], w[4], w[128], pars->GC_100, amp[414]); 
  FFV1_0(w[132], w[4], w[26], pars->GC_11, amp[415]); 
  FFV2_0(w[27], w[4], w[128], pars->GC_100, amp[416]); 
  FFV2_5_0(w[132], w[4], w[21], pars->GC_51, pars->GC_58, amp[417]); 
  FFV2_0(w[57], w[4], w[128], pars->GC_100, amp[418]); 
  FFV2_0(w[31], w[135], w[128], pars->GC_100, amp[419]); 
  VVV1_0(w[39], w[128], w[127], pars->GC_4, amp[420]); 
  VVS1_0(w[128], w[127], w[38], pars->GC_72, amp[421]); 
  VVV1_0(w[128], w[127], w[40], pars->GC_53, amp[422]); 
  FFV1_0(w[131], w[2], w[39], pars->GC_3, amp[423]); 
  FFV2_0(w[3], w[130], w[40], pars->GC_62, amp[424]); 
  FFV2_4_0(w[131], w[2], w[40], pars->GC_50, pars->GC_59, amp[425]); 
  FFV1_0(w[132], w[4], w[39], pars->GC_2, amp[426]); 
  FFV2_0(w[63], w[4], w[128], pars->GC_100, amp[427]); 
  FFV1_0(w[132], w[4], w[42], pars->GC_11, amp[428]); 
  FFV2_0(w[43], w[4], w[128], pars->GC_100, amp[429]); 
  FFV2_5_0(w[132], w[4], w[40], pars->GC_51, pars->GC_58, amp[430]); 
  FFV2_0(w[64], w[4], w[128], pars->GC_100, amp[431]); 
  FFV2_0(w[1], w[137], w[128], pars->GC_100, amp[432]); 
  VVV1_0(w[18], w[128], w[136], pars->GC_4, amp[433]); 
  VVS1_0(w[128], w[136], w[17], pars->GC_72, amp[434]); 
  VVV1_0(w[128], w[136], w[21], pars->GC_53, amp[435]); 
  FFV1_0(w[138], w[2], w[18], pars->GC_3, amp[436]); 
  FFV2_0(w[3], w[139], w[21], pars->GC_62, amp[437]); 
  FFV2_4_0(w[138], w[2], w[21], pars->GC_50, pars->GC_59, amp[438]); 
  FFV1_0(w[140], w[65], w[18], pars->GC_2, amp[439]); 
  FFV2_0(w[105], w[65], w[128], pars->GC_100, amp[440]); 
  FFV1_0(w[140], w[65], w[26], pars->GC_11, amp[441]); 
  FFV2_0(w[82], w[65], w[128], pars->GC_100, amp[442]); 
  FFV2_5_0(w[140], w[65], w[21], pars->GC_51, pars->GC_58, amp[443]); 
  FFV2_0(w[106], w[65], w[128], pars->GC_100, amp[444]); 
  FFV2_0(w[31], w[141], w[128], pars->GC_100, amp[445]); 
  VVV1_0(w[39], w[128], w[136], pars->GC_4, amp[446]); 
  VVS1_0(w[128], w[136], w[38], pars->GC_72, amp[447]); 
  VVV1_0(w[128], w[136], w[40], pars->GC_53, amp[448]); 
  FFV1_0(w[138], w[2], w[39], pars->GC_3, amp[449]); 
  FFV2_0(w[3], w[139], w[40], pars->GC_62, amp[450]); 
  FFV2_4_0(w[138], w[2], w[40], pars->GC_50, pars->GC_59, amp[451]); 
  FFV1_0(w[140], w[65], w[39], pars->GC_2, amp[452]); 
  FFV2_0(w[112], w[65], w[128], pars->GC_100, amp[453]); 
  FFV1_0(w[140], w[65], w[42], pars->GC_11, amp[454]); 
  FFV2_0(w[92], w[65], w[128], pars->GC_100, amp[455]); 
  FFV2_5_0(w[140], w[65], w[40], pars->GC_51, pars->GC_58, amp[456]); 
  FFV2_0(w[113], w[65], w[128], pars->GC_100, amp[457]); 
  FFV2_0(w[142], w[5], w[128], pars->GC_100, amp[458]); 
  VVV1_0(w[18], w[136], w[128], pars->GC_4, amp[459]); 
  VVS1_0(w[136], w[128], w[17], pars->GC_72, amp[460]); 
  VVV1_0(w[136], w[128], w[21], pars->GC_53, amp[461]); 
  FFV1_0(w[3], w[139], w[18], pars->GC_3, amp[462]); 
  FFV2_4_0(w[3], w[139], w[21], pars->GC_50, pars->GC_59, amp[463]); 
  FFV2_0(w[138], w[2], w[21], pars->GC_62, amp[464]); 
  FFV1_0(w[140], w[65], w[18], pars->GC_1, amp[465]); 
  FFV2_0(w[81], w[65], w[128], pars->GC_100, amp[466]); 
  FFV1_0(w[140], w[65], w[26], pars->GC_11, amp[467]); 
  FFV2_0(w[82], w[65], w[128], pars->GC_100, amp[468]); 
  FFV2_3_0(w[140], w[65], w[21], pars->GC_50, pars->GC_58, amp[469]); 
  FFV2_0(w[83], w[65], w[128], pars->GC_100, amp[470]); 
  FFV2_0(w[143], w[30], w[128], pars->GC_100, amp[471]); 
  VVV1_0(w[39], w[136], w[128], pars->GC_4, amp[472]); 
  VVS1_0(w[136], w[128], w[38], pars->GC_72, amp[473]); 
  VVV1_0(w[136], w[128], w[40], pars->GC_53, amp[474]); 
  FFV1_0(w[3], w[139], w[39], pars->GC_3, amp[475]); 
  FFV2_4_0(w[3], w[139], w[40], pars->GC_50, pars->GC_59, amp[476]); 
  FFV2_0(w[138], w[2], w[40], pars->GC_62, amp[477]); 
  FFV1_0(w[140], w[65], w[39], pars->GC_1, amp[478]); 
  FFV2_0(w[91], w[65], w[128], pars->GC_100, amp[479]); 
  FFV1_0(w[140], w[65], w[42], pars->GC_11, amp[480]); 
  FFV2_0(w[92], w[65], w[128], pars->GC_100, amp[481]); 
  FFV2_3_0(w[140], w[65], w[40], pars->GC_50, pars->GC_58, amp[482]); 
  FFV2_0(w[93], w[65], w[128], pars->GC_100, amp[483]); 


}
double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ub_emepub() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[0] + amp[1] + amp[2] + amp[3] - 1./6. * amp[4] - 1./6. *
      amp[5] - 1./6. * amp[6] - 1./6. * amp[7] + amp[8] + amp[9] + amp[10] +
      amp[11] + amp[12] + amp[13] + amp[14] + amp[15] + amp[16] + amp[17] +
      amp[18] + amp[19] + amp[20] + amp[21] + amp[22] - 1./6. * amp[23] - 1./6.
      * amp[24] + amp[25] + amp[26] + amp[27] + amp[28] - 1./6. * amp[29] -
      1./6. * amp[30] + amp[31] + amp[32];
  jamp[1] = +1./2. * (+amp[4] + amp[5] + amp[6] + amp[7] + amp[23] + amp[24] +
      amp[29] + amp[30]);

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ubx_emepubx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[37] - amp[38] - amp[39] - amp[40] - amp[56] -
      amp[57] - amp[62] - amp[63]);
  jamp[1] = -amp[33] - amp[34] - amp[35] - amp[36] + 1./6. * amp[37] + 1./6. *
      amp[38] + 1./6. * amp[39] + 1./6. * amp[40] - amp[41] - amp[42] - amp[43]
      - amp[44] - amp[45] - amp[46] - amp[47] - amp[48] - amp[49] - amp[50] -
      amp[51] - amp[52] - amp[53] - amp[54] - amp[55] + 1./6. * amp[56] + 1./6.
      * amp[57] - amp[58] - amp[59] - amp[60] - amp[61] + 1./6. * amp[62] +
      1./6. * amp[63] - amp[64] - amp[65];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_db_emepdb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[66] + amp[67] + amp[68] + amp[69] - 1./6. * amp[4] - 1./6. *
      amp[5] - 1./6. * amp[6] - 1./6. * amp[7] + amp[70] + amp[71] + amp[72] +
      amp[73] + amp[74] + amp[75] + amp[76] + amp[77] + amp[78] + amp[79] +
      amp[80] + amp[81] + amp[82] + amp[83] + amp[84] - 1./6. * amp[85] - 1./6.
      * amp[86] + amp[87] + amp[88] + amp[89] + amp[90] - 1./6. * amp[91] -
      1./6. * amp[92] + amp[93] + amp[94];
  jamp[1] = +1./2. * (+amp[4] + amp[5] + amp[6] + amp[7] + amp[85] + amp[86] +
      amp[91] + amp[92]);

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dbx_emepdbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[99] - amp[100] - amp[101] - amp[102] - amp[118] -
      amp[119] - amp[124] - amp[125]);
  jamp[1] = -amp[95] - amp[96] - amp[97] - amp[98] + 1./6. * amp[99] + 1./6. *
      amp[100] + 1./6. * amp[101] + 1./6. * amp[102] - amp[103] - amp[104] -
      amp[105] - amp[106] - amp[107] - amp[108] - amp[109] - amp[110] -
      amp[111] - amp[112] - amp[113] - amp[114] - amp[115] - amp[116] -
      amp[117] + 1./6. * amp[118] + 1./6. * amp[119] - amp[120] - amp[121] -
      amp[122] - amp[123] + 1./6. * amp[124] + 1./6. * amp[125] - amp[126] -
      amp[127];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxb_emepuxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[132] - amp[133] - amp[134] - amp[135] - amp[151] -
      amp[152] - amp[157] - amp[158]);
  jamp[1] = -amp[128] - amp[129] - amp[130] - amp[131] + 1./6. * amp[132] +
      1./6. * amp[133] + 1./6. * amp[134] + 1./6. * amp[135] - amp[136] -
      amp[137] - amp[138] - amp[139] - amp[140] - amp[141] - amp[142] -
      amp[143] - amp[144] - amp[145] - amp[146] - amp[147] - amp[148] -
      amp[149] - amp[150] + 1./6. * amp[151] + 1./6. * amp[152] - amp[153] -
      amp[154] - amp[155] - amp[156] + 1./6. * amp[157] + 1./6. * amp[158] -
      amp[159] - amp[160];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxbx_emepuxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[161] + amp[162] + amp[163] + amp[164] - 1./6. * amp[165] -
      1./6. * amp[166] - 1./6. * amp[167] - 1./6. * amp[168] + amp[169] +
      amp[170] + amp[171] + amp[172] + amp[173] + amp[174] + amp[175] +
      amp[176] + amp[177] + amp[178] + amp[179] + amp[180] + amp[181] +
      amp[182] + amp[183] - 1./6. * amp[184] - 1./6. * amp[185] + amp[186] +
      amp[187] + amp[188] + amp[189] - 1./6. * amp[190] - 1./6. * amp[191] +
      amp[192] + amp[193];
  jamp[1] = +1./2. * (+amp[165] + amp[166] + amp[167] + amp[168] + amp[184] +
      amp[185] + amp[190] + amp[191]);

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxb_emepdxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[198] - amp[199] - amp[200] - amp[201] - amp[217] -
      amp[218] - amp[223] - amp[224]);
  jamp[1] = -amp[194] - amp[195] - amp[196] - amp[197] + 1./6. * amp[198] +
      1./6. * amp[199] + 1./6. * amp[200] + 1./6. * amp[201] - amp[202] -
      amp[203] - amp[204] - amp[205] - amp[206] - amp[207] - amp[208] -
      amp[209] - amp[210] - amp[211] - amp[212] - amp[213] - amp[214] -
      amp[215] - amp[216] + 1./6. * amp[217] + 1./6. * amp[218] - amp[219] -
      amp[220] - amp[221] - amp[222] + 1./6. * amp[223] + 1./6. * amp[224] -
      amp[225] - amp[226];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxbx_emepdxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 33;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[227] + amp[228] + amp[229] + amp[230] - 1./6. * amp[231] -
      1./6. * amp[232] - 1./6. * amp[233] - 1./6. * amp[234] + amp[235] +
      amp[236] + amp[237] + amp[238] + amp[239] + amp[240] + amp[241] +
      amp[242] + amp[243] + amp[244] + amp[245] + amp[246] + amp[247] +
      amp[248] + amp[249] - 1./6. * amp[250] - 1./6. * amp[251] + amp[252] +
      amp[253] + amp[254] + amp[255] - 1./6. * amp[256] - 1./6. * amp[257] +
      amp[258] + amp[259];
  jamp[1] = +1./2. * (+amp[231] + amp[232] + amp[233] + amp[234] + amp[250] +
      amp[251] + amp[256] + amp[257]);

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ub_vevexub() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[260] + amp[261] - 1./6. * amp[262] - 1./6. * amp[263] +
      amp[264] + amp[265] + amp[266] + amp[267] + amp[268] + amp[269] +
      amp[270] - 1./6. * amp[271] - 1./6. * amp[272] + amp[273] + amp[274];
  jamp[1] = +1./2. * (+amp[262] + amp[263] + amp[271] + amp[272]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ubx_vevexubx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[277] - amp[278] - amp[286] - amp[287]); 
  jamp[1] = -amp[275] - amp[276] + 1./6. * amp[277] + 1./6. * amp[278] -
      amp[279] - amp[280] - amp[281] - amp[282] - amp[283] - amp[284] -
      amp[285] + 1./6. * amp[286] + 1./6. * amp[287] - amp[288] - amp[289];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_db_vevexdb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[290] + amp[291] - 1./6. * amp[292] - 1./6. * amp[293] +
      amp[294] + amp[295] + amp[296] + amp[297] + amp[298] + amp[299] +
      amp[300] - 1./6. * amp[301] - 1./6. * amp[302] + amp[303] + amp[304];
  jamp[1] = +1./2. * (+amp[292] + amp[293] + amp[301] + amp[302]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dbx_vevexdbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[307] - amp[308] - amp[316] - amp[317]); 
  jamp[1] = -amp[305] - amp[306] + 1./6. * amp[307] + 1./6. * amp[308] -
      amp[309] - amp[310] - amp[311] - amp[312] - amp[313] - amp[314] -
      amp[315] + 1./6. * amp[316] + 1./6. * amp[317] - amp[318] - amp[319];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxb_vevexuxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[322] - amp[323] - amp[331] - amp[332]); 
  jamp[1] = -amp[320] - amp[321] + 1./6. * amp[322] + 1./6. * amp[323] -
      amp[324] - amp[325] - amp[326] - amp[327] - amp[328] - amp[329] -
      amp[330] + 1./6. * amp[331] + 1./6. * amp[332] - amp[333] - amp[334];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxbx_vevexuxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[335] + amp[336] - 1./6. * amp[337] - 1./6. * amp[338] +
      amp[339] + amp[340] + amp[341] + amp[342] + amp[343] + amp[344] +
      amp[345] - 1./6. * amp[346] - 1./6. * amp[347] + amp[348] + amp[349];
  jamp[1] = +1./2. * (+amp[337] + amp[338] + amp[346] + amp[347]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxb_vevexdxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[352] - amp[353] - amp[361] - amp[362]); 
  jamp[1] = -amp[350] - amp[351] + 1./6. * amp[352] + 1./6. * amp[353] -
      amp[354] - amp[355] - amp[356] - amp[357] - amp[358] - amp[359] -
      amp[360] + 1./6. * amp[361] + 1./6. * amp[362] - amp[363] - amp[364];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxbx_vevexdxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 15;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[365] + amp[366] - 1./6. * amp[367] - 1./6. * amp[368] +
      amp[369] + amp[370] + amp[371] + amp[372] + amp[373] + amp[374] +
      amp[375] - 1./6. * amp[376] - 1./6. * amp[377] + amp[378] + amp[379];
  jamp[1] = +1./2. * (+amp[367] + amp[368] + amp[376] + amp[377]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ub_veepdb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[380] + amp[381] + amp[382] + amp[383] + amp[384] + amp[385] +
      amp[386] + amp[387] + amp[388] - 1./6. * amp[389] - 1./6. * amp[390] +
      amp[391] + amp[392];
  jamp[1] = +1./2. * (+amp[389] + amp[390]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_ubx_veepdbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[402] - amp[403]); 
  jamp[1] = -amp[393] - amp[394] - amp[395] - amp[396] - amp[397] - amp[398] -
      amp[399] - amp[400] - amp[401] + 1./6. * amp[402] + 1./6. * amp[403] -
      amp[404] - amp[405];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_db_emvexub() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[406] + amp[407] + amp[408] + amp[409] + amp[410] + amp[411] +
      amp[412] + amp[413] + amp[414] - 1./6. * amp[415] - 1./6. * amp[416] +
      amp[417] + amp[418];
  jamp[1] = +1./2. * (+amp[415] + amp[416]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dbx_emvexubx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[428] - amp[429]); 
  jamp[1] = -amp[419] - amp[420] - amp[421] - amp[422] - amp[423] - amp[424] -
      amp[425] - amp[426] - amp[427] + 1./6. * amp[428] + 1./6. * amp[429] -
      amp[430] - amp[431];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxb_emvexdxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[441] - amp[442]); 
  jamp[1] = -amp[432] - amp[433] - amp[434] - amp[435] - amp[436] - amp[437] -
      amp[438] - amp[439] - amp[440] + 1./6. * amp[441] + 1./6. * amp[442] -
      amp[443] - amp[444];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_uxbx_emvexdxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[445] + amp[446] + amp[447] + amp[448] + amp[449] + amp[450] +
      amp[451] + amp[452] + amp[453] - 1./6. * amp[454] - 1./6. * amp[455] +
      amp[456] + amp[457];
  jamp[1] = +1./2. * (+amp[454] + amp[455]); 

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxb_veepuxb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +1./2. * (-amp[467] - amp[468]); 
  jamp[1] = -amp[458] - amp[459] - amp[460] - amp[461] - amp[462] - amp[463] -
      amp[464] - amp[465] - amp[466] + 1./6. * amp[467] + 1./6. * amp[468] -
      amp[469] - amp[470];

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

double PY8MEs_R7_P8_sm_qb_llqb::matrix_7_dxbx_veepuxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 13;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[471] + amp[472] + amp[473] + amp[474] + amp[475] + amp[476] +
      amp[477] + amp[478] + amp[479] - 1./6. * amp[480] - 1./6. * amp[481] +
      amp[482] + amp[483];
  jamp[1] = +1./2. * (+amp[480] + amp[481]); 

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


}  // end namespace PY8MEs_namespace

