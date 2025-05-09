# Monte Carlo integration in 1 dimension

from math import pi, sqrt
from random import random
from sys import stdout

a = 0.0
b = 1.0

def f(x):
    return 4.0 / (1.0 + x**2)

N = int(input(" Enter number of integration points N: "))
M = int(input(" Enter number of trials M: "))

I_M = 0.0
sigma_M = 0.0
sigmaAverage = 0.0

stdout.write(" Trial   Integral       MC Error       Actual Error\n" +
             " --------------------------------------------------\n")
for m in range(1, M + 1):
    I = 0.0
    sigma = 0.0
    for n in range(1, N + 1):
        x = a + (b - a) * random()
        fx = f(x)
        I += fx
        sigma += fx**2
    I /= N
    sigma /= N
    sigma -= I**2
    I *= b - a
    sigma = (b - a) * sqrt(sigma / N)
    stdout.write(" " + str(m).ljust(8) + str(I)[:12].ljust(15)
        + str(sigma)[:12].ljust(15) + str(I - pi)[:12] + "\n")
    I_M += I
    sigma_M += I**2
    sigmaAverage += sigma

stdout.write(" --------------------------------------------------\n")
I_M /= M
sigma_M /= M
sigma_M -= I_M**2
sigma_M = sqrt(sigma_M)
sigmaAverage /= M
stdout.write(" Average " + str(I_M)[:12].ljust(15)
    + str(sigmaAverage)[:12].ljust(15) + str(I_M - pi)[:12] + "\n"
    + " Standard Deviation     " + str(sigma_M)[:12] + "\n"
    + " (Std. Dev.)/sqrt(M)    " + str(sigma_M / sqrt(float(M)))[:12] + "\n")
stdout.write(" --------------------------------------------------\n")
