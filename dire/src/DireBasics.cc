
#include "Dire/DireBasics.h"

namespace Pythia8 {

//--------------------------------------------------------------------------

// Function to hash string into long integer.

ulong shash(const std::string& str) {
    ulong hash = 5381;
    for (size_t i = 0; i < str.size(); ++i)
        hash = 33 * hash + (unsigned char)str[i];
    return hash;
}

//--------------------------------------------------------------------------

// Helper function to calculate dilogarithm.

double polev(double x,double* coef,int N ) {
  double ans;
  int i;
  double *p;

  p = coef;
  ans = *p++;
  i = N;
    
  do
    ans = ans * x  +  *p++;
  while( --i );
    
  return ans;
}
  
//--------------------------------------------------------------------------

// Function to calculate dilogarithm.

double dilog(double x) {

  static double cof_A[8] = {
    4.65128586073990045278E-5,
    7.31589045238094711071E-3,
    1.33847639578309018650E-1,
    8.79691311754530315341E-1,
    2.71149851196553469920E0,
    4.25697156008121755724E0,
    3.29771340985225106936E0,
    1.00000000000000000126E0,
  };
  static double cof_B[8] = {
    6.90990488912553276999E-4,
    2.54043763932544379113E-2,
    2.82974860602568089943E-1,
    1.41172597751831069617E0,
    3.63800533345137075418E0,
    5.03278880143316990390E0,
    3.54771340985225096217E0,
    9.99999999999999998740E-1,
  };

  if( x >1. ) {
    return -dilog(1./x)+M_PI*M_PI/3.-0.5*pow2(log(x));
  }

  x = 1.-x;
  double w, y, z;
  int flag;
  if( x == 1.0 )
    return( 0.0 );
  if( x == 0.0 )
    return( M_PI*M_PI/6.0 );
    
  flag = 0;
    
  if( x > 2.0 ) {
    x = 1.0/x;
    flag |= 2;
  }
    
  if( x > 1.5 ) {
    w = (1.0/x) - 1.0;
    flag |= 2;
  }
    
  else if( x < 0.5 ) {
    w = -x;
    flag |= 1;
  }
    
  else
    w = x - 1.0;
    
  y = -w * polev( w, cof_A, 7) / polev( w, cof_B, 7 );
    
  if( flag & 1 )
    y = (M_PI * M_PI)/6.0  - log(x) * log(1.0-x) - y;
    
  if( flag & 2 ) {
    z = log(x);
    y = -0.5 * z * z  -  y;
  }
    
  return y;

}

double lABC(double a, double b, double c) { return pow2(a-b-c) - 4.*b*c;}
double bABC(double a, double b, double c) { 
  double ret = 0.;
  if      ((a-b-c) > 0.) ret = sqrt(lABC(a,b,c));
  else if ((a-b-c) < 0.) ret =-sqrt(lABC(a,b,c));
  else                   ret = 0.;
  return ret; }
double gABC(double a, double b, double c) { return 0.5*(a-b-c+bABC(a,b,c));}

int puppybort( string input, int iPuppy) {
  srand (time(NULL));
  if (iPuppy == 0) iPuppy = rand() % 7 + 1;
  cout << "\nSomething went terribly wrong in " << input << endl;
  cout << "\nMaybe this...\n" << endl;
  if (iPuppy == 1) {
    cout << "  __      _" << endl
         << "o'')}____//" << endl
         << " `_/      )" << endl
         << " (_(_/-(_/" << endl;
  } else if (iPuppy == 2) {
    cout << "    ___" << endl
         << " __/_  `.  .-\"\"\"-." << endl
         << " \\_,` | \\-'  /   )`-')" << endl
         << "  \"\") `\"`    \\  ((`\"`" << endl
         << " ___Y  ,    .'7 /|" << endl
         << "(_,___/...-` (_/_/" << endl;
  } else if (iPuppy == 3) {
    cout << "       /^-^\\         /^-----^\\" << endl
         << "      / o o \\        V  o o  V" << endl
         << "     /   Y   \\        |  Y  |" << endl
         << "     V \\ v / V         \\ Q /" << endl
         << "       / - \\           / - \\" << endl
         << "      /    |           |    \\" << endl
         << "(    /     |           |     \\     )" << endl
         << " ===/___) ||           || (___\\====" << endl;
  } else if (iPuppy == 4) {
    cout << "_     /)---(\\          /~~~\\" << endl
         << "\\\\   (/ . . \\)        /  .. \\" << endl
         << " \\\\__)-\\(*)/         (_,\\  |_)" << endl
         << " \\_       (_         /   \\@/    /^^^\\" << endl
         << " (___/-(____) _     /      \\   / . . \\" << endl
         << "              \\\\   /  `    |   V\\ Y /V" << endl
         << "               \\\\/  \\   | _\\    / - \\" << endl
         << "                \\   /__'|| \\\\_  |    \\" << endl
         << "                 \\_____)|_).\\_).||(__V" << endl;
  } else if (iPuppy == 5) {
    cout << "              ,-~~~~-," << endl
         << "        .-~~~;        ;~~~-." << endl
         << "       /    /          i\\    \\" << endl
         << "      {   .'{  O    O  }'.   }" << endl
         << "       `~`  { .-~~~~-. }  `~`" << endl
         << "            ;/        \\;" << endl
         << "           /'._  ()  _.'\\" << endl
         << "          /    `~~~~`    \\" << endl
         << "         ;                ;" << endl
         << "         {                }" << endl
         << "         {     }    {     }" << endl
         << "         {     }    {     }" << endl
         << "         /     \\    /     \\" << endl
         << "        { { {   }~~{   } } }" << endl
         << "         `~~~~~`    `~~~~~`" << endl
         << "           (`\"=======\"`)" << endl
         << "           (_.=======._)" << endl;
  } else if (iPuppy == 6) {
    cout << "                            ..,,,,,,,,,.. " << endl
         << "                     .,;%%%%%%%%%%%%%%%%%%%%;,. " << endl
         << "                   %%%%%%%%%%%%%%%%%%%%////%%%%%%, .,;%%;, " << endl
         << "            .,;%/,%%%%%/////%%%%%%%%%%%%%%////%%%%,%%//%%%, " << endl
         << "        .,;%%%%/,%%%///%%%%%%%%%%%%%%%%%%%%%%%%%%%%,////%%%%;, " << endl
         << "     .,%%%%%%//,%%%%%%%%%%%%%%%%@@%a%%%%%%%%%%%%%%%%,%%/%%%%%%%;, " << endl
         << "   .,%//%%%%//,%%%%///////%%%%%%%@@@%%%%%%///////%%%%,%%//%%%%%%%%, " << endl
         << " ,%%%%%///%%//,%%//%%%%%///%%%%%@@@%%%%%////%%%%%%%%%,/%%%%%%%%%%%%% " << endl
         << ".%%%%%%%%%////,%%%%%%%//%///%%%%@@@@%%%////%%/////%%%,/;%%%%%%%%/%%% " << endl
         << "%/%%%%%%%/////,%%%%///%%////%%%@@@@@%%%///%%/%%%%%//%,////%%%%//%%%' " << endl
         << "%//%%%%%//////,%/%a`  'a%///%%%@@@@@@%%////a`  'a%%%%,//%///%/%%%%% " << endl
         << "%///%%%%%%///,%%%%@@aa@@%//%%%@@@@S@@@%%///@@aa@@%%%%%,/%////%%%%% " << endl
         << "%%//%%%%%%%//,%%%%%///////%%%@S@@@@SS@@@%%/////%%%%%%%,%////%%%%%' " << endl
         << "%%//%%%%%%%//,%%%%/////%%@%@SS@@@@@@@S@@@@%%%%/////%%%,////%%%%%' " << endl
         << "`%/%%%%//%%//,%%%///%%%%@@@S@@@@@@@@@@@@@@@S%%%%////%%,///%%%%%' " << endl
         << "  %%%%//%%%%/,%%%%%%%%@@@@@@@@@@@@@@@@@@@@@SS@%%%%%%%%,//%%%%%' " << endl
         << "  `%%%//%%%%/,%%%%@%@@@@@@@@@@@@@@@@@@@@@@@@@S@@%%%%%,/////%%' " << endl
         << "   `%%%//%%%/,%%%@@@SS@@SSs@@@@@@@@@@@@@sSS@@@@@@%%%,//%%//%' " << endl
         << "    `%%%%%%/  %%S@@SS@@@@@Ss` .,,.    'sS@@@S@@@@%'  ///%/%' " << endl
         << "      `%%%/    %SS@@@@SSS@@S.         .S@@SSS@@@@'    //%%' " << endl
         << "               /`S@@@@@@SSSSSs,     ,sSSSSS@@@@@' " << endl
         << "             %%//`@@@@@@@@@@@@@Ss,sS@@@@@@@@@@@'/ " << endl
         << "           %%%%@@00`@@@@@@@@@@@@@'@@@@@@@@@@@'//%% " << endl
         << "       %%%%%%a%@@@@000aaaaaaaaa00a00aaaaaaa00%@%%%%% " << endl
         << "    %%%%%%a%%@@@@@@@@@@000000000000000000@@@%@@%%%@%%% " << endl
         << " %%%%%%a%%@@@%@@@@@@@@@@@00000000000000@@@@@@@@@%@@%%@%% " << endl
         << "%%%aa%@@@@@@@@@@@@@@0000000000000000000000@@@@@@@@%@@@%%%% " << endl
         << "%%@@@@@@@@@@@@@@@00000000000000000000000000000@@@@@@@@@%%%%%"  << endl;
  } else if (iPuppy == 7) {
    cout << "                          _..___" << endl
         << "                      _..xxxxxxxllllxxxx...___" << endl
         << "                   _.ssssssxxxxxxxxsssxxxxxxxxLlllxxx..._" << endl
         << "               _.ssssSSSSsssssSSSSSSSSSsxxxxxxxXxxxXxxxXxlll++._" << endl
         << "          _.sdSSSSSSSSSSSSSSSSSSSSSSsxxxxxxxXxxxXxxxXxxxXxxxxx+++." << endl
         << "       .dSSSSS$$$$$S$$SSSSSSS$$888SsxxxXxxxxXxxxXxxxxXxxxXxxxxxxxxx." << endl
         << "      j$$$$SS$$$$$$$$$$$S$SS$$888sxxxxXxxxxXxxxxXxxxxXxxXxxXxxxxxxxxx." << endl
         << "      $$$$SS$$$$$$$$$$$$$$$$$$88xxxxXXxxxXxxxxxXXxxxxXxxxXxxxXxxxxxxxx." << endl
         << "      Y$$$$SS$$$$$$$$$$$$$$$$8SsxxxxXxxXXxxxxxXXxxxxxxXxxxXxxxXxxxxS$xxh." << endl
         << "       `$$$S$S$$$$$$$$$$$$$$$SsxxxxxxxxxxxxxxxXxxxxxxxXxxxXxxxXXxxxS$$Sxx." << endl
         << "        .$$$SS$$$$$$$$$$$$$$SsxxxxxxxxxxxxxxxXxxxxxxxxXxxxXXxxXxxXxsS$$$xx." << endl
         << "        xSS$$$S$$$$$$$$$$$$SsxXxxxxxxxxxxxxxXxxxxxxxxxxXxxxxXXXxxxXxS$$$$xx." << endl
         << "       .+xSS$$$$$$$$$$$$$$$SxxxxxxxXxxxxxxxxxXXXxxxxxxxXXxxxXxxxxxxxsS$$$$xx." << endl
         << "      .++++SS$$$$$$$$$$$$$$SxXxxxxxxxxxxxxxxxxxXXXxxxxxxXxxxXxxxssSxsS$$$$$xx" << endl
         << "     .+++++xxSS$$$$$$$$$$$SxxxxxXxxxxxxxxxssSSxxxxXxxxxxxxxXXxxsSx$Ssx$$$$$Sx." << endl
         << "    .++++xxxxxxSS$$$$$$$$SxxxxsxxxxxxxxssS$$$SSsxxxxSsxxxssxxxsSsxS$SsS$$$$$Xx." << endl
         << "   .++++x++xxxxxxSS$$$$SxxxxxsSssxxxxxxxxsS$$$SssxxsSSsxsSSssSSsxxS$$SsS$$$$$xx" << endl
         << "   ++++++x+x++xxxxxxxxxxxxxssS$$SssssssssSS$$$$$SssSSSSsS$$SSSsxxsS$$SssS$$$$xx" << endl
         << "  .+++x++xxxx++xxxxxxxXxxxxsS$$$$SSSyysSS$$$$$$$$$$$$$$$$$$$$$$SSyS$$$$S$$$$$xx" << endl
         << " .++++++x+xx+x++xxxxxxxXxxsS$$$$$$d8,,n88b$$S$$$$$SSS$$$$$$$SS$$d,8b$$$$$$$$$xx" << endl
         << ".++++++x+xxXx++xxxxxxxxXxxxsS$$S$$$Y##880P$$$$$$$$SSSSSSSSSSSSSSY##P$$s'Y$$$$x'" << endl
         << "++++++++xxxxXx++xxxxxxxXxxxxsS$SS$$$$$$$$$$$$$$SSS$$$$d8####b$$SS$$$Ssx  `\"\"\"'" << endl
         << "+++++x+x+xxxXXx+x+xxxxxxXxxxxS$$$S$$$$$$$$S$$$SS$$$d#8$$8$8$8##8bSS$$sx" << endl
         << "++++x++xxxxxxXXXx+++xxxxxXxxxxS$S$$$$$$$$$$$SS$$d#8$$8$8$$8$8$$8#8b$Sx'" << endl
         << "+x+++xxxxxxxxXxXxx++xxxxxxXxxxxS$$$$$$S$$$SS$$888$$$$$8$8#8$$$$$8#P$S'" << endl
         << "+++x+xxxxxxxxxXxXxxx+xxxxxxXXxxsS$$$$$$$SS$$$88$$$$$$S$SS#SS$$$$$Y$$S" << endl
         << "+x++xxxxxxxxxxxXxXxxxxxxxxxxXXxssS$$$SSS$$$88$$$$$$SS$$SS#$SS$$$$$$$Sl" << endl
         << "+xxxxXxxxxxxxxxxXxXxxxxxxxxxXXxXxsSSS$$$$68$$$$$$$S$$SSS$#$$$$S$$$$$$$" << endl
         << "xxxxxxxxxXxxxxxxxxxXXXxxxxxxxxxXXxsS$$$$$9$$$$$$$$$$$$$$d#$$$$$$$$$$$$" << endl
         << "xxxxxxxxxxxxxxxxxxxxXxXXxxxxxxxxxXXS$$$$$$$$$$$$$$$$$$d88##6$$$$$$$$$'" << endl
         << "xxxxxxxXxxxXxxxxxxxxxxXxxxxxxxxxXXXSS$$$$$$$$$$$$$$$$d8888##b$$$$$$S'" << endl
         << "xxXxxxxxxxXxxxXxxxxxxxxxxXxxxxxxxXXXXS$$$$$$$$$$$$$d88888888##b$$$P'" << endl
         << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXXSS$$$$$$$$$$$$$Y8888P$$$$Y\"'" << endl
         << "xXxxxxXxxxxxxXxxxxxXxxxxxxxxxxxxxXxxxxXXsSS$$$$$$$$$$$$SSSS._" << endl
         << "xxxxxxxxxxxxxxxXxxxxxxxxxxxxxxxxxxxXxxxxxXXSSSSSSSSSSSssxx+++;" << endl
         << "xxxxxxxxxxxxxxxxxxXxXxxxXxxxxxxxx+xxXxxxxxxxsssssssssxxxxxx+'" << endl
         << "xxxxxXxxxxxxXxxxxxxxxxXxxXxxxxxx+xxxxxXXxxxxxxxxxxxxxxxxxxx." << endl
         << "xxXxxxxxxxxxxxxxxxXxxxxxxXxxxXxxxx+xxx+xxXXxxxxxxxxxxxxxxXxx." << endl
         << "xxxxxxxxxxxxxxxxxxxxxxXxxxxxxxxxxxx+x+xxxxxXXxxXxxxxxxxXxx++xx" << endl
         << "xxxxxxxxxxXxxxxxxxXxxxxxxxxxxxxxxx+xxx+xx+xxxXxxxxxxxxX+++++xx" << endl
         << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxXxxxXxxxX++x++++." << endl
         << "xxxxXxxxxxxxxxxxxxXxxxxxxxxxxxxxxxx+xxxx++xxxxxXxxxXX+++++++++." << endl
         << "xxxxxxxxxxxxxXxxxxxxxxxXxxxxxxxxxxxxxxxxxxx+xxxx+xxX+x++++++++x." << endl
         << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx+xxxxx++xxxXxx+++++xx++xx." << endl
         << "xxxxxxxxXxxxxxxxxxxxxxxxxxxxxxxxXxxxxxxxxxxxxxx+xXxx+x++++x+xxxxx." << endl
         << "xxxxxxxxxxxxXxxxxxXxxxxxxxxXxxxxxxxxxxxxxxxxXxxxXXxxxxx++xxxxx+xxxx." << endl
         << "xxxxXxxxxxxxxxxxxxxxxxxxxxxxxxxxxXxxxxxxXxxxxxxxXxxxxx++++++++xxx+xxxx." << endl
         << "xxxxxxxxxxxxxxxxxxxxxxXxxxxxxxxxxxxxxxxxxxxxxxxxXxxxxxxx++++++xx+xxx+xxx." << endl;
  } else {
    cout << "No puppies found. All hope is lost." << endl;
  }
  cout << "\n... will help?\n" << endl;
  abort();
}

//==========================================================================

bool DireEventUtils::checkSIJ(const Event& e, double minSIJ) {
  //return true;
  double sijmin=1e10;
  for (int i=0; i < e.size(); ++i) {
    if (!e[i].isFinal() && e[i].mother1() !=1 && e[i].mother1() !=2) continue;
    for (int j=0; j < e.size(); ++j) {
      if (i==j) continue;
      if (!e[j].isFinal() && e[j].mother1() !=1 && e[j].mother1() !=2) continue;
      sijmin=min(sijmin,abs(2.*e[i].p()*e[j].p()));
    }
  }
  return (sijmin>minSIJ);
}

//--------------------------------------------------------------------------

void DireEventUtils::printSI(const Event& e) {
  for (int i=0; i < e.size(); ++i) {
    if (!e[i].isFinal() && e[i].mother1() !=1 && e[i].mother1() !=2) continue;
    cout << "  [" << e[i].isFinal()
         << " s("<< i << ")=" 
         << e[i].p().m2Calc() << "],\n";
  }
}

//--------------------------------------------------------------------------

void DireEventUtils::printSIJ(const Event& e) {
  for (int i=0; i < e.size(); ++i) {
    if (!e[i].isFinal() && e[i].mother1() !=1 && e[i].mother1() !=2) continue;
    for (int j=0; j < e.size(); ++j) {
      if (i==j) continue;
      if (!e[j].isFinal() && e[j].mother1() !=1 && e[j].mother1() !=2) continue;
      cout << "  [" << e[i].isFinal() << e[j].isFinal()
           << " s("<< i << "," << j << ")=" 
           << 2.*e[i].p()*e[j].p() << "],\n";
    }
  } 
}

//--------------------------------------------------------------------------

string DireEventUtils::printSIJstring(const Event& e) {
  ostringstream os;
  for (int i=0; i < e.size(); ++i) {
    if (!e[i].isFinal() && e[i].mother1() !=1 && e[i].mother1() !=2) continue;
    for (int j=0; j < e.size(); ++j) {
      if (i==j) continue;
      if (!e[j].isFinal() && e[j].mother1() !=1 && e[j].mother1() !=2) continue;
      os << "  [" << e[i].isFinal() << e[j].isFinal()
           << " s("<< i << "," << j << ")=" 
           << 2.*e[i].p()*e[j].p() << "],\n";
    }
  } 
  return os.str();
}

//--------------------------------------------------------------------------

string DireEventUtils::listEvent(const Event& e) {
  ostringstream os;
  Vec4 pSum;
  double chargeSum = 0.;
  int prec = 5;
  for (int i = 0; i < e.size(); ++i) {
    const Particle& pt = e[i];
    // Basic line for a particle, always printed.
    os   << setw(6) << i << setw(11) << pt.id() << "  " << left
         << setw(18) << pt.nameWithStatus(18) << right << setw(4)
         << pt.status() << setw(6) << pt.mother1() << setw(6)
         << pt.mother2() << setw(6) << pt.daughter1() << setw(6)
         << pt.daughter2() << setw(6) << pt.col() << setw(6) << pt.acol()
         << scientific << setprecision(prec)
         << setw(8+prec) << pt.px() << setw(8+prec) << pt.py()
         << setw(8+prec) << pt.pz() << setw(8+prec) << pt.e()
         << setw(8+prec) << pt.mCalc() << "\n";
    if (pt.status() > 0) {
      pSum += pt.p();
      chargeSum += pt.charge();
    }
  }
  // Line with sum charge, momentum, energy and invariant mass.
  os   << fixed << setprecision(3) << "                                   "
       << "Charge sum:" << setw(7) << chargeSum << "           Momentum sum:"
       << scientific << setprecision(prec)
       << setw(8+prec) << pSum.px() << setw(8+prec) << pSum.py()
       << setw(8+prec) << pSum.pz() << setw(8+prec) << pSum.e()
       << setw(8+prec) << pSum.mCalc() << "\n";
  return os.str();
}

//--------------------------------------------------------------------------

Event DireEventUtils::makeHardEvent( int iSys, const Event& state,
  bool isProcess) {

  // Do nothing for empty event.
  if (state.size() == 0) return state;

  bool hasSystems = !isProcess && partonSystemsPtr->sizeSys() > 0;
  int sizeSys     = (hasSystems) ? partonSystemsPtr->sizeSys() : 1;

  Event outputEvt;
  outputEvt.clear();
  outputEvt.init( "(hard process-modified)", particleDataPtr );

  int in1 = 0;
  for ( int i = state.size()-1; i > 0; --i)
    if ( state[i].mother1() == 1 && state[i].mother2() == 0
      && (!hasSystems || partonSystemsPtr->getSystemOf(i,true) == iSys))
      {in1 = i; break;}
  if (in1 == 0) in1 = partonSystemsPtr->getInA(iSys);

  int in2 = 0;
  for ( int i = state.size()-1; i > 0; --i)
    if ( state[i].mother1() == 2 && state[i].mother2() == 0
      && (!hasSystems || partonSystemsPtr->getSystemOf(i,true) == iSys))
      {in2 = i; break;}
  if (in2 == 0) in2 = partonSystemsPtr->getInB(iSys);

  // Keep track of MPI systems, so that we can later avoid attaching them to
  // the hard process.
  bool isMPIsystem
    =   (in1!=0 && state[in1].statusAbs() > 30 && state[in1].statusAbs() < 40)
     || (in2!=0 && state[in2].statusAbs() > 30 && state[in2].statusAbs() < 40);
  // First find obvious MPI particles by status code...
  vector<int> mpi;
  for ( int i = 0; i < state.size(); ++i)
    if (state[i].statusAbs() > 30 && state[i].statusAbs() < 40)
      mpi.push_back(i);
  // ... then find all particles coming from these MPI progenitors.
  for ( int i = 0; i < state.size(); ++i) {
    if (find(mpi.begin(), mpi.end(), i) != mpi.end() ) continue;
    bool isMPI = false;
    for (size_t impi = 0; impi < mpi.size(); ++impi)
     if (state[i].isAncestor(mpi[impi])) isMPI =true;
    if (isMPI) mpi.push_back(i);
  }
  // ... then mark all particles in systems containing MPI particles as
  // MPI particles as well.
  if (hasSystems) {
    for (size_t impi = 0; impi < mpi.size(); ++impi) {
      int iMPIsys    = partonSystemsPtr->getSystemOf(mpi[impi],true);
      if (iMPIsys<0) continue;
      int sizeSysNow = partonSystemsPtr->sizeAll(iMPIsys);
      for (int i = 0; i < sizeSysNow; ++i){
        int iNow = partonSystemsPtr->getAll(iMPIsys,i);
        if (find(mpi.begin(), mpi.end(), iNow) != mpi.end() ) continue;
        else mpi.push_back(iNow);
      }
    }
    // Flag the system as MPI if it contains any MPI particles.
    int nInSys = partonSystemsPtr->sizeAll(iSys);
    for (int iInSys = 0; iInSys < nInSys; ++iInSys){
      int iNow = partonSystemsPtr->getAll(iSys,iInSys);
      if (find(mpi.begin(), mpi.end(), iNow) != mpi.end()) isMPIsystem = true;
    }
  }

  // Some diffractive topologies are not handled correctly, since 
  // the beams are not found. Even if they were, momentum checks would
  // fail, since the beams are not on z-axis in this case. Thus, skip
  // problematic final states as well.
  vector<int> pskip;
  for ( int i = 0; i < state.size(); ++i)
    if (state[i].statusAbs() < 20 && state[i].statusAbs() > 12)
      pskip.push_back(i);

  // If no incoming particles have been found, try to find them in other
  // systems, e.g. if the current system arose from a resonance decay.
  bool resonantIncoming = false;
  if ( in1 == 0 && in2 == 0 ) {
    int iParentInOther = 0;
    int nSys = partonSystemsPtr->sizeAll(iSys);
    for (int iInSys = 0; iInSys < nSys; ++iInSys){
      int iNow = partonSystemsPtr->getAll(iSys,iInSys);
      for (int iOtherSys = 0; iOtherSys < sizeSys; ++iOtherSys){
        if (iOtherSys == iSys) continue;
        int nOtherSys = partonSystemsPtr->sizeAll(iOtherSys);
        for (int iInOtherSys = 0; iInOtherSys < nOtherSys; ++iInOtherSys){
          int iOtherNow = partonSystemsPtr->getAll(iOtherSys,iInOtherSys);
          if (state[iNow].isAncestor(iOtherNow)) {
            iParentInOther = iOtherNow;
          }
        }
      }
    }
    in1 = iParentInOther;
    if (iParentInOther) resonantIncoming = true;
  }

  int in1ForRes(0), in2ForRes(0);
  if (hasSystems) {
    int iSysIn1    = partonSystemsPtr->getSystemOf(in1,true);
    int iMother    = state[in1].mother1();
    if ( in1 == partonSystemsPtr->getInA(iSysIn1)
      || in1 == partonSystemsPtr->getInB(iSysIn1))
      iMother = in1;
    int iSysMother = max(0,partonSystemsPtr->getSystemOf(iMother,true));
    while (!partonSystemsPtr->hasInAB(iSysMother) && iSysMother != 0) {
      iMother    = state[iMother].mother1();
      iSysMother = partonSystemsPtr->getSystemOf(iMother,true);
    }
    in1ForRes = partonSystemsPtr->getInA(iSysMother); 
    in2ForRes = partonSystemsPtr->getInB(iSysMother); 
  } else {
    in1ForRes = state[in1].mother1();
    in2ForRes = state[in1].mother2();
  }

  // Attach the beam particles and incoming hard particles to the event.
  // Resonances decay systems have to be treated separately, since
  // the incoming particles are not at fixed position in the input event.
  vector<int> alreadyAttached;
  int iBeamAPos =      1;
  int iBeamBPos =      2;
  int iIncomingAPos = (!resonantIncoming)? in1 : in1ForRes;
  int iIncomingBPos = (!resonantIncoming)? in2 : in2ForRes;

  outputEvt.append(state[0]);
  alreadyAttached.push_back(0);
  int beamA = outputEvt.append(state[iBeamAPos]);
  alreadyAttached.push_back(iBeamAPos);
  outputEvt[beamA].mothers(0,0);
  outputEvt[beamA].status(-12);
  int beamB = outputEvt.append(state[iBeamBPos]);
  alreadyAttached.push_back(iBeamBPos);
  outputEvt[beamB].mothers(0,0);
  outputEvt[beamB].status(-12);

  int i1(-1), i2(-1);
  if (iIncomingAPos > 0) {
    i1 = outputEvt.append(state[iIncomingAPos]);
    alreadyAttached.push_back(iIncomingAPos);
    outputEvt[i1].mothers(beamA,0);
    outputEvt[i1].status(-21);
    outputEvt[i1].daughters(0,0);
    outputEvt[beamA].daughters(i1,0);
  }
  if (iIncomingBPos > 0) {
    i2 = outputEvt.append(state[iIncomingBPos]);
    alreadyAttached.push_back(iIncomingBPos);
    outputEvt[i2].mothers(beamB,0);
    outputEvt[i2].status(-21);
    outputEvt[i2].daughters(0,0);
    outputEvt[beamB].daughters(i2,0);
  }

  if (resonantIncoming) {

    // Now append the resonance as intermediate particle.
    int iRes = outputEvt.append(state[in1]);
    alreadyAttached.push_back(in1);
    outputEvt[iRes].mothers(i1,i2);
    outputEvt[iRes].daughters(0,0);
    outputEvt[iRes].status(-22);
    outputEvt[i1].daughters(iRes,0);
    outputEvt[i2].daughters(iRes,0);

    // Now attach particles in other systems, e.g. additional radiation
    // in resonance production system.
    int iResDecSys = partonSystemsPtr->getSystemOf(in1,true);
    for (int iOtherSys = 0; iOtherSys < iResDecSys; ++iOtherSys){
      if (iOtherSys != 0) continue;
      if (iOtherSys == iSys) continue;
      int nOtherSys = partonSystemsPtr->sizeAll(iOtherSys);
      for (int iInOtherSys = 0; iInOtherSys < nOtherSys; ++iInOtherSys){
        int iOtherNow = partonSystemsPtr->getAll(iOtherSys,iInOtherSys);
        if (find(mpi.begin(), mpi.end(), iOtherNow) != mpi.end())
          continue;
        if (find(pskip.begin(), pskip.end(), iOtherNow) != pskip.end())
          continue;
        if (state[iOtherNow].isFinal()) {
          int iNow = outputEvt.append(state[iOtherNow]);
          alreadyAttached.push_back(iOtherNow);
          outputEvt[iNow].mothers(i1,i2);
          outputEvt[iNow].daughters(0,0);
          outputEvt[iNow].status(23);
        }
      }
    }
    i1=iRes;
    i2=-1;
  }

  int sizeOld = outputEvt.size();
  for ( int i = 0; i < state.size(); ++i) {

    if (find(alreadyAttached.begin(), alreadyAttached.end(), i)
      != alreadyAttached.end() ) continue;
    if (!state[i].isFinal()) continue;

    // For test of hard system, skip all MPI systems.
    if (!isMPIsystem && find(mpi.begin(), mpi.end(), i) != mpi.end())
      continue;
    // Test each MPI system individually.
    else if (isMPIsystem && ( partonSystemsPtr->getSystemOf(i) != iSys
      || find(mpi.begin(), mpi.end(), i) == mpi.end()))
      continue;

    if (find(pskip.begin(), pskip.end(), i) != pskip.end())
      continue;

    int iN = outputEvt.append(state[i]);
    alreadyAttached.push_back(i);
    outputEvt[iN].daughters(0,0);
    outputEvt[iN].mothers(max(0,i1),max(0,i2));
    int status = (state[i].statusAbs() == 22) ? state[i].statusAbs() : 23;
    if ( particleDataPtr->isResonance(state[i].id()) ) status = 22;
    outputEvt[iN].status(status);
  }

  int iDaughter2 = (outputEvt.size() > sizeOld+1) ? outputEvt.size()-1 : 0;

  // Set daughters of initial particles.
  if (i1 > -1 && outputEvt.size() > sizeOld) 
    outputEvt[i1].daughters(sizeOld, iDaughter2);
  if (i2 > -1 && outputEvt.size() > sizeOld)
    outputEvt[i2].daughters(sizeOld, iDaughter2);

  return outputEvt;

}

//--------------------------------------------------------------------------

// Check colour/flavour correctness of state.

bool DireEventUtils::validMomentum( const Vec4& p, int id, int status,
  BeamParticle* beam, bool usePDFmass) {

  // Do not check light lepton momenta, since usually inconsistent
  // in input LHEFs
  if (abs(id)==1 || abs(id)==13) return true;

  // Check for INFs
  if ( std::isinf(p.e())  || std::isinf(p.px())
    || std::isinf(p.py()) || std::isinf(p.pz()))
    return false;
  // Check for NANs
  if ( std::isnan(p.e())  || std::isnan(p.px())
    || std::isnan(p.py()) || std::isnan(p.pz()))
    return false;

  // Check if particles is on mass shell
  double mNow = (status < 0) ? 0.
              : ((abs(id) < 6) ? getMass(id,2,beam,usePDFmass)
                               : getMass(id,1,beam,usePDFmass));

  if (status < 0 && useMassiveBeams
    && (abs(id) == 11 || abs(id) == 13 || abs(id) > 900000))
    mNow = getMass(id,1,beam,usePDFmass);

  mNow = sqrt(mNow);
  // Do not check on-shell condition for massive intermediate (!)
  // resonances. Assuming all non-SM particles are heavy here! 
  if ( particleDataPtr->isResonance(id) || abs(id) > 22) mNow = p.mCalc();
  double errMass = abs(p.mCalc() - mNow) / max( 1.0, p.e());
  if ( errMass > mTolErr ) return false;

  // Check for negative energies.
  if ( p.e() < 0. ) return false;

  // Done
  return true;

}

//-------------------------------------------------------------------------

// Check colour/flavour correctness of state.
bool DireEventUtils::validEvent( const Event& state, BeamParticle* beam,
  bool usePDFmass, bool isProcess, int iSysCheck ) {

  // Do nothing for empty event.
  if (state.size() == 0) return false;

  bool validColour  = true;
  bool validCharge  = true;
  bool validMomenta = true;

  bool hasSystems = !isProcess && partonSystemsPtr->sizeSys() > 0;
  int sizeSys     = (hasSystems) ? partonSystemsPtr->sizeSys() : 1;

  // Check for INFs
  for ( int i = 0; i < state.size(); ++i)
    if ( std::isinf(state[i].e())  || std::isinf(state[i].px())
      || std::isinf(state[i].py()) || std::isinf(state[i].pz()))
      return false;
  // Check for NANs
  for ( int i = 0; i < state.size(); ++i)
    if ( std::isnan(state[i].e())  || std::isnan(state[i].px())
      || std::isnan(state[i].py()) || std::isnan(state[i].pz()))
      return false;

  for (int iSys = 0; iSys < sizeSys; ++iSys) {

    if (iSysCheck >= 0 && iSys != iSysCheck) continue;

    // Done if the state is already broken.
    if (!validColour || !validCharge || !validMomenta) break;

    Event testEvt = makeHardEvent(iSys, state, isProcess);

    // Check if event is coloured
    for ( int i = 0; i < testEvt.size(); ++i)
     // Check colour of quarks
     if ( testEvt[i].isFinal() && testEvt[i].colType() == 1
            // No corresponding anticolour in final state
         && ( FindCol(testEvt[i].col(),vector<int>(1,i),testEvt,1) == 0
            // No corresponding colour in initial state
           && FindCol(testEvt[i].col(),vector<int>(1,i),testEvt,2) == 0 )) {
       validColour = false;
       break;
     // Check anticolour of antiquarks
     } else if ( testEvt[i].isFinal() && testEvt[i].colType() == -1
            // No corresponding colour in final state
         && ( FindCol(testEvt[i].acol(),vector<int>(1,i),testEvt,2) == 0
            // No corresponding anticolour in initial state
           && FindCol(testEvt[i].acol(),vector<int>(1,i),testEvt,1) == 0 )) {
       validColour = false;
       break;
     // No uncontracted colour (anticolour) charge of gluons
     } else if ( testEvt[i].isFinal() && testEvt[i].colType() == 2
            // No corresponding anticolour in final state
         && ( FindCol(testEvt[i].col(),vector<int>(1,i),testEvt,1) == 0
            // No corresponding colour in initial state
           && FindCol(testEvt[i].col(),vector<int>(1,i),testEvt,2) == 0 )
            // No corresponding colour in final state
         && ( FindCol(testEvt[i].acol(),vector<int>(1,i),testEvt,2) == 0
            // No corresponding anticolour in initial state
           && FindCol(testEvt[i].acol(),vector<int>(1,i),testEvt,1) == 0 )) {
       validColour = false;
       break;
     }

    for(int i = 0; i < testEvt.size(); ++i) {
      if ( !testEvt[i].isFinal()
        &&  testEvt[i].status() != -11
        &&  testEvt[i].status() != -12)  {
        if ( testEvt[i].colType() == 1 && testEvt[i].acol()>0)
          validColour = false;
        if ( testEvt[i].colType() ==-1 && testEvt[i].col() >0)
          validColour = false;
      }
      if ( testEvt[i].isFinal() ) {
        if ( testEvt[i].colType() == 1 && testEvt[i].acol()>0)
          validColour = false;
        if ( testEvt[i].colType() ==-1 && testEvt[i].col() >0)
          validColour = false;
      }
    }

    // Check charge sum in initial and final state
    double initCharge = 0.0;
    for(int i = 0; i < testEvt.size(); ++i)
      if ( !testEvt[i].isFinal()
        &&  testEvt[i].status() != -11
        &&  testEvt[i].status() != -12
        &&  testEvt[i].status() != -22)
        initCharge += testEvt[i].charge();
    double finalCharge = 0.0;
    for(int i = 0; i < testEvt.size(); ++i)
      if (testEvt[i].isFinal()) finalCharge += testEvt[i].charge();
    if (abs(initCharge-finalCharge) > 1e-12) validCharge = false;

    // Check if particles are on mass shell
    for ( int i = 0; i < testEvt.size(); ++i) {
      if (testEvt[i].statusAbs() < 20) continue;
      validMomenta = validMomenta && validMomentum(testEvt[i].p(),
        testEvt[i].id(), (testEvt[i].isFinal() ? 1 : -1), beam, usePDFmass);
    }

    // Check that overall pT is vanishing.
    Vec4 pIn(0.,0.,0.,0.), pResIn(0.,0.,0.,0.), pOut(0.,0.,0.,0.);
    //Vec4 pSum(0.,0.,0.,0.);
    //for ( int i = 0; i < testEvt.size(); ++i) {
    //  if ( testEvt[i].status() == -21
    //    || testEvt[i].status() == -22 ) pSum -= testEvt[i].p();
    //  if ( testEvt[i].isFinal() )       pSum += testEvt[i].p();
    //}
    for ( int i = 0; i < testEvt.size(); ++i) {
      if ( testEvt[i].status() == -21) pIn += testEvt[i].p();
      if ( testEvt[i].status() == -22) pResIn += testEvt[i].p();
      if ( testEvt[i].isFinal() )      pOut   += testEvt[i].p();
    }

    if (pIn.m2Calc()==0.) pIn += pResIn;
    Vec4 pSum = pOut-pIn;
    if ( abs(pSum.px()) > mTolErr || abs(pSum.py()) > mTolErr) {
      validMomenta = false;
    }

    if ( !particleDataPtr->isResonance(testEvt[3].id())
      && testEvt[3].status() == -21
      && (abs(testEvt[3].px()) > mTolErr || abs(testEvt[3].py()) > mTolErr))
      validMomenta = false;
    if ( !particleDataPtr->isResonance(testEvt[4].id())
      && testEvt[4].status() == -21
      && (abs(testEvt[4].px()) > mTolErr || abs(testEvt[4].py()) > mTolErr))
      validMomenta = false;
    // Check for negative energies.
    for ( int i = 0; i < testEvt.size(); ++i)
      if ( (testEvt[i].status() == -21 || testEvt[i].status() == -22
         || testEvt[i].isFinal() ) && testEvt[i].e() < 0. )
         validMomenta = false;

    //if (!(validColour && validCharge && validMomenta)) {
    //  direInfoPtr->eatCout();
    //  testEvt.list();
    //  if (hasSystems) partonSystemsPtr->list();
    //  cout << isProcess << " " << iSys << " " << iSysCheck << endl;
    //  cout << validColour << " " << validCharge << " " << validMomenta << endl;
    //  direInfoPtr->freeCout();
    //}

  } // Done with loop over systems.

  return (validColour && validCharge && validMomenta);

}

//-------------------------------------------------------------------------

bool DireEventUtils::validMotherDaughter( const Event& event ) {

  vector<int> noMot;
  vector<int> noDau;
  vector< pair<int,int> > noMotDau;

  // Loop through the event and check that there are beam particles.
  bool hasBeams = false;
  for (int i = 0; i < event.size(); ++i) {
    int status = event[i].status();
    if (abs(status) == 12) hasBeams = true;

    // Check that mother and daughter lists not empty where not expected to.
    vector<int> mList = event[i].motherList();
    vector<int> dList = event[i].daughterList();
    if (mList.size() == 0 && abs(status) != 11 && abs(status) != 12)
      noMot.push_back(i);
    if (dList.size() == 0 && status < 0 && status != -11)
      noDau.push_back(i);

    // Check that the particle appears in the daughters list of each mother.
    for (int j = 0; j < int(mList.size()); ++j) {
      if ( event[mList[j]].daughter1() <= i
        && event[mList[j]].daughter2() >= i ) continue;
      vector<int> dmList = event[mList[j]].daughterList();
      bool foundMatch = false;
      for (int k = 0; k < int(dmList.size()); ++k)
      if (dmList[k] == i) {
        foundMatch = true;
        break;
      }
      if (!hasBeams && mList.size() == 1 && mList[0] == 0) foundMatch = true;
      if (!foundMatch) {
        bool oldPair = false;
        for (int k = 0; k < int(noMotDau.size()); ++k)
        if (noMotDau[k].first == mList[j] && noMotDau[k].second == i) {
          oldPair = true;
          break;
        }
        if (!oldPair) noMotDau.push_back( make_pair( mList[j], i) );
      }
    }

    // Check that the particle appears in the mothers list of each daughter.
    for (int j = 0; j < int(dList.size()); ++j) {
      if ( event[dList[j]].statusAbs() > 80
        && event[dList[j]].statusAbs() < 90
        && event[dList[j]].mother1() <= i
        && event[dList[j]].mother2() >= i) continue;
      vector<int> mdList = event[dList[j]].motherList();
      bool foundMatch = false;
      for (int k = 0; k < int(mdList.size()); ++k)
      if (mdList[k] == i) {
        foundMatch = true;
        break;
      }
      if (!foundMatch) {
        bool oldPair = false;
        for (int k = 0; k < int(noMotDau.size()); ++k)
        if (noMotDau[k].first == i && noMotDau[k].second == dList[j]) {
          oldPair = true;
          break;
        }
        if (!oldPair) noMotDau.push_back( make_pair( i, dList[j]) );
      }
    }
  }

  // Mother-daughter relations not correct if any lists do not match.
  bool valid = true;
  if (noMot.size() > 0 || noDau.size() > 0 || noMotDau.size() > 0)
    valid = false;

  // Done.
  return valid;

}

//--------------------------------------------------------------------------

// Find index of colour partner for input colour.

int DireEventUtils::FindCol(int col, vector<int> iExc, const Event& event,
    int type, int iSys) {

  int index = 0;

  int inA = 0, inB = 0;
  for (int i=event.size()-1; i > 0; --i) {
    if ( event[i].mother1() == 1 && event[i].status() != -31
      && event[i].status() != -34) { if (inA == 0) inA = i; }
    if ( event[i].mother1() == 2 && event[i].status() != -31
      && event[i].status() != -34) { if (inB == 0) inB = i; }
  }
  if (iSys >= 0) inA = partonSystemsPtr->getInA(iSys);
  if (iSys >= 0) inB = partonSystemsPtr->getInB(iSys);
  // Unset if the incoming particles are flagged as outgoing. Instead, try to
  // resort to information stored in 0th event entry.
  if (event[inA].status() > 0) {
    inA = 0;
    if (event[0].daughter1() > 0) inA = event[0].daughter1();
  }
  if (event[inB].status() > 0) {
    inB = 0;
    if (event[0].daughter2() > 0) inB = event[0].daughter2();
  }

  // Search event record for matching colour & anticolour
  for(int n = 0; n < event.size(); ++n) {
    // Skip if this index is excluded.
    if ( find(iExc.begin(), iExc.end(), n) != iExc.end() ) continue;
    if ( event[n].colType() != 0 &&  event[n].status() > 0 ) {
       if ( event[n].acol() == col ) {
        index = -n;
        break;
      }
      if ( event[n].col()  == col ) {
        index =  n;
        break;
      }
    }
  }
  // Search event record for matching colour & anticolour
  for(int n = event.size()-1; n > 0; --n) {
    // Skip if this index is excluded.
    if ( find(iExc.begin(), iExc.end(), n) != iExc.end() ) continue;
    if ( index == 0 && event[n].colType() != 0
      && ( n == inA || n == inB) ) {  // Check incoming
       if ( event[n].acol() == col ) {
        index = -n;
        break;
      }
      if ( event[n].col()  == col ) {
        index =  n;
        break;
      }
    }
  }
  // if no matching colour / anticolour has been found, return false
  if ( type == 1 && index < 0) return abs(index);
  if ( type == 2 && index > 0) return abs(index);
  return 0;

}

//--------------------------------------------------------------------------

// Return event stripped from decay products.

Event DireEventUtils::eventForMerging(const Event& inputEventIn,
  bool storeInputEvent ) {

  // Find and detach decay products.
  Event newProcess = Event();
  newProcess.init("(hard process-modified)", particleDataPtr);

  // If desired, store input event.
  if ( storeInputEvent ) {
    resonances.resize(0);
    inputEvent.clear();
    inputEvent.init("(hard process)", particleDataPtr);
    for (int i = 0; i < inputEventIn.size(); ++i)
      inputEvent.append( inputEventIn[i] );
    for (int i = 0; i < inputEventIn.sizeJunction(); ++i)
      inputEvent.appendJunction( inputEventIn.getJunction(i) );
    inputEvent.saveSize();
    inputEvent.saveJunctionSize();
  }

  // Now remove decay products.
  if ( doRemoveDecayProducts ) {

    // Add the beam and initial partons to the event record.
    for (int i = 0; i < inputEventIn.size(); ++ i) {
      if ( inputEventIn[i].mother1() > 4
        || inputEventIn[i].statusAbs() == 22
        || inputEventIn[i].statusAbs() == 23)
        break;
      newProcess.append(inputEventIn[i]);
    }

    // Add the intermediate particles to the event record.
    for (int i = 0; i < inputEventIn.size(); ++ i) {
      if (inputEventIn[i].mother1() > 4) break;
      if ( inputEventIn[i].statusAbs() == 22) {
        int j = newProcess.append(inputEventIn[i]);
        newProcess[j].statusPos();
        if ( storeInputEvent ) resonances.push_back( make_pair(j, i) );
        newProcess[j].daughters(0, 0);
      }
    }

    // Add remaining outgoing particles to the event record.
    for (int i = 0; i < inputEventIn.size(); ++ i) {
      if (inputEventIn[i].mother1() > 4) break;
      if ( inputEventIn[i].statusAbs() != 11
        && inputEventIn[i].statusAbs() != 12
        && inputEventIn[i].statusAbs() != 21
        && inputEventIn[i].statusAbs() != 22)
        newProcess.append(inputEventIn[i]);
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

  } else {
    newProcess = inputEventIn;
  }

  // Remember scale
  newProcess.scale( inputEventIn.scale() );

  // Done
  return newProcess;

}

//--------------------------------------------------------------------------

// Write event with decay products attached to argument. Only possible if an
// input event with decay producs had been stored before.

bool DireEventUtils::reattachDecaysAfterMerging(Event& process ) {

  // Now reattach the decay products.
  if ( doRemoveDecayProducts && inputEvent.size() > 0 ) {

    int sizeBef = process.size();
    // Vector of resonances for which the decay products were already attached.
    vector<int> iAftChecked;
    // Reset daughters and status of intermediate particles.
    for ( int i = 0; i < int(resonances.size()); ++i ) {
      for (int j = 0; j < sizeBef; ++j ) {
        if ( j != resonances[i].first ) continue;

        int iOldDaughter1 = inputEvent[resonances[i].second].daughter1();
        int iOldDaughter2 = inputEvent[resonances[i].second].daughter2();

        // Get momenta in case of reclustering.
        int iHardMother      = resonances[i].second;
        Particle& hardMother = inputEvent[iHardMother];
        // Find current mother copy (after clustering).
        int iAftMother       = 0;
        for ( int k = 0; k < process.size(); ++k )
          if ( process[k].id() == inputEvent[resonances[i].second].id() ) {
            // Only attempt if decays of this resonance were not attached.
            bool checked = false;
            for ( int l = 0; l < int(iAftChecked.size()); ++l )
              if ( k == iAftChecked[l] )
                checked = true;
            if ( !checked ) {
              iAftChecked.push_back(k);
              iAftMother = k;
              break;
            }
          }
        if (iAftMother== 0) continue;

        Particle& aftMother  = process[iAftMother];

        // Resonance can have been moved by clustering,
        // so prepare to update colour and momentum information for system.
        int colBef  = hardMother.col();
        int acolBef = hardMother.acol();
        int colAft  = aftMother.col();
        int acolAft = aftMother.acol();
        RotBstMatrix M;
        M.bst( hardMother.p(), aftMother.p());

        // Attach resonance decay products.
        int iNewDaughter1 = 0;
        int iNewDaughter2 = 0;
        for ( int k = iOldDaughter1; k <= iOldDaughter2; ++k ) {
          if ( k == iOldDaughter1 )
            iNewDaughter1 = process.append(inputEvent[k] );
          else
            iNewDaughter2 = process.append(inputEvent[k] );
          process.back().statusPos();
          Particle& now = process.back();
          // Update colour and momentum information.
          if (now.col()  != 0 && now.col()  == colBef ) now.col(colAft);
          if (now.acol() != 0 && now.acol() == acolBef) now.acol(acolAft);
          now.rotbst( M);
          // Update vertex information.
          if (now.hasVertex()) now.vProd( aftMother.vDec() );
          // Update mothers.
          now.mothers(iAftMother,0);
        }

        process[iAftMother].daughters( iNewDaughter1, iNewDaughter2 );
        process[iAftMother].statusNeg();

        // Loop through event and attach remaining decays
        int iDec = 0;
        do {
          if ( process[iDec].isFinal() && process[iDec].canDecay()
            && process[iDec].mayDecay() && process[iDec].isResonance() ) {

            int iD1 = process[iDec].daughter1();
            int iD2 = process[iDec].daughter2();

            // Done if no daughters exist.
            if ( iD1 == 0 || iD2 == 0 ) continue;

            // Attach daughters.
            int iNewDaughter12 = 0;
            int iNewDaughter22 = 0;
            for ( int k = iD1; k <= iD2; ++k ) {
              if ( k == iD1 )
                iNewDaughter12 = process.append(inputEvent[k] );
              else
                iNewDaughter22 = process.append(inputEvent[k] );
              process.back().statusPos();
              Particle& now = process.back();
              // Update colour and momentum information.
              if (now.col() != 0 && now.col() == colBef ) now.col(colAft);
              if (now.acol()!= 0 && now.acol()== acolBef) now.acol(acolAft);
              now.rotbst( M);
              // Update vertex information.
              if (now.hasVertex()) now.vProd( process[iDec].vDec() );
              // Update mothers.
              now.mothers(iDec,0);
            }

            // Modify mother status and daughters.
            process[iDec].status(-22);
            process[iDec].daughters(iNewDaughter12, iNewDaughter22);

          // End of loop over all entries.
          }
        } while (++iDec < process.size());
      } // End loop over process entries.
    } // End loop over resonances.

    // Update event colour tag to maximum in whole process.
    int maxColTag = 0;
    for (int i = 0; i < process.size(); ++ i) {
      if (process[i].col() > maxColTag) maxColTag = process[i].col();
      if (process[i].acol() > maxColTag) maxColTag = process[i].acol();
    }
    process.initColTag(maxColTag);

  }

  // Done.
  return (doRemoveDecayProducts) ? inputEvent.size() > 0 : true;

}

//==========================================================================

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_II ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return sai*sbi / sab * ( sai+sbi+sab ) / sab;
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_IF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sik =  2.*rec*emt;
  double sak = -2.*rad*rec;
  return sai*sik / (sai+sak) * (sai+sik+sak) / (sai+sak);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolCS_II ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return sai*sbi / sab * ( sai+sbi+sab ) / sab;
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolCS_IF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sik =  2.*rec*emt;
  double sak = -2.*rad*rec;
  return sai*sik*sak / pow2(sai+sak);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_II ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return 1. + sbi/sab;
}

//-------------------------------------------------------------------------

double DireKinRelations::z_IF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sik =  2.*rec*emt;
  double sak = -2.*rad*rec;
  return 1. + sik / (sai+sak);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_II ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return (sab + sai + sbi);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_IF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rad*emt;
  double sik =  2.*rec*emt;
  double sak = -2.*rad*rec;
  return -1.*(sai+sik+sak);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_II ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double sa1 = -2.*rad*emt1;
  double sb1 = -2.*rec*emt1;
  double sa2 = -2.*rad*emt2;
  double sb2 = -2.*rec*emt2;
  double sab =  2.*rad*rec;
  double s12 =  2.*emt1*emt2;
  return (sa1+sa2)*(sb1+sb2) / (sa1+sa2+sb1+sb2+sab+s12);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_IF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double sa1 = -2.*rad*emt1;
  double sb1 =  2.*rec*emt1;
  double sa2 = -2.*rad*emt2;
  double sab = -2.*rad*rec;
  double s12 =  2.*emt1*emt2;
  return -(sa2+s12)*(sab+sb1) / (sa1+sa2+sab);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_II ( const Vec4& rad, const Vec4& emt, const Vec4&,
  const Vec4& rec) {
  cout << __FILE__ << " " << __func__ << " not yet implemented " << endl;
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return 1. + sbi/sab;
}

//-------------------------------------------------------------------------

double DireKinRelations::z_IF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double sa1 = -2.*rad*emt1;
  double sa2 = -2.*rad*emt2;
  double sak = -2.*rad*rec;
  return -m2dip_IF (rad,emt1,emt2,rec) / (sa1+sa2+sak);
}

