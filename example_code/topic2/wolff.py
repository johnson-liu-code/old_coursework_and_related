# Wolff cluster algorithm for the 2-D Ising Model

import math
import random

def initialize_spin_lattice(s, L_x, L_y, start="hot"):
    """ set spin matrix s to L_x x L_y array
        set spins randomly "hot", or all up "cold"
    """
    s.clear()
    for x in range(L_x):
        s.append([])
        for y in range(L_y):
            if start == "hot":
                s[x].append(random.choice((-1, 1)))
            else:
                s[x].append(1)

def initialize_cluster_variables(cluster, L_x, L_y):
    """ cluster[i][j] = True is spin i,j belongs to Wolff cluster
        add_probability = 1 - e^(-2J/kT)
    """
    cluster.clear()
    for x in range(L_x):
        cluster.append([])
        for y in range(L_y):
            cluster[x].append(False)

#  Pair of mutually recursive functions implement Wolff's algorithm

def grow_cluster(i, j):
    global s, cluster, cluster_spin, add_probability

    #  mark spin i,j as belonging to the cluster and flip it
    cluster[i][j] = True
    s[i][j] = -s[i][j]

    #  if any of the 4 neighboring spins does not belong to the cluster
    #  try to add it to the cluster.  Use periodic boundary conditions
    i_prev = (i - 1) % L_x
    if not cluster[i_prev][j]:
        try_add(i_prev, j)
    i_next = (i + 1) % L_x
    if not cluster[i_next][j]:
        try_add(i_next, j)
    j_prev = (j - 1) % L_y
    if not cluster[i][j_prev]:
        try_add(i, j_prev)
    j_next = (j + 1) % L_y
    if not cluster[i][j_next]:
        try_add(i, j_next)

def try_add(i, j):
    global s, cluster, cluster_spin, add_probability

    if s[i][j] == cluster_spin:
        if random.random() < add_probability:
            grow_cluster(i, j)

def one_Monte_Carlo_step():
    global cluster, cluster_spin
    #  no cluster has been identified so clear the cluster array
    for i in range(len(cluster)):
        for j in range(len(cluster[0])):
            cluster[i][j] = False
    #  choose a random spin and grow a cluster
    i = random.randrange(len(cluster))
    j = random.randrange(len(cluster[0]))
    cluster_spin = s[i][j]
    grow_cluster(i, j)

def initialize_observables():
    # variables to measure susceptibility per spin and its error estimate
    global n_chi, chi_sum, chi_sqd_sum
    n_chi = 0
    chi_sum = chi_sqd_sum = 0.0

    # variables to measure autocorrelation time
    global n_save, c_chi_sum, chi_save, c_chi, n_corr
    n_save = 10                     # number of values to save
    c_chi_sum = 0.0                 # accumulator
    chi_save = []                   # list of saved values
    c_chi = [0.0] * (n_save + 1)    # correlation sums
    n_corr = 0                      # number of values accumulated

    # variables to estimate fluctuation by blocking
    global step_in_block, chi_block, chi_block_sum, chi_block_sqd_sum
    step_in_block = 0               # steps taken in current block
    chi_block = chi_block_sum = chi_block_sqd_sum = 0.0

def measure_observables():
    # observables are derived from the magnetic moment
    M = 0.0
    for i in range(L_x):
        for j in range(L_y):
            M += s[i][j]
    chi = M**2 / N

    # accumulate chi values
    global chi_sum, chi_sqd_sum, n_chi
    chi_sum += chi
    chi_sqd_sum += chi**2
    n_chi += 1

    # accumulate correlation values
    global n_corr, c_chi, c_chi_sum, chi_save
    if len(chi_save) == n_save:
        c_chi_sum += chi
        c_chi[0] += chi**2
        n_corr += 1
        for i in range(1, n_save + 1):
            c_chi[i] += chi_save[i - 1] * chi
        chi_save.pop()              # discard oldest saved value
    chi_save.insert(0, chi)         # save the current chi value

    # accumulate block values
    global step_in_block, chi_block, chi_block_sum, chi_block_sqd_sum
    chi_block += chi
    step_in_block += 1
    if step_in_block == steps_per_block:
        chi_block /= steps_per_block
        chi_block_sum += chi_block
        chi_block_sqd_sum += chi_block**2
        step_in_block = 0
        chi_block = 0.0

def compute_averages():
    global chi_ave, chi_error, tau_chi, chi_std_dev, tau_effective

    # average susceptibility per spin
    chi_ave = chi_sum / n_chi

    # Monte Carlo error estimate
    chi_error = chi_sqd_sum / n_chi
    chi_error = math.sqrt(chi_error - chi_ave**2)
    chi_error /= math.sqrt(float(n_chi))

    # exponential correlation time
    tau_chi = 0.0
    c_ave = c_chi_sum / n_corr
    c0 = c_chi[0] / n_corr - c_ave**2
    for i in range(1, n_save + 1):
        c = (c_chi[i] / n_corr - c_ave**2) / c0
        if c > 0.01:
            tau_chi += -i / math.log(c)
        else:
            tau_chi /= (i - 1)
            break
        if i == n_save:
            tau_chi /= n_save

    # standard deviation from blocking
    chi_block_ave = chi_block_sum / blocks
    chi_std_dev = chi_block_sqd_sum / blocks
    chi_std_dev = math.sqrt(chi_std_dev - chi_block_ave**2)
    chi_std_dev /= math.sqrt(float(blocks))

    # effective autocorrelation time
    tau_effective = chi_std_dev / chi_error
    tau_effective *= tau_effective / 2

print(" Two-dimensional Ising Model - Wolff Cluster Algorithm")
print(" -----------------------------------------------------")
L_x = int(input(" Enter number of spins L in each direction: "))
L_y = L_x
N = L_x * L_y

J = 1.0                 # coupling constant
T = float(input(" Enter temperature T: "))
add_probability = 1 - math.exp(- 2.0 * J / T)

s = [[]]                # lattice of N spins
initialize_spin_lattice(s, L_x, L_y)
cluster = [[]]          # boolean lattice of Wolff cluster spin membership
initialize_cluster_variables(cluster, L_x, L_y)

MC_steps = int(input(" Enter number of Monte Carlo steps: "))
steps_per_block = 1000  # value suggested in Wolff article
blocks = math.ceil(MC_steps / steps_per_block)
if blocks < 5:
    blocks = 5
    steps_per_block = math.ceil(MC_steps / blocks)
MC_steps = steps_per_block * blocks

therm_steps = round(0.2 * MC_steps)
print(" Performing", therm_steps, "thermalization steps")
for step in range(therm_steps):
    one_Monte_Carlo_step()

print( " Performing", MC_steps, "production steps in", blocks, "blocks")
initialize_observables()
for step in range(MC_steps):
    one_Monte_Carlo_step()
    measure_observables()

compute_averages()
print("")
print("       Average chi per spin = ", chi_ave)
print(" Monte Carlo error estimate = ", chi_error)
print("   Autocorrelation time tau = ", tau_chi)
print("   Std. Dev. using blocking = ", chi_std_dev)
print("              Effective tau = ", tau_effective)
