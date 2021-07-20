// Merging.cc is a part of the DIRE plugin to the PYTHIA event generator.
// Copyright (C) 2018 Stefan Prestel.

#include "Dire/Merging.h"
#include "Dire/DireSpace.h"
#include "Dire/DireTimes.h"

namespace Pythia8 {

//==========================================================================

// The Merging class.

//--------------------------------------------------------------------------


// Check colour/flavour correctness of state.

bool validEvent( const Event& event ) {

  bool validColour  = true;
  bool validCharge  = true;
  bool validMomenta = true;
  double mTolErr=1e-2;

  // Check charge sum in initial and final state
  double initCharge = event[3].charge() + event[4].charge();
  double finalCharge = 0.0;
  for(int i = 0; i < event.size(); ++i)
    if (event[i].isFinal()) finalCharge += event[i].charge();
  if (abs(initCharge-finalCharge) > 1e-12) validCharge = false;

  // Check that overall pT is vanishing.
  Vec4 pSum(0.,0.,0.,0.);
  for ( int i = 0; i < event.size(); ++i) {
    //if ( i ==3 || i == 4 )    pSum -= event[i].p();
    if ( event[i].status() == -21 ) pSum -= event[i].p();
    if ( event[i].isFinal() )       pSum += event[i].p();
  }
  if ( abs(pSum.px()) > mTolErr || abs(pSum.py()) > mTolErr) {
    validMomenta = false;
  }

  if ( event[3].status() == -21
    && (abs(event[3].px()) > mTolErr || abs(event[3].py()) > mTolErr)){
    validMomenta = false;
  }
  if ( event[4].status() == -21
    && (abs(event[4].px()) > mTolErr || abs(event[4].py()) > mTolErr)){
    validMomenta = false;
  }

  return (validColour && validCharge && validMomenta);

}

//--------------------------------------------------------------------------

// Initialise Merging class

void DireMerging::init(){
  // Reset minimal tms value.
  tmsNowMin             = infoPtr->eCM();

  if (!myLHEF3Ptr) {
    hasOwnLHEF3 = true;
    myLHEF3Ptr = new LHEF3FromPythia8(0, settingsPtr,
      infoPtr, particleDataPtr, 15, /*false*/ true);
    myLHEF3Ptr->openLHEF("test.lhef3");
    myLHEF3Ptr->setInit();
  }

  enforceCutOnLHE = settingsPtr->flag("Merging:enforceCutOnLHE");
  doMOPS          = settingsPtr->flag("Dire:doMOPS");
  applyTMSCut     = settingsPtr->flag("Merging:doXSectionEstimate");
  doMerging       = settingsPtr->flag("Dire:doMerging");
  usePDF          = settingsPtr->flag("ShowerPDF:usePDF");
  usePDFmass      = settingsPtr->flag("ShowerPDF:usePDFmasses")
                 && (toLower(settingsPtr->word("PDF:pSet")).find("lhapdf")
                          != string::npos);
  allowReject     = settingsPtr->flag("Merging:applyVeto");
  doMECs          = settingsPtr->flag("Dire:doMECs");
  doMEM           = settingsPtr->flag("Dire:doMEM");
  doTOMTEs        = settingsPtr->flag("Dire:doTOMTE");
  doTOMTESudakovs     = settingsPtr->flag("Dire:doTOMTE:Sudakovs");
  doTOMTEAlphasRatios = settingsPtr->flag("Dire:doTOMTE:AlphasRatios");
  doTOMTEPDFRatios    = settingsPtr->flag("Dire:doTOMTE:PDFRatios");
  clusterMode         = settingsPtr->mode("Dire:checkBiases:clusterMode");
  correctionMode      = settingsPtr->mode("Dire:checkBiases:correctionMode");
  doGenerateSubtractions   = settingsPtr->flag("Dire:doGenerateSubtractions");
  doGenerateMergingWeights = settingsPtr->flag("Dire:doGenerateMergingWeights");
  doExitAfterMerging       =  settingsPtr->flag("Dire:doExitAfterMerging");
  allowIncompleteReal
    =  settingsPtr->flag("Merging:allowIncompleteHistoriesInReal");
  nQuarksMerge    =  settingsPtr->mode("Merging:nQuarksMerge");

  doWeakMerging   =  settingsPtr->flag("SpaceShower:EWshowerByQ")
                  || settingsPtr->flag("TimeShower:EWshowerByQ");
  first = true;
  ntries=0;

  // Cross section conversion factor to undo stupid conversions done in
  // info.weight() calls.
  CONVERTMB2PB = 1.;
  if (abs(infoPtr->lhaStrategy()) == 4) CONVERTMB2PB = 1e9;

  doCheckBasics   = settingsPtr->flag("Merging:checkBiasesBasic");
  doCheckSudakovs = settingsPtr->flag("Merging:checkBiasesSudakov");
  makeToys        = settingsPtr->flag("Merging:makeToyCalculation");

  doN3LOs = makeToys || doCheckBasics || doCheckSudakovs || doTOMTEs;

}

//--------------------------------------------------------------------------

// Function to print information.
void DireMerging::statistics() {

  // Recall merging scale value.
  double tmsval         = mergingHooksPtr->tms();
  bool printBanner      = enforceCutOnLHE && tmsNowMin > TMSMISMATCH*tmsval
                        && tmsval > 0.;
  // Reset minimal tms value.
  tmsNowMin             = infoPtr->eCM();

  if (doMOPS) printBanner = false;
  if (doMEM)  printBanner = false;
  if (doMECs) printBanner = false;

  if (!printBanner) return;

  // Header.
  cout << "\n *-------  PYTHIA Matrix Element Merging Information  ------"
       << "-------------------------------------------------------*\n"
       << " |                                                            "
       << "                                                     |\n";
  // Print warning if the minimal tms value of any event was significantly
  // above the desired merging scale value.
  cout << " | Warning in DireMerging::statistics: All Les Houches events"
       << " significantly above Merging:TMS cut. Please check.       |\n";

  // Listing finished.
  cout << " |                                                            "
       << "                                                     |\n"
       << " *-------  End PYTHIA Matrix Element Merging Information -----"
       << "-----------------------------------------------------*" << endl;
}

//--------------------------------------------------------------------------

// Return event stripped from decay products.

Event DireMerging::insertResonances (const Event& inputEventIn) {

  // Find and detach decay products.
  Event newProcess = Event();
  newProcess.init("(hard process-modified)", particleDataPtr);

  // If there are already intermediate resonances, simply return
  // event w/o decay products.
  bool hasRes = false;
  for (int i = 0; i < inputEventIn.size(); ++ i)
    if ( inputEventIn[i].statusAbs() == 22) hasRes = true;
  if (hasRes) return inputEventIn;

  // Add the beam and initial partons to the event record.
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if ( inputEventIn[i].mother1() > 4
      || inputEventIn[i].statusAbs() == 22
      || inputEventIn[i].statusAbs() == 23)
      break;
    newProcess.append(inputEventIn[i]);
  }

  Vec4 pV; int chg(0);
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if (inputEventIn[i].mother1() > 4) break;
    if ( inputEventIn[i].statusAbs() != 11
      && inputEventIn[i].statusAbs() != 12
      && inputEventIn[i].statusAbs() != 21
      && inputEventIn[i].statusAbs() != 22
      && inputEventIn[i].isLepton()) {
      if (inputEventIn[i].isCharged() && inputEventIn[i].charge() < 0) chg--;
      if (inputEventIn[i].isCharged() && inputEventIn[i].charge() > 0) chg++;
      pV += inputEventIn[i].p();
    }
  }

  int idRes = 23;
  if (chg == 0)  idRes =  23;
  if (chg == -1) idRes = -24;
  if (chg == +1) idRes =  24;

  int iRes = newProcess.append(idRes,-22,3,4,0,0,0,0,
    pV, pV.mCalc(), pV.mCalc());

  // Add outgoing particles to the event record.
  int iMax(0), iMin(iRes);
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if (inputEventIn[i].mother1() > 4) break;
    if ( inputEventIn[i].statusAbs() != 11
      && inputEventIn[i].statusAbs() != 12
      && inputEventIn[i].statusAbs() != 21
      && inputEventIn[i].statusAbs() != 22
      && !inputEventIn[i].isLepton()) {
      int iNow = newProcess.append(inputEventIn[i]);
      newProcess[iNow].mothers(3,4);
      iMax = max(iMax,iNow);
      iMin = min(iMin,iNow);
    }
  }

  int iMaxRes(0), iMinRes(1000);
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if (inputEventIn[i].mother1() > 4) break;
    if ( inputEventIn[i].statusAbs() != 11
      && inputEventIn[i].statusAbs() != 12
      && inputEventIn[i].statusAbs() != 21
      && inputEventIn[i].statusAbs() != 22
      && inputEventIn[i].isLepton()) {
      int iNow = newProcess.append(inputEventIn[i]);
      newProcess[iNow].mothers(iRes,0);
      iMaxRes = max(iMaxRes,iNow);
      iMinRes = min(iMinRes,iNow);
    }
  }
  newProcess[iRes].daughters(iMinRes,iMaxRes);
  newProcess[3].daughters(iMin,iMax);
  newProcess[4].daughters(iMin,iMax);

  // Update event colour tag to maximum in whole process.
  int maxColTag = 0;
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if ( inputEventIn[i].col() > maxColTag )
      maxColTag = inputEventIn[i].col();
    if ( inputEventIn[i].acol() > maxColTag )
      maxColTag = inputEventIn[i].acol();
  }
  newProcess.initColTag(maxColTag);

  // Copy junctions from process to newProcess.
  for (int i = 0; i < inputEventIn.sizeJunction(); ++i)
    newProcess.appendJunction( inputEventIn.getJunction(i));
  newProcess.saveSize();
  newProcess.saveJunctionSize();
  // Remember scale
  newProcess.scale( inputEventIn.scale() );

  // Done
  return newProcess;

}

//--------------------------------------------------------------------------

// Return event stripped from decay products.

Event DireMerging::stripResonances (const Event& inputEventIn) {

  // Find and detach decay products.
  Event newProcess = Event();
  newProcess.init("(hard process-modified)", particleDataPtr);

  // If there are no intermediate resonances, simply return event.
  bool hasRes = false;
  for (int i = 0; i < inputEventIn.size(); ++ i)
    if ( inputEventIn[i].statusAbs() == 22) hasRes = true;
  if (!hasRes) return inputEventIn;

  // Add the beam and initial partons to the event record.
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if ( inputEventIn[i].mother1() > 4
      || inputEventIn[i].statusAbs() == 22
      || inputEventIn[i].statusAbs() == 23)
      break;
    newProcess.append(inputEventIn[i]);
  }

  // Add outgoing particles to the event record.
  int iMax(0), iMin(10000);
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if ( inputEventIn[i].mother1() <= 4
      || inputEventIn[i].statusAbs() == 11
      || inputEventIn[i].statusAbs() == 12
      || inputEventIn[i].statusAbs() == 21
      || inputEventIn[i].statusAbs() == 22) continue;
    int iNow = newProcess.append(inputEventIn[i]);
    newProcess[iNow].mothers(3,4);
    iMax = max(iMax,iNow);
    iMin = min(iMin,iNow);
  }

  if (iMax>=iMin){
    newProcess[3].daughters(iMin,iMax);
    newProcess[4].daughters(iMin,iMax);
  }

  // Update event colour tag to maximum in whole process.
  int maxColTag = 0;
  for (int i = 0; i < inputEventIn.size(); ++ i) {
    if ( inputEventIn[i].col() > maxColTag )
      maxColTag = inputEventIn[i].col();
    if ( inputEventIn[i].acol() > maxColTag )
      maxColTag = inputEventIn[i].acol();
  }
  newProcess.initColTag(maxColTag);

  // Copy junctions from process to newProcess.
  for (int i = 0; i < inputEventIn.sizeJunction(); ++i)
    newProcess.appendJunction( inputEventIn.getJunction(i));
  newProcess.saveSize();
  newProcess.saveJunctionSize();
  // Remember scale
  newProcess.scale( inputEventIn.scale() );

  // Done
  return newProcess;

}

//--------------------------------------------------------------------------

void DireMerging::storeInfos() {

  // Clear previous information.
  clearInfos();

  // Store information on every possible last clustering.
  for ( int i = 0 ; i < int(myHistory->children.size()); ++i) {
    // Just store pT and mass for now.
    stoppingScalesSave.push_back(myHistory->children[i]->clusterIn.pT());
    radSave.push_back(myHistory->children[i]->clusterIn.radPos);
    emtSave.push_back(myHistory->children[i]->clusterIn.emt1Pos);
    recSave.push_back(myHistory->children[i]->clusterIn.recPos);
    mDipSave.push_back(myHistory->children[i]->clusterIn.mass());
  }

}

//--------------------------------------------------------------------------

void DireMerging::getStoppingInfo(double scales [100][100],
  double masses [100][100]) {

  int posOffest=2;
  for (unsigned int i=0; i < radSave.size(); ++i){
    scales[radSave[i]-posOffest][recSave[i]-posOffest] = stoppingScalesSave[i];
    masses[radSave[i]-posOffest][recSave[i]-posOffest] = mDipSave[i];
  }

}

//--------------------------------------------------------------------------

double DireMerging::generateSingleSudakov ( double pTbegAll, 
  double pTendAll, double m2dip, int idA, int type, double s, double x) {
  return isr->noEmissionProbability( pTbegAll, pTendAll, m2dip, idA,
    type, s, x);
}

//--------------------------------------------------------------------------

void DireMerging::reset() {
  mergingHooksPtr->partonSystemsPtr->clear();
  isr->clear();
  fsr->clear();
  beamAPtr->clear();
  beamBPtr->clear();
}

//--------------------------------------------------------------------------

// Function to steer different merging prescriptions.

void DireMerging::initSettings(){

  // Reinitialise hard process.
  mergingHooksPtr->hardProcess->clear();
  string processNow = settingsPtr->word("Merging:Process");
  // Remove whitespace from process string
  while(processNow.find(" ", 0) != string::npos)
    processNow.erase(processNow.begin()+processNow.find(" ",0));
#if (PYTHIA_VERSION_INTEGER >= 8242)
  mergingHooksPtr->processNow  = processNow;
#endif
  mergingHooksPtr->hardProcess->initOnProcess(processNow, particleDataPtr);

  mergingHooksPtr->doUserMergingSave
    = settingsPtr->flag("Merging:doUserMerging");
  mergingHooksPtr->doMGMergingSave
    = settingsPtr->flag("Merging:doMGMerging");
  mergingHooksPtr->doKTMergingSave
    = settingsPtr->flag("Merging:doKTMerging");
  mergingHooksPtr->doPTLundMergingSave
    = settingsPtr->flag("Merging:doPTLundMerging");
  mergingHooksPtr->doCutBasedMergingSave
    = settingsPtr->flag("Merging:doCutBasedMerging");
  mergingHooksPtr->doUNLOPSTreeSave
    = settingsPtr->flag("Merging:doUNLOPSTree");
  mergingHooksPtr->doUNLOPSLoopSave
    = settingsPtr->flag("Merging:doUNLOPSLoop");
  mergingHooksPtr->doUNLOPSSubtSave
    = settingsPtr->flag("Merging:doUNLOPSSubt");
  mergingHooksPtr->doUNLOPSSubtNLOSave
    = settingsPtr->flag("Merging:doUNLOPSSubtNLO");
  mergingHooksPtr->doUMEPSTreeSave
    = settingsPtr->flag("Merging:doUMEPSTree");
  mergingHooksPtr->doUMEPSSubtSave
    = settingsPtr->flag("Merging:doUMEPSSubt");
  mergingHooksPtr->nReclusterSave
    = settingsPtr->mode("Merging:nRecluster");

  mergingHooksPtr->hasJetMaxLocal  = false;
  mergingHooksPtr->nJetMaxLocal
    = mergingHooksPtr->nJetMaxSave;
  mergingHooksPtr->nJetMaxNLOLocal
    = mergingHooksPtr->nJetMaxNLOSave;

}

//--------------------------------------------------------------------------

