

import numpy as np
import pickle
#import matplotlib.pyplot as plt
#from matplotlib import colors
#import matplotlib.animation as animation

from determine_ij import determine_ij


def get_rand_coors(x_len, y_len, num_coors):
    # Generate a list of coordinates that does not repeat.
    coors_list = []
    # Generate num_coors number of coordinates.
    while len(coors_list) < num_coors:
        x_coor = np.random.randint(0, x_len-1)
        y_coor = np.random.randint(0, y_len-1)
        if (x_coor, y_coor) not in coors_list:
            coors_list.append( (x_coor, y_coor) )
    return coors_list

#cmap = colors.ListedColormap(['black', 'red', 'green'])

if __name__ == '__main__':
    n = 100
    k = 2500

    # 0 is black
    lattice = [ [ 0 for j in range(n) ] for i in range(n)]

    rand_init_list = get_rand_coors(n, n, k)

    # 1 is red
    for r in rand_init_list:
        lattice[ r[0] ][ r[1] ] = 1

    # 2 is green
    lattice[25][25] = 2
    lattice[75][75] = 2
    #lattice[5][5] = 2

    #w = np.zeros((n,n))
    #for i in range(n):
    #    for j in range(n):
    #        w[i][j] = lattice[i][j]

    data = []

    a = 0

    stop = False
    while stop == False:
        print(a)

        w = np.zeros((n,n))
        for i in range(n):
            for j in range(n):
                w[i][j] = lattice[i][j]

        for i in range(n):
            for j in range(n):
                if lattice[i][j] == 1:
                    i_up, i_down, j_left, j_right = determine_ij(i, j, n, n)
                
                    # north, south, west, east
                    #occupied = [ lattice[i_up][j] != 0, lattice[i_down][j] != 0, lattice[i][j_left] != 0, lattice[i][j_right] != 0 ]
                    occupied = [ w[i_up][j] != 0, w[i_down][j] != 0, w[i][j_left] != 0, w[i][j_right] != 0 ]

                    valid = False

                    if occupied[0] and occupied[1] and occupied[2] and occupied[3]:
                        valid = True

                    while valid == False:
                        #print('stuck here')
                        #if a == 1:
                        #    valid = True
                        #    stop = True
                        #    break
                        r = np.random.random()

                        # north
                        if 0 < r <= 1./4:
                            #if lattice[i_up][j] == 2:
                            #    lattice[i][j] = 2
                            #    valid = True
                            if occupied[0] == False:
                                #w[i][j], w[i_up][j] = lattice[i_up][j], lattice[i][j]
                                w[i][j] = 0
                                w[i_up][j] = 1
                                valid = True

                        # south
                        elif 1./4 < r <= 2./4:
                            #if lattice[i_down][j] == 2:
                            #    lattice[i][j] = 2
                            #    valid = True
                            if occupied[1] == False:
                                #w[i][j], w[i_down][j] = lattice[i_down][j], lattice[i][j]
                                w[i][j] = 0
                                w[i_down][j] = 1
                                valid = True

                        # west
                        elif 2./4 < r <= 3./4:
                            #if lattice[i][j_left] == 2:
                            #    lattice[i][j] = 2
                            #    valid = True
                            if occupied[2] == False:
                                #w[i][j], w[i][j_left] = lattice[i][j_left], lattice[i][j]
                                w[i][j] = 0
                                w[i][j_left] = 1
                                valid = True

                        # east
                        elif 3./4 < r <= 1.:
                            #if lattice[i][j_right] == 2:
                            #    lattice[i][j] = 2
                            #    valid = True
                            if occupied[3] == False:
                                #w[i][j], w[i][j_right] = lattice[i][j_right], lattice[i][j]
                                w[i][j] = 0
                                w[i][j_right] = 1
                                valid = True
                #else:
                #    w[i][j] = 1

        for i in range(n):
            for j in range(n):
                i_up, i_down, j_left, j_right = determine_ij(i, j, n, n)
                #if lattice[i][j] == 1:
                if w[i][j] == 1:
                    #if lattice[i_up][j] == 2 or lattice[i_down][j] == 2 or lattice[i][j_left] == 2 or lattice[i][j_right] == 2:
                    if w[i_up][j] == 2 or w[i_down][j] == 2 or w[i][j_left] == 2 or w[i][j_right] == 2:
                        w[i][j] = 2

        data.append(w)

        live_cells = 0.
        for i in range(n):
            for j in range(n):
                if w[i][j] == 1:
                    live_cells = live_cells + 1
                lattice[i][j] = w[i][j]

        print('live cells: ' + str(live_cells))
        print('ratio: ' + str(live_cells/k))

        #if live_cells/k < .02:
        #    stop = True
        #    break

        stop_2 = True
        for i in range(n):
            if 1 in lattice[i]:
                stop_2 = False
                break

        if stop_2 == True:
            stop = True        

        a = a + 1
        #if a == 1000:
        #    stop = True

    with open('test_02.pkl', 'wb') as save_file:
        pickle.dump(data, save_file)

    #plt.imshow(lattice, cmap = cmap)

    #plt.show()
