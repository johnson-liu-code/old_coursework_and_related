from math import ceil
from random import random

N = 64                              # number of particles
r = [ [0.0] * 3 for i in range(N) ] # positions
v = [ [0.0] * 3 for i in range(N) ] # velocities
a = [ [0.0] * 3 for i in range(N) ] # accelerations

L = 10.0                            # linear size of cubical volume
vMax = 0.1                          # maximum initial velocity component

def initialize():
    global r, v                     # set global variables
    # initialize positions
    r0 = N**(1.0 / 3)               # interparticle spacing
    M = ceil(r0)                    # number of atoms in each direction
    a0 = L / M                      # lattice spacing
    p = 0                           # particles placed so far
    for x in range(M):
        for y in range(M):
            for z in range(M):
                    if p < N:
                        r[p][0] = (x + 0.5) * a0
                        r[p][1] = (y + 0.5) * a0
                        r[p][2] = (z + 0.5) * a0
                    p += 1
    # initialize velocities
    for p in range(N):
        for i in range(3):
            v[p][i] = vMax * (2 * random() - 1)

def computeAccelerations():
    global a                        # modify global variables
    # set all accelerations to zero
    for i in range(N):
        for k in range(3):
            a[i][k] = 0.0
    for i in range(N - 1):          # loop over all distinct pairs i,j
        for j in range(i + 1, N):
            rij = [0.0] * 3         # position of i relative to j
            rSqd = 0.0
            for k in range(3):
                rij[k] = r[i][k] - r[j][k]
                rSqd += rij[k] * rij[k]
            f = 48.0 / rSqd**7 - 24.0 / rSqd**4
            for k in range(3):
                 a[i][k] += rij[k] * f
                 a[j][k] -= rij[k] * f

def velocityVerlet(dt):
    global r, v                     # modify global variables
    computeAccelerations()
    for i in range(N):
        for k in range(3):
            r[i][k] += v[i][k] * dt + 0.5 * a[i][k] * dt**2
            v[i][k] += 0.5 * a[i][k] * dt
    computeAccelerations()
    for i in range(N):
        for k in range(3):
            v[i][k] += 0.5 * a[i][k] * dt

def instantaneousTemperature():
    vSqdSum = 0.0
    for i in range(N):
        for k in range(3):
            vSqdSum += v[i][k]**2
    return vSqdSum / (3 * (N - 1))

initialize()
dt = 0.01
file = open("T.data", "w")
for i in range(1000):
    velocityVerlet(dt)
    file.write(str(instantaneousTemperature()) + '\n')
