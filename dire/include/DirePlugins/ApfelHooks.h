
#include "Dire/Hooks.h"
#include "LHAPDF/LHAPDF.h"
#include "apfel/apfelxx.h"
#include "apfel/betaqcd.h"

namespace Pythia8 {

//==========================================================================

// Hooks is base class for user access to program execution.

class ApfelHooks : public DireHooks {

public:

  ApfelHooks(string setName="MMHT2014nlo68cl") :
    info(::LHAPDF::PDFSet(setName)),
    pdfs(vector< ::LHAPDF::PDF* >(info.size(), 0)) {
    for (int i=0; i < (int) pdfs.size(); ++i)
      if (!pdfs[i]) pdfs[i] = info.mkPDF(i);
  }

 ~ApfelHooks() {
    //if (pdf) delete pdf;
  }

  ::LHAPDF::PDFSet info;
  vector< ::LHAPDF::PDF* > pdfs;

  // APFEL++ x-space grid
  std::unique_ptr<const apfel::Grid> g;

  // Terms of the expansion of the PDF evolution
  std::map<int, apfel::Distribution> f00;
  std::map<int, apfel::Distribution> f10;
  std::map<int, apfel::Distribution> f20;
  std::map<int, apfel::Distribution> f21;
  std::map<int, apfel::Distribution> f22;

  void initPDFexpansion() {
    // Parameters to be passed for now set manually
    //////////////////////////////////////////////////////////////////
    // Get PDF member
    const int member = 1;

    // Renormalisation and factorisation scales (pick two values)
    //const double muf2 = pow2(100);
    //const double mur2 = pow2(50);
    const double muf = settingsPtr->parm("Merging:muFacInME");
    const double mur = settingsPtr->parm("Merging:muRenInME");

    // Initialise x-space grid of APFEL++
    g = std::unique_ptr<const apfel::Grid>(new apfel::Grid({{80, 1e-5, 3}, {50, 1e-1, 3}, {40, 8e-1, 3}}));
    //////////////////////////////////////////////////////////////////

    // Get PDF set
    ::LHAPDF::PDF *pdf = pdfs[member];

    // Get heavy-quark thresholds from LHAPDF
    std::vector<double> Thresholds;
    for (auto const& v : pdf->flavors())
      if (v > 0 && v < 7)
        Thresholds.push_back(pdf->quarkThreshold(v));

    // Get alpha_s/4pi at mur from LHAPDF
    const double asR  = pdf->alphasQ(mur) / apfel::FourPi;
    const double asR2 = asR * asR;

    // Set silent mode for APFEL
    //apfel::SetVerbosityLevel(0);

    // Initialize DGLAP objects on the grid (this contains the
    // splitting functions on the grid).
    const auto DglapObj = apfel::InitializeDglapObjectsQCD(*g, Thresholds);

    // Rotate PDF set into the QCD evolution basis
    const auto RotPDFs = [=] (double const& x, double const& mu) ->
      std::map<int, double>{ return apfel::PhysToQCDEv(pdf->xfxQ(x, mu)); };

    // Get "apfel::Set<apfel::Distribution>" in the QCD evolution
    // basis at the scale muf
    const apfel::Set<apfel::Distribution> pdfmuf
    {apfel::EvolutionBasisQCD{apfel::NF(muf, Thresholds)},
        DistributionMap(*g, RotPDFs, muf)};

    // Get splitting functions with the correct number of active
    // flavours determined by muf and do the convolutions with the
    // PDFs.
    const apfel::DglapObjects dob = DglapObj.at(apfel::NF(muf, Thresholds));
    const apfel::Set<apfel::Operator> P0 = dob.SplittingFunctions.at(0);
    const apfel::Set<apfel::Operator> P1 = dob.SplittingFunctions.at(1);
    const apfel::Set<apfel::Distribution> P0f = P0 * pdfmuf;
    const apfel::Set<apfel::Distribution> P1f = P1 * pdfmuf;
    const apfel::Set<apfel::Distribution> P0P0f = P0 * P0f;

    // Get beta0 zero with the approriate number of active flavours
    // determined by mur.
    const double b0 = apfel::beta0qcd(apfel::NF(mur, Thresholds));

    // Construct terms that multiply powers of log(mur^2/Q^2) and
    // log(muf^2/Q^2) up to O(as^2). In order to save time, include
    // also alpha_s itself because the renormalisation scale is know
    // here. Rotate into the physical basis to save time.

    // LO term
    f00 = apfel::QCDEvToPhys(pdfmuf.GetObjects());

    // NLO term
    f10 = apfel::QCDEvToPhys(((-asR) * P0f).GetObjects());        // Multiplies LF

    // NNLO terms
    f20 = apfel::QCDEvToPhys(((-asR2) * P1f).GetObjects());       // Multiplies LF
    f21 = apfel::QCDEvToPhys(((asR2 * b0) * P0f).GetObjects());   // Multiplies ( LF / 2 - LR ) * LF
    f22 = apfel::QCDEvToPhys(((asR2 / 2) * P0P0f).GetObjects());  // Multiplies LF^2

    return;
  }

  double getPDFexpansion(int order, int flav, double x, double q2,
    double muf2, double mur2) {
    /////////////////////////////////////////////////////////////////
    // NOTE: the gluon has index 0 not 21. For quarks, the PDG
    // convension is used: d = 1, dbar = -1, u = 2, ubar = -2, s = 3,
    // sbar = -3, etc.
    /////////////////////////////////////////////////////////////////
    if (flav == 21) flav = 0;

    // Log of the scales
    const double LR = log(mur2 / q2);
    const double LF = log(muf2 / q2);

    // LO
    double exppdf = f00.at(flav).Evaluate(x);

    // NLO
    if (order > 0)
      exppdf += LF * f10.at(flav).Evaluate(x);

    // NNLO
    if (order > 1)
      exppdf += LF * f20.at(flav).Evaluate(x)
        + ( LF / 2 - LR ) * LF * f21.at(flav).Evaluate(x)
        + ( pow2(LF) / 2 ) * f22.at(flav).Evaluate(x);

    return exppdf;
  }

};

//==========================================================================

} // end namespace Pythia8
