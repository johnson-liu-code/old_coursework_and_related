

### created 7 Feb 2017 ###

### commented 17 Feb 2017 ###
#   - Remeber to change the directory where you want to save the figures.

### modified 25 Feb 2017 ###
#   - Trimmed down the code.
#   - No longer saves every grid. Instead, a plot is made when the code is finished iterating through a single grid. Then, the code repeats.

### modified 28 Feb 2017 ###
#   - Only makes one plot out of every m iterations.

### modified 7 Mar 2017 ###
#   - Added code to plot magnetization versus time.


import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from mpl_toolkits.axes_grid1 import make_axes_locatable


### Parameters for random number generator.
a = 7.**5
m = float(2**31 - 1)
c = 0

q = m/a
r = m % a

x1 = 2.**13.
#x2 = 111.

#r1 = 0.
#d = .75

### Accept/reject method.

def accept_reject(x1, y):
    # Generate random number.
    x1 = a*(x1 % q) - (r*x1)/q

    if x1 < 0:
        x1 += m

    r1 = x1/m

    # If random number is less than y, change the spin.
    if r1 <= y:
        change = True
    else:
        change = False
    #print 'r1 = ', r1, ' y = ', y, change
    return x1, change

### Metropolis method.
def metropolis(x1, x2, r1, cutoff):
    x1 = a*(x1 % q) - (r*x1)/q

    if x1 < 0:
        x1 += m

    s1 = x1/m

    x2 = a*(x2 % q) - (r*x2)/q

    if x2 < 0:
        x2 += m

    s2 = x2/m

    r2 = r1 + d*(2*s1 - 1)

    if r2 > 0 and r2 < cutoff:
        r1 = r2
        change = True
    else:
        change = False

    return x1, x2, r1

### Wrap-around function.
def determine_ij(i, j, x_len, y_len):
    if i == 0:
        i_up = 1
        i_down = x_len - 1
    elif i == x_len - 1:
        i_up = 0
        i_down = i - 1
    else:
        i_up = i + 1
        i_down = i - 1
    if j == 0:
        j_left = y_len - 1
        j_right = 1
    elif j == y_len - 1:
        j_left = j - 1
        j_right = 0
    else:
        j_left = j - 1
        j_right = j + 1

    return i_up, i_down, j_left, j_right

### Function to evaluate E_old and E_new.
def evaluate_E(i, j, i_up, i_down, j_left, j_right, v, x1):
    E_old = -J_ * v[i][j] * (v[i_up][j] + v[i_down][j] + v[i][j_left] + v[i][j_right])
    E_new = E_old * -1.		# E_new has the same magnitude as E_old, but with the oppposite sign in the case of only two available spins.

    if E_new <= E_old:		# If E_new is less than or equal to E_old, change the spin.
        change = True
        #print change
    elif E_new > E_old:		# If E_new is greater than E_old, change the spin only if a generated random number is less than the exponential.
        y = np.exp(-B * (E_new - E_old))
        x1, change = accept_reject(x1, y)
    return x1, change

def energy(i, j, i_up, i_down, j_left, j_right, v,):
    ENERGY = -J_ * v[i][j] * (v[i_up][j] + v[i_down][j] + v[i][j_left] + v[i][j_right])
    return ENERGY

