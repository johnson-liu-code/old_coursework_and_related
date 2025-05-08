

import sys
import pickle
import numpy as np


from determine_ij import determine_ij


savefile_name = 'data/test_001/' + sys.argv[1] + '.pkl'


class cell():
    type = 0


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


def init_lattice_binary(x_len, y_len, num_coors):
    # Create a lattice and randomly pick certain cells to be "on" (have a value of 1 instead of 0).
    lattice = [ [cell() for y in range(y_len)] for x in range(x_len) ]
    coors_list = get_rand_coors(x_len, y_len, num_coors)
    for coor in coors_list:
        x, y = coor[0], coor[1]
        lattice[x][y].type = 1
    return lattice


def init_lattice_rps(x_len, y_len):
    lattice = [ [cell() for y in range(y_len)] for x in range(x_len) ]
    for x in range(x_len):
        for y in range(y_len):
            lattice[x][y].type = np.random.randint(0,3)
    return lattice

'''
def determine_ij(i, j, x_len, y_len):
    # Compute the i, j coordinates of neighboring cells (includes wrap-around on lattice).
    if i == 0:
        i_up = 1
        i_down = x_len - 1
    elif i == x_len - 1:
        i_up = 0
        i_down = i - 1
    else:
        i_up = i + 1
        i_down = i - 1
    if j == 0:
        j_left = y_len - 1
        j_right = 1
    elif j == y_len - 1:
        j_left = j - 1
        j_right = 0
    else:
        j_left = j - 1
        j_right = j + 1

    return i_up, i_down, j_left, j_right
'''

# Game of Life style update.
def update_binary(lattice, x_len, y_len):
    for i in range(x_len):
        for j in range(y_len):
            i_up, i_down, j_left, j_right = determine_ij(i, j, x_len, y_len)
            sum = lattice[i][j_left].type
            sum += lattice[i][j_right].type
            sum += lattice[i_up][j].type
            sum += lattice[i_down][j].type
            sum += lattice[i_up][j_left].type
            sum += lattice[i_up][j_right].type
            sum += lattice[i_down][j_left].type
            sum += lattice[i_down][j_right].type
            #if sum >= 3 and sum <= 5:
            #if sum >= 3 and sum <= 4:
            #if sum >= 2 and sum <= 7:
            if sum >= 1 and sum <= 3:
                lattice[i][j].type = 1
            else:
                lattice[i][j].type = 0
            #if lattice[i][j].type == 0 and sum >= 1 and sum <= 5:
            #    lattice[i][j].type = 1
            #elif lattice[i][j].type == 1 and sum == 3:
            #    lattice[i][j].type = 0

    return lattice


def update_rps_01(lattice, x_len, y_len):
    #temp_lattice = [row[:] for row in lattice]
    new_lattice = [ [cell() for y in range(y_len)] for x in range(x_len) ]

    for i in range(x_len):
        for j in range(y_len):
            i_up, i_down, j_left, j_right = determine_ij(i, j, x_len, y_len)

            neighbor_types = [ lattice[i][j_left].type, lattice[i][j_right].type,
                               lattice[i_up][j].type, lattice[i_down][j].type,
                               lattice[i_up][j_left].type, lattice[i_up][j_right].type,
                               lattice[i_down][j_left].type, lattice[i_down][j_right].type ]

            type_0 = neighbor_types.count(0)
            type_1 = neighbor_types.count(1)
            type_2 = neighbor_types.count(2)

            types = [type_0, type_1, type_2]

            max_value = max(types)
            max_index = types.index(max_value)

            new_lattice[i][j].type = max_index

    return new_lattice


