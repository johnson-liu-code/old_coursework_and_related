

import sys
import pickle
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
from matplotlib import animation


file_name = sys.argv[1] + '.pkl'

with open(file_name, 'rb') as save_file:
    data = pickle.load(save_file)


fig = plt.figure()
im = plt.imshow( data[0], cmap = 'BuPu' )

def init():
    im.set_data( data[0] )

def animate(t):
    im = plt.imshow( data[t], cmap = 'BuPu')
    #im.set_data( data[t] )
    return im

anim = animation.FuncAnimation(fig, animate, init_func = init, frames = len(data), interval = 5)

plt.show()
