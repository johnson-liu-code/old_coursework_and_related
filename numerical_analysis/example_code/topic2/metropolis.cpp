// estimate Gaussian integral using the Monte Carlo algorithm

#include <cmath>
#include <cstdlib>
#include <iostream>
using namespace std;

const double pi = 4 * atan(1.0);

inline double std_rand()
{
    return rand() / (RAND_MAX + 1.0);
}

double P(double x) {
    return exp(- x * x / 2) / sqrt(2 * pi);
}

double f_over_w(double x) {
    return x * x;
}

double x = 0;             // initial position of walker
double delta = 1.0;       // step size

int accepts = 0;          // number of steps accepted

void MetropolisStep() {
    double xTrial = x + (2 * std_rand() - 1) * delta;
    double w = P(xTrial) / P(x);
    if (w >= 1) {                  // uphill
        x = xTrial;                // accept the step
        ++accepts;
    } else {                       // downhill
        if (std_rand() < w) {      // but not too far
            x = xTrial;            // accept the step
            ++accepts;
        }
    }
}

int main() {

    // get input parameters from user
    cout << "Enter step size  delta: ";
    cin >> delta;
    cout << "Enter number of trials: ";
    int M;
    cin >> M;
    cout << "Enter steps per  trial: ";
    int N;
    cin >> N;

    double sum = 0;        // accumulator for <f>
    double sqdSum = 0;     // accumulator for <f> * <f>
    double errSum = 0;     // accumulator error estimates
    for (int i = 0; i < M; i++) {
        double avg = 0;        // accumulator for f(x)
        double var = 0;        // accumulator for f(x) * f(x)
        for (int j = 0; j < N; j++) {
            MetropolisStep();
            double fx = f_over_w(x);
            avg += fx;
            var += fx * fx;
        }
        avg /= N;
        var /= N;
        var = var - avg * avg;
        double err = sqrt(var / N);
        sum += avg;
        sqdSum += avg * avg;
        errSum += err;
    }
    double ans = sum / M;
    double stdDev = sqrt(sqdSum / M - ans * ans);
    stdDev /= sqrt(double(M));
    double err = errSum / M;
    err /= sqrt(double(M));
    cout << "\n Exact  answer: " << 1.0 << endl;
    cout << "      Integral: " << ans << "  +-  " << err << endl;
    cout << "     Std. Dev.: " << stdDev << endl;
    cout << "  Accept ratio: " << accepts / double(N * M) << endl;
}
