#  Autocorrelation time in the 2-D Ising Model

import math
import random

J = 1.0                     #  ferromagnetic coupling
L_x = L_y = 10              #  number of spins in x and y
N = L_x * L_y               #  number of spins
s = []                      #  the spins
T = 1.0                     #  temperature
H = 0.0                     #  magnetic field

w = []                      #  Boltzmann factors

def compute_Boltzmann_factors():
    global w
    w = []
    for m in range(5):
        w.append([])
        sum_of_neighbors = -4 + 2 * m
        for n in range(2):
            s_i = -1 + 2 * n
            factor = math.exp( -2.0 * (J * sum_of_neighbors + H) * s_i / T )
            w[m].append(factor)

eAv = mAv = 0.0             #  accumulators to compute <e> and <m>
nSave = 10                  #  values to save for autocorrelations
eSave = []; mSave = []      #  saved energy and magnetization values
cee = []; cmm = []          #  energy and magnetization correlation sums
nCorr = 0                   #  number of values accumulated in sums

def initialize_correlations():
    global eAv, mAv, eSave, mSave, cee, cmm, nCorr
    eAv = mAv = 0.0
    eSave.clear()
    mSave.clear()
    cee = [0.0] * (nSave + 1)
    cmm = [0.0] * (nSave + 1)
    nCorr = 0

steps = 0                  #  steps so far

def initialize():
    # create spin lattice and set spin randomly up or down (hot start)
    global s, steps
    s = []
    for i in range(L_x):
        s.append([])
        for j in range(L_y):
            s[i].append(random.choice((-1, 1)))
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

def accumulate_correlations():
    global nCorr, eAv, mAv, cee, cmm, eSave, mSave
    #  calculate current energy and magnetization
    e = energy_per_spin()
    m = magnetization_per_spin()
    #  accumulate averages and correlation products
    if len(eSave) == nSave:     #  if nSave values have been saved
        nCorr += 1
        eAv += e
        mAv += m
        cee[0] += e**2
        cmm[0] += m**2
        for i in range(1, nSave + 1):
            cee[i] += eSave[i - 1] * e
            cmm[i] += mSave[i - 1] * m
        #  discard the oldest values
        eSave.pop()
        mSave.pop()
    #  save the current values
    eSave.insert(0, e)
    mSave.insert(0, m)

tau_e = tau_m = 0.0         #  autocorrelation times

def compute_autocorrelation_times():
    global tau_e, tau_m
    #  energy correlation
    av = eAv / nCorr
    c0 = cee[0] / nCorr - av**2
    tau_e = 0.0
    for i in range(nSave + 1):
        tau_e += (cee[i] / nCorr - av**2) / c0
    #  magnetization correlation
    av = mAv / nCorr
    c0 = cmm[0] / nCorr - av**2
    tau_m = 0.0
    for i in range(nSave + 1):
        tau_m += (cmm[i] / nCorr - av**2) / c0

print(" Two-dimensional Ising Model - Autocorrelation times")
print(" ---------------------------------------------------")
L_x = L_y = int(input(" Enter number of spins L in each direction: "))
N = L_x * L_y
T1 = float(input(" Enter starting temperature: "))
T2 = float(input(" Enter ending temperature: "))
TSteps = int(input(" Enter number of temperature steps: "))
MCSteps = int(input(" Enter number of Monte Carlo steps: "))

initialize()
file = open("auto.data", "w")
thermSteps = int(0.2 * MCSteps)
for i in range(TSteps + 1):
    T = T1 + i * (T2 - T1) / float(TSteps)
    compute_Boltzmann_factors()
    for step in range(thermSteps):
        one_Monte_Carlo_step_per_spin()
    initialize_correlations()
    for step in range(MCSteps):
        one_Monte_Carlo_step_per_spin()
        accumulate_correlations()
    compute_autocorrelation_times()
    print(" T = ", str(T), "\ttau_e = ", str(tau_e), "\ttau_m = ", str(tau_m))
    file.write(str(T) + '\t' + str(tau_e) + '\t' + str(tau_m) + '\n')
file.close()
