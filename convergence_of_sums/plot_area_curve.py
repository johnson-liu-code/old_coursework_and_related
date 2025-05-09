import numpy as np
import matplotlib.pyplot as plt


def f(x):
    return 1/x**2.

x = np.linspace(10, 15, 200)
y = f(x)

x_val = np.arange(10, 15, 1)

def plt_rectangle(left_corner_x):
    rectangle = plt.Rectangle((left_corner_x, 0), 1, f(left_corner_x + 1), fc = 'purple', alpha = .75)
    plt.gca().add_patch(rectangle)

for i in x_val:
    plt_rectangle(i)

plt.plot(x, y)

plt.xlim(10, 15)
plt.ylim(0, .01)

plt.grid(linestyle = '--')

plt.xlabel(r'$x$', size = 24)
plt.ylabel(r'$f(x)$', size = 24, rotation = 0)

plt.xticks(fontsize = 20)
plt.yticks(fontsize = 20)

plt.show()
