
#ifndef Pythia8_DireBasics_H
#define Pythia8_DireBasics_H

#define DIRE_BASICS_VERSION "2.004"

// Pythia includes.
#include "Pythia8/Pythia.h"
#include <limits>
#include <unordered_map>

using std::unordered_map;

namespace Pythia8 {

typedef unsigned long ulong;

//==========================================================================

// Function to hash string into long integer.

ulong shash(const string& str);

//==========================================================================

// Template to make initializing maps simpler, while not relying on C++11.
// Usage: map(createmap<T,U>(a,b)(c,d)(e,f));

template <typename T, typename U> class createmap {

private:

  map<T, U> m_map;

public:

  createmap(const T& key, const U& val) { m_map[key] = val; }
  createmap<T, U>& operator()(const T& key, const U& val) {
    m_map[key] = val;
    return *this;
  }
  operator map<T, U>() { return m_map; }

};

//==========================================================================

// Template to make initializing maps simpler, while not relying on C++11.
// Usage: map(createmap<T,U>(a,b)(c,d)(e,f));

template <typename T, typename U> class create_unordered_map {

private:

  unordered_map<T, U> um_map;

public:

  create_unordered_map(const T& key, const U& val) { um_map[key] = val; }
  create_unordered_map<T, U>& operator()(const T& key, const U& val) {
    um_map[key] = val;
    return *this;
  }
  operator unordered_map<T, U>() { return um_map; }

};

//==========================================================================

// Template to make initializing maps simpler, while not relying on C++11.
// Usage: map(createmap<T,U>(a,b)(c,d)(e,f));

template <typename T> class createvector {

private:

  vector<T> m_vector;

public:

  createvector(const T& val) { m_vector.push_back(val); }
  createvector<T>& operator()(const T& val) {
    m_vector.push_back(val);
    return *this;
  }
  operator vector<T>() { return m_vector; }

};

//==========================================================================

// Helper function to calculate dilogarithm.

double polev(double x,double* coef,int N );
// Function to calculate dilogarithm.
double dilog(double x);

//==========================================================================

// Kallen function and derived quantities. 

double lABC(double a, double b, double c);
double bABC(double a, double b, double c);
double gABC(double a, double b, double c);

//==========================================================================

class DireFunction {

public:

  virtual double f(double) { return 0.; }
  virtual double f(double, double) { return 0.; }
  virtual double f(double, vector<double>) { return 0.; }

};

class DireRootFinder {

public:

  DireRootFinder() {};
  virtual ~DireRootFinder() {};

  //virtual double f(double, vector<double> = vector<double>()) { return 0.; }

  double findRootSecant1D( DireFunction* f, double xmin, double xmax,
    double constant, vector<double> xb = vector<double>(), int N=10 ) {
    vector<double> x;
    x.push_back(xmin);
    x.push_back(xmax);
    for ( int i=2; i < N; ++i ) {
      double xn = x[i-1]
      - ( f->f(x[i-1],xb) - constant)
      * ( x[i-1] - x[i-2] )
      / ( f->f(x[i-1],xb) - f->f(x[i-2],xb) );
      x.push_back(xn);
    }
    return x.back();
  }

  double findRoot1D( DireFunction* f, double xmin, double xmax,
    double constant, vector<double> xx = vector<double>(), int N=10,
    double tol = 1e-10 ) {

    double a(xmin), b(xmax), c(xmax), d(0.), e(0.),
      fa(f->f(a,xx)-constant), fb(f->f(b,xx)-constant), fc(fb),
      p(0.), q(0.), r(0.), s(0.),
      tol1(tol), xm(0.);
    double EPS = std::numeric_limits<double>::epsilon();

    // No root.
    if ( (fa>0. && fb>0.) || (fa<0. && fb<0.) ) {
     //cout << scientific << setprecision(10)
     //<< "Warning in " << __func__ << " : No root for"
     //<< " constant=" << constant
     //<< " f(" << a << ")=" << f->f(a,xx)
     //<< " f(" << b << ")=" << f->f(b,xx)
     //<< endl;
     return std::numeric_limits<double>::quiet_NaN();
    }

    for ( int i=0; i < N; ++i ) {

      if ( (fb>0. && fc>0.) || (fb<0. && fc<0.) ) {
        c  = a;
        fc = fa;
        e  = d = b-a;
      }

      if ( abs(fc) < abs(fb) ) {
        a = b;
        b = c;
        c = a;
        fa = fb;
        fb = fc;
        fc = fa;
      }

      tol1 = 2.*EPS*abs(b) + 0.5*tol;
      xm = 0.5*(c-b);

      if (abs(xm) <= tol1 || fb == 0.) return b;
      //if (abs(xm) <= tol1 || fb < EPS) return b;
      //if (abs(xm) <= tol1 || abs(fb) < EPS) return b;

      if (abs(e) >= tol1 && abs(fa) > abs(fb) ) {
        s = fb/fa;
        if ( a == c ) {
        //if ( abs(abs(a)-abs(c)) < EPS ) {
          p = 2.*xm*s;
          q = 1.-s;
        } else {
          q = fa/fc;
          r = fb/fc;
          p = s*(2.*xm*q*(q-r) - (b-a)*(r-1.));
          q = (q-1.)*(r-1.)*(s-1.);
        }
        if (p>0.) q = -q;
        p = abs(p);
        double min1 = 3.*xm*q - abs(tol1*q);
        double min2 = abs(e*q);
        if (2.*p < ((min1 < min2) ? min1 : min2)) {
          e = d;
          d = p/q;
        } else {
          d = xm;
          e = d;
        }

      } else {
        d = xm;
        e = d;
      }

      a = b;
      fa = fb;

      if (abs(d) > tol1) { b += d; }
      else {
        b += (xm> 0.) ? tol1 : -tol1;
      }
      fb = f->f(b,xx)-constant;
    }

    // Failed. Return NaN
    return std::numeric_limits<double>::quiet_NaN();

  }

};

//==========================================================================

// Abort function.
int puppybort( string input, int iPuppy = 0);

//==========================================================================

class DireEventInfo {

