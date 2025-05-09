
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


h_bar = 1
m = 1
dx = .1
V = 0

a = 1
p = 1
n = 1

E = (n**2 * p**2 * h_bar**2) / (2 * m * a**2)
#E = -1
C = -(2*m)/h_bar**2 * dx**2

length = 1
intervals = int(length/dx)
time = 2

# mat = (C * (E - V) + 2)**-1 * np.diag(np.ones(intervals-1), 1) + np.diag(np.ones(intervals-1), -1)

mat = np.diag(np.ones(intervals-1), 1) + np.diag(np.ones(intervals-1), -1)
mat[0], mat[-1] = 0, 0
#print(mat)


psi = np.ones(intervals).reshape(intervals, 1)
# psi[int(intervals/2),:] = -2

psi[0][0] = 0
psi[-1][0] = 0

data = np.zeros( (intervals, time) )
data[:,0] = psi[:,0]

#print(data[:,0])
#print(psi)
#print(psi[:,0])


for t in range(1, time):
    psi = np.dot(mat, psi)
    data[:,t] = psi[:,0]
    #print(psi)


'''
fig, ax = plt.subplots()
ax.set(xlim=(0, intervals), ylim=(-500, 500))
ax.set(xlim=(0, intervals))

line = ax.plot(range(intervals), data[:,0], color='k', lw=2)[0]

def animate(i):
    line.set_ydata(data[:,i])

anim = FuncAnimation(fig, animate, interval=200, frames=time-1, repeat=False)

plt.draw()
plt.show()
'''
