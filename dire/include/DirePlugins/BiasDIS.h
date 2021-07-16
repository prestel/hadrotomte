
// Includes
#include "Pythia8/Pythia.h"

namespace Pythia8 {

//==========================================================================

class BiasDIS : public UserHooks {

public:

  BiasDIS() : t0(2.0), s0(1.0) {}

  // Possibility to bias selection of events, compensated by a weight.
  bool canBiasSelection() {return true;}

  // Multiplicative factor in the phase space selection of a hard process.
  double biasSelectionBy(const SigmaProcess*, const PhaseSpace* phaseSpacePtr,
    bool) {
    return pow(6./abs(phaseSpacePtr->tHat()),6.)*pow(abs(phaseSpacePtr->sHat())/s0,4.);
  }

private:

  double t0, s0;

};

//==========================================================================

} // end namespace Pythia8