//--------------------------------------------------------------------------

double DireKinRelations::xa_II ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  cout << __FILE__ << " " << __func__ << " not yet implemented " << endl;
  double s1k = -2.*rec*emt1;
  double sak = -2.*rad*rec;
  double sa1 = -2.*rad*emt1;
  double sa2 = -2.*rad*emt2;
  return (sak+s1k) / (sak+sa1+sa2);
}

//-------------------------------------------------------------------------

double DireKinRelations::xa_IF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double s1k =  2.*rec*emt1;
  double sak = -2.*rad*rec;
  double sa1 = -2.*rad*emt1;
  double sa2 = -2.*rad*emt2;
  return (sak+s1k) / (sak+sa1+sa2);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_II ( const Vec4& rad, const Vec4& emt, const Vec4&,
  const Vec4& rec) {
  cout << __FILE__ << " " << __func__ << " not yet implemented " << endl;
  double sai = -2.*rad*emt;
  double sbi = -2.*rec*emt;
  double sab =  2.*rad*rec;
  return (sab + sai + sbi);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_IF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double sa1 = -2.*rad*emt1;
  double s1k =  2.*rec*emt1;
  double sa2 = -2.*rad*emt2;
  double s2k =  2.*rec*emt2;
  double s12 =  2.*emt1*emt2;
  double sak = -2.*rad*rec;
  return -1.*(sa1+s1k+sak+sa2+s2k+s12);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_FF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij = 2.*rad*emt;
  double sik = 2.*rad*rec;
  double sjk = 2.*rec*emt;
  return sij*sjk / (sij+sik+sjk);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_FI ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij =  2.*rad*emt;
  double sai = -2.*rec*rad;
  double saj = -2.*rec*emt;
  //return sij*saj / (sai+saj) * (sij+saj+sai) / (sai+saj) ;
  double t = sij*saj / (sai+saj) * (sij+saj+sai) / (sai+saj) ;
  if (sij+saj+sai < 1e-5 && abs(sij+saj+sai) < 1e-5) t = sij;
  return t;

}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolCS_FF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij = 2.*rad*emt;
  double sik = 2.*rad*rec;
  double sjk = 2.*rec*emt;
  return sij*sjk / (sij+sik+sjk);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolCS_FI ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij =  2.*rad*emt;
  double sai = -2.*rec*rad;
  double saj = -2.*rec*emt;
  double t = sij*saj*sai / pow2(sai+saj);
  if (sij+saj+sai < 1e-5 && abs(sij+saj+sai) < 1e-5) t = sij;
  return t;

}