  public:

  DireEventInfo() {}

  // Bookkeeping of soft particles.
  int sizeSoftPos () const { return softPosSave.size(); }
  int getSoftPos(unsigned int i) const {
    return (i > softPosSave.size()-1) ? -1 : softPosSave[i]; }
  bool isSoft(int iPos) {
    vector<int>::iterator it = find( softPosSave.begin(),
      softPosSave.end(), iPos);
    return (it != softPosSave.end());
  }
  void addSoftPos(int iPos) { if (!isSoft(iPos)) softPosSave.push_back(iPos); }
  void removeSoftPos(int iPos) { 
    vector<int>::iterator it = find( softPosSave.begin(),
      softPosSave.end(), iPos); 
    if (it != softPosSave.end()) softPosSave.erase(it);
  }
  void updateSoftPos(int iPosOld, int iPosNew) {
    if (isSoft(iPosOld)) removeSoftPos(iPosOld);
    if (isSoft(iPosNew)) removeSoftPos(iPosNew);
    addSoftPos(iPosNew);
  }
  void updateSoftPosIfMatch(int iPosOld, int iPosNew) {
    if (isSoft(iPosOld)) {
      vector<int>::iterator it
        = find (softPosSave.begin(), softPosSave.end(), iPosOld);
      *it = iPosNew;
    }
  }
  vector<int> softPos () const { return softPosSave; }
  void clearSoftPos () { softPosSave.clear(); }
  void listSoft() const {
    cout << " 'Soft' particles: ";
    for (int i=0; i < sizeSoftPos(); ++i) cout << setw(5) << getSoftPos(i);
    cout << endl;
  }

  // Bookkeeping of resonances.
  void removeResPos(int iPos) {
    vector<int>::iterator it = find (iPosRes.begin(), iPosRes.end(), iPos);
    if (it == iPosRes.end()) return;
    iPosRes.erase(it);
    sort (iPosRes.begin(), iPosRes.end());
  } 
  void addResPos(int iPos) {
    vector<int>::iterator it = find (iPosRes.begin(), iPosRes.end(), iPos);
    if (it != iPosRes.end()) return;
    iPosRes.push_back(iPos);
    sort (iPosRes.begin(), iPosRes.end());
  }
  void updateResPos(int iPosOld, int iPosNew) {
    vector<int>::iterator it = find (iPosRes.begin(), iPosRes.end(), iPosOld);
    if (it == iPosRes.end()) iPosRes.push_back(iPosNew);
    else                    *it = iPosNew;
    sort (iPosRes.begin(), iPosRes.end());
  }
  void updateResPosIfMatch(int iPosOld, int iPosNew) {
    vector<int>::iterator it = find (iPosRes.begin(), iPosRes.end(), iPosOld);
    if (it != iPosRes.end()) {
      iPosRes.erase(it);
      iPosRes.push_back(iPosNew);
      sort (iPosRes.begin(), iPosRes.end());
    }
  } 
  bool isRes(int iPos) {
    vector<int>::iterator it = find (iPosRes.begin(), iPosRes.end(), iPos);
    return (it != iPosRes.end());
  } 
  int sizeResPos() const { return iPosRes.size(); }
  int getResPos(unsigned int i) const { 
    return (i > iPosRes.size()-1) ? -1 : iPosRes[i]; }
  void clearResPos() { iPosRes.resize(0); }
  void listRes() const {
    cout << " 'Resonant' particles: ";
    for (int i=0; i < sizeResPos(); ++i) cout << setw(5) <<  getResPos(i);
    cout << endl;
  }

  // Data members.
  vector<int> softPosSave;
  vector<int> iPosRes;

};

//==========================================================================

class DireDebugInfo {

  public:

