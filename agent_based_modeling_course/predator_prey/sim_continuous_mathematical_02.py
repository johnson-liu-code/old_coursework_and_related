


import numpy as np
import matplotlib.pyplot as plt





#x_init_list = [1, 2, 3, 4, 5]
#y_init_list = [1, 2, 3, 4, 5]
x_init_list = np.arange(1, 5)
y_init_list = np.arange(1, 5)

#x_init_list = np.arange(4, 8)
#y_init_list = np.arange(1, 5)

time = 200000

#x_data = [ [x_init] for x_init in x_init_list ]
#y_data = [ [y_init] for y_init in y_init_list ]
x_data = [ [10] ]
y_data = [ [2] ]

dt = .001

t_lin = np.linspace(0, dt*time, time)

#alpha = .4
alpha = .1
#beta = .3
beta = .5
#delta = .2
delta = .5
#gamma = .1
gamma = .1

for t in range(1, time):
    for c, item in enumerate(x_data):
        dx = (alpha*x_data[c][t-1] - beta*x_data[c][t-1] * y_data[c][t-1]) * dt
        #dy = (delta*x_prev * gamma*y_prev - y_prev) * dt
        new_x = x_data[c][t-1] + dx

        dy = (delta*new_x * y_data[c][t-1] - gamma*y_data[c][t-1]) * dt
        new_y = y_data[c][t-1] + dy

        x_data[c].append( new_x )
        y_data[c].append( new_y )

#print(x_data)


plt.plot(t_lin, x_data[0], label = 'Prey, P$_0$ = {}'.format(x_data[0][0]))
plt.plot(t_lin, y_data[0], label = 'Predator, P$_0$ = {}'.format(y_data[0][0]))
plt.scatter(1, 1, color = 'white', label = r'$\alpha = {0}, \beta = {1},$'.format(alpha, beta) + '\n' + r'$\delta = {0}, \gamma = {1}$'.format(delta, gamma))

#plt.scatter(gamma/delta, alpha/beta)

plt.xlabel('Simulation Time')
plt.ylabel('Population Size')

#print(x_data[c])
#print(y_data[c])


#for c, item in enumerate(x_data):
#    plt.plot(x_data[c], y_data[c])

plt.legend()

plt.grid(linestyle = '--')

#plt.show()
plt.savefig('prey_pred_004.png')
