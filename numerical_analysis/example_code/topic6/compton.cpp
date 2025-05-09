#include <cmath>
#include <complex>
#include <cstdlib>
#include <iostream>
using namespace std;

const double pi = 4 * atan(1.0);

#include "../tools/quadrature.hpp"

double omega;               // incident photon angular frequency
complex<double> ep_10;      // x-component of incident photon polarization
complex<double> ep_20;      // y-component
complex<double> ep_1;       // in-plane scattered photon polarization
complex<double> ep_2;       // perpendicular component

double f(const Vector& x, const double wgt)
{
    double theta = x[0];
    double phi = x[1];
    double omega_prime = omega / (1 + omega * (1 - cos(theta)));

    // compute polarization dot products
    complex<double> ep_star_dot_ep0 =
        conj(ep_1 * cos(theta) * cos(phi) - ep_2 * sin(phi)) * ep_10 +
        conj(ep_1 * cos(theta) * sin(phi) + ep_2 * cos(phi)) * ep_20;
    complex<double> ep_dot_ep0 =
        (ep_1 * cos(theta) * cos(phi) - ep_2 * sin(phi)) * ep_10 +
        (ep_1 * cos(theta) * sin(phi) + ep_2 * cos(phi)) * ep_20;

    return pow(omega_prime / omega, 2.0) *
        (norm(ep_star_dot_ep0) + pow(omega - omega_prime, 2.0) /
        (4 * omega * omega_prime) * (1 + norm(ep_star_dot_ep0) -
            norm(ep_dot_ep0)));
}

int main()
{
    cout << " Relativistic Compton Scattering Cross Sections using VEGAS\n";

    double tgral, sd, chi2a;
    Vector regn(4);
    regn[0] = 0.0;  regn[2] = pi;       // 0 < theta < pi
    regn[1] = 0.0;  regn[3] = 2 * pi;   // 0 < phi < 2 pi

    // set global parameters
    omega = 0.0025;                     // incident angular frequency
    cout << " omega = " << omega << endl;

    // define and normalize polarization vectors
    ep_10 = 1.0;
    ep_20 = 0.0;
    ep_1 = 1.0;
    ep_2 = 0.0;
    double n0 = sqrt(norm(ep_10) + norm(ep_20)),
            n = sqrt(norm(ep_1) + norm(ep_2));
    ep_10 /= n0;
    ep_20 /= n0;
    ep_1 /= n;
    ep_2 /= n;

    int init = 0;                       // initialize grid
    int ncall = 50000;                  // number of function evaluations
    int itmx = 10;                      // number of iterations
    int nprn = 0;                       // print some info after each iteration

    vegas(regn, f, init, ncall, itmx, nprn, tgral, sd, chi2a);
    cout << " sigma_tot = " << tgral << " +/- " << sd << endl;
}