void DireMerging::initOnEvent(const Event& process){

  unitarizationFactor(1.);

  string processNow = settingsPtr->word("Merging:Process");

  // Reset to default merging scale.
  mergingHooksPtr->tms(mergingHooksPtr->tmsCut());

  if ( doN3LO() ) return; 

  int nPartons = 0;
  // Do not include resonance decay products in the counting.
  Event newp( evtUtils->eventForMerging( process, false) );

  // Call nSteps once to store some counters for inclusive merging.
  mergingHooksPtr->getNumberOfClusteringSteps( newp, true);

  // Dynamically set the process string.
  if ( processNow.find("guess") != string::npos) {
    //string processString = "";
    string processString;
    // Set incoming particles.
    int beamAid = beamAPtr->id();
    int beamBid = beamBPtr->id();
    if (abs(beamAid) == 2212) processString += "p";
    if (beamAid == 11)        processString += "e-";
    if (beamAid ==-11)        processString += "e+";
    if (abs(beamBid) == 2212) processString += "p";
    if (beamBid == 11)        processString += "e-";
    if (beamBid ==-11)        processString += "e+";
    processString += ">";
    // Set outgoing particles.
    bool foundOutgoing = false;
    for(int i=0; i < int(newp.size()); ++i)
      if ( newp[i].isFinal()
        && ( newp[i].colType() == 0
          || newp[i].idAbs() > 21
          || ( newp[i].id() != 21
            && newp[i].idAbs() > nQuarksMerge) ) ) {
        foundOutgoing = true;
        ostringstream proc;
        proc << "{" << newp[i].name() << "," << newp[i].id()
             << "}";
        processString += proc.str();
      }
    // Set the process string.
    if (foundOutgoing) settingsPtr->word("Merging:Process", processString);
  }

  // Loop through event and count.
  for(int i=0; i < int(newp.size()); ++i)
    if ( newp[i].isFinal()
      && newp[i].colType()!= 0
      && ( newp[i].id() == 21 || newp[i].idAbs() <= nQuarksMerge))
      nPartons++;
  nPartons -= mergingHooksPtr->hardProcess->nQuarksOut();

  // Get number of requested partons.
  string nps_nlo = infoPtr->getEventAttribute("npNLO",true);
  //int np_nlo     = (nps_nlo != "") ? atoi((char*)nps_nlo.c_str()) : -1;
  int np_nlo     = (!nps_nlo.empty()) ? atoi((char*)nps_nlo.c_str()) : -1;
  string nps_lo  = infoPtr->getEventAttribute("npLO",true);
  //int np_lo      = (nps_lo != "") ? atoi((char*)nps_lo.c_str()) : -1;
  int np_lo      = (!nps_lo.empty()) ? atoi((char*)nps_lo.c_str()) : -1;

  // Set number of requested partons.
  if (np_nlo > -1){
    settingsPtr->mode("Merging:nRequested", np_nlo);
    np_lo = -1;
  } else if (np_lo > -1){
    settingsPtr->mode("Merging:nRequested", np_lo);
    np_nlo = -1;
  } else {
    settingsPtr->mode("Merging:nRequested", nPartons);
    np_nlo = -1;
    np_lo = nPartons;
  }

  mergingHooksPtr->nRequestedSave
    = settingsPtr->mode("Merging:nRequested");

  // Store merging scheme.
  bool isumeps  = mergingHooksPtr->doUMEPSMerging();
  bool isunlops = mergingHooksPtr->doUNLOPSMerging();

  if ( (settingsPtr->flag("Merging:doUNLOPSTree")
     || settingsPtr->flag("Merging:doUNLOPSSubt")
     || settingsPtr->flag("Merging:doUNLOPSSubtNLO")) && np_lo == 0)
     return;

  if (settingsPtr->flag("Merging:doXSectionEstimate")) {
    if (settingsPtr->flag("Merging:doUNLOPSSubt")) {
      settingsPtr->flag("Merging:doUNLOPSTree", true);
      settingsPtr->flag("Merging:doUNLOPSSubt", false);
    }
    if (settingsPtr->flag("Merging:doUNLOPSSubtNLO")) {
      settingsPtr->flag("Merging:doUNLOPSLoop", true);
      settingsPtr->flag("Merging:doUNLOPSSubtNLO", false);
    }
    return;
  }

  // Choose randomly if this event should be treated as subtraction or
  // as regular event. Put the correct settings accordingly.
  double normFactor = 1.;
  if (isunlops && np_nlo == 0 && np_lo == -1) {
    settingsPtr->flag("Merging:doUNLOPSTree", false);
    settingsPtr->flag("Merging:doUNLOPSSubt", false);
    settingsPtr->flag("Merging:doUNLOPSLoop", true);
    settingsPtr->flag("Merging:doUNLOPSSubtNLO", false);
    settingsPtr->mode("Merging:nRecluster",0);
    normFactor *= 1.;
  } else if (isunlops && np_nlo > 0 && np_lo == -1) {
    normFactor *= 2.;
    if (rndmPtr->flat() < 0.5) {
      normFactor *= -1.;
      settingsPtr->flag("Merging:doUNLOPSTree", false);
      settingsPtr->flag("Merging:doUNLOPSSubt", false);
      settingsPtr->flag("Merging:doUNLOPSLoop", false);
      settingsPtr->flag("Merging:doUNLOPSSubtNLO", true);
      settingsPtr->mode("Merging:nRecluster",1);
    } else {
      settingsPtr->flag("Merging:doUNLOPSTree", false);
      settingsPtr->flag("Merging:doUNLOPSSubt", false);
      settingsPtr->flag("Merging:doUNLOPSLoop", true);
      settingsPtr->flag("Merging:doUNLOPSSubtNLO", false);
      settingsPtr->mode("Merging:nRecluster",0);
    }
  } else if (isunlops && np_nlo == -1 && np_lo > -1) {
    normFactor *= 2.;
    if (rndmPtr->flat() < 0.5) {
      normFactor *= -1.;
      //normFactor *=0.;
      settingsPtr->flag("Merging:doUNLOPSTree", false);
      settingsPtr->flag("Merging:doUNLOPSSubt", true);
      settingsPtr->flag("Merging:doUNLOPSLoop", false);
      settingsPtr->flag("Merging:doUNLOPSSubtNLO", false);
      settingsPtr->mode("Merging:nRecluster",1);

      // Double reclustering for exclusive NLO cross sections.
      bool isnlotilde = settingsPtr->flag("Merging:doUNLOPSTilde");
      int nmaxNLO = settingsPtr->mode("Merging:nJetMaxNLO");
      if ( isnlotilde
        && nmaxNLO > 0
        && np_lo <= nmaxNLO+1
        && np_lo > 1 ){
        normFactor *= 2.;
        if (rndmPtr->flat() < 0.5)
          settingsPtr->mode("Merging:nRecluster",2);
      }
    } else {
      settingsPtr->flag("Merging:doUNLOPSTree", true);
      settingsPtr->flag("Merging:doUNLOPSSubt", false);
      settingsPtr->flag("Merging:doUNLOPSLoop", false);
      settingsPtr->flag("Merging:doUNLOPSSubtNLO", false);
      settingsPtr->mode("Merging:nRecluster",0);
    }
  } else if (isumeps && np_lo == 0) {
    settingsPtr->flag("Merging:doUMEPSTree", true);
    settingsPtr->flag("Merging:doUMEPSSubt", false);
    settingsPtr->mode("Merging:nRecluster",0);
  } else if (isumeps && np_lo > 0) {
    normFactor *= 2.;
    if (rndmPtr->flat() < 0.5) {
      normFactor *= -1.;
      settingsPtr->flag("Merging:doUMEPSTree", false);
      settingsPtr->flag("Merging:doUMEPSSubt", true);
      settingsPtr->mode("Merging:nRecluster",1);
    } else {
      settingsPtr->flag("Merging:doUMEPSTree", true);
      settingsPtr->flag("Merging:doUMEPSSubt", false);
      settingsPtr->mode("Merging:nRecluster",0);
    }
  }

  // Remember factor from assigning unitarization procedure.
  unitarizationFactor(normFactor);

}

//--------------------------------------------------------------------------

// Function to steer different merging prescriptions.

int DireMerging::mergeProcess(Event& state){

  //cout << "\n\n" << __func__ << " new event \n";
  //direInfoPtr->clearAll();
  //Event process(insertResonances(state));

  // Construct hard process for merging.
  Event process;
  if (doMECs || makeToys)
    process = stripResonances(state);
  else if (doWeakMerging) process = insertResonances(state);
  else                    process = state;

  state = process;

  //fsr->direInfoPtr->eatCout();
  //cout << "\n\n\n\n\n new event" << endl;
  //state.list(false,false,10);
  //process.list(false,false,10);
  //fsr->direInfoPtr->freeCout();

  // Reject input events with problemaatic flavor/color/momentum.
  BeamParticle* beam = ( particleDataPtr->isHadron(beamAPtr->id()) )
    ? beamAPtr : beamBPtr;

  if (!evtUtils->validEvent(process,beam,usePDFmass,false,-1)) {
    string message="Warning in DireMerging::mergeProcess: Input event";
    message+=" has inconsistent flavor/color/momentum. Reject.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Clear and reset previous event-by-event information.
  clearInfos();
  initOnEvent(process);
  initSettings();
  int vetoCode = 1;

  // Possibility to apply merging scale to an input event.
  if (!doMECs && applyTMSCut && cutOnProcess(process) ) {
    //infoPtr->updateWeight(0.);
    //return 1;
    return vetoEvent();
  }
  // Done if only a cut should be applied.
  if (applyTMSCut && !doMOPS && !doMECs) {
    return 1;
  }

  //if (doTOMTE()) return matchN3LO (process);

  if (doMerging){

    // Do not include resonance decay products in the counting.
    Event newp( evtUtils->eventForMerging( process, false) );
    int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newp);
    mergingHooksPtr->nHardNowSave = nSteps;
    if (doMEM) {
      int nFinal(0), nQuarks(0), nGammas(0), nLeptons(0);
      for (int i=3; i < newp.size(); ++i) {
        if (newp[i].idAbs() <   7) nQuarks++;
        if (newp[i].idAbs() == 22) nGammas++;
        if (newp[i].isLepton())    nLeptons++;
        if (newp[i].isFinal())     nFinal++;
      }
      settingsPtr->mode("DireSpace:nFinalMax",nFinal-1);
      settingsPtr->mode("DireTimes:nFinalMax",nFinal-1);
      if (nQuarks > 4) return 1;
      if (nLeptons >4) return 1;
      if (nLeptons+nQuarks>7) return 1;
    }

    // For ME corrections, only do mergingHooksPtr reinitialization here,
    // and do not perform any veto.
    if (doMECs) return 1;


    if (makeToys) {
      vetoCode = makeToyCalculation(process);
      state=process;
      if (doExitAfterMerging) return 0;
      return vetoCode;
    }

    if (doCheckBasics) {
      vetoCode = checkBiasCorrectionBasic(process);
      state=process;
      if (doExitAfterMerging) return 0;
      return vetoCode;
    }

    if (doCheckSudakovs) {
      vetoCode = checkBiasCorrectionIncludingSudakov(process);
      state=process;
      if (doExitAfterMerging) return 0;
      return vetoCode;
    }
    
    if (doTOMTE()) {
      vetoCode = matchN3LO(process);
      state=process;
      if (doExitAfterMerging) return 0;
      return vetoCode;
    }


    if (doMEM) mergingHooksPtr->orderHistories(false);

    //if (doMOPS) implement generateUnorderedPoint(process); 

    bool foundHistories = generateHistories(process, false);
    int returnCode = (foundHistories) ? 1 : 0;
    if (doMOPS && myHistory->foundAnyOrderedPaths() && nSteps > 0)
      returnCode = 0;

    // Done if only a cut should be applied.
    if (applyTMSCut && doMOPS) return 1;

    // For interative resummed matrix element method, tag histories and exit.
    if (doMEM) { 
      tagHistories();
      return 1;
    }

    if (doGenerateSubtractions) calculateSubtractions();

    bool useAll = doMOPS;
    double RNpath = getPathIndex(useAll);
    if ((doMOPS && returnCode > 0) || doGenerateMergingWeights)
      returnCode = calculateWeights(RNpath, useAll);

    int tmp_code = getStartingConditions( RNpath, process);
    if (returnCode > 0) returnCode = tmp_code;

    // Ensure that merging weight is not counted twice.
    if (returnCode == 0) vetoEvent();

    if (!allowReject && returnCode < 1) returnCode=1;

    // Store information before leaving.
    if (foundHistories) storeInfos();

    // Overwrite state to return to Pythia.
    state=process;

    if (doMOPS) {
      vetoEvent();
      return returnCode;
    }

    // Veto if we do not want to do event generation.
    if (doExitAfterMerging) return -1;

    return 1;
  }

  // Possibility to perform CKKW-L merging on this event.
  if ( mergingHooksPtr->doCKKWLMerging() )
    vetoCode = mergeProcessCKKWL(process);

  // Possibility to perform UMEPS merging on this event.
  if ( mergingHooksPtr->doUMEPSMerging() )
     vetoCode = mergeProcessUMEPS(process);

  // Possibility to perform UNLOPS merging on this event.
  if ( mergingHooksPtr->doUNLOPSMerging() )
    vetoCode = mergeProcessUNLOPS(process);

  // Overwrite state to return to Pythia.
  state=process;

  return vetoCode;

}

//--------------------------------------------------------------------------

// Function to perform CKKW-L merging on this event.

int DireMerging::mergeProcessCKKWL( Event& process) {

  // Ensure that merging hooks to not veto events in the trial showers.
  mergingHooksPtr->doIgnoreStep(true);
  // For pp > h, allow cut on state, so that underlying processes
  // can be clustered to gg > h
  if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0 )
    mergingHooksPtr->allowCutOnRecState(true);

  // Construct all histories. 
  // This needs to be done because MECs can depend on unordered paths if
  // these unordered paths are ordered up to some point.
  mergingHooksPtr->orderHistories(false);

  // Reset weight of the event.
  double wgt = 1.0;
  mergingHooksPtr->setWeightCKKWL(1.);
  mergingHooksPtr->muMI(-1.);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'.
  mergingHooksPtr->storeHardProcessCandidates( newProcess);

  // Calculate number of clustering steps.
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;
  double tmsnow = mergingHooksPtr->tmsNow( newProcess );
  int vetoCode = mergingHooksPtr->ktTypeSave;
  mergingHooksPtr->ktTypeSave=-99;

  // Too few steps can be possible if a chain of resonance decays has been
  // removed. In this case, reject this event, since it will be handled in
  // lower-multiplicity samples.
  int nRequested = mergingHooksPtr->nRequested();

  // Store hard event cut information, reset veto information.
  mergingHooksPtr->setHardProcessInfo(nSteps, tmsnow);

  if (nSteps < nRequested && allowReject) return vetoEvent();

  // Reset the minimal tms value, if necessary.
  tmsNowMin     = (nSteps == 0) ? 0. : min(tmsNowMin, tmsnow);

  // Set dummy process scale.
  newProcess.scale(0.0);
  // Generate all histories.
  DireHistory FullHistory( nSteps, 0.0, newProcess, DireClustering(),
    mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
    trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true, false, 
    1.0, 1.0, 1.0, 1.0, 0);

  // Project histories onto desired branches, e.g. only ordered paths.
  FullHistory.projectOntoDesiredHistories();

  // Setup to choose shower starting conditions randomly.
  double sumAll(0.), sumFullAll(0.);
  double RN = FullHistory.getPathIndexRandom(rndmPtr, true, sumAll,
     sumFullAll);

  // Do not apply cut if the configuration could not be projected onto an
  // underlying born configuration.
  bool applyCut = nSteps > 0 && FullHistory.select(RN)->nClusterings(NULL) > 0;

  Event core( FullHistory.lowestMultProc(RN) );
  // Set event-specific merging scale cut. Q2-dependent for DIS.
  if ( mergingHooksPtr->getProcessString().compare("e+p>e+j") == 0
    || mergingHooksPtr->getProcessString().compare("e-p>e-j") == 0 ) {

    // Set dynamical merging scale for DIS
    if (FullHistory.isDIS2to2(core)) {
      int iInEl(0), iOutEl(0);
      for ( int i=0; i < core.size(); ++i )
        if ( core[i].idAbs() == 11 ) {
          if ( core[i].status() == -21 ) iInEl  = i;
          if ( core[i].isFinal() )       iOutEl = i;
        }
      double Q      = sqrt( -(core[iInEl].p() - core[iOutEl].p() ).m2Calc());
      double tmsCut = mergingHooksPtr->tmsCut();
      double tmsEvt = tmsCut / sqrt( 1. + pow( tmsCut/ ( 0.5*Q ), 2)  );
      mergingHooksPtr->tms(tmsEvt);

    } else if (FullHistory.isMassless2to2(core)) {
      double mT(1.);
      for ( int i=0; i < core.size(); ++i )
        if ( core[i].isFinal() ) mT *= core[i].mT();
      double Q      = sqrt(mT);
      double tmsCut = mergingHooksPtr->tmsCut();
      double tmsEvt = tmsCut / sqrt( 1. + pow( tmsCut/ ( 0.5*Q ), 2)  );
      mergingHooksPtr->tms(tmsEvt);
    }
  }
  double tmsval = mergingHooksPtr->tms();

  // Enfore merging scale cut if the event did not pass the merging scale
  // criterion.
  bool doVeto = enforceCutOnLHE && applyCut && tmsnow < tmsval && tmsnow > 0.;
  //int vetoCode = mergingHooksPtr->ktTypeSave;
  //mergingHooksPtr->ktTypeSave=-99;
  if (tmsnow <= 0. && vetoCode!=-99) {
    if (vetoCode == -1) doVeto = enforceCutOnLHE && applyCut;
    else                doVeto = false;
  }
  //if ( enforceCutOnLHE && applyCut && tmsnow < tmsval ) {
  if (doVeto) {
    string message="Warning in DireMerging::mergeProcessCKKWL: Les Houches Event";
    message+=" fails merging scale cut. Reject event.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Check if more steps should be taken.
  int nFinalP(0), nFinalW(0), nFinalZ(0);
  for ( int i = 0; i < core.size(); ++i )
    if ( core[i].isFinal() ) {
      if ( core[i].colType() != 0 ) nFinalP++;
      if ( core[i].idAbs() == 24 )  nFinalW++;
      if ( core[i].idAbs() == 23 )  nFinalZ++;
    }
  bool complete = (FullHistory.select(RN)->nClusterings(NULL) == nSteps) ||
    (nFinalP == 2 && nFinalW+nFinalZ == 0);
  if ( !complete ) {
    string message="Warning in DireMerging::mergeProcessCKKWL: No clusterings";
    message+=" found. History incomplete.";
    infoPtr->errorMsg(message);
  }

  // Calculate CKKWL reweighting for all paths.
  double wgtsum(0.);
  double lastp(0.);
  for ( map<double, DireHistory*>::iterator
    it = FullHistory.branches.begin();
    it != FullHistory.branches.end(); ++it ) {

    // Double to access path.
    double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
    lastp = it->first;

    // Probability of path.
    double probPath = it->second->prodOfProbsFull/sumFullAll;

    FullHistory.select(indexNow)->setSelectedChild();

    // Calculate CKKWL weight:
    double w = FullHistory.weightTREE( trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      indexNow);

    wgtsum += probPath*w;
  }
  wgt = wgtsum;

  // Event with production scales set for further (trial) showering
  // and starting conditions for the shower.
  FullHistory.getStartingConditions( RN, process );
  FullHistory.select(RN)->setSelectedChild();

  // If necessary, reattach resonance decay products.
  evtUtils->reattachDecaysAfterMerging(process);

  // Ensure that merging weight is not counted twice.
  bool includeWGT = mergingHooksPtr->includeWGTinXSEC();

  // Save the weight of the event for histogramming.
  if (!includeWGT) mergingHooksPtr->setWeightCKKWL(wgt);

  // Update the event weight.
  if (includeWGT) infoPtr->updateWeight(infoPtr->weight()/CONVERTMB2PB*wgt);

  // Allow merging hooks to veto events from now on.
  mergingHooksPtr->doIgnoreStep(false);

  // If no-emission probability is zero.
  if (allowReject && wgt == 0.) return 0;

  // Done
  return 1;

}

