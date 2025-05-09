# Burgers equation in one dimension

import math
import time
from tkinter import *

L = 1.0                         # size of periodic region
N = 500                         # number of grid points
dx = L / float(N)               # lattice spacing
t = 0.0                         # time
u_max = 1.0                     # maximum wave amplitude
CFL_ratio = 1.0                 # Courant-Friedrichs-Lewy ratio
dt = CFL_ratio * dx             # time step
initial_waveform = "Sine"

nu = 1.0e-6                     # kinematic viscosity
u = [] ; u_new = []             # the solution and its update
next = [] ; prev = []           # for periodic boundary conditions

method = "Godunov"              # integration method
step = 0                        # integration step number

def initialize():

    # create arrays for lattice vectors
    global u, u_new
    u = [ 0.0 for j in range(N) ]
    u_new = [ 0.0 for j in range(N) ]

    # initialize arrays for periodic boundary conditions
    global next, prev
    next = [ j+1 for j in range(N) ]
    prev = [ j-1 for j in range(N) ]
    next[N-1] = 0
    prev[0] = N-1

    # reset lattice spacing and initialize waveform
    global dx, u_max
    dx = L / float(N)
    u_max = 0.0
    for j in range(N):
        x = j * dx
        if initial_waveform == "Sine":
            u[j] = math.sin(2 * math.pi * x) + 0.5 * math.sin(math.pi * x)
        elif initial_waveform == "Step":
            if x > L/4.0 and x < 3*L/4.0:
                u[j] = 1.0
            else:
                u[j] = 0.0
        else:
            u[j] = 1.0
        u_max = max(abs(u[j]), u_max)

    # set time, step and step number
    global t, dt, step
    t = 0.0
    dt = CFL_ratio * dx / u_max
    step = 0

def FTCS():
    global u_new
    for j in range(N):
        u_new[j]  = u[j] * (1.0 - dt / (2.0 * dx) * (u[next[j]] - u[prev[j]]))
        u_new[j] += nu * dt / dx**2 * (u[next[j]] + u[prev[j]] - 2 * u[j])

def Lax():
    global u_new
    for j in range(N):
        u_new[j]  = (u[next[j]] + u[prev[j]]) / 2.0
        u_new[j] -= u[j] * dt / (2.0 * dx) * (u[next[j]] - u[prev[j]])
        u_new[j] += nu * dt / dx**2 * (u[next[j]] + u[prev[j]] - 2 * u[j])

def Lax_Wendroff():
    global u_new
    F = [ u[j]**2 / 2.0 for j in range(N) ]     # flux vector
    for j in range(N):
        u_new[j]  = (u[j] + u[next[j]]) / 2.0
        u_new[j] -= dt / (2.0 * dx) * (F[next[j]] - F[j])
        u_new[j] += nu * dt / (2.0 * dx**2) * (
                    (u[next[j]] + u[prev[j]] - 2 * u[j])/ 2.0 +
                    (u[next[next[j]]] + u[j] - 2 * u[next[j]])/ 2.0 )
    for j in range(N):
        F[j] = u_new[j]**2 / 2.0
    for j in range(N):
        u_new[j]  = u[j] - dt / dx * (F[j] - F[prev[j]])
        u_new[j] += nu * dt / dx**2 * (u[next[j]] + u[prev[j]] - 2 * u[j])

def Godunov():
    global u_new
    u_plus = [ u[j] for j in range(N) ]
    u_minus = [ u[j] for j in range(N) ]
    for j in range(N):
        if u_plus[j] < 0.0:
            u_plus[j] = 0.0
        if u_minus[j] > 0.0:
            u_minus[j] = 0.0
    F = [ 0.0 ] * N
    for j in range(N):
        f1 = u_plus[prev[j]]**2 / 2.0
        f2 = u_minus[j]**2 / 2.0
        if f1 > f2:
            F[prev[j]] = f1
        else:
            F[prev[j]] = f2
        f1 = u_plus[j]**2 / 2.0
        f2 = u_minus[next[j]]**2 / 2.0
        if f1 > f2:
            F[j] = f1
        else:
            F[j] = f2
        u_new[j]  = u[j]
        u_new[j] += nu * dt / dx**2 * (u[next[j]] + u[prev[j]] - 2 * u[j])
        u_new[j] -= dt / dx * (F[j] - F[prev[j]])

T = 1.0                 # time to travel length L
frames_per_sec = 25     # animation rate for screen redraws

def time_step():
    global t, u, u_new
    eval(method + "()")
    swap = u
    u = u_new
    u_new = swap
    t += dt;

class Application(Frame):

    def create_widgets(self):
        self.controls = Frame(self, relief=RAISED, borderwidth=2)
        self.controls.pack(side=BOTTOM)
        self.waveform = StringVar()
        self.waveform.set(initial_waveform)
        self.INIT = Menubutton(self.controls, text=initial_waveform)
        self.INIT.menu = Menu(self.INIT)
        for wave in [ 'Sine', 'Step'  ]:
            self.INIT.menu.add_radiobutton(variable=self.waveform,
                                           value=wave, label=wave,
                                           command=self.reset)
        self.INIT['menu'] = self.INIT.menu
        self.INIT.pack(side=LEFT)
        self.algorithm = StringVar()
        self.algorithm.set(method)
        self.METHOD = Menubutton(self.controls, text=method.center(20))
        self.METHOD.menu = Menu(self.METHOD)
        for algo in [ 'FTCS', 'Lax', 'Lax_Wendroff', 'Godunov' ]:
            self.METHOD.menu.add_radiobutton(variable=self.algorithm,
                                             value=algo, label=algo)
        self.METHOD['menu'] = self.METHOD.menu
        self.METHOD.pack(side=LEFT)
        self.RESET = Button(self.controls, text="RESET", command=self.reset)
        self.RESET.pack(side=LEFT)
        self.QUIT = Button(self.controls, text="QUIT", command=self.quit)
        self.QUIT.pack(side=LEFT)
        self.draw = Canvas(self, width="600", height="400")
        self.draw.pack(side=TOP)

    def update_frame(self):
        self.draw.delete(ALL)
        for j in range(1, N):
            x0 = int((j-1) * dx / L * 600) ; x1 = int(j * dx / L * 600)
            y0 = 200 - int(u[j-1] * 180) ; y1 = 200 - int(u[j] * 180)
            self.draw.create_line(x0, y0, x1, y1, fill="red")
        global method
        method = self.algorithm.get()
        self.METHOD.config(text = method.center(20))
        start_time = time.clock()
        while True:
            time_step()
            if time.clock() - start_time > 1.0 / frames_per_sec:
                break
        self.after(frames_per_sec, self.update_frame)

    def __init__(self, master=None):
        Frame.__init__(self, master)
        Pack.config(self)
        self.create_widgets()
        self.after(10, self.update_frame)

    def reset(self):
        global initial_waveform
        initial_waveform = self.waveform.get()
        self.INIT.config(text = initial_waveform)
        initialize()

initialize()
root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()
