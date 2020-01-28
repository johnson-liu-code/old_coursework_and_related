
import pickle
import numpy as np
from scipy.optimize import curve_fit
import scipy.optimize as opt
import matplotlib.pyplot as plt


file_name = '/home/jliu/Desktop/files/pet_projects/ising_model/test_mag_list_energy_list_vs_beta_09/mag_list_energy_list_vs_beta.pkl'
with open(file_name, 'rb') as plk_file:
    data = pickle.load(plk_file)

beta, mag_squared, mag, energy_squared, energy = zip(*data)
chi_list = []
C_list = []

points = []

num_bins = 10

for i, b in enumerate(beta):
    mag_list = mag[i]
    plt.hist(mag_list, bins = 100)
    plt.title(r'$\beta = $' + str(b))
    plt.show()
    # print mag_list[:100]
    # mag_list = np.array_split(mag[i][:100], num_bins)
    # print mag_list
    # mag_list = [np.mean(x) for x in mag_list]
    # print mag_list
    # mag_squared_list = mag_squared[i]

    # energy_list = energy[i]
    energy_list = np.array_split(energy[i], num_bins)
    energy_list = [np.mean(x) for x in energy_list]

    # energy_squared_list = energy_squared[i]

    mag_squared_list = np.array(mag_list)**2.
    # print mag_squared_list
    energy_squared_list = np.array(energy_list)**2.

    # mag_list = np.array_split(mag_list, num_bins)
    # mag_squared_list = np.array_split(mag_squared_list, num_bins)
    # energy_list = np.array_split(energy_list, num_bins)
    # energy_squared_list = np.array_split(energy_squared_list, num_bins)

    mag_mean = np.mean(mag_list)
    # print mag_mean
    mag_squared_mean = np.mean(mag_squared_list)
    # print mag_squared_mean
    energy_mean = np.mean(energy_list)
    energy_squared_mean = np.mean(energy_squared_list)

    length = len(mag_list)
    ##for j in range(length):
    ##    fake_mag_list = mag_list - mag_list[j]


    # chi = b * ( np.mean(mag_squared_list) - np.mean(mag_list)**2. )
    # C = b**2. * ( np.mean(energy_squared_list) - np.mean(energy_list)**2. )
    chi = b * ( mag_squared_mean - mag_mean**2. )
    C = b**2. * ( energy_squared_mean - energy_mean**2. )
    # print chi
    fake_chi_list = []
    fake_C_list = []

    #length = len(mag_list)
    mag_j_list = []
    mag_squared_j_list = []
    energy_j_list = []
    energy_squared_j_list = []


    # for j, itm in enumerate(mag_list):
    '''
    for j in range(length):
        mag_j_mean = ( length * mag_mean - mag_list[j] ) / (length - 1.)
        # print mag_j_mean
        mag_squared_j_mean = ( length * mag_squared_mean - mag_squared_list[j] ) / (length - 1.)
        # print mag_squared_mean
        energy_j_mean = ( length * energy_mean - energy_list[j] ) / (length - 1.)
        energy_squared_j_mean = ( length * energy_squared_mean - energy_squared_list[j] ) / (length - 1.)

        fake_chi = b * ( mag_squared_j_mean - mag_j_mean**2. )
        # print fake_chi
        fake_C = b**2. * ( energy_squared_j_mean - energy_j_mean**2. )

        # print fake_chi
    '''
    #     fake_mag_list = mag_list
    #     del fake_mag_list[j]
    #     fake_mag_squared_list = mag_squared_list
    #     del fake_mag_squared_list[j]
    #     fake_energy_list = energy_list
    #     del fake_energy_list[j]
    #     fake_energy_squared_list = energy_squared_list
    #     del fake_energy_squared_list[j]
    #
    #     fake_chi = b * ( np.mean(fake_mag_squared_list) - np.mean(fake_mag_list)**2. )
    #     fake_C = b**2. * ( np.mean(fake_energy_squared_list) - np.mean(fake_energy_list)**2. )
    #
        # fake_chi_list.append(fake_chi)
        # fake_C_list.append(fake_C)

    # print fake_chi_list
    # print chi
    # print fake_C_list
    # print (length - 1. ) / length
    # print ( (length - 1. ) / length ) * (fake_chi_list - chi)**2.
    # chi_sigma = ( ( ( length - 1. )/length ) * np.sum( ( np.array(fake_chi_list) - chi)**2. ) )**.5
    # print np.array(fake_chi_list) - chi
    # C_sigma = ( ( ( length - 1. )/length ) * np.sum( ( np.array(fake_C_list) - C)**2. ) )**.5
    # print chi_sigma
    # print C_sigma

    # chi_sigma = np.sqrt(len(mag_list)) * np.std(fake_chi_list)
    # C_sigma = np.sqrt(len(mag_list)) * np.std(fake_C_list)

    # length = len(mag_list)
    # chi_sigma = ( (length - 1. ) * np.sum( (np.array(fake_chi_list - chi)**2. ) / length ) )**.5
    # C_sigma = ( (length - 1. ) * np.sum( (np.array(fake_C_list - C)**2. ) / length ) )**.5

    #points.append( (b, chi, C) )
    # points.append( (b, chi, chi_sigma, C, C_sigma) )
    # print fake_chi_list
    # print chi
    # (n, bins, patches) = plt.hist(fake_chi_list, bins = 'auto', align = 'mid')
    # # print n
    # # print bins
    # plt.title(r'$\beta$ = ' + str(b))
    # plt.xticks(rotation = -45)
    # plt.grid()
    # plt.show()

#print fake_chi_list
#print fake_C_list


#beta, chi, C = zip(*points)
# beta, chi, chi_sigma, C, C_sigma = zip(*points)

# file_name = 'test_09_1000_bins.pkl'
# with open(file_name, 'wb') as out_file:
#     pickle.dump(points, out_file)


# print chi_sigma
# print C_sigma
'''

#plt.plot(beta, chi)
plt.errorbar(beta, chi, chi_sigma)
plt.grid(linestyle = '--')
plt.xlabel(r'$\beta$')
plt.ylabel(r'$\chi$', rotation = 0)
plt.show()
#plt.plot(beta, C)
plt.errorbar(beta, C, C_sigma)
plt.grid(linestyle = '--')
plt.xlabel(r'$\beta$')
plt.ylabel('C', rotation = 0)
plt.show()
'''