def update_rps_02(lattice, x_len, y_len):
    new_lattice = [row[:] for row  in lattice]
    #new_lattice = [ [cell() for y in range(y_len)] for x in range(x_len) ]

    for i in range(x_len):
        for j in range(y_len):
            i_up, i_down, j_left, j_right = determine_ij(i, j, x_len, y_len)

            neighbor_types = [ lattice[i][j_left].type, lattice[i][j_right].type,
                               lattice[i_up][j].type, lattice[i_down][j].type,
                               lattice[i_up][j_left].type, lattice[i_up][j_right].type,
                               lattice[i_down][j_left].type, lattice[i_down][j_right].type ]

            type_1 = neighbor_types.count(1)
            type_2 = neighbor_types.count(2)
            type_3 = neighbor_types.count(3)

            if lattice[i][j].type == 1:
                if type_2 > type_1:
                    new_lattice[i][j].type = 2
                #else:
                #    new_lattice[i][j].type = 0

            elif lattice[i][j].type == 2:
                if type_3 > type_2:
                    new_lattice[i][j].type = 3
                #else:
                #    new_lattice[i][j].type = 0

            elif lattice[i][j].type == 3:
                if type_1 > type_3:
                    new_lattice[i][j].type = 1
                #else:
                #    new_lattice[i][j].type = 0

    return new_lattice


def update_rps_03(lattice, x_len, y_len, num_coors):
    coors = get_rand_coors(x_len, y_len, num_coors)

    for coor in coors:
        i, j = coor[0], coor[1]
        i_up, i_down, j_left, j_right = determine_ij(i, j, x_len, y_len)

        cell_1 = lattice[i][j]

        direction = np.random.randint(0,3)
        if direction == 0:              # Take the above cell.
            cell_2 = lattice[i_up][j]
            cell_1, cell_2 = combat(cell_1, cell_2)
            lattice[i_up][j] = cell_2

        elif direction == 1:            # Take the right cell.
            cell_2 = lattice[i][j_right]
            cell_1, cell_2 = combat(cell_1, cell_2)
            lattice[i][j_right] = cell_2

        elif direction == 2:            # Take the below cell.
            cell_2 = lattice[i_down][j]
            cell_1, cell_2 = combat(cell_1, cell_2)
            lattice[i_down][j] = cell_2

        elif direction == 3:            # Take the left cell.
            cell_2 = lattice[i][j_left]
            cell_1, cell_2 = combat(cell_1, cell_2)
            lattice[i][j_left] = cell_2

    return lattice

def combat(cell_1, cell_2):
    if cell_1.type == 0 and cell_2.type != 0:
        cell_1.type = cell_2.type

    elif cell_1.type != 0 and cell_2.type == 0:
        cell_2.type = cell_1.type

    elif cell_1.type != 0 and cell_2.type != 0:
        if cell_1.type == 1 and cell_2.type == 2:
            cell_1.type = 0

        elif cell_1.type == 2 and cell_2.type == 1:
            cell_2.type = 0

        elif cell_1.type == 2 and cell_2.type == 3:
            cell_1.type = 0

        elif cell_1.type == 3 and cell_2.type == 2:
            cell_2.type = 0

        elif cell_1.type == 3 and cell_2.type == 1:
            cell_1.type = 0

        elif cell_1.type == 1 and cell_2.type == 3:
            cell_2.type = 0

    return cell_1, cell_2


if __name__ == '__main__':
    x_len = 150
    y_len = 150
    num_coors = 2000
    trajecs = 2000

    savedata = []

    '''
    # Initiate a lattice of cells.
    lattice = init_lattice_binary(x_len, y_len, num_coors)
    #print('lattice:\n', lattice)
    '''
    lattice = init_lattice_rps(x_len, y_len)

    # Generate a lattice of types. (Why is this necessary? Is it to print the lattice?)
    lat = [ [lattice[x][y].type for y in range(y_len)] for x in range(x_len) ]

    savedata.append( (0, lat) )

    for traj in range(1, trajecs):
        print(traj)
        #lattice = update_binary(lattice, x_len, y_len)
        #lattice = update_rps_02(lattice, x_len, y_len)
        lattice = update_rps_03(lattice, x_len, y_len, num_coors)

        lat = [ [lattice[x][y].type for y in range(y_len)] for x in range(x_len) ]

        savedata.append( (traj, lat) )

    #with open('test_002.pkl', 'wb') as savefile:
    with open(savefile_name, 'wb') as savefile:
        pickle.dump(savedata, savefile)

    #for x in range(x_len):
    #     y_values = [ lattice[x][y].type for y in range(y_len) ]
    #     print(y_values)


    #coors_list = get_rand_coors(10, 10)
    #print(coors_list)