//--------------------------------------------------------------------------

// Function to perform UMEPS merging on this event.

int DireMerging::mergeProcessUMEPS( Event& process) {

  // Initialise which part of UMEPS merging is applied.
  bool doUMEPSTree                = settingsPtr->flag("Merging:doUMEPSTree");
  bool doUMEPSSubt                = settingsPtr->flag("Merging:doUMEPSSubt");
  // Save number of clustering steps
  //mergingHooksPtr->nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  int nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  // Set number of clustering steps to zero, such that cuts and history
  // selection are applied identically to normal and subtractive events.
  mergingHooksPtr->nReclusterSave = 0;
  int nRecluster                  = settingsPtr->mode("Merging:nRecluster");

  // Ensure that merging hooks does not remove emissions.
  mergingHooksPtr->doIgnoreEmissions(true);
  // For pp > h, allow cut on state, so that underlying processes
  // can be clustered to gg > h
  if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0 )
    mergingHooksPtr->allowCutOnRecState(true);
  //// For now, prefer construction of ordered histories.
  //mergingHooksPtr->orderHistories(true);
  // Do not prefer ordered histories.
  mergingHooksPtr->orderHistories(false);

  // Reset weights of the event.
  double wgt   = 1.;
  mergingHooksPtr->setWeightCKKWL(1.);
  mergingHooksPtr->muMI(-1.);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'.
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps.
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Check if event passes the merging scale cut.
  double tmsval   = mergingHooksPtr->tms();
  // Get merging scale in current event.
  double tmsnow  = mergingHooksPtr->tmsNow( newProcess );
  int vetoCode = mergingHooksPtr->ktTypeSave;
  mergingHooksPtr->ktTypeSave=-99;
  int nRequested = mergingHooksPtr->nRequested();

  // Too few steps can be possible if a chain of resonance decays has been
  // removed. In this case, reject this event, since it will be handled in
  // lower-multiplicity samples.
  if (nSteps < nRequested && allowReject) return vetoEvent();

  // Reset the minimal tms value, if necessary.
  tmsNowMin      = (nSteps == 0) ? 0. : min(tmsNowMin, tmsnow);

  // Get random number to choose a path.
  // Set dummy process scale.
  newProcess.scale(0.0);
  // Generate all histories.
  DireHistory FullHistory( nSteps, 0.0, newProcess, DireClustering(),
    mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
    trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true, false,
    1.0, 1.0, 1.0, 1.0, 0);
  // Project histories onto desired branches, e.g. only ordered paths.
  FullHistory.projectOntoDesiredHistories();

  // Setup to choose shower starting conditions randomly.
  double sumAll(0.), sumFullAll(0.);
  double RN = FullHistory.getPathIndexRandom(rndmPtr, true, sumAll,
     sumFullAll);

  // Do not apply cut if the configuration could not be projected onto an
  // underlying born configuration.
  bool applyCut = nSteps > 0 && FullHistory.select(RN)->nClusterings(NULL) > 0;

  // Enfore merging scale cut if the event did not pass the merging scale
  // criterion.
  bool doVeto = enforceCutOnLHE && applyCut && tmsnow < tmsval && tmsnow > 0.;
  if (tmsnow <= 0. && vetoCode!=-99) {
    if (vetoCode == -1) doVeto = enforceCutOnLHE && applyCut;
    else                doVeto = false;
  }
  if (doVeto) {
    string message="Warning in DireMerging::mergeProcessUMEPS: Les Houches Event";
    message+=" fails merging scale cut. Reject event.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Restore information on nRecluster
  mergingHooksPtr->nReclusterSave = nReclusterSave;
  int nPerformed = 0;

  // Calculate CKKWL reweighting for all paths.
  double wgtsum(0.);
  double lastp(0.);
  for ( map<double, DireHistory*>::iterator
    it = FullHistory.branches.begin();
    it != FullHistory.branches.end(); ++it ) {

    // Double to access path.
    double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
    lastp = it->first;

    // Probability of path.
    double probPath = it->second->prodOfProbsFull/sumFullAll;

    FullHistory.select(indexNow)->setSelectedChild();

    nPerformed = 0;
    // Get the number of clustering steps, to ensure that MPI is properly 
    // initialized. The particular function is *only* used to retrieve nPerformed
    if (doUMEPSSubt) FullHistory.getFirstClusteredEventAboveTMS( 
      indexNow, nRecluster, newProcess, nPerformed, false );
    mergingHooksPtr->nMinMPI(nSteps - nPerformed);

    // Calculate CKKWL weight:
    double w = doUMEPSTree
     //? FullHistory.weight_UMEPS_TREE( trialPartonLevelPtr,
      ? FullHistory.weightTREE( trialPartonLevelPtr,
          mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
          mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
          indexNow)
      : FullHistory.weight_UMEPS_SUBT( trialPartonLevelPtr,
          mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
          mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
          indexNow);
    wgtsum += probPath*w;
  }
  wgt = wgtsum;

  // Event with production scales set for further (trial) showering
  // and starting conditions for the shower.
  if ( doUMEPSTree ) FullHistory.getStartingConditions( RN, process );
  // Do reclustering steps.
  else FullHistory.getFirstClusteredEventAboveTMS( RN, nRecluster, process,
    nPerformed, true );

  // Ensure that merging weight is not counted twice.
  bool includeWGT = mergingHooksPtr->includeWGTinXSEC();

  // Save the weight of the event for histogramming.
  if (!includeWGT) mergingHooksPtr->setWeightCKKWL(unitarizationFactor()*wgt);

  // Update the event weight.
  if (includeWGT) infoPtr->updateWeight(infoPtr->weight()/CONVERTMB2PB*
                                        unitarizationFactor()*wgt);

  // Set QCD 2->2 starting scale different from arbitrary scale in LHEF!
  // --> Set to minimal mT of partons.
  int nFinal = 0;
  double muf = process[0].e();
  for ( int i=0; i < process.size(); ++i )
  if ( process[i].isFinal()
    && (process[i].colType() != 0 || process[i].id() == 22 ) ) {
    nFinal++;
    muf = min( muf, abs(process[i].mT()) );
  }

  // For pure QCD dijet events (only!), set the process scale to the
  // transverse momentum of the outgoing partons.
  // Calculate number of clustering steps.
  int nStepsNew = mergingHooksPtr->getNumberOfClusteringSteps(process);
  if ( nStepsNew == 0
    && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
      || mergingHooksPtr->getProcessString().compare("pp>aj") == 0) )
    process.scale(muf);

  // Reset hard process candidates (changed after clustering a parton).
  mergingHooksPtr->storeHardProcessCandidates( process );

  // Check if resonance structure has been changed
  //  (e.g. because of clustering W/Z/gluino)
  vector <int> oldResonance;
  for ( int i=0; i < newProcess.size(); ++i )
    if ( newProcess[i].status() == 22 )
      oldResonance.push_back(newProcess[i].id());
  vector <int> newResonance;
  for ( int i=0; i < process.size(); ++i )
    if ( process[i].status() == 22 )
      newResonance.push_back(process[i].id());
  // Compare old and new resonances
  for ( int i=0; i < int(oldResonance.size()); ++i )
    for ( int j=0; j < int(newResonance.size()); ++j )
      if ( newResonance[j] == oldResonance[i] ) {
        oldResonance[i] = 99;
        break;
      }
  bool hasNewResonances = (newResonance.size() != oldResonance.size());
  for ( int i=0; i < int(oldResonance.size()); ++i )
    hasNewResonances = (oldResonance[i] != 99);

  // If necessary, reattach resonance decay products.
  if (!hasNewResonances) evtUtils->reattachDecaysAfterMerging(process);

  // Allow merging hooks to remove emissions from now on.
  mergingHooksPtr->doIgnoreEmissions(false);

  // If no-emission probability is zero.
  if (allowReject && wgt == 0.) return 0;

  // If the resonance structure of the process has changed due to reclustering,
  // redo the resonance decays in Pythia::next()
  if (hasNewResonances) return 2;

  // Done
  return 1;

}

//--------------------------------------------------------------------------

// Function to perform UNLOPS merging on this event.

