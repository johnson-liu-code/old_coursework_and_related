// code to reproduce results in LA_1940 by Fermi, Pasta, Ulam, Tsingou

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<double> Fourier_sine_transform(
    const vector<double>& x,
    bool inverse=false)
{
    vector<double> a(x.size());
    int N = x.size() - 1;
    const double pi = 4 * atan(1.0);
    for (int k = 1; k < N; ++k)
        for (int i = 1; i < N; ++i)
            a[k] += x[i] * sin(i * k * pi / double(N));
    if (inverse)
        for (int k = 1; k < N; ++k)
            a[k] *= 2.0 / double(N);
    return a;
}

double E(
    const vector<double>& x,
    const vector<double>& dxdt,
    const double alpha)
{
    int N = x.size() - 1;
    double E_kin = 0;
    for (int i = 1; i < N; ++i)
        E_kin += dxdt[i] * dxdt[i] / 2.0;
    double E_pot = 0;
    for (int i = 1; i <= N; ++i) {
        double dx = x[i] - x[i-1];
        E_pot += pow(dx, 2.0) / 2.0 + alpha * pow(dx, 3.0) / 3.0;
    }
    return E_kin + E_pot;
}

vector<double> E_mode(
    const vector<double>& x,
    const vector<double>& dxdt)
{
    int N = x.size() - 1;
    vector<double> a = Fourier_sine_transform(x);
    vector<double> dadt = Fourier_sine_transform(dxdt);
    vector<double> E_mode = vector<double>(x.size());
    const double pi = 4 * atan(1.0);
    for (int k = 1; k < N; ++k) {
        double E_kin = 0.5 * pow(dadt[k], 2.0);
        double E_pot = 2 * pow(a[k] * sin(k * pi / (2.0 * N)), 2.0);
        E_mode[k] = E_kin + E_pot;
    }
    return E_mode;
}

void compute_accelerations(
    const vector<double>& x,
    vector<double>& d2xdt2,
    const double alpha)
{
    int N = x.size() - 1;
    for (int i = 1; i < N; ++i) {
        double dx_plus = x[i+1] - x[i], dx_minus = x[i] - x[i-1];
        d2xdt2[i] = dx_plus - dx_minus +
            alpha * (pow(dx_plus, 2.0) - pow(dx_minus, 2.0));
    }
}

void initialize(
    const vector<double>& a,
    vector<double>& x,
    vector<double>& dxdt,
    vector<double>& d2xdt2,
    const double alpha)
{
    int N = x.size() - 1;
    // zero all components
    for (int i = 0; i <= N; ++i)
        x[i] = dxdt[i] = d2xdt2[i] = 0.0;

    // inverse sine transform of mode amplitudes
    bool inverse = true;
    vector<double> dx = Fourier_sine_transform(a, inverse);
    for (int i = 1; i < N; ++i)
        x[i] = dx[i];

    // adjust amplitude
    double x_max = 0;
    for (int i = 1; i < N; ++i) {
        double ax = abs(x[i]);
        if (ax > x_max)
            x_max = ax;
    }
    for (int i = 1; i < N; ++i)
        x[i] /= x_max;

    compute_accelerations(x, d2xdt2, alpha);
}

void velocity_Verlet(
    const double dt,
    vector<double>& x,
    vector<double>& dxdt,
    vector<double>& d2xdt2,
    const double alpha)
{
    int N = x.size() - 1;
    for (int i = 1; i < N; ++i) {
        x[i] += dxdt[i] * dt + 0.5 * d2xdt2[i] * dt * dt;
        dxdt[i] += 0.5 * d2xdt2[i] * dt;
    }
    compute_accelerations(x, d2xdt2, alpha);
    for (int i = 1; i < N; ++i)
        dxdt[i] += 0.5 * d2xdt2[i] * dt;
}

int main()
{
    cout << " Studies of Nonlinear Problems by Fermi, Pasta, Ulam, Tsingou\n"
         << " ------------------------------------------------------------\n";

    int N = 32;
    double alpha = 1.0 / 4.0;
    double delta_t = sqrt(1.0 / 8.0);
    cout << " N = " << N << '\t' << " alpha = " << alpha << '\t'
         << " delta_t = " << delta_t << '\n';

    int computation_steps_per_cycle = 100;
    double dt = delta_t / computation_steps_per_cycle;
    cout << " integration time step dt = " << dt << endl;

    // create vectors for position, velocity, acceleration, mode amplitudes
    vector<double> x = vector<double>(N+1);
    vector<double> dxdt = x, d2xdt2 = x, a = x;

    // initialize with lowest eigenmode of the linear chain
    a[1] = 1;
    initialize(a, x, dxdt, d2xdt2, alpha);

    vector<double> E_a = E_mode(x, dxdt);
    double E_scale = E_a[1] / 300.0;

    ofstream ofs_fig1("fpu1.dat"), ofs_fig8("fpu8.dat");

    for (int i = 0; i <= N; i++)
        ofs_fig8 << i << '\t' << x[i] << '\n';

    int nc = 1000;
    int computation_cycles = 30 * nc;
    for (int cycle = 0; cycle <= computation_cycles; ++cycle) {

        // save total and mode energies every nc cycles
        if (cycle % (nc/10) == 0) {
            double t = cycle / double(nc);
            double energy = E(x, dxdt, alpha);
            E_a = E_mode(x, dxdt);

            cout << " " << t << '\t' << energy;
            ofs_fig1 << t << '\t' << energy;
            for (int k = 1; k <= 5; ++k) {
                cout << '\t' << E_a[k] / E_scale;
                ofs_fig1 << '\t' << E_a[k] / E_scale;
            }
            // sum energies in modes 6 through N
            energy = 0;
            for (int k = 6; k <= N; ++k)
                energy += E_a[k] * E_scale;
            cout << '\t' << energy << '\n';
            ofs_fig1 << '\t' << energy << '\n';
        }

        if (cycle == 1000 || cycle == 10000 || cycle == 12000 ||
            cycle == 14000 || cycle == 19000 || cycle == 22000 ||
            cycle == 28311)
        {
            ofs_fig8 << '\n';
            for (int i = 0; i <= N; i++)
                ofs_fig8 << i << '\t' << x[i] << '\n';
        }

        for (int step = 0; step < computation_steps_per_cycle; ++step)
            velocity_Verlet(dt, x, dxdt, d2xdt2, alpha);
    }

    return 0;
}
