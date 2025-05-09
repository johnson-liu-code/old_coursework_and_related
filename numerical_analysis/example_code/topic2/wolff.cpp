// Wolff cluster algorithm for the 2-D Ising Model

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>
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
int steps;                      // number of Monte Carlo steps

void initialize ( ) {
    s = new int* [Lx];
    for (int i = 0; i < Lx; i++)
        s[i] = new int [Ly];
    for (int i = 0; i < Lx; i++)
        for (int j = 0; j < Ly; j++)
            s[i][j] = std_rand() < 0.5 ? +1 : -1;   // hot start
    steps = 0;
}

bool **cluster;                     // cluster[i][j] = true if i,j belongs
double addProbability;              // 1 - e^(-2J/kT)

void initializeClusterVariables() {

    // allocate 2-D array for spin cluster labels
    cluster = new bool* [Lx];
    for (int i = 0; i < Lx; i++)
        cluster[i] = new bool [Ly];

    // compute the probability to add a like spin to the cluster
    addProbability = 1 - exp(-2*J/T);
}

// declare functions to implement Wolff algorithm
void growCluster(int i, int j, int clusterSpin);
void tryAdd(int i, int j, int clusterSpin);

void oneMonteCarloStep() {

    // no cluster defined so clear the cluster array
    for (int i = 0; i < Lx; i++)
    for (int j = 0; j < Lx; j++)
        cluster[i][j] = false;

    // choose a random spin and grow a cluster
    int i = int(std_rand() * Lx);
    int j = int(std_rand() * Ly);
    growCluster(i, j, s[i][j]);

    ++steps;
}

void growCluster(int i, int j, int clusterSpin) {

    // mark the spin as belonging to the cluster and flip it
    cluster[i][j] = true;
    s[i][j] = -s[i][j];

    // find the indices of the 4 neighbors
    // assuming periodic boundary conditions
    int iPrev = i == 0    ? Lx-1 : i-1;
    int iNext = i == Lx-1 ? 0    : i+1;
    int jPrev = j == 0    ? Ly-1 : j-1;
    int jNext = j == Ly-1 ? 0    : j+1;

    // if the neighbor spin does not belong to the
    // cluster, then try to add it to the cluster
    if (!cluster[iPrev][j])
        tryAdd(iPrev, j, clusterSpin);
    if (!cluster[iNext][j])
        tryAdd(iNext, j, clusterSpin);
    if (!cluster[i][jPrev])
        tryAdd(i, jPrev, clusterSpin);
    if (!cluster[i][jNext])
        tryAdd(i, jNext, clusterSpin);
}

void tryAdd(int i, int j, int clusterSpin) {
    if (s[i][j] == clusterSpin)
        if (std_rand() < addProbability)
            growCluster(i, j, clusterSpin);
}

// variables to measure chi and its error estimate
double chi;                // current susceptibility per spin
double chiSum;             // accumulate chi values
double chiSqdSum;          // accumulate chi^2 values
int nChi;                  // number of values accumulated

// variables to measure autocorrelation time
int nSave = 10;            // number of values to save
double cChiSum;            // accumulate
list<double> chiSave;      // the saved values
double *cChi;              // correlation sums
int nCorr;                 // number of values accumulated

// variables to estimate fluctuations by blocking
int stepsPerBlock = 1000;  // suggested in Wolff paper
double chiBlock;           // used to calculate block average
double chiBlockSum;        // accumulate block <chi> values
double chiBlockSqdSum;     // accumulate block <chi>^2 values
int stepInBlock;           // number of steps in current block
int blocks;                // number of blocks

void initializeObservables() {
    chiSum = chiSqdSum = 0;
    nChi = 0;
    chiBlock = chiBlockSum = chiBlockSqdSum = 0;
    stepInBlock = blocks = 0;
    cChiSum = 0;
    cChi = new double [nSave + 1];
    for (int i = 0; i <= nSave; i++)
        cChi[i] = 0;
    nCorr = 0;
}

