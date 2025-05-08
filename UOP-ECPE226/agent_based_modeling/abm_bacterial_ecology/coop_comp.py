


import sys
import numpy as np
import random
import copy
import pickle


# sys.path.insert(1, '/mnt/c/Users/Swiftie/Desktop/Class/common_functions/')

# Function get coordinates of neighbors on the lattice.
from determine_ij import determine_ij
# Function to return random coordinates.
from get_rand_coors import get_rand_coors

# Name of file to save the data to.
save_file_name = sys.argv[1] + '.pkl'


# Individuals are represented by an organism_class object. There are multiple objects stored in
#   each node on the lattice (the nodes themselves are objects).
class organism_class:
    def __init__(self, starting_energy):
        # Attribute to remember whether the organism has moved or not during an iteration in the
        #   simulation.
        self.moved = False
        # The amount of energy that the organism starts out with when initializing the lattice.
        #   How this value is determined can be changed as a design parameter.
        self.energy = starting_energy

        # Ability to produce enzyme_A to break down nutrient_A.
        self.enzyme_A = True
        # Ability to take in nutrient_A without the need for it to be broken down by enzyme_A.
        self.nutrient_A = False

        # Ability to produce bacteriotoxin_A (which kills a non-resistant individual).
        self.bacteriotoxin_A = False
        # Ability to produce antibacteriotoxin_A which breaks down bacteriotoxin_A.
        self.antibacteriotoxin_A = False
        # Ability to resist bacteriotoxin_A.
        self.resistant_A = False

    # Set the value of an attribute. Create the attribute if it doesn't already exist
    #   within the object.
    def set_attribute(self, attribute, value):
        setattr(self, attribute, value)

    # Get the value of an attribute.
    def get_attribute_value(self, attribute):
        return getattr(self, attribute)

    # Delete the value of an attribute.
    def del_attribute(self, attribute):
        delatt(self, x)

    # Determine whether or not the object has a particular attribute.
    def get_has_attribute(self, attribute):
        return hasattr(self, attribute)

    # Return a list of all of the attributes.
    @property
    def get_attributes(self):
        return self.__dict__

    # Return a list of all of the nutrient types that the organism can consume without the
    #   need for the corresponding enzyme to be present.
    def get_nutrient_consumption_types(self):
        attributes = self.get_attributes
        nutrient_types = [attribute for attribute in attributes if 'nutrient' in attribute]
        return nutrient_types

    # Return a list of all of the enzymes that the organism can produce.
    def get_enzyme_production_types(self):
        attributes = self.get_attributes
        enzyme_types = [attribute for attribute in attributes if 'enzyme' in attribute]
        return enzyme_types

    # Return a list of all of the bacteriotoxins that the organism can produce.
    def get_bacteriotoxin_production_types(self):
        attributes = self.get_attributes
        bacteriotoxin_types = [attribute for attribute in attributes if 'bacteriotoxin' in attribute and 'anti' not in attribute]
        return bacteriotoxin_types

    # Return a list of all of the antibacteriotoxins that the organism can produce.
    def get_antibacteriotoxin_production_types(self):
        attributes = self.get_attributes
        antibacteriotoxin_types = [attribute for attribute in attributes if 'antibacteriotoxin' in attribute]
        return antibacteriotoxin_types

    # Return a list of all of the resistances that the organism has (the organism is resistant to the
    #   corresponding bacteriotoxin).
    def get_resistance_types(self):
        attributes = self.get_attributes
        resistance_types = [attribute for attribute in attributes if 'resistant' in attribute]
        return resistance_types

    def resistance_upkeep(self):
        attributes = self.get_attributes
        resistance_types = [attribute for attribute in attributes if 'resistant' in attribute]
        for resistance_type in resistance_types:
            self.energy = self.energy - resistance_upkeep_cost

    def existance_upkeep(self):
        self.energy = self.energy - existance_upkeep_cost

    # Produce all of the particles that the organism can produce while reducing the organism's energy.
    #   The organism will not continue to produce particles if it does not have enough energy.
    def produce_particles(self, particle_type):
        produced_particle_list = []
        # Get a list of all of the organism's attributes.
        attributes = self.get_attributes
        # Get a list of all of the attributes that represent producable particles.
        available_particles = [ attribute for attribute in attributes if particle_type in attribute and attributes[attribute] == True ]
        # Shuffle the list of producable particles.
        np.random.shuffle(available_particles)
        # Iterate over the producable particles.
        for particle in available_particles:
            # Randomly choose the amount of energy it takes to produce the specific particle.
            #   This can be changed as a design parameter.
            # energy_used = np.random.randint(1, 11)
            # energy_used = energy_consumed_for_producing_particles
            if 'bacteriotoxin' in particle and 'anti' not in particle:
                energy_used = energy_consumed_for_producing_bacteriotoxin
            elif 'anti' in particle:
                energy_used = energy_consumed_for_producing_antibacteriotoxin
            elif 'enzyme' in particle:
                energy_used = energy_consumed_for_producing_enzyme

            # If the energy required to make the particle is greater than the amount of energy
            #   that the organism has, do not produce the particle.
            if energy_used > self.energy:
                break
            # Otherwise, add the particle to the list of produced particles and reduce the organism's
            #   energy reserves accordingly.
            else:
                produced_particle_list.append(particle)
                self.energy = self.energy - energy_used

        # Return a list of all of the particles that are produced.
        return produced_particle_list

