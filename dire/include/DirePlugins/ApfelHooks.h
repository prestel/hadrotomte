
#include "Dire/Hooks.h"
#include "LHAPDF/LHAPDF.h"
#include "apfel/apfelxx.h"

namespace Pythia8 {

//==========================================================================

// Hooks is base class for user access to program execution.

class ApfelHooks : public DireHooks {

public:

  ApfelHooks(string setName="MMHT2014nlo68cl") :
    info(::LHAPDF::PDFSet(setName)),
    pdfs(vector< ::LHAPDF::PDF* >(info.size(), 0)) {
    for (int i=0; i < pdfs.size(); ++i)
      if (!pdfs[i]) pdfs[i] = info.mkPDF(i);
  }

 ~ApfelHooks() {
    //if (pdf) delete pdf;
  }

  ::LHAPDF::PDFSet info;
  vector< ::LHAPDF::PDF* > pdfs;

  void initPDFexpansion() {
    int member = 1;
    ::LHAPDF::PDF *pdf = pdfs[member];
    cout << pdf->info().get_entry_as<double>("MBottom") << endl;
    return;
  }

  double getPDFexpansion(int order, int flav, double x, double q2,
    double muf2, double mur2) {

    const apfel::Grid g{{apfel::SubGrid{80,1e-5,3},
      apfel::SubGrid{50,1e-1,3}, apfel::SubGrid{40,8e-1,3}}};

    int member = 1;
    ::LHAPDF::PDF *pdf = pdfs[member];

    cout << pdf->xfxQ2(21, 1e-2, 100.) << endl;

    return 0.;
  }

};

//==========================================================================

} // end namespace Pythia8
