import copy
import math
import random

def new_extended_coil(dna):
    """ input:  dna sequence of 'B' (hydrophopic) and 'W' (hydrophilic) residues
        output: extended linear conformation
    """
    L = len(dna)
    assert L == dna.count('B') + dna.count('W')
    return [ [0, i] for i in range(L) ]

def E(s, dna):
    """ input:  conformation, dna sequence
        output: E = - (number of non-covalent BB nearest neighbors
    """
    L = len(s)
    n_BB = 0
    for i in range(L - 2):
        for j in range(i + 2, L):
            if dna[i] == 'B' and dna[j] == 'B':
                dx = s[i][0] - s[j][0]
                dy = s[i][1] - s[j][1]
                if abs(dx) + abs(dy) == 1:
                    n_BB += 1
    return -n_BB

def MMC_mutation_step(s, dna, c_k):
    """ input:  conformation, temperature
        output: changed conformation, whether mutation was self-avoiding
    """
    L = len(s)
    s_trial = copy.deepcopy(s)          # for trial conformation
    i = random.randrange(1, L - 1)      # choose a random interior amino acid
    # rotation matrices for 90, 180, and 270 degrees
    rotation_matrices = [ [ [0, -1],
                            [1,  0]], [ [-1, 0],
                                        [0, -1]], [ [ 0, 1],
                                                    [-1, 0]] ]
    rot_mat = rotation_matrices[random.randrange(3)]
    # rotate the C-terminal (j < i) portion about amino acid i
    for j in range(i):
        dr = [ s[j][k] - s[i][k] for k in range(2) ]
        for k in range(2):
            s_trial[j][k] = s[i][k]
            for l in range(2):
                s_trial[j][k] += rot_mat[k][l] * dr[l]
    # check whether this is a valid self-avoiding conformation
    for j in range(i):
        for k in range(i + 1, len(s)):
            if s_trial[j] == s[k]:
                return False
    # no overlaps - update conformation using Metropolis et al. algorithm
    dE = E(s_trial, dna) - E(s, dna)
    w = math.exp(- dE / c_k)
    if random.random() < w:
        for j in range(i):
            for k in range(2):
                s[j][k] = s_trial[j][k]
    return True

def simulated_annealing_run(s, dna, mmc_steps):
    """ input:  conformation s, dna, number of Metropolis Monte Carlo steps
        output: lowest energy, step found, fraction self-avoiding conformations
    """
    c_k = 2.0           # initial temperature
    alpha = 0.99        # cooling factor
    valid_confs = 0
    E_min = E(s, dna)
    step_min = 0
    for step in range(1, mmc_steps + 1):
        if MMC_mutation_step(s, dna, c_k):
            valid_confs += 1
            E_step = E(s, dna)
            if E_step < E_min:
                E_min = E_step
                step_min = step
                print(" E =", E_min, "at step", step)
        if step % 200000 == 0 and c_k > 0.15:
            c_k *= 0.99
    valid_fraction = valid_confs / float(mmc_steps)
    return E_min, step_min, valid_fraction

print(" Folding of a Simple Model Protein on a Square Lattice")
print(" using Simulated Annealing and Genetic Algorithms")
print(" R. Unger and J. Moult, J. Mol. Biol. 231, 75-81 (1993)")
print(" ------------------------------------------------------")

# sample protein with 20 amino acids
dna = "BWBWWBBWBWWBWBBWWBWB"
p20 = new_extended_coil(dna)
L = len(p20)
print(" Initialized sequence", dna, "L =", L, "fully extended")
mmc_steps = 50 * 10**6
print(" Simulated annealing with", mmc_steps, "steps")
E_min, step_min, valid_confs = simulated_annealing_run(p20, dna, mmc_steps)
print(" E_min =", E_min, "at step", step_min,
    "fraction of valid configurations =", valid_confs)
