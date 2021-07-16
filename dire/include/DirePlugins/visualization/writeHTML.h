#include <limits>
#include "Pythia8/Pythia.h"

#ifndef MM2FM
#define MM2FM 1e12
#endif

using namespace Pythia8;

typedef pair<int,int> pii;

// Helper functions.

string  name(Particle& pt) { return "\"" + pt.name() + "\""; }
double tProd(Particle& pt) { return abs(pt.tProd())*MM2FM; }

int checkDaughters(Particle& p1, Event& event) {
  for (int i=0; i<(int)p1.daughterList().size(); i++) {
    Particle& p2 = event[p1.daughterList()[i]];
    if (p2.statusAbs() < 60 && p2.scale() > 0.001) return i;
  }
  return -1;
}

int checkMothers(Particle& p1, Event& event) {
  for (int i=0; i<(int)p1.motherList().size(); i++) {
    Particle& p2 = event[p1.motherList()[i]];
    if (p2.statusAbs() < 60 && p2.scale() > 0.001) return i;
  }
  return -1;
}

string parton(int col, int acol) {
  map<int,string> colors;
  colors.insert(make_pair(101,"\"red\""));
  colors.insert(make_pair(102,"\"green\""));
  colors.insert(make_pair(103,"\"blue\""));
  while ( col > 103)  col -= 3;
  while (acol > 103) acol -= 3;
  if (col == 0) {
     col = acol;
    acol = 0;
  }
  if (acol == 0) return "new quark("+colors[col]+")";
  return "new gluon("+colors[col]+", "+colors[acol]+")";
}

string meson(Rndm& random) {
  double rnd = random.flat();
  if (rnd > 0.66667) return "new diquark(\"red\", \"green\", true)";
  if (rnd > 0.33333) return "new diquark(\"red\", \"blue\", true)";
  return "new diquark(\"green\", \"blue\", true)";
}

string particle(Particle& pt) {
  if (pt.isParton()) return parton(pt.col(), pt.acol())+", "+name(pt);
  if (pt.isLepton()) return "new lepton(), "+name(pt);
  if (pt.idAbs() == 22) return "new gamma(), "+name(pt);
  if (pt.idAbs() >= 23 && pt.idAbs() <= 25) return "new hwzBoson(), "+name(pt);
  return "";
}

string particle(Particle& pt, Rndm& random) {
  if (pt.particleDataEntry().isMeson()) return meson(random)+", "+name(pt);
  if (pt.particleDataEntry().isBaryon())
    return "new triquark(\"red\", \"green\", \"blue\", true), "+name(pt);
  return particle(pt);
}

vector<int> findStringParents(Event& event, int idx) {
  int mots[2] = { event[idx].mother1(), event[idx].mother2() };
  vector<int> iParents;
  for (int i=0; i<2; i++) {
    while (event[mots[i]].statusAbs() > 70 && event[mots[i]].statusAbs() < 80)
      mots[i] = event[mots[i]].mother1();
    iParents.push_back(mots[i]);
  }
  return iParents;
}

void printEndPosition(int i, int type, ostream& outf) {
  map<int,string> types;
  types.insert(make_pair(0,"particles"));
  types.insert(make_pair(1,"primaryHadrons"));
  types.insert(make_pair(2,"decayProducts"));
  outf << "    endPosition(" << types[type] << "[" << i << "], "
       << type << ", " << i << ")," << endl;
}

void printMomentum(Particle& pt, ostream& outf, bool full, bool backwards
  = false) {
  double mom[3] = { pt.px(), pt.py(), pt.pz() };
  if (backwards) for (int i=0; i<3; i++) mom[i] = -mom[i];
  outf << "    new THREE.Vector3(" << mom[0] << ", " << mom[1] << ", " << mom[2]
       << "), "<< pt.e() << ", " << pt.m() << (full ? "));" : ",") << endl;
}

// Write incoming of the hard process to file.
void writeInHard(int scatType, Particle& pt, ostream& outf) {
  outf << "  particles.push(new Particle(" << particle(pt) << "," << endl
       << "    inTimeStart" << (scatType == 0 ? "" : "/3") << ", inTimeEnd,"
       << endl << "    new THREE.Vector3(0.0, 0.0, "
       << (pt.pz() > 0 ? "-" : "") << "detectorInnerHeight/"
       << (scatType == 0 ? "2" : "6") << ")," << endl;
  printMomentum(pt, outf, true);
}
void writeInHardBack(Event& event, Particle& pt, int& iEndPos, ostream& outf) {
  outf << "  particles.push(new Particle(" << particle(pt) << "," << endl
       << "    showerTimeStart, ";
  // Check if a mother exists with a scale > 0.
  int idx = checkMothers(pt,event);
  if (idx > -1)
    outf << "showerTimeStart+" << 1.0/event[pt.motherList()[idx]].scale()
         << "*scaleTimeMult," << endl;
  else outf << "showerTimeEnd," << endl;
  printEndPosition(iEndPos++, 0, outf);
  printMomentum(pt, outf, true, true);
}

