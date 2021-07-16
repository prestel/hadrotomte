//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R8_P40_sm_qb_zqb.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u b > z u b WEIGHTED<=99 @8
// Process: c b > z c b WEIGHTED<=99 @8
// Process: u b~ > z u b~ WEIGHTED<=99 @8
// Process: c b~ > z c b~ WEIGHTED<=99 @8
// Process: d b > z d b WEIGHTED<=99 @8
// Process: s b > z s b WEIGHTED<=99 @8
// Process: d b~ > z d b~ WEIGHTED<=99 @8
// Process: s b~ > z s b~ WEIGHTED<=99 @8
// Process: u~ b > z u~ b WEIGHTED<=99 @8
// Process: c~ b > z c~ b WEIGHTED<=99 @8
// Process: u~ b~ > z u~ b~ WEIGHTED<=99 @8
// Process: c~ b~ > z c~ b~ WEIGHTED<=99 @8
// Process: d~ b > z d~ b WEIGHTED<=99 @8
// Process: s~ b > z s~ b WEIGHTED<=99 @8
// Process: d~ b~ > z d~ b~ WEIGHTED<=99 @8
// Process: s~ b~ > z s~ b~ WEIGHTED<=99 @8

// Exception class
class PY8MEs_R8_P40_sm_qb_zqbException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R8_P40_sm_qb_zqb'."; 
  }
}
PY8MEs_R8_P40_sm_qb_zqb_exception; 

std::set<int> PY8MEs_R8_P40_sm_qb_zqb::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R8_P40_sm_qb_zqb::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R8_P40_sm_qb_zqb::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9, 9,
    9};