# Object to represent a node on the lattice. Each patch contains the amounts of each of the nutrient and
#   particle types as well as a list of the individuals that are alive on the specific node.
class patch_class:
    def __init__(self, nutrient_A, init_num_organisms, starting_energy):
        # Start out with some amount of nutrient_A.
        self.nutrient_A = nutrient_A
        # Start out with no enzyme_A, bacteriotoxin_A, and antibacteriotoxin_A.
        self.enzyme_A = 0
        self.bacteriotoxin_A = 0
        self.antibacteriotoxin_A = 0

        # Generate the initial list of organisms.
        self.organism_list = [ organism_class(starting_energy) for org in range(init_num_organisms) ]

    # Set the value of an attribute. Create the attribute if it doesn't already exist
    #   within the object.
    def set_attribute(self, attribute, value):
        setattr(self, attribute, value)

    # Get the value of an attribute.
    def get_attribute_value(self, attribute):
        return getattr(self, attribute)

    # Delete the value of an attribute.
    def del_attribute(self, attribute):
        delatt(self, x)

    # Determine whether or not the object has a particular attribute.
    def get_has_attribute(self, attribute):
        return hasattr(self, attribute)

    # Return a list of all of the attributes.
    @property
    def get_attributes(self):
        return self.__dict__

    # Return the sum of the amounts of each of the nutrient types on the node.
    def get_total_amount_of_nutrients(self):
        class_variables = self.get_attributes
        total_amount_of_nutrients = sum( [ class_variables[var] for var in class_variables if 'nutrient' in var] )
        return total_amount_of_nutrients

    # Return the sum of the amounts of each of the enzyme types on the node.
    def get_total_amount_of_enzymes(self):
        class_variables = self.get_attributes
        total_amount_of_enzymes = sum( [ class_variables[var] for var in class_variables if 'enzyme' in var] )
        return total_amount_of_enzymes

    # Return the sum of the amounts of each of the bacteriotoxin types on the node.
    def get_total_amount_of_bacteriotoxins(self):
        class_variables = self.get_attributes
        total_amount_of_bacteriotoxin = sum( [ class_variables[var] for var in class_variables if 'bacteriotoxin' in var and 'anti' not in var] )
        return total_amount_of_bacteriotoxin

    # Return the sum of the amounts of each of the antibacteriotoxin types on the node.
    def get_total_amount_of_antibacteriotoxins(self):
        class_variables = self.get_attributes
        total_amount_of_antibacteriotoxin = sum( [ class_variables[var] for var in class_variables if 'antibacteriotoxin' in var] )
        return total_amount_of_antibacteriotoxin

    # Return the total number of particles present on the node.
    def get_total_number_of_particles(self):
        total_amount_of_enzymes = self.get_total_amount_of_enzymes()
        total_amount_of_bacteriotoxins = self.get_total_amount_of_bacteriotoxins()
        total_amount_of_antibacteriotoxins = self.get_total_amount_of_antibacteriotoxins()
        total_amount_of_particles = total_amount_of_enzymes + total_amount_of_bacteriotoxins + total_amount_of_antibacteriotoxins
        return total_amount_of_particles

    # Return a list of all of the nutrient types on the node.
    def get_nutrient_types(self):
        nutrient_types = [ attribute for attribute in self.get_attributes if 'nutrient' in attribute ]
        return nutrient_types

    # Return a list of all of the enzyme types on the node.
    def get_enzyme_types(self):
        enzyme_types = [ attribute for attribute in self.get_attributes if 'enzyme' in attribute ]
        return enzyme_types

    # Return a list of all of the bacteriotoxin types on the node.
    def get_bacteriotoxin_types(self):
        bacteriotoxin_types = [ attribute for attribute in self.get_attributes if 'bacteriotoxin' in attribute and 'anti' not in attribute ]
        return bacteriotoxin_types

    # Return a list of all of the antibacteriotoxin types on the node.
    def get_antibacteriotoxin_types(self):
        antibacteriotoxin_types = [ attribute for attribute in self.get_attributes if 'antibacteriotoxin' in attribute ]
        return antibacteriotoxin_types

    # Increase the amount of each nutrient type on the node.
    def grow_nutrients(self):
        nutrient_types = self.get_nutrient_types()
        for nutrient_type in nutrient_types:
            self.set_attribute( nutrient_type, self.get_attribute_value(nutrient_type) + np.random.randint(0, 11) )

    # Reduce the amount of a nutrient type on the node (through consumption by an organism).
    def consume_nutrient(self, nutrient, amount_consumed):
        new_nutrient_amount = self.get_attribute_value(nutrient) - amount_consumed
        self.set_attribute(nutrient, new_nutrient_amount)

    # Return the number of organisms on the node.
    def get_number_of_organisms(self):
        return len(self.organism_list)


