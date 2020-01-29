import numpy as np
import matplotlib.pyplot as plt


def f(y):
    return np.log(y)**2

actual_int = 2*np.log(2)**2 - 4*np.log(2) + 2
#print actual_int

#N_list = np.arange(10, 1000)

#N_list = [1e1, 1e2, 1e3]
N_list = [1e1, 1e2, 1e3, 1e4, 1e5, 1e6]

rec_left_err = np.zeros(len(N_list))
rec_righ_err = np.zeros(len(N_list))
trap_err = np.zeros(len(N_list))

for d, N in enumerate(N_list):
    delta = 1. / N
    x = np.linspace(1, 2, N)
    #print delta, x
    rec_left_areas = np.zeros(len(x))
    rec_righ_areas = np.zeros(len(x))
    trap_areas = np.zeros(len(x))

    for c, n in enumerate(x):
        f1 = f(n)
        f2 = f(n+delta)

        rec_left = f1 * delta
        rec_left_areas[c] = rec_left
        rec_righ = f2 * delta
        rec_righ_areas[c] = rec_righ

        trap = .5*(f1 + f2)*delta
        trap_areas[c] = trap

    #print np.sum(rec_areas), np.sum(trap_areas)
    rec_left_err[d] = np.abs( np.sum(rec_left_areas) - actual_int ) / actual_int
    rec_righ_err[d] = np.abs( np.sum(rec_righ_areas) - actual_int ) / actual_int
    trap_err[d] = np.abs( np.sum(trap_areas) - actual_int ) / actual_int

#print actual_int

fig, ax = plt.subplots()

plt.plot(N_list, rec_left_err, label = 'Rectangle Rule (Left)')
plt.plot(N_list, rec_righ_err, label = 'Rectangle Rule (Right)')
plt.plot(N_list, trap_err, label = 'Trapezoid Rule')

plt.legend()

plt.grid(linestyle = '--', which = 'both')

plt.xlabel('N', size = 24)
plt.ylabel(r'$\epsilon$', rotation = 0, labelpad = 20, size = 24)

plt.xticks(fontsize = 20)
plt.yticks(fontsize = 20)

plt.legend(prop = {'size': 20})

ax.tick_params(labelright = True, labelsize = 20)

ax.set_xscale('log')
ax.set_yscale('log')

plt.show()