int PY8MEs_R8_P40_sm_qb_zqb::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4, 4, 4}; 
int PY8MEs_R8_P40_sm_qb_zqb::denom_iden[nprocesses] = {1, 1, 1, 1, 1, 1, 1, 1}; 

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R8_P40_sm_qb_zqb::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u b > z u b WEIGHTED<=99 @8
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

  // Color flows of process Process: u b~ > z u b~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d b > z d b WEIGHTED<=99 @8
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

  // Color flows of process Process: d b~ > z d b~ WEIGHTED<=99 @8
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

  // Color flows of process Process: u~ b > z u~ b WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: u~ b~ > z u~ b~ WEIGHTED<=99 @8
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

  // Color flows of process Process: d~ b > z d~ b WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[6].push_back(vec_int(createvector<int>
      (0)(1)(1)(0)(0)(0)(0)(2)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 
  // JAMP #1
  color_configs[6].push_back(vec_int(createvector<int>
      (0)(1)(2)(0)(0)(0)(0)(1)(2)(0)));
  jamp_nc_relative_power[6].push_back(0); 

  // Color flows of process Process: d~ b~ > z d~ b~ WEIGHTED<=99 @8
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[7].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[7].push_back(0); 
  // JAMP #1
  color_configs[7].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[7].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R8_P40_sm_qb_zqb::~PY8MEs_R8_P40_sm_qb_zqb() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R8_P40_sm_qb_zqb::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R8_P40_sm_qb_zqb::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R8_P40_sm_qb_zqb::getColorConfigs(int
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
int PY8MEs_R8_P40_sm_qb_zqb::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R8_P40_sm_qb_zqb::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
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
int PY8MEs_R8_P40_sm_qb_zqb::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R8_P40_sm_qb_zqb': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R8_P40_sm_qb_zqb::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R8_P40_sm_qb_zqb': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
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
int PY8MEs_R8_P40_sm_qb_zqb::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R8_P40_sm_qb_zqb': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
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
      " 'PY8MEs_R8_P40_sm_qb_zqb': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R8_P40_sm_qb_zqb::getAllResults(int
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
double PY8MEs_R8_P40_sm_qb_zqb::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
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
    " 'PY8MEs_R8_P40_sm_qb_zqb': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R8_P40_sm_qb_zqb::static_getPY8ME(vector<int>
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
  const int nprocs = 32; 
  const int proc_IDS[nprocs] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7,
      0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7};
  const int in_pdgs[nprocs][ninitial] = {{2, 5}, {4, 5}, {2, -5}, {4, -5}, {1,
      5}, {3, 5}, {1, -5}, {3, -5}, {-2, 5}, {-4, 5}, {-2, -5}, {-4, -5}, {-1,
      5}, {-3, 5}, {-1, -5}, {-3, -5}, {5, 2}, {5, 4}, {-5, 2}, {-5, 4}, {5,
      1}, {5, 3}, {-5, 1}, {-5, 3}, {5, -2}, {5, -4}, {-5, -2}, {-5, -4}, {5,
      -1}, {5, -3}, {-5, -1}, {-5, -3}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{23, 2, 5}, {23, 4, 5},
      {23, 2, -5}, {23, 4, -5}, {23, 1, 5}, {23, 3, 5}, {23, 1, -5}, {23, 3,
      -5}, {23, -2, 5}, {23, -4, 5}, {23, -2, -5}, {23, -4, -5}, {23, -1, 5},
      {23, -3, 5}, {23, -1, -5}, {23, -3, -5}, {23, 2, 5}, {23, 4, 5}, {23, 2,
      -5}, {23, 4, -5}, {23, 1, 5}, {23, 3, 5}, {23, 1, -5}, {23, 3, -5}, {23,
      -2, 5}, {23, -4, 5}, {23, -2, -5}, {23, -4, -5}, {23, -1, 5}, {23, -3,
      5}, {23, -1, -5}, {23, -3, -5}};

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
void PY8MEs_R8_P40_sm_qb_zqb::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R8_P40_sm_qb_zqb': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R8_P40_sm_qb_zqb::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R8_P40_sm_qb_zqb::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R8_P40_sm_qb_zqb::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R8_P40_sm_qb_zqb::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R8_P40_sm_qb_zqb::initProc() 
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
  jamp2 = vector < vec_double > (8); 
  jamp2[0] = vector<double> (2, 0.); 
  jamp2[1] = vector<double> (2, 0.); 
  jamp2[2] = vector<double> (2, 0.); 
  jamp2[3] = vector<double> (2, 0.); 
  jamp2[4] = vector<double> (2, 0.); 
  jamp2[5] = vector<double> (2, 0.); 
  jamp2[6] = vector<double> (2, 0.); 
  jamp2[7] = vector<double> (2, 0.); 
  all_results = vector < vec_vec_double > (8); 
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
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R8_P40_sm_qb_zqb::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->mdl_MB; 
  mME[2] = pars->mdl_MZ; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->mdl_MB; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R8_P40_sm_qb_zqb::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R8_P40_sm_qb_zqb::getMasses() 
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
void PY8MEs_R8_P40_sm_qb_zqb::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R8_P40_sm_qb_zqb': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R8_P40_sm_qb_zqb_exception; 
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

double PY8MEs_R8_P40_sm_qb_zqb::sigmaKin() 
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

    if (proc_ID == 0)
      t = matrix_8_ub_zub(); 
    if (proc_ID == 1)
      t = matrix_8_ubx_zubx(); 
    if (proc_ID == 2)
      t = matrix_8_db_zdb(); 
    if (proc_ID == 3)
      t = matrix_8_dbx_zdbx(); 
    if (proc_ID == 4)
      t = matrix_8_uxb_zuxb(); 
    if (proc_ID == 5)
      t = matrix_8_uxbx_zuxbx(); 
    if (proc_ID == 6)
      t = matrix_8_dxb_zdxb(); 
    if (proc_ID == 7)
      t = matrix_8_dxbx_zdxbx(); 

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

