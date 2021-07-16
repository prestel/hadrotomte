
#include "Dire/SplittingLibrary.h"

namespace Pythia8 {
 
//==========================================================================

// class SplittingLibrary

//--------------------------------------------------------------------------

// Clean up
void DireSplittingLibrary::clear() {
  for ( std::unordered_map<string,DireSplitting*>::iterator
    it = splittings.begin();
    it != splittings.end(); ++it ) if (it->second) delete it->second;
  splittings.clear();
  splittingsVec.clear();
}

//--------------------------------------------------------------------------

// Initialisation.
void DireSplittingLibrary::init(Settings* settings, ParticleData* particleData,
  Rndm* rndm, BeamParticle* beamA, BeamParticle* beamB, CoupSM* coupSM,
  Info* info, DireInfo* direInfo, DireHooks* hooks,
   SLHAinterface* slhaInterface) {

  // Store infrastructure pointers.
  settingsPtr     = settings;
  particleDataPtr = particleData;
  rndmPtr         = rndm;
  beamAPtr        = beamA;
  beamBPtr        = beamB;
  coupSMPtr       = coupSM;
  infoPtr         = info;
  direInfoPtr     = direInfo;
  slhaInterfacePtr = slhaInterface;

  if (!hooksPtr) hooksPtr        = hooks;
  if (hooksPtr)  hasExternalHook = true;

  // Initialise splitting names.
  clear();
  initISR();
  initFSR();

  // Now fill vector of splittings (more efficient for iteration than
  // unordered_map)
  for ( unordered_map<string,DireSplitting*>::iterator it = splittings.begin();
    it != splittings.end(); ++it )
    splittingsVec.push_back(it->second);

  fsrQCD_1_to_1_and_21            = shash("Dire_fsr_qcd_1->1&21");
  fsrQCD_1_to_21_and_1            = shash("Dire_fsr_qcd_1->21&1");
  fsrQCD_21_to_21_and_21a         = shash("Dire_fsr_qcd_21->21&21a");
  fsrQCD_21_to_21_and_21b         = shash("Dire_fsr_qcd_21->21&21b");
  fsrQCD_21_to_1_and_1a           = shash("Dire_fsr_qcd_21->1&1a");
  fsrQCD_21_to_1_and_1b           = shash("Dire_fsr_qcd_21->1&1b");
  fsrQCD_1_to_2_and_1_and_2       = shash("Dire_fsr_qcd_1->2&1&2");
  fsrQCD_1_to_1_and_1_and_1       = shash("Dire_fsr_qcd_1->1&1&1");
  fsrQCD_1_to_1_and_21_notPartial = shash("Dire_fsr_qcd_1->1&21_notPartial");
  fsrQCD_21_to_21_and_21_notPartial = shash("Dire_fsr_qcd_21->21&21_notPartial");
  fsrQCD_21_to_1_and_1_notPartial = shash("Dire_fsr_qcd_21->1&1_notPartial");
  fsrQCD_1_to_1_and_21_and_21     = shash("Dire_fsr_qcd_1->1&21&21");
  fsrQCD_1_to_1_and_1_and_1a      = shash("Dire_fsr_qcd_1->1&d&dbar");
  fsrQCD_1_to_1_and_1_and_1b      = shash("Dire_fsr_qcd_1->1&dbar&d");
  fsrQCD_1_to_1_and_2_and_2a      = shash("Dire_fsr_qcd_1->1&u&ubar");
  fsrQCD_1_to_1_and_2_and_2b      = shash("Dire_fsr_qcd_1->1&ubar&u");
  fsrQCD_1_to_1_and_3_and_3a      = shash("Dire_fsr_qcd_1->1&s&sbar");
  fsrQCD_1_to_1_and_3_and_3b      = shash("Dire_fsr_qcd_1->1&sbar&s");
  fsrQCD_1_to_1_and_4_and_4a      = shash("Dire_fsr_qcd_1->1&c&cbar");
  fsrQCD_1_to_1_and_4_and_4b      = shash("Dire_fsr_qcd_1->1&cbar&c");
  fsrQCD_1_to_1_and_5_and_5a      = shash("Dire_fsr_qcd_1->1&b&bbar");
  fsrQCD_1_to_1_and_5_and_5b      = shash("Dire_fsr_qcd_1->1&bbar&b");
  fsrQCD_21_to_21_and_21_and_21   = shash("Dire_fsr_qcd_21->21&21&21");
  fsrQCD_21_to_21_and_1_and_1a    = shash("Dire_fsr_qcd_21->21&d&dbar");
  fsrQCD_21_to_21_and_1_and_1b    = shash("Dire_fsr_qcd_21->21&dbar&d");
  fsrQCD_21_to_21_and_2_and_2a    = shash("Dire_fsr_qcd_21->21&u&ubar");
  fsrQCD_21_to_21_and_2_and_2b    = shash("Dire_fsr_qcd_21->21&ubar&u");
  fsrQCD_21_to_21_and_3_and_3a    = shash("Dire_fsr_qcd_21->21&s&sbar");
  fsrQCD_21_to_21_and_3_and_3b    = shash("Dire_fsr_qcd_21->21&sbar&s");
  fsrQCD_21_to_21_and_4_and_4a    = shash("Dire_fsr_qcd_21->21&c&cbar");
  fsrQCD_21_to_21_and_4_and_4b    = shash("Dire_fsr_qcd_21->21&cbar&c");
  fsrQCD_21_to_21_and_5_and_5a    = shash("Dire_fsr_qcd_21->21&b&bbar");
  fsrQCD_21_to_21_and_5_and_5b    = shash("Dire_fsr_qcd_21->21&bbar&b");

  fsrQED_1_to_1_and_22            = shash("Dire_fsr_qed_1->1&22");
  fsrQED_1_to_22_and_1            = shash("Dire_fsr_qed_1->22&1");
  fsrQED_11_to_11_and_22          = shash("Dire_fsr_qed_11->11&22");
  fsrQED_11_to_22_and_11          = shash("Dire_fsr_qed_11->22&11");
  fsrQED_22_to_1_and_1a           = shash("Dire_fsr_qed_22->1&1a");
  fsrQED_22_to_1_and_1b           = shash("Dire_fsr_qed_22->1&1b");
  fsrQED_22_to_2_and_2a           = shash("Dire_fsr_qed_22->2&2a");
  fsrQED_22_to_2_and_2b           = shash("Dire_fsr_qed_22->2&2b");
  fsrQED_22_to_3_and_3a           = shash("Dire_fsr_qed_22->3&3a");
  fsrQED_22_to_3_and_3b           = shash("Dire_fsr_qed_22->3&3b");
  fsrQED_22_to_4_and_4a           = shash("Dire_fsr_qed_22->4&4a");
  fsrQED_22_to_4_and_4b           = shash("Dire_fsr_qed_22->4&4b");
  fsrQED_22_to_5_and_5a           = shash("Dire_fsr_qed_22->5&5a");
  fsrQED_22_to_5_and_5b           = shash("Dire_fsr_qed_22->5&5b");
  fsrQED_22_to_11_and_11a         = shash("Dire_fsr_qed_22->11&11a");
  fsrQED_22_to_11_and_11b         = shash("Dire_fsr_qed_22->11&11b");
  fsrQED_22_to_13_and_13a         = shash("Dire_fsr_qed_22->13&13a");
  fsrQED_22_to_13_and_13b         = shash("Dire_fsr_qed_22->13&13b");
  fsrQED_22_to_15_and_15a         = shash("Dire_fsr_qed_22->15&15a");
  fsrQED_22_to_15_and_15b         = shash("Dire_fsr_qed_22->15&15b");
  fsrQED_1_to_1_and_22_notPartial = shash("Dire_fsr_qed_1->1&22_notPartial");
  fsrQED_11_to_11_and_22_notPartial = shash("Dire_fsr_qed_11->11&22_notPartial");

  fsrEWK_1_to_1_and_23            = shash("Dire_fsr_ew_1->1&23");
  fsrEWK_1_to_23_and_1            = shash("Dire_fsr_ew_1->23&1");
  fsrEWK_23_to_1_and_1a           = shash("Dire_fsr_ew_23->1&1a");
  fsrEWK_23_to_1_and_1b           = shash("Dire_fsr_ew_23->1&1b");
  fsrEWK_24_to_1_and_1a           = shash("Dire_fsr_ew_24->1&1a");
  fsrEWK_24_to_1_and_1b           = shash("Dire_fsr_ew_24->1&1b");
  fsrEWK_25_to_24_and_24          = shash("Dire_fsr_ew_25->24&24");
  fsrEWK_25_to_22_and_22          = shash("Dire_fsr_ew_25->22&22");
  fsrEWK_25_to_21_and_21          = shash("Dire_fsr_ew_25->21&21");
  fsrEWK_24_to_24_and_22          = shash("Dire_fsr_ew_24->24&22");

  isrQCD_1_to_1_and_21            = shash("Dire_isr_qcd_1->1&21");
  isrQCD_21_to_1_and_1            = shash("Dire_isr_qcd_21->1&1");
  isrQCD_21_to_21_and_21a         = shash("Dire_isr_qcd_21->21&21a");
  isrQCD_21_to_21_and_21b         = shash("Dire_isr_qcd_21->21&21b");
  isrQCD_1_to_21_and_1            = shash("Dire_isr_qcd_1->21&1");
  isrQCD_1_to_2_and_1_and_2       = shash("Dire_isr_qcd_1->2&1&2");
  isrQCD_1_to_1_and_1_and_1       = shash("Dire_isr_qcd_1->1&1&1");

  isrQED_1_to_1_and_22            = shash("Dire_isr_qed_1->1&22");
  isrQED_11_to_11_and_22          = shash("Dire_isr_qed_11->11&22");
  isrQED_1_to_22_and_1            = shash("Dire_isr_qed_1->22&1");
  isrQED_11_to_22_and_11          = shash("Dire_isr_qed_11->22&11");
  isrQED_22_to_1_and_1            = shash("Dire_isr_qed_22->1&1");
  isrQED_22_to_11_and_11          = shash("Dire_isr_qed_22->11&11");

  isrEWK_1_to_1_and_23            = shash("Dire_isr_ew_1->1&23");

  fsrEWK_d_to_d_and_z0            = shash("Dire_fsr_ew_d->d&z");
  fsrEWK_d_to_z0_and_d            = shash("Dire_fsr_ew_d->z&d");
  isrEWK_d_to_d_and_z0            = shash("Dire_isr_ew_d->d&z");

  fsrEWK_d_to_u_and_wm            = shash("Dire_fsr_ew_d->u&w-");
  fsrEWK_d_to_wm_and_u            = shash("Dire_fsr_ew_d->w-&u");
  isrEWK_d_to_u_and_wm            = shash("Dire_isr_ew_d->w&w-");

  fsrEWK_dbar_to_dbar_and_z0      = shash("Dire_fsr_ew_dbar->dbar&z");
  fsrEWK_dbar_to_z0_and_dbar      = shash("Dire_fsr_ew_dbar->z&dbar");
  fsrEWK_u_to_u_and_z0            = shash("Dire_fsr_ew_u->u&z");
  fsrEWK_u_to_z0_and_u            = shash("Dire_fsr_ew_u->z&u");
  fsrEWK_ubar_to_ubar_and_z0      = shash("Dire_fsr_ew_ubar->ubar&z");
  fsrEWK_ubar_to_z0_and_ubar      = shash("Dire_fsr_ew_ubar->z&ubar");
  fsrEWK_s_to_s_and_z0            = shash("Dire_fsr_ew_s->s&z");
  fsrEWK_s_to_z0_and_s            = shash("Dire_fsr_ew_s->z&s");
  fsrEWK_sbar_to_sbar_and_z0      = shash("Dire_fsr_ew_sbar->sbar&z");
  fsrEWK_sbar_to_z0_and_sbar      = shash("Dire_fsr_ew_sbar->z&sbar");
  fsrEWK_c_to_c_and_z0            = shash("Dire_fsr_ew_c->c&z");
  fsrEWK_c_to_z0_and_c            = shash("Dire_fsr_ew_c->z&c");
  fsrEWK_cbar_to_cbar_and_z0      = shash("Dire_fsr_ew_cbar->cbar&z");
  fsrEWK_cbar_to_z0_and_cbar      = shash("Dire_fsr_ew_cbar->z&cbar");
  fsrEWK_b_to_b_and_z0            = shash("Dire_fsr_ew_b->b&z");
  fsrEWK_b_to_z0_and_b            = shash("Dire_fsr_ew_b->z&b");
  fsrEWK_bbar_to_bbar_and_z0      = shash("Dire_fsr_ew_bbar->bbar&z");
  fsrEWK_bbar_to_z0_and_bbar      = shash("Dire_fsr_ew_bbar->z&bbar");
  fsrEWK_t_to_t_and_z0            = shash("Dire_fsr_ew_t->t&z");
  fsrEWK_t_to_z0_and_t            = shash("Dire_fsr_ew_t->z&t");
  fsrEWK_tbar_to_tbar_and_z0      = shash("Dire_fsr_ew_tbar->tbar&z");
  fsrEWK_tbar_to_z0_and_tbar      = shash("Dire_fsr_ew_tbar->z&tbar");
  isrEWK_dbar_to_dbar_and_z0      = shash("Dire_isr_ew_dbar->dbar&z");
  isrEWK_u_to_u_and_z0            = shash("Dire_isr_ew_u->u&z");
  isrEWK_ubar_to_ubar_and_z0      = shash("Dire_isr_ew_ubar->ubar&z");
  isrEWK_s_to_s_and_z0            = shash("Dire_isr_ew_s->s&z");
  isrEWK_s_to_sbar_and_z0         = shash("Dire_isr_ew_sbar->sbar&z");
  isrEWK_c_to_c_and_z0            = shash("Dire_isr_ew_c->c&z");
  isrEWK_cbar_to_cbar_and_z0      = shash("Dire_isr_ew_cbar->cbar&z");
  isrEWK_b_to_b_and_z0            = shash("Dire_isr_ew_b->b&z");
  isrEWK_bbar_to_bbar_and_z0      = shash("Dire_isr_ew_bbar->bbar&z");
  isrEWK_t_to_t_and_z0            = shash("Dire_isr_ew_t->t&z");
  isrEWK_tbar_to_tbar_and_z0      = shash("Dire_isr_ew_tbar->tbar&z");

  fsrEWK_s_to_c_and_wm            = shash("Dire_fsr_ew_s->c&w-");
  fsrEWK_s_to_wm_and_c            = shash("Dire_fsr_ew_s->w-&c");
  fsrEWK_b_to_t_and_wm            = shash("Dire_fsr_ew_b->t&w-");
  fsrEWK_b_to_wm_and_t            = shash("Dire_fsr_ew_b->w-&t");
  fsrEWK_ubar_to_dbar_and_wm      = shash("Dire_fsr_ew_ubar->dbar&w-");
  fsrEWK_ubar_to_wm_and_dbar      = shash("Dire_fsr_ew_ubar->w-&dbar");
  fsrEWK_cbar_to_sbar_and_wm      = shash("Dire_fsr_ew_cbar->sbar&w-");
  fsrEWK_cbar_to_wm_and_sbar      = shash("Dire_fsr_ew_cbar->w-&sbar");
  fsrEWK_tbar_to_bbar_and_wm      = shash("Dire_fsr_ew_tbar->bbar&w-");
  fsrEWK_tbar_to_wm_and_bbar      = shash("Dire_fsr_ew_tbar->w-&bbar");
  isrEWK_s_to_c_and_wm            = shash("Dire_isr_ew_s->c&w-");
  isrEWK_b_to_t_and_wm            = shash("Dire_isr_ew_b->t&w-");
  isrEWK_ubar_to_dbar_and_wm      = shash("Dire_isr_ew_ubar->dbar&w-");
  isrEWK_cbar_to_sbar_and_wm      = shash("Dire_isr_ew_cbar->sbar&w-");
  isrEWK_tbar_to_bbar_and_wm      = shash("Dire_isr_ew_tbar->bbar&w-");

  fsrU1N_1_to_1_and_22            = shash("Dire_fsr_u1new_1->1&22");
  fsrU1N_1_to_22_and_1            = shash("Dire_fsr_u1new_1->22&1");
  fsrU1N_11_to_11_and_22          = shash("Dire_fsr_u1new_11->11&22");
  fsrU1N_11_to_22_and_11          = shash("Dire_fsr_u1new_11->22&11");
  fsrU1N_22_to_1_and_1a           = shash("Dire_fsr_u1new_22->1&1a");
  fsrU1N_22_to_1_and_1b           = shash("Dire_fsr_u1new_22->1&1b");
  fsrU1N_22_to_2_and_2a           = shash("Dire_fsr_u1new_22->2&2a");
  fsrU1N_22_to_2_and_2b           = shash("Dire_fsr_u1new_22->2&2b");
  fsrU1N_22_to_3_and_3a           = shash("Dire_fsr_u1new_22->3&3a");
  fsrU1N_22_to_3_and_3b           = shash("Dire_fsr_u1new_22->3&3b");
  fsrU1N_22_to_4_and_4a           = shash("Dire_fsr_u1new_22->4&4a");
  fsrU1N_22_to_4_and_4b           = shash("Dire_fsr_u1new_22->4&4b");
  fsrU1N_22_to_5_and_5a           = shash("Dire_fsr_u1new_22->5&5a");
  fsrU1N_22_to_5_and_5b           = shash("Dire_fsr_u1new_22->5&5b");
  fsrU1N_22_to_11_and_11a         = shash("Dire_fsr_u1new_22->11&11a");
  fsrU1N_22_to_11_and_11b         = shash("Dire_fsr_u1new_22->11&11b");
  fsrU1N_22_to_13_and_13a         = shash("Dire_fsr_u1new_22->13&13a");
  fsrU1N_22_to_13_and_13b         = shash("Dire_fsr_u1new_22->13&13b");
  fsrU1N_22_to_15_and_15a         = shash("Dire_fsr_u1new_22->15&15a");
  fsrU1N_22_to_15_and_15b         = shash("Dire_fsr_u1new_22->15&15b");
  fsrU1N_22_to_211_and_211a       = shash("Dire_fsr_u1new_22->211&211a");
  fsrU1N_22_to_211_and_211b       = shash("Dire_fsr_u1new_22->211&211b");

  isrU1N_1_to_1_and_22            = shash("Dire_isr_u1new_1->1&22");
  isrU1N_1_to_22_and_1            = shash("Dire_isr_u1new_1->22&1");
  isrU1N_22_to_1_and_1            = shash("Dire_isr_u1new_22->1&1");
  isrU1N_11_to_11_and_22          = shash("Dire_isr_u1new_11->11&22");
  isrU1N_11_to_22_and_11          = shash("Dire_isr_u1new_11->22&11");
  isrU1N_22_to_11_and_11          = shash("Dire_isr_u1new_22->11&11");

  // Done.
}

//--------------------------------------------------------------------------

void DireSplittingLibrary::initFSR() {

  /********************* FSR ******************************************/

  // Add corrections to the LO splitting kernel.
  // order  = 0 -> A1, B1
  // order  = 1 -> A1, A2, B1
  // order  = 2 -> A1, A2, A3, B1
  // order  = 3 -> A1, A2, A3, B1, B2
  int order = settingsPtr->mode("DireTimes:kernelOrder");
  string name = "";

  // QCD splittings.
  if (settingsPtr->flag("TimeShower:QCDshower")) {
    // Q -> Q G, soft part + collinear
    name = "Dire_fsr_qcd_1->1&21";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2QG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> G Q, soft part + collinear
    // At leading order, this can be trivially combined with Q->QG because of
    // symmetry under z --> 1 -z .
    // Since this is no longer possible at NLO, we keep the kernels separately.
    name = "Dire_fsr_qcd_1->21&1";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2GQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part + collinear
    name = "Dire_fsr_qcd_21->21&21a";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2GG1( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part + collinear
    name = "Dire_fsr_qcd_21->21&21b";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2GG2( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

/*    // G -> Q Q (regular DGLAP kernel)
    name = "Dire_fsr_qcd_21->1&1a";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2QQ1( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> Q Q (regular DGLAP kernel)
    name = "Dire_fsr_qcd_21->1&1b";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2QQ2( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
*/


  /*for (int i=-6; i <= 6; i++) {

    if (i==0) continue;

    string base="Dire_fsr_qcd_21->"

    stringstream nameNow;
    nameNow << base << i << "hard&" << -i;
    string n = nameNow.str();
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF( i, true, n,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );

    nameNow.str("");
    nameNow << base << i << "soft&" << -i;
    n = nameNow.str();
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF( i, false, n,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );

    //name = "Dire_fsr_qcd_21->1hard&-1";
    //splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF( 1, true, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
    //  infoPtr, direInfoPtr)) );
    //name = "Dire_fsr_qcd_21->-1hard&1";
    //splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF(-1, true, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
    //  infoPtr, direInfoPtr)) );
    //name = "Dire_fsr_qcd_21->1soft&-1";
    //splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF( 1, false, name,
    //  order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
    //  coupSMPtr, infoPtr, direInfoPtr)) );
    //name = "Dire_fsr_qcd_21->-1soft&1";
    //splittings.insert( make_pair( name, new Dire_fsr_qcd_G2FF(-1, false, name,
    //  order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
    //  coupSMPtr, infoPtr, direInfoPtr)) );

  }*/

    // Q -> Q' Q Q'bar (pure NLO kernel)
    name = "Dire_fsr_qcd_1->2&1&2";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2qQqbarDist( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Qbar Q Q (pure NLO kernel)
    name = "Dire_fsr_qcd_1->1&1&1";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2QbarQQId( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

/*
    // Full DGLAP kernels for shower w/o color-connected recoiler.
    name = "Dire_fsr_qcd_1->1&21_notPartial";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2QG_notPartial( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qcd_21->21&21_notPartial";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2GG_notPartial( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qcd_21->1&1_notPartial";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2QQ_notPartial( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
*/

    // Q -> Q G G
    name = "Dire_fsr_qcd_1->1&21&21";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2QGG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q d dbar
    name = "Dire_fsr_qcd_1->1&d&dbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q dbar d
    name = "Dire_fsr_qcd_1->1&dbar&d";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q u ubar
    name = "Dire_fsr_qcd_1->1&u&ubar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q ubar u
    name = "Dire_fsr_qcd_1->1&ubar&u";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q s sbar
    name = "Dire_fsr_qcd_1->1&s&sbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q sbar s
    name = "Dire_fsr_qcd_1->1&sbar&s";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q c cbar
    name = "Dire_fsr_qcd_1->1&c&cbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q cbar c
    name = "Dire_fsr_qcd_1->1&cbar&c";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q b bbar
    name = "Dire_fsr_qcd_1->1&b&bbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q bbar b
    name = "Dire_fsr_qcd_1->1&bbar&b";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_Q2Qqqbar(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G G
    name = "Dire_fsr_qcd_21->21&21&21";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2GGG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G d dbar
    name = "Dire_fsr_qcd_21->21&d&dbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G dbar d
    name = "Dire_fsr_qcd_21->21&dbar&d";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G u ubar
    name = "Dire_fsr_qcd_21->21&u&ubar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G ubar u
    name = "Dire_fsr_qcd_21->21&ubar&u";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G s sbar
    name = "Dire_fsr_qcd_21->21&s&sbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G sbar s
    name = "Dire_fsr_qcd_21->21&sbar&s";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G c cbar
    name = "Dire_fsr_qcd_21->21&c&cbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G cbar c
    name = "Dire_fsr_qcd_21->21&cbar&c";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G b bbar
    name = "Dire_fsr_qcd_21->21&b&bbar";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G bbar b
    name = "Dire_fsr_qcd_21->21&bbar&b";
    splittings.insert( make_pair( name, new Dire_fsr_qcd_G2Gqqbar(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  }

  /*// QCD splittings.
  if (settingsPtr->flag("TimeShower:QCDshower")) {
    // Q -> Q G, soft part + collinear
    name = "CS_fsr_qcd_1->1&21";
    splittings.insert( make_pair( name, new CS_fsr_qcd_Q2QG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> G Q, soft part + collinear
    name = "CS_fsr_qcd_1->21&1";
    splittings.insert( make_pair( name, new CS_fsr_qcd_Q2GQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part + collinear
    name = "CS_fsr_qcd_21->21&21a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2GG1( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part + collinear
    name = "CS_fsr_qcd_21->21&21b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2GG2( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> Q Q (regular DGLAP kernel)
    name = "CS_fsr_qcd_21->1&1a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->1&1b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->2&2a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->2&2b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->3&3a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->3&3b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->4&4a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->4&4b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->5&5a";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_fsr_qcd_21->5&5b";
    splittings.insert( make_pair( name, new CS_fsr_qcd_G2QQ(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
  }*/

  // QED splittings
  if (settingsPtr->flag("TimeShower:QEDshowerByQ")) {
    name = "Dire_fsr_qed_1->1&22";
    splittings.insert( make_pair( name, new Dire_fsr_qed_Q2QA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_1->22&1";
    splittings.insert( make_pair( name, new Dire_fsr_qed_Q2AQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    /*name = "Dire_fsr_qed_22->1&1a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->1&1b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->2&2a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->2&2b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->3&3a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->3&3b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->4&4a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->4&4b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->5&5a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->5&5b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    // Complete DGLAG kernel for photon emission off charge, as e.g. needed
    // after charged hadron decay.
    name = "Dire_fsr_qed_1->1&22_notPartial";
    splittings.insert( make_pair( name, new Dire_fsr_qed_Q2QA_notPartial( name,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );*/
  }

  if (settingsPtr->flag("TimeShower:QEDshowerByL")) {
    name = "Dire_fsr_qed_11->11&22";
    splittings.insert( make_pair( name, new Dire_fsr_qed_L2LA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_11->22&11";
    splittings.insert( make_pair( name, new Dire_fsr_qed_L2AL( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    /*name = "Dire_fsr_qed_22->11&11a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 11, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->11&11b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-11, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );*/



/*
    name = "Dire_fsr_qed_22->13&13a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 13, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->13&13b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-13, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
*/



    name = "Dire_fsr_qed_22->13hard&-13";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 13, true, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->-13hard&13";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-13, true, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );

    name = "Dire_fsr_qed_22->13soft&-13";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 13, false, name,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->-13soft&13";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-13, false, name,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );





    /*name = "Dire_fsr_qed_22->15&15a";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF( 15, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "Dire_fsr_qed_22->15&15b";
    splittings.insert( make_pair( name, new Dire_fsr_qed_A2FF(-15, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    // Complete DGLAG kernel for photon emission off charge, as e.g. needed
    // after charged hadron decay.
    name = "Dire_fsr_qed_11->11&22_notPartial";
    splittings.insert( make_pair( name, new Dire_fsr_qed_L2LA_notPartial( name,
      order, settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr,
      coupSMPtr, infoPtr, direInfoPtr)) );*/

    //name = "Dire_fsr_qed_11->11&e&ebar";
    //splittings.insert( make_pair( name, new Dire_fsr_qed_L2Lffbar( 11, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    //name = "Dire_fsr_qed_11->11&ebar&e";
    //splittings.insert( make_pair( name, new Dire_fsr_qed_L2Lffbar(-11, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  }

  // EW splittings
  if (settingsPtr->flag("TimeShower:EWshowerByQ")) {
    name = "Dire_fsr_ew_d->d&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(1,1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_d->z&d";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(1,1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_fsr_ew_dbar->dbar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-1,-1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_dbar->z&dbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-1,-1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_u->u&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(2,2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_u->z&u";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(2,2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_ubar->ubar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-2,-2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_ubar->z&ubar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-2,-2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_s->s&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(3,3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_s->z&s";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(3,3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_sbar->sbar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-3,-3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_sbar->z&sbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-3,-3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_c->c&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(4,4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_c->z&c";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(4,4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_cbar->cbar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-4,-4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_cbar->z&cbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-4,-4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_b->b&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(5,5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_b->z&b";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(5,5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_bbar->bbar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-5,-5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_bbar->z&bbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-5,-5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_t->t&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(6,6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_t->z&t";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(6,6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_tbar->tbar&z";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-6,-6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_tbar->z&tbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-6,-6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_fsr_ew_d->u&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(1,2,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_d->w-&u";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(1,2,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_fsr_ew_s->c&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(3,4,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_s->w-&c";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(3,4,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_b->t&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(5,6,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_b->w-&t";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(5,6,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_fsr_ew_ubar->dbar&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-2,-1,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_ubar->w-&dbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-2,-1,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_cbar->sbar&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-4,-3,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_cbar->w-&sbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-4,-3,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_tbar->bbar&w-";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2FV(-6,-5,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_fsr_ew_tbar->w-&bbar";
    splittings.insert( make_pair(name, new Dire_fsr_ew_F2VF(-6,-5,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    // H -> A A
    name = "Dire_fsr_ew_25->22&22";
    splittings.insert( make_pair( name, new Dire_fsr_ew_H2AA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );

    name = "Dire_fsr_ew_25->21&21";
    splittings.insert( make_pair( name, new Dire_fsr_ew_H2GG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );

  }

  /*// EW splittings
  // Q -> Q Z
  name = "Dire_fsr_ew_1->1&23";
  splittings.insert( make_pair( name, new Dire_fsr_ew_Q2QZ( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // Q -> Z Q
  name = "Dire_fsr_ew_1->23&1";
  splittings.insert( make_pair( name, new Dire_fsr_ew_Q2ZQ( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // Z -> Q Q~
  name = "Dire_fsr_ew_23->1&1a";
  splittings.insert( make_pair( name, new Dire_fsr_ew_Z2QQ1( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // Z -> Q~ Q
  name = "Dire_fsr_ew_23->1&1b";
  splittings.insert( make_pair( name, new Dire_fsr_ew_Z2QQ2( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // W -> Q Q~
  name = "Dire_fsr_ew_24->1&1a";
  splittings.insert( make_pair( name, new Dire_fsr_ew_W2QQ1( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // W -> Q~ Q
  name = "Dire_fsr_ew_24->1&1b";
  splittings.insert( make_pair( name, new Dire_fsr_ew_W2QQ2( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  // H -> W W
  name = "Dire_fsr_ew_25->24&24";
  splittings.insert( make_pair( name, new Dire_fsr_ew_H2WW( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );*/

  /*name = "Dire_fsr_ew_24->24&22";
  splittings.insert( make_pair( name, new Dire_fsr_ew_W2WA( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
    infoPtr, direInfoPtr)) );*/

  /*// New U(1) splittings
  if (settingsPtr->flag("TimeShower:U1newShowerByQ")) {
    name = "Dire_fsr_u1new_22->211&211a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2SS(211, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->211&211b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2SS(-211, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
  }*/

  // New U(1) splittings
  if (settingsPtr->flag("TimeShower:U1newShowerByL")) {
    name = "Dire_fsr_u1new_11->11&22";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_L2LA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_11->22&11";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_L2AL( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    /*name = "Dire_fsr_u1new_22->11&11a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 11, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->11&11b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-11, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );*/
/*    name = "Dire_fsr_u1new_22->13&13a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 13, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13&13b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-13, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
*/
    /*name = "Dire_fsr_u1new_22->15&15a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 15, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->15&15b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-15, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );*/

    /*name = "Dire_fsr_u1new_22->11&11aResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 11, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->11&11bResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-11, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->11&11aResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 11, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->11&11bResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-11, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );*/

/*    name = "Dire_fsr_u1new_22->13&13aResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13&13bResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13&13aResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13&13bResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
*/


/*

    name = "Dire_fsr_u1new_22->13hard&-13ResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13soft&-13ResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->-13hard&13ResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->-13soft&13ResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13hard&-13ResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->13soft&-13ResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->-13hard&13ResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->-13soft&13ResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-13, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
*/

  for (int i=13; i <= 13; i += 2) {
    stringstream nameNow;
    nameNow << "Dire_fsr_u1new_22->" << i << "hard&" << -i;
    string n = nameNow.str();
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FF(i, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResA";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i, 1, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResB";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i,-1, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    nameNow.str("");
    nameNow << "Dire_fsr_u1new_22->" << i << "soft&" << -i;
    n = nameNow.str();
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FF(i, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResA";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i, 1, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResB";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i,-1, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
  }

  for (int i=-13; i >= -13; i -= 2) {
    stringstream nameNow;
    nameNow << "Dire_fsr_u1new_22->" << i << "hard&" << -i;
    string n = nameNow.str();
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FF(i, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResA";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i, 1, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResB";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i,-1, true, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    nameNow.str("");
    nameNow << "Dire_fsr_u1new_22->" << i << "soft&" << -i;
    n = nameNow.str();
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FF(i, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResA";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i, 1, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    n = nameNow.str() + "ResB";
    splittings.insert( make_pair( n, new Dire_fsr_u1new_A2FFres(i,-1, false, n, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
  }









    /*name = "Dire_fsr_u1new_22->15&15aResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 15, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->15&15bResA";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-15, 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->15&15aResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( 15, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->15&15bResB";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-15, -1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );*/
  }

  if (settingsPtr->flag("TimeShower:U1newShowerByQ")) {
    name = "Dire_fsr_u1new_1->1&22";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_Q2QA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_1->22&1";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_Q2AQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    /*name = "Dire_fsr_u1new_22->1&1a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->1&1b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->2&2a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->2&2b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->3&3a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->3&3b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->4&4a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->4&4b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->5&5a";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    name = "Dire_fsr_u1new_22->5&5b";
    splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FF(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
    for (int i=1; i < 6; ++i) {
      stringstream nameNow;
      nameNow << "Dire_fsr_u1new_22->" << i << "&" << i;
      name = nameNow.str() + "aResA";
      splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( i, 1, name, order,
        settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
        infoPtr, direInfoPtr, slhaInterfacePtr)) );
      name = nameNow.str() + "bResA";
      splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-i, 1, name, order,
        settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
        infoPtr, direInfoPtr, slhaInterfacePtr)) );
      name = nameNow.str() + "aResB";
      splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres( i, -1, name, order,
        settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
        infoPtr, direInfoPtr, slhaInterfacePtr)) );
      name = nameNow.str() + "bResB";
      splittings.insert( make_pair( name, new Dire_fsr_u1new_A2FFres(-i, -1, name, order,
        settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
        infoPtr, direInfoPtr, slhaInterfacePtr)) );
    }*/
  }

  // Read more kernels.
  if (hasExternalHook && hooksPtr->canLoadFSRKernels())
    hooksPtr->doLoadFSRKernels(splittings);

  // Done.
}

//--------------------------------------------------------------------------

void DireSplittingLibrary::initISR() {

  /********************* ISR off Drell-Yan ****************************/

  // Add corrections to the LO splitting kernel.
  // order  = 0 -> A1, B1
  // order  = 1 -> A1, A2, B1
  // order  = 2 -> A1, A2, A3, B1
  // order  = 3 -> A1, A2, A3, B1, B2
  int order = settingsPtr->mode("DireSpace:kernelOrder");
  string name = "";

  // QCD splittings.
  if (settingsPtr->flag("SpaceShower:QCDshower")) {
    // Q -> Q G, soft and collinear part.
    name = "Dire_isr_qcd_1->1&21";
    splittings.insert( make_pair( name, new Dire_isr_qcd_Q2QG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> Q Q~ (regular DGLAP kernel)
    name = "Dire_isr_qcd_21->1&1";
    splittings.insert( make_pair( name, new Dire_isr_qcd_G2QQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part.
    name = "Dire_isr_qcd_21->21&21a";
    splittings.insert( make_pair( name, new Dire_isr_qcd_G2GG1( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_qcd_21->21&21b";
    splittings.insert( make_pair( name, new Dire_isr_qcd_G2GG2( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> G Q (regular DGLAP kernel)
    name = "Dire_isr_qcd_1->21&1";
    splittings.insert( make_pair( name, new Dire_isr_qcd_Q2GQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Q' Q Q'bar (pure NLO kernel)
    name = "Dire_isr_qcd_1->2&1&2";
    splittings.insert( make_pair( name, new Dire_isr_qcd_Q2qQqbarDist( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> Qbar Q Q (pure NLO kernel)
    name = "Dire_isr_qcd_1->1&1&1";
    splittings.insert( make_pair( name, new Dire_isr_qcd_Q2QbarQQId( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  }

  /*// QCD splittings.
  if (settingsPtr->flag("SpaceShower:QCDshower")) {
    // Q -> Q G, soft and collinear part.
    name = "CS_isr_qcd_1->1&21";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2QG( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> Q Q~ (regular DGLAP kernel)
    name = "CS_isr_qcd_21->1&1";
    splittings.insert( make_pair( name, new CS_isr_qcd_G2QQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // G -> G G, soft part.
    name = "CS_isr_qcd_21->21&21a";
    splittings.insert( make_pair( name, new CS_isr_qcd_G2GG1( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_21->21&21b";
    splittings.insert( make_pair( name, new CS_isr_qcd_G2GG2( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // Q -> G Q (regular DGLAP kernel)
    name = "CS_isr_qcd_1->21&1a";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ( 1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_1->21&1b";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ(-1, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_2->21&2a";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ( 2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_2->21&2b";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ(-2, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_3->21&3a";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ( 3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_3->21&3b";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ(-3, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_4->21&4a";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ( 4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_4->21&4b";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ(-4, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_5->21&5a";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ( 5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
    name = "CS_isr_qcd_5->21&5b";
    splittings.insert( make_pair( name, new CS_isr_qcd_Q2GQ(-5, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr)) );
  }*/

  // QED splittings
  if (settingsPtr->flag("SpaceShower:QEDshowerByQ")) {
    // Q -> Q A, soft and collinear part.
    name = "Dire_isr_qed_1->1&22";
    splittings.insert( make_pair( name, new Dire_isr_qed_Q2QA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    /*// Q -> A Q (regular DGLAP kernel)
    name = "Dire_isr_qed_1->22&1";
    splittings.insert( make_pair( name, new Dire_isr_qed_Q2AQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // A -> Q Q~ (regular DGLAP kernel)
    name = "Dire_isr_qed_22->1&1";
    splittings.insert( make_pair( name, new Dire_isr_qed_A2QQ( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );*/
  }

  if (settingsPtr->flag("SpaceShower:QEDshowerByL")) {
    // L -> L A, soft and collinear part.
    name = "Dire_isr_qed_11->11&22";
    splittings.insert( make_pair( name, new Dire_isr_qed_L2LA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    /*// L -> A L (regular DGLAP kernel)
    name = "Dire_isr_qed_11->22&11";
    splittings.insert( make_pair( name, new Dire_isr_qed_L2AL( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    // A -> L L~ (regular DGLAP kernel)
    name = "Dire_isr_qed_22->11&11";
    splittings.insert( make_pair( name, new Dire_isr_qed_A2LL( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );*/
    //name = "Dire_isr_qed_11->11&e&ebar";
    //splittings.insert( make_pair( name, new Dire_isr_qed_L2Lffbar( 11, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    //name = "Dire_isr_qed_11->11&ebar&e";
    //splittings.insert( make_pair( name, new Dire_isr_qed_L2Lffbar(-11, name, order,
    //  settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
  }

  // EW splittings
  if (settingsPtr->flag("SpaceShower:EWshowerByQ")) {
    name = "Dire_isr_ew_d->d&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(1,1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_isr_ew_dbar->dbar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-1,-1,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_u->u&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(2,2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_ubar->ubar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-2,-2,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_s->s&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(3,3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_sbar->sbar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-3,-3,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_c->c&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(4,4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_cbar->cbar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-4,-4,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_b->b&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(5,5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_bbar->bbar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-5,-5,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_t->t&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(6,6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_tbar->tbar&z";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-6,-6,23, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_isr_ew_d->u&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(1,2,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );

    name = "Dire_isr_ew_s->c&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(3,4,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_b->t&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(5,6,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_ubar->dbar&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-2,-1,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_cbar->sbar&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-4,-3,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );
    name = "Dire_isr_ew_tbar->bbar&w-";
    splittings.insert( make_pair(name, new Dire_isr_ew_F2FV(-6,-5,-24, name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );


  }

  /*// EW splittings
  // Q -> Q Z
  name = "Dire_isr_ew_1->1&23";
  splittings.insert( make_pair( name, new Dire_isr_ew_Q2QZ( name, order,
    settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr, infoPtr, direInfoPtr)) );*/

  // New U(1) splittings
  if (settingsPtr->flag("SpaceShower:U1newShowerByL")) {
    name = "Dire_isr_u1new_11->11&22";
    splittings.insert( make_pair( name, new Dire_isr_u1new_L2LA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
  }

  if (settingsPtr->flag("SpaceShower:U1newShowerByQ")) {
    name = "Dire_isr_u1new_1->1&22";
    splittings.insert( make_pair( name, new Dire_isr_u1new_Q2QA( name, order,
      settingsPtr, particleDataPtr, rndmPtr, beamAPtr, beamBPtr, coupSMPtr,
      infoPtr, direInfoPtr, slhaInterfacePtr)) );
  }

  // Read more kernels.
  if (hasExternalHook && hooksPtr->canLoadISRKernels())
    hooksPtr->doLoadISRKernels(splittings);

  // Done.
}

//--------------------------------------------------------------------------

// Overload index operator to access element of splitting vector.

DireSplitting* DireSplittingLibrary::operator[](string id) {
  if (splittings.find(id) != splittings.end()) return splittings[id];
  return NULL;
}

const DireSplitting* DireSplittingLibrary::operator[](string id) const {
  if (splittings.find(id) != splittings.end()) return splittings.at(id);
  return NULL;
}

//--------------------------------------------------------------------------

// Generate identifier of radiator before the splitting

vector<int> DireSplittingLibrary::getSplittingRadBefID(const Event& event,
  int rad, int emt) {

  vector<int>radBefIDs;
  /*for ( std::unordered_map<string,DireSplitting*>::iterator
    it = splittings.begin();
    it != splittings.end(); ++it ) {
    int idNow = it->second->radBefID(event[rad].id(), event[emt].id());
    if (idNow != 0) radBefIDs.push_back(idNow);
  }*/

  for (size_t i = 0; i < splittings.size(); ++i) {
    int idNow = splittingsVec[i]->radBefID(event[rad].id(), event[emt].id());
    if (idNow != 0) radBefIDs.push_back(idNow);
  }

  return radBefIDs;

}

//--------------------------------------------------------------------------

// Generate name for a splitting

vector<string> DireSplittingLibrary::getSplittingName(const Event& event,
  int rad, int emt) {

  vector<string> names;
  /*for ( std::unordered_map<string,DireSplitting*>::iterator
    it = splittings.begin();
    it != splittings.end(); ++it ) {

    int type = event[rad].isFinal() ? 1 :-1;
    if (type < 0 && it->first.find("isr") == string::npos) continue;
    if (type > 0 && it->first.find("fsr") == string::npos) continue;

    // Find radiator before emission.
    int idNow = it->second->radBefID(event[rad].id(), event[emt].id());

    direInfoPtr->message(1) << __FILE__ << " " << __LINE__
    << " Found radBef id " << idNow << " in splitting " << it->first << endl;

    // Now check that after emission, we would find same flavors.
    vector <int> radAndEmt;
    if (idNow != 0) radAndEmt = it->second->radAndEmt(idNow,0);

    bool valid = false;
    if (radAndEmt.size() == 2) {
      if (radAndEmt[1] == event[emt].id())
        valid = true;
      if (event[emt].isQuark() && event[emt].colType() > 0
        && particleDataPtr->isQuark(radAndEmt[1]))
        valid = true;
      if (event[emt].isQuark() && event[emt].colType() < 0
        && radAndEmt[1] == 1)
        valid = true;
    }

    // Found valid splitting name.
    if (valid && idNow != 0) {
      direInfoPtr->message(1) << __FILE__ << " " << __LINE__
      << " Splitting " << it->first << " valid for "
      << idNow << " -->> "  << event[rad].id() << " " << event[emt].id()
      << endl;
      names.push_back(it->first);
    } else {
      direInfoPtr->message(1) << __FILE__ << " " << __LINE__
      << " Splitting " << it->first << " invalid for "
      << idNow << " -->> "  << event[rad].id() << " " << event[emt].id()
      << endl;
    }
  }*/

  for (size_t i=0; i < splittingsVec.size(); ++i) {

    int type = event[rad].isFinal() ? 1 :-1;
    string name = splittingsVec[i]->name();
    if (type < 0 && name.find("isr") == string::npos) continue;
    if (type > 0 && name.find("fsr") == string::npos) continue;

    // Find radiator before emission.
    int idNow = splittingsVec[i]->radBefID(event[rad].id(), event[emt].id());

    // Now check that after emission, we would find same flavors.
    vector <int> radAndEmt;
    if (idNow != 0) radAndEmt = splittingsVec[i]->radAndEmt(idNow,0);

    bool valid = false;
    if (radAndEmt.size() == 2) {
      if (radAndEmt[1] == event[emt].id())
        valid = true;
      // Short-hands for QCD radiation off quarks.
      if (event[emt].isQuark() && event[emt].colType() > 0
        && particleDataPtr->isQuark(radAndEmt[1]))
        valid = true;
      if (event[emt].isQuark() && event[emt].colType() < 0
        && particleDataPtr->isQuark(radAndEmt[1]))
        valid = true;
      if (event[emt].isQuark() && event[emt].colType() < 0
        && radAndEmt[1] == 1)
        valid = true;
      // Short-hands for QED-like radiation off quarks.
      if (event[emt].isQuark() && event[rad].colType() == 0
        && particleDataPtr->isQuark(radAndEmt[1]))
        valid = true;
      if (event[emt].isQuark() && event[rad].colType() == 0
        && particleDataPtr->isQuark(radAndEmt[0]))
        valid = true;
    }

    //if (valid && idNow != 0) {
    //  direInfoPtr->message(1) << __FILE__ << " " << __LINE__
    //  << " Splitting " << name << " valid for "
    //  << idNow << " -->> "  << event[rad].id() << " " << event[emt].id()
    //  << endl;
    //} else {
    //  direInfoPtr->message(1) << __FILE__ << " " << __LINE__
    //  << " Splitting " << name << " invalid for "
    //  << idNow << " -->> "  << event[rad].id() << " " << event[emt].id()
    //  << endl;
    //  if (radAndEmt.size() == 2) direInfoPtr->message(1) << __FILE__ << " " << __LINE__
    //  << radAndEmt[0] << " " << radAndEmt[1]
    //  << endl;
    //}

    // Found valid splitting name.
    if (valid && idNow != 0) names.push_back(name);

  }

  return names;

}

//--------------------------------------------------------------------------

// Generate name for a splitting

vector<string> DireSplittingLibrary::getSplittingName(const Event& event,
  int rad, int emt1, int emt2) {

  vector<string> names;
  /*for ( std::unordered_map<string,DireSplitting*>::iterator
    it = splittings.begin();
    it != splittings.end(); ++it ) {

    int type = event[rad].isFinal() ? 1 :-1;
    if (type < 0 && it->first.find("isr") == string::npos) continue;
    if (type > 0 && it->first.find("fsr") == string::npos) continue;

    // Find radiator before emission.
    int idNow = it->second->radBefID(event[rad].id(), event[emt1].id());

    // Now check that after emission, we would find same flavors.
    vector <int> radAndEmt;
    if (idNow != 0) radAndEmt = it->second->radAndEmt(idNow,0);

    bool valid = false;
    if ( emt2 < 0 && radAndEmt.size() == 2) {
      if (radAndEmt[1] == event[emt1].id())
        valid = true;
      if (event[emt1].isQuark() && event[emt1].colType() > 0
        && radAndEmt[1] == 1)
        valid = true;
      if (event[emt1].isQuark() && event[emt1].colType() < 0
        && radAndEmt[1] == 1)
        valid = true;
    }
    if ( emt2 > 0 && radAndEmt.size() == 3) {
      if ( radAndEmt[1] == event[emt1].id()
        && radAndEmt[2] == event[emt2].id())
        valid = true;
    }

    // Found valid splitting name.
    if (valid && idNow != 0) names.push_back(it->first);
  }*/

  for (size_t i=0; i < splittingsVec.size(); ++i) {

    int type = event[rad].isFinal() ? 1 :-1;
    string name = splittingsVec[i]->name();
    if (type < 0 && name.find("isr") == string::npos) continue;
    if (type > 0 && name.find("fsr") == string::npos) continue;

    // Find radiator before emission.
    int idNow = splittingsVec[i]->radBefID(event[rad].id(), event[emt1].id());

    // Now check that after emission, we would find same flavors.
    vector <int> radAndEmt;
    if (idNow != 0) radAndEmt = splittingsVec[i]->radAndEmt(idNow,0);

    bool valid = false;
    if ( emt2 < 0 && radAndEmt.size() == 2) {
      if (radAndEmt[1] == event[emt1].id())
        valid = true;
      if (event[emt1].isQuark() && event[emt1].colType() > 0
        && radAndEmt[1] == 1)
        valid = true;
      if (event[emt1].isQuark() && event[emt1].colType() < 0
        && radAndEmt[1] == 1)
        valid = true;
    }
    if ( emt2 > 0 && radAndEmt.size() == 3) {
      if ( radAndEmt[1] == event[emt1].id()
        && radAndEmt[2] == event[emt2].id())
        valid = true;
    }

    // Found valid splitting name.
    if (valid && idNow != 0) names.push_back(name);
  }

  return names;

}

/*//--------------------------------------------------------------------------

// Return the total number of emissions for a particular splitting 

int DireSplittingLibrary::nEmissions( string name ) {

  std::unordered_map<string, DireSplitting*>::iterator
    it = splittings.find(name);
  if (it != splittings.end() && abs(it->second->kinMap()) == 2) return 2;

  // Flavour-changing 1->3 splitting for FSR implemented.
  if ( name.find("Dire_fsr_qcd_1->2&1&2") != string::npos ) return 2;

  // Flavour-preserving 1->3 splitting for FSR implemented.
  if ( name.find("Dire_fsr_qcd_1->1&1&1") != string::npos ) return 2;

  // Flavour-changing 1->3 splitting for FSR implemented.
  if ( name.find("Dire_isr_qcd_1->2&1&2") != string::npos ) return 2;

  // Flavour-preserving 1->3 splitting for FSR implemented.
  if ( name.find("Dire_isr_qcd_1->1&1&1") != string::npos ) return 2;

  // Default is one emission.
  return 1; 

}*/

//==========================================================================

} // end namespace Pythia8
