// definitions and functions to solve Sod's shock tube problem

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>

using namespace std;

#include "../tools/cfdalg.hpp"   // Roe's Riemann solver for Euler equations
                                 // Laney's upwind Godunov Riemann solver

double L = 1;                    // length of shock tube
double gama = 1.4;               // ratio of specific heats
int N = 200;                     // number of grid points

double CFL = 0.9;                // Courant-Friedrichs-Lewy number
double nu = 0.0;                 // artificial viscosity coefficient

double **U;                      // solution with 3 components
double **newU;                   // new solution
double **F;                      // flux with 3 components
double *vol;                     // for Roe solver

double h;                        // lattice spacing
double tau;                      // time step

int step;

void allocate() {
    static int oldN = 0;
    if (N != oldN) {
        if (U != 0) {
            for (int j = 0; j < oldN; j++) {
                delete [] U[j]; delete newU[j]; delete [] F[j];
            }
            delete [] U; delete [] newU; delete [] F; delete [] vol;
        }
        oldN = N;
        U = new double* [N];
        newU = new double* [N];
        F = new double* [N];
        vol = new double [N];
        for (int j = 0; j < N; j++) {
            U[j] = new double [3];
            newU[j] = new double [3];
            F[j] = new double [3];
        }
    }
}

double cMax() {
    double uMax = 0;
    for (int i = 0; i < N; i++) {
        if (U[i][0] == 0)
            continue;
        double rho = U[i][0];
        double u = U[i][1] / rho;
        double p = (U[i][2] - rho * u * u / 2) * (gama - 1);
        double c = sqrt(gama * abs(p) / rho);
        if (uMax < c + abs(u))
            uMax = c + abs(u);
    }
    return uMax;
}

void initialize() {

    allocate();
    h = L / (N - 1);
    for (int j = 0; j < N; j++) {
        double rho = 1, p = 1, u = 0;
        if (j > N / 2)
            rho = 0.125, p = 0.1;
        double e = p / (gama - 1) + rho * u * u / 2;
        U[j][0] = rho;
        U[j][1] = rho * u;
        U[j][2] = e;
        vol[j] = 1;
    }
    tau = CFL * h / cMax();
    step = 0;
}

void boundaryConditions(double **U) {

    // reflection boundary conditions at the tube ends
    U[0][0] = U[1][0];
    U[0][1] = -U[1][1];
    U[0][2] = U[1][2];
    U[N - 1][0] = U[N - 2][0];
    U[N - 1][1] = -U[N - 2][1];
    U[N - 1][2] = U[N - 2][2];
}

void LaxWendroffStep() {

    // compute flux F from U
    for (int j = 0; j < N; j++) {
        double rho = U[j][0];
        double m = U[j][1];
        double e = U[j][2];
        double p = (gama - 1) * (e - m * m / rho / 2);
        F[j][0] = m;
        F[j][1] = m * m / rho + p;
        F[j][2] = m / rho * (e + p);
    }

    // half step
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            newU[j][i] = (U[j + 1][i] + U[j][i]) / 2 -
                         tau / 2 / h * (F[j + 1][i] - F[j][i]);
    boundaryConditions(newU);

    // compute flux at half steps
    for (int j = 0; j < N; j++) {
        double rho = newU[j][0];
        double m = newU[j][1];
        double e = newU[j][2];
        double p = (gama - 1) * (e - m * m / rho / 2);
        F[j][0] = m;
        F[j][1] = m * m / rho + p;
        F[j][2] = m / rho * (e + p);
    }

    // step using half step flux
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            newU[j][i] = U[j][i] - tau / h * (F[j][i] - F[j - 1][i]);

    // update U from newU
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            U[j][i] = newU[j][i];
}

void LaxFriedrichsStep() {

    // compute flux F from U
    for (int j = 0; j < N; j++) {
        double rho = U[j][0];
        double m = U[j][1];
        double e = U[j][2];
        double p = (gama - 1) * (e - m * m / rho / 2);
        F[j][0] = m;
        F[j][1] = m * m / rho + p;
        F[j][2] = m / rho * (e + p);
    }

    // Lax-Friedrichs step
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            newU[j][i] = (U[j + 1][i] + U[j - 1][i]) / 2 -
                         tau / h * (F[j + 1][i] - F[j - 1][i]);
    boundaryConditions(newU);

    // update U from newU
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            U[j][i] = newU[j][i];
}

void upwindGodunovStep() {

    // find fluxes using Riemann solver
    for (int j = 0; j < N - 1; j++)
        Riemann(U[j], U[j + 1], F[j]);

    // update U
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            U[j][i] -= tau / h * (F[j][i] - F[j - 1][i]);
}

void RoeStep() {

    // compute fluxes at cell boundaries
    int icntl;
    RoeSolve(h, tau, gama, vol, U, F, N - 2, icntl);

    // update U
    for (int j = 1; j < N - 1; j++)
        for (int i = 0; i < 3; i++)
            U[j][i] -= tau / h * (F[j + 1][i] - F[j][i]);
}

void LapidusViscosity() {

    // store Delta_U values in newU
    for (int j = 1; j < N; j++)
        for (int i = 0; i < 3; i++)
            newU[j][i] = U[j][i] - U[j - 1][i];

    // multiply Delta_U by |Delta_U|
    for (int j = 1; j < N; j++)
        for (int i = 0; i < 3; i++)
            newU[j][i] *= abs(newU[j][i]);

    // add artificial viscosity
    for (int j = 2; j < N; j++)
        for (int i = 0; i < 3; i++)
            U[j][i] += nu * tau / h * (newU[j][i] - newU[j - 1][i]);
}
