
import sys
import pickle
import matplotlib.pyplot as plt
from matplotlib import colors
from mpl_toolkits.axes_grid1 import make_axes_locatable


#with open('save_lattice_dir_3/J_1.10/J_1.10_beta_0.70.pickle', 'rb') as fil:
    #v = pickle.load(fil)

file_name = sys.argv[1]
with open(file_name, 'rb') as fil:
    v = pickle.load(fil)

cmap = colors.ListedColormap(['white', 'black'])
bounds=[-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)

plt.figure()
fig = plt.imshow(v, cmap = cmap,  interpolation='nearest', origin = 'lower')
plt.colorbar(fig, cmap=cmap, norm=norm, boundaries=bounds, ticks=[-1, 1])
#plt.title(r'$\beta = $' + str(B) + '\n' + r'$J = $' + str(J_))
plt.show()

