
import numpy as np
import matplotlib.pyplot as plt


#h = 1.E-2
a = 1.

#length = a/h
length = 1
delta_x = .001

spread = int(length/delta_x)

psi = np.ones(spread)
psi[0] = 0
#psi[int(spread/2.):-2] = -1.
psi[-1] = 0

m = 1
h_bar = 1

n = 2.
E = (n**2. * np.pi**2. * h_bar**2.) / (2. * m * a**2.)
print(E)

#V = 0

#c = -((2 * m) / h_bar^2) * (E - V)

c = -2*m*delta_x**2. / h_bar**2.

def get_potential(x):
    if x < (1./5)*length:
        V = 0.
    elif x >= (1./5)*length and x < (2./5)*length:
        V = 0.
    elif x >= (2./5)*length and x < (3./5)*length:
        V = 0.
    elif x >= (3./5)*length and x < (4./5)*length:
        V = 0.
    elif x >= (4./5)*length:
        V = 0.
    else:
        V = 0.

    return V

#print(c*-E)

time = 1000

for j in range(time):
    #psi_new = np.copy(psi)
    for i in range(1, spread-1):
        #psi[i+1] = (V - E - (2*c)/h**2. )**-1. * (c/h**2.) * ( psi[i] + psi[i+2] )
        #psi[i+1] = (c*(E-V)+2.)**-1. * (psi[i] + psi[i+2])
        #psi_new[i+1] = (c*(E-V)+2.)**-1. * (psi[i] + psi[i+2])
        V = get_potential(i*delta_x)
        #psi_new[i] = (c*(E-V)+2.)**-1. * (psi[i-1] + psi[i+1])
        psi[i] = (c*(E-V)+2.)**-1. * (psi[i-1] + psi[i+1])
        #print(new)
    #psi = np.copy(psi_new)


#print(length)
#print(delta_x)
#print(spread)

plt.plot(np.linspace(0, delta_x, spread), psi)

plt.grid()
plt.ylim(-1.5, 1.5)

plt.show()
