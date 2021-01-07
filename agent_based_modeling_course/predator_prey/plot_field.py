


import sys
import pickle
import numpy as np
from numpy import random
import matplotlib
import matplotlib.pyplot as plt
from matplotlib import colors
import matplotlib.animation as animation



data_file_name = sys.argv[1]
save_fig_name = sys.argv[2]


with open(data_file_name, 'rb') as datafile:
    data = pickle.load(datafile)[:100]


prey, pred, nutrients = zip(*data)

x_len = len(prey[0])
y_len = len(prey[0][0])

data_len = len(prey)

prey_over_time = []
pred_over_time = []
nutrients_over_time = []

for t in range(data_len):
    prey_total = 0
    pred_total = 0
    nutrient_total = 0

    for i in range(x_len):
        for j in range(y_len):
            prey_total = prey_total + prey[t][i][j] 
            pred_total = pred_total + pred[t][i][j]
            nutrient_total = nutrient_total + nutrients[t][i][j]

    prey_over_time.append(prey_total)
    pred_over_time.append(pred_total)
    nutrients_over_time.append(nutrient_total)


prey_over_time = np.array( prey_over_time ) / max(prey_over_time)
pred_over_time = np.array( pred_over_time ) / max(pred_over_time)
nutrients_over_time = np.array( nutrients_over_time ) / max(nutrients_over_time)

'''
#plt.plot(prey_over_time, label = 'Prey', linewidth = .5)
#plt.plot(pred_over_time, label = 'Pred', linewidth = .5)
#plt.plot(nutrients_over_time, label = 'Nutrients', linewidth = .5)

fig, ( (ax1, ax2), (ax3, ax4) ) = plt.subplots(2,2)

#plt.plot(prey_over_time, pred_over_time, label = 'Predator vs Prey')
#plt.plot(prey_over_time, nutrients_over_time, label = 'Nutrients vs Prey')
#plt.plot(pred_over_time, nutrients_over_time, label = 'Nutriens vs Predator')

ax1.plot(prey_over_time, pred_over_time, label = 'Predator vs Prey')
ax1.plot(prey_over_time, nutrients_over_time, label = 'Nutrients vs Prey')
ax1.plot(pred_over_time, nutrients_over_time, label = 'Nutriens vs Predator')

ax1.grid(linestyle = '--')
ax1.legend()

ax2.plot(prey_over_time, pred_over_time, label = 'Predator vs Prey', color = 'C0')
ax2.grid(linestyle = '--')
ax2.legend() 

ax3.plot(prey_over_time, nutrients_over_time, label = 'Nutrients vs Prey', color = 'C1')
ax3.grid(linestyle = '--')
ax3.legend()

ax4.plot(pred_over_time, nutrients_over_time, label = 'Nutrients vs Predator', color = 'C2')
ax4.grid(linestyle = '--')
ax4.legend()

#plt.show()

plt.savefig(save_fig_name + '.png')
'''

x = np.linspace(0, len(data), len(data))

data = [prey_over_time, pred_over_time, nutrients_over_time]

fig, ( (ax1, ax2), (ax3, ax4) ) = plt.subplots(2, 2)
lines1 = []

#line1, = ax.plot(x, prey_over_time, linewidth = .5)
#line2, = ax.plot(x, pred_over_time, linewidth = .5)
#line3, = ax.plot(x, nutrients_over_time, linewidth = .5)

colors = ['blue', 'red', 'green']
labels = ['Prey', 'Predator', 'Nutrients']

for i in range(3):
    line, = ax1.plot(x, data[i], color = colors[i], linewidth = .5, label = labels[i])
    lines1.append(line)

ax1.set_title('Prey-Predator-Nutrients')
ax1.legend()

ax1.grid(linestyle = '--')


axes = [ax2, ax3, ax4]
groups = [ [0,1], [0,2], [1,2] ]

mult_lines = []

for i in range(3):
    line1, = axes[i].plot(x, data[ groups[i][0] ], color = colors[ groups[i][0] ] )
    line2, = axes[i].plot(x, data[ groups[i][1] ], color = colors[ groups[i][1] ] )

    lines = [line1, line2]

    mult_lines.append( lines )

line111, = ax1.plot(x, prey_over_time, color = 'blue', linewidth = .5)
line112, = ax1.plot(x, pred_over_time, color = 'red', linewidth = .5)
line113, = ax1.plot(x, nutrients_over_time, color = 'green', linewidth = .5)

line121, = ax2.plot(x, prey_over_time, color = 'blue', linewidth = .5)
line122, = ax2.plot(x, pred_over_time, color = 'red', linewidth = .5)

ax2.set_title('Prey-Predator')
ax2.grid(linestyle = '--')

line211, = ax3.plot(x, prey_over_time, color = 'blue', linewidth = .5)
line212, = ax3.plot(x, nutrients_over_time, color = 'green', linewidth = .5)

ax3.set_title('Prey-Nutrients')
ax3.grid(linestyle = '--')

line221, = ax4.plot(x, pred_over_time, color = 'red', linewidth = .5)
line222, = ax4.plot(x, nutrients_over_time, color = 'green', linewidth = .5)

ax4.set_title('Predator-Nutrients')
ax4.grid(linestyle = '--')

ax1.legend()

fig.tight_layout()

plt.savefig(save_fig_name + '.png')

#def animate(t, x, prey_over_time, pred_over_time, nutrients_over_time, line1, line2, line3):
#     line1.set_data(x[:t], prey_over_time[:t])
#     line2.set_data(x[:t], pred_over_time[:t])
#     line3.set_data(x[:t], nutrients_over_time[:t])

