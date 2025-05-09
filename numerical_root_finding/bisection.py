import numpy as np
import matplotlib.pyplot as plt



def f(x):
    return np.tanh(x - 5)

left = -20
right = 30

init = False
while not init:
    x1 = np.random.uniform(left, right)
    x2 = np.random.uniform(left, right)
    f1 = f(x1)
    f2 = f(x2)
    if f1/f2 < 0:
        init = True

x1_values = []
x2_values = []

prev_fm = 0

found_root = False
while not found_root:
#for i in range(10):
    print('{0:.16f} {1:.16f}'.format(x1, x2) )
    x1_values.append(x1)
    x2_values.append(x2)
    f1 = f(x1)
    f2 = f(x2)
    xm = .5*(x1 + x2)
    fm = f(xm)
    if np.abs(fm - prev_fm) < 1e-5:
        found_root = True
    if fm/f1 < 0:
        x2 = xm
    else:
        x1 = xm
    prev_fm = fm

plt.plot(x1_values, label = r'$x_1$ values')
plt.plot(x2_values, label = r'$x_2$ values')
plt.axhline(y = 5, color = 'red')
plt.grid(linestyle = '--')
plt.legend(prop = {'size':20})
plt.xlabel('Iteration', size = 24)
plt.ylabel('x', rotation = 0, size = 24, labelpad = 20)
plt.xticks(size = 20)
plt.yticks(size = 20)
plt.show()

'''
x = np.linspace(left, right, 1000)
y = f(x)

plt.plot(x, y, label = r'tanh($x-5$)')
plt.axhline(y = 0, color = 'red')
plt.grid(linestyle = '--')
plt.legend(prop = {'size':20})
plt.xlabel('x', size = 24)
plt.ylabel('y', rotation = 0, size = 24)
plt.xticks(size = 20)
plt.yticks(size = 20)
plt.show()
'''
