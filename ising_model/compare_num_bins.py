
import pickle
from scipy.optimize import curve_fit
import numpy as np
import matplotlib.pyplot as plt


file_1_name = 'test_04_no_bins.pkl'
file_2_name = 'test_09_no_bins.pkl'
file_3_name = 'test_10_no_bins.pkl'
file_4_name = 'test_04_1000_bins.pkl'
file_5_name = 'test_09_1000_bins.pkl'
file_6_name = 'test_10_1000_bins.pkl'

# file_2_name = 'test_04_3000_bins.pkl'
# file_3_name = 'test_04_2000_bins.pkl'
# file_4_name = 'test_04_1000_bins.pkl'
# file_5_name = 'test_04_500_bins.pkl'
# file_6_name = 'test_04_100_bins.pkl'
# file_7_name = 'test_04_20_bins.pkl'
# file_2_name = 'warms_2000_traj_10000_bins_500.pkl'
# file_3_name = 'warms_2000_traj_10000_bins_1000.pkl'
# file_4_name = 'warms_2000_traj_10000_bins_2000.pkl'
# file_5_name = 'second_warms_2000_traj_10000_bins_0.pkl'

with open(file_1_name, 'rb') as file_1:
    points_1 = pickle.load(file_1)
with open(file_2_name, 'rb') as file_2:
    points_2 = pickle.load(file_2)
with open(file_3_name, 'rb') as file_3:
    points_3 = pickle.load(file_3)
with open(file_4_name, 'rb') as file_4:
    points_4 = pickle.load(file_4)
with open(file_5_name, 'rb') as file_5:
    points_5 = pickle.load(file_5)
with open(file_6_name, 'rb') as file_6:
    points_6 = pickle.load(file_6)
# with open(file_7_name, 'rb') as file_7:
#     points_7 = pickle.load(file_7)
beta_1, chi_1, chi_sigma_1, C_1, C_sigma_1 = zip(*points_1)
beta_2, chi_2, chi_sigma_2, C_2, C_sigma_2 = zip(*points_2)
beta_3, chi_3, chi_sigma_3, C_3, C_sigma_3 = zip(*points_3)
beta_4, chi_4, chi_sigma_4, C_4, C_sigma_4 = zip(*points_4)
beta_5, chi_5, chi_sigma_5, C_5, C_sigma_5 = zip(*points_5)
beta_6, chi_6, chi_sigma_6, C_6, C_sigma_6 = zip(*points_6)
# beta_7, chi_7, chi_sigma_7, C_7, C_sigma_7 = zip(*points_7)

def fit_func(x, a, b, c):
    return a + b*(x - c)**2.

init_guess_chi = [max(chi_1), -1., beta_1[8]]

chi_start = 5
chi_end = 11

popt_chi, pconv_chi = curve_fit(fit_func, beta_1[chi_start:chi_end], chi_1[chi_start:chi_end], sigma = chi_sigma_1[chi_start:chi_end], p0 = init_guess_chi, maxfev = 1000000)
x_range_chi = np.linspace(beta_1[chi_start], beta_1[chi_end])
a_chi, b_chi, c_chi = popt_chi

init_guess_C = [max(C_1), -1., beta_1[12]]

C_start = 7
C_end = 14

popt_C, pconv_C = curve_fit(fit_func, beta_1[C_start:C_end], C_1[C_start:C_end], sigma = C_sigma_1[C_start:C_end], p0 = init_guess_C, maxfev = 1000000)
x_range_C = np.linspace(beta_1[C_start], beta_1[C_end])
a_C, b_C, c_C = popt_C

print 'chi: ', popt_chi[2], pconv_chi[2][2]**.5
print 'C: ', popt_C[2], pconv_C[2][2]**.5

plt.errorbar(beta_1, chi_1, chi_sigma_1, linewidth = 3, label = 'no bins 4th seed')
plt.errorbar(beta_4, chi_4, chi_sigma_4, linewidth = 3, label = '1000 bins 4th seed')
# plt.errorbar(beta_2, chi_2, chi_sigma_2, linewidth = 3, label = '3000 bins 1st seed')
plt.errorbar(beta_2, chi_2, chi_sigma_2, linewidth = 3, label = 'no bins 9th seed')
plt.errorbar(beta_5, chi_5, chi_sigma_5, linewidth = 3, label = '1000 bins 5th seed')
# plt.errorbar(beta_3, chi_3, chi_sigma_3, linewidth = 3, label = '2000 bins 1st seed')
plt.errorbar(beta_3, chi_3, chi_sigma_3, linewidth = 3, label = 'no bins 10th seed')
plt.errorbar(beta_6, chi_6, chi_sigma_6, linewidth = 3, label = '1000 bins 10th seed')
# plt.errorbar(beta_4, chi_4, chi_sigma_4, linewidth = 3, label = '1000 bins 1st seed')
# plt.errorbar(beta_5, chi_5, chi_sigma_5, linewidth = 3, label = '500 bins 1st seed')
# plt.errorbar(beta_6, chi_6, chi_sigma_6, linewidth = 3, label = '100 bins 1st seed')
# plt.errorbar(beta_7, chi_7, chi_sigma_7, linewidth = 3, label = '20 bins 1st seed')
# plt.plot(x_range_chi, fit_func(x_range_chi, a_chi, b_chi, c_chi), color = 'black', linewidth = 3, linestyle = '--', label = 'fit', zorder = 10)
plt.grid(linestyle = '--')
plt.xlabel(r'$\beta$')
plt.ylabel(r'$\chi$', rotation = 0)
plt.legend()
plt.show()

plt.errorbar(beta_1, C_1, C_sigma_1, linewidth = 3, label = 'no bins 4th seed')
plt.errorbar(beta_4, C_4, C_sigma_4, linewidth = 3, label = '1000 bins 4th seed')
# plt.errorbar(beta_2, C_2, C_sigma_2, linewidth = 3, label = '3000 bins 1st seed')
plt.errorbar(beta_2, C_2, C_sigma_2, linewidth = 3, label = 'no bins 9th seed')
plt.errorbar(beta_5, C_5, C_sigma_5, linewidth = 3, label = '1000 bins 9th seed')
# plt.errorbar(beta_3, C_3, C_sigma_3, linewidth = 3, label = '2000 bins 1st seed')
plt.errorbar(beta_3, C_3, C_sigma_3, linewidth = 3, label = 'no bins 10th seed')
plt.errorbar(beta_6, C_6, C_sigma_6, linewidth = 3, label = '1000 bins 10th seed')
# plt.errorbar(beta_4, C_4, C_sigma_4, linewidth = 3, label = '1000 bins 1st seed')
# plt.errorbar(beta_5, C_5, C_sigma_5, linewidth = 3, label = '500 bins 1st seed')
# plt.errorbar(beta_6, C_6, C_sigma_6, linewidth = 3, label = '100 bins 1st seed')
# plt.errorbar(beta_7, C_7, C_sigma_7, linewidth = 3, label = '20 bins 1st seed')
# plt.plot(x_range_C, fit_func(x_range_C, a_C, b_C, c_C), color = 'black', linewidth = 3, linestyle = '--', label = 'fit', zorder = 10)
plt.grid(linestyle = '--')
plt.xlabel(r'$\beta$')
plt.ylabel('C', rotation = 0)
plt.legend()
plt.show()
