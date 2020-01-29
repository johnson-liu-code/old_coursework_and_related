import matplotlib.pyplot as plt


with open('converge_sum_data.txt', 'r') as fil:
    points = [ ( float(line.split()[0]), float(line.split()[1]) ) for line in fil.readlines()[0:200] ]

i, sum = zip(*points)

plt.plot([i[0], i[-1]], [-0.69314768055925257695, -0.69314768055925257695], color = 'red', label = 'y = -0.69314768055925257695', linewidth = 3)
plt.plot(i, sum, label = 'Partial Sum')

plt.grid(linestyle = '--')

plt.xlabel('Iteration', size = 24)
plt.ylabel('Partial Sum', size = 24)

plt.xticks(size = 20)
plt.yticks(size = 20)

plt.legend(prop = {'size': 20})

plt.show()