  DireDebugInfo() {
    /*mecSum = 0.;
    log_MEC_1em.book("log_mec_1em",60,-3,3.);
    log_MEC_2em.book("log_mec_2em",60,-3,3.);
    MEC_1em_ii_v_pt.book("mec_1em_ii_v_pt",1000,0.1,10.);
    MEC_1em_if_v_pt.book("mec_1em_if_v_pt",1000,0.1,10.);
    MEC_1em_fi_v_pt.book("mec_1em_fi_v_pt",1000,0.1,10.);
    MEC_1em_ff_v_pt.book("mec_1em_ff_v_pt",1000,0.1,10.);
    MEC_2em_ii_v_pt.book("mec_2em_ii_v_pt",1000,0.1,10.);
    MEC_2em_if_v_pt.book("mec_2em_if_v_pt",1000,0.1,10.);
    MEC_2em_fi_v_pt.book("mec_2em_fi_v_pt",1000,0.1,10.);
    MEC_2em_ff_v_pt.book("mec_2em_ff_v_pt",1000,0.1,10.);

    n_1em_ii_v_pt.book("n_1em_ii_v_pt",1000,0.1,10.);
    n_1em_if_v_pt.book("n_1em_if_v_pt",1000,0.1,10.);
    n_1em_fi_v_pt.book("n_1em_fi_v_pt",1000,0.1,10.);
    n_1em_ff_v_pt.book("n_1em_ff_v_pt",1000,0.1,10.);
    n_2em_ii_v_pt.book("n_2em_ii_v_pt",1000,0.1,10.);
    n_2em_if_v_pt.book("n_2em_if_v_pt",1000,0.1,10.);
    n_2em_fi_v_pt.book("n_2em_fi_v_pt",1000,0.1,10.);
    n_2em_ff_v_pt.book("n_2em_ff_v_pt",1000,0.1,10.);

    MEC_1em_ii_v_z.book("mec_1em_ii_v_z",1000,0.,1.);
    MEC_1em_if_v_z.book("mec_1em_if_v_z",1000,0.,1.);
    MEC_1em_fi_v_z.book("mec_1em_fi_v_z",1000,0.,1.);
    MEC_1em_ff_v_z.book("mec_1em_ff_v_z",1000,0.,1.);
    MEC_2em_ii_v_z.book("mec_2em_ii_v_z",1000,0.,1.);
    MEC_2em_if_v_z.book("mec_2em_if_v_z",1000,0.,1.);
    MEC_2em_fi_v_z.book("mec_2em_fi_v_z",1000,0.,1.);
    MEC_2em_ff_v_z.book("mec_2em_ff_v_z",1000,0.,1.);

    n_1em_ii_v_z.book("n_1em_ii_v_z",1000,0.,1.);
    n_1em_if_v_z.book("n_1em_if_v_z",1000,0.,1.);
    n_1em_fi_v_z.book("n_1em_fi_v_z",1000,0.,1.);
    n_1em_ff_v_z.book("n_1em_ff_v_z",1000,0.,1.);
    n_2em_ii_v_z.book("n_2em_ii_v_z",1000,0.,1.);
    n_2em_if_v_z.book("n_2em_if_v_z",1000,0.,1.);
    n_2em_fi_v_z.book("n_2em_fi_v_z",1000,0.,1.);
    n_2em_ff_v_z.book("n_2em_ff_v_z",1000,0.,1.);*/

  }

  void clearMessages() {
    messageStream0.str("");
    messageStream1.str("");
    messageStream2.str("");
  }

  void printMessages( int verbosity = 0) {
    cout << "\n"
      << "*------------------------------------------------------------*\n"
      << "*----------------- Begin diagnostic output ------------------*\n\n";
    if (verbosity == 0) cout << scientific << setprecision(8)
    << messageStream0.str();
    if (verbosity == 1) cout << scientific << setprecision(8)
    << messageStream1.str();
    if (verbosity == 2) cout << scientific << setprecision(8)
    << messageStream2.str();
    cout << "\n\n"
      << "*----------------- End diagnostic output -------------------*\n"
      << "*-----------------------------------------------------------*"
      << endl;
  }

