# Zabusky and Kruskal, Phys. Rev. Lett. 15, 240-243 (1965)

from math import cos, cosh, pi

delta = 0.022

#  spatial grid
N = 256
L = 2.0
h = L / float(N)        # spatial interval

x = [ 0.0 ] * N
for i in range(N):
    x[i] = i * h

#  initialize solution vector on spatial grid
u = [ 0.0 ] * N
for i in range(N):
    u[i] = cos(pi * x[i])

#  write initial waveform to file
file = open("kdv.data", "w")
for i in range(N):
    file.write(' ' + str(x[i]) + '\t' + str(u[i]) + '\n')
file.write('\n')

#  temporal grid
T_B = 1 / pi
k = h**3                # time step must satisfy CFL criterion

#  take one time step to prime the algorithm
u_minus = [ 0.0 ] * N
for i in range(N):
    u_minus[i] = u[i]
    #  u = cos(pi(x-ut) if delta^2u_xxx is negligible
    u[i] = cos(pi * (x[i] - u[i] * k))
u_plus = [ 0.0 ] * N

t_max = 4 * T_B
t = 0.0

while t <= t_max:
    #  write waveform to file at selected times
    if abs(t - T_B) <  k / 2 or abs(t - 3.6 * T_B) < k / 2:
        for i in range(N):
            file.write(' ' + str(x[i]) + '\t' + str(u[i]) + '\n')
        file.write('\n')
    #  use algorithm in Footnote 6 to evolve in time
    for i in range(N):
        ip2 = (i + 2 + N) % N ; ip1 = (i + 1 + N) % N
        im1 = (i - 1 + N) % N ; im2 = (i - 2 + N) % N
        u_plus[i] = (u_minus[i] - (1 / 3.0) * (k / h) *
            (u[ip1] + u[i] + u[im1]) * (u[ip1] - u[im1]) -
            (delta * delta * k / (h * h * h)) *
            (u[ip2] - 2.0 * u[ip1] + 2.0 * u[im1] - u[im2]) )
    for i in range(N):
        u_minus[i] = u[i]
        u[i] = u_plus[i]
    t += k

file.close()
