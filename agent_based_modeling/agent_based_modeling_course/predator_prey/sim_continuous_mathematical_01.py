


import numpy as np
import matplotlib.pyplot as plt





x_init = 10
y_init = 10

time = 500000

x_data = [ x_init ]
y_data = [ y_init ]

x_prev = x_init
y_prev = y_init

dt = .001

t_lin = np.linspace(0, dt*time, time+1)

alpha = .1
#alpha = 2
beta = .2
#beta = .4
delta = .3
#delta = .1
gamma = .4
#gamma = 2

for t in range(time):
    dx = (alpha*x_prev - beta*x_prev * y_prev) * dt
    #dy = (delta*x_prev * y_prev - gamma*y_prev) * dt

    x_prev = x_prev + dx

    dy = (delta*x_prev * y_prev - gamma*y_prev) * dt
    y_prev = y_prev + dy

    x_data.append( x_prev )
    y_data.append( y_prev )

#print(x_data)


#plt.plot(t_lin, x_data, label = 'prey')
#plt.plot(t_lin, y_data, label = 'predator')

plt.plot(x_data, y_data)
#plt.scatter(gamma/delta, alpha/beta)

plt.legend()

plt.show()