  void printHistograms() {

    /*log_MEC_1em /= log_MEC_1em.getEntries();
    log_MEC_2em /= log_MEC_2em.getEntries();
    MEC_1em_ii_v_pt  /= MEC_1em_ii_v_pt.getEntries();
    MEC_1em_if_v_pt  /= MEC_1em_if_v_pt.getEntries();
    MEC_1em_fi_v_pt  /= MEC_1em_fi_v_pt.getEntries();
    MEC_1em_ff_v_pt  /= MEC_1em_ff_v_pt.getEntries();
    MEC_2em_ii_v_pt  /= MEC_2em_ii_v_pt.getEntries();
    MEC_2em_if_v_pt  /= MEC_2em_if_v_pt.getEntries();
    MEC_2em_fi_v_pt  /= MEC_2em_fi_v_pt.getEntries();
    MEC_2em_ff_v_pt  /= MEC_2em_ff_v_pt.getEntries();

    MEC_1em_ii_v_pt  /= mecSum;
    MEC_1em_if_v_pt  /= mecSum;
    MEC_1em_fi_v_pt  /= mecSum;
    MEC_1em_ff_v_pt  /= mecSum;
    MEC_2em_ii_v_pt  /= mecSum;
    MEC_2em_if_v_pt  /= mecSum;
    MEC_2em_fi_v_pt  /= mecSum;
    MEC_2em_ff_v_pt  /= mecSum;

    ofstream write;
    write.open( (char*)( log_MEC_1em.getTitle() + ".dat" ).c_str() );
    log_MEC_1em.table(write);
    write.close();
    write.open( (char*)( log_MEC_2em.getTitle() + ".dat" ).c_str() );
    log_MEC_2em.table(write);
    write.close();

    write.open( (char*)( MEC_1em_ii_v_pt.getTitle() + ".dat" ).c_str() );
    MEC_1em_ii_v_pt.table(write);
    write.close();
    write.open( (char*)( MEC_1em_if_v_pt.getTitle() + ".dat" ).c_str() );
    MEC_1em_if_v_pt.table(write);
    write.close();
    write.open( (char*)( MEC_1em_fi_v_pt.getTitle() + ".dat" ).c_str() );
    MEC_1em_fi_v_pt.table(write);
    write.close();
    write.open( (char*)( MEC_1em_ff_v_pt.getTitle() + ".dat" ).c_str() );
    MEC_1em_ff_v_pt.table(write);
    write.close();

    write.open( (char*)( n_1em_ii_v_pt.getTitle() + ".dat" ).c_str() );
    n_1em_ii_v_pt.table(write);
    write.close();
    write.open( (char*)( n_1em_if_v_pt.getTitle() + ".dat" ).c_str() );
    n_1em_if_v_pt.table(write);
    write.close();
    write.open( (char*)( n_1em_fi_v_pt.getTitle() + ".dat" ).c_str() );
    n_1em_fi_v_pt.table(write);
    write.close();
    write.open( (char*)( n_1em_ff_v_pt.getTitle() + ".dat" ).c_str() );
    n_1em_ff_v_pt.table(write);
    write.close();

    write.open( (char*)( MEC_1em_ii_v_z.getTitle() + ".dat" ).c_str() );
    MEC_1em_ii_v_z.table(write);
    write.close();
    write.open( (char*)( MEC_1em_if_v_z.getTitle() + ".dat" ).c_str() );
    MEC_1em_if_v_z.table(write);
    write.close();
    write.open( (char*)( MEC_1em_fi_v_z.getTitle() + ".dat" ).c_str() );
    MEC_1em_fi_v_z.table(write);
    write.close();
    write.open( (char*)( MEC_1em_ff_v_z.getTitle() + ".dat" ).c_str() );
    MEC_1em_ff_v_z.table(write);
    write.close();

    write.open( (char*)( n_1em_ii_v_z.getTitle() + ".dat" ).c_str() );
    n_1em_ii_v_z.table(write);
    write.close();
    write.open( (char*)( n_1em_if_v_z.getTitle() + ".dat" ).c_str() );
    n_1em_if_v_z.table(write);
    write.close();
    write.open( (char*)( n_1em_fi_v_z.getTitle() + ".dat" ).c_str() );
    n_1em_fi_v_z.table(write);
    write.close();
    write.open( (char*)( n_1em_ff_v_z.getTitle() + ".dat" ).c_str() );
    n_1em_ff_v_z.table(write);
    write.close();*/

  }

