
// DIRE includes.
#include "Dire/Dire.h"

// Pythia includes.
#include "Pythia8/Pythia.h"
#ifdef HEPMC2
#include "Pythia8Plugins/HepMC2.h"
#endif

// OpenMP includes.
#ifdef OPENMP
#include <omp.h>
#endif

#include "DirePlugins/Flux/NeutrinoFlux.h"
#include "DirePlugins/ApfelHooks.h"

//#include "DirePlugins/BiasDIS.h"

using namespace Pythia8;

//static const double LARGE_WT = 5e2;
static const double LARGE_WT = 1e2;

//==========================================================================

// The following functions analyze a scattering event and save the event in
// an output format that can be converted into a postscript figure using the
// "graphviz" program. Written by N. Fischer, 2017

string py_status(int stAbs) {
  string status    = "";
       if (stAbs > 20 && stAbs <  30) status = "hardProcess";
  else if (stAbs > 30 && stAbs <  40) status = "MPI";
  else if (stAbs > 40 && stAbs <  50) status = "ISR";
  else if (stAbs > 50 && stAbs <  60) status = "FSR";
  else if (stAbs > 60 && stAbs <  70) status = "beamRemnants";
  else if (stAbs > 70 && stAbs <  80) status = "hadronizationPrep";
  else if (stAbs > 80 && stAbs <  90) status = "hadronization";
  else if (stAbs > 90 && stAbs < 110) status = "decays";
  else                                status = "default";
  return status;
}

void makeArrow(map< pair<string,string>, string >* arrows,
  string identParent, string identChild) {
  pair<string,string> key = make_pair(identParent,identChild);
  string value = "  " + identParent + " -> " + identChild
    + " [weight=2,label=\" \"];";
  arrows->insert( pair< pair<string,string>, string>(key, value) );
}

void printEvent(Event& evt, string fileName = "event") {

  bool simplifyHadronization = true;
  bool addLegend             = true;
  map<string, pair<string,string> > colMap;
  colMap["default"]           = make_pair("white","black");
  colMap["hardProcess"]       = make_pair("red","black");
  colMap["MPI"]               = make_pair("lightsalmon","black");
  colMap["ISR"]               = make_pair("lightseagreen","black");
  colMap["FSR"]               = make_pair("limegreen","black");
  colMap["beamRemnants"]      = make_pair("mediumpurple","black");
  colMap["hadronizationPrep"] = make_pair("blue","black");
  colMap["hadronization"]     = make_pair("blue","black");
  colMap["decays"]            = make_pair("lightskyblue","black");

  map<string,string> blobs;
  map< pair<string,string>, string > arrows;
  vector< vector<int> > hadronGroups;
  vector< vector<int> > hadronParents;
  
  for (int i=1; i<(int)evt.size(); i++) {
    // Identifier of that particle.
    //string ident     = "F" + std::to_string(10000+i);
    string ident     = "F" + std::to_string(10000+i);
    // Name that will appear in graph.
    //string label     = std::to_string(evt[i].id()) + " (" + evt[i].name() + ")";
    string label    = std::to_string(evt[i].id()) + " (" + evt[i].name() + ")";
    // Find particle group for colors.
    string status   = py_status(evt[i].statusAbs());
    // Skip hadrons and decay products for simplified output.
    if (simplifyHadronization && 
      (status == "decays" || status == "hadronization") ) continue;
    // Special treatment of hadronization particles for simplified output.
    bool checkDaughters = simplifyHadronization;
    if (status != "hadronizationPrep" && status != "beamRemnants")
        checkDaughters = false;
    // Check that daughters are are part of hadronization
    if (checkDaughters) {
      vector<int> daus = evt[i].daughterList();
      for (int j=0; j<(int)daus.size(); j++)
        if (py_status(evt[daus[j]].statusAbs()) != "hadronization")
          checkDaughters = false;
    }
    if (checkDaughters) {
      vector<int> daus = evt[i].daughterList();
      // Check if other particles in preparation has same daughter list.
      bool foundSameDaus = false;
      for (int j=0; j<(int)hadronGroups.size(); j++) {
        if (daus.size() == hadronGroups[j].size()) {
          foundSameDaus = true;
          for (int k=0; k<(int)hadronGroups[j].size(); k++)
            if (daus[k] != hadronGroups[j][k]) foundSameDaus = false;
          if (foundSameDaus) {
            hadronParents[j].push_back(i);
            break;
          }
        }
      }
      if (!foundSameDaus) {
        hadronGroups.push_back(daus);
        vector<int> parents; parents.push_back(i);
        hadronParents.push_back(parents);
      }
      if (status == "hadronizationPrep") continue;
    }
    // Setup the graph for the particle.
    pair<string,string> colors = colMap[status];
    string fillcolor = colors.first, fontcolor = colors.second;
    blobs[ident] = "  " + ident + " [shape=box,style=filled,fillcolor=\""
      + fillcolor + "\",fontcolor=\"" + fontcolor + "\",label=\""
      + label + "\"];";
    // Setup arrow to mother(s).
    int mot1 = evt[i].mother1(), mot2 = evt[i].mother2();
    if ( i > 3 && (mot1 == 0 || mot2 == 0) ) 
      //makeArrow(&arrows, "F"+std::to_string(10000+max(mot1,mot2)), ident);
      makeArrow(&arrows, "F"+std::to_string(10000+max(mot1,mot2)), ident);
    // Setup arrow to daughter(s).
    if (!checkDaughters) {
      vector<int> daus = evt[i].daughterList();
      for (int j=0; j<(int)daus.size(); j++)
        //makeArrow(&arrows, ident, "F"+std::to_string(10000+daus[j]));
        makeArrow(&arrows, ident, "F"+std::to_string(10000+daus[j]));
    }
  }

  // Add the hadron groups for simplified output.
  map< pair<string,string>, string > arrowsSav = arrows;
  for (int i=0; i<(int)hadronGroups.size(); i++) {
    // Identifier of that group.
    //string ident     = "G" + std::to_string(10000+i);
    string ident     = "G" + std::to_string(10000+i);
    pair<string,string> colors = colMap["hadronization"];
    string fillcolor = colors.first, fontcolor = colors.second;
    string line      = "  " + ident + " [shape=none,\n     label = <<"
      "table border=\"0\" cellspacing=\"0\">\n";
    for (int j=0; j<(int)hadronGroups[i].size(); j++) {
      // Name that will appear in graph.
      //string label = std::to_string(evt[hadronGroups[i][j]].id()) + " ("
      string label = std::to_string(evt[hadronGroups[i][j]].id()) + " ("
        + evt[hadronGroups[i][j]].name() + ")";
      //line += ( "               <tr><td port=\"port" + std::to_string(j)
      line += ( "               <tr><td port=\"port" + std::to_string(j)
        + "\" border=\"1\" bgcolor=\"" + fillcolor + "\"><font color=\""
        + fontcolor + "\">" + label + "</font></td></tr>\n" );
    }
    line += "             </table>> ];";
    // Add the group to the graph.
    blobs[ident] = line;
    // Add an arrow from each parent to the group.
    for (int j=0; j<(int)hadronParents[i].size(); j++) {
      // Identifier of that parent.
      //string identParent = "F"+std::to_string(10000+hadronParents[i][j]);
      string identParent = "F"+std::to_string(10000+hadronParents[i][j]);
      // List of particles to be erased.
      vector<string> toErase;
      toErase.push_back(identParent);
      // Check if parent is beam remnant.
      bool parentIsBR = (py_status(evt[hadronParents[i][j]].statusAbs()) ==
        "beamRemnants");
      if (parentIsBR) {
        makeArrow(&arrows, identParent, ident);
      } else {
        int nrGP1 = evt[hadronParents[i][j]].mother1();
        int nrGP2 = evt[hadronParents[i][j]].mother2();
        if (nrGP1 > 0) {
          // Trace back one more generation if double hadronization prep.
          if (py_status(evt[nrGP1].statusAbs()) == "hadronizationPrep") {
            toErase.push_back("F"+std::to_string(10000+nrGP1));
            int nrGGP1 = evt[nrGP1].mother1();
            int nrGGP2 = evt[nrGP1].mother2();
            if (nrGGP1 > 0) makeArrow(&arrows, "F"+std::to_string(10000+nrGGP1), ident);
            if (nrGGP2 > 0 && nrGGP2 != nrGGP1)
              makeArrow(&arrows, "F"+std::to_string(10000+nrGGP2), ident);
          } else makeArrow(&arrows, "F"+std::to_string(10000+nrGP1), ident);
        }
        if (nrGP2 > 0 && nrGP2 != nrGP1) {
          // Trace back one more generation if double hadronization prep.
          if (py_status(evt[nrGP2].statusAbs()) == "hadronizationPrep") {
            toErase.push_back("F"+std::to_string(10000+nrGP2));
            int nrGGP1 = evt[nrGP2].mother1();
            int nrGGP2 = evt[nrGP2].mother2();
            if (nrGGP1 > 0) makeArrow(&arrows, "F"+std::to_string(10000+nrGGP1), ident);
            if (nrGGP2 > 0 && nrGGP2 != nrGGP1)
              makeArrow(&arrows, "F"+std::to_string(10000+nrGGP2), ident);
          } else makeArrow(&arrows, "F"+std::to_string(10000+nrGP2), ident);
        }
        // Erase any parents that might be left in the graph.
        for (int iToE=0; iToE<(int)toErase.size(); iToE++)
          if (blobs.find(toErase[iToE]) != blobs.end())
            blobs.erase(toErase[iToE]);
        for (map< pair<string,string>, string >::iterator k=arrowsSav.begin();
          k!=arrowsSav.end(); k++) {
          for (int iToE=0; iToE<(int)toErase.size(); iToE++) {
            if (k->first.second == toErase[iToE]) 
              arrows.erase(k->first);
          }
        }
      }
    }
  }

  // Write output.
  ofstream outfile;
  outfile.open((char*)(fileName+".dot").c_str());
  outfile << "digraph \"event\" {" << endl
          << "  rankdir=LR;" << endl;
  for (map<string,string>::iterator iBlob=blobs.begin(); iBlob!=blobs.end();
    iBlob++) outfile << iBlob->second << endl;
  for (map< pair<string,string>, string >::iterator iArrow=arrows.begin();
    iArrow!=arrows.end(); iArrow++) outfile << iArrow->second << endl;
  // Add a legend, skip default.
  if (addLegend) {
    outfile << "  { rank = source;" << endl
            << "    Legend [shape=none, margin=0, label=<<table border=\"0\""
            << " cellspacing=\"0\">" << endl
            << "     <tr><td port=\"0\" border=\"1\"><b>Legend</b></td></tr>" << endl;
    int count = 1;
    for (map<string, pair<string,string> >::iterator iLeg=colMap.begin();
      iLeg!=colMap.end(); iLeg++) {
      if (iLeg->first == "default") continue;
      if (iLeg->first == "hadronizationPrep") continue;
      if (simplifyHadronization && iLeg->first == "decays") continue;
      string fillcolor = iLeg->second.first;
      string fontcolor = iLeg->second.second;
      outfile << "     <tr><td port=\"port" << count << "\" border=\"1\" "
              << "bgcolor=\"" << fillcolor << "\"><font color=\"" << fontcolor
              << "\">" << iLeg->first << "</font></td></tr>" << endl;
      count++;
    }
    outfile << "    </table>" << endl << "   >];" << endl << "  }" << endl;
  }
  outfile << "}" << endl;
  outfile.close();

  cout << "\n\nPrinted one event to output file " << fileName + ".dot\n";
  if (system(NULL)) {
    if (system("which dot > /dev/null 2>&1") == 0) {
      cout << "Producing .ps figure by using the 'dot' command." << endl;
      string command =  "dot -Tps " + fileName + ".dot -o " + fileName+".ps"; 
      if (system(command.c_str()) == 0)
        cout << "Stored event visualization in file " << fileName+".ps" << endl;
      else
        cout << "Failed to store event visualization in file." << endl;
    }
  } else {
    cout << "You can now produce a .ps figure by using the 'dot' command:\n\n"
      << "dot -Tps " << fileName << ".dot -o " << fileName << ".ps" << "\n\n";
    cout << "Note: 'dot' is part of the 'graphviz' package.\n"
      << "You might want to install this package to produce the .ps event"
      << endl << endl;
  }

}

