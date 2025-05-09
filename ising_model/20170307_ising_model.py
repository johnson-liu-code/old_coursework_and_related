

### created 7 Feb 2017 ###

### commented 17 Feb 2017 ###
#   - Remeber to change the directory where you want to save the figures.

### modified 25 Feb 2017 ###
#   - Trimmed down the code.
#   - No longer saves every grid. Instead, a plot is made when the code is finished iterating through a single grid. Then, the code repeats.

### modified 28 Feb 2017 ###
#   - Only makes one plot out of every m iterations.

### modified 7 Mar 2017 ###
#   - Added code to plot magnetization versus time.


import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import colors


### Parameters for random number generator.
a = 7.**5
m = float(2**31 - 1)
c = 0

q = m/a
r = m % a

x1 = 2.**13.
#x2 = 111.

#r1 = 0.
#d = .75

### Accept/reject method.

def accept_reject(x1, y):
    # Generate random number.
    x1 = a*(x1 % q) - (r*x1)/q
    
    if x1 < 0:
        x1 += m

    r1 = x1/m
    
    # If random number is less than y, change the spin.
    if r1 <= y:
        change = True
        
    else:
        change = False
    
    #print 'r1 = ', r1, ' y = ', y, change
    
    return x1, change


### Metropolis method.
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

# Directory to save graphs.
dir_num = 3

#directory = 'C:\Users\jliu25\Desktop\ising_model\\28_Feb_17\\' + str("{0:0=3d}".format(dir_num)) + '\\'
directory = 'U:\desktop\school_jliu\Holland\\7_Mar_2017_ising_model\\' + str("{0:0=3d}".format(dir_num)) + '\\'

if not os.path.exists(directory):
    os.makedirs(directory)


### Parameters for the Ising model.
n = 10
v = np.ones((n,n))

#k = 1.38064852E-23                  # m^2 kg s^{-2} K^{-1}		# Boltzmann constant.
#T = 300.                            # K				# Temperature.

#B = (k * T)**-1.							# Beta.

#B = .44
beta = [x*.05 for x in range(0,20)]

J_ = 1.									# J.


iterations = 1000			# Number of iterations.


### Wrap-around function.
def determine_ij(i, j):
    I = i
    J = j
    
    if i == 0:			# Top edge of grid.
        I_up = n-1
        I_down = i + 1
        
        if j == 0:		# Left edge of grid.
            J_left = n-1
            J_right = j + 1

        elif j == n-1:		# Right edge of grid.
            J_left = j - 1
            J_right = 0
        
        else:
            J_left = j - 1
            J_right = j + 1

    elif i == n-1:		# Bottom edge of grid.
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

### Function to evaluate E_old and E_new.

def evaluate_E(I, J, I_up, I_down, J_left, J_right, v, x1):
    E_old = -J_ * v[I][J] * (v[I_up][J] + v[I_down][J] + v[I][J_left] + v[I][J_right])
    E_new = E_old * -1.		# E_new has the same magnitude as E_old, but with the oppposite sign in the case of only two available spins.
   
    if E_new <= E_old:		# If E_new is less than or equal to E_old, change the spin.
        change = True
                
        #print change
                
    elif E_new > E_old:		# If E_new is greater than E_old, change the spin only if a generated random number is less than the exponential.
        y = np.exp(-B * (E_new - E_old))
            
        x1, change = accept_reject(x1, y)
    
    return x1, change
    
def energy(I, J, I_up, I_down, J_left, J_right, v,):
    ENERGY = -J_ * v[I][J] * (v[I_up][J] + v[I_down][J] + v[I][J_left] + v[I][J_right])
    return ENERGY


### Graphing parameters.
cmap = colors.ListedColormap(['white', 'black'])
bounds=[-1, 0, 1]
norm = colors.BoundaryNorm(bounds, cmap.N)


mag_vs_beta = []
E_per_spin_vs_beta = []

for B in beta:
    ### Initialize grid.
    for i in range(n):			# Iterate throught boxes in grid.
        for j in range(n):
            # Randomly decide whether or not to change the spin of the current box.
            x1, change = accept_reject(x1, .5)
        
            if change == True:
                v[i][j] = v[i][j] * -1

    #mag_vs_time = []

    ### Iterate through each box in the grid and decide whether or not to change the spin of each box.
    for iterate in range(iterations):
        #m = 0.
        for i in range(n):
            for j in range(n):
                I, J, I_up, I_down, J_left, J_right = determine_ij(i, j)
                
                x1, change = evaluate_E(I, J, I_up, I_down, J_left, J_right, v, x1)
            
                if change == True:
                    v[I][J] = v[I][J] * -1
            
                #m += v[I][J]
    
        #M = m / n**2
        #mag_vs_time.append((iterate, M))
        
    #m = 0
    e = 0
    for i in range(n):
        for j in range(n):
            #m += v[i][j]
            
            I, J, I_up, I_down, J_left, J_right = determine_ij(i, j)
                
            en = energy(I, J, I_up, I_down, J_left, J_right, v)
            
            e += en
            
    #M = m / n**2
    #mag_vs_beta.append((B, M))
    
    E = e / n**2
    E_per_spin_vs_beta.append((B, E))
    

    '''
    if iterate%10 == 0:
        print iterate
        
    if iterate%10 == 0:
   	plt.figure()
   	fig = plt.imshow(v, cmap = cmap,  interpolation='nearest', origin = 'lower')
   	plt.colorbar(fig, cmap=cmap, norm=norm, boundaries=bounds, ticks=[-1, 1])
   	plt.title(r'$\beta = $' + str(B) + '\n' + r'$J = $' + str(J_))    
    
	#plt.show()
	plt.savefig(directory + str("{0:0=4d}".format(iterate)) + '.png', format = 'png')
    '''
    
#time, mag = zip(*mag_vs_time)
#Beta, mag = zip(*mag_vs_beta)
Beta, Energy = zip(*E_per_spin_vs_beta)

'''
plt.plot(time, mag, color = 'purple', marker = 'o')
plt.title(r'$\beta$ = ' + str(B) + '\nn = ' + str(n**2), size = 20)
plt.xlabel('Time (Number of iterations)', size = 20)
plt.ylabel('Magnetization', rotation = 0, labelpad = 40, size = 20)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.xlim(0, iterations+1)
plt.show()
'''
'''
plt.plot(Beta, mag, color = 'purple', marker = 'o')
plt.title('Time = ' + str(iterations) + '\nn = ' + str(n**2), size = 20)
plt.xlabel(r'$\beta$', size = 20)
plt.ylabel('Magnetization', rotation = 0, labelpad = 40, size = 20)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.xlim(0, max(beta))
plt.show()
'''

plt.plot(Beta, Energy, color = 'purple', marker = 'o')
plt.title('Time = ' + str(iterations) + '\nn = ' + str(n**2), size = 20)
plt.xlabel(r'$\beta$', size = 20)
plt.ylabel('Energy\nper spin', rotation = 0, labelpad = 40, size = 20)
plt.xticks(fontsize = 16)
plt.yticks(fontsize = 16)
plt.xlim(0, max(beta))
plt.show()