//--------------------------------------------------------------------------

double DireKinRelations::z_FF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij = 2.*rad*emt;
  double sik = 2.*rad*rec;
  double sjk = 2.*rec*emt;
  return (sij + sik) / (sij+sik+sjk);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_FI ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sai = -2.*rec*rad;
  double saj = -2.*rec*emt;
  return sai / (sai+saj);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_FF ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij = 2.*rad*emt;
  double sik = 2.*rad*rec;
  double sjk = 2.*rec*emt;
  return (sij+sik+sjk);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_FI ( const Vec4& rad, const Vec4& emt,
  const Vec4& rec) {
  double sij =  2.*rad*emt;
  double sai = -2.*rec*rad;
  double saj = -2.*rec*emt;
  return -1.*(sij+saj+sai);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_FF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double si1 = 2.*rad*emt1;
  double si2 = 2.*rad*emt2;
  double sik = 2.*rad*rec;
  double sk1 = 2.*rec*emt1;
  double sk2 = 2.*rec*emt2;
  double s12 = 2.*emt1*emt2;
  return (si1+si2)*(sk1+sk2) / (si1+si2+sk1+sk2+sik+s12);
}

//--------------------------------------------------------------------------

double DireKinRelations::tEvolDire_FI ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double saj = 2.*rad*emt2;
  double sak = 2.*rad*rec;
  double sik = 2.*rec*emt1;
  double sjk = 2.*rec*emt2;
  double sij = 2.*emt1*emt2;
  return (saj+sij)*(sak+sik) / (sak+sik+sjk);

}