//==========================================================================
// An example Dire main program.

int main( int argc, char* argv[] ){

  // Get command-line arguments
  vector<string> arguments;
  for (int i = 0; i < argc; ++i) { 
    arguments.push_back(string(argv[i]));
    if (arguments.back() == "--visualize_event")
      arguments.push_back(" ");
  }

  // Print help.
  for (int i = 0; i < int(arguments.size()); ++i) {
    if ( arguments[i] == "--help" || arguments[i] == "-h") {
      cout << "\n"
        << "Simple standardized executable for the Pythia+Dire event "
        << "generator.\n\n" 
        << "Usage:\n\n"
        << "dire [option] <optionValue> [option] <optionValue> ...\n\n"
        << "Examples:\n\n"
        << "dire --nevents 50 --setting \"WeakSingleBoson:ffbar2gmZ = on\"\n"
        << "dire --input main/lep.cmnd --hepmc_output myfile.hepmc\n\n"
        << "Options:\n\n"
        << "  --visualize_event       :"
        << " Saves one event for visualization of event generation steps.\n"
        << "  --nevents N             :"
        << " Generate N events (overwrites default value and\n"
        << "                           "
        << " number of events in input settings file).\n"
        << "  --nthreads N            :"
        << " Use N threads, takes effect only if Dire was configured\n"
        << "                            with OpenMP\n"
        << "  --input FILENAME        :"
        << " Use file FILENAME to read & use Pythia settings.\n" 
        << "                            Multiple input files are allowed.\n" 
        << "  --hepmc_output FILENAME :"
        << " Store generated events in HepMC file FILENAME.\n" 
        << "  --lhef_output FILENAME :"
        << " Store generated events in LHEF  file FILENAME.\n" 
        << "  --setting VALUE         :"
        << " Use the Pythia/Dire setting VALUE for event generation, e.g.\n"
        << "                            --setting Beams:eCM=100.0\n"
        << "                            --setting \"Beams:idA = -11\"\n"
        << "                            --setting \"PartonLevel:MPI = off\"\n"
        << "                           "
        << " possible Pythia/Dire settings can be found in the\n"
        << "                            respective online manuals\n\n"
        << "More documentation can be found on dire.gitlab.io\n" << endl;
      return 0;
    }
  }

  // Parse command-line arguments
  // input file
  vector<string>::iterator it
     = std::find(arguments.begin(),arguments.end(),"--input");
  string input  = (it != arguments.end()) ? *(it+1) : "";
  // output hepmc file
  it = std::find(arguments.begin(),arguments.end(),"--hepmc_output");
  string hepmc_output = (it != arguments.end()) ? *(it+1) : "";
  // output lhe file
  it = std::find(arguments.begin(),arguments.end(),"--lhef_output");
  string lhef_output = (it != arguments.end()) ? *(it+1) : "";
  // number of events to generate
  it = std::find(arguments.begin(),arguments.end(),"--nevents");
  int nevents = (it != arguments.end()) ? atoi((*(it+1)).c_str()) : -1;
#ifdef OPENMP
  // number of threads
  it = std::find(arguments.begin(),arguments.end(),"--nthreads");
  int nThreads = (it != arguments.end()) ? atoi((*(it+1)).c_str()) : 1;
#endif
  // visualize_event flag
  it = std::find(arguments.begin(),arguments.end(),"--visualize_event");
  bool visualize_event     = (it != arguments.end());
  string visualize_output  = (input == "") ? "event" : "event-" + input;
  replace(visualize_output.begin(), visualize_output.end(), '/', '-');

  // run executable for default pythia only.
  it = std::find(arguments.begin(),arguments.end(),"--run_default_pythia");
  bool run_default_pythia = false;
  if (it != arguments.end()) run_default_pythia = true;

  vector<Pythia*> pythiaPtr;
  vector<Dire*> direPtr;
  // Allow Pythia to use Dire merging classes. 
  vector<DireMerging*> mergingPtr;
  vector<DireHardProcess*> hardProcessPtr;
  vector<DireMergingHooks*> mergingHooksPtr;

  // Read input files.
  vector<string> input_file;
  for (int i = 0; i < int(arguments.size()); ++i)
    if (arguments[i] == "--input" && i+1 <= int(arguments.size())-1)
      input_file.push_back(arguments[i+1]);
  if (input_file.size() < 1) input_file.push_back("");

  // For default Pythia run, strip input files from Dire settings flags.
  vector<string> default_pythia_input_file;
  if (run_default_pythia) {
    for (int i = 0; i < int(input_file.size()); ++i) {

      istream * infile;
      infile = new igzstream(input_file[i].c_str());

      default_pythia_input_file.push_back(input_file[i]+".tmp_pythia");
      ofstream outfile;
      outfile.open(default_pythia_input_file.back());

      string currentLine;
      while (getline(*infile, currentLine)) {
        if ( currentLine.find("Dire") != string::npos
          || currentLine.find("Enhance") != string::npos
          || currentLine.find("ShowerPDF") != string::npos
          || currentLine.find("Variations") != string::npos)
          currentLine = "#"+currentLine;
        outfile << currentLine << endl;
      }
      delete infile;
      outfile.close();
    }

    input_file = default_pythia_input_file;
  }

  // For several settings files as input, check that they use
  // a different process.
  if (input_file.size() > 1) {
    bool sameProcess = false;
    for (int i = 1; i < int(input_file.size()); ++i)
      if (input_file[i] == input_file[i-1]) sameProcess = true;
    if (sameProcess)
      cout << "WARNING: several input files with the same name\n"
        << " found; this will lead to a wrong cross section!\n";
  }

  std::streambuf *old = cout.rdbuf();
  stringstream ss;
  for (int i = 0; i < int(input_file.size()); ++i) {
    ss.str("");
    // Redirect output so that Pythia banner will not be printed twice.
    if(i>0) cout.rdbuf (ss.rdbuf());
    pythiaPtr.push_back( new Pythia());
    // Restore print-out.
    cout.rdbuf (old);
    direPtr.push_back( new Dire());
  }

#ifdef OPENMP
  old = cout.rdbuf();
  int nThreadsMax = omp_get_max_threads();
  int nThreadsReq = min(nThreads,nThreadsMax);

  //#pragma omp parallel
  //{
  //  #pragma omp single
  //  cout << "num_threads = " << omp_get_num_threads() << endl;
  //}

  // Divide a single Pythia object into several, in case of multiple threads.
  int nPythiaOrg = (int)pythiaPtr.size();

  if (nThreadsReq > 1 && (nPythiaOrg == 1 || nThreadsReq%nPythiaOrg ==0)) {
    int niterations(0);
    for (int i = nPythiaOrg; i < nThreadsReq; ++i) {
      if (i%nPythiaOrg == 0) niterations++;
      int ifile    = i-niterations*nPythiaOrg;
      string sfile = input_file[ifile];
      //input_file.push_back(input_file.front());
      input_file.push_back(sfile);
      ss.str("");
      // Redirect output so that Pythia banner will not be printed twice.
      cout.rdbuf (ss.rdbuf());
      pythiaPtr.push_back( new Pythia());
      direPtr.push_back( new Dire());
    }
  }

  // Restore print-out.
  cout.rdbuf (old);

  bool doParallel = true;
  int  nPythiaAct = (int)pythiaPtr.size();
  // The number of Pythia objects exceeds the number of available threads.
  if (nPythiaAct > nThreadsReq) {
    cout << "WARNING: The number of requested Pythia instances exceeds the\n"
      << " number of available threads! No parallelization will be done!\n";
    nThreadsReq = 1;
    doParallel  = false;
  } else if (nPythiaAct == 1) {
    cout << "WARNING: The number of requested Pythia instances still one!\n"
      << " No parallelization will be done!\n";
    nThreadsReq = 1;
    doParallel  = false;
  } else if (nPythiaAct < nThreadsReq) {
    cout << "WARNING: The number of requested Pythia instances too small!\n"
      << " Reset to minimal parallelization!\n";
    nThreadsReq = nPythiaAct;
  }

  // Only print with first Pythia instance to avoid output mangling.
  if (doParallel) {
    pythiaPtr[0]->readString("Init:showProcesses = off");
    pythiaPtr[0]->readString("Init:showMultipartonInteractions = off");
    pythiaPtr[0]->readString("Init:showChangedParticleData = off");
    pythiaPtr[0]->readString("Next:numberShowLHA = 0");
    pythiaPtr[0]->readString("Next:numberShowProcess = 0");
    pythiaPtr[0]->readString("Next:numberShowEvent = 0");
    pythiaPtr[0]->readString("Next:numberShowInfo = 0");
    pythiaPtr[0]->readString("SLHA:verbose = 0");
    for (int j = 1; j < int(pythiaPtr.size()); ++j){
      pythiaPtr[j]->readString("Print:quiet = on");
      pythiaPtr[j]->readString("SLHA:verbose = 0");
    }
  }

#endif

  // Read command line settings.
  for (int i = 0; i < int(arguments.size()); ++i) {
    if (arguments[i] == "--setting" && i+1 <= int(arguments.size())-1) {
      string setting = arguments[i+1];
      replace(setting.begin(), setting.end(), '"', ' ');      

      // Skip Dire settings at this stage.
      if (setting.find("Dire") != string::npos) continue;
      if (setting.find("Enhance") != string::npos) continue;

      for (int j = 0; j < int(pythiaPtr.size()); ++j)
        pythiaPtr[j]->readString(setting);

    }
  }

  // Initialize Dire settings.
  for (int i = 0; i < int(direPtr.size()); ++i)
    if (!run_default_pythia) direPtr[i]->initSettings(*pythiaPtr[i]);

  // Read command line settings again and overwrite file settings.
  for (int i = 0; i < int(arguments.size()); ++i) {
    if (arguments[i] == "--setting" && i+1 <= int(arguments.size())-1) {
      string setting = arguments[i+1];
      replace(setting.begin(), setting.end(), '"', ' ');      
      for (int j = 0; j < int(pythiaPtr.size()); ++j)
        pythiaPtr[j]->readString(setting);
    }
  }
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    if (i < int(input_file.size()) && input_file[i] != "") {
      pythiaPtr[i]->readFile(input_file[i].c_str());
      pythiaPtr[i]->settings.mode("Main:numberOfSubruns",input_file.size());
    }

  }

  // Two classes to do the two PDFs externally. Hand pointers to Pythia.
  PDF* pdfAPtr = NULL;
  PDF* pdfBPtr = NULL;
  if ( pythiaPtr.front()->settings.flag("WeakBosonExchange:ff2ff(t:Zp)")
    || pythiaPtr.front()->settings.flag("WeakBosonExchange_elastic:ff2ff(t:Zp)"))
    pdfAPtr = new MiniBooneNeutrinoFlux(
      pythiaPtr.front()->settings.mode("Beams:idA"));
  //if (pythiaPtr.front()->settings.flag("WeakBosonExchange:ff2ff(t:W)"))
  //  pdfAPtr = new GenericNeutrinoFlux(
  //    pythiaPtr.front()->settings.mode("Beams:idA"),
  //    pythiaPtr.front()->settings.parm("Beams:eA"));
  //if (pythiaPtr.front()->settings.flag("WeakBosonExchange:ff2ff(t:W)"))
  //  pdfAPtr = new GaussNeutrinoFlux(
  //    pythiaPtr.front()->settings.mode("Beams:idA"),
  //    pythiaPtr.front()->settings.parm("Beams:eA"),
  //    4.51551e+04, // Norm of Gaussian
  //    3.03110e+00, // Mean of Gaussian
  //    8.35974e-01 // Width of Gaussian
  //    );
  if (pythiaPtr.front()->settings.flag("WeakBosonExchange:ff2ff(t:W)"))
    pdfAPtr = new TestDuneNeutrinoFlux(
      pythiaPtr.front()->settings.mode("Beams:idA"));

  //BiasDIS* biasDIS = new BiasDIS();

  // Allow Pythia to use Dire merging classes. 
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    mergingPtr.push_back(0);
    hardProcessPtr.push_back(0);
    mergingHooksPtr.push_back(0);
    if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
      || pythiaPtr[i]->settings.flag("Dire:doMECs")
      || pythiaPtr[i]->settings.flag("Dire:doMEM")) {
      mergingPtr.back()      = new DireMerging();
      hardProcessPtr.back()  = new DireHardProcess();
      mergingHooksPtr.back() = new DireMergingHooks();
      mergingHooksPtr.back()->setHardProcessPtr( hardProcessPtr.back() );
      if (!run_default_pythia) pythiaPtr[i]->setMergingHooksPtr(mergingHooksPtr.back());
      if (!run_default_pythia) pythiaPtr[i]->setMergingPtr(mergingPtr.back());
    }
    if (pdfAPtr != NULL) pythiaPtr[i]->setPDFAPtr(pdfAPtr);
    if (pdfBPtr != NULL) pythiaPtr[i]->setPDFBPtr(pdfBPtr);
    //pythiaPtr[i]->setUserHooksPtr(biasDIS);
  }

  // TODO: Need to parse this to get the PDF set name.
  // string pdfSet = pythiaPtr.front()->word("PDF:pHardSet");
  ApfelHooks* apfelHooks = new ApfelHooks();

  for (int i = 0; i < int(direPtr.size()); ++i)
    if (!run_default_pythia) {
      direPtr[i]->init(*pythiaPtr[i], input_file[i].c_str(), -999, NULL, apfelHooks);
    } else {
      if (i < int(input_file.size()) && input_file[i] != "")
        pythiaPtr[i]->readFile(input_file[i].c_str());
      pythiaPtr[i]->init();
    }

