//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R7_P7_sm_qq_llbbx.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: u u~ > e- e+ b b~ WEIGHTED<=99 @7
// Process: u u~ > mu- mu+ b b~ WEIGHTED<=99 @7
// Process: c c~ > e- e+ b b~ WEIGHTED<=99 @7
// Process: c c~ > mu- mu+ b b~ WEIGHTED<=99 @7
// Process: d d~ > e- e+ b b~ WEIGHTED<=99 @7
// Process: d d~ > mu- mu+ b b~ WEIGHTED<=99 @7
// Process: s s~ > e- e+ b b~ WEIGHTED<=99 @7
// Process: s s~ > mu- mu+ b b~ WEIGHTED<=99 @7
// Process: u u~ > ve ve~ b b~ WEIGHTED<=99 @7
// Process: u u~ > vm vm~ b b~ WEIGHTED<=99 @7
// Process: c c~ > ve ve~ b b~ WEIGHTED<=99 @7
// Process: c c~ > vm vm~ b b~ WEIGHTED<=99 @7
// Process: d d~ > ve ve~ b b~ WEIGHTED<=99 @7
// Process: d d~ > vm vm~ b b~ WEIGHTED<=99 @7
// Process: s s~ > ve ve~ b b~ WEIGHTED<=99 @7
// Process: s s~ > vm vm~ b b~ WEIGHTED<=99 @7
// Process: u d~ > ve e+ b b~ WEIGHTED<=99 @7
// Process: u d~ > vm mu+ b b~ WEIGHTED<=99 @7
// Process: c s~ > ve e+ b b~ WEIGHTED<=99 @7
// Process: c s~ > vm mu+ b b~ WEIGHTED<=99 @7
// Process: d u~ > e- ve~ b b~ WEIGHTED<=99 @7
// Process: d u~ > mu- vm~ b b~ WEIGHTED<=99 @7
// Process: s c~ > e- ve~ b b~ WEIGHTED<=99 @7
// Process: s c~ > mu- vm~ b b~ WEIGHTED<=99 @7

// Exception class
class PY8MEs_R7_P7_sm_qq_llbbxException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R7_P7_sm_qq_llbbx'."; 
  }
}
PY8MEs_R7_P7_sm_qq_llbbx_exception; 

