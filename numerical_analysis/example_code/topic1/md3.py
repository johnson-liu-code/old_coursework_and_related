# md3.py incorporates Verlet's neighbor list algorithm

from math import ceil, sqrt
from random import normalvariate
from sys import stdout

# simulation parameters
N = 864                     # number of particles
rho = 1.0                   # density (number per unit volume)
T = 1.0                     # temperature

# parameters to implement neighbor list algorithm
rCutOff = 2.5               # cut-off on Lennard-Jones potential and force
rMax = 3.3                  # maximum separation to include in pair list
updateInterval = 10         # number of time steps between updates of pair list

def initVerlet():
    # create and initialize global arrays for Verlet's neighbor list algorithm
    global nPairs           # number of pairs currently in pair list
    global pairList         # the list of pair indices (i,j)
    global drPair           # vector separations of each pair (i,j)
    global rSqdPair         # squared separation of each pair (i,j)
    nPairs = ceil(N * (N - 1) / 2)
    pairList = [ [0, 0] for i in range(nPairs) ]
    drPair = [ [0.0] * 3 for i in range(nPairs) ]
    rSqdPair = [ 0.0 for i in range(nPairs) ]

def computeSeparation(i, j, dr, rSqd):
    # find separation using closest image convention
    rSqd[0] = 0.0
    for d in range(3):
        dr[d] = r[i][d] - r[j][d]
        if dr[d] >= 0.5 * L:
            dr[d] -= L
        if dr[d] < -0.5 * L:
            dr[d] += L
        rSqd[0] += dr[d]**2

def updatePairList():
    global nPairs, pairList
    nPairs = 0
    dr = [0.0] * 3
    for i in range(N - 1):                  # all distinct pairs
        for j in range(i + 1, N):           # of particles i,j
            rSqd = [0.0]
            computeSeparation(i, j, dr, rSqd)
            if rSqd[0] < rMax**2:
                pairList[nPairs][0] = i
                pairList[nPairs][1] = j
                nPairs += 1

def updatePairSeparations():
    global rSqdPair, drPair
    dr = [0.0] * 3
    for p in range(nPairs):
        i = pairList[p][0]
        j = pairList[p][1]
        rSqd = [0.0]
        computeSeparation(i, j, dr, rSqd);
        for d in range(3):
            drPair[p][d] = dr[d]
        rSqdPair[p] = rSqd[0]

def computeAccelerations():
    global a
    # set all accelerations to zero
    for i in range(N):
        for k in range(3):
            a[i][k] = 0.0
    for p in range(nPairs):
        i = pairList[p][0]
        j = pairList[p][1]
        if rSqdPair[p] < rCutOff**2:
            f = 48.0 / rSqdPair[p]**7 - 24.0 / rSqdPair[p]**4
            for d in range(3):
                a[i][d] += f * drPair[p][d]
                a[j][d] -= f * drPair[p][d]

def velocityVerlet(dt):
    global r, v
    # assume accelerations have been computed
    for i in range(N):
        for k in range(3):
            r[i][k] += v[i][k] * dt + 0.5 * a[i][k] * dt**2
            # use periodic boundary conditions
            if r[i][k] < 0:
                r[i][k] += L
            if r[i][k] >= L:
                r[i][k] -= L
            v[i][k] += 0.5 * a[i][k] * dt
    updatePairSeparations()
    computeAccelerations()
    for i in range(N):
        for k in range(3):
            v[i][k] += 0.5 * a[i][k] * dt

# functions repeated from md2.py
# initialize, initPositions, initVelocities
# rescaleVelocities, instantaneousTemperature

def initialize():
    global r, v, a          # set values for global variables
    r = [ [0.0] * 3 for i in range(N) ]
    v = [ [0.0] * 3 for i in range(N) ]
    a = [ [0.0] * 3 for i in range(N) ]
    initPositions()
    initVelocities()

def initPositions():
    global L, r, v
    # compute side of cube from number of particles and number density
    L = (N / rho)**(1.0 / 3)
    # find M large enough to fit N atoms on an fcc lattice
    M = 1
    while 4 * M**3 < N:
        M += 1
    a0 = L / M              # lattice constant of conventional cell

    # 4 atomic positions in fcc unit cell
    xCell = [ 0.25, 0.75, 0.75, 0.25 ]
    yCell = [ 0.25, 0.75, 0.25, 0.75 ]
    zCell = [ 0.25, 0.25, 0.75, 0.75 ]

    n = 0                   # atoms placed so far
    for x in range(M):
        for y in range(M):
            for z in range(M):
                for k in range(4):
                    if n < N:
                        r[n][0] = (x + xCell[k]) * a0
                        r[n][1] = (y + yCell[k]) * a0
                        r[n][2] = (z + zCell[k]) * a0
                        n += 1

def initVelocities():
    global v
    # Gaussian with zero mean and unit width
    mu = 0.0
    sigma = 1.0
    for i in range(N):
        for j in range(3):
            v[i][j] = normalvariate(mu, sigma)
    # Adjust velocities so center-of-mass velocity is zero
    vCM = [ 0.0 ] * 3
    for i in range(N):
        for j in range(3):
            vCM[j] += v[i][j]
    for i in range(3):
        vCM[i] /= N
    for i in range(N):
        for j in range(3):
            v[i][j] -= vCM[j]
    # Rescale velocities to get the desired instantaneous temperature
    rescaleVelocities()

def rescaleVelocities():
    global v
    vSqdSum = 0.0
    for i in range(N):
        for j in range(3):
            vSqdSum += v[i][j]**2
    scale = sqrt(3 * (N - 1) * T / vSqdSum)
    for i in range(N):
        for j in range(3):
            v[i][j] *= scale

def instantaneousTemperature():
    vSqdSum = 0.0
    for i in range(N):
        for k in range(3):
            vSqdSum += v[i][k]**2
    return vSqdSum / (3 * (N - 1))

# main script code

initialize()
initVerlet()
updatePairList()
updatePairSeparations()
computeAccelerations()
dt = 0.01
file = open("T3.data", "w")
for i in range(1000):
    velocityVerlet(dt)
    file.write(str(instantaneousTemperature()) + '\n')
    if i % 200 == 0:
        rescaleVelocities()
    if i % updateInterval == 0:
        updatePairList()
        updatePairSeparations()
file.close()