#ifdef OPENMP
  // A divided single Pythia run does not work with Les Houches events.
  if (nThreadsReq > 1 && nPythiaOrg == 1 &&
    pythiaPtr.front()->mode("Beams:frameType") > 3) {
    cout << "WARNING: can not divide the run into subruns as the\n"
      << " same hard events from the Les Houches file would be\n"
      << " used multiple times!\n";
    // Clean-up.
    nThreadsReq = 1;
    for (int i = 1; i < int(pythiaPtr.size()); ++i) {
      if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
        || pythiaPtr[i]->settings.flag("Dire:doMECs")
        || pythiaPtr[i]->settings.flag("Dire:doMEM")) {
        delete mergingPtr[i];      mergingPtr[i]=0;
        delete hardProcessPtr[i];  hardProcessPtr[i]=0;
        delete mergingHooksPtr[i]; mergingHooksPtr[i]=0;
      }
      delete pythiaPtr[i]; pythiaPtr[i]=0;
      delete direPtr[i];   direPtr[i]=0;
    }
  }
  // Add random seeds for parallelization of a single Pythia run.
  bool splitSingleRun = false;
  if (nThreadsReq > 1 && nPythiaOrg == 1) {
    splitSingleRun = true;
    int currentSeed  = pythiaPtr.front()->settings.mode("Random:seed");
    int randomOffset = (currentSeed>0) ? currentSeed : 100;
    for (int j = 0; j < int(pythiaPtr.size()); ++j) {
      pythiaPtr[j]->readString("Random:setSeed = on");
      pythiaPtr[j]->readString("Random:seed = "+std::to_string(randomOffset+j));
    }
  }