# Operation for the diffusion of particles from a central node to neighboring nodes.
def diffuse_particles():
    for i in range(x_len):
        for j in range(y_len):
            # Get the coordinates of the neighboring nodes. (The lattice is periodic: a torus).
            i_up, i_down, j_left, j_right = determine_ij( i, j, x_len, y_len )

            # Get the amount of particles in the central node and the neighboring nodes.
            particles_in_place = max( lattice[i][j].get_total_number_of_particles(), 1 )
            particles_up = max( lattice[i_up][j].get_total_number_of_particles(), 1 )
            particles_down = max( lattice[i_down][j].get_total_number_of_particles(), 1 )
            particles_left = max( lattice[i][j_left].get_total_number_of_particles(), 1 )
            particles_right = max( lattice[i][j_right].get_total_number_of_particles(), 1 )

            # Compute the probabilities for a particle of staying on the central node or of moving
            #   to a neighboring node. The greater the number of particles already present in a node,
            #   the lower the probability of a particle moving into that node.
            y = particles_in_place + particles_up + particles_down + particles_left + particles_right

            a1 = y/particles_in_place
            a2 = y/particles_up
            a3 = y/particles_down
            a4 = y/particles_left
            a5 = y/particles_right

            z = a1 + a2 + a3 + a4 + a5

            p1 = a1/z
            p2 = a2/z
            p3 = a3/z
            p4 = a4/z
            p5 = a5/z

            particle_types = ['enzyme', 'bacteriotoxin', 'antibacteriotoxin']
            attributes = lattice[i][j].get_attributes

            # Iterate over all of the particle types.
            for particle_type in particle_types:
                particles = [ particle for particle in attributes if particle_type in particle ]

                # Iterate over all of the particles of a particular type on the node.
                for particle in particles:
                    if lattice[i][j].get_attribute_value(particle) > 0:
                        # Generate a random number in the range (0, 1).
                        r = np.random.random()
                        # Determine where the particle moves to, if it does move.
                        if r > p1:
                            lattice[i][j].set_attribute(particle, lattice[i][j].get_attribute_value(particle) - 1)
                            if p1 <= r < p1+p2:
                                lattice[i_up][j].set_attribute(particle, lattice[i_up][j].get_attribute_value(particle) + 1)
                            elif p1+p2 <= r < p1+p2+p3:
                                lattice[i_down][j].set_attribute(particle, lattice[i_down][j].get_attribute_value(particle) + 1)
                            elif p1+p2+p3 <= r < p1+p2+p3+p4:
                                lattice[i][j_left].set_attribute(particle, lattice[i][j_left].get_attribute_value(particle) + 1)
                            elif p1+p2+p3+p4 <= r <= 1:
                                lattice[i][j_right].set_attribute(particle, lattice[i][j_right].get_attribute_value(particle) + 1)


# Kill off all of the organisms that do not have enough energy to survive.
def kill_organisms(patch):
    patch.organism_list = [ organism for organism in patch.organism_list if organism.energy > 0 ]


def existance_upkeep(patch):
    for organism in patch.organism_list:
        organism.existance_upkeep()


def resistance_upkeep(patch):
    for organism in patch.organism_list:
        organism.resistance_upkeep()


# Destroy bacteriotoxin within a node with the corresponding antibacteriotoxin.
def destroy_bacteriotoxin(patch):
    # Get a list of all of the bacteriotoxin types in the node.
    bacteriotoxin_list = patch.get_bacteriotoxin_types()
    # Iterate over each bacteriotoxin type.
    for bacteriotoxin in bacteriotoxin_list:
        # Get the corresponding antibacteriotoxin type.
        antibacteriotoxin = get_corresponding_particle(bacteriotoxin)
        # Check to see if the node contains the corresponding antibacteriotoxin type.
        if patch.get_has_attribute(antibacteriotoxin) == True:
            # Get the amount of the bacteriotoxin present on the node.
            amount_of_bacteriotoxin = patch.get_attribute_value(bacteriotoxin)
            # Get the amount of the antibacteriotoxin on the node.
            amount_of_antibacteriotoxin = patch.get_attribute_value(antibacteriotoxin)
            # Reduce the amount of both the bacteriotoxin and the antibacteriotoxin until there is
            #   no more of one of them (the antibacteriotoxin is destroying the bacteriotoxin).
            if amount_of_bacteriotoxin > amount_of_antibacteriotoxin:
                new_bacteriotoxin_amount = amount_of_bacteriotoxin - amount_of_antibacteriotoxin
                new_antibacteriotoxin_amount = 0
            else:
                new_antibacteriotoxin_amount = amount_of_antibacteriotoxin - amount_of_bacteriotoxin
                new_bacteriotoxin_amount = 0

            # Update the new bacteriotoxin and antibacteriotoxin quantities on the node.
            patch.set_attribute(bacteriotoxin, new_bacteriotoxin_amount)
            patch.set_attribute(antibacteriotoxin, new_antibacteriotoxin_amount)


# Return the resistance type corresponding to the given bacteriotoxin type.
def get_corresponding_resistance(bacteriotoxin_type):
    name_ID = bacteriotoxin_type.split('_')[-1]
    resistance_type = 'resistant_' + name_ID
    return resistance_type


# Destroy organisms with bacteriotoxin.
def bacteriotoxin_destroy_cells(patch):
    # A list to store of the organisms that get killed off.
    dead_organism_list = []
    # print('stuck here 13.1')
    # Get the list of all of the bacteriotoxin types on the node.
    bacteriotoxin_list = patch.get_bacteriotoxin_types()
    # print('stuck here 13.2')
    # Shuffle the ordering of the bacteriotoxin in the list.
    np.random.shuffle(bacteriotoxin_list)
    # print('stuck here 13.3')
    # Iterate over each of the bacteriotoxin.
    for bacteriotoxin in bacteriotoxin_list:
        # print('stuck here 13.4')
        # Get the corresponding resistance type.
        resistance_type = get_corresponding_resistance(bacteriotoxin)
        # print('stuck here 13.5')
        # Get the amount of the specific bacteriotoxin in the node.
        amount_of_bacteriotoxin = patch.get_attribute_value(bacteriotoxin)
        # print('stuck here 13.6')
        # Shuffle the node's organism list.
        np.random.shuffle(patch.organism_list)
        # print('stuck here 13.7')
        # Iterate over each of the organisms.
        if amount_of_bacteriotoxin >= amount_of_bacteriotoxin_needed_to_kill:
            for organism in patch.organism_list:
                # print('stuck here 13.8')
                # print('stuck here 13.9')
                # If the organism is not resistant to the bacteriotoxin, kill the organism
                #   and reduce the amount of the bacteriotoxin present by a specific amount.
                if resistance_type not in organism.get_resistance_types():
                    # print('stuck here 13.10')
                    dead_organism_list.append(organism)
                    amount_of_bacteriotoxin -= amount_of_bacteriotoxin_needed_to_kill
                if amount_of_bacteriotoxin < amount_of_bacteriotoxin_needed_to_kill:
                    break

    # print('stuck here 13.11')
    # Update the node's organism list, throwing away all of the organisms that were killed.
    patch.organism_list = [ org for org in patch.organism_list if org not in dead_organism_list ]


