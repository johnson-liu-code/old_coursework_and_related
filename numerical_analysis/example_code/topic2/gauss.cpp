// estimate Gaussian integral using uniform and importance sampling

#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

const double pi = 4 * atan(1.0);

#include "../tools/random.hpp"

double f(double x)
{
    return x * x * exp(- x * x / 2) / sqrt(2 * pi);
}

double f_over_w(double x)
{
    return x * x;
}

int main() {

    // get input parameters from user
    cout << "Enter number of points N: ";
    int N;
    cin >> N;
    cout << "Enter cut-off L for uniform sampling: ";
    double L;
    cin >> L;

    // uniform sampling
    double avg = 0;
    double var = 0;
    for (int i = 0; i < N; i++) {
        double x = (2 * uniform_dist() - 1) * L;
        double fx = f(x);
        avg += fx;
        var += fx * fx;
    }
    avg /= N;
    var /= N;
    var = var - avg * avg;
    cout << "\n   Uniform sampling: " << 2 * L * avg << "  +-  "
         << 2 * L * sqrt(var / N) << endl;

    // importance sampling
    avg = var = 0;
    for (int i = 0; i < N; i++) {
        double x = normal_dist();
        double fx = f_over_w(x);
        avg += fx;
        var += fx * fx;
    }
    avg /= N;
    var /= N;
    var = var - avg * avg;
    cout << "Importance sampling: " << avg << "  +-  "
         << sqrt(var / N) << endl;

    cout << "       Exact answer: " << 1.0 << endl;
}
