
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt


def fit_func(x, a, b, c):
    return float(a) + float(b)*(x - float(c))**2.

x = np.linspace(0, 10)

a = 1.
b = 2.
c = 3.

y = a + b*(x - c)**2.

popt, pconv = curve_fit(fit_func, x, y, maxfev = 100000)
a, b, c = popt
y_fit = a + b*(x - c)**2.

plt.plot(x, y)
plt.plot(x, y_fit, '--')
plt.plot
plt.show()
