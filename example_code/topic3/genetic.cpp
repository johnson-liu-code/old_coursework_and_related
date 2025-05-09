#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "../tools/random.hpp"

vector<vector<int> > new_extended_coil(string dna) {
    // input:  dna sequence of 'B' (hydrophopic) and 'W' (hydrophilic) residues
    // output: extended linear conformation

    int L = dna.size();
    int n_B = 0, n_W = 0;
    for (int i = 0; i < L; i++) {
        if (dna[i] == 'B')
            n_B += 1;
        else if (dna[i] == 'W')
            n_W += 1;
    }
    assert(L == n_B + n_W);
    vector<vector<int> > coil;
    for (int i = 0; i < L; i++) {
        vector<int> xy(2);
        xy[1] = i;
        coil.push_back(xy);
    }
    return coil;
}

double E(vector<vector<int> > s, string dna)
{
    // input:  conformation, dna sequence
    // output: E = - (number of non-covalent BB nearest neighbors

    int L = s.size();
    int n_BB = 0;
    for (int i = 0; i < L - 2; i++)
        for (int j = i + 2; j < L; j++)
            if (dna[i] == 'B' && dna[j] == 'B') {
                int dx = s[i][0] - s[j][0];
                int dy = s[i][1] - s[j][1];
                if (abs(dx) + abs(dy) == 1)
                    n_BB += 1;
            }
    return -n_BB;
}

bool MMC_mutation_step(vector<vector<int> >& s, string dna, double c_k)
{
    // input:  conformation, temperature
    // output: changed conformation, whether mutation was self-avoiding

    int L = s.size();
    vector<vector<int> > s_trial = s;   // for trial conformation

    // choose a random interior amino acid
    int i = 1 + int(floor(uniform_dist() * (L - 2)));

    // rotation matrices for 90, 180, and 270 degrees
    int rotation_matrices[3][2][2] =
        { { {0, -1},
            {1,  0} }, { {-1, 0},
                         {0, -1} }, { { 0, 1},
                                      {-1, 0}} };
    int r = int(floor(uniform_dist() * 3));

    // rotate the C-terminal (j < i) portion about amino acid i
    for (int j = 0; j < i; j++) {
        int dr[2];
        for (int k = 0; k < 2; k++)
            dr[k] = s[j][k] - s[i][k];
        for (int k = 0; k < 2; k++) {
            s_trial[j][k] = s[i][k];
            for (int l = 0; l < 2; l++)
                s_trial[j][k] += rotation_matrices[r][k][l] * dr[l];
        }
    }

    // check whether this is a valid self-avoiding conformation
    for (int j = 0; j < i; j++)
        for (int k = i + 1; k < L; k++)
            if (s_trial[j][0] == s[k][0] && s_trial[j][1] == s[k][1])
                return false;

    // no overlaps - update conformation using Metropolis et al. algorithm
    double dE = E(s_trial, dna) - E(s, dna);
    double w = exp(- dE / c_k);
    if (uniform_dist() < w)
        for (int j = 0; j < i; j++)
            for (int k = 0; k < 2; k++)
                s[j][k] = s_trial[j][k];
    return true;
}

void simulated_annealing_run(vector<vector<int> >& s, string dna, int mmc_steps,
        double& E_min, int& step_min, double& valid_confs)
{
    // input:  conformation s, number of Metropolis Monte Carlo steps
    // output: lowest energy, step found, fraction self-avoiding conformations

    double c_k = 2.0;           // initial temperature
    double alpha = 0.99;        // cooling factor
    valid_confs = 0;
    E_min = E(s, dna);
    step_min = 0;
    for (int step = 1; step <= mmc_steps; step++) {
        if (MMC_mutation_step(s, dna, c_k)) {
            valid_confs += 1;
            double E_step = E(s, dna);
            if (E_step < E_min) {
                E_min = E_step;
                step_min = step;
                cout << " E = " << E_min << " at step " << step << endl;
            }
        }
        if (step % 200000 == 0 && c_k > 0.15)
            c_k *= 0.99;
    }
    valid_confs /= double(mmc_steps);
}

int main()
{
    cout << " Folding of a Simple Model Protein on a Square Lattice\n"
         << " using Simulated Annealing and Genetic Algorithms\n"
         << " R. Unger and J. Moult, J. Mol. Biol. 231, 75-81 (1993)\n"
         << " ------------------------------------------------------" << endl;

    // sample protein with 20 amino acids
    string dna("BWBWWBBWBWWBWBBWWBWB");
    vector<vector<int> > p20 = new_extended_coil(dna);
    int L = p20.size();
    cout << " Initialized sequence " << dna << " L = " << L
         << " fully extended" << endl;
    int mmc_steps = 50 * 1000 * 1000;
    cout << " Simulated annealing with " << mmc_steps << " steps" << endl;
    double E_min, valid_confs;
    int step_min;
    simulated_annealing_run(p20, dna, mmc_steps, E_min, step_min, valid_confs);
    cout << " E_min = " << E_min << " at step " << step_min
         << " fraction of valid configurations = " << valid_confs << endl;
}