//--------------------------------------------------------------------------

double DireKinRelations::z_FF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double si1 = 2.*rad*emt1;
  double si2 = 2.*rad*emt2;
  double sik = 2.*rad*rec;
  double sk1 = 2.*rec*emt1;
  double sk2 = 2.*rec*emt2;
  double s12 = 2.*emt1*emt2;
  return sik / (si1+si2+sk1+sk2+sik+s12);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_FI ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double sik =-2.*rad*rec;
  double sk1 =-2.*rec*emt1;
  double sk2 =-2.*rec*emt2;
  return sik / (sk1+sk2+sik);
}

//--------------------------------------------------------------------------

double DireKinRelations::xa_FF ( const Vec4& rad, const Vec4& emt1,
  const Vec4&, const Vec4& rec) {
  double sik = 2.*rad*rec;
  double sk1 = 2.*rec*emt1;
  return sik / (sk1+sik);
}

//--------------------------------------------------------------------------

double DireKinRelations::xa_FI ( const Vec4& rad, const Vec4& emt1,
  const Vec4&, const Vec4& rec) {
  double sik =-2.*rad*rec;
  double sk1 =-2.*rec*emt1;
  return sik / (sk1+sik);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_FF ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double si1 = 2.*rad*emt1;
  double si2 = 2.*rad*emt2;
  double sik = 2.*rad*rec;
  double sk1 = 2.*rec*emt1;
  double sk2 = 2.*rec*emt2;
  double s12 = 2.*rec*emt1;
  return (si1+si2+sk1+sk2+sik+s12);
}

