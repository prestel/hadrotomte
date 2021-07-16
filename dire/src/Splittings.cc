
#include "Dire/Splittings.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

namespace Pythia8 {

//==========================================================================

// The Splitting class.

//--------------------------------------------------------------------------

void DireSplitting::init() {

  renormMultFac      = 1.;
  if (id.find("Dire_isr_") != string::npos)
    renormMultFac    = settingsPtr->parm("SpaceShower:renormMultFac");
  else
    renormMultFac    = settingsPtr->parm("TimeShower:renormMultFac");

  if ( id.find("_qcd_")      != string::npos) is_qcd  = true;
  if ( id.find("_qed_")      != string::npos) is_qed  = true;
  if ( id.find("_ew_")       != string::npos) is_ewk  = true;
  if ( id.find("Dire_")      != string::npos) is_dire = true;
  if ( id.find("Dire_isr_")  != string::npos) is_isr  = true;
  if ( id.find("Dire_fsr_")  != string::npos) is_fsr  = true;

  doVariations    = settingsPtr->flag("Variations:doVariations");
  doMECs          = settingsPtr->flag("Dire:doMECs")
                 || settingsPtr->flag("Dire:doMOPS")
                 || settingsPtr->flag("Dire:doMEM");

  enhanceSave = settingsPtr->parm("Enhance:"+ id);

  nameHash = shash(id);

}

//--------------------------------------------------------------------------

double DireSplitting::getKernel(string key) {
  unordered_map<string, double>::iterator it = kernelVals.find(key);
  if ( it == kernelVals.end() ) return 0./0.;
  return it->second;
}

//--------------------------------------------------------------------------

void DireSplitting::adjustKernelVals(unordered_map<string,double>& in,
  const Event& e, double t) {
  bool doMECnow = hasMECBef(e, t);
  for ( unordered_map<string,double>::iterator it = in.begin();
    it != in.end(); ++it )
    if (it->first != "base_order_as2" && doMECnow)
      it->second = abs(it->second);
}

//--------------------------------------------------------------------------

void DireSplitting::storeKernelVals(
  unordered_map<string,double> in) {
  // Reset all kernel values ifany entry is not well-defined.
  bool isgood = true;
  for ( unordered_map<string,double>::iterator it = in.begin();
    it != in.end(); ++it ) if (std::isnan(it->second)) isgood = false; 
  if (!isgood) { 
   string message = "Warning in Dire splitting kernel ";
   message += name();
   message += ": Not-a-number splitting probability. Force to zero.";
   infoPtr->errorMsg(message);
   for ( unordered_map<string,double>::iterator it = in.begin();
     it != in.end(); ++it ) it->second = 0.0; 
  }

  // Store kernel values.
  clearKernelVals();
  for ( unordered_map<string,double>::iterator it = in.begin();
    it != in.end(); ++it )
    kernelVals.insert(make_pair( it->first, it->second ));
}

//--------------------------------------------------------------------------

void DireSplitting::storeKernelVal(string key, double val) {
  // Reset all kernel values ifany entry is not well-defined.
  bool isgood = true;
  if (std::isnan(val)) isgood = false; 
  unordered_map<string, double>::iterator it = kernelVals.find(key);
  if (!isgood) { 
   string message = "Warning in Dire splitting kernel ";
   message += name();
   message += ": Not-a-number splitting probability. Force to zero.";
   infoPtr->errorMsg(message);
   val = 0.0;
  }
  if ( it == kernelVals.end() ) kernelVals.insert(make_pair(key,val));
  else it->second = val;
}

//--------------------------------------------------------------------------

bool DireSplitting::zero() {

  storeKernelVal("base", 0.);
  if (doVariations && settingsPtr->parm("Variations:muRfsrDown") != 1.)
    storeKernelVal("Variations:muRfsrDown", 0.);
  if (doVariations && settingsPtr->parm("Variations:muRfsrUp")   != 1.)
    storeKernelVal("Variations:muRfsrUp", 0.);
  return true;

}

//--------------------------------------------------------------------------

bool DireSplitting::hasMECBef(const Event& state, double pT2) {
  if (!doMECs) return false;
  vector <int> in, out;

  for (int i=0; i < state.size(); ++i) {
    if (i == splitInfo.iRadBef) continue;
    if (state[i].isFinal()) out.push_back(state[i].id());
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      in.push_back(state[i].id());
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      in.push_back(state[i].id());
  }
  int idRad   = splitInfo.radBef()->id; 
  int colType = (idRad!=21) ? idRad/abs(idRad) : 2;
  vector<int> re = radAndEmt( idRad, colType);
  if (is_isr) in.push_back(re[0]);
  else       out.push_back(re[0]);

  if (in.size()>2) {
    cout << "Problem with state" << endl;
    state.list();
    return false;
  }

  for (size_t i=1; i < re.size(); ++i) out.push_back(re[i]);
  bool aboveCut = doMECs &&
    pT2 > pow2(max(0.,settingsPtr->parm("Dire:pTminMECs")));
  bool hasMEcode = (is_isr)
    ? isr->weights->hasME(in,out) : fsr->weights->hasME(in,out);
  return aboveCut && hasMEcode;
}

//--------------------------------------------------------------------------

bool DireSplitting::hasMECAft(const Event& state, double pT2) {
  if (!doMECs) return false;
  vector <int> in, out;
  for (int i=0; i < state.size(); ++i) {
    if (state[i].isFinal()) out.push_back(state[i].id());
    if (state[i].mother1() == 1 && state[i].mother2() == 0)
      in.push_back(state[i].id());
    if (state[i].mother1() == 2 && state[i].mother2() == 0)
      in.push_back(state[i].id());
  }
  bool aboveCut = doMECs &&
    pT2 > pow2(max(0.,settingsPtr->parm("Dire:pTminMECs")));
  bool hasMEcode = (is_isr)
    ? isr->weights->hasME(in,out) : fsr->weights->hasME(in,out);
  return aboveCut && hasMEcode;
}

//==========================================================================

} // end namespace Pythia8
