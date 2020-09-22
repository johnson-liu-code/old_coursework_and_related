


import pickle
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation



with open('data/test_01.pkl', 'rb') as datafile:
    data = pickle.load(datafile)

print(len(data))

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

#def animate(t):
    #plt.clf()
    #fig, (ax1, ax2) = plt.subplots(1, 2)
#    im1 = ax1.imshow( data[t][0] )
#    fig.colorbar(im1)
#    im2 = ax2.imshow( data[t][1], interpolation = 'nearest' )
#    fig.colorbar(im2)
#    return im1, im2




animals, nutrients = zip(*data)

x_len = len(animals[0])
y_len = len(animals[0][0])

extent = [-0.5, x_len-0.5, -0.5, y_len-0.5]

xticks = np.arange(0, x_len, 1)
yticks = np.arange(0, y_len, 1)


print(xticks)
print(extent)

#print(animals)
max1 = max( max( map( max, animals ) ) )
#print(max1)
cmap1 = plt.get_cmap('cool', max1+1)
ticks1 = np.arange(0, max1+1)
boundaries1 = np.arange(-0.5, max1+1.5)

max2 = max( max( map( max, nutrients ) ) )
#print(max2)
cmap2 = plt.get_cmap('summer_r', max2+1)
ticks2 = np.arange(0, max2+1, 100)
boundaries2 = np.arange(-0.5, max2+1.5)



def animate(t):
    plt.cla()

    #plt.xticks(xticks)
    #plt.yticks(yticks)

    #fig, (cax1, ax1, ax2, cax2) = plt.subplots(1, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

    #max1 = max( map( max, data[t][0] ) )
    #cmap1 = plt.get_cmap('cool', max1+1)

    im1 = ax1.imshow(data[t][0], cmap=cmap1, vmin = -.5, vmax = max1+.5, extent=extent)
    ax1.set_xticks(xticks)
    ax1.set_yticks(yticks)
    #ticks1 = np.arange(0, max1+1)
    #boundaries1 = np.arange(-0.5, max1+1.5)
    cb1 = matplotlib.colorbar.ColorbarBase(cax1, cmap=cmap1, ticks=ticks1, boundaries=boundaries1)

    #max2 = max( map( max, data[t][1] ) )
    #cmap2 = plt.get_cmap('summer_r', max2+1)

    im2 = ax2.imshow(data[t][1], cmap=cmap2, vmin = 0, vmax = max2, extent=extent)
    ax2.set_xticks(xticks)
    ax2.set_yticks(yticks)
    #ticks2 = np.arange(0, max2+1, 10)
    #boundaries2 = np.arange(-0.5, max2+1.5)
    cb2 = matplotlib.colorbar.ColorbarBase(cax2, cmap=cmap2, ticks=ticks2, boundaries=boundaries2)

    fig.tight_layout()


fig, (cax1, ax1, ax2, cax2) = plt.subplots(1, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

ani = animation.FuncAnimation( fig, animate, len(data) )

#plt.show()

ani.save('test_01.gif', fps = 20)