  void fillHistograms(int type, int nfinal, double mec, double pT, double z) {

    if (false) cout << type*nfinal*mec*pT*z;

    /*//double mecfill = abs(log10(abs(mec)));
    double mecfill = mec;
    mecSum += mecfill;

    if (nfinal == 3) log_MEC_1em.fill(log10(mec),1.);
    if (nfinal > 3)  log_MEC_2em.fill(log10(mec),1.);
    if (nfinal == 3 && type == -2) MEC_1em_ii_v_pt.fill(pT,mecfill);
    if (nfinal == 3 && type == -1) MEC_1em_if_v_pt.fill(pT,mecfill); 
    if (nfinal == 3 && type ==  1) MEC_1em_fi_v_pt.fill(pT,mecfill);
    if (nfinal == 3 && type ==  2) MEC_1em_ff_v_pt.fill(pT,mecfill);
    if (nfinal > 3 && type == -2)  MEC_2em_ii_v_pt.fill(pT,mecfill);
    if (nfinal > 3 && type == -1)  MEC_2em_if_v_pt.fill(pT,mecfill);
    if (nfinal > 3 && type ==  1)  MEC_2em_fi_v_pt.fill(pT,mecfill);
    if (nfinal > 3 && type ==  2)  MEC_2em_ff_v_pt.fill(pT,mecfill);

    double nfill = 1.;
    if (nfinal == 3 && type == -2) n_1em_ii_v_pt.fill(pT,nfill);
    if (nfinal == 3 && type == -1) n_1em_if_v_pt.fill(pT,nfill); 
    if (nfinal == 3 && type ==  1) n_1em_fi_v_pt.fill(pT,nfill);
    if (nfinal == 3 && type ==  2) n_1em_ff_v_pt.fill(pT,nfill);
    if (nfinal > 3 && type == -2)  n_2em_ii_v_pt.fill(pT,nfill);
    if (nfinal > 3 && type == -1)  n_2em_if_v_pt.fill(pT,nfill);
    if (nfinal > 3 && type ==  1)  n_2em_fi_v_pt.fill(pT,nfill);
    if (nfinal > 3 && type ==  2)  n_2em_ff_v_pt.fill(pT,nfill);

    if (nfinal == 3 && type == -2) MEC_1em_ii_v_z.fill(z,mecfill);
    if (nfinal == 3 && type == -1) MEC_1em_if_v_z.fill(z,mecfill); 
    if (nfinal == 3 && type ==  1) MEC_1em_fi_v_z.fill(z,mecfill);
    if (nfinal == 3 && type ==  2) MEC_1em_ff_v_z.fill(z,mecfill);
    if (nfinal > 3 && type == -2)  MEC_2em_ii_v_z.fill(z,mecfill);
    if (nfinal > 3 && type == -1)  MEC_2em_if_v_z.fill(z,mecfill);
    if (nfinal > 3 && type ==  1)  MEC_2em_fi_v_z.fill(z,mecfill);
    if (nfinal > 3 && type ==  2)  MEC_2em_ff_v_z.fill(z,mecfill);

    if (nfinal == 3 && type == -2) n_1em_ii_v_z.fill(z,nfill);
    if (nfinal == 3 && type == -1) n_1em_if_v_z.fill(z,nfill); 
    if (nfinal == 3 && type ==  1) n_1em_fi_v_z.fill(z,nfill);
    if (nfinal == 3 && type ==  2) n_1em_ff_v_z.fill(z,nfill);
    if (nfinal > 3 && type == -2)  n_2em_ii_v_z.fill(z,nfill);
    if (nfinal > 3 && type == -1)  n_2em_if_v_z.fill(z,nfill);
    if (nfinal > 3 && type ==  1)  n_2em_fi_v_z.fill(z,nfill);
    if (nfinal > 3 && type ==  2)  n_2em_ff_v_z.fill(z,nfill);*/


  }

  // Add debug messages to message stream.
  ostream & message ( int verbosity = 0) {
    if (verbosity == 0) return messageStream0;
    if (verbosity == 1) return messageStream1;
    if (verbosity == 2) return messageStream2;
    return messageStream0;
  }

  void eatCout() {
    old = cout.rdbuf();
    cout.rdbuf (messageStream1.rdbuf());
  }
  void freeCout() { cout.flush(); cout.rdbuf (old); }

  std::streambuf *old;
  // Debug message streams.
  ostringstream messageStream0, messageStream1, messageStream2;

  /*double mecSum;
  Hist log_MEC_1em, log_MEC_2em;
  Hist MEC_1em_ii_v_pt, MEC_1em_if_v_pt, MEC_1em_fi_v_pt, MEC_1em_ff_v_pt,
    MEC_2em_ii_v_pt, MEC_2em_if_v_pt, MEC_2em_fi_v_pt, MEC_2em_ff_v_pt,
    n_1em_ii_v_pt, n_1em_if_v_pt, n_1em_fi_v_pt, n_1em_ff_v_pt,
    n_2em_ii_v_pt, n_2em_if_v_pt, n_2em_fi_v_pt, n_2em_ff_v_pt,
    MEC_1em_ii_v_z, MEC_1em_if_v_z, MEC_1em_fi_v_z, MEC_1em_ff_v_z,
    MEC_2em_ii_v_z, MEC_2em_if_v_z, MEC_2em_fi_v_z, MEC_2em_ff_v_z,
    n_1em_ii_v_z, n_1em_if_v_z, n_1em_fi_v_z, n_1em_ff_v_z,
    n_2em_ii_v_z, n_2em_if_v_z, n_2em_fi_v_z, n_2em_ff_v_z;*/

};

//==========================================================================

class DireInfo {

  public:

  DireInfo() {}

  void clearAll() {
    direEventInfo.clearResPos();
    direEventInfo.clearSoftPos();
    direDebugInfo.clearMessages();
  }

  // Resonance info forwards.
  void removeResPos(int iPos)   { return direEventInfo.removeResPos(iPos); } 
  void addResPos(int iPos)      { return direEventInfo.addResPos(iPos); }
  bool isRes(int iPos)          { return direEventInfo.isRes(iPos); } 
  void clearResPos ()           { return direEventInfo.clearResPos(); }
  int sizeResPos() const        { return direEventInfo.sizeResPos(); }
  void listRes() const          { return direEventInfo.listRes(); }
  int getResPos(unsigned int i) const { return direEventInfo.getResPos(i); }
  void updateResPos(int iPosOld, int iPosNew) {
    return direEventInfo.updateResPos(iPosOld,iPosNew); }
  void updateResPosIfMatch(int iPosOld, int iPosNew) {
    return direEventInfo.updateResPosIfMatch(iPosOld,iPosNew); } 