std::set<int> PY8MEs_R7_P7_sm_qq_llbbx::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R7_P7_sm_qq_llbbx::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R7_P7_sm_qq_llbbx::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9}; 
int PY8MEs_R7_P7_sm_qq_llbbx::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4}; 
int PY8MEs_R7_P7_sm_qq_llbbx::denom_iden[nprocesses] = {1, 1, 1, 1, 1, 1}; 

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R7_P7_sm_qq_llbbx::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: u u~ > e- e+ b b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[0].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[0].push_back(0); 
  // JAMP #1
  color_configs[0].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[0].push_back(0); 

  // Color flows of process Process: d d~ > e- e+ b b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: u u~ > ve ve~ b b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: d d~ > ve ve~ b b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: u d~ > ve e+ b b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[4].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[4].push_back(0); 
  // JAMP #1
  color_configs[4].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[4].push_back(0); 

  // Color flows of process Process: d u~ > e- ve~ b b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[5].push_back(vec_int(createvector<int>
      (1)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(2)));
  jamp_nc_relative_power[5].push_back(0); 
  // JAMP #1
  color_configs[5].push_back(vec_int(createvector<int>
      (2)(0)(0)(1)(0)(0)(0)(0)(2)(0)(0)(1)));
  jamp_nc_relative_power[5].push_back(0); 
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R7_P7_sm_qq_llbbx::~PY8MEs_R7_P7_sm_qq_llbbx() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R7_P7_sm_qq_llbbx::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R7_P7_sm_qq_llbbx::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R7_P7_sm_qq_llbbx::getColorConfigs(int
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
int PY8MEs_R7_P7_sm_qq_llbbx::getColorFlowRelativeNCPower(int color_flow_ID,
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
vector<int> PY8MEs_R7_P7_sm_qq_llbbx::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
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
int PY8MEs_R7_P7_sm_qq_llbbx::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R7_P7_sm_qq_llbbx::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
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
int PY8MEs_R7_P7_sm_qq_llbbx::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R7_P7_sm_qq_llbbx': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
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
      " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R7_P7_sm_qq_llbbx::getAllResults(int
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
double PY8MEs_R7_P7_sm_qq_llbbx::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
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
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R7_P7_sm_qq_llbbx::static_getPY8ME(vector<int> initial_pdgs, vector<int> final_pdgs, set<int> schannels) 
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
  const int nprocs = 48; 
  const int proc_IDS[nprocs] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
      4, 4, 4, 4, 5, 5, 5, 5, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3,
      4, 4, 4, 4, 5, 5, 5, 5};
  const int in_pdgs[nprocs][ninitial] = {{2, -2}, {2, -2}, {4, -4}, {4, -4},
      {1, -1}, {1, -1}, {3, -3}, {3, -3}, {2, -2}, {2, -2}, {4, -4}, {4, -4},
      {1, -1}, {1, -1}, {3, -3}, {3, -3}, {2, -1}, {2, -1}, {4, -3}, {4, -3},
      {1, -2}, {1, -2}, {3, -4}, {3, -4}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4},
      {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-2, 2}, {-2, 2}, {-4, 4}, {-4, 4},
      {-1, 1}, {-1, 1}, {-3, 3}, {-3, 3}, {-1, 2}, {-1, 2}, {-3, 4}, {-3, 4},
      {-2, 1}, {-2, 1}, {-4, 3}, {-4, 3}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{11, -11, 5, -5}, {13,
      -13, 5, -5}, {11, -11, 5, -5}, {13, -13, 5, -5}, {11, -11, 5, -5}, {13,
      -13, 5, -5}, {11, -11, 5, -5}, {13, -13, 5, -5}, {12, -12, 5, -5}, {14,
      -14, 5, -5}, {12, -12, 5, -5}, {14, -14, 5, -5}, {12, -12, 5, -5}, {14,
      -14, 5, -5}, {12, -12, 5, -5}, {14, -14, 5, -5}, {12, -11, 5, -5}, {14,
      -13, 5, -5}, {12, -11, 5, -5}, {14, -13, 5, -5}, {11, -12, 5, -5}, {13,
      -14, 5, -5}, {11, -12, 5, -5}, {13, -14, 5, -5}, {11, -11, 5, -5}, {13,
      -13, 5, -5}, {11, -11, 5, -5}, {13, -13, 5, -5}, {11, -11, 5, -5}, {13,
      -13, 5, -5}, {11, -11, 5, -5}, {13, -13, 5, -5}, {12, -12, 5, -5}, {14,
      -14, 5, -5}, {12, -12, 5, -5}, {14, -14, 5, -5}, {12, -12, 5, -5}, {14,
      -14, 5, -5}, {12, -12, 5, -5}, {14, -14, 5, -5}, {12, -11, 5, -5}, {14,
      -13, 5, -5}, {12, -11, 5, -5}, {14, -13, 5, -5}, {11, -12, 5, -5}, {13,
      -14, 5, -5}, {11, -12, 5, -5}, {13, -14, 5, -5}};

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
void PY8MEs_R7_P7_sm_qq_llbbx::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P7_sm_qq_llbbx': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R7_P7_sm_qq_llbbx::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R7_P7_sm_qq_llbbx::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R7_P7_sm_qq_llbbx::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R7_P7_sm_qq_llbbx::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R7_P7_sm_qq_llbbx::initProc() 
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
  jamp2 = vector < vec_double > (6); 
  jamp2[0] = vector<double> (2, 0.); 
  jamp2[1] = vector<double> (2, 0.); 
  jamp2[2] = vector<double> (2, 0.); 
  jamp2[3] = vector<double> (2, 0.); 
  jamp2[4] = vector<double> (2, 0.); 
  jamp2[5] = vector<double> (2, 0.); 
  all_results = vector < vec_vec_double > (6); 
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
}

