/*
    Uses http://www.netlib.org/lapack/
    c++  -o helium-hf  helium-hf.cpp  -llapack
 */

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "lapack.hpp"

const double pi = 4 * atan(1.0);

typedef vector< vector<double> > matrix;
typedef vector< vector< vector< vector<double> > > > matrix4;

vector<double> C, alpha;
matrix A, H, S;
matrix4 Q;

void initialize(size_t N)
{
    C.resize(N);
    alpha.resize(N);
    A.resize(N);
    H.resize(N);
    S.resize(N);
    Q.resize(N);
    for (int i = 0; i < N; i++) {
        A[i].resize(N);
        H[i].resize(N);
        S[i].resize(N);
        Q[i].resize(N);
        for (int j = 0; j < N; j++) {
            Q[i][j].resize(N);
            for (int k = 0; k < N; k++)
                Q[i][j][k].resize(N);
        }
    }
}

void compute_coefficients()
{
    int N = alpha.size();
    for (int p = 0; p < N; ++p) {
        for (int q = 0; q < N; ++q) {
            H[p][q] = 3 * alpha[p] * alpha[q] * pow(pi, 3.0/2.0)
                * pow(alpha[p] + alpha[q], 5.0/2.0)
                - 2 * pi / (alpha[p] + alpha[q]);
            S[p][q] = pow(pi / (alpha[p] + alpha[q]), 3.0/2.0);
            for (int r = 0; r < N; ++r)
                for (int s = 0; s < N; ++s)
                    Q[p][q][r][s] = 2 * pow(pi, 5.0/2.0)
                        / (alpha[p] + alpha[q])
                        / (alpha[r] + alpha[s])
                        / sqrt(alpha[p] + alpha[q] + alpha[r] + alpha[s]);
        }
    }
}

int main()
{
    cout << " Hartree-Fock method for the Helium Atom using 4 s-wave GTO\n"
         << " Uses LAPACK DSYGVD to solve the Generalized Eigenvalue Problem"
         << endl;

    size_t N = 4;
    initialize(N);
    alpha[0] = 0.297104;
    alpha[1] = 1.236745;
    alpha[2] = 5.749982;
    alpha[0] = 38.21667;

    C[0] = C[1] = C[2] = C[3] = 1.0 / sqrt(4.0);

    return 0;
}