  // Debug info forwards.
  void printMessages( int verbosity = 0) {
    return direDebugInfo.printMessages(verbosity); }
  ostream & message ( int verbosity = 0) {
    return direDebugInfo.message(verbosity); }
  void eatCout()  { return direDebugInfo.eatCout(); }
  void freeCout() { return direDebugInfo.freeCout(); }
  void clearMessages() { direDebugInfo.clearMessages(); }

  void fillHistograms(int type, int nfinal, double mec, double pT, double z) {
    direDebugInfo.fillHistograms(type, nfinal,  mec, pT, z); }
  void printHistograms() { direDebugInfo.printHistograms(); }

  // Soft particle info forwards.
  bool isSoft(int iPos)          { return direEventInfo.isSoft(iPos); }
  void addSoftPos(int iPos)      { return direEventInfo.addSoftPos(iPos); }
  void removeSoftPos(int iPos)   { return direEventInfo.removeSoftPos(iPos); }
  vector<int> softPos ()         { return direEventInfo.softPos(); }
  void clearSoftPos ()           { return direEventInfo.clearSoftPos(); }
  int sizeSoftPos () const       { return direEventInfo.sizeSoftPos(); }
  void listSoft() const          { return direEventInfo.listSoft(); }
  int getSoftPos(unsigned int i) const { return direEventInfo.getSoftPos(i); }
  void updateSoftPos(int iPosOld, int iPosNew) {
    return direEventInfo.updateSoftPos(iPosOld, iPosNew);
  }
  void updateSoftPosIfMatch(int iPosOld, int iPosNew) {
    return direEventInfo.updateSoftPosIfMatch(iPosOld, iPosNew);
  }

  bool usePTLastSave;
  bool usePTLast()          { return usePTLastSave; }
  void usePTLast(bool in)   { usePTLastSave = in; }
  double pTLastSave;
  double pTLast()           { return pTLastSave;}
  void   pTLast(double in)  { pTLastSave = in;}
  double pTLastMinSave;
  double pTLastMin()        { return pTLastMinSave;}
  void pTLastMin(double in) { pTLastMinSave = in;}

  DireEventInfo direEventInfo;
  DireDebugInfo direDebugInfo;

};

//==========================================================================

class DireEventUtils {

  public:

  DireEventUtils() : mTolErr(1e-3), TINYMASS(1e-3), partonSystemsPtr(NULL),
    particleDataPtr(NULL), settingsPtr(NULL) {}

  void setPointers (PartonSystems* pSysIn, ParticleData*  pDataIn,
    Settings* settingsIn, DireInfo* direInfoPtrIn) {
    partonSystemsPtr = pSysIn;
    particleDataPtr  = pDataIn;
    settingsPtr      = settingsIn;
    direInfoPtr      = direInfoPtrIn;
    //if (settingsPtr) mTolErr = 1e-2*settingsPtr->parm("Check:mTolErr");
    if (settingsPtr) mTolErr = settingsPtr->parm("Check:mTolErr");
    // Allow massive incoming particles. Currently not supported by Pythia.
    if (settingsPtr) useMassiveBeams
      = settingsPtr->flag("Beams:massiveLeptonBeams");
    if (settingsPtr) doRemoveDecayProducts
      = settingsPtr->flag("Merging:mayRemoveDecayProducts");
  }

  bool checkSIJ(const Event& e, double minSIJ=0.0);
  void printSI(const Event& e);
  void printSIJ(const Event& e);
  string printSIJstring(const Event& e);
  string listEvent(const Event& e);

  bool checkSIJhard(const Event& e, int iSys, bool isProcess = false, 
    double minSIJ=0.0) {
    return checkSIJ( makeHardEvent(iSys, e, isProcess), minSIJ);
  }

  // Get particle masses.
  double mTolErr, TINYMASS;
  bool useMassiveBeams;
  double getMass(int id, int strategy, BeamParticle* beam, bool usePDFmass,
    double mass = 0.) {
    double mRet = 0.;
    // Parton masses.
    if ( particleDataPtr->colType(id) != 0) {
      if (strategy == 1) mRet = particleDataPtr->m0(id);
      if (strategy == 2 &&  usePDFmass && beam != 0)
        mRet = beam->mQuarkPDF(id);
      if (strategy == 2 && (!usePDFmass || beam == 0))
        mRet = particleDataPtr->m0(id);
      if (strategy == 3) mRet = mass;
      if (mRet < TINYMASS) mRet = 0.;
    // Masses of other particles.
    } else {
      mRet = particleDataPtr->m0(id);
      if (strategy == 3) mRet = mass;
      if (mRet < TINYMASS) mRet = 0.;
    }
    return pow2(max(0.,mRet));
  }

