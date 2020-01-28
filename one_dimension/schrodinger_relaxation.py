
import numpy as np
import matplotlib.pyplot as plt


h = 1.E-2
a = 1.

length = a/h

psi = np.ones(int(length))

m = 1;
h_bar = 1;

n=1.;
E = (n**2. * np.pi**2. * h_bar**2.) / (2 * m * a**2.);
#print(E)
V = 0;

#c = -((2 * m) / h_bar^2) * (E - V);

c = -2*m*h**2. / h_bar**2.

#print(c*-E)

for j in range(100):
    for i in range(int(length)-2):
        #psi[i+1] = (V - E - (2*c)/h**2. )**-1. * (c/h**2.) * ( psi[i] + psi[i+2] )
        psi[i+1] = (c*(E-V)+2.)**-1. * (psi[i] + psi[i+2])
        #print(new)


plt.plot(np.linspace(0, a, int(length)), psi)

plt.show()