# Have the organisms in a node produce particles.
def organisms_produce_particles(patch, particle_type):
    # Iterate over each of the organisms within the node.
    for organism in patch.organism_list:
        # Get a list of the particles that the organism can produce.
        produced_particles = organism.produce_particles(particle_type)

        # Iterate over each of the particle types that can be produced.
        for particle in produced_particles:
            # If the node does not contain any of the specific particle, create an attribute for
            #   the node to store the particle. Set the amount of the particle present to one (or
            #   some other amount).
            if patch.get_has_attribute(particle) == False:
                if 'bacteriotoxin' in particle and 'anti' not in particle:
                    patch.set_attribute(particle, new_bacteriotoxin_particle_amount)
                elif 'anti' in particle:
                    patch.set_attribute(particle, new_antibacteriotoxin_particle_amount)
                elif 'enzyme' in particle:
                    patch.set_attribute(particle, new_enzyme_particle_amount)
            # If the node already has the specific attribute, add on one particle (or some other
            #   amount) to the attribute value.
            else:
                particle_present = patch.get_attribute_value(particle)
                if 'bacteriotoxin' in particle and 'anti' not in particle:
                    new_particle_amount = particle_present + additional_bacteriotoxin_particle_amount
                elif 'anti' in particle:
                    new_particle_amount = particle_present + additional_antibacteriotoxin_particle_amount
                elif 'enzyme' in particle:
                    new_particle_amount = particle_present + additional_enzyme_particle_amount
                patch.set_attribute(particle, new_particle_amount)


