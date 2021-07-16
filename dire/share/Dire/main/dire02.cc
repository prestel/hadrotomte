
// DIRE includes.
#include "Dire/Dire.h"

// Pythia includes.
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

//==========================================================================

int main( int argc, char* argv[] ){

  // Check that correct number of command-line arguments
  if (argc < 3) {
    cerr << " Unexpected number of command-line arguments ("<<argc-1<<"). \n"
         << " You are expected to provide the arguments" << endl
         << " 1. Input file for settings" << endl
         << " 2. Output HepMC file" << endl
         << argc-1 << " arguments provided:";
         for ( int i=1; i<argc; ++i) cerr << " " << argv[i];
         cerr << "\n Program stopped. " << endl;
    return 1;
  }

  Pythia pythia;

  // Create DIRE shower plugin.
  Dire dire;

  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io(argv[2], std::ios::out);
  // Switch off warnings for parton-level events.
  ToHepMC.set_print_inconsistency(false);
  ToHepMC.set_free_parton_exception(false);
  // Do not store cross section information, as this will be done manually.
  ToHepMC.set_store_pdf(false);
  ToHepMC.set_store_proc(false);
  ToHepMC.set_store_xsec(false);

  // Initialize DIRE shower plugin.
  dire.init(pythia, argv[1], 0);

  // Get number of subruns.
  int nMerge = pythia.mode(" Main:numberOfSubruns");
  int nEvent = pythia.settings.mode("Main:numberOfEvents");
  bool fsr = pythia.flag("PartonLevel:FSR");
  bool isr = pythia.flag("PartonLevel:ISR");
  bool mpi = pythia.flag("PartonLevel:MPI");
  bool had = pythia.flag("HadronLevel:all");
  bool rem = pythia.flag("PartonLevel:Remnants");
  bool chk = pythia.flag("Check:Event");

  // Cross section estimate run.
  vector<double> sumSH;
  vector<double> nASH;
  vector<double> xs;
  vector<int> neve_real;
  // Loop over subruns with varying number of jets.
  for (int iMerge = 0; iMerge < nMerge; ++iMerge) {

    dire.resetFlag("PartonLevel:FSR",false);
    dire.resetFlag("PartonLevel:ISR",false);
    dire.resetFlag("PartonLevel:MPI",false);
    dire.resetFlag("HadronLevel:all",false);
    dire.resetFlag("PartonLevel:Remnants",false);
    dire.resetFlag("Check:Event",false);
    if (dire.doMerge()) dire.resetFlag("Merging:doXSectionEstimate", true);

    // Initialize with the LHE file for the current subrun.
    dire.init(pythia, argv[1], iMerge);

    int nEventEst = pythia.settings.mode("Main:numberOfEvents");
    // Cross section estimate run.
    double sumSHnow = 0.;
    double nAcceptSHnow = 0.;
    for( int iEvent=0; iEvent<nEventEst; ++iEvent ){
      // Generate next event
      if( !pythia.next() ) {
        if( pythia.info.atEndOfFile() )
          break;
        else continue;
      }
      sumSHnow     += pythia.info.weight();
      map <string,string> eventAttributes;
      if (pythia.info.eventAttributes)
        eventAttributes = *(pythia.info.eventAttributes);
      string trials = (eventAttributes.find("trials") != eventAttributes.end())
                  ?  eventAttributes["trials"] : "";
      if (trials != "") nAcceptSHnow += atof(trials.c_str());
    }

    // print cross section, errors
    pythia.stat();
    xs.push_back(pythia.info.sigmaGen());
    neve_real.push_back(
      (pythia.settings.flag("Merging:includeWeightInXsection")
      ? pythia.info.nSelected() : pythia.info.nAccepted()));
    sumSH.push_back(sumSHnow);
    nASH.push_back(nAcceptSHnow);
  }

  // Histogram the weight.
  Hist histWT("weight",10000,-500.,500.);

  // Switch showering and multiple interaction back on.
  pythia.settings.flag("PartonLevel:FSR",fsr);
  pythia.settings.flag("PartonLevel:ISR",isr);
  pythia.settings.flag("HadronLevel:all",had);
  pythia.settings.flag("PartonLevel:MPI",mpi);
  pythia.settings.flag("PartonLevel:Remnants",rem);
  pythia.settings.flag("Check:Event",chk);
  pythia.settings.flag("Merging:doXSectionEstimate", false);

  // Cross section and error.
  double sigmaTotal  = 0.;
  double errorTotal  = 0.;

  // Loop over subruns with varying number of jets.
  for (int iMerge = 0; iMerge < nMerge; ++iMerge) {

    double sigmaSample = 0., errorSample = 0.;
    // Initialize with the LHE file for the current subrun.
    dire.init(pythia, argv[1], iMerge);

    double wmax =-1e15;
    double wmin = 1e15;
    double sumwt = 0.;
    double sumwtsq = 0.;

    // Get the inclusive x-section by summing over all process x-sections.
    //double xs = 0.;
    //for (int i=0; i < pythia.info.nProcessesLHEF(); ++i)
    //  xs += pythia.info.sigmaLHEF(i);

    // Start generation loop
    for ( int iEvent=0; iEvent<nEvent; ++iEvent ){

      // Generate next event
      if( !pythia.next() ) {
        if( pythia.info.atEndOfFile() )
          break;
        else continue;
      }

      // Get event weight(s).
      double evtweight         = pythia.info.weight();

      // Retrieve the shower weight.
      dire.weightsPtr->calcWeight(0.);
      dire.weightsPtr->reset();
      double wt = dire.weightsPtr->getShowerWeight();
      wmin = min(wmin,wt);
      wmax = max(wmax,wt);
      sumwt += wt;
      sumwtsq+=pow2(wt);
      histWT.fill( wt, 1.0);


      if (std::isnan(wt)) {
        pythia.event.list();
        dire.direInfo.printMessages(1);
        abort();
      }

      evtweight *= wt;
      if (abs(wt) > 1e3) {
        cout << scientific << setprecision(8)
        << "Warning in DIRE main program dire03.cc: Large shower weight wt="
        << wt << endl;
        if (abs(wt) > 1e4) { 
          cout << "Warning in DIRE main program dire03.cc: Shower weight larger"
          << " than 10000. Discard event with rare shower weight fluctuation."
          << endl;
          evtweight = 0.;
        }
      }
      // Do not print zero-weight events.
      if ( evtweight == 0. ) continue;

      /*// Work with weighted (LHA strategy=-4) events.
      double normhepmc = 1.;
      if (abs(pythia.info.lhaStrategy()) == 4)
        normhepmc = 1. / double(1e9*nEvent);
      // Work with unweighted events.
      else
        normhepmc = xs / double(1e9*nEvent);*/

      double normhepmc = xs[iMerge] / double(neve_real[iMerge]);
      // Weighted events with additional number of trial events to consider.
      if ( pythia.info.lhaStrategy() != 0
        && pythia.info.lhaStrategy() != 3
        && nASH[iMerge] > 0)
        normhepmc = 1. / (1e9*nASH[iMerge]);
      // Weighted events.
      else if ( pythia.info.lhaStrategy() != 0
        && pythia.info.lhaStrategy() != 3
        && nASH[iMerge] == 0)
        normhepmc = 1. / (1e9*neve_real[iMerge]);

      // Construct new empty HepMC event.
      HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
      // Set event weight
      hepmcevt->weights().push_back(evtweight*normhepmc);
      // Fill HepMC event
      ToHepMC.fill_next_event( pythia, hepmcevt );

if (std::isnan(evtweight*normhepmc)){
dire.direInfo.printMessages(1);
cout << __LINE__ << " " << evtweight << " " << normhepmc << endl;
abort();
}

      // Add the weight of the current event to the cross section. 
      sigmaTotal  += evtweight*normhepmc;
      sigmaSample += evtweight*normhepmc;
      errorTotal  += pow2(evtweight*normhepmc);
      errorSample += pow2(evtweight*normhepmc);

      // Report cross section to hepmc
      HepMC::GenCrossSection xsec;
      xsec.set_cross_section( sigmaTotal*1e9, pythia.info.sigmaErr()*1e9 );
      hepmcevt->set_cross_section( xsec );
      // Write the HepMC event to file. Done with it.
      ascii_io << hepmcevt;
      delete hepmcevt;

    } // end loop over events to generate

    // print cross section, errors
    pythia.stat();

    cout << endl << " Contribution of sample " << iMerge
         << " to the inclusive cross section : "
         << scientific << setprecision(8)
         << sigmaSample << "  +-  " << sqrt(errorSample)  << endl;

    cout << "\t Minimal shower weight=" << wmin
       << "\n\t Maximal shower weight=" << wmax
       << "\n\t Mean shower weight=" << sumwt/double(nEvent)
       << "\n\t Variance of shower weight="
       << sqrt(1/double(nEvent)*(sumwtsq - pow(sumwt,2)/double(nEvent)))
       << endl;

  }

  ofstream write;
  // Write histograms to file
  write.open("wt.dat");
  histWT.table(write);
  write.close();

  cout << endl << endl << endl;
  cout << "Inclusive cross section: " << scientific << setprecision(8)
         << sigmaTotal << "  +-  " << sqrt(errorTotal) << " mb " << endl;
  cout << endl << endl << endl;

  // Done
  return 0;

}
