


import sys
import numpy as np
import pickle
import json
import matplotlib.pyplot as plt
import matplotlib.animation as animation


save_file_name = sys.argv[1] + '.pkl'

class agent:
    def __init__(self, num, x_dim_len, y_dim_len, friend = None, enemy = None):
        self.personality = np.random.choice( ['hero', 'coward', 'villain'] )
        #self.personality = 'hero'
        #self.personality = 'coward'
        #self.personality = 'villain'

        self.friend = friend
        self.enemy = enemy

        self.num = num
        self.x_loc = np.random.uniform(x_dim_len)
        self.y_loc = np.random.uniform(y_dim_len)


def choose_rand_agent(agent_list):
    return np.random.choice(agent_list)


if __name__ == '__main__':
    num_agents = 50
    x_dim_len = 10
    y_dim_len = 10
    sim_len = 500

    agent_list = [ agent(i, x_dim_len, y_dim_len) for i in range(num_agents)]

    for agent in agent_list:
        #print(agent.x_loc)
        agent.friend = choose_rand_agent(agent_list)
        while agent.num == agent.friend.num:
            agent.friend = choose_rand_agent(agent_list)

        agent.enemy = choose_rand_agent(agent_list)
        while agent.num == agent.enemy.num or agent.enemy.num == agent.friend.num:
            agent.enemy = choose_rand_agent(agent_list)


    #for agent in agent_list:
        #print(agent.num, agent.friend.num, agent.enemy.num)
        #print(agent.num, agent.x_loc, agent.y_loc)
        #print(agent.num, agent.personality)

    #lattice = [ [None for j in range(y_dim_len)] for i in range(x_dim_len) ]

    data = []

    for t in range(sim_len):
        for agent in agent_list:
            if agent.personality == 'hero':
                target_x = (1./2)*( agent.friend.x_loc + agent.enemy.x_loc )
                target_y = (1./2)*( agent.friend.y_loc + agent.enemy.y_loc )

            elif agent.personality == 'coward':
                target_x = agent.x_loc + (1./2)*( agent.friend.x_loc - agent.enemy.x_loc )
                target_y = agent.y_loc + (1./2)*( agent.friend.y_loc - agent.enemy.y_loc )

            elif agent.personality == 'villain':
                target_x = agent.enemy.x_loc
                target_y = agent.enemy.y_loc

            if target_x > agent.x_loc:
                agent.x_loc += .1

            else:
                agent.x_loc -= .1

            if target_y > agent.y_loc:
                agent.y_loc += .1
            else:
                agent.y_loc -= .1

            if agent.x_loc > x_dim_len:
                #agent.x_loc = 0
                agent.x_loc = x_dim_len
            elif agent.x_loc < 0:
                #agent.x_loc = x_dim_len
                agent.x_loc = 0

            if agent.y_loc > y_dim_len:
                #agent.y_loc = 0
                agent.y_loc = y_dim_len
            elif agent.y_loc < 0:
                #agent.y_loc = y_dim_len
                agent.y_loc = 0

            #print(agent.x_loc)

        #temp = agent_list[:]

        #xy = [ (agent.x_loc, agent.y_loc) for agent in agent_list ]

        xy_personality = [ (agent.x_loc, agent.y_loc, agent.personality) for agent in agent_list ]

        #data.append( xy )
        #data.append( agent_list[:] )
        data.append( xy_personality )

    #print(data[0] == data[5])


    with open(save_file_name, 'wb') as save_file:
        pickle.dump(data, save_file)
        #save_file.write(data)
        #save_file.write(json.dumps(data))

'''
xy = [ (agent.x_loc, agent.y_loc) for agent in agent_list ]
#y = [ agent.y_loc for agent in agent_list ]
x, y = zip(*xy)


plt.scatter(x, y)

plt.show()
'''
'''
fig = plt.figure()

def init():
    x, y = zip(*data[0])
    plt.scatter(x, y)
    plt.xlim([-.01, 10.01])
    plt.ylim([-.01, 10.01])
    #return fig

def animate(t):
    plt.cla()
    plt.xlim([-.01, 10.01])
    plt.ylim([-.01, 10.01])
    x, y = zip(*data[t])
    plt.scatter( x, y )
    #return fig

ani = animation.FuncAnimation(fig, animate, init_func = init, frames = len(data))
ani.save('test.gif', fps = 20)
'''



'''
fig = plt.figure()
plts = []
for t in range(len(data)):
    plt.cla()
    x, y = zip(*data[t])
    p = plt.scatter(x, y)
    plts.append([p])

ani = animation.ArtistAnimation(fig, plts, interval=100, blit=True, repeat_delay=10)
ani.save('test.gif', writer = 'imagemagick', fps = 15)
'''
