import math
from tools.quadrature import vegas

def f(x, wgt):
    dx2 = 0
    for d in range(4):
        dx2 += (x[d] - 0.5) ** 2
    return math.exp(-dx2 * 100.) * 1013.2118364296088

regn = [-1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0]
init = 0
ncall = 1000
itmx = 10
nprn = 0
tgral, sd, chi2a = vegas(regn, f, init, ncall, itmx, nprn)
