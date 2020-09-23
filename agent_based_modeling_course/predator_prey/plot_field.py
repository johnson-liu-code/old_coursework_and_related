


import sys
import pickle
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation



data_file_name = sys.argv[1]
save_fig_name = sys.argv[2] + '.gif'


with open(data_file_name, 'rb') as datafile:
    data = pickle.load(datafile)

#print(len(data))

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
#print(animals)

x_len = len(animals[0])
y_len = len(animals[0][0])


data_len = len(animals)
animals_over_time = []
nutrients_over_time = []

for t in range(data_len):
    animal_total = 0
    nutrient_total = 0
    for i in range(x_len):
        for j in range(y_len):
            animal_total = animal_total + animals[t][i][j]
            nutrient_total = nutrient_total + nutrients[t][i][j]

    animals_over_time.append(animal_total)
    nutrients_over_time.append(nutrient_total)

#for a in animals_over_time:
#    print(a)

animals_over_time = np.array( animals_over_time ) / max(animals_over_time)
nutrients_over_time = np.array( nutrients_over_time ) / max(nutrients_over_time)

plt.plot(animals_over_time, label = 'Prey')
plt.plot(nutrients_over_time, label = 'Nutrients')

#plt.plot(animals_over_time, nutrients_over_time)

plt.grid(linestyle = '--')

plt.xlabel('Time')
plt.ylabel('Amount')
plt.legend()

plt.show()

'''
extent = [-0.5, x_len-0.5, -0.5, y_len-0.5]

xticks = np.arange(0, x_len, 1)
yticks = np.arange(0, y_len, 1)

#print(xticks)
#print(extent)

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
    #plt.cla()

    #plt.xticks(xticks)
    #plt.yticks(yticks)

    #fig, (cax1, ax1, ax2, cax2) = plt.subplots(1, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

    #max1 = max( map( max, data[t][0] ) )
    #cmap1 = plt.get_cmap('cool', max1+1)

    #im1 = ax1.imshow(data[t][0], cmap=cmap1, vmin = -.5, vmax = max1+.5, extent=extent)
    im1.set_data(data[t][0])
    #ax1.set_xticks(xticks)
    #ax1.set_yticks(yticks)

    #ticks1 = np.arange(0, max1+1)
    #boundaries1 = np.arange(-0.5, max1+1.5)
    #cb1 = matplotlib.colorbar.ColorbarBase(cax1, cmap=cmap1, ticks=ticks1, boundaries=boundaries1)

    #max2 = max( map( max, data[t][1] ) )
    #cmap2 = plt.get_cmap('summer_r', max2+1)

    #im2 = ax2.imshow(data[t][1], cmap=cmap2, vmin = 0, vmax = max2, extent=extent)
    im2.set_data(data[t][1])
    #ax2.set_xticks(xticks)
    #ax2.set_yticks(yticks)

    #ticks2 = np.arange(0, max2+1, 10)
    #boundaries2 = np.arange(-0.5, max2+1.5)
    #cb2 = matplotlib.colorbar.ColorbarBase(cax2, cmap=cmap2, ticks=ticks2, boundaries=boundaries2)

    #fig.tight_layout()


fig, (cax1, ax1, ax2, cax2) = plt.subplots(1, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

im1 = ax1.imshow(data[0][0], cmap=cmap1, vmin = -.5, vmax = max1+.5, extent=extent)
im2 = ax2.imshow(data[0][1], cmap=cmap2, vmin = 0, vmax = max2, extent=extent)

cb1 = matplotlib.colorbar.ColorbarBase(cax1, cmap=cmap1, ticks=ticks1, boundaries=boundaries1)
cb2 = matplotlib.colorbar.ColorbarBase(cax2, cmap=cmap2, ticks=ticks2, boundaries=boundaries2)

ax1.set_xticks(xticks)
ax1.set_yticks(yticks)

ax2.set_xticks(xticks)
ax2.set_yticks(yticks)

fig.tight_layout()

ani = animation.FuncAnimation( fig, animate, len(data) )

#plt.show()

ani.save(save_fig_name, fps = 10)
'''
