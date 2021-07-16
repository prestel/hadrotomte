// This main program (C) Nadine Fischer 2018
// This program allows to generate movies of the event generation and
// embeds them in a html file.

#include <limits>
#include "Pythia8/Pythia.h"
#include "Dire/Dire.h"
#include "DirePlugins/visualization/writeHTML.h"

using namespace Pythia8;

int main( int argc, char* argv[] ){

  // Create and initialize DIRE shower plugin.
  Pythia pythia;
  Dire dire;
  string file( ((argc == 1) ? "" : argv[1]) );

  // Random numbers.
  Rndm& random = pythia.rndm;

  // Less printing output.
  pythia.readString("Init:showChangedParticleData = off");
  pythia.readString("Next:numberShowProcess = 0");
  pythia.readString("Next:numberShowEvent = 0");

  // Switch on vertices. Switch off QED shower.
  pythia.readString("Fragmentation:setVertices = on");
  pythia.readString("PartonVertex:setVertex = on");
  pythia.readString("TimeShower:QEDshowerByQ = off");
  pythia.readString("TimeShower:QEDshowerByL = off");
  pythia.readString("TimeShower:QEDshowerByOther = off");
  pythia.readString("TimeShower:QEDshowerByGamma = off");
  pythia.readString("SpaceShower:QEDshowerByQ = off");
  pythia.readString("SpaceShower:QEDshowerByL = off");

  int type = -1, seed = -1;
  while (argc == 1 && !(type == 0 || type == 1 || type == 2)) {
    cout << endl << "Please enter type of collision"
         << " (0 = LEP, 1 = DIS, 2 = LHC): ";
    cin >> type;
    cout << endl << "Please enter seed:";
    cin >> seed;
  }

  pythia.readString("Random:setSeed = on");

  if (type == -1) ;
  else if (type == 0) {
    // Allow no substructure in e+- beams.
    pythia.readString("PDF:lepton = off");
    // Process selection.
    pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
    // Switch off all Z0 decays and then switch back on those to quarks.
    pythia.readString("23:onMode = off");
    pythia.readString("23:onIfAny = 1 2 3 4 5");

    // LEP1 initialization at Z0 mass.
    pythia.readString("Beams:idA =  11");
    pythia.readString("Beams:idB = -11");
    double mZ = pythia.particleData.m0(23);
    pythia.settings.parm("Beams:eCM", mZ);
    pythia.settings.mode("Random:seed", seed);
  } else if (type == 1) {
    // Allow no substructure in e+- beams.
    pythia.readString("PDF:lepton = off");
    // Process selection.
    pythia.readString("WeakBosonExchange:ff2ff(t:gmZ) = on");
    // DIS initialization.
    pythia.readString("Beams:idA = -11");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:frameType = 2");

    //pythia.readString("Beams:eA = 27.5");
    //pythia.readString("Beams:eB = 920");
    //pythia.readString("PhaseSpace:Q2min = 500.0");

    pythia.readString("Beams:eA = 10.");
    pythia.readString("Beams:eB = 100.");
    pythia.readString("PhaseSpace:Q2min = 50.0");
    pythia.settings.mode("Random:seed", seed);

  } else if (type == 2) {
    // Process selection.
    pythia.readString("HardQCD:qqbar2gg = on");
    // Phase-space cuts.
    pythia.readString("PhaseSpace:pTHatMin = 1000.0");

    // Switch off MPI and resonance radiation.
    pythia.readString("PartonLevel:MPI = off");
    pythia.readString("PartonLevel:FSRinResonances = off");

    // LHC 7TeV initialization.
    pythia.readString("Beams:idA = 2212");
    pythia.readString("Beams:idB = 2212");
    pythia.readString("Beams:eCM = 13000.0");
    pythia.settings.mode("Random:seed", seed);
  }

  if (argc > 1)  dire.init(pythia, file.c_str());
  if (argc == 1) dire.init(pythia);

  // Event loop. Generate event. Skip if error.
  for (int iEvent = 0; iEvent < 2; ++iEvent) {
    if (!pythia.next()) continue;
    if (iEvent == 1) {
      pythia.event.list(true,true);
      writeHTML(pythia.event, random, type);
    }
  }

  cout << endl << endl
       << "  *---------------------------------------------*\n\n"
       << "  Collision movie written to collision.html file.\n\n"
       << "  To view, start a HTTP server with\n\n"
       << "\033[1;31m  python -m SimpleHTTPServer &\033[0m\n\n"
       << "  and open for example with \n\n"
       << "\033[1;31m  firefox http://localhost:8000/collision.html\033[0m\n\n"
       << "  *---------------------------------------------*\n"
       << endl;

  // Done.
  return 0;
}
