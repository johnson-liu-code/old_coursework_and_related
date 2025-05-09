
import os
import sys
import pickle
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation


dir_name = sys.argv[1]

lattice_list = []

for fil_name in sorted(os.listdir(dir_name)):
    with open(dir_name + fil_name, 'rb') as fil:
        lattice = pickle.load(fil)
        lattice_list.append(lattice)

fig = plt.figure()
cmap = colors.ListedColormap(['white', 'black'])
bounds=[-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)
ims = []
for i in range(len(lattice_list)):
    im = plt.imshow(lattice_list[i], cmap=cmap, origin='lower', animated=True)
    ims.append([im])
ani = animation.ArtistAnimation(fig, ims, interval=100, blit=True, repeat_delay=10)
plt.show()