int DireMerging::mergeProcessUNLOPS( Event& process) {

  // Initialise which part of UNLOPS merging is applied.
  //bool nloTilde         = settingsPtr->flag("Merging:doUNLOPSTilde");
  bool doUNLOPSTree     = settingsPtr->flag("Merging:doUNLOPSTree");
  bool doUNLOPSLoop     = settingsPtr->flag("Merging:doUNLOPSLoop");
  bool doUNLOPSSubt     = settingsPtr->flag("Merging:doUNLOPSSubt");
  bool doUNLOPSSubtNLO  = settingsPtr->flag("Merging:doUNLOPSSubtNLO");
  // Save number of clustering steps
  int nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  int nRecluster = nReclusterSave;
  mergingHooksPtr->nReclusterSave = nReclusterSave;
  if (doUNLOPSSubt || doUNLOPSSubtNLO) mergingHooksPtr->nReclusterSave = 0;

  // Ensure that merging hooks to not remove emissions
  mergingHooksPtr->doIgnoreEmissions(true);
  //// For now, prefer construction of ordered histories.
  //mergingHooksPtr->orderHistories(true);
  //if (doUNLOPSLoop || doUNLOPSSubtNLO) mergingHooksPtr->orderHistories(false);
  // Do not prefer ordered histories.
  mergingHooksPtr->orderHistories(false);
  // For pp > h, allow cut on state, so that underlying processes
  // can be clustered to gg > h
  if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0)
    mergingHooksPtr->allowCutOnRecState(true);

  // Reset weight of the event.
  double wgt      = 1.;
  mergingHooksPtr->setWeightCKKWL(1.);
  // Reset the O(alphaS)-term of the UMEPS weight.
  double wgtFIRST = 0.;
  mergingHooksPtr->setWeightFIRST(0.);
  mergingHooksPtr->muMI(-1.);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  int nRequested = mergingHooksPtr->nRequested();
  bool containsRealKin = nSteps > nRequested && nSteps > 0;
  // Too few steps can be possible if a chain of resonance decays has been
  // removed. In this case, reject this event, since it will be handled in
  // lower-multiplicity samples.
  if (nSteps < nRequested) {
    string message="Warning in DireMerging::mergeProcessUNLOPS: Input event";
    message+=" does not contain enough partons after removing decay products.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Check if event passes the merging scale cut.
  double tmsval  = mergingHooksPtr->tms();
  // Get merging scale in current event.
  double tmsnow  = !containsRealKin ? mergingHooksPtr->tmsNow(newProcess) : 0.;
  int vetoCode = mergingHooksPtr->ktTypeSave;
  mergingHooksPtr->ktTypeSave=-99;

  // Reset the minimal tms value, if necessary.
  tmsNowMin = (nSteps == 0) ? 0. : min(tmsNowMin, tmsnow);

  // Set dummy process scale.
  newProcess.scale(0.0);
  // Generate all histories
  DireHistory FullHistory( nSteps, 0.0, newProcess, DireClustering(),
     mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
     trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
     containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);

  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = &FullHistory;
  if ( containsRealKin && !FullHistory.children.empty()) {
    //FullHistory.projectOntoDesiredHistories();
    //picked = FullHistory.getProbabilisticFullLeaf(rndmPtr).second;
    //picked->rescaleProbs();
    picked = FullHistory.getDemocraticLeaf(rndmPtr).second;
    picked->rescaleProbs();
    //picked = FullHistory.getProbabilisticLeaf(rndmPtr);
    picked->mother = 0;
    //mergingHooksPtr->orderHistories(true);
    picked->projectOntoDesiredHistories();
  } else {
    // Project histories onto desired branches, e.g. only ordered paths.
    //if (doUNLOPSLoop || doUNLOPSSubtNLO) mergingHooksPtr->orderHistories(true);
    //mergingHooksPtr->orderHistories(true);
    picked->projectOntoDesiredHistories();
  }

  // Pick path at random (assuming that the weight of ALL paths are used
  // later to perform reweighting.
  double sumAll(0.), sumFullAll(0.);
  double RN = picked->getPathIndexRandom(rndmPtr, true, sumAll,
    sumFullAll);

  // Now enfore merging scale cut if the input event did not pass the merging
  // scale. Note: Do not apply cut if the configuration could not be projected
  // onto an underlying born configuration.
  bool doVetoInputState = enforceCutOnLHE && !containsRealKin
    && nSteps > 0
    && FullHistory.select(RN)->nClusterings(NULL) > 0
    && nSteps == nRequested
    && tmsnow < tmsval;
  // If merging scale is not well-defined, check veto code instead!
  //int vetoCode = mergingHooksPtr->ktTypeSave;
  //mergingHooksPtr->ktTypeSave=-99;
  if (tmsnow <= 0. && vetoCode!=-99) {
    if (vetoCode == -1) doVetoInputState = enforceCutOnLHE && !containsRealKin
      && nSteps > 0
      && FullHistory.select(RN)->nClusterings(NULL) > 0
      && nSteps == nRequested;
    else                doVetoInputState = false;
  }
  if (doVetoInputState) {
    string message="Warning in DireMerging::mergeProcessUNLOPS: Input event";
    message+=" fails merging scale cut. Reject event.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Remove real emission events without underlying Born configuration from
  // the loop sample, since such states will be taken care of by tree-level
  // samples.
  if ( containsRealKin && !allowIncompleteReal
    //&& FullHistory.select(RN)->nClusterings() == 0 ) {
    //&& nSteps > 1 && picked->select(RN)->nClusterings(NULL) == 0 ) {
    && nSteps > 1 && picked == &FullHistory) {
    string message="Warning in DireMerging::mergeProcessUNLOPS: Input";
    message+=" real-correction event has no underlying Born. Reject.";
    infoPtr->errorMsg(message);
    return vetoEvent();
  }

  // Perform one reclustering for real emission kinematics, then apply
  // merging scale cut on underlying Born kinematics.
  if ( containsRealKin && enforceCutOnLHE) {
    //int nReclusterSave = mergingHooksPtr->nReclusterSave;
    mergingHooksPtr->nReclusterSave = 1;
    double tnowNew  = mergingHooksPtr->tmsNow( picked->state);
    bool doVetoClusteredState = enforceCutOnLHE
      && nSteps > 0 && nRequested > 0
      && tnowNew < tmsval;
    vetoCode = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->ktTypeSave=-99;
    if (vetoCode==-99) doVetoClusteredState = false;
    if (tnowNew <= 0. && vetoCode!=-99) {
      if (vetoCode == -1) doVetoClusteredState = enforceCutOnLHE
        && nSteps > 0 && nRequested > 0;
      else                doVetoClusteredState = false;
    }
    mergingHooksPtr->nReclusterSave = nReclusterSave;
    // Veto if underlying Born kinematics do not pass merging scale cut.
    if (doVetoClusteredState) {
      string message="Warning in DireMerging::mergeProcessUNLOPS: Clustered";
      message+=" input event fails merging scale cut. Reject event.";
      infoPtr->errorMsg(message);
      return vetoEvent();
    }
  }

  mergingHooksPtr->nReclusterSave
    = nReclusterSave;
  mergingHooksPtr->nHardNowSave
    = mergingHooksPtr->getNumberOfClusteringSteps(picked->state);

  // New UNLOPS strategy based on UN2LOPS.
  bool doUNLOPS2 = false;
  int depth = (!doUNLOPS2) ? -1 : ( (containsRealKin) ? nSteps-1 : nSteps);

  // Calculate reweighting, considering all paths.
  double wgtsum(0.);
  double lastp(0.);

  //double sumNow(0.), sumNowFull(0.);
  //double sumPathNow(0.), sumPathNowFull(0.);
  //int iBranch(0);

  for ( map<double, DireHistory*>::iterator
    it = picked->branches.begin();
    it != picked->branches.end(); ++it ) {

    // Double to access path.
    double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
    lastp = it->first;

    // Probability of path.
    double probPath = it->second->prodOfProbsFull/sumFullAll;

    picked->select(indexNow)->setSelectedChild();
    mergingHooksPtr->nMinMPI(
      mergingHooksPtr->getNumberOfClusteringSteps(picked->state));

    // Calculate weights.
    double w(0.);
    // Do LO or first part of NLO tree-level reweighting
    if( doUNLOPSTree ) {
      // Perform reweighting with Sudakov factors, save as ratios and
      // PDF ratio weights
      w = picked->weight_UNLOPS_TREE( trialPartonLevelPtr,
              mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
              mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
              indexNow, depth);
    } else if( doUNLOPSLoop ) {
      // Set event scales properly, reweight for new UNLOPS
      w = picked->weight_UNLOPS_LOOP( trialPartonLevelPtr,
              mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
              mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
              indexNow, depth);
    } else if( doUNLOPSSubtNLO ) {
      // Set event scales properly, reweight for new UNLOPS
      w = picked->weight_UNLOPS_SUBTNLO( trialPartonLevelPtr,
              mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
              mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
              indexNow, depth);
    } else if( doUNLOPSSubt ) {
      // Perform reweighting with Sudakov factors, save as ratios and
      // PDF ratio weights
      w = picked->weight_UNLOPS_SUBT( trialPartonLevelPtr,
              mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
              mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
              indexNow, depth);
    }
    wgtsum += probPath*w;

    //sumNow+=it->second->prodOfProbs;
    //sumNowFull+=it->second->prodOfProbsFull;
    //sumPathNow+=it->second->prodOfProbs/sumAll;
    //sumPathNowFull+=probPath;
    //cout << iBranch << ": sumAll=" << sumAll << "\t sumAllFull=" << sumFullAll
    //<< "\t sumNow=" << sumNow << "\t sumNowFull=" << sumNowFull
    //<< "\t probPath=" << probPath << "\t sumPath=" << sumPathNow
    //<< " sumPathFull=" << sumPathNowFull <<  endl;
    //iBranch++;

  }
  wgt = wgtsum;

  // For tree-level or subtractive sammples, rescale with k-Factor
  if ( doUNLOPSTree || doUNLOPSSubt ){
    // Find k-factor
    double kFactor = 1.;
    if ( nSteps > mergingHooksPtr->nMaxJetsNLO() )
      kFactor = mergingHooksPtr->kFactor( mergingHooksPtr->nMaxJetsNLO() );
    else kFactor = mergingHooksPtr->kFactor(nSteps);
    // For NLO merging, rescale CKKW-L weight with k-factor
    wgt *= kFactor;
  }

  // Ensure that merging weight is not counted twice.
  bool includeWGT = mergingHooksPtr->includeWGTinXSEC();

  // Save the weight of the event for histogramming.
  if (!includeWGT) mergingHooksPtr->setWeightCKKWL(unitarizationFactor()*wgt);

  // Check if we need to subtract the O(\alpha_s)-term. If the number
  // of additional partons is larger than the number of jets for
  // which loop matrix elements are available, do standard UMEPS.
  int nMaxNLO     = mergingHooksPtr->nMaxJetsNLO();
  bool doOASTree  = doUNLOPSTree && nSteps <= nMaxNLO;
  bool doOASSubt  = doUNLOPSSubt && nSteps <= nMaxNLO+1 && nSteps > 0;

  // Now begin NLO part for tree-level events
  if ( doOASTree || doOASSubt ) {

    // Decide on which order to expand to.
    int order = ( nSteps > 0 && nSteps <= nMaxNLO) ? 1 : -1;

    // Calculate reweighting, considering all paths.
    wgtsum = lastp = 0.;
    for ( map<double, DireHistory*>::iterator
      it = picked->branches.begin();
      it != picked->branches.end(); ++it ) {
      // Double to access path.
      double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
      lastp = it->first;
      // Probability of path.
      double probPath = it->second->prodOfProbsFull/sumFullAll;
      picked->select(indexNow)->setSelectedChild();

      mergingHooksPtr->nMinMPI(
        mergingHooksPtr->getNumberOfClusteringSteps(picked->state));

      // Calculate terms in expansion of the CKKW-L weight.
      double w = picked->weight_UNLOPS_CORRECTION( order,
        trialPartonLevelPtr, mergingHooksPtr->AlphaS_FSR(),
        mergingHooksPtr->AlphaS_ISR(), mergingHooksPtr->AlphaEM_FSR(),
        mergingHooksPtr->AlphaEM_ISR(), indexNow, rndmPtr );

      wgtsum += probPath*w;
    }
    wgtFIRST = wgtsum;

    // Set the subtractive weight to the value calculated so far
    if (!includeWGT)
      mergingHooksPtr->setWeightFIRST(unitarizationFactor()*wgtFIRST);
    else
      mergingHooksPtr->setWeightFIRST(0.);

    // Subtract the O(\alpha_s)-term from the CKKW-L weight
    // If PDF contributions have not been included, subtract these later
    // New UNLOPS based on UN2LOPS.
    if (doUNLOPS2 && order > -1) wgt = -wgt*(wgtFIRST-1.);
    else if (order > -1) wgt = wgt - wgtFIRST;

  }

  // Event with production scales set for further (trial) showering
  // and starting conditions for the shower.
  if (!doUNLOPSSubt && !doUNLOPSSubtNLO)
    picked->getStartingConditions(RN, process);
  // Do reclustering steps.
  else {
    int nPerformed = 0;
    picked->getFirstClusteredEventAboveTMS(RN, nRecluster, process,
      nPerformed, true );
  }

  // Set QCD 2->2 starting scale different from arbitrary scale in LHEF!
  // --> Set to minimal mT of partons.
  int nFinal = 0;
  double muf = process[0].e();
  for ( int i=0; i < process.size(); ++i )
  if ( process[i].isFinal()
    && (process[i].colType() != 0 || process[i].id() == 22 ) ) {
    nFinal++;
    muf = min( muf, abs(process[i].mT()) );
  }
  // For pure QCD dijet events (only!), set the process scale to the
  // transverse momentum of the outgoing partons.
  if ( nSteps == 0 && nFinal == 2
    && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
      || mergingHooksPtr->getProcessString().compare("pp>aj") == 0) )
    process.scale(muf);

  // Reset hard process candidates (changed after clustering a parton).
  mergingHooksPtr->storeHardProcessCandidates( process );

  // Check if resonance structure has been changed
  //  (e.g. because of clustering W/Z/gluino)
  vector <int> oldResonance;
  for ( int i=0; i < newProcess.size(); ++i )
    if ( newProcess[i].status() == 22 )
      oldResonance.push_back(newProcess[i].id());
  vector <int> newResonance;
  for ( int i=0; i < process.size(); ++i )
    if ( process[i].status() == 22 )
      newResonance.push_back(process[i].id());
  // Compare old and new resonances
  for ( int i=0; i < int(oldResonance.size()); ++i )
    for ( int j=0; j < int(newResonance.size()); ++j )
      if ( newResonance[j] == oldResonance[i] ) {
        oldResonance[i] = 99;
        break;
      }
  bool hasNewResonances = (newResonance.size() != oldResonance.size());
  for ( int i=0; i < int(oldResonance.size()); ++i )
    hasNewResonances = (oldResonance[i] != 99);

  // If necessary, reattach resonance decay products.
  if (!hasNewResonances) evtUtils->reattachDecaysAfterMerging(process);

  // Update the event weight.
  if (includeWGT) infoPtr->updateWeight(infoPtr->weight()/CONVERTMB2PB
                                       *unitarizationFactor()*wgt);

  // Allow merging hooks to remove emissions from now on.
  mergingHooksPtr->doIgnoreEmissions(false);

  // If no-emission probability is zero.
  if (allowReject && wgt == 0.) return 0;

  // If the resonance structure of the process has changed due to reclustering,
  // redo the resonance decays in Pythia::next()
  if (hasNewResonances) return 2;

  // Done
  return 1;

}

//--------------------------------------------------------------------------

// Function to set up all histories for an event.

bool DireMerging::generateHistories( const Event& process, bool orderedOnly) {

  // Input not valid.
  if (!validEvent(process)) {
    cout << "Warning in DireMerging::generateHistories: Input event "
         << "has invalid flavour or momentum structure, thus reject. " << endl;
    return false;
  }

  // Clear previous history.
  if (myHistory) delete myHistory;

  // For now, prefer construction of ordered histories.
  mergingHooksPtr->orderHistories(orderedOnly);

//?????????????? comment back in!!
  if (doMOPS) mergingHooksPtr->orderHistories(false);

  // For pp > h, allow cut on state, so that underlying processes
  // can be clustered to gg > h
  if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0)
    mergingHooksPtr->allowCutOnRecState(true);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);

nSteps++;
  mergingHooksPtr->nHardNowSave = nSteps;

  // Set dummy process scale.
  newProcess.scale(0.0);
  // Generate all histories
  myHistory = new DireHistory( nSteps, 0.0, newProcess, DireClustering(),
        mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
        trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true, false,
        1.0, 1.0, 1.0, 1.0, 0);
  // Project histories onto desired branches, e.g. only ordered paths.
  bool foundHistories = myHistory->projectOntoDesiredHistories();

  // Done
  return (doMOPS ? foundHistories : true);

}

//--------------------------------------------------------------------------

void DireMerging::tagHistories() {

  // Nothing to do if no histories were found.
  if (!myHistory || myHistory->branches.empty()) return;
  
  // Tag history paths as "signal" or "background"
  for ( map<double, DireHistory*>::iterator it = myHistory->branches.begin();
    it != myHistory->branches.end(); ++it )
    it->second->tagPath(it->second);

  double sumAll(0.), sumFullAll(0.), lastp(0.);
  for ( map<double, DireHistory*>::iterator it = myHistory->branches.begin();
    it != myHistory->branches.end(); ++it ) {
    sumAll     += it->second->prodOfProbs;
    sumFullAll += it->second->prodOfProbsFull;
  }

  // Sum up signal and background probabilities.
  vector<double> sumSignalProb(createvector<double>(0.)(0.)(0.)),
    sumBkgrndProb(createvector<double>(0.)(0.)(0.));

  for ( map<double, DireHistory*>::iterator it = myHistory->branches.begin();
    it != myHistory->branches.end(); ++it ) {

    if (it->second == myHistory) continue;

    // Get ME weight.
    double prob = it->second->prodOfProbsFull;
    // Reweight with Sudakovs, couplings and PDFs.
    double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
    lastp = it->first;
    myHistory->select(indexNow)->setSelectedChild();
    vector<double> w = myHistory->weightMEM( trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaEM_FSR(), indexNow);
    for (unsigned int i=0; i < w.size(); ++i) {
      //if (it->second->tag() == 0) sumSignalProb[i] += prob*w[i];
      //if (it->second->hasTag("higgs") ) sumSignalProb[i] += prob*w[i];
      //else                              sumBkgrndProb[i] += prob*w[i];
      totalProbSave[i] += prob*w[i];
      if (it->second->hasTag("higgs") ) signalProbSave["higgs"][i] += prob*w[i];
      else                              bkgrndProbSave["higgs"][i] += prob*w[i];
      if (it->second->hasTag("qed") )   signalProbSave["qed"][i]   += prob*w[i];
      else                              bkgrndProbSave["qed"][i]   += prob*w[i];
      if (it->second->hasTag("qcd") )   signalProbSave["qcd"][i]   += prob*w[i];
      else                              bkgrndProbSave["qcd"][i]   += prob*w[i];

      if (it->second->hasTag("higgs") ) signalProbSave["higgs-subt"][i] += prob*(w[i]-1.);
      else                              bkgrndProbSave["higgs-subt"][i] += prob*(w[i]-1.);
      if (it->second->hasTag("higgs") ) signalProbSave["higgs-nosud"][i] += prob;
      else                              bkgrndProbSave["higgs-nosud"][i] += prob;

      if (it->second->hasTag("bsm") )   signalProbSave["bsm"][i] += prob*w[i];
      else                              bkgrndProbSave["bsm"][i] += prob*w[i];
    }
  }

}

//--------------------------------------------------------------------------

double DireMerging::getPathIndex( bool useAll) {
  if (!useAll) return rndmPtr->flat();
  double sumAll(0.), sumFullAll(0.);
  return myHistory->getPathIndexRandom(rndmPtr, useAll,sumAll, sumFullAll);
}

//--------------------------------------------------------------------------

// Function to set up all histories for an event.

bool DireMerging::calculateSubtractions() {

  // Store shower subtractions.
  clearSubtractions();
  for ( int i = 0 ; i < int(myHistory->children.size()); ++i) {

    // Need to reattach resonance decays, if necessary.
    Event psppoint = myHistory->children[i]->state;
    // Reset hard process candidates (changed after clustering a parton).
    mergingHooksPtr->storeHardProcessCandidates( psppoint );

    // Check if resonance structure has been changed
    //  (e.g. because of clustering W/Z/gluino)
    vector <int> oldResonance;
    for ( int n=0; n < myHistory->state.size(); ++n )
      if ( myHistory->state[n].status() == 22 )
        oldResonance.push_back(myHistory->state[n].id());
    vector <int> newResonance;
    for ( int n=0; n < psppoint.size(); ++n )
      if ( psppoint[n].status() == 22 )
        newResonance.push_back(psppoint[n].id());
    // Compare old and new resonances
    for ( int n=0; n < int(oldResonance.size()); ++n )
      for ( int m=0; m < int(newResonance.size()); ++m )
        if ( newResonance[m] == oldResonance[n] ) {
          oldResonance[n] = 99;
          break;
        }
    bool hasNewResonances = (newResonance.size() != oldResonance.size());
    for ( int n=0; n < int(oldResonance.size()); ++n )
      hasNewResonances = (oldResonance[n] != 99);

    // If necessary, reattach resonance decay products.
    if (!hasNewResonances) evtUtils->reattachDecaysAfterMerging(psppoint);
    else {
      cout << "Warning in DireMerging::generateHistories: Resonance "
           << "structure changed due to clustering. Cannot attach decay "
           << "products correctly." << endl;
    }

    double prob = myHistory->children[i]->clusterProb;

    // Switch from 4pi to 8pi convention
    prob *= 2.;

    // Get clustering variables.
    int rad = myHistory->children[i]->clusterIn.radPos;
    int emt = myHistory->children[i]->clusterIn.emt1Pos;
    int rec = myHistory->children[i]->clusterIn.recPos;
    double z = kinRels->zEvol(myHistory->state[rad],
      myHistory->state[emt],
      myHistory->state[rec]);
    double t = kinRels->tEvol(myHistory->state[rad],
      myHistory->state[emt],
      myHistory->state[rec]);
    double m2dip = abs(-2.*myHistory->state[emt].p()*myHistory->state[rad].p()
                      -2.*myHistory->state[emt].p()*myHistory->state[rec].p()
                       +2.*myHistory->state[rad].p()*myHistory->state[rec].p());
    double kappa2 = t/m2dip;
    double xCS        = (z*(1-z) - kappa2) / (1 -z);

    // For II dipoles, scale with 1/xCS.
    prob *= 1./xCS;

    // Multiply with ME correction.
    prob *= myHistory->MECnum/myHistory->MECden;

    // Attach point to list of shower subtractions.
    appendSubtraction( prob, psppoint);

  }

  // Restore stored hard process candidates
  mergingHooksPtr->storeHardProcessCandidates(  myHistory->state );

  // Done
  return true;

}