// Write outgoing of the hard process to file.
void writeOutHard(Event& event, Particle& pt, int& iEndPos, ostream& outf) {
  outf << "  particles.push(new Particle(" << particle(pt) << "," << endl
       << "    showerTimeStart, ";
  // Check if a daughter exists with a scale > 0.
  int idx = checkDaughters(pt,event);
  if (idx > -1)
    outf << "showerTimeStart+" << 1.0/event[pt.daughterList()[idx]].scale()
         << "*scaleTimeMult," << endl;
  else outf << (pt.isParton() ? "showerTimeEnd," : "timeEnd,") << endl;
  printEndPosition(iEndPos++, 0, outf);
  printMomentum(pt, outf, true);
}

// Write shower particles to file.
void writeShower(Event& event, Particle& pt, map<int,int>& idxPyJv,
  ostream& outf, bool time, bool out) {
  outf << "  particles.push(new Particle(" << particle(pt) << ","
       << endl << "    showerTimeStart+" << 1.0/pt.scale()
       << "*scaleTimeMult, ";
  // Outgoing: check if a daughter exists with a scale > 0.
  // Incoming: check if a mother exists with a scale > 0.
  int idx = (out ? checkDaughters(pt,event) : checkMothers(pt,event));
  if (idx > -1) {
    idx = (out ? pt.daughterList()[idx] : pt.motherList()[idx]);
    outf << "showerTimeStart+" << 1.0/event[idx].scale()
         << "*scaleTimeMult," << endl;
  } else outf << "showerTimeEnd," << endl;
  // Starting position of parton depends on mother (outgoing) or daughter
  // (incoming).
  if (time && out) printEndPosition(idxPyJv[pt.mother1()], 0, outf);
  else if (time && !out) printEndPosition(idxPyJv[pt.daughter1()], 0, outf);
  else if (!time && !out) printEndPosition(idxPyJv[pt.daughter2()], 0, outf);
  else if (pt.statusAbs() == 43)
    outf << "    particles[" << idxPyJv[pt.mother1()] << "].pos," << endl;
  else printEndPosition(idxPyJv[pt.mother1()], 0, outf);
  if (out) printMomentum(pt, outf, true);
  else printMomentum(pt, outf, true, true);
}

// Setup the strings by finding the color partners of current particle.
void stringSetup(Event& event, int i, map<pii,pii>& strings, int scatType) {
  Particle& pt = event[i];
  // Find color partner for string setup
  for (int j=(int)event.size()-1; j>i; j--) {
    if ( (scatType == 0 && event[j].statusAbs() < 60)
      || (scatType > 0 && (event[j].statusAbs() == 62 ||
                           event[j].statusAbs() == 63)) ) {
      if (pt.acol() == 0 && event[j].acol() == pt.col()) {
        strings.insert( make_pair(pii(i,j), pii(pt.col(),0)) );
        break;
      } else if (pt.col() == 0 && event[j].col() == pt.acol()) {
        strings.insert( make_pair(pii(i,j), pii(pt.acol(),0)) );
        break;
      } else if (pt.acol() != 0 && pt.col() != 0) {
        if (event[j].acol() == pt.col()) {
          strings.insert( make_pair(pii(i,j), pii(pt.col(),0)) );
          break;
        } else if (event[j].col() == pt.acol()) {
          strings.insert( make_pair(pii(i,j), pii(pt.acol(),0)) );
          break;
        }
      }
    }
  }
}

