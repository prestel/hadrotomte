
// DIRE includes.
#include "Dire/Dire.h"

// Pythia includes.
#include "Pythia8/Pythia.h"
#include "Pythia8Plugins/HepMC2.h"

using namespace Pythia8;

// Functions for histogramming
#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
#include "fastjet/CDFMidPointPlugin.hh"
#include "fastjet/CDFJetCluPlugin.hh"
#include "fastjet/D0RunIIConePlugin.hh"

//==========================================================================

// Find the Durham kT separation of the clustering from
// nJetMin --> nJetMin-1 jets in te input event

double pTfirstJet( const Event& event, int nJetMin, double Rparam) {

  double yPartonMax = 4.;

  // Fastjet analysis - select algorithm and parameters
  fastjet::Strategy               strategy = fastjet::Best;
  fastjet::RecombinationScheme    recombScheme = fastjet::E_scheme;
  fastjet::JetDefinition         *jetDef = NULL;
  // For hadronic collision, use hadronic Durham kT measure
  if(event[3].colType() != 0 || event[4].colType() != 0)
    jetDef = new fastjet::JetDefinition(fastjet::kt_algorithm, Rparam,
                                      recombScheme, strategy);
  // For e+e- collision, use e+e- Durham kT measure
  else
    jetDef = new fastjet::JetDefinition(fastjet::ee_kt_algorithm,
                                      recombScheme, strategy);
  // Fastjet input
  std::vector <fastjet::PseudoJet> fjInputs;
  // Reset Fastjet input
  fjInputs.resize(0);

  // Loop over event record to decide what to pass to FastJet
  for (int i = 0; i < event.size(); ++i) {
    // (Final state && coloured+photons) only!
    if ( !event[i].isFinal()
      || event[i].isLepton()
      || event[i].id() == 23
      || abs(event[i].id()) == 24
      || abs(event[i].y()) > yPartonMax)
      continue;

    // Store as input to Fastjet
    fjInputs.push_back( fastjet::PseudoJet (event[i].px(),
            event[i].py(), event[i].pz(),event[i].e() ) );
  }

  // Do nothing for empty input
  if (int(fjInputs.size()) == 0) {
    delete jetDef;
    return 0.0;
  }

  // Run Fastjet algorithm
  fastjet::ClusterSequence clustSeq(fjInputs, *jetDef);
  // Extract kT of first clustering
  double pTFirst = sqrt(clustSeq.exclusive_dmerge_max(nJetMin-1));

  delete jetDef;
  // Return kT
  return pTFirst;

}

double Yij(const Vec4 &p, const Vec4 &q, const double ecm) {
  double pq(p.px()*q.px()+p.py()*q.py()+p.pz()*q.pz());
  double p2(p.px()*p.px()+p.py()*p.py()+p.pz()*p.pz());
  double q2(q.px()*q.px()+q.py()*q.py()+q.pz()*q.pz());
  return 2.0*pow2(min(p.e(),q.e()))*(1.0-min(max(pq/sqrt(p2*q2),-1.0),1.0))/pow2(ecm);
}

std::vector<double> Cluster(const Event & event) {

  vector<Vec4> p;
  for (int i = 0; i < event.size(); ++i) {
    // (Final state && coloured+photons) only!
    if ( !event[i].isFinal()
      || event[i].isLepton()
      || event[i].id() == 23
      || abs(event[i].id()) == 24)
      continue;
    p.push_back(event[i].p());
  }

  std::vector<double> kt2;
  if (p.size()<=1) return kt2;
  int ii=0, jj=0, n=p.size();
  std::vector<int> imap(p.size());
  for (size_t i(0);i<imap.size();++i) imap[i]=i;
  std::vector<std::vector<double> > kt2ij(n,std::vector<double>(n));
  double dmin=std::numeric_limits<double>::max();
  for (int i=0;i<n;++i)
    for (int j=0;j<i;++j) {
      double dij=kt2ij[i][j]=Yij(p[i],p[j], 91.2);
      if (dij<dmin) { dmin=dij; ii=i; jj=j; }
    }
  for (--n;n>1;--n) {
    kt2.push_back(dmin);
    int jjx=imap[jj]; p[jjx]+=p[imap[ii]];
    for (int i=ii;i<n;++i) imap[i]=imap[i+1];
    for (int j=0;j<jj;++j) kt2ij[jjx][imap[j]]=Yij(p[jjx],p[imap[j]],91.2);
    for (int i=jj+1;i<n;++i) kt2ij[imap[i]][jjx]=Yij(p[jjx],p[imap[i]],91.2);
    ii=jj=0; dmin=std::numeric_limits<double>::max();
    for (int i=0;i<n;++i)
      for (int j=0;j<i;++j) {
        double dij=kt2ij[imap[i]][imap[j]];
        if (dij<dmin) { dmin=dij; ii=i; jj=j; }
      }
  }
  return kt2;
}
 
//==========================================================================

