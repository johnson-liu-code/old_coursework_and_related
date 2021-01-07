


import sys
import numpy as np
import random
import pickle


sys.path.insert(1, '/mnt/c/Users/Swiftie/Desktop/Class/common_functions/')

from determine_ij import determine_ij



save_file_name = sys.argv[1] + '.pkl'



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
        self.organism_list = []


class organism_class:
    def __init__(self, organism_type):
        self.type = organism_type
        #self.energy = np.random.randint(10, 101)
        # Config A. 20 initial energy.
        self.energy = 20

prey_species = ['prey_1', 'prey_2', 'prey_3']

def prey_eat_nutrients(patch):
    if patch.nutrient_storage > 0:
        for organism in patch.organism_list:
            if organism.type in prey_species:
                if patch.nutrient_storage > 0:
                    #if patch.nutrient_storage > 10:
                        # Config A. rand energy exchange.
                        energy_exchange = np.random.uniform(0, patch.nutrient_storage)

                        organism.energy = organism.energy + energy_exchange
                        patch.nutrient_storage = patch.nutrient_storage - energy_exchange

                        if patch.nutrient_storage == 0:
                            break

                    #else:
                    #    organism.energy = organism.energy + patch.nutrient_storage
                    #    patch.nutrient_storage = 0
                    #    break
    #return patch


def pred_eat_prey(patch):
    prey_list = [ organism for organism in patch.organism_list if organism.type in prey_species ]
    pred_list = [ organism for organism in patch.organism_list if organism.type == 'pred' ]
    
    if len(prey_list) > 0 and len(pred_list) > 0:
        for pred in pred_list:
            if len(prey_list) > 0:
                #prey_list = np.random.choice(prey_list, len(prey_list)-1, replace = False)
                org = prey_list.pop( random.randrange( len( prey_list ) ) )
            if org.type == 'prey_1':
                pred.energy = pred.energy + 100
            elif org.type == 'prey_2':
                pred.energy = pred.energy + 80
            elif org.type == 'prey_3':
                pred.energy = pred.energy + 60

    patch.organism_list = prey_list + pred_list



def kill_organisms(patch):
    dead_list = []
    for organism in patch.organism_list:
        if organism.energy <= 0:
            dead_list.append(organism)

    patch.organism_list = [ organism for organism in patch.organism_list if organism not in dead_list ]

    #return patch


def reproduce_organisms(patch):
    born_organism_list = []
    for organism in patch.organism_list:
        #print(organism.type)
        # Config A. Reproduce if > 30 energy.
        if organism.energy > 30:
            born_organism_list.append( organism_class(organism.type) )
            # Config A. -10 energy.
            organism.energy = organism.energy - 10

    for organism in born_organism_list:
        patch.organism_list.append(organism)


def move_organisms(lattice, i, j, x_len, y_len):
    i_up, i_down, j_left, j_right = determine_ij( i, j, x_len, y_len )

    organism_move_list = []

    for organism in lattice[i][j].organism_list:
        r = np.random.random()

        if r <= 4./5:
            # Config A. -10 energy.
            organism.energy = organism.energy - 10
            organism_move_list.append( organism )
        
        ### Move north.
        if r <= 1./5:
            lattice[i_up][j].organism_list.append( organism )

        ### Move east.
        elif 1./5 < r <= 2./5:
            lattice[i][j_right].organism_list.append( organism )

        ### Move south.
        elif 2./5 < r <= 3./5:
            lattice[i_down][j].organism_list.append( organism )

        ### Move west.
        elif 3./5 < r <= 4./5:
            lattice[i][j_left].organism_list.append( organism )

        ### Otherwise, stay in place.

    lattice[i][j].organism_list = [ organism for organism in lattice[i][j].organism_list if organism not in organism_move_list ]


