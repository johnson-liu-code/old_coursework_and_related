



import sys
import pickle
import matplotlib.pyplot as plt
import matplotlib.animation as animation


data_file_name = sys.argv[1]
save_file_name = sys.argv[2] + '.gif'


with open(data_file_name, 'rb') as data_file:
    #data = pickle.load(data_file)[:400]
    data = pickle.load(data_file)

'''
heroes = [ agent for agent in data[0] if agent[2] == 'hero' ]
if len(heroes) > 0:
    hx, hy, hp = zip(*heroes)
cowards = [ agent for agent in data[0] if agent[2] == 'coward' ]
if len(cowards) > 0:
   cx, cy, cp = zip(*cowards)

#print('heroes: ', heroes)
#print('cowards: ', cowards)

fig = plt.figure()

plt.scatter(cx, cy, c = 'red')
plt.show()
'''


'''
fig = plt.figure()

def init():
    heroes = [ agent for agent in data[0] if agent[2] == 'hero' ]
    if len(heroes) > 0:
        hx, hy, hp = zip(*heroes)
        plt.scatter(hx, hy, c = 'blue')

    cowards = [ agent for agent in data[0] if agent[2] == 'coward' ]
    if len(cowards) > 0:
        cx, cy, cp = zip(*cowards)
        plt.scatter(cx, cy, c = 'red')

    #plt.title('Heroes and Cowards')
    #plt.title('All Heroes')
    plt.title('All Cowards')
    plt.xlim([-.01, 10.01])
    plt.ylim([-.01, 10.01])
    plt.grid(linestyle = '--')
    plt.axes().set_aspect('equal')

def animate(t):
    plt.cla()
    heroes = [ agent for agent in data[t] if agent[2] == 'hero' ]
    if len(heroes) > 0:
        hx, hy, hp = zip(*heroes)
        plt.scatter(hx, hy, c = 'blue')

    cowards = [ agent for agent in data[t] if agent[2] == 'coward' ]
    if len(cowards) > 0:
        cx, cy, cp = zip(*cowards)
        plt.scatter(cx, cy, c = 'red')

    #plt.cla()
    #plt.title('Heroes and Cowards')
    #plt.title('All Heroes')
    plt.title('All Cowards')
    plt.xlim([-.01, 10.01])
    plt.ylim([-.01, 10.01])
    #x, y, color = zip(*data[t])
    #plt.scatter( x, y )
    plt.grid(linestyle = '--')
    plt.axes().set_aspect('equal')
    #return fig

ani = animation.FuncAnimation(fig, animate, init_func = init, frames = len(data))
#plt.show()
ani.save(save_file_name, fps = 30)
#ani.save('streaks', fps = 30)
'''

fig = plt.figure()

for i in range(len(data)):
    #if i%4 == 0:
        plt.cla()

        heroes = [ agent for agent in data[i] if agent[2] == 'hero' ]
        if len(heroes) > 0:
            hx, hy, hp = zip(*heroes)
            plt.scatter(hx, hy, c = 'blue')

        cowards = [ agent for agent in data[i] if agent[2] == 'coward' ]
        if len(cowards) > 0:
            cx, cy, cp = zip(*cowards)
            plt.scatter(cx, cy, c = 'red')

        villains = [ agent for agent in data[i] if agent[2] == 'villain' ]
        if len(villains) > 0:
            vx, vy, vp = zip(*villains)
            plt.scatter(vx, vy, c = 'orange')

        #plt.title('Heroes and Cowards')
        #plt.title('All Heroes')
        #plt.title('All Cowards')
        #plt.title('All Villains')
        plt.title('Mix')
        plt.xlim([-.01, 10.01])
        plt.ylim([-.01, 10.01])
        plt.grid(linestyle = '--')
        plt.axes().set_aspect('equal')
        plt.savefig('mix/mix_test_01-{:03d}'.format(i))
        #plt.savefig('mix/mix_test_01-{:03d}'.format(int(i/4)))
        #plt.savefig('mix_heroes_and_cowards_movie_02/mix_heroes_and_cowards-{:03d}'.format(int(i/4)))
