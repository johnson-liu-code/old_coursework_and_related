# code to reproduce results in LA_1940 by Fermi, Pasta, Ulam, Tsingou

from math import sin, pi, sqrt

def Fourier_sine_transform(x, inverse=False):
    a = [0.0 for i in range(len(x))]
    N = len(x) - 1
    for k in range(1, N):
        for i in range(1, N):
            a[k] += x[i] * sin(i * k * pi / float(N))
    if inverse:
        for k in range(1, N):
            a[k] *= 2.0 / float(N)
    return a

def E(x, dxdt, alpha):
    N = len(x) - 1
    E_kin = 0.0
    for i in range(1, N):
        E_kin += dxdt[i]**2 / 2.0
    E_pot = 0.0
    for i in range(1, N+1):
        dx = x[i] - x[i-1]
        E_pot += dx**2 / 2.0 + alpha * dx**3 / 3.0
    return E_kin + E_pot

def E_mode(x, dxdt):
    N = len(x) - 1
    a = Fourier_sine_transform(x)
    dadt = Fourier_sine_transform(dxdt)
    E_mode = [0.0 for i in range(len(x))]
    for k in range(1, N):
        E_kin = 0.5 * dadt[k]**2
        E_pot = 2 * (a[k] * sin(k * pi / (2.0 * N)))**2
        E_mode[k] = E_kin + E_pot
    return E_mode

def compute_accelerations(x, d2xdt2, alpha):
    N = len(x) - 1
    for i in range(1, N):
        dx_plus = x[i+1] - x[i]
        dx_minus = x[i] - x[i-1]
        d2xdt2[i] = dx_plus - dx_minus + alpha * (dx_plus**2 - dx_minus**2)

def initialize(a, x, dxdt, d2xdt2, alpha):
    N = len(x) - 1
    # zero all components
    for i in range(N+1):
        x[i] = dxdt[i] = d2xdt2[i] = 0.0

    # inverse sine transform of mode amplitudes
    inverse = True
    dx = Fourier_sine_transform(a, inverse)
    for i in range(1, N):
        x[i] = dx[i]

    # adjust amplitude
    x_max = 0.0
    for i in range(1, N):
        ax = abs(x[i])
        if ax > x_max:
            x_max = ax
    for i in range(1, N):
        x[i] /= x_max

    compute_accelerations(x, d2xdt2, alpha)

def velocity_Verlet(dt, x, dxdt, d2dxt2, alpha):
    N = len(x) - 1
    for i in range(1, N):
        x[i] += dxdt[i] * dt + 0.5 * d2xdt2[i] * dt**2
        dxdt[i] += 0.5 * d2xdt2[i] * dt
    compute_accelerations(x, d2xdt2, alpha)
    for i in range(1, N):
        dxdt[i] += 0.5 * d2xdt2[i] * dt

print(" Studies of Nonlinear Problems by Fermi, Pasta, Ulam, Tsingou")
print(" ------------------------------------------------------------")

N = 32
alpha = 1.0 / 4.0
delta_t = sqrt(1.0 / 8.0)
print(" N = ", N, " alpha = ", alpha, " delta_t = ", delta_t)

computation_steps_per_cycle = 100
dt = delta_t / computation_steps_per_cycle
print(" integration time step dt = ", dt)

# create vectors for position, velocity, acceleration, mode amplitudes
x = [0.0 for i in range(N+1)]
dxdt = [0.0 for i in range(N+1)]
d2xdt2 = [0.0] * (N + 1)
a = [0.0] * (N + 1)

# initialize with lowest eigenmode of the linear chain
a[1] = 1.0
initialize(a, x, dxdt, d2xdt2, alpha)

E_a = E_mode(x, dxdt)
E_scale = E_a[1] / 300.0

fpu1 = open("fpu1.data", "w")
fpu8 = open("fpu8.data", "w")

for i in range(N+1):
    fpu8.write(str(i) + '\t' + str(x[i]) + '\n')

nc = 1000
computation_cycles = 30 * nc
for cycle in range(computation_cycles+1):
    # save total and mode energies every nc cycles
    if cycle % (nc//10) == 0:
        t = cycle / float(nc)
        energy = E(x, dxdt, alpha)
        E_a = E_mode(x, dxdt)

        data = " " + str(t) + '\t' + str(energy)
        for k in range(1, 6):
            data += '\t' + str(E_a[k] / E_scale)
        # sum energies in modes 6 through N
        energy = 0;
        for k in range(6, N+1):
            energy += E_a[k] * E_scale;
        data += '\t' + str(energy)
        print(data)
        fpu1.write(data + '\n')

    if cycle in [1000, 10000, 12000, 14000, 19000, 22000, 28311]:
        fpu8.write('\n')
        for i in range(N+1):
            fpu8.write(str(i) + '\t' + str(x[i]) + '\n')

    for step in range(computation_steps_per_cycle):
        velocity_Verlet(dt, x, dxdt, d2xdt2, alpha)
