

import os
import pickle
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from mpl_toolkits.axes_grid1 import make_axes_locatable


beta_chi = []
save_dir = 'save_lattice_dir_01/'
dir_list = sorted(os.listdir(save_dir))
for dir in dir_list:
    file_list = sorted(os.listdir(save_dir + dir))
    for fil in file_list:
        fields = fil.split('_')
        J = float(fields[1])
        beta = float(fields[3][:4])
        total_mag = 0
        total_mag_squared = 0
        with open(save_dir + dir + '/' + fil, 'rb') as dat:
            v = pickle.load(dat)
            for i in range(len(v[0])):
                for j in range(len(v[0])):
                    total_mag += v[i][j]
                    total_mag_squared += v[i][j]**2
        average_mag = total_mag / (len(v[0])**2)
        average_mag_squared = total_mag_squared / (len(v[0])**2)
        chi = beta * (average_mag_squared - average_mag**2)
        beta_chi.append( (beta, chi) )

beta, chi = zip(*beta_chi)

plt.plot(beta, chi)

plt.show()
