#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "../tools/random.hpp"

const double pi = 4 * atan(1.0);

const int D = 4;            // number of dimensions
// number of sites in t, x, y, z directions
const int N0 = 20, N1 = 8, N2 = 8, N3 = 8;
const int N[D] = { N0, N1, N2, N3 };
int spin[N0][N1][N2][N3][D];

enum Initial_state {
    init_identity,          // set all U = 1
    init_random             // set each U randomly
};

void initialize_spins(int Z_N, Initial_state state)
{
    for (int i0 = 0; i0 < N[0]; ++i0)  for (int i1 = 0; i1 < N[1]; ++i1)
    for (int i2 = 0; i2 < N[2]; ++i2)  for (int i3 = 0; i3 < N[3]; ++i3)
    for (int d = 0; d < D; ++d)
    {
        if (state == init_random)
            spin[i0][i1][i2][i3][d] = int(uniform_dist() * Z_N);
        else
            spin[i0][i1][i2][i3][d] = 0;
    }
}

double average_energy(int Z_N)
{
    double e_av = 0;
    int n[D];
    for (n[0] = 0; n[0] < N[0]; ++n[0])  for (n[1] = 0; n[1] < N[1]; ++n[1])
    for (n[2] = 0; n[2] < N[2]; ++n[2])  for (n[3] = 0; n[3] < N[3]; ++n[3])
    {
        for (int mu = 0; mu < D - 1; ++mu)
        for (int nu = mu + 1; nu < D; ++nu) {
            int n_mu[D], n_nu[D];
            for (int d = 0; d < D; ++d)
                n_mu[d] = n_nu[d] = n[d];
            n_mu[mu] = (n_mu[mu] + 1) % N[mu];
            n_nu[nu] = (n_nu[nu] + 1) % N[nu];
            int spin_sum = spin[n[0]][n[1]][n[2]][n[3]][mu]
                + spin[n_mu[0]][n_mu[1]][n_mu[2]][n_mu[3]][nu]
                - spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][mu]
                - spin[n[0]][n[1]][n[2]][n[3]][nu];
            e_av += 1 - cos(2 * pi * spin_sum / double(Z_N));
        }
    }
    return e_av / double(N[0] * N[1] * N[2] * N[3] * 6);
}

bool one_metropolis_step(int Z_N, double w_B[], int n[], int mu)
{
    bool accepted = false;
    int trial_spin = int(uniform_dist() * Z_N);
    double w = 1;
    for (int nu = 0; nu < D; ++nu) {
        if (nu == mu)
            continue;
        int n_mu[D], n_nu[D];

        // plaquette in n + nu direction
        for (int d = 0; d < D; ++d)
            n_mu[d] = n_nu[d] = n[d];
        n_mu[mu] = (n_mu[mu] + 1) % N[mu];
        n_nu[nu] = (n_nu[nu] + 1) % N[nu];
        int spin_sum = trial_spin
            + spin[n_mu[0]][n_mu[1]][n_mu[2]][n_mu[3]][nu]
            - spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][mu]
            - spin[n[0]][n[1]][n[2]][n[3]][nu];
        spin_sum = (spin_sum + 2 * Z_N) % Z_N;
        w *= w_B[spin_sum];
        spin_sum = spin[n[0]][n[1]][n[2]][n[3]][mu]
            + spin[n_mu[0]][n_mu[1]][n_mu[2]][n_mu[3]][nu]
            - spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][mu]
            - spin[n[0]][n[1]][n[2]][n[3]][nu];
        spin_sum = (spin_sum + 2 * Z_N) % Z_N;
        w /= w_B[spin_sum];

        // plaquette in n - nu direction
        int n_mn[D];    // n + mu - nu
        for (int d = 0; d < D; ++d)
            n_mn[d] = n_nu[d] = n[d];
        n_mn[mu] = (n_mn[mu] + 1) % N[mu];
        n_mn[nu] = (n_mn[nu] - 1 + N[nu]) % N[nu];
        n_nu[nu] = (n_nu[nu] - 1 + N[nu]) % N[nu];
        spin_sum = - trial_spin
            - spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][nu]
            + spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][mu]
            + spin[n_mn[0]][n_mn[1]][n_mn[2]][n_mn[3]][nu];
        spin_sum = (spin_sum + 2 * Z_N) % Z_N;
        w *= w_B[spin_sum];
        spin_sum = - spin[n[0]][n[1]][n[2]][n[3]][mu]
            - spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][nu]
            + spin[n_nu[0]][n_nu[1]][n_nu[2]][n_nu[3]][mu]
            + spin[n_mn[0]][n_mn[1]][n_mn[2]][n_mn[3]][nu];
        spin_sum = (spin_sum + 2 * Z_N) % Z_N;
        w /= w_B[spin_sum];
    }

    // Metropolis test
    if (w > 1 || w > uniform_dist()) {
        spin[n[0]][n[1]][n[2]][n[3]][mu] = trial_spin;
        accepted = true;
    }
    return accepted;
}

void sweep_update_lattice(int Z_N, double beta)
{
    // compute exponential Boltzmann weights
    double w_B[Z_N];
    for (int j = 0; j < Z_N; ++j)
        w_B[j] = exp(- beta * (1 - cos(2 * pi * j / double(Z_N))));

    int accepted_steps = 0;
    int n[D];
    for (n[0] = 0; n[0] < N[0]; ++n[0])  for (n[1] = 0; n[1] < N[1]; ++n[1])
    for (n[2] = 0; n[2] < N[2]; ++n[2])  for (n[3] = 0; n[3] < N[3]; ++n[3])
    {
        for (int mu = 0; mu < D; ++mu)
            if (one_metropolis_step(Z_N, w_B, n, mu))
                ++accepted_steps;
    }
}

void thermal_cycle(int Z_N, double beta_0, int iterations)
{
    initialize_spins(Z_N, init_identity);   // cold start
    cout << " Z_" << Z_N << " Model Thermal Cycle\n"
         << " Iter\tbeta\tE\n"
         << ' ' << 0 << '\t' << beta_0 << '\t' << average_energy(Z_N) << '\n';

    ofstream file("abelian.data");

    for (int iter = 0; iter < iterations; ++iter) {

        double beta = beta_0;
        if (iter < iterations / 2)
            beta *= (iterations / 2 - 1 - iter);
        else beta *= (iter + 1 - iterations / 2);
        beta /= iterations / 2;

        for (int i = 0; i < 1; ++i)
            sweep_update_lattice(Z_N, beta);

        if ((iter+1) % 16 == 0) {
            double e_av = average_energy(Z_N);
            cout << ' ' << iter + 1 << '\t' << beta << '\t'
                 << e_av << '\n';
            file << beta << '\t' << e_av << '\n';
        }
    }
    cout << " Output in file abelian.data" << endl;
}

int main()
{
    cout << " Monte Carlo Simulation of 4-D Abelian Gauge Models\n"
         << " --------------------------------------------------\n"
         << " N_t = " << N[0] << ", N_x = " << N[1] << ", N_y = " << N[2]
         << ", N_z = " << N[3] << ", # spins = " << N[0]*N[1]*N[2]*N[3]*D
         << endl;

    int Z_N = 8;
    double beta_0 = 3.5;        // starting value for thermal cycle
    int iterations = 7000;
    thermal_cycle(Z_N, beta_0, iterations);
}
