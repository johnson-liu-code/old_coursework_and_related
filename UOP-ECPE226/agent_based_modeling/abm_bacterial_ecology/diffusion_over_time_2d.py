

import sys
import numpy as np
import random
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from matplotlib import colors
import pickle

from determine_ij import determine_ij



file_name = sys.argv[1] + '.pkl'


n = 41
v = [ [ [] for x in range(n)] for y in range(n)]

a = 16807
m = 2147483647
c = 0

xn = 54938

diffuse_prob = .2

class particle():
    moved = False

### Initial Conditions #########

v[20][20] = [ particle() for x in range(1000)]

'''
#for j in range(45, 56):
#    for i in range(45, 56):
for j in range(19, 21):
    for i in range(19, 21):
        #v[j][i] = 100
        v[j][i] = [ particle() for x in range(500) ]
'''

################################

data = []

time = 10

for t in range(time):
    w = np.zeros((n,n))
    for i in range(n):
        for j in range(n):
            for p in v[i][j]:
                if p.moved == False:
                    r = random.random()
                    if r >= diffuse_prob:
                        i_up, i_down, j_left, j_right = determine_ij(i, j, n, n)

                        north = len( v[i_up][j] )
                        south= len( v[i_down][j] )
                        west = len( v[i][j_left] )
                        east = len( v[i][j_right] )

                        total = float( north + south + west + east )

                        if total == 0:
                            north, south, west, east = 1, 1, 1, 1
                            total = 4.

                        xf = (a*xn + c)%m
                        xn = float(xf)
                        xnm = xn/m

                        part = particle()
                        part.moved = True

                        if 0 <= xnm < (north)/total:
                            v[i_up][j].append(part)

                        elif (north)/total <= xnm < (north+south)/total:
                            v[i_down][j].append(part)

                        elif (north+south)/total <= xnm < (north+south+west):
                            v[i][j_left].append(part)

                        elif (north+south+west)/total <= xnm <= 1:
                            v[i][j_right].append(part)

                        v[i][j].remove(p)

    for i in range(n):
        for j in range(n):
            w[i][j] = len(v[i][j])
            for p in v[i][j]:
                p.moved = False

    data.append(w)


### Plot particles ###############


'''
w = np.zeros((n,n))

#maximum = 0
for j in range(n):
    for i in range(n):
        num_particles = len(v[j][i])
        #if num_particles > maximum:
        #    maximum = num_particles
        w[j][i] = num_particles
'''

'''
cmap = plt.get_cmap('BuPu', np.max(w)+1)
#cmap = plt.get_cmap('BuPu', maximum + 1)
mat = plt.matshow(w, cmap = cmap, vmin = -.5, vmax = np.max(w)+.5)
cax = plt.colorbar(mat, label = "Number of Particles")
plt.title("Time = %s iterations" %time)

plt.show()
'''

with open(file_name, 'wb') as save_file:
    pickle.dump(data, save_file)
