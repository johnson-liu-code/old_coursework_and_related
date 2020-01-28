

import os
import pickle
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from mpl_toolkits.axes_grid1 import make_axes_locatable


J_H = []
mag_J_H = []
save_dir = 'save_lattice_dir_03/'
J_list = np.arange(-1.0, 1.05, .05)
H_list = np.arange(-1.0, 1.05, .05)


#dir_list = sorted(os.listdir(save_dir))
#print dir_list
#for dir in dir_list:
#    file_list = sorted(os.listdir(save_dir + dir))
    #print file_list
for J in J_list:
    J_mag = []
    for H in H_list:
    #for fil in file_list:
        #fields = fil.split('_')
        #J = float(fields[1])
        #H = float(fields[3][:4])
        #print J, H
        mag = 0
        file_name = 'J_{0:.2f}/J_{1:.2f}_H_{2:.2f}.pickle'.format(J, J, H)
        #with open(save_dir + dir + '/' + fil, 'rb') as dat:
        with open(save_dir + file_name, 'rb') as dat:
            v = pickle.load(dat)
            for i in range(len(v[0])):
                for j in range(len(v[0])):
                    mag += v[i][j]
        mag = mag / (len(v[0])**2.)

        J_mag.append(mag)
        J_H.append( (J, H) )
    mag_J_H.append(J_mag)

J, H = zip(*J_H)
J = sorted(list(set(J)))
H = sorted(list(set(H)))

plt.figure()
ax = plt.gca()
im = ax.imshow(mag_J_H, cmap='cool', interpolation='nearest', origin='lower')
ax.set_xticks(np.arange(len(H)) )
ax.set_yticks(np.arange(len(J)) )
ax.set_xticklabels(['{0:.2f}'.format(h) for h in H], rotation=45)
ax.set_yticklabels(['{0:.2f}'.format(j) for j in J])
plt.xlabel('H')
plt.ylabel('J', rotation=0)
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size="5%", pad=0.05)
cbar = plt.colorbar(im, cax=cax, cmap='cool', label='Magnetization')

plt.show()