#endif

  // Transfer initialized shower weights pointer to merging class.
  for (int i = 0; i < int(direPtr.size()); ++i)
    if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
      || pythiaPtr[i]->settings.flag("Dire:doMECs")
      || pythiaPtr[i]->settings.flag("Dire:doMEM")) {
      mergingPtr[i]->initPtrs(direPtr[i]->weightsPtr, direPtr[i]->timesPtr,
        direPtr[i]->spacePtr, direPtr[i]->timesPtr->direInfoPtr);
      mergingPtr[i]->setHelpersPtr(&direPtr[i]->helpers);
      mergingHooksPtr[i]->setHelpersPtr(&direPtr[i]->helpers);
    }

  int nEventEst = pythiaPtr.front()->settings.mode("Main:numberOfEvents");
  if (nevents > 0) nEventEst = nevents;

  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    pythiaPtr[i]->settings.mode("Main:numberOfEvents", nEventEst);

  int nEventEstEach = nEventEst;
#ifdef OPENMP
  // Number of events per thread.
  if (nThreadsReq > 1) {
    while (nEventEst%nThreadsReq != 0) nEventEst++;
    nEventEstEach = nEventEst/nThreadsReq;
  }
#endif

  // Switch off all showering and MPI when estimating the cross section,
  // and re-initialise (unfortunately).
  bool fsr = pythiaPtr.front()->flag("PartonLevel:FSR");
  bool isr = pythiaPtr.front()->flag("PartonLevel:ISR");
  bool mpi = pythiaPtr.front()->flag("PartonLevel:MPI");
  bool had = pythiaPtr.front()->flag("HadronLevel:all");
  bool rem = pythiaPtr.front()->flag("PartonLevel:Remnants");
  bool chk = pythiaPtr.front()->flag("Check:Event");
  vector<bool> merge;
  if (!visualize_event) {
    for (int i = 0; i < int(pythiaPtr.size()); ++i) {
      bool doMerge = pythiaPtr[i]->flag("Merging:doMerging");
      merge.push_back(doMerge);
      pythiaPtr[i]->settings.flag("PartonLevel:FSR",false);
      pythiaPtr[i]->settings.flag("PartonLevel:ISR",false);
      pythiaPtr[i]->settings.flag("PartonLevel:MPI",false);
      pythiaPtr[i]->settings.flag("HadronLevel:all",false);
      pythiaPtr[i]->settings.flag("PartonLevel:Remnants",false);
      pythiaPtr[i]->settings.flag("Check:Event",false);
      if (doMerge) pythiaPtr[i]->settings.flag("Merging:doXSectionEstimate", true);
    }
  }

  // Force PhaseSpace:pTHatMinDiverge to something very small to not bias DIS.
  for (int j = 0; j < int(pythiaPtr.size()); ++j)
    pythiaPtr[j]->settings.forceParm("PhaseSpace:pTHatMinDiverge",1e-6);
  for (int i = 0; i < int(arguments.size()); ++i) {
    if (arguments[i] == "--setting" && i+1 <= int(arguments.size())-1) {
      string setting = arguments[i+1];
      replace(setting.begin(), setting.end(), '"', ' ');      
      if (setting.find("PhaseSpace:pTHatMinDiverge") != string::npos) {
        string value = setting.substr(setting.find("=")+1);
        while(value.find(" ", 0) != string::npos)
          value.erase(value.begin()+value.find(" ",0));
        for (int j = 0; j < int(pythiaPtr.size()); ++j)
          pythiaPtr[j]->settings.forceParm("PhaseSpace:pTHatMinDiverge",
            atof(value.c_str()));
      }
    }
  }

  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    pythiaPtr[i]->init();

  // Cross section estimate run.
  vector<double> nash, sumsh;
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    nash.push_back(0.);
    sumsh.push_back(0.);
  }

  // Save a single event for event generation visualization.
  if (visualize_event) {
    while ( !pythiaPtr.front()->next() )
      if ( pythiaPtr.front()->info.atEndOfFile() ) break;
    printEvent(pythiaPtr.front()->event, visualize_output);
    cout << "\nCreated event visualization. Exiting event generation.\n"<<endl; 
    // Clean-up.
    for (int i = 0; i < int(pythiaPtr.size()); ++i) {
      if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
        || pythiaPtr[i]->settings.flag("Dire:doMECs")
        || pythiaPtr[i]->settings.flag("Dire:doMEM")) {
        delete mergingPtr[i];      mergingPtr[i]=0;
        delete hardProcessPtr[i];  hardProcessPtr[i]=0;
        delete mergingHooksPtr[i]; mergingHooksPtr[i]=0;
      }
      delete pythiaPtr[i]; pythiaPtr[i]=0;
      delete direPtr[i];   direPtr[i]=0;
    }
    return 0;
  }

#ifdef OPENMP
#pragma omp parallel num_threads(nThreadsReq)
{
  for (int i = 0; i < nEventEstEach; ++i) {
    vector<int> pythiaIDs;
    // If parallelization can not be done, loop through all
    // Pythia objects.
    if (!doParallel)
      for (int j = 0; j < int(pythiaPtr.size()); ++j)
        pythiaIDs.push_back(j);
    else pythiaIDs.push_back(omp_get_thread_num());
    for (int id = 0; id < int(pythiaIDs.size()); ++id) {
      int j = pythiaIDs[id];
      if ( !pythiaPtr[j]->next() ) {
        if ( pythiaPtr[j]->info.atEndOfFile() ) break;
        else continue;
      }
      sumsh[j] += pythiaPtr[j]->info.weight();
      map <string,string> eventAttributes;
      if (pythiaPtr[j]->info.eventAttributes)
        eventAttributes = *(pythiaPtr[j]->info.eventAttributes);
      string trials = (eventAttributes.find("trials") != eventAttributes.end())
                    ?  eventAttributes["trials"] : "";
      if (trials != "") nash[j] += atof(trials.c_str());
    }
  }
}
#pragma omp barrier
#else

  for (int i = 0; i < nEventEstEach; ++i) {
    for (int j = 0; j < int(pythiaPtr.size()); ++j) {
      if ( !pythiaPtr[j]->next() ) {
        if ( pythiaPtr[j]->info.atEndOfFile() ) break;
        else continue;
      }
      sumsh[j] += pythiaPtr[j]->info.weight();
      map <string,string> eventAttributes;
      if (pythiaPtr[j]->info.eventAttributes)
        eventAttributes = *(pythiaPtr[j]->info.eventAttributes);
      string trials = (eventAttributes.find("trials") != eventAttributes.end())
                    ?  eventAttributes["trials"] : "";
      if (trials != "") nash[j] += atof(trials.c_str());
    }
  }
#endif

  // Store estimated cross sections.
  vector<double> na, xss;
  double natot = 0., xsstot = 0.;
  //old = cout.rdbuf();
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    // Redirect output so that Pythia banner will not be printed twice.
    //stringstream ss;
    ss.str("");
    //cout.rdbuf (ss.rdbuf());
    pythiaPtr[i]->stat();
    na.push_back(pythiaPtr[i]->info.nAccepted());
    xss.push_back(pythiaPtr[i]->info.sigmaGen());
    natot += pythiaPtr[i]->info.nAccepted();
    xsstot += pythiaPtr[i]->info.sigmaGen();
  }
  // Restore print-out.
  //cout.rdbuf (old);

  double avgweight = 1.0;
  //double avgweight = xsstot/natot;