// Synchronize local variables of the process that depend on the model
// parameters
void PY8MEs_R7_P7_sm_qq_llbbx::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->ZERO; 
  mME[1] = pars->ZERO; 
  mME[2] = pars->ZERO; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->mdl_MB; 
  mME[5] = pars->mdl_MB; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R7_P7_sm_qq_llbbx::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R7_P7_sm_qq_llbbx::getMasses() 
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
void PY8MEs_R7_P7_sm_qq_llbbx::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R7_P7_sm_qq_llbbx': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R7_P7_sm_qq_llbbx_exception; 
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

double PY8MEs_R7_P7_sm_qq_llbbx::sigmaKin() 
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

    if (proc_ID == 0)
      t = matrix_7_uux_emepbbx(); 
    if (proc_ID == 1)
      t = matrix_7_ddx_emepbbx(); 
    if (proc_ID == 2)
      t = matrix_7_uux_vevexbbx(); 
    if (proc_ID == 3)
      t = matrix_7_ddx_vevexbbx(); 
    if (proc_ID == 4)
      t = matrix_7_udx_veepbbx(); 
    if (proc_ID == 5)
      t = matrix_7_dux_emvexbbx(); 

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

void PY8MEs_R7_P7_sm_qq_llbbx::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  ixxxxx(p[perm[5]], mME[5], hel[5], -1, w[5]); 
  FFV1P0_3(w[0], w[1], pars->GC_2, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[3], w[2], pars->GC_3, pars->ZERO, pars->ZERO, w[7]); 
  FFV1_1(w[4], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[8]); 
  FFV1_2(w[5], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[9]); 
  FFV2_4_3(w[3], w[2], pars->GC_50, pars->GC_59, pars->mdl_MZ, pars->mdl_WZ,
      w[10]);
  FFV1P0_3(w[0], w[1], pars->GC_11, pars->ZERO, pars->ZERO, w[11]); 
  FFV1_1(w[4], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[12]); 
  FFV1_2(w[5], w[11], pars->GC_11, pars->mdl_MB, pars->ZERO, w[13]); 
  FFV2_5_3(w[0], w[1], pars->GC_51, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[14]);
  FFV2_3_1(w[4], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[15]);
  FFV2_3_2(w[5], w[14], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[16]);
  FFS4_3(w[5], w[4], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[17]); 
  FFV1P0_3(w[5], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[18]); 
  FFV1_1(w[2], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[19]); 
  FFV1_2(w[3], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[20]); 
  FFV2_3_3(w[5], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[21]);
  FFV2_4_1(w[2], w[14], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[22]);
  FFV2_4_2(w[3], w[14], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[23]);
  FFV1_2(w[0], w[7], pars->GC_2, pars->ZERO, pars->ZERO, w[24]); 
  FFV1_2(w[0], w[18], pars->GC_2, pars->ZERO, pars->ZERO, w[25]); 
  FFV1P0_3(w[5], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[26]); 
  FFV1_2(w[0], w[26], pars->GC_11, pars->ZERO, pars->ZERO, w[27]); 
  FFV2_5_2(w[0], w[21], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[28]);
  FFV2_5_2(w[0], w[10], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[29]);
  FFV1P0_3(w[0], w[1], pars->GC_1, pars->ZERO, pars->ZERO, w[30]); 
  FFV1_1(w[4], w[30], pars->GC_1, pars->mdl_MB, pars->ZERO, w[31]); 
  FFV1_2(w[5], w[30], pars->GC_1, pars->mdl_MB, pars->ZERO, w[32]); 
  FFV2_3_3(w[0], w[1], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[33]);
  FFV2_3_1(w[4], w[33], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[34]);
  FFV2_3_2(w[5], w[33], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[35]);
  FFV1_1(w[2], w[30], pars->GC_3, pars->ZERO, pars->ZERO, w[36]); 
  FFV1_2(w[3], w[30], pars->GC_3, pars->ZERO, pars->ZERO, w[37]); 
  FFV2_4_1(w[2], w[33], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[38]);
  FFV2_4_2(w[3], w[33], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[39]);
  FFV1_2(w[0], w[7], pars->GC_1, pars->ZERO, pars->ZERO, w[40]); 
  FFV1_2(w[0], w[18], pars->GC_1, pars->ZERO, pars->ZERO, w[41]); 
  FFV2_3_2(w[0], w[21], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[42]);
  FFV2_3_2(w[0], w[10], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[43]);
  FFV2_3(w[3], w[2], pars->GC_62, pars->mdl_MZ, pars->mdl_WZ, w[44]); 
  FFV2_1(w[2], w[14], pars->GC_62, pars->ZERO, pars->ZERO, w[45]); 
  FFV2_2(w[3], w[14], pars->GC_62, pars->ZERO, pars->ZERO, w[46]); 
  FFV2_5_2(w[0], w[44], pars->GC_51, pars->GC_58, pars->ZERO, pars->ZERO,
      w[47]);
  FFV2_1(w[2], w[33], pars->GC_62, pars->ZERO, pars->ZERO, w[48]); 
  FFV2_2(w[3], w[33], pars->GC_62, pars->ZERO, pars->ZERO, w[49]); 
  FFV2_3_2(w[0], w[44], pars->GC_50, pars->GC_58, pars->ZERO, pars->ZERO,
      w[50]);
  FFV2_3(w[0], w[1], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[51]); 
  FFV2_3(w[3], w[2], pars->GC_100, pars->mdl_MW, pars->mdl_WW, w[52]); 
  FFV2_2(w[5], w[51], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[53]); 
  FFV2_1(w[2], w[51], pars->GC_100, pars->ZERO, pars->ZERO, w[54]); 
  FFV2_2(w[3], w[51], pars->GC_100, pars->ZERO, pars->ZERO, w[55]); 
  FFV2_2(w[0], w[52], pars->GC_100, pars->ZERO, pars->ZERO, w[56]); 
  FFV2_1(w[4], w[51], pars->GC_100, pars->mdl_MT, pars->mdl_WT, w[57]); 

  // Calculate all amplitudes
  // Amplitude(s) for diagram number 0
  FFV1_0(w[5], w[8], w[7], pars->GC_1, amp[0]); 
  FFV1_0(w[9], w[4], w[7], pars->GC_1, amp[1]); 
  FFV2_3_0(w[5], w[8], w[10], pars->GC_50, pars->GC_58, amp[2]); 
  FFV2_3_0(w[9], w[4], w[10], pars->GC_50, pars->GC_58, amp[3]); 
  FFV1_0(w[5], w[12], w[7], pars->GC_1, amp[4]); 
  FFV1_0(w[13], w[4], w[7], pars->GC_1, amp[5]); 
  FFV2_3_0(w[5], w[12], w[10], pars->GC_50, pars->GC_58, amp[6]); 
  FFV2_3_0(w[13], w[4], w[10], pars->GC_50, pars->GC_58, amp[7]); 
  FFV1_0(w[5], w[15], w[7], pars->GC_1, amp[8]); 
  FFV1_0(w[16], w[4], w[7], pars->GC_1, amp[9]); 
  FFV2_3_0(w[5], w[15], w[10], pars->GC_50, pars->GC_58, amp[10]); 
  FFV2_3_0(w[16], w[4], w[10], pars->GC_50, pars->GC_58, amp[11]); 
  VVS1_0(w[14], w[10], w[17], pars->GC_81, amp[12]); 
  FFV1_0(w[3], w[19], w[18], pars->GC_3, amp[13]); 
  FFV1_0(w[20], w[2], w[18], pars->GC_3, amp[14]); 
  FFV2_4_0(w[3], w[19], w[21], pars->GC_50, pars->GC_59, amp[15]); 
  FFV2_4_0(w[20], w[2], w[21], pars->GC_50, pars->GC_59, amp[16]); 
  FFV1_0(w[3], w[22], w[18], pars->GC_3, amp[17]); 
  FFV1_0(w[23], w[2], w[18], pars->GC_3, amp[18]); 
  FFV2_4_0(w[3], w[22], w[21], pars->GC_50, pars->GC_59, amp[19]); 
  FFV2_4_0(w[23], w[2], w[21], pars->GC_50, pars->GC_59, amp[20]); 
  FFV1_0(w[24], w[1], w[18], pars->GC_2, amp[21]); 
  FFV1_0(w[25], w[1], w[7], pars->GC_2, amp[22]); 
  FFV1_0(w[24], w[1], w[26], pars->GC_11, amp[23]); 
  FFV1_0(w[27], w[1], w[7], pars->GC_2, amp[24]); 
  FFV2_5_0(w[24], w[1], w[21], pars->GC_51, pars->GC_58, amp[25]); 
  FFV1_0(w[28], w[1], w[7], pars->GC_2, amp[26]); 
  FFV1_0(w[29], w[1], w[18], pars->GC_2, amp[27]); 
  FFV2_5_0(w[25], w[1], w[10], pars->GC_51, pars->GC_58, amp[28]); 
  FFV1_0(w[29], w[1], w[26], pars->GC_11, amp[29]); 
  FFV2_5_0(w[27], w[1], w[10], pars->GC_51, pars->GC_58, amp[30]); 
  FFV2_5_0(w[29], w[1], w[21], pars->GC_51, pars->GC_58, amp[31]); 
  FFV2_5_0(w[28], w[1], w[10], pars->GC_51, pars->GC_58, amp[32]); 
  FFV1_0(w[5], w[31], w[7], pars->GC_1, amp[33]); 
  FFV1_0(w[32], w[4], w[7], pars->GC_1, amp[34]); 
  FFV2_3_0(w[5], w[31], w[10], pars->GC_50, pars->GC_58, amp[35]); 
  FFV2_3_0(w[32], w[4], w[10], pars->GC_50, pars->GC_58, amp[36]); 
  FFV1_0(w[5], w[34], w[7], pars->GC_1, amp[37]); 
  FFV1_0(w[35], w[4], w[7], pars->GC_1, amp[38]); 
  FFV2_3_0(w[5], w[34], w[10], pars->GC_50, pars->GC_58, amp[39]); 
  FFV2_3_0(w[35], w[4], w[10], pars->GC_50, pars->GC_58, amp[40]); 
  VVS1_0(w[33], w[10], w[17], pars->GC_81, amp[41]); 
  FFV1_0(w[3], w[36], w[18], pars->GC_3, amp[42]); 
  FFV1_0(w[37], w[2], w[18], pars->GC_3, amp[43]); 
  FFV2_4_0(w[3], w[36], w[21], pars->GC_50, pars->GC_59, amp[44]); 
  FFV2_4_0(w[37], w[2], w[21], pars->GC_50, pars->GC_59, amp[45]); 
  FFV1_0(w[3], w[38], w[18], pars->GC_3, amp[46]); 
  FFV1_0(w[39], w[2], w[18], pars->GC_3, amp[47]); 
  FFV2_4_0(w[3], w[38], w[21], pars->GC_50, pars->GC_59, amp[48]); 
  FFV2_4_0(w[39], w[2], w[21], pars->GC_50, pars->GC_59, amp[49]); 
  FFV1_0(w[40], w[1], w[18], pars->GC_1, amp[50]); 
  FFV1_0(w[41], w[1], w[7], pars->GC_1, amp[51]); 
  FFV1_0(w[40], w[1], w[26], pars->GC_11, amp[52]); 
  FFV1_0(w[27], w[1], w[7], pars->GC_1, amp[53]); 
  FFV2_3_0(w[40], w[1], w[21], pars->GC_50, pars->GC_58, amp[54]); 
  FFV1_0(w[42], w[1], w[7], pars->GC_1, amp[55]); 
  FFV1_0(w[43], w[1], w[18], pars->GC_1, amp[56]); 
  FFV2_3_0(w[41], w[1], w[10], pars->GC_50, pars->GC_58, amp[57]); 
  FFV1_0(w[43], w[1], w[26], pars->GC_11, amp[58]); 
  FFV2_3_0(w[27], w[1], w[10], pars->GC_50, pars->GC_58, amp[59]); 
  FFV2_3_0(w[43], w[1], w[21], pars->GC_50, pars->GC_58, amp[60]); 
  FFV2_3_0(w[42], w[1], w[10], pars->GC_50, pars->GC_58, amp[61]); 
  FFV2_3_0(w[5], w[8], w[44], pars->GC_50, pars->GC_58, amp[62]); 
  FFV2_3_0(w[9], w[4], w[44], pars->GC_50, pars->GC_58, amp[63]); 
  FFV2_3_0(w[5], w[12], w[44], pars->GC_50, pars->GC_58, amp[64]); 
  FFV2_3_0(w[13], w[4], w[44], pars->GC_50, pars->GC_58, amp[65]); 
  FFV2_3_0(w[5], w[15], w[44], pars->GC_50, pars->GC_58, amp[66]); 
  FFV2_3_0(w[16], w[4], w[44], pars->GC_50, pars->GC_58, amp[67]); 
  VVS1_0(w[14], w[44], w[17], pars->GC_81, amp[68]); 
  FFV2_0(w[3], w[45], w[21], pars->GC_62, amp[69]); 
  FFV2_0(w[46], w[2], w[21], pars->GC_62, amp[70]); 
  FFV1_0(w[47], w[1], w[18], pars->GC_2, amp[71]); 
  FFV2_5_0(w[25], w[1], w[44], pars->GC_51, pars->GC_58, amp[72]); 
  FFV1_0(w[47], w[1], w[26], pars->GC_11, amp[73]); 
  FFV2_5_0(w[27], w[1], w[44], pars->GC_51, pars->GC_58, amp[74]); 
  FFV2_5_0(w[47], w[1], w[21], pars->GC_51, pars->GC_58, amp[75]); 
  FFV2_5_0(w[28], w[1], w[44], pars->GC_51, pars->GC_58, amp[76]); 
  FFV2_3_0(w[5], w[31], w[44], pars->GC_50, pars->GC_58, amp[77]); 
  FFV2_3_0(w[32], w[4], w[44], pars->GC_50, pars->GC_58, amp[78]); 
  FFV2_3_0(w[5], w[12], w[44], pars->GC_50, pars->GC_58, amp[79]); 
  FFV2_3_0(w[13], w[4], w[44], pars->GC_50, pars->GC_58, amp[80]); 
  FFV2_3_0(w[5], w[34], w[44], pars->GC_50, pars->GC_58, amp[81]); 
  FFV2_3_0(w[35], w[4], w[44], pars->GC_50, pars->GC_58, amp[82]); 
  VVS1_0(w[33], w[44], w[17], pars->GC_81, amp[83]); 
  FFV2_0(w[3], w[48], w[21], pars->GC_62, amp[84]); 
  FFV2_0(w[49], w[2], w[21], pars->GC_62, amp[85]); 
  FFV1_0(w[50], w[1], w[18], pars->GC_1, amp[86]); 
  FFV2_3_0(w[41], w[1], w[44], pars->GC_50, pars->GC_58, amp[87]); 
  FFV1_0(w[50], w[1], w[26], pars->GC_11, amp[88]); 
  FFV2_3_0(w[27], w[1], w[44], pars->GC_50, pars->GC_58, amp[89]); 
  FFV2_3_0(w[50], w[1], w[21], pars->GC_50, pars->GC_58, amp[90]); 
  FFV2_3_0(w[42], w[1], w[44], pars->GC_50, pars->GC_58, amp[91]); 
  FFV2_0(w[53], w[4], w[52], pars->GC_100, amp[92]); 
  VVV1_0(w[18], w[51], w[52], pars->GC_4, amp[93]); 
  VVS1_0(w[51], w[52], w[17], pars->GC_72, amp[94]); 
  VVV1_0(w[51], w[52], w[21], pars->GC_53, amp[95]); 
  FFV1_0(w[3], w[54], w[18], pars->GC_3, amp[96]); 
  FFV2_4_0(w[3], w[54], w[21], pars->GC_50, pars->GC_59, amp[97]); 
  FFV2_0(w[55], w[2], w[21], pars->GC_62, amp[98]); 
  FFV1_0(w[56], w[1], w[18], pars->GC_1, amp[99]); 
  FFV2_0(w[25], w[1], w[52], pars->GC_100, amp[100]); 
  FFV1_0(w[56], w[1], w[26], pars->GC_11, amp[101]); 
  FFV2_0(w[27], w[1], w[52], pars->GC_100, amp[102]); 
  FFV2_3_0(w[56], w[1], w[21], pars->GC_50, pars->GC_58, amp[103]); 
  FFV2_0(w[28], w[1], w[52], pars->GC_100, amp[104]); 
  FFV2_0(w[5], w[57], w[52], pars->GC_100, amp[105]); 
  VVV1_0(w[18], w[52], w[51], pars->GC_4, amp[106]); 
  VVS1_0(w[52], w[51], w[17], pars->GC_72, amp[107]); 
  VVV1_0(w[52], w[51], w[21], pars->GC_53, amp[108]); 
  FFV1_0(w[55], w[2], w[18], pars->GC_3, amp[109]); 
  FFV2_0(w[3], w[54], w[21], pars->GC_62, amp[110]); 
  FFV2_4_0(w[55], w[2], w[21], pars->GC_50, pars->GC_59, amp[111]); 
  FFV1_0(w[56], w[1], w[18], pars->GC_2, amp[112]); 
  FFV2_0(w[41], w[1], w[52], pars->GC_100, amp[113]); 
  FFV1_0(w[56], w[1], w[26], pars->GC_11, amp[114]); 
  FFV2_0(w[27], w[1], w[52], pars->GC_100, amp[115]); 
  FFV2_5_0(w[56], w[1], w[21], pars->GC_51, pars->GC_58, amp[116]); 
  FFV2_0(w[42], w[1], w[52], pars->GC_100, amp[117]); 


}
double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_uux_emepbbx() 
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