# Mutate the organisms on a node.
def mutate_organisms(patch, enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index):
    # A list to store the new gene types that organisms can mutate into existance.
    new_particle_type_list = []

    # Iterate over the organisms on the node.
    for organism in patch.organism_list:
        # Generate random numbers in the range (0, 1).
        r = np.random.random()
        rr = np.random.random()
        rrr = np.random.random()
        r_bacteriotoxin = np.random.random()
        r_anti = np.random.random()
        r_resistant = np.random.random()

        # How the mutation probabilities are chosen and handled are taken as design
        #   parameters/decisions.

        # If r is less than or equal to the mutation probability, perform mutations
        #   on the organism.
        if r <= mutation_probability:
            # If rr is less than or equal to the mutate existing genes probability,
            #   perform mutations on the genes that already exist for the organism.
            if rr <= mutate_existing_probability:
                if enzyme_nutrient_naming_index < max_ID_enzyme_nutrient:
                    # If rrr is less than or equal to the consume nutrient mutation probability,
                    #   perform mutations on the ability of the organism to consume a nutrient
                    #   without the need of the corresponding enzyme to be present.
                    if rrr <= consume_nutrient_mutation_probability:
                        # Get a list of the nutrient types that the organism might or might not
                        #   be able to consume without enzymes present.
                        nutrients_consumption_list = organism.get_nutrient_consumption_types()
                        # Randomly select a nutrient consumption gene to mutate.
                        gene_to_mutate = np.random.choice(nutrients_consumption_list)
                    else:
                        # Get a list of the enzyme types that the organism might or might not
                        #   be able to produce.
                        enzyme_production_list = organism.get_enzyme_production_types()
                        # Randomly select an enzyme production gene to mutate.
                        gene_to_mutate = np.random.choice(enzyme_production_list)

                    # Get the truth value of the organism's gene and flip it.
                    value = organism.get_attribute_value(gene_to_mutate)
                    if value == True:
                        new_value = False
                    else:
                        new_value = True
                    # Set the new truth value.
                    organism.set_attribute(gene_to_mutate, new_value)

                if bacteriotoxin_anti_naming_index < max_ID_anti_bacteriotoxin:
                    # Check to see if a mutation on an existing bacteriotoxin gene occurs.
                    if r_bacteriotoxin <= bacteriotoxin_mutation_probability:
                        # Get the list of all of the bacteriotoxin genes present in the organism.
                        bacteriotoxin_production_list = organism.get_bacteriotoxin_production_types()
                        # Randomly choose one of the bacteriotoxin types to mutate.
                        gene_to_mutate = np.random.choice(bacteriotoxin_production_list)

                        # Get the truth value of the organism's gene and flip it.
                        value = organism.get_attribute_value(gene_to_mutate)
                        if value == True:
                            new_value = False
                        else:
                            new_value = True
                        # Set the new truth value.
                        organism.set_attribute(gene_to_mutate, new_value)
                        resistance_gene = get_corresponding_resistance(gene_to_mutate)
                        organism.set_attribute(resistance_gene, True)

                    # Check to see if a mutation on an existing antibacteriotoxin gene occurs.
                    if r_anti <= anti_mutation_probability:
                        # Get the list of all of the antibacteriotoxin genes present in the organism.
                        antibacteriotoxin_production_list = organism.get_antibacteriotoxin_production_types()
                        # Randomly choose one of the antibacteriotoxin types to mutate.
                        gene_to_mutate = np.random.choice(antibacteriotoxin_production_list)

                        # Get the truth value of the organism's gene and flip it.
                        value = organism.get_attribute_value(gene_to_mutate)
                        if value == True:
                            new_value = False
                        else:
                            new_value = True
                        # Set the new truth value.
                        organism.set_attribute(gene_to_mutate, new_value)

                    # Check to see if a mutation on an existing resistance gene occurs.
                    if r_resistant <= resistance_mutation_probability:
                        # Get the list of all of the resistance genes present in the organism.
                        resistance_list = organism.get_resistance_types()
                        # Randomly choose one of the resistance types to mutate.
                        gene_to_mutate = np.random.choice(resistance_list)

                        # Get the truth value of the organism's gene and flip it.
                        value = organism.get_attribute_value(gene_to_mutate)
                        if value == True:
                            new_value = False
                        else:
                            new_value = True
                        # Set the new truth value.
                        organism.set_attribute(gene_to_mutate, new_value)

            else:
                # Get the next available particle naming ID for naming nutrients and enzymes.
                new_name_ID_1 = naming_list[enzyme_nutrient_naming_index]
                # Increment the naming index.
                enzyme_nutrient_naming_index += 1

                if enzyme_nutrient_naming_index < max_ID_enzyme_nutrient:
                    # Check to see whether the nutrient gene or the enzyme gene is mutated.
                    if rrr <= consume_nutrient_mutation_probability:
                        gene_to_add_name = 'nutrient_' + new_name_ID_1
                    else:
                        gene_to_add_name = 'enzyme_' + new_name_ID_1

                    # Get the corresponding particle type.
                    corresponding_particle_type = get_corresponding_particle(gene_to_add_name)

                    # Add the new gene attributes to the organism.
                    organism.set_attribute(gene_to_add_name, True)
                    organism.set_attribute(corresponding_particle_type, False)

                    # Add the new genes to the list of new genes.
                    new_particle_type_list.append(gene_to_add_name)
                    new_particle_type_list.append(corresponding_particle_type)

                if bacteriotoxin_anti_naming_index < max_ID_anti_bacteriotoxin:
                    # Check to see if a new bacteriotoxin gene mutates into existance.
                    if r_bacteriotoxin <= bacteriotoxin_mutation_probability:
                        # Get the next available particle naming ID for naming bacteriotoxins
                        #   antibacteriotoxins.
                        new_name_ID_2 = naming_list[bacteriotoxin_anti_naming_index]
                        # Increment the naming index.
                        bacteriotoxin_anti_naming_index += 1

                        # Name the new bacteriotoxin, antibacteriotoxin, and resistance genes.
                        bacteriotoxin_gene_to_add_name = 'bacteriotoxin_' + new_name_ID_2
                        anti_gene_to_add_name = 'antibacteriotoxin_' + new_name_ID_2
                        resistance_gene_to_add_name = 'resistant_' + new_name_ID_2

                        # Add the new gene attributes to the organism.
                        organism.set_attribute(bacteriotoxin_gene_to_add_name, True)
                        organism.set_attribute(anti_gene_to_add_name, False)
                        organism.set_attribute(resistance_gene_to_add_name, True)

                        # Add the new genes to the list of new genes.
                        new_particle_type_list.append(bacteriotoxin_gene_to_add_name)
                        new_particle_type_list.append(anti_gene_to_add_name)
                        new_particle_type_list.append(resistance_gene_to_add_name)

                    # Same as previous block.
                    if r_anti <= anti_mutation_probability:
                        new_name_ID_2 = naming_list[bacteriotoxin_anti_naming_index]
                        bacteriotoxin_anti_naming_index += 1

                        bacteriotoxin_gene_to_add_name = 'bacteriotoxin_' + new_name_ID_2
                        anti_gene_to_add_name = 'antibacteriotoxin_' + new_name_ID_2
                        resistance_gene_to_add_name = 'resistant_' + new_name_ID_2

                        organism.set_attribute(bacteriotoxin_gene_to_add_name, False)
                        organism.set_attribute(anti_gene_to_add_name, True)
                        organism.set_attribute(resistance_gene_to_add_name, False)

                        new_particle_type_list.append(bacteriotoxin_gene_to_add_name)
                        new_particle_type_list.append(anti_gene_to_add_name)
                        new_particle_type_list.append(resistance_gene_to_add_name)

                    # Same as previous block.
                    if r_resistant <= resistance_mutation_probability:
                        new_name_ID_2 = naming_list[bacteriotoxin_anti_naming_index]
                        bacteriotoxin_anti_naming_index += 1

                        bacteriotoxin_gene_to_add_name = 'bacteriotoxin_' + new_name_ID_2
                        anti_gene_to_add_name = 'antibacteriotoxin_' + new_name_ID_2
                        resistance_gene_to_add_name = 'resistant_' + new_name_ID_2

                        organism.set_attribute(bacteriotoxin_gene_to_add_name, False)
                        organism.set_attribute(anti_gene_to_add_name, False)
                        organism.set_attribute(resistance_gene_to_add_name, True)

                        new_particle_type_list.append(bacteriotoxin_gene_to_add_name)
                        new_particle_type_list.append(anti_gene_to_add_name)
                        new_particle_type_list.append(resistance_gene_to_add_name)

    # Return the naming indices and the list of new genes.
    return enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index, new_particle_type_list