#ifdef HEPMC2
  bool printHepMC = !(hepmc_output == "");
  // Interface for conversion from Pythia8::Event to HepMC one. 
  HepMC::Pythia8ToHepMC ToHepMC;
  // Specify file where HepMC events will be stored.
  HepMC::IO_GenEvent ascii_io(hepmc_output, std::ios::out);
  // Switch off warnings for parton-level events.
  ToHepMC.set_print_inconsistency(false);
  ToHepMC.set_free_parton_exception(false);
  // Do not store cross section information, as this will be done manually.
  ToHepMC.set_store_pdf(false);
  ToHepMC.set_store_proc(false);
  ToHepMC.set_store_xsec(false);
  vector< HepMC::IO_GenEvent* > ascii_io_var;
#endif

  // Create and open file for LHEF 3.0 output.
  LHEF3FromPythia8* lhef3 = NULL;
  if (lhef_output != "") {
    lhef3 = new LHEF3FromPythia8(&pythiaPtr.front()->event,
       &pythiaPtr.front()->settings, &pythiaPtr.front()->info,
       &pythiaPtr.front()->particleData,20);
     lhef3->openLHEF(lhef_output);
     // Write out initialization info on the file.
     lhef3->setInit();
  }

  // Cross section and weights:
  // Total for all runs combined: main.
  double sigmaTotAll(0.);
  // Total for all runs combined: variations.
  vector<double> sigmaTotVarAll;
  // Individual run: main.
  vector<double> sigmaInc, sigmaTot, sumwt, sumwtsq;
  // Individual run: variations.
  vector<vector<double> > sigmaTotVar;
  // Check variations.
  bool doVariationsAll(true);
  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    if ( ! pythiaPtr.front()->settings.flag("Variations:doVariations") )
      doVariationsAll = false;
  if ( doVariationsAll ) {
    //for (int iwt=0; iwt<direPtr.front()->weightsPtr->sizeWeights(); ++iwt) {
    for (int iwt=0; iwt < 3; ++iwt) {
#ifdef HEPMC2
      if (printHepMC) {
        string hepmc_var = hepmc_output + "-" + std::to_string(iwt);
        ascii_io_var.push_back( new HepMC::IO_GenEvent(hepmc_var, std::ios::out));
      }
#endif
      sigmaTotVarAll.push_back(0.);
    }
  }

  if (!run_default_pythia && !doVariationsAll) sigmaTotVarAll.push_back(0.);

  if (run_default_pythia) {
    sigmaTotVarAll.push_back(0.);
  }

  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    sigmaTotVar.push_back(vector<double>());
    if ( doVariationsAll ) {
      //for (int iwt=0; iwt<direPtr.front()->weightsPtr->sizeWeights(); ++iwt)
      for (int iwt=0; iwt < 3; ++iwt)
        sigmaTotVar.back().push_back(0.);
    } else if(run_default_pythia) {
      sigmaTotVar.back().push_back(0.);
    } else if(!run_default_pythia && !doVariationsAll) {
      sigmaTotVar.back().push_back(0.);
    }

    sigmaInc.push_back(0.);
    sigmaTot.push_back(0.);
    sumwt.push_back(0.);
    sumwtsq.push_back(0.);
  }

  int nEvent = pythiaPtr.front()->settings.mode("Main:numberOfEvents");
  if (nevents > 0) nEvent = nevents;

  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    pythiaPtr[i]->settings.mode("Main:numberOfEvents", nEvent);

  int nEventEach = nEvent;
#ifdef OPENMP
  // Number of events per thread.
  if (nThreadsReq > 1) {
    while (nEvent%nThreadsReq != 0) nEvent++;
    nEventEach = nEvent/nThreadsReq;
  }
#endif

  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    pythiaPtr[i]->settings.mode("Main:numberOfEvents", nEventEach);

  /*// Histogram of the event weight.
  Hist shower_weight_histogram("weight",2000,-100.,100.);
  double bw0 = (100+100)/2000.;
  Hist shower_pos_weight_histogram("weight",1000,0.,10.);
  double bw_pos = (10-0)/1000.;
  Hist shower_neg_weight_histogram("weight",1000,0.,10.);
  double bw_neg = (10-0)/1000.;
  Hist log10_shower_pos_weight_histogram("weight",200,-5.,5.);
  double bw_pos_l10 = (5+5)/200.;
  Hist log10_shower_neg_weight_histogram("weight",200,-5.,5.);
  double bw_neg_l10 = (5+5)/200.;*/

  cout << endl << endl << endl;
  cout << "Start generating events" << endl;

  vector<int> ntries;
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    ntries.push_back(0);
    if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
      || pythiaPtr[i]->settings.flag("Dire:doMECs")
      || pythiaPtr[i]->settings.flag("Dire:doMEM"))
      ntries.back() += mergingPtr[i]->ntries;
  }

  // Switch showering and multiple interaction back on.
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    pythiaPtr[i]->settings.flag("PartonLevel:FSR",fsr);
    pythiaPtr[i]->settings.flag("PartonLevel:ISR",isr);
    pythiaPtr[i]->settings.flag("HadronLevel:all",had);
    pythiaPtr[i]->settings.flag("PartonLevel:MPI",mpi);
    pythiaPtr[i]->settings.flag("PartonLevel:Remnants",rem);
    pythiaPtr[i]->settings.flag("Check:Event",chk);
    pythiaPtr[i]->settings.flag("Merging:doMerging",merge[i]);
    pythiaPtr[i]->settings.flag("Merging:doXSectionEstimate", false);
  }

  // Reinitialize Pythia for event generation runs.
  for (int i = 0; i < int(pythiaPtr.size()); ++i)
    pythiaPtr[i]->init();

  bool printLHEF = true;
  if (pythiaPtr.front()->flag("Dire:doTOMTE")) printLHEF = false;

  // Event generation run.
  double evtwmax =-1e15;
  double wmax =-1e15;
  double wmin = 1e15;

  vector <double> wminv;
  vector <double> wmaxv;
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    wminv.push_back(1e15);
    wmaxv.push_back(-1e15);
  }
