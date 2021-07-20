
// DIRE includes.
#include "Dire/Dire.h"

namespace Pythia8 {


void Dire::initSettings( Pythia& pythia ) {

  // This should be changed in the future: Currently, Pythia
  // has a hard cut-off on the QED shower evolution variable.
  //pythia.settings.forceParm("TimeShower:pTminChgQ",1e-3);
  //pythia.settings.forceParm("SpaceShower:pTminChgQ",1e-3);
  //pythia.settings.forceParm("TimeShower:pTminChgL",1e-3);
  //pythia.settings.forceParm("SpaceShower:pTminChgL",1e-3);

  // Change some of the Pythia defaults.
  // No smooth pT cut-off
  pythia.settings.forceParm("SpaceShower:pT0Ref",0.0);
  pythia.settings.forceParm("PhaseSpace:pTHatMinDiverge",1e-3);
  // No QED radiation by default (until implemented & validated) 
  pythia.settings.flag("TimeShower:QEDshowerByQ",false);
  pythia.settings.flag("TimeShower:QEDshowerByL",false);
  pythia.settings.flag("SpaceShower:QEDshowerByQ",false);
  pythia.settings.flag("SpaceShower:QEDshowerByL",false);
  pythia.settings.addFlag("Dire:QED:doForcePosChgCorrelators",false);
  pythia.settings.addParm("Dire:QED:pTminForcePos",-1.0,false,false,-1.0,1e10);
  pythia.settings.addParm("Dire:QED:pTminAllowNeg",-1.0,false,false,-1.0,1e10);
  pythia.settings.addParm("Dire:U1new:pTminForcePos",-1.0,false,false,-1.0,1e10);
  pythia.settings.addParm("Dire:U1new:pTminAllowNeg",-1.0,false,false,-1.0,1e10);

  pythia.settings.addParm("DireTimes:QED:pTminChgQ",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireTimes:QED:pTminChgL",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireSpace:QED:pTminChgQ",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireSpace:QED:pTminChgL",0.001,false,false,-1.0,1e10);

  pythia.settings.addParm("DireTimes:U1new:pTminChgQ",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireTimes:U1new:pTminChgL",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireSpace:U1new:pTminChgQ",0.001,false,false,-1.0,1e10);
  pythia.settings.addParm("DireSpace:U1new:pTminChgL",0.001,false,false,-1.0,1e10);

  // Teach Pythia the additional DIRE input settings.
  pythia.settings.addFlag("ShowerPDF:usePDFalphas",false);
  pythia.settings.addFlag("ShowerPDF:usePDFmasses",true);
  pythia.settings.addFlag("ShowerPDF:useSummedPDF",true);
  pythia.settings.addFlag("ShowerPDF:usePDF",true);
  pythia.settings.addFlag("DireSpace:useGlobalMapIF",false);
  pythia.settings.addFlag("DireSpace:forceMassiveMap",true);
  pythia.settings.addMode("DireTimes:nFinalMax",-10,true,false,-1,10000000);
  pythia.settings.addMode("DireSpace:nFinalMax",-10,true,false,-1,10000000);
  pythia.settings.addMode("DireTimes:kernelOrder",1,true,false,-1,10);
  pythia.settings.addMode("DireSpace:kernelOrder",1,true,false,-1,10);
  pythia.settings.addMode("DireTimes:kernelOrderMPI",1,true,false,-1,10);
  pythia.settings.addMode("DireSpace:kernelOrderMPI",1,true,false,-1,10);
  pythia.settings.addParm("DireTimes:pTrecombine",1.414,false,false,0.0,1e10);
  pythia.settings.addMode("DireTimes:alphasScheme",0,true,false,0,10);
  pythia.settings.addMode("DireSpace:alphasScheme",0,true,false,0,10);

  // Teach Pythia some enhance factors.
  // QCD FSR
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&21",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->21&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&21a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&21b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->1&1a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->1&1b",1.0,false,false,-1e5,1e5);


  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->-1soft&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->1soft&-1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->-1hard&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->1hard&-1",1.0,false,false,-1e5,1e5);



  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->2&1&2",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&1&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&21_notPartial",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&21_notPartial",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->1&1_notPartial",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&21&21",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&d&dbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&dbar&d",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&u&ubar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&ubar&u",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&s&sbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&sbar&s",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&c&cbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&cbar&c",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&b&bbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_1->1&bbar&b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&21&21",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&d&dbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&dbar&d",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&u&ubar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&ubar&u",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&s&sbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&sbar&s",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&c&cbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&cbar&c",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&b&bbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qcd_21->21&bbar&b",1.0,false,false,-1e5,1e5);
  // QCD ISR
  pythia.settings.addParm("Enhance:Dire_isr_qcd_1->1&21",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_21->1&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_21->21&21a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_21->21&21b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_1->21&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_1->2&1&2",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qcd_1->1&1&1",1.0,false,false,-1e5,1e5);
  // QED FSR
  pythia.settings.addParm("Enhance:Dire_fsr_qed_1->1&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_1->22&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_11->11&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_11->22&11",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->1&1a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->1&1b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->2&2a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->2&2b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->3&3a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->3&3b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->4&4a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->4&4b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->5&5a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->5&5b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->11&11a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->11&11b",1.0,false,false,-1e5,1e5);
  //pythia.settings.addParm("Enhance:Dire_fsr_qed_22->13&13a",1.0,false,false,-1e5,1e5);
  //pythia.settings.addParm("Enhance:Dire_fsr_qed_22->13&13b",1.0,false,false,-1e5,1e5);

  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->-13soft&13",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->13soft&-13",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->-13hard&13",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->13hard&-13",1.0,false,false,-1e5,1e5);



  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->15&15a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_22->15&15b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_1->1&22_notPartial",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_11->11&22_notPartial",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_11->11&e&ebar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_qed_11->11&ebar&e",1.0,false,false,-1e5,1e5);
  // QED ISR
  pythia.settings.addParm("Enhance:Dire_isr_qed_1->1&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_1->22&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_22->1&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_11->11&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_11->22&11",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_22->11&11",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_11->11&e&ebar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_qed_11->11&ebar&e",1.0,false,false,-1e5,1e5);
  // EW FSR
  pythia.settings.addParm("Enhance:Dire_fsr_ew_1->1&23",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_1->23&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_23->1&1a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_23->1&1b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_24->1&1a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_24->1&1b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_24->24&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_25->21&21",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_25->22&22",1.0,false,false,-1e5,1e5);

  // New U(1) FSR
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_1->1&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_1->22&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_11->11&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_11->22&11",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->1&1a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->1&1b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->2&2a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->2&2b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->3&3a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->3&3b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->4&4a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->4&4b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->5&5a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->5&5b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->11&11a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->11&11b",1.0,false,false,-1e5,1e5);
//  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->13&13a",1.0,false,false,-1e5,1e5);
//  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->13&13b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->15&15a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->15&15b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->211&211a",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_u1new_22->211&211b",1.0,false,false,-1e5,1e5);
/*  // 2020/07/13
  for (int i=11; i <= 15; i += 2) {
    stringstream nameNow;
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "&" << i;
    string name = nameNow.str() + "aResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "bResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "aResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "bResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
  }
*/

