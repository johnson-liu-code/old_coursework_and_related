import math
import random

J = 1.0                     # spin-spin coupling += ferro, -= antiferro
L_x = 10; L_y = 10          # number of spins in x and y
N = 100                     # total number of spins
s = []                      # L_x x L_y array of spin values
T = 2.0                     # Temperature
H = 0.0                     # magnetic field

w = []                      # Boltzmann factors at fixed T and H

def compute_Boltzmann_factors():

    global w
    w = []
    for m in range(5):
        w.append( [] )
        sum_of_neighbors = -4 + 2 * m
        for n in range(2):
            s_i = -1 + 2 * n
            factor = math.exp( -2.0 * (J * sum_of_neighbors + H) * s_i / T )
            w[m].append(factor)

steps = 0                   # Monte Carlo steps so far

def initialize():

    # create spin lattice and set spin randomly up or down (hot start)
    global s, steps
    s = [ ]
    for i in range(L_x):
        s.append( [ ] )
        for j in range(L_y):
            s[i].append(random.choice( (-1, 1) ))
    compute_Boltzmann_factors()
    steps = 0

def Metropolis_step_accepted():

    # choose a random spin
    i = random.randrange(L_x)
    j = random.randrange(L_y)

    # find the sum of neighbors assuming periodic boundary conditions
    sum_of_neighbors = ( s[(i-1)%L_x][j] + s[(i+1)%L_x][j] +
                         s[i][(j-1)%L_y] + s[i][(j+1)%L_y] )

    # access ratio of precomputed Boltzmann factors
    ratio = w[2 + int(sum_of_neighbors/2)][int((1 + s[i][j])/2)]

    # apply the Metropolis test
    if ratio > 1.0 or ratio > random.random():
        s[i][j] = -s[i][j]
        return True
    else:
        return False

acceptance_ratio = 0        # accepted steps / total number of steps

def one_Monte_Carlo_step_per_spin():

    global acceptance_ratio, steps
    accepts = 0
    for n in range(N):
        if Metropolis_step_accepted():
            accepts += 1
    acceptance_ratio = accepts / float(N)
    steps += 1

def magnetization_per_spin():

    s_sum = 0.0
    for i in range(L_x):
        for j in range(L_y):
            s_sum += s[i][j]
    return s_sum / float(N)

def energy_per_spin():

    s_sum = 0.0
    ss_sum = 0.0
    for i in range(L_x):
        for j in range(L_y):
            s_sum += s[i][j]
            ss_sum += s[i][j] * (s[(i+1)%L_x][j] + s[i][(j+1)%L_y])
    return -(J * ss_sum + H * s_sum) / float(N)

print(" Two-dimensional Ising Model - Metropolis simulation")
print(" ---------------------------------------------------")
L = int(input(" Enter number of spins L in each direction: "))
L_x = L
L_y = L
N = L_x * L_y
T = float(input(" Enter temperature T: "))
H = float(input(" Enter magnetic field H: "))
MC_steps = int(input(" Enter number of Monte Carlo steps: "))

initialize()
therm_steps = int(0.2 * MC_steps)
print(" Performing", therm_steps, "thermalization steps ...")
for i in range(therm_steps):
    one_Monte_Carlo_step_per_spin()

print(" Done ... Performing production steps ...")
m_av = 0.0; m2_av = 0.0; e_av = 0.0; e2_av = 0.0
data_file = open("ising.data", "w")
for i in range(MC_steps):
    one_Monte_Carlo_step_per_spin()
    m = magnetization_per_spin()
    e = energy_per_spin()
    m_av += m
    m2_av += m**2
    e_av += e
    e2_av += e**2
    data_file.write(repr(m) + "\t" + repr(e) + "\n")
data_file.close()
print(" M/spin and E/spin values written in ising.data")
m_av /= float(MC_steps)
m2_av /= float(MC_steps)
e_av /= float(MC_steps)
e2_av /= float(MC_steps)
print(" <m> =", m_av, "+/-", math.sqrt(m2_av - m_av**2))
print(" <e> =", e_av, "+/-", math.sqrt(e2_av - e_av**2))
