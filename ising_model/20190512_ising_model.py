

import os
import sys
import argparse
import numpy as np
import time
import pickle
import matplotlib.pyplot as plt
from matplotlib import colors
from mpl_toolkits.axes_grid1 import make_axes_locatable


parser = argparse.ArgumentParser()
parser.add_argument('-r', '--run_type', type=str, choices=['single', 'beta_sweep', 'jh_sweep'], default='single', help='Type of simulation run. single, beta_sweep, or jh_sweep.')
parser.add_argument('-b', '--beta', type=float, default=.5, help='beta value for single run.')
parser.add_argument('-bs', '--beta_start', type=float, default=0, help='Starting beta value for beta sweep.')
parser.add_argument('-be', '--beta_end', type=float, default=1, help='Ending beta value for beta sweep.')
parser.add_argument('-bi', '--beta_interval', type=float, default=.1, help='beta interval for beta sweep.')
parser.add_argument('-w', '--warms', type=int, default=10, help='Number of iterations to warm up for beta sweep.')
parser.add_argument('-J', '--J_value', type=float, default=1.0, help='J value.')
parser.add_argument('-H', '--H_value', type=float, default=0.0, help='H value for external magnetic field.')
parser.add_argument('-t', '--number_of_iterations', type=int, default=10, help='Number of iterations to run.')
parser.add_argument('-n', '--dimension_size', type=int, default=10, help='Dimension size of the lattice.')
parser.add_argument('-a', '--start', type=str, choices=['cold', 'hot'], default='hot', help='Start with a cold or a hot configuration.')
parser.add_argument('-o', '--output_directory', type=str, default = 'test/', help='Directory to store the output.')
parser.add_argument('-m', '--save_mag', action='store_false', help='Save the average magnetization at each time step.')
parser.add_argument('-e', '--save_energy', action='store_true', help='Save the energy at each time step.')
parser.add_argument('-s', '--save_configurations', action='store_true', help='Save every configuration.')
parser.add_argument('-l', '--save_last', action='store_true', help='Save the last lattice configuration.')

args = parser.parse_args()
run_type = args.run_type
beta = args.beta
beta_start = args.beta_start
beta_end = args.beta_end
beta_interval = args.beta_interval
warms = args.warms
J = args.J_value
H = args.H_value
number_of_iterations = args.number_of_iterations
dimension_size = args.dimension_size
start = args.start
output_directory = args.output_directory + '/'
save_mag = args.save_mag
save_energy = args.save_energy
save_configurations = args.save_configurations
save_last = args.save_last



k = 1.38064852E-23

### Parameters for random number generator.
a = 7.**5
m = float(2**31 - 1)
c = 0

q = m/a
r = m % a

x1 = 5.5**13.
# x1 = 5.**12.
# x1 = 4.**11.
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

    return x1, x2, r1, change

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

def compute_energy_at_site(i, j, i_up, i_down, j_left, j_right, lattice, J, H):
    energy = -J * lattice[i][j] * (lattice[i_up][j] + lattice[i_down][j] + lattice[i][j_left] + lattice[i][j_right]) - H*lattice[i, j]
    return energy

def evaluate_accept_reject(i, j, i_up, i_down, j_left, j_right, lattice, J, x1, beta, H):
    #E_old = -J * lattice[i][j] * (lattice[i_up][j] + lattice[i_down][j] + lattice[i][j_left] + lattice[i][j_right]) - H*lattice[i][j]
    E_old = compute_energy_at_site(i, j, i_up, i_down, j_left, j_right, lattice, J, H)
    E_new = E_old * -1.		# E_new has the same magnitude as E_old, but with the oppposite sign in the case of only two available spins.

    if E_new <= E_old:		# If E_new is less than or equal to E_old, change the spin.
        change = True
        #print change
    elif E_new > E_old:		# If E_new is greater than E_old, change the spin only if a generated random number is less than the exponential.
        y = np.exp(-beta * (E_new - E_old))
        x1, change = accept_reject(x1, y)
        # x1, x2, r1, change = metropolis(x1, x1, x2, r1, cutoff)
    return x1, change

def initialize_lattice(dimension_size, start, x1):
    lattice = np.ones((dimension_size, dimension_size))
    if start == 'hot':
        for i in range(dimension_size):
            for j in range(dimension_size):
                x1, change = accept_reject(x1, .5)
                if change == True:
                   lattice[i][j] = lattice[i][j] * -1

    return lattice