#ifdef OPENMP
#pragma omp parallel num_threads(nThreadsReq)
{
  for (int i = 0; i < nEventEach; ++i) {

    vector<int> pythiaIDs;
    // If parallelization can not be done, loop through all
    // Pythia objects.
    if (!doParallel)
      for (int j = 0; j < int(pythiaPtr.size()); ++j)
        pythiaIDs.push_back(j);
    else pythiaIDs.push_back(omp_get_thread_num());
    for (int id = 0; id < int(pythiaIDs.size()); ++id) {
      int j = pythiaIDs[id];
      if ( !pythiaPtr[j]->next() ) {
        if ( pythiaPtr[j]->info.atEndOfFile() ) break;
        else continue;
      }

      // Do MEM.    
      if (pythiaPtr[j]->settings.flag("Dire:doMEM")) { ; }

      // Get event weight(s).
      double evtweight = pythiaPtr[j]->info.weight();

      // Do not print zero-weight events.
      if ( evtweight == 0. ) continue;

      // Retrieve the shower weight.
      if (!run_default_pythia) direPtr[j]->weightsPtr->calcWeight(0.);
      if (!run_default_pythia) direPtr[j]->weightsPtr->reset();
      double pswt = (!run_default_pythia)
                  ?  direPtr[j]->weightsPtr->getShowerWeight()
                  : 1.;

#pragma omp critical
{
      evtwmax = max(evtwmax,evtweight);
      wmin = min(wmin,pswt);
      wmax = max(wmax,pswt);
      wminv[j] = min(wminv[j],pswt);
      wmaxv[j] = max(wmaxv[j],pswt);
}

/*#pragma omp critical
{
      shower_weight_histogram.fill( pswt, 1.0);
      if (pswt>0.) shower_pos_weight_histogram.fill( pswt, 1.0);
      if (pswt<0.) shower_neg_weight_histogram.fill(-pswt, 1.0);
      if (pswt>0.) log10_shower_pos_weight_histogram.fill(log10(pswt), 1.0);
      if (pswt<0.) log10_shower_neg_weight_histogram.fill(log10(-pswt), 1.0);
      if (i>0 && i%100==0) {
        ofstream wr;
        wr.open("shower_weights.dat");
        shower_weight_histogram /= double(i)*bw0;
        shower_weight_histogram.table(wr);
        shower_weight_histogram *= double(i)*bw0;
        wr.close();
        wr.open("shower_pos_weights.dat");
        shower_pos_weight_histogram /= double(i)*bw_pos;
        shower_pos_weight_histogram.table(wr);
        shower_pos_weight_histogram *= double(i)*bw_pos;
        wr.close();
        wr.open("shower_neg_weights.dat");
        shower_neg_weight_histogram /= double(i)*bw_neg;
        shower_neg_weight_histogram.table(wr);
        shower_neg_weight_histogram *= double(i)*bw_neg;
        wr.close();
        wr.open("log10_shower_pos_weights.dat");
        log10_shower_pos_weight_histogram /= double(i)*bw_pos_l10;
        log10_shower_pos_weight_histogram.table(wr);
        log10_shower_pos_weight_histogram *= double(i)*bw_pos_l10;
        wr.close();
        wr.open("log10_shower_neg_weights.dat");
        log10_shower_neg_weight_histogram /= double(i)*bw_neg_l10;
        log10_shower_neg_weight_histogram.table(wr);
        log10_shower_neg_weight_histogram *= double(i)*bw_neg_l10;
        wr.close();
      }
}*/

      //double wtcheck = evtweight*pswt;
      double wtcheck = pswt;
      if ( pythiaPtr[j]->info.lhaStrategy() != 0
        && pythiaPtr[j]->info.lhaStrategy() != 3)
        wtcheck /= 1e9;

//      if (abs(pswt) > 1e3) {
      if (abs(wtcheck) > LARGE_WT || abs(pswt) > LARGE_WT) {
#pragma omp critical
{
        cout << scientific << setprecision(8)
          << "Warning in DIRE main program dire.cc: Large shower weight wt="
          << pswt << endl;
        if (abs(pswt) > 1e4) { 
          cout << "Warning in DIRE main program dire.cc: Shower weight larger"
            << " than 10000. Discard event with rare shower weight fluctuation."
            << endl;
          evtweight = 0.;
          // Print diagnostic output.
          //if (!run_default_pythia) direPtr[j]->direInfo.printMessages(1);
        }
        evtweight = 0.;
//        if (!run_default_pythia) direPtr[j]->direInfo.printMessages(1); 
}
      }


if (std::isnan(evtweight*pswt)) {
          direPtr[j]->direInfo.printMessages(1); abort();
} 

      // Do not print zero-weight events.
      if ( evtweight == 0. ) continue;

//#pragma omp critical
//{
//      evtwmax = max(evtwmax,evtweight);
//      wmin = min(wmin,pswt);
//      wmax = max(wmax,pswt);
//      wminv[j] = min(wminv[j],pswt);
//      wmaxv[j] = max(wmaxv[j],pswt);
//}

      // Now retrieve additional shower weights, and combine these
      // into muR-up and muR-down variations.
      vector<string> pswts_names;
      vector<double> pswts;
      //if (pythia.settings.flag("Variations:doVariations")) { 
      //  for (int iwt=0; iwt < dire.weightsPtr->sizeWeights(); ++iwt) {
      //    string key = dire.weightsPtr->weightName(iwt);
      //    pswts.push_back(dire.weightsPtr->getShowerWeight(key));
      //  }
      //}

      if (!run_default_pythia) {
      if (pythiaPtr[j]->settings.flag("Variations:doVariations")) { 
        pswts.push_back(direPtr[j]->weightsPtr->getShowerWeight("base"));
        pswts_names.push_back("Weight");
        bool hasupvar(false), hasdownvar(false);
        double uvar(1.), dvar(1.);
        // Get ISR variations.
        if ( pythiaPtr[j]->settings.flag("PartonLevel:ISR")) {
          if ( pythiaPtr[j]->settings.parm("Variations:muRisrUp") != 1.) {
            hasupvar=true;
            uvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRisrUp");
          }
          if ( pythiaPtr[j]->settings.parm("Variations:muRisrDown") != 1.) {
            hasdownvar=true;
            dvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRisrDown");
          }
        }
        // Get FSR variations.
        if ( pythiaPtr[j]->settings.flag("PartonLevel:FSR")) {
          if ( pythiaPtr[j]->settings.parm("Variations:muRfsrUp") != 1.) {
            hasupvar=true;
            uvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRfsrUp");
          }
          if ( pythiaPtr[j]->settings.parm("Variations:muRfsrDown") != 1.) {
            hasdownvar=true;
            dvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRfsrDown");
          }
        }

        if (hasupvar && abs(uvar) < LARGE_WT)   pswts.push_back(uvar);
        else            pswts.push_back(0.0);
        //if (abs(pswts.back()) > 1e1) {
        //  cout << "Large up variation  " << pswts.back() << endl; 
        //  //direPtr[j]->direInfo.printMessages(1);
        //}
        if (hasdownvar && abs(dvar) < LARGE_WT) pswts.push_back(dvar);
        else            pswts.push_back(0.0);
        //if (abs(pswts.back()) > 1e1) {
        //  cout << "Large down variation  " << pswts.back() << endl; 
        //  //direPtr[j]->direInfo.printMessages(1);
        //}

        ostringstream name;
        name << "PSMUR" << pythiaPtr[j]->settings.parm("Variations:muRfsrUp");
        pswts_names.push_back(name.str());
        name.str("");
        name << "PSMUR" << pythiaPtr[j]->settings.parm("Variations:muRfsrDown");
        pswts_names.push_back(name.str());

        } else {
        pswts.push_back(pswt);
        pswts_names.push_back("Weight");
        }
      } else {
        pswts.push_back(pswt);
        pswts_names.push_back("Weight");
      }

#pragma omp critical
{

      sumwt[j]   += pswt;
      sumwtsq[j] += pow2(pswt);

      double normhepmc = xss[j]/na[j];

//      if (ntries[j]!=0) normhepmc *= double(nEventEach)/double(ntries[j]);

      // Weighted events with additional number of trial events to consider.
      if ( pythiaPtr[j]->info.lhaStrategy() != 0
        && pythiaPtr[j]->info.lhaStrategy() != 3
        && nash[j] > 0)
        normhepmc = 1. / (1e9*nash[j]);
      // Weighted events.
      else if ( pythiaPtr[j]->info.lhaStrategy() != 0
        && pythiaPtr[j]->info.lhaStrategy() != 3
        && nash[j] == 0)
        normhepmc = 1. / (1e9*na[j]);

      if (pythiaPtr[j]->settings.flag("PhaseSpace:bias2Selection"))
        normhepmc = xss[j] / (sumsh[j]);

      if (pythiaPtr[j]->event.size() > 3) {
        double w = evtweight*pswt*normhepmc;
        // Add the weight of the current event to the cross section.
        double divide = (splitSingleRun ? double(nThreadsReq) : 1.0);
        sigmaTotAll += w/divide;

        sigmaInc[j] += evtweight*normhepmc;
        sigmaTot[j] += w;
#ifdef HEPMC2
        if (printHepMC) {
          // Construct new empty HepMC event.
          HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
          // Set event weight
          hepmcevt->weights().push_back(w);
          //hepmcevt->weights()["Weight"] = w;
          for (int iwt=0; iwt < int(pswts.size()); ++iwt)
            hepmcevt->weights()[pswts_names[iwt]]
              = pswts[iwt]*evtweight*normhepmc;
          // Other weights could be attached like this:
          //hepmcevt->weights()["NOT_VALIDATED_MUR1"]
          //  = 1e9*evtweight*normhepmc;
          // Fill HepMC event
          ToHepMC.fill_next_event( *pythiaPtr[j], hepmcevt);
          // Report cross section to hepmc
          HepMC::GenCrossSection xsec;
          xsec.set_cross_section( sigmaTotAll*1e9,
            pythiaPtr[j]->info.sigmaErr()*1e9 );
          hepmcevt->set_cross_section( xsec );
          // Write the HepMC event to file. Done with it.
          ascii_io << hepmcevt;
          delete hepmcevt;
        }
#endif

        // Write additional HepMC events.
        for (int iwt=0; iwt < int(pswts.size()); ++iwt) {
          double wVar = evtweight*pswts[iwt]*normhepmc;
          // Add the weight of the current event to the cross section.
          double divideVar = (splitSingleRun ? double(nThreadsReq) : 1.0);
          sigmaTotVarAll[iwt] += wVar/divideVar;
          sigmaTotVar[j][iwt] += wVar;
#ifdef HEPMC2
          /*if (printHepMC) {
            HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
            // Set event weight
            //hepmcevt->weights().push_back(wVar);
            hepmcevt->weights()[pswts_names[iwt]] = wVar;
            // Fill HepMC event
            ToHepMC.fill_next_event( *pythiaPtr[j], hepmcevt);
            // Report cross section to hepmc
            HepMC::GenCrossSection xsec;
            xsec.set_cross_section( sigmaTotVarAll[iwt]*1e9,
              pythiaPtr[j]->info.sigmaErr()*1e9 );
            hepmcevt->set_cross_section( xsec );
            // Write the HepMC event to file. Done with it.
            *ascii_io_var[iwt] << hepmcevt;
            delete hepmcevt;
          }*/
#endif
        }

        // Store and write event info.
        if (printLHEF && lhef3) {
          //lhef3->setPointers(&pythiaPtr[j]->event,
          lhef3->setPointers(&pythiaPtr[j]->process,
            &pythiaPtr[j]->settings, &pythiaPtr[j]->info,
            &pythiaPtr[j]->particleData);
          lhef3->setEvent();
        } else if (lhef3) {
          double nsamples
            = atof(pythiaPtr[j]->info.getEventAttribute("nsamples").c_str());
//          nsamples *= pythiaPtr[j]->settings.mode("Main:numberOfSubruns");
          string typeOld
            = pythiaPtr[j]->info.getEventAttribute("eventType");
//nsamples=1;
//nsamples=1;
          double neve
            = double(pythiaPtr[j]->settings.mode("Main:numberOfEvents"));
//          pythiaPtr[j]->info.setEventAttribute("nsamples", std::to_string(1.));
          for (auto s : direPtr[j]->mergingPtr->tomteInfo.states) {
            if (s.name == "input") continue;
            double neveNow = neve/nsamples;
            ostringstream vstream; vstream.str(""); vstream<<double(neveNow);
            pythiaPtr[j]->info.setEventAttribute("neve",
              vstream.str());
            pythiaPtr[j]->info.setEventAttribute("eventType",
              s.name);
            pythiaPtr[j]->info.setEventAttribute("matched_weight",
              std::to_string(s.wt));
            //pythiaPtr[j]->info.updateWeight(s.wt);
            pythiaPtr[j]->info.updateWeight(1.0);
            lhef3->setPointers(&s.state,
              &pythiaPtr[j]->settings, &pythiaPtr[j]->info,
              &pythiaPtr[j]->particleData);
            lhef3->setEvent();
            pythiaPtr[j]->info.setEventAttribute("eventType",typeOld);
          }
//          pythiaPtr[j]->info.setEventAttribute("nsamples", std::to_string(nsamples));
          pythiaPtr[j]->info.setEventAttribute("matched_weight",
            std::to_string(1.));
        }
      }
}

    }
  }
}
#pragma omp barrier
#else
  for (int i = 0; i < nEventEach; ++i) {

    for (int j = 0; j < int(pythiaPtr.size()); ++j) {

      if ( !pythiaPtr[j]->next() ) {
        if ( pythiaPtr[j]->info.atEndOfFile() ) break;
        else continue;
      }

      // Get event weight(s).
      double evtweight = pythiaPtr[j]->info.weight();

      // Do not print zero-weight events.
      if ( evtweight == 0. ) continue;

      // Retrieve the shower weight.
      if (!run_default_pythia) direPtr[j]->weightsPtr->calcWeight(0.);
      if (!run_default_pythia) direPtr[j]->weightsPtr->reset();
      double pswt = (!run_default_pythia)
                  ? direPtr[j]->weightsPtr->getShowerWeight()
                  : 1.;

      evtwmax = max(evtwmax,evtweight);
      wmin = min(wmin,pswt);
      wmax = max(wmax,pswt);

      /*shower_weight_histogram.fill( pswt, 1.0);
      if (pswt>0.) shower_pos_weight_histogram.fill( pswt, 1.0);
      if (pswt<0.) shower_neg_weight_histogram.fill(-pswt, 1.0);
      if (pswt>0.) log10_shower_pos_weight_histogram.fill(log10(pswt), 1.0);
      if (pswt<0.) log10_shower_neg_weight_histogram.fill(log10(-pswt), 1.0);
      if (i>0 && i%100==0) {
        ofstream wr;
        wr.open("shower_weights.dat");
        shower_weight_histogram /= double(i)*bw0;
        shower_weight_histogram.table(wr);
        shower_weight_histogram *= double(i)*bw0;
        wr.close();
        wr.open("shower_pos_weights.dat");
        shower_pos_weight_histogram /= double(i)*bw_pos;
        shower_pos_weight_histogram.table(wr);
        shower_pos_weight_histogram *= double(i)*bw_pos;
        wr.close();
        wr.open("shower_neg_weights.dat");
        shower_neg_weight_histogram /= double(i)*bw_neg;
        shower_neg_weight_histogram.table(wr);
        shower_neg_weight_histogram *= double(i)*bw_neg;
        wr.close();
        wr.open("log10_shower_pos_weights.dat");
        log10_shower_pos_weight_histogram /= double(i)*bw_pos_l10;
        log10_shower_pos_weight_histogram.table(wr);
        log10_shower_pos_weight_histogram *= double(i)*bw_pos_l10;
        wr.close();
        wr.open("log10_shower_neg_weights.dat");
        log10_shower_neg_weight_histogram /= double(i)*bw_neg_l10;
        log10_shower_neg_weight_histogram.table(wr);
        log10_shower_neg_weight_histogram *= double(i)*bw_neg_l10;
        wr.close();
      }*/

      //if (abs(evtweight/avgweight*pswt) > LARGE_WT || abs(pswt) > LARGE_WT) {
      if (abs(pswt) > LARGE_WT) {
        cout << scientific << setprecision(8)
          << "Warning in DIRE main program dire.cc: Large shower weight wt="
          << pswt << endl;
        if (abs(pswt) > 1e4) { 
          cout << "Warning in DIRE main program dire.cc: Shower weight larger"
            << " than 10000. Discard event with rare shower weight fluctuation."
            << endl;
          evtweight = 0.;
          // Print diagnostic output.
          //if (!run_default_pythia) direPtr[j]->direInfo.printMessages(1);
        }
        evtweight = 0.;
//        if (!run_default_pythia) direPtr[j]->direInfo.printMessages(1);
      }

if (std::isnan(evtweight*pswt)) {
          direPtr[j]->direInfo.printMessages(1); abort();
} 

      // Do not print zero-weight events.
      if ( evtweight == 0. ) continue;

      // Now retrieve additional shower weights, and combine these
      // into muR-up and muR-down variations.
      vector<string> pswts_names;
      vector<double> pswts;
      //if (pythia.settings.flag("Variations:doVariations")) { 
      //  for (int iwt=0; iwt < dire.weightsPtr->sizeWeights(); ++iwt) {
      //    string key = dire.weightsPtr->weightName(iwt);
      //    pswts.push_back(dire.weightsPtr->getShowerWeight(key));
      //  }
      //}

      if (!run_default_pythia) {
        if (pythiaPtr[j]->settings.flag("Variations:doVariations")) { 
          pswts.push_back(direPtr[j]->weightsPtr->getShowerWeight("base"));
          pswts_names.push_back("Weight");
          bool hasupvar(false), hasdownvar(false);
          double uvar(1.), dvar(1.);
          // Get ISR variations.
          if ( pythiaPtr[j]->settings.flag("PartonLevel:ISR")) {
            if ( pythiaPtr[j]->settings.parm("Variations:muRisrUp") != 1.) {
              hasupvar=true;
              uvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRisrUp");
            }
            if ( pythiaPtr[j]->settings.parm("Variations:muRisrDown") != 1.) {
              hasdownvar=true;
              dvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRisrDown");
            }
          }
          // Get FSR variations.
          if ( pythiaPtr[j]->settings.flag("PartonLevel:FSR")) {
            if ( pythiaPtr[j]->settings.parm("Variations:muRfsrUp") != 1.) {
              hasupvar=true;
              uvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRfsrUp");
            }
            if ( pythiaPtr[j]->settings.parm("Variations:muRfsrDown") != 1.) {
              hasdownvar=true;
              dvar *= direPtr[j]->weightsPtr->getShowerWeight("Variations:muRfsrDown");
            }
          }
          if (hasupvar && abs(uvar) < LARGE_WT)   pswts.push_back(uvar);
          else            pswts.push_back(0.0);
          if (hasdownvar && abs(dvar) < LARGE_WT) pswts.push_back(dvar);
          else            pswts.push_back(0.0);

          ostringstream name;
          name << "PSMUR" << pythiaPtr[j]->settings.parm("Variations:muRfsrUp");
          pswts_names.push_back(name.str());
          name.str("");
          name << "PSMUR" << pythiaPtr[j]->settings.parm("Variations:muRfsrDown");
          pswts_names.push_back(name.str());

        } else {
          pswts.push_back(pswt);
          pswts_names.push_back("Weight");
        }

      } else {
        pswts.push_back(pswt);
        pswts_names.push_back("Weight");
      }

      sumwt[j]   += pswt;
      sumwtsq[j] += pow2(pswt);

      double normhepmc = xss[j]/na[j];

      // Weighted events with additional number of trial events to consider.
      if ( pythiaPtr[j]->info.lhaStrategy() != 0
        && pythiaPtr[j]->info.lhaStrategy() != 3
        && nash[j] > 0)
        normhepmc = 1. / (1e9*nash[j]);
      // Weighted events.
      else if ( pythiaPtr[j]->info.lhaStrategy() != 0
        && pythiaPtr[j]->info.lhaStrategy() != 3
        && nash[j] == 0)
        normhepmc = 1. / (1e9*na[j]);

      if (pythiaPtr[j]->settings.flag("PhaseSpace:bias2Selection"))
        normhepmc = 1. / (1e9*na[j]);

      if (pythiaPtr[j]->event.size() > 3) {
        double w = evtweight*pswt*normhepmc;
        // Add the weight of the current event to the cross section.
        sigmaTotAll += w;
        sigmaInc[j] += evtweight*normhepmc;
        sigmaTot[j] += w;
#ifdef HEPMC2
        if (printHepMC) {
          // Construct new empty HepMC event.
          HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
          // Set event weight
          hepmcevt->weights().push_back(w);
          //hepmcevt->weights()["Weight"] = w;
          for (int iwt=0; iwt < int(pswts.size()); ++iwt)
            hepmcevt->weights()[pswts_names[iwt]]
              = pswts[iwt]*evtweight*normhepmc;
          // Other weights could be attached like this:
          //hepmcevt->weights()["NOT_VALIDATED_MUR1"]
          //  = 1e9*evtweight*normhepmc;
          // Fill HepMC event
          ToHepMC.fill_next_event( *pythiaPtr[j], hepmcevt);
          // Report cross section to hepmc
          HepMC::GenCrossSection xsec;
          xsec.set_cross_section( sigmaTotAll*1e9,
            pythiaPtr[j]->info.sigmaErr()*1e9 );
          hepmcevt->set_cross_section( xsec );
          // Write the HepMC event to file. Done with it.
          ascii_io << hepmcevt;
          delete hepmcevt;
        }
#endif

        // Write additional HepMC events.
        for (int iwt=0; iwt < int(pswts.size()); ++iwt) {
          double wVar = evtweight*pswts[iwt]*normhepmc;
          // Add the weight of the current event to the cross section.
          sigmaTotVarAll[iwt] += wVar;
          sigmaTotVar[j][iwt] += wVar;
#ifdef HEPMC2
          /*if (printHepMC) {
            HepMC::GenEvent* hepmcevt = new HepMC::GenEvent();
            // Set event weight
            //hepmcevt->weights().push_back(wVar);
            hepmcevt->weights()[pswts_names[iwt]] = wVar;
            // Fill HepMC event
            ToHepMC.fill_next_event( *pythiaPtr[j], hepmcevt);
            // Report cross section to hepmc
            HepMC::GenCrossSection xsec;
            xsec.set_cross_section( sigmaTotVarAll[iwt]*1e9,
              pythiaPtr[j]->info.sigmaErr()*1e9 );
            hepmcevt->set_cross_section( xsec );
            // Write the HepMC event to file. Done with it.
            *ascii_io_var[iwt] << hepmcevt;
            delete hepmcevt;
          }*/
#endif
        }

        // Store and write event info.
        if (printLHEF && lhef3) {
          //lhef3->setPointers(&pythiaPtr[j]->event,
          lhef3->setPointers(&pythiaPtr[j]->process,
            &pythiaPtr[j]->settings, &pythiaPtr[j]->info,
            &pythiaPtr[j]->particleData);
          lhef3->setEvent();
        } else if (lhef3) {
          double nsamples
            = atof(pythiaPtr[j]->info.getEventAttribute("nsamples").c_str());
          //nsamples *= pythiaPtr[j]->settings.mode("Main:numberOfSubruns");
          string typeOld
            = pythiaPtr[j]->info.getEventAttribute("eventType");
//nsamples=1;
          double neve
            = double(pythiaPtr[j]->settings.mode("Main:numberOfEvents"));
//          pythiaPtr[j]->info.setEventAttribute("nsamples", std::to_string(1));
          for (auto s : direPtr[j]->mergingPtr->tomteInfo.states) {
            if (s.name == "input") continue;
            double neveNow = neve/nsamples;
            ostringstream vstream; vstream.str(""); vstream<<double(neveNow);
            pythiaPtr[j]->info.setEventAttribute("neve",
              vstream.str());
            pythiaPtr[j]->info.setEventAttribute("eventType",
              s.name);
            pythiaPtr[j]->info.setEventAttribute("matched_weight",
              std::to_string(s.wt));
            //pythiaPtr[j]->info.updateWeight(s.wt);
            pythiaPtr[j]->info.updateWeight(1.0);
            lhef3->setPointers(&s.state,
              &pythiaPtr[j]->settings, &pythiaPtr[j]->info,
              &pythiaPtr[j]->particleData);
            lhef3->setEvent();
            pythiaPtr[j]->info.setEventAttribute("eventType",typeOld);
          }
//          pythiaPtr[j]->info.setEventAttribute("nsamples", std::to_string(nsamples));
          pythiaPtr[j]->info.setEventAttribute("matched_weight",
            std::to_string(1.));
        }
      }
    }
  }