### Graphing parameters.
cmap = colors.ListedColormap(['white', 'black'])
bounds=[-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

mag_vs_beta = []
E_per_spin_vs_beta = []
mag_beta_J = []

### Parameters for the Ising model.
n = 10
v = np.ones((n,n))

#k = 1.38064852E-23                  # m^2 kg s^{-2} K^{-1}		# Boltzmann constant.
#T = 300.                            # K				# Temperature.

#B = (k * T)**-1.							# Beta.

#B = .44
beta = np.arange(0, 1.1, .05)
# beta = [.7]
J = np.arange(.1, 1.1, .1)
# J_ = 1.									# J.

iterations = 10			# Number of iterations.

for J_ in J:
    beta_save = []
    for B in beta:
        ### Initialize grid.
        for i in range(n):			# Iterate throught boxes in grid.
            for j in range(n):
                # Randomly decide whether or not to change the spin of the current box.
                x1, change = accept_reject(x1, .5)

                if change == True:
                    v[i][j] = v[i][j] * -1

        # mag_vs_time = []

        ### Iterate through each box in the grid and decide whether or not to change the spin of each box.
        for iterate in range(iterations):
            for i in range(n):
                for j in range(n):
                    i_up, i_down, j_left, j_right = determine_ij(i, j, n, n)

                    x1, change = evaluate_E(i, j, i_up, i_down, j_left, j_right, v, x1)

                    if change == True:
                        v[i][j] = v[i][j] * -1

            #         m += v[i][j]
            # M = m / n**2
            # mag_vs_time.append((iterate, M))
        mag = 0
        # e = 0
        for i in range(n):
            for j in range(n):
                mag += v[i][j]
                i_up, i_down, j_left, j_right = determine_ij(i, j, n, n)
                # en = energy(i, j, i_up, i_down, j_left, j_right, v)
                # e += en

        M = mag / n**2
        # mag_vs_beta.append((B, M))
        beta_save.append((M))
    mag_beta_J.append(beta_save)

        # E = e / n**2
        # E_per_spin_vs_beta.append((B, E))

    # if iterate%10 == 0:
        # print iterate

    # if iterate%10 == 0:
# plt.figure()
# fig = plt.imshow(v, cmap = cmap,  interpolation='nearest', origin = 'lower')
# plt.colorbar(fig, cmap=cmap, norm=norm, boundaries=bounds, ticks=[-1, 1])
# plt.title(r'$\beta = $' + str(B) + '\n' + r'$J = $' + str(J_))
# plt.show()
	# plt.savefig(directory + str("{0:0=4d}".format(iterate)) + '.png', format = 'png')


# time, mag = zip(*mag_vs_time)
# Beta, mag = zip(*mag_vs_beta)
# Beta, Energy = zip(*E_per_spin_vs_beta)

# print mag_beta_J[0]
plt.figure()
ax = plt.gca()
im = ax.imshow(mag_beta_J, cmap='cool', interpolation='nearest', origin='lower')
ax.set_xticks(np.arange(len(beta)) )
ax.set_yticks(np.arange(len(J)) )
ax.set_xticklabels(['{0:.2f}'.format(b) for b in beta], rotation=45)
ax.set_yticklabels(['{0:.2f}'.format(f) for f in J])
plt.xlabel(r'$\beta$')
plt.ylabel('J', rotation=0)
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="5%", pad=0.05)
cbar = plt.colorbar(im, cax=cax, cmap='cool', label='Magnetization')

plt.show()

# plt.plot(time, mag, color = 'purple', marker = 'o')
# plt.title(r'$\beta$ = ' + str(B) + '\nn = ' + str(n**2), size = 20)
# plt.xlabel('Time (Number of iterations)', size = 20)
# plt.ylabel('Magnetization', size = 20)
# plt.grid()
# plt.xticks(fontsize = 16)
# plt.yticks(fontsize = 16)
# plt.xlim(0, iterations+1)
# plt.show()

# plt.plot(Beta, mag, color = 'purple', marker = 'o')
# plt.title('Time = ' + str(iterations) + '\nn = ' + str(n**2), size = 20)
# plt.xlabel(r'$\beta$', size = 20)
# plt.ylabel('Magnetization', size = 20)
# plt.grid()
# plt.xticks(fontsize = 16)
# plt.yticks(fontsize = 16)
# plt.xlim(0, max(beta))
# plt.show()
#
# plt.plot(Beta, Energy, color = 'purple', marker = 'o')
# plt.title('Time = ' + str(iterations) + '\nn = ' + str(n**2), size = 20)
# plt.xlabel(r'$\beta$', size = 20)
# plt.ylabel('Energy\nper spin', size = 20)
# plt.grid()
# plt.xticks(fontsize = 16)
# plt.yticks(fontsize = 16)
# plt.xlim(0, max(beta))
# plt.show()
