#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "../tools/linalg.hpp"

const double pi = 4 * atan(1.0);

// physical constants
double hbar = 1.0;                  // Planck's constant / 2pi
double m = 1.0;                     // electron mass
double e = 1.0;                     // proton charge

// LCAO variational wave function
// psi = sum( d_i g(alpha_i, r) ) for i = 0, 1, 2, ...
// assume d_0 = 1 and vary alpha_0, d_1, alpha_1, d_2, alpha_2, ...
// vector of variational parameters

int N = 2;                          // number of Gaussians
// initial guess for p = [ alpha_0, d_1, alpha_1 ]
Vector p(1.0, 1.0, 0.5);            // vector of 2N-1 variational parameters

double accuracy = 1.0e-6;           // desired accuracy for numerical operations

double g(double alpha, double r)    // normalized s-wave Gaussian orbital
{
    return pow(2.0 * alpha / pi, 3.0 / 4.0) * exp(-alpha * r * r);
}

double Sij(                         // matrix elements of S
    double alpha_i, double alpha_j)
{
    return pow(pi / (alpha_i + alpha_j), 3.0 / 2.0);
}

double Tij(                         // matrix elements of T
    double alpha_i, double alpha_j)
{
    return 3.0 * hbar**2 / m * alpha_i * alpha_j *
        pow(pi, 3.0 / 2.0) / pow(alpha_i + alpha_j, 5.0 / 2.0);
}

double Vij(                         // matrix elements of V
    double alpha_i, double alpha_j)
{
    return - 2.0 * e*e * pi / (alpha_i + alpha_j);
}

double E(double alpha, double d)    // energy as function of N alpha_i and d_i
{
    double S = 0.0, H = 0.0;
    for i in range(len(alpha)):
        for j in range(len(alpha)):
            fac = (alpha[i] * alpha[j])**(3.0/4.0)* d[i] * d[j]
            H += fac * (Tij(alpha[i], alpha[j]) + Vij(alpha[i], alpha[j]))
            S += fac * Sij(alpha[i], alpha[j])
    return H / S

def func(p):                // function for BFGS minimization
    // assume p = [ alpha_0, d_1, alpha_1, d_2, alpha_2, ... ]
    alpha = [ max(p[2 * i], accuracy) for i in range(N) ]
    d = [ 1.0 ]
    d.extend(p[2 * i + 1] for i in range(N - 1))
    return E(alpha, d)

def dfunc(p, g):            // gradient of func for BFGS minimization
    // use symmetric finite difference f'(x) = (f(x+eps) - f(x-eps)) / (2 eps)
    eps = 0.5 * accuracy    // finite difference
    for i in range(len(p)):
        p1 = list(p)
        p1[i] += eps
        p2 = list(p)
        p2[i] -= eps
        g[i] = (func(p1) - func(p2)) / (2 * eps)
    return

def norm(p):                // norm of LCAO
    alpha = [ p[2 * i] for i in range(N) ]
    d = [ 1.0 ]
    d.extend(p[2 * i + 1] for i in range(N - 1))
    norm = 0.0
    for i in range(N):
        for j in range(N):
            norm += Sij(alpha[i], alpha[j]) * d[i] * d[j]
    return sqrt(norm)

int main()
{
    cout << " Variational method for Hydrogen using Gaussian LCAO\n"
         << " Minimize <psi|H|psi>/<psi|psi> using BFGS algorithm" << endl;

    size_t iter = 0;
    int status;

    const gsl_multimin_fdfminimizer_type *T;
    gsl_multimin_fdfminimizer *s;

    /* Position of the minimum (1,2), scale factors
       10,20, height 30. */
    double par[5] = { 1.0, 2.0, 10.0, 20.0, 30.0 };

    gsl_vector *x;
    gsl_multimin_function_fdf my_func;

    my_func.n = 2;
    my_func.f = my_f;
    my_func.df = my_df;
    my_func.fdf = my_fdf;
    my_func.params = par;

    /* Starting point, x = (5,7) */
    x = gsl_vector_alloc (2);
    gsl_vector_set (x, 0, 5.0);
    gsl_vector_set (x, 1, 7.0);

    T = gsl_multimin_fdfminimizer_conjugate_fr;
    s = gsl_multimin_fdfminimizer_alloc (T, 2);

    gsl_multimin_fdfminimizer_set (s, &my_func, x, 0.01, 1e-4);

    do
      {
        iter++;
        status = gsl_multimin_fdfminimizer_iterate (s);

        if (status)
          break;

        status = gsl_multimin_test_gradient (s->gradient, 1e-3);

        if (status == GSL_SUCCESS)
          printf ("Minimum found at:\n");

        printf ("%5d %.5f %.5f %10.5f\n", iter,
                gsl_vector_get (s->x, 0),
                gsl_vector_get (s->x, 1),
                s->f);

      }
    while (status == GSL_CONTINUE && iter < 100);

    gsl_multimin_fdfminimizer_free (s);
    gsl_vector_free (x);
gtol = accuracy
iterations, e = ml.minimize_BFGS(p, gtol, func, dfunc)
print " number of Gaussians N = " + repr(N)
print " number of iterations = " + repr(iterations)
print " energy E = " + repr(e)
print " i\talpha_i\t\t\td_i"
exit
for i in range(N):
    alpha_i = p[2 * i]
    if i == 0:
        d_i = 1.0 / norm(p)
    else:
        d_i = p[2 * i - 1] / norm(p)
    print " " + repr(i) + "\t" + repr(p[2*i]) + "\t" + repr(d_i)