  for (int i=13; i <= 13; i += 2) {
    stringstream nameNow;
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "hard&" << -i;
    string name = nameNow.str();
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    nameNow.str("");
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "soft&" << -i;
    name = nameNow.str();
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
  }

  for (int i=-13; i >= -13; i -= 2) {
    stringstream nameNow;
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "hard&" << -i;
    string name = nameNow.str();
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    nameNow.str("");
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "soft&" << -i;
    name = nameNow.str();
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "ResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
  }

  for (int i=1; i < 6; ++i) {
    stringstream nameNow;
    nameNow << "Enhance:Dire_fsr_u1new_22->" << i << "&" << i;
    string name = nameNow.str() + "aResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "bResA";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "aResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
    name = nameNow.str() + "bResB";
    pythia.settings.addParm(name,1.0,false,false,-1e5,1e5);
  }

  // New U(1) ISR
  pythia.settings.addParm("Enhance:Dire_isr_u1new_1->1&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_u1new_1->22&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_u1new_22->1&1",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_u1new_11->11&22",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_u1new_11->22&11",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_u1new_22->11&11",1.0,false,false,-1e5,1e5);

  pythia.settings.addParm("Enhance:Dire_fsr_ew_d->d&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_d->z&d",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_d->d&z",1.0,false,false,-1e5,1e5);

  pythia.settings.addParm("Enhance:Dire_fsr_ew_dbar->dbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_dbar->z&dbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_u->u&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_u->z&u",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_ubar->ubar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_ubar->z&ubar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_s->s&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_s->z&s",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_sbar->sbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_sbar->z&sbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_c->c&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_c->z&c",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_cbar->cbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_cbar->z&cbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_b->b&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_b->z&b",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_bbar->bbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_bbar->z&bbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_t->t&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_t->z&t",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_tbar->tbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_tbar->z&tbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_dbar->dbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_u->u&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_ubar->ubar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_s->s&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_sbar->sbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_c->c&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_cbar->cbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_b->b&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_bbar->bbar&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_t->t&z",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_tbar->tbar&z",1.0,false,false,-1e5,1e5);

  pythia.settings.addParm("Enhance:Dire_fsr_ew_s->c&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_s->w-&c",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_b->t&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_b->w-&t",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_ubar->dbar&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_ubar->w-&dbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_cbar->sbar&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_cbar->w-&sbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_tbar->bbar&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_tbar->w-&bbar",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_s->c&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_b->t&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_ubar->dbar&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_cbar->sbar&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_tbar->bbar&w-",1.0,false,false,-1e5,1e5);

  pythia.settings.addParm("Enhance:Dire_fsr_ew_d->u&w-",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_fsr_ew_d->w-&u",1.0,false,false,-1e5,1e5);
  pythia.settings.addParm("Enhance:Dire_isr_ew_d->u&w-",1.0,false,false,-1e5,1e5);

  // When to stop enhancements.
  pythia.settings.addParm("Enhance:pTmin",2.0,false,false,1.0,1e10);

  pythia.settings.addMode("Dire:U1new:idZprime",10,true,false,0,1000000000);
  pythia.settings.addParm("Dire:U1new:epsilon",-1.0,true,false,0.0,1e5);
  pythia.settings.addParm("Dire:U1new:alphaX",1.0,false,false,0.0,1e5);
  pythia.settings.addParm("Dire:U1new:nuMixSq",1.0,false,false,0.0,1e5);
  pythia.settings.addParm("Dire:U1new:KinMix",1.0,false,false,0.0,1e5);
  pythia.settings.addParm("Dire:U1new:LambdaElastic",1.0,false,false,0.0,1e5);
  pythia.settings.addParm("Dire:U1new:pElastic",2.0,false,false,0.0,1e5);

  pythia.settings.addFlag("TimeShower:U1newShowerByL",false);
  pythia.settings.addFlag("TimeShower:U1newShowerByQ",false);
  pythia.settings.addFlag("SpaceShower:U1newShowerByL",false);
  pythia.settings.addFlag("SpaceShower:U1newShowerByQ",false);
  pythia.settings.addFlag("WeakBosonExchange:ff2ff(t:Zp)",false);
  pythia.settings.addFlag("WeakBosonExchange:ff2ff(t:Wp)",false);
  pythia.settings.addFlag("WeakBosonExchange_elastic:ff2ff(t:Zp)",false);

  pythia.settings.addFlag("TimeShower:EWshowerByL",false);
  pythia.settings.addFlag("TimeShower:EWshowerByQ",false);
  pythia.settings.addFlag("SpaceShower:EWshowerByL",false);
  pythia.settings.addFlag("SpaceShower:EWshowerByQ",false);

  pythia.settings.addFlag("Check:beams", false);
  pythia.settings.addFlag("Beams:massiveLeptonBeams", false);

  // Teach Pythia scale variations.
  pythia.settings.addFlag("Variations:doVariations",false);
  pythia.settings.addParm("Variations:muRisrDown",1.0,false,false,1e-2,1.0);
  pythia.settings.addParm("Variations:muRisrUp",1.0,false,false,1.0,1e2);
  pythia.settings.addParm("Variations:muRfsrDown",1.0,false,false,1e-2,1.0);
  pythia.settings.addParm("Variations:muRfsrUp",1.0,false,false,1.0,1e2);
  pythia.settings.addMode("Variations:PDFmemberMin",-1,true,false,-1,100000000);
  pythia.settings.addMode("Variations:PDFmemberMax",-1,true,false,-1,100000000);
  pythia.settings.addFlag("Variations:PDFup",false);
  pythia.settings.addFlag("Variations:PDFdown",false);
  pythia.settings.addParm("Variations:pTmin",-1.0,false,false,-1.0,1e10);
  pythia.settings.addMode("Variations:nSystemsToVary",0,true,false,-1,100000000);

  // Teach Pythia merging.
  pythia.settings.addFlag("Dire:doMerging",false);
  pythia.settings.addFlag("Dire:doGenerateSubtractions",false);
  pythia.settings.addFlag("Dire:doGenerateMergingWeights",false);
  pythia.settings.addFlag("Dire:doMECs",false);
  pythia.settings.addFlag("Dire:doMOPS",false);
  //pythia.settings.addFlag("Dire:doMcAtNloDelta",false);
  pythia.settings.addFlag("Dire:doExitAfterMerging",false);
  pythia.settings.addParm("Dire:pTminMECs",-1.0,false,false,0.0,1e10);
  pythia.settings.addParm("Dire:QminMECs",1.0,false,false,0.0,1e10);
  pythia.settings.addMode("Dire:nFinalMaxMECs",-1,true,false,-1,100000000);
  pythia.settings.addFlag("Dire:suppressLargeMECs",false);
  pythia.settings.addFlag("Dire:allowMECsBelowCutoff",false);
  pythia.settings.addFlag("Dire:doMEM",false);
  pythia.settings.addParm("MEM:WidthH",-1.0,false,false,0.0,1e10);
  pythia.settings.addFlag("Dire:doSingleLegSudakovs",false);

  pythia.settings.addFlag("Merging:makeToyCalculation",false);
  pythia.settings.addFlag("Merging:checkBiasesBasic",false);
  pythia.settings.addFlag("Merging:checkBiasesSudakov",false);
  pythia.settings.addFlag("Dire:doTOMTE",false);
  pythia.settings.addFlag("Dire:doTOMTE:Sudakovs",true);
  pythia.settings.addFlag("Dire:doTOMTE:AlphasRatios",true);
  pythia.settings.addFlag("Dire:doTOMTE:PDFRatios",false);
  pythia.settings.addMode("Dire:checkBiases:clusterMode",1,true,false,-10,10);
  pythia.settings.addMode("Dire:checkBiases:correctionMode",0,true,false,-10,10);
  pythia.settings.addFlag("Merging:useMEs",true);

  // Teach Pythia MG5 inputs for external MEs
  pythia.settings.addWord("Dire:MG5card", "");

  pythia.settings.addMode("DireTimes:evolutionMode",0,true,false,0,1);
  pythia.settings.addMode("DireSpace:evolutionMode",0,true,false,0,1);

  // Teach Pythia to treat resonance decays within the shower evolution.
  pythia.settings.addFlag("DireTimes:DecaysAsShower",false);
  pythia.settings.addFlag("DireSpace:DecaysAsShower",false);

  // Teach Pythia tune settings.
  pythia.settings.addMode("Dire:Tune",1,true,false,0,10);

  pythia.settings.addParm("DireColorQCD:TR",-1.0,false,false,0.0,1e1);
  pythia.settings.addParm("DireColorQCD:CA",-1.0,false,false,0.0,1e1);
  pythia.settings.addParm("DireColorQCD:NC",-1.0,false,false,0.0,1e1);
  pythia.settings.addParm("DireColorQCD:CF",-1.0,false,false,0.0,1e1);

  pythia.settings.addFlag("DireTimes:useBackboneGluons",false);
  pythia.settings.addFlag("DireTimes:doGeneralizedKernel",false);
  pythia.settings.addPVec("DireGeneralizedKernel:softCoeffs:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:softExps:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaCoeffs:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaExps:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_1->1&21", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_1->1&21",-2.0,false,false,-1e5,1e5);

  pythia.settings.addPVec("DireGeneralizedKernel:softCoeffs:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:softExps:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaCoeffs:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaExps:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_1->21&1", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_1->21&1",-2.0,false,false,-1e5,1e5);

  pythia.settings.addPVec("DireGeneralizedKernel:softCoeffs:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:softExps:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaCoeffs:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaExps:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_21->21&21a", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_21->21&21a",-2.0,false,false,-1e5,1e5);

  pythia.settings.addPVec("DireGeneralizedKernel:softCoeffs:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:softExps:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaCoeffs:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:kappaExps:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_21->21&21b", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_21->21&21b",-2.0,false,false,-1e5,1e5);

  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_21->1&1a", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_21->1&1a", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_21->1&1a",0.0,false,false,-1e5,1e5);

  pythia.settings.addPVec("DireGeneralizedKernel:collCoeffs:Dire_fsr_qcd_21->1&1b", 
    createvector<double>(0.)(1.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addPVec("DireGeneralizedKernel:collExps:Dire_fsr_qcd_21->1&1b", 
    createvector<double>(0.)(0.)(0.)(0.), false, false, -1e5, 1e5);
  pythia.settings.addParm("DireGeneralizedKernel:finCoeffs:Dire_fsr_qcd_21->1&1b",0.0,false,false,-1e5,1e5);

  // Done.
  initNewSettings = true;

}

void Dire::initTune( Pythia& pythia ) {

  // Get tune id.
  int iTune = pythia.settings.mode("Dire:Tune");

  // Default tune.
  if (iTune == 1) {
    // Preliminary Professor tune, dated 2017-10-10. To be used with:
    // PDF:pSet                   = LHAPDF6:MMHT2014nlo68cl
    // PDF:pHardSet               = LHAPDF6:MMHT2014nlo68cl
    // TimeShower:alphaSvalue     = 0.1201
    // SpaceShower:alphaSvalue    = 0.1201
    // ShowerPDF:usePDFalphas     = on
    // ShowerPDF:useSummedPDF     = on
    // DireSpace:forceMassiveMap  = on
    // ShowerPDF:usePDFmasses     = off

    // Tuned hadronization from e+e- data
    pythia.readString("StringPT:sigma = 0.2952");
    pythia.readString("StringZ:aLund = 0.9704");
    pythia.readString("StringZ:bLund = 1.0809");
    pythia.readString("StringZ:aExtraDiquark = 1.3490");
    pythia.readString("StringFlav:probStoUD = 0.2046");
    pythia.readString("StringZ:rFactB = 0.8321");
    pythia.readString("StringZ:aExtraSQuark = 0.0");
    pythia.readString("TimeShower:pTmin = 0.9");

    // Tuned MPI and primordial kT to LHC data (UE in dijets + Drell-Yan pT).
    pythia.readString("SpaceShower:pTmin = 0.9");
    pythia.readString("MultipartonInteractions:alphaSvalue = 0.1309");
    pythia.readString("MultipartonInteractions:pT0Ref = 1.729");
    pythia.readString("MultipartonInteractions:expPow = 1.769");
    pythia.readString("ColourReconnection:range = 2.1720");
    pythia.readString("BeamRemnants:primordialKThard = 2.2873");
    pythia.readString("BeamRemnants:primordialKTsoft =  0.25");
    pythia.readString("BeamRemnants:reducedKTatHighY =  0.47");

  }

  // For new U(1) splittings, teach Pythia new particles, if not already read 
  // from input file.
  if ( pythia.settings.flag("TimeShower:U1newShowerByL")
    || pythia.settings.flag("TimeShower:U1newShowerByQ")
    || pythia.settings.flag("SpaceShower:U1newShowerByL")
    || pythia.settings.flag("SpaceShower:U1newShowerByQ")) {
    if (!pythia.particleData.isParticle(900032)) {
      pythia.readString("900032:all = Zp void 1 0 0 1. 0.01 0. 0. 0.");
      pythia.readString("900032:addChannel = 1 0.33 101 11 -11");
      pythia.readString("900032:addChannel = 1 0.33 101 13 -13");
      pythia.readString("900032:addChannel = 1 0.34 101 211 -211");
      pythia.readString("900032:isResonance = true");
    }
    if (!pythia.particleData.isParticle(900012)) {
      pythia.readString("900012:all = nup nup_bar 1 0 0 0.0 0.0 0. 0. 0.");
    }
    if (!pythia.particleData.isParticle(9000001)) {
      pythia.readString("9000001:all = Zp void 1 0 0 1. 0.01 0. 0. 0.");
      pythia.readString("9000001:addChannel = 1 0.33 101 11 -11");
      pythia.readString("9000001:addChannel = 1 0.33 101 13 -13");
      pythia.readString("9000001:addChannel = 1 0.34 101 211 -211");
      pythia.readString("9000001:isResonance = true");
    }
  }

  return;

}

void Dire::initShowersAndWeights(Pythia& pythia, UserHooks* userHooks,
  DireHooks* hooks) {

  // Construct showers.
  if (!weightsPtr)  { 
    hasOwnWeights  = true;
    weightsPtr     = new DireWeightContainer(&pythia.settings);
  }
  if (!timesPtr) {
    hasOwnTimes    = true;
    timesPtr       = new DireTimes(&pythia);
  }
  if (!spacePtr) {
    hasOwnSpace    = true;
    spacePtr       = new DireSpace(&pythia);
  }
  if (!timesDecPtr) {
    hasOwnTimesDec = true;
    timesDecPtr    = new DireTimes(&pythia);
  }

  if (!mergingHooksPtr) {
    hasOwnMergingHooks = true;
    mergingHooksPtr    = new DireMergingHooks();
  }

  if (!mergingPtr) {
    hasOwnMerging = true;
    mergingPtr    = new DireMerging();
  }

  if (!hardProcessPtr) {
    hasOwnHardProcess = true;
    hardProcessPtr    = new DireHardProcess();
    hardProcessPtr->initPtrs(&pythia.particleData);
  }

  hooksPtr         = hooks;
  userHooksPtr     = userHooks;

  timesPtr->setWeightContainerPtr(weightsPtr);
  spacePtr->setWeightContainerPtr(weightsPtr);
  timesDecPtr->setWeightContainerPtr(weightsPtr);

  mergingHooksPtr->setHardProcessPtr( hardProcessPtr);
  mergingPtr->initPtrs(weightsPtr, timesPtr, spacePtr, 
    &direInfo);
  mergingPtr->setHelpersPtr(&helpers);
  mergingHooksPtr->setHelpersPtr(&helpers);

  // Feed new DIRE showers to Pythia.
  pythia.setShowerPtr( timesDecPtr, timesPtr, spacePtr);

}

void Dire::setup( Pythia& pythia) {

  // Initialise library of splitting functions.
  if (!splittings) {
    hasOwnSplittings = true;
    splittings       = new DireSplittingLibrary();
  }

  helpers.setPointers(&pythia.partonSystems, &pythia.particleData,
    &pythia.settings, &direInfo, hooksPtr);

  // If Pythia has, for ominous reasons, not initialized the spacelike shower,
  // retry to initialize from timelike shower beams.
  if ( !spacePtr->isInit() && timesPtr->isInit()
    && timesPtr->getBeamA() != 0 && timesPtr->getBeamB() != 0)
    spacePtr->init( timesPtr->getBeamA(), timesPtr->getBeamB() );

  // Reinitialise showers to ensure that pointers are
  // correctly set.
  timesPtr->reinitPtr(&pythia.info,
    &pythia.settings,
    &pythia.particleData,
    &pythia.rndm,
    &pythia.partonSystems,
     userHooksPtr, pythia.mergingHooksPtr,
     splittings, &direInfo);
  spacePtr->reinitPtr(&pythia.info,
    &pythia.settings,
    &pythia.particleData,
    &pythia.rndm,
    &pythia.partonSystems,
     userHooksPtr, pythia.mergingHooksPtr,
     splittings, &direInfo);
  timesDecPtr->reinitPtr(&pythia.info,
    &pythia.settings,
    &pythia.particleData,
    &pythia.rndm,
    &pythia.partonSystems,
     userHooksPtr, pythia.mergingHooksPtr,
     splittings, &direInfo);

  timesPtr->setHelpersPtr(&helpers);
  spacePtr->setHelpersPtr(&helpers);
  timesDecPtr->setHelpersPtr(&helpers);

  // Reset Pythia masses if necessary.
  if ( pythia.settings.flag("ShowerPDF:usePDFmasses")
    && ( spacePtr->getBeamA() != NULL || spacePtr->getBeamB() != NULL) ) {
    for (int i=1; i <= 5; ++i) {
      // Try to get masses from the hadron beams.
      double mPDF = (abs(spacePtr->getBeamA()->id()) > 30)
                  ? spacePtr->getBeamA()->mQuarkPDF(i)
                  : (abs(spacePtr->getBeamB()->id()) > 30) 
                    ? spacePtr->getBeamB()->mQuarkPDF(i) : -1.0;
      // If there are no hadron beams, get the masses from either beam.
      if (spacePtr->getBeamA() != NULL && mPDF < 0.)
        mPDF = spacePtr->getBeamA()->mQuarkPDF(i);
      if (spacePtr->getBeamB() != NULL && mPDF < 0.)
        mPDF = spacePtr->getBeamB()->mQuarkPDF(i);
      if (mPDF > -1.) {
        stringstream resetMass;
        resetMass << i << ":m0 = " << mPDF;
        pythia.readString(resetMass.str());
      }
    }
  }

  // Switch off all showering and MPI when estimating the cross section,
  if (hooksPtr)
    hooksPtr->initPtr( &pythia.info, &pythia.settings, &pythia.particleData,
      &pythia.rndm, spacePtr->getBeamA(), spacePtr->getBeamB(),
      &pythia.couplings, &pythia.partonSystems);

  hooksPtr->init();

  splittings->setKernelHooks(hooksPtr);

  // Initialise splitting function library here so that beam pointers
  // are already correctly initialised.
  splittings->init(&pythia.settings, &pythia.particleData, &pythia.rndm,
    spacePtr->getBeamA(), spacePtr->getBeamB(), spacePtr->getCoupSM(),
    &pythia.info, &direInfo, hooksPtr, &pythia.slhaInterface);

  // Feed the splitting functions to the showers.
  splittings->setTimesPtr(timesPtr);
  splittings->setTimesDecPtr(timesDecPtr);
  splittings->setSpacePtr(spacePtr);

  // Initialize splittings in showers again (!), now that splittings are
  // properly set up.
  timesDecPtr->initSplits();
  timesPtr->initSplits();
  spacePtr->initSplits();

  weightsPtr->initPtrs(spacePtr->getBeamA(), spacePtr->getBeamB(), &direInfo);
  weightsPtr->setHelpersPtr(&helpers);
  timesDecPtr->initVariations();
  timesPtr->initVariations();
  spacePtr->initVariations();

}

bool Dire::init(Pythia& pythia, char const* settingsFile, int subrun,
  UserHooks* userHooks, DireHooks* hooks) {

  // Initialize new settings.
  if (!initNewSettings) initSettings(pythia);

  // Construct showers.
  initShowersAndWeights(pythia, userHooks, hooks); 

  // Redirect output so that Pythia banner will not be printed twice.
  std::streambuf *old = cout.rdbuf();
  stringstream ss;
  cout.rdbuf (ss.rdbuf());

  // Read Pythia settings from file (to define tune).
  if (string(settingsFile) != "")
    pythia.readFile(settingsFile, ((subrun>-1) ? subrun : 0) );

  // Reset flags after reading input file, if necessary.
  setFlags(pythia);

  // Initialize Dire tune settings.
  initTune(pythia);

  // Restore print-out.
  cout.rdbuf (old);

  // Read Pythia settings from file and initialise
  // (needed so that we have a well-defined beam particle
  // pointer that can be fed to the splitting functions).
  if (string(settingsFile) != "")
    pythia.readFile(settingsFile, ((subrun>-1) ? subrun : 0) );

  // Replace dijet process with own code (uses changed scale setting).
  if (pythia.settings.flag("HardQCD:all") ) {

    sigmaHelper.init( &pythia.info, &pythia.settings, &pythia.particleData,
      &pythia.rndm, spacePtr->getBeamA(), spacePtr->getBeamB(),
      &pythia.couplings, &pythia.slhaInterface.slha, weightsPtr, hooksPtr);
    pythia.settings.flag("HardQCD:all", false);

    DireSigma2gg2gg * sigNow1 = new DireSigma2gg2gg();
    sigNow1->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow1 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2gg2qqbar * sigNow2 = new DireSigma2gg2qqbar();
    sigNow2->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow2 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qg2qg* sigNow3 = new DireSigma2qg2qg();
    sigNow3->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow3 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qq2qq* sigNow4 = new DireSigma2qq2qq();
    sigNow4->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow4 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qqbar2gg* sigNow5 = new DireSigma2qqbar2gg();
    sigNow5->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow5 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qqbar2qqbarNew* sigNow6 = new DireSigma2qqbar2qqbarNew();
    sigNow6->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow6 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2gg2QQbar* sigNow7 = new DireSigma2gg2QQbar(4, 121);
    sigNow7->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow7 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qqbar2QQbar* sigNow8 = new DireSigma2qqbar2QQbar(4, 122);
    sigNow8->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow8 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2gg2QQbar* sigNow9 = new DireSigma2gg2QQbar(5, 123);
    sigNow9->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow9 );
    pythia.setSigmaPtr(sigmaPtr.back());

    DireSigma2qqbar2QQbar* sigNow10 = new DireSigma2qqbar2QQbar(5, 124);
    sigNow10->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow10 );
    pythia.setSigmaPtr(sigmaPtr.back());
  }

  // New weak Zprime boson exchange process
  if (pythia.settings.flag("WeakBosonExchange:ff2ff(t:Zp)") ) {

    sigmaHelper.init( &pythia.info, &pythia.settings, &pythia.particleData,
      &pythia.rndm, spacePtr->getBeamA(), spacePtr->getBeamB(),
      &pythia.couplings, &pythia.slhaInterface.slha, weightsPtr, hooksPtr);

    pythia.settings.flag("WeakBosonExchange:ff2ff(t:Zp)", false);
    pythia.settings.flag("Check:beams", false);

    DireSigmaSigma2ff2fft_neutral_current * sigNow1
      = new DireSigmaSigma2ff2fft_neutral_current(1);
    sigNow1->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow1 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow2
      = new DireSigmaSigma2ff2fft_neutral_current(-1);
    sigNow2->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow2 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow3
      = new DireSigmaSigma2ff2fft_neutral_current(2);
    sigNow3->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow3 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow4
      = new DireSigmaSigma2ff2fft_neutral_current(-2);
    sigNow4->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow4 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow5
      = new DireSigmaSigma2ff2fft_neutral_current(3);
    sigNow5->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow5 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow6
      = new DireSigmaSigma2ff2fft_neutral_current(-3);
    sigNow6->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow6 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow7
      = new DireSigmaSigma2ff2fft_neutral_current(4);
    sigNow7->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow7 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow8
      = new DireSigmaSigma2ff2fft_neutral_current(-4);
    sigNow8->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow8 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow9
      = new DireSigmaSigma2ff2fft_neutral_current(5);
    sigNow9->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow9 );
    pythia.setSigmaPtr(sigmaPtr.back());
    DireSigmaSigma2ff2fft_neutral_current * sigNow10
      = new DireSigmaSigma2ff2fft_neutral_current(-5);
    sigNow10->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow10 );
    pythia.setSigmaPtr(sigmaPtr.back());
  }

  // New weak Zprime boson exchange process - elastic scattering
  if (pythia.settings.flag("WeakBosonExchange_elastic:ff2ff(t:Zp)") ) {

    sigmaHelper.init( &pythia.info, &pythia.settings, &pythia.particleData,
      &pythia.rndm, spacePtr->getBeamA(), spacePtr->getBeamB(),
      &pythia.couplings, &pythia.slhaInterface.slha, weightsPtr, hooksPtr);

    pythia.settings.flag("WeakBosonExchange_elastic:ff2ff(t:Zp)", false);
    pythia.settings.flag("Check:beams", false);

    DireSigmaSigma2ff2fft_neutral_current_elastic * sigNow1
      = new DireSigmaSigma2ff2fft_neutral_current_elastic();
    sigNow1->setHelper(&sigmaHelper);
    sigmaPtr.push_back( sigNow1 );
    pythia.setSigmaPtr(sigmaPtr.back());
  }


  /*// Replace dijet process with own code (uses changed scale setting).
  if (pythia.settings.flag("WeakBosonExchange:ff2ff(t:W)") ) {

    sigmaHelper.init( &pythia.info, &pythia.settings, &pythia.particleData,
      &pythia.rndm, spacePtr->getBeamA(), spacePtr->getBeamB(),
      &pythia.couplings, &pythia.slhaInterface.slha, weightsPtr, hooksPtr);
    pythia.settings.flag("WeakBosonExchange:ff2ff(t:W)", false);

    int idBeam1 = pythia.settings.mode("Beams:idA");
    int idBeam2 = pythia.settings.mode("Beams:idB");

    if (idBeam1 == 12 && abs(idBeam2) > 100) {

      DireSigmaSigma2ff2fftW * sigNow1
        = new DireSigmaSigma2ff2fftW(11,1);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow1 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow2
        = new DireSigmaSigma2ff2fftW(11,2);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow2 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow3
        = new DireSigmaSigma2ff2fftW(11,3);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow3 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow4
        = new DireSigmaSigma2ff2fftW(11,4);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow4 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow5
        = new DireSigmaSigma2ff2fftW(11,5);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow5 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow6
        = new DireSigmaSigma2ff2fftW(11,-1);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow6 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow7
        = new DireSigmaSigma2ff2fftW(11,-2);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow7 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow8
        = new DireSigmaSigma2ff2fftW(11,-3);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow8 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow9
        = new DireSigmaSigma2ff2fftW(11,-4);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow9 );
      pythia.setSigmaPtr(sigmaPtr.back());

      DireSigmaSigma2ff2fftW * sigNow10
        = new DireSigmaSigma2ff2fftW(11,-5);
      sigNow1->setHelper(&sigmaHelper);
      sigmaPtr.push_back( sigNow10 );
      pythia.setSigmaPtr(sigmaPtr.back());
    }
  }*/

  if ( pythia.settings.flag("Dire:doMerging")
    || pythia.settings.flag("Dire:doMECs")
    || pythia.settings.flag("Dire:doMEM")) {
    pythia.settings.flag("Dire:doMerging",true);
    pythia.settings.flag("Merging:doMerging",true);
    pythia.settings.flag("Merging:useShowerPlugin",true);
  }

  if ( pythia.settings.flag("Dire:doMECs")
    || pythia.settings.flag("Dire:doMEM")) {
    pythia.settings.parm("Merging:TMS",0.0);
  }

  // Feed merging pointers to Pythia.
  if ( pythia.settings.flag("Dire:doMerging")
    || pythia.settings.flag("Dire:doMECs")
    || pythia.settings.flag("Dire:doMEM")
    || pythia.settings.flag("Merging:doUNLOPSTree")
    || pythia.settings.flag("Merging:doUNLOPSSubt")
    || pythia.settings.flag("Merging:doUNLOPSLoop")
    || pythia.settings.flag("Merging:doUNLOPSSubtNLO")
    || pythia.settings.flag("Merging:doXSectionEstimate")
    || pythia.settings.flag("Dire:doMOPS")
    || pythia.settings.flag("Merging:doUserMerging")
    || pythia.settings.flag("Merging:doPTLundMerging")
    || pythia.settings.flag("Merging:doUMEPSTree")
    || pythia.settings.flag("Merging:doUMEPSSubt")) {
    pythia.setMergingHooksPtr(mergingHooksPtr);
    pythia.setMergingPtr(mergingPtr);
  }

  // Setup weight container (after user-defined enhance factors have been read)
  weightsPtr->setup();
  bool isInit = pythia.init();
  setup(pythia);

  return isInit;

}

//==========================================================================

} // end namespace Pythia8
