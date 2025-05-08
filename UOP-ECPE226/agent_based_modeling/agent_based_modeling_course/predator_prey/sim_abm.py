


import sys
import numpy as np
import pickle


sys.path.insert(1, '/mnt/c/Users/Swiftie/Desktop/Class/common_functions/')

from determine_ij import determine_ij



save_file_name = 'data/' + sys.argv[1] + '.pkl'



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

class animal_class:
    def __init__(self, animal_type):
        self.type = animal_type
        #self.energy = np.random.randint(10, 101)
        # Config A. 20 initial energy.
        self.energy = 20
        self.sex = np.random.choice( ['male', 'female'] )


def prey_eat_nutrients(patch):
    if patch.nutrient_storage > 0:
        for animal in patch.animal_list:
            if animal.type == 'prey':
                if patch.nutrient_storage > 0:
                    #if patch.nutrient_storage > 10:
                        # Config A. rand energy exchange.
                        energy_exchange = np.random.uniform(0, patch.nutrient_storage)

                        animal.energy = animal.energy + energy_exchange
                        patch.nutrient_storage = patch.nutrient_storage - energy_exchange

                        if patch.nutrient_storage == 0:
                            break

                    #else:
                    #    animal.energy = animal.energy + patch.nutrient_storage
                    #    patch.nutrient_storage = 0
                    #    break
    #return patch


def pred_eat_prey(patch):
    prey_list = [ animal for animal in patch.animal_list if animal.type == 'prey' ]
    pred_list = [ animal for animal in patch.animal_list if animal.type == 'pred' ]
    
    if len(prey_list) > 0 and len(pred_list) > 0:
        for pred in pred_list:
            if len(prey_list) > 0:
                prey_list = np.random.choice(prey_list, len(prey_list)-1, replace = False)
            pred.energy = pred.energy + 80



def kill_animals(patch):
    dead_list = []
    for animal in patch.animal_list:
        if animal.energy <= 0:
            dead_list.append(animal)

    patch.animal_list = [ animal for animal in patch.animal_list if animal not in dead_list ]

    #return patch


def reproduce_animals(patch):
    born_animal_list = []

    '''
    for animal in patch.animal_list:
        #print(animal.type)
        # Config A. Reproduce if > 30 energy.
        if animal.energy > 30:
            born_animal_list.append( animal_class(animal.type) )
            # Config A. -10 energy.
            animal.energy = animal.energy - 10
    '''

    #male_prey = [ animal for animal in patch.animal_list if animal.type == 'prey' and animal.sex == 'male' ]
    #female_prey = [ animal for animal in patch.animal_list if animal.type == 'prey' and animal.sex == 'female' ]

    not_enough_energy = []

    male_prey = []
    female_prey = []
    male_pred = []
    female_pred = []

    for animal in patch.animal_list:
        if animal.energy > 30:
            if animal.type == 'prey':
                if animal.sex == 'male':
                    male_prey.append( animal )
                elif animal.sex == 'female':
                    female_prey.append( animal )
            elif animal.type == 'pred':
                if animal.sex == 'male':
                    male_pred.append( animal )
                elif animal.sex == 'female':
                   female_pred.append( animal )
        else:
            not_enough_energy.append( animal )

    '''
    for male in male_prey:
        female = np.random.choice( female_prey )
        born_animal_list.append( animal_class( male.type ) )
        male.energy = male.energy - 10
        female.energy = female.energy - 10

    for male in male_pred:
        female = np.random.choice( female_pred )
        born_animal_list.append( animal_class( male.type) )
        male.energy = male.energy - 10
        female.energy = female.energy - 10
    '''

    if len(female_prey) == 0:
        female_prey = [None]
    if len(female_pred) == 0:
        female_pred = [None]


    for male in male_prey + male_pred:
        if male.type == 'prey':
            female = np.random.choice( female_prey )
        elif male.type == 'pred':
            female = np.random.choice( female_pred )

        if female != None:
            if female.energy > 30:
                born_animal_list.append( animal_class( male.type ) )
                male.energy = male.energy - 10
                female.energy = female.energy - 10

    patch.animal_list = not_enough_energy + male_prey + male_pred + born_animal_list

    if female_prey[0] != None:
        patch.animal_list = patch.animal_list + female_prey
    if female_pred[0] != None:
        patch.animal_list = patch.animal_list + female_pred

    #for animal in born_animal_list:
    #    patch.animal_list.append(animal)

    #for animal in patch.animal_list:
    #    print(animal)

def move_animals(lattice, i, j, x_len, y_len):
    i_up, i_down, j_left, j_right = determine_ij( i, j, x_len, y_len )

    animal_move_list = []

    for animal in lattice[i][j].animal_list:
        r = np.random.random()

        if r <= 4./5:
            # Config A. -10 energy.
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

                #print(lattice[i][j].nutrient_storage)

                #col.animal_list = pred_eat_prey( col.animal_list )
                #col.animal_list = 
                #for animal in lattice[i][j].animal_list:
                #    print(animal.energy)

    for i, row in enumerate(lattice):
        for j, patch in enumerate(row):
            ### Have patch grow more nutrients.
            # Config A. rand(0,11).
            lattice[i][j].nutrient_storage = lattice[i][j].nutrient_storage + np.random.randint(0, 11)

            if len(lattice[i][j].animal_list) > 0:
                pred_eat_prey( lattice[i][j] )

                move_animals( lattice, i, j, x_len, y_len )

                reproduce_animals( lattice[i][j] )

                kill_animals( lattice[i][j] )


    #return lattice


if __name__ == '__main__':
    x_len = 20
    y_len = 20

    sim_length = 500
    #sim_length = 1

    # Config A. init_prey_num = 20.
    init_prey_num = 100
    init_pred_num = 40

    prey_init_coors = get_rand_coors(x_len, y_len, init_prey_num)
    pred_init_coors = get_rand_coors(x_len, y_len, init_pred_num)

    lattice = [ [ patch(np.random.randint(0, 201) ) for j in range(y_len)] for i in range(x_len) ]

    # Right now, animals do not repeat in the same cell initially.
    for coor in prey_init_coors:
        lattice[ coor[0] ][ coor[1] ].animal_list.append( animal_class('prey') )
    for coor in pred_init_coors:
        lattice[ coor[0] ][ coor[1] ].animal_list.append( animal_class('pred') )

    #for i in range(x_len):
    #    for j in range(y_len):
            #print( lattice[i][j].animal_list )
    #        for agent in lattice[i][j].animal_list:
    #            print( agent.animal_type )          

    data = []

    for t in range(sim_length):
        print('step {}'.format(t))
        #lattice = update_lattice(lattice, x_len, y_len)
        update_lattice(lattice, x_len, y_len)

        prey = [ [ len( [ animal for animal in patch.animal_list if animal.type == 'prey' ] ) for patch in lattice[row] ] for row in range(x_len) ]
        pred = [ [ len( [ animal for animal in patch.animal_list if animal.type == 'pred' ] ) for patch in lattice[row] ] for row in range(x_len) ]

        nutrients = [ [ patch.nutrient_storage for patch in lattice[row] ] for row in range(x_len) ]

        data.append( [ prey, pred, nutrients] )

    #print(lattice[5][5])

    with open(save_file_name, 'wb') as savefile:
        pickle.dump(data, savefile)
