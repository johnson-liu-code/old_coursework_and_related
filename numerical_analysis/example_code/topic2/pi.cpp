// Monte Carlo integration in 1 dimension

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

#include "../tools/random.hpp"  // for Mersenne Twister generator

const double pi = 4*atan(1.0);
double a = 0, b = 1;
double f (double x) {
    return 4/(1+x*x);
}

int main ( ) {
    cout << "Enter number of integration points N: ";
    int N;
    cin >> N;
    cout << "Enter number of trials M: ";
    int M;
    cin >> M;
    double I_M = 0, sigma_M = 0, sigmaAverage = 0;
    cout << " Trial   " << "Integral       "
         << "MC Error       " << "Actual Error" << "\n ";
    for (int i = 0; i < 50; i++) cout << '-'; cout << endl;
    for (int m = 1; m <= M; m++) {
        double I = 0, sigma = 0;
        for (int n = 1; n <= N; n++) {
            double x = a + (b-a)*uniform_dist();
            double fx = f(x);
            I += fx;
            sigma += fx*fx;
        }
        I /= N;
        sigma /= N;
        sigma -= I*I;
        I *= b-a;
        sigma = (b-a)*sqrt(sigma/N);
        cout.setf(ios::left);
        cout << ' ' << setw(8) << m << setw(15) << I
             << setw(15) << sigma << I-pi << endl;
        I_M += I;
        sigma_M += I*I;
        sigmaAverage += sigma;
    }
    cout << " ";
    for (int i = 0; i < 50; i++) cout << '-'; cout << endl;
    I_M /= M;
    sigma_M /= M;
    sigma_M -= I_M*I_M;
    sigma_M = sqrt(sigma_M);
    sigmaAverage /= M;
    cout << " Average " << setw(15) << I_M << setw(15) << sigmaAverage
         << setw(15) << I_M-pi << '\n'
         << " Standard Deviation     " << sigma_M << '\n'
         << " (Std. Dev.)/sqrt(M)    " << sigma_M/sqrt(double(M)) << "\n ";
    for (int i = 0; i < 50; i++) cout << '-'; cout << endl;
}