//--------------------------------------------------------------------------

double DireKinRelations::m2dip_FI ( const Vec4& rad, const Vec4& emt1,
  const Vec4& emt2, const Vec4& rec) {
  double si1 =  2.*rad*emt1;
  double si2 =  2.*rad*emt2;
  double sik = -2.*rec*rad;
  double sk1 = -2.*rec*emt1;
  double sk2 = -2.*rec*emt2;
  double s12 =  2.*emt1*emt2;
  return -1.*(si1+si2+sk1+sk2+sik+s12);
}

//--------------------------------------------------------------------------

// Functions to calculate Dire variables from CS evolution variables.

double DireKinRelations::t_ff_dire_from_cs(double z, double t, double m2d) { 
  double ycs = ycs_ff(z,t,m2d);
  double zcs = zcs_ff(z,t,m2d);
  return ycs*(1-ycs)*(1-zcs)*m2d;
}

//--------------------------------------------------------------------------

double DireKinRelations::z_ff_dire_from_cs(double z, double t, double m2d) {
  double ycs = ycs_ff(z,t,m2d);
  double zcs = zcs_ff(z,t,m2d);
  return 1.-(1-ycs)*(1-zcs);
}

//--------------------------------------------------------------------------

double DireKinRelations::t_fi_dire_from_cs(double z, double t, double m2d) {
  double xcs = xcs_fi(z,t,m2d);
  double zcs = zcs_fi(z,t,m2d);
  return m2d*(1-xcs)*(1.-zcs);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_fi_dire_from_cs(double z, double t, double m2d) {
  double zcs = zcs_fi(z,t,m2d);
  return zcs;
}

//--------------------------------------------------------------------------

double DireKinRelations::t_if_dire_from_cs(double z, double t, double m2d) {
  double xcs = xcs_if(z,t,m2d);
  double ucs = ucs_if(z,t,m2d);
  return m2d*ucs*(1-xcs);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_if_dire_from_cs(double z, double t, double m2d) {
  double xcs = xcs_if(z,t,m2d);
  return xcs;
}

//--------------------------------------------------------------------------

double DireKinRelations::t_ii_dire_from_cs(double z, double t, double m2d) {
  double xcs = xcs_ii(z,t,m2d);
  double vcs = vcs_ii(z,t,m2d);
  return m2d*vcs*(1-vcs-xcs);
}

//--------------------------------------------------------------------------

double DireKinRelations::z_ii_dire_from_cs(double z, double t, double m2d) {
  double xcs = xcs_ii(z,t,m2d);
  double vcs = vcs_ii(z,t,m2d);
  return xcs + vcs;
}

//--------------------------------------------------------------------------

}