#endif

  // print cross section, errors
  double sumTot(0.), sum2Tot(0.), nacTot(0.);
  cout << "\nSummary of individual runs:\n";
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    cout << "\nSummary of runs #" << i << " :\n";
    pythiaPtr[i]->stat();
    int nAc = pythiaPtr[i]->info.nAccepted();
    cout << scientific << setprecision(6)
      << "\t Minimal shower weight      = " << wminv[i] << "\n"
      << "\t Maximal shower weight      = " << wmaxv[i] << "\n";
    cout << scientific << setprecision(6)
      << "\n\t Mean shower weight         = " << sumwt[i]/double(nAc) << "\n"
      << "\t Deviation from unity in %  = " << std::lround(abs(sumwt[i]/double(nAc)-1.0)*100.0) << " % " << "\n"
      << "\t Variance of shower weight  = "
      << sqrt(1/double(nAc)*(sumwtsq[i] - pow(sumwt[i],2)/double(nAc)))
      << endl;
    cout << "\t Inclusive cross section    : " << sigmaInc[i] << "\n";
    cout << "\t Cross section after shower : " << sigmaTot[i] << "\n";
    sumTot += sumwt[i];
    sum2Tot += sumwtsq[i];
    nacTot += nAc;
  }
  cout << "\nCombination of runs:\n"
    << scientific << setprecision(6)
    << "\t Minimal shower weight      = " << wmin << "\n"
    << "\t Maximal shower weight      = " << wmax << "\n"
    << "\t Mean shower weight         = " << sumTot/nacTot << "\n"
    << "\t Variance of shower weight  = "
    << sqrt(1/nacTot*(sum2Tot - pow(sumTot,2)/nacTot ))
    << " " << 1/nacTot*(sum2Tot - pow(sumTot,2)/nacTot )
    << "\n"
    << "\t Maximal event weight       = " << evtwmax << "\n"
    << "\t Cross section after shower : " << sigmaTotAll << "\n";
  