  void shiftWZbosonID(Event& event, int iPos) {
    if (iPos <=0
      || (event[iPos].idAbs() != 23 && event[iPos].idAbs() != 24)
      || !event[iPos].isFinal()) return;
      event[iPos].id( event[iPos].id()/event[iPos].idAbs()
                    *(event[iPos].idAbs()+70));
    return;
  }

  // Check that particle has sensible momentum.
  bool validMomentum( const Vec4& p, int id, int status, BeamParticle* beam,
    bool usePDFmass);

  // Check colour/flavour correctness of state.
  bool validEvent( const Event& state, BeamParticle* beam,
    bool usePDFmass, bool isProcess = false, int iSysCheck = -1 );

  // Check that mother-daughter-relations are correctly set.
  bool validMotherDaughter( const Event& state );

  // Find index of colour partner for input colour.
  int FindCol(int col, vector<int> iExclude, const Event& event, int type,
    int iSys = -1);

  Event hardEventSave;
  Event getHardEvent() { return hardEventSave; }

  Event makeHardEvent(int iSys, const Event& state, bool isProcess = false);

  // Return event stripped from decay products.
  Event inputEvent;
  vector< pair<int,int> > resonances;
  bool doRemoveDecayProducts;
  Event eventForMerging( const Event& inputEventIn, bool storeInputEvent );
  // Write event with decay products attached to argument.
  bool reattachDecaysAfterMerging( Event& process );

  PartonSystems* partonSystemsPtr;
  ParticleData*  particleDataPtr;
  Settings*      settingsPtr;
  DireInfo*      direInfoPtr;

};

//==========================================================================

class DireKinRelations {

  public: 

  void setPointers (PartonSystems* pSysIn, ParticleData*  pDataIn,
    Settings* settingsIn) {
    partonSystemsPtr = pSysIn;
    particleDataPtr  = pDataIn;
    settingsPtr      = settingsIn;
    if (settingsPtr) ISRevolutionMode
      = settingsPtr->mode("DireSpace:evolutionMode");
    if (settingsPtr) FSRevolutionMode
      = settingsPtr->mode("DireTimes:evolutionMode");
  }

