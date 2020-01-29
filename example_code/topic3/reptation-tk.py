import math
import random
import copy
from tkinter import *

N = 5                           # length of polymer chain
polymer = []                    # list of [x,y] coordinates
L = 10                          # number of lattice sites in x and y

def occupied(x, y):
    return [x, y] in polymer

x_current, y_current = [0, 0]   # coordinates of current monomer
x_previous, y_previous = [0, 0] # coordinates of previous monomer

def trial_step():
    global x_trial, y_trial
    if x_previous == x_current: # step right or left at random
        x_trial = x_current + random.choice((-1, 1))
        y_trial = y_current
    else:                       # step up or down at random
        x_trial = x_current
        y_trial = y_current + random.choice((-1, 1))

def cul_de_sac():
    if x_previous == x_current:
        return (occupied(x_current + 1, y_current) and
                occupied(x_current - 1, y_current))
    else:
        return (occupied(x_current, y_current + 1) and
                occupied(x_current, y_current - 1))

n_trials = 0                    # number of trials made
n_steps = 0                     # number of steps in trial

def random_step(O):
    global n_steps, polymer, x_current, y_current, x_previous, y_previous
    global need_to_clear
    if n_steps == 0:            # take first step in a random direction
        r = randrange(4)
        if r == 0:
            polymer[1][0] += 1
        elif r == 1:
            polymer[1][0] -= 1
        elif r == 2:
            polymer[1][1] += 1
        else:
            polymer[1][1] -= 1
        n_steps = 1
        return
    x_current, y_current = polymer[n_steps]
    x_previous, y_previous = polymer[n_steps - 1]
    if cul_de_sac():
        initialize()
        need_to_clear = True
        return
    trial_succeeded = False
    while not trial_succeeded:
        trial_step()
        trial_succeeded = not occupied(x_trial, y_trial)
    n_steps += 1
    polymer[n_steps] = [x_trial, y_trial]

def initialize():
    global n_polymers, r_squared_sum, polymer, polymer_copy, n_steps, n_trials
    n_polymers = 0
    r_squared_sum = 0.0
    x = y = L // 2              # place all monomers at center of lattice
    polymer = [ [x, y] for i in range(N + 1) ]
    polymer_copy = copy.deepcopy(polymer)
    n_steps = 0
    n_trials += 1

def reptate():
    global polymer, polymer_copy, x_current, y_current, x_previous, y_previous
    # save a copy in case reptation fails
    polymer_copy = copy.deepcopy(polymer)
    # remove tail
    for i in range(N):
        polymer[i] = polymer[i+1]
    # head attempts to move
    x_current, y_current = polymer[N-1]
    x_previous, y_previous = polymer[N-2]
    trial_step()
    # test whether move is allowed
    if not occupied(x_trial, y_trial):
        # accept new head position
        polymer[N] = [x_trial, y_trial]
    else:
        # interchange head and tail in previous configuration
        polymer = polymer_copy.reverse()
    n_polymers += 1
    r_squared_sum += (  (polymer[N][0] - polymer[0][0])**2
                        (polymer[N][0] - polymer[0][0])**2  )
    move_to_center_of_screen()

class Animation(Frame):

    def __init__(self, master=None):
        Frame.__init__(self, master)
        Pack.config(self)
        self.create_widgets()
        self.after(10, self.animation_step)

    def create_widgets(self):
        self.control = Frame(self)
        self.control.pack(side=BOTTOM)
        self.quit_button = Button(self.control, text='QUIT', command=self.quit)
        self.quit_button.pack(side=RIGHT)
        self.draw = Canvas(self, width='400', height='400')
        self.draw.pack(side=TOP)

    def draw_polymer(self):
        self.draw.delete("all")

    def animation_step(self):
        self.draw_polymer()
        trial_step()
        self.after(10, self.animation_step())

print(" Reptation Algorithm Animation using Tkinter")
root = Tk()
anim = Animation(master=root)
anim.mainloop()
root.destroy()
