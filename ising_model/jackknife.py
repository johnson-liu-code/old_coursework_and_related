
import numpy as np
import matplotlib.pyplot as plt


def jackknife_err(value_list):
    values = np.array(value_list)
    mean = np.mean(values)
    length = len(values)
    xj_list = []

    for j in range(length):
        xj = (length * mean - value_list[j] ) / (length - 1)
        xj_list.append(xj)

    fake_xj = np.array(xj_list)
    sigma = np.sum( (fake_xj - mean)**2. )**.5

    return sigma


def compute_chi_err(polyakov, Ls):
    chi = Ls**3. * np.var(polyakov)
    length = float(len(polyakov))
    P = np.array(polyakov)
    P_sum = sum(P)
    P2_sum = sum(P*P)
    Pj_avg = (P_sum - P)/(length - 1.)
    P2_j_avg = (P2_sum - P*P)/(length - 1.)
    chi_fake = Ls**3. * (P2_j_avg - Pj_avg**2.)

    chi_fake_avg = np.mean(chi_fake)
    chi_fake_avg_sq = np.mean(chi_fake**2.)
    #print chi_fake_avg
    #print chi_fake_avg_sq

    #print("chi_fake_avg - chi:", chi_fake_avg - chi)

    sigma = np.std(chi_fake)

    #sigma = ( (length - 1) * np.sum( (chi_fake_avg - chi)**2. ) / length )**.5

    #plt.plot(chi_fake)
    #plt.plot([0, len(chi_fake)], [chi, chi], color = 'blue', linewidth = 2)

    #plt.show()

    print chi, sigma

    return chi, sigma
