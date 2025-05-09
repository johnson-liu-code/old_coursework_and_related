// Zabusky and Kruskal, Phys. Rev. Lett. 15, 240-243 (1965)

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main()
{

    const double pi = 4 * atan(1.0);

    double delta = 0.022;

    // spatial grid
    int N = 256;
    double L = 2.0;
    double h = L / double(N);       // spatial interval

    vector<double> x(N);
    for (int i = 0; i < N; ++i)
        x[i] = i * h;

    // initialize solution vector on spatial grid
    vector<double> u(N);
    for (int i = 0; i < N; ++i)
        u[i] = cos(pi * x[i]);

    // write initial waveform to file
    ofstream ofs("kdv.data");
    for (int i = 0; i < N; ++i)
        ofs << x[i] << '\t' << u[i] << '\n';
    ofs << '\n';

    // temporal grid
    double T_B = 1 / pi;
    double k = h * h * h;     // time step must satisfy CFL criterion

    // take one time step to prime the algorithm
    vector<double> u_minus(N);
    for (int i = 0; i < N; ++i) {
        u_minus[i] = u[i];
        // u = cos(pi(x-ut) if delta^2u_xxx is negligible
        u[i] = cos(pi * (x[i] - u[i] * k));
    }

    double t_max = 4 * T_B;
    double t = 0;

    vector<double> u_plus(N);

    for (t = 0; t <= t_max; t += k) {

        // write waveform to file at selected times
        if (abs(t - T_B) <  k / 2 ||
            abs(t - 3.6 * T_B) < k / 2)
        {
            for (int i = 0; i < N; ++i)
                ofs << x[i] << '\t' << u[i] << '\n';
            ofs << '\n';
        }

        // use algorithm in Footnote 6 to evolve in time
        for (int i = 0; i < N; ++i) {
            int ip2 = (i + 2 + N) % N, ip1 = (i + 1 + N) % N,
                im1 = (i - 1 + N) % N, im2 = (i - 2 + N) % N;
            u_plus[i] = u_minus[i] - (1 / 3.0) * (k / h) *
                (u[ip1] + u[i] + u[im1]) * (u[ip1] - u[im1]) -
                (delta * delta * k / (h * h * h)) *
                (u[ip2] - 2.0 * u[ip1] + 2.0 * u[im1] - u[im2]);
        }
        for (int i = 0; i < N; ++i) {
            u_minus[i] = u[i];
            u[i] = u_plus[i];
        }
    }

    return 0;
}
