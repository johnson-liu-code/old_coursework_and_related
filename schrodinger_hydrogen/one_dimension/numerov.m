function psi_n2 = numerov(psi_n, psi_n1, h, k_n, k_n1, k_n2)
    psi_n2 = ( 2 * (1 - (5/12) * h^2 * k_n1^2) * psi_n1 - (1 - 1/12 * h^2 * k_n^2) * psi_n ) / (1 + 1/12 * h^2 * k_n2^2);
end