def run_trajectory_single(dimension_size, number_of_iterations, lattice, x1, save_configurations):
    #print('hello')
    if save_mag == True:
        mag_vs_time = []
    if save_energy == True:
        energy_vs_time = []

    if save_configurations == True:
        save_dir_name = output_directory + time.strftime('%Y_%m_%d_%H_%M_%S') + '/'
        print(save_dir_name)

    for iterate in range(number_of_iterations):
        #print(iterate)
        for i in range(dimension_size):
            for j in range(dimension_size):
                i_up, i_down, j_left, j_right = determine_ij(i, j, dimension_size, dimension_size)
                x1, change = evaluate_accept_reject(i, j, i_up, i_down, j_left, j_right, lattice, J, x1, beta, H)
                if change == True:
                    lattice[i][j] = lattice[i][j] * -1
        if save_mag == True:
            overall_magnetization = 0
        if save_energy == True:
            total_energy = 0
        #print('hello2')
        if save_mag == True or save_energy == True:
            for i in range(dimension_size):
                for j in range(dimension_size):
                    i_up, i_down, j_left, j_right = determine_ij(i, j, dimension_size, dimension_size)
                    if save_mag == True:
                        overall_magnetization += lattice[i][j]
                    if save_energy == True:
                        total_energy += compute_energy_at_site(i, j, i_up, i_down, j_left, j_right, lattice, J, H)
            if save_mag == True:
                overall_magnetization /= dimension_size**2
                mag_vs_time.append(overall_magnetization)
            if save_energy == True:
                energy_vs_time.append(total_energy)
        #print('hello3')
        if save_configurations == True:
            #print('save configs')
            if not os.path.isdir(save_dir_name):
                os.makedirs(save_dir_name)
            file_name = save_dir_name + 'save_configurations_{0:05d}.pkl'.format(iterate)
            #print(file_name)
            with open(file_name, 'wb') as fil:
                pickle.dump(lattice, fil)

    data = [lattice]

    if save_mag == True:
        data.append(mag_vs_time)
    if save_energy == True:
        data.append(energy_vs_time)

    return data

def run_trajectory_beta_sweep(dimension_size, number_of_iterations, x1):

    beta_list = np.arange(beta_start, beta_end, beta_interval)

    chi_vs_beta = []
    C_vs_beta = []
    mag_vs_beta = []

    mag_list_energy_list_vs_beta = []

    for beta in beta_list:
        lattice = initialize_lattice(dimension_size, start, x1)

        for iterate in range(warms):
            for i in range(dimension_size):
                for j in range(dimension_size):
                    i_up, i_down, j_left, j_right = determine_ij(i, j, dimension_size, dimension_size)
                    x1, change = evaluate_accept_reject(i, j, i_up, i_down, j_left, j_right, lattice, J, x1, beta, H)
                    if change == True:
                        lattice[i][j] = lattice[i][j] * -1

        mag_list = []
        mag_squared_list = []
        energy_list = []
        energy_squared_list = []

        if save_configurations == True:
            beta_save_dir_name = 'data/beta_' + str(beta) + '/'
            if not os.path.isdir(beta_save_dir_name):
                os.makedirs(beta_save_dir_name)

        for iterate in range(number_of_iterations):
            for i in range(dimension_size):
                for j in range(dimension_size):
                    i_up, i_down, j_left, j_right = determine_ij(i, j, dimension_size, dimension_size)
                    x1, change = evaluate_accept_reject(i, j, i_up, i_down, j_left, j_right, lattice, J, x1, beta, H)
                    if change == True:
                        lattice[i][j] = lattice[i][j] * -1

            if save_configurations == True:
                save_file_name = beta_save_dir_name + 'beta_' + str(beta) + '_itr_' + str(iterate)
                with open(save_file_name, 'wb') as fil:
                    pickle.dump(lattice, fil)

            mag = 0
            energy = 0

            for i in range(dimension_size):
                for j in range(dimension_size):
                    i_up, i_down, j_left, j_right = determine_ij(i, j, dimension_size, dimension_size)

                    mag += lattice[i][j]
                    energy += compute_energy_at_site(i, j, i_up, i_down, j_left, j_right, lattice, J, H)

            # take absolute value of mag

            mag = np.abs(mag) / dimension_size**2.
            mag_squared = mag**2.

            energy_squared = energy**2.

            mag_list.append(mag)
            mag_squared_list.append(mag_squared)
            energy_list.append(energy)
            energy_squared_list.append(energy_squared)

        chi = beta * ( np.mean(mag_squared_list) - np.mean(mag_list)**2. )
        C = beta**2. * ( np.mean(energy_squared_list) - np.mean(energy_list)**2. )

        mag_list_energy_list_vs_beta.append( (beta, mag_squared_list, mag_list, energy_squared_list, energy_list) )

        mag_vs_beta.append( (beta, mag) )
        chi_vs_beta.append( (beta, chi) )
        C_vs_beta.append( (beta, C) )

    data = [chi_vs_beta, C_vs_beta, mag_vs_beta]

    # with open('save_chi_C_vs_beta.txt', 'wb') as fil:
        # pickle.dump(data, fil)

    return data, mag_list_energy_list_vs_beta