void PY8MEs_R8_P40_sm_qb_zqb::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  vxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  oxxxxx(p[perm[3]], mME[3], hel[3], +1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  FFV1P0_3(w[0], w[3], pars->GC_2, pars->ZERO, pars->ZERO, w[5]); 
  FFV2_3_1(w[4], w[2], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[6]);
  FFV1P0_3(w[0], w[3], pars->GC_11, pars->ZERO, pars->ZERO, w[7]); 
  FFV2_5_3(w[0], w[3], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[8]);
  FFV2_3_2(w[1], w[2], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[9]);
  FFS4_3(w[1], w[4], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[10]); 
  FFV2_5_2(w[0], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[11]);
  FFV1P0_3(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[12]); 
  FFV1P0_3(w[1], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[13]); 
  FFV2_3_3(w[1], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[14]);
  FFV2_5_1(w[3], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[15]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[16]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[17]); 
  FFV2_3_1(w[16], w[2], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[18]);
  FFV2_3_2(w[17], w[2], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[19]);
  FFS4_3(w[17], w[16], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[20]); 
  FFV1P0_3(w[17], w[16], pars->GC_1, pars->ZERO, pars->ZERO, w[21]); 
  FFV1P0_3(w[17], w[16], pars->GC_11, pars->ZERO, pars->ZERO, w[22]); 
  FFV2_3_3(w[17], w[16], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[23]);
  FFV1P0_3(w[0], w[3], pars->GC_1, pars->ZERO, pars->ZERO, w[24]); 
  FFV2_3_3(w[0], w[3], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[25]);
  FFV2_3_2(w[0], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[26]);
  FFV2_3_1(w[3], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[27]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[28]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[29]); 
  FFV1P0_3(w[29], w[28], pars->GC_2, pars->ZERO, pars->ZERO, w[30]); 
  FFV1P0_3(w[29], w[28], pars->GC_11, pars->ZERO, pars->ZERO, w[31]); 
  FFV2_5_3(w[29], w[28], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[32]);
  FFV2_5_2(w[29], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[33]);
  FFV2_5_1(w[28], w[2], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[34]);
  FFV1P0_3(w[29], w[28], pars->GC_1, pars->ZERO, pars->ZERO, w[35]); 
  FFV2_3_3(w[29], w[28], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[36]);
  FFV2_3_2(w[29], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[37]);
  FFV2_3_1(w[28], w[2], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[38]);

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[1], w[6], w[5], pars->GC_1, amp[0]); 
  FFV1_0(w[1], w[6], w[7], pars->GC_11, amp[1]); 
  FFV2_3_0(w[1], w[6], w[8], pars->GC_50, pars->GC_58, amp[2]); 
  FFV1_0(w[9], w[4], w[5], pars->GC_1, amp[3]); 
  FFV1_0(w[9], w[4], w[7], pars->GC_11, amp[4]); 
  FFV2_3_0(w[9], w[4], w[8], pars->GC_50, pars->GC_58, amp[5]); 
  VVS1_0(w[8], w[2], w[10], pars->GC_81, amp[6]); 
  FFV1_0(w[11], w[3], w[12], pars->GC_2, amp[7]); 
  FFV1_0(w[11], w[3], w[13], pars->GC_11, amp[8]); 
  FFV2_5_0(w[11], w[3], w[14], pars->GC_51, pars->GC_58, amp[9]); 
  FFV1_0(w[0], w[15], w[12], pars->GC_2, amp[10]); 
  FFV1_0(w[0], w[15], w[13], pars->GC_11, amp[11]); 
  FFV2_5_0(w[0], w[15], w[14], pars->GC_51, pars->GC_58, amp[12]); 
  FFV1_0(w[17], w[18], w[5], pars->GC_1, amp[13]); 
  FFV1_0(w[17], w[18], w[7], pars->GC_11, amp[14]); 
  FFV2_3_0(w[17], w[18], w[8], pars->GC_50, pars->GC_58, amp[15]); 
  FFV1_0(w[19], w[16], w[5], pars->GC_1, amp[16]); 
  FFV1_0(w[19], w[16], w[7], pars->GC_11, amp[17]); 
  FFV2_3_0(w[19], w[16], w[8], pars->GC_50, pars->GC_58, amp[18]); 
  VVS1_0(w[8], w[2], w[20], pars->GC_81, amp[19]); 
  FFV1_0(w[11], w[3], w[21], pars->GC_2, amp[20]); 
  FFV1_0(w[11], w[3], w[22], pars->GC_11, amp[21]); 
  FFV2_5_0(w[11], w[3], w[23], pars->GC_51, pars->GC_58, amp[22]); 
  FFV1_0(w[0], w[15], w[21], pars->GC_2, amp[23]); 
  FFV1_0(w[0], w[15], w[22], pars->GC_11, amp[24]); 
  FFV2_5_0(w[0], w[15], w[23], pars->GC_51, pars->GC_58, amp[25]); 
  FFV1_0(w[1], w[6], w[24], pars->GC_1, amp[26]); 
  FFV2_3_0(w[1], w[6], w[25], pars->GC_50, pars->GC_58, amp[27]); 
  FFV1_0(w[9], w[4], w[24], pars->GC_1, amp[28]); 
  FFV2_3_0(w[9], w[4], w[25], pars->GC_50, pars->GC_58, amp[29]); 
  VVS1_0(w[25], w[2], w[10], pars->GC_81, amp[30]); 
  FFV1_0(w[26], w[3], w[12], pars->GC_1, amp[31]); 
  FFV1_0(w[26], w[3], w[13], pars->GC_11, amp[32]); 
  FFV2_3_0(w[26], w[3], w[14], pars->GC_50, pars->GC_58, amp[33]); 
  FFV1_0(w[0], w[27], w[12], pars->GC_1, amp[34]); 
  FFV1_0(w[0], w[27], w[13], pars->GC_11, amp[35]); 
  FFV2_3_0(w[0], w[27], w[14], pars->GC_50, pars->GC_58, amp[36]); 
  FFV1_0(w[17], w[18], w[24], pars->GC_1, amp[37]); 
  FFV1_0(w[17], w[18], w[7], pars->GC_11, amp[38]); 
  FFV2_3_0(w[17], w[18], w[25], pars->GC_50, pars->GC_58, amp[39]); 
  FFV1_0(w[19], w[16], w[24], pars->GC_1, amp[40]); 
  FFV1_0(w[19], w[16], w[7], pars->GC_11, amp[41]); 
  FFV2_3_0(w[19], w[16], w[25], pars->GC_50, pars->GC_58, amp[42]); 
  VVS1_0(w[25], w[2], w[20], pars->GC_81, amp[43]); 
  FFV1_0(w[26], w[3], w[21], pars->GC_1, amp[44]); 
  FFV1_0(w[26], w[3], w[22], pars->GC_11, amp[45]); 
  FFV2_3_0(w[26], w[3], w[23], pars->GC_50, pars->GC_58, amp[46]); 
  FFV1_0(w[0], w[27], w[21], pars->GC_1, amp[47]); 
  FFV1_0(w[0], w[27], w[22], pars->GC_11, amp[48]); 
  FFV2_3_0(w[0], w[27], w[23], pars->GC_50, pars->GC_58, amp[49]); 
  FFV1_0(w[1], w[6], w[30], pars->GC_1, amp[50]); 
  FFV1_0(w[1], w[6], w[31], pars->GC_11, amp[51]); 
  FFV2_3_0(w[1], w[6], w[32], pars->GC_50, pars->GC_58, amp[52]); 
  FFV1_0(w[9], w[4], w[30], pars->GC_1, amp[53]); 
  FFV1_0(w[9], w[4], w[31], pars->GC_11, amp[54]); 
  FFV2_3_0(w[9], w[4], w[32], pars->GC_50, pars->GC_58, amp[55]); 
  VVS1_0(w[32], w[2], w[10], pars->GC_81, amp[56]); 
  FFV1_0(w[33], w[28], w[12], pars->GC_2, amp[57]); 
  FFV1_0(w[33], w[28], w[13], pars->GC_11, amp[58]); 
  FFV2_5_0(w[33], w[28], w[14], pars->GC_51, pars->GC_58, amp[59]); 
  FFV1_0(w[29], w[34], w[12], pars->GC_2, amp[60]); 
  FFV1_0(w[29], w[34], w[13], pars->GC_11, amp[61]); 
  FFV2_5_0(w[29], w[34], w[14], pars->GC_51, pars->GC_58, amp[62]); 
  FFV1_0(w[17], w[18], w[30], pars->GC_1, amp[63]); 
  FFV1_0(w[17], w[18], w[31], pars->GC_11, amp[64]); 
  FFV2_3_0(w[17], w[18], w[32], pars->GC_50, pars->GC_58, amp[65]); 
  FFV1_0(w[19], w[16], w[30], pars->GC_1, amp[66]); 
  FFV1_0(w[19], w[16], w[31], pars->GC_11, amp[67]); 
  FFV2_3_0(w[19], w[16], w[32], pars->GC_50, pars->GC_58, amp[68]); 
  VVS1_0(w[32], w[2], w[20], pars->GC_81, amp[69]); 
  FFV1_0(w[33], w[28], w[21], pars->GC_2, amp[70]); 
  FFV1_0(w[33], w[28], w[22], pars->GC_11, amp[71]); 
  FFV2_5_0(w[33], w[28], w[23], pars->GC_51, pars->GC_58, amp[72]); 
  FFV1_0(w[29], w[34], w[21], pars->GC_2, amp[73]); 
  FFV1_0(w[29], w[34], w[22], pars->GC_11, amp[74]); 
  FFV2_5_0(w[29], w[34], w[23], pars->GC_51, pars->GC_58, amp[75]); 
  FFV1_0(w[1], w[6], w[35], pars->GC_1, amp[76]); 
  FFV1_0(w[1], w[6], w[31], pars->GC_11, amp[77]); 
  FFV2_3_0(w[1], w[6], w[36], pars->GC_50, pars->GC_58, amp[78]); 
  FFV1_0(w[9], w[4], w[35], pars->GC_1, amp[79]); 
  FFV1_0(w[9], w[4], w[31], pars->GC_11, amp[80]); 
  FFV2_3_0(w[9], w[4], w[36], pars->GC_50, pars->GC_58, amp[81]); 
  VVS1_0(w[36], w[2], w[10], pars->GC_81, amp[82]); 
  FFV1_0(w[37], w[28], w[12], pars->GC_1, amp[83]); 
  FFV1_0(w[37], w[28], w[13], pars->GC_11, amp[84]); 
  FFV2_3_0(w[37], w[28], w[14], pars->GC_50, pars->GC_58, amp[85]); 
  FFV1_0(w[29], w[38], w[12], pars->GC_1, amp[86]); 
  FFV1_0(w[29], w[38], w[13], pars->GC_11, amp[87]); 
  FFV2_3_0(w[29], w[38], w[14], pars->GC_50, pars->GC_58, amp[88]); 
  FFV1_0(w[17], w[18], w[35], pars->GC_1, amp[89]); 
  FFV1_0(w[17], w[18], w[31], pars->GC_11, amp[90]); 
  FFV2_3_0(w[17], w[18], w[36], pars->GC_50, pars->GC_58, amp[91]); 
  FFV1_0(w[19], w[16], w[35], pars->GC_1, amp[92]); 
  FFV1_0(w[19], w[16], w[31], pars->GC_11, amp[93]); 
  FFV2_3_0(w[19], w[16], w[36], pars->GC_50, pars->GC_58, amp[94]); 
  VVS1_0(w[36], w[2], w[20], pars->GC_81, amp[95]); 
  FFV1_0(w[37], w[28], w[21], pars->GC_1, amp[96]); 
  FFV1_0(w[37], w[28], w[22], pars->GC_11, amp[97]); 
  FFV2_3_0(w[37], w[28], w[23], pars->GC_50, pars->GC_58, amp[98]); 
  FFV1_0(w[29], w[38], w[21], pars->GC_1, amp[99]); 
  FFV1_0(w[29], w[38], w[22], pars->GC_11, amp[100]); 
  FFV2_3_0(w[29], w[38], w[23], pars->GC_50, pars->GC_58, amp[101]); 


}
double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_ub_zub() 
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
  jamp[0] = -amp[0] + 1./6. * amp[1] - amp[2] - amp[3] + 1./6. * amp[4] -
      amp[5] - amp[6] - amp[7] + 1./6. * amp[8] - amp[9] - amp[10] + 1./6. *
      amp[11] - amp[12];
  jamp[1] = +1./2. * (-amp[1] - amp[4] - amp[8] - amp[11]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_ubx_zubx() 
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
  jamp[0] = +1./2. * (+amp[14] + amp[17] + amp[21] + amp[24]); 
  jamp[1] = +amp[13] - 1./6. * amp[14] + amp[15] + amp[16] - 1./6. * amp[17] +
      amp[18] + amp[19] + amp[20] - 1./6. * amp[21] + amp[22] + amp[23] - 1./6.
      * amp[24] + amp[25];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_db_zdb() 
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
  jamp[0] = -amp[26] + 1./6. * amp[1] - amp[27] - amp[28] + 1./6. * amp[4] -
      amp[29] - amp[30] - amp[31] + 1./6. * amp[32] - amp[33] - amp[34] + 1./6.
      * amp[35] - amp[36];
  jamp[1] = +1./2. * (-amp[1] - amp[4] - amp[32] - amp[35]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_dbx_zdbx() 
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
  jamp[0] = +1./2. * (+amp[38] + amp[41] + amp[45] + amp[48]); 
  jamp[1] = +amp[37] - 1./6. * amp[38] + amp[39] + amp[40] - 1./6. * amp[41] +
      amp[42] + amp[43] + amp[44] - 1./6. * amp[45] + amp[46] + amp[47] - 1./6.
      * amp[48] + amp[49];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_uxb_zuxb() 
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
  jamp[0] = +1./2. * (+amp[51] + amp[54] + amp[58] + amp[61]); 
  jamp[1] = +amp[50] - 1./6. * amp[51] + amp[52] + amp[53] - 1./6. * amp[54] +
      amp[55] + amp[56] + amp[57] - 1./6. * amp[58] + amp[59] + amp[60] - 1./6.
      * amp[61] + amp[62];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_uxbx_zuxbx() 
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
  jamp[0] = -amp[63] + 1./6. * amp[64] - amp[65] - amp[66] + 1./6. * amp[67] -
      amp[68] - amp[69] - amp[70] + 1./6. * amp[71] - amp[72] - amp[73] + 1./6.
      * amp[74] - amp[75];
  jamp[1] = +1./2. * (-amp[64] - amp[67] - amp[71] - amp[74]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_dxb_zdxb() 
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
  jamp[0] = +1./2. * (+amp[77] + amp[80] + amp[84] + amp[87]); 
  jamp[1] = +amp[76] - 1./6. * amp[77] + amp[78] + amp[79] - 1./6. * amp[80] +
      amp[81] + amp[82] + amp[83] - 1./6. * amp[84] + amp[85] + amp[86] - 1./6.
      * amp[87] + amp[88];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R8_P40_sm_qb_zqb::matrix_8_dxbx_zdxbx() 
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
  jamp[0] = -amp[89] + 1./6. * amp[90] - amp[91] - amp[92] + 1./6. * amp[93] -
      amp[94] - amp[95] - amp[96] + 1./6. * amp[97] - amp[98] - amp[99] + 1./6.
      * amp[100] - amp[101];
  jamp[1] = +1./2. * (-amp[90] - amp[93] - amp[97] - amp[100]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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


}  // end namespace PY8MEs_namespace