//--------------------------------------------------------------------------

// Function to calulate the weights used for UNLOPS merging.

int DireMerging::calculateWeights( double RNpath, bool useAll ) {

  // Initialise which part of UNLOPS merging is applied.
  bool nloTilde         = settingsPtr->flag("Merging:doUNLOPSTilde");
  bool doUNLOPSTree     = settingsPtr->flag("Merging:doUNLOPSTree");
  bool doUNLOPSLoop     = settingsPtr->flag("Merging:doUNLOPSLoop");
  bool doUNLOPSSubt     = settingsPtr->flag("Merging:doUNLOPSSubt");
  bool doUNLOPSSubtNLO  = settingsPtr->flag("Merging:doUNLOPSSubtNLO");
  // Save number of looping steps
  mergingHooksPtr->nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  int nRecluster        = settingsPtr->mode("Merging:nRecluster");

  // Ensure that merging hooks to not remove emissions
  mergingHooksPtr->doIgnoreEmissions(true);
  mergingHooksPtr->setWeightCKKWL(1.);
  mergingHooksPtr->setWeightFIRST(0.);

  // Reset weight of the event.
  double wgt      = 1.;
  // Reset the O(alphaS)-term of the UMEPS weight.
  double wgtFIRST = 0.;
  mergingHooksPtr->muMI(-1.);

  // Check if event passes the merging scale cut.
  double tmsval  = mergingHooksPtr->tms();

  if (doMOPS) tmsval = 0.;

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(myHistory->state);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Get merging scale in current event.
  double tmsnow  = mergingHooksPtr->tmsNow( myHistory->state );
  int nRequested = mergingHooksPtr->nRequested();

  if (doMOPS && nSteps == 0) { return 1; }

  // Too few steps can be possible if a chain of resonance decays has been
  // removed. In this case, reject this event, since it will be handled in
  // lower-multiplicity samples.
  if (nSteps < nRequested) {
    string message="Warning in DireMerging::calculateWeights: Les Houches Event";
    message+=" after removing decay products does not contain enough partons.";
    infoPtr->errorMsg(message);
    if (allowReject) return -1;
  }

  // Reset the minimal tms value, if necessary.
  tmsNowMin = (nSteps == 0) ? 0. : min(tmsNowMin, tmsnow);

  // Do not apply cut if the configuration could not be projected onto an
  // underlying born configuration.
  bool applyCut = nSteps > 0 && myHistory->select(RNpath)->nClusterings(NULL) > 0;

  // Enfore merging scale cut if the event did not pass the merging scale
  // criterion.
  if ( enforceCutOnLHE && applyCut && nSteps == nRequested
    && tmsnow < tmsval && tmsval > 0.) {
    string message="Warning in DireMerging::calculateWeights: Les Houches";
    message+=" Event fails merging scale cut. Reject event.";
    infoPtr->errorMsg(message);
    if (allowReject) return -1;
  }

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  bool containsRealKin = nSteps > nRequested && nSteps > 0;
  if ( containsRealKin ) nRecluster += nSteps - nRequested;

  // Remove real emission events without underlying Born configuration from
  // the loop sample, since such states will be taken care of by tree-level
  // samples.
  if ( doUNLOPSLoop && containsRealKin && !allowIncompleteReal
    && myHistory->select(RNpath)->nClusterings(NULL) == 0 ) {
    if (allowReject) return -1;
  }

  // Discard if the state could not be reclustered to any state above TMS.
  int nPerformed = 0;
  if ( nSteps > 0 && !allowIncompleteReal
    && ( doUNLOPSSubt || doUNLOPSSubtNLO || containsRealKin )
    && !myHistory->getFirstClusteredEventAboveTMS( RNpath, nRecluster,
          myHistory->state, nPerformed, false ) ) {
    if (allowReject) return -1;
    //return -1;
  }

  // Check reclustering steps to correctly apply MPI.
  mergingHooksPtr->nMinMPI(nSteps - nPerformed);

  // Perform one reclustering for real emission kinematics, then apply
  // merging scale cut on underlying Born kinematics.
  if ( containsRealKin ) {
    Event dummy = Event();
    // Initialise temporary output of reclustering.
    dummy.clear();
    dummy.init( "(hard process-modified)", particleDataPtr );
    dummy.clear();
    // Recluster once.
    myHistory->getClusteredEvent( RNpath, nSteps, dummy );
    double tnowNew  = mergingHooksPtr->tmsNow( dummy );
    // Veto if underlying Born kinematics do not pass merging scale cut.
    if ( enforceCutOnLHE && nSteps > 0 && nRequested > 0
      && tnowNew < tmsval && tmsval > 0.) {
      string message="Warning in DireMerging::calculateWeights: Les Houches";
      message+=" Event fails merging scale cut. Reject event.";
      infoPtr->errorMsg(message);
      if (allowReject) return -1;
    }
  }

  // Setup to choose shower starting conditions randomly.
  double sumAll(0.), sumFullAll(0.);
  for ( map<double, DireHistory*>::iterator it = myHistory->branches.begin();
    it != myHistory->branches.end(); ++it ) {
    sumAll     += it->second->prodOfProbs;
    sumFullAll += it->second->prodOfProbsFull;
  }

  // Sum up signal and background probabilities.
  double sumSignalProb(0.), sumBkgrndProb(0.);

  // New UNLOPS strategy based on UN2LOPS.
  bool doUNLOPS2 = false;
  int depth = (!doUNLOPS2) ? -1 : ( (containsRealKin) ? nSteps-1 : nSteps);

  if (!useAll) {

  // Calculate weights.
  if (doMOPS)
    wgt = myHistory->weightMOPS( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaEM_FSR(),
            RNpath);
  else if ( mergingHooksPtr->doCKKWLMerging() )
    wgt = myHistory->weightTREE( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath);
  else if (  mergingHooksPtr->doUMEPSTreeSave )
    wgt = myHistory->weight_UMEPS_TREE( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath);
  else if ( mergingHooksPtr->doUMEPSSubtSave )
    wgt = myHistory->weight_UMEPS_SUBT( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath);
  else if ( mergingHooksPtr->doUNLOPSTreeSave )
    wgt = myHistory->weight_UNLOPS_TREE( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath, depth);
  else if ( mergingHooksPtr->doUNLOPSLoopSave )
    wgt = myHistory->weight_UNLOPS_LOOP( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath, depth);
  else if ( mergingHooksPtr->doUNLOPSSubtNLOSave )
    wgt = myHistory->weight_UNLOPS_SUBTNLO( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath, depth);
  else if ( mergingHooksPtr->doUNLOPSSubtSave )
    wgt = myHistory->weight_UNLOPS_SUBT( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            RNpath, depth);

  // For tree-level or subtractive sammples, rescale with k-Factor
  if ( doUNLOPSTree || doUNLOPSSubt ){
    // Find k-factor
    double kFactor = 1.;
    if ( nSteps > mergingHooksPtr->nMaxJetsNLO() )
      kFactor = mergingHooksPtr->kFactor( mergingHooksPtr->nMaxJetsNLO() );
    else kFactor = mergingHooksPtr->kFactor(nSteps);
    // For NLO merging, rescale CKKW-L weight with k-factor
    wgt *= (nRecluster == 2 && nloTilde) ? 1. : kFactor;
  }

  } else if (useAll && doMOPS) {
    // Calculate CKKWL reweighting for all paths.
    double wgtsum(0.);
    double lastp(0.);

    for ( map<double, DireHistory*>::iterator it = myHistory->branches.begin();
      it != myHistory->branches.end(); ++it ) {

      // Double to access path.
      double indexNow =  (lastp + 0.5*(it->first - lastp))/sumAll;
      lastp = it->first;

      // Probability of path.
      double probPath = it->second->prodOfProbsFull/sumFullAll;

      myHistory->select(indexNow)->setSelectedChild();

      // Calculate CKKWL weight:
      double w = myHistory->weightMOPS( trialPartonLevelPtr,
        mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaEM_FSR(),
        indexNow);

      wgtsum += probPath*w;

      // Sum up signal and background probabilities separately.
      if (it->second->hasTag("higgs"))
        sumSignalProb += it->second->prodOfProbsFull*w;
      else if (it->second->hasTag("bsm"))
        sumSignalProb += it->second->prodOfProbsFull*w;
      else
        sumBkgrndProb += it->second->prodOfProbsFull*w;

    }
    wgt = wgtsum;

  }

  mergingHooksPtr->setWeightCKKWL(wgt);

  // Check if we need to subtract the O(\alpha_s)-term. If the number
  // of additional partons is larger than the number of jets for
  // which loop matrix elements are available, do standard UMEPS.
  int nMaxNLO     = mergingHooksPtr->nMaxJetsNLO();
  bool doOASTree  = doUNLOPSTree && nSteps <= nMaxNLO;
  bool doOASSubt  = doUNLOPSSubt && nSteps <= nMaxNLO+1 && nSteps > 0;

  // Now begin NLO part for tree-level events
  if ( doOASTree || doOASSubt ) {

    // Decide on which order to expand to.
    int order = ( nSteps > 0 && nSteps <= nMaxNLO) ? 1 : -1;

    // Exclusive inputs:
    // Subtract only the O(\alpha_s^{n+0})-term from the tree-level
    // subtraction, if we're at the highest NLO multiplicity (nMaxNLO).
    if ( nloTilde && doUNLOPSSubt && nRecluster == 1
      && nSteps == nMaxNLO+1 ) order = 0;

    // Exclusive inputs:
    // Do not remove the O(as)-term if the number of reclusterings
    // exceeds the number of NLO jets, or if more clusterings have
    // been performed.
    if (nloTilde && doUNLOPSSubt && ( nSteps > nMaxNLO+1
      || (nSteps == nMaxNLO+1 && nPerformed != nRecluster) ))
        order = -1;

    // Calculate terms in expansion of the CKKW-L weight.
    wgtFIRST = myHistory->weight_UNLOPS_CORRECTION( order,
      trialPartonLevelPtr, mergingHooksPtr->AlphaS_FSR(),
      mergingHooksPtr->AlphaS_ISR(), mergingHooksPtr->AlphaEM_FSR(),
      mergingHooksPtr->AlphaEM_ISR(), RNpath, rndmPtr );

    // Exclusive inputs:
    // Subtract the O(\alpha_s^{n+1})-term from the tree-level
    // subtraction, not the O(\alpha_s^{n+0})-terms.
    if ( nloTilde && doUNLOPSSubt && nRecluster == 1
      && nPerformed == nRecluster && nSteps <= nMaxNLO )
      wgtFIRST += 1.;

    // Subtract the O(\alpha_s)-term from the CKKW-L weight
    // If PDF contributions have not been included, subtract these later
    // New UNLOPS based on UN2LOPS.
    if (doUNLOPS2 && order > -1) wgt = -wgt*(wgtFIRST-1.);
    else if (order > -1) wgt = wgt - wgtFIRST;

  }

  // If no-emission probability is zero.
  if (allowReject && wgt == 0.) return 0;

  // Done
  return 1;

}

//--------------------------------------------------------------------------

// Function to perform UNLOPS merging on this event.

int DireMerging::getStartingConditions( double RNpath, Event& process) {

  // Initialise which part of UNLOPS merging is applied.
  bool doUNLOPSSubt     = settingsPtr->flag("Merging:doUNLOPSSubt");
  bool doUNLOPSSubtNLO  = settingsPtr->flag("Merging:doUNLOPSSubtNLO");
  // Save number of clustering steps
  mergingHooksPtr->nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  int nRecluster        = settingsPtr->mode("Merging:nRecluster");

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(myHistory->state);
  mergingHooksPtr->nHardNowSave = nSteps;
  int nRequested = mergingHooksPtr->nRequested();

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  bool containsRealKin = nSteps > nRequested && nSteps > 0;
  if ( containsRealKin ) nRecluster += nSteps - nRequested;

  // Event with production scales set for further (trial) showering
  // and starting conditions for the shower.
  int nPerformed = 0;
  if (!doUNLOPSSubt && !doUNLOPSSubtNLO && !containsRealKin )
    myHistory->getStartingConditions(RNpath, process);
  // Do reclustering steps.
  else myHistory->getFirstClusteredEventAboveTMS( RNpath, nRecluster, process,
    nPerformed, true );

  // Set QCD 2->2 starting scale different from arbitrary scale in LHEF!
  // --> Set to minimal mT of partons.
  int nFinal = 0;
  double muf = process[0].e();
  for ( int i=0; i < process.size(); ++i )
  if ( process[i].isFinal()
    && (process[i].colType() != 0 || process[i].id() == 22 ) ) {
    nFinal++;
    muf = min( muf, abs(process[i].mT()) );
  }
  // For pure QCD dijet events (only!), set the process scale to the
  // transverse momentum of the outgoing partons.
  if ( nSteps == 0 && nFinal == 2
    && ( mergingHooksPtr->getProcessString().compare("pp>jj") == 0
      || mergingHooksPtr->getProcessString().compare("pp>aj") == 0) )
    process.scale(muf);

  // Reset hard process candidates (changed after clustering a parton).
  mergingHooksPtr->storeHardProcessCandidates( process );

  // Check if resonance structure has been changed
  //  (e.g. because of clustering W/Z/gluino)
  vector <int> oldResonance;
  for ( int i=0; i < myHistory->state.size(); ++i )
    if ( myHistory->state[i].status() == 22 )
      oldResonance.push_back(myHistory->state[i].id());
  vector <int> newResonance;
  for ( int i=0; i < process.size(); ++i )
    if ( process[i].status() == 22 )
      newResonance.push_back(process[i].id());
  // Compare old and new resonances
  for ( int i=0; i < int(oldResonance.size()); ++i )
    for ( int j=0; j < int(newResonance.size()); ++j )
      if ( newResonance[j] == oldResonance[i] ) {
        oldResonance[i] = 99;
        break;
      }
  bool hasNewResonances = (newResonance.size() != oldResonance.size());
  for ( int i=0; i < int(oldResonance.size()); ++i )
    hasNewResonances = (oldResonance[i] != 99);

  // If necessary, reattach resonance decay products.
  if (!hasNewResonances) evtUtils->reattachDecaysAfterMerging(process);

  // Allow merging hooks to remove emissions from now on.
  mergingHooksPtr->doIgnoreEmissions(false);

  // If the resonance structure of the process has changed due to reclustering,
  // redo the resonance decays in Pythia::next()
  if (hasNewResonances) return 2;

  // Done
  return 1;

}

//--------------------------------------------------------------------------

// Function to apply the merging scale cut on an input event.

