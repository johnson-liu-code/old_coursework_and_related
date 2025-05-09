import math
import random
import sys
sys.setrecursionlimit(10000)
from tkinter import *

L = 40                  # number of spins in x and y, N = L^2 = 1,600
s = []                  # array of spin values
J = 1.0                 # nearest neighbor coupling constant
T = 2.269               # temperature
H = 0.0                 # external magnetic field

def initialize_spins():
    global s
    s = []
    for i in range(L):
        s.append([])
        for j in range(L):
            s[i].append(random.choice((-1, +1)))

# --------------------- definitions for Metropolis update
w = []                  # Boltzmann factors at fixed T and H

def compute_Boltzmann_factors():
    global w
    w = []
    for m in range(5):
        w.append( [] )
        sum_of_neighbors = -4 + 2 * m
        for n in range(2):
            s_i = -1 + 2 * n
            factor = math.exp( -2.0 * (J * sum_of_neighbors + H) * s_i / T )
            w[m].append(factor)

def Metropolis_sweep():
    # update every spin using the alogrithm of Metropolis et al.
    for i in range(L):
        for j in range(L):
            sum_of_neighbors = (
                s[(i-1)%L][j] + s[(i+1)%L][j] + s[i][(j-1)%L] + s[i][(j+1)%L] )
            ratio = w[2 + int(sum_of_neighbors/2)][int((1 + s[i][j])/2)]
            if ratio > 1.0 or ratio > random.random():
                s[i][j] = -s[i][j]

# --------------------- definitions for Wolff cluster update

cluster = []            # boolean array for s[i][j] belonging to cluster
cluster_spin = 1        # value of spin chosen to seed cluster
add_probability = 1.0   # probability for adding a candidate spin
try_add_sum = 0         # number of candidate spins

def grow_cluster(i, j):
    #  mark spin i,j as belonging to the cluster and flip it
    cluster[i][j] = True
    s[i][j] = -s[i][j]

    #  if any of the 4 neighboring spins does not belong to the cluster
    #  try to add it to the cluster.  Use periodic boundary conditions
    i_prev = (i - 1) % L
    if not cluster[i_prev][j]:
        try_add(i_prev, j)
    i_next = (i + 1) % L
    if not cluster[i_next][j]:
        try_add(i_next, j)
    j_prev = (j - 1) % L
    if not cluster[i][j_prev]:
        try_add(i, j_prev)
    j_next = (j + 1) % L
    if not cluster[i][j_next]:
        try_add(i, j_next)

def try_add(i, j):
    global try_add_sum
    try_add_sum += 1
    if s[i][j] == cluster_spin:
        if random.random() < add_probability:
            grow_cluster(i, j)

def Wolff_cluster_update():
    global add_probability, cluster_spin, try_add_sum
    add_probability = 1 - math.exp(- 2.0 * J / T)
    try_add_sum = 0
    while try_add_sum < L**2:
        cluster.clear()
        for i in range(L):
            cluster.append([])
            for j in range(L):
                cluster[i].append(False)
        # choose a random spin to seed the cluster
        i = random.randrange(L)
        j = random.randrange(L)
        cluster_spin = s[i][j]
        grow_cluster(i, j)

# --------------------- definitions for GUI and animation

class Animation(Frame):

    def __init__(self, master=None):
        Frame.__init__(self, master)
        Pack.config(self)
        self.create_widgets()
        self.after(10, self.animation_step)
        self.algorithm = 'Metropolis'

    def create_widgets(self):
        self.control = Frame(self)
        self.control.pack(side=BOTTOM)
        self.QUIT = Button(self.control, text='QUIT', command=self.quit)
        self.QUIT.pack(side=RIGHT)
        self.TOGGLE = Button(self.control, text='Switch Algorithm',
            command=self.toggle)
        self.TOGGLE.pack(side=RIGHT)
        self.TEMP = Entry(self.control)
        self.TEMP.insert(0, str(T))
        self.TEMP.bind("<Return>", (lambda event: self.set_T(self.TEMP.get())))
        self.TEMP.pack(side=RIGHT)
        self.TLABEL = Label(self.control, text="Enter T = ")
        self.TLABEL.pack(side=RIGHT)
        self.draw = Canvas(self, width='400', height='400')
        self.draw.pack(side=TOP)

    def set_T(self, T_string):
        global T, add_probability
        T = float(T_string)
        compute_Boltzmann_factors()
        add_probability = 1 - math.exp(- 2.0 * J / T)

    def toggle(self):
        if self.algorithm == 'Metropolis':
            self.algorithm = 'Wolff'
        else:
            self.algorithm = 'Metropolis'
        self.TOGGLE["text"] = self.algorithm[:6] + ' Algorithm'

    def draw_spins(self):
        self.draw.delete("all")
        d = max(math.floor(400.0 / L), 2)
        for i in range(L):
            for j in range(L):
                if s[i][j] == 1:
                    color = 'red'
                else:
                    color = 'black'
                self.draw.create_rectangle(
                    i * d, j * d, i * d + d, j * d + d, fill=color)

    def animation_step(self):
        self.draw_spins()
        if self.algorithm == 'Metropolis':
            Metropolis_sweep()
        else:
            Wolff_cluster_update()
        self.after(10, self.animation_step)

print(" Ising Model Animation using Tkinter")
T = 2.269 # float(input(" Enter temperature T: "))
initialize_spins()
compute_Boltzmann_factors()
root = Tk()
anim = Animation(master=root)
anim.mainloop()
root.destroy()
