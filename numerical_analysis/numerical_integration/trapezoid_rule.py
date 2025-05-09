
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches


def f(x):
    #return x*np.exp(-x) + 1
    return x + np.cos(x)

end = 10
x = np.linspace(0, end, 1000)


plt.plot(x, f(x))

for i in range(0,end,2):
    x_loc = [i, i+2, i+2, i]
    y_loc = [0, 0, f(i+2), f(i)]
    plt.gca().add_patch(patches.Polygon( xy=zip(x_loc,y_loc), color = 'cyan', alpha = .5 ) )

plt.xlim(x[0], x[-1])
plt.ylim(0, f(x[-1]))

plt.grid(linestyle = '--')

plt.xlabel(r'$x$', size = 24)
plt.ylabel(r'$f(x)$', size = 24, rotation = 0, labelpad = 20)

plt.xticks(fontsize = 20)
plt.yticks(fontsize = 20)

plt.show()