#     return [line1, line2, line3]

#mult_lines = [ [line121, line122], [line211, line212], [line221, line222] ]
'''
def animate(t, x, data, lines1):
#def animate(t, x, data, lines1, line121, line122, line211, line212, line221, line222):
    for lnum, line in enumerate(lines1):
        line.set_data( x[:t], data[lnum][:t] )

    #line121.set_data( x[:t], data[0][:t] )
    #line122.set_data( x[:t], data[1][:t] )

    #line211.set_data( x[:t], data[0][:t] )
    #line212.set_data( x[:t], data[2][:t] )

    #line221.set_data( x[:t], data[1][:t] )
    #line222.set_data( x[:t], data[2][:t] )

    #for gnum, group in enumerate(groups):
    #    mult_lines[gnum][0].set_data( x[:t], data[group[0]][:t] )
    #    mult_lines[gnum][1].set_data( x[:t], data[group[1]][:t] )

    return lines1
    #return lines1, line121, line122, line211, line212, line221, line222

#args = [x, prey_over_time, pred_over_time, nutrients_over_time, line1, line2, line3]
args = [x, data, lines1]
#args = [x, data, lines1, line121, line122, line211, line212, line221, line222]

ani = animation.FuncAnimation(fig, animate, data_len, fargs = args, blit = True)

fig.tight_layout()

ani.save(save_fig_name + '.mp4', fps = 15)
'''

######################################################################################
"""
extent = [-0.5, x_len-0.5, -0.5, y_len-0.5]

#xticks = np.arange(0, x_len, 1)
#yticks = np.arange(0, y_len, 1)

#print(xticks)
#print(extent)

#print(animals)
max1 = max( max( map( max, prey ) ) )
#print(max1)
cmap1 = plt.get_cmap('Blues', max1 + 1)
ticks1 = np.arange(0, max1 + 1)
boundaries1 = np.arange(-0.5, max1 + 1.5)

max2 = max( max( map( max, nutrients ) ) )
#print(max2)
cmap2 = plt.get_cmap('summer_r', max2 + 1)
ticks2 = np.arange(0, max2 + 1, 100)
boundaries2 = np.arange(-0.5, max2 + 1.5)

max3 = max( max( map( max, pred ) ) )
cmap3 = plt.get_cmap('Reds', max3 + 1)
ticks3 = np.arange(0, max3 + 1, 2)
boundaries3 = np.arange(-0.5, max3 + 1.5) 


def animate(t):
    #plt.cla()

    #plt.xticks(xticks)
    #plt.yticks(yticks)

    #fig, (cax1, ax1, ax2, cax2) = plt.subplots(1, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

    #max1 = max( map( max, data[t][0] ) )
    #cmap1 = plt.get_cmap('cool', max1+1)

    #im1 = ax1.imshow(data[t][0], cmap=cmap1, vmin = -.5, vmax = max1+.5, extent=extent)
    im1.set_data(data[t][0])
    #ax1.set_xticks(xticks)
    #ax1.set_yticks(yticks)

    #ticks1 = np.arange(0, max1+1)
    #boundaries1 = np.arange(-0.5, max1+1.5)
    #cb1 = matplotlib.colorbar.ColorbarBase(cax1, cmap=cmap1, ticks=ticks1, boundaries=boundaries1)

    #max2 = max( map( max, data[t][1] ) )
    #cmap2 = plt.get_cmap('summer_r', max2+1)

    #im2 = ax2.imshow(data[t][1], cmap=cmap2, vmin = 0, vmax = max2, extent=extent)
    im2.set_data(data[t][2])
    #ax2.set_xticks(xticks)
    #ax2.set_yticks(yticks)

    #ticks2 = np.arange(0, max2+1, 10)
    #boundaries2 = np.arange(-0.5, max2+1.5)
    #cb2 = matplotlib.colorbar.ColorbarBase(cax2, cmap=cmap2, ticks=ticks2, boundaries=boundaries2)

    im3.set_data(data[t][1])

    #fig.tight_layout()


fig, ( (cax1, ax1, ax2, cax2), (cax3, ax3, ax4, cax4) ) = plt.subplots(2, 4, gridspec_kw = {'width_ratios':[5, 50, 50, 5]})

im1 = ax1.imshow(data[0][0], cmap=cmap1, vmin = -.5, vmax = max1+.5, extent=extent)
im2 = ax2.imshow(data[0][2], cmap=cmap2, vmin = 0, vmax = max2, extent=extent)
im3 = ax3.imshow(data[0][1], cmap=cmap3, vmin = -.5, vmax = max3+.5, extent=extent)

ax1.set_title('Prey')
ax2.set_title('Nutrients')
ax3.set_title('Predators')

cb1 = matplotlib.colorbar.ColorbarBase(cax1, cmap=cmap1, ticks=ticks1, boundaries=boundaries1)
cb2 = matplotlib.colorbar.ColorbarBase(cax2, cmap=cmap2, ticks=ticks2, boundaries=boundaries2)
cb3 = matplotlib.colorbar.ColorbarBase(cax3, cmap=cmap3, ticks=ticks3, boundaries=boundaries3)

#ax1.set_xticks(xticks)
#ax1.set_yticks(yticks)

#ax2.set_xticks(xticks)
#ax2.set_yticks(yticks)

#ax3.set_xticks(xticks)
#ax3.set_yticks(yticks)

fig.tight_layout()

ani = animation.FuncAnimation( fig, animate, len(data) )

#plt.show()

ani.save(save_fig_name + '.mp4', fps = 10)
"""
