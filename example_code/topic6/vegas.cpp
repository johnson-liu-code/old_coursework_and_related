#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#include "../tools/quadrature.hpp"

double f(const Vector& x, const double wgt)
{
    double dx2 = 0.0;
    for (int d = 0; d < 4; d++)
        dx2 += pow(x[d] - 0.5, 2.0);
    return exp(-dx2 * 100.0) * 1013.2118364296088;
}

int main()
{
    double tgral, sd, chi2a;
    Vector regn(8);
    regn[0] = -1.0; regn[4] = 1.0;  // x_0
    regn[1] = 0.0;  regn[5] = 1.0;  // x_1
    regn[2] = 0.0;  regn[6] = 1.0;  // x_2
    regn[3] = 0.0;  regn[7] = 1.0;  // x_3
    int init = 0;               // initialize grid
    int ncall = 1000;           // number of function calls
    int itmx = 10;              // number of iterations
    int nprn = 0;               // print some info after each iteration
    time_t now;
    time(&now);
    seed_random(now);           // current time in seconds since 1/1/70
    vegas(regn, f, init, ncall, itmx, nprn, tgral, sd, chi2a);
}
