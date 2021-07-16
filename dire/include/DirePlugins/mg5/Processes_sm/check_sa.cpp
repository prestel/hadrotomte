#include <iostream> 
#include <sstream> 
#include <iomanip> 
#include <vector> 
#include <set> 

#include "PY8ME.h"
#include "PY8MEs.h"
#include "rambo.h"

using namespace std; 

typedef vector<double> vec_double; 

// Nice string to display a process
string proc_string(vector<int> in_pdgs, vector<int> out_pdgs, set<int> 
req_s_channels = set<int> ())
{

  std::stringstream ss; 

  for (unsigned int i = 0; i < in_pdgs.size(); i++ )
    ss << in_pdgs[i] <<  " "; 
  if (req_s_channels.size() > 0)
  {
    ss <<  "> "; 
    for (set<int> ::iterator it = req_s_channels.begin(); it != 
      req_s_channels.end(); ++ it)
    ss << * it <<  " "; 
  }
  ss <<  "> "; 
  for (unsigned int i = 0; i < out_pdgs.size(); i++ )
  {
    ss << out_pdgs[i]; 
    if (i != (out_pdgs.size() - 1))
      ss <<  " "; 
  }

  return ss.str(); 
}

// Evaluate a given process with an accessor
void run_proc(PY8MEs_namespace::PY8MEs& accessor, vector<int> in_pdgs,
    vector<int> out_pdgs, set<int> req_s_channels = set<int> ())
{

  // This is not mandatory, we run it here only because we need an instance of
  // the process
  // to obtain the external masses to generate the PS point.
  PY8MEs_namespace::PY8ME * query = accessor.getProcess(in_pdgs, out_pdgs,
      req_s_channels);

  cout <<  " -> Process '"; 
  cout << proc_string(in_pdgs, out_pdgs, req_s_channels) <<  "'"; 
  if (query)
  {
    cout <<  " is available." << endl; 
  }
  else
  {
    cout <<  " is not available." << endl; 
    return; 
  }

  double energy = 1500; 
  double weight; 

  vector < vec_double > p_vec = vector < vec_double > (in_pdgs.size() +
      out_pdgs.size(), vec_double(4, 0.));

  //----
  // The line below 'get_momenta' that uses RAMBO has memory leaks. It is fine
  // for testing/debugging.
  // But replace with an hard-coded momentum configuration if you want to
  // memory-check the ME code.
  //----
  // Get phase space point
  vector < double * > p = get_momenta(in_pdgs.size(), energy,
      query->getMasses(), weight);
  // Cast to a sane type
  for (unsigned int i = 0; i < in_pdgs.size() + out_pdgs.size(); i++ )
  {
    for (unsigned int j = 0; j < 4; j++ )
    {
      p_vec[i][j] = p[i][j]; 
      // Copy-paste the printout below in this code to use an hard-coded
      // momentum configuration
      // cout<<setiosflags(ios::scientific) << setprecision(14) <<
      // setw(22)<<"p_vec["<<i<<"]["<<j<<"]"<<"="<<p_vec[i][j]<<";"<<endl;
    }
  }
  // Release arrays
  for(unsigned int i = 0; i < (in_pdgs.size() + out_pdgs.size()); i++ )
  {
    delete[] p[i]; 
    p[i] = NULL; 
  }
  //---
  // End of the segment that can cause memory leak.
  //---

  // You could require specific helicity and quantum numbers here
  // (these arguments, like req_s_channels are optional for calculateME and
  // considerd empty by default)
  // They are left empty here, meaning that these quantum numbers will be
  // summed/averaged over.
  // This vector's size would be twice the number of external legs (for color
  // and anti-color specification)
  vector<int> colors(0); 
  // This vector's size would be the number of external legs
  vector<int> helicities(0); 
  pair < double, bool > res = accessor.calculateME(in_pdgs, out_pdgs, p_vec,
      req_s_channels, colors, helicities);

  if ( !res.second)
  {
    cout <<  " | Its evaluation failed." << endl; 
    return; 
  }
  else
  {
    cout <<  " | Momenta:" << endl; 
    for(unsigned int i = 0; i < (in_pdgs.size() + out_pdgs.size()); i++ )
      cout <<  " | " << setw(4) << i + 1
     << setiosflags(ios::scientific) << setprecision(14) << setw(22) <<
        p_vec[i][0]
     << setiosflags(ios::scientific) << setprecision(14) << setw(22) <<
        p_vec[i][1]
     << setiosflags(ios::scientific) << setprecision(14) << setw(22) <<
        p_vec[i][2]
     << setiosflags(ios::scientific) << setprecision(14) << setw(22) <<
        p_vec[i][3] << endl;
    cout <<  " | Matrix element : " << setiosflags(ios::scientific) <<
        setprecision(17) << res.first;
    cout <<  " GeV^" << - (2 * int(in_pdgs.size() + out_pdgs.size()) - 8) <<
        endl;
  }
}