# Add new genes to individuals.
def add_genes_to_individuals(patch, new_genes):
    for organism in patch.organism_list:
        for gene in new_genes:
            # print(gene)
            if organism.get_has_attribute(gene) == False:
                organism.set_attribute(gene, False)


# Add new particle types to a node.
def add_particle_types_to_patch(patch, new_particle_types):
    # Iterate over each particle in the new particle type list.
    for particle in new_particle_types:
        # This part of the code is messy. There should be no "resistant" type particles
        #   (resistance should be a gene only and not expressed as a particle in the
        #   simulation). But elsewhere in the code, genes with "resistance" in the name
        #   are passed through functions and treated as "particles". Should make the code
        #   more consistent.
        if 'resistant' not in particle:
            # If the node does not have an attribute to represent the particle, add it
            #   and its corresponding particle as attributes to the node.
            if patch.get_has_attribute(particle) == False:
                corresponding_particle_type = get_corresponding_particle(particle)

                if 'nutrient' in particle:
                    patch.set_attribute(particle, init_patch_nutrients)
                    patch.set_attribute(corresponding_particle_type, 0)
                elif 'enzyme' in particle:
                    patch.set_attribute(particle, 0)
                    patch.set_attribute(corresponding_particle_type, init_patch_nutrients)

                elif 'bacteriotoxin' in particle:
                    patch.set_attribute(particle, 0)
                    patch.set_attribute(corresponding_particle_type, 0)


# Have organisms reproduce within the node. The way that the organism's energy is used/
#   passed down as it reproduces, as well as the threshold for reproducing can be
#   changed as a design decision.
def reproduce_organisms(patch):
    # A list to keep track of new organisms.
    born_organism_list = []
    # Iterate over each organism in the node.
    for organism in patch.organism_list:
        # Check to see if the organism has enough energy to perform binary fission.
        if organism.energy >= energy_threshold_for_reproduction:
            # When dividing, cut the organism's energy in half (each daugther cell
            #   gets half of the energy from the parent cell).
            organism.energy -= energy_consumed_for_reproduction
            organism.energy = int( np.floor( organism.energy / 2 ) )
            new_organism = organism_class(organism.energy)

            # Get the attributes of the original organism.
            attributes = organism.get_attributes
            # Iterate over all of the attributes.
            for attribute in attributes:
                # Get the value for each attribute.
                value = organism.get_attribute_value(attribute)
                # Add these attributes and their values to the new organism.
                new_organism.set_attribute(attribute, value)

            # Add the new organism to the new organism list.
            born_organism_list.append( new_organism )

    # Add all of the new organisms to the node's organism list.
    patch.organism_list += born_organism_list


# Return the corresponding particle type of the given particle.
def get_corresponding_particle(particle_type):
    # Get the name ID of the given particle.
    name = particle_type.split('_')
    particle_type_name = name[0]
    ID = name[1]

    # particle_type_names = [ 'enzyme', 'nutrient', 'bacteriotoxin', 'antibacteriotoxin' ]

    # 'enzyme' and 'nutrient' particles correspond to each other and 'bacteriotoxin'
    #   and 'antibacteriotoxin' particles correspond to each other.
    if particle_type_name == 'enzyme':
        corresponding_particle_type = 'nutrient_' + ID
    elif particle_type_name == 'nutrient':
        corresponding_particle_type = 'enzyme_' + ID
    elif particle_type_name == 'bacteriotoxin':
        corresponding_particle_type = 'antibacteriotoxin_' + ID
    elif particle_type_name == 'antibacteriotoxin':
        corresponding_particle_type = 'bacteriotoxin_' + ID

    # print(particle_type)
    return corresponding_particle_type


