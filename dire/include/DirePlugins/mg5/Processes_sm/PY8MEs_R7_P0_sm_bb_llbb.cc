//==========================================================================
// This file has been automatically generated for Pythia 8 by
// MadGraph5_aMC@NLO v. 2.6.0, 2017-08-16
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "PY8MEs_R7_P0_sm_bb_llbb.h"
#include "HelAmps_sm.h"

using namespace Pythia8_sm; 

namespace PY8MEs_namespace 
{
//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: b b > e- e+ b b WEIGHTED<=99 @7
// Process: b b > mu- mu+ b b WEIGHTED<=99 @7
// Process: b b~ > e- e+ b b~ WEIGHTED<=99 @7
// Process: b b~ > mu- mu+ b b~ WEIGHTED<=99 @7
// Process: b~ b~ > e- e+ b~ b~ WEIGHTED<=99 @7
// Process: b~ b~ > mu- mu+ b~ b~ WEIGHTED<=99 @7
// Process: b b > ve ve~ b b WEIGHTED<=99 @7
// Process: b b > vm vm~ b b WEIGHTED<=99 @7
// Process: b b~ > ve ve~ b b~ WEIGHTED<=99 @7
// Process: b b~ > vm vm~ b b~ WEIGHTED<=99 @7
// Process: b~ b~ > ve ve~ b~ b~ WEIGHTED<=99 @7
// Process: b~ b~ > vm vm~ b~ b~ WEIGHTED<=99 @7

// Exception class
class PY8MEs_R7_P0_sm_bb_llbbException : public exception
{
  virtual const char * what() const throw()
  {
    return "Exception in class 'PY8MEs_R7_P0_sm_bb_llbb'."; 
  }
}
PY8MEs_R7_P0_sm_bb_llbb_exception; 

std::set<int> PY8MEs_R7_P0_sm_bb_llbb::s_channel_proc = std::set<int>
    (createset<int> ());

int PY8MEs_R7_P0_sm_bb_llbb::helicities[ncomb][nexternal] = {{-1, -1, -1, -1,
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
int PY8MEs_R7_P0_sm_bb_llbb::denom_colors[nprocesses] = {9, 9, 9, 9, 9, 9}; 
int PY8MEs_R7_P0_sm_bb_llbb::denom_hels[nprocesses] = {4, 4, 4, 4, 4, 4}; 
int PY8MEs_R7_P0_sm_bb_llbb::denom_iden[nprocesses] = {2, 1, 2, 2, 1, 2}; 

//--------------------------------------------------------------------------
// Color config initialization
void PY8MEs_R7_P0_sm_bb_llbb::initColorConfigs() 
{
  color_configs = vector < vec_vec_int > (); 
  jamp_nc_relative_power = vector < vec_int > (); 

  // Color flows of process Process: b b > e- e+ b b WEIGHTED<=99 @7
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

  // Color flows of process Process: b b~ > e- e+ b b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: b~ b~ > e- e+ b~ b~ WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[2].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)));
  jamp_nc_relative_power[2].push_back(0); 
  // JAMP #1
  color_configs[2].push_back(vec_int(createvector<int>
      (0)(1)(0)(2)(0)(0)(0)(0)(0)(2)(0)(1)));
  jamp_nc_relative_power[2].push_back(0); 

  // Color flows of process Process: b b > ve ve~ b b WEIGHTED<=99 @7
  color_configs.push_back(vec_vec_int()); 
  jamp_nc_relative_power.push_back(vec_int()); 
  // JAMP #0
  color_configs[3].push_back(vec_int(createvector<int>
      (1)(0)(2)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[3].push_back(0); 
  // JAMP #1
  color_configs[3].push_back(vec_int(createvector<int>
      (2)(0)(1)(0)(0)(0)(0)(0)(1)(0)(2)(0)));
  jamp_nc_relative_power[3].push_back(0); 

  // Color flows of process Process: b b~ > ve ve~ b b~ WEIGHTED<=99 @7
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

  // Color flows of process Process: b~ b~ > ve ve~ b~ b~ WEIGHTED<=99 @7
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
}

//--------------------------------------------------------------------------
// Destructor.
PY8MEs_R7_P0_sm_bb_llbb::~PY8MEs_R7_P0_sm_bb_llbb() 
{
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
}

//--------------------------------------------------------------------------
// Invert the permutation mapping
vector<int> PY8MEs_R7_P0_sm_bb_llbb::invert_mapping(vector<int> mapping) 
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
vector < vec_int > PY8MEs_R7_P0_sm_bb_llbb::getHelicityConfigs(vector<int>
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
vector < vec_int > PY8MEs_R7_P0_sm_bb_llbb::getColorConfigs(int
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
int PY8MEs_R7_P0_sm_bb_llbb::getColorFlowRelativeNCPower(int color_flow_ID, int
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
vector<int> PY8MEs_R7_P0_sm_bb_llbb::getHelicityConfigForID(int hel_ID,
    vector<int> permutation)
{
  if (hel_ID < 0 || hel_ID >= ncomb)
  {
    cerr <<  "Error in function 'getHelicityConfigForID' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Specified helicity ID '" << 
    hel_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
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
int PY8MEs_R7_P0_sm_bb_llbb::getHelicityIDForConfig(vector<int> hel_config,
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
      " 'PY8MEs_R7_P0_sm_bb_llbb': Specified helicity" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
    }
  }
  return user_ihel; 
}


//--------------------------------------------------------------------------
// Implements the map Color ID -> Color Config
vector<int> PY8MEs_R7_P0_sm_bb_llbb::getColorConfigForID(int color_ID, int
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
    " 'PY8MEs_R7_P0_sm_bb_llbb': Specified color ID '" << 
    color_ID <<  "' cannot be found." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
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
int PY8MEs_R7_P0_sm_bb_llbb::getColorIDForConfig(vector<int> color_config, int
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
            " 'PY8MEs_R7_P0_sm_bb_llbb': A color line could " << 
            " not be closed." << endl; 
            throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
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
      " 'PY8MEs_R7_P0_sm_bb_llbb': Specified color" << 
      " configuration cannot be found." << endl; 
      throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
    }
  }
  return user_icol; 
}

//--------------------------------------------------------------------------
// Returns all result previously computed in SigmaKin
vector < vec_double > PY8MEs_R7_P0_sm_bb_llbb::getAllResults(int
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
double PY8MEs_R7_P0_sm_bb_llbb::getResult(int helicity_ID, int color_ID, int
    specify_proc_ID)
{
  if (helicity_ID < - 1 || helicity_ID >= ncomb)
  {
    cerr <<  "Error in function 'getResult' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Specified helicity ID '" << 
    helicity_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
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
    " 'PY8MEs_R7_P0_sm_bb_llbb': Specified color ID '" << 
    color_ID <<  "' configuration cannot be found." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  return all_results[chosenProcID][helicity_ID + 1][color_ID + 1]; 
}

//--------------------------------------------------------------------------
// Check for the availability of the requested process and if available,
// If available, this returns the corresponding permutation and Proc_ID to use.
// If not available, this returns a negative Proc_ID.
pair < vector<int> , int > PY8MEs_R7_P0_sm_bb_llbb::static_getPY8ME(vector<int>
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
  const int nprocs = 16; 
  const int proc_IDS[nprocs] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 1, 4,
      4};
  const int in_pdgs[nprocs][ninitial] = {{5, 5}, {5, 5}, {5, -5}, {5, -5}, {-5,
      -5}, {-5, -5}, {5, 5}, {5, 5}, {5, -5}, {5, -5}, {-5, -5}, {-5, -5}, {-5,
      5}, {-5, 5}, {-5, 5}, {-5, 5}};
  const int out_pdgs[nprocs][nexternal - ninitial] = {{11, -11, 5, 5}, {13,
      -13, 5, 5}, {11, -11, 5, -5}, {13, -13, 5, -5}, {11, -11, -5, -5}, {13,
      -13, -5, -5}, {12, -12, 5, 5}, {14, -14, 5, 5}, {12, -12, 5, -5}, {14,
      -14, 5, -5}, {12, -12, -5, -5}, {14, -14, -5, -5}, {11, -11, 5, -5}, {13,
      -13, 5, -5}, {12, -12, 5, -5}, {14, -14, 5, -5}};

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
void PY8MEs_R7_P0_sm_bb_llbb::setMomenta(vector < vec_double > momenta_picked)
{
  if (momenta_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setMomenta' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number of" << 
    " momenta specified." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    if (momenta_picked[i].size() != 4)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number of" << 
      " momenta components specified." << endl; 
      throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
    }
    if (momenta_picked[i][0] < 0.0)
    {
      cerr <<  "Error in function 'setMomenta' of class" << 
      " 'PY8MEs_R7_P0_sm_bb_llbb': A momentum was specified" << 
      " with negative energy. Check conventions." << endl; 
      throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
    }
    for (unsigned int j = 0; j < 4; j++ )
    {
      p[i][j] = momenta_picked[i][j]; 
    }
  }
}

//--------------------------------------------------------------------------
// Set color configuration to use. An empty vector means sum over all.
void PY8MEs_R7_P0_sm_bb_llbb::setColors(vector<int> colors_picked)
{
  if (colors_picked.size() == 0)
  {
    user_colors = vector<int> (); 
    return; 
  }
  if (colors_picked.size() != (2 * nexternal))
  {
    cerr <<  "Error in function 'setColors' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number" << 
    " of colors specified." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  user_colors = vector<int> ((2 * nexternal), 0); 
  for(unsigned int i = 0; i < (2 * nexternal); i++ )
  {
    user_colors[i] = colors_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the helicity configuration to use. Am empty vector means sum over all.
void PY8MEs_R7_P0_sm_bb_llbb::setHelicities(vector<int> helicities_picked) 
{
  if (helicities_picked.size() != nexternal)
  {
    if (helicities_picked.size() == 0)
    {
      user_helicities = vector<int> (); 
      return; 
    }
    cerr <<  "Error in function 'setHelicities' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number" << 
    " of helicities specified." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  user_helicities = vector<int> (nexternal, 0); 
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    user_helicities[i] = helicities_picked[i]; 
  }
}

//--------------------------------------------------------------------------
// Set the permutation to use (will apply to momenta, colors and helicities)
void PY8MEs_R7_P0_sm_bb_llbb::setPermutation(vector<int> perm_picked) 
{
  if (perm_picked.size() != nexternal)
  {
    cerr <<  "Error in function 'setPermutations' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number" << 
    " of permutations specified." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  for(unsigned int i = 0; i < nexternal; i++ )
  {
    perm[i] = perm_picked[i]; 
  }
}

// Set the proc_ID to use
void PY8MEs_R7_P0_sm_bb_llbb::setProcID(int procID_picked) 
{
  proc_ID = procID_picked; 
}

//--------------------------------------------------------------------------
// Initialize process.

void PY8MEs_R7_P0_sm_bb_llbb::initProc() 
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
void PY8MEs_R7_P0_sm_bb_llbb::syncProcModelParams() 
{

  // Instantiate the model class and set parameters that stay fixed during run
  mME[0] = pars->mdl_MB; 
  mME[1] = pars->mdl_MB; 
  mME[2] = pars->ZERO; 
  mME[3] = pars->ZERO; 
  mME[4] = pars->mdl_MB; 
  mME[5] = pars->mdl_MB; 
}

//--------------------------------------------------------------------------
// Setter allowing to force particular values for the external masses
void PY8MEs_R7_P0_sm_bb_llbb::setMasses(vec_double external_masses) 
{

  if (external_masses.size() != mME.size())
  {
    cerr <<  "Error in function 'setMasses' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect number of" << 
    " masses specified." << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
  }
  for (unsigned int j = 0; j < mME.size(); j++ )
  {
    mME[j] = external_masses[perm[j]]; 
  }
}

//--------------------------------------------------------------------------
// Getter accessing external masses with the correct ordering
vector<double> PY8MEs_R7_P0_sm_bb_llbb::getMasses() 
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
void PY8MEs_R7_P0_sm_bb_llbb::setExternalMassesMode(int mode) 
{
  if (mode != 0 && mode != 1 && mode != 2)
  {
    cerr <<  "Error in function 'setExternalMassesMode' of class" << 
    " 'PY8MEs_R7_P0_sm_bb_llbb': Incorrect mode selected :" << mode << 
    ". It must be either 0, 1 or 2" << endl; 
    throw PY8MEs_R7_P0_sm_bb_llbb_exception; 
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

double PY8MEs_R7_P0_sm_bb_llbb::sigmaKin() 
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
      t = matrix_7_bb_emepbb(); 
    if (proc_ID == 1)
      t = matrix_7_bbx_emepbbx(); 
    if (proc_ID == 2)
      t = matrix_7_bxbx_emepbxbx(); 
    if (proc_ID == 3)
      t = matrix_7_bb_vevexbb(); 
    if (proc_ID == 4)
      t = matrix_7_bbx_vevexbbx(); 
    if (proc_ID == 5)
      t = matrix_7_bxbx_vevexbxbx(); 

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

void PY8MEs_R7_P0_sm_bb_llbb::calculate_wavefunctions(const int hel[])
{
  // Calculate wavefunctions for all processes
  // Calculate all wavefunctions
  ixxxxx(p[perm[0]], mME[0], hel[0], +1, w[0]); 
  ixxxxx(p[perm[1]], mME[1], hel[1], +1, w[1]); 
  oxxxxx(p[perm[2]], mME[2], hel[2], +1, w[2]); 
  ixxxxx(p[perm[3]], mME[3], hel[3], -1, w[3]); 
  oxxxxx(p[perm[4]], mME[4], hel[4], +1, w[4]); 
  oxxxxx(p[perm[5]], mME[5], hel[5], +1, w[5]); 
  FFV1P0_3(w[0], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[6]); 
  FFV1P0_3(w[1], w[5], pars->GC_1, pars->ZERO, pars->ZERO, w[7]); 
  FFV1_1(w[2], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[8]); 
  FFV1_2(w[3], w[6], pars->GC_3, pars->ZERO, pars->ZERO, w[9]); 
  FFV2_3_3(w[1], w[5], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[10]);
  FFV2_3_3(w[0], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[11]);
  FFV2_4_1(w[2], w[11], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[12]);
  FFV2_4_2(w[3], w[11], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[13]);
  FFS4_3(w[0], w[4], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[14]); 
  FFV2_4_3(w[3], w[2], pars->GC_50, pars->GC_59, pars->mdl_MZ, pars->mdl_WZ,
      w[15]);
  FFS4_3(w[1], w[5], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[16]); 
  FFV1P0_3(w[3], w[2], pars->GC_3, pars->ZERO, pars->ZERO, w[17]); 
  FFV1_2(w[1], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[18]); 
  FFV1_1(w[5], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[19]); 
  FFV1P0_3(w[0], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[20]); 
  FFV1_2(w[1], w[20], pars->GC_11, pars->mdl_MB, pars->ZERO, w[21]); 
  FFV1_1(w[5], w[20], pars->GC_11, pars->mdl_MB, pars->ZERO, w[22]); 
  FFS4_2(w[1], w[14], pars->GC_83, pars->mdl_MB, pars->ZERO, w[23]); 
  FFS4_1(w[5], w[14], pars->GC_83, pars->mdl_MB, pars->ZERO, w[24]); 
  FFV2_3_2(w[1], w[11], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[25]);
  FFV2_3_1(w[5], w[11], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[26]);
  FFV1P0_3(w[0], w[5], pars->GC_1, pars->ZERO, pars->ZERO, w[27]); 
  FFV1P0_3(w[1], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[28]); 
  FFV1_1(w[2], w[27], pars->GC_3, pars->ZERO, pars->ZERO, w[29]); 
  FFV1_2(w[3], w[27], pars->GC_3, pars->ZERO, pars->ZERO, w[30]); 
  FFV2_3_3(w[1], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[31]);
  FFV2_3_3(w[0], w[5], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[32]);
  FFV2_4_1(w[2], w[32], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[33]);
  FFV2_4_2(w[3], w[32], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[34]);
  FFS4_3(w[0], w[5], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[35]); 
  FFS4_3(w[1], w[4], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[36]); 
  FFV1_2(w[1], w[27], pars->GC_1, pars->mdl_MB, pars->ZERO, w[37]); 
  FFV1_1(w[4], w[27], pars->GC_1, pars->mdl_MB, pars->ZERO, w[38]); 
  FFV1P0_3(w[0], w[5], pars->GC_11, pars->ZERO, pars->ZERO, w[39]); 
  FFV1_2(w[1], w[39], pars->GC_11, pars->mdl_MB, pars->ZERO, w[40]); 
  FFV1_1(w[4], w[39], pars->GC_11, pars->mdl_MB, pars->ZERO, w[41]); 
  FFS4_2(w[1], w[35], pars->GC_83, pars->mdl_MB, pars->ZERO, w[42]); 
  FFS4_1(w[4], w[35], pars->GC_83, pars->mdl_MB, pars->ZERO, w[43]); 
  FFV2_3_2(w[1], w[32], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[44]);
  FFV2_3_1(w[4], w[32], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[45]);
  FFV1_2(w[0], w[28], pars->GC_1, pars->mdl_MB, pars->ZERO, w[46]); 
  FFV1_2(w[0], w[17], pars->GC_1, pars->mdl_MB, pars->ZERO, w[47]); 
  FFV2_3_2(w[0], w[15], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[48]);
  FFV1P0_3(w[1], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[49]); 
  FFV1_2(w[0], w[49], pars->GC_11, pars->mdl_MB, pars->ZERO, w[50]); 
  FFS4_2(w[0], w[36], pars->GC_83, pars->mdl_MB, pars->ZERO, w[51]); 
  FFV2_3_2(w[0], w[31], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[52]);
  FFV1_2(w[0], w[7], pars->GC_1, pars->mdl_MB, pars->ZERO, w[53]); 
  FFV1P0_3(w[1], w[5], pars->GC_11, pars->ZERO, pars->ZERO, w[54]); 
  FFV1_2(w[0], w[54], pars->GC_11, pars->mdl_MB, pars->ZERO, w[55]); 
  FFS4_2(w[0], w[16], pars->GC_83, pars->mdl_MB, pars->ZERO, w[56]); 
  FFV2_3_2(w[0], w[10], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[57]);
  oxxxxx(p[perm[1]], mME[1], hel[1], -1, w[58]); 
  ixxxxx(p[perm[5]], mME[5], hel[5], -1, w[59]); 
  FFV1P0_3(w[0], w[58], pars->GC_1, pars->ZERO, pars->ZERO, w[60]); 
  FFV1P0_3(w[59], w[4], pars->GC_1, pars->ZERO, pars->ZERO, w[61]); 
  FFV1_1(w[2], w[60], pars->GC_3, pars->ZERO, pars->ZERO, w[62]); 
  FFV1_2(w[3], w[60], pars->GC_3, pars->ZERO, pars->ZERO, w[63]); 
  FFV2_3_3(w[59], w[4], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[64]);
  FFV2_3_3(w[0], w[58], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[65]);
  FFV2_4_1(w[2], w[65], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[66]);
  FFV2_4_2(w[3], w[65], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[67]);
  FFS4_3(w[0], w[58], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[68]); 
  FFS4_3(w[59], w[4], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[69]); 
  FFV1_2(w[59], w[60], pars->GC_1, pars->mdl_MB, pars->ZERO, w[70]); 
  FFV1_1(w[4], w[60], pars->GC_1, pars->mdl_MB, pars->ZERO, w[71]); 
  FFV1P0_3(w[0], w[58], pars->GC_11, pars->ZERO, pars->ZERO, w[72]); 
  FFV1_2(w[59], w[72], pars->GC_11, pars->mdl_MB, pars->ZERO, w[73]); 
  FFV1_1(w[4], w[72], pars->GC_11, pars->mdl_MB, pars->ZERO, w[74]); 
  FFS4_2(w[59], w[68], pars->GC_83, pars->mdl_MB, pars->ZERO, w[75]); 
  FFS4_1(w[4], w[68], pars->GC_83, pars->mdl_MB, pars->ZERO, w[76]); 
  FFV2_3_2(w[59], w[65], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[77]);
  FFV2_3_1(w[4], w[65], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[78]);
  FFV1P0_3(w[59], w[58], pars->GC_1, pars->ZERO, pars->ZERO, w[79]); 
  FFV2_3_3(w[59], w[58], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[80]);
  FFS4_3(w[59], w[58], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[81]); 
  FFV1_2(w[59], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[82]); 
  FFV1_1(w[58], w[6], pars->GC_1, pars->mdl_MB, pars->ZERO, w[83]); 
  FFV1_2(w[59], w[20], pars->GC_11, pars->mdl_MB, pars->ZERO, w[84]); 
  FFV1_1(w[58], w[20], pars->GC_11, pars->mdl_MB, pars->ZERO, w[85]); 
  FFS4_2(w[59], w[14], pars->GC_83, pars->mdl_MB, pars->ZERO, w[86]); 
  FFS4_1(w[58], w[14], pars->GC_83, pars->mdl_MB, pars->ZERO, w[87]); 
  FFV2_3_2(w[59], w[11], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[88]);
  FFV2_3_1(w[58], w[11], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[89]);
  FFV1_2(w[0], w[79], pars->GC_1, pars->mdl_MB, pars->ZERO, w[90]); 
  FFV1P0_3(w[59], w[58], pars->GC_11, pars->ZERO, pars->ZERO, w[91]); 
  FFV1_2(w[0], w[91], pars->GC_11, pars->mdl_MB, pars->ZERO, w[92]); 
  FFS4_2(w[0], w[81], pars->GC_83, pars->mdl_MB, pars->ZERO, w[93]); 
  FFV2_3_2(w[0], w[80], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[94]);
  FFV1_2(w[0], w[61], pars->GC_1, pars->mdl_MB, pars->ZERO, w[95]); 
  FFV1P0_3(w[59], w[4], pars->GC_11, pars->ZERO, pars->ZERO, w[96]); 
  FFV1_2(w[0], w[96], pars->GC_11, pars->mdl_MB, pars->ZERO, w[97]); 
  FFS4_2(w[0], w[69], pars->GC_83, pars->mdl_MB, pars->ZERO, w[98]); 
  FFV2_3_2(w[0], w[64], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[99]);
  oxxxxx(p[perm[0]], mME[0], hel[0], -1, w[100]); 
  ixxxxx(p[perm[4]], mME[4], hel[4], -1, w[101]); 
  FFV1P0_3(w[101], w[100], pars->GC_1, pars->ZERO, pars->ZERO, w[102]); 
  FFV1_1(w[2], w[102], pars->GC_3, pars->ZERO, pars->ZERO, w[103]); 
  FFV1_2(w[3], w[102], pars->GC_3, pars->ZERO, pars->ZERO, w[104]); 
  FFV2_3_3(w[101], w[100], pars->GC_50, pars->GC_58, pars->mdl_MZ,
      pars->mdl_WZ, w[105]);
  FFV2_4_1(w[2], w[105], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[106]);
  FFV2_4_2(w[3], w[105], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[107]);
  FFS4_3(w[101], w[100], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[108]); 
  FFV1_2(w[59], w[102], pars->GC_1, pars->mdl_MB, pars->ZERO, w[109]); 
  FFV1_1(w[58], w[102], pars->GC_1, pars->mdl_MB, pars->ZERO, w[110]); 
  FFV1P0_3(w[101], w[100], pars->GC_11, pars->ZERO, pars->ZERO, w[111]); 
  FFV1_2(w[59], w[111], pars->GC_11, pars->mdl_MB, pars->ZERO, w[112]); 
  FFV1_1(w[58], w[111], pars->GC_11, pars->mdl_MB, pars->ZERO, w[113]); 
  FFS4_2(w[59], w[108], pars->GC_83, pars->mdl_MB, pars->ZERO, w[114]); 
  FFS4_1(w[58], w[108], pars->GC_83, pars->mdl_MB, pars->ZERO, w[115]); 
  FFV2_3_2(w[59], w[105], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[116]);
  FFV2_3_1(w[58], w[105], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[117]);
  FFV1P0_3(w[101], w[58], pars->GC_1, pars->ZERO, pars->ZERO, w[118]); 
  FFV1P0_3(w[59], w[100], pars->GC_1, pars->ZERO, pars->ZERO, w[119]); 
  FFV1_1(w[2], w[118], pars->GC_3, pars->ZERO, pars->ZERO, w[120]); 
  FFV1_2(w[3], w[118], pars->GC_3, pars->ZERO, pars->ZERO, w[121]); 
  FFV2_3_3(w[59], w[100], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[122]);
  FFV2_3_3(w[101], w[58], pars->GC_50, pars->GC_58, pars->mdl_MZ, pars->mdl_WZ,
      w[123]);
  FFV2_4_1(w[2], w[123], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[124]);
  FFV2_4_2(w[3], w[123], pars->GC_50, pars->GC_59, pars->ZERO, pars->ZERO,
      w[125]);
  FFS4_3(w[101], w[58], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[126]); 
  FFS4_3(w[59], w[100], pars->GC_83, pars->mdl_MH, pars->mdl_WH, w[127]); 
  FFV1_2(w[59], w[118], pars->GC_1, pars->mdl_MB, pars->ZERO, w[128]); 
  FFV1_1(w[100], w[118], pars->GC_1, pars->mdl_MB, pars->ZERO, w[129]); 
  FFV1P0_3(w[101], w[58], pars->GC_11, pars->ZERO, pars->ZERO, w[130]); 
  FFV1_2(w[59], w[130], pars->GC_11, pars->mdl_MB, pars->ZERO, w[131]); 
  FFV1_1(w[100], w[130], pars->GC_11, pars->mdl_MB, pars->ZERO, w[132]); 
  FFS4_2(w[59], w[126], pars->GC_83, pars->mdl_MB, pars->ZERO, w[133]); 
  FFS4_1(w[100], w[126], pars->GC_83, pars->mdl_MB, pars->ZERO, w[134]); 
  FFV2_3_2(w[59], w[123], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[135]);
  FFV2_3_1(w[100], w[123], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[136]);
  FFV1_2(w[101], w[119], pars->GC_1, pars->mdl_MB, pars->ZERO, w[137]); 
  FFV1_2(w[101], w[17], pars->GC_1, pars->mdl_MB, pars->ZERO, w[138]); 
  FFV2_3_2(w[101], w[15], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[139]);
  FFV1P0_3(w[59], w[100], pars->GC_11, pars->ZERO, pars->ZERO, w[140]); 
  FFV1_2(w[101], w[140], pars->GC_11, pars->mdl_MB, pars->ZERO, w[141]); 
  FFS4_2(w[101], w[127], pars->GC_83, pars->mdl_MB, pars->ZERO, w[142]); 
  FFV2_3_2(w[101], w[122], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[143]);
  FFV1_2(w[101], w[79], pars->GC_1, pars->mdl_MB, pars->ZERO, w[144]); 
  FFV1_2(w[101], w[91], pars->GC_11, pars->mdl_MB, pars->ZERO, w[145]); 
  FFS4_2(w[101], w[81], pars->GC_83, pars->mdl_MB, pars->ZERO, w[146]); 
  FFV2_3_2(w[101], w[80], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[147]);
  FFV2_1(w[2], w[11], pars->GC_62, pars->ZERO, pars->ZERO, w[148]); 
  FFV2_2(w[3], w[11], pars->GC_62, pars->ZERO, pars->ZERO, w[149]); 
  FFV2_3(w[3], w[2], pars->GC_62, pars->mdl_MZ, pars->mdl_WZ, w[150]); 
  FFV2_1(w[2], w[32], pars->GC_62, pars->ZERO, pars->ZERO, w[151]); 
  FFV2_2(w[3], w[32], pars->GC_62, pars->ZERO, pars->ZERO, w[152]); 
  FFV2_3_2(w[0], w[150], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[153]);
  FFV2_1(w[2], w[65], pars->GC_62, pars->ZERO, pars->ZERO, w[154]); 
  FFV2_2(w[3], w[65], pars->GC_62, pars->ZERO, pars->ZERO, w[155]); 
  FFV2_1(w[2], w[105], pars->GC_62, pars->ZERO, pars->ZERO, w[156]); 
  FFV2_2(w[3], w[105], pars->GC_62, pars->ZERO, pars->ZERO, w[157]); 
  FFV2_1(w[2], w[123], pars->GC_62, pars->ZERO, pars->ZERO, w[158]); 
  FFV2_2(w[3], w[123], pars->GC_62, pars->ZERO, pars->ZERO, w[159]); 
  FFV2_3_2(w[101], w[150], pars->GC_50, pars->GC_58, pars->mdl_MB, pars->ZERO,
      w[160]);

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
  VVS1_0(w[10], w[15], w[14], pars->GC_81, amp[8]); 
  VVS1_0(w[11], w[15], w[16], pars->GC_81, amp[9]); 
  FFV1_0(w[18], w[5], w[17], pars->GC_1, amp[10]); 
  FFV1_0(w[1], w[19], w[17], pars->GC_1, amp[11]); 
  FFV2_3_0(w[18], w[5], w[15], pars->GC_50, pars->GC_58, amp[12]); 
  FFV2_3_0(w[1], w[19], w[15], pars->GC_50, pars->GC_58, amp[13]); 
  FFV1_0(w[21], w[5], w[17], pars->GC_1, amp[14]); 
  FFV1_0(w[1], w[22], w[17], pars->GC_1, amp[15]); 
  FFV2_3_0(w[21], w[5], w[15], pars->GC_50, pars->GC_58, amp[16]); 
  FFV2_3_0(w[1], w[22], w[15], pars->GC_50, pars->GC_58, amp[17]); 
  FFV1_0(w[23], w[5], w[17], pars->GC_1, amp[18]); 
  FFV1_0(w[1], w[24], w[17], pars->GC_1, amp[19]); 
  FFV2_3_0(w[23], w[5], w[15], pars->GC_50, pars->GC_58, amp[20]); 
  FFV2_3_0(w[1], w[24], w[15], pars->GC_50, pars->GC_58, amp[21]); 
  FFV1_0(w[25], w[5], w[17], pars->GC_1, amp[22]); 
  FFV1_0(w[1], w[26], w[17], pars->GC_1, amp[23]); 
  FFV2_3_0(w[25], w[5], w[15], pars->GC_50, pars->GC_58, amp[24]); 
  FFV2_3_0(w[1], w[26], w[15], pars->GC_50, pars->GC_58, amp[25]); 
  FFV1_0(w[3], w[29], w[28], pars->GC_3, amp[26]); 
  FFV1_0(w[30], w[2], w[28], pars->GC_3, amp[27]); 
  FFV2_4_0(w[3], w[29], w[31], pars->GC_50, pars->GC_59, amp[28]); 
  FFV2_4_0(w[30], w[2], w[31], pars->GC_50, pars->GC_59, amp[29]); 
  FFV1_0(w[3], w[33], w[28], pars->GC_3, amp[30]); 
  FFV1_0(w[34], w[2], w[28], pars->GC_3, amp[31]); 
  FFV2_4_0(w[3], w[33], w[31], pars->GC_50, pars->GC_59, amp[32]); 
  FFV2_4_0(w[34], w[2], w[31], pars->GC_50, pars->GC_59, amp[33]); 
  VVS1_0(w[31], w[15], w[35], pars->GC_81, amp[34]); 
  VVS1_0(w[32], w[15], w[36], pars->GC_81, amp[35]); 
  FFV1_0(w[37], w[4], w[17], pars->GC_1, amp[36]); 
  FFV1_0(w[1], w[38], w[17], pars->GC_1, amp[37]); 
  FFV2_3_0(w[37], w[4], w[15], pars->GC_50, pars->GC_58, amp[38]); 
  FFV2_3_0(w[1], w[38], w[15], pars->GC_50, pars->GC_58, amp[39]); 
  FFV1_0(w[40], w[4], w[17], pars->GC_1, amp[40]); 
  FFV1_0(w[1], w[41], w[17], pars->GC_1, amp[41]); 
  FFV2_3_0(w[40], w[4], w[15], pars->GC_50, pars->GC_58, amp[42]); 
  FFV2_3_0(w[1], w[41], w[15], pars->GC_50, pars->GC_58, amp[43]); 
  FFV1_0(w[42], w[4], w[17], pars->GC_1, amp[44]); 
  FFV1_0(w[1], w[43], w[17], pars->GC_1, amp[45]); 
  FFV2_3_0(w[42], w[4], w[15], pars->GC_50, pars->GC_58, amp[46]); 
  FFV2_3_0(w[1], w[43], w[15], pars->GC_50, pars->GC_58, amp[47]); 
  FFV1_0(w[44], w[4], w[17], pars->GC_1, amp[48]); 
  FFV1_0(w[1], w[45], w[17], pars->GC_1, amp[49]); 
  FFV2_3_0(w[44], w[4], w[15], pars->GC_50, pars->GC_58, amp[50]); 
  FFV2_3_0(w[1], w[45], w[15], pars->GC_50, pars->GC_58, amp[51]); 
  FFV1_0(w[46], w[5], w[17], pars->GC_1, amp[52]); 
  FFV1_0(w[47], w[5], w[28], pars->GC_1, amp[53]); 
  FFV2_3_0(w[46], w[5], w[15], pars->GC_50, pars->GC_58, amp[54]); 
  FFV1_0(w[48], w[5], w[28], pars->GC_1, amp[55]); 
  FFV1_0(w[50], w[5], w[17], pars->GC_1, amp[56]); 
  FFV1_0(w[47], w[5], w[49], pars->GC_11, amp[57]); 
  FFV2_3_0(w[50], w[5], w[15], pars->GC_50, pars->GC_58, amp[58]); 
  FFV1_0(w[48], w[5], w[49], pars->GC_11, amp[59]); 
  FFV1_0(w[51], w[5], w[17], pars->GC_1, amp[60]); 
  FFS4_0(w[47], w[5], w[36], pars->GC_83, amp[61]); 
  FFV2_3_0(w[51], w[5], w[15], pars->GC_50, pars->GC_58, amp[62]); 
  FFS4_0(w[48], w[5], w[36], pars->GC_83, amp[63]); 
  FFV1_0(w[52], w[5], w[17], pars->GC_1, amp[64]); 
  FFV2_3_0(w[47], w[5], w[31], pars->GC_50, pars->GC_58, amp[65]); 
  FFV2_3_0(w[52], w[5], w[15], pars->GC_50, pars->GC_58, amp[66]); 
  FFV2_3_0(w[48], w[5], w[31], pars->GC_50, pars->GC_58, amp[67]); 
  FFV1_0(w[53], w[4], w[17], pars->GC_1, amp[68]); 
  FFV1_0(w[47], w[4], w[7], pars->GC_1, amp[69]); 
  FFV2_3_0(w[53], w[4], w[15], pars->GC_50, pars->GC_58, amp[70]); 
  FFV1_0(w[48], w[4], w[7], pars->GC_1, amp[71]); 
  FFV1_0(w[55], w[4], w[17], pars->GC_1, amp[72]); 
  FFV1_0(w[47], w[4], w[54], pars->GC_11, amp[73]); 
  FFV2_3_0(w[55], w[4], w[15], pars->GC_50, pars->GC_58, amp[74]); 
  FFV1_0(w[48], w[4], w[54], pars->GC_11, amp[75]); 
  FFV1_0(w[56], w[4], w[17], pars->GC_1, amp[76]); 
  FFS4_0(w[47], w[4], w[16], pars->GC_83, amp[77]); 
  FFV2_3_0(w[56], w[4], w[15], pars->GC_50, pars->GC_58, amp[78]); 
  FFS4_0(w[48], w[4], w[16], pars->GC_83, amp[79]); 
  FFV1_0(w[57], w[4], w[17], pars->GC_1, amp[80]); 
  FFV2_3_0(w[47], w[4], w[10], pars->GC_50, pars->GC_58, amp[81]); 
  FFV2_3_0(w[57], w[4], w[15], pars->GC_50, pars->GC_58, amp[82]); 
  FFV2_3_0(w[48], w[4], w[10], pars->GC_50, pars->GC_58, amp[83]); 
  FFV1_0(w[3], w[62], w[61], pars->GC_3, amp[84]); 
  FFV1_0(w[63], w[2], w[61], pars->GC_3, amp[85]); 
  FFV2_4_0(w[3], w[62], w[64], pars->GC_50, pars->GC_59, amp[86]); 
  FFV2_4_0(w[63], w[2], w[64], pars->GC_50, pars->GC_59, amp[87]); 
  FFV1_0(w[3], w[66], w[61], pars->GC_3, amp[88]); 
  FFV1_0(w[67], w[2], w[61], pars->GC_3, amp[89]); 
  FFV2_4_0(w[3], w[66], w[64], pars->GC_50, pars->GC_59, amp[90]); 
  FFV2_4_0(w[67], w[2], w[64], pars->GC_50, pars->GC_59, amp[91]); 
  VVS1_0(w[64], w[15], w[68], pars->GC_81, amp[92]); 
  VVS1_0(w[65], w[15], w[69], pars->GC_81, amp[93]); 
  FFV1_0(w[70], w[4], w[17], pars->GC_1, amp[94]); 
  FFV1_0(w[59], w[71], w[17], pars->GC_1, amp[95]); 
  FFV2_3_0(w[70], w[4], w[15], pars->GC_50, pars->GC_58, amp[96]); 
  FFV2_3_0(w[59], w[71], w[15], pars->GC_50, pars->GC_58, amp[97]); 
  FFV1_0(w[73], w[4], w[17], pars->GC_1, amp[98]); 
  FFV1_0(w[59], w[74], w[17], pars->GC_1, amp[99]); 
  FFV2_3_0(w[73], w[4], w[15], pars->GC_50, pars->GC_58, amp[100]); 
  FFV2_3_0(w[59], w[74], w[15], pars->GC_50, pars->GC_58, amp[101]); 
  FFV1_0(w[75], w[4], w[17], pars->GC_1, amp[102]); 
  FFV1_0(w[59], w[76], w[17], pars->GC_1, amp[103]); 
  FFV2_3_0(w[75], w[4], w[15], pars->GC_50, pars->GC_58, amp[104]); 
  FFV2_3_0(w[59], w[76], w[15], pars->GC_50, pars->GC_58, amp[105]); 
  FFV1_0(w[77], w[4], w[17], pars->GC_1, amp[106]); 
  FFV1_0(w[59], w[78], w[17], pars->GC_1, amp[107]); 
  FFV2_3_0(w[77], w[4], w[15], pars->GC_50, pars->GC_58, amp[108]); 
  FFV2_3_0(w[59], w[78], w[15], pars->GC_50, pars->GC_58, amp[109]); 
  FFV1_0(w[3], w[8], w[79], pars->GC_3, amp[110]); 
  FFV1_0(w[9], w[2], w[79], pars->GC_3, amp[111]); 
  FFV2_4_0(w[3], w[8], w[80], pars->GC_50, pars->GC_59, amp[112]); 
  FFV2_4_0(w[9], w[2], w[80], pars->GC_50, pars->GC_59, amp[113]); 
  FFV1_0(w[3], w[12], w[79], pars->GC_3, amp[114]); 
  FFV1_0(w[13], w[2], w[79], pars->GC_3, amp[115]); 
  FFV2_4_0(w[3], w[12], w[80], pars->GC_50, pars->GC_59, amp[116]); 
  FFV2_4_0(w[13], w[2], w[80], pars->GC_50, pars->GC_59, amp[117]); 
  VVS1_0(w[80], w[15], w[14], pars->GC_81, amp[118]); 
  VVS1_0(w[11], w[15], w[81], pars->GC_81, amp[119]); 
  FFV1_0(w[82], w[58], w[17], pars->GC_1, amp[120]); 
  FFV1_0(w[59], w[83], w[17], pars->GC_1, amp[121]); 
  FFV2_3_0(w[82], w[58], w[15], pars->GC_50, pars->GC_58, amp[122]); 
  FFV2_3_0(w[59], w[83], w[15], pars->GC_50, pars->GC_58, amp[123]); 
  FFV1_0(w[84], w[58], w[17], pars->GC_1, amp[124]); 
  FFV1_0(w[59], w[85], w[17], pars->GC_1, amp[125]); 
  FFV2_3_0(w[84], w[58], w[15], pars->GC_50, pars->GC_58, amp[126]); 
  FFV2_3_0(w[59], w[85], w[15], pars->GC_50, pars->GC_58, amp[127]); 
  FFV1_0(w[86], w[58], w[17], pars->GC_1, amp[128]); 
  FFV1_0(w[59], w[87], w[17], pars->GC_1, amp[129]); 
  FFV2_3_0(w[86], w[58], w[15], pars->GC_50, pars->GC_58, amp[130]); 
  FFV2_3_0(w[59], w[87], w[15], pars->GC_50, pars->GC_58, amp[131]); 
  FFV1_0(w[88], w[58], w[17], pars->GC_1, amp[132]); 
  FFV1_0(w[59], w[89], w[17], pars->GC_1, amp[133]); 
  FFV2_3_0(w[88], w[58], w[15], pars->GC_50, pars->GC_58, amp[134]); 
  FFV2_3_0(w[59], w[89], w[15], pars->GC_50, pars->GC_58, amp[135]); 
  FFV1_0(w[90], w[4], w[17], pars->GC_1, amp[136]); 
  FFV1_0(w[47], w[4], w[79], pars->GC_1, amp[137]); 
  FFV2_3_0(w[90], w[4], w[15], pars->GC_50, pars->GC_58, amp[138]); 
  FFV1_0(w[48], w[4], w[79], pars->GC_1, amp[139]); 
  FFV1_0(w[92], w[4], w[17], pars->GC_1, amp[140]); 
  FFV1_0(w[47], w[4], w[91], pars->GC_11, amp[141]); 
  FFV2_3_0(w[92], w[4], w[15], pars->GC_50, pars->GC_58, amp[142]); 
  FFV1_0(w[48], w[4], w[91], pars->GC_11, amp[143]); 
  FFV1_0(w[93], w[4], w[17], pars->GC_1, amp[144]); 
  FFS4_0(w[47], w[4], w[81], pars->GC_83, amp[145]); 
  FFV2_3_0(w[93], w[4], w[15], pars->GC_50, pars->GC_58, amp[146]); 
  FFS4_0(w[48], w[4], w[81], pars->GC_83, amp[147]); 
  FFV1_0(w[94], w[4], w[17], pars->GC_1, amp[148]); 
  FFV2_3_0(w[47], w[4], w[80], pars->GC_50, pars->GC_58, amp[149]); 
  FFV2_3_0(w[94], w[4], w[15], pars->GC_50, pars->GC_58, amp[150]); 
  FFV2_3_0(w[48], w[4], w[80], pars->GC_50, pars->GC_58, amp[151]); 
  FFV1_0(w[95], w[58], w[17], pars->GC_1, amp[152]); 
  FFV1_0(w[47], w[58], w[61], pars->GC_1, amp[153]); 
  FFV2_3_0(w[95], w[58], w[15], pars->GC_50, pars->GC_58, amp[154]); 
  FFV1_0(w[48], w[58], w[61], pars->GC_1, amp[155]); 
  FFV1_0(w[97], w[58], w[17], pars->GC_1, amp[156]); 
  FFV1_0(w[47], w[58], w[96], pars->GC_11, amp[157]); 
  FFV2_3_0(w[97], w[58], w[15], pars->GC_50, pars->GC_58, amp[158]); 
  FFV1_0(w[48], w[58], w[96], pars->GC_11, amp[159]); 
  FFV1_0(w[98], w[58], w[17], pars->GC_1, amp[160]); 
  FFS4_0(w[47], w[58], w[69], pars->GC_83, amp[161]); 
  FFV2_3_0(w[98], w[58], w[15], pars->GC_50, pars->GC_58, amp[162]); 
  FFS4_0(w[48], w[58], w[69], pars->GC_83, amp[163]); 
  FFV1_0(w[99], w[58], w[17], pars->GC_1, amp[164]); 
  FFV2_3_0(w[47], w[58], w[64], pars->GC_50, pars->GC_58, amp[165]); 
  FFV2_3_0(w[99], w[58], w[15], pars->GC_50, pars->GC_58, amp[166]); 
  FFV2_3_0(w[48], w[58], w[64], pars->GC_50, pars->GC_58, amp[167]); 
  FFV1_0(w[3], w[103], w[79], pars->GC_3, amp[168]); 
  FFV1_0(w[104], w[2], w[79], pars->GC_3, amp[169]); 
  FFV2_4_0(w[3], w[103], w[80], pars->GC_50, pars->GC_59, amp[170]); 
  FFV2_4_0(w[104], w[2], w[80], pars->GC_50, pars->GC_59, amp[171]); 
  FFV1_0(w[3], w[106], w[79], pars->GC_3, amp[172]); 
  FFV1_0(w[107], w[2], w[79], pars->GC_3, amp[173]); 
  FFV2_4_0(w[3], w[106], w[80], pars->GC_50, pars->GC_59, amp[174]); 
  FFV2_4_0(w[107], w[2], w[80], pars->GC_50, pars->GC_59, amp[175]); 
  VVS1_0(w[80], w[15], w[108], pars->GC_81, amp[176]); 
  VVS1_0(w[105], w[15], w[81], pars->GC_81, amp[177]); 
  FFV1_0(w[109], w[58], w[17], pars->GC_1, amp[178]); 
  FFV1_0(w[59], w[110], w[17], pars->GC_1, amp[179]); 
  FFV2_3_0(w[109], w[58], w[15], pars->GC_50, pars->GC_58, amp[180]); 
  FFV2_3_0(w[59], w[110], w[15], pars->GC_50, pars->GC_58, amp[181]); 
  FFV1_0(w[112], w[58], w[17], pars->GC_1, amp[182]); 
  FFV1_0(w[59], w[113], w[17], pars->GC_1, amp[183]); 
  FFV2_3_0(w[112], w[58], w[15], pars->GC_50, pars->GC_58, amp[184]); 
  FFV2_3_0(w[59], w[113], w[15], pars->GC_50, pars->GC_58, amp[185]); 
  FFV1_0(w[114], w[58], w[17], pars->GC_1, amp[186]); 
  FFV1_0(w[59], w[115], w[17], pars->GC_1, amp[187]); 
  FFV2_3_0(w[114], w[58], w[15], pars->GC_50, pars->GC_58, amp[188]); 
  FFV2_3_0(w[59], w[115], w[15], pars->GC_50, pars->GC_58, amp[189]); 
  FFV1_0(w[116], w[58], w[17], pars->GC_1, amp[190]); 
  FFV1_0(w[59], w[117], w[17], pars->GC_1, amp[191]); 
  FFV2_3_0(w[116], w[58], w[15], pars->GC_50, pars->GC_58, amp[192]); 
  FFV2_3_0(w[59], w[117], w[15], pars->GC_50, pars->GC_58, amp[193]); 
  FFV1_0(w[3], w[120], w[119], pars->GC_3, amp[194]); 
  FFV1_0(w[121], w[2], w[119], pars->GC_3, amp[195]); 
  FFV2_4_0(w[3], w[120], w[122], pars->GC_50, pars->GC_59, amp[196]); 
  FFV2_4_0(w[121], w[2], w[122], pars->GC_50, pars->GC_59, amp[197]); 
  FFV1_0(w[3], w[124], w[119], pars->GC_3, amp[198]); 
  FFV1_0(w[125], w[2], w[119], pars->GC_3, amp[199]); 
  FFV2_4_0(w[3], w[124], w[122], pars->GC_50, pars->GC_59, amp[200]); 
  FFV2_4_0(w[125], w[2], w[122], pars->GC_50, pars->GC_59, amp[201]); 
  VVS1_0(w[122], w[15], w[126], pars->GC_81, amp[202]); 
  VVS1_0(w[123], w[15], w[127], pars->GC_81, amp[203]); 
  FFV1_0(w[128], w[100], w[17], pars->GC_1, amp[204]); 
  FFV1_0(w[59], w[129], w[17], pars->GC_1, amp[205]); 
  FFV2_3_0(w[128], w[100], w[15], pars->GC_50, pars->GC_58, amp[206]); 
  FFV2_3_0(w[59], w[129], w[15], pars->GC_50, pars->GC_58, amp[207]); 
  FFV1_0(w[131], w[100], w[17], pars->GC_1, amp[208]); 
  FFV1_0(w[59], w[132], w[17], pars->GC_1, amp[209]); 
  FFV2_3_0(w[131], w[100], w[15], pars->GC_50, pars->GC_58, amp[210]); 
  FFV2_3_0(w[59], w[132], w[15], pars->GC_50, pars->GC_58, amp[211]); 
  FFV1_0(w[133], w[100], w[17], pars->GC_1, amp[212]); 
  FFV1_0(w[59], w[134], w[17], pars->GC_1, amp[213]); 
  FFV2_3_0(w[133], w[100], w[15], pars->GC_50, pars->GC_58, amp[214]); 
  FFV2_3_0(w[59], w[134], w[15], pars->GC_50, pars->GC_58, amp[215]); 
  FFV1_0(w[135], w[100], w[17], pars->GC_1, amp[216]); 
  FFV1_0(w[59], w[136], w[17], pars->GC_1, amp[217]); 
  FFV2_3_0(w[135], w[100], w[15], pars->GC_50, pars->GC_58, amp[218]); 
  FFV2_3_0(w[59], w[136], w[15], pars->GC_50, pars->GC_58, amp[219]); 
  FFV1_0(w[137], w[58], w[17], pars->GC_1, amp[220]); 
  FFV1_0(w[138], w[58], w[119], pars->GC_1, amp[221]); 
  FFV2_3_0(w[137], w[58], w[15], pars->GC_50, pars->GC_58, amp[222]); 
  FFV1_0(w[139], w[58], w[119], pars->GC_1, amp[223]); 
  FFV1_0(w[141], w[58], w[17], pars->GC_1, amp[224]); 
  FFV1_0(w[138], w[58], w[140], pars->GC_11, amp[225]); 
  FFV2_3_0(w[141], w[58], w[15], pars->GC_50, pars->GC_58, amp[226]); 
  FFV1_0(w[139], w[58], w[140], pars->GC_11, amp[227]); 
  FFV1_0(w[142], w[58], w[17], pars->GC_1, amp[228]); 
  FFS4_0(w[138], w[58], w[127], pars->GC_83, amp[229]); 
  FFV2_3_0(w[142], w[58], w[15], pars->GC_50, pars->GC_58, amp[230]); 
  FFS4_0(w[139], w[58], w[127], pars->GC_83, amp[231]); 
  FFV1_0(w[143], w[58], w[17], pars->GC_1, amp[232]); 
  FFV2_3_0(w[138], w[58], w[122], pars->GC_50, pars->GC_58, amp[233]); 
  FFV2_3_0(w[143], w[58], w[15], pars->GC_50, pars->GC_58, amp[234]); 
  FFV2_3_0(w[139], w[58], w[122], pars->GC_50, pars->GC_58, amp[235]); 
  FFV1_0(w[144], w[100], w[17], pars->GC_1, amp[236]); 
  FFV1_0(w[138], w[100], w[79], pars->GC_1, amp[237]); 
  FFV2_3_0(w[144], w[100], w[15], pars->GC_50, pars->GC_58, amp[238]); 
  FFV1_0(w[139], w[100], w[79], pars->GC_1, amp[239]); 
  FFV1_0(w[145], w[100], w[17], pars->GC_1, amp[240]); 
  FFV1_0(w[138], w[100], w[91], pars->GC_11, amp[241]); 
  FFV2_3_0(w[145], w[100], w[15], pars->GC_50, pars->GC_58, amp[242]); 
  FFV1_0(w[139], w[100], w[91], pars->GC_11, amp[243]); 
  FFV1_0(w[146], w[100], w[17], pars->GC_1, amp[244]); 
  FFS4_0(w[138], w[100], w[81], pars->GC_83, amp[245]); 
  FFV2_3_0(w[146], w[100], w[15], pars->GC_50, pars->GC_58, amp[246]); 
  FFS4_0(w[139], w[100], w[81], pars->GC_83, amp[247]); 
  FFV1_0(w[147], w[100], w[17], pars->GC_1, amp[248]); 
  FFV2_3_0(w[138], w[100], w[80], pars->GC_50, pars->GC_58, amp[249]); 
  FFV2_3_0(w[147], w[100], w[15], pars->GC_50, pars->GC_58, amp[250]); 
  FFV2_3_0(w[139], w[100], w[80], pars->GC_50, pars->GC_58, amp[251]); 
  FFV2_0(w[3], w[148], w[10], pars->GC_62, amp[252]); 
  FFV2_0(w[149], w[2], w[10], pars->GC_62, amp[253]); 
  VVS1_0(w[10], w[150], w[14], pars->GC_81, amp[254]); 
  VVS1_0(w[11], w[150], w[16], pars->GC_81, amp[255]); 
  FFV2_3_0(w[18], w[5], w[150], pars->GC_50, pars->GC_58, amp[256]); 
  FFV2_3_0(w[1], w[19], w[150], pars->GC_50, pars->GC_58, amp[257]); 
  FFV2_3_0(w[21], w[5], w[150], pars->GC_50, pars->GC_58, amp[258]); 
  FFV2_3_0(w[1], w[22], w[150], pars->GC_50, pars->GC_58, amp[259]); 
  FFV2_3_0(w[23], w[5], w[150], pars->GC_50, pars->GC_58, amp[260]); 
  FFV2_3_0(w[1], w[24], w[150], pars->GC_50, pars->GC_58, amp[261]); 
  FFV2_3_0(w[25], w[5], w[150], pars->GC_50, pars->GC_58, amp[262]); 
  FFV2_3_0(w[1], w[26], w[150], pars->GC_50, pars->GC_58, amp[263]); 
  FFV2_0(w[3], w[151], w[31], pars->GC_62, amp[264]); 
  FFV2_0(w[152], w[2], w[31], pars->GC_62, amp[265]); 
  VVS1_0(w[31], w[150], w[35], pars->GC_81, amp[266]); 
  VVS1_0(w[32], w[150], w[36], pars->GC_81, amp[267]); 
  FFV2_3_0(w[37], w[4], w[150], pars->GC_50, pars->GC_58, amp[268]); 
  FFV2_3_0(w[1], w[38], w[150], pars->GC_50, pars->GC_58, amp[269]); 
  FFV2_3_0(w[40], w[4], w[150], pars->GC_50, pars->GC_58, amp[270]); 
  FFV2_3_0(w[1], w[41], w[150], pars->GC_50, pars->GC_58, amp[271]); 
  FFV2_3_0(w[42], w[4], w[150], pars->GC_50, pars->GC_58, amp[272]); 
  FFV2_3_0(w[1], w[43], w[150], pars->GC_50, pars->GC_58, amp[273]); 
  FFV2_3_0(w[44], w[4], w[150], pars->GC_50, pars->GC_58, amp[274]); 
  FFV2_3_0(w[1], w[45], w[150], pars->GC_50, pars->GC_58, amp[275]); 
  FFV2_3_0(w[46], w[5], w[150], pars->GC_50, pars->GC_58, amp[276]); 
  FFV1_0(w[153], w[5], w[28], pars->GC_1, amp[277]); 
  FFV2_3_0(w[50], w[5], w[150], pars->GC_50, pars->GC_58, amp[278]); 
  FFV1_0(w[153], w[5], w[49], pars->GC_11, amp[279]); 
  FFV2_3_0(w[51], w[5], w[150], pars->GC_50, pars->GC_58, amp[280]); 
  FFS4_0(w[153], w[5], w[36], pars->GC_83, amp[281]); 
  FFV2_3_0(w[52], w[5], w[150], pars->GC_50, pars->GC_58, amp[282]); 
  FFV2_3_0(w[153], w[5], w[31], pars->GC_50, pars->GC_58, amp[283]); 
  FFV2_3_0(w[53], w[4], w[150], pars->GC_50, pars->GC_58, amp[284]); 
  FFV1_0(w[153], w[4], w[7], pars->GC_1, amp[285]); 
  FFV2_3_0(w[55], w[4], w[150], pars->GC_50, pars->GC_58, amp[286]); 
  FFV1_0(w[153], w[4], w[54], pars->GC_11, amp[287]); 
  FFV2_3_0(w[56], w[4], w[150], pars->GC_50, pars->GC_58, amp[288]); 
  FFS4_0(w[153], w[4], w[16], pars->GC_83, amp[289]); 
  FFV2_3_0(w[57], w[4], w[150], pars->GC_50, pars->GC_58, amp[290]); 
  FFV2_3_0(w[153], w[4], w[10], pars->GC_50, pars->GC_58, amp[291]); 
  FFV2_0(w[3], w[154], w[64], pars->GC_62, amp[292]); 
  FFV2_0(w[155], w[2], w[64], pars->GC_62, amp[293]); 
  VVS1_0(w[64], w[150], w[68], pars->GC_81, amp[294]); 
  VVS1_0(w[65], w[150], w[69], pars->GC_81, amp[295]); 
  FFV2_3_0(w[70], w[4], w[150], pars->GC_50, pars->GC_58, amp[296]); 
  FFV2_3_0(w[59], w[71], w[150], pars->GC_50, pars->GC_58, amp[297]); 
  FFV2_3_0(w[73], w[4], w[150], pars->GC_50, pars->GC_58, amp[298]); 
  FFV2_3_0(w[59], w[74], w[150], pars->GC_50, pars->GC_58, amp[299]); 
  FFV2_3_0(w[75], w[4], w[150], pars->GC_50, pars->GC_58, amp[300]); 
  FFV2_3_0(w[59], w[76], w[150], pars->GC_50, pars->GC_58, amp[301]); 
  FFV2_3_0(w[77], w[4], w[150], pars->GC_50, pars->GC_58, amp[302]); 
  FFV2_3_0(w[59], w[78], w[150], pars->GC_50, pars->GC_58, amp[303]); 
  FFV2_0(w[3], w[148], w[80], pars->GC_62, amp[304]); 
  FFV2_0(w[149], w[2], w[80], pars->GC_62, amp[305]); 
  VVS1_0(w[80], w[150], w[14], pars->GC_81, amp[306]); 
  VVS1_0(w[11], w[150], w[81], pars->GC_81, amp[307]); 
  FFV2_3_0(w[82], w[58], w[150], pars->GC_50, pars->GC_58, amp[308]); 
  FFV2_3_0(w[59], w[83], w[150], pars->GC_50, pars->GC_58, amp[309]); 
  FFV2_3_0(w[84], w[58], w[150], pars->GC_50, pars->GC_58, amp[310]); 
  FFV2_3_0(w[59], w[85], w[150], pars->GC_50, pars->GC_58, amp[311]); 
  FFV2_3_0(w[86], w[58], w[150], pars->GC_50, pars->GC_58, amp[312]); 
  FFV2_3_0(w[59], w[87], w[150], pars->GC_50, pars->GC_58, amp[313]); 
  FFV2_3_0(w[88], w[58], w[150], pars->GC_50, pars->GC_58, amp[314]); 
  FFV2_3_0(w[59], w[89], w[150], pars->GC_50, pars->GC_58, amp[315]); 
  FFV2_3_0(w[90], w[4], w[150], pars->GC_50, pars->GC_58, amp[316]); 
  FFV1_0(w[153], w[4], w[79], pars->GC_1, amp[317]); 
  FFV2_3_0(w[92], w[4], w[150], pars->GC_50, pars->GC_58, amp[318]); 
  FFV1_0(w[153], w[4], w[91], pars->GC_11, amp[319]); 
  FFV2_3_0(w[93], w[4], w[150], pars->GC_50, pars->GC_58, amp[320]); 
  FFS4_0(w[153], w[4], w[81], pars->GC_83, amp[321]); 
  FFV2_3_0(w[94], w[4], w[150], pars->GC_50, pars->GC_58, amp[322]); 
  FFV2_3_0(w[153], w[4], w[80], pars->GC_50, pars->GC_58, amp[323]); 
  FFV2_3_0(w[95], w[58], w[150], pars->GC_50, pars->GC_58, amp[324]); 
  FFV1_0(w[153], w[58], w[61], pars->GC_1, amp[325]); 
  FFV2_3_0(w[97], w[58], w[150], pars->GC_50, pars->GC_58, amp[326]); 
  FFV1_0(w[153], w[58], w[96], pars->GC_11, amp[327]); 
  FFV2_3_0(w[98], w[58], w[150], pars->GC_50, pars->GC_58, amp[328]); 
  FFS4_0(w[153], w[58], w[69], pars->GC_83, amp[329]); 
  FFV2_3_0(w[99], w[58], w[150], pars->GC_50, pars->GC_58, amp[330]); 
  FFV2_3_0(w[153], w[58], w[64], pars->GC_50, pars->GC_58, amp[331]); 
  FFV2_0(w[3], w[156], w[80], pars->GC_62, amp[332]); 
  FFV2_0(w[157], w[2], w[80], pars->GC_62, amp[333]); 
  VVS1_0(w[80], w[150], w[108], pars->GC_81, amp[334]); 
  VVS1_0(w[105], w[150], w[81], pars->GC_81, amp[335]); 
  FFV2_3_0(w[109], w[58], w[150], pars->GC_50, pars->GC_58, amp[336]); 
  FFV2_3_0(w[59], w[110], w[150], pars->GC_50, pars->GC_58, amp[337]); 
  FFV2_3_0(w[112], w[58], w[150], pars->GC_50, pars->GC_58, amp[338]); 
  FFV2_3_0(w[59], w[113], w[150], pars->GC_50, pars->GC_58, amp[339]); 
  FFV2_3_0(w[114], w[58], w[150], pars->GC_50, pars->GC_58, amp[340]); 
  FFV2_3_0(w[59], w[115], w[150], pars->GC_50, pars->GC_58, amp[341]); 
  FFV2_3_0(w[116], w[58], w[150], pars->GC_50, pars->GC_58, amp[342]); 
  FFV2_3_0(w[59], w[117], w[150], pars->GC_50, pars->GC_58, amp[343]); 
  FFV2_0(w[3], w[158], w[122], pars->GC_62, amp[344]); 
  FFV2_0(w[159], w[2], w[122], pars->GC_62, amp[345]); 
  VVS1_0(w[122], w[150], w[126], pars->GC_81, amp[346]); 
  VVS1_0(w[123], w[150], w[127], pars->GC_81, amp[347]); 
  FFV2_3_0(w[128], w[100], w[150], pars->GC_50, pars->GC_58, amp[348]); 
  FFV2_3_0(w[59], w[129], w[150], pars->GC_50, pars->GC_58, amp[349]); 
  FFV2_3_0(w[131], w[100], w[150], pars->GC_50, pars->GC_58, amp[350]); 
  FFV2_3_0(w[59], w[132], w[150], pars->GC_50, pars->GC_58, amp[351]); 
  FFV2_3_0(w[133], w[100], w[150], pars->GC_50, pars->GC_58, amp[352]); 
  FFV2_3_0(w[59], w[134], w[150], pars->GC_50, pars->GC_58, amp[353]); 
  FFV2_3_0(w[135], w[100], w[150], pars->GC_50, pars->GC_58, amp[354]); 
  FFV2_3_0(w[59], w[136], w[150], pars->GC_50, pars->GC_58, amp[355]); 
  FFV2_3_0(w[137], w[58], w[150], pars->GC_50, pars->GC_58, amp[356]); 
  FFV1_0(w[160], w[58], w[119], pars->GC_1, amp[357]); 
  FFV2_3_0(w[141], w[58], w[150], pars->GC_50, pars->GC_58, amp[358]); 
  FFV1_0(w[160], w[58], w[140], pars->GC_11, amp[359]); 
  FFV2_3_0(w[142], w[58], w[150], pars->GC_50, pars->GC_58, amp[360]); 
  FFS4_0(w[160], w[58], w[127], pars->GC_83, amp[361]); 
  FFV2_3_0(w[143], w[58], w[150], pars->GC_50, pars->GC_58, amp[362]); 
  FFV2_3_0(w[160], w[58], w[122], pars->GC_50, pars->GC_58, amp[363]); 
  FFV2_3_0(w[144], w[100], w[150], pars->GC_50, pars->GC_58, amp[364]); 
  FFV1_0(w[160], w[100], w[79], pars->GC_1, amp[365]); 
  FFV2_3_0(w[145], w[100], w[150], pars->GC_50, pars->GC_58, amp[366]); 
  FFV1_0(w[160], w[100], w[91], pars->GC_11, amp[367]); 
  FFV2_3_0(w[146], w[100], w[150], pars->GC_50, pars->GC_58, amp[368]); 
  FFS4_0(w[160], w[100], w[81], pars->GC_83, amp[369]); 
  FFV2_3_0(w[147], w[100], w[150], pars->GC_50, pars->GC_58, amp[370]); 
  FFV2_3_0(w[160], w[100], w[80], pars->GC_50, pars->GC_58, amp[371]); 


}
double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bb_emepbb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 84;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[0] + amp[1] + amp[2] + amp[3] + amp[4] + amp[5] + amp[6] +
      amp[7] + amp[8] + amp[9] + amp[10] + amp[11] + amp[12] + amp[13] - 1./6.
      * amp[14] - 1./6. * amp[15] - 1./6. * amp[16] - 1./6. * amp[17] + amp[18]
      + amp[19] + amp[20] + amp[21] + amp[22] + amp[23] + amp[24] + amp[25] -
      1./2. * amp[40] - 1./2. * amp[41] - 1./2. * amp[42] - 1./2. * amp[43] -
      1./2. * amp[56] - 1./2. * amp[57] - 1./2. * amp[58] - 1./2. * amp[59] +
      amp[68] + amp[69] + amp[70] + amp[71] - 1./6. * amp[72] - 1./6. * amp[73]
      - 1./6. * amp[74] - 1./6. * amp[75] + amp[76] + amp[77] + amp[78] +
      amp[79] + amp[80] + amp[81] + amp[82] + amp[83];
  jamp[1] = +1./2. * amp[14] + 1./2. * amp[15] + 1./2. * amp[16] + 1./2. *
      amp[17] - amp[26] - amp[27] - amp[28] - amp[29] - amp[30] - amp[31] -
      amp[32] - amp[33] - amp[34] - amp[35] - amp[36] - amp[37] - amp[38] -
      amp[39] + 1./6. * amp[40] + 1./6. * amp[41] + 1./6. * amp[42] + 1./6. *
      amp[43] - amp[44] - amp[45] - amp[46] - amp[47] - amp[48] - amp[49] -
      amp[50] - amp[51] - amp[52] - amp[53] - amp[54] - amp[55] + 1./6. *
      amp[56] + 1./6. * amp[57] + 1./6. * amp[58] + 1./6. * amp[59] - amp[60] -
      amp[61] - amp[62] - amp[63] - amp[64] - amp[65] - amp[66] - amp[67] +
      1./2. * amp[72] + 1./2. * amp[73] + 1./2. * amp[74] + 1./2. * amp[75];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bbx_emepbbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 84;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[84] + amp[85] + amp[86] + amp[87] + amp[88] + amp[89] +
      amp[90] + amp[91] + amp[92] + amp[93] + amp[94] + amp[95] + amp[96] +
      amp[97] - 1./6. * amp[98] - 1./6. * amp[99] - 1./6. * amp[100] - 1./6. *
      amp[101] + amp[102] + amp[103] + amp[104] + amp[105] + amp[106] +
      amp[107] + amp[108] + amp[109] - 1./2. * amp[124] - 1./2. * amp[125] -
      1./2. * amp[126] - 1./2. * amp[127] - 1./2. * amp[140] - 1./2. * amp[141]
      - 1./2. * amp[142] - 1./2. * amp[143] + amp[152] + amp[153] + amp[154] +
      amp[155] - 1./6. * amp[156] - 1./6. * amp[157] - 1./6. * amp[158] - 1./6.
      * amp[159] + amp[160] + amp[161] + amp[162] + amp[163] + amp[164] +
      amp[165] + amp[166] + amp[167];
  jamp[1] = +1./2. * amp[98] + 1./2. * amp[99] + 1./2. * amp[100] + 1./2. *
      amp[101] - amp[110] - amp[111] - amp[112] - amp[113] - amp[114] -
      amp[115] - amp[116] - amp[117] - amp[118] - amp[119] - amp[120] -
      amp[121] - amp[122] - amp[123] + 1./6. * amp[124] + 1./6. * amp[125] +
      1./6. * amp[126] + 1./6. * amp[127] - amp[128] - amp[129] - amp[130] -
      amp[131] - amp[132] - amp[133] - amp[134] - amp[135] - amp[136] -
      amp[137] - amp[138] - amp[139] + 1./6. * amp[140] + 1./6. * amp[141] +
      1./6. * amp[142] + 1./6. * amp[143] - amp[144] - amp[145] - amp[146] -
      amp[147] - amp[148] - amp[149] - amp[150] - amp[151] + 1./2. * amp[156] +
      1./2. * amp[157] + 1./2. * amp[158] + 1./2. * amp[159];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bxbx_emepbxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 84;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[168] + amp[169] + amp[170] + amp[171] + amp[172] + amp[173] +
      amp[174] + amp[175] + amp[176] + amp[177] + amp[178] + amp[179] +
      amp[180] + amp[181] - 1./6. * amp[182] - 1./6. * amp[183] - 1./6. *
      amp[184] - 1./6. * amp[185] + amp[186] + amp[187] + amp[188] + amp[189] +
      amp[190] + amp[191] + amp[192] + amp[193] - 1./2. * amp[208] - 1./2. *
      amp[209] - 1./2. * amp[210] - 1./2. * amp[211] - 1./2. * amp[224] - 1./2.
      * amp[225] - 1./2. * amp[226] - 1./2. * amp[227] + amp[236] + amp[237] +
      amp[238] + amp[239] - 1./6. * amp[240] - 1./6. * amp[241] - 1./6. *
      amp[242] - 1./6. * amp[243] + amp[244] + amp[245] + amp[246] + amp[247] +
      amp[248] + amp[249] + amp[250] + amp[251];
  jamp[1] = +1./2. * amp[182] + 1./2. * amp[183] + 1./2. * amp[184] + 1./2. *
      amp[185] - amp[194] - amp[195] - amp[196] - amp[197] - amp[198] -
      amp[199] - amp[200] - amp[201] - amp[202] - amp[203] - amp[204] -
      amp[205] - amp[206] - amp[207] + 1./6. * amp[208] + 1./6. * amp[209] +
      1./6. * amp[210] + 1./6. * amp[211] - amp[212] - amp[213] - amp[214] -
      amp[215] - amp[216] - amp[217] - amp[218] - amp[219] - amp[220] -
      amp[221] - amp[222] - amp[223] + 1./6. * amp[224] + 1./6. * amp[225] +
      1./6. * amp[226] + 1./6. * amp[227] - amp[228] - amp[229] - amp[230] -
      amp[231] - amp[232] - amp[233] - amp[234] - amp[235] + 1./2. * amp[240] +
      1./2. * amp[241] + 1./2. * amp[242] + 1./2. * amp[243];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bb_vevexbb() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 40;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[252] + amp[253] + amp[254] + amp[255] + amp[256] + amp[257] -
      1./6. * amp[258] - 1./6. * amp[259] + amp[260] + amp[261] + amp[262] +
      amp[263] - 1./2. * amp[270] - 1./2. * amp[271] - 1./2. * amp[278] - 1./2.
      * amp[279] + amp[284] + amp[285] - 1./6. * amp[286] - 1./6. * amp[287] +
      amp[288] + amp[289] + amp[290] + amp[291];
  jamp[1] = +1./2. * amp[258] + 1./2. * amp[259] - amp[264] - amp[265] -
      amp[266] - amp[267] - amp[268] - amp[269] + 1./6. * amp[270] + 1./6. *
      amp[271] - amp[272] - amp[273] - amp[274] - amp[275] - amp[276] -
      amp[277] + 1./6. * amp[278] + 1./6. * amp[279] - amp[280] - amp[281] -
      amp[282] - amp[283] + 1./2. * amp[286] + 1./2. * amp[287];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bbx_vevexbbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 40;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[292] + amp[293] + amp[294] + amp[295] + amp[296] + amp[297] -
      1./6. * amp[298] - 1./6. * amp[299] + amp[300] + amp[301] + amp[302] +
      amp[303] - 1./2. * amp[310] - 1./2. * amp[311] - 1./2. * amp[318] - 1./2.
      * amp[319] + amp[324] + amp[325] - 1./6. * amp[326] - 1./6. * amp[327] +
      amp[328] + amp[329] + amp[330] + amp[331];
  jamp[1] = +1./2. * amp[298] + 1./2. * amp[299] - amp[304] - amp[305] -
      amp[306] - amp[307] - amp[308] - amp[309] + 1./6. * amp[310] + 1./6. *
      amp[311] - amp[312] - amp[313] - amp[314] - amp[315] - amp[316] -
      amp[317] + 1./6. * amp[318] + 1./6. * amp[319] - amp[320] - amp[321] -
      amp[322] - amp[323] + 1./2. * amp[326] + 1./2. * amp[327];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

double PY8MEs_R7_P0_sm_bb_llbb::matrix_7_bxbx_vevexbxbx() 
{
  int i, j; 
  // Local variables
  // const int ngraphs = 40;
  const int ncolor = 2; 
  Complex<double> ztemp; 
  Complex<double> jamp[ncolor]; 
  // The color matrix;
  static const double denom[ncolor] = {1, 1}; 
  static const double cf[ncolor][ncolor] = {{9, 3}, {3, 9}}; 

  // Calculate color flows
  jamp[0] = +amp[332] + amp[333] + amp[334] + amp[335] + amp[336] + amp[337] -
      1./6. * amp[338] - 1./6. * amp[339] + amp[340] + amp[341] + amp[342] +
      amp[343] - 1./2. * amp[350] - 1./2. * amp[351] - 1./2. * amp[358] - 1./2.
      * amp[359] + amp[364] + amp[365] - 1./6. * amp[366] - 1./6. * amp[367] +
      amp[368] + amp[369] + amp[370] + amp[371];
  jamp[1] = +1./2. * amp[338] + 1./2. * amp[339] - amp[344] - amp[345] -
      amp[346] - amp[347] - amp[348] - amp[349] + 1./6. * amp[350] + 1./6. *
      amp[351] - amp[352] - amp[353] - amp[354] - amp[355] - amp[356] -
      amp[357] + 1./6. * amp[358] + 1./6. * amp[359] - amp[360] - amp[361] -
      amp[362] - amp[363] + 1./2. * amp[366] + 1./2. * amp[367];

  // Sum and square the color flows to get the matrix element
  double matrix = 0; 
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

