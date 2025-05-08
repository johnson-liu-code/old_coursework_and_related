

import sys
import os
import pickle
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation


file_name = sys.argv[1]
save_file_name = sys.argv[2] + '.gif'
#save_file_name = 'test.gif'

#with open('test_001.pkl', 'rb') as savefile:
#    savedata = pickle.load(savefile)

with open(file_name, 'rb') as savefile:
    save_data = pickle.load(savefile)


directory_name = 'test/'
if not os.path.isdir(directory_name):
    os.makedirs(directory_name)

#cmap = colors.ListedColormap(['white', 'purple', 'pink', 'cyan'])
#for data in save_data[-1:]:
#    file_name = directory_name + 'save_configurations_{0:05d}.png'.format(data[0])
    #print(data[1])
    #fig = plt.figure()
#    im = plt.imshow(data[1], cmap=cmap)
    #plt.show()
#    plt.savefig(file_name)


'''
red_species = []
black_species = []
blue_species = []

for s in save_data:
    red_species_count = 0
    black_species_count = 0
    blue_species_count = 0

    for row in s[1]:
        red_species_count += row.count(1)
        black_species_count += row.count(2)
        blue_species_count += row.count(3)

    red_species.append(red_species_count)
    black_species.append(black_species_count)
    blue_species.append(blue_species_count)


plt.plot(red_species, color = 'red', label = 'red')
plt.plot(black_species, color = 'black', label = 'black')
plt.plot(blue_species, color = 'blue', label = 'blue')

plt.legend()

plt.show()
'''
#print( type( save_data[0][1]) )


#cmap = colors.ListedColormap(['white', 'grey', 'black'])
#cmap = colors.ListedColormap(['white', 'red', 'black'])
cmap = colors.ListedColormap(['white', 'purple', 'pink', 'cyan'])
#bounds = [-1, 0, 1]
#bounds = [0, 1, 2, 3]
#norm = colors.BoundaryNorm(bounds, cmap.N)

#conc_data = save_data[:]
'''
def animate(t):
    plt.cla()
    plt.imshow(save_data[t][1], cmap = cmap)
    #im.set_data( conc_data[t][1] )
    #return im

fig = plt.figure()
im = plt.imshow(save_data[0][1], cmap = cmap, interpolation='nearest', origin = 'lower')
#plt.axis('off')

#plt.plot(save_data[0][1])

#def init():
#    im.set_data( save_data[0][1] )

# init_func = init
# frames = save_data[-1][0]
ani = animation.FuncAnimation(fig, animate, len(save_data))
#ani.save(save_file_name, writer = 'imagemagick', fps = 10)
ani.save(save_file_name, fps = 15)
#plt.show()

'''
fig = plt.figure()

ims = []
for i in range(len(save_data)):
    im = plt.imshow(np.array( save_data[i][1] ), cmap=cmap, origin='lower', animated=True)
    ims.append([im])


ani = animation.ArtistAnimation(fig, ims, interval=100, blit=True, repeat_delay=10)
#ani.save(save_file_name, writer = 'imagemagick', fps = 15)
ani.save(save_file_name, fps = 15)

#print(ims[0])
#print(save_data[0][1])
#x = np.array(save_data[0][1])
#print(x)


#plt.show()