double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_ddx_emepbbx() 
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
  jamp[0] = +amp[33] + amp[34] + amp[35] + amp[36] - 1./6. * amp[4] - 1./6. *
      amp[5] - 1./6. * amp[6] - 1./6. * amp[7] + amp[37] + amp[38] + amp[39] +
      amp[40] + amp[41] + amp[42] + amp[43] + amp[44] + amp[45] + amp[46] +
      amp[47] + amp[48] + amp[49] + amp[50] + amp[51] - 1./6. * amp[52] - 1./6.
      * amp[53] + amp[54] + amp[55] + amp[56] + amp[57] - 1./6. * amp[58] -
      1./6. * amp[59] + amp[60] + amp[61];
  jamp[1] = +1./2. * (+amp[4] + amp[5] + amp[6] + amp[7] + amp[52] + amp[53] +
      amp[58] + amp[59]);

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_uux_vevexbbx() 
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
  jamp[0] = +amp[62] + amp[63] - 1./6. * amp[64] - 1./6. * amp[65] + amp[66] +
      amp[67] + amp[68] + amp[69] + amp[70] + amp[71] + amp[72] - 1./6. *
      amp[73] - 1./6. * amp[74] + amp[75] + amp[76];
  jamp[1] = +1./2. * (+amp[64] + amp[65] + amp[73] + amp[74]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_ddx_vevexbbx() 
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
  jamp[0] = +amp[77] + amp[78] - 1./6. * amp[79] - 1./6. * amp[80] + amp[81] +
      amp[82] + amp[83] + amp[84] + amp[85] + amp[86] + amp[87] - 1./6. *
      amp[88] - 1./6. * amp[89] + amp[90] + amp[91];
  jamp[1] = +1./2. * (+amp[79] + amp[80] + amp[88] + amp[89]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_udx_veepbbx() 
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
  jamp[0] = +amp[92] + amp[93] + amp[94] + amp[95] + amp[96] + amp[97] +
      amp[98] + amp[99] + amp[100] - 1./6. * amp[101] - 1./6. * amp[102] +
      amp[103] + amp[104];
  jamp[1] = +1./2. * (+amp[101] + amp[102]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P7_sm_qq_llbbx::matrix_7_dux_emvexbbx() 
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
  jamp[0] = +amp[105] + amp[106] + amp[107] + amp[108] + amp[109] + amp[110] +
      amp[111] + amp[112] + amp[113] - 1./6. * amp[114] - 1./6. * amp[115] +
      amp[116] + amp[117];
  jamp[1] = +1./2. * (+amp[114] + amp[115]); 

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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


}  // end namespace PY8MEs_namespace

