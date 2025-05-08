


import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation



#print(np.random.randint(0,2))

x_len = 10
y_len = 10

lattice_1_dat = []
lattice_2_dat = []

for k in range(10):
    lattice_1 = [ [ np.random.randint(0,2) for j in range(y_len) ] for i in range(x_len) ]
    lattice_2 = [ [ np.random.randint(0,2) for j in range(y_len) ] for i in range(x_len) ]

    lattice_1_dat.append(lattice_1)
    lattice_2_dat.append(lattice_2)

#print(lattice_1)

'''
fig, (ax1, ax2) = plt.subplots(1, 2)

im1 = ax1.imshow(lattice_1)
im2 = ax2.imshow(lattice_2)


plt.show()
'''

'''
fig, (ax1, ax2) = plt.subplots(1, 2)

ims = []
for k in range(10):
    plt.cla()

    im1 = ax1.imshow(lattice_1_dat[k])
    im2 = ax2.imshow(lattice_2_dat[k])

    ims.append()

ani = animation.ArtistAnimation(fig, ims, interval=10, blit=True, repeat_delay=10)
plt.show()
'''

def animate(t):
    plt.cla()
    im1 = ax1.imshow(lattice_1_dat[t])
    im2 = ax2.imshow(lattice_2_dat[t])

fig, (ax1, ax2) = plt.subplots(1, 2)

ani = animation.FuncAnimation( fig, animate, len(lattice_1_dat) )


plt.show()
