



import sys
import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import matplotlib.animation as animation


csv_file_name = sys.argv[1]

save_file_name = sys.argv[2] + '.gif'

with open(csv_file_name) as fil:
    lines = fil.readlines()



#money_list = [ int(x) for x in lines[7].split(',')[2][2:-3].split() ]
#print(money_list)
#print(lines[-1])

#data = []
#for line in lines[7:]:
#    money_list = [ int(x) for x in line.split(',')[2][2:-3].split() ]
#    data.append(money_list)

#data = [ [ int(x) for x in line.split(',')[2][2:-3].split() ] for c, line in enumerate(lines[7:]) if c%200 == 0 ]
#data = [ [ int(x) for x in line.split(',')[2][2:-3].split() ] for c, line in enumerate(lines[7:]) ]
data = [ [ int(x) for x in line.split(',')[2][2:-3].split() ] for c, line in enumerate(lines[-1:])]
#print(data[0])
#print(len(data))
#print(max(data[-1]))

def func(x, a, b):
    return a*np.exp(-b*x)

bins = np.arange(0, 551, 10)
#print(bins)
xticks = np.arange(0, 501, 50)
#print(xticks)

bin_heights, bin_borders, _ = plt.hist(data[0], bins=bins, label='Raw Data')
bin_centers = bin_borders[:-1] + np.diff(bin_borders) / 2
popt, pcov = curve_fit(func, bin_centers, bin_heights, p0=[1., 1.])

print(popt)
print(pcov)

x_interval_for_fit = np.linspace(bin_borders[0], bin_borders[-1], 10000)
plt.plot(x_interval_for_fit, func(x_interval_for_fit, *popt), label='Boltzmann-Like Distribution', linewidth = 4)

plt.yscale('log')

plt.xlabel('Wealth')
plt.ylabel('Number of Individuals')

plt.xlim([-1, 501])
plt.xticks(xticks)

plt.grid()
plt.legend()

#plt.show()

#plt.savefig('boltzmann_02_logy.png')

'''
#plt.hist(data[1000], bins = bins)
plt.hist(data, bins = bins)

plt.grid()
plt.xticks(xticks)
plt.xlim([-1, 501])
plt.ylim([0, 40])

plt.xlabel('Wealth')
plt.ylabel('Number of Individuals')

plt.show()
#plt.savefig('50000_ticks.png')
'''
'''
fig = plt.figure()
plts = []
for dat in data[:2]:
    f = plt.hist(dat, bins = bins, align = 'left')
    plts.append([f])

ani = animation.ArtistAnimation(fig, plts, interval=100, blit=True, repeat_delay=10)
#ani.save(save_file_name, writer = 'imagemagick', fps = 15)


plt.show()
'''
'''
def animate(i):
    plt.cla()
    #plt.title('tick = {}'.format(i*100))
    plt.title('tick = {}'.format(i*200))
    plt.hist(data[i], bins = bins)
    plt.xticks(xticks)
    plt.xlim([-1, 551])
    #plt.ylim([0, 60])
    plt.grid(linestyle = '--')
    plt.xlabel('Wealth')
    plt.ylabel('Number of individuals')

fig = plt.figure()
hist = plt.hist(data[0], bins = bins)
plt.xticks(xticks)
plt.xlim([-1, 551])
#plt.ylim([0, 60])
plt.grid(linestyle = '--')
plt.xlabel('Wealth')
plt.ylabel('Number of individuals') 

ani = animation.FuncAnimation(fig, animate, len(data))
#plt.show()
ani.save(save_file_name, fps = 100)
'''
'''
test_data = data[-1]
#print(test_data)
sorted_data = sorted(test_data)[::-1]
#print(sorted_data)
top_10_percent_wealth = sum(sorted_data[:50])
#print(top_10_percent_wealth)
bottom_50_percent_wealth = sum(sorted_data[250:])
#print(bottom_50_percent_wealth)

cumsum = np.cumsum(sorted_data)/100

plt.plot(sorted_data, label = 'Wealth from richest to poorest')
plt.plot(cumsum, label = 'Cumulative wealth (Divided by 100)')

plt.xlabel('Individuals (from richest to poorest)')
plt.ylabel('Individual wealth')

plt.xlim([-1, len(sorted_data)])

plt.grid(linestyle = '--')

plt.legend(loc = 'center right')

plt.show()

#plt.savefig('cumsum.png')
'''
'''
top_data = []
#mid_data = []
bot_data = []

for dat in data:
    sorted_data = sorted(dat)[::-1]
    top_10_percent_wealth = sum(sorted_data[:50])
    #mid_40_percent_wealth = sum(sorted_data[50:250])
    bot_50_percent_wealth = sum(sorted_data[250:])

    top_data.append(top_10_percent_wealth)
    #mid_data.append(mid_40_percent_wealth)
    bot_data.append(bot_50_percent_wealth)


plt.plot(top_data, label = 'Top 10%')
#plt.plot(mid_data, label = 'Mid 40%')
plt.plot(bot_data, label = 'Bottom 50%')

plt.xlabel('Simluation Time')
plt.ylabel('Total Wealth')

plt.xlim([-2, len(data)+1])
plt.ylim([0, max(bot_data)])

plt.grid(linestyle = '--')

plt.legend()

#plt.show()

plt.savefig('top_v_bot.png')
'''