bool DireMerging::cutOnProcess( Event& process) {

  // No cuts for MOPS.
  if (doMOPS) return false;
  if (doN3LO()) {
    tomteInfo.sumExternalWeights += infoPtr->weight();
    if ( cutForN3LO(process) != 1) return true;
    tomteInfo.sumExternalWeightsPassCut += infoPtr->weight();
    return false;
  }

  bool doUMEPS      = settingsPtr->flag("Merging:doUMEPSTree")
                   || settingsPtr->flag("Merging:doUMEPSSubt");
  //bool doUNLOPSLoop = settingsPtr->flag("Merging:doUNLOPSLoop")
  //                 || settingsPtr->flag("Merging:doUNLOPSSubtNLO");
  // Save number of clustering steps
  int nReclusterSave = settingsPtr->mode("Merging:nRecluster");
  mergingHooksPtr->nReclusterSave = nReclusterSave;
  if (doUMEPS) mergingHooksPtr->nReclusterSave = 0;

  // For now, prefer construction of ordered histories.
  //mergingHooksPtr->orderHistories(true);
  //if (doUNLOPSLoop) mergingHooksPtr->orderHistories(false);
  mergingHooksPtr->orderHistories(false);
  // For pp > h, allow cut on state, so that underlying processes
  // can be clustered to gg > h
  if ( mergingHooksPtr->getProcessString().compare("pp>h") == 0)
    mergingHooksPtr->allowCutOnRecState(true);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Too few steps can be possible if a chain of resonance decays has been
  // removed. In this case, reject this event, since it will be handled in
  // lower-multiplicity samples.
  int nRequested = mergingHooksPtr->nRequested();
  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  bool containsRealKin = nSteps > nRequested && nSteps > 0;

  // Check if event passes the merging scale cut.
  double tmsval  = mergingHooksPtr->tms();
  // Get merging scale in current event.
  double tmsnow  = !containsRealKin ? mergingHooksPtr->tmsNow(newProcess) : 0.; 
  int vetoCode = mergingHooksPtr->ktTypeSave;
  mergingHooksPtr->ktTypeSave=-99;

  if (nSteps < nRequested) return true;

  // Reset the minimal tms value, if necessary.
  tmsNowMin = (nSteps == 0) ? 0. : min(tmsNowMin, tmsnow);

  // Set dummy process scale.
  newProcess.scale(0.0);
  // Generate all histories
  DireHistory FullHistory( nSteps, 0.0, newProcess, DireClustering(),
    mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
    trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
    containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);

  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = &FullHistory;
  if ( containsRealKin && !FullHistory.children.empty()) {
    FullHistory.projectOntoDesiredHistories();
    picked = FullHistory.getDemocraticLeaf(rndmPtr).second;
    if (picked==nullptr) return true;
    picked->rescaleProbs();
    picked->mother = 0;
    picked->projectOntoDesiredHistories();
  } else {
    // Project histories onto desired branches, e.g. only ordered paths.
    picked->projectOntoDesiredHistories();
  }

  // Setup to choose shower starting conditions randomly.
  double sumAll(0.), sumFullAll(0.);
  double RN = picked->getPathIndexRandom(rndmPtr, true, sumAll,
     sumFullAll);
  // Now enfore merging scale cut if the input event did not pass the merging
  // scale. Note: Do not apply cut if the configuration could not be projected
  // onto an underlying born configuration.
  bool doVetoInputState = !containsRealKin
   && nSteps > 0
   && FullHistory.select(RN)->nClusterings(NULL) > 0
   && nSteps == nRequested
   && tmsnow < tmsval;
  // If merging scale is not well-defined, check veto code instead!
  if (tmsnow <= 0. && vetoCode!=-99) {
    if (vetoCode == -1) doVetoInputState = !containsRealKin
      && nSteps > 0
      && FullHistory.select(RN)->nClusterings(NULL) > 0
      && nSteps == nRequested;
    else                doVetoInputState = false;
  }

  if (doVetoInputState) {
    string message="Warning in DireMerging::cutOnProcess: Input event";
    message+=" fails merging scale cut. Reject event.";
    infoPtr->errorMsg(message);
    return true;
  }

  // Remove real emission events without underlying Born configuration from
  // the loop sample, since such states will be taken care of by tree-level
  // samples.
  if ( containsRealKin && !allowIncompleteReal
    //&& nSteps > 1 && picked->select(RN)->nClusterings(NULL) == 0) {
    && nSteps > 1 && picked == &FullHistory) {
    string message="Warning in DireMerging::cutOnProcess:";
    message+=" real-correction event has no underlying Born. Reject.";
    infoPtr->errorMsg(message);
    return true;
  }

  // Perform one reclustering for real emission kinematics, then apply
  // merging scale cut on underlying Born kinematics.
  if (containsRealKin) {
    mergingHooksPtr->nReclusterSave = 1;
    double tnowNew  = mergingHooksPtr->tmsNow( picked->state);
    bool doVetoClusteredState = nSteps > 0 && nRequested > 0
      && tnowNew < tmsval;
    vetoCode = mergingHooksPtr->ktTypeSave;
    mergingHooksPtr->ktTypeSave=-99;
    if (vetoCode==-99) doVetoClusteredState = false;
    if (tnowNew <= 0. && vetoCode!=-99) {
      if (vetoCode == -1) doVetoClusteredState = nSteps > 0 && nRequested > 0;
      else                doVetoClusteredState = false;
    }
    mergingHooksPtr->nReclusterSave = nReclusterSave;
    // Veto if underlying Born kinematics do not pass merging scale cut.
    if (doVetoClusteredState) {
      string message="Warning in DireMerging::cutOnProcess: Clustered";
      message+=" input event fails merging scale cut. Reject event.";
      infoPtr->errorMsg(message);
      return true;
    }
  }

  mergingHooksPtr->nReclusterSave = nReclusterSave;

  // Done if only interested in cross section estimate after cuts.
  return false;

}

//--------------------------------------------------------------------------

vector<double> DireMerging::reweight(const Event& state) {

  double ecm = 91.2;
  double ecm2 = ecm*ecm;
  Vec4 pa(0.,0., 0.5*ecm,0.5*ecm);
  Vec4 pb(0.,0.,-0.5*ecm,0.5*ecm);

  vector<Vec4> quarks, antiquarks, gluons;

  for(int i = 0; i < state.size(); ++i) {
    if (!state[i].isFinal()) continue;
    if (state[i].id()==21) {
    vector<Vec4>::iterator it = gluons.begin();
    if ((int)gluons.size()>0 && state[i].e() > gluons.back().e())
      gluons.insert ( it , state[i].p());
    else
      gluons.push_back(state[i].p());
    }
    if (state[i].id()>0 && state[i].idAbs()<10)
      quarks.push_back(state[i].p());
    if (state[i].id()<0 && state[i].idAbs()<10)
      antiquarks.push_back(state[i].p());
  }  

  double sqe = 0., /*sqp = 0.,*/ saqe = 0./*, saqp = 0.*/;
  if (quarks.size()>0) sqe = 2.*quarks[0]*pa / ecm2;
  //if (quarks.size()>0) sqp = 2.*quarks[0]*pb / ecm2;
  if (antiquarks.size()>0) saqe = 2.*antiquarks[0]*pa / ecm2;
  //if (antiquarks.size()>0) saqp = 2.*antiquarks[0]*pb / ecm2;

  double sqg1 = 0., sqg2 = 0., /*sqg3 = 0.,*/ sg1g2 = 0.,
    /*sg1g3 = 0., sg2g3 = 0.,*/
    saqg1 = 0., saqg2 = 0., /*saqg3 = 0.,*/ sqaq = 0.;
  if (quarks.size()>0 && (int)gluons.size() > 0)
    sqg1 = 2.*quarks[0]*gluons[0] / ecm2;
  if (quarks.size()>0 && (int)gluons.size() > 1)
    sqg2 = 2.*quarks[0]*gluons[1] / ecm2;
  //if (quarks.size()>0 && (int)gluons.size() > 2) sqg3 = 2.*quarks[0]*gluons[2] / ecm2;
  if (antiquarks.size()>0 && (int)gluons.size() > 0)
    saqg1 = 2.*antiquarks[0]*gluons[0] / ecm2;
  if (antiquarks.size()>0 && (int)gluons.size() > 1)
    saqg2 = 2.*antiquarks[0]*gluons[1] / ecm2;
  //if (antiquarks.size()>0 && (int)gluons.size() > 2) saqg3 = 2.*antiquarks[0]*gluons[2] / ecm2;
  if ((int)gluons.size() > 1) sg1g2 = 2.*gluons[0]*gluons[1] / ecm2;
  //if ((int)gluons.size() > 2) {
  //  sg1g3 = 2.*gluons[0]*gluons[2] / ecm2;
  //  sg2g3 = 2.*gluons[1]*gluons[2] / ecm2;
  //}

  double a2qaq = -50., a2qg1 = 10., a2qg2 = 50., a2aqg1 = 10., a2aqg2 = 50., a2g1g2 = 100.;
  double a1qaq = 50., a1qg1 = 100., a1aqg1 = 100., b1qaq = 0., b1qg1 = -7000., b1aqg1 = -7000.;
  double a0qe = 2., a0aqe = 10., b0qe = -100., b0aqe = -100., c0qe = 10000., c0aqe = 10000.;

  double asOpi = 0.118/(2.*M_PI);
  vector<double> w(5,1.);
  w[0] = 1.;
  w[1] = 0.;
  w[2] = 0.;
  w[3] = 0.;

  int nRequested = mergingHooksPtr->nRequested();
  if (nRequested==2 && (int)gluons.size()==2) {
    w[0] = 1.;
    w[1] = asOpi*( a2qaq*sqaq + a2qg1*sqg1 + a2qg2*sqg2 + a2aqg1*saqg1 + a2aqg2*saqg2 + a2g1g2*sg1g2);
  }
  if (nRequested==1 && (int)gluons.size()==1) {
    w[0] = 1.;
    w[1] = asOpi*( a1qaq*sqaq + a1qg1*sqg1 + a1aqg1*saqg1);
    w[2] = asOpi*asOpi*( b1qaq*sqaq + b1qg1*sqg1 + b1aqg1*saqg1);
  }
  if (nRequested==0 && (int)gluons.size()==0) {
    w[0] = 1.;
    w[1] = asOpi*( a0qe*sqe + a0aqe*saqe);
    w[2] = asOpi*asOpi*( b0qe*log(sqe)*(1-sqe) + b0aqe*log(saqe)*(1-saqe));
    w[3] = asOpi*asOpi*asOpi*( c0qe*cos(sqe*2.*M_PI)*sqe + c0aqe*sin(saqe*2.*M_PI)*saqe);
  }

  w[4] = w[0] + w[1] + w[2] + w[3];

  return w;

}

//--------------------------------------------------------------------------

int DireMerging::checkBiasCorrectionBasic( Event& process) {

  double wgt = 1.;

  // Do not prefer ordered histories.
  //mergingHooksPtr->orderHistories(false);
  mergingHooksPtr->orderHistories(true);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  int nRequested = mergingHooksPtr->nRequested();
  bool containsRealKin = nSteps > nRequested && nSteps > 0;

  string scaleString = infoPtr->getEventAttribute("clusteringScale");
  double sc  = 0.;
  if (!scaleString.empty()) sc = atof(scaleString.c_str());
  // Set dummy process scale.
  newProcess.scale(sc);
  // Generate all histories
  DireHistory FullHistory( nSteps, sc, newProcess, DireClustering(),
     mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
     trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
     containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);
  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = &FullHistory;
  pair<double,DireHistory*> ppp;
  //int nClustering = 1;
  int nClustering = settingsPtr->mode("Merging:nRecluster");

  // Get the event weight.
  string old_weight = infoPtr->getEventAttribute("weight");
  double evtWeight  = (old_weight.empty())
           ? infoPtr->weight()/CONVERTMB2PB
           : atof(old_weight.c_str());
  
  /*// Discard any events for which not all paths are above the cut-off.
  if (nSteps > 0 && !picked->allPathsAboveTMS()) {
    //cout << "State fails cut at line " << __LINE__ << endl;
    return vetoEvent();
  }*/

  if ( nClustering > 0 && !picked->children.empty()) {

    // Need this to fill good branches.
    if ( evtWeight != 0.
      && !picked->projectOntoDesiredHistories()) {
      //evtWeight = 0.;
      return vetoEvent();
    }
    if ( evtWeight != 0.
      && nSteps > 0 && picked->goodBranches.empty()){
      //eventWeight = 0.;
      return vetoEvent();
    }

    // Shower-like clustering
    if (evtWeight != 0. && clusterMode==1) {

      DireHistory* starting_leaf = 0;
      double selRate = 1.;
      if (nClustering>=1) {
        pair<double,DireHistory*> p1,p2,p3;
        // Already applies probability rescaling
        p1 = picked->getProbabilisticFullLeaf(rndmPtr, starting_leaf);
        //p1= picked->getProbabilisticLeaf(rndmPtr);
        if (p1.second == nullptr) return vetoEvent();
        //if (p1.second == nullptr) eventWeight = 0.;
        selRate *= 1./p1.first;
        if (nClustering>=2) {
          p2 = p1.second->getNextProbabilisticFullLeaf(starting_leaf);
          selRate *= 1./p2.first;
        }
        if (nClustering>=3) {
          p3 = p2.second->getNextProbabilisticFullLeaf(starting_leaf);
          selRate *= 1./p3.first;
        }

        if (correctionMode==3)
          selRate *= picked->getSelectionRateDemocratic(p1.second);
        else
          selRate *= picked->getSelectionRateProbabilistic(p1.second);
        picked = p1.second;

        if (nClustering>=2) {
          picked->rescaleProbs();
          picked->mother = 0;
          selRate
            *= picked->getSelectionRateProbabilistic(p2.second);
          // Rate correction to democratic clustering not implemented.
          picked = p2.second;
        }

        if (nClustering>=3) {
          picked->rescaleProbs();
          picked->mother = 0;
          selRate
            *= picked->getSelectionRateProbabilistic(p3.second);
          // Rate correction to democratic clustering not implemented.
          picked = p3.second;
        }

        // Ignore bias correction factor for pure PS clustering
        if (correctionMode==0) selRate = 1.;

        wgt *= selRate;

      }

    // Probabilistic clustering
    } else if (evtWeight != 0. && clusterMode==2) {

      double selRate = 1.;
      if (nClustering>=1) {
        ppp = picked->getProbabilisticLeaf(rndmPtr);
        if (ppp.second == nullptr) return vetoEvent();
        //if (ppp.second == nullptr) evtWeight = 0.;
        if (correctionMode==3) {
          selRate *= 1./ppp.first;
          double demoRate
            = picked->getSelectionRateDemocratic(ppp.second);
          selRate *= demoRate;
        }
        ppp.second->extractBranches(picked->branches);
        picked = ppp.second;
        picked->rescaleProbs();
        picked->mother = 0;
      }

      if (nClustering>=2) {
        ppp = picked->getProbabilisticLeaf(rndmPtr);
        ppp.second->extractBranches(picked->branches);
        picked = ppp.second;
        picked->rescaleProbs();
        picked->mother = 0;
        // Rate correction to democratic clustering not implemented.
      }

      if (nClustering>=3) {
        ppp = picked->getProbabilisticLeaf(rndmPtr);
        ppp.second->extractBranches(picked->branches);
        picked = ppp.second;
        picked->rescaleProbs();
        picked->mother = 0;
        // Rate correction to democratic clustering not implemented.
      }

      wgt *= selRate;

    // Democratic clustering.
    } else if (evtWeight != 0.) {
      if (nClustering>=1) {
        ppp = picked->getDemocraticLeaf(rndmPtr);
        if (ppp.second == nullptr) return vetoEvent();
        //if (ppp.second == nullptr) evtWeight = 0.;
        picked = ppp.second;
        picked->mother = 0;
      }
      // Democratic clustering for nClustering>1 not implemented.
    }

  } else {
    // Project histories onto desired branches, e.g. only ordered paths.
    picked->projectOntoDesiredHistories();
    if ( evtWeight != 0.
      && nSteps > 0 && picked->goodBranches.empty()) {
      //eventWeight = 0.;
      return vetoEvent();
    }
  }

  // Set process to (potentially) new state.
  process = picked->state;

  //// Update the event weight.
  //double cutEfficiency
  //  = tomteInfo.sumExternalWeightsPassCut
  //  / tomteInfo.sumExternalWeights;
  //evtWeight *= cutEfficiency;

  infoPtr->updateWeight(evtWeight*wgt);

  // Done
  return 1;

}

//--------------------------------------------------------------------------

int DireMerging::checkBiasCorrectionIncludingSudakov(Event& process) {

  double wgt = 1.;
  string scaleString = infoPtr->getEventAttribute("clusteringScale");
  double scaleValue  = 0.;
  if (!scaleString.empty()) scaleValue = atof(scaleString.c_str());

  // Do not prefer ordered histories.
  //mergingHooksPtr->orderHistories(false);
  mergingHooksPtr->orderHistories(true);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  int nRequested = mergingHooksPtr->nRequested();
  bool containsRealKin = nSteps > nRequested && nSteps > 0;

  // Set dummy process scale.
  newProcess.scale(scaleValue);
  // Generate all histories
  DireHistory FullHistory( nSteps, scaleValue, newProcess, DireClustering(),
     mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
     trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
     containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);

  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = &FullHistory;
  DireHistory* starting_leaf = 0;
  pair<double,DireHistory*> ppp;
  int nClustering = 1;

  // Discard any events for which not all paths are above the cut-off.
  if (nSteps > 0 && !picked->allPathsAboveTMS()) {
    //cout << "State fails cut at line " << __LINE__ << endl;
    return vetoEvent();
  }

  double wmatch = 1.;

  if ( containsRealKin && !picked->children.empty()) {

    double selClusteringRate = 1.;
    // Need this to fill good branches.
    if (!picked->projectOntoDesiredHistories())
      return vetoEvent();

    if (nSteps > 0 && picked->goodBranches.empty())
      return vetoEvent();

    if (nClustering>=1) {
      pair<double,DireHistory*> p1, p2;
      // Pick a leaf
      p1 = picked->getProbabilisticFullLeaf(rndmPtr, starting_leaf);

      // Replace selection rate with single-clustering probabilistic rate.
      selClusteringRate *= 1./p1.first;
      selClusteringRate
        *= picked->getSelectionRateProbabilistic(p1.second);

      if (nClustering>=2) {
        DireHistory* mom = p1.second->mother;
        p1.second->mother = 0;
        p2 = p1.second->getNextProbabilisticFullLeaf(starting_leaf);
        p1.second->mother = mom;
        selClusteringRate *= 1./p2.first;
      }

      // Select the new leaf
      picked = p1.second;

      // Construct rate to pick this particular path to (n-1)-body state.
      picked->rescaleProbs();
      picked->extractBranches(FullHistory.branches);

      if (nClustering>=2) {
        selClusteringRate
          *= picked->getSelectionRateProbabilistic(p2.second);
        picked = p2.second;
        picked->rescaleProbs();
        picked->extractBranches(p1.second->branches);
      }

      // Done. 
      wgt *= selClusteringRate;

    }

    picked->mother = 0;

  } else {
    // Project histories onto desired branches, e.g. only ordered paths.
    picked->projectOntoDesiredHistories();
    if (nSteps > 0 && picked->goodBranches.empty())
      return vetoEvent();
  }

  double pathIndex(0.);
  if (starting_leaf) {
    double lastp(0.);
    double sumAll(0.);
    for ( map<double, DireHistory*>::iterator
      it = picked->branches.begin();
      it != picked->branches.end(); ++it )
      sumAll     += it->second->prodOfProbs;
    for ( map<double, DireHistory*>::iterator
      it = picked->branches.begin();
      it != picked->branches.end(); ++it ) {
      pathIndex =  (lastp + 0.5*(it->first - lastp))/sumAll;
      lastp = it->first;
      if (it->second == starting_leaf) break;
    }
  } else
    pathIndex = rndmPtr->flat();

  // Set process to (potentially) new state.
  process = picked->state;

  wmatch = picked->weightTREE( trialPartonLevelPtr,
            mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
            mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
            pathIndex);

  // Update the event weight.
  infoPtr->updateWeight(infoPtr->weight()/CONVERTMB2PB*wgt*wmatch);

  // Done
  return 1;

}

