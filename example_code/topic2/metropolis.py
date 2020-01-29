# estimate Gaussian integral using the Monte Carlo algorithm

from math import exp, pi, sqrt
from random import random

def P(x):
    return exp(- x**2 / 2) / sqrt(2 * pi)

def f_over_w(x):
    return x**2

x = 0.0                         # initial position of walker
delta = 1.0                     # step size

accepts = 0                     # number of steps accepted

def MetropolisStep():
    global x, accepts           # updated the global value
    xTrial = x + (2 * random() - 1) * delta
    w = P(xTrial) / P(x)
    if w >= 1:                  # uphill
        x = xTrial              # accept the step
        accepts += 1
    else:                       # downhill
        if random() < w:        # but not too far
            x = xTrial          # accept the step
            accepts += 1

# get input parameters from user
delta = float(input(" Enter step size  delta: "))
M = int(input(" Enter number of trials: "))
N = int(input(" Enter steps per trial: "))

fSum = 0.0                      # accumulator for <f>
sqdSum = 0.0                    # accumulator for <f> * <f>
errSum = 0.0                    # accumulator error estimates
for i in range(M):
    avg = 0.0                   # accumulator for f(x)
    var = 0.0                   # accumulator for f(x) * f(x)
    for j in range(N):
        MetropolisStep()
        fx = f_over_w(x)
        avg += fx
        var += fx**2
    avg /= N
    var /= N
    var = var - avg**2
    err = sqrt(var / N)
    fSum += avg
    sqdSum += avg**2
    errSum += err
ans = fSum / M
stdDev = sqrt(sqdSum / M - ans**2)
stdDev /= sqrt(float(M))
err = errSum / M
err /= sqrt(float(M))
print("\n Exact  answer: " + str(1.0))
print("      Integral: " + str(ans) + "  +-  " + str(err))
print("     Std. Dev.: " + str(stdDev))
print("  Accept ratio: " + str(accepts / float(N * M)))

# under construction