# Have the organisms in a node consume the nutrients in the node.
def consume_nutrients( patch ):
    # Collect all of the types of nutrients in the node.
    nutrient_types = patch.get_nutrient_types()
    # Iterate over the individuals in the node.
    for k, organism in enumerate( patch.organism_list ):
        # Iterate over the types of nutrients in the node.
        for nutrient_type in nutrient_types:
            # Get the amount available for a specific nutrient type.
            nutrient_amount_available = patch.get_attribute_value( nutrient_type )
            # Check to see if there are nutrients available for consumption.
            if nutrient_amount_available > 0:
                # Check to see if the organism has the appropriate nutrient attribute.
                #   If not, add the nutrient attribute to the organism and set its value
                #   to False (meaning the organism cannot consume the nutrient without
                #   the proper enzyme). Also check to see if the organism has an attribute
                #   for the associated enzyme.

                use_enzyme = False
                consume = False

                if organism.get_has_attribute( nutrient_type ) == True:
                    # If the organism has a value of true for its nutrient gene, it can
                    #   consume nutrients without the need for an enzyme to be present.
                    if organism.get_attribute_value( nutrient_type ) == True:
                        consume = True
                    # Otherwise, it will need an enzyme to consume the nutrient.
                    else:
                        use_enzyme = True
                # If the organism does not have the nutrient gene at all, it will have to
                #   use enzymes by default.
                else:
                    use_enzyme = True

                if use_enzyme == True:
                    # Get the name of the enzyme associated with the specified nutrient.
                    corresponding_enzyme_type = get_corresponding_particle( nutrient_type )
                    # Check to see if the node has the specified enzyme attribute.
                    if patch.get_has_attribute( corresponding_enzyme_type ) == True:
                        # Get the amount of the specified enzyme in the node.
                        enzyme_amount_available = patch.get_attribute_value( corresponding_enzyme_type )
                        # Check to see if there are any of the specified enzyme available for use.
                        if enzyme_amount_available > 0:
                            consume = True
                            # Decrement the amount of the enzyme by one.
                            patch.set_attribute( corresponding_enzyme_type, enzyme_amount_available - enzyme_needed_to_consume )

                # Consume will be equal to true if either the organism has the appropriate nutrient
                #   gene to allow it to consume the nutrient without the need for an enzyme or if
                #   there are enzymes available to aid the organism in the consumption of the nutrient.
                #   The following can be modified according to different design decisions.
                if consume == True:
                    # Check to make sure there is enough nutrients available to be consumed.
                    if nutrient_amount_available >= 20:
                        # Randomly choose the amount of nutrients consumed.
                        # nutrient_amount_consumed = np.random.randint(1, 21)
                        nutrient_amount_consumed = 20
                    # If there are less than ten units of the nutrient available, the organism will
                    #   simply consume them all.
                    else:
                        nutrient_amount_consumed = nutrient_amount_available
                    # Tell the node to update its nutrient count according to the organism's consumption.
                    patch.consume_nutrient( nutrient_type, nutrient_amount_consumed )
                    # Add the consumed nutrients as energy to the organism's energy reserves.
                    organism.energy = organism.energy + nutrient_amount_consumed


# Move the organisms within a node.
def move_organisms( i, j ):
    # Get the coordinates of the neighboring nodes.
    i_up, i_down, j_left, j_right = determine_ij( i, j, x_len, y_len )

    # A list to keep track of with organisms have moved.
    organism_moved_list = []

    # Iterate over the organisms in the node.
    for organism in lattice[i][j].organism_list:
        # Continue if the organism has not already been moved during this iteration
        #   in the simulation.
        if organism.moved == False:
            # Check to see if the organism has enough energy to move.
            if organism.energy >= 5:
                # Get a random number in the range (0, 1).
                r = np.random.random()

                # If it is decided that the organism moves, remove five energy from its
                #   energy reserves, set its moved attribute to be true, and append it
                #   to the list of moved organisms for the node.
                if r <= 4./5:
                    organism.energy -= 5
                    organism.moved = True
                    organism_moved_list.append( organism )

                    # Move north.
                    if r <= 1./5:
                        lattice[i_up][j].organism_list.append( organism )

                    # Move south.
                    elif 1./5 < r <= 2./5:
                        lattice[i_down][j].organism_list.append( organism )

                    # Move west.
                    elif 2./5 < r <= 3./5:
                        lattice[i][j_left].organism_list.append( organism )

                    # Move east.
                    elif 3./5 < r <= 4./5:
                        lattice[i][j_right].organism_list.append( organism )

                # Otherwise, stay in place.

    # Update the node's organism list leaving out the organisms that were moved.
    lattice[i][j].organism_list = [ organism for organism in lattice[i][j].organism_list if organism not in organism_moved_list ]


# Reset the moved attribute for each organism in the node to false.
def demove_organisms(patch):
    for organism in patch.organism_list:
        organism.moved = False


# Code to perform updates on the lattice.
def update_lattice(enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index):
    # A list to keep track of the new genes that arise when mutations occur.
    all_new_particles = []

    # Iterate over each row in the lattice.
    for i, row in enumerate(lattice):
        # Iterate over each column in the row.
        for j, patch in enumerate(row):
            # Have node grow more nutrients.
            lattice[i][j].grow_nutrients()

            # Check to see if the node contains organisms.
            if len(lattice[i][j].organism_list) > 0:
                # Have organisms in the node produce enzymes.
                # print('stuck here 1')
                organisms_produce_particles( lattice[i][j], 'enzyme' )
                # print('stuck here 2')
                # Have organisms in the node produce bacteriotoxins.
                organisms_produce_particles( lattice[i][j], 'bacteriotoxin' )
                # print('stuck here 3')
                # Have organisms in the node produce antibacteriotoxins.
                organisms_produce_particles( lattice[i][j], 'antibacteriotoxin' )
                # print('stuck here 4')
                # Have organisms in the node consume nutrients.
                consume_nutrients( lattice[i][j] )
                # print('stuck here 5')
                # Have organisms in the node reproduce.
                reproduce_organisms( lattice[i][j] )
                # print('stuck here 6')
                # Mutate the organisms in the node.
                enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index, new_particle_types = mutate_organisms(
                    lattice[i][j], enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index )
                # print('stuck here 7')
                # Keep track of the new genes that arise from the mutations.
                all_new_particles = all_new_particles + new_particle_types

                # Move the organisms in the node.
                move_organisms( i, j )
                # print('stuck here 8')
                # Kill off organisms that do not have enough energy to survive in the node.
                kill_organisms( lattice[i][j] )
                # print('stuck here 9')
    # print(all_new_particles)

    # Iterate over the nodes.
    for i in range(x_len):
        for j in range(y_len):
            # Add new genes to each organism in the node.
            # print('stuck here 10')
            add_genes_to_individuals( lattice[i][j], all_new_particles )
            # print('stuck here 11')
            # Add new particle attributes to the node.
            add_particle_types_to_patch( lattice[i][j], all_new_particles )
            # print('stuck here 12')
            # Have antibacteriotoxins destroy bacteriotoxins in the node.
            destroy_bacteriotoxin( lattice[i][j] )
            # print('stuck here 13')
            # Have bacteriotoxin destroy organisms in the node.
            bacteriotoxin_destroy_cells( lattice[i][j] )
            # print('stuck here 14')
            resistance_upkeep( lattice[i][j] )
            existance_upkeep( lattice[i][j] )
            # Reset the move attribute for the organisms in the node.
            demove_organisms( lattice[i][j] )
            # print('stuck here 15')
    # Allow the particles to diffuse across the lattice.
    # print('stuck here 16')
    diffuse_particles()
    # print('stuck here 17')
    return enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index