//--------------------------------------------------------------------------

int DireMerging::makeToyCalculation( Event& process) {

  vector<double> wgt(5,0.);
  wgt[0] = 1.;
  wgt[1] = 0.;
  wgt[2] = 0.;
  wgt[3] = 0.;
  wgt[4] = 1.;

  string old_nsamples = infoPtr->getEventAttribute("nsamples");

  int nsamples = settingsPtr->mode("Main:numberOfSubruns");

  string att = infoPtr->getEventAttribute("eventType");
  if(att.empty()) wgt = reweight(process);

  string scaleString = infoPtr->getEventAttribute("clusteringScale");
  double scaleValue  = 0.;
  if (!scaleString.empty()) scaleValue = atof(scaleString.c_str());

  ostringstream vstream;
  string old_wtorig = infoPtr->getEventAttribute("original_weight");
  double wtorig = infoPtr->weight() /*/neve*/;
  vstream.str(""); vstream << wtorig;
  if (old_wtorig.empty())
    infoPtr->setEventAttribute("original_weight", vstream.str());

  string old_weight = infoPtr->getEventAttribute("weight");
  double evtWeight  = (old_weight.empty())
           ? infoPtr->weight()
           : atof(old_weight.c_str());

  double cutEfficiency
    = tomteInfo.sumExternalWeightsPassCut
    / tomteInfo.sumExternalWeights;
  evtWeight *= cutEfficiency;

  double neve = double(settingsPtr->mode("Main:numberOfEvents"));
  vstream.str(""); vstream << double(neve);
  infoPtr->setEventAttribute("neve", vstream.str());

  // Do not prefer ordered histories.
  //mergingHooksPtr->orderHistories(false);
  mergingHooksPtr->orderHistories(true);

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  int nRequested = mergingHooksPtr->nRequested();

  vector<Vec4> quarks, antiquarks, gluons;
  for(int i = 0; i < newProcess.size(); ++i) {
    if (!newProcess[i].isFinal()) continue;
    if (newProcess[i].id()==21) {
    vector<Vec4>::iterator it = gluons.begin();
    if (gluons.size()>0 && newProcess[i].e() > gluons.back().e())
      gluons.insert ( it , newProcess[i].p());
    else gluons.push_back(newProcess[i].p());
    }
    if (newProcess[i].id()>0 && newProcess[i].idAbs()<10) quarks.push_back(newProcess[i].p());
    if (newProcess[i].id()<0 && newProcess[i].idAbs()<10) antiquarks.push_back(newProcess[i].p());
  }  

  ostringstream wval[4];
  vstream.str("");
  wval[0] << scientific << setprecision(6);
  wval[1] << scientific << setprecision(6);
  wval[2] << scientific << setprecision(6);
  wval[3] << scientific << setprecision(6);
  wval[0] << wgt[0]*evtWeight;
  wval[1] << wgt[1]*evtWeight;
  wval[2] << wgt[2]*evtWeight;
  wval[3] << wgt[3]*evtWeight;
  string wname[4];
  wname[0] = "n/a";
  wname[1] = "n/a";
  wname[2] = "n/a";
  wname[3] = "n/a";

//  if (!att.empty()) vstream << att << "_";

  if (nRequested == 0 && (int)gluons.size()==nRequested) {
    vstream << "n3lo_2";
    wname[0] = "wfo_0_2";
    wname[1] = "wfo_1_2";
    wname[2] = "wfo_2_2";
    wname[3] = "wfo_3_2";
  }
  if (nRequested == 1 && (int)gluons.size()==nRequested) {
    vstream << "n2lo_3";
    wname[0] = "wfo_1_3";
    wname[1] = "wfo_2_3";
    wname[2] = "wfo_3_3";
    wname[3] = "n/a";
  }
  if (nRequested == 2 && (int)gluons.size()==nRequested) {
    vstream << "n1lo_4";
    wname[0] = "wfo_2_4";
    wname[1] = "wfo_3_4";
    wname[2] = "n/a";
    wname[3] = "n/a";
  }
  if (nRequested == 3 && (int)gluons.size()==nRequested) {
    vstream << "n0lo_5";
    wname[0] = "wfo_3_5";
    wname[1] = "n/a";
    wname[2] = "n/a";
    wname[3] = "n/a";
    nsamples = 1;
  }

  if (!old_nsamples.empty()) nsamples *= atoi(old_nsamples.c_str());
  ostringstream new_nsamples; new_nsamples << nsamples;
  infoPtr->setEventAttribute("nsamples",new_nsamples.str());

  // Calculate number of clustering steps
  int nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = nSteps;

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  bool containsRealKin = nSteps > nRequested && nSteps > 0;

  // Set dummy process scale.
  //newProcess.scale(0.0);
  newProcess.scale(scaleValue);
  // Generate all histories
  //DireHistory FullHistory( nSteps, 0.0, newProcess, DireClustering(),
  DireHistory FullHistory( nSteps, scaleValue, newProcess, DireClustering(),
     mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
     trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
     containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);

  double clusteringScale = 0.;
  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = &FullHistory;
  pair<double,DireHistory*> ppp;
  int nClustering = 1;

  // Discard any events for which not all paths are above the cut-off.
  if (tomteInfo.nSteps > 0 && !picked->allPathsAboveTMS()) {
    //cout << __LINE__ << " " << att << " veto " << endl; 
    return vetoEvent();
  }

  double sign = 1.;

  if ( containsRealKin && !picked->children.empty()) {

    sign = -1.;

    // Need this to fill good branches.
    if (!picked->projectOntoDesiredHistories()) {
      return vetoEvent();
    }

    if (nSteps > 0 && picked->goodBranches.empty()) {
      return vetoEvent();
    }

    if (nClustering>=1) {
      ppp = FullHistory.getProbabilisticLeaf(rndmPtr);
      ppp.second->extractBranches(picked->branches);
      picked = ppp.second;
      picked->rescaleProbs();
      picked->mother = 0;
    }

    if (nClustering>=2) {
      ppp = picked->getProbabilisticLeaf(rndmPtr);
      ppp.second->extractBranches(picked->branches);
      picked = ppp.second;
      picked->rescaleProbs();
      picked->mother = 0;
    }

    if (nClustering>=3) {
      ppp = picked->getProbabilisticLeaf(rndmPtr);
      ppp.second->extractBranches(picked->branches);
      picked = ppp.second;
      picked->rescaleProbs();
      picked->mother = 0;
    }

    clusteringScale = picked->scale;
  
    /*cout << "begin check cut again " << clusteringScale << endl;
    picked->state.list();
    cout << "print leaves at " << __LINE__ << " " << picked->paths.size() << endl;
    picked->printLeaves();
    picked->allPathsAboveTMS();
    cout << "end check cut again" << endl;*/



  } else {
    // Project histories onto desired branches, e.g. only ordered paths.
    picked->projectOntoDesiredHistories();
    if (nSteps > 0 && picked->goodBranches.empty()) {
      return vetoEvent();
    }
  }

  if (nRequested == 0 && (int)gluons.size()==nRequested+1) {
    vstream << "n3lo_3_2";
    wval[0].str("");
    wval[0] << 0.0;

    string wfo_1_3 = infoPtr->getEventAttribute("wfo_1_3");
    wname[1] = "wfo_1_2";
    wval[1].str("");
    if (wfo_1_3.empty()) wval[1] << 0.0;
    else wval[1] << sign*atof(wfo_1_3.c_str());
    infoPtr->removeEventAttribute("wfo_1_3");

    wname[2] = "wfo_2_2";
    string wfo_2_3 = infoPtr->getEventAttribute("wfo_2_3");
    wval[2].str("");
    if (wfo_2_3.empty()) wval[2] << 0.0;
    else wval[2] << sign*atof(wfo_2_3.c_str());
    infoPtr->removeEventAttribute("wfo_2_3");

    wname[3] = "wfo_3_2";
    string wfo_3_3 = infoPtr->getEventAttribute("wfo_3_3");
    wval[3].str("");
    if (wfo_3_3.empty()) wval[3] << 0.0;
    else wval[3] << sign*atof(wfo_3_3.c_str());
    infoPtr->removeEventAttribute("wfo_3_3");

  }

  if (nRequested == 1 && (int)gluons.size()==nRequested+1) {
    vstream << "n2lo_4_3";
    wval[0].str("");
    wval[0] << 0.0;

    string wfo_2_4 = infoPtr->getEventAttribute("wfo_2_4");
    wname[1] = "wfo_2_3";
    wval[1].str("");
    if (wfo_2_4.empty()) wval[1] << 0.0;
    else wval[1] << sign*atof(wfo_2_4.c_str());
    infoPtr->removeEventAttribute("wfo_2_4");

    wname[2] = "wfo_3_3";
    string wfo_3_4 = infoPtr->getEventAttribute("wfo_3_4");
    wval[2].str("");
    if (wfo_3_4.empty()) wval[2] << 0.0;
    else wval[2] << sign*atof(wfo_3_4.c_str());
    infoPtr->removeEventAttribute("wfo_3_4");

  }
  if (nRequested == 2 && (int)gluons.size()==nRequested+1) {
    vstream << "n1lo_5_4";
    wname[1] = "wfo_3_4";
    wval[0].str("");
    wval[0] << 0.0;
    wval[1].str("");
    wval[1] << sign*evtWeight;
  }

  infoPtr->setEventAttribute("eventType",   vstream.str());

  for (int i=0; i<4; ++i)
    if (wname[i] != "n/a") infoPtr->setEventAttribute(wname[i], wval[i].str());
  
  string old_wtsum = infoPtr->getEventAttribute("wfo_sum");
  vstream.str("");
  if (old_wtsum.empty()) vstream << sign*wgt[4]*evtWeight;
  else vstream << sign*atof(old_wtsum.c_str());
  infoPtr->setEventAttribute("wfo_sum", vstream.str());

  // Set process to (potentially) new state.
  process = picked->state;
  process.scale(infoPtr->eCM());

  // Update the event weight.
  infoPtr->updateWeight(infoPtr->weight()/CONVERTMB2PB*wgt[4]*sign);

  //string old_weight = infoPtr->getEventAttribute("weight");
  double w = (old_weight.empty())
           ? infoPtr->weight()*cutEfficiency /* /neve */ 
           : atof(old_weight.c_str())*wgt[4]*sign*cutEfficiency;
  vstream.str(""); vstream << w;
  infoPtr->setEventAttribute("weight", vstream.str());

  vstream.str("");
  vstream << clusteringScale;
  if (clusteringScale != 0.) {
    infoPtr->setEventAttribute("clusteringScale", vstream.str());
//cout << "set clustering scale " << clusteringScale << endl;
  }

  // Done
  return 1;

}

//--------------------------------------------------------------------------

int DireMerging::cutForN3LO ( Event& process) {

  initForN3LO(process);
  int returnCode = createHistoryForN3LO ();

  if (tomteInfo.history) {
    delete tomteInfo.history;
    tomteInfo.history = 0;
  }

  return returnCode;

}

//--------------------------------------------------------------------------

int DireMerging::matchN3LO ( Event& process) {

  /*int initCode          = initForN3LO(process);
  int histCreationCode  = createHistoryForN3LO ();
  int wtCreationCode    = createMatchedEventsForN3LO ();
  int wtAssembleCode    = assembleOutputsForN3LO ();
  int initGenCode       = getStartingConditionsForN3LO (process);*/

  initForN3LO(process);
  createHistoryForN3LO ();
  createMatchedEventsForN3LO ();
  assembleOutputsForN3LO ();
  getStartingConditionsForN3LO (process);

  if (tomteInfo.history) {
    delete tomteInfo.history;
    tomteInfo.history = 0;
  }

  return 1;

}

//--------------------------------------------------------------------------

int DireMerging::initForN3LO ( const Event& process) {

  //if (tomteInfo.history) delete tomteInfo.history;
  tomteInfo.pathIndex = -1.;
  tomteInfo.clear();

  // Prepare process record for merging. If Pythia has already decayed
  // resonances used to define the hard process, remove resonance decay
  // products.
  Event newProcess( evtUtils->eventForMerging( process, true) );
  // Store candidates for the splitting V -> qqbar'
  mergingHooksPtr->storeHardProcessCandidates( newProcess );

  // Calculate number of clustering steps
  tomteInfo.nSteps = mergingHooksPtr->getNumberOfClusteringSteps(newProcess);
  mergingHooksPtr->nHardNowSave = tomteInfo.nSteps;

  // Potentially recluster real emission jets for powheg input containing
  // "too many" jets, i.e. real-emission kinematics.
  tomteInfo.nRequested = mergingHooksPtr->nRequested();
  tomteInfo.containsRealKin = tomteInfo.nSteps > tomteInfo.nRequested
    && tomteInfo.nSteps > 0;

  tomteInfo.states.push_back(TomteState(1.,"input",newProcess));

  return 1;
}

//--------------------------------------------------------------------------

int DireMerging::createHistoryForN3LO () {

  string scaleString = infoPtr->getEventAttribute("clusteringScale");
  double scaleValue  = 0.;
  if (!scaleString.empty()) scaleValue = atof(scaleString.c_str());

  Event newProcess = tomteInfo.states[0].state;

  // prefer ordered histories.
  mergingHooksPtr->orderHistories(true);

  // Set dummy process scale.
  newProcess.scale(scaleValue);
  // Generate all histories
  tomteInfo.history = new DireHistory( tomteInfo.nSteps, scaleValue,
     newProcess, DireClustering(),
     mergingHooksPtr, (*beamAPtr), (*beamBPtr), particleDataPtr, infoPtr,
     trialPartonLevelPtr, fsr, isr, psweights, coupSMPtr, true, true,
     tomteInfo.containsRealKin, 1.0, 1.0, 1.0, 1.0, 0);

  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = tomteInfo.history;

  // Discard any events for which not all paths are above the cut-off.
// begin comment when using histories below tms
  if (!doCheckBasics && tomteInfo.nSteps > 0 && !picked->allPathsAboveTMS()) {
    //cout << "State fails cut at line " << __LINE__ << " <" << scaleString << ">" << endl;
    //cout << __LINE__ << " " << infoPtr->getEventAttribute("eventType")
    //  << " veto " << endl; 
    return vetoEvent();
  }
// end comment when using histories below tms

  // Need this to fill good branches.
  if (tomteInfo.nSteps > 0 && !picked->projectOntoDesiredHistories()){
    //cout << "State fails cut at line " << __LINE__ << " " << tomteInfo.nSteps << endl;
    //cout << __LINE__ << " " << infoPtr->getEventAttribute("eventType")
    //  << " veto " << endl; 
    return vetoEvent();
  }
  if (tomteInfo.nSteps > 0 && picked->goodBranches.empty()){
    //cout << "State fails cut at line " << __LINE__ << endl;
    //cout << __LINE__ << " " << infoPtr->getEventAttribute("eventType")
    //  << " veto " << endl; 
    return vetoEvent();
  }

  return 1;

}

//--------------------------------------------------------------------------

