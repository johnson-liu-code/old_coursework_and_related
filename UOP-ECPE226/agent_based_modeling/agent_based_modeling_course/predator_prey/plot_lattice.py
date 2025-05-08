


import pickle
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation



with open('test_01.pkl', 'rb') as datafile:
    data = pickle.load(datafile)[:2]

#cmap = colors.ListedColormap(['black', 'red'])

'''
fig = plt.figure()

ims = []
for i in range(len(data)):
    plt.cla()
    im = plt.imshow( data[i][0] )
    ims.append( [im] )

ani = animation.ArtistAnimation(fig, ims, interval=100, blit=True)
'''

def animate(t):
    plt.cla()
    im1 = ax1.imshow( data[t][0] )
    fig.colorbar(im1)
    im2 = ax2.imshow( data[t][1], interpolation = 'nearest' )
    fig.colorbar(im2)

fig, (ax1, ax2) = plt.subplots(1, 2)

ani = animation.FuncAnimation( fig, animate, len(data) )

#plt.show()

ani.save('test_01.gif', fps = 15)