#ifdef HEPMC2
  // Clean-up.
  if ( pythiaPtr.front()->settings.flag("Variations:doVariations") ) { 
    //for (int iwt=0; iwt < dire.weightsPtr->sizeWeights(); ++iwt) {
    if (printHepMC) for (int iwt=0; iwt < 3; ++iwt) delete ascii_io_var[iwt];
 }
#endif

   
  // Write endtag. Overwrite initialization info with new cross sections.
  if (lhef3) lhef3->closeLHEF(true);

  //// Print debugging histograms, if any.
  //for (int i = 0; i < int(pythiaPtr.size()); ++i) 
  //  direPtr[i]->direInfo.printHistograms();

  /*ofstream write;
  write.open("shower_weights.dat");
  shower_weight_histogram /= double(nacTot)*bw0;
  shower_weight_histogram.table(write);
  write.close();
  write.open("shower_pos_weights.dat");
  shower_pos_weight_histogram /= double(nacTot)*bw_pos;
  shower_pos_weight_histogram.table(write);
  write.close();
  write.open("shower_neg_weights.dat");
  shower_neg_weight_histogram /= double(nacTot)*bw_neg;
  shower_neg_weight_histogram.table(write);
  write.close();
  write.open("log10_shower_pos_weights.dat");
  log10_shower_pos_weight_histogram /= double(nacTot)*bw_pos_l10;
  log10_shower_pos_weight_histogram.table(write);
  write.close();
  write.open("log10_shower_neg_weights.dat");
  log10_shower_neg_weight_histogram /= double(nacTot)*bw_neg_l10;
  log10_shower_neg_weight_histogram.table(write);
  write.close();*/

  // Clean-up.
  for (int i = 0; i < int(pythiaPtr.size()); ++i) {
    if ( pythiaPtr[i]->settings.flag("Dire:doMerging")
      || pythiaPtr[i]->settings.flag("Dire:doMECs")
      || pythiaPtr[i]->settings.flag("Dire:doMEM")) {
      delete mergingPtr[i];      mergingPtr[i]=0;
      delete hardProcessPtr[i];  hardProcessPtr[i]=0;
      delete mergingHooksPtr[i]; mergingHooksPtr[i]=0;
    }
    delete direPtr[i];   direPtr[i]=0;
    delete pythiaPtr[i]; pythiaPtr[i]=0;
  }

  delete apfelHooks;
  // Done.
  return 0;

}