if run_type == 'single':
    lattice = initialize_lattice(dimension_size, start, x1)
    data = run_trajectory_single(dimension_size, number_of_iterations, lattice, x1, save_configurations)

elif run_type == 'beta_sweep':
    data, mag_list_energy_list_vs_beta = run_trajectory_beta_sweep(dimension_size, number_of_iterations, x1)

    if not os.path.isdir(output_directory):
        os.makedirs(output_directory)

    file_name = 'mag_list_energy_list_vs_beta.pkl'
    with open(output_directory + '/' + file_name, 'wb') as outfile:
        pickle.dump(mag_list_energy_list_vs_beta, outfile)

    # chi_vs_beta = data[0]
    # C_vs_beta = data[1]
    # mag_vs_beta  = data[2]

    # plt.plot(beta_1, chi)
    # plt.xlabel(r'$\beta$')
    # plt.ylabel(r'$\chi$', rotation = 0)
    # plt.grid()
    # plt.legend()
    # plt.show()
    #
    # plt.plot(beta_2, C)
    # plt.xlabel(r'$\beta$')
    # plt.ylabel('C', rotation = 0)
    # plt.grid()
    # plt.legend()
    # plt.show()


# cold_lattice = initialize_lattice(dimension_size, 'cold', x1)
# cold_lattice, cold_mag_vs_time, cold_e_vs_time = run_trajectory(dimension_size, number_of_iterations, cold_lattice, x1)
# hot_lattice = initialize_lattice(dimension_size, 'hot', x1)
# hot_lattice, hot_mag_vs_time, hot_e_vs_time = run_trajectory(dimension_size, number_of_iterations, hot_lattice, x1)


# plt.plot(cold_mag_vs_time, label='Avg spin versus time (cold start).')
# plt.plot(hot_mag_vs_time, label='Avg spin versus time (hot start).')
# plt.grid()
# plt.legend()
# plt.title('100x100\n' + r'$\beta = .7$, $J = 1$')
# plt.show()
#
# plt.plot(cold_e_vs_time, label=r'Energy versus time (cold start).')
# plt.plot(hot_e_vs_time, label=r'Energy versus time (hot start).')
# plt.grid()
# plt.legend()
# plt.title('100x100\n' + r'$\beta = .7$, $J = 1$')
# plt.show()

'''
    # if iterate%10 == 0:
        save_dir = 'save_lattice_dir_' + num + '/'
        save_J_dir = save_dir + 'J_{0:.2f}'.format(J_) + '/'
        if not os.path.isdir(save_J_dir):
            os.makedirs(save_J_dir)
        save_name = save_J_dir + 'J_{0:.2f}_H_{1:.2f}.pickle'.format(J_, H_)
        with open(save_name, 'wb') as out:
            pickle.dump(lattice, out)
    #mag_J_beta.append(beta_save)
'''

# if run_type == 'single':
    # cmap = colors.ListedColormap(['white', 'black'])
    # bounds=[-1, 0, 1]
    # norm = colors.BoundaryNorm(bounds, cmap.N)
    #
    # plt.figure()
    # fig = plt.imshow(lattice, cmap = cmap,  interpolation='nearest', origin = 'lower')
    # plt.colorbar(fig, cmap=cmap, norm=norm, boundaries=bounds, ticks=[-1, 1])
    # plt.title(r'$\beta = $' + str(beta) + '\n' + r'$J = $' + str(J))
    # plt.show()
	# plt.savefig(directory + str("{0:0=4d}".format(iterate)) + '.png', format = 'png')


# time, mag = zip(*mag_vs_time)
# Beta, mag = zip(*mag_vs_beta)
# Beta, Energy = zip(*E_per_spin_vs_beta)

# print mag_beta_J[0]
'''
plt.figure()
ax = plt.gca()
im = ax.imshow(M_J_H, cmap='cool', interpolation='nearest', origin='lower')
ax.set_xticks(np.arange(len(H)) )
ax.set_yticks(np.arange(len(J)) )
ax.set_xticklabels(['{0:.2f}'.format(b) for b in H], rotation=45)
ax.set_yticklabels(['{0:.2f}'.format(f) for f in J])
plt.xlabel(r'H')
plt.ylabel('J', rotation=0)
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="5%", pad=0.05)
cbar = plt.colorbar(im, cax=cax, cmap='cool', label='Magnetization')

plt.show()
'''
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
