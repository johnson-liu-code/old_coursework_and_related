import numpy as np
import matplotlib.pyplot as plt


x = np.linspace(0, 10, 1000)
y = .5*x**2*np.exp(-x)


plt.plot(x, y)
plt.xlabel(r'$x$', size = 24)
plt.ylabel(r'$f(x)$', rotation = 0, size = 24, labelpad = 30)
plt.grid(linestyle = '--')
plt.xticks(size = 20)
plt.yticks(size = 20)
plt.show()
