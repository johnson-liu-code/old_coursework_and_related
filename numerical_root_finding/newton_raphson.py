import numpy as np
import matplotlib.pyplot as plt


def f(x):
    return np.tanh(x - 5.)

def df(x):
    return 1. - np.tanh(x - 5.)**2.

x = 4

x_values = []

prev_fm = 0

found_root = False
while not found_root:
#for i in range(10):
    print('{0:.16f}'.format(x) )
    x_values.append(x)
    fx = f(x)
    dfx = df(x)

    x = x - fx/dfx
    fm = f(x)

    if np.abs(fm - prev_fm) < 1e-5:
        found_root = True
    prev_fm = fm

