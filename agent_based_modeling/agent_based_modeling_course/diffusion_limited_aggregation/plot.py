


import pickle
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation



with open('test_02.pkl', 'rb') as data_file:
    data = pickle.load(data_file)

cmap = colors.ListedColormap(['black', 'red', 'green'])

fig = plt.figure()

ims = []
for i in range(len(data)):
    if i%6 == 0:
        print(i)
        plt.cla()
        im = plt.imshow(data[i], cmap=cmap)
        #ims.append([im])
        plt.savefig('dla_movie_two_seeds_01/dla_01-{:03d}'.format(int(i/6)))


#ani = animation.ArtistAnimation(fig, ims, interval=100, blit=True, repeat_delay=10)
#ani.save('test.gif', fps = 15)
