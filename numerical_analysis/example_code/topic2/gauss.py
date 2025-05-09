# estimate Gaussian integral using uniform and importance sampling

from math import pi, sqrt
from random import random, normalvariate

double f_over_w(x):
    return x**2

# get input parameters from user
N = int(input(" Enter number of points N: "))
L = float(input(" Enter cut-off L for uniform sampling: "))

# uniform sampling
avg = 0.0
var = 0.0
for i in range(N):
    x = (2 * random() - 1) * L;
    fx = f(x)
    avg += fx
    var += fx**2

avg /= N
var /= N
var = var - avg**2
print()
print("   Uniform sampling: " + str(2 * L * avg) + "  +-  "
    + str(2 * L * sqrt(var / N)))

# importance sampling
avg = var = 0.0
for i in range(N):
    x = normalvariate();
    fx = f_over_w(x)
    avg += fx
    var += fx**2

avg /= N
var /= N
var = var - avg**2
print("Importance sampling: " + str(avg) + "  +-  " + str(sqrt(var / N)))
print("       Exact answer: " + str(1.0))
