

### created 7 Feb 2017 ###

### commented 17 Feb 2017
#   - remeber to change the directory where you want to save the figures


import numpy as np
from copy import deepcopy
import matplotlib.pyplot as plt
from matplotlib import colors

### parameters for random number generator
a = 7.**5
m = float(2**31 - 1)
c = 0

q = m/a
r = m % a

x1 = 9101994.
#x2 = 111.

r1 = 0.
d = .75

### accept/reject method

def accept_reject(x1, y):   
    x1 = a*(x1 % q) - (r*x1)/q
    
    if x1 < 0:
        x1 += m

    r1 = x1/m
    
    if r1 <= y:
        change = True
        
    else:
        change = False
    
    #print 'r1 = ', r1, ' y = ', y, change
    
    return x1, change

### metropolis method

'''
def metropolis(x1, x2, r1, cutoff):
    x1 = a*(x1 % q) - (r* x1)/q

    if x1 < 0:
        x1 += m
    
    s1 = x1/m
    
    x2 = a*(x2 % q) - (r*x2)/q
    
    if x2 < 0:
        x2 += m
    
    s2 = x2/m
    
    r2 = r1 + d*(2*s1 - 1)
    
    if r2 > 0 and r2 < cutoff:
        r1 = r2
        change = True
    
    else:
        change = False
    
    return x1, x2, r1
'''


### parameters for Ising model
n = 60
v = np.ones((n,n))

#k = 1.38064852E-23                  # m^2 kg s^{-2} K^{-1}
#T = 300.                            # K

#B = (k * T)**-1.

B = 100.

J_ = -1.


iterations = 30

### initialize grid


for i in range(n):
    for j in range(n):
        x1, change = accept_reject(x1, .5)
        
        if change == True:
            v[i][j] = v[i][j] * -1.


### wrap-around function

def determine_ij(i, j):
    I = i
    J = j
    
    if i == 0:
        I_up = n-1
        I_down = i + 1
        
        if j == 0:
            J_left = n-1
            J_right = j + 1

        elif j == n-1:
            J_left = j - 1
            J_right = 0
        
        else:
            J_left = j - 1
            J_right = j + 1

    elif i == n-1:
        I_up = i - 1
        I_down = 0
            
        if j == 0:
            J_left = n-1
            J_right = j + 1
            
        elif j == n-1:
            J_left = j - 1
            J_right = 0
        
        else:
            J_left = j - 1
            J_right = j + 1
    
    else:
        I_up = i - 1
        I_down = i + 1
        
        if j == 0:
            J_left = n-1
            J_right = j + 1
            
        elif j == n-1:
            J_left = j - 1
            J_right = 0
        
        else:
            J_left = j - 1
            J_right = j + 1

    return I, J, I_up, I_down, J_left, J_right

### function to evaluate E_old and E_new

def evaluate_E(I, J, I_up, I_down, J_left, J_right, p_grid, x1):    
    E_old = -J_ * p_grid[I][J] * (p_grid[I_up][J] + p_grid[I_down][J] + p_grid[I][J_left] + p_grid[I][J_right])
    
    E_new = E_old * -1.
    
    #print p_grid[I_up][J], p_grid[I_down][J], p_grid[I][J_left], p_grid[I][J_right]

    #print 'E_new = ', E_new, ' E_old = ', E_old
    
    if E_new <= E_old:
        change = True
                
        #print change
                
    elif E_new > E_old:
        y = np.exp(-B * (E_new - E_old))
            
        x1, change = accept_reject(x1, y)
    
    return x1, change

collection = [deepcopy(v) for it in range(iterations)]

#print len(collection)

#print v

#for c in collection:
#    print c

#print '\n'

for count, col in enumerate(collection[1:]):
    #print count
    for i in range(n):
        for j in range(n):
            #print i, j
            I, J, I_up, I_down, J_left, J_right = determine_ij(i, j)
            
            x1, change = evaluate_E(I, J, I_up, I_down, J_left, J_right, collection[count], x1)
            
            #print x1, change
            
            #print change
            
            #print collection[count+1][I][J]
            
            #print count+1
            
            if change == True:
                collection[count+1][I][J] = collection[count+1][I][J] * -1.
                
                #collection[count+1][I][J] = 10.
        
            #print collection[count+1][I][J]
            
            #print c_grid[I][J]
    
    collection[count+1] = deepcopy(col)
    
    #print collection[count+1], '\n'

    #print col, '\n'


#print len(collection)

#print collection

#for c in collection:
#    print c


### graphing parameters

cmap = colors.ListedColormap(['white', 'black'])
bounds=[-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)


for count, c in enumerate(collection):
#    print c, '\n'
    plt.clf()
    plt.figure()
    fig = plt.imshow(c, cmap = cmap,  interpolation='nearest', origin = 'lower')
    plt.colorbar(fig, cmap=cmap, norm=norm, boundaries=bounds, ticks=[-1, 1])

    #plt.show()
    plt.savefig('C:\Users\jliu25\Desktop\ising_model\\17_Feb_17\\016\\' + str("{0:0=4d}".format(count)) + '.png', format = 'png')