if __name__ == '__main__':
    np.random.seed(989084550)

    # The lengths of the x and y spatial dimensions.
    x_len = 8
    y_len = 8
    # The number of simulation time steps to take.
    sim_length = 400


    init_patch_nutrients = 100
    # The initial number of organisms in each node at the start of the simulation.
    #   The way the simulation is set up right now, the number of initial organisms
    #   should be less than x_len times y_len. init_num_organisms can be greater than
    #   that if multiple organisms are allowed to start in the same node.
    init_num_organisms = 40
    # The amount of energy that each initial organism starts out with.
    starting_energy = 100
    energy_threshold_for_reproduction = 40
    energy_consumed_for_reproduction = 10
    # energy_consumed_for_producing_particles = 10
    energy_consumed_for_producing_bacteriotoxin = 1
    energy_consumed_for_producing_antibacteriotoxin = 1
    energy_consumed_for_producing_enzyme = 1
    enzyme_needed_to_consume = 1
    amount_of_bacteriotoxin_needed_to_kill = 1
    resistance_upkeep_cost = 2
    existance_upkeep_cost = 2
    new_bacteriotoxin_particle_amount = 1
    new_antibacteriotoxin_particle_amount = 1
    new_enzyme_particle_amount = 1
    additional_bacteriotoxin_particle_amount = 1
    additional_antibacteriotoxin_particle_amount = 1
    additional_enzyme_particle_amount = 1

    # Probability that a mutation will occur.
    mutation_probability = .01

    # Probabily that a mutation occurs on an existing gene versus on a new gene.
    mutate_existing_probability = .9
    mutate_new_probabilty = 1 - mutate_existing_probability

    # Probability that a mutation occurs on a nutrient gene versus on an enzyme gene.
    consume_nutrient_mutation_probability = .2
    produce_enzyme_mutation_probability = 1 - consume_nutrient_mutation_probability

    # Probabilities that mutations will occur for the bacteriotoxin, antibacteriotoxin,
    #   and resistance genes.
    bacteriotoxin_mutation_probability = .5
    anti_mutation_probability = .1
    resistance_mutation_probability = .1

    # Set up a list of naming IDs.
    alphabet = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    naming_list = []
    for i in range(27):
        for j in range(26):
            for k in range(26):
                string = alphabet[i] + alphabet[j+1] + alphabet[k+1]
                string = string.strip()
                naming_list.append( string )

    # Indices for extracting naming IDs for enzyme/nutrients and bacteriotoxin/
    #   antibacteriotoxin/resistance.
    enzyme_nutrient_naming_index = 1
    bacteriotoxin_anti_naming_index = 1

    max_ID_enzyme_nutrient = 4
    max_ID_anti_bacteriotoxin = 4

    # Initialize the lattice.
    # lattice = [ [ patch_class(np.random.randint(0, 41), init_num_organisms, starting_energy )
                # for j in range(y_len) ] for i in range(x_len) ]
    rand_coors = get_rand_coors( x_len, y_len, init_num_organisms )
    # print(rand_coors)
    # lattice = [ [ patch_class(np.random.randint(0, 41), 0, starting_energy )
    #             for j in range(y_len) ] for i in range(x_len) ]

    lattice = [ [ patch_class( init_patch_nutrients, 0, starting_energy )
                for j in range(y_len) ] for i in range(x_len) ]

    for coor in rand_coors:
        lattice[coor[0]][coor[1]] = patch_class(np.random.randint(0, 41), 1, starting_energy )

    # A list to save the lattice at each time step.
    data = []

    # Iterate over the simulation length.
    for t in range(sim_length):
        print('time: {}'.format(t))
        # Update the lattice.
        enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index = update_lattice(
            enzyme_nutrient_naming_index, bacteriotoxin_anti_naming_index )

        data.append( copy.deepcopy(lattice) )

        num_organisms = 0
        for i in range(x_len):
            for j in range(y_len):
                num = lattice[i][j].get_number_of_organisms()
                num_organisms += num

        print('number of organisms: {}'.format( num_organisms) )
                # print(lattice[i][j].get_attributes)
                # for organism in lattice[i][j].organism_list:
                    # resistance_types = organism.get_resistance_types()
                    # for resistance_type in resistance_types:
                        # value = organism.get_attribute_value(resistance_type)
                        # if value == True:
                            # print('i: {}, j: {}, resistance: {}'.format(i, j, resistance_type))
                        # print(organism.get_attribute_value(resistance_type))
                    # print(organism.get_attributes)

    # print( lattice[5][5].organism_list[0].get_attributes )

    print(lattice[-1][-1].get_attributes)

    # Save the data to a pickle file.
    with open(save_file_name, 'wb') as savefile:
        pickle.dump(data, savefile)
