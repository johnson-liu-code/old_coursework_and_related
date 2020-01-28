
import pickle
import matplotlib.pyplot as plt


with open('save_chi_C_vs_beta.pkl', 'rb') as outfile:
    data = pickle.load(outfile)

chi_vs_beta = data[0]
C_vs_beta = data[1]
mag_vs_beta = data[2]

beta, mag = zip(*mag_vs_beta)

plt.plot(beta, mag)
plt.xlabel(r'$\beta$')
plt.ylabel('Avg S', rotation = 0)
plt.grid()
plt.show()
