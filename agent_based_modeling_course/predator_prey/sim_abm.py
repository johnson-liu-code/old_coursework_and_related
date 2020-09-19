


import sys
import numpy as np
import pickle


sys.path.insert(1, '/mnt/c/Users/Swiftie/Desktop/Class/common_functions/')

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


class patch:
    def __init__(self, nutrient_storage):
        self.nutrient_storage = nutrient_storage
        self.animal_list = []


class animal:
    def __init__(self, animal_type, sex = None):
        self.type = animal_type
        self.energy = 100
        self.sex = sex


def prey_eat_nutrients(patch):
    if patch.nutrient_storage > 0:
        for animal in patch.animal_list:
            if animal.type == 'prey':
                if patch.nutrient_storage > 0:
                    if patch.nutrient_storage > 10:
                        animal.energy = animal.energy + 10
                        patch.nutrient_storage = patch.nutrient_storage - 10
                        if patch.nutrient_storage == 0:
                            break

                    else:
                        animal.energy = animal.energy + patch.nutrient_storage
                        patch.nutrient_storage = 0
                        break
    #return patch


def pred_eat_prey(patch):
        

    return patch


def kill_animals(patch):
    dead_list = []
    for animal in patch.animal_list:
        if animal.energy <= 0:
            dead_list.append(animal)

    patch.animal_list = [ animal for animal in patch.animal_list if animal not in dead_list ]

    #return patch


def reproduce_animals(patch):
    born_animal_list = []
    for animal in patch.animal_list:
        if animal.energy > 50:
            born_animal_list.append( animal(animal.type) )
            animal.energy = animal.energy - 50

    for animal in born_animal_list:
        patch.animal_list.append(animal)


def move_animals(lattice, i, j, x_len, y_len):
    i_up, i_down, j_left, j_right = determine_ij( i, j, x_len, y_len )

    animal_move_list = []

    for animal in lattice[i][j].animal_list:
        r = np.random.random()

        if r <= 4./5:
            animal.energy = animal.energy - 10
            animal_move_list.append( animal )
        
        ### Move north.
        if r <= 1./5:
            lattice[i_up][j].animal_list.append( animal )

        ### Move east.
        elif 1./5 < r <= 2./5:
            lattice[i][j_right].animal_list.append( animal )

        ### Move south.
        elif 2./5 < r <= 3./5:
            lattice[i_down][j].animal_list.append( animal )

        ### Move west.
        elif 3./5 < r <= 4./5:
            lattice[i][j_left].animal_list.append( animal )

        ### Otherwise, stay in place.

    lattice[i][j].animal_list = [ animal for animal in lattice[i][j].animal_list if animal not in animal_move_list ]


def update_lattice(lattice, x_len, y_len):
    #w = [ [lattice[i][j] for j, y in enumerate(range(y_len)) ] for i, x in enumerate(range(x_len)) ]

    for i, row in enumerate(lattice):
        for j, patch in enumerate(row):
            #for agent in col.animal_list:
            #    print(agent.animal_type)
            if len(lattice[i][j].animal_list) != 0:
                #print(col.animal_list)
                #lattice[i][j] = prey_eat_nutrients(lattice[i][j])
                prey_eat_nutrients(lattice[i][j])
                #lattice[i][j] = patch
                print(lattice[i][j].nutrient_storage)
                #col.animal_list = pred_eat_prey( col.animal_list )
                #col.animal_list = 
                #for animal in lattice[i][j].animal_list:
                #    print(animal.energy)

    for i, row in enumerate(lattice):
        for j, patch in enumerate(row):
            ### Have patch grow more nutrients.
            lattice[i][j].nutrient_storage = lattice[i][j].nutrient_storage + np.random.randint(0, 10)
            if len(lattice[i][j].animal_list) > 0:
                #lattice[i][j] = kill_animals(lattice[i][j])
                #lattice[i][j] = reproduce_animals(lattice[i][j])

                move_animals( lattice, i, j, x_len, y_len )

                kill_animals( lattice[i][j] )


    #return lattice


if __name__ == '__main__':
    x_len = 10
    y_len = 10

    sim_length = 100

    init_prey_num = 20
    init_pred_num = 0

    prey_init_coors = get_rand_coors(x_len, y_len, init_prey_num)
    pred_init_coors = get_rand_coors(x_len, y_len, init_pred_num)

    lattice = [ [ patch(np.random.randint(0, 101) ) for j in range(y_len)] for i in range(x_len) ]

    # Right now, animals do not repeat in the same cell initially.
    for coor in prey_init_coors:
        lattice[ coor[0] ][ coor[1] ].animal_list.append( animal('prey') )
    for coor in pred_init_coors:
        lattice[ coor[0] ][ coor[1] ].animal_list.append( animal('pred') )

    #for i in range(x_len):
    #    for j in range(y_len):
            #print( lattice[i][j].animal_list )
    #        for agent in lattice[i][j].animal_list:
    #            print( agent.animal_type )          

    data = []

    for t in range(sim_length):
        #lattice = update_lattice(lattice, x_len, y_len)
        update_lattice(lattice, x_len, y_len)

        prey = [ [ len( [ animal for animal in patch.animal_list if animal.type == 'prey' ] ) for patch in lattice[row] ] for row in range(x_len) ]
        #print(v)
        nutrients = [ [ patch.nutrient_storage for patch in lattice[row] ] for row in range(x_len) ]

        data.append( [ prey, nutrients] )

    #print(lattice[5][5])

    with open('test_01.pkl', 'wb') as savefile:
        pickle.dump(data, savefile)
