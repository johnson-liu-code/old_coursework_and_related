from math import sqrt
from random import normalvariate

# simulation parameters

N = 64                      # number of particles
rho = 1.0                   # density (number per unit volume)
T = 1.0                     # temperature

def initialize():
    global r, v, a          # set values for global variables
    r = [ [0.0] * 3 for i in range(N) ]
    v = [ [0.0] * 3 for i in range(N) ]
    a = [ [0.0] * 3 for i in range(N) ]
    initPositions()
    initVelocities()

L = 10.0                    # linear size of cubical volume

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

def computeAccelerations():
    global a
    for i in range(N):          # set all accelerations to zero
        for k in range(3):
            a[i][k] = 0.0
    for i in range(N - 1):      # loop over all distinct pairs i,j
        for j in range(i + 1, N):
            rij = [0.0] * 3     # position of i relative to j
            rSqd = 0.0
            for k in range(3):
                rij[k] = r[i][k] - r[j][k]
                # closest image convention
                if abs(rij[k]) > 0.5 * L:
                    if rij[k] > 0.0:
                        rij[k] -= L
                    else:
                        rij[k] += L
                rSqd += rij[k] * rij[k]
            f = 48.0 / rSqd**7 - 24.0 / rSqd**4
            for k in range(3):
                 a[i][k] += rij[k] * f
                 a[j][k] -= rij[k] * f

def velocityVerlet(dt):
    global r, v
    computeAccelerations()
    for i in range(N):
        for k in range(3):
            r[i][k] += v[i][k] * dt + 0.5 * a[i][k] * dt**2
            # use periodic boundary conditions
            if r[i][k] < 0.0:
                r[i][k] += L
            if r[i][k] >= L:
                r[i][k] -= L
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
file = open("T2.data", "w")
for i in range(1000):
    velocityVerlet(dt)
    file.write(str(instantaneousTemperature()) + '\n')
    if i % 200 == 0:
        rescaleVelocities()
file.close()