int main( int argc, char* argv[] ){

  // Check that correct number of command-line arguments
  if (argc < 4) {
    cerr << " Unexpected number of command-line arguments ("<<argc-1<<"). \n"
         << " You are expected to provide the arguments" << endl
         << " 1. Input file for settings" << endl
         << " 2. Weight name" << endl
         << " 3. Output file name" << endl
         << argc-1 << " arguments provided:";
         for ( int i=1; i<argc; ++i) cerr << " " << argv[i];
         cerr << "\n Program stopped. " << endl;
    return 1;
  }

  Pythia pythia;
  pythia.settings.addFlag("Main:isFixedOrder",false);
  pythia.settings.addWVec("Main:eventTypes",vector<string>());

  pythia.readFile(argv[1]);
  pythia.init();

  string wname = string(argv[2]);
  string etype = string(argv[3]);

  double scaleBy = atof(argv[4]);

  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io(argv[5], std::ios::out);
  //HepMC::IO_GenEvent ascii_io("/dev/null", std::ios::out);
  // Switch off warnings for parton-level events.
  ToHepMC.set_print_inconsistency(false);
  ToHepMC.set_free_parton_exception(false);
  // Do not store cross section information, as this will be done manually.
  ToHepMC.set_store_pdf(false);
  ToHepMC.set_store_proc(false);
  ToHepMC.set_store_xsec(false);

  int nEvent = pythia.settings.mode("Main:numberOfEvents");
  if (nEvent<=0) {
    int nev=0;
    while ( true ) {
      // Generate next event
      if( !pythia.next() ) {
        if( pythia.info.atEndOfFile() )
          break;
        else continue;
      }
      nev++;
    }
    nEvent=nev;
  }

  // Cross section an error.
  double sigmaTotal  = 0.;
  double errorTotal  = 0.;
  pythia.readFile(argv[1]);
  pythia.init();

  double maxwt = 0.;
  string maxtype = "";
  int nlarge = 0;
  double sumwttot = 0.;

  const vector<string> types = pythia.settings.wvec("Main:eventTypes");
  //for (int i=0; i<types.size(); ++i) {
  //  cout << types[i] << endl;
  //}

  double sumwt = 0.;

  // Start generation loop
  for( int iEvent=0; iEvent<nEvent; ++iEvent ){

    // Generate next event
    if( !pythia.next() ) {
      if( pythia.info.atEndOfFile() )
        break;
      else continue;
    }

    // Get event weight(s).
    string etypeNow = pythia.info.getEventAttribute("eventType");

    string wvalue = pythia.info.getEventAttribute(wname);
    double weight = atof(wvalue.c_str());

//    if (etype!="n/a" && etype != etypeNow) weight = 0.;
//    if (etypeNow != ev0 && etypeNow != ev1) continue;
    if (!types.empty()
      && find(types.begin(),types.end(),etypeNow) == types.end()) {
cout << "continue for " << etypeNow << endl;
continue;
}
    if(types.empty() || wname == "n/a") weight = pythia.info.weight();

    if (abs(weight) > abs(maxwt)) { maxwt = weight; maxtype = etypeNow; cout << "new max " << maxwt << " " << maxtype << endl; }

    bool skip = false;
    //if ( abs(weight) > 1.4e5 ) { nlarge++; /*cout << "zero weight" << endl;*/ skip = true; }
    if ( abs(weight) > 1e6 ) { nlarge++; /*cout << "zero weight" << endl;*/ skip = true; }
    //sumwt += weight;

//    if (etypeNow == ev0) weight = atof(pythia.info.getEventAttribute("wfo_2_4").c_str());
//    if (etypeNow == ev1) weight = atof(pythia.info.getEventAttribute("wfo_3_4").c_str());

//if (weight== 0.) abort();

    // Do not print zero-weight events.
    if ( weight == 0. ) { /*cout << "zero weight" << endl;*/ continue; }
    //if ( weight <= 0. ) continue;
//if (fo) {
//if ( weight > 0. ) continue;
//weight = abs(weight);
//}

//    double nsamples = atof(pythia.info.getEventAttribute("nsamples").c_str());

    double scaleByNow = scaleBy > 0
      ? scaleBy
      : atof(pythia.info.getEventAttribute("neve").c_str());
//        / ( (nsamples>=0) ? nsamples : 1);
    if (scaleByNow<=0) scaleByNow = nEvent;

//cout << etypeNow << " " << weight << " " << scaleByNow << " \t\t " << pTfirstJet(pythia.event, 4, 1.0) << " " << log10(pow2(pTfirstJet(pythia.event, 4, 1.0))/pow2(pythia.info.eCM())) << endl;

//if (log10(pow2(pTfirstJet(pythia.event, 4, 1.0))/pow2(pythia.info.eCM())) < -4.5) {
    /*for ( map<string,string>::iterator
        it = pythia.info.eventAttributes->begin();
        it != pythia.info.eventAttributes->end(); ++it )
        cout << it->first << " " << it->second << endl;*/
//abort();
//}

    //std::vector<double> dij2 = Cluster(pythia.event);
    //for (size_t i=0;i<dij2.size();++i)
    //  if (dij2[dij2.size()-1-i]>0.)
    //    cout << i << " " << log10(dij2[dij2.size()-1-i]) << endl;

    weight /= double(scaleByNow);
    //if (fo) weight /= 2.;
    sumwttot += weight;
    if ( skip ) { /*cout << "zero weight" << endl;*/ continue; }

    sumwt += weight;
    // Construct new empty HepMC event.
    HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();

    // Set event weight
    hepmcevt->weights().push_back(weight);
    // Fill HepMC event
    ToHepMC.fill_next_event( pythia, hepmcevt );
 
    // Add the weight of the current event to the cross section.
    sigmaTotal  += weight;
    errorTotal  += pow2(weight);
    // Report cross section to hepmc
    HepMC::GenCrossSection xsec;
    //xsec.set_cross_section( max(1e-10,sigmaTotal), sqrt(errorTotal) );
    xsec.set_cross_section( 1e-10, 1e-10);
    hepmcevt->set_cross_section( xsec );
    // Write the HepMC event to file. Done with it.
    ascii_io << hepmcevt;
    delete hepmcevt;

  } // end loop over events to generate

  // print cross section, errors
  pythia.stat();

  cout << sumwt << " " << sumwttot << " " << nlarge << endl;

  // Done
  return 0;

}