  double m2dip ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rad.isFinal()) return m2dipTimes (rad, emt, rec);
    else               return m2dipSpace (rad, emt, rec);
  }

  double zEvol ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rad.isFinal()) return zTimes (rad, emt, rec);
    else               return zSpace (rad, emt, rec);
  }

  double tEvol ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rad.isFinal()) return tEvolTimes (rad, emt, rec);
    else               return tEvolSpace (rad, emt, rec);
  }

  // Functional forms of intial-state splitting variables.
  double tEvolSpace ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (ISRevolutionMode==1 && rec.isFinal())
      return tEvolCSSpace(rad,emt,rec);
    else
      return tEvolDireSpace(rad,emt,rec);
   }
  double tEvolSpace ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    return tEvolDireSpace(rad,emt1,emt2,rec);
  }

  double tEvolDireSpace ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return tEvolDire_IF(rad.p(),emt.p(),rec.p());
    return tEvolDire_II(rad.p(),emt.p(),rec.p()); }
  double tEvolDire_II ( const Vec4& rad, const Vec4& emt, const Vec4& rec);
  double tEvolDire_IF ( const Vec4& rad, const Vec4& emt, const Vec4& rec);

  double tEvolDireSpace ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return tEvolDire_IF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return tEvolDire_II(rad.p(),emt1.p(),emt2.p(),rec.p()); }
  double tEvolDire_II ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);
  double tEvolDire_IF ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);

  double tEvolCSSpace ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return tEvolCS_IF(rad.p(),emt.p(),rec.p());
    return tEvolCS_II(rad.p(),emt.p(),rec.p()); }
  double tEvolCS_II ( const Vec4& rad, const Vec4& emt, const Vec4& rec);
  double tEvolCS_IF ( const Vec4& rad, const Vec4& emt, const Vec4& rec);

  // Return auxiliary variable.
  // From Pythia version 8.215 onwards no longer virtual.
  double zSpace ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return z_IF(rad.p(),emt.p(),rec.p());
    return z_II(rad.p(),emt.p(),rec.p()); }
  double z_II ( const Vec4& rad, const Vec4& emt, const Vec4& rec);
  double z_IF ( const Vec4& rad, const Vec4& emt, const Vec4& rec);

  double zSpace ( const Particle& rad, const Particle& emt1, const Particle& emt2,
    const Particle& rec) {
    if (rec.isFinal()) return z_IF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return z_II(rad.p(),emt1.p(),emt2.p(),rec.p()); }
  double z_II ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);
  double z_IF ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);

  double xaSpace ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return xa_IF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return xa_II(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double xa_IF ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);
  double xa_II ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);

  double m2dipSpace ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return m2dip_IF(rad.p(),emt.p(),rec.p());
    return m2dip_II(rad.p(),emt.p(),rec.p());
  }
  double m2dip_II ( const Vec4& rad, const Vec4& emt, const Vec4& rec);
  double m2dip_IF ( const Vec4& rad, const Vec4& emt, const Vec4& rec);

  double m2dipSpace ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return m2dip_IF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return m2dip_II(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double m2dip_IF ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);
  double m2dip_II ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);

  // From Pythia version 8.215 onwards no longer virtual.
  double tEvolTimes ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (FSRevolutionMode==1 && !rec.isFinal())
      return tEvolCSTimes(rad,emt,rec);
    else
      return tEvolDireTimes(rad,emt,rec);
  }
  double tEvolTimes ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    return tEvolDireTimes(rad,emt1,emt2,rec);
  }

  // From Pythia version 8.215 onwards no longer virtual.
  double tEvolDireTimes ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return tEvolDire_FF(rad.p(),emt.p(),rec.p());
    return tEvolDire_FI(rad.p(),emt.p(),rec.p());
  }
  double tEvolDire_FF ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);
  double tEvolDire_FI ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);


  // From Pythia version 8.215 onwards no longer virtual.
  double tEvolCSTimes ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return tEvolCS_FF(rad.p(),emt.p(),rec.p());
    return tEvolCS_FI(rad.p(),emt.p(),rec.p());
  }
  double tEvolCS_FF ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);
  double tEvolCS_FI ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);

  double tEvolDireTimes ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return tEvolDire_FF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return tEvolDire_FI(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double tEvolDire_FF ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);
  double tEvolDire_FI ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);

  // From Pythia version 8.215 onwards no longer virtual.
  double zTimes ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return z_FF(rad.p(),emt.p(),rec.p());
    return z_FI(rad.p(),emt.p(),rec.p());
  }
  double z_FF ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);
  double z_FI ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);

  double m2dipTimes ( const Particle& rad, const Particle& emt,
    const Particle& rec) {
    if (rec.isFinal()) return m2dip_FF(rad.p(),emt.p(),rec.p());
    return m2dip_FI(rad.p(),emt.p(),rec.p());
  }

  double m2dip_FF ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);
  double m2dip_FI ( const Vec4& rad, const Vec4& emt,
    const Vec4& rec);

  // From Pythia version 8.215 onwards no longer virtual.
  double zTimes ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return z_FF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return z_FI(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double z_FF ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);
  double z_FI ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);

  double xaTimes ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return xa_FF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return xa_FI(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double xa_FF ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);
  double xa_FI ( const Vec4& rad, const Vec4& emt1,
    const Vec4& emt2, const Vec4& rec);

  double m2dipTimes ( const Particle& rad, const Particle& emt1,
    const Particle& emt2, const Particle& rec) {
    if (rec.isFinal()) return m2dip_FF(rad.p(),emt1.p(),emt2.p(),rec.p());
    return m2dip_FI(rad.p(),emt1.p(),emt2.p(),rec.p());
  }
  double m2dip_FF ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);
  double m2dip_FI ( const Vec4& rad, const Vec4& emt1, const Vec4& emt2,
    const Vec4& rec);

  // Functions to calculate CS variables from the evolution variables.
  double ycs_ff(double, double t, double m2d) { return t/m2d; }
  double zcs_ff(double z, double, double)     { return z; }
  double xcs_ii(double z, double, double)     { return z; }
  double vcs_ii(double, double t, double m2d) { return t/m2d;  }
  double xcs_fi(double z, double t, double m2d) {
   return m2d*z*(1-z) / (t + m2d*z*(1-z));
  }
  double zcs_fi(double z, double, double) {
    return z;
  }
  double xcs_if(double z, double, double) {
    return z;
  }
  double ucs_if(double z, double t, double m2d) {
    double u = 0.5*(1.-sqrt(1.-4.*t/m2d*z/(1.-z)));
    return u;
  }

  // Functions to calculate Dire variables from CS evolution variables.
  double t_ff_dire_from_cs(double, double, double); 
  double z_ff_dire_from_cs(double, double, double);
  double t_fi_dire_from_cs(double, double, double);
  double z_fi_dire_from_cs(double, double, double);
  double t_if_dire_from_cs(double, double, double);
  double z_if_dire_from_cs(double, double, double);
  double t_ii_dire_from_cs(double, double, double);
  double z_ii_dire_from_cs(double, double, double);

  PartonSystems* partonSystemsPtr;
  ParticleData*  particleDataPtr;
  Settings*      settingsPtr;

  int ISRevolutionMode, FSRevolutionMode;

};

//==========================================================================

class DireHelpers {

  public: 

  void setPointers (PartonSystems* pSysIn, ParticleData*  pDataIn,
    Settings* settingsIn, DireInfo* direInfoPtrIn) {
    evtUtils.setPointers (pSysIn, pDataIn, settingsIn, direInfoPtrIn);
    kinRels.setPointers (pSysIn, pDataIn, settingsIn);
  }

  DireEventUtils evtUtils;
  DireKinRelations kinRels;

};

//==========================================================================

} // end namespace Pythia8

#endif
