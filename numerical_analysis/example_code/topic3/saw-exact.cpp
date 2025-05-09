#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

const int rMax = 50;                // maximum length of walk
const int nMax = 2 * rMax + 1;      // maximum number of lattice points in x, y
bool occupied[nMax][nMax];          // true if lattice site is occupied

inline int index(int xORy) {        // translate x,y to array index
    return xORy + rMax;
}

bool isOccupied(int x, int y) {     // check if site is occupied
    return occupied[index(y)][index(x)];
}

void occupy(int x, int y) {         // mark the site occupied
    occupied[index(y)][index(x)] = true;
}

void clear(int x, int y) {          // mark the site empty
    occupied[index(y)][index(x)] = false;
}

int nSteps;                         // desired number of steps in the walk
int steps;                          // number of steps so far
unsigned long walks;                // number of walks so far with nSteps
double r2av;                        // accumulator for <r^2>
double r4av;                        // accumulator for <r^4>
int culDeSacs;                      // accumulator for cul-de-sacs
int doubleCulDeSacs;                // accumulator for double cul-de-sacs

void initialize() {                 // empty sites and zero variables
    for (int y = -rMax; y <= rMax; y++)
        for (int x = -rMax; x <= rMax; x++)
            clear(x, y);
    r2av = r4av = 0;
    walks = 0;
    culDeSacs = doubleCulDeSacs = 0;
    occupy(0, 0);
    steps = 1;
}

int deadEnds(int x, int y, bool& isDoubleCulDeSac) {

    // count number of dead ends for this walk
    int deadEnds = 0;

    // is the start point surrounded by 4 occupied sites?
    if (isOccupied( 1, 0) && isOccupied(0,  1) &&
        isOccupied(-1, 0) && isOccupied(0, -1)    ) ++deadEnds;

    // is the end point surrounded by 4 occupied sites?
    if (isOccupied(x + 1, y) && isOccupied(x, y + 1) &&
        isOccupied(x - 1, y) && isOccupied(x, y - 1)   ) ++deadEnds;

    isDoubleCulDeSac = deadEnds == 2  && x*x + y*y != 1;

    return deadEnds;
}

void visit(int x, int y) {

    if (isOccupied(x, y))
      return;                       // back up and continue

    occupy(x, y);                   // add this site to the walk
    ++steps;

    if (steps <= nSteps) {          // recursively visit
        visit(x + 1, y);            // East neighbor
        visit(x, y + 1);            // North neighbor
        visit(x - 1, y);            // West neighbor
        visit(x, y - 1);            // South neighbor
    } else {                        // have desired length
       ++walks;
       double r2 = x*x + y*y;       // start-to-end distance squared
       r2av += r2;
       r4av += r2 * r2;
       bool isDoubleCulDeSac;
       culDeSacs += deadEnds(x, y, isDoubleCulDeSac);
       if (isDoubleCulDeSac)
           ++doubleCulDeSacs;
    }

    clear(x, y);                    // remove this site from the walk
    --steps;                        // before backing up an continuing
}

int main() {

    cout << " Exact Enumeration of Self-Avoiding Walks on a Square Lattice\n"
         << " ------------------------------------------------------------\n"
         << " Enter maximum number of steps: ";
    int maxSteps;
    cin >> maxSteps;
    cout << " Steps   <r^2>       Std. Dev.  S.-A. Walks Cul-de-sacs "
         << " Double Cds    CPU secs" << endl;

    double cpuTotal = 0;
    unsigned long walksTotal = 0, cdsTotal = 0, dcdsTotal = 0;
    for (nSteps = 1; nSteps <= maxSteps; nSteps++) {
        clock_t startTime = clock();
        initialize();
        visit(1, 0);
        r2av /= walks;
        r4av /= walks;
        double stdDev = sqrt(r4av - r2av * r2av);
        walksTotal +=  walks;
        cdsTotal += culDeSacs;
        dcdsTotal += doubleCulDeSacs;
        clock_t endTime = clock();
        double cpu = double(endTime - startTime) / CLOCKS_PER_SEC;
        cpuTotal += cpu;
        cout << right << setw(4)  << nSteps              << "     "
             << left  << setw(10) << r2av                << "  "
             << left  << setw(10) << stdDev              << "  "
             << right << setw(10) << 4 * walks           << "  "
             << right << setw(10) << 4 * culDeSacs       << "  "
             << right << setw(10) << 4 * doubleCulDeSacs << "    "
             << left  << setw(8)  << cpu                 << '\n';
    }
    cout << " -------------------------------------------------------------"
         << "-----------------\n Totals                          "
         << right << setw(10) << 4 * walksTotal << "  "
         << right << setw(10) << 4 * cdsTotal   << "  "
         << right << setw(10) << 4 * dcdsTotal  << "    "
         << left  << setw(8)  << cpuTotal       << endl;
}