int main(int argc, char * * argv)
{
  // Prevent unused variable warning
  if (false)
    cout << argc; 
  if (false)
    cout << argv; 

  // Simplest way of creating a PY8MEs accessor
  PY8MEs_namespace::PY8MEs PY8MEs_accessor("param_card_sm.dat"); 

  //----------------------------------------------------------------------------
  // Here is an alternative way of creating a PY8MEs_accessor for which we
  // handle ourselves the instantiation, release and initialization of the
  // model. Notice that we need here the name of the model class because it
  // does not have a generic base class (I can add it if really necessary)
  // 
  // Parameters_sm* model = PY8MEs_namespace::PY8MEs::instantiateModel();
  // 
  // Or even directly with
  // 
  // Parameters_sm* model = new Parameters_sm();
  // 
  // With here an example of the initialization of the model using
  // Pythia8 objects.
  // 
  // model->setIndependentParameters(particleDataPtr,couplingsPtr,slhaPtr);
  // model->setIndependentCouplings();
  // model->printIndependentParameters();
  // model->printIndependentCouplings();
  // 
  // And then finally obtain the accessor with this particular model
  // 
  // PY8MEs_namespace::PY8MEs PY8MEs_accessor(model);
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  // Finally one last way of creating a PY8MEs_accessor, which does the same
  // as above but this time doesn't require to define a local pointer to the
  // model (and hence to know its class name):
  // 
  // PY8MEs_namespace::PY8MEs PY8MEs_accessor();
  // 
  // We could now initialize the model from PY8 directly using the accessor
  // without having to manipulate a local pointer of the model
  // 
  // PY8MEs_namespace.initModelWithPY8(particleDataPtr, couplingsPtr, slhaPtr);
  // 
  // If needed, one can still access an instance of the model (for example
  // to be used for instantiating another PY8MEs_accessor) as follows. Be
  // wary however that as soon as you call this accessor, the PY8MEs_accessor
  // destructor will no longer take care of releasing the model instance and
  // it will be your responsability to do so.
  // 
  // Parameters_sm* model = PY8MEs_accessor.getModel();
  //----------------------------------------------------------------------------

  vector<int> vec_in_pdgs; 
  vector<int> vec_out_pdgs; 
  set<int> set_req_s_channels; 

  // Test the existence of a non-available process
  cout << endl <<  "Testing the non-existence of a non-available process:" <<
      endl;
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (33)(43)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (33)(2)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> (2)(5)); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 

  // Testing available processes
  cout << endl <<  "Testing the evaluation of available processes:" << endl; 

  // Process Process: b b > e- e+ b b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > mu- mu+ b b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > e- e+ b~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > mu- mu+ b~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > ve ve~ b b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > vm vm~ b b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > ve ve~ b~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > vm vm~ b~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > e- e+ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > mu- mu+ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > e- e+ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > mu- mu+ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > e- e+ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > mu- mu+ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > e- e+ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > mu- mu+ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > e- e+ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > mu- mu+ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > e- e+ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > mu- mu+ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > e- e+ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > mu- mu+ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > e- e+ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > mu- mu+ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > e- e+ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > mu- mu+ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > e- e+ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > mu- mu+ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > e- e+ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > mu- mu+ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > e- e+ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > mu- mu+ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > e- e+ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > mu- mu+ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > e- e+ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > mu- mu+ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > e- e+ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > mu- mu+ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > e- e+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > mu- mu+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > e- e+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > mu- mu+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > e- e+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > mu- mu+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > e- e+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > mu- mu+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > e- e+ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > mu- mu+ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > e- e+ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > mu- mu+ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > e- e+ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > mu- mu+ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > e- e+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > mu- mu+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > e- e+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > mu- mu+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > e- e+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > mu- mu+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > e- e+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > mu- mu+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > e- e+ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > mu- mu+ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > e- e+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > mu- mu+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > e- e+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > mu- mu+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > e- e+ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > mu- mu+ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > ve ve~ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > vm vm~ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > ve ve~ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > vm vm~ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > ve ve~ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > vm vm~ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > ve ve~ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > vm vm~ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > ve ve~ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > vm vm~ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > ve ve~ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > vm vm~ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > ve ve~ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > vm vm~ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > ve ve~ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > vm vm~ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > ve e+ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > vm mu+ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > ve e+ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > vm mu+ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > e- ve~ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > mu- vm~ u u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > e- ve~ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > mu- vm~ c c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > ve e+ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > vm mu+ d d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > ve e+ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > vm mu+ s s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > e- ve~ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > mu- vm~ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > e- ve~ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > mu- vm~ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > e- ve~ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > mu- vm~ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > e- ve~ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > mu- vm~ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > e- ve~ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > mu- vm~ d~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > e- ve~ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > mu- vm~ s~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > ve e+ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > vm mu+ u~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > ve e+ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > vm mu+ c~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > ve e+ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > vm mu+ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > ve e+ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > vm mu+ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > ve ve~ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > vm vm~ u d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > ve ve~ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > vm vm~ c s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > ve ve~ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > vm vm~ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > ve ve~ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > vm vm~ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > ve ve~ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > vm vm~ u~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > ve ve~ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > vm vm~ c~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > ve ve~ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > vm vm~ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > ve ve~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > vm vm~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > ve ve~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > vm vm~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > ve ve~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > vm vm~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > ve ve~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > vm vm~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > ve ve~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > vm vm~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > ve ve~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > vm vm~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > ve ve~ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > vm vm~ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > ve ve~ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > vm vm~ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > ve ve~ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > vm vm~ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > ve ve~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > vm vm~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > ve ve~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > vm vm~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > ve ve~ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > vm vm~ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > ve ve~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > vm vm~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > ve ve~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > vm vm~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > ve ve~ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > vm vm~ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > ve e+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > vm mu+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > ve e+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > vm mu+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > e- ve~ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > mu- vm~ u c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > e- ve~ c u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > mu- vm~ c u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > ve e+ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > vm mu+ d s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > ve e+ s d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > vm mu+ s d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > e- ve~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > mu- vm~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > e- ve~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > mu- vm~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > ve e+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > vm mu+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > ve e+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > vm mu+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > ve e+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > vm mu+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > ve e+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > vm mu+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > ve e+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > vm mu+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > ve e+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > vm mu+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > e- ve~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > mu- vm~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > e- ve~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > mu- vm~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > e- ve~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > mu- vm~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > e- ve~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > mu- vm~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > e- ve~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > mu- vm~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > e- ve~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > mu- vm~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > e- ve~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > mu- vm~ u s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > e- ve~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > mu- vm~ c d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > ve e+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > vm mu+ d c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > ve e+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > vm mu+ s u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > e- ve~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > mu- vm~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > e- ve~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > mu- vm~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > e- ve~ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > mu- vm~ d~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > e- ve~ s~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > mu- vm~ s~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > ve e+ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > vm mu+ u~ c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > ve e+ c~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > vm mu+ c~ u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > ve e+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > vm mu+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > ve e+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > vm mu+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > e- e+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > mu- mu+ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > e- e+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > mu- mu+ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > e- e+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > mu- mu+ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > e- e+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > mu- mu+ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > e- e+ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > mu- mu+ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > e- e+ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > mu- mu+ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > e- e+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > mu- mu+ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > e- e+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > mu- mu+ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > e- e+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > mu- mu+ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > e- e+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > mu- mu+ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > ve ve~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > vm vm~ c d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > ve ve~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > vm vm~ u s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > ve ve~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > vm vm~ d s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > ve ve~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > vm vm~ s d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > ve ve~ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > vm vm~ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > ve ve~ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > vm vm~ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > ve ve~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > vm vm~ u c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > ve ve~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > vm vm~ c u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > ve ve~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > vm vm~ c~ d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > ve ve~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > vm vm~ u~ s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ a a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > z b b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > z b~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > b b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > b b~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > g b b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > g b~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > e- e+ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > mu- mu+ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > e- e+ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > mu- mu+ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > e- e+ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > mu- mu+ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > e- e+ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > mu- mu+ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > e- e+ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > mu- mu+ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > e- e+ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > mu- mu+ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > e- e+ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > mu- mu+ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > e- e+ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > mu- mu+ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > e- e+ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > mu- mu+ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > e- e+ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > mu- mu+ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > e- e+ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > mu- mu+ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > e- e+ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > mu- mu+ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > e- e+ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > mu- mu+ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > e- e+ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > mu- mu+ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > e- e+ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > mu- mu+ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > e- e+ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > mu- mu+ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > ve ve~ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > vm vm~ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > ve ve~ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > vm vm~ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > ve ve~ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > vm vm~ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > ve ve~ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > vm vm~ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > ve ve~ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > vm vm~ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > ve ve~ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > vm vm~ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > ve ve~ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > vm vm~ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > ve ve~ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > vm vm~ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > ve ve~ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > vm vm~ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > ve ve~ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > vm vm~ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > ve ve~ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > vm vm~ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > ve ve~ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > vm vm~ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > ve ve~ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > vm vm~ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > ve ve~ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > vm vm~ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > ve ve~ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > vm vm~ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > ve ve~ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > vm vm~ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > ve e+ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > vm mu+ d b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > ve e+ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > vm mu+ s b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > ve e+ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > vm mu+ d b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > ve e+ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > vm mu+ s b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > e- ve~ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > mu- vm~ u b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > e- ve~ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > mu- vm~ c b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > e- ve~ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > mu- vm~ u b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > e- ve~ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > mu- vm~ c b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > e- ve~ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > mu- vm~ d~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > e- ve~ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > mu- vm~ s~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > e- ve~ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > mu- vm~ d~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > e- ve~ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > mu- vm~ s~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > ve e+ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > vm mu+ u~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > ve e+ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > vm mu+ c~ b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > ve e+ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > vm mu+ u~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > ve e+ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > vm mu+ c~ b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > a b b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > a b~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(-5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > d d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > s s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > u u~ u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > c c~ c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > d d~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > s s~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > u d u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > c s c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > d u~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > s c~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > u u~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > c c~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > c d c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > u s u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > d s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > s d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > c u~ c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > u c~ u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > s u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > d c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > c c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > u u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > s d~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > d s~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > c d s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > u s d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > u s c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > c d u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > s c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > d u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > c u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > u c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > g u u WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > g c c WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > g d d WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > g s s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > g u~ u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > g c~ c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > g d~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > g s~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > g u d WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > g c s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > g u d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > g c s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > g d u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > g s c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > g u~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > g c~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > g u c WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > g u s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > g c d WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > g u c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > g c u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > g u s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > g c d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > g d s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > g d c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > g s u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > g d s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > g s d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > g u~ c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > g u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > g c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > g d~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > g c d WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > g u s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > g d s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > g s d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > g u c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > g c u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > g c s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > g u d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > g s c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > g d u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > g c~ d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > g u~ s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > u u a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > c c a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > d d a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > s s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > u~ u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > c~ c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > d~ d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-1)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > s~ s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-3)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > u d a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > c s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > u d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > c s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > d u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > s c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > u~ d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > c~ s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > u c a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > u s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > c d a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > u c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > c u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > u s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > c d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > d s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > d c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > s u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > d s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > s d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > u~ c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > u~ s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > c~ d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > d~ s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-1)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > c d a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > u s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > d s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > s d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > c s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > u d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > s c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > d u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > u c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > c u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > c~ d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > u~ s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > z u u WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > z c c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > z d d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > z s s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > z u~ u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > z c~ c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > z d~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > z s~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > z u d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > z c s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > z u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > z c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > z d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > z s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > z u~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > z c~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > z u c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > z u s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > z c d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > z u c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > z c u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > z u s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > z c d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > z d s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > z d c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > z s u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > z d s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > z s d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > z u~ c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > z u~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > z c~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > z d~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > z c d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > z u s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > z d s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > z s d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > z c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > z u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > z s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > z d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > z u c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > z c u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > z c~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > z u~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > e- e+ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > mu- mu+ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > e- e+ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > mu- mu+ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- e+ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- mu+ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- e+ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- mu+ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- e+ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- mu+ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- e+ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- mu+ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > e- e+ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > mu- mu+ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > e- e+ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > mu- mu+ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve e+ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm mu+ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve e+ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm mu+ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- ve~ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- vm~ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- ve~ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- vm~ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- ve~ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- vm~ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- ve~ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- vm~ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve e+ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm mu+ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve e+ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm mu+ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve ve~ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm vm~ u a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve ve~ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm vm~ c a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > ve ve~ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > vm vm~ d a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > ve ve~ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > vm vm~ s a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > ve ve~ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > vm vm~ u~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > ve ve~ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > vm vm~ c~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve ve~ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm vm~ d~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve ve~ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm vm~ s~ a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > e- e+ a b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > mu- mu+ a b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > e- e+ a b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > mu- mu+ a b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > ve ve~ a b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > vm vm~ a b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > ve ve~ a b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > vm vm~ a b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ g a WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > w+ u d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(2)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > w+ c s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(4)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > w+ d d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > w+ s s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > w- u u WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > w- c c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > w- u d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > w- c s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > w- u~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > w- c~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > w+ u~ u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > w+ c~ c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > w- d~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > w- s~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > w+ u~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > w+ c~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > w+ u s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > w+ c d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > w+ d s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > w+ s d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > w- u c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > w- c u WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > w+ d c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > w+ s u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > w- u s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > w- c d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > w+ u c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > w+ c u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > w+ d s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > w+ s d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > w- u s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > w- c d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > w- u c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > w- c u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > w- d s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > w- s d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > w+ d c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > w+ s u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > w- u s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > w- c d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > w- u~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > w- c~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > w+ u~ c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > w+ c~ u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > w- d~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-1)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > w- s~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-3)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > w+ u~ s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > w+ c~ d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > g g u WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > g g c WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > g g d WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > g g s WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > g g u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > g g c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > g g d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > g g s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > g g b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > g g b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g g g WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- e+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- e+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- mu+ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- mu+ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- e+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- e+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- mu+ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- mu+ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- ve~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- ve~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- vm~ u d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- vm~ c s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve e+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve e+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm mu+ d u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm mu+ s c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve ve~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve ve~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm vm~ u u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm vm~ c c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve ve~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve ve~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm vm~ d d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm vm~ s s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > e- e+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > mu- mu+ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > ve ve~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > vm vm~ b b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > e- e+ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > mu- mu+ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > e- e+ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > mu- mu+ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- e+ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- mu+ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- e+ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- mu+ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- e+ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- mu+ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- e+ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- mu+ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > e- e+ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > mu- mu+ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > e- e+ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > mu- mu+ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve e+ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm mu+ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve e+ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm mu+ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve ve~ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm vm~ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve ve~ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm vm~ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- ve~ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- vm~ g u WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- ve~ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- vm~ g c WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > ve ve~ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > vm vm~ g d WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > ve ve~ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > vm vm~ g s WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- ve~ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- vm~ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- ve~ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- vm~ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > ve ve~ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > vm vm~ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > ve ve~ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > vm vm~ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve e+ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm mu+ g u~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve e+ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm mu+ g c~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve ve~ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm vm~ g d~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve ve~ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm vm~ g s~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > e- e+ g b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > mu- mu+ g b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > e- e+ g b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > mu- mu+ g b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > ve ve~ g b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > vm vm~ g b WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > ve ve~ g b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > vm vm~ g b~ WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ g g WEIGHTED<=99 @7
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > d b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > s b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > u~ b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > c~ b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > d~ b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > s~ b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > u u~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > c c~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > d d~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > s s~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > u u~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > c c~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > d d~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > s s~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > g u b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > g c b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > g u b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > g c b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > g d b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > g s b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > g d b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > g s b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > g u~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > g c~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > g u~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > g c~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > g d~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > g s~ b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > g d~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > g s~ b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g u u~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g c c~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g d d~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g s s~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > z u b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > z c b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > z u b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > z c b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > z d b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > z s b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > z d b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > z s b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > z u~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > z c~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > z u~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > z c~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > z d~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > z s~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > z d~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > z s~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > u a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > c a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > u a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(22)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > c a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(22)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > d a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > s a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > d a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(22)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > s a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(22)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > u~ a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > c~ a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > u~ a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > c~ a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > d~ a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > s~ a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > d~ a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-1)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > s~ a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-3)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(5)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > w+ d b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > w+ s b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > w+ d b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > w+ s b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > w- u b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > w- c b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > w- u b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > w- c b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > w- d~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-1)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > w- s~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-3)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > w- d~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-1)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > w- s~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-3)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > w+ u~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(-2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > w+ c~ b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(-4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > w+ u~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > w+ c~ b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b > b b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b~ b~ > b~ b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ a WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > u u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > c c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > d d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > s s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > a b b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > g u a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > g c a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > g d a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > g s a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > g u~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > g c~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > g d~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > g s~ a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > g a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > g a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g g a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g g a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g g a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g g a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g g a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > w+ d u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > w+ s c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > w- u d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > w- c s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > z u u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > z c c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > z d d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > z s s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > z b b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > w+ g d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(21)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > w+ g s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(21)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > w- g u WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > w- g c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > w- g d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > w- g s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > w+ g u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > w+ g c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > w+ d a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > w+ s a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > w- u a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > w- c a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > w- d~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > w- s~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > w+ u~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > w+ c~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > z g u WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > z g c WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > z g d WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > z g s WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > z g u~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > z g c~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > z g d~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > z g s~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > z g b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > z g b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > z ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > z vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > z ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > z vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > z e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > z mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > z e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > z mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z g g WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- e- e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(11)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- mu- mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(13)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w+ e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w+ mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w+ e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w+ mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w- ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > w- vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w- ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > w- vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w+ e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w+ mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w+ e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w+ mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w- ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > w- vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w- ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > w- vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- ve ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- vm vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w+ e- ve~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(11)(-12));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w+ mu- vm~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (24)(13)(-14));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w- ve e+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(12)(-11));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > w- vm mu+ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-24)(14)(-13));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u > u u WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c > c c WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d > d d WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s > s s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ u~ > u~ u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ c~ > c~ c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ d~ > d~ d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ s~ > s~ s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d > u d WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s > c s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > u d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > c s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > d u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > s c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ d~ > u~ d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ s~ > c~ s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c > u c WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > u s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > c d WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > u c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > c u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s~ > u s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d~ > c d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s > d s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d c~ > d c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s u~ > s u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > d s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > s d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ c~ > u~ c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > u~ s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > c~ d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ s~ > d~ s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u s > c d WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c d > u s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u c~ > d s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c u~ > s d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d s~ > u c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s d~ > c u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > c s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > u d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > s c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > d u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ s~ > c~ d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ d~ > u~ s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > d a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > s a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > u~ a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-2)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > c~ a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-4)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > d~ a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-1)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > s~ a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (-3)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > a a b WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > a a b~ WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > a a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > a a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > a a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > a a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (21)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > a a a WEIGHTED<=99 @5
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (22)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > z u a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > z c a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > z d a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > z s a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > z u~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-2)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > z c~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-4)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > z d~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-1)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > z s~ a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(-3)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > z a b WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > z a b~ WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z g a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(21)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z a a WEIGHTED<=99 @8
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (23)(22)(22));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > e- e+ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > mu- mu+ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > e- e+ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > mu- mu+ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- e+ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- mu+ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- e+ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- mu+ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- e+ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- mu+ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- e+ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- mu+ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > e- e+ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > mu- mu+ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > e- e+ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > mu- mu+ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve e+ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm mu+ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve e+ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm mu+ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > ve ve~ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > vm vm~ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > ve ve~ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > vm vm~ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > e- ve~ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > mu- vm~ u WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > e- ve~ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > mu- vm~ c WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > ve ve~ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > vm vm~ d WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > ve ve~ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > vm vm~ s WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > e- ve~ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > mu- vm~ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > e- ve~ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > mu- vm~ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > ve ve~ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > vm vm~ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > ve ve~ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > vm vm~ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve e+ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm mu+ u~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-2));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve e+ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm mu+ c~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(-4));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > ve ve~ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > vm vm~ d~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-1));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > ve ve~ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > vm vm~ s~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-3));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > e- e+ b WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > mu- mu+ b WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > e- e+ b~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > mu- mu+ b~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > ve ve~ b WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > vm vm~ b WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > ve ve~ b~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > vm vm~ b~ WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(-5));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (11)(-11)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (13)(-13)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (12)(-12)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ g WEIGHTED<=99 @4
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int>
      (14)(-14)(21));
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g g > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > g u WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > g c WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > g d WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > g s WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > g u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > g c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > g d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > g s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > g b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > g b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > b b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b > u b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b > c b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u b~ > u b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c b~ > c b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b > d b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b > s b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d b~ > d b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s b~ > s b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b > u~ b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b > c~ b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u~ b~ > u~ b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c~ b~ > c~ b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b > d~ b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b > s~ b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d~ b~ > d~ b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s~ b~ > s~ b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g g WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > u u~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > c c~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > d d~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > s s~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > e- e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > mu- mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > e- e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > mu- mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > e- e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > mu- mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > e- e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > mu- mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > ve ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > vm vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > ve ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > vm vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > ve e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > vm mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > ve e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > vm mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > e- ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > mu- vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > e- ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > mu- vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > ve ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > vm vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > ve ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > vm vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > e- e+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (11)(-11)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > mu- mu+ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (13)(-13)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > ve ve~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (12)(-12)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > vm vm~ WEIGHTED<=99 @1
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (14)(-14)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > u a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > c a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > d a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > s a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > u~ a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-2)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > c~ a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-4)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > d~ a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-1)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > s~ a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-3)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > a b WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > a b~ WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > g a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > g a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > g a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > g a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > a a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > a a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > a a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > a a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > g a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > a a WEIGHTED<=99 @2
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (22)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > w+ d WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > w+ s WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > w- u WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > w- c WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > w- d~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > w- s~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > w+ u~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > w+ c~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u > z u WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c > z c WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d > z d WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s > z s WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g u~ > z u~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-2)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g c~ > z c~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-4)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g d~ > z d~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-1)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g s~ > z s~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-3)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b > z b WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: g b~ > z b~ WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (21)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(-5)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z g WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(21)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z a WEIGHTED<=99 @6
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)(22)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u u~ > z WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c c~ > z WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d d~ > z WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s s~ > z WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: u d~ > w+ WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (2)(-1)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: c s~ > w+ WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (4)(-3)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (24)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: d u~ > w- WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (1)(-2)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: s c~ > w- WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (3)(-4)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (-24)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 
  // Process Process: b b~ > z WEIGHTED<=99 @3
  vec_in_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (5)(-5)); 
  vec_out_pdgs = vector<int> (PY8MEs_namespace::createvector<int> (23)); 
  set_req_s_channels = set<int> (PY8MEs_namespace::createset<int> ()); 
  run_proc(PY8MEs_accessor, vec_in_pdgs, vec_out_pdgs, set_req_s_channels); 


  #include "check_sa_additional_runs.inc"

}