// Main function.
void writeHTML(Event& event, Rndm& random, int type, const char* input =
  "template.html", const char* output = "collision.html") {
  ofstream outf;
  outf.open(output);
  ifstream inpf;
  inpf.open(input);
  // Copy input to output file, up to begin tag.
  if (inpf.is_open()) {
    string line;
    while (getline(inpf,line)) {
      if (line == "//**** BEGIN ****//") break;
      else outf << line << endl;
    }
  } else {
    cout << "  Did not find input file for writeHTML!"
         << endl << "  Exiting!" << endl;
    return;
  }

  // Conversion from Pythia's index to index used in JavaScript.
  // Shower particles, primary hadrons, and decay products of hadrons.
  int count = 0;
  map<int,int> idxPyJv, idxPyJvPH, idxPyJvDH;
  // Map to store all string endpoints with colors.
  map<pii,pii> strings;

  // 1. Particles up to end of shower.
  outf << "  // Particles." << endl;
  // 1.1 Incoming of hard process.
  for (int i=0; i<(int)event.size(); i++) if (event[i].statusAbs() == 21) {
    writeInHard(type, event[i], outf);
    idxPyJv[i] = count++;
  }
  int iEndPos = 0;
  // 1.2 LHC/DIS only: incoming of the hard process, going backwards.
  if (type != 0) {
    for (int i=0; i<(int)event.size(); i++)
      if (event[i].statusAbs() == 21 && event[i].isParton()) {
        writeInHardBack(event, event[i], iEndPos, outf);
        idxPyJv[i] = count++;
      }
  }
  iEndPos = 0;
  // 1.3 Outgoing of hard process.
  for (int i=0; i<(int)event.size(); i++) if (event[i].statusAbs() == 23) {
    writeOutHard(event, event[i], iEndPos, outf);
    idxPyJv[i] = count++;
  }
  // 1.4 Added / recoiled during shower.
  for (int i=0; i<(int)event.size(); i++) {
    Particle& pt = event[i];
    // 1.4.1 Time shower: outgoing radiator / emission / recoiler.
    if (pt.statusAbs() == 51 || pt.statusAbs() == 52 || pt.statusAbs() == 59) {
      writeShower(event, pt, idxPyJv, outf, true, true);
      idxPyJv[i] = count++;
    }
    // 1.4.2 Time shower: incoming recoiler.
    if (pt.statusAbs() == 53) {
      writeShower(event, pt, idxPyJv, outf, true, false);
      idxPyJv[i] = count++;
    }
    // 1.4.3 Space shower: incoming radiator / recoiler.
    if (pt.statusAbs() == 41 || pt.statusAbs() == 42 || pt.statusAbs() == 49) {
      writeShower(event, pt, idxPyJv, outf, false, false);
      idxPyJv[i] = count++;
    }
    // 1.4.4 Space shower: outgoing emission / recoiler.
    if (pt.statusAbs() == 43 || pt.statusAbs() == 44 || pt.statusAbs() == 48) {
      writeShower(event, pt, idxPyJv, outf, false, true);
      idxPyJv[i] = count++;
    }
  }

  // 2. Particle ends for strings.
  outf << "  // Particles at the end of the shower." << endl;
  for (int i=0; i<(int)event.size(); i++) {
    Particle& pt = event[i];
    // Lepton beam: outgoing of hard process or added / recoiled during shower.
    // Hadron beam: outgoing shower particle with primordial kT or outgoing
    //              beam remnant.
    if ( (type == 0 && (pt.statusAbs() == 23 || pt.statusAbs() == 51 ||
                        pt.statusAbs() == 52 || pt.statusAbs() == 59))
      || (type > 0 && (pt.statusAbs() == 62 || pt.statusAbs() == 63)) ) {
      // Lepton beam: check if no daughters with scale > 0 exist.
      if ( (type == 0 && checkDaughters(pt, event) < 0) || type > 0 ) {
        stringSetup(event, i, strings, type);
        outf << "  particles.push(new Particle(new stringPoint(), "
             << name(pt) << "," << endl << "    stringTimeStart, "
             << "stringTimeStart," << endl;
        int iP = (type == 0 ? i : (pt.statusAbs() == 62 ? pt.mother1() :
                  event[event[pt.mother1()].daughter1()].daughter1()));
        printEndPosition(idxPyJv[iP], 0, outf);
        printMomentum(pt, outf, true);
        idxPyJv[i] = count++;
      }
    }
  }
  outf << "  // Update velocities according to relative speed." << endl
       << "  for (var i=0; i<particles.length; i++)"
       << " rescaleVelocity(particles[i], 0, i);" << endl;

  count = 0;

  // 3. Strings.
  outf << "  // Strings." << endl;
  for (map<pii,pii>::iterator i=strings.begin(); i!=strings.end(); i++) {
    outf << "  strings.push(new StringTube(new string(), stringTimeStart,"
         << " stringTimeStart," << endl << "    " << idxPyJv[i->first.first]
         << ", " << idxPyJv[i->first.second] << "));" << endl;
    i->second.second = count++;
  }

  // Reset counter for index conversion.
  count = 0;

  // Check all production times of hadrons.
  double tProdMin = std::numeric_limits<double>::max();
  for (int i=0; i<(int)event.size(); i++) {
    Particle& pt = event[i];
    if (pt.statusAbs() > 80 && pt.statusAbs() < 100)
      if (tProd(pt) < tProdMin) tProdMin = tProd(pt);
  }
  double add = -log10(tProdMin)+0.1;

  // 4. Primary hadrons.
  outf << "  // Primary hadrons." << endl;
  for (int i=0; i<(int)event.size(); i++) {
    Particle& pt = event[i];
    if (pt.statusAbs() > 80 && pt.statusAbs() < 90) {
      // Add the parent parton indices and string indices.
      vector<int> iParents = findStringParents(event, i);
      vector<int> iStrings;
      while (true) {
        bool found = false;
        for (map<pii,pii>::iterator j=strings.begin(); j!=strings.end(); j++) {
          for (int k=0; k<(int)iParents.size(); k++) {
            int indices[2] = { j->first.first, j->first.second };
            for (int l=0; l<2; l++) if (indices[l] == iParents[k]) {
              if (find(iParents.begin(), iParents.end(), indices[(l+1)%2]) ==
                iParents.end()) {
                iParents.push_back(indices[(l+1)%2]);
                found = true;
              }
              if (find(iStrings.begin(), iStrings.end(), j->second.second) ==
                iStrings.end()) iStrings.push_back(j->second.second);
            }
          }
        }
        if (!found) break;
      }
      outf << "  primaryHadrons.push(new PrimaryHadron(" << endl << "    "
           << particle(pt,random) << "," << endl << "    primHadTimeStart+"
           << log10(tProd(pt))+add << "*tauTimeMult, ";
      if (pt.status() > 0) outf << "timeEnd," << endl;
      else outf << "primHadTimeStart+" << (log10(tProd(pt))+add) +
                   (log10(tProd(event[pt.daughter1()]))+add)
                << "*tauTimeMult," << endl;
      outf << "    new THREE.Vector3(" << pt.xProd()*MM2FM << ", "
           << pt.yProd()*MM2FM << ", "<< pt.zProd()*MM2FM << ")," << endl;
      printMomentum(pt, outf, false);
      outf << "    [";
      for (int j=0, N=(int)iParents.size(); j<N; j++)
        outf << idxPyJv[iParents[j]] << (j < N-1 ? ", " : "");
      outf << "], [";
      for (int j=0, N=(int)iStrings.size(); j<N; j++)
        outf << iStrings[j] << (j < N-1 ? ", " : "");
      outf << "]));" << endl;
      idxPyJvPH[i] = count++;
    }
  }
  outf << "  // Update velocities according to relative speed." << endl
       << "  for (var i=0; i<primaryHadrons.length; i++)" << endl
       << "    rescaleVelocity(primaryHadrons[i], 1, i);" << endl;
  outf << "  // Update string end times." << endl
       << "  setStringTimes();" << endl;
  outf << "  // Update positions." << endl
       << "  for (var i=0; i<primaryHadrons.length; i++)" << endl
       << "    setPrimaryHadronPosition(primaryHadrons[i]);" << endl;

  // Reset counter for index conversion.
  count = 0;

  // 5. Decay products.
  outf << "  // Decay products." << endl;
  for (int i=0; i<(int)event.size(); i++) {
    Particle& pt = event[i];
    if (pt.statusAbs() > 90 && pt.statusAbs() < 100) {
      outf << "  decayProducts.push(new DecayProduct(" << endl << "    "
           << particle(pt,random) << "," << endl << "    ";
      bool prim = (event[pt.mother1()].statusAbs() < 90);
      int index = (prim ? idxPyJvPH[pt.mother1()] : idxPyJvDH[pt.mother1()]);
      //string base = (prim ? "primaryHadrons[" : "decayProducts[")+STRING(index);
      string base = (prim ? "primaryHadrons[" : "decayProducts[")+std::to_string(index);
      outf << base << "].end, ";
      if (pt.status() > 0) outf << "timeEnd," << endl;
      else outf << base << "].end+" << log10(tProd(event[pt.daughter1()]))+add
                << "*tauTimeMult," << endl;
      printEndPosition(index, prim ? 1 : 2, outf);
      printMomentum(pt, outf, true);
      idxPyJvDH[i] = count++;
    }
  }
  outf << "  // Update velocities according to relative speed." << endl
       << "  for (var i=0; i<decayProducts.length; i++)" << endl
       << "    rescaleVelocity(decayProducts[i], 2, i);" << endl;

  // Copy input to output file, after end tag.
  if (inpf.is_open()) {
    string line;
    bool writeNow = false;
    while (getline(inpf,line)) {
      if (line == "//**** END ****//") writeNow = true;
      else if (writeNow) outf << line << endl;
    }
    inpf.close();
  }
}
