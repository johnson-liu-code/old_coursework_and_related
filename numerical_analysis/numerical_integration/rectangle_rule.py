
import numpy as np
import matplotlib.pyplot as plt



def f(x):
    #return x*np.exp(-x) + 1
    return x + np.cos(x)

end = 10

x = np.linspace(0, end, 1000)



plt.plot(x, f(x))

for i in range(end):
    rectangle = plt.Rectangle((i, 0), 1, f(i), color = 'cyan', alpha = .5 )
    plt.gca().add_patch(rectangle)

plt.xlim(x[0], x[-1])
plt.ylim(0, f(x[-1]))

plt.grid(linestyle = '--')

plt.xlabel(r'$x$', size = 24)
plt.ylabel(r'$f(x)$', size = 24, rotation = 0, labelpad = 20)

plt.xticks(fontsize = 20)
plt.yticks(fontsize = 20)

plt.show()