int DireMerging::createMatchedEventsForN3LO () {

  DireHistory* history = tomteInfo.history;
  string w = infoPtr->getEventAttribute("weight");
  double wt = atof(w.c_str()); // *infoPtr->weight()/CONVERTMB2PB;

  // Save number of looping steps
  mergingHooksPtr->nReclusterSave = settingsPtr->mode("Merging:nRecluster");

  // Ensure that merging hooks to not remove emissions
  mergingHooksPtr->doIgnoreEmissions(true);
  mergingHooksPtr->setWeightCKKWL(1.);
  mergingHooksPtr->setWeightFIRST(0.);

  string eventType = infoPtr->getEventAttribute("eventType");
  Event newProcess = tomteInfo.states[0].state;

  // If need be, perform one clustering of real-emission state to one
  // underlying Born, with uniform probability
  DireHistory* picked = history;
  DireHistory* starting_leaf = 0;
  pair<double,DireHistory*> ppp;

// begin comment when using histories below tms

  // Discard any events for which not all paths are above the cut-off.
  if (tomteInfo.nSteps > 0 && !picked->allPathsAboveTMS()) {
    cout << "State fails cut at line " << __LINE__ << endl;
    return vetoEvent();
  }
  // Need this to fill good branches.
  if (tomteInfo.nSteps > 0 && !picked->projectOntoDesiredHistories()){
    return vetoEvent();
  }
  if (tomteInfo.nSteps > 0 && picked->goodBranches.empty()){
    return vetoEvent();
  }

// end comment when using histories below tms

  if (eventType == "n3lo_2" || eventType == "n3lo_3_2") {
    string suffix = eventType.substr(
      eventType.find_first_of("_",0)+1,
      eventType.size());
    //tomteInfo.states.push_back(
    //  TomteState(wt,"matched_n3lo_" + suffix, history->state));

    double n0lo_wt = atof(infoPtr->getEventAttribute("wfo_0_2").c_str());
    double n1lo_wt = atof(infoPtr->getEventAttribute("wfo_1_2").c_str());
    double n2lo_wt = atof(infoPtr->getEventAttribute("wfo_2_2").c_str());
    double n3lo_wt = atof(infoPtr->getEventAttribute("wfo_3_2").c_str());

//cout << suffix << " " << n0lo_wt << " " << n1lo_wt << " " << n2lo_wt << " " << n3lo_wt << endl;

    if (eventType == "n3lo_2") tomteInfo.states.push_back(
      TomteState(n0lo_wt,"matched_n0lo_" + suffix,history->state));
    tomteInfo.states.push_back(
      TomteState(n1lo_wt,"matched_n1lo_" + suffix,history->state));
    tomteInfo.states.push_back(
      TomteState(n2lo_wt,"matched_n2lo_" + suffix,history->state));
    tomteInfo.states.push_back(
      TomteState(n3lo_wt,"matched_n3lo_" + suffix,history->state));

  } else if (eventType == "n2lo_3" || eventType == "n2lo_4_3") {

    string suffix = eventType.substr(
      eventType.find_first_of("_",0)+1,
      eventType.size());

    pair<double,DireHistory*> p1;
    // Pick a leaf
    p1 = picked->getProbabilisticFullLeaf(rndmPtr, starting_leaf);
    //p1 = picked->getDemocraticLeaf(rndmPtr);

    double one1to1 = 1.;
    double path = pathIndexForN3LO(starting_leaf,picked->branches);

    map<string,double> weights = picked->weightAllOrder( trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      path);

    map<string,double> weightsExp = picked->weightAllOrderExpanded( 12,
      trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      path);


    for ( map<string,double>::iterator
        it = weights.begin();
        it != weights.end(); ++it )
        cout << " " << it->first << " " << it->second << endl;
    for ( map<string,double>::iterator
        it = weightsExp.begin();
        it != weightsExp.end(); ++it )
        cout << " " << it->first << " " << it->second << endl;


abort();











    double wgt1
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.);

    double wgt1SingleSubt
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * ( 1. - (doTOMTESudakovs     ? weightsExp["delta_0_1"]       : 0.)
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_1_1"] : 0.));

    double wgt1DoubleSubt
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * ( 1. - (doTOMTESudakovs     ? weightsExp["delta_0_1"]              : 0.) 
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_1_1"]        : 0.)
             - (doTOMTESudakovs     ? weightsExp["delta_0_2"]              : 0.)
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_1_2"]        : 0.)
             // absent because already cancelled with delta_0_2
             // + pow2(weightsExp["delta_0_1"])
             // absent because already cancelled with alphasratio_1_2 // wrong comment, see History.cc lines 4065 - 4077 
             + (doTOMTEAlphasRatios  ? pow2(weightsExp["alphasratio_1_1"]) : 0.)
             +  (doTOMTESudakovs     ? weightsExp["delta_0_1"]             : 0.)
               *(doTOMTEAlphasRatios ? weightsExp["alphasratio_1_1"]       : 0.));

    double n0lo_wt = atof(infoPtr->getEventAttribute("wfo_1_3").c_str());
    double n1lo_wt = atof(infoPtr->getEventAttribute("wfo_2_3").c_str());
    double n2lo_wt = atof(infoPtr->getEventAttribute("wfo_3_3").c_str());

    if (eventType == "n2lo_3") tomteInfo.states.push_back(
      TomteState(n0lo_wt*one1to1*wgt1DoubleSubt,
      "matched_n0lo_" + suffix,picked->state));
    tomteInfo.states.push_back(
      TomteState(n1lo_wt*one1to1*wgt1SingleSubt,
      "matched_n1lo_" + suffix,picked->state));
    tomteInfo.states.push_back(
      TomteState(n2lo_wt*one1to1*wgt1,
      "matched_n2lo_" + suffix,picked->state));

    // Replace selection rate with single-clustering probabilistic rate.
    double one1to0 = 1./p1.first;
    one1to0 *= picked->getSelectionRateProbabilistic(p1.second);

    // Select the new leaf and construct rate to pick this particular path
    // to (n-1)-body state.
    picked = p1.second;
    picked->rescaleProbs();
    picked->extractBranches(history->branches);
    picked->mother = 0;

    if (eventType == "n2lo_3") tomteInfo.states.push_back(
      TomteState(n0lo_wt*one1to0 - n0lo_wt*one1to1*wgt1DoubleSubt,
      "matched_n1lo_" + suffix + "_2",picked->state));
    tomteInfo.states.push_back(
      TomteState(n1lo_wt*one1to0 - n1lo_wt*one1to1*wgt1SingleSubt,
      "matched_n2lo_" + suffix + "_2",picked->state));
    tomteInfo.states.push_back(
      TomteState(n2lo_wt*one1to0 - n2lo_wt*one1to1*wgt1,
      "matched_n3lo_" + suffix + "_2",picked->state));

  } else if (eventType == "n1lo_4" || eventType == "n1lo_5_4") {

    string suffix = eventType.substr(
      eventType.find_first_of("_",0)+1,
      eventType.size());

    pair<double,DireHistory*> p1, p2;
    // Pick a leaf
    p1 = picked->getProbabilisticFullLeaf(rndmPtr, starting_leaf);

    double one2to2 = 1.;
    double path = pathIndexForN3LO(starting_leaf,picked->branches);

    map<string,double> weights = picked->weightAllOrder( trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      path);

    map<string,double> weightsExp = picked->weightAllOrderExpanded( 1,
      trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      path);

    /*for ( map<string,double>::iterator
        it = weights.begin();
        it != weights.end(); ++it )
        infoPtr->setEventAttribute(it->first,std::to_string(it->second));
    for ( map<string,double>::iterator
        it = weightsExp.begin();
        it != weightsExp.end(); ++it )
        infoPtr->setEventAttribute(it->first,std::to_string(it->second));*/

    double wgt2
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTESudakovs     ? weights["delta_1"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_2"] : 1.);

    double wgt2Subt
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTESudakovs     ? weights["delta_1"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_2"] : 1.)
      * ( 1. - (doTOMTESudakovs     ? weightsExp["delta_0_1"]       : 0.)
             - (doTOMTESudakovs     ? weightsExp["delta_1_1"]       : 0.)
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_1_1"] : 0.)
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_2_1"] : 0.));

//wgt2=1.;
//wgt2Subt=1.;

    double n0lo_wt = atof(infoPtr->getEventAttribute("wfo_2_4").c_str());
    double n1lo_wt = atof(infoPtr->getEventAttribute("wfo_3_4").c_str());

    if (eventType == "n1lo_4") {
      tomteInfo.states.push_back(
      TomteState(n0lo_wt*one2to2*wgt2Subt,
      "matched_n0lo_" +suffix,picked->state));
    }
    tomteInfo.states.push_back(
      TomteState(n1lo_wt*one2to2*wgt2,
      "matched_n1lo_" +suffix,picked->state));

    // Replace selection rate with single-clustering probabilistic rate.
    double one2to1 = 1./p1.first;
    one2to1 *= picked->getSelectionRateProbabilistic(p1.second);

    DireHistory* mom = p1.second->mother;
    p1.second->mother = 0;
    double one2to0 = one2to1;
    p2 = p1.second->getNextProbabilisticFullLeaf(starting_leaf);
    p1.second->mother = mom;
    one2to0 *= 1./p2.first;

    // Select the new leaf and construct rate to pick this particular path
    // to (n-1)-body state.
    picked = p1.second;
    picked->rescaleProbs();
    picked->extractBranches(history->branches);
    one2to0
        *= picked->getSelectionRateProbabilistic(p2.second);
    picked->mother = 0;

    double wgt1
      = (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.);
    double wgt1Subt
      = (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * ( 1. - (doTOMTESudakovs     ? weightsExp["delta_0_1"]       : 0.)
             - (doTOMTEAlphasRatios ? weightsExp["alphasratio_1_1"] : 0.));
    
    if (eventType == "n1lo_4") {
      tomteInfo.states.push_back(
      TomteState(n0lo_wt*one2to1*wgt1Subt - n0lo_wt*one2to2*wgt2Subt,
      "matched_n1lo_" + suffix + "_3",picked->state));
    }
    tomteInfo.states.push_back(
      TomteState(n1lo_wt*one2to1*wgt1 - n1lo_wt*one2to2*wgt2,
      "matched_n2lo_" + suffix + "_3",picked->state));

    // Select the new leaf and construct rate to pick this particular path
    // to (n-1)-body state.
    picked = p2.second;
    picked->rescaleProbs();
    picked->extractBranches(p1.second->branches);
    picked->mother = 0;

    double wgt0 = 1.;
    if (eventType == "n1lo_4") {
      tomteInfo.states.push_back(
      TomteState(n0lo_wt*one2to0*wgt0 - n0lo_wt*one2to1*wgt1Subt,
      "matched_n2lo_" + suffix + "_2",picked->state));
    }
    tomteInfo.states.push_back(
      TomteState(n1lo_wt*one2to0*wgt0 - n1lo_wt*one2to1*wgt1,
      "matched_n3lo_" + suffix + "_2",picked->state));

  } else if (eventType == "n0lo_5") {

    string suffix = eventType.substr(
      eventType.find_first_of("_",0)+1,
      eventType.size());

    pair<double,DireHistory*> p1, p2, p3;
    // Pick a leaf
    p1 = picked->getProbabilisticFullLeaf(rndmPtr, starting_leaf);

    double one3to3 = 1.;
    double path = pathIndexForN3LO(starting_leaf,picked->branches);

    map<string,double> weights = picked->weightAllOrder( trialPartonLevelPtr,
      mergingHooksPtr->AlphaS_FSR(), mergingHooksPtr->AlphaS_ISR(),
      mergingHooksPtr->AlphaEM_FSR(), mergingHooksPtr->AlphaEM_ISR(),
      path);

    double wgt3
      = 1.
      * (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTESudakovs     ? weights["delta_1"]       : 1.)
      * (doTOMTESudakovs     ? weights["delta_2"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_2"] : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_3"] : 1.)
      ;

//    double n0lo_wt = atof(infoPtr->getEventAttribute("wfo_3_5").c_str());
/*
    vector<double> scales = starting_leaf->scales(picked);
//begin uncomment when using histories below tms
    for (int i=0; i < (int)scales.size(); ++i) {
      //if(scales[i]<1.0) wgt3=0.;
      ostringstream name; name << "scale_" << i;
      infoPtr->setEventAttribute(name.str(),std::to_string(scales[i]));
    }
    if (scales.size()>2 && scales[2] < mergingHooksPtr->tms()) wgt3=0.0;
// end uncomment when using histories below tms
*/

//wgt3=1.0;
    for ( map<string,double>::iterator
        it = weights.begin();
        it != weights.end(); ++it )
        infoPtr->setEventAttribute(it->first,std::to_string(it->second));

    tomteInfo.states.push_back(TomteState(wt*one3to3*wgt3,
      "matched_n0lo_" + suffix,picked->state));

    // Replace selection rate with single-clustering probabilistic rate.
    double one3to2 = 1./p1.first;
    //one3to2 *= picked->getSelectionRateDemocratic(p1.second);
    one3to2 *= picked->getSelectionRateProbabilistic(p1.second);

    DireHistory* mom = p1.second->mother;
    p1.second->mother = 0;
    double one3to1 = one3to2;
    p2 = p1.second->getNextProbabilisticFullLeaf(starting_leaf);
    p1.second->mother = mom;
    one3to1 *= 1./p2.first;

    mom = p2.second->mother;
    p2.second->mother = 0;
    double one3to0 = one3to1;
    p3 = p2.second->getNextProbabilisticFullLeaf(starting_leaf);
    p2.second->mother = mom;
    one3to0 *= 1./p3.first;

    // Select the new leaf and construct rate to pick this particular path
    // to (n-1)-body state.
    picked = p1.second;
    picked->rescaleProbs();
    picked->extractBranches(history->branches);
    one3to1
        *= picked->getSelectionRateProbabilistic(p2.second);
    one3to0
        *= picked->getSelectionRateProbabilistic(p2.second);
    picked->mother = 0;

    double wgt2
      = (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTESudakovs     ? weights["delta_1"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_2"] : 1.);

/*//begin uncomment when using histories below tms
    if (scales.size()>1 && scales[1] < mergingHooksPtr->tms()) wgt2=0.0;
// end uncomment when using histories below tms
*/
//wgt2=1.;

    tomteInfo.states.push_back(TomteState(wt*one3to2*wgt2 - wt*one3to3*wgt3,
    //tomteInfo.states.push_back(TomteState(wt*one3to2*wgt2 - wt*one3to2*wgt3,
      "matched_n1lo_" + suffix + "_4",picked->state));
    
    // Select the new leaf and construct rate to pick this particular path
    // to (n-1)-body state.
    picked = p2.second;
    picked->rescaleProbs();
    picked->extractBranches(p1.second->branches);
    one3to0
      *= picked->getSelectionRateProbabilistic(p3.second);
    picked->mother = 0;

    double wgt1
      = (doTOMTESudakovs     ? weights["delta_0"]       : 1.)
      * (doTOMTEAlphasRatios ? weights["alphasratio_1"] : 1.);

/*//begin uncomment when using histories below tms
    if (scales.size()>0 && scales[0] < mergingHooksPtr->tms()) wgt1=0.0;
// end uncomment when using histories below tms
*/
    tomteInfo.states.push_back(TomteState(wt*one3to1*wgt1 - wt*one3to2*wgt2,
      "matched_n2lo_" + suffix + "_3",picked->state));

    picked = p3.second;
    picked->mother = 0;

    double wgt0 = 1.;
    tomteInfo.states.push_back(TomteState(wt*one3to0*wgt0 - wt*one3to1*wgt1,
      "matched_n3lo_" + suffix + "_2",picked->state));

  }

  // Done
  return 1;
}

//--------------------------------------------------------------------------

int DireMerging::assembleOutputsForN3LO() {

  /*double nsamples = atof(infoPtr->getEventAttribute("nsamples").c_str());
  string typeOld = infoPtr->getEventAttribute("eventType");
  double neve = double(settingsPtr->mode("Main:numberOfEvents"));

  for (auto s : tomteInfo.states) {
    if (s.name == "input") continue;
    double neveNow = neve/nsamples;
    ostringstream vstream; vstream.str(""); vstream << double(neveNow);
    infoPtr->setEventAttribute("neve", vstream.str());
    infoPtr->setEventAttribute("eventType",s.name);
    infoPtr->setEventAttribute("matched_weight", std::to_string(s.wt));
    infoPtr->updateWeight(s.wt);
    infoPtr->setEventAttribute("eventType",typeOld);
  }
  infoPtr->setEventAttribute("matched_weight", std::to_string(1.));
*/
  return 1;
}

//--------------------------------------------------------------------------

int DireMerging::getStartingConditionsForN3LO( Event& process ) {

  process = tomteInfo.history->state;

  // Update the event weight.
  infoPtr->updateWeight(
     infoPtr->weight()
    / CONVERTMB2PB
    * tomteInfo.states[0].wt);

  return 1;
}

double DireMerging::pathIndexForN3LO(DireHistory* starting_leaf,
  map<double, DireHistory*> branches) {

  double pathIndex(0.);
  if (starting_leaf) {
    double lastp(0.);
    double sumAll(0.);
    for ( map<double, DireHistory*>::iterator
      it = branches.begin();
      it != branches.end(); ++it )
      sumAll     += it->second->prodOfProbs;
    for ( map<double, DireHistory*>::iterator
      it = branches.begin();
      it != branches.end(); ++it ) {
      pathIndex =  (lastp + 0.5*(it->first - lastp))/sumAll;
      lastp = it->first;
      if (it->second == starting_leaf) break;
    }
  } else
    pathIndex = rndmPtr->flat();

  return pathIndex;

}

//==========================================================================

} // end namespace Pythia8