def update_lattice(lattice, x_len, y_len):
    #w = [ [lattice[i][j] for j, y in enumerate(range(y_len)) ] for i, x in enumerate(range(x_len)) ]

    for i, row in enumerate(lattice):
        for j, patch in enumerate(row):
            #for agent in col.organism_list:
            #    print(agent.organism_type)
            if len(lattice[i][j].organism_list) != 0:
                #print(col.organism_list)
                #lattice[i][j] = prey_eat_nutrients(lattice[i][j])
                prey_eat_nutrients(lattice[i][j])
                #lattice[i][j] = patch

                #print(lattice[i][j].nutrient_storage)

                #col.organism_list = pred_eat_prey( col.organism_list )
                #col.organism_list = 
                #for organism in lattice[i][j].organism_list:
                #    print(organism.energy)

    for i, row in enumerate(lattice):
        for j, patch in enumerate(row):
            ### Have patch grow more nutrients.
            # Config A. rand(0,11).
            lattice[i][j].nutrient_storage = lattice[i][j].nutrient_storage + np.random.randint(0, 11)

            if len(lattice[i][j].organism_list) > 0:
                reproduce_organisms( lattice[i][j] )

                move_organisms( lattice, i, j, x_len, y_len )

                pred_eat_prey( lattice[i][j] )

                kill_organisms( lattice[i][j] )


    #return lattice


if __name__ == '__main__':
    x_len = 100
    y_len = 100

    sim_length = 300
    #sim_length = 1

    # Config A. init_prey_num = 20.
    init_prey_num = 200
    init_pred_num = 400

    prey_init_coors_1 = get_rand_coors(x_len, y_len, init_prey_num)
    prey_init_coors_2 = get_rand_coors(x_len, y_len, init_prey_num)
    prey_init_coors_2 = get_rand_coors(x_len, y_len, init_prey_num)

    pred_init_coors = get_rand_coors(x_len, y_len, init_pred_num)

    lattice = [ [ patch(np.random.randint(0, 101) ) for j in range(y_len) ] for i in range(x_len) ]

    # Right now, organisms do not repeat in the same cell initially.
    for coor in prey_init_coors_1:
        lattice[ coor[0] ][ coor[1] ].organism_list.append( organism_class('prey_1') )

    for coor in prey_init_coors_2:
        lattice[ coor[0] ][ coor[1] ].organism_list.append( organism_class('prey_2') )

    for coor in prey_init_coors_2:
        lattice[ coor[0] ][ coor[1] ].organism_list.append( organism_class('prey_3') )

    for coor in pred_init_coors:
        lattice[ coor[0] ][ coor[1] ].organism_list.append( organism_class('pred') )

    #for i in range(x_len):
    #    for j in range(y_len):
            #print( lattice[i][j].organism_list )
    #        for agent in lattice[i][j].organism_list:
    #            print( agent.organism_type )          

    data = []

    for t in range(sim_length):
        print('step {}'.format(t))
        #lattice = update_lattice(lattice, x_len, y_len)
        update_lattice(lattice, x_len, y_len)

        #prey_1 = [ [ len( [ organism for organism in patch.organism_list if organism.type == 'prey_1' ] ) for patch in lattice[row] ] for row in range(x_len) ]

        prey_1 = [ [ 0 for j in range(y_len) ] for i in range(x_len) ]
        prey_2 = [ [ 0 for j in range(y_len) ] for i in range(x_len) ]
        prey_3 = [ [ 0 for j in range(y_len) ] for i in range(x_len) ]
        nutrients = [ [ 0 for j in range(y_len) ] for i in range(x_len) ]
        pred = [ [ 0 for j in range(y_len) ] for i in range(x_len) ]

        ###
        #pred = [ [ len( [ organism for organism in patch.organism_list if organism.type == 'pred' ] ) for patch in lattice[row] ] for row in range(x_len) ]
        ###
        #nutrients = [ [ patch.nutrient_storage for patch in lattice[row] ] for row in range(x_len) ]

        for i in range(x_len):
            for j in range(y_len):
                prey_1[i][j] = len( [organism for organism in lattice[i][j].organism_list if organism.type == 'prey_1'] )
                prey_2[i][j] = len( [organism for organism in lattice[i][j].organism_list if organism.type == 'prey_2'] )
                prey_3[i][j] = len( [organism for organism in lattice[i][j].organism_list if organism.type == 'prey_3'] )
                nutrients[i][j] = lattice[i][j].nutrient_storage
                pred[i][j] = len( [organism for organism in lattice[i][j].organism_list if organism.type == 'pred'] )

        #data.append( [ prey, pred, nutrients] )
        data.append( [prey_1, prey_2, prey_3, nutrients, pred] )

    #print(lattice[5][5])

    with open(save_file_name, 'wb') as savefile:
        pickle.dump(data, savefile)