void measureObservables() {

    // observables are derived from the magnetic moment
    int M = 0;
    for (int i = 0; i < Lx; i++)
    for (int j = 0; j < Ly; j++)
        M += s[i][j];
    chi = M * double(M) / double(N);
    // accumulate values
    chiSum += chi;
    chiSqdSum += chi * chi;
    ++nChi;
    // accumulate correlation values
    if (chiSave.size() == nSave) {
        cChiSum += chi;
        cChi[0] += chi * chi;
        ++nCorr;
        list<double>::const_iterator iter = chiSave.begin();
        for (int i = 1; i <= nSave; i++)
            cChi[i] += *iter++ * chi;
        chiSave.pop_back();     // remove oldest saved chi value
    }
    chiSave.push_front(chi);    // add current chi value
    // accumulate block values
    chiBlock += chi;
    ++stepInBlock;
    if (stepInBlock == stepsPerBlock) {
        chiBlock /= stepInBlock;
        chiBlockSum += chiBlock;
        chiBlockSqdSum += chiBlock * chiBlock;
        ++blocks;
        stepInBlock = 0;
        chiBlock = 0;
    }
}

// averages of observables
double chiAve;               // average susceptibility per spin
double chiError;             // Monte Carlo error estimate
double chiStdDev;            // Standard deviation error from blocking
double tauChi;               // autocorrelation time
double tauEffective;         // effective autocorrelation time

void computeAverages()  {

    // average susceptibility per spin
    chiAve = chiSum / nChi;

    // Monte Carlo error estimate
    chiError = chiSqdSum / nChi;
    chiError = sqrt(chiError - chiAve * chiAve);
    chiError /= sqrt(double(nChi));
    // exponential correlation time
    tauChi = 0;
    double cAve = cChiSum / nCorr;
    double c0 = cChi[0] / nCorr - cAve * cAve;
    for (int i = 1; i <= nSave; i++) {
         double c = (cChi[i] / nCorr - cAve * cAve) / c0;
         if (c > 0.01) {
             tauChi += -i/log(c);
         } else {
             tauChi /= (i - 1);
             break;
         }
         if (i == nSave)
             tauChi /= nSave;
    }
    // standard deviation from blocking
    double chiBlockAve = chiBlockSum / blocks;
    chiStdDev = chiBlockSqdSum / blocks;
    chiStdDev = sqrt(chiStdDev - chiBlockAve * chiBlockAve);
    chiStdDev /= sqrt(double(blocks));
    // effective autocorrelation time
    tauEffective = chiStdDev / chiError;
    tauEffective *= tauEffective / 2;
}

int main() {

    cout << " Two-dimensional Ising Model - Wolff Cluster Algorithm\n"
         << " -----------------------------------------------------\n"
         << " Enter number of spins L in each direction: ";
    cin >> Lx;
    Ly = Lx;
    N = Lx * Ly;
    cout << " Enter temperature T: ";
    cin >> T;
    cout << " Enter number of Monte Carlo steps: ";
    int MCSteps;
    cin >> MCSteps;

    initialize();
    initializeClusterVariables();
    int thermSteps = MCSteps / 5;
    cout << " Performing " << thermSteps
         << " thermalization steps ..." << flush;
    for (int i = 0; i < thermSteps; i++)
        oneMonteCarloStep();

    int numBlocks = MCSteps / stepsPerBlock;
    if (numBlocks < 5) {
        numBlocks = 5;
        stepsPerBlock = ceil(MCSteps / double(5));
    }
    MCSteps = numBlocks * stepsPerBlock;
    cout << " done\n Performing " << MCSteps << "production steps int "
         << numBlocks << " blocks ..." << flush;
    initializeObservables();
    for (int i = 0; i < MCSteps; i++) {
        oneMonteCarloStep();
        measureObservables();
    }
    cout << " done" << endl;
    computeAverages();
    cout << "\n       Average chi per spin = " << chiAve
         << "\n Monte Carlo error estimate = " << chiError
         << "\n   Autocorrelation time tau = " << tauChi
         << "\n   Std. Dev. using blocking = " << chiStdDev
         << "\n              Effective tau = " << tauEffective << endl;
}
