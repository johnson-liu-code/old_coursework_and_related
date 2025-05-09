// Autocorrelation time in the 2-D Ising Model

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>                 // to save values for autocorrelations
using namespace std;

inline double std_rand()
{
    return rand() / (RAND_MAX + 1.0);
}

double J = +1;                  // ferromagnetic coupling
int Lx, Ly;                     // number of spins in x and y
int N;                          // number of spins
int **s;                        // the spins
double T;                       // temperature
double H = 0;                   // magnetic field

double w[17][3];                // Boltzmann factors

void computeBoltzmannFactors ( ) {
     for (int i = -8; i <= 8; i += 4) {
          w[i + 8][0] = exp( - (i * J + 2 * H) / T);
          w[i + 8][2] = exp( - (i * J - 2 * H) / T);
     }
}

double eAv, mAv;                // accumulators to compute <e> and <m>
int nSave = 10;                 // values to save for autocorrelations
list<double> eSave, mSave;      // saved energy and magnetization values
double *cee, *cmm;              // energy and magnetization correlation sums
int nCorr;                      // number of values accumulated in sums

void initializeCorrelations() {
     eAv = mAv = 0;
     eSave.clear();
     mSave.clear();
     if (cee != NULL) delete [] cee;
     if (cmm != NULL) delete [] cmm;
     cee = new double [nSave + 1];
     cmm = new double [nSave + 1];
     for (int i = 0; i <= nSave; i++)
          cee[i] = cmm[i] = 0;
     nCorr = 0;
}

int steps = 0;                  // steps so far

void initialize ( ) {
     s = new int* [Lx];
     for (int i = 0; i < Lx; i++)
          s[i] = new int [Ly];
     for (int i = 0; i < Lx; i++)
          for (int j = 0; j < Ly; j++)
               s[i][j] = std_rand() < 0.5 ? +1 : -1;   // hot start
     computeBoltzmannFactors();
     steps = 0;
}

bool MetropolisStep ( ) {

     // choose a random spin
     int i = int(Lx*std_rand());
     int j = int(Ly*std_rand());

     // find its neighbors using periodic boundary conditions
     int iPrev = i == 0 ? Lx-1 : i-1;
     int iNext = i == Lx-1 ? 0 : i+1;
     int jPrev = j == 0 ? Ly-1 : j-1;
     int jNext = j == Ly-1 ? 0 : j+1;

     // find sum of neighbors
     int sumNeighbors = s[iPrev][j] + s[iNext][j] + s[i][jPrev] + s[i][jNext];
     int delta_ss = 2*s[i][j]*sumNeighbors;

     // ratio of Boltzmann factors
     double ratio = w[delta_ss+8][1+s[i][j]];
     if (std_rand() < ratio) {
          s[i][j] = -s[i][j];
          return true;
     } else return false;
}

double acceptanceRatio;

void oneMonteCarloStepPerSpin ( ) {
     int accepts = 0;
     for (int i = 0; i < N; i++)
          if (MetropolisStep())
               ++accepts;
     acceptanceRatio = accepts/double(N);
     ++steps;
}

double magnetizationPerSpin ( ) {
     int sSum = 0;
     for (int i = 0; i < Lx; i++)
     for (int j = 0; j < Ly; j++) {
          sSum += s[i][j];
     }
     return sSum / double(N);
}

double energyPerSpin ( ) {
     int sSum = 0, ssSum = 0;
     for (int i = 0; i < Lx; i++)
     for (int j = 0; j < Ly; j++) {
          sSum += s[i][j];
          int iNext = i == Lx-1 ? 0 : i+1;
          int jNext = j == Ly-1 ? 0 : j+1;
          ssSum += s[i][j]*(s[iNext][j] + s[i][jNext]);
     }
     return -(J*ssSum + H*sSum)/N;
}

void accumulateCorrelations() {

     // calculate current energy and magnetization
     double e = energyPerSpin();
     double m = magnetizationPerSpin();

     // accumulate averages and correlation products
     if (eSave.size() == nSave) {   // if nSave values have been saved
          ++nCorr;
          eAv += e;
          mAv += m;
          cee[0] += e * e;
          cmm[0] += m * m;
          list<double>::const_iterator ie = eSave.begin(), im = mSave.begin();
          for (int i = 1; i <= nSave; i++) {
               cee[i] += *ie++ * e;
               cmm[i] += *im++ * m;
          }

          // discard the oldest values
          eSave.pop_back();
          mSave.pop_back();
     }

     // save the current values
     eSave.push_front(e);
     mSave.push_front(m);
}

double tau_e, tau_m;

void computeAutocorrelationTimes() {

     // energy correlation
     double av = eAv / nCorr;
     double c0 = cee[0] / nCorr - av * av;
     tau_e = 0;
     for (int i = 1; i <= nSave; i++)
          tau_e += (cee[i] / nCorr - av * av) / c0;

     // magnetization correlation
     av = mAv / nCorr;
     c0 = cmm[0] / nCorr - av * av;
     tau_m = 0;
     for (int i = 1; i <= nSave; i++)
          tau_m += (cmm[i] / nCorr - av * av) / c0;
}

int main (int argc, char *argv[]) {

     cout << " Two-dimensional Ising Model - Autocorrelation times\n"
          << " ---------------------------------------------------\n"
          << " Enter number of spins L in each direction: ";
     cin >> Lx;
     Ly = Lx;
     N = Lx * Ly;
     double T1, T2;
     cout << " Enter starting temperature: ";
     cin >> T1;
     cout << " Enter ending temperature: ";
     cin >> T2;
     cout << " Enter number of temperature steps: ";
     int TSteps;
     cin >> TSteps;
     cout << " Enter number of Monte Carlo steps: ";
     int MCSteps;
     cin >> MCSteps;

     initialize();
     ofstream file("auto.data");
     int thermSteps = int(0.2 * MCSteps);
     for (int i = 0; i <= TSteps; i++) {
          T = T1 + i * (T2 - T1) / double(TSteps);
          computeBoltzmannFactors();
          for (int s = 0; s < thermSteps; s++)
               oneMonteCarloStepPerSpin();
          initializeCorrelations();
          for (int s = 0; s < MCSteps; s++) {
               oneMonteCarloStepPerSpin();
               accumulateCorrelations();
          }
          computeAutocorrelationTimes();
          cout << " T = " << T << "\ttau_e = " << tau_e
               << "\ttau_m = " << tau_m << endl;
          file << T << '\t' << tau_e << '\t' << tau_m << '\n';
     }
     file.close();
}
