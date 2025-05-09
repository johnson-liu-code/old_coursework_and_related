# Duffing Oscillator

from math import cos

# physics parameters
omega = 2.4
gamma = 0.1
a = 0.5
b = 0.25
F0 = 2.0

# Duffing equation
def dxvdt(t, xv):
    dxdt = xv[1]
    dvdt = - gamma * xv[1] + 2 * a * xv[0] - 4 * b * xv[0]**3
    dvdt += F0 * cos(omega * t)
    return [dxdt, dvdt]

# get input from user and initialize
print(' Duffing Oscillator Simulation')
print(' =============================')
x = float(input(' Enter initial x: '))
v = float(input(' Enter initial v: '))
xv = [x, v]
dt = float(input(' Enter time step dt: '))
t_max = float(input(' Enter integration time: '))
file_name = input(' Enter output file name: ')
file = open(file_name, "w")
t = 0.0
file.write(str(t) + '\t' + str(xv[0]) + '\t' + str(xv[1]) + '\n')

# main integration loop
while t < t_max:
    # 4th order Runge-Kutta step
    k1 = [ dt * d for d in dxvdt(t, xv) ]
    xv_step = [ xv[i] + k1[i] / 2 for i in range(2) ]
    k2 = [ dt *  d for d in dxvdt(t + 0.5 * dt, xv_step) ]
    xv_step = [ xv[i] + k2[i] / 2 for i in range(2) ]
    k3 = [ dt * d for d in dxvdt(t + 0.5 * dt, xv_step) ]
    xv_step = [ xv[i] + k3[i] for i in range(2) ]
    k4 = [ dt * d for d in dxvdt(t + dt, xv_step) ]
    for i in range(2):
        xv[i] += (k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i]) / 6.0
    t += dt
    file.write(str(t) + '\t' + str(xv[0]) + '\t' + str(xv[1]) + '\n')

file.close()
print(' Output in file:', file_name)